	.file "C:\\Projects\\Firmware\\MRF49XA\\Library\\targets\\mrf49xa_pic24\\..\\..\\src\\devices\\mrf49xa.c"
	.section	.debug_abbrev,info
.Ldebug_abbrev0:
	.section	.debug_info,info
.Ldebug_info0:
	.section	.debug_line,info
.Ldebug_line0:
	.section	.text,code
.Ltext0:
	.section	.text,code
	.align	2
	.global	_SPI_Read	; export
	.type	_SPI_Read,@function
_SPI_Read:
.LFB0:
.LSM0:
	.set ___PA___,1
.LSM1:
	bclr.b	_LATBbits+1,#0
.LSM2:
	bclr.b	_LATBbits,#7
.LSM3:
	clr.b	w0
.LSM4:
	mov.b	w0,w1
.L4:
.LSM5:
	add.b	w0,w0,w0
.LSM6:
	btst	_PORTCbits,#4
	.set ___BP___,50
	bra	z,.L2
.LSM7:
	bset.b	w0,#0
	bra	.L3
.L2:
.LSM8:
	bclr.b	w0,#0
.L3:
.LSM9:
	bset.b	_LATBbits,#7
.LSM10:
	nop	
.LSM11:
	bclr.b	_LATBbits,#7
.LSM12:
	inc.b	w1,w1
	sub.b	w1,#7,[w15]
	.set ___BP___,87
	bra	leu,.L4
.LSM13:
	return	
	.set ___PA___,0
.LFE0:
	.align	2
	.global	_SPI_Write	; export
	.type	_SPI_Write,@function
_SPI_Write:
.LFB1:
.LSM14:
	.set ___PA___,1
.LSM15:
	bclr.b	_LATBbits+1,#0
.LSM16:
	bclr.b	_LATBbits,#7
.LSM17:
	clr.b	w1
.L10:
.LSM18:
	sub.b	w0,#0,[w15]
	.set ___BP___,73
	bra	ge,.L7
.LSM19:
	bset.b	_LATBbits+1,#0
	bra	.L8
.L7:
.LSM20:
	bclr.b	_LATBbits+1,#0
.L8:
.LSM21:
	bset.b	_LATBbits,#7
.LSM22:
	nop	
.LSM23:
	bclr.b	_LATBbits,#7
.LSM24:
	inc.b	w1,w1
	sub.b	w1,#7,[w15]
	.set ___BP___,12
	bra	gtu,.L9
.LSM25:
	add.b	w0,w0,w0
	bra	.L10
.L9:
.LSM26:
	bclr.b	_LATBbits+1,#0
.LSM27:
	return	
	.set ___PA___,0
.LFE1:
	.align	2
	.global	_SPI_Command	; export
	.type	_SPI_Command,@function
_SPI_Command:
.LFB2:
.LSM28:
	.set ___PA___,1
	mov	w8,[w15++]
	mov	w0,w8
.LSM29:
	bclr.b	_LATBbits,#5
.LSM30:
	lsr	w8,#8,w0
	rcall	_SPI_Write
.LSM31:
	mov.b	w8,w0
	rcall	_SPI_Write
.LSM32:
	bset.b	_LATBbits,#5
.LSM33:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE2:
	.align	2
	.global	_SPI_Write16	; export
	.type	_SPI_Write16,@function
_SPI_Write16:
.LFB3:
.LSM34:
	.set ___PA___,1
	mov	w8,[w15++]
	mov	w0,w8
.LSM35:
	lsr	w8,#8,w0
	rcall	_SPI_Write
.LSM36:
	mov.b	w8,w0
	rcall	_SPI_Write
.LSM37:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE3:
	.align	2
	.global	_MRF49XA_Reset_Radio	; export
	.type	_MRF49XA_Reset_Radio,@function
_MRF49XA_Reset_Radio:
.LFB4:
.LSM38:
	.set ___PA___,1
.LSM39:
	mov	#-32256,w0
	rcall	_SPI_Command
