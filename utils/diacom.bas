' dialogue compiler

Sub usage
	Print "$ dialogue_compiler.exe in.txt out.h width [space]"
	Print "Lines are expected to be in the format N|T where N is an"
	Print "hex digit, T is a text."
	Print "<END> marks the end of a dialogue."
	Print "width is the maximum # of characters per line for the word"
	Print "wrapper, max = 30."
	Print "space is code for space, default 32."
End Sub

Dim As Integer tw
Dim As String linea
Dim As Integer character 
Dim As Integer i, j, l, f, x, found
Dim As String m, o
Dim As Integer textsIndex, useThisTextIndex
Dim As String texts (255), curText
Dim As Integer textIndexesUsed (255)
Dim As Integer newDiag, endOfLoop
Dim As String dialogues (255)
Dim As Integer dialoguesIndex
Dim As String spaceCharacter

For i = 0 To 255
	texts (i) = "": dialogues (i) = "": textIndexesUsed (i) = 0
Next i

If Command (4) = "" Then usage: End
tw = Val (Command (3)): If tw = 0 Or tw > 30 Then usage: End

If Command (4) = "" then spaceCharacter = " " Else spaceCharacter = Chr(Val(Command(4)))

? "Reading & parsing " & Command (1)
f = Freefile
Open Command (1) For Input As #f

dialoguesIndex = 0: dialogues (dialoguesIndex) = ""
textsIndex = 0
endOfLoop = 0
Do
	newDiag = 0
	If Eof (f) Then 
		newDiag = -1
		endOfLoop = -1
	Else
		Line Input #1, linea
		If Trim (linea) = "<END>" Then newDiag = -1
	End If

	If newDiag Then
		If dialogues (dialoguesIndex) <> "" Then
			If command (4) = "debug" Then 
				? "DIALOGUE: ";
				For i = 1 To Len (dialogues (dialoguesIndex))
					Print Hex (Asc (Mid (dialogues (dialoguesIndex), i, 1)), 2); " ";
				Next i
				Print
			End If
			dialoguesIndex = dialoguesIndex + 1
			dialogues (dialoguesIndex) = ""
		End If
	Else
		linea = Trim (linea)
		If Len (linea) >= 3 And Left (linea, 1) <> "#" Then
			character = Val ("&H" & Left (linea, 1))
			curText = "": o = "": x = 0
			linea = linea & " "
			For i = 3 To Len (linea)
				m = Mid (linea, i, 1)
				If m = " " Or m = "%" Then
					If x + Len (o) > tw Or m = "%" Then
						curText = curText & "%"
						x = 0
					End If
					curText = curText & o
					x = x + Len (o)
					If i < Len (linea) Then
						If x < tw Then 
							curText = curText & spaceCharacter
							x = x + 1
						Else
							curText = curText & "%"
							x = 0
						End If
					End If
					o = ""
				Else
					o = o & m
				End If
			Next i
			curText = trim (curText)

			' New: Search for duplicate strings and save memory!
			found = 0
			For i = 0 To textsIndex - 1
				If texts (i) = curText Then
					If Command (4) = "debug" Then
						Print "String #" & textsIndex & " is a duplicate of #" & i
					End If
					useThisTextIndex = i
					found = -1
					Exit For
				End If
			Next i
			If Not found Then
				texts (textsIndex) = curText
				useThisTextIndex = textsIndex
				textsIndex = textsIndex + 1
			End If

			If command (4) = "debug" Then
				Print "" & useThisTextIndex & "-> CHR: " & character & " TEXT: " & texts (useThisTextIndex)
			End If			
			dialogues (dialoguesIndex) = dialogues (dialoguesIndex) & Chr (character) & Chr (useThisTextIndex)
		End If
	End If
Loop Until endOfLoop

? "Text lines: " & textsIndex
? "Dialogues: " & dialoguesIndex
? 

Close f

? "Generating code to " & Command (2)

f = Freefile
Open Command (2) For Output As #f

Print #f, "// dialogues.h"
Print #f, "// Generated from " & Command (1) & " by dialogue_compiler.exe"
Print #f, "// Copyleft 2017 by The Mojon Twins"
Print #f, ""

? "Writing dialogues"

For i = 0 To dialoguesIndex - 1
	Print #f, "const unsigned char dialogue_" & Lcase (Hex (i, 2)) & " [] = {"
	Print #f, "	";
	For j = 1 To Len (dialogues (i))
		Print #f, "0x" & Lcase (Hex (Asc (Mid (dialogues (i), j, 1)), 2)) & ", ";
	Next j
	Print #f, "0xff"
	Print #f, "};"
	Print #f, ""
Next i

? "Writing dialogue index"

Print #f, "const unsigned char * const dialogues [] = {"
For i = 0 To dialoguesIndex - 1
	Print #f, "	dialogue_" & Lcase (Hex (i, 2));
	If i < dialoguesIndex - 1 Then Print #f, ", " Else Print #f, ""
Next i
Print #f, "};"
Print #f, ""

? "Writing text lines"

For i = 0 To textsIndex - 1
	Print #f, "const unsigned char text_" & Lcase (Hex (i, 2)) & " [] = """ & texts (i) & """;"
Next i
Print #f, ""

? "Writing text lines index"

Print #f, "const unsigned char * const texts [] = {"
For i = 0 To textsIndex - 1
	Print #f, "	text_" & Lcase (Hex (i, 2));
	If i < textsIndex - 1 Then Print #f, ", " Else Print #f, ""
Next i
Print #f, "};"
Print #f, ""

Close #f

? "DONE!"
