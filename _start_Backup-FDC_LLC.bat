rem 	Note: @ character : User settings

rem 	 - Cautions -
rem 	1. The path or folder name must not have space
rem 	2. Batch file must be located in the project folder
rem 	3. Make sure that the files in the project folder that you want to back up are not open.

rem 	=========================< User settings >=========================

rem 	@ Project folder name
set PROJECT_FOLDER_NAME=YHTEC_LLC_100kW

rem 	@ Project folder path
cd D:\07_Working

rem 	@ Back-up path
set BACKUP_PATH=D:\07_Working\Backup\FDC_LLC_100kW\

rem 	@ Password( yhtech!! ) Please don't change password
set PASSWORD=yhtech!!

rem 	@ If the installation path of WinZip is different, change it (In case of Winzip, use after installation of wzcline32.exe program)
set WINZIP_INSTALL_PATH=C:\Program Files\WinZip

rem 	@ If the installation path of ALZip is different, change it
set ALZIP_INSTALL_PATH=C:\Program Files\ESTsoft\ALZip

rem 	@ If the installation path of Bandizip is different, change it
set BANDIZIP_INSTALL_PATH=C:\Program Files\Bandizip

rem 	The color attribute is specified in two hexadecimal digits. The first digit is the background color, the second digit is the text color
rem 	0:Black
rem 	1:Blue
rem 	2:Green
rem 	3:Turquoise
rem 	4:Red
rem 	5:Purple
rem 	6:Yellow
rem 	7:White
rem 	8:Gray
rem 	9:Light blue
rem 	A:Light green
rem 	B:Light turquoise
rem 	C:Light red
rem 	D:Light purple
rem 	E:Light Yello
rem 	F:Light white

rem 	@ Background clor / text color
color 0B

rem 	=============================================================

@echo off
cls 

title Young Hwa Tech Source Automatic Safe Backup Tool

:MENU
cls 

echo.
echo  =============================================
echo. * Young Hwa Tech Source Automatic Safe Backup
echo  =============================================
echo.
echo  * Project : %PROJECT_FOLDER_NAME%
echo  ---------------------------------------------
echo.

set /p YN=Continue(y/n)?
echo.

if "%YN%" == "Y" goto NEXT
if "%YN%" == "y" goto NEXT
if "%YN%" == "N" goto EXIT
if "%YN%" == "n" goto EXIT

goto MENU

:NEXT

set BACKUP_DATE=%date%

set BACKUP_HOUR=%time:~0,2%
if "%BACKUP_HOUR%"==" 0" set BACKUP_HOUR=00
if "%BACKUP_HOUR%"==" 1" set BACKUP_HOUR=01
if "%BACKUP_HOUR%"==" 2" set BACKUP_HOUR=02
if "%BACKUP_HOUR%"==" 3" set BACKUP_HOUR=03
if "%BACKUP_HOUR%"==" 4" set BACKUP_HOUR=04
if "%BACKUP_HOUR%"==" 5" set BACKUP_HOUR=05
if "%BACKUP_HOUR%"==" 6" set BACKUP_HOUR=06
if "%BACKUP_HOUR%"==" 7" set BACKUP_HOUR=07
if "%BACKUP_HOUR%"==" 8" set BACKUP_HOUR=08
if "%BACKUP_HOUR%"==" 9" set BACKUP_HOUR=09

set BACKUP_TIME=(%BACKUP_HOUR%-%time:~3,2%-%time:~6,2%)

if exist "%WINZIP_INSTALL_PATH%" goto WINZIP
if exist "%ALZIP_INSTALL_PATH%" goto ALZIP
if exist "%BANDIZIP_INSTALL_PATH%" goto BANDIZIP

goto EXIT

:WINZIP
path %PATH%;%WINZIP_INSTALL_PATH%
WZZIP.EXE -P -r -whs -s%PASSWORD% %BACKUP_PATH%%PROJECT_FOLDER_NAME%_%BACKUP_DATE%%BACKUP_TIME% %PROJECT_FOLDER_NAME%
if ErrorLevel 1 Goto ErrMsg
goto CONTINUE

:ALZIP
path %PATH%;%ALZIP_INSTALL_PATH%
alzipcon -a -p%PASSWORD% %PROJECT_FOLDER_NAME% %BACKUP_PATH%%PROJECT_FOLDER_NAME%_%BACKUP_DATE%%BACKUP_TIME%.ZIP 
goto CONTINUE

:BANDIZIP
path %PATH%;%BANDIZIP_INSTALL_PATH%
bc.exe c -p:%PASSWORD% %BACKUP_PATH%%PROJECT_FOLDER_NAME%_%BACKUP_DATE%%BACKUP_TIME%.ZIP %PROJECT_FOLDER_NAME%  
goto CONTINUE

:CONTINUE
echo.
echo * Source code has been safely backed up.!
echo -----------------------------------------
echo.

pause
goto EXIT

:ErrMsg
echo.
echo ***** Serious Error Detected *****
echo.

pause

:EXIT
exit