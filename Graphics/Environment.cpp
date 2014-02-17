#include "Environment.h"

#include <boost/assign/list_of.hpp>

#include <iostream>

using std::cout;
using std::endl;

Environment::Environment(const std::string& filePath) : DataFile(filePath, boost::assign::list_of("ENV0")),
	_exData(0)
{
	boost::format errorMsg;
	if(!ReadInit(errorMsg))
		cout <<errorMsg <<endl;
}

void Environment::Edit()
{
	boost::format errorMsg;
	ReadInit(errorMsg);
	//_objList.push_back(std::make_shared<Object>());
	//_enemyList.push_back(std::make_pair(0, Object::Core()));
	WriteInit("ENV0", errorMsg);
}

void Environment::Read(std::vector<std::shared_ptr<Object>>& objList)
{
	foreach(_objList, [&objList](const Object::Core& objCore)
	{
		objList.push_back(std::make_shared<Object>(objCore));
	});

	foreach(_enemyList, [&objList](const enemy_desc_t& enemyDesc)
	{
		objList.push_back(std::make_shared<Entity>(static_cast<Object::EnemyType::E>(enemyDesc.first), enemyDesc.second));
	});
}

bool Environment::HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg)
{
	bool rv = true;

	rv &= Extract(fin, _exData);
	rv &= Extract(fin, _objList);
	rv &= Extract(fin, _enemyList);

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
	rv &= Insert(fout, _objList);
	rv &= Insert(fout, _enemyList);

	if(!rv)
	{
		errorMsg = boost::format("Error writing environment file \"%s\"") % _filePath;
		return false;
	}
	return true;
}