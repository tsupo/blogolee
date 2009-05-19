/*
 *  echoo.c
 *      �G�R���O���e����
 *
 *      written by H.Tsujimura    25 Nov 2004 / 2 Oct 2006
 *
 *      Copyright (c) 2004, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�������������ė��p
 *
 * History:
 * $Log: /comm/blogolee/blogs/echoo.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     08/09/10 21:41 Tsujimura543
 * loginEchoo(), postEchoo(), getCategoryListEchoo(),
 * getBlogIDsEchoo() �� xmlRPC.dll ����ڊ�
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
 * 1     06/10/02 19:05 Tsujimura543
 * cocousagi.c ���� �G�R���O ���L�̏����𕪗�
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
 * �G�R���O�������e����
 */

/* �w�蕶�����10�i�����񂩔ۂ� */
int
isDecString( const char *p )
{
    int ret = 1;

    while ( *p ) {
        if ( (*p >= '0') && (*p <= '9') ) {
            p++;
            continue;
        }

        ret = 0;
        break;
    }

    return ( ret );
}

int
selectOpenClassification()
{
    int     openClass = 0, i = 6;
    int     numOfOpenClasses = 6;
    BOOL    done = FALSE;

    do {
        fputs( "\n���J�敪: \n", stderr );
        fputs( "\t[1] ������\n", stderr );
        fputs( "\t[2] Echoo!���F�B�̂݌��J\n", stderr );
        fputs( "\t[3] ��тƂ܂��F�B�̂݌��J\n", stderr );
        fputs( "\t[4] Echoo!���̂݌��J\n", stderr );
        fputs( "\t[5] ��тƂܓ��̂݌��J\n", stderr );
        fputs( "\t[6] �O�����J\n", stderr );
        done = inputNumeric( &i, 1, numOfOpenClasses );
    } while ( !done );

    switch ( i ) {
    case 1:
        openClass = 0;
        break;
    case 2:
        openClass = 1;
        break;
    case 3:
        openClass = 2;
        break;
    case 4:
        openClass = 3;
        break;
    case 5:
        openClass = 6;
        break;
    case 6:
    default:
        openClass = 4;
        break;
    }

    return ( openClass );
}

int
loginEchoo( const char *username,   // (I) Echoo! ID (���[���A�h���X)
            const char *password,   // (I) �p�X���[�h
            char       *cookie,     // (O) �N�b�L�[
            char       *myBlogURL ) // (O) ��blog�g�b�v�y�[�WURL
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

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

    strcpy( url, "https://echoo.yubitoma.or.jp/index.htm" );
    setTargetURL( url );
    sprintf( request,
             "loginid=%s&"
             "pw=%s"     /*
             "&submit=%s"*/,
             username, password /* ,
             encodeURL(sjis2euc("���O�C��")) */ );
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
        if ( strstr( response, sjis2euc("����̃}�C�z�[���ł�") ) != NULL ) {
            char    *p, *q;
            ret = 1;    /* ���O�C������ */

            /* ��blog URL���擾 */
            p = strstr( response, sjis2euc( "�}�C�G�R���O�\��" ) );
            if ( p ) {
                while ( *p ) {
                    p--;
                    if ( (*p == ':') && !strncmp( p - 4, "http", 4 ) ) {
                        p -= 4;
                        q = strchr( p, '"' );
                        if ( q ) {
                            strncpy( myBlogURL, p, q - p );
                            myBlogURL[q - p] = NUL;
                            break;
                        }
                    }
                }
            }
        }
        else
            ret = 0;    /* ���O�C�����s */
    }

    free( response );
    free( request  );

    return ( ret );
}


