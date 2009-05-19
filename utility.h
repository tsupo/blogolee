/*
 * utility.h  : ブログクライアント BloGolEe
 *      各種ユーティリティ関数群 ヘッダーファイル
 *          written by H.Tsujimura  7 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/utility.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/03/12 18:35 Tsujimura543
 * utility.h を .cpp と .c の両者から include できるように書き直す
 * 
 * 3     07/03/12 18:31 Tsujimura543
 * selectBlog() を導入し、リファクタリング
 * 
 * 2     07/03/12 15:37 Tsujimura543
 * (1) encodeParameter() と decodeParameter() を utility.{h,cpp} へ移動
 * (2) 上記に対応して freeParameter() を別途用意
 * 
 * 1     07/03/07 22:37 Tsujimura543
 * 新規作成
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
            CString             &param,          // 設定先
            const unsigned char *encryptedString,// 設定すべき内容(要・復号)
            const unsigned char *rsaString );    // RSA鍵対応文字列

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
