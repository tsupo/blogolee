/*
 * utility.cpp : �u���O�N���C�A���g BloGolEe
 *      �e�탆�[�e�B���e�B�֐��Q
 *
 *          written by H.Tsujimura  7 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/utility.cpp $
 * 
 * 2     09/05/27 1:47 tsupo
 * 1.22��
 * 
 * 6     09/05/26 21:52 Tsujimura543
 * tumblr �ւ̓��e�ɑΉ�
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     07/12/05 23:17 Tsujimura543
 * unbase64() �̈����ǉ��ɔ����C�������{
 * 
 * 4     07/03/12 18:31 Tsujimura543
 * selectBlog() �𓱓����A���t�@�N�^�����O
 * 
 * 3     07/03/12 15:37 Tsujimura543
 * (1) encodeParameter() �� decodeParameter() �� utility.{h,cpp} �ֈړ�
 * (2) ��L�ɑΉ����� freeParameter() ��ʓr�p��
 * 
 * 2     07/03/12 5:07 Tsujimura543
 * Visual Studio 2005 �ł��r���h�ł���悤�ɃR�[�h���C��
 * 
 * 1     07/03/07 22:37 Tsujimura543
 * �V�K�쐬
 */

#include "blogolee.h"
#include "utility.h"
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "encryptRSA.h"
#ifdef __cplusplus
}
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/utility.cpp 2     09/05/27 1:47 tsupo $";
#endif

CString
GetValueFromXML(
        const char *element,
        const char *src,
        const char *terminator,
        bool       needToConvert )
{
    CString     s = _T("");
    char        startElement[BUFSIZ];
    char        endElement[BUFSIZ];
    const char  *p, *q;
    char        value[MAX_CONTENT_SIZE];

    sprintf( startElement, "<%s>",  element );
    sprintf( endElement,   "</%s>", element );

    q = strstr( src, startElement );
    if ( !q || (q > terminator) )
        return ( s );
    p = q + strlen( startElement );
    q = strstr( src, endElement );
    if ( !q || (q > terminator) )
        return ( s );

    strncpy( value, p, q - p );
    value[q - p] = NUL;

    if ( needToConvert ) {
        p = utf2sjis( value );
        if ( p )
            strcpy( value, p );
    }

    s = value;
    return ( s );
}

int
GetValueFromXML(
        const char *element,
        const char *src )
{
    int         value = 0;
    char        startElement[BUFSIZ];
    const char  *p;

    sprintf( startElement, "<%s>", element );

    p = strstr( src, startElement );
    if ( p ) {
        p += strlen( startElement );;
        value = atol( p );
    }

    return ( value );
}


char *readXML( const char *filename )
{
    char        *buf = NULL;
    size_t      sz   = 0;
    struct stat s;

    if ( !stat( filename, &s ) )
        sz = s.st_size;

    if ( sz > 0 ) {
        FILE    *fp = fopen( filename, "r" );

        if ( fp ) {
            buf = new char [sz + 16];
            if ( buf ) {
                memset( buf, NUL, sz + 16 );
                fread( buf, sz, 1, fp );
            }
            fclose( fp );
        }
    }

    if ( buf ) {
        register char   *p = buf;
        while ( *p ) {
            if ( *p == '\r' ) {
                if ( *( p + 1 ) == '\n' )
                    strcpy( p, p + 2 );
                else
                    strcpy( p, p + 1 );
            }
            else if ( *p == '\n' ) {
                if ( *( p + 1 ) == '\r' )
                    strcpy( p, p + 2 );
                else
                    strcpy( p, p + 1 );
            }

            else
                p++;
        }
    }

    return ( buf );
}


