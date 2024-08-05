#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;

	ifstream rdr("Text.txt");

int main() {
	grid prison;
	int jail[maxr][maxc];
	int r, c;

	prison.readjail(jail, r, c);
	prison.display_grid(jail, r, c);

	position prisoner;
	cout << endl;

	prison.find_prisoner(r,c,jail,prisoner);
	prison.display_prisoner(jail, prisoner);
	cout << endl<<endl;
	
	position first;
	prison.first_one(first,jail,r,c);
	prison.first_one_display(first);
	cout << endl;

	position last;
	prison.last_one(last, jail, r, c);
	prison.last_one_display(last);
	cout << endl;

	cout << prison.final_condition(jail, r, c, first, last) << endl;
	cout << endl;

	prison.prisoner_output(last, first, prisoner, jail, r, c);

	cout << endl;
	
	cout << "--------------------------" << endl << endl;

	prison.final_floodfill(prisoner,jail,r,c);
	cout << endl;
	prison.display_grid(jail, r, c);


	return 0;
}