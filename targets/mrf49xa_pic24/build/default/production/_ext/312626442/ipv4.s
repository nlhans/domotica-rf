	.file "C:\\Projects\\Firmware\\MRF49XA\\Library\\targets\\mrf49xa_pic24\\..\\..\\src\\ipstack\\ipv4.c"
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
	.global	_ipv4Init	; export
	.type	_ipv4Init,@function
_ipv4Init:
.LFB0:
.LSM0:
	.set ___PA___,1
.LSM1:
	clr.b	w0
	mov.b	WREG,_Ipv4Handlers
	mov.b	WREG,_Ipv4Handlers+4
	mov.b	WREG,_Ipv4Handlers+8
.LSM2:
	return	
	.set ___PA___,0
.LFE0:
	.align	2
	.global	_ipv4RegisterHandler	; export
	.type	_ipv4RegisterHandler,@function
_ipv4RegisterHandler:
.LFB1:
.LSM3:
	.set ___PA___,1
.LSM4:
	mov	#_Ipv4Handlers,w1
	mov.b	[w1],w1
	sub.b	w1,#0,[w15]
	.set ___BP___,4
	bra	z,.L3
	mov	#_Ipv4Handlers+4,w1
	mov.b	[w1],w1
	sub.b	w1,#0,[w15]
	.set ___BP___,4
	bra	z,.L6
	mov	#_Ipv4Handlers+8,w1
	mov.b	[w1],w1
	sub.b	w1,#0,[w15]
	.set ___BP___,95
	bra	nz,.L2
.LSM5:
	mov.b	#2,w1
	bra	.L3
.L6:
	mov.b	#1,w1
.L3:
.LSM6:
	ze	w1,w1
	sl	w1,#2,w1
	mov.b	#1,w2
	mov	#_Ipv4Handlers,w3
	mov.b	w2,[w3+w1]
.LSM7:
	inc2	w3,w2
	mov	w0,[w2+w1]
.L2:
	return	
.LFE1:
	.align	2
	.global	_ipv4UnregisterHandler	; export
	.type	_ipv4UnregisterHandler,@function
_ipv4UnregisterHandler:
.LFB2:
.LSM8:
	.set ___PA___,1
.LSM9:
	clr.b	w1
.LSM10:
	mov	#_Ipv4Handlers,w2
.L9:
	ze	w1,w3
	sl	w3,#2,w3
	inc2	w3,w4
	mov	[w2+w4],w4
	sub	w4,w0,[w15]
	.set ___BP___,85
	bra	nz,.L8
.LSM11:
	add	w2,w3,w3
	clr.b	[w3]
.L8:
.LSM12:
	inc.b	w1,w1
.LSM13:
	sub.b	w1,#2,[w15]
	.set ___BP___,66
	bra	leu,.L9
.LSM14:
	return	
	.set ___PA___,0
.LFE2:
	.align	2
	.global	_ipv4FireHandlers	; export
	.type	_ipv4FireHandlers,@function
_ipv4FireHandlers:
.LFB3:
.LSM15:
	.set ___PA___,1
	lnk	#2
	mov.d	w8,[w15++]
	mov	w0,w9
.LSM16:
	clr.b	w0
	mov.b	w0,[w15-6]
.LSM17:
	mov.b	w0,w8
	bra	.L12
.L15:
.LSM18:
	ze	w8,w2
	sl	w2,#2,w2
	mov	#_Ipv4Handlers,w1
	mov.b	[w1+w2],w0
	sub.b	w0,#1,[w15]
	.set ___BP___,86
	bra	nz,.L13
.LSM19:
	inc2	w2,w2
	mov	[w1+w2],w2
	sub	w15,#6,w1
	mov	w9,w0
	call	w2
.L13:
.LSM20:
	inc.b	w8,w8
.LSM21:
	sub.b	w8,#2,[w15]
	.set ___BP___,34
	bra	gtu,.L11
.L12:
	mov.b	[w15-6],w0
	sub.b	w0,#0,[w15]
	.set ___BP___,95
	bra	z,.L15
.L11:
.LSM22:
	mov.d	[--w15],w8
	ulnk	
	return	
	.set ___PA___,0
.LFE3:
	.align	2
	.global	_ipv4HandlePacket	; export
	.type	_ipv4HandlePacket,@function
