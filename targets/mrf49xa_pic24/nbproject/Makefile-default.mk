#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../src/bsp/softI2c.c ../../src/bsp/pic24/spi.c ../../src/devices/enc28j60.c ../../src/devices/mcp9800.c ../../src/devices/mrf49xa.c ../../src/devices/SST26VF032.c ../../src/ipstack/arp.c ../../src/ipstack/icmp.c ../../src/ipstack/ipv4.c ../../src/ipstack/ntp.c ../../src/ipstack/tcp.c ../../src/ipstack/udp.c ../../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1161282060/softI2c.o ${OBJECTDIR}/_ext/585513329/spi.o ${OBJECTDIR}/_ext/767653358/enc28j60.o ${OBJECTDIR}/_ext/767653358/mcp9800.o ${OBJECTDIR}/_ext/767653358/mrf49xa.o ${OBJECTDIR}/_ext/767653358/SST26VF032.o ${OBJECTDIR}/_ext/312626442/arp.o ${OBJECTDIR}/_ext/312626442/icmp.o ${OBJECTDIR}/_ext/312626442/ipv4.o ${OBJECTDIR}/_ext/312626442/ntp.o ${OBJECTDIR}/_ext/312626442/tcp.o ${OBJECTDIR}/_ext/312626442/udp.o ${OBJECTDIR}/_ext/1445274692/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1161282060/softI2c.o.d ${OBJECTDIR}/_ext/585513329/spi.o.d ${OBJECTDIR}/_ext/767653358/enc28j60.o.d ${OBJECTDIR}/_ext/767653358/mcp9800.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa.o.d ${OBJECTDIR}/_ext/767653358/SST26VF032.o.d ${OBJECTDIR}/_ext/312626442/arp.o.d ${OBJECTDIR}/_ext/312626442/icmp.o.d ${OBJECTDIR}/_ext/312626442/ipv4.o.d ${OBJECTDIR}/_ext/312626442/ntp.o.d ${OBJECTDIR}/_ext/312626442/tcp.o.d ${OBJECTDIR}/_ext/312626442/udp.o.d ${OBJECTDIR}/_ext/1445274692/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1161282060/softI2c.o ${OBJECTDIR}/_ext/585513329/spi.o ${OBJECTDIR}/_ext/767653358/enc28j60.o ${OBJECTDIR}/_ext/767653358/mcp9800.o ${OBJECTDIR}/_ext/767653358/mrf49xa.o ${OBJECTDIR}/_ext/767653358/SST26VF032.o ${OBJECTDIR}/_ext/312626442/arp.o ${OBJECTDIR}/_ext/312626442/icmp.o ${OBJECTDIR}/_ext/312626442/ipv4.o ${OBJECTDIR}/_ext/312626442/ntp.o ${OBJECTDIR}/_ext/312626442/tcp.o ${OBJECTDIR}/_ext/312626442/udp.o ${OBJECTDIR}/_ext/1445274692/main.o

