#include <iostream>
using namespace std;

const int N = 105;
int max_x, max_y;
int tree[N][N];

void update(int x, int y, int val)
{
	for(int i = x; i <= max_x; i += i & (-i))
		for(int j = y; j <= max_y; j += j & (-j))
			tree[i][j] += val;
}

int get(int x, int y)
{
	int res = 0;
	for(int i = x; i > 0; i -= i & (-i))
		for(int j = y; j > 0; j -= j & (-j))
			res += tree[i][j];
	return res;
}

int rsq(int x1, int y1, int x2, int y2)
{
	return get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1 - 1, y1 - 1);
}

int main() 
{
	max_x = max_y = 4;
	update(1, 1, 1);
	cout << rsq(1, 1, 4, 4) << endl;
	update(3, 3, 12);
	cout << rsq(3, 3, 3, 3) << endl;
	cout << rsq(3, 3, 4, 4) << endl;
	cout << rsq(1, 1, 3, 3) << endl;
	return 0;
}
