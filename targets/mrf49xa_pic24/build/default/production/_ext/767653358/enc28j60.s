	.file "C:\\Projects\\Firmware\\MRF49XA\\Library\\targets\\mrf49xa_pic24\\..\\..\\src\\devices\\enc28j60.c"
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
	.global	_enc28j60WriteUint8	; export
	.type	_enc28j60WriteUint8,@function
_enc28j60WriteUint8:
.LFB0:
.LSM0:
	.set ___PA___,0
	mov	w8,[w15++]
	mov.b	w1,w8
.LSM1:
; 47 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM2:
	and.b	w0,#31,w0
	bset.b	w0,#6
	mov.b	w0,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM3:
	mov.b	w8,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM4:
; 50 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM5:
; 52 "../../src/devices/enc28j60.c" 1
	nop
.LSM6:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE0:
	.align	2
	.global	_enc28j60BitSetUint8	; export
	.type	_enc28j60BitSetUint8,@function
_enc28j60BitSetUint8:
.LFB1:
.LSM7:
	.set ___PA___,0
	mov	w8,[w15++]
	mov.b	w1,w8
.LSM8:
; 56 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM9:
	and.b	w0,#31,w0
	bset.b	w0,#7
	mov.b	w0,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM10:
	mov.b	w8,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM11:
; 59 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM12:
; 61 "../../src/devices/enc28j60.c" 1
	nop
.LSM13:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE1:
	.align	2
	.global	_enc28j60BitClrUint8	; export
	.type	_enc28j60BitClrUint8,@function
_enc28j60BitClrUint8:
.LFB2:
.LSM14:
	.set ___PA___,0
	mov	w8,[w15++]
	mov.b	w1,w8
.LSM15:
; 65 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM16:
	and.b	w0,#31,w1
	mov.b	#-96,w2
	ior.b	w1,w2,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM17:
	mov.b	w8,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM18:
; 68 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM19:
; 70 "../../src/devices/enc28j60.c" 1
	nop
.LSM20:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE2:
	.align	2
	.global	_enc28j60WriteUint16	; export
	.type	_enc28j60WriteUint16,@function
_enc28j60WriteUint16:
.LFB3:
.LSM21:
	.set ___PA___,0
	mov	w8,[w15++]
	mov	w1,w8
.LSM22:
; 75 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM23:
	and.b	w0,#31,w0
	bset.b	w0,#6
	mov.b	w0,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM24:
	mov.b	w8,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM25:
	lsr	w8,#8,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM26:
; 79 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM27:
; 81 "../../src/devices/enc28j60.c" 1
	nop
.LSM28:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE3:
	.align	2
	.global	_enc28j60ReadUint8	; export
	.type	_enc28j60ReadUint8,@function
_enc28j60ReadUint8:
.LFB4:
.LSM29:
	.set ___PA___,0
	mov	w8,[w15++]
	mov.b	w0,w8
.LSM30:
; 87 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM31:
	and.b	w8,#31,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM32:
	mov.b	#1,w0
	rcall	_spiRxByte
.LSM33:
; 90 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM34:
	mov.b	#-100,w1
	sub.b	w8,w1,[w15]
	.set ___BP___,19
	bra	z,.L6
.LSM35:
; 93 "../../src/devices/enc28j60.c" 1
	nop
.L6:
.LSM36:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE4:
	.align	2
	.global	_enc28j60ReadMacUint8	; export
	.type	_enc28j60ReadMacUint8,@function
_enc28j60ReadMacUint8:
.LFB5:
.LSM37:
	.set ___PA___,0
.LSM38:
; 101 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM39:
	and.b	w0,#31,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM40:
	clr.b	w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM41:
	mov.b	#1,w0
	rcall	_spiRxByte
.LSM42:
; 105 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM43:
; 107 "../../src/devices/enc28j60.c" 1
	nop
.LSM44:
	return	
	.set ___PA___,0
.LFE5:
	.align	2
	.global	_enc28j60ReadUint16	; export
	.type	_enc28j60ReadUint16,@function
_enc28j60ReadUint16:
.LFB6:
.LSM45:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov.b	w0,w8
.LSM46:
	mov.b	w8,w0
	rcall	_enc28j60ReadUint8
	ze	w0,w9
.LSM47:
	inc.b	w8,w0
	rcall	_enc28j60ReadUint8
	sl	w0,#8,w0
	ior	w0,w9,w0
.LSM48:
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE6:
	.align	2
	.global	_enc28j60SetBank	; export
	.type	_enc28j60SetBank,@function
_enc28j60SetBank:
.LFB7:
.LSM49:
	.set ___PA___,0
	mov	w8,[w15++]
	mov.b	w0,w8
.LSM50:
	mov.b	_currentBank,WREG
	.set ___BP___,71
	bra	z,.L10
.LSM51:
; 125 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM52:
	mov.b	#-65,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM53:
	mov.b	#3,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM54:
; 128 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.L10:
.LSM55:
	lsr	w8,#5,w0
	and	w0,#3,w0
	mov.b	WREG,_currentBank
.LSM56:
	sub.b	w0,#0,[w15]
	.set ___BP___,61
	bra	z,.L9
.LSM57:
; 134 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM58:
	mov.b	#-97,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM59:
	mov	#_currentBank,w1
	mov.b	[w1],w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM60:
; 137 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.L9:
.LSM61:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE7:
	.align	2
	.global	_enc28j60WriteData	; export
	.type	_enc28j60WriteData,@function
_enc28j60WriteData:
.LFB8:
.LSM62:
	.set ___PA___,0
	lnk	#2
	mov	w8,[w15++]
	mov	w1,w8
	mov	w2,w3
.LSM63:
; 146 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM64:
	mov.b	#122,w1
	mov.b	#1,w0
	mov	w3,[w15-4]
	rcall	_spiTxByte
.LSM65:
	mov	[w15-4],w3
	clr	w2
	mov	w8,w1
	mov.b	#1,w0
	rcall	_spiTxRxBytes
.LSM66:
; 149 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM67:
	mov	[--w15],w8
	ulnk	
	return	
	.set ___PA___,0
.LFE8:
	.align	2
	.global	_enc28j60ReadRegisterUint8	; export
	.type	_enc28j60ReadRegisterUint8,@function
_enc28j60ReadRegisterUint8:
.LFB10:
.LSM68:
	.set ___PA___,1
	mov	w8,[w15++]
	mov.b	w0,w8
.LSM69:
	sub.b	w8,#0,[w15]
	.set ___BP___,39
	bra	lt,.L14
.LSM70:
	lsr	w8,#5,w1
	and	w1,#3,w1
	mov.b	_currentBank,WREG
	ze	w0,w0
	sub	w1,w0,[w15]
	.set ___BP___,37
	bra	z,.L14
.LSM71:
	mov.b	w8,w0
	rcall	_enc28j60SetBank
.L14:
.LSM72:
	mov.b	w8,w0
	rcall	_enc28j60ReadUint8
.LSM73:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE10:
	.align	2
	.global	_enc28j60ReadRegisterUint16	; export
	.type	_enc28j60ReadRegisterUint16,@function
_enc28j60ReadRegisterUint16:
.LFB11:
.LSM74:
	.set ___PA___,1
	mov	w8,[w15++]
	mov.b	w0,w8
.LSM75:
	sub.b	w8,#0,[w15]
	.set ___BP___,39
	bra	lt,.L16
.LSM76:
	lsr	w8,#5,w1
	and	w1,#3,w1
	mov.b	_currentBank,WREG
	ze	w0,w0
	sub	w1,w0,[w15]
	.set ___BP___,37
	bra	z,.L16
.LSM77:
	mov.b	w8,w0
	rcall	_enc28j60SetBank
.L16:
.LSM78:
	mov.b	w8,w0
	rcall	_enc28j60ReadUint16
.LSM79:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE11:
	.align	2
	.global	_enc28j60WriteRegisterUint8	; export
	.type	_enc28j60WriteRegisterUint8,@function
_enc28j60WriteRegisterUint8:
.LFB12:
.LSM80:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov.b	w0,w8
	mov.b	w1,w9
.LSM81:
	sub.b	w8,#0,[w15]
	.set ___BP___,39
	bra	lt,.L18
.LSM82:
	lsr	w8,#5,w1
	and	w1,#3,w1
	mov.b	_currentBank,WREG
	ze	w0,w0
	sub	w1,w0,[w15]
	.set ___BP___,37
	bra	z,.L18
.LSM83:
	mov.b	w8,w0
	rcall	_enc28j60SetBank
.L18:
.LSM84:
	mov.b	w9,w1
	mov.b	w8,w0
	rcall	_enc28j60WriteUint8
.LSM85:
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE12:
	.align	2
	.global	_enc28j60BitSetRegisterUint8	; export
	.type	_enc28j60BitSetRegisterUint8,@function
_enc28j60BitSetRegisterUint8:
.LFB13:
.LSM86:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov.b	w0,w8
	mov.b	w1,w9
.LSM87:
	sub.b	w8,#0,[w15]
	.set ___BP___,39
	bra	lt,.L20
