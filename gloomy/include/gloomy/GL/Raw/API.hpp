#pragma once

#include <iostream>
#include <gloomy/gl.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/Enum/Error.hpp>

namespace gloomy::gl::raw {
	inline gloomy::Enum get_error() { return glGetError(); }
}

namespace gloomy::util {
	inline void check_error(const char* file, uint32_t line, const char* expression) {
		auto error = gloomy::to_enum<gloomy::Error>(gloomy::gl::raw::get_error());

		if (error != Error::NONE) {
			std::cerr << "OpenGL error: " << gloomy::error_message(error) << "\n\tFile: " << file << ",\n\tLine: " << line << ",\n\tExpression: " << expression << std::endl;
		}
	}
}

#ifdef GLOOMY_DEBUG
#define GLOOMY_CHECK(expr) do { expr; gloomy::util::check_error(__FILE__, __LINE__, #expr); } while (false)
#else
#define GLOOMY_CHECK(expr) (expr)
#endif

namespace gloomy::gl::raw {
	/*
	inline void cull_face(gloomy::Enum mode) { glCullFace(mode); }
	inline void front_face(gloomy::Enum mode) { glFrontFace(mode); }

	inline void line_width(Float width) { glLineWidth(width); }
	inline void point_size(Float size) { glPointSize(size); };
	inline void polygon_mode(gloomy::Enum face, gloomy::Enum mode) { glPolygonMode(face, mode); }
	*/

	inline void hint(gloomy::Enum target, gloomy::Enum mode) { (glHint(target, mode)); }
	inline void enable(gloomy::Enum cap) { (glEnable(cap)); }
	inline void disable(gloomy::Enum cap) { (glDisable(cap)); }
	inline void viewport(I32 x, I32 y, Size width, Size height) { (glViewport(x, y, width, height)); }
	inline void clear(Bitfield mask) { (glClear(mask)); }
	inline void clear_color(Float red, Float green, Float blue, Float alpha) { (glClearColor(red, green, blue, alpha)); }
	inline void blend_func(gloomy::Enum sfactor, gloomy::Enum dfactor) { (glBlendFunc(sfactor, dfactor)); }
	inline void blend_func_separate(gloomy::Enum sfactor_rgb, gloomy::Enum dfactor_rgb, gloomy::Enum sfactor_a, gloomy::Enum dfactor_a) {
		(glBlendFuncSeparate(sfactor_rgb, dfactor_rgb, sfactor_a, dfactor_a));
	}

