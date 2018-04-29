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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Animator.o \
	${OBJECTDIR}/AssetManager.o \
	${OBJECTDIR}/Factory.o \
	${OBJECTDIR}/Hud.o \
	${OBJECTDIR}/Juego.o \
	${OBJECTDIR}/MPuntuaciones.o \
	${OBJECTDIR}/Mapa/Mapa.o \
	${OBJECTDIR}/Mapa/Nodo/Minijuegos/Minijuego.o \
	${OBJECTDIR}/Mapa/Nodo/Minijuegos/goingUp.o \
	${OBJECTDIR}/Mapa/Nodo/NPCs/NPC.o \
	${OBJECTDIR}/Mapa/Nodo/NPCs/Skull.o \
	${OBJECTDIR}/Mapa/Nodo/NPCs/xPlotato.o \
	${OBJECTDIR}/Mapa/Nodo/Nodo.o \
	${OBJECTDIR}/MenuInicio.o \
	${OBJECTDIR}/MenuPausa.o \
	${OBJECTDIR}/Particle.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/boss.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mj_t.o \
	${OBJECTDIR}/particleSystem.o \
	${OBJECTDIR}/physicsEngine/contactListener.o \
	${OBJECTDIR}/physicsEngine/pBody.o \
	${OBJECTDIR}/physicsEngine/pConverter.o \
	${OBJECTDIR}/physicsEngine/physicsEngine.o \
	${OBJECTDIR}/renderEngine/rMusic.o \
	${OBJECTDIR}/renderEngine/rSoundBuffer.o \
	${OBJECTDIR}/renderEngine/renderEngine.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Animator.o: Animator.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Animator.o Animator.cpp

${OBJECTDIR}/AssetManager.o: AssetManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AssetManager.o AssetManager.cpp

${OBJECTDIR}/Factory.o: Factory.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Factory.o Factory.cpp

${OBJECTDIR}/Hud.o: Hud.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hud.o Hud.cpp

${OBJECTDIR}/Juego.o: Juego.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Juego.o Juego.cpp

${OBJECTDIR}/MPuntuaciones.o: MPuntuaciones.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MPuntuaciones.o MPuntuaciones.cpp

${OBJECTDIR}/Mapa/Mapa.o: Mapa/Mapa.cpp
	${MKDIR} -p ${OBJECTDIR}/Mapa
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mapa/Mapa.o Mapa/Mapa.cpp

${OBJECTDIR}/Mapa/Nodo/Minijuegos/Minijuego.o: Mapa/Nodo/Minijuegos/Minijuego.cpp
	${MKDIR} -p ${OBJECTDIR}/Mapa/Nodo/Minijuegos
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mapa/Nodo/Minijuegos/Minijuego.o Mapa/Nodo/Minijuegos/Minijuego.cpp

${OBJECTDIR}/Mapa/Nodo/Minijuegos/goingUp.o: Mapa/Nodo/Minijuegos/goingUp.cpp
	${MKDIR} -p ${OBJECTDIR}/Mapa/Nodo/Minijuegos
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mapa/Nodo/Minijuegos/goingUp.o Mapa/Nodo/Minijuegos/goingUp.cpp

${OBJECTDIR}/Mapa/Nodo/NPCs/NPC.o: Mapa/Nodo/NPCs/NPC.cpp
	${MKDIR} -p ${OBJECTDIR}/Mapa/Nodo/NPCs
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mapa/Nodo/NPCs/NPC.o Mapa/Nodo/NPCs/NPC.cpp

${OBJECTDIR}/Mapa/Nodo/NPCs/Skull.o: Mapa/Nodo/NPCs/Skull.cpp
	${MKDIR} -p ${OBJECTDIR}/Mapa/Nodo/NPCs
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mapa/Nodo/NPCs/Skull.o Mapa/Nodo/NPCs/Skull.cpp

${OBJECTDIR}/Mapa/Nodo/NPCs/xPlotato.o: Mapa/Nodo/NPCs/xPlotato.cpp
	${MKDIR} -p ${OBJECTDIR}/Mapa/Nodo/NPCs
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mapa/Nodo/NPCs/xPlotato.o Mapa/Nodo/NPCs/xPlotato.cpp

${OBJECTDIR}/Mapa/Nodo/Nodo.o: Mapa/Nodo/Nodo.cpp
	${MKDIR} -p ${OBJECTDIR}/Mapa/Nodo
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mapa/Nodo/Nodo.o Mapa/Nodo/Nodo.cpp

${OBJECTDIR}/MenuInicio.o: MenuInicio.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MenuInicio.o MenuInicio.cpp

${OBJECTDIR}/MenuPausa.o: MenuPausa.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MenuPausa.o MenuPausa.cpp

${OBJECTDIR}/Particle.o: Particle.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Particle.o Particle.cpp

${OBJECTDIR}/Player.o: Player.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/boss.o: boss.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/boss.o boss.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/mj_t.o: mj_t.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mj_t.o mj_t.cpp

${OBJECTDIR}/particleSystem.o: particleSystem.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/particleSystem.o particleSystem.cpp

${OBJECTDIR}/physicsEngine/contactListener.o: physicsEngine/contactListener.cpp
	${MKDIR} -p ${OBJECTDIR}/physicsEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/physicsEngine/contactListener.o physicsEngine/contactListener.cpp

${OBJECTDIR}/physicsEngine/pBody.o: physicsEngine/pBody.cpp
	${MKDIR} -p ${OBJECTDIR}/physicsEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/physicsEngine/pBody.o physicsEngine/pBody.cpp

${OBJECTDIR}/physicsEngine/pConverter.o: physicsEngine/pConverter.cpp
	${MKDIR} -p ${OBJECTDIR}/physicsEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/physicsEngine/pConverter.o physicsEngine/pConverter.cpp

${OBJECTDIR}/physicsEngine/physicsEngine.o: physicsEngine/physicsEngine.cpp
	${MKDIR} -p ${OBJECTDIR}/physicsEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/physicsEngine/physicsEngine.o physicsEngine/physicsEngine.cpp

${OBJECTDIR}/renderEngine/rMusic.o: renderEngine/rMusic.cpp
	${MKDIR} -p ${OBJECTDIR}/renderEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/renderEngine/rMusic.o renderEngine/rMusic.cpp

${OBJECTDIR}/renderEngine/rSoundBuffer.o: renderEngine/rSoundBuffer.cpp
	${MKDIR} -p ${OBJECTDIR}/renderEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/renderEngine/rSoundBuffer.o renderEngine/rSoundBuffer.cpp

${OBJECTDIR}/renderEngine/renderEngine.o: renderEngine/renderEngine.cpp
	${MKDIR} -p ${OBJECTDIR}/renderEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/renderEngine/renderEngine.o renderEngine/renderEngine.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
