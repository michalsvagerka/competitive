#include "../l/lib.h"
#include "../l/mod.h"

constexpr int MX = 512;
class ModCounters {
public:
    vector<FieldMod> conv(const vector<FieldMod>&A, const vector<FieldMod>&B) {
        vector<FieldMod> C(MX, 0);
        for (int i = 0; i < MX; ++i) {
            for (int j = 0; j < MX; ++j) {
                C[i+j-(MX*(i+j>=MX))] += A[i]*B[j];
            }
        }
        return C;
    }

    int findExpectedSum(vector <int> P, int A0, int X, int Y, int N, int K) {
        vector<ll> A(N);
        A[0] = A0;
        for (int i = 1; i < N; ++i) A[i] = (A[i-1] * X + Y) % 1812447359;

        vector<int> S = P;
        for (int i = P.size(); i < N; ++i) S.push_back(A[i] % MX);

        vector<int> C(MX, 0);
        for (int i = 0; i < N; ++i) C[S[i]]++;

        vector<FieldMod> R(MX, 0);
        R[0] = 1;
        vector<FieldMod> Pow(MX, 0);
        Pow[0] = FieldMod{N-1}/FieldMod{N};
        Pow[1] = FieldMod{1}/FieldMod{N};
        while (K) {
            if (K&1) {
                R = conv(R, Pow);
            }
            Pow = conv(Pow, Pow);
            K /= 2;
        }

        FieldMod ans = 0;
        for (int i = 0; i < MX; ++i) {
            for (int j = 0; j < MX; ++j) {
                ans += R[j] * FieldMod{C[i]} * (i+j-MX*(i+j>=MX));
            }
        }


        return (ui)ans;
    }
    void solve(istream& cin, ostream& cout) {
        cout << findExpectedSum({33},0,0,0,1,10) << '\n';
        cout << findExpectedSum({0, 511},0,0,0,2,1) << '\n';
        cout << findExpectedSum({0},1001,1001,1001,2,2) << '\n';
        cout << findExpectedSum({},3583,1000,1812447358,2,2) << '\n';
        cout << findExpectedSum({100, 101},5000,50000,100000,1000,1000) << '\n';
        cout << findExpectedSum({},100000000,100000000,100000000,10,1000) << '\n';
        cout << findExpectedSum({},501296088,234548363,703491623,2000000,1894643) << '\n';
    }
};
