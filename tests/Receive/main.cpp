#include "../../IR/IR.hpp"
#include "hwlib.hpp"

int main( void ){
	hwlib::wait_ms(100);
	auto trans_p = hwlib::target::pin_out(hwlib::target::pins::d45);
	auto rec_p = hwlib::target::pin_in(hwlib::target::pins::d43);

	protocol prot={};
	uint32_t code=0;

	Receiver rec(rec_p, prot, code);
	Transmitter trans(trans_p, prot, code);

	protocol tmp;

	for(;;){
		hwlib::wait_ms(100);
		rec.detect();
		rec.match();
		rec.decode();
		trans.encode();
		rec.print_protocol();
		rec.print();
		trans.print();
		tmp = rec.get_protocol();
		if(tmp.bits!=0){
			hwlib::cout << "Start: " << tmp.start[0] << tmp.start[1]
						<< "\nOne  : " << tmp.l_one[0] << tmp.l_one[1]
						<< "\nZero : " << tmp.l_zero[0] << tmp.l_zero[1]
						<< "\n\n";
		}
		prot={};
		code={};
	}

}