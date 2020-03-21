#include<fstream>
#include<iostream>
#include<set>
#include<math.h>
#include<GL/glut.h>
#include<vector>
#include "./tokenizer.hpp"
#include "./sim_bodies.hpp"
#include "./sim_bodies_generator.hpp"
#include "./physics.hpp"
#define X_WIDTH 780
#define Y_HEIGHT 420

std::vector<std::string> tokens;
std::vector<Sim_Body> sim_objs;
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
    Static_Rect *srttemp;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

     glBegin(GL_LINES);
        glVertex2f(-X_WIDTH, 0);
        glVertex2f(X_WIDTH, 0);
        glVertex2f(0,-Y_HEIGHT);
        glVertex2f(0,Y_HEIGHT);
    glEnd();
    
    if(global_config.delay == 0 || global_config.counter == 0){
        collision(sim_objs);
        calc_forces(sim_objs,global_config);
        update(sim_objs,global_config);
    }
    if(global_config.delay !=0){
        global_config.counter = (global_config.counter+1)%global_config.delay;
    }    
    
    for(auto& body:sim_objs){
        if(body.type==SPHERE){
            stemp = static_cast<Sphere*>(&body);
            stemp->draw();
        }else if(body.type == POINT){
            ptemp = static_cast<Point*>(&body);
            ptemp->draw();
        }else if(body.type == STAT_RECT){
            srttemp = static_cast<Static_Rect*>(&body);
            srttemp->draw();
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

