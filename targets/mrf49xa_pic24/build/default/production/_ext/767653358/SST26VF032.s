	.file "C:\\Projects\\Firmware\\MRF49XA\\Library\\targets\\mrf49xa_pic24\\..\\..\\src\\devices\\SST26VF032.c"
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
	.global	_FlashCsSet	; export
	.type	_FlashCsSet,@function
_FlashCsSet:
.LFB1:
.LSM0:
	.set ___PA___,1
.LSM1:
	sub.b	w2,#1,[w15]
	.set ___BP___,80
	bra	nz,.L2
.LSM2:
	mov	#129,w0
	ior	_LATA
	return	
.L2:
.LSM3:
	mov	#65535,w2
	mov	#63,w3
	sub	w0,w2,[w15]
	subb	w1,w3,[w15]
	.set ___BP___,61
	bra	gtu,.L4
.LSM4:
	bclr.b	_LATA,#0
	return	
.L4:
.LSM5:
	bclr.b	_LATA,#7
	return	
.LFE1:
	.align	2
	.global	_FlashInit	; export
	.type	_FlashInit,@function
_FlashInit:
.LFB0:
.LSM6:
	.set ___PA___,0
.LSM7:
	bclr.b	_TRISC,#1
.LSM8:
	bclr.b	_TRISB+1,#13-8
.LSM9:
	bset.b	_LATB+1,#13-8
.LSM10:
	bset.b	_LATC,#1
.LSM11:
	mov.b	#1,w2
	mul.uu	w0,#0,w0
	rcall	_FlashCsSet
.LSM12:
	mov.b	#2,w0
	rcall	_spiInit
.LSM13:
	mov.b	#1,w2
	mul.uu	w0,#0,w0
	rcall	_FlashCsSet
.LSM14:
; 15 "../../src/devices/SST26VF032.c" 1
	nop
.LSM15:
	clr.b	w2
	mul.uu	w0,#0,w0
	rcall	_FlashCsSet
.LSM16:
	mov.b	#56,w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM17:
	mov.b	#1,w2
	mul.uu	w0,#0,w0
	rcall	_FlashCsSet
.LSM18:
	mov.b	#2,w0
	bra	_sqiEnable
.LSM19:
	.set ___PA___,0
.LFE0:
	.align	2
	.global	_FlashReadId	; export
	.type	_FlashReadId,@function
_FlashReadId:
.LFB2:
.LSM20:
	.set ___PA___,1
.LSM21:
	clr.b	w2
	mul.uu	w0,#0,w0
	rcall	_FlashCsSet
.LSM22:
	mov.b	#-81,w1
	mov.b	#2,w0
	rcall	_sqiTxByte
.LSM23:
	mov.b	#2,w0
	rcall	_sqiRxByte
	mov.b	WREG,_flashChipId
.LSM24:
	mov.b	#2,w0
	rcall	_sqiRxByte
	mov.b	WREG,_flashChipId+1
.LSM25:
	mov.b	#2,w0
	rcall	_sqiRxByte
	mov.b	WREG,_flashChipId+2
.LSM26:
	mov.b	#1,w2
	mul.uu	w0,#0,w0
	rcall	_FlashCsSet
.LSM27:
	mov	#_flashChipId,w0
	return	
	.set ___PA___,0
.LFE2:
	.align	2
	.global	_FlashRxByte	; export
	.type	_FlashRxByte,@function
_FlashRxByte:
.LFB3:
.LSM28:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov	w10,[w15++]
	mov.d	w0,w8
.LSM29:
	mov.b	#2,w0
	rcall	_sqiDisable
.LSM30:
	clr.b	w2
	mov.d	w8,w0
	rcall	_FlashCsSet
.LSM31:
	mov.b	#3,w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM32:
	lsr	w9,#0,w0
	mov	#0,w1
	mov.b	w0,w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM33:
	sl	w9,#8,w2
	lsr	w8,#8,w0
	ior	w2,w0,w0
	lsr	w9,#8,w1
	mov.b	w0,w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM34:
	mov.b	w8,w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM35:
	mov.b	#2,w0
	rcall	_spiRxByte
	mov.b	w0,w10
.LSM36:
	mov.b	#1,w2
	mov.d	w8,w0
	rcall	_FlashCsSet
.LSM37:
	mov.b	#2,w0
	rcall	_sqiEnable
