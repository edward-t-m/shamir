/**
 * bip39.h
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

#include <stdlib.h>
#include <stdint.h>
#include "sha256.h"


/** Usable entropy lengths. Some are invalid under bip39 spec - "The allowed size of ENT is 128-256 bits" */
#define BIP39_ENTROPY_LEN_32 4
#define BIP39_ENTROPY_LEN_64 8
#define BIP39_ENTROPY_LEN_96 12
#define BIP39_ENTROPY_LEN_128 16
#define BIP39_ENTROPY_LEN_160 20
#define BIP39_ENTROPY_LEN_192 24
#define BIP39_ENTROPY_LEN_224 28
#define BIP39_ENTROPY_LEN_256 32
#define BIP39_ENTROPY_LEN_288 36
#define BIP39_ENTROPY_LEN_320 40
#define BIP39_ENTROPY_LEN_MAX (BIP39_ENTROPY_LEN_320 + sizeof(unsigned char) * 2)

size_t len_to_mask(size_t len);
size_t bip39_checksum(const unsigned char *bytes_in, size_t len_in, size_t mask);
// int checksum_ok(const unsigned char *bytes, size_t idx, size_t mask);


