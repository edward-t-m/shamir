/**
 * funcs.h
 *
 *  Created on: 7th Jan, 2018, most of it copy-pasta from Ryan Casey's
 *      https://github.com/ryepdx/keyphrase/blob/master/funcs.c
 *
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Affero General Public License v3.0
 *
 * Permissions of this strongest copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights. When a modified version is used to provide a service over a network, the complete source code of the modified version must be made available.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *
 */

#include "constants.h"

int is_hex(char arg[]);
int get_word(char buffer[], char hex_chunk[], char *wordlist[]);
int is_hex_padded(char hex_string[]);
int normalized_hex_string_length(char hex_string[]);
int normalize_hex_string(char buffer[], char hex_string[]);
int max_phrase_length(char hex_string[]);
int get_phrase(char buffer[], char hex_string[], char *wordlist[]);
int index_of_word(char *word, char *wordlist[], int numwords);
int hex_chunk(char buffer[HEX_CHUNK_LENGTH+1], int source);
int binary_chunk(char buffer[HEX_CHUNK_LENGTH+1], int source, int length);
int wordcount(char phrase[]);
int key_length(char phrase[]);
int get_key(char key[], char phrase[], char* wordlist[], int wordlist_size, char err_msg[]);
char* get_params_from_share(int *threshold, int *order, char mnemonic[], char *wordlist[], int wordlist_size, char err_msg[], char shamir39token[]);
void get_binary_from_mnemonic(char binary[], char mnemonic[], char *wordlist[], int wordlist_size, char err_msg[]);
void get_mnemonic_from_binary(char binary[], char mnemonic[], char *wordlist[]);
void paramsToBinaryStr(int t, int order, char binary[BINARY_CHUNK_LENGTH+1]);
char* paramsToMnemonic(int t, int order, char mnemonic[], char* wordlist[]);
void disuniteIntoParams(int combinedparamint, int *threshold, int *order);
int loadwordlist(char *wordlist[]);
