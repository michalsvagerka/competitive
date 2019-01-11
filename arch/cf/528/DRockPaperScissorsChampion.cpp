#include "../l/lib.h"
#include "../l/fenwick.h"

class DRockPaperScissorsChampion {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        string S; cin >> S;
        vector<Fenwick<int>> F(3, Fenwick<int>(N));
        vector<set<int>> G(3);
        vector<int> C(255);
        C['R'] = 0; C['P'] = 1; C['S'] = 2;
        for (int i = 0; i < N; ++i) {
            F[C[S[i]]].add(i, 1);
            G[C[S[i]]].insert(i);
        }

        // if P has S on the left, and there is no R on the left, then it can't win
        // if P has S on the right, and there is no R on the right, then it can't win

        for (int i = 0; i <= Q; ++i) {
            int ans = N;
//            cout << S << endl;
//            cout << F[0].sum(N) << ' ' << F[1].sum(N) << ' ' << F[2].sum(N) << endl;
            for (int j = 0; j < 3; ++j) {
                int killedBy = (j+1)%3;
                int kills = (j+2)%3;
                if (G[killedBy].empty()) continue;
                if (G[kills].empty()) {
//                    cout << "saviour " << kills << " does not exist, killing " << F[j].sum(N) << endl;
                    ans -= F[j].sum(N);
                } else {
                    int leftKiller = *G[killedBy].begin();
                    int leftSaviour = *G[kills].begin();
                    if (leftSaviour > leftKiller) {
//                        cout << "removing " << j << " in range " << leftKiller << ' ' << leftSaviour << ' ' << F[j].range(leftKiller, leftSaviour) << endl;
                        ans -= F[j].range(leftKiller, leftSaviour);
                    }
                    
                    int rightKiller = *G[killedBy].rbegin();
                    int rightSaviour = *G[kills].rbegin();
                    if (rightKiller > rightSaviour) {

//                        cout << "removing " << j << " in range " << rightSaviour << ' ' << rightKiller << ' ' << F[j].range(rightSaviour, rightKiller) << endl;
                        ans -= F[j].range(rightSaviour, rightKiller);
                    }
                }
            }
            cout << ans << '\n';
            
            if (i != Q) {
                int a; char c;
                cin >> a >> c;
                --a;
                G[C[S[a]]].erase(a);
                F[C[S[a]]].add(a, -1);
                S[a] = c;
                G[C[S[a]]].insert(a);
                F[C[S[a]]].add(a, 1);
            }
        }
        
    }
};
