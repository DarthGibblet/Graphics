#include "Texture.h"

#include <iostream>
#include <fstream>

#include <Windows.h>

using std::cout;
using std::endl;

Texture::Texture(const std::string& filePath) : _textureId(0)
{
	boost::format initErrorMsg;
	if(!Init(filePath, initErrorMsg))
		cout <<initErrorMsg <<endl;
}

bool Texture::Init(const std::string& filePath, boost::format& errorMsg)
{
	if(filePath.empty())
		return true;

	std::ifstream fin(filePath, std::ios_base::binary);

	if(!fin.is_open())
	{
		char errorDetail[128];
		strerror_s(errorDetail, errno);
		errorMsg = boost::format("Error opening file: \"%s\": %s") % filePath % errorDetail;
		return false;
	}

	//First check to make sure the file is in the expected format
	char fileCode[4];
	fin.read(fileCode, 4);
	if(strncmp(fileCode, "DDS ", 4) != 0)
	{
		errorMsg = boost::format("File \"%s\" does not self-identify as a DDS file") % filePath;
		return false;
	}

	//Easier to deal with the header as an array of unsigned ints than a raw char buffer
	const static unsigned int DDS_HEADER_SIZE = 31;
	unsigned int fileHeader[DDS_HEADER_SIZE];
	fin.read(reinterpret_cast<char*>(fileHeader), DDS_HEADER_SIZE * sizeof(unsigned int));
	//We're only interested in a few key values
	unsigned int&	height = fileHeader[2],
					width = fileHeader[3],
					linearSize = fileHeader[4],
					mipMapCount = fileHeader[6],
					fourCC = fileHeader[20];
	
	//Check the four character code to make sure we're using a format OpenGL can understand
	unsigned int format;
	switch(fourCC)
	{
	case mmioFOURCC('D','X','T','1'):
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case mmioFOURCC('D','X','T','3'):
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case mmioFOURCC('D','X','T','5'):
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		errorMsg = boost::format("File \"%s\" uses an unrecognized fourCC: %d") % filePath % fourCC;
		return false;
	}

	//Now that we've got all the metadata we need, read the meat of the file
	unsigned int bufSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	std::unique_ptr<char[]> buffer(new char[bufSize]);
	fin.read(buffer.get(), bufSize);

	//Create the texture and tell OpenGL to use Mipmaps when scaling
	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Dump the data for the main texture and all mipmaps into OpenGL
	unsigned int blockSize = format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 8 : 16;
	char* curOffset = buffer.get();
	unsigned int curWidth = width, curHeight = height;
	for(unsigned int level = 0; level < mipMapCount && (curWidth || curHeight); ++level)
	{
		unsigned int size = ((curWidth + 3)/4) * ((curHeight + 3)/4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, curWidth, curHeight, 0, size, curOffset);
		curOffset += size;
		curWidth /= 2;
		curHeight /= 2;
	}

	//Unbind the texture so it's not hanging around after the constructor call
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void Texture::Activate(int targetTextureUnit)
{
	Set(_textureId, targetTextureUnit);
}

void Texture::Deactivate(int targetTextureUnit)
{
	//Deactivating is just activating a null texture
	Set(0, targetTextureUnit);
}

std::shared_ptr<ResourceHolder> Texture::ActivateScoped(int targetTextureUnit)
{
	Activate(targetTextureUnit);
	return std::make_shared<ResourceHolder>(std::bind(&Texture::Deactivate, this, targetTextureUnit));
}

void Texture::Set(GLuint textureId, int targetTextureUnit)
{
	//Basic sanity check to make sure we're not requesting a texture unit we don't support
	static GLint textureUnitCount = 0;
	if(textureUnitCount == 0)
	{
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &textureUnitCount);
	}

	if(targetTextureUnit >= textureUnitCount)
		return;

	GLint targetTextureUnitId = GL_TEXTURE0 + targetTextureUnit;

	//Make sure we leave OpenGL in the same state we found it minus the texture bind
	GLint startingTextureUnitId = 0;
	glGetIntegerv(GL_ACTIVE_TEXTURE, &startingTextureUnitId);

	if(targetTextureUnitId != startingTextureUnitId)
		glActiveTexture(targetTextureUnitId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	if(targetTextureUnitId != startingTextureUnitId)
		glActiveTexture(startingTextureUnitId);
}

