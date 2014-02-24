#pragma once

#include <glm/glm.hpp>

#include <boost/format.hpp>

#include <string>
#include <vector>
#include <fstream>

class DataFile
{
public:
	typedef std::string file_code_t;
	DataFile(const std::string& filePath, const std::vector<std::string>& expectedFileCodes);

	typedef uint32_t length_t;

	template<typename T>
	struct TypeChecker
	{
		static const bool is_base_type = std::is_fundamental<T>::value;
		static const bool is_enum_type = std::is_enum<T>::value;
		static const bool is_other_type = !is_base_type && !is_enum_type;
	};

	//Base Types
	template<typename T>
	static typename std::enable_if<TypeChecker<T>::is_base_type, bool>::type Insert(std::ofstream& stream, const T& val)
	{
		stream.write(reinterpret_cast<const char*>(&val), sizeof(T));
		return stream != 0;
	}

	template<typename T>
	static typename std::enable_if<TypeChecker<T>::is_base_type, bool>::type Extract(std::ifstream& stream, T& val)
	{
		stream.read(reinterpret_cast<char*>(&val), sizeof(T));
		return stream != 0;
	}

	//Enum Types
	template<typename T>
	static typename std::enable_if<TypeChecker<T>::is_enum_type, bool>::type Insert(std::ofstream& stream, const T& val)
	{
		return InsertAs<uint32_t>(stream, val);
	}

	template<typename T>
	static typename std::enable_if<TypeChecker<T>::is_enum_type, bool>::type Extract(std::ifstream& stream, T& val)
	{
		return ExtractAs<uint32_t>(stream, val);
	}

	//Custom Types
	template<typename T>
	static typename std::enable_if<TypeChecker<T>::is_other_type, bool>::type Insert(std::ofstream& stream, const T& val)
	{
		return val.StreamInsert(stream);
	}

	template<typename T>
	static typename std::enable_if<TypeChecker<T>::is_other_type, bool>::type Extract(std::ifstream& stream, T& val)
	{
		return val.StreamExtract(stream);
	}

	//Converted Types
	template<typename S, typename T>
	static bool InsertAs(std::ofstream& stream, const T& val)
	{
		return Insert(stream, static_cast<S>(val));
	}

	template<typename S, typename T>
	static bool ExtractAs(std::ifstream& stream, T& val)
	{
		S tmpVal;
		auto rv = Extract(stream, tmpVal);
		val = static_cast<T>(tmpVal);
		return rv;
	}

	//std::string
	template<>
	static bool Insert<std::string>(std::ofstream& stream, const std::string& val)
	{
		if(!InsertAs<length_t>(stream, val.length()))
			return false;
		stream.write(val.c_str(), val.length());
		return stream ? true : false;
	}

	template<>
	static bool Extract<std::string>(std::ifstream& stream, std::string& val)
	{
		length_t length;
		if(!Extract(stream, length))
			return false;
		val.resize(length);
		stream.read(&val[0], length);
		return stream != 0;
	}

	//std::pair
	template<typename T, typename S>
	static bool Insert(std::ofstream& stream, const std::pair<T, S>& val)
	{
		bool rv = true;
		rv &= Insert(stream, val.first);
		rv &= Insert(stream, val.second);
		return rv;
	}

	template<typename T, typename S>
	static bool Extract(std::ifstream& stream, std::pair<T, S>& val)
	{
		bool rv = true;
		rv &= Extract(stream, val.first);
		rv &= Extract(stream, val.second);
		return rv;
	}

	//std::vector
	template<typename T>
	static bool Insert(std::ofstream& stream, const std::vector<T>& val)
	{
		if(!InsertAs<length_t>(stream, val.size()))
			return false;

		for(auto iItem = std::begin(val); iItem != std::end(val); ++iItem)
		{
			if(!Insert(stream, *iItem))
				return false;
		}

		return true;
	}

	template<typename T>
	static bool Extract(std::ifstream& stream, std::vector<T>& val)
	{
		length_t length;
		if(!Extract(stream, length))
			return false;
		val.resize(length);

		for(length_t i=0; i<length; ++i)
		{
			if(!Extract(stream, val[i]))
				return false;
		}

		return true;
	}

	//glm::vec3
	template<>
	static bool Insert<glm::vec3>(std::ofstream& stream, const glm::vec3& val)
	{
		bool rv = true;
		rv &= Insert(stream, val.x);
		rv &= Insert(stream, val.y);
		rv &= Insert(stream, val.z);
		return rv;
	}

	template<>
	static bool Extract<glm::vec3>(std::ifstream& stream, glm::vec3& val)
	{
		bool rv = true;
		rv &= Extract(stream, val.x);
		rv &= Extract(stream, val.y);
		rv &= Extract(stream, val.z);
		return rv;
	}

protected:
	bool ReadInit(boost::format& errorMsg);
	virtual bool HandleDataRead(const file_code_t& fileCode, std::ifstream& fin, boost::format& errorMsg) {return true;};

	bool WriteInit(const std::string& fileCode, boost::format& errorMsg);
	virtual bool HandleDataWrite(const file_code_t& fileCode, std::ofstream& fout, boost::format& errorMsg) {return true;};

	std::string _filePath;
	std::vector<std::string> _expectedFileCodes;
};