#include "../l/lib.h"
// #include "../l/mod.h"

class princess {
public:
    void solve(istream& cin, ostream& cout) {
		int N, K; cin >> N >> K;
		string S; cin >> S;
		unordered_map<int, set<int>> A,D;
		int X=0,Y=0;
		for (int i = 0; i < N; ++i) {
			int x,y; cin >> x >> y; if (i==0) {X=x; Y=y;}
			A[x+y].insert(x);
			D[x-y].insert(x);
		}

		set<int> *d = &D[X-Y];
		set<int> *a = &A[X+Y];

		for (char s:S) {
			int px=X, py=Y;
			if (s=='A') {
				if (!d) d = &D[X-Y];
				auto it = d->lower_bound(X);
				if (++it != d->end())  { Y = *it+Y-X; X=*it; a=nullptr;}
			} else if (s == 'B') {
				if (!a) a = &A[X+Y];
				auto it = a->lower_bound(X);
				if (++it != a->end())  { Y = X+Y-*it; X=*it; d=nullptr;}
			} else if (s == 'C') {
				if (!a) a = &A[X+Y];
				auto it = a->lower_bound(X);
				if (it != a->begin())  { --it; Y = X+Y-*it; X=*it; d=nullptr;}
			} else {
				if (!d) d = &D[X-Y];
				auto it = d->lower_bound(X);
				if (it != d->begin())  { --it; Y = *it+Y-X; X=*it; a=nullptr;}
			}
			if (px != X) {
				A[px+py].erase(px);
				D[px-py].erase(px);
			}
		}
		cout << X << ' ' << Y << endl;
    }
};
