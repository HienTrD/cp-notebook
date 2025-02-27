#include <bits/stdc++.h>
using namespace std;

/// Macro
#define  fi  first 
#define  se  second
#define  int  long long
#define  ALL(x)  (x).begin(), (x).end()
#define  BIT(x)  (1LL << (x))
#define  MASK(x, i)  (((x) >> (i)) & 1)
#define  FORE(i, v)  for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)
#define  FOR(i, a, b)  for(int i = (a), _b = (b); i <= _b; ++ i)
#define  FORD(i, b, a)  for(int i = (b), _a = (a); i >= _a; -- i)

/// Number of tests
const int NTEST = 1000;

/// Name of two files
const string NAME = "code";

/// Generate random number according to computer clock
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/// Random number in range [L, R]
int randInt(int L, int R){
  assert(L <= R);
  return uniform_int_distribution<int>(L, R)(rng);
}

/// Randomly shuffle a vector 
template<class T>
  void shuf(vector<T> &v){
    shuffle(ALL(v), rng);
  }

/// Generate random permutation of [1, N]
/// *To make sure the permutation always in [1, N] from index [1, N]. We will put 0 at the index 0.
vector<int> random_perm_gen(int N){
  vector<int> v;
  FOR(i, 1, N) v.push_back(i);
  shuf(v);
  v.insert(v.begin(), 0);
  return v;
}

/// Generate vector with all entries in [L, R]
vector<int> random_vector_gen(int N, int L, int R){
  vector<int> v;
  FOR(i, 1, N) v.push_back(randInt(L, R));
  return v;
}

/// Random graph
/// Generate permutation + randomize edge
void gentest_graph(vector<pair<int, int>> &edge, vector<int> perm){
  FORE(i, edge){
    i->first = perm[i->first];
    i->second = perm[i->second];
    if(rng() & 1) swap(i->first, i->second);
  }
}

/// Random DAG
/// Generate permutation + Topo sort
vector<pair<int, int>> gentest_dag(int N, int M, vector<int> perm){
  vector<pair<int, int>> edge;
  int cnt = 0;
  while(cnt < M){
    FOR(i, 1, N - 1){
      if(cnt >= M) break;
      FOR(j, i + 1, N){
        if(cnt >= M) break;
        else if(rng() & (int)(1e9 + 7)) edge.push_back(make_pair(perm[i], perm[j])), ++ cnt;
      }
    }
  }
  FOR(i, 1, N){
    int l = randInt(0, M - 1);
    int r = randInt(0, M - 1);
    if(rng() & 1) swap(edge[l], edge[r]);
  }
  return edge;
}

/// Random Tree
/// Generate permutation + DSU
namespace gentest_tree{
  struct DisjointSetUnion{
    vector<int> sz;
    vector<int> par;

    DisjointSetUnion(int sizes) : sz(sizes + 1, 1), par(sizes + 1, -1){};

    int root(int u){
      return par[u] < 0 ? u : par[u] = root(par[u]);
    }

    bool merge(int u, int v){
      u = root(u);
      v = root(v);
      if(u == v) return false;
      if(sz[v] > sz[u]) swap(u, v);
      sz[u] += sz[v];
      par[v] = u;
      return true;
    }
  };

  vector<pair<int, int>> gentest(int N){
    DisjointSetUnion dsu(N);
    vector<int> perm;
    vector<pair<int, int>> edge;
    FOR(i, 2, N) perm.push_back(i);
    perm.insert(perm.begin(), 1);
    perm.insert(perm.begin(), 0);
    int cnt = 0;
    while(cnt < N - 1){
      FOR(i, 1, N){
        int u = perm[i];
        int v = perm[randInt(i + 1, N)];
        if(dsu.merge(u, v) == true){
          ++ cnt;
          edge.push_back(make_pair(u, v));
        }
        if(cnt == N - 1) break;
      }
    }
    FOR(i, 1, N){
      int l = randInt(0, N - 2);
      int r = randInt(0, N - 2);
      if(rng() & 1) swap(edge[l], edge[r]);
    }
    return edge;
  }
};

/// Main gentest generator 
void gentest(void){
  ofstream out((NAME + ".inp").c_str());

  

  out.close();
}

signed main(void){
  srand(time(nullptr));

  FOR(i, 1, NTEST){
    gentest();
    system((NAME + "_slow.exe").c_str());
    system((NAME + "_ac.exe").c_str());
    if(system(("fc " + NAME + ".out " + NAME + ".ans").c_str()) != 0){
      cout << "Testcase " << i << ": Wrong Answer!!!" << endl;
      return 0;
    }
    cout << "Testcase " << i << ": Accepted!!!" << endl;
  }
  return 0;
}