.LSM88:
	lsr	w8,#5,w1
	and	w1,#3,w1
	mov.b	_currentBank,WREG
	ze	w0,w0
	sub	w1,w0,[w15]
	.set ___BP___,37
	bra	z,.L20
.LSM89:
	mov.b	w8,w0
	rcall	_enc28j60SetBank
.L20:
.LSM90:
	mov.b	w9,w1
	mov.b	w8,w0
	rcall	_enc28j60BitSetUint8
.LSM91:
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE13:
	.align	2
	.global	_enc28j60BitClrRegisterUint8	; export
	.type	_enc28j60BitClrRegisterUint8,@function
_enc28j60BitClrRegisterUint8:
.LFB14:
.LSM92:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov.b	w0,w8
	mov.b	w1,w9
.LSM93:
	sub.b	w8,#0,[w15]
	.set ___BP___,39
	bra	lt,.L22
.LSM94:
	lsr	w8,#5,w1
	and	w1,#3,w1
	mov.b	_currentBank,WREG
	ze	w0,w0
	sub	w1,w0,[w15]
	.set ___BP___,37
	bra	z,.L22
.LSM95:
	mov.b	w8,w0
	rcall	_enc28j60SetBank
.L22:
.LSM96:
	mov.b	w9,w1
	mov.b	w8,w0
	rcall	_enc28j60BitClrUint8
.LSM97:
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE14:
	.align	2
	.global	_enc28j60WriteRegisterUint16	; export
	.type	_enc28j60WriteRegisterUint16,@function
_enc28j60WriteRegisterUint16:
.LFB15:
.LSM98:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov.b	w0,w8
	mov	w1,w9
.LSM99:
	sub.b	w8,#0,[w15]
	.set ___BP___,39
	bra	lt,.L24
.LSM100:
	lsr	w8,#5,w1
	and	w1,#3,w1
	mov.b	_currentBank,WREG
	ze	w0,w0
	sub	w1,w0,[w15]
	.set ___BP___,37
	bra	z,.L24
.LSM101:
	mov.b	w8,w0
	rcall	_enc28j60SetBank
.L24:
.LSM102:
	mov.b	w9,w1
	mov.b	w8,w0
	rcall	_enc28j60WriteUint8
.LSM103:
	lsr	w9,#8,w1
	inc.b	w8,w0
	rcall	_enc28j60WriteUint8
.LSM104:
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE15:
	.align	2
	.global	_enc28j60ReadData	; export
	.type	_enc28j60ReadData,@function
_enc28j60ReadData:
.LFB9:
.LSM105:
	.set ___PA___,0
	lnk	#2
	mov	w8,[w15++]
	mov	w1,w8
	mov	w2,w3
.LSM106:
	mov	w0,w1
	clr.b	w0
	mov	w3,[w15-4]
	rcall	_enc28j60WriteRegisterUint16
.LSM107:
; 157 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM108:
	mov.b	#58,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM109:
	mov	[w15-4],w3
	mov	w8,w2
	clr	w1
	mov.b	#1,w0
	rcall	_spiTxRxBytes
.LSM110:
; 160 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM111:
	mov	[--w15],w8
	ulnk	
	return	
	.set ___PA___,0
.LFE9:
	.align	2
	.global	_enc28j60WritePhyRegisterUint16	; export
	.type	_enc28j60WritePhyRegisterUint16,@function
_enc28j60WritePhyRegisterUint16:
.LFB16:
.LSM112:
	.set ___PA___,1
	mov	w8,[w15++]
	mov	w1,w8
.LSM113:
	mov.b	w0,w1
	mov.b	#84,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM114:
	mov	w8,w1
	mov.b	#86,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM115:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE16:
	.align	2
	.global	_enc28j60ReadPhyRegisterUint16	; export
	.type	_enc28j60ReadPhyRegisterUint16,@function
_enc28j60ReadPhyRegisterUint16:
.LFB17:
.LSM116:
	.set ___PA___,0
	mov.d	w8,[w15++]
.LSM117:
	mov.b	w0,w1
	mov.b	#84,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM118:
	mov.b	#1,w1
	mov.b	#82,w0
	rcall	_enc28j60BitSetRegisterUint8
.L28:
.LSM119:
	mov.b	#106,w0
	rcall	_enc28j60ReadMacUint8
	and	w0,#1,w8
	.set ___BP___,91
	bra	nz,.L28
.LSM120:
	mov.b	#1,w1
	mov.b	#82,w0
	rcall	_enc28j60BitClrRegisterUint8
.LSM121:
; 268 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM122:
	mov.b	#24,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM123:
	mov.b	w8,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM124:
	mov.b	#1,w0
	rcall	_spiRxByte
	ze	w0,w9
.LSM125:
; 273 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM126:
; 277 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM127:
	mov.b	#25,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM128:
	mov.b	w8,w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM129:
	mov.b	#1,w0
	rcall	_spiRxByte
.LSM130:
; 281 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM131:
	sl	w0,#8,w0
	ior	w0,w9,w0
.LSM132:
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE17:
	.align	2
	.global	_enc28j60TxFrame	; export
	.type	_enc28j60TxFrame,@function
_enc28j60TxFrame:
.LFB19:
.LSM133:
	.set ___PA___,0
	mov.d	w8,[w15++]
	mov	w10,[w15++]
	mov	w0,w10
	mov	w1,w8
.LSM134:
	bra	.L31
.L32:
.LSM135:
	mov.b	#8,w1
	mov.b	#-97,w0
	rcall	_enc28j60BitSetRegisterUint8
.LSM136:
	mov.b	#8,w1
	mov.b	#-97,w0
	rcall	_enc28j60BitClrRegisterUint8
.L31:
.LSM137:
	mov.b	#-97,w0
	rcall	_enc28j60ReadRegisterUint8
	and	w0,#8,w0
	.set ___BP___,91
	bra	nz,.L32
.LSM138:
	mov	#4096,w1
	mov.b	#2,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM139:
	mov	#4096,w9
	add	w8,w9,w3
	mov	w3,w1
	mov.b	#6,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM140:
	mov	#1,w2
	mov	#_controlByte.6745,w1
	mov	w9,w0
	rcall	_enc28j60WriteData
.LSM141:
	mov	w8,w2
	mov	w10,w1
	mov	#4097,w0
	rcall	_enc28j60WriteData
.LSM142:
	mov.b	#10,w1
	mov.b	#-100,w0
	rcall	_enc28j60BitClrRegisterUint8
.LSM143:
	mov.b	#8,w1
	mov.b	#-97,w0
	rcall	_enc28j60BitSetRegisterUint8
.L33:
.LSM144:
	mov.b	#-100,w0
	rcall	_enc28j60ReadRegisterUint8
	and	w0,#8,w0
	.set ___BP___,91
	bra	z,.L33
.LSM145:
; 395 "../../src/devices/enc28j60.c" 1
	nop
.LSM146:
	mov	[--w15],w10
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE19:
	.align	2
	.global	_enc28j60TxReplyFrame	; export
	.type	_enc28j60TxReplyFrame,@function
_enc28j60TxReplyFrame:
.LFB20:
.LSM147:
	.set ___PA___,1
	lnk	#6
.LSM148:
	mov.d	[w0],w2
	mov	w2,[w15-6]
	mov	w3,[w15-4]
	mov	[w0+4],w3
	mov	w3,[w15-2]
.LSM149:
	add	w0,#6,w2
	mov.d	[w2],w4
	mov.d	w4,[w0]
	mov	[w0+10],w2
	mov	w2,[w0+4]
.LSM150:
	mov	[w15-6],w2
	mov	[w15-4],w3
	mov	w2,[w0+6]
	mov	w3,[w0+8]
	mov	[w15-2],w3
	mov	w3,[w0+10]
.LSM151:
	add	w1,#14,w1
	rcall	_enc28j60TxFrame
.LSM152:
	ulnk	
	return	
	.set ___PA___,0
.LFE20:
	.align	2
	.global	_enc28j60PacketPending	; export
	.type	_enc28j60PacketPending,@function
_enc28j60PacketPending:
.LFB22:
.LSM153:
	.set ___PA___,1
.LSM154:
	mov.b	#-100,w0
	rcall	_enc28j60ReadRegisterUint8
	mov	w0,w1
	and	#64,w1
	mov.b	#1,w0
	.set ___BP___,79
	bclr.b	_SR,#2
	bra	gt,.L37
	clr.b	w0
.L37:
.LSM155:
	return	
.LFE22:
	.align	2
	.global	_enc28j60GetPacketCount	; export
	.type	_enc28j60GetPacketCount,@function
_enc28j60GetPacketCount:
.LFB23:
.LSM156:
	.set ___PA___,1
.LSM157:
	mov.b	#57,w0
	bra	_enc28j60ReadRegisterUint8
.LSM158:
	.set ___PA___,0
.LFE23:
	.align	2
	.global	_enc28j60RxFrame	; export
	.type	_enc28j60RxFrame,@function