int
postEchoo( const char *username,    // (I) Echoo! ID (���[���A�h���X)
           const char *password,    // (I) �p�X���[�h
           char       *cookie,      // (I/O) �N�b�L�[
           const char *categoryID,  // (I) �J�e�S��ID (10�i����)
                                    //     �܂��� �J�e�S����
           const char *title,       // (I) �L���薼
           const char *body )       // (I) �L���{��
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    catID[36];
    char    url[MAX_URLLENGTH];
    char    contentType[128];
    char    *separator = getMultiPartID();
    char    *p;
    int     openClass;
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

    setUpReceiveBuffer( response, sz );
    if ( !categoryID || !(*categoryID) ) {
        /* �J�e�S���ꗗ�̎擾 */
     // httpGetBufferWithSession(
     //     "http://echoo.yubitoma.or.jp/blog/entry.htm",
     //     response, TRUE, NULL, NULL, cookie,
     //     NULL, NULL );
        http_getEx( "http://echoo.yubitoma.or.jp/blog/entry.htm",
                     response, cookie );

        /* �J�e�S���̑I�� */
        getCategoryIDstring( catID, response,
                             "<option value=\"\">--",
                           "</select>&nbsp;&nbsp;<a href=\"./category.htm\">",
                             "<option value=\"", "\">",
                             CHARSET_EUCJP );
    }
    else if ( !isDecString( categoryID ) ) {
        /* �J�e�S���ꗗ�̎擾 */
     // httpGetBufferWithSession(
     //     "http://echoo.yubitoma.or.jp/blog/entry.htm",
     //     response, TRUE, NULL, NULL, cookie,
     //     NULL, NULL );
        http_getEx( "http://echoo.yubitoma.or.jp/blog/entry.htm",
                    response, cookie );

        /* �J�e�S���� �� �J�e�S��ID �ϊ� */
        getCategoryIDbyName( catID, categoryID, response,
                             "<option value=\"\">--",
                           "</select>&nbsp;&nbsp;<a href=\"./category.htm\">",
                             "<option value=\"", "\">",
                             CHARSET_EUCJP );
    }
    else
        strncpy( catID, categoryID, 32 );

    /* ���J�敪�̑I�� */
    openClass = selectOpenClassification();

    /* ���e */
    sprintf( contentType, "multipart/form-data; boundary=%s", separator );
    strcpy( url, "http://echoo.yubitoma.or.jp/blog/entry.htm" );
    setTargetURL( url );
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "e_kind", 0,
#if 0
                    "http://echoo.yubitoma.or.jp/blog/entry.htm?e_kind=1"
#else
                    "1"
#endif
                    , NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "title", 0, sjis2euc( title ), NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "category", 0, catID, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "entry", 0, sjis2euc( body ), NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "imgfile", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "amazon", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "trackbackurl", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_INTEGER,
                               "b_open", openClass, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "w_place", 0, "NULL", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "echoo_entry", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "eid", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "proc", 0, "kakunin", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "amazon_hidden", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "tmp_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "image", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "e_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "person", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "flg", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "sdate", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "m_factur", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "search_mode", 0, NULL, NULL ) );
    sprintf( request + strlen( request ), "--%s--\r\n", separator );

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );
    setUpReceiveBuffer( response, sz );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            contentType,
 //                            request, response, cookie,
 //                            NULL, NULL );
    http_postEx( url, contentType, request, response, cookie );

    /* ���e�m�F */
    strcpy( url, "http://echoo.yubitoma.or.jp/blog/entry.htm" );
    setTargetURL( url );
#if 0
    sprintf( request,
             "e_kind=1&"
             "tmp_title=&"
             "image=&"
             "person=&"
             "flg=&"
             "sdate=&"
             "m_factur=&"
             "search_mode=&"
             "title=%s&",
             sjis2euc( title ) );
    sprintf( request + strlen( request ),
             "entry=%s&"
             "category=%s&"
             "proc=write&"
             "b_open=%d&"
             "w_place=NULL&"
             "MAX_FILE_SIZE=",
             encodeURL( sjis2euc( body ) ), catID, openClass );
    setUpReceiveBuffer( response, sz );
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               "application/x-www-form-urlencoded",
                               request, response, cookie );
