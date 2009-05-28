/*
 * blogoleeDlg.cpp : �u���O�N���C�A���g BloGolEe
 *      ���C���_�C�A���O
 *
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *      (�u�����������E�B�U�[�h�v�̃\�[�X carotDlg.cpp �𗬗p�A����)
 *
 * $Log: /comm/blogolee/blogoleeDlg.cpp $
 * 
 * 3     09/05/29 7:55 tsupo
 * 1.23��
 * 
 * 46    09/05/28 18:41 Tsujimura543
 * (1) �o�O�C�� (Amazon API �֘A�����Ń������j��)
 * (2) �o�b�t�@�I�[�o�[�����΍������
 * 
 * 45    09/05/27 22:19 Tsujimura543
 * Amazon API ����� �y�V API �֌W���A�b�v�f�[�g
 * (Amazon API �̔F�؂͖��Ή� �� xmlRPC.dll ���̑Ή��Ɠ����ɍ�Ɨ\��)
 * 
 * 2     09/05/27 1:47 tsupo
 * 1.22��
 * 
 * 44    09/05/26 21:52 Tsujimura543
 * tumblr �ւ̓��e�ɑΉ�
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 43    09/03/24 18:58 Tsujimura543
 * Windows Live Spaces �g���� metaWeblog API �̗p�u���O��
 * �u�J�e�S���ꗗ�擾�v�ɑΉ�
 * 
 * 42    09/03/23 17:51 Tsujimura543
 * Windows Live Spaces ����уE�F�u���u���O�� blogID �̈����Ɋւ���C��
 * 
 * 41    09/03/20 22:48 Tsujimura543
 * �͂Ăȃ_�C�A���[(�� Atom API �ł̓��e)�ɑΉ�����
 * 
 * 40    09/03/19 20:24 Tsujimura543
 * �E�F�u���u���O�̃e���v���[�g�֘A�������폜
 * 
 * 39    09/03/16 20:49 Tsujimura543
 * �E�F�u���u���O�� XMLRPC API �Ή���ƊJ�n
 * 
 * 38    08/02/18 23:11 Tsujimura543
 * copyright �\�����A�b�v�f�[�g
 * 
 * 37    08/02/18 23:08 Tsujimura543
 * �o�[�W�����������\�[�X����擾���ĕ\������悤�ɂ���
 * 
 * 36    07/12/05 23:17 Tsujimura543
 * unbase64() �̈����ǉ��ɔ����C�������{
 * 
 * 35    07/11/30 2:03 Tsujimura543
 * (1) Jugem�A���v���O!�A�h���R���u���O�� XML-RPC API �o�R�ł͂Ȃ�����
 *     ���X���폜
 * (2) ���܂ɂĂ������L�֘A�̏��X���폜 (2007�N11��30���ŃT�[�r�X�I��)
 * 
 * 34    07/10/29 21:03 Tsujimura543
 * getFoodCodeInfo() ���C���A�t�@�C���̒��g�����������ꍇ���Ď擾����
 * �悤�ɂ���
 * 
 * 33    07/10/29 20:34 Tsujimura543
 * (1) XML-RPC API �o�R�ł� ���v���O! �ւ̃A�N�Z�X�ɑΉ�
 * (2) XML-RPC API �o�R�ł̃h���R���u���O�̃J�e�S���ꗗ�擾�A�J�e�S���ݒ�
 *     �ɑΉ�
 * 
 * 32    07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 31    07/03/14 21:00 Tsujimura543
 * �R�����g���C��
 * 
 * 30    07/03/14 20:57 Tsujimura543
 * proxy�ݒ�Ɍ�肪����Ǝv����ꍇ�́A�ēx�A�ݒ肵�������Ƃ��ł���悤
 * �ɂ������񏉊���Ԃɖ߂��悤�ɂ���
 * 
 * 29    07/03/14 0:08 Tsujimura543
 * ���C���_�C�A���O�Ƒ�2���C���_�C�A���O�̊Ԃ̘A�g�@�\������
 * 
 * 28    07/03/13 23:46 Tsujimura543
 * OnButtonSmall() �̏������e��ύX
 * 
 * 27    07/03/13 21:16 Tsujimura543
 * �u�������߁v���i�̌f�ڌ�����ς��邱�Ƃ��ł���悤�ɂ���
 * (+ �f�t�H���g�̌f�ڌ�����10������4���ɕύX)
 * 
 * 26    07/03/13 19:56 Tsujimura543
 * proxy�ݒ���� BlogoleeApp ���ɕێ�����悤�ɂ���
 * 
 * 25    07/03/12 18:31 Tsujimura543
 * selectBlog() �𓱓����A���t�@�N�^�����O
 * 
 * 24    07/03/12 16:06 Tsujimura543
 * �������t�@�N�^�����O
 * 
 * 23    07/03/12 15:55 Tsujimura543
 * BLOGKIND �֘A�̕\�L�𓝈� (enum blogKind �Ə����Ă���Aint �Ə����Ă���
 * ���Ă���)
 * 
 * 22    07/03/12 15:37 Tsujimura543
 * (1) encodeParameter() �� decodeParameter() �� utility.{h,cpp} �ֈړ�
 * (2) ��L�ɑΉ����� freeParameter() ��ʓr�p��
 * 
 * 21    07/03/12 15:23 Tsujimura543
 * BLOGKIND�񋓑̂���l sweetBox ���폜
 * 
 * 20    07/03/12 5:08 Tsujimura543
 * (1) Visual Studio 2005 �ł��r���h�ł���悤�ɃR�[�h���C��
 * (2) �ꕔ�̃_�C�A���O�̕������C��
 * 
 * 19    07/03/10 22:11 Tsujimura543
 * (1) SweetBox Blog �͂��łɃT�[�r�X�I�����Ă���Ƃ̂��ƂŁA�{�c�[����
 *     �T�|�[�g�Ώۃu���O����O����
 * (2) ������.net ���烁���e���Ȃǂ̗��R�ŃG���[�������Ԃ��Ă����ꍇ�A
 *     �G���[�������Ɋ܂܂�郁�b�Z�[�W��\������悤�ɂ���
 * 
 * 18    07/03/10 6:17 Tsujimura543
 * ProceedingDialog::ChangeDialogText() �ɓn�������̏������t�������̂��C��
 * 
 * 17    07/03/09 21:26 Tsujimura543
 * proxy���̐ݒ肪�Ԉ���Ă���ꍇ�̑Ώ���ǉ�
 * 
 * 16    07/03/09 20:23 Tsujimura543
 * ProceedingDialog �𓱓�
 * 
 * 15    07/03/09 19:34 Tsujimura543
 * proxy���̎擾�A�ݒ�^�C�~���O�� CBlogoleeDlg �_�C�A���O��
 * OnShowWindow() ���s�J�n�ȍ~�ɕύX
 * 
 * 14    07/03/08 23:09 Tsujimura543
 * �R�����g���C��
 * 
 * 13    07/03/08 23:08 Tsujimura543
 * (1) �f�[�^�t�@�C�����S���Ȃ���ԂŋN�������Ƃ��̋����������������ɂ�
 *     �ďC��
 * (2) ���[�U�C���^�[�t�F�[�X�������
 * 
 * 12    07/03/07 22:43 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 11    07/03/07 22:40 Tsujimura543
 * �u�z�e�����_�C�A���O�v(������.net�̃A�t�B���G�C�g�����N�Ή�)���Ă�
 * �o���@�\������
 * 
 * 10    07/03/07 15:37 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 9     07/03/07 0:47 Tsujimura543
 * ������̃A�t�B���G�C�g���������{�̈ȊO�́A�قڎ�������
 * 
 * 8     07/03/06 6:06 Tsujimura543
 * makeXsltOfSearchResult() ��ǉ�
 * 
 * 7     07/03/06 4:42 Tsujimura543
 * makeXmlOfSearchResult() ��ǉ�
 * 
 * 6     07/03/06 3:40 Tsujimura543
 * �u�z�b�g�y�b�p�[�v�̃O�����T�[�`�������I�ɓ���
 * 
 * 5     07/03/06 1:39 Tsujimura543
 * �ݒ�t�@�C���ǂݎ�菈�����C��
 * (�y�V�A�t�B���G�C�gID��ǂޕ����̈������)
 * 
 * 4     07/03/06 0:36 Tsujimura543
 * (1) �o�b�t�@�[�I�[�o�[�����΍�����{
 * (2) ���e�������Ƀ��C���_�C�A���O�̍ĕ`�悪�ł���悤�ɓ��e������
 *     �ʃX���b�h������
 * 
 * 3     07/03/03 1:06 Tsujimura543
 * switchArticleKeyword(), switchArticleExtended(), switchArticleSummary()
 * ��ǉ�
 * 
 * 2     07/03/03 0:44 Tsujimura543
 * ���e����(�N���������b)�̎w��@�\�͂�������p�~����
 * [���e�����͏�Ɍ��ݎ����ƂȂ�]
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#include "blogolee.h"
#include "blogoleeDlg.h"
#include "AboutDlg.h"
#include "EndPointDlg.h"
#include "BlogIDSelectDlg.h"
#include "EditBlogInfoDlg.h"
#include "AddBlogInfoDlg.h"
#include "confirmProxy.h"
#include "ProxyInfoDialog.h"
#include "ProceedingDialog.h"
#include "HotelDialog.h"
#include "hotelInfo.h"
#include "BlogoleeMini.h"
#include "utility.h"
#include <sys/stat.h>
#include <direct.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/blogoleeDlg.cpp 3     09/05/29 7:55 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeDlg �_�C�A���O

CBlogoleeDlg::CBlogoleeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlogoleeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlogoleeDlg)
	m_blogPassword = _T("");
	m_blogUserName = _T("");
	m_endpointURL = _T("");
	m_blogID = _T("");
	m_associateID = _T("");
	m_categoryName = _T("");
	m_blogName = _T("");
	m_blogURL = _T("");
	m_rakuten_affiliateID = _T("");
	m_article_title = _T("");
	m_article_keyword = _T("");
	m_article_summary = _T("");
	m_article_description = _T("");
	m_article_extended = _T("");
	m_foodKeyword = _T("");
	m_foodName = _T("");
	m_sid = _T("");
	m_pidForJalan = _T("");
	//}}AFX_DATA_INIT

    m_blogKind = unset;
    m_keyword  = false;
    strcpy( m_settingDir,   "setting" );
    strcpy( m_settingFile,  "blogolee.inf" );
    strcpy( m_blogInfoFile, "blogList.inf" );
    m_editorPath[0]   = NULL;
    m_currentBlogID   = 0;
    m_numOfFoodCodes  = 0;
    m_foodCodeInfo    = NULL;
    m_foodCode[0]     = NUL;
    m_numOfAreaCodes  = 0;
    m_areaCodeInfo    = NUL;
    m_prefCode        = -1;
    m_hotelTypeNum    = -1;
    m_areaCode[0]     = NUL;
    m_numOfRecomended = DEFAULT_RECOMENDED_ITEMS;
    m_initialized     = false;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
}

void CBlogoleeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlogoleeDlg)
	DDX_Control(pDX, IDC_COMBO_HOTEL_TYPE, m_hotelType);
	DDX_Control(pDX, IDC_COMBO_AREA_LIST2, m_areaList2);
	DDX_Control(pDX, IDC_COMBO_AREA_LIST, m_areaList);
	DDX_Control(pDX, IDC_COMBO_FOODCD, m_foodeCodeList);
	DDX_Control(pDX, IDC_COMBO_BLOGKIND, m_blogKindList);
	DDX_Control(pDX, IDC_LIST_CATEGORY, m_categoryList);
	DDX_Text(pDX, IDC_EDIT_BLOG_PASSWORD, m_blogPassword);
	DDV_MaxChars(pDX, m_blogPassword, 16);
	DDX_Text(pDX, IDC_EDIT_BLOG_USERNAME, m_blogUserName);
	DDV_MaxChars(pDX, m_blogUserName, 80);
	DDX_Text(pDX, IDC_EDIT_ENDPOINT_URL, m_endpointURL);
	DDV_MaxChars(pDX, m_endpointURL, 384);
	DDX_Text(pDX, IDC_EDIT_BLOG_ID, m_blogID);
	DDV_MaxChars(pDX, m_blogID, 48);
	DDX_Text(pDX, IDC_EDIT_ASSOCIATE_ID, m_associateID);
	DDV_MaxChars(pDX, m_associateID, 20);
	DDX_LBString(pDX, IDC_LIST_CATEGORY, m_categoryName);
	DDX_Text(pDX, IDC_EDIT_BLOG_NAME, m_blogName);
	DDV_MaxChars(pDX, m_blogName, 127);
	DDX_Text(pDX, IDC_EDIT_BLOG_URL, m_blogURL);
	DDV_MaxChars(pDX, m_blogURL, 384);
	DDX_Text(pDX, IDC_EDIT_RAKUTEN_ID, m_rakuten_affiliateID);
	DDV_MaxChars(pDX, m_rakuten_affiliateID, 64);
	DDX_Text(pDX, IDC_EDIT_ARTICLE_TITLE, m_article_title);
	DDV_MaxChars(pDX, m_article_title, 128);
	DDX_Text(pDX, IDC_EDIT_ARTICLE_KEYWORD, m_article_keyword);
	DDV_MaxChars(pDX, m_article_keyword, 128);
	DDX_Text(pDX, IDC_EDIT_ARTICLE_SUMMARY, m_article_summary);
	DDV_MaxChars(pDX, m_article_summary, 512);
	DDX_Text(pDX, IDC_EDIT_ARTICLE, m_article_description);
	DDV_MaxChars(pDX, m_article_description, 65536);
	DDX_Text(pDX, IDC_EDIT_ARTICLE_EXTENDED, m_article_extended);
	DDV_MaxChars(pDX, m_article_extended, 65536);
	DDX_Text(pDX, IDC_EDIT_FOOD_KEYWORD, m_foodKeyword);
	DDV_MaxChars(pDX, m_foodKeyword, 80);
	DDX_CBString(pDX, IDC_COMBO_FOODCD, m_foodName);
	DDV_MaxChars(pDX, m_foodName, 80);
	DDX_Text(pDX, IDC_EDIT_JALAN_SID, m_sid);
	DDV_MaxChars(pDX, m_sid, 12);
	DDX_Text(pDX, IDC_EDIT_JALAN_PID, m_pidForJalan);
	DDV_MaxChars(pDX, m_pidForJalan, 12);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBlogoleeDlg, CDialog)
	//{{AFX_MSG_MAP(CBlogoleeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnExecutePostArticle)
	ON_BN_CLICKED(IDC_RADIO_KEYWORD_ON, OnRadioKeywordOn)
	ON_BN_CLICKED(IDC_RADIO_KEYWORD_OFF, OnRadioKeywordOff)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDCANCEL, OnExit)
	ON_BN_CLICKED(IDC_RADIO_SIMILARITY_ON, OnRadioSimlarityOn)
	ON_BN_CLICKED(IDC_RADIO_SIMILARITY_OFF, OnRadioSimilarityOff)
	ON_EN_KILLFOCUS(IDC_EDIT_ASSOCIATE_ID, OnKillfocusEditAssociateId)
	ON_BN_CLICKED(IDC_BUTTON_GET_CATEGORIES, OnButtonGetCategories)
	ON_LBN_SELCHANGE(IDC_LIST_CATEGORY, OnSelchangeListCategory)
	ON_CBN_SELCHANGE(IDC_COMBO_BLOGKIND, OnSelchangeComboBlogKind)
	ON_EN_KILLFOCUS(IDC_EDIT_ENDPOINT_URL, OnKillfocusEditEndpointURL)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH_BLOG, OnButtonSwitchBlog)
	ON_EN_KILLFOCUS(IDC_EDIT_BLOG_USERNAME, OnKillfocusEditBlogUsername)
	ON_EN_KILLFOCUS(IDC_EDIT_BLOG_PASSWORD, OnKillfocusEditBlogPassword)
	ON_EN_KILLFOCUS(IDC_EDIT_BLOG_ID, OnKillfocusEditBlogID)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_BLOG, OnButtonBrowseBlog)
	ON_EN_KILLFOCUS(IDC_EDIT_RAKUTEN_ID, OnKillfocusEditRakutenId)
	ON_EN_KILLFOCUS(IDC_EDIT_ARTICLE_KEYWORD, OnKillfocusEditArticleKeyword)
	ON_EN_KILLFOCUS(IDC_EDIT_ARTICLE_SUMMARY, OnKillfocusEditArticleSummary)
	ON_EN_KILLFOCUS(IDC_EDIT_ARTICLE_EXTENDED, OnKillfocusEditArticleExtended)
	ON_BN_CLICKED(IDC_BUTTON_FOOD_SEARCH, OnButtonFoodSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_FOODCD, OnSelchangeComboFoodcd)
	ON_EN_KILLFOCUS(IDC_EDIT_FOOD_KEYWORD, OnKillfocusEditFoodKeyword)
	ON_BN_CLICKED(IDC_WEB_HOTPEPPER, OnWebHotpepper)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_WEB_JALAN, OnWebJalan)
	ON_CBN_SELCHANGE(IDC_COMBO_AREA_LIST, OnSelchangeComboAreaList)
	ON_CBN_SELCHANGE(IDC_COMBO_AREA_LIST2, OnSelchangeComboAreaList2)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTEL_TYPE, OnSelchangeComboHotelType)
	ON_BN_CLICKED(IDC_BUTTON_HOTEL_SEARCH, OnButtonHotelSearch)
	ON_BN_CLICKED(IDC_BUTTON_JALAN_LINK, OnButtonJalanLink)
	ON_EN_UPDATE(IDC_EDIT_JALAN_SID, OnUpdateEditJalanSid)
	ON_EN_UPDATE(IDC_EDIT_JALAN_PID, OnUpdateEditJalanPid)
	ON_EN_UPDATE(IDC_EDIT_ARTICLE_TITLE, OnUpdateEditArticleTitle)
	ON_EN_UPDATE(IDC_EDIT_ARTICLE, OnUpdateEditArticle)
	ON_BN_CLICKED(IDC_BUTTON_SMALL, OnButtonSmall)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_BUTTON_PROXY, OnButtonProxy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeDlg �ǉ����\�b�h

bool    CBlogoleeDlg::allocateBlogInfo()
{
    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();

    if ( cp->m_numOfBlogs == 0 ) {
        cp->m_blogList = new CBlogoleeApp::blogList [MAX_NUM_OF_BLOGS];
        if ( cp->m_blogList == NULL )
            return ( false );

        for ( long i = 0; i < MAX_NUM_OF_BLOGS; i++ ) {
            cp->m_blogList[i].blogKind         = unset;
            cp->m_blogList[i].blogName[0]      = NUL;
            cp->m_blogList[i].blogUsername[0]  = NUL;
            cp->m_blogList[i].blogPassword[0]  = NUL;
            cp->m_blogList[i].blogID[0]        = NUL;
            cp->m_blogList[i].blogURL[0]       = NUL;
            cp->m_blogList[i].endpointURL[0]   = NUL;
            cp->m_blogList[i].numOfCategories  = 0;
            cp->m_blogList[i].catagory         = NULL;
        }

        return ( true );
    }

    return ( false );
}

void    CBlogoleeDlg::switchKeyword( bool value )
{
    CButton *p;

    if ( value == true ) {
        p = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_ON );
        p->SetCheck( 1 );

        p = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_OFF );
        p->SetCheck( 0 );

        m_keyword = true;
    }
    else {
        p = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_OFF );
        p->SetCheck( 1 );

        p = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_ON );
        p->SetCheck( 0 );

        m_keyword = false;
    }
}

void    CBlogoleeDlg::switchSimilarity( bool value )
{
    CButton *p;

    if ( /*
         (m_blogKind == ameblo)     || */
         (m_blogKind == exciteBlog) ||
         (m_blogKind == mixi)       ||
         (m_blogKind == kinugasa)   ||
         (m_blogKind == fc2network) ||
         (m_blogKind == echoo)      ||
         (m_blogKind == colors)     ||
         (m_blogKind == openPne)    ||
         (m_blogKind == rakuten) /* ||
         (m_blogKind == webry)   */    ) {
        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_ON );
        p->EnableWindow( FALSE );

        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_OFF );
        p->EnableWindow( FALSE );
        value = false;
    }
    else {
        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_ON );
        p->EnableWindow( TRUE );

        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_OFF );
        p->EnableWindow( TRUE );
    }

    if ( value == true ) {
        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_ON );
        p->SetCheck( 1 );

        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_OFF );
        p->SetCheck( 0 );

        m_similarity = true;
    }
    else {
        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_OFF );
        p->SetCheck( 1 );

        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_ON );
        p->SetCheck( 0 );

        m_similarity = false;
    }

    switchAssociateID( value );
    switchAffiliateID( value );
}

void    CBlogoleeDlg::switchAssociateID( bool value )
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ASSOCIATE_ID );
    p->SetReadOnly( value == true ? FALSE : TRUE );
    p->SetWindowText( m_associateID );
}

