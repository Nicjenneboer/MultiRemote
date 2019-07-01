#include "hwlib.hpp"
#include "game.hpp"
extern "C" void __cxa_pure_virtual() { while (1); }
int main( void ){

	pot turn;
	sets board;

	std::array< map *, 2 > game = {&turn, &board}; 

	for(;;){
		for( auto p : game){
			p->mark();
			
		}
		for( auto p : game){
			p->draw();
		}
		for( auto & p : game ){
        	for( auto & other : game ){
        		p->interact( *other );
         	} 
      	}
      	for( auto p : game){
			p->win();
		}
	}

}
