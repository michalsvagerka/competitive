#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353u> FF;
class SpanningNoLine {
public:
    int countSpanning(int n, int m) {
        FF D = 0, Y = 1;
        for (int i = 0; i+1 < m; ++i) {
            D -= Y * n;
            Y += D;
        }
        D -= Y * n;
        if (m&1) D = -D;

        return (ui)(D * FF{n}.pow(n-m) / n / n);
    }

    void solve(istream& cin, ostream& cout) {
        cout << countSpanning(3, 1) << endl;
        cout << countSpanning(3, 2) << endl;
        cout << countSpanning(3, 3) << endl;
        cout << countSpanning(4, 4) << endl;
        cout << countSpanning(50, 20) << endl;
        cout << countSpanning(1, 1) << endl;
        cout << countSpanning(1000000, 1000000) << endl;
    }
};
