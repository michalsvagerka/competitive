#include "../../../l/lib.h"
// #include "../l/mod.h"

class lazystudent {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pair<pii,int>> B(M);
        vector<pii> A(M);
        for (int i = 0; i < M; ++i) {
            int w,b; cin >> w >> b;
            B[i] = {{w,1-b}, i};
        }

        sort(B.begin(),B.end());
        int comp = 1;
        int r = 0, t = 3;
        for (int i = 0; i < M; ++i) {
            int id = B[i].y;
            if (B[i].x.y == 0) {
                A[id] = {comp, comp+1};
                ++comp;
            } else {
                ++r;
                if (r >= t-1) {
                    r = 1;
                    t++;
                }
                if (t > comp) {
                    cout << "-1\n";
                    return;
                }

                A[id] = {r,t};
            }
        }

        for (int i = 0; i < M; ++i) {
            cout << A[i] << '\n';
        }

    }
};
