#include "../l/lib.h"
#include "../l/random.h"
#include "../l/nsegtree.h"

class DDreamoonLikesStrings {
public:

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            string S; cin >> S;
            int N = S.size(), j = 0;
            vector<int> Same, C(26, 0), stack, Ones(N, 2);
            vector<pii> Solve;
            AssignSumTree<int> ASS(Ones, 0, 0);
            for (int i = 1; i < N; ++i) {
                if (S[i] == S[i-1]) {
                    Same.push_back(i);
                    C[S[i]-'a']++;
                }
            }

            auto add = [&](int a, int b){
                int x = a == 0 ? 0 : ASS.get(0, a-1);
                int y = ASS.get(0, b);
                Solve.push_back({x-a+1, y-b-1});
                ASS.put(a,b,1);
            };

            int mx = *max_element(C.begin(),C.end());
            int sm = Same.size();
            while (true) {
                int X = stack.size();
                if (X >= 2 && S[stack[X-1]] != S[stack[X-2]]) {
                    C[S[stack[X - 1]]-'a']--;
                    C[S[stack[X - 2]]-'a']--;
                    int newMx = *max_element(C.begin(),C.end());
                    if (max(mx, (sm+1)/2) != max(newMx+1, (sm+1)/2)) {
                        C[S[stack[X - 1]] - 'a']++;
                        C[S[stack[X - 2]] - 'a']++;
                    } else {
                        add(stack[X-2], stack[X-1] - 1);
                        stack.pop_back(); stack.pop_back();
                        mx = newMx;
                        sm -= 2;
                        continue;
                    }
                }

                if (j != Same.size()) {
                    stack.push_back(Same[j++]);
                } else {
                    break;
                }
            }

            for (int i: stack) add(0, i-1);
            add(0, N-1);

            cout << Solve.size() << '\n';
            for (pii soln: Solve) cout << soln << '\n';
        }
    }
};
