#include "../l/lib.h"
// #include "../l/mod.h"

class jednotky {
public:
	int solve(int N) {
		int M = 2000000;
		vector<bool> U(M+1, false);
		int c = 0, d = 0;
		vector<vector<int>> V;
		int i = 1;
		while(true) {
			V.push_back({});
			if (i == N) return i;
			if (!U[i]) { V[i-1].push_back(i); U[i] = true; ++c; }
			for (int j = 1; j < i; ++j) {
				for (int v:V[j-1])
					for (int w:V[i - j-1]) {
						if (v+w == N || (ll)v*w == N) return i;
						if (v + w <= M && !U[v + w]) {
							V[i-1].push_back(v + w);
							U[v + w] = true;
						}
						if ((ll)v * w <= M && !U[v * w]) {
							V[i-1].push_back(v * w);
							U[v * w] = true;
						}
					}
			}
			++i;
		}
	}

    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;


		cout << solve(N) << endl;
    }
};
