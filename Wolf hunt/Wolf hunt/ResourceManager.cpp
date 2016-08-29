#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	InitTextures();
	InitShaders();
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::InitTextures()
{
	FloorTexture = sf::Texture();
	FloorTexture.loadFromFile("./Textures/Floor.png");
	TracerTexture = sf::Texture();
	TracerTexture.loadFromFile("./Textures/Ray.png");
	SwordTexture = sf::Texture();
	SwordTexture.loadFromFile("./Textures/Sword.png");
}
void ResourceManager::InitShaders()
{
	FlashBangShaderFrag.loadFromFile("./Shaders/Flashbang.frag", sf::Shader::Fragment);
}