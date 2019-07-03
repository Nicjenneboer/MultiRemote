#include "hwlib.hpp"
#include "button_matrix.hpp"

int main( void ){
	
	auto r0 = hwlib::target::pin_out(hwlib::target::pins::d53);
	auto r1 = hwlib::target::pin_out(hwlib::target::pins::d52);
	auto r2 = hwlib::target::pin_out(hwlib::target::pins::d51);
	auto r3 = hwlib::target::pin_out(hwlib::target::pins::d50);

	auto c0 = hwlib::target::pin_in(hwlib::target::pins::d49);
	auto c1 = hwlib::target::pin_in(hwlib::target::pins::d48);
	auto c2 = hwlib::target::pin_in(hwlib::target::pins::d47);
	auto c3 = hwlib::target::pin_in(hwlib::target::pins::d46);

	std::array< hwlib::target::pin_out, 4 > rows = {r0, r1, r2, r3};
	std::array< hwlib::target::pin_in, 4 > columns= {c0, c1, c2, c3};

	button_matrix matrix(rows, columns);



	for(;;){
		hwlib::wait_ms(100);
		for(int i=0; i<16; i++){
			if(matrix.buttons[i].read()==0){
				hwlib::cout << i << "\n";
			}
		}

	}	
}