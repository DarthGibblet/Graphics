#include "Environment.h"
#include "Constants.h"
#include "Exit.h"

#include <boost/assign/list_of.hpp>

#include <iostream>

using std::cout;
using std::endl;

Environment::ExitDesc::ExitDesc() : _envId(0), _entranceId(0)
{
}

Environment::Environment(const std::string& name, const unsigned int& entranceId, const bool fullPath) : 
	DataFile(fullPath ? name : std::string(RESOURCE_DIR_PATH) + "environments\\" + name + ".env", boost::assign::list_of("ENV0")),
	_name(name), _entranceId(entranceId), _exData(0)
{
	boost::format errorMsg;
	if(!ReadInit(errorMsg))
		cout <<errorMsg <<endl;
}

void Environment::Read(std::vector<std::shared_ptr<Object>>& objList, std::shared_ptr<Player> player, std::shared_ptr<Camera> cam,
	const Exit::env_change_func_t& envChange)
{
	objList.clear();
	objList.push_back(cam);
	objList.push_back(player);

	foreach(_architecture._list, [&objList](const arch_desc_t& archCore)
	{
		objList.push_back(std::make_shared<Object>(archCore));
	});

	foreach(_enemies._list, [&objList](const enemy_desc_t& enemyDesc)
	{
		objList.push_back(std::make_shared<Entity>(enemyDesc.first, enemyDesc.second));
	});

	foreach(_upgrades._list, [&objList, &player](const upgrade_desc_t& upgradeDesc)
	{
		if(!player->HasUpgrade(upgradeDesc.first))
			objList.push_back(std::make_shared<Upgrade>(upgradeDesc.first, upgradeDesc.second));
	});

	foreach(_exits._list, [&objList, &envChange](const exit_desc_t& exitDesc)
	{
		objList.push_back(std::make_shared<Exit>(exitDesc._core, GetEnvName(exitDesc._envId), exitDesc._entranceId, envChange));
	});

	if(_entrances.Size() > _entranceId)
		player->Pos(_entrances._list[_entranceId]);
	else
		std::cout <<"Error loading environment file. Unable to find entrance with ID " <<_entranceId <<std::endl;
	cam->SetRestrictLeft(-_maxX);
	cam->SetRestrictRight(_maxX);
	cam->SetRestrictTop(_maxY);
	cam->SetRestrictBottom(-_maxY);
}

void Environment::Write()
{
	boost::format errorMsg;
	WriteInit("ENV0", errorMsg);
}

std::string Environment::Name() const
{
	return _name;
}

uint32_t Environment::EntranceId() const
{
	return _entranceId;
}

float Environment::MaxX() const
{
	return _maxX;
}

void Environment::MaxX(const float& maxX)
{
	_maxX = maxX;
}

float Environment::MaxY() const
{
	return _maxY;
}

void Environment::MaxY(const float& maxY)
{
	_maxY = maxY;
}

bool Environment::HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg)
{
	bool rv = true;

	rv &= Extract(fin, _exData);
	rv &= Extract(fin, _maxX);
	rv &= Extract(fin, _maxY);
	rv &= Extract(fin, _architecture);
	rv &= Extract(fin, _enemies);
	rv &= Extract(fin, _upgrades);
	rv &= Extract(fin, _entrances);
	rv &= Extract(fin, _exits);

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
	rv &= Insert(fout, _architecture);
	rv &= Insert(fout, _enemies);
	rv &= Insert(fout, _upgrades);
	rv &= Insert(fout, _entrances);
	rv &= Insert(fout, _exits);

	if(!rv)
	{
		errorMsg = boost::format("Error writing environment file \"%s\"") % _filePath;
		return false;
	}
	return true;
}

bool Environment::ExitDesc::StreamInsert(std::ofstream& fout) const
{
	bool rv = true;
	rv &= Insert(fout, _envId);
	rv &= Insert(fout, _entranceId);
	rv &= Insert(fout, _core);
	return rv;
}

bool Environment::ExitDesc::StreamExtract(std::ifstream& fin)
{
	bool rv = true;
	rv &= Extract(fin, _envId);
	rv &= Extract(fin, _entranceId);
	rv &= Extract(fin, _core);
	return rv;
}