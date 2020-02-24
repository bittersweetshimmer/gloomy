#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class BufferUsageCombined : gloomy::Enum {
		STREAM_DRAW = gl::raw::STREAM_DRAW,
		STREAM_READ = gl::raw::STREAM_READ,
		STREAM_COPY = gl::raw::STREAM_COPY,
		STATIC_DRAW = gl::raw::STATIC_DRAW,
		STATIC_READ = gl::raw::STATIC_READ,
		STATIC_COPY = gl::raw::STATIC_COPY,
		DYNAMIC_DRAW = gl::raw::DYNAMIC_DRAW,
		DYNAMIC_READ = gl::raw::DYNAMIC_READ,
		DYNAMIC_COPY = gl::raw::DYNAMIC_COPY
	};

	struct BufferUsage {
		enum class Frequency {
			STREAM,
			STATIC,
			DYNAMIC
		};

		enum class Nature {
			DRAW,
			READ,
			COPY
		};

		Frequency frequency;
		Nature nature;

		constexpr BufferUsageCombined combined() const;
		constexpr static BufferUsage from(BufferUsageCombined combined);
	};

	constexpr BufferUsageCombined BufferUsage::combined() const {
		const auto& freq = this->frequency;
		const auto& nat = this->nature;

		if (freq == BufferUsage::Frequency::STREAM) {
			if (nat == BufferUsage::Nature::DRAW) {
				return BufferUsageCombined::STREAM_DRAW;
			}
			else if (nat == BufferUsage::Nature::READ) {
				return BufferUsageCombined::STREAM_READ;
			}
			else if (nat == BufferUsage::Nature::COPY) {
				return BufferUsageCombined::STREAM_COPY;
			}
		}
		else if (freq == BufferUsage::Frequency::STATIC) {
			if (nat == BufferUsage::Nature::DRAW) {
				return BufferUsageCombined::STATIC_DRAW;
			}
			else if (nat == BufferUsage::Nature::READ) {
				return BufferUsageCombined::STATIC_READ;
			}
			else if (nat == BufferUsage::Nature::COPY) {
				return BufferUsageCombined::STATIC_COPY;
			}
		}
		else if (freq == BufferUsage::Frequency::DYNAMIC) {
			if (nat == BufferUsage::Nature::DRAW) {
				return BufferUsageCombined::DYNAMIC_DRAW;
			}
			else if (nat == BufferUsage::Nature::READ) {
				return BufferUsageCombined::DYNAMIC_READ;
			}
			else if (nat == BufferUsage::Nature::COPY) {
				return BufferUsageCombined::DYNAMIC_COPY;
			}
		}

		return BufferUsageCombined::STATIC_DRAW;
	}

	inline constexpr BufferUsage BufferUsage::from(BufferUsageCombined combined) {
		if (combined == BufferUsageCombined::STATIC_DRAW) return BufferUsage{ BufferUsage::Frequency::STATIC, BufferUsage::Nature::DRAW };
		else if (combined == BufferUsageCombined::STATIC_READ) return BufferUsage{ BufferUsage::Frequency::STATIC, BufferUsage::Nature::READ };
		else if (combined == BufferUsageCombined::STATIC_COPY) return BufferUsage{ BufferUsage::Frequency::STATIC, BufferUsage::Nature::COPY };
		else if (combined == BufferUsageCombined::STREAM_DRAW) return BufferUsage{ BufferUsage::Frequency::STREAM, BufferUsage::Nature::DRAW };
		else if (combined == BufferUsageCombined::STREAM_READ) return BufferUsage{ BufferUsage::Frequency::STREAM, BufferUsage::Nature::READ };
		else if (combined == BufferUsageCombined::STREAM_COPY) return BufferUsage{ BufferUsage::Frequency::STREAM, BufferUsage::Nature::COPY };
		else if (combined == BufferUsageCombined::DYNAMIC_DRAW) return BufferUsage{ BufferUsage::Frequency::DYNAMIC, BufferUsage::Nature::DRAW };
		else if (combined == BufferUsageCombined::DYNAMIC_READ) return BufferUsage{ BufferUsage::Frequency::DYNAMIC, BufferUsage::Nature::READ };
		else if (combined == BufferUsageCombined::DYNAMIC_COPY) return BufferUsage{ BufferUsage::Frequency::DYNAMIC, BufferUsage::Nature::COPY };
		return BufferUsage{ BufferUsage::Frequency::STATIC, BufferUsage::Nature::DRAW };
	}
}