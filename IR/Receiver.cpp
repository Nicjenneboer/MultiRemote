#include "hwlib.hpp"
#include "Receiver.hpp"
#include "Protocols.hpp"

bool inRange(int in, int out, int range){
  if(in>out-range && in<out+range){
    return true;
  }
  return false;
}


void Receiver::detect(){
	bool tmp;
  	long unsigned int ms;
  	long unsigned int ms_dif;
  	int switches=0;

  	code = 0;
  	raw_data = {};
  	protocol_D= {};
  	encode_data={};

    while(read()!=0){};
     	tmp = read();
    	ms=hwlib::now_us();
    	while(switches<2 || hwlib::now_us()-ms<raw_data[0].ms*2){
      	if(tmp!=read()){
       		ms_dif=hwlib::now_us()-ms;
      		raw_data[switches]=signal{ms_dif, !tmp};
       		switches++;
       		tmp = !tmp;
       		ms=hwlib::now_us();
      	}
    } 
  match();
  decode();
  encode();
}

void Receiver::match(){
    for( protocol p : protocols){
      bool tmp = true;
      for(int i=0; i<100; i++){
        if(raw_data[i].ms!=0 && tmp==true){
          if(i<2 && !inRange(raw_data[i].ms, p.start[i].ms, p.range)){
              tmp=false;
          }else if (i>3){
            for(int j=0; j<2; j++){
              if(raw_data[i].stat==j){
                if(!inRange(raw_data[i].ms, p.l_one[1-j].ms, p.range) &&
                !inRange(raw_data[i].ms, p.l_zero[1-j].ms, p.range)){
                  tmp=false;
      }}}}}}
      if(tmp==true){
        protocol_D=p;
        return;
      }
    }
  protocol_D={};
}

void Receiver::decode(){
  int tmp;
	for(int i=0; i<protocol_D.c_bits; i++){
      tmp=i*2+2;
			if(inRange(raw_data[tmp].ms, protocol_D.l_one[0].ms, protocol_D.range) &&
				inRange(raw_data[tmp+1].ms, protocol_D.l_one[1].ms, protocol_D.range)){
				code |= (1 << (protocol_D.c_bits - i-1));
			}
	}
}

void Receiver::encode(){
  int tmp;
	for(int i=0; i<2; i++){
    encode_data[i] = protocol_D.start[i];
  }
    for(int i=0; i<=protocol_D.c_bits; i++){
      tmp=i*2+2;
      if((code & (1 << (protocol_D.c_bits-i-1))) != 0){
        encode_data[tmp]=protocol_D.l_one[0];
        encode_data[tmp+1]=protocol_D.l_one[1];
      }else{
        encode_data[tmp]=protocol_D.l_zero[0];
        encode_data[tmp+1]=protocol_D.l_zero[1];
      }
    }
}

void Receiver::print(bool i){
	
  for(const char & n : protocol_D.name){
    hwlib::cout << n;
  }
	hwlib::cout << " - " << hwlib::hex << code <<"\n\n";


  if(i==1){
  for(const signal & x : raw_data){
    if(x.ms!=0){
      hwlib::cout << x.stat << "[" << hwlib::dec << x.ms << "] ";
    }
  }
  hwlib::cout << "\n\n";
  for(const signal & x : encode_data){
    if(x.ms!=0){
      hwlib::cout << x.stat << "[" << hwlib::dec << x.ms << "] ";
    }
  }
  hwlib::cout << "\n\n";
  }
}




