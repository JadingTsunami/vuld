# VULD: A Launcher for Vanilla Mods

## Compilation

Compiled with [DJGPP](http://www.delorie.com/djgpp/).

Unzip the sources and run:

`make vuld`

## Runtime Prerequisites

* VULD
* [CWSDPMI](http://sandmann.dotster.com/cwsdpmi/)
* [DEHACKED.EXE](https://www.doomworld.com/idgames/utils/exe_edit/dhe31)
    * **NOTE**: Delete or move the DEHACKED.INI file before starting!
* [DEUSF.EXE or DEUTEX.EXE](http://www.gamers.org/addons/utils/deutex/)

## Instructions

* Gather the required ingredients below and put them in your game folder.
    * **Required**: Only ONE game per folder! Do not mix game assets from different versions or sequels.
    * **Required**: Delete or move the DEHACKED.INI file before starting, or it may interfere with VULD patching.
* Unzip the vanilla mods with flats, sprites, etc. and/or DeHackEd files into subdirectories of your main game folder.
    * **Required**: Only ONE mod per subfolder! All mods (DEH and WAD files) in a subfolder will be merged at the same time, potentially overwriting one another.
* While in your main game folder, type `VRUN`, press enter, select the mod you want to play and it should compile and launch without modifying your game files.
    * **Warning:** If you have a doomhack.exe, back it up first or it will be overwritten!
    * If DeHackEd asks if you want to create a **doomhack.exe**, say "yes" to avoid overwriting data in your main game files.

## TODO List

* INI file mode
* Automatic detection of game/mod pairing(?)


# DEHPICK

DEHPICK is a simple utility to find and apply DeHackEd patches.

Run `DEHPICK.EXE` in a folder containing your game files and a set of DeHackEd patches, and DEHPICK will let you choose which one to apply.

**WARNING**: If you have a DOOMHACK.EXE, patches will be applied *on top of that* executable. If this is not the behavior you want, delete DOOMHACK.EXE before running DEHPICK. DEHPICK will not delete DOOMHACK.EXE for you.


# License

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
