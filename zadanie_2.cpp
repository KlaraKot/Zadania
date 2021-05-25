#include <iostream>
#include <string>

std::string compress(std::string expression){
    int length = expression.length();
    std::string compres_string = "";
    int counter= 0;
    for(auto i =0; i<length; i++){
        if(i==0){
            compres_string += expression[i];
            counter += 1;
        }
        else if(expression[i] == expression[i-1]){
            counter += 1;
        }
        else if(expression[i] != expression[i-1]){
            compres_string += std::to_string(counter);
            counter = 0;
            compres_string += expression[i];
            counter += 1;
        }
    }
    compres_string += std::to_string(counter);
    return compres_string;
}


std::string decompress(std::string hash){

    std::string result = "";

    for(auto i=0; i<hash.length(); ++i){
        if(isdigit(hash[i])){
            int counter = hash[i] - 48;
            for(auto k = 0; k<counter; ++k){
                result += hash[i-1];
            }
        }
    }
return result;
}

int main() {

    std::string test = "hhhhrrttftfgk";
    std::string test1 = compress(test);
    std::cout<<test1<<std::endl;
    std::string test2 = decompress(test1);
    std::cout<<test2<<std::endl;

    return 0;
}
