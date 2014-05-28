#!/usr/bin/env python
##############################################################################
#
# buildinc.py
#
##############################################################################


enc_table = [
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '-', '_'
]


#=============================================================================
def main( argv ):
    """ Script execution entry point """

    # start with a table of 256 integers
    table = [ 0 ] * 256

    # replace all integers from the encoding table
    for i in range( len( enc_table ) ):
        table[ ord( enc_table[ i ] ) ] = i

    # write the decoding table out to a new file
    out = open( 'dec_table.inc', 'wb' )

    for i in range( 256 ):
        if ( i % 8 ) == 0:
            out.write( '    ' )
        out.write( '0x%02X,' % table[ i ] )
        if ( ( i + 1 ) % 8 ) == 0:
            out.write( '\n' )
        else:
            out.write( ' ' )

    out.close()

    # write out the encoding table to a new file
    out = open( 'enc_table.inc', 'wb' )

    for i in range( len( enc_table ) ):
        if ( i % 8 ) == 0:
            out.write( '    ' )
        out.write( "'%s'," % enc_table[ i ] )
        if ( ( i + 1 ) % 8 ) == 0:
            out.write( '\n' )
        else:
            out.write( ' ' )

    out.close()

    # Return success.
    return 0

#=============================================================================
if __name__ == "__main__":
    import sys
    sys.exit( main( sys.argv ) )
