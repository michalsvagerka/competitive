#include "../l/lib.h"

class ERearranging {
public:
    int N, M, P;
    vector<vector<int>> Multiples;
    vector<vector<int>> Factors;
//    map<int, int> C;
    vector<int> B;
    vector<int> Stack;
    vector<bool> Forbidden;
    vector<int> CompVisit, PrimeVisit;
    int CompTime;

    vector<int> component(int value) {
        ++CompTime;
        CompVisit[value] = CompTime; 
        vector<int> Q{value};
        for (int q = 0; q < Q.size(); ++q) {
            int v = Q[q];
            for (int f: Factors[v]) {
                if (PrimeVisit[f] == CompTime) continue;
                PrimeVisit[f] = CompTime;
                for (int m: Multiples[f]) {
                    if (Forbidden[m]) continue;
                    if (CompVisit[m] == CompTime) continue;
                    CompVisit[m] = CompTime;
                    Q.push_back(m);
                }
            }
        }
        sort(Q.begin(),Q.end());
        return Q;
    }

    vector<int> solve(const vector<int> &Component) {
        vector<vector<int>> Others;
        vector<bool> Used(N, false);

        for (int val: Component) {
            if (!Used[val]) {
                auto cc = component(val);
                for (int c: cc) Used[c] = true;

                int root = -1;
                for (int c: cc) {
                    if (Stack.empty() || gcd(B[Stack.back()], B[c]) != 1) {
                        root = c;
                        break;
                    }
                }

                Stack.push_back(root);
                Forbidden[root] = true;
                cc.erase(find(cc.begin(),cc.end(),root));
                vector<int> Z = solve(cc);
                Stack.pop_back();
                Forbidden[root] = false;

                Others.push_back({B[root]});
                for (int z: Z) Others.back().push_back(z);
            }
        }

        vector<int> Answer;
        if (!Others.empty()) {
            vector<int> Merged = Others[0];
            for (int i = 1; i < Others.size(); ++i) {
                vector<int> QQ;
                int j = 0, k = 0;
                while (j < Merged.size() || k < Others[i].size()) {
                    if (j == Merged.size()) { QQ.push_back(Others[i][k++]); }
                    else if (k == Others[i].size()) { QQ.push_back(Merged[j++]); }
                    else if (Merged[j] < Others[i][k]) { QQ.push_back(Others[i][k++]); }
                    else { QQ.push_back(Merged[j++]); }
                }
                swap(Merged, QQ);
            }
            for (int m: Merged) Answer.push_back(m);
        }
        return Answer;
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        B = A;

        vector<int> Ans;
        if (!B.empty()) {
            Forbidden.assign(N, false);

            CompTime = 0;
            CompVisit.assign(N, 0);

            vector<int> AllPrimes;
            for (int b: B) {
                int x = b;
                for (int p = 2; p <= 10000; ++p) {
                    if (x%p == 0) {
                        AllPrimes.push_back(p);
                        while (x%p == 0) x /= p;
                    }
                }
                if (x != 1) {
                    AllPrimes.push_back(x);
                }
            }
            map<int, int> CompressPrimes;
            P = 0;
            sort(AllPrimes.begin(),AllPrimes.end());
            AllPrimes.resize(distance(AllPrimes.begin(),unique(AllPrimes.begin(),AllPrimes.end())));
            for (int p: AllPrimes) CompressPrimes[p] = P++;
            Multiples.resize(P);
            PrimeVisit.assign(P, 0);

            for (int j = 0; j < N; ++j) {
                int x = B[j];
                Factors.push_back({});
                for (int p = 2; p <= 10000; ++p) {
                    if (x%p == 0) {
                        Factors.back().push_back(CompressPrimes[p]);
                        while (x%p == 0) x /= p;
                        Multiples[CompressPrimes[p]].push_back(j);
                    }
                }
                if (x != 1) {
                    Factors.back().push_back(CompressPrimes[x]);
                    Multiples[CompressPrimes[x]].push_back(j);
                }
            }

            vector<int> All;
            for (int i = 0; i < N; ++i) All.push_back(i);
            auto res = solve(All);
            for (int r: res) Ans.push_back(r);
        }
        cout << Ans;
    }
};
