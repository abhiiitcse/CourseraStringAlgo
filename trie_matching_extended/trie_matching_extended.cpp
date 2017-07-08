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
  bool patternEnd;

  Node ()
  {
    fill (next, next + Letters, NA);
    patternEnd = false;
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

trie build_trie(vector<string> &patterns){
  trie t;
  Node edge;
  t.pb(edge);
  int nodeInd = 0;
  FOR(i,0,patterns.size()){
    int currNode = 0;
    FOR(j,0,patterns[i].length()){
      int currSymInd = letterToIndex(patterns[i][j]);
      int nextNode = t[currNode].next[currSymInd];
      if(nextNode!=NA){
	if(j==(patterns[i].length()-1)){
	  t[nextNode].patternEnd = true;
	}else{
	  currNode = nextNode;
	}
      }else{
	t[currNode].next[currSymInd] = ++nodeInd;
	Node temp;
	if(j==(patterns[i].length()-1)){
	  temp.patternEnd = true;
	}
	t.pb(temp);
	currNode = nodeInd;
      }
    }
  }
  return t;
}

int patternTrieMatching(string text, trie t){
  Node currNode = t[0];
  int currInd = 0;
  int currSymInd = letterToIndex(text[currInd]);
  while(true){
    if(currNode.patternEnd){
      return 1;
    }else if(currNode.next[currSymInd]!=NA){
      currNode = t[currNode.next[currSymInd]];
      if(currInd<text.length()-1){
	currSymInd = letterToIndex(text[++currInd]);
      }else{
	if(currNode.patternEnd){
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

vector <int> solve (string text, int n, vector <string> patterns)
{
  vector <int> result;
  trie t = build_trie(patterns);
  FOR(i,0,text.length()){
    string currText = text.substr(i,text.length()-i);
    int isMatch = patternTrieMatching(currText,t);
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
