/*
 *  tumblr.c
 *      Tumblr ���e����
 *
 *      written by H.Tsujimura    26 May 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * History:
 * $Log: /comm/blogolee/blogs/tumblr.c $
 * 
 * 3     09/05/29 7:55 tsupo
 * 1.23��
 * 
 * 4     09/05/28 20:12 Tsujimura543
 * getBlogIDsTumblr() ���C���Bpublic group �̏ꍇ�́AURL �����ɂ��� ID ��
 * �̗p����悤�ɂ��� (���e�pAPI �� group �����Ŏw�肷�镶���񑊓�)
 * 
 * 3     09/05/28 18:41 Tsujimura543
 * format=html ���w�肵�ē��e����悤�ɂ���
 * 
 * 2     09/05/27 1:47 tsupo
 * 1.22��
 * 
 * 1     09/05/27 1:40 tsupo
 * VSS�T�[�o���_��ύX
 * 
 * 2     09/05/26 21:52 Tsujimura543
 * tumblr �ւ̓��e�ɑΉ�
 * 
 * 1     09/05/26 21:46 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "xmlRPC.h"
#include "../postArticle.h"
#include "../utility.h"

/*
 * Tumblr �������e����
 */

int
postArticleOnTumblr( const char *userName,  /* ���[�U�� (���[���A�h���X) */
                     const char *password,  /* �p�X���[�h                */
                     const char *group,     /* ���e���tumblelog         */
                     char       *title,     /* ���e�L���薼              */
                     char       *body )     /* ���e�L���{��             */
{
    char            *request  = NULL;
    char            *response = NULL;
    size_t          sz        = MAX_CONTENT_SIZE * 3;
    char            url[MAX_URLLENGTH * 4];
    char            name[MAX_DESCRIPTION_LEN];
    char            description[MAX_DESCRIPTION_LEN];
    char            tumblelogID[MAX_URLLENGTH];
    char            *p;
    int             ret = 0;

    request  = (char *)malloc( sz );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    strcpy( url, APIURL_TUMBLR_WRITE );

    // title
    strcpy( name, title );
    p = any2utf( name );
    if ( p )
        strcpy( name, p );

    /* �� �� &Lt; �ɉ�������A�� �� &Gt; �ɉ������肷�錏�̑΍� */
    if ( strstr( name, "\342\211\253" ) )   // &raquo; (E2 89 AB)
        replaceString( name, "\342\211\253", "\302\273" );// E2 89 AB �� C2 BB
    if ( strstr( name, "\342\211\252" ) )   // &laquo; (E2 89 AA)
        replaceString( name, "\342\211\252", "\302\253" );// E2 89 AA �� C2 AB

    // body
    strcpy( description, body );
    p = any2utf( description );
    if ( p )
        strcpy( description, p );

    // group
    p = strstr( group, "http://" );
    if ( p ) {
        strcpy( tumblelogID, p + 7 );
        if ( tumblelogID[strlen(tumblelogID) - 1] == '/' )
            tumblelogID[strlen(tumblelogID) - 1] = NUL;
    }
    else
        strcpy( tumblelogID, group );

    sprintf( request,
             "email=%s&"
             "password=%s&"
             "type=regular&",
             userName,
             password );
    sprintf( request + strlen(request),
             "title=%s&",
             encodeURL( name ) );
    sprintf( request + strlen(request),
             "body=%s&",
             encodeURL( description ) );
    sprintf( request + strlen(request),
             "format=html&"
             "group=%s&"
             "generator=BloGolEe",
             encodeURL( group ) );

    setUpReceiveBuffer( response, sz );
    http_post( url, "application/x-www-form-urlencoded",
               request, response );
    if ( *response ) {
        int postID = atol( response );
        if ( postID >= 1 )
            ret = 1;    /* ���e���� */
    }

    free( response );
    free( request );

    return ( ret );
}


int
getBlogIDsTumblr(
    const char *userName,       // (I) ���[�U�� (���[���A�h���X)
    const char *password,       // (I) �p�X���[�h
    int        *numberOfBlogs,  // (I) �擾����/�擾���� blog ���̐�
    BLOGINF    *blogInfo )      // (O) �擾���� blog ���
{
    char    cookie[MAX_COOKIE_LEN];
    char    url[MAX_URLLENGTH];
    char    name[MAX_BLOGNAMELENGTH];
    char    id[MAX_BLOGIDLENGTH];
    int     numOfBlogs = 0;
    size_t  sz  = MAX_CONTENT_SIZE;
    BOOL    ret = FALSE;
    char    request[BUFSIZ];
    char    *response = (char *)malloc( sz );

    if ( !response )
        return ( ret );

    cookie[0] = NUL;
    sprintf( request,
             "email=%s&"
             "password=%s",
             userName, password );

    setUpReceiveBuffer( response, sz );
    http_postEx( APIURL_TUMBLR_ACOUNT,
                 "application/x-www-form-urlencoded",
                 request, response, cookie );


    if ( *response ) {
        char    *p = strstr( response, "<tumblelog title=\"" );
        char    *q;
        char    *r;
        char    *s;

        while ( p ) {
            url[0]  = NUL;
            name[0] = NUL;
            id[0]   = NUL;
            blogInfo[numOfBlogs].blogName[0] = NUL;
            blogInfo[numOfBlogs].url[0]      = NUL;
            blogInfo[numOfBlogs].blogID[0]   = NUL;

            p += 18;
            q = strchr( p, '"' );
            r = strstr( p, "/>" );
            if ( !q || !r )
                break;

            if ( q < r ) {
                strncpy( name, p, q - p );
                name[q - p] = NUL;
                s = utf2sjis( name );
                strcpy( blogInfo[numOfBlogs].blogName, s ? s : name );

                p = q + 1;
            }

            q = strstr( p, "url=\"" );
            if ( q && (q < r) ) {
                p = q + 5;
                q = strchr( p, '"' );
                if ( q && (q < r) ) {
                    strncpy( url, p, q - p );
                    url[q - p] = NUL;
                    strcpy( blogInfo[numOfBlogs].url, url );

                    s = strstr( url, "http://" );
                    if ( s ) {
                        strcpy( blogInfo[numOfBlogs].blogID, s + 7 );
                        s = blogInfo[numOfBlogs].blogID;
                        if ( s[strlen(s) - 1] == '/' )
                            s[strlen(s) - 1] = NUL;
                    }

                    p = q + 1;
                }
            }
            else
                strcpy( blogInfo[numOfBlogs].url, "(private)" );

            q = strstr( p, "id=\"" );
            if ( q && (q < r) ) {
                p = q + 4;
                q = strchr( p, '"' );
                if ( q && (q < r) ) {
                    strncpy( id, p, q - p );
                    id[q - p] = NUL;
                    strcpy( blogInfo[numOfBlogs].blogID, id );

                    p = q + 1;
                }
            }

            q = p;
            p = strstr( q, "<tumblelog title=\"" );
            numOfBlogs++;

            if ( numOfBlogs >= *numberOfBlogs )
                break;
        }

        ret = TRUE;
        *numberOfBlogs = numOfBlogs;
    }

    free( response );

    return ( numOfBlogs );
}


