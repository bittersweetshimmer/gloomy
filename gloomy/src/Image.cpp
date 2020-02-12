#include <gloomy/Sources/Image.hpp>
#include <stb/stb_image.h>

gloomy::src::Image::Image(Size width, Size height, InternalFormat internal_format, PixelFormat pixel_format, PixelDataType pixel_data_type)
    : width(width), height(height), internal_format(internal_format), pixel_format(pixel_format), pixel_data_type(pixel_data_type), pixels{ PixelsPtr{nullptr, stbi_image_free}, 0 } {

}

gloomy::src::Image::Image(Pixels&& pixels, Size width, Size height, InternalFormat internal_format, PixelFormat pixel_format, PixelDataType pixel_data_type)
    : width(width), height(height), internal_format(internal_format), pixel_format(pixel_format), pixel_data_type(pixel_data_type), pixels(std::move(pixels)) {
}

gloomy::src::Image::~Image() {}

inline gloomy::src::Image gloomy::src::Image::clone() const {
    return gloomy::src::Image(
        this->pixels.clone(),
        this->width,
        this->height,
        this->internal_format,
        this->pixel_format,
        this->pixel_data_type
    );
}

nonstd::expected<gloomy::src::Image, void*> gloomy::src::Image::from_file(std::filesystem::path path) {
    int32_t width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    uint8_t* data = stbi_load(path.string().data(), &width, &height, &channels, 4);
    auto size = static_cast<size_t>(static_cast<int64_t>(width)* static_cast<int64_t>(height) * 4);
    auto pointer = PixelsPtr(reinterpret_cast<std::byte*>(data), stbi_image_free);

    if (data == nullptr) return nonstd::make_unexpected(nullptr);
    return gloomy::src::Image(Pixels(std::move(pointer), size), width, height);
}