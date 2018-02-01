@echo off
if [%1]==[justcompile] goto :justcompile

echo Generating Pals
..\utils\mkts.exe mode=pals pals=..\gfx\palts0.png out=work\palts0.h label=palts0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1.png out=work\palts1.h label=palts1 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts2.png out=work\palts2.h label=palts2 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss0.png out=work\palss0.h label=palss0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\paltstitle.png out=work\paltstitle.h label=paltstitle silent
..\utils\mkts.exe mode=pals pals=..\gfx\palsstitle.png out=work\palsstitle.h label=palsstitle silent
..\utils\mkts.exe mode=pals pals=..\gfx\palcuts0.png out=work\palcuts0.h label=palcuts0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\paltsl.png out=work\paltsl.h label=paltsl silent
..\utils\mkts.exe mode=pals pals=..\gfx\palssl.png out=work\palssl.h label=palssl silent
..\utils\mkts.exe mode=pals pals=..\gfx\paltsr.png out=work\paltsr.h label=paltsr silent
copy /b work\palts0.h + work\palts1.h + work\palts2.h + work\palss0.h + work\paltstitle.h + work\palsstitle.h + work\palcuts0.h + work\paltsl.h + work\palssl.h + work\paltsr.h assets\palettes.h

echo Exporting chr
cd ..\gfx

if [%1]==[compo] goto :compo
..\utils\mkts.exe mode=scripted in=cut_patterns_0.spt out=..\dev\tileset0.chr silent
..\utils\mkts.exe mode=scripted in=cut_patterns_3.spt out=..\dev\tileset3.chr silent
goto :compodone
:compo
..\utils\mkts.exe mode=scripted in=cut_patterns_0_compo.spt out=..\dev\tileset0.chr silent
..\utils\mkts.exe mode=scripted in=cut_patterns_3_compo.spt out=..\dev\tileset3.chr silent
:compodone


echo Exporting enems
cd ..\enems
..\utils\eneexp3c.exe level0.ene ..\dev\assets\enems0.h 0 1
..\utils\eneexp3c.exe level1.ene ..\dev\assets\enems1.h 1 1
..\utils\eneexp3c.exe level2.ene ..\dev\assets\enems2.h 2 1
..\utils\eneexp3c.exe level3.ene ..\dev\assets\enems3.h 3 1
..\utils\eneexp3c.exe level4.ene ..\dev\assets\enems4.h 4 1
..\utils\eneexp3c.exe leveli.ene ..\dev\assets\enemsi.h i 1

echo Making map 
cd ..\map
..\utils\rle53mapchrrom.exe in=maplist.txt bin=..\dev\work\mapchr.bin out=..\dev\assets\chr-rom-maps.h
cd ..\dev
copy work\mapchr.bin.1 tileset1.chr >nul
copy work\mapchr.bin.2 tileset2.chr >nul

rem echo Making texts
rem cd ..\texts
rem ..\utils\texts2array.exe dialogue.txt ..\dev\assets\texts.h texts0 19

cd ..\dev
:justcompile

if [%1]==[compo] goto :compocomp
cc65 -Oi game.c --add-source
goto :compocompdone
:compocomp
cc65 -Oi game.c --add-source -DCOMPO
:compocompdone

ca65 crt0-CNROM.s -o crt0.o
ca65 game.s
ld65 -v -C nes-CNROM.cfg -o d'veel'ng.nes crt0.o game.o runtime.lib -Ln labels.txt

del game.s
del game.o
del crt0.o
