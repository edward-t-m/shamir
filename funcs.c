/**
 * funcs.c
 *
 *  Created on: 7th Jan, 2018 most of it copy-pasta from Ryan Casey's
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

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "funcs.h"

int loadwordlist(char *wordlist[]) {

    FILE *fp = fopen(WORDFILE, "r");

    if (!fp) {
       printf("Could not find wordlist: '%s' is missing!\n", WORDFILE);
       return 1;
    }


	for(int i=0; i < NUMWORDS; i++) {
	    wordlist[i] = malloc(WORDLENGTH + 1);
	    fgets(wordlist[i], WORDLENGTH + 1, fp);
	    for (int j=strlen(wordlist[i])-1; j>=0 && (wordlist[i][j] == '\n' || wordlist[i][j]=='\r'); j--) {
	        wordlist[i][j]='\0';
	    }
	}

	return 0;
}


int is_hex_padded(char hex[]) {
    int length = strlen(hex);
    return (length >= 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'));
}

int normalized_hex_string_length(char hex_string[]) {
    int length = strlen(hex_string);
    
    if (is_hex_padded(hex_string)) {
        length -= 2;
    }

    if (length % HEX_CHUNK_LENGTH != 0) {
        length = (length / HEX_CHUNK_LENGTH + 1) * HEX_CHUNK_LENGTH;
    }

    return length;
}

int normalize_hex_string(char buffer[], char hex_string[]) {
    memset(buffer, 0, sizeof(*buffer));

    if (is_hex_padded(hex_string)) {
        hex_string += 2;
    }
    strcpy(buffer, hex_string);
    
    int length = strlen(hex_string);
    int normalized_length = normalized_hex_string_length(hex_string);
    int gap = (normalized_length - length);

    for (int i=normalized_length; i > 0 && gap; i--) {
        buffer[i] = buffer[i - gap];
    }
    for (int i=0; i < gap; i++) {
        buffer[i] = '0';
    }
    buffer[normalized_length] = '\0';

    return 0;
}

int is_hex(char arg[]) {
    int index = 0;
    int result = 1;
    int length = strlen(arg);

    if (length == 0) {
        return 0;

    } else if (is_hex_padded(arg)) {
        index = 2;
    }

    while (index < length && result) {
        result = isxdigit(arg[index]);
        index += 1;
    }

    return result;
}

int get_word(char buffer[], char hex_chunk[], char *wordlist[]) {
    strcpy(buffer, wordlist[(int) strtol(hex_chunk, 0, 16)]);
    return 0;
}

int max_phrase_length(char hex_string[]) {
    int length = normalized_hex_string_length(hex_string);
    return (length / HEX_CHUNK_LENGTH) * (WORDLENGTH + 1) - 1;
}

int get_phrase(char buffer[], char hex_string[], char *wordlist[]) {
    memset(buffer, 0, sizeof(*buffer));

    int length = strlen(hex_string);
    char hex_quad[4];
    char word[11];

    for (int i=0; i < length / 4; i++) {
        strncpy(hex_quad, hex_string + (i*4), 4);

        if (i != 0) {
            strcat(buffer, " ");
        }
        get_word(word, hex_quad, wordlist);
        strcat(buffer, word);
    }

    return 0;
}


int wordlist_cmp(const void *s1, const void *s2) {
    const char *key = s1;
    const char * const *arg = s2;
    return strcmp(key, *arg);
}

int index_of_word(char *word, char *wordlist[], int numwords) {
    char **ptr = (char**) bsearch(word, wordlist, numwords, sizeof(char *), wordlist_cmp);
    return ptr ? (ptr - wordlist) : -1;
}

int hex_chunk(char buffer[HEX_CHUNK_LENGTH+1], int source) {
    sprintf(buffer, HEX_CHUNK_FORMAT, source);
    return 0;
}

/*
 * assumes little endian. works on buffer of length BINARY_CHUNK_LENGTH+1
 */
int binary_chunk(char buffer[], int source, int length) {
	unsigned char byte;
	unsigned char *b = (unsigned char*) &source;
	size_t const size = sizeof(source);
	int bit = size*8;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--,bit--)
        {
            if (bit <= length)
            {
                byte = (b[i] >> j) & 1;
            	buffer += sprintf(buffer, "%u", byte);
            }
        }
    }

//    printf("binary_chunk from source %i, resultant chunk: %s\n", source, buffer);

    return 0;
}