.LSM40:
	mov	#-13695,w0
	rcall	_SPI_Command
.LSM41:
	mov	#-32728,w0
	rcall	_SPI_Command
.LSM42:
	mov	#-32128,w0
	rcall	_SPI_Command
.LSM43:
	mov	#-32664,w0
	rcall	_SPI_Command
.LSM44:
	mov	#-13693,w0
	bra	_SPI_Command
.LSM45:
	.set ___PA___,0
.LFE4:
	.align	2
	.global	_MRF49XA_Init	; export
	.type	_MRF49XA_Init,@function
_MRF49XA_Init:
.LFB5:
.LSM46:
	.set ___PA___,1
.LSM47:
	bclr.b	_LATCbits,#6
.LSM48:
	nop	
.LSM49:
	bset.b	_LATCbits,#6
.LSM50:
	clr.b	w0
	bra	.L15
.L16:
	nop	
	inc.b	w1,w1
	add.b	w1,#7,[w15]
	.set ___BP___,98
	bra	leu,.L16
	inc.b	w0,w0
	add.b	w0,#7,[w15]
	.set ___BP___,1
	bra	gtu,.L17
.L15:
.LSM51:
	clr.b	w1
	bra	.L16
.L17:
.LSM52:
	mov	#-13695,w0
	rcall	_SPI_Command
.LSM53:
	mov	#-13693,w0
	rcall	_SPI_Command
.LSM54:
	mov	#-32728,w0
	rcall	_SPI_Command
.LSM55:
	mov	#-15145,w0
	rcall	_SPI_Command
.LSM56:
	mov	#-22432,w0
	rcall	_SPI_Command
.LSM57:
	mov	#-14685,w0
	rcall	_SPI_Command
.LSM58:
	mov	#-32256,w0
	rcall	_SPI_Command
.LSM59:
	mov	#-27552,w0
	rcall	_SPI_Command
.LSM60:
	mov	#-26480,w0
	rcall	_SPI_Command
.LSM61:
	mov	#-15700,w0
	rcall	_SPI_Command
.LSM62:
	mov	#-32224,w0
	rcall	_SPI_Command
.LSM63:
	clr.b	w0
	bra	.L18
.L19:
	nop	
	inc.b	w1,w1
	add.b	w1,#7,[w15]
	.set ___BP___,98
	bra	leu,.L19
	inc.b	w0,w0
	add.b	w0,#7,[w15]
	.set ___BP___,1
	bra	gtu,.L20
.L18:
.LSM64:
	clr.b	w1
	bra	.L19
.L20:
.LSM65:
	mov	#-32128,w0
	rcall	_SPI_Command
.LSM66:
	mov	#-32664,w0
	rcall	_SPI_Command
.LSM67:
	mov	#-13695,w0
	rcall	_SPI_Command
.LSM68:
	mov	#-13693,w0
	rcall	_SPI_Command
.LSM69:
	bset.b	_LATCbits,#5
.LSM70:
	return	
	.set ___PA___,0
.LFE5:
	.align	2
	.global	_MRF49XA_TxPacket	; export
	.type	_MRF49XA_TxPacket,@function
_MRF49XA_TxPacket:
.LFB6:
.LSM71:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov.d	w10,[w15++]
	mov	w12,[w15++]
	mov	w0,w12
	mov.b	w1,w10
.LSM72:
	mov	#-32256,w0
	rcall	_SPI_Command
.LSM73:
	mov	#-32600,w0
	rcall	_SPI_Command
.LSM74:
	mov	#-32224,w0
	rcall	_SPI_Command
.LSM75:
	bclr.b	_LATBbits,#5
.L24:
.LSM76:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L24
	mov	#-18262,w0
	rcall	_SPI_Write16
.L25:
.LSM77:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L25
	mov.b	#-86,w0
	rcall	_SPI_Write
.L26:
.LSM78:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L26
	mov.b	#45,w0
	rcall	_SPI_Write
