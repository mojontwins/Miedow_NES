Sub usage
	print "This program generates a strip for the Pantanow Engine [maritrini]"
	print "$ eneexpp enems.ene out.h prefix"
End Sub

Type enemType
	type As uByte
	x As uByte
	y As uByte
	xx As uByte
	yy As uByte
	mn As uByte
	s1 As uByte
	s2 As uByte
End Type

Dim As Integer fIn, fOut, ctrr
Dim As uByte d, y, x, a, b, t
Dim As enemType enems (16*16)
Dim As Integer mapW, mapH, scrW, scrH, nEnems, maxEnems, mapPants, nPant, i, j, hl, yadjust, noHotspots
Dim As String prefix, dummy

If Command (3) = "" Then usage: End
prefix = Command (3)

' .ENE contains...
' t x1 y1 x2 y2 n s1 s2
' n is speed
' s1, s2 are unused.

fIn = FreeFile
Open Command (1) For Binary As #fIn
fOut = FreeFile
Open Command (2) For Output As #fOut

' Header
dummy = Input (256, fIn)
Get #fIn, , d: mapW = d
Get #fIn, , d: mapH = d
Get #fIn, , d: scrW = d
Get #fIn, , d: scrH = d
Get #fIn, , d: nEnems = d

mapPants = mapW * mapH
maxEnems = mapPants * nEnems

If mapW <> 1 Or mapH <> 16 Or scrW <> 16 Or scrH <> 16 Then
	Print "*warning* map size may be incorrect (" & mapW & "x" & mapH & "x" & scrW & "x" & scrH & ", must be 1x16x16x16)"
	'System
End If

Print "Reading " & maxEnems & " enems. ";

For i = 0 To maxEnems - 1
	Get #fIn, , d: enems (i).type = d
	Get #fIn, , d: enems (i).x = d
	Get #fIn, , d: enems (i).y = d + (i\nEnems)*16
	Get #fIn, , d: enems (i).xx = d
	Get #fIn, , d: enems (i).yy = d
	Get #fIn, , d: enems (i).mn = d
	Get #fIn, , d: enems (i).s1 = d
	Get #fIn, , d: enems (i).s2 = d
Next i

Print "Reordering. ";

For i = 0 To maxEnems-1
	For j = 0 To maxEnems - 1 - i
		if enems (j).y < enems (j+1).y Then Swap enems (j), enems (j+1)
	Next j
Next i

Print "Writing. ";

Print #fOut, "// " & Command (2)
Print #fOut, "// Generated by eneexpp.exe v0.1 [20170531]"
Print #fOut, "// Copyleft 2017 The Mojon Twins"
Print #fOut, ""
Print #fOut, "// YYYYYYYY XXXXTTTT BBBBAAAA"
Print #fOut, "// enems stored in decreasing Y order"
Print #fOut, ""

Print #fOut, "const unsigned char enems_strip_" & prefix & " [] = {"

For i = 0 To maxEnems - 1
	j = 0
	If enems (i).type Then
		y = enems (i).y
		x = enems (i).x
		t = enems (i).type
		a = enems (i).mn
		b = enems (i).s1

		Select Case enems (i).type
			Case 1:
				b = 0
			Case 2:
				If enems (i).x < enems (i).xx Then b = 0 Else b = 1
			Case 3:
				If enems (i).x < enems (i).xx Then b = 0 Else b = 1
			Case 4:
			Case 5:
				If enems (i).x <> enems (i).xx Then 
					b = 8 
					If enems (i).x > enems (i).xx Then b = b Or 4 
				Else 
					b = 0
				End If
			Case 7:
				a = enems (i).x: b = enems (i).xx	
		End Select

		Print #fOut, "	" & y & ", 0x" & Lcase (Hex (((x Shl 4) Or t), 2)) & ", 0x" & Lcase (Hex (((b Shl 4) Or a), 2)) & ","
	End If
Next i

Print #fOut, "	";
Print #fOut, "0, 0, 0 // end marker"
Print #fOut, "};"
Print #fOut, ""

Close

Print "DONE"