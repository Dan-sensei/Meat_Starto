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
	${OBJECTDIR}/Tile.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/physicsEngine.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib /usr/lib/libsfml-audio.so /usr/lib/libsfml-graphics.so /usr/lib/libsfml-network.so /usr/lib/libsfml-system.so /usr/lib/libsfml-window.so /usr/lib/libBox2D.so /usr/lib/libtinyxml2.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: /usr/lib/libsfml-audio.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: /usr/lib/libsfml-graphics.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: /usr/lib/libsfml-network.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: /usr/lib/libsfml-system.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: /usr/lib/libsfml-window.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: /usr/lib/libBox2D.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: /usr/lib/libtinyxml2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Tile.o: Tile.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -I/usr/include/Box2D -include /usr/include/tinyxml2.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Tile.o Tile.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -I/usr/include/Box2D -include /usr/include/tinyxml2.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/physicsEngine.o: physicsEngine.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -I/usr/include/Box2D -include /usr/include/tinyxml2.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/physicsEngine.o physicsEngine.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsfml-audio.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsfml-graphics.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsfml-network.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsfml-system.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsfml-window.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libBox2D.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libtinyxml2.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
