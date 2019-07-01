#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include "hwlib.hpp"
#include "Protocols.hpp"


class Receiver : public hwlib::target::pin_in {
private:
  std::array< signal, 100 > raw_data = {};
  protocol protocol_D = {};
  uint32_t code = 0;
  std::array< signal, 100 > encode_data = {};

public:
  Receiver(hwlib::target::pin_in pin):
  hwlib::target::pin_in( pin )
  {}

  void detect();

  void print(bool i=0);

  void match();

  void decode();

  void encode();

  std::array< signal, 100 >  get(){return encode_data;}
};

#endif // RECEIVER_HPP