/*
    Ini File I/O
    Copyright (c) 2016-2017 NuclearC
*/

#include "ini.h"

namespace nc {
    Ini::Ini(const std::string & _File) : file(_File)
    {
    }

    Ini::Ini(const Ini & _Other)
    {
        file = _Other.file;
    }

    Ini::~Ini()
    {
    }

    IniNode& Ini::operator[](const std::string & _NodeName)
    {
        if (nodes.size() > 0 && nodes.find(_NodeName) != nodes.end())
            return nodes[_NodeName];
        else
            throw std::exception("invalid node name");
    }

    void Ini::Save()
    {
        if (nodes.size() < 1)
            return;

        if (fs.is_open())
            fs.close();

        fs.open(file, std::ios::out | std::ios::trunc);

        for (auto it = nodes.begin(); it != nodes.end(); it++) {
            fs << "[" << it->first << "]\n";

            if (it->second.values.size() < 1)
                continue;

            for (auto it2 = it->second.values.begin(); it2 != it->second.values.end();
                it2++) {
                fs << it2->first;

                if (!it2->second.empty())
                    fs << "=" << it2->second;
                fs << "\n";
            }

            fs << "\n";
        }
    }

    void Ini::Load()
    {
        if (fs.is_open()) {
            fs.close();
        }

        fs.open(file, std::ios::out | std::ios::in);
        
        if (!fs.is_open()) {
            throw std::exception("failed to open the file");
        }

        std::string line, token;

        while (std::getline(fs, line)) {
            if (line.length() < 3)
                continue;

            if (line.front() == '[' && line.find(']') != std::string::npos) {
                token = line.substr(1, line.find(']') - 1);

                IniNode node;
                node.name = token;
                node.owner = this;

                while (std::getline(fs, line)) {
                    if (line.length() < 3)
                        continue;

                    if (line.front() == '[' && line.find(']') != std::string::npos) {
                        nodes[token] = node;
                        token = node.name = line.substr(1, line.find(']') - 1);
                        // break;
                    }
                    else if (line.front() != '#' && line.front() != ';') {
                        auto pair = Split(line, '=');
                        trim(pair.first);
                        trim(pair.second);
                        node.Set(pair.first, pair.second);
                    }
                }

                nodes[token] = node;
            }
        }
    }

    const std::string & IniNode::operator[](const std::string & _ValueName)
    {
        return Get(_ValueName);
    }

    void IniNode::Set(const std::string & _Name, const std::string & _Value)
    {
        values[_Name] = _Value;
    }

    const std::string & IniNode::Get(const std::string & _Name)
    {
        if (values.size() > 0 && values.find(_Name) != values.end())
            return values[_Name];
        else
            throw std::exception("invalid property name");
    }
} // namespace nc