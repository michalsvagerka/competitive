#include "../../../l/lib.h"
// #include "../l/mod.h"

class gamewithpowers {
public:
    unordered_map<int, int> G;
    vector<int> PAT;

    int grundy(int m) {
        auto it = G.find(m);
        if (it != G.end()) {
            return it->y;
        }

        set<int> S;
        for (int i = 0; i < 30; ++i) {
            if (m&(1<<i)) {
                S.insert(grundy(m&~PAT[i]));
            }
        }
        int g = 0;
        while (S.find(g) != S.end()) g++;
        return G[m] = g;
    }

    void solve(istream& cin, ostream& cout) {
        for (int i = 1; i <= 30; ++i) {
            int s = 0;
            for (int j = i-1; j < 30; j+=i) s |= 1<<j;
            PAT.push_back(s);
        }

        vector<int> GG{1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12,14};
//        cout << PAT;
        G[0] = 0;
//        for (int i = 1; i <= 30; ++i) {
//            int t = (1<<i)-1;
//            cout << grundy(t) << ',';
//        }
//        cout << endl;

        int N; cin >> N;
        int g = GG[0]; //grundy(1);

        int i;
        set<int> F;
        for (i = 2; i*i <= N; ++i) {
            if (F.find(i) != F.end()) {
                F.erase(i);
            } else {
                ll j = i, k = 1;
                while (j * i <= N) {
                    j *= i;
                    k++;
                    F.insert(j);
                }
                //g ^= grundy((1<<k)-1);
                g ^= GG[k - 1];
            }
        }
        if ((N - i+1-F.size())%2==1) g ^= GG[0]; //grundy(1);
        cout << (g?"Vas":"Pet") << "ya\n";
//        cout << G.size();
    }
};
