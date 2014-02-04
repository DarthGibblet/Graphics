#pragma once

#include <boost/format.hpp>

#include <string>
#include <vector>
#include <fstream>

class DataFile
{
public:
	typedef std::string file_code_t;
	DataFile(const std::string& filePath, const std::vector<std::string>& expectedFileCodes);

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

protected:
	bool ReadInit(boost::format& errorMsg);
	virtual bool HandleDataRead(const file_code_t& fileCode, std::ifstream& fin, boost::format& errorMsg) {return true;};

	bool WriteInit(const std::string& fileCode, boost::format& errorMsg);
	virtual bool HandleDataWrite(const file_code_t& fileCode, std::ofstream& fout, boost::format& errorMsg) {return true;};

	std::string _filePath;
	std::vector<std::string> _expectedFileCodes;
};