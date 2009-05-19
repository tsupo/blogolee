/*
 *  kinugasa.c
 *      �L�k�K�T �����L���e����
 *
 *      written by H.Tsujimura    8 Oct 2004 / 2 Oct 2006
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�������������ė��p
 *
 * History:
 * $Log: /comm/blogolee/blogs/kinugasa.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     08/09/09 21:42 Tsujimura543
 * loginKinugasa() �� postKinugasa() �� xmlRPC.dll ����ڊ�
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
 * 1     06/10/02 19:17 Tsujimura543
 * cocousagi.c ���� �L�k�K�T ���L�̏����𕪗�
 */

#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "xmlRPC.h"
#include "../postArticle.h"

/*
 * �L�k�K�T�������e����
 */

int
loginKinugasa( const char *username,// (I) �L�k�K�T ID (���[���A�h���X)
               const char *password,// (I) �p�X���[�h
               char       *cookie ) // (O) �N�b�L�[
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE;

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
    response = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );

    strcpy( url, "http://kinugasa.cc/login.php?url=%2F" );
    setTargetURL( url );
    sprintf( request,
             "url=%s&"
             "username=%s&"
             "password=%s&"
             "auto_login=1",
             "/index.php",
             username, password );
    setUpReceiveBuffer( response, sz );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            "application/x-www-form-urlencoded",
 //                            request, response, cookie,
 //                            NULL, NULL );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
 // if ( ret == -1 )
 //     ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
 // else
    if ( *response ) {
     // if ( strstr( response, "./profile.php?key=" ) != NULL )
        if ( strstr( response, "./icon.php?key=" ) != NULL )
            ret = 1;    /* ���O�C������ */
        else
            ret = 0;    /* ���O�C�����s */
    }

    free( response );
    free( request  );

    return ( ret );
}

int
postKinugasa( const char *username, // (I) �L�k�K�T ID (���[���A�h���X)
              const char *password, // (I) �p�X���[�h
              char       *cookie,   // (I/O) �N�b�L�[
              const char *title,    // (I) �L���薼
              const char *body )    // (I) �L���{��
{
    int         ret = 0;
    char        *request;
    char        *response;
    char        url[MAX_URLLENGTH];
    time_t      t = time( NULL );
    struct tm   *tm = localtime( &t );
    int         yy, mm, dd, HH, MM, SS;
    size_t      sz = MAX_CONTENT_SIZE * 2;

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
    memset( request, 0x00, MAX_CONTENT_SIZE );

    /* ���e */
    yy = tm->tm_year + 1900;
    mm = tm->tm_mon + 1;
    dd = tm->tm_mday;
    HH = tm->tm_hour;
    MM = tm->tm_min;
    SS = tm->tm_sec;
    strcpy( url, "http://kinugasa.cc/diary_add.php" );
    setTargetURL( url );
    sprintf( request,
             "diary_title=%s&"
             "diary_view_policy=1&"
             "diary_comment_policy=1&"
             "diary_link_policy=1&"
          // "diary_datetime=%04d-%02d-%02d+%02d%%3A%02d%%3A%02d&"
             "diary_datetime=%04d-%02d-%02d %02d:%02d:%02d&"
             "diary_text=%s",
             title, yy, mm, dd, HH, MM, SS, body );
    setUpReceiveBuffer( response, sz );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            "application/x-www-form-urlencoded",
 //                            request, response, cookie,
 //                            NULL, NULL );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response )
        ret = 1;

    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}


int
postArticleOnKinugasa( const char *username,/* �L�k�K�T ID (���[���A�h���X) */
                       const char *password,/* �p�X���[�h                   */
                       char *title,         /* ���e�L���薼                 */
                       char *body )         /* ���e�L���{��                 */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginKinugasa( username, password, cookie ) ) {
            char    *s, *t;

            s = sjis2euc( title );
            strcpy( title, s );
            s = encodeURL( title );
            strcpy( title, s );
            t = editForMixi( body );/* mixi �p�̏����𗬗p */
            strcpy( body, encodeURL( sjis2euc( t ) ) );

            ret = postKinugasa( username, password, cookie,
                                title, body );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login �Ɏ��s���܂����B\n" );
        else
            MessageBox( NULL, "login �Ɏ��s���܂����B    ",
                        "�L�k�K�T", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
