#include <bits/stdc++.h>

using namespace std;
using ull = uint64_t;
using ll = int64_t;
using ld = long double;

int main()
{
#ifdef FI
	freopen("input.txt", "r", stdin);
#endif
	int N, caseNo = 0;
	while (scanf("%d", &N) && N)
	{
		++caseNo;
		printf("%s", caseNo == 1 ? "" : "\n");
		bool solved = false;
		// Enumerate all possible values for fghij
		for (int fghij = 1234; fghij <= 98765 / N; ++fghij)
		{
			int abcde = fghij * N;
			int tmp;
			int used = (fghij < 10000);
			// Check whether abcde and fghij use all digits from 0 through 9
			tmp = abcde;
			while (tmp)
			{
				used |= 1 << (tmp % 10);
				tmp /= 10;
			}
			tmp = fghij;
			while (tmp)
			{
				used |= 1 << (tmp % 10);
				tmp /= 10;
			}
			if (used == (1 << 10) - 1)
			{
				printf("%0.5d / %0.5d = %d\n", abcde, fghij, N);
				solved = true;
			}
		}
		if (!solved)
			printf("There are no solutions for %d.\n", N);
	}
	return 0;
}

