#include<iostream>
#include<set>
#include<math.h>
#include<vector>

std::set<std::set<int>> exemptions;

int main(){


    std::set<int> l = {1,2};
    std::set<int> k = {2,1};

    std::cout<<"Sets .. "<<(l==k);
   return 0; 
}