void    CBlogoleeDlg::switchAffiliateID( bool value )
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_RAKUTEN_ID );
    p->SetReadOnly( value == true ? FALSE : TRUE );
    p->SetWindowText( m_rakuten_affiliateID );
}


void    CBlogoleeDlg::switchEndpointURL( int blogKindIndex /* = -1 */ )
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );

    if ( (m_blogKind == movableType) ||
         (m_blogKind == bloggerAPI)  ||
         (m_blogKind == metaWeblog)  ||
         (m_blogKind == mtAPI)       ||
         (m_blogKind == atomAPI)     ||
         (m_blogKind == newPostOnly)    ) {    
     // m_endpointURL = "";
        p->SetReadOnly( FALSE );
    }
    else {
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
             (m_blogKind == blogger)         ) {
            if ( blogKindIndex == -1 ) {
                int i;
                for ( i = 0; i < m_numOfBlogKinds; i++ ) {
                    if ( m_blogKindInfo[i].blogKind == m_blogKind )
                        break;
                }
                blogKindIndex = i;
            }
            m_endpointURL = m_blogKindInfo[blogKindIndex].endpointURL;
        }
        else
            m_endpointURL = "";
    }

    p->SetWindowText( m_endpointURL );

    bool    buttonStatus = true;
    CButton *bp = (CButton *)GetDlgItem( IDOK );
    if ( m_endpointURL.GetLength() <= 0 )
        if ( (m_blogKind == movableType) ||
             (m_blogKind == metaWeblog)  ||
             (m_blogKind == mtAPI)       ||
             (m_blogKind == atomAPI)        )
            buttonStatus = false;
    if ( buttonStatus == false )
        bp->SetWindowText( "�G���h�|�C���gURL�擾" );
    else
        bp->SetWindowText( "���e" );
}

void    CBlogoleeDlg::switchBlogID( const char *blogID /* = NULL */ )
{
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_ID );
    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_GET_CATEGORIES );
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
         (m_blogKind == seesaa)       ||
         (m_blogKind == netLaputa)    ||
         (m_blogKind == blogG)        ||
         (m_blogKind == fc2blog)      ||
         (m_blogKind == gooBlog)      ||
         (m_blogKind == msnSpaces)    ||
         (m_blogKind == webryX)       ||
         (m_blogKind == drecomX)      ||
         (m_blogKind == yaplogX)      ||
         (m_blogKind == jugemX)       ||
         (m_blogKind == livedoor)     ||
         (m_blogKind == lovelog)   /* ||
         (m_blogKind == ameblo)       ||
         (m_blogKind == sonet)        ||
         (m_blogKind == vox)          ||
         (m_blogKind == hatena)       ||
         (m_blogKind == blogger)   */     ) {
            /* ����: So-net blog, Blogger.com, �A���[�o�u���O �ł� Atom API */
            /*       �ɂ��J�e�S���̎擾�͍��̂Ƃ���T�|�[�g����Ă��Ȃ�   */
        if ( blogID && *blogID )
            m_blogID = blogID;
        else
            m_blogID = "";
        cp->SetWindowText( (const char *)m_blogID );
        cp->SetReadOnly( FALSE );

        // �u�J�e�S���ꗗ�擾�v�{�^���� enable �ɂ���
        bp->EnableWindow( TRUE );
    }
    else if ( (m_blogKind == echoo)      ||
              (m_blogKind == exciteBlog) ||
              (m_blogKind == rakuten)       ) {
        m_blogID = "";
        cp->SetWindowText( "" );
        cp->SetReadOnly( TRUE );

        // �u�J�e�S���ꗗ�擾�v�{�^���� enable �ɂ���
        bp->EnableWindow( TRUE );
    }
    else {
        if ( m_blogKind == newPostOnly ) {
            if ( blogID && *blogID )
                m_blogID = blogID;
            else
                m_blogID = "";
        }
        else
            m_blogID = "";
        cp->SetWindowText( "" );
        cp->SetReadOnly( TRUE );

        // �u�J�e�S���ꗗ�擾�v�{�^���� disable �ɂ���
        bp->EnableWindow( FALSE );
    }

    switchSimilarity( m_similarity );
    m_categoryList.ResetContent();
    m_categoryName = "";
}

void    CBlogoleeDlg::switchBlogInfo()
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_NAME );
    p->SetWindowText( m_blogName );

    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_USERNAME );
    p->SetWindowText( (const char *)m_blogUserName );

    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_PASSWORD );
    p->SetWindowText( (const char *)m_blogPassword );
    if ( m_blogPassword.GetLength() == 0 ) {
        MessageBox( "blog �̃p�X���[�h��ݒ肵�����ĉ������B    ",
                    "�p�X���[�h�Đݒ�", MB_OK|MB_ICONWARNING );
    }

    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_ID );
    p->SetWindowText( (const char *)m_blogID );

    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_URL );
    p->SetWindowText( (const char *)m_blogURL );

    p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );
    p->SetWindowText( (const char *)m_endpointURL );

    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    if ( cp->m_blogList ) {
        int i = -1;

        if ( (m_blogKind == newPostOnly) &&
             (cp->m_blogList[m_currentBlogID].useCbox == true) ) {
            // �uBlogPet ���甠�v�̂��߂̓��ʏ���
            for ( i = 0; i < m_numOfBlogKinds; i++ ) {
                if ( !strcmp( m_blogKindInfo[i].blogKindString,
                              "BlogPet ���甠" ) )
                    break;
            }
        }
        else {
            for ( i = 0; i < m_numOfBlogKinds; i++ ) {
                if ( cp->m_blogList[m_currentBlogID].blogKind == 
                                                m_blogKindInfo[i].blogKind )
                    break;
            }
        }

        if ( (i >= 0) && (i < m_numOfBlogKinds) )
            m_blogKindList.SetCurSel( i );
    }

    if ( m_categoryName.GetLength() > 0 ) {
        CString str;
        for ( int i = 0; i < m_categoryList.GetCount(); i++ ) {
            m_categoryList.GetText( i, str );
            if ( !strcmp( m_categoryName, (const char *)str ) ) {
                m_categoryList.SetCurSel( i );
                break;
            }
        }
    }
}

void    CBlogoleeDlg::switchBrowseBlog()
{
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_BROWSE_BLOG );

    if ( m_blogURL.GetLength() > 0 )
        p->SetWindowText( "blog ������" );
    else
        p->SetWindowText( "blog���擾" );

    p->EnableWindow( TRUE );
}

void    CBlogoleeDlg::initBlogKindList()
{
    int cnt = 0;

    m_numOfBlogKinds = 0;

    m_blogKindInfo[cnt].blogKind       = typepad;
    m_blogKindInfo[cnt].blogKindString = "TypePad(, France, Germany)";
    m_blogKindInfo[cnt].blogKindID     = "typepad";
    m_blogKindInfo[cnt].endpointURL    = APIURL_TYPEPAD;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = typepadJapan;
    m_blogKindInfo[cnt].blogKindString = "TypePad Japan";
    m_blogKindInfo[cnt].blogKindID     = "typepadJapan";
    m_blogKindInfo[cnt].endpointURL    = APIURL_TYPEPADJAPAN;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = cocolog;
    m_blogKindInfo[cnt].blogKindString = "�R�R���O";
    m_blogKindInfo[cnt].blogKindID     = "cocolog";
    m_blogKindInfo[cnt].endpointURL    = APIURL_COCOLOG;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = cocologFree;
    m_blogKindInfo[cnt].blogKindString = "�R�R���O�t���[";
    m_blogKindInfo[cnt].blogKindID     = "cocologFree";
    m_blogKindInfo[cnt].endpointURL    = APIURL_COCOLOGFREE;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = blogzine;
    m_blogKindInfo[cnt].blogKindString = "�u���O�l";
    m_blogKindInfo[cnt].blogKindID     = "blogzine";
    m_blogKindInfo[cnt].endpointURL    = APIURL_BLOGZINE;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = newsHandler;
    m_blogKindInfo[cnt].blogKindString = "News-Handler";
    m_blogKindInfo[cnt].blogKindID     = "newsHandler";
    m_blogKindInfo[cnt].endpointURL    = APIURL_NEWSHANDLER;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = seesaa;
    m_blogKindInfo[cnt].blogKindString = "Seesaa BLOG";
    m_blogKindInfo[cnt].blogKindID     = "seesaa";
    m_blogKindInfo[cnt].endpointURL    = APIURL_SEESAABLOG_SEC;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = netLaputa;
    m_blogKindInfo[cnt].blogKindString = "NetLaputa BLOG";
    m_blogKindInfo[cnt].blogKindID     = "netLaputa";
    m_blogKindInfo[cnt].endpointURL    = APIURL_NETLAPUTA;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = blogG;
    m_blogKindInfo[cnt].blogKindString = "269g";
    m_blogKindInfo[cnt].blogKindID     = "blogG";
    m_blogKindInfo[cnt].endpointURL    = APIURL_269G;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = livedoor;
    m_blogKindInfo[cnt].blogKindString = "livedoor Blog";
    m_blogKindInfo[cnt].blogKindID     = "livedoor";
    m_blogKindInfo[cnt].endpointURL    = ATOMURL_LIVEDOOR_200507;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = lovelog;
    m_blogKindInfo[cnt].blogKindString = "LOVELOG";
    m_blogKindInfo[cnt].blogKindID     = "lovelog";
    m_blogKindInfo[cnt].endpointURL    = ATOMURL_LOVELOG;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = sonet;
    m_blogKindInfo[cnt].blogKindString = "So-net blog";
    m_blogKindInfo[cnt].blogKindID     = "sonet";
    m_blogKindInfo[cnt].endpointURL    = ATOMURL_SONET;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = blogger;
    m_blogKindInfo[cnt].blogKindString = "Blogger";
    m_blogKindInfo[cnt].blogKindID     = "blogger";
    m_blogKindInfo[cnt].endpointURL    = ATOMURL_BLOGGER;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = vox;
    m_blogKindInfo[cnt].blogKindString = "Vox";
    m_blogKindInfo[cnt].blogKindID     = "vox";
    m_blogKindInfo[cnt].endpointURL    = ATOMURL_VOX;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = movableType;
    m_blogKindInfo[cnt].blogKindString = "Movable Type";
    m_blogKindInfo[cnt].blogKindID     = "movableType";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = bloggerAPI;
    m_blogKindInfo[cnt].blogKindString = "blogger API �T�|�[�g";
    m_blogKindInfo[cnt].blogKindID     = "bloggerAPI";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = metaWeblog;
    m_blogKindInfo[cnt].blogKindString = "metaWeblog API �T�|�[�g";
    m_blogKindInfo[cnt].blogKindID     = "metaWeblog";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = mtAPI;
    m_blogKindInfo[cnt].blogKindString = "MovableType API �T�|�[�g";
    m_blogKindInfo[cnt].blogKindID     = "mtAPI";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = atomAPI;
    m_blogKindInfo[cnt].blogKindString = "Atom API �T�|�[�g blog";
    m_blogKindInfo[cnt].blogKindID     = "atomAPI";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = newPostOnly;
    m_blogKindInfo[cnt].blogKindString = "metaWeblog.newPost �̂݃T�|�[�g";
    m_blogKindInfo[cnt].blogKindID     = "newPostOnly";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = newPostOnly;
    m_blogKindInfo[cnt].blogKindString = "BlogPet ���甠";
    m_blogKindInfo[cnt].blogKindID     = "newPostOnly";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = jugemX;
    m_blogKindInfo[cnt].blogKindString = "JUGEM";
    m_blogKindInfo[cnt].blogKindID     = "jugemX";
    m_blogKindInfo[cnt].endpointURL    = APIURL_JUGEM_X;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = exciteBlog;
    m_blogKindInfo[cnt].blogKindString = "excite�u���O";
    m_blogKindInfo[cnt].blogKindID     = "exciteBlog";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = yaplogX;
    m_blogKindInfo[cnt].blogKindString = "���v���O!";
    m_blogKindInfo[cnt].blogKindID     = "yaplogX";
    m_blogKindInfo[cnt].endpointURL    = APIURL_YAPLOG_X;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = drecomX;
    m_blogKindInfo[cnt].blogKindString = "�h���R���u���O";
    m_blogKindInfo[cnt].blogKindID     = "drecomX";
    m_blogKindInfo[cnt].endpointURL    = APIURL_DRECOMBLOG_X;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = mixi;
    m_blogKindInfo[cnt].blogKindString = "mixi�����L";
    m_blogKindInfo[cnt].blogKindID     = "mixi";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = kinugasa;
    m_blogKindInfo[cnt].blogKindString = "�L�k�K�T�����L";
    m_blogKindInfo[cnt].blogKindID     = "kinugasa";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = ameblo;
    m_blogKindInfo[cnt].blogKindString = "�A���[�o�u���O";
    m_blogKindInfo[cnt].blogKindID     = "ameblo";
    m_blogKindInfo[cnt].endpointURL    = ATOMURL_AMEBLO;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = echoo;
    m_blogKindInfo[cnt].blogKindString = "�G�R���O";
    m_blogKindInfo[cnt].blogKindID     = "echoo";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = webryX;
    m_blogKindInfo[cnt].blogKindString = "�E�F�u���u���O";
    m_blogKindInfo[cnt].blogKindID     = "webryX";
    m_blogKindInfo[cnt].endpointURL    = APIURL_WEBRY_X;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = rakuten;
    m_blogKindInfo[cnt].blogKindString = "�y�V�u���O";
    m_blogKindInfo[cnt].blogKindID     = "rakuten";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = fc2blog;
    m_blogKindInfo[cnt].blogKindString = "FC2BLOG";
    m_blogKindInfo[cnt].blogKindID     = "fc2blog";
    m_blogKindInfo[cnt].endpointURL    = APIURL_FC2BLOG;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = fc2network;
    m_blogKindInfo[cnt].blogKindString = "FC2NETWORK�����L";
    m_blogKindInfo[cnt].blogKindID     = "fc2network";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = gooBlog;
    m_blogKindInfo[cnt].blogKindString = "goo Blog";
    m_blogKindInfo[cnt].blogKindID     = "gooBlog";
    m_blogKindInfo[cnt].endpointURL    = APIURL_GOOBLOG;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = msnSpaces;
    m_blogKindInfo[cnt].blogKindString = "Windows Live Spaces";
    m_blogKindInfo[cnt].blogKindID     = "msnSpaces";
    m_blogKindInfo[cnt].endpointURL    = APIURL_MSNSPACES;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = colors;
    m_blogKindInfo[cnt].blogKindString = "COLORS�����L";
    m_blogKindInfo[cnt].blogKindID     = "colors";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = openPne;
    m_blogKindInfo[cnt].blogKindString = "OpenPNE�����L";
    m_blogKindInfo[cnt].blogKindID     = "openPne";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_blogKindInfo[cnt].blogKind       = hatena;
    m_blogKindInfo[cnt].blogKindString = "�͂Ăȃ_�C�A���[";
    m_blogKindInfo[cnt].blogKindID     = "hatena";
    m_blogKindInfo[cnt].endpointURL    = ATOMURL_HATENADIARY;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = tumblr;
    m_blogKindInfo[cnt].blogKindString = "Tumblr";
    m_blogKindInfo[cnt].blogKindID     = "tumblr";
    m_blogKindInfo[cnt].endpointURL    = APIURL_TUMBLR_WRITE;
    cnt++;

    m_blogKindInfo[cnt].blogKind       = unsupported;
    m_blogKindInfo[cnt].blogKindString = "���̑�";
    m_blogKindInfo[cnt].blogKindID     = "unsupported";
    m_blogKindInfo[cnt].endpointURL    = "";
    cnt++;

    m_numOfBlogKinds = cnt;

    m_blogKindList.ResetContent();
    for ( int i = 0; i < cnt; i++ )
        m_blogKindList.AddString( m_blogKindInfo[i].blogKindString );
}


bool    CBlogoleeDlg::getStringValue(
                const char *inputString,
                const char *targetName,
                char       *stringValue
            )
{
    bool        ret = false;
    const char  *p = inputString, *q;
    int         len;

    len = targetName && *targetName ? strlen( targetName ) : 0;

    if ( (len > 0) && !strncmp( p, targetName, len ) ) {
        p += len;
        while ( (*p == ' ') || (*p == '\t') )
            p++;
        q = p + (strlen( p ) - 1);
        while ( (*q == ' ') || (*q == '\t') || (*q == '\r') || (*q == '\n') )
            q--;
        q++;
        strncpy( stringValue, p, q - p );
        stringValue[q - p] = '\0';

        ret = true;
    }

    return ( ret );
}

bool    CBlogoleeDlg::getStringValue(
                const char *inputString,
                const char *targetName,
                CString    &param
            )
{
    char    buf[BUFSIZ];
    bool    ret = getStringValue( inputString, targetName, buf );

    if ( ret )
        param = buf;

    return ( ret );
}

bool    CBlogoleeDlg::getStringValue(
                const char *inputString,
                const char *paramName,
                CString    &param,
                int        idc,
                int        paramAreaSize /* = MAX_NAMELEN */
            )
{
    bool    ret = false;
    CString targetName;
    char    *name = new char [paramAreaSize + 1];

    targetName = paramName;
    targetName += ":";

    memset( name, 0x00, paramAreaSize + 1 );
    if ( getStringValue( inputString, targetName, name ) ) {
        CEdit   *cp = (CEdit *)GetDlgItem( idc );

        cp->SetWindowText( name );
        param = name;

        ret = true;
    }

    delete [] name;

    return ( ret );
}

bool    CBlogoleeDlg::getStringValue(
            const char      *inputString,
            const char      *targetName,
            int             &blogIndex )
{
    bool    ret = false;
    char    name[MAX_NAMELEN + 1];

    memset( name, 0x00, MAX_NAMELEN + 1 );
    if ( getStringValue( inputString, targetName, name ) ) {
        int i;
        for ( i = 0; i < m_numOfBlogKinds; i++ ) {
            if ( !strcmp( name, m_blogKindInfo[i].blogKindID ) )
                break;
        }

        m_blogKind = m_blogKindInfo[i].blogKind;
        m_blogKindList.SetCurSel( i );
        blogIndex = i;

        ret = true;
    }

    return ( ret );
}


void    CBlogoleeDlg::loadSetting()
{
    struct stat s;

    m_blogUserName        = "";
    m_blogPassword        = "";
    m_blogName            = "";
    m_endpointURL         = "";
    m_blogID              = "";
    m_blogURL             = "";
    m_associateID         = "";
    m_rakuten_affiliateID = "";
    m_categoryName        = "";
    m_editorPath[0]       = NUL;

    if ( !stat( m_settingDir, &s ) &&
         ((s.st_mode & _S_IFDIR ) == _S_IFDIR) ) {
        // �ݒ�t�@�C���i�[�p�t�H���_�����݂���ꍇ
        char    filename[MAX_PATH];
        sprintf( filename, "%s/%s", m_settingDir, m_settingFile );

        FILE    *fp = fopen( filename, "r" );
        if ( fp != NULL ) {
            // �ݒ�t�@�C�������݂����
            //   �ݒ�t�@�C����ǂݎ��
            loadSetting( fp );
            fclose( fp );

            sprintf( filename, "%s/%s", m_settingDir, m_blogInfoFile );
            if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
                // blog ���t�@�C�������݂����
                //   blog ���t�@�C����ǂݎ��
                loadBlogInfo( fp );
                fclose( fp );
            }
            else {
                // blog ���t�@�C�������݂��Ȃ����
                //   �ݒ�t�@�C�������� blog ���t�@�C���𐶐�����
                createBlogInfo();
                saveSetting();
            }
        }
        else {
            // �������݂��Ȃ���Ԃ��� blog ���t�@�C���𐶐�����
            if ( createBlogList() == false )
                return;
        }

        //   �ublog �ؑցv�{�^���� enable �ɂ���
        CButton *q = (CButton *)GetDlgItem( IDC_BUTTON_SWITCH_BLOG );
        q->EnableWindow( TRUE );
    }
    else {
        // �ݒ�t�@�C���i�[�p�t�H���_�����݂��Ȃ��ꍇ
        //   �ݒ�t�@�C���i�[�p�t�H���_���쐬����
        mkdir( m_settingDir );

        // �������݂��Ȃ���Ԃ��� blog ���t�@�C���𐶐�����
        if ( createBlogList() == false )
            return;

        //   �ublog �ؑցv�{�^���� enable �ɂ���
        CButton *q = (CButton *)GetDlgItem( IDC_BUTTON_SWITCH_BLOG );
        q->EnableWindow( TRUE );
    }
}

