#pragma once

#include "DataFile.h"

#include <string>

class SaveFile : public DataFile
{
public:
	SaveFile(const std::string& filePath);

	bool Read(unsigned int& upgradeMask);
	bool Write(const unsigned int upgradeMask);

private:
	bool HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg) override;
	bool HandleDataWrite(const std::string& fileCode, std::ofstream& fout, boost::format& errorMsg) override;

	unsigned int _cachedUpgradeMask;

	static const unsigned int UPGRADE_MASK_OFFSET = 0;
};