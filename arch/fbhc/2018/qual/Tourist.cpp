#include "../l/lib.h"
// #include "../l/mod.h"

class Tourist {
public:
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    cerr << "TC " << T << endl;
    for (int t = 0; t < T; ++t) {
        int K, N; ll V;
        cin >> N >> K >> V;
        vector<string> S(N); cin >> S;
        V = (V-1)%N+1;
        vector<int> T(N, 0);
        vector<pii> Z(N);
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < N; ++j) {
                Z[j] = {T[j], j};
            }
            sort(Z.begin(),Z.end());
            for (int j = 0; j < K; ++j) {
                T[Z[j].y]++;
            }
        }

        vector<int> Ret(K);
        for (int i = 0; i < K; ++i) Ret[i] = Z[i].y;
        sort(Ret.begin(),Ret.end());
        vector<string> Ans(K);
        for (int i = 0; i < K; ++i) Ans[i] = S[Ret[i]];

        cout << "Case #" << t+1 << ": " << Ans;

    }

}
};
