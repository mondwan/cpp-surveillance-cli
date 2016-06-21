//
//  "$Id: Security.h 482 2009-01-06 07:03:43Z liwj $"
//
//  Copyright (c)2008-2010, ZheJiang XuanChuang Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __SECURITY_H__
#define __SECURITY_H__

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/// 3DES加密算法
/// pResult 加密后的缓存位置 
///		缓存的长度 >= ((iOrigLen+7)/8)*8 
///		即比iOrigLen大，且是8的倍数的最少整数
///	\param	pResult可以为pOrig，但是会覆盖原有东西
///	\param	pOrig 待加密的缓存位置
/// \param  iOrigLen 待加密缓存长度
/// \param  pKey 密钥 超过16字节后只取前16字节
/// \param  iKeylen 密钥长度
/// \return : true 成功, false 失败
bool DesEncrypt(char *pResult, char *pOrig, long iOrigLen, const char *pKey, int iKeylen);

/// 3DES解密算法
/// \param [out] Result 解密后的缓存位置
/// \param [in]pOrig 待解密的缓存位置
/// \param  iOrigLen 待解密缓存长度
/// \param  pKey 密钥
/// \param  iKeylen 密钥长度
/// \return : true 成功, false 失败
bool DesDecrypt(char *pResult, char *pOrig, long iOrigLen, const char *pKey, int iKeylen);

/// MD5加密算法
/// \param [out] strOutput 加密后的秘文
/// \param [in] strInput 要加密的秘文
void MD5Encrypt(signed char *strOutput, unsigned char *strInput);

#endif
