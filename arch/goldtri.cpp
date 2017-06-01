#include "../l/lib.h"
// #include "../l/mod.h"

typedef pair<pii, int> pos;

class goldtri {
public:
	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		int C = 0;
		vector<pos> K;
		for (int i = 0; i < N; ++i) {
			int x, y;
			cin >> x >> y;
			if (y > 0) ++C;
			K.push_back({{x,y}, -1});
			K.push_back({{-x,-y}, 1});
		}

		sort(K.begin(), K.end(), [](const pos&p, const pos&q) {
			if (p.x.y > 0 && q.x.y <= 0) return true;
			if (p.x.y <= 0 && q.x)
		}

	}
};
