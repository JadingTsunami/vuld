# VULD: A Launcher for Vanilla Mods

## Compilation

Acquire the [latest source](https://github.com/JadingTsunami/vuld).

Compiles with [DJGPP](http://www.delorie.com/djgpp/).

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
* If you want to re-run the most recent mod without rebuilding, use the `VRERUN` command.
    * Note this requires you to have run with `VRUN` first.
* If you want to use VULD to create files but not run them, leaving them available for later use, use the `VCREATE` command instead of VRUN above.
    * **Warning:** Files constructed by `VCREATE` are for **local use only** on your machine; do not distribute them.
    * Files will be placed in a subfolder called VULD_DIR and will be named according to the mod you loaded (example: files from the subdirectory ASTRO would be ASTRO.EXE if DeHackEd patches were loaded and/or ASTRO.WAD if WAD file patches were loaded).
    * The resulting files need to be run from your game directory and loaded with the `-file` command as with any standard PWAD. So if your mod is called `example`, you can run it immediately after `VCREATE` by navigating to your game directory and typing: `vuld_dir\example.exe -file vuld_dir\example.wad`.


## TODO List

* INI file mode
* Automatic detection of game/mod pairing(?)


# DEHPICK

DEHPICK is a simple utility to find and apply DeHackEd patches.

Run `DEHPICK.EXE` in a folder containing your game files and a set of DeHackEd patches, and DEHPICK will let you choose which one to apply.

You can also optionally supply a folder as a command-line argument and DEHPICK will look for DeHackEd patches there, as well as store the patched executable in that folder.

**WARNING**: If you have a DOOMHACK.EXE, patches can be applied *on top of that* executable. This will allow you to apply multiple patches by running DEHPICK more than once. Alternatively, DEHPICK will give you the option to start over. The "start over" option will **delete your DOOMHACK.EXE** and start with a clean game executable.

# Acknowledgements and Credits

All company names, product names, trademarks and/or registered trademarks are property of their respective owners. All company, product and/or service names used on this page are for identification purposes only. Use of these names, trademarks and/or brands does not imply endorsement nor affiliation.

Big thanks to Redneckerz for testing and providing valuable and detailed feedback during development.

Thanks to Doomkid for inspiring the creation of [DEHPick](https://www.doomworld.com/forum/topic/114759-creating-an-auto-dehacker-for-vanilla/?page=2&tab=comments#comment-2138488).

[DeHackEd](https://www.doomworld.com/idgames/utils/exe_edit/dhe31) was created by Greg Lewis.

[DeuTex, DeuSF and WinTex](http://www.gamers.org/addons/utils/deutex/)  are Copyright (c) O.Montanuy 1994,1995.

DOOM and DOOM II are registered trademarks of ZeniMax Media Inc. in the US and/or other countries. Id Software® is a registered trademark of ZeniMax Media Inc. in the US and/or other countries. This software is in no way affiliated with ZeniMax Media Inc. or id Software LLC and is not approved by ZeniMax Media Inc. or id Software.


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
