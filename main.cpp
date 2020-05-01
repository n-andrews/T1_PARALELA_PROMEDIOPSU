#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#define DEBUG_MODE !true

float calcMean(const std::vector<int>& v);
std::pair<int, float> tokenize(const std::string s,const char delim= ';');

int main(int argc, char** argv) { 
    auto start = std::chrono::high_resolution_clock::now(); 
    if(DEBUG_MODE && argv[1] == NULL) {
        std::cout << "ERROR: Archivo no seleccionado\n";
        return EXIT_FAILURE;
    }

    std::ifstream file("archivo.csv");
    std::cout << "i: " << argv[1] << std::endl;
    std::string outputStr = "promediosPSU.csv";
    std::cout << "o: " << outputStr << std::endl;
    std::ofstream output(outputStr);
    std::pair<int,float> pair;
    std::string build="";
    int numlines=-1;
    std::string line;
        while(!file.eof()) {
            std::getline(file,line);
            numlines = numlines + 1;
        }
    file.close();
    file.open(argv[1]);

    #pragma omp parallel for ordered schedule(static)
    for(int i = 0; i < numlines; i++) {
        std::getline(file,line);
        pair = tokenize(line);
        build = std::to_string(pair.first) + ";" + std::to_string(pair.second) + "\n";
    #pragma omp ordered
        output << build;
    }

    file.close();
    output.close();
    std::string pause;
    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
    std::cout << "Duration: " << duration.count() << "ms\n";
    std::cout << "--- TALLER 01 ---\n [ Nicolas Andrews Sandoval ]\n[ Otro integrante ]\n [ Otro mas ]\n";
    std::cin >> pause;
    return EXIT_SUCCESS;
}

float calcMean(const std::vector<int>& v) {
    int r = 0;
    float f = 0.f;
    #pragma omp simd reduction(+:r)
    for(unsigned int i = 1; i < v.size(); i++) {  //rut0, Nem1, ranking2, cs3, historias4, mat5, leng6 ; v[0] es el rut.
        r += v[i];
    }
    f = (float)r/6.0;
    return f;
}

std::pair<int,float> tokenize(const std::string s,const char delim) {
    std::pair<int,float> ret_val;
    std::vector<int> vec;
    std::string str;
    for(auto c : s) {
        if(c == delim) {
            vec.push_back(std::stoi(str));
            str="";
        }else {
            str += c;
        }
    }
    ret_val.first = vec[0];
    ret_val.second = calcMean(vec);
    return ret_val;
}