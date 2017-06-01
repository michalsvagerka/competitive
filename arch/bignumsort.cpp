#include "../l/lib.h"
// #include "../l/mod.h"

class bignumsort {
public:
	bignumsort() {
		LN = vector<double>{0};
		V.resize(31);
		for (int i : {2,3,5,6,7,10,11,12,13,14,15,17,18,19,20,21,22,23,24,26,27,28,29,30}) {
			V[i] = {1, LN.size()};
			LN.push_back(log(i));
		}
		V[1] = {0, 0};
		V[4] = {2, V[2].y};
		V[8] = {3, V[2].y};
		V[9] = {2, V[3].y};
		V[16] = {4, V[2].y};
		V[25] = {2, V[5].y};
	}

	static bool iseq(pii a, pii b, int fa = 1, int fb = 1) {
		return V[a.x].y == V[b.x].y && V[a.x].x * a.y == V[b.x].x * b.y;
	}

	static bool iseq(pair<int,pii> a, pair<int,pii> b) {
		return V[a.x].y == V[b.x].y && V[a.x].x * a.y == V[b.x].x * b.y;
	}

	static bool islt(pii a, pii b) {
		if (V[a.x].y == V[b.x].y) {
			return V[a.x].x * a.y < V[b.x].x * b.y || (V[a.x].x * a.y == V[b.x].x * b.y && a.x < b.x);
		} else {
			return V[a.x].x * a.y * LN[V[a.x].y] < V[b.x].x * b.y * LN[V[b.x].y];
		}
	}

	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		vector<pii> P;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				P.push_back({i,j});
			}
		}
		sort(P.begin(), P.end(), islt);
		pii l = {0,0};
		for (pii&p: P) {
			cout << (iseq(l, p) ? '=' : '<') << ' ' << p.x << '^' << p.y << endl;
			l = p;
		}
	}

	static vector<double> LN;
	static vector<pii> V;

};

vector<double> bignumsort::LN;
vector<pii> bignumsort::V;

