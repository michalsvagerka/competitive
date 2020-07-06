#include "../l/lib.h"

class covidwall {
public:
    void solve(istream& cin, ostream& cout) {
        int N, L, R; cin >> N >> L >> R;
        vector2<int> D(N, 4); cin >> D;
        --L;

        set<int> X,Y;
        for (int i = 0; i < N; ++i) {
            for (int j: {0,2}) X.insert(D[i][j]);
            for (int j: {1,3}) Y.insert(D[i][j]);
        }
        map<int, int> DX, DY;
        vector<int> AX(X.begin(),X.end()), AY(Y.begin(),Y.end());
        for (int x: X) {
            int id = DX.size();
            DX[x] = id;
        }

        for (int y: Y) {
            int id = DY.size();
            DY[y] = id;
        }

        int A = DX.size(), B = DY.size();
        vector2<int> CNT(B, A, 0);
        for (int i = 0; i < N; ++i) {
            for (int y = DY[D[i][1]]; y < DY[D[i][3]]; ++y) {
                CNT[y][DX[D[i][0]]]++;
                CNT[y][DX[D[i][2]]]--;
            }
        }

        for (int i = 0; i < B; ++i) {
            for (int j = 1; j < A; ++j) {
                CNT[i][j] += CNT[i][j-1];
            }
        }


        ll ans = 0;
        auto add = [&](int top, int bot, int beg, int diff) {
            if (L > top || R <= bot) return;
            if (L > bot) bot = L;
            if (R < top) {
                beg += diff * (top - R);
                top = R;
            }

            int end = beg + diff * (top - bot - 1);
            ll chg = ll(beg + end) * (top - bot) / 2;
            ans += chg;
        };

        for (int i = 0; i < B-1; ++i) {
            for (int j = 0; j < A-1; ++j) {
                if (CNT[i][j]) {
                    int a = AX[j+1] + AY[i+1];
                    int b = AX[j] + AY[i+1];
                    int c = AX[j+1] + AY[i];
                    int d = AX[j] + AY[i];
                    int w = min(AY[i+1]-AY[i], AX[j+1]-AX[j]);
                    add(a, max(b,c), 0, 1);
                    add(max(b,c), min(b,c), w, 0);
                    add(min(b,c), d, w, -1);
                }
            }
        }
        cout << ans << endl;
    }
};
