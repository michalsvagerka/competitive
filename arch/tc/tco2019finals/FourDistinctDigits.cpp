#include "../l/lib.h"
#include "../l/random.h"

constexpr int MIND = 40;

class FourDistinctDigits {
public:
    char digit(int d) {
        if (d < 10) return char('0' + d);
        else if (d < 36) return char ('A' + d - 10);
        else return char('a' + d - 36);
    }

    string find(long long N, int D, int B) {
        if (N == 1) {
            string ans(D, '0');
            ans[0] = '1';
            return ans;
        }

        unordered_map<ll, pair<ll, int>> X;
        random_ll R(1, (1LL<<MIND)-1);
        random_ll Dig(1, (B-1)/2);
        vector<ll> Y(MIND, 1);
        for (int j = MIND-2; j >= 0; --j) {
            Y[j] = (Y[j+1] * B) % N;
        }
        while (true) {
            ll a = R(rng), aR = 0;
            int b = Dig(rng);
            for (int i = 0; i < MIND; ++i) aR += Y[i] * (a>>i&1);
            aR = (aR * b) % N;
            auto it = X.find(aR == 0 ? 0 : N-aR);
            if (it != X.end()) {
                string ans(D, '0');
                for (int i = 0; i < MIND; ++i) ans[i] = digit((a>>i&1)*b + (it->y.x>>i&1)*it->y.y);
                while (ans[0] == '0') ans = ans.substr(1, D) + '0';
                cerr << X.size() << '\n';
                return ans;
            } else {
                X[aR] = {a,b};
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cout << find(4247, 40, 10) << endl;
        cout << find(2, 43, 46) << endl;
        cout << find(2, 40, 5   ) << endl;
        cout << find(46029, 47, 7) << endl;
        cout << find(987654321, 40, 12) << endl;
        cout << find(6224942400LL, 46, 61) << endl;
        cout << find(46656000000LL, 46, 61) << endl;
    }
};
