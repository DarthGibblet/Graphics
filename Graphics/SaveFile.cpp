#include "SaveFile.h"

#include <boost/assign/list_of.hpp>

#include <fstream>

SaveFile::SaveFile(const std::string& filePath) : DataFile(filePath, boost::assign::list_of("SAVE"))
{
}

bool SaveFile::HandleDataRead(const std::string& /*fileCode*/, std::ifstream& fin, boost::format& /*errorMsg*/)
{
	bool rv = true;
	rv &= Extract(fin, _upgradeMask);
	rv &= Extract(fin, _envName);
	rv &= Extract(fin, _envEntranceId);
	return rv;
}

bool SaveFile::HandleDataWrite(const std::string& /*fileCode*/, std::ofstream& fout, boost::format& /*errorMsg*/)
{
	bool rv = true;
	rv &= Insert(fout, _upgradeMask);
	rv &= Insert(fout, _envName);
	rv &= Insert(fout, _envEntranceId);
	return rv;
}

bool SaveFile::Read(/*out*/uint32_t& upgradeMask, /*out*/std::string& envName, /*out*/uint32_t& envEntranceId)
{
	boost::format errorMsg;
	if(!ReadInit(errorMsg))
		return false;

	upgradeMask = _upgradeMask;
	envName = _envName;
	envEntranceId = _envEntranceId;

	return true;
}

bool SaveFile::Write(const uint32_t upgradeMask, const std::string& envName, const uint32_t& envEntranceId)
{
	_upgradeMask = upgradeMask;
	_envName = envName;
	_envEntranceId = envEntranceId;

	boost::format errorMsg;
	if(!WriteInit("SAVE", errorMsg))
		return false;

	return true;
}
