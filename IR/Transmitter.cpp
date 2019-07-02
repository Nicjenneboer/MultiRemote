#include "hwlib.hpp"
#include "Transmitter.hpp"


void Transmitter::encode(){
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

void Transmitter::send(){
	long unsigned int us;
	for(signal x : encoded_data){
		if(x.ms!=0){
		us = hwlib::now_us();
		if(x.stat==1){
			while(hwlib::now_us() - us < x.ms){
				pin_out.write(1);
				hwlib::wait_us(12);
				pin_out.write(0);
				hwlib::wait_us(12);
			}
		}else{
			hwlib::wait_us(x.ms);
		}
	}
	pin_out.write(0);
	}
}