a.out : ./sim_bodies.o ./sim_bodies_generator.o gen_body_test.o 
	g++  -o a.out ./sim_bodies.o ./sim_bodies_generator.o gen_body_test.o 

gen_body_test.o : ./sim_bodies_generator.hpp 
	g++ -c  gen_body_test.cpp

./sim_bodies_generator.o : ./sim_bodies_generator.hpp ./sim_bodies.hpp 
	g++ -c  ./sim_bodies_generator.cpp

./sim_bodies.o : ./sim_bodies.hpp 
	g++ -c  ./sim_bodies.cpp


clean : 
	rm ./*.o
