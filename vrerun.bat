@echo off
if not exist vuld_dir\vuldmod.exe goto error
if not exist vuld_dir\vuldmod.wad goto error

:rerun
vuld_dir\vuldmod.exe -file vuld_dir\vuldmod.wad
goto exit

:error
echo.
echo ERROR: Did not found VULD files.
echo Please run VULD via VRUN first before
echo using the VRERUN command.
echo.
goto exit


:exit
