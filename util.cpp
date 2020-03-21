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