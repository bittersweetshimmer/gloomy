#pragma once
#include <cstddef>
#include <filesystem>
#include <vector>

#include <nonstd/expected.hpp>

#include <gloomy/gl.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Enum/Texture/InternalFormat.hpp>
#include <gloomy/Enum/Texture/PixelFormat.hpp>
#include <gloomy/Enum/Texture/PixelDataType.hpp>
#include <gloomy/Utilities/NonCopyable.hpp>
#include <gloomy/Utilities/DynamicArray.hpp>

#include <stb/stb_image.h>

namespace gloomy::src {
	struct Image : public util::NonCopyable {
		using PixelsDeleter = decltype(stbi_image_free)*;
		using Pixels = util::Bytes<PixelsDeleter>;
		using PixelsPtr = typename Pixels::data_pointer;

		Size width = 0;
		Size height = 0;

		InternalFormat internal_format = InternalFormat::RGBA;
		PixelFormat pixel_format = PixelFormat::RGBA;
		PixelDataType pixel_data_type = PixelDataType::U8;
		
		Pixels pixels;

		Image(
			Size width = 0,
			Size height = 0,
			InternalFormat internal_format = InternalFormat::RGBA,
			PixelFormat pixel_format = PixelFormat::RGBA,
			PixelDataType pixel_data_type = PixelDataType::U8
		);

		Image(
			Pixels&& pixels,
			Size width = 0,
			Size height = 0,
			InternalFormat internal_format = InternalFormat::RGBA,
			PixelFormat pixel_format = PixelFormat::RGBA,
			PixelDataType pixel_data_type = PixelDataType::U8
		);
		~Image();

		Image(Image&& other) noexcept = default;
		Image& operator=(Image&& other) = default;

		inline Image clone() const;

		static nonstd::expected<Image, void*> from_file(std::filesystem::path path);
	};
}