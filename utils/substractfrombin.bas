' Substract from bin

Sub usage
	Print "substractfrombin in out amount"
End Sub

Dim As Integer amount
Dim As uByte d

If Command (3) = "" Then usage: End

amount = Val (Command (3))

Open Command (1) For Binary As #1
Open Command (2) For Binary As #2

While Not Eof (1)
	Get #1, , d
	d = d - amount
	Put #2, , d
Wend

Close #1, #2
