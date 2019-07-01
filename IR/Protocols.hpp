#ifndef PROTOCOLS_HPP
#define PROTOCOLS_HPP


struct signal{
  long unsigned int ms;
  bool stat;
};

struct protocol{
	char name[25];
	signal start[2];
	signal l_one[2];
	signal l_zero[2];
	int c_bits;
	int range;
};



const protocol sony = {
	"SONY",
	{{2400, 1},{600, 0}},
	{{1200, 1},{600, 0}},
	{{600, 1},{600, 0}},
	11,
	150
};

const protocol nec = {
	"NEC",
	{{9000, 1},{4500, 0}},
	{{560, 1},{1690, 0}},
	{{560, 1},{560, 0}},
	32,
	150
};

const protocol jvc = {
	"JVC",
	{{8400, 1},{4200, 0}},
	{{525, 1},{1575, 0}},
	{{525, 1},{525, 0}},
	16,
	150
};

const protocol samsung = {
	"SAMSUNG",
	{{4500, 1},{4500, 0}},
	{{550, 1},{1700, 0}},
	{{550, 1},{550, 0}},
	32,
	150
};


const std::array<protocol, 4> protocols = 
{
	sony,
	nec,
	jvc,
	samsung
};


#endif // PROTOCOLS_HPP