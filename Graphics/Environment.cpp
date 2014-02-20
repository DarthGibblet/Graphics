#include "Environment.h"
#include "Constants.h"

#include <boost/assign/list_of.hpp>

#include <iostream>

using std::cout;
using std::endl;

Environment::Environment(const std::string& name) : DataFile(std::string(RESOURCE_DIR_PATH) + "environments\\" + name + ".env", boost::assign::list_of("ENV0")),
	_name(name), _exData(0)
{
	boost::format errorMsg;
	if(!ReadInit(errorMsg))
		cout <<errorMsg <<endl;
}

void Environment::Edit()
{
	boost::format errorMsg;
	if(!ReadInit(errorMsg))
	{
		cout <<errorMsg <<endl;
	}
	else
	{
		//_objList.push_back(std::make_shared<Object>());
		//_enemyList.push_back(std::make_pair(Object::EnemyType::Generic, Object::Core()));
		//_upgradeList.push_back(std::make_pair(Upgrade::Type::WALL_JUMP, Object::Core()));
		//_spawnPointList.push_back(glm::vec3(0, 5, 0));
		//_exitList.push_back(Object::Core());
		WriteInit("ENV0", errorMsg);
	}
}

void Environment::Read(std::vector<std::shared_ptr<Object>>& objList, std::shared_ptr<Player> player, const uint32_t& entranceId, std::shared_ptr<Camera> cam)
{
	foreach(_objList, [&objList](const Object::Core& objCore)
	{
		objList.push_back(std::make_shared<Object>(objCore));
	});

	foreach(_enemyList, [&objList](const enemy_desc_t& enemyDesc)
	{
		objList.push_back(std::make_shared<Entity>(enemyDesc.first, enemyDesc.second));
	});

	foreach(_upgradeList, [&objList, &player](const upgrade_desc_t& upgradeDesc)
	{
		if(!player->HasUpgrade(upgradeDesc.first))
			objList.push_back(std::make_shared<Upgrade>(upgradeDesc.first, upgradeDesc.second));
	});

	foreach(_exitList, [&objList](const Object::Core& exitDesc)
	{
		objList.push_back(std::make_shared<Object>(exitDesc));
	});

	if(_entryList.size() > entranceId)
		player->Pos(_entryList[entranceId]);
	else
		std::cout <<"Error loading environment file. Unable to find entrance with ID " <<entranceId <<std::endl;
	cam->SetRestrictLeft(-_maxX);
	cam->SetRestrictRight(_maxX);
	cam->SetRestrictTop(_maxY);
	cam->SetRestrictBottom(-_maxY);
}

std::string Environment::Name() const
{
	return _name;
}

float Environment::MaxX() const
{
	return _maxX;
}

float Environment::MaxY() const
{
	return _maxY;
}

bool Environment::HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg)
{
	bool rv = true;

	rv &= Extract(fin, _exData);
	rv &= Extract(fin, _maxX);
	rv &= Extract(fin, _maxY);
	rv &= Extract(fin, _objList);
	rv &= Extract(fin, _enemyList);
	rv &= Extract(fin, _upgradeList);
	rv &= Extract(fin, _entryList);
	rv &= Extract(fin, _exitList);

	if(!rv)
	{
		errorMsg = boost::format("Error reading environment file \"%s\"") % _filePath;
		return false;
	}
	return true;
}

bool Environment::HandleDataWrite(const std::string& fileCode, std::ofstream& fout, boost::format& errorMsg)
{
	bool rv = true;

	rv &= Insert(fout, _exData);
	rv &= Insert(fout, _maxX);
	rv &= Insert(fout, _maxY);
	rv &= Insert(fout, _objList);
	rv &= Insert(fout, _enemyList);
	rv &= Insert(fout, _upgradeList);
	rv &= Insert(fout, _entryList);
	rv &= Insert(fout, _exitList);

	if(!rv)
	{
		errorMsg = boost::format("Error writing environment file \"%s\"") % _filePath;
		return false;
	}
	return true;
}