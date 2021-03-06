#include <deque>
#include "AESUtils.h"

unsigned char tableLookup(unsigned char c, bool isInverse) {
    unsigned char index[2];
    unsigned char ret;
    std::string tmpChar;
    // Lambda expression! (completely useless though) :D
    auto convHex = [](unsigned char _c) {
        std::string out;
        std::vector<unsigned char> mod;
        // use the modulo method to get a hexadecimal string.
        if (_c) {
            while (_c != 0) {
                mod.push_back((unsigned char)(_c % 16));
                _c /= 16;
            }
            for (long i = mod.size() - 1; i >= 0; i--) {
                out += mod[i];
            }
        } else {
            out += '\0';
        }
        return out;
    };

    tmpChar = convHex(c);
    if (tmpChar.length() == 2) {
        index[0] = static_cast<unsigned char>(tmpChar[0]);
        index[1] = static_cast<unsigned char>(tmpChar[1]);
    } else {
        index[0] = 0;
        index[1] = static_cast<unsigned char>(tmpChar[0]);
    }

    ret = isInverse ? inv_s[index[0]][index[1]] : s[index[0]][index[1]];
    return ret;
}

std::string readFile(std::string s, int &nb_lines) {
    nb_lines = 0;
    std::string output;
    std::string line;
    std::string filename = s != "" ? s : "/home/notjustin/Projects/Personal/AES/AEScpp17/test2.txt";
    std::ifstream file(filename);
    if (file.is_open()) {
        while (getline(file, line)) {
            output += line + "\n";
            nb_lines++;
        }
        file.close();
    } else {
        std::cout << "Failed to open " << filename << "\n";
    }
    return output;
}