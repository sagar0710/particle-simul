#ifndef UTIL
#define UTIL

#include <utility>
#include "./sim_body_def.hpp"

std::pair<float,float> get_point_in_original(float xc,float yc,float rot,float other_x,float other_y);
bool check_stat_rect_collision(const Sim_Body& body,const Sim_Body& rect);

#endif