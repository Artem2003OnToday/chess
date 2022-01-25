#include "bot_.h"

figures::figures() {
	form = 0;
	color = empty;
}
figures field[size_y][size_x];

void figures::init(int color, int form) {
	this->color = color;
	this->form = form;
}

void figures::delete_() {
	form = 0;
	color = empty;
}

bool check_knight(int r1, int c1, int r2, int c2) {
	int dr = abs(r1 - r2), dc = abs(c1 - c2);
	return (dr && dc && dr + dc == 3) ? true : false;
}

bool can_motion(int r1, int c1, int r2, int c2) {
	switch (field[r1][c1].form) {
		case knight: {
			return check_knight(r1, c1, r2, c2);
			break;
		}
	}
}

void print_pair(pii a) {
	printf("{%i, %i} ", a.first, a.second);
}

pair<pii, pii> must_attack(int my_color) {
	vector<pair<pii, pii> > motion;

	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			if (field[i][j].color == my_color) {
				for (int next_i = 0; next_i < size_y; next_i++) {
					for (int next_j = 0; next_j < size_x; next_j++) {
						if (field[next_i][next_j].color != my_color && can_motion(i, j, next_i, next_j)) {
							motion.push_back({ {i, j}, {next_i, next_j} });
						}
					}
				}
			}
		}
	}

	printf("motion.size() = %i\n", motion.size());
	int index = motion.size() ? rand() % motion.size() : -1;
	if (motion.size()) {
		print_pair(motion[index].first);
		print_pair(motion[index].second);
		printf("\n");
	}

	return motion.size() ? motion[index] : empty_pair;
}

pair<pii, pii> other_motion(int my_color) {
	vector<pair<pii, pii> > motion;

	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			if (field[i][j].color == my_color) {
				for (int next_i = 0; next_i < size_y; next_i++) {
					for (int next_j = 0; next_j < size_x; next_j++) {
						//if(!field[next_i][next_j].form && can_motion(i, j, next_i, next_j)) {
						if(field[ next_i ][ next_j ].color != my_color && can_motion(i, j, next_i, next_j)) {
							printf("{%i, %i}, {%i, %i}\n", i, j, next_i, next_j);
							motion.push_back({ {i, j}, {next_i, next_j} });
						}
					}
				}
			}
		}
	}

	printf("other_motion.size() = %i\n", motion.size());
	int index = motion.size() ? rand() % motion.size() : -1;
	if (motion.size()) {
		print_pair(motion[index].first);
		print_pair(motion[index].second);
		printf("\n");
	}

	return motion.size() ? motion[ index ] : empty_pair;
}

string coord_to_string(pair<pii, pii> ty) {
	string ret = "";

	ret += (ty.first.second  + 'a');
	ret += (ty.first.first + 1 + '0');

	ret += ":";

	ret += (ty.second.second + 'a');
	ret += (ty.second.first + 1 + '0');

	ret += "\n";
	return ret;
}
