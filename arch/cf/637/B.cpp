#include "../l/lib.h"

class B {
public:

    void solve(istream& cin, ostream& cout) {
        vector<string> S{"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};
        auto val = [&](string s) {
            int x = 0;
            for (char c: s) {
                x *= 2;
                x += c=='1';
            }
            return x;
        };
        int N, K; cin >> N >> K;
        vector<string> T(N); cin >> T;
        vector<int> W,A;
        for (string s: S) W.push_back(val(s));
        for (string t: T) A.push_back(val(t));
        reverse(A.begin(),A.end());
        vector<bitset<2020>> D(N+1);
        D[0][0] = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j <= K; ++j) {
                if (D[i][j]) {
                    for (int w: W) {
                        if ((A[i]&w)==A[i]) {
                            D[i+1][j+__builtin_popcount(A[i]^w)] = true;
                        }
                    }
                }
            }
        }

        if (!D[N][K]) cout << -1 << endl;
        else {
            int k = K;
            string ans;
            for (int i = N-1; i >= 0; --i) {
                for (int j = 9; j >= 0; --j) {
                    int x = __builtin_popcount(A[i]^W[j]);
                    if ((A[i]&W[j])==A[i] && k >= x && D[i][k-x]) {
                        k -= x;
                        ans += (char)('0'+j);
                        break;
                    }
                }
            }
            cout << ans << '\n';
        }
    }
};
