#include "../l/lib.h"
// #include "../l/mod.h"

class romansort {
public:

	string torom(int n) {
		stringstream s;
		while (n >= 1000) { n-=1000; s << "M"; }
		if (n >= 900) { n-= 900; s << "CM"; }
		if (n >= 500) { n-= 500; s << "D"; }
		if (n >= 400) { n-= 400; s << "CD"; }
		while (n >= 100) { n-= 100; s << "C"; }
		if (n >= 90) { n-= 90; s << "XC"; }
		if (n >= 50) { n-= 50; s << "L"; }
		if (n >= 40) { n-= 40; s << "XL"; }
		while (n >= 10) { n-= 10; s << "X"; }
		if (n >= 9) { n-= 9; s << "IX"; }
		if (n >= 5) { n-= 5; s << "V"; }
		if (n >= 4) { n-= 4; s << "IV"; }
		while (n >= 1) { n-= 1; s << "I"; }
		return s.str();
	}


	ll slow(ll N, ll P) {
		if (O.size() != N) {
			O.resize(N);
			for (int i = 0; i < N; ++i) {
				O[i] = {torom(i + 1), i + 1};
			}
			sort(O.begin(), O.end());
		}
		return O[P-1].y;
	}

	ll fast(ll N, ll P) {
			ll th = P / 946LL;
			ll TH = N / 1000LL;
			ll AF = int(N % 1000LL);
			if (th < TH) {
				if (P % 946 == 0) {
					return th * 1000LL;
				} else {
					return th * 1000LL + R[P % 946LL - 1].y;
				}
			} else if (P <= TH*946LL + AF) {
				int paf = P - TH*946LL;
				if (paf == 0) {
					return TH * 1000LL;
				}
				for (int i = 0; i < 1000; ++i) {
					if (R[i].y <= AF) {
						if (!--paf) { return TH*1000LL + R[i].y; };
					}
				}
				return -1;
			} else {
				P = N - P;
				return (ll)(P / 54) * 1000LL + R[1000- P % 54-1].y;
			}
	}

	vector<pair<string,int>> R, O;

    void solve(istream& cin, ostream& cout) {
		ll N; int Q; cin >> N >> Q;
		R.resize(1000);
		for (int i = 0; i < 1000; ++i) {
			R[i] = {torom(i+1), i+1};
		}
		sort(R.begin(), R.end());

//		for (int i = 1; i < 100000; ++i) {
//			for (int j = 1; j <= i; ++j) {
//				if (fast(i,j) != slow(i,j)) {
//					cerr << i << ' ' << j << ' ' << fast(i,j) << ' ' << slow(i,j) << endl;
//				}
//			}
//			if (i%1000==0) cerr << "done " << i << endl;
//		}

//
		for (int i = 0; i < Q; ++i) {
			ll P; cin >> P;
			cout << fast(N, P) << '\n';
		}
    }
};
