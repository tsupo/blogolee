/*
 * EditAmazonAccessKey.h  : �u���O�N���C�A���g BloGolEe
 *      Amazon Access Key �ݒ�_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  1 Jun 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/EditAmazonAccessKey.h $
 * 
 * 1     09/06/02 3:49 tsupo
 * VSS�T�[�o���_��ύX
 * 
 * 2     09/06/01 21:40 Tsujimura543
 * Amazon Product Advertising API �Ή� (����m�F�ς�)
 * 
 * 1     09/06/01 20:05 Tsujimura543
 * �ŏ��̔�
 */

#if !defined(AFX_EDITAMAZONACCESSKEY_H__6B59DCE1_7D9F_47E9_99B8_CD531335EDC0__INCLUDED_)
#define AFX_EDITAMAZONACCESSKEY_H__6B59DCE1_7D9F_47E9_99B8_CD531335EDC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// EditAmazonAccessKey �_�C�A���O

class EditAmazonAccessKey : public CDialog
{
// �R���X�g���N�V����
public:
	EditAmazonAccessKey(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(EditAmazonAccessKey)
	enum { IDD = IDD_EDIT_AMAZON_ACCESS_KEY };
	CString	m_accessKeyID;
	CString	m_accessKeySecret;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(EditAmazonAccessKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(EditAmazonAccessKey)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_EDITAMAZONACCESSKEY_H__6B59DCE1_7D9F_47E9_99B8_CD531335EDC0__INCLUDED_)
