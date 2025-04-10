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
  * @file iso20_WPT_Decoder.h
  * @brief Description goes here
  *
  **/

#ifndef ISO20_WPT_DECODER_H
#define ISO20_WPT_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "exi_bitstream.h"
#include "iso20_WPT_Datatypes.h"


// main function for decoding
int decode_iso20_wpt_exiDocument(exi_bitstream_t* stream, struct iso20_wpt_exiDocument* exiDoc, char* xmlOut, size_t xmlOut_size);

#ifdef __cplusplus
}
#endif

#endif /* ISO20_WPT_DECODER_H */

