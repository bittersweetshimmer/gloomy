#pragma once

namespace gloomy::util {
	struct NonCopyable {
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
		NonCopyable(NonCopyable&& other) = default;
		NonCopyable& operator=(NonCopyable&& other) = default;
	};
}