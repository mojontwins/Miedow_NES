' Map Reorganizer 1.0
' Copyleft 2017 by The Mojon Twins

' fbc mapreorganizer.bas cmdlineparser.bas mtparser.bas

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

#include "cmdlineparser.bi"
#include "mtparser.bi"

Dim Shared As Integer verbose
Dim Shared As Integer fixMappy
Dim Shared As String orderfile

Sub usage
	Puts "$ mapreorganizer.exe in=in.map out=out.map "
	Puts "                     ts_in=in.png ts_out=out.png"
	Puts "                     [script_in=in.spt script_out=out.spt]"
	Puts "                     [verbose] [fixmappy]"
	Puts "                     [orderfile=orderfile.bin]"
End Sub

Sub mapRead (fnIn As String, map () As Integer, ByRef mapL As Integer)
	Dim As Integer fIn
	Dim As uByte d

	fIn = FreeFile
	Open fnIn For Binary As #fIn 

	mapL = 0
	While Not Eof (fIn)
		Get #fIn, , d
		If fixMappy Then d = d - 1
		map (mapL) = d: mapL = mapL + 1
	Wend

	Close #fIn 

	If verbose Then
		Puts "Map " & fnIn & " read. " & mapL & " tiles."
		Puts ""
	End If
End Sub

Sub mapCount (map () As Integer, count () As Integer, mapL As Integer, ByRef maxT As Integer)
	Dim As Integer i

	For i = 0 To mapL
		count (map (i)) = count (map (i)) + 1
		If map(i) > maxT Then maxT = map (i)
	Next i

	If verbose Then
		Puts "Tile count"
		For i = 0 To maxT
			Puts "+ Tile " & Hex (i, 2) & " x " & count (i)
		Next i
		Puts "This is, maxT different tiles."
		Puts ""
	End If
End Sub

Sub listReorder (list () As Integer, count () As Integer, maxT As Integer)
	Dim As Integer i, j
	Dim As uByte d

	' Zero doesn't count!
	For i = 1 To maxT
		For j = 1 To maxT - i
			If count (j) < count (j + 1) Then
				Swap count (j), count (j + 1)
				Swap list (j), list (j + 1)
			End If 
		Next j
	Next i

	If orderfile <> "" Then
		j = FreeFile
		Open orderfile For Binary As j
		For i = 0 To maxT
			d = list (i): Put #j , , d
		Next i
		Close j
	End If

	If verbose Then
		Puts "Bubble Sort'd (minus 0)"
		For i = 0 To maxT
			Puts "+ Tile " & Hex (i, 2) & " -> " & Hex (list (i), 2) & " x " & count (i)
		Next i
	End If
End Sub

Function findInList (value As Integer, list () As Integer) As Integer
	Dim As Integer res, i
	res = 0

	For i = 0 To uBound (list)
		If value = list (i) Then res = i : Exit For
	Next i

	findInList = res
End Function 

Sub mapReorder (map () As Integer, list () As Integer, mapL As Integer, maxT As Integer)
	Dim As Integer i

	For i = 0 To mapL - 1
		map (i) = findInList (map (i), list ())
	Next i

	If verbose Then
		Puts "Map file reordered."
		Puts ""
	End If
End Sub

Sub mapWrite (fnOut As String, map () As Integer, mapL As Integer)
	Dim As integer i, fOut 
	Dim As uByte d

	fOut = FreeFile
	Open fnOut For Binary As #fOut

	For i = 0 To mapL - 1
		d = map (i)
		If fixMappy Then d = d + 1
		Put #fOut, , d
	Next i

	Close #fOut

	If verbose Then
		Puts "Map file " & fnOut & " written"
		Puts ""
	End If
End Sub

Sub tsLoad (fnIn As String, ByRef img As Any Ptr, maxT As Integer)
	Dim As Integer w, h

	img = png_load (fnIn)
	If ImageInfo (img, w, h, , , , ) Then
		' Error!
	End If

	If verbose Then
		Puts "Tileset " & fnIn & " read."
		Puts "+ Image size " & w & "x" & h & "."
		Puts "+ estimated tile count (I'm blind) = " & ((w\16)*(h\16))
		If ((w\16)*(h\16)) >= maxT Then Puts "  which seems right..." Else Puts "  which are TOO FEW!"
		Puts ""
	End If
End Sub

Sub getTileCoordinatesInTs (tN As Integer, w As Integer, h As Integer, ByRef tx As Integer, ByRef ty As Integer)
	tx = 16 * (tN Mod (w\16))
	ty = 16 * (tN \ (w\16))
End Sub

