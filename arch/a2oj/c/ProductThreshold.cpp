#include "../l/lib.h"
#include "../l/fenwick.h"

class ProductThreshold {
public:
    long long subarrayCount(int N, int limit, vector <int> Aprefix, int spread, int offset) {
        vector<int> A(N);
        int p = Aprefix.size();
        for (int i = 0; i < p; ++i) {
            A[i] = Aprefix[i];
        }


        int seed = abs(A[p-1]);
        for (int i = p; i < N; ++i) {
            seed = (seed * 1103515245LL + 12345) % (1LL<<31);
            A[i] = (seed % spread) + offset;
        }

        vector<int> P(N), F(N+1), Z(N+1);
        int q = N, z = N;
        for (int i = N-1; i >= 0; --i) {
            if (A[i] != 1 && A[i] != -1) q = i;
            if (A[i] == 0) z = i;
            Z[i] = z;
            P[i] = q;
        }

        Z[N] = N;

        F[0] = 1;
        for (int i = 0; i < N; ++i) {
            if (A[i] >= 0) F[i+1] = F[i];
            if (A[i] < 0) F[i+1] = -F[i];
            A[i] = abs(A[i]);
        }


        Fenwick<int> G(N+1, 0), I(N+1, 0);
        for (int i = 0; i <= N; ++i) {
            if (F[i] == 1) G.add(i, 1);
            if (F[i] == -1) I.add(i, 1);
        }

//        cerr << F << Z;

        ll ans = 0;
        for (int j = 0; j < N; ++j) {
            int k = P[j];
            if (k == N) {
                ans += N-j;
                continue;
            }

            ll val = A[k];
            while (val <= limit) {
                if (val == 0) { k = N; break; }
                if (k == N-1) { k = N; break; }
                k = P[k+1];
                if (k == N) break;
                val *= A[k];
            }


            ans += k-j;
            if (k != N) {
                int e = Z[k+1];
                if (F[j] == 1) ans += I.range(k + 1, e);
                if (F[j] == -1) ans += G.range(k + 1, e);
                ans += N - e;
            }
        }
        return ans;
    }


    void solve(istream& cin, ostream& cout) {
        int N, limit, M, spread, offset;
        cin >> N >> limit >> M;
        vector <int> Aprefix(M);
        cin >> Aprefix >> spread >> offset;
        cout << subarrayCount(N, limit, Aprefix, spread, offset) << '\n';
    }
};
