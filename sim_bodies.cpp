#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include "./sim_bodies.hpp"

int sim_body::num = 1;

#define SIGN(x) ((x)/abs(x))
#define ERR_MARGIN 0.1

void sim_body::calc_force(const std::vector<sim_body>& objs,const config& global){

    //* NOTE : Will need to be changed if 3D is implemented
    this->ax = this->ay = this->az =0;
    if(global.g){
        this->ay -=9.81;
    }
    for(auto obj:objs){
        if(obj.ID == this->ID){
            continue;
        }
        if(global.G){
            if(abs(this->xc-obj.xc)>ERR_MARGIN)
                this->ax += SIGN(obj.xc-this->xc)*((6.674e-11 * obj.mass)/((this->xc-obj.xc)*(this->xc-obj.xc)));
            if(abs(this->yc-obj.yc)>ERR_MARGIN)
                this->ay += SIGN(obj.yc-this->yc)*((6.674e-11 * obj.mass)/((this->yc-obj.yc)*(this->yc-obj.yc)));
            if(abs(this->zc-obj.zc)>ERR_MARGIN)
                this->az += SIGN(obj.zc-this->zc)*((6.674e-11 * obj.mass)/((this->zc-obj.zc)*(this->zc-obj.zc)));
        }

        if(global.em){
            if(abs(this->xc-obj.xc)>ERR_MARGIN)
                this->ax += (8.99e9 * obj.charge*this->charge)/((this->xc-obj.xc)*(this->xc-obj.xc)*this->mass);
            if(abs(this->yc-obj.yc)>ERR_MARGIN)
                this->ay += (8.99e9 * obj.charge*this->charge)/((this->yc-obj.yc)*(this->yc-obj.yc)*this->mass);
            if(abs(this->zc-obj.zc)>ERR_MARGIN)
                this->az += (8.99e9 * obj.charge*this->charge)/((this->zc-obj.zc)*(this->zc-obj.zc)*this->mass);
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