.L27:
.LSM79:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L27
	mov.b	#-44,w0
	rcall	_SPI_Write
.L28:
.LSM80:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L28
	inc.b	w10,w0
	rcall	_SPI_Write
.LSM81:
	clr.b	w8
.LSM82:
	mov.b	w8,w9
	bra	.L29
.L37:
.LSM83:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L37
.LSM84:
	ze	w9,w11
	add	w12,w11,w11
	mov.b	[w11],w0
	rcall	_SPI_Write
.LSM85:
	xor.b	w8,[w11],w8
.LSM86:
	inc.b	w9,w9
.L29:
	sub.b	w9,w10,[w15]
	.set ___BP___,91
	bra	ltu,.L37
.L36:
.LSM87:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L36
	mov.b	w8,w0
	rcall	_SPI_Write
.L32:
.LSM88:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L32
	clr.b	w0
	rcall	_SPI_Write
.L33:
.LSM89:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L33
	clr.b	w0
	rcall	_SPI_Write
.L34:
.LSM90:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L34
	clr.b	w0
	rcall	_SPI_Write
.L35:
.LSM91:
	btst	_PORTCbits,#4
	.set ___BP___,91
	bra	z,.L35
.LSM92:
	bset.b	_LATBbits,#5
.LSM93:
	mov	#-13695,w0
	rcall	_SPI_Command
.LSM94:
	mov	#-32128,w0
	rcall	_SPI_Command
.LSM95:
	mov	#-32664,w0
	rcall	_SPI_Command
.LSM96:
	mov	#-13693,w0
	rcall	_SPI_Command
.LSM97:
	mov	[--w15],w12
	mov.d	[--w15],w10
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE6:
	.align	2
	.global	_MRF49XA_RxPacket	; export
	.type	_MRF49XA_RxPacket,@function
_MRF49XA_RxPacket:
.LFB7:
.LSM98:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov	w0,w9
.LSM99:
	bclr.b	_LATBbits+1,#0
.LSM100:
	bclr.b	_LATBbits,#5
.LSM101:
	nop	
.LSM102:
	mov	_PORTCbits,w0
	and	w0,#16,w0
	.set ___BP___,50
	bra	z,.L50
.LSM103:
	bset.b	_LATBbits,#5
.LSM104:
	bclr.b	_LATCbits,#5
.LSM105:
	mov	#_inPacket.6389,w8
	mov.b	[w8],w8
	sub.b	w8,#0,[w15]
	.set ___BP___,50
	bra	nz,.L51
.LSM106:
	rcall	_SPI_Read
	mov.b	WREG,_length.6390
.LSM107:
	bset.b	_LATCbits,#5
.LSM108:
	sub.b	w0,#20,[w15]
	.set ___BP___,71
	bra	leu,.L52
.LSM109:
	rcall	_MRF49XA_Reset_Radio
	bra	.L55
.L52:
.LSM110:
	mov.b	#1,w0
	mov.b	WREG,_inPacket.6389
.LSM111:
	exch	w0,w8
	mov.b	WREG,_index.6391
	mov.b	WREG,_crc.6392
	exch	w0,w8
.L55:
.LSM112:
	mov.b	w8,w0
	bra	.L53
.L51:
.LSM113:
	mov	#_index.6391,w8
	mov.b	[w8],w8
	ze	w8,w8
	add	w9,w8,w8
	rcall	_SPI_Read
	mov.b	w0,[w8]
.LSM114:
	mov	#_index.6391,w1
	mov.b	[w1],w1
	ze	w1,w0
	mov.b	[w9+w0],w2
	mov	#_crc.6392,w0
	xor.b	w2,[w0],w2
	mov	w2,w0
	mov.b	WREG,_crc.6392
.LSM115:
	inc.b	w1,w1
	mov	w1,w0
	mov.b	WREG,_index.6391
.LSM116:
	bset.b	_LATCbits,#5
