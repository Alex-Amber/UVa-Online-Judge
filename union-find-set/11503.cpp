#include <bits/stdc++.h>

using namespace std;
using ull = uint64_t;
using ll = int64_t;
using ld = long double;

typedef vector<int> vi;

// Enhanced UnionFind class with methods to return the size of connected component and clear the set
class UnionFind
{
private:
	vi p, rank, size;
public:
	// Constructor
	UnionFind(int N)
	{
		p.assign(N, 0);
		rank.assign(N, 0);
		size.assign(N, 1);
		for (int i = 0; i != N; ++i)
			p[i] = i;
	}
	// Recursively find the SetId that a node belongs to with path compression
	int findSet(int i)
	{
		return p[i] == i ? i : (p[i] = findSet(p[i]));
	}
	// Determine whether two nodes belong to a same set
	bool isSameSet(int i, int j)
	{
		return findSet(i) == findSet(j);
	}
	// Return the size of a connected component that a node belongs to
	int findSetSize(int i)
	{
		return size[findSet(i)];
	}
	// Unite two sets
	void unionSet(int i, int j)
	{
		if (!isSameSet(i, j))
		{
			int x = findSet(i);
			int y = findSet(j);
			if (rank[x] > rank[y])
			{
				p[y] = x;
				size[x] += size[y];
			}
			else
			{
				p[x] = y;
				size[y] += size[x];
				if (rank[x] == rank[y])
					++rank[y];
			}
		}
		return;
	}
	// Reset the set to where all nodes are isolated
	void clearSet()
	{
		int N = p.size();
		for (int i = 0; i != N; ++i)
		{
			p[i] = i;
			rank[i] = 0;
			size[i] = 1;
		}
		return;
	}
};

const int maxn = 200000 + 50;
UnionFind VFnetwork(maxn);
map<string, int> records;
int id = 0;

// assign Id to a new appeared node if needed, and return its Id
int getId(string s)
{
	if (!records.count(s))
		records[s] = ++id;
	return records[s];
}

int main()
{
#ifdef FI
	freopen("input.txt", "r", stdin);
#endif
	int n;
	scanf("%d", &n);
	while (n--)
	{
		VFnetwork.clearSet();
		records.clear();
		id = 0;
		int f;
		scanf("%d", &f);
		getchar();
		while (f--)
		{
			string f1, f2;
			cin >> f1 >> f2;
			VFnetwork.unionSet(getId(f1), getId(f2));
			printf("%d\n", VFnetwork.findSetSize(getId(f1)));
		}
	}
	return 0;
}
