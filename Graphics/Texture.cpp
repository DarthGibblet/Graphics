#include "Texture.h"

#include <Windows.h>

Texture::Texture(const std::string& filePath) : _textureId(0)
{
	unsigned char header[124];

	FILE *fp;

	fopen_s(&fp, filePath.c_str(), "rb");

	char filecode[4];
	fread(filecode, 1, 4, fp);
	if(strncmp(filecode, "DDS ", 4) != 0)
	{
		fclose(fp);
		return;
	}

	fread(&header, 124, 1, fp);
	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);

	unsigned char* buffer;
	unsigned int bufsize;
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	auto rv = fread(buffer, 1, bufsize, fp);
	fclose(fp);

	unsigned int components = (fourCC == mmioFOURCC('D', 'X', 'T', '1'));
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
		free(buffer);
		return;
	}

	glGenTextures(1, &_textureId);

	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	for(unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3)/4) * ((height + 3)/4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);
		offset += size;
		width /= 2;
		height /= 2;
	}
	free(buffer);
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

