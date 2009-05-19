/*
 * ProceedingDialog.cpp : �u���O�N���C�A���g BloGolEe
 *      �i�s�󋵕\���_�C�A���O �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  10 Nov 2005 / 9 Mar 2007
 *
 *  �u�\�[�V�����u�b�N�}�[�N�Ǘ��v���O�����v�Ŏg���Ă���\�[�X�R�[�h��
 *  ���̂܂ܗ��p
 *
 * $Log: /comm/blogolee/ProceedingDialog.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/03/09 20:13 Tsujimura543
 * bookey �̃\�[�X�𗬗p
 * 
 * ------------------------------------------------------------------------
 * �ȉ��́Abookey/ProceedingDialog.cpp �̕ύX����
 * ------------------------------------------------------------------------
 * 7     07/01/30 21:44 Tsujimura543
 * �R�����g���C��
 * 
 * 6     07/01/17 23:57 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 5     07/01/04 18:54 Tsujimura543
 * ShowWindow() �̈������C��
 * 
 * 4     06/07/11 18:15 Tsujimura543
 * �R�����g���C��
 * 
 * 3     06/07/11 18:14 Tsujimura543
 * SetFocus() ���݂̏C�������{ (�u���s���v�_�C�A���O�� focus ��������悤
 * �ɒ�������)
 * 
 * 2     06/07/03 23:37 Tsujimura543
 * ProceedingDialog �� DestroyWindow() ���ɗ�O���������邱�Ƃ����錏��
 * �b��Ώ������{ (�f�o�b�O�łł����������Ȃ�?)
 * 
 * 1     05/11/10 21:17 Tsujimura543
 * �V�K�쐬
 */

#include "blogolee.h"
#include "ProceedingDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/ProceedingDialog.cpp 1     09/05/14 3:47 tsupo $";
#endif

/////////////////////////////////////////////////////////////////////////////
// ProceedingDialog �_�C�A���O

ProceedingDialog::ProceedingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ProceedingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ProceedingDialog)
	//}}AFX_DATA_INIT
}


void ProceedingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProceedingDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ProceedingDialog, CDialog)
	//{{AFX_MSG_MAP(ProceedingDialog)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProceedingDialog �ǉ����\�b�h

void    ProceedingDialog::ChangeDialogText(
                const char *title,
                const char *message
            )
{
    SetWindowText( title );

    CStatic *sp = (CStatic *)GetDlgItem( IDC_STATIC_PROCEED_STRING );
    sp->SetWindowText( message );

    SetFocus();
}

void    ProceedingDialog::ResetDialogText()
{
    CString text;
    text.LoadString(IDS_TXT_CONTINUE_PROCEEDING);
    ChangeDialogText( text, text );
}

/////////////////////////////////////////////////////////////////////////////
// ProceedingDialog ���b�Z�[�W �n���h��

void ProceedingDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CButton *bp = (CButton *)GetDlgItem( IDCANCEL );
        bp->ShowWindow( SW_HIDE );
    }
}
