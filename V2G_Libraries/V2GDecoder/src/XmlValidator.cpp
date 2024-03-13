/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    XmlValidator.cpp
 *
 *  @author
 *    ThorenG
 *
 *  @copyright
 *    Copyright 2024, dSPACE GmbH. All rights reserved.
 *    See LICENSE file
 *
 *<!-------------------------------------------------------------------------->*/
#include <libxml/xmlschemastypes.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <cstring>
#include <cstdint>

#include "XmlValidator.h"
#include "Utils.h"
#include "Schemas.h"

// we ignore the following validation error because the decoder gives us a hex-string instead of a big int
constexpr const char* VALIDATION_ERROR_X509SN_PREFIX = "Element '{http://www.w3.org/2000/09/xmldsig#}X509SerialNumber'";
constexpr uint16_t VALIDATION_ERROR_X509SN_PREFIX_LEN = 62;

// libxml XSD callbacks:
static int rlen = 0; // rest len of string we are reading right now
static int plen = 0; // already processed len

static void *xsd_prepare(uint8_t *zipped_data, uint16_t zipped_data_length)
{
    char *XSD_unzipped = unzip_data(zipped_data, zipped_data_length, MAX_UNZIPPED_LEN);
    rlen = strlen(XSD_unzipped);
    return ((void *)XSD_unzipped);
}

