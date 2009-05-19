/*
 *  rakuten.c
 *      �y�V�u���O���e����
 *
 *      written by H.Tsujimura    21 Apr 2005 / 2 Oct 2006
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�������������ė��p
 *
 * History:
 * $Log: /comm/blogolee/blogs/rakuten.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     08/09/10 18:02 Tsujimura543
 * loginRakuten(), postRakuten(), getCategoryListRakuten(),
 * getBlogIDsRakuten() �� xmlRPC.dll ����ڊ�
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
 * 3     07/01/23 15:33 Tsujimura543
 * (1) �y�V�u���O�̐V�����Ǘ���ʂɑΉ�
 * (2) �y�V�u���O�ɃJ�e�S���w�肵�ē��e�ł���悤�ɂ���
 * 
 * 2     06/10/02 20:08 Tsujimura543
 * cocousagi.h ���C���N���[�h����悤�ɂ���
 * 
 * 1     06/10/02 18:54 Tsujimura543
 * cocousagi.c ���� �y�V�u���O ���L�̏����𕪗�
 */

#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "xmlRPC.h"
#include "../postArticle.h"

/*
 * �u�y�V�L��v���߁u�y�V�u���O�v�������e����
 */

/* �� blog URL ���擾 */
static char *
getBlogURL( char *url, const char *htmlSrc )
{
    const char  *p, *q;

    p = strstr( htmlSrc, sjis2euc("My�y�[�W�̊m�F") );
    if ( p ) {
        while ( p > htmlSrc ) {
            if ( *--p != 'h' )
                continue;
            if ( !strncmp( p, "href=\"http://plaza.rakuten.co.jp/", 33 ) ) {
                p += 6;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( url, p, q - p );
                    url[q - p] = NUL;
                }
                break;
            }
        }
    }

    return ( url );
}

int
loginRakuten( const char *username,
              const char *password,
              char       *cookie,
              char       *myBlogURL )
{
    int     ret = 0;
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;
    char    url[MAX_URLLENGTH];

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

    memset( request, 0x00, MAX_CONTENT_SIZE );
    strcpy( url,
     "https://grp02.id.rakuten.co.jp/rms/nid/vc?__event=login&service_id=59");
    setTargetURL( url );
    sprintf( request,
             "u=%s&"
             "p=%s&"
             "autologin=true",
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
        if ( strstr( response, "class=\"loginUser\"" ) &&
             strstr( response, "class=\"blogData\"" )     ) {
            ret = 1;    /* ���O�C������ */
            getBlogURL( myBlogURL, response );
        }
        else
            ret = 0;    /* ���O�C�����s */
    }

    free( response );
    free( request  );

    return ( ret );
}


