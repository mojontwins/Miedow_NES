' rle53mapchrrom v0.1 20171113
' Creates a packed map plus decorations ready to be written to CHR ROM.
' Copyleft 2017 by The Mojon Twins

' fbc rle53map.bas cmdlineparser.bas mtparser.bas

#include "cmdlineparser.bi"
#include "mtparser.bi"

Dim Shared As uByte mainBin (8191)
Dim Shared As Integer binIndex

Dim Shared As uByte partialBin (8191)
Dim Shared As Integer partialBinIndex

Sub resetBin ()
	binIndex = 0
End Sub

Sub writeToBin (v as uByte)
	mainBin (binIndex) = v
	If binIndex < 8191 Then binIndex = binIndex + 1
End Sub

Sub writeBin (f As Integer)
	Dim As Integer i
	Dim As uByte d
	d = 0

	For i = 0 To 8191
		If i < binIndex Then
			Put #f, , mainBin (i)
		Else
			Put #f, , d
		End If
	Next i
End Sub

Sub resetPartialBin ()
	partialBinIndex = 0
End Sub

Sub writeToPartialBin (v As uByte)
	partialBin (partialBinIndex) = v
	If partialBinIndex < 8191 Then partialBinIndex = partialBinIndex + 1
End Sub

Sub copyPartialBinToMainBin ()
	Dim As Integer i
	Print "Copying " & partialBinIndex & " bytes to main bin @ " & binIndex
	For i = 0 To partialBinIndex - 1
		writeToBin partialBin (i)
	Next i
End Sub

Sub usage
	Print "usage: "
	Print ""
	Print "rle53mapchrrom in=list.txt bin=chr.bin out=map.h [fixmappy]"
	Print "              in is the input filename. A list of .map in text format."
	Print "              bin is the binary file to be loaded to CHR-ROM"
	Print "              out is the output filename."
	Print "              fixmappy will substract 1 from every byte read"
	Print ""
	Print "list file format: Each line must look like this:"
	Print ""
	Print "filename.map,w,h,l0[-...]"
	Print ""
	Print "Where filename.map is the map filename, and w and h are each map's size"
	Print "lX are lock tile #s, '-' separated."
End Sub

Dim As String mandatory (2) = { "in", "bin", "out" }
Dim As Integer coords (31), mapW, mapH, scrW, scrH, nPant, maxPants, mapWtiles, fixMappy, realPant, nMap
Dim As Integer fIn, fOut, fBin, fListIn, xP, yP, x, y, i, j, first, tLock, locksI, n, cMapI, ctr, totalBytes, t0, lockssize, screensum
Dim As uByte BigMap (127, 255)
Dim As uByte cMap (127, 255), scrSizes (127)
Dim As String*384 cMapAmalgam (127)
Dim As uByte locks (63)
Dim As uByte d, dp, layer
Dim As uByte scrMaps (127)
Dim As String mapFile
Dim As Integer tlocks (31), tlocksIndex
DIm As String tlocksString
Dim As Integer shows
Dim As String fileName

' decos
Dim As Integer decosAre, decosize
Dim As uByte decoT, decoCT
Dim As uByte decos (127, 127), decosYX (127, 127), YX (127), decosO (127, 127), decosI (127), decosOI (127)
Dim As Integer scrBinOffs (127)

' CHR ROM
Dim As uByte chrRom 
Dim As uInteger lBase

Print "rle53mapchrrom v0.1 20171113"

sclpParseAttrs
If Not sclpCheck (mandatory ()) Then usage: End

fixMappy = (sclpGetValue ("fixmappy") <> ""): If fixMappy Then Print "[fixmappy] ";

fListIn = FreeFile
Open sclpGetValue ("in") For Input As #fListIn

fOut = FreeFile
Open sclpGetValue ("out") For Output As #fOut

shows = (sclpGetValue ("scrsizes") <> "")

Print #fOut, "// CHR-ROM Map & decos indexes"
Print #fOut, "// Generated by rle53mapchrrom.exe v0.1 20171113"
Print #fOut, "// Copyleft 2017 by The Mojon Twins"

