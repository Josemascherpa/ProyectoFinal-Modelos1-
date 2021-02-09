#include <iostream>
#include "Game.h"
#include <ctime>


using namespace std;

int main() {
	bool restart = false;
	
	do {
		Game G;

		G.Loop();

		if (G.restart()) {
			restart = true;
			
		}else {
			restart = false;
		}
	} while (restart == false);
	
	return 0;
}