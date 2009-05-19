/*
 *  livedoor.c
 *      livedoor Blog �č\�z����
 *
 *      written by H.Tsujimura    27 Jan 2006 / 2 Oct 2006
 *
 *      Copyright (c) 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�����̂܂ܗ��p
 *
 * History:
 * $Log: /comm/blogolee/blogs/livedoor.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
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
 * 3     07/02/14 16:46 Tsujimura543
 * http�ʐM�̃^�C���A�E�g���Ԃ𒷂߂ɂ��Ă݂�
 * 
 * 2     06/10/02 20:08 Tsujimura543
 * cocousagi.h ���C���N���[�h����悤�ɂ���
 * 
 * 1     06/10/02 18:11 Tsujimura543
 * cocousagi.c ���� livedoor Blog ���L�̏����𕪗�
 */

#include "xmlRPC.h"
#include "../postArticle.h"

/*
 *  livedoor �����č\�z����
 */
int
loginLivedoor( const char *username,
               const char *password,
               char       *cookie )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    memset( request,  0x00, MAX_CONTENT_SIZE );
    setUpReceiveBuffer( response, sz );
    http_getEx( "http://blog.livedoor.com/",
                response, cookie );

    strcpy( url, "http://member.livedoor.com/login/index" );
    setTargetURL( url );
    sprintf( request,
             ".next=%s&"
             ".sv=blog&"
             "livedoor_id=%s&"
             "password=%s&"
             "auto_login=on\r\n",
             encodeURL("http://cms.blog.livedoor.com/cms/"),
             username, password );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        if ( strstr( response,
                     "<input type=\"hidden\" name=\"blog_id\"" ) != NULL )
            ret = 1;    /* ���O�C������ */
        else
            ret = 0;    /* ���O�C�����s */
    }
    else
        ret = 0;        /* ���O�C�����s */

    free( response );
    free( request  );

    return ( ret );
}

void
rebuildOnLivedoor(
        const char *username,
        const char *password,
        const char *blogID
    )
{
    char    *request;
    char    *response;
    char    *cookie;
    char    url[MAX_URLLENGTH * 16];
    int     ret;
    size_t  sz = MAX_CONTENT_SIZE * 32;

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return;
    request = (char *)malloc( MAX_COOKIE_LEN );
    if ( !request ) {
        free( cookie );
        return;
    }
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( cookie );
        return;
    }

    // livedoor Blog �� login
    memset( cookie, 0x00, MAX_COOKIE_LEN );
    ret = loginLivedoor( username, password, cookie );
    if ( ret ) {
        // �u�S�y�[�W�v�̍č\�z�����s
        setTimeoutTime( DEFAULT_HTTP_TIMEOUT * 4 );
        strcpy( url, "http://cms.blog.livedoor.com/cms/rebuild/index" );
        sprintf( request,
                 "blog_id=%s&"
                 "command=css,index,rss,atom,monthly,category,articles:all&"
                 ".popup=0",
                 blogID );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        while ( *response ) {
            char    *p = strstr(response,
                                "<body onLoad=\"JavaScript: location.href='");
            char    *q;

            if ( p ) {
                 p += 41;
                 q = strchr( p, '\'' );
                 if ( q ) {
                    int    len;

                    strcpy(url, "http://cms.blog.livedoor.com/cms/rebuild/");
                    len = strlen( url );
                    strncat( url, p, q - p );
                    url[len + (q - p)] = NUL;

                    setTargetURL( url );
                    if ( isatty( fileno( stderr ) ) )
                        fprintf( stderr, "�č\�z�� %s ...", url );
                    setUpReceiveBuffer( response, sz );
                    http_getEx( url, response, cookie );
                    if ( isatty( fileno( stderr ) ) )
                        fputs( "\n", stderr );
                 }
            }
            else
                break;
        }
        setTimeoutTime( DEFAULT_HTTP_TIMEOUT );
    }

    free( response );
    free( request );
    free( cookie );
}
