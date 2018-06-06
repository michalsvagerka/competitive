#include "../../../l/lib.h"
 #include "../../../l/segtree.h"

class lastchance {
public:
    bool isvowel(char s) {
        return s=='a'||s=='e'||s=='i'||s=='o'||s=='u'||s=='A'||s=='E'||s=='I'||s=='O'||s=='U';
    }

    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();

        vector<int> R(3*N+1, N+1);
        AssignMinTree<int> T;
        T.setup(R, N+1);

        T.put(0, 2*N, 0);

        int ans = 0, cnt = 0;
        int bal = 2*N;
        for (int i = 0; i < N; ++i) {
            if (isvowel(S[i])) bal++;
            else bal-=2;

            int b = T.get(bal);
            if (b != N+1) {
                int k = i-b+1;
                if (k > ans) {
                    ans = k;
                    cnt = 1;
                } else if (k == ans) {
                    cnt++;
                }
            }
            T.put(0, bal, i+1);
        }


        if (ans == 0) {
            cout << "No solution\n";
        } else {
            cout << ans << ' ' << cnt << endl;
        }
    }
};
