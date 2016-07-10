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

#include <locale>
#include <codecvt>
#include <string>

class IniNode
{
private:
	std::string fileName;
	std::string section;
public:
	IniNode(std::string _fileName, std::string _section)
		: fileName(_fileName),section(_section) {}
	~IniNode();

	void SetValue(std::string, std::string);
	std::string GetValue(std::string);

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

