#include <bits/stdc++.h>
using namespace std;

// Macro
#define  int  long long
#define  ALL(x)  (x).begin(), (x).end()
#define  FORE(i, v)  for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)
#define  FOR(i, a, b)  for(int i = (a), _b = (b); i <= _b; ++ i)
#define  FORD(i, b, a)  for(int i = (b), _a = (a); i >= _a; -- i)

// Number of tests
const int NTEST = 100;

// Name of two files
const string NAME = "code";

// Generate random number according to computer clock
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Random number in range [L, R]
int randInt(int L, int R){
  assert(L <= R);
  return uniform_int_distribution<int>(L, R)(rng);
}

// Random shuffle vector v
template<class T> void shuf(vector<T> &v){
  shuffle(ALL(v), rng);
}

// Generate permutation in [1, N] from index [1, N]
// 0 at index 0
vector<int> gen_perm(int N){
  vector<int> perm;
  FOR(i, 1, N){
    perm.push_back(i);
  }
  shuf(perm);
  perm.insert(perm.begin(), 0);
  return perm;
}

// Shuffle edge
void shuf_edge(vector<pair<int, int>> &edge, int N){
  vector<int> perm = gen_perm(N);
  FORE(i, edge){
    i->first = perm[i->first];
    i->second = perm[i->second];
    if(rng() & 1) swap(i->first, i->second);    
  }
}

// Generate normal graph
namespace gen_graph{
  vector<pair<int, int>> gentest(int N, int M){
    // Generate random graph maybe have multiple components
    vector<pair<int, int>> edge;
    set<pair<int, int>> st;
    vector<int> perm = gen_perm(N);
    while((int)edge.size() < M){
      int l = randInt(1, N);
      int r = randInt(1, N);
      // Don't have self edge and every edge appear one time only
      if(l == r || st.count(make_pair(min(l, r), max(l, r))) != 0){
        continue;
      }
      if(rng() & 1){
        edge.push_back(make_pair(l, r));
        st.insert(make_pair(min(l, r), max(l, r)));
      }
    }
    shuf_edge(edge, N);
    return edge;
  }
};

// Generate tree
namespace gen_tree{
  struct DisjointSetUnion{
    vector<int> sz;
    vector<int> par;
    int N;
  
    DisjointSetUnion(int sizes){
      N = sizes;
      sz.assign(N + 1, 1);
      par.assign(N + 1, -1);
    }
  
    int root(int u){
      if(par[u] < 0){
        return u;
      }
      else{
        par[u] = root(par[u]);
        return par[u];
      }
    }
  
    bool merge(int u, int v){
      u = root(u);
      v = root(v);
      if(u == v){
        return false;
      }
      if(sz[v] > sz[u]){
        swap(u, v);
      }
      sz[u] += sz[v];
      par[v] = u;
      return true;
    }
  };

  vector<pair<int, int>> gentest(bool types, int N){
    vector<pair<int, int>> edge;
    // Generate random tree
    if(types == true){
      DisjointSetUnion dsu(N);
      vector<int> perm = gen_perm(N);
      while((int)edge.size() < N - 1){
        int u = perm[randInt(1, N)];
        int v = perm[randInt(1, N)];
        if(dsu.merge(u, v) == true){
          edge.push_back(make_pair(u, v));
        }
      }
    }
    // Generate line tree
    else{
      vector<int> perm = gen_perm(N);
      FOR(i, 1, N - 1){
        edge.push_back(make_pair(perm[i], perm[i + 1]));
      }
    }
    shuf_edge(edge, N);
    return edge;
  }
};

// Main gentest generator 
void gentest(void){
  ofstream out((NAME + ".inp").c_str());

  

  out.close();
}

signed main(void){
  // Don't forget this!!!
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
