#include "../l/lib.h"
// #include "../l/mod.h"

class javacert {
public:
    ui C,Q,M;
    vector<ui> S;
    vector<vector<pair<ui,ui>>> O;
    unordered_map<ui,ui> Mem;

    bool solve(ui correct, ui total, ui lo, ui hi, ui i, ui &bestLo, ui&bestHi) {
        if (correct > total) return false;

        if (i == M) {
            if (correct == 0 && total == 0) {
                bestLo = lo;
                bestHi = hi;
                return true;
            } else {
                return false;
            }
        }

        ui key = correct | (total << 7) | (lo << 14) | (hi << 21) | (i<<28);
        auto it = Mem.find(key);
        if (it!=Mem.end()) {
            bestLo = it->y&0x7f;
            bestHi = (it->y>>7)&0x7f;
            return it->y>>14;
        }

        bool ans = false;
        bestLo = 0; bestHi = 101;
        for (auto&o : O[S[i]]) {
            if (o.x > correct || o.y > total) break;
            ui myLo, myHi;
            if (solve(correct - o.x, total - o.y, min(lo, o.y), max(hi, o.y), i+1,myLo,myHi)) {
                if (myHi-myLo < bestHi-bestLo) {
                    bestHi = myHi;
                    bestLo = myLo;
                    ans = true;
                }
            }
        }

        Mem[key] = (ans<<14) | (bestLo) | (bestHi<<7);
        return ans;
    }

    ui percent(ui c, ui t) {
        ui pct = 100*c / t;
        ui mod = (100*c)%t;
        if (2*mod < t) return pct;
        else if (2*mod > t) return pct + 1;
        else return pct + pct%2;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> C >> Q >> M;
        S.resize(M);
        cin >> S;

        O.resize(101);
        for (ui t = 1; t <= 100; ++t) {
            for (ui c = 0; c <= t; ++c) {
                O[percent(c,t)].emplace_back(c,t);
            }
        }
        
        ui ansLo, ansHi;
        solve(C,Q,101,0,0,ansLo,ansHi);

        for (ui i = 0; i < M; ++i) {
            for (auto&o : O[S[i]]) {
                if (o.y < ansLo || o.y > ansHi) continue;
                ui myLo, myHi;
                if (solve(C - o.x, Q - o.y, ansLo, ansHi, i+1, myLo, myHi) && myLo == ansLo && myHi == ansHi) {
                    C -= o.x;
                    Q -= o.y;
                    cout << o.y-o.x << ' ' << o.y << '\n';
                    break;
                }
            }
        }
    }
};
