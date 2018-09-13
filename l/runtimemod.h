class RField {
    typedef unsigned int ui;
    typedef unsigned long long ull;
    inline int pow(int a, ll p){ui r=1,e=a;while(p){if(p&1){r=((ull)r*e)%N;}e=((ull)e*e)%N;p>>=1;}return r;}
    /*extended GCD(slow):ll t=0,nt=1,r=N,nr=a;while(nr){ll q=r/nr;t-=q*nt;swap(t,nt);r-=q*nr;swap(r,nr);}assert(r<=1);return(t<0)?t+N:t;*/
    inline int inv(int a){return pow(a,N-2);}
public:
    inline RField(int x = 0, int N = 0) : N(N), v(x) {}
    inline RField pow(int p){return (*this)^p; }
    inline RField operator^(ll p){return {pow(v,p),N};}
    inline RField&operator+=(const RField&o) {checkMod(o);if ((ll)v+o.v >= N) v = (ll)v+o.v-N; else v = v+o.v; return *this; }
    inline RField&operator-=(const RField&o) {checkMod(o);if (v<o.v) v = N-o.v+v; else v=v-o.v; return *this; }
    inline RField&operator*=(const RField&o) {checkMod(o);v=ll(v)*o.v % N; return *this; }
    inline RField&operator/=(const RField&o) {checkMod(o); return *this*={inv(o.v),N}; }
    inline RField operator+(const RField&o) const {RField r{*this};return r+=o;}
    inline RField operator-(const RField&o) const {RField r{*this};return r-=o;}
    inline RField operator*(const RField&o) const {RField r{*this};return r*=o;}
    inline RField operator/(const RField&o) const {RField r{*this};return r/=o;}
    inline RField operator-() {if(v) return {N-v,N}; else return {0,N};};
    inline RField& operator++() { ++v; if (v==N) v=0; return *this; }
    inline RField operator++(int) { RField r{*this}; ++*this; return r; }
    inline RField& operator--() { --v; if (v==-1) v=N-1; return *this; }
    inline RField operator--(int) { RField r{*this}; --*this; return r; }
    inline bool operator==(const RField&o) const { return o.v==v; }
    inline bool operator!=(const RField&o) const { return o.v!=v; }
    inline explicit operator int() const { return v; }
    void checkMod(const RField&o) {
        if (N == 0 && o.N == 0) {
            throw std::runtime_error("No modulus set");
        } else if (N == 0) {
            N = o.N;
        } else if (o.N != 0 && N != o.N) {
            cerr << N << ' ' << o.N << endl;
            throw std::runtime_error("Different moduli");
        }
    }
//    inline static vector<RField>fact(int t){vector<RField>F(t+1,1);for(int i=2;i<=t;++i){F[i]=F[i-1]*i;}return F;}
//    inline static vector<RField>invfact(int t){vector<RField>F(t+1,1);RField X{1};for(int i=2;i<=t;++i){X=X*i;}F[t]=1/X;for(int i=t-1;i>=2;--i){F[i]=F[i+1]*(i+1);}return F;}
private:
    int v; int N;
};
//istream &operator>>(std::istream&is,RField&f){unsigned int v;is>>v;f=v;return is;}
ostream &operator<<(std::ostream&os,const RField&f){return os<<int(f);}
RField operator+(int i,const RField&f){return i+f;}
RField operator-(int i,const RField&f){return i-f;}
RField operator*(int i,const RField&f){return i*f;}
RField operator/(int i,const RField&f){return i/f;}
