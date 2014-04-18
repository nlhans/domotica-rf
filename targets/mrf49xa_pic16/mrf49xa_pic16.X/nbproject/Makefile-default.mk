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
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../src/bsp/softI2c.c ../../../src/bsp/pic16/adc16.c ../../../src/bsp/pic16/interrupt.c ../../../src/devices/mcp9800.c ../../../src/devices/mrf49xa.c ../../../src/devices/mrf49xa_spi_pic16.c ../../../src/devices/mrf49xa_cmd.c ../../../src/devices/mrf49xa_packet.c ../../../src/rfstack/hal.c ../../../src/rfstack/packets.c ../../../src/node/main.c ../../../src/devices/mrf49xa_data.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/534562843/softI2c.p1 ${OBJECTDIR}/_ext/421542533/adc16.p1 ${OBJECTDIR}/_ext/421542533/interrupt.p1 ${OBJECTDIR}/_ext/2092508035/mcp9800.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1 ${OBJECTDIR}/_ext/1658841978/hal.p1 ${OBJECTDIR}/_ext/1658841978/packets.p1 ${OBJECTDIR}/_ext/608774428/main.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/534562843/softI2c.p1.d ${OBJECTDIR}/_ext/421542533/adc16.p1.d ${OBJECTDIR}/_ext/421542533/interrupt.p1.d ${OBJECTDIR}/_ext/2092508035/mcp9800.p1.d ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1.d ${OBJECTDIR}/_ext/1658841978/hal.p1.d ${OBJECTDIR}/_ext/1658841978/packets.p1.d ${OBJECTDIR}/_ext/608774428/main.p1.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/534562843/softI2c.p1 ${OBJECTDIR}/_ext/421542533/adc16.p1 ${OBJECTDIR}/_ext/421542533/interrupt.p1 ${OBJECTDIR}/_ext/2092508035/mcp9800.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1 ${OBJECTDIR}/_ext/1658841978/hal.p1 ${OBJECTDIR}/_ext/1658841978/packets.p1 ${OBJECTDIR}/_ext/608774428/main.p1 ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1

