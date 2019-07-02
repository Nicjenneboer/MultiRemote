#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include "hwlib.hpp"
#include "Protocols.hpp"

class Receiver{
protected:
  hwlib::target::pin_in pin_in;
  protocol & pro_data; 
  uint32_t & code;
  std::array< signal, 100 > raw_data = {};
  int switches = 0;

public:
  Receiver(
    hwlib::target::pin_in pin_in, 
    protocol & pro_data,
    uint32_t & code
  	):
  pin_in( pin_in ),
  pro_data( pro_data ),
  code( code)
  {}

  void detect();

  void match();

  void decode();


};

#endif // RECEIVER_HPP