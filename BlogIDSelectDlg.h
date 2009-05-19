/*
 * BlogIDSelectDlg.h  : �u���O�N���C�A���g BloGolEe
 *      Blog ID �I���_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�����̂܂ܗ��p
 *
 * $Log: /comm/blogolee/BlogIDSelectDlg.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#if !defined(AFX_BLOGIDSELECTDLG_H__D8F46A4C_89A9_4DD9_9B52_7A7B750C75B6__INCLUDED_)
#define AFX_BLOGIDSELECTDLG_H__D8F46A4C_89A9_4DD9_9B52_7A7B750C75B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "blogoleeDlg.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "xmlRPC.h"
#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg �_�C�A���O

class CBlogIDSelectDlg : public CDialog
{
// �R���X�g���N�V����
private:
    BLOGINF *m_blogList;
    int     m_numOfBlogs;

    void    initBlogList( void );

public:
	CBlogIDSelectDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    ~CBlogIDSelectDlg() {
        if ( m_blogList )
            delete [] m_blogList;
    }

    void    initialize( BLOGINF *blogList, int numOfBlogs );

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CBlogIDSelectDlg)
	enum { IDD = IDD_BLOGID_DIALOG };
	CListBox	m_blogIDlist;
	int		m_blogIDlistIndex;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CBlogIDSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CBlogIDSelectDlg)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeListBlogid();
	afx_msg void OnDblclkListBlogID();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BLOGIDSELECTDLG_H__D8F46A4C_89A9_4DD9_9B52_7A7B750C75B6__INCLUDED_)
