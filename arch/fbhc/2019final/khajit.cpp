#include "../l/lib.h"

class khajit {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            string X; cin >> X;
            string Y; cin >> Y;

            ll ans = 0;
            for (int i = 0; i < N; ++i) {
                vector<int> AX, AY, BX, BY;
                for (int j = 0; j < M; ++j) {
                    if (X[M*i+j+1] == 'A') AX.push_back(j+1); else BX.push_back(j+1);
                    if (Y[M*i+j+1] == 'A') AY.push_back(j+1); else BY.push_back(j+1);
                }
                reverse(AX.begin(),AX.end());
                reverse(AY.begin(),AY.end());
                reverse(BX.begin(),BX.end());
                reverse(BY.begin(),BY.end());
                while (AX.size() < AY.size()) AX.push_back(0);
                while (AY.size() < AX.size()) AY.push_back(0);
                while (BX.size() < BY.size()) BX.push_back(0);
                while (BY.size() < BX.size()) BY.push_back(0);

                for (int j = 0; j < AX.size(); ++j) {
                    ans += abs(AX[j] - AY[j]);
                }
                for (int j = 0; j < BX.size(); ++j) {
                    ans += abs(BX[j] - BY[j]);
                }
            }
            cout << "Case #" << t+1 << ": " << ans/2 << endl;
        }
    }
};
