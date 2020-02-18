/**
 * bip39.c
 *
 *  Created on: 15th Jan, 2018, most of it just copy-pasta from Elements libwally project
 *      https://github.com/ElementsProject/libwally-core
 *
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the BSD-MIT License
 *
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 *
 */

#include "bip39.h"
#include "sha256.h"

/* Convert an input entropy length to a mask for checksum bits. As it
 * returns 0 for bad lengths, it serves as a validation function too.
 */
size_t len_to_mask(size_t len)
{
    switch (len) {
    case BIP39_ENTROPY_LEN_32: return 0x80;
    case BIP39_ENTROPY_LEN_64: return 0xc0;
    case BIP39_ENTROPY_LEN_96: return 0xe0;
    case BIP39_ENTROPY_LEN_128: return 0xf0;
    case BIP39_ENTROPY_LEN_160: return 0xf8;
    case BIP39_ENTROPY_LEN_192: return 0xfc;
    case BIP39_ENTROPY_LEN_224: return 0xfe;
    case BIP39_ENTROPY_LEN_256: return 0xff;
    case BIP39_ENTROPY_LEN_288: return 0x80ff;
    case BIP39_ENTROPY_LEN_320: return 0xC0ff;
    }
    return 0;
}

/**
 *  Checksum length is entropy bits / 32. eg 320 bits / 32 = 10 bit checksum
 *  see https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki#generating-the-mnemonic
 */
size_t bip39_checksum(const unsigned char *bytes_in, size_t len_in, size_t mask)
{
    struct sha256 sha;
    size_t ret;

    // generate the sha256
    sha256(&sha, bytes_in, len_in);

    // the most we'll need is the leftmost 2 bytes, ie 16 bits
    ret = sha.u.u8[0] | (sha.u.u8[1] << 8);

    // return the specific bits required, as specified by the mask
    return ret & mask;
}

/*
int checksum_ok(const unsigned char *bytes, size_t idx, size_t mask)
{
    // The checksum is stored after the data to sum
    size_t calculated = bip39_checksum(bytes, idx, mask);
    size_t stored = bytes[idx];
    if (mask > 0xff)
        stored |= (bytes[idx + 1] << 8);
    return (stored & mask) == calculated;
}
*/
