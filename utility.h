/*
 * utility.h  : �u���O�N���C�A���g BloGolEe
 *      �e�탆�[�e�B���e�B�֐��Q �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  7 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/utility.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     07/03/12 18:35 Tsujimura543
 * utility.h �� .cpp �� .c �̗��҂��� include �ł���悤�ɏ�������
 * 
 * 3     07/03/12 18:31 Tsujimura543
 * selectBlog() �𓱓����A���t�@�N�^�����O
 * 
 * 2     07/03/12 15:37 Tsujimura543
 * (1) encodeParameter() �� decodeParameter() �� utility.{h,cpp} �ֈړ�
 * (2) ��L�ɑΉ����� freeParameter() ��ʓr�p��
 * 
 * 1     07/03/07 22:37 Tsujimura543
 * �V�K�쐬
 */

#ifndef __UTILITY_H__
#define __UTILITY_H__

#ifdef __cplusplus
CString
GetValueFromXML(
        const char *element,
        const char *src,
        const char *terminator,
        bool       needToConvert );

int
GetValueFromXML(
        const char *element,
        const char *src );

char *readXML( const char *filename );


void    decodeParameter(
            CString             &param,          // �ݒ��
            const unsigned char *encryptedString,// �ݒ肷�ׂ����e(�v�E����)
            const unsigned char *rsaString );    // RSA���Ή�������

void    encodeParameter(
            FILE          *fp,
            FILE          *gp,
            const char    *param,
            const char    *paramName,
            char          *key,
            unsigned char **rsaString,
            bool          &encrypted );

void    freeParameter( unsigned char *rsaString );
#endif

#ifdef __cplusplus
extern "C" {
#endif
int     selectBlog( BLOGINF *blogInfo, int numOfBlogs );
#ifdef __cplusplus
}
#endif

#endif  /* __UTILITY_H__ */
