// ==========================================================================
//
// File      : IR_Data.hpp
// Part of   : IR Library
// Copyright : Nic Jenneboer  Mail : Nicjenneboer@gmail.com
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef IR_DATA_HPP
#define IR_DATA_HPP

#include "hwlib.hpp"
#include "Protocols.hpp"


/// @file

/// \brief
/// IR_Data
/// \details
/// IR_Data stores 32 bit with an associated protocol.
class IR_Data{
protected:
	protocol & pro_data;
  	uint32_t & code;

public:
	IR_Data(
		protocol & pro_data,
    	uint32_t & code
    ):
    pro_data( pro_data ),
    code( code )
    {}

/// \brief
/// Print the name of the Protocol and the 32 bit code.
    void print_protocol(){
    	if(code!=0){
    		for(const char & n : pro_data.name){
    			hwlib::cout << n;
    		}
    		hwlib::cout << " - HEX:" << hwlib::hex 
    		<< code << " DEC:" <<  hwlib::dec << code 
    		<< "\nBits: " << pro_data.bits << "\n\n";
    	}else{
    		hwlib::cout << "NOT FOUND!\n\n";
    	}
	}

/// \brief
/// This inRange() function return true if an int value is in x range with another int value.
    bool inRange(int in, int out, int range){
  		if(in>out-range && in<out+range){
      		return true;
    	}
    	return false;
	}

};


#endif // TRANSLATE