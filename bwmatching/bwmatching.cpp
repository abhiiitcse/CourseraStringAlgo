#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#define MAX_CHAR 256

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;
using std::cout;
using std::endl;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  int count[MAX_CHAR];
  memset(count,0,sizeof count);
  for(int i=0;i<bwt.size();i++){
    count[bwt[i]]++;
  }
  for(int i=1;i<MAX_CHAR;i++){
    count[i] += count[i-1];
  }
  cout<<count['$']<<endl;
  for(int i=0;i<bwt.size();i++){
      starts[bwt[i]] = count[bwt[i]]--;
  }
  map<char,int>::iterator it;
  for(it=starts.begin();it!=starts.end();++it){
    starts[it->first] = it->second-1;
    cout<<it->first<<"->"<<it->second<<endl;
  }
  vector<int> count_charpos[MAX_CHAR];
  for(int i=0;i<MAX_CHAR;i++){
    count_charpos[i].push_back(0);
  }
  for(int i=0;i<bwt.size();i++){
    for(int j=0;j<MAX_CHAR;j++){
      if(i>0){
	if(bwt[i]==j){
	  count_charpos[j].push_back(1+count_charpos[j][count_charpos[j].size()-1]);
	}else{
	  count_charpos[j].push_back(count_charpos[j][count_charpos[j].size()-1]);
	}
      }else{
	if(bwt[i]==j){
	  count_charpos[j].push_back(1);
	}else{
	  count_charpos[j].push_back(0);
	}
      }
    }
  }
  
  for(int i=0;i<bwt.size();i++){
    occ_count_before[bwt[i]] = count_charpos[bwt[i]];
  }
  map<char,vector<int> >::iterator it1;
  for(it1=occ_count_before.begin();it1!=occ_count_before.end();++it1){
    cout<<it1->first<<": ";
    for(int i=0;i<it1->second.size();i++){
      cout<<it1->second[i]<<",";
    }
    cout<<endl;
  }
  
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     map<char, int>& starts, 
                     map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  int top = 0;
  int bottom = bwt.size()-1;
  string tempPattern = pattern;
  while (top<=bottom){
    int patternLen = tempPattern.length();
    if(patternLen>0){
      char symbol = tempPattern[patternLen-1];
      tempPattern.pop_back();
      if((occ_count_before[symbol][top+1]<occ_count_before[symbol][bottom+1]) || (occ_count_before[symbol][top]<occ_count_before[symbol][bottom+1])){
	top = starts[symbol] + occ_count_before[symbol][top];
	bottom = starts[symbol] + occ_count_before[symbol][bottom+1] - 1;
      }else{
	return 0;
      }
    }else{
      return bottom-top+1;
    }
  }
  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
