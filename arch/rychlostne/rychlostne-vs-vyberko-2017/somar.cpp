#include "../l/lib.h"
#include "../l/avl.h"

struct Rect {
	int x,h,i;
};

class somar {
public:

	vector<int> calc(vector<Rect> &R, int V) {
		sort(R.begin(), R.end(), [](const Rect&r, const Rect&s) { return r.x < s.x; });
		vector<int> A(R.size(),0);
		avl<int, int> T;
		for (Rect &r: R) {
			// cerr << r.h << ' ' << V - r.h + 1 << endl;
			A[r.i] = T.size() - T.smaller(V - r.h + 1);
			T.insert(r.h, 1);
		}
		return A;
	}

    void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			int N,V; cin >> N >> V;

			vector<Rect> R(N);
			for (int i = 0; i < N; ++i) {
				int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
				R[i] = {min(x1,x2), abs(y1-y2), i};
			}
			vector<int> X = calc(R, V);
			for (int i = 0; i < N; ++i) {
				int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
				R[i] = {min(x1,x2), abs(y1-y2), i};
			}
			vector<int> Y = calc(R, V);
			// cerr << X << Y;
			if (X==Y) cout << "ANO\n"; else cout << "NIE\n";
		}

    }
};
