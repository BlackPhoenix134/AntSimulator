#pragma once
#include <iostream>
#include "raylib.h"
#include <mathfu/glsl_mappings.h>

namespace Comps {
	struct TextureStr {
		std::string name;
	};

	struct SpriteRender {
		Texture2D texture;
		int order = 0;
		Color tint = WHITE;
		mathfu::vec2i desiredDimensions;
		Rectangle sourceRect = { 0,0,0,0 };

		void setTexture(Texture2D texture) {
			this->texture = texture;
			sourceRect = { 0, 0, (float)texture.width, (float)texture.height };
			desiredDimensions = { texture.width, texture.height };
		}

		float width() const {
			float width = texture.width;
			return width * desiredDimensions.x / width;
		}
		
		float height() const {
			float height = texture.height;
			return height * desiredDimensions.y / height;
		}
	};
}