_enc28j60RxFrame:
.LFB21:
.LSM159:
	.set ___PA___,0
	add	w15,#10,w15
	mov.d	w8,[w15++]
	mov.d	w10,[w15++]
	mov	w14,[w15++]
	mov	w0,w10
.LSM160:
	rcall	_enc28j60GetPacketCount
.LSM161:
	sub	w15,#18,w14
	mov.b	#1,w2
	mov.b	w2,[w14++]
.LBB2:
.LSM162:
	inc2	w10,w8
.LBE2:
.LSM163:
	bra	.L40
.L44:
.LBB3:
.LSM164:
	mov	_dataPtr.6762,w1
	clr.b	w0
	rcall	_enc28j60WriteRegisterUint16
.LSM165:
	mov	#6,w2
	mov	w14,w1
	mov	_dataPtr.6762,w0
	rcall	_enc28j60ReadData
.LSM166:
	mov.b	[w15-16],w11
	sl	w11,#8,w11
	mov.b	[w15-17],w0
	ze	w0,w0
	ior	w11,w0,w11
.LSM167:
	mov.b	[w15-15],w3
	mov.b	[w15-14],w2
.LSM168:
	mov.b	[w15-13],w9
	and	w9,#16,w9
	.set ___BP___,71
	bra	nz,.L41
.LSM169:
	sl	w2,#8,w2
	ze	w3,w3
	ior	w2,w3,w2
.LSM170:
	dec2	w2,w2
	mov	_dataPtr.6762,w0
	add	w0,#4,w0
	mov	w10,w1
	rcall	_enc28j60ReadData
.LSM171:
	mov	[w8+12],w0
	sl	w0,#8,w1
	lsr	w0,#8,w0
	ior	w1,w0,w0
	mov	w0,[w8+12]
.LSM172:
; 461 "../../src/devices/enc28j60.c" 1
	nop
.LSM173:
	mov.b	w9,[w15-18]
.LSM174:
	sub	w15,#18,w1
	mov	w8,w0
	rcall	_ipv4HandlePacket
.LSM175:
	mov.b	[w15-18],w0
	sub.b	w0,#0,[w15]
	.set ___BP___,71
	bra	nz,.L41
.LSM176:
	sub	w15,#18,w1
	mov	w8,w0
	rcall	_arpProcessPacket
.L41:
.LSM177:
	mov	w11,_dataPtr.6762
.LSM178:
	mov.b	#8,w0
	rcall	_enc28j60ReadRegisterUint16
	ze	w0,w0
	sub	w11,w0,[w15]
	.set ___BP___,72
	bra	nz,.L42
.LSM179:
	mov.b	#10,w0
	rcall	_enc28j60ReadRegisterUint16
	ze	w0,w1
	bra	.L45
.L42:
.LSM180:
	mov	_dataPtr.6762,w1
	dec	w1,w1
.L45:
	mov.b	#12,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM181:
	mov.b	#64,w1
	mov.b	#-98,w0
	rcall	_enc28j60BitSetRegisterUint8
.LSM182:
	rcall	_enc28j60GetPacketCount
.L40:
.LBE3:
.LSM183:
	sub.b	w0,#0,[w15]
	.set ___BP___,91
	bra	nz,.L44
.LSM184:
	mov	[--w15],w14
	mov.d	[--w15],w10
	mov.d	[--w15],w8
	sub	w15,#10
	return	
	.set ___PA___,0
.LFE21:
	.align	2
	.global	_enc28j60RegisterTxHandler	; export
	.type	_enc28j60RegisterTxHandler,@function
_enc28j60RegisterTxHandler:
.LFB24:
.LSM185:
	.set ___PA___,1
	mov	w0,w2
.LSM186:
	mov	#_handlers,w1
	mov.b	[w1],w1
	sub.b	w1,#0,[w15]
	.set ___BP___,4
	bra	z,.L47
.LSM187:
	clr.b	w0
.LSM188:
	mov	#_handlers+4,w1
	mov.b	[w1],w1
	sub.b	w1,w0,[w15]
	.set ___BP___,95
	bra	nz,.L48
.LSM189:
	mov.b	#1,w1
.L47:
.LSM190:
	ze	w1,w1
	sl	w1,#2,w1
	mov	#_handlers,w0
	add	w0,w1,w0
	mov.b	#1,w1
	mov.b	w1,[w0]
.LSM191:
	mov	w2,[w0+2]
.LSM192:
	mov.b	w1,w0
.L48:
.LSM193:
	return	
.LFE24:
	.align	2
	.global	_enc28j60UnregisterTxHandler	; export
	.type	_enc28j60UnregisterTxHandler,@function
_enc28j60UnregisterTxHandler:
.LFB25:
.LSM194:
	.set ___PA___,1
.LSM195:
	mov	_handlers+2,w1
	sub	w1,w0,[w15]
	.set ___BP___,85
	bra	nz,.L52
.LSM196:
	clr.b	_handlers
.L52:
.LSM197:
	mov	_handlers+6,w1
	sub	w1,w0,[w15]
	.set ___BP___,85
	bra	nz,.L51
.LSM198:
	clr.b	_handlers+4
.L51:
	return	
.LFE25:
	.align	2
	.global	_enc28j60FireTxHandlers	; export
	.type	_enc28j60FireTxHandlers,@function
_enc28j60FireTxHandlers:
.LFB26:
.LSM199:
	.set ___PA___,1
	lnk	#2
	mov	w8,[w15++]
	mov	w0,w8
.LSM200:
	clr.b	w0
	mov.b	w0,[w15-4]
.LSM201:
	mov.b	_handlers,WREG
	sub.b	w0,#1,[w15]
	.set ___BP___,86
	bra	nz,.L55
.LSM202:
	sub	w15,#4,w1
	mov	w8,w0
	mov	_handlers+2,w2
	call	w2
.L55:
.LSM203:
	mov.b	[w15-4],w0
	sub.b	w0,#0,[w15]
	.set ___BP___,4
	bra	nz,.L54
.LSM204:
	mov.b	_handlers+4,WREG
	sub.b	w0,#1,[w15]
	.set ___BP___,86
	bra	nz,.L54
.LSM205:
	sub	w15,#4,w1
	mov	w8,w0
	mov	_handlers+6,w2
	call	w2
.L54:
.LSM206:
	mov	[--w15],w8
	ulnk	
	return	
	.set ___PA___,0
.LFE26:
	.align	2
	.global	_enc28j60Reset	; export
	.type	_enc28j60Reset,@function
_enc28j60Reset:
.LFB27:
.LSM207:
	.set ___PA___,0
.LSM208:
	mov	#128,w0
	ior	_PORTC
.LSM209:
	bclr.b	_PORTC,#7
.LSM210:
	ior	_PORTC
.LSM211:
; 567 "../../src/devices/enc28j60.c" 1
	bclr PORTC, #8

.LSM212:
	setm.b	w1
	mov.b	#1,w0
	rcall	_spiTxByte
.LSM213:
; 569 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM214:
	return	
	.set ___PA___,0
.LFE27:
	.align	2
	.global	_enc28j60Initialize	; export
	.type	_enc28j60Initialize,@function
_enc28j60Initialize:
.LFB18:
.LSM215:
	.set ___PA___,0
	mov	w8,[w15++]
	mov	w0,w8
.LSM216:
; 294 "../../src/devices/enc28j60.c" 1
	bset PORTC, #8

.LSM217:
	mov	w8,_myMac
.LSM218:
	clr	_handlers
.LSM219:
	rcall	_enc28j60Reset
.LSM220:
	mov.b	#2,w0
	rcall	_enc28j60ReadPhyRegisterUint16
.LSM221:
	mov.b	#3,w0
	rcall	_enc28j60ReadPhyRegisterUint16
.LSM222:
	mov.b	#114,w0
	rcall	_enc28j60ReadRegisterUint8
.LSM223:
	mov.b	#64,w1
	mov.b	#-98,w0
	rcall	_enc28j60BitSetRegisterUint8
.L59:
.LSM224:
	mov.b	#-99,w0
	rcall	_enc28j60ReadRegisterUint8
	and	w0,#1,w0
	.set ___BP___,91
	bra	z,.L59
.LSM225:
	mov	#1858,w1
	mov.b	#20,w0
	rcall	_enc28j60WritePhyRegisterUint16
.LSM226:
	clr	w1
	mov.b	#8,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM227:
	mov	#4095,w1
	mov.b	#10,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM228:
	clr	w1
	mov.b	#12,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM229:
	mov	#4096,w1
	mov.b	#4,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM230:
	mov	#8191,w1
	mov.b	#6,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM231:
	mov.b	#13,w1
	mov.b	#64,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM232:
	mov.b	#-10,w1
	mov.b	#66,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM233:
	mov.b	#64,w1
	mov.b	#67,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM234:
	mov	#1518,w1
	mov.b	#74,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM235:
	mov.b	#18,w1
	mov.b	#68,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM236:
	mov	#3090,w1
	mov.b	#70,w0
	rcall	_enc28j60WriteRegisterUint16
