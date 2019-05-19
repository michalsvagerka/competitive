#include "../l/lib.h"
#include "../l/fft.h"
#include <numeric>

typedef Field<998244353> FF;

class ELadiesShop {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N); cin >> A;
        
        vector<int> C(M+1);
        vector<FF> B(2*M+1, 0);
        for (int a: A) B[a] = C[a] = 1;
        FFT<998244353> fft;
        fft.fft(B);
        for (int i = 0; i < B.size(); ++i) B[i] *= B[i];
        fft.fft(B, true);
        vector<int> Answer;
        for (int i = 1; i <= M; ++i) {
            if (B[i] != 0 && C[i] == 0) {
                cout << "NO\n";
                return;
            }

            if (B[i] == 0 && C[i] != 0) {
                Answer.push_back(i);
            }
        }
        cout << "YES\n" << Answer.size() << '\n' << Answer;
    }
};
