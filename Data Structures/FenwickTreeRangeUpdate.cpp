#include <iostream>
using namespace std;

const int N = 1e7 + 1;

long long n, treeM[N], treeA[N];

void internalUpdate(int idx, long long m, long long a)
{
	while(idx <= n)
	{
		treeM[idx] += m;
		treeA[idx] += a;
		idx += idx &(-idx);
	}
}

void update(int left, int right, long long val)
{
	internalUpdate(left, val, -val * (left - 1));
	internalUpdate(right, -val, val * right);
}

long long get(int idx)
{
	long long m = 0;
	long long a = 0;
	int start = idx;
	while(idx > 0)
	{
		m += treeM[idx];
		a += treeA[idx];
		idx -= idx & (-idx);
	}
	return m * start + a;
}

long long rsq(int a, int b)
{
	return get(b) - get(a - 1);
}

int main() 
{
	n = 5;
	update(1, 1, 1);
	update(2, 2, 2);
	update(3, 3, 3);
	cout << rsq(1, 3) << endl;
	return 0;
}