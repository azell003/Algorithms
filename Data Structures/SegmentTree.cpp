#include <iostream>
using namespace std;

const int N = 10000;

int n;
int tree[4 * N]; // indexed starting at 1

// Segment tree for RSQ (easily modified for anything else)

void buildst(int a[], int vertex = 0, int L = 0, int R = n - 1)
{
	if(L == R)
		tree[vertex] = a[L];
	else
	{
		int mid = (L + R) >> 1;
		
		buildst(a, 2 * vertex + 1, L, mid);
		buildst(a, 2 * vertex + 2, mid + 1, R);
		
		tree[vertex] = tree[2 * vertex + 1] + tree[2 * vertex + 2];
	}
}

void update(int i, int val, int vertex = 0, int L = 0, int R = n - 1)
{
	if(L == R)
		tree[vertex] = val; 
	else
	{
		int mid = (L + R) >> 1;
		
		if(i <= mid)
			update(i, val, 2 * vertex + 1, L, mid);
		else
			update(i, val, 2 * vertex + 2, mid, R);
		
		tree[vertex] = tree[2 * vertex + 1] + tree[2 * vertex + 2];
	}
}


int getrsq(int ql, int qr, int vertex = 0, int L = 0, int R = n - 1)
{
	if(ql == L && qr == R)
		return tree[vertex];
	else
	{
		int mid = (L + R) >> 1;
		int sum = 0;
		
		if(ql <= mid)
			sum += getrsq(ql, min(mid, qr), 2 * vertex + 1, L, mid);
		if(mid + 1 <= qr)
			sum += getrsq(max(mid + 1, ql), qr, 2 * vertex + 2, mid + 1, R);
		return sum;
	}
}

int main() 
{
	n = 5;
	int a[] = {1, 2, 3, 4, 5};
	buildst(a);
	cout << getrsq(0, n - 1) << endl;
	return 0;
}
