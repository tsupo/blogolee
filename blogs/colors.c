/*
 *  colors.c
 *      COLORS �����L���e����
 *
 *      written by H.Tsujimura    27 Dec 2005 / 2 Oct 2006
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�������������ė��p
 *
 * History:
 * $Log: /comm/blogolee/blogs/colors.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     08/09/09 19:58 Tsujimura543
 * loginColors() �� postColors() �� xmlRPC.dll ����ڊ�
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
 * 1     06/10/02 18:38 Tsujimura543
 * cocousagi.c ���� COLORS ���L�̏����𕪗�
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
 * COLORS�������e����
 */

int
loginColors( const char *username,  // (I) COLORS ID (���[���A�h���X)
             const char *password,  // (I) �p�X���[�h
             char       *cookie )   // (O) �N�b�L�[
{
    int         ret = 0;
    char        *request;
    char        *response;
    char        url[MAX_URLLENGTH];
    size_t      sz = MAX_CONTENT_SIZE * 2;

    if ( !username || !(*username) ||
         !password || !(*password) ||
         !cookie )
         return ( ret );

 // if ( !username )
 //     username = xmlrpc_p->userName;
 // if ( !password )
 //     password = xmlrpc_p->password;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );
    memset( response, 0x00, sz );

    strcpy( url, "http://clrs.jp/index.php" );
    setTargetURL( url );
    sprintf( request,
             "mode=sign&"
             "user=%s&"
             "password=%s&"
             "submit=%s&"
             "auto=on",
             username, password,
             encodeURL("���O�C��") );

 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            "application/x-www-form-urlencoded",
 //                            request, response, cookie,
 //                            NULL, NULL );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

 // if ( ret == -1 )
 //     ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
 // else
    if ( *response ) {
        if ( strstr( response, " alt=\"���O�A�E�g\" " ) != NULL )
            ret = 1;    /* ���O�C������ */
        else
            ret = 0;    /* ���O�C�����s */
    }

    free( response );
    free( request  );

    return ( ret );
}


int
postColors( const char *username,   // (I) COLORS ID (���[���A�h���X)
            const char *password,   // (I) �p�X���[�h
            char       *cookie,     // (I/O) �N�b�L�[
            const char *title,      // (I) �L���薼
            const char *body )      // (I) �L���{��
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    contentType[128];
    char    checkcode[64];
    char    dummy[4096];
    char    *separator = getMultiPartID();
    size_t  sz = MAX_CONTENT_SIZE * 4;

    if ( !username || !(*username) ||
         !password || !(*password) ||
         !title    || !(*title)    ||
         !body     || !(*body)     ||
         !cookie   || !(*cookie)      )
         return ( ret );

 // if ( !username )
 //     username = xmlrpc_p->userName;
 // if ( !password )
 //     password = xmlrpc_p->password;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );
    memset( response, 0x00, sz );

    /* ���e */
    Sleep( 2000 );  /* �O�̂��� */
    strcpy( url, "http://clrs.jp/add_diary.php?mode=addconfirm" );
    setTargetURL( url );
    sprintf( contentType, "multipart/form-data; boundary=%s", separator );
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "magicword", 0, "����", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "subject", 0, title, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "body", 0, body, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "MAX_FILE_SIZE", 0, "300000", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "upload_img", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "img_url1_width", 0, "0", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "img_url1", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "img_url2_width", 0, "0", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "img_url2", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "Submit", 0, "�m�@�F", NULL ) );
    sprintf( request + strlen( request ), "--%s--\r\n", separator );

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );
    sprintf( dummy,
             "%sReferer: %s\r\n", cookie,
             "http://clrs.jp/add_diary.php" );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            contentType,
 //                            request, response, dummy,
 //                            NULL, NULL );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, contentType, request, response, dummy );

    /* checkcode �擾 */
    checkcode[0] = NUL;
    if ( response[0] ) {
        char    *p = strstr( response, "name=\"checkcode\"" );
        char    *q;

        if ( p ) {
            p += 16;
            q = strstr( p, "value=\"" );
            if ( q ) {
                p = q + 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( checkcode, p, q - p );
                    checkcode[q - p] = NUL;
                }
            }
        }
    }
    ret = -1;

    /* ���e�m�F */
    if ( checkcode[0] ) {
        Sleep( 2000 );  /* �O�̂��� */
        memset( response, 0x00, sz );
        strcpy( url, "http://clrs.jp/add_diary.php?mode=addexec" );
        setTargetURL( url );
        sprintf( request,
                 "magicword=%s&"
                 "checkcode=%s&"
                 "subject=%s&"
                 "body=%s&"
                 "upload_img=&"
                 "img_url1=&"
                 "img_url1_width=0&"
                 "img_url2=&"
                 "img_url2_width=0&"
                 "Submit=%s",
                 "����", checkcode, title, body, "��@��" );
        sprintf( dummy,
                 "%sReferer: %s\r\n", cookie,
                 "http://clrs.jp/add_diary.php?mode=addconfirm" );

     // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
     //                            "application/x-www-form-urlencoded",
     //                            request, response, dummy,
     //                            NULL, NULL );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, dummy );
        if ( response[0] )
            ret = 1;
    }

    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}