.LSM237:
	mov.b	[w8],w1
	mov.b	#100,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM238:
	mov.b	[w8+1],w1
	mov.b	#101,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM239:
	mov.b	[w8+2],w1
	mov.b	#98,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM240:
	mov.b	[w8+3],w1
	mov.b	#99,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM241:
	mov.b	[w8+4],w1
	mov.b	#96,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM242:
	mov.b	[w8+5],w1
	mov.b	#97,w0
	rcall	_enc28j60WriteRegisterUint8
.LSM243:
	mov	#256,w1
	mov.b	#16,w0
	rcall	_enc28j60WritePhyRegisterUint16
.LSM244:
	mov.b	#4,w1
	mov.b	#-97,w0
	rcall	_enc28j60BitSetRegisterUint8
.LSM245:
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE18:
	.section	.nbss,bss,near
	.type	_debugBuffer,@object
	.global	_debugBuffer
_debugBuffer:	.space	256
	.pushsection	.nbss,bss,near
	.align	2
_handlers:	.space	8
	.popsection
	.pushsection	.nbss,bss,near
	.align	2
_dataPtr.6762:	.space	2
	.popsection
	.pushsection	.nbss,bss,near
_controlByte.6745:	.space	1
	.popsection
	.pushsection	.nbss,bss,near
	.align	2
_myMac:	.space	2
	.popsection
	.pushsection	.nbss,bss,near
_currentBank:	.space	1
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
.LSFDE16:
	.4byte	.LEFDE16-.LASFDE16
.LASFDE16:
	.4byte	.Lframe0
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.align	4
.LEFDE16:
.LSFDE18:
	.4byte	.LEFDE18-.LASFDE18
.LASFDE18:
	.4byte	.Lframe0
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.align	4
.LEFDE18:
.LSFDE20:
	.4byte	.LEFDE20-.LASFDE20
.LASFDE20:
	.4byte	.Lframe0
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.align	4
.LEFDE20:
.LSFDE22:
	.4byte	.LEFDE22-.LASFDE22
.LASFDE22:
	.4byte	.Lframe0
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.align	4
.LEFDE22:
.LSFDE24:
	.4byte	.LEFDE24-.LASFDE24
.LASFDE24:
	.4byte	.Lframe0
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.align	4
.LEFDE24:
.LSFDE26:
	.4byte	.LEFDE26-.LASFDE26
.LASFDE26:
	.4byte	.Lframe0
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.align	4
.LEFDE26:
.LSFDE28:
	.4byte	.LEFDE28-.LASFDE28
.LASFDE28:
	.4byte	.Lframe0
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.align	4
.LEFDE28:
.LSFDE30:
	.4byte	.LEFDE30-.LASFDE30
.LASFDE30:
	.4byte	.Lframe0
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.align	4
.LEFDE30:
.LSFDE32:
	.4byte	.LEFDE32-.LASFDE32
.LASFDE32:
	.4byte	.Lframe0
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.align	4
.LEFDE32:
.LSFDE34:
	.4byte	.LEFDE34-.LASFDE34
.LASFDE34:
	.4byte	.Lframe0
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.align	4
.LEFDE34:
.LSFDE36:
	.4byte	.LEFDE36-.LASFDE36
.LASFDE36:
	.4byte	.Lframe0
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.align	4
.LEFDE36:
.LSFDE38:
	.4byte	.LEFDE38-.LASFDE38
.LASFDE38:
	.4byte	.Lframe0
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.align	4
.LEFDE38:
.LSFDE40:
	.4byte	.LEFDE40-.LASFDE40
.LASFDE40:
	.4byte	.Lframe0
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.align	4
.LEFDE40:
.LSFDE42:
	.4byte	.LEFDE42-.LASFDE42
.LASFDE42:
	.4byte	.Lframe0
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.align	4
.LEFDE42:
.LSFDE44:
	.4byte	.LEFDE44-.LASFDE44
.LASFDE44:
	.4byte	.Lframe0
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.align	4
.LEFDE44:
.LSFDE46:
	.4byte	.LEFDE46-.LASFDE46
.LASFDE46:
	.4byte	.Lframe0
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.align	4
.LEFDE46:
.LSFDE48:
	.4byte	.LEFDE48-.LASFDE48
.LASFDE48:
	.4byte	.Lframe0
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.align	4
.LEFDE48:
.LSFDE50:
	.4byte	.LEFDE50-.LASFDE50
.LASFDE50:
	.4byte	.Lframe0
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.align	4
.LEFDE50:
.LSFDE52:
	.4byte	.LEFDE52-.LASFDE52
.LASFDE52:
	.4byte	.Lframe0
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.align	4
.LEFDE52:
.LSFDE54:
	.4byte	.LEFDE54-.LASFDE54
.LASFDE54:
	.4byte	.Lframe0
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.align	4
.LEFDE54:
	.section	.text,code
