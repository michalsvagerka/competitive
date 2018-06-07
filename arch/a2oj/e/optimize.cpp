#include "../../../l/lib.h"
#include "../../../l/segtree.h"

class optimize {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Len, H; cin >> N >> Len >> H;
        vector<int> B(Len), A(N);
        cin >> B >> A;
        set<int> C;
        C.insert(0);
        C.insert(H);
        for (int&a:A) { a = min(a, H); C.insert(H-a); }
        for (int&b:B) { b = min(b, H); if (b) { C.insert(b-1); C.insert(b); } }

        map<int,int> W;
        int S = 0;
        for (auto it = C.begin(); it != C.end(); ++S, ++it) W[*it] = S;

        AddMinTree<int> T;
        T.setup(S, 0);
        for (int b:B) if (b) T.put(0, W[b-1], 1);

        for (int i = 0; i < Len-1; ++i) T.put(W[H-A[i]], S-1, 1);
        int ans = 0;
        for (int j = Len-1; j < A.size(); ++j) {
            T.put(W[H-A[j]],W[H],1);

            ans += (T.get(0, S-1) >= Len);
            T.put(W[H-A[j-Len+1]],S-1,-1);
        }
        cout << ans << endl;
    }
};
