#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include<set>
#include "./sim_bodies.hpp"


int Sim_Body::num = 1;

#define SIGN(x) ((x)/abs(x))
#define ERR_MARGIN 0.001
#define G_CONST 6.67e-11
#define E_CONST 8.99e9

#define APPR(val) ((int)(val)*1000)/(float)1000;

std::set<std::set<int>> exemptions;



void add_exemption(const Sim_Body& b1,const Sim_Body& b2){
    std::set<int> l = {b1.ID,b2.ID};
    exemptions.insert(l);
}

void remove_exemption(const Sim_Body& b1,const Sim_Body& b2){
    std::set<int> l = {b1.ID,b2.ID};
    exemptions.erase(l);
}

bool is_exempted(const Sim_Body& b1,const Sim_Body& b2){
    std::set<int> l = {b1.ID,b2.ID};
    return exemptions.count(l) == 1;
}


int sign(float val){
    if(val == 0)return 1;
    else return val/abs(val);
}


void Sim_Body::calc_force(const std::vector<Sim_Body>& objs,const config& global){

    //* NOTE : Will need to be changed if 3D is implemented
    this->ax =0;
    this->ay =0;
    this->az =0;
    if(global.g){
        this->ay -=9.81;
    }
    for(auto obj:objs){
        float dx,dy;
        dx = obj.xc-this->xc;
        dy = obj.yc-this->yc;
        float r = sqrt(dx*dx+dy*dy);

        if(obj.ID == this->ID){
            continue;
        }
        if(is_exempted(*this,obj)){
            if(r<=this->r+obj.r){
                continue;
            }else{
                remove_exemption(*this,obj);
            }
        }
        if(global.G){

            float f = G_CONST*this->mass*obj.mass/(r*r);

            float theta = abs(atan(dy/dx));
            if(isnan(theta))theta = 0;
            ax += sign(dx)*f*cos(theta)/this->mass;
            ay += sign(dy)*f*sin(theta)/this->mass;

        }

        if(global.em){

            float dx,dy;
            dx = obj.xc-this->xc;
            dy = obj.yc-this->yc;
            float r = sqrt(dx*dx+dy*dy);
            float f = E_CONST*this->charge*obj.charge/(r*r);

            float theta = abs(atan(dy/dx));
            if(isnan(theta))theta = 0;
            ax += APPR(sign(dx)*f*cos(theta)/(this->charge*this->mass));
            ay += APPR(sign(dy)*f*sin(theta)/(this->charge*this->mass));

        }
    }
}

void Sphere::update(const std::vector<Sim_Body>&objs,const config& global){

    float dt = global.time_slice;
    //* NOTE : Will need to be changed if 3D is implemented
    if(this->trace)
        trace_history.push_back(std::pair<float,float>(xc,yc));
    
    
    xc += vx*dt + 0.5*ax*(dt*dt);
    yc += vy*dt + 0.5*ay*(dt*dt);
    zc += vz*dt + 0.5*az*(dt*dt); 

    vx += ax*dt;
    vy += ay*dt;
    vz += az*dt;


}

void Sphere::draw(){

    //* NOTE : Will need to be changed if 3D is implemented
    if(trace){
        glBegin(GL_POINTS); 
        for(auto p : trace_history){
            auto [x,y] = p;
            glVertex2f(x, y); 
        }
        glEnd(); 
    }

    glBegin(GL_POINTS); 
    float x, y, i; 
    for ( i = 0; i < (2 * M_PI); i += FINENESS){ 
        x = xc+r * cos(i); 
        y = yc+r * sin(i); 
        glVertex2f(x, y); 
    } 
    glEnd(); 

}

void Point::update(const std::vector<Sim_Body>&objs,const config& global){
    //* NOTE : Will need to be changed if 3D is implemented
    if(this->trace)
        trace_history.push_back(std::pair<float,float>(xc,yc));

    xc += vx*global.time_slice + 0.5*ax*(global.time_slice*global.time_slice);
    yc += vy*global.time_slice + 0.5*ay*(global.time_slice*global.time_slice);
    zc += vz*global.time_slice + 0.5*az*(global.time_slice*global.time_slice);

    vx += ax*global.time_slice;
    vy += ay*global.time_slice;
    vz += az*global.time_slice;    


}

void Point::draw(){

    //* NOTE : Will need to be changed if 3D is implemented
    if(trace){
        glBegin(GL_POINTS); 
        for(auto p : trace_history){
            auto [x,y] = p;
            glVertex2f(x, y); 
        }
        glEnd(); 
    }

    glBegin(GL_POINT); 
    glVertex2f(xc,yc);
    glEnd(); 

}

/** 
 * Helper funtion, so we'll have to calculate co-ordinates only once
*/
void Static_Rect::set_draw_coordinates(){
    //* Temporary
    float tx,ty;
    std::pair<float,float> tp;
    /** 
     * Here we calculate the tx and ty assuming rectagle is at (0,0) in unrotated frame
     * Then we use fun get_point_in_original() to get the co-ordinates in actual frame.
    */

    //* Top Right
    tx = width/2;
    ty = height/2;
    tp = get_point_in_original(xc,yc,rot,tx,ty);
    xtr = tp.first;
    ytr = tp.second;

    //* Top Left
    tx = -width/2;
    ty = height/2;
    tp = get_point_in_original(xc,yc,rot,tx,ty);
    xtl = tp.first;
    ytl = tp.second;

    //* Bottem Right
    tx = width/2;
    ty = -height/2;
    tp = get_point_in_original(xc,yc,rot,tx,ty);
    xbr = tp.first;
    ybr = tp.second;
    
    //* Bottem Left
    tx = -width/2;
    ty = -height/2;
    tp = get_point_in_original(xc,yc,rot,tx,ty);
    xbl = tp.first;
    ybl = tp.second;
}

void Static_Rect::draw(){

    //* As static, No trace
    glBegin(GL_POLYGON);
    glVertex2f(xtl,ytl);
    glVertex2f(xtr,ytr);
    glVertex2f(xbr,ybr);
    glVertex2f(xbl,ybl);
    glEnd();   

}

void Static_Rect::update(const std::vector<Sim_Body>&objs,const config& global){
    //* Nothing Here
}