.LSM38:
	mov.b	w10,w0
	mov	[--w15],w10
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE3:
	.align	2
	.global	_FlashRxBytes	; export
	.type	_FlashRxBytes,@function
_FlashRxBytes:
.LFB4:
.LSM39:
	.set ___PA___,1
	lnk	#2
	mov.d	w8,[w15++]
	mov	w10,[w15++]
	mov.d	w0,w8
	mov	w2,w10
.LSM40:
	mov.b	#2,w0
	mov	w3,[w15-8]
	rcall	_sqiDisable
.LSM41:
	clr.b	w2
	mov.d	w8,w0
	rcall	_FlashCsSet
.LSM42:
	mov.b	#11,w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM43:
	lsr	w9,#0,w0
	mov	#0,w1
	mov.b	w0,w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM44:
	sl	w9,#8,w2
	lsr	w8,#8,w0
	ior	w2,w0,w0
	lsr	w9,#8,w1
	mov.b	w0,w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM45:
	mov.b	w8,w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM46:
	clr.b	w1
	mov.b	#2,w0
	rcall	_spiTxByte
.LSM47:
	mov	[w15-8],w3
	mov	w10,w2
	clr	w1
	mov.b	#2,w0
	rcall	_spiTxRxBytes
.LSM48:
	mov.b	#1,w2
	mov.d	w8,w0
	rcall	_FlashCsSet
.LSM49:
	mov.b	#2,w0
	rcall	_sqiEnable
.LSM50:
	mov	[--w15],w10
	mov.d	[--w15],w8
	ulnk	
	return	
	.set ___PA___,0
.LFE4:
	.align	2
	.global	_FlashTxBytes	; export
	.type	_FlashTxBytes,@function
_FlashTxBytes:
.LFB5:
.LSM51:
	.set ___PA___,0
	lnk	#2
	mov	w8,[w15++]
	mov.d	w10,[w15++]
	mov.d	w0,w10
	mov	w2,w8
.LSM52:
	clr.b	w2
	mov	w3,[w15-8]
	rcall	_FlashCsSet
.LSM53:
	mov.b	#6,w1
	mov.b	#2,w0
	rcall	_sqiTxByte
.LSM54:
	mov.b	#1,w2
	mov.d	w10,w0
	rcall	_FlashCsSet
.LSM55:
; 98 "../../src/devices/SST26VF032.c" 1
	nop
.LSM56:
	clr.b	w2
	mov.d	w10,w0
	rcall	_FlashCsSet
.LSM57:
	mov.b	#2,w1
	mov.b	w1,w0
	rcall	_sqiTxByte
.LSM58:
	lsr	w11,#0,w4
	mov	#0,w5
	mov.b	w4,w1
	mov.b	#2,w0
	rcall	_sqiTxByte
.LSM59:
	sl	w11,#8,w0
	lsr	w10,#8,w4
	ior	w0,w4,w4
	lsr	w11,#8,w5
	mov.b	w4,w1
	mov.b	#2,w0
	rcall	_sqiTxByte
.LSM60:
	mov.b	w10,w1
	mov.b	#2,w0
	rcall	_sqiTxByte
.LSM61:
	mov	[w15-8],w3
	clr	w2
	mov	w8,w1
	mov.b	#2,w0
	rcall	_sqiTxRxBytes
.LSM62:
	mov.b	#1,w2
	mov.d	w10,w0
	rcall	_FlashCsSet
.LSM63:
	mov.d	[--w15],w10
	mov	[--w15],w8
	ulnk	
	return	
	.set ___PA___,0
.LFE5:
	.align	2
	.global	_FlashEraseSector	; export
	.type	_FlashEraseSector,@function
_FlashEraseSector:
.LFB6:
.LSM64:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov.d	w0,w8
.LSM65:
	clr.b	w2
	rcall	_FlashCsSet
.LSM66:
	mov.b	#32,w1
	mov.b	#2,w0
	rcall	_sqiTxByte
.LSM67:
	lsr	w9,#0,w0
	mov	#0,w1
	mov.b	w0,w1
	mov.b	#2,w0
	rcall	_sqiTxByte
.LSM68:
	sl	w9,#8,w2
	lsr	w8,#8,w0
	ior	w2,w0,w0
	lsr	w9,#8,w1
	mov.b	w0,w1
	mov.b	#2,w0
	rcall	_sqiTxByte