int
postRakuten( const char *username,
             const char *password,
             char       *cookie,
             const char *categoryName,  /* �J�e�S���� */
             const char *title,         /* �薼       */
             const char *body )         /* �{��       */
{
    int         ret = 0;
    char        *request;
    char        *response;
    size_t      sz = MAX_CONTENT_SIZE * 4;
    char        url[MAX_URLLENGTH];
    char        var_dummy[80];
    char        ch[80];
    int         yyyy, mm, dd;
    time_t      t;
    struct tm   *tm;
    int         categoryID = 0; /* �f�t�H���g�́u�J�e�S�������ށv */

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

    /* var_dummy �擾 */
    memset( request, 0x00, MAX_CONTENT_SIZE );
    var_dummy[0] = NUL;
    ch[0]        = NUL;
    strcpy( url, "http://my.plaza.rakuten.co.jp/?func=diary&act=write" );
    setUpReceiveBuffer( response, sz );
 // httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
 //                           NULL, NULL );
    http_getEx( url, response, cookie );
    if ( response[0] ) {
        char    *p = strstr( response, "name=\"var_dummy\"" );
        char    *q;

        if ( p ) {
            p += 16;
            q = strstr( p, "value=\"" );
            if ( q ) {
                q += 7;
                p = strchr( q, '"' );
                if ( p ) {
                    strncpy( var_dummy, q, p - q );
                    var_dummy[p - q] = NUL;
                }
            }
        }

        p = strstr( response, "name=\"ch\"" );
        if ( p ) {
            p += 9;
            q = strstr( p, "value=\"" );
            if ( q ) {
                q += 7;
                p = strchr( q, '"' );
                if ( p ) {
                    strncpy( ch, q, p - q );
                    ch[p - q] = NUL;
                }
            }
        }

        if ( categoryName && *categoryName ) {
            /* �J�e�S���� �� �J�e�S��ID �ϊ� */
            char    catID[64];

            getCategoryIDbyName( catID, categoryName, response,
                                 "<select name=\"cate_id\">",
                                 "</select>",
                                 "<option value=\"", "\">",
                                 CHARSET_EUCJP );
            if ( *catID )
                categoryID = atol( catID );
        }

        /* ���e */
        strcpy( url, "http://my.plaza.rakuten.co.jp/" );
        setTargetURL( url );

        t  = time( NULL );
        tm = localtime( &t );
        yyyy = tm->tm_year + 1900;
        mm   = tm->tm_mon + 1;
        dd   = tm->tm_mday;

        sprintf( request,
                 "theme_id=0&current_theme_id=0&ex_cate_id=0&"
                 "cate_id=%d&"  /* �J�e�S��ID (�e�[�}ID) */
                 "d_title=%s&"  /* �薼 (160�o�C�g�ȓ�)  */
                 "d_text=%s&"   /* �{�� */
                 "d_img_service=&"
                 "d_img_filename=&"
                 "d_img_position=0&"
                 "d_feel=1&"    /* �C���� (����: 1) */
                 "d_himitsu=&"  /* ����J���L */
                 "s_d_img_fileid=&"
                 "s_d_img_position=&"
                 "s_d_imgurl=&"
                 "s_d_img_title=&"
                 "s_d_img_w=&"
                 "s_d_img_h=&"
                 "t_img_service=&"
                 "char_dummy=%s&"
                 "var_dummy=%s&"
                 "d_date=%04d-%02d-%02d&"
                 "func=diary&act=write&"
                 "sub_act=insert&"
                 "ch=%s",
                 categoryID,
                 title, body, sjis2euc( "���y�V��"),
                 var_dummy, yyyy, mm, dd, ch );

        setUpReceiveBuffer( response, sz );
     // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
     //                            "application/x-www-form-urlencoded",
     //                            request, response, cookie,
     //                            NULL, NULL );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( response[0] &&
             strstr( response, sjis2euc( "�������݂��������܂���" ) ) )
            ret = 0;    /* ���e���� */
        else
            ret = -1;   /* ���e���s */
        /* ����: �y�V�L���1��3���܂ł������e�ł��Ȃ��B4���ڂ𓊍e���悤�� */
        /*       ����ƃG���[�ɂȂ�                                        */
    }
    else
        ret = -1;

    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}

int
getBlogIDsRakuten(
    const char *userName,       // (I) ���[�U��
    const char *password,       // (I) �p�X���[�h
    int        *numberOfBlogs,  // (I) �擾����/�擾���� blog ���̐�
    BLOGINF    *blogInfo )      // (O) �擾���� blog ���
{
    char    cookie[MAX_COOKIE_LEN];
    char    url[MAX_URLLENGTH];
    int     numOfBlogs = 0;

    cookie[0] = NUL;
    url[0]    = NUL;
    loginRakuten( userName, password, cookie, url );
    if ( url[0] ) {
        size_t  sz = MAX_CONTENT_SIZE;
        char    *response;

        strcpy( blogInfo[0].url, url );
        blogInfo[0].blogName[0] = NUL;
        blogInfo[0].blogID[0]   = NUL;

        response = (char *)malloc( sz );
        if ( response ) {
            setUpReceiveBuffer( response, sz );
            http_get( url, response );
            if ( *response ) {
                char        target[BUFSIZ];
                const char  *p, *q;

                target[0] = NUL;
                p = strstr( response,
                            "<td class=\"title_text\" id=\"title\">" );
                if ( p ) {
                    p += 34;
                    while ( (*p == ' ')  || (*p == '\t') ||
                            (*p == '\r') || (*p == '\n')    )
                        p++;
                    q = strstr( p, "</td>" );
                    if ( q ) {
                        while ( (q > p)                   &&
                                ( (*(q - 1) == ' ')  ||
                                  (*(q - 1) == '\t') ||
                                  (*(q - 1) == '\r') ||
                                  (*(q - 1) == '\n')    )    )
                            q--;
                        strncpy( target, p, q - p );
                        target[q - p] = NUL;
                    }
                }
                else {
                    p = strstr( response, "<title>" );
                    if ( p ) {
                        p += 7;
                        q = strstr( p, sjis2euc(" - �y�V") );
                        if ( q ) {
                            strncpy( target, p, q - p );
                            target[q - p] = NUL;
                        }
                    }
                    else {
                        p = strstr( response, " id=\"counter\">" );
                        if ( p ) {
                            p += 14;
                            p = strstr( p, "<font color=\"" );
                            if ( p ) {
                                p = strchr( p + 13, '>' );
                                if ( p ) {
                                    p++;
                                    q = strstr( p, sjis2euc("&nbsp;  �y�V") );
                                    if ( q ) {
                                        strncpy( target, p, q - p );
                                        target[q - p] = NUL;
                                    }
                                }
                            }
                        }
                    }
                }

                if ( target[0] ) {
                    p = euc2sjis( target );
                    strcpy( blogInfo[0].blogName, p ? p : target );
                }
            }

            free( response );
        }

        numOfBlogs = 1;
    }

    *numberOfBlogs = numOfBlogs;

    return ( numOfBlogs );
}


