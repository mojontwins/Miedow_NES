@echo off
..\utils\text2data.exe miedow.txt -ca65 -ch1..4
copy miedow.s ..\dev\music.s
echo DONE.