.LSM69:
	mov.b	w8,w1
	mov.b	#2,w0
	rcall	_sqiTxByte
.LSM70:
	mov.b	#1,w2
	mov.d	w8,w0
	rcall	_FlashCsSet
.LSM71:
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE6:
	.section	.nbss,bss,near
	.type	_flashChipId,@object
	.global	_flashChipId
_flashChipId:	.space	3
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
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
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
	.section	.text,code
.Letext0:
	.section	.debug_info,info
	.4byte	0x40b
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1_11) (A) Build date: Nov 17 2012"
	.byte	0x1
	.asciz	"../../src/devices/SST26VF032.c"
	.ascii	"C:\\\\Projects\\\\Firmware\\\\MRF49XA\\\\Library\\\\targets\\\\mrf49"
	.asciz	"xa_pic24"
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.asciz	"unsigned int"
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
	.uleb128 0x3
	.asciz	"bool_t"
	.byte	0x2
	.byte	0x65
	.4byte	0x127
	.uleb128 0x3
	.asciz	"UI08_t"
	.byte	0x2
	.byte	0x66
	.4byte	0x127
	.uleb128 0x3
	.asciz	"UI16_t"
	.byte	0x2
	.byte	0x67
	.4byte	0xb9
	.uleb128 0x3
	.asciz	"UI32_t"
	.byte	0x2
	.byte	0x68
	.4byte	0x138
	.uleb128 0x4
	.byte	0x1
	.asciz	"FlashCsSet"
	.byte	0x1
	.byte	0x18
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.4byte	0x1e0
	.uleb128 0x5
	.asciz	"addr"
	.byte	0x1
	.byte	0x18
	.4byte	0x191
	.byte	0x6
	.byte	0x50
	.byte	0x93
	.uleb128 0x2
	.byte	0x51
	.byte	0x93
	.uleb128 0x2
	.uleb128 0x5
	.asciz	"state"
	.byte	0x1
	.byte	0x18
	.4byte	0x167
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.uleb128 0x6
	.byte	0x1
	.asciz	"FlashInit"
	.byte	0x1
	.byte	0x3
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.uleb128 0x7
	.byte	0x1
	.asciz	"FlashReadId"
	.byte	0x1
	.byte	0x2e
	.byte	0x1
	.4byte	0x218
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.uleb128 0x8
	.byte	0x2
	.4byte	0x175
	.uleb128 0x9
	.byte	0x1
	.asciz	"FlashRxByte"
	.byte	0x1
	.byte	0x3a
	.byte	0x1
	.4byte	0x175
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.4byte	0x263
	.uleb128 0x5
	.asciz	"addr"
	.byte	0x1
	.byte	0x3a
	.4byte	0x191
	.byte	0x6
	.byte	0x58
	.byte	0x93
	.uleb128 0x2
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.uleb128 0xa
	.asciz	"data"
	.byte	0x1
	.byte	0x44
	.4byte	0x175
	.byte	0x1
	.byte	0x5a
	.byte	0x0
	.uleb128 0x4
	.byte	0x1
	.asciz	"FlashRxBytes"
	.byte	0x1
	.byte	0x4a
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.4byte	0x2b1
	.uleb128 0x5
	.asciz	"addr"
	.byte	0x1
	.byte	0x4a
	.4byte	0x191
	.byte	0x6
	.byte	0x58
	.byte	0x93
	.uleb128 0x2
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.uleb128 0x5
	.asciz	"bf"
	.byte	0x1
	.byte	0x4a
	.4byte	0x218
	.byte	0x1
	.byte	0x5a
	.uleb128 0x5
	.asciz	"size"
	.byte	0x1
	.byte	0x4a
	.4byte	0x183
	.byte	0x1
	.byte	0x53
	.byte	0x0
	.uleb128 0x4
	.byte	0x1
	.asciz	"FlashTxBytes"
	.byte	0x1
	.byte	0x5a
	.byte	0x1
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.4byte	0x308
	.uleb128 0x5
	.asciz	"addr"
	.byte	0x1
	.byte	0x5a
	.4byte	0x191
	.byte	0x6
	.byte	0x5a
	.byte	0x93
	.uleb128 0x2
	.byte	0x5b
	.byte	0x93
	.uleb128 0x2
	.uleb128 0x5
	.asciz	"bf"
	.byte	0x1
	.byte	0x5a
	.4byte	0x218
	.byte	0x1
	.byte	0x58
	.uleb128 0x5
	.asciz	"size"
	.byte	0x1
	.byte	0x5a
	.4byte	0x183
	.byte	0x1
	.byte	0x53
	.uleb128 0xb
	.asciz	"i"
	.byte	0x1
	.byte	0x5c
	.4byte	0x183
	.byte	0x0
	.uleb128 0x4
	.byte	0x1
	.asciz	"FlashEraseSector"
	.byte	0x1
	.byte	0x71
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.4byte	0x340
	.uleb128 0x5
	.asciz	"addr"
	.byte	0x1
	.byte	0x71
	.4byte	0x191
	.byte	0x6
	.byte	0x58
	.byte	0x93
	.uleb128 0x2
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x0
	.uleb128 0xc
	.asciz	"LATA"
	.byte	0x3
	.2byte	0x805
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0xd
	.4byte	0xb9
	.uleb128 0xc
	.asciz	"TRISB"
	.byte	0x3
	.2byte	0x823
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"LATB"
	.byte	0x3
	.2byte	0x84d
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"TRISC"
	.byte	0x3
	.2byte	0x877
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"LATC"
	.byte	0x3
	.2byte	0x895
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.4byte	0x175
	.4byte	0x3a2
	.uleb128 0xf
	.4byte	0xb9
	.byte	0x2
	.byte	0x0
	.uleb128 0x10
	.4byte	.LASF0
	.byte	0x1
	.byte	0x2d
	.4byte	0x392
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"LATA"
	.byte	0x3
	.2byte	0x805
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"TRISB"
	.byte	0x3
	.2byte	0x823
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"LATB"
	.byte	0x3
	.2byte	0x84d
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"TRISC"
	.byte	0x3
	.2byte	0x877
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"LATC"
	.byte	0x3
	.2byte	0x895
	.4byte	0x34f
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF0
	.byte	0x1
	.byte	0x2d
	.4byte	0x392
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	_flashChipId
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
	.uleb128 0x4
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
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0xd
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x92
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x40f
	.4byte	0x19f
	.asciz	"FlashCsSet"
	.4byte	0x1e0
	.asciz	"FlashInit"
	.4byte	0x1f9
	.asciz	"FlashReadId"
	.4byte	0x21e
	.asciz	"FlashRxByte"
	.4byte	0x263
	.asciz	"FlashRxBytes"
	.4byte	0x2b1
	.asciz	"FlashTxBytes"
	.4byte	0x308
	.asciz	"FlashEraseSector"
	.4byte	0x3fc
	.asciz	"flashChipId"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x3a
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x40f
	.4byte	0x167
	.asciz	"bool_t"
	.4byte	0x175
	.asciz	"UI08_t"
	.4byte	0x183
	.asciz	"UI16_t"
	.4byte	0x191
	.asciz	"UI32_t"
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
	.asciz	"SST26VF032.c"
	.uleb128 0x1
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"bspPIC24.h"
	.uleb128 0x2
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"p24FJ64GB004.h"
	.uleb128 0x3
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
	.byte	0x2c
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM1
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM2
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM3
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM4
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM5
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
	.4byte	.LSM6
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM7
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM8
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM9
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM10
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM11
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM12
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM13
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM14
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM15
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM16
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM17
	.byte	0x15
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
	.4byte	.LFE0
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM20
	.byte	0x42
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM21
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM22
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM23
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM24
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM25
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM26
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM27
	.byte	0x17
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
	.4byte	.LSM28
	.byte	0x4e
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM32
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM33
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM34
	.byte	0x15
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM38
	.byte	0x16
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
	.4byte	.LSM39
	.byte	0x5e
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
	.byte	0x16
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
	.4byte	.LSM46
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM47
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM48
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM49
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM50
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
	.4byte	.LSM51
	.byte	0x6e
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM52
	.byte	0x17
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM56
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM57
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM58
	.byte	0x16
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM62
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM63
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
	.4byte	.LSM64
	.byte	0x85
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM65
	.byte	0x16
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
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM70
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM71
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE6
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
.LELT0:
	.section	.debug_str,info
.LASF0:
	.asciz	"flashChipId"
	.section	.text,code

	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
