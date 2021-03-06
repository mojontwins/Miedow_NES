;this file for FamiTone2 library generated by text2data tool

miedow_music_data:
	.byte 8
	.word @instruments
	.word @samples-3
	.word @song0ch0,@song0ch1,@song0ch2,@song0ch3,@song0ch4,307,256
	.word @song1ch0,@song1ch1,@song1ch2,@song1ch3,@song1ch4,307,256
	.word @song2ch0,@song2ch1,@song2ch2,@song2ch3,@song2ch4,307,256
	.word @song3ch0,@song3ch1,@song3ch2,@song3ch3,@song3ch4,307,256
	.word @song4ch0,@song4ch1,@song4ch2,@song4ch3,@song4ch4,307,256
	.word @song5ch0,@song5ch1,@song5ch2,@song5ch3,@song5ch4,307,256
	.word @song6ch0,@song6ch1,@song6ch2,@song6ch3,@song6ch4,307,256
	.word @song7ch0,@song7ch1,@song7ch2,@song7ch3,@song7ch4,307,256

@instruments:
	.byte $30 ;instrument $00
	.word @env2,@env0,@env0
	.byte $00
	.byte $30 ;instrument $01
	.word @env1,@env0,@env0
	.byte $00
	.byte $30 ;instrument $02
	.word @env3,@env18,@env0
	.byte $00
	.byte $30 ;instrument $04
	.word @env10,@env21,@env0
	.byte $00
	.byte $30 ;instrument $05
	.word @env16,@env0,@env0
	.byte $00
	.byte $30 ;instrument $06
	.word @env12,@env0,@env0
	.byte $00
	.byte $b0 ;instrument $07
	.word @env7,@env0,@env0
	.byte $00
	.byte $30 ;instrument $08
	.word @env13,@env0,@env0
	.byte $00
	.byte $b0 ;instrument $09
	.word @env8,@env0,@env0
	.byte $00
	.byte $30 ;instrument $0a
	.word @env4,@env0,@env0
	.byte $00
	.byte $b0 ;instrument $0b
	.word @env5,@env0,@env0
	.byte $00
	.byte $b0 ;instrument $0c
	.word @env6,@env0,@env0
	.byte $00
	.byte $b0 ;instrument $0d
	.word @env9,@env17,@env0
	.byte $00
	.byte $30 ;instrument $0e
	.word @env3,@env19,@env0
	.byte $00
	.byte $b0 ;instrument $11
	.word @env11,@env20,@env0
	.byte $00
	.byte $b0 ;instrument $12
	.word @env14,@env0,@env0
	.byte $00
	.byte $b0 ;instrument $13
	.word @env15,@env0,@env0
	.byte $00
	.byte $b0 ;instrument $3f
	.word @env1,@env17,@env0
	.byte $00

@samples:
@env0:
	.byte $c0,$00,$00
@env1:
	.byte $c1,$c2,$c3,$c5,$00,$03
@env2:
	.byte $cf,$00,$00
@env3:
	.byte $c3,$c4,$c7,$c7,$c6,$c5,$c4,$c4,$c3,$06,$c3,$00,$0a
@env4:
	.byte $c9,$c8,$c7,$c6,$c5,$c4,$c3,$c2,$c0,$00,$08
@env5:
	.byte $cf,$ce,$cd,$cb,$ca,$c9,$c8,$c7,$c6,$c5,$03,$c4,$03,$c3,$03,$c2
	.byte $04,$c1,$03,$c0,$00,$13
@env6:
	.byte $c4,$c6,$c7,$c8,$c8,$c7,$c6,$02,$c5,$02,$c4,$02,$c4,$00,$0c
@env7:
	.byte $cf,$cb,$c9,$c7,$c5,$c4,$c3,$c3,$c2,$02,$c1,$c1,$c0,$00,$0c
@env8:
	.byte $ce,$cc,$ca,$c9,$c8,$c8,$c7,$c6,$c6,$c5,$c5,$ca,$c7,$c7,$c6,$c6
	.byte $c5,$c5,$c4,$c4,$c3,$c3,$c2,$03,$c1,$05,$c0,$00,$1a
@env9:
	.byte $c2,$c3,$c5,$c6,$c7,$c8,$c9,$03,$c8,$c6,$c5,$02,$c5,$00,$0c
@env10:
	.byte $cd,$cb,$c9,$c7,$c5,$c4,$c2,$c1,$c0,$00,$08
@env11:
	.byte $c7,$c6,$c5,$c5,$c4,$c4,$c3,$04,$c2,$0b,$c1,$0e,$c0,$00,$0c
@env12:
	.byte $ca,$c5,$c3,$c2,$c0,$00,$04
@env13:
	.byte $cf,$cf,$ce,$ce,$cd,$cb,$c6,$c5,$c3,$c3,$c2,$04,$c2,$00,$0c
@env14:
	.byte $c2,$c5,$c6,$c7,$c8,$05,$c7,$c6,$c5,$02,$c5,$00,$0a
@env15:
	.byte $cf,$cd,$cb,$ca,$c9,$c8,$c8,$c7,$c6,$02,$c5,$02,$c4,$c4,$cc,$c9
	.byte $c8,$c7,$c7,$c6,$c6,$c5,$c5,$c4,$02,$c3,$03,$c9,$c7,$c6,$c5,$c5
	.byte $c4,$c4,$c3,$03,$c2,$02,$c1,$c5,$c4,$c3,$c3,$c2,$03,$c1,$03,$c1
	.byte $00,$2f
@env16:
	.byte $cf,$cc,$c8,$c7,$c4,$c3,$c2,$c1,$c0,$00,$08
@env17:
	.byte $c0,$cc,$cc,$c0,$00,$03
@env18:
	.byte $c0,$c4,$c7,$cc,$00,$00
@env19:
	.byte $bb,$c0,$c3,$c7,$00,$00
@env20:
	.byte $c0,$c3,$c7,$00,$00
@env21:
	.byte $c7,$c3,$c0,$bd,$00,$02


@song0ch0:
	.byte $fb,$0e
@song0ch0loop:
@ref0:
	.byte $9c,$3a,$00,$83,$3b,$01,$3a,$00,$83,$3b,$01,$3a,$00,$83,$3b,$01
	.byte $3a,$00,$83,$3b,$00,$81
@ref1:
	.byte $3a,$00,$83,$3b,$01,$3a,$00,$83,$3b,$01,$3a,$00,$83,$3b,$01,$3a
	.byte $00,$83,$3b,$00,$81
	.byte $ff,$15
	.word @ref1
	.byte $ff,$15
	.word @ref1
@ref4:
	.byte $3a,$00,$83,$3b,$92,$26,$28,$9c,$3a,$00,$83,$3b,$92,$26,$28,$9c
	.byte $3a,$00,$83,$3b,$01,$3a,$92,$30,$28,$22,$9c,$3a,$92,$28,$26,$22
@ref5:
	.byte $9c,$3a,$00,$83,$3b,$01,$3a,$00,$83,$3b,$01,$3a,$92,$28,$26,$22
	.byte $9c,$3b,$01,$3a,$00,$92,$1b,$9c,$3b,$00,$81
	.byte $ff,$15
	.word @ref1
	.byte $ff,$15
	.word @ref1
	.byte $ff,$15
	.word @ref1
	.byte $ff,$15
	.word @ref1
