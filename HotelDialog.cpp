/*
 * HotelDialog.cpp : ブログクライアント BloGolEe
 *      ホテル情報表示ダイアログ
 *
 *          written by H.Tsujimura  7 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/HotelDialog.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/03/13 23:43 Tsujimura543
 * コメント追加
 * 
 * 2     07/03/08 23:06 Tsujimura543
 * (1) 閲覧中のホテル情報が全何件中の何件目か表示するようにした
 * (2) 画像へのリンクが存在しない場合は MyLink の画像リンクは生成しない
 *     ようにした
 * 
 * 1     07/03/07 22:39 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "blogolee.h"
#include "HotelDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/HotelDialog.cpp 1     09/05/14 3:47 tsupo $";
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
// CHotelDialog ダイアログ

CHotelDialog::CHotelDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CHotelDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHotelDialog)
	m_hotelInfoString = _T("");
	m_hotelName = _T("");
	m_hotelURL = _T("");
	m_catchCopy = _T("");
	m_description = _T("");
	m_hotelAddress = _T("");
	m_checkIn = _T("");
	m_checkOut = _T("");
	m_imageURL = _T("");
	m_imageDescription = _T("");
	m_textLink = _T("");
	m_imageLink = _T("");
	m_sid = _T("");
	m_pid = _T("");
	m_affiliateURL = _T("");
	//}}AFX_DATA_INIT

    m_numOfHotelInfo   = 0;
    m_currentHotelInfo = 0;
    m_hotelInfo        = NULL;
    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
}

void CHotelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHotelDialog)
	DDX_Text(pDX, IDC_STATIC_HOTEL1, m_hotelInfoString);
	DDV_MaxChars(pDX, m_hotelInfoString, 32);
	DDX_Text(pDX, IDC_EDIT_HOTEL_NAME, m_hotelName);
	DDV_MaxChars(pDX, m_hotelName, 256);
	DDX_Text(pDX, IDC_EDIT_HOTEL_URL, m_hotelURL);
	DDV_MaxChars(pDX, m_hotelURL, 512);
	DDX_Text(pDX, IDC_EDIT_CATCH_COPY, m_catchCopy);
	DDV_MaxChars(pDX, m_catchCopy, 256);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_description);
	DDV_MaxChars(pDX, m_description, 4096);
	DDX_Text(pDX, IDC_EDIT_HOTEL_ADDERESS, m_hotelAddress);
	DDV_MaxChars(pDX, m_hotelAddress, 256);
	DDX_Text(pDX, IDC_EDIT_CHEKIN_TIME, m_checkIn);
	DDV_MaxChars(pDX, m_checkIn, 64);
	DDX_Text(pDX, IDC_EDIT_CHECKOUT_TIME, m_checkOut);
	DDV_MaxChars(pDX, m_checkOut, 64);
	DDX_Text(pDX, IDC_EDIT_IMAGE_URL, m_imageURL);
	DDV_MaxChars(pDX, m_imageURL, 512);
	DDX_Text(pDX, IDC_EDIT_IMAGE_DESCRIPTION, m_imageDescription);
	DDV_MaxChars(pDX, m_imageDescription, 2048);
	DDX_Text(pDX, IDC_EDIT_TEXT_LINK, m_textLink);
	DDV_MaxChars(pDX, m_textLink, 8192);
	DDX_Text(pDX, IDC_EDIT1_IMAGE_LINK, m_imageLink);
	DDV_MaxChars(pDX, m_imageLink, 8192);
	DDX_Text(pDX, IDC_EDIT_SID, m_sid);
	DDV_MaxChars(pDX, m_sid, 32);
	DDX_Text(pDX, IDC_EDIT_PID, m_pid);
	DDV_MaxChars(pDX, m_pid, 32);
	DDX_Text(pDX, IDC_AFFILIATE_URL, m_affiliateURL);
	DDV_MaxChars(pDX, m_affiliateURL, 1024);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHotelDialog, CDialog)
	//{{AFX_MSG_MAP(CHotelDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACKWARD, OnButtonBackward)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, OnButtonForward)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_AFFILIATE_URL, OnAffiliateURL)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotelDialog 追加メソッド

void CHotelDialog::showHotelInfo()
{
    CButton *bp;
    CStatic *sp;
    CEdit   *ep;
    char    tmp[BUFSIZ];
    int     index = m_currentHotelInfo - 1;
    CString affiliateURLforXHTML;
    CString affiliateURLhead = "http://ck.jp.ap.valuecommerce.com/servlet/referral?sid=";

    affiliateURLhead += m_sid;
    affiliateURLhead += "&pid=";
    affiliateURLhead += m_pid;
    affiliateURLhead += "&vc_url=";

    if ( m_currentHotelInfo == 1 ) {
        bp = (CButton *)GetDlgItem( IDC_BUTTON_BACKWARD );
        bp->EnableWindow( FALSE );
    }
    else {
        bp = (CButton *)GetDlgItem( IDC_BUTTON_BACKWARD );
        bp->EnableWindow( TRUE );
    }

    if ( m_currentHotelInfo == m_numOfHotelInfo ) {
        bp = (CButton *)GetDlgItem( IDC_BUTTON_FORWARD );
        bp->EnableWindow( FALSE );
    }
    else {
        bp = (CButton *)GetDlgItem( IDC_BUTTON_FORWARD );
        bp->EnableWindow( TRUE );
    }

    sp = (CStatic *)GetDlgItem( IDC_STATIC_HOTEL1 );
    sprintf( tmp, "ホテル情報 #%d (全%d件)",
             m_currentHotelInfo, m_numOfHotelInfo );
    m_hotelInfoString = tmp;
    sp->SetWindowText( m_hotelInfoString );

    ep = (CEdit *)GetDlgItem( IDC_EDIT_HOTEL_NAME );
    m_hotelName = m_hotelInfo[index].m_hotelName;
    ep->SetWindowText( m_hotelName );

    ep = (CEdit *)GetDlgItem( IDC_EDIT_HOTEL_URL );
    m_hotelURL = m_hotelInfo[index].m_hotelDetailURL;
    ep->SetWindowText( m_hotelURL );

    ep = (CEdit *)GetDlgItem( IDC_EDIT_CATCH_COPY );
    m_catchCopy = m_hotelInfo[index].m_hotelCatchCopy;
    ep->SetWindowText( m_catchCopy );

	ep = (CEdit *)GetDlgItem( IDC_EDIT_DESCRIPTION );
    m_description = m_hotelInfo[index].m_hotelCaption;
    ep->SetWindowText( m_description );

	ep = (CEdit *)GetDlgItem( IDC_EDIT_HOTEL_ADDERESS );
    m_hotelAddress = m_hotelInfo[index].m_hotelAddress;
    ep->SetWindowText( m_hotelAddress );

	ep = (CEdit *)GetDlgItem( IDC_EDIT_CHEKIN_TIME );
    m_checkIn = m_hotelInfo[index].m_checkInTime;
    ep->SetWindowText( m_checkIn );

	ep = (CEdit *)GetDlgItem( IDC_EDIT_CHECKOUT_TIME );
    m_checkOut = m_hotelInfo[index].m_checkOutTime;
    ep->SetWindowText( m_checkOut );

	ep = (CEdit *)GetDlgItem( IDC_EDIT_IMAGE_URL );
    m_imageURL = m_hotelInfo[index].m_pictureURL;
    ep->SetWindowText( m_imageURL );

	ep = (CEdit *)GetDlgItem( IDC_EDIT_IMAGE_DESCRIPTION );
    m_imageDescription = m_hotelInfo[index].m_pictureCaption;
    ep->SetWindowText( m_imageDescription );

    m_affiliateURL = makeAffilateURL( affiliateURLhead,
                                      m_hotelInfo[index].m_hotelDetailURL );
    affiliateURLforXHTML = makeAffilateURLforXHTML( m_affiliateURL );

	ep = (CEdit *)GetDlgItem( IDC_EDIT_TEXT_LINK );
    m_textLink = "<a href=\"" + affiliateURLforXHTML + "\">" +
                    m_hotelInfo[index].m_hotelName +
                 "</a>";
    ep->SetWindowText( m_textLink );

    if ( m_hotelInfo[index].m_pictureURL.GetLength() > 0 ) {
        m_imageLink = "<a href=\"" + affiliateURLforXHTML + "\"><img src=\"" +
                        m_hotelInfo[index].m_pictureURL +
                      "\" alt=\"" +
                        m_hotelInfo[index].m_pictureCaption +
                      "\" border=\"0\" /></a>";
    }
    else
        m_imageLink = _T("");
	ep = (CEdit *)GetDlgItem( IDC_EDIT1_IMAGE_LINK );
    ep->SetWindowText( m_imageLink );

    sp = (CStatic *)GetDlgItem( IDC_AFFILIATE_URL );
    sp->SetWindowText( wordrap(m_affiliateURL) );
}

CString CHotelDialog::makeAffilateURL( CString trailerURL, CString targetURL )
{
    char        s[MAX_URLLENGTH], *p, *q;
    static char c[]   = ":/?&=";
    static char hex[] = "0123456789abcdef";
    bool        found = false;
    
    strcpy( s, targetURL );
    p = s;
    while ( *p ) {
        found = false;
        for ( char *r = c; *r; r++ ) {
            if ( *p == *r ) {
                q = p + strlen(p);
                while ( q > p ) {
                    *(q + 2) = *q;
                    q--;
                }

                *p++ = '%';
                *p++ = hex[(*r) / 16];
                *p++ = hex[(*r) % 16];

                found = true;
            }
        }
        if ( !found )
            p++;
    }

    CString url = trailerURL + s;
    return ( url );
}

CString CHotelDialog::makeAffilateURLforXHTML( CString affiliateURL )
{
    char    s[MAX_URLLENGTH], *p, *q;

    strcpy( s, affiliateURL );
    p = s;
    while ( *p ) {
        if ( (*p == '&') && (strncmp( p + 1, "amp;", 4 ) != 0) ) {
            q = p + strlen(p);
            while ( q > p ) {
                *(q + 4) = *q;
                q--;
            }

            *++p = 'a';
            *++p = 'm';
            *++p = 'p';
            *++p = ';';
        }

        p++;
    }

    CString url = s;
    return ( url );
}

CString CHotelDialog::wordrap( CString url )
{
    char    s[MAX_URLLENGTH], *p, *q;

    strcpy( s, url );
    p = strstr( s, "vc_url=" );
    if ( p ) {
        q = p + strlen(p);
        while ( q >= p ) {
            *(q + 2) = *q;
            q--;
        }

        *p++ = '\r';
        *p++ = '\n';
    }

    CString result = s;
    return ( result );
}

/////////////////////////////////////////////////////////////////////////////
// CHotelDialog メッセージ ハンドラ

void CHotelDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        if ( m_hotelInfo && (m_numOfHotelInfo > 0) ) {
            CEdit   *ep;

            ep = (CEdit *)GetDlgItem( IDC_EDIT_SID );
            ep->SetWindowText( m_sid );

            ep = (CEdit *)GetDlgItem( IDC_EDIT_PID );
            ep->SetWindowText( m_pid );

            m_currentHotelInfo = 1;
            showHotelInfo();
        }
    }

    LOGFONT tLogFont;
    CFont   *cWndFont;

    cWndFont = GetFont(); 
    cWndFont->GetLogFont( &tLogFont );
    tLogFont.lfUnderline = 1;
    m_cFont.CreateFontIndirect( &tLogFont );

    CStatic *s = (CStatic *)GetDlgItem( IDC_AFFILIATE_URL );
    s->SetFont( &m_cFont, TRUE );
}

void CHotelDialog::OnButtonBackward() 
{
    if ( m_currentHotelInfo > 1 ) {
        m_currentHotelInfo--;
        showHotelInfo();
    }
}

void CHotelDialog::OnButtonForward() 
{
    if ( m_currentHotelInfo < m_numOfHotelInfo ) {
        m_currentHotelInfo++;
        showHotelInfo();
    }
}


void CHotelDialog::OnAffiliateURL() 
{
    if ( m_affiliateURL.GetLength() > 0 ) {
    	CString cmd = m_affiliateURL;
        ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
    }
}

BOOL CHotelDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if ( nHitTest == HTCLIENT ) {
        // アフィリエイトリンク(MyLink) の URL部分にマウスポインタが
        // 来たら、指カーソルを表示する
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );
		CPoint  poCursor( wX, wY );
		CRect   rcClient;

        CStatic *s = (CStatic *)GetDlgItem( IDC_AFFILIATE_URL );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}
	
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
