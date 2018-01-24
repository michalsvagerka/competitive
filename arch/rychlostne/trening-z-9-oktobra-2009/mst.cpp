#include "../l/lib.h"
// #include "../l/mod.h"
#include "../l/util.h"

class mst {
public:
	void solve(istream& cin, ostream& cout) {
		int t = 1;
		while (true) {
			int N; cin >> N;
			if (N==0) break;
			vector2<int> E(N, N, 0);
			vector<pair<int,pii>> V;
			for (int i = 0; i < N-1; ++i) {
				for (int j = i+1; j < N; ++j) {
					int w; cin >> w;
					if (w) {E[i][j] = E[j][i] = w; V.push_back({w, {i,j}});}
				}
			}
			sort(V.begin(), V.end());
			UnionFind UF(N);
			int cost = 0;
			for(auto v:V) {
				if (UF.unite(v.y.x,v.y.y)) {
					cost += v.x;
				}
			}
			int Q; cin >> Q;
			string s;
			getline(cin, s);

			for (int q = 0; q < Q; ++q) {
				int test = 0;
				int n = 1;
				vector<int> V;

				getline(cin, s);
				stringstream ss(s);
				char c; int i;
				ss << noskipws; ss >> c >> i; --i;
				V.push_back(i);
				while (!V.empty()) {
					while (ss.peek() == ' ') ss >> c;
					if (ss.peek() == ')') { ss >> c; V.pop_back(); }
					else {
						bool st = (ss.peek() == '(');
						if (st) ss >> c;
						ss >> i;--i;++n;
						test += E[i][V.back()];
						if (st) V.push_back(i);
					}
				}
				cout << t << '.' << q+1 << '.' << ' ' << (n == N && cost == test ? "YES" : "NO") << '\n';
			}
			t++;
		}
	}
};
