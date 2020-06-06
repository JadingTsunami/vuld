@echo off
del vuld_dir\*.*
if exist doomhack.exe
    echo WARNING!!
    echo DoomHack.exe will be deleted.
    echo Press Ctrl-C to quit or
    pause
del doomhack.exe
vuld
vuld_dir\vuld.exe -file vuld_dir\vuld.wad
