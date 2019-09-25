#include "../l/lib.h"

class EPetyaAndConstructionSet {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> D(N);
        for (int i = 0; i < N; ++i) {
            cin >> D[i].x;
            D[i].y = i+1;
        }
        sort(D.begin(),D.end());
        reverse(D.begin(),D.end());
        vector<int> W(N);
        for (int i = 0; i < N; ++i) W[i] = 2*D[i].y;
        for (int i = 0; i < N-1; ++i) {
            cout << W[i] << ' ' << W[i+1] << '\n';
        }

        for (int i = 0; i < N; ++i) {
            int j = i + D[i].x - 1;
            cout << 2*D[i].y-1 << ' ' << W[j] << endl;
            if (j == W.size()-1) W.push_back(2*D[i].y-1);
        }
    }
};
