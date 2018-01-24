#include "../l/lib.h"
#include "../l/suffixarray.h"


class strihanie {
public:
	pii range(int A, int B, int V) {
		return {V == 0 ? 0 : (V-1)/B+1, V/A};
	}

	bool inrange(pii r, int v, int K) {
		return K-1-v >= r.x && K-1-v <= r.y;
	}


	void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			int N; cin >> N;
			vector<int> S(N); for (int&s: S) cin >> s;
			int A,B,K,M; cin >> A >> B >> K >> M;
			S.resize(N + 2 + M);
			S[N] = -100000002;
			S[N+M+1] = -100000003;
			for (int i = 0; i < M; ++i) cin >> S[N+1+i];

			SuffixArray<int, true> X(S);
			int ans = 2*N;
			for (int i = X.I[N+1]; X.LCP[i] >= M; ++i) {
				int p = X.S[i+1];
				int q = N - M - p;
				pii pr = range(A,B,p);
				pii qr = range(A,B,q);
				if (pr.x <= pr.y && qr.x <= qr.y)
					if ((K-1-pr.y <= qr.x && qr.x <= K-1-pr.x) || (K-1-pr.y <= qr.y && qr.y <= K-1-pr.x)
						|| (qr.x <= K-1-pr.x && K-1-pr.x <= qr.y) || (qr.x <= K-1-pr.y && K-1-pr.y <= qr.y))
						ans = min(ans, p);
			}

			if (ans == 2*N) cout << "NIE\n";
			else cout << "TAK " << ans+1 << "\n";
		}
	}
};
