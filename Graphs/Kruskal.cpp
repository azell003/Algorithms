#include <iostream>
#include <algorithm>

const int N = 1000000;

int p[N];
pair<int, pair<int, int> >edgeList[N];

int getp(int i)
{
	return (p[i] == p[p[i]] ? p[i] : p[i] = getp(p[i]));
}

int main()
{
	int e, v, ans = 0;
	scanf("%d%d", &v, &e);
	for(int i = 0; i < e; i++)
		scanf("%d%d%d", &edgeList[i].second.first, &edgeList[i].second.second, &edgeList[i].first);

	sort(edgeList, edgeList + e);

	for(int i = 0; i < v; i++)
		p[i] = i;

	for(int i = 0; i < e; i++)
	{
		int a = getp(edgeList[i].second.first);
		int b = getp(edgeList[i].second.second);
		if(a != b)
		{
			p[b] = a;
			ans += edgeList[i].first;
		}
	}

	cout << ans << endl;
}
