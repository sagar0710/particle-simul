#include "./sim_bodies.hpp"


#ifndef SIM_BODIES_GEN
#define SIM_BODIES_GEN


config generate_config(const std::vector<std::string>& tokens);
void generate_sim_bodies(const std::vector<std::string>& tokens,std::vector<sim_body>& bodies);

void read_and_set_centre(std::vector<std::string>::const_iterator& itr,sim_body& s);

void add_mball(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies);
void add_qball(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies);
void add_mqball(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies);

void add_mpt(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies);
void add_qpt(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies);
void add_mqpt(std::vector<std::string>::const_iterator& itr,std::vector<sim_body>& bodies);

#endif