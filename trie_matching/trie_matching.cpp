#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define pb push_back

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
  int next [Letters];

  Node ()
  {
    fill (next, next + Letters, NA);
  }

  bool isLeaf () const
  {
    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
  }
};

typedef vector<Node> trie;
int letterToIndex (char letter)
{
  switch (letter)
    {
    case 'A': return 0; break;
    case 'C': return 1; break;
    case 'G': return 2; break;
    case 'T': return 3; break;
    default: assert (false); return -1;
    }
}

trie build_trie(const vector<string> &patterns){
  trie t;
  Node edge;
  t.pb(edge);
  int nodeNum = 0;
  FOR(i,0,patterns.size()){
    int currNode = 0;
    FOR(j,0,patterns[i].length()){
      int currSymInd = letterToIndex(patterns[i][j]);
      if(t[currNode].next[currSymInd] == NA){
	t[currNode].next[currSymInd] = ++nodeNum;
	Node temp;
	t.pb(temp);
	currNode = nodeNum;
      }else{
	currNode = t[currNode].next[currSymInd];
      }
    }
  }
  return t;
}

int prefixTrieMatching(const string &text, trie t){
  Node currNode = t[0];
  int curInd = 0;
  int currSymbol = letterToIndex(text[curInd]);
  while(true){
    if(currNode.isLeaf()){
      return 1;
    }else if(currNode.next[currSymbol]!=NA){
      currNode = t[currNode.next[currSymbol]];
      if(curInd < text.size()-1){
	currSymbol = letterToIndex(text[++curInd]);
      }else{
	if(currNode.isLeaf()){
	  return 1;
	}else{
	  return 0;
	}
      }
    }else{
      return 0;
    }
  }
  return 0;		 
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
  vector <int> result;
  trie t = build_trie(patterns);
  FOR(i,0,text.length()){
    string currText = text.substr(i,text.length()-i);
    int isMatch = prefixTrieMatching(currText,t);
    if(isMatch){
      result.pb(i);
    }
  }

  return result;
}

int main (void)
{
  string t;
  cin >> t;

  int n;
  cin >> n;

  vector <string> patterns (n);
  for (int i = 0; i < n; i++)
    {
      cin >> patterns[i];
    }

  vector <int> ans;
  ans = solve (t, n, patterns);

  for (int i = 0; i < (int) ans.size (); i++)
    {
      cout << ans[i];
      if (i + 1 < (int) ans.size ())
	{
	  cout << " ";
	}
      else
	{
	  cout << endl;
	}
    }

  return 0;
}
