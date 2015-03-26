#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define maxN 100005
#define	INF (1ull << 60)

int v, e;
vector<pair<int, int> >G[maxN];	
priority_queue<pair<long long, long long> >q; 	
long long d[maxN], p[maxN];

void printPath(int v)
{
	stack<int>s;
	while(v != -1)
	{
		s.push(v);
		v = p[v];
	}
	while(!s.empty())
	{
		cout << s.top() << (s.size() == 1 ? "" : " ");
		s.pop();
	}
}

int main()
{
	cin >> v >> e;
	for(int i = 0; i < e; i++)
	{
		int a, b, w;
		cin >> a >> b >> w;
		G[a].push_back(make_pair(w, b));
		G[b].push_back(make_pair(w, a));
	}

	for(int i = 1; i <= v; i++)
	{
		d[i] = INF;
		p[i] = -1;
	}
	d[1] = 0;
	q.push(make_pair(0, 1));

	while(!q.empty())
	{
		int dist = -q.top().first;
		int u = q.top().second;
		q.pop();

		if(dist <= d[u])
		{
			for(int i = 0; i < G[u].size(); i++)
			{
				int v = G[u][i].second;
				int w = G[u][i].first;
				
				if(d[u] + w < d[v])
				{
					d[v] = d[u] + w;
					p[v] = u;
					q.push(make_pair(-d[v], v));
				}
			}
		}
	}

	if(d[v] == INF)
		cout << -1;
	else
		printPath(v);
	cout << endl;

	return 0;
}
