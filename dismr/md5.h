#pragma once
/*********************************************************************
* Filename:   md5.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding MD5 implementation.
*********************************************************************/

#ifndef MD5_H
#define MD5_H
/*************************** HEADER FILES ***************************/
#include <stddef.h>
#include <string>

/****************************** MACROS ******************************/
#define MD5_BLOCK_SIZE 16               // MD5 outputs a 16 unsigned char digest

/**************************** DATA TYPES ****************************/
         // 8-bit unsigned char             // 32-bit unsigned int, change to "long" for 16-bit machines

typedef struct {
	unsigned char data[64];
	unsigned int datalen;
	unsigned long long bitlen;
	unsigned int state[4];
} MD5_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void md5_init(MD5_CTX* ctx);
void md5_update(MD5_CTX* ctx, const unsigned char data[], size_t len);
void md5_final(MD5_CTX* ctx, unsigned char hash[]);
std::wstring md5_text(std::wstring text);
#endif   // MD5_H