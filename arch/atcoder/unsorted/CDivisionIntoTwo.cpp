#include "../l/lib.h"
 #include "../l/mod.h"
#include "../l/random.h"

class CDivisionIntoTwo {
public:
    FieldMod smart(vector<ll> S, int N, ll A, ll B) {
        vector<int> NextSafeB(N), ForbiddenA(N, N);
        int j = 0;
        for (int i = 0; i < N; ++i) {
            while (j < N && S[j] < S[i] + B) ++j;
            NextSafeB[i] = j;

            // if i belongs to Y, all up to j-1 inclusive must belong to X
        }

        for (int i = 0; i < N-2; ++i) {
            if (S[i+2] < S[i] + A) {
                // a b c are less then A (and hence less than B) away, but two of those need to be in the same set
                return 0;
            }
        }

        j = N;
        for (int i = N-2; i >= 0; --i) {
            if (S[i+1] < S[i] + A) j = i;
            ForbiddenA[i] = j;
            // a block of X's starting here must end on j or earlier
        }
        
//        cerr << NextSafeB << ForbiddenA;
        
        vector<FieldMod> D(N+1, 0);
        // D[i] - the ways of covering first i elements such that i+1 is safe to assign to Y
        D[0] = 1;
        for (int i = 0; i < N; ++i) {
            // take A
            if (i == 0 || S[i] >= S[i-1] + A) D[i+1] += D[i];

            // take B
            if (i == N-1 || NextSafeB[i]-1 <= ForbiddenA[i+1]) D[NextSafeB[i]] += D[i];

//            if (i < N-1) cerr << NextSafeB[i] << ' ' << ForbiddenA[i+1] << endl;
            
//            cerr << D;
        }

        return D[N];
    }

    FieldMod slow(vector<ll> S, int N, int A, int B) {
        vector2<FieldMod> D(N, N+1, 0);
        D[0][0] = 1;
        D[0][1] = 1;
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (i == j) { // previous is in Y
                    if (i == 1 || S[i] >= S[i-2] + A) D[i][j] += D[i-1][j];
                } else {
                    if (S[i] >= S[i-1] + A) D[i][j] += D[i-1][j];
                }

                // put into Y
                if (j == 0 || S[i] >= S[j-1] + B) D[i][i+1] += D[i-1][j];
            }
        }

        FieldMod ans = 0;
        for (int i = 0; i <= N; ++i) {
            ans += D[N-1][i];
        }
        return ans;
    }

    void stress() {
        random_int RN{3, 10}, RA{4, 20}, RB{4, 20}, RD{4, 20};
        while (true) {
            int N = RN(rng);
            ll A = RA(rng), B = RB(rng);
            vector<ll> S(N, 0);
            for (int i = 1; i < N; ++i) {
                S[i] = S[i-1] + RD(rng);
            }
            if (A > B) swap(A, B);
            
            FieldMod a1 = smart(S, N, A, B);
            FieldMod a2 = slow(S, N, A, B);
            if (a1 == a2) {
                cout << "OK\n";
            } else {
                cout << N << ' ' << A << ' ' << B << '\n' << S;
                cout << a1 << ' ' << a2 << endl;
                break;
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
//        stress();
        
        int N;
        ll A, B;
        cin >> N >> A >> B;
        vector<ll> S(N); cin >> S;
        if (A > B) swap(A, B);
        cout << smart(S, N, A, B) << '\n';
    }
};
