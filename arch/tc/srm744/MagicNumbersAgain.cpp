#include "../l/lib.h"
// #include "../l/mod.h"

class MagicNumbersAgain {
public:

    int count(ll A, ll B) {
        int ans = 0;
        for (ll i = 1; i <= 1e5; ++i) {
            if (i*i >= A && i*i <= B) {
                stringstream ss;
                ss << i*i;
                string s = ss.str();
                bool ok = true;
                for (int j = 0; j < s.size()-1; ++j) {
                    if (j%2 == 0) {
                        ok &= s[j] < s[j+1];
                    } else {
                        ok &= s[j] > s[j+1];
                    }
                }
                ans += ok;
            }
        }
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        cout << count(1, 64) << endl;
        cout << count(50, 60) << endl;
        cout << count(121, 121) << endl;
        cout << count(5679, 1758030) << endl;
        cout << count(1304164, 2000000) << endl;
    }
};
