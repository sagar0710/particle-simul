#include<fstream>
#include<iostream>
#include<math.h>
#include<GL/glut.h>
#include<vector>
#include "./tokenizer.hpp"
#include "./sim_bodies.hpp"
#include "./sim_bodies_generator.hpp"

#define X_WIDTH 780
#define Y_HEIGHT 420
#define EXEMPT_COUNT 5

std::vector<std::string> tokens;
std::vector<sim_body> sim_objs;
config global_config;

void init(void){ 
    // making background color black as first  
    // 3 arguments all are 0.0 
    glClearColor(0.0, 0.0, 0.0, 1.0); 
      
    // making picture color green (in RGB mode), as middle argument is 1.0 
    glColor3f(0.0, 1.0, 0.0); 
      
    // breadth of picture boundary is 1 pixel 
    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
      
    // setting window dimension in X- and Y- direction 
    gluOrtho2D(-X_WIDTH, X_WIDTH, -Y_HEIGHT, Y_HEIGHT); 
}

void draw_scene(void){

    Sphere *stemp;
    Point *ptemp;

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

     glBegin(GL_LINES);
        glVertex2f(-X_WIDTH, 0);
        glVertex2f(X_WIDTH, 0);
        glVertex2f(0,-Y_HEIGHT);
        glVertex2f(0,Y_HEIGHT);
    glEnd();
    float d;
    for(auto& body:sim_objs){
       body.calc_force(sim_objs,global_config);
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
    for(auto& body1:sim_objs){

        for(auto& body2:sim_objs){
            if(body1.ID == body2.ID){
                continue;
            }
            float dx = body2.xc-body1.xc;
            float dy = body2.yc-body1.yc;
            d = sqrt(dx*dx+dy*dy);
            if(d<=body1.r+body2.r){
                if(body1.exempt && body2.exempt){
                    body1.count = (body1.count+1)%EXEMPT_COUNT;
                    body2.count = (body2.count+1)%EXEMPT_COUNT;
                    if(!body1.count)body1.exempt=false;
                    if(!body2.count)body2.exempt=false;
                    continue;
                }
                float phi;
                float theta1,theta2;
                float v1x,v1y,v2x,v2y;
                float v1 = sqrt(body1.vx*body1.vx+body1.vy*body1.vy);
                float v2 = sqrt(body2.vx*body2.vx+body2.vy*body2.vy);
                float term1;
                if(dx == 0){
                    phi = M_PI_2;
                }else{
                    phi = atan(dy/dx);
                }

                theta1 = acos(body1.vx/v1);
                theta2 = acos(body2.vx/v2);
                term1 = (body1.vx*cos(theta1-phi)*(body1.mass-body2.mass)+2*body2.mass*v2*cos(theta2-phi))/(body1.mass+body2.mass);
                v1x = term1*cos(phi)+v1*sin(theta1-phi)*cos(phi+M_PI_2);
                v1y = term1*sin(phi)+v1*sin(theta1-phi)*sin(phi+M_PI_2);

                term1 = (body2.vx*cos(theta2-phi)*(body2.mass-body1.mass)+2*body1.mass*v1*cos(theta1-phi))/(body1.mass+body2.mass);
                v2x = term1*cos(phi)+v2*sin(theta2-phi)*cos(phi+M_PI_2);
                v2y = term1*sin(phi)+v2*sin(theta2-phi)*sin(phi+M_PI_2);

                body1.vx = v1x;
                body1.vy = v1y;
                body2.vx = v2x;
                body2.vy = v2y;
            
                body1.exempt = true;
                body2.exempt = true;
            }


        }

    }
    
    
    for(auto& body:sim_objs){
        if(body.type==SPHERE){
            stemp = static_cast<Sphere*>(&body);
            stemp->draw();
        }else{
            ptemp = static_cast<Point*>(&body);
            ptemp->draw();
        }
    }
    glFlush(); 
    glutSwapBuffers();
    glutPostRedisplay();
} 

bool file_readable(std::string file){
    std::ifstream test(file);
    bool ret = test.good();
    test.close();
    return ret;
}

int main(int argc, char** argv){ 

    if(argc != 2){

        std::cerr<<"Invalid Number of arguments, Expected 1 got "<<argc-1<<std::endl;
        std::cerr<<"Usage : sim <filename>"<<std::endl;
        exit(1);
    }

    std::string file(argv[1]);
    
    if(!file_readable(file)){
        std::cerr<<"Sorry Cannot Open or read File "<<file<<" Please check the file permissions"<<std::endl;
        exit(1);
    }

    get_word_tokens(file,tokens);
    global_config = generate_config(tokens);
    generate_sim_bodies(tokens,sim_objs);

    //! DONE TILL DISPLAY PHYSICS PART IS REMAINING

    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(1366, 768); 
    glutInitWindowPosition(0, 0); 
      
    // Giving name to window 
    glutCreateWindow("Simulator"); 
    init(); 
      
    glutDisplayFunc(draw_scene); 
    glutMainLoop(); 

    return 0;
} 

