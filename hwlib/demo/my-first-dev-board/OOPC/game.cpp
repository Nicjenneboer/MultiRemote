#include "hwlib.hpp"
#include "game.hpp"

bool turn = 0;

bool map::overlaps( const map & other ){
   		for(unsigned int i=0; i<9; i++){
   			if(board[i] != 0 && other.board[i] != 0){
   				return 1;
   			}
   		}
   		return 0;
}

void map::draw(){
		for(int i=0; i<3; i++){
			for(int j=0; j<9; j++){
				if(i==0 && board[j]==1){
					color_write(0,1,0);
					points[j]->write( 1 );
				}else if(i==1 && board[j]==2){
					color_write(0,0,1);
					points[j]->write( 1 );
				}else if(i==2 && board[j]==3){
					color_write(1,0,0);
					points[j]->write( 1 );
				}else{
					points[j]->write( 0 );
				}
				points[j]->flush();
			}
			color_flush();
			hwlib::wait_ms(1);
		}
	}

void pot::mark() {
	for(unsigned int i=0; i<9; i++){
			if(adc.read()/100>i && adc.read()/100<i+2){
				board[i] = turn+1;
			}else{
				board[i] = 0;
			}
		}
}

void sets::mark() {
	if(overlap==0){
		for(unsigned int i=0; i<9; i++){
			if(adc.read()/100>i && adc.read()/100<i+2){
				if(sw1.read()==1){
					board[i] = turn+1;
					turn = !turn;
					while(sw1.read()==1);
					hwlib::wait_ms(50);
				}
			}
		}
	}
}

void sets::interact( map & other ) {
	if( this != & other){
        if( overlaps( other )){
    		overlap=1;
        }else{
        	overlap=0;
        }
    }
}

int sets::check( std::array< int , 9 > board ){
	if(
		(board[0] == board[1] && board[1] == board[2] && board[0]!=0)||
		(board[3] == board[4] && board[4] == board[5] && board[3]!=0)||
		(board[6] == board[7] && board[7] == board[8] && board[6]!=0)||

		(board[0] == board[3] && board[3] == board[6] && board[0]!=0)||
		(board[1] == board[4] && board[4] == board[7] && board[1]!=0)||
		(board[2] == board[5] && board[5] == board[8] && board[2]!=0)||

		(board[0] == board[4] && board[4] == board[8] && board[0]!=0)||
		(board[2] == board[4] && board[4] == board[6] && board[2]!=0)
		)
		{
		return !turn+1;
		}
	for( int p : board){
		if(p==0){
			return 0;
		}
	}
	return no_winner;
}

void sets::win(){
	int win=check(board);
	if(win>=1){
		for(unsigned int i=0; i<9; i++){
			board[i]=win;
		}
		for(unsigned int i=0; i<1000; i++){
			draw();
		}
		for(unsigned int i=0; i<9; i++){
			board[i]=0;
		}
	}
}

void map::color_write(const int i_red,const int i_blue,const int i_green){
	red.write(i_red);
	blue.write(i_blue);
	green.write(i_green);
}

void map::color_flush(){
	red.flush();
	blue.flush();
	green.flush();
}