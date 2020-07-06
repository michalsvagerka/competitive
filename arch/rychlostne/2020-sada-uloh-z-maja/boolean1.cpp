#include "../l/lib.h"

class boolean1 {
public:
    void solve(istream& cin, ostream& cout) {
        int R, S, P; cin >> S >> R >> P;
        vector3<int> F(R, S-1, 3); cin >> F;
        vector2<int> X(R, S); cin >> X;
        int W = 2*S-1;

        vector2<int> Val(R, W, 0);
        vector2<int> Input(R, W-1, -1);
        int cur = 0;

        vector2<int> Row(S, R, -1);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < S; ++j) {
                Row[j][X[i][j]] = i;
            }
        }

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < S-1; ++j) {
                Input[i][F[i][j][0]-1] = j+S;
                Input[i][F[i][j][1]-1] = j+S;
            }
        }
        
        vector<int> H(S, 0);
        for (int i = 0; i < S; ++i) {
            while (H[i] < R && cur < P) {
                int row = Row[i][H[i]];
                if (!Val[row][W-1]) {
                    Val[row][i] = 1;
                    int pos = i;
                    while (pos != W - 1) {
                        pos = Input[row][pos];
                        if (Val[row][pos]) break;
                        auto op = F[row][pos - S];
                        if (op[2] + Val[row][op[0]-1] + Val[row][op[1]-1] >= 3) {
                            Val[row][pos] = 1;
                        } else {
                            // didn't switch to true
                            break;
                        }
                    }

                    cur += Val[row][W-1];
                }

                H[i]++;
            }
        }

        cout << H;

    }
};
