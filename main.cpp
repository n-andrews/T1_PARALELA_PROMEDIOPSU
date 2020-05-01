#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

float calcMean(const std::vector<int>& v);
std::vector<int> tokenize(const std::string& s,const char delim= ';');

int main(int argc, char** argv) { 
    auto start = std::chrono::high_resolution_clock::now(); 
    if(argv[1] == NULL) {
        std::cout << "ERROR: Archivo no seleccionado\n";
        return EXIT_FAILURE;
    }
    std::ifstream file(argv[1]);
    std::cout << "i: " << argv[1] << std::endl;
    std::string outputStr = "promediosPSU.csv";
    std::cout << "o: " << outputStr << std::endl;
    std::ofstream output(outputStr);
    std::vector<int> values;
    std::string build="";
    float mean = 0.f;
    for(std::string line; std::getline(file, line);) {
        values = tokenize(line);
        mean = calcMean(values);
        build = std::to_string(values[0]) + ";" + std::to_string(mean) + "\n";
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
    for(int i = 1; i < 6; i++) {  //rut0, Nem1, ranking2, cs3, historias4, mat5, leng6 ; v[0] es el rut.
        r += v[i];
    }
    f = (float)r/6.0;
    return f;
}

std::vector<int> tokenize(const std::string& s,const char delim) {
    std::vector<int> ret_val;
    std::string str;
    for(auto c : s) {
        if(c == delim) {
            ret_val.push_back(std::stoi(str));
            str="";
        }else {
            str += c;
        }
    }
    return ret_val;
}