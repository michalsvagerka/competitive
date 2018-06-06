#include "../../../l/lib.h"
// #include "../l/mod.h"

class zeroone {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        set<string> Ans;
        int X = S.find_last_of('?');
        for (char c = '0'; c <= '1'; ++c) {
            if (X != string::npos) S[X] = c;
            int Y = S.find_last_of('?');
            for (char d = '0'; d <= '1'; ++d) {
                if (Y != string::npos) S[Y] = d;
                int cq = count(S.begin(),S.end(),'?');
                int c1 = count(S.begin(),S.end(),'1');
                int c0 = N-c1-cq;
                c1 -= N%2;
                if (c0+cq>c1) Ans.insert("00");
                if (c1+cq > c0) Ans.insert("11");

                if (c1+cq >= c0 && c0+cq>=c1) {
                    if (S[N - 1] == '1') {
                        Ans.insert("01");
                    } else {
                        Ans.insert("10");
                    }
                }
                if (Y != string::npos) S[Y] = '?';


            }
        }
        for (auto ans:Ans) cout << ans << endl;
    }
};
