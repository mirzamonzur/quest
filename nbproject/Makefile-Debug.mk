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
CC=mpicc
CCC=mpic++
CXX=mpic++
FC=mpif90
AS=as

# Macros
CND_PLATFORM=MPI-Linux-x86
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
	${OBJECTDIR}/src/atoms/AtomicStruct.o \
	${OBJECTDIR}/src/atoms/Lattice.o \
	${OBJECTDIR}/src/band/BandStruct.o \
	${OBJECTDIR}/src/kpoints/KPoints.o \
	${OBJECTDIR}/src/negf/CohRgfa.o \
	${OBJECTDIR}/src/negf/NegfEloop.o \
	${OBJECTDIR}/src/negf/NegfResult.o \
	${OBJECTDIR}/src/negf/computegs.o \
	${OBJECTDIR}/src/parallel/Workers.o \
	${OBJECTDIR}/src/parallel/parloop.o \
	${OBJECTDIR}/src/potential/linearPot.o \
	${OBJECTDIR}/src/potential/potential.o \
	${OBJECTDIR}/src/potential/terminal.o \
	${OBJECTDIR}/src/python/pyqmicad.o \
	${OBJECTDIR}/src/qm/kp/graphenekp.o \
	${OBJECTDIR}/src/qm/kp/tikp.o \
	${OBJECTDIR}/src/qm/tb/graphenetb.o \
	${OBJECTDIR}/src/string/stringutils.o \
	${OBJECTDIR}/src/utils/ConsoleProgressBar.o \
	${OBJECTDIR}/src/utils/Timer.o \
	${OBJECTDIR}/src/utils/vout.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=-m64

# Assembler Flags
ASFLAGS=--64

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,--start-group /home/kh8hk/usr/lib/libboost_mpi_python.a /home/kh8hk/usr/lib/libboost_mpi.a -Wl,--end-group -Wl,--start-group /opt/intel/mkl/lib/intel64/libmkl_intel_lp64.a /opt/intel/mkl/lib/intel64/libmkl_core.a /opt/intel/mkl/lib/intel64/libmkl_intel_thread.a -Wl,--end-group -Wl,-Bdynamic -L/home/kh8hk/usr/lib -lboost_serialization -L/home/kh8hk/usr/lib -lboost_python -L/opt/intel/lib/intel64 -liomp5 -lpthread -lm -ldl -Wl,--no-as-needed

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk lib/qmicad.${CND_DLIB_EXT}

lib/qmicad.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p lib
	${LINK.cc} -o lib/qmicad.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

: doc/qmicad.doxy 
	@echo Performing Custom Build Step
	doxygen

${OBJECTDIR}/src/atoms/AtomicStruct.o: src/atoms/AtomicStruct.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/atoms
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/atoms/AtomicStruct.o src/atoms/AtomicStruct.cpp

${OBJECTDIR}/src/atoms/Lattice.o: src/atoms/Lattice.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/atoms
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/atoms/Lattice.o src/atoms/Lattice.cpp

${OBJECTDIR}/src/band/BandStruct.o: src/band/BandStruct.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/band
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/band/BandStruct.o src/band/BandStruct.cpp

${OBJECTDIR}/src/include/qmicad.hpp.gch: src/include/qmicad.hpp 
	${MKDIR} -p ${OBJECTDIR}/src/include
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o "$@" src/include/qmicad.hpp

${OBJECTDIR}/src/kpoints/KPoints.o: src/kpoints/KPoints.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/kpoints
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/kpoints/KPoints.o src/kpoints/KPoints.cpp

${OBJECTDIR}/src/negf/CohRgfa.o: src/negf/CohRgfa.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/negf
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/negf/CohRgfa.o src/negf/CohRgfa.cpp

${OBJECTDIR}/src/negf/NegfEloop.o: src/negf/NegfEloop.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/negf
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/negf/NegfEloop.o src/negf/NegfEloop.cpp

${OBJECTDIR}/src/negf/NegfResult.o: src/negf/NegfResult.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/negf
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/negf/NegfResult.o src/negf/NegfResult.cpp

${OBJECTDIR}/src/negf/computegs.o: src/negf/computegs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/negf
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/negf/computegs.o src/negf/computegs.cpp

${OBJECTDIR}/src/parallel/Workers.o: src/parallel/Workers.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/parallel
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/parallel/Workers.o src/parallel/Workers.cpp

${OBJECTDIR}/src/parallel/parloop.o: src/parallel/parloop.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/parallel
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/parallel/parloop.o src/parallel/parloop.cpp

${OBJECTDIR}/src/potential/linearPot.o: src/potential/linearPot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/potential
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/potential/linearPot.o src/potential/linearPot.cpp

${OBJECTDIR}/src/potential/potential.o: src/potential/potential.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/potential
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/potential/potential.o src/potential/potential.cpp

${OBJECTDIR}/src/potential/terminal.o: src/potential/terminal.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/potential
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/potential/terminal.o src/potential/terminal.cpp

${OBJECTDIR}/src/python/pyqmicad.o: src/python/pyqmicad.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/python
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/python/pyqmicad.o src/python/pyqmicad.cpp

${OBJECTDIR}/src/qm/kp/graphenekp.o: src/qm/kp/graphenekp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/qm/kp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/qm/kp/graphenekp.o src/qm/kp/graphenekp.cpp

${OBJECTDIR}/src/qm/kp/tikp.o: src/qm/kp/tikp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/qm/kp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/qm/kp/tikp.o src/qm/kp/tikp.cpp

${OBJECTDIR}/src/qm/tb/graphenetb.o: src/qm/tb/graphenetb.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/qm/tb
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/qm/tb/graphenetb.o src/qm/tb/graphenetb.cpp

${OBJECTDIR}/src/string/stringutils.o: src/string/stringutils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/string/stringutils.o src/string/stringutils.cpp

${OBJECTDIR}/src/utils/ConsoleProgressBar.o: src/utils/ConsoleProgressBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/ConsoleProgressBar.o src/utils/ConsoleProgressBar.cpp

${OBJECTDIR}/src/utils/Timer.o: src/utils/Timer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/Timer.o src/utils/Timer.cpp

${OBJECTDIR}/src/utils/vout.o: src/utils/vout.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/python2.6 -I/home/kh8hk/usr/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/vout.o src/utils/vout.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} lib/qmicad.${CND_DLIB_EXT}
	${RM} 

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
