#include<iostream>
#include<chrono>
#include "physics.hpp"
#define SQR(x) ((x)*(x))

inline uint64_t get_time(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void collision(std::vector<Sim_Body>& sim_objs,const config& global){
    for(auto& body1:sim_objs){   
        if(body1.type == STAT_RECT){
            continue;
        }
        for(auto& body2:sim_objs){
            float dx = body2.xc-body1.xc;
            float dy = body2.yc-body1.yc;
            float d = sqrt((dx*dx)+(dy*dy));
            if(body1.ID == body2.ID){
                continue;
            }
            if(body2.type == STAT_RECT){
                if(check_stat_rect_collision(body1,body2)){
                    if(is_exempted(body1,body2))continue;
                    handle_static_collision(body1,body2,global);
                    continue;
                }else if(is_exempted(body1,body2)){
                    remove_exemption(body1,body2);
                    continue;
                }
            }
            if(is_exempted(body1,body2)){
                if(d<=body1.r+body2.r){
                    continue;
                }
            }

            if(d<=body1.r+body2.r){
                add_exemption(body1,body2);
                float phi;
                float theta1,theta2;
                float v1x,v1y,v2x,v2y;
                float v1 = sqrt(body1.vx*body1.vx+body1.vy*body1.vy);
                float v2 = sqrt(body2.vx*body2.vx+body2.vy*body2.vy);
                float term1;
                if(dx == 0){
                    phi = M_PI_2;
                }else if(abs(dy)<=ERR_MARGINE){
                    phi =0;
                }else{
                    phi = atan(dy/dx);
                }
                theta1 = acos(body1.vx/(v1+ERR_MARGINE));
                theta2 = acos(body2.vx/(v2+ERR_MARGINE));
                if(abs(v1)<ERR_MARGINE)theta1 = 0;
                if(abs(v2)<ERR_MARGINE)theta2 = 0;
                

                term1 = (body1.vx*cos(theta1-phi)*(body1.mass-body2.mass)+2*body2.mass*v2*cos(theta2-phi))/(body1.mass+body2.mass);
                v1x = term1*cos(phi)+v1*sin(theta1-phi)*cos(phi+M_PI_2);
                v1y = term1*sin(phi)+v1*sin(theta1-phi)*sin(phi+M_PI_2);

                term1 = (body2.vx*cos(theta2-phi)*(body2.mass-body1.mass)+2*body1.mass*v1*cos(theta1-phi))/(body1.mass+body2.mass);
                v2x = term1*cos(phi)+v2*sin(theta2-phi)*cos(phi+M_PI_2);
                v2y = term1*sin(phi)+v2*sin(theta2-phi)*sin(phi+M_PI_2);

                body1.vx = ((int)v1x*PRECISION)/(float)PRECISION;
                body1.vy = ((int)v1y*PRECISION)/(float)PRECISION;
                if(body2.type != STAT_RECT){
                    body2.vx = ((int)v2x*PRECISION)/(float)PRECISION;
                    body2.vy = ((int)v2y*PRECISION)/(float)PRECISION;
                }
                
            }
        }
    }
}

void calc_forces(std::vector<Sim_Body>& sim_objs,config& global_config){
    for(auto& body:sim_objs){
        if(body.type == STAT_RECT){
            continue;
        }
        body.calc_force(sim_objs,global_config);
    }
}

void update(std::vector<Sim_Body>& sim_objs,config& global_config){
    Sphere *stemp;
    Point *ptemp;

    static uint64_t time = get_time();
    if(global_config.time_slice == 0){
        uint64_t t = get_time();
        global_config.time_slice = ((float)(t - time+1))/1000;
        time = t;
    }
    for(auto& body:sim_objs){
        if(body.type==SPHERE){
            stemp = static_cast<Sphere*>(&body);
            stemp->update(sim_objs,global_config);
        }else{
            ptemp = static_cast<Point*>(&body);
            ptemp->update(sim_objs,global_config);
        }
    }
}


void handle_static_collision(Sim_Body& body,Sim_Body& stat,const config& global){

    //* Check out the video by Physics Galaxy on Oblique collision of ball on flat surface
    
    //* Assuming that the rectangle is horizontal,let theta be inital angle with rectangle
    //* phi be angle after collision
    std::pair tp = get_point_in_shifted_rotated(0,0,stat.rot,body.vx,body.vy);

    float theta = M_PI_2 - atan(tp.second/tp.first);
    float phi = M_PI_2 + atan((1/global.e)*tan(theta));

    float u = sqrt(SQR(body.vx)+SQR(body.vy));
    float v = u*sqrt(SQR(sin(theta))+SQR(global.e*cos(theta)));
    body.vx = ((int)(v*cos(phi)*1000))/(float)1000;
    body.vy = ((int)(v*sin(phi)*1000))/(float)1000;

}