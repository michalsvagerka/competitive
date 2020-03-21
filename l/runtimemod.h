int MOD;

class RField {
    typedef unsigned int ui;
    typedef unsigned long long ull;
    inline int pow(int a, ll p){ui r=1,e=a;while(p){if(p&1){r=((ull)r*e)%MOD;}e=((ull)e*e)%MOD;p>>=1;}return r;}
    /*extended GCD(slow):ll t=0,nt=1,r=MOD,nr=a;while(nr){ll q=r/nr;t-=q*nt;swap(t,nt);r-=q*nr;swap(r,nr);}assert(r<=1);return(t<0)?t+MOD:t;*/
    inline int inv(int a){return pow(a,MOD-2);}
public:
    inline RField(int x = 0) : v(x) {}
    inline RField pow(int p){return (*this)^p; }
    inline RField operator^(ll p){return {pow(v,p)};}
    inline RField&operator+=(const RField&o) {checkMod(o);if ((ll)v+o.v >= MOD) v = (ll)v+o.v-MOD; else v = v+o.v; return *this; }
    inline RField&operator-=(const RField&o) {checkMod(o);if (v<o.v) v = MOD-o.v+v; else v=v-o.v; return *this; }
    inline RField&operator*=(const RField&o) {checkMod(o);v=ll(v)*o.v % MOD; return *this; }
    inline RField&operator/=(const RField&o) {checkMod(o); return *this*=RField{inv(o.v)}; }
    inline RField operator+(const RField&o) const {RField r{*this};return r+=o;}
    inline RField operator-(const RField&o) const {RField r{*this};return r-=o;}
    inline RField operator*(const RField&o) const {RField r{*this};return r*=o;}
    inline RField operator/(const RField&o) const {RField r{*this};return r/=o;}
    inline RField operator-() {if(v) return {MOD-v}; else return {0};};
    inline RField& operator++() { ++v; if (v==MOD) v=0; return *this; }
    inline RField operator++(int) { RField r{*this}; ++*this; return r; }
    inline RField& operator--() { --v; if (v==-1) v=MOD-1; return *this; }
    inline RField operator--(int) { RField r{*this}; --*this; return r; }
    inline bool operator==(const RField&o) const { return o.v==v; }
    inline bool operator!=(const RField&o) const { return o.v!=v; }
    inline explicit operator int() const { return v; }
    void checkMod(const RField&o) {}
    inline static vector<RField>fact(int t){vector<RField>F(t+1,1);for(int i=2;i<=t;++i){F[i]=F[i-1]*i;}return F;}
//    inline static vector<RField>invfact(int t){vector<RField>F(t+1,1);RField X{1};for(int i=2;i<=t;++i){X=X*i;}F[t]=1/X;for(int i=t-1;i>=2;--i){F[i]=F[i+1]*(i+1);}return F;}
private:
    int v;
};
//istream &operator>>(std::istream&is,RField&f){unsigned int v;is>>v;f=v;return is;}
ostream &operator<<(std::ostream&os,const RField&f){return os<<int(f);}
RField operator+(int i,const RField&f){return i+f;}
RField operator-(int i,const RField&f){return i-f;}
RField operator*(int i,const RField&f){return i*f;}
RField operator/(int i,const RField&f){return i/f;}
