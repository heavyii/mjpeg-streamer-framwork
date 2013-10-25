###############################################################
#
# Purpose: Makefile for "M-JPEG Streamer"
# Author.: Tom Stoeveken (TST)
# Version: 0.4
# License: GPL
#
###############################################################

# specifies where to install the binaries after compilation
# to use another directory you can specify it with:
# $ sudo make DESTDIR=/some/path install
DESTDIR = ./INSTALL

# set the compiler to use

#CC=arm-linux-gcc

SVNDEV := -D'SVN_REV="2013/10/25 v1.0"'
CFLAGS += $(SVNDEV)

# general compile flags, enable all warnings to make compile more verbose
CFLAGS += -O2 -DLINUX -D_GNU_SOURCE -Wall 
# CFLAGS += -g 
#CFLAGS +=  -DDEBUG

# we are using the libraries "libpthread" and "libdl"
# libpthread is used to run several tasks (virtually) in parallel
# libdl is used to load the plugins (shared objects) at runtime
LFLAGS += -lpthread -ldl

# define the name of the program
APP_BINARY = mjpg_streamer

# define the names and targets of the plugins
PLUGINS += output_file.so
PLUGINS += input_file.so

# define the names of object files
OBJECTS=mjpg_streamer.o utils.o

# this is the first target, thus it will be used implictely if no other target
# was given. It defines that it is dependent on the application target and
# the plugins
all: application plugins

application: $(APP_BINARY)

plugins: $(PLUGINS)

$(APP_BINARY): mjpg_streamer.c mjpg_streamer.h mjpg_streamer.o utils.c utils.h utils.o
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(APP_BINARY)
	chmod 755 $(APP_BINARY)

output_file.so: mjpg_streamer.h utils.h
	make -C plugins/output_file all
	cp plugins/output_file/output_file.so .

input_file.so: mjpg_streamer.h utils.h
	make -C plugins/input_file all
	cp plugins/input_file/input_file.so .

# cleanup
clean:
	make -C plugins/output_file $@
	make -C plugins/input_file $@
	rm -f *.a *.o $(APP_BINARY) core *~ *.so *.lo

# install MJPG-streamer and example webpages
install: all
	install --mode=755 $(APP_BINARY) $(DESTDIR)/
	install --mode=644 $(PLUGINS) $(DESTDIR)/

# remove the files installed above
uninstall:
	rm -f $(DESTDIR)/bin/$(APP_BINARY)
	for plug in $(PLUGINS); do \
	  rm -f $(DESTDIR)/lib/$$plug; \
	done;
