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
  * @file iso20_ACDP_Decoder.h
  * @brief Description goes here
  *
  **/

#ifndef ISO20_ACDP_DECODER_H
#define ISO20_ACDP_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "exi_bitstream.h"
#include "iso20_ACDP_Datatypes.h"


// main function for decoding
int decode_iso20_acdp_exiDocument(exi_bitstream_t* stream, struct iso20_acdp_exiDocument* exiDoc, char* xmlOut, size_t xmlOut_size);

#ifdef __cplusplus
}
#endif

#endif /* ISO20_ACDP_DECODER_H */

