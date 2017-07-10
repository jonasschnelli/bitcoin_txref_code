Confirmed Transaction Reference Codes
=====
[![Build Status](https://travis-ci.org/jonasschnelli/bitcoin_txref_code.svg?branch=master)](https://travis-ci.org/jonasschnelli/bitcoin_txref_code)  [![Coverage Status](https://coveralls.io/repos/jonasschnelli/bitcoin_txref_code/badge.svg?branch=master&service=github)](https://coveralls.io/github/jonasschnelli/bitcoin_txref_code?branch=master)

Simple C implementation for ctxref codes after BIP XXXX

Build steps
-----------

Object code:

    $  gcc -O3 -c txref_code.c segwit_addr.c

Tests:

    $ gcc -O3 txref_code.c segwit_addr.c tests.c -o test

Example:

    /* ENCODE */
    char encoded_txref[32]; //buffer should be at least strlen(hrp) + 19 + 1(0 byte)
    char *hrp = "tx"; //mainnet
    
    // now encode for height 100 and pos 100
    int res = btc_txref_encode(encoded_txref, hrp, TXREF_MAGIC_BTC_MAINNET, 100, 100);
    printf("%s\n", encoded_txref);
    
    /* DECODE */
    int height;
    int pos;
    char hrpbuf[strlen(encoded_txref)];
    char magic;
    res = btc_txref_decode(encoded_txref, hrpbuf, &magic, &height, &pos);