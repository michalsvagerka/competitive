#include "../l/lib.h"
// #include "../l/mod.h"

class ohrad {
public:
    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		vector<pii> P(N); cin >> P;
		sort(P.begin(), P.end());
		set<int> A,B,C,D;
		for (pii&p: P) {
			A.insert(p.x + p.y);
			B.insert(p.x - p.y);
			C.insert(p.y);
			D.insert(p.x);
		}
		

		int minX = *D.begin() - 1;
		int maxX = *D.rbegin() + 1;
		int minY = *C.begin() - 1;
		int maxY = *C.rbegin() + 1;
		int minXY = *A.begin() - 1;
		int maxXY = *A.rbegin() + 1;
		int minYX = *B.begin() - 1;
		int maxYX = *B.rbegin() + 1;

		double ans = 2 * (maxX - minX + maxY - minY);
		ans += (maxX + maxY - maxXY + minXY - minX - minY + maxX - minY + minYX - minX + maxY - maxYX) * (sqrt(2) - 2);

		cout << fixed << setprecision(10)  << ans << endl;

    }
};
