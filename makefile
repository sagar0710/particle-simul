simulator : ./physics.o ./sim_bodies.o ./sim_bodies_generator.o ./tokenizer.o ./util.o main.o 
	g++ ./physics.o ./sim_bodies.o ./sim_bodies_generator.o ./tokenizer.o ./util.o main.o -lGL -lGLU -lglut -std=c++17 -o simulator 
	rm ./*.o

main.o : ./physics.hpp ./sim_bodies.hpp ./sim_bodies_generator.hpp ./tokenizer.hpp 
	g++ -c main.cpp -lGL -lGLU -lglut -std=c++17

./tokenizer.o : ./tokenizer.hpp 
	g++ -c ./tokenizer.cpp -lGL -lGLU -lglut -std=c++17

./physics.o : ./physics.hpp ./sim_bodies.hpp ./sim_bodies_generator.hpp ./util.hpp 
	g++ -c ./physics.cpp -lGL -lGLU -lglut -std=c++17

./sim_bodies_generator.o : ./sim_bodies_generator.hpp ./sim_bodies.hpp 
	g++ -c ./sim_bodies_generator.cpp -lGL -lGLU -lglut -std=c++17

./sim_bodies.o : ./sim_bodies.hpp ./sim_body_def.hpp ./util.hpp 
	g++ -c ./sim_bodies.cpp -lGL -lGLU -lglut -std=c++17

./util.o : ./util.hpp ./sim_body_def.hpp 
	g++ -c ./util.cpp -lGL -lGLU -lglut -std=c++17


clean : 
	rm ./*.o
