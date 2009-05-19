# Microsoft Developer Studio Project File - Name="blogolee" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=blogolee - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "blogolee.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "blogolee.mak" CFG="blogolee - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "blogolee - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "blogolee - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/comm/blogolee", ZEBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "blogolee - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\xmlRPC" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 xmlRPC.lib /nologo /version:1.21 /subsystem:windows /machine:I386 /libpath:"..\xmlRPC\Release"

!ELSEIF  "$(CFG)" == "blogolee - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /I "..\xmlRPC" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xmlRPC.lib /nologo /version:1.21 /subsystem:windows /incremental:no /debug /machine:I386 /pdbtype:sept /libpath:"..\xmlRPC\Debug"

!ENDIF 

# Begin Target

# Name "blogolee - Win32 Release"
# Name "blogolee - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddBlogInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BlogIDSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\blogolee.cpp
# End Source File
# Begin Source File

SOURCE=.\blogolee.rc
# End Source File
# Begin Source File

SOURCE=.\blogoleeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BlogoleeMini.cpp
# End Source File
# Begin Source File

SOURCE=.\blogs\colors.c
# End Source File
# Begin Source File

SOURCE=.\confirmProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\blogs\echoo.c
# End Source File
# Begin Source File

SOURCE=.\EditBlogInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EndPointDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\blogs\excite.c
# End Source File
# Begin Source File

SOURCE=.\blogs\fc2network.c
# End Source File
# Begin Source File

SOURCE=.\HotelDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\blogs\kinugasa.c
# End Source File
# Begin Source File

SOURCE=.\blogs\livedoor.c
# End Source File
# Begin Source File

SOURCE=.\blogs\mixi.c
# End Source File
# Begin Source File

SOURCE=.\blogs\openPNE.c
# End Source File
# Begin Source File

SOURCE=.\postArticle.c
# End Source File
# Begin Source File

SOURCE=.\ProceedingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ProxyInfoDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\blogs\rakuten.c
# End Source File
# Begin Source File

SOURCE=.\strncmpi.c
# End Source File
# Begin Source File

SOURCE=.\utility.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddBlogInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\BlogIDSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\blogolee.h
# End Source File
# Begin Source File

SOURCE=.\blogoleeDlg.h
# End Source File
# Begin Source File

SOURCE=.\BlogoleeMini.h
# End Source File
# Begin Source File

SOURCE=.\confirmProxy.h
# End Source File
# Begin Source File

SOURCE=.\EditBlogInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\EndPointDlg.h
# End Source File
# Begin Source File

SOURCE=.\HotelDialog.h
# End Source File
# Begin Source File

SOURCE=.\hotelInfo.h
# End Source File
# Begin Source File

SOURCE=.\postArticle.h
# End Source File
# Begin Source File

SOURCE=.\ProceedingDialog.h
# End Source File
# Begin Source File

SOURCE=.\ProxyInfoDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\utility.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\blogolee.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\res\blogolee.ico
# End Source File
# Begin Source File

SOURCE=.\res\blogolee.rc2
# End Source File
# Begin Source File

SOURCE=.\res\hand2.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\dist.bat
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
