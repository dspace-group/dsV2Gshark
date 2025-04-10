/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    Decoder.h
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

#include <string>
#include <exi_bitstream.h>

#include "Utils.h"

constexpr size_t MAX_MESSAGE_SIZE = 524288; // 512kb

struct result_decode
{
    int errn = EXI_ERROR__DECODER_NOT_IMPLEMENTED;
    std::string decoded_xml = "ERROR";
    std::string used_schema = "ERROR";
};

class Decoder
{
 public:
    result_decode decode_message(const std::string &exiIn, const std::string &schemaIn);
    result_decode decode_message_auto_schema(const std::string &exiIn);

 private:
    exi_bitstream_t init_exi_bitstream(const uint8_t *buffer, size_t len);
    template <typename T>
    int decode_exi(const uint8_t *buffer,
                   size_t len,
                   char *xmlOut,
                   size_t xmlOut_size,
                   int (*decodeFunction)(exi_bitstream_t *, T *, char *, size_t));

    const std::string AUTODECODER_NAMESPACES[8] = {
        NAMESPACE_SAP,
        NAMESPACE_DIN,
        NAMESPACE_ISO_2,
        NAMESPACE_ISO_20_CM,
        NAMESPACE_ISO_20_AC,
        NAMESPACE_ISO_20_DC,
        NAMESPACE_ISO_20_ACDP,
        NAMESPACE_ISO_20_WPT};
    const int AUTODECODER_NAMESPACES_INDEX_20_GROUP = 3;

    int autodecoder_last_index_used = 0;
    char xml_buffer[MAX_MESSAGE_SIZE] = {};
};
