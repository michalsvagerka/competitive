#include "../l/lib.h"
#include "../l/consttree.h"

class cold {
public:
    int N;
    vector<int> H, F;
    ConstTree<int, MaxQOp<int>> HH{{1}};

    bool goLeft(int cur, pii range, ll over) {
        if (over < 0) return false;
        if (cur == 0) {

            return goRight(cur, range)
        }
        pair<ll, int> bestResult = {-1,-1};
    }

//
//     bool goLeft(int cur, pii range, ll over) {
//         if (cur == 0) {
//             return goRight(cur, range, over);
//         }
//         // TODO: if first move, then set F[range.x] = H[range.x]
//
//         over = over + F[cur] - H[cur-1];
//
//         if (range.x != cur) {
//             // move yourself to range.x
//             auto x = AL[cur - 1][range.x];
//             if (over + x.x < 0) return false;
//             over += x.y;
//         }
//
//         // now F[range.x] == H[range.x]
//         ll crr = over;
//         pair<ll, int> bestResult = {-1, -1};
//         for (int j = range.x; j > 0; --j) {
//             crr += H[j] - H[j-1];
//             if (crr < 0) break;
//             auto y = AR[j-1][range.y];
//             if (crr + y.x >= 0) {
//                 ll before = crr + F[j-1] - H[j-1];
//                 if (before >= 0) {
//                     ll after = before + y.y;
//                     if (after >= bestResult.x) {
//                         bestResult = {after, j - 1};
//                     }
//                 }
//             }
//         }
//
//         if (bestResult.y != -1) {
//             if (goRight(bestResult.y, {bestResult.y, range.y}, bestResult.x)) return true;
//         }
//
//         return false;
//     }
//
//
//    bool goRight(int cur, pii range, ll over) {
//        if (cur == N-1) {
//            return goLeft(cur, range, over);
//        }
//
//        over = over + F[cur] - H[cur];
//
//        if (range.y != cur) {
//            // move yourself to range.x
//            auto x = AL[cur + 1][range.y];
//            if (over + x.x < 0) return false;
//            over += x.y;
//        }
//
//        // now F[range.x] == H[range.x]
//        ll crr = over;
//        pair<ll, int> bestResult = {-1, -1};
//        for (int j = range.y; j < N-1; ++j) {
//            crr += H[j-1] - H[j];
//            if (crr < 0) break;
//            auto y = AL[j+1][range.x];
//            if (crr + y.x >= 0) {
//                ll before = crr + F[j-1] - H[j-1];
//                if (before >= 0) {
//                    ll after = before + y.y;
//                    if (after >= bestResult.x) {
//                        bestResult = {after, j + 1};
//                    }
//                }
//            }
//        }
//
//        if (bestResult.y != -1) {
//            if (goLeft(bestResult.y, {range.x, bestResult.y}, bestResult.x)) return true;
//        }
//
//        return false;
//    }

//    bool go(bool left, int cur, pii range, ll over, vector<int> &F) {
//        pair<ll,int> best = {over, cur};
//        int i = cur;
//        ll carry = over;
//        int myEnd = left ? 0 : N-1;
//        int otherEnd = left ? N-1 : 0;
//        while (i != myEnd) {
//            if (H[i-left] <= carry + F[i]) {
//                carry = carry + F[i] - H[i-left];
//                i += left ? -1 : 1;
//                if (carry > best.x) best = {carry, i};
//            } else break;
//        }
//
//        cerr << "Go " << left << ' ' << i << endl;
//
//        if (i == myEnd) {
//            // got all the way
//            vector<int> FF = F;
//            ll crr = over;
//            walk(FF, crr, left, cur, myEnd);
//            if (walk(FF, crr, !left, myEnd, otherEnd)) return true;
//        }
//
//        if ((best.y < range.x || best.y > range.y) && best.y != myEnd) {
//            // got better than before
//            walk(F, over, left, cur, best.y);
//            if (go(!left, best.y, {min(best.y, range.x), max(best.y, range.y)}, over, F)) return true;
//        }
//
//        return false;
//    }


    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int M; cin >> N >> M;
            F.resize(N); cin >> F;
            H.resize(N-1); cin >> H;

            HH = ConstTree<int,MaxQOp<int>>(H);
            cout << "Case #" << t+1 << ": ";
            for (int i = 0; i < M; ++i) {
                int X, Y; cin >> X >> Y;
                --X;


//                vector<int> G1 = F, G2 = F;
//                bool res = go(true, X, {X,X}, Y, G1) || go(false, X, {X,X}, Y, G2);
//                cout << "NY"[res];
//                if (i == 21) cerr << X << ' ' << Y << ' '  << res << endl;

            }
            cout << endl;
        }
    }
};
