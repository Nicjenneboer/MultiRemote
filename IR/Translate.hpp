#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP

#include "hwlib.hpp"
#include "Protocols.hpp"

class Translate{
protected:
	protocol & pro_data; 
  	uint32_t & code;

public:
	Translate(
		protocol & pro_data,
    	uint32_t & code
    ):
    pro_data( pro_data ),
    code( code )
    {}

    void print_protocol(){
    	if(code!=0){
    		for(const char & n : pro_data.name){
    			hwlib::cout << n;
    		}
    		hwlib::cout << " - " << hwlib::hex << code << hwlib::dec 
    		<< "\nBits: " << pro_data.bits << "\n\n";
    	}else{
    		hwlib::cout << "NOT FOUND!\n\n";
    	}
	}

    bool inRange(int in, int out, int range){
  		if(in>out-range && in<out+range){
      		return true;
    	}
    	return false;
	}

};


#endif // TRANSLATE