_ipv4HandlePacket:
.LFB4:
.LSM23:
	.set ___PA___,0
.LSM24:
	mov	[w0+12],w3
	mov	#2048,w2
	sub	w3,w2,[w15]
	.set ___BP___,80
	bra	nz,.L16
.LSM25:
	mov.b	#1,w2
	mov.b	w2,[w1]
.LSM26:
	mov	[w0+16],w1
	sl	w1,#8,w2
	lsr	w1,#8,w1
	ior	w2,w1,w1
	mov	w1,[w0+16]
.LSM27:
; 85 "../../src/ipstack/ipv4.c" 1
	nop
.LSM28:
	rcall	_ipv4FireHandlers
.L16:
	return	
.LFE4:
	.align	2
	.global	_ipv4Crc	; export
	.type	_ipv4Crc,@function
_ipv4Crc:
.LFB5:
.LSM29:
	.set ___PA___,1
	lnk	#10
.LSM30:
	clr	w2
	mov	w2,[w15-10]
.LSM31:
	mul.uu	w2,#0,w2
	mov	w2,[w15-8]
	mov	w3,[w15-6]
.LSM32:
	mov	w2,[w15-4]
	mov	w3,[w15-2]
.LSM33:
	lsr	w1,w1
	bra	.L19
.L20:
.LSM34:
	mov	[w15-4],w4
	mov	[w15-2],w5
	mov	[w15-10],w2
	add	w2,w2,w2
	mov	[w0+w2],w2
	mov	[w15-10],w3
	add	w3,w3,w3
	mov	[w0+w3],w3
	sl	w3,#8,w3
	lsr	w2,#8,w2
	ior	w3,w2,w2
	add	w4,w2,w2
	addc	w5,#0,w3
	mov	w2,[w15-4]
	mov	w3,[w15-2]
.LSM35:
	mov	[w15-10],w2
	inc	w2,w2
	mov	w2,[w15-10]
.L19:
.LSM36:
	mov	[w15-10],w2
	sub	w2,w1,[w15]
	.set ___BP___,91
	bra	ltu,.L20
.LSM37:
	mov	[w15-4],w0
	mov	[w15-2],w1
	mov	w1,[w15-10]
.LSM38:
	mov	[w15-4],w0
	mov	[w15-2],w1
	mov	#0,w1
	mov	w0,[w15-4]
	mov	w1,[w15-2]
.LSM39:
	mov	[w15-4],w0
	mov	[w15-2],w1
	mov	[w15-10],w2
	add	w0,w2,w0
	addc	w1,#0,w1
	mov	w0,[w15-4]
	mov	w1,[w15-2]
.LSM40:
	mov	[w15-4],w0
	mov	[w15-2],w1
	com	w0,w0
	com	w1,w1
	mov	w0,[w15-8]
	mov	w1,[w15-6]
.LSM41:
	mov	[w15-8],w0
	mov	[w15-6],w1
.LSM42:
	ulnk	
	return	
	.set ___PA___,0
.LFE5:
	.align	2
	.global	_ipv4TxReplyPacket	; export
	.type	_ipv4TxReplyPacket,@function
_ipv4TxReplyPacket:
.LFB6:
.LSM43:
	.set ___PA___,0
	lnk	#4
	mov.d	w8,[w15++]
	mov.d	w10,[w15++]
	mov	w0,w8
.LSM44:
	mov	[w8+30],w2
	mov	[w8+32],w3
	mov	w2,[w15-12]
	mov	w3,[w15-10]
.LSM45:
	mov	[w8+26],w2
	mov	[w8+28],w3
	mov	w2,[w8+30]
	mov	w3,[w8+32]
.LSM46:
	mov	[w15-12],w2
	mov	[w15-10],w3
	mov	w2,[w8+26]
	mov	w3,[w8+28]
.LSM47:
	clr	w0
	mov	w0,[w8+24]
.LSM48:
	mov	w0,[w8+20]
.LSM49:
	add.b	w1,#20,w1
.LSM50:
	ze	w1,w10
.LSM51:
	mov	[w8+12],w0
	sl	w0,#8,w1
	lsr	w0,#8,w0
	ior	w1,w0,w0
	mov	w0,[w8+12]
.LSM52:
	sl	w10,#8,w0
	mov	w0,[w8+16]
