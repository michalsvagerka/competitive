#include "../l/lib.h"
 #include "../l/random.h"

class F {
public:

    char ask(int i, int j) {
        cout << "? " << i+1 << ' ' << j+1 << endl;
        char ans; cin >> ans;
        return ans;
    }

    vector<int> sort(vector<int> &s, bool theySayAbove) {
        if (s.empty()) return s;
        if (s.size() == 1) return s;
        random_int I(0, int(s.size())-1);
        int id = I(rng);
        vector<int> Above, Below;
        for (int i = 0; i < s.size(); ++i) {
            if (i != id) {
                char ans = ask(s[id], s[i]);
                if (ans == '-') { Above.push_back(s[i]); }
                else if (ans == '+') { Below.push_back(s[i]); }
                else if (theySayAbove) { Below.push_back(s[i]); }
                else { Above.push_back(s[i]); }
            }
        }

        Above = sort(Above, theySayAbove);
        Below = sort(Below, theySayAbove);
        vector<int> Ans;
        for (int a:Above) Ans.push_back(a);
        Ans.push_back(s[id]);
        for (int a:Below) Ans.push_back(a);
        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<char> IAsk(N), HeAsks(N);
        int questionMark = 0;

        int zeroGuy = random_int{0,N-1}(rng);
        
        
        bool saysBelow = false, saysAbove = false;
        for (int i = 0; i < N; ++i) {
            if (zeroGuy != i) {
                IAsk[i] = ask(zeroGuy, i);
                HeAsks[i] = ask(i, zeroGuy);
                if (IAsk[i] == '+') saysBelow = true;
                if (IAsk[i] == '-') saysAbove = true;
                if (HeAsks[i] == '?') questionMark++;
            }
        }

        vector<int> Ans(N, -1000);

        if (questionMark == 1) {
            Ans[zeroGuy] = 3;
            vector<int> Below, Above;
            for (int i = 0; i < N; ++i) {
                if (i == zeroGuy) continue;
                if (IAsk[i] == '+') Below.push_back(i);
                else if (HeAsks[i] == '?') Ans[i] = 1;
                else Above.push_back(i);
            }

            Above = sort(Above, false); // above also contains the '2' guy
            for (int i = 0; i < Above.size()-1; ++i) Ans[Above[i]] = 2+i-int(Above.size());
            Ans[Above[Above.size()-1]] = 2;

            Below = sort(Below, true);
            for (int i = 0; i < Below.size(); ++i) Ans[Below[i]] = 4+i;

        } else if (saysAbove) {
            vector<int> Above, Below{zeroGuy};
            for (int i = 0; i < N; ++i) {
                if (i == zeroGuy) continue;
                if (HeAsks[i] == '-' || HeAsks[i] == '?') Below.push_back(i);
                else Above.push_back(i);
            }

            Above = sort(Above, false); // above also contains the '3' guy
            for (int i = 0; i < Above.size()-1; ++i) Ans[Above[i]] = 2+i-int(Above.size());
            Ans[Above[Above.size()-1]] = 3;
            int three = Above[Above.size()-1];

            Below = sort(Below, true); // below also contains the '1' and '2' guy
            if (ask(Below[0], three) == '+') {
                Ans[Below[0]] = 2;
                Ans[Below[1]] = 1;
            } else {
                Ans[Below[0]] = 1;
                Ans[Below[1]] = 2;
            }
            for (int i = 2; i < Below.size(); ++i) Ans[Below[i]] = 2+i;
        } else if (questionMark == 2) {
            vector<int> Below, Above;

            if (saysBelow) {
                Ans[zeroGuy] = 2;
                for (int i = 0; i < N; ++i) {
                    if (i == zeroGuy) continue;
                    if (IAsk[i] == '+') Ans[i] = 3;
                    else if (HeAsks[i] == '-') Below.push_back(i);
                    else if (HeAsks[i] == '+') Above.push_back(i);
                    else Ans[i] = 1;
                }

                Below = sort(Below, true);
                Above = sort(Above, false);
                for (int i = 0; i < Above.size(); ++i) Ans[Above[i]] = 1+i-int(Above.size());
                for (int i = 0; i < Below.size(); ++i) Ans[Below[i]] = 4+i;
            } else {
                Ans[zeroGuy] = 1;
                vector<int> TwoThree;
                for (int i = 0; i < N; ++i) {
                    if (i == zeroGuy) continue;
                    if (HeAsks[i] == '-') Below.push_back(i);
                    else if (HeAsks[i] == '+') Above.push_back(i);
                    else TwoThree.push_back(i);
                }
                char ch = ask(TwoThree[0], TwoThree[1]);
                if (ch == '+') { Ans[TwoThree[0]] = 2; Ans[TwoThree[1]] = 3; }
                else { Ans[TwoThree[1]] = 2; Ans[TwoThree[0]] = 3; }

                Below = sort(Below, true);
                Above = sort(Above, false);
                for (int i = 0; i < Above.size(); ++i) Ans[Above[i]] = 1+i-int(Above.size());
                for (int i = 0; i < Below.size(); ++i) Ans[Below[i]] = 4+i;
            }
        } else {

            vector<int> Above{zeroGuy}, Below;
            for (int i = 0; i < N; ++i) {
                if (i == zeroGuy) continue;
                if (HeAsks[i] == '+' || HeAsks[i] == '?') Above.push_back(i);
                else Below.push_back(i);
            }


            Below = sort(Below, true);
            for (int i = 0; i < Below.size(); ++i) Ans[Below[i]] = 4+i;

            Above = sort(Above, false); // above also contains the '1', '2' and '3'
            for (int i = 0; i < Above.size()-3; ++i) Ans[Above[i]] = 4+i-int(Above.size());


            vector<int> ABC{Above[Above.size()-1], Above[Above.size()-2], Above[Above.size()-3]};
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i != j && ask(ABC[i], ABC[j]) == '+') {
                        Ans[ABC[i]] = 2;
                        Ans[ABC[j]] = 3;
                        Ans[ABC[3-i-j]] = 1;
                    }
                }
            }
        }

        cout << "! " << Ans;

    }
};
