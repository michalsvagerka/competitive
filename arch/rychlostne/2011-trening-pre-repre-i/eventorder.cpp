#include "../../../l/lib.h"
#include "../../../l/mod.h"

typedef Field<1000000009> T;

class eventorder {
public:
    void solve(istream& cin, ostream& cout) {
        auto F = T::fact(3000);
        auto G = T::invfact(3000);
        int L,I;
        cin >> L >> I;
        int m = 2*L+I;
        vector<T> D(m+1,0);
        T ans = D[1] = L == 0;

        for (int i = 2; i <= m; ++i) {
            D[i] = (T(i)^I) * ((T(i)*T(i-1)/2)^L);
            for (int j = i; j > 0; --j) {
                if ((j-i)%2==0)
                    ans += F[i] * G[j] * G[i-j] * D[j];
                else
                    ans -= F[i] * G[j] * G[i-j] * D[j];
            }
        }

        cout << ans << endl;


    }
};