int wordcount(char phrase[]) {
    int count = 0;
    int length = strlen(phrase);
    int in_word = 0;

    for (int i=0; i < length; i++) {
        if (phrase[i] == '\t' || phrase[i] == '\n' || phrase[i] == ' ' || phrase[i] == '\r' || phrase[i] == '\0') {
            count += in_word;
            in_word = 0;
        } else {
            in_word = 1;
        }
    }
    count += in_word;

    return count;
}

int key_length(char phrase[]) {
    return wordcount(phrase) * HEX_CHUNK_LENGTH;
}

int get_key(char key[], char phrase[], char *wordlist[], int wordlist_size, char err_msg[]) {
    int length = strlen(phrase);
    int char_index = 0;
    int word_index;
    int on_whitespace = 0;
    char word[WORDLENGTH+1];
    char chunk[HEX_CHUNK_LENGTH+1];
    memset(word, 0, sizeof(*word));
    memset(chunk, 0, sizeof(*chunk));
    memset(key, 0, sizeof(*key));
    memset(err_msg, 0, sizeof(*err_msg));

    for (int i=0; i < length; i++) {
        on_whitespace = (phrase[i] == '\t' || phrase[i] == '\n' || phrase[i] == ' ' || phrase[i] == '\r' || phrase[i] == '\0');

        if (!on_whitespace) {
            word[char_index] = phrase[i];
            char_index++;
        }
        
        if (char_index && (on_whitespace || char_index == WORDLENGTH || i+1 == length)) {
            word[char_index] = '\0';
            word_index = index_of_word(word, wordlist, wordlist_size);

            if (word_index == -1) {
                sprintf(err_msg, "Could not find '%s' in the wordlist!", word);
                return 1;
            }

            hex_chunk(chunk, word_index);
            strcat(key, chunk);

            memset(word, 0, sizeof(*word));
            memset(chunk, 0, sizeof(*chunk));
            char_index = 0;
            on_whitespace = 0;
        }
    }

    return 0;
}

void get_binary_from_mnemonic(char binary[], char mnemonic[], char *wordlist[], int wordlist_size, char err_msg[]) {
    int length = strlen(mnemonic);
    int char_index = 0;
    int word_index;
    int on_whitespace = 0;
    char word[WORDLENGTH+1];
    char chunk[HEX_CHUNK_LENGTH+1];
    memset(word, 0, sizeof(*word));
    memset(chunk, 0, sizeof(*chunk));
    memset(binary, 0, sizeof(*binary));
    memset(err_msg, 0, sizeof(*err_msg));


    for (int i=0; i < length; i++) {
        on_whitespace = (mnemonic[i] == '\t' || mnemonic[i] == '\n' || mnemonic[i] == ' ' || mnemonic[i] == '\r' || mnemonic[i] == '\0');

        if (!on_whitespace) {
            word[char_index] = mnemonic[i];
            char_index++;
        }

        if (char_index && (on_whitespace || char_index == WORDLENGTH || i+1 == length)) {
        	word[char_index] = '\0';  // null terminate this word

        	word_index = index_of_word(word, wordlist, wordlist_size);  // what index in the wordlist is this word
            if (word_index == -1) {
                sprintf(err_msg, "'%s' is not a valid mnemonic word. Check wordlist/wordlist language", word);
                return;
            }

            binary_chunk(chunk, word_index, BINARY_CHUNK_LENGTH);
            strcat(binary, chunk);

            memset(word, 0, sizeof(*word));
            memset(chunk, 0, sizeof(*chunk));
            char_index = 0;
            on_whitespace = 0;
        }

    }

    return;
}

void get_mnemonic_from_binary(char binary[], char mnemonic[], char *wordlist[]) {
    int length = strlen(binary);
    char chunk[BINARY_CHUNK_LENGTH+1];
    memset(mnemonic, 0, sizeof(*mnemonic));

    for (int i=0; i < length / BINARY_CHUNK_LENGTH; i++) {
        strncpy(chunk, binary + (i*BINARY_CHUNK_LENGTH), BINARY_CHUNK_LENGTH);

        if (i != 0) {
            strcat(mnemonic, " ");
        }

        strcat(mnemonic, wordlist[(int) strtol(chunk, 0, 2)]);
    }
}

/**
 * Encode both number of shares and their order with mnemonic words, per shamir39 spec
 *
 * Builds the second component which encodes the parameters of
 * Shares Required (M), called -t threshold in original ssss implementation,
 * and Share Ordering (O), which was just a numerical prefix in original ssss implementation
 *
 * TODO handle > 31 shares (ie parameters span across multiple mnemonic words)
 */
