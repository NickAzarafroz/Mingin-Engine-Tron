#pragma once
#include <string>
#include <memory>
#include <fstream>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		std::ifstream ReadFile(const std::string& file) const;
		std::ofstream WriteToFile(const std::string& file);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
	};
}
