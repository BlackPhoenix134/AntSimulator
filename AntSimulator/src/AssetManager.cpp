#include "AssetManager.hpp"

namespace Assets {

	std::map<std::string, Texture2D> cache;

	Texture2D get(std::string path) {
		if (cache.find(path) == cache.end()) {
			Texture2D tex = LoadTexture(path.c_str());
			cache.emplace(path, tex);
			return tex;
		}
		else {
			return cache[path];
		}
	}
}