// ordinary rooted tree with level ancestry and LCA. look elsewhere
struct TreeX {
	explicit TreeX(int N=1) : N(N), M(0), logN(logceil(N)), _root(0), E(N) {}
	void addEdge(int u,int v){++M;E[u].push_back(v);E[v].push_back(u);}
	int la(int u, int depth){/*calcLA();*/return _la(u,depth);}
	inline int lca(int u, int v){/*calcLA();*/return _lca(u,v);}
	int parent(int u) { return P[u]; }
	void setRoot(int r) { _root = r; }
	int root() { return _root; }
	const vector<int>& neighbors(int u) const { return E[u]; }
    int depth(int u) const { return D[u]; }
	bool isAncestor(int top, int bottom) { return lca(top, bottom) == top; }
	bool sameBranch(int top, int bottom) { int l = lca(top, bottom); return l == top || l == bottom; }

	int _la(int u, int d)const{for(int i=0;i<logN&&u!=-1;++i){if(d&(1<<i))u=PP[i][u];}return u;}
	int _lca(int u, int v) { if(D[u]<D[v]){swap(u,v);} u=_la(u,D[u]-D[v]);
		for(int i=logN-1;i>=0;--i)if(PP[i][u]!=PP[i][v]){u=PP[i][u];v=PP[i][v];}
		return u==v?u:PP[0][v];
	}
	inline void calcParents(){assert(M == N-1);if(P.size()==0){P.resize(N);D.resize(N);dfs(_root,-1,0);}}
	void dfs(int u,int v,int d){P[u]=v;D[u]=d;for(int w:E[u])if(v!=w)dfs(w,u,d+1);}
	inline void calcLA(){calcParents();if(PP.size()==0){PP=vector2<int>(logN,N,-1);for(int i=0;i<N;++i){PP[0][i]=P[i];}
			for(int i=1;i<logN;++i)for(int j=0;j<N;++j)if(PP[i-1][j]!=-1)PP[i][j]=PP[i-1][PP[i-1][j]];}}
	int N,M,logN,_root; vector<vector<int>> E;vector<int> P,D;vector2<int>PP;
};

template <typename EdgeType>
class DFSOrder {
public:
    DFSOrder(const vector<vector<EdgeType>> &_E) : T(0), N(_E.size()), E(_E), RevEnter(N), Enter(N), Exit(N) {
        dfs(0, -1);
    }

    vector<vector<EdgeType>> linearize() {
        vector<vector<EdgeType>> F(N);
        for (int i = 0; i < N; ++i) {
            for (auto v:E[i]) {
                F[conv(i)].push_back(conv(v));
            }
        }
        return F;
    }

    void dfs(int u, int p) {
        RevEnter[T] = u;
        Enter[u] = T++;
        for (auto v:E[u]) if (t(v) != p) dfs(t(v), u);
        Exit[u] = T;
    }

    inline int t(const int&e) const { return e; }
    template <typename U> inline int t(const pair<int, U>&e) const { return e.x; }

    inline int conv(const int&e) const { return Enter[e]; }
    template <typename U> inline pair<int, U> conv(const pair<int, U>&e) const { return {Enter[e.x], e.y}; }

    const vector<int> &revEnter() const { return RevEnter; }
    const vector<int> &enter() const { return Enter; }
    const vector<int> &exit() const { return Exit; }

    int T, N;
    const vector<vector<EdgeType>> &E;
    vector<int> Enter, Exit, RevEnter;
};

/** Centroid decomposition.
 *
 * Input: graph as adjacency list (either int or pair<int,T>)
 * Output: array U of integers of size |V|
 *
 * Here, U[v] is the bfs order in the centroid tree. For DFS, only process
 * vertices with higher U[w] when processing centroid v, for instance:
 *
 * void dfs(int u, int p, int ctr, ...) {
 *      ....
 *      for (int v:E[u]) {
 *          if (v != p && U[v] > U[ctr]) {
 *              dfs(v, u, ctr, ...);
 *          }
 *      }
 * }
 */
template <typename EdgeType>
class CentroidDecomposition {
public:
    CentroidDecomposition(const vector<vector<EdgeType>> &E) : E(E) {}

    const vector<int>& findCentroids() {
        DFSOrder<EdgeType> DFS(E);
        auto EF = DFS.linearize();

        N = E.size(); U.assign(N, -1);
        int L = 0;

        for (int j = 0; j < N; ) {
            for (int i = N-1; i >= 0; --i) {
                if (U[i] >= 0) continue;

                U[i] = -1;
                bool root = true;
                for (auto v:EF[i]) {
                    if (U[t(v)]<0) {
                        if (t(v) > i) U[i] += U[t(v)];
                        else root = false;
                    }
                }

                if (root) {
                    int n = -U[i], u = i, p = -1;
                    while (true) {
                        int s = n + U[u];
                        for (auto v:EF[u]) if (t(v)!=p && U[t(v)] < 0) s = max(s, -U[t(v)]);
                        if (2 * s <= n) { U[u] = j++; break; }
                        else { for (auto v:EF[u]) if (t(v)!=p && -U[t(v)] > n / 2) { p = u;u = t(v);break; } }
                    }
                }
            }
        }
        vector<int> Ans(N);
        for (int i = 0; i < N; ++i) Ans[i] = U[DFS.enter()[i]];
        swap(Ans, U);
        return U;
    }

