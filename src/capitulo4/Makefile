# The subdirectories in this directory.
SUBDIRS		= listing4.1 listing4.2 listing4.3 listing4.4 listing4.5 listing4.6 listing4.7 listing4.8 listing4.10 listing4.11 listing4.12 listing4.13 listing4.14 listing4.15 
# PROGRAMS	= listing4.1exe listing4.2exe listing4.3exe listing4.4exe listing4.5exe listing4.6exe listing4.7exe listing4.8exe listing4.10exe listing4.11exe listing4.12exe listing4.13exe listing4.14exe listing4.15exe 

# Link programs with the pthread library.
LDLIBS		= -lpthread

.PHONY:         all clean $(SUBDIRS)

all:		$(SUBDIRS)

# For each subdirectory, invoke a make subprocess.
$(SUBDIRS): 
	$(CC) $@/$@.c $(LDLIBS) -o ../../build/$@
	# $(CC) listing4.9/listing4.9.cpp $(LDLIBS)