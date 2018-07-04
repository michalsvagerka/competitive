#include "../../../l/lib.h"
 #include "../../../l/suffixarray.h"
#include "../../../l/consttree.h"
#include <numeric>

class TaskE {
public:
void solve(istream& cin, ostream& cout) {
    string S, T; cin >> S >> T;
    int N = S.size(), M = T.size();
    string W = S + '$' + T + '#';
    SuffixArray<int, true, true> SA(W);
    vector<int> Z(N+1);
    iota(Z.begin(),Z.end(),0);

//    vector<pair<string,int>> D;
//    for (int i = 0; i <= N; ++i) {
//        string s = S.substr(0, i);
//        s += T;
//        s += S.substr(i);
//        D.push_back({s,i});
//    }
//    sort(D.begin(),D.end());
//    for (int i = 0; i <= N; ++i) cout << D[i].y << ' ';
//    cout << endl;

    auto cmp = [&](int a, int b, int l) {
        int p = SA.lcp(a, b);
        if (p >= l) return 0;
        else if (W[a+p] < W[b+p]) return -1;
        else return 1;
    };

    auto srt = [&](int a, int b) -> bool {
        bool sw = false;
        if (b < a) {
            swap(a,b);
            sw = true;
        }
        if (a + M <= b) {
            int x = cmp(N+1, a, M);
            if (x) return sw ^ (x == -1);
            x = cmp(a, a+M, b-(a+M));
            if (x) return sw ^ (x == -1);
            x = cmp(b - M, N+1, M);
            if (x) return sw ^ (x == -1);
            return sw;
        } else {
            int x = cmp(N+1, a, b-a);
            if (x) return sw ^ (x == -1);
            x = cmp(N+1+b-a, N+1, M-(b-a));
            if (x) return sw ^ (x == -1);
            x = cmp(a, N+1+(M-(b-a)), b-a);
            if (x) return sw ^ (x == -1);
            return sw;
        }
    };

    sort(Z.begin(),Z.end(),srt);

    vector<pii> O(N+1);
    for (int i = 0; i <= N; ++i) O[Z[i]] = {i, Z[i]};

    vector<vector<pair<pair<pii,pii>,int>>> T(N+1);
    for (int q = 0; q < Q; ++q) {
        int l,r,k,x,y; cin >> l >> r >> k >> x >> y;
        T[k].push_back({{{l,r},{x,y}},q});
    }

    for (int k = 0; k <= N; ++k) {
        if (T[k].empty()) continue;
        if (k < 200) {
            vector<Const
        }
    }

}
};