void    CBlogoleeDlg::loadSetting( FILE *fp )
{
    // �ݒ�t�@�C����ǂݎ��
    char            buf[BUFSIZ];
    char            *p;
    int             blogIndex = 0;
    bool            useCbox   = false;
    bool            encrypted = false;
    char            blogPasswordEncrypted[MAX_PASSWDLEN * 16];
    char            key[BUFSIZ];
    char            temp[BUFSIZ];
    CBlogoleeApp    *bp = (CBlogoleeApp *)AfxGetApp();

    m_blogUserName        = "";
    m_blogPassword        = "";
    m_blogName            = "";
    m_endpointURL         = "";
    m_blogID              = "";
    m_blogURL             = "";
    m_associateID         = "";
    m_rakuten_affiliateID = "";
    m_sid                 = "";
    m_pidForJalan         = "";
    m_categoryName        = "";
    m_editorPath[0]       = NUL;
    blogPasswordEncrypted[0] = NUL;
    key[0]                   = NUL;

    while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
        if ( !strncmp(p, BLOGOLEE_INF_EOF_STRING,
                      strlen(BLOGOLEE_INF_EOF_STRING)) )
            break;

        if ( getStringValue( p, "blogName",
                             m_blogName, IDC_EDIT_BLOG_NAME,
                             MAX_BLOGNAMELENGTH ) )
            continue;   // �u���O��

        if ( getStringValue( p, "blogUserName",
                             m_blogUserName, IDC_EDIT_BLOG_USERNAME ) )
            continue;   // �u���O login ID

        if ( getStringValue( p, "blogPassword",
                             m_blogPassword, IDC_EDIT_BLOG_PASSWORD ) )
            continue;   // �u���O login �p�X���[�h

        if ( getStringValue( p, "endpointURL",
                             m_endpointURL, IDC_EDIT_ENDPOINT_URL,
                             MAX_URLLENGTH ) )
            continue;   // �G���h�|�C���g URL

        if ( getStringValue( p, "blogID",
                             m_blogID, IDC_EDIT_BLOG_ID,
                             MAX_BLOGIDLENGTH ) )
            continue;   // blog ID

        if ( getStringValue( p, "blogURL",
                             m_blogURL, IDC_EDIT_BLOG_URL,
                             MAX_URLLENGTH ) )
            continue;   // blog �̃g�b�v�y�[�W�� URL

        if ( !strncmp( p, "keywordLink:", 12 ) ) {
            if ( strstr( p + 12, "on" ) != NULL )
                switchKeyword( true );
            else
                switchKeyword( false );
            continue;
        }

        if ( !strncmp( p, "similarity:", 11 ) ) {
            if ( strstr( p + 11, "on" ) != NULL )
                switchSimilarity( true );
            else
                switchSimilarity( false );
            continue;
        }

#if 0   // �����Ή�
        if ( getStringValue( p, "editorPath",
                             m_editorPath,
                             IDC_EDIT_EDITOR_PATH,
                             MAX_PATH ) )
            continue;   // �L���ҏW�p�G�f�B�^�̃p�X��
#endif

        if ( getStringValue( p, "associateID",
                             m_associateID,
                             IDC_EDIT_ASSOCIATE_ID,
                             MAX_NAMELEN ) )
            continue;   // Amazon �A�\�V�G�C�g ID

        if ( getStringValue( p, "affiliateID",
                             m_rakuten_affiliateID,
                             IDC_EDIT_RAKUTEN_ID,
                             MAX_LOGICALLINELEN ) )
            continue;   // �y�V�A�t�B���G�C�gID

        if ( getStringValue( p, "sID",
                             m_sid,
                             IDC_EDIT_JALAN_SID,
                             MAX_NAMELEN ) )
            continue;   // �o�����[�R�}�[�X SID

        if ( getStringValue( p, "pIDforJalan",
                             m_pidForJalan,
                             IDC_EDIT_JALAN_PID,
                             MAX_NAMELEN ) )
            continue;   // �o�����[�R�}�[�X PID (������ MyLink�p)

        if ( getStringValue( p, "numOfRecomended:", temp ) ) {
            m_numOfRecomended = atol( temp );
            if ( m_numOfRecomended < 0 )
                m_numOfRecomended = DEFAULT_RECOMENDED_ITEMS;
            continue;
        }

        if ( getStringValue( p, "proxyType:", temp ) ) {
            if ( strstr( temp, "notUsed" ) ) {
                bp->m_proxyType = CBlogoleeApp::notUsed;
                bp->m_useProxy  = false;
            }
            else if ( strstr( temp, "specialSetting" ) )
                bp->m_proxyType = CBlogoleeApp::specialSetting;
            else if ( strstr( temp, "manualSetting" ) )
                bp->m_proxyType = CBlogoleeApp::manualSetting;
            else
                bp->m_proxyType = CBlogoleeApp::autoDetect;
            continue;
        }

        if ( (bp->m_proxyType == CBlogoleeApp::specialSetting) ||
             (bp->m_proxyType == CBlogoleeApp::manualSetting)     ) {
            if ( !strncmp( p, "useProxy:", 9 ) ) {
                if ( strstr( p + 9, "true" ) != NULL )
                    bp->m_useProxy = true;
                else
                    bp->m_useProxy = false;
                continue;
            }

            if ( getStringValue( p, "proxyServer:",
                                 bp->m_proxyServer ) )
                continue;

            if ( getStringValue( p, "proxyPort:", temp ) ) {
                bp->m_proxyPort = atol( temp );
                if ( bp->m_proxyPort < 0 )
                    bp->m_proxyPort = 0;
                continue;
            }

            if ( getStringValue( p, "proxyUsername:",
                                 bp->m_proxyUsername ) )
                continue;

            if ( getStringValue( p, "proxyPassword:",
                                 bp->m_proxyPassword ) )
                continue;
        }

        if ( getStringValue( p, "blogType:", blogIndex ) )
            continue;   // blog���

        if ( !strncmp( p, "cbox:", 5 ) ) {
            useCbox = true;
            continue;
        }

        if ( getStringValue( p, "blogPasswordEncrypted:",
                             blogPasswordEncrypted ) ) {
            encrypted = true;
            continue;
        }
        if ( getStringValue( p, "encryptedKey:", key ) ) { /* {@@} */
            encrypted = true;
            continue;
        }
    }

    if ( encrypted && key[0] ) {
        /* �Í�������Ă���p�X���[�h�𕜍����� */
        char            *p;
        unsigned char   rsaString[BUFSIZ];
        size_t          sz = 0;

        memset( rsaString, 0x00, BUFSIZ );
        p = unbase64( (unsigned char *)key, (unsigned char *)rsaString, &sz );
        if ( p ) {
            if ( blogPasswordEncrypted[0] )
                decodeParameter( m_blogPassword,
                                 (unsigned char *)blogPasswordEncrypted,
                                 (unsigned char *)rsaString );
        }
    }

    // �K�v�ɉ����āA�G���h�|�C���gURL���� enable �ɂ���
    switchEndpointURL( blogIndex );

    // �K�v�ɉ����āAblog ID ���� enable �ɂ���
    switchBlogID( m_blogID );

    // �K�v�ɉ����āA�ublog ������{�^���v�� enable �ɂ���
    switchBrowseBlog();

    switchArticleKeyword();
    switchArticleExtended();
    switchArticleSummary();

    switchJalanLink();

    if ( (m_blogKind == newPostOnly) && (useCbox == true) ) {
        // �uBlogPet ���甠�v�̂��߂̓��ʏ���
        int i;
        for ( i = 0; i < m_numOfBlogKinds; i++ ) {
            if ( !strcmp(m_blogKindInfo[i].blogKindString, "BlogPet ���甠" ))
                break;
        }

     // m_blogKind = m_blogKindInfo[i].blogKind;
        m_blogKindList.SetCurSel( i );
    }
}

void    CBlogoleeDlg::saveSetting( bool savedForcely /* = false */)
{
    if ( m_blogKind == unset )
        return;

    mkdir( m_settingDir );

    char    filename[MAX_PATH];
    sprintf( filename, "%s/%s", m_settingDir, m_settingFile );

    FILE    *fp = fopen( filename, "w+" );
    if ( fp ) {             /* �� w+ �Ƃ��邱�Ƃ� rewind() �\�Ƃ��� */
        saveSetting( fp, savedForcely );
        fclose( fp );

        /* blog�ʐݒ�t�@�C���ۑ� */
        int i;
        for ( i = 0; i < m_numOfBlogKinds; i++ ) {
            if ( m_blogKind == m_blogKindInfo[i].blogKind )
                break;
        }
        if ( i < m_numOfBlogKinds ) {
            sprintf( filename, "%s/%s.inf",
                     m_settingDir, m_blogKindInfo[i].blogKindID );
            if ( m_blogKind == newPostOnly ) {
                // �uBlogPet ���甠�v�̂��߂̓��ʏ���
                CString     blogKindString;
                int         location = m_blogKindList.GetCurSel();

	            m_blogKindList.GetLBText( location, blogKindString );
                if ( blogKindString.Compare( "BlogPet ���甠" ) == 0 )
                    sprintf( filename, "%s/%s.inf",
                             m_settingDir, "cbox" );
            }

            fp = fopen( filename, "w+" );
            if ( fp ) {     /* �� w+ �Ƃ��邱�Ƃ� rewind() �\�Ƃ��� */
                saveSetting( fp, savedForcely );
                fclose( fp );
            }
        }
    }
}

void    CBlogoleeDlg::saveSetting( FILE *fp, bool savedForcely )
{
    bool            done = false;
    bool            encrypted;
    char            key[BUFSIZ];
    unsigned char   *rsaString;
    FILE            *gp;
    int             retryCount = 0;
    char            fileForCheck[MAX_PATH];
    CBlogoleeApp    *bp = (CBlogoleeApp *)AfxGetApp();

    sprintf( fileForCheck, "%s/chk%08dCD",
             m_settingDir, time( NULL ) % 10000000 );
    do {
        key[0]    = NUL;
        rsaString = NULL;
        encrypted = false;
        gp = fopen( fileForCheck, "w" );
        if ( gp )
            fprintf( gp, "numOfBlogPasswords: %d\n", 2 );

        if ( savedForcely ) {
            // �p�����[�^�m��
            getParameter( savedForcely );
        }

        // �ݒ�t�@�C���������o��
        int i;
        for ( i = 0; i < m_numOfBlogKinds; i++ ) {
            if ( m_blogKind == m_blogKindInfo[i].blogKind )
                break;
        }
        if ( i < m_numOfBlogKinds )
            fprintf( fp, "blogType:        %s\n",
                     m_blogKindInfo[i].blogKindID );

        if ( m_blogName.GetLength() > 0 )
            fprintf( fp, "blogName:   %s\n",
                     (const char *)m_blogName );

        if ( m_blogUserName.GetLength() > 0 )
            fprintf( fp, "blogUserName:    %s\n",
                     (const char *)m_blogUserName );

        if ( m_blogPassword.GetLength() > 0 )
            encodeParameter( fp, gp,
                             (const char *)m_blogPassword,
                             "blogPassword",
                             key, &rsaString, encrypted );
        else {
            // checkBlogInfo() �������� false ��Ԃ��̂�h�~���邽��
            // �_�~�[�̃p�X���[�h��ݒ�
            encodeParameter( NULL, gp, /* gp �ɂ̂� write */
                             "dummy",
                             "blogPassword",
                             key, &rsaString, encrypted );
        }

        if ( (m_blogKind == movableType) ||
             (m_blogKind == bloggerAPI)  ||
             (m_blogKind == metaWeblog)  ||
             (m_blogKind == mtAPI)       ||
             (m_blogKind == atomAPI)     ||
             (m_blogKind == newPostOnly)    ) {
            if ( m_endpointURL.GetLength() > 0 )
                fprintf( fp, "endpointURL:     %s\n",
                         (const char *)m_endpointURL );
        }

        if ( m_blogID.GetLength() > 0 )
            fprintf( fp, "blogID:          %s\n", m_blogID );
        if ( m_blogURL.GetLength() > 0 )
            fprintf( fp, "blogURL:         %s\n", m_blogURL );

        fprintf( fp, "keywordLink:     %s\n",
                 m_keyword  == true         ? "on" : "off" );
        fprintf( fp, "similarity:      %s\n",
                 m_similarity == true       ? "on" : "off" );

        if ( m_editorPath[0] != NUL )
            fprintf( fp, "editorPath:      %s\n", m_editorPath );

        if ( m_associateID.GetLength() > 0 )
            fprintf( fp, "associateID:     %s\n",
                     (const char *)m_associateID );

        if ( m_rakuten_affiliateID.GetLength() > 0 )
            fprintf( fp, "affiliateID:     %s\n",
                     (const char *)m_rakuten_affiliateID );

        if ( m_sid.GetLength() > 0 )
            fprintf( fp, "sID:             %s\n",
                     (const char *)m_sid );

        if ( m_pidForJalan.GetLength() > 0 )
            fprintf( fp, "pIDforJalan:     %s\n",
                     (const char *)m_pidForJalan );

        fprintf( fp, "numOfRecomended: %d\n",
                 m_numOfRecomended );

        if ( (bp->m_proxyType == CBlogoleeApp::specialSetting) ||
             (bp->m_proxyType == CBlogoleeApp::manualSetting)     ) {
            fprintf( fp, "proxyType: %s\n",
                     bp->m_proxyType == CBlogoleeApp::specialSetting
                        ? "specialSetting"
                        : "manualSetting" );
            fprintf(fp, "useProxy: %s\n", bp->m_useProxy ? "true" : "false");
            if ( bp->m_useProxy ) {
                fprintf( fp, "proxyServer: %s\n", bp->m_proxyServer );
                fprintf( fp, "proxyPort:   %d\n", bp->m_proxyPort );
                if ( bp->m_proxyUsername.GetLength() > 0 ) {
                    fprintf( fp, "proxyUsername: %s\n",
                             (const char *)bp->m_proxyUsername );
                    if ( bp->m_proxyPassword.GetLength() )
                        fprintf( fp, "proxyPassword: %s\n",
                                 (const char *)bp->m_proxyPassword );
                }
            }
        }
        else if ( bp->m_proxyType == CBlogoleeApp::notUsed )
            fprintf( fp, "proxyType: notUsed\n" );
        else
            fprintf( fp, "proxyType: autoDetect\n" );

        if ( m_blogKind == newPostOnly ) {
            // �uBlogPet ���甠�v�̂��߂̓��ʏ���
            CString     blogKindString;
            int         location = m_blogKindList.GetCurSel();

	        m_blogKindList.GetLBText( location, blogKindString );
            if ( blogKindString.Compare( "BlogPet ���甠" ) == 0 )
                fprintf( fp, "cbox:            alive\n" );
        }

        if ( m_categoryName.GetLength() > 0 )
            fprintf( fp, "categoryName:    %s\n",
                     (const char *)m_categoryName );

        if ( encrypted && key[0] ) {
            fprintf( fp, "encryptedKey: %s\n", key );
            if ( gp )
                fprintf( gp, "encryptedKey: %s\n", key );
            freeParameter( rsaString );
        }
        fprintf( fp, "%s\n", BLOGOLEE_INF_EOF_STRING );

        if ( gp ) {
            fclose( gp );
            gp = NULL;
        }

        if ( encrypted && key[0] ) {
            done = checkSetting( fileForCheck );
            if ( done == false )
                rewind( fp );
        }
        else
            done = true;

        if ( done == false ) {
            retryCount++;
            if ( retryCount >= 27 )
                break;
        }
    } while ( done == false );

    unlink( fileForCheck );
}

bool    CBlogoleeDlg::createBlogList()
{
    // blog ���i�[�̈���m��
    if ( allocateBlogInfo() == false )
        return ( false );   // �m�ێ��s

    //   blog �o�^��ʂ�\��
    OnButtonSwitchBlog();
    return ( true );
}

void    CBlogoleeDlg::createBlogInfo()
{
    // �u�ݒ�t�@�C���v�Q�����ɁuBlog ���t�@�C���v�𐶐�
    FILE    *fp, *gp;
    char    filename[MAX_PATH];

    sprintf( filename, "%s/%s", m_settingDir, m_blogInfoFile );
    if ( ( gp = fopen( filename, "w+" ) ) == NULL )
        return;                 /* �� w+ �Ƃ��邱�Ƃ� rewind() �\�Ƃ��� */

    sprintf( filename, "%s/%s", m_settingDir, m_settingFile );
    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        registerBlogInfoFromFile( fp );
        fclose( fp );
    }

    for ( int i = 0; i < m_numOfBlogKinds; i++ ) {
        sprintf( filename, "%s/%s.inf",
                 m_settingDir, m_blogKindInfo[i].blogKindID );
        if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
            registerBlogInfoFromFile( fp );
            fclose( fp );
        }
    }

    sprintf( filename, "%s/%s.inf", m_settingDir, "cbox" ); // BlogPet���甠
    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        registerBlogInfoFromFile( fp );
        fclose( fp );
    }

    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    m_currentBlogID = 0;
    m_blogKind      = cp->m_blogList[m_currentBlogID].blogKind;
    m_blogName      = cp->m_blogList[m_currentBlogID].blogName;
    m_blogUserName  = cp->m_blogList[m_currentBlogID].blogUsername;
    m_blogPassword  = cp->m_blogList[m_currentBlogID].blogPassword;
    m_blogID        = cp->m_blogList[m_currentBlogID].blogID;
    m_blogURL       = cp->m_blogList[m_currentBlogID].blogURL;

    if ( cp->m_blogList[m_currentBlogID].endpointURL[0] )
        m_endpointURL = cp->m_blogList[m_currentBlogID].endpointURL;
    else {
        int blogKindIndex = -1;
        for ( int j = 0; j < m_numOfBlogKinds; j++ ) {
            if ( m_blogKind == m_blogKindInfo[j].blogKind ) {
                blogKindIndex = j;
                break;
            }
        }
        if ( blogKindIndex >= 0 )
            m_endpointURL = m_blogKindInfo[blogKindIndex].endpointURL;
        else
            m_endpointURL = "";
    }

    m_categoryList.ResetContent();
    m_categoryName  = "";

    saveBlogInfo( gp );
    fclose( gp );

    switchBlogInfo();
}

