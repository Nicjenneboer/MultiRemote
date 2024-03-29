#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := IR/Receiver.cpp IR/Transmitter.cpp MultiRemote.cpp

# header files in this project
HEADERS := IR/IR.hpp IR/Receiver.hpp IR/Protocols.hpp IR/IR_Data.hpp IR/Transmitter.hpp  MultiRemote.hpp

# other places to look for files for this project
SEARCH  := 

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include Makefile.due
