/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Copyright (C) 2022 - 2023 chargebyte GmbH
 * Copyright (C) 2022 - 2023 Contributors to EVerest
 */

/*****************************************************
 *
 * @author
 * @version
 *
 * The Code is generated! Changes may be overwritten.
 *
 *****************************************************/

/**
  * @file iso20_CommonMessages_Decoder.h
  * @brief Description goes here
  *
  **/

#ifndef ISO20_COMMON_MESSAGES_DECODER_H
#define ISO20_COMMON_MESSAGES_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "exi_bitstream.h"
#include "iso20_CommonMessages_Datatypes.h"


// main function for decoding
int decode_iso20_exiDocument(exi_bitstream_t* stream, struct iso20_exiDocument* exiDoc, char* xmlOut, size_t xmlOut_size);
// decoding function for fragment
int decode_iso20_exiFragment(exi_bitstream_t* stream, struct iso20_exiFragment* exiFrag, char* xmlOut, size_t xmlOut_size);
// decoding function for xmldsig fragment
int decode_iso20_xmldsigFragment(exi_bitstream_t* stream, struct iso20_xmldsigFragment* xmldsigFrag, char* xmlOut, size_t xmlOut_size);

#ifdef __cplusplus
}
#endif

#endif /* ISO20_COMMON_MESSAGES_DECODER_H */

