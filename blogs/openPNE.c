/*
 *  openPNE.c
 *      OpenPNE �����L���e����
 *
 *      written by H.Tsujimura    15 Sep 2006 / 2 Oct 2006
 *
 *      Copyright (c) 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�������������ė��p
 *
 * History:
 * $Log: /comm/blogolee/blogs/openPNE.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     07/12/05 23:34 Tsujimura543
 * makeMultiPartItem() �̈����ǉ��ɔ����C�������{
 * 
 * 4     07/03/06 0:08 Tsujimura543
 * �R�����g���C��
 * 
 * 3     07/03/06 0:06 Tsujimura543
 * �W���G���[�o�͂ɃG���[���b�Z�[�W���o�͂ł��Ȃ��ꍇ�́A���b�Z�[�W�{�b�N
 * �X���g���ăG���[���b�Z�[�W��\������悤�ɂ���
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 * 
 * 2     06/10/02 20:08 Tsujimura543
 * cocousagi.h ���C���N���[�h����悤�ɂ���
 * 
 * 1     06/10/02 18:27 Tsujimura543
 * cocousagi.c ���� OpenPNE ���L�̏����𕪗�
 */

#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "xmlRPC.h"
#include "multipart.h"
#include "../postArticle.h"


/*
 *  OpenPNE �������e����
 */

BOOL
loginOpenPNE( const char *username, const char *password, char *cookie )
{
    BOOL    ret = FALSE;
    char    request[BUFSIZ];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    sprintf( request,
             "m=pc&"
             "a=do_o_login&"
             "username=%s&"
             "password=%s&"
             "is_save=1",
             username, password );
    setUpReceiveBuffer( response, sz );
    http_postEx( "http://openpne.jp/", "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, "a=do_inc_page_header_logout" ) )
            ret = TRUE; // ���O�C������
    }
    free( response );

    return ( ret );
}

int
postOpenPNE( const char *title, const char *body, char *cookie )
{
    int     ret = 0;
    char    url[MAX_URLLENGTH];
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;
    char    dummy[4096];
    char    sessid[64];
    char    contentType[128];
    char    *separator = getMultiPartID();

    sessid[0] = NUL;
    request = (char *)malloc( sz );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    // http://openpne.jp/?m=pc&a=page_h_diary_add �� GET
    Sleep( 1000 );
    strcpy( url, "http://openpne.jp/?m=pc&a=page_h_diary_add" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    // ���e
    Sleep( 1000 );
    sprintf( contentType, "multipart/form-data; boundary=%s", separator );
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "m", 0, "pc", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "a", 0, "page_h_diary_add_confirm", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "MAX_FILE_SIZE", 0, "307200", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "subject", 0, title, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "body", 0, body, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "upfile_1", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "upfile_2", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "upfile_3", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "submit", 0, sjis2utf("�@�m�F��ʁ@"), NULL ));
    sprintf( request + strlen( request ), "--%s--\r\n", separator );
    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL ); // ��n��
    sprintf( dummy, "%sReferer: %s\r\n", cookie, url );
    strcpy( url, "http://openpne.jp/" );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, contentType,
                request, response, dummy );
    if ( *response ) {
        //  -- sessid ���擾
        char    *p, *q;

        p = strstr( response, "name=\"sessid\" value=\"" );
        if ( p ) {
            p += 21;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( sessid, p, q - p );
                sessid[q - p] = NUL;
            }
        }
    }

    if ( sessid[0] ) {
        // ���e�m�F
        Sleep( 1000 );
        sprintf( request,
                 "m=pc&"
                 "a=do_h_diary_add_insert_c_diary&"
                 "sessid=%s&"
                 "subject=%s&"
                 "body=%s&"
                 "tmpfile_1=&"
                 "tmpfile_2=&"
                 "tmpfile_3=&"
                 "submit=%s",
                 sessid, title, body, sjis2utf("�@�� �@���@") );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                    request, response, cookie );

        if ( *response ) {
            if ( strstr( response, sjis2utf("��������F���L�{��") ) )
                ret = 1; // ���e����
        }
    }

    free( response );
    free( request );

    return ( ret );
}

int
postArticleOnOpenPNE( const char *username,     /* ���[�U��(���[���A�h���X) */
                      const char *password,     /* �p�X���[�h               */
                      char *title,              /* ���e�L���薼             */
                      char *body )              /* ���e�L���{��             */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginOpenPNE( username, password, cookie ) ) {
            char    *s, *t;

            s = editForColors( body );  /* �b��I�� editForColors() �𗬗p */
            t = sjis2utf( s );
                /* OpenPNE �ł͎g���Ȃ��^�O��ʂ̕\���ɒu�� */
            strcpy( body, t ? t : s );

            ret = postOpenPNE( title, body, cookie );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login �Ɏ��s���܂����B\n" );
        else
            MessageBox( NULL, "login �Ɏ��s���܂����B    ",
                        "OpenPNE", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
