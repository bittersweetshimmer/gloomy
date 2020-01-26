#pragma once
#include <optional>
#include <functional>

#include <gloomy/gl.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Sources/Image.hpp>
#include <gloomy/Enum/Texture/Kind.hpp>

namespace gloomy {
    struct Program : public Object<Program>, public Bindable<Program>, public Committable<Program> {
        using Object<Program>::Object;

        template<typename... Ts>
        Program(Ts&&... shaders) : shaders{{std::forward<Ts>(shaders).get_raw_id()...}} {};
        Program(Program&& other) noexcept;
        Program& operator=(Program&& other) noexcept;

        template<typename T, typename... Ts>
        inline void attach_shaders(T&& shader, Ts&&... shaders);

        inline std::vector<RawID>& get_shaders();
        inline const std::vector<RawID>& get_shaders() const;
        inline void clear_shaders();

        using UniformLocation = gloomy::util::Newtype<I32, struct UniformTag>;
        UniformLocation get_uniform_location(const std::string& name) const;

    private:
        std::vector<RawID> shaders;
   //     mutable std::unordered_map<std::string, UniformLocation> cached_locations;

        friend struct CommittableTrait<Program>;
    };

    template<> struct ObjectTrait<Program> {
        static inline ID<Program> generate() { ID<Program> id; id.get() = gl::create_program(); return id; };
        static inline void release(const ID<Program>& id) {
            assert(id.is_valid() && "Releasing null Program.");
            gl::delete_program(id.get());
        };
    };

    template<> struct BindableTrait<Program> {
        static inline void bind(const Program& program) {
            assert(program.get_id().is_valid() && "Binding not generated Program.");
            gl::use_program(program.get_raw_id());
        };
        static inline void unbind(const Program& texture) { gl::use_program(gloomy::null_raw_id); };
    };

    template<> struct CommittableTrait<Program> {
        static constexpr bool bind_before_commit = false;
        static inline void commit(const Program& program) {
            assert(program.shaders.size() != 0 && "Program commit with no attached shaders.");

            for (const auto& shader_id : program.shaders) {
                gl::attach_shader(program.get_raw_id(), shader_id);
            }

            gl::link_program(program.get_raw_id());

            {
                int32_t success;
                char info[512];
                gl::get_program_iv(program.get_raw_id(), gl::LINK_STATUS, &success);

                if (!success) {
                    gl::get_program_info_log(program.get_raw_id(), 512, nullptr, info);

                    assert(success && "Program linking failed.");
                }
            }
        };
    };

    template<typename T, typename ...Ts>
    inline void Program::attach_shaders(T&& shader, Ts&& ...shaders) {
        this->shaders.push_back(std::forward<T>(shader));

        if (sizeof...(Ts) > 0) this->attach_shaders(std::forward<Ts>(shaders)...);
    }
}