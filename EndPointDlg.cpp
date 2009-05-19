/*
 * EndPointDlg.cpp : �u���O�N���C�A���g BloGolEe
 *      �G���h�|�C���gURL�ݒ�E�ҏW�_�C�A���O
 *
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�����̂܂ܗ��p
 *
 * $Log: /comm/blogolee/EndPointDlg.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/03/03 0:06 Tsujimura543
 * �s�v�ɂȂ����R�����g���폜
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#include "blogolee.h"
#include "EndPointDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/EndPointDlg.cpp 1     09/05/14 3:47 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEndPointDlg �_�C�A���O


CEndPointDlg::CEndPointDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEndPointDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEndPointDlg)
	m_endPointURL = _T("");
	//}}AFX_DATA_INIT
}


void CEndPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEndPointDlg)
	DDX_Text(pDX, IDC_EDIT_TOPPAGE_URL, m_endPointURL);
	DDV_MaxChars(pDX, m_endPointURL, 384);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEndPointDlg, CDialog)
	//{{AFX_MSG_MAP(CEndPointDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEndPointDlg ���b�Z�[�W �n���h��

void CEndPointDlg::OnOK() 
{
    char    url[MAX_URLLENGTH + 1];
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_TOPPAGE_URL );
    p->GetLine( 0, url, MAX_URLLENGTH );
    m_endPointURL = url;
    if ( m_endPointURL.GetLength() <= 0 )
        return;
	
	CDialog::OnOK();
}
