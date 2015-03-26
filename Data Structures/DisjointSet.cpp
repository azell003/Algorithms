#include <iostream>
using namespace std;

long long n;
int p[100005], s[100005];

// Path Compression
int getp(int x)
{
	return (p[x] == x ? x : p[x] = getp(p[x]));
}

// Union by size
void join(int x, int y)
{
	int a = getp(x);
	int b = getp(y);
	if(a != b)
	{
		if(s[a] > s[b])
		{
			p[b] = a;
			s[a] += s[b];
		}
		else
		{
			p[a] = b;
			s[b] += s[a];
		}
	}
}

// Initialize all nodes
int main() 
{
	cin >> n;
	
	for(int i = 0; i < n; i++) 
	{
		p[i] = i;
		s[i] = 1;
	}
	
	return 0;
}
