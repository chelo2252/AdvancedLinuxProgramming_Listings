# _*_MakeFile_*_

DESTDIR 	= /var/opt/lp3/tp1

# The subdirectories in this directory.
SUBDIRS		= capitulo3 capitulo4 capitulo5 

PROGRAMS_CAP_3 = listing3.1 listing3.2 listing3.3 listing3.4 listing3.5 listing3.6 listing3.7
PROGRAMS_CAP_4 = listing4.1 listing4.2 listing4.3 listing4.4 listing4.5 listing4.6 listing4.7 listing4.8 listing4.10 listing4.11 listing4.12 listing4.13 listing4.14 listing4.15 
PROGRAMS_CAP_5 = listing5.1 listing5.2 listing5.3 listing5.4 listing5.5 listing5.6 listing5.7 listing5.8 listing5.9 listing5.10 listing5.11 listing5.12

LDLIBSC4		= -lpthread

.PHONY:		all clean install $(SUBDIRS) $(PROGRAMS_CAP_3) $(PROGRAMS_CAP_4) $(PROGRAMS_CAP_5)

# The default target: build the contents of each subdirectory.
all:		$(SUBDIRS)

# For each subdirectory, invoke a make subprocess.
$(SUBDIRS):
	cd src/$@; $(MAKE)

install: 
	mkdir -p $(DESTDIR)
	cp -r * $(DESTDIR)/

$(PROGRAMS_CAP_3): 
	$(CC) src/capitulo3/$@/$@.c -o build/$@

$(PROGRAMS_CAP_4): 
	$(CC) src/capitulo4/$@/$@.c $(LDLIBSC4) -o build/$@

$(PROGRAMS_CAP_5): 
	$(CC) src/capitulo5/$@/$@.c -o build/$@

# Clean up build products
clean:
	rm -f build/*
