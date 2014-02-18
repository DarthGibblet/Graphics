#pragma once

#include "DataFile.h"
#include "Object.h"
#include "Entity.h"
#include "Upgrade.h"
#include "Player.h"

#include <string>
#include <vector>
#include <memory>

class Environment : DataFile
{
public:

	Environment(const std::string& filePath);

	void Read(std::vector<std::shared_ptr<Object>>& objList, std::shared_ptr<Player> player);
	void Edit();

	float MaxX() const;
	float MaxY() const;

protected:
	bool HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg) override;
	bool HandleDataWrite(const std::string& fileCode, std::ofstream& fout, boost::format& errorMsg) override;

	typedef std::pair<Object::EnemyType::E, Object::Core> enemy_desc_t;
	typedef std::pair<Upgrade::Type::E, Object::Core> upgrade_desc_t;

	uint64_t _exData;
	float _maxX, _maxY;
	std::vector<Object::Core> _objList;
	std::vector<enemy_desc_t> _enemyList;
	std::vector<upgrade_desc_t> _upgradeList;
};