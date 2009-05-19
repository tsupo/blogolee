/*
 * HotelDialog.h  : �u���O�N���C�A���g BloGolEe
 *      �z�e�����\���_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  7 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/HotelDialog.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/03/07 22:39 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#if !defined(AFX_HOTELDIALOG_H__FACA5207_C3C8_4885_8BED_AFFC7353DD1D__INCLUDED_)
#define AFX_HOTELDIALOG_H__FACA5207_C3C8_4885_8BED_AFFC7353DD1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "hotelInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CHotelDialog �_�C�A���O

class CHotelDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CHotelDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
    ~CHotelDialog() {
        m_cFont.DeleteObject();
    }

    HCURSOR     m_hCursor;
    CFont       m_cFont;

    int         m_numOfHotelInfo;
    int         m_currentHotelInfo;
    HotelInfo   *m_hotelInfo;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CHotelDialog)
	enum { IDD = IDD_DIALOG_HOTEL_INFO };
	CString	m_hotelInfoString;
	CString	m_hotelName;
	CString	m_hotelURL;
	CString	m_catchCopy;
	CString	m_description;
	CString	m_hotelAddress;
	CString	m_checkIn;
	CString	m_checkOut;
	CString	m_imageURL;
	CString	m_imageDescription;
	CString	m_textLink;
	CString	m_imageLink;
	CString	m_sid;
	CString	m_pid;
	CString	m_affiliateURL;
	//}}AFX_DATA

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHotelDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
    void    showHotelInfo();
    CString makeAffilateURL( CString trailerURL, CString targetURL );
    CString makeAffilateURLforXHTML( CString affiliateURL );
    CString wordrap( CString url );

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CHotelDialog)
	afx_msg void OnButtonBackward();
	afx_msg void OnButtonForward();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnAffiliateURL();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HOTELDIALOG_H__FACA5207_C3C8_4885_8BED_AFFC7353DD1D__INCLUDED_)