char    *
editForColors( char *text )
{
    char    *p = text;
    char    *tmp, *q;

    if ( !p || !(*p) )
        return ( text );

    tmp = (char *)malloc( strlen( p ) + 1 );
    if ( tmp )
        q = tmp;
    else
        q = p;

    /* ���̊֐��̏������e                */
    /*   (1) <br /> �����s�ɒu������     */
    /*   (2) <p>, <cite>, <a> ����菜�� */
    /*   (3) <blockquote> ����菜��     */

    while ( *p ) {
        if ( !strncmp( p, "<br />", 6 ) ) {
            /* (1) <br /> �� [:br:] �ɒu������ */
            const char  *pp = "\r\n";

            p += 6;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "<p>", 3 ) ) {
            /* (2a1) <p> ����菜�� */
            p += 3;
        }
        else if ( !strncmp( p, "</p>", 4 ) ) {
            /* (2a2) </p> ����菜�� */
            const char  *pp = "\r\n";

            p += 4;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "<cite>", 6 ) ) {
            /* (2b1) <cite> ����菜�� */
            const char  *pp = "�w";

            p += 6;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "</cite>", 7 ) ) {
            /* (2b2) </cite> ����菜�� */
            const char  *pp = "�x";

            p += 7;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "<a ", 3 ) ) {
            /* (2c1) <a> ����菜�� */
            p += 3;
            while ( *p && (*p != '>') )
                p++;
            if ( *p == '>' )
                p++;
        }
        else if ( !strncmp( p, "</a>", 4 ) ) {
            /* (2c2) </a> ����菜�� */
            p += 4;
        }
        else if ( !strncmp( p, "<blockquote>", 12 ) ) {
            /* (3a) <blockquote> ����菜�� */
            const char  *pp = ">>\r\n";

            p += 12;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "</blockquote>", 13 ) ) {
            /* (3b) </blockquote> ����菜�� */
            const char  *pp = "\r\n<<\r\n";

            p += 13;
            while ( *pp )
                *q++ = *pp++;
        }
        else
            *q++ = *p++;
    }
    *q = NUL;

    if ( tmp ) {
        strcpy( text, tmp );
        free( tmp );
    }

    return ( text );
}

int
postArticleOnColors( const char *username,  /* ���[�U��(���[���A�h���X) */
                     const char *password,  /* �p�X���[�h               */
                     char *title,           /* ���e�L���薼 */
                     char *body )           /* ���e�L���{�� */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( title[0] && (strlen(title) > 40) ) {
            /* COLORS �ł́A�L���̃^�C�g���� 40 �o�C�g�ȓ� */
            /*     (40�o�C�g��蒷���Ɠ��e�Ɏ��s����)      */
            strcpy( title, sjis2utf( "�����̓��L" ) );
        }
        if ( loginColors( username, password, cookie ) ) {
            char    *t;

            /* COLORS�ł͎g���Ȃ��^�O��ʂ̕\���ɒu�� */
            t = editForColors( body );
            strcpy( body, t );

            ret = postColors( username, password, cookie,
                              title, body );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login �Ɏ��s���܂����B\n" );
        else
            MessageBox( NULL, "login �Ɏ��s���܂����B    ",
                        "COLORS", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
