#pragma once
#include <iostream>
#include <fstream>
using namespace std;

const int maxr = 40, maxc = 80;

class position
{
	public:
	int r;
	int c;
};


class grid
{
public:
	grid();
	void readjail(int jail[][maxc], int& r, int& c);
	void display_grid(int jail[][maxc], int r, int c);
	void display_prisoner(int jail[][maxc], position& prisoner);
	void find_prisoner(int r, int c, int jail[][maxc], position& prisoner);
	void first_one(position& pos, int jail[][maxc], int r, int c);
	void first_one_display(position& pos);
	void last_one(position& pos, int jail[][maxc], int r, int c);
	void last_one_display(position& pos);
	bool condition_for_prisoner(position last, position first, position prisoner);
	bool final_condition(int jail[][maxc], int r, int c, position first, position last);
	void prisoner_output(position last, position first, position prisoner, int jail[][maxc], int r, int c);
	bool isValid(int r, int c, int rows, int cols, int jail[][maxc]);
	int final_floodfill(position prisoner, int jail[][maxc], int r, int c);



private:

};

grid::grid()
{
}


void grid::readjail(int jail[][maxc], int& r, int& c)
{
	ifstream rdr("Text.txt");

	rdr >> r;
	rdr >> c;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++) {
			rdr >> jail[i][j];
		}
	}
}


void grid::display_grid(int jail[][maxc], int r, int c) {

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++) {
			cout << jail[i][j] << " ";
		}
		cout << endl;
	}
}


void grid::find_prisoner(int r, int c, int jail[][maxc], position& prisoner) {
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++) {
			if (jail[i][j] == 2)
			{
				prisoner.r = i;
				prisoner.c = j;
			}
		}
	}
}


void grid::display_prisoner(int jail[][maxc], position& prisoner) {
	cout << "The location of prisoner is " << prisoner.r + 1 << " row and " << prisoner.c + 1 << " column " << endl;
}


void grid::first_one(position& pos, int jail[][maxc], int r, int c) {
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++) {
			if (jail[i][j] == 1)
			{
				pos.r = i;
				pos.c = j;
				return;
			}
		}
	}
}



void grid::first_one_display(position& pos) {
	cout << "the first one is " << pos.r + 1 << " row and " << pos.c + 1 << " column" << endl;
}


void grid::last_one(position& pos, int jail[][maxc], int r, int c) {
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++) {
			if (jail[i][j] == 1)
			{
				pos.r = i;
				pos.c = j;

			}
		}

	}
}



void grid::last_one_display(position& pos) {
	cout << "the last one is " << pos.r + 1 << " row and " << pos.c + 1 << " column" << endl;
}


bool grid::condition_for_prisoner(position last, position first, position prisoner) {

	if (first.r<prisoner.r && last.r>prisoner.r)
	{
		return true;
	}
	else {
		return false;
	}
}

bool grid::final_condition(int jail[][maxc], int r, int c, position first, position last) {

	bool escape;
	for (int j = first.c; j < last.c; j++) {
		if (jail[first.r][j] != 1 || jail[last.r][j] != 1 )
		{
			return escape = true;
		}

		if (jail[j][first.c] != 1 || jail[j][last.c] != 1) {
			return escape = true;
		}

		else {
			escape = false;
		}
	}

	return escape;
}



void grid::prisoner_output(position last, position first, position prisoner, int jail[][maxc], int r, int c) {

	if (condition_for_prisoner(last, first, prisoner) && final_condition(jail, r, c, first, last))
	{
		cout << endl << "the prisoner can escape" << endl;
	}
	else {
		cout << endl << "the prisoner can't escape" << endl;
	}
}



bool grid::isValid(int r, int c, int rows, int cols, int jail[][maxc]) {
	return (r >= 0 && r < rows && c >= 0 && c < cols && jail[r][c] == 0);
}


int grid::final_floodfill(position prisoner, int jail[][maxc], int rows, int cols) {
	bool canEscape = false;
	bool escaped = false;

	while (true) {
		canEscape = false;

		int nextR = prisoner.r;
		int nextC = prisoner.c;

		if (isValid(prisoner.r, prisoner.c + 1, rows, cols, jail)) {
			nextR = prisoner.r;
			nextC = prisoner.c + 1;
			canEscape = true;
			jail[prisoner.r][prisoner.c] = 2;
		}

		if (isValid(prisoner.r, prisoner.c - 1, rows, cols, jail) &&
			(nextR != prisoner.r || nextC != prisoner.c - 1)) {
			nextR = prisoner.r;
			nextC = prisoner.c - 1;
			canEscape = true;
			jail[prisoner.r][prisoner.c] = 2;
		}

		if (isValid(prisoner.r + 1, prisoner.c, rows, cols, jail) &&
			(nextR != prisoner.r + 1 || nextC != prisoner.c)) {
			nextR = prisoner.r + 1;
			nextC = prisoner.c;
			canEscape = true;
			jail[prisoner.r][prisoner.c] = 2;
		}

		if (isValid(prisoner.r - 1, prisoner.c, rows, cols, jail) &&
			(nextR != prisoner.r - 1 || nextC != prisoner.c)) {
			nextR = prisoner.r - 1;
			nextC = prisoner.c;
			canEscape = true;
			jail[prisoner.r][prisoner.c] = 2;
		}

		if (canEscape) {
			prisoner.r = nextR;
			prisoner.c = nextC;
			jail[prisoner.r][prisoner.c] = 2;

			cout << "(" << prisoner.r + 1 << ", " << prisoner.c + 1 << ")" << " , ";
		}


		if (!canEscape) {
			break;
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) {

			if (jail[0][j] == 2 || jail[9][j] == 2 || jail[i][0] == 2 || jail[i][9] == 2)
			{
				cout << endl << endl << "The prisoner have escaped...." << endl;
				return 0;
			}

		}
	}

	cout << endl << endl << "The prisoner can not escape...." << endl;
}


