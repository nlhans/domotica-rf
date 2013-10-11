	.file "C:\\Projects\\Firmware\\MRF49XA\\Library\\targets\\mrf49xa_pic24\\..\\..\\src\\devices\\mcp9800.c"
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
	.global	_Mcp9800Start	; export
	.type	_Mcp9800Start,@function
_Mcp9800Start:
.LFB0:
.LSM0:
	.set ___PA___,1
	mov	w8,[w15++]
	mov	w0,w8
.LSM1:
	rcall	_SoftI2cStart
.LSM2:
	mov.b	#-112,w0
	rcall	_SoftI2cTxByte
.LSM3:
	mov.b	#1,w0
	rcall	_SoftI2cTxByte
.LSM4:
	mov.b	w8,w0
	rcall	_SoftI2cTxByte
.LSM5:
	rcall	_SoftI2cStop
.LSM6:
	rcall	_SoftI2cStart
.LSM7:
	mov.b	#-112,w0
	rcall	_SoftI2cTxByte
.LSM8:
	clr.b	w0
	rcall	_SoftI2cTxByte
.LSM9:
	rcall	_SoftI2cStop
.LSM10:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE0:
	.align	2
	.global	_Mcp9800Read	; export
	.type	_Mcp9800Read,@function
_Mcp9800Read:
.LFB1:
.LSM11:
	.set ___PA___,1
	mov.d	w8,[w15++]
.LSM12:
	rcall	_SoftI2cStart
.LSM13:
	mov.b	#-111,w0
	rcall	_SoftI2cTxByte
.LSM14:
	mov.b	#1,w0
	rcall	_SoftI2cRxByte
	mov.b	w0,w9
.LSM15:
	clr.b	w0
	rcall	_SoftI2cRxByte
	mov.b	w0,w8
.LSM16:
	rcall	_SoftI2cStop
.LSM17:
	sl	w9,#8,w0
	ze	w8,w8
	ior	w0,w8,w0
.LSM18:
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE1:
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
	.section	.text,code
.Letext0:
	.section	.debug_info,info
	.4byte	0x269
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1_11) (A) Build date: Nov 17 2012"
	.byte	0x1
	.asciz	"../../src/devices/mcp9800.c"
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
	.asciz	"UI08_t"
	.byte	0x2
	.byte	0x66
	.4byte	0x124
	.uleb128 0x3
	.asciz	"UI16_t"
	.byte	0x2
	.byte	0x67
	.4byte	0xb6
	.uleb128 0x4
	.asciz	"Mcp9800Resolution_e"
	.byte	0x2
	.byte	0x3
	.byte	0x6
	.4byte	0x1de
	.uleb128 0x5
	.asciz	"Mcp9800_9bit"
	.sleb128 0
	.uleb128 0x5
	.asciz	"Mcp9800_10bit"
	.sleb128 32
	.uleb128 0x5
	.asciz	"Mcp9800_11bit"
	.sleb128 64
	.uleb128 0x5
	.asciz	"Mcp9800_12bit"
	.sleb128 96
	.byte	0x0
	.uleb128 0x3
	.asciz	"Mcp9800Resolution_t"
	.byte	0x3
	.byte	0xc
	.4byte	0x180
	.uleb128 0x6
	.byte	0x1
	.asciz	"Mcp9800Start"
	.byte	0x1
	.byte	0x4
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.4byte	0x22e
	.uleb128 0x7
	.asciz	"resolution"
	.byte	0x1
	.byte	0x4
	.4byte	0x1de
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x8
	.byte	0x1
	.asciz	"Mcp9800Read"
	.byte	0x1
	.byte	0x13
	.byte	0x1
	.4byte	0x172
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.uleb128 0x9
	.asciz	"tempH"
	.byte	0x1
	.byte	0x1a
	.4byte	0x164
	.byte	0x1
	.byte	0x59
	.uleb128 0x9
	.asciz	"tempL"
	.byte	0x1
	.byte	0x1b
	.4byte	0x164
	.byte	0x1
	.byte	0x58
	.byte	0x0
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
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x2f
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x26d
	.4byte	0x1f9
	.asciz	"Mcp9800Start"
	.4byte	0x22e
	.asciz	"Mcp9800Read"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x54
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x26d
	.4byte	0x164
	.asciz	"UI08_t"
	.4byte	0x172
	.asciz	"UI16_t"
	.4byte	0x180
	.asciz	"Mcp9800Resolution_e"
	.4byte	0x1de
	.asciz	"Mcp9800Resolution_t"
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
	.ascii	"C:/Projects/Firmware/MRF49XA/Library/inc/devices"
	.byte 0
	.byte	0x0
	.asciz	"mcp9800.c"
	.uleb128 0x1
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"bspPIC24.h"
	.uleb128 0x2
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"devices/mcp9800.h"
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
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM1
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM2
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM3
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM4
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM5
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM6
	.byte	0x16
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
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM10
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
	.4byte	.LSM11
	.byte	0x27
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM12
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM13
	.byte	0x18
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM18
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE1
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
.LELT0:
	.section	.debug_str,info
	.section	.text,code

	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
