#include "../l/lib.h"
#include "../l/mod.h"

class Renovations {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, K, A, B;
            cin >> N >> K >> A >> B;
            vector<int> P(N-1); cin >> P;
            for (int &p: P) --p;
            --A; --B;
            vector<int> QA{A}, QB{B};
            while (QA.back() != 0) {
                int a = P[QA.back()-1];
                QA.push_back(a);
            }
            while (QB.back() != 0) {
                int b = P[QB.back()-1];
                QB.push_back(b);
            }
            reverse(QA.begin(),QA.end());
            reverse(QB.begin(),QB.end());
            int lca = 0;
            while (lca < QA.size() && lca < QB.size() && QA[lca] == QB[lca]) ++lca;

            int RA = QA.size();
            int RB = QB.size();
            int UA = RA - lca;
            int UB = RB - lca;
            FieldMod ans = 0;
            RA--;
            RB--;

            vector<FieldMod> EX(N);
            for (int i = 0; i < N; ++i) EX[i] = FieldMod{i}.pow(K);

            ans += EX[N-UA-UB-1] * (UA + UB);
            for (int i = 1; i <= UA; ++i) {
                FieldMod pst = EX[N-i] - EX[N-i-1];
                ans += i * pst;
            }

            for (int i = 1; i <= UB; ++i) {
                FieldMod pst = EX[N-i] - EX[N-i-1];
                ans += i * pst;
            }

            for (int i = 1; i <= UA; ++i) {
                FieldMod pst = EX[N-RB-i] - EX[N-RB-i-1];
                ans += RB * pst;
            }

            for (int i = 1; i <= UB; ++i) {
                FieldMod pst = EX[N-RA-i] - EX[N-RA-i-1];
                ans += RA * pst;
            }
            
            for (int j = UB + 1; j <= RB; ++j) {
                FieldMod pst = EX[N-j] - EX[N-j-1] - EX[N-j-UA] + EX[N-j-UA-1];
                ans += j * pst;
            }

            for (int j = UA + 1; j <= RA; ++j) {
                FieldMod pst = EX[N-j] - EX[N-j-1] - EX[N-j-UB] + EX[N-j-UB-1];
                ans += j * pst;
            }

            ans /= EX[N-1];
            cout << "Case #" << t+1 << ": " << ans << '\n';
        }
    }
};
