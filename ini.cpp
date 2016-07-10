// ----------------------------------------------------- //
//                                                       //
//             Ini File C++ Libraries                    //
//               Copyright (C) 2016                      //
//                  by NucleArc                          //
//                                                       //
// ----------------------------------------------------- //


#include "ini.h"
#include <Windows.h>


IniFile::~IniFile()
{
}

IniNode IniFile::operator[](std::string section)
{
	return IniNode(fileName, section);
}

IniNode::~IniNode()
{
}

void IniNode::setValue(std::string key, std::string value)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wFileName = converter.from_bytes(fileName);
	std::wstring wSection = converter.from_bytes(section);
	std::wstring wKey = converter.from_bytes(key);
	std::wstring wValue = converter.from_bytes(value);

	if (WritePrivateProfileString(
		wSection.c_str(),
		wKey.c_str(),
		wValue.c_str(),
		wFileName.c_str()) != 0)
	{
		throw std::exception("unable to write Ini content");
		return;
	}
}

std::string IniNode::getValue(std::string key)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wFileName = converter.from_bytes(fileName);
	std::wstring wSection = converter.from_bytes(section);
	std::wstring wKey = converter.from_bytes(key);

	wchar_t wValue[256];
	GetPrivateProfileString(
		wSection.c_str(),
		wKey.c_str(),
		L"",
		wValue,
		256,
		wFileName.c_str());

	if (wValue == 0)
	{
		throw std::exception("unable to read Ini content");
		return std::string();
	}

	std::string value = std::string(converter.to_bytes(wValue));

	return value;
}

std::string IniNode::operator[](std::string key)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wFileName = converter.from_bytes(fileName);
	std::wstring wSection = converter.from_bytes(section);
	std::wstring wKey = converter.from_bytes(key);

	wchar_t wValue[256];
	GetPrivateProfileString(
		wSection.c_str(),
		wKey.c_str(),
		L"",
		wValue,
		256,
		wFileName.c_str());

	if (wValue == 0)
	{
		throw std::exception("unable to read Ini content");
		return std::string();
	}

	std::string value = std::string(converter.to_bytes(wValue));

	return value;
}
