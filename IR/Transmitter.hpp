#ifndef TRANSMITTER_HPP
#define TRANSMITTER_HPP

#include "hwlib.hpp"
#include "Protocols.hpp"


class Transmitter{
protected:
  hwlib::target::pin_out pin_out;
  protocol & pro_data; 
  uint32_t & code;
	std::array< signal, 100 > encoded_data = {};

public:
  Transmitter(
    hwlib::target::pin_out pin_out,
    protocol & pro_data,
    uint32_t & code
  ):
    pin_out( pin_out ), pro_data( pro_data ), code( code )
    {}
  
  void encode();

  void send();

 
   
};

#endif // TRANSMITTER