Sub tsReorder (img As Any Ptr, ByRef imgOut As Any Ptr, list () As Integer, maxT As Integer)
	' Let's try to outsmart this...
	Dim As Integer w, h, t1X, t1Y, t2X, t2Y, i

	If ImageInfo (img, w, h, , , , ) Then
		' Error!
	End If
	
	imgOut = ImageCreate (w, h, 0)

	For i = 0 To maxT
		getTileCoordinatesInTs i, w, h, t1X, t1Y
		getTileCoordinatesInTs list (i), w, h, t2X, t2Y

		' Copy
		Put imgOut, (t1X, t1Y), img, (t2X, t2Y) - (15 + t2X, 15 + t2Y), PSet
	Next i

	If verbose Then
		Puts "Tileset reordered."
		Puts ""
	End if
End Sub

Sub tsSave (fnOut As String, img As Any Ptr)
	Dim As Integer dummy

	dummy = png_save (fnOut, img)

	If verbose Then
		Puts "Tileset " & fnOut & " written."
		Puts ""
	End If
End Sub

Sub processScript (fnIn As String, fnOut As String, list () As Integer)
	Dim As Integer fIn, fOut
	Dim As String linea, nLinea
	Dim As String tokens (63)
	Dim As Integer decorating, rebuild

	fIn = FreeFile
	Open fnIn For Input As #fIn
	fOut = FreeFile
	Open fnOut For Output As #fOut

	If verbose Then
		Puts "Processing script " + fnIn
		Puts "Writing script " + fnOut
		Puts "With changes: "
	End if

	decorating = 0
	While Not Eof (fIn)
		Line Input #fIn, linea
		rebuild = 0

		' Fullery here
		parseTokenizeString Trim (Ucase (linea), Any Chr (32) + Chr (9)), tokens (), "(),=", ""

		If decorating Then
			If tokens (0) = "END" Then 
				decorating = 0
			Else
				' ?, ?, T
				If tokens (2) <> "" Then
					If Left (tokens (2), 1) <> "#" Then
					tokens (2) = Trim (Str (findInList (Val (tokens (2)), list ())))
						rebuild = -1
						nLinea = tokens (0) & ", " & tokens (1) & ", " & tokens (2)
					End If
				End If
			End If
		Else
			If tokens (0) = "DECORATIONS" Then	
				decorating = -1
			ElseIf tokens (0) = "SET" And tokens (1) = "TILE" Then
				' SET TILE (?, ?) = T
				If tokens (4) <> "" Then
					If Left (tokens (4), 1) <> "#" Then
						tokens (4) = Trim (Str (findInList (Val (tokens (4)), list ())))
						rebuild = -1
						nLinea = "SET TILE (" & tokens (2) & ", " & tokens (3) & ") = " & tokens (4)
					End If 
				End If 
			End If
		End If

		If rebuild Then
			If verbose Then Puts " + rewriting " & linea
			linea = initialWhiteSpace (linea) & nLinea
			If verbose Then Puts " + into      " & linea
		End If

		Print #fOut, linea
	Wend

	If verbose Then
		Puts "Done with the script."
	End If

	Close fIn, fOut
End Sub

Dim As String mandatory (3) = { "in", "out", "ts_in", "ts_out" }
Dim As Integer list (255)
Dim As Integer count (255)
Dim As Integer map (65535), mapL, maxT
Dim As Integer i, j, k, x, y
Dim As Any Ptr img, imgOut

sclpParseAttrs

If Not sclpCheck (mandatory ()) Then
	usage
	End
End If

If sclpGetValue ("script_in") <> "" Or sclpGetValue ("script_out") <> "" Then
	If sclpGetValue ("script_in") = "" Or sclpGetValue ("script_out") = "" Then
		usage
		End
	End if
End If

verbose = (sclpGetValue ("verbose") <> "")
fixMappy = (sclpGetValue ("fixmappy") <> "")
orderfile = sclpGetValue ("orderfile")

' Initialization

For i = 0 To 255
	list (i) = i
	count (i) = 0
Next i

mapRead sclpGetValue ("in"), map (), mapL
mapCount map (), count (), mapL, maxT
listReorder list (), count (), maxT
mapReorder map (), list (), mapL, maxT
mapWrite sclpGetValue ("out"), map (), mapL

screenres 640, 480, 32, , -1

tsLoad sclpGetValue ("ts_in"), img, maxT
tsReorder img, imgOut, list (), maxT
tsSave sclpGetValue ("ts_out"), imgOut

ImageDestroy img
ImageDestroy imgOut

If sclpGetValue ("script_in") <> "" Then
	processScript sclpGetValue ("script_in"), sclpGetValue ("script_out"), list ()
End if

Puts "Done."
