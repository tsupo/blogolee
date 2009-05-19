/*
 *  fc2network.c
 *      FC2NETWORK �����L���e����
 *
 *      written by H.Tsujimura    29 Mar 2005 / 2 Oct 2006
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�������������ė��p
 *
 * History:
 * $Log: /comm/blogolee/blogs/fc2network.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     08/09/09 22:19 Tsujimura543
 * loginFC2NETWORK() �� postFC2NETWORK() �� xmlRPC.dll ����ڊ�
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
 * 1     06/10/02 19:11 Tsujimura543
 * cocousagi.c ���� FC2NETWORK ���L�̏����𕪗�
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
 * FC2NETWORK�������e����
 */

int
loginFC2NETWORK( const char *username,  // (I) ���[���A�h���X
                 const char *password,  // (I) �p�X���[�h
                 char       *cookie )   // (O) �N�b�L�[
{
    int     ret = 0;
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !username || !(*username) ||
         !password || !(*password) ||
         !cookie )
         return ( ret );

 // if ( cp )
 //     destroyCookie( cp );
 // cp = createCookie();
 // if ( !cp )
 //     return ( ret );
 // xmlrpc_p->blogDependentArea = (void *)cp;

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

    setTargetURL( "http://network.fc2.com/index.php" );
    sprintf( request,
             "loginid=%s&"
             "loginpass=%s&"
             "idptoc=1",
             username, password );
    setUpReceiveBuffer( response, sz );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            "application/x-www-form-urlencoded",
 //                            request, response, cookie,
 //                            NULL, NULL );
    http_postEx( "http://network.fc2.com/index.php",
                 "application/x-www-form-urlencoded",
                 request, response, cookie );
 // if ( ret == -1 )
 //     ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
 // else
    if ( *response ) {
        if ( strstr( response, "index.php?vid=" ) != NULL )
            ret = 1;    /* ���O�C������ */
        else {
            ret = 0;    /* ���O�C�����s */
         // destroyCookie( cp );
         // cp = NULL;
         // xmlrpc_p->blogDependentArea = NULL;
        }
    }

    free( response );
    free( request  );

    return ( ret );
}


int
postFC2NETWORK( const char *username,       // (I) ���[���A�h���X
                const char *password,       // (I) �p�X���[�h
                char       *cookie,         // (I/O) �N�b�L�[
                const char *title,          // (I) �L���薼
                const char *body,           // (I) �L���{��
                const char *trackbackURL )  // (I) �g���b�N�o�b�N���M��URL
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    contentType[128];
    char    magicName[80];
    char    magicValue[80];
    char    *separator = getMultiPartID();
    size_t  sz = MAX_CONTENT_SIZE * 2;

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

    /* �}�W�b�N�i���o�[�擾 */
    magicName[0]  = NUL;
    magicValue[0] = NUL;
    setUpReceiveBuffer( response, sz );
    http_getEx( "http://network.fc2.com/diary/index.php", response, cookie );
    if ( *response ) {
        char    *p, *q;
        char    url[MAX_URLLENGTH];

        p = strstr( response, "<a href=\"topic_post.php?" );
        if ( p ) {
            p += 9;
            q = strchr( p, '"' );
            if ( q ) {
                strcpy( url, "http://network.fc2.com/diary/" );
                strncat( url, p, q - p );
                url[29 + (q - p)] = NUL;
                setUpReceiveBuffer( response, sz );
                http_getEx( url, response, cookie );

                if ( *response ) {
                    p = strstr( response, "<input type=\"hidden\" name=\"" );
                    if ( p ) {
                        p += 27;
                        q = strchr( p, '"' );
                        if ( q ) {
                            strncpy( magicName, p, q - p );
                            magicName[q - p] = NUL;

                            p = strstr( q + 1, "value=\"" );
                            if ( p ) {
                                p += 7;
                                q = strchr( p, '"' );
                                if ( q ) {
                                    strncpy( magicValue, p, q - p );
                                    magicValue[q - p] = NUL;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /* ���e */
    sprintf( contentType, "multipart/form-data; boundary=%s", separator );
    setTargetURL( "http://network.fc2.com/diary/topic_input.php" );
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "post_settime", 0, "use_nowtime", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "pub_set", 0, "default", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "post_title", 0, title, NULL ) );  /* 40byte �ȓ� */
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "post_body", 0, body, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "by_html", 0, "1", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "postfile1", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "align1", 0, "none", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "flink1", 0, "1", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "postfile2", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "align2", 0, "none", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "flink2", 0, "1", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "postfile3", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "align3", 0, "none", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "flink3", 0, "1", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "postfile4", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "align4", 0, "none", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "flink4", 0, "1", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "postfile5", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "align5", 0, "none", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "flink5", 0, "1", NULL ) );

    if ( trackbackURL && *trackbackURL ) {
        strcat( request, 
                makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                                   "tbto_url", 0, "1", NULL ) );
        strcat( request, 
                makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                                   "tb_url", 0, trackbackURL, NULL ) );
        strcat( request, 
                makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                                   "tb_encode", 0, "UTF-8", NULL ) );
    }

    if ( magicName[0] && magicValue[0] )
        strcat( request, 
                makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                                   magicName, 0, magicValue, NULL ) );

    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "mode", 0, "newpost", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "back_url", 0,
                               "http://network.fc2.com/index.php",
                               NULL ) );

    sprintf( request + strlen( request ), "--%s--\r\n", separator );

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );

    setUpReceiveBuffer( response, sz );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            contentType,
 //                            request, response, cookie,
 //                            NULL, NULL );
    http_postEx( "http://network.fc2.com/diary/topic_input.php",
                 contentType, request, response, cookie );
    if ( *response ) {
        if ( strstr( response, "ERROR" ) )
            ret = -1;   /* ���e���s */
        else
            ret = 1;    /* ���e���� */
    }

    free( response );
    free( request  );
 // destroyCookie( cp );
 // cp = NULL;
 // xmlrpc_p->blogDependentArea = NULL;

    return ( ret == -1 ? 0 : 1 );
}


char    *
editForFC2NETWORK( char *text )
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
            const char  *pp = "[:br:]";

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
            const char  *pp = "[:br:]";

            p += 4;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "<cite>", 6 ) ) {
            /* (2b1) <cite> ����菜�� */
            const char  *pp = "[:i-s:]";

            p += 6;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "</cite>", 7 ) ) {
            /* (2b2) </cite> ����菜�� */
            const char  *pp = "[:i-e:]";

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
            const char  *pp = "[:qt-s:]";

            p += 12;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "</blockquote>", 13 ) ) {
            /* (3b) </blockquote> ����菜�� */
            const char  *pp = "[:qt-e:][:br:]";

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
postArticleOnFC2NETWORK( const char *username,  /* ���[���A�h���X */
                         const char *password,  /* �p�X���[�h     */
                         char *title,           /* ���e�L���薼   */
                         char *body )           /* ���e�L���{��   */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginFC2NETWORK( username, password, cookie ) ) {
            char    *s, *t;

            s = sjis2euc( title );
            strcpy( title, s );

            /* FC2NETWORK�ł͎g���Ȃ��^�O��ʂ̕\���ɒu�� */
            t = editForFC2NETWORK( body );
            strcpy( body, sjis2euc( t ) );

            ret = postFC2NETWORK( username, password, cookie,
                                  title, body, NULL );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login �Ɏ��s���܂����B\n" );
        else
            MessageBox( NULL, "login �Ɏ��s���܂����B    ",
                        "FC2NETWORK", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
