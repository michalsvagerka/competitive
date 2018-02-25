#include "../../../l/lib.h"
#include "../../../l/mod.h"


constexpr int Q = 14000000;
class F {
public:
    FieldMod ten;
    inline bool hasEnough(int digits, ll needed) {
        if (digits > 13) return true;
        needed -= 1;
        needed /= 9;
        for (int d = 0; d < digits-1; ++d) {
            needed /= 10;
        }
        return needed == 0;
    }
    inline FieldMod count(int digits) { return digits == 1 ? 9 : 9 * (ten ^ (digits-1)); }

    void solve(istream& cin, ostream& cout) {
        ll S; cin >> S;
        FieldMod ans = 0;
        ten = 10;
        for (int numbers = 1; numbers <= S; ++numbers) {
            if (S % numbers == 0 && hasEnough(S / numbers, numbers)) {
                ans += count(S / numbers) - numbers + 1;
            } else if (hasEnough(S / numbers, numbers - S % numbers) && hasEnough(S / numbers + 1, S%numbers)) {
                ++ans;
            }
        }

        vector<ll> P(13, 1);
        P[1] = 9;
        for (int i = 2; i < 13; ++i) P[i] = P[i-1] * 10;

        for (int i = 1; i < 12; ++i) { // i == first full
            ll count = 0;
            for (int j = i; j < 12; ++j) { // j == last full
                count += j * P[j];

                if (count <= S) {
                    for (int k = 0; k < P[i-1]; ++k) {
                        int rest = S - count - (i-1)*k;
                        if (rest >= 0 && rest % (j+1) == 0 && rest / (j+1) < P[j+1]) {
                            if (i == j && (k == 0 || rest == 0)) continue;
                            if (i+1 == j && k == 0 && rest == 0) continue;
                            ++ans;
                        }
                    }
                }
            }
        }
        cout << ans << endl;

//        vector<int> Z(Q);
//        Z[0] = 0;
//        int p = 10, k = 1;
//        for (int i = 1; i < Q; ++i) {
//            if (i == p) {
//                p *= 10;
//                ++k;
//            }
//            Z[i] = Z[i-1] + k;
//        }
//
//        cout << Z[Q-1]-100000000 << endl;

    }
};
