#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;

#ifdef _WIN32
#define EXPORT __declspec(dllexport)  // Exportar funciones en Windows
#else
#define EXPORT
#endif

class FunctionAnalyzer {
private:
    std::string outputFile;

    bool isBalanced(const std::string& code) {
        int count = 0;
        for (char c : code) {
            if (c == '{') count++;
            if (c == '}') count--;
            if (count < 0) return false;
        }
        return count == 0;
    }

    void analyzeFile(const std::string& inputFile) {
        std::ifstream inFile(inputFile);
        std::ofstream outFile(outputFile, std::ios::app);

        if (!inFile.is_open() || !outFile.is_open()) {
            std::cerr << "Error abriendo el archivo: " << inputFile << std::endl;
            return;
        }

        std::string line, currentFunction, functionBody;
        bool insideFunction = false;
        std::regex functionPattern(R"(\w+\s+\w+\s*\([^)]*\)\s*\{)");

        while (std::getline(inFile, line)) {
            if (!insideFunction) {
                std::smatch matches;
                if (std::regex_search(line, matches, functionPattern)) {
                    std::string fullMatch = matches[0];
                    std::regex namePattern(R"(\s(\w+)\s*\()");
                    std::smatch nameMatches;
                    if (std::regex_search(fullMatch, nameMatches, namePattern)) {
                        currentFunction = nameMatches[1];
                    }
                    insideFunction = true;
                    functionBody = line + "\n";
                }
            } else {
                functionBody += line + "\n";

                if (line.find('}') != std::string::npos && isBalanced(functionBody)) {
                    outFile << "ARCHIVO: " << inputFile << "\n";
                    outFile << "FUNCTION_NAME: " << currentFunction << "\n";
                    outFile << "FUNCTION_BODY:\n" << functionBody;
                    outFile << "END_FUNCTION\n\n";

                    insideFunction = false;
                    functionBody.clear();
                }
            }
        }

        inFile.close();
        outFile.close();
    }

public:
    FunctionAnalyzer(const std::string& output) : outputFile(output) {}

    void analyzeDirectory(const std::string& directoryPath) {
        std::ofstream outFile(outputFile, std::ios::trunc);
        outFile.close();

        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            if (entry.path().extension() == ".cpp") {
                std::cout << "Analizando: " << entry.path() << std::endl;
                analyzeFile(entry.path().string());
            }
        }

        // Ejecutar script de Python
        #ifdef _WIN32
            system("python CalcularBigO.py");
        #else
            system("python3 CalcularBigO.py");
        #endif
    }
};

// 🔹 **Función exportada para analizar un directorio**
extern "C" EXPORT void analyzeProject(const char* directoryPath, const char* outputFile) {
    FunctionAnalyzer analyzer(outputFile);
    analyzer.analyzeDirectory(directoryPath);
}
