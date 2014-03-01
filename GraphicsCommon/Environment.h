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

	typedef Object::Core arch_desc_t;
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

	template<typename T>
	struct Collection
	{
		friend Environment;

		size_t Size() const { return _list.size(); }
		T Get(const unsigned int& idx) const { return _list[idx]; }
		T Get(size_t& idx) const { return Get(static_cast<unsigned int>(idx)); }
		void Add() { _list.push_back(T()); }
		void Remove(const unsigned int& idx) { _list.erase(_list.begin() + idx); }
		void Update(const T& item, const unsigned int& idx) { _list[idx] = item; }
		bool StreamInsert(std::ofstream& stream) const { return DataFile::Insert(stream, _list); }
		bool StreamExtract(std::ifstream& stream) { return DataFile::Extract(stream, _list); }

	private:
		std::vector<T> _list;
	};

	Environment(const std::string& name, const unsigned int& entranceId, const bool fullPath = false);

	//Configures the parameters to match the currently-loaded information
	void Read(std::vector<std::shared_ptr<Object>>& objList, std::shared_ptr<Player> player, std::shared_ptr<Camera> cam,
		const Exit::env_change_func_t& envChange);
	//Writes the currently-loaded information to disc
	void Write();

	std::string Name() const;
	unsigned int EntranceId() const;
	float MaxX() const;
	void MaxX(const float& maxX);
	float MaxY() const;
	void MaxY(const float& maxY);

	Collection<arch_desc_t> _architecture;
	Collection<enemy_desc_t> _enemies;
	Collection<upgrade_desc_t> _upgrades;
	Collection<entrance_desc_t> _entrances;
	Collection<exit_desc_t> _exits;
protected:
	bool HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg) override;
	bool HandleDataWrite(const std::string& fileCode, std::ofstream& fout, boost::format& errorMsg) override;

	std::string _name;
	unsigned int _entranceId;
	uint64_t _exData;
	float _maxX, _maxY;
};