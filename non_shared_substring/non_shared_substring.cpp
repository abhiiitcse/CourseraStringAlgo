#include <bits/stdc++.h>

using namespace std;

struct Node{
  vector<Node*> next_nodes;
  vector<pair<int,int> > edges;
};

int getCommonStrLen(const string &text, int nodePos, int substrIndex, int nodeLen){
  int sameCharNum = 0;
  while(text[nodePos+sameCharNum]==text[substrIndex+sameCharNum]){
    ++sameCharNum;
    if(((substrIndex+sameCharNum)>=text.size())||(sameCharNum>=nodeLen)){
      break;
    }
  }
  return sameCharNum;
}

void updateTree(Node *root, const string &text, int substringIndex){
  if(substringIndex >= text.size()){
    return;
  }
  for(int i=0;i<root->next_nodes.size();i++){
    int startingPos = root->edges[i].first;
    int nodeLen = root->edges[i].second;
    int commonStrLen = getCommonStrLen(text, startingPos, substringIndex, nodeLen);
    if((commonStrLen>0)&&(commonStrLen<nodeLen)){
      Node *oldNode = root->next_nodes[i];
      Node *newNode = new Node;
      pair<int,int> partOldEdge(startingPos + commonStrLen, nodeLen - commonStrLen);
      pair<int,int> newEdge(substringIndex+commonStrLen,text.size()-substringIndex-commonStrLen);
      Node *middle = new Node;
      middle->next_nodes.push_back(oldNode);
      middle->next_nodes.push_back(newNode);
      middle->edges.push_back(partOldEdge);
      middle->edges.push_back(newEdge);
      root->next_nodes[i] = middle;
      root->edges[i].second = commonStrLen;
      return;
    }else if(commonStrLen==nodeLen){
      Node *nextNode = root->next_nodes[i];
      updateTree(nextNode, text, substringIndex+commonStrLen);
      return;
    }else if((commonStrLen==0)&&(i==(root->next_nodes.size()-1))){
      Node *new_node = new Node;
      root->next_nodes.push_back(new_node);
      pair<int,int> newEdge(substringIndex,text.size()-substringIndex);
      root->edges.push_back(newEdge);
      return;
    }
  }
  Node *new_node = new Node;
  root->next_nodes.push_back(new_node);
  pair<int,int> stringIndex(substringIndex,text.size()-substringIndex);
  root->edges.push_back(stringIndex);
  return;
}

Node* constructSuffixTree(const string &str){
  Node *root = new Node;
  for(int i=0;i<str.size();i++){
    updateTree(root,str,i);
  }
  return root;
}

bool getMinLength(Node *root, int p_len, int q_len, int &minLen){
  for(int i=0;i<root->next_nodes.size();i++){
    if(root->edges[i].first<p_len){
      if(!getMinLength(root->next_nodes[i],p_len,q_len,minLen)){
	int currLen = root->edges[i].first+root->edges[i].second;
	currLen = (currLen>p_len)?p_len:currLen;
	if(currLen<minLen){
	  cout<<"yes"<<endl;
	  minLen = currLen;
	}
      }
    }else if(root->edges[i].first > p_len){
      return true;
    }
    //getMinLength(root->next_nodes[i],p_len,q_len,minLen);
  }
  return false;
}

void printSuffixTree(Node *root, const string &text){
  for(int i=0;i<root->next_nodes.size();i++){
    cout<<text.substr(root->edges[i].first,root->edges[i].second)<<endl;
    printSuffixTree(root->next_nodes[i],text);
  }
}

string solve (string p, string q){
  string result = p;
  string new_str = p+'#'+q+'$';
  Node *root = constructSuffixTree(new_str);
  cout<<"printing suffix tree ..."<<endl;
  printSuffixTree(root,new_str);
  int minLen = 100000;
  int p_len = p.size();
  int q_len = q.size();
  getMinLength(root,p_len,q_len,minLen);
  cout<<"min length = "<<minLen<<endl;
  return result;
}

int main (void){
  ios::sync_with_stdio(false);
  string p;
  cin >> p;
  string q;
  cin >> q;

  string ans = solve (p, q);

  cout << ans << endl;

  return 0;
}
