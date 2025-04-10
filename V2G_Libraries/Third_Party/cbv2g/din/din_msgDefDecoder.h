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
  * @file din_msgDefDecoder.h
  * @brief Description goes here
  *
  **/

#ifndef DIN_MSG_DEF_DECODER_H
#define DIN_MSG_DEF_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "exi_bitstream.h"
#include "din_msgDefDatatypes.h"


// main function for decoding
int decode_din_exiDocument(exi_bitstream_t* stream, struct din_exiDocument* exiDoc, char* xmlOut, size_t xmlOut_size);

#ifdef __cplusplus
}
#endif

#endif /* DIN_MSG_DEF_DECODER_H */

