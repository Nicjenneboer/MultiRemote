// ==========================================================================
//
// File      : MultiRemote.cpp
// Part of   : MultiRemote
// Copyright : Nic Jenneboer
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

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

void IR::clear(){
	code=0;
	pro_data={};
}

void IR::print(){
	Receiver::print_protocol();
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