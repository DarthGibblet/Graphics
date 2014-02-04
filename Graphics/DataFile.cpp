#include "DataFile.h"

//Quick utility function to take care of opening both an std::ifstream and std::ofstream, since the process is identical
template<typename T>
bool PrepStream(const std::string& filePath, T& stream, boost::format& errorMsg)
{
	stream = T(filePath, std::ios_base::binary);

	if(!stream.is_open())
	{
		char errorDetail[128];
		strerror_s(errorDetail, errno);
		errorMsg = boost::format("Error opening file: \"%s\": %s") % filePath % errorDetail;
		return false;
	}

	return true;
}

DataFile::DataFile(const std::string& filePath, const std::vector<std::string>& expectedFileCode) : _filePath(filePath), _expectedFileCodes(expectedFileCode)
{
}

bool DataFile::ReadInit(boost::format& errorMsg)
{
	if(_filePath.empty())
		return true;

	std::ifstream fin;
	if(!PrepStream(_filePath, fin, errorMsg))
		return false;

	//Check to make sure the file is in the expected format
	std::string fileCode;
	fileCode.resize(4, 0);
	fin.read(&fileCode[0], 4);

	bool foundValidFileCode = false;
	std::for_each(std::begin(_expectedFileCodes), std::end(_expectedFileCodes), [&fileCode, &foundValidFileCode](std::string& expectedFileCode)
	{
		if(expectedFileCode == fileCode)
			foundValidFileCode = true;
	});

	if(!foundValidFileCode)
	{
		errorMsg = boost::format("File \"%s\" does not self-identify as one of the required file types") % _filePath;
		return false;
	}

	return this->HandleDataRead(fileCode, fin, errorMsg);
}

bool DataFile::WriteInit(const std::string& fileCode, boost::format& errorMsg)
{
	if(_filePath.empty())
		return true;

	std::ofstream fout;
	if(!PrepStream(_filePath, fout, errorMsg))
		return false;

	fout.write(fileCode.c_str(), fileCode.length());

	return this->HandleDataWrite(fileCode, fout, errorMsg);
}