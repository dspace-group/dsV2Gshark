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
  * @file exi_basetypes.c
  * @brief Description goes here
  *
  **/

#include "exi_error_codes.h"
#include "exi_basetypes.h"
#include "exi_bitstream.h"


/*****************************************************************************
 * interface functions
 *****************************************************************************/
int exi_basetypes_convert_to_unsigned(exi_unsigned_t* exi_unsigned, uint32_t value, size_t max_octets)
{
    exi_unsigned->octets_count = 0;
    uint8_t* current_octet = exi_unsigned->octets;
    uint32_t dummy = value;

    for (size_t n = 0; n < EXI_BASETYPES_UINT32_MAX_OCTETS; n++)
    {
        exi_unsigned->octets_count++;
        *current_octet = (uint8_t)(dummy & EXI_BASETYPES_OCTET_SEQ_VALUE_MASK);

        dummy = dummy >> 7u;
        if (dummy == 0)
        {
            break;
        }

        *current_octet |= EXI_BASETYPES_OCTET_SEQ_FLAG_MASK;
        current_octet++;
    }

    return (exi_unsigned->octets_count <= max_octets) ? EXI_ERROR__NO_ERROR : EXI_ERROR__OCTET_COUNT_LARGER_THAN_TYPE_SUPPORTS;
}

int exi_basetypes_convert_64_to_unsigned(exi_unsigned_t* exi_unsigned, uint64_t value)
{
    exi_unsigned->octets_count = 0;
    uint8_t* current_octet = exi_unsigned->octets;
    uint64_t dummy = value;

    for (size_t n = 0; n < EXI_BASETYPES_UINT64_MAX_OCTETS; n++)
    {
        exi_unsigned->octets_count++;
        *current_octet = (uint8_t)(dummy & EXI_BASETYPES_OCTET_SEQ_VALUE_MASK);

        dummy = dummy >> 7u;
        if (dummy == 0)
        {
            break;
        }

        *current_octet |= EXI_BASETYPES_OCTET_SEQ_FLAG_MASK;
        current_octet++;
    }

    return (exi_unsigned->octets_count <= EXI_BASETYPES_UINT64_MAX_OCTETS) ? EXI_ERROR__NO_ERROR : EXI_ERROR__OCTET_COUNT_LARGER_THAN_TYPE_SUPPORTS;
}

int exi_basetypes_convert_to_signed(exi_signed_t* exi_signed, int32_t value, size_t max_octets)
{
    if (value < 0) {
        exi_signed->is_negative = 1;
        return exi_basetypes_convert_to_unsigned(&exi_signed->data, -value, max_octets);
    }
    exi_signed->is_negative = 0;
    return exi_basetypes_convert_to_unsigned(&exi_signed->data, value, max_octets);
}

int exi_basetypes_convert_64_to_signed(exi_signed_t* exi_signed, int64_t value)
{
    if (value < 0) {
        exi_signed->is_negative = 1;
        return exi_basetypes_convert_64_to_unsigned(&exi_signed->data, -value);
    }
    exi_signed->is_negative = 0;
    return exi_basetypes_convert_64_to_unsigned(&exi_signed->data, value);
}

int exi_basetypes_convert_from_unsigned(const exi_unsigned_t* exi_unsigned, uint32_t* value, size_t max_octets)
{
    if (exi_unsigned->octets_count > max_octets)
    {
        return EXI_ERROR__OCTET_COUNT_LARGER_THAN_TYPE_SUPPORTS;
    }

    const uint8_t* current_octet = exi_unsigned->octets;
    *value = 0;

    for (size_t n = 0; n < exi_unsigned->octets_count; n++)
    {
        *value = *value + ((uint32_t)(*current_octet & EXI_BASETYPES_OCTET_SEQ_VALUE_MASK) << (n * 7));

        current_octet++;
    }

    return EXI_ERROR__NO_ERROR;
}

int exi_basetypes_convert_64_from_unsigned(const exi_unsigned_t* exi_unsigned, uint64_t* value)
{
    if (exi_unsigned->octets_count > EXI_BASETYPES_UINT64_MAX_OCTETS)
    {
        return EXI_ERROR__OCTET_COUNT_LARGER_THAN_TYPE_SUPPORTS;
    }

    const uint8_t* current_octet = exi_unsigned->octets;
    *value = 0;

    for (size_t n = 0; n < exi_unsigned->octets_count; n++)
    {
        *value = *value + ((uint64_t)(*current_octet & EXI_BASETYPES_OCTET_SEQ_VALUE_MASK) << (n * 7));

        current_octet++;
    }

    return EXI_ERROR__NO_ERROR;
}

int exi_basetypes_convert_from_signed(const exi_signed_t* exi_signed, int32_t* value, size_t max_octets)
{
    uint32_t uValue = 0;
    int res = exi_basetypes_convert_from_unsigned(&exi_signed->data, &uValue, max_octets);
    *value = (exi_signed->is_negative == 0) ? uValue : -uValue;
    return res;
}

int exi_basetypes_convert_64_from_signed(const exi_signed_t* exi_signed, int64_t* value)
{
    uint64_t uValue = 0;
    int res = exi_basetypes_convert_64_from_unsigned(&exi_signed->data, &uValue);
    *value = (exi_signed->is_negative == 0) ? uValue : -uValue;
    return res;
}

int exi_basetypes_convert_bytes_from_unsigned(const exi_unsigned_t* exi_unsigned, uint8_t* data, size_t* data_len, size_t data_size)
{    
    const uint8_t* current_octet = exi_unsigned->octets;
    uint16_t temp = 0;
    *data_len = 0;
    size_t total_offset = 0;

    for (size_t n = 0; n < exi_unsigned->octets_count; n++) {
        temp = temp + ((uint16_t)(*current_octet & EXI_BASETYPES_OCTET_SEQ_VALUE_MASK) << (total_offset));
        total_offset += 7;
        if (total_offset >= 8) {
            if (data_size == *data_len) {
                return -1;
            }
            total_offset -= 8;
            data[(*data_len)++] = temp & 0xFF;
            temp >>= 8;
        }
        current_octet++;
    }
    if (total_offset != 0) {
        if (data_size == *data_len) {
            return -1;
        }
        data[(*data_len)++] = temp & 0xFF;
    }
    return 0;
}

int exi_basetypes_convert_bytes_to_unsigned(exi_unsigned_t* exi_unsigned, const uint8_t* data, size_t data_len)
{
    uint8_t *current_octet = &exi_unsigned->octets[0];
    uint16_t dummy = 0;
    uint8_t dummy_count = 0;

    for (size_t n = 0; n != data_len; n++, current_octet++) {
        if (dummy_count <= 8) {
            dummy = dummy | ((data[n]) << dummy_count);
            dummy_count += 8;
        }
        exi_unsigned->octets_count++;
        *current_octet = (uint8_t)(dummy & EXI_BASETYPES_OCTET_SEQ_VALUE_MASK);

        dummy = dummy >> 7u;
        dummy_count -= 7;
        if (n == data_len) {
            break;
        }

        *current_octet |= EXI_BASETYPES_OCTET_SEQ_FLAG_MASK;
    }
    if (dummy_count > 0) {
        *(current_octet-1) |= EXI_BASETYPES_OCTET_SEQ_FLAG_MASK;
        exi_unsigned->octets_count++;
        *current_octet = (uint8_t)(dummy & EXI_BASETYPES_OCTET_SEQ_VALUE_MASK);
    }
    return 0;
}