@ref10:
	.byte $3a,$00,$8c,$40,$3e,$9c,$3b,$01,$3a,$00,$8c,$48,$40,$9c,$3b,$01
	.byte $3a,$00,$8c,$3f,$9c,$3b,$8c,$33,$9c,$3a,$00,$83,$3b,$00,$81
@ref11:
	.byte $3a,$00,$8c,$48,$32,$9c,$3b,$01,$3a,$00,$8c,$40,$44,$9c,$3b,$00
	.byte $8c,$3a,$9c,$3a,$00,$83,$3b,$8c,$3f,$9c,$3a,$00,$8c,$40,$3e,$9c
	.byte $3b,$00,$81
	.byte $ff,$15
	.word @ref1
	.byte $ff,$15
	.word @ref1
	.byte $ff,$15
	.word @ref1
	.byte $ff,$15
	.word @ref1
@ref16:
	.byte $00,$8d
@ref17:
	.byte $8f
	.byte $ff,$17
	.word @ref10
	.byte $ff,$19
	.word @ref11
	.byte $fd
	.word @song0ch0loop

@song0ch1:
@song0ch1loop:
@ref20:
	.byte $bf
@ref21:
	.byte $bf
@ref22:
	.byte $98,$3a,$85,$01,$3e,$40,$3a,$85,$01,$3e,$40,$48,$85,$00,$85,$4a
	.byte $48,$40,$3a,$3e,$40,$3e,$3a
@ref23:
	.byte $48,$85,$00,$85,$40,$83,$00,$3a,$83,$00,$3e,$40,$3e,$3a,$85,$00
	.byte $31,$33,$28,$83,$00
@ref24:
	.byte $3a,$85,$01,$3e,$40,$3a,$85,$01,$3e,$40,$48,$85,$00,$85,$4a,$48
	.byte $40,$3a,$3e,$40,$3e,$3a
	.byte $ff,$15
	.word @ref23
@ref26:
	.byte $bf
@ref27:
	.byte $bf
@ref28:
	.byte $8c,$52,$00,$58,$56,$53,$01,$52,$00,$60,$58,$6b,$01,$71,$6f,$69
	.byte $63,$60,$85,$00,$85
@ref29:
	.byte $63,$60,$62,$61,$01,$5d,$58,$5c,$59,$00,$52,$56,$85,$01,$57,$53
	.byte $58,$56,$52,$85
@ref30:
	.byte $90,$53,$58,$56,$52,$85,$53,$60,$58,$6a,$85,$71,$6f,$69,$63,$60
	.byte $8d
@ref31:
	.byte $63,$60,$62,$60,$85,$5d,$58,$5c,$58,$83,$52,$56,$89,$57,$53,$58
	.byte $56,$52,$83,$00
	.byte $ff,$16
	.word @ref22
	.byte $ff,$15
	.word @ref23
@ref34:
	.byte $96,$3a,$8d,$30,$85,$32,$85,$28,$26,$24,$22,$21,$19,$22,$8d
@ref35:
	.byte $98,$3b,$41,$3b,$41,$3a,$3c,$3e,$40,$3b,$41,$49,$4b,$49,$4f,$4a
	.byte $85,$48,$85
@ref36:
	.byte $96,$3a,$85,$40,$85
@ref37:
	.byte $38,$85,$3a,$85
	.byte $ff,$10
	.word @ref30
	.byte $ff,$14
	.word @ref31
	.byte $fd
	.word @song0ch1loop

@song0ch2:
@song0ch2loop:
@ref40:
	.byte $80,$3a,$30,$28,$30,$3a,$30,$28,$30,$3a,$30,$28,$30,$3a,$30,$28
	.byte $30,$3a,$30,$28,$30,$3a,$30,$28,$30,$3a,$30,$28,$30,$3a,$30,$28
	.byte $30
@ref41:
	.byte $3a,$30,$28,$30,$3a,$30,$28,$30,$3a,$30,$28,$30,$3a,$30,$28,$30
	.byte $3a,$30,$28,$30,$3a,$30,$28,$30,$3a,$30,$28,$30,$3a,$30,$28,$30
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
@ref56:
	.byte $00,$8d
@ref57:
	.byte $8f
	.byte $ff,$20
	.word @ref41
	.byte $ff,$20
	.word @ref41
	.byte $fd
	.word @song0ch2loop

@song0ch3:
@song0ch3loop:
@ref60:
	.byte $88,$02,$85,$86,$12,$83,$12,$88,$03,$03,$86,$12,$85,$88,$02,$85
	.byte $86,$12,$83,$12,$88,$03,$03,$86,$12,$85
@ref61:
	.byte $88,$02,$85,$86,$12,$83,$12,$88,$03,$03,$86,$12,$85,$88,$02,$85
	.byte $86,$12,$83,$12,$88,$03,$03,$86,$13,$88,$02,$02
@ref62:
	.byte $02,$85,$86,$12,$83,$12,$88,$03,$03,$86,$12,$85,$88,$02,$85,$86
	.byte $12,$83,$12,$88,$03,$03,$86,$12,$85
	.byte $ff,$13
	.word @ref61
	.byte $ff,$12
	.word @ref62
	.byte $ff,$13
	.word @ref61
	.byte $ff,$12
	.word @ref62
	.byte $ff,$13
	.word @ref61
	.byte $ff,$12
	.word @ref62
	.byte $ff,$13
	.word @ref61
	.byte $ff,$12
	.word @ref62
	.byte $ff,$13
	.word @ref61
	.byte $ff,$12
	.word @ref62
	.byte $ff,$13
	.word @ref61
	.byte $ff,$12
	.word @ref62
	.byte $ff,$13
	.word @ref61
@ref76:
	.byte $8f
@ref77:
	.byte $8f
	.byte $ff,$12
	.word @ref62
	.byte $ff,$13
	.word @ref61
	.byte $fd
	.word @song0ch3loop

@song0ch4:
@song0ch4loop:
@ref80:
	.byte $bf
@ref81:
	.byte $bf
@ref82:
	.byte $bf
@ref83:
	.byte $bf
@ref84:
	.byte $bf
@ref85:
	.byte $bf
@ref86:
	.byte $bf
@ref87:
	.byte $bf
@ref88:
	.byte $bf
@ref89:
	.byte $bf
@ref90:
	.byte $bf
@ref91:
	.byte $bf
@ref92:
	.byte $bf
@ref93:
	.byte $bf
@ref94:
	.byte $bf
@ref95:
	.byte $bf
@ref96:
	.byte $8f
@ref97:
	.byte $8f
@ref98:
	.byte $bf
@ref99:
	.byte $bf
	.byte $fd
	.word @song0ch4loop


@song1ch0:
	.byte $fb,$14
@song1ch0loop:
@ref100:
	.byte $96,$32,$85,$41,$32,$85,$41,$40,$85,$4b,$3a,$95
@ref101:
	.byte $32,$85,$41,$32,$85,$41,$40,$85,$4b,$3a,$95
@ref102:
	.byte $97
	.byte $ff,$0b
	.word @ref101
	.byte $ff,$0b
	.word @ref101
	.byte $ff,$0b
	.word @ref101
@ref106:
	.byte $40,$93,$00
@ref107:
	.byte $97
