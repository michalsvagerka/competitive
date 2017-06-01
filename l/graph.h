#include "../l/dinic.h"

// ordinary rooted tree with level ancestry and LCA. look elsewhere
template <int Indexing=1>struct Tree {
	explicit Tree(int N) : N(N), logN(logceil(N)), E(N) {}
	void addEdge(int u,int v){u-=Indexing; v-=Indexing;E[u].push_back(v);E[v].push_back(u);}
	int la(int u, int depth){calcLA();return _la(u-Indexing,depth)+Indexing;}
	int lca(int u, int v){calcLA();return _lca(u-Indexing,v-Indexing)+Indexing;}

private:
	int _la(int u, int d)const{for(int i=0;i<logN&&u!=-1;++i){if(d&(1<<i))u=PP[i][u];}return u;}
	int _lca(int u, int v) { if(D[u]<D[v]){swap(u,v);} u=_la(u,D[u]-D[v]);
		for(int i=logN-1;i>=0;--i)if(PP[i][u]!=PP[i][v]){u=PP[i][u];v=PP[i][v];}
		return u==v?u:PP[0][v];
	}
	inline void calcParents(){if(P.size()==0){P.resize(N);D.resize(N);dfs(0,-1,0);}}
	void dfs(int u,int v,int d){P[u]=v;D[u]=d;for(int w:E[u])if(v!=w)dfs(w,u,d+1);}
	inline void calcLA(){calcParents();if(PP.size()==0){PP=vector2<int>(logN,N,-1);for(int i=0;i<N;++i){PP[0][i]=P[i];}
			for(int i=1;i<logN;++i)for(int j=0;j<N;++j)if(PP[i-1][j]!=-1)PP[i][j]=PP[i-1][PP[i-1][j]];}}
	int N,logN; vector<vector<int>> E;vector<int> P,D;vector2<int>PP;
};

// ordinary bipartite graph, with max. matching, max. indep. set and min. vertex cover. look elsewhere
template <int Indexing=1> struct Bipartite {
	explicit Bipartite(size_t A, size_t B) : A(A), B(B), N(A+B), ms(-1), eId(0), E(N), G(N+2) {}
	void addEdge(int u,int v){u-=Indexing; v-=Indexing;E[u].push_back({v,eId++});E[v].push_back({u,eId++});G.AddEdge(u,v);}
	size_t matchingSize(){calcMatchingSize();return ms;}
	int matched(int v){calcMatching();return M[v];}
	vector<int>cover(){calcCover();vector<int>C;for(int i=0;i<N;++i){if(Z[i]!=(i<A))C.push_back(i+Indexing);}return C;}
	vector<int>indep(){calcCover();vector<int>I;for(int i=0;i<N;++i){if(Z[i]==(i<A))I.push_back(i+Indexing);}return I;}
private:
	void konigDfs(int u){if(Z[u]){return;}Z[u]=true;if(u<A){for(pii v:E[u])if(v.x!=M[u])konigDfs(v.x);}else if(M[u]!=-1)konigDfs(M[u]);}
	inline void calcMatchingSize(){if(ms!=-1){return;}for(int i=0;i<A;++i){G.AddEdge(N, i);}for(int i=A;i<N;++i){G.AddEdge(i,N+1);}ms=(size_t)G.GetMaxFlow(N, N+1);}
	inline void calcMatching(){if(M.size()==N){return;}calcMatchingSize();M=vector<int>(N,-1);for(int i=0;i<A;++i)for(pii ed:E[i])if(G.Capacity[ed.y]==0){M[i]=ed.x;M[ed.x]=i;}}
	inline void calcCover(){if(Z.size()==N){return;}calcMatching();Z=vector<bool>(N,false);for(int i=0;i<A;++i)if(M[i]==-1)konigDfs(i);}
	size_t N,A,B,ms,eId;vector<vector<pii>>E;Dinic G;vector<int>M;vector<bool>Z;
};

template <int Indexing=1> struct DirectedGraph {
	explicit DirectedGraph(int N) : N(N), E(N) {}
	void addEdge(int u,int v){u-=Indexing; v-=Indexing;E[u].push_back({v});}
	int stronglyConnectedComponent(int v){v-=Indexing;calcStronglyConnectedComponents();return SCC[v];}
	bool stronglyConnected(int u,int v){u-=Indexing;v-=Indexing;calcStronglyConnectedComponents();return SCC[u]==SCC[v];}
	const vector<int>& stronglyConnectedPermutation() {calcStronglyConnectedComponents(); return O;}
private:
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
	explicit TwoSat(int N=0) : N(N), G(2*N) {}
	void forbid(int u,bool w){G.addEdge(u+N*(1-w),u+N*w);}
	void addClause(int u,bool w,int v,bool x){G.addEdge(u+N*w,v+N*(1-x));G.addEdge(v+N*x,u+N*(1-w));}
	bool satisfiable() {calculateAssignment();return ok;}
	const vector<int>& assignment() {calculateAssignment();return A;}
private:
	inline void calculateAssignment(){if(A.size()==N){return;}A.resize(N);ok=true;map<int,bool>Q;
		for(int u:G.stronglyConnectedPermutation()){
			int c1=G.stronglyConnectedComponent(u),c2=G.stronglyConnectedComponent((u+N)%(2*N));
			if(c1==c2){ok=false;return;}if(Q.find(c1)==Q.end()){Q[c1]=true;Q[c2]=false;}}
		for(int i=0;i<N;++i){A[i]=Q[G.stronglyConnectedComponent(i)];}
	}
	int N; DirectedGraph<0>G;vector<int>A;bool ok;
};