static void *xsd_open(const char *URI)
{
    if (URI == NULL)
    {
        return 0;
    }
    plen = 0;

    // common xsd
    if (strcmp("schemas/common/V2G_CI_AppProtocol.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_SAP, XSD_SAP_zipped_len);
    }

    // ISO 15118-20 XSDs
    else if (strcmp("schemas/15118-20/V2G_CI_DC.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO20_DC, XSD_ISO20_DC_zipped_len);
    }
    else if (strcmp("schemas/15118-20/V2G_CI_CommonTypes.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO20_CommonTypes, XSD_ISO20_CommonTypes_zipped_len);
    }
    else if (strcmp("schemas/15118-20/V2G_CI_CommonMessages.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO20_CM, XSD_ISO20_CM_zipped_len);
    }
    else if (strcmp("schemas/15118-20/V2G_CI_ACDP.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO20_ACDP, XSD_ISO20_ACDP_zipped_len);
    }
    else if (strcmp("schemas/15118-20/V2G_CI_AC.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO20_AC, XSD_ISO20_AC_zipped_len);
    }
    else if (strcmp("schemas/15118-20/V2G_CI_WPT.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO20_WPT, XSD_ISO20_WPT_zipped_len);
    }
    else if (strcmp("schemas/15118-20/xmldsig-core-schema.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_XMLDSIG_CORE, XSD_XMLDSIG_CORE_zipped_len);
    }

    // ISO2
    else if (strcmp("schemas/15118-2/V2G_CI_MsgBody.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO2_MsgBody, XSD_ISO2_MsgBody_zipped_len);
    }
    else if (strcmp("schemas/15118-2/V2G_CI_MsgDataTypes.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO2_MsgDataTypes, XSD_ISO2_MsgDataTypes_zipped_len);
    }
    else if (strcmp("schemas/15118-2/V2G_CI_MsgDef.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO2_MsgDef, XSD_ISO2_MsgDef_zipped_len);
    }
    else if (strcmp("schemas/15118-2/V2G_CI_MsgHeader.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_ISO2_MsgHeader, XSD_ISO2_MsgHeader_zipped_len);
    }
    else if (strcmp("schemas/15118-2/xmldsig-core-schema.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_XMLDSIG_CORE, XSD_XMLDSIG_CORE_zipped_len);
    }

    // DIN
    else if (strcmp("schemas/DIN/V2G_CI_MsgBody.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_DIN_MsgBody, XSD_DIN_MsgBody_zipped_len);
    }
    else if (strcmp("schemas/DIN/V2G_CI_MsgDataTypes.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_DIN_MsgDataTypes, XSD_DIN_MsgDataTypes_zipped_len);
    }
    else if (strcmp("schemas/DIN/V2G_CI_MsgDef.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_DIN_MsgDef, XSD_DIN_MsgDef_zipped_len);
    }
    else if (strcmp("schemas/DIN/V2G_CI_MsgHeader.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_DIN_MsgHeader, XSD_DIN_MsgHeader_zipped_len);
    }
    else if (strcmp("schemas/DIN/xmldsig-core-schema.xsd", URI) == 0)
    {
        return xsd_prepare(XSD_XMLDSIG_CORE, XSD_XMLDSIG_CORE_zipped_len);
    }

    rlen = 0;
    return NULL;
}

static int xsd_close(void *context)
{
    rlen = 0;
    free(context); // memory was allocated in 'unzip_data' (xsd_open)
    return (0);
}

static int xsd_read(void *context, char *buffer, int len)
{
    // the buffer can only hold 4000 bytes
    // we have to copy here len bytes from context[plen] to context[plen+len]
    const char *ptr = (const char *)context;

    if ((context == NULL) || (buffer == NULL) || (len < 0))
        return (-1);

    if (len > rlen)
        len = rlen;
    memcpy(buffer, ptr + plen, len);
    rlen -= len;
    plen += len;
    return (len);
}

static int xsd_match(const char *URI)
{
    if (URI == NULL)
    {
        return 0;
    }

    if (strncmp("schemas/", URI, 8) == 0)
    {
        return 1;
    }

    return 0;
}

static void xsd_parse_error_handler(void *arg, xmlErrorPtr error)
{
    *((bool *)arg) = true;
}

xmlSchemaValidCtxtPtr XmlValidator::create_parser(const char *URL)
{
    xmlSchemaParserCtxtPtr schema_parser_ctxt = xmlSchemaNewParserCtxt(URL);
    if (schema_parser_ctxt)
    {
        xmlSchemaPtr schema = xmlSchemaParse(schema_parser_ctxt);
        xmlSchemaFreeParserCtxt(schema_parser_ctxt);
        if (schema)
        {
            return xmlSchemaNewValidCtxt(schema);
        }
    }
    return NULL;
}

void XmlValidator::init_validators()
{
    xmlInitParser();
    if (xmlRegisterInputCallbacks(xsd_match, xsd_open, xsd_read, xsd_close) < 0)
    {
        fprintf(stderr, "failed to register internal xsd handler\n");
        exit(1);
    }
    Validator_ctxt_SAP = create_parser("schemas/common/V2G_CI_AppProtocol.xsd");
    Validator_ctxt_DIN = create_parser("schemas/DIN/V2G_CI_MsgDef.xsd");
    Validator_ctxt_ISO2 = create_parser("schemas/15118-2/V2G_CI_MsgDef.xsd");
    Validator_ctxt_ISO20_CM = create_parser("schemas/15118-20/V2G_CI_CommonMessages.xsd");
    Validator_ctxt_ISO20_DC = create_parser("schemas/15118-20/V2G_CI_DC.xsd");
    Validator_ctxt_ISO20_AC = create_parser("schemas/15118-20/V2G_CI_AC.xsd");
    Validator_ctxt_ISO20_ACDP = create_parser("schemas/15118-20/V2G_CI_ACDP.xsd");
    Validator_ctxt_ISO20_WPT = create_parser("schemas/15118-20/V2G_CI_WPT.xsd");
}

void XmlValidator::cleanup_validators()
{
    xmlSchemaCleanupTypes();
    xmlCleanupParser();
}

/**
 * @param xml
 * @param xsdnamespace
 * @param errorOut Buffer where error message is written to
 * @param size length of errorOut Buffer
 * @return true valid
 * @return false not valid
 */
bool XmlValidator::validate_xml(const char *xml, const char *xsdnamespace, char *errorOut, size_t size)
{
    bool valid = false;
    int has_schema_errors = 0;
    int ret = -1;
    xmlSchemaValidCtxtPtr valid_ctxt = NULL;

    if (strcmp(NAMESPACE_SAP, xsdnamespace) == 0)
    {
        valid_ctxt = Validator_ctxt_SAP;
    }
    else if (strcmp(NAMESPACE_DIN, xsdnamespace) == 0)
    {
        valid_ctxt = Validator_ctxt_DIN;
    }
    else if (strcmp(NAMESPACE_ISO_2, xsdnamespace) == 0)
    {
        valid_ctxt = Validator_ctxt_ISO2;
    }
    else if (strcmp(NAMESPACE_ISO_20_CM, xsdnamespace) == 0)
    {
        valid_ctxt = Validator_ctxt_ISO20_CM;
    }
    else if (strcmp(NAMESPACE_ISO_20_DC, xsdnamespace) == 0)
    {
        valid_ctxt = Validator_ctxt_ISO20_DC;
    }
    else if (strcmp(NAMESPACE_ISO_20_AC, xsdnamespace) == 0)
    {
        valid_ctxt = Validator_ctxt_ISO20_AC;
    }
    else if (strcmp(NAMESPACE_ISO_20_ACDP, xsdnamespace) == 0)
    {
        valid_ctxt = Validator_ctxt_ISO20_ACDP;
    }
    else if (strcmp(NAMESPACE_ISO_20_WPT, xsdnamespace) == 0)
    {
        valid_ctxt = Validator_ctxt_ISO20_WPT;
    }

    xmlTextReaderPtr reader = NULL;
    reader = xmlReaderForMemory(xml, strlen(xml), "v2g_msg.xml", NULL, 0);

    if (reader != NULL)
    {
        if (valid_ctxt)
        {
            xmlTextReaderSchemaValidateCtxt(reader, valid_ctxt, 0);
            xmlSchemaSetValidStructuredErrors(valid_ctxt, xsd_parse_error_handler, &has_schema_errors);
        }
        ret = xmlTextReaderRead(reader);
        while (ret == 1 && !has_schema_errors)
        {
            //... procesing informations
            ret = xmlTextReaderRead(reader);
        }
    }

    if (ret != 0)
    {
        xmlErrorPtr err = xmlGetLastError();

        if (strncmp(err->message, VALIDATION_ERROR_X509SN_PREFIX, VALIDATION_ERROR_X509SN_PREFIX_LEN) == 0)
        {
            // we expect this error, because we decode the serial number as hex, not int
            valid = true;
        }
        else
        {
            size_t errorlength = strlen(err->message);
            if (errorlength > size)
            {
                errorlength = size;
            }
            memcpy(errorOut, err->message, errorlength);
            valid = false;
        }
    }
    else
    {
        valid = true;
    }
    xmlFreeTextReader(reader);
    return valid;
}
