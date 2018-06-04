#include "../../../l/lib.h"
#include "../../../l/bigint.h"
#include "../../../l/mod.h"

typedef Field<1000000009> FF;
constexpr int allow16 = false;

class smooth1 {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        Num N(S);
        int two = 0, three = 0, five = 0, seven = 0, eleven = 0, thirteen = 0;
        while (N%268435456 == 0) { N /= 268435456; two+=28; }
        while (N%2 == 0) { N /= 2; two++; }
        while (N%387420489 == 0) { N /= 387420489; three+=18; }
        while (N%3 == 0) { N /= 3; three++; }
        while (N%1220703125 == 0) { N /= 1220703125; five+=13; }
        while (N%5 == 0) { N /= 5; five++; }
        while (N%1977326743 == 0) { N /= 1977326743; seven+=11; }
        while (N%7 == 0) { N /= 7; seven++; }
        if (allow16) {
            while (N%214358881 == 0) { N /= 214358881; eleven+=8; }
            while (N%11 == 0) { N /= 11; eleven++; }
            while (N%815730721 == 0) { N /= 815730721; thirteen+=8; }
            while (N%13 == 0) { N /= 13; thirteen++; }
        }

        if (N != 1) {
            cout << "0\n";
            return;
        }

        vector<FF> Twos(two+1, 0);
        for (int i = 0; i <= allow16*min(two,seven); ++i) Twos[i] = 1; // 14

        for (int i = 1; i <= 3 + allow16; ++i) { // 2,4,8,16
            vector<FF> W(two+1, 0);
            for (int j = 0; j < two+1; ++j) {
                for (int k = j; k < two+1; k += i) {
                    W[k] += Twos[j];
                }
            }
            swap(W,Twos);
        }

        vector<FF> Threes(three+1, 0); // 3,9
        for (int i = 0; i < three+1; ++i) Threes[i] = 1 + i/2;

        vector2<FF> TwoThree(two+1, three+1, 0);
        for (int i = 0; i <= two; ++i) {
            for (int j = 0; j <= three; ++j) {
                TwoThree[i][j] += Twos[i] * Threes[j];
                if (i != two && j != three) TwoThree[i+1][j+1] += TwoThree[i][j]; // 6
            }
        }

        if (allow16) {
            for (int i = 0; i < two - 1; ++i) {
                for (int j = 0; j < three; ++j) {
                    TwoThree[i + 2][j + 1] += TwoThree[i][j]; // 12
                }
            }
        }

        FF ans = 0;
        for (int ten = 0; ten <= min(two, five); ++ten) { // 10
            for (int fifteen = 0; fifteen <= allow16 * min(three, five-ten); ++fifteen) { // 15
                ans += TwoThree[two - ten][three - fifteen];
                // 5, 7, 11, 13 are implicit
            }
        }
        cout << ans << endl;
    }
};
