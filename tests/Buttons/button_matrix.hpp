#ifndef BUTTON_MATRIX_HPP
#define BUTTON_MATRIX_HPP


class button{
private:
	hwlib::target::pin_out & row;
	hwlib::target::pin_in & column;

public:
	button(
		hwlib::target::pin_out & row, 
		hwlib::target::pin_in & column
	):
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
		std::array< hwlib::target::pin_in, 4 > c
	):
	buttons{
		button(r[0], c[0]), button(r[0], c[1]), 
		button(r[0], c[2]), button(r[0], c[3]),
		button(r[1], c[0]), button(r[1], c[1]), 
		button(r[1], c[2]), button(r[1], c[3]),
		button(r[2], c[0]), button(r[2], c[1]), 
		button(r[2], c[2]), button(r[2], c[3]),
		button(r[3], c[0]), button(r[3], c[1]), 
		button(r[3], c[2]), button(r[3], c[3])
	} {}
};

#endif // BUTTON_MATRIX_HPP