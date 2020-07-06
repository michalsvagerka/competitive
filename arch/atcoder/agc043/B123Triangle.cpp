#include "../l/lib.h"
#include "../l/random.h"

class B123Triangle {
public:
    void solve(istream& cin, ostream& cout) {
        int M; cin >> M;
        string S; cin >> S;

            int N = M;
            vector<int> A(N);
            for (int i = 0; i < N; ++i) {
                A[i] = S[i] - '0';
            }
                vector<int> B(N - 1);
                for (int i = 0; i < N - 1; ++i) {
                    B[i] = abs(A[i] - A[i + 1]);
                }
                swap(A, B);
                --N;

            int ans = 1;
            int one = count(A.begin(),A.end(),1);
            if (one == 0) {
                for (int &a: A) a /= 2;
                ans *= 2;
            }

            for (int &a: A) if (a == 2) a = 0;

            int t = 0;

        for (int i = 0; i <= N-1; ++i) {
            if (((N-1)&i)==i) t ^= A[i];
        }



        cout << t * ans << endl;
    }
};
