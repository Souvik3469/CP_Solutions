#include <bits/stdc++.h>

#include <cmath>

#include <ext/pb_ds/assoc_container.hpp>

#include <ext/pb_ds/tree_policy.hpp>

#define sz(x) ((int)(x).size())
#define ll long long int
#define ld long double
#define ull unsigned long long
#define ordered_set tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>

#define pb push_back
// #define mod 1000000007
#define fastread() (ios_base::sync_with_stdio(false), cin.tie(NULL));
#define in_range(i, x, y) for (int i = x; i <= y; i++)
#define in_range_back(i, x, y) for (int i = y; i >= x; i--)
#define debug(x) cout << #x << " -> " << x << endl

#define ff first
#define ss second

using namespace std;
using namespace __gnu_pbds;
const ll mod = 1e9 + 7;
const ll mod1 = 998244353;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
/***********MODULAR*************/
ll modadd(ll a, ll b, ll p)
{
    return (a + b) % p;
}

ll modsub(ll a, ll b, ll p)
{
    return ((a - b) % p + p) % p;
}

ll modmul(ll a, ll b, ll p)
{
    return ((a % p) * (b % p)) % p;
}


ll modpow(ll x, ll y, ll p)
{
    ll res = 1;

    x = x % p;

    if (x == 0)
        return 0;

    while (y > 0)
    {

        if (y & 1)
            res = (1LL * res * x) % p;

        y = y >> 1;
        x = (1LL * x * x) % p;
    }
    return res;
}

ll modinv(ll a, ll p)
{
   return modpow(a,p-2,p);
    
}
ll modfact(ll n, ll p)
{
    vector<ll> f(n + 1);
    f[0] = 1;
    for (ll i = 1; i <= n; i++)
    {
        f[i] = ((i % p) * (f[i - 1] % p)) % p;
    }
    return f[n] % p;
}

ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}

/*************MODULAREND**********/
class DSU {
public:
    vector<ll> parent;
    vector<ll> rank;

