#make cap5

# The subdirectories in this directory.
SUBDIRS		= listing5.1 listing5.2 listing5.3 listing5.4 listing5.5 listing5.6 listing5.7 listing5.8 listing5.9 listing5.10 listing5.11 listing5.12
# PROGRAMS	= listing5.1exe listing5.2exe listing5.3exe listing5.4exe listing5.5exe listing5.6exe listing5.7exe listing5.8exe listing5.9exe listing5.10exe listing5.11exe

.PHONY:         all clean $(SUBDIRS)

all:		$(SUBDIRS)

# For each subdirectory, invoke a make subprocess.
$(SUBDIRS): 
	$(CC) $@/$@.c -o ../../build/$@