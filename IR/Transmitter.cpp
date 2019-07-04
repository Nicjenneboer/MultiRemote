// ==========================================================================
//
// File      : Transmitter.cpp
// Part of   : IR Library
// Copyright : Nic Jenneboer
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "Transmitter.hpp"

void Transmitter::encode(){
	encoded_data={};
	if(code!=0){
		int tmp;
		for(int i=0; i<2; i++){
	    	encoded_data[i] = pro_data.start[i];
	  	}
	    for(int i=0; i<=pro_data.bits; i++){
	    	tmp=i*2+2;
	    	if((code & (1 << (pro_data.bits-i-1))) != 0){
	        	encoded_data[tmp]=pro_data.l_one[0];
	        	encoded_data[tmp+1]=pro_data.l_one[1];
	      	}else{
	        	encoded_data[tmp]=pro_data.l_zero[0];
	        	encoded_data[tmp+1]=pro_data.l_zero[1];
	      	}
	    }
	}
}


void Transmitter::send(){
	if(code!=0){
		long unsigned int us;
		for(signal x : encoded_data){
			if(x.us!=0){
			us = hwlib::now_us();
			if(x.stat==1){
				while(hwlib::now_us() - us < x.us){
					pin_out.write(1);
					pin_out.flush();
					hwlib::wait_us(12);
					pin_out.write(0);
					pin_out.flush();
					hwlib::wait_us(12);
				}
			}else{
				hwlib::wait_us(x.us);
			}
		}
		pin_out.write(0);
		pin_out.flush();
		}
	}
}

void Transmitter::print(){
	if(encoded_data[0].us!=0){
    	hwlib::cout <<"Encoded Data:\n";
    	for(const signal & s : encoded_data){
    		if(s.us!=0){
          		hwlib::cout  << s;
        	}
      	}
      	hwlib::cout << "\n\n";
  	}
}