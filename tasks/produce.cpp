#include "../l/lib.h"
#include "../l/random.h"
#include "../l/fft.h"

typedef Field<4194304001u> F;


constexpr bool fast = true;

class produce {
public:
    int B, T;
    vector<int> A;
    vector<vector<pii>> Q;
    // 0 - and, 1 - or, 2 - xor

    vector<F> S;

    void decode(int two, int three, int b) {
        if (b == B) {
            S[three] = A[two];
        } else {
            decode(two * 2, three * 3, b + 1);
            decode(two * 2 + 1, three * 3 + 1, b + 1);
        }
    }

    F encode(int q, int b, int three) {
        if (b == -1) {
            return S[three];
        } else {
            F ans = 0;
            for (int i = 0; i < 3; ++i) {
                if ((Q[q][b].x == 0 && (i == 2) == Q[q][b].y)
                    || (Q[q][b].x == 1 && (i != 0) == Q[q][b].y)
                    || (Q[q][b].x == 2 && (i == 1) == Q[q][b].y)) {
                    ans += encode(q, b-1, 3 * three + i);
                }
            }
            return ans;
        }
    }

    ui brute(int q, int b, int two, int val) {
        if (b == B) {
//            cerr << two << ' ' << val << endl;
            return A[two];
        } else {
            int r = (val >> b)&1;
            ui ans = 0;
            for (int i = 0; i < 2; ++i) {
                if ((Q[q][b].x == 0 && (i&r) == Q[q][b].y)
                    || (Q[q][b].x == 1 && (i|r) == Q[q][b].y)
                    || (Q[q][b].x == 2 && (i^r) == Q[q][b].y)) {
                    ans += brute(q, b+1, two | (i<<b), val);
                }
            }
            return ans;
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> B >> T;
        std::mt19937 rng{12345};
        uniform_int_distribution<int> R1{0,10}, R2{0,2}, R3{0,1};
        A.resize(1<<B);
        Q.resize(T);
        for (int i = 0; i < (1<<B); ++i) A[i] = R1(rng);
        for (int i = 0; i < T; ++i) {
            for (int j = 0; j < B; ++j) {
                Q[i].emplace_back(R2(rng), R3(rng));
            }
        }

//        cout << A;
//        cout << Q;

        vector<ui> Ans(T);
        if (fast) {
            int pt = 1;
            for (int i = 0; i < B; ++i) pt *= 3;
            S = vector<F>(pt, 0);
            decode(0, 0, 0);
            FFT<4194304001u> Conv;
            Conv.fft(S);
            for (auto &s : S) s *= s;
            Conv.fft(S, true);
            for (int i = 0; i < T; ++i) {
                Ans[i] = (ui)encode(i, B-1, 0);
            }
        } else {
            for (int i = 0; i < T; ++i) {
//                cerr << "T " << i << endl;
                Ans[i] = 0;
                for (int j = 0; j < (1<<B); ++j) {
                    Ans[i] += A[j] * brute(i, 0, 0, j);
                }
            }
        }
        cout << Ans[0];
    }
};
