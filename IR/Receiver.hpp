#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include "hwlib.hpp"
#include "Protocols.hpp"
#include "Translate.hpp"

class Receiver : public Translate{
protected:
  hwlib::target::pin_in pin_in;
  std::array< signal, max_length_signals > raw_data;
  int switches = 0;

public:
  Receiver(
    hwlib::target::pin_in pin_in, 
    protocol & pro_data,
    uint32_t & code,
    std::array< signal, max_length_signals > raw_data = {0}
  ):
    Translate( pro_data, code ),
    pin_in( pin_in ), raw_data( raw_data )
  {}

  void detect(unsigned int time = 0);

  void match();

  void decode();

  void print ();

};

#endif // RECEIVER_HPP