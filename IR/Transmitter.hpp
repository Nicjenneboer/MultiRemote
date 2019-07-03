#ifndef TRANSMITTER_HPP
#define TRANSMITTER_HPP

#include "hwlib.hpp"
#include "Protocols.hpp"
#include "Translate.hpp"


class Transmitter : public Translate{
protected:
  hwlib::target::pin_out pin_out;
  std::array< signal, max_length_signals > encoded_data;

public:
  Transmitter(
    hwlib::target::pin_out pin_out,
    protocol & pro_data,
    uint32_t & code,
    std::array< signal, max_length_signals > encoded_data = {}
  ):
    Translate( pro_data, code ),
    pin_out( pin_out ), encoded_data( encoded_data )
    {}
  
  void encode();

  void send();

  void print();

};

#endif // TRANSMITTER