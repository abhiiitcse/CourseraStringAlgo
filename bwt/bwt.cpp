#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";

  // write your code here
  vector<string> bwtMatrix;
  for(int i=0;i<text.size();i++){
    string new_str = "";
    for(int j=0;j<text.size();j++){
      new_str += text[(i+j)%text.size()];
    }
    bwtMatrix.push_back(new_str);
  }
  sort(bwtMatrix.begin(),bwtMatrix.end());
  for(int i=0;i<bwtMatrix.size();i++){
    result += bwtMatrix[i][bwtMatrix[i].size()-1];
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
