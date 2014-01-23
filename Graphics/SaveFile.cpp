#include "SaveFile.h"

#include <fstream>

typedef char str_len_t;

template<typename T>
void Insert(std::ofstream& stream, const T& val)
{
	stream.write(reinterpret_cast<const char*>(&val), sizeof(T));
}

template<>
void Insert<std::string>(std::ofstream& stream, const std::string& val)
{
	Insert(stream, static_cast<str_len_t>(val.length()));
	stream.write(val.c_str(), val.length());
}

template<typename T>
void Extract(std::ifstream& stream, T& val)
{
	stream.read(reinterpret_cast<char*>(&val), sizeof(T));
}

template<>
void Extract<std::string>(std::ifstream& stream, std::string& val)
{
	str_len_t length;
	Extract(stream, length);
	val.resize(length);
	stream.read(&val[0], length);
}

SaveFile::SaveFile(const std::string& filePath) : _filePath(filePath)
{
}

bool SaveFile::Read(unsigned int& upgradeMask)
{
	std::ifstream fin(_filePath, std::ios_base::binary);

	if(!fin.is_open())
		return false;

	std::string fileCode;
	Extract(fin, fileCode);
	if(fileCode != "SAVE")
		return false;

	Extract(fin, upgradeMask);
	return true;
}

bool SaveFile::Write(const unsigned int upgradeMask)
{
	std::ofstream fout(_filePath, std::ios_base::binary);

	if(!fout.is_open())
		return false;

	Insert(fout, std::string("SAVE"));
	Insert(fout, upgradeMask);
	return true;
}
