#include "SaveFile.h"

#include <boost/assign/list_of.hpp>

#include <fstream>

SaveFile::SaveFile(const std::string& filePath) : DataFile(filePath, boost::assign::list_of("SAVE"))
{
}

bool SaveFile::HandleDataRead(const std::string& /*fileCode*/, std::ifstream& fin, boost::format& /*errorMsg*/)
{
	Extract(fin, _cachedUpgradeMask);
	return true;
}

bool SaveFile::HandleDataWrite(const std::string& /*fileCode*/, std::ofstream& fout, boost::format& /*errorMsg*/)
{
	Insert(fout, _cachedUpgradeMask);
	return true;
}

bool SaveFile::Read(unsigned int& upgradeMask)
{
	boost::format errorMsg;
	if(!ReadInit(errorMsg))
		return false;

	upgradeMask = _cachedUpgradeMask;

	return true;
}

bool SaveFile::Write(const unsigned int upgradeMask)
{
	_cachedUpgradeMask = upgradeMask;

	boost::format errorMsg;
	if(!WriteInit("SAVE", errorMsg))
		return false;

	return true;
}
