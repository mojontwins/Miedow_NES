'' pencompiler.bas

#include "mtparser.bi"

Type LabelType
	name As String * 32
	pos As Integer
End Type

Dim As Integer fIn, fOut
Dim Shared As uByte byteCode (255)
Dim Shared As Integer byteCodeI
Dim As String tokens (15), lineFromFile, myCommand
Dim As Integer op, parm1, parm2, i, ctr
Dim Shared As LabelType labels (15)
Dim Shared As Integer labelI

Sub writeByte (b As uByte)
	byteCode (byteCodeI) = b
	If byteCodeI < 255 Then byteCodeI = byteCodeI + 1
End Sub

Sub addLabel (lname As String)
	Print "Creating Label " & lname & " @ " & Hex (byteCodeI, 2)
	labels (labelI).name = lname
	labels (labelI).pos = bytecodeI
	labelI = labelI + 1
End Sub

Function findPos (lname As String) As Integer
	Dim As Integer res, i

	res = 0
	For i = 0 To labelI - 1
		If lname = labels (i).name Then res = labels (i).pos: Exit For
	Next i

	Return res
End Function

? "Pencompiler v0.2 [comandow edition]"

If Len (Command (2)) = 0 Then
	Print "": Print "usage: "
	Print "$ pencompiler.exe in.spt out.h"
	End
End If

fIn = FreeFile
Open Command (1) For Input As #fIn

byteCodeI = 0: labelI = 0

While Not Eof (fIn) 
	Line Input #fIn, lineFromFile
	parseTokenizeString lineFromFile, tokens (), "", "#"
	myCommand = Trim (Ucase (tokens (0)))

	' Fix tokens
	If Instr ("UPRIGHTDOWNLEFT", Ucase (tokens (1))) Then
		myCommand = myCommand & "_" & Ucase (tokens (1))
		tokens (1) = tokens (2)
	End If

	If myCommand = "" Then Continue While
	
	If Len (myCommand) > 1 And Left (myCommand, 1) = ":" Then
		addLabel Right (myCommand, Len (myCommand) - 1)
		Continue While
	End If

	? Hex (byteCodeI, 2), myCommand, tokens (1),

	Select Case myCommand
		Case "LEFT": 		op = 1: parm1 = 0: parm2 = Val (tokens (1))
		Case "DOWN_LEFT": 	op = 1: parm1 = 1: parm2 = Val (tokens (1))
		Case "DOWN":		op = 1: parm1 = 2: parm2 = Val (tokens (1))
		Case "DOWN_RIGHT":	op = 1: parm1 = 3: parm2 = Val (tokens (1))
		Case "RIGHT":		op = 1: parm1 = 4: parm2 = Val (tokens (1))
		Case "UP_RIGHT":	op = 1: parm1 = 5: parm2 = Val (tokens (1))
		Case "UP":			op = 1: parm1 = 6: parm2 = Val (tokens (1))
		Case "UP_LEFT":		op = 1: parm1 = 7: parm2 = Val (tokens (1))

		Case "IDLE":		op = 0: parm1 = 1: parm2 = Val (tokens (1))

		Case "FIRE":		
			op = 2: parm1 = 0
			parm2 = 0
			If Instr ("PLAYER1", Ucase (tokens (1))) Then parm2 = 2

		Case "RETURN":
			op = 3
			parm1 = byteCodeI - findPos (tokens (1))

		Case Else:			op = 0: parm1 = 0: parm2 = 0
	End Select

	' Build
	
	If op < 3 Then 
		Print Bin ((op Shl 6) Or (parm1 Shl 3) Or parm2, 8), Hex ((op Shl 6) Or (parm1 Shl 3) Or parm2, 2)
		writeByte (op Shl 6) Or (parm1 Shl 3) Or parm2
	Else
	'?op,parm1
		Print Bin ((op Shl 6) Or parm1, 8), Hex ((op Shl 6) Or parm1, 2) , "-> " & Hex (byteCodeI - parm1, 2)
		writeByte (op Shl 6) Or parm1
	End If
Wend

writeByte 0

Close #fIn

' Write back
fOut = FreeFile
Open Command (2) For Output As #fOut

ctr = 0
Print #fOut, "const unsigned char behaviour [] = {"
Print #fOut, "	";
For i = 0 To byteCodeI - 1
	print #fOut, "0x" & Lcase (Hex (byteCode (i), 2));
	If i < byteCodeI - 1 Then Print #fOut, ", ";
	ctr = ctr + 1: If ctr = 16 Then ctr = 0: Print #fOut, "": Print #fOut, "	";
Next i 
Print #fOut, ""
Print #fOut, "};"

Close fOut