    DSU(ll n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (ll i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    ll find(ll x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

   void Union(ll x, ll y) {
        ll xroot = find(x);
        ll yroot = find(y);
        if (xroot == yroot) {
            return;
        }
        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
};
ll fceil(ll a, ll b)
{
    if (a % b == 0)
        return a / b;
    else
        return a / b + 1LL;
}
/************DEBUG**************/
void debugv(vector<ll> &v)
{
    cout << "Vector" << endl;
    for (auto x : v)
        cout << x << " ";
    cout << endl;
}
void debugp(vector<pair<ll, ll>> &v)
{
    cout << "Pair" << endl;
    for (auto x : v)
        cout << x.ff << " " << x.ss << "    ";
    cout << endl;
}
void debugm(map<ll, ll> &mp)
{
    cout << "MAP" << endl;
    for (auto x : mp)
        cout << x.ff << " " << x.ss << "     ";
    cout << endl;
}
void debugmat(vector<vector<ll>> &mat)
{
    cout << "MATRIX" << endl;
    for (ll i = 0; i < mat.size(); i++)
    {
        for (ll j = 0; j < mat[0].size(); j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
/***************DEBUGEND**************/
/****************rabinkarp***********/
ll compute_hash(string s)
{
    ll p = 31;
    ll m = 1e9 + 9;
    ll hash_value = 0;
    ll n = s.size();
    vector<ll> p_pow(n);
    p_pow[0] = 1;
    for (ll i = 1; i < n; i++)
        p_pow[i] = (p_pow[i - 1] * p) % m;
    for (ll i = 1; i < n; i++)
    {
        hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow[i]) % m;
    }
    return hash_value;
}

vector<ll> rabin_karp(string const &s, string const &t)
{
    const int p = 31;
    const int m = 1e9 + 9;
    ll S = s.size(), T = t.size();

    vector<ll> p_pow(max(S, T));
    p_pow[0] = 1;
    for (ll i = 1; i < (ll)p_pow.size(); i++)
        p_pow[i] = (p_pow[i - 1] * p) % m;

    vector<ll> h(S + 1, 0);
    for (ll i = 0; i < S; i++)
        h[i + 1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;
    ll ht = 0;
    for (int i = 0; i < T; i++)
        ht = (ht + (t[i] - 'a' + 1) * p_pow[i]) % m;

    vector<ll> occurrences;
    for (ll i = 0; i + T - 1 < S; i++)
    {
        long long cur_h = (h[i + T] + m - h[i]) % m;
        if (cur_h == ht * p_pow[i] % m)
            occurrences.push_back(i);
    }
    return occurrences;
}

ll compute_hash1(string s)
{
    ll n = s.size();
    ll h = 0;
    ll m = 1e9 + 9;
    for (ll i = 0; i < n; i++)
        h = (h * 31 + (s[i] - 'a' + 1)) % m;
    return h;
}

vector<ll> rabin_karp1(string const &s, string const &t)
{
    ll p = 1;
    ll m = 1e9 + 9;
    ll S = s.size(), T = t.size();
    for (ll i = 0; i < T - 1; i++)
        p = (p * 31) % m;

    ll ht = compute_hash1(t);
    ll hs = compute_hash1(s.substr(0, T));

    vector<ll> occurrences;
    if (hs == ht)
        occurrences.pb(0);
    for (ll i = 1, j = T; j < S; i++, j++)
    {
        ll del = ((s[i - 1] - 'a' + 1) * p) % m;
        ll add = s[j] - 'a' + 1;
        hs = ((hs - del + m) * 31 + add) % m;
        if (hs == ht)
            occurrences.pb(i);
    }
    return occurrences;
}
ll compute_hash2(string &s){
    ll ans = 0;
    ll pr = 1;
    ll m=1e9+9;
    for(ll i = 0; i < s.size(); i++){
        ans = (ans + ((s[i] - 'a'+ 1ll) * pr) % m) % m;
        pr = (pr * 31ll) % m;
    }
    return ans;
}
typedef struct Hashing
{
    string s;
    int n;
    int primes;
    vector<long long> hashPrimes = {1000000009, 100000007};
    const long long base = 31;
    vector<vector<long long> > hashValues;
    vector<vector<long long> > powersOfBase;
    vector<vector<long long> > inversePowersOfBase;
    Hashing(string a)
    {
        primes = sz(hashPrimes);
        hashValues.resize(primes);
        powersOfBase.resize(primes);
        inversePowersOfBase.resize(primes);
        s = a;
        n = s.length();
        for (int i = 0; i < sz(hashPrimes); i++)
        {
            powersOfBase[i].resize(n + 1);
            inversePowersOfBase[i].resize(n + 1);
            powersOfBase[i][0] = 1;
            for (int j = 1; j <= n; j++)
            {
                powersOfBase[i][j] = (base * powersOfBase[i][j - 1]) % hashPrimes[i];
            }
            inversePowersOfBase[i][n] = mminvprime(powersOfBase[i][n], hashPrimes[i]);
            for (int j = n - 1; j >= 0; j--)
            {
                inversePowersOfBase[i][j] = modmul(inversePowersOfBase[i][j + 1], base, hashPrimes[i]);
            }
        }
        for (int i = 0; i < sz(hashPrimes); i++)
        {
            hashValues[i].resize(n);
            for (int j = 0; j < n; j++)
            {
                hashValues[i][j] = ((s[j] - 'a' + 1LL) * powersOfBase[i][j]) % hashPrimes[i];
                hashValues[i][j] = (hashValues[i][j] + (j > 0 ? hashValues[i][j - 1] : 0LL)) % hashPrimes[i];
            }
        }
    }
    vector<long long> substringHash(int l, int r) // O(1)
    {
        vector<long long> hash(primes);
        for (int i = 0; i < primes; i++)
        {
            long long val1 = hashValues[i][r];
            long long val2 = l > 0 ? hashValues[i][l - 1] : 0LL;
            hash[i] = modmul(modsub(val1, val2, hashPrimes[i]), inversePowersOfBase[i][l], hashPrimes[i]);
        }
        return hash;
    }
}Hashing;

/************************************/
bool iss(char ch)
{

    if (ch > 'a' && ch < 'z')
        return true;
    else
        return false;
}
bool isc(char ch)
{

    if (ch > 'A' && ch < 'Z')
        return true;
    else
        return false;
}
bool issorted(vector<int> &b, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (b[i] > b[i + 1])
            return false;
    }
    return true;
}
bool isr(string a, string b)
{
    int n = a.length();
    int m = b.length();
    if (n != m)
        return false;
    int i = 0;
    int j = m - 1;
    while (i < n && j >= 0)
    {
        if (a[i] != b[j])
            return false;
        i++;
        j--;
    }
    return true;
}

bool ispal(string s)
{
    int i = 0;
    int j = s.length() - 1;
    while (i < j)
    {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

ll LIS(vector<ll> &nums)
{
    vector<ll> dp(nums.size(), 1);
    for (ll i = 0; i < nums.size(); i++)
        for (ll j = i - 1; j >= 0; j--)
            if (nums[i] > nums[j])
                dp[i] = max(dp[i], 1 + dp[j]);
    return *max_element(dp.begin(), dp.end());
}

bool ispv(vector<ll> &a, ll n)
{

    for (ll i = 1; i < n - 1; i++)
    {
        if (!((a[i - 1] < a[i] && a[i] > a[i + 1]) || (a[i - 1] > a[i] && a[i] < a[i + 1])))
        {
            return false;
        }
    }
    return true;
}

ll mex(vector<ll> &arr, int N)
{

    // sort the array
    sort(arr.begin(), arr.end());

    ll mex = 0;
    for (ll idx = 0; idx < N; idx++)
    {
        if (arr[idx] == mex)
        {
            // Increment mex
            mex += 1;
        }
    }

    // Return mex as answer
    return mex;
}

ll power(ll base, ll exponent)
{
    if (exponent == 0)
        return 1;
    if (exponent == 1)
        return base;

    ll result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return result;
}
bool ispower(ll n, ll b)
{
    /*if (n == 0)
        return false;

    ll c = 0;
    while (n % b == 0 && n > 1)
    {
        n /= b;
        c++;
    }

    if (n == 1)
    {
        return true;
    }

    return false;*/

    return (fceil(log(n), log(b))) == (floor(log(n) / log(b)));
}

bool primes[2000001];
void pr(ll n)
{
    fill(primes, primes + n + 1, true);
    primes[0] = false;
    primes[1] = false;
    for (ll i = 2; i <= n; i++)
    {
        if (primes[i])
        {
            for (ll j = i * 2; j <= n; j += i)
                primes[j] = false;
        }
    }
}
// map<ll,ll>prev_val;
// ll n;
// ll query(ll idx){
//     if(prev_val.find(idx)!=prev_val.end())return prev_val[idx];
//     if(idx==0||idx==n+1)return LLONG_MAX-1;
//     cout<<"? "<<idx<<endl;
//     ll val;
//     cin>>val;
//     return prev_val[idx]=val;
// }

void rotatematrix(vector<vector<ll>> &a)
{
    ll n=a.size();

    for (ll i = 0; i < n / 2; i++)
    {
        for (ll j = i; j < n - i - 1; j++)
        {
            ll t = a[i][j];
            a[i][j] = a[n - 1 - j][i];
            a[n - 1 - j][i] = a[n - 1 - i][n - 1 - j];
            a[n - 1 - i][n - 1 - j] = a[j][n - i - 1];
            a[j][n - i - 1] = t;
        }
    }
}
bool isinc(vector<ll> &a, ll n)
{
    for (ll i = 0; i < n; i++)
    {
        if (i + 1 < n and a[i] >= a[i + 1])
            return false;
    }
    return true;
}
ll psum(ll l, ll r, vector<ll> &pr)
{
    if (l == 0)
    {
        return pr[r];
    }
    return pr[r] - pr[l - 1];
}

vector<ll> position(string str, string s)
{

    ll pos = str.find(s, 0);
        vector<ll>v;
    if (pos == string::npos)
        return v;

    while (pos != string::npos) {
        v.pb(pos);
        pos = str.find(s, pos + 1);
    }
    return v;
}



void solve(){
    ll sx,sy,tx,ty;
    cin>>sx>>sy>>tx>>ty;
    
    
    // debug(d1);
    // debug(d2);
    
    // ll a1=d1/2;
    // ll a2=d2/2;
    
     // debug(a1);
    // debug(a2);
    ll c=0;
  //   c=d2+(a1-min(a1,a2));
    
    if(sx>tx){
        if((sx+sy)%2!=0)sx--;
    }
    if(sx<tx){
        if((sx+sy)%2==0)sx++;
    }
    ll d1=abs(sx-tx);
    ll d2=abs(sy-ty);
    ll ex=0;
    if(sx>tx+d2){
        ex=(d1-d2+1)/2;
    }
    if(tx>sx+d2){
        ex=(d1-d2+1)/2;
    }
    c=d2+ex;
    cout<<c<<endl;
    
}
/*
   void dbg(){

    srand(time(NULL));
    int c=1;
    while(c<=1000){
        int n=rand()%5+1;
      vector<int>a(n);
        for(int i=0;i<n;i++)
        a[i]=rand()%7+1;
        int cans=cs(a,n);
        int mans=solve(a,n);
        if(cans!=mans){
            cout<<n<<endl;
            for(int i=0;i<n;i++)
            cout<<a[i]<<" ";
            cout<<endl;
            break;
        }
        c++;
    }
}

*/

signed main()
{
    // #ifndef ONLINE_JUDGE
    //     freopen("input1.txt", "r", stdin);
    //     freopen("output1.txt", "w", stdout);
    // #endif
    fastread();
    ll tt;
    // ll n;
    // cin>>n;
    // pr(1e6+1);
    // cout<<primes[n]<<endl;
    // vector<ll>v;
    // for(ll i=2;i<=1e6;i++){
    //     if(primes[i])v.pb(i);
    // }

    //cin >> tt;

    // while (tt--)
    // {

    //     solve();
    // }
    // dbg();

    // for (int i = 1; i <= tt; i++)
    // {
        // cout << "Case #" << i << ": ";
        solve();
    //}

    return 0;
}