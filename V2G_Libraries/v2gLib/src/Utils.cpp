/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    Utils.cpp
 *
 *  @author
 *    ThorenG
 *
 *  @copyright
 *    Copyright 2024, dSPACE GmbH. All rights reserved.
 *    See LICENSE file
 *
 *<!-------------------------------------------------------------------------->*/
#include <sstream>
#include <iomanip>
#include <cstring>
#include <zlib.h>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#include <fcntl.h>
#include <io.h>
#define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#define SET_BINARY_MODE(file)
#endif

#include "Utils.h"

uint8_t *hex_str_to_uint8(const char *string)
{
    if (string == NULL)
        return NULL;

    size_t slength = strlen(string);
    if ((slength % 2) != 0) // must be even
        return NULL;

    size_t dlength = slength / 2;

    uint8_t *data = new uint8_t[dlength];

    std::memset(data, 0, dlength);

    size_t index = 0;
    while (index < slength)
    {
        char c = string[index];
        int value = 0;
        if (c >= '0' && c <= '9')
            value = (c - '0');
        else if (c >= 'A' && c <= 'F')
            value = (10 + (c - 'A'));
        else if (c >= 'a' && c <= 'f')
            value = (10 + (c - 'a'));
        else
            return NULL;

        data[(index / 2)] += value << (((index + 1) % 2) * 4);

        index++;
    }

    return data;
}

std::string uint8_to_hex_string(const uint8_t *v, const size_t s)
{
    std::stringstream ss;

    ss << std::hex << std::setfill('0');

    for (size_t i = 0; i < s; i++)
    {
        ss << std::hex << std::setw(2) << static_cast<int>(v[i]);
    }

    return ss.str();
}

char *unzip_data(uint8_t *zipped_data, uint16_t zipped_data_length, uint16_t max_unzipped_len)
{
    char *out_stream = new char[max_unzipped_len + 1];

    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;
    // setup the input and the decompressed output
    infstream.avail_in = static_cast<uInt>(zipped_data_length); // size of input
    infstream.next_in = reinterpret_cast<Bytef *>(zipped_data); // input char array
    infstream.avail_out = max_unzipped_len;                     // size of output
    infstream.next_out = reinterpret_cast<Bytef *>(out_stream); // output char array

    // decompression
    inflateInit(&infstream);
    int return_value = inflate(&infstream, Z_NO_FLUSH);
    if (return_value != Z_STREAM_END)
    {
        fprintf(stderr, "Failed to read the complete input stream.");
    }
    return_value = inflateEnd(&infstream);
    if (return_value != Z_OK)
    {
        fprintf(stderr, "Failed to clean up after decompression.");
    }
    out_stream[infstream.total_out] = '\0';

    return out_stream;
}