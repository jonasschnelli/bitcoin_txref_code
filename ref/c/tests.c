#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "segwit_addr.h"
#include "txref_code.h"


struct test_vector {
    const char* txref_encoded;
    int blockheight;
    int pos;
    int enc_fail;
    int dec_fail;
};

static struct test_vector test_vectors[] = {
    {
        "tx1tjk0u5ngtusvf6",
        466793,
        2205,
        0,0
    },
    {
        "tx1tjk0u5ngtusvf7", /* must error correct */
        466793,
        2205,
        1,0
    },
    {
        "tx1tqqqqqqq74hej5",
        0,
        0,
        0,0
    },
    {
        "tx1tjk0u5ngtusvf7",
        0,
        0,
        1,1 /* enc & dec must fail */
    },
    {
        "tx1t7lllrarry7jyf",
        2097151, /* last valid block height with current enc/dec version is 0x1FFFFF*/
        1000,
        0,0
    },
    {
        "tx1tqqqqqqq74hej5",
        2097152, /* invalid height */
        1000,
        1,1
    },
    {
        "tx1t7llllllgey7ez",
        2097151, /* last valid block height with current enc/dec version is 0x1FFFFF*/
        8191, /* last valid tx pos is 0x1FFF */
        0,0
    },
    {
        "tx1t7llllllgey7ez",
        2097151, /* last valid block height with current enc/dec version is 0x1FFFFF*/
        8192, /* invalid tx pos */
        1,1
    },
};

int main(void) {
    int fail = 0;

    for (size_t i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
        char encoded_txref[20] = {};
        char magic_in = 0xb;
        int res = btc_txref_encode(encoded_txref, magic_in, test_vectors[i].blockheight, test_vectors[i].pos);
        if (strcmp(test_vectors[i].txref_encoded, encoded_txref) != 0 && !test_vectors[i].enc_fail) {
            fail++;
        }
        if (test_vectors[i].enc_fail) {
            continue;
        }

        char magic;
        int bh_check;
        int pos_check;
        res = btc_txref_decode(encoded_txref, &magic, &bh_check, &pos_check);
        if (res!=1 && !test_vectors[i].dec_fail) {
            fail++;
        }
        if (test_vectors[i].pos != pos_check) {
            fail++;
        }
        if (test_vectors[i].blockheight != bh_check) {
            fail++;
        }
        if (magic != magic_in) {
            fail++;
        }
    }

    printf("%i failures\n", fail);
    return fail != 0;
}
