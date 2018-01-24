#include "../l/lib.h"
// #include "../l/mod.h"

struct krab {
	int a,b,c,d,e;
};

typedef pair<pair<int,ll>,pair<int,string>> ord;

class tenistydar {
public:
	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		map<ll, krab> X;
		for (int i = 0; i < N; ++i) {
			int a,b,c; cin >> a >> b >> c;
			ll d = min(a,min(b,c));
			ll f = max(a,max(b,c));
			ll e = a+b+c-d-f;
			ll k = (1000000*d+e)*1000000+f;
			auto it = X.find(k);
			if (it == X.end()) {
				X[k] = {a,b,c,1,i};
			} else {
				X[k].d++;
			}
		}

		vector<ord> R;
		for (auto it = X.begin(); it != X.end(); ++it) {
			if (it->y.d > 1) {
				stringstream s;
				s << it->y.a << 'x' << it->y.b << 'x' << it->y.c << ' ' << it->y.d << '\n';
				ll vol = (ll)it->y.a * (ll) it->y.b * (ll)it->y.c;
				R.push_back({{-it->y.d, -vol}, {it->y.e, s.str()}});
			}
		}
		sort(R.begin(), R.end());

		for (auto r:R) {
			cout << r.y.y;
		}
	}
};
