#include "../../../l/lib.h"

class AHitTheLottery {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int C = 0;
        for (int b: {100,20,10,5,1}) {
            C += N/b;
            N %= b;
        }
        cout << C << endl;
    }
};
