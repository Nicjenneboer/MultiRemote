#include "hwlib.hpp"
#include "IR/IR.hpp"
#include "button_matrix.hpp"

int main(void){

auto r0 = hwlib::target::pin_out(hwlib::target::pins::d46);
auto r1 = hwlib::target::pin_out(hwlib::target::pins::d47);
auto r2 = hwlib::target::pin_out(hwlib::target::pins::d48);
auto r3 = hwlib::target::pin_out(hwlib::target::pins::d49);

auto c0 = hwlib::target::pin_in(hwlib::target::pins::d50);
auto c1 = hwlib::target::pin_in(hwlib::target::pins::d51);
auto c2 = hwlib::target::pin_in(hwlib::target::pins::d52);
auto c3 = hwlib::target::pin_in(hwlib::target::pins::d53);

button b0(r0, c0), b1(r0, c1), b2(r0, c2), b3(r0, c3),
	b4(r1, c0), b5(r1, c1), b6(r1, c2), b7(r1, c3),
	b8(r2, c0), b9(r2, c1), b10(r2, c2), b11(r2, c3),
	b12(r3, c0), b13(r3, c1), b14(r3, c2), b15(r3, c3);

Receiver rec(hwlib::target::pins::d3);
transmitter trans(hwlib::target::pins::d2);
auto led = hwlib::target::pin_out(hwlib::target::pins::d4);


std::array< button *, 16 > buttons = {
	&b0, &b1, &b2, &b3,
	&b4, &b5, &b6, &b7,
	&b8, &b9, &b10, &b11,
	&b12, &b13, &b14, &b15,
};
int us;
for(;;){
	hwlib::wait_ms(100);
	for(int i=0; i<16; i++){
		if(buttons[i]->read()==0){
			us = hwlib::now_us();
			while(buttons[i]->read()==0){
				trans.send(buttons[i]->encode_data);
				hwlib::wait_ms(100);
				if(hwlib::now_us() - us > 3000000){
					led.write(1);
					led.flush();
					rec.detect();
					buttons[i]->encode_data=rec.get();
				}
			}
		
			led.write(0);
			led.flush();
			rec.print();
		}
	}
}


}




