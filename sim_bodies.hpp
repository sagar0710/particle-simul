#include<string>
#include<vector>
#include<set>
#include "./util.hpp"

#define FINENESS 0.001

#ifndef SIM_BODIES
#define SIM_BODIES

enum body_type{
    SPHERE,
    POINT,
    STAT_RECT
};
struct config{
    bool g = false;
    bool G = false;
    bool em = false;
    float time_slice = 0;
    int delay =0;
    int counter =0;
};

class Sim_Body{

    public:
    int ID;
    static int num;
    std::vector<std::pair<float,float>> trace_history = {}; //* NOTE : Will need to be changed if 3D is implemented
    float xc=0,yc=0,zc=0;
    float vx=0,vy=0,vz=0;
    float ax=0,ay=0,az=0;
    float r=0;
    float mass=0,charge =0;
    float rot;
    float width,height;
    float xtl,ytl,xtr,ytr,xbl,ybl,xbr,ybr;
    bool trace = false;
    bool exempt =false;
    int count =0;
    body_type type;

    void draw(){};
    virtual void calc_force(const std::vector<Sim_Body>& bodies,const config& gloabl);
    void update(const std::vector<Sim_Body>&,const config&){};
};

class Sphere:public Sim_Body{
    
    public:
    Sphere(){
        ID = num;
        ++num;
    }
    void draw();
    void update(const std::vector<Sim_Body>&,const config&);

};

class Point:public Sim_Body{

    public:
    Point(){
        ID = num;
        ++num;
    }
    void draw();
    void update(const std::vector<Sim_Body>&,const config&);
};

//* Will need to change if 3D
class Static_Rect:public Sim_Body{

    public:
    Static_Rect(float x,float y,float h,float w,float rot){
        ID = num;
        ++num;
        xc = x;
        yc =y;
        height = h;
        width = w;
        this->rot = rot;
        set_draw_coordinates();
    }
    void set_draw_coordinates();
    void draw();
    void update(const std::vector<Sim_Body>&,const config&);
};

void add_exemption(const Sim_Body& b1,const Sim_Body& b2);
void remove_exemption(const Sim_Body& b1,const Sim_Body& b2);
bool is_exempted(const Sim_Body& b1,const Sim_Body& b2);
#endif