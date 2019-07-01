#ifndef GAME_HPP
#define GAME_HPP

#include "hwlib.hpp"



class map : public hwlib::target::board{
protected:
	std::array< atmega328::pin_out *, 9 > points;
	std::array< int , 9 > board;

public:
	map():
	points{
		&led7, &led8, &led9,
		&led4, &led5, &led6,
		&led1, &led2, &led3
	},
	board{
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	}{}

	void color_write(
		const int i_red,
		const int i_blue,
		const int i_green
		);  

	void color_flush();

	void draw();

	bool overlaps( const map & other );

	virtual void interact( map & other ){}
	virtual void mark()=0;
	virtual void win(){}
};



class pot : public map{
public:
	void mark();
};



class sets : public map{
private:
	bool overlap=0;
public:

	const uint8_t no_winner = 3;

	void mark();
	void interact( map & other );
	int check(std::array< int , 9 > board);
	void win();
};



#endif 