.LSM117:
	mov.b	_length.6390,WREG
	sub.b	w1,w0,[w15]
	.set ___BP___,39
	bra	ltu,.L54
.LSM118:
	clr.b	_inPacket.6389
.LSM119:
	sub.b	w0,#0,[w15]
	.set ___BP___,39
	bra	z,.L53
.LSM120:
	ze	w1,w1
	mov.b	[w9+w1],w1
	sub.b	w2,w1,[w15]
	.set ___BP___,28
	bra	z,.L53
.LSM121:
	bset.b	w0,#7
	bra	.L53
.L50:
.LSM122:
	bset.b	_LATBbits,#5
.LSM123:
	bra	.L53
.L54:
.LSM124:
	clr.b	w0
.L53:
.LSM125:
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE7:
	.pushsection	.nbss,bss,near
_crc.6392:	.space	1
	.popsection
	.pushsection	.nbss,bss,near
_index.6391:	.space	1
	.popsection
	.pushsection	.nbss,bss,near
_length.6390:	.space	1
	.popsection
	.pushsection	.nbss,bss,near
_inPacket.6389:	.space	1
	.popsection
	.section	.debug_frame,info
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.byte	0
	.uleb128 0x1
	.sleb128 2
	.byte	0x21
	.byte	0x12
	.uleb128 0xf
	.sleb128 -2
	.byte	0x9
	.uleb128 0x21
	.uleb128 0xf
	.align	4
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.align	4
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.align	4
.LEFDE12:
.LSFDE14:
	.4byte	.LEFDE14-.LASFDE14
.LASFDE14:
	.4byte	.Lframe0
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.align	4
.LEFDE14:
	.section	.text,code
