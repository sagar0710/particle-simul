#include<string>
#include<vector>
#include<set>

#define FINENESS 0.001

#ifndef SIM_BODIES
#define SIM_BODIES

enum body_type{
    SPHERE,
    POINT
};
struct config{
    bool g = false;
    bool G = false;
    bool em = false;
    float time_slice = 0.001;
};

class sim_body{

    public:
    int ID;
    static int num;
    std::vector<std::pair<float,float>> trace_history = {}; //* NOTE : Will need to be changed if 3D is implemented
    float xc=0,yc=0,zc=0;
    float vx=0,vy=0,vz=0;
    float ax=0,ay=0,az=0;
    float r=0;
    float mass=0,charge =0;
    bool trace = false;
    bool exempt =false;
    int count =0;
    body_type type;

    void draw(){};
    virtual void calc_force(const std::vector<sim_body>& bodies,const config& gloabl);
    void update(const std::vector<sim_body>&,const config&){};
};

class Sphere:public sim_body{
    
    public:
    Sphere(){
        ID = num;
        ++num;
    }
    void draw();
    void update(const std::vector<sim_body>&,const config&);

};

class Point:public sim_body{

    public:
    Point(){
        ID = num;
        ++num;
    }
    void draw();
    void update(const std::vector<sim_body>&,const config&);
};

void add_exemption(const sim_body& b1,const sim_body& b2);
void remove_exemption(const sim_body& b1,const sim_body& b2);
bool is_exempted(const sim_body& b1,const sim_body& b2);
#endif