#include "../l/lib.h"
#include "../l/dinic.h"

class kolace {
public:
    void solve(istream& cin, ostream& cout) {
        ui A,B,K; cin >> A >> B >> K;
        Dinic<ll> D(A+B+2, A+B+A*B-K);
        vector2<bool> E(A,B,true);
        for (ui i = 0; i < K; ++i) {
            int a,b; cin >> a >> b; --a; --b;
            E[a][b] = false;
        }


        for (int i = 0; i < A; ++i) {
            for (int j = 0; j < B; ++j) {
                if (E[i][j]) D.AddEdge(i+1,j+A+1,1e14);
            }
        }

        ll tot = 0;
        for (ui i = 0; i < A; ++i) {
            int n; cin >> n;
            tot += n;
            D.AddEdge(0,i+1,n);
        }

        for (ui i = 0; i < B; ++i) {
            int n; cin >> n;
            tot += n;
            D.AddEdge(i+A+1,A+B+1,n);
        }

        ll flow = D.GetMaxFlow(0, A+B+1);
        auto cut = D.GetMinCut(0);
        // cerr << cut;
        vector<ui> IA,IB;
        for (int i = 1; i <= A; ++i) {
            if (cut[i]) IA.push_back(i);
        }
        for (int i = 1; i <= B; ++i) {
            if (!cut[i+A]) IB.push_back(i);
        }

        cout << tot-flow << '\n' << IA.size() << '\n' << IA << IB.size() << '\n' << IB;
    }
};
