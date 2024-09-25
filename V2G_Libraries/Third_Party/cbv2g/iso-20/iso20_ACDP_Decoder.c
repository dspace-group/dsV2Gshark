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
  * @file iso20_ACDP_Decoder.c
  * @brief Description goes here
  *
  **/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "exi_basetypes.h"
#include "exi_types_decoder.h"
#include "exi_basetypes_decoder.h"
#include "exi_error_codes.h"
#include "exi_header.h"
#include "iso20_ACDP_Datatypes.h"
#include "iso20_ACDP_Decoder.h"



static int decode_iso20_acdp_TransformType(exi_bitstream_t* stream, struct iso20_acdp_TransformType* TransformType, char* xmlOut);
static int decode_iso20_acdp_TransformsType(exi_bitstream_t* stream, struct iso20_acdp_TransformsType* TransformsType, char* xmlOut);
static int decode_iso20_acdp_DSAKeyValueType(exi_bitstream_t* stream, struct iso20_acdp_DSAKeyValueType* DSAKeyValueType, char* xmlOut);
static int decode_iso20_acdp_X509IssuerSerialType(exi_bitstream_t* stream, struct iso20_acdp_X509IssuerSerialType* X509IssuerSerialType, char* xmlOut);
static int decode_iso20_acdp_DigestMethodType(exi_bitstream_t* stream, struct iso20_acdp_DigestMethodType* DigestMethodType, char* xmlOut);
static int decode_iso20_acdp_RSAKeyValueType(exi_bitstream_t* stream, struct iso20_acdp_RSAKeyValueType* RSAKeyValueType, char* xmlOut);
static int decode_iso20_acdp_CanonicalizationMethodType(exi_bitstream_t* stream, struct iso20_acdp_CanonicalizationMethodType* CanonicalizationMethodType, char* xmlOut);
static int decode_iso20_acdp_SignatureMethodType(exi_bitstream_t* stream, struct iso20_acdp_SignatureMethodType* SignatureMethodType, char* xmlOut);
static int decode_iso20_acdp_KeyValueType(exi_bitstream_t* stream, struct iso20_acdp_KeyValueType* KeyValueType, char* xmlOut);
static int decode_iso20_acdp_ReferenceType(exi_bitstream_t* stream, struct iso20_acdp_ReferenceType* ReferenceType, char* xmlOut);
static int decode_iso20_acdp_RetrievalMethodType(exi_bitstream_t* stream, struct iso20_acdp_RetrievalMethodType* RetrievalMethodType, char* xmlOut);
static int decode_iso20_acdp_X509DataType(exi_bitstream_t* stream, struct iso20_acdp_X509DataType* X509DataType, char* xmlOut);
static int decode_iso20_acdp_PGPDataType(exi_bitstream_t* stream, struct iso20_acdp_PGPDataType* PGPDataType, char* xmlOut);
static int decode_iso20_acdp_SPKIDataType(exi_bitstream_t* stream, struct iso20_acdp_SPKIDataType* SPKIDataType, char* xmlOut);
static int decode_iso20_acdp_SignedInfoType(exi_bitstream_t* stream, struct iso20_acdp_SignedInfoType* SignedInfoType, char* xmlOut);
static int decode_iso20_acdp_SignatureValueType(exi_bitstream_t* stream, struct iso20_acdp_SignatureValueType* SignatureValueType, char* xmlOut);
static int decode_iso20_acdp_KeyInfoType(exi_bitstream_t* stream, struct iso20_acdp_KeyInfoType* KeyInfoType, char* xmlOut);
static int decode_iso20_acdp_ObjectType(exi_bitstream_t* stream, struct iso20_acdp_ObjectType* ObjectType, char* xmlOut);
static int decode_iso20_acdp_SignatureType(exi_bitstream_t* stream, struct iso20_acdp_SignatureType* SignatureType, char* xmlOut);
static int decode_iso20_acdp_RationalNumberType(exi_bitstream_t* stream, struct iso20_acdp_RationalNumberType* RationalNumberType, char* xmlOut);
static int decode_iso20_acdp_MessageHeaderType(exi_bitstream_t* stream, struct iso20_acdp_MessageHeaderType* MessageHeaderType, char* xmlOut);
static int decode_iso20_acdp_SignaturePropertyType(exi_bitstream_t* stream, struct iso20_acdp_SignaturePropertyType* SignaturePropertyType, char* xmlOut);
static int decode_iso20_acdp_EVTechnicalStatusType(exi_bitstream_t* stream, struct iso20_acdp_EVTechnicalStatusType* EVTechnicalStatusType, char* xmlOut);
static int decode_iso20_acdp_ACDP_VehiclePositioningReqType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_VehiclePositioningReqType* ACDP_VehiclePositioningReqType, char* xmlOut);
static int decode_iso20_acdp_ACDP_VehiclePositioningResType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_VehiclePositioningResType* ACDP_VehiclePositioningResType, char* xmlOut);
static int decode_iso20_acdp_ACDP_ConnectReqType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_ConnectReqType* ACDP_ConnectReqType, char* xmlOut);
static int decode_iso20_acdp_ACDP_ConnectResType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_ConnectResType* ACDP_ConnectResType, char* xmlOut);
static int decode_iso20_acdp_ACDP_SystemStatusReqType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_SystemStatusReqType* ACDP_SystemStatusReqType, char* xmlOut);
static int decode_iso20_acdp_ACDP_SystemStatusResType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_SystemStatusResType* ACDP_SystemStatusResType, char* xmlOut);
static int decode_iso20_acdp_CLReqControlModeType(exi_bitstream_t* stream, struct iso20_acdp_CLReqControlModeType* CLReqControlModeType, char* xmlOut);
static int decode_iso20_acdp_CLResControlModeType(exi_bitstream_t* stream, struct iso20_acdp_CLResControlModeType* CLResControlModeType, char* xmlOut);
static int decode_iso20_acdp_ManifestType(exi_bitstream_t* stream, struct iso20_acdp_ManifestType* ManifestType, char* xmlOut);
static int decode_iso20_acdp_SignaturePropertiesType(exi_bitstream_t* stream, struct iso20_acdp_SignaturePropertiesType* SignaturePropertiesType, char* xmlOut);

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}Transform; type={http://www.w3.org/2000/09/xmldsig#}TransformType; base type=; content type=mixed;
//          abstract=False; final=False; choice=True;
// Particle: Algorithm, anyURI (1, 1); ANY, anyType (0, 1); XPath, string (0, 1);
static int decode_iso20_acdp_TransformType(exi_bitstream_t* stream, struct iso20_acdp_TransformType* TransformType, char* xmlOut) {
    int grammar_id = 0;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_TransformType(TransformType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 0:
            // Grammar: ID=0; read/write bits=1; START (Algorithm)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Algorithm, anyURI (anyURI)); next=1

                    strcat(xmlOut, " Algorithm");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &TransformType->Algorithm.charactersLen);
                    if (error == 0)
                    {
                        if (TransformType->Algorithm.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            TransformType->Algorithm.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, TransformType->Algorithm.charactersLen, TransformType->Algorithm.characters, iso20_acdp_Algorithm_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < TransformType->Algorithm.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(TransformType->Algorithm.characters[i]))
                                {
                                    TransformType->Algorithm.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, TransformType->Algorithm.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    grammar_id = 1;

                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 1:
            // Grammar: ID=1; read/write bits=3; START (XPath), START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (XPath, string (string)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}XPath");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}XPath");
                    // decode: string (len, characters)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            error = exi_basetypes_decoder_uint_16(stream, &TransformType->XPath.charactersLen);
                            if (error == 0)
                            {
                                if (TransformType->XPath.charactersLen >= 2)
                                {
                                    // string tables and table partitions are not supported, so the length has to be decremented by 2
                                    TransformType->XPath.charactersLen -= 2;
                                    error = exi_basetypes_decoder_characters(stream, TransformType->XPath.charactersLen, TransformType->XPath.characters, iso20_acdp_XPath_CHARACTER_SIZE);
                                    strcat(xmlOut, ">");
                                    for(int i = 0; i < TransformType->XPath.charactersLen; i++) { // check for unprintable characters
                                        if(!isprint(TransformType->XPath.characters[i]))
                                        {
                                            TransformType->XPath.characters[i]   = '?';
                                        }
                                    }
                                    strcat(xmlOut, TransformType->XPath.characters);
                                }
                                else
                                {
                                    // the string seems to be in the table, but this is not supported
                                    error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                                }
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_characters is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                TransformType->XPath_isUsed = 1u;
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}XPath>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 2:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 3:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &TransformType->ANY.bytesLen, &TransformType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((TransformType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < TransformType->ANY.bytesLen;) {
                            uint32_t octet_a = i < TransformType->ANY.bytesLen ? (unsigned char) TransformType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < TransformType->ANY.bytesLen ? (unsigned char) TransformType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < TransformType->ANY.bytesLen ? (unsigned char) TransformType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[TransformType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        TransformType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}Transforms; type={http://www.w3.org/2000/09/xmldsig#}TransformsType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: Transform, TransformType (1, 1);
static int decode_iso20_acdp_TransformsType(exi_bitstream_t* stream, struct iso20_acdp_TransformsType* TransformsType, char* xmlOut) {
    int grammar_id = 4;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_TransformsType(TransformsType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 4:
            // Grammar: ID=4; read/write bits=1; START (Transform)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Transform, TransformType (TransformType)); next=5

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transform");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Transform");
                    // decode: element
                    error = decode_iso20_acdp_TransformType(stream, &TransformsType->Transform, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 5;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transform>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 5:
            // Grammar: ID=5; read/write bits=2; START (Transform), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Transform, TransformType (TransformType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transform");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Transform");
                    // decode: element
                    error = decode_iso20_acdp_TransformType(stream, &TransformsType->Transform, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transform>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}DSAKeyValue; type={http://www.w3.org/2000/09/xmldsig#}DSAKeyValueType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: P, CryptoBinary (0, 1)(was 1, 1)(seq. ['P', 'Q']); Q, CryptoBinary (0, 1)(was 1, 1)(seq. ['P', 'Q']); G, CryptoBinary (0, 1); Y, CryptoBinary (1, 1); J, CryptoBinary (0, 1); Seed, CryptoBinary (0, 1)(was 1, 1)(seq. ['Seed', 'PgenCounter']); PgenCounter, CryptoBinary (0, 1)(was 1, 1)(seq. ['Seed', 'PgenCounter']);
static int decode_iso20_acdp_DSAKeyValueType(exi_bitstream_t* stream, struct iso20_acdp_DSAKeyValueType* DSAKeyValueType, char* xmlOut) {
    int grammar_id = 6;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_DSAKeyValueType(DSAKeyValueType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 6:
            // Grammar: ID=6; read/write bits=2; START (P), START (G), START (Y)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (P, CryptoBinary (base64Binary)); next=7

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}P");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}P");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->P.bytesLen, &DSAKeyValueType->P.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->P.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->P.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->P.bytesLen ? (unsigned char) DSAKeyValueType->P.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->P.bytesLen ? (unsigned char) DSAKeyValueType->P.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->P.bytesLen ? (unsigned char) DSAKeyValueType->P.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->P.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        DSAKeyValueType->P_isUsed = 1u;
                        grammar_id = 7;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}P>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (G, CryptoBinary (base64Binary)); next=9

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}G");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}G");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->G.bytesLen, &DSAKeyValueType->G.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->G.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->G.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->G.bytesLen ? (unsigned char) DSAKeyValueType->G.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->G.bytesLen ? (unsigned char) DSAKeyValueType->G.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->G.bytesLen ? (unsigned char) DSAKeyValueType->G.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->G.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        DSAKeyValueType->G_isUsed = 1u;
                        grammar_id = 9;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}G>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (Y, CryptoBinary (base64Binary)); next=10

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Y");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Y");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->Y.bytesLen, &DSAKeyValueType->Y.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->Y.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->Y.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->Y.bytesLen ? (unsigned char) DSAKeyValueType->Y.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->Y.bytesLen ? (unsigned char) DSAKeyValueType->Y.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->Y.bytesLen ? (unsigned char) DSAKeyValueType->Y.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->Y.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        grammar_id = 10;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Y>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 7:
            // Grammar: ID=7; read/write bits=1; START (Q)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Q, CryptoBinary (base64Binary)); next=8

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Q");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Q");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->Q.bytesLen, &DSAKeyValueType->Q.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->Q.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->Q.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->Q.bytesLen ? (unsigned char) DSAKeyValueType->Q.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->Q.bytesLen ? (unsigned char) DSAKeyValueType->Q.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->Q.bytesLen ? (unsigned char) DSAKeyValueType->Q.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->Q.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        DSAKeyValueType->Q_isUsed = 1u;
                        grammar_id = 8;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Q>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 8:
            // Grammar: ID=8; read/write bits=2; START (G), START (Y)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (G, CryptoBinary (base64Binary)); next=9

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}G");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}G");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->G.bytesLen, &DSAKeyValueType->G.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->G.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->G.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->G.bytesLen ? (unsigned char) DSAKeyValueType->G.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->G.bytesLen ? (unsigned char) DSAKeyValueType->G.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->G.bytesLen ? (unsigned char) DSAKeyValueType->G.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->G.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        DSAKeyValueType->G_isUsed = 1u;
                        grammar_id = 9;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}G>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (Y, CryptoBinary (base64Binary)); next=10

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Y");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Y");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->Y.bytesLen, &DSAKeyValueType->Y.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->Y.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->Y.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->Y.bytesLen ? (unsigned char) DSAKeyValueType->Y.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->Y.bytesLen ? (unsigned char) DSAKeyValueType->Y.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->Y.bytesLen ? (unsigned char) DSAKeyValueType->Y.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->Y.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        grammar_id = 10;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Y>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 9:
            // Grammar: ID=9; read/write bits=1; START (Y)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Y, CryptoBinary (base64Binary)); next=10

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Y");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Y");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->Y.bytesLen, &DSAKeyValueType->Y.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->Y.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->Y.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->Y.bytesLen ? (unsigned char) DSAKeyValueType->Y.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->Y.bytesLen ? (unsigned char) DSAKeyValueType->Y.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->Y.bytesLen ? (unsigned char) DSAKeyValueType->Y.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->Y.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        grammar_id = 10;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Y>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 10:
            // Grammar: ID=10; read/write bits=2; START (J), START (Seed), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (J, CryptoBinary (base64Binary)); next=11

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}J");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}J");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->J.bytesLen, &DSAKeyValueType->J.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->J.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->J.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->J.bytesLen ? (unsigned char) DSAKeyValueType->J.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->J.bytesLen ? (unsigned char) DSAKeyValueType->J.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->J.bytesLen ? (unsigned char) DSAKeyValueType->J.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->J.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        DSAKeyValueType->J_isUsed = 1u;
                        grammar_id = 11;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}J>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (Seed, CryptoBinary (base64Binary)); next=12

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Seed");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Seed");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->Seed.bytesLen, &DSAKeyValueType->Seed.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->Seed.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->Seed.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->Seed.bytesLen ? (unsigned char) DSAKeyValueType->Seed.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->Seed.bytesLen ? (unsigned char) DSAKeyValueType->Seed.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->Seed.bytesLen ? (unsigned char) DSAKeyValueType->Seed.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->Seed.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        DSAKeyValueType->Seed_isUsed = 1u;
                        grammar_id = 12;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Seed>");
                    }
                    break;
                case 2:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 11:
            // Grammar: ID=11; read/write bits=2; START (Seed), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Seed, CryptoBinary (base64Binary)); next=12

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Seed");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Seed");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->Seed.bytesLen, &DSAKeyValueType->Seed.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->Seed.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->Seed.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->Seed.bytesLen ? (unsigned char) DSAKeyValueType->Seed.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->Seed.bytesLen ? (unsigned char) DSAKeyValueType->Seed.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->Seed.bytesLen ? (unsigned char) DSAKeyValueType->Seed.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->Seed.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        DSAKeyValueType->Seed_isUsed = 1u;
                        grammar_id = 12;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Seed>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 12:
            // Grammar: ID=12; read/write bits=2; START (PgenCounter), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (PgenCounter, CryptoBinary (base64Binary)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}PgenCounter");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}PgenCounter");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DSAKeyValueType->PgenCounter.bytesLen, &DSAKeyValueType->PgenCounter.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DSAKeyValueType->PgenCounter.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DSAKeyValueType->PgenCounter.bytesLen;) {
                            uint32_t octet_a = i < DSAKeyValueType->PgenCounter.bytesLen ? (unsigned char) DSAKeyValueType->PgenCounter.bytes[i++] : 0;
                            uint32_t octet_b = i < DSAKeyValueType->PgenCounter.bytesLen ? (unsigned char) DSAKeyValueType->PgenCounter.bytes[i++] : 0;
                            uint32_t octet_c = i < DSAKeyValueType->PgenCounter.bytesLen ? (unsigned char) DSAKeyValueType->PgenCounter.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DSAKeyValueType->PgenCounter.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        DSAKeyValueType->PgenCounter_isUsed = 1u;
                        grammar_id = 2;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}PgenCounter>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}X509IssuerSerial; type={http://www.w3.org/2000/09/xmldsig#}X509IssuerSerialType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: X509IssuerName, string (1, 1); X509SerialNumber, integer (1, 1);
static int decode_iso20_acdp_X509IssuerSerialType(exi_bitstream_t* stream, struct iso20_acdp_X509IssuerSerialType* X509IssuerSerialType, char* xmlOut) {
    int grammar_id = 13;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_X509IssuerSerialType(X509IssuerSerialType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 13:
            // Grammar: ID=13; read/write bits=1; START (X509IssuerName)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (X509IssuerName, string (string)); next=14

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509IssuerName");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}X509IssuerName");
                    // decode: string (len, characters)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            error = exi_basetypes_decoder_uint_16(stream, &X509IssuerSerialType->X509IssuerName.charactersLen);
                            if (error == 0)
                            {
                                if (X509IssuerSerialType->X509IssuerName.charactersLen >= 2)
                                {
                                    // string tables and table partitions are not supported, so the length has to be decremented by 2
                                    X509IssuerSerialType->X509IssuerName.charactersLen -= 2;
                                    error = exi_basetypes_decoder_characters(stream, X509IssuerSerialType->X509IssuerName.charactersLen, X509IssuerSerialType->X509IssuerName.characters, iso20_acdp_X509IssuerName_CHARACTER_SIZE);
                                    strcat(xmlOut, ">");
                                    for(int i = 0; i < X509IssuerSerialType->X509IssuerName.charactersLen; i++) { // check for unprintable characters
                                        if(!isprint(X509IssuerSerialType->X509IssuerName.characters[i]))
                                        {
                                            X509IssuerSerialType->X509IssuerName.characters[i]   = '?';
                                        }
                                    }
                                    strcat(xmlOut, X509IssuerSerialType->X509IssuerName.characters);
                                }
                                else
                                {
                                    // the string seems to be in the table, but this is not supported
                                    error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                                }
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_characters is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 14;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509IssuerName>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 14:
            // Grammar: ID=14; read/write bits=1; START (X509SerialNumber)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (X509SerialNumber, integer (decimal)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509SerialNumber");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}X509SerialNumber");
                    // decode: signed
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        error = exi_basetypes_decoder_signed(stream, &X509IssuerSerialType->X509SerialNumber);
                        if (error == 0)
                        {
                            uint8_t realInteger[21] = {0}; // max length: 20 + 1 zero terminator
                            size_t realInteger_size = 0;
                            int result = exi_basetypes_convert_bytes_from_unsigned(&(X509IssuerSerialType->X509SerialNumber.data), &realInteger[0], &realInteger_size, 21);
                            if (result == 0)
                            {
                                // reverse array
                                uint8_t temp;
                                uint8_t start = 0;
                                uint8_t end = realInteger_size - 1;
                                while (start < end) {
                                    temp = realInteger[start];
                                    realInteger[start] = realInteger[end];
                                    realInteger[end] = temp;
                                    start++;
                                    end--;
                                }
                                char asHex[128] = "";
                                char* ahPtr = &asHex[0];
                                uint8_t* contentPtr = &realInteger[0];
                                if(realInteger_size * 2 + 1 > 128) {  error = -2; strcat(xmlOut, "DECODE_ERROR"); break; }
                                while(realInteger_size--) {
                                  sprintf(ahPtr, "%02X", *contentPtr);
                                  ahPtr += 2;
                                  ++contentPtr;
                                }
                                *ahPtr = 0;
                                strcat(xmlOut, ">0x");
                                strcat(xmlOut, asHex);
                            }
                            else
                            {
                                strcat(xmlOut, ">ERROR");
                            }
                            grammar_id = 2;
                        }
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509SerialNumber>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}DigestMethod; type={http://www.w3.org/2000/09/xmldsig#}DigestMethodType; base type=; content type=mixed;
//          abstract=False; final=False;
// Particle: Algorithm, anyURI (1, 1); ANY, anyType (0, 1);
static int decode_iso20_acdp_DigestMethodType(exi_bitstream_t* stream, struct iso20_acdp_DigestMethodType* DigestMethodType, char* xmlOut) {
    int grammar_id = 15;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_DigestMethodType(DigestMethodType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 15:
            // Grammar: ID=15; read/write bits=1; START (Algorithm)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Algorithm, anyURI (anyURI)); next=16

                    strcat(xmlOut, " Algorithm");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &DigestMethodType->Algorithm.charactersLen);
                    if (error == 0)
                    {
                        if (DigestMethodType->Algorithm.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            DigestMethodType->Algorithm.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, DigestMethodType->Algorithm.charactersLen, DigestMethodType->Algorithm.characters, iso20_acdp_Algorithm_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < DigestMethodType->Algorithm.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(DigestMethodType->Algorithm.characters[i]))
                                {
                                    DigestMethodType->Algorithm.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, DigestMethodType->Algorithm.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    grammar_id = 16;

                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 16:
            // Grammar: ID=16; read/write bits=2; START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 2:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &DigestMethodType->ANY.bytesLen, &DigestMethodType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((DigestMethodType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < DigestMethodType->ANY.bytesLen;) {
                            uint32_t octet_a = i < DigestMethodType->ANY.bytesLen ? (unsigned char) DigestMethodType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < DigestMethodType->ANY.bytesLen ? (unsigned char) DigestMethodType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < DigestMethodType->ANY.bytesLen ? (unsigned char) DigestMethodType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[DigestMethodType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        DigestMethodType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}RSAKeyValue; type={http://www.w3.org/2000/09/xmldsig#}RSAKeyValueType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: Modulus, CryptoBinary (1, 1); Exponent, CryptoBinary (1, 1);
static int decode_iso20_acdp_RSAKeyValueType(exi_bitstream_t* stream, struct iso20_acdp_RSAKeyValueType* RSAKeyValueType, char* xmlOut) {
    int grammar_id = 17;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_RSAKeyValueType(RSAKeyValueType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 17:
            // Grammar: ID=17; read/write bits=1; START (Modulus)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Modulus, CryptoBinary (base64Binary)); next=18

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Modulus");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Modulus");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &RSAKeyValueType->Modulus.bytesLen, &RSAKeyValueType->Modulus.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((RSAKeyValueType->Modulus.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < RSAKeyValueType->Modulus.bytesLen;) {
                            uint32_t octet_a = i < RSAKeyValueType->Modulus.bytesLen ? (unsigned char) RSAKeyValueType->Modulus.bytes[i++] : 0;
                            uint32_t octet_b = i < RSAKeyValueType->Modulus.bytesLen ? (unsigned char) RSAKeyValueType->Modulus.bytes[i++] : 0;
                            uint32_t octet_c = i < RSAKeyValueType->Modulus.bytesLen ? (unsigned char) RSAKeyValueType->Modulus.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[RSAKeyValueType->Modulus.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        grammar_id = 18;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Modulus>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 18:
            // Grammar: ID=18; read/write bits=1; START (Exponent)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Exponent, CryptoBinary (base64Binary)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Exponent");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Exponent");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &RSAKeyValueType->Exponent.bytesLen, &RSAKeyValueType->Exponent.bytes[0], iso20_acdp_CryptoBinary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((RSAKeyValueType->Exponent.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < RSAKeyValueType->Exponent.bytesLen;) {
                            uint32_t octet_a = i < RSAKeyValueType->Exponent.bytesLen ? (unsigned char) RSAKeyValueType->Exponent.bytes[i++] : 0;
                            uint32_t octet_b = i < RSAKeyValueType->Exponent.bytesLen ? (unsigned char) RSAKeyValueType->Exponent.bytes[i++] : 0;
                            uint32_t octet_c = i < RSAKeyValueType->Exponent.bytesLen ? (unsigned char) RSAKeyValueType->Exponent.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[RSAKeyValueType->Exponent.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        grammar_id = 2;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Exponent>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethod; type={http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethodType; base type=; content type=mixed;
//          abstract=False; final=False;
// Particle: Algorithm, anyURI (1, 1); ANY, anyType (0, 1);
static int decode_iso20_acdp_CanonicalizationMethodType(exi_bitstream_t* stream, struct iso20_acdp_CanonicalizationMethodType* CanonicalizationMethodType, char* xmlOut) {
    int grammar_id = 19;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_CanonicalizationMethodType(CanonicalizationMethodType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 19:
            // Grammar: ID=19; read/write bits=1; START (Algorithm)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Algorithm, anyURI (anyURI)); next=20

                    strcat(xmlOut, " Algorithm");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &CanonicalizationMethodType->Algorithm.charactersLen);
                    if (error == 0)
                    {
                        if (CanonicalizationMethodType->Algorithm.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            CanonicalizationMethodType->Algorithm.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, CanonicalizationMethodType->Algorithm.charactersLen, CanonicalizationMethodType->Algorithm.characters, iso20_acdp_Algorithm_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < CanonicalizationMethodType->Algorithm.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(CanonicalizationMethodType->Algorithm.characters[i]))
                                {
                                    CanonicalizationMethodType->Algorithm.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, CanonicalizationMethodType->Algorithm.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    grammar_id = 20;

                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 20:
            // Grammar: ID=20; read/write bits=2; START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 2:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &CanonicalizationMethodType->ANY.bytesLen, &CanonicalizationMethodType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((CanonicalizationMethodType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < CanonicalizationMethodType->ANY.bytesLen;) {
                            uint32_t octet_a = i < CanonicalizationMethodType->ANY.bytesLen ? (unsigned char) CanonicalizationMethodType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < CanonicalizationMethodType->ANY.bytesLen ? (unsigned char) CanonicalizationMethodType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < CanonicalizationMethodType->ANY.bytesLen ? (unsigned char) CanonicalizationMethodType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[CanonicalizationMethodType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        CanonicalizationMethodType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}SignatureMethod; type={http://www.w3.org/2000/09/xmldsig#}SignatureMethodType; base type=; content type=mixed;
//          abstract=False; final=False;
// Particle: Algorithm, anyURI (1, 1); HMACOutputLength, HMACOutputLengthType (0, 1); ANY, anyType (0, 1);
static int decode_iso20_acdp_SignatureMethodType(exi_bitstream_t* stream, struct iso20_acdp_SignatureMethodType* SignatureMethodType, char* xmlOut) {
    int grammar_id = 21;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_SignatureMethodType(SignatureMethodType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 21:
            // Grammar: ID=21; read/write bits=1; START (Algorithm)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Algorithm, anyURI (anyURI)); next=22

                    strcat(xmlOut, " Algorithm");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &SignatureMethodType->Algorithm.charactersLen);
                    if (error == 0)
                    {
                        if (SignatureMethodType->Algorithm.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            SignatureMethodType->Algorithm.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, SignatureMethodType->Algorithm.charactersLen, SignatureMethodType->Algorithm.characters, iso20_acdp_Algorithm_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < SignatureMethodType->Algorithm.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(SignatureMethodType->Algorithm.characters[i]))
                                {
                                    SignatureMethodType->Algorithm.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, SignatureMethodType->Algorithm.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    grammar_id = 22;

                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 22:
            // Grammar: ID=22; read/write bits=3; START (HMACOutputLength), START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (HMACOutputLength, HMACOutputLengthType (integer)); next=23

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}HMACOutputLength");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}HMACOutputLength");
                    // decode: signed
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        error = exi_basetypes_decoder_signed(stream, &SignatureMethodType->HMACOutputLength);
                        if (error == 0)
                        {
                            uint8_t realInteger[21] = {0}; // max length: 20 + 1 zero terminator
                            size_t realInteger_size = 0;
                            int result = exi_basetypes_convert_bytes_from_unsigned(&(SignatureMethodType->HMACOutputLength.data), &realInteger[0], &realInteger_size, 21);
                            if (result == 0)
                            {
                                // reverse array
                                uint8_t temp;
                                uint8_t start = 0;
                                uint8_t end = realInteger_size - 1;
                                while (start < end) {
                                    temp = realInteger[start];
                                    realInteger[start] = realInteger[end];
                                    realInteger[end] = temp;
                                    start++;
                                    end--;
                                }
                                char asHex[128] = "";
                                char* ahPtr = &asHex[0];
                                uint8_t* contentPtr = &realInteger[0];
                                if(realInteger_size * 2 + 1 > 128) {  error = -2; strcat(xmlOut, "DECODE_ERROR"); break; }
                                while(realInteger_size--) {
                                  sprintf(ahPtr, "%02X", *contentPtr);
                                  ahPtr += 2;
                                  ++contentPtr;
                                }
                                *ahPtr = 0;
                                strcat(xmlOut, ">0x");
                                strcat(xmlOut, asHex);
                            }
                            else
                            {
                                strcat(xmlOut, ">ERROR");
                            }
                            SignatureMethodType->HMACOutputLength_isUsed = 1u;
                            grammar_id = 23;
                        }
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}HMACOutputLength>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 2:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 3:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &SignatureMethodType->ANY.bytesLen, &SignatureMethodType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((SignatureMethodType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < SignatureMethodType->ANY.bytesLen;) {
                            uint32_t octet_a = i < SignatureMethodType->ANY.bytesLen ? (unsigned char) SignatureMethodType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < SignatureMethodType->ANY.bytesLen ? (unsigned char) SignatureMethodType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < SignatureMethodType->ANY.bytesLen ? (unsigned char) SignatureMethodType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[SignatureMethodType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        SignatureMethodType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 23:
            // Grammar: ID=23; read/write bits=2; START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 2:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &SignatureMethodType->ANY.bytesLen, &SignatureMethodType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((SignatureMethodType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < SignatureMethodType->ANY.bytesLen;) {
                            uint32_t octet_a = i < SignatureMethodType->ANY.bytesLen ? (unsigned char) SignatureMethodType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < SignatureMethodType->ANY.bytesLen ? (unsigned char) SignatureMethodType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < SignatureMethodType->ANY.bytesLen ? (unsigned char) SignatureMethodType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[SignatureMethodType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        SignatureMethodType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}KeyValue; type={http://www.w3.org/2000/09/xmldsig#}KeyValueType; base type=; content type=mixed;
//          abstract=False; final=False; choice=True;
// Particle: DSAKeyValue, DSAKeyValueType (0, 1); RSAKeyValue, RSAKeyValueType (0, 1); ANY, anyType (0, 1);
static int decode_iso20_acdp_KeyValueType(exi_bitstream_t* stream, struct iso20_acdp_KeyValueType* KeyValueType, char* xmlOut) {
    int grammar_id = 24;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_KeyValueType(KeyValueType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 24:
            // Grammar: ID=24; read/write bits=2; START (DSAKeyValue), START (RSAKeyValue), START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (DSAKeyValue, DSAKeyValueType (DSAKeyValueType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DSAKeyValue");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}DSAKeyValue");
                    // decode: element
                    error = decode_iso20_acdp_DSAKeyValueType(stream, &KeyValueType->DSAKeyValue, xmlOut);
                    if (error == 0)
                    {
                        KeyValueType->DSAKeyValue_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DSAKeyValue>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (RSAKeyValue, RSAKeyValueType (RSAKeyValueType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}RSAKeyValue");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}RSAKeyValue");
                    // decode: element
                    error = decode_iso20_acdp_RSAKeyValueType(stream, &KeyValueType->RSAKeyValue, xmlOut);
                    if (error == 0)
                    {
                        KeyValueType->RSAKeyValue_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}RSAKeyValue>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &KeyValueType->ANY.bytesLen, &KeyValueType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((KeyValueType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < KeyValueType->ANY.bytesLen;) {
                            uint32_t octet_a = i < KeyValueType->ANY.bytesLen ? (unsigned char) KeyValueType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < KeyValueType->ANY.bytesLen ? (unsigned char) KeyValueType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < KeyValueType->ANY.bytesLen ? (unsigned char) KeyValueType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[KeyValueType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        KeyValueType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}Reference; type={http://www.w3.org/2000/09/xmldsig#}ReferenceType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: Id, ID (0, 1); Type, anyURI (0, 1); URI, anyURI (0, 1); Transforms, TransformsType (0, 1); DigestMethod, DigestMethodType (1, 1); DigestValue, DigestValueType (1, 1);
static int decode_iso20_acdp_ReferenceType(exi_bitstream_t* stream, struct iso20_acdp_ReferenceType* ReferenceType, char* xmlOut) {
    int grammar_id = 25;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_ReferenceType(ReferenceType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 25:
            // Grammar: ID=25; read/write bits=3; START (Id), START (Type), START (URI), START (Transforms), START (DigestMethod)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Id, ID (NCName)); next=26

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ReferenceType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (ReferenceType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ReferenceType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ReferenceType->Id.charactersLen, ReferenceType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ReferenceType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ReferenceType->Id.characters[i]))
                                {
                                    ReferenceType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ReferenceType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ReferenceType->Id_isUsed = 1u;
                    grammar_id = 26;

                    }
                    break;
                case 1:
                    {
                    // Event: START (Type, anyURI (anyURI)); next=27

                    strcat(xmlOut, " Type");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ReferenceType->Type.charactersLen);
                    if (error == 0)
                    {
                        if (ReferenceType->Type.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ReferenceType->Type.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ReferenceType->Type.charactersLen, ReferenceType->Type.characters, iso20_acdp_Type_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ReferenceType->Type.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ReferenceType->Type.characters[i]))
                                {
                                    ReferenceType->Type.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ReferenceType->Type.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ReferenceType->Type_isUsed = 1u;
                    grammar_id = 27;

                    }
                    break;
                case 2:
                    {
                    // Event: START (URI, anyURI (anyURI)); next=28

                    strcat(xmlOut, " URI");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ReferenceType->URI.charactersLen);
                    if (error == 0)
                    {
                        if (ReferenceType->URI.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ReferenceType->URI.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ReferenceType->URI.charactersLen, ReferenceType->URI.characters, iso20_acdp_URI_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ReferenceType->URI.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ReferenceType->URI.characters[i]))
                                {
                                    ReferenceType->URI.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ReferenceType->URI.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ReferenceType->URI_isUsed = 1u;
                    grammar_id = 28;

                    }
                    break;
                case 3:
                    {
                    // Event: START (Transforms, TransformsType (TransformsType)); next=29

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    // decode: element
                    error = decode_iso20_acdp_TransformsType(stream, &ReferenceType->Transforms, xmlOut);
                    if (error == 0)
                    {
                        ReferenceType->Transforms_isUsed = 1u;
                        grammar_id = 29;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transforms>");
                    }
                    break;
                case 4:
                    {
                    // Event: START (DigestMethod, DigestMethodType (DigestMethodType)); next=30

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    // decode: element
                    error = decode_iso20_acdp_DigestMethodType(stream, &ReferenceType->DigestMethod, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 30;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DigestMethod>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 26:
            // Grammar: ID=26; read/write bits=3; START (Type), START (URI), START (Transforms), START (DigestMethod)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Type, anyURI (anyURI)); next=27

                    strcat(xmlOut, " Type");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ReferenceType->Type.charactersLen);
                    if (error == 0)
                    {
                        if (ReferenceType->Type.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ReferenceType->Type.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ReferenceType->Type.charactersLen, ReferenceType->Type.characters, iso20_acdp_Type_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ReferenceType->Type.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ReferenceType->Type.characters[i]))
                                {
                                    ReferenceType->Type.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ReferenceType->Type.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ReferenceType->Type_isUsed = 1u;
                    grammar_id = 27;

                    }
                    break;
                case 1:
                    {
                    // Event: START (URI, anyURI (anyURI)); next=28

                    strcat(xmlOut, " URI");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ReferenceType->URI.charactersLen);
                    if (error == 0)
                    {
                        if (ReferenceType->URI.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ReferenceType->URI.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ReferenceType->URI.charactersLen, ReferenceType->URI.characters, iso20_acdp_URI_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ReferenceType->URI.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ReferenceType->URI.characters[i]))
                                {
                                    ReferenceType->URI.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ReferenceType->URI.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ReferenceType->URI_isUsed = 1u;
                    grammar_id = 28;

                    }
                    break;
                case 2:
                    {
                    // Event: START (Transforms, TransformsType (TransformsType)); next=29

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    // decode: element
                    error = decode_iso20_acdp_TransformsType(stream, &ReferenceType->Transforms, xmlOut);
                    if (error == 0)
                    {
                        ReferenceType->Transforms_isUsed = 1u;
                        grammar_id = 29;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transforms>");
                    }
                    break;
                case 3:
                    {
                    // Event: START (DigestMethod, DigestMethodType (DigestMethodType)); next=30

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    // decode: element
                    error = decode_iso20_acdp_DigestMethodType(stream, &ReferenceType->DigestMethod, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 30;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DigestMethod>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 27:
            // Grammar: ID=27; read/write bits=2; START (URI), START (Transforms), START (DigestMethod)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (URI, anyURI (anyURI)); next=28

                    strcat(xmlOut, " URI");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ReferenceType->URI.charactersLen);
                    if (error == 0)
                    {
                        if (ReferenceType->URI.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ReferenceType->URI.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ReferenceType->URI.charactersLen, ReferenceType->URI.characters, iso20_acdp_URI_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ReferenceType->URI.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ReferenceType->URI.characters[i]))
                                {
                                    ReferenceType->URI.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ReferenceType->URI.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ReferenceType->URI_isUsed = 1u;
                    grammar_id = 28;

                    }
                    break;
                case 1:
                    {
                    // Event: START (Transforms, TransformsType (TransformsType)); next=29

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    // decode: element
                    error = decode_iso20_acdp_TransformsType(stream, &ReferenceType->Transforms, xmlOut);
                    if (error == 0)
                    {
                        ReferenceType->Transforms_isUsed = 1u;
                        grammar_id = 29;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transforms>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (DigestMethod, DigestMethodType (DigestMethodType)); next=30

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    // decode: element
                    error = decode_iso20_acdp_DigestMethodType(stream, &ReferenceType->DigestMethod, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 30;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DigestMethod>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 28:
            // Grammar: ID=28; read/write bits=2; START (Transforms), START (DigestMethod)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Transforms, TransformsType (TransformsType)); next=29

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    // decode: element
                    error = decode_iso20_acdp_TransformsType(stream, &ReferenceType->Transforms, xmlOut);
                    if (error == 0)
                    {
                        ReferenceType->Transforms_isUsed = 1u;
                        grammar_id = 29;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transforms>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (DigestMethod, DigestMethodType (DigestMethodType)); next=30

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    // decode: element
                    error = decode_iso20_acdp_DigestMethodType(stream, &ReferenceType->DigestMethod, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 30;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DigestMethod>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 29:
            // Grammar: ID=29; read/write bits=1; START (DigestMethod)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (DigestMethod, DigestMethodType (DigestMethodType)); next=30

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}DigestMethod");
                    // decode: element
                    error = decode_iso20_acdp_DigestMethodType(stream, &ReferenceType->DigestMethod, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 30;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DigestMethod>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 30:
            // Grammar: ID=30; read/write bits=1; START (DigestValue)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (DigestValue, DigestValueType (base64Binary)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DigestValue");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}DigestValue");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &ReferenceType->DigestValue.bytesLen, &ReferenceType->DigestValue.bytes[0], iso20_acdp_DigestValueType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((ReferenceType->DigestValue.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < ReferenceType->DigestValue.bytesLen;) {
                            uint32_t octet_a = i < ReferenceType->DigestValue.bytesLen ? (unsigned char) ReferenceType->DigestValue.bytes[i++] : 0;
                            uint32_t octet_b = i < ReferenceType->DigestValue.bytesLen ? (unsigned char) ReferenceType->DigestValue.bytes[i++] : 0;
                            uint32_t octet_c = i < ReferenceType->DigestValue.bytesLen ? (unsigned char) ReferenceType->DigestValue.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[ReferenceType->DigestValue.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        grammar_id = 2;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DigestValue>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}RetrievalMethod; type={http://www.w3.org/2000/09/xmldsig#}RetrievalMethodType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: Type, anyURI (0, 1); URI, anyURI (0, 1); Transforms, TransformsType (0, 1);
static int decode_iso20_acdp_RetrievalMethodType(exi_bitstream_t* stream, struct iso20_acdp_RetrievalMethodType* RetrievalMethodType, char* xmlOut) {
    int grammar_id = 31;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_RetrievalMethodType(RetrievalMethodType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 31:
            // Grammar: ID=31; read/write bits=3; START (Type), START (URI), START (Transforms), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Type, anyURI (anyURI)); next=32

                    strcat(xmlOut, " Type");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &RetrievalMethodType->Type.charactersLen);
                    if (error == 0)
                    {
                        if (RetrievalMethodType->Type.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            RetrievalMethodType->Type.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, RetrievalMethodType->Type.charactersLen, RetrievalMethodType->Type.characters, iso20_acdp_Type_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < RetrievalMethodType->Type.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(RetrievalMethodType->Type.characters[i]))
                                {
                                    RetrievalMethodType->Type.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, RetrievalMethodType->Type.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    RetrievalMethodType->Type_isUsed = 1u;
                    grammar_id = 32;

                    }
                    break;
                case 1:
                    {
                    // Event: START (URI, anyURI (anyURI)); next=33

                    strcat(xmlOut, " URI");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &RetrievalMethodType->URI.charactersLen);
                    if (error == 0)
                    {
                        if (RetrievalMethodType->URI.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            RetrievalMethodType->URI.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, RetrievalMethodType->URI.charactersLen, RetrievalMethodType->URI.characters, iso20_acdp_URI_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < RetrievalMethodType->URI.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(RetrievalMethodType->URI.characters[i]))
                                {
                                    RetrievalMethodType->URI.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, RetrievalMethodType->URI.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    RetrievalMethodType->URI_isUsed = 1u;
                    grammar_id = 33;

                    }
                    break;
                case 2:
                    {
                    // Event: START (Transforms, TransformsType (TransformsType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    // decode: element
                    error = decode_iso20_acdp_TransformsType(stream, &RetrievalMethodType->Transforms, xmlOut);
                    if (error == 0)
                    {
                        RetrievalMethodType->Transforms_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transforms>");
                    }
                    break;
                case 3:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 32:
            // Grammar: ID=32; read/write bits=2; START (URI), START (Transforms), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (URI, anyURI (anyURI)); next=33

                    strcat(xmlOut, " URI");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &RetrievalMethodType->URI.charactersLen);
                    if (error == 0)
                    {
                        if (RetrievalMethodType->URI.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            RetrievalMethodType->URI.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, RetrievalMethodType->URI.charactersLen, RetrievalMethodType->URI.characters, iso20_acdp_URI_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < RetrievalMethodType->URI.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(RetrievalMethodType->URI.characters[i]))
                                {
                                    RetrievalMethodType->URI.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, RetrievalMethodType->URI.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    RetrievalMethodType->URI_isUsed = 1u;
                    grammar_id = 33;

                    }
                    break;
                case 1:
                    {
                    // Event: START (Transforms, TransformsType (TransformsType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    // decode: element
                    error = decode_iso20_acdp_TransformsType(stream, &RetrievalMethodType->Transforms, xmlOut);
                    if (error == 0)
                    {
                        RetrievalMethodType->Transforms_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transforms>");
                    }
                    break;
                case 2:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 33:
            // Grammar: ID=33; read/write bits=2; START (Transforms), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Transforms, TransformsType (TransformsType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Transforms");
                    // decode: element
                    error = decode_iso20_acdp_TransformsType(stream, &RetrievalMethodType->Transforms, xmlOut);
                    if (error == 0)
                    {
                        RetrievalMethodType->Transforms_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transforms>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}X509Data; type={http://www.w3.org/2000/09/xmldsig#}X509DataType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: X509IssuerSerial, X509IssuerSerialType (0, 1); X509SKI, base64Binary (0, 1); X509SubjectName, string (0, 1); X509Certificate, base64Binary (0, 1); X509CRL, base64Binary (0, 1); ANY, anyType (0, 1);
static int decode_iso20_acdp_X509DataType(exi_bitstream_t* stream, struct iso20_acdp_X509DataType* X509DataType, char* xmlOut) {
    int grammar_id = 34;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_X509DataType(X509DataType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 34:
            // Grammar: ID=34; read/write bits=3; START (X509IssuerSerial), START (X509SKI), START (X509SubjectName), START (X509Certificate), START (X509CRL), START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (X509IssuerSerial, X509IssuerSerialType (X509IssuerSerialType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509IssuerSerial");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}X509IssuerSerial");
                    // decode: element
                    error = decode_iso20_acdp_X509IssuerSerialType(stream, &X509DataType->X509IssuerSerial, xmlOut);
                    if (error == 0)
                    {
                        X509DataType->X509IssuerSerial_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509IssuerSerial>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (X509SKI, base64Binary (base64Binary)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509SKI");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}X509SKI");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &X509DataType->X509SKI.bytesLen, &X509DataType->X509SKI.bytes[0], iso20_acdp_base64Binary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((X509DataType->X509SKI.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < X509DataType->X509SKI.bytesLen;) {
                            uint32_t octet_a = i < X509DataType->X509SKI.bytesLen ? (unsigned char) X509DataType->X509SKI.bytes[i++] : 0;
                            uint32_t octet_b = i < X509DataType->X509SKI.bytesLen ? (unsigned char) X509DataType->X509SKI.bytes[i++] : 0;
                            uint32_t octet_c = i < X509DataType->X509SKI.bytesLen ? (unsigned char) X509DataType->X509SKI.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[X509DataType->X509SKI.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        X509DataType->X509SKI_isUsed = 1u;
                        grammar_id = 2;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509SKI>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (X509SubjectName, string (string)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509SubjectName");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}X509SubjectName");
                    // decode: string (len, characters)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            error = exi_basetypes_decoder_uint_16(stream, &X509DataType->X509SubjectName.charactersLen);
                            if (error == 0)
                            {
                                if (X509DataType->X509SubjectName.charactersLen >= 2)
                                {
                                    // string tables and table partitions are not supported, so the length has to be decremented by 2
                                    X509DataType->X509SubjectName.charactersLen -= 2;
                                    error = exi_basetypes_decoder_characters(stream, X509DataType->X509SubjectName.charactersLen, X509DataType->X509SubjectName.characters, iso20_acdp_X509SubjectName_CHARACTER_SIZE);
                                    strcat(xmlOut, ">");
                                    for(int i = 0; i < X509DataType->X509SubjectName.charactersLen; i++) { // check for unprintable characters
                                        if(!isprint(X509DataType->X509SubjectName.characters[i]))
                                        {
                                            X509DataType->X509SubjectName.characters[i]   = '?';
                                        }
                                    }
                                    strcat(xmlOut, X509DataType->X509SubjectName.characters);
                                }
                                else
                                {
                                    // the string seems to be in the table, but this is not supported
                                    error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                                }
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_characters is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                X509DataType->X509SubjectName_isUsed = 1u;
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509SubjectName>");
                    }
                    break;
                case 3:
                    {
                    // Event: START (X509Certificate, base64Binary (base64Binary)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509Certificate");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}X509Certificate");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &X509DataType->X509Certificate.bytesLen, &X509DataType->X509Certificate.bytes[0], iso20_acdp_base64Binary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((X509DataType->X509Certificate.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < X509DataType->X509Certificate.bytesLen;) {
                            uint32_t octet_a = i < X509DataType->X509Certificate.bytesLen ? (unsigned char) X509DataType->X509Certificate.bytes[i++] : 0;
                            uint32_t octet_b = i < X509DataType->X509Certificate.bytesLen ? (unsigned char) X509DataType->X509Certificate.bytes[i++] : 0;
                            uint32_t octet_c = i < X509DataType->X509Certificate.bytesLen ? (unsigned char) X509DataType->X509Certificate.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[X509DataType->X509Certificate.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        X509DataType->X509Certificate_isUsed = 1u;
                        grammar_id = 2;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509Certificate>");
                    }
                    break;
                case 4:
                    {
                    // Event: START (X509CRL, base64Binary (base64Binary)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509CRL");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}X509CRL");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &X509DataType->X509CRL.bytesLen, &X509DataType->X509CRL.bytes[0], iso20_acdp_base64Binary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((X509DataType->X509CRL.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < X509DataType->X509CRL.bytesLen;) {
                            uint32_t octet_a = i < X509DataType->X509CRL.bytesLen ? (unsigned char) X509DataType->X509CRL.bytes[i++] : 0;
                            uint32_t octet_b = i < X509DataType->X509CRL.bytesLen ? (unsigned char) X509DataType->X509CRL.bytes[i++] : 0;
                            uint32_t octet_c = i < X509DataType->X509CRL.bytesLen ? (unsigned char) X509DataType->X509CRL.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[X509DataType->X509CRL.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        X509DataType->X509CRL_isUsed = 1u;
                        grammar_id = 2;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509CRL>");
                    }
                    break;
                case 5:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &X509DataType->ANY.bytesLen, &X509DataType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((X509DataType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < X509DataType->ANY.bytesLen;) {
                            uint32_t octet_a = i < X509DataType->ANY.bytesLen ? (unsigned char) X509DataType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < X509DataType->ANY.bytesLen ? (unsigned char) X509DataType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < X509DataType->ANY.bytesLen ? (unsigned char) X509DataType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[X509DataType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        X509DataType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}PGPData; type={http://www.w3.org/2000/09/xmldsig#}PGPDataType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False; choice=True; sequence=True (2;
// Particle: PGPKeyID, base64Binary (1, 1); PGPKeyPacket, base64Binary (0, 1); ANY, anyType (0, 1); PGPKeyPacket, base64Binary (1, 1); ANY, anyType (0, 1);
static int decode_iso20_acdp_PGPDataType(exi_bitstream_t* stream, struct iso20_acdp_PGPDataType* PGPDataType, char* xmlOut) {
    int grammar_id = 35;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_PGPDataType(PGPDataType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 35:
            // Grammar: ID=35; read/write bits=2; START (PGPKeyID), START (PGPKeyPacket)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (PGPKeyID, base64Binary (base64Binary)); next=36

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}PGPKeyID");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}PGPKeyID");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &PGPDataType->choice_1.PGPKeyID.bytesLen, &PGPDataType->choice_1.PGPKeyID.bytes[0], iso20_acdp_base64Binary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((PGPDataType->choice_1.PGPKeyID.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < PGPDataType->choice_1.PGPKeyID.bytesLen;) {
                            uint32_t octet_a = i < PGPDataType->choice_1.PGPKeyID.bytesLen ? (unsigned char) PGPDataType->choice_1.PGPKeyID.bytes[i++] : 0;
                            uint32_t octet_b = i < PGPDataType->choice_1.PGPKeyID.bytesLen ? (unsigned char) PGPDataType->choice_1.PGPKeyID.bytes[i++] : 0;
                            uint32_t octet_c = i < PGPDataType->choice_1.PGPKeyID.bytesLen ? (unsigned char) PGPDataType->choice_1.PGPKeyID.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[PGPDataType->choice_1.PGPKeyID.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        grammar_id = 36;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}PGPKeyID>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (PGPKeyPacket, base64Binary (base64Binary)); next=37

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}PGPKeyPacket");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}PGPKeyPacket");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &PGPDataType->choice_1.PGPKeyPacket.bytesLen, &PGPDataType->choice_1.PGPKeyPacket.bytes[0], iso20_acdp_base64Binary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((PGPDataType->choice_1.PGPKeyPacket.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < PGPDataType->choice_1.PGPKeyPacket.bytesLen;) {
                            uint32_t octet_a = i < PGPDataType->choice_1.PGPKeyPacket.bytesLen ? (unsigned char) PGPDataType->choice_1.PGPKeyPacket.bytes[i++] : 0;
                            uint32_t octet_b = i < PGPDataType->choice_1.PGPKeyPacket.bytesLen ? (unsigned char) PGPDataType->choice_1.PGPKeyPacket.bytes[i++] : 0;
                            uint32_t octet_c = i < PGPDataType->choice_1.PGPKeyPacket.bytesLen ? (unsigned char) PGPDataType->choice_1.PGPKeyPacket.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[PGPDataType->choice_1.PGPKeyPacket.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        PGPDataType->choice_1.PGPKeyPacket_isUsed = 1u;
                        grammar_id = 37;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}PGPKeyPacket>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 36:
            // Grammar: ID=36; read/write bits=3; START (PGPKeyPacket), START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (PGPKeyPacket, base64Binary (base64Binary)); next=37

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}PGPKeyPacket");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}PGPKeyPacket");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &PGPDataType->choice_1.PGPKeyPacket.bytesLen, &PGPDataType->choice_1.PGPKeyPacket.bytes[0], iso20_acdp_base64Binary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((PGPDataType->choice_1.PGPKeyPacket.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < PGPDataType->choice_1.PGPKeyPacket.bytesLen;) {
                            uint32_t octet_a = i < PGPDataType->choice_1.PGPKeyPacket.bytesLen ? (unsigned char) PGPDataType->choice_1.PGPKeyPacket.bytes[i++] : 0;
                            uint32_t octet_b = i < PGPDataType->choice_1.PGPKeyPacket.bytesLen ? (unsigned char) PGPDataType->choice_1.PGPKeyPacket.bytes[i++] : 0;
                            uint32_t octet_c = i < PGPDataType->choice_1.PGPKeyPacket.bytesLen ? (unsigned char) PGPDataType->choice_1.PGPKeyPacket.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[PGPDataType->choice_1.PGPKeyPacket.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        PGPDataType->choice_1.PGPKeyPacket_isUsed = 1u;
                        grammar_id = 37;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}PGPKeyPacket>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=38
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 2:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 3:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=38
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &PGPDataType->choice_1.ANY.bytesLen, &PGPDataType->choice_1.ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((PGPDataType->choice_1.ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < PGPDataType->choice_1.ANY.bytesLen;) {
                            uint32_t octet_a = i < PGPDataType->choice_1.ANY.bytesLen ? (unsigned char) PGPDataType->choice_1.ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < PGPDataType->choice_1.ANY.bytesLen ? (unsigned char) PGPDataType->choice_1.ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < PGPDataType->choice_1.ANY.bytesLen ? (unsigned char) PGPDataType->choice_1.ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[PGPDataType->choice_1.ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        PGPDataType->choice_1.ANY_isUsed = 1u;
                        grammar_id = 38;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 37:
            // Grammar: ID=37; read/write bits=3; START (ANY), END Element, END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=38
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 2:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 3:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=38
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &PGPDataType->choice_1.ANY.bytesLen, &PGPDataType->choice_1.ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((PGPDataType->choice_1.ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < PGPDataType->choice_1.ANY.bytesLen;) {
                            uint32_t octet_a = i < PGPDataType->choice_1.ANY.bytesLen ? (unsigned char) PGPDataType->choice_1.ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < PGPDataType->choice_1.ANY.bytesLen ? (unsigned char) PGPDataType->choice_1.ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < PGPDataType->choice_1.ANY.bytesLen ? (unsigned char) PGPDataType->choice_1.ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[PGPDataType->choice_1.ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        PGPDataType->choice_1.ANY_isUsed = 1u;
                        grammar_id = 38;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 38:
            // Grammar: ID=38; read/write bits=1; START (PGPKeyPacket)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (PGPKeyPacket, base64Binary (base64Binary)); next=39

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}PGPKeyPacket");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}PGPKeyPacket");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &PGPDataType->choice_2.PGPKeyPacket.bytesLen, &PGPDataType->choice_2.PGPKeyPacket.bytes[0], iso20_acdp_base64Binary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((PGPDataType->choice_2.PGPKeyPacket.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < PGPDataType->choice_2.PGPKeyPacket.bytesLen;) {
                            uint32_t octet_a = i < PGPDataType->choice_2.PGPKeyPacket.bytesLen ? (unsigned char) PGPDataType->choice_2.PGPKeyPacket.bytes[i++] : 0;
                            uint32_t octet_b = i < PGPDataType->choice_2.PGPKeyPacket.bytesLen ? (unsigned char) PGPDataType->choice_2.PGPKeyPacket.bytes[i++] : 0;
                            uint32_t octet_c = i < PGPDataType->choice_2.PGPKeyPacket.bytesLen ? (unsigned char) PGPDataType->choice_2.PGPKeyPacket.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[PGPDataType->choice_2.PGPKeyPacket.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        grammar_id = 39;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}PGPKeyPacket>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 39:
            // Grammar: ID=39; read/write bits=2; START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=38
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 2:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=38
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &PGPDataType->choice_2.ANY.bytesLen, &PGPDataType->choice_2.ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((PGPDataType->choice_2.ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < PGPDataType->choice_2.ANY.bytesLen;) {
                            uint32_t octet_a = i < PGPDataType->choice_2.ANY.bytesLen ? (unsigned char) PGPDataType->choice_2.ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < PGPDataType->choice_2.ANY.bytesLen ? (unsigned char) PGPDataType->choice_2.ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < PGPDataType->choice_2.ANY.bytesLen ? (unsigned char) PGPDataType->choice_2.ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[PGPDataType->choice_2.ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        PGPDataType->choice_2.ANY_isUsed = 1u;
                        grammar_id = 38;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}SPKIData; type={http://www.w3.org/2000/09/xmldsig#}SPKIDataType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: SPKISexp, base64Binary (1, 1); ANY, anyType (0, 1);
static int decode_iso20_acdp_SPKIDataType(exi_bitstream_t* stream, struct iso20_acdp_SPKIDataType* SPKIDataType, char* xmlOut) {
    int grammar_id = 40;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_SPKIDataType(SPKIDataType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 40:
            // Grammar: ID=40; read/write bits=1; START (SPKISexp)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SPKISexp, base64Binary (base64Binary)); next=41

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SPKISexp");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SPKISexp");
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &SPKIDataType->SPKISexp.bytesLen, &SPKIDataType->SPKISexp.bytes[0], iso20_acdp_base64Binary_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((SPKIDataType->SPKISexp.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < SPKIDataType->SPKISexp.bytesLen;) {
                            uint32_t octet_a = i < SPKIDataType->SPKISexp.bytesLen ? (unsigned char) SPKIDataType->SPKISexp.bytes[i++] : 0;
                            uint32_t octet_b = i < SPKIDataType->SPKISexp.bytesLen ? (unsigned char) SPKIDataType->SPKISexp.bytes[i++] : 0;
                            uint32_t octet_c = i < SPKIDataType->SPKISexp.bytesLen ? (unsigned char) SPKIDataType->SPKISexp.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[SPKIDataType->SPKISexp.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        grammar_id = 41;
                    }




                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SPKISexp>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 41:
            // Grammar: ID=41; read/write bits=2; START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 2:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &SPKIDataType->ANY.bytesLen, &SPKIDataType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((SPKIDataType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < SPKIDataType->ANY.bytesLen;) {
                            uint32_t octet_a = i < SPKIDataType->ANY.bytesLen ? (unsigned char) SPKIDataType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < SPKIDataType->ANY.bytesLen ? (unsigned char) SPKIDataType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < SPKIDataType->ANY.bytesLen ? (unsigned char) SPKIDataType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[SPKIDataType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        SPKIDataType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}SignedInfo; type={http://www.w3.org/2000/09/xmldsig#}SignedInfoType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: Id, ID (0, 1); CanonicalizationMethod, CanonicalizationMethodType (1, 1); SignatureMethod, SignatureMethodType (1, 1); Reference, ReferenceType (1, 4);
static int decode_iso20_acdp_SignedInfoType(exi_bitstream_t* stream, struct iso20_acdp_SignedInfoType* SignedInfoType, char* xmlOut) {
    int grammar_id = 42;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_SignedInfoType(SignedInfoType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 42:
            // Grammar: ID=42; read/write bits=2; START (Id), START (CanonicalizationMethod)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Id, ID (NCName)); next=43

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &SignedInfoType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (SignedInfoType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            SignedInfoType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, SignedInfoType->Id.charactersLen, SignedInfoType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < SignedInfoType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(SignedInfoType->Id.characters[i]))
                                {
                                    SignedInfoType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, SignedInfoType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    SignedInfoType->Id_isUsed = 1u;
                    grammar_id = 43;

                    }
                    break;
                case 1:
                    {
                    // Event: START (CanonicalizationMethod, CanonicalizationMethodType (CanonicalizationMethodType)); next=44

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethod");
                    // decode: element
                    error = decode_iso20_acdp_CanonicalizationMethodType(stream, &SignedInfoType->CanonicalizationMethod, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 44;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethod>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 43:
            // Grammar: ID=43; read/write bits=1; START (CanonicalizationMethod)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (CanonicalizationMethod, CanonicalizationMethodType (CanonicalizationMethodType)); next=44

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethod");
                    // decode: element
                    error = decode_iso20_acdp_CanonicalizationMethodType(stream, &SignedInfoType->CanonicalizationMethod, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 44;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethod>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 44:
            // Grammar: ID=44; read/write bits=1; START (SignatureMethod)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SignatureMethod, SignatureMethodType (SignatureMethodType)); next=45

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SignatureMethod");
                    // decode: element
                    error = decode_iso20_acdp_SignatureMethodType(stream, &SignedInfoType->SignatureMethod, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 45;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureMethod>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 45:
            // Grammar: ID=45; read/write bits=1; START (Reference)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=46

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (SignedInfoType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &SignedInfoType->Reference.array[SignedInfoType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 46;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 46:
            // Grammar: ID=46; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=47

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (SignedInfoType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &SignedInfoType->Reference.array[SignedInfoType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 47;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 47:
            // Grammar: ID=47; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=48

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (SignedInfoType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &SignedInfoType->Reference.array[SignedInfoType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 48;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 48:
            // Grammar: ID=48; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=49

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (SignedInfoType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &SignedInfoType->Reference.array[SignedInfoType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 49;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 49:
            // Grammar: ID=49; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (SignedInfoType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &SignedInfoType->Reference.array[SignedInfoType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 2;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}SignatureValue; type={http://www.w3.org/2000/09/xmldsig#}SignatureValueType; base type=base64Binary; content type=simple;
//          abstract=False; final=False; derivation=extension;
// Particle: Id, ID (0, 1); CONTENT, SignatureValueType (1, 1);
static int decode_iso20_acdp_SignatureValueType(exi_bitstream_t* stream, struct iso20_acdp_SignatureValueType* SignatureValueType, char* xmlOut) {
    int grammar_id = 50;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_SignatureValueType(SignatureValueType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 50:
            // Grammar: ID=50; read/write bits=2; START (Id), START (CONTENT)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Id, ID (NCName)); next=51

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &SignatureValueType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (SignatureValueType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            SignatureValueType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, SignatureValueType->Id.charactersLen, SignatureValueType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < SignatureValueType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(SignatureValueType->Id.characters[i]))
                                {
                                    SignatureValueType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, SignatureValueType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    SignatureValueType->Id_isUsed = 1u;
                    grammar_id = 51;

                    }
                    break;
                case 1:
                    {
                    // Event: START (CONTENT, SignatureValueType (base64Binary)); next=2
                    // decode exi type: base64Binary (simple)
                    error = exi_basetypes_decoder_uint_16(stream, &SignatureValueType->CONTENT.bytesLen);
                    if (error == 0)
                    {
                        error = exi_basetypes_decoder_bytes(stream, SignatureValueType->CONTENT.bytesLen, &SignatureValueType->CONTENT.bytes[0], iso20_acdp_SignatureValueType_BYTES_SIZE);
                        if (error == 0)
                        {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((SignatureValueType->CONTENT.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < SignatureValueType->CONTENT.bytesLen;) {
                            uint32_t octet_a = i < SignatureValueType->CONTENT.bytesLen ? (unsigned char) SignatureValueType->CONTENT.bytes[i++] : 0;
                            uint32_t octet_b = i < SignatureValueType->CONTENT.bytesLen ? (unsigned char) SignatureValueType->CONTENT.bytes[i++] : 0;
                            uint32_t octet_c = i < SignatureValueType->CONTENT.bytesLen ? (unsigned char) SignatureValueType->CONTENT.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[SignatureValueType->CONTENT.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                            grammar_id = 2;
                        }
                    }
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 51:
            // Grammar: ID=51; read/write bits=1; START (CONTENT)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (CONTENT, SignatureValueType (base64Binary)); next=2
                    // decode exi type: base64Binary (simple)
                    error = exi_basetypes_decoder_uint_16(stream, &SignatureValueType->CONTENT.bytesLen);
                    if (error == 0)
                    {
                        error = exi_basetypes_decoder_bytes(stream, SignatureValueType->CONTENT.bytesLen, &SignatureValueType->CONTENT.bytes[0], iso20_acdp_SignatureValueType_BYTES_SIZE);
                        if (error == 0)
                        {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((SignatureValueType->CONTENT.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < SignatureValueType->CONTENT.bytesLen;) {
                            uint32_t octet_a = i < SignatureValueType->CONTENT.bytesLen ? (unsigned char) SignatureValueType->CONTENT.bytes[i++] : 0;
                            uint32_t octet_b = i < SignatureValueType->CONTENT.bytesLen ? (unsigned char) SignatureValueType->CONTENT.bytes[i++] : 0;
                            uint32_t octet_c = i < SignatureValueType->CONTENT.bytesLen ? (unsigned char) SignatureValueType->CONTENT.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[SignatureValueType->CONTENT.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                            grammar_id = 2;
                        }
                    }
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}KeyInfo; type={http://www.w3.org/2000/09/xmldsig#}KeyInfoType; base type=; content type=mixed;
//          abstract=False; final=False; choice=True;
// Particle: Id, ID (0, 1); KeyName, string (0, 1); KeyValue, KeyValueType (0, 1); RetrievalMethod, RetrievalMethodType (0, 1); X509Data, X509DataType (0, 1); PGPData, PGPDataType (0, 1); SPKIData, SPKIDataType (0, 1); MgmtData, string (0, 1); ANY, anyType (0, 1);
static int decode_iso20_acdp_KeyInfoType(exi_bitstream_t* stream, struct iso20_acdp_KeyInfoType* KeyInfoType, char* xmlOut) {
    int grammar_id = 52;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_KeyInfoType(KeyInfoType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 52:
            // Grammar: ID=52; read/write bits=4; START (Id), START (KeyName), START (KeyValue), START (RetrievalMethod), START (X509Data), START (PGPData), START (SPKIData), START (MgmtData), START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 4, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Id, ID (NCName)); next=53

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &KeyInfoType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (KeyInfoType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            KeyInfoType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, KeyInfoType->Id.charactersLen, KeyInfoType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < KeyInfoType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(KeyInfoType->Id.characters[i]))
                                {
                                    KeyInfoType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, KeyInfoType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    KeyInfoType->Id_isUsed = 1u;
                    grammar_id = 53;

                    }
                    break;
                case 1:
                    {
                    // Event: START (KeyName, string (string)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}KeyName");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}KeyName");
                    // decode: string (len, characters)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            error = exi_basetypes_decoder_uint_16(stream, &KeyInfoType->KeyName.charactersLen);
                            if (error == 0)
                            {
                                if (KeyInfoType->KeyName.charactersLen >= 2)
                                {
                                    // string tables and table partitions are not supported, so the length has to be decremented by 2
                                    KeyInfoType->KeyName.charactersLen -= 2;
                                    error = exi_basetypes_decoder_characters(stream, KeyInfoType->KeyName.charactersLen, KeyInfoType->KeyName.characters, iso20_acdp_KeyName_CHARACTER_SIZE);
                                    strcat(xmlOut, ">");
                                    for(int i = 0; i < KeyInfoType->KeyName.charactersLen; i++) { // check for unprintable characters
                                        if(!isprint(KeyInfoType->KeyName.characters[i]))
                                        {
                                            KeyInfoType->KeyName.characters[i]   = '?';
                                        }
                                    }
                                    strcat(xmlOut, KeyInfoType->KeyName.characters);
                                }
                                else
                                {
                                    // the string seems to be in the table, but this is not supported
                                    error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                                }
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_characters is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                KeyInfoType->KeyName_isUsed = 1u;
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}KeyName>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (KeyValue, KeyValueType (KeyValueType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}KeyValue");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}KeyValue");
                    // decode: element
                    error = decode_iso20_acdp_KeyValueType(stream, &KeyInfoType->KeyValue, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->KeyValue_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}KeyValue>");
                    }
                    break;
                case 3:
                    {
                    // Event: START (RetrievalMethod, RetrievalMethodType (RetrievalMethodType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}RetrievalMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}RetrievalMethod");
                    // decode: element
                    error = decode_iso20_acdp_RetrievalMethodType(stream, &KeyInfoType->RetrievalMethod, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->RetrievalMethod_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}RetrievalMethod>");
                    }
                    break;
                case 4:
                    {
                    // Event: START (X509Data, X509DataType (X509DataType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509Data");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}X509Data");
                    // decode: element
                    error = decode_iso20_acdp_X509DataType(stream, &KeyInfoType->X509Data, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->X509Data_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509Data>");
                    }
                    break;
                case 5:
                    {
                    // Event: START (PGPData, PGPDataType (PGPDataType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}PGPData");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}PGPData");
                    // decode: element
                    error = decode_iso20_acdp_PGPDataType(stream, &KeyInfoType->PGPData, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->PGPData_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}PGPData>");
                    }
                    break;
                case 6:
                    {
                    // Event: START (SPKIData, SPKIDataType (SPKIDataType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SPKIData");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SPKIData");
                    // decode: element
                    error = decode_iso20_acdp_SPKIDataType(stream, &KeyInfoType->SPKIData, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->SPKIData_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SPKIData>");
                    }
                    break;
                case 7:
                    {
                    // Event: START (MgmtData, string (string)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}MgmtData");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}MgmtData");
                    // decode: string (len, characters)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            error = exi_basetypes_decoder_uint_16(stream, &KeyInfoType->MgmtData.charactersLen);
                            if (error == 0)
                            {
                                if (KeyInfoType->MgmtData.charactersLen >= 2)
                                {
                                    // string tables and table partitions are not supported, so the length has to be decremented by 2
                                    KeyInfoType->MgmtData.charactersLen -= 2;
                                    error = exi_basetypes_decoder_characters(stream, KeyInfoType->MgmtData.charactersLen, KeyInfoType->MgmtData.characters, iso20_acdp_MgmtData_CHARACTER_SIZE);
                                    strcat(xmlOut, ">");
                                    for(int i = 0; i < KeyInfoType->MgmtData.charactersLen; i++) { // check for unprintable characters
                                        if(!isprint(KeyInfoType->MgmtData.characters[i]))
                                        {
                                            KeyInfoType->MgmtData.characters[i]   = '?';
                                        }
                                    }
                                    strcat(xmlOut, KeyInfoType->MgmtData.characters);
                                }
                                else
                                {
                                    // the string seems to be in the table, but this is not supported
                                    error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                                }
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_characters is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                KeyInfoType->MgmtData_isUsed = 1u;
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}MgmtData>");
                    }
                    break;
                case 8:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &KeyInfoType->ANY.bytesLen, &KeyInfoType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((KeyInfoType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < KeyInfoType->ANY.bytesLen;) {
                            uint32_t octet_a = i < KeyInfoType->ANY.bytesLen ? (unsigned char) KeyInfoType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < KeyInfoType->ANY.bytesLen ? (unsigned char) KeyInfoType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < KeyInfoType->ANY.bytesLen ? (unsigned char) KeyInfoType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[KeyInfoType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        KeyInfoType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 53:
            // Grammar: ID=53; read/write bits=4; START (KeyName), START (KeyValue), START (RetrievalMethod), START (X509Data), START (PGPData), START (SPKIData), START (MgmtData), START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 4, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (KeyName, string (string)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}KeyName");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}KeyName");
                    // decode: string (len, characters)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            error = exi_basetypes_decoder_uint_16(stream, &KeyInfoType->KeyName.charactersLen);
                            if (error == 0)
                            {
                                if (KeyInfoType->KeyName.charactersLen >= 2)
                                {
                                    // string tables and table partitions are not supported, so the length has to be decremented by 2
                                    KeyInfoType->KeyName.charactersLen -= 2;
                                    error = exi_basetypes_decoder_characters(stream, KeyInfoType->KeyName.charactersLen, KeyInfoType->KeyName.characters, iso20_acdp_KeyName_CHARACTER_SIZE);
                                    strcat(xmlOut, ">");
                                    for(int i = 0; i < KeyInfoType->KeyName.charactersLen; i++) { // check for unprintable characters
                                        if(!isprint(KeyInfoType->KeyName.characters[i]))
                                        {
                                            KeyInfoType->KeyName.characters[i]   = '?';
                                        }
                                    }
                                    strcat(xmlOut, KeyInfoType->KeyName.characters);
                                }
                                else
                                {
                                    // the string seems to be in the table, but this is not supported
                                    error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                                }
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_characters is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                KeyInfoType->KeyName_isUsed = 1u;
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}KeyName>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (KeyValue, KeyValueType (KeyValueType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}KeyValue");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}KeyValue");
                    // decode: element
                    error = decode_iso20_acdp_KeyValueType(stream, &KeyInfoType->KeyValue, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->KeyValue_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}KeyValue>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (RetrievalMethod, RetrievalMethodType (RetrievalMethodType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}RetrievalMethod");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}RetrievalMethod");
                    // decode: element
                    error = decode_iso20_acdp_RetrievalMethodType(stream, &KeyInfoType->RetrievalMethod, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->RetrievalMethod_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}RetrievalMethod>");
                    }
                    break;
                case 3:
                    {
                    // Event: START (X509Data, X509DataType (X509DataType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509Data");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}X509Data");
                    // decode: element
                    error = decode_iso20_acdp_X509DataType(stream, &KeyInfoType->X509Data, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->X509Data_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509Data>");
                    }
                    break;
                case 4:
                    {
                    // Event: START (PGPData, PGPDataType (PGPDataType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}PGPData");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}PGPData");
                    // decode: element
                    error = decode_iso20_acdp_PGPDataType(stream, &KeyInfoType->PGPData, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->PGPData_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}PGPData>");
                    }
                    break;
                case 5:
                    {
                    // Event: START (SPKIData, SPKIDataType (SPKIDataType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SPKIData");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SPKIData");
                    // decode: element
                    error = decode_iso20_acdp_SPKIDataType(stream, &KeyInfoType->SPKIData, xmlOut);
                    if (error == 0)
                    {
                        KeyInfoType->SPKIData_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SPKIData>");
                    }
                    break;
                case 6:
                    {
                    // Event: START (MgmtData, string (string)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}MgmtData");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}MgmtData");
                    // decode: string (len, characters)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            error = exi_basetypes_decoder_uint_16(stream, &KeyInfoType->MgmtData.charactersLen);
                            if (error == 0)
                            {
                                if (KeyInfoType->MgmtData.charactersLen >= 2)
                                {
                                    // string tables and table partitions are not supported, so the length has to be decremented by 2
                                    KeyInfoType->MgmtData.charactersLen -= 2;
                                    error = exi_basetypes_decoder_characters(stream, KeyInfoType->MgmtData.charactersLen, KeyInfoType->MgmtData.characters, iso20_acdp_MgmtData_CHARACTER_SIZE);
                                    strcat(xmlOut, ">");
                                    for(int i = 0; i < KeyInfoType->MgmtData.charactersLen; i++) { // check for unprintable characters
                                        if(!isprint(KeyInfoType->MgmtData.characters[i]))
                                        {
                                            KeyInfoType->MgmtData.characters[i]   = '?';
                                        }
                                    }
                                    strcat(xmlOut, KeyInfoType->MgmtData.characters);
                                }
                                else
                                {
                                    // the string seems to be in the table, but this is not supported
                                    error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                                }
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_characters is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                KeyInfoType->MgmtData_isUsed = 1u;
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}MgmtData>");
                    }
                    break;
                case 7:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &KeyInfoType->ANY.bytesLen, &KeyInfoType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((KeyInfoType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < KeyInfoType->ANY.bytesLen;) {
                            uint32_t octet_a = i < KeyInfoType->ANY.bytesLen ? (unsigned char) KeyInfoType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < KeyInfoType->ANY.bytesLen ? (unsigned char) KeyInfoType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < KeyInfoType->ANY.bytesLen ? (unsigned char) KeyInfoType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[KeyInfoType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        KeyInfoType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}Object; type={http://www.w3.org/2000/09/xmldsig#}ObjectType; base type=; content type=mixed;
//          abstract=False; final=False;
// Particle: Encoding, anyURI (0, 1); Id, ID (0, 1); MimeType, string (0, 1); ANY, anyType (0, 1)(old 1, 1);
static int decode_iso20_acdp_ObjectType(exi_bitstream_t* stream, struct iso20_acdp_ObjectType* ObjectType, char* xmlOut) {
    int grammar_id = 54;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_ObjectType(ObjectType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 54:
            // Grammar: ID=54; read/write bits=3; START (Encoding), START (Id), START (MimeType), START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Encoding, anyURI (anyURI)); next=55

                    strcat(xmlOut, " Encoding");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ObjectType->Encoding.charactersLen);
                    if (error == 0)
                    {
                        if (ObjectType->Encoding.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ObjectType->Encoding.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ObjectType->Encoding.charactersLen, ObjectType->Encoding.characters, iso20_acdp_Encoding_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ObjectType->Encoding.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ObjectType->Encoding.characters[i]))
                                {
                                    ObjectType->Encoding.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ObjectType->Encoding.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ObjectType->Encoding_isUsed = 1u;
                    grammar_id = 55;

                    }
                    break;
                case 1:
                    {
                    // Event: START (Id, ID (NCName)); next=56

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ObjectType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (ObjectType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ObjectType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ObjectType->Id.charactersLen, ObjectType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ObjectType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ObjectType->Id.characters[i]))
                                {
                                    ObjectType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ObjectType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ObjectType->Id_isUsed = 1u;
                    grammar_id = 56;

                    }
                    break;
                case 2:
                    {
                    // Event: START (MimeType, string (string)); next=57

                    strcat(xmlOut, " MimeType");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ObjectType->MimeType.charactersLen);
                    if (error == 0)
                    {
                        if (ObjectType->MimeType.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ObjectType->MimeType.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ObjectType->MimeType.charactersLen, ObjectType->MimeType.characters, iso20_acdp_MimeType_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ObjectType->MimeType.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ObjectType->MimeType.characters[i]))
                                {
                                    ObjectType->MimeType.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ObjectType->MimeType.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ObjectType->MimeType_isUsed = 1u;
                    grammar_id = 57;

                    }
                    break;
                case 3:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 4:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 5:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &ObjectType->ANY.bytesLen, &ObjectType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((ObjectType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < ObjectType->ANY.bytesLen;) {
                            uint32_t octet_a = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[ObjectType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        ObjectType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 55:
            // Grammar: ID=55; read/write bits=3; START (Id), START (MimeType), START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Id, ID (NCName)); next=56

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ObjectType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (ObjectType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ObjectType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ObjectType->Id.charactersLen, ObjectType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ObjectType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ObjectType->Id.characters[i]))
                                {
                                    ObjectType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ObjectType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ObjectType->Id_isUsed = 1u;
                    grammar_id = 56;

                    }
                    break;
                case 1:
                    {
                    // Event: START (MimeType, string (string)); next=57

                    strcat(xmlOut, " MimeType");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ObjectType->MimeType.charactersLen);
                    if (error == 0)
                    {
                        if (ObjectType->MimeType.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ObjectType->MimeType.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ObjectType->MimeType.charactersLen, ObjectType->MimeType.characters, iso20_acdp_MimeType_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ObjectType->MimeType.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ObjectType->MimeType.characters[i]))
                                {
                                    ObjectType->MimeType.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ObjectType->MimeType.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ObjectType->MimeType_isUsed = 1u;
                    grammar_id = 57;

                    }
                    break;
                case 2:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 3:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 4:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &ObjectType->ANY.bytesLen, &ObjectType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((ObjectType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < ObjectType->ANY.bytesLen;) {
                            uint32_t octet_a = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[ObjectType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        ObjectType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 56:
            // Grammar: ID=56; read/write bits=3; START (MimeType), START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (MimeType, string (string)); next=57

                    strcat(xmlOut, " MimeType");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ObjectType->MimeType.charactersLen);
                    if (error == 0)
                    {
                        if (ObjectType->MimeType.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ObjectType->MimeType.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ObjectType->MimeType.charactersLen, ObjectType->MimeType.characters, iso20_acdp_MimeType_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ObjectType->MimeType.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ObjectType->MimeType.characters[i]))
                                {
                                    ObjectType->MimeType.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ObjectType->MimeType.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ObjectType->MimeType_isUsed = 1u;
                    grammar_id = 57;

                    }
                    break;
                case 1:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 2:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 3:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &ObjectType->ANY.bytesLen, &ObjectType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((ObjectType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < ObjectType->ANY.bytesLen;) {
                            uint32_t octet_a = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[ObjectType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        ObjectType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 57:
            // Grammar: ID=57; read/write bits=2; START (ANY), END Element, START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode: event not accepted
                    error = EXI_ERROR__UNKNOWN_EVENT_FOR_DECODING;
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                case 2:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &ObjectType->ANY.bytesLen, &ObjectType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((ObjectType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < ObjectType->ANY.bytesLen;) {
                            uint32_t octet_a = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < ObjectType->ANY.bytesLen ? (unsigned char) ObjectType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[ObjectType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        ObjectType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}Signature; type={http://www.w3.org/2000/09/xmldsig#}SignatureType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: Id, ID (0, 1); SignedInfo, SignedInfoType (1, 1); SignatureValue, SignatureValueType (1, 1); KeyInfo, KeyInfoType (0, 1); Object, ObjectType (0, 1);
static int decode_iso20_acdp_SignatureType(exi_bitstream_t* stream, struct iso20_acdp_SignatureType* SignatureType, char* xmlOut) {
    int grammar_id = 58;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_SignatureType(SignatureType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 58:
            // Grammar: ID=58; read/write bits=2; START (Id), START (SignedInfo)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Id, ID (NCName)); next=59

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &SignatureType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (SignatureType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            SignatureType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, SignatureType->Id.charactersLen, SignatureType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < SignatureType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(SignatureType->Id.characters[i]))
                                {
                                    SignatureType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, SignatureType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    SignatureType->Id_isUsed = 1u;
                    grammar_id = 59;

                    }
                    break;
                case 1:
                    {
                    // Event: START (SignedInfo, SignedInfoType (SignedInfoType)); next=60

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignedInfo");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SignedInfo");
                    // decode: element
                    error = decode_iso20_acdp_SignedInfoType(stream, &SignatureType->SignedInfo, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 60;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignedInfo>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 59:
            // Grammar: ID=59; read/write bits=1; START (SignedInfo)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SignedInfo, SignedInfoType (SignedInfoType)); next=60

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignedInfo");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SignedInfo");
                    // decode: element
                    error = decode_iso20_acdp_SignedInfoType(stream, &SignatureType->SignedInfo, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 60;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignedInfo>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 60:
            // Grammar: ID=60; read/write bits=1; START (SignatureValue)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SignatureValue, SignatureValueType (base64Binary)); next=61

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureValue");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SignatureValue");
                    // decode: element
                    error = decode_iso20_acdp_SignatureValueType(stream, &SignatureType->SignatureValue, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 61;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureValue>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 61:
            // Grammar: ID=61; read/write bits=2; START (KeyInfo), START (Object), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (KeyInfo, KeyInfoType (KeyInfoType)); next=63

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}KeyInfo");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}KeyInfo");
                    // decode: element
                    error = decode_iso20_acdp_KeyInfoType(stream, &SignatureType->KeyInfo, xmlOut);
                    if (error == 0)
                    {
                        SignatureType->KeyInfo_isUsed = 1u;
                        grammar_id = 63;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}KeyInfo>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (Object, ObjectType (ObjectType)); next=62

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Object");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Object");
                    // decode: element
                    error = decode_iso20_acdp_ObjectType(stream, &SignatureType->Object, xmlOut);
                    if (error == 0)
                    {
                        SignatureType->Object_isUsed = 1u;
                        grammar_id = 62;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Object>");
                    }
                    break;
                case 2:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 62:
            // Grammar: ID=62; read/write bits=2; START (Object), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Object, ObjectType (ObjectType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Object");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Object");
                    // decode: element
                    error = decode_iso20_acdp_ObjectType(stream, &SignatureType->Object, xmlOut);
                    if (error == 0)
                    {
                        SignatureType->Object_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Object>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 63:
            // Grammar: ID=63; read/write bits=2; START (Object), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Object, ObjectType (ObjectType)); next=64

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Object");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Object");
                    // decode: element
                    error = decode_iso20_acdp_ObjectType(stream, &SignatureType->Object, xmlOut);
                    if (error == 0)
                    {
                        SignatureType->Object_isUsed = 1u;
                        grammar_id = 64;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Object>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 64:
            // Grammar: ID=64; read/write bits=2; START (Object), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Object, ObjectType (ObjectType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Object");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Object");
                    // decode: element
                    error = decode_iso20_acdp_ObjectType(stream, &SignatureType->Object, xmlOut);
                    if (error == 0)
                    {
                        SignatureType->Object_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Object>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:ACDP}EVWLANStrength; type={urn:iso:std:iso:15118:-20:CommonTypes}RationalNumberType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: Exponent, byte (1, 1); Value, short (1, 1);
static int decode_iso20_acdp_RationalNumberType(exi_bitstream_t* stream, struct iso20_acdp_RationalNumberType* RationalNumberType, char* xmlOut) {
    int grammar_id = 65;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_RationalNumberType(RationalNumberType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 65:
            // Grammar: ID=65; read/write bits=1; START (Exponent)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Exponent, byte (short)); next=66

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}Exponent");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}Exponent");
                    // decode: byte (restricted integer)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 8, &value);
                            if (error == 0)
                            {
                                // type has min_value = -128
                                RationalNumberType->Exponent = (int8_t)(value + -128);
                                char append[7]; // max length: 5 digits (uint8) + 1 sign + 1 zero terminator
                                sprintf(append, "%d", RationalNumberType->Exponent);
                                strcat(xmlOut, ">");
                                strcat(xmlOut, append);
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 66;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}Exponent>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 66:
            // Grammar: ID=66; read/write bits=1; START (Value)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Value, short (int)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}Value");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}Value");
                    // decode: short
                    error = decode_exi_type_integer16(stream, &RationalNumberType->Value);
                    if (error == 0)
                    {
                        char append[7]; // max length: 5 digits + 1 sign + 1 zero terminator
                        sprintf(append, "%d", RationalNumberType->Value);
// TODO the short value 'Value' of physical value type is an attribute according to cbexigen. Uncomment me (in jinja) as soon as it is fixed
//
                        strcat(xmlOut, ">");
//
                        strcat(xmlOut, append);
                        grammar_id = 2;
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}Value>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:CommonTypes}Header; type={urn:iso:std:iso:15118:-20:CommonTypes}MessageHeaderType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: SessionID, sessionIDType (1, 1); TimeStamp, unsignedLong (1, 1); Signature, SignatureType (0, 1);
static int decode_iso20_acdp_MessageHeaderType(exi_bitstream_t* stream, struct iso20_acdp_MessageHeaderType* MessageHeaderType, char* xmlOut) {
    int grammar_id = 67;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_MessageHeaderType(MessageHeaderType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 67:
            // Grammar: ID=67; read/write bits=1; START (SessionID)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SessionID, sessionIDType (hexBinary)); next=68

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}SessionID");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}SessionID");
                    // decode exi type: hexBinary
                    error = decode_exi_type_hex_binary(stream, &MessageHeaderType->SessionID.bytesLen, &MessageHeaderType->SessionID.bytes[0], iso20_acdp_sessionIDType_BYTES_SIZE);
                    if (error == 0)
                    {
                        char asHex[128] = "";
                        char* ahPtr = &asHex[0];
                        uint8_t* contentPtr = &MessageHeaderType->SessionID.bytes[0];
                        uint16_t len = MessageHeaderType->SessionID.bytesLen;
                        if(len * 2 + 1 > 128) {  error = -2; strcat(xmlOut, "DECODE_ERROR"); break; }
                        while(len--) {
                          sprintf(ahPtr, "%02X", *contentPtr);
                          ahPtr += 2;
                          ++contentPtr;
                        }
                        *ahPtr = 0;
                        strcat(xmlOut, ">");
                        strcat(xmlOut, asHex);
                        grammar_id = 68;
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}SessionID>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 68:
            // Grammar: ID=68; read/write bits=1; START (TimeStamp)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (TimeStamp, unsignedLong (nonNegativeInteger)); next=69

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}TimeStamp");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}TimeStamp");
                    // decode: unsigned long int
                    error = decode_exi_type_uint64(stream, &MessageHeaderType->TimeStamp);
                    if (error == 0)
                    {
                        char append[20]; // max length: 19 digits + 0 sign + 1 zero terminator
                        sprintf(append, "%llu", MessageHeaderType->TimeStamp);
                        strcat(xmlOut, ">");
                        strcat(xmlOut, append);
                        grammar_id = 69;
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}TimeStamp>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 69:
            // Grammar: ID=69; read/write bits=2; START (Signature), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Signature, SignatureType (SignatureType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Signature");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Signature");
                    // decode: element
                    error = decode_iso20_acdp_SignatureType(stream, &MessageHeaderType->Signature, xmlOut);
                    if (error == 0)
                    {
                        MessageHeaderType->Signature_isUsed = 1u;
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Signature>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}SignatureProperty; type={http://www.w3.org/2000/09/xmldsig#}SignaturePropertyType; base type=; content type=mixed;
//          abstract=False; final=False; choice=True;
// Particle: Id, ID (0, 1); Target, anyURI (1, 1); ANY, anyType (0, 1);
static int decode_iso20_acdp_SignaturePropertyType(exi_bitstream_t* stream, struct iso20_acdp_SignaturePropertyType* SignaturePropertyType, char* xmlOut) {
    int grammar_id = 70;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_SignaturePropertyType(SignaturePropertyType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 70:
            // Grammar: ID=70; read/write bits=2; START (Id), START (Target)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Id, ID (NCName)); next=71

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &SignaturePropertyType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (SignaturePropertyType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            SignaturePropertyType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, SignaturePropertyType->Id.charactersLen, SignaturePropertyType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < SignaturePropertyType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(SignaturePropertyType->Id.characters[i]))
                                {
                                    SignaturePropertyType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, SignaturePropertyType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    SignaturePropertyType->Id_isUsed = 1u;
                    grammar_id = 71;

                    }
                    break;
                case 1:
                    {
                    // Event: START (Target, anyURI (anyURI)); next=72

                    strcat(xmlOut, " Target");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &SignaturePropertyType->Target.charactersLen);
                    if (error == 0)
                    {
                        if (SignaturePropertyType->Target.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            SignaturePropertyType->Target.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, SignaturePropertyType->Target.charactersLen, SignaturePropertyType->Target.characters, iso20_acdp_Target_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < SignaturePropertyType->Target.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(SignaturePropertyType->Target.characters[i]))
                                {
                                    SignaturePropertyType->Target.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, SignaturePropertyType->Target.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    grammar_id = 72;

                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 71:
            // Grammar: ID=71; read/write bits=1; START (Target)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Target, anyURI (anyURI)); next=72

                    strcat(xmlOut, " Target");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &SignaturePropertyType->Target.charactersLen);
                    if (error == 0)
                    {
                        if (SignaturePropertyType->Target.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            SignaturePropertyType->Target.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, SignaturePropertyType->Target.charactersLen, SignaturePropertyType->Target.characters, iso20_acdp_Target_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < SignaturePropertyType->Target.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(SignaturePropertyType->Target.characters[i]))
                                {
                                    SignaturePropertyType->Target.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, SignaturePropertyType->Target.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    grammar_id = 72;

                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 72:
            // Grammar: ID=72; read/write bits=1; START (ANY)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ANY, anyType (base64Binary)); next=2
                    // decode exi type: base64Binary
                    error = decode_exi_type_hex_binary(stream, &SignaturePropertyType->ANY.bytesLen, &SignaturePropertyType->ANY.bytes[0], iso20_acdp_anyType_BYTES_SIZE);
                    if (error == 0)
                    {
                        // Binary to Base64:
                        char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                        int mod_table[] = {0, 2, 1};
                        size_t output_length = 4 * ((SignaturePropertyType->ANY.bytesLen + 2) / 3);
                        unsigned char* encoded_data = (unsigned char*)malloc(output_length);
                        for (int i = 0, j = 0; i < SignaturePropertyType->ANY.bytesLen;) {
                            uint32_t octet_a = i < SignaturePropertyType->ANY.bytesLen ? (unsigned char) SignaturePropertyType->ANY.bytes[i++] : 0;
                            uint32_t octet_b = i < SignaturePropertyType->ANY.bytesLen ? (unsigned char) SignaturePropertyType->ANY.bytes[i++] : 0;
                            uint32_t octet_c = i < SignaturePropertyType->ANY.bytesLen ? (unsigned char) SignaturePropertyType->ANY.bytes[i++] : 0;
                            
                            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
                            
                            encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                            encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
                        }
                        for (int i = 0; i < mod_table[SignaturePropertyType->ANY.bytesLen % 3]; i++) {
                            encoded_data[output_length - 1 - i] = '=';
                        }
                        strcat(xmlOut, ">");
                        strncat(xmlOut, (char*)encoded_data, output_length);
                        free(encoded_data);
                        SignaturePropertyType->ANY_isUsed = 1u;
                        grammar_id = 2;
                    }



                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:ACDP}EVTechnicalStatus; type={urn:iso:std:iso:15118:-20:ACDP}EVTechnicalStatusType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: EVReadyToCharge, boolean (1, 1); EVImmobilizationRequest, boolean (1, 1); EVImmobilized, boolean (0, 1); EVWLANStrength, RationalNumberType (0, 1); EVCPStatus, cpStatusType (0, 1); EVSOC, percentValueType (0, 1); EVErrorCode, errorCodeType (0, 1); EVTimeout, boolean (0, 1);
static int decode_iso20_acdp_EVTechnicalStatusType(exi_bitstream_t* stream, struct iso20_acdp_EVTechnicalStatusType* EVTechnicalStatusType, char* xmlOut) {
    int grammar_id = 73;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_EVTechnicalStatusType(EVTechnicalStatusType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 73:
            // Grammar: ID=73; read/write bits=1; START (EVReadyToCharge)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVReadyToCharge, boolean (boolean)); next=74

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVReadyToCharge");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVReadyToCharge");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVReadyToCharge = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 74;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVReadyToCharge>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 74:
            // Grammar: ID=74; read/write bits=1; START (EVImmobilizationRequest)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVImmobilizationRequest, boolean (boolean)); next=75

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVImmobilizationRequest");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVImmobilizationRequest");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVImmobilizationRequest = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 75;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVImmobilizationRequest>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 75:
            // Grammar: ID=75; read/write bits=3; START (EVImmobilized), START (EVWLANStrength), START (EVCPStatus), START (EVSOC), START (EVErrorCode), START (EVTimeout), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVImmobilized, boolean (boolean)); next=76

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVImmobilized");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVImmobilized");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVImmobilized = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                                EVTechnicalStatusType->EVImmobilized_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 76;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVImmobilized>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (EVWLANStrength, RationalNumberType (RationalNumberType)); next=77

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVWLANStrength");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVWLANStrength");
                    // decode: element
                    error = decode_iso20_acdp_RationalNumberType(stream, &EVTechnicalStatusType->EVWLANStrength, xmlOut);
                    if (error == 0)
                    {
                        EVTechnicalStatusType->EVWLANStrength_isUsed = 1u;
                        grammar_id = 77;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVWLANStrength>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (EVCPStatus, cpStatusType (string)); next=78

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVCPStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVCPStatus");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 3, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVCPStatus = (iso20_acdp_cpStatusType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_cpStatusType_reverse(value));
                                EVTechnicalStatusType->EVCPStatus_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 78;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVCPStatus>");
                    }
                    break;
                case 3:
                    {
                    // Event: START (EVSOC, percentValueType (byte)); next=79

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSOC");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSOC");
                    // decode: restricted integer (4096 or fewer values)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 7, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVSOC = (int8_t)value;
                                char append[7]; // max length: 5 digits (uint8) + 1 sign + 1 zero terminator
                                sprintf(append, "%d", EVTechnicalStatusType->EVSOC);
                                strcat(xmlOut, ">");
                                strcat(xmlOut, append);
                                EVTechnicalStatusType->EVSOC_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 79;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSOC>");
                    }
                    break;
                case 4:
                    {
                    // Event: START (EVErrorCode, errorCodeType (string)); next=80

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 4, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVErrorCode = (iso20_acdp_errorCodeType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_errorCodeType_reverse(value));
                                EVTechnicalStatusType->EVErrorCode_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 80;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode>");
                    }
                    break;
                case 5:
                    {
                    // Event: START (EVTimeout, boolean (boolean)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVTimeout = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                                EVTechnicalStatusType->EVTimeout_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVTimeout>");
                    }
                    break;
                case 6:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 76:
            // Grammar: ID=76; read/write bits=3; START (EVWLANStrength), START (EVCPStatus), START (EVSOC), START (EVErrorCode), START (EVTimeout), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVWLANStrength, RationalNumberType (RationalNumberType)); next=77

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVWLANStrength");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVWLANStrength");
                    // decode: element
                    error = decode_iso20_acdp_RationalNumberType(stream, &EVTechnicalStatusType->EVWLANStrength, xmlOut);
                    if (error == 0)
                    {
                        EVTechnicalStatusType->EVWLANStrength_isUsed = 1u;
                        grammar_id = 77;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVWLANStrength>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (EVCPStatus, cpStatusType (string)); next=78

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVCPStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVCPStatus");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 3, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVCPStatus = (iso20_acdp_cpStatusType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_cpStatusType_reverse(value));
                                EVTechnicalStatusType->EVCPStatus_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 78;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVCPStatus>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (EVSOC, percentValueType (byte)); next=79

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSOC");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSOC");
                    // decode: restricted integer (4096 or fewer values)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 7, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVSOC = (int8_t)value;
                                char append[7]; // max length: 5 digits (uint8) + 1 sign + 1 zero terminator
                                sprintf(append, "%d", EVTechnicalStatusType->EVSOC);
                                strcat(xmlOut, ">");
                                strcat(xmlOut, append);
                                EVTechnicalStatusType->EVSOC_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 79;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSOC>");
                    }
                    break;
                case 3:
                    {
                    // Event: START (EVErrorCode, errorCodeType (string)); next=80

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 4, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVErrorCode = (iso20_acdp_errorCodeType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_errorCodeType_reverse(value));
                                EVTechnicalStatusType->EVErrorCode_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 80;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode>");
                    }
                    break;
                case 4:
                    {
                    // Event: START (EVTimeout, boolean (boolean)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVTimeout = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                                EVTechnicalStatusType->EVTimeout_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVTimeout>");
                    }
                    break;
                case 5:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 77:
            // Grammar: ID=77; read/write bits=3; START (EVCPStatus), START (EVSOC), START (EVErrorCode), START (EVTimeout), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVCPStatus, cpStatusType (string)); next=78

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVCPStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVCPStatus");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 3, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVCPStatus = (iso20_acdp_cpStatusType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_cpStatusType_reverse(value));
                                EVTechnicalStatusType->EVCPStatus_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 78;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVCPStatus>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (EVSOC, percentValueType (byte)); next=79

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSOC");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSOC");
                    // decode: restricted integer (4096 or fewer values)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 7, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVSOC = (int8_t)value;
                                char append[7]; // max length: 5 digits (uint8) + 1 sign + 1 zero terminator
                                sprintf(append, "%d", EVTechnicalStatusType->EVSOC);
                                strcat(xmlOut, ">");
                                strcat(xmlOut, append);
                                EVTechnicalStatusType->EVSOC_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 79;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSOC>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (EVErrorCode, errorCodeType (string)); next=80

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 4, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVErrorCode = (iso20_acdp_errorCodeType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_errorCodeType_reverse(value));
                                EVTechnicalStatusType->EVErrorCode_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 80;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode>");
                    }
                    break;
                case 3:
                    {
                    // Event: START (EVTimeout, boolean (boolean)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVTimeout = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                                EVTechnicalStatusType->EVTimeout_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVTimeout>");
                    }
                    break;
                case 4:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 78:
            // Grammar: ID=78; read/write bits=3; START (EVSOC), START (EVErrorCode), START (EVTimeout), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 3, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSOC, percentValueType (byte)); next=79

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSOC");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSOC");
                    // decode: restricted integer (4096 or fewer values)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 7, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVSOC = (int8_t)value;
                                char append[7]; // max length: 5 digits (uint8) + 1 sign + 1 zero terminator
                                sprintf(append, "%d", EVTechnicalStatusType->EVSOC);
                                strcat(xmlOut, ">");
                                strcat(xmlOut, append);
                                EVTechnicalStatusType->EVSOC_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 79;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSOC>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (EVErrorCode, errorCodeType (string)); next=80

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 4, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVErrorCode = (iso20_acdp_errorCodeType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_errorCodeType_reverse(value));
                                EVTechnicalStatusType->EVErrorCode_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 80;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode>");
                    }
                    break;
                case 2:
                    {
                    // Event: START (EVTimeout, boolean (boolean)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVTimeout = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                                EVTechnicalStatusType->EVTimeout_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVTimeout>");
                    }
                    break;
                case 3:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 79:
            // Grammar: ID=79; read/write bits=2; START (EVErrorCode), START (EVTimeout), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVErrorCode, errorCodeType (string)); next=80

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 4, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVErrorCode = (iso20_acdp_errorCodeType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_errorCodeType_reverse(value));
                                EVTechnicalStatusType->EVErrorCode_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 80;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVErrorCode>");
                    }
                    break;
                case 1:
                    {
                    // Event: START (EVTimeout, boolean (boolean)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVTimeout = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                                EVTechnicalStatusType->EVTimeout_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVTimeout>");
                    }
                    break;
                case 2:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 80:
            // Grammar: ID=80; read/write bits=2; START (EVTimeout), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVTimeout, boolean (boolean)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVTimeout");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                EVTechnicalStatusType->EVTimeout = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                                EVTechnicalStatusType->EVTimeout_isUsed = 1u;
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVTimeout>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:ACDP}ACDP_VehiclePositioningReq; type={urn:iso:std:iso:15118:-20:ACDP}ACDP_VehiclePositioningReqType; base type=V2GRequestType; content type=ELEMENT-ONLY;
//          abstract=False; final=False; derivation=extension;
// Particle: Header, MessageHeaderType (1, 1); EVMobilityStatus, boolean (1, 1); EVPositioningSupport, boolean (1, 1);
static int decode_iso20_acdp_ACDP_VehiclePositioningReqType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_VehiclePositioningReqType* ACDP_VehiclePositioningReqType, char* xmlOut) {
    int grammar_id = 81;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_ACDP_VehiclePositioningReqType(ACDP_VehiclePositioningReqType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 81:
            // Grammar: ID=81; read/write bits=1; START (Header)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Header, MessageHeaderType (MessageHeaderType)); next=82

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    // decode: element
                    error = decode_iso20_acdp_MessageHeaderType(stream, &ACDP_VehiclePositioningReqType->Header, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 82;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}Header>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 82:
            // Grammar: ID=82; read/write bits=1; START (EVMobilityStatus)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVMobilityStatus, boolean (boolean)); next=83

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVMobilityStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVMobilityStatus");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_VehiclePositioningReqType->EVMobilityStatus = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 83;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVMobilityStatus>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 83:
            // Grammar: ID=83; read/write bits=1; START (EVPositioningSupport)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVPositioningSupport, boolean (boolean)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVPositioningSupport");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVPositioningSupport");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_VehiclePositioningReqType->EVPositioningSupport = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVPositioningSupport>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:ACDP}ACDP_VehiclePositioningRes; type={urn:iso:std:iso:15118:-20:ACDP}ACDP_VehiclePositioningResType; base type=V2GResponseType; content type=ELEMENT-ONLY;
//          abstract=False; final=False; derivation=extension;
// Particle: Header, MessageHeaderType (1, 1); ResponseCode, responseCodeType (1, 1); EVSEProcessing, processingType (1, 1); EVSEPositioningSupport, boolean (1, 1); EVRelativeXDeviation, short (1, 1); EVRelativeYDeviation, short (1, 1); ContactWindowXc, short (1, 1); ContactWindowYc, short (1, 1); EVInChargePosition, boolean (1, 1);
static int decode_iso20_acdp_ACDP_VehiclePositioningResType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_VehiclePositioningResType* ACDP_VehiclePositioningResType, char* xmlOut) {
    int grammar_id = 84;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_ACDP_VehiclePositioningResType(ACDP_VehiclePositioningResType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 84:
            // Grammar: ID=84; read/write bits=1; START (Header)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Header, MessageHeaderType (MessageHeaderType)); next=85

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    // decode: element
                    error = decode_iso20_acdp_MessageHeaderType(stream, &ACDP_VehiclePositioningResType->Header, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 85;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}Header>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 85:
            // Grammar: ID=85; read/write bits=1; START (ResponseCode)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ResponseCode, responseCodeType (string)); next=86

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}ResponseCode");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}ResponseCode");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 6, &value);
                            if (error == 0)
                            {
                                ACDP_VehiclePositioningResType->ResponseCode = (iso20_acdp_responseCodeType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_responseCodeType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 86;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}ResponseCode>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 86:
            // Grammar: ID=86; read/write bits=1; START (EVSEProcessing)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEProcessing, processingType (string)); next=87

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEProcessing");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEProcessing");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 2, &value);
                            if (error == 0)
                            {
                                ACDP_VehiclePositioningResType->EVSEProcessing = (iso20_acdp_processingType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_processingType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 87;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEProcessing>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 87:
            // Grammar: ID=87; read/write bits=1; START (EVSEPositioningSupport)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEPositioningSupport, boolean (boolean)); next=88

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEPositioningSupport");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEPositioningSupport");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_VehiclePositioningResType->EVSEPositioningSupport = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 88;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEPositioningSupport>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 88:
            // Grammar: ID=88; read/write bits=1; START (EVRelativeXDeviation)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVRelativeXDeviation, short (int)); next=89

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVRelativeXDeviation");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVRelativeXDeviation");
                    // decode: short
                    error = decode_exi_type_integer16(stream, &ACDP_VehiclePositioningResType->EVRelativeXDeviation);
                    if (error == 0)
                    {
                        char append[7]; // max length: 5 digits + 1 sign + 1 zero terminator
                        sprintf(append, "%d", ACDP_VehiclePositioningResType->EVRelativeXDeviation);
// TODO the short value 'Value' of physical value type is an attribute according to cbexigen. Uncomment me (in jinja) as soon as it is fixed
//
                        strcat(xmlOut, ">");
//
                        strcat(xmlOut, append);
                        grammar_id = 89;
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVRelativeXDeviation>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 89:
            // Grammar: ID=89; read/write bits=1; START (EVRelativeYDeviation)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVRelativeYDeviation, short (int)); next=90

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVRelativeYDeviation");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVRelativeYDeviation");
                    // decode: short
                    error = decode_exi_type_integer16(stream, &ACDP_VehiclePositioningResType->EVRelativeYDeviation);
                    if (error == 0)
                    {
                        char append[7]; // max length: 5 digits + 1 sign + 1 zero terminator
                        sprintf(append, "%d", ACDP_VehiclePositioningResType->EVRelativeYDeviation);
// TODO the short value 'Value' of physical value type is an attribute according to cbexigen. Uncomment me (in jinja) as soon as it is fixed
//
                        strcat(xmlOut, ">");
//
                        strcat(xmlOut, append);
                        grammar_id = 90;
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVRelativeYDeviation>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 90:
            // Grammar: ID=90; read/write bits=1; START (ContactWindowXc)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ContactWindowXc, short (int)); next=91

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ContactWindowXc");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}ContactWindowXc");
                    // decode: short
                    error = decode_exi_type_integer16(stream, &ACDP_VehiclePositioningResType->ContactWindowXc);
                    if (error == 0)
                    {
                        char append[7]; // max length: 5 digits + 1 sign + 1 zero terminator
                        sprintf(append, "%d", ACDP_VehiclePositioningResType->ContactWindowXc);
// TODO the short value 'Value' of physical value type is an attribute according to cbexigen. Uncomment me (in jinja) as soon as it is fixed
//
                        strcat(xmlOut, ">");
//
                        strcat(xmlOut, append);
                        grammar_id = 91;
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ContactWindowXc>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 91:
            // Grammar: ID=91; read/write bits=1; START (ContactWindowYc)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ContactWindowYc, short (int)); next=92

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ContactWindowYc");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}ContactWindowYc");
                    // decode: short
                    error = decode_exi_type_integer16(stream, &ACDP_VehiclePositioningResType->ContactWindowYc);
                    if (error == 0)
                    {
                        char append[7]; // max length: 5 digits + 1 sign + 1 zero terminator
                        sprintf(append, "%d", ACDP_VehiclePositioningResType->ContactWindowYc);
// TODO the short value 'Value' of physical value type is an attribute according to cbexigen. Uncomment me (in jinja) as soon as it is fixed
//
                        strcat(xmlOut, ">");
//
                        strcat(xmlOut, append);
                        grammar_id = 92;
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ContactWindowYc>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 92:
            // Grammar: ID=92; read/write bits=1; START (EVInChargePosition)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVInChargePosition, boolean (boolean)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVInChargePosition");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVInChargePosition");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_VehiclePositioningResType->EVInChargePosition = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVInChargePosition>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:ACDP}ACDP_ConnectReq; type={urn:iso:std:iso:15118:-20:ACDP}ACDP_ConnectReqType; base type=V2GRequestType; content type=ELEMENT-ONLY;
//          abstract=False; final=False; derivation=extension;
// Particle: Header, MessageHeaderType (1, 1); EVElectricalChargingDeviceStatus, electricalChargingDeviceStatusType (1, 1);
static int decode_iso20_acdp_ACDP_ConnectReqType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_ConnectReqType* ACDP_ConnectReqType, char* xmlOut) {
    int grammar_id = 93;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_ACDP_ConnectReqType(ACDP_ConnectReqType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 93:
            // Grammar: ID=93; read/write bits=1; START (Header)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Header, MessageHeaderType (MessageHeaderType)); next=94

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    // decode: element
                    error = decode_iso20_acdp_MessageHeaderType(stream, &ACDP_ConnectReqType->Header, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 94;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}Header>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 94:
            // Grammar: ID=94; read/write bits=1; START (EVElectricalChargingDeviceStatus)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVElectricalChargingDeviceStatus, electricalChargingDeviceStatusType (string)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVElectricalChargingDeviceStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVElectricalChargingDeviceStatus");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 2, &value);
                            if (error == 0)
                            {
                                ACDP_ConnectReqType->EVElectricalChargingDeviceStatus = (iso20_acdp_electricalChargingDeviceStatusType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_electricalChargingDeviceStatusType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVElectricalChargingDeviceStatus>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:ACDP}ACDP_ConnectRes; type={urn:iso:std:iso:15118:-20:ACDP}ACDP_ConnectResType; base type=V2GResponseType; content type=ELEMENT-ONLY;
//          abstract=False; final=False; derivation=extension;
// Particle: Header, MessageHeaderType (1, 1); ResponseCode, responseCodeType (1, 1); EVSEProcessing, processingType (1, 1); EVSEElectricalChargingDeviceStatus, electricalChargingDeviceStatusType (1, 1); EVSEMechanicalChargingDeviceStatus, mechanicalChargingDeviceStatusType (1, 1);
static int decode_iso20_acdp_ACDP_ConnectResType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_ConnectResType* ACDP_ConnectResType, char* xmlOut) {
    int grammar_id = 95;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_ACDP_ConnectResType(ACDP_ConnectResType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 95:
            // Grammar: ID=95; read/write bits=1; START (Header)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Header, MessageHeaderType (MessageHeaderType)); next=96

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    // decode: element
                    error = decode_iso20_acdp_MessageHeaderType(stream, &ACDP_ConnectResType->Header, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 96;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}Header>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 96:
            // Grammar: ID=96; read/write bits=1; START (ResponseCode)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ResponseCode, responseCodeType (string)); next=97

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}ResponseCode");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}ResponseCode");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 6, &value);
                            if (error == 0)
                            {
                                ACDP_ConnectResType->ResponseCode = (iso20_acdp_responseCodeType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_responseCodeType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 97;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}ResponseCode>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 97:
            // Grammar: ID=97; read/write bits=1; START (EVSEProcessing)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEProcessing, processingType (string)); next=98

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEProcessing");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEProcessing");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 2, &value);
                            if (error == 0)
                            {
                                ACDP_ConnectResType->EVSEProcessing = (iso20_acdp_processingType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_processingType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 98;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEProcessing>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 98:
            // Grammar: ID=98; read/write bits=1; START (EVSEElectricalChargingDeviceStatus)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEElectricalChargingDeviceStatus, electricalChargingDeviceStatusType (string)); next=99

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEElectricalChargingDeviceStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEElectricalChargingDeviceStatus");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 2, &value);
                            if (error == 0)
                            {
                                ACDP_ConnectResType->EVSEElectricalChargingDeviceStatus = (iso20_acdp_electricalChargingDeviceStatusType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_electricalChargingDeviceStatusType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 99;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEElectricalChargingDeviceStatus>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 99:
            // Grammar: ID=99; read/write bits=1; START (EVSEMechanicalChargingDeviceStatus)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEMechanicalChargingDeviceStatus, mechanicalChargingDeviceStatusType (string)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEMechanicalChargingDeviceStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEMechanicalChargingDeviceStatus");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 2, &value);
                            if (error == 0)
                            {
                                ACDP_ConnectResType->EVSEMechanicalChargingDeviceStatus = (iso20_acdp_mechanicalChargingDeviceStatusType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_mechanicalChargingDeviceStatusType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEMechanicalChargingDeviceStatus>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:ACDP}ACDP_SystemStatusReq; type={urn:iso:std:iso:15118:-20:ACDP}ACDP_SystemStatusReqType; base type=V2GRequestType; content type=ELEMENT-ONLY;
//          abstract=False; final=False; derivation=extension;
// Particle: Header, MessageHeaderType (1, 1); EVTechnicalStatus, EVTechnicalStatusType (1, 1);
static int decode_iso20_acdp_ACDP_SystemStatusReqType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_SystemStatusReqType* ACDP_SystemStatusReqType, char* xmlOut) {
    int grammar_id = 100;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_ACDP_SystemStatusReqType(ACDP_SystemStatusReqType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 100:
            // Grammar: ID=100; read/write bits=1; START (Header)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Header, MessageHeaderType (MessageHeaderType)); next=101

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    // decode: element
                    error = decode_iso20_acdp_MessageHeaderType(stream, &ACDP_SystemStatusReqType->Header, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 101;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}Header>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 101:
            // Grammar: ID=101; read/write bits=1; START (EVTechnicalStatus)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVTechnicalStatus, EVTechnicalStatusType (EVTechnicalStatusType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVTechnicalStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVTechnicalStatus");
                    // decode: element
                    error = decode_iso20_acdp_EVTechnicalStatusType(stream, &ACDP_SystemStatusReqType->EVTechnicalStatus, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVTechnicalStatus>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:ACDP}ACDP_SystemStatusRes; type={urn:iso:std:iso:15118:-20:ACDP}ACDP_SystemStatusResType; base type=V2GResponseType; content type=ELEMENT-ONLY;
//          abstract=False; final=False; derivation=extension;
// Particle: Header, MessageHeaderType (1, 1); ResponseCode, responseCodeType (1, 1); EVSEMechanicalChargingDeviceStatus, mechanicalChargingDeviceStatusType (1, 1); EVSEReadyToCharge, boolean (1, 1); EVSEIsolationStatus, isolationStatusType (1, 1); EVSEDisabled, boolean (1, 1); EVSEUtilityInterruptEvent, boolean (1, 1); EVSEEmergencyShutdown, boolean (1, 1); EVSEMalfunction, boolean (1, 1); EVInChargePosition, boolean (1, 1); EVAssociationStatus, boolean (1, 1);
static int decode_iso20_acdp_ACDP_SystemStatusResType(exi_bitstream_t* stream, struct iso20_acdp_ACDP_SystemStatusResType* ACDP_SystemStatusResType, char* xmlOut) {
    int grammar_id = 102;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_ACDP_SystemStatusResType(ACDP_SystemStatusResType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 102:
            // Grammar: ID=102; read/write bits=1; START (Header)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Header, MessageHeaderType (MessageHeaderType)); next=103

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}Header");
                    // decode: element
                    error = decode_iso20_acdp_MessageHeaderType(stream, &ACDP_SystemStatusResType->Header, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 103;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}Header>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 103:
            // Grammar: ID=103; read/write bits=1; START (ResponseCode)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ResponseCode, responseCodeType (string)); next=104

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}ResponseCode");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:CommonTypes}ResponseCode");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 6, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->ResponseCode = (iso20_acdp_responseCodeType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_responseCodeType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 104;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}ResponseCode>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 104:
            // Grammar: ID=104; read/write bits=1; START (EVSEMechanicalChargingDeviceStatus)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEMechanicalChargingDeviceStatus, mechanicalChargingDeviceStatusType (string)); next=105

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEMechanicalChargingDeviceStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEMechanicalChargingDeviceStatus");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 2, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->EVSEMechanicalChargingDeviceStatus = (iso20_acdp_mechanicalChargingDeviceStatusType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_mechanicalChargingDeviceStatusType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 105;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEMechanicalChargingDeviceStatus>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 105:
            // Grammar: ID=105; read/write bits=1; START (EVSEReadyToCharge)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEReadyToCharge, boolean (boolean)); next=106

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEReadyToCharge");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEReadyToCharge");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->EVSEReadyToCharge = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 106;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEReadyToCharge>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 106:
            // Grammar: ID=106; read/write bits=1; START (EVSEIsolationStatus)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEIsolationStatus, isolationStatusType (string)); next=107

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEIsolationStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEIsolationStatus");
                    // decode: enum
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 2, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->EVSEIsolationStatus = (iso20_acdp_isolationStatusType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_iso20_acdp_isolationStatusType_reverse(value));
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 107;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEIsolationStatus>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 107:
            // Grammar: ID=107; read/write bits=1; START (EVSEDisabled)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEDisabled, boolean (boolean)); next=108

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEDisabled");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEDisabled");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->EVSEDisabled = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 108;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEDisabled>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 108:
            // Grammar: ID=108; read/write bits=1; START (EVSEUtilityInterruptEvent)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEUtilityInterruptEvent, boolean (boolean)); next=109

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEUtilityInterruptEvent");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEUtilityInterruptEvent");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->EVSEUtilityInterruptEvent = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 109;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEUtilityInterruptEvent>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 109:
            // Grammar: ID=109; read/write bits=1; START (EVSEEmergencyShutdown)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEEmergencyShutdown, boolean (boolean)); next=110

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEEmergencyShutdown");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEEmergencyShutdown");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->EVSEEmergencyShutdown = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 110;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEEmergencyShutdown>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 110:
            // Grammar: ID=110; read/write bits=1; START (EVSEMalfunction)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVSEMalfunction, boolean (boolean)); next=111

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVSEMalfunction");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVSEMalfunction");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->EVSEMalfunction = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 111;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVSEMalfunction>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 111:
            // Grammar: ID=111; read/write bits=1; START (EVInChargePosition)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVInChargePosition, boolean (boolean)); next=112

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVInChargePosition");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVInChargePosition");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->EVInChargePosition = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 112;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVInChargePosition>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 112:
            // Grammar: ID=112; read/write bits=1; START (EVAssociationStatus)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (EVAssociationStatus, boolean (boolean)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}EVAssociationStatus");
                    xmlPos += strlen("<{urn:iso:std:iso:15118:-20:ACDP}EVAssociationStatus");
                    // decode: boolean
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 1, &value);
                            if (error == 0)
                            {
                                ACDP_SystemStatusResType->EVAssociationStatus = value;
                                    strcat(xmlOut, ">");
                                strcat(xmlOut, value ? "true" : "false");
                            }
                        }
                        else
                        {
                            // second level event is not supported
                            error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                        }
                    }

                    // if nothing went wrong, the error of exi_basetypes_decoder_nbit_uint is evaluated here
                    if (error == 0)
                    {
                        // END Element for simple type
                        error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                        if (error == 0)
                        {
                            if (eventCode == 0)
                            {
                                grammar_id = 2;
                            }
                            else
                            {
                                error = EXI_ERROR__DEVIANTS_NOT_SUPPORTED;
                            }
                        }
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}EVAssociationStatus>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:CommonTypes}CLReqControlMode; type={urn:iso:std:iso:15118:-20:CommonTypes}CLReqControlModeType; base type=; content type=empty;
//          abstract=False; final=False;
static int decode_iso20_acdp_CLReqControlModeType(exi_bitstream_t* stream, struct iso20_acdp_CLReqControlModeType* CLReqControlModeType, char* xmlOut) {
    // Element has no particles, so the function just decodes END Element
    (void)CLReqControlModeType;
    uint32_t eventCode;

    int error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
    if (error == 0)
    {
        if (eventCode != 0)
        {
            error = EXI_ERROR__UNKNOWN_EVENT_CODE;
        }
    }

    return error;
}

// Element: definition=complex; name={urn:iso:std:iso:15118:-20:CommonTypes}CLResControlMode; type={urn:iso:std:iso:15118:-20:CommonTypes}CLResControlModeType; base type=; content type=empty;
//          abstract=False; final=False;
static int decode_iso20_acdp_CLResControlModeType(exi_bitstream_t* stream, struct iso20_acdp_CLResControlModeType* CLResControlModeType, char* xmlOut) {
    // Element has no particles, so the function just decodes END Element
    (void)CLResControlModeType;
    uint32_t eventCode;

    int error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
    if (error == 0)
    {
        if (eventCode != 0)
        {
            error = EXI_ERROR__UNKNOWN_EVENT_CODE;
        }
    }

    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}Manifest; type={http://www.w3.org/2000/09/xmldsig#}ManifestType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: Id, ID (0, 1); Reference, ReferenceType (1, 4);
static int decode_iso20_acdp_ManifestType(exi_bitstream_t* stream, struct iso20_acdp_ManifestType* ManifestType, char* xmlOut) {
    int grammar_id = 113;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_ManifestType(ManifestType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 113:
            // Grammar: ID=113; read/write bits=2; START (Id), START (Reference)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Id, ID (NCName)); next=118

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &ManifestType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (ManifestType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            ManifestType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, ManifestType->Id.charactersLen, ManifestType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < ManifestType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(ManifestType->Id.characters[i]))
                                {
                                    ManifestType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, ManifestType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    ManifestType->Id_isUsed = 1u;
                    grammar_id = 118;

                    }
                    break;
                case 1:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=114

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 114;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 114:
            // Grammar: ID=114; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=115

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 115;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 115:
            // Grammar: ID=115; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=116

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 116;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 116:
            // Grammar: ID=116; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=117

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 117;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 117:
            // Grammar: ID=117; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 2;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 118:
            // Grammar: ID=118; read/write bits=1; START (Reference)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=119

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 119;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 119:
            // Grammar: ID=119; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=120

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 120;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 120:
            // Grammar: ID=120; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=121

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 121;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 121:
            // Grammar: ID=121; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=122

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 122;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 122:
            // Grammar: ID=122; read/write bits=2; START (Reference), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Reference, ReferenceType (ReferenceType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}Reference");
                    // decode: element array
                    if (ManifestType->Reference.arrayLen < iso20_acdp_ReferenceType_4_ARRAY_SIZE)
                    {

                        error = decode_iso20_acdp_ReferenceType(stream, &ManifestType->Reference.array[ManifestType->Reference.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 2;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}

// Element: definition=complex; name={http://www.w3.org/2000/09/xmldsig#}SignatureProperties; type={http://www.w3.org/2000/09/xmldsig#}SignaturePropertiesType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: Id, ID (0, 1); SignatureProperty, SignaturePropertyType (1, 1);
static int decode_iso20_acdp_SignaturePropertiesType(exi_bitstream_t* stream, struct iso20_acdp_SignaturePropertiesType* SignaturePropertiesType, char* xmlOut) {
    int grammar_id = 123;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_iso20_acdp_SignaturePropertiesType(SignaturePropertiesType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 123:
            // Grammar: ID=123; read/write bits=2; START (Id), START (SignatureProperty)
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Id, ID (NCName)); next=125

                    strcat(xmlOut, " Id");
                    // decode: string (len, characters) (Attribute)
                    error = exi_basetypes_decoder_uint_16(stream, &SignaturePropertiesType->Id.charactersLen);
                    if (error == 0)
                    {
                        if (SignaturePropertiesType->Id.charactersLen >= 2)
                        {
                            // string tables and table partitions are not supported, so the length has to be decremented by 2
                            SignaturePropertiesType->Id.charactersLen -= 2;
                            error = exi_basetypes_decoder_characters(stream, SignaturePropertiesType->Id.charactersLen, SignaturePropertiesType->Id.characters, iso20_acdp_Id_CHARACTER_SIZE);
                            strcat(xmlOut, "=\"");
                            for(int i = 0; i < SignaturePropertiesType->Id.charactersLen; i++) { // check for unprintable characters
                                if(!isprint(SignaturePropertiesType->Id.characters[i]))
                                {
                                    SignaturePropertiesType->Id.characters[i]   = '?';
                                }
                            }
                            strcat(xmlOut, SignaturePropertiesType->Id.characters);
                            strcat(xmlOut, "\"");
                        }
                        else
                        {
                            // the string seems to be in the table, but this is not supported
                            error = EXI_ERROR__STRINGVALUES_NOT_SUPPORTED;
                        }
                    }
                    SignaturePropertiesType->Id_isUsed = 1u;
                    grammar_id = 125;

                    }
                    break;
                case 1:
                    {
                    // Event: START (SignatureProperty, SignaturePropertyType (SignaturePropertyType)); next=124

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureProperty");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SignatureProperty");
                    // decode: element
                    error = decode_iso20_acdp_SignaturePropertyType(stream, &SignaturePropertiesType->SignatureProperty, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 124;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureProperty>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 124:
            // Grammar: ID=124; read/write bits=2; START (SignatureProperty), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SignatureProperty, SignaturePropertyType (SignaturePropertyType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureProperty");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SignatureProperty");
                    // decode: element
                    error = decode_iso20_acdp_SignaturePropertyType(stream, &SignaturePropertiesType->SignatureProperty, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureProperty>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 125:
            // Grammar: ID=125; read/write bits=1; START (SignatureProperty)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SignatureProperty, SignaturePropertyType (SignaturePropertyType)); next=126

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureProperty");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SignatureProperty");
                    // decode: element
                    error = decode_iso20_acdp_SignaturePropertyType(stream, &SignaturePropertiesType->SignatureProperty, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 126;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureProperty>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 126:
            // Grammar: ID=126; read/write bits=2; START (SignatureProperty), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SignatureProperty, SignaturePropertyType (SignaturePropertyType)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureProperty");
                    xmlPos += strlen("<{http://www.w3.org/2000/09/xmldsig#}SignatureProperty");
                    // decode: element
                    error = decode_iso20_acdp_SignaturePropertyType(stream, &SignaturePropertiesType->SignatureProperty, xmlOut);
                    if (error == 0)
                    {
                        grammar_id = 2;
                    }


                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureProperty>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=3
                    done = 1;
                    grammar_id = 3;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        default:
            error = EXI_ERROR__UNKNOWN_GRAMMAR_ID;
            break;
        }

        if (error)
        {
            done = 1;
        }
    }
    return error;
}


// main function for decoding
int decode_iso20_acdp_exiDocument(exi_bitstream_t* stream, struct iso20_acdp_exiDocument* exiDoc, char* xmlOut) {
    uint32_t eventCode;
    int error = exi_header_read_and_check(stream);

    if (error == 0)
    {
        init_iso20_acdp_exiDocument(exiDoc);
        strcat(xmlOut, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");

        error = exi_basetypes_decoder_nbit_uint(stream, 6, &eventCode);
        if (error == 0)
        {
            switch(eventCode)
            {
            case 0:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ACDP_ConnectReq>");
                error = decode_iso20_acdp_ACDP_ConnectReqType(stream, &exiDoc->ACDP_ConnectReq, xmlOut);
                exiDoc->ACDP_ConnectReq_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ACDP_ConnectReq>");
                break;
            case 1:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ACDP_DisconnectReq>");
                error = decode_iso20_acdp_ACDP_ConnectReqType(stream, &exiDoc->ACDP_DisconnectReq, xmlOut);
                exiDoc->ACDP_DisconnectReq_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ACDP_DisconnectReq>");
                break;
            case 2:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ACDP_ConnectRes>");
                error = decode_iso20_acdp_ACDP_ConnectResType(stream, &exiDoc->ACDP_ConnectRes, xmlOut);
                exiDoc->ACDP_ConnectRes_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ACDP_ConnectRes>");
                break;
            case 3:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ACDP_DisconnectRes>");
                error = decode_iso20_acdp_ACDP_ConnectResType(stream, &exiDoc->ACDP_DisconnectRes, xmlOut);
                exiDoc->ACDP_DisconnectRes_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ACDP_DisconnectRes>");
                break;
            case 4:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ACDP_SystemStatusReq>");
                error = decode_iso20_acdp_ACDP_SystemStatusReqType(stream, &exiDoc->ACDP_SystemStatusReq, xmlOut);
                exiDoc->ACDP_SystemStatusReq_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ACDP_SystemStatusReq>");
                break;
            case 5:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ACDP_SystemStatusRes>");
                error = decode_iso20_acdp_ACDP_SystemStatusResType(stream, &exiDoc->ACDP_SystemStatusRes, xmlOut);
                exiDoc->ACDP_SystemStatusRes_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ACDP_SystemStatusRes>");
                break;
            case 6:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ACDP_VehiclePositioningReq>");
                error = decode_iso20_acdp_ACDP_VehiclePositioningReqType(stream, &exiDoc->ACDP_VehiclePositioningReq, xmlOut);
                exiDoc->ACDP_VehiclePositioningReq_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ACDP_VehiclePositioningReq>");
                break;
            case 7:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:ACDP}ACDP_VehiclePositioningRes>");
                error = decode_iso20_acdp_ACDP_VehiclePositioningResType(stream, &exiDoc->ACDP_VehiclePositioningRes, xmlOut);
                exiDoc->ACDP_VehiclePositioningRes_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:ACDP}ACDP_VehiclePositioningRes>");
                break;
            case 8:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}CLReqControlMode>");
                error = decode_iso20_acdp_CLReqControlModeType(stream, &exiDoc->CLReqControlMode, xmlOut);
                exiDoc->CLReqControlMode_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}CLReqControlMode>");
                break;
            case 9:
                
                strcat(xmlOut, "<{urn:iso:std:iso:15118:-20:CommonTypes}CLResControlMode>");
                error = decode_iso20_acdp_CLResControlModeType(stream, &exiDoc->CLResControlMode, xmlOut);
                exiDoc->CLResControlMode_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:std:iso:15118:-20:CommonTypes}CLResControlMode>");
                break;
            case 10:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethod>");
                error = decode_iso20_acdp_CanonicalizationMethodType(stream, &exiDoc->CanonicalizationMethod, xmlOut);
                exiDoc->CanonicalizationMethod_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}CanonicalizationMethod>");
                break;
            case 11:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DSAKeyValue>");
                error = decode_iso20_acdp_DSAKeyValueType(stream, &exiDoc->DSAKeyValue, xmlOut);
                exiDoc->DSAKeyValue_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DSAKeyValue>");
                break;
            case 12:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DigestMethod>");
                error = decode_iso20_acdp_DigestMethodType(stream, &exiDoc->DigestMethod, xmlOut);
                exiDoc->DigestMethod_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DigestMethod>");
                break;
            case 13:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}DigestValue>");
                // simple type! decode_iso20_acdp_DigestValue;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}DigestValue>");
                break;
            case 14:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}KeyInfo>");
                error = decode_iso20_acdp_KeyInfoType(stream, &exiDoc->KeyInfo, xmlOut);
                exiDoc->KeyInfo_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}KeyInfo>");
                break;
            case 15:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}KeyName>");
                // simple type! decode_iso20_acdp_KeyName;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}KeyName>");
                break;
            case 16:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}KeyValue>");
                error = decode_iso20_acdp_KeyValueType(stream, &exiDoc->KeyValue, xmlOut);
                exiDoc->KeyValue_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}KeyValue>");
                break;
            case 17:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Manifest>");
                error = decode_iso20_acdp_ManifestType(stream, &exiDoc->Manifest, xmlOut);
                exiDoc->Manifest_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Manifest>");
                break;
            case 18:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}MgmtData>");
                // simple type! decode_iso20_acdp_MgmtData;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}MgmtData>");
                break;
            case 19:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Object>");
                error = decode_iso20_acdp_ObjectType(stream, &exiDoc->Object, xmlOut);
                exiDoc->Object_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Object>");
                break;
            case 20:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}PGPData>");
                error = decode_iso20_acdp_PGPDataType(stream, &exiDoc->PGPData, xmlOut);
                exiDoc->PGPData_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}PGPData>");
                break;
            case 21:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}RSAKeyValue>");
                error = decode_iso20_acdp_RSAKeyValueType(stream, &exiDoc->RSAKeyValue, xmlOut);
                exiDoc->RSAKeyValue_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}RSAKeyValue>");
                break;
            case 22:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Reference>");
                error = decode_iso20_acdp_ReferenceType(stream, &exiDoc->Reference, xmlOut);
                exiDoc->Reference_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Reference>");
                break;
            case 23:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}RetrievalMethod>");
                error = decode_iso20_acdp_RetrievalMethodType(stream, &exiDoc->RetrievalMethod, xmlOut);
                exiDoc->RetrievalMethod_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}RetrievalMethod>");
                break;
            case 24:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SPKIData>");
                error = decode_iso20_acdp_SPKIDataType(stream, &exiDoc->SPKIData, xmlOut);
                exiDoc->SPKIData_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SPKIData>");
                break;
            case 25:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureMethod>");
                error = decode_iso20_acdp_SignatureMethodType(stream, &exiDoc->SignatureMethod, xmlOut);
                exiDoc->SignatureMethod_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureMethod>");
                break;
            case 26:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureProperties>");
                error = decode_iso20_acdp_SignaturePropertiesType(stream, &exiDoc->SignatureProperties, xmlOut);
                exiDoc->SignatureProperties_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureProperties>");
                break;
            case 27:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureProperty>");
                error = decode_iso20_acdp_SignaturePropertyType(stream, &exiDoc->SignatureProperty, xmlOut);
                exiDoc->SignatureProperty_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureProperty>");
                break;
            case 28:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Signature>");
                error = decode_iso20_acdp_SignatureType(stream, &exiDoc->Signature, xmlOut);
                exiDoc->Signature_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Signature>");
                break;
            case 29:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignatureValue>");
                error = decode_iso20_acdp_SignatureValueType(stream, &exiDoc->SignatureValue, xmlOut);
                exiDoc->SignatureValue_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignatureValue>");
                break;
            case 30:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}SignedInfo>");
                error = decode_iso20_acdp_SignedInfoType(stream, &exiDoc->SignedInfo, xmlOut);
                exiDoc->SignedInfo_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}SignedInfo>");
                break;
            case 31:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transform>");
                error = decode_iso20_acdp_TransformType(stream, &exiDoc->Transform, xmlOut);
                exiDoc->Transform_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transform>");
                break;
            case 32:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}Transforms>");
                error = decode_iso20_acdp_TransformsType(stream, &exiDoc->Transforms, xmlOut);
                exiDoc->Transforms_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}Transforms>");
                break;
            case 33:
                
                strcat(xmlOut, "<{http://www.w3.org/2000/09/xmldsig#}X509Data>");
                error = decode_iso20_acdp_X509DataType(stream, &exiDoc->X509Data, xmlOut);
                exiDoc->X509Data_isUsed = 1u;
                strcat(xmlOut, "</{http://www.w3.org/2000/09/xmldsig#}X509Data>");
                break;
            default:
                error = EXI_ERROR__UNSUPPORTED_SUB_EVENT;
                break;
            }
        }
    }


    // xmlOut Postprocessing: resolve FQNs
    int FQN_FULL_LENGTH = 50;
    int FQN_SHORT_LENGTH = 5;
    char *prefixList[10][2]; // 10 prefixes max. [0]: shorthand, [1]:fqn
    int prefixCount = 0;
    char* currentXmlPtr = &xmlOut[0];
    size_t posOfPrefixStart;
    size_t prefixSize;
    // create prefix table
    while( (posOfPrefixStart = strcspn(currentXmlPtr, "{")) != strlen(currentXmlPtr) ) {
        currentXmlPtr += posOfPrefixStart + 1;
        prefixSize = strcspn(currentXmlPtr, "}");
        
        bool hit = false;
        // check if prefix already in list
        for(int i = 0; i < prefixCount; i++)
        {
            if(strncmp(prefixList[i][1], currentXmlPtr, prefixSize) == 0)
            {
                hit = true; break;
            }
        }
        if(!hit) {
            prefixList[prefixCount][0] = malloc(sizeof(*prefixList[prefixCount]) * FQN_SHORT_LENGTH);
            prefixList[prefixCount][1] = malloc(sizeof(*prefixList[prefixCount]) * FQN_FULL_LENGTH);
            strncpy(prefixList[prefixCount][1], currentXmlPtr, prefixSize);
            prefixList[prefixCount][1][prefixSize] = 0;
                sprintf(prefixList[prefixCount][0], "ns%d", prefixCount + 1);
                    prefixCount ++;
        }
        currentXmlPtr += prefixSize;
    }
    char* xmlDup = strdup(xmlOut);
    int elementCount = 0;
    int xmlOutLength = 0;
    for(size_t i = 0; i < strlen(xmlDup); i++)
    {
        if(xmlDup[i] == '{')
        {
            // handle prefix stuff
            i++; // skip '{'
            char fqn[FQN_FULL_LENGTH];
            memset(fqn, 0, FQN_FULL_LENGTH*sizeof(char) );
            for(int j = 0; j < FQN_FULL_LENGTH && i < strlen(xmlDup); j++)
            {
                if(xmlDup[i] == '}') { fqn[j] = 0; break; }
                else { fqn[j] = xmlDup[i]; }
                i++;
            }
            xmlOut[xmlOutLength] = 0;
            for(int k = 0; k < prefixCount; k++) {
                if (strcmp(fqn, prefixList[k][1]) == 0)
                {
                    strcat(xmlOut, prefixList[k][0]);
                    strcat(xmlOut, ":");
                    xmlOutLength += strlen(prefixList[k][0]) + 1;
                    break;
                }
            }
        }
        else
        {
            if(xmlDup[i] == '<') elementCount++;
            if(elementCount == 2 && xmlDup[i] == '>')
            {
                // root element, add namespaces here
                for(int j = 0; j < prefixCount; j++)
                {
                    xmlOut[xmlOutLength] = 0;
                    strcat(xmlOut, " xmlns:");
                    strcat(xmlOut, prefixList[j][0]);
                    strcat(xmlOut, "=\"");
                    strcat(xmlOut, prefixList[j][1]);
                    strcat(xmlOut, "\"");
                    xmlOutLength = strlen(xmlOut);
                }
            }
            xmlOut[xmlOutLength++] = xmlDup[i];
        }
    }
    xmlOut[xmlOutLength] = 0;
    
    // clean up
    for(int i = 0; i < prefixCount; i++)
    {
        free(prefixList[i][0]);
        free(prefixList[i][1]);
    }
    free(xmlDup);

    return error;
}