void    CBlogoleeDlg::loadBlogInfo( FILE *fp /* = NULL */ )
{
    char            buf[BUFSIZ], *p;
    char            temp[BUFSIZ];
    char            target[MAX_KEYLENGTH];
    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    long            current   = 0;
    int             count     = 0;
    int             catCount  = 0;
    bool            justOpen  = false;
    bool            encrypted = false;
    char            key[BUFSIZ];
    char            blogPasswordEncrypted[MAX_PASSWDLEN * 16];

    if ( fp == NULL ) {
        char    filename[MAX_PATH];

        sprintf( filename, "%s/%s", m_settingDir, m_blogInfoFile );
        if ( ( fp = fopen( filename, "r" ) ) == NULL )
            return;
        justOpen = true;
    }

    m_currentBlogID  = 0;
    cp->m_numOfBlogs = 0;

    if ( cp->m_blogList == NULL ) {
        // blog ���i�[�̈���m��
        if ( allocateBlogInfo() == false )
            return; // �m�ێ��s
    }

    key[0] = NUL;
    blogPasswordEncrypted[0] = NUL;
    while ( ( p = fgets( buf, BUFSIZ -1, fp ) ) != NULL ) {
        if ( getStringValue( p, "encryptedKey:", key ) ) {
            encrypted = true;
            break;
        }
    }
    rewind( fp );

    while ( ( p = fgets( buf, BUFSIZ -1, fp ) ) != NULL ) {
        if ( !strncmp(p, BLOGOLEE_INF_EOF_STRING,
                      strlen(BLOGOLEE_INF_EOF_STRING)) )
            break;

        if ( getStringValue( p, "currentBlogIndex:", temp ) ) {
            m_currentBlogID = atol( temp );
            if ( m_currentBlogID < 0 )
                m_currentBlogID = 0;
            continue;
        }
        if ( getStringValue( p, "numOfBlogs:", temp ) ) {
            cp->m_numOfBlogs = atol( temp );
            if ( cp->m_numOfBlogs < 0 )
                cp->m_numOfBlogs = 0;
            continue;
        }

        if ( cp->m_numOfBlogs > 0 ) {
            sprintf( target, "blog#%d_", current + 2 );
            if ( !strncmp( p, target, strlen( target ) ) ) {
                current++;
                if ( current >= cp->m_numOfBlogs )
                    break;
                count    = 0;
                catCount = 0;
                cp->m_blogList[current].useCbox = false;
            }

            do {
                sprintf( target, "blog#%d_blogType:", current + 1 );
                if ( getStringValue( p, target, temp ) ) {
                    for ( int j = 0; j < m_numOfBlogKinds; j++ ) {
                        if ( !stricmp(temp, m_blogKindInfo[j].blogKindID) ) {
                            cp->m_blogList[current].blogKind =
                                                m_blogKindInfo[j].blogKind;
                            count++;
                            break;
                        }
                    }
                    break;
                }

                sprintf( target, "blog#%d_blogName:", current + 1 );
                if ( getStringValue( p, target,
                                     cp->m_blogList[current].blogName ) ) {
                    count++;
                    break;
                }

                sprintf( target, "blog#%d_blogID:", current + 1 );
                if ( getStringValue( p, target,
                                     cp->m_blogList[current].blogID ) ) {
                    count++;
                    break;
                }

                sprintf( target, "blog#%d_blogURL:", current + 1 );
                if ( getStringValue( p, target,
                                     cp->m_blogList[current].blogURL ) ) {
                    count++;
                    break;
                }

                sprintf( target, "blog#%d_blogUsername:", current + 1 );
                if ( getStringValue(p, target,
                                    cp->m_blogList[current].blogUsername) ) {
                    count++;
                    break;
                }

                sprintf( target, "blog#%d_blogPassword:", current + 1 );
                if ( getStringValue(p, target,
                                    cp->m_blogList[current].blogPassword) ) {
                    count++;
                    break;
                }
                sprintf( target, "blog#%d_blogPasswordEncrypted:",
                         current + 1 );
                if ( encrypted && key[0] &&
                     getStringValue( p, target, blogPasswordEncrypted ) ) {
                    /* �Í�������Ă���p�X���[�h�𕜍����� */
                    char            *p;
                    unsigned char   rsaString[BUFSIZ];
                    CString         blogPassword;
                    size_t          sz = 0;

                    count++;
                    memset( rsaString, 0x00, BUFSIZ );
                    p = unbase64( (unsigned char *)key,
                                  (unsigned char *)rsaString,
                                  &sz );
                    if ( p ) {
                        if ( blogPasswordEncrypted[0] ) {
                            decodeParameter(
                                    blogPassword,
                                    (unsigned char *)blogPasswordEncrypted,
                                    (unsigned char *)rsaString );
                            strcpy( cp->m_blogList[current].blogPassword,
                                    (const char *)blogPassword );
                        }
                    }
                }

                sprintf( target, "blog#%d_endpointURL:", current + 1 );
                if ( getStringValue( p, target,
                                     cp->m_blogList[current].endpointURL ) ) {
                    count++;
                    break;
                }

                sprintf( target, "blog#%d_cbox:", current + 1 );
                if ( getStringValue( p, target, temp ) ) {
                    cp->m_blogList[current].useCbox = true;
                    count++;
                    break;
                }

                sprintf( target, "blog#%d_numOfCategories:", current + 1 );
                if ( getStringValue( p, target, temp ) ) {
                    long    numOfCats = atol( temp );

                    if (cp->m_blogList[current].numOfCategories != numOfCats){
                        if ( cp->m_blogList[current].catagory ) {
                            for ( int j = 0;
                                  j < cp->m_blogList[current].numOfCategories;
                                  j++ )
                                free( cp->m_blogList[current].catagory[j] );
                            free( cp->m_blogList[current].catagory );
                        }

                        cp->m_blogList[current].numOfCategories = numOfCats;
                        cp->m_blogList[current].catagory =
                          (char **)malloc( 
                                     cp->m_blogList[current].numOfCategories *
                                                          sizeof ( char * ) );
                        if ( cp->m_blogList[current].catagory ) {
                            for ( int j = 0;
                                  j < cp->m_blogList[current].numOfCategories;
                                  j++ ) {
                                cp->m_blogList[current].catagory[j] =
                                        (char *)malloc(
                                           MAX_CATNAMELENGTH * sizeof (char));
                                if ( !(cp->m_blogList[current].catagory[j]) )
                                    break;
                            }
                        }
                    }
                    count++;
                    break;
                }

                if ((cp->m_blogList[current].numOfCategories > catCount) &&
                    (cp->m_blogList[current].catagory != NULL)             ) {
                    sprintf( target, "blog#%d_category#%d_name:",
                             current + 1, catCount + 1 );
                    if ( getStringValue( p, target,
                             cp->m_blogList[current].catagory[catCount] ) ) {
                        count++;
                        catCount++;
                        break;
                    }
                }
            } while ( false );

            if ( count == 9 + cp->m_blogList[current].numOfCategories ) {
                current++;
                if ( current >= cp->m_numOfBlogs )
                    break;
                count    = 0;
                catCount = 0;
                cp->m_blogList[current].useCbox = false;
            }
        }
    }

    if ( count >= 1 )
        if ( current < cp->m_numOfBlogs )
            current++;

    if ( m_currentBlogID >= cp->m_numOfBlogs )
        m_currentBlogID = 0;

    m_blogKind      = cp->m_blogList[m_currentBlogID].blogKind;
    m_blogName      = cp->m_blogList[m_currentBlogID].blogName;
    m_blogUserName  = cp->m_blogList[m_currentBlogID].blogUsername;
    m_blogPassword  = cp->m_blogList[m_currentBlogID].blogPassword;
    m_blogID        = cp->m_blogList[m_currentBlogID].blogID;
    m_blogURL       = cp->m_blogList[m_currentBlogID].blogURL;

    if ( cp->m_blogList[m_currentBlogID].endpointURL[0] )
        m_endpointURL = cp->m_blogList[m_currentBlogID].endpointURL;
    else {
        int blogKindIndex = -1;
        for ( int j = 0; j < m_numOfBlogKinds; j++ ) {
            if ( m_blogKind == m_blogKindInfo[j].blogKind ) {
                blogKindIndex = j;
                break;
            }
        }
        if ( blogKindIndex >= 0 )
            m_endpointURL = m_blogKindInfo[blogKindIndex].endpointURL;
        else
            m_endpointURL = "";
    }

    switchBlogInfo();

    if ( justOpen )
        fclose( fp );
}

void    CBlogoleeDlg::saveBlogInfo( FILE *fp /* = NULL */ )
{
    bool            done = false;
    bool            flag = false;
    bool            encrypted;
    char            key[BUFSIZ];
    unsigned char   *rsaString;
    FILE            *gp;
    char            fileForCheck[MAX_PATH];
    int             retryCount = 0;
    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();

    sprintf( fileForCheck, "%s/chk%08dBI",
             m_settingDir, time( NULL ) % 10000000 );
    do {
        key[0]    = NUL;
        rsaString = NULL;
        encrypted = false;

        if ( fp == NULL ) {
            char    filename[MAX_PATH];

            sprintf( filename, "%s/%s", m_settingDir, m_blogInfoFile );
            if ( ( fp = fopen( filename, "w" ) ) == NULL )
                return;
            flag = true;
        }
        gp = fopen( fileForCheck, "w" );

        if ( cp->m_numOfBlogs > 0 ) {
            char    blogKindString[16];

            fprintf( fp, "currentBlogIndex: %d\n", m_currentBlogID );
            fprintf( fp, "numOfBlogs: %d\n", cp->m_numOfBlogs );
            if ( gp )
                fprintf( gp, "numOfBlogs: %d\n", cp->m_numOfBlogs );

            for ( long i = 0; i < cp->m_numOfBlogs; i++ ) {
                /*  blog ���               */
                blogKindString[0] = NUL;
                for ( int j = 0; j < m_numOfBlogKinds; j++ ) {
                    if ( cp->m_blogList[i].blogKind ==
                                            m_blogKindInfo[j].blogKind ) {
                        strcpy(blogKindString, m_blogKindInfo[j].blogKindID);
                        break;
                    }
                }

                if ( blogKindString[0] != NUL )
                    fprintf( fp, "blog#%d_blogType: %s\n",
                             i + 1,
                             blogKindString );

                /*  blog �̖��O             */
                if ( cp->m_blogList[i].blogName[0] != NUL )
                    fprintf( fp, "blog#%d_blogName: %s\n",
                             i + 1,
                             cp->m_blogList[i].blogName );

                /*  blog ID                 */
                if ( cp->m_blogList[i].blogID[0] != NUL )
                    fprintf( fp, "blog#%d_blogID: %s\n",
                             i + 1,
                             cp->m_blogList[i].blogID );

                /*  blog�̃g�b�v�y�[�W��URL */
                if ( cp->m_blogList[i].blogURL[0] != NUL )
                    fprintf( fp, "blog#%d_blogURL: %s\n",
                             i + 1,
                             cp->m_blogList[i].blogURL );

                /*  blog ���O�C�����[�U��   */
                if ( cp->m_blogList[i].blogUsername[0] != NUL )
                    fprintf( fp, "blog#%d_blogUsername: %s\n",
                             i + 1,
                             cp->m_blogList[i].blogUsername );

                /*  blog ���O�C���p�X���[�h */
                if ( cp->m_blogList[i].blogPassword[0] != NUL ) {
                    char    paramName[BUFSIZ];

                    sprintf( paramName, "blog#%d_blogPassword", i + 1 );
                    encodeParameter( fp, gp,
                                     cp->m_blogList[i].blogPassword,
                                     paramName,
                                     key, &rsaString, encrypted );
                }
                else {
                    // checkBlogInfo() �������� false ��Ԃ��̂�h�~���邽��
                    // �_�~�[�̃p�X���[�h��ݒ�
                    char    paramName[BUFSIZ];

                    sprintf( paramName, "blog#%d_blogPassword", i + 1 );
                    encodeParameter( NULL, gp, /* gp �ɂ̂� write */
                                     "dummy",
                                     paramName,
                                     key, &rsaString, encrypted );
                }

                /*  �G���h�|�C���gURL       */
                if ( cp->m_blogList[i].endpointURL[0] != NUL )
                    fprintf( fp, "blog#%d_endpointURL: %s\n",
                             i + 1,
                             cp->m_blogList[i].endpointURL );

                /*  for �gBlog Pet ���甠�h */
                if ( cp->m_blogList[i].useCbox )
                    fprintf( fp, "blog#%d_cbox: alive\n", i + 1 );

                /* �J�e�S���ꗗ */
                if ( cp->m_blogList[i].numOfCategories > 0 ) {
                    fprintf( fp, "blog#%d_numOfCategories: %d\n",
                             i + 1,
                             cp->m_blogList[i].numOfCategories );
                    int j;
                    for (j = 0; j < cp->m_blogList[i].numOfCategories; j++) {
                        fprintf( fp, "blog#%d_category#%d_name: %s\n",
                                 i + 1, j + 1,
                                 cp->m_blogList[i].catagory[j] );
                    }
                }
            }

            if ( encrypted && key[0] ) {
                fprintf( fp, "encryptedKey: %s\n", key );
                if ( gp )
                    fprintf( gp, "encryptedKey: %s\n", key );
                freeParameter( rsaString );
            }
        }
        fprintf( fp, "%s\n", BLOGOLEE_INF_EOF_STRING );

        if ( flag ) {
            fclose( fp );
            fp = NULL;
        }
        if ( gp ) {
            fclose( gp );
            gp = NULL;
        }

        /* �p�X���[�h�� decode �ł��邱�Ƃ��m�F */
        if ( encrypted && key[0] ) {
            done = checkBlogInfo( fileForCheck );
            if ( done == false )
                if ( fp )
                    rewind( fp );
        }
        else
            done = true;

        if ( done == false ) {
            retryCount++;
            if ( retryCount >= 27 )
                break;
        }
    } while ( done == false );

    unlink( fileForCheck );
}

void    CBlogoleeDlg::registerBlogInfoFromFile( FILE *fp )
{
    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    char            buf[BUFSIZ], *p;

    if ( cp->m_numOfBlogs >= MAX_NUM_OF_BLOGS )
        return;

    if ( cp->m_blogList == NULL ) {
        // blog ���i�[�̈���m��
        if ( allocateBlogInfo() == false )
            return; // �m�ێ��s
    }

    char        blogKindString[16];
    char        cboxString[16];
    BLOGKIND    blogKind;                       /* blog ���               */
    char        blogName[MAX_NAMELEN];          /* blog �̖��O             */
    char        blogUsername[MAX_NAMELEN];      /* blog ���O�C�����[�U��   */
    char        blogPassword[MAX_PASSWDLEN];    /* blog ���O�C���p�X���[�h */
    char        blogID[MAX_BLOGIDLENGTH + 1];   /* blog ID                 */
    char        blogURL[MAX_URLLENGTH];         /* blog�̃g�b�v�y�[�W��URL */
    char        endpointURL[MAX_URLLENGTH];     /* �G���h�|�C���gURL       */
    bool        useCbox;                        /* for �gBlog Pet ���甠�h */

    blogKind         = unset;
    blogName[0]      = NUL;
    blogUsername[0]  = NUL;
    blogPassword[0]  = NUL;
    blogID[0]        = NUL;
    blogURL[0]       = NUL;
    endpointURL[0]   = NUL;
    useCbox          = false;

    while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
        if ( getStringValue( p, "blogUserName:", blogUsername ) )
            continue;
        if ( getStringValue( p, "blogPassword:", blogPassword ) )
            continue;
        if ( getStringValue( p, "endpointURL:", endpointURL ) )
            continue;
        if ( getStringValue( p, "blogID:", blogID ) )
            continue;
        if ( getStringValue( p, "blogURL:", blogURL ) )
            continue;
        if ( getStringValue( p, "blogName:", blogName ) )
            continue;

        if ( getStringValue( p, "blogType:", blogKindString ) ) {
            blogKind = unset;
            for ( int i = 0; i < m_numOfBlogKinds; i++ ) {
                if ( !stricmp( blogKindString,
                               m_blogKindInfo[i].blogKindID ) ) {
                    blogKind =  m_blogKindInfo[i].blogKind;
                    break;
                }
            }
            continue;
        }

        if ( getStringValue( p, "cbox:", cboxString ) ) {
            useCbox = true;
            continue;
        }
    }

    long    n = cp->m_numOfBlogs;
    bool    found = false;

    if ( blogName[0] != NUL ) {
        for ( long i = 0; i < n; i++ ) {
            if ( !strcmp( blogName, cp->m_blogList[i].blogName ) ) {
                found = true;
                break;
            }
        }
    }
    else {
        for ( long i = 0; i < n; i++ ) {
            if ( blogKind == cp->m_blogList[i].blogKind ) {
                found = true;
                break;
            }
        }
    }

    if ( found == false ) {
        if ( blogUsername[0] != NUL )
            strcpy( cp->m_blogList[n].blogUsername, blogUsername );
        else
            cp->m_blogList[n].blogUsername[0] = NUL;

        if ( blogPassword[0] != NUL )
            strcpy( cp->m_blogList[n].blogPassword, blogPassword );
        else
            cp->m_blogList[n].blogPassword[0] = NUL;

        if ( endpointURL[0] != NUL )
            strcpy( cp->m_blogList[n].endpointURL, endpointURL );
        else
            cp->m_blogList[n].endpointURL[0] = NUL;

        if ( blogID[0] != NUL )
            strcpy( cp->m_blogList[n].blogID, blogID );
        else
            cp->m_blogList[n].blogID[0] = NUL;

        if ( blogURL[0] != NUL )
            strcpy( cp->m_blogList[n].blogURL, blogURL );
        else
            cp->m_blogList[n].blogURL[0] = NUL;

        if ( blogName[0] != NUL )
            strcpy( cp->m_blogList[n].blogName, blogName );
        else
            cp->m_blogList[n].blogName[0] = NUL;

        cp->m_blogList[n].blogKind = blogKind;
        cp->m_blogList[n].useCbox  = useCbox;

        cp->m_numOfBlogs++;
    }
}


/* �G���R�[�h�ς݃p�X���[�h���{���Ƀf�R�[�h�ł���̂��ǂ������O�� */
/* �m�F���Ă��� (decodeByRSA() ���f�R�[�h�Ɏ��s���邱�Ƃ����邱�� */
/* �������A���̃��\�b�h��p�ӂ��邱�Ƃ�[�b��I��]�΍�Ƃ���)      */
bool
CBlogoleeDlg::checkEncodedPassword( const char *filename )
{
    bool    ret = true;
    int     numOfPasswords = 0;
    int     num = 0;
    char    **passwordEncrypted = NULL;
    CString password;
    char    key[BUFSIZ];
    char    buf[BUFSIZ];
    char    *p, *q;
    FILE    *fp;

    key[0] = NUL;

    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            while ( (*p == ' ') || (*p == '\t') )
                p++;
            while ( *p && (p[strlen( p ) - 1] == '\n') )
                p[strlen( p ) - 1] = NUL;
            if ( !(*p) )
                continue;

            if ( !strncmp( p, "numOf", 5 )        &&
                 ((q = strchr( p, ':' )) != NULL)    ) {
                numOfPasswords = atol( q + 1 );

                passwordEncrypted =
                        (char **)malloc( sizeof ( char *) * numOfPasswords );
                for ( int i = 0; i < numOfPasswords; i++ ) {
                    passwordEncrypted[i] = (char *)malloc(MAX_PASSWDLEN * 16);
                    memset( passwordEncrypted[i], 0x00, MAX_PASSWDLEN * 16 );
                }
                break;
            }
        }

        if ( numOfPasswords > 0 ) {
            rewind( fp );
            while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
                if ( strstr( p, "Encrypted: " ) != NULL ) {
                    if ( num < numOfPasswords ) {
                        q = strchr( p, ':' ) + 1;
                        while ( (*q == ' ') || (*q == '\t') )
                            q++;
                        strcpy( passwordEncrypted[num], q );
                    }
                    num++;
                }
                else if ( !strncmp( p, "encryptedKey: ", 14 ) ) {
                    q = strchr( p, ':' ) + 1;
                    while ( (*q == ' ') || (*q == '\t') )
                        q++;
                    strcpy( key, q );
                }
            }
        }
        fclose( fp );
    }

    if ( numOfPasswords > 0 ) {
        if ( key[0] != NUL ) {
            unsigned char   rsaString[BUFSIZ];
            size_t          sz = 0;

            p = unbase64( (unsigned char *)key, (unsigned char *)rsaString, &sz );
            if ( p ) {
                for ( int i = 0; i < numOfPasswords; i++ ) {
                    password = "";
                    decodeParameter( password,
                                     (unsigned char *)passwordEncrypted[i],
                                     (unsigned char *)rsaString );
                    if ( password.GetLength() == 0 )
                        ret = false;
                }
            }
        }

        for ( int i = numOfPasswords; i > 0; i-- )
            free( passwordEncrypted[i - 1] );
        free( passwordEncrypted );
    }

    return ( ret ); /* true: �f�R�[�h����, false: �f�R�[�h���s */
}

bool
CBlogoleeDlg::checkSetting( const char *filename )
{
    return ( checkEncodedPassword( filename ) );
}

bool
CBlogoleeDlg::checkBlogInfo( const char *filename )
{
    return ( checkEncodedPassword( filename ) );
}


void    CBlogoleeDlg::switchArticleKeyword()
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_KEYWORD );
    if ( (m_blogKind == typepad)       ||
         (m_blogKind == typepadJapan ) ||
         (m_blogKind == cocolog )      ||
         (m_blogKind == cocologFree )  ||
         (m_blogKind == blogzine )     ||
         (m_blogKind == seesaa )       ||
         (m_blogKind == netLaputa )    ||
         (m_blogKind == blogG )        ||
         (m_blogKind == newsHandler )  ||
         (m_blogKind == fc2blog )      ||
         (m_blogKind == gooBlog )      ||
      /* (m_blogKind == drecomX)       || */
      /* (m_blogKind == yaplogX)       || */
                            // �h���R���u���O,���v���O! �̓L�[���[�h���g���Ȃ�
         (m_blogKind == jugemX)        ||
      /* (m_blogKind == msnSpaces )    || */
      /* (m_blogKind == webryX )       || */
         (m_blogKind == movableType )  ||
         (m_blogKind == mtAPI )        ||
         (m_blogKind == movableType)   ||
         (m_blogKind == bloggerAPI)    ||
         (m_blogKind == metaWeblog)    ||
         (m_blogKind == newPostOnly)      ) {
        p->EnableWindow( TRUE );
    }
    else {
        p->EnableWindow( FALSE );
    }
}

void    CBlogoleeDlg::switchArticleExtended()
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_EXTENDED );
    if ( (m_blogKind == typepad)       ||
         (m_blogKind == typepadJapan ) ||
         (m_blogKind == cocolog )      ||
         (m_blogKind == cocologFree )  ||
         (m_blogKind == blogzine )     ||
         (m_blogKind == seesaa )       ||
         (m_blogKind == netLaputa )    ||
         (m_blogKind == blogG )        ||
         (m_blogKind == newsHandler )  ||
         (m_blogKind == fc2blog )      ||
         (m_blogKind == gooBlog )      ||
         (m_blogKind == drecomX)       ||
         (m_blogKind == yaplogX)       ||
         (m_blogKind == jugemX)        ||
         (m_blogKind == exciteBlog)    ||
      /* (m_blogKind == msnSpaces )    || */
      /* (m_blogKind == webryX )       || */
         (m_blogKind == movableType )  ||
         (m_blogKind == mtAPI )        ||
         (m_blogKind == movableType)   ||
         (m_blogKind == bloggerAPI)    ||
         (m_blogKind == metaWeblog)    ||
         (m_blogKind == newPostOnly)      ) {
        p->EnableWindow( TRUE );
    }
    else {
        p->EnableWindow( FALSE );
    }
}

