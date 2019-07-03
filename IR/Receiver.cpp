

#include "Receiver.hpp"

  bool inRange(int in, int out, int range){
 	if(in>out-range && in<out+range){
    	return true;
  	}
  	return false;
}


void Receiver::detect(){
    bool tmp;
  	long unsigned int ms = hwlib::now_us();
  	long unsigned int ms_dif;
    switches=0;
    raw_data={};

    while(pin_in.read()!=0)
    {
        if(hwlib::now_us() - ms > 10000){
          return;
        }
    }
    tmp = pin_in.read();
    ms=hwlib::now_us();
    while(switches<2 || hwlib::now_us()-ms<raw_data[0].ms*3){
      	if(tmp!=pin_in.read()){
    		ms_dif=hwlib::now_us()-ms;
      		raw_data[switches]=signal{ms_dif, !tmp};
      		switches++;
       		tmp = !tmp;
       		ms=hwlib::now_us();
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
      		for(int i=0; i<100; i++){
        		if(raw_data[i].ms!=0 && tmp){
          			if(i<2 && !inRange(raw_data[i].ms, p.start[i].ms, p.range)){
              			tmp=false;
          			}if(i>=2){
            			for(int j=0; j<2; j++){
              				if(raw_data[i].stat==j){
                				if(!inRange(raw_data[i].ms, p.l_one[1-j].ms, p.range) &&
                				!inRange(raw_data[i].ms, p.l_zero[1-j].ms, p.range)){
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
      	if(inRange(raw_data[tmp].ms, pro_data.l_one[0].ms, pro_data.range) &&
        	inRange(raw_data[tmp+1].ms, pro_data.l_one[1].ms, pro_data.range)){
        	code |= (1 << (pro_data.bits - i-1));
      	}
  	}
}






