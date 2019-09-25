#include "../l/lib.h"
#include "../l/suffixarray.h"
#include "../l/random.h"

class EReversingAndConcatenating {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int K; cin >> K;
        string S; cin >> S;
        string Ans(N, 'z');
        char smallest = *min_element(S.begin(),S.end());
        for (int i = 0; i <= N; ++i) {
            string A = S;
            string T = A;
            reverse(T.begin(),T.end());
            A += T;
            A = A.substr(i, N);
            int w = 0;
            while (w < N && A[0] == A[w]) ++w;
            int z = w;
            for (int g = 1; g < K; ++g) {
                z *= 2;
                if (z > N) {
                    z = N;
                    break;
                }
            }
                
                
            A = string(z, A[0]) + A.substr(w, N-z);
            Ans = min(Ans, A);
        }

        cout << Ans << endl;
    }
};
