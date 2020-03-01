#include<iostream>
#include<fstream>
#include<vector>
#include "./tokenizer.hpp"

int get_word_tokens(std::string file,std::vector<std::string>& vec){

    std::ifstream in(file);
    std::string word;
    int count;
    while(in.good()){

        in>>word;
        vec.push_back(word);

    }
    in.close();
    count = vec.size();
    if(vec[count-1] == vec[count-2]){
        vec.pop_back();
    }
    return 0;

}