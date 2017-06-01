#include "../l/lib.h"
// #include "../l/mod.h"

class threerow {
public:
	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		vector<int> A(N), B(N), C(N), I(N+1), BB(N+1, 0), CC(N+1, 0);
		cin >> A >> B >> C;
		for(int i = 0; i < N; ++i) { I[A[i]] = i; BB[B[i]]++; CC[C[i]]++; }

		vector<bool> K(N+1, true);
		queue<int> D;
		for (int i = 1; i <= N; ++i) if (!BB[i] || !CC[i]) { K[i] = false; D.push(i); }
		while (!D.empty()) {
			int t = I[D.front()]; D.pop();
			int b = B[t], c = C[t];
			if (--BB[b] == 0 && K[b]) { K[b] = false; D.push(b); }
			if (--CC[c] == 0 && K[c]) { K[c] = false; D.push(c); }
		}

		cout << count(K.begin(), K.end(), false) << endl;

	}
};
