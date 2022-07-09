#include <assert.h>
#include <stdio.h>

/* For convenience, an 80-bit (5*16) key is expanded into 16 unsigned
   chars, each one of which should be between 0 and 31. This is the
   key specified in the exercise. */
unsigned char key[16] = {6,19,1,6,17,19,25,3,17,25,25,18,19,14,24,5};

/* This function corresponds to E_k in the instructions. You can see
   that the structure closely matches the definition. You might want
   to verify for yourself that the left argument of "%" will always be
   non-negative as a signed int, which ensures that the remainder will
   be computed appropriately, even though C's "%" has a different sign
   convention. */
unsigned char enc_byte(unsigned char b, unsigned char k) {
    assert(k >= 0 && k <= 31);
    if (b >= 0x41 && b <= 0x5A) {
	return 0x41 + ((b - 0x41 + k) % 26);
    } else if (b >= 0x61 && b <= 0x7A) {
	return 0x61 + ((b - 0x61 + k) % 26);
    } else {
	return b;
    }
}

/* This function corresponds to D_k. The computation of k2 as the
   inverse rotation amount is similar in spirit to "26 - k", but
   respects the range 0 .. 31 on both input and output without the "%"
   argument becoming negative. */
unsigned char dec_byte(unsigned char b, unsigned char k) {
    assert(k >= 0 && k <= 31);
    int k2 = (52 - k) % 26;
    return enc_byte(b, k2);
}

/* A 128-bit block is structured as 16 bytes. */
struct block {
    unsigned char b[16];
};

/* CCEA3 encryption of a 128-byte plaintext block into a 128-byte
   ciphertext block, using a byte-expanded key. */
void enc_block(struct block *plain_in, struct block *cipher_out,
	       unsigned char *key) {
    int i;
    for (i = 0; i < 16; i++) {
	cipher_out->b[i] = enc_byte(plain_in->b[i], key[i]);
    }
}

/* CCEA3 encryption of a 128-byte plaintext block into a 128-byte
   ciphertext block, using a byte-expanded key. */
void dec_block(struct block *cipher_in, struct block *plain_out,
	       unsigned char *key) {
    int i;
    for (i = 0; i < 16; i++) {
	plain_out->b[i] = dec_byte(cipher_in->b[i], key[i]);
    }
}

/* Copy the contents of block IN to block OUT */
void copy_block(struct block *in, struct block *out) {
    int i;
    for (i = 0; i < 16; i++) {
	out->b[i] = in->b[i];
    }
}

/* Compute the bitwise XOR of the blocks IN1 and IN2 in theb lock
   OUT */
void xor_blocks(struct block *in1, struct block *in2,
		struct block *out) {
    int i;
    for (i = 0; i < 16; i++) {
	out->b[i] = in1->b[i] ^ in2->b[i];
    }
}

/* Increment a block as if it were a 128-bit integer */
void incr_block(struct block *bp) {
    int i;
    for (i = 15; i >= 0; i--) {
	bp->b[i]++;
	if (bp->b[i] != 0) {
	    /* stop if no carry */
	    break;
	}
    }
}

/* echo -n "GALLIA EST OMNIS DIVISA IN PARTES TRES." | hd */

/*
00000000  47 41 4c 4c 49 41 20 45  53 54 20 4f 4d 4e 49 53  |GALLIA EST OMNIS|
00000010  20 44 49 56 49 53 41 20  49 4e 20 50 41 52 54 45  | DIVISA IN PARTE|
00000020  53 20 54 52 45 53 2e                              |S TRES.|
*/

/* With padding:
47 41 4c 4c 49 41 20 45  53 54 20 4f 4d 4e 49 53
20 44 49 56 49 53 41 20  49 4e 20 50 41 52 54 45
53 20 54 52 45 53 2e 09  09 09 09 09 09 09 09 09
*/

/* The exercise plaintext, divided into blocks and padded. */
struct block plaintext[3] =
    {{{0x47,0x41,0x4c,0x4c,0x49,0x41,0x20,0x45,
       0x53,0x54,0x20,0x4f,0x4d,0x4e,0x49,0x53}},
     {{0x20,0x44,0x49,0x56,0x49,0x53,0x41,0x20,
       0x49,0x4e,0x20,0x50,0x41,0x52,0x54,0x45}},
     {{0x53,0x20,0x54,0x52,0x45,0x53,0x2e,0x09,
       0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09}}};

/* The corresponding ciphertext should also be three blocks long. */
struct block ciphertext[3];

