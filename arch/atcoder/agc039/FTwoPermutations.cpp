#include "../l/lib.h"
#include "../l/util.h"
#include "../l/dinic.h"

/** Project selection problem.
 *  =========================
 *
 * Let A_i be profit (or cost) of a project i,
 * and let (u,v) mean: cannot do project u without also doing project v (v is prerequisite of u)
 * If (u,v) don't form a dag, contract scc first.
 *
 * Otherwise, build a flow graph, with each project having single node, and:
 *   if A_i > 0: put edge (source, i) with capacity A_i
 *   if A_i < 0: put edge (i, sink) with capacity -A_i
 *   for (u,v): put edge (u,v) with infinite capacity
 *
 * The maximum profit is (sum of all project costs) - (max flow)
 *
 */
class FTwoPermutations {
public:
    void solve(istream& cin, ostream& cout) {
        // if P[i] = Q[i] = i, ignore i
        // if P[i] != Q[i] for rest, then done
        // if P[i] = Q[i] != i, we try to set A[i] = P[i] or B[i] = Q[i] and see where that gets us
        // setting A[i] = P[i] fixes the whole cycle containing "i" in A[i]


        /* i is ok if:
         *
         *  P[i] == Q[i] != i => C[i] && !D[i]
         *  P[i] == Q[i] != i => !C[i] && D[i]
         *  P[i] = i != Q[i] => D[i]
         *  Q[i] = i != P[i] => C[i]
         *  i != P[i] != Q[i] != i => always
         *
         */

        /**
         *    0                 C[i]+(C[i]^D[i])
         *    D[i]+(C[i]^D[i])  C[i]+D[i]
         *
         */

        /*
         * each C[j] has score
         * each D[j] has score
         * each C[j]&D[j] has penalty 2*(P[i]==Q[i]) */


        int N; cin >> N;
        vector<int> P(N), Q(N); cin >> P >> Q;
        UnionFind UP(N), UQ(N);
        for (int i = 0; i < N; ++i) {
            UP.unite(i,P[i]);
            UQ.unite(i,Q[i]);
        }

        int ans = 0;
        map<pii, int> R;
        for (int i = 0; i < N; ++i) {
            if (P[i] == Q[i]) {
                if (P[i] != i) {
                    R[{UP.find(i), UQ.find(i)}] += 2;
                    R[{-1, UQ.find(i)}]--;
                    R[{UP.find(i), -1}]--;
                    ans++;
                } else {
                    // this is never a point
                }
            } else if (P[i] == i) {
                R[{-1, UQ.find(i)}]--;
                ++ans;
            } else if (Q[i] == i) {
                R[{UP.find(i), -1}]++;
            } else {
                R[{-1, UQ.find(i)}]--;
                R[{UP.find(i), UQ.find(i)}]++;

                // this is always a point, except if A[i]=i && B[i]=i
                ++ans;
            }
        }

        /* By Default, all A[i] = i && B[i] = Q[i]
         * This means that we get:
         *    - all bonuses for case Q[i] != P[i] == i;
         *        - picking {-1, UQ.find(i)} has penalty -x
         *    - all bonuses for case Q[i] == P[i] != i
         *        - picking {-1, UQ.find(i)} has penalty -x
         *        - picking {UP.find(i), -1} has penalty -x
         *        - there is a project {UP.find(i),UQ.find(i)} that has bonus 2*x
         *    - no bonus for case P[i] != Q[i] == i
         *        - picking {UP.find(i), -1} has bonus +x */
        map<pii, int> I;
        for (auto r: R) {
            int i = I.size();
            I[r.x] = i+2;
        }

        int left = 0, right = 0;
        Dinic<int> X(2 + R.size());
        for (auto r: R) {
            if (r.y < 0) {
                left += -r.y;
                X.AddEdge(I[r.x], 1, -r.y);
            } else if (r.y > 0) {
                right += r.y;
                X.AddEdge(0, I[r.x], r.y);
            }

            if (r.x.x != -1 && r.x.y != -1) {
                X.AddEdge(I[r.x], I[{-1,r.x.y}], 1000000);
                X.AddEdge(I[r.x], I[{r.x.x,-1}], 1000000);
            }
        }

        int flow = X.GetMaxFlow(0, 1);

        cout << ans + right - flow << endl;
    }
};