.Letext0:
	.section	.debug_info,info
	.4byte	0x6f5
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1_11) (A) Build date: Nov 17 2012"
	.byte	0x1
	.asciz	"../../src/devices/mrf49xa.c"
	.ascii	"C:\\\\Projects\\\\Firmware\\\\MRF49XA\\\\Library\\\\targets\\\\mrf49"
	.asciz	"xa_pic24"
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.asciz	"unsigned int"
	.uleb128 0x3
	.asciz	"tagLATBBITS"
	.byte	0x2
	.byte	0x2
	.2byte	0x84e
	.4byte	0x1f9
	.uleb128 0x4
	.asciz	"LATB0"
	.byte	0x2
	.2byte	0x84f
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB1"
	.byte	0x2
	.2byte	0x850
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB2"
	.byte	0x2
	.2byte	0x851
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB3"
	.byte	0x2
	.2byte	0x852
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB4"
	.byte	0x2
	.2byte	0x853
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB5"
	.byte	0x2
	.2byte	0x854
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB7"
	.byte	0x2
	.2byte	0x856
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB8"
	.byte	0x2
	.2byte	0x857
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB9"
	.byte	0x2
	.2byte	0x858
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB10"
	.byte	0x2
	.2byte	0x859
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB11"
	.byte	0x2
	.2byte	0x85a
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB13"
	.byte	0x2
	.2byte	0x85c
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB14"
	.byte	0x2
	.2byte	0x85d
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATB15"
	.byte	0x2
	.2byte	0x85e
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x5
	.asciz	"LATBBITS"
	.byte	0x2
	.2byte	0x85f
	.4byte	0xc6
	.uleb128 0x3
	.asciz	"tagPORTCBITS"
	.byte	0x2
	.byte	0x2
	.2byte	0x887
	.4byte	0x2d5
	.uleb128 0x4
	.asciz	"RC0"
	.byte	0x2
	.2byte	0x888
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"RC1"
	.byte	0x2
	.2byte	0x889
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"RC2"
	.byte	0x2
	.2byte	0x88a
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"RC3"
	.byte	0x2
	.2byte	0x88b
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"RC4"
	.byte	0x2
	.2byte	0x88c
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"RC5"
	.byte	0x2
	.2byte	0x88d
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"RC6"
	.byte	0x2
	.2byte	0x88e
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"RC7"
	.byte	0x2
	.2byte	0x88f
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"RC8"
	.byte	0x2
	.2byte	0x890
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"RC9"
	.byte	0x2
	.2byte	0x891
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x5
	.asciz	"PORTCBITS"
	.byte	0x2
	.2byte	0x892
	.4byte	0x20a
	.uleb128 0x3
	.asciz	"tagLATCBITS"
	.byte	0x2
	.byte	0x2
	.2byte	0x896
	.4byte	0x3c5
	.uleb128 0x4
	.asciz	"LATC0"
	.byte	0x2
	.2byte	0x897
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATC1"
	.byte	0x2
	.2byte	0x898
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATC2"
	.byte	0x2
	.2byte	0x899
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATC3"
	.byte	0x2
	.2byte	0x89a
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATC4"
	.byte	0x2
	.2byte	0x89b
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATC5"
	.byte	0x2
	.2byte	0x89c
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATC6"
	.byte	0x2
	.2byte	0x89d
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATC7"
	.byte	0x2
	.2byte	0x89e
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATC8"
	.byte	0x2
	.2byte	0x89f
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.asciz	"LATC9"
	.byte	0x2
	.2byte	0x8a0
	.4byte	0xb6
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x5
	.asciz	"LATCBITS"
	.byte	0x2
	.2byte	0x8a1
	.4byte	0x2e7
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.asciz	"short unsigned int"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.asciz	"char"
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.asciz	"short int"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.asciz	"signed char"
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.asciz	"long int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.asciz	"long long int"
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.asciz	"unsigned char"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.asciz	"long unsigned int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.asciz	"long long unsigned int"
	.uleb128 0x6
	.asciz	"UI08_t"
	.byte	0x3
	.byte	0x66
	.4byte	0x434
	.uleb128 0x6
	.asciz	"UI16_t"
	.byte	0x3
	.byte	0x67
	.4byte	0xb6
	.uleb128 0x7
	.byte	0x1
	.asciz	"SPI_Read"
	.byte	0x1
	.byte	0x5
	.byte	0x1
	.4byte	0x474
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.4byte	0x4c8
	.uleb128 0x8
	.asciz	"i"
	.byte	0x1
	.byte	0x7
	.4byte	0x474
	.byte	0x1
	.byte	0x51
	.uleb128 0x9
	.asciz	"data"
	.byte	0x1
	.byte	0x8
	.4byte	0x474
	.byte	0x0
	.uleb128 0xa
	.byte	0x1
	.asciz	"SPI_Write"
	.byte	0x1
	.byte	0x23
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.4byte	0x4ff
	.uleb128 0xb
	.asciz	"data"
	.byte	0x1
	.byte	0x23
	.4byte	0x474
	.byte	0x1
	.byte	0x50
	.uleb128 0x8
	.asciz	"i"
	.byte	0x1
	.byte	0x25
	.4byte	0x474
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0xa
	.byte	0x1
	.asciz	"SPI_Command"
	.byte	0x1
	.byte	0x41
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.4byte	0x52c
	.uleb128 0xb
	.asciz	"cmd"
	.byte	0x1
	.byte	0x41
	.4byte	0x482
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0xa
	.byte	0x1
	.asciz	"SPI_Write16"
	.byte	0x1
	.byte	0x4b
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.4byte	0x55c
	.uleb128 0xb
	.asciz	"data16"
	.byte	0x1
	.byte	0x4b
	.4byte	0x482
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.asciz	"MRF49XA_Reset_Radio"
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.uleb128 0xd
	.byte	0x1
	.asciz	"MRF49XA_Init"
	.byte	0x1
	.byte	0x5b
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.4byte	0x5b1
	.uleb128 0x9
	.asciz	"i"
	.byte	0x1
	.byte	0x5d
	.4byte	0x474
	.uleb128 0x9
	.asciz	"j"
	.byte	0x1
	.byte	0x5d
	.4byte	0x474
	.byte	0x0
	.uleb128 0xa
	.byte	0x1
	.asciz	"MRF49XA_TxPacket"
	.byte	0x1
	.byte	0x7c
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.4byte	0x60a
	.uleb128 0xb
	.asciz	"data"
	.byte	0x1
	.byte	0x7c
	.4byte	0x60a
	.byte	0x1
	.byte	0x5c
	.uleb128 0xb
	.asciz	"size"
	.byte	0x1
	.byte	0x7c
	.4byte	0x474
	.byte	0x1
	.byte	0x5a
	.uleb128 0x8
	.asciz	"i"
	.byte	0x1
	.byte	0x7e
	.4byte	0x474
	.byte	0x1
	.byte	0x59
	.uleb128 0x8
	.asciz	"crc"
	.byte	0x1
	.byte	0x7e
	.4byte	0x474
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0xe
	.byte	0x2
	.4byte	0x474
	.uleb128 0x7
	.byte	0x1
	.asciz	"MRF49XA_RxPacket"
	.byte	0x1
	.byte	0xa2
	.byte	0x1
	.4byte	0x474
	.4byte	.LFB7
	.4byte	.LFE7
	.byte	0x1
	.byte	0x5f
	.4byte	0x695
	.uleb128 0xb
	.asciz	"data"
	.byte	0x1
	.byte	0xa2
	.4byte	0x60a
	.byte	0x1
	.byte	0x59
	.uleb128 0x8
	.asciz	"inPacket"
	.byte	0x1
	.byte	0xa4
	.4byte	0x474
	.byte	0x5
	.byte	0x3
	.4byte	_inPacket.6389
	.uleb128 0x8
	.asciz	"length"
	.byte	0x1
	.byte	0xa5
	.4byte	0x474
	.byte	0x5
	.byte	0x3
	.4byte	_length.6390
	.uleb128 0x8
	.asciz	"index"
	.byte	0x1
	.byte	0xa6
	.4byte	0x474
	.byte	0x5
	.byte	0x3
	.4byte	_index.6391
	.uleb128 0x8
	.asciz	"crc"
	.byte	0x1
	.byte	0xa7
	.4byte	0x474
	.byte	0x5
	.byte	0x3
	.4byte	_crc.6392
	.byte	0x0
	.uleb128 0xf
	.4byte	.LASF0
	.byte	0x2
	.2byte	0x860
	.4byte	0x6a3
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x1f9
	.uleb128 0xf
	.4byte	.LASF1
	.byte	0x2
	.2byte	0x893
	.4byte	0x6b6
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x2d5
	.uleb128 0xf
	.4byte	.LASF2
	.byte	0x2
	.2byte	0x8a2
	.4byte	0x6c9
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x3c5
	.uleb128 0xf
	.4byte	.LASF0
	.byte	0x2
	.2byte	0x860
	.4byte	0x6a3
	.byte	0x1
	.byte	0x1
	.uleb128 0xf
	.4byte	.LASF1
	.byte	0x2
	.2byte	0x893
	.4byte	0x6b6
	.byte	0x1
	.byte	0x1
	.uleb128 0xf
	.4byte	.LASF2
	.byte	0x2
	.2byte	0x8a2
	.4byte	0x6c9
	.byte	0x1
	.byte	0x1
	.byte	0x0
	.section	.debug_abbrev,info
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x9c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x6f9
	.4byte	0x490
	.asciz	"SPI_Read"
	.4byte	0x4c8
	.asciz	"SPI_Write"
	.4byte	0x4ff
	.asciz	"SPI_Command"
	.4byte	0x52c
	.asciz	"SPI_Write16"
	.4byte	0x55c
	.asciz	"MRF49XA_Reset_Radio"
	.4byte	0x57f
	.asciz	"MRF49XA_Init"
	.4byte	0x5b1
	.asciz	"MRF49XA_TxPacket"
	.4byte	0x610
	.asciz	"MRF49XA_RxPacket"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x7d
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x6f9
	.4byte	0xc6
	.asciz	"tagLATBBITS"
	.4byte	0x1f9
	.asciz	"LATBBITS"
	.4byte	0x20a
	.asciz	"tagPORTCBITS"
	.4byte	0x2d5
	.asciz	"PORTCBITS"
	.4byte	0x2e7
	.asciz	"tagLATCBITS"
	.4byte	0x3c5
	.asciz	"LATCBITS"
	.4byte	0x474
	.asciz	"UI08_t"
	.4byte	0x482
	.asciz	"UI16_t"
	.4byte	0x0
	.section	.debug_aranges,info
	.4byte	0x14
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_line,info
	.4byte	.LELT0-.LSLT0
