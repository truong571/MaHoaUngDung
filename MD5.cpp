﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
using namespace std;

const uint32_t k[64] = {
0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

const uint32_t r[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                      5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

uint32_t leftRotate(uint32_t x, uint32_t c) {
    return ((x) << (c)) | ((x) >> (32 - (c)));
}


void uint32ToBytes(uint32_t value, uint8_t* bytes)
{
    bytes[0] = (uint8_t)value;
    bytes[1] = (uint8_t)(value >> 8);
    bytes[2] = (uint8_t)(value >> 16);
    bytes[3] = (uint8_t)(value >> 24);
}

uint32_t bytesToUint32(const uint8_t* bytes)
{
    return (uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8) | ((uint32_t)bytes[2] << 16) | ((uint32_t)bytes[3] << 24);
}

void MD5(const uint8_t* originMsg, uint64_t originMsgLen, uint8_t* digest) 
{
    uint32_t h0, h1, h2, h3;
    uint8_t* newMsg = NULL;
    uint64_t newMsgLen = originMsgLen;
    size_t offset;
    uint32_t w[16];
    
    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;

    //Pre-processing:
    newMsgLen = originMsgLen;
    do {
        newMsgLen++;
    } while (newMsgLen % 64 != 56); //newMsgLen % (512 / 8) != 448 / 8

    newMsg = (uint8_t*)malloc(newMsgLen + 8);
    if (newMsg != NULL) {
        memcpy(newMsg, originMsg, originMsgLen);
        newMsg[originMsgLen] = 0x80; // append the byte "10000000"
        for (offset = originMsgLen + 1; offset < newMsgLen; offset++)
        {
            newMsg[offset] = 0; // append "0" bits
        }
        //append 4 high bytes to the newMsg
        uint32ToBytes(originMsgLen * 8, newMsg + newMsgLen);
        // originMsgLen>>29 == originMsgLen*8>>32
        //append 4 low byte to the the newMsg
        uint32ToBytes(originMsgLen >> 29, newMsg + newMsgLen + 4);
        // Process the message
        for (offset = 0; offset < newMsgLen; offset += (512 / 8)) 
        {
            uint32_t a, b, c, d, i, f, g, temp;
            for (i = 0; i < 16; i++)
            {
                w[i] = bytesToUint32(newMsg + offset + i * 4);
            }

            a = h0;
            b = h1;
            c = h2;
            d = h3;

            for (i = 0; i < 64; i++) {

                if (i < 16) {
                    f = (b & c) | ((~b) & d);
                    g = i;
                }
                else if (i < 32) {
                    f = (d & b) | ((~d) & c);
                    g = (5 * i + 1) % 16;
                }
                else if (i < 48) {
                    f = b ^ c ^ d;
                    g = (3 * i + 5) % 16;
                }
                else {
                    f = c ^ (b | (~d));
                    g = (7 * i) % 16;
                }

                temp = d;
                d = c;
                c = b;
                b = b + leftRotate((a + f + k[i] + w[g]), r[i]);
                a = temp;
            }

            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
        }

        free(newMsg);

        uint32ToBytes(h0, digest);
        uint32ToBytes(h1, digest + 4);
        uint32ToBytes(h2, digest + 8);
        uint32ToBytes(h3, digest + 12);
    }
    
}
int main() {
    const char* msg;
    uint64_t len;
    int i;
    uint8_t result[16];
    msg = "fit.hcmus";
    len = strlen(msg);
    MD5((uint8_t*)msg, len, result);
    // display result
    for (i = 0; i < 16; i++)
        printf("%.2x", result[i]);
    cout << endl;
    return 0;
}