void    decodeParameter(
            CString             &param,          // �ݒ��
            const unsigned char *encryptedString,// �ݒ肷�ׂ����e(�v�E����)
            const unsigned char *rsaString )     // RSA���Ή�������
{
    char            *p;
    char            *decodedString;         // �������ʊi�[�̈�ւ̃|�C���^
    unsigned char   targetString[BUFSIZ];   // �����Ώۃo�C�g��
    int             len;                    // ��������(������)�̒���
    size_t          sz = 0;

    memset( targetString, 0x00, BUFSIZ );
    p = unbase64( encryptedString, targetString, &sz );
    if ( p && *p ) {
        len = decodeByRSA( &decodedString, rsaString,
                           (unsigned char *)targetString,
                           strlen( (char *)targetString ) );
        if ( len >= 0 ) {
            param = decodedString;
            freeRSAbuffer( decodedString );
        }
    }
}

void    encodeParameter(
            FILE          *fp,
            FILE          *gp,
            const char    *param,
            const char    *paramName,
            char          *key,
            unsigned char **rsaString,
            bool          &encrypted )
{
    int           len;
    unsigned char *cryptedString = NULL;

    len = encodeByRSA( param, rsaString, &cryptedString );
    if ( len > 0 ) {
        encrypted = true;
        if ( !(key[0]) )
            strcpy( key, base64(*rsaString, strlen((char *)*rsaString)) );
        if ( fp )
            fprintf( fp, "%sEncrypted: %s\n",
                     paramName,
                     base64( cryptedString, len ) );
        if ( gp )
            fprintf( gp, "%sEncrypted: %s\n",
                     paramName,
                     base64( cryptedString, len ) );
        freeRSAbuffer( (char *)cryptedString );
    }
    else {
        if ( fp )
            fprintf( fp, "%s: %s\n", paramName, param );
    }
}

void    freeParameter( unsigned char *rsaString )
{
    freeRSAkey( rsaString );
}


char    *
any2utf( const char *p )
{
    char    *q;

    q = utf2sjis( p );
    if ( q )
        q = (char *)p;  // ���ł� UTF-8 �ϊ��ς�
    else {
        // p �� charset �� UTF-8 �ł͂Ȃ�
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) )
            q = jis2utf( p );
        else {
            q = euc2sjis( p );
            if ( q )
                q = euc2utf( p );
            if ( !q )
                q = sjis2utf( p );
            if ( !q && p ) {
                /* �ȉ��AVox �΍� */
                char    *r = (char *)malloc( strlen(p) * 12 + 1 );

                if ( r ) {
                    char    *s;

                    strcpy( r, p );
                    s = utf2sjisEx( r );    /* (��Ƃ���) &ccedil; �΍� */
                    if ( s )
                        q = sjis2utf( s );
                    free( r );
                }
            }
            if ( !q )
                q = (char *)p;
        }
    }

    return ( q );
}

/* �w�蕶�����ʂ̎w�蕶����ɒu������ */
BOOL
replaceString( char *target, const char *src, const char *dst )
{
    char    *p = target;
    char    *q;
    BOOL    ret = FALSE;
    int     len = strlen( dst );

    while ( ( q = strstr( p, src ) ) != NULL ) {
        char    *temp;
        int     l = strlen( src );

        temp = (char *)malloc( strlen( p ) - l + strlen( dst ) + 1 );
        if ( temp ) {
            strncpy( temp, p, q - p );
            strcpy( &(temp[q - p]), dst );
            strcat( temp, q + l );

            strcpy( p, temp );
            free( temp );
            ret = TRUE;

            p = q + len;
        }
        else
            break;
    }

    return ( ret );
}


#include "BlogIDSelectDlg.h"

int selectBlog( BLOGINF *blogInfo, int numOfBlogs )
{
    CBlogIDSelectDlg    dlg;
    int                 ret = -1;

    dlg.initialize( blogInfo, numOfBlogs );
    int res = dlg.DoModal();
    if ( (res == IDOK) && (dlg.m_blogIDlistIndex != -1) ) {
        if ( (dlg.m_blogIDlistIndex >= 0)         &&
             (dlg.m_blogIDlistIndex < numOfBlogs)    ) {
            ret = dlg.m_blogIDlistIndex;
        }
    }

    return ( ret );
}
