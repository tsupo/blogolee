/*
 * AddBlogInfoDlg.cpp : �u���O�N���C�A���g BloGolEe
 *      �u���O���ǉ��_�C�A���O
 *
 *          written by H.Tsujimura  18 Mar 2005 / 2 Mar 2007
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�����̂܂ܗ��p
 *
 * $Log: /comm/blogolee/AddBlogInfoDlg.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 11    09/03/23 17:51 Tsujimura543
 * Windows Live Spaces ����уE�F�u���u���O�� blogID �̈����Ɋւ���C��
 * 
 * 10    09/03/20 22:48 Tsujimura543
 * �͂Ăȃ_�C�A���[(�� Atom API �ł̓��e)�ɑΉ�����
 * 
 * 9     09/03/16 20:49 Tsujimura543
 * �E�F�u���u���O�� XMLRPC API �Ή���ƊJ�n
 * 
 * 8     07/11/30 2:03 Tsujimura543
 * (1) Jugem�A���v���O!�A�h���R���u���O�� XML-RPC API �o�R�ł͂Ȃ�����
 *     ���X���폜
 * (2) ���܂ɂĂ������L�֘A�̏��X���폜 (2007�N11��30���ŃT�[�r�X�I��)
 * 
 * 7     07/10/29 20:34 Tsujimura543
 * (1) XML-RPC API �o�R�ł� ���v���O! �ւ̃A�N�Z�X�ɑΉ�
 * (2) XML-RPC API �o�R�ł̃h���R���u���O�̃J�e�S���ꗗ�擾�A�J�e�S���ݒ�
 *     �ɑΉ�
 * 
 * 6     07/03/12 18:31 Tsujimura543
 * selectBlog() �𓱓����A���t�@�N�^�����O
 * 
 * 5     07/03/12 15:23 Tsujimura543
 * BLOGKIND�񋓑̂���l sweetBox ���폜
 * 
 * 4     07/03/12 5:07 Tsujimura543
 * Visual Studio 2005 �ł��r���h�ł���悤�ɃR�[�h���C��
 * 
 * 3     07/03/03 0:04 Tsujimura543
 * �s�v�ɂȂ����R�����g���폜
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#include "blogolee.h"
#include "AddBlogInfoDlg.h"
#include "EndPointDlg.h"
#include "BlogIDSelectDlg.h"
#include "utility.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/AddBlogInfoDlg.cpp 1     09/05/14 3:47 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddBlogInfoDlg �_�C�A���O


CAddBlogInfoDlg::CAddBlogInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddBlogInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddBlogInfoDlg)
	m_blogID = _T("");
	m_blogName = _T("");
	m_blogPassword = _T("");
	m_blogUserName = _T("");
	m_endpointURL = _T("");
	m_blogURL = _T("");
	//}}AFX_DATA_INIT

    m_blogInfo = NULL;
    m_blogKind = unset;
    m_useCbox  = false;
    m_mode     = true;
}


void CAddBlogInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddBlogInfoDlg)
	DDX_Control(pDX, IDC_COMBO_BLOG_LIST, m_blogKindList);
	DDX_Text(pDX, IDC_EDIT_BLOGID, m_blogID);
	DDV_MaxChars(pDX, m_blogID, 48);
	DDX_Text(pDX, IDC_EDIT_BLOGNAME, m_blogName);
	DDV_MaxChars(pDX, m_blogName, 127);
	DDX_Text(pDX, IDC_EDIT_BLOGPASSWORD, m_blogPassword);
	DDV_MaxChars(pDX, m_blogPassword, 16);
	DDX_Text(pDX, IDC_EDIT_BLOGUSERNAME, m_blogUserName);
	DDV_MaxChars(pDX, m_blogUserName, 32);
	DDX_Text(pDX, IDC_EDIT_ENDPOINTURL, m_endpointURL);
	DDV_MaxChars(pDX, m_endpointURL, 384);
	DDX_Text(pDX, IDC_EDIT_BLOGURL, m_blogURL);
	DDV_MaxChars(pDX, m_blogURL, 384);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddBlogInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CAddBlogInfoDlg)
	ON_BN_CLICKED(IDC_BUTTON_MOREINFO, OnButtonMoreInfo)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_BLOG_LIST, OnSelchangeComboBlogList)
	ON_EN_UPDATE(IDC_EDIT_BLOGUSERNAME, OnUpdateEditBlogUserName)
	ON_EN_UPDATE(IDC_EDIT_BLOGPASSWORD, OnUpdateEditBlogPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddBlogInfoDlg �ǉ����\�b�h

void    CAddBlogInfoDlg::switchEndpointURL()
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );

    if ( m_mode )
        m_endpointURL = "";

    if ( (m_blogKind == bloggerAPI)  ||
         (m_blogKind == metaWeblog)  ||
         (m_blogKind == mtAPI)       ||
         (m_blogKind == atomAPI)     ||
         (m_blogKind == newPostOnly)    )
        p->SetReadOnly( FALSE );
    else
        p->SetReadOnly( TRUE );

    if ( (m_blogKind == typepad)      ||
         (m_blogKind == typepadJapan) ||
         (m_blogKind == cocolog)      ||
         (m_blogKind == cocologFree)  ||
         (m_blogKind == blogzine)     ||
         (m_blogKind == newsHandler)  ||
         (m_blogKind == ameblo)       ||
         (m_blogKind == seesaa)       ||
         (m_blogKind == netLaputa)    ||
         (m_blogKind == blogG)        ||
         (m_blogKind == fc2blog)      ||
         (m_blogKind == gooBlog)      ||
         (m_blogKind == msnSpaces)    ||
         (m_blogKind == drecomX)      ||
         (m_blogKind == yaplogX)      ||
         (m_blogKind == jugemX)       ||
         (m_blogKind == webryX)       ||
         (m_blogKind == livedoor)     ||
         (m_blogKind == lovelog)      ||
         (m_blogKind == sonet)        ||
         (m_blogKind == vox)          ||
         (m_blogKind == hatena)       ||
         (m_blogKind == blogger)      ||
         (m_blogKind == movableType)     ) {
        int blogKindIndex = -1;
        int i;

        for ( i = 0; i < m_blogInfo->m_numOfBlogKinds; i++ ) {
            if ( m_blogInfo->m_blogKindInfo[i].blogKind == (blogKind)m_blogKind )
                break;
        }
        blogKindIndex = i;
        if ( m_endpointURL.GetLength() == 0 )
            m_endpointURL = m_blogInfo->m_blogKindInfo[blogKindIndex].endpointURL;
    }
    else
        m_endpointURL = "";

    p->SetWindowText( m_endpointURL );
}

void    CAddBlogInfoDlg::switchBlogID()
{
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );

    if ( m_mode )
        m_blogID = "";
    cp->SetWindowText( m_blogID );

    if ( m_useCbox ) {
        m_blogID = "0";
        cp->SetWindowText( m_blogID );
    }
    else if ( /* (m_blogKind == movableType)  || */
                 (m_blogKind == bloggerAPI)   ||
                 (m_blogKind == metaWeblog)   ||
                 (m_blogKind == mtAPI)        ||
                 (m_blogKind == atomAPI)         )
        cp->SetReadOnly( FALSE );
    /*
    else if ( (m_blogKind == typepad)      ||
              (m_blogKind == typepadJapan) ||
              (m_blogKind == cocolog)      ||
              (m_blogKind == cocologFree)  ||
              (m_blogKind == blogzine)     ||
              (m_blogKind == newsHandler)  ||
              (m_blogKind == ameblo)       ||
              (m_blogKind == seesaa)       ||
              (m_blogKind == netLaputa)    ||
              (m_blogKind == blogG)        ||
              (m_blogKind == fc2blog)      ||
              (m_blogKind == gooBlog)      ||
              (m_blogKind == msnSpaces)    ||
              (m_blogKind == drecomX)      ||
              (m_blogKind == yaplogX)      ||
              (m_blogKind == jugemX)       ||
              (m_blogKind == webryX)       ||
              (m_blogKind == livedoor)     ||
              (m_blogKind == lovelog)      ||
              (m_blogKind == sonet)        ||
              (m_blogKind == vox)          ||
              (m_blogKind == hatena)       ||
              (m_blogKind == blogger)         )
        cp->SetReadOnly( TRUE );
    */
    else
        cp->SetReadOnly( TRUE );
}

