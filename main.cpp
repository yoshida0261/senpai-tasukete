#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
using namespace std;

static vector<int> values;
static vector<int> prices;

/*
 商品の値段リスト  
 */
bool getValues(int count){
  if(count <= 0)
    return false;

  int temp;
  for(int i=0; i< count; i++){
    cin >> temp;
    values.push_back(temp);
  }

  sort(values.data(), values.data() + count);
  return true;
}
/*
 設定金額リスト
 */
bool getPrices(int count){
  if(count <= 0)
	return false;

  int temp;
  for(int i=0; i< count; i++){
    cin >> temp;
    prices.push_back(temp);
  }
	return true;
}
int total;//商品の総数
int days;//日数
void printParam();

/*
  文字列分割関数
  商品の総数、キャンペーンの日数を分割する
 */
vector<int> split(const string &str, char delim){
  istringstream iss(str); string tmp; vector<int> res;
  while(getline(iss, tmp, delim)) res.push_back(atoi(tmp.c_str()));
  return res;
}


bool getParameter(){
  string s1;
  getline(cin, s1);
  vector<int> n_d = split(s1, ' '); 
  total = n_d[0];
  days  = n_d[1]; 
  if(!getValues(total)){
    return false;
  }
  getPrices(days);
  //printParam();  
  
  return true;
}

/*
   debug 用メソッド
 */
void printParam()
{

  cout << "total " << total << endl;
  cout << "days" << days << endl; 
  
  vector<int>::iterator it = values.begin();
  while( it != values.end() )  
  {
    cout << *it << endl;  
    ++it;
  }

  it = prices.begin();
  while( it != prices.end() )
  {
    cout << *it << endl;   
    ++it;
  }

}


int totalAmount(int price)
{
//  cout << "price " << price << endl;
  int result = 0;

  int *v = values.data();
  int size = values.size();

  if(size == 1){
    cout << values[0] << endl;
    return values[0];
  }

  for(int i =0 ; i < size; i++){
    if(price < v[i]){
      break;
    }
    for(int j = 0; j < size; j++){
      if((((j != i ) && (v[j] == v[i])) ||
         (v[j] != v[i]) )&&
         ((v[j]+v[i]) <= price)){

        if(result < v[j] + v[i]){
          result = v[j] + v[i];
	}
        if(result == price){
          cout << result << endl;
          return result;
        }
      }
    }
  }
  cout << result << endl;
  return result;
}

int main(int argc, char** argv) {

  bool res = getParameter();
  if(!res){
    cout << "fault" << endl;
    return 1;
  }

  vector<int>::iterator it = prices.begin();
  while( it != prices.end() )
  {
    totalAmount(*it);
    ++it;
  }

  return 0;
}

