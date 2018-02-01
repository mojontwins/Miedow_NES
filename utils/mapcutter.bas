Sub usage
	Print "$ mapcutter in.map out.map x0 y0 win hin wout hout scr_w scr_h"
	Print
	Print "    x0,y0        - cut from here (in screens)"
	Print "    win,hin      - original map is this size (in screens)"
	Print "    wout,hout    - output map is this size (in screens)"
	Print "    scr_w,scr_h  - original screen size"
End Sub

Dim As Integer x0, y0, x, y, xx, yy, w, h, scr_w, scr_h, x1, y1, map_w, map_h, i, j
Dim As Integer fIn, fOut
Dim As uByte d

If Command (10) = "" Then 
	usage
	End
End If

fIn = FreeFile: Open Command (1) For Binary As #fIn
fOut = FreeFile: Open Command (2) For Binary As #fOut

x0 = Val (Command (3)): y0 = Val (Command (4))
w = Val (Command (7)): h = Val (Command (8))
scr_w = Val (Command (9)): scr_h = Val (Command (10))
map_w = Val (Command (5)) * scr_w: map_h = Val (Command (6)) * scr_h
x1 = x0 + w - 1: y1 = y0 + h - 1

' Skip?
If y0 > 0 Then
	For i = 1 To y0 * scr_h * map_w
		Get #fIn, , d
	Next i
End If

' Process h files of screens
For j = 1 To h * scr_h

	' Skip?
	If x0 > 0 Then
		For i = 1 To x0 * scr_w
			Get #fIn, , d 
		Next i 
	End If

	' Process w screens accross
	For i = 1 To w * scr_w
		Get #fIn, , d
		Put #fOut, , d 
	Next i

	' Skip to next line ?
	If (x0 + w) * scr_w < map_w Then
		For i = 1 To map_w - (x0 + w) * scr_w
			Get #fIn, , d
		Next i
	End If
Next j
	
Close

' this was way too easy...
