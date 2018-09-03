CXX = g++
CXXFLAGS = -std=c++11 -lpanel -lncurses
SRCDIR = src
HDRDIR = hdr
SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard hdr/*.h)

# file containing headers for precompilation 
PCH_SRC = precompile.h
# project headers that are going to get precompiled (pch dependencies)
PCH_HEADERS = header.h
# pch output filename
PCH_OUT = precompile.h.gch


all: $(SOURCES) $(HEADERS)
	$(CXX) $(SOURCES) $(CXXFLAGS) -I$(HDRDIR) -I$(SRCDIR) -o play_egyptian_ratscrew

# $(PCH_OUT): $(PCH_SRC) $(PCH_HEADERS)
#   $(CXX) $(CXXFLAGS) -o $@ $<

# %.o: %.cpp $(PCH_OUT)
#   $(CXX) $(CXXFLAGS) -include $(PCH_SRC) -c -o $@ $<