# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = g++
CC  = $(CXX)

# Generate dependencies in *.d files
DEPFLAGS = -MT $@ -MMD -MP -MF $*.d
SRC_DIR = src
BINDIR = bin
# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
# -g is for debugging.
CPPFLAGS =  -std=c++17
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast 
CXXFLAGS += -std=c++17 
CXXFLAGS += -g
CXXFLAGS += $(DEPFLAGS)
LDFLAGS =   -g -I.
#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Targets
TARGETS = memorynewsserver disknewsserver mynewsclient
all: $(TARGETS) libclientserver.a
	make -C test

MEMOBJS =  connection.o messagehandler.o server.o memorydb.o newsgroup.o article.o memorynewsserver.o mynewsserver.o
DISKOBJS = connection.o messagehandler.o server.o diskdb.o newsgroup.o article.o disknewsserver.o mynewsserver.o
MYCLIENTOBJS = connection.o mynewsclient.o messagehandler.o client.o
CLIENTOBJS = connection.o client.o
# Create the library; ranlib is for Darwin (OS X) and maybe other systems.
# Doesn't seem to do any damage on other systems.

libclientserver.a: connection.o server.o
	ar rv libclientserver.a  connection.o server.o
	ranlib libclientserver.a

client: $(CLIENTOBJS)
	$(CC) $(LDFLAGS) $^ -o client
disknewsserver: $(DISKOBJS)
	$(CC) $(LDFLAGS) $^ -o disknewsserver
memorynewsserver: $(MEMOBJS)
	$(CC) $(LDFLAGS) $^ -o memorynewsserver
mynewsclient: $(MYCLIENTOBJS)
	$(CC) $(LDFLAGS) $^ -o mynewsclient


%.o	:	$(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Phony targets
.PHONY: all clean distclean

SRC = $(wildcard *.cc)

# Standard clean
clean:
	$(RM) *.o $(TARGETS)

distclean: clean
	$(RM) libclientserver.a
	$(RM) *.d 
	make -C test distclean
install:
	mv $(TARGETS) $(BINDIR)

# Include the *.d files
-include $(SRC:.cc=.d)
