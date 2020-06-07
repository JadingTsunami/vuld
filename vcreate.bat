@echo off
echo VULD Create Mode
echo.
echo VULD will create the selected game files, place them
echo in your VULD_DIR subfolder and then exit without
echo running the game.
echo.
echo VULD will NOT manage these files for you;
echo you will need to move or delete them yourself.
echo.
choice Is this OK?
if errorlevel 2 goto safeexit

if not exist doomhack.exe goto nodhe

echo.
echo WARNING!!
echo DoomHack.exe will be deleted.
choice Is this OK?
if errorlevel 2 goto safeexit
echo.
del doomhack.exe

:nodhe

if not exist dehacked.ini goto nodh
echo.
echo WARNING!!
echo DEHACKED.INI will be deleted.
choice Is this OK?
if errorlevel 2 goto safeexit
echo.
del dehacked.ini

:nodh
if exist doom.exe copy doom.exe doomhack.exe
if exist doom2.exe copy doom2.exe doomhack.exe
vuld -create
if errorlevel 1 goto error
goto exit

:error
echo.
echo ERROR occurred -- please check the program output above.
goto exit

:safeexit
echo Aborting program without creating any new files.
goto exit

:exit