@ref108:
	.byte $9e,$32,$89,$36,$89,$40,$89,$3c,$89,$36,$89,$36,$89,$32,$89,$32
	.byte $89
@ref109:
	.byte $32,$89,$36,$89,$40,$89,$3c,$89,$36,$89,$36,$89,$32,$89,$32,$89
@ref110:
	.byte $94,$32,$85,$3a,$44,$3d,$49,$4f,$4a,$4a,$4a,$4a,$48,$44,$5d,$53
	.byte $4b,$55,$5d,$58,$54,$53,$61,$5c,$58,$53,$59,$5c,$60,$61,$5b,$52
	.byte $81
@ref111:
	.byte $52,$83,$53,$52,$48,$4e,$54,$60,$54,$4e,$58,$52,$58,$4a,$58,$40
	.byte $52,$83,$53,$52,$55,$5d,$58,$54,$53,$61,$5c,$58,$53,$59,$5c,$60
	.byte $61,$5b,$52,$81
@ref112:
	.byte $9e,$32,$83,$94,$53,$52,$9e,$36,$83,$94,$59,$58,$9e,$40,$83,$94
	.byte $4f,$4e,$9e,$3c,$83,$94,$4b,$4a,$9e,$36,$83,$94,$59,$54,$9e,$36
	.byte $83,$94,$55,$54,$9e,$32,$83,$94,$55,$4a,$9e,$32,$83,$94,$4b,$4a
	.byte $ff,$20
	.word @ref112
	.byte $fd
	.word @song1ch0loop

@song1ch1:
@song1ch1loop:
@ref114:
	.byte $00,$85,$96,$37,$3a,$85,$4b,$4e,$89,$48,$95
@ref115:
	.byte $00,$85,$37,$3a,$85,$4b,$4e,$89,$48,$95
@ref116:
	.byte $97
	.byte $ff,$0a
	.word @ref115
@ref118:
	.byte $00,$85,$37,$3a,$85,$4b,$4e,$85,$4b,$48,$95
	.byte $ff,$0b
	.word @ref118
@ref120:
	.byte $4a,$93,$00
@ref121:
	.byte $97
@ref122:
	.byte $9e,$3a,$85,$3d,$40,$85,$45,$48,$89,$44,$89,$40,$89,$3c,$89,$3c
	.byte $89,$3a,$89
@ref123:
	.byte $3a,$85,$3d,$40,$85,$45,$48,$89,$44,$89,$40,$89,$3c,$89,$3c,$89
	.byte $3a,$89
@ref124:
	.byte $22,$85,$2d,$1e,$85,$31,$28,$89,$2c,$89,$2c,$85,$25,$28,$85,$1f
	.byte $22,$85,$29,$2a,$85,$30,$81
	.byte $ff,$17
	.word @ref124
	.byte $ff,$12
	.word @ref123
	.byte $ff,$12
	.word @ref123
	.byte $fd
	.word @song1ch1loop

@song1ch2:
@song1ch2loop:
@ref128:
	.byte $80,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30
	.byte $32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32
@ref129:
	.byte $30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32
	.byte $30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32,$30,$32
	.byte $ff,$0c
	.word @ref129
@ref131:
	.byte $94,$32,$85,$41,$32,$85,$41,$40,$85,$33,$3a,$95
	.byte $ff,$1e
	.word @ref128
	.byte $ff,$1e
	.word @ref129
@ref134:
	.byte $96,$32,$95
	.byte $ff,$0c
	.word @ref128
@ref136:
	.byte $28,$32,$3a,$40,$4a,$3a,$40,$48,$4e,$58,$4e,$48,$40,$48,$4e,$48
	.byte $40,$36,$32,$3c,$44,$3c,$4a,$44,$40,$36,$40,$30,$36,$40,$3c,$36
	.byte $44,$3c,$4e,$44,$3c,$32,$44,$3c,$4a,$44,$3a,$32,$44,$3a,$4a,$44
@ref137:
	.byte $32,$28,$3a,$32,$4a,$40,$36,$30,$40,$36,$4e,$48,$40,$36,$48,$40
	.byte $4e,$58,$54,$4a,$44,$3c,$32,$2c,$40,$36,$40,$30,$36,$40,$3c,$36
	.byte $44,$3c,$4e,$44,$3c,$32,$44,$3c,$4a,$44,$3a,$32,$44,$3a,$4a,$44
@ref138:
	.byte $44,$3a,$4a,$44,$52,$4a,$48,$3c,$4e,$48,$54,$4e,$4a,$40,$52,$4a
	.byte $58,$52,$44,$3a,$4a,$44,$52,$4a,$5c,$58,$54,$52,$4e,$4a,$48,$4a
	.byte $4e,$52,$54,$58,$52,$4a,$58,$52,$62,$58,$52,$48,$5a,$52,$60,$5a
@ref139:
	.byte $52,$5c,$52,$5c,$62,$6a,$78,$6c,$66,$60,$66,$6c,$70,$6a,$62,$58
	.byte $62,$6a,$5c,$62,$6a,$62,$5c,$62,$5c,$62,$6c,$62,$5c,$62,$60,$66
	.byte $70,$66,$60,$66,$6a,$62,$5c,$62,$60,$5c,$5a,$60,$6a,$60,$72,$6a
	.byte $ff,$30
	.word @ref136
	.byte $ff,$30
	.word @ref137
	.byte $fd
	.word @song1ch2loop

@song1ch3:
@song1ch3loop:
@ref142:
	.byte $88,$02,$8a,$16,$86,$18,$8a,$16,$8e,$1a,$86,$18,$88,$02,$8a,$16
	.byte $86,$18,$8a,$16,$8e,$1a,$86,$18,$88,$02,$8a,$16,$86,$18,$8a,$16
	.byte $8e,$1a,$86,$18,$88,$02,$8a,$16,$86,$18,$8a,$16,$8e,$1a,$86,$18
	.byte $88,$02,$8a,$16,$86,$18,$8a,$16,$86,$02,$02
	.byte $ff,$1e
	.word @ref142
@ref144:
	.byte $88,$02,$8a,$16,$86,$18,$8a,$16,$8e,$1a,$86,$18,$88,$02,$8a,$16
	.byte $86,$18,$8a,$16,$86,$02,$02
	.byte $ff,$1e
	.word @ref142
	.byte $ff,$1e
	.word @ref142
	.byte $ff,$1e
	.word @ref142
	.byte $ff,$0c
	.word @ref144
	.byte $ff,$0c
	.word @ref144
@ref150:
	.byte $88,$02,$8a,$16,$86,$18,$8a,$16,$8e,$1a,$86,$18,$88,$02,$8a,$16
	.byte $86,$18,$8a,$16,$8e,$1a,$86,$18,$88,$02,$8a,$16,$86,$18,$8a,$16
	.byte $8e,$1a,$86,$18,$88,$02,$8a,$16,$86,$18,$8a,$16,$8e,$1a,$86,$18
	.byte $88,$02,$8a,$16,$86,$18,$8a,$16,$86,$02,$02,$88,$02,$8a,$16,$86
	.byte $18,$8a,$16,$8e,$1a,$86,$18,$88,$02,$8a,$16,$86,$18,$8a,$16,$8e
	.byte $1a,$86,$18,$88,$02,$8a,$16,$86,$18,$8a,$16,$86,$02,$02
	.byte $ff,$30
	.word @ref150
	.byte $ff,$30
	.word @ref150
	.byte $ff,$30
	.word @ref150
	.byte $ff,$30
	.word @ref150
	.byte $ff,$30
	.word @ref150
	.byte $fd
	.word @song1ch3loop