/* The initialization vector is the same size as a block. This is the
   one specified for the exercise. */
struct block iv =
    {{0x78,0x44,0x4f,0xa1,0x76,0x57,0x70,0xe5,
      0x47,0x54,0x72,0x52,0x4d,0x6e,0x49,0x71}};

/* A block of zeros may be useful for initialization */
struct block zero_block =
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

/* A plaintext of zeros may be useful for testing */
struct block zero_blocks[3] =
    {{{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
     {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
     {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}};


/* You might find it helpful to define other specific blocks or
   messages as part of an attack. */

/* Print one or more blocks as a sequence of hex bytes to the standard
   output */
void print_blocks(struct block *bp, int n) {
    int i, j;
    for (j = 0; j < n; j++) {
	for (i = 0; i < 16; i++) {
	    printf("%02x ", bp[j].b[i]);
	}
	putchar('\n');
    }
}

int rotation_amt[] = {6,19,1,6,17,19,25,3,17,25,25,18,19,14,24,5};


/* ECB mode encryption with CCEA3 */
void ccea3_ecb(struct block *plain, struct block *cipher,
	       int num_blocks, unsigned char *key) {
    for(int i = 0; i < 3; i++){
        enc_block(&(plaintext[i]), &(cipher[i]), key);
    }
}

/* CTR mode encryption with CCEA3 */
void ccea3_ctr(struct block *plain, struct block *cipher,
	       int num_blocks, unsigned char *key, struct block *iv) {
    for(int i = 0; i < 3; i++){
        struct block out;
        if(i == 0){
            enc_block(iv, &out, key);
        } else {

            enc_block(&(cipher[i-1]), &out, key);
        }

        xor_blocks(&out, &(plain[i]) ,&(cipher[i]));
    }
}

/* OFB mode encryption with CCEA3 */
void ccea3_ofb(struct block *plain, struct block *cipher,
	       int num_blocks, unsigned char *key, struct block *iv) {
    for(int i = 0; i < 3; i++){
        struct block out;
        enc_block(iv, &out, key);
    
        xor_blocks(&out, &(plain[i]) ,&(cipher[i]));

        incr_block(iv);
    }
}

/* CBC mode encryption with CCEA3 */
void ccea3_cbc(struct block *plain, struct block *cipher,
	       int num_blocks, unsigned char *key, struct block *iv) {
    for(int i = 0; i < 3; i++){
        struct block out;
        if(i == 0){
            xor_blocks(&(plaintext[i]), iv, &out);
        } else { xor_blocks(&(plaintext[i]), &(cipher[i-1]), &out); }

        enc_block(&out, &(cipher[i]), key);
    }
}

int main(int argc, char **argv) {
    printf("Plaintext:\n");
    print_blocks(plaintext, 3);
    printf("\n");
    printf("IV:\n");
    print_blocks(&iv, 1);
    printf("\n");
    

    printf("ECB ciphertext:\n");
    ccea3_ecb(plaintext, ciphertext, 3, key);
    print_blocks(ciphertext, 3);
    printf("\n");

    printf("CBC ciphertext:\n");
    ccea3_cbc(ciphertext, ciphertext, 3, key, &iv);
    print_blocks(ciphertext, 3);
    printf("\n");

    printf("OFB ciphertext:\n");
    ccea3_ofb(plaintext, ciphertext, 3, key, &iv);
    print_blocks(ciphertext, 3);
    printf("\n");

    printf("CTR ciphertext:\n");
    ccea3_ctr(plaintext, ciphertext, 3, key, &iv);
    print_blocks(ciphertext, 3);
    printf("\n");

#if 0
    /* You can use code like this to test the encryption modes after
       you have implemented them: */
    printf("ECB ciphertext:\n");
    ccea3_ecb(plaintext, ciphertext, 3, key);
    print_blocks(ciphertext, 3);
    printf("CTR ciphertext:\n");
    ccea3_ctr(plaintext, ciphertext, 3, key, &iv);
    print_blocks(ciphertext, 3);
    printf("OFB ciphertext:\n");
    ccea3_ofb(plaintext, ciphertext, 3, key, &iv);
    print_blocks(ciphertext, 3);
    printf("CBC ciphertext:\n");
    ccea3_cbc(ciphertext, ciphertext, 3, key, &iv);
    print_blocks(ciphertext, 3);
#endif

    /* You might use this to space for code testing an attack. */

    return 0;
}