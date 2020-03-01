#include<vector>
#include<iostream>
#include<string>
#include "./sim_bodies.hpp"

int main(){

    std::vector<std::string> v1 = {"SET","g","SET","G","SET","em","ADD","TEST"};
    std::vector<std::string> v2 = {"SET","g","SET","em","ADD","TEST"};
    std::vector<std::string> v3 = {"ADD","TEST"};
    std::vector<std::string> v4 = {"SET","C"};

    config c1 = generate_config(v1);
    config c2 = generate_config(v2);
    config c3 = generate_config(v3);
    
    if((c1.g !=0 && c1.G != 0 && c1.em != 0)){
        std::cout<<"TEST 1 PASSED"<<std::endl;
    }else{
        std::cout<<"TEST 1 FAILING"<<std::endl;
    }
    if((c2.g != 0&& c2.G == 0 && c2.em != 0)){
        std::cout<<"TEST 2 PASSED"<<std::endl;
    }else{
        std::cout<<"TEST 2 FAILING"<<std::endl;
    }

    if(c3.g == 0 && c3.G == 0 && c3.em ==0){
        std::cout<<"TEST 3 PASSED"<<std::endl;
    }else{
        std::cout<<"TEST 3 FAILING"<<std::endl;
    }
    std::cout<<"Program should exit..."<<std::endl;
    config c4 = generate_config(v4);
    std::cout<<"TEST 4 FAILING"<<std::endl;

}