void    CAddBlogInfoDlg::switchBlogName()
{
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );

    if ( m_mode )
        m_blogName = "";

    if ( m_useCbox ) {
        m_blogName = "BlogPet ���甠";
        cp->SetReadOnly( TRUE );
    }
    else if ( /* (m_blogKind == movableType)  || */
                 (m_blogKind == bloggerAPI)   ||
                 (m_blogKind == metaWeblog)   ||
                 (m_blogKind == mtAPI)        ||
                 (m_blogKind == atomAPI)         )
        cp->SetReadOnly( FALSE );
    else if ( (m_blogKind == typepad)      ||
              (m_blogKind == typepadJapan) ||
              (m_blogKind == cocolog)      ||
              (m_blogKind == cocologFree)  ||
              (m_blogKind == blogzine)     ||
              (m_blogKind == newsHandler)  ||
              (m_blogKind == ameblo)       ||
              (m_blogKind == seesaa)       ||
              (m_blogKind == netLaputa)    ||
              (m_blogKind == blogG)        ||
              (m_blogKind == fc2blog)      ||
              (m_blogKind == gooBlog)      ||
              (m_blogKind == msnSpaces)    ||
              (m_blogKind == drecomX)      ||
              (m_blogKind == yaplogX)      ||
              (m_blogKind == jugemX)       ||
              (m_blogKind == webryX)       ||
              (m_blogKind == livedoor)     ||
              (m_blogKind == lovelog)      ||
              (m_blogKind == sonet)        ||
              (m_blogKind == vox)          ||
              (m_blogKind == hatena)       ||
              (m_blogKind == blogger)         ) {
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == kinugasa ) {
        m_blogName = "�L�k�K�T";
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == mixi ) {
        m_blogName = "mixi";
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == fc2network ) {
        m_blogName = "FC2NETWORK";
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == colors ) {
        m_blogName = "COLORS";
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == openPne ) {
        m_blogName = "OpenPNE";
        cp->SetReadOnly( TRUE );
    }
    else
        cp->SetReadOnly( TRUE );

    cp->SetWindowText( m_blogName );
}

