#pragma once

#include "DataFile.h"
#include "Object.h"
#include "Entity.h"
#include "Upgrade.h"
#include "Player.h"
#include "Camera.h"
#include "Exit.h"

#include <string>
#include <vector>
#include <memory>

class Environment : DataFile
{
public:

	typedef std::pair<Object::EnemyType::E, Object::Core> enemy_desc_t;
	typedef std::pair<Upgrade::Type::E, Object::Core> upgrade_desc_t;
	typedef glm::vec3 entrance_desc_t;
	typedef struct ExitDesc
	{
		ExitDesc();
		uint32_t _envId;
		uint32_t _entranceId;
		Object::Core _core;

		bool StreamInsert(std::ofstream& fout) const;
		bool StreamExtract(std::ifstream& fin);
	} exit_desc_t;

	Environment(const std::string& name, const unsigned int& entranceId);

	void Read(std::vector<std::shared_ptr<Object>>& objList, std::shared_ptr<Player> player, std::shared_ptr<Camera> cam,
		const Exit::env_change_func_t& envChange);
	void Write();
	void Edit();

	std::string Name() const;
	unsigned int EntranceId() const;
	float MaxX() const;
	void MaxX(const float& maxX);
	float MaxY() const;
	void MaxY(const float& maxY);

	size_t ObjListSize() const;
	Object::Core GetObj(const unsigned int& idx) const;
	void AddObj();
	void RemoveObj(const unsigned int& idx);
	void UpdateObj(const Object::Core& core, const unsigned int& idx);

	size_t EnemyListSize() const;
	enemy_desc_t GetEnemy(const unsigned int& idx) const;
	void AddEnemy();
	void RemoveEnemy(const unsigned int& idx);
	void UpdateEnemy(const enemy_desc_t& desc, const unsigned int& idx);

	size_t UpgradeListSize() const;
	upgrade_desc_t GetUpgrade(const unsigned int& idx) const;
	void AddUpgrade();
	void RemoveUpgrade(const unsigned int& idx);
	void UpdateUpgrade(const upgrade_desc_t& desc, const unsigned int& idx);

	size_t EntranceListSize() const;
	entrance_desc_t GetEntrance(const unsigned int& idx) const;
	void AddEntrance();
	void RemoveEntrance(const unsigned int& idx);
	void UpdateEntrance(const entrance_desc_t& desc, const unsigned int& idx);

	size_t ExitListSize() const;
	exit_desc_t GetExit(const unsigned int& idx) const;
	void AddExit();
	void RemoveExit(const unsigned int& idx);
	void UpdateExit(const exit_desc_t& desc, const unsigned int& idx);

protected:
	bool HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg) override;
	bool HandleDataWrite(const std::string& fileCode, std::ofstream& fout, boost::format& errorMsg) override;

	std::string _name;
	unsigned int _entranceId;
	uint64_t _exData;
	float _maxX, _maxY;
	std::vector<Object::Core> _objList;
	std::vector<enemy_desc_t> _enemyList;
	std::vector<upgrade_desc_t> _upgradeList;
	std::vector<entrance_desc_t> _entryList;
	std::vector<exit_desc_t> _exitList;
};