void    CBlogoleeDlg::switchArticleSummary()
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_SUMMARY );
    if ( (m_blogKind == typepad)       ||
         (m_blogKind == typepadJapan ) ||
         (m_blogKind == cocolog )      ||
         (m_blogKind == cocologFree )  ||
         (m_blogKind == blogzine )     ||
         (m_blogKind == seesaa )       ||
         (m_blogKind == netLaputa )    ||
         (m_blogKind == blogG )        ||
         (m_blogKind == newsHandler )  ||
         (m_blogKind == fc2blog )      ||
         (m_blogKind == gooBlog )      ||
         (m_blogKind == drecomX)       ||
         (m_blogKind == yaplogX)       ||
         (m_blogKind == jugemX)        ||
      /* (m_blogKind == msnSpaces )    || */
      /* (m_blogKind == webryX )       || */
         (m_blogKind == atomAPI)       ||
         (m_blogKind == movableType )  ||
         (m_blogKind == mtAPI )        ||
         (m_blogKind == movableType)   ||
         (m_blogKind == bloggerAPI)    ||
         (m_blogKind == metaWeblog)    ||
         (m_blogKind == newPostOnly)      ) {
        p->EnableWindow( TRUE );
    }
    else {
        p->EnableWindow( FALSE );
    }
}

void    CBlogoleeDlg::switchPostArticle()
{
    CButton *q = (CButton *)GetDlgItem( IDOK );
    CString buttonName;

    q->GetWindowText( buttonName );
    if ( !buttonName.Compare("���e") ) {
        if ( ( m_article_title.GetLength() > 0)      &&
             (m_article_description.GetLength() > 0)    )
            q->EnableWindow( TRUE );
        else
            q->EnableWindow( FALSE );
    }
}

#define isWhiteSpace(p) \\
     (((p) == ' ') || ((p) == '\t') || ((p) == '\r') || ((p) == '\n'))

int
CBlogoleeDlg::getFoodCodeInfo()
{
    int         num = 0, n = 0;
    FILE        *fp = NULL;
    char        filename[MAX_PATH];
    struct stat s;
    bool        needToGet = false;

    sprintf( filename, "%s/foodCode.xml", m_settingDir );

    if ( !stat( filename, &s ) ) {
        time_t  t = time( NULL );
        if ( s.st_mtime < t - 72 * 60 * 60 )
            needToGet = true;
                /* �O��̎擾���� 72���Ԉȏ�o�߂��Ă���ꍇ�̂ݍĎ擾���� */
        else {
            fp = fopen( filename, "r" );
            if ( fp ) {
                char    *p;
                char    buf[BUFSIZ];
                bool    found = false;

                while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
                    if ( strstr( p, "<Food>" ) ) {
                        found = true;
                        break;
                    }
                }
                fclose( fp );

                needToGet = !found;
                // �t�@�C������ <Food> �����݂��Ȃ��ꍇ�́A���߂Ď擾������
            }
        }
    }
    else
        needToGet = true;
                /* �t�@�C�������݂��Ȃ��̂ŁA�擾���� */

    if ( needToGet ) {
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        char        url[MAX_URLLENGTH];
        char        *response;
        size_t      sz = MAX_CONTENT_SIZE;

        response = (char *)malloc( sz );
        if ( !response )
            return ( num );

        ProceedingDialog    *pdlg;
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
        pdlg->ChangeDialogText( "�z�b�g�y�b�p�[Web�T�[�r�X",
                                "�u�������}�X�^�v���擾���c�c" );

        strcpy( url, "http://api.hotpepper.jp/Food/V110/?key=guest" );
        setUpReceiveBuffer( response, sz );
        http_get( url, response );
        if ( *response ) {
            fp = fopen( filename, "w" );
            if ( fp ) {
                fputs( response, fp );
                fclose( fp );
            }
        }
        else
            MessageBox( "�u�������}�X�^�v�̎擾�Ɏ��s���܂���    ",
                        "�擾���s",
                        MB_OK|MB_ICONWARNING );
        delete [] pdlg;
        free( response );
    }

    char    *buf = readXML( filename );
    if ( buf ) {
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

        num = GetValueFromXML( "NumberOfResults", buf );
        if ( num > 0 ) {
            m_foodCodeInfo = new struct foodCodeInfo [num];

            char    *p, *q, *r;
            p = buf;
            while ( *p ) {
                q = strstr( p, "<Food>" );
                if ( !q )
                    break;
                q += 6;
                r = strstr( q, "</Food>" );
                if ( !r )
                    break;

                strcpy( m_foodCodeInfo[n].foodCD,
                        GetValueFromXML( "FoodCD",   q, r, false ) );
                strcpy( m_foodCodeInfo[n].foodName,
                        GetValueFromXML( "FoodName", q, r, true ) );

                p = r + 7;
                if ( ++n >= num )
                    break;
            }

            strcpy( m_foodCode, m_foodCodeInfo[0].foodCD );
        }

        delete [] buf;
    }

    return ( num );
}

int
CBlogoleeDlg::getAreaCodeInfo()
{
    int         num = 0, n = 0;
    FILE        *fp = NULL;
    char        filename[MAX_PATH];
    struct stat s;
    bool        needToGet = false;

    sprintf( filename, "%s/area.xml", m_settingDir );

    if ( !stat( filename, &s ) ) {
        time_t  t = time( NULL );
        if ( s.st_mtime < t - 72 * 60 * 60 )
            needToGet = true;
                /* �O��̎擾���� 72���Ԉȏ�o�߂��Ă���ꍇ�̂ݍĎ擾���� */
    }
    else
        needToGet = true;
                /* �t�@�C�������݂��Ȃ��̂ŁA�擾���� */

    if ( needToGet ) {
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        char        url[MAX_URLLENGTH];
        char        *response;
        size_t      sz = MAX_CONTENT_SIZE;

        response = (char *)malloc( sz );
        if ( !response )
            return ( num );

        ProceedingDialog    *pdlg;
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
        pdlg->ChangeDialogText( "������Web�T�[�r�X",
                                "�u�G���A�R�[�h�Ή��\�v���擾���c�c" );

        strcpy( url, "http://jws.jalan.net/content/data/area.xml" );
        setUpReceiveBuffer( response, sz );
        http_get( url, response );
        if ( *response ) {
            fp = fopen( filename, "w" );
            if ( fp ) {
                fputs( response, fp );
                fclose( fp );
            }
        }
        else
            MessageBox( "�u�G���A�R�[�h�Ή��\�v�̎擾�Ɏ��s���܂���    ",
                        "�擾���s",
                        MB_OK|MB_ICONWARNING );
        delete pdlg;
        free( response );
    }

    char    *buf = readXML( filename );
    if ( buf ) {
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        char        *p;
        char        *q;

        p = strstr( buf, "<Error" );
        if ( p ) {
            CString errorMessage = "�f�[�^�̎擾�Ɏ��s���܂���";

            p += 6;
            q = strchr( p, '>' );
            if ( q ) {
                p = q + 1;
                q = strstr( p, "</Error>" );
                if ( q ) {
                    errorMessage = GetValueFromXML( "Message", p, q, true );
                    errorMessage += "    ";
                }
            }

            MessageBox( errorMessage, "�G���A�R�[�h�Ή��\�v�擾���s",
                        MB_OK|MB_ICONWARNING );
            unlink( filename );
        }
        else {
            p = buf;
            while ( *p ) {
                q = strstr( p, "Area cd=\"" );
                if ( q ) {
                    num++;
                    p = q + 9;
                }
                else
                    break;
            }
        }

        if ( num > 0 ) {
            char    largeAreaName[MAX_AREA_NAME_LEN];
            char    smallAreaName[MAX_AREA_NAME_LEN];
            m_areaCodeInfo = new struct areaCodeInfo [num];

            p = buf;
            largeAreaName[0] = NUL;
            while ( *p ) {
                q = strstr( p, "Area cd=\"" );
                if ( q ) {
                    p = q + 9;
                    q = strchr( p, '"' );
                    if ( !q )
                        break;
                    strncpy( m_areaCodeInfo[n].areaCode, p, q - p );
                    m_areaCodeInfo[n].areaCode[q - p] = NUL;

                    q++;
                    p = strstr( q, "name=\"" );
                    if ( !p )
                        break;
                    p += 6;
                    q = strchr( p, '"' );
                    if ( !q )
                        break;
                    strncpy( m_areaCodeInfo[n].areaName, p, q - p );
                    m_areaCodeInfo[n].areaName[q - p] = NUL;
                    p = utf2sjis( m_areaCodeInfo[n].areaName );
                    if ( p )
                        strcpy( m_areaCodeInfo[n].areaName, p );

                    if ( m_areaCodeInfo[n].areaCode[
                            strlen(m_areaCodeInfo[n].areaCode) - 1] == '0' )
                        strcpy( largeAreaName, m_areaCodeInfo[n].areaName );
                    else {
                        sprintf( smallAreaName, "%s - %s",
                                 largeAreaName, m_areaCodeInfo[n].areaName );
                        strcpy( m_areaCodeInfo[n].areaName, smallAreaName );
                    }

                    p = q + 1;
                    n++;
                }
                else
                    break;
            }
        }

        delete [] buf;
    }

    return ( num );
}


void    CBlogoleeDlg::makeHeadOfXslt(
                FILE       *fp,
                const char *selector,
                const char *sourceHref /* = NULL */
            )
{
    fputs( "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
           "<xsl:stylesheet xmlns:xsl=\"http://www.w3.org/1999/XSL/"
           "Transform\" version=\"1.0\">\n"
           "\n"
           "  <xsl:template match=\"/\">\n"
           "    <xsl:apply-templates select=\"Results\"/>\n"
           "  </xsl:template>\n"
           "\n"
           "  <xsl:template match=\"Results\">\n"
           "    <html xml:lang=\"ja\" lang=\"ja\">\n"
           "      <head>\n", fp );
    fputs( sjis2utf(
           "        <title>��������: "
                   "<xsl:value-of select=\"NumberOfResults\"/>��</title>\n" ),
           fp );
    fputs( "      <style type=\"text/css\">\n"
           "          img { border: 0; margin: 6px 6px 6px 12px; }\n"
           "          hr {color: #aaa; height: 3px; }\n"
           "          h3 { margin-left: 60px; color: #F00; }\n"
           "          .head { float: left; width: 48%; }\n"
           "          .headDescription { margin: 0px 0px 0px 10px; "
                                        "font-weight: bold; }\n"
           "          .headAddress { margin: 5px 0px 0px 18px; }\n"
           "          .headAccess { margin: 5px 0px 0px 18px; }\n"
           "          .headTime { margin: 5px 0px 0px 18px; }\n"
           "          .picture { float: left; wirth: 50%; }\n"
           "          .reset { clear: both; }\n"
           "          .footer { margin-top: 0px; margin-bottom: 0px;\n"
           "                    font-size: x-small; font-weight: bold; }\n"
           "          .author { font-style: italic; }\n"
           "      </style>\n"
           "      </head>\n", fp );
    fprintf( fp,
           "      <body>\n"
           "       <xsl:apply-templates select=\"%s\"/>\n"
           "        <p class=\"footer\">\n"
           "          Powerd by %s\n"
           "          [\n"
           "          generated by `<a href=\"http://watcher.moe-nifty.com/"
                     "memo/2007/03/blogolee.html\">BloGolEe</a>'.\n"
           "          `BloGolEe ' is presented by\n"
           "          <span class=\"author\">tsupo at na.rim.or.jp</span>\n"
           "          ]\n"
           "        </p>\n"
           "      </body>\n"
           "    </html>\n"
           "  </xsl:template>\n"
           "\n",
             selector,
             sjis2utf( sourceHref
                         ? sourceHref
                         : "<a href=\"http://jws.jalan.net/\">"
                           "������ Web �T�[�r�X</a>" ) );
}

void    CBlogoleeDlg::makeTailOfXslt( FILE *fp, bool jalan /* = false */ )
{
    if ( jalan )
        fputs(
           "\n"
             "<xsl:template match=\"Area\">"
               "<xsl:value-of select=\"Prefecture\"/> - "
               "<xsl:value-of select=\"LargeArea\"/> - "
               "<xsl:value-of select=\"SmallArea\"/>"
             "</xsl:template>\n", fp );
    fputs( "\n"
           "</xsl:stylesheet>\n", fp );
}

void    CBlogoleeDlg::makeXsltOfSearchShopResult( const char *base )
{    
    CString s = m_settingDir;
    s += "/result";
    s += base;
    s += ".xsl";

    FILE    *fp = fopen( s, "w" );
    if ( fp ) {
        makeHeadOfXslt( fp, base,
            "<a href=\"http://www.hotpepper.jp/\">�z�b�g�y�b�p�[.jp</a>" );
        fprintf( fp,
               "<xsl:template match=\"%s\">\n",
                 base );
        fputs( sjis2utf(
               "  <h1>"
                   "<a>"
                     "<xsl:attribute name=\"href\">"
                       "<xsl:value-of select=\"ShopUrl\" />"
                     "</xsl:attribute>"
                     "<xsl:value-of select=\"ShopName\"/>"
                   "</a>"
                 "</h1>\n"
               "  <div class=\"head\">\n"
               "    <h2>"
                     "<xsl:value-of select=\"LargeAreaName\"/> - "
                     "<xsl:value-of select=\"MiddleAreaName\"/> - "
                     "<xsl:value-of select=\"SmallAreaName\"/>"
                   "</h2>\n"
               "    <h3>"
                     "<xsl:value-of select=\"GenreCatch\"/>"
                   "</h3>\n"
               "    <p class=\"headDescription\">"
                     "<xsl:value-of select=\"ShopCatch\"/>"
                   "</p>\n"
               "    <p class=\"headAddress\">"
                     "<xsl:value-of select=\"ShopAddress\"/>"
                   "</p>\n"
               "    <p class=\"headAccess\">"
                     "<xsl:value-of select=\"Access\"/>"
                   "</p>\n"
               "    <p class=\"headTime\">"
                     "�c�Ǝ���: "
                       "<xsl:value-of select=\"Open\"/> / "
                     "�x�Ɠ�: "
                       "<xsl:value-of select=\"Close\"/>"
                   "</p>\n"
               "    <ul>\n"
               "      <li>"
                       "<a>"
                         "<xsl:attribute name=\"href\">"
                           "http://map.yahoo.co.jp/pl?sc=3&amp;lat="
                           "<xsl:value-of select=\"Latitude\"/>"
                           "&amp;lon="
                           "<xsl:value-of select=\"Longitude\"/>"
                         "</xsl:attribute>"
                         "Yahoo! �n�}���"
                       "</a>"
                     "</li>\n"
               "      <li>"
                       "<a>"
                         "<xsl:attribute name=\"href\">"
                           "http://maps.google.co.jp/?"
                           "ie=UTF8&amp;z=17&amp;ll="
                           "<xsl:value-of select=\"Latitude\"/>,"
                           "<xsl:value-of select=\"Longitude\"/>"
                         "</xsl:attribute>"
                         "Google�}�b�v"
                       "</a>"
                     "</li>\n"
               "    </ul>\n"
               "  </div>\n"
               "  <div class=\"picture\">\n"
               "    <a>"
                     "<xsl:attribute name=\"href\">"
                       "<xsl:value-of select=\"ShopUrl\" />"
                     "</xsl:attribute>"
                     "<img>"
                       "<xsl:attribute name=\"src\">"
                         "<xsl:apply-templates select=\"PictureUrl\"/>"
                       "</xsl:attribute>"
                       "<xsl:attribute name=\"alt\">"
                        "<xsl:value-of select=\"ShopName\"/>"
                       "</xsl:attribute>"
                     "</img>"
                   "</a>\n"
                   "<img>"
                     "<xsl:attribute name=\"src\">"
                       "<xsl:value-of select=\"KtaiQRUrl\"/>"
                     "</xsl:attribute>"
                   "</img>\n"
               "  </div>\n"
               "  <hr class=\"reset\" />\n"
               "</xsl:template>\n"
               "\n"
               "<xsl:template match=\"PictureUrl\">\n"
               "  <xsl:value-of select=\"PcLargeImg\" /> \n"
               "</xsl:template>\n" ), fp );
        makeTailOfXslt( fp );

        fclose( fp );
    }
}

