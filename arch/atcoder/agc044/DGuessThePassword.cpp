#include "../l/lib.h"

constexpr int L = 128;
constexpr int Q = 850;
constexpr int M = 62;
string S = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890";
string hidden = "987iuhdsfiw7yishdfiuwyhfiou98uIOUHIUHIFYUHFISDHFIH";

class DGuessThePassword {
public:
    string Ans;
    int N;
    vector<int> C;

    int dist(string A, string B) {
        int a = A.size(), b = B.size();
        vector2<int> D(a+1, b+1, a+b+2);
        D[0][0] = 0;
        for (int i = 0; i <= a; ++i) {
            for (int j = 0; j <= b; ++j) {
                if (i != a && j != b && A[i] == B[j]) D[i+1][j+1] = min(D[i+1][j+1], D[i][j]);
                if (i != a) D[i+1][j] = min(D[i+1][j], D[i][j]+1);
                if (j != b) D[i][j+1] = min(D[i][j+1], D[i][j]+1);
                if (i != a && j != b) D[i+1][j+1] = min(D[i+1][j+1], D[i][j]+1);
            }
        }
        return D[a][b];
    }

    int query(istream& cin, ostream& cout, string S) {
//        return dist(S, hidden);
        cout << "? " << S << endl;
        int q; cin >> q; return q;
    }

    void binsearch(istream&cin, ostream&cout, int l, int r, int have, char c) {
        if (l == r) return;
        if (have == 0) return;

        vector<int> Pos;
        int free = 0;
        for (int i = l; i < r; ++i) {
            if (Ans[i] == '-') Pos.push_back(i);
        }
        if (Pos.size() == have) {
            // no need to query
            for (int i = l; i < r; ++i) {
                if (Ans[i] == '-') Ans[i] = c;
            }
        } else {
            string Q(N, S[0]);
            int mid = Pos[(Pos.size()-1)/2];
            for (int i = l; i <= mid; ++i) {
                if (Ans[i] == '-') Q[i] = c;
            }
            int q = query(cin, cout, Q);
            int good = N - q - C[0];
            binsearch(cin, cout, l, mid+1, good, c);
            binsearch(cin, cout, mid+1, r, have - good, c);
        }
    }

    void solve(istream& cin, ostream& cout) {
        C.resize(M);
        for (int i = 0; i < M; ++i) {
            C[i] = L - query(cin, cout, string(L, S[i]));
        }

        N = 0;
        for (int i = 0; i < M; ++i) N += C[i];

        Ans = string(N, '-');
        for (int i = 0; i < N; ++i) {
            string Q(N, S[1]);
            Q[i] = S[0];
            int s = query(cin, cout, Q);
            if (N - s == C[1] + 1) Ans[i] = S[0];
        }

        for (int i = 1; i < M; ++i) {
            binsearch(cin, cout, 0, N, C[i], S[i]);
        }
//
        cout << "! " << Ans << endl;
    }
};
