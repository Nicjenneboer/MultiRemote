#include "hwlib.hpp"
#include "Transmitter.hpp"
#include "Protocols.hpp"

void transmitter::write( bool b ){
	if( b ){
         // eable C match -> pin set
         TC0->TC_CHANNEL[ 0 ].TC_CMR |= TC_CMR_ACPC_SET;         
      } else {
         // remove pin C match action
         TC0->TC_CHANNEL[ 0 ].TC_CMR &= ~ ( 0x3 << 18);  
      }
}

void transmitter::send(std::array< signal, 100 > encode_data){
	for(signal x : encode_data){
		write(x.stat);
		hwlib::wait_us(x.ms);
	}
	write(0);
}