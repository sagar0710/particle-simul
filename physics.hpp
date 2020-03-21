#include<set>
#include<math.h>
#include<vector>
#include "./sim_bodies.hpp"
#include "./sim_bodies_generator.hpp"

#define EXEMPT_COUNT 5
#define ERR_MARGINE 0.001
#define PRECISION 1000
#define G_CONST 6.67e-11

void collision(std::vector<Sim_Body>&);
void calc_forces(std::vector<Sim_Body>&,config&);
void update(std::vector<Sim_Body>&,config&);