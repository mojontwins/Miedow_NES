#Include "gui.bi"

Dim Shared As Button Button_Add, Button_Close
Dim Shared As TextBox Text_a, Text_b, Text_result


Sub CreateWindow()
'Create Window

	OpenWindow						(250, 200, "Add two numbers")
	Var Label_a = Label_New 		(20, 20, 60, 20, "a:")
	Var Label_b = Label_New 		(20, 50, 60, 20, "b:")
	Button_Add = Button_New 		(120, 80, 60, 20, "Add")
	Var Label_result = Label_New	(20, 110, 60, 20, "a + b:")
	Text_a = TextBox_New			(80, 20, 100, 20, "0")
	Text_b = TextBox_New			(80, 50, 100, 20, "0")
	Text_result = TextBox_New		(80, 110, 100, 20, "0")
	Button_Close = Button_New		(180, 170, 60, 20, "Close")

End Sub


Sub Add()
'Get a and b from textboxes, display a + b:

	Dim As Single a, b, result

	a = Val(TextBox_GetText(Text_a))
	b = Val(TextBox_GetText(Text_b))
	result = a + b
	TextBox_SetText(Text_result, Str(result))

End Sub


'Main:

CreateWindow()

Do
	If TextBox_Event(Text_a) Then TextBox_Edit(Text_a)
	If TextBox_Event(Text_b) Then TextBox_Edit(Text_b)
	If TextBox_Event(Text_result) Then TextBox_Edit(Text_result, 1) 'ReadOnly
	If Button_Event(Button_Add) Then Add()
Loop Until Button_Event(Button_Close) Or Window_Event_Close

End
