echo off

REM batch file for distribution of BloGolEe
REM $Header: /comm/blogolee/dist.bat 1     09/05/14 3:47 tsupo $

chmod -R +w dist

rm -Rf dist\src

mkdir dist\src
mkdir dist\src\blogolee
mkdir dist\src\blogolee\blogs
mkdir dist\src\blogolee\res
mkdir dist\src\include
mkdir dist\src\lib

copy *.c           dist\src\blogolee
copy *.h           dist\src\blogolee
copy *.cpp         dist\src\blogolee
copy blogolee.rc   dist\src\blogolee
copy blogs\*.c     dist\src\blogolee\blogs
copy res\*.ico     dist\src\blogolee\res
copy res\*.rc2     dist\src\blogolee\res
REM copy res\*.bmp dist\src\blogolee\res
copy res\*.cur     dist\src\blogolee\res
copy readme.txt            dist
copy blogolee.exe.manifest dist
copy Release\blogolee.exe  dist
copy Release\xmlRPC.dll    dist

copy ..\xmlRPC\amazon.h     dist\src\include
copy ..\xmlRPC\atomApi.h    dist\src\include
copy ..\xmlRPC\encryptRSA.h dist\src\include
copy ..\xmlRPC\multipart.h  dist\src\include
copy ..\xmlRPC\rakuten.h    dist\src\include
copy ..\xmlRPC\xmlRPC.h     dist\src\include

copy ..\xmlRPC\Release\xmlRPC.lib dist\src\lib
