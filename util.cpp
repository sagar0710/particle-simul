#include "util.hpp"
#include <math.h>
/**
 * This is a function to convert co-ordinates of points in new(other) co-ordinate frame 
 * to original [centre at  (0,0) , no rotation] co-ordinates.
 * @param xc X-centre of new co-ordinate frame in original co-ordinates
 * @param yc Y-centre of new co-ordinate frame in original co-ordinates
 * @param rot_rad rotation of other frame in Radians
 * @param other_x X-coordinate of point in other frame
 * @param other_y Y-coordinate of point in other frame
 * 
 * @returns std::pair<float,float> co-ordinates of the point in original frame
*/

std::pair<float,float> get_point_in_original(float xc,float yc,float rot_rad,float other_x,float other_y){

    /** 
     * First we apply inverse rotation matrix : | cos  sin | to co-ordinates to get non-rotated co-ordinates
     *                                          | -sin cos |
    */ 
    float _x = cos(rot_rad)*other_x+sin(rot_rad)*other_y;
    float _y = -sin(rot_rad)*other_x+cos(rot_rad)*other_y;

    /**
     * Now we have got the 'un-rotated' co-ordiantes we use inverse of shift of origin to get 
     * The co-ordinates in original frame
    */
    _x = _x+xc;
    _y = _y+yc;

    return std::pair(_x,_y);
}


/**
 * This is a function to convert co-ordinates of points in original [centre at  (0,0), no rotation] frame 
 * to shifted,rotated (other) co-ordinates.
 * @param xc X-centre of other frame in original co-ordinates
 * @param yc Y-centre of other frame in original co-ordinates
 * @param rot_rad rotation of other frame in Radians
 * @param x X-coordinate of point original frame
 * @param y Y-coordinate of point original frame
 * 
 * @returns std::pair<float,float> co-ordinates of the point in shifted and rotated frame
*/

std::pair<float,float> get_point_in_shifted_rotated(float xc,float yc,float rot_rad,float x,float y){
    float _x,_y;

    /**
     *First We apply shift of origin to get co-ordinates in shifted frame
    */
    _x = x-xc;
    _y = y-yc;

     /** 
     * Then we apply rotation matrix : | cos -sin | to co-ordinates to get rotated co-ordinates
     *                                 | sin  cos |
     * Used intermidiate tx and ty as both depend on both _x & _y
    */ 

    float tx = cos(rot_rad)*_x-sin(rot_rad)*_y;
    float ty = sin(rot_rad)*_x+cos(rot_rad)*_y;

    _x = tx;
    _y = ty;
    
    return std::pair(_x,_y);
}

bool check_stat_rect_collision(const Sim_Body& body,const Sim_Body& rect){

    std::pair tp = get_point_in_shifted_rotated(rect.xc,rect.yc,rect.rot,body.xc,body.yc);
    float _x = tp.first;
    float _y = tp.second;
    float coll_dist_x = body.r +rect.width/2;
    float coll_dist_y = body.r +rect.height/2;

    //* NOTE : This collison detection may be possible to implement in
    //*        Single condition, in fact the second if cluase is possibaly 
    //*        Redundent.


    //* First check if the body (shpere) is between y endpts of rect
    if(_y <coll_dist_y && _y > -coll_dist_y){
        //* check if body is between x endpts of rect
         return (_x< coll_dist_x && _x > -coll_dist_x);
    }

    //* check if the body (shpere) is between x endpts of rect
    if(_x < coll_dist_x && _x > -coll_dist_x){
        //* check if body is between y endpts of rect
        return (_y< coll_dist_y && _y > -coll_dist_y);
    }

    return false;

}