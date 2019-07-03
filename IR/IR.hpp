#ifndef IR_HPP
#define IR_HPP

#include "hwlib.hpp"
#include "Receiver.hpp"
#include "Transmitter.hpp"
#include "Protocols.hpp"


class IR : public Receiver, public Transmitter {
private:
  protocol pro_data={}; 
  uint32_t code=0;
public:
  IR( 
      hwlib::target::pin_in pin_in, 
      hwlib::target::pin_out pin_out
    ):
    Receiver(pin_in, pro_data, code),
    Transmitter(pin_out, pro_data, code)
  {}

  void receive(unsigned int time=0);

  void transmit();

  void clear();

  void print(bool i=0);

};


#endif // IR