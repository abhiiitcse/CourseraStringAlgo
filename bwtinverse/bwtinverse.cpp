#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#define MAX_CHAR 256

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;

string InverseBWT(const string& bwt) {
  string text = "";
  string new_text = "";
  int count_arr[MAX_CHAR];
  memset(count_arr,0,sizeof count_arr);
  for(int i=0;i<bwt.size();i++){
    count_arr[bwt[i]]++;
  }
  for(int i=1;i<MAX_CHAR;i++){
    count_arr[i] += count_arr[i-1];
  }
  char first_row[bwt.size()];
  for(int i=0;i<bwt.size();i++){
    first_row[count_arr[bwt[i]]--] = bwt[i];
  }
  for(int i=1;i<=bwt.size();i++){
    new_text += first_row[i];
  }
  int charcnt[MAX_CHAR];
  memset(charcnt,0,sizeof charcnt);
  vector<pair<int,int> > lastcol;
  for(int i=0;i<bwt.size();i++){
    lastcol.push_back(make_pair(bwt[i],charcnt[bwt[i]]++));
  }
  memset(charcnt,0,sizeof charcnt);
  map<pair<int,int>,int> mpchar;
  for(int i=0;i<bwt.size();i++){
    mpchar.insert(make_pair(make_pair(new_text[i],charcnt[new_text[i]]++),i));
  }
  int lastindex = 0;
  for(int i=0;i<bwt.size();i++){
    text += new_text[lastindex];
    lastindex = mpchar[lastcol[lastindex]];
  }
  reverse(text.begin(),text.end());
			     

  
  

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