	inline void gen_textures(Size n, U32* textures) { (glGenTextures(n, textures)); }
	inline void delete_textures(Size n, const U32* textures) { (glDeleteTextures(n, textures)); }
	inline void bind_texture(gloomy::Enum target, U32 texture) { (glBindTexture(target, texture)); }
	inline void active_texture(gloomy::Enum texture) { (glActiveTexture(texture)); }
	inline void tex_parameter_f(gloomy::Enum target, gloomy::Enum pname, Float param) { (glTexParameterf(target, pname, param)); }
	inline void tex_parameter_i(gloomy::Enum target, gloomy::Enum pname, I32 param) { (glTexParameteri(target, pname, param)); }
	inline void tex_image_2D(gloomy::Enum target, I32 level, I32 internalformat, Size width, Size height, I32 border, gloomy::Enum format, gloomy::Enum type, const void* pixels) {
		(glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels));
	}

	inline void gen_buffers(Size n, U32* buffers) { (glGenBuffers(n, buffers)); }
	inline void bind_buffer(gloomy::Enum target, U32 buffer) { (glBindBuffer(target, buffer)); }
	inline void delete_buffers(Size n, const U32* buffers) { (glDeleteBuffers(n, buffers)); }
	inline void buffer_data(gloomy::Enum target, SizeIPointer size, const void* data, gloomy::Enum usage) { (glBufferData(target, size, data, usage)); }
	inline void buffer_sub_data(gloomy::Enum target, IPointer offset, SizeIPointer size, const void* data) { (glBufferSubData(target, offset, size, data)); }

	inline void bind_vertex_array(U32 array) { (glBindVertexArray(array)); }
	inline void delete_vertex_array(Size n, const U32* arrays) { (glDeleteVertexArrays(n, arrays)); }
	inline void gen_vertex_arrays(Size n, U32* arrays) { (glGenVertexArrays(n, arrays)); }
	inline void enable_vertex_attrib_array(U32 index) { (glEnableVertexAttribArray(index)); }
	inline void vertex_attrib_pointer(U32 index, I32 size, gloomy::Enum type, Bool normalized, Size stride, const void* pointer) {
		(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
	}
	inline void vertex_attrib_divisor(U32 index, U32 divisor) { (glVertexAttribDivisor(index, divisor)); }

	inline U32 create_shader(gloomy::Enum type) { return glCreateShader(type); }
	inline void delete_shader(U32 shader) { (glDeleteShader(shader)); }
	inline void shader_source(U32 shader, Size count, const Char* const* string, const I32* length) { (glShaderSource(shader, count, string, length)); }
	inline void compile_shader(U32 shader) { (glCompileShader(shader)); }
	inline void get_shader_iv(U32 shader, gloomy::Enum pname, I32* params) { (glGetShaderiv(shader, pname, params)); }
	inline void get_shader_info_log(U32 shader, Size bufSize, Size* length, Char* infolog) { (glGetShaderInfoLog(shader, bufSize, length, infolog)); }

	inline U32 create_program() { return glCreateProgram(); }
	inline void delete_program(U32 program) { (glDeleteProgram(program)); }
	inline void use_program(U32 program) { (glUseProgram(program)); }
	inline void attach_shader(U32 program, U32 shader) { (glAttachShader(program, shader)); }
	inline void link_program(U32 program) { (glLinkProgram(program)); }
	inline void get_program_iv(U32 program, gloomy::Enum pname, I32* params) { (glGetProgramiv(program, pname, params)); }
	inline void get_program_info_log(U32 program, Size bufSize, Size* length, Char* infolog) { (glGetProgramInfoLog(program, bufSize, length, infolog)); }
	inline I32 get_uniform_location(U32 program, const Char* name) { return glGetUniformLocation(program, name); }

	inline void bind_framebuffer(gloomy::Enum target, U32 framebuffer) { (glBindFramebuffer(target, framebuffer)); }

	inline void draw_elements(gloomy::Enum mode, Size count, gloomy::Enum type, const void* indices) { (glDrawElements(mode, count, type, indices)); }
	inline void draw_arrays(gloomy::Enum mode, I32 first, Size count) { (glDrawArrays(mode, first, count)); }

	inline void uniform_1f(gloomy::I32 location, gloomy::Float v0) { glUniform1f(location, v0); }
	inline void uniform_2f(gloomy::I32 location, gloomy::Float v0, gloomy::Float v1) { glUniform2f(location, v0, v1); }
	inline void uniform_3f(gloomy::I32 location, gloomy::Float v0, gloomy::Float v1, gloomy::Float v2)  { glUniform3f(location, v0, v1, v2); }
	inline void uniform_4f(gloomy::I32 location, gloomy::Float v0, gloomy::Float v1, gloomy::Float v2, gloomy::Float v3)  { glUniform4f(location, v0, v1, v2, v3); }
	inline void uniform_1i(gloomy::I32 location, gloomy::I32 v0) { glUniform1i(location, v0); }
	inline void uniform_2i(gloomy::I32 location, gloomy::I32 v0, gloomy::I32 v1) { glUniform2i(location, v0, v1); }
	inline void uniform_3i(gloomy::I32 location, gloomy::I32 v0, gloomy::I32 v1, gloomy::I32 v2)  { glUniform3i(location, v0, v1, v2); }
	inline void uniform_4i(gloomy::I32 location, gloomy::I32 v0, gloomy::I32 v1, gloomy::I32 v2, gloomy::I32 v3)  { glUniform4i(location, v0, v1, v2, v3); }
	inline void uniform_1ui(gloomy::I32 location, gloomy::U32 v0) { glUniform1ui(location, v0); }
	inline void uniform_2ui(gloomy::I32 location, gloomy::U32 v0, gloomy::U32 v1) { glUniform2ui(location, v0, v1); }
	inline void uniform_3ui(gloomy::I32 location, gloomy::U32 v0, gloomy::U32 v1, gloomy::U32 v2) { glUniform3ui(location, v0, v1, v2); }
	inline void uniform_4ui(gloomy::I32 location, gloomy::U32 v0, gloomy::U32 v1, gloomy::U32 v2, gloomy::U32 v3) { glUniform4ui(location, v0, v1, v2, v3); }
	inline void uniform_1fv(gloomy::I32 location, gloomy::Size count, const gloomy::Float *value) { glUniform1fv(location, count, value); }
	inline void uniform_2fv(gloomy::I32 location, gloomy::Size count, const gloomy::Float *value) { glUniform2fv(location, count, value); }
	inline void uniform_3fv(gloomy::I32 location, gloomy::Size count, const gloomy::Float *value) { glUniform3fv(location, count, value); }
	inline void uniform_4fv(gloomy::I32 location, gloomy::Size count, const gloomy::Float *value) { glUniform4fv(location, count, value); }
	inline void uniform_1iv(gloomy::I32 location, gloomy::Size count, const gloomy::I32 *value) { glUniform1iv(location, count, value); }
	inline void uniform_2iv(gloomy::I32 location, gloomy::Size count, const gloomy::I32 *value) { glUniform2iv(location, count, value); }
	inline void uniform_3iv(gloomy::I32 location, gloomy::Size count, const gloomy::I32 *value) { glUniform3iv(location, count, value); }
	inline void uniform_4iv(gloomy::I32 location, gloomy::Size count, const gloomy::I32 *value) { glUniform4iv(location, count, value); }
	inline void uniform_1uiv(gloomy::I32 location, gloomy::Size count, const gloomy::U32 *value) { glUniform1uiv(location, count, value); }
	inline void uniform_2uiv(gloomy::I32 location, gloomy::Size count, const gloomy::U32 *value) { glUniform2uiv(location, count, value); }
	inline void uniform_3uiv(gloomy::I32 location, gloomy::Size count, const gloomy::U32 *value) { glUniform3uiv(location, count, value); }
	inline void uniform_4uiv(gloomy::I32 location, gloomy::Size count, const gloomy::U32 *value) { glUniform4uiv(location, count, value); }
	inline void uniform_mat2fv(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float *value) { glUniformMatrix2fv(location, count, transpose, value); }
 	inline void uniform_mat3fv(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float *value) { glUniformMatrix3fv(location, count, transpose, value); }
 	inline void uniform_mat4fv(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float *value) { glUniformMatrix4fv(location, count, transpose, value); }
 	inline void uniform_mat2x3fv(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float *value) { glUniformMatrix2x3fv(location, count, transpose, value); }
 	inline void uniform_mat3x2fv(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float *value) { glUniformMatrix3x2fv(location, count, transpose, value); }
 	inline void uniform_mat2x4fv(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float *value) { glUniformMatrix2x4fv(location, count, transpose, value); }
 	inline void uniform_mat4x2fv(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float *value) { glUniformMatrix4x2fv(location, count, transpose, value); }
 	inline void uniform_mat3x4fv(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float *value) { glUniformMatrix3x4fv(location, count, transpose, value); }
 	inline void uniform_mat4x3fv(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float *value) { glUniformMatrix4x3fv(location, count, transpose, value); }

	/*
	typedef void (APIENTRYP PFNGLSCISSORPROC)(gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLSCISSORPROC glad_glScissor;
#define glScissor glad_glScissor
	typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, gloomy::Float param);
	GLAPI PFNGLTEXPARAMETERFPROC glad_glTexParameterf;
#define glTexParameterf glad_glTexParameterf
	typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const gloomy::Float* params);
	GLAPI PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv;
#define glTexParameterfv glad_glTexParameterfv
	typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, gloomy::I32 param);
	GLAPI PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
#define glTexParameteri glad_glTexParameteri
	typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const gloomy::I32* params);
	GLAPI PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv;
#define glTexParameteriv glad_glTexParameteriv
	typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 internalformat, gloomy::Size width, gloomy::I32 border, GLenum format, GLenum type, const void* pixels);
	GLAPI PFNGLTEXIMAGE1DPROC glad_glTexImage1D;
#define glTexImage1D glad_glTexImage1D
	typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 internalformat, gloomy::Size width, gloomy::Size height, gloomy::I32 border, GLenum format, GLenum type, const void* pixels);
	GLAPI PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
#define glTexImage2D glad_glTexImage2D
	typedef void (APIENTRYP PFNGLDRAWBUFFERPROC)(GLenum buf);
	GLAPI PFNGLDRAWBUFFERPROC glad_glDrawBuffer;
#define glDrawBuffer glad_glDrawBuffer
	typedef void (APIENTRYP PFNGLCLEARPROC)(GLbitfield mask);
	GLAPI PFNGLCLEARPROC glad_glClear;
#define glClear glad_glClear
	typedef void (APIENTRYP PFNGLCLEARCOLORPROC)(gloomy::Float red, gloomy::Float green, gloomy::Float blue, gloomy::Float alpha);
	GLAPI PFNGLCLEARCOLORPROC glad_glClearColor;
#define glClearColor glad_glClearColor
	typedef void (APIENTRYP PFNGLCLEARSTENCILPROC)(gloomy::I32 s);
	GLAPI PFNGLCLEARSTENCILPROC glad_glClearStencil;
#define glClearStencil glad_glClearStencil
	typedef void (APIENTRYP PFNGLCLEARDEPTHPROC)(GLdouble depth);
	GLAPI PFNGLCLEARDEPTHPROC glad_glClearDepth;
#define glClearDepth glad_glClearDepth
	typedef void (APIENTRYP PFNGLSTENCILMASKPROC)(gloomy::U32 mask);
	GLAPI PFNGLSTENCILMASKPROC glad_glStencilMask;
#define glStencilMask glad_glStencilMask
	typedef void (APIENTRYP PFNGLCOLORMASKPROC)(gloomy::Bool red, gloomy::Bool green, gloomy::Bool blue, gloomy::Bool alpha);
	GLAPI PFNGLCOLORMASKPROC glad_glColorMask;
#define glColorMask glad_glColorMask
	typedef void (APIENTRYP PFNGLDEPTHMASKPROC)(gloomy::Bool flag);
	GLAPI PFNGLDEPTHMASKPROC glad_glDepthMask;
#define glDepthMask glad_glDepthMask
	typedef void (APIENTRYP PFNGLDISABLEPROC)(GLenum cap);
	GLAPI PFNGLDISABLEPROC glad_glDisable;
#define glDisable glad_glDisable
	typedef void (APIENTRYP PFNGLENABLEPROC)(GLenum cap);
	GLAPI PFNGLENABLEPROC glad_glEnable;
#define glEnable glad_glEnable
	typedef void (APIENTRYP PFNGLFINISHPROC)(void);
	GLAPI PFNGLFINISHPROC glad_glFinish;
#define glFinish glad_glFinish
	typedef void (APIENTRYP PFNGLFLUSHPROC)(void);
	GLAPI PFNGLFLUSHPROC glad_glFlush;
#define glFlush glad_glFlush
	typedef void (APIENTRYP PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
	GLAPI PFNGLBLENDFUNCPROC glad_glBlendFunc;
#define glBlendFunc glad_glBlendFunc
	typedef void (APIENTRYP PFNGLLOGICOPPROC)(GLenum opcode);
	GLAPI PFNGLLOGICOPPROC glad_glLogicOp;
#define glLogicOp glad_glLogicOp
	typedef void (APIENTRYP PFNGLSTENCILFUNCPROC)(GLenum func, gloomy::I32 ref, gloomy::U32 mask);
	GLAPI PFNGLSTENCILFUNCPROC glad_glStencilFunc;
#define glStencilFunc glad_glStencilFunc
	typedef void (APIENTRYP PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
	GLAPI PFNGLSTENCILOPPROC glad_glStencilOp;
#define glStencilOp glad_glStencilOp
	typedef void (APIENTRYP PFNGLDEPTHFUNCPROC)(GLenum func);
	GLAPI PFNGLDEPTHFUNCPROC glad_glDepthFunc;
#define glDepthFunc glad_glDepthFunc
	typedef void (APIENTRYP PFNGLPIXELSTOREFPROC)(GLenum pname, gloomy::Float param);
	GLAPI PFNGLPIXELSTOREFPROC glad_glPixelStoref;
#define glPixelStoref glad_glPixelStoref
	typedef void (APIENTRYP PFNGLPIXELSTOREIPROC)(GLenum pname, gloomy::I32 param);
	GLAPI PFNGLPIXELSTOREIPROC glad_glPixelStorei;
#define glPixelStorei glad_glPixelStorei
	typedef void (APIENTRYP PFNGLREADBUFFERPROC)(GLenum src);
	GLAPI PFNGLREADBUFFERPROC glad_glReadBuffer;
#define glReadBuffer glad_glReadBuffer
	typedef void (APIENTRYP PFNGLREADPIXELSPROC)(gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height, GLenum format, GLenum type, void* pixels);
	GLAPI PFNGLREADPIXELSPROC glad_glReadPixels;
#define glReadPixels glad_glReadPixels
	typedef void (APIENTRYP PFNGLGETBOOLEANVPROC)(GLenum pname, gloomy::Bool* data);
	GLAPI PFNGLGETBOOLEANVPROC glad_glGetBooleanv;
#define glGetBooleanv glad_glGetBooleanv
	typedef void (APIENTRYP PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble* data);
	GLAPI PFNGLGETDOUBLEVPROC glad_glGetDoublev;
#define glGetDoublev glad_glGetDoublev
	typedef GLenum(APIENTRYP PFNGLGETERRORPROC)(void);
	GLAPI PFNGLGETERRORPROC glad_glGetError;
#define glGetError glad_glGetError
	typedef void (APIENTRYP PFNGLGETFLOATVPROC)(GLenum pname, gloomy::Float* data);
	GLAPI PFNGLGETFLOATVPROC glad_glGetFloatv;
#define glGetFloatv glad_glGetFloatv
	typedef void (APIENTRYP PFNGLGETINTEGERVPROC)(GLenum pname, gloomy::I32* data);
	GLAPI PFNGLGETINTEGERVPROC glad_glGetIntegerv;
#define glGetIntegerv glad_glGetIntegerv
	typedef const GLubyte* (APIENTRYP PFNGLGETSTRINGPROC)(GLenum name);
	GLAPI PFNGLGETSTRINGPROC glad_glGetString;
#define glGetString glad_glGetString
	typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC)(GLenum target, gloomy::I32 level, GLenum format, GLenum type, void* pixels);
	GLAPI PFNGLGETTEXIMAGEPROC glad_glGetTexImage;
#define glGetTexImage glad_glGetTexImage
	typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, gloomy::Float* params);
	GLAPI PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv;
#define glGetTexParameterfv glad_glGetTexParameterfv
	typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv;
#define glGetTexParameteriv glad_glGetTexParameteriv
	typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, gloomy::I32 level, GLenum pname, gloomy::Float* params);
	GLAPI PFNGLGETTEXLEVELPARAMETERFVPROC glad_glGetTexLevelParameterfv;
#define glGetTexLevelParameterfv glad_glGetTexLevelParameterfv
	typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, gloomy::I32 level, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETTEXLEVELPARAMETERIVPROC glad_glGetTexLevelParameteriv;
#define glGetTexLevelParameteriv glad_glGetTexLevelParameteriv
	typedef gloomy::Bool(APIENTRYP PFNGLISENABLEDPROC)(GLenum cap);
	GLAPI PFNGLISENABLEDPROC glad_glIsEnabled;
#define glIsEnabled glad_glIsEnabled
	typedef void (APIENTRYP PFNGLDEPTHRANGEPROC)(GLdouble n, GLdouble f);
	GLAPI PFNGLDEPTHRANGEPROC glad_glDepthRange;
#define glDepthRange glad_glDepthRange
	typedef void (APIENTRYP PFNGLVIEWPORTPROC)(gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLVIEWPORTPROC glad_glViewport;
#define glViewport glad_glViewport
#endif
#ifndef GL_VERSION_1_1
#define GL_VERSION_1_1 1
	GLAPI int GLAD_GL_VERSION_1_1;
	typedef void (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum mode, gloomy::I32 first, gloomy::Size count);
	GLAPI PFNGLDRAWARRAYSPROC glad_glDrawArrays;
#define glDrawArrays glad_glDrawArrays
	typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC)(GLenum mode, gloomy::Size count, GLenum type, const void* indices);
	GLAPI PFNGLDRAWELEMENTSPROC glad_glDrawElements;
#define glDrawElements glad_glDrawElements
	typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC)(gloomy::Float factor, gloomy::Float units);
	GLAPI PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset;
#define glPolygonOffset glad_glPolygonOffset
	typedef void (APIENTRYP PFNGLCOPYTEXIMAGE1DPROC)(GLenum target, gloomy::I32 level, GLenum internalformat, gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::I32 border);
	GLAPI PFNGLCOPYTEXIMAGE1DPROC glad_glCopyTexImage1D;
#define glCopyTexImage1D glad_glCopyTexImage1D
	typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, gloomy::I32 level, GLenum internalformat, gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height, gloomy::I32 border);
	GLAPI PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D;
#define glCopyTexImage2D glad_glCopyTexImage2D
	typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 x, gloomy::I32 y, gloomy::Size width);
	GLAPI PFNGLCOPYTEXSUBIMAGE1DPROC glad_glCopyTexSubImage1D;
#define glCopyTexSubImage1D glad_glCopyTexSubImage1D
	typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D;
#define glCopyTexSubImage2D glad_glCopyTexSubImage2D
	typedef void (APIENTRYP PFNGLTEXSUBIMAGE1DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 xoffset, gloomy::Size width, GLenum format, GLenum type, const void* pixels);
	GLAPI PFNGLTEXSUBIMAGE1DPROC glad_glTexSubImage1D;
#define glTexSubImage1D glad_glTexSubImage1D
	typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::Size width, gloomy::Size height, GLenum format, GLenum type, const void* pixels);
	GLAPI PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D;
#define glTexSubImage2D glad_glTexSubImage2D
	typedef void (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum target, gloomy::U32 texture);
	GLAPI PFNGLBINDTEXTUREPROC glad_glBindTexture;
#define glBindTexture glad_glBindTexture
	typedef void (APIENTRYP PFNGLDELETETEXTURESPROC)(gloomy::Size n, const gloomy::U32* textures);
	GLAPI PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
#define glDeleteTextures glad_glDeleteTextures
	typedef void (APIENTRYP PFNGLGENTEXTURESPROC)(gloomy::Size n, gloomy::U32* textures);
	GLAPI PFNGLGENTEXTURESPROC glad_glGenTextures;
#define glGenTextures glad_glGenTextures
	typedef gloomy::Bool(APIENTRYP PFNGLISTEXTUREPROC)(gloomy::U32 texture);
	GLAPI PFNGLISTEXTUREPROC glad_glIsTexture;
#define glIsTexture glad_glIsTexture
#endif
#ifndef GL_VERSION_1_2
#define GL_VERSION_1_2 1
	GLAPI int GLAD_GL_VERSION_1_2;
	typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, gloomy::U32 start, gloomy::U32 end, gloomy::Size count, GLenum type, const void* indices);
	GLAPI PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements;
#define glDrawRangeElements glad_glDrawRangeElements
	typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 internalformat, gloomy::Size width, gloomy::Size height, gloomy::Size depth, gloomy::I32 border, GLenum format, GLenum type, const void* pixels);
	GLAPI PFNGLTEXIMAGE3DPROC glad_glTexImage3D;
#define glTexImage3D glad_glTexImage3D
	typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::Size width, gloomy::Size height, gloomy::Size depth, GLenum format, GLenum type, const void* pixels);
	GLAPI PFNGLTEXSUBIMAGE3DPROC glad_glTexSubImage3D;
#define glTexSubImage3D glad_glTexSubImage3D
	typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLCOPYTEXSUBIMAGE3DPROC glad_glCopyTexSubImage3D;
#define glCopyTexSubImage3D glad_glCopyTexSubImage3D
#endif
#ifndef GL_VERSION_1_3
#define GL_VERSION_1_3 1
	GLAPI int GLAD_GL_VERSION_1_3;
	typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);
	GLAPI PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
#define glActiveTexture glad_glActiveTexture
	typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC)(gloomy::Float value, gloomy::Bool invert);
	GLAPI PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage;
#define glSampleCoverage glad_glSampleCoverage
	typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, gloomy::I32 level, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::Size depth, gloomy::I32 border, gloomy::Size imageSize, const void* data);
	GLAPI PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D;
#define glCompressedTexImage3D glad_glCompressedTexImage3D
	typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, gloomy::I32 level, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::I32 border, gloomy::Size imageSize, const void* data);
	GLAPI PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D;
#define glCompressedTexImage2D glad_glCompressedTexImage2D
	typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, gloomy::I32 level, GLenum internalformat, gloomy::Size width, gloomy::I32 border, gloomy::Size imageSize, const void* data);
	GLAPI PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_glCompressedTexImage1D;
#define glCompressedTexImage1D glad_glCompressedTexImage1D
	typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::Size width, gloomy::Size height, gloomy::Size depth, GLenum format, gloomy::Size imageSize, const void* data);
	GLAPI PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_glCompressedTexSubImage3D;
#define glCompressedTexSubImage3D glad_glCompressedTexSubImage3D
	typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::Size width, gloomy::Size height, GLenum format, gloomy::Size imageSize, const void* data);
	GLAPI PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D;
#define glCompressedTexSubImage2D glad_glCompressedTexSubImage2D
	typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, gloomy::I32 level, gloomy::I32 xoffset, gloomy::Size width, GLenum format, gloomy::Size imageSize, const void* data);
	GLAPI PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glad_glCompressedTexSubImage1D;
#define glCompressedTexSubImage1D glad_glCompressedTexSubImage1D
	typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, gloomy::I32 level, void* img);
	GLAPI PFNGLGETCOMPRESSEDTEXIMAGEPROC glad_glGetCompressedTexImage;
#define glGetCompressedTexImage glad_glGetCompressedTexImage
#endif
#ifndef GL_VERSION_1_4
#define GL_VERSION_1_4 1
	GLAPI int GLAD_GL_VERSION_1_4;
	typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
	GLAPI PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate;
#define glBlendFuncSeparate glad_glBlendFuncSeparate
	typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const gloomy::I32* first, const gloomy::Size* count, gloomy::Size drawcount);
	GLAPI PFNGLMULTIDRAWARRAYSPROC glad_glMultiDrawArrays;
#define glMultiDrawArrays glad_glMultiDrawArrays
	typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const gloomy::Size* count, GLenum type, const void* const* indices, gloomy::Size drawcount);
	GLAPI PFNGLMULTIDRAWELEMENTSPROC glad_glMultiDrawElements;
#define glMultiDrawElements glad_glMultiDrawElements
	typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC)(GLenum pname, gloomy::Float param);
	GLAPI PFNGLPOINTPARAMETERFPROC glad_glPointParameterf;
#define glPointParameterf glad_glPointParameterf
	typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const gloomy::Float* params);
	GLAPI PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv;
#define glPointParameterfv glad_glPointParameterfv
	typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC)(GLenum pname, gloomy::I32 param);
	GLAPI PFNGLPOINTPARAMETERIPROC glad_glPointParameteri;
#define glPointParameteri glad_glPointParameteri
	typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const gloomy::I32* params);
	GLAPI PFNGLPOINTPARAMETERIVPROC glad_glPointParameteriv;
#define glPointParameteriv glad_glPointParameteriv
	typedef void (APIENTRYP PFNGLBLENDCOLORPROC)(gloomy::Float red, gloomy::Float green, gloomy::Float blue, gloomy::Float alpha);
	GLAPI PFNGLBLENDCOLORPROC glad_glBlendColor;
#define glBlendColor glad_glBlendColor
	typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC)(GLenum mode);
	GLAPI PFNGLBLENDEQUATIONPROC glad_glBlendEquation;
#define glBlendEquation glad_glBlendEquation
#endif
#ifndef GL_VERSION_1_5
#define GL_VERSION_1_5 1
	GLAPI int GLAD_GL_VERSION_1_5;
	typedef void (APIENTRYP PFNGLGENQUERIESPROC)(gloomy::Size n, gloomy::U32* ids);
	GLAPI PFNGLGENQUERIESPROC glad_glGenQueries;
#define glGenQueries glad_glGenQueries
	typedef void (APIENTRYP PFNGLDELETEQUERIESPROC)(gloomy::Size n, const gloomy::U32* ids);
	GLAPI PFNGLDELETEQUERIESPROC glad_glDeleteQueries;
#define glDeleteQueries glad_glDeleteQueries
	typedef gloomy::Bool(APIENTRYP PFNGLISQUERYPROC)(gloomy::U32 id);
	GLAPI PFNGLISQUERYPROC glad_glIsQuery;
#define glIsQuery glad_glIsQuery
	typedef void (APIENTRYP PFNGLBEGINQUERYPROC)(GLenum target, gloomy::U32 id);
	GLAPI PFNGLBEGINQUERYPROC glad_glBeginQuery;
#define glBeginQuery glad_glBeginQuery
	typedef void (APIENTRYP PFNGLENDQUERYPROC)(GLenum target);
	GLAPI PFNGLENDQUERYPROC glad_glEndQuery;
#define glEndQuery glad_glEndQuery
	typedef void (APIENTRYP PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETQUERYIVPROC glad_glGetQueryiv;
#define glGetQueryiv glad_glGetQueryiv
	typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC)(gloomy::U32 id, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETQUERYOBJECTIVPROC glad_glGetQueryObjectiv;
#define glGetQueryObjectiv glad_glGetQueryObjectiv
	typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC)(gloomy::U32 id, GLenum pname, gloomy::U32* params);
	GLAPI PFNGLGETQUERYOBJECTUIVPROC glad_glGetQueryObjectuiv;
#define glGetQueryObjectuiv glad_glGetQueryObjectuiv
	typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, gloomy::U32 buffer);
	GLAPI PFNGLBINDBUFFERPROC glad_glBindBuffer;
#define glBindBuffer glad_glBindBuffer
	typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(gloomy::Size n, const gloomy::U32* buffers);
	GLAPI PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
#define glDeleteBuffers glad_glDeleteBuffers
	typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(gloomy::Size n, gloomy::U32* buffers);
	GLAPI PFNGLGENBUFFERSPROC glad_glGenBuffers;
#define glGenBuffers glad_glGenBuffers
	typedef gloomy::Bool(APIENTRYP PFNGLISBUFFERPROC)(gloomy::U32 buffer);
	GLAPI PFNGLISBUFFERPROC glad_glIsBuffer;
#define glIsBuffer glad_glIsBuffer
	typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, gloomy::Sizeptr size, const void* data, GLenum usage);
	GLAPI PFNGLBUFFERDATAPROC glad_glBufferData;
#define glBufferData glad_glBufferData
	typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC)(GLenum target, gloomy::I32ptr offset, gloomy::Sizeptr size, const void* data);
	GLAPI PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;
#define glBufferSubData glad_glBufferSubData
	typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC)(GLenum target, gloomy::I32ptr offset, gloomy::Sizeptr size, void* data);
	GLAPI PFNGLGETBUFFERSUBDATAPROC glad_glGetBufferSubData;
#define glGetBufferSubData glad_glGetBufferSubData
	typedef void* (APIENTRYP PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
	GLAPI PFNGLMAPBUFFERPROC glad_glMapBuffer;
#define glMapBuffer glad_glMapBuffer
	typedef gloomy::Bool(APIENTRYP PFNGLUNMAPBUFFERPROC)(GLenum target);
	GLAPI PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer;
#define glUnmapBuffer glad_glUnmapBuffer
	typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv;
#define glGetBufferParameteriv glad_glGetBufferParameteriv
	typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, void** params);
	GLAPI PFNGLGETBUFFERPOINTERVPROC glad_glGetBufferPointerv;
#define glGetBufferPointerv glad_glGetBufferPointerv
#endif
#ifndef GL_VERSION_2_0
#define GL_VERSION_2_0 1
	GLAPI int GLAD_GL_VERSION_2_0;
	typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
	GLAPI PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate;
#define glBlendEquationSeparate glad_glBlendEquationSeparate
	typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC)(gloomy::Size n, const GLenum* bufs);
	GLAPI PFNGLDRAWBUFFERSPROC glad_glDrawBuffers;
#define glDrawBuffers glad_glDrawBuffers
	typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
	GLAPI PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate;
#define glStencilOpSeparate glad_glStencilOpSeparate
	typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, gloomy::I32 ref, gloomy::U32 mask);
	GLAPI PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate;
#define glStencilFuncSeparate glad_glStencilFuncSeparate
	typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, gloomy::U32 mask);
	GLAPI PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate;
#define glStencilMaskSeparate glad_glStencilMaskSeparate
	typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(gloomy::U32 program, gloomy::U32 shader);
	GLAPI PFNGLATTACHSHADERPROC glad_glAttachShader;
#define glAttachShader glad_glAttachShader
	typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC)(gloomy::U32 program, gloomy::U32 index, const GLchar* name);
	GLAPI PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation;
#define glBindAttribLocation glad_glBindAttribLocation
	typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(gloomy::U32 shader);
	GLAPI PFNGLCOMPILESHADERPROC glad_glCompileShader;
#define glCompileShader glad_glCompileShader
	typedef gloomy::U32(APIENTRYP PFNGLCREATEPROGRAMPROC)(void);
	GLAPI PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
#define glCreateProgram glad_glCreateProgram
	typedef gloomy::U32(APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
	GLAPI PFNGLCREATESHADERPROC glad_glCreateShader;
#define glCreateShader glad_glCreateShader
	typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC)(gloomy::U32 program);
	GLAPI PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
#define glDeleteProgram glad_glDeleteProgram
	typedef void (APIENTRYP PFNGLDELETESHADERPROC)(gloomy::U32 shader);
	GLAPI PFNGLDELETESHADERPROC glad_glDeleteShader;
#define glDeleteShader glad_glDeleteShader
	typedef void (APIENTRYP PFNGLDETACHSHADERPROC)(gloomy::U32 program, gloomy::U32 shader);
	GLAPI PFNGLDETACHSHADERPROC glad_glDetachShader;
#define glDetachShader glad_glDetachShader
	typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC)(gloomy::U32 index);
	GLAPI PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;
#define glDisableVertexAttribArray glad_glDisableVertexAttribArray
	typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(gloomy::U32 index);
	GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
#define glEnableVertexAttribArray glad_glEnableVertexAttribArray
	typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC)(gloomy::U32 program, gloomy::U32 index, gloomy::Size bufSize, gloomy::Size* length, gloomy::I32* size, GLenum* type, GLchar* name);
	GLAPI PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib;
#define glGetActiveAttrib glad_glGetActiveAttrib
	typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC)(gloomy::U32 program, gloomy::U32 index, gloomy::Size bufSize, gloomy::Size* length, gloomy::I32* size, GLenum* type, GLchar* name);
	GLAPI PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform;
#define glGetActiveUniform glad_glGetActiveUniform
	typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC)(gloomy::U32 program, gloomy::Size maxCount, gloomy::Size* count, gloomy::U32* shaders);
	GLAPI PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders;
#define glGetAttachedShaders glad_glGetAttachedShaders
	typedef gloomy::I32(APIENTRYP PFNGLGETATTRIBLOCATIONPROC)(gloomy::U32 program, const GLchar* name);
	GLAPI PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation;
#define glGetAttribLocation glad_glGetAttribLocation
	typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(gloomy::U32 program, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
#define glGetProgramiv glad_glGetProgramiv
	typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(gloomy::U32 program, gloomy::Size bufSize, gloomy::Size* length, GLchar* infoLog);
	GLAPI PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
#define glGetProgramInfoLog glad_glGetProgramInfoLog
	typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(gloomy::U32 shader, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETSHADERIVPROC glad_glGetShaderiv;
#define glGetShaderiv glad_glGetShaderiv
	typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(gloomy::U32 shader, gloomy::Size bufSize, gloomy::Size* length, GLchar* infoLog);
	GLAPI PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
#define glGetShaderInfoLog glad_glGetShaderInfoLog
	typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC)(gloomy::U32 shader, gloomy::Size bufSize, gloomy::Size* length, GLchar* source);
	GLAPI PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource;
#define glGetShaderSource glad_glGetShaderSource
	typedef gloomy::I32(APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(gloomy::U32 program, const GLchar* name);
	GLAPI PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
#define glGetUniformLocation glad_glGetUniformLocation
	typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Float* params);
	GLAPI PFNGLGETUNIFORMFVPROC glad_glGetUniformfv;
#define glGetUniformfv glad_glGetUniformfv
	typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::I32* params);
	GLAPI PFNGLGETUNIFORMIVPROC glad_glGetUniformiv;
#define glGetUniformiv glad_glGetUniformiv
	typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC)(gloomy::U32 index, GLenum pname, GLdouble* params);
	GLAPI PFNGLGETVERTEXATTRIBDVPROC glad_glGetVertexAttribdv;
#define glGetVertexAttribdv glad_glGetVertexAttribdv
	typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC)(gloomy::U32 index, GLenum pname, gloomy::Float* params);
	GLAPI PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv;
#define glGetVertexAttribfv glad_glGetVertexAttribfv
	typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC)(gloomy::U32 index, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv;
#define glGetVertexAttribiv glad_glGetVertexAttribiv
	typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC)(gloomy::U32 index, GLenum pname, void** pointer);
	GLAPI PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv;
#define glGetVertexAttribPointerv glad_glGetVertexAttribPointerv
	typedef gloomy::Bool(APIENTRYP PFNGLISPROGRAMPROC)(gloomy::U32 program);
	GLAPI PFNGLISPROGRAMPROC glad_glIsProgram;
#define glIsProgram glad_glIsProgram
	typedef gloomy::Bool(APIENTRYP PFNGLISSHADERPROC)(gloomy::U32 shader);
	GLAPI PFNGLISSHADERPROC glad_glIsShader;
#define glIsShader glad_glIsShader
	typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(gloomy::U32 program);
	GLAPI PFNGLLINKPROGRAMPROC glad_glLinkProgram;
#define glLinkProgram glad_glLinkProgram
	typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(gloomy::U32 shader, gloomy::Size count, const GLchar* const* string, const gloomy::I32* length);
	GLAPI PFNGLSHADERSOURCEPROC glad_glShaderSource;
#define glShaderSource glad_glShaderSource
	typedef void (APIENTRYP PFNGLUSEPROGRAMPROC)(gloomy::U32 program);
	GLAPI PFNGLUSEPROGRAMPROC glad_glUseProgram;
#define glUseProgram glad_glUseProgram
	typedef void (APIENTRYP PFNGLUNIFORM1FPROC)(gloomy::I32 location, gloomy::Float v0);
	GLAPI PFNGLUNIFORM1FPROC glad_glUniform1f;
#define glUniform1f glad_glUniform1f
	typedef void (APIENTRYP PFNGLUNIFORM2FPROC)(gloomy::I32 location, gloomy::Float v0, gloomy::Float v1);
	GLAPI PFNGLUNIFORM2FPROC glad_glUniform2f;
#define glUniform2f glad_glUniform2f
	typedef void (APIENTRYP PFNGLUNIFORM3FPROC)(gloomy::I32 location, gloomy::Float v0, gloomy::Float v1, gloomy::Float v2);
	GLAPI PFNGLUNIFORM3FPROC glad_glUniform3f;
#define glUniform3f glad_glUniform3f
	typedef void (APIENTRYP PFNGLUNIFORM4FPROC)(gloomy::I32 location, gloomy::Float v0, gloomy::Float v1, gloomy::Float v2, gloomy::Float v3);
	GLAPI PFNGLUNIFORM4FPROC glad_glUniform4f;
#define glUniform4f glad_glUniform4f
	typedef void (APIENTRYP PFNGLUNIFORM1IPROC)(gloomy::I32 location, gloomy::I32 v0);
	GLAPI PFNGLUNIFORM1IPROC glad_glUniform1i;
#define glUniform1i glad_glUniform1i
	typedef void (APIENTRYP PFNGLUNIFORM2IPROC)(gloomy::I32 location, gloomy::I32 v0, gloomy::I32 v1);
	GLAPI PFNGLUNIFORM2IPROC glad_glUniform2i;
#define glUniform2i glad_glUniform2i
	typedef void (APIENTRYP PFNGLUNIFORM3IPROC)(gloomy::I32 location, gloomy::I32 v0, gloomy::I32 v1, gloomy::I32 v2);
	GLAPI PFNGLUNIFORM3IPROC glad_glUniform3i;
#define glUniform3i glad_glUniform3i
	typedef void (APIENTRYP PFNGLUNIFORM4IPROC)(gloomy::I32 location, gloomy::I32 v0, gloomy::I32 v1, gloomy::I32 v2, gloomy::I32 v3);
	GLAPI PFNGLUNIFORM4IPROC glad_glUniform4i;
#define glUniform4i glad_glUniform4i
	typedef void (APIENTRYP PFNGLUNIFORM1FVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::Float* value);
	GLAPI PFNGLUNIFORM1FVPROC glad_glUniform1fv;
#define glUniform1fv glad_glUniform1fv
	typedef void (APIENTRYP PFNGLUNIFORM2FVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::Float* value);
	GLAPI PFNGLUNIFORM2FVPROC glad_glUniform2fv;
#define glUniform2fv glad_glUniform2fv
	typedef void (APIENTRYP PFNGLUNIFORM3FVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::Float* value);
	GLAPI PFNGLUNIFORM3FVPROC glad_glUniform3fv;
#define glUniform3fv glad_glUniform3fv
	typedef void (APIENTRYP PFNGLUNIFORM4FVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::Float* value);
	GLAPI PFNGLUNIFORM4FVPROC glad_glUniform4fv;
#define glUniform4fv glad_glUniform4fv
	typedef void (APIENTRYP PFNGLUNIFORM1IVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::I32* value);
	GLAPI PFNGLUNIFORM1IVPROC glad_glUniform1iv;
#define glUniform1iv glad_glUniform1iv
	typedef void (APIENTRYP PFNGLUNIFORM2IVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::I32* value);
	GLAPI PFNGLUNIFORM2IVPROC glad_glUniform2iv;
#define glUniform2iv glad_glUniform2iv
	typedef void (APIENTRYP PFNGLUNIFORM3IVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::I32* value);
	GLAPI PFNGLUNIFORM3IVPROC glad_glUniform3iv;
#define glUniform3iv glad_glUniform3iv
	typedef void (APIENTRYP PFNGLUNIFORM4IVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::I32* value);
	GLAPI PFNGLUNIFORM4IVPROC glad_glUniform4iv;
#define glUniform4iv glad_glUniform4iv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv;
#define glUniformMatrix2fv glad_glUniformMatrix2fv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv;
#define glUniformMatrix3fv glad_glUniformMatrix3fv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
#define glUniformMatrix4fv glad_glUniformMatrix4fv
	typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC)(gloomy::U32 program);
	GLAPI PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram;
#define glValidateProgram glad_glValidateProgram
	typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC)(gloomy::U32 index, GLdouble x);
	GLAPI PFNGLVERTEXATTRIB1DPROC glad_glVertexAttrib1d;
#define glVertexAttrib1d glad_glVertexAttrib1d
	typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC)(gloomy::U32 index, const GLdouble* v);
	GLAPI PFNGLVERTEXATTRIB1DVPROC glad_glVertexAttrib1dv;
#define glVertexAttrib1dv glad_glVertexAttrib1dv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC)(gloomy::U32 index, gloomy::Float x);
	GLAPI PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f;
#define glVertexAttrib1f glad_glVertexAttrib1f
	typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC)(gloomy::U32 index, const gloomy::Float* v);
	GLAPI PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv;
#define glVertexAttrib1fv glad_glVertexAttrib1fv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC)(gloomy::U32 index, GLshort x);
	GLAPI PFNGLVERTEXATTRIB1SPROC glad_glVertexAttrib1s;
#define glVertexAttrib1s glad_glVertexAttrib1s
	typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC)(gloomy::U32 index, const GLshort* v);
	GLAPI PFNGLVERTEXATTRIB1SVPROC glad_glVertexAttrib1sv;
#define glVertexAttrib1sv glad_glVertexAttrib1sv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC)(gloomy::U32 index, GLdouble x, GLdouble y);
	GLAPI PFNGLVERTEXATTRIB2DPROC glad_glVertexAttrib2d;
#define glVertexAttrib2d glad_glVertexAttrib2d
	typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC)(gloomy::U32 index, const GLdouble* v);
	GLAPI PFNGLVERTEXATTRIB2DVPROC glad_glVertexAttrib2dv;
#define glVertexAttrib2dv glad_glVertexAttrib2dv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC)(gloomy::U32 index, gloomy::Float x, gloomy::Float y);
	GLAPI PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f;
#define glVertexAttrib2f glad_glVertexAttrib2f
	typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC)(gloomy::U32 index, const gloomy::Float* v);
	GLAPI PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv;
#define glVertexAttrib2fv glad_glVertexAttrib2fv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC)(gloomy::U32 index, GLshort x, GLshort y);
	GLAPI PFNGLVERTEXATTRIB2SPROC glad_glVertexAttrib2s;
#define glVertexAttrib2s glad_glVertexAttrib2s
	typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC)(gloomy::U32 index, const GLshort* v);
	GLAPI PFNGLVERTEXATTRIB2SVPROC glad_glVertexAttrib2sv;
#define glVertexAttrib2sv glad_glVertexAttrib2sv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC)(gloomy::U32 index, GLdouble x, GLdouble y, GLdouble z);
	GLAPI PFNGLVERTEXATTRIB3DPROC glad_glVertexAttrib3d;
#define glVertexAttrib3d glad_glVertexAttrib3d
	typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC)(gloomy::U32 index, const GLdouble* v);
	GLAPI PFNGLVERTEXATTRIB3DVPROC glad_glVertexAttrib3dv;
#define glVertexAttrib3dv glad_glVertexAttrib3dv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC)(gloomy::U32 index, gloomy::Float x, gloomy::Float y, gloomy::Float z);
	GLAPI PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f;
#define glVertexAttrib3f glad_glVertexAttrib3f
	typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC)(gloomy::U32 index, const gloomy::Float* v);
	GLAPI PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv;
#define glVertexAttrib3fv glad_glVertexAttrib3fv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC)(gloomy::U32 index, GLshort x, GLshort y, GLshort z);
	GLAPI PFNGLVERTEXATTRIB3SPROC glad_glVertexAttrib3s;
#define glVertexAttrib3s glad_glVertexAttrib3s
	typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC)(gloomy::U32 index, const GLshort* v);
	GLAPI PFNGLVERTEXATTRIB3SVPROC glad_glVertexAttrib3sv;
#define glVertexAttrib3sv glad_glVertexAttrib3sv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC)(gloomy::U32 index, const GLbyte* v);
	GLAPI PFNGLVERTEXATTRIB4NBVPROC glad_glVertexAttrib4Nbv;
#define glVertexAttrib4Nbv glad_glVertexAttrib4Nbv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC)(gloomy::U32 index, const gloomy::I32* v);
	GLAPI PFNGLVERTEXATTRIB4NIVPROC glad_glVertexAttrib4Niv;
#define glVertexAttrib4Niv glad_glVertexAttrib4Niv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC)(gloomy::U32 index, const GLshort* v);
	GLAPI PFNGLVERTEXATTRIB4NSVPROC glad_glVertexAttrib4Nsv;
#define glVertexAttrib4Nsv glad_glVertexAttrib4Nsv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC)(gloomy::U32 index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
	GLAPI PFNGLVERTEXATTRIB4NUBPROC glad_glVertexAttrib4Nub;
#define glVertexAttrib4Nub glad_glVertexAttrib4Nub
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC)(gloomy::U32 index, const GLubyte* v);
	GLAPI PFNGLVERTEXATTRIB4NUBVPROC glad_glVertexAttrib4Nubv;
#define glVertexAttrib4Nubv glad_glVertexAttrib4Nubv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC)(gloomy::U32 index, const gloomy::U32* v);
	GLAPI PFNGLVERTEXATTRIB4NUIVPROC glad_glVertexAttrib4Nuiv;
#define glVertexAttrib4Nuiv glad_glVertexAttrib4Nuiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC)(gloomy::U32 index, const GLushort* v);
	GLAPI PFNGLVERTEXATTRIB4NUSVPROC glad_glVertexAttrib4Nusv;
#define glVertexAttrib4Nusv glad_glVertexAttrib4Nusv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC)(gloomy::U32 index, const GLbyte* v);
	GLAPI PFNGLVERTEXATTRIB4BVPROC glad_glVertexAttrib4bv;
#define glVertexAttrib4bv glad_glVertexAttrib4bv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC)(gloomy::U32 index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	GLAPI PFNGLVERTEXATTRIB4DPROC glad_glVertexAttrib4d;
#define glVertexAttrib4d glad_glVertexAttrib4d
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC)(gloomy::U32 index, const GLdouble* v);
	GLAPI PFNGLVERTEXATTRIB4DVPROC glad_glVertexAttrib4dv;
#define glVertexAttrib4dv glad_glVertexAttrib4dv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC)(gloomy::U32 index, gloomy::Float x, gloomy::Float y, gloomy::Float z, gloomy::Float w);
	GLAPI PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f;
#define glVertexAttrib4f glad_glVertexAttrib4f
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC)(gloomy::U32 index, const gloomy::Float* v);
	GLAPI PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv;
#define glVertexAttrib4fv glad_glVertexAttrib4fv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC)(gloomy::U32 index, const gloomy::I32* v);
	GLAPI PFNGLVERTEXATTRIB4IVPROC glad_glVertexAttrib4iv;
#define glVertexAttrib4iv glad_glVertexAttrib4iv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC)(gloomy::U32 index, GLshort x, GLshort y, GLshort z, GLshort w);
	GLAPI PFNGLVERTEXATTRIB4SPROC glad_glVertexAttrib4s;
#define glVertexAttrib4s glad_glVertexAttrib4s
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC)(gloomy::U32 index, const GLshort* v);
	GLAPI PFNGLVERTEXATTRIB4SVPROC glad_glVertexAttrib4sv;
#define glVertexAttrib4sv glad_glVertexAttrib4sv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC)(gloomy::U32 index, const GLubyte* v);
	GLAPI PFNGLVERTEXATTRIB4UBVPROC glad_glVertexAttrib4ubv;
#define glVertexAttrib4ubv glad_glVertexAttrib4ubv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC)(gloomy::U32 index, const gloomy::U32* v);
	GLAPI PFNGLVERTEXATTRIB4UIVPROC glad_glVertexAttrib4uiv;
#define glVertexAttrib4uiv glad_glVertexAttrib4uiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC)(gloomy::U32 index, const GLushort* v);
	GLAPI PFNGLVERTEXATTRIB4USVPROC glad_glVertexAttrib4usv;
#define glVertexAttrib4usv glad_glVertexAttrib4usv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(gloomy::U32 index, gloomy::I32 size, GLenum type, gloomy::Bool normalized, gloomy::Size stride, const void* pointer);
	GLAPI PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
#define glVertexAttribPointer glad_glVertexAttribPointer
#endif
#ifndef GL_VERSION_2_1
#define GL_VERSION_2_1 1
	GLAPI int GLAD_GL_VERSION_2_1;
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLUNIFORMMATRIX2X3FVPROC glad_glUniformMatrix2x3fv;
#define glUniformMatrix2x3fv glad_glUniformMatrix2x3fv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLUNIFORMMATRIX3X2FVPROC glad_glUniformMatrix3x2fv;
#define glUniformMatrix3x2fv glad_glUniformMatrix3x2fv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLUNIFORMMATRIX2X4FVPROC glad_glUniformMatrix2x4fv;
#define glUniformMatrix2x4fv glad_glUniformMatrix2x4fv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLUNIFORMMATRIX4X2FVPROC glad_glUniformMatrix4x2fv;
#define glUniformMatrix4x2fv glad_glUniformMatrix4x2fv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLUNIFORMMATRIX3X4FVPROC glad_glUniformMatrix3x4fv;
#define glUniformMatrix3x4fv glad_glUniformMatrix3x4fv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLUNIFORMMATRIX4X3FVPROC glad_glUniformMatrix4x3fv;
#define glUniformMatrix4x3fv glad_glUniformMatrix4x3fv
#endif
#ifndef GL_VERSION_3_0
#define GL_VERSION_3_0 1
	GLAPI int GLAD_GL_VERSION_3_0;
	typedef void (APIENTRYP PFNGLCOLORMASKIPROC)(gloomy::U32 index, gloomy::Bool r, gloomy::Bool g, gloomy::Bool b, gloomy::Bool a);
	GLAPI PFNGLCOLORMASKIPROC glad_glColorMaski;
#define glColorMaski glad_glColorMaski
	typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC)(GLenum target, gloomy::U32 index, gloomy::Bool* data);
	GLAPI PFNGLGETBOOLEANI_VPROC glad_glGetBooleani_v;
#define glGetBooleani_v glad_glGetBooleani_v
	typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC)(GLenum target, gloomy::U32 index, gloomy::I32* data);
	GLAPI PFNGLGETINTEGERI_VPROC glad_glGetIntegeri_v;
#define glGetIntegeri_v glad_glGetIntegeri_v
	typedef void (APIENTRYP PFNGLENABLEIPROC)(GLenum target, gloomy::U32 index);
	GLAPI PFNGLENABLEIPROC glad_glEnablei;
#define glEnablei glad_glEnablei
	typedef void (APIENTRYP PFNGLDISABLEIPROC)(GLenum target, gloomy::U32 index);
	GLAPI PFNGLDISABLEIPROC glad_glDisablei;
#define glDisablei glad_glDisablei
	typedef gloomy::Bool(APIENTRYP PFNGLISENABLEDIPROC)(GLenum target, gloomy::U32 index);
	GLAPI PFNGLISENABLEDIPROC glad_glIsEnabledi;
#define glIsEnabledi glad_glIsEnabledi
	typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
	GLAPI PFNGLBEGINTRANSFORMFEEDBACKPROC glad_glBeginTransformFeedback;
#define glBeginTransformFeedback glad_glBeginTransformFeedback
	typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC)(void);
	GLAPI PFNGLENDTRANSFORMFEEDBACKPROC glad_glEndTransformFeedback;
#define glEndTransformFeedback glad_glEndTransformFeedback
	typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC)(GLenum target, gloomy::U32 index, gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Sizeptr size);
	GLAPI PFNGLBINDBUFFERRANGEPROC glad_glBindBufferRange;
#define glBindBufferRange glad_glBindBufferRange
	typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC)(GLenum target, gloomy::U32 index, gloomy::U32 buffer);
	GLAPI PFNGLBINDBUFFERBASEPROC glad_glBindBufferBase;
#define glBindBufferBase glad_glBindBufferBase
	typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(gloomy::U32 program, gloomy::Size count, const GLchar* const* varyings, GLenum bufferMode);
	GLAPI PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_glTransformFeedbackVaryings;
#define glTransformFeedbackVaryings glad_glTransformFeedbackVaryings
	typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(gloomy::U32 program, gloomy::U32 index, gloomy::Size bufSize, gloomy::Size* length, gloomy::Size* size, GLenum* type, GLchar* name);
	GLAPI PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_glGetTransformFeedbackVarying;
#define glGetTransformFeedbackVarying glad_glGetTransformFeedbackVarying
	typedef void (APIENTRYP PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
	GLAPI PFNGLCLAMPCOLORPROC glad_glClampColor;
#define glClampColor glad_glClampColor
	typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC)(gloomy::U32 id, GLenum mode);
	GLAPI PFNGLBEGINCONDITIONALRENDERPROC glad_glBeginConditionalRender;
#define glBeginConditionalRender glad_glBeginConditionalRender
	typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERPROC)(void);
	GLAPI PFNGLENDCONDITIONALRENDERPROC glad_glEndConditionalRender;
#define glEndConditionalRender glad_glEndConditionalRender
	typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC)(gloomy::U32 index, gloomy::I32 size, GLenum type, gloomy::Size stride, const void* pointer);
	GLAPI PFNGLVERTEXATTRIBIPOINTERPROC glad_glVertexAttribIPointer;
#define glVertexAttribIPointer glad_glVertexAttribIPointer
	typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC)(gloomy::U32 index, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETVERTEXATTRIBIIVPROC glad_glGetVertexAttribIiv;
#define glGetVertexAttribIiv glad_glGetVertexAttribIiv
	typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC)(gloomy::U32 index, GLenum pname, gloomy::U32* params);
	GLAPI PFNGLGETVERTEXATTRIBIUIVPROC glad_glGetVertexAttribIuiv;
#define glGetVertexAttribIuiv glad_glGetVertexAttribIuiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IPROC)(gloomy::U32 index, gloomy::I32 x);
	GLAPI PFNGLVERTEXATTRIBI1IPROC glad_glVertexAttribI1i;
#define glVertexAttribI1i glad_glVertexAttribI1i
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IPROC)(gloomy::U32 index, gloomy::I32 x, gloomy::I32 y);
	GLAPI PFNGLVERTEXATTRIBI2IPROC glad_glVertexAttribI2i;
#define glVertexAttribI2i glad_glVertexAttribI2i
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IPROC)(gloomy::U32 index, gloomy::I32 x, gloomy::I32 y, gloomy::I32 z);
	GLAPI PFNGLVERTEXATTRIBI3IPROC glad_glVertexAttribI3i;
#define glVertexAttribI3i glad_glVertexAttribI3i
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC)(gloomy::U32 index, gloomy::I32 x, gloomy::I32 y, gloomy::I32 z, gloomy::I32 w);
	GLAPI PFNGLVERTEXATTRIBI4IPROC glad_glVertexAttribI4i;
#define glVertexAttribI4i glad_glVertexAttribI4i
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIPROC)(gloomy::U32 index, gloomy::U32 x);
	GLAPI PFNGLVERTEXATTRIBI1UIPROC glad_glVertexAttribI1ui;
#define glVertexAttribI1ui glad_glVertexAttribI1ui
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIPROC)(gloomy::U32 index, gloomy::U32 x, gloomy::U32 y);
	GLAPI PFNGLVERTEXATTRIBI2UIPROC glad_glVertexAttribI2ui;
#define glVertexAttribI2ui glad_glVertexAttribI2ui
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIPROC)(gloomy::U32 index, gloomy::U32 x, gloomy::U32 y, gloomy::U32 z);
	GLAPI PFNGLVERTEXATTRIBI3UIPROC glad_glVertexAttribI3ui;
#define glVertexAttribI3ui glad_glVertexAttribI3ui
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC)(gloomy::U32 index, gloomy::U32 x, gloomy::U32 y, gloomy::U32 z, gloomy::U32 w);
	GLAPI PFNGLVERTEXATTRIBI4UIPROC glad_glVertexAttribI4ui;
#define glVertexAttribI4ui glad_glVertexAttribI4ui
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IVPROC)(gloomy::U32 index, const gloomy::I32* v);
	GLAPI PFNGLVERTEXATTRIBI1IVPROC glad_glVertexAttribI1iv;
#define glVertexAttribI1iv glad_glVertexAttribI1iv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IVPROC)(gloomy::U32 index, const gloomy::I32* v);
	GLAPI PFNGLVERTEXATTRIBI2IVPROC glad_glVertexAttribI2iv;
#define glVertexAttribI2iv glad_glVertexAttribI2iv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IVPROC)(gloomy::U32 index, const gloomy::I32* v);
	GLAPI PFNGLVERTEXATTRIBI3IVPROC glad_glVertexAttribI3iv;
#define glVertexAttribI3iv glad_glVertexAttribI3iv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC)(gloomy::U32 index, const gloomy::I32* v);
	GLAPI PFNGLVERTEXATTRIBI4IVPROC glad_glVertexAttribI4iv;
#define glVertexAttribI4iv glad_glVertexAttribI4iv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC)(gloomy::U32 index, const gloomy::U32* v);
	GLAPI PFNGLVERTEXATTRIBI1UIVPROC glad_glVertexAttribI1uiv;
#define glVertexAttribI1uiv glad_glVertexAttribI1uiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC)(gloomy::U32 index, const gloomy::U32* v);
	GLAPI PFNGLVERTEXATTRIBI2UIVPROC glad_glVertexAttribI2uiv;
#define glVertexAttribI2uiv glad_glVertexAttribI2uiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC)(gloomy::U32 index, const gloomy::U32* v);
	GLAPI PFNGLVERTEXATTRIBI3UIVPROC glad_glVertexAttribI3uiv;
#define glVertexAttribI3uiv glad_glVertexAttribI3uiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC)(gloomy::U32 index, const gloomy::U32* v);
	GLAPI PFNGLVERTEXATTRIBI4UIVPROC glad_glVertexAttribI4uiv;
#define glVertexAttribI4uiv glad_glVertexAttribI4uiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI4BVPROC)(gloomy::U32 index, const GLbyte* v);
	GLAPI PFNGLVERTEXATTRIBI4BVPROC glad_glVertexAttribI4bv;
#define glVertexAttribI4bv glad_glVertexAttribI4bv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI4SVPROC)(gloomy::U32 index, const GLshort* v);
	GLAPI PFNGLVERTEXATTRIBI4SVPROC glad_glVertexAttribI4sv;
#define glVertexAttribI4sv glad_glVertexAttribI4sv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC)(gloomy::U32 index, const GLubyte* v);
	GLAPI PFNGLVERTEXATTRIBI4UBVPROC glad_glVertexAttribI4ubv;
#define glVertexAttribI4ubv glad_glVertexAttribI4ubv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBI4USVPROC)(gloomy::U32 index, const GLushort* v);
	GLAPI PFNGLVERTEXATTRIBI4USVPROC glad_glVertexAttribI4usv;
#define glVertexAttribI4usv glad_glVertexAttribI4usv
	typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::U32* params);
	GLAPI PFNGLGETUNIFORMUIVPROC glad_glGetUniformuiv;
#define glGetUniformuiv glad_glGetUniformuiv
	typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC)(gloomy::U32 program, gloomy::U32 color, const GLchar* name);
	GLAPI PFNGLBINDFRAGDATALOCATIONPROC glad_glBindFragDataLocation;
#define glBindFragDataLocation glad_glBindFragDataLocation
	typedef gloomy::I32(APIENTRYP PFNGLGETFRAGDATALOCATIONPROC)(gloomy::U32 program, const GLchar* name);
	GLAPI PFNGLGETFRAGDATALOCATIONPROC glad_glGetFragDataLocation;
#define glGetFragDataLocation glad_glGetFragDataLocation
	typedef void (APIENTRYP PFNGLUNIFORM1UIPROC)(gloomy::I32 location, gloomy::U32 v0);
	GLAPI PFNGLUNIFORM1UIPROC glad_glUniform1ui;
#define glUniform1ui glad_glUniform1ui
	typedef void (APIENTRYP PFNGLUNIFORM2UIPROC)(gloomy::I32 location, gloomy::U32 v0, gloomy::U32 v1);
	GLAPI PFNGLUNIFORM2UIPROC glad_glUniform2ui;
#define glUniform2ui glad_glUniform2ui
	typedef void (APIENTRYP PFNGLUNIFORM3UIPROC)(gloomy::I32 location, gloomy::U32 v0, gloomy::U32 v1, gloomy::U32 v2);
	GLAPI PFNGLUNIFORM3UIPROC glad_glUniform3ui;
#define glUniform3ui glad_glUniform3ui
	typedef void (APIENTRYP PFNGLUNIFORM4UIPROC)(gloomy::I32 location, gloomy::U32 v0, gloomy::U32 v1, gloomy::U32 v2, gloomy::U32 v3);
	GLAPI PFNGLUNIFORM4UIPROC glad_glUniform4ui;
#define glUniform4ui glad_glUniform4ui
	typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::U32* value);
	GLAPI PFNGLUNIFORM1UIVPROC glad_glUniform1uiv;
#define glUniform1uiv glad_glUniform1uiv
	typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::U32* value);
	GLAPI PFNGLUNIFORM2UIVPROC glad_glUniform2uiv;
#define glUniform2uiv glad_glUniform2uiv
	typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::U32* value);
	GLAPI PFNGLUNIFORM3UIVPROC glad_glUniform3uiv;
#define glUniform3uiv glad_glUniform3uiv
	typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC)(gloomy::I32 location, gloomy::Size count, const gloomy::U32* value);
	GLAPI PFNGLUNIFORM4UIVPROC glad_glUniform4uiv;
#define glUniform4uiv glad_glUniform4uiv
	typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const gloomy::I32* params);
	GLAPI PFNGLTEXPARAMETERIIVPROC glad_glTexParameterIiv;
#define glTexParameterIiv glad_glTexParameterIiv
	typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const gloomy::U32* params);
	GLAPI PFNGLTEXPARAMETERIUIVPROC glad_glTexParameterIuiv;
#define glTexParameterIuiv glad_glTexParameterIuiv
	typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETTEXPARAMETERIIVPROC glad_glGetTexParameterIiv;
#define glGetTexParameterIiv glad_glGetTexParameterIiv
	typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, gloomy::U32* params);
	GLAPI PFNGLGETTEXPARAMETERIUIVPROC glad_glGetTexParameterIuiv;
#define glGetTexParameterIuiv glad_glGetTexParameterIuiv
	typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC)(GLenum buffer, gloomy::I32 drawbuffer, const gloomy::I32* value);
	GLAPI PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv;
#define glClearBufferiv glad_glClearBufferiv
	typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, gloomy::I32 drawbuffer, const gloomy::U32* value);
	GLAPI PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv;
#define glClearBufferuiv glad_glClearBufferuiv
	typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC)(GLenum buffer, gloomy::I32 drawbuffer, const gloomy::Float* value);
	GLAPI PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv;
#define glClearBufferfv glad_glClearBufferfv
	typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC)(GLenum buffer, gloomy::I32 drawbuffer, gloomy::Float depth, gloomy::I32 stencil);
	GLAPI PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi;
#define glClearBufferfi glad_glClearBufferfi
	typedef const GLubyte* (APIENTRYP PFNGLGETSTRINGIPROC)(GLenum name, gloomy::U32 index);
	GLAPI PFNGLGETSTRINGIPROC glad_glGetStringi;
#define glGetStringi glad_glGetStringi
	typedef gloomy::Bool(APIENTRYP PFNGLISRENDERBUFFERPROC)(gloomy::U32 renderbuffer);
	GLAPI PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer;
#define glIsRenderbuffer glad_glIsRenderbuffer
	typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC)(GLenum target, gloomy::U32 renderbuffer);
	GLAPI PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer;
#define glBindRenderbuffer glad_glBindRenderbuffer
	typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC)(gloomy::Size n, const gloomy::U32* renderbuffers);
	GLAPI PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers;
#define glDeleteRenderbuffers glad_glDeleteRenderbuffers
	typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC)(gloomy::Size n, gloomy::U32* renderbuffers);
	GLAPI PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers;
#define glGenRenderbuffers glad_glGenRenderbuffers
	typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage;
#define glRenderbufferStorage glad_glRenderbufferStorage
	typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv;
#define glGetRenderbufferParameteriv glad_glGetRenderbufferParameteriv
	typedef gloomy::Bool(APIENTRYP PFNGLISFRAMEBUFFERPROC)(gloomy::U32 framebuffer);
	GLAPI PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer;
#define glIsFramebuffer glad_glIsFramebuffer
	typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC)(GLenum target, gloomy::U32 framebuffer);
	GLAPI PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer;
#define glBindFramebuffer glad_glBindFramebuffer
	typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC)(gloomy::Size n, const gloomy::U32* framebuffers);
	GLAPI PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers;
#define glDeleteFramebuffers glad_glDeleteFramebuffers
	typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC)(gloomy::Size n, gloomy::U32* framebuffers);
	GLAPI PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers;
#define glGenFramebuffers glad_glGenFramebuffers
	typedef GLenum(APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
	GLAPI PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus;
#define glCheckFramebufferStatus glad_glCheckFramebufferStatus
	typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum target, GLenum attachment, GLenum textarget, gloomy::U32 texture, gloomy::I32 level);
	GLAPI PFNGLFRAMEBUFFERTEXTURE1DPROC glad_glFramebufferTexture1D;
#define glFramebufferTexture1D glad_glFramebufferTexture1D
	typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, gloomy::U32 texture, gloomy::I32 level);
	GLAPI PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D;
#define glFramebufferTexture2D glad_glFramebufferTexture2D
	typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum target, GLenum attachment, GLenum textarget, gloomy::U32 texture, gloomy::I32 level, gloomy::I32 zoffset);
	GLAPI PFNGLFRAMEBUFFERTEXTURE3DPROC glad_glFramebufferTexture3D;
#define glFramebufferTexture3D glad_glFramebufferTexture3D
	typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, gloomy::U32 renderbuffer);
	GLAPI PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer;
#define glFramebufferRenderbuffer glad_glFramebufferRenderbuffer
	typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv;
#define glGetFramebufferAttachmentParameteriv glad_glGetFramebufferAttachmentParameteriv
	typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC)(GLenum target);
	GLAPI PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;
#define glGenerateMipmap glad_glGenerateMipmap
	typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC)(gloomy::I32 srcX0, gloomy::I32 srcY0, gloomy::I32 srcX1, gloomy::I32 srcY1, gloomy::I32 dstX0, gloomy::I32 dstY0, gloomy::I32 dstX1, gloomy::I32 dstY1, GLbitfield mask, GLenum filter);
	GLAPI PFNGLBLITFRAMEBUFFERPROC glad_glBlitFramebuffer;
#define glBlitFramebuffer glad_glBlitFramebuffer
	typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum target, gloomy::Size samples, GLenum internalformat, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glRenderbufferStorageMultisample;
#define glRenderbufferStorageMultisample glad_glRenderbufferStorageMultisample
	typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum target, GLenum attachment, gloomy::U32 texture, gloomy::I32 level, gloomy::I32 layer);
	GLAPI PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_glFramebufferTextureLayer;
#define glFramebufferTextureLayer glad_glFramebufferTextureLayer
	typedef void* (APIENTRYP PFNGLMAPBUFFERRANGEPROC)(GLenum target, gloomy::I32ptr offset, gloomy::Sizeptr length, GLbitfield access);
	GLAPI PFNGLMAPBUFFERRANGEPROC glad_glMapBufferRange;
#define glMapBufferRange glad_glMapBufferRange
	typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, gloomy::I32ptr offset, gloomy::Sizeptr length);
	GLAPI PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_glFlushMappedBufferRange;
#define glFlushMappedBufferRange glad_glFlushMappedBufferRange
	typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(gloomy::U32 array);
	GLAPI PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
#define glBindVertexArray glad_glBindVertexArray
	typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(gloomy::Size n, const gloomy::U32* arrays);
	GLAPI PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
#define glDeleteVertexArrays glad_glDeleteVertexArrays
	typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(gloomy::Size n, gloomy::U32* arrays);
	GLAPI PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
#define glGenVertexArrays glad_glGenVertexArrays
	typedef gloomy::Bool(APIENTRYP PFNGLISVERTEXARRAYPROC)(gloomy::U32 array);
	GLAPI PFNGLISVERTEXARRAYPROC glad_glIsVertexArray;
#define glIsVertexArray glad_glIsVertexArray
#endif
#ifndef GL_VERSION_3_1
#define GL_VERSION_3_1 1
	GLAPI int GLAD_GL_VERSION_3_1;
	typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, gloomy::I32 first, gloomy::Size count, gloomy::Size instancecount);
	GLAPI PFNGLDRAWARRAYSINSTANCEDPROC glad_glDrawArraysInstanced;
#define glDrawArraysInstanced glad_glDrawArraysInstanced
	typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, gloomy::Size count, GLenum type, const void* indices, gloomy::Size instancecount);
	GLAPI PFNGLDRAWELEMENTSINSTANCEDPROC glad_glDrawElementsInstanced;
#define glDrawElementsInstanced glad_glDrawElementsInstanced
	typedef void (APIENTRYP PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, gloomy::U32 buffer);
	GLAPI PFNGLTEXBUFFERPROC glad_glTexBuffer;
#define glTexBuffer glad_glTexBuffer
	typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC)(gloomy::U32 index);
	GLAPI PFNGLPRIMITIVERESTARTINDEXPROC glad_glPrimitiveRestartIndex;
#define glPrimitiveRestartIndex glad_glPrimitiveRestartIndex
	typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, gloomy::I32ptr readOffset, gloomy::I32ptr writeOffset, gloomy::Sizeptr size);
	GLAPI PFNGLCOPYBUFFERSUBDATAPROC glad_glCopyBufferSubData;
#define glCopyBufferSubData glad_glCopyBufferSubData
	typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC)(gloomy::U32 program, gloomy::Size uniformCount, const GLchar* const* uniformNames, gloomy::U32* uniformIndices);
	GLAPI PFNGLGETUNIFORMINDICESPROC glad_glGetUniformIndices;
#define glGetUniformIndices glad_glGetUniformIndices
	typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC)(gloomy::U32 program, gloomy::Size uniformCount, const gloomy::U32* uniformIndices, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETACTIVEUNIFORMSIVPROC glad_glGetActiveUniformsiv;
#define glGetActiveUniformsiv glad_glGetActiveUniformsiv
	typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC)(gloomy::U32 program, gloomy::U32 uniformIndex, gloomy::Size bufSize, gloomy::Size* length, GLchar* uniformName);
	GLAPI PFNGLGETACTIVEUNIFORMNAMEPROC glad_glGetActiveUniformName;
#define glGetActiveUniformName glad_glGetActiveUniformName
	typedef gloomy::U32(APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC)(gloomy::U32 program, const GLchar* uniformBlockName);
	GLAPI PFNGLGETUNIFORMBLOCKINDEXPROC glad_glGetUniformBlockIndex;
#define glGetUniformBlockIndex glad_glGetUniformBlockIndex
	typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(gloomy::U32 program, gloomy::U32 uniformBlockIndex, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETACTIVEUNIFORMBLOCKIVPROC glad_glGetActiveUniformBlockiv;
#define glGetActiveUniformBlockiv glad_glGetActiveUniformBlockiv
	typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(gloomy::U32 program, gloomy::U32 uniformBlockIndex, gloomy::Size bufSize, gloomy::Size* length, GLchar* uniformBlockName);
	GLAPI PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glad_glGetActiveUniformBlockName;
#define glGetActiveUniformBlockName glad_glGetActiveUniformBlockName
	typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC)(gloomy::U32 program, gloomy::U32 uniformBlockIndex, gloomy::U32 uniformBlockBinding);
	GLAPI PFNGLUNIFORMBLOCKBINDINGPROC glad_glUniformBlockBinding;
#define glUniformBlockBinding glad_glUniformBlockBinding
#endif
#ifndef GL_VERSION_3_2
#define GL_VERSION_3_2 1
	GLAPI int GLAD_GL_VERSION_3_2;
	typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, gloomy::Size count, GLenum type, const void* indices, gloomy::I32 basevertex);
	GLAPI PFNGLDRAWELEMENTSBASEVERTEXPROC glad_glDrawElementsBaseVertex;
#define glDrawElementsBaseVertex glad_glDrawElementsBaseVertex
	typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, gloomy::U32 start, gloomy::U32 end, gloomy::Size count, GLenum type, const void* indices, gloomy::I32 basevertex);
	GLAPI PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glad_glDrawRangeElementsBaseVertex;
#define glDrawRangeElementsBaseVertex glad_glDrawRangeElementsBaseVertex
	typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, gloomy::Size count, GLenum type, const void* indices, gloomy::Size instancecount, gloomy::I32 basevertex);
	GLAPI PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glad_glDrawElementsInstancedBaseVertex;
#define glDrawElementsInstancedBaseVertex glad_glDrawElementsInstancedBaseVertex
	typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const gloomy::Size* count, GLenum type, const void* const* indices, gloomy::Size drawcount, const gloomy::I32* basevertex);
	GLAPI PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glad_glMultiDrawElementsBaseVertex;
#define glMultiDrawElementsBaseVertex glad_glMultiDrawElementsBaseVertex
	typedef void (APIENTRYP PFNGLPROVOKINGVERTEXPROC)(GLenum mode);
	GLAPI PFNGLPROVOKINGVERTEXPROC glad_glProvokingVertex;
#define glProvokingVertex glad_glProvokingVertex
	typedef GLsync(APIENTRYP PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
	GLAPI PFNGLFENCESYNCPROC glad_glFenceSync;
#define glFenceSync glad_glFenceSync
	typedef gloomy::Bool(APIENTRYP PFNGLISSYNCPROC)(GLsync sync);
	GLAPI PFNGLISSYNCPROC glad_glIsSync;
#define glIsSync glad_glIsSync
	typedef void (APIENTRYP PFNGLDELETESYNCPROC)(GLsync sync);
	GLAPI PFNGLDELETESYNCPROC glad_glDeleteSync;
#define glDeleteSync glad_glDeleteSync
	typedef GLenum(APIENTRYP PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, gloomy::U3264 timeout);
	GLAPI PFNGLCLIENTWAITSYNCPROC glad_glClientWaitSync;
#define glClientWaitSync glad_glClientWaitSync
	typedef void (APIENTRYP PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, gloomy::U3264 timeout);
	GLAPI PFNGLWAITSYNCPROC glad_glWaitSync;
#define glWaitSync glad_glWaitSync
	typedef void (APIENTRYP PFNGLGETINTEGER64VPROC)(GLenum pname, gloomy::I3264* data);
	GLAPI PFNGLGETINTEGER64VPROC glad_glGetInteger64v;
#define glGetInteger64v glad_glGetInteger64v
	typedef void (APIENTRYP PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, gloomy::Size count, gloomy::Size* length, gloomy::I32* values);
	GLAPI PFNGLGETSYNCIVPROC glad_glGetSynciv;
#define glGetSynciv glad_glGetSynciv
	typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC)(GLenum target, gloomy::U32 index, gloomy::I3264* data);
	GLAPI PFNGLGETINTEGER64I_VPROC glad_glGetInteger64i_v;
#define glGetInteger64i_v glad_glGetInteger64i_v
	typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, gloomy::I3264* params);
	GLAPI PFNGLGETBUFFERPARAMETERI64VPROC glad_glGetBufferParameteri64v;
#define glGetBufferParameteri64v glad_glGetBufferParameteri64v
	typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, gloomy::U32 texture, gloomy::I32 level);
	GLAPI PFNGLFRAMEBUFFERTEXTUREPROC glad_glFramebufferTexture;
#define glFramebufferTexture glad_glFramebufferTexture
	typedef void (APIENTRYP PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, gloomy::Size samples, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::Bool fixedsamplelocations);
	GLAPI PFNGLTEXIMAGE2DMULTISAMPLEPROC glad_glTexImage2DMultisample;
#define glTexImage2DMultisample glad_glTexImage2DMultisample
	typedef void (APIENTRYP PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, gloomy::Size samples, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::Size depth, gloomy::Bool fixedsamplelocations);
	GLAPI PFNGLTEXIMAGE3DMULTISAMPLEPROC glad_glTexImage3DMultisample;
#define glTexImage3DMultisample glad_glTexImage3DMultisample
	typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, gloomy::U32 index, gloomy::Float* val);
	GLAPI PFNGLGETMULTISAMPLEFVPROC glad_glGetMultisamplefv;
#define glGetMultisamplefv glad_glGetMultisamplefv
	typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC)(gloomy::U32 maskNumber, GLbitfield mask);
	GLAPI PFNGLSAMPLEMASKIPROC glad_glSampleMaski;
#define glSampleMaski glad_glSampleMaski
#endif
#ifndef GL_VERSION_3_3
#define GL_VERSION_3_3 1
	GLAPI int GLAD_GL_VERSION_3_3;
	typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(gloomy::U32 program, gloomy::U32 colorNumber, gloomy::U32 index, const GLchar* name);
	GLAPI PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glad_glBindFragDataLocationIndexed;
#define glBindFragDataLocationIndexed glad_glBindFragDataLocationIndexed
	typedef gloomy::I32(APIENTRYP PFNGLGETFRAGDATAINDEXPROC)(gloomy::U32 program, const GLchar* name);
	GLAPI PFNGLGETFRAGDATAINDEXPROC glad_glGetFragDataIndex;
#define glGetFragDataIndex glad_glGetFragDataIndex
	typedef void (APIENTRYP PFNGLGENSAMPLERSPROC)(gloomy::Size count, gloomy::U32* samplers);
	GLAPI PFNGLGENSAMPLERSPROC glad_glGenSamplers;
#define glGenSamplers glad_glGenSamplers
	typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC)(gloomy::Size count, const gloomy::U32* samplers);
	GLAPI PFNGLDELETESAMPLERSPROC glad_glDeleteSamplers;
#define glDeleteSamplers glad_glDeleteSamplers
	typedef gloomy::Bool(APIENTRYP PFNGLISSAMPLERPROC)(gloomy::U32 sampler);
	GLAPI PFNGLISSAMPLERPROC glad_glIsSampler;
#define glIsSampler glad_glIsSampler
	typedef void (APIENTRYP PFNGLBINDSAMPLERPROC)(gloomy::U32 unit, gloomy::U32 sampler);
	GLAPI PFNGLBINDSAMPLERPROC glad_glBindSampler;
#define glBindSampler glad_glBindSampler
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC)(gloomy::U32 sampler, GLenum pname, gloomy::I32 param);
	GLAPI PFNGLSAMPLERPARAMETERIPROC glad_glSamplerParameteri;
#define glSamplerParameteri glad_glSamplerParameteri
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC)(gloomy::U32 sampler, GLenum pname, const gloomy::I32* param);
	GLAPI PFNGLSAMPLERPARAMETERIVPROC glad_glSamplerParameteriv;
#define glSamplerParameteriv glad_glSamplerParameteriv
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC)(gloomy::U32 sampler, GLenum pname, gloomy::Float param);
	GLAPI PFNGLSAMPLERPARAMETERFPROC glad_glSamplerParameterf;
#define glSamplerParameterf glad_glSamplerParameterf
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC)(gloomy::U32 sampler, GLenum pname, const gloomy::Float* param);
	GLAPI PFNGLSAMPLERPARAMETERFVPROC glad_glSamplerParameterfv;
#define glSamplerParameterfv glad_glSamplerParameterfv
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC)(gloomy::U32 sampler, GLenum pname, const gloomy::I32* param);
	GLAPI PFNGLSAMPLERPARAMETERIIVPROC glad_glSamplerParameterIiv;
#define glSamplerParameterIiv glad_glSamplerParameterIiv
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC)(gloomy::U32 sampler, GLenum pname, const gloomy::U32* param);
	GLAPI PFNGLSAMPLERPARAMETERIUIVPROC glad_glSamplerParameterIuiv;
#define glSamplerParameterIuiv glad_glSamplerParameterIuiv
	typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC)(gloomy::U32 sampler, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETSAMPLERPARAMETERIVPROC glad_glGetSamplerParameteriv;
#define glGetSamplerParameteriv glad_glGetSamplerParameteriv
	typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC)(gloomy::U32 sampler, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETSAMPLERPARAMETERIIVPROC glad_glGetSamplerParameterIiv;
#define glGetSamplerParameterIiv glad_glGetSamplerParameterIiv
	typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC)(gloomy::U32 sampler, GLenum pname, gloomy::Float* params);
	GLAPI PFNGLGETSAMPLERPARAMETERFVPROC glad_glGetSamplerParameterfv;
#define glGetSamplerParameterfv glad_glGetSamplerParameterfv
	typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC)(gloomy::U32 sampler, GLenum pname, gloomy::U32* params);
	GLAPI PFNGLGETSAMPLERPARAMETERIUIVPROC glad_glGetSamplerParameterIuiv;
#define glGetSamplerParameterIuiv glad_glGetSamplerParameterIuiv
	typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC)(gloomy::U32 id, GLenum target);
	GLAPI PFNGLQUERYCOUNTERPROC glad_glQueryCounter;
#define glQueryCounter glad_glQueryCounter
	typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC)(gloomy::U32 id, GLenum pname, gloomy::I3264* params);
	GLAPI PFNGLGETQUERYOBJECTI64VPROC glad_glGetQueryObjecti64v;
#define glGetQueryObjecti64v glad_glGetQueryObjecti64v
	typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC)(gloomy::U32 id, GLenum pname, gloomy::U3264* params);
	GLAPI PFNGLGETQUERYOBJECTUI64VPROC glad_glGetQueryObjectui64v;
#define glGetQueryObjectui64v glad_glGetQueryObjectui64v
	typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC)(gloomy::U32 index, gloomy::U32 divisor);
	GLAPI PFNGLVERTEXATTRIBDIVISORPROC glad_glVertexAttribDivisor;
#define glVertexAttribDivisor glad_glVertexAttribDivisor
	typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIPROC)(gloomy::U32 index, GLenum type, gloomy::Bool normalized, gloomy::U32 value);
	GLAPI PFNGLVERTEXATTRIBP1UIPROC glad_glVertexAttribP1ui;
#define glVertexAttribP1ui glad_glVertexAttribP1ui
	typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIVPROC)(gloomy::U32 index, GLenum type, gloomy::Bool normalized, const gloomy::U32* value);
	GLAPI PFNGLVERTEXATTRIBP1UIVPROC glad_glVertexAttribP1uiv;
#define glVertexAttribP1uiv glad_glVertexAttribP1uiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIPROC)(gloomy::U32 index, GLenum type, gloomy::Bool normalized, gloomy::U32 value);
	GLAPI PFNGLVERTEXATTRIBP2UIPROC glad_glVertexAttribP2ui;
#define glVertexAttribP2ui glad_glVertexAttribP2ui
	typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIVPROC)(gloomy::U32 index, GLenum type, gloomy::Bool normalized, const gloomy::U32* value);
	GLAPI PFNGLVERTEXATTRIBP2UIVPROC glad_glVertexAttribP2uiv;
#define glVertexAttribP2uiv glad_glVertexAttribP2uiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIPROC)(gloomy::U32 index, GLenum type, gloomy::Bool normalized, gloomy::U32 value);
	GLAPI PFNGLVERTEXATTRIBP3UIPROC glad_glVertexAttribP3ui;
#define glVertexAttribP3ui glad_glVertexAttribP3ui
	typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIVPROC)(gloomy::U32 index, GLenum type, gloomy::Bool normalized, const gloomy::U32* value);
	GLAPI PFNGLVERTEXATTRIBP3UIVPROC glad_glVertexAttribP3uiv;
#define glVertexAttribP3uiv glad_glVertexAttribP3uiv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIPROC)(gloomy::U32 index, GLenum type, gloomy::Bool normalized, gloomy::U32 value);
	GLAPI PFNGLVERTEXATTRIBP4UIPROC glad_glVertexAttribP4ui;
#define glVertexAttribP4ui glad_glVertexAttribP4ui
	typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIVPROC)(gloomy::U32 index, GLenum type, gloomy::Bool normalized, const gloomy::U32* value);
	GLAPI PFNGLVERTEXATTRIBP4UIVPROC glad_glVertexAttribP4uiv;
#define glVertexAttribP4uiv glad_glVertexAttribP4uiv
	typedef void (APIENTRYP PFNGLVERTEXP2UIPROC)(GLenum type, gloomy::U32 value);
	GLAPI PFNGLVERTEXP2UIPROC glad_glVertexP2ui;
#define glVertexP2ui glad_glVertexP2ui
	typedef void (APIENTRYP PFNGLVERTEXP2UIVPROC)(GLenum type, const gloomy::U32* value);
	GLAPI PFNGLVERTEXP2UIVPROC glad_glVertexP2uiv;
#define glVertexP2uiv glad_glVertexP2uiv
	typedef void (APIENTRYP PFNGLVERTEXP3UIPROC)(GLenum type, gloomy::U32 value);
	GLAPI PFNGLVERTEXP3UIPROC glad_glVertexP3ui;
#define glVertexP3ui glad_glVertexP3ui
	typedef void (APIENTRYP PFNGLVERTEXP3UIVPROC)(GLenum type, const gloomy::U32* value);
	GLAPI PFNGLVERTEXP3UIVPROC glad_glVertexP3uiv;
#define glVertexP3uiv glad_glVertexP3uiv
	typedef void (APIENTRYP PFNGLVERTEXP4UIPROC)(GLenum type, gloomy::U32 value);
	GLAPI PFNGLVERTEXP4UIPROC glad_glVertexP4ui;
#define glVertexP4ui glad_glVertexP4ui
	typedef void (APIENTRYP PFNGLVERTEXP4UIVPROC)(GLenum type, const gloomy::U32* value);
	GLAPI PFNGLVERTEXP4UIVPROC glad_glVertexP4uiv;
#define glVertexP4uiv glad_glVertexP4uiv
	typedef void (APIENTRYP PFNGLTEXCOORDP1UIPROC)(GLenum type, gloomy::U32 coords);
	GLAPI PFNGLTEXCOORDP1UIPROC glad_glTexCoordP1ui;
#define glTexCoordP1ui glad_glTexCoordP1ui
	typedef void (APIENTRYP PFNGLTEXCOORDP1UIVPROC)(GLenum type, const gloomy::U32* coords);
	GLAPI PFNGLTEXCOORDP1UIVPROC glad_glTexCoordP1uiv;
#define glTexCoordP1uiv glad_glTexCoordP1uiv
	typedef void (APIENTRYP PFNGLTEXCOORDP2UIPROC)(GLenum type, gloomy::U32 coords);
	GLAPI PFNGLTEXCOORDP2UIPROC glad_glTexCoordP2ui;
#define glTexCoordP2ui glad_glTexCoordP2ui
	typedef void (APIENTRYP PFNGLTEXCOORDP2UIVPROC)(GLenum type, const gloomy::U32* coords);
	GLAPI PFNGLTEXCOORDP2UIVPROC glad_glTexCoordP2uiv;
#define glTexCoordP2uiv glad_glTexCoordP2uiv
	typedef void (APIENTRYP PFNGLTEXCOORDP3UIPROC)(GLenum type, gloomy::U32 coords);
	GLAPI PFNGLTEXCOORDP3UIPROC glad_glTexCoordP3ui;
#define glTexCoordP3ui glad_glTexCoordP3ui
	typedef void (APIENTRYP PFNGLTEXCOORDP3UIVPROC)(GLenum type, const gloomy::U32* coords);
	GLAPI PFNGLTEXCOORDP3UIVPROC glad_glTexCoordP3uiv;
#define glTexCoordP3uiv glad_glTexCoordP3uiv
	typedef void (APIENTRYP PFNGLTEXCOORDP4UIPROC)(GLenum type, gloomy::U32 coords);
	GLAPI PFNGLTEXCOORDP4UIPROC glad_glTexCoordP4ui;
#define glTexCoordP4ui glad_glTexCoordP4ui
	typedef void (APIENTRYP PFNGLTEXCOORDP4UIVPROC)(GLenum type, const gloomy::U32* coords);
	GLAPI PFNGLTEXCOORDP4UIVPROC glad_glTexCoordP4uiv;
#define glTexCoordP4uiv glad_glTexCoordP4uiv
	typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIPROC)(GLenum texture, GLenum type, gloomy::U32 coords);
	GLAPI PFNGLMULTITEXCOORDP1UIPROC glad_glMultiTexCoordP1ui;
#define glMultiTexCoordP1ui glad_glMultiTexCoordP1ui
	typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIVPROC)(GLenum texture, GLenum type, const gloomy::U32* coords);
	GLAPI PFNGLMULTITEXCOORDP1UIVPROC glad_glMultiTexCoordP1uiv;
#define glMultiTexCoordP1uiv glad_glMultiTexCoordP1uiv
	typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIPROC)(GLenum texture, GLenum type, gloomy::U32 coords);
	GLAPI PFNGLMULTITEXCOORDP2UIPROC glad_glMultiTexCoordP2ui;
#define glMultiTexCoordP2ui glad_glMultiTexCoordP2ui
	typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIVPROC)(GLenum texture, GLenum type, const gloomy::U32* coords);
	GLAPI PFNGLMULTITEXCOORDP2UIVPROC glad_glMultiTexCoordP2uiv;
#define glMultiTexCoordP2uiv glad_glMultiTexCoordP2uiv
	typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIPROC)(GLenum texture, GLenum type, gloomy::U32 coords);
	GLAPI PFNGLMULTITEXCOORDP3UIPROC glad_glMultiTexCoordP3ui;
#define glMultiTexCoordP3ui glad_glMultiTexCoordP3ui
	typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIVPROC)(GLenum texture, GLenum type, const gloomy::U32* coords);
	GLAPI PFNGLMULTITEXCOORDP3UIVPROC glad_glMultiTexCoordP3uiv;
#define glMultiTexCoordP3uiv glad_glMultiTexCoordP3uiv
	typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIPROC)(GLenum texture, GLenum type, gloomy::U32 coords);
	GLAPI PFNGLMULTITEXCOORDP4UIPROC glad_glMultiTexCoordP4ui;
#define glMultiTexCoordP4ui glad_glMultiTexCoordP4ui
	typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIVPROC)(GLenum texture, GLenum type, const gloomy::U32* coords);
	GLAPI PFNGLMULTITEXCOORDP4UIVPROC glad_glMultiTexCoordP4uiv;
#define glMultiTexCoordP4uiv glad_glMultiTexCoordP4uiv
	typedef void (APIENTRYP PFNGLNORMALP3UIPROC)(GLenum type, gloomy::U32 coords);
	GLAPI PFNGLNORMALP3UIPROC glad_glNormalP3ui;
#define glNormalP3ui glad_glNormalP3ui
	typedef void (APIENTRYP PFNGLNORMALP3UIVPROC)(GLenum type, const gloomy::U32* coords);
	GLAPI PFNGLNORMALP3UIVPROC glad_glNormalP3uiv;
#define glNormalP3uiv glad_glNormalP3uiv
	typedef void (APIENTRYP PFNGLCOLORP3UIPROC)(GLenum type, gloomy::U32 color);
	GLAPI PFNGLCOLORP3UIPROC glad_glColorP3ui;
#define glColorP3ui glad_glColorP3ui
	typedef void (APIENTRYP PFNGLCOLORP3UIVPROC)(GLenum type, const gloomy::U32* color);
	GLAPI PFNGLCOLORP3UIVPROC glad_glColorP3uiv;
#define glColorP3uiv glad_glColorP3uiv
	typedef void (APIENTRYP PFNGLCOLORP4UIPROC)(GLenum type, gloomy::U32 color);
	GLAPI PFNGLCOLORP4UIPROC glad_glColorP4ui;
#define glColorP4ui glad_glColorP4ui
	typedef void (APIENTRYP PFNGLCOLORP4UIVPROC)(GLenum type, const gloomy::U32* color);
	GLAPI PFNGLCOLORP4UIVPROC glad_glColorP4uiv;
#define glColorP4uiv glad_glColorP4uiv
	typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIPROC)(GLenum type, gloomy::U32 color);
	GLAPI PFNGLSECONDARYCOLORP3UIPROC glad_glSecondaryColorP3ui;
#define glSecondaryColorP3ui glad_glSecondaryColorP3ui
	typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIVPROC)(GLenum type, const gloomy::U32* color);
	GLAPI PFNGLSECONDARYCOLORP3UIVPROC glad_glSecondaryColorP3uiv;
#define glSecondaryColorP3uiv glad_glSecondaryColorP3uiv
#endif
#ifndef GL_VERSION_4_0
#define GL_VERSION_4_0 1
	GLAPI int GLAD_GL_VERSION_4_0;
	typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC)(gloomy::Float value);
	GLAPI PFNGLMINSAMPLESHADINGPROC glad_glMinSampleShading;
#define glMinSampleShading glad_glMinSampleShading
	typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC)(gloomy::U32 buf, GLenum mode);
	GLAPI PFNGLBLENDEQUATIONIPROC glad_glBlendEquationi;
#define glBlendEquationi glad_glBlendEquationi
	typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC)(gloomy::U32 buf, GLenum modeRGB, GLenum modeAlpha);
	GLAPI PFNGLBLENDEQUATIONSEPARATEIPROC glad_glBlendEquationSeparatei;
#define glBlendEquationSeparatei glad_glBlendEquationSeparatei
	typedef void (APIENTRYP PFNGLBLENDFUNCIPROC)(gloomy::U32 buf, GLenum src, GLenum dst);
	GLAPI PFNGLBLENDFUNCIPROC glad_glBlendFunci;
#define glBlendFunci glad_glBlendFunci
	typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC)(gloomy::U32 buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	GLAPI PFNGLBLENDFUNCSEPARATEIPROC glad_glBlendFuncSeparatei;
#define glBlendFuncSeparatei glad_glBlendFuncSeparatei
	typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC)(GLenum mode, const void* indirect);
	GLAPI PFNGLDRAWARRAYSINDIRECTPROC glad_glDrawArraysIndirect;
#define glDrawArraysIndirect glad_glDrawArraysIndirect
	typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void* indirect);
	GLAPI PFNGLDRAWELEMENTSINDIRECTPROC glad_glDrawElementsIndirect;
#define glDrawElementsIndirect glad_glDrawElementsIndirect
	typedef void (APIENTRYP PFNGLUNIFORM1DPROC)(gloomy::I32 location, GLdouble x);
	GLAPI PFNGLUNIFORM1DPROC glad_glUniform1d;
#define glUniform1d glad_glUniform1d
	typedef void (APIENTRYP PFNGLUNIFORM2DPROC)(gloomy::I32 location, GLdouble x, GLdouble y);
	GLAPI PFNGLUNIFORM2DPROC glad_glUniform2d;
#define glUniform2d glad_glUniform2d
	typedef void (APIENTRYP PFNGLUNIFORM3DPROC)(gloomy::I32 location, GLdouble x, GLdouble y, GLdouble z);
	GLAPI PFNGLUNIFORM3DPROC glad_glUniform3d;
#define glUniform3d glad_glUniform3d
	typedef void (APIENTRYP PFNGLUNIFORM4DPROC)(gloomy::I32 location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	GLAPI PFNGLUNIFORM4DPROC glad_glUniform4d;
#define glUniform4d glad_glUniform4d
	typedef void (APIENTRYP PFNGLUNIFORM1DVPROC)(gloomy::I32 location, gloomy::Size count, const GLdouble* value);
	GLAPI PFNGLUNIFORM1DVPROC glad_glUniform1dv;
#define glUniform1dv glad_glUniform1dv
	typedef void (APIENTRYP PFNGLUNIFORM2DVPROC)(gloomy::I32 location, gloomy::Size count, const GLdouble* value);
	GLAPI PFNGLUNIFORM2DVPROC glad_glUniform2dv;
#define glUniform2dv glad_glUniform2dv
	typedef void (APIENTRYP PFNGLUNIFORM3DVPROC)(gloomy::I32 location, gloomy::Size count, const GLdouble* value);
	GLAPI PFNGLUNIFORM3DVPROC glad_glUniform3dv;
#define glUniform3dv glad_glUniform3dv
	typedef void (APIENTRYP PFNGLUNIFORM4DVPROC)(gloomy::I32 location, gloomy::Size count, const GLdouble* value);
	GLAPI PFNGLUNIFORM4DVPROC glad_glUniform4dv;
#define glUniform4dv glad_glUniform4dv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX2DVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLUNIFORMMATRIX2DVPROC glad_glUniformMatrix2dv;
#define glUniformMatrix2dv glad_glUniformMatrix2dv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX3DVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLUNIFORMMATRIX3DVPROC glad_glUniformMatrix3dv;
#define glUniformMatrix3dv glad_glUniformMatrix3dv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX4DVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLUNIFORMMATRIX4DVPROC glad_glUniformMatrix4dv;
#define glUniformMatrix4dv glad_glUniformMatrix4dv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3DVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLUNIFORMMATRIX2X3DVPROC glad_glUniformMatrix2x3dv;
#define glUniformMatrix2x3dv glad_glUniformMatrix2x3dv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4DVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLUNIFORMMATRIX2X4DVPROC glad_glUniformMatrix2x4dv;
#define glUniformMatrix2x4dv glad_glUniformMatrix2x4dv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2DVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLUNIFORMMATRIX3X2DVPROC glad_glUniformMatrix3x2dv;
#define glUniformMatrix3x2dv glad_glUniformMatrix3x2dv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4DVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLUNIFORMMATRIX3X4DVPROC glad_glUniformMatrix3x4dv;
#define glUniformMatrix3x4dv glad_glUniformMatrix3x4dv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2DVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLUNIFORMMATRIX4X2DVPROC glad_glUniformMatrix4x2dv;
#define glUniformMatrix4x2dv glad_glUniformMatrix4x2dv
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3DVPROC)(gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLUNIFORMMATRIX4X3DVPROC glad_glUniformMatrix4x3dv;
#define glUniformMatrix4x3dv glad_glUniformMatrix4x3dv
	typedef void (APIENTRYP PFNGLGETUNIFORMDVPROC)(gloomy::U32 program, gloomy::I32 location, GLdouble* params);
	GLAPI PFNGLGETUNIFORMDVPROC glad_glGetUniformdv;
#define glGetUniformdv glad_glGetUniformdv
	typedef gloomy::I32(APIENTRYP PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(gloomy::U32 program, GLenum shadertype, const GLchar* name);
	GLAPI PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glad_glGetSubroutineUniformLocation;
#define glGetSubroutineUniformLocation glad_glGetSubroutineUniformLocation
	typedef gloomy::U32(APIENTRYP PFNGLGETSUBROUTINEINDEXPROC)(gloomy::U32 program, GLenum shadertype, const GLchar* name);
	GLAPI PFNGLGETSUBROUTINEINDEXPROC glad_glGetSubroutineIndex;
#define glGetSubroutineIndex glad_glGetSubroutineIndex
	typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(gloomy::U32 program, GLenum shadertype, gloomy::U32 index, GLenum pname, gloomy::I32* values);
	GLAPI PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glad_glGetActiveSubroutineUniformiv;
#define glGetActiveSubroutineUniformiv glad_glGetActiveSubroutineUniformiv
	typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(gloomy::U32 program, GLenum shadertype, gloomy::U32 index, gloomy::Size bufSize, gloomy::Size* length, GLchar* name);
	GLAPI PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glad_glGetActiveSubroutineUniformName;
#define glGetActiveSubroutineUniformName glad_glGetActiveSubroutineUniformName
	typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINENAMEPROC)(gloomy::U32 program, GLenum shadertype, gloomy::U32 index, gloomy::Size bufSize, gloomy::Size* length, GLchar* name);
	GLAPI PFNGLGETACTIVESUBROUTINENAMEPROC glad_glGetActiveSubroutineName;
#define glGetActiveSubroutineName glad_glGetActiveSubroutineName
	typedef void (APIENTRYP PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum shadertype, gloomy::Size count, const gloomy::U32* indices);
	GLAPI PFNGLUNIFORMSUBROUTINESUIVPROC glad_glUniformSubroutinesuiv;
#define glUniformSubroutinesuiv glad_glUniformSubroutinesuiv
	typedef void (APIENTRYP PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum shadertype, gloomy::I32 location, gloomy::U32* params);
	GLAPI PFNGLGETUNIFORMSUBROUTINEUIVPROC glad_glGetUniformSubroutineuiv;
#define glGetUniformSubroutineuiv glad_glGetUniformSubroutineuiv
	typedef void (APIENTRYP PFNGLGETPROGRAMSTAGEIVPROC)(gloomy::U32 program, GLenum shadertype, GLenum pname, gloomy::I32* values);
	GLAPI PFNGLGETPROGRAMSTAGEIVPROC glad_glGetProgramStageiv;
#define glGetProgramStageiv glad_glGetProgramStageiv
	typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC)(GLenum pname, gloomy::I32 value);
	GLAPI PFNGLPATCHPARAMETERIPROC glad_glPatchParameteri;
#define glPatchParameteri glad_glPatchParameteri
	typedef void (APIENTRYP PFNGLPATCHPARAMETERFVPROC)(GLenum pname, const gloomy::Float* values);
	GLAPI PFNGLPATCHPARAMETERFVPROC glad_glPatchParameterfv;
#define glPatchParameterfv glad_glPatchParameterfv
	typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum target, gloomy::U32 id);
	GLAPI PFNGLBINDTRANSFORMFEEDBACKPROC glad_glBindTransformFeedback;
#define glBindTransformFeedback glad_glBindTransformFeedback
	typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC)(gloomy::Size n, const gloomy::U32* ids);
	GLAPI PFNGLDELETETRANSFORMFEEDBACKSPROC glad_glDeleteTransformFeedbacks;
#define glDeleteTransformFeedbacks glad_glDeleteTransformFeedbacks
	typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC)(gloomy::Size n, gloomy::U32* ids);
	GLAPI PFNGLGENTRANSFORMFEEDBACKSPROC glad_glGenTransformFeedbacks;
#define glGenTransformFeedbacks glad_glGenTransformFeedbacks
	typedef gloomy::Bool(APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC)(gloomy::U32 id);
	GLAPI PFNGLISTRANSFORMFEEDBACKPROC glad_glIsTransformFeedback;
#define glIsTransformFeedback glad_glIsTransformFeedback
	typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC)(void);
	GLAPI PFNGLPAUSETRANSFORMFEEDBACKPROC glad_glPauseTransformFeedback;
#define glPauseTransformFeedback glad_glPauseTransformFeedback
	typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC)(void);
	GLAPI PFNGLRESUMETRANSFORMFEEDBACKPROC glad_glResumeTransformFeedback;
#define glResumeTransformFeedback glad_glResumeTransformFeedback
	typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum mode, gloomy::U32 id);
	GLAPI PFNGLDRAWTRANSFORMFEEDBACKPROC glad_glDrawTransformFeedback;
#define glDrawTransformFeedback glad_glDrawTransformFeedback
	typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum mode, gloomy::U32 id, gloomy::U32 stream);
	GLAPI PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glad_glDrawTransformFeedbackStream;
#define glDrawTransformFeedbackStream glad_glDrawTransformFeedbackStream
	typedef void (APIENTRYP PFNGLBEGINQUERYINDEXEDPROC)(GLenum target, gloomy::U32 index, gloomy::U32 id);
	GLAPI PFNGLBEGINQUERYINDEXEDPROC glad_glBeginQueryIndexed;
#define glBeginQueryIndexed glad_glBeginQueryIndexed
	typedef void (APIENTRYP PFNGLENDQUERYINDEXEDPROC)(GLenum target, gloomy::U32 index);
	GLAPI PFNGLENDQUERYINDEXEDPROC glad_glEndQueryIndexed;
#define glEndQueryIndexed glad_glEndQueryIndexed
	typedef void (APIENTRYP PFNGLGETQUERYINDEXEDIVPROC)(GLenum target, gloomy::U32 index, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETQUERYINDEXEDIVPROC glad_glGetQueryIndexediv;
#define glGetQueryIndexediv glad_glGetQueryIndexediv
#endif
#ifndef GL_VERSION_4_1
#define GL_VERSION_4_1 1
	GLAPI int GLAD_GL_VERSION_4_1;
	typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC)(void);
	GLAPI PFNGLRELEASESHADERCOMPILERPROC glad_glReleaseShaderCompiler;
#define glReleaseShaderCompiler glad_glReleaseShaderCompiler
	typedef void (APIENTRYP PFNGLSHADERBINARYPROC)(gloomy::Size count, const gloomy::U32* shaders, GLenum binaryformat, const void* binary, gloomy::Size length);
	GLAPI PFNGLSHADERBINARYPROC glad_glShaderBinary;
#define glShaderBinary glad_glShaderBinary
	typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum shadertype, GLenum precisiontype, gloomy::I32* range, gloomy::I32* precision);
	GLAPI PFNGLGETSHADERPRECISIONFORMATPROC glad_glGetShaderPrecisionFormat;
#define glGetShaderPrecisionFormat glad_glGetShaderPrecisionFormat
	typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC)(gloomy::Float n, gloomy::Float f);
	GLAPI PFNGLDEPTHRANGEFPROC glad_glDepthRangef;
#define glDepthRangef glad_glDepthRangef
	typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC)(gloomy::Float d);
	GLAPI PFNGLCLEARDEPTHFPROC glad_glClearDepthf;
#define glClearDepthf glad_glClearDepthf
	typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC)(gloomy::U32 program, gloomy::Size bufSize, gloomy::Size* length, GLenum* binaryFormat, void* binary);
	GLAPI PFNGLGETPROGRAMBINARYPROC glad_glGetProgramBinary;
#define glGetProgramBinary glad_glGetProgramBinary
	typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC)(gloomy::U32 program, GLenum binaryFormat, const void* binary, gloomy::Size length);
	GLAPI PFNGLPROGRAMBINARYPROC glad_glProgramBinary;
#define glProgramBinary glad_glProgramBinary
	typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC)(gloomy::U32 program, GLenum pname, gloomy::I32 value);
	GLAPI PFNGLPROGRAMPARAMETERIPROC glad_glProgramParameteri;
#define glProgramParameteri glad_glProgramParameteri
	typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC)(gloomy::U32 pipeline, GLbitfield stages, gloomy::U32 program);
	GLAPI PFNGLUSEPROGRAMSTAGESPROC glad_glUseProgramStages;
#define glUseProgramStages glad_glUseProgramStages
	typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC)(gloomy::U32 pipeline, gloomy::U32 program);
	GLAPI PFNGLACTIVESHADERPROGRAMPROC glad_glActiveShaderProgram;
#define glActiveShaderProgram glad_glActiveShaderProgram
	typedef gloomy::U32(APIENTRYP PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, gloomy::Size count, const GLchar* const* strings);
	GLAPI PFNGLCREATESHADERPROGRAMVPROC glad_glCreateShaderProgramv;
#define glCreateShaderProgramv glad_glCreateShaderProgramv
	typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC)(gloomy::U32 pipeline);
	GLAPI PFNGLBINDPROGRAMPIPELINEPROC glad_glBindProgramPipeline;
#define glBindProgramPipeline glad_glBindProgramPipeline
	typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC)(gloomy::Size n, const gloomy::U32* pipelines);
	GLAPI PFNGLDELETEPROGRAMPIPELINESPROC glad_glDeleteProgramPipelines;
#define glDeleteProgramPipelines glad_glDeleteProgramPipelines
	typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC)(gloomy::Size n, gloomy::U32* pipelines);
	GLAPI PFNGLGENPROGRAMPIPELINESPROC glad_glGenProgramPipelines;
#define glGenProgramPipelines glad_glGenProgramPipelines
	typedef gloomy::Bool(APIENTRYP PFNGLISPROGRAMPIPELINEPROC)(gloomy::U32 pipeline);
	GLAPI PFNGLISPROGRAMPIPELINEPROC glad_glIsProgramPipeline;
#define glIsProgramPipeline glad_glIsProgramPipeline
	typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC)(gloomy::U32 pipeline, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETPROGRAMPIPELINEIVPROC glad_glGetProgramPipelineiv;
#define glGetProgramPipelineiv glad_glGetProgramPipelineiv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::I32 v0);
	GLAPI PFNGLPROGRAMUNIFORM1IPROC glad_glProgramUniform1i;
#define glProgramUniform1i glad_glProgramUniform1i
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::I32* value);
	GLAPI PFNGLPROGRAMUNIFORM1IVPROC glad_glProgramUniform1iv;
#define glProgramUniform1iv glad_glProgramUniform1iv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Float v0);
	GLAPI PFNGLPROGRAMUNIFORM1FPROC glad_glProgramUniform1f;
#define glProgramUniform1f glad_glProgramUniform1f
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORM1FVPROC glad_glProgramUniform1fv;
#define glProgramUniform1fv glad_glProgramUniform1fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DPROC)(gloomy::U32 program, gloomy::I32 location, GLdouble v0);
	GLAPI PFNGLPROGRAMUNIFORM1DPROC glad_glProgramUniform1d;
#define glProgramUniform1d glad_glProgramUniform1d
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORM1DVPROC glad_glProgramUniform1dv;
#define glProgramUniform1dv glad_glProgramUniform1dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::U32 v0);
	GLAPI PFNGLPROGRAMUNIFORM1UIPROC glad_glProgramUniform1ui;
#define glProgramUniform1ui glad_glProgramUniform1ui
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::U32* value);
	GLAPI PFNGLPROGRAMUNIFORM1UIVPROC glad_glProgramUniform1uiv;
#define glProgramUniform1uiv glad_glProgramUniform1uiv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::I32 v0, gloomy::I32 v1);
	GLAPI PFNGLPROGRAMUNIFORM2IPROC glad_glProgramUniform2i;
#define glProgramUniform2i glad_glProgramUniform2i
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::I32* value);
	GLAPI PFNGLPROGRAMUNIFORM2IVPROC glad_glProgramUniform2iv;
#define glProgramUniform2iv glad_glProgramUniform2iv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Float v0, gloomy::Float v1);
	GLAPI PFNGLPROGRAMUNIFORM2FPROC glad_glProgramUniform2f;
#define glProgramUniform2f glad_glProgramUniform2f
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORM2FVPROC glad_glProgramUniform2fv;
#define glProgramUniform2fv glad_glProgramUniform2fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DPROC)(gloomy::U32 program, gloomy::I32 location, GLdouble v0, GLdouble v1);
	GLAPI PFNGLPROGRAMUNIFORM2DPROC glad_glProgramUniform2d;
#define glProgramUniform2d glad_glProgramUniform2d
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORM2DVPROC glad_glProgramUniform2dv;
#define glProgramUniform2dv glad_glProgramUniform2dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::U32 v0, gloomy::U32 v1);
	GLAPI PFNGLPROGRAMUNIFORM2UIPROC glad_glProgramUniform2ui;
#define glProgramUniform2ui glad_glProgramUniform2ui
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::U32* value);
	GLAPI PFNGLPROGRAMUNIFORM2UIVPROC glad_glProgramUniform2uiv;
#define glProgramUniform2uiv glad_glProgramUniform2uiv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::I32 v0, gloomy::I32 v1, gloomy::I32 v2);
	GLAPI PFNGLPROGRAMUNIFORM3IPROC glad_glProgramUniform3i;
#define glProgramUniform3i glad_glProgramUniform3i
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::I32* value);
	GLAPI PFNGLPROGRAMUNIFORM3IVPROC glad_glProgramUniform3iv;
#define glProgramUniform3iv glad_glProgramUniform3iv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Float v0, gloomy::Float v1, gloomy::Float v2);
	GLAPI PFNGLPROGRAMUNIFORM3FPROC glad_glProgramUniform3f;
#define glProgramUniform3f glad_glProgramUniform3f
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORM3FVPROC glad_glProgramUniform3fv;
#define glProgramUniform3fv glad_glProgramUniform3fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DPROC)(gloomy::U32 program, gloomy::I32 location, GLdouble v0, GLdouble v1, GLdouble v2);
	GLAPI PFNGLPROGRAMUNIFORM3DPROC glad_glProgramUniform3d;
#define glProgramUniform3d glad_glProgramUniform3d
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORM3DVPROC glad_glProgramUniform3dv;
#define glProgramUniform3dv glad_glProgramUniform3dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::U32 v0, gloomy::U32 v1, gloomy::U32 v2);
	GLAPI PFNGLPROGRAMUNIFORM3UIPROC glad_glProgramUniform3ui;
#define glProgramUniform3ui glad_glProgramUniform3ui
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::U32* value);
	GLAPI PFNGLPROGRAMUNIFORM3UIVPROC glad_glProgramUniform3uiv;
#define glProgramUniform3uiv glad_glProgramUniform3uiv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::I32 v0, gloomy::I32 v1, gloomy::I32 v2, gloomy::I32 v3);
	GLAPI PFNGLPROGRAMUNIFORM4IPROC glad_glProgramUniform4i;
#define glProgramUniform4i glad_glProgramUniform4i
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::I32* value);
	GLAPI PFNGLPROGRAMUNIFORM4IVPROC glad_glProgramUniform4iv;
#define glProgramUniform4iv glad_glProgramUniform4iv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Float v0, gloomy::Float v1, gloomy::Float v2, gloomy::Float v3);
	GLAPI PFNGLPROGRAMUNIFORM4FPROC glad_glProgramUniform4f;
#define glProgramUniform4f glad_glProgramUniform4f
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORM4FVPROC glad_glProgramUniform4fv;
#define glProgramUniform4fv glad_glProgramUniform4fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DPROC)(gloomy::U32 program, gloomy::I32 location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
	GLAPI PFNGLPROGRAMUNIFORM4DPROC glad_glProgramUniform4d;
#define glProgramUniform4d glad_glProgramUniform4d
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORM4DVPROC glad_glProgramUniform4dv;
#define glProgramUniform4dv glad_glProgramUniform4dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::U32 v0, gloomy::U32 v1, gloomy::U32 v2, gloomy::U32 v3);
	GLAPI PFNGLPROGRAMUNIFORM4UIPROC glad_glProgramUniform4ui;
#define glProgramUniform4ui glad_glProgramUniform4ui
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, const gloomy::U32* value);
	GLAPI PFNGLPROGRAMUNIFORM4UIVPROC glad_glProgramUniform4uiv;
#define glProgramUniform4uiv glad_glProgramUniform4uiv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX2FVPROC glad_glProgramUniformMatrix2fv;
#define glProgramUniformMatrix2fv glad_glProgramUniformMatrix2fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX3FVPROC glad_glProgramUniformMatrix3fv;
#define glProgramUniformMatrix3fv glad_glProgramUniformMatrix3fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX4FVPROC glad_glProgramUniformMatrix4fv;
#define glProgramUniformMatrix4fv glad_glProgramUniformMatrix4fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX2DVPROC glad_glProgramUniformMatrix2dv;
#define glProgramUniformMatrix2dv glad_glProgramUniformMatrix2dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX3DVPROC glad_glProgramUniformMatrix3dv;
#define glProgramUniformMatrix3dv glad_glProgramUniformMatrix3dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX4DVPROC glad_glProgramUniformMatrix4dv;
#define glProgramUniformMatrix4dv glad_glProgramUniformMatrix4dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glad_glProgramUniformMatrix2x3fv;
#define glProgramUniformMatrix2x3fv glad_glProgramUniformMatrix2x3fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glad_glProgramUniformMatrix3x2fv;
#define glProgramUniformMatrix3x2fv glad_glProgramUniformMatrix3x2fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glad_glProgramUniformMatrix2x4fv;
#define glProgramUniformMatrix2x4fv glad_glProgramUniformMatrix2x4fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glad_glProgramUniformMatrix4x2fv;
#define glProgramUniformMatrix4x2fv glad_glProgramUniformMatrix4x2fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glad_glProgramUniformMatrix3x4fv;
#define glProgramUniformMatrix3x4fv glad_glProgramUniformMatrix3x4fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const gloomy::Float* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glad_glProgramUniformMatrix4x3fv;
#define glProgramUniformMatrix4x3fv glad_glProgramUniformMatrix4x3fv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glad_glProgramUniformMatrix2x3dv;
#define glProgramUniformMatrix2x3dv glad_glProgramUniformMatrix2x3dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glad_glProgramUniformMatrix3x2dv;
#define glProgramUniformMatrix3x2dv glad_glProgramUniformMatrix3x2dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glad_glProgramUniformMatrix2x4dv;
#define glProgramUniformMatrix2x4dv glad_glProgramUniformMatrix2x4dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glad_glProgramUniformMatrix4x2dv;
#define glProgramUniformMatrix4x2dv glad_glProgramUniformMatrix4x2dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glad_glProgramUniformMatrix3x4dv;
#define glProgramUniformMatrix3x4dv glad_glProgramUniformMatrix3x4dv
	typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size count, gloomy::Bool transpose, const GLdouble* value);
	GLAPI PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glad_glProgramUniformMatrix4x3dv;
#define glProgramUniformMatrix4x3dv glad_glProgramUniformMatrix4x3dv
	typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC)(gloomy::U32 pipeline);
	GLAPI PFNGLVALIDATEPROGRAMPIPELINEPROC glad_glValidateProgramPipeline;
#define glValidateProgramPipeline glad_glValidateProgramPipeline
	typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC)(gloomy::U32 pipeline, gloomy::Size bufSize, gloomy::Size* length, GLchar* infoLog);
	GLAPI PFNGLGETPROGRAMPIPELINEINFOLOGPROC glad_glGetProgramPipelineInfoLog;
#define glGetProgramPipelineInfoLog glad_glGetProgramPipelineInfoLog
	typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DPROC)(gloomy::U32 index, GLdouble x);
	GLAPI PFNGLVERTEXATTRIBL1DPROC glad_glVertexAttribL1d;
#define glVertexAttribL1d glad_glVertexAttribL1d
	typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DPROC)(gloomy::U32 index, GLdouble x, GLdouble y);
	GLAPI PFNGLVERTEXATTRIBL2DPROC glad_glVertexAttribL2d;
#define glVertexAttribL2d glad_glVertexAttribL2d
	typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DPROC)(gloomy::U32 index, GLdouble x, GLdouble y, GLdouble z);
	GLAPI PFNGLVERTEXATTRIBL3DPROC glad_glVertexAttribL3d;
#define glVertexAttribL3d glad_glVertexAttribL3d
	typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DPROC)(gloomy::U32 index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	GLAPI PFNGLVERTEXATTRIBL4DPROC glad_glVertexAttribL4d;
#define glVertexAttribL4d glad_glVertexAttribL4d
	typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DVPROC)(gloomy::U32 index, const GLdouble* v);
	GLAPI PFNGLVERTEXATTRIBL1DVPROC glad_glVertexAttribL1dv;
#define glVertexAttribL1dv glad_glVertexAttribL1dv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DVPROC)(gloomy::U32 index, const GLdouble* v);
	GLAPI PFNGLVERTEXATTRIBL2DVPROC glad_glVertexAttribL2dv;
#define glVertexAttribL2dv glad_glVertexAttribL2dv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DVPROC)(gloomy::U32 index, const GLdouble* v);
	GLAPI PFNGLVERTEXATTRIBL3DVPROC glad_glVertexAttribL3dv;
#define glVertexAttribL3dv glad_glVertexAttribL3dv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DVPROC)(gloomy::U32 index, const GLdouble* v);
	GLAPI PFNGLVERTEXATTRIBL4DVPROC glad_glVertexAttribL4dv;
#define glVertexAttribL4dv glad_glVertexAttribL4dv
	typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC)(gloomy::U32 index, gloomy::I32 size, GLenum type, gloomy::Size stride, const void* pointer);
	GLAPI PFNGLVERTEXATTRIBLPOINTERPROC glad_glVertexAttribLPointer;
#define glVertexAttribLPointer glad_glVertexAttribLPointer
	typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLDVPROC)(gloomy::U32 index, GLenum pname, GLdouble* params);
	GLAPI PFNGLGETVERTEXATTRIBLDVPROC glad_glGetVertexAttribLdv;
#define glGetVertexAttribLdv glad_glGetVertexAttribLdv
	typedef void (APIENTRYP PFNGLVIEWPORTARRAYVPROC)(gloomy::U32 first, gloomy::Size count, const gloomy::Float* v);
	GLAPI PFNGLVIEWPORTARRAYVPROC glad_glViewportArrayv;
#define glViewportArrayv glad_glViewportArrayv
	typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFPROC)(gloomy::U32 index, gloomy::Float x, gloomy::Float y, gloomy::Float w, gloomy::Float h);
	GLAPI PFNGLVIEWPORTINDEXEDFPROC glad_glViewportIndexedf;
#define glViewportIndexedf glad_glViewportIndexedf
	typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFVPROC)(gloomy::U32 index, const gloomy::Float* v);
	GLAPI PFNGLVIEWPORTINDEXEDFVPROC glad_glViewportIndexedfv;
#define glViewportIndexedfv glad_glViewportIndexedfv
	typedef void (APIENTRYP PFNGLSCISSORARRAYVPROC)(gloomy::U32 first, gloomy::Size count, const gloomy::I32* v);
	GLAPI PFNGLSCISSORARRAYVPROC glad_glScissorArrayv;
#define glScissorArrayv glad_glScissorArrayv
	typedef void (APIENTRYP PFNGLSCISSORINDEXEDPROC)(gloomy::U32 index, gloomy::I32 left, gloomy::I32 bottom, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLSCISSORINDEXEDPROC glad_glScissorIndexed;
#define glScissorIndexed glad_glScissorIndexed
	typedef void (APIENTRYP PFNGLSCISSORINDEXEDVPROC)(gloomy::U32 index, const gloomy::I32* v);
	GLAPI PFNGLSCISSORINDEXEDVPROC glad_glScissorIndexedv;
#define glScissorIndexedv glad_glScissorIndexedv
	typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYVPROC)(gloomy::U32 first, gloomy::Size count, const GLdouble* v);
	GLAPI PFNGLDEPTHRANGEARRAYVPROC glad_glDepthRangeArrayv;
#define glDepthRangeArrayv glad_glDepthRangeArrayv
	typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDPROC)(gloomy::U32 index, GLdouble n, GLdouble f);
	GLAPI PFNGLDEPTHRANGEINDEXEDPROC glad_glDepthRangeIndexed;
#define glDepthRangeIndexed glad_glDepthRangeIndexed
	typedef void (APIENTRYP PFNGLGETFLOATI_VPROC)(GLenum target, gloomy::U32 index, gloomy::Float* data);
	GLAPI PFNGLGETFLOATI_VPROC glad_glGetFloati_v;
#define glGetFloati_v glad_glGetFloati_v
	typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC)(GLenum target, gloomy::U32 index, GLdouble* data);
	GLAPI PFNGLGETDOUBLEI_VPROC glad_glGetDoublei_v;
#define glGetDoublei_v glad_glGetDoublei_v
#endif
#ifndef GL_VERSION_4_2
#define GL_VERSION_4_2 1
	GLAPI int GLAD_GL_VERSION_4_2;
	typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)(GLenum mode, gloomy::I32 first, gloomy::Size count, gloomy::Size instancecount, gloomy::U32 baseinstance);
	GLAPI PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glad_glDrawArraysInstancedBaseInstance;
#define glDrawArraysInstancedBaseInstance glad_glDrawArraysInstancedBaseInstance
	typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)(GLenum mode, gloomy::Size count, GLenum type, const void* indices, gloomy::Size instancecount, gloomy::U32 baseinstance);
	GLAPI PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glad_glDrawElementsInstancedBaseInstance;
#define glDrawElementsInstancedBaseInstance glad_glDrawElementsInstancedBaseInstance
	typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)(GLenum mode, gloomy::Size count, GLenum type, const void* indices, gloomy::Size instancecount, gloomy::I32 basevertex, gloomy::U32 baseinstance);
	GLAPI PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glad_glDrawElementsInstancedBaseVertexBaseInstance;
#define glDrawElementsInstancedBaseVertexBaseInstance glad_glDrawElementsInstancedBaseVertexBaseInstance
	typedef void (APIENTRYP PFNGLGETINTERNALFORMATIVPROC)(GLenum target, GLenum internalformat, GLenum pname, gloomy::Size count, gloomy::I32* params);
	GLAPI PFNGLGETINTERNALFORMATIVPROC glad_glGetInternalformativ;
#define glGetInternalformativ glad_glGetInternalformativ
	typedef void (APIENTRYP PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)(gloomy::U32 program, gloomy::U32 bufferIndex, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glad_glGetActiveAtomicCounterBufferiv;
#define glGetActiveAtomicCounterBufferiv glad_glGetActiveAtomicCounterBufferiv
	typedef void (APIENTRYP PFNGLBINDIMAGETEXTUREPROC)(gloomy::U32 unit, gloomy::U32 texture, gloomy::I32 level, gloomy::Bool layered, gloomy::I32 layer, GLenum access, GLenum format);
	GLAPI PFNGLBINDIMAGETEXTUREPROC glad_glBindImageTexture;
#define glBindImageTexture glad_glBindImageTexture
	typedef void (APIENTRYP PFNGLMEMORYBARRIERPROC)(GLbitfield barriers);
	GLAPI PFNGLMEMORYBARRIERPROC glad_glMemoryBarrier;
#define glMemoryBarrier glad_glMemoryBarrier
	typedef void (APIENTRYP PFNGLTEXSTORAGE1DPROC)(GLenum target, gloomy::Size levels, GLenum internalformat, gloomy::Size width);
	GLAPI PFNGLTEXSTORAGE1DPROC glad_glTexStorage1D;
#define glTexStorage1D glad_glTexStorage1D
	typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC)(GLenum target, gloomy::Size levels, GLenum internalformat, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLTEXSTORAGE2DPROC glad_glTexStorage2D;
#define glTexStorage2D glad_glTexStorage2D
	typedef void (APIENTRYP PFNGLTEXSTORAGE3DPROC)(GLenum target, gloomy::Size levels, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::Size depth);
	GLAPI PFNGLTEXSTORAGE3DPROC glad_glTexStorage3D;
#define glTexStorage3D glad_glTexStorage3D
	typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)(GLenum mode, gloomy::U32 id, gloomy::Size instancecount);
	GLAPI PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glad_glDrawTransformFeedbackInstanced;
#define glDrawTransformFeedbackInstanced glad_glDrawTransformFeedbackInstanced
	typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)(GLenum mode, gloomy::U32 id, gloomy::U32 stream, gloomy::Size instancecount);
	GLAPI PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glad_glDrawTransformFeedbackStreamInstanced;
#define glDrawTransformFeedbackStreamInstanced glad_glDrawTransformFeedbackStreamInstanced
#endif
#ifndef GL_VERSION_4_3
#define GL_VERSION_4_3 1
	GLAPI int GLAD_GL_VERSION_4_3;
	typedef void (APIENTRYP PFNGLCLEARBUFFERDATAPROC)(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data);
	GLAPI PFNGLCLEARBUFFERDATAPROC glad_glClearBufferData;
#define glClearBufferData glad_glClearBufferData
	typedef void (APIENTRYP PFNGLCLEARBUFFERSUBDATAPROC)(GLenum target, GLenum internalformat, gloomy::I32ptr offset, gloomy::Sizeptr size, GLenum format, GLenum type, const void* data);
	GLAPI PFNGLCLEARBUFFERSUBDATAPROC glad_glClearBufferSubData;
#define glClearBufferSubData glad_glClearBufferSubData
	typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC)(gloomy::U32 num_groups_x, gloomy::U32 num_groups_y, gloomy::U32 num_groups_z);
	GLAPI PFNGLDISPATCHCOMPUTEPROC glad_glDispatchCompute;
#define glDispatchCompute glad_glDispatchCompute
	typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC)(gloomy::I32ptr indirect);
	GLAPI PFNGLDISPATCHCOMPUTEINDIRECTPROC glad_glDispatchComputeIndirect;
#define glDispatchComputeIndirect glad_glDispatchComputeIndirect
	typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC)(gloomy::U32 srcName, GLenum srcTarget, gloomy::I32 srcLevel, gloomy::I32 srcX, gloomy::I32 srcY, gloomy::I32 srcZ, gloomy::U32 dstName, GLenum dstTarget, gloomy::I32 dstLevel, gloomy::I32 dstX, gloomy::I32 dstY, gloomy::I32 dstZ, gloomy::Size srcWidth, gloomy::Size srcHeight, gloomy::Size srcDepth);
	GLAPI PFNGLCOPYIMAGESUBDATAPROC glad_glCopyImageSubData;
#define glCopyImageSubData glad_glCopyImageSubData
	typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC)(GLenum target, GLenum pname, gloomy::I32 param);
	GLAPI PFNGLFRAMEBUFFERPARAMETERIPROC glad_glFramebufferParameteri;
#define glFramebufferParameteri glad_glFramebufferParameteri
	typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETFRAMEBUFFERPARAMETERIVPROC glad_glGetFramebufferParameteriv;
#define glGetFramebufferParameteriv glad_glGetFramebufferParameteriv
	typedef void (APIENTRYP PFNGLGETINTERNALFORMATI64VPROC)(GLenum target, GLenum internalformat, GLenum pname, gloomy::Size count, gloomy::I3264* params);
	GLAPI PFNGLGETINTERNALFORMATI64VPROC glad_glGetInternalformati64v;
#define glGetInternalformati64v glad_glGetInternalformati64v
	typedef void (APIENTRYP PFNGLINVALIDATETEXSUBIMAGEPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::Size width, gloomy::Size height, gloomy::Size depth);
	GLAPI PFNGLINVALIDATETEXSUBIMAGEPROC glad_glInvalidateTexSubImage;
#define glInvalidateTexSubImage glad_glInvalidateTexSubImage
	typedef void (APIENTRYP PFNGLINVALIDATETEXIMAGEPROC)(gloomy::U32 texture, gloomy::I32 level);
	GLAPI PFNGLINVALIDATETEXIMAGEPROC glad_glInvalidateTexImage;
#define glInvalidateTexImage glad_glInvalidateTexImage
	typedef void (APIENTRYP PFNGLINVALIDATEBUFFERSUBDATAPROC)(gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Sizeptr length);
	GLAPI PFNGLINVALIDATEBUFFERSUBDATAPROC glad_glInvalidateBufferSubData;
#define glInvalidateBufferSubData glad_glInvalidateBufferSubData
	typedef void (APIENTRYP PFNGLINVALIDATEBUFFERDATAPROC)(gloomy::U32 buffer);
	GLAPI PFNGLINVALIDATEBUFFERDATAPROC glad_glInvalidateBufferData;
#define glInvalidateBufferData glad_glInvalidateBufferData
	typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC)(GLenum target, gloomy::Size numAttachments, const GLenum* attachments);
	GLAPI PFNGLINVALIDATEFRAMEBUFFERPROC glad_glInvalidateFramebuffer;
#define glInvalidateFramebuffer glad_glInvalidateFramebuffer
	typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC)(GLenum target, gloomy::Size numAttachments, const GLenum* attachments, gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLINVALIDATESUBFRAMEBUFFERPROC glad_glInvalidateSubFramebuffer;
#define glInvalidateSubFramebuffer glad_glInvalidateSubFramebuffer
	typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC)(GLenum mode, const void* indirect, gloomy::Size drawcount, gloomy::Size stride);
	GLAPI PFNGLMULTIDRAWARRAYSINDIRECTPROC glad_glMultiDrawArraysIndirect;
#define glMultiDrawArraysIndirect glad_glMultiDrawArraysIndirect
	typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void* indirect, gloomy::Size drawcount, gloomy::Size stride);
	GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTPROC glad_glMultiDrawElementsIndirect;
#define glMultiDrawElementsIndirect glad_glMultiDrawElementsIndirect
	typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC)(gloomy::U32 program, GLenum programInterface, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETPROGRAMINTERFACEIVPROC glad_glGetProgramInterfaceiv;
#define glGetProgramInterfaceiv glad_glGetProgramInterfaceiv
	typedef gloomy::U32(APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC)(gloomy::U32 program, GLenum programInterface, const GLchar* name);
	GLAPI PFNGLGETPROGRAMRESOURCEINDEXPROC glad_glGetProgramResourceIndex;
#define glGetProgramResourceIndex glad_glGetProgramResourceIndex
	typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC)(gloomy::U32 program, GLenum programInterface, gloomy::U32 index, gloomy::Size bufSize, gloomy::Size* length, GLchar* name);
	GLAPI PFNGLGETPROGRAMRESOURCENAMEPROC glad_glGetProgramResourceName;
#define glGetProgramResourceName glad_glGetProgramResourceName
	typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC)(gloomy::U32 program, GLenum programInterface, gloomy::U32 index, gloomy::Size propCount, const GLenum* props, gloomy::Size count, gloomy::Size* length, gloomy::I32* params);
	GLAPI PFNGLGETPROGRAMRESOURCEIVPROC glad_glGetProgramResourceiv;
#define glGetProgramResourceiv glad_glGetProgramResourceiv
	typedef gloomy::I32(APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC)(gloomy::U32 program, GLenum programInterface, const GLchar* name);
	GLAPI PFNGLGETPROGRAMRESOURCELOCATIONPROC glad_glGetProgramResourceLocation;
#define glGetProgramResourceLocation glad_glGetProgramResourceLocation
	typedef gloomy::I32(APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)(gloomy::U32 program, GLenum programInterface, const GLchar* name);
	GLAPI PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glad_glGetProgramResourceLocationIndex;
#define glGetProgramResourceLocationIndex glad_glGetProgramResourceLocationIndex
	typedef void (APIENTRYP PFNGLSHADERSTORAGEBLOCKBINDINGPROC)(gloomy::U32 program, gloomy::U32 storageBlockIndex, gloomy::U32 storageBlockBinding);
	GLAPI PFNGLSHADERSTORAGEBLOCKBINDINGPROC glad_glShaderStorageBlockBinding;
#define glShaderStorageBlockBinding glad_glShaderStorageBlockBinding
	typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC)(GLenum target, GLenum internalformat, gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Sizeptr size);
	GLAPI PFNGLTEXBUFFERRANGEPROC glad_glTexBufferRange;
#define glTexBufferRange glad_glTexBufferRange
	typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC)(GLenum target, gloomy::Size samples, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::Bool fixedsamplelocations);
	GLAPI PFNGLTEXSTORAGE2DMULTISAMPLEPROC glad_glTexStorage2DMultisample;
#define glTexStorage2DMultisample glad_glTexStorage2DMultisample
	typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC)(GLenum target, gloomy::Size samples, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::Size depth, gloomy::Bool fixedsamplelocations);
	GLAPI PFNGLTEXSTORAGE3DMULTISAMPLEPROC glad_glTexStorage3DMultisample;
#define glTexStorage3DMultisample glad_glTexStorage3DMultisample
	typedef void (APIENTRYP PFNGLTEXTUREVIEWPROC)(gloomy::U32 texture, GLenum target, gloomy::U32 origtexture, GLenum internalformat, gloomy::U32 minlevel, gloomy::U32 numlevels, gloomy::U32 minlayer, gloomy::U32 numlayers);
	GLAPI PFNGLTEXTUREVIEWPROC glad_glTextureView;
#define glTextureView glad_glTextureView
	typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC)(gloomy::U32 bindingindex, gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Size stride);
	GLAPI PFNGLBINDVERTEXBUFFERPROC glad_glBindVertexBuffer;
#define glBindVertexBuffer glad_glBindVertexBuffer
	typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC)(gloomy::U32 attribindex, gloomy::I32 size, GLenum type, gloomy::Bool normalized, gloomy::U32 relativeoffset);
	GLAPI PFNGLVERTEXATTRIBFORMATPROC glad_glVertexAttribFormat;
#define glVertexAttribFormat glad_glVertexAttribFormat
	typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC)(gloomy::U32 attribindex, gloomy::I32 size, GLenum type, gloomy::U32 relativeoffset);
	GLAPI PFNGLVERTEXATTRIBIFORMATPROC glad_glVertexAttribIFormat;
#define glVertexAttribIFormat glad_glVertexAttribIFormat
	typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATPROC)(gloomy::U32 attribindex, gloomy::I32 size, GLenum type, gloomy::U32 relativeoffset);
	GLAPI PFNGLVERTEXATTRIBLFORMATPROC glad_glVertexAttribLFormat;
#define glVertexAttribLFormat glad_glVertexAttribLFormat
	typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC)(gloomy::U32 attribindex, gloomy::U32 bindingindex);
	GLAPI PFNGLVERTEXATTRIBBINDINGPROC glad_glVertexAttribBinding;
#define glVertexAttribBinding glad_glVertexAttribBinding
	typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC)(gloomy::U32 bindingindex, gloomy::U32 divisor);
	GLAPI PFNGLVERTEXBINDINGDIVISORPROC glad_glVertexBindingDivisor;
#define glVertexBindingDivisor glad_glVertexBindingDivisor
	typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC)(GLenum source, GLenum type, GLenum severity, gloomy::Size count, const gloomy::U32* ids, gloomy::Bool enabled);
	GLAPI PFNGLDEBUGMESSAGECONTROLPROC glad_glDebugMessageControl;
#define glDebugMessageControl glad_glDebugMessageControl
	typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC)(GLenum source, GLenum type, gloomy::U32 id, GLenum severity, gloomy::Size length, const GLchar* buf);
	GLAPI PFNGLDEBUGMESSAGEINSERTPROC glad_glDebugMessageInsert;
#define glDebugMessageInsert glad_glDebugMessageInsert
	typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC callback, const void* userParam);
	GLAPI PFNGLDEBUGMESSAGECALLBACKPROC glad_glDebugMessageCallback;
#define glDebugMessageCallback glad_glDebugMessageCallback
	typedef gloomy::U32(APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC)(gloomy::U32 count, gloomy::Size bufSize, GLenum* sources, GLenum* types, gloomy::U32* ids, GLenum* severities, gloomy::Size* lengths, GLchar* messageLog);
	GLAPI PFNGLGETDEBUGMESSAGELOGPROC glad_glGetDebugMessageLog;
#define glGetDebugMessageLog glad_glGetDebugMessageLog
	typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC)(GLenum source, gloomy::U32 id, gloomy::Size length, const GLchar* message);
	GLAPI PFNGLPUSHDEBUGGROUPPROC glad_glPushDebugGroup;
#define glPushDebugGroup glad_glPushDebugGroup
	typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC)(void);
	GLAPI PFNGLPOPDEBUGGROUPPROC glad_glPopDebugGroup;
#define glPopDebugGroup glad_glPopDebugGroup
	typedef void (APIENTRYP PFNGLOBJECTLABELPROC)(GLenum identifier, gloomy::U32 name, gloomy::Size length, const GLchar* label);
	GLAPI PFNGLOBJECTLABELPROC glad_glObjectLabel;
#define glObjectLabel glad_glObjectLabel
	typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC)(GLenum identifier, gloomy::U32 name, gloomy::Size bufSize, gloomy::Size* length, GLchar* label);
	GLAPI PFNGLGETOBJECTLABELPROC glad_glGetObjectLabel;
#define glGetObjectLabel glad_glGetObjectLabel
	typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC)(const void* ptr, gloomy::Size length, const GLchar* label);
	GLAPI PFNGLOBJECTPTRLABELPROC glad_glObjectPtrLabel;
#define glObjectPtrLabel glad_glObjectPtrLabel
	typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC)(const void* ptr, gloomy::Size bufSize, gloomy::Size* length, GLchar* label);
	GLAPI PFNGLGETOBJECTPTRLABELPROC glad_glGetObjectPtrLabel;
#define glGetObjectPtrLabel glad_glGetObjectPtrLabel
	typedef void (APIENTRYP PFNGLGETPOINTERVPROC)(GLenum pname, void** params);
	GLAPI PFNGLGETPOINTERVPROC glad_glGetPointerv;
#define glGetPointerv glad_glGetPointerv
#endif
#ifndef GL_VERSION_4_4
#define GL_VERSION_4_4 1
	GLAPI int GLAD_GL_VERSION_4_4;
	typedef void (APIENTRYP PFNGLBUFFERSTORAGEPROC)(GLenum target, gloomy::Sizeptr size, const void* data, GLbitfield flags);
	GLAPI PFNGLBUFFERSTORAGEPROC glad_glBufferStorage;
#define glBufferStorage glad_glBufferStorage
	typedef void (APIENTRYP PFNGLCLEARTEXIMAGEPROC)(gloomy::U32 texture, gloomy::I32 level, GLenum format, GLenum type, const void* data);
	GLAPI PFNGLCLEARTEXIMAGEPROC glad_glClearTexImage;
#define glClearTexImage glad_glClearTexImage
	typedef void (APIENTRYP PFNGLCLEARTEXSUBIMAGEPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::Size width, gloomy::Size height, gloomy::Size depth, GLenum format, GLenum type, const void* data);
	GLAPI PFNGLCLEARTEXSUBIMAGEPROC glad_glClearTexSubImage;
#define glClearTexSubImage glad_glClearTexSubImage
	typedef void (APIENTRYP PFNGLBINDBUFFERSBASEPROC)(GLenum target, gloomy::U32 first, gloomy::Size count, const gloomy::U32* buffers);
	GLAPI PFNGLBINDBUFFERSBASEPROC glad_glBindBuffersBase;
#define glBindBuffersBase glad_glBindBuffersBase
	typedef void (APIENTRYP PFNGLBINDBUFFERSRANGEPROC)(GLenum target, gloomy::U32 first, gloomy::Size count, const gloomy::U32* buffers, const gloomy::I32ptr* offsets, const gloomy::Sizeptr* sizes);
	GLAPI PFNGLBINDBUFFERSRANGEPROC glad_glBindBuffersRange;
#define glBindBuffersRange glad_glBindBuffersRange
	typedef void (APIENTRYP PFNGLBINDTEXTURESPROC)(gloomy::U32 first, gloomy::Size count, const gloomy::U32* textures);
	GLAPI PFNGLBINDTEXTURESPROC glad_glBindTextures;
#define glBindTextures glad_glBindTextures
	typedef void (APIENTRYP PFNGLBINDSAMPLERSPROC)(gloomy::U32 first, gloomy::Size count, const gloomy::U32* samplers);
	GLAPI PFNGLBINDSAMPLERSPROC glad_glBindSamplers;
#define glBindSamplers glad_glBindSamplers
	typedef void (APIENTRYP PFNGLBINDIMAGETEXTURESPROC)(gloomy::U32 first, gloomy::Size count, const gloomy::U32* textures);
	GLAPI PFNGLBINDIMAGETEXTURESPROC glad_glBindImageTextures;
#define glBindImageTextures glad_glBindImageTextures
	typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERSPROC)(gloomy::U32 first, gloomy::Size count, const gloomy::U32* buffers, const gloomy::I32ptr* offsets, const gloomy::Size* strides);
	GLAPI PFNGLBINDVERTEXBUFFERSPROC glad_glBindVertexBuffers;
#define glBindVertexBuffers glad_glBindVertexBuffers
#endif
#ifndef GL_VERSION_4_5
#define GL_VERSION_4_5 1
	GLAPI int GLAD_GL_VERSION_4_5;
	typedef void (APIENTRYP PFNGLCLIPCONTROLPROC)(GLenum origin, GLenum depth);
	GLAPI PFNGLCLIPCONTROLPROC glad_glClipControl;
#define glClipControl glad_glClipControl
	typedef void (APIENTRYP PFNGLCREATETRANSFORMFEEDBACKSPROC)(gloomy::Size n, gloomy::U32* ids);
	GLAPI PFNGLCREATETRANSFORMFEEDBACKSPROC glad_glCreateTransformFeedbacks;
#define glCreateTransformFeedbacks glad_glCreateTransformFeedbacks
	typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)(gloomy::U32 xfb, gloomy::U32 index, gloomy::U32 buffer);
	GLAPI PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC glad_glTransformFeedbackBufferBase;
#define glTransformFeedbackBufferBase glad_glTransformFeedbackBufferBase
	typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)(gloomy::U32 xfb, gloomy::U32 index, gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Sizeptr size);
	GLAPI PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC glad_glTransformFeedbackBufferRange;
#define glTransformFeedbackBufferRange glad_glTransformFeedbackBufferRange
	typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKIVPROC)(gloomy::U32 xfb, GLenum pname, gloomy::I32* param);
	GLAPI PFNGLGETTRANSFORMFEEDBACKIVPROC glad_glGetTransformFeedbackiv;
#define glGetTransformFeedbackiv glad_glGetTransformFeedbackiv
	typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI_VPROC)(gloomy::U32 xfb, GLenum pname, gloomy::U32 index, gloomy::I32* param);
	GLAPI PFNGLGETTRANSFORMFEEDBACKI_VPROC glad_glGetTransformFeedbacki_v;
#define glGetTransformFeedbacki_v glad_glGetTransformFeedbacki_v
	typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI64_VPROC)(gloomy::U32 xfb, GLenum pname, gloomy::U32 index, gloomy::I3264* param);
	GLAPI PFNGLGETTRANSFORMFEEDBACKI64_VPROC glad_glGetTransformFeedbacki64_v;
#define glGetTransformFeedbacki64_v glad_glGetTransformFeedbacki64_v
	typedef void (APIENTRYP PFNGLCREATEBUFFERSPROC)(gloomy::Size n, gloomy::U32* buffers);
	GLAPI PFNGLCREATEBUFFERSPROC glad_glCreateBuffers;
#define glCreateBuffers glad_glCreateBuffers
	typedef void (APIENTRYP PFNGLNAMEDBUFFERSTORAGEPROC)(gloomy::U32 buffer, gloomy::Sizeptr size, const void* data, GLbitfield flags);
	GLAPI PFNGLNAMEDBUFFERSTORAGEPROC glad_glNamedBufferStorage;
#define glNamedBufferStorage glad_glNamedBufferStorage
	typedef void (APIENTRYP PFNGLNAMEDBUFFERDATAPROC)(gloomy::U32 buffer, gloomy::Sizeptr size, const void* data, GLenum usage);
	GLAPI PFNGLNAMEDBUFFERDATAPROC glad_glNamedBufferData;
#define glNamedBufferData glad_glNamedBufferData
	typedef void (APIENTRYP PFNGLNAMEDBUFFERSUBDATAPROC)(gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Sizeptr size, const void* data);
	GLAPI PFNGLNAMEDBUFFERSUBDATAPROC glad_glNamedBufferSubData;
#define glNamedBufferSubData glad_glNamedBufferSubData
	typedef void (APIENTRYP PFNGLCOPYNAMEDBUFFERSUBDATAPROC)(gloomy::U32 readBuffer, gloomy::U32 writeBuffer, gloomy::I32ptr readOffset, gloomy::I32ptr writeOffset, gloomy::Sizeptr size);
	GLAPI PFNGLCOPYNAMEDBUFFERSUBDATAPROC glad_glCopyNamedBufferSubData;
#define glCopyNamedBufferSubData glad_glCopyNamedBufferSubData
	typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERDATAPROC)(gloomy::U32 buffer, GLenum internalformat, GLenum format, GLenum type, const void* data);
	GLAPI PFNGLCLEARNAMEDBUFFERDATAPROC glad_glClearNamedBufferData;
#define glClearNamedBufferData glad_glClearNamedBufferData
	typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERSUBDATAPROC)(gloomy::U32 buffer, GLenum internalformat, gloomy::I32ptr offset, gloomy::Sizeptr size, GLenum format, GLenum type, const void* data);
	GLAPI PFNGLCLEARNAMEDBUFFERSUBDATAPROC glad_glClearNamedBufferSubData;
#define glClearNamedBufferSubData glad_glClearNamedBufferSubData
	typedef void* (APIENTRYP PFNGLMAPNAMEDBUFFERPROC)(gloomy::U32 buffer, GLenum access);
	GLAPI PFNGLMAPNAMEDBUFFERPROC glad_glMapNamedBuffer;
#define glMapNamedBuffer glad_glMapNamedBuffer
	typedef void* (APIENTRYP PFNGLMAPNAMEDBUFFERRANGEPROC)(gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Sizeptr length, GLbitfield access);
	GLAPI PFNGLMAPNAMEDBUFFERRANGEPROC glad_glMapNamedBufferRange;
#define glMapNamedBufferRange glad_glMapNamedBufferRange
	typedef gloomy::Bool(APIENTRYP PFNGLUNMAPNAMEDBUFFERPROC)(gloomy::U32 buffer);
	GLAPI PFNGLUNMAPNAMEDBUFFERPROC glad_glUnmapNamedBuffer;
#define glUnmapNamedBuffer glad_glUnmapNamedBuffer
	typedef void (APIENTRYP PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)(gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Sizeptr length);
	GLAPI PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC glad_glFlushMappedNamedBufferRange;
#define glFlushMappedNamedBufferRange glad_glFlushMappedNamedBufferRange
	typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERIVPROC)(gloomy::U32 buffer, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETNAMEDBUFFERPARAMETERIVPROC glad_glGetNamedBufferParameteriv;
#define glGetNamedBufferParameteriv glad_glGetNamedBufferParameteriv
	typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)(gloomy::U32 buffer, GLenum pname, gloomy::I3264* params);
	GLAPI PFNGLGETNAMEDBUFFERPARAMETERI64VPROC glad_glGetNamedBufferParameteri64v;
#define glGetNamedBufferParameteri64v glad_glGetNamedBufferParameteri64v
	typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPOINTERVPROC)(gloomy::U32 buffer, GLenum pname, void** params);
	GLAPI PFNGLGETNAMEDBUFFERPOINTERVPROC glad_glGetNamedBufferPointerv;
#define glGetNamedBufferPointerv glad_glGetNamedBufferPointerv
	typedef void (APIENTRYP PFNGLGETNAMEDBUFFERSUBDATAPROC)(gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Sizeptr size, void* data);
	GLAPI PFNGLGETNAMEDBUFFERSUBDATAPROC glad_glGetNamedBufferSubData;
#define glGetNamedBufferSubData glad_glGetNamedBufferSubData
	typedef void (APIENTRYP PFNGLCREATEFRAMEBUFFERSPROC)(gloomy::Size n, gloomy::U32* framebuffers);
	GLAPI PFNGLCREATEFRAMEBUFFERSPROC glad_glCreateFramebuffers;
#define glCreateFramebuffers glad_glCreateFramebuffers
	typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)(gloomy::U32 framebuffer, GLenum attachment, GLenum renderbuffertarget, gloomy::U32 renderbuffer);
	GLAPI PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC glad_glNamedFramebufferRenderbuffer;
#define glNamedFramebufferRenderbuffer glad_glNamedFramebufferRenderbuffer
	typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)(gloomy::U32 framebuffer, GLenum pname, gloomy::I32 param);
	GLAPI PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC glad_glNamedFramebufferParameteri;
#define glNamedFramebufferParameteri glad_glNamedFramebufferParameteri
	typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)(gloomy::U32 framebuffer, GLenum attachment, gloomy::U32 texture, gloomy::I32 level);
	GLAPI PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glad_glNamedFramebufferTexture;
#define glNamedFramebufferTexture glad_glNamedFramebufferTexture
	typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)(gloomy::U32 framebuffer, GLenum attachment, gloomy::U32 texture, gloomy::I32 level, gloomy::I32 layer);
	GLAPI PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC glad_glNamedFramebufferTextureLayer;
#define glNamedFramebufferTextureLayer glad_glNamedFramebufferTextureLayer
	typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)(gloomy::U32 framebuffer, GLenum buf);
	GLAPI PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC glad_glNamedFramebufferDrawBuffer;
#define glNamedFramebufferDrawBuffer glad_glNamedFramebufferDrawBuffer
	typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)(gloomy::U32 framebuffer, gloomy::Size n, const GLenum* bufs);
	GLAPI PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC glad_glNamedFramebufferDrawBuffers;
#define glNamedFramebufferDrawBuffers glad_glNamedFramebufferDrawBuffers
	typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)(gloomy::U32 framebuffer, GLenum src);
	GLAPI PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC glad_glNamedFramebufferReadBuffer;
#define glNamedFramebufferReadBuffer glad_glNamedFramebufferReadBuffer
	typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)(gloomy::U32 framebuffer, gloomy::Size numAttachments, const GLenum* attachments);
	GLAPI PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC glad_glInvalidateNamedFramebufferData;
#define glInvalidateNamedFramebufferData glad_glInvalidateNamedFramebufferData
	typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)(gloomy::U32 framebuffer, gloomy::Size numAttachments, const GLenum* attachments, gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC glad_glInvalidateNamedFramebufferSubData;
#define glInvalidateNamedFramebufferSubData glad_glInvalidateNamedFramebufferSubData
	typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)(gloomy::U32 framebuffer, GLenum buffer, gloomy::I32 drawbuffer, const gloomy::I32* value);
	GLAPI PFNGLCLEARNAMEDFRAMEBUFFERIVPROC glad_glClearNamedFramebufferiv;
#define glClearNamedFramebufferiv glad_glClearNamedFramebufferiv
	typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)(gloomy::U32 framebuffer, GLenum buffer, gloomy::I32 drawbuffer, const gloomy::U32* value);
	GLAPI PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC glad_glClearNamedFramebufferuiv;
#define glClearNamedFramebufferuiv glad_glClearNamedFramebufferuiv
	typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)(gloomy::U32 framebuffer, GLenum buffer, gloomy::I32 drawbuffer, const gloomy::Float* value);
	GLAPI PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glad_glClearNamedFramebufferfv;
#define glClearNamedFramebufferfv glad_glClearNamedFramebufferfv
	typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)(gloomy::U32 framebuffer, GLenum buffer, gloomy::I32 drawbuffer, gloomy::Float depth, gloomy::I32 stencil);
	GLAPI PFNGLCLEARNAMEDFRAMEBUFFERFIPROC glad_glClearNamedFramebufferfi;
#define glClearNamedFramebufferfi glad_glClearNamedFramebufferfi
	typedef void (APIENTRYP PFNGLBLITNAMEDFRAMEBUFFERPROC)(gloomy::U32 readFramebuffer, gloomy::U32 drawFramebuffer, gloomy::I32 srcX0, gloomy::I32 srcY0, gloomy::I32 srcX1, gloomy::I32 srcY1, gloomy::I32 dstX0, gloomy::I32 dstY0, gloomy::I32 dstX1, gloomy::I32 dstY1, GLbitfield mask, GLenum filter);
	GLAPI PFNGLBLITNAMEDFRAMEBUFFERPROC glad_glBlitNamedFramebuffer;
#define glBlitNamedFramebuffer glad_glBlitNamedFramebuffer
	typedef GLenum(APIENTRYP PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)(gloomy::U32 framebuffer, GLenum target);
	GLAPI PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC glad_glCheckNamedFramebufferStatus;
#define glCheckNamedFramebufferStatus glad_glCheckNamedFramebufferStatus
	typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)(gloomy::U32 framebuffer, GLenum pname, gloomy::I32* param);
	GLAPI PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC glad_glGetNamedFramebufferParameteriv;
#define glGetNamedFramebufferParameteriv glad_glGetNamedFramebufferParameteriv
	typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(gloomy::U32 framebuffer, GLenum attachment, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetNamedFramebufferAttachmentParameteriv;
#define glGetNamedFramebufferAttachmentParameteriv glad_glGetNamedFramebufferAttachmentParameteriv
	typedef void (APIENTRYP PFNGLCREATERENDERBUFFERSPROC)(gloomy::Size n, gloomy::U32* renderbuffers);
	GLAPI PFNGLCREATERENDERBUFFERSPROC glad_glCreateRenderbuffers;
#define glCreateRenderbuffers glad_glCreateRenderbuffers
	typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEPROC)(gloomy::U32 renderbuffer, GLenum internalformat, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLNAMEDRENDERBUFFERSTORAGEPROC glad_glNamedRenderbufferStorage;
#define glNamedRenderbufferStorage glad_glNamedRenderbufferStorage
	typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)(gloomy::U32 renderbuffer, gloomy::Size samples, GLenum internalformat, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glNamedRenderbufferStorageMultisample;
#define glNamedRenderbufferStorageMultisample glad_glNamedRenderbufferStorageMultisample
	typedef void (APIENTRYP PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)(gloomy::U32 renderbuffer, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC glad_glGetNamedRenderbufferParameteriv;
#define glGetNamedRenderbufferParameteriv glad_glGetNamedRenderbufferParameteriv
	typedef void (APIENTRYP PFNGLCREATETEXTURESPROC)(GLenum target, gloomy::Size n, gloomy::U32* textures);
	GLAPI PFNGLCREATETEXTURESPROC glad_glCreateTextures;
#define glCreateTextures glad_glCreateTextures
	typedef void (APIENTRYP PFNGLTEXTUREBUFFERPROC)(gloomy::U32 texture, GLenum internalformat, gloomy::U32 buffer);
	GLAPI PFNGLTEXTUREBUFFERPROC glad_glTextureBuffer;
#define glTextureBuffer glad_glTextureBuffer
	typedef void (APIENTRYP PFNGLTEXTUREBUFFERRANGEPROC)(gloomy::U32 texture, GLenum internalformat, gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Sizeptr size);
	GLAPI PFNGLTEXTUREBUFFERRANGEPROC glad_glTextureBufferRange;
#define glTextureBufferRange glad_glTextureBufferRange
	typedef void (APIENTRYP PFNGLTEXTURESTORAGE1DPROC)(gloomy::U32 texture, gloomy::Size levels, GLenum internalformat, gloomy::Size width);
	GLAPI PFNGLTEXTURESTORAGE1DPROC glad_glTextureStorage1D;
#define glTextureStorage1D glad_glTextureStorage1D
	typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DPROC)(gloomy::U32 texture, gloomy::Size levels, GLenum internalformat, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLTEXTURESTORAGE2DPROC glad_glTextureStorage2D;
#define glTextureStorage2D glad_glTextureStorage2D
	typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DPROC)(gloomy::U32 texture, gloomy::Size levels, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::Size depth);
	GLAPI PFNGLTEXTURESTORAGE3DPROC glad_glTextureStorage3D;
#define glTextureStorage3D glad_glTextureStorage3D
	typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)(gloomy::U32 texture, gloomy::Size samples, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::Bool fixedsamplelocations);
	GLAPI PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glad_glTextureStorage2DMultisample;
#define glTextureStorage2DMultisample glad_glTextureStorage2DMultisample
	typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)(gloomy::U32 texture, gloomy::Size samples, GLenum internalformat, gloomy::Size width, gloomy::Size height, gloomy::Size depth, gloomy::Bool fixedsamplelocations);
	GLAPI PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC glad_glTextureStorage3DMultisample;
#define glTextureStorage3DMultisample glad_glTextureStorage3DMultisample
	typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE1DPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::Size width, GLenum format, GLenum type, const void* pixels);
	GLAPI PFNGLTEXTURESUBIMAGE1DPROC glad_glTextureSubImage1D;
#define glTextureSubImage1D glad_glTextureSubImage1D
	typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE2DPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::Size width, gloomy::Size height, GLenum format, GLenum type, const void* pixels);
	GLAPI PFNGLTEXTURESUBIMAGE2DPROC glad_glTextureSubImage2D;
#define glTextureSubImage2D glad_glTextureSubImage2D
	typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE3DPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::Size width, gloomy::Size height, gloomy::Size depth, GLenum format, GLenum type, const void* pixels);
	GLAPI PFNGLTEXTURESUBIMAGE3DPROC glad_glTextureSubImage3D;
#define glTextureSubImage3D glad_glTextureSubImage3D
	typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::Size width, GLenum format, gloomy::Size imageSize, const void* data);
	GLAPI PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC glad_glCompressedTextureSubImage1D;
#define glCompressedTextureSubImage1D glad_glCompressedTextureSubImage1D
	typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::Size width, gloomy::Size height, GLenum format, gloomy::Size imageSize, const void* data);
	GLAPI PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC glad_glCompressedTextureSubImage2D;
#define glCompressedTextureSubImage2D glad_glCompressedTextureSubImage2D
	typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::Size width, gloomy::Size height, gloomy::Size depth, GLenum format, gloomy::Size imageSize, const void* data);
	GLAPI PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC glad_glCompressedTextureSubImage3D;
#define glCompressedTextureSubImage3D glad_glCompressedTextureSubImage3D
	typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE1DPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 x, gloomy::I32 y, gloomy::Size width);
	GLAPI PFNGLCOPYTEXTURESUBIMAGE1DPROC glad_glCopyTextureSubImage1D;
#define glCopyTextureSubImage1D glad_glCopyTextureSubImage1D
	typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE2DPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLCOPYTEXTURESUBIMAGE2DPROC glad_glCopyTextureSubImage2D;
#define glCopyTextureSubImage2D glad_glCopyTextureSubImage2D
	typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE3DPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height);
	GLAPI PFNGLCOPYTEXTURESUBIMAGE3DPROC glad_glCopyTextureSubImage3D;
#define glCopyTextureSubImage3D glad_glCopyTextureSubImage3D
	typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFPROC)(gloomy::U32 texture, GLenum pname, gloomy::Float param);
	GLAPI PFNGLTEXTUREPARAMETERFPROC glad_glTextureParameterf;
#define glTextureParameterf glad_glTextureParameterf
	typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFVPROC)(gloomy::U32 texture, GLenum pname, const gloomy::Float* param);
	GLAPI PFNGLTEXTUREPARAMETERFVPROC glad_glTextureParameterfv;
#define glTextureParameterfv glad_glTextureParameterfv
	typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIPROC)(gloomy::U32 texture, GLenum pname, gloomy::I32 param);
	GLAPI PFNGLTEXTUREPARAMETERIPROC glad_glTextureParameteri;
#define glTextureParameteri glad_glTextureParameteri
	typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIIVPROC)(gloomy::U32 texture, GLenum pname, const gloomy::I32* params);
	GLAPI PFNGLTEXTUREPARAMETERIIVPROC glad_glTextureParameterIiv;
#define glTextureParameterIiv glad_glTextureParameterIiv
	typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIUIVPROC)(gloomy::U32 texture, GLenum pname, const gloomy::U32* params);
	GLAPI PFNGLTEXTUREPARAMETERIUIVPROC glad_glTextureParameterIuiv;
#define glTextureParameterIuiv glad_glTextureParameterIuiv
	typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIVPROC)(gloomy::U32 texture, GLenum pname, const gloomy::I32* param);
	GLAPI PFNGLTEXTUREPARAMETERIVPROC glad_glTextureParameteriv;
#define glTextureParameteriv glad_glTextureParameteriv
	typedef void (APIENTRYP PFNGLGENERATETEXTUREMIPMAPPROC)(gloomy::U32 texture);
	GLAPI PFNGLGENERATETEXTUREMIPMAPPROC glad_glGenerateTextureMipmap;
#define glGenerateTextureMipmap glad_glGenerateTextureMipmap
	typedef void (APIENTRYP PFNGLBINDTEXTUREUNITPROC)(gloomy::U32 unit, gloomy::U32 texture);
	GLAPI PFNGLBINDTEXTUREUNITPROC glad_glBindTextureUnit;
#define glBindTextureUnit glad_glBindTextureUnit
	typedef void (APIENTRYP PFNGLGETTEXTUREIMAGEPROC)(gloomy::U32 texture, gloomy::I32 level, GLenum format, GLenum type, gloomy::Size bufSize, void* pixels);
	GLAPI PFNGLGETTEXTUREIMAGEPROC glad_glGetTextureImage;
#define glGetTextureImage glad_glGetTextureImage
	typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::Size bufSize, void* pixels);
	GLAPI PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC glad_glGetCompressedTextureImage;
#define glGetCompressedTextureImage glad_glGetCompressedTextureImage
	typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERFVPROC)(gloomy::U32 texture, gloomy::I32 level, GLenum pname, gloomy::Float* params);
	GLAPI PFNGLGETTEXTURELEVELPARAMETERFVPROC glad_glGetTextureLevelParameterfv;
#define glGetTextureLevelParameterfv glad_glGetTextureLevelParameterfv
	typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERIVPROC)(gloomy::U32 texture, gloomy::I32 level, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETTEXTURELEVELPARAMETERIVPROC glad_glGetTextureLevelParameteriv;
#define glGetTextureLevelParameteriv glad_glGetTextureLevelParameteriv
	typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERFVPROC)(gloomy::U32 texture, GLenum pname, gloomy::Float* params);
	GLAPI PFNGLGETTEXTUREPARAMETERFVPROC glad_glGetTextureParameterfv;
#define glGetTextureParameterfv glad_glGetTextureParameterfv
	typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIIVPROC)(gloomy::U32 texture, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETTEXTUREPARAMETERIIVPROC glad_glGetTextureParameterIiv;
#define glGetTextureParameterIiv glad_glGetTextureParameterIiv
	typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIUIVPROC)(gloomy::U32 texture, GLenum pname, gloomy::U32* params);
	GLAPI PFNGLGETTEXTUREPARAMETERIUIVPROC glad_glGetTextureParameterIuiv;
#define glGetTextureParameterIuiv glad_glGetTextureParameterIuiv
	typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIVPROC)(gloomy::U32 texture, GLenum pname, gloomy::I32* params);
	GLAPI PFNGLGETTEXTUREPARAMETERIVPROC glad_glGetTextureParameteriv;
#define glGetTextureParameteriv glad_glGetTextureParameteriv
	typedef void (APIENTRYP PFNGLCREATEVERTEXARRAYSPROC)(gloomy::Size n, gloomy::U32* arrays);
	GLAPI PFNGLCREATEVERTEXARRAYSPROC glad_glCreateVertexArrays;
#define glCreateVertexArrays glad_glCreateVertexArrays
	typedef void (APIENTRYP PFNGLDISABLEVERTEXARRAYATTRIBPROC)(gloomy::U32 vaobj, gloomy::U32 index);
	GLAPI PFNGLDISABLEVERTEXARRAYATTRIBPROC glad_glDisableVertexArrayAttrib;
#define glDisableVertexArrayAttrib glad_glDisableVertexArrayAttrib
	typedef void (APIENTRYP PFNGLENABLEVERTEXARRAYATTRIBPROC)(gloomy::U32 vaobj, gloomy::U32 index);
	GLAPI PFNGLENABLEVERTEXARRAYATTRIBPROC glad_glEnableVertexArrayAttrib;
#define glEnableVertexArrayAttrib glad_glEnableVertexArrayAttrib
	typedef void (APIENTRYP PFNGLVERTEXARRAYELEMENTBUFFERPROC)(gloomy::U32 vaobj, gloomy::U32 buffer);
	GLAPI PFNGLVERTEXARRAYELEMENTBUFFERPROC glad_glVertexArrayElementBuffer;
#define glVertexArrayElementBuffer glad_glVertexArrayElementBuffer
	typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERPROC)(gloomy::U32 vaobj, gloomy::U32 bindingindex, gloomy::U32 buffer, gloomy::I32ptr offset, gloomy::Size stride);
	GLAPI PFNGLVERTEXARRAYVERTEXBUFFERPROC glad_glVertexArrayVertexBuffer;
#define glVertexArrayVertexBuffer glad_glVertexArrayVertexBuffer
	typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERSPROC)(gloomy::U32 vaobj, gloomy::U32 first, gloomy::Size count, const gloomy::U32* buffers, const gloomy::I32ptr* offsets, const gloomy::Size* strides);
	GLAPI PFNGLVERTEXARRAYVERTEXBUFFERSPROC glad_glVertexArrayVertexBuffers;
#define glVertexArrayVertexBuffers glad_glVertexArrayVertexBuffers
	typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBBINDINGPROC)(gloomy::U32 vaobj, gloomy::U32 attribindex, gloomy::U32 bindingindex);
	GLAPI PFNGLVERTEXARRAYATTRIBBINDINGPROC glad_glVertexArrayAttribBinding;
#define glVertexArrayAttribBinding glad_glVertexArrayAttribBinding
	typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBFORMATPROC)(gloomy::U32 vaobj, gloomy::U32 attribindex, gloomy::I32 size, GLenum type, gloomy::Bool normalized, gloomy::U32 relativeoffset);
	GLAPI PFNGLVERTEXARRAYATTRIBFORMATPROC glad_glVertexArrayAttribFormat;
#define glVertexArrayAttribFormat glad_glVertexArrayAttribFormat
	typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBIFORMATPROC)(gloomy::U32 vaobj, gloomy::U32 attribindex, gloomy::I32 size, GLenum type, gloomy::U32 relativeoffset);
	GLAPI PFNGLVERTEXARRAYATTRIBIFORMATPROC glad_glVertexArrayAttribIFormat;
#define glVertexArrayAttribIFormat glad_glVertexArrayAttribIFormat
	typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBLFORMATPROC)(gloomy::U32 vaobj, gloomy::U32 attribindex, gloomy::I32 size, GLenum type, gloomy::U32 relativeoffset);
	GLAPI PFNGLVERTEXARRAYATTRIBLFORMATPROC glad_glVertexArrayAttribLFormat;
#define glVertexArrayAttribLFormat glad_glVertexArrayAttribLFormat
	typedef void (APIENTRYP PFNGLVERTEXARRAYBINDINGDIVISORPROC)(gloomy::U32 vaobj, gloomy::U32 bindingindex, gloomy::U32 divisor);
	GLAPI PFNGLVERTEXARRAYBINDINGDIVISORPROC glad_glVertexArrayBindingDivisor;
#define glVertexArrayBindingDivisor glad_glVertexArrayBindingDivisor
	typedef void (APIENTRYP PFNGLGETVERTEXARRAYIVPROC)(gloomy::U32 vaobj, GLenum pname, gloomy::I32* param);
	GLAPI PFNGLGETVERTEXARRAYIVPROC glad_glGetVertexArrayiv;
#define glGetVertexArrayiv glad_glGetVertexArrayiv
	typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXEDIVPROC)(gloomy::U32 vaobj, gloomy::U32 index, GLenum pname, gloomy::I32* param);
	GLAPI PFNGLGETVERTEXARRAYINDEXEDIVPROC glad_glGetVertexArrayIndexediv;
#define glGetVertexArrayIndexediv glad_glGetVertexArrayIndexediv
	typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXED64IVPROC)(gloomy::U32 vaobj, gloomy::U32 index, GLenum pname, gloomy::I3264* param);
	GLAPI PFNGLGETVERTEXARRAYINDEXED64IVPROC glad_glGetVertexArrayIndexed64iv;
#define glGetVertexArrayIndexed64iv glad_glGetVertexArrayIndexed64iv
	typedef void (APIENTRYP PFNGLCREATESAMPLERSPROC)(gloomy::Size n, gloomy::U32* samplers);
	GLAPI PFNGLCREATESAMPLERSPROC glad_glCreateSamplers;
#define glCreateSamplers glad_glCreateSamplers
	typedef void (APIENTRYP PFNGLCREATEPROGRAMPIPELINESPROC)(gloomy::Size n, gloomy::U32* pipelines);
	GLAPI PFNGLCREATEPROGRAMPIPELINESPROC glad_glCreateProgramPipelines;
#define glCreateProgramPipelines glad_glCreateProgramPipelines
	typedef void (APIENTRYP PFNGLCREATEQUERIESPROC)(GLenum target, gloomy::Size n, gloomy::U32* ids);
	GLAPI PFNGLCREATEQUERIESPROC glad_glCreateQueries;
#define glCreateQueries glad_glCreateQueries
	typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTI64VPROC)(gloomy::U32 id, gloomy::U32 buffer, GLenum pname, gloomy::I32ptr offset);
	GLAPI PFNGLGETQUERYBUFFEROBJECTI64VPROC glad_glGetQueryBufferObjecti64v;
#define glGetQueryBufferObjecti64v glad_glGetQueryBufferObjecti64v
	typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTIVPROC)(gloomy::U32 id, gloomy::U32 buffer, GLenum pname, gloomy::I32ptr offset);
	GLAPI PFNGLGETQUERYBUFFEROBJECTIVPROC glad_glGetQueryBufferObjectiv;
#define glGetQueryBufferObjectiv glad_glGetQueryBufferObjectiv
	typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUI64VPROC)(gloomy::U32 id, gloomy::U32 buffer, GLenum pname, gloomy::I32ptr offset);
	GLAPI PFNGLGETQUERYBUFFEROBJECTUI64VPROC glad_glGetQueryBufferObjectui64v;
#define glGetQueryBufferObjectui64v glad_glGetQueryBufferObjectui64v
	typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUIVPROC)(gloomy::U32 id, gloomy::U32 buffer, GLenum pname, gloomy::I32ptr offset);
	GLAPI PFNGLGETQUERYBUFFEROBJECTUIVPROC glad_glGetQueryBufferObjectuiv;
#define glGetQueryBufferObjectuiv glad_glGetQueryBufferObjectuiv
	typedef void (APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC)(GLbitfield barriers);
	GLAPI PFNGLMEMORYBARRIERBYREGIONPROC glad_glMemoryBarrierByRegion;
#define glMemoryBarrierByRegion glad_glMemoryBarrierByRegion
	typedef void (APIENTRYP PFNGLGETTEXTURESUBIMAGEPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::Size width, gloomy::Size height, gloomy::Size depth, GLenum format, GLenum type, gloomy::Size bufSize, void* pixels);
	GLAPI PFNGLGETTEXTURESUBIMAGEPROC glad_glGetTextureSubImage;
#define glGetTextureSubImage glad_glGetTextureSubImage
	typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)(gloomy::U32 texture, gloomy::I32 level, gloomy::I32 xoffset, gloomy::I32 yoffset, gloomy::I32 zoffset, gloomy::Size width, gloomy::Size height, gloomy::Size depth, gloomy::Size bufSize, void* pixels);
	GLAPI PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC glad_glGetCompressedTextureSubImage;
#define glGetCompressedTextureSubImage glad_glGetCompressedTextureSubImage
	typedef GLenum(APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC)(void);
	GLAPI PFNGLGETGRAPHICSRESETSTATUSPROC glad_glGetGraphicsResetStatus;
#define glGetGraphicsResetStatus glad_glGetGraphicsResetStatus
	typedef void (APIENTRYP PFNGLGETNCOMPRESSEDTEXIMAGEPROC)(GLenum target, gloomy::I32 lod, gloomy::Size bufSize, void* pixels);
	GLAPI PFNGLGETNCOMPRESSEDTEXIMAGEPROC glad_glGetnCompressedTexImage;
#define glGetnCompressedTexImage glad_glGetnCompressedTexImage
	typedef void (APIENTRYP PFNGLGETNTEXIMAGEPROC)(GLenum target, gloomy::I32 level, GLenum format, GLenum type, gloomy::Size bufSize, void* pixels);
	GLAPI PFNGLGETNTEXIMAGEPROC glad_glGetnTexImage;
#define glGetnTexImage glad_glGetnTexImage
	typedef void (APIENTRYP PFNGLGETNUNIFORMDVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size bufSize, GLdouble* params);
	GLAPI PFNGLGETNUNIFORMDVPROC glad_glGetnUniformdv;
#define glGetnUniformdv glad_glGetnUniformdv
	typedef void (APIENTRYP PFNGLGETNUNIFORMFVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size bufSize, gloomy::Float* params);
	GLAPI PFNGLGETNUNIFORMFVPROC glad_glGetnUniformfv;
#define glGetnUniformfv glad_glGetnUniformfv
	typedef void (APIENTRYP PFNGLGETNUNIFORMIVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size bufSize, gloomy::I32* params);
	GLAPI PFNGLGETNUNIFORMIVPROC glad_glGetnUniformiv;
#define glGetnUniformiv glad_glGetnUniformiv
	typedef void (APIENTRYP PFNGLGETNUNIFORMUIVPROC)(gloomy::U32 program, gloomy::I32 location, gloomy::Size bufSize, gloomy::U32* params);
	GLAPI PFNGLGETNUNIFORMUIVPROC glad_glGetnUniformuiv;
#define glGetnUniformuiv glad_glGetnUniformuiv
	typedef void (APIENTRYP PFNGLREADNPIXELSPROC)(gloomy::I32 x, gloomy::I32 y, gloomy::Size width, gloomy::Size height, GLenum format, GLenum type, gloomy::Size bufSize, void* data);
	GLAPI PFNGLREADNPIXELSPROC glad_glReadnPixels;
#define glReadnPixels glad_glReadnPixels
	typedef void (APIENTRYP PFNGLGETNMAPDVPROC)(GLenum target, GLenum query, gloomy::Size bufSize, GLdouble* v);
	GLAPI PFNGLGETNMAPDVPROC glad_glGetnMapdv;
#define glGetnMapdv glad_glGetnMapdv
	typedef void (APIENTRYP PFNGLGETNMAPFVPROC)(GLenum target, GLenum query, gloomy::Size bufSize, gloomy::Float* v);
	GLAPI PFNGLGETNMAPFVPROC glad_glGetnMapfv;
#define glGetnMapfv glad_glGetnMapfv
	typedef void (APIENTRYP PFNGLGETNMAPIVPROC)(GLenum target, GLenum query, gloomy::Size bufSize, gloomy::I32* v);
	GLAPI PFNGLGETNMAPIVPROC glad_glGetnMapiv;
#define glGetnMapiv glad_glGetnMapiv
	typedef void (APIENTRYP PFNGLGETNPIXELMAPFVPROC)(GLenum map, gloomy::Size bufSize, gloomy::Float* values);
	GLAPI PFNGLGETNPIXELMAPFVPROC glad_glGetnPixelMapfv;
#define glGetnPixelMapfv glad_glGetnPixelMapfv
	typedef void (APIENTRYP PFNGLGETNPIXELMAPUIVPROC)(GLenum map, gloomy::Size bufSize, gloomy::U32* values);
	GLAPI PFNGLGETNPIXELMAPUIVPROC glad_glGetnPixelMapuiv;
#define glGetnPixelMapuiv glad_glGetnPixelMapuiv
	typedef void (APIENTRYP PFNGLGETNPIXELMAPUSVPROC)(GLenum map, gloomy::Size bufSize, GLushort* values);
	GLAPI PFNGLGETNPIXELMAPUSVPROC glad_glGetnPixelMapusv;
#define glGetnPixelMapusv glad_glGetnPixelMapusv
	typedef void (APIENTRYP PFNGLGETNPOLYGONSTIPPLEPROC)(gloomy::Size bufSize, GLubyte* pattern);
	GLAPI PFNGLGETNPOLYGONSTIPPLEPROC glad_glGetnPolygonStipple;
#define glGetnPolygonStipple glad_glGetnPolygonStipple
	typedef void (APIENTRYP PFNGLGETNCOLORTABLEPROC)(GLenum target, GLenum format, GLenum type, gloomy::Size bufSize, void* table);
	GLAPI PFNGLGETNCOLORTABLEPROC glad_glGetnColorTable;
#define glGetnColorTable glad_glGetnColorTable
	typedef void (APIENTRYP PFNGLGETNCONVOLUTIONFILTERPROC)(GLenum target, GLenum format, GLenum type, gloomy::Size bufSize, void* image);
	GLAPI PFNGLGETNCONVOLUTIONFILTERPROC glad_glGetnConvolutionFilter;
#define glGetnConvolutionFilter glad_glGetnConvolutionFilter
	typedef void (APIENTRYP PFNGLGETNSEPARABLEFILTERPROC)(GLenum target, GLenum format, GLenum type, gloomy::Size rowBufSize, void* row, gloomy::Size columnBufSize, void* column, void* span);
	GLAPI PFNGLGETNSEPARABLEFILTERPROC glad_glGetnSeparableFilter;
#define glGetnSeparableFilter glad_glGetnSeparableFilter
	typedef void (APIENTRYP PFNGLGETNHISTOGRAMPROC)(GLenum target, gloomy::Bool reset, GLenum format, GLenum type, gloomy::Size bufSize, void* values);
	GLAPI PFNGLGETNHISTOGRAMPROC glad_glGetnHistogram;
#define glGetnHistogram glad_glGetnHistogram
	typedef void (APIENTRYP PFNGLGETNMINMAXPROC)(GLenum target, gloomy::Bool reset, GLenum format, GLenum type, gloomy::Size bufSize, void* values);
	GLAPI PFNGLGETNMINMAXPROC glad_glGetnMinmax;
#define glGetnMinmax glad_glGetnMinmax
	typedef void (APIENTRYP PFNGLTEXTUREBARRIERPROC)(void);
	GLAPI PFNGLTEXTUREBARRIERPROC glad_glTextureBarrier;
#define glTextureBarrier glad_glTextureBarrier
#endif
#ifndef GL_VERSION_4_6
#define GL_VERSION_4_6 1
	GLAPI int GLAD_GL_VERSION_4_6;
	typedef void (APIENTRYP PFNGLSPECIALIZESHADERPROC)(gloomy::U32 shader, const GLchar* pEntryPoint, gloomy::U32 numSpecializationConstants, const gloomy::U32* pConstantIndex, const gloomy::U32* pConstantValue);
	GLAPI PFNGLSPECIALIZESHADERPROC glad_glSpecializeShader;
#define glSpecializeShader glad_glSpecializeShader
	typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)(GLenum mode, const void* indirect, gloomy::I32ptr drawcount, gloomy::Size maxdrawcount, gloomy::Size stride);
	GLAPI PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glad_glMultiDrawArraysIndirectCount;
#define glMultiDrawArraysIndirectCount glad_glMultiDrawArraysIndirectCount
	typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)(GLenum mode, GLenum type, const void* indirect, gloomy::I32ptr drawcount, gloomy::Size maxdrawcount, gloomy::Size stride);
	GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glad_glMultiDrawElementsIndirectCount;
#define glMultiDrawElementsIndirectCount glad_glMultiDrawElementsIndirectCount
	typedef void (APIENTRYP PFNGLPOLYGONOFFSETCLAMPPROC)(gloomy::Float factor, gloomy::Float units, gloomy::Float clamp);
	GLAPI PFNGLPOLYGONOFFSETCLAMPPROC glad_glPolygonOffsetClamp;
#define glPolygonOffsetClamp glad_glPolygonOffsetClamp
#endif
*/
}