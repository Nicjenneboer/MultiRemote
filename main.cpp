
#include "IR/IR.hpp"
#include "MultiRemote.hpp"

int main(void){

	

	auto led = hwlib::target::pin_out(hwlib::target::pins::d44);
	auto receiver = hwlib::target::pin_in(hwlib::target::pins::d43);
	auto transmitter = hwlib::target::pin_out(hwlib::target::pins::d45);

	auto r0 = hwlib::target::pin_out(hwlib::target::pins::d46);
	auto r1 = hwlib::target::pin_out(hwlib::target::pins::d47);
	auto r2 = hwlib::target::pin_out(hwlib::target::pins::d48);
	auto r3 = hwlib::target::pin_out(hwlib::target::pins::d49);

	auto c0 = hwlib::target::pin_in(hwlib::target::pins::d50);
	auto c1 = hwlib::target::pin_in(hwlib::target::pins::d51);
	auto c2 = hwlib::target::pin_in(hwlib::target::pins::d52);
	auto c3 = hwlib::target::pin_in(hwlib::target::pins::d53);

	std::array< hwlib::target::pin_out, 4 > rows = {r0, r1, r2, r3};
	std::array< hwlib::target::pin_in, 4 > columns= {c0, c1, c2, c3};

	button_matrix matrix(rows, columns, receiver, transmitter);

	int us;

hwlib::wait_ms(100);

	for(;;){
		for(button & b : matrix.buttons){
			if(b.read()==0){
				us=hwlib::now_us();
				while(b.read()==0){
					b.transmit();
					hwlib::wait_ms(50);
					if(hwlib::now_us() - us > 3000000){
						led.write(1);
						us=hwlib::now_us();
						b.receive(3000000);
						led.write(0);
						b.transmit();
						b.print(0);
					}
				}
			}
		}
	}
}




