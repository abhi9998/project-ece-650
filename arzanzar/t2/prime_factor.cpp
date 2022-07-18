#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

std::string prime_factor(unsigned x) {
  std::stringstream out;

  //input is 1 return 2^0
  if(x==1){
      out<<"2^0";
      return out.str();
  }

  //for storing prime and its power
  std::vector<int> base;
  std::vector<int> power;


  int temp = x;
  int count=0;
  
  //finding number of 2 which can divide x
  while(temp!=0){
      if(temp%2==0){
          temp=temp/2;
          count++;
      }else{
          break;
      }
  }

  if(count>0){
      base.push_back(2);
      power.push_back(count);
  }

  //iterating over all odd number. this reduces no of division check because except 2 all primes are odd.
  for(int i=3;i<=x;i=i+2){
      int divi = i;
      count=0;
      while(temp!=0){
          if(temp%divi==0){
              temp=temp/divi;
              count++;
          }else{
              break;
          }
      }
      if(count>0){
          base.push_back(i);
          power.push_back(count);
      }
  }

    //storing output in stream defined
  for(int i=0;i<base.size();i++){
      int val = base.at(i);
      int pow = power.at(i);

      // keepign power symbol if its more than 2
      if(pow>1){
        out<<val<<"^"<<pow;
      }else{
        out<<val;
      }
      //add multiply for every except last
      if(i!=base.size()-1){
          out<<" x ";
      }
  }      

  return out.str();
}


int main() {

  auto input = 9;
  auto output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 3^2


  input = 1;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 2^0


  input = 240;
  output = prime_factor(input);

  std::cout << "Prime factorization of " << input << " is " << output
            << std::endl;
  // expected output: 2^4 x 3 x 5
  return 0;
}
