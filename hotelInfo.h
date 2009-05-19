/*
 * hotelInfo.h  : �u���O�N���C�A���g BloGolEe
 *      �z�e�����\���� �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  7 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/hotelInfo.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/03/07 22:37 Tsujimura543
 * �V�K�쐬
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