Print #fOut, ""

lBase = 0
chrRom = 1
scrW = 16: scrH = 12
nMap = 0

resetBin

While Not Eof (fListIn) 

	Input #fListIn, mapFile
	Input #fListIn, mapW
	Input #fListIn, mapH
	Input #fListIn, tlocksString

	parseCoordinatesStringCustom tlocksString, "-", coords ()
	tlocksIndex = 0
	While (coords (tlocksIndex) > 0)
		tlocks (tlocksIndex) = coords (tlocksIndex)
		tlocksIndex = tlocksIndex + 1
	Wend

	maxPants = mapW * mapH
	Print "Processing " & mapFile & " (" & mapW & "x" & mapH & ") ~ ";

	Print #fOut, "// Map # " & nMap & " read from " & mapFile & " (" & mapW & "x" & mapH & ")"
	Print #fOut, ""
	
	Print "Reading ~ ";

	fIn = FreeFile
	Open mapFile For Binary As #fIn

	For i = 0 To 127
		decosI (i) = 0
		decosOI (i) = 0
	Next i

	i = 0: dp = 0
	locksI = 0
	decosAre = 0

	While Not Eof (fIn)
		Get #fIn, , d

		xP = (i \ scrW) Mod mapW
		yP = i \ (scrW * scrH * mapW)

		x = i Mod scrW
		y = (i \ (mapW * scrW)) Mod scrH

		nPant = xP + yP * mapW

		i = i + 1

		For j = 0 To tlocksIndex - 1
			If d = tlocks (j) Then
				locks (locksI) = nPant: locksI = locksI + 1
				locks (locksI) = (y Shl 4) Or x: locksI = locksI + 1
			End If
		Next j
	
		If d > 31 Then
			' deco
			If Not decosAre Then 
				Print "Found T(s) OOR ";
				If sclpGetValue ("nodecos") <> "" Then Print "(ignored)" Else Print "(decos)"
				decosAre = -1
			End If			
			' Write to decos
			decosYX (nPant, decosI (nPant)) = y * 16 + x
			decos (nPant, decosI (nPant)) = d
			decosI (nPant) = decosI (nPant) + 1
			' Reset to previous (so there's more repetitions)
			d = dp
		End If

		BigMap (nPant, scrW * y + x) = d - t0
		dp = d
	Wend

	Print "Compressing ~ ";
	totalBytes = 0
	For nPant = 0 To maxPants - 1
		d = BigMap (nPant, 0): n = 1: cMapI = 0
		cMapAmalgam (nPant) = ""
		screensum = 0
		For i = 1 To scrW*scrH-1
			screensum = screensum + BigMap (nPant, i)
			' Different: write, substitute
			If BigMap (nPant, i) <> d Or n = 8 Then
				cMap (nPant, cMapI) = (d And 31) Or ((n - 1) Shl 5)
				cMapAmalgam (nPant) = cMapAmalgam (nPant) & Hex (cMap (nPant, cMapI), 2)
				cMapI = cMapI + 1
				n = 0
			End If
			d = BigMap (nPant, i): n = n + 1
		Next i
		cMap (nPant, cMapI) = (d And 31) Or ((n - 1) Shl 5)
		cMapAmalgam (nPant) = cMapAmalgam (nPant) & Hex (cMap (nPant, cMapI), 2)
		cMapI = cMapI + 1

		realPant = nPant

		' Detect empty screen
		If screensum = 0 Then 
			realPant = 255: cMapI = 0
		Else
			' Search for repeated screens
			For j = 0 To nPant - 1
				If cMapAmalgam (j) = cMapAmalgam (nPant) Then
					realPant = j
					cMapI = 0
					Exit For
				End If
			Next j
		End If

		scrSizes (nPant) = cMapI
		scrMaps (nPant) = realPant '' Fixe here
		totalBytes = totalBytes + cMapI
	Next nPant

	' Write packed tiles to tempbin
	Print "Writing packed tiles"
	resetPartialBin 
	For nPant = 0 To maxPants - 1
		If scrMaps (nPant) = 255 Then
			If shows Then Print #fOut, "// Screen " & Lcase (Hex (nPant, 2)) & " is empty."
		ElseIf scrSizes (nPant) Then
			scrBinOffs (nPant) = partialBinIndex
			For i = 0 To scrSizes (nPant) - 1
				writeToPartialBin cMap (nPant, i)
			Next i
			If shows Then Print #fOut, "// Size = " & scrSizes (nPant) & " bytes."
		Else
			If shows Then Print #fOut, "// Screen " & Lcase (Hex (nPant, 2)) & " is a copy of screen " & Lcase (Hex (scrMaps (nPant), 2)) & "."
		End If
	Next nPant

	' Does it fit?
	If binIndex + partialBinIndex > 8192 Then
		fBin = FreeFile
		Print "Writing binary #" & chrRom
		Open sclpGetValue ("bin") & "." & chrRom For Binary As #fBin
		writeBin fBin
		Close fBin
		resetBin
		chrRom = chrRom + 1
		lBase = 0
	End If

	' Copy
	copyPartialBinToMainBin

	Print #fOut, "// Definitions"
	Print #fOut, ""
	Print #fOut, "#define MAP_" & Hex (nMap, 2) & "_CHRROM    " & chrRom
	Print #fOut, "#define MAP_" & Hex (nMap, 2) & "_BASE      0x" & Hex (lBase, 4)
	Print #fOut, "#define MAP_" & Hex (nMap, 2) & "_W         " & mapW
	Print #fOut, "#define MAP_" & Hex (nMap, 2) & "_H         " & mapH
	Print #fOut, "#define MAP_" & Hex (nMap, 2) & "_MAXPANTS  " & (mapW*mapH)
	Print #fOut, ""

	Print #fOut, "// Screens index"
	Print #fOut, ""
	Print #fOut, "const unsigned int map_" & Hex (nMap, 2) & "_scr_offsets [] = {"
	j = 0: first = -1

	For nPant = 0 To maxPants - 1
		If first Then first = 0 Else Print #fOut, ", ";
		If j = 2 Then Print #fOut, "": j = 0
		If j = 0 Then Print #fOut, "	";

		If scrMaps (nPant) = 255 Then
			Print #fOut, "0                   ";
		ElseIf scrSizes (nPant) Then
			Print #fOut, "MAP_" & Hex (nMap, 2) & "_BASE + 0x" & Hex (scrBinOffs (nPant), 4);
		Else
			Print #fOut, "MAP_" & Hex (nMap, 2) & "_BASE + 0x" & Hex (scrBinOffs (scrMaps (nPant)), 4);
		End if
		j = j + 1
	Next nPant

	If j then Print #fOut, ""
	Print #fOut, "};"
	Print #fOut, ""
	Print #fOut, "// Total screens size in bytes is " & partialBinIndex
	Print #fOut, ""

	Print "Writing locks"
	lockssize = 0
	If locksI Then
		Print #fOut, "// Locks"
		Print #fOut, "// These tiles are locks: ";
		For i = 0 To tlocksIndex - 1
			Print #fOut, tlocks (i); 
		Next i
		Print #fOut, ""
		Print #fOut, "const unsigned char map_" & Hex (nMap, 2) & "_locks [] = {"
		Print #fOut, "	";

		For i = 0 To locksI - 1
			Print #fOut, "0x" & Lcase (Hex (locks (i), 2));
			If i < locksI - 1 Then Print #fOut, ", ";
			lockssize = lockssize + 1
		Next i
		Print #fOut, ""
		Print #fOut, "};"
		Print #fOut, ""
	End If

	' Update base
	lBase = lBase + partialBinIndex

	Close #fIn

	Print "DONE!"

	nMap = nMap + 1

Wend

Print "Writing binary #" & chrRom
fBin = FreeFile
Open sclpGetValue ("bin") & "." & chrRom For Binary As #fBin
writeBin fBin
Close fBin

Close fListIn
Close fOut