.LSLT0:
	.2byte	0x2
	.4byte	.LELTP0-.LASLTP0
.LASLTP0:
	.byte	0x1
	.byte	0x1
	.byte	0xf6
	.byte	0xf5
	.byte	0xa
	.byte	0x0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.byte	0x1
	.ascii	"../../src/devices"
	.byte 0
	.ascii	"C:/Projects/Firmware/MRF49XA/Library/inc"
	.byte 0
	.ascii	"c:\\program files (x86)\\microchip\\xc16\\v1.11\\bin\\bin\\../..\\su"
	.ascii	"pport\\PIC24F\\h"
	.byte 0
	.byte	0x0
	.asciz	"mrf49xa.c"
	.uleb128 0x1
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"p24FJ64GB004.h"
	.uleb128 0x3
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"bspPIC24.h"
	.uleb128 0x2
	.uleb128 0x0
	.uleb128 0x0
	.byte	0x0
.LELTP0:
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.Letext0
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM0
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM1
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM2
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM3
	.byte	0x11
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM4
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM5
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM6
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM7
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM8
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM9
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM10
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM11
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM12
	.byte	0x3
	.sleb128 -17
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM13
	.byte	0x28
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE0
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM14
	.byte	0x37
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM15
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM16
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM17
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM18
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM19
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM20
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM21
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM22
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM23
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM24
	.byte	0x3
	.sleb128 -14
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM25
	.byte	0x24
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM26
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM27
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE1
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM28
	.byte	0x55
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM29
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM30
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM31
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM32
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM33
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE2
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM34
	.byte	0x5f
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM35
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM36
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM37
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE3
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM38
	.byte	0x65
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM39
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM40
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM41
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM42
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM43
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM44
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM45
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE4
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM46
	.byte	0x6f
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM47
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM48
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM49
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM50
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM51
	.byte	0xc
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM52
	.byte	0x1e
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM53
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM54
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM55
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM56
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM57
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM58
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM59
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM60
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM61
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM62
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM63
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM64
	.byte	0x3
	.sleb128 -14
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM65
	.byte	0x24
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM66
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM67
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM68
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM69
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM70
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE5
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM71
	.byte	0x90
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM72
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM73
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM74
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM75
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM76
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM77
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM78
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM79
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM80
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM81
	.byte	0x3
	.sleb128 -12
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM82
	.byte	0x22
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM83
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM84
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM85
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM86
	.byte	0x10
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM87
	.byte	0x1b
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM88
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM89
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM90
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM91
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM92
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM93
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM94
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM95
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM96
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM97
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE6
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM98
	.byte	0xb6
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM99
	.byte	0x1a
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM100
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM101
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM102
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM103
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM104
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM105
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM106
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM107
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM108
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM109
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM110
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM111
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM112
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM113
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM114
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM115
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM116
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM117
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM118
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM119
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM120
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM121
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM122
	.byte	0x20
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM123
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM124
	.byte	0xd
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM125
	.byte	0x1d
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE7
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
.LELT0:
	.section	.debug_str,info
.LASF0:
	.asciz	"LATBbits"
.LASF2:
	.asciz	"LATCbits"
.LASF1:
	.asciz	"PORTCbits"
	.section	.text,code

	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