void        CAddBlogInfoDlg::switchBlogURL()
{
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
    
    if ( m_mode )
        m_blogURL = "";

    if ( m_blogKind == kinugasa )
        m_blogURL = "http://kinugasa.cc/diary.php";
    else if ( m_blogKind == mixi )
        m_blogURL = "http://mixi.jp/list_diary.pl";
    else if ( m_blogKind == fc2network )
        m_blogURL = "http://network.fc2.com/diary/index.php";
    else if ( m_blogKind == colors )
        m_blogURL = "http://clrs.jp/list_diary.php";
    else if ( m_blogKind == openPne )
        m_blogURL = "http://openpne.jp/?m=pc&a=page_fh_diary_list";

    cp->SetWindowText( m_blogURL );
}

void    CAddBlogInfoDlg::switchMoreInfo()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_MOREINFO );

    if ( (m_blogKind == movableType)  ||
         (m_blogKind == bloggerAPI)   ||
         (m_blogKind == metaWeblog)   ||
         (m_blogKind == mtAPI)        ||
         (m_blogKind == atomAPI)      ||
         (m_blogKind == typepad)      ||
         (m_blogKind == typepadJapan) ||
         (m_blogKind == cocolog)      ||
         (m_blogKind == cocologFree)  ||
         (m_blogKind == blogzine)     ||
         (m_blogKind == newsHandler)  ||
         (m_blogKind == ameblo)       ||
         (m_blogKind == seesaa)       ||
         (m_blogKind == netLaputa)    ||
         (m_blogKind == blogG)        ||
         (m_blogKind == fc2blog)      ||
         (m_blogKind == gooBlog)      ||
         (m_blogKind == msnSpaces)    ||
         (m_blogKind == drecomX)      ||
         (m_blogKind == yaplogX)      ||
         (m_blogKind == jugemX)       ||
         (m_blogKind == webryX)       ||
         (m_blogKind == livedoor)     ||
         (m_blogKind == lovelog)      ||
         (m_blogKind == sonet)        ||
         (m_blogKind == vox)          ||
         (m_blogKind == hatena)       ||
         (m_blogKind == blogger)      ||
         (m_blogKind == exciteBlog)   ||
         (m_blogKind == echoo)        ||
         (m_blogKind == rakuten)         ) {
        if ( (m_blogUserName.GetLength() > 0) &&
             (m_blogPassword.GetLength() > 0)    )
            bp->EnableWindow( TRUE );
        else
            bp->EnableWindow( FALSE );
    }
    else
        bp->EnableWindow( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// CAddBlogInfoDlg ���b�Z�[�W �n���h��

void CAddBlogInfoDlg::OnButtonMoreInfo() 
{
	// �ǉ����擾
    CEdit   *p;

#define MAX_BLOGS       30  /* ����V�X�e�����ő�ݒu�\blog�� */

    if ( (m_blogKind == movableType) ||
         (m_blogKind == metaWeblog)  ||
         (m_blogKind == mtAPI)       ||
         (m_blogKind == atomAPI)        ) {
        // �G���h�|�C���gURL�̎����擾�����݂�
        //  -- �g�b�v�y�[�W URL ���擾
        char    topPageURL[MAX_URLLENGTH + 1];
        CEndPointDlg    dialog;
        int res = dialog.DoModal();
        if ( (res == IDOK) && (dialog.m_endPointURL.GetLength() > 0) ) {
            strcpy( topPageURL, (const char *)dialog.m_endPointURL );
            m_blogURL = topPageURL;
            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
            p->SetWindowText( m_blogURL );

            // -- �G���h�|�C���gURL �� blog ID ���擾
            char    id[MAX_BLOGIDLENGTH + 1];
            char    *url = NULL;

            memset( id, 0x00, MAX_BLOGIDLENGTH + 1 );
            if ( m_blogKind == atomAPI ) {
                CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
                url = getEndpointURLbyAutoDiscoveryOnAtomAPI(
                                                     topPageURL, id );
            }
            else {
                CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
                url = getEndpointURLbyAutoDiscovery( topPageURL, id );
            }

            if ( url && *url ) {
                MessageBox( "�G���h�|�C���gURL�̎擾�ɐ������܂����B    ",
                            "�擾����", MB_OK|MB_ICONINFORMATION );
                m_endpointURL = url;
                p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
                p->SetWindowText( m_endpointURL );

                if ( id[0] ) {
                    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
                    m_blogID = id;
                    p->SetWindowText( m_blogID );

                    // -- blog���̎擾
                    BLOGINF blogInfo[MAX_BLOGS];
                    int     numOfBlogs = MAX_BLOGS;
                    int     r;

                    setTargetURL( m_endpointURL );
                    if ( m_blogKind == atomAPI ) {
                        //  --- Atom API �n�̏ꍇ
                        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
                        r = getBlogIDsOnAtomAPI( m_blogUserName, m_blogPassword,
                                                 &numOfBlogs, blogInfo );
                    }
                    else {
                        //  --- blogger API �n�̏ꍇ
                        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
                        r = getBlogIDs( m_blogUserName, m_blogPassword,
                                        &numOfBlogs, blogInfo );    /* blogger API */
                    }

                    if ( r == 1 ) {
                        MessageBox( "blog���̎擾�ɐ������܂����B    ",
                                    "�擾����", MB_OK|MB_ICONINFORMATION );
                        m_blogName = utf2sjis( blogInfo[0].blogName );  /* �m�� */
                        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
                        p->SetWindowText( (const char *)m_blogName );
                    }
                    else if ( r > 1 ) {
                        for ( int i = 0; i < r; i++ ) {
                            if ( !strcmp( (const char *)m_blogID, blogInfo[i].blogID ) ) {
                                MessageBox( "blog���̎擾�ɐ������܂����B    ",
                                            "�擾����", MB_OK|MB_ICONINFORMATION );
                                m_blogName = utf2sjis( blogInfo[i].blogName );  /* �m�� */
                                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
                                p->SetWindowText( (const char *)m_blogName );
                                break;
                            }
                        }
                    }
                    else {
                        MessageBox( "blog���̎擾�Ɏ��s���܂����B\n\n"
                                    "���[�U���A�p�X���[�h�����������m�F���Ă��������B    ",
                                    "�ݒ�m�F", MB_OK|MB_ICONWARNING );
                    }
                }
            }
            else
                MessageBox( "�G���h�|�C���gURL�̎擾�Ɏ��s���܂����B\n\n"
                            "���[�U���A�p�X���[�h�����������m�F���Ă��������B    ",
                            "�ݒ�m�F", MB_OK|MB_ICONWARNING );
        }
    }
    else if ( (m_blogKind == bloggerAPI)   ||
              (m_blogKind == typepad)      ||
              (m_blogKind == typepadJapan) ||
              (m_blogKind == cocolog)      ||
              (m_blogKind == cocologFree)  ||
              (m_blogKind == blogzine)     ||
              (m_blogKind == newsHandler)  ||
              (m_blogKind == ameblo)       ||
              (m_blogKind == seesaa)       ||
              (m_blogKind == netLaputa)    ||
              (m_blogKind == blogG)        ||
              (m_blogKind == fc2blog)      ||
              (m_blogKind == gooBlog)      ||
              (m_blogKind == msnSpaces)    ||
              (m_blogKind == drecomX)      ||
              (m_blogKind == yaplogX)      ||
              (m_blogKind == jugemX)       ||
              (m_blogKind == webryX)       ||
              (m_blogKind == livedoor)     ||
              (m_blogKind == lovelog)      ||
              (m_blogKind == sonet)        ||
              (m_blogKind == vox)          ||
              (m_blogKind == hatena)       ||
              (m_blogKind == blogger)         ) {
        // blog ID �̎����擾�����݂�
        //  -- ������ blog �����݂���ꍇ�͈ꗗ�\�����A
        //     ���[�U�ɑI�����Ă��炤

        if ( m_blogPassword.GetLength() <= 0 ) {
            // blog ID �̎擾�ɂ̓p�X���[�h�K�{
            MessageBox( "blog ID �̎����擾�����݂܂��B\n"
                        "blog ID �̎����擾�ɂ́A�ublog ��login����"
                        "�Ƃ��̃p�X���[�h�v���K�v�ł��B    \n"
                        "blog ��login����Ƃ��̃p�X���[�h��ݒ肵��"
                        "���������B",
                        "�ݒ�m�F", MB_OK|MB_ICONWARNING );
            return;
        }

        BLOGINF blogInfo[MAX_BLOGS];
        int     numOfBlogs = MAX_BLOGS;
        int     r;

        /* --- ���e�\�� blog �ꗗ�̎擾 */
        if ( m_blogKind == jugemX ) {
            if ( m_blogUserName.GetLength() > 0 ) {
                char        url[MAX_URLLENGTH];
                const char  *q = strchr( m_endpointURL, '$' );

                if ( q )
                    q++;
                else
                    q = ".jugem.jp/admin/xmlrpc.php";
                sprintf( url, "http://%s%s",
                         (const char *)m_blogUserName,
                         q );

                m_endpointURL = url;
                p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
                p->SetWindowText( m_endpointURL );
            }
        }
        if ( m_blogKind == hatena ) {
            if ( strstr( m_endpointURL, "{hatenaID}" ) ) {
                m_endpointURL =
                    "http://d.hatena.ne.jp/" + m_blogUserName + "/atom/blog";
                p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
                p->SetWindowText( m_endpointURL );
            }
        }

        blogInfo[0].blogName[0] = NUL;
        setTargetURL( m_endpointURL );
        if ( (m_blogKind == livedoor) ||
             (m_blogKind == lovelog)  ||
             (m_blogKind == sonet)    ||
             (m_blogKind == ameblo)   ||
             (m_blogKind == vox)      ||
             (m_blogKind == hatena)   ||
             (m_blogKind == blogger)     ) {
            //  --- Atom API �n�̏ꍇ
            CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
            r = getBlogIDsOnAtomAPI( m_blogUserName, m_blogPassword,
                                     &numOfBlogs, blogInfo );
                    /* ���l: �{�Ƃ� blogger.com �ɑ΂��Ă� blogger API */
                    /*       �ł͂Ȃ� Atom API ��K�p����              */
        }
        else {
            //  --- blogger API �n�̏ꍇ
            CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
            r = getBlogIDs( m_blogUserName, m_blogPassword,
                            &numOfBlogs, blogInfo );    /* blogger API */
        }
        if ( (r >= 1) && (blogInfo[0].blogName[0] == NUL) ) {
            /* FC2BLOG �̂悤�Ɏ擾�Ɏ��s���Ă� r == 1 �ƂȂ� blog �΍� */
            MessageBox( "blog ID �̎擾�Ɏ��s���܂����B\n"
                        "���[�U���A�p�X���[�h�����������m�F���Ă��������B    ",
                        "�擾���s", MB_OK|MB_ICONWARNING );
        }
        else if ( r == 1 ) {
            MessageBox( "blog ID �̎擾�ɐ������܂����B    ",
                        "�擾����", MB_OK|MB_ICONINFORMATION );
            m_blogName = utf2sjis( blogInfo[0].blogName );  /* �m�� */
            m_blogID   = blogInfo[0].blogID;                /* �m�� */
            m_blogURL  = blogInfo[0].url;                   /* �m�� */

            if ( m_blogID == "" )
                if ( (m_blogKind == msnSpaces) ||
                     (m_blogKind == webryX)       )
                    m_blogID = "MyBlog";

            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
            p->SetWindowText( (const char *)m_blogName );

            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
            p->SetWindowText( (const char *)m_blogID );

            if ( !strncmp( m_blogURL, m_endpointURL, strlen(m_endpointURL) ) ) {
                if ( m_blogKind == livedoor )
                    m_blogURL = "http://blog.livedoor.jp/" + m_blogUserName + "/";
                if ( m_blogKind == lovelog )
                    m_blogURL = "http://blog.dion.ne.jp/" + m_blogUserName + "/";
                if ( m_blogKind == ameblo )
                    m_blogURL = "http://ameblo.jp/" + m_blogUserName + "/";
                if ( m_blogKind == sonet )
                    m_blogURL = "http://blog.so-net.ne.jp/" + m_blogUserName + "/";
            }
            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
            p->SetWindowText( m_blogURL );
        }
        else if ( r > 1 ) {
            /* ---- ���e�� blog �̑I�� */
            int rr = selectBlog( blogInfo, r );
            if ( (rr >= 0) && (rr < r) ) {
                r = rr;
                m_blogName = utf2sjis( blogInfo[r].blogName );  /* �m�� */
                m_blogID   = blogInfo[r].blogID;                /* �m�� */
                m_blogURL  = blogInfo[r].url;                   /* �m�� */

                if ( m_blogID == "" )
                    if ( (m_blogKind == msnSpaces) ||
                         (m_blogKind == webryX)       )
                        m_blogID = "MyBlog";

                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
                p->SetWindowText( (const char *)m_blogName );

                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
                p->SetWindowText( (const char *)m_blogID );

                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
                p->SetWindowText( m_blogURL );

                MessageBox( "blog ID �̎擾�ɐ������܂����B    ",
                            "�擾����", MB_OK|MB_ICONINFORMATION );
            }
        }
        else {
            MessageBox( "blog ID �̎擾�Ɏ��s���܂����B\n"
                        "���[�U���A�p�X���[�h�����������m�F���Ă��������B    ",
                        "�擾���s", MB_OK|MB_ICONWARNING );
        }
    }
    else if ( m_blogKind == newPostOnly ) {
        m_blogID = "0";
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
        p->SetWindowText( (const char *)m_blogID );
    }
    else if ( (m_blogKind == exciteBlog) ||
              (m_blogKind == echoo)      ||
              (m_blogKind == rakuten)       ) {
        BLOGINF blogInfo[MAX_BLOGS];
        int     numOfBlogs = MAX_BLOGS;
        int     r = 0;

        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

        switch ( m_blogKind ) {
        case exciteBlog:
            r = getBlogIDsExciteBlog( m_blogUserName, m_blogPassword,
                                      &numOfBlogs, blogInfo );
            break;

        case echoo:
            r = getBlogIDsEchoo( m_blogUserName, m_blogPassword,
                                 &numOfBlogs, blogInfo );
            break;

        case rakuten:
            r = getBlogIDsRakuten( m_blogUserName, m_blogPassword,
                                   &numOfBlogs, blogInfo );
            break;
        }

        if ( r == 1 ) {
            MessageBox( "blog URL �̎擾�ɐ������܂����B    ",
                        "�擾����", MB_OK|MB_ICONINFORMATION );

            m_blogURL  = blogInfo[0].url;
            m_blogName = blogInfo[0].blogName;

            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
            p->SetWindowText( (const char *)m_blogName );

            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
            p->SetWindowText( m_blogURL );

            if ( m_blogKind == exciteBlog ) {
                m_blogID = blogInfo[0].blogID;
                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
                p->SetWindowText( m_blogID );
            }
        }
        else if ( r <= 0 ) {
            MessageBox("blog URL �̎擾�Ɏ��s���܂����B"
                       "���[�U���A�p�X���[�h�����������m�F���Ă��������B    ",
                       "�擾���s", MB_OK|MB_ICONWARNING );
        }
    }
}

void CAddBlogInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        if ( m_blogInfo ) {
            m_blogKindList.InitStorage( BLOGOLEE_NUM_OF_BLOG_KINDS,
                                        BLOGOLEE_MAX_BLOG_NAME_LENGTH );
            m_blogKindList.ResetContent();
            for ( int i = 0; i < m_blogInfo->m_numOfBlogKinds; i++ ) {
                m_blogKindList.AddString( m_blogInfo->m_blogKindInfo[i].blogKindString );
            }
        }

        CEdit   *p;
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
        p->SetReadOnly( TRUE );
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
        p->SetReadOnly( TRUE );
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
        p->SetReadOnly( TRUE );
        p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
        p->SetReadOnly( TRUE );

        CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_MOREINFO );
        bp->EnableWindow( FALSE );

        if ( m_mode == false ) {
            long    location = -1;

            if ( (m_blogKind == newPostOnly) && (m_useCbox == true) ) {
                // �uBlogPet ���甠�v�̂��߂̓��ʏ���
                for ( location = 0; location < m_blogInfo->m_numOfBlogKinds; location++ ) {
                    if ( !strcmp( m_blogInfo->m_blogKindInfo[location].blogKindString,
                                  "BlogPet ���甠" ) )
                        break;
                }
            }
            else {
                for ( location = 0; location < m_blogInfo->m_numOfBlogKinds; location++ ) {
                    if ( m_blogKind == m_blogInfo->m_blogKindInfo[location].blogKind )
                        break;
                }
            }

            if ( (location >= 0) && (location < m_blogInfo->m_numOfBlogKinds) )
                m_blogKindList.SetCurSel( location );

            OnSelchangeComboBlogList();
            SetWindowText( "�o�^���C��" );
        }
    }
}

