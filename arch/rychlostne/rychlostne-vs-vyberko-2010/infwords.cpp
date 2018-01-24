#include "../l/lib.h"

struct DirectedGraph {
    friend class infwords;
    explicit DirectedGraph(int N) : N(N), E(8*N, 0), ER(8*N, 0), V(N,false), F(N,0) {}
    void addEdge(int u,int v){
        E[u+(E[u]+=N)] = v;
        ER[v+(ER[v]+=N)] = u;
    }
    inline int stronglyConnectedComponent(int v){return SCC[v];}
    inline bool stronglyConnected(int u,int v){return SCC[u]==SCC[v];}
private:
    inline void calcStronglyConnectedComponents(){
        if(SCC.size()==N){return;}SCC.resize(N);O.resize(N);
        t=0;for(int i=N-1;i>=0;i--){if(!V[i]){dfsReverse(i);}O[N-1-F[i]] = i;}
        fill(V.begin(),V.end(),false);for(int i=0;i<N;i++){if(!V[O[i]]){p=O[i];dfsForward(O[i]);}}
    }
    void dfsForward(int i){
        V[i]=true;SCC[i]=p;
        for(int j = N; j <= E[i]; j+=N) {
            int v = E[i + j];
            if (!V[v])
                dfsForward(v);
        }
    }
    void dfsReverse(int i){
        V[i]=true;
        for(int j = N; j <= ER[i]; j+=N) {
            int v = ER[i + j];

            if(!V[v])
                dfsReverse(v);
        }
        F[i] = t++;
    }
    int N; vector<int>E,ER,SCC,O,F;vector<bool> V;int t,p;
};

class infwords {
public:
    int g;
    vector<int> MP;
    vector<int> SCV, SCE, SCO, SCI;
    vector<vector<int>> R;

    inline int idx(int i) {
        if (MP[i] != -1) return MP[i];
        else {
            SCV.push_back(0);
            SCE.push_back(0);
            SCO.push_back(0);
            SCI.push_back(0);
            R.push_back({});
            return MP[i] = g++;
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> P(11, 1);
        for (int i = 0; i < 10; ++i) {
            P[i+1] = P[i] * N;
        }


        vector<bool> T(P[10],true);
        vector<bool> VRT(P[9],true);
        set<string> forb;
        int F = 2;
        for (int i = 0; i < M; ++i) {
            string S;
            cin >> S;
            F = max(F, int(S.size()));
            forb.insert(S);
        }
        for (string S: forb) {
            int w = 0;
            for (char s:S) w = w*N + s - 'a';
            if (S.size() != F) for (int j = w; j < P[F-1]; j+=P[S.size()]) { VRT[j] = false; }
            for (int j = w; j < P[F]; j+=P[S.size()]) { T[j] = false; }
        }

        int vert = 0;
        MP.resize(P[F-1]);
        for (int i = 0; i < P[F-1]; ++i) { if (VRT[i]) MP[i] = vert++; }

        int edges = 0;
        DirectedGraph E(vert);
        for (int i = 0; i < P[F-1]; ++i) {
            if (VRT[i]) {
                int l = N * i;
                for (int j = 0; j < N; ++j) {
                    int k = l + j;
                    if (T[k]) {
                        int t = (l + j) % P[F - 1];
                        E.addEdge(MP[i], MP[t]);
//                        if (++edges > P[F-1]+P[F-2]) {
//                            cout << -1 << endl;
//                            return;
//                        }
                    }
                }
            }
        }

        E.calcStronglyConnectedComponents();
        MP = vector<int>(vert, -1); g = 0;
        for (int i = 0; i < vert; ++i) {
            int k = idx(E.SCC[i]);
            SCV[k]++;
            for (int j = vert; j <= E.E[i]; j+=vert) {
                int l = idx(E.SCC[E.E[i+j]]);
                if (k == l)SCE[k]++;
                else {
                    SCI[l]++;
                    R[k].push_back(l);
                }
            }
        }

        int ans = 0;
        queue<int> Q;
        for (int i = 0; i < SCE.size(); ++i) {
            if (SCE[i] > SCV[i]) {
                cout << -1 << endl;
                return;
            }

            if (!SCI[i]) Q.push(i);
            SCV[i] = 0;
        }


        while (!Q.empty()) {
            int q = Q.front(); Q.pop();
            if (SCE[q]) {
                ans += ++SCV[q];
                if (++SCO[q] == 3) {
                    cout << -1 << endl;
                    return;
                }
            }
            for (int v : R[q]) {
                SCV[v] += SCV[q];
                SCO[v] = max(SCO[v],SCO[q]);
                if (!--SCI[v]) Q.push(v);
            }
        }
        cout << ans << endl;
    }
};
