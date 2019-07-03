#include "MultiRemote.hpp"

void IR::receive(unsigned int time){
	unsigned int us = hwlib::now_us();
	clear();
	while(pro_data.bits==0 && time!=0 && hwlib::now_us() - us < time){
	detect(time);
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
	pro_data={};
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
		Receiver::print();
		Transmitter::print();
	}
}

bool button::read(){
	bool tmp;
	row.write(0);
	row.flush();
	tmp = column.read();
	row.write(1);
	row.flush();
	return tmp;
}