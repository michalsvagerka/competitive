#include "../l/lib.h"
// #include "../l/mod.h"
class FPassports {
public:

    void solve(istream& cin, ostream& cout) {
        int N, P; cin >> N >> P;
        vector<pair<pii,pii>> T(N);  // first day of trip, end of trip, days for consulate, trip ID
        for (int i = 0; i < N; ++i) {
            cin >> T[i].x.x >> T[i].x.y >> T[i].y.x;
            T[i].x.y += T[i].x.x;
            T[i].y.y = i;
        }
        sort(T.begin(),T.end());

        vector<pii> ByLength(N); // days for consulate, tripID
        for (int i = 0; i < N; ++i) {
            ByLength[i] = {T[i].y.x, i};
        }
        sort(ByLength.begin(),ByLength.end());

        int inf = 2e9;

        // mask of visas in the passport -> earliest time to achieve this, last visa ID, last visa ID application
        vector<pair<int,pii>> W(1<<N, {inf,{-1,0}});

        vector2<int> Bad(N, N, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    // we apply for i right after j. Is k underway when the passport gets back?
                    int apply = T[j].x.y;
                    int passBack = apply + T[i].y.x;
                    if (apply <= T[k].x.x && T[k].x.x <= passBack) {
                        Bad[i][j] |= 1<<k;
                    }
                }
            }
        }

        W[0].x = 1;
        for (int b = 0; b < (1<<N); ++b) {
            if (W[b].x == inf) continue;

            // find the first trip that is not already finished by time W[b].x
            int first = 0;
            while (first < N && (T[first].x.y < W[b].x)) ++first;

            // we cannot apply right now if we are currently on a trip
            int bar = first;
            while (bar < N && T[bar].x.y - 1 < W[b].x) ++bar;
            bool canApplyRightAway = !(bar < N && T[bar].x.x <= W[b].x);

            int earliestAfter = first;
            // find the earlier trip that starts on or after 'apply' that we have in this passport
            while (earliestAfter < N && (T[earliestAfter].x.x < W[b].x || ((b & (1<<earliestAfter)) == 0))) ++earliestAfter;

            int k = first;
            for (int gX = 0; gX < N; ++gX) {
                int g = ByLength[gX].y;
                if (T[g].x.y < W[b].x || (b & (1 << g))) continue;

                int passBackNow = W[b].x + T[g].y.x;
                if (T[g].x.x <= passBackNow) continue; // too late to get the passport back for this trip

                if (canApplyRightAway && !(earliestAfter != N && W[b].x <= T[earliestAfter].x.x && T[earliestAfter].x.x <= passBackNow)) {
                    W[b|(1<<g)] = min(W[b|(1<<g)], {passBackNow, {g, W[b].x}});
                } else {
                    while (k < N) {
                        // apply for visa right away or after returning from trip k
                        int apply = T[k].x.y;
                        int passBack = apply + T[g].y.x;
                        if (T[g].x.x <= passBack) break; // too late to get the passport back for this trip

                        // we cannot apply at all when there are back to back trips,
                        // or if there is a visa in this passport for a trip that starts before we get the passport back
                        if ((k == N-1 || T[k+1].x.x != apply) && !(b & Bad[g][k])) {
                            // we found the earliest possible application time, we don't care about later times
                            W[b|(1<<g)] = min(W[b|(1<<g)], {passBack, {g, apply}});
                            break;
                        } else k++;
                    }
                }
            }
        }

        vector<pii> Ans(N);
        if (P == 1) {
            if (W[(1<<N)-1].x == inf) {
                cout << "NO\n";
                return;
            } else {
                int m = (1<<N)-1;
                while (m != 0) {
                    Ans[T[W[m].y.x].y.y] = {1, W[m].y.y};
                    m ^= 1<<W[m].y.x;
                }
            }
        }

        if (P == 2) {
            bool found = false;
            for (int m = 0; m < (1<<N); ++m) {
                int c = ((1<<N)-1)^m;
                if (W[m].x != inf && W[c].x != inf) {
                    while (m != 0) {
                        Ans[T[W[m].y.x].y.y] = {1, W[m].y.y};
                        m ^= 1<<W[m].y.x;
                    }

                    while (c != 0) {
                        Ans[T[W[c].y.x].y.y] = {2, W[c].y.y};
                        c ^= 1<<W[c].y.x;
                    }

                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "NO\n";
                return;
            }
        }


        cout << "YES\n";
        for (pii ans:Ans) cout << ans << endl;
    }
};
