Dim As Integer y, m, c, d, s, x, beh
Dim As uByte d1, d2
Dim As Integer fOut

'' Enems Calculator
Print "Enems Calculator for Pantanow et al"
Print "99 + enter to end"
Print
Print "If you run with a parameter, output will be written to the file"
Print "Careful! If file exists it will be overwritten."
Print

fOut = 0
If Command (1) <> "" Then 
	fOut = FreeFile
	Open Command (1) For Output As #fOut
	Print "Data lines will be output to " & Command (1)
End If 

Do
	Print "COORDENADA Y"
	Print "0 a 239"
	Input y
	If y = 99 Then Exit Do

	Print
	Print "MOVIMIENTO"
	Print "0 000 - Torreta, no se mueve."
	Print "1 001 - Se mueve al azar en obstáculo."
	Print "2 010 - Se mueve al azar con contador en obstáculo."
	Print "3 011 - Se mueve hacia tí."
	Print "4 100 - Programado"
	Print "5, 6, 7 = 1, 2, 3 desde abajo"
	Input m
	If m = 99 Then Exit Do

	If m = 4 Then
		Print
		Print "COMPORTAMIENTO"
		Print "0-31 - comportamiento elegido"
		Input beh
	Else
		Print
		Print "COLISION"
		Print "0 000 - No hacer nada (parar y ya)."
		Print "1 001 - Invertir ejes."
		Print "2 010 - Elegir otra dirección"
		Print "3 011 - ?"
		Print "4, 5, 6, 7 = 0, 1, 2, 3, pero además disparan."
		Input c
		If c = 99 Then Exit Do

		Print
		Print "DISPARO"
		Print "0 00 - Aleatoriamente, en la dirección en la que andan"
		Print "1 01 - Cada segundo, en la dirección en la que andan"
		Print "2, 3 = 1, 2, pero hacia tí."
		Input d
		If d = 99 Then Exit Do
	End If

	If m = 0 Then 
		s = 2 
	Else
		Print "SPRITE"
		Print "0 Morena, 1 Pelirroja"
		Input s
		If s = 99 Then Exit Do
	End If

	Print
	Print "COORDENADA X"
	Print "0 a 15"
	Input x
	If x = 99 Then Exit Do

	Print "LINEA RESULTANTE"

	If m = 4 Then
		d1 = (m Shl 5) Or beh
	Else
		d1 = (m Shl 5) Or (c Shl 2) Or d
	End If
	
	d2 = (x Shl 4) Or s
	Print y & ", 0x" & Hex (d1, 2) & ", 0x" & Hex (d2, 2) & ", " 

	If fOut Then Print #fOut, "	" & y & ", 0x" & Hex (d1, 2) & ", 0x" & Hex (d2, 2) & ", "

	Print "------------------------------------"
Loop

If fOut Then Close fOut

