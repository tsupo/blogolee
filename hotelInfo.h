/*
 * hotelInfo.h  : ブログクライアント BloGolEe
 *      ホテル情報構造体 ヘッダーファイル
 *          written by H.Tsujimura  7 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/hotelInfo.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/03/07 22:37 Tsujimura543
 * 新規作成
 */

#ifndef __HOTEL_INFO_H__
#define __HOTEL_INFO_H__

struct  HotelInfo   {
    CString m_hotelName;
    CString m_hotelDetailURL;
    CString m_hotelCatchCopy;
    CString m_hotelCaption;
    CString m_hotelAddress;
    CString m_checkInTime;
    CString m_checkOutTime;

    CString m_pictureURL;
    CString m_pictureCaption;
};

#endif  /* __HOTEL_INFO_H__ */
