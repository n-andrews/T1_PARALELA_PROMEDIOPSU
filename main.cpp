#include <iostream>
#include <fstream>
#include <vector>
#include <string>

float calcMean(const std::vector<int>& v);
std::pair<int, float> tokenize(const std::string s,const char delim= ';');

int main(int argc, char** argv) { 
    if(argv[1] == NULL) {
        std::cout << "ERROR: Archivo no seleccionado\n";
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1]);
    std::ofstream output("promediosPSU.csv");
    std::pair<int,float> pair;
    std::string build="";
    
    // Debido a que OMP no trabaj con for loops no canonicas debemos saber la cantidad de lineas que el archivo tiene, sin contar eof
    int numlines=-1;
    std::string line;
        while(!file.eof()) {
            std::getline(file,line);
            numlines += 1;
        }
    file.close();
    file.open(argv[1]);

    #pragma omp parallel for ordered schedule(auto)
    for(int i = 0; i < numlines; i++) {
    /* Como la STL de c++ no es thread safe (al menos en c++11 y c++14) debemos usar 2 clausulas ordered 
        para evitar que los thread se pisen y modifiquen el valor actual de "line" */
    #pragma omp ordered 
    {
        std::getline(file,line);
        pair = tokenize(line);
    }
        build = std::to_string(pair.first) + ";" + std::to_string(pair.second) + "\n";
    #pragma omp ordered
        output << build;
    }

    file.close();
    output.close();
    std::cout << "--- TALLER 01 ---\n[ Nicolas Andrews Sandoval ]\n[ Daniel Aguilera Tasso ]\n[ Allan Morales Prado ]\n";
    return EXIT_SUCCESS;
}

// Calcula el promedio de acuerdo a los valores en el vector tokenizado del string leído
float calcMean(const std::vector<int>& v) {
    int r = 0;
    float f = 0.f;
    // Reducción por SIMD, no se encontró ninguna ventaja en "paralelizar" este for debido a que ya hay otros threads corriendo pero SIMD ayuda bastante.
    #pragma omp simd reduction(+:r)
    for(unsigned int i = 1; i < v.size(); i++) {  //rut0, Nem1, ranking2, cs3, historias4, mat5, leng6 ; v[0] es el rut.
        r += v[i];
    }
    f = (float)r/6.0;
    return f;
}

// Separa el string en un vector de enteros, calcula el promedio de este y retorna un pair con la información.
std::pair<int,float> tokenize(const std::string s, const char delim) {
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