/*********************************************************************
*
*   Resource Identifier Hashing
*
*   Reduces the length of ID strings when used in I/O and storage.
*
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include <stdint.h>
#include <string.h>

#include "rhash.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

#define BIT_MASK      ( 0x3F )      /* 6-bit mask                   */
#define BITS_PER_BYTE ( 6 )         /* bits stored per encoded byte */
#define NUM_SEXTETS   ( ( 64 / BITS_PER_BYTE ) + 1 )
                                    /* number of sextets in an ID   */

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

static const unsigned char
                        dec_table[] = {
                                    /* hash decoding table          */
#include "dec_table.inc"
};

static const char       enc_table[] = {
                                    /* hash encoding table          */
#include "enc_table.inc"
};

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/


/*********************************************************************
*
*   Decodes a resource hash (string) into its identifier value
*   (64-bit unsigned integer).
*
*********************************************************************/

rhash_result_t rhash_decode(
    uint64_t*           id,         /* user's identifier memory     */
    const char*         hash        /* user's hash to decode        */
) {                                 /* decode result                */

    /*------------------------------------------------------
    Local variables
    ------------------------------------------------------*/
    size_t              hash_length;/* length of hash string        */
    int                 sextet;     /* current sextet in decoder    */

    /*------------------------------------------------------
    Check usage.
    ------------------------------------------------------*/
    if( ( id == NULL ) || ( hash == NULL ) ) {
        return RHASH_PARAM;
    }

    /*------------------------------------------------------
    Find length of hash string.
    ------------------------------------------------------*/
    hash_length = strlen( hash );

    if( ( hash_length == 0 ) || ( hash_length > NUM_SEXTETS ) ) {
        return RHASH_STRING;
    }

    /*------------------------------------------------------
    Clear the integer.
    ------------------------------------------------------*/
    *id = 0;

    /*------------------------------------------------------
    Translate each character representation into the final
    identifier's value six bits at a time.
    ------------------------------------------------------*/
    for( sextet = ( hash_length - 1 ); sextet >= 0; --sextet ) {
        *id |= dec_table[ ( unsigned char ) hash[ sextet ] ];
        if( sextet > 0 ) {
            *id <<= BITS_PER_BYTE;
        }
    }

    /*------------------------------------------------------
    Decoded successfully.
    ------------------------------------------------------*/
    return RHASH_RES_OK;

}   /* rhash_decode() */


/*********************************************************************
*
*   Encodes a resource ID (64-bit unsigned integer) into a hash
*   (string).
*
*********************************************************************/

rhash_result_t rhash_encode(
    char*               hash,       /* user's memory to store hash  */
    size_t              size,       /* size (bytes) of user's memory*/
    uint64_t            id          /* 64-bit resource identifier   */
) {                                 /* encode result                */

    /*------------------------------------------------------
    Local variables
    ------------------------------------------------------*/
    int                 sextet;

    /*------------------------------------------------------
    Check usage.
    ------------------------------------------------------*/
    if( hash == NULL ) {
        return RHASH_PARAM;
    }

    /*------------------------------------------------------
    Check user's memory.
    ------------------------------------------------------*/
    if( size < ( NUM_SEXTETS + 1 ) ) {
        return RHASH_MEMORY;
    }

    /*------------------------------------------------------
    Clear enough of the string to ensure null termination.
    ------------------------------------------------------*/
    memset( hash, 0, ( NUM_SEXTETS + 1 ) );

    /*------------------------------------------------------
    Encode the identifier by representing every six bits
    with a (ASCII-readable) byte.
    ------------------------------------------------------*/
    for( sextet = 0; sextet < NUM_SEXTETS; ++sextet ) {
        hash[ sextet ] = enc_table[ id & BIT_MASK ];
        id >>= BITS_PER_BYTE;
        if( id == 0 ) {
            break;
        }
    }

    /*------------------------------------------------------
    Identifier successfully encoded.
    ------------------------------------------------------*/
    return RHASH_RES_OK;

}   /* rhash_encode() */
