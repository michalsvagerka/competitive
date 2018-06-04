#include "../../../l/lib.h"
#include "../../../l/mod.h"
#include "../../../l/runtimemod.h"

constexpr int MOD = 1000000006;

class multipliers {
public:
    void solve(istream& cin, ostream& cout) {
        int M; cin >> M;
        map<int,int> S;
        for (int i = 0; i < M; ++i) {
            int p; cin >> p; S[p]++;
        }

        RField pw = RField{1,MOD};
        int twos = 0;
        for (pii s:S) {
            int x = s.y+1;
            while (x%2==0) {
                twos++;
                x /= 2;
            }
            pw *= x;
        }

        FieldMod ans = 1;
        for (pii s:S) {
            int x = s.y;
            int tw = 0;
            while (x%2 == 0) {
                tw++;
                x /= 2;
            }
            ui u = ui(pw * x * RField{2, MOD}.pow(twos+tw-1));
            ans *= FieldMod{s.x}.pow(u);
        }
        cout << ans << endl;
    }
};
