#include <bits/stdc++.h>

using namespace std;
using ull = uint64_t;
using ll = int64_t;
using ld = long double;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

const int maxn = 200 + 5;
int n;
vi g[maxn];		// graph represented in adjacent list

// Tweak of BFS to check whether a graph is bipartite
bool bipartite(int s)
{
	queue<int> q;
	q.push(s);
	vi color(n, INT_MAX);	// array to record the color for each node
	color[s] = 0;
	bool isBipartite = true;
	while (!q.empty() && isBipartite)
	{
		int u = q.front();
		q.pop();
		int num_adj = (int) g[u].size();
		// Color all adjacent nodes with different color
		for (int i = 0; i != num_adj; ++i)
		{
			int v = g[u][i];
			if (color[v] == INT_MAX)	// not colored
			{
				color[v] = !color[u];
				q.push(v);
			}
			else if (color[v] == color[u])	// adjacent nodes have the same color
			{
				isBipartite = false;
				break;
			}
		}
	}
	return isBipartite;
}

int main()
{
#ifdef FI
	freopen("input.txt", "r", stdin);
#endif
	while (scanf("%d", &n) && n)
	{
		for (int i = 0; i != n; ++i)	// clear the graph
			g[i].clear();
		int l;
		scanf("%d", &l);
		for (int i = 0; i != l; ++i)
		{
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		printf("%s\n", bipartite(0) ? "BICOLORABLE." : "NOT BICOLORABLE.");
	}
	return 0;
}
