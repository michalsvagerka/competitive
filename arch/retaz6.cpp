#include "../l/lib.h"
// #include "../l/mod.h"

class retaz6 {
public:
    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		vector<int> E;
		vector<pii> R;
		vector<vector<pii>> A;
		for (int i = 0; i < N; ++i) {
			int u,v; cin >> u >> v;
			if (u==v) E.push_back(u);
			else R.push_back({v,-u});
		}
		sort(R.begin(), R.end());
		set<pair<pii, int>> Q;
		for (pii r: R) {
			int x = -r.y;
			int y = r.x;
			auto it = Q.upper_bound({{x,-y}, N});
			if (it != Q.end()) {
				int i = it->y;
				A[i].push_back({x,y});
				Q.erase(it);
				Q.insert({{x,-y}, i});
			} else if (!E.empty()) {
				int r = E.back();
				E.pop_back();
				A.push_back({{r,r}, {x,y}});
				Q.insert({{x,-y}, A.size()-1});
			} else {
				A.push_back({{x,y}});
				Q.insert({{x,-y}, A.size()-1});
			}
		}

		for (int e:E) {
			A.push_back({{e,e}});
		}

		cout << A.size() << '\n';
		for (auto &a:A) {
			for (int i = 0; i < a.size(); ++i) {
				cout << '[' << a[i].x << ',' << a[i].y << ')' << " \n"[i==a.size()-1];
			}
		}
    }
};
