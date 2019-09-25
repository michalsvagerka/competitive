#include "../l/lib.h"

class CTokitsukazeAndDuel {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        string S; cin >> S;
        vector<int> C, D;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '0') C.push_back(i);
            else D.push_back(i);
        }

        int A = C.size(), B = D.size();

        if (A == 0 || B == 0) {
            cout << "tokitsukaze\n";
            return;
        }

        if (C.back() - C.front() < K || D.back() - D.front() < K) {
            cout << "tokitsukaze\n";
            return;
        }

        int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
        for (int i = 0; i + K <= N; ++i) {
            while (a1 < A && C[a1] < i) ++a1;
            while (a2 < A && C[a2] < i + K) ++a2;
            while (b1 < B && D[b1] < i) ++b1;
            while (b2 < B && D[b2] < i + K) ++b2;
            int lA = a1 == 0 ? 0 : 1 + (C[a1-1] - C[0] >= K);
            int rA = a2 == A ? 0 : 1 + (C[A-1] - C[a2] >= K);
            int lB = b1 == 0 ? 0 : 1 + (D[b1-1] - D[0] >= K);
            int rB = b2 == B ? 0 : 1 + (D[B-1] - D[b2] >= K);
            if (max(lA + rA, lB + rB) >= 2) {
                cout << "once again\n";
                return;
            }
        }

        cout << "quailty\n";
    }
};
