#ifndef CONSTANTS_INCLUDED
#define VERSION_COMPONENT "shamir39-p2"
#define WORDLENGTH 11 // longest word in BIP39 English list is 8. TODO check other languages + MBCS
#define PARAMETER_BITS_PER_WORD 5
#define THRESHOLD_PARAMETER_MASK 0x3e0
#define ORDER_PARAMETER_MASK 0x1f
#define MAX_MNEMONIC_WORDS 24 // TODO allow for Monero 25-word seeds
#define MAX_SHARES 31 // TODO make this implementation handle more shares per the spec
#define NUMWORDS 2048
#define HEX_CHUNK_LENGTH 4
#define HEX_CHUNK_FORMAT "%04x"
#define BINARY_CHUNK_LENGTH 11
#define ERR_MSG_LENGTH 64
#define HAVE_LITTLE_ENDIAN 1  // for Intel x86 architectures. TODO binary_chunk assumes little endian
#define CONSTANTS_INCLUDED
#endif
#ifndef WORDFILE
#define WORDFILE "english.txt"
#endif
