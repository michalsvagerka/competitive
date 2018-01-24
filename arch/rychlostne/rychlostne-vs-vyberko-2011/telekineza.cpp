#include "../l/lib.h"
// #include "../l/mod.h"

class telekineza {
public:
    void solve(istream& cin, ostream& cout) {
        ui N, K; string S;
        cin >> N >> K >> S;
        ++K;
        map<pii,int> I{{{0,0},0}};
        int z = 0, a = 0;
        for (int i = 1; i <= N; ++i) {
            z += (S[i-1] == 'Z') - (i%K == 0);
            auto it = I.find({i%K,z});
            if (it != I.end()) a = max(a, i-it->y);
            else I[{i%K,z}] = i;
        }
        cout << a << endl;
    }
};
