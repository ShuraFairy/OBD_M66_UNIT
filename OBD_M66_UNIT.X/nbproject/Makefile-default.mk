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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OBD_M66_UNIT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OBD_M66_UNIT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=OBD_M66_UNIT.c ECAN1Config.c ECAN1Drv.c ECAN2Config.c ECAN2Drv.c ERA/Src/ERA.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/OBD_M66_UNIT.o ${OBJECTDIR}/ECAN1Config.o ${OBJECTDIR}/ECAN1Drv.o ${OBJECTDIR}/ECAN2Config.o ${OBJECTDIR}/ECAN2Drv.o ${OBJECTDIR}/ERA/Src/ERA.o
POSSIBLE_DEPFILES=${OBJECTDIR}/OBD_M66_UNIT.o.d ${OBJECTDIR}/ECAN1Config.o.d ${OBJECTDIR}/ECAN1Drv.o.d ${OBJECTDIR}/ECAN2Config.o.d ${OBJECTDIR}/ECAN2Drv.o.d ${OBJECTDIR}/ERA/Src/ERA.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/OBD_M66_UNIT.o ${OBJECTDIR}/ECAN1Config.o ${OBJECTDIR}/ECAN1Drv.o ${OBJECTDIR}/ECAN2Config.o ${OBJECTDIR}/ECAN2Drv.o ${OBJECTDIR}/ERA/Src/ERA.o

# Source Files
SOURCEFILES=OBD_M66_UNIT.c ECAN1Config.c ECAN1Drv.c ECAN2Config.c ECAN2Drv.c ERA/Src/ERA.c


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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/OBD_M66_UNIT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MU806
MP_LINKER_FILE_OPTION=,-Tp33EP256MU806.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/OBD_M66_UNIT.o: OBD_M66_UNIT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OBD_M66_UNIT.o.d 
	@${RM} ${OBJECTDIR}/OBD_M66_UNIT.o.ok ${OBJECTDIR}/OBD_M66_UNIT.o.err 
	@${RM} ${OBJECTDIR}/OBD_M66_UNIT.o 
	@${FIXDEPS} "${OBJECTDIR}/OBD_M66_UNIT.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/OBD_M66_UNIT.o.d" -o ${OBJECTDIR}/OBD_M66_UNIT.o OBD_M66_UNIT.c    
	
${OBJECTDIR}/ECAN1Config.o: ECAN1Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ECAN1Config.o.d 
	@${RM} ${OBJECTDIR}/ECAN1Config.o.ok ${OBJECTDIR}/ECAN1Config.o.err 
	@${RM} ${OBJECTDIR}/ECAN1Config.o 
	@${FIXDEPS} "${OBJECTDIR}/ECAN1Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ECAN1Config.o.d" -o ${OBJECTDIR}/ECAN1Config.o ECAN1Config.c    
	
${OBJECTDIR}/ECAN1Drv.o: ECAN1Drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ECAN1Drv.o.d 
	@${RM} ${OBJECTDIR}/ECAN1Drv.o.ok ${OBJECTDIR}/ECAN1Drv.o.err 
	@${RM} ${OBJECTDIR}/ECAN1Drv.o 
	@${FIXDEPS} "${OBJECTDIR}/ECAN1Drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ECAN1Drv.o.d" -o ${OBJECTDIR}/ECAN1Drv.o ECAN1Drv.c    
	
${OBJECTDIR}/ECAN2Config.o: ECAN2Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ECAN2Config.o.d 
	@${RM} ${OBJECTDIR}/ECAN2Config.o.ok ${OBJECTDIR}/ECAN2Config.o.err 
	@${RM} ${OBJECTDIR}/ECAN2Config.o 
	@${FIXDEPS} "${OBJECTDIR}/ECAN2Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ECAN2Config.o.d" -o ${OBJECTDIR}/ECAN2Config.o ECAN2Config.c    
	
${OBJECTDIR}/ECAN2Drv.o: ECAN2Drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ECAN2Drv.o.d 
	@${RM} ${OBJECTDIR}/ECAN2Drv.o.ok ${OBJECTDIR}/ECAN2Drv.o.err 
	@${RM} ${OBJECTDIR}/ECAN2Drv.o 
	@${FIXDEPS} "${OBJECTDIR}/ECAN2Drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ECAN2Drv.o.d" -o ${OBJECTDIR}/ECAN2Drv.o ECAN2Drv.c    
	
