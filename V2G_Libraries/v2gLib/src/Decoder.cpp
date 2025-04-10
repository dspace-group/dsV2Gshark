
/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    Decoder.cpp
 *
 *  @author
 *    ThorenG
 *
 *  @copyright
 *    Copyright 2024, dSPACE GmbH. All rights reserved.
 *    See LICENSE file
 *
 *<!--------------------------------------------------------------------------->*/
#include <string>
#include <cstring>
#include <exi_basetypes.h>
#include <exi_basetypes_decoder.h>
#include <exi_error_codes.h>
#include <exi_header.h>
#include <exi_types_decoder.h>
#include <iso2_msgDefDatatypes.h>
#include <iso2_msgDefDecoder.h>
#include <iso20_CommonMessages_Datatypes.h>
#include <iso20_CommonMessages_Decoder.h>
#include <iso20_DC_Datatypes.h>
#include <iso20_DC_Decoder.h>
#include <iso20_AC_Datatypes.h>
#include <iso20_AC_Decoder.h>
#include <iso20_ACDP_Datatypes.h>
#include <iso20_ACDP_Decoder.h>
#include <iso20_WPT_Datatypes.h>
#include <iso20_WPT_Decoder.h>
#include <din_msgDefDatatypes.h>
#include <din_msgDefDecoder.h>
#include <appHand_Datatypes.h>
#include <appHand_Decoder.h>
#include <exi_v2gtp.h>

#include "Utils.h"
#include "Decoder.h"

exi_bitstream_t Decoder::init_exi_bitstream(const uint8_t *buffer, size_t len)
{
    exi_bitstream_t input_stream;
    input_stream.data = const_cast<uint8_t *>(buffer);
    input_stream.byte_pos = 0;
    input_stream.bit_count = 0;
    input_stream.data_size = len;
    return input_stream;
}

template <typename T>
int Decoder::decode_exi(const uint8_t *buffer,
                        size_t len,
                        char *xmlOut,
                        size_t xmlOut_size,
                        int (*decodeFunction)(exi_bitstream_t *, T *, char *, size_t))
{
    T exi;
    exi_bitstream_t input_stream = init_exi_bitstream(buffer, len);
    return decodeFunction(&input_stream, &exi, xmlOut, xmlOut_size);
}

result_decode Decoder::decode_message(const std::string &exiIn, const std::string &schemaIn)
{
    result_decode result;

    const uint8_t *buffer = hex_str_to_uint8(exiIn.c_str());
    xml_buffer[0] = 0;  // reset buffer

    if (!buffer)
    {
        result.decoded_xml = std::string("Invalid input!");
        result.used_schema = schemaIn;
        return result;
    }
    
    size_t len = exiIn.size() / 2;

    if (schemaIn == NAMESPACE_SAP)
    {
        result.errn = decode_exi<appHand_exiDocument>(buffer, len, xml_buffer, MAX_MESSAGE_SIZE, decode_appHand_exiDocument);
    }
    else if (schemaIn == NAMESPACE_ISO_2)
    {
        result.errn = decode_exi<iso2_exiDocument>(buffer, len, xml_buffer, MAX_MESSAGE_SIZE, decode_iso2_exiDocument);
    }
    else if (schemaIn == NAMESPACE_DIN)
    {
        result.errn = decode_exi<din_exiDocument>(buffer, len, xml_buffer, MAX_MESSAGE_SIZE, decode_din_exiDocument);
    }
    else if (schemaIn == NAMESPACE_ISO_20_DC)
    {
        result.errn = decode_exi<iso20_dc_exiDocument>(buffer, len, xml_buffer, MAX_MESSAGE_SIZE, decode_iso20_dc_exiDocument);
    }
    else if (schemaIn == NAMESPACE_ISO_20_CM)
    {
        result.errn = decode_exi<iso20_exiDocument>(buffer, len, xml_buffer, MAX_MESSAGE_SIZE, decode_iso20_exiDocument);
    }
    else if (schemaIn == NAMESPACE_ISO_20_AC)
    {
        result.errn = decode_exi<iso20_ac_exiDocument>(buffer, len, xml_buffer, MAX_MESSAGE_SIZE, decode_iso20_ac_exiDocument);
    }
    else if (schemaIn == NAMESPACE_ISO_20_ACDP)
    {
        result.errn = decode_exi<iso20_acdp_exiDocument>(buffer, len, xml_buffer, MAX_MESSAGE_SIZE, decode_iso20_acdp_exiDocument);
    }
    else if (schemaIn == NAMESPACE_ISO_20_WPT)
    {
        result.errn = decode_exi<iso20_wpt_exiDocument>(buffer, len, xml_buffer, MAX_MESSAGE_SIZE, decode_iso20_wpt_exiDocument);
    }
    else
    {
        strcat(xml_buffer, "ERROR");
    }
    delete[] buffer;

    result.decoded_xml = std::string(xml_buffer);
    result.used_schema = schemaIn;
    return result;
}

result_decode Decoder::decode_message_auto_schema(const std::string &exiIn)
{
    result_decode result;

    // go through all namespaces, start with last successful
    for (size_t i = 0; i < sizeof(AUTODECODER_NAMESPACES) / sizeof(std::string); i++)
    {
        result = decode_message(exiIn, AUTODECODER_NAMESPACES[autodecoder_last_index_used]);
        if (result.errn == EXI_ERROR__NO_ERROR)
        {
            // sub-elements of messages are valid according to the XSD, but we try to decode a full message here!
            // All full messages should have a 'HEADER' element, except of SAP messages
            if (result.used_schema.compare(NAMESPACE_SAP) != 0 &&
                result.decoded_xml.find("Header>") == std::string::npos)
            {
                result.errn = EXI_ERROR__NOT_IMPLEMENTED_YET;
            }
        }
        if (result.errn == EXI_ERROR__NO_ERROR)
        {
            if (result.used_schema.find(NAMESPACE_ISO_20_PREFIX) == 0)
            {
                // if any -20 message was decoded, start with -20 CM next time
                autodecoder_last_index_used = AUTODECODER_NAMESPACES_INDEX_20_GROUP;
            }
            break;
        }
        else
        {
            autodecoder_last_index_used = (autodecoder_last_index_used + 1) %
                                          (sizeof(AUTODECODER_NAMESPACES) / sizeof(std::string));
        }
    }

    return result;
}