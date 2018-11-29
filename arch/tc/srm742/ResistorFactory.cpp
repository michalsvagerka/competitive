#include "../l/lib.h"
// #include "../l/mod.h"

class ResistorFactory {
public:
    vector <int> construct(long long nanoOhms) {
        vector<int> Ans;
        ll full = nanoOhms/ll(1e9);
        for (int i = 0; i < 30; ++i) { Ans.push_back(i); Ans.push_back(i); Ans.push_back(0); }
        Ans.push_back(0); Ans.push_back(0); Ans.push_back(1);
        for (int i = 31; i <= 200; ++i) { Ans.push_back(i); Ans.push_back(i); Ans.push_back(1); }

        vector<int> Need;
        for (int i = 0; i <= 30; ++i) {
            if (full&(1LL<<i)) Need.push_back(i);
        }

        double left = nanoOhms / 1e9 - full;
        for (int i = 31; i <= 200; ++i) {
            left *= 2;
            if (left > 1.0) { left -= 1.0; Need.push_back(i); }
        }

        Ans.push_back(Need[0]);
        Ans.push_back(Need[0]);
        Ans.push_back(0);
        Ans.push_back(Ans.size()/3);
        Ans.push_back(Ans.size()/3);
        Ans.push_back(1);
        for (int i = 1; i < Need.size(); ++i) {
            Ans.push_back(Ans.size()/3);
            Ans.push_back(Need[i]);
            Ans.push_back(0);
        }
        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
        ll s; cin >> s;
        auto a = construct(s);
        vector<double> W{1};
        for (int i = 0; i < a.size(); i+=3) {
            double p1 = W[a[i]];
            double p2 = W[a[i+1]];
            int op = a[i+2];
            if (op == 0) {
                W.push_back(p1 + p2);
            } else {
                W.push_back(p1*p2/(p1+p2));
            }
        }
        cout << fixed << setprecision(10) << s/1e9 << ' ' << W.back() << ' ' << abs(s/1e9 - W.back()) << endl;

    }
};