${OBJECTDIR}/ERA/Src/ERA.o: ERA/Src/ERA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ERA/Src" 
	@${RM} ${OBJECTDIR}/ERA/Src/ERA.o.d 
	@${RM} ${OBJECTDIR}/ERA/Src/ERA.o.ok ${OBJECTDIR}/ERA/Src/ERA.o.err 
	@${RM} ${OBJECTDIR}/ERA/Src/ERA.o 
	@${FIXDEPS} "${OBJECTDIR}/ERA/Src/ERA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ERA/Src/ERA.o.d" -o ${OBJECTDIR}/ERA/Src/ERA.o ERA/Src/ERA.c    
	
else
${OBJECTDIR}/OBD_M66_UNIT.o: OBD_M66_UNIT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OBD_M66_UNIT.o.d 
	@${RM} ${OBJECTDIR}/OBD_M66_UNIT.o.ok ${OBJECTDIR}/OBD_M66_UNIT.o.err 
	@${RM} ${OBJECTDIR}/OBD_M66_UNIT.o 
	@${FIXDEPS} "${OBJECTDIR}/OBD_M66_UNIT.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/OBD_M66_UNIT.o.d" -o ${OBJECTDIR}/OBD_M66_UNIT.o OBD_M66_UNIT.c    
	
${OBJECTDIR}/ECAN1Config.o: ECAN1Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ECAN1Config.o.d 
	@${RM} ${OBJECTDIR}/ECAN1Config.o.ok ${OBJECTDIR}/ECAN1Config.o.err 
	@${RM} ${OBJECTDIR}/ECAN1Config.o 
	@${FIXDEPS} "${OBJECTDIR}/ECAN1Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ECAN1Config.o.d" -o ${OBJECTDIR}/ECAN1Config.o ECAN1Config.c    
	
${OBJECTDIR}/ECAN1Drv.o: ECAN1Drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ECAN1Drv.o.d 
	@${RM} ${OBJECTDIR}/ECAN1Drv.o.ok ${OBJECTDIR}/ECAN1Drv.o.err 
	@${RM} ${OBJECTDIR}/ECAN1Drv.o 
	@${FIXDEPS} "${OBJECTDIR}/ECAN1Drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ECAN1Drv.o.d" -o ${OBJECTDIR}/ECAN1Drv.o ECAN1Drv.c    
	
${OBJECTDIR}/ECAN2Config.o: ECAN2Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ECAN2Config.o.d 
	@${RM} ${OBJECTDIR}/ECAN2Config.o.ok ${OBJECTDIR}/ECAN2Config.o.err 
	@${RM} ${OBJECTDIR}/ECAN2Config.o 
	@${FIXDEPS} "${OBJECTDIR}/ECAN2Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ECAN2Config.o.d" -o ${OBJECTDIR}/ECAN2Config.o ECAN2Config.c    
	
${OBJECTDIR}/ECAN2Drv.o: ECAN2Drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ECAN2Drv.o.d 
	@${RM} ${OBJECTDIR}/ECAN2Drv.o.ok ${OBJECTDIR}/ECAN2Drv.o.err 
	@${RM} ${OBJECTDIR}/ECAN2Drv.o 
	@${FIXDEPS} "${OBJECTDIR}/ECAN2Drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ECAN2Drv.o.d" -o ${OBJECTDIR}/ECAN2Drv.o ECAN2Drv.c    
	
${OBJECTDIR}/ERA/Src/ERA.o: ERA/Src/ERA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ERA/Src" 
	@${RM} ${OBJECTDIR}/ERA/Src/ERA.o.d 
	@${RM} ${OBJECTDIR}/ERA/Src/ERA.o.ok ${OBJECTDIR}/ERA/Src/ERA.o.err 
	@${RM} ${OBJECTDIR}/ERA/Src/ERA.o 
	@${FIXDEPS} "${OBJECTDIR}/ERA/Src/ERA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-code -Os -MMD -MF "${OBJECTDIR}/ERA/Src/ERA.o.d" -o ${OBJECTDIR}/ERA/Src/ERA.o ERA/Src/ERA.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/OBD_M66_UNIT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/OBD_M66_UNIT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/OBD_M66_UNIT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/OBD_M66_UNIT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/OBD_M66_UNIT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