#else
    /* ���e�m�F��ʂ� application/x-www-form-urlencoded ��      */
    /*                         multipart/form-data �ɕύX���ꂽ */
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "e_kind", 0, "1", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "tmp_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "image", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "e_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "person", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "flg", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "sdate", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "m_factur", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "search_mode", 0, NULL, NULL ) );

    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "title", 0, sjis2euc( title ), NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "entry", 0, sjis2euc( body ), NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "category", 0, catID, NULL ) );

    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "proc", 0, "write", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_INTEGER,
                               "b_open", openClass, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "w_place", 0, "NULL", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "MAX_FILE_SIZE", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "imgsize", 0, "150", NULL ) );
    sprintf( request + strlen( request ), "--%s--\r\n", separator );

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );
    setUpReceiveBuffer( response, sz );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            contentType,
 //                            request, response, cookie,
 //                            NULL, NULL );
    http_postEx( url, contentType, request, response, cookie );
    ret = 1;
#endif

    if ( !(response[0])                           ||
         (((p = euc2sjis(response)) != NULL) &&
          !strstr( p, "�L���C���E�폜" )        )    ) {
        // ���e���s
        fputs( "���e�Ɏ��s���܂����B\n", stderr );
        ret = -1;
    }

    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}

int
getCategoryListEchoo(
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
        if ( loginEchoo( userName, password, cookie, url ) ) {
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
            setUpReceiveBuffer( response, sz );
         // httpGetBufferWithSession(
         //     "http://echoo.yubitoma.or.jp/blog/entry.htm",
         //     response, TRUE, NULL, NULL, cookie,
         //     NULL, NULL );
            http_getEx( "http://echoo.yubitoma.or.jp/blog/entry.htm",
                        response, cookie );

            /* �J�e�S�����̒��o */
            numOfCats = getCategoryIDs( numOfCategories, categories,
                                        response,
                                        "<option value=\"\">--",
                           "</select>&nbsp;&nbsp;<a href=\"./category.htm\">",
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

int
getBlogIDsEchoo(
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
    loginEchoo( userName, password, cookie, url );
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
                p = strstr( response, "<title>" );
                if ( p ) {
                    p += 7;
                    q = strstr( p, " - Echoo!" );
                    if ( q ) {
                        strncpy( target, p, q - p );
                        target[q - p] = NUL;
                    }
                }
                else {
                    p = strstr( response, "<h1><a href=\"" );
                    if ( p ) {
                        p = strchr( p + 13, '>' );
                        if ( p ) {
                            p++;
                            q = strstr( p, "</a>" );
                            if ( q ) {
                                strncpy( target, p, q - p );
                                target[q - p] = NUL;
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


char    *
editForEchoo( char *text )
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

    /* ���̊֐��̏������e            */
    /*   (1) <br /> �����s�ɒu������ */
    /*   (2) <p>, <cite> ����菜��  */
    /*   (3) class ��������菜��    */

    while ( *p ) {
        if ( !strncmp( p, "<br />", 6 ) ) {
            /* (1) <br /> �����s�ɒu������ */
            p += 6;
            *q++ = '\r';
            *q++ = '\n';
        }
        else if ( !strncmp( p, "<p>", 3 ) ) {
            /* (2a1) <p> ����菜�� */
            p += 3;
        }
        else if ( !strncmp( p, "</p>", 4 ) ) {
            /* (2a2) </p> ����菜�� */
            p += 4;
            *q++ = '\r';
            *q++ = '\n';
        }
        else if ( !strncmp( p, "<cite>", 6 ) ) {
            /* (2b1) <cite> ����菜�� */
            const char  *pp = "<i>";

            p += 6;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "</cite>", 7 ) ) {
            /* (2b2) </cite> ����菜�� */
            const char  *pp = "</i>";

            p += 7;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "class=\"", 7 ) ) {
            /* (3) class="..." ����菜�� */
            char    *r;
            p += 7;
            r = strchr( p, '"' );
            if ( r )
                p = r + 1;
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
postArticleOnEchoo( const char *userName,       /* ���[�U��     */
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
        if ( loginEchoo( userName, password, cookie, myBlogURL ) ) {
            const char  *t;

            t = editForEchoo( body );
            ret = postEchoo( userName, password, cookie,
                             (categoryName && *categoryName)
                                ? categoryName  /* �J�e�S���� */
                                : "",  /* �J�e�S��ID: �󕶎��� �́u���ݒ�v */
                             title, t );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login �Ɏ��s���܂����B\n" );
        else
            MessageBox( NULL, "login �Ɏ��s���܂����B    ",
                        "�G�R���O", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
