#include "../l/lib.h"

vector<int> manacher (string const&s){
    int n = s.size(), m=2*n-1;
    vector<int> ret(m), t(m, -1);
    for(int i=0;i<n;++i) t[2*i] = s[i];
    int x=0;
    for(int i=1;i<m;++i){
        int &y = ret[i] = 0;
        if(i<x+ret[x]) y = min(ret[2*x-i], x+ret[x]-i); // copy from left side
        while(i-y-1 >=0 && i+y+1 < m && t[i-y-1] == t[i+y+1]) ++y; // scan
        if(i+y>=x+ret[x]) x=i; // move right border
    }
    for(int i=0;i<m;++i) if(i-ret[i]==0 || i+ret[i]== m-1) ++ret[i]; // ???
    for(int&e:ret) e/=2;
    return ret;
}

class D1PrefixSuffixPalindromeEasyVersion {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int i = 0; i < T; ++i) {
            string S; cin >> S;
            string T = "";

            int N = S.size();
            int L = 0;
            while (2*(L+1) <= N && S[L] == S[N-L-1]) ++L;


            for (int t = 0; t < 2; ++t) {
                auto Q = manacher(S);

                int best = 0;
                for (int i = 1; i + 2*L <= N; ++i) {
//                    bool ok = true;
//                    for (int j = 0; j < i; ++j) ok &= S[L + j] == S[L + i - j - 1];
//                    if (ok) best = i;
                    if (2*Q[2*L+i-1]+(i%2) >= i) best = i;
//                    if (ok != (2*Q[2*L+i-1]+i%2 >= i)) cout << "fail\n";
                }
                string W = S.substr(0, L) + S.substr(L, best) + S.substr(N-L, L);
                if (W.size() > T.size()) T = W;
                reverse(S.begin(),S.end());
            }
            cout << T << '\n';
        }
    }
};
