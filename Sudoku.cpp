#include <bits/stdc++.h>
#define SIZE 9
using namespace std;

int matrix[9][9];

set<int> rows[9], cols[9], grid[9];
vector< pair<int, int> > empty_slots;

int main()
{
	// take input
	for(int i = 0; i < SIZE ; ++i) {
		for(int j = 0; j < SIZE ; ++j) {
			cin>>matrix[i][j];
			if(matrix[i][j] == '*')
				empty_slots.push_back({i,j});
		}
	}

	// initialize rows, cols and grid sets
	for(int i = 0; i < SIZE ; ++i) {
		for(int j = 0; j < SIZE ; ++j) {

			if(matrix[i][j] == '*')
				continue;

			rows[i].insert(matrix[i][j]);
			cols[j].insert(matrix[i][j]);

			int x = i/3, y = j/3;
			grid[x*3 + j].insert(matrix[i][j]);
		}
	}

	


	return 0;
}