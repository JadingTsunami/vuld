@echo off
if exist vuld_dir\vuldmod.exe del vuld_dir\vuldmod.exe
if exist vuld_dir\vuldmod.wad del vuld_dir\vuldmod.wad
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

if exist vuld_dir\vuldmod.exe goto checkwad
if exist doom.exe copy doom.exe vuld_dir\vuldmod.exe
if exist vuld_dir\vuldmod.exe goto checkwad
if exist doom2.exe copy doom2.exe vuld_dir\vuldmod.exe

:checkwad
if exist vuld_dir\vuldmod.wad goto runvuld
if exist doom.wad copy doom.wad vuld_dir\vuldmod.wad
if exist vuld_dir\vuldmod.wad goto runvuld
if exist doom2.wad copy doom2.wad vuld_dir\vuldmod.wad

:runvuld
vuld_dir\vuldmod.exe -file vuld_dir\vuldmod.wad
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