CString CBlogoleeDlg::makeXmlOfSearchResult(
            const char *base,
            const char *response
        )
{
    CString s = m_settingDir;
    s += "/result";
    s += base;
    s += ".xml";

    FILE    *fp = fopen( s, "w" );
    if ( fp ) {
        const char  *p;

        fputs( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n", fp );
        fprintf( fp,
               "<?xml-stylesheet href=\"./result%s.xsl\" type=\"text/xsl\" "
               "media=\"screen\"?>\n",
               base );
        fputs( "<Results>\n", fp );
        p = strstr( response, "<Results>" );
        if ( !p )
            p = strstr( response, "<Results " );
        if ( p ) {
            p = strchr( p + 8, '>' );
            if ( p )
                fputs( p + 1, fp );
        }
        fclose( fp );
    }

    return ( s );
}


CString CBlogoleeDlg::makeXmlOfSearchShopResult( const char *response )
{
    const char  *base = "Shop";

    makeXsltOfSearchShopResult( base );
    CString s = makeXmlOfSearchResult( base, response );

    return ( s );
}


void    CBlogoleeDlg::makeXsltOfSearchOnsenResult( const char *base )
{
    CString s = m_settingDir;
    s += "/result";
    s += base;
    s += ".xsl";

    FILE    *fp = fopen( s, "w" );
    if ( fp ) {
        makeHeadOfXslt( fp, base );
        fprintf( fp,
               "<xsl:template match=\"%s\">\n",
                 base );
        fputs( sjis2utf(
               "  <h1>"
                   "<xsl:value-of select=\"OnsenName\"/>"
                 "</h1>\n"
               "\n"
               "  <div class=\"head\">\n"
               "    <h2>"
                     "<xsl:apply-templates select=\"Area\"/>"
                   "</h2>\n"
               "    <p class=\"headDescription\">"
                     "<xsl:value-of select=\"NatureOfOnsen\"/>"
                   "</p>\n"
               "    <p class=\"headAddress\">"
                     "<xsl:value-of select=\"OnsenAddress\"/>"
                   "</p>\n"
               "  </div>\n"
               "  <hr class=\"reset\" />\n"
               "</xsl:template>\n" ), fp );
        makeTailOfXslt( fp, true );

        fclose( fp );
    }
}

CString CBlogoleeDlg::makeXmlOfSearchOnsenResult( const char *response )
{
    const char  *base = "Onsen";

    makeXsltOfSearchOnsenResult( base );
    CString s = makeXmlOfSearchResult( base, response );

    return ( s );
}

void    CBlogoleeDlg::makeXsltOfSearchHotelResult( const char *base )
{
    CString s = m_settingDir;
    s += "/result";
    s += base;
    s += ".xsl";

    FILE    *fp = fopen( s, "w" );
    if ( fp ) {
        makeHeadOfXslt( fp, base );
        fprintf( fp,
               "<xsl:template match=\"%s\">\n",
                 base );
        fputs( sjis2utf(
               "  <h1>"
                   "<a>"
                     "<xsl:attribute name=\"href\">"
                       "<xsl:value-of select=\"HotelDetailURL\"/>"
                     "</xsl:attribute>"
                     "<xsl:value-of select=\"HotelName\"/>"
                   "</a>"
                 "</h1>\n"
               "  <div class=\"head\">\n"
               "    <h2>"
                     "<xsl:apply-templates select=\"Area\"/>"
                   "</h2>\n"
               "    <h3>"
                     "<xsl:value-of select=\"HotelCatchCopy\"/>"
                   "</h3>\n"
               "    <p class=\"headDescription\">"
                     "<xsl:value-of select=\"HotelCaption\"/>"
                   "</p>\n"
               "    <p class=\"headAddress\">"
                     "<xsl:value-of select=\"PostCode\"/>"
                     "<xsl:value-of select=\"HotelAddress\"/>"
                   "</p>\n"
               "    <p class=\"headAddress\">"
                     "<xsl:value-of select=\"AccessInformation\"/>"
               "    </p>\n"
               "    <p class=\"headAddress\">"
                      "�`�F�b�N�C��: "
                         "<xsl:value-of select=\"CheckInTime\"/> / "
                      "�`�F�b�N�A�E�g: "
                        "<xsl:value-of select=\"CheckOutTime\"/>"
                   "</p>\n"
               "\n"
               "  </div>\n"
               "  <div class=\"picture\">\n"
                   "<a>"
                     "<xsl:attribute name=\"href\">"
                       "<xsl:value-of select=\"HotelDetailURL\" />"
                     "</xsl:attribute>"
                     "<img>"
                       "<xsl:attribute name=\"src\">"
                         "<xsl:value-of select=\"PictureURL\"/>"
                       "</xsl:attribute>"
                       "<xsl:attribute name=\"alt\">"
                         "<xsl:value-of select=\"PictureCaption\"/>"
                       "</xsl:attribute>"
                     "</img>"
                   "</a>\n"
               "  </div>\n"
               "  <hr class=\"reset\" />\n"
               "</xsl:template>\n" ), fp );
        makeTailOfXslt( fp, true );

        fclose( fp );
    }
}

CString CBlogoleeDlg::makeXmlOfSearchHotelResult( const char *response )
{
    const char  *base = "Hotel";

    makeXsltOfSearchHotelResult( base );
    CString s = makeXmlOfSearchResult( base, response );

    return ( s );
}


void    CBlogoleeDlg::changeAreaInfo( int prefCode )
{
    char    prefArea[3];
    bool    found = false;

    sprintf( prefArea, "%02d", prefCode );

    m_areaList2.ResetContent();
    m_areaList2.AddString( "�w��Ȃ�" );
    for ( int i = 0; i < m_numOfAreaCodes; i++ ) {
        if ( !strncmp( m_areaCodeInfo[i].areaCode, prefArea, 2 ) ) {
            found = true;
            m_areaList2.AddString( m_areaCodeInfo[i].areaName );
        }
        else if ( found == true )
            break;
    }
    m_areaList2.SetCurSel( 0 );
    m_areaCode[0] = NUL;
}

void    CBlogoleeDlg::switchJalanLink()
{
    CButton *q = (CButton *)GetDlgItem( IDC_BUTTON_JALAN_LINK );
    if ( (m_numOfAreaCodes > 0)          && 
         (m_sid.GetLength() > 0)         &&
         (m_pidForJalan.GetLength() > 0)    )
        q->EnableWindow( TRUE );
    else
        q->EnableWindow( FALSE );
}

CString CBlogoleeDlg::searchJalan()
{
    char    url[MAX_URLLENGTH];
    int     count = 20;

    url[0] = NUL;

    if ( m_areaCode[0] == NUL ) {
        // �s���{���R�[�h�Ō���
        if ( m_hotelTypeNum == 5 ) {
            // ����T�[�`
            sprintf( url,
                     "http://jws.jalan.net/APICommon/OnsenSearch/V1/?"
                     "key=%s&pref=%02d0000&onsen_q=0&count=%d",
                     "ari111107effef", m_prefCode, count );
        }
        else {
            // �h�T�[�`
            sprintf( url,
                     "http://jws.jalan.net/APILite/HotelSearch/V1/?"
                     "key=%s&pref=%02d0000&h_type=%d&count=%d",
                     "ari111107effef", m_prefCode, m_hotelTypeNum, count );
        }
    }
    else if ( m_areaCode[strlen(m_areaCode) - 1] == '0' ) {
        // ��G���A�R�[�h�Ō���
        if ( m_hotelTypeNum == 5 ) {
            // ����T�[�`
            sprintf( url,
                     "http://jws.jalan.net/APICommon/OnsenSearch/V1/?"
                     "key=%s&l_area=%s&onsen_q=0&count=%d",
                     "ari111107effef", m_areaCode, count );
        }
        else {
            // �h�T�[�`
            sprintf( url,
                     "http://jws.jalan.net/APILite/HotelSearch/V1/?"
                     "key=%s&l_area=%s&h_type=%d&count=%d",
                     "ari111107effef", m_areaCode, m_hotelTypeNum, count );
        }
    }
    else {
        // ���G���A�R�[�h�Ō���
        if ( m_hotelTypeNum == 5 ) {
            // ����T�[�`
            sprintf( url,
                     "http://jws.jalan.net/APICommon/OnsenSearch/V1/?"
                     "key=%s&s_area=%s&onsen_q=0&count=%d",
                     "ari111107effef", m_areaCode, count );
        }
        else {
            // �h�T�[�`
            sprintf( url,
                     "http://jws.jalan.net/APILite/HotelSearch/V1/?"
                     "key=%s&s_area=%s&h_type=%d&count=%d",
                     "ari111107effef", m_areaCode, m_hotelTypeNum, count );
        }
    }

    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    response = (char *)malloc( sz );
    setUpReceiveBuffer( response, sz );
    http_get( url, response );
    if ( *response ) {
        char    *p = strstr( response, "<Error" );
        if ( p ) {
            CString errorMessage = "�f�[�^�̎擾�Ɏ��s���܂���";
            char    *q;

            p += 6;
            q = strchr( p, '>' );
            if ( q ) {
                p = q + 1;
                q = strstr( p, "</Error>" );
                if ( q ) {
                    errorMessage = GetValueFromXML( "Message", p, q, true );
                    errorMessage += "    ";
                }
            }

            MessageBox( errorMessage, "�f�[�^�擾���s",
                        MB_OK|MB_ICONWARNING );

            url[0] = NUL;

#ifdef  _DEBUG
            const char  *base;
            if ( m_hotelTypeNum == 5 )
                base = "Onsen";
            else 
                base = "Hotel";
            CString s = m_settingDir;
            s += "/result";
            s += base;
            s += ".xml";

            FILE    *fp;
            if ( (fp = fopen( s, "r" )) != NULL ) {
                fclose( fp );
                int r = MessageBox(
                            "����̓f�[�^�̎擾�Ɏ��s���܂������A�ȑO�擾����"
                            "�f�[�^���c���Ă���悤�ł��B\n�ȑO�擾�����f�[�^"
                            "��\�����܂���?",
                                    "�f�[�^�擾���s",
                                    MB_YESNO|MB_ICONWARNING );
                if ( r == IDYES )
                    strcpy( url, s );
            }
#endif
        }
        else {
            int results = GetValueFromXML( "NumberOfResults", response );
            if ( results <= 0 )
                MessageBox( "�w�肵�������Ɉ�v����f�[�^�͌�����"
                            "�܂���ł���    ",
                            "�Y���f�[�^�Ȃ�",  MB_OK|MB_ICONWARNING );
            else {
                if ( m_hotelTypeNum == 5 ) {
                    // �������ʕ\���p�� xml �𐶐�
                    strcpy( url, makeXmlOfSearchOnsenResult( response ) );
                }
                else {
                    // �������ʕ\���p�� xml �𐶐�
                    strcpy( url, makeXmlOfSearchHotelResult( response ) );
                }
            }
        }
    }
    else
        MessageBox( "�T�[�o�Ƃ̒ʐM�Ɏ��s���܂���   ",
                    "�ʐM�G���[",  MB_OK|MB_ICONWARNING );

    CString s = url;
    return ( s );
}

void    CBlogoleeDlg::makeAffiliateLink( const char *filename )
{
    char    *buf = readXML( filename );
    if ( buf ) {
        char    *p, *q, *r;
        int     numOfHotelInfo = 0;

        p = buf;
        q = strstr( p, "<DisplayPerPage>" );
        if ( !q ) {
            delete [] buf;
            return;
        }
        numOfHotelInfo = atol( q + 16 );
        if ( numOfHotelInfo <= 0 ) {
            delete [] buf;
            return;
        }

        size_t      sz = MAX_CONTENT_SIZE;
        char        temp[MAX_URLLENGTH];
        char        *response = new char [sz];
        HotelInfo   *hp = new HotelInfo [numOfHotelInfo];
        int         n = 0;
        while ( *p ) {
            q = strstr( p, "<Hotel>" );
            if ( !q )
                break;
            q += 7;
            r = strstr( q, "</Hotel>" );
            if ( !r )
                break;

            // HotelName
            hp[n].m_hotelName = GetValueFromXML( "HotelName", q, r, true );

            // HotelDetailURL
            hp[n].m_hotelDetailURL =
                            GetValueFromXML( "HotelDetailURL", q, r, false );

            setUpReceiveBuffer( response, sz );
            http_get( decodeURL(hp[n].m_hotelDetailURL), response );
            if ( *response )
                hp[n].m_hotelDetailURL = getCurrentLocation( temp );

            // HotelCatchCopy
            hp[n].m_hotelCatchCopy =
                            GetValueFromXML( "HotelCatchCopy", q, r, true );

            // HotelCaption
            hp[n].m_hotelCaption =
                            GetValueFromXML( "HotelCaption", q, r, true );

            // HotelAddress
            hp[n].m_hotelAddress =
                            GetValueFromXML( "HotelAddress", q, r, true );

            // CheckInTime
            hp[n].m_checkInTime = GetValueFromXML("CheckInTime", q, r, true);

            // CheckOutTime
            hp[n].m_checkOutTime =
                            GetValueFromXML( "CheckOutTime", q, r, true );

            // PictureURL
            hp[n].m_pictureURL = GetValueFromXML( "PictureURL", q, r, false );

            // PictureCaption
            hp[n].m_pictureCaption =
                            GetValueFromXML( "PictureCaption", q, r, true );

            p = r + 8;
            if ( ++n >= numOfHotelInfo )
                break;
        }

        delete [] response;
        delete [] buf;

        CHotelDialog    dlg;

        dlg.m_numOfHotelInfo = n;
        dlg.m_hotelInfo      = hp;
        dlg.m_sid            = m_sid;
        dlg.m_pid            = m_pidForJalan;

        dlg.DoModal();

        delete [] hp;
    }
}

bool    CBlogoleeDlg::IsInner( int id, WORD wX, WORD wY )
{
    CRect   rcClient;
    CStatic *s = (CStatic *)GetDlgItem( id );
    bool    ret = false;

    s->GetWindowRect( &rcClient );
    if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
         (wY >= rcClient.top)  && (wY <= rcClient.bottom)    )
        ret = true;

    return ( ret );
}

bool
CBlogoleeDlg::SetSigInfo(
        CString    &sID1, CString    &sID2,
        const char *sig1, const char *sig2
    )
{
    char    id1[BUFSIZ];
    char    id2[BUFSIZ];
    BOOL    ret;

    ret = setSigInfo( id1, id2, sig1, sig2, "-op", "ee-" );
    if ( ret ) {
        sID1 = id1;
        sID2 = id2;
    }

    return ( ret ? true : false );
}

bool
CBlogoleeDlg::SetSigInfo(
        CString    &sID1, CString    &sID2, CString    &sID3,
        const char *sig1, const char *sig2, const char *sig3
    )
{
    char    id1[BUFSIZ];
    char    id2[BUFSIZ];
    char    id3[BUFSIZ];
    BOOL    ret = FALSE;

    ret = setSigInfo3( id1, id2, id3, sig1, sig2, sig3,
                       "-ts", "ee-", "-op", "en-" );
    if ( ret ) {
        sID1 = id1;
        sID2 = id2;
        sID3 = id3;
    }

    return ( ret ? true : false );
}

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeDlg ���b�Z�[�W �n���h��

BOOL CBlogoleeDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL) {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    SetIcon(m_hIcon, TRUE);     // �傫���A�C�R����ݒ�
    SetIcon(m_hIcon, FALSE);    // �������A�C�R����ݒ�

    switchKeyword( m_keyword );

    return TRUE;
}

void CBlogoleeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else {
        CDialog::OnSysCommand(nID, lParam);
    }
}

void CBlogoleeDlg::OnPaint() 
{
    if (IsIconic()) {
        CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // �N���C�A���g�̋�`�̈���̒���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1)  / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        dc.DrawIcon(x, y, m_hIcon);
    }
    else {
        CDialog::OnPaint();
    }
}

HCURSOR CBlogoleeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


bool    CBlogoleeDlg::getParameter( bool savedForcely /* = FALSE */ )
{
    bool    ret = false;
    CEdit   *p;

    if ( m_blogKind == unset ) {
        MessageBox( "Blog��ʂ�ݒ肵�Ă�������    ",
                    "�ݒ�m�F", MB_OK|MB_ICONWARNING );
        return ( ret );
    }

    // �u���O login �p�X���[�h (optional)
    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_PASSWORD );
    p->GetWindowText( m_blogPassword );

    // Amazon associete ID (optional)
    p = (CEdit *)GetDlgItem( IDC_EDIT_ASSOCIATE_ID );
    p->GetWindowText( m_associateID );

    // �y�V�A�t�B���G�C�gID (optional)
    p = (CEdit *)GetDlgItem( IDC_EDIT_RAKUTEN_ID );
    p->GetWindowText( m_rakuten_affiliateID );

    // �u���O login ID (�K�{)
    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_USERNAME );
    p->GetWindowText( m_blogUserName );
    if ( (m_blogUserName.GetLength() <= 0) && (savedForcely == false) ) {
        MessageBox( "blog ��login����Ƃ��̃��[�U����ݒ肵�Ă�������    ",
                    "�ݒ�m�F", MB_OK|MB_ICONWARNING );
        return ( ret );
    }

    // �G���h�|�C���g URL (optional)
    p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );
    p->GetWindowText( m_endpointURL );
    if ( (m_endpointURL.GetLength() <= 0) && (savedForcely == false) ) {
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

                // -- �G���h�|�C���gURL �� blog ID ���擾
                char    id[MAX_BLOGIDLENGTH + 1];
                char    *url = NULL;

                memset( id, 0x00, MAX_BLOGIDLENGTH + 1 );
                if ( m_blogKind == atomAPI )
                    url = getEndpointURLbyAutoDiscoveryOnAtomAPI(
                                                         topPageURL, id );
                else
                    url = getEndpointURLbyAutoDiscovery( topPageURL, id );

                if ( url && *url ) {
                    MessageBox( "�G���h�|�C���gURL�̎擾�ɐ������܂����B    ",
                                "�擾����", MB_OK|MB_ICONINFORMATION );
                    m_endpointURL = url;
                    p->SetWindowText( (const char *)m_endpointURL );

                    if ( id[0] ) {
                        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_ID );
                        m_blogID = id;
                        p->SetWindowText( (const char *)m_blogID );
                    }
                }
            }

            if ( m_endpointURL.GetLength() <= 0 ) {
                MessageBox( "�G���h�|�C���gURL��ݒ肵�Ă�������    ",
                            "�ݒ�m�F", MB_OK|MB_ICONWARNING );
                return ( ret );
            }
        }
    }

    // blog ID (optional)
    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_ID );
    p->GetWindowText( m_blogID );
    if ( (m_blogID.GetLength() <= 0) && (savedForcely == false) ) {
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
             (m_blogKind == webryX )      ||
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
                return ( ret );
            }

#define MAX_BLOGS       30  /* ����V�X�e�����ő�ݒu�\blog�� */
            BLOGINF blogInfo[MAX_BLOGS];
            int     numOfBlogs = MAX_BLOGS;
            int     r;

            /* --- ���e�\�� blog �ꗗ�̎擾 */
            setTargetURL( m_endpointURL );
            if ( (m_blogKind == livedoor) ||
                 (m_blogKind == lovelog)  ||
                 (m_blogKind == sonet)    ||
                 (m_blogKind == vox)      ||
                 (m_blogKind == hatena)   ||
                 (m_blogKind == blogger)  ||
                 (m_blogKind == atomAPI)     ) {
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
            if ( r == 1 ) {
                MessageBox( "blog ID �̎擾�ɐ������܂����B    ",
                            "�擾����", MB_OK|MB_ICONINFORMATION );
                m_blogID = blogInfo[0].blogID;  /* �m�� */

                if ( m_blogID == "" )
                    if ( (m_blogKind == msnSpaces) ||
                         (m_blogKind == webryX)       )
                        m_blogID = "MyBlog";

                p->SetWindowText( (const char *)m_blogID );
            }
            else if ( r > 1 ) {
                /* ---- ���e�� blog �̑I�� */
                int rr = selectBlog( blogInfo, r );
                if ( (rr >= 0) && (rr < r) ) {
                    r = rr;
                    m_blogID = blogInfo[r].blogID;  /* �m�� */

                    if ( m_blogID == "" )
                        if ( (m_blogKind == msnSpaces) ||
                             (m_blogKind == webryX)       )
                            m_blogID = "MyBlog";

                    p->SetWindowText( (const char *)m_blogID );
                    MessageBox( "blog ID �̎擾�ɐ������܂����B    ",
                                "�擾����", MB_OK|MB_ICONINFORMATION );
                }
                else {
                    MessageBox( "blog ID ��ݒ肵�Ă�������    ",
                                "�ݒ�m�F", MB_OK|MB_ICONWARNING );
                    return ( ret );
                }
            }
            else {
                MessageBox( "blog ID �̎擾�Ɏ��s���܂����B\n"
                            "blog �� login ���郆�[�U�����p�X���[�h��"
                            "�Ԉ���Ă��Ȃ����A�m�F���Ă��������B    ",
                            "�擾���s", MB_OK|MB_ICONWARNING );
                return ( ret );
            }
        }
        else if ( m_blogKind == newPostOnly ) {
            m_blogID = "0";
            p->SetWindowText( (const char *)m_blogID );
        }
    }

    // blog �̃g�b�v�y�[�W�� URL (optional)
    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_URL );
    p->GetWindowText( m_blogURL );

    // �J�e�S���� (option)
    CString     categoryString;
    int         location = m_categoryList.GetCurSel();

    if ( location >= 0 ) {
    	m_categoryList.GetText( location, categoryString );
        m_categoryName = categoryString;
    }

    ret = true;

    return ( ret );
}


typedef struct paramForPostArticle  {
    ARTICLE_INFO    article;
    POST_INFO       postInfo;
}   BLOGOLEE_PARAM;

UINT
ExecutePostArticle( LPVOID pParam )
{
    const char *p = (const char *)pParam;

    if ( p ) {
        BLOGOLEE_PARAM  *pp = (BLOGOLEE_PARAM *)p;
        postArticle( &(pp->article), &(pp->postInfo) );
    }

    return ( 0 );
}

void CBlogoleeDlg::OnExecutePostArticle() 
{
    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    bool            buttonState = true;
    CString         buttonStr;
    CButton         *bp = (CButton *)GetDlgItem( IDOK );
    bp->GetWindowText( buttonStr );
    if ( buttonStr.Compare( "���e" ) != 0 )
        buttonState = false;

    // �p�����[�^�m��
    if ( getParameter() == false )
        return;

    // �ݒ�t�@�C���ۑ�
    saveSetting();

    if ( buttonState == false ) {
        if ( m_endpointURL.GetLength() > 0  )
            bp->SetWindowText( "���e" );
        return;
    }

    CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

    // �e��{�^���� disable �ɂ���
 // bp = (CButton *)GetDlgItem( IDOK );
    BOOL    bOk = bp->IsWindowEnabled();
    bp->EnableWindow( FALSE );

    bp = (CButton *)GetDlgItem( IDCANCEL );
    BOOL    bCancel = bp->IsWindowEnabled();
    bp->EnableWindow( FALSE );

    bp = (CButton *)GetDlgItem( IDC_BUTTON_SWITCH_BLOG );
    BOOL    bSwitchBlog = bp->IsWindowEnabled();
    bp->EnableWindow( FALSE );

    bp = (CButton *)GetDlgItem( IDC_BUTTON_BROWSE_BLOG );
    BOOL    bBrowseBlog = bp->IsWindowEnabled();
    bp->EnableWindow( FALSE );

    bp = (CButton *)GetDlgItem( IDC_BUTTON_GET_CATEGORIES );
    BOOL    bGetcategories = bp->IsWindowEnabled();
    bp->EnableWindow( FALSE );

    BLOGOLEE_PARAM  param;
    const char      *p;

    // �L���薼
    param.article.title_size = m_article_title.GetLength() + 32;
    param.article.title =
            (char *)malloc( param.article.title_size );
    if ( !param.article.title )
        goto exit;
    strcpy( param.article.title, (const char *)m_article_title );

    // �L���{��
    param.article.body_size = m_article_description.GetLength() + 32 +
                                (m_keyword
                                    ? m_article_description.GetLength() * 64
                                    : 0                                     ) +
                                (m_similarity
                                    ? MAX_CONTENT_SIZE
                                    : 0               );
    param.article.body = (char *)malloc( param.article.body_size );
    if ( !param.article.body )
        goto exit;
    strcpy( param.article.body, (const char *)m_article_description );

    // �L���T�v
    param.article.summary_size = 0;
    param.article.summary = NULL;
    p = (const char *)m_article_summary;
    if ( p && *p ) {
        param.article.summary_size = strlen(p) + 32;
        param.article.summary = (char *)malloc( param.article.summary_size );
        if ( !param.article.summary )
            goto exit;
        strcpy( param.article.summary,  p );
    }
 
    // �ǋL
    param.article.extended_size = 0;
    param.article.extended = NULL;
    p = (const char *)m_article_extended;
    if ( p && *p ) {
        param.article.extended_size = strlen(p) + 32;
        param.article.extended = (char *)malloc(param.article.extended_size);
        if ( !param.article.extended )
            goto exit;
        strcpy( param.article.extended,  p );
    }

    // �L�[���[�h
    param.article.keyword_size = 0;
    param.article.keyword = NULL;
    p = (const char *)m_article_keyword;
    if ( p && *p ) {
        param.article.keyword_size = strlen(p) + 32;
        param.article.keyword = (char *)malloc( param.article.keyword_size );
        if ( !param.article.keyword )
            goto exit;
        strcpy( param.article.keyword,  p );
    }

    // ���e�� blog ���
    /* blog login �� */
    strcpy( param.postInfo.blogUserName,
            (const char*)m_blogUserName );

    /* blog �p�X���[�h */
    strcpy( param.postInfo.blogPassword,
            (const char*)m_blogPassword );

    /* blogID */
    if ( m_blogID.GetLength() > 0 )
        strcpy( param.postInfo.blogID,
                (const char*)m_blogID );
    else
        param.postInfo.blogID[0] = NUL;

    /* blog��� */
    param.postInfo.blogType = m_blogKind;

    /* blog URL */
    if ( m_blogURL.GetLength() > 0 )
        strcpy( param.postInfo.blogURL,
                (const char*)m_blogURL );
    else
        param.postInfo.blogURL[0] = NUL;

    /* �G���h�|�C���gURL */
    if ( m_endpointURL.GetLength() > 0 )
        strcpy( param.postInfo.endpointURL,
                (const char*)m_endpointURL );
    else
        param.postInfo.endpointURL[0] = NUL;

    /* �L�[���[�h�����N���݂̗v�� */
    param.postInfo.useHatenaLink = m_keyword ? TRUE : FALSE;

    /* proxy�o�R�ŒʐM���邩�ۂ� */
    param.postInfo.useProxy = cp->m_useProxy ? TRUE : FALSE;

    /* �������߂��g�����ۂ� */
    param.postInfo.useSimilarity   = m_similarity ? TRUE : FALSE;
    param.postInfo.numOfRecomended = m_numOfRecomended;

    /* Amazon�A�\�V�G�C�gID */
    if ( m_associateID.GetLength() > 0 )
        strcpy( param.postInfo.amazonAssociateID,
                (const char*)m_associateID );
    else if ( cp->m_aaID.GetLength() > 0 )
        strcpy( param.postInfo.amazonAssociateID,
                (const char*)cp->m_aaID );
    else
        param.postInfo.amazonAssociateID[0] = NUL;

    if ( cp->m_asID.GetLength() > 0 )
        strcpy( param.postInfo.amazonSubscriptionID,
                (const char*)cp->m_asID );
    else
        param.postInfo.amazonSubscriptionID[0] = NUL;

    /* �y�V�A�t�B���G�C�gID */
    param.postInfo.rakutenDeveloperID[0] = NUL;
    if ( m_rakuten_affiliateID.GetLength() > 0 ) {
        strcpy( param.postInfo.rakutenAffiliateID,
                (const char*)m_rakuten_affiliateID );
        if ( cp->m_rdID.GetLength() > 0 )
            strcpy( param.postInfo.rakutenDeveloperID,
                    (const char*)cp->m_rdID );
    }
    else
        param.postInfo.rakutenAffiliateID[0] = NUL;

    /* ���e�Ώۂ̃J�e�S���� */
    if ( m_categoryName.GetLength() > 0 )
        strcpy( param.postInfo.categoryName,
                (const char*)m_categoryName );
    else
        param.postInfo.categoryName[0] = NUL;

    // postArticle() �N���X���b�h���N��
 // try
    {
        CWinThread  *tp = AfxBeginThread( ExecutePostArticle,
                                          (void *)&param );
        if ( tp ) {
            DWORD   exitCode  = 0;
            int     status;

            ProceedingDialog    *pdlg;
            pdlg = new ProceedingDialog();
            pdlg->Create( IDD_PROCEEDING_DIALOG );
            pdlg->ChangeDialogText( "���e��",
                                    "���e���c�c" );

            // postArticle() �N���X���b�h���I������̂�҂�
            tp->m_bAutoDelete = FALSE;
            do {
                status = GetExitCodeThread( tp->m_hThread, &exitCode );
                if ( status == FALSE )
                    break;
                if ( exitCode == STILL_ACTIVE ) {
                    MSG msg;
                    if ( PeekMessage(&msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE) )
                        DispatchMessage( &msg );
                    Sleep( 200 );
                }
            } while ( exitCode == STILL_ACTIVE );

            delete pdlg;
            delete tp;
        }
    }
 // catch (...) {
 // }

    if ( param.article.keyword )
        free( param.article.keyword );
    if ( param.article.extended )
        free( param.article.extended );
    if ( param.article.summary )
        free( param.article.summary );
    if ( param.article.body )
        free( param.article.body );
    if ( param.article.title )
        free( param.article.title );

  exit:
    // �e��{�^���� enable �ɂ���
    bp = (CButton *)GetDlgItem( IDOK );
    bp->EnableWindow( bOk );

    bp = (CButton *)GetDlgItem( IDCANCEL );
    bp->EnableWindow( bCancel );

    bp = (CButton *)GetDlgItem( IDC_BUTTON_SWITCH_BLOG );
    bp->EnableWindow( bSwitchBlog );

    bp = (CButton *)GetDlgItem( IDC_BUTTON_BROWSE_BLOG );
    bp->EnableWindow( bBrowseBlog );

    bp = (CButton *)GetDlgItem( IDC_BUTTON_GET_CATEGORIES );
    bp->EnableWindow( bGetcategories );
}

