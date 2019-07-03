#include "../../IR/IR.hpp"
#include "hwlib.hpp"


int main( void ){

	auto rec = hwlib::target::pin_in(hwlib::target::pins::d43);
	auto trans = hwlib::target::pin_out(hwlib::target::pins::d45);

	IR receiver(rec, trans);

	for(;;){
		receiver.receive();
		receiver.encode();
		receiver.print(1);
	}
}