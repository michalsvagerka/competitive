#include "../l/lib.h"
#include "../l/nsegtree.h"

constexpr int P = 100001;

void ApplyTag(int &a, int b, ui) {
    if (b == 1) a = 1;
    else if (b == 2) a = 2;
    else if (b == 3) a = a ^ 3;
}

void CombineTag(int &a, int b) {
    if (b == 1 || b == 2) a = b;
    else if (b == 3) a = a ^ 3;
}

int CombineValues(int a, int b) {
    return a+b;
}

class EHotIsCold {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<int> A(N); cin >> A;
        LSegTree<int, int, CombineTag, ApplyTag, CombineValues> T(P, 0, 0);

        auto perform_swap = [&](int a, int b) { T.put(a, b, 3); };
        auto set_right = [&](int a, int b) { T.put(a, b, 1); };
        auto set_left = [&](int a, int b) { T.put(a, b, 2); };

        for (int i = 0; i < Q; ++i) {
            char s; cin >> s;
            int x; cin >> x;
            int l = s == '>' ? x + 1 : -P;
            int r = s == '<' ? x - 1 : P;
            if (l <= 0 && r >= 0) {
                perform_swap(0, min(-l, r));
                if (abs(l) > abs(r)) {
                    set_right(abs(r) + 1, abs(l));
                } else if (abs(r) > abs(l)) {
                    set_left(abs(l) + 1, abs(r));
                }
            } else if (l > 0) {
                set_left(l, r);
            } else if (r < 0) {
                set_right(abs(r), abs(l));
            }
        }

        vector<int> S(P+1);
        for (int i = 0; i <= P; ++i) {
            S[i] = T.get(i);
        }
        
        for (int i = 0; i < N; ++i) {
            int s = A[i];
            int g = abs(s);
            int r = S[g];
            if (r == 1) {
                A[i] = abs(A[i]);
            } else if (r == 2) {
                A[i] = -abs(A[i]);
            } else if (r == 3) {
                A[i] = -A[i];
            }
        }

        cout << A;
    }
};
