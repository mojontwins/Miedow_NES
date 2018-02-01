' Write With Font 1.0

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

#include "cmdlineparser.bi"

#define RGBA_R( c ) ( CUInt( c ) Shr 16 And 255 )
#define RGBA_G( c ) ( CUInt( c ) Shr  8 And 255 )
#define RGBA_B( c ) ( CUInt( c )        And 255 )
#define RGBA_A( c ) ( CUInt( c ) Shr 24         )

Sub usage
	Print "$ writewithfont.exe font.png text.txt out.png"
	Print ""
	Print "Writes a PNG file you can feed to mkts afterwards."
	Print "Output will be 256 pixels wide to make things easier [for me]"
	Print "font.png must be a 256x32 pixels image with chars with ASCII 32-95"
	Print "text.txt must contains lines <= 32 chars long."
	Print "out.png will be generated after some magic process takes place."
End Sub

Sub copyChar (fontImg As Any Ptr, outImg As Any Ptr, ascii As uByte, x as uByte, y as uByte)
	Dim As uByte srcX, srcY
	
	If ascii < 32 Or ascii > 95 Then Exit Sub
	
	srcX = 8 * ((ascii - 32) And 31)
	srcY = 8 * ((ascii - 32) \ 32)
	
	Put outImg, (x, y), fontImg, (srcX, srcY) - (7 + srcX, 7 + srcY), Pset
End Sub

Dim As Any Ptr fontImg, outImg
Dim As String lines (255)
Dim As Integer textIndex, fIn, maxLength, i, j, x, y
Dim As String lineFromFile

If Command (3) = "" Then usage: End

screenres 640, 480, 32, , -1

Puts "Reading font from " & Command (1)
fontImg = png_load (Command (1))

Puts "Reading text from " & Command (2)
fIn = FreeFile
Open Command (2) For Input As #fIn
maxLength = 1
textIndex = 0: While Not Eof (fIn)
	Line Input #fIn, lineFromFile
	If Len (lineFromFile) > 32 Then lineFromFile = Left(lineFromFile, 32): Puts "WARNING! Had to trim line #" & (textIndex + 1)
	If maxLength < Len (lineFromFile) Then maxLength = Len (lineFromFile)
	lines (textIndex) = lineFromFile: textIndex = textIndex + 1
Wend
Close #fIn

Puts "   " & textIndex & " lines read."
Puts "   Max. line length is " & maxLength & "."
maxLength = maxLength + 1
Puts "Creating output image (" & (8*maxLength) & "x" & (8*textIndex) & ")."

outImg = ImageCreate (8 * maxLength, 8 * textIndex, RGB (0, 0, 0))

Puts "Converting text..."

y = 0
For i = 0 To textIndex - 1
	x = 0
	For j = 1 To Len (lines (i))
		copyChar fontImg, outImg, Asc (Mid (lines (i), j, 1)), x, y
		x = x + 8
	Next j
	Line outImg, (x, y) - (7 + x, 7 + y), RGB (255, 0, 0), BF
	y = y + 8
Next i

Puts "Saving image..."
png_save (Command (3), outImg)

Puts "DONE"
