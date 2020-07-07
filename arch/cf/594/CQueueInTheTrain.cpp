#include "../../../l/lib.h"

class CQueueInTheTrain {
public:
    void solve(istream& cin, ostream& cout) {
        int N, P; cin >> N >> P;
        vector<int> A(N); cin >> A;
        set<pair<ll,ll>> Ev;
        for (int i = 0; i < N; ++i) {
            Ev.insert({A[i],i+1});
        }

        set<int> Q;
        deque<int> QQ;
        set<int> Anx;
        bool occ = false;
        vector<ll> Ans(N, -1);
        while (!Ev.empty()) {
            pair<ll,ll> e = *Ev.begin();
            Ev.erase(Ev.begin());

            if (e.y != 1000000) {
                if (Q.empty() || *Q.begin() > e.y) {
                    Q.insert(e.y);
                    QQ.push_back(e.y);
                } else {
                    Anx.insert(e.y);
                }
            } else {
                int q = QQ.front();
                QQ.pop_front();
                Q.erase(q);
                
                Ans[q-1] = e.x;
                occ = false;
            }
            
            if (!Anx.empty() && (Q.empty() || *Q.begin() > *Anx.begin())) {
                int a = *Anx.begin();
                Anx.erase(a);
                Q.insert(a);
                QQ.push_back(a);
            }
            
            if (!occ) {
                if (!QQ.empty()) {
                    Ev.insert({e.x+P, 1000000});
                    occ = true;
                }
            }

        }
        
        cout << Ans;

    }
};
