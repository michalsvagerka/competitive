#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr int cnt = 987654322;

class pestreprv {
public:
    vector<int> R;

    bool pestra(int x) {
        int y = x;
        while(y) {
            if (R[y%10]==x) return false;
            R[y%10] = x;
            y/=10;
        }
        return true;
    }


    void solve(istream& cin, ostream& cout) {
        R = vector<int>(10,0);
        vector<bool> P(cnt, true);
        for (int i = 2; i*i <= cnt; ++i) {
            if (P[i]) {
                for (int j = i*i; j <= cnt; j+=i) P[j] = false;
            }
        }

        for (int i = 2; i < cnt; ++i) {
            if (P[i] && pestra(i)) {
                cout << i << '\n';
            }
        }
    }
};
