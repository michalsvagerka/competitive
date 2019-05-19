#include "../l/lib.h"

class CStrangeSorting {
public:
    string S;
    void dsort(int a, int k, int d) {
        string T = S.substr(a,k);
        int j = 0;
        for (int i = 0; i < d; ++i) {
            for (int l = i; l < k; l += d) {
                S[a+j++] = T[l];
                cerr << l << ' ';
            }
        }
        cerr << endl;
    }

    vector<int> dsortperm(int N, int k, int d) {
        vector<int> Ans(N);
        int j = 0;
        for (int i = 0; i < d; ++i) {
            for (int l = i; l < k; l += d) {
                Ans[j++] = l;
            }
        }
        for (int i = k; i < N; ++i) Ans[i] = i;
        return Ans;
    }

    void apply(vector<int>&perm) {
        string T = S;
        for (int i = 0; i < S.size(); ++i) {
            S[i] = T[perm[i]];
        }
    }

    vector<int> rotperm(int N) {
        vector<int> Ans(N);
        for (int i = 0; i < N; ++i) {
            Ans[i] = (i+1)%N;
        }
        return Ans;
    }
    
    vector<int> mul(const vector<int> &A, const vector<int> &B) {
        vector<int> C(A.size());
        for (int i = 0; i < A.size(); ++i) {
            C[i] = A[B[i]];
        }
        return C;
    }
    
    vector<int> exp(vector<int> A, int P) {
        vector<int> R(A.size());
        for (int i = 0; i < A.size(); ++i) R[i] = i;
        while (P) {
            if (P&1) { R = mul(R,A); }
            P >>= 1;
            A = mul(A, A);
        }
        return R;
    }


    void solve(istream& cin, ostream& cout) {
        cin >> S;
        int N = S.size();
        vector<int> Rot = rotperm(N);
        int T; cin >> T;
        for (int i = 0; i < T; ++i) {
            int K, D; cin >> K >> D;
            vector<int> Perm = dsortperm(N, K, D);
            vector<int> Real = mul(Perm,Rot);
            vector<int> Pow = exp(Real, N-K+1);
            apply(Pow);
            rotate(S.begin(),S.begin()+K-1,S.end());
            cout << S << '\n';
        }
    }
};
