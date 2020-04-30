#include <iostream>
#include <fstream>
#include <vector>
#include <string>

float calcMean(const std::vector<int>& v);
std::vector<int> tokenize(const std::string& s,const char delim= ';');

int main(int argc, char** argv) { 
    if(argv[1] == NULL) {
        std::cout << "ERROR: Archivo no seleccionado\n";
        return EXIT_FAILURE;
    }
    std::ifstream file(argv[1]);
    std::ofstream output("promedios_"+std::string(argv[1]));
    std::vector<int> values;
    std::string build="";
    float mean;
    for(std::string line; getline(file, line);) {
        values = tokenize(line);
        mean = calcMean(values);
        build = std::to_string(values[0]) + ";" + std::to_string(mean);
        output << build;
    }
    file.close();
    output.close();
    return EXIT_SUCCESS;
}

float calcMean(const std::vector<int>& v) {
    float r;
    for(int i = 1; i < 7; i++) {  //Nem, ranking, cs, historias, mat, leng ; v[0] es el rut.
        r += (float)v[i];
    }
    r = r/6.0;
    return r;
}

std::vector<int> tokenize(const std::string& s,const char delim) {
    std::vector<int> ret_val;
    std::string str;
    for(auto& c : s) {
        if(c == delim) {
            ret_val.push_back(std::stoi(str));
            str="";
        }else {
            str += c;
        }
    }
    return ret_val;
}