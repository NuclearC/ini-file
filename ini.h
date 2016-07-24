// ----------------------------------------------------- //
//                                                       //
//             Ini File C++ Libraries                    //
//               Copyright (C) 2016                      //
//                  by NucleArc                          //
//                                                       //
// ----------------------------------------------------- //

#pragma once

#ifndef INI_H_
#define INI_H_

#include <fstream>
#include <locale>
#include <codecvt>
#include <string>
#include <sstream>

class IniNode
{
private:
	std::string fileName;
	std::string section;

	std::string getValueFromFile(std::string);
public:
	IniNode(std::string _fileName, std::string _section)
		: fileName(_fileName),section(_section) {}
	~IniNode();

	void setValue(std::string, std::string);

	std::string getValue(std::string);
	int getInt(std::string);
	char getChar(std::string);
	float getFloat(std::string);
	double getDouble(std::string);
	long getLong(std::string);
	long long getLongLong(std::string);

	std::string operator[](std::string);
};

class IniFile
{
private:
	std::string fileName;
public:
	IniFile(std::string _fileName) : fileName(_fileName) {}
	~IniFile();

	IniNode operator[](std::string);
};

#endif // INI_H

