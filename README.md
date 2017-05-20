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

