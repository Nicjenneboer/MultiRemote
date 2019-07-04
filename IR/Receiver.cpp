// ==========================================================================
//
// File      : Receiver.cpp
// Part of   : IR Library
// Copyright : Nic Jenneboer  Mail : Nicjenneboer@gmail.com
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "Receiver.hpp"
void Receiver::detect(unsigned int time){
    bool tmp;
  	long unsigned int us = hwlib::now_us();
  	long unsigned int us_dif;
    switches=0;
    raw_data={};

    while(pin_in.read()!=0)
    {
        if(time!=0 && hwlib::now_us() - us > time){
          return;
        }
    }
    tmp = pin_in.read();
    us=hwlib::now_us();
    while(switches<2 || hwlib::now_us()-us<raw_data[0].us*2){
      	if(tmp!=pin_in.read()){
    		us_dif=hwlib::now_us()-us;
      		raw_data[switches]=signal{us_dif, !tmp};
      		switches++;
       		tmp = !tmp;
       		us=hwlib::now_us();
      	}
    } 
}

void Receiver::match(){
    bool tmp;
    for( protocol p : protocols){
    	tmp = true;
    	if((switches-2)/2!=p.bits){
        	tmp=false;
      	}else{
      		for(int i=0; i<max_length_signals; i++){
        		if(raw_data[i].us!=0 && tmp){
          			if(i<2 && !inRange(raw_data[i].us, p.start[i].us, p.range)){
              			tmp=false;
          			}if(i>=2){
            			for(int j=0; j<2; j++){
              				if(raw_data[i].stat==j){
                				if(!inRange(raw_data[i].us, p.l_one[1-j].us, p.range) &&
                				!inRange(raw_data[i].us, p.l_zero[1-j].us, p.range)){
                  					tmp=false;
                				}
              				}
            			}
          			}
        		}
      		}
    	}if(tmp==true){
       		pro_data=p;
       		return;
      	}
    }
}

void Receiver::decode(){
  int tmp;
    for(int i=0; i<pro_data.bits; i++){
      tmp=i*2+2;
        if(inRange(raw_data[tmp].us, pro_data.l_one[0].us, pro_data.range) &&
          inRange(raw_data[tmp+1].us, pro_data.l_one[1].us, pro_data.range)){
          code |= (1 << (pro_data.bits - i-1));
        }
    }
}

void Receiver::print(){
  if(raw_data[0].us!=0){
      hwlib::cout <<"Raw Data:\n";
      for(const signal & s : raw_data){
        if(s.us!=0){
          hwlib::cout  << s;
        }
      }
      hwlib::cout << "\n\n";
    }
}