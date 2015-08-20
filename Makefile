UNAME_S := $(shell uname -s)

MATLABROOT = /Applications/MATLAB_R2015a.app
MATLABINCLUDEDIR = $(MATLABROOT)/extern/include/


CFLAGS = -Wall -fpic
DFLAG = -g
CFLAGS += -DTIMES -DSIGNALS -DB64 -DLRS_QUIET -DNOINFO


# Set DEBUG macro for functions to print GMPmat and mpx_t type data in debugger, 
# set NOINFO macro to avoid printing out number of rows/vertices/rays found during computation.
# CFLAGS += -DDEBUG


# Linker flags, do not modify!
LFLAGS = -shared -lmx -lmex -lmat -lgmp -L$(MATLABLIB)

ifeq ($(UNAME_S),Darwin)
	LFLAGS += -Wl,-no_pie
	EXTENTION = dylib
	MATLABLIB = $(MATLABROOT)/bin/maci64/
endif
ifeq ($(UNAME_S),Linux)
	LFLAGS += -Wl,-rpath,$(MATLABLIB)
	EXTENTION = so
	MATLABLIB = $(MATLABROOT)/bin/glnxa64/
endif

# Path to which everything should be installed, has to be on Matlab path!
INSTALLDIR = /Users/Manuel/Documents/MATLAB/Funktionen/

OBJECTS = mainFunctions.o translation_functions.o lrslib.o lrsgmp.o


all: libgeocalc.$(EXTENTION)
	mv libgeocalc.$(EXTENTION) $(INSTALLDIR)libgeocalc.$(EXTENTION)
	cp *.m $(INSTALLDIR)
	rm *.o


libgeocalc.$(EXTENTION): $(OBJECTS)
	$(CC) $(DFLAG) $(LFLAGS) $^ -o libgeocalc.$(EXTENTION) 

.c.o:
	$(CC) $(DFLAG) $(CFLAGS) -I$(MATLABINCLUDEDIR) $< -o $@ -c

clean:
	rm -f *.o *.$(EXTENTION)