int
getCategoryListRakuten(
    const char   *userName,         // (I) ���[�U��
    const char   *password,         // (I) �p�X���[�h
    long         *numOfCategories,  // (I) �擾����J�e�S���̐�
                                    // (O) �擾�����J�e�S���̐�
    CATLISTINF_t categories )       // (O) �擾�����J�e�S�����
{
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    int     numOfCats = 0;
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !numOfCategories                      ||
         (*numOfCategories <= 0)               ||
         !categories                              )
        return ( numOfCats );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginRakuten( userName, password, cookie, url ) ) {
            request  = (char *)malloc( MAX_CONTENT_SIZE );
            if ( !request ) {
                free( cookie );
                return ( numOfCats );
            }
            response = (char *)malloc( sz );
            if ( !response ) {
                free( request );
                free( cookie );
                return ( numOfCats );
            }
            memset( request,  0x00, MAX_CONTENT_SIZE );

            /* �J�e�S���ꗗ�̎擾 */
            strcpy( url,
                    "http://my.plaza.rakuten.co.jp/?func=diary&act=write" );
            setUpReceiveBuffer( response, sz );
         // httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
         //                           NULL, NULL );
            http_getEx( url, response, cookie );

            /* �J�e�S�����̒��o */
            numOfCats = getCategoryIDs( numOfCategories, categories,
                                        response,
                                        "<select name=\"cate_id\">",
                                        "</select>",
                                        "<option value=\"", "\">",
                                        CHARSET_EUCJP );

            free( response );
            free( request  );
        }

        free( cookie );
    }

    *numOfCategories = numOfCats;

    return ( numOfCats );
}


char    *
editForRakuten( char *text )
{
    char    *p = text;
    char    *tmp, *q, *r;

    if ( !p || !(*p) )
        return ( text );

    tmp = (char *)malloc( strlen( p ) + 1 );
    if ( tmp )
        q = tmp;
    else
        q = p;

    /* ���̊֐��̏������e                  */
    /*   (1) class="xxx" ����菜�� [�K�{] */

    while ( *p ) {
        if ( !strncmp( p, "class=", 6 ) ) {
            /* (1) class="xxx" ����菜�� */
            r = strchr( p + 6, '"' );
            if ( r ) {
                r = strchr( r + 1, '"' );
                if ( r ) {
                    p = r + 1;
                    continue;
                }
            }

            r = strchr( p + 6, ' ' );
            if ( r ) {
                p = r;
                *q++ = *p++;// ' '
            }
            else if ( ( r = strchr( p + 6, '>') ) != NULL ) {
                p = r;
                *q++ = *p++;// '>'
            }
            else
                p += 6;
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
postArticleOnRakuten(
    const char *userName,       /* ���[�U��     */
    const char *password,       /* �p�X���[�h   */
    char       *title,          /* ���e�L���薼 */
    char       *body,           /* ���e�L���{�� */
    const char *categoryName )  /* �J�e�S����   */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );
    char    myBlogURL[MAX_URLLENGTH];

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginRakuten( userName, password, cookie, myBlogURL ) ) {
            char    *s, *t;

            s = sjis2euc( title );
            strcpy( title, s );
            t = sjis2euc( editForRakuten( body ) );
            strcpy( body,  t );
            ret = postRakuten( userName, password, cookie,
                               categoryName, title, body );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login �Ɏ��s���܂����B\n" );
        else
            MessageBox( NULL, "login �Ɏ��s���܂����B    ",
                        "�y�V�u���O", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
