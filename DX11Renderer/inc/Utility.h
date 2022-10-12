#pragma once

#include <Windows.h>
#include <string>
#include <vector>


namespace Utility
{
	std::string  ToString(std::wstring value);
	std::wstring ToWstring(std::string value);

	void SplitString(std::vector<std::string>& dest, std::string origin, std::string tok);
	void Replace(std::string* str, std::string comp, std::string rep);

	std::wstring GetExtension(std::wstring path);
	std::string GetDirectoryName(std::string path);
	std::string GetFileName(std::string path);
	std::string GetFileNameWithoutExtension(std::string path);

	void ToUpper(std::string& value);

	bool ExistFile(std::string path);
	bool ExistFileW(std::wstring path);
	bool ExistDirectory(std::string path);
	void CreateFolders(std::string path);

};