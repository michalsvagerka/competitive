#include "../../../l/lib.h"
#include "../../../l/util.h"

class EJigsaw {
public:
    void solve(istream& cin, ostream& cout) {
        int N, H; cin >> N >> H;
        UnionFind UF(2*H+2);
        vector<int> InDeg(2*H+2, 0), OutDeg(2*H+2, 0);
        for (int i = 0; i < N; ++i) {
            int A, B, C, D; cin >> A >> B >> C >> D;
            int left = C ? C : H+1+A;
            int right = D ? H+1+D : B;
            InDeg[right]++;
            OutDeg[left]++;
            UF.unite(left, right);
        }

        for (int i = H+2; i <= 2*H+1; ++i) {
            if (OutDeg[i] >= InDeg[i]) {
                int diff = OutDeg[i] - InDeg[i];
                InDeg[i] += diff;
                OutDeg[0] += diff;
                if (diff) UF.unite(0, i);
            } else {
                cout << "NO\n";
                return;
            }
        }
        for (int i = 1; i <= H; ++i) {
            if (OutDeg[i] <= InDeg[i]) {
                int diff = InDeg[i] - OutDeg[i];
                InDeg[0] += diff;
                OutDeg[i] += diff;
                if (diff) UF.unite(0, i);
            } else {
                cout << "NO\n";
                return;
            }
        }

        int cmp = UF.comp;
        for (int i = 1; i < 2*H+2; ++i) if (InDeg[i] == 0 && OutDeg[i] == 0) --cmp;
        if (cmp == 1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
};
