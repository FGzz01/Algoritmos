#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Función para verificar si un código malicioso está en la transmisión
bool containsCode(const string& transmission, const string& code, int& position) {
    size_t pos = transmission.find(code);
    if (pos != string::npos) {
        position = pos + 1;  // Devuelve la posición iniciando en 1
        return true;
    }
    return false;
}

// Función para verificar si un string es palíndromo
bool isPalindrome(const string& s) {
    int left = 0;
    int right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right])
            return false;
        left++;
        right--;
    }
    return true;
}

// Función para encontrar el palíndromo más largo en un archivo de transmisión
pair<int, string> longestPalindrome(const string& transmission) {
    int maxLength = 0;
    pair<int, string> result(0, "");

    for (int i = 0; i < transmission.size(); i++) {
        for (int j = i; j < transmission.size(); j++) {
            string substring = transmission.substr(i, j - i + 1);
            if (isPalindrome(substring) && substring.size() > maxLength) {
                maxLength = substring.size();
                result = {i + 1, substring};  // Posición inicial y contenido
            }
        }
    }
    return result;
}

// Función para encontrar el substring común más largo entre dos transmisiones
pair<int, string> longestCommonSubstring(const string& t1, const string& t2) {
    int maxLength = 0;
    int endPos = 0;
    vector<vector<int>> dp(t1.size() + 1, vector<int>(t2.size() + 1, 0));

    for (int i = 1; i <= t1.size(); i++) {
        for (int j = 1; j <= t2.size(); j++) {
            if (t1[i - 1] == t2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endPos = i;  // Guardar la posición final del substring
                }
            }
        }
    }

    // Obtener el substring más largo
    string longestSubstring = t1.substr(endPos - maxLength, maxLength);
    return {endPos - maxLength + 1, longestSubstring};  // Posición inicial y el substring
}


string readFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return "";
    }

    stringstream result;
    result << file.rdbuf();
    return result.str();      // Convierte el buffer en un string
}

int main() {
    string transmission1 = readFile("/Users/davidz/Desktop/Actividad Integradora 1/transmission1.txt");
    string transmission2 = readFile("/Users/davidz/Desktop/Actividad Integradora 1/transmission2.txt");
    string mcode1 = readFile("/Users/davidz/Desktop/Actividad Integradora 1/mcode1.txt");
    string mcode2 = readFile("/Users/davidz/Desktop/Actividad Integradora 1/mcode2.txt");
    string mcode3 = readFile("/Users/davidz/Desktop/Actividad Integradora 1/mcode3.txt");

    cout << "Parte 1: \n\n";

    int pos;
    cout << (containsCode(transmission1, mcode1, pos) ? "true " + to_string(pos) : "false") << endl;
    cout << (containsCode(transmission1, mcode2, pos) ? "true " + to_string(pos) : "false") << endl;
    cout << (containsCode(transmission1, mcode3, pos) ? "true " + to_string(pos) : "false") << endl;
    cout << (containsCode(transmission2, mcode1, pos) ? "true " + to_string(pos) : "false") << endl;
    cout << (containsCode(transmission2, mcode2, pos) ? "true " + to_string(pos) : "false") << endl;
    cout << (containsCode(transmission2, mcode3, pos) ? "true " + to_string(pos) : "false") << endl;

    cout << "\nParte 2: \n\n";
    pair<int, string> palindrome1 = longestPalindrome(transmission1);
    cout << palindrome1.first << " " << palindrome1.first + palindrome1.second.size() - 1 << " " << palindrome1.second << endl;

    pair<int, string> palindrome2 = longestPalindrome(transmission2);
    cout << palindrome2.first << " " << palindrome2.first + palindrome2.second.size() - 1 << " " << palindrome2.second << endl;

    cout << "\nParte 3: \n\n";
    pair<int, string> commonSubstring = longestCommonSubstring(transmission1, transmission2);
    cout << commonSubstring.first << " " << commonSubstring.first + commonSubstring.second.size() - 1 << " " << commonSubstring.second << endl;


    return 0;
}