#include <string>
#include <iostream>
#include <vector>
#include <map>
#define FOR(i,a,b) for(size_t i=a;i<b;i++)
#define pb push_back

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  edges root;
  t.pb(root);
  int nodeNum = 0;
  FOR(i,0,patterns.size()){
    int currNode = 0;
    FOR(j,0,patterns[i].length()){
      char currSymbol = patterns[i][j];
      if(t[currNode].find(currSymbol)!=t[currNode].end()){
	currNode = t[currNode][currSymbol];
      }else{
	t[currNode][currSymbol] = ++nodeNum;
	edges temp;
	t.pb(temp);
	currNode = nodeNum;
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
