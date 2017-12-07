#include "lib.h"

struct Graph {
    explicit Graph(const vector<vector<int>> &E):E(E),N(E.size()) {}

    void prep_dfs(){D=P=vector<int>(N,0);T=0;}
    void bridges(vector<pii>&br){prep_dfs();for(int i=0;i<N;i++)if(!D[i])_bridge_dfs(br,i);}
    int _bridge_dfs(vector<pii>&br,int u){
        int top=D[u]=++T;
        for(int v:E[u]) {
            if(!D[v]){
                P[v]=u;
                int up=_bridge_dfs(br, v);
                top=min(top,up);
                if(up>D[u])br.push_back({u,v});
            }else if(P[u]!=v)top=min(top, D[v]);
        }
        return top;
    }

    bool bicon(const function<bool(vector<pii>::iterator,vector<pii>::iterator)> &f) {
        prep_dfs();vector<pii> s;
        for(int i=0;i<N;i++) {
            if(D[i])continue;
            if (_bicon_dfs(i,s,f)==-1) return true;
            if(!s.empty()){
                if (f(s.begin(),s.end())) return true;
                s.erase(s.begin(),s.end());
            }
        }
        return false;
    }
    int _bicon_dfs(int u,vector<pii>&s,const function<bool(vector<pii>::iterator,vector<pii>::iterator)> &f){
        int c=0,top=D[u]=++T;
        for(int v:E[u]) {
            if(!D[v]){
                P[v]=u;
                int r = s.size();
                s.push_back({u,v});
                int up=_bicon_dfs(v, s, f);
                if (up == -1) return -1;
                top=min(top,up);
                if((D[u]==1&&++c>1)||(D[u]!=1&&up>=D[u])){
                    if(f(s.begin()+r,s.end())) return -1;
                    s.erase(s.begin()+r,s.end());
                }
            }else if(P[u]!=v){top=min(top,D[v]);if(D[v]<D[u])s.push_back({u,v});}
        }
        return top;
    }

    void artic(vector<bool>&art){prep_dfs();for(int i=0;i<N;i++)if(!D[i])_artic_dfs(art,i);}
    int _artic_dfs(vector<bool>&art,int u){
        int top=D[u]=++T,c=0;art[u]=false;
        for(int v:E[u]) {
            if(!D[v]){
                P[v]=u;
                int up=_artic_dfs(art, v);
                top=min(top,up);
                if((D[u]==1&&++c>1)||(D[u]!=-1&&up>=D[u]))art[u]=true;
            }else if(P[u]!=v)top=min(top,D[v]);
        }
        return top;
    }
    const vector<vector<int>>&E;int N,T;
    vector<int>P,D;
};