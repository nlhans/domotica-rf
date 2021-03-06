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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_dbg.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_dbg.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../src/bsp/pic24/context.s ../../src/bsp/pic24/adc.c ../../src/bsp/pic24/i2c.c ../../src/bsp/pic24/interrupt.c ../../src/bsp/pic24/rtc.c ../../src/bsp/pic24/rtos.c ../../src/bsp/pic24/spi.c ../../src/bsp/pic24/timer.c ../../src/bsp/pic24/uart.c ../../src/bsp/pic24/dma.c ../../src/devices/mrf49xa.c ../../src/devices/mrf49xa_cmd.c ../../src/devices/mrf49xa_data.c ../../src/devices/mrf49xa_packet.c ../../src/devices/mrf49xa_spi_dspic33.c ../../src/rfstack/debugger.c ../../src/server/rtos/task.c ../../src/server/rtos/timer.c ../../src/server/tasks/rf_task.c ../../src/dbg/dbg_task.c ../../src/utilities/ccbuf.c ../../src/server/utilities/spiArbiter.c ../../src/dbg/main.c ../../src/dbg/config.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/585513329/context.o ${OBJECTDIR}/_ext/585513329/adc.o ${OBJECTDIR}/_ext/585513329/i2c.o ${OBJECTDIR}/_ext/585513329/interrupt.o ${OBJECTDIR}/_ext/585513329/rtc.o ${OBJECTDIR}/_ext/585513329/rtos.o ${OBJECTDIR}/_ext/585513329/spi.o ${OBJECTDIR}/_ext/585513329/timer.o ${OBJECTDIR}/_ext/585513329/uart.o ${OBJECTDIR}/_ext/585513329/dma.o ${OBJECTDIR}/_ext/767653358/mrf49xa.o ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o ${OBJECTDIR}/_ext/767653358/mrf49xa_data.o ${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o ${OBJECTDIR}/_ext/1201319415/debugger.o ${OBJECTDIR}/_ext/1209926055/task.o ${OBJECTDIR}/_ext/1209926055/timer.o ${OBJECTDIR}/_ext/1145713235/rf_task.o ${OBJECTDIR}/_ext/1161280674/dbg_task.o ${OBJECTDIR}/_ext/2125849857/ccbuf.o ${OBJECTDIR}/_ext/1709695401/spiArbiter.o ${OBJECTDIR}/_ext/1161280674/main.o ${OBJECTDIR}/_ext/1161280674/config.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/585513329/context.o.d ${OBJECTDIR}/_ext/585513329/adc.o.d ${OBJECTDIR}/_ext/585513329/i2c.o.d ${OBJECTDIR}/_ext/585513329/interrupt.o.d ${OBJECTDIR}/_ext/585513329/rtc.o.d ${OBJECTDIR}/_ext/585513329/rtos.o.d ${OBJECTDIR}/_ext/585513329/spi.o.d ${OBJECTDIR}/_ext/585513329/timer.o.d ${OBJECTDIR}/_ext/585513329/uart.o.d ${OBJECTDIR}/_ext/585513329/dma.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa_data.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o.d ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o.d ${OBJECTDIR}/_ext/1201319415/debugger.o.d ${OBJECTDIR}/_ext/1209926055/task.o.d ${OBJECTDIR}/_ext/1209926055/timer.o.d ${OBJECTDIR}/_ext/1145713235/rf_task.o.d ${OBJECTDIR}/_ext/1161280674/dbg_task.o.d ${OBJECTDIR}/_ext/2125849857/ccbuf.o.d ${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d ${OBJECTDIR}/_ext/1161280674/main.o.d ${OBJECTDIR}/_ext/1161280674/config.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/585513329/context.o ${OBJECTDIR}/_ext/585513329/adc.o ${OBJECTDIR}/_ext/585513329/i2c.o ${OBJECTDIR}/_ext/585513329/interrupt.o ${OBJECTDIR}/_ext/585513329/rtc.o ${OBJECTDIR}/_ext/585513329/rtos.o ${OBJECTDIR}/_ext/585513329/spi.o ${OBJECTDIR}/_ext/585513329/timer.o ${OBJECTDIR}/_ext/585513329/uart.o ${OBJECTDIR}/_ext/585513329/dma.o ${OBJECTDIR}/_ext/767653358/mrf49xa.o ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o ${OBJECTDIR}/_ext/767653358/mrf49xa_data.o ${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o ${OBJECTDIR}/_ext/1201319415/debugger.o ${OBJECTDIR}/_ext/1209926055/task.o ${OBJECTDIR}/_ext/1209926055/timer.o ${OBJECTDIR}/_ext/1145713235/rf_task.o ${OBJECTDIR}/_ext/1161280674/dbg_task.o ${OBJECTDIR}/_ext/2125849857/ccbuf.o ${OBJECTDIR}/_ext/1709695401/spiArbiter.o ${OBJECTDIR}/_ext/1161280674/main.o ${OBJECTDIR}/_ext/1161280674/config.o

# Source Files
SOURCEFILES=../../src/bsp/pic24/context.s ../../src/bsp/pic24/adc.c ../../src/bsp/pic24/i2c.c ../../src/bsp/pic24/interrupt.c ../../src/bsp/pic24/rtc.c ../../src/bsp/pic24/rtos.c ../../src/bsp/pic24/spi.c ../../src/bsp/pic24/timer.c ../../src/bsp/pic24/uart.c ../../src/bsp/pic24/dma.c ../../src/devices/mrf49xa.c ../../src/devices/mrf49xa_cmd.c ../../src/devices/mrf49xa_data.c ../../src/devices/mrf49xa_packet.c ../../src/devices/mrf49xa_spi_dspic33.c ../../src/rfstack/debugger.c ../../src/server/rtos/task.c ../../src/server/rtos/timer.c ../../src/server/tasks/rf_task.c ../../src/dbg/dbg_task.c ../../src/utilities/ccbuf.c ../../src/server/utilities/spiArbiter.c ../../src/dbg/main.c ../../src/dbg/config.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_dbg.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP804
MP_LINKER_FILE_OPTION=,--script=p33FJ128GP804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/585513329/adc.o: ../../src/bsp/pic24/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/adc.c  -o ${OBJECTDIR}/_ext/585513329/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/i2c.o: ../../src/bsp/pic24/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/i2c.c  -o ${OBJECTDIR}/_ext/585513329/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/i2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/interrupt.o: ../../src/bsp/pic24/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/interrupt.c  -o ${OBJECTDIR}/_ext/585513329/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/interrupt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/interrupt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/rtc.o: ../../src/bsp/pic24/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/rtc.c  -o ${OBJECTDIR}/_ext/585513329/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/rtc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/rtos.o: ../../src/bsp/pic24/rtos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtos.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/rtos.c  -o ${OBJECTDIR}/_ext/585513329/rtos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/rtos.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/rtos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/spi.o: ../../src/bsp/pic24/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/spi.c  -o ${OBJECTDIR}/_ext/585513329/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/spi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/timer.o: ../../src/bsp/pic24/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/timer.c  -o ${OBJECTDIR}/_ext/585513329/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/uart.o: ../../src/bsp/pic24/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/uart.c  -o ${OBJECTDIR}/_ext/585513329/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/dma.o: ../../src/bsp/pic24/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/dma.c  -o ${OBJECTDIR}/_ext/585513329/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/dma.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa.o: ../../src/devices/mrf49xa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o: ../../src/devices/mrf49xa_cmd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_cmd.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_data.o: ../../src/devices/mrf49xa_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_data.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_data.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_data.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_data.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_data.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o: ../../src/devices/mrf49xa_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_packet.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o: ../../src/devices/mrf49xa_spi_dspic33.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_spi_dspic33.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1201319415/debugger.o: ../../src/rfstack/debugger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1201319415 
	@${RM} ${OBJECTDIR}/_ext/1201319415/debugger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1201319415/debugger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/rfstack/debugger.c  -o ${OBJECTDIR}/_ext/1201319415/debugger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1201319415/debugger.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1201319415/debugger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1209926055/task.o: ../../src/server/rtos/task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209926055 
	@${RM} ${OBJECTDIR}/_ext/1209926055/task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209926055/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/rtos/task.c  -o ${OBJECTDIR}/_ext/1209926055/task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1209926055/task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209926055/task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1209926055/timer.o: ../../src/server/rtos/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209926055 
	@${RM} ${OBJECTDIR}/_ext/1209926055/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209926055/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/rtos/timer.c  -o ${OBJECTDIR}/_ext/1209926055/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1209926055/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209926055/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1145713235/rf_task.o: ../../src/server/tasks/rf_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1145713235 
	@${RM} ${OBJECTDIR}/_ext/1145713235/rf_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1145713235/rf_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/tasks/rf_task.c  -o ${OBJECTDIR}/_ext/1145713235/rf_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1145713235/rf_task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1145713235/rf_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1161280674/dbg_task.o: ../../src/dbg/dbg_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1161280674 
	@${RM} ${OBJECTDIR}/_ext/1161280674/dbg_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1161280674/dbg_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/dbg/dbg_task.c  -o ${OBJECTDIR}/_ext/1161280674/dbg_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1161280674/dbg_task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1161280674/dbg_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2125849857/ccbuf.o: ../../src/utilities/ccbuf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2125849857 
	@${RM} ${OBJECTDIR}/_ext/2125849857/ccbuf.o.d 
	@${RM} ${OBJECTDIR}/_ext/2125849857/ccbuf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/utilities/ccbuf.c  -o ${OBJECTDIR}/_ext/2125849857/ccbuf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2125849857/ccbuf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2125849857/ccbuf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1709695401/spiArbiter.o: ../../src/server/utilities/spiArbiter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1709695401 
	@${RM} ${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1709695401/spiArbiter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/utilities/spiArbiter.c  -o ${OBJECTDIR}/_ext/1709695401/spiArbiter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1161280674/main.o: ../../src/dbg/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1161280674 
	@${RM} ${OBJECTDIR}/_ext/1161280674/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1161280674/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/dbg/main.c  -o ${OBJECTDIR}/_ext/1161280674/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1161280674/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1161280674/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1161280674/config.o: ../../src/dbg/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1161280674 
	@${RM} ${OBJECTDIR}/_ext/1161280674/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1161280674/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/dbg/config.c  -o ${OBJECTDIR}/_ext/1161280674/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1161280674/config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1161280674/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/585513329/adc.o: ../../src/bsp/pic24/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/adc.c  -o ${OBJECTDIR}/_ext/585513329/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/adc.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/i2c.o: ../../src/bsp/pic24/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/i2c.c  -o ${OBJECTDIR}/_ext/585513329/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/i2c.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/interrupt.o: ../../src/bsp/pic24/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/interrupt.c  -o ${OBJECTDIR}/_ext/585513329/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/interrupt.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/interrupt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/rtc.o: ../../src/bsp/pic24/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/rtc.c  -o ${OBJECTDIR}/_ext/585513329/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/rtc.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/rtos.o: ../../src/bsp/pic24/rtos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtos.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/rtos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/rtos.c  -o ${OBJECTDIR}/_ext/585513329/rtos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/rtos.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/rtos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/spi.o: ../../src/bsp/pic24/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/spi.c  -o ${OBJECTDIR}/_ext/585513329/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/spi.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/timer.o: ../../src/bsp/pic24/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/timer.c  -o ${OBJECTDIR}/_ext/585513329/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/timer.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/uart.o: ../../src/bsp/pic24/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/uart.c  -o ${OBJECTDIR}/_ext/585513329/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/uart.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/585513329/dma.o: ../../src/bsp/pic24/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/bsp/pic24/dma.c  -o ${OBJECTDIR}/_ext/585513329/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/585513329/dma.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa.o: ../../src/devices/mrf49xa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o: ../../src/devices/mrf49xa_cmd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_cmd.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_cmd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_data.o: ../../src/devices/mrf49xa_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_data.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_data.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_data.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_data.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_data.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o: ../../src/devices/mrf49xa_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_packet.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_packet.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o: ../../src/devices/mrf49xa_spi_dspic33.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/767653358 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o.d 
	@${RM} ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/devices/mrf49xa_spi_dspic33.c  -o ${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/767653358/mrf49xa_spi_dspic33.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1201319415/debugger.o: ../../src/rfstack/debugger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1201319415 
	@${RM} ${OBJECTDIR}/_ext/1201319415/debugger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1201319415/debugger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/rfstack/debugger.c  -o ${OBJECTDIR}/_ext/1201319415/debugger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1201319415/debugger.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1201319415/debugger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1209926055/task.o: ../../src/server/rtos/task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209926055 
	@${RM} ${OBJECTDIR}/_ext/1209926055/task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209926055/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/rtos/task.c  -o ${OBJECTDIR}/_ext/1209926055/task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1209926055/task.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209926055/task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1209926055/timer.o: ../../src/server/rtos/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209926055 
	@${RM} ${OBJECTDIR}/_ext/1209926055/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209926055/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/rtos/timer.c  -o ${OBJECTDIR}/_ext/1209926055/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1209926055/timer.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209926055/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1145713235/rf_task.o: ../../src/server/tasks/rf_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1145713235 
	@${RM} ${OBJECTDIR}/_ext/1145713235/rf_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1145713235/rf_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/tasks/rf_task.c  -o ${OBJECTDIR}/_ext/1145713235/rf_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1145713235/rf_task.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1145713235/rf_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1161280674/dbg_task.o: ../../src/dbg/dbg_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1161280674 
	@${RM} ${OBJECTDIR}/_ext/1161280674/dbg_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1161280674/dbg_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/dbg/dbg_task.c  -o ${OBJECTDIR}/_ext/1161280674/dbg_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1161280674/dbg_task.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1161280674/dbg_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2125849857/ccbuf.o: ../../src/utilities/ccbuf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2125849857 
	@${RM} ${OBJECTDIR}/_ext/2125849857/ccbuf.o.d 
	@${RM} ${OBJECTDIR}/_ext/2125849857/ccbuf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/utilities/ccbuf.c  -o ${OBJECTDIR}/_ext/2125849857/ccbuf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2125849857/ccbuf.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2125849857/ccbuf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1709695401/spiArbiter.o: ../../src/server/utilities/spiArbiter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1709695401 
	@${RM} ${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1709695401/spiArbiter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/server/utilities/spiArbiter.c  -o ${OBJECTDIR}/_ext/1709695401/spiArbiter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1709695401/spiArbiter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1161280674/main.o: ../../src/dbg/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1161280674 
	@${RM} ${OBJECTDIR}/_ext/1161280674/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1161280674/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/dbg/main.c  -o ${OBJECTDIR}/_ext/1161280674/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1161280674/main.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1161280674/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1161280674/config.o: ../../src/dbg/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1161280674 
	@${RM} ${OBJECTDIR}/_ext/1161280674/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1161280674/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../src/dbg/config.c  -o ${OBJECTDIR}/_ext/1161280674/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1161280674/config.o.d"        -g -omf=elf -Os -I"../../inc" -I"../../inc/server" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1161280674/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/585513329/context.o: ../../src/bsp/pic24/context.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/context.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/context.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../src/bsp/pic24/context.s  -o ${OBJECTDIR}/_ext/585513329/context.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/_ext/585513329/context.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/585513329/context.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/585513329/context.o: ../../src/bsp/pic24/context.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/585513329 
	@${RM} ${OBJECTDIR}/_ext/585513329/context.o.d 
	@${RM} ${OBJECTDIR}/_ext/585513329/context.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../src/bsp/pic24/context.s  -o ${OBJECTDIR}/_ext/585513329/context.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/_ext/585513329/context.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
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
dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_dbg.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_dbg.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_dbg.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_dbg.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_dbg.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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
