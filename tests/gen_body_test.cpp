#include<iostream>
#include<vector>
#include<string>
#include "./sim_bodies_generator.hpp"

int main(){

    std::vector<std::string> tok = {"ADD","MBALL","2","3","0","5","8","9","2","5","ENDBODY",\
                                    "ADD","QBALL","2","3","0","5","8","9","2","5","ENDBODY", \
                                    "ADD","MQBALL","2","3","0","5","8","9","2","3","5","TRACE","ENDBODY", \
                                    "ADD","MQPT","2","3","0","5","8","9","5","3","ENDBODY", \
                                    "ADD","MPT","2","3","0","5","8","9","5","TRACE","ENDBODY" \
                                    };

    std::vector<sim_body> vec;

    generate_sim_bodies(tok,vec);
    int i = 1;
    for(auto b : vec){
        std::cout<<"Start : "<<i++<<std::endl;
        std::cout<<"x : "<<b.xc<<" yc : "<<b.yc<<" z : "<<b.zc<<std::endl;
        std::cout<<"vx : "<<b.vx<<" vy : "<<b.vy<<" vz : "<<b.vz<<std::endl;
        std::cout<<"r : "<<b.r<<" mass : "<<b.mass<<" charge : "<<b.charge<<std::endl;
        std::cout<<"Type : "<<b.type<<" TRACE : "<<b.trace<<std::endl;
        std::cout<<"End\n"<<std::endl;
    }
    return 0;
}