#pragma once

#include "DataFile.h"
#include "Object.h"

#include <string>
#include <vector>
#include <memory>

class Environment : DataFile
{
public:
	Environment(const std::string& filePath);

	void Edit();

	std::vector<std::shared_ptr<Object>> GetObjs();

protected:
	bool HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg) override;
	bool HandleDataWrite(const std::string& fileCode, std::ofstream& fout, boost::format& errorMsg) override;

	uint64_t _exData;
	std::vector<std::shared_ptr<Object>> _objList;
};