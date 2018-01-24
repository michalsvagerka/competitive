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
};