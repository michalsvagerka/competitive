#include "../l/lib.h"
 #include "../l/runtimemod.h"

class VisitOfTheGreat {
public:
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        int K, P;
        ll L, R;
        cin >> K >> L >> R >> P;

        if (P == 2) {
            cout << (K+1)%2 << '\n';
            continue;
        }

        if (K == 1) {
            cout << 2 << '\n';
            continue;
        }



        bool isOdd = K%2;
        auto Y = RField{2, P-1} ^ L;
        auto X = RField{K%P, P} ^ int(Y);
        R -= L;
        
        if (K%P == 0 && Y == 0) X = RField{0, P};

        RField Z;
        if (X == 0) {
            Z = {1, P};
        } else if (X == 1) {
            Z = RField{2, P} ^ ((R+1)%(P-1));
        } else {
            Z = ((X ^ int(RField{2, P-1} ^ (R+1))) - 1) / (X-1);
        }
        if (isOdd) {
            Z /= RField{2, P} ^ (R%(P-1));
        }

        cout << Z << '\n';

    }
}
};