@song1ch4:
@song1ch4loop:
@ref156:
	.byte $bb
@ref157:
	.byte $bb
@ref158:
	.byte $97
@ref159:
	.byte $bb
@ref160:
	.byte $bb
@ref161:
	.byte $bb
@ref162:
	.byte $97
@ref163:
	.byte $97
@ref164:
	.byte $df
@ref165:
	.byte $df
@ref166:
	.byte $df
@ref167:
	.byte $df
@ref168:
	.byte $df
@ref169:
	.byte $df
	.byte $fd
	.word @song1ch4loop


@song2ch0:
	.byte $fb,$0e
@ref170:
	.byte $94,$32,$36,$3a,$45,$40,$40,$3c,$32,$36,$38,$43,$40,$40,$38,$30
	.byte $32,$36,$3d,$38,$38,$36,$32,$85,$4a,$4a,$4a,$81
@song2ch0loop:
@ref171:
	.byte $9e,$32,$36,$3a,$45,$40,$40,$3c,$32,$36,$38,$43,$40,$40,$38,$30
	.byte $32,$36,$3d,$38,$38,$36,$32,$85,$4a,$4a,$4a,$81
@ref172:
	.byte $32,$36,$3a,$45,$40,$40,$3c,$32,$36,$38,$43,$40,$40,$38,$30,$32
	.byte $36,$3d,$38,$38,$36,$32,$85,$4a,$4a,$4a,$81
@ref173:
	.byte $00,$bd
@ref174:
	.byte $96,$32,$8d,$32,$8d,$32,$8d,$32,$8d
@ref175:
	.byte $9e,$4a,$4a,$00,$4a,$50,$4a,$00,$4a,$40,$42,$48,$4a,$48,$42,$40
	.byte $3c,$40,$40,$00,$32,$40,$40,$00,$40,$3c,$40,$3c,$38,$36,$38,$36
	.byte $32
@ref176:
	.byte $4a,$4a,$00,$4a,$50,$4a,$00,$4a,$40,$42,$48,$4a,$48,$42,$40,$3c
	.byte $40,$40,$00,$32,$40,$40,$00,$40,$3c,$40,$3c,$38,$36,$38,$36,$32
@ref177:
	.byte $4a,$4a,$00,$4a,$50,$4a,$00,$4a,$40,$42,$48,$4a,$48,$42,$40,$3c
	.byte $40,$40,$40,$40,$42,$48,$4a,$4e,$50,$54,$58,$54,$4a,$00,$54,$54
@ref178:
	.byte $50,$50,$00,$50,$54,$50,$00,$50,$4e,$50,$4e,$4a,$48,$42,$40,$3c
	.byte $40,$40,$00,$32,$40,$40,$00,$40,$3c,$40,$3c,$38,$36,$38,$36,$30
@ref179:
	.byte $96,$38,$38,$00,$38,$38,$38,$00,$38,$36,$36,$00,$36,$36,$36,$00
	.byte $36,$32,$32,$00,$40,$32,$32,$01,$9e,$40,$42,$48,$4a,$48,$42,$40
	.byte $3c
	.byte $ff,$1b
	.word @ref170
	.byte $ff,$1b
	.word @ref172
@ref182:
	.byte $32,$38,$40,$4b,$68,$62,$5a,$58,$50,$4a,$40,$00,$40,$3e,$40,$3c
	.byte $42,$48,$4a,$50,$4a,$48,$42,$40,$42,$40,$42,$40,$42,$48,$42
@ref183:
	.byte $32,$38,$40,$4b,$68,$62,$5a,$58,$50,$4a,$40,$00,$40,$3e,$40,$3c
	.byte $42,$48,$4a,$50,$58,$62,$68,$58,$5a,$58,$5a,$58,$54,$50,$4e
	.byte $ff,$20
	.word @ref175
	.byte $ff,$20
	.word @ref176
	.byte $ff,$20
	.word @ref177
	.byte $ff,$20
	.word @ref178
	.byte $ff,$1f
	.word @ref179
	.byte $fd
	.word @song2ch0loop

@song2ch1:
@ref189:
	.byte $00,$b9,$94,$62,$81
@song2ch1loop:
@ref190:
	.byte $8c,$52,$54,$52,$5d,$58,$58,$54,$4a,$4e,$50,$5b,$58,$58,$5a,$4e
	.byte $50,$4e,$55,$50,$50,$4e,$4a,$85,$62,$62,$62,$58
@ref191:
	.byte $52,$54,$52,$5d,$58,$58,$54,$4a,$4e,$50,$5b,$58,$58,$5a,$4e,$50
	.byte $4e,$55,$50,$50,$4e,$4a,$85,$62,$62,$62,$58
@ref192:
	.byte $00,$bd
@ref193:
	.byte $96,$38,$8d,$48,$8d,$40,$8d,$3c,$8d
@ref194:
	.byte $38,$8d,$48,$8d,$40,$8d,$3c,$8d
	.byte $ff,$08
	.word @ref194
	.byte $ff,$08
	.word @ref194
	.byte $ff,$08
	.word @ref194
@ref198:
	.byte $32,$8d,$30,$8d,$32,$8b,$00,$8f
	.byte $ff,$1b
	.word @ref190
	.byte $ff,$1b
	.word @ref191
@ref201:
	.byte $96,$32,$8d,$38,$8d,$36,$8d,$32,$8d
@ref202:
	.byte $32,$8d,$38,$8d,$36,$8d,$32,$85,$40,$3c,$38,$36
	.byte $ff,$08
	.word @ref194
	.byte $ff,$08
	.word @ref194
	.byte $ff,$08
	.word @ref194
	.byte $ff,$08
	.word @ref194
	.byte $ff,$08
	.word @ref198
	.byte $fd
	.word @song2ch1loop

@song2ch2:
@ref208:
	.byte $00,$bd
@song2ch2loop:
@ref209:
	.byte $8c,$1a,$1a,$28,$1a,$00,$28,$22,$1a,$1a,$1a,$20,$1a,$00,$20,$28
	.byte $20,$18,$18,$1e,$18,$00,$20,$18,$1e,$1a,$00,$83,$1a,$00,$1a,$00
@ref210:
	.byte $1a,$1a,$28,$1a,$00,$28,$22,$1a,$1a,$1a,$20,$1a,$00,$20,$28,$20
	.byte $18,$18,$1e,$18,$00,$20,$18,$1e,$1a,$00,$83,$1a,$00,$1a,$00
@ref211:
	.byte $1a,$85,$88,$18,$1a,$20,$1e,$8c,$1a,$85,$88,$28,$24,$20,$1e,$8c
	.byte $1a,$85,$88,$18,$1a,$20,$28,$8c,$24,$85,$88,$24,$20,$1e,$1a
@ref212:
	.byte $8c,$1a,$85,$88,$18,$1a,$20,$1e,$8c,$1a,$85,$88,$28,$24,$20,$1e
	.byte $8c,$1a,$85,$88,$18,$1a,$20,$28,$8c,$24,$85,$88,$24,$20,$1e,$1a
	.byte $ff,$18
	.word @ref212
	.byte $ff,$18
	.word @ref212
	.byte $ff,$18
	.word @ref212
	.byte $ff,$18
	.word @ref212
