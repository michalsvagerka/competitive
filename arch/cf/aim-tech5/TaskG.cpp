#include "../l/lib.h"
// #include "../l/mod.h"

constexpr ll up = 10004205361450474LL;

class TaskG {
public:

    map<pair<pair<ll,ll>,int>,vector<ll>> M;
    unordered_map<pair<pair<ll,ll>,int>,bool> C;
    vector<ll> INTSIZE;

    bool canSolve(ll lo, ll hi, int depth) {
        if ((hi-lo) > INTSIZE[depth]) return false;
        if (lo >= 10000) return true;
//        if (lo >= 10000) return true;
//            return (hi-lo) <= INTSIZE[depth];
//        }


        auto it = C.find({{lo,hi},depth});
        if (it!=C.end()) return it->y;
        if (depth == 1) {
            if (hi <= min(2*lo, lo + 10000)) return true;
            else return false;
        } else {
//            cerr << lo << ' ' << hi << ' ' << depth << endl;

            ll l = lo;
            for (int i = 0; i <= min(lo, 10000LL); ++i) {
                ll r = bsh(l, hi, [&](ll z) { return canSolve(l, z, depth-1); });
                M[{{lo,hi},depth}].push_back(r);
                if (r >= hi) {
                    M[{{lo,hi},depth}].pop_back();
                    C[{{lo,hi},depth}] = true;
                    return true;
                }
                l = r+1;
            }
            return C[{{lo,hi},depth}] = false;
        }
    }

    /*
     *
     * imc => imca => acmi => acmicpc
     * cm => cmi => imc => imca => acmicpc => acmicpc
     * m => mi => im => imc => imca => acmi => acmicpc
     */

void solve(istream& cin, ostream& cout) {
//        cout << bsh(200000000000LL, 250000000000LL, [&](ll w) { return canSolve(1, w, 4); }) << endl;

        INTSIZE.resize(5);
        INTSIZE[0] = 0;
        for (int l = 0; l < 4; ++l) INTSIZE[l+1] = INTSIZE[l]*10001+10000;
        vector<ll> H{204761410474LL};
        cerr << canSolve(1, H[0], 4);
        int d = 5;
        ll lo = 1;
        ll hi = up+1;
        while (d > 0) {
            auto &G = d == 5 ? H : M[{{lo, hi}, d}];
            cerr << lo << ' ' << hi << endl;
            if (G.empty()) {
                if (d == 1) {
                    for (ll i = lo; i < hi; ++i) {
                        G.push_back(i);
                        if (G.size() == 10000) break;
                    }
                } else {
                    for (ll s = lo+INTSIZE[d-1]; s < hi; s += INTSIZE[d-1]+1) {
                        G.push_back(s);
                        if (G.size() == 10000) break;
                    }
                }
            }
            cout << G.size() << ' ' << G;
            flush(cout);
            int ans; cin >> ans;
            if (ans < 0) return;

            if (ans != 0) { lo = G[ans-1]+1; }
            if (ans != G.size()) { hi = G[ans]; }
            --d;
        }
//        print(1, hi, d, cout);
//        cout << canSolve(1, 10004205361450474LL, 3) << '\n';
//    for (int i = 1; i < 10; ++i) {
//        int r = bsh(i+1, 10000, [&](int w) { return canSolve(i, w, 4); });
//        cout << i << ' ' << r << endl;
//    }
}
};
