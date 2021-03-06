#include <bits/stdc++.h>

using namespace std;
using ull = uint64_t;
using ll = int64_t;
using ld = long double;

typedef vector<int> vi;

// Segment Tree with methods to update a single element
class SegmentTree
{
private:
	vi st, A;
	int n;
	int left(int p)
	{
		return (p << 1);
	}
	int right(int p)
	{
		return (p << 1) + 1;
	}
	// Build the whole segment tree. Time complexity is O(n)
	void build(int p, int L, int R)
	{
		if (L == R)		// build leaf node
		{
			st[p] = A[L] ? (A[L] > 0 ? 1 : -1) : 0;
		}
		else			// build a parent node
		{
			build(left(p), L, (L + R) / 2);
			build(right(p), (L + R) / 2 + 1, R);
			int p1 = st[left(p)], p2 = st[right(p)];
			if (!p1 || !p2)
				st[p] = 0;
			else
				st[p] = (p1 == p2 ? 1 : -1);
		}
	}
	// Range Sign Query
	int rsq(int p, int L, int R, int i, int j)
	{
		if (i > R || j < L)		// out of range
			return -2;
		if (L >= i && R <= j)	// part of the query range
			return st[p];

		int p1 = rsq(left(p), L, (L + R) / 2, i, j);		// left part query
		int p2 = rsq(right(p), (L + R) / 2 + 1, R, i, j);	// right part query
		if (p1 == -2)			// left part is out of range
			return p2;
		if (p2 == -2)			// right part is out of range
			return p1;
		if (!p1 || !p2)
			return 0;
		else
			return (p1 == p2 ? 1 : -1);
	}
	// Update a element whose index is pos (0-based) from leaf to root
	void update(int p, int L, int R, int pos, int val)
	{
		if (L == R)			// leaf node
		{
			st[p] = (val == 0 ? 0 : (val > 0 ? 1 : -1));
			return;
		}
		if (pos <= (L + R) / 2)		// along left path
			update(left(p), L, (L + R) / 2, pos, val);
		else						// along right path
			update(right(p), (L + R) / 2 + 1, R, pos, val);
		st[p] = st[left(p)] * st[right(p)];
		return;
	}
public:
	SegmentTree(const vi& _A)
	{
		A = _A;
		n = _A.size();
		st.assign(4 * n, 0);
		build(1, 0, n - 1);
	}
	// Range Sign Query
	int rsq(int i, int j)
	{
		return rsq(1, 0, n - 1, i, j);	// query from the root of the segment tree
	}
	void update(int pos, int val)
	{
		update(1, 0, n - 1, pos, val);
		return;
	}
};

int main()
{
#ifdef FI
	freopen("input.txt", "r", stdin);
#endif
	int n, k;
	while (scanf("%d %d", &n, &k) != EOF)
	{
		vi a;
		while (n--)
		{
			int num;
			scanf("%d", &num);
			a.push_back(num);
		}
		getchar();
		SegmentTree seq(a);
		char cmd;
		int i, v;
		while (k--)
		{
			scanf("%c %d %d", &cmd, &i, &v);
			getchar();
			if (cmd == 'C')
				seq.update(i - 1, v);
			else
			{
				int ret = seq.rsq(i - 1, v - 1);
				printf("%s", ret == 0 ? "0" : (ret > 0 ? "+" : "-"));
			}
		}
		printf("\n");
	}
	return 0;
}
