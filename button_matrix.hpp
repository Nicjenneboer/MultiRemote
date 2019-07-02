#ifndef BUTTON_MATRIX_HPP
#define BUTTON_MATRIX_HPP

#include "IR/IR.hpp"

class button : public IR{
private:
	hwlib::target::pin_out & row;
	hwlib::target::pin_in & column;

public:
	std::array< signal, 100 > encoded_data = {};
	button(
		hwlib::target::pin_out & row, 
		hwlib::target::pin_in & column,

		hwlib::target::pin_in reveiver_pin,
		hwlib::target::pin_out transmitter_pin
	):

	IR( reveiver_pin, transmitter_pin ),
	row( row ), column( column )
	{}

	bool read(){
		bool tmp;
		row.write(0);
		row.flush();
		tmp = column.read();
		row.write(1);
		row.flush();
		return tmp;
	}
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

#endif // BUTTON_MATRIX_HPP