# Source Files
SOURCEFILES=../../../src/bsp/softI2c.c ../../../src/bsp/pic16/adc16.c ../../../src/bsp/pic16/interrupt.c ../../../src/devices/mcp9800.c ../../../src/devices/mrf49xa.c ../../../src/devices/mrf49xa_spi_pic16.c ../../../src/devices/mrf49xa_cmd.c ../../../src/devices/mrf49xa_packet.c ../../../src/rfstack/hal.c ../../../src/rfstack/packets.c ../../../src/node/main.c ../../../src/devices/mrf49xa_data.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16LF1508
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/534562843/softI2c.p1: ../../../src/bsp/softI2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/534562843 
	@${RM} ${OBJECTDIR}/_ext/534562843/softI2c.p1.d 
	@${RM} ${OBJECTDIR}/_ext/534562843/softI2c.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/534562843/softI2c.p1  ../../../src/bsp/softI2c.c 
	@-${MV} ${OBJECTDIR}/_ext/534562843/softI2c.d ${OBJECTDIR}/_ext/534562843/softI2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/534562843/softI2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/421542533/adc16.p1: ../../../src/bsp/pic16/adc16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/421542533 
	@${RM} ${OBJECTDIR}/_ext/421542533/adc16.p1.d 
	@${RM} ${OBJECTDIR}/_ext/421542533/adc16.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/421542533/adc16.p1  ../../../src/bsp/pic16/adc16.c 
	@-${MV} ${OBJECTDIR}/_ext/421542533/adc16.d ${OBJECTDIR}/_ext/421542533/adc16.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/421542533/adc16.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/421542533/interrupt.p1: ../../../src/bsp/pic16/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/421542533 
	@${RM} ${OBJECTDIR}/_ext/421542533/interrupt.p1.d 
	@${RM} ${OBJECTDIR}/_ext/421542533/interrupt.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/421542533/interrupt.p1  ../../../src/bsp/pic16/interrupt.c 
	@-${MV} ${OBJECTDIR}/_ext/421542533/interrupt.d ${OBJECTDIR}/_ext/421542533/interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/421542533/interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mcp9800.p1: ../../../src/devices/mcp9800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mcp9800.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mcp9800.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mcp9800.p1  ../../../src/devices/mcp9800.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mcp9800.d ${OBJECTDIR}/_ext/2092508035/mcp9800.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mcp9800.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa.p1: ../../../src/devices/mrf49xa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa.p1  ../../../src/devices/mrf49xa.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa.d ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1: ../../../src/devices/mrf49xa_spi_pic16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1  ../../../src/devices/mrf49xa_spi_pic16.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1: ../../../src/devices/mrf49xa_cmd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1  ../../../src/devices/mrf49xa_cmd.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1: ../../../src/devices/mrf49xa_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1  ../../../src/devices/mrf49xa_packet.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1658841978/hal.p1: ../../../src/rfstack/hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1658841978 
	@${RM} ${OBJECTDIR}/_ext/1658841978/hal.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1658841978/hal.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1658841978/hal.p1  ../../../src/rfstack/hal.c 
	@-${MV} ${OBJECTDIR}/_ext/1658841978/hal.d ${OBJECTDIR}/_ext/1658841978/hal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1658841978/hal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1658841978/packets.p1: ../../../src/rfstack/packets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1658841978 
	@${RM} ${OBJECTDIR}/_ext/1658841978/packets.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1658841978/packets.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1658841978/packets.p1  ../../../src/rfstack/packets.c 
	@-${MV} ${OBJECTDIR}/_ext/1658841978/packets.d ${OBJECTDIR}/_ext/1658841978/packets.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1658841978/packets.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/608774428/main.p1: ../../../src/node/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/608774428 
	@${RM} ${OBJECTDIR}/_ext/608774428/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/608774428/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/608774428/main.p1  ../../../src/node/main.c 
	@-${MV} ${OBJECTDIR}/_ext/608774428/main.d ${OBJECTDIR}/_ext/608774428/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/608774428/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1: ../../../src/devices/mrf49xa_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1  ../../../src/devices/mrf49xa_data.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/534562843/softI2c.p1: ../../../src/bsp/softI2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/534562843 
	@${RM} ${OBJECTDIR}/_ext/534562843/softI2c.p1.d 
	@${RM} ${OBJECTDIR}/_ext/534562843/softI2c.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/534562843/softI2c.p1  ../../../src/bsp/softI2c.c 
	@-${MV} ${OBJECTDIR}/_ext/534562843/softI2c.d ${OBJECTDIR}/_ext/534562843/softI2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/534562843/softI2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/421542533/adc16.p1: ../../../src/bsp/pic16/adc16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/421542533 
	@${RM} ${OBJECTDIR}/_ext/421542533/adc16.p1.d 
	@${RM} ${OBJECTDIR}/_ext/421542533/adc16.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/421542533/adc16.p1  ../../../src/bsp/pic16/adc16.c 
	@-${MV} ${OBJECTDIR}/_ext/421542533/adc16.d ${OBJECTDIR}/_ext/421542533/adc16.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/421542533/adc16.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/421542533/interrupt.p1: ../../../src/bsp/pic16/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/421542533 
	@${RM} ${OBJECTDIR}/_ext/421542533/interrupt.p1.d 
	@${RM} ${OBJECTDIR}/_ext/421542533/interrupt.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/421542533/interrupt.p1  ../../../src/bsp/pic16/interrupt.c 
	@-${MV} ${OBJECTDIR}/_ext/421542533/interrupt.d ${OBJECTDIR}/_ext/421542533/interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/421542533/interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mcp9800.p1: ../../../src/devices/mcp9800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mcp9800.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mcp9800.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mcp9800.p1  ../../../src/devices/mcp9800.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mcp9800.d ${OBJECTDIR}/_ext/2092508035/mcp9800.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mcp9800.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa.p1: ../../../src/devices/mrf49xa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa.p1  ../../../src/devices/mrf49xa.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa.d ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1: ../../../src/devices/mrf49xa_spi_pic16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1  ../../../src/devices/mrf49xa_spi_pic16.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa_spi_pic16.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1: ../../../src/devices/mrf49xa_cmd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1  ../../../src/devices/mrf49xa_cmd.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa_cmd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1: ../../../src/devices/mrf49xa_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1  ../../../src/devices/mrf49xa_packet.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa_packet.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1658841978/hal.p1: ../../../src/rfstack/hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1658841978 
	@${RM} ${OBJECTDIR}/_ext/1658841978/hal.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1658841978/hal.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1658841978/hal.p1  ../../../src/rfstack/hal.c 
	@-${MV} ${OBJECTDIR}/_ext/1658841978/hal.d ${OBJECTDIR}/_ext/1658841978/hal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1658841978/hal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1658841978/packets.p1: ../../../src/rfstack/packets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1658841978 
	@${RM} ${OBJECTDIR}/_ext/1658841978/packets.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1658841978/packets.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1658841978/packets.p1  ../../../src/rfstack/packets.c 
	@-${MV} ${OBJECTDIR}/_ext/1658841978/packets.d ${OBJECTDIR}/_ext/1658841978/packets.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1658841978/packets.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/608774428/main.p1: ../../../src/node/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/608774428 
	@${RM} ${OBJECTDIR}/_ext/608774428/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/608774428/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/608774428/main.p1  ../../../src/node/main.c 
	@-${MV} ${OBJECTDIR}/_ext/608774428/main.d ${OBJECTDIR}/_ext/608774428/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/608774428/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1: ../../../src/devices/mrf49xa_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092508035 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1  ../../../src/devices/mrf49xa_data.c 
	@-${MV} ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.d ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2092508035/mrf49xa_data.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"      --ram=default,-160-16f  -odist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.map  --double=24 --float=24 --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N255 -I"../../../inc" --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -odist/${CND_CONF}/${IMAGE_TYPE}/mrf49xa_pic16.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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
