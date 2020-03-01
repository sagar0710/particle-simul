a.out : ./sim_bodies.o ./sim_bodies_generator.o ./tokenizer.o main.o 
	g++ ./sim_bodies.o ./sim_bodies_generator.o ./tokenizer.o main.o -lGL -lGLU -lglut -lm -std=c++17 -g -o a.out 
	rm ./*.o

main.o : ./sim_bodies.hpp ./sim_bodies_generator.hpp ./tokenizer.hpp 
	g++ -c main.cpp -lGL -lGLU -lglut -lm -std=c++17 -g

./tokenizer.o : ./tokenizer.hpp 
	g++ -c ./tokenizer.cpp -lGL -lGLU -lglut -lm -std=c++17 -g

./sim_bodies_generator.o : ./sim_bodies_generator.hpp ./sim_bodies.hpp 
	g++ -c ./sim_bodies_generator.cpp -lGL -lGLU -lglut -lm -std=c++17 -g

./sim_bodies.o : ./sim_bodies.hpp 
	g++ -c ./sim_bodies.cpp -lGL -lGLU -lglut -lm -std=c++17 -g


clean : 
	rm ./*.o
