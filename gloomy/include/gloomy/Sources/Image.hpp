#pragma once

#include <memory>

#include <gloomy/TypeAliases.hpp>
#include <gloomy/Enum/Texture/InternalFormat.hpp>
#include <gloomy/Enum/Texture/PixelFormat.hpp>
#include <gloomy/Enum/Texture/PixelDataType.hpp>

namespace gloomy::src {
	struct Image final {
		std::unique_ptr<std::byte[]> data = nullptr;
		size_t size = 0;

		Size width = 0;
		Size height = 0;
		TextureInternalFormat internal_format = TextureInternalFormat::RGBA;
		PixelFormat pixel_format = PixelFormat::RGBA;
		PixelDataType pixel_data_type = PixelDataType::U8;
	};
}