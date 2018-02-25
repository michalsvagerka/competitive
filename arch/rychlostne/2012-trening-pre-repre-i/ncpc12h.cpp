#include "../../../l/lib.h"
// #include "../l/mod.h"

class ncpc12h {
public:
    void solve(istream& cin, ostream& cout) {
        int N,H,L; cin >> N >> H >> L;

        vector<int> D(N, N);
        vector<int> Q(H);
        cin >> Q;
        for (int q:Q) D[q] = 0;

        vector<vector<int>> E(N);
        for (int i = 0; i < L; ++i) {
            int a, b; cin >> a >> b;
            E[a].push_back(b);
            E[b].push_back(a);
        }

        while (!Q.empty()) {
            vector<int> R;
            for (int q:Q) {
                for (int r:E[q]) {
                    if (D[r] == N) {
                        R.push_back(r);
                        D[r] = D[q]+1;
                    }
                }
            }
            swap(R,Q);
        }

        cout << distance(D.begin(), max_element(D.begin(),D.end())) << endl;
    }
};
