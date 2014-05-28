
#include <stdint.h>
#include <stdio.h>

#include "rhash.h"

int main(
    int                 argc,
    char**              argv
) {

    #define STR_SIZE      ( 16 )

    static const uint64_t
                        enc_tests[] = {
        0x0000000000000000ULL,
        0x0000000000000001ULL,
        0x0000000000000010ULL,
        0x0000000000000100ULL,
        0x0000000000030000ULL,
        0x0000A00000000000ULL,
        0x000B000000000000ULL,
        0xFF00000000000000ULL,
        0xFFFFFFFFFFFFFFFFULL,
        0x1001001001001001ULL,
        0xAAAAAAAAAAAAAAAAULL,
        0x53A0E4C21F69BD78ULL,
    };
    static const unsigned char
                        enc_num = sizeof( enc_tests ) / sizeof( uint64_t );

    static const char*  dec_tests[] = {
        "A",
        "B",
        "Q",
        "AE",
        "AAAAAAAAA8P",
        "__________P",
        "BABABABABAB",
        "qqqqqqqqqqK",
        "41bafIM5gOF",
    };
    static const unsigned char
                        dec_num = sizeof( dec_tests ) / sizeof( char* );

    char                hash[ STR_SIZE ];
    uint64_t            id;
    int                 index;

    printf( "Testing rhash_encode()\n" );

    for( index = 0; index < enc_num; ++index ) {
        rhash_encode( hash, STR_SIZE, enc_tests[ index ] );
        printf( "    0x%016llX => %18s\n", enc_tests[ index ], hash );
    }

    printf( "Testing rhash_decode()\n" );

    for( index = 0; index < dec_num; ++index ) {
        rhash_decode( &id, dec_tests[ index ] );
        printf( "    %18s => 0x%016llX\n", dec_tests[ index ], id );
    }

    return 0;
}
