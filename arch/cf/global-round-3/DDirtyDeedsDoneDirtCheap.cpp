#include "../l/lib.h"

class DDirtyDeedsDoneDirtCheap {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> P(N); cin >> P;
        vector<pair<pii, int>> LO, HI;
        for (int i = 0; i < N; ++i) {
            if (P[i].x < P[i].y) {
                LO.emplace_back(P[i], i+1);
            } else if (P[i].x > P[i].y) {
                HI.emplace_back(P[i], i+1);
            }
        }
        sort(LO.begin(),LO.end());
        reverse(LO.begin(),LO.end());
        sort(HI.begin(),HI.end());
        if (LO.size() >= HI.size()) {
            cout << LO.size() << endl;
            for (int i = 0; i < LO.size(); ++i) {
                cout << LO[i].y << " \n"[i==LO.size()-1];
            }
        } else {
            cout << HI.size() << endl;
            for (int i = 0; i < HI.size(); ++i) {
                cout << HI[i].y << " \n"[i==HI.size()-1];
            }
        }
    }
};
