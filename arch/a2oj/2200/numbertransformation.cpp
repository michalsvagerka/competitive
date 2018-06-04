#include "../../../l/lib.h"
// #include "../l/mod.h"

class numbertransformation {
public:
    vector<vector<int>> E;

    void addEdge(int i, int lo, int hi, int from, int to, int tar) {
        if (lo >= to || hi <= from) return;
        if (lo >= from && hi <= to) {
            E[i].push_back(tar);
            return;
        }

        addEdge(2*i, lo, (lo+hi)/2, from, to, tar);
        addEdge(2*i+1, (lo+hi)/2, hi, from, to, tar);
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> X(N);
        cin >> X;
        sort(X.begin(),X.end());
        X.erase(unique(X.begin(),X.end()),X.end());

        int A, B; cin >> A >> B;
        vector<vector<int>> V(A-B+1);
        for (int x:X) {
            int p = (B+x-1)/x*x;
            if (p <= A) V[p-B].push_back(x);
        }

        int ans = 0, R = B;
        vector<int> S = V[0];
        while (R < A) {
            ++ans;
            int s = R+1;
            for (int x:S) s = max(s, R + x - (R % x) - 1);
            for (int j = R+1; j <= min(A,s); ++j) for (int v:V[j-B]) S.push_back(v);
            R = s;
        }

        cout << ans << '\n';


//        int W = 1<<logceil(A-B+1);
//        E.resize(2*W);
//        for (int i = 2; i < 2*W; ++i) E[i].push_back(i/2);
//        for (int i = W+1; i <= W+A-B; ++i) E[i].push_back(i-1);
//        for (int x:X) {
//            for (int j = (B+x-1)/x*x; j < A; j += x) {
////                cerr << x << ' ' << j+1 << ' ' << min(A,j+x) << endl;
//                addEdge(1, 0, W, j+1-B, min(W,j+x-B), W+j-B);
//            }
//        }
//
//
//
//        vector<bool> V(2*W, false);
//        vector<int> S{W+A-B}, T;
//        int ans = 0;
//        while (true) {
//            for (int s = 0; s < S.size(); ++s) {
//                if (S[s] == W) {
//                    cout << ans << endl;
//                    return;
//                }
//                for (int v:E[S[s]]) {
//                    if (!V[v]) {
//                        V[v] = true;
//                        if (v >= W) T.push_back(v);
//                        else S.push_back(v);
//                    }
//                }
//            }
//            swap(S,T);
//            T.clear();
//            ++ans;
//        }
//


    }
};
