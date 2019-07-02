#include "IR.hpp"

void IR::receive(unsigned int time){
	clear();
	unsigned int us = hwlib::now_us();
	while(pro_data.bits==0 && hwlib::now_us() - us < time){
		detect();
		match();
	}
	decode();
}

void IR::transmit(){
	if(Transmitter::code!=0){
		encode();
		send();
	}
}

void IR::clear(){
	code=0;
	pro_data={};
	Receiver::raw_data={};
	Receiver::switches=0;
	Transmitter::encoded_data={};
}

void IR::print(bool i){
	if(code==0){
		hwlib::cout << "NOT FOUND!\n\n";
	}else{
		for(const char & n : pro_data.name){
			hwlib::cout << n;
		}
		hwlib::cout << " - " << hwlib::hex << code <<"\n\nRaw Data:\n";
		if(i==1){
			for(const signal & s : Receiver::raw_data){
				if(s.ms!=0){
					hwlib::cout << hwlib::dec << s;
				}
			}
			hwlib::cout << "\n\nEncoded Data:\n";
			for(const signal & s : encoded_data){
				if(s.ms!=0){
					hwlib::cout << hwlib::dec << s;
				}
			}
			hwlib::cout << "\n\n";
		}
	}
}