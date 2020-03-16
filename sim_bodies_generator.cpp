#include<cstring>
#include<vector>
#include<iostream>
#include "./sim_bodies_generator.hpp"

config generate_config(const std::vector<std::string>& tokens){
    config ret;
    std::string temp;
    for(auto itr = tokens.begin();itr != tokens.end();++itr){
        
        temp = *itr;
        if( strcmp(temp.c_str(),"SET") != 0 && strcmp(temp.c_str(),"set") != 0 ){
            break;
        }else{
            ++itr;
            temp = *itr;
            if(!strcmp(temp.c_str(),"g")){
                ret.G = false;
                ret.g = true;
            }else if(!strcmp(temp.c_str(),"G")){
                ret.g = false;
                ret.G = true;
            }else if(!strcmp(temp.c_str(),"em")){
                ret.em = true;
            }else if(!strcmp(temp.c_str(),"tslice")){
                ++itr;
                ret.time_slice = atof((*itr).c_str());
            }else if(!strcmp(temp.c_str(),"delay")){
                ++itr;
                ret.delay = atoi((*itr).c_str());
            }else{
                std::cerr<<"Expected \'g\' ,\'G\' ,\'em\' .\'tslice\' or \'delay\' after SET.. got : \'"<<temp<<"\'\nExiting...";
                exit(1);
            }
        }
    }
    return ret;
}
void generate_sim_bodies(const std::vector<std::string>& tokens,std::vector<sim_body>& bodies){

    auto itr = tokens.begin();
    while(itr != tokens.end()){
        if(strcmp((*itr).c_str(),"SET") == 0 || strcmp((*itr).c_str(),"set") == 0){
            ++itr; // Goes to the SET arg
            if(!strcmp((*itr).c_str(),"tslice") || !strcmp((*itr).c_str(),"delay")){
                ++itr;
            }
            ++itr; // Goes to next instruction token
        }else{
            break;
        }
        
    }

    for(;itr!=tokens.end();++itr){
        if(strcmp((*itr).c_str(),"ADD") != 0 && strcmp((*itr).c_str(),"add") != 0){
            std::cerr<<"Error : Invalid Token Found : "<<*itr<<"\nExiting..."<<std::endl;
            exit(1);
        }
        ++itr;
        if(strcmp((*itr).c_str(),"MBALL") == 0 || strcmp((*itr).c_str(),"mball") == 0){

            add_mball(itr,bodies);

        }else if(strcmp((*itr).c_str(),"QBALL") == 0 || strcmp((*itr).c_str(),"qball") == 0){
            add_qball(itr,bodies);
        }else if(strcmp((*itr).c_str(),"MQBALL") == 0 || strcmp((*itr).c_str(),"mqball") == 0){
            add_mqball(itr,bodies);
        }else if(strcmp((*itr).c_str(),"MPT") == 0 || strcmp((*itr).c_str(),"mpt") == 0){
            add_mpt(itr,bodies);
        }else if(strcmp((*itr).c_str(),"QPT") == 0 || strcmp((*itr).c_str(),"qpt") == 0){
            add_mpt(itr,bodies);
        }else if(strcmp((*itr).c_str(),"MQPT") == 0 || strcmp((*itr).c_str(),"mqpt") == 0){
            add_mqpt(itr,bodies);
        }
        

    }
}

void read_and_set_centre(std::vector<std::string>::const_iterator& itr,sim_body& s){
    ++itr;
    s.xc = atof((*itr).c_str());
    ++itr;
    s.yc = atof((*itr).c_str());
    ++itr;
    s.zc = atof((*itr).c_str());
    ++itr;
    s.vx = atof((*itr).c_str());
    ++itr;
    s.vy = atof((*itr).c_str());
    ++itr;
    s.vz = atof((*itr).c_str());
}

