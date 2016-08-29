#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
class ResourceManager
{
public:
	sf::Texture FloorTexture;
	sf::Texture PlayerTexture;
	sf::Texture SwordTexture;
	sf::Texture TracerTexture;
	sf::Texture TracerTerminationTexture;
	sf::Shader FlashBangShaderFrag;
	ResourceManager();
	~ResourceManager();
	void InitTextures();
	void InitShaders();
};

