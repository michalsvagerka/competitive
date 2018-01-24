#include "../l/lib.h"
// #include "../l/mod.h"

class rotator {
public:
    string A, B;
    vector<bool> Z;

    /** Let T(A,B) == true iff A can be modified to B. Clearly, T is equivalence.
     *
     * Let A = A_1 A_2, B = B_1 B_2.
     *
     * We have T(A_1, B_1) && T(A_1, B_2) && T(A_2, B_1) => T(A_2, B_2)
     * Thus T(A_1, B_1) && T(A_1, B_2) && not T(A_2, B_2) => not T(A_2, B_1)
     * That is T(A_1, B_1) && not T(A_2, B_2) => not (T(A_2, B_1) && T(A_1, B_2))
     *  We only have at most three checks per recursion level.
     *
     *  T(n) = 2T(n/2) + O(1) ===(master thm)==> T(n) = O(n^1.6)
     */
    bool solve(ui Ai, ui Bi, ui Zi, ui size) {
        if (size == 1) return A[Ai] == B[Bi];
        ui s = size/2;
        if (!(Z[Zi + size - 2] = !solve(Ai, Bi, Zi, s))) {
            return solve(Ai + s, Bi + s, Zi + s - 1, s);
        } else {
            return solve(Ai, Bi + s, Zi, s) && solve(Ai + s, Bi, Zi + s - 1, s);
        }
    }

    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (ui t = 0; t < T; ++t) {
            cin >> A >> B;
            Z.resize(A.size() - 1);
            if (solve(0,0,0,A.size())) {
                cout << "Yes\n" << Z;
            } else {
                cout << "No\n";
            }
        }
    }
};
