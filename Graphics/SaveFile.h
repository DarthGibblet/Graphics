#pragma once

#include <string>

class SaveFile
{
public:
	SaveFile(const std::string& filePath);

	bool Read(unsigned int& upgradeMask);
	bool Write(const unsigned int upgradeMask);

private:
	std::string _filePath;

	static const unsigned int UPGRADE_MASK_OFFSET = 0;
};