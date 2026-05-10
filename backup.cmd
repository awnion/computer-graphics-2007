@echo off
set /p comment=Enter comments(1-2word):
if "%comment%"=="" goto empty
set comment=_%comment: =_%
:empty
set prj=MG_OGL
set d=%date:.=_%
set d=%d: =_%
set YYYY=%d:~6,4%
set MM=%d:~3,2%
set DD=%d:~0,2%
set t=%time::=-%
set t=%t: =0%
:JAgain
set fnm=..\z-backups\%prj%_%YYYY%_%MM%_%DD%_%t:~0,8%%comment%.rar
if not exist %fnm% goto JOk
	echo !ERROR!File "%fnm%" already exists.
	set /p comment=Enter another comments(1-2word):
    goto JAgain
:JOk

rar.exe a -m5 -s -r %fnm% * -x*.zip -x*.rar -x.svn -x*.log -xtmp -xtest

echo.
echo.
echo.
echo ===================================================================
echo  %fnm% archive has been created
echo ===================================================================
echo.
echo.
echo.
pause