@ref217:
	.byte $1a,$1a,$1a,$1a,$1a,$1a,$1a,$1a,$1e,$1e,$1e,$1e,$1e,$1e,$1e,$1e
	.byte $20,$20,$20,$20,$1a,$1a,$1a,$1a,$28,$2a,$30,$32,$30,$2a,$28,$00
	.byte $ff,$1f
	.word @ref209
	.byte $ff,$1f
	.word @ref210
@ref220:
	.byte $88,$1a,$1a,$10,$1a,$00,$20,$20,$20,$1a,$1a,$10,$1a,$00,$1a,$1a
	.byte $1a,$28,$28,$1e,$28,$00,$1e,$1e,$1e,$1a,$1a,$1a,$1a,$1a,$28,$30
	.byte $28
@ref221:
	.byte $1a,$1a,$10,$1a,$00,$20,$20,$20,$1a,$1a,$10,$1a,$00,$1a,$1a,$1a
	.byte $28,$28,$1e,$28,$00,$1e,$1e,$1e,$1a,$1a,$1a,$1a,$96,$28,$24,$20
	.byte $1e
	.byte $ff,$18
	.word @ref212
	.byte $ff,$18
	.word @ref212
	.byte $ff,$18
	.word @ref212
	.byte $ff,$18
	.word @ref212
	.byte $ff,$20
	.word @ref217
	.byte $fd
	.word @song2ch2loop

@song2ch3:
@ref227:
	.byte $00,$bd
@song2ch3loop:
@ref228:
	.byte $88,$02,$8e,$1e,$88,$10,$03,$8e,$1e,$88,$10,$8e,$1e,$88,$02,$8e
	.byte $1e,$88,$10,$03,$8e,$1e,$88,$10,$8e,$1e,$88,$02,$8e,$1e,$88,$10
	.byte $03,$8e,$1e,$88,$10,$8e,$1e,$88,$02,$8e,$1e,$88,$10,$8e,$1e,$88
	.byte $02,$02,$10,$8e,$1e
	.byte $ff,$1d
	.word @ref228
@ref230:
	.byte $88,$02,$02,$10,$8e,$1e,$88,$02,$02,$10,$8e,$1e,$88,$02,$02,$10
	.byte $8e,$1e,$88,$02,$8e,$1e,$88,$10,$8e,$1e,$88,$02,$02,$10,$8e,$1e
	.byte $88,$02,$02,$10,$8e,$1e,$88,$02,$02,$10,$8e,$1e,$88,$02,$8e,$1e
	.byte $88,$10,$8e,$1e
	.byte $ff,$20
	.word @ref230
	.byte $ff,$20
	.word @ref230
	.byte $ff,$20
	.word @ref230
	.byte $ff,$20
	.word @ref230
	.byte $ff,$20
	.word @ref230
@ref236:
	.byte $88,$02,$02,$10,$8e,$1e,$88,$02,$02,$10,$8e,$1e,$88,$02,$02,$10
	.byte $8e,$1e,$88,$02,$8e,$1e,$88,$10,$8e,$1e,$88,$02,$02,$10,$8e,$1e
	.byte $88,$02,$02,$10,$8e,$1e,$88,$02,$8d
@ref237:
	.byte $02,$8e,$1e,$88,$10,$03,$8e,$1e,$88,$10,$8e,$1e,$88,$02,$8e,$1e
	.byte $88,$10,$03,$8e,$1e,$88,$10,$8e,$1e,$88,$02,$8e,$1e,$88,$10,$03
	.byte $8e,$1e,$88,$10,$8e,$1e,$88,$02,$8e,$1e,$88,$10,$8e,$1e,$88,$02
	.byte $02,$10,$8e,$1e
	.byte $ff,$1d
	.word @ref228
	.byte $ff,$20
	.word @ref230
	.byte $ff,$20
	.word @ref230
	.byte $ff,$20
	.word @ref230
	.byte $ff,$20
	.word @ref230
	.byte $ff,$20
	.word @ref230
	.byte $ff,$20
	.word @ref230
	.byte $ff,$1a
	.word @ref236
	.byte $fd
	.word @song2ch3loop

@song2ch4:
@ref246:
	.byte $bf
@song2ch4loop:
@ref247:
	.byte $bf
@ref248:
	.byte $bf
@ref249:
	.byte $bf
@ref250:
	.byte $bf
@ref251:
	.byte $bf
@ref252:
	.byte $bf
@ref253:
	.byte $bf
@ref254:
	.byte $bf
@ref255:
	.byte $bf
@ref256:
	.byte $bf
@ref257:
	.byte $bf
@ref258:
	.byte $bf
@ref259:
	.byte $bf
@ref260:
	.byte $bf
@ref261:
	.byte $bf
@ref262:
	.byte $bf
@ref263:
	.byte $bf
@ref264:
	.byte $bf
	.byte $fd
	.word @song2ch4loop


@song3ch0:
	.byte $fb,$0e
@song3ch0loop:
@ref265:
	.byte $96,$32,$3a,$40,$48,$4a,$52,$4a,$48,$40,$3a,$32,$28,$1a,$22,$28
	.byte $30,$32,$3a,$32,$3a,$40,$4a,$48,$40,$3a,$40,$48,$50,$52,$50,$58
	.byte $52,$48,$40,$3a,$48,$52,$50,$52,$58,$52,$50,$52,$58,$60,$58,$52
	.byte $48
@ref266:
	.byte $32,$3a,$40,$48,$4a,$52,$4a,$48,$40,$3a,$32,$28,$1a,$22,$28,$30
	.byte $32,$3a,$32,$3a,$40,$4a,$48,$40,$3a,$40,$48,$50,$52,$50,$58,$52
	.byte $48,$40,$3a,$48,$52,$50,$52,$58,$52,$50,$52,$58,$60,$58,$52,$48
@ref267:
	.byte $00,$dd
@ref268:
	.byte $52,$50,$52,$58,$52,$50,$52,$58,$60,$58,$52,$48
	.byte $ff,$30
	.word @ref266
	.byte $ff,$30
	.word @ref266
@ref271:
	.byte $4a,$4a,$4a,$32,$4a,$32,$48,$48,$48,$30,$48,$30,$4a,$4a,$4a,$32
	.byte $4a,$32,$48,$48,$48,$30,$48,$30,$4a,$4a,$4a,$32,$4a,$32,$48,$48
	.byte $48,$30,$48,$30,$4a,$4a,$4a,$32,$4a,$32,$48,$48,$48,$30,$48,$30
@ref272:
	.byte $6a,$6a,$6a,$62,$6a,$62,$60,$60,$60,$58,$60,$58,$66,$66,$66,$5c
	.byte $66,$5c,$62,$62,$62,$58,$62,$58,$5e,$5e,$5e,$54,$5e,$54,$5c,$5e
	.byte $5c,$58,$54,$52,$58,$58,$58,$4e,$58,$4e,$4a,$4e,$4e,$52,$52,$58
	.byte $ff,$30
	.word @ref272