    inline int t(const int&e) const { return e; }
    template <typename U> inline int t(const pair<int, U>&e) const { return e.x; }

    int N;
    const vector<vector<EdgeType>> &E;
    vector<int> U;
};


// ordinary bipartite graph, with max. matching, max. indep. set and min. vertex cover. look elsewhere
struct Bipartite {
	explicit Bipartite(ui A, ui B) : A(A), B(B), N(A+B), ms(-1), H(N,-1), used(A) {}
	void addEdge(int u,int v){G.push_back(v);P.push_back(H[u]);H[u]=(ui)G.size()-1;}
	ui matchingSize(){calcMatching();return ms;}
	int matched(int v){calcMatching();return M[v];}
	vector<int>cover(){calcCover();vector<int>C;for(int i=0;i<N;++i){if(Z[i]!=(i<A))C.push_back(i);}return C;}
	vector<int>indep(){calcCover();vector<int>I;for(int i=0;i<N;++i){if(Z[i]==(i<A))I.push_back(i);}return I;}
//private:
	void konigDfs(int u){
        if(Z[u]){return;}
        Z[u]=true;
        if(u<A){
            for (ui p = H[u]; p != -1; p = P[p]) {
                ui v = G[p];
                if (v != M[u])konigDfs(v);
            }
        }
        else if(M[u]!=-1)
            konigDfs(M[u]);
    }
    bool matchingDfs(int u) {
        if (used[u]) return false;
        used[u] = true;

        for (ui p = H[u]; p != -1; p = P[p]) {
            ui v = G[p];
            if (M[v]==-1) { M[u] = v; M[v] = u; ++ms; return true; }
        }

        for (ui p = H[u]; p != -1; p = P[p]) {
            ui v = G[p];
            if (matchingDfs(M[v])) { M[u] = v; M[v] = u; return true; }
        }
        return false;

    }
	inline void calcMatching(){
        if(ms!=-1){return;}
        M = vector<ui>(N,-1);
        size_t cur; ms = 0;
        do {
            cur = ms;
            for(int i=0;i<A;++i) used[i] = false;
            for(int i=0;i<A;++i) if(M[i]==-1) matchingDfs(i);
        } while(cur != ms);
    }
	inline void calcCover(){if(Z.size()==N){return;}calcMatching();Z=vector<bool>(N,false);for(int i=0;i<A;++i)if(M[i]==-1)konigDfs(i);}
	ui N,A,B,ms;vector<ui>M,H,G,P;vector<bool>Z,used;
};

struct DirectedGraph {
	explicit DirectedGraph(int N) : N(N), E(N) {}
	void addEdge(int u,int v){E[u].push_back({v});}
	int stronglyConnectedComponent(int v){calcStronglyConnectedComponents();return SCC[v];}
	bool stronglyConnected(int u,int v){calcStronglyConnectedComponents();return SCC[u]==SCC[v];}
	const vector<int>& stronglyConnectedPermutation() {calcStronglyConnectedComponents(); return O;}
//private:
	inline void calcReverseEdges(){if(ER.size()==N){return;}ER.resize(N);for(int i=0;i<N;++i)for(int u:E[i])ER[u].push_back(i);}
	inline void calcStronglyConnectedComponents(){
		if(SCC.size()==N){return;}SCC.resize(N);O.resize(N);calcReverseEdges();
		vector<bool>V(N,false);vector<int>F(N,0);int t=0;for(int i=N-1;i>=0;i--){if(!V[i]){dfsReverse(i,V,F,t);}O[N-1-F[i]] = i;}
		fill(V.begin(),V.end(),false);for(int i=0;i<N;i++){if(!V[O[i]])dfsForward(O[i],O[i],V);}
	}
	void dfsForward(int i,int p,vector<bool>&V){V[i]=true;SCC[i]=p;for(int v:E[i])if(!V[v])dfsForward(v,p,V);}
	void dfsReverse(int i,vector<bool>&V,vector<int>&F,int&t){V[i]=true;for(int v:ER[i]){if(!V[v])dfsReverse(v,V,F,t);}F[i] = t++;}
	int N; vector<vector<int>>E,ER;vector<int>SCC,O;
};


struct TwoSat {
	int N;
	vector<int> val; vector<char> valid;
	vector<vector<int>> G;

	TwoSat(int N) : N(N), val(2*N), G(2*N) {}
	void addImplication(int a, bool w, int b, bool x) { G[2*a+w].push_back(2*b+x); }
	void addOr(int a, bool w, int b, bool x) { addImplication(a, !w, b, x); addImplication(b, !x, a, w); }
	void addTrue(int x) { addImplication(x, false, x, true); }
    void addFalse(int x) { addImplication(x, true, x, false); }
	int time() { return valid.size()-1; }
	bool dfs(int x) {
		if(valid[abs(val[x])]) return val[x]>0;
		val[x] = time();
		val[x^1] = -time();
		for(int e:G[x]) if(!dfs(e)) return false;
		return true;
	}

	bool value(int i) const { return val[2*i]<0; }

	bool solve() {
		fill(val.begin(), val.end(), 0);
		valid.assign(1, 0);
		for(int i=0; i<val.size(); i+=2) {
			if(!valid[abs(val[i])]) {
				valid.push_back(1);
				if(!dfs(i)) {
					valid.back()=0;
					valid.push_back(1);
					if(!dfs(i+1)) return false;
				}
			}
		}
		return true;
	}
};