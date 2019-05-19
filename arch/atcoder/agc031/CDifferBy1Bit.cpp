#include "../l/lib.h"
#include <numeric>

class CDifferBy1Bit {
public:
    void solve(istream& cin, ostream& cout) {
        int N, A, B; cin >> N >> A >> B;
        B ^= A;

        int a = __builtin_popcount(B);
        if (a%2 == 0) {
            cout << "NO\n";
            return;
        }

        // go from 0 to A^B and then xor everything with A
        vector<int> E, F;
        for (int i = 0; i < N; ++i) {
            if (B&(1<<i)) E.push_back(i);
            else F.push_back(i);
        }

        vector<int> Ans{0, 1<<E[0]};
        for (int j = 1; j < E.size(); j += 2) {
            int k = 1<<E[j], l = 1<<E[j+1];
            vector<int> SS;
            for (int w = 0; w+2 < Ans.size(); w+=2) {
                SS.push_back(Ans[w]);
                SS.push_back(Ans[w] ^ k);
                SS.push_back(Ans[w] ^ k ^ l);
                SS.push_back(Ans[w] ^ l);
                SS.push_back(Ans[w+1] ^ l);
                SS.push_back(Ans[w+1] ^ k ^ l);
                SS.push_back(Ans[w+1] ^ k);
                SS.push_back(Ans[w+1]);
            }
            
            int w = Ans.size() - 2;
            SS.push_back(Ans[w]);
            SS.push_back(Ans[w] ^ k);
            SS.push_back(Ans[w+1] ^ k);
            SS.push_back(Ans[w+1]);
            SS.push_back(Ans[w+1] ^ l);
            SS.push_back(Ans[w] ^ l);
            SS.push_back(Ans[w] ^ k ^ l);
            SS.push_back(Ans[w+1] ^ k ^ l);
            swap(SS, Ans);
        }
        for (int f: F) {
            vector<int> SS;
            int k = 1<<f;
            for (int w = 0; w < Ans.size(); w += 2) {
                SS.push_back(Ans[w]);
                SS.push_back(Ans[w] ^ k);
                SS.push_back(Ans[w+1] ^ k);
                SS.push_back(Ans[w+1]);
            }
            swap(SS, Ans);
        }
        

        for (int&ans: Ans) ans ^= A;
        cout << "YES\n" << Ans;
    }
};
