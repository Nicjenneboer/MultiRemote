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
RELATIVE := ..
SOURCES := ../../IR/IR.cpp ../../IR/Transmitter.cpp ../../IR/Receiver.cpp 

# header files in this project
HEADERS := ../../IR/IR.hpp ../../IR/Protocols.hpp ../../IR/Receiver.hpp ../../IR/Transmitter.hpp

# other places to look for files for this project
SEARCH  := 

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/makefile.link
