#include "../l/lib.h"

#include "../l/geo.h"
typedef long double ld;

class ERandomPawn {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N, 0), B(N, 100);
        cin >> A >> B;
        int maxPos = max_element(A.begin(),A.end())-A.begin();
        rotate(A.begin(),A.begin()+maxPos,A.end());
        rotate(B.begin(),B.begin()+maxPos,B.end());
        A.push_back(A[0]);
        B.push_back(B[0]);
        vector<ld> C(N+1, 0), D(N+1, 0);
        for (int i = 1; i < N; ++i) C[i+1] = 2*B[i] + 2*C[i] - C[i-1];
        for (int i = 0; i <= N; ++i) D[i] = A[i] - C[i];
        vector<int> S{0,1};
        for (int i = 2; i <= N; ++i) {
            Point<ld> C{i, D[i]};
            while (S.size() >= 2) {
                int h = S.size();
                Point<ld> A{S[h-2], D[S[h-2]]};
                Point<ld> B{S[h-1], D[S[h-1]]};
                if (orientation(A,B,C) == 1) S.pop_back();
                else break;
            }
            S.push_back(i);
        }

        int h = S.size();
        ld tot = 0;
        for (int i = 0; i < h-1; ++i) {
            tot += D[S[i]] * (S[i+1]-S[i]);
            tot += ll(S[i+1]-S[i])*(S[i+1]-S[i]-1)*(D[S[i+1]]-D[S[i]])/(S[i+1]-S[i])/2;
        }

        for (int i = 0; i < N; ++i) tot += C[i];
        cout << fixed << setprecision(20) << tot / N << endl;
    }
};
