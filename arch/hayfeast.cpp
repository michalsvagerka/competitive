#include "../l/lib.h"
// #include "../l/mod.h"

class hayfeast {
public:
	int N;
	vector<pii> C, A, B;

	ll penalty(const vector<pii> &R) {
		auto W=R; sort(W.begin(), W.end(), [](const pii&a, const pii&b){ return (ll)a.x*b.y < (ll)b.x*a.y; });
		ll ans = 0; int t = 0;
		for (pii w:W) { ans += (ll)w.y * t; t += w.x; }
		return ans;
	}

	ll min_penalty(int i) {
		if (i==N) {
			return penalty(A) + penalty(B);
		}

		A.push_back(C[i]);
		ll ans = min_penalty(i+1);
		A.pop_back();
		B.push_back(C[i]);
		ans = min(min_penalty(i+1), ans);
		B.pop_back();
		return ans;
	}

    void solve(istream& cin, ostream& cout) {
		cin >> N;
		C.resize(N);
		for (int i = 0; i < N; ++i) {
			cin >> C[i].x >> C[i].y;
		}

		A.push_back(C[0]);
		cout << min_penalty(1) << endl;
    }
};
