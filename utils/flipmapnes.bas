' Flip Map Nes

Dim As Integer mapW, mapH, fIn, fOut, x, y, xx, yy, iVi, iVf, iVs, iHi, iHf, iHs, xo, yo
ReDim As uByte map (1024, 1024)
Dim As uByte d

If Len (Command (5)) = 0 Then
	Print "flipmapnes in.map out.map w h [horz|vert|both]"
	Print "w and h = screens, 16x12 tiles."
	System
End If

mapW = 16 * Val (Command (3))
mapH = 12 * Val (Command (4))

fIn = FreeFile
Open Command (1) For Binary as #fIn
fOut = FreeFile
Open Command (2) For Binary as #fOut

For y = 0 To mapH - 1
	For x = 0 To mapW - 1
		get #fIn, , d
		map (y, x) = d
	Next x
Next y

' Reorder
if Command (5) = "vert" Or Command (5) = "both" Then
	iVi = mapH - 1: iVf = 0: iVs = -1
Else
	iVi = 0: iVf = mapH - 1: iVs = 1
End if

if Command (5) = "horz" Or Command (5) = "both" Then
	iHi = mapW - 1: iHf = 0: iHs = -1
Else
	iHi = 0: iHf = mapW - 1: iHs = 1
End If

For y = iVi To iVf Step iVs
	For x = iHi To iHf Step iHs
		d = map (y, x)
		Put #fOut, , d
	Next x
Next y

Close

Redim map (0,0)

? "OK"
