#include "../l/lib.h"
// #include "../l/mod.h"

class jetoftak {
public:
	vector<pii> NF;

	bool jeftak(int a1, int a2, int b1, int b2, int a, int b) {
		return a1 <= a && a <= a2 && b1 <= b && b <= b2;
	}

	bool nejniftak(int a1, int a2, int b1, int b2) {
		for (const pii&nf: NF) {
			if (jeftak(a1, a2, b1, b2, nf.x, nf.y)) return true;
		}
		return false;
	}



	void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			int N; cin >> N;
			NF.clear();
			int a,b; string s,q;
			int a1=10000000, a2=0, b1=100000000, b2=0;

			for (int i = 0; i < N; ++i) {
				cin >> a >> b >> s >> q;
				if (s == "JE") {
					a1 = min(a1, a);
					a2 = max(a2, a);
					b1 = min(b1, b);
					b2 = max(b2, b);
				} else {
					NF.push_back({a,b});
				}
			}

			int M; cin >> M;
			cout << "Case #" << t+1 << ":\n";
			for (int i = 0; i < M; ++i) {
				cin >> a >> b;
				if (jeftak(a1, a2, b1, b2, a, b)) {
					cout << "JE FTAK\n";
				} else if (nejniftak(min(a1,a), max(a2,a), min(b1,b), max(b2,b))) {
					cout << "NEJNI FTAK\n";
				} else {
					cout << "ANI SRNKA NETUSI\n";
				}
			}

		}
	}
};
