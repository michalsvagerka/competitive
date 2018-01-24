#include "../l/lib.h"
// #include "../l/mod.h"

class warehouse {
public:
	int N;
	vector<bool> W;
	vector<vector<int>> E;
	vector<vector<int>> V;

	int dfs(int u, int ig) {
		int ans = W[u] ? 0 : -N;
		for (int v:E[u]) {
			if (v!=ig) {
				int x = dfs(v, u)+1;
				ans = max(ans, x);
				V[u].push_back(x);
			}
		}
		return ans;
	}

	int dfs2(int u, int ig, int w) {
		int M = V[u].size();
		vector<int> P(M+1, -N), S(M+1, -N);
		for (int i = 0; i < M; ++i) {
			P[i+1] = max(P[i], V[u][i]);
			S[M-i-1] = max(S[M-i], V[u][M-i-1]);
		}

		if (W[u]) w = max(w, 0);
		int ans = max(P[M], w);
		int i = 0;
		for (int v:E[u]) {
			if (v!=ig) {
				int g = max(P[i], S[i+1]);
				++i;
				ans = min(ans, dfs2(v, u, max(g,w)+1));
			}
		}
		return ans;
	}

    void solve(istream& cin, ostream& cout) {
		W.resize(N=$);
		E.clear();
		E.resize(N);
		V.clear();
		V.resize(N);

		for (int i = 0; i < N; ++i) {
			if ((int)$) W[i] = true;
		}
		for (int i = 0; i < N - 1; ++i) {
			int u=$,v=$;--u;--v;
			E[u].push_back(v);
			E[v].push_back(u);
		}

		dfs(0, -1);
		cout << dfs2(0, -1, -N) << endl;
    }
};
