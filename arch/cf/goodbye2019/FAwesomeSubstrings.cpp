#include "../../../l/lib.h"

class FAwesomeSubstrings {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        if (N == 1) {
            cout << (S == "1") << '\n';
            return;
        }

        ll ans = 0;
        int SQRT = max(2, (int)(sqrt(N)));
        for (int i = 1; i <= SQRT; ++i) {
            vector<int> C{0};
            int c = 0;
            for (char s: S) {
                if (s == '1') c += i-1;
                else c--;
                C.push_back(c);
            }
            sort(C.begin(),C.end());
            int prev = -2*N, cnt = 0;
            for (int i = 0; i < C.size(); ++i) {
                if (C[i] == prev) {
                    ans += cnt;
                    ++cnt;
                } else {
                    prev = C[i];
                    cnt = 1;
                }
            }
        }
        vector<int> Ones;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '1') Ones.push_back(i);
        }
        vector<int> P(N+1, 0);

        if (!Ones.empty()) {
            int nextOne = 0;
            for (int i = 0; i < N; ++i) {
                if (Ones[nextOne] < i) ++nextOne;
                if (nextOne == Ones.size()) break;
                for (int j = 1; j < SQRT+5; ++j) {
                    if (nextOne + j - 1 >= Ones.size()) break;
                    int l = Ones[nextOne+j-1];
                    int r = nextOne+j==Ones.size()?N-1:Ones[nextOne+j]-1;
                    int lo = max(SQRT+1, (l - i + 1 + j - 1)/j);
                    int hi = (r - i + 1)/j;

                    if (lo <= hi) ans += hi-lo+1;
                }
            }
        }


        cout << ans << '\n';
    }
};
