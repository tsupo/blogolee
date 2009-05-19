/*
 * confirmProxy.cpp : �u���O�N���C�A���g BloGolEe
 *      proxy���ݒ�m�F����
 *
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/confirmProxy.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 8     07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 7     07/03/14 20:33 Tsujimura543
 * checkProxyInfo() ������
 * 
 * 6     07/03/14 20:09 Tsujimura543
 * proxy.txt �ɏ����o���|�[�g�ԍ��̒l�����������s����C��
 * 
 * 5     07/03/13 19:56 Tsujimura543
 * proxy�ݒ���� BlogoleeApp ���ɕێ�����悤�ɂ���
 * 
 * 4     07/03/10 5:22 Tsujimura543
 * ���[�U���ƃp�X���[�h�̎w�肪�K�v��proxy�T�[�o�ɂ��b��I�ɑΉ����Ă݂�
 * 
 * 3     07/03/09 21:23 Tsujimura543
 * FILE_CONFIG_PROXY ��ǉ�
 * 
 * 2     07/03/09 21:21 Tsujimura543
 * checkProxyInfo() ��ǉ�
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "blogolee.h"
#include "ProxyInfoDialog.h"
#include "confirmProxy.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/confirmProxy.cpp 1     09/05/14 3:47 tsupo $";
#endif

#define FILE_CONFIG_PROXY   "./proxy.txt"   // proxy�T�[�o���ݒ�t�@�C��

int confirmProxyInfo( int            *useProxy,
                      char           *proxyServer,
                      unsigned short *proxyPort,
                      char           *proxyUserName,
                      char           *proxyPassword )
{
    int             ret = FALSE;
    CBlogoleeApp    *bp = (CBlogoleeApp *)AfxGetApp();

    int r = MessageBox( NULL,
                        "proxy�T�[�o�o�R�ŃC���^�[�l�b�g�𗘗p���Ă��܂���?",
                        "�C���^�[�l�b�g���p�`�Ԋm�F",
                        MB_YESNO|MB_ICONQUESTION );
    if ( r == IDYES ) {
        CProxyInfoDialog    dlg;
        dlg.DoModal();

        *useProxy = TRUE;
        strcpy( proxyServer, dlg.m_proxyServerName );
        *proxyPort = (unsigned short)(dlg.m_proxyPortNumber);

        bp->m_proxyServer = proxyServer;
        bp->m_proxyPort   = *proxyPort;

        if ( dlg.m_proxyUserName.GetLength() > 0 ) {
            bp->m_proxyUsername = dlg.m_proxyUserName;
            if ( dlg.m_proxyPassword.GetLength() > 0 )
                bp->m_proxyPassword = dlg.m_proxyPassword;
        }

        FILE    *fp;
        if ( ( fp = fopen( FILE_CONFIG_PROXY, "w" ) ) != NULL ) {
            fprintf( fp, "%s\n", proxyServer );
            fprintf( fp, "%d\n", *proxyPort );

            if ( dlg.m_proxyUserName.GetLength() > 0 ) {
                if ( proxyUserName )
                    strcpy( proxyUserName, dlg.m_proxyUserName );
                fprintf( fp, "%s\n", (const char *)dlg.m_proxyUserName );

                if ( dlg.m_proxyPassword.GetLength() > 0 ) {
                    if ( proxyPassword )
                        strcpy( proxyPassword, dlg.m_proxyPassword );
                    fprintf( fp, "%s\n", (const char *)dlg.m_proxyPassword );
                }
            }
            fclose( fp );
        }

        ret = TRUE;
    }
    else {
        *useProxy = FALSE;
        ret = TRUE;
    }

    bp->m_proxyType = CBlogoleeApp::manualSetting;
    bp->m_useProxy  = *useProxy == TRUE ? true : false;

    return ( ret );
}

bool
checkProxyInfo()
{
    bool    ret = isNecessaryToCheckProxyInfo() ? true : false;

    if ( ret )
        initProxyInfo();

    return ( ret );
}

void
initProxyInfo()
{
    unlink( FILE_CONFIG_PROXY );
}
