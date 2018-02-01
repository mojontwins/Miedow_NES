' Map Reordenator 1.0
' Copyleft 2017 by The Mojon Twins

' fbc mapreordenator.bas cmdlineparser.bas mtparser.bas

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

#include "cmdlineparser.bi"
#include "mtparser.bi"

Sub usage
	Puts "$ mapreordenator.exe in=in.map out=out.map "
	Puts "                     orderfile=orderfile.bin"
	Puts "                     [fixmappy]"
End Sub

Function findInList (value As Integer, list () As Integer) As Integer
	Dim As Integer res, i
	res = 0

	For i = 0 To uBound (list)
		If value = list (i) Then res = i : Exit For
	Next i

	findInList = res
End Function 

Dim As String mandatory (2) = { "in", "out", "orderfile" }
Dim As uByte d 
Dim As Integer fIn, fOut
Dim As Integer idx, fixmappy
Dim As Integer list (255)

sclpParseAttrs

If Not sclpCheck (mandatory ()) Then
	usage
	End
End If

fixmappy = (sclpGetValue ("fixmappy") <> "")

fIn = FreeFile: Open sclpGetValue ("orderfile") For Binary As #fIn
idx = 0
While Not Eof (fIn)
	Get #fIn, , d
	If idx <= 255 Then
		list (idx) = d: idx = idx + 1
	End If
Wend
Close #fIn

fIn = FreeFile:  Open sclpGetValue ("in")  For Binary As #fIn
fOut = FreeFile: Open sclpGetValue ("out") For Binary As #fOut

While Not Eof (fIn)
	Get #fIn, , d
	If fixmappy Then d = d - 1
	d = findInList (d, list ())
	If fixmappy Then d = d + 1
	Put #fOut, , d
Wend

Close
