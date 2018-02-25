#include "../../l/lib.h"
// #include "../l/mod.h"

class bittorrent {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> C(K, 0);
        int seeds = 0;
        for (int i = 0; i < N; ++i) {
            int t = 0;
            string S; cin >> S;
            for (int j = 0; j < K; ++j) {
                if (S[j]=='1') {
                    ++t;
                    C[j]++;
                }
            }
            seeds += t == K;
        }

        int distributed = *min_element(C.begin(),C.end()) - seeds;
        int peers = N - seeds;
        int foo[3];
        for (int i = 0; i < 3; ++i) {
            foo[i] = (1000 * count_if(C.begin(), C.end(), [&](int x) { return x > seeds + distributed + i; }) + K/2) / K;
        }

        cout << "seeds: " << seeds << " seen now, "
             << "plus " << distributed << " distributed copies ("
             << distributed+1 << ":" << foo[0]/10 << "." << foo[0]%10 << "%, "
             << distributed+2 << ":" << foo[1]/10 << "." << foo[1]%10 << "%, "
             << distributed+3 << ":" << foo[2]/10 << "." << foo[2]%10 << "%)\n"
             << "peers: " << peers << " seen now\n";
    }
};