# Source Files
SOURCEFILES=../../src/bsp/softI2c.c ../../src/bsp/pic24/spi.c ../../src/devices/enc28j60.c ../../src/devices/mcp9800.c ../../src/devices/mrf49xa.c ../../src/devices/SST26VF032.c ../../src/ipstack/arp.c ../../src/ipstack/icmp.c ../../src/ipstack/ipv4.c ../../src/ipstack/ntp.c ../../src/ipstack/tcp.c ../../src/ipstack/udp.c ../../src/main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GB004
MP_LINKER_FILE_OPTION=,--script=p24FJ64GB004.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1161282060/softI2c.o: ../../src/bsp/softI2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1161282060 
	@${RM} ${OBJECTDIR}/_ext/1161282060/softI2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1161282060/softI2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/softI2c.c  -o ${OBJECTDIR}/_ext/1161282060/softI2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1161282060/softI2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1161282060/softI2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/spi.o: ../../src/bsp/pic24/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/spi.c  -o ${OBJECTDIR}/_ext/585513329/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/spi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/enc28j60.o: ../../src/devices/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/enc28j60.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/enc28j60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/enc28j60.c  -o ${OBJECTDIR}/_ext/767653358/enc28j60.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/enc28j60.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/enc28j60.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mcp9800.o: ../../src/devices/mcp9800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mcp9800.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mcp9800.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mcp9800.c  -o ${OBJECTDIR}/_ext/767653358/mcp9800.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mcp9800.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mcp9800.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa.o: ../../src/devices/mrf49xa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/SST26VF032.o: ../../src/devices/SST26VF032.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/SST26VF032.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/SST26VF032.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/SST26VF032.c  -o ${OBJECTDIR}/_ext/767653358/SST26VF032.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/SST26VF032.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/SST26VF032.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/arp.o: ../../src/ipstack/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/arp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/arp.c  -o ${OBJECTDIR}/_ext/312626442/arp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/arp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/arp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/icmp.o: ../../src/ipstack/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/icmp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/icmp.c  -o ${OBJECTDIR}/_ext/312626442/icmp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/icmp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/icmp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/ipv4.o: ../../src/ipstack/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/ipv4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/ipv4.c  -o ${OBJECTDIR}/_ext/312626442/ipv4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/ipv4.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/ipv4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/ntp.o: ../../src/ipstack/ntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/ntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/ntp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/ntp.c  -o ${OBJECTDIR}/_ext/312626442/ntp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/ntp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/ntp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/tcp.o: ../../src/ipstack/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/tcp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/tcp.c  -o ${OBJECTDIR}/_ext/312626442/tcp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/tcp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/tcp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/udp.o: ../../src/ipstack/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/udp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/udp.c  -o ${OBJECTDIR}/_ext/312626442/udp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/udp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/udp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445274692/main.o: ../../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445274692 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/main.c  -o ${OBJECTDIR}/_ext/1445274692/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445274692/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445274692/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1161282060/softI2c.o: ../../src/bsp/softI2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1161282060 
	@${RM} ${OBJECTDIR}/_ext/1161282060/softI2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1161282060/softI2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/softI2c.c  -o ${OBJECTDIR}/_ext/1161282060/softI2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1161282060/softI2c.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1161282060/softI2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/spi.o: ../../src/bsp/pic24/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/spi.c  -o ${OBJECTDIR}/_ext/585513329/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/spi.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/enc28j60.o: ../../src/devices/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/enc28j60.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/enc28j60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/enc28j60.c  -o ${OBJECTDIR}/_ext/767653358/enc28j60.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/enc28j60.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/enc28j60.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mcp9800.o: ../../src/devices/mcp9800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mcp9800.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mcp9800.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mcp9800.c  -o ${OBJECTDIR}/_ext/767653358/mcp9800.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mcp9800.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mcp9800.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa.o: ../../src/devices/mrf49xa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/SST26VF032.o: ../../src/devices/SST26VF032.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/SST26VF032.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/SST26VF032.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/SST26VF032.c  -o ${OBJECTDIR}/_ext/767653358/SST26VF032.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/SST26VF032.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/SST26VF032.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/arp.o: ../../src/ipstack/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/arp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/arp.c  -o ${OBJECTDIR}/_ext/312626442/arp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/arp.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/arp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/icmp.o: ../../src/ipstack/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/icmp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/icmp.c  -o ${OBJECTDIR}/_ext/312626442/icmp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/icmp.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/icmp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/ipv4.o: ../../src/ipstack/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/ipv4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/ipv4.c  -o ${OBJECTDIR}/_ext/312626442/ipv4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/ipv4.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/ipv4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/ntp.o: ../../src/ipstack/ntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/ntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/ntp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/ntp.c  -o ${OBJECTDIR}/_ext/312626442/ntp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/ntp.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/ntp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/tcp.o: ../../src/ipstack/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/tcp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/tcp.c  -o ${OBJECTDIR}/_ext/312626442/tcp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/tcp.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/tcp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/312626442/udp.o: ../../src/ipstack/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/312626442 
	@${RM} ${OBJECTDIR}/_ext/312626442/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/312626442/udp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/ipstack/udp.c  -o ${OBJECTDIR}/_ext/312626442/udp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/312626442/udp.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/312626442/udp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445274692/main.o: ../../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445274692 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/main.c  -o ${OBJECTDIR}/_ext/1445274692/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445274692/main.o.d"      -g -omf=elf -save-temps=obj -Os -I"C:/Projects/Firmware/MRF49XA/Library/inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445274692/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -save-temps=obj -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
