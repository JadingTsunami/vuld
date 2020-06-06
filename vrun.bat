@echo off
if exist vuld_dir\vuld.exe del vuld_dir\vuld.exe
if exist vuld_dir\vuld.wad del vuld_dir\vuld.wad
if not exist doomhack.exe goto nodh

echo WARNING!!
echo DoomHack.exe will be deleted.
choice Is this OK?
if errorlevel 2 goto safeexit
echo.
del doomhack.exe

:nodh
vuld
if not errorlevel 0 goto :error
if exist vuld_dir\vuld.exe goto runvuld
if exist doom.exe copy doom.exe vuld_dir\vuld.exe
if exist vuld_dir\vuld.exe goto runvuld
if exist doom2.exe copy doom2.exe vuld_dir\vuld.exe

:runvuld
vuld_dir\vuld.exe -file vuld_dir\vuld.wad
goto exit

:safeexit
echo.
echo Aborting program without changing anything.
goto exit

:error
echo.
echo Error occurred running VULD; exiting.
goto exit

:exit
