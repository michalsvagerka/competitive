#include "../l/lib.h"
#include "../l/primes.h"
#include "../l/random.h"

class DTreasureIsland {
public:
    int N, M;
    vector<string> S;

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<string> S(N); cin >> S;
        vector2<int> X(N, M, 0);
        LargePrimes LP; 
        random_int R{0, (int)LP.size()-1};
        int att = 4;
        int zero = 0;
        for (int c = 0; c < att; ++c) {
            int P = LP[R(rng)];
            vector2<int> D(N, M, 0); D[0][0] = 1;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (i != N-1 && S[i+1][j] == '.') ( D[i+1][j] += D[i][j]) %= P;
                    if (j != M-1 && S[i][j+1] == '.') ( D[i][j+1] += D[i][j]) %= P; 
                }
            }

            vector2<int> E(N, M, 0); E[N-1][M-1] = 1;
            for (int i = N-1; i >= 0; --i) {
                for (int j = M-1; j >= 0; --j) {
                    if (i != 0 && S[i-1][j] == '.') ( E[i-1][j] += E[i][j]) %= P;
                    if (j != 0 && S[i][j-1] == '.') ( E[i][j-1] += E[i][j]) %= P;
                }
            }
            
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    X[i][j] += (ll(D[i][j]) * E[i][j]) % P == D[N-1][M-1];
                }   
            }
            zero += D[N-1][M-1] == 0;
        }
        
        if (zero == att) {
            cout << 0 << endl;
        } else {

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (i == 0 && j == 0) continue;
                    if (i == N-1 && j == M-1) continue;
                    if (X[i][j] == att) {
                        cout << 1 << endl;
                        return;
                    }
                }
            }
            cout << 2 << endl;
        }
        
        
        




    }
};
