#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstdio>

using namespace std;

typedef pair<int, int> pii;
#define empty_pair make_pair(make_pair(-1, -1), make_pair(-1, -1)) 

#define size_y	8
#define size_x	8

#define empty	-1
#define pawn	1
#define knight	2
#define rook	3
#define bishop	4
#define queen	5
#define king	6

#define white		0
#define black		1

class figures {
	public:
		int color, form;

		figures();
		void init(int color, int form);
		void delete_();
};
extern figures field[size_y][size_x];

bool can_motion(int r1, int c1, int r2, int c2);
bool check_knight(int r1, int c1, int r2, int c2);

pair<pii, pii> must_attack(int my_color);
pair<pii, pii> other_motion(int my_color);

string coord_to_string(pair<pii, pii> ty);

void print_pair(pii a);
