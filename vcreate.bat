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
echo.

if not exist doomhack.exe goto nodhe

echo WARNING!!
echo DoomHack.exe will be deleted.
choice Is this OK?
if errorlevel 2 goto safeexit
echo.
del doomhack.exe

:nodhe

if not exist dehacked.ini goto nodh
echo WARNING!!
echo DEHACKED.INI will be deleted.
choice Is this OK?
if errorlevel 2 goto safeexit
echo.
del dehacked.ini

:nodh
vuld -create
if not errorlevel 0 goto :error
echo.
goto exit

:error
echo ERROR occurred -- please check the program output above.
goto exit

:safeexit
echo Aborting program without creating any new files.
goto exit

:exit