.LSM53:
	add	w8,#14,w9
	mov	[w8+14],w1
	and	w1,#15,w1
	sl	w1,#2,w1
	mov	w9,w0
	rcall	_ipv4Crc
	mov	w0,w11
	mov	[w8+14],w1
	and	w1,#15,w1
	sl	w1,#2,w1
	mov	w9,w0
	rcall	_ipv4Crc
	sl	w0,#8,w2
	lsr	w11,#8,w1
	ior	w2,w1,w0
	mov	w0,[w8+24]
.LSM54:
; 134 "../../src/ipstack/ipv4.c" 1
	nop
.LSM55:
	mov	w10,w1
	mov	w8,w0
	rcall	_macTxReplyFrame
.LSM56:
	mov.d	[--w15],w10
	mov.d	[--w15],w8
	ulnk	
	return	
	.set ___PA___,0
.LFE6:
	.align	2
	.global	_ipv4TxPacket	; export
	.type	_ipv4TxPacket,@function
_ipv4TxPacket:
.LFB7:
.LSM57:
	.set ___PA___,0
	mov.d	w8,[w15++]
	mov.d	w10,[w15++]
	mov	w2,w8
.LSM58:
	add	w3,#20,w9
.LSM59:
	mov	#_gw,w2
	repeat	#6-1
	mov.b	[w2++],[w8++]
	sub	#6, w8
.LSM60:
	mov	w8,w3
	add	#6,w3
	mov	#_thisMac,w2
	repeat	#6-1
	mov.b	[w2++],[w3++]
.LSM61:
	mov	#8,w2
	mov	w2,[w8+12]
.LSM62:
	mov	w8,w3
	add	#30,w3
	repeat	#4-1
	mov.b	[w0++],[w3++]
	sub	#4, w0
.LSM63:
	mov	w8,w0
	add	#26,w0
	mov	#_thisIp,w2
	repeat	#4-1
	mov.b	[w2++],[w0++]
.LSM64:
	mov	[w8+14],w2
	mov	#-241,w0
	and	w2,w0,w0
	bset	w0,#6
.LSM65:
	mov	#-16,w2
	and	w0,w2,w0
	ior	#5,w0
	mov	w0,[w8+14]
.LSM66:
	clr.b	w0
	mov.b	w0,[w8+15]
.LSM67:
	sl	w9,#8,w2
	lsr	w9,#8,w0
	ior	w2,w0,w0
	mov	w0,[w8+16]
.LSM68:
	mov	#13330,w0
	mov	w0,[w8+18]
.LSM69:
	clr	w2
	mov	w2,[w8+20]
.LSM70:
	mov.b	#-128,w0
	mov.b	w0,[w8+22]
.LSM71:
	mov.b	w1,[w8+23]
.LSM72:
	mov	w2,[w8+24]
.LSM73:
	add	w8,#14,w10
	mov	#20,w1
	mov	w10,w0
	rcall	_ipv4Crc
	mov	w0,w11
	mov	[w8+14],w1
	and	w1,#15,w1
	sl	w1,#2,w1
	mov	w10,w0
	rcall	_ipv4Crc
	sl	w0,#8,w2
	lsr	w11,#8,w1
	ior	w2,w1,w0
	mov	w0,[w8+24]
.LSM74:
; 164 "../../src/ipstack/ipv4.c" 1
	nop
.LSM75:
	add	w9,#14,w1
	mov	w8,w0
	rcall	_macTxFrame
.LSM76:
	mov.d	[--w15],w10
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE7:
	.global	_gw	; export
	.section	.ndata,data,near
	.type	_gw,@object
_gw:
	.byte -80
	.byte 72
	.byte 122
	.byte -37
	.byte 91
	.byte -22
	.section	.nbss,bss,near
	.type	_Ipv4Handlers,@object
	.global	_Ipv4Handlers
	.align	2
