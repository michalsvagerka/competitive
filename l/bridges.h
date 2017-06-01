struct Graph {
    explicit Graph(const vector<vector<int>> &E):E(E),N(E.size()) {}

    void prep_dfs(){V=vector<bool>(N,false);D=P=L=vector<int>(N,-1);T=0;}
    void bridges(vector<pii>&br){prep_dfs();for(int i=0;i<N;i++)if(!V[i])_bridge_dfs(br,i);}
    void _bridge_dfs(vector<pii>&br,int u){
        L[u]=D[u]=T++;V[u]=true;
        for(int v:E[u]) {
            if(!V[v]){
                P[v]=u;
                _bridge_dfs(br, v);
                L[u]=min(L[u],L[v]);
                if(L[v]>D[u])br.push_back({u,v});
            }else if(P[u]!=v)L[u]=min(L[u], D[v]);
        }
    }

    void artic(vector<bool>&art){prep_dfs();for(int i=0;i<N;i++)if(!V[i])_artic_dfs(art,i);}
    void _artic_dfs(vector<bool>&art,int u){
        L[u]=D[u]=T++;V[u]=true;int c=0;art[u]=false;
        for(int v:E[u]) {
            if(!V[v]){
                P[v]=u;
                _artic_dfs(art, v);
                L[u]=min(L[u],L[v]);
                if((P[v]==-1&&++c>1)||(P[v]!=-1&&L[v]>=D[u]))art[u]=true;
            }else if(P[u]!=v)L[u]=min(L[u], D[v]);
        }
    }
    const vector<vector<int>>&E;int N,T;
    vector<bool>V;vector<int>L,P,D;
};