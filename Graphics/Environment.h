#pragma once

#include "DataFile.h"
#include "Object.h"
#include "Entity.h"

#include <string>
#include <vector>
#include <memory>

class Environment : DataFile
{
public:

	Environment(const std::string& filePath);

	void Read(std::vector<std::shared_ptr<Object>>& objList);
	void Edit();

protected:
	bool HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg) override;
	bool HandleDataWrite(const std::string& fileCode, std::ofstream& fout, boost::format& errorMsg) override;

	typedef std::pair<Object::EnemyType::E, Object::Core> enemy_desc_t;

	uint64_t _exData;
	std::vector<Object::Core> _objList;
	std::vector<enemy_desc_t> _enemyList;
};