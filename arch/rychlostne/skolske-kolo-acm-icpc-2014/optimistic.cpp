#include "../l/lib.h"
#include "../l/mod.h"

class optimistic {
public:
    pair<FieldMod,bool> findOptimistic(string S) {
        map<ui, FieldMod> T;
        T[0xffff] = 1;
        ui id = 0;
        for (char s:S) {
            ui d = ui(s-'0');
            map<ui, FieldMod> U;
            for (auto &t: T) {
                for (ui e = 0; e < 10; ++e) {
                    ui isLower = (t.x>>17)&1;
                    if (e > d && !isLower) continue;
                    if (e < d) isLower = 1;

                    ui nonZero = (t.x>>18)&1;
                    ui a1 = t.x&0xf;
                    ui a2 = (t.x>>4)&0xf;
                    ui a3 = (t.x>>8)&0xf;
                    ui a4 = (t.x>>12)&0xf;
                    ui isOpt = (t.x>>16)&1;
                    if (e > 0) nonZero = 1;
                    if (e > a4) isOpt = 1;
                    else if (e > a3) a4 = e;
                    else if (e > a2) a3 = e;
                    else if (e > a1) a2 = e;
                    else if (nonZero) a1 = e;

                    ui state = (a1) | (a2<<4) | (a3<<8) | (a4<<12) | (isOpt<<16) | (isLower<<17) | (nonZero<<18);
                    U[state] += t.y;
                }
            }
            ++id;
            swap(U,T);
        }
        FieldMod ans = 0;
        bool isSOpt = false;
        for (auto &t:T) {
            if (t.x&(1<<16)) {
                if (t.x&(1<<17)) {
                    ans += t.y;
                } else {
                    isSOpt = true;
                }
            }
        }
        return {ans,isSOpt};
    }

    void solve(istream& cin, ostream& cout) {
        string A,B; cin >> A >> B;
        auto AS = findOptimistic(A),
             BS = findOptimistic(B);
        cout << BS.x + BS.y - AS.x << endl;
    }
};
