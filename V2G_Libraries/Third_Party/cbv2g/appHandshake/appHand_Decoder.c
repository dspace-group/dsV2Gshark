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
  * @file appHand_Decoder.c
  * @brief Description goes here
  *
  **/
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "exi_basetypes.h"
#include "exi_basetypes_decoder.h"
#include "exi_error_codes.h"
#include "exi_header.h"
#include "exi_types_decoder.h"
#include "appHand_Datatypes.h"



static int decode_appHand_AppProtocolType(exi_bitstream_t* stream, struct appHand_AppProtocolType* AppProtocolType, char* xmlOut);
static int decode_appHand_supportedAppProtocolReq(exi_bitstream_t* stream, struct appHand_supportedAppProtocolReq* supportedAppProtocolReq, char* xmlOut);
static int decode_appHand_supportedAppProtocolRes(exi_bitstream_t* stream, struct appHand_supportedAppProtocolRes* supportedAppProtocolRes, char* xmlOut);

// Element: definition=complex; name=AppProtocol; type={urn:iso:15118:2:2010:AppProtocol}AppProtocolType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: ProtocolNamespace, protocolNamespaceType (1, 1); VersionNumberMajor, unsignedInt (1, 1); VersionNumberMinor, unsignedInt (1, 1); SchemaID, idType (1, 1); Priority, priorityType (1, 1);
static int decode_appHand_AppProtocolType(exi_bitstream_t* stream, struct appHand_AppProtocolType* AppProtocolType, char* xmlOut) {
    int grammar_id = 0;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_appHand_AppProtocolType(AppProtocolType);

    while(!done)
    {
        switch(grammar_id)
        {
        case 0:
            // Grammar: ID=0; read/write bits=1; START (ProtocolNamespace)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ProtocolNamespace, protocolNamespaceType (anyURI)); next=1

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<ProtocolNamespace");
                    xmlPos += strlen("<ProtocolNamespace");
                    // decode: string (len, characters)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            error = exi_basetypes_decoder_uint_16(stream, &AppProtocolType->ProtocolNamespace.charactersLen);
                            if (error == 0)
                            {
                                if (AppProtocolType->ProtocolNamespace.charactersLen >= 2)
                                {
                                    // string tables and table partitions are not supported, so the length has to be decremented by 2
                                    AppProtocolType->ProtocolNamespace.charactersLen -= 2;
                                    error = exi_basetypes_decoder_characters(stream, AppProtocolType->ProtocolNamespace.charactersLen, AppProtocolType->ProtocolNamespace.characters, appHand_ProtocolNamespace_CHARACTER_SIZE);
                                    strcat(xmlOut, ">");
                                    for(int i = 0; i < AppProtocolType->ProtocolNamespace.charactersLen; i++) { // check for unprintable characters
                                        if(!isprint(AppProtocolType->ProtocolNamespace.characters[i]))
                                        {
                                            AppProtocolType->ProtocolNamespace.characters[i]   = '?';
                                        }
                                    }
                                    strcat(xmlOut, AppProtocolType->ProtocolNamespace.characters);
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
                                grammar_id = 1;
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
                    strcat(xmlOut, "</ProtocolNamespace>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 1:
            // Grammar: ID=1; read/write bits=1; START (VersionNumberMajor)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (VersionNumberMajor, unsignedInt (unsignedLong)); next=2

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<VersionNumberMajor");
                    xmlPos += strlen("<VersionNumberMajor");
                    // decode: unsigned int
                    error = decode_exi_type_uint32(stream, &AppProtocolType->VersionNumberMajor);
                    if (error == 0)
                    {
                        char append[11]; // max length: 10 digits + 0 sign + 1 zero terminator
                        sprintf(append, "%u", AppProtocolType->VersionNumberMajor);
                        strcat(xmlOut, ">");
                        strcat(xmlOut, append);
                        grammar_id = 2;
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</VersionNumberMajor>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 2:
            // Grammar: ID=2; read/write bits=1; START (VersionNumberMinor)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (VersionNumberMinor, unsignedInt (unsignedLong)); next=3

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<VersionNumberMinor");
                    xmlPos += strlen("<VersionNumberMinor");
                    // decode: unsigned int
                    error = decode_exi_type_uint32(stream, &AppProtocolType->VersionNumberMinor);
                    if (error == 0)
                    {
                        char append[11]; // max length: 10 digits + 0 sign + 1 zero terminator
                        sprintf(append, "%u", AppProtocolType->VersionNumberMinor);
                        strcat(xmlOut, ">");
                        strcat(xmlOut, append);
                        grammar_id = 3;
                    }

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</VersionNumberMinor>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 3:
            // Grammar: ID=3; read/write bits=1; START (SchemaID)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SchemaID, idType (unsignedByte)); next=4

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<SchemaID");
                    xmlPos += strlen("<SchemaID");
                    // decode: restricted integer (4096 or fewer values)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 8, &value);
                            if (error == 0)
                            {
                                AppProtocolType->SchemaID = (uint8_t)value;
                                char append[7]; // max length: 5 digits (uint8) + 1 sign + 1 zero terminator
                                sprintf(append, "%d", AppProtocolType->SchemaID);
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
                                grammar_id = 4;
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
                    strcat(xmlOut, "</SchemaID>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 4:
            // Grammar: ID=4; read/write bits=1; START (Priority)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (Priority, priorityType (unsignedByte)); next=5

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<Priority");
                    xmlPos += strlen("<Priority");
                    // decode: restricted integer (4096 or fewer values)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 5, &value);
                            if (error == 0)
                            {
                                // type has min_value = 1
                                AppProtocolType->Priority = (uint8_t)(value + 1);
                                char append[7]; // max length: 5 digits (uint8) + 1 sign + 1 zero terminator
                                sprintf(append, "%d", AppProtocolType->Priority);
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
                                grammar_id = 5;
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
                    strcat(xmlOut, "</Priority>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 5:
            // Grammar: ID=5; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=6
                    done = 1;
                    grammar_id = 6;
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

// Element: definition=complex; name={urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolReq; type=AnonymousType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: AppProtocol, AppProtocolType (1, 5);
static int decode_appHand_supportedAppProtocolReq(exi_bitstream_t* stream, struct appHand_supportedAppProtocolReq* supportedAppProtocolReq, char* xmlOut) {
    int grammar_id = 7;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_appHand_supportedAppProtocolReq(supportedAppProtocolReq);

    while(!done)
    {
        switch(grammar_id)
        {
        case 7:
            // Grammar: ID=7; read/write bits=1; START (AppProtocol)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (AppProtocol, AppProtocolType (AppProtocolType)); next=8

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<AppProtocol");
                    xmlPos += strlen("<AppProtocol");
                    // decode: element array
                    if (supportedAppProtocolReq->AppProtocol.arrayLen < appHand_AppProtocolType_5_ARRAY_SIZE)
                    {

                        error = decode_appHand_AppProtocolType(stream, &supportedAppProtocolReq->AppProtocol.array[supportedAppProtocolReq->AppProtocol.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 8;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</AppProtocol>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 8:
            // Grammar: ID=8; read/write bits=2; START (AppProtocol), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (AppProtocol, AppProtocolType (AppProtocolType)); next=9

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<AppProtocol");
                    xmlPos += strlen("<AppProtocol");
                    // decode: element array
                    if (supportedAppProtocolReq->AppProtocol.arrayLen < appHand_AppProtocolType_5_ARRAY_SIZE)
                    {

                        error = decode_appHand_AppProtocolType(stream, &supportedAppProtocolReq->AppProtocol.array[supportedAppProtocolReq->AppProtocol.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 9;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</AppProtocol>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=6
                    done = 1;
                    grammar_id = 6;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 9:
            // Grammar: ID=9; read/write bits=2; START (AppProtocol), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (AppProtocol, AppProtocolType (AppProtocolType)); next=10

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<AppProtocol");
                    xmlPos += strlen("<AppProtocol");
                    // decode: element array
                    if (supportedAppProtocolReq->AppProtocol.arrayLen < appHand_AppProtocolType_5_ARRAY_SIZE)
                    {

                        error = decode_appHand_AppProtocolType(stream, &supportedAppProtocolReq->AppProtocol.array[supportedAppProtocolReq->AppProtocol.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 10;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</AppProtocol>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=6
                    done = 1;
                    grammar_id = 6;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 10:
            // Grammar: ID=10; read/write bits=2; START (AppProtocol), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (AppProtocol, AppProtocolType (AppProtocolType)); next=11

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<AppProtocol");
                    xmlPos += strlen("<AppProtocol");
                    // decode: element array
                    if (supportedAppProtocolReq->AppProtocol.arrayLen < appHand_AppProtocolType_5_ARRAY_SIZE)
                    {

                        error = decode_appHand_AppProtocolType(stream, &supportedAppProtocolReq->AppProtocol.array[supportedAppProtocolReq->AppProtocol.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 11;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</AppProtocol>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=6
                    done = 1;
                    grammar_id = 6;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 11:
            // Grammar: ID=11; read/write bits=2; START (AppProtocol), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (AppProtocol, AppProtocolType (AppProtocolType)); next=12

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<AppProtocol");
                    xmlPos += strlen("<AppProtocol");
                    // decode: element array
                    if (supportedAppProtocolReq->AppProtocol.arrayLen < appHand_AppProtocolType_5_ARRAY_SIZE)
                    {

                        error = decode_appHand_AppProtocolType(stream, &supportedAppProtocolReq->AppProtocol.array[supportedAppProtocolReq->AppProtocol.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 12;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</AppProtocol>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=6
                    done = 1;
                    grammar_id = 6;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 12:
            // Grammar: ID=12; read/write bits=2; START (AppProtocol), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (AppProtocol, AppProtocolType (AppProtocolType)); next=5

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<AppProtocol");
                    xmlPos += strlen("<AppProtocol");
                    // decode: element array
                    if (supportedAppProtocolReq->AppProtocol.arrayLen < appHand_AppProtocolType_5_ARRAY_SIZE)
                    {

                        error = decode_appHand_AppProtocolType(stream, &supportedAppProtocolReq->AppProtocol.array[supportedAppProtocolReq->AppProtocol.arrayLen++], xmlOut);
                    }
                    else
                    {
                        error = EXI_ERROR__ARRAY_OUT_OF_BOUNDS;
                    }
                    grammar_id = 5;

                    bool isClosed = false;
                    while(*xmlPos != '\0' && !isClosed) { if(*xmlPos++ == '>') isClosed = true; }
                    if(!isClosed) {strcat(xmlOut, ">");} // empty element
                    strcat(xmlOut, "</AppProtocol>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=6
                    done = 1;
                    grammar_id = 6;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 5:
            // Grammar: ID=5; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=6
                    done = 1;
                    grammar_id = 6;
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

// Element: definition=complex; name={urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolRes; type=AnonymousType; base type=; content type=ELEMENT-ONLY;
//          abstract=False; final=False;
// Particle: ResponseCode, responseCodeType (1, 1); SchemaID, idType (0, 1);
static int decode_appHand_supportedAppProtocolRes(exi_bitstream_t* stream, struct appHand_supportedAppProtocolRes* supportedAppProtocolRes, char* xmlOut) {
    int grammar_id = 13;
    int done = 0;
    uint32_t eventCode;
    int error;

    init_appHand_supportedAppProtocolRes(supportedAppProtocolRes);

    while(!done)
    {
        switch(grammar_id)
        {
        case 13:
            // Grammar: ID=13; read/write bits=1; START (ResponseCode)
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (ResponseCode, responseCodeType (string)); next=14

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<ResponseCode");
                    xmlPos += strlen("<ResponseCode");
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
                                supportedAppProtocolRes->ResponseCode = (appHand_responseCodeType)value;
                                strcat(xmlOut, ">");
                                strcat(xmlOut, get_enum_val_appHand_responseCodeType_reverse(value));
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
                    strcat(xmlOut, "</ResponseCode>");
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 14:
            // Grammar: ID=14; read/write bits=2; START (SchemaID), END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: START (SchemaID, idType (unsignedByte)); next=5

                    char* xmlPos = &xmlOut[strlen(xmlOut)];
                    if(*(xmlPos - 1) != '>') { strcat(xmlOut, ">"); xmlPos++; }
                    strcat(xmlOut, "<SchemaID");
                    xmlPos += strlen("<SchemaID");
                    // decode: restricted integer (4096 or fewer values)
                    error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
                    if (error == 0)
                    {
                        if (eventCode == 0)
                        {
                            uint32_t value;
                            error = exi_basetypes_decoder_nbit_uint(stream, 8, &value);
                            if (error == 0)
                            {
                                supportedAppProtocolRes->SchemaID = (uint8_t)value;
                                char append[7]; // max length: 5 digits (uint8) + 1 sign + 1 zero terminator
                                sprintf(append, "%d", supportedAppProtocolRes->SchemaID);
                                strcat(xmlOut, ">");
                                strcat(xmlOut, append);
                                supportedAppProtocolRes->SchemaID_isUsed = 1u;
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
                                grammar_id = 5;
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
                    strcat(xmlOut, "</SchemaID>");
                    }
                    break;
                case 1:
                    {
                    // Event: END Element; next=6
                    done = 1;
                    grammar_id = 6;
                    }
                    break;
                default:
                    error = EXI_ERROR__UNKNOWN_EVENT_CODE;
                    break;
                }
            }
            break;
        case 5:
            // Grammar: ID=5; read/write bits=1; END Element
            error = exi_basetypes_decoder_nbit_uint(stream, 1, &eventCode);
            if (error == 0)
            {
                switch(eventCode)
                {
                case 0:
                    {
                    // Event: END Element; next=6
                    done = 1;
                    grammar_id = 6;
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
int decode_appHand_exiDocument(exi_bitstream_t* stream, struct appHand_exiDocument* exiDoc, char* xmlOut) {
    uint32_t eventCode;
    int error = exi_header_read_and_check(stream);

    if (error == 0)
    {
        init_appHand_exiDocument(exiDoc);
        strcat(xmlOut, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");

        error = exi_basetypes_decoder_nbit_uint(stream, 2, &eventCode);
        if (error == 0)
        {
            switch(eventCode)
            {
            case 0:
                
                strcat(xmlOut, "<{urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolReq>");
                error = decode_appHand_supportedAppProtocolReq(stream, &exiDoc->supportedAppProtocolReq, xmlOut);
                exiDoc->supportedAppProtocolReq_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolReq>");
                break;
            case 1:
                
                strcat(xmlOut, "<{urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolRes>");
                error = decode_appHand_supportedAppProtocolRes(stream, &exiDoc->supportedAppProtocolRes, xmlOut);
                exiDoc->supportedAppProtocolRes_isUsed = 1u;
                strcat(xmlOut, "</{urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolRes>");
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


