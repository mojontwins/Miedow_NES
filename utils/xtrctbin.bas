' Xtractbin
' Extracts X bytes from offset O from binary file
' This probably exists already but I don't care / can't be arsed to search.

' Copyleft 2015 the Mojon Twins

Sub usage
	Print "xtrctbin in.bin out.bin from length"
End Sub

Dim i As Integer, d as uByte

If Len (Command (4)) = 0 Then usage: System
If Val (Command (4)) = 0 Then usage: System
If Str (Val (Command (3))) <> Command (3) Then usage: System

Open Command (1) For Binary as #1
Open Command (2) For Binary as #2

Seek 1, Val (Command (3)) + 1

For i = 1 To Val (Command (4))
	Get #1, , d
	Put #2, , d
Next i

Close 
