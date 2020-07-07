#include "../../../l/lib.h"

class GBalancedDistribution {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N); cin >> A;
        int one = 0;
        for (int a: A) one += a;
        one /= N;

        for (int i = 0; i < N; ++i) A.push_back(A[i]);
        N *= 2;

        vector<int> Pref(N+1, 0);
        for (int i = 0; i < N; ++i) Pref[i+1] = Pref[i] + A[i];

        vector<int> Next(N+1, N);
        for (int i = N - 1; i >= 0; --i) {
            if (A[i] == one) Next[i] = Next[i+1];
            else Next[i] = i;
        }


        pii best{2*N, -1};
        for (int i = 0; i < K; ++i) {
            int j = Next[i];
            int tot = 0;
            do {
                int c = 1;
                int k = j + K;
                while (k - i < N/2 && Pref[k] - Pref[j] != (k - j) * one) {
                    k += K - 1;
                    ++c;
                }
                tot += c;

                j = Next[k];
            } while (j-i < N/2);

            best = min(best, {tot, i});
        }

        cout << best.x << '\n';


        int s = 0;
        int beg = best.y, j = Next[best.y];
        do {
            int k = j + K;
            while (k - beg < N/2 && Pref[k] - Pref[j] < (k-j) * one) k += K-1;
            int overRight = Pref[k] - Pref[j] - (k-j)*one;
            int overLeft = Pref[k] - Pref[k - K] - K*one - overRight;
            cout <<  (k - K)%(N/2) << ' ' << one+overLeft;
            for (int i = 0; i < K-2; ++i) cout << ' ' << one;
            cout << ' ' << one + overRight << '\n';
            Pref[k] -= A[k-1];
            A[k-K] = one+overLeft;
            A[k-1] = one+overRight;
            Pref[k] += A[k-1];
            for (int z = k - K - (K-1); z >= j+1; z -= K-1) {
                overLeft = Pref[k] - Pref[z] - (k-z)*one - overRight;
                cout << z%(N/2) << ' ' << one + overLeft;
                for (int i = 0; i < K-1; ++i) cout << ' ' << one;
                cout << '\n';
            }
            if (A[k-1] == one) j = Next[k];
            else j = k-1;
            if (s++ > 10) break;
        } while (j - beg < N/2);
    }
};