_Ipv4Handlers:	.space	12
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
	.4byte	0x78f
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1_11) (A) Build date: Nov 17 2012"
	.byte	0x1
	.asciz	"../../src/ipstack/ipv4.c"
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
	.byte	0x4
	.byte	0x40
	.4byte	0x113
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
	.4byte	0x13f
	.uleb128 0x5
	.asciz	"UI08_t"
	.byte	0x2
	.byte	0x66
	.4byte	0x13f
	.uleb128 0x5
	.asciz	"UI16_t"
	.byte	0x2
	.byte	0x67
	.4byte	0xb3
	.uleb128 0x5
	.asciz	"UI32_t"
	.byte	0x2
	.byte	0x68
	.4byte	0x150
	.uleb128 0x6
	.asciz	"EthernetFrame_s"
	.byte	0xe
	.byte	0x3
	.byte	0x7
	.4byte	0x201
	.uleb128 0x7
	.asciz	"dstMac"
	.byte	0x3
	.byte	0x9
	.4byte	0x201
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x7
	.asciz	"srcMac"
	.byte	0x3
	.byte	0xa
	.4byte	0x201
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x7
	.asciz	"type"
	.byte	0x3
	.byte	0xb
	.4byte	0x19b
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0x0
	.uleb128 0x8
	.4byte	0x18d
	.4byte	0x211
	.uleb128 0x9
	.4byte	0xb3
	.byte	0x5
	.byte	0x0
	.uleb128 0x5
	.asciz	"EthernetFrame_t"
	.byte	0x3
	.byte	0xc
	.4byte	0x1b7
	.uleb128 0x3
	.asciz	"EthernetProtocol_e"
	.byte	0x2
	.byte	0x3
	.byte	0xe
	.4byte	0x263
	.uleb128 0x4
	.asciz	"ProtocolIPv4"
	.sleb128 2048
	.uleb128 0x4
	.asciz	"ProtocolARP"
	.sleb128 2054
	.byte	0x0
	.uleb128 0xa
	.byte	0x2
	.4byte	0x211
	.uleb128 0xa
	.byte	0x2
	.4byte	0x17f
	.uleb128 0x6
	.asciz	"EthernetIpv4Header_s"
	.byte	0x14
	.byte	0x5
	.byte	0x1c
	.4byte	0x34c
	.uleb128 0xb
	.asciz	"ihl"
	.byte	0x5
	.byte	0x1e
	.4byte	0x18d
	.byte	0x1
	.byte	0x4
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xb
	.asciz	"version"
	.byte	0x5
	.byte	0x1f
	.4byte	0x18d
	.byte	0x1
	.byte	0x4
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x7
	.asciz	"DSCP"
	.byte	0x5
	.byte	0x20
	.4byte	0x18d
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x7
	.asciz	"length"
	.byte	0x5
	.byte	0x21
	.4byte	0x19b
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x7
	.asciz	"ID"
	.byte	0x5
	.byte	0x23
	.4byte	0x19b
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x7
	.asciz	"flags"
	.byte	0x5
	.byte	0x24
	.4byte	0x19b
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x7
	.asciz	"timeToLive"
	.byte	0x5
	.byte	0x25
	.4byte	0x18d
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xc
	.4byte	.LASF0
	.byte	0x5
	.byte	0x26
	.4byte	0x18d
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.uleb128 0x7
	.asciz	"crc"
	.byte	0x5
	.byte	0x27
	.4byte	0x34c
	.byte	0x2
	.byte	0x23
	.uleb128 0xa
	.uleb128 0x7
	.asciz	"sourceIp"
	.byte	0x5
	.byte	0x29
	.4byte	0x351
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x7
	.asciz	"destinationIp"
	.byte	0x5
	.byte	0x2a
	.4byte	0x351
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0x0
	.uleb128 0xd
	.4byte	0x19b
	.uleb128 0x8
	.4byte	0x18d
	.4byte	0x361
	.uleb128 0x9
	.4byte	0xb3
	.byte	0x3
	.byte	0x0
	.uleb128 0x5
	.asciz	"EthernetIpv4Header_t"
	.byte	0x5
	.byte	0x2c
	.4byte	0x26f
	.uleb128 0x6
	.asciz	"EthernetIpv4_s"
	.byte	0x22
	.byte	0x5
	.byte	0x2e
	.4byte	0x3b6
	.uleb128 0x7
	.asciz	"frame"
	.byte	0x5
	.byte	0x30
	.4byte	0x211
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x7
	.asciz	"header"
	.byte	0x5
	.byte	0x31
	.4byte	0x361
	.byte	0x2
	.byte	0x23
	.uleb128 0xe
	.byte	0x0
	.uleb128 0x5
	.asciz	"EthernetIpv4_t"
	.byte	0x5
	.byte	0x32
	.4byte	0x37d
	.uleb128 0x5
	.asciz	"Ipv4PacketHandler_t"
	.byte	0x5
	.byte	0x34
	.4byte	0x3e7
	.uleb128 0xa
	.byte	0x2
	.4byte	0x3ed
	.uleb128 0xe
	.byte	0x1
	.4byte	0x3fe
	.uleb128 0xf
	.4byte	0x3fe
	.uleb128 0xf
	.4byte	0x269
	.byte	0x0
	.uleb128 0xa
	.byte	0x2
	.4byte	0x3b6
	.uleb128 0x6
	.asciz	"Ipv4PacketHandlerInfo_s"
	.byte	0x4
	.byte	0x1
	.byte	0x7
	.4byte	0x446
	.uleb128 0x7
	.asciz	"used"
	.byte	0x1
	.byte	0x9
	.4byte	0x17f
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x7
	.asciz	"handler"
	.byte	0x1
	.byte	0xa
	.4byte	0x3cc
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0x0
	.uleb128 0x5
	.asciz	"Ipv4PacketHandlerInfo_t"
	.byte	0x1
	.byte	0xb
	.4byte	0x404
	.uleb128 0x10
	.byte	0x1
	.asciz	"ipv4Init"
	.byte	0x1
	.byte	0xf
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.4byte	0x48a
	.uleb128 0x11
	.asciz	"i"
	.byte	0x1
	.byte	0x11
	.4byte	0x18d
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"ipv4RegisterHandler"
	.byte	0x1
	.byte	0x19
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.4byte	0x4ca
	.uleb128 0x13
	.4byte	.LASF1
	.byte	0x1
	.byte	0x19
	.4byte	0x3cc
	.byte	0x1
	.byte	0x50
	.uleb128 0x14
	.asciz	"i"
	.byte	0x1
	.byte	0x1b
	.4byte	0x18d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"ipv4UnregisterHandler"
	.byte	0x1
	.byte	0x29
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.4byte	0x50c
	.uleb128 0x13
	.4byte	.LASF1
	.byte	0x1
	.byte	0x29
	.4byte	0x3cc
	.byte	0x1
	.byte	0x50
	.uleb128 0x14
	.asciz	"i"
	.byte	0x1
	.byte	0x2b
	.4byte	0x18d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"ipv4FireHandlers"
	.byte	0x1
	.byte	0x38
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.4byte	0x55a
	.uleb128 0x15
	.asciz	"frame"
	.byte	0x1
	.byte	0x38
	.4byte	0x3fe
	.byte	0x1
	.byte	0x59
	.uleb128 0x14
	.asciz	"i"
	.byte	0x1
	.byte	0x3a
	.4byte	0x18d
	.byte	0x1
	.byte	0x58
	.uleb128 0x14
	.asciz	"done"
	.byte	0x1
	.byte	0x3b
	.4byte	0x17f
	.byte	0x2
	.byte	0x91
	.sleb128 -6
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"ipv4HandlePacket"
	.byte	0x1
	.byte	0x47
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.4byte	0x5c3
	.uleb128 0x15
	.asciz	"frame"
	.byte	0x1
	.byte	0x47
	.4byte	0x263
	.byte	0x1
	.byte	0x50
	.uleb128 0x15
	.asciz	"handled"
	.byte	0x1
	.byte	0x47
	.4byte	0x269
	.byte	0x1
	.byte	0x51
	.uleb128 0x11
	.asciz	"ipv4Header"
	.byte	0x1
	.byte	0x49
	.4byte	0x3fe
	.uleb128 0x11
	.asciz	"headerSize"
	.byte	0x1
	.byte	0x4a
	.4byte	0x18d
	.byte	0x0
	.uleb128 0x16
	.byte	0x1
	.asciz	"ipv4Crc"
	.byte	0x1
	.byte	0x5d
	.byte	0x1
	.4byte	0x19b
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.4byte	0x645
	.uleb128 0x15
	.asciz	"data"
	.byte	0x1
	.byte	0x5d
	.4byte	0x645
	.byte	0x1
	.byte	0x50
	.uleb128 0x15
	.asciz	"size"
	.byte	0x1
	.byte	0x5d
	.4byte	0x19b
	.byte	0x1
	.byte	0x51
	.uleb128 0x14
	.asciz	"b"
	.byte	0x1
	.byte	0x5f
	.4byte	0x34c
	.byte	0x2
	.byte	0x91
	.sleb128 -10
	.uleb128 0x11
	.asciz	"dataUI16"
	.byte	0x1
	.byte	0x60
	.4byte	0x64b
	.uleb128 0x14
	.asciz	"crc"
	.byte	0x1
	.byte	0x61
	.4byte	0x651
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0x14
	.asciz	"sum"
	.byte	0x1
	.byte	0x62
	.4byte	0x651
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x11
	.asciz	"counts"
	.byte	0x1
	.byte	0x63
	.4byte	0x18d
	.byte	0x0
	.uleb128 0xa
	.byte	0x2
	.4byte	0x18d
	.uleb128 0xa
	.byte	0x2
	.4byte	0x34c
	.uleb128 0xd
	.4byte	0x1a9
	.uleb128 0x12
	.byte	0x1
	.asciz	"ipv4TxReplyPacket"
	.byte	0x1
	.byte	0x75
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.4byte	0x6ac
	.uleb128 0x13
	.4byte	.LASF2
	.byte	0x1
	.byte	0x75
	.4byte	0x3fe
	.byte	0x1
	.byte	0x58
	.uleb128 0x15
	.asciz	"totalSize"
	.byte	0x1
	.byte	0x75
	.4byte	0x18d
	.byte	0x1
	.byte	0x51
	.uleb128 0x14
	.asciz	"ipTmp"
	.byte	0x1
	.byte	0x78
	.4byte	0x351
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.asciz	"ipv4TxPacket"
	.byte	0x1
	.byte	0x8d
	.byte	0x1
	.4byte	.LFB7
	.4byte	.LFE7
	.byte	0x1
	.byte	0x5f
	.4byte	0x704
	.uleb128 0x15
	.asciz	"dstIp"
	.byte	0x1
	.byte	0x8d
	.4byte	0x645
	.byte	0x1
	.byte	0x50
	.uleb128 0x13
	.4byte	.LASF0
	.byte	0x1
	.byte	0x8d
	.4byte	0x18d
	.byte	0x1
	.byte	0x51
	.uleb128 0x13
	.4byte	.LASF2
	.byte	0x1
	.byte	0x8d
	.4byte	0x3fe
	.byte	0x1
	.byte	0x58
	.uleb128 0x15
	.asciz	"size"
	.byte	0x1
	.byte	0x8d
	.4byte	0x19b
	.byte	0x1
	.byte	0x53
	.byte	0x0
	.uleb128 0x17
	.asciz	"thisIp"
	.byte	0x6
	.byte	0x26
	.4byte	0x351
	.byte	0x1
	.byte	0x1
	.uleb128 0x17
	.asciz	"thisMac"
	.byte	0x6
	.byte	0x27
	.4byte	0x201
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x446
	.4byte	0x735
	.uleb128 0x9
	.4byte	0xb3
	.byte	0x2
	.byte	0x0
	.uleb128 0x18
	.4byte	.LASF3
	.byte	0x1
	.byte	0xd
	.4byte	0x725
	.byte	0x1
	.byte	0x1
	.uleb128 0x17
	.asciz	"gw"
	.byte	0x1
	.byte	0x8c
	.4byte	0x201
	.byte	0x1
	.byte	0x1
	.uleb128 0x17
	.asciz	"thisIp"
	.byte	0x6
	.byte	0x26
	.4byte	0x351
	.byte	0x1
	.byte	0x1
	.uleb128 0x17
	.asciz	"thisMac"
	.byte	0x6
	.byte	0x27
	.4byte	0x201
	.byte	0x1
	.byte	0x1
	.uleb128 0x19
	.4byte	.LASF3
	.byte	0x1
	.byte	0xd
	.4byte	0x725
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	_Ipv4Handlers
	.uleb128 0x1a
	.asciz	"gw"
	.byte	0x1
	.byte	0x8c
	.4byte	0x201
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	_gw
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
	.uleb128 0xc
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
	.uleb128 0xd
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.4byte	0xc2
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x793
	.4byte	0x465
	.asciz	"ipv4Init"
	.4byte	0x48a
	.asciz	"ipv4RegisterHandler"
	.4byte	0x4ca
	.asciz	"ipv4UnregisterHandler"
	.4byte	0x50c
	.asciz	"ipv4FireHandlers"
	.4byte	0x55a
	.asciz	"ipv4HandlePacket"
	.4byte	0x5c3
	.asciz	"ipv4Crc"
	.4byte	0x656
	.asciz	"ipv4TxReplyPacket"
	.4byte	0x6ac
	.asciz	"ipv4TxPacket"
	.4byte	0x76f
	.asciz	"Ipv4Handlers"
	.4byte	0x781
	.asciz	"gw"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x12b
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x793
	.4byte	0xf5
	.asciz	"_BOOL"
	.4byte	0x17f
	.asciz	"bool_t"
	.4byte	0x18d
	.asciz	"UI08_t"
	.4byte	0x19b
	.asciz	"UI16_t"
	.4byte	0x1a9
	.asciz	"UI32_t"
	.4byte	0x1b7
	.asciz	"EthernetFrame_s"
	.4byte	0x211
	.asciz	"EthernetFrame_t"
	.4byte	0x228
	.asciz	"EthernetProtocol_e"
	.4byte	0x26f
	.asciz	"EthernetIpv4Header_s"
	.4byte	0x361
	.asciz	"EthernetIpv4Header_t"
	.4byte	0x37d
	.asciz	"EthernetIpv4_s"
	.4byte	0x3b6
	.asciz	"EthernetIpv4_t"
	.4byte	0x3cc
	.asciz	"Ipv4PacketHandler_t"
	.4byte	0x404
	.asciz	"Ipv4PacketHandlerInfo_s"
	.4byte	0x446
	.asciz	"Ipv4PacketHandlerInfo_t"
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
	.ascii	"../../src/ipstack"
	.byte 0
	.ascii	"C:/Projects/Firmware/MRF49XA/Library/inc"
	.byte 0
	.ascii	"C:/Projects/Firmware/MRF49XA/Library/inc/ipstack"
	.byte 0
	.ascii	"c:\\program files (x86)\\microchip\\xc16\\v1.11\\bin\\bin\\../..\\su"
	.ascii	"pport\\peripheral_24F"
	.byte 0
	.byte	0x0
	.asciz	"ipv4.c"
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
	.asciz	"GenericTypeDefs.h"
	.uleb128 0x4
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"ipstack/ipv4.h"
	.uleb128 0x2
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"ipstack/arp.h"
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
	.byte	0x23
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM1
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM2
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
	.4byte	.LSM3
	.byte	0x2d
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM4
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM5
	.byte	0x1a
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM6
	.byte	0x10
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM7
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
	.4byte	.LSM8
	.byte	0x3d
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM9
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM10
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM11
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM12
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM13
	.byte	0xe
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM14
	.byte	0x1c
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
	.4byte	.LSM15
	.byte	0x4c
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM16
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM17
	.byte	0x13
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM18
	.byte	0x19
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM19
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM20
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM21
	.byte	0xe
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM22
	.byte	0x1c
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
	.4byte	.LSM23
	.byte	0x5b
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM24
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM25
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM26
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM27
	.byte	0x18
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM28
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
	.4byte	.LSM29
	.byte	0x71
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM30
	.byte	0x15
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
	.byte	0x17
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
	.byte	0x11
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM37
	.byte	0x1c
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM38
	.byte	0x15
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM42
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
	.4byte	.LSM43
	.byte	0x89
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM44
	.byte	0x18
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
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM48
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM49
	.byte	0xb
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM50
	.byte	0x1e
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM51
	.byte	0x15
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM55
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM56
	.byte	0x15
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
	.4byte	.LSM57
	.byte	0xa1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM58
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM59
	.byte	0x17
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
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM63
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM64
	.byte	0x16
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
	.4byte	.LSM72
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM73
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM74
	.byte	0x16
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM75
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM76
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE7
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
.LELT0:
	.section	.debug_str,info
.LASF1:
	.asciz	"myHandler"
.LASF0:
	.asciz	"protocol"
.LASF2:
	.asciz	"ipv4Packet"
.LASF3:
	.asciz	"Ipv4Handlers"
	.section	.text,code

	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
