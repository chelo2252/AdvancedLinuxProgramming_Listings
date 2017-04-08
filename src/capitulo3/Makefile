#make cap3

# The subdirectories in this directory.
SUBDIRS		= listing3.1 listing3.2 listing3.3 listing3.4 listing3.5 listing3.6 listing3.7 
# PROGRAMS	= listing3.1 listing3.2 listing3.3 listing3.4 listing3.5 listing3.6 listing3.7

.PHONY:         all clean $(SUBDIRS)

all:		$(SUBDIRS)

# For each subdirectory, invoke a make subprocess.
$(SUBDIRS): 
	$(CC) $@/$@.c -o ../../build/$@