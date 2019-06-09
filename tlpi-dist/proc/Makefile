include ../Makefile.inc

GEN_EXE = bad_longjmp display_env longjmp \
      necho setjmp_vars setjmp_vars_opt t_getenv t_pid

LINUX_EXE = modify_env

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