void add_mball(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies){

    Sphere s;
    s.type = SPHERE;
    read_and_set_centre(itr,s);
    ++itr;
    s.r = atof((*itr).c_str());
    ++itr;
    s.mass = atof((*itr).c_str());
    ++itr;
    if(strcmp((*itr).c_str(),"TRACE") == 0 || strcmp((*itr).c_str(),"trace") == 0){
        s.trace = true;
        ++itr;
    }
    if(strcmp((*itr).c_str(),"ENDBODY") != 0 && strcmp((*itr).c_str(),"endbody") != 0){
        std::cerr<<"Error : Invalid Token Found : MBALL"<<*itr<<"\nExiting..."<<std::endl;
        exit(1);
    }
    bodies.push_back(s);
    return;
}

void add_qball(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies){

    Sphere s;
    s.type = SPHERE;
    read_and_set_centre(itr,s);
    ++itr;
    s.r = atof((*itr).c_str());
    ++itr;
    s.charge = atof((*itr).c_str());
    ++itr;
    if(strcmp((*itr).c_str(),"TRACE") == 0 || strcmp((*itr).c_str(),"trace") == 0){
        s.trace = true;
        ++itr;
    }
    if(strcmp((*itr).c_str(),"ENDBODY") != 0 && strcmp((*itr).c_str(),"endbody") != 0){
        std::cerr<<"Error : Invalid Token Found : QBALL"<<*itr<<"\nExiting..."<<std::endl;
        exit(1);
    }
    bodies.push_back(s);
    return;

}

void add_mqball(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies){

    Sphere s;
    s.type = SPHERE;
    read_and_set_centre(itr,s);
    ++itr;
    s.r = atof((*itr).c_str());
    ++itr;
    s.mass = atof((*itr).c_str());
    ++itr;
    s.charge = atof((*itr).c_str());
    ++itr;
    if(strcmp((*itr).c_str(),"TRACE") == 0 || strcmp((*itr).c_str(),"trace") == 0){
        s.trace = true;
        ++itr;
    }
    if(strcmp((*itr).c_str(),"ENDBODY") != 0 && strcmp((*itr).c_str(),"endbody") != 0){
        std::cerr<<"Error : Invalid Token Found : MQBALL"<<*itr<<"\nExiting..."<<std::endl;
        exit(1);
    }
    bodies.push_back(s);
    return;

}

void add_mpt(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies){

    Point p;
    p.type = POINT;
    read_and_set_centre(itr,p);
    ++itr;
    p.mass = atof((*itr).c_str());
    ++itr;
    
    if(strcmp((*itr).c_str(),"TRACE") == 0 || strcmp((*itr).c_str(),"trace") == 0){
        p.trace = true;
        ++itr;
    }
    if(strcmp((*itr).c_str(),"ENDBODY") != 0 && strcmp((*itr).c_str(),"endbody") != 0){
        std::cerr<<"Error : Invalid Token Found : "<<*itr<<"\nExiting..."<<std::endl;
        exit(1);
    }
    bodies.push_back(p);
    return;

}

void add_qpt(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies){

    Point p;
    p.type = POINT;
    read_and_set_centre(itr,p);
    ++itr;
    p.mass = atof((*itr).c_str());
    ++itr;
    if(strcmp((*itr).c_str(),"TRACE") == 0 || strcmp((*itr).c_str(),"trace") == 0){
        p.trace = true;
        ++itr;
    }
    if(strcmp((*itr).c_str(),"ENDBODY") != 0 && strcmp((*itr).c_str(),"endbody") != 0){
        std::cerr<<"Error : Invalid Token Found : "<<*itr<<"\nExiting..."<<std::endl;
        exit(1);
    }
    bodies.push_back(p);
    return;

}

void add_mqpt(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies){

    Point p;
    p.type = POINT;
    read_and_set_centre(itr,p);
    ++itr;
    p.mass = atof((*itr).c_str());
    ++itr;
    p.charge = atof((*itr).c_str());
    ++itr;
    if(strcmp((*itr).c_str(),"TRACE") == 0 || strcmp((*itr).c_str(),"trace") == 0){
        p.trace = true;
        ++itr;
    }
    if(strcmp((*itr).c_str(),"ENDBODY") != 0 && strcmp((*itr).c_str(),"endbody") != 0){
        std::cerr<<"Error : Invalid Token Found : "<<*itr<<"\nExiting..."<<std::endl;
        exit(1);
    }
    bodies.push_back(p);
    return;

}