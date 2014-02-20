#pragma once

#include "DataFile.h"

#include <string>

class SaveFile : public DataFile
{
public:
	SaveFile(const std::string& filePath);

	bool Read(/*out*/uint32_t& upgradeMask, /*out*/std::string& envName, /*out*/uint32_t& envEntranceId);
	bool Write(const uint32_t upgradeMask, const std::string& envName, const uint32_t& envEntranceId);

private:
	bool HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg) override;
	bool HandleDataWrite(const std::string& fileCode, std::ofstream& fout, boost::format& errorMsg) override;

	uint32_t _upgradeMask;
	std::string _envName;
	uint32_t _envEntranceId;

	static const unsigned int UPGRADE_MASK_OFFSET = 0;
};