void CAddBlogInfoDlg::OnSelchangeComboBlogList() 
{
	int location = m_blogKindList.GetCurSel();

    m_blogKind = m_blogInfo->m_blogKindInfo[location].blogKind;

    if ( !strcmp( m_blogInfo->m_blogKindInfo[location].blogKindString, "BlogPet ���甠" ) )
        m_useCbox = true;
    else
        m_useCbox = false;

    switchBlogName();
    switchBlogURL();
    switchBlogID();
    switchEndpointURL();
    switchMoreInfo();
}

void CAddBlogInfoDlg::OnUpdateEditBlogUserName() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGUSERNAME );
    p->GetWindowText( m_blogUserName );

    switchMoreInfo();
}

void CAddBlogInfoDlg::OnUpdateEditBlogPassword() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGPASSWORD );
    p->GetWindowText( m_blogPassword );

    switchMoreInfo();
}

void CAddBlogInfoDlg::OnOK() 
{
    // ���͓��e�`�F�b�N
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGUSERNAME );
    p->GetWindowText( m_blogUserName );
    if ( m_blogUserName.GetLength() == 0 ) {
        MessageBox( "�u���[�U���A�܂��� ID�v��ݒ肵�Ă�������    ",
                    "�ݒ�m�F", MB_OK|MB_ICONWARNING );
        return;
    }

    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGPASSWORD );
    p->GetWindowText( m_blogPassword );
    if ( m_blogPassword.GetLength() == 0 ) {
        MessageBox( "�u�p�X���[�h�v��ݒ肵�Ă�������    ",
                    "�ݒ�m�F", MB_OK|MB_ICONWARNING );
        return;
    }

    if ( m_blogKind == unset ) {
        MessageBox( "�ublog �̎�ށv��ݒ肵�Ă�������    ",
                    "�ݒ�m�F", MB_OK|MB_ICONWARNING );
        return;
    }

    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
    p->GetWindowText( m_blogName );
    if ( m_blogName.GetLength() == 0 ) {
        if ( (m_blogKind == movableType)  ||
             (m_blogKind == bloggerAPI)   ||
             (m_blogKind == metaWeblog)   ||
             (m_blogKind == mtAPI)        ||
             (m_blogKind == atomAPI)      ||
             (m_blogKind == newPostOnly)  ||   
             (m_blogKind == typepad)      ||
             (m_blogKind == typepadJapan) ||
             (m_blogKind == cocolog)      ||
             (m_blogKind == cocologFree)  ||
             (m_blogKind == blogzine)     ||
             (m_blogKind == newsHandler)  ||
             (m_blogKind == ameblo)       ||
             (m_blogKind == seesaa)       ||
             (m_blogKind == netLaputa)    ||
             (m_blogKind == blogG)        ||
             (m_blogKind == fc2blog)      ||
             (m_blogKind == gooBlog)      ||
             (m_blogKind == msnSpaces)    ||
             (m_blogKind == drecomX)      ||
             (m_blogKind == yaplogX)      ||
             (m_blogKind == jugemX)       ||
             (m_blogKind == webryX)       ||
             (m_blogKind == livedoor)     ||
             (m_blogKind == lovelog)      ||
             (m_blogKind == sonet)        ||
             (m_blogKind == vox)          ||
             (m_blogKind == hatena)       ||
             (m_blogKind == blogger)      ||
             (m_blogKind == exciteBlog)   ||
             (m_blogKind == echoo)        ||
             (m_blogKind == rakuten)         ) {
            // �ǉ����擾
            OnButtonMoreInfo();
        }

        if ( m_blogName.GetLength() == 0 ) {
            MessageBox( "�ublog ���v��ݒ肵�Ă�������    ",
                        "�ݒ�m�F", MB_OK|MB_ICONWARNING );
            return;
        }
    }

    if ( (m_blogKind == movableType)  ||
         (m_blogKind == bloggerAPI)   ||
         (m_blogKind == metaWeblog)   ||
         (m_blogKind == mtAPI)        ||
         (m_blogKind == atomAPI)      ||
         (m_blogKind == newPostOnly)  ||   
         (m_blogKind == typepad)      ||
         (m_blogKind == typepadJapan) ||
         (m_blogKind == cocolog)      ||
         (m_blogKind == cocologFree)  ||
         (m_blogKind == blogzine)     ||
         (m_blogKind == newsHandler)  ||
         (m_blogKind == ameblo)       ||
         (m_blogKind == seesaa)       ||
         (m_blogKind == netLaputa)    ||
         (m_blogKind == blogG)        ||
         (m_blogKind == fc2blog)      ||
         (m_blogKind == gooBlog)      ||
         (m_blogKind == msnSpaces)    ||
         (m_blogKind == drecomX)      ||
         (m_blogKind == yaplogX)      ||
         (m_blogKind == jugemX)       ||
         (m_blogKind == webryX)       ||
         (m_blogKind == livedoor)     ||
         (m_blogKind == lovelog)      ||
         (m_blogKind == sonet)        ||
         (m_blogKind == vox)          ||
         (m_blogKind == hatena)       ||
         (m_blogKind == blogger)         ) {
        if ( m_blogID.GetLength() == 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
            p->GetWindowText( m_blogID );
            if ( m_blogID.GetLength() == 0 ) {
                MessageBox( "�ublog ID�v��ݒ肵�Ă�������    ",
                            "�ݒ�m�F", MB_OK|MB_ICONWARNING );
                return;
            }
        }

        if ( m_useCbox ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
            p->GetWindowText( m_endpointURL );
        }
        if ( m_endpointURL.GetLength() == 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
            p->GetWindowText( m_endpointURL );
            if ( m_endpointURL.GetLength() == 0 ) {
                MessageBox( "�u�G���h�|�C���gURL�v��ݒ肵�Ă�������    ",
                            "�ݒ�m�F", MB_OK|MB_ICONWARNING );
                return;
            }
        }
    }

	CDialog::OnOK();
}
