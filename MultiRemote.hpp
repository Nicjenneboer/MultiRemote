#ifndef MULTIREMOTE_HPP
#define MULTIREMOTE_HPP

#include "IR/IR.hpp"

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

class button : public IR{
private:
	hwlib::target::pin_out & row;
	hwlib::target::pin_in & column;

public:
	button(
		hwlib::target::pin_out & row, 
		hwlib::target::pin_in & column,

		hwlib::target::pin_in reveiver_pin,
		hwlib::target::pin_out transmitter_pin
	):

	IR( reveiver_pin, transmitter_pin ),
	row( row ), column( column )
	{}

	bool read();
};

class button_matrix{
public:
	std::array< button , 16 > buttons;

	button_matrix(
		std::array< hwlib::target::pin_out, 4 > r,
		std::array< hwlib::target::pin_in, 4 > c,
		hwlib::target::pin_in in,
		hwlib::target::pin_out out
	):
	buttons{
		button(r[0], c[0], in, out), button(r[0], c[1], in, out), 
		button(r[0], c[2], in, out), button(r[0], c[3], in, out),
		button(r[1], c[0], in, out), button(r[1], c[1], in, out), 
		button(r[1], c[2], in, out), button(r[1], c[3], in, out),
		button(r[2], c[0], in, out), button(r[2], c[1], in, out), 
		button(r[2], c[2], in, out), button(r[2], c[3], in, out),
		button(r[3], c[0], in, out), button(r[3], c[1], in, out), 
		button(r[3], c[2], in, out), button(r[3], c[3], in, out)
	} {}
};

#endif // MULTIREMOTE