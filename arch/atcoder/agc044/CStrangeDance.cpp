#include "../l/lib.h"

class CStrangeDance {
public:
    int N;
    vector<int> D, E, Ans;

    string canonical(const string&S) {
        string T;
        for (char s: S) {
            if (s == 'R') T += s;
            else if (T.empty() || T.back() != s) T.push_back(s);
            else T.pop_back();
        }
        return T;
    }

    int num(const vector<int>&A) {
        int ret = 0;
        for (int i = N-1; i >= 0; --i) ret = 3*ret + A[i];
        return ret;
    }

    void solve(int X, const string &T) {
        if (X == N) {
            Ans[num(D)] = num(E);
            return;
        }

        for (int d = 0; d < 3; ++d) {
            string S;
            int e = d;
            for (char t: T) {
                if (t == 'S') {
                    if (e) e = 3-e;
                    S += t;
                } else if (++e == 3) {
                    e = 0;
                    S += t;
                }
            }
            D[X] = d;
            E[X] = e;
            solve(X+1, canonical(S));
        }
    }

    void solve(istream& cin, ostream& cout) {
        string T;
        cin >> N >> T;
        D.resize(N);
        E.resize(N);
        int M = 1;
        for (int i = 0; i < N; ++i) M *= 3;
        Ans.resize(M);
        solve(0, canonical(T));
        cout << Ans;
    }
};