void paramsToBinaryStr(int t, int order, char binary[BINARY_CHUNK_LENGTH+1]) {
	// int moreWords = 1 << (BINARY_CHUNK_LENGTH-1);  // TODO finish handling of > 31 shares
    char chunk[BINARY_CHUNK_LENGTH+1];

    memset(binary, 0, sizeof(*binary));
    memset(chunk, 0, sizeof(*chunk));

    *binary = '0';  // leading zero means < 32 shares.

    binary_chunk(chunk, t, BINARY_CHUNK_LENGTH);
    strncpy(binary+1,chunk+6,5);

    binary_chunk(chunk, order, BINARY_CHUNK_LENGTH);
    strncpy(binary+6,chunk+6,5);

    return;

    /*  TODO finish handling of > 31 shares
	for (int i = t, i >= 0, i--)
	{
		binary
		if ( i > 31 )
			x = x & moreWords;
	}
 	 */
}

char* paramsToMnemonic(int t, int order, char mnemonic[], char* wordlist[])
{
    char binary[BINARY_CHUNK_LENGTH+1];
    paramsToBinaryStr(t, order, binary);
    get_mnemonic_from_binary(binary, mnemonic, wordlist);

    return mnemonic;
}

/**
 * Return offset to the start of the mnemonic string (ie after the parameter words). Offset of zero means an error
 */
char* get_params_from_share(int *threshold, int *order, char mnemonic[], char *wordlist[], int wordlist_size, char err_msg[], char shamir39token[]) {
    int length = strlen(mnemonic);
    int char_index = 0;
    int word_index;
    int next_word_is_parameter = 0, nthword = 0;
    int on_whitespace = 0;
    char word[WORDLENGTH+1];
    char chunk[HEX_CHUNK_LENGTH+1];

    memset(word, 0, sizeof(*word));
    memset(chunk, 0, sizeof(*chunk));
    memset(err_msg, 0, sizeof(*err_msg));
	*threshold = 0; *order = 0;


    for (int i=0; i < length; i++) {

        on_whitespace = (mnemonic[i] == '\t' || mnemonic[i] == '\n' || mnemonic[i] == ' ' || mnemonic[i] == '\r' || mnemonic[i] == '\0');

        if (!on_whitespace) {
            word[char_index] = mnemonic[i];
            char_index++;
        }

        if (char_index && (on_whitespace || char_index == WORDLENGTH+1 || i+1 == length)) {
            word[char_index] = '\0';  // null terminate this word
            nthword++;

        	if (nthword == 1) // if we're at first word of the shamir share...
        	{
        		next_word_is_parameter = 1;
                char_index = 0;
                on_whitespace = 0;
        		continue;  // TODO add validation of token...for now we'll just skip it
        		/*
        		if ( !strncmp (buf,  ( opt_token ? opt_token : VERSION_COMPONENT ), tokenlen) )
        			fatal("First word of share must be \"%s\"", ( opt_token ? opt_token : VERSION_COMPONENT ) );
				*/
        	}

        	if ( next_word_is_parameter ) {
        		word_index = index_of_word(word, wordlist, wordlist_size);  // what index in the wordlist is this parameter-word
                if (word_index == -1) {
                    sprintf(err_msg, "'%s' is not a valid parameter word. Check wordlist/wordlist language", word);
                    return 0;
                }
        		next_word_is_parameter = word_index & 0x400;  // bit 11 flag is 1 (true) only if more parameter words follow
        	}

			// add the relevant bits from the current word to the corresponding parameter
			*threshold+=((word_index & THRESHOLD_PARAMETER_MASK) >> PARAMETER_BITS_PER_WORD);
			*order    +=(word_index & ORDER_PARAMETER_MASK);

    		if (next_word_is_parameter)
    		{
    			*threshold	<<= PARAMETER_BITS_PER_WORD;	// left shift parameter bits ready for the next parameter word
    			*order		<<= PARAMETER_BITS_PER_WORD;	// left shift parameter bits ready for the next parameter word
    		}
    		else
    		{
    			return &(mnemonic[i+1]);
    		}
        }
    }

    sprintf(err_msg, "Invalid parameter words or truncated mnemonic");
    return 0;  // we ran out of mnemonic string before getting final parameter word
}

