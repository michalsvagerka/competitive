#include "../l/lib.h"
#include "../l/avl.h"

class inner {
public:
    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		map<int,pii> XR, YR;
		for (int i = 0; i < N; ++i) {
			int x,y; cin >> x >> y;
			auto it = XR.find(y);
			if (it!=XR.end()) { it->y.x = min(it->y.x, x); it->y.y = max(it->y.y, x); }
			else XR[y] = {x,x};
			it = YR.find(x);
			if (it!=YR.end()) { it->y.x = min(it->y.x, y); it->y.y = max(it->y.y, y); }
			else YR[x] = {y,y};
		}
		vector<pair<pii, pii>> E;
		for (auto it=XR.begin(); it!=XR.end();++it) {
			E.push_back({{it->y.x, -1}, {it->x,0}});
			E.push_back({{it->y.y, 1}, {it->x,0}});
		}
		for (auto it=YR.begin(); it!=YR.end();++it) {
			E.push_back({{it->x, 0}, it->y});
		}

		avl<int,int> T;
		sort(E.begin(), E.end());
		ll ans = 0;
		for(auto&e:E) {
			switch (e.x.y) {
				case -1:
					T.insert(e.y.x, 0);
					break;
				case 0:
					ans += T.smaller(e.y.y+1) - T.smaller(e.y.x);
					break;
				case 1:
					T.remove(e.y.x);
					break;
			}

		}
		cout << ans << endl;
    }
};
