#include "../../../l/lib.h"
 #include "../../../l/mincostmaxflow.h"

class bitsofmerryengland {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M; cin >> N >> M;
        vector<int> A(N);
        map<int,int> L;
        cin >> A;

        MinCostMaxFlow<int> F(4*N+1);
        for (int i = 0; i < N; i++) {
            F.AddEdge(4*i, 4*i+1, M, 0);
            F.AddEdge(4*i+1, 4*i+4, M, 0);
            F.AddEdge(4*i+1, 4*i+2, 1, __builtin_popcount(A[i]));
            F.AddEdge(4*i+2, 4*i+3, 1, -100);
            F.AddEdge(4*i+3, 4*i+4, 1, 0);

            auto it = L.find(A[i]);
            if (it != L.end()) F.AddEdge(4*it->y+3, 4*i+2, 1, 0);
            L[A[i]] = i;
        }

        auto f = F.GetMaxFlow(0, 4*N);
        map<int,int> I;
        vector<bool> W(M, true);
        vector<string> C;

        for (auto e: F.GetEdgesWithFlow()) {
            ui u = get<0>(e), v = get<1>(e);
            ui j = u/4;
            if (u%4 == 1 && v%4 == 2) {
                for (int i = 0; i < M; ++i) {
                    if (W[i]) {
//                        cout << __builtin_popcount(A[j]) << ' ';
                        stringstream SS; SS << char(i+'a') << '=' << A[j];
                        C.push_back(SS.str());
                        I[A[j]] = i;
                        W[i] = false;
                        break;
                    }
                }
            } else if (u%4 == 3 && v%4 == 0) {
                int i = I[A[j]];
                W[i] = true;
            } else if (u%4 == 2) {
                stringstream SS; SS << "print(" << char(I[A[j]]+'a') << ')';
                C.push_back(SS.str());
            }
        }
        f.y += 100*N;
        cout << C.size() << ' ' << f.y << endl;
        for (string &c:C) cout << c << '\n';
    }
};
