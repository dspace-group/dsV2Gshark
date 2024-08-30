/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    XmlValidator.h
 *
 *  @author
 *    ThorenG
 *
 *  @copyright
 *    Copyright 2024, dSPACE GmbH. All rights reserved.
 *    See LICENSE file
 *
 *<!-------------------------------------------------------------------------->*/
#pragma once

#include <libxml/xmlschemastypes.h>

class XmlValidator
{
 public:
    bool validate_xml(const char *xml, const char *xsdnamespace, char *errorOut, size_t size);
    void init_validators();
    void cleanup_validators();

 private:
    xmlSchemaValidCtxtPtr Validator_ctxt_SAP = NULL;
    xmlSchemaValidCtxtPtr Validator_ctxt_DIN = NULL;
    xmlSchemaValidCtxtPtr Validator_ctxt_ISO2 = NULL;
    xmlSchemaValidCtxtPtr Validator_ctxt_ISO20_CM = NULL;
    xmlSchemaValidCtxtPtr Validator_ctxt_ISO20_DC = NULL;
    xmlSchemaValidCtxtPtr Validator_ctxt_ISO20_AC = NULL;
    xmlSchemaValidCtxtPtr Validator_ctxt_ISO20_ACDP = NULL;
    xmlSchemaValidCtxtPtr Validator_ctxt_ISO20_WPT = NULL;

    xmlSchemaValidCtxtPtr create_parser(const char *URL);
};
