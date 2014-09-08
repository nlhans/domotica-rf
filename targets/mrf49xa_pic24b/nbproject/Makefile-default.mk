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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24b.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24b.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../src/bsp/pic24/adc.c ../../src/bsp/pic24/context.s ../../src/bsp/pic24/i2c.c ../../src/bsp/pic24/interrupt.c ../../src/bsp/pic24/rtc.c ../../src/bsp/pic24/rtos.c ../../src/bsp/pic24/spi.c ../../src/bsp/pic24/timer.c ../../src/bsp/pic24/uart.c ../../src/devices/SST26VF032.c ../../src/devices/enc28j60.c ../../src/devices/mcp9800.c ../../src/devices/mrf49xa.c ../../src/devices/mrf49xa_cmd.c ../../src/devices/mrf49xa_spi_pic24.c ../../src/devices/mrf49xa_mac.c ../../src/devices/mrf49xa_phy.c ../../src/server/ipstack/arp.c ../../src/server/ipstack/icmp.c ../../src/server/ipstack/ipv4.c ../../src/server/ipstack/ntp.c ../../src/server/ipstack/tcp.c ../../src/server/ipstack/udp.c ../../src/rfstack/packets.c ../../src/rfstack/server.c ../../src/server/rtos/task.c ../../src/server/rtos/timer.c ../../src/server/tasks/rf_task.c ../../src/server/tasks/eth_task.c ../../src/server/utilities/executiontime.c ../../src/server/utilities/spiArbiter.c ../../src/utilities/ccbuf.c ../../src/server/webserver/router.c ../../src/server/main.c ../../src/server/config.c ../../src/bsp/common/softI2c.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/585513329/adc.o ${OBJECTDIR}/_ext/585513329/context.o ${OBJECTDIR}/_ext/585513329/i2c.o ${OBJECTDIR}/_ext/585513329/interrupt.o ${OBJECTDIR}/_ext/585513329/rtc.o ${OBJECTDIR}/_ext/585513329/rtos.o ${OBJECTDIR}/_ext/585513329/spi.o ${OBJECTDIR}/_ext/585513329/timer.o ${OBJECTDIR}/_ext/585513329/uart.o ${OBJECTDIR}/_ext/767653358/SST26VF032.o ${OBJECTDIR}/_ext/767653358/enc28j60.o ${OBJECTDIR}/_ext/767653358/mcp9800.o ${OBJECTDIR}/_ext/767653358/mrf49xa.o ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o ${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o ${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o ${OBJECTDIR}/_ext/2033261600/arp.o ${OBJECTDIR}/_ext/2033261600/icmp.o ${OBJECTDIR}/_ext/2033261600/ipv4.o ${OBJECTDIR}/_ext/2033261600/ntp.o ${OBJECTDIR}/_ext/2033261600/tcp.o ${OBJECTDIR}/_ext/2033261600/udp.o ${OBJECTDIR}/_ext/1201319415/packets.o ${OBJECTDIR}/_ext/1201319415/server.o ${OBJECTDIR}/_ext/1209926055/task.o ${OBJECTDIR}/_ext/1209926055/timer.o ${OBJECTDIR}/_ext/1145713235/rf_task.o ${OBJECTDIR}/_ext/1145713235/eth_task.o ${OBJECTDIR}/_ext/1709695401/executiontime.o ${OBJECTDIR}/_ext/1709695401/spiArbiter.o ${OBJECTDIR}/_ext/2125849857/ccbuf.o ${OBJECTDIR}/_ext/296506934/router.o ${OBJECTDIR}/_ext/681662318/main.o ${OBJECTDIR}/_ext/681662318/config.o ${OBJECTDIR}/_ext/604762726/softI2c.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/585513329/adc.o.d ${OBJECTDIR}/_ext/585513329/context.o.d ${OBJECTDIR}/_ext/585513329/i2c.o.d ${OBJECTDIR}/_ext/585513329/interrupt.o.d ${OBJECTDIR}/_ext/585513329/rtc.o.d ${OBJECTDIR}/_ext/585513329/rtos.o.d ${OBJECTDIR}/_ext/585513329/spi.o.d ${OBJECTDIR}/_ext/585513329/timer.o.d ${OBJECTDIR}/_ext/585513329/uart.o.d ${OBJECTDIR}/_ext/767653358/SST26VF032.o.d ${OBJECTDIR}/_ext/767653358/enc28j60.o.d ${OBJECTDIR}/_ext/767653358/mcp9800.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o.d ${OBJECTDIR}/_ext/2033261600/arp.o.d ${OBJECTDIR}/_ext/2033261600/icmp.o.d ${OBJECTDIR}/_ext/2033261600/ipv4.o.d ${OBJECTDIR}/_ext/2033261600/ntp.o.d ${OBJECTDIR}/_ext/2033261600/tcp.o.d ${OBJECTDIR}/_ext/2033261600/udp.o.d ${OBJECTDIR}/_ext/1201319415/packets.o.d ${OBJECTDIR}/_ext/1201319415/server.o.d ${OBJECTDIR}/_ext/1209926055/task.o.d ${OBJECTDIR}/_ext/1209926055/timer.o.d ${OBJECTDIR}/_ext/1145713235/rf_task.o.d ${OBJECTDIR}/_ext/1145713235/eth_task.o.d ${OBJECTDIR}/_ext/1709695401/executiontime.o.d ${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d ${OBJECTDIR}/_ext/2125849857/ccbuf.o.d ${OBJECTDIR}/_ext/296506934/router.o.d ${OBJECTDIR}/_ext/681662318/main.o.d ${OBJECTDIR}/_ext/681662318/config.o.d ${OBJECTDIR}/_ext/604762726/softI2c.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/585513329/adc.o ${OBJECTDIR}/_ext/585513329/context.o ${OBJECTDIR}/_ext/585513329/i2c.o ${OBJECTDIR}/_ext/585513329/interrupt.o ${OBJECTDIR}/_ext/585513329/rtc.o ${OBJECTDIR}/_ext/585513329/rtos.o ${OBJECTDIR}/_ext/585513329/spi.o ${OBJECTDIR}/_ext/585513329/timer.o ${OBJECTDIR}/_ext/585513329/uart.o ${OBJECTDIR}/_ext/767653358/SST26VF032.o ${OBJECTDIR}/_ext/767653358/enc28j60.o ${OBJECTDIR}/_ext/767653358/mcp9800.o ${OBJECTDIR}/_ext/767653358/mrf49xa.o ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o ${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o ${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o ${OBJECTDIR}/_ext/2033261600/arp.o ${OBJECTDIR}/_ext/2033261600/icmp.o ${OBJECTDIR}/_ext/2033261600/ipv4.o ${OBJECTDIR}/_ext/2033261600/ntp.o ${OBJECTDIR}/_ext/2033261600/tcp.o ${OBJECTDIR}/_ext/2033261600/udp.o ${OBJECTDIR}/_ext/1201319415/packets.o ${OBJECTDIR}/_ext/1201319415/server.o ${OBJECTDIR}/_ext/1209926055/task.o ${OBJECTDIR}/_ext/1209926055/timer.o ${OBJECTDIR}/_ext/1145713235/rf_task.o ${OBJECTDIR}/_ext/1145713235/eth_task.o ${OBJECTDIR}/_ext/1709695401/executiontime.o ${OBJECTDIR}/_ext/1709695401/spiArbiter.o ${OBJECTDIR}/_ext/2125849857/ccbuf.o ${OBJECTDIR}/_ext/296506934/router.o ${OBJECTDIR}/_ext/681662318/main.o ${OBJECTDIR}/_ext/681662318/config.o ${OBJECTDIR}/_ext/604762726/softI2c.o

# Source Files
SOURCEFILES=../../src/bsp/pic24/adc.c ../../src/bsp/pic24/context.s ../../src/bsp/pic24/i2c.c ../../src/bsp/pic24/interrupt.c ../../src/bsp/pic24/rtc.c ../../src/bsp/pic24/rtos.c ../../src/bsp/pic24/spi.c ../../src/bsp/pic24/timer.c ../../src/bsp/pic24/uart.c ../../src/devices/SST26VF032.c ../../src/devices/enc28j60.c ../../src/devices/mcp9800.c ../../src/devices/mrf49xa.c ../../src/devices/mrf49xa_cmd.c ../../src/devices/mrf49xa_spi_pic24.c ../../src/devices/mrf49xa_mac.c ../../src/devices/mrf49xa_phy.c ../../src/server/ipstack/arp.c ../../src/server/ipstack/icmp.c ../../src/server/ipstack/ipv4.c ../../src/server/ipstack/ntp.c ../../src/server/ipstack/tcp.c ../../src/server/ipstack/udp.c ../../src/rfstack/packets.c ../../src/rfstack/server.c ../../src/server/rtos/task.c ../../src/server/rtos/timer.c ../../src/server/tasks/rf_task.c ../../src/server/tasks/eth_task.c ../../src/server/utilities/executiontime.c ../../src/server/utilities/spiArbiter.c ../../src/utilities/ccbuf.c ../../src/server/webserver/router.c ../../src/server/main.c ../../src/server/config.c ../../src/bsp/common/softI2c.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24b.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GB004
MP_LINKER_FILE_OPTION=,--script=p24FJ64GB004.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/585513329/adc.o: ../../src/bsp/pic24/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/adc.c  -o ${OBJECTDIR}/_ext/585513329/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/i2c.o: ../../src/bsp/pic24/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/i2c.c  -o ${OBJECTDIR}/_ext/585513329/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/i2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/interrupt.o: ../../src/bsp/pic24/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/interrupt.c  -o ${OBJECTDIR}/_ext/585513329/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/interrupt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/interrupt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/rtc.o: ../../src/bsp/pic24/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/rtc.c  -o ${OBJECTDIR}/_ext/585513329/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/rtc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/rtos.o: ../../src/bsp/pic24/rtos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtos.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/rtos.c  -o ${OBJECTDIR}/_ext/585513329/rtos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/rtos.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/rtos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/spi.o: ../../src/bsp/pic24/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/spi.c  -o ${OBJECTDIR}/_ext/585513329/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/spi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/timer.o: ../../src/bsp/pic24/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/timer.c  -o ${OBJECTDIR}/_ext/585513329/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/uart.o: ../../src/bsp/pic24/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/uart.c  -o ${OBJECTDIR}/_ext/585513329/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/SST26VF032.o: ../../src/devices/SST26VF032.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/SST26VF032.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/SST26VF032.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/SST26VF032.c  -o ${OBJECTDIR}/_ext/767653358/SST26VF032.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/SST26VF032.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/SST26VF032.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/enc28j60.o: ../../src/devices/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/enc28j60.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/enc28j60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/enc28j60.c  -o ${OBJECTDIR}/_ext/767653358/enc28j60.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/enc28j60.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/enc28j60.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mcp9800.o: ../../src/devices/mcp9800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mcp9800.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mcp9800.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mcp9800.c  -o ${OBJECTDIR}/_ext/767653358/mcp9800.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mcp9800.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mcp9800.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa.o: ../../src/devices/mrf49xa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o: ../../src/devices/mrf49xa_cmd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_cmd.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o: ../../src/devices/mrf49xa_spi_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_spi_pic24.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o: ../../src/devices/mrf49xa_mac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_mac.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o: ../../src/devices/mrf49xa_phy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_phy.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/arp.o: ../../src/server/ipstack/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/arp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/arp.c  -o ${OBJECTDIR}/_ext/2033261600/arp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/arp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/arp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/icmp.o: ../../src/server/ipstack/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/icmp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/icmp.c  -o ${OBJECTDIR}/_ext/2033261600/icmp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/icmp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/icmp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/ipv4.o: ../../src/server/ipstack/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/ipv4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/ipv4.c  -o ${OBJECTDIR}/_ext/2033261600/ipv4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/ipv4.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/ipv4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/ntp.o: ../../src/server/ipstack/ntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/ntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/ntp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/ntp.c  -o ${OBJECTDIR}/_ext/2033261600/ntp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/ntp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/ntp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/tcp.o: ../../src/server/ipstack/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/tcp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/tcp.c  -o ${OBJECTDIR}/_ext/2033261600/tcp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/tcp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/tcp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/udp.o: ../../src/server/ipstack/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/udp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/udp.c  -o ${OBJECTDIR}/_ext/2033261600/udp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/udp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/udp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1201319415/packets.o: ../../src/rfstack/packets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1201319415 
	@${RM} ${OBJECTDIR}/_ext/1201319415/packets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1201319415/packets.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/rfstack/packets.c  -o ${OBJECTDIR}/_ext/1201319415/packets.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1201319415/packets.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1201319415/packets.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1201319415/server.o: ../../src/rfstack/server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1201319415 
	@${RM} ${OBJECTDIR}/_ext/1201319415/server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1201319415/server.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/rfstack/server.c  -o ${OBJECTDIR}/_ext/1201319415/server.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1201319415/server.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1201319415/server.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1209926055/task.o: ../../src/server/rtos/task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209926055 
	@${RM} ${OBJECTDIR}/_ext/1209926055/task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209926055/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/rtos/task.c  -o ${OBJECTDIR}/_ext/1209926055/task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1209926055/task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209926055/task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1209926055/timer.o: ../../src/server/rtos/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209926055 
	@${RM} ${OBJECTDIR}/_ext/1209926055/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209926055/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/rtos/timer.c  -o ${OBJECTDIR}/_ext/1209926055/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1209926055/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209926055/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1145713235/rf_task.o: ../../src/server/tasks/rf_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1145713235 
	@${RM} ${OBJECTDIR}/_ext/1145713235/rf_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1145713235/rf_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/tasks/rf_task.c  -o ${OBJECTDIR}/_ext/1145713235/rf_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1145713235/rf_task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1145713235/rf_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1145713235/eth_task.o: ../../src/server/tasks/eth_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1145713235 
	@${RM} ${OBJECTDIR}/_ext/1145713235/eth_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1145713235/eth_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/tasks/eth_task.c  -o ${OBJECTDIR}/_ext/1145713235/eth_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1145713235/eth_task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1145713235/eth_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1709695401/executiontime.o: ../../src/server/utilities/executiontime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1709695401 
	@${RM} ${OBJECTDIR}/_ext/1709695401/executiontime.o.d 
	@${RM} ${OBJECTDIR}/_ext/1709695401/executiontime.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/utilities/executiontime.c  -o ${OBJECTDIR}/_ext/1709695401/executiontime.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1709695401/executiontime.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1709695401/executiontime.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1709695401/spiArbiter.o: ../../src/server/utilities/spiArbiter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1709695401 
	@${RM} ${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1709695401/spiArbiter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/utilities/spiArbiter.c  -o ${OBJECTDIR}/_ext/1709695401/spiArbiter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2125849857/ccbuf.o: ../../src/utilities/ccbuf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2125849857 
	@${RM} ${OBJECTDIR}/_ext/2125849857/ccbuf.o.d 
	@${RM} ${OBJECTDIR}/_ext/2125849857/ccbuf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/utilities/ccbuf.c  -o ${OBJECTDIR}/_ext/2125849857/ccbuf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2125849857/ccbuf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2125849857/ccbuf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/296506934/router.o: ../../src/server/webserver/router.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/296506934 
	@${RM} ${OBJECTDIR}/_ext/296506934/router.o.d 
	@${RM} ${OBJECTDIR}/_ext/296506934/router.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/webserver/router.c  -o ${OBJECTDIR}/_ext/296506934/router.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/296506934/router.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/296506934/router.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/681662318/main.o: ../../src/server/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681662318 
	@${RM} ${OBJECTDIR}/_ext/681662318/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/681662318/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/main.c  -o ${OBJECTDIR}/_ext/681662318/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/681662318/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/681662318/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/681662318/config.o: ../../src/server/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681662318 
	@${RM} ${OBJECTDIR}/_ext/681662318/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/681662318/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/config.c  -o ${OBJECTDIR}/_ext/681662318/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/681662318/config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/681662318/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/604762726/softI2c.o: ../../src/bsp/common/softI2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/604762726 
	@${RM} ${OBJECTDIR}/_ext/604762726/softI2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/604762726/softI2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/common/softI2c.c  -o ${OBJECTDIR}/_ext/604762726/softI2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/604762726/softI2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/604762726/softI2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/585513329/adc.o: ../../src/bsp/pic24/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/adc.c  -o ${OBJECTDIR}/_ext/585513329/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/adc.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/i2c.o: ../../src/bsp/pic24/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/i2c.c  -o ${OBJECTDIR}/_ext/585513329/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/i2c.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/interrupt.o: ../../src/bsp/pic24/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/interrupt.c  -o ${OBJECTDIR}/_ext/585513329/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/interrupt.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/interrupt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/rtc.o: ../../src/bsp/pic24/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/rtc.c  -o ${OBJECTDIR}/_ext/585513329/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/rtc.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/rtos.o: ../../src/bsp/pic24/rtos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtos.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/rtos.c  -o ${OBJECTDIR}/_ext/585513329/rtos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/rtos.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/rtos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/spi.o: ../../src/bsp/pic24/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/spi.c  -o ${OBJECTDIR}/_ext/585513329/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/spi.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/timer.o: ../../src/bsp/pic24/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/timer.c  -o ${OBJECTDIR}/_ext/585513329/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/timer.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/uart.o: ../../src/bsp/pic24/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/uart.c  -o ${OBJECTDIR}/_ext/585513329/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/uart.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/SST26VF032.o: ../../src/devices/SST26VF032.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/SST26VF032.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/SST26VF032.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/SST26VF032.c  -o ${OBJECTDIR}/_ext/767653358/SST26VF032.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/SST26VF032.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/SST26VF032.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/enc28j60.o: ../../src/devices/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/enc28j60.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/enc28j60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/enc28j60.c  -o ${OBJECTDIR}/_ext/767653358/enc28j60.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/enc28j60.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/enc28j60.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mcp9800.o: ../../src/devices/mcp9800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mcp9800.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mcp9800.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mcp9800.c  -o ${OBJECTDIR}/_ext/767653358/mcp9800.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mcp9800.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mcp9800.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa.o: ../../src/devices/mrf49xa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o: ../../src/devices/mrf49xa_cmd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_cmd.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o: ../../src/devices/mrf49xa_spi_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_spi_pic24.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_spi_pic24.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o: ../../src/devices/mrf49xa_mac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_mac.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_mac.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o: ../../src/devices/mrf49xa_phy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_phy.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_phy.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/arp.o: ../../src/server/ipstack/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/arp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/arp.c  -o ${OBJECTDIR}/_ext/2033261600/arp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/arp.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/arp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/icmp.o: ../../src/server/ipstack/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/icmp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/icmp.c  -o ${OBJECTDIR}/_ext/2033261600/icmp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/icmp.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/icmp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/ipv4.o: ../../src/server/ipstack/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/ipv4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/ipv4.c  -o ${OBJECTDIR}/_ext/2033261600/ipv4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/ipv4.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/ipv4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/ntp.o: ../../src/server/ipstack/ntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/ntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/ntp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/ntp.c  -o ${OBJECTDIR}/_ext/2033261600/ntp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/ntp.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/ntp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/tcp.o: ../../src/server/ipstack/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/tcp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/tcp.c  -o ${OBJECTDIR}/_ext/2033261600/tcp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/tcp.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/tcp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2033261600/udp.o: ../../src/server/ipstack/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2033261600 
	@${RM} ${OBJECTDIR}/_ext/2033261600/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2033261600/udp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/ipstack/udp.c  -o ${OBJECTDIR}/_ext/2033261600/udp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2033261600/udp.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2033261600/udp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1201319415/packets.o: ../../src/rfstack/packets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1201319415 
	@${RM} ${OBJECTDIR}/_ext/1201319415/packets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1201319415/packets.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/rfstack/packets.c  -o ${OBJECTDIR}/_ext/1201319415/packets.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1201319415/packets.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1201319415/packets.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1201319415/server.o: ../../src/rfstack/server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1201319415 
	@${RM} ${OBJECTDIR}/_ext/1201319415/server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1201319415/server.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/rfstack/server.c  -o ${OBJECTDIR}/_ext/1201319415/server.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1201319415/server.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1201319415/server.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1209926055/task.o: ../../src/server/rtos/task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209926055 
	@${RM} ${OBJECTDIR}/_ext/1209926055/task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209926055/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/rtos/task.c  -o ${OBJECTDIR}/_ext/1209926055/task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1209926055/task.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209926055/task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1209926055/timer.o: ../../src/server/rtos/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209926055 
	@${RM} ${OBJECTDIR}/_ext/1209926055/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209926055/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/rtos/timer.c  -o ${OBJECTDIR}/_ext/1209926055/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1209926055/timer.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209926055/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1145713235/rf_task.o: ../../src/server/tasks/rf_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1145713235 
	@${RM} ${OBJECTDIR}/_ext/1145713235/rf_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1145713235/rf_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/tasks/rf_task.c  -o ${OBJECTDIR}/_ext/1145713235/rf_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1145713235/rf_task.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1145713235/rf_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1145713235/eth_task.o: ../../src/server/tasks/eth_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1145713235 
	@${RM} ${OBJECTDIR}/_ext/1145713235/eth_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1145713235/eth_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/tasks/eth_task.c  -o ${OBJECTDIR}/_ext/1145713235/eth_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1145713235/eth_task.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1145713235/eth_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1709695401/executiontime.o: ../../src/server/utilities/executiontime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1709695401 
	@${RM} ${OBJECTDIR}/_ext/1709695401/executiontime.o.d 
	@${RM} ${OBJECTDIR}/_ext/1709695401/executiontime.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/utilities/executiontime.c  -o ${OBJECTDIR}/_ext/1709695401/executiontime.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1709695401/executiontime.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1709695401/executiontime.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1709695401/spiArbiter.o: ../../src/server/utilities/spiArbiter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1709695401 
	@${RM} ${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1709695401/spiArbiter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/utilities/spiArbiter.c  -o ${OBJECTDIR}/_ext/1709695401/spiArbiter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2125849857/ccbuf.o: ../../src/utilities/ccbuf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2125849857 
	@${RM} ${OBJECTDIR}/_ext/2125849857/ccbuf.o.d 
	@${RM} ${OBJECTDIR}/_ext/2125849857/ccbuf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/utilities/ccbuf.c  -o ${OBJECTDIR}/_ext/2125849857/ccbuf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2125849857/ccbuf.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2125849857/ccbuf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/296506934/router.o: ../../src/server/webserver/router.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/296506934 
	@${RM} ${OBJECTDIR}/_ext/296506934/router.o.d 
	@${RM} ${OBJECTDIR}/_ext/296506934/router.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/webserver/router.c  -o ${OBJECTDIR}/_ext/296506934/router.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/296506934/router.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/296506934/router.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/681662318/main.o: ../../src/server/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681662318 
	@${RM} ${OBJECTDIR}/_ext/681662318/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/681662318/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/main.c  -o ${OBJECTDIR}/_ext/681662318/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/681662318/main.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/681662318/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/681662318/config.o: ../../src/server/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681662318 
	@${RM} ${OBJECTDIR}/_ext/681662318/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/681662318/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/config.c  -o ${OBJECTDIR}/_ext/681662318/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/681662318/config.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/681662318/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/604762726/softI2c.o: ../../src/bsp/common/softI2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/604762726 
	@${RM} ${OBJECTDIR}/_ext/604762726/softI2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/604762726/softI2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/common/softI2c.c  -o ${OBJECTDIR}/_ext/604762726/softI2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/604762726/softI2c.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -I"../../inc/bsp/pic24" -DBUILD_TARGET=0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/604762726/softI2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/585513329/context.o: ../../src/bsp/pic24/context.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/context.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/context.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../src/bsp/pic24/context.s  -o ${OBJECTDIR}/_ext/585513329/context.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/_ext/585513329/context.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-ai$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/context.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/585513329/context.o: ../../src/bsp/pic24/context.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/context.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/context.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../src/bsp/pic24/context.s  -o ${OBJECTDIR}/_ext/585513329/context.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/_ext/585513329/context.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-ai$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/context.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24b.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24b.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24b.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24b.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic24b.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
