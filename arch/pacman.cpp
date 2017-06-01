#include "../l/lib.h"
// #include "../l/mod.h"

class pacman {
public:
	vector<vector<int>> E;
	int N,T;
	int C, D, L;
	vector<int> P, Ans;

	pii dfs(int u, int v, int d) {
		pii ans = {d, u};
		for (int w:E[u]) if (v!=w) ans = max(ans, dfs(w,u, d+1));
		return ans;
	}

	bool path(int u, int v, int w, vector<int> &p) {
		if (v == u) { p.push_back(u); return true; }
		for (int x:E[u]) if (w!=x && path(x, v, u, p)) {
				p.push_back(u);
				return true;
			}

		return false;
	}

	bool dfs2(int u, int v) {
		if (T < L + 2) return false;
		++D;
		T -= 2;
		Ans.push_back(u+1);
		for (int w: E[u]) {
			if (w != v && dfs2(w, u)) Ans.push_back(u+1);
		}
		return true;
	}


    void solve(istream& cin, ostream& cout) {
		cin >> N >> T; E.resize(N);
		for (int i = 0; i < N - 1; ++i) {
			int u,v; cin >> u >> v; --u; --v;
			E[u].push_back(v); E[v].push_back(u);
		}
		pii f = dfs(0, -1, 0);
		pii g = dfs(f.y, -1, 0);
		path(f.y, g.y, -1, P);
		C = 0; D = 0;
		L = P.size()-1;
		for (int i = 0; i < P.size(); ++i) {
			Ans.push_back(P[i]+1);
			++C;
			if (T == 0) break;
			--T;
			--L;
			if (i != 0 && i != P.size()-1) {
				for (int v:E[P[i]]) {
					if (P[i-1]!=v && P[i+1]!=v) {
						if (dfs2(v, P[i])) Ans.push_back(P[i]+1);
					}
				}
			}
		}

		cout << C + D << endl;
		cout << Ans.size()-1 << endl;
		cout << Ans;
    }
};
