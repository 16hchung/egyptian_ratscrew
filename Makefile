CXX = g++
CXXFLAGS = -std=c++11 -lpanel -lncurses
SRC = src
HDR = hdr
SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard hdr/*.h)

# file containing headers for precompilation 
PCH_SRC = precompile.h
# project headers that are going to get precompiled (pch dependencies)
PCH_HEADERS = header.h
# pch output filename
PCH_OUT = precompile.h.gch


main: $(SOURCES) $(HEADERS)
	$(CXX) $(SOURCES) $(CXXFLAGS) -I$(HDR) -I$(SRC) -o main

# $(PCH_OUT): $(PCH_SRC) $(PCH_HEADERS)
#   $(CXX) $(CXXFLAGS) -o $@ $<

# %.o: %.cpp $(PCH_OUT)
#   $(CXX) $(CXXFLAGS) -include $(PCH_SRC) -c -o $@ $<

# # compiler
# CXX = g++

# # directories
# SRC = src
# OBJ = obj
# HDR = hdr

# # flags
# CXXFLAGS = -std=c++11 -Wall -g
# LIB = -lpanel -lncurses
# INC = -I$(HDR)

# # file containing headers for precompilation 
# PCH_SRC = precompile.h
# # project headers that are going to get precompiled (pch dependencies)
# PCH_HEADERS = header.h
# # pch output filename
# PCH_OUT = precompile.h.gch


# # main: $(OBJ)/main.o $(OBJ)/card.o
# # 	$(CXX) $(CXXFLAGS) $(INC) -o main $(OBJ)/main.o $(OBJ)/card.o

# # $(OBJ)/main.o: $(HDR)/main.h $(HDR)/card.h
# # 	$(CXX) $(CXXFLAGS) $(INC) -c $(SRC)/main.cpp $(LIB) -o $@

# # $(OBJ)/card.o: $(HDR)/card.h
# # 	$(CXX) $(CXXFLAGS) -c $(SRC)/card.cpp $(LIB) -o $@
# main: main.o player.o card.o
# 	$(CXX) $(CXXFLAGS) $(INC) $(LIB) -o main main.o card.o

# main.o: $(HDR)/main.h $(HDR)/player.h $(HDR)/card.h
# 	$(CXX) $(CXXFLAGS) $(INC) $(LIB) -c $(SRC)/main.cpp 

# player.o: $(SRC)/player.cpp $(HDR)/card.h

# card.o: $(SRC)/card.cpp



# # $(PCH_OUT): $(PCH_SRC) $(PCH_HEADERS)
# #   $(CXX) $(CXXFLAGS) -o $@ $<

# # %.o: %.cpp $(PCH_OUT)
# #   $(CXX) $(CXXFLAGS) -include $(PCH_SRC) -c -o $@ $<