.Letext0:
	.section	.debug_info,info
	.4byte	0x1083
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1_11) (A) Build date: Nov 17 2012"
	.byte	0x1
	.asciz	"../../src/devices/enc28j60.c"
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
	.uleb128 0x3
	.asciz	"_BOOL"
	.byte	0x2
	.byte	0x5
	.byte	0x40
	.4byte	0x117
	.uleb128 0x4
	.asciz	"FALSE"
	.sleb128 0
	.uleb128 0x4
	.asciz	"TRUE"
	.sleb128 1
	.byte	0x0
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
	.uleb128 0x5
	.asciz	"bool_t"
	.byte	0x2
	.byte	0x65
	.4byte	0x143
	.uleb128 0x5
	.asciz	"UI08_t"
	.byte	0x2
	.byte	0x66
	.4byte	0x143
	.uleb128 0x5
	.asciz	"UI16_t"
	.byte	0x2
	.byte	0x67
	.4byte	0xb7
	.uleb128 0x6
	.asciz	"EthernetFrame_s"
	.byte	0xe
	.byte	0x3
	.byte	0x7
	.4byte	0x1f7
	.uleb128 0x7
	.asciz	"dstMac"
	.byte	0x3
	.byte	0x9
	.4byte	0x1f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x7
	.asciz	"srcMac"
	.byte	0x3
	.byte	0xa
	.4byte	0x1f7
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x7
	.asciz	"type"
	.byte	0x3
	.byte	0xb
	.4byte	0x19f
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0x0
	.uleb128 0x8
	.4byte	0x191
	.4byte	0x207
	.uleb128 0x9
	.4byte	0xb7
	.byte	0x5
	.byte	0x0
	.uleb128 0x5
	.asciz	"EthernetFrame_t"
	.byte	0x3
	.byte	0xc
	.4byte	0x1ad
	.uleb128 0x5
	.asciz	"EthernetPacketHandler_t"
	.byte	0x3
	.byte	0x15
	.4byte	0x23d
	.uleb128 0xa
	.byte	0x2
	.4byte	0x243
	.uleb128 0xb
	.byte	0x1
	.4byte	0x254
	.uleb128 0xc
	.4byte	0x254
	.uleb128 0xc
	.4byte	0x25a
	.byte	0x0
	.uleb128 0xa
	.byte	0x2
	.4byte	0x207
	.uleb128 0xa
	.byte	0x2
	.4byte	0x183
	.uleb128 0xd
	.byte	0x1
	.byte	0x4
	.byte	0x17
	.4byte	0x2a1
	.uleb128 0xe
	.asciz	"addr"
	.byte	0x4
	.byte	0x19
	.4byte	0x191
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xe
	.asciz	"bank"
	.byte	0x4
	.byte	0x1a
	.4byte	0x191
	.byte	0x1
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xe
	.asciz	"global"
	.byte	0x4
	.byte	0x1b
	.4byte	0x191
	.byte	0x1
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0xf
	.asciz	"enc28j60Register_u"
	.byte	0x1
	.byte	0x4
	.byte	0x15
	.4byte	0x2e4
	.uleb128 0x10
	.asciz	"registerObj"
	.byte	0x4
	.byte	0x1c
	.4byte	0x260
	.uleb128 0x10
	.asciz	"registerByte"
	.byte	0x4
	.byte	0x1d
	.4byte	0x191
	.byte	0x0
	.uleb128 0x5
	.asciz	"enc28j60Register_t"
	.byte	0x4
	.byte	0x1f
	.4byte	0x2a1
	.uleb128 0x3
	.asciz	"enc28j60Addressing_e"
	.byte	0x2
	.byte	0x4
	.byte	0x28
	.4byte	0x34a
	.uleb128 0x4
	.asciz	"RCR"
	.sleb128 0
	.uleb128 0x4
	.asciz	"RBM"
	.sleb128 58
	.uleb128 0x4
	.asciz	"WCR"
	.sleb128 64
	.uleb128 0x4
	.asciz	"WBM"
	.sleb128 122
	.uleb128 0x4
	.asciz	"BFS"
	.sleb128 128
	.uleb128 0x4
	.asciz	"BFC"
	.sleb128 160
	.uleb128 0x4
	.asciz	"SC"
	.sleb128 255
	.byte	0x0
	.uleb128 0x3
	.asciz	"enc28j60PhyRegisters_e"
	.byte	0x2
	.byte	0x4
	.byte	0x36
	.4byte	0x3b7
	.uleb128 0x4
	.asciz	"PHCON1"
	.sleb128 0
	.uleb128 0x4
	.asciz	"PHSTAT1"
	.sleb128 1
	.uleb128 0x4
	.asciz	"PHID1"
	.sleb128 2
	.uleb128 0x4
	.asciz	"PHID2"
	.sleb128 3
	.uleb128 0x4
	.asciz	"PHCON2"
	.sleb128 16
	.uleb128 0x4
	.asciz	"PHSTAT2"
	.sleb128 17
	.uleb128 0x4
	.asciz	"PHIE"
	.sleb128 18
	.uleb128 0x4
	.asciz	"PHIR"
	.sleb128 19
	.uleb128 0x4
	.asciz	"PHLCON"
	.sleb128 20
	.byte	0x0
	.uleb128 0x3
	.asciz	"enc28j60Registers_e"
	.byte	0x2
	.byte	0x4
	.byte	0x44
	.4byte	0x70d
	.uleb128 0x4
	.asciz	"ERDPTL"
	.sleb128 0
	.uleb128 0x4
	.asciz	"ERDPTH"
	.sleb128 1
	.uleb128 0x4
	.asciz	"EWRPTL"
	.sleb128 2
	.uleb128 0x4
	.asciz	"EWRPTH"
	.sleb128 3
	.uleb128 0x4
	.asciz	"ETXSTL"
	.sleb128 4
	.uleb128 0x4
	.asciz	"ETXSTH"
	.sleb128 5
	.uleb128 0x4
	.asciz	"ETXNDL"
	.sleb128 6
	.uleb128 0x4
	.asciz	"ETXNDH"
	.sleb128 7
	.uleb128 0x4
	.asciz	"ERXSTL"
	.sleb128 8
	.uleb128 0x4
	.asciz	"ERXSTH"
	.sleb128 9
	.uleb128 0x4
	.asciz	"ERXNDL"
	.sleb128 10
	.uleb128 0x4
	.asciz	"ERXNDH"
	.sleb128 11
	.uleb128 0x4
	.asciz	"ERXRDPTL"
	.sleb128 12
	.uleb128 0x4
	.asciz	"ERXRDPTH"
	.sleb128 13
	.uleb128 0x4
	.asciz	"ERXWRPTL"
	.sleb128 14
	.uleb128 0x4
	.asciz	"ERXWRPTH"
	.sleb128 15
	.uleb128 0x4
	.asciz	"EDMASTL"
	.sleb128 16
	.uleb128 0x4
	.asciz	"EDMASTH"
	.sleb128 17
	.uleb128 0x4
	.asciz	"EDMANDL"
	.sleb128 18
	.uleb128 0x4
	.asciz	"EDMANDH"
	.sleb128 19
	.uleb128 0x4
	.asciz	"EDMADSTL"
	.sleb128 20
	.uleb128 0x4
	.asciz	"EDMADSTH"
	.sleb128 21
	.uleb128 0x4
	.asciz	"EDMACSL"
	.sleb128 22
	.uleb128 0x4
	.asciz	"EDMACSH"
	.sleb128 23
	.uleb128 0x4
	.asciz	"EHT0"
	.sleb128 32
	.uleb128 0x4
	.asciz	"EHT1"
	.sleb128 33
	.uleb128 0x4
	.asciz	"EHT2"
	.sleb128 34
	.uleb128 0x4
	.asciz	"EHT3"
	.sleb128 35
	.uleb128 0x4
	.asciz	"EHT4"
	.sleb128 36
	.uleb128 0x4
	.asciz	"EHT5"
	.sleb128 37
	.uleb128 0x4
	.asciz	"EHT6"
	.sleb128 38
	.uleb128 0x4
	.asciz	"EHT7"
	.sleb128 39
	.uleb128 0x4
	.asciz	"EPMM0"
	.sleb128 40
	.uleb128 0x4
	.asciz	"EPMM1"
	.sleb128 41
	.uleb128 0x4
	.asciz	"EPMM2"
	.sleb128 42
	.uleb128 0x4
	.asciz	"EPMM3"
	.sleb128 43
	.uleb128 0x4
	.asciz	"EPMM4"
	.sleb128 44
	.uleb128 0x4
	.asciz	"EPMM5"
	.sleb128 45
	.uleb128 0x4
	.asciz	"EPMM6"
	.sleb128 46
	.uleb128 0x4
	.asciz	"EPMM7"
	.sleb128 47
	.uleb128 0x4
	.asciz	"EPMCSL"
	.sleb128 48
	.uleb128 0x4
	.asciz	"EPMCSH"
	.sleb128 49
	.uleb128 0x4
	.asciz	"EPMOL"
	.sleb128 52
	.uleb128 0x4
	.asciz	"EPMOH"
	.sleb128 53
	.uleb128 0x4
	.asciz	"EWOLIE"
	.sleb128 54
	.uleb128 0x4
	.asciz	"EWOLIR"
	.sleb128 55
	.uleb128 0x4
	.asciz	"ERXFCON"
	.sleb128 56
	.uleb128 0x4
	.asciz	"EPKTCNT"
	.sleb128 57
	.uleb128 0x4
	.asciz	"MACON1"
	.sleb128 64
	.uleb128 0x4
	.asciz	"MACON2"
	.sleb128 65
	.uleb128 0x4
	.asciz	"MACON3"
	.sleb128 66
	.uleb128 0x4
	.asciz	"MACON4"
	.sleb128 67
	.uleb128 0x4
	.asciz	"MABBIPG"
	.sleb128 68
	.uleb128 0x4
	.asciz	"MAIPGL"
	.sleb128 70
	.uleb128 0x4
	.asciz	"MAIPGH"
	.sleb128 71
	.uleb128 0x4
	.asciz	"MACLCON1"
	.sleb128 72
	.uleb128 0x4
	.asciz	"MACLCON2"
	.sleb128 73
	.uleb128 0x4
	.asciz	"MAMXFLL"
	.sleb128 74
	.uleb128 0x4
	.asciz	"MAMXFLH"
	.sleb128 75
	.uleb128 0x4
	.asciz	"MAPHSUP"
	.sleb128 77
	.uleb128 0x4
	.asciz	"MICON"
	.sleb128 81
	.uleb128 0x4
	.asciz	"MICMD"
	.sleb128 82
	.uleb128 0x4
	.asciz	"MIREGADR"
	.sleb128 84
	.uleb128 0x4
	.asciz	"MIWRL"
	.sleb128 86
	.uleb128 0x4
	.asciz	"MIWRH"
	.sleb128 87
	.uleb128 0x4
	.asciz	"MIRDL"
	.sleb128 88
	.uleb128 0x4
	.asciz	"MIRDH"
	.sleb128 89
	.uleb128 0x4
	.asciz	"MAADR1"
	.sleb128 96
	.uleb128 0x4
	.asciz	"MAADR0"
	.sleb128 97
	.uleb128 0x4
	.asciz	"MAADR3"
	.sleb128 98
	.uleb128 0x4
	.asciz	"MAADR2"
	.sleb128 99
	.uleb128 0x4
	.asciz	"MAADR5"
	.sleb128 100
	.uleb128 0x4
	.asciz	"MAADR4"
	.sleb128 101
	.uleb128 0x4
	.asciz	"EBSTSD"
	.sleb128 102
	.uleb128 0x4
	.asciz	"EBSTCON"
	.sleb128 103
	.uleb128 0x4
	.asciz	"EBSTCSL"
	.sleb128 104
	.uleb128 0x4
	.asciz	"EBSTCSH"
	.sleb128 105
	.uleb128 0x4
	.asciz	"MISTAT"
	.sleb128 106
	.uleb128 0x4
	.asciz	"EREVID"
	.sleb128 114
	.uleb128 0x4
	.asciz	"ECOCON"
	.sleb128 117
	.uleb128 0x4
	.asciz	"EFLOCON"
	.sleb128 119
	.uleb128 0x4
	.asciz	"EPAUSL"
	.sleb128 120
	.uleb128 0x4
	.asciz	"EPAUSH"
	.sleb128 121
	.uleb128 0x4
	.asciz	"EIE"
	.sleb128 155
	.uleb128 0x4
	.asciz	"EIR"
	.sleb128 156
	.uleb128 0x4
	.asciz	"ESTAT"
	.sleb128 157
	.uleb128 0x4
	.asciz	"ECON2"
	.sleb128 158
	.uleb128 0x4
	.asciz	"ECON1"
	.sleb128 159
	.byte	0x0
	.uleb128 0x6
	.asciz	"EthernetPacketHandlerInfo_s"
	.byte	0x4
	.byte	0x1
	.byte	0xe
	.4byte	0x74f
	.uleb128 0x7
	.asciz	"used"
	.byte	0x1
	.byte	0x10
	.4byte	0x183
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x11
	.4byte	.LASF0
	.byte	0x1
	.byte	0x11
	.4byte	0x21e
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0x0
	.uleb128 0x5
	.asciz	"EthernetPacketHandlerInfo_t"
	.byte	0x1
	.byte	0x12
	.4byte	0x70d
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60WriteUint8"
	.byte	0x1
	.byte	0x2d
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.4byte	0x7b3
	.uleb128 0x13
	.asciz	"reg"
	.byte	0x1
	.byte	0x2d
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.uleb128 0x14
	.4byte	.LASF1
	.byte	0x1
	.byte	0x2d
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60BitSetUint8"
	.byte	0x1
	.byte	0x36
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.4byte	0x7f5
	.uleb128 0x13
	.asciz	"reg"
	.byte	0x1
	.byte	0x36
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.uleb128 0x14
	.4byte	.LASF1
	.byte	0x1
	.byte	0x36
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60BitClrUint8"
	.byte	0x1
	.byte	0x3f
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.4byte	0x837
	.uleb128 0x13
	.asciz	"reg"
	.byte	0x1
	.byte	0x3f
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.uleb128 0x14
	.4byte	.LASF1
	.byte	0x1
	.byte	0x3f
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60WriteUint16"
	.byte	0x1
	.byte	0x49
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.4byte	0x879
	.uleb128 0x13
	.asciz	"reg"
	.byte	0x1
	.byte	0x49
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.uleb128 0x14
	.4byte	.LASF1
	.byte	0x1
	.byte	0x49
	.4byte	0x19f
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x15
	.byte	0x1
	.asciz	"enc28j60ReadUint8"
	.byte	0x1
	.byte	0x54
	.byte	0x1
	.4byte	0x191
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.4byte	0x8bb
	.uleb128 0x13
	.asciz	"reg"
	.byte	0x1
	.byte	0x54
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.uleb128 0x16
	.asciz	"d"
	.byte	0x1
	.byte	0x56
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x15
	.byte	0x1
	.asciz	"enc28j60ReadMacUint8"
	.byte	0x1
	.byte	0x62
	.byte	0x1
	.4byte	0x191
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.4byte	0x900
	.uleb128 0x13
	.asciz	"reg"
	.byte	0x1
	.byte	0x62
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.uleb128 0x16
	.asciz	"d"
	.byte	0x1
	.byte	0x64
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x15
	.byte	0x1
	.asciz	"enc28j60ReadUint16"
	.byte	0x1
	.byte	0x70
	.byte	0x1
	.4byte	0x19f
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.4byte	0x941
	.uleb128 0x13
	.asciz	"reg"
	.byte	0x1
	.byte	0x70
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.uleb128 0x17
	.asciz	"d"
	.byte	0x1
	.byte	0x72
	.4byte	0x19f
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60SetBank"
	.byte	0x1
	.byte	0x79
	.byte	0x1
	.4byte	.LFB7
	.4byte	.LFE7
	.byte	0x1
	.byte	0x5f
	.4byte	0x972
	.uleb128 0x13
	.asciz	"reg"
	.byte	0x1
	.byte	0x79
	.4byte	0x2e4
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60WriteData"
	.byte	0x1
	.byte	0x8e
	.byte	0x1
	.4byte	.LFB8
	.4byte	.LFE8
	.byte	0x1
	.byte	0x5f
	.4byte	0x9bf
	.uleb128 0x14
	.4byte	.LASF2
	.byte	0x1
	.byte	0x8e
	.4byte	0x19f
	.byte	0x1
	.byte	0x50
	.uleb128 0x13
	.asciz	"bf"
	.byte	0x1
	.byte	0x8e
	.4byte	0x9bf
	.byte	0x1
	.byte	0x58
	.uleb128 0x13
	.asciz	"size"
	.byte	0x1
	.byte	0x8e
	.4byte	0x19f
	.byte	0x1
	.byte	0x53
	.byte	0x0
	.uleb128 0xa
	.byte	0x2
	.4byte	0x191
	.uleb128 0x15
	.byte	0x1
	.asciz	"enc28j60ReadRegisterUint8"
	.byte	0x1
	.byte	0xab
	.byte	0x1
	.4byte	0x191
	.4byte	.LFB10
	.4byte	.LFE10
	.byte	0x1
	.byte	0x5f
	.4byte	0xa0f
	.uleb128 0x14
	.4byte	.LASF3
	.byte	0x1
	.byte	0xab
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.uleb128 0x17
	.asciz	"reg"
	.byte	0x1
	.byte	0xad
	.4byte	0x2e4
	.byte	0x0
	.uleb128 0x15
	.byte	0x1
	.asciz	"enc28j60ReadRegisterUint16"
	.byte	0x1
	.byte	0xb7
	.byte	0x1
	.4byte	0x191
	.4byte	.LFB11
	.4byte	.LFE11
	.byte	0x1
	.byte	0x5f
	.4byte	0xa5a
	.uleb128 0x14
	.4byte	.LASF3
	.byte	0x1
	.byte	0xb7
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.uleb128 0x17
	.asciz	"reg"
	.byte	0x1
	.byte	0xb9
	.4byte	0x2e4
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60WriteRegisterUint8"
	.byte	0x1
	.byte	0xc3
	.byte	0x1
	.4byte	.LFB12
	.4byte	.LFE12
	.byte	0x1
	.byte	0x5f
	.4byte	0xaae
	.uleb128 0x14
	.4byte	.LASF3
	.byte	0x1
	.byte	0xc3
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.uleb128 0x14
	.4byte	.LASF1
	.byte	0x1
	.byte	0xc3
	.4byte	0x191
	.byte	0x1
	.byte	0x59
	.uleb128 0x17
	.asciz	"reg"
	.byte	0x1
	.byte	0xc5
	.4byte	0x2e4
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60BitSetRegisterUint8"
	.byte	0x1
	.byte	0xd0
	.byte	0x1
	.4byte	.LFB13
	.4byte	.LFE13
	.byte	0x1
	.byte	0x5f
	.4byte	0xb03
	.uleb128 0x14
	.4byte	.LASF3
	.byte	0x1
	.byte	0xd0
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.uleb128 0x14
	.4byte	.LASF1
	.byte	0x1
	.byte	0xd0
	.4byte	0x191
	.byte	0x1
	.byte	0x59
	.uleb128 0x17
	.asciz	"reg"
	.byte	0x1
	.byte	0xd2
	.4byte	0x2e4
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60BitClrRegisterUint8"
	.byte	0x1
	.byte	0xdd
	.byte	0x1
	.4byte	.LFB14
	.4byte	.LFE14
	.byte	0x1
	.byte	0x5f
	.4byte	0xb58
	.uleb128 0x14
	.4byte	.LASF3
	.byte	0x1
	.byte	0xdd
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.uleb128 0x14
	.4byte	.LASF1
	.byte	0x1
	.byte	0xdd
	.4byte	0x191
	.byte	0x1
	.byte	0x59
	.uleb128 0x17
	.asciz	"reg"
	.byte	0x1
	.byte	0xdf
	.4byte	0x2e4
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60WriteRegisterUint16"
	.byte	0x1
	.byte	0xe9
	.byte	0x1
	.4byte	.LFB15
	.4byte	.LFE15
	.byte	0x1
	.byte	0x5f
	.4byte	0xbad
	.uleb128 0x14
	.4byte	.LASF3
	.byte	0x1
	.byte	0xe9
	.4byte	0x191
	.byte	0x1
	.byte	0x58
	.uleb128 0x14
	.4byte	.LASF1
	.byte	0x1
	.byte	0xe9
	.4byte	0x19f
	.byte	0x1
	.byte	0x59
	.uleb128 0x17
	.asciz	"reg"
	.byte	0x1
	.byte	0xeb
	.4byte	0x2e4
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60ReadData"
	.byte	0x1
	.byte	0x99
	.byte	0x1
	.4byte	.LFB9
	.4byte	.LFE9
	.byte	0x1
	.byte	0x5f
	.4byte	0xbf9
	.uleb128 0x14
	.4byte	.LASF2
	.byte	0x1
	.byte	0x99
	.4byte	0x19f
	.byte	0x1
	.byte	0x50
	.uleb128 0x13
	.asciz	"bf"
	.byte	0x1
	.byte	0x99
	.4byte	0x9bf
	.byte	0x1
	.byte	0x58
	.uleb128 0x13
	.asciz	"size"
	.byte	0x1
	.byte	0x99
	.4byte	0x19f
	.byte	0x1
	.byte	0x53
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"enc28j60WritePhyRegisterUint16"
	.byte	0x1
	.byte	0xf7
	.byte	0x1
	.4byte	.LFB16
	.4byte	.LFE16
	.byte	0x1
	.byte	0x5f
	.4byte	0xc46
	.uleb128 0x14
	.4byte	.LASF3
	.byte	0x1
	.byte	0xf7
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.uleb128 0x14
	.4byte	.LASF1
	.byte	0x1
	.byte	0xf7
	.4byte	0x19f
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x18
	.byte	0x1
	.asciz	"enc28j60ReadPhyRegisterUint16"
	.byte	0x1
	.2byte	0x100
	.byte	0x1
	.4byte	0x19f
	.4byte	.LFB17
	.4byte	.LFE17
	.byte	0x1
	.byte	0x5f
	.4byte	0xc98
	.uleb128 0x19
	.4byte	.LASF3
	.byte	0x1
	.2byte	0x100
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.uleb128 0x1a
	.asciz	"temp"
	.byte	0x1
	.2byte	0x102
	.4byte	0x19f
	.byte	0x0
	.uleb128 0x1b
	.byte	0x1
	.asciz	"enc28j60TxFrame"
	.byte	0x1
	.2byte	0x16d
	.byte	0x1
	.4byte	.LFB19
	.4byte	.LFE19
	.byte	0x1
	.byte	0x5f
	.4byte	0xcf6
	.uleb128 0x1c
	.asciz	"packet"
	.byte	0x1
	.2byte	0x16d
	.4byte	0x254
	.byte	0x1
	.byte	0x5a
	.uleb128 0x19
	.4byte	.LASF4
	.byte	0x1
	.2byte	0x16d
	.4byte	0x19f
	.byte	0x1
	.byte	0x58
	.uleb128 0x1d
	.asciz	"controlByte"
	.byte	0x1
	.2byte	0x16f
	.4byte	0x191
	.byte	0x5
	.byte	0x3
	.4byte	_controlByte.6745
	.byte	0x0
	.uleb128 0x1b
	.byte	0x1
	.asciz	"enc28j60TxReplyFrame"
	.byte	0x1
	.2byte	0x190
	.byte	0x1
	.4byte	.LFB20
	.4byte	.LFE20
	.byte	0x1
	.byte	0x5f
	.4byte	0xd50
	.uleb128 0x1c
	.asciz	"frame"
	.byte	0x1
	.2byte	0x190
	.4byte	0x254
	.byte	0x1
	.byte	0x50
	.uleb128 0x19
	.4byte	.LASF4
	.byte	0x1
	.2byte	0x190
	.4byte	0x19f
	.byte	0x1
	.byte	0x51
	.uleb128 0x1d
	.asciz	"tmpMac"
	.byte	0x1
	.2byte	0x192
	.4byte	0x1f7
	.byte	0x2
	.byte	0x91
	.sleb128 -6
	.byte	0x0
	.uleb128 0x1e
	.byte	0x1
	.asciz	"enc28j60PacketPending"
	.byte	0x1
	.2byte	0x1ef
	.4byte	0x191
	.4byte	.LFB22
	.4byte	.LFE22
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1e
	.byte	0x1
	.asciz	"enc28j60GetPacketCount"
	.byte	0x1
	.2byte	0x1f4
	.4byte	0x191
	.4byte	.LFB23
	.4byte	.LFE23
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1b
	.byte	0x1
	.asciz	"enc28j60RxFrame"
	.byte	0x1
	.2byte	0x19d
	.byte	0x1
	.4byte	.LFB21
	.4byte	.LFE21
	.byte	0x1
	.byte	0x5f
	.4byte	0xea5
	.uleb128 0x1c
	.asciz	"packet"
	.byte	0x1
	.2byte	0x19d
	.4byte	0x9bf
	.byte	0x1
	.byte	0x5a
	.uleb128 0x19
	.4byte	.LASF4
	.byte	0x1
	.2byte	0x19d
	.4byte	0x19f
	.byte	0x1
	.byte	0x51
	.uleb128 0x1d
	.asciz	"packetCount"
	.byte	0x1
	.2byte	0x19f
	.4byte	0x191
	.byte	0x1
	.byte	0x50
	.uleb128 0x1d
	.asciz	"dataPtr"
	.byte	0x1
	.2byte	0x1a0
	.4byte	0x19f
	.byte	0x5
	.byte	0x3
	.4byte	_dataPtr.6762
	.uleb128 0x1d
	.asciz	"packetHeader"
	.byte	0x1
	.2byte	0x1a1
	.4byte	0x1f7
	.byte	0x2
	.byte	0x91
	.sleb128 -17
	.uleb128 0x1a
	.asciz	"frame"
	.byte	0x1
	.2byte	0x1a2
	.4byte	0x254
	.uleb128 0x1a
	.asciz	"data"
	.byte	0x1
	.2byte	0x1a3
	.4byte	0x9bf
	.uleb128 0x1d
	.asciz	"dummy"
	.byte	0x1
	.2byte	0x1a4
	.4byte	0x183
	.byte	0x2
	.byte	0x91
	.sleb128 -18
	.uleb128 0x1f
	.4byte	.LBB2
	.4byte	.LBE2
	.uleb128 0x1d
	.asciz	"nextPacketOffset"
	.byte	0x1
	.2byte	0x1b0
	.4byte	0x19f
	.byte	0x1
	.byte	0x5b
	.uleb128 0x1a
	.asciz	"packetSize"
	.byte	0x1
	.2byte	0x1b1
	.4byte	0x19f
	.uleb128 0x1a
	.asciz	"receiveStatus"
	.byte	0x1
	.2byte	0x1b2
	.4byte	0x19f
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
	.byte	0x1
	.asciz	"enc28j60RegisterTxHandler"
	.byte	0x1
	.2byte	0x1f9
	.byte	0x1
	.4byte	0x183
	.4byte	.LFB24
	.4byte	.LFE24
	.byte	0x1
	.byte	0x5f
	.4byte	0xef2
	.uleb128 0x19
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x1f9
	.4byte	0x21e
	.byte	0x1
	.byte	0x52
	.uleb128 0x1d
	.asciz	"i"
	.byte	0x1
	.2byte	0x1fb
	.4byte	0x191
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x1b
	.byte	0x1
	.asciz	"enc28j60UnregisterTxHandler"
	.byte	0x1
	.2byte	0x20c
	.byte	0x1
	.4byte	.LFB25
	.4byte	.LFE25
	.byte	0x1
	.byte	0x5f
	.4byte	0xf3b
	.uleb128 0x19
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x20c
	.4byte	0x21e
	.byte	0x1
	.byte	0x50
	.uleb128 0x1a
	.asciz	"i"
	.byte	0x1
	.2byte	0x20e
	.4byte	0x191
	.byte	0x0
	.uleb128 0x1b
	.byte	0x1
	.asciz	"enc28j60FireTxHandlers"
	.byte	0x1
	.2byte	0x21c
	.byte	0x1
	.4byte	.LFB26
	.4byte	.LFE26
	.byte	0x1
	.byte	0x5f
	.4byte	0xf91
	.uleb128 0x1c
	.asciz	"frame"
	.byte	0x1
	.2byte	0x21c
	.4byte	0x254
	.byte	0x1
	.byte	0x58
	.uleb128 0x1a
	.asciz	"i"
	.byte	0x1
	.2byte	0x21e
	.4byte	0x191
	.uleb128 0x1d
	.asciz	"done"
	.byte	0x1
	.2byte	0x21f
	.4byte	0x183
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0x0
	.uleb128 0x20
	.byte	0x1
	.asciz	"enc28j60Reset"
	.byte	0x1
	.2byte	0x22c
	.byte	0x1
	.4byte	.LFB27
	.4byte	.LFE27
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1b
	.byte	0x1
	.asciz	"enc28j60Initialize"
	.byte	0x1
	.2byte	0x124
	.byte	0x1
	.4byte	.LFB18
	.4byte	.LFE18
	.byte	0x1
	.byte	0x5f
	.4byte	0xfe5
	.uleb128 0x1c
	.asciz	"mac"
	.byte	0x1
	.2byte	0x124
	.4byte	0x9bf
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x21
	.asciz	"PORTC"
	.byte	0x6
	.2byte	0x886
	.4byte	0xff5
	.byte	0x1
	.byte	0x1
	.uleb128 0x22
	.4byte	0xb7
	.uleb128 0x16
	.asciz	"myMac"
	.byte	0x1
	.byte	0x23
	.4byte	0x9bf
	.byte	0x5
	.byte	0x3
	.4byte	_myMac
	.uleb128 0x16
	.asciz	"currentBank"
	.byte	0x1
	.byte	0x24
	.4byte	0x191
	.byte	0x5
	.byte	0x3
	.4byte	_currentBank
	.uleb128 0x8
	.4byte	0x74f
	.4byte	0x1036
	.uleb128 0x9
	.4byte	0xb7
	.byte	0x1
	.byte	0x0
	.uleb128 0x16
	.asciz	"handlers"
	.byte	0x1
	.byte	0x26
	.4byte	0x1026
	.byte	0x5
	.byte	0x3
	.4byte	_handlers
	.uleb128 0x21
	.asciz	"PORTC"
	.byte	0x6
	.2byte	0x886
	.4byte	0xff5
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0xe4
	.4byte	0x106c
	.uleb128 0x9
	.4byte	0xb7
	.byte	0xff
	.byte	0x0
	.uleb128 0x23
	.asciz	"debugBuffer"
	.byte	0x1
	.byte	0xc
	.4byte	0x105c
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	_debugBuffer
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
	.uleb128 0x4
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x13
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
	.uleb128 0x7
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x13
	.byte	0x1
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
	.uleb128 0xe
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
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
	.uleb128 0xf
	.uleb128 0x17
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
	.uleb128 0x10
	.uleb128 0xd
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
	.uleb128 0x11
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x19
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x1a
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
	.byte	0x0
	.byte	0x0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x1d
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x1f
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x21
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
	.uleb128 0x22
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x23
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x2fb
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x1087
	.4byte	0x772
	.asciz	"enc28j60WriteUint8"
	.4byte	0x7b3
	.asciz	"enc28j60BitSetUint8"
	.4byte	0x7f5
	.asciz	"enc28j60BitClrUint8"
	.4byte	0x837
	.asciz	"enc28j60WriteUint16"
	.4byte	0x879
	.asciz	"enc28j60ReadUint8"
	.4byte	0x8bb
	.asciz	"enc28j60ReadMacUint8"
	.4byte	0x900
	.asciz	"enc28j60ReadUint16"
	.4byte	0x941
	.asciz	"enc28j60SetBank"
	.4byte	0x972
	.asciz	"enc28j60WriteData"
	.4byte	0x9c5
	.asciz	"enc28j60ReadRegisterUint8"
	.4byte	0xa0f
	.asciz	"enc28j60ReadRegisterUint16"
	.4byte	0xa5a
	.asciz	"enc28j60WriteRegisterUint8"
	.4byte	0xaae
	.asciz	"enc28j60BitSetRegisterUint8"
	.4byte	0xb03
	.asciz	"enc28j60BitClrRegisterUint8"
	.4byte	0xb58
	.asciz	"enc28j60WriteRegisterUint16"
	.4byte	0xbad
	.asciz	"enc28j60ReadData"
	.4byte	0xbf9
	.asciz	"enc28j60WritePhyRegisterUint16"
	.4byte	0xc46
	.asciz	"enc28j60ReadPhyRegisterUint16"
	.4byte	0xc98
	.asciz	"enc28j60TxFrame"
	.4byte	0xcf6
	.asciz	"enc28j60TxReplyFrame"
	.4byte	0xd50
	.asciz	"enc28j60PacketPending"
	.4byte	0xd79
	.asciz	"enc28j60GetPacketCount"
	.4byte	0xda3
	.asciz	"enc28j60RxFrame"
	.4byte	0xea5
	.asciz	"enc28j60RegisterTxHandler"
	.4byte	0xef2
	.asciz	"enc28j60UnregisterTxHandler"
	.4byte	0xf3b
	.asciz	"enc28j60FireTxHandlers"
	.4byte	0xf91
	.asciz	"enc28j60Reset"
	.4byte	0xfaf
	.asciz	"enc28j60Initialize"
	.4byte	0x106c
	.asciz	"debugBuffer"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x137
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x1087
	.4byte	0xf9
	.asciz	"_BOOL"
	.4byte	0x183
	.asciz	"bool_t"
	.4byte	0x191
	.asciz	"UI08_t"
	.4byte	0x19f
	.asciz	"UI16_t"
	.4byte	0x1ad
	.asciz	"EthernetFrame_s"
	.4byte	0x207
	.asciz	"EthernetFrame_t"
	.4byte	0x21e
	.asciz	"EthernetPacketHandler_t"
	.4byte	0x2a1
	.asciz	"enc28j60Register_u"
	.4byte	0x2e4
	.asciz	"enc28j60Register_t"
	.4byte	0x2fe
	.asciz	"enc28j60Addressing_e"
	.4byte	0x34a
	.asciz	"enc28j60PhyRegisters_e"
	.4byte	0x3b7
	.asciz	"enc28j60Registers_e"
	.4byte	0x70d
	.asciz	"EthernetPacketHandlerInfo_s"
	.4byte	0x74f
	.asciz	"EthernetPacketHandlerInfo_t"
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
	.ascii	"C:/Projects/Firmware/MRF49XA/Library/inc/ipstack"
	.byte 0
	.ascii	"c:\\program files (x86)\\microchip\\xc16\\v1.11\\bin\\bin\\../..\\su"
	.ascii	"pport\\PIC24F\\h"
	.byte 0
	.ascii	"c:\\program files (x86)\\microchip\\xc16\\v1.11\\bin\\bin\\../..\\su"
	.ascii	"pport\\peripheral_24F"
	.byte 0
	.byte	0x0
	.asciz	"enc28j60.c"
	.uleb128 0x1
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"bspPIC24.h"
	.uleb128 0x2
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"ipstack/ethdefs.h"
	.uleb128 0x2
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"devices/enc28j60.h"
	.uleb128 0x2
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"GenericTypeDefs.h"
	.uleb128 0x6
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"p24FJ64GB004.h"
	.uleb128 0x5
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
	.byte	0x41
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM6
	.byte	0x15
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
	.4byte	.LSM7
	.byte	0x4a
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
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM11
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM12
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM13
	.byte	0x15
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
	.4byte	.LSM14
	.byte	0x53
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
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM19
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM20
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
	.4byte	.LSM21
	.byte	0x5d
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM22
	.byte	0x15
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM28
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
	.4byte	.LSM29
	.byte	0x68
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM35
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM36
	.byte	0x17
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
	.4byte	.LSM37
	.byte	0x76
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM38
	.byte	0x16
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM44
	.byte	0x17
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
	.4byte	.LSM45
	.byte	0x84
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM46
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM47
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM48
	.byte	0x17
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
	.4byte	.LSM49
	.byte	0x8d
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM50
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM51
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM52
	.byte	0x15
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
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE7
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM62
	.byte	0xa2
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM63
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM64
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM65
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM66
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM67
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE8
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM68
	.byte	0xbf
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM69
	.byte	0x18
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
	.4byte	.LSM72
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM73
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE10
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM74
	.byte	0xcb
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM75
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM76
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM77
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM78
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM79
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE11
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM80
	.byte	0xd7
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM81
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM82
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM83
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM84
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM85
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE12
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM86
	.byte	0xe4
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM87
	.byte	0x18
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM91
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE13
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM92
	.byte	0xf1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM93
	.byte	0x18
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM97
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE14
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM98
	.byte	0xfd
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM99
	.byte	0x18
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
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM103
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM104
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE15
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM105
	.byte	0xad
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM106
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM107
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM108
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM109
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM110
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM111
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE9
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM112
	.byte	0x3
	.sleb128 247
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM113
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM114
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM115
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE16
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM116
	.byte	0x3
	.sleb128 256
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM117
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM118
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM119
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM120
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM121
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM122
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM123
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM124
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM125
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM126
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM127
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM128
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM129
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM130
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM131
	.byte	0x13
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM132
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE17
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM133
	.byte	0x3
	.sleb128 365
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM134
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM135
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM136
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM137
	.byte	0x11
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM138
	.byte	0x1b
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM139
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM140
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM141
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM142
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM143
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM144
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM145
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM146
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE19
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM147
	.byte	0x3
	.sleb128 400
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM148
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM149
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM150
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM151
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM152
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE20
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM153
	.byte	0x3
	.sleb128 495
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM154
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM155
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE22
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM156
	.byte	0x3
	.sleb128 500
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM157
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM158
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE23
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM159
	.byte	0x3
	.sleb128 413
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM160
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM161
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM162
	.byte	0x39
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM163
	.byte	0x3
	.sleb128 -35
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM164
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM165
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM166
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM167
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM168
	.byte	0x23
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM169
	.byte	0x3
	.sleb128 -15
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM170
	.byte	0x2a
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM171
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM172
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM173
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM174
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM175
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM176
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM177
	.byte	0x1a
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM178
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM179
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM180
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM181
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM182
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM183
	.byte	0x3
	.sleb128 -65
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM184
	.byte	0x5b
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE21
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM185
	.byte	0x3
	.sleb128 505
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM186
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM187
	.byte	0x1e
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM188
	.byte	0xa
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM189
	.byte	0x1b
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM190
	.byte	0xf
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM191
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM192
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM193
	.byte	0x1b
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE24
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM194
	.byte	0x3
	.sleb128 524
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM195
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM196
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM197
	.byte	0x12
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM198
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE25
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM199
	.byte	0x3
	.sleb128 540
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM200
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM201
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM202
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM203
	.byte	0x10
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM204
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM205
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM206
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE26
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM207
	.byte	0x3
	.sleb128 556
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM208
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM209
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM210
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM211
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM212
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM213
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM214
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE27
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM215
	.byte	0x3
	.sleb128 292
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM216
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM217
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM218
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM219
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM220
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM221
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM222
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM223
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM224
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM225
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM226
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM227
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM228
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM229
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM230
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM231
	.byte	0x28
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM232
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM233
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM234
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM235
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM236
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM237
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM238
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM239
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM240
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM241
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM242
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM243
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM244
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM245
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE18
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
.LELT0:
	.section	.debug_str,info
.LASF0:
	.asciz	"handler"
.LASF4:
	.asciz	"length"
.LASF1:
	.asciz	"value"
.LASF2:
	.asciz	"memAddress"
.LASF3:
	.asciz	"address"
	.section	.text,code

	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
