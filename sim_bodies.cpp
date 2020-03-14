#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include<set>
#include "./sim_bodies.hpp"

int sim_body::num = 1;

#define SIGN(x) ((x)/abs(x))
#define ERR_MARGIN 0.001
#define G_CONST 6.67e-11
#define E_CONST 8.99e9
std::set<std::set<int>> exemptions;
void add_exemption(const sim_body& b1,const sim_body& b2){
    std::set<int> l = {b1.ID,b2.ID};
    exemptions.insert(l);
}

void remove_exemption(const sim_body& b1,const sim_body& b2){
    std::set<int> l = {b1.ID,b2.ID};
    exemptions.erase(l);
}

bool is_exempted(const sim_body& b1,const sim_body& b2){
    std::set<int> l = {b1.ID,b2.ID};
    return exemptions.count(l) == 1;
}


int sign(float val){
    if(val == 0)return 1;
    else return val/abs(val);
}


void sim_body::calc_force(const std::vector<sim_body>& objs,const config& global){

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
         
            continue;
         
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
            ax += sign(dx)*f*cos(theta)/(this->charge*this->mass);
            ay += sign(dy)*f*sin(theta)/(this->charge*this->mass);

        }
    }
}

void Sphere::update(const std::vector<sim_body>&objs,const config& global){

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

void Point::update(const std::vector<sim_body>&objs,const config& global){
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

