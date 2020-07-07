#include "../../../l/lib.h"

class FAbbreviation {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> W(N); cin >> W;
        vector<int> L(N);
        for (int i = 0; i < N; ++i) {
            L[i] = W[i].size();
        }

        map<string, int> I;
        vector<int> C(N);
        for (int i = 0; i < N; ++i) {
            auto it = I.find(W[i]);
            if (it != I.end()) {
                C[i] = it->y;
            } else {
                C[i] = I.size();
                I[W[i]] = C[i];
            }
        }

        int tot = accumulate(L.begin(),L.end(),0);
        int ans = tot + N - 1;
        for (int i = 0; i < N; ++i) {
            vector<int> Same;
            for (int j = i+1; j < N; ++j) Same.push_back(j);
            int len = 0;
            for (int k = 0; i+k < N; ++k) {
                len += L[i+k];

                vector<int> New;
                for (int s: Same) {
                    if (s+k < N && C[i+k] == C[s+k]) {
                        New.push_back(s);
                    }
                }
                swap(New, Same);
                int c = 1, l = i;
                for (int s: Same) {
                    if (l + k < s) {
                        l = s;
                        c++;
                    }
                }

                if (c > 1) {
//                    cout << i << ' ' << k << ' ' << c << ' ' << len << ' ' << tot + N - 1 - c * (len - k - 1 + k)
//                         << endl;
                    ans = min(ans, tot + N - 1 - c * (len - 1));
                }
            }
        }
        cout << ans << '\n';
    }
};
