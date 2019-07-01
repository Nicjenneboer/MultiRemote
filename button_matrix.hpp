#ifndef BUTTON_MATRIX_HPP
#define BUTTON_MATRIX_HPP

class button{
private:
	hwlib::target::pin_out & row;
	hwlib::target::pin_in & column;

public:
	std::array< signal, 100 > encode_data = {};
	button(hwlib::target::pin_out & row, hwlib::target::pin_in & column):
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


#endif // BUTTON_MATRIX_HPP