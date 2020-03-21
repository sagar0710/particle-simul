#include "physics.hpp"
#define SQR(x) ((x)*(x))
#define COEFF_REST 1

void collision(std::vector<Sim_Body>& sim_objs){
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
                    handle_static_collision(body1,body2);
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
                float mi =sqrt(SQR(body1.vx*body1.mass+body2.vx*body2.mass)+SQR(body1.vx*body1.mass+body2.vx*body2.mass));
                float ma =sqrt(SQR(v1x*body1.mass+v2x*body2.mass)+SQR(v1y*body1.mass+v2y*body2.mass));

                if(mi != ma){
                    float here =0;
                }

                body1.vx = ((int)v1x*PRECISION)/(float)PRECISION;
                body1.vy = ((int)v1y*PRECISION)/(float)PRECISION;
                body2.vx = ((int)v2x*PRECISION)/(float)PRECISION;
                body2.vy = ((int)v2y*PRECISION)/(float)PRECISION;
            }
        }
    }
}

void calc_forces(std::vector<Sim_Body>& sim_objs,config& global_config){
    for(auto& body:sim_objs){
        body.calc_force(sim_objs,global_config);
    }
}

void update(std::vector<Sim_Body>& sim_objs,config& global_config){
    Sphere *stemp;
    Point *ptemp;
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


void handle_static_collision(Sim_Body& body,Sim_Body& stat){

    //* Check out the video by Physics Galaxy on Oblique collision of ball on flat surface
    float v = sqrt(SQR(body.vx)+SQR(body.vy));
    //* Adjusting for negation of anlge initially
    float ang = -stat.rot;
    //* Assuming that the rectangle is horizontal,let theta be inital angle with rectangle
    //* phi be angle after collision
    float theta = M_PI_2- (atan(abs(body.vy/body.vx)) - ang);
    float phi =M_PI_2 + atan( (1/COEFF_REST)*tan(theta) ) +ang;
    body.vx = ((int)(v*cos(phi)*1000))/(float)1000;
    body.vy = ((int)(v*sin(phi)*1000))/(float)1000;

}