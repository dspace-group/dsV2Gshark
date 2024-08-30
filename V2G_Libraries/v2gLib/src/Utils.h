/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    Utils.h
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
#include <cstdint>

#define NAMESPACE_SAP "urn:iso:15118:2:2010:AppProtocol"
#define NAMESPACE_DIN "urn:din:70121:2012:MsgDef"
#define NAMESPACE_ISO_2 "urn:iso:15118:2:2013:MsgDef"
#define NAMESPACE_ISO_20_PREFIX "urn:iso:std:iso:15118:-20"
#define NAMESPACE_ISO_20_CM "urn:iso:std:iso:15118:-20:CommonMessages"
#define NAMESPACE_ISO_20_AC "urn:iso:std:iso:15118:-20:AC"
#define NAMESPACE_ISO_20_DC "urn:iso:std:iso:15118:-20:DC"
#define NAMESPACE_ISO_20_ACDP "urn:iso:std:iso:15118:-20:ACDP"
#define NAMESPACE_ISO_20_WPT "urn:iso:std:iso:15118:-20:WPT"

uint8_t *hex_str_to_uint8(const char *string);
std::string uint8_to_hex_string(const uint8_t *v, const size_t s);

char *unzip_data(uint8_t *zipped_data, uint16_t zipped_data_length, uint16_t max_unzipped_len);
