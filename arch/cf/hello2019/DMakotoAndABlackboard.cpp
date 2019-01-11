#include "../l/lib.h"
#include "../l/mod.h"

class DMakotoAndABlackboard {
public:
void solve(istream& cin, ostream& cout) {
    ll N, K; cin >> N >> K;
    vector<pair<ll,int>> F;
    for (ll i = 2; i < 4e7; ++i) {
        if (N%i==0) {
            int c = 0;
            while (N%i==0) { N/=i; c++; }
            F.push_back({i, c});
        }
    }
    if (N != 1) {
        F.push_back({N,1});
    }

    vector<FieldMod> INV(70);
    for (int i = 1; i < 70; ++i) {
        INV[i] = FieldMod{1} / i;
    }
    
//    map<ll, FieldMod> G;
//    G[1] = 1;
    FieldMod cur = 1;
    for (auto &f:F) {
        vector<FieldMod> Z(f.y+1, 0);
        Z[f.y] = 1;
        for (int k = 0; k < K; ++k) {
            vector<FieldMod> W(f.y+1, 0);
            for (int i = 0; i <= f.y; ++i) {
                for (int j = 0; j <= i; ++j) {
                    W[j] += Z[i] * INV[i+1];
                }
            }
            swap(W, Z);
        }

        map<ll, FieldMod> R;
        FieldMod s = 1;
        FieldMod g = 0;
        for (int i = 0; i <= f.y; ++i) {
//            for (auto g:G) {
//                R[g.x * s] += g.y * Z[i];
//            }
            g += Z[i] * s;
            s *= (f.x%1000000007);
        }

        cur *= g;
//        swap(R, G);
    }

    FieldMod ans = cur;
//    for (auto g:G) {
//        ans += (g.x%(1000000007)) * g.y;
//    }
    cout << ans << endl;
}
};
