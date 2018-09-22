#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AppManager.o \
	${OBJECTDIR}/AppTimeRecords.o \
	${OBJECTDIR}/Server.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/usr/local/lib/libwt.so /usr/local/lib/libwtdbo.so /usr/local/lib/libwtdbopostgres.so /usr/local/lib/libwthttp.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/apptimerecords

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/apptimerecords: /usr/local/lib/libwt.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/apptimerecords: /usr/local/lib/libwtdbo.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/apptimerecords: /usr/local/lib/libwtdbopostgres.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/apptimerecords: /usr/local/lib/libwthttp.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/apptimerecords: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/apptimerecords ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/AppManager.o: AppManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AppManager.o AppManager.cpp

${OBJECTDIR}/AppTimeRecords.o: AppTimeRecords.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AppTimeRecords.o AppTimeRecords.cpp

${OBJECTDIR}/Server.o: Server.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server.o Server.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwt.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwtdbo.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwtdbopostgres.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwthttp.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/apptimerecords

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