@ref274:
	.byte $54,$83,$58,$55,$52,$83,$58,$53,$4e,$83,$44,$4e,$44,$4a,$83,$52
	.byte $58,$81
	.byte $ff,$12
	.word @ref274
	.byte $ff,$30
	.word @ref272
	.byte $ff,$30
	.word @ref272
	.byte $fd
	.word @song3ch0loop

@song3ch1:
@song3ch1loop:
@ref278:
	.byte $00,$dd
@ref279:
	.byte $84,$32,$ad,$9a,$3a,$ad
@ref280:
	.byte $00,$dd
@ref281:
	.byte $00,$95
	.byte $ff,$04
	.word @ref279
	.byte $ff,$04
	.word @ref279
@ref284:
	.byte $00,$95,$96,$52,$52,$52,$3a,$52,$3a,$52,$52,$52,$3a,$52,$3a,$58
	.byte $58,$58,$40,$58,$40,$58,$58,$58,$40,$58,$40,$62,$62,$62,$4a,$62
	.byte $4a,$6a,$6a,$6a,$60,$6a,$60
@ref285:
	.byte $84,$32,$89,$9a,$3a,$89,$36,$89,$84,$32,$89,$2e,$89,$9a,$44,$89
	.byte $84,$28,$89,$32,$89
@ref286:
	.byte $32,$89,$9a,$3a,$89,$36,$89,$84,$32,$89,$2e,$89,$9a,$44,$89,$84
	.byte $28,$89,$32,$89
@ref287:
	.byte $3c,$89,$32,$89,$9a,$36,$89,$84,$32,$89
	.byte $ff,$08
	.word @ref287
	.byte $ff,$10
	.word @ref286
	.byte $ff,$10
	.word @ref286
	.byte $fd
	.word @song3ch1loop

@song3ch2:
@song3ch2loop:
@ref291:
	.byte $00,$dd
@ref292:
	.byte $80,$1a,$87,$00,$1a,$87,$00,$22,$87,$00,$1a,$87,$00,$18,$87,$00
	.byte $18,$87,$00,$22,$87,$00,$18,$87,$00
@ref293:
	.byte $00,$dd
@ref294:
	.byte $00,$95
@ref295:
	.byte $1a,$87,$00,$1a,$87,$00,$22,$87,$00,$1a,$87,$00,$18,$87,$00,$18
	.byte $87,$00,$22,$87,$00,$18,$87,$00
	.byte $ff,$18
	.word @ref295
@ref297:
	.byte $1a,$89,$18,$89,$1a,$89,$18,$89,$1a,$89,$18,$89,$1a,$89,$18,$89
@ref298:
	.byte $1a,$85,$11,$18,$85,$11,$1e,$85,$15,$1a,$85,$11,$16,$85,$0d,$14
	.byte $85,$0b,$28,$85,$1f,$1a,$85,$28,$81
	.byte $ff,$19
	.word @ref298
@ref300:
	.byte $25,$1b,$2d,$29,$1b,$23,$1f,$2d,$25,$1b,$23,$28,$81
	.byte $ff,$0d
	.word @ref300
@ref302:
	.byte $23,$33,$29,$31,$23,$29,$1f,$25,$2d,$29,$1b,$23,$2f,$1f,$25,$2d
	.byte $1b,$23,$29,$1f,$19,$1b,$23,$28,$81
	.byte $ff,$19
	.word @ref302
	.byte $fd
	.word @song3ch2loop

@song3ch3:
@song3ch3loop:
@ref304:
	.byte $88,$20,$8a,$1c,$1c,$8e,$1c,$86,$0e,$8a,$18,$88,$20,$8a,$1c,$1c
	.byte $8e,$1c,$86,$0e,$8a,$18,$88,$20,$8a,$1c,$1c,$8e,$1c,$86,$0e,$8a
	.byte $18,$88,$20,$8e,$1c,$86,$0e,$8e,$1c,$86,$0e,$8a,$18,$88,$20,$8a
	.byte $1c,$1c,$8e,$1c,$86,$0e,$8a,$18,$88,$20,$8a,$1c,$1c,$8e,$1c,$86
	.byte $0e,$8a,$18,$88,$20,$8a,$1c,$1c,$8e,$1c,$86,$0e,$8a,$18,$88,$20
	.byte $8e,$1c,$86,$0e,$8e,$1c,$86,$0e,$88,$20
@ref305:
	.byte $20,$8a,$1c,$1c,$8e,$1c,$86,$0e,$8a,$18,$88,$20,$8a,$1c,$1c,$8e
	.byte $1c,$86,$0e,$8a,$18,$88,$20,$8a,$1c,$1c,$8e,$1c,$86,$0e,$8a,$18
	.byte $88,$20,$8e,$1c,$86,$0e,$8e,$1c,$86,$0e,$8a,$18,$88,$20,$8a,$1c
	.byte $1c,$8e,$1c,$86,$0e,$8a,$18,$88,$20,$8a,$1c,$1c,$8e,$1c,$86,$0e
	.byte $8a,$18,$88,$20,$8a,$1c,$1c,$8e,$1c,$86,$0e,$8a,$18,$88,$20,$8e
	.byte $1c,$86,$0e,$8e,$1c,$86,$0e,$88,$20
	.byte $ff,$30
	.word @ref305
@ref307:
	.byte $97
	.byte $ff,$30
	.word @ref305
	.byte $ff,$30
	.word @ref305
@ref310:
	.byte $8a,$1f,$1f,$1f,$1f,$1f,$1f,$8e,$1f,$1f,$1f,$1f,$1f,$1f,$1b,$1b
	.byte $1b,$1b,$1b,$1b,$19,$19,$19,$15,$15,$14,$81
	.byte $ff,$30
	.word @ref304
	.byte $ff,$30
	.word @ref305
	.byte $ff,$18
	.word @ref305
	.byte $ff,$18
	.word @ref304
	.byte $ff,$30
	.word @ref304
	.byte $ff,$30
	.word @ref305
	.byte $fd
	.word @song3ch3loop

@song3ch4:
@song3ch4loop:
@ref317:
	.byte $df
@ref318:
	.byte $df
@ref319:
	.byte $df
@ref320:
	.byte $97
@ref321:
	.byte $df
@ref322:
	.byte $df
@ref323:
	.byte $df
@ref324:
	.byte $df
@ref325:
	.byte $df
@ref326:
	.byte $af
@ref327:
	.byte $af
@ref328:
	.byte $df
@ref329:
	.byte $df
	.byte $fd
	.word @song3ch4loop


@song4ch0:
	.byte $fb,$08
@ref330:
	.byte $a0,$40,$8d
@song4ch0loop:
@ref331:
	.byte $a0,$52,$ad,$4f,$4b,$49,$4a,$81
@ref332:
	.byte $52,$ad,$4f,$4b,$49,$4a,$81
@ref333:
	.byte $52,$8d,$48,$8d,$4e,$8d,$44,$85,$3b,$3d,$40,$9d,$00,$8d,$94,$41
	.byte $45,$a0,$47,$48,$81
@ref334:
	.byte $4a,$ad,$4b,$4d,$4f,$51,$52,$ad,$58,$8d
@ref335:
	.byte $62,$89,$61,$5d,$61,$58,$a5,$5c,$89,$59,$4f,$59,$52,$a5
