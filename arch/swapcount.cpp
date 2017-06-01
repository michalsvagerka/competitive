#include "../l/lib.h"
#include "../l/avl.h"
// #include "../l/mod.h"

class swapcount {
public:
	ll slow(const vector<int> &A) {
		vector<int> B = A;
		ll	 ans = 0;
		for (int i = 0; i < A.size(); ++i) {
			for (int j = 0; j < A.size(); ++j) {
				if (B[i] > B[j]) { swap(B[i], B[j]); ++ans; }
			}
		}
		return ans;
	}

	ll fast(vector<int> &A) {
		int i = 0;
		ll ans = 0;

		for (int j = 1; j < A.size(); ++j) {
			if (A[i] > A[j]) { swap(A[i], A[j]); ++ans; }
		}
		avl<int,int> T;
		T.insert(A[i], 0);

		for (int i = 1; i < A.size(); ++i) {
			ans += T.smaller(A[i]);
			if (T.get(A[i]) == nullptr) T.insert(A[i], 0);
		}
		return ans;
	}

    void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int i = 0; i < T; ++i) {
			int N; cin >> N;
			vector<int>A(N);
			cin >> A;

//			cerr << N << endl;
			//cout << slow(A) << ' ' ;
			cout << fast(A) << endl;
		}
    }
};
