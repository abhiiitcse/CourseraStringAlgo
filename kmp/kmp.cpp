#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::endl;

vector<int> preprocess_pattern(const string& pattern){
  vector<int> lps(pattern.size(),0);
  int len = 0;
  lps[0] = 0;
  int i = 1;
  int M = pattern.size();
  while(i<M){
    if(pattern[len] == pattern[i]){
      len++;
      lps[i] = len;
      i++;
    }else{
      if(len!=0){
	len = lps[len-1];
      }else{
	lps[i] = 0;
	i++;
      }
    }
  }
  return lps;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  vector<int> lps = preprocess_pattern(pattern);
  // Implement this function yourself
  int M = pattern.size();
  int N = text.size();
  int i=0;
  int j=0;
  while(i<N){
    if(text[i]==pattern[j]){
      i++;
      j++;
    }
    if(j==M){
      result.push_back(i-j);
      j = lps[j-1];
    }else if(i<N && pattern[j]!=text[i]){
      if(j!=0){
	j=lps[j-1];
      }else{
	i++;
      }
    }
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
