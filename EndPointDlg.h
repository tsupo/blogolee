/*
 * EndPointDlg.h : �u���O�N���C�A���g BloGolEe
 *      �G���h�|�C���gURL�ݒ�E�ҏW�_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�����̂܂ܗ��p
 *
 * $Log: /comm/blogolee/EndPointDlg.h $
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

#if !defined(AFX_ENDPOINTDLG_H__F9B8577B_82FC_4364_A132_CA5444A71003__INCLUDED_)
#define AFX_ENDPOINTDLG_H__F9B8577B_82FC_4364_A132_CA5444A71003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EndPointDlg.h : �w�b�_�[ �t�@�C��
//

#ifdef __cplusplus
extern "C" {
#endif
#include "xmlRPC.h"
#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CEndPointDlg �_�C�A���O

class CEndPointDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CEndPointDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CEndPointDlg)
	enum { IDD = IDD_ENDPOINT_DIALOG };
	CString	m_endPointURL;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CEndPointDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CEndPointDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ENDPOINTDLG_H__F9B8577B_82FC_4364_A132_CA5444A71003__INCLUDED_)
