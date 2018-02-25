#include "../../../l/lib.h"
#include "../../../l/frac.h"
#include "../../../l/fenwick.h"

class therace {
public:
    pair<Fraction,Fraction> event(int i) {

        // x = X[i] + t * V[i]
        // x = X[i+1] + t * V[i+1]
        //
        // t = (X[i+1]-X[i])/(V[i]-V[i+1])
        // x = X[i] + V[i]*(X[i+1]-X[i])/(V[i]-V[i+1])

        Fraction time{X[i+1]-X[i],V[i]-V[i+1]};
        Fraction location = time * V[i] + X[i];
        return {time,location};
    }

    vector<int> X,V,I;

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        X.resize(N);
        V.resize(N);
        I.resize(N);
        Fenwick<int> F(101, 0);
        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            cin >> X[i] >> V[i];
            ans += i - F.sum(V[i]+1);
            F.add(V[i], 1);
            I[i] = i;
        }

        map<pair<Fraction,Fraction>, int> Events;
        for (int i = 0; i < N-1; ++i) {
            if (V[i] > V[i+1]) {
                Events[event(i)] = i;
            }
        }

        cout << ans % 1000000 << endl;
        for (int j = 0; j < 10000 && !Events.empty(); ++j) {
            Fraction time = Events.begin()->x.x;
            Fraction location = Events.begin()->x.y;
            int i = Events.begin()->y;
            Events.erase(Events.begin());
            cout << I[i]+1 << ' ' << I[i+1]+1 << '\n';
            if (i != 0 && V[i-1] > V[i]) Events.erase(event(i-1));
            if (i != N-2 && V[i+1] > V[i+2]) Events.erase(event(i+1));
            swap(I[i],I[i+1]);
            swap(V[i],V[i+1]);
            swap(X[i],X[i+1]);
            if (i != 0 && V[i-1] > V[i]) Events[event(i-1)] = i-1;
            if (i != N-2 && V[i+1] > V[i+2]) Events[event(i+1)] = i+1;
        }
    }
};
