template<typename T> struct Fenwick {
    explicit Fenwick(ui N=0, T t=T()):N(1u<<logceil(N)),F(this->N,t),t(t){}
    explicit Fenwick(const vector<T>&A, T t=T()):N(1u<<logceil(A.size())),F(A),t(t){
        F.resize(N); fill(F.begin()+A.size(),F.end(),t);
        for(int i=0;i<N;i++){int j=i+lsb(i+1);if(j<N)F[j]+=F[i];}}
    void add(int i, T v){while(i<=N){F[i]+=v;i+=lsb(i+1);}}
    T sum(int i)const{T sum(t);while(i){sum+=F[i-1];i-=lsb(i);}return sum;}
    T range(int i,int j)const{j++; T s(t);while(j>i){s+=F[j-1];j-=lsb(j);}while(i>j){s-=F[i-1];i-=lsb(i);}return s;}
    T get(int i)const{return range(i,i);}
    void set(int i, T v) {add(i, v-get(i)); }
    constexpr int lsb(int i)const{return i&-i;}
    ui N;vector<T> F;T t;
    int max_lower(T v) {
        // TODO: this returns suspicious results ...
        if (F[0] >= v) return -1;
        if (F[N-1] < v) return N-1;
            
        int x = 0; T a = t;
        for (int s = N>>1; s > 0; s >>= 1) if (a+F[x+s-1]<v) { a += F[x+s-1]; x += s; }
        return x;
    }
};

template<typename T> struct Fenwick2 {
    explicit Fenwick2(ui N=0, T t=T()):N(1u<<logceil(N)),F(this->N,this->N,t),t(t){}
//    explicit Fenwick2(const vector<vector<T>>&A, T t=T()):N(1u<<logceil(A.size())),F(A),t(t){
//            F.resize(N);
//            for (int i=0;i<A.size();++i) { F[i].resize(N); fill(F[i].begin()+A.size(),F[i].end(),t); }
//            for (int i=A.size();i<N;++i) { F[i].resize(N); fill(F[i].begin(),F[i].end(),t); }
//
////            for(int i=0;i<N;i++){int j=i+lsb(i+1);if(j<N)F[j]+=F[i];}
//    }
    void add(int x, int y, T v){
        while(x<=N){ int z = y; while(z<=N) { F[x][z] += v; z += lsb(z+1); }x +=lsb(x+1); }
    }

    T sum(int x, int y) {
        T sum(t);
        while (x <= N) { int z = y;while (z <= N) { sum += F[x][z];z -= lsb(z + 1); }x -= lsb(x + 1); }
        return sum;
    }
    T range(int x1, int y1, int x2, int y2) {
        T ans = sum(x2, y2);
        if (x1) ans -= sum(x1-1, y2);
        if (y1) ans -= sum(x2, y1-1);
        if (x1 && y1) ans += sum(x1-1,y1-1);
        return ans;
    }
    constexpr int lsb(int i)const{return i&-i;}
    ui N;vector2<T> F;T t;
};