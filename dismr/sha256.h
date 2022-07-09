#include<stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

#pragma once
#include <stddef.h>

/*********************************************************************
* Filename:   sha256.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding SHA1 implementation.
*********************************************************************/

#ifndef SHA256_H
#define SHA256_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 unsigned char digest

/**************************** DATA TYPES ****************************/
            // 8-bit unsigned char          // 32-bit unsigned int, change to "long" for 16-bit machines

typedef struct {
	unsigned char data[64];
	unsigned int datalen;
	unsigned long long bitlen;
	unsigned int state[8];
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const unsigned char data[], size_t len);
void sha256_final(SHA256_CTX *ctx, unsigned char hash[]);

#endif   // SHA256_H
/*�����ļ�sha256��ϣֵ
 *inparam		pfile			Դ�ļ�
 *outparam		psha256_value	��Ź�ϣֵ��ָ��
 *inparam		nvalue_length	��ϣֵָ��ĳ���  ����32
 * */

int sha256_calcufile(const wchar_t* pfile, unsigned char* psha256_value, int nvalue_length);

/*���sha256��ϣֵ
 *outparam		psha256_value	��Ź�ϣֵ��ָ��
 *inparam		nvalue_length	��ϣֵָ��ĳ���
 * */
void sha256_put(unsigned char* psha256_value, int nlength);
