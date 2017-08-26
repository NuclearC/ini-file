/*
    Ini File I/O
    Copyright (c) 2016-2017 NuclearC
*/

#ifndef NC_INI_H_
#define NC_INI_H_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm> 
#include <cctype>
#include <locale>

namespace nc {

    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    // trim from start (copying)
    static inline std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
    }

    // trim from end (copying)
    static inline std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
    }

    // trim from both ends (copying)
    static inline std::string trim_copy(std::string s) {
        trim(s);
        return s;
    }

    static std::pair<std::string, std::string> Split(const std::string& str, char delimiter) {
        if (str.find(delimiter) == std::string::npos)
            return{};

        std::string str1 = str.substr(0, str.find(delimiter));
        std::string str2 = str.substr(str.find(delimiter), str.length() - str.find(delimiter));

        for (int i = 0; i < str2.size(); i++) {
            if (isspace(str2[i])) {
                str2.erase(str2.begin() + i);
                i--;
            }
            else if (str2[i] == delimiter) {
                str2.erase(str2.begin() + i);
                i--;
            }
            else {
                break;
            }
        }

        return std::make_pair(str1, str2);
    }

    class Ini;

    class IniNode {
    public:
        std::map<std::string, std::string> values;
        std::string name;

        const std::string& operator[](const std::string& _ValueName);

        void Set(const std::string& _Name, const std::string& _Value);
        const std::string& Get(const std::string& _Name);

        Ini * owner;
    };

    class Ini {
    public:
        Ini(const std::string& _File);
        Ini(const Ini& _Other);
        ~Ini();

        IniNode& operator[](const std::string& _NodeName);

        void Save();
        void Load();

    private:
        std::string file;
        std::fstream fs;
        std::map<std::string, IniNode> nodes;
    };
} // namespace nc

#endif // NC_INI_H_