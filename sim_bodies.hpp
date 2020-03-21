#include<string>
#include<vector>
#include<set>
#include "./sim_body_def.hpp"
#include "./util.hpp"

#define FINENESS 0.001

#ifndef SIM_BODIES
#define SIM_BODIES
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