#include "IR.hpp"

void IR::receive(unsigned int time){
	unsigned int us = hwlib::now_us();
	clear();
	while((hwlib::now_us() - us < time && Receiver::raw_data[0].ms==0) ||
		(time==0 && Receiver::raw_data[0].ms==0)){
		detect();
		match();
	}
	if(pro_data.bits!=0){
		decode();
	}
}

void IR::transmit(){
	if(code!=0){
		encode();
		send();
	}
}

void IR::clear(){
	code=0;
	pro_data={0};
	Receiver::raw_data={};
	Receiver::switches=0;
	Transmitter::encoded_data={};
}

void IR::print(bool i){

	if(code==0){
		hwlib::cout << "NOT FOUND!";
	}else{
		for(const char & n : pro_data.name){
			hwlib::cout << n;
		}
	}
		hwlib::cout << " - " << hwlib::hex << code 
		<< "\nLength: " << hwlib::dec << switches << "\n\n";
		if(i==1){
			hwlib::cout <<"Raw Data:\n";
			for(const signal & s : Receiver::raw_data){
				if(s.ms!=0){
					hwlib::cout  << s;
				}
			}
			hwlib::cout << "\n\nEncoded Data:\n";
			for(const signal & s : encoded_data){
				if(s.ms!=0){
					hwlib::cout << s;
				}
			}
			hwlib::cout << "\n\n";
		}
}