void CBlogoleeDlg::OnRadioKeywordOn() 
{
    switchKeyword( true );
}

void CBlogoleeDlg::OnRadioKeywordOff() 
{
    switchKeyword( false );
}

void CBlogoleeDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow && (m_initialized == false) ) {
        CStatic *s;
        CString str;
        str.LoadString( IDS_VERSION );
        s = (CStatic *)GetDlgItem( IDC_VERSION );
        s->SetWindowText( str );

        m_blogKindList.InitStorage( BLOGOLEE_NUM_OF_BLOG_KINDS,
                                    BLOGOLEE_MAX_BLOG_NAME_LENGTH );
        initBlogKindList();

        // �G���h�|�C���gURL���� disable �ɂ���
        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );
        p->SetReadOnly( TRUE );

        // blog ID ���� disable �ɂ���
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_ID );
        p->SetReadOnly( TRUE );

        // blog ���̗��� disable �ɂ���
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_NAME );
        p->SetReadOnly( TRUE );

        // blog URL�̗��� disable �ɂ���
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_URL );
        p->SetReadOnly( TRUE );

        // �ublog �ؑցv�{�^���� disable �ɂ���
        CButton *q = (CButton *)GetDlgItem( IDC_BUTTON_SWITCH_BLOG );
        q->EnableWindow( FALSE );

        // �ublog ������v�{�^���� disable �ɂ���
        q = (CButton *)GetDlgItem( IDC_BUTTON_BROWSE_BLOG );
        q->EnableWindow( FALSE );

        // �u�J�e�S���ꗗ�擾�v�{�^���� disable �ɂ���
        q = (CButton *)GetDlgItem( IDC_BUTTON_GET_CATEGORIES );
        q->EnableWindow( FALSE );

        // �ݒ�t�@�C����ǂݍ���ŉ�ʂ�������
        loadSetting();

        // proxy ���g�����ǂ����̐ݒ�
        CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();

        if ( cp->m_proxyType == CBlogoleeApp::autoDetect ) {
            setConfirmProxyInfoFunc( confirmProxyInfo );
            cp->m_useProxy = isUsedProxy() == TRUE ? true : false;
        }
        if ( cp->m_proxyType == CBlogoleeApp::manualSetting ) {
            if ( cp->m_useProxy ) {
                setProxyInfo( cp->m_proxyServer,
                              (unsigned short)(cp->m_proxyPort),
                              cp->m_proxyUsername,
                              cp->m_proxyPassword );
            }
        }
        setUseProxy( cp->m_useProxy );

        CString sigHead = _T("");
        CString sigMidl = _T("");
        CString sigTail = _T("");
        sigHead.LoadString( IDS_AMAZON_P001 );
        sigTail.LoadString( IDS_AMAZON_P002 );
        SetSigInfo( cp->m_asID, cp->m_aaID, sigHead, sigTail );

        sigHead.LoadString( IDS_RAKUTEN_D001 );
        sigMidl.LoadString( IDS_RAKUTEN_D002 );
        sigTail.LoadString( IDS_RAKUTEN_D003 );
        SetSigInfo( cp->m_rdID, cp->m_raID, cp->m_raID2,
                    sigHead, sigMidl, sigTail );

        if ( m_numOfFoodCodes == 0 ) {
            m_numOfFoodCodes = getFoodCodeInfo();
            if ( m_numOfFoodCodes > 0 ) {
                m_foodeCodeList.InitStorage( m_numOfFoodCodes,
                                             sizeof ( struct foodCodeInfo ) );
                m_foodeCodeList.ResetContent();
                for ( int i = 0; i < m_numOfFoodCodes; i++ )
                    m_foodeCodeList.AddString( m_foodCodeInfo[i].foodName );
                m_foodeCodeList.SetCurSel( 0 );
            }
        }

        if ( m_numOfAreaCodes == 0 ) {
            m_areaList.SetCurSel( 0 );
            m_hotelType.SetCurSel( 0 );

            m_prefCode     = 1;
            m_hotelTypeNum = 0;

            m_numOfAreaCodes = getAreaCodeInfo();
            if ( m_numOfAreaCodes > 0 ) {
                m_areaList2.InitStorage( m_numOfAreaCodes,
                                         sizeof ( struct areaCodeInfo ) );
                changeAreaInfo( m_prefCode );
                m_areaList2.SetCurSel( 0 );
            }
            else {
                // ������.net �������e���̏ꍇ�ȂǁA�u�G���A�R�[�h�Ή��\�v��
                // �擾�Ɏ��s�����ꍇ�́A�����{�^���ƃG���A�R�[�h�I��p�R���{
                // �{�b�N�X���g�p�s�ɂ���
                CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_HOTEL_SEARCH );
                p->EnableWindow( FALSE );

                CComboBox   *cp =
                            (CComboBox *)GetDlgItem( IDC_COMBO_AREA_LIST2 );
                cp->EnableWindow( FALSE );
            }
        }

        LOGFONT tLogFont;
        CFont   *cWndFont;

        cWndFont = GetFont(); 
        cWndFont->GetLogFont( &tLogFont );
        tLogFont.lfUnderline = 1;
        m_cFont.CreateFontIndirect( &tLogFont );

        s = (CStatic *)GetDlgItem( IDC_WEB_HOTPEPPER );
        s->SetFont( &m_cFont, TRUE );

        s = (CStatic *)GetDlgItem( IDC_WEB_JALAN );
        s->SetFont( &m_cFont, TRUE );

        switchPostArticle();
        switchJalanLink();

        m_initialized = true;
    }
}

void CBlogoleeDlg::OnExit() 
{
    // �ݒ�t�@�C���ۑ�
    if ( checkProxyInfo() ) {
        // proxy�֘A�̐ݒ�Ɍ�肪����Ǝv����ꍇ�A����N�����ɍĐݒ�\��
        // ���邽�߁A���܂̐ݒ����������j������
        CBlogoleeApp    *bp = (CBlogoleeApp *)AfxGetApp();
        bp->m_proxyType = CBlogoleeApp::autoDetect;
    }
    saveSetting( TRUE );

    OnOK();
}

void CBlogoleeDlg::OnRadioSimlarityOn() 
{
    switchSimilarity( true );
}

void CBlogoleeDlg::OnRadioSimilarityOff() 
{
    switchSimilarity( false );
}

void CBlogoleeDlg::OnKillfocusEditAssociateId() 
{
    char    buf[MAX_NAMELEN + 1];
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ASSOCIATE_ID );

    memset( buf, 0x00, MAX_NAMELEN + 1 );
    p->GetWindowText( buf, MAX_NAMELEN );
    if ( buf[0] ) {
        if ((strlen( buf ) < 4)                          ||
            (strcmp( buf + strlen(buf) - 3, "-22" ) != 0)  ) {
            MessageBox( "Amazon �A�\�V�G�C�g ID �̒��g���ςł��B    \n"
                        "�ݒ肵�����Ă��������B",
                        "�ݒ�m�F", MB_OK|MB_ICONWARNING );
            p->SetFocus();
        }
        else
            m_associateID = buf;
    }
}

void CBlogoleeDlg::OnButtonGetCategories() 
{
    m_categoryList.ResetContent();
    // �p�����[�^�m��
    if ( getParameter() == false )
        return;

    // �O�̂��߂ɂ�������ۑ�
    saveSetting();
    saveBlogInfo();

    ProceedingDialog    *pdlg;
    pdlg = new ProceedingDialog();
    pdlg->Create( IDD_PROCEEDING_DIALOG );
    pdlg->ChangeDialogText( "�J�e�S���ꗗ�擾��",
                            "�J�e�S���ꗗ�擾���c�c" );

	/* �J�e�S���ꗗ�擾 */
    if ( (m_blogKind == typepad)       ||
         (m_blogKind == typepadJapan ) ||
         (m_blogKind == cocolog )      ||
         (m_blogKind == cocologFree )  ||
         (m_blogKind == blogzine )     ||
         (m_blogKind == seesaa )       ||
         (m_blogKind == netLaputa )    ||
         (m_blogKind == blogG )        ||
         (m_blogKind == newsHandler )  ||
         (m_blogKind == fc2blog )      ||
         (m_blogKind == gooBlog )      ||
         (m_blogKind == drecomX)       ||
         (m_blogKind == yaplogX)       ||
         (m_blogKind == jugemX)        ||
         (m_blogKind == movableType )  ||
         (m_blogKind == mtAPI )           ) {
        /* MovableType �݊� API ���p�\ blog �̏ꍇ */
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        CATLISTINF  categoryList[MAX_CATS];
        long        numOfCategories;

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
                CEdit *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );
                p->SetWindowText( m_endpointURL );
            }
        }

        setTargetURL( m_endpointURL );
        numOfCategories = MAX_CATS;
        getCategoryList( (const char *)m_blogID,
                         (const char *)m_blogUserName,
                         (const char *)m_blogPassword,
                         &numOfCategories,
                         categoryList );    /* Movable Type API */
        if ( numOfCategories > 0 ) {
            int numOfCats = 0;
            for ( long i = 0; i < numOfCategories; i++ ) {
                char    *p = utf2sjis( categoryList[i].categoryName );
                if ( p ) {
                    m_categoryList.AddString( p );
                    numOfCats++;
                }
            }
            numOfCategories = numOfCats;
        }
    }
    else
    if ( (m_blogKind == msnSpaces) ||
         (m_blogKind == webryX )      ) {
        /* Windows Live Spaces �g���� metaWeblog API �̗p blog �̏ꍇ */
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        CATEGORIES  categoryList[MAX_CATS];
        long        numOfC = MAX_CATS;
        int         numOfCategories;

        setTargetURL( m_endpointURL );
        numOfCategories = 
            getCategories( "MyBlog",
                           (const char *)m_blogUserName,
                           (const char *)m_blogPassword,
                           &numOfC,
                           categoryList );
        int numOfCats = 0;
        for ( long i = 0; i < numOfCategories; i++ ) {
            char    *p = utf2sjis( categoryList[i].categoryTitle );
            if ( p ) {
                m_categoryList.AddString( p );
                numOfCats++;
            }
        }
        numOfCategories = numOfCats;
    }
    else
    if ( (m_blogKind == livedoor) ||
         (m_blogKind == lovelog)  ||
         (m_blogKind == sonet)    ||
         (m_blogKind == ameblo)   ||
         (m_blogKind == livedoor) ||
         (m_blogKind == vox )     ||
         (m_blogKind == hatena)   ||
         (m_blogKind == blogger ) ||
         (m_blogKind == atomAPI )    ) {
        /* Atom API ���p�\ blog �̏ꍇ */
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        CATLISTINF  categoryList[MAX_CATS];
        long        numOfC = MAX_CATS;
        int         numOfCategories;

        setTargetURL( m_endpointURL );
        numOfCategories = 
            listCategoriesOnAtomAPI( (const char *)m_blogUserName,
                                     (const char *)m_blogPassword,
                                     (const char *)m_blogID,
                                     &numOfC,
                                     categoryList );
        int numOfCats = 0;
        for ( long i = 0; i < numOfCategories; i++ ) {
            char    *p = utf2sjis( categoryList[i].categoryName );
            if ( p ) {
                m_categoryList.AddString( p );
                numOfCats++;
            }
        }
        numOfCategories = numOfCats;
    }
    else if ( (m_blogKind == echoo)      ||
              (m_blogKind == exciteBlog) ||
              (m_blogKind == rakuten)       ) {
        /* �G�R���O�Aexcite�u���O�A�y�V�u���O �̏ꍇ */
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        CATLISTINF  categoryList[MAX_CATS];
        long        numOfCategories;

        numOfCategories = MAX_CATS;

        switch ( m_blogKind ) {
        case echoo:
            getCategoryListEchoo( (const char *)m_blogUserName,
                                  (const char *)m_blogPassword,
                                  &numOfCategories,
                                  categoryList );
            break;

        case exciteBlog:
            getCategoryListExciteBlog( (const char *)m_blogUserName,
                                       (const char *)m_blogPassword,
                                       &numOfCategories,
                                       categoryList );
            break;

        case rakuten:
            getCategoryListRakuten( (const char *)m_blogUserName,
                                    (const char *)m_blogPassword,
                                    &numOfCategories,
                                    categoryList );
            break;
        }

        if ( numOfCategories > 0 ) {
            for ( long i = 0; i < numOfCategories; i++ ) {
                m_categoryList.AddString( categoryList[i].categoryName );
            }
        }
    }
    else {
        MessageBox(
          "�\���󂠂�܂��񂪁A���̃o�[�W������ �gBloGolEe�h�ł́A    \n"
          "�J�e�S���ꗗ�̎擾�͂ł��܂���",
                    "�J�e�S���ꗗ�擾", MB_OK|MB_ICONWARNING );
    }

    delete pdlg;
}

void CBlogoleeDlg::OnSelchangeListCategory() 
{
    CString     categoryString;
    int         location = m_categoryList.GetCurSel();

	m_categoryList.GetText( location, categoryString );
    m_categoryName = categoryString;
}

void CBlogoleeDlg::OnSelchangeComboBlogKind() 
{
    CString         blogKindString;
    int             location = m_blogKindList.GetCurSel();
    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    bool            useCbox = false;

	m_blogKindList.GetLBText( location, blogKindString );

    if ( !blogKindString.Compare(m_blogKindInfo[location].blogKindString) ) {
        m_blogKind      = m_blogKindInfo[location].blogKind;
        m_endpointURL   = "";
        switchEndpointURL( location );
        switchBlogID();
        switchArticleKeyword();
        switchArticleExtended();
        switchArticleSummary();

        // blog�ʐݒ�t�@�C���ǂݍ���
        int i;
        for ( i = 0; i < m_numOfBlogKinds; i++ ) {
            if ( m_blogKind == m_blogKindInfo[i].blogKind )
                break;
        }
        if ( i < m_numOfBlogKinds ) {
            char    filename[MAX_PATH];

            sprintf( filename, "%s/%s.inf",
                     m_settingDir, m_blogKindInfo[i].blogKindID );
            if ( m_blogKind == newPostOnly ) {
                // �uBlogPet ���甠�v�̂��߂̓��ʏ���
                CString     blogKindString;
                int         location = m_blogKindList.GetCurSel();

	            m_blogKindList.GetLBText( location, blogKindString );
                if ( blogKindString.Compare( "BlogPet ���甠" ) == 0 ) {
                    sprintf( filename, "%s/%s.inf",
                             m_settingDir, "cbox" );
                    useCbox = true;
                }
            }

            FILE    *fp = fopen( filename, "r" );
            if ( fp ) {
                loadSetting( fp );
                fclose( fp );
            }
            else {
                // blog ���ǉ�
                if ( cp->m_numOfBlogs < MAX_NUM_OF_BLOGS - 1 ) {
                    // �p�����[�^�m��
                    if ( getParameter() == false )
                        return;

                    // �ݒ�t�@�C���ۑ�
                    saveSetting();

                    strcpy( cp->m_blogList[cp->m_numOfBlogs].blogID,
                            (const char *)m_blogID );
                    strcpy( cp->m_blogList[cp->m_numOfBlogs].blogURL,
                            (const char *)m_blogURL );
                    strcpy( cp->m_blogList[cp->m_numOfBlogs].blogUsername,
                            (const char *)m_blogUserName );
                    strcpy( cp->m_blogList[cp->m_numOfBlogs].blogPassword,
                            (const char *)m_blogPassword );
                    strcpy( cp->m_blogList[cp->m_numOfBlogs].blogName,
                            (const char *)m_blogName );
                    strcpy( cp->m_blogList[cp->m_numOfBlogs].endpointURL,
                            (const char *)m_endpointURL );
                    cp->m_blogList[cp->m_numOfBlogs].useCbox = useCbox;

                    BLOGKIND    blogKindValue = unset;
                    for ( int i = 0; i < m_numOfBlogKinds; i++ ) {
                        if ( !strcmp( blogKindString,
                                      m_blogKindInfo[i].blogKindString ) ) {
                            blogKindValue = m_blogKindInfo[i].blogKind;
                            break;
                        }
                    }
                    cp->m_blogList[cp->m_numOfBlogs].blogKind = blogKindValue;

                    m_currentBlogID = cp->m_numOfBlogs;
                    (cp->m_numOfBlogs)++;

                    switchBlogInfo();
                    saveBlogInfo();

                    return;
                }
            }
        }

        // m_currentBlogID �̊m��
        for ( i = 0; i < cp->m_numOfBlogs; i++ ) {
            if (((m_blogID.GetLength() == 0)                 ||
                 (cp->m_blogList[i].blogID[0] == NUL)        ||
                 !m_blogID.Compare( cp->m_blogList[i].blogID ))          &&
                ((m_blogName.GetLength() == 0)               ||
                 (cp->m_blogList[i].blogName[0] == NUL)      ||
                 !m_blogName.Compare( cp->m_blogList[i].blogName ))      &&
                ((m_blogUserName.GetLength() == 0)           ||
                 (cp->m_blogList[i].blogUsername[0] == NUL)  ||
                 !m_blogUserName.Compare(cp->m_blogList[i].blogUsername))&&
                ((m_blogPassword.GetLength() == 0)           ||
                 (cp->m_blogList[i].blogPassword[0] == NUL)  ||
                 !m_blogPassword.Compare(cp->m_blogList[i].blogPassword))&&
                ((m_endpointURL.GetLength() == 0)            ||
                 (cp->m_blogList[i].endpointURL[0] == NUL)   ||
                 !m_endpointURL.Compare( cp->m_blogList[i].endpointURL ))&&
                (m_blogKind == cp->m_blogList[i].blogKind)                 ) {
                // �J�����g blog �����
                m_currentBlogID = i;
                if ( m_blogID.GetLength() == 0 )
                    m_blogID = cp->m_blogList[i].blogID;
                if ( m_blogName.GetLength() == 0 )
                    m_blogName = cp->m_blogList[i].blogName;
                if ( m_blogUserName.GetLength() == 0 )
                    m_blogUserName = cp->m_blogList[i].blogUsername;
                if ( m_blogPassword.GetLength() == 0 )
                    m_blogPassword = cp->m_blogList[i].blogPassword;
                if ( m_endpointURL.GetLength() == 0 )
                    m_endpointURL = cp->m_blogList[i].endpointURL;
                if ( m_blogURL.GetLength() == 0 )
                    m_blogURL = cp->m_blogList[i].blogURL;
                break;
            }
        }

        switchBlogInfo();
        switchBrowseBlog();
        saveBlogInfo();
    }
}

void CBlogoleeDlg::OnKillfocusEditEndpointURL() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );
    p->GetWindowText( m_endpointURL );

    bool    buttonStatus = true;
    CButton *bp = (CButton *)GetDlgItem( IDOK );
    if ( m_endpointURL.GetLength() <= 0 )
        if ( (m_blogKind == movableType) ||
             (m_blogKind == metaWeblog)  ||
             (m_blogKind == mtAPI)       ||
             (m_blogKind == atomAPI)        )
            buttonStatus = false;
    if ( buttonStatus == false )
        bp->SetWindowText( "�G���h�|�C���gURL�擾" );
    else
        bp->SetWindowText( "���e" );

    DWORD   res = p->GetStyle();
    if ( (res & ES_READONLY) != ES_READONLY ) {
        CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
        if ( m_endpointURL.Compare(
                            cp->m_blogList[m_currentBlogID].endpointURL ) ) {
            strcpy( cp->m_blogList[m_currentBlogID].endpointURL,
                    (const char *)m_endpointURL );
            saveBlogInfo();
        }
    }
}

void CBlogoleeDlg::OnButtonSwitchBlog() 
{
    CEditBlogInfoDlg    dlg;
    
    dlg.m_currentBlogID = m_currentBlogID;
    dlg.m_blogInfo      = this;

    int res = dlg.DoModal();
    if ( res == IDOK ) {
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        int blogKindIndex = -1;

        // blog �ؑ�
        m_currentBlogID = dlg.m_currentBlogID;
        m_blogKind      = dlg.m_blogKind;
        m_blogName      = dlg.m_blogName;
        m_blogUserName  = dlg.m_blogUsername;
        m_blogPassword  = dlg.m_blogPassword;
        m_blogID        = dlg.m_blogID;
        m_blogURL       = dlg.m_blogURL;

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
                CEdit *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );
                p->SetWindowText( m_endpointURL );
            }
        }
        if ( m_blogKind == hatena ) {
            if ( strstr( m_endpointURL, "{hatenaID}" ) ) {
                m_endpointURL =
                    "http://d.hatena.ne.jp/" + m_blogUserName + "/atom/blog";
                CEdit *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );
                p->SetWindowText( m_endpointURL );
            }
        }

        if ( dlg.m_endpointURL.GetLength() > 0 )
            m_endpointURL = dlg.m_endpointURL;
        else {
            int j;
            for ( j = 0; j < m_numOfBlogKinds; j++ ) {
                if ( m_blogKind == m_blogKindInfo[j].blogKind ) {
                    blogKindIndex = j;
                    break;
                }
            }
            if ( blogKindIndex >= 0 )
                m_endpointURL = m_blogKindInfo[j].endpointURL;
            else
                m_endpointURL = "";
        }

        m_categoryList.ResetContent();
        m_categoryName  = "";

        switchEndpointURL( blogKindIndex );
        if ( m_blogID.GetLength() > 0 )
            switchBlogID( m_blogID );
        else
            switchBlogID();
        switchBlogInfo();
        switchBrowseBlog();
        switchArticleKeyword();
        switchArticleExtended();
        switchArticleSummary();
        saveBlogInfo();
    }

    CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
    loadBlogInfo();
}

void CBlogoleeDlg::OnKillfocusEditBlogUsername() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_USERNAME );
    p->GetWindowText( m_blogUserName );

    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    if ( m_blogUserName.Compare(
                            cp->m_blogList[m_currentBlogID].blogUsername ) ) {
        strcpy( cp->m_blogList[m_currentBlogID].blogUsername,
                (const char *)m_blogUserName );
        saveBlogInfo();
    }
}

void CBlogoleeDlg::OnKillfocusEditBlogPassword() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_PASSWORD );
    p->GetWindowText( m_blogPassword );

    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    if ( m_blogPassword.Compare(
                            cp->m_blogList[m_currentBlogID].blogPassword ) ) {
        strcpy( cp->m_blogList[m_currentBlogID].blogPassword,
                (const char *)m_blogPassword );
        saveBlogInfo();
    }
}

void CBlogoleeDlg::OnKillfocusEditBlogID() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_ID );
    p->GetWindowText( m_blogID );

    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    if ( m_blogID.Compare( cp->m_blogList[m_currentBlogID].blogID ) ) {
        strcpy( cp->m_blogList[m_currentBlogID].blogID,
                (const char *)m_blogID );
        saveBlogInfo();
    }
}

void CBlogoleeDlg::OnButtonBrowseBlog() 
{
    char            cmd[BUFSIZ];
    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();

    cmd[0] = NUL;
    if ( cp->m_blogList[m_currentBlogID].blogURL[0] ) {
        // blog (�܂��� SNS �̓��L)������
        strcpy( cmd, cp->m_blogList[m_currentBlogID].blogURL );
        ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
    }
    else {
        // blog (�ǉ�)�����擾����
	    CAddBlogInfoDlg dlg;
        int             res;

        dlg.m_blogInfo = this;
        dlg.m_mode     = false;

        dlg.m_blogKind      = cp->m_blogList[m_currentBlogID].blogKind;
        dlg.m_blogName      = cp->m_blogList[m_currentBlogID].blogName;
        dlg.m_blogUserName  = cp->m_blogList[m_currentBlogID].blogUsername;
        dlg.m_blogPassword  = cp->m_blogList[m_currentBlogID].blogPassword;
        dlg.m_blogID        = cp->m_blogList[m_currentBlogID].blogID;
        dlg.m_blogURL       = cp->m_blogList[m_currentBlogID].blogURL;
        dlg.m_endpointURL   = cp->m_blogList[m_currentBlogID].endpointURL;
        dlg.m_useCbox       = cp->m_blogList[m_currentBlogID].useCbox;

        res = dlg.DoModal();
        if ( res == IDOK ) {
            CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

            m_blogKind      = dlg.m_blogKind;
            m_blogName      = dlg.m_blogName;
            m_blogUserName  = dlg.m_blogUserName;
            m_blogPassword  = dlg.m_blogPassword;
            m_blogID        = dlg.m_blogID;
            m_blogURL       = dlg.m_blogURL;
            m_endpointURL   = dlg.m_endpointURL;

            cp->m_blogList[m_currentBlogID].blogKind = dlg.m_blogKind;
            strcpy( cp->m_blogList[m_currentBlogID].blogName,
                    dlg.m_blogName );
            strcpy( cp->m_blogList[m_currentBlogID].blogUsername,
                    dlg.m_blogUserName );
            strcpy( cp->m_blogList[m_currentBlogID].blogPassword,
                    dlg.m_blogPassword );
            strcpy( cp->m_blogList[m_currentBlogID].blogID,
                    dlg.m_blogID );
            strcpy( cp->m_blogList[m_currentBlogID].blogURL,
                    dlg.m_blogURL );
            strcpy( cp->m_blogList[m_currentBlogID].endpointURL,
                    dlg.m_endpointURL );
            cp->m_blogList[m_currentBlogID].useCbox = dlg.m_useCbox;

            switchEndpointURL();
            if ( m_blogID.GetLength() > 0 )
                switchBlogID( m_blogID );
            else
                switchBlogID();
            switchBlogInfo();
            switchBrowseBlog();
            switchArticleKeyword();
            switchArticleExtended();
            switchArticleSummary();
            saveBlogInfo();
        }
    }
}

void CBlogoleeDlg::OnKillfocusEditRakutenId() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_RAKUTEN_ID );
    p->GetWindowText( m_rakuten_affiliateID );
}

void CBlogoleeDlg::OnUpdateEditArticle() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE );
    p->GetWindowText( m_article_description );
    switchPostArticle();
}

void CBlogoleeDlg::OnUpdateEditArticleTitle() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_TITLE );
    p->GetWindowText( m_article_title );
    switchPostArticle();
}

void CBlogoleeDlg::OnKillfocusEditArticleKeyword() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_KEYWORD );
    p->GetWindowText( m_article_keyword );
}

void CBlogoleeDlg::OnKillfocusEditArticleSummary() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_SUMMARY );
    p->GetWindowText( m_article_summary );
}

void CBlogoleeDlg::OnKillfocusEditArticleExtended() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_EXTENDED );
    p->GetWindowText( m_article_extended );
}

void CBlogoleeDlg::OnButtonFoodSearch() 
{
    if ( m_foodCode[0] && (m_foodKeyword.GetLength() > 0) ) {
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_FOOD_SEARCH );
        bp->EnableWindow( FALSE );

        char    *p = sjis2utf(m_foodKeyword);
        CString url = "http://api.hotpepper.jp/GourmetSearch/V110/?"
                      "key=guest&FoodCD=";
        url += m_foodCode;
        url += "&Keyword=";
        url += encodeURL( p ? p : (const char *)m_foodKeyword );
        url += "&Count=20";

        char    *response;
        size_t  sz = MAX_CONTENT_SIZE;

        response = (char *)malloc( sz );
        setUpReceiveBuffer( response, sz );
        http_get( url, response );
        if ( *response ) {
            int results = GetValueFromXML( "NumberOfResults", response );
            if ( results <= 0 )
                MessageBox( "�w�肵�������Ɉ�v����f�[�^�͌�����"
                            "�܂���ł���    ",
                            "�Y���f�[�^�Ȃ�",  MB_OK|MB_ICONWARNING );
            else {
                // �������ʕ\���p�� xml �𐶐�
                url = makeXmlOfSearchShopResult( response );

                // �u�ʏ�g���u���E�U�v�� xml ��\��
                ShellExecute( NULL, "open", url, NULL, NULL, SW_SHOWNORMAL );
            }
        }
        else
            MessageBox( "�T�[�o�Ƃ̒ʐM�Ɏ��s���܂���   ",
                        "�ʐM�G���[",  MB_OK|MB_ICONWARNING );
        bp->EnableWindow( TRUE );
    }
}

void CBlogoleeDlg::OnSelchangeComboFoodcd() 
{
    int location = m_foodeCodeList.GetCurSel();

    if ( location >= 0 ) {
        strcpy( m_foodCode, m_foodCodeInfo[location].foodCD );
	    m_foodeCodeList.GetLBText( location, m_foodName );
    }
}

void CBlogoleeDlg::OnKillfocusEditFoodKeyword() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_FOOD_KEYWORD );
    p->GetWindowText( m_foodKeyword );
}

void CBlogoleeDlg::OnWebHotpepper() 
{
	CString cmd;
	cmd.LoadString( IDS_WEB_HOTPEPPER );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CBlogoleeDlg::OnWebJalan() 
{
	CString cmd;
	cmd.LoadString( IDS_WEB_JALAN );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

BOOL CBlogoleeDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if ( nHitTest == HTCLIENT ) {
        // �z�b�g�y�b�p�[.jp / ������Web�T�[�r�X �� URL�����Ƀ}�E�X
        // �|�C���^��������A�w�J�[�\����\������
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );

        if ( IsInner( IDC_WEB_HOTPEPPER, wX, wY ) ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_WEB_JALAN, wX, wY ) ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}
	
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CBlogoleeDlg::OnSelchangeComboAreaList() 
{
    int location = m_areaList.GetCurSel();
    if ( location >= 0 ) {
        m_prefCode = location + 1;
        changeAreaInfo( m_prefCode );
    }
}

void CBlogoleeDlg::OnSelchangeComboAreaList2() 
{
    int location = m_areaList2.GetCurSel();
    if ( location >= 0 ) {
        bool    found = false;
        CString areaName;
        int     i;

	    m_areaList2.GetLBText( location, areaName );
        for ( i = 0; i < m_numOfAreaCodes; i++ ) {
            if ( areaName.Compare( m_areaCodeInfo[i].areaName ) == 0 ) {
                found = true;
                break;
            }
        }

        if ( found )
            strcpy( m_areaCode, m_areaCodeInfo[i].areaCode );
    }
}

void CBlogoleeDlg::OnSelchangeComboHotelType() 
{
    int location = m_hotelType.GetCurSel();
    if ( location >= 0 )
        m_hotelTypeNum = location;
}

void CBlogoleeDlg::OnButtonHotelSearch() 
{
    CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_HOTEL_SEARCH );
    p->EnableWindow( FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_JALAN_LINK );
    p->EnableWindow( FALSE );

    CString url = searchJalan();

    if ( url.GetLength() > 0 ) {
        // �u�ʏ�g���u���E�U�v�� xml ��\��
        ShellExecute( NULL, "open", url, NULL, NULL, SW_SHOWNORMAL );
    }

    p = (CButton *)GetDlgItem( IDC_BUTTON_HOTEL_SEARCH );
    p->EnableWindow( TRUE );
    switchJalanLink();
}

void CBlogoleeDlg::OnUpdateEditJalanSid() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_JALAN_SID );
    p->GetWindowText( m_sid );
    switchJalanLink();
}

void CBlogoleeDlg::OnUpdateEditJalanPid() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_JALAN_PID );
    p->GetWindowText( m_pidForJalan );
    switchJalanLink();
}

void CBlogoleeDlg::OnButtonJalanLink() 
{
    if ( m_sid.GetLength() == 0 ) {
        MessageBox( "SID ���ݒ�",
            "SID ����͂��Ă��������B�o�����[�R�}�[�X�o�R�ł̃A�t�B���G�C�g  "
            "�����N(MyLink)�𐶐�����ɂ� SID �̐ݒ肪�K�v�ł��B",
            MB_OK|MB_ICONWARNING );
        return;
    }
    if ( m_pidForJalan.GetLength() == 0 ) {
        MessageBox( "PID ���ݒ�",
            "PID ����͂��Ă��������B�o�����[�R�}�[�X�o�R�ł̃A�t�B���G�C�g  "
            "�����N(MyLink)�𐶐�����ɂ� PID �̐ݒ肪�K�v�ł��B",
            MB_OK|MB_ICONWARNING );
        return;
    }
    if ( ((m_prefCode > 0) || m_areaCode[0]) && (m_hotelTypeNum >= 0) ) {
        if ( m_hotelTypeNum != 5 ) {
            CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
            CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_HOTEL_SEARCH );
            p->EnableWindow( FALSE );

            p = (CButton *)GetDlgItem( IDC_BUTTON_JALAN_LINK );
            p->EnableWindow( FALSE );

            CString url = searchJalan();
            makeAffiliateLink( url );

            p->EnableWindow( TRUE );
            p = (CButton *)GetDlgItem( IDC_BUTTON_HOTEL_SEARCH );
            p->EnableWindow( TRUE );
        }
        else
            MessageBox(
                "����T�[�`�̃A�t�B���G�C�g�����N�����ɂ͖��Ή��ł�   ",
                "�����N�̐����͂ł��܂���",  MB_OK|MB_ICONWARNING );
    }	
}

void CBlogoleeDlg::OnButtonSmall() 
{
    // �ݒ�t�@�C���ۑ�
    if ( checkProxyInfo() ) {
        // proxy�֘A�̐ݒ�Ɍ�肪����Ǝv����ꍇ�A����ʐM���s�^�C�~���O��
        // �ɍĐݒ�\�Ƃ��邽�߁A���܂̐ݒ����������j������
        CBlogoleeApp    *bp = (CBlogoleeApp *)AfxGetApp();
        bp->m_proxyType = CBlogoleeApp::autoDetect;
    }
    saveSetting( TRUE );

    this->ShowWindow( SW_HIDE );

    CBlogoleeMini   dlg;
    dlg.m_dlg = this;

    int r;
    do {
        r = dlg.DoModal();
        if ( r == IDCANCEL )
            OnExit();
        else if ( r == IDOK )
            OnExecutePostArticle();
        else {
            CEdit   *p;

            if ( dlg.m_articleTitle.GetLength() > 0 ) {
                p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_TITLE );
                p->SetWindowText( m_article_title );
            }

            if ( dlg.m_articleSummary.GetLength() > 0 ) {
                p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_SUMMARY );
                p->SetWindowText( m_article_summary );
            }

            if ( dlg.m_articleDescription.GetLength() > 0 ) {
                p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE );
                p->SetWindowText( m_article_description );
            }

            this->ShowWindow( SW_SHOW ); // IDC_BUTTON_LARGE
        }
    } while ( r == IDOK );
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CBlogoleeDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    DWORD       dwPos = GetMessagePos();
    WORD        wX    = LOWORD( dwPos );
    WORD        wY    = HIWORD( dwPos );

    if ( IsInner( IDC_STATIC_RECOMENDED, wX, wY ) && m_similarity ) {
        CPoint  cMenuPt;
        GetCursorPos( &cMenuPt );

#define IDC_MENU_SWITCH_ONE 1
        CMenu   menu;
        CString text;
        int     i;
        char    temp[16];

        menu.CreatePopupMenu();
        for ( i = IDC_MENU_SWITCH_ONE; i < IDC_MENU_SWITCH_ONE + 10; i++ ) {

            if ( m_numOfRecomended == (i - IDC_MENU_SWITCH_ONE) + 1 )
                sprintf( temp, "%2d�� *", (i - IDC_MENU_SWITCH_ONE) + 1 );
            else
                sprintf( temp, "%2d��", (i - IDC_MENU_SWITCH_ONE) + 1 );
            menu.AppendMenu( MF_STRING, i, temp );
        }

        if ( i >= IDC_MENU_SWITCH_ONE + 10 ) {
            int iCommand =
                menu.TrackPopupMenu(
                    TPM_LEFTALIGN | TPM_BOTTOMALIGN |
                    TPM_RETURNCMD | TPM_LEFTBUTTON,
                    cMenuPt.x, cMenuPt.y, this, NULL );

            if ( (iCommand >= IDC_MENU_SWITCH_ONE)     &&
                 (iCommand <= IDC_MENU_SWITCH_ONE + 9)    )
                m_numOfRecomended = (iCommand - IDC_MENU_SWITCH_ONE) + 1;
        }

        menu.DestroyMenu();	
    }
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void CBlogoleeDlg::OnButtonProxy() 
{
    CBlogoleeApp    *bp = (CBlogoleeApp *)AfxGetApp();
    int             useProxy = bp->m_useProxy;
    char            proxyServer[MAX_SERVERNAME];
    unsigned short  proxyPort;
    char            proxyUserName[MAX_NAMELEN + 1];
    char            proxyPassword[MAX_NAMELEN + 1];

    proxyServer[0]   = NUL;
    proxyPort        = 0;
    proxyUserName[0] = NUL;
    proxyPassword[0] = NUL;
    initProxyInfo();
    if ( bp->m_proxyServer.GetLength() == 0 ) {
        useProxy = FALSE;
        getProxyInfo( &useProxy, proxyServer, &proxyPort,
                      proxyUserName, proxyPassword );
    }
    else {
        strcpy( proxyServer, bp->m_proxyServer );
        proxyPort = (unsigned short)(bp->m_proxyPort);
        strcpy( proxyUserName, bp->m_proxyUsername );
        strcpy( proxyPassword, bp->m_proxyPassword );
    }
    confirmProxyInfo( &useProxy, proxyServer, &proxyPort,
                      proxyUserName, proxyPassword );

    if ( useProxy == FALSE ) {
        bp->m_proxyType = CBlogoleeApp::notUsed;
        bp->m_useProxy  = false;
    }
    else if ( bp->m_proxyType == CBlogoleeApp::manualSetting ) {
        bp->m_proxyType = CBlogoleeApp::specialSetting;
        if ( bp->m_useProxy ) {
            setProxyInfo( bp->m_proxyServer,
                          (unsigned short)(bp->m_proxyPort),
                          bp->m_proxyUsername,
                          bp->m_proxyPassword );
        }
    }
    setUseProxy( bp->m_useProxy );
    setConfirmProxyInfoFunc( NULL );
    syncProxyInfo();
    saveSetting();
}