@ref336:
	.byte $54,$8d,$52,$8d,$48,$8d,$4a,$8d,$40,$ad,$40,$8d
	.byte $ff,$07
	.word @ref332
	.byte $ff,$07
	.word @ref332
	.byte $ff,$13
	.word @ref333
	.byte $ff,$0a
	.word @ref334
	.byte $ff,$0e
	.word @ref335
	.byte $ff,$08
	.word @ref336
@ref343:
	.byte $52,$8d,$4e,$8d,$60,$8d,$62,$8d
	.byte $fd
	.word @song4ch0loop

@song4ch1:
@ref344:
	.byte $8f
@song4ch1loop:
@ref345:
	.byte $a0,$28,$85,$3a,$85,$32,$85,$3a,$85,$24,$85,$36,$85,$30,$85,$36
	.byte $85
@ref346:
	.byte $28,$85,$3a,$85,$32,$85,$3a,$85,$24,$85,$36,$85,$30,$85,$36,$85
@ref347:
	.byte $28,$85,$3a,$85,$30,$85,$3a,$85,$24,$85,$36,$85,$2c,$85,$36,$85
	.byte $28,$85,$3a,$85,$32,$85,$3a,$85,$24,$85,$36,$85,$30,$85,$36,$85
@ref348:
	.byte $28,$85,$3a,$85,$32,$85,$3a,$85,$24,$85,$36,$85,$30,$85,$2c,$85
	.byte $28,$85,$3a,$85,$32,$85,$3a,$85,$24,$85,$36,$85,$28,$85,$36,$85
@ref349:
	.byte $28,$89,$33,$3a,$ad,$24,$89,$37,$30,$ad
@ref350:
	.byte $32,$8d,$30,$8d,$28,$8d,$2c,$8d,$28,$85,$32,$85,$3a,$85,$32,$85
	.byte $24,$85,$30,$85,$36,$85,$3a,$85
	.byte $ff,$10
	.word @ref346
	.byte $ff,$10
	.word @ref346
	.byte $ff,$20
	.word @ref347
	.byte $ff,$20
	.word @ref348
	.byte $ff,$0a
	.word @ref349
	.byte $ff,$08
	.word @ref350
@ref357:
	.byte $30,$8d,$28,$8d,$24,$8d,$3a,$8d
	.byte $fd
	.word @song4ch1loop

@song4ch2:
@ref358:
	.byte $8f
@song4ch2loop:
@ref359:
	.byte $bf
@ref360:
	.byte $bf
@ref361:
	.byte $f9,$85
@ref362:
	.byte $f9,$85
@ref363:
	.byte $f9,$85
@ref364:
	.byte $f9,$85
@ref365:
	.byte $bf
@ref366:
	.byte $bf
@ref367:
	.byte $f9,$85
@ref368:
	.byte $f9,$85
@ref369:
	.byte $f9,$85
@ref370:
	.byte $bf
@ref371:
	.byte $bf
	.byte $fd
	.word @song4ch2loop

@song4ch3:
@ref372:
	.byte $8f
@song4ch3loop:
@ref373:
	.byte $8e,$16,$9d,$00,$8d,$16,$85,$00,$85
@ref374:
	.byte $16,$9d,$00,$8d,$16,$85,$00,$85
@ref375:
	.byte $16,$9d,$00,$8d,$16,$85,$00,$85,$16,$9d,$00,$8d,$16,$85,$00,$85
	.byte $ff,$10
	.word @ref375
	.byte $ff,$10
	.word @ref375
	.byte $ff,$10
	.word @ref375
	.byte $ff,$08
	.word @ref374
	.byte $ff,$08
	.word @ref374
	.byte $ff,$10
	.word @ref375
	.byte $ff,$10
	.word @ref375
	.byte $ff,$10
	.word @ref375
	.byte $ff,$08
	.word @ref374
	.byte $ff,$08
	.word @ref374
	.byte $fd
	.word @song4ch3loop

@song4ch4:
@ref386:
	.byte $8f
@song4ch4loop:
@ref387:
	.byte $bf
@ref388:
	.byte $bf
@ref389:
	.byte $f9,$85
@ref390:
	.byte $f9,$85
@ref391:
	.byte $f9,$85
@ref392:
	.byte $f9,$85
@ref393:
	.byte $bf
@ref394:
	.byte $bf
@ref395:
	.byte $f9,$85
@ref396:
	.byte $f9,$85
@ref397:
	.byte $f9,$85
@ref398:
	.byte $bf
@ref399:
	.byte $bf
	.byte $fd
	.word @song4ch4loop


@song5ch0:
	.byte $fb,$04
@song5ch0loop:
@ref400:
	.byte $8c,$22,$9d,$26,$8d,$28,$8d,$1e,$9d,$1a,$85,$1e,$85,$22,$8d
@ref401:
	.byte $26,$95,$22,$95,$1e,$95,$1a,$95,$1e,$85,$22,$85,$26,$8d
@ref402:
	.byte $22,$9d,$26,$8d,$28,$8d,$1e,$9d,$1a,$85,$1e,$85,$22,$8d
	.byte $ff,$0e
	.word @ref401
@ref404:
	.byte $22,$85,$22,$8d,$22,$a5,$20,$85,$20,$8d,$20,$a5
@ref405:
	.byte $1a,$85,$1a,$8d,$1a,$a5,$20,$85,$20,$8d,$20,$a5
	.byte $ff,$0c
	.word @ref404
	.byte $ff,$0c
	.word @ref405
@ref408:
	.byte $20,$85,$38,$85,$16,$85,$16,$85,$18,$85,$30,$85,$16,$85,$16,$85
	.byte $18,$85,$30,$85,$1c,$85,$34,$85,$20,$85,$38,$85,$1c,$85,$20,$85
@ref409:
	.byte $20,$85,$38,$85,$16,$85,$16,$85,$18,$85,$30,$85,$16,$85,$16,$85
	.byte $18,$85,$30,$85,$1c,$85,$34,$85,$20,$85,$38,$85,$26,$85,$3e,$85
@ref410:
	.byte $19,$19,$30,$85,$18,$85,$32,$85,$18,$85,$36,$85,$1b,$1b,$38,$85
	.byte $19,$19,$30,$85,$18,$85,$32,$85,$18,$85,$36,$85,$19,$19,$38,$85
	.byte $ff,$20
	.word @ref410
	.byte $ff,$20
	.word @ref408
	.byte $ff,$20
	.word @ref409
	.byte $ff,$20
	.word @ref410
	.byte $ff,$20
	.word @ref410
	.byte $ff,$20
	.word @ref410
	.byte $ff,$20
	.word @ref410
@ref418:
	.byte $a0,$22,$a5,$00,$95
	.byte $fd
	.word @song5ch0loop

@song5ch1:
@song5ch1loop:
@ref419:
	.byte $94,$3a,$3e,$93,$3a,$95,$36,$95,$32,$95,$36,$8d,$3a,$8d
@ref420:
	.byte $82,$46,$85,$40,$85,$3e,$85,$46,$85,$40,$85,$3e,$85,$46,$85,$40
	.byte $85,$46,$85,$40,$85,$3e,$85,$46,$85,$40,$85,$3e,$85,$46,$85,$40
	.byte $85
	.byte $ff,$0d
	.word @ref419
	.byte $ff,$20
	.word @ref420
@ref423:
	.byte $46,$85,$40,$85,$3e,$85,$46,$85,$40,$85,$3e,$85,$46,$85,$40,$85
	.byte $46,$85,$40,$85,$3e,$85,$46,$85,$40,$85,$3e,$85,$46,$85,$48,$85
	.byte $ff,$20
	.word @ref423
	.byte $ff,$20
	.word @ref423
	.byte $ff,$20
	.word @ref423
@ref427:
	.byte $94,$50,$95,$38,$85,$46,$95,$2e,$85,$48,$85,$46,$85,$30,$85,$42
	.byte $8d,$38,$95
@ref428:
	.byte $50,$95,$38,$85,$46,$95,$2e,$85,$48,$85,$46,$85,$30,$85,$42,$8d
	.byte $46,$95
@ref429:
	.byte $31,$31,$48,$85,$30,$85,$4a,$85,$30,$85,$4e,$85,$33,$33,$50,$85
	.byte $82,$51,$4b,$49,$4b,$51,$4b,$49,$4b,$51,$4b,$49,$4b,$51,$4b,$49
	.byte $50,$81
@ref430:
	.byte $94,$31,$31,$48,$85,$30,$85,$4a,$85,$30,$85,$4e,$85,$33,$33,$50
	.byte $85,$82,$51,$4b,$49,$4b,$51,$4b,$49,$4b,$51,$4b,$49,$4b,$51,$4b
	.byte $49,$50,$81
	.byte $ff,$12
	.word @ref427
	.byte $ff,$12
	.word @ref428
	.byte $ff,$21
	.word @ref429
	.byte $ff,$21
	.word @ref430
@ref435:
	.byte $94,$4a,$85,$50,$85,$4a,$8d,$48,$8d,$4a,$85,$4a,$85,$4a,$85,$50
	.byte $85,$4a,$8d,$48,$8d,$4a,$8d
@ref436:
	.byte $96,$38,$85,$32,$85,$30,$85,$32,$85,$38,$85,$32,$85,$30,$85,$32
	.byte $85,$39,$33,$31,$33,$39,$33,$31,$33,$39,$33,$31,$33,$39,$33,$31
	.byte $32,$81
@ref437:
	.byte $94,$3a,$3e,$bb
	.byte $fd
	.word @song5ch1loop

@song5ch2:
@song5ch2loop:
@ref438:
	.byte $00,$f9,$83
@ref439:
	.byte $00,$f9,$83
@ref440:
	.byte $00,$f9,$83
@ref441:
	.byte $00,$f9,$83
@ref442:
	.byte $00,$f9,$83
@ref443:
	.byte $00,$f9,$83
@ref444:
	.byte $00,$f9,$83
@ref445:
	.byte $00,$f9,$83
@ref446:
	.byte $00,$f9,$83
@ref447:
	.byte $00,$f9,$83
@ref448:
	.byte $00,$f9,$83
@ref449:
	.byte $00,$f9,$83
@ref450:
	.byte $00,$f9,$83
@ref451:
	.byte $00,$f9,$83
@ref452:
	.byte $00,$f9,$83
@ref453:
	.byte $00,$f9,$83
@ref454:
	.byte $00,$f9,$83
@ref455:
	.byte $00,$f9,$83
@ref456:
	.byte $00,$bd
	.byte $fd
	.word @song5ch2loop

@song5ch3:
@song5ch3loop:
@ref457:
	.byte $f9,$85
@ref458:
	.byte $f9,$85
@ref459:
	.byte $f9,$85
@ref460:
	.byte $f9,$85
@ref461:
	.byte $f9,$85
@ref462:
	.byte $f9,$85
@ref463:
	.byte $f9,$85
@ref464:
	.byte $df,$86,$07,$07,$03,$03,$1f,$1f,$07,$1e,$81
@ref465:
	.byte $88,$04,$85,$05,$05,$8a,$10,$85,$88,$05,$04,$85,$8a,$11,$88,$05
	.byte $05,$8a,$11,$11,$86,$09,$8a,$11,$88,$04,$85,$05,$05,$8a,$10,$85
	.byte $88,$05,$04,$85,$8a,$11,$88,$05,$05,$8a,$11,$11,$86,$09,$8a,$10
	.byte $81
	.byte $ff,$21
	.word @ref465
	.byte $ff,$21
	.word @ref465
	.byte $ff,$21
	.word @ref465
	.byte $ff,$21
	.word @ref465
	.byte $ff,$21
	.word @ref465
	.byte $ff,$21
	.word @ref465
	.byte $ff,$21
	.word @ref465
	.byte $ff,$21
	.word @ref465
	.byte $ff,$21
	.word @ref465
@ref475:
	.byte $bf
	.byte $fd
	.word @song5ch3loop

@song5ch4:
@song5ch4loop:
@ref476:
	.byte $f9,$85
@ref477:
	.byte $f9,$85
@ref478:
	.byte $f9,$85
@ref479:
	.byte $f9,$85
@ref480:
	.byte $f9,$85
@ref481:
	.byte $f9,$85
@ref482:
	.byte $f9,$85
@ref483:
	.byte $f9,$85
@ref484:
	.byte $f9,$85
@ref485:
	.byte $f9,$85
@ref486:
	.byte $f9,$85
@ref487:
	.byte $f9,$85
@ref488:
	.byte $f9,$85
@ref489:
	.byte $f9,$85
@ref490:
	.byte $f9,$85
@ref491:
	.byte $f9,$85
@ref492:
	.byte $f9,$85
@ref493:
	.byte $f9,$85
@ref494:
	.byte $bf
	.byte $fd
	.word @song5ch4loop


@song6ch0:
	.byte $fb,$04
@song6ch0loop:
@ref495:
	.byte $8c,$26,$95,$22,$95,$1e,$8d
@ref496:
	.byte $87,$1a,$95,$1e,$85,$22,$85,$26,$8d
	.byte $fd
	.word @song6ch0loop

@song6ch1:
@song6ch1loop:
	.byte $ff,$10
	.word @ref420
@ref498:
	.byte $46,$85,$40,$85,$3e,$85,$46,$85,$40,$85,$3e,$85,$46,$85,$48,$85
	.byte $fd
	.word @song6ch1loop

@song6ch2:
@song6ch2loop:
@ref499:
	.byte $00,$bd
@ref500:
	.byte $bf
	.byte $fd
	.word @song6ch2loop

@song6ch3:
@song6ch3loop:
@ref501:
	.byte $bf
@ref502:
	.byte $bf
	.byte $fd
	.word @song6ch3loop

@song6ch4:
@song6ch4loop:
@ref503:
	.byte $bf
@ref504:
	.byte $bf
	.byte $fd
	.word @song6ch4loop


@song7ch0:
	.byte $fb,$04
@song7ch0loop:
@ref505:
	.byte $f9,$85
	.byte $fd
	.word @song7ch0loop

@song7ch1:
@song7ch1loop:
@ref506:
	.byte $f9,$85
	.byte $fd
	.word @song7ch1loop

@song7ch2:
@song7ch2loop:
@ref507:
	.byte $f9,$85
	.byte $fd
	.word @song7ch2loop

@song7ch3:
@song7ch3loop:
@ref508:
	.byte $a0,$06,$f9,$83
	.byte $fd
	.word @song7ch3loop

@song7ch4:
@song7ch4loop:
@ref509:
	.byte $f9,$85
	.byte $fd
	.word @song7ch4loop
