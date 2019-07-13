#ifndef TINYEXTENDER_H_
#define	TINYEXTENDER_H_

#if defined(_WIN32) || defined(_WIN64)
#ifndef WIN32_LEAN_AND_MEAN
#define	WIN32_LEAN_AND_MEAN 1
#endif //WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define	NOMINMAX 1
#endif //NOMINMAX
#ifndef TW_WINDOWS
#define TE_WINDOWS 1
#endif //TE_WINDOWS
#include <Windows.h>
#include <gl/GL.h>
#endif //_WIN32 || _WIN64

#if defined(__linux__)
		TE_LINUX
#include <GL/glx.h>
#endif //__linux__

#include <system_error>
#include <cstring>

#ifndef GLEXT_64_TYPES_DEFINED
	// This code block is duplicated in glxext.h, so must be protected
#define	GLEXT_64_TYPES_DEFINED
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#if defined(__STDC__)
	using int64_t = long long int;
	using uint64_t = unsigned long long int;
#endif // __STDC__
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
	using int32_t = __int32;
	using int64_t = __int64;
	using uint64_t = unsigned __int64;
#else
	// fall back if nothing above works
#include <inttypes.h>
#endif
#endif

namespace TinyExtender
{
	typedef unsigned int GLenum;
	typedef unsigned int GLbitfield;
	typedef unsigned int GLuint;
	typedef int GLint;
	typedef int GLsizei;
	typedef unsigned char GLboolean;
	typedef signed char GLbyte;
	typedef short GLshort;
	typedef unsigned char GLubyte;
	typedef unsigned short GLushort;
	typedef unsigned long GLulong;
	typedef float GLfloat;
	typedef float GLclampf;
	typedef double GLdouble;
	typedef double GLclampd;
	typedef void GLvoid;
	using GLuint64 = uint64_t;
	using GLint64 = int64_t;
#if defined(_MSC_VER) && _MSC_VER < 1400
	typedef __int64 GLint64EXT;
	typedef unsigned __int64 GLuint64EXT;
#elif defined(_MSC_VER) || defined(__BORLANDC__)
	typedef signed long long GLint64EXT;
	typedef unsigned long long GLuint64EXT;
#else
# if defined(__MINGW32__) || defined(__CYGWIN__)
#include <inttypes.h>
# endif
	typedef int64_t GLint64EXT;
	typedef uint64_t GLuint64EXT;
#endif
	//typedef GLint64EXT GLint64;
	//typedef GLuint64EXT GLuint64;
	typedef struct __GLsync* GLsync;

	typedef char GLchar;

	//*< returns a proc address to an OpenGL extension
	template<typename T> void FetchProcAddress(T& funcPointer, const char* procName)
	{
#if defined(TE_WINDOWS)
		funcPointer = (T)wglGetProcAddress(procName);
#elif defined(TE_LINUX)
		funcPointer = (T)glXGetProcAddress(procName);
#endif
	}

	//OpenGL 1.2 Extensions
#pragma region OpenGL1_2

	enum openGL1_2_t
	{
		gl_smooth_point_size_range = 0x0b12,
		gl_smooth_point_size_granularity = 0x0b13,
		gl_smooth_line_width_range = 0x0b22,
		gl_smooth_line_width_granularity = 0x0b23,
		gl_unsigned_byte_3_3_2 = 0x8032,
		gl_unsigned_short_4_4_4_4 = 0x8033,
		gl_unsigned_short_5_5_5_1 = 0x8034,
		gl_unsigned_int_8_8_8_8 = 0x8035,
		gl_unsigned_int_10_10_10_2 = 0x8036,
		gl_rescale_normal = 0x803a,
		gl_texture_binding_3d = 0x806a,
		gl_pack_skip_images = 0x806b,
		gl_pack_image_height = 0x806c,
		gl_unpack_skip_images = 0x806d,
		gl_unpack_image_height = 0x806e,
		gl_texture_3d = 0x806f,
		gl_proxy_texture_3d = 0x8070,
		gl_texture_depth = 0x8071,
		gl_texture_wrap_r = 0x8072,
		gl_max_3d_texture_size = 0x8073,
		gl_bgr = 0x80e0,
		gl_bgra = 0x80e1,
		gl_max_elements_vertices = 0x80e8,
		gl_max_elements_indices = 0x80e9,
		gl_clamp_to_edge = 0x812f,
		gl_texture_min_lod = 0x813a,
		gl_texture_max_lod = 0x813b,
		gl_texture_base_level = 0x813c,
		gl_texture_max_level = 0x813d,
		gl_light_model_color_control = 0x81f8,
		gl_single_color = 0x81f9,
		gl_separate_specular_color = 0x81fa,
		gl_unsigned_byte_2_3_3_rev = 0x8362,
		gl_unsigned_short_5_6_5 = 0x8363,
		gl_unsigned_short_5_6_5_rev = 0x8364,
		gl_unsigned_short_4_4_4_4_rev = 0x8365,
		gl_unsigned_short_1_5_5_5_rev = 0x8366,
		gl_unsigned_int_8_8_8_8_rev = 0x8367,
		gl_aliased_point_size_range = 0x846d,
		gl_aliased_line_width_range = 0x846e,
	};

	void(*glDrawRangeElements) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices) = nullptr;
	void(*glTexImage3D) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels) = nullptr;
	void(*glTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels) = nullptr;
	void(*glCopyTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;

	//*< load OpenGL 1.2 extensions
	void Load1_2Extensions()
	{
		FetchProcAddress(glDrawRangeElements, "glDrawRangeElements");
		FetchProcAddress(glTexImage3D, "glTexImage3D");
		FetchProcAddress(glTexSubImage3D, "glTexSubImage3D");
		FetchProcAddress(glCopyTexSubImage3D, "glCopyTexSubImage3D");
	}

#pragma endregion OpenGL1_2 Extensions

	//OpenGL 1.3 Extensions
#pragma region OpenGL1_3

	enum openGL1_3_t
	{
		gl_multisample = 0x809d,
		gl_sample_alpha_to_coverage = 0x809e,
		gl_sample_alpha_to_one = 0x809f,
		gl_sample_coverage = 0x80a0,
		gl_sample_buffers = 0x80a8,
		gl_samples = 0x80a9,
		gl_sample_coverage_value = 0x80aa,
		gl_sample_coverage_invert = 0x80ab,
		gl_clamp_to_border = 0x812d,
		gl_texture0 = 0x84c0,
		gl_texture1 = 0x84c1,
		gl_texture2 = 0x84c2,
		gl_texture3 = 0x84c3,
		gl_texture4 = 0x84c4,
		gl_texture5 = 0x84c5,
		gl_texture6 = 0x84c6,
		gl_texture7 = 0x84c7,
		gl_texture8 = 0x84c8,
		gl_texture9 = 0x84c9,
		gl_texture10 = 0x84ca,
		gl_texture11 = 0x84cb,
		gl_texture12 = 0x84cc,
		gl_texture13 = 0x84cd,
		gl_texture14 = 0x84ce,
		gl_texture15 = 0x84cf,
		gl_texture16 = 0x84d0,
		gl_texture17 = 0x84d1,
		gl_texture18 = 0x84d2,
		gl_texture19 = 0x84d3,
		gl_texture20 = 0x84d4,
		gl_texture21 = 0x84d5,
		gl_texture22 = 0x84d6,
		gl_texture23 = 0x84d7,
		gl_texture24 = 0x84d8,
		gl_texture25 = 0x84d9,
		gl_texture26 = 0x84da,
		gl_texture27 = 0x84db,
		gl_texture28 = 0x84dc,
		gl_texture29 = 0x84dd,
		gl_texture30 = 0x84de,
		gl_texture31 = 0x84df,
		gl_active_texture = 0x84e0,
		gl_client_active_texture = 0x84e1,
		gl_max_texture_units = 0x84e2,
		gl_transpose_modelview_matrix = 0x84e3,
		gl_transpose_projection_matrix = 0x84e4,
		gl_transpose_texture_matrix = 0x84e5,
		gl_transpose_color_matrix = 0x84e6,
		gl_subtract = 0x84e7,
		gl_compressed_alpha = 0x84e9,
		gl_compressed_luminance = 0x84ea,
		gl_compressed_luminance_alpha = 0x84eb,
		gl_compressed_intensity = 0x84ec,
		gl_compressed_rgb = 0x84ed,
		gl_compressed_rgba = 0x84ee,
		gl_texture_compression_hint = 0x84ef,
		gl_normal_map = 0x8511,
		gl_reflection_map = 0x8512,
		gl_texture_cube_map = 0x8513,
		gl_texture_binding_cube_map = 0x8514,
		gl_texture_cube_map_positive_x = 0x8515,
		gl_texture_cube_map_negative_x = 0x8516,
		gl_texture_cube_map_positive_y = 0x8517,
		gl_texture_cube_map_negative_y = 0x8518,
		gl_texture_cube_map_positive_z = 0x8519,
		gl_texture_cube_map_negative_z = 0x851a,
		gl_proxy_texture_cube_map = 0x851b,
		gl_max_cube_map_texture_size = 0x851c,
		gl_combine = 0x8570,
		gl_combine_rgb = 0x8571,
		gl_combine_alpha = 0x8572,
		gl_rgb_scale = 0x8573,
		gl_add_signed = 0x8574,
		gl_interpolate = 0x8575,
		gl_constant = 0x8576,
		gl_primary_color = 0x8577,
		gl_previous = 0x8578,
		gl_source0_rgb = 0x8580,
		gl_source1_rgb = 0x8581,
		gl_source2_rgb = 0x8582,
		gl_source0_alpha = 0x8588,
		gl_source1_alpha = 0x8589,
		gl_source2_alpha = 0x858a,
		gl_operand0_rgb = 0x8590,
		gl_operand1_rgb = 0x8591,
		gl_operand2_rgb = 0x8592,
		gl_operand0_alpha = 0x8598,
		gl_operand1_alpha = 0x8599,
		gl_operand2_alpha = 0x859a,
		gl_texture_compressed_image_size = 0x86a0,
		gl_texture_compressed = 0x86a1,
		gl_num_compressed_texture_formats = 0x86a2,
		gl_compressed_texture_formats = 0x86a3,
		gl_dot3_rgb = 0x86ae,
		gl_dot3_rgba = 0x86af,
		gl_multisample_bit = 0x20000000,
	};

	void(*glActiveTexture) (GLenum texture) = nullptr;
	void(*glClientActiveTexture) (GLenum texture) = nullptr;
	void(*glCompressedTexImage1D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) = nullptr;
	void(*glCompressedTexImage2D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) = nullptr;
	void(*glCompressedTexImage3D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data) = nullptr;

	void(*glCompressedTexSubImage1D) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data) = nullptr;
	void(*glCompressedTexSubImage2D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	void(*glCompressedTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	void(*glGetCompressedTexImage) (GLenum target, GLint level, void *img) = nullptr;
	
	void(*glLoadTransposeMatrixd) (const GLdouble* m) = nullptr;
	void(*glLoadTransposeMatrixf) (const GLfloat* m) = nullptr;
	void(*glMultTransposeMatrixd) (const GLdouble* m) = nullptr;
	void(*glMultTransposeMatrixf) (const GLfloat* m) = nullptr;

	void(*glMultiTexCoord1d) (GLenum target, GLdouble s) = nullptr;
	void(*glMultiTexCoord1dv) (GLenum target, const GLdouble *v) = nullptr;
	void(*glMultiTexCoord1f) (GLenum target, GLfloat s) = nullptr;
	void(*glMultiTexCoord1fv) (GLenum target, const GLfloat *v) = nullptr;
	void(*glMultiTexCoord1i) (GLenum target, GLint s) = nullptr;
	void(*glMultiTexCoord1iv) (GLenum target, const GLint *v) = nullptr;
	void(*glMultiTexCoord1s) (GLenum target, GLshort s) = nullptr;
	void(*glMultiTexCoord1sv) (GLenum target, const GLshort *v) = nullptr;
	void(*glMultiTexCoord2d) (GLenum target, GLdouble s, GLdouble t) = nullptr;
	void(*glMultiTexCoord2dv) (GLenum target, const GLdouble *v) = nullptr;
	void(*glMultiTexCoord2f) (GLenum target, GLfloat s, GLfloat t) = nullptr;
	void(*glMultiTexCoord2fv) (GLenum target, const GLfloat *v) = nullptr;
	void(*glMultiTexCoord2i) (GLenum target, GLint s, GLint t) = nullptr;
	void(*glMultiTexCoord2iv) (GLenum target, const GLint *v) = nullptr;
	void(*glMultiTexCoord2s) (GLenum target, GLshort s, GLshort t) = nullptr;
	void(*glMultiTexCoord2sv) (GLenum target, const GLshort *v) = nullptr;
	void(*glMultiTexCoord3d) (GLenum target, GLdouble s, GLdouble t, GLdouble r) = nullptr;
	void(*glMultiTexCoord3dv) (GLenum target, const GLdouble *v) = nullptr;
	void(*glMultiTexCoord3f) (GLenum target, GLfloat s, GLfloat t, GLfloat r) = nullptr;
	void(*glMultiTexCoord3fv) (GLenum target, const GLfloat *v) = nullptr;
	void(*glMultiTexCoord3i) (GLenum target, GLint s, GLint t, GLint r) = nullptr;
	void(*glMultiTexCoord3iv) (GLenum target, const GLint *v) = nullptr;
	void(*glMultiTexCoord3s) (GLenum target, GLshort s, GLshort t, GLshort r) = nullptr;
	void(*glMultiTexCoord3sv) (GLenum target, const GLshort *v) = nullptr;
	void(*glMultiTexCoord4d) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) = nullptr;
	void(*glMultiTexCoord4dv) (GLenum target, const GLdouble *v) = nullptr;
	void(*glMultiTexCoord4f) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) = nullptr;
	void(*glMultiTexCoord4fv) (GLenum target, const GLfloat *v) = nullptr;
	void(*glMultiTexCoord4i) (GLenum target, GLint s, GLint t, GLint r, GLint q) = nullptr;
	void(*glMultiTexCoord4iv) (GLenum target, const GLint *v) = nullptr;
	void(*glMultiTexCoord4s) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) = nullptr;
	void(*glMultiTexCoord4sv) (GLenum target, const GLshort *v) = nullptr;
	void(*glSampleCoverage) (GLfloat value, GLboolean invert) = nullptr;

	//*< load OpenGL 1.3 extensions
	void Load1_3Extensions()
	{
		FetchProcAddress(glActiveTexture, "glActiveTexture");
		FetchProcAddress(glSampleCoverage, "glSampleCoverage");
		FetchProcAddress(glCompressedTexImage3D, "glCompressedTexImage3D");
		FetchProcAddress(glCompressedTexImage2D, "glCompressedTexImage2D");
		FetchProcAddress(glCompressedTexImage1D, "glCompressedTexImage1D");
		FetchProcAddress(glCompressedTexSubImage3D, "glCompressedTexSubImage3D");
		FetchProcAddress(glCompressedTexSubImage2D, "glCompressedTexSubImage2D");
		FetchProcAddress(glCompressedTexSubImage1D, "glCompressedTexSubImage1D");
		FetchProcAddress(glGetCompressedTexImage, "glGetCompressedTexImage");
		FetchProcAddress(glClientActiveTexture, "glClientActiveTexture");
		FetchProcAddress(glMultiTexCoord1d, "glMultiTexCoord1d");
		FetchProcAddress(glMultiTexCoord1dv, "glMultiTexCoord1dv");
		FetchProcAddress(glMultiTexCoord1f, "glMultiTexCoord1f");
		FetchProcAddress(glMultiTexCoord1fv, "glMultiTexCoord1fv");
		FetchProcAddress(glMultiTexCoord1i, "glMultiTexCoord1i");
		FetchProcAddress(glMultiTexCoord1iv, "glMultiTexCoord1iv");
		FetchProcAddress(glMultiTexCoord1s, "glMultiTexCoord1s");
		FetchProcAddress(glMultiTexCoord1sv, "glMultiTexCoord1sv");
		FetchProcAddress(glMultiTexCoord2d, "glMultiTexCoord2d");
		FetchProcAddress(glMultiTexCoord2dv, "glMultiTexCoord2dv");
		FetchProcAddress(glMultiTexCoord2f, "glMultiTexCoord2f");
		FetchProcAddress(glMultiTexCoord2fv, "glMultiTexCoord2fv");
		FetchProcAddress(glMultiTexCoord2i, "glMultiTexCoord2i");
		FetchProcAddress(glMultiTexCoord2iv, "glMultiTexCoord2iv");
		FetchProcAddress(glMultiTexCoord2s, "glMultiTexCoord2s");
		FetchProcAddress(glMultiTexCoord2sv, "glMultiTexCoord2sv");
		FetchProcAddress(glMultiTexCoord3d, "glMultiTexCoord3d");
		FetchProcAddress(glMultiTexCoord3dv, "glMultiTexCoord3dv");
		FetchProcAddress(glMultiTexCoord3f, "glMultiTexCoord3f");
		FetchProcAddress(glMultiTexCoord3fv, "glMultiTexCoord3fv");
		FetchProcAddress(glMultiTexCoord3i, "glMultiTexCoord3i");
		FetchProcAddress(glMultiTexCoord3iv, "glMultiTexCoord3iv");
		FetchProcAddress(glMultiTexCoord3s, "glMultiTexCoord3s");
		FetchProcAddress(glMultiTexCoord3sv, "glMultiTexCoord3sv");
		FetchProcAddress(glMultiTexCoord4d, "glMultiTexCoord4d");
		FetchProcAddress(glMultiTexCoord4dv, "glMultiTexCoord4dv");
		FetchProcAddress(glMultiTexCoord4f, "glMultiTexCoord4f");
		FetchProcAddress(glMultiTexCoord4fv, "glMultiTexCoord4fv");
		FetchProcAddress(glMultiTexCoord4i, "glMultiTexCoord4i");
		FetchProcAddress(glMultiTexCoord4iv, "glMultiTexCoord4iv");
		FetchProcAddress(glMultiTexCoord4s, "glMultiTexCoord4s");
		FetchProcAddress(glMultiTexCoord4sv, "glMultiTexCoord4sv");
		FetchProcAddress(glLoadTransposeMatrixf, "glLoadTransposeMatrixf");
		FetchProcAddress(glLoadTransposeMatrixd, "glLoadTransposeMatrixd");
		FetchProcAddress(glMultTransposeMatrixf, "glMultTransposeMatrixf");
		FetchProcAddress(glMultTransposeMatrixd, "glMultTransposeMatrixd");
	}

#pragma endregion OpenGL1_3 Extensions
	
	//OpenGL 1.4 Extensions
#pragma region OpenGL1_4

	enum openGL1_4_t
	{
		gl_blend_dst_rgb = 0x80c8,
		gl_blend_src_rgb = 0x80c9,
		gl_blend_dst_alpha = 0x80ca,
		gl_blend_src_alpha = 0x80cb,
		gl_point_size_min = 0x8126,
		gl_point_size_max = 0x8127,
		gl_point_fade_threshold_size = 0x8128,
		gl_point_distance_attenuation = 0x8129,
		gl_generate_mipmap = 0x8191,
		gl_generate_mipmap_hint = 0x8192,
		gl_depth_component16 = 0x81a5,
		gl_depth_component24 = 0x81a6,
		gl_depth_component32 = 0x81a7,
		gl_mirrored_repeat = 0x8370,
		gl_fog_coordinate_source = 0x8450,
		gl_fog_coordinate = 0x8451,
		gl_fragment_depth = 0x8452,
		gl_current_fog_coordinate = 0x8453,
		gl_fog_coordinate_array_type = 0x8454,
		gl_fog_coordinate_array_stride = 0x8455,
		gl_fog_coordinate_array_pointer = 0x8456,
		gl_fog_coordinate_array = 0x8457,
		gl_color_sum = 0x8458,
		gl_current_secondary_color = 0x8459,
		gl_secondary_color_array_size = 0x845a,
		gl_secondary_color_array_type = 0x845b,
		gl_secondary_color_array_stride = 0x845c,
		gl_secondary_color_array_pointer = 0x845d,
		gl_secondary_color_array = 0x845e,
		gl_max_texture_lod_bias = 0x84fd,
		gl_texture_filter_control = 0x8500,
		gl_texture_lod_bias = 0x8501,
		gl_incr_wrap = 0x8507,
		gl_decr_wrap = 0x8508,
		gl_texture_depth_size = 0x884a,
		gl_depth_texture_mode = 0x884b,
		gl_texture_compare_mode = 0x884c,
		gl_texture_compare_func = 0x884d,
		gl_compare_r_to_texture = 0x884e,
	};

	void(*glBlendColor) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = nullptr;
	void(*glBlendEquation) (GLenum mode) = nullptr;
	void(*glBlendFuncSeparate) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) = nullptr;
	void(*glMultiDrawArrays) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount) = nullptr;
	void(*glMultiDrawElements) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount) = nullptr;
	void(*glPointParameterf) (GLenum pname, GLfloat param) = nullptr;
	void(*glPointParameterfv) (GLenum pname, const GLfloat *params) = nullptr;
	void(*glPointParameteri) (GLenum pname, GLint param) = nullptr;
	void(*glPointParameteriv) (GLenum pname, const GLint *params) = nullptr;
	void(*glFogCoordf) (GLfloat coord) = nullptr;
	void(*glFogCoordfv) (const GLfloat *coord) = nullptr;
	void(*glFogCoordd) (GLdouble coord) = nullptr;
	void(*glFogCoorddv) (const GLdouble *coord) = nullptr;
	void(*glFogCoordPointer) (GLenum type, GLsizei stride, const void *pointer) = nullptr;
	void(*glSecondaryColor3b) (GLbyte red, GLbyte green, GLbyte blue) = nullptr;
	void(*glSecondaryColor3bv) (const GLbyte *v) = nullptr;
	void(*glSecondaryColor3d) (GLdouble red, GLdouble green, GLdouble blue) = nullptr;
	void(*glSecondaryColor3dv) (const GLdouble *v) = nullptr;
	void(*glSecondaryColor3f) (GLfloat red, GLfloat green, GLfloat blue) = nullptr;
	void(*glSecondaryColor3fv) (const GLfloat *v) = nullptr;
	void(*glSecondaryColor3i) (GLint red, GLint green, GLint blue) = nullptr;
	void(*glSecondaryColor3iv) (const GLint *v) = nullptr;
	void(*glSecondaryColor3s) (GLshort red, GLshort green, GLshort blue) = nullptr;
	void(*glSecondaryColor3sv) (const GLshort *v) = nullptr;
	void(*glSecondaryColor3ub) (GLubyte red, GLubyte green, GLubyte blue) = nullptr;
	void(*glSecondaryColor3ubv) (const GLubyte *v) = nullptr;
	void(*glSecondaryColor3ui) (GLuint red, GLuint green, GLuint blue) = nullptr;
	void(*glSecondaryColor3uiv) (const GLuint *v) = nullptr;
	void(*glSecondaryColor3us) (GLushort red, GLushort green, GLushort blue) = nullptr;
	void(*glSecondaryColor3usv) (const GLushort *v) = nullptr;
	void(*glSecondaryColorPointer) (GLint size, GLenum type, GLsizei stride, const void *pointer) = nullptr;
	void(*glWindowPos2d) (GLdouble x, GLdouble y) = nullptr;
	void(*glWindowPos2dv) (const GLdouble *v) = nullptr;
	void(*glWindowPos2f) (GLfloat x, GLfloat y) = nullptr;
	void(*glWindowPos2fv) (const GLfloat *v) = nullptr;
	void(*glWindowPos2i) (GLint x, GLint y) = nullptr;
	void(*glWindowPos2iv) (const GLint *v) = nullptr;
	void(*glWindowPos2s) (GLshort x, GLshort y) = nullptr;
	void(*glWindowPos2sv) (const GLshort *v) = nullptr;
	void(*glWindowPos3d) (GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void(*glWindowPos3dv) (const GLdouble *v) = nullptr;
	void(*glWindowPos3f) (GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void(*glWindowPos3fv) (const GLfloat *v) = nullptr;
	void(*glWindowPos3i) (GLint x, GLint y, GLint z) = nullptr;
	void(*glWindowPos3iv) (const GLint *v) = nullptr;
	void(*glWindowPos3s) (GLshort x, GLshort y, GLshort z) = nullptr;
	void(*glWindowPos3sv) (const GLshort *v) = nullptr;

	//*< load OpenGL 1.4 extensions
	void Load1_4Extensions()
	{
		FetchProcAddress(glBlendFuncSeparate, "glBlendFuncSeparate");
		FetchProcAddress(glMultiDrawArrays, "glMultiDrawArrays");
		FetchProcAddress(glMultiDrawElements, "glMultiDrawElements");
		FetchProcAddress(glPointParameterf, "glPointParameterf");
		FetchProcAddress(glPointParameterfv, "glPointParameterfv");
		FetchProcAddress(glPointParameteri, "glPointParameteri");
		FetchProcAddress(glPointParameteriv, "glPointParameteriv");
		FetchProcAddress(glFogCoordf, "glFogCoordf");
		FetchProcAddress(glFogCoordfv, "glFogCoordfv");
		FetchProcAddress(glFogCoordd, "glFogCoordd");
		FetchProcAddress(glFogCoorddv, "glFogCoorddv");
		FetchProcAddress(glFogCoordPointer, "glFogCoordPointer");
		FetchProcAddress(glSecondaryColor3b, "glSecondaryColor3b");
		FetchProcAddress(glSecondaryColor3bv, "glSecondaryColor3bv");
		FetchProcAddress(glSecondaryColor3d, "glSecondaryColor3d");
		FetchProcAddress(glSecondaryColor3dv, "glSecondaryColor3dv");
		FetchProcAddress(glSecondaryColor3f, "glSecondaryColor3f");
		FetchProcAddress(glSecondaryColor3fv, "glSecondaryColor3fv");
		FetchProcAddress(glSecondaryColor3i, "glSecondaryColor3i");
		FetchProcAddress(glSecondaryColor3iv, "glSecondaryColor3iv");
		FetchProcAddress(glSecondaryColor3s, "glSecondaryColor3s");
		FetchProcAddress(glSecondaryColor3sv, "glSecondaryColor3sv");
		FetchProcAddress(glSecondaryColor3ub, "glSecondaryColor3ub");
		FetchProcAddress(glSecondaryColor3ubv, "glSecondaryColor3ubv");
		FetchProcAddress(glSecondaryColor3ui, "glSecondaryColor3ui");
		FetchProcAddress(glSecondaryColor3uiv, "glSecondaryColor3uiv");
		FetchProcAddress(glSecondaryColor3us, "glSecondaryColor3us");
		FetchProcAddress(glSecondaryColor3usv, "glSecondaryColor3usv");
		FetchProcAddress(glSecondaryColorPointer, "glSecondaryColorPointer");
		FetchProcAddress(glWindowPos2d, "glWindowPos2d");
		FetchProcAddress(glWindowPos2dv, "glWindowPos2dv");
		FetchProcAddress(glWindowPos2f, "glWindowPos2f");
		FetchProcAddress(glWindowPos2fv, "glWindowPos2fv");
		FetchProcAddress(glWindowPos2i, "glWindowPos2i");
		FetchProcAddress(glWindowPos2iv, "glWindowPos2iv");
		FetchProcAddress(glWindowPos2s, "glWindowPos2s");
		FetchProcAddress(glWindowPos2sv, "glWindowPos2sv");
		FetchProcAddress(glWindowPos3d, "glWindowPos3d");
		FetchProcAddress(glWindowPos3dv, "glWindowPos3dv");
		FetchProcAddress(glWindowPos3f, "glWindowPos3f");
		FetchProcAddress(glWindowPos3fv, "glWindowPos3fv");
		FetchProcAddress(glWindowPos3i, "glWindowPos3i");
		FetchProcAddress(glWindowPos3iv, "glWindowPos3iv");
		FetchProcAddress(glWindowPos3s, "glWindowPos3s");
		FetchProcAddress(glWindowPos3sv, "glWindowPos3sv");
		FetchProcAddress(glBlendColor, "glBlendColor");
		FetchProcAddress(glBlendEquation, "glBlendEquation");
	}
#pragma endregion OpenGL1_4 Extensions

	//OpenGL 1.5 Extensions
#pragma region OpenGL1_5

	using GLsizeiptr = ptrdiff_t;
	using GLintptr = ptrdiff_t;

	enum openGL1_5_t
	{
		gl_buffer_size = 0x8764,
		gl_buffer_usage = 0x8765,
		gl_query_counter_bits = 0x8864,
		gl_current_query = 0x8865,
		gl_query_result = 0x8866,
		gl_query_result_available = 0x8867,
		gl_array_buffer = 0x8892,
		gl_element_array_buffer = 0x8893,
		gl_array_buffer_binding = 0x8894,
		gl_element_array_buffer_binding = 0x8895,
		gl_vertex_array_buffer_binding = 0x8896,
		gl_normal_array_buffer_binding = 0x8897,
		gl_color_array_buffer_binding = 0x8898,
		gl_index_array_buffer_binding = 0x8899,
		gl_texture_coord_array_buffer_binding = 0x889a,
		gl_edge_flag_array_buffer_binding = 0x889b,
		gl_secondary_color_array_buffer_binding = 0x889c,
		gl_fog_coordinate_array_buffer_binding = 0x889d,
		gl_weight_array_buffer_binding = 0x889e,
		gl_vertex_attrib_array_buffer_binding = 0x889f,
		gl_read_only = 0x88b8,
		gl_write_only = 0x88b9,
		gl_read_write = 0x88ba,
		gl_buffer_access = 0x88bb,
		gl_buffer_mapped = 0x88bc,
		gl_buffer_map_pointer = 0x88bd,
		gl_stream_draw = 0x88e0,
		gl_stream_read = 0x88e1,
		gl_stream_copy = 0x88e2,
		gl_static_draw = 0x88e4,
		gl_static_read = 0x88e5,
		gl_static_copy = 0x88e6,
		gl_dynamic_draw = 0x88e8,
		gl_dynamic_read = 0x88e9,
		gl_dynamic_copy = 0x88ea,
		gl_samples_passed = 0x8914,
		//what is the point of this?
		gl_current_fog_coord = gl_current_fog_coordinate,
		gl_fog_coord = gl_fog_coordinate,
		gl_fog_coord_array = gl_fog_coordinate_array,
		gl_fog_coord_array_buffer_binding = gl_fog_coordinate_array_buffer_binding,
		gl_fog_coord_array_pointer = gl_fog_coordinate_array_pointer,
		gl_fog_coord_array_stride = gl_fog_coordinate_array_stride,
		gl_fog_coord_array_type = gl_fog_coordinate_array_type,
		gl_fog_coord_src = gl_fog_coordinate_source,
		gl_src0_alpha = gl_source0_alpha,
		gl_src0_rgb = gl_source0_rgb,
		gl_src1_alpha = gl_source1_alpha,
		gl_src1_rgb = gl_source1_rgb,
		gl_src2_alpha = gl_source2_alpha,
		gl_src2_rgb = gl_source2_rgb,
	};

	void(*glGenQueries) (GLsizei n, GLuint *ids);
	void(*glDeleteQueries) (GLsizei n, const GLuint *ids);
	GLboolean(*glIsQuery) (GLuint id);
	void(*glBeginQuery) (GLenum target, GLuint id);
	void(*glEndQuery) (GLenum target);
	void(*glGetQueryiv) (GLenum target, GLenum pname, GLint *params);
	void(*glGetQueryObjectiv) (GLuint id, GLenum pname, GLint *params);
	void(*glGetQueryObjectuiv) (GLuint id, GLenum pname, GLuint *params);
	void(*glBindBuffer) (GLenum target, GLuint buffer);
	void(*glDeleteBuffers) (GLsizei n, const GLuint *buffers);
	void(*glGenBuffers) (GLsizei n, GLuint *buffers);
	GLboolean(*glIsBuffer) (GLuint buffer);
	void(*glBufferData) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
	void(*glBufferSubData) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
	void(*glGetBufferSubData) (GLenum target, GLintptr offset, GLsizeiptr size, void *data);
	void * (*glMapBuffer) (GLenum target, GLenum access);
	GLboolean(*glUnmapBuffer) (GLenum target);
	void(*glGetBufferParameteriv) (GLenum target, GLenum pname, GLint *params);
	void(*glGetBufferPointerv) (GLenum target, GLenum pname, void **params);

	//*< load OpenGL 1.5 extensions
	void Load1_5Extensions()
	{
		FetchProcAddress(glGenQueries, "glGenQueries");
		FetchProcAddress(glDeleteQueries, "glDeleteQueries");
		FetchProcAddress(glIsQuery, "glIsQuery");
		FetchProcAddress(glBeginQuery, "glBeginQuery");
		FetchProcAddress(glEndQuery, "glEndQuery");
		FetchProcAddress(glGetQueryiv, "glGetQueryiv");
		FetchProcAddress(glGetQueryObjectiv, "glGetQueryObjectiv");
		FetchProcAddress(glGetQueryObjectuiv, "glGetQueryObjectuiv");
		FetchProcAddress(glBindBuffer, "glBindBuffer");
		FetchProcAddress(glDeleteBuffers, "glDeleteBuffers");
		FetchProcAddress(glGenBuffers, "glGenBuffers");
		FetchProcAddress(glIsBuffer, "glIsBuffer");
		FetchProcAddress(glBufferData, "glBufferData");
		FetchProcAddress(glBufferSubData, "glBufferSubData");
		FetchProcAddress(glGetBufferSubData, "glGetBufferSubData");
		FetchProcAddress(glMapBuffer, "glMapBuffer");
		FetchProcAddress(glUnmapBuffer, "glUnmapBuffer");
		FetchProcAddress(glGetBufferParameteriv, "glGetBufferParameteriv");
		FetchProcAddress(glGetBufferPointerv, "glGetBufferPointerv");
	}
#pragma endregion OpenGL1_5 Extensions

	//OpenGL 2.0 Extensions
#pragma region OpenGL2_0

	using GLchar = char;
	
	enum openGL2_0_t
	{
		gl_blend_equation_rgb = 0x8009,
		gl_vertex_attrib_array_enabled = 0x8622,
		gl_vertex_attrib_array_size = 0x8623,
		gl_vertex_attrib_array_stride = 0x8624,
		gl_vertex_attrib_array_type = 0x8625,
		gl_current_vertex_attrib = 0x8626,
		gl_vertex_program_point_size = 0x8642,
		gl_vertex_attrib_array_pointer = 0x8645,
		gl_stencil_back_func = 0x8800,
		gl_stencil_back_fail = 0x8801,
		gl_stencil_back_pass_depth_fail = 0x8802,
		gl_stencil_back_pass_depth_pass = 0x8803,
		gl_max_draw_buffers = 0x8824,
		gl_draw_buffer0 = 0x8825,
		gl_draw_buffer1 = 0x8826,
		gl_draw_buffer2 = 0x8827,
		gl_draw_buffer3 = 0x8828,
		gl_draw_buffer4 = 0x8829,
		gl_draw_buffer5 = 0x882a,
		gl_draw_buffer6 = 0x882b,
		gl_draw_buffer7 = 0x882c,
		gl_draw_buffer8 = 0x882d,
		gl_draw_buffer9 = 0x882e,
		gl_draw_buffer10 = 0x882f,
		gl_draw_buffer11 = 0x8830,
		gl_draw_buffer12 = 0x8831,
		gl_draw_buffer13 = 0x8832,
		gl_draw_buffer14 = 0x8833,
		gl_draw_buffer15 = 0x8834,
		gl_blend_equation_alpha = 0x883d,
		gl_max_vertex_attribs = 0x8869,
		gl_vertex_attrib_array_normalized = 0x886a,
		gl_max_texture_image_units = 0x8872,
		gl_fragment_shader = 0x8b30,
		gl_vertex_shader = 0x8b31,
		gl_max_fragment_uniform_components = 0x8b49,
		gl_max_vertex_uniform_components = 0x8b4a,
		gl_max_varying_floats = 0x8b4b,
		gl_max_vertex_texture_image_units = 0x8b4c,
		gl_max_combined_texture_image_units = 0x8b4d,
		gl_shader_type = 0x8b4f,
		gl_float_vec2 = 0x8b50,
		gl_float_vec3 = 0x8b51,
		gl_float_vec4 = 0x8b52,
		gl_int_vec2 = 0x8b53,
		gl_int_vec3 = 0x8b54,
		gl_int_vec4 = 0x8b55,
		gl_bool = 0x8b56,
		gl_bool_vec2 = 0x8b57,
		gl_bool_vec3 = 0x8b58,
		gl_bool_vec4 = 0x8b59,
		gl_float_mat2 = 0x8b5a,
		gl_float_mat3 = 0x8b5b,
		gl_float_mat4 = 0x8b5c,
		gl_sampler_1d = 0x8b5d,
		gl_sampler_2d = 0x8b5e,
		gl_sampler_3d = 0x8b5f,
		gl_sampler_cube = 0x8b60,
		gl_sampler_1d_shadow = 0x8b61,
		gl_sampler_2d_shadow = 0x8b62,
		gl_delete_status = 0x8b80,
		gl_compile_status = 0x8b81,
		gl_link_status = 0x8b82,
		gl_validate_status = 0x8b83,
		gl_info_log_length = 0x8b84,
		gl_attached_shaders = 0x8b85,
		gl_active_uniforms = 0x8b86,
		gl_active_uniform_max_length = 0x8b87,
		gl_shader_source_length = 0x8b88,
		gl_active_attributes = 0x8b89,
		gl_active_attribute_max_length = 0x8b8a,
		gl_fragment_shader_derivative_hint = 0x8b8b,
		gl_shading_language_version = 0x8b8c,
		gl_current_program = 0x8b8d,
		gl_point_sprite_coord_origin = 0x8ca0,
		gl_lower_left = 0x8ca1,
		gl_upper_left = 0x8ca2,
		gl_stencil_back_ref = 0x8ca3,
		gl_stencil_back_value_mask = 0x8ca4,
		gl_stencil_back_writemask = 0x8ca5,
		gl_vertex_program_two_side = 0x8643,
		gl_point_sprite = 0x8861,
		gl_coord_replace = 0x8862,
		gl_max_texture_coords = 0x8871
	};
	
	void(*glBlendEquationSeparate) (GLenum modeRGB, GLenum modeAlpha) = nullptr;
	void(*glDrawBuffers) (GLsizei n, const GLenum *bufs) = nullptr;
	void(*glStencilOpSeparate) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) = nullptr;
	void(*glStencilFuncSeparate) (GLenum face, GLenum func, GLint ref, GLuint mask) = nullptr;
	void(*glStencilMaskSeparate) (GLenum face, GLuint mask) = nullptr;
	void(*glAttachShader) (GLuint program, GLuint shader) = nullptr;
	void(*glBindAttribLocation) (GLuint program, GLuint index, const GLchar *name) = nullptr;
	void(*glCompileShader) (GLuint shader) = nullptr;
	GLuint(*glCreateProgram) (void) = nullptr;
	GLuint(*glCreateShader) (GLenum type) = nullptr;
	void(*glDeleteProgram) (GLuint program) = nullptr;
	void(*glDeleteShader) (GLuint shader) = nullptr;
	void(*glDetachShader) (GLuint program, GLuint shader) = nullptr;
	void(*glDisableVertexAttribArray) (GLuint index) = nullptr;
	void(*glEnableVertexAttribArray) (GLuint index) = nullptr;
	void(*glGetActiveAttrib) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) = nullptr;
	void(*glGetActiveUniform) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) = nullptr;
	void(*glGetAttachedShaders) (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders) = nullptr;
	GLint(*glGetAttribLocation) (GLuint program, const GLchar *name) = nullptr;
	void(*glGetProgramiv) (GLuint program, GLenum pname, GLint *params) = nullptr;
	void(*glGetProgramInfoLog) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) = nullptr;
	void(*glGetShaderiv) (GLuint shader, GLenum pname, GLint *params) = nullptr;
	void(*glGetShaderInfoLog) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) = nullptr;
	void(*glGetShaderSource) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source) = nullptr;
	GLint(*glGetUniformLocation) (GLuint program, const GLchar *name) = nullptr;
	void(*glGetUniformfv) (GLuint program, GLint location, GLfloat *params) = nullptr;
	void(*glGetUniformiv) (GLuint program, GLint location, GLint *params) = nullptr;
	void(*glGetVertexAttribdv) (GLuint index, GLenum pname, GLdouble *params) = nullptr;
	void(*glGetVertexAttribfv) (GLuint index, GLenum pname, GLfloat *params) = nullptr;
	void(*glGetVertexAttribiv) (GLuint index, GLenum pname, GLint *params) = nullptr;
	void(*glGetVertexAttribPointerv) (GLuint index, GLenum pname, void **pointer) = nullptr;
	GLboolean(*glIsProgram) (GLuint program) = nullptr;
	GLboolean(*glIsShader) (GLuint shader) = nullptr;
	void(*glLinkProgram) (GLuint program) = nullptr;
	void(*glShaderSource) (GLuint shader, GLsizei count, const GLchar** string, const GLint *length) = nullptr;
	void(*glUseProgram) (GLuint program) = nullptr;
	void(*glUniform1f) (GLint location, GLfloat v0) = nullptr;
	void(*glUniform2f) (GLint location, GLfloat v0, GLfloat v1) = nullptr;
	void(*glUniform3f) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2) = nullptr;
	void(*glUniform4f) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) = nullptr;
	void(*glUniform1i) (GLint location, GLint v0) = nullptr;
	void(*glUniform2i) (GLint location, GLint v0, GLint v1) = nullptr;
	void(*glUniform3i) (GLint location, GLint v0, GLint v1, GLint v2) = nullptr;
	void(*glUniform4i) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3) = nullptr;
	void(*glUniform1fv) (GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void(*glUniform2fv) (GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void(*glUniform3fv) (GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void(*glUniform4fv) (GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void(*glUniform1iv) (GLint location, GLsizei count, const GLint *value) = nullptr;
	void(*glUniform2iv) (GLint location, GLsizei count, const GLint *value) = nullptr;
	void(*glUniform3iv) (GLint location, GLsizei count, const GLint *value) = nullptr;
	void(*glUniform4iv) (GLint location, GLsizei count, const GLint *value) = nullptr;
	void(*glUniformMatrix2fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix3fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glValidateProgram) (GLuint program) = nullptr;
	void(*glVertexAttrib1d) (GLuint index, GLdouble x) = nullptr;
	void(*glVertexAttrib1dv) (GLuint index, const GLdouble *v) = nullptr;
	void(*glVertexAttrib1f) (GLuint index, GLfloat x) = nullptr;
	void(*glVertexAttrib1fv) (GLuint index, const GLfloat *v) = nullptr;
	void(*glVertexAttrib1s) (GLuint index, GLshort x) = nullptr;
	void(*glVertexAttrib1sv) (GLuint index, const GLshort *v) = nullptr;
	void(*glVertexAttrib2d) (GLuint index, GLdouble x, GLdouble y) = nullptr;
	void(*glVertexAttrib2dv) (GLuint index, const GLdouble *v) = nullptr;
	void(*glVertexAttrib2f) (GLuint index, GLfloat x, GLfloat y) = nullptr;
	void(*glVertexAttrib2fv) (GLuint index, const GLfloat *v) = nullptr;
	void(*glVertexAttrib2s) (GLuint index, GLshort x, GLshort y) = nullptr;
	void(*glVertexAttrib2sv) (GLuint index, const GLshort *v) = nullptr;
	void(*glVertexAttrib3d) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void(*glVertexAttrib3dv) (GLuint index, const GLdouble *v) = nullptr;
	void(*glVertexAttrib3f) (GLuint index, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void(*glVertexAttrib3fv) (GLuint index, const GLfloat *v) = nullptr;
	void(*glVertexAttrib3s) (GLuint index, GLshort x, GLshort y, GLshort z) = nullptr;
	void(*glVertexAttrib3sv) (GLuint index, const GLshort *v) = nullptr;
	void(*glVertexAttrib4Nbv) (GLuint index, const GLbyte *v) = nullptr;
	void(*glVertexAttrib4Niv) (GLuint index, const GLint *v) = nullptr;
	void(*glVertexAttrib4Nsv) (GLuint index, const GLshort *v) = nullptr;
	void(*glVertexAttrib4Nub) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) = nullptr;
	void(*glVertexAttrib4Nubv) (GLuint index, const GLubyte *v) = nullptr;
	void(*glVertexAttrib4Nuiv) (GLuint index, const GLuint *v) = nullptr;
	void(*glVertexAttrib4Nusv) (GLuint index, const GLushort *v) = nullptr;
	void(*glVertexAttrib4bv) (GLuint index, const GLbyte *v) = nullptr;
	void(*glVertexAttrib4d) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void(*glVertexAttrib4dv) (GLuint index, const GLdouble *v) = nullptr;
	void(*glVertexAttrib4f) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void(*glVertexAttrib4fv) (GLuint index, const GLfloat *v) = nullptr;
	void(*glVertexAttrib4iv) (GLuint index, const GLint *v) = nullptr;
	void(*glVertexAttrib4s) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
	void(*glVertexAttrib4sv) (GLuint index, const GLshort *v) = nullptr;
	void(*glVertexAttrib4ubv) (GLuint index, const GLubyte *v) = nullptr;
	void(*glVertexAttrib4uiv) (GLuint index, const GLuint *v) = nullptr;
	void(*glVertexAttrib4usv) (GLuint index, const GLushort *v) = nullptr;
	void(*glVertexAttribPointer) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) = nullptr;
	
	//*< load OpenGL 2.0 extensions
	void Load2_0Extensions()
	{
		FetchProcAddress(glBlendEquationSeparate, "glBlendEquationSeparate");
		FetchProcAddress(glDrawBuffers, "glDrawBuffers");
		FetchProcAddress(glStencilOpSeparate, "glStencilOpSeparate");
		FetchProcAddress(glStencilFuncSeparate, "glStencilFuncSeparate");
		FetchProcAddress(glStencilMaskSeparate, "glStencilMaskSeparate");
		FetchProcAddress(glAttachShader, "glAttachShader");
		FetchProcAddress(glBindAttribLocation, "glBindAttribLocation");
		FetchProcAddress(glCompileShader, "glCompileShader");
		FetchProcAddress(glCreateProgram, "glCreateProgram");
		FetchProcAddress(glCreateShader, "glCreateShader");
		FetchProcAddress(glDeleteProgram, "glDeleteProgram");
		FetchProcAddress(glDeleteShader, "glDeleteShader");
		FetchProcAddress(glDetachShader, "glDetachShader");
		FetchProcAddress(glDisableVertexAttribArray, "glDisableVertexAttribArray");
		FetchProcAddress(glEnableVertexAttribArray, "glEnableVertexAttribArray");
		FetchProcAddress(glGetActiveAttrib, "glGetActiveAttrib");
		FetchProcAddress(glGetActiveUniform, "glGetActiveUniform");
		FetchProcAddress(glGetAttachedShaders, "glGetAttachedShaders");
		FetchProcAddress(glGetAttribLocation, "glGetAttribLocation");
		FetchProcAddress(glGetProgramiv, "glGetProgramiv");
		FetchProcAddress(glGetProgramInfoLog, "glGetProgramInfoLog");
		FetchProcAddress(glGetShaderiv, "glGetShaderiv");
		FetchProcAddress(glGetShaderInfoLog, "glGetShaderInfoLog");
		FetchProcAddress(glGetShaderSource, "glGetShaderSource");
		FetchProcAddress(glGetUniformLocation, "glGetUniformLocation");
		FetchProcAddress(glGetUniformfv, "glGetUniformfv");
		FetchProcAddress(glGetUniformiv, "glGetUniformiv");
		FetchProcAddress(glGetVertexAttribdv, "glGetVertexAttribdv");
		FetchProcAddress(glGetVertexAttribfv, "glGetVertexAttribfv");
		FetchProcAddress(glGetVertexAttribiv, "glGetVertexAttribiv");
		FetchProcAddress(glGetVertexAttribPointerv, "glGetVertexAttribPointerv");
		FetchProcAddress(glIsProgram, "glIsProgram");
		FetchProcAddress(glIsShader, "glIsShader");
		FetchProcAddress(glLinkProgram, "glLinkProgram");
		FetchProcAddress(glShaderSource, "glShaderSource");
		FetchProcAddress(glUseProgram, "glUseProgram");
		FetchProcAddress(glUniform1f, "glUniform1f");
		FetchProcAddress(glUniform2f, "glUniform2f");
		FetchProcAddress(glUniform3f, "glUniform3f");
		FetchProcAddress(glUniform4f, "glUniform4f");
		FetchProcAddress(glUniform1i, "glUniform1i");
		FetchProcAddress(glUniform2i, "glUniform2i");
		FetchProcAddress(glUniform3i, "glUniform3i");
		FetchProcAddress(glUniform4i, "glUniform4i");
		FetchProcAddress(glUniform1fv, "glUniform1fv");
		FetchProcAddress(glUniform2fv, "glUniform2fv");
		FetchProcAddress(glUniform3fv, "glUniform3fv");
		FetchProcAddress(glUniform4fv, "glUniform4fv");
		FetchProcAddress(glUniform1iv, "glUniform1iv");
		FetchProcAddress(glUniform2iv, "glUniform2iv");
		FetchProcAddress(glUniform3iv, "glUniform3iv");
		FetchProcAddress(glUniform4iv, "glUniform4iv");
		FetchProcAddress(glUniformMatrix2fv, "glUniformMatrix2fv");
		FetchProcAddress(glUniformMatrix3fv, "glUniformMatrix3fv");
		FetchProcAddress(glUniformMatrix4fv, "glUniformMatrix4fv");
		FetchProcAddress(glValidateProgram, "glValidateProgram");
		FetchProcAddress(glVertexAttrib1d, "glVertexAttrib1d");
		FetchProcAddress(glVertexAttrib1dv, "glVertexAttrib1dv");
		FetchProcAddress(glVertexAttrib1f, "glVertexAttrib1f");
		FetchProcAddress(glVertexAttrib1fv, "glVertexAttrib1fv");
		FetchProcAddress(glVertexAttrib1s, "glVertexAttrib1s");
		FetchProcAddress(glVertexAttrib1sv, "glVertexAttrib1sv");
		FetchProcAddress(glVertexAttrib2d, "glVertexAttrib2d");
		FetchProcAddress(glVertexAttrib2dv, "glVertexAttrib2dv");
		FetchProcAddress(glVertexAttrib2f, "glVertexAttrib2f");
		FetchProcAddress(glVertexAttrib2fv, "glVertexAttrib2fv");
		FetchProcAddress(glVertexAttrib2s, "glVertexAttrib2s");
		FetchProcAddress(glVertexAttrib2sv, "glVertexAttrib2sv");
		FetchProcAddress(glVertexAttrib3d, "glVertexAttrib3d");
		FetchProcAddress(glVertexAttrib3dv, "glVertexAttrib3dv");
		FetchProcAddress(glVertexAttrib3f, "glVertexAttrib3f");
		FetchProcAddress(glVertexAttrib3fv, "glVertexAttrib3fv");
		FetchProcAddress(glVertexAttrib3s, "glVertexAttrib3s");
		FetchProcAddress(glVertexAttrib3sv, "glVertexAttrib3sv");
		FetchProcAddress(glVertexAttrib4Nbv, "glVertexAttrib4Nbv");
		FetchProcAddress(glVertexAttrib4Niv, "glVertexAttrib4Niv");
		FetchProcAddress(glVertexAttrib4Nsv, "glVertexAttrib4Nsv");
		FetchProcAddress(glVertexAttrib4Nub, "glVertexAttrib4Nub");
		FetchProcAddress(glVertexAttrib4Nubv, "glVertexAttrib4Nubv");
		FetchProcAddress(glVertexAttrib4Nuiv, "glVertexAttrib4Nuiv");
		FetchProcAddress(glVertexAttrib4Nusv, "glVertexAttrib4Nusv");
		FetchProcAddress(glVertexAttrib4bv, "glVertexAttrib4bv");
		FetchProcAddress(glVertexAttrib4d, "glVertexAttrib4d");
		FetchProcAddress(glVertexAttrib4dv, "glVertexAttrib4dv");
		FetchProcAddress(glVertexAttrib4f, "glVertexAttrib4f");
		FetchProcAddress(glVertexAttrib4fv, "glVertexAttrib4fv");
		FetchProcAddress(glVertexAttrib4iv, "glVertexAttrib4iv");
		FetchProcAddress(glVertexAttrib4s, "glVertexAttrib4s");
		FetchProcAddress(glVertexAttrib4sv, "glVertexAttrib4sv");
		FetchProcAddress(glVertexAttrib4ubv, "glVertexAttrib4ubv");
		FetchProcAddress(glVertexAttrib4uiv, "glVertexAttrib4uiv");
		FetchProcAddress(glVertexAttrib4usv, "glVertexAttrib4usv");
		FetchProcAddress(glVertexAttribPointer, "glVertexAttribPointer");
	}
	
#pragma endregion OpenGL2_0 Extensions

	//OpenGL 2.1 Extensions
#pragma region OpenGL2_1

	enum openGL2_1_t
	{
		gl_pixel_pack_buffer = 0x88eb,
		gl_pixel_unpack_buffer = 0x88ec,
		gl_pixel_pack_buffer_binding = 0x88ed,
		gl_pixel_unpack_buffer_binding = 0x88ef,
		gl_float_mat2x3 = 0x8b65,
		gl_float_mat2x4 = 0x8b66,
		gl_float_mat3x2 = 0x8b67,
		gl_float_mat3x4 = 0x8b68,
		gl_float_mat4x2 = 0x8b69,
		gl_float_mat4x3 = 0x8b6a,
		gl_srgb = 0x8c40,
		gl_srgb8 = 0x8c41,
		gl_srgb_alpha = 0x8c42,
		gl_srgb8_alpha8 = 0x8c43,
		gl_compressed_srgb = 0x8c48,
		gl_compressed_srgb_alpha = 0x8c49,
		gl_current_raster_secondary_color = 0x845f,
		gl_sluminance_alpha = 0x8c44,
		gl_sluminance8_alpha8 = 0x8c45,
		gl_sluminance = 0x8c46,
		gl_sluminance8 = 0x8c47,
		gl_compressed_sluminance = 0x8c4a,
		gl_compressed_sluminance_alpha = 0x8c4b,
	};

	void(*glUniformMatrix2x3fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix3x2fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix2x4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix4x2fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix3x4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix4x3fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;

	//*< load OpenGL 2.1 extensions
	void Load2_1Extensions()
	{
		FetchProcAddress(glUniformMatrix2x3fv, "glUniformMatrix2x3fv");
		FetchProcAddress(glUniformMatrix3x2fv, "glUniformMatrix3x2fv");
		FetchProcAddress(glUniformMatrix2x4fv, "glUniformMatrix2x4fv");
		FetchProcAddress(glUniformMatrix4x2fv, "glUniformMatrix4x2fv");
		FetchProcAddress(glUniformMatrix3x4fv, "glUniformMatrix3x4fv");
		FetchProcAddress(glUniformMatrix4x3fv, "glUniformMatrix4x3fv");
	}

#pragma endregion OpenGL2_1 Extensions
	
	//OpenGL 3.0 Extensions
#pragma region OpenGL3_0

	enum openGL3_0_t
	{
		gl_clip_distance0 = 0x3000,
		gl_clip_distance1 = 0x3001,
		gl_clip_distance2 = 0x3002,
		gl_clip_distance3 = 0x3003,
		gl_clip_distance4 = 0x3004,
		gl_clip_distance5 = 0x3005,
		gl_compare_ref_to_texture = 0x884E,
		gl_max_clip_distances = 0x0D32,
		gl_max_varying_components = gl_max_varying_floats,

		gl_context_flag_forward_compatible_bit = 0x0001,
		gl_major_version = 0x821b,
		gl_minor_version = 0x821c,
		gl_num_extensions = 0x821d,
		gl_context_flags = 0x821e,
		gl_depth_buffer = 0x8223,
		gl_stencil_buffer = 0x8224,
		gl_rgba32f = 0x8814,
		gl_rgb32f = 0x8815,
		gl_rgba16f = 0x881a,
		gl_rgb16f = 0x881b,
		gl_vertex_attrib_array_integer = 0x88fd,
		gl_max_array_texture_layers = 0x88ff,
		gl_min_program_texel_offset = 0x8904,
		gl_max_program_texel_offset = 0x8905,
		gl_clamp_vertex_color = 0x891a,
		gl_clamp_fragment_color = 0x891b,
		gl_clamp_read_color = 0x891c,
		gl_fixed_only = 0x891d,
		gl_texture_red_type = 0x8c10,
		gl_texture_green_type = 0x8c11,
		gl_texture_blue_type = 0x8c12,
		gl_texture_alpha_type = 0x8c13,
		gl_texture_luminance_type = 0x8c14,
		gl_texture_intensity_type = 0x8c15,
		gl_texture_depth_type = 0x8c16,
		gl_texture_1d_array = 0x8c18,
		gl_proxy_texture_1d_array = 0x8c19,
		gl_texture_2d_array = 0x8c1a,
		gl_proxy_texture_2d_array = 0x8c1b,
		gl_texture_binding_1d_array = 0x8c1c,
		gl_texture_binding_2d_array = 0x8c1d,
		gl_r11f_g11f_b10f = 0x8c3a,
		gl_unsigned_int_10f_11f_11f_rev = 0x8c3b,
		gl_rgb9_e5 = 0x8c3d,
		gl_unsigned_int_5_9_9_9_rev = 0x8c3e,
		gl_texture_shared_size = 0x8c3f,
		gl_transform_feedback_varying_max_length = 0x8c76,
		gl_transform_feedback_buffer_mode = 0x8c7f,
		gl_max_transform_feedback_separate_components = 0x8c80,
		gl_transform_feedback_varyings = 0x8c83,
		gl_transform_feedback_buffer_start = 0x8c84,
		gl_transform_feedback_buffer_size = 0x8c85,
		gl_primitives_generated = 0x8c87,
		gl_transform_feedback_primitives_written = 0x8c88,
		gl_rasterizer_discard = 0x8c89,
		gl_max_transform_feedback_interleaved_components = 0x8c8a,
		gl_max_transform_feedback_separate_attribs = 0x8c8b,
		gl_interleaved_attribs = 0x8c8c,
		gl_separate_attribs = 0x8c8d,
		gl_transform_feedback_buffer = 0x8c8e,
		gl_transform_feedback_buffer_binding = 0x8c8f,
		gl_rgba32ui = 0x8d70,
		gl_rgb32ui = 0x8d71,
		gl_rgba16ui = 0x8d76,
		gl_rgb16ui = 0x8d77,
		gl_rgba8ui = 0x8d7c,
		gl_rgb8ui = 0x8d7d,
		gl_rgba32i = 0x8d82,
		gl_rgb32i = 0x8d83,
		gl_rgba16i = 0x8d88,
		gl_rgb16i = 0x8d89,
		gl_rgba8i = 0x8d8e,
		gl_rgb8i = 0x8d8f,
		gl_red_integer = 0x8d94,
		gl_green_integer = 0x8d95,
		gl_blue_integer = 0x8d96,
		gl_alpha_integer = 0x8d97,
		gl_rgb_integer = 0x8d98,
		gl_rgba_integer = 0x8d99,
		gl_bgr_integer = 0x8d9a,
		gl_bgra_integer = 0x8d9b,
		gl_sampler_1d_array = 0x8dc0,
		gl_sampler_2d_array = 0x8dc1,
		gl_sampler_1d_array_shadow = 0x8dc3,
		gl_sampler_2d_array_shadow = 0x8dc4,
		gl_sampler_cube_shadow = 0x8dc5,
		gl_unsigned_int_vec2 = 0x8dc6,
		gl_unsigned_int_vec3 = 0x8dc7,
		gl_unsigned_int_vec4 = 0x8dc8,
		gl_int_sampler_1d = 0x8dc9,
		gl_int_sampler_2d = 0x8dca,
		gl_int_sampler_3d = 0x8dcb,
		gl_int_sampler_cube = 0x8dcc,
		gl_int_sampler_1d_array = 0x8dce,
		gl_int_sampler_2d_array = 0x8dcf,
		gl_unsigned_int_sampler_1d = 0x8dd1,
		gl_unsigned_int_sampler_2d = 0x8dd2,
		gl_unsigned_int_sampler_3d = 0x8dd3,
		gl_unsigned_int_sampler_cube = 0x8dd4,
		gl_unsigned_int_sampler_1d_array = 0x8dd6,
		gl_unsigned_int_sampler_2d_array = 0x8dd7,
		gl_query_wait = 0x8e13,
		gl_query_no_wait = 0x8e14,
		gl_query_by_region_wait = 0x8e15,
		gl_query_by_region_no_wait = 0x8e16,
	};

	void (*glBeginConditionalRender) (GLuint id, GLenum mode);
	void (*glBeginTransformFeedback) (GLenum primitiveMode);
	void (*glBindFragDataLocation) (GLuint program, GLuint colorNumber, const GLchar* name);
	void (*glClampColor) (GLenum target, GLenum clamp);
	void (*glClearBufferfi) (GLenum buffer, GLint drawBuffer, GLfloat depth, GLint stencil);
	void (*glClearBufferfv) (GLenum buffer, GLint drawBuffer, const GLfloat* value);
	void (*glClearBufferiv) (GLenum buffer, GLint drawBuffer, const GLint* value);
	void (*glClearBufferuiv) (GLenum buffer, GLint drawBuffer, const GLuint* value);
	void (*glColorMaski) (GLuint buf, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void (*glDisablei) (GLenum cap, GLuint index);
	void (*glEnablei) (GLenum cap, GLuint index);
	void (*glEndConditionalRender) (void);
	void (*glEndTransformFeedback) (void);
	void (*glGetBooleani_v) (GLenum pname, GLuint index, GLboolean* data);
	GLint(*glGetFragDataLocation) (GLuint program, const GLchar* name);
	const GLubyte* (*glGetStringi) (GLenum name, GLuint index);
	void (*glGetTexParameterIiv) (GLenum target, GLenum pname, GLint* params);
	void (*glGetTexParameterIuiv) (GLenum target, GLenum pname, GLuint* params);
	void (*glGetTransformFeedbackVarying) (GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);
	void (*glGetUniformuiv) (GLuint program, GLint location, GLuint* params);
	void (*glGetVertexAttribIiv) (GLuint index, GLenum pname, GLint* params);
	void (*glGetVertexAttribIuiv) (GLuint index, GLenum pname, GLuint* params);
	GLboolean(*glIsEnabledi) (GLenum cap, GLuint index);
	void (*glTexParameterIiv) (GLenum target, GLenum pname, const GLint* params);
	void (*glTexParameterIuiv) (GLenum target, GLenum pname, const GLuint* params);
	void (*glTransformFeedbackVaryings) (GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode);
	void (*glUniform1ui) (GLint location, GLuint v0);
	void (*glUniform1uiv) (GLint location, GLsizei count, const GLuint* value);
	void (*glUniform2ui) (GLint location, GLuint v0, GLuint v1);
	void (*glUniform2uiv) (GLint location, GLsizei count, const GLuint* value);
	void (*glUniform3ui) (GLint location, GLuint v0, GLuint v1, GLuint v2);
	void (*glUniform3uiv) (GLint location, GLsizei count, const GLuint* value);
	void (*glUniform4ui) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	void (*glUniform4uiv) (GLint location, GLsizei count, const GLuint* value);
	void (*glVertexAttribI1i) (GLuint index, GLint v0);
	void (*glVertexAttribI1iv) (GLuint index, const GLint* v0);
	void (*glVertexAttribI1ui) (GLuint index, GLuint v0);
	void (*glVertexAttribI1uiv) (GLuint index, const GLuint* v0);
	void (*glVertexAttribI2i) (GLuint index, GLint v0, GLint v1);
	void (*glVertexAttribI2iv) (GLuint index, const GLint* v0);
	void (*glVertexAttribI2ui) (GLuint index, GLuint v0, GLuint v1);
	void (*glVertexAttribI2uiv) (GLuint index, const GLuint* v0);
	void (*glVertexAttribI3i) (GLuint index, GLint v0, GLint v1, GLint v2);
	void (*glVertexAttribI3iv) (GLuint index, const GLint* v0);
	void (*glVertexAttribI3ui) (GLuint index, GLuint v0, GLuint v1, GLuint v2);
	void (*glVertexAttribI3uiv) (GLuint index, const GLuint* v0);
	void (*glVertexAttribI4bv) (GLuint index, const GLbyte* v0);
	void (*glVertexAttribI4i) (GLuint index, GLint v0, GLint v1, GLint v2, GLint v3);
	void (*glVertexAttribI4iv) (GLuint index, const GLint* v0);
	void (*glVertexAttribI4sv) (GLuint index, const GLshort* v0);
	void (*glVertexAttribI4ubv) (GLuint index, const GLubyte* v0);
	void (*glVertexAttribI4ui) (GLuint index, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	void (*glVertexAttribI4uiv) (GLuint index, const GLuint* v0);
	void (*glVertexAttribI4usv) (GLuint index, const GLushort* v0);
	void (*glVertexAttribIPointer) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);

	//*< load OpenGL 3.0 extensions
	void Load3_0Extensions()
	{
		FetchProcAddress(glColorMaski, "glColorMaski");
		FetchProcAddress(glGetBooleani_v, "glGetBooleani_v");
		FetchProcAddress(glEnablei, "glEnablei");
		FetchProcAddress(glDisablei, "glDisablei");
		FetchProcAddress(glIsEnabledi, "glIsEnabledi");
		FetchProcAddress(glBeginTransformFeedback, "glBeginTransformFeedback");
		FetchProcAddress(glEndTransformFeedback, "glEndTransformFeedback");
		FetchProcAddress(glTransformFeedbackVaryings, "glTransformFeedbackVaryings");
		FetchProcAddress(glGetTransformFeedbackVarying, "glGetTransformFeedbackVarying");
		FetchProcAddress(glClampColor, "glClampColor");
		FetchProcAddress(glBeginConditionalRender, "glBeginConditionalRender");
		FetchProcAddress(glEndConditionalRender, "glEndConditionalRender");
		FetchProcAddress(glVertexAttribIPointer, "glVertexAttribIPointer");
		FetchProcAddress(glGetVertexAttribIiv, "glGetVertexAttribIiv");
		FetchProcAddress(glGetVertexAttribIuiv, "glGetVertexAttribIuiv");
		FetchProcAddress(glVertexAttribI1i, "glVertexAttribI1i");
		FetchProcAddress(glVertexAttribI2i, "glVertexAttribI2i");
		FetchProcAddress(glVertexAttribI3i, "glVertexAttribI3i");
		FetchProcAddress(glVertexAttribI4i, "glVertexAttribI4i");
		FetchProcAddress(glVertexAttribI1ui, "glVertexAttribI1ui");
		FetchProcAddress(glVertexAttribI2ui, "glVertexAttribI2ui");
		FetchProcAddress(glVertexAttribI3ui, "glVertexAttribI3ui");
		FetchProcAddress(glVertexAttribI4ui, "glVertexAttribI4ui");
		FetchProcAddress(glVertexAttribI1iv, "glVertexAttribI1iv");
		FetchProcAddress(glVertexAttribI2iv, "glVertexAttribI2iv");
		FetchProcAddress(glVertexAttribI3iv, "glVertexAttribI3iv");
		FetchProcAddress(glVertexAttribI4iv, "glVertexAttribI4iv");
		FetchProcAddress(glVertexAttribI1uiv, "glVertexAttribI1uiv");
		FetchProcAddress(glVertexAttribI2uiv, "glVertexAttribI2uiv");
		FetchProcAddress(glVertexAttribI3uiv, "glVertexAttribI3uiv");
		FetchProcAddress(glVertexAttribI4uiv, "glVertexAttribI4uiv");
		FetchProcAddress(glVertexAttribI4bv, "glVertexAttribI4bv");
		FetchProcAddress(glVertexAttribI4sv, "glVertexAttribI4sv");
		FetchProcAddress(glVertexAttribI4ubv, "glVertexAttribI4ubv");
		FetchProcAddress(glVertexAttribI4usv, "glVertexAttribI4usv");
		FetchProcAddress(glGetUniformuiv, "glGetUniformuiv");
		FetchProcAddress(glBindFragDataLocation, "glBindFragDataLocation");
		FetchProcAddress(glGetFragDataLocation, "glGetFragDataLocation");
		FetchProcAddress(glUniform1ui, "glUniform1ui");
		FetchProcAddress(glUniform2ui, "glUniform2ui");
		FetchProcAddress(glUniform3ui, "glUniform3ui");
		FetchProcAddress(glUniform4ui, "glUniform4ui");
		FetchProcAddress(glUniform1uiv, "glUniform1uiv");
		FetchProcAddress(glUniform2uiv, "glUniform2uiv");
		FetchProcAddress(glUniform3uiv, "glUniform3uiv");
		FetchProcAddress(glUniform4uiv, "glUniform4uiv");
		FetchProcAddress(glTexParameterIiv, "glTexParameterIiv");
		FetchProcAddress(glTexParameterIuiv, "glTexParameterIuiv");
		FetchProcAddress(glGetTexParameterIiv, "glGetTexParameterIiv");
		FetchProcAddress(glGetTexParameterIuiv, "glGetTexParameterIuiv");
		FetchProcAddress(glClearBufferiv, "glClearBufferiv");
		FetchProcAddress(glClearBufferuiv, "glClearBufferuiv");
		FetchProcAddress(glClearBufferfv, "glClearBufferfv");
		FetchProcAddress(glClearBufferfi, "glClearBufferfi");
		FetchProcAddress(glGetStringi, "glGetStringi");
	}

#pragma endregion OpenGL3_0 Extensions

	//OpenGL 3.1 Extensions
#pragma region OpenGL3_1

	enum openGL3_1_t
	{
		gl_texture_rectangle = 0x84f5,
		gl_texture_binding_rectangle = 0x84f6,
		gl_proxy_texture_rectangle = 0x84f7,
		gl_max_rectangle_texture_size = 0x84f8,
		gl_sampler_2d_rect = 0x8b63,
		gl_sampler_2d_rect_shadow = 0x8b64,
		gl_texture_buffer = 0x8c2a,
		gl_max_texture_buffer_size = 0x8c2b,
		gl_texture_binding_buffer = 0x8c2c,
		gl_texture_buffer_data_store_binding = 0x8c2d,
		gl_texture_buffer_format = 0x8c2e,
		gl_sampler_buffer = 0x8dc2,
		gl_int_sampler_2d_rect = 0x8dcd,
		gl_int_sampler_buffer = 0x8dd0,
		gl_unsigned_int_sampler_2d_rect = 0x8dd5,
		gl_unsigned_int_sampler_buffer = 0x8dd8,
		gl_red_snorm = 0x8f90,
		gl_rg_snorm = 0x8f91,
		gl_rgb_snorm = 0x8f92,
		gl_rgba_snorm = 0x8f93,
		gl_r8_snorm = 0x8f94,
		gl_rg8_snorm = 0x8f95,
		gl_rgb8_snorm = 0x8f96,
		gl_rgba8_snorm = 0x8f97,
		gl_r16_snorm = 0x8f98,
		gl_rg16_snorm = 0x8f99,
		gl_rgb16_snorm = 0x8f9a,
		gl_rgba16_snorm = 0x8f9b,
		gl_signed_normalized = 0x8f9c,
		gl_primitive_restart = 0x8f9d,
		gl_primitive_restart_index = 0x8f9e,
	};

	void(*glDrawArraysInstanced) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount) = nullptr;
	void(*glDrawElementsInstanced) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount) = nullptr;
	void(*glTexBuffer) (GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
	void(*glPrimitiveRestartIndex) (GLuint index) = nullptr;

	//*< load OpenGL 3.1 extensions
	void Load3_1Extensions()
	{
		FetchProcAddress(glDrawArraysInstanced, "glDrawArraysInstanced");
		FetchProcAddress(glDrawElementsInstanced, "glDrawElementsInstanced");
		FetchProcAddress(glTexBuffer, "glTexBuffer");
		FetchProcAddress(glPrimitiveRestartIndex, "glPrimitiveRestartIndex");
	}
	
#pragma endregion OpenGL3_1 Extensions

	//OpenGL 3.2 Extensions
#pragma region OpenGL3_2

	enum openGL3_2
	{
		gl_context_core_profile_bit = 0x00000001,
		gl_context_compatibility_profile_bit = 0x00000002,
		gl_lines_adjacency = 0x000a,
		gl_line_strip_adjacency = 0x000b,
		gl_triangles_adjacency = 0x000c,
		gl_triangle_strip_adjacency = 0x000d,
		gl_program_point_size = 0x8642,
		gl_geometry_vertices_out = 0x8916,
		gl_geometry_input_type = 0x8917,
		gl_geometry_output_type = 0x8918,
		gl_max_geometry_texture_image_units = 0x8c29,
		gl_framebuffer_attachment_layered = 0x8da7,
		gl_framebuffer_incomplete_layer_targets = 0x8da8,
		gl_geometry_shader = 0x8dd9,
		gl_max_geometry_uniform_components = 0x8ddf,
		gl_max_geometry_output_vertices = 0x8de0,
		gl_max_geometry_total_output_components = 0x8de1,
		gl_max_vertex_output_components = 0x9122,
		gl_max_geometry_input_components = 0x9123,
		gl_max_geometry_output_components = 0x9124,
		gl_max_fragment_input_components = 0x9125,
		gl_context_profile_mask = 0x9126,
	};

	void(*glFramebufferTexture) (GLenum target, GLenum attachment, GLuint texture, GLint level) = nullptr;
	void(*glGetBufferParameteri64v) (GLenum target, GLenum pname, GLint64* params) = nullptr;
	void(*glGetInteger64i_v) (GLenum target, GLuint index, GLint64* data) = nullptr;

	//*< load OpenGL 3.2 extensions
	void Load3_2Extensions()
	{
		FetchProcAddress(glGetInteger64i_v, "glGetInteger64i_v");
		FetchProcAddress(glGetBufferParameteri64v, "glGetBufferParameteri64v");
		FetchProcAddress(glFramebufferTexture, "glFramebufferTexture");
	}

#pragma endregion OpenGL3_2 Extensions

	//OpenGL 3.3 Extensions
#pragma region OpenGL3_3
	
	enum openGL3_3
	{
		gl_vertex_attrib_array_divisor = 0x88fe,
		gl_rgb10_a2ui = 0x906f,
	};

	void(*glVertexAttribDivisor) (GLuint index, GLuint divisor) = nullptr;

	//*< load OpenGL 3.3 extensions
	void Load3_3Extensions()
	{
		FetchProcAddress(glVertexAttribDivisor, "glVertexAttribDivisor");
	}
#pragma endregion OpenGL3_3 Extensions

	//OpenGL 4.0 Extensions
#pragma region OpenGL4_0

	enum openGL4_0
	{
		gl_sample_shading = 0x8c36,
		gl_min_sample_shading_value = 0x8c37,
		gl_min_program_texture_gather_offset = 0x8e5e,
		gl_max_program_texture_gather_offset = 0x8e5f,
		gl_max_program_texture_gather_components = 0x8f9f,
		gl_texture_cube_map_array = 0x9009,
		gl_texture_binding_cube_map_array = 0x900a,
		gl_proxy_texture_cube_map_array = 0x900b,
		gl_sampler_cube_map_array = 0x900c,
		gl_sampler_cube_map_array_shadow = 0x900d,
		gl_int_sampler_cube_map_array = 0x900e,
		gl_unsigned_int_sampler_cube_map_array = 0x900f,
	};

	void(*glMinSampleShading) (GLfloat value) = nullptr;
	void(*glBlendEquationi) (GLuint buf, GLenum mode) = nullptr;
	void(*glBlendEquationSeparatei) (GLuint buf, GLenum modeRGB, GLenum modeAlpha) = nullptr;
	void(*glBlendFunci) (GLuint buf, GLenum src, GLenum dst) = nullptr;
	void(*glBlendFuncSeparatei) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = nullptr;

	//*< load OpenGL 4.0 extensions
	void Load4_0Extensions()
	{
		FetchProcAddress(glMinSampleShading, "glMinSampleShading");
		FetchProcAddress(glBlendEquationi, "glBlendEquationi");
		FetchProcAddress(glBlendEquationSeparatei, "glBlendEquationSeparatei");
		FetchProcAddress(glBlendFunci, "glBlendFunci");
		FetchProcAddress(glBlendFuncSeparatei, "glBlendFuncSeparatei");
	}

#pragma endregion OpenGL4_0 Extensions

	//OpenGL 4.1 Extensions
#pragma region OpenGL4_1

	//*< load OpenGL 4.1 extensions
	void Load4_1Extensions()
	{

	}

#pragma endregion OpenGL4_1 Extensions

	//OpenGL 4.2 Extensions
#pragma region OpenGL4_2
	
	enum openGL4_2
	{
		gl_transform_feedback_paused =								0x8e23,
		gl_transform_feedback_active =								0x8e24,
		gl_compressed_rgba_bptc_unorm =								0x8e8c,
		gl_compressed_srgb_alpha_bptc_unorm =						0x8e8d,
		gl_compressed_rgb_bptc_signed_float =						0x8e8e,
		gl_compressed_rgb_bptc_unsigned_float =						0x8e8f,
		gl_copy_read_buffer_binding =								0x8f36,
		gl_copy_write_buffer_binding =								0x8f37,
	};

	//*< load OpenGL 4.2 extensions
	void Load4_2Extensions()
	{

	}

#pragma endregion OpenGL4_2 Extensions

	//OpenGL 4.3 Extensions
#pragma region OpenGL4_3
	enum openGL4_3
	{
		gl_num_shading_language_versions =		0x82e9,
		gl_vertex_attrib_array_long =			0x874e,
	};

	//*< load OpenGL 4.3 extensions
	void Load4_3Extensions()
	{

	}

#pragma endregion OpenGL4_3 Extensions

	//OpenGL 4.4 Extensions
#pragma region OpenGL4_4
	enum openGL4_4
	{
		gl_primitive_restart_for_patches_supported =		0x8221,
		gl_max_vertex_attrib_stride =				0x82e5,
		gl_texture_buffer_binding =					0x8c2a,
	};

	//*< load OpenGL 4.4 extensions
	void Load4_4Extensions()
	{

	}

#pragma endregion OpenGL4_4 Extensions

	//OpenGL 4.5 Extensions
#pragma region OpenGL4_5
	GLenum(*glGetGraphicsResetStatus) (void) = nullptr;
	void(*glGetnCompressedTexImage) (GLenum target, GLint lod, GLsizei bufSize, GLvoid* pixels) = nullptr;
	void(*glGetnTexImage) (GLenum tex, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid* pixels) = nullptr;
	void(*glGetnUniformdv) (GLuint program, GLint location, GLsizei bufSize, GLdouble* params) = nullptr;

	//*< load OpenGL 4.5 extensions
	void Load4_5Extensions()
	{
		FetchProcAddress(glGetGraphicsResetStatus, "glGetGraphicsResetStatus");
		FetchProcAddress(glGetnCompressedTexImage, "glGetnCompressedTexImage");
		FetchProcAddress(glGetnTexImage, "glGetnTexImage");
		FetchProcAddress(glGetnUniformdv, "glGetnUniformdv");
	}

	enum openGL4_5
	{
		gl_context_flag_robust_access_bit =				0x00000004
	};

#pragma endregion OpenGL4_5 Extensions
	
	//OpenGL 4.6 Extensions
#pragma region OpenGL4_6

	enum openGL4_6
	{
		gl_context_flag_no_error_bit = 0x00000008,
		gl_parameter_buffer = 0x80ee,
		gl_parameter_buffer_binding = 0x80ef,
		gl_transform_feedback_overflow = 0x82ec,
		gl_transform_feedback_stream_overflow = 0x82ed,
		gl_vertices_submitted = 0x82ee,
		gl_primitives_submitted = 0x82ef,
		gl_vertex_shader_invocations = 0x82f0,
		gl_tess_control_shader_patches = 0x82f1,
		gl_tess_evaluation_shader_invocations = 0x82f2,
		gl_geometry_shader_primitives_emitted = 0x82f3,
		gl_fragment_shader_invocations = 0x82f4,
		gl_compute_shader_invocations = 0x82f5,
		gl_clipping_input_primitives = 0x82f6,
		gl_clipping_output_primitives = 0x82f7,
		gl_texture_max_anisotropy = 0x84fe,
		gl_max_texture_max_anisotropy = 0x84ff,
		gl_polygon_offset_clamp = 0x8e1b,
		gl_shader_binary_format_spir_v = 0x9551,
		gl_spir_v_binary = 0x9552,
		gl_spir_v_extensions = 0x9553,
		gl_num_spir_v_extensions = 0x9554,
	};

	GLenum(*glMultiDrawArraysIndirectCount) (GLenum mode, const GLvoid* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) = nullptr;
	GLenum(*glMultiDrawElementsIndirectCount) (GLenum mode, GLenum type, const GLvoid* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) = nullptr;
	GLenum(*glSpecializeShader) (GLuint shader, const GLchar* pEntryPoint, GLuint numSpecializationConstants, const GLuint* pConstantIndex, const GLuint* pConstantValue) = nullptr;

	//*< load OpenGL 4.6 extensions
	void Load4_6Extensions()
	{
		FetchProcAddress(glMultiDrawArraysIndirectCount, "glMultiDrawArraysIndirectCount");
		FetchProcAddress(glMultiDrawElementsIndirectCount, "glMultiDrawElementsIndirectCount");
		FetchProcAddress(glSpecializeShader, "glSpecializeShader");
	}

#pragma endregion OpenGL4_6 Extensions

	//OpenGL 3DFX Extensions
#pragma region 3DFX

	enum OpenGL_3DFX_t
	{
		//multisample
		gl_multisample_3dfx = 0x86b2,
		gl_sample_buffers_3dfx = 0x86b3,
		gl_samples_3dfx = 0x86b4,
		gl_multisample_bit_3dfx = 0x20000000,

		//compression
		gl_compressed_rgb_fxt1_3dfx = 0x86b0,
		gl_compressed_rgba_fxt1_3dfx = 0x86b1,
	};

	//multisample
	bool multisample_3DFX = false;

	//tbuffer
	bool tbuffer_3DFX = false;
	void (*glTbufferMask3DFX) (GLuint mask) = nullptr;

	//texture compression FXT1
	bool texture_compression_FXT1_3DFX = false;

	//*< load OpenGL 3DFX Extensions
	void Load3DFXExtensions()
	{
		//multisample
		FetchProcAddress(multisample_3DFX, "multisample_3DFX");

		//tbuffer
		FetchProcAddress(tbuffer_3DFX, "tbuffer_3DFX");
		FetchProcAddress(glTbufferMask3DFX, "glTbufferMask3DFX");

		//texture compression FXT1
		FetchProcAddress(texture_compression_FXT1_3DFX, "texture_compression_FXT1_3DFX");
	}

#pragma endregion 3DFX Extensions

	//OpenGL AMD Extensions
#pragma region AMD

	enum OpenGL_AMD_t
	{
		//blend minmax factor,
		gl_factor_min_amd = 0x901c,
		gl_factor_max_amd = 0x901d,

		//compressed 3dc texture,
		gl_3dc_x_amd = 0x87f9,
		gl_3dc_xy_amd = 0x87fa,

		//compressed atc texture,
		gl_atc_rgba_interpolated_alpha_amd = 0x87ee,
		gl_atc_rgb_amd = 0x8c92,
		gl_atc_rgba_explicit_alpha_amd = 0x8c93,

		//debug output,
		gl_max_debug_message_length_amd = 0x9143,
		gl_max_debug_logged_messages_amd = 0x9144,
		gl_debug_logged_messages_amd = 0x9145,
		gl_debug_severity_high_amd = 0x9146,
		gl_debug_severity_medium_amd = 0x9147,
		gl_debug_severity_low_amd = 0x9148,
		gl_debug_category_api_error_amd = 0x9149,
		gl_debug_category_window_system_amd = 0x914a,
		gl_debug_category_deprecation_amd = 0x914b,
		gl_debug_category_undefined_behavior_amd = 0x914c,
		gl_debug_category_performance_amd = 0x914d,
		gl_debug_category_shader_compiler_amd = 0x914e,
		gl_debug_category_application_amd = 0x914f,
		gl_debug_category_other_amd = 0x9150,

		//depth clamp separate,
		gl_depth_clamp_near_amd = 0x901e,
		gl_depth_clamp_far_amd = 0x901f,

		//framebuffer sample positions,
		gl_subsample_distance_amd = 0x883f,
		gl_pixels_per_sample_pattern_x_amd = 0x91ae,
		gl_pixels_per_sample_pattern_y_amd = 0x91af,
		gl_all_pixels_amd = 0xffffffff,

		//gpu shader half float,
		gl_float16_nv = 0x8ff8,
		gl_float16_vec2_nv = 0x8ff9,
		gl_float16_vec3_nv = 0x8ffa,
		gl_float16_vec4_nv = 0x8ffb,
		gl_float16_mat2_amd = 0x91c5,
		gl_float16_mat3_amd = 0x91c6,
		gl_float16_mat4_amd = 0x91c7,
		gl_float16_mat2x3_amd = 0x91c8,
		gl_float16_mat2x4_amd = 0x91c9,
		gl_float16_mat3x2_amd = 0x91ca,
		gl_float16_mat3x4_amd = 0x91cb,
		gl_float16_mat4x2_amd = 0x91cc,
		gl_float16_mat4x3_amd = 0x91cd,

		//interleaved elements,
		gl_red_amd = 0x1903,
		gl_green_amd = 0x1904,
		gl_blue_amd = 0x1905,
		gl_alpha_amd = 0x1906,
		gl_rg8ui_amd = 0x8238,
		gl_rg16ui_amd = 0x823a,
		gl_rgba8ui_amd = 0x8d7c,
		gl_vertex_element_swizzle_amd = 0x91a4,
		gl_vertex_id_swizzle_amd = 0x91a5,

		//name gen delete,
		gl_data_buffer_amd = 0x9151,
		gl_performance_monitor_amd = 0x9152,
		gl_query_object_amd = 0x9153,
		gl_vertex_array_object_amd = 0x9154,
		gl_sampler_object_amd = 0x9155,

		//occlusion query event,
		gl_query_depth_pass_event_bit_amd = 0x00000001,
		gl_query_depth_fail_event_bit_amd = 0x00000002,
		gl_query_stencil_fail_event_bit_amd = 0x00000004,
		gl_query_depth_bounds_fail_event_bit_amd = 0x00000008,
		gl_occlusion_query_event_mask_amd = 0x874f,
		gl_query_all_event_bits_amd = 0xffffffff,

		//performance monitor,
		gl_counter_type_amd = 0x8bc0,
		gl_counter_range_amd = 0x8bc1,
		gl_unsigned_int64_amd = 0x8bc2,
		gl_percentage_amd = 0x8bc3,
		gl_perfmon_result_available_amd = 0x8bc4,
		gl_perfmon_result_size_amd = 0x8bc5,
		gl_perfmon_result_amd = 0x8bc6,

		//pinned memory,
		gl_external_virtual_memory_buffer_amd = 0x9160,

		//program binary z400,
		gl_z400_binary_amd = 0x8740,

		//query buffer object,
		gl_query_buffer_amd = 0x9192,
		gl_query_buffer_binding_amd = 0x9193,
		gl_query_result_no_wait_amd = 0x9194,

		//seamless cubemap per texture,
		gl_texture_cube_map_seamless = 0x884f,

		//sparse texture,
		gl_texture_storage_sparse_bit_amd = 0x00000001,
		gl_virtual_page_size_x_amd = 0x9195,
		gl_virtual_page_size_y_amd = 0x9196,
		gl_virtual_page_size_z_amd = 0x9197,
		gl_max_sparse_texture_size_amd = 0x9198,
		gl_max_sparse_3d_texture_size_amd = 0x9199,
		gl_max_sparse_array_texture_layers = 0x919a,
		gl_min_sparse_level_amd = 0x919b,
		gl_min_lod_warning_amd = 0x919c,

		//stencil operation extended,
		gl_set_amd = 0x874a,
		gl_replace_value_amd = 0x874b,
		gl_stencil_op_value_amd = 0x874c,
		gl_stencil_back_op_value_amd = 0x874d,

		//transform feedback,
		gl_stream_rasterization_amd = 0x91a0,

		//vertex shader tesselator,
		gl_sampler_buffer_amd = 0x9001,
		gl_int_sampler_buffer_amd = 0x9002,
		gl_unsigned_int_sampler_buffer_amd = 0x9003,
		gl_tessellation_mode_amd = 0x9004,
		gl_tessellation_factor_amd = 0x9005,
		gl_discrete_amd = 0x9006,
		gl_continuous_amd = 0x9007,
	};

	//blend minmax factor
	bool AMD_blend_minmax_factor = false;

	//compressed 3DC texture
	bool AMD_compressed_3DC_texture = false;

	//compressed ATC texture
	bool AMD_compressed_ATC_texture = false;
	
	//conservative depth
	bool AMD_conservative_depth = false;

	//debug output
	bool AMD_debug_output = false;
	typedef void (*GLDEBUGPROCAMD)(GLuint id, GLenum category, GLenum severity, GLsizei length, const GLchar* message, void* userParam);
	void (*glDebugMessageCallbackAMD) (GLDEBUGPROCAMD callback, void* userParam) = nullptr;
	void (*glDebugMessageEnableAMD) (GLenum category, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled) = nullptr;
	void (*glDebugMessageInsertAMD) (GLenum category, GLenum severity, GLuint id, GLsizei length, const GLchar* buf) = nullptr;
	GLuint (*glGetDebugMessageLogAMD) (GLuint count, GLsizei bufsize, GLenum* categories, GLuint* severities, GLuint* ids, GLsizei* lengths, GLchar* message) = nullptr;

	//depth clamp separate
	bool AMD_depth_clamp_separate = false;

	//draw buffers blend
	bool AMD_draw_buffers_blend = false;
	void (*glBlendEquationIndexedAMD) (GLuint buf, GLenum mode) = nullptr;
	void (*glBlendEquationSeparateIndexedAMD) (GLuint buf, GLenum modeRGB, GLenum modeAlpha) = nullptr;
	void (*glBlendFuncIndexedAMD) (GLuint buf, GLenum src, GLenum dst) = nullptr;
	void (*glBlendFuncSeparateIndexedAMD) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = nullptr;

	//framebuffer sample positions
	bool AMD_framebuffer_sample_positions = false;
	void (*glFramebufferSamplePositionsfvAMD) (GLenum target, GLuint numsamples, GLuint pixelindex, const GLfloat* values) = nullptr;
	void (*glGetFramebufferParameterfvAMD) (GLenum target, GLenum pname, GLuint numsamples, GLuint pixelindex, GLsizei size, GLfloat* values) = nullptr;
	void (*glGetNamedFramebufferParameterfvAMD) (GLuint framebuffer, GLenum pname, GLuint numsamples, GLuint pixelindex, GLsizei size, GLfloat* values) = nullptr;
	void (*glNamedFramebufferSamplePositionsfvAMD) (GLuint framebuffer, GLuint numsamples, GLuint pixelindex, const GLfloat* values) = nullptr;

	//gcn shader
	bool AMD_gcn_shader = false;

	//gpu shader half float
	bool AMD_gpu_shader_half_float = false;

	//gpu shader int16
	bool AMD_gpu_shader_int16 = false;

	//gpu shader int64
	bool AMD_gpu_shader_int64 = false;

	//interleaved elements
	bool AMD_interleaved_elements = false;
	void (*glVertexAttribParameteriAMD) (GLuint index, GLenum pname, GLint param) = nullptr;

	//multi draw indirect
	bool AMD_multi_draw_indirect = false;
	void (*glMultiDrawArraysIndirectAMD) (GLenum mode, const void* indirect, GLsizei primcount, GLsizei stride) = nullptr;
	void (*glMultiDrawElementsIndirectAMD) (GLenum mode, GLenum type, const void* indirect, GLsizei primcount, GLsizei stride) = nullptr;

	//name gen delete
	bool AMD_name_gen_delete = false;
	void (*glDeleteNamesAMD) (GLenum identifier, GLuint num, const GLuint* names) = nullptr;
	void (*glGenNamesAMD) (GLenum identifier, GLuint num, GLuint* names) = nullptr;
	GLboolean(*glIsNameAMD) (GLenum identifier, GLuint name) = nullptr;

	//occlusion query event
	bool AMD_occlusion_query_event = false;
	void (*glQueryObjectParameteruiAMD) (GLenum target, GLuint id, GLenum pname, GLuint param) = nullptr;

	//performance monitor
	bool AMD_performance_monitor = false;
	void (*glBeginPerfMonitorAMD) (GLuint monitor) = nullptr;
	void (*glDeletePerfMonitorsAMD) (GLsizei n, GLuint* monitors) = nullptr;
	void (*glEndPerfMonitorAMD) (GLuint monitor) = nullptr;
	void (*glGenPerfMonitorsAMD) (GLsizei n, GLuint* monitors) = nullptr;
	void (*glGetPerfMonitorCounterDataAMD) (GLuint monitor, GLenum pname, GLsizei dataSize, GLuint* data, GLint* bytesWritten) = nullptr;
	void (*glGetPerfMonitorCounterInfoAMD) (GLuint group, GLuint counter, GLenum pname, void* data) = nullptr;
	void (*glGetPerfMonitorCounterStringAMD) (GLuint group, GLuint counter, GLsizei bufSize, GLsizei* length, GLchar* counterString) = nullptr;
	void (*glGetPerfMonitorCountersAMD) (GLuint group, GLint* numCounters, GLint* maxActiveCounters, GLsizei countersSize, GLuint* counters) = nullptr;
	void (*glGetPerfMonitorGroupStringAMD) (GLuint group, GLsizei bufSize, GLsizei* length, GLchar* groupString) = nullptr;
	void (*glGetPerfMonitorGroupsAMD) (GLint* numGroups, GLsizei groupsSize, GLuint* groups) = nullptr;
	void (*glSelectPerfMonitorCountersAMD) (GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint* counterList) = nullptr;

	//pinned memory
	bool AMD_pinned_memory = false;

	//program binary Z400
	bool AMD_program_binary_Z400 = false;

	//query buffer object
	bool AMD_query_buffer_object = false;

	//sample positions
	bool AMD_sample_positions = false;
	void (*glSetMultisamplefvAMD) (GLenum pname, GLuint index, const GLfloat* val) = nullptr;

	//seamless cubemap per texture
	bool AMD_seamless_cubemap_per_texture = false;

	//shader atomic counter ops
	bool AMD_shader_atomic_counter_ops = false;

	//shader ballot
	bool AMD_shader_ballot = false;

	//shader explicit vertex parameter
	bool AMD_shader_explicit_vertex_parameter = false;

	//shader stencil export
	bool AMD_shader_stencil_export = false;

	//shader stencil value export
	bool AMD_shader_stencil_value_export = false;

	//shader trinary minmax
	bool AMD_shader_trinary_minmax = false;

	//sparse texture
	bool AMD_sparse_texture = false;
	void (*glTexStorageSparseAMD) (GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags) = nullptr;
	void (*glTextureStorageSparseAMD) (GLuint texture, GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags) = nullptr;

	//stencil operation extended
	bool AMD_stencil_operation_extended = false;
	void (*glStencilOpValueAMD) (GLenum face, GLuint value) = nullptr;

	//texture gather bias lod
	bool AMD_texture_gather_bias_lod = false;

	//texture texture4
	bool AMD_texture_texture4 = false;

	//transform feedback3 lines triangles
	bool AMD_transform_feedback3_lines_triangles = false;

	//transform feedback4 
	bool AMD_transform_feedback4 = false;

	//vertex shader layer
	bool AMD_vertex_shader_layer = false;

	//vertex shader tessellator
	bool AMD_vertex_shader_tessellator = false;
	void (*glTessellationFactorAMD) (GLfloat factor) = nullptr;
	void (*glTessellationModeAMD) (GLenum mode) = nullptr;

	//vertex shader viewport index
	bool AMD_vertex_shader_viewport_index = false;

	//*< load OpenGL AMD Extensions
	void LoadAMDExtensions()
	{
		//blend minmax factor
		FetchProcAddress(AMD_blend_minmax_factor, "AMD_blend_minmax_factor");

		//compressed 3DC texture
		FetchProcAddress(AMD_compressed_3DC_texture, "AMD_compressed_3DC_texture");

		//compressed ATC texture
		FetchProcAddress(AMD_compressed_ATC_texture, "AMD_compressed_ATC_texture");

		//conservative depth
		FetchProcAddress(AMD_conservative_depth, "AMD_conservative_depth");

		//debug output
		FetchProcAddress(AMD_debug_output, "AMD_debug_output");
		FetchProcAddress(glDebugMessageCallbackAMD, "glDebugMessageCallbackAMD");
		FetchProcAddress(glDebugMessageEnableAMD, "glDebugMessageEnableAMD");
		FetchProcAddress(glDebugMessageInsertAMD, "glDebugMessageInsertAMD");
		FetchProcAddress(glGetDebugMessageLogAMD, "glGetDebugMessageLogAMD");

		//depth clamp separate
		FetchProcAddress(AMD_depth_clamp_separate, "AMD_depth_clamp_separate");

		//draw buffers blend
		FetchProcAddress(AMD_draw_buffers_blend, "AMD_draw_buffers_blend");
		FetchProcAddress(glBlendEquationIndexedAMD, "glBlendEquationIndexedAMD");
		FetchProcAddress(glBlendEquationSeparateIndexedAMD, "glBlendEquationSeparateIndexedAMD");
		FetchProcAddress(glBlendFuncIndexedAMD, "glBlendFuncIndexedAMD");
		FetchProcAddress(glBlendFuncSeparateIndexedAMD, "glBlendFuncSeparateIndexedAMD");

		//framebuffer sample positions
		FetchProcAddress(AMD_framebuffer_sample_positions, "AMD_framebuffer_sample_positions");
		FetchProcAddress(glFramebufferSamplePositionsfvAMD, "glFramebufferSamplePositionsfvAMD");
		FetchProcAddress(glGetFramebufferParameterfvAMD, "glGetFramebufferParameterfvAMD");
		FetchProcAddress(glGetNamedFramebufferParameterfvAMD, "glGetNamedFramebufferParameterfvAMD");
		FetchProcAddress(glNamedFramebufferSamplePositionsfvAMD, "glNamedFramebufferSamplePositionsfvAMD");

		//gcn shader
		FetchProcAddress(AMD_gcn_shader, "AMD_gcn_shader");

		//gpu shader half float
		FetchProcAddress(AMD_gpu_shader_half_float, "AMD_gpu_shader_half_float");

		//gpu shader int16
		FetchProcAddress(AMD_gpu_shader_int16, "AMD_gpu_shader_int16");

		//gpu shader int64
		FetchProcAddress(AMD_gpu_shader_int64, "AMD_gpu_shader_int64");

		//interleaved elements
		FetchProcAddress(AMD_interleaved_elements, "AMD_interleaved_elements");
		FetchProcAddress(glVertexAttribParameteriAMD, "glVertexAttribParameteriAMD");

		//multi draw indirect
		FetchProcAddress(AMD_multi_draw_indirect, "AMD_multi_draw_indirect");
		FetchProcAddress(glMultiDrawArraysIndirectAMD, "glMultiDrawArraysIndirectAMD");
		FetchProcAddress(glMultiDrawElementsIndirectAMD, "glMultiDrawElementsIndirectAMD");

		//name gen delete
		FetchProcAddress(AMD_name_gen_delete, "AMD_name_gen_delete");
		FetchProcAddress(glDeleteNamesAMD, "glDeleteNamesAMD");
		FetchProcAddress(glGenNamesAMD, "glGenNamesAMD");
		FetchProcAddress(glIsNameAMD, "glIsNameAMD");

		//occlusion query event
		FetchProcAddress(AMD_occlusion_query_event, "AMD_occlusion_query_event");
		FetchProcAddress(glQueryObjectParameteruiAMD, "glQueryObjectParameteruiAMD");

		//performance monitor
		FetchProcAddress(AMD_performance_monitor, "AMD_performance_monitor");
		FetchProcAddress(glBeginPerfMonitorAMD, "glBeginPerfMonitorAMD");
		FetchProcAddress(glDeletePerfMonitorsAMD, "glDeletePerfMonitorsAMD");
		FetchProcAddress(glEndPerfMonitorAMD, "glEndPerfMonitorAMD");
		FetchProcAddress(glGenPerfMonitorsAMD, "glGenPerfMonitorsAMD");
		FetchProcAddress(glGetPerfMonitorCounterDataAMD, "glGetPerfMonitorCounterDataAMD");
		FetchProcAddress(glGetPerfMonitorCounterInfoAMD, "glGetPerfMonitorCounterInfoAMD");
		FetchProcAddress(glGetPerfMonitorCounterStringAMD, "glGetPerfMonitorCounterStringAMD");
		FetchProcAddress(glGetPerfMonitorCountersAMD, "glGetPerfMonitorCountersAMD");
		FetchProcAddress(glGetPerfMonitorGroupStringAMD, "glGetPerfMonitorGroupStringAMD");
		FetchProcAddress(glGetPerfMonitorGroupsAMD, "glGetPerfMonitorGroupsAMD");
		FetchProcAddress(glSelectPerfMonitorCountersAMD, "glSelectPerfMonitorCountersAMD");

		//pinned memory
		FetchProcAddress(AMD_pinned_memory, "AMD_pinned_memory");

		//program binary Z400
		FetchProcAddress(AMD_program_binary_Z400, "AMD_program_binary_Z400");

		//query buffer object
		FetchProcAddress(AMD_query_buffer_object, "AMD_query_buffer_object");

		//sample positions
		FetchProcAddress(AMD_sample_positions, "AMD_sample_positions");
		FetchProcAddress(glSetMultisamplefvAMD, "glSetMultisamplefvAMD");

		//seamless cubemap per texture
		FetchProcAddress(AMD_seamless_cubemap_per_texture, "AMD_seamless_cubemap_per_texture");

		//shader atomic counter ops
		FetchProcAddress(AMD_shader_atomic_counter_ops, "AMD_shader_atomic_counter_ops");

		//shader ballot
		FetchProcAddress(AMD_shader_ballot, "AMD_shader_ballot");

		//shader explicit vertex parameter
		FetchProcAddress(AMD_shader_explicit_vertex_parameter, "AMD_shader_explicit_vertex_parameter");

		//shader stencil export
		FetchProcAddress(AMD_shader_stencil_export, "AMD_shader_stencil_export");

		//shader stencil value export
		FetchProcAddress(AMD_shader_stencil_value_export, "AMD_shader_stencil_value_export");

		//shader trinary minmax
		FetchProcAddress(AMD_shader_trinary_minmax, "AMD_shader_trinary_minmax");

		//sparse texture
		FetchProcAddress(AMD_sparse_texture, "AMD_sparse_texture");
		FetchProcAddress(glTexStorageSparseAMD, "glTexStorageSparseAMD");
		FetchProcAddress(glTextureStorageSparseAMD, "glTextureStorageSparseAMD");

		//stencil operation extended
		FetchProcAddress(AMD_stencil_operation_extended, "AMD_stencil_operation_extended");
		FetchProcAddress(glStencilOpValueAMD, "glStencilOpValueAMD");

		//texture gather bias lod
		FetchProcAddress(AMD_texture_gather_bias_lod, "AMD_texture_gather_bias_lod");

		//texture texture4
		FetchProcAddress(AMD_texture_texture4, "AMD_texture_texture4");

		//transform feedback3 lines triangles
		FetchProcAddress(AMD_transform_feedback3_lines_triangles, "AMD_transform_feedback3_lines_triangles");

		//transform feedback4 
		FetchProcAddress(AMD_transform_feedback4, "AMD_transform_feedback4");

		//vertex shader layer
		FetchProcAddress(AMD_vertex_shader_layer, "AMD_vertex_shader_layer");

		//vertex shader tessellator
		FetchProcAddress(AMD_vertex_shader_tessellator, "AMD_vertex_shader_tessellator");
		FetchProcAddress(glTessellationFactorAMD, "glTessellationFactorAMD");
		FetchProcAddress(glTessellationModeAMD, "glTessellationModeAMD");

		//vertex shader viewport index
		FetchProcAddress(AMD_vertex_shader_viewport_index, "AMD_vertex_shader_viewport_index");
	}

#pragma endregion AMD Extensions

	//OpenGL Android Extensions
#pragma region Android
	//ANDROID_extension_pack_es31a
	bool ANDROID_extension_pack_es31a = false;

	//*< load Android Extensions
	void LoadAndroidExtensions()
	{
		FetchProcAddress(ANDROID_extension_pack_es31a, "ANDROID_extension_pack_es31a");
	}
#pragma endregion Android Extensions

	//OpenGL Angle Extensions
#pragma region Angle

	enum OpenGL_Angle_t
	{
		//framebuffer blit
		gl_draw_framebuffer_binding_angle = 0x8ca6,
		gl_read_framebuffer_angle = 0x8ca8,
		gl_draw_framebuffer_angle = 0x8ca9,
		gl_read_framebuffer_binding_angle = 0x8caa,

		//framebuffer multisample
		gl_renderbuffer_samples_angle = 0x8cab,
		gl_framebuffer_incomplete_multisample_angle = 0x8d56,
		gl_max_samples_angle = 0x8d57,

		//instanced arrays
		gl_vertex_attrib_array_divisor_angle = 0x88fe,

		//pack reverse row order
		gl_pack_reverse_row_order_angle = 0x93a4,

		//program binary
		gl_program_binary_angle = 0x93a6,

		//texture compression
		gl_compressed_rgb_s3tc_dxt1_angle = 0x83f0,
		gl_compressed_rgba_s3tc_dxt1_angle = 0x83f1,
		gl_compressed_rgba_s3tc_dxt3_angle = 0x83f2,
		gl_compressed_rgba_s3tc_dxt5_angle = 0x83f3,

		//texture usage
		gl_texture_usage_angle = 0x93a2,
		gl_framebuffer_attachment_angle = 0x93a3,

		//timer query
		gl_query_counter_bits_angle = 0x8864,
		gl_current_query_angle = 0x8865,
		gl_query_result_angle = 0x8866,
		gl_query_result_available_angle = 0x8867,
		gl_time_elapsed_angle = 0x88bf,
		gl_timestamp_angle = 0x8e28,

		//translated shader source
		gl_translated_shader_source_length_angle = 0x93a0,
	};

	//depth texture
	bool ANGLE_depth_texture = false;

	//framebuffer blit
	bool ANGLE_framebuffer_blit = false;
	void (*glBlitFramebufferANGLE) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;

	//framebuffer multisample
	bool ANGLE_framebuffer_multisample = false;
	void (*glRenderbufferStorageMultisampleANGLE) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;

	//instanced arrays
	bool ANGLE_instanced_arrays = false;
	void (*glDrawArraysInstancedANGLE) (GLenum mode, GLint first, GLsizei count, GLsizei primcount) = nullptr;
	void (*glDrawElementsInstancedANGLE) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) = nullptr;
	void (*glVertexAttribDivisorANGLE) (GLuint index, GLuint divisor) = nullptr;

	//pack reverse row order
	bool ANGLE_pack_reverse_row_order = false;

	//program binary
	bool ANGLE_program_binary = false;

	//texture compression dxt1
	bool ANGLE_texture_compression_dxt1 = false;

	//texture compression dxt3
	bool ANGLE_texture_compression_dxt3 = false;

	//texture compression dxt5
	bool ANGLE_texture_compression_dxt5 = false;

	//texture usage
	bool ANGLE_texture_usage = false;

	//timer query
	bool ANGLE_timer_query = false;
	void (*glBeginQueryANGLE) (GLenum target, GLuint id) = nullptr;
	void (*glDeleteQueriesANGLE) (GLsizei n, const GLuint* ids) = nullptr;
	void (*glEndQueryANGLE) (GLenum target) = nullptr;
	void (*glGenQueriesANGLE) (GLsizei n, GLuint* ids) = nullptr;
	void (*glGetQueryObjecti64vANGLE) (GLuint id, GLenum pname, GLint64* params) = nullptr;
	void (*glGetQueryObjectivANGLE) (GLuint id, GLenum pname, GLint* params) = nullptr;
	void (*glGetQueryObjectui64vANGLE) (GLuint id, GLenum pname, GLuint64* params) = nullptr;
	void (*glGetQueryObjectuivANGLE) (GLuint id, GLenum pname, GLuint* params) = nullptr;
	void (*glGetQueryivANGLE) (GLenum target, GLenum pname, GLint* params) = nullptr;
	GLboolean(*glIsQueryANGLE) (GLuint id) = nullptr;
	void (*glQueryCounterANGLE) (GLuint id, GLenum target) = nullptr;

	//translated shader source
	bool ANGLE_translated_shader_source = false;
	void (*glGetTranslatedShaderSourceANGLE) (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source) = nullptr;

	//*< load Angle Extensions
	void LoadAngleExtensions()
	{
		//depth texture
		FetchProcAddress(ANGLE_depth_texture, "ANGLE_depth_texture");

		//framebuffer blit
		FetchProcAddress(ANGLE_framebuffer_blit, "ANGLE_framebuffer_blit");
		FetchProcAddress(glBlitFramebufferANGLE, "glBlitFramebufferANGLE");

		//framebuffer multisample
		FetchProcAddress(ANGLE_framebuffer_multisample, "ANGLE_framebuffer_multisample");
		FetchProcAddress(glRenderbufferStorageMultisampleANGLE, "glRenderbufferStorageMultisampleANGLE");

		//instanced arrays
		FetchProcAddress(ANGLE_instanced_arrays, "ANGLE_instanced_arrays");		
		FetchProcAddress(glDrawArraysInstancedANGLE, "glDrawArraysInstancedANGLE");
		FetchProcAddress(glDrawElementsInstancedANGLE, "glDrawElementsInstancedANGLE");
		FetchProcAddress(glVertexAttribDivisorANGLE, "glVertexAttribDivisorANGLE");

		//pack reverse row order
		FetchProcAddress(ANGLE_pack_reverse_row_order, "ANGLE_pack_reverse_row_order");

		//program binary
		FetchProcAddress(ANGLE_program_binary, "ANGLE_program_binary");

		//texture compression dxt1
		FetchProcAddress(ANGLE_texture_compression_dxt1, "ANGLE_texture_compression_dxt1");

		//texture compression dxt3
		FetchProcAddress(ANGLE_texture_compression_dxt3, "ANGLE_texture_compression_dxt3");

		//texture compression dxt5
		FetchProcAddress(ANGLE_texture_compression_dxt5, "ANGLE_texture_compression_dxt5");

		//texture usage
		FetchProcAddress(ANGLE_texture_usage, "ANGLE_texture_usage");

		//timer query
		FetchProcAddress(ANGLE_timer_query, "ANGLE_timer_query");
		FetchProcAddress(glBeginQueryANGLE, "glBeginQueryANGLE");
		FetchProcAddress(glDeleteQueriesANGLE, "glDeleteQueriesANGLE");
		FetchProcAddress(glEndQueryANGLE, "glEndQueryANGLE");
		FetchProcAddress(glGenQueriesANGLE, "glGenQueriesANGLE");
		FetchProcAddress(glGetQueryObjecti64vANGLE, "glGetQueryObjecti64vANGLE");
		FetchProcAddress(glGetQueryObjectivANGLE, "glGetQueryObjectivANGLE");
		FetchProcAddress(glGetQueryObjectui64vANGLE, "glGetQueryObjectui64vANGLE");
		FetchProcAddress(glGetQueryObjectuivANGLE, "glGetQueryObjectuivANGLE");
		FetchProcAddress(glGetQueryivANGLE, "glGetQueryivANGLE");
		FetchProcAddress(glIsQueryANGLE, "glIsQueryANGLE");
		FetchProcAddress(glQueryCounterANGLE, "glQueryCounterANGLE");

		//translated shader source
		FetchProcAddress(ANGLE_translated_shader_source, "ANGLE_translated_shader_source");
		FetchProcAddress(glGetTranslatedShaderSourceANGLE, "glGetTranslatedShaderSourceANGLE");
	}

#pragma endregion Angle Extensions

	//OpenGL Apple Extensions
#pragma region Apple

	enum openGL_Apple_t
	{
		//aux depth stencil
		gl_aux_depth_stencil_apple = 0x8a14,

		//client storage,
		gl_unpack_client_storage_apple = 0x85b2,

		//clip distance,
		gl_max_clip_distances_apple = 0x0d32,
		gl_clip_distance0_apple = 0x3000,
		gl_clip_distance1_apple = 0x3001,
		gl_clip_distance2_apple = 0x3002,
		gl_clip_distance3_apple = 0x3003,
		gl_clip_distance4_apple = 0x3004,
		gl_clip_distance5_apple = 0x3005,
		gl_clip_distance6_apple = 0x3006,
		gl_clip_distance7_apple = 0x3007,

		//element array,
		gl_element_array_apple = 0x8a0c,
		gl_element_array_type_apple = 0x8a0d,
		gl_element_array_pointer_apple = 0x8a0e,

		//fence,
		gl_draw_pixels_apple = 0x8a0a,
		gl_fence_apple = 0x8a0b,

		//float pixels,
		gl_half_apple = 0x140b,
		gl_rgba_float32_apple = 0x8814,
		gl_rgb_float32_apple = 0x8815,
		gl_alpha_float32_apple = 0x8816,
		gl_intensity_float32_apple = 0x8817,
		gl_luminance_float32_apple = 0x8818,
		gl_luminance_alpha_float32_apple = 0x8819,
		gl_rgba_float16_apple = 0x881a,
		gl_rgb_float16_apple = 0x881b,
		gl_alpha_float16_apple = 0x881c,
		gl_intensity_float16_apple = 0x881d,
		gl_luminance_float16_apple = 0x881e,
		gl_luminance_alpha_float16_apple = 0x881f,
		gl_color_float_apple = 0x8a0f,

		//flush buffer range,
		gl_buffer_serialized_modify_apple = 0x8a12,
		gl_buffer_flushing_unmap_apple = 0x8a13,

		//framebuffer multisample,
		gl_draw_framebuffer_binding_apple = 0x8ca6,
		gl_read_framebuffer_apple = 0x8ca8,
		gl_draw_framebuffer_apple = 0x8ca9,
		gl_read_framebuffer_binding_apple = 0x8caa,
		gl_renderbuffer_samples_apple = 0x8cab,
		gl_framebuffer_incomplete_multisample_apple = 0x8d56,
		gl_max_samples_apple = 0x8d57,

		//object purgeable,
		gl_buffer_object_apple = 0x85b3,
		gl_released_apple = 0x8a19,
		gl_volatile_apple = 0x8a1a,
		gl_retained_apple = 0x8a1b,
		gl_undefined_apple = 0x8a1c,
		gl_purgeable_apple = 0x8a1d,

		//pixel buffer,
		gl_min_pbuffer_viewport_dims_apple = 0x8a10,

		//rgb 422,
		gl_unsigned_short_8_8_apple = 0x85ba,
		gl_unsigned_short_8_8_rev_apple = 0x85bb,
		gl_rgb_422_apple = 0x8a1f,
		gl_rgb_raw_422_apple = 0x8a51,

		//row bytes,
		gl_pack_row_bytes_apple = 0x8a15,
		gl_unpack_row_bytes_apple = 0x8a16,

		//specular vector,
		gl_light_model_specular_vector_apple = 0x85b0,

		//sync,
		gl_sync_flush_commands_bit_apple = 0x00000001,
		gl_sync_object_apple = 0x8a53,
		gl_max_server_wait_timeout_apple = 0x9111,
		gl_object_type_apple = 0x9112,
		gl_sync_condition_apple = 0x9113,
		gl_sync_status_apple = 0x9114,
		gl_sync_flags_apple = 0x9115,
		gl_sync_fence_apple = 0x9116,
		gl_sync_gpu_commands_complete_apple = 0x9117,
		gl_unsignaled_apple = 0x9118,
		gl_signaled_apple = 0x9119,
		gl_already_signaled_apple = 0x911a,
		gl_timeout_expired_apple = 0x911b,
		gl_condition_satisfied_apple = 0x911c,
		gl_wait_failed_apple = 0x911d,
		gl_timeout_ignored_apple = 0xffffffffffffffffull,

		//texture format bgra_8888,
		gl_bgra_ext = 0x80e1,
		gl_bgra8_ext = 0x93a1,

		//texture max level,
		gl_texture_max_level_apple = 0x813d,

		//texture packed float,
		gl_r11f_g11f_b10f_apple = 0x8c3a,
		gl_unsigned_int_10f_11f_11f_rev_apple = 0x8c3b,
		gl_rgb9_e5_apple = 0x8c3d,
		gl_unsigned_int_5_9_9_9_rev_apple = 0x8c3e,

		//texture range,
		gl_texture_range_length_apple = 0x85b7,
		gl_texture_range_pointer_apple = 0x85b8,
		gl_texture_storage_hint_apple = 0x85bc,
		gl_storage_private_apple = 0x85bd,
		gl_storage_cached_apple = 0x85be,
		gl_storage_shared_apple = 0x85bf,

		//transform hint,
		gl_transform_hint_apple = 0x85b1,

		//vertex array object,
		gl_vertex_array_binding_apple = 0x85b5,

		//vertex array range,
		gl_vertex_array_range_apple = 0x851d,
		gl_vertex_array_range_length_apple = 0x851e,
		gl_vertex_array_storage_hint_apple = 0x851f,
		gl_max_vertex_array_range_element_apple = 0x8520,
		gl_vertex_array_range_pointer_apple = 0x8521,

		//vertex program evaluators,
		gl_vertex_attrib_map1_apple = 0x8a00,
		gl_vertex_attrib_map2_apple = 0x8a01,
		gl_vertex_attrib_map1_size_apple = 0x8a02,
		gl_vertex_attrib_map1_coeff_apple = 0x8a03,
		gl_vertex_attrib_map1_order_apple = 0x8a04,
		gl_vertex_attrib_map1_domain_apple = 0x8a05,
		gl_vertex_attrib_map2_size_apple = 0x8a06,
		gl_vertex_attrib_map2_coeff_apple = 0x8a07,
		gl_vertex_attrib_map2_order_apple = 0x8a08,
		gl_vertex_attrib_map2_domain_apple = 0x8a09,

		//ycbcr 422,
		gl_ycbcr_422_apple = 0x85b9,
	};

	//aux depth stencil
	bool APPLE_aux_depth_stencil = false;

	//client storage
	bool APPLE_client_storage = false;

	//clip distance
	bool APPLE_clip_distance = false;

	//color buffer packed float
	bool APPLE_color_buffer_packed_float = false;

	//copy texture levels
	bool APPLE_copy_texture_levels = false;
	void (*glCopyTextureLevelsAPPLE) (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount) = nullptr;

	//element array
	bool APPLE_element_array = false;
	void (*glDrawElementArrayAPPLE) (GLenum mode, GLint first, GLsizei count) = nullptr;
	void (*glDrawRangeElementArrayAPPLE) (GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count) = nullptr;
	void (*glElementPointerAPPLE) (GLenum type, const void* pointer) = nullptr;
	void (*glMultiDrawElementArrayAPPLE) (GLenum mode, const GLint* first, const GLsizei* count, GLsizei primcount) = nullptr;
	void (*glMultiDrawRangeElementArrayAPPLE) (GLenum mode, GLuint start, GLuint end, const GLint* first, const GLsizei* count, GLsizei primcount) = nullptr;

	//fence
	bool APPLE_fence = false;
	void (*glDeleteFencesAPPLE) (GLsizei n, const GLuint* fences) = nullptr;
	void (*glFinishFenceAPPLE) (GLuint fence) = nullptr;
	void (*glFinishObjectAPPLE) (GLenum object, GLint name) = nullptr;
	void (*glGenFencesAPPLE) (GLsizei n, GLuint* fences) = nullptr;
	GLboolean(*glIsFenceAPPLE) (GLuint fence) = nullptr;
	void (*glSetFenceAPPLE) (GLuint fence) = nullptr;
	GLboolean(*glTestFenceAPPLE) (GLuint fence) = nullptr;
	GLboolean(*glTestObjectAPPLE) (GLenum object, GLuint name) = nullptr;

	//float pixels
	bool APPLE_float_pixels = false;

	//flush buffer range
	bool APPLE_flush_buffer_range = false;
	void (*glBufferParameteriAPPLE) (GLenum target, GLenum pname, GLint param) = nullptr;
	void (*glFlushMappedBufferRangeAPPLE) (GLenum target, GLintptr offset, GLsizeiptr size) = nullptr;

	//framebuffer multisample
	bool APPLE_framebuffer_multisample = false;
	void (*glRenderbufferStorageMultisampleAPPLE) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void (*glResolveMultisampleFramebufferAPPLE) (void) = nullptr;

	//object purgeable
	bool APPLE_object_purgeable = false;
	void (*glGetObjectParameterivAPPLE) (GLenum objectType, GLuint name, GLenum pname, GLint* params) = nullptr;
	GLenum(*glObjectPurgeableAPPLE) (GLenum objectType, GLuint name, GLenum option) = nullptr;
	GLenum(*glObjectUnpurgeableAPPLE) (GLenum objectType, GLuint name, GLenum option) = nullptr;

	//pixel buffer
	bool APPLE_pixel_buffer = false;

	//rgb 422
	bool APPLE_rgb_422 = false;

	//row bytes
	bool APPLE_row_bytes = false;

	//specular vector
	bool APPLE_specular_vector = false;

	//sync
	bool APPLE_sync = false;
	GLenum(*glClientWaitSyncAPPLE) (GLsync GLsync, GLbitfield flags, GLuint64 timeout) = nullptr;
	void (*glDeleteSyncAPPLE) (GLsync GLsync) = nullptr;
	GLsync(*glFenceSyncAPPLE) (GLenum condition, GLbitfield flags) = nullptr;
	void (*glGetInteger64vAPPLE) (GLenum pname, GLint64* params) = nullptr;
	void (*glGetSyncivAPPLE) (GLsync GLsync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) = nullptr;
	GLboolean(*glIsSyncAPPLE) (GLsync GLsync) = nullptr;
	void (*glWaitSyncAPPLE) (GLsync GLsync, GLbitfield flags, GLuint64 timeout) = nullptr;

	//texture 2D limited npot
	bool APPLE_texture_2D_limited_npot = false;

	//texture format BGRA8888
	bool APPLE_texture_format_BGRA8888 = false;

	//texture max level
	bool APPLE_texture_max_level = false;

	//texture packed float
	bool APPLE_texture_packed_float = false;

	//texture range
	bool APPLE_texture_range = false;
	void (*glGetTexParameterPointervAPPLE) (GLenum target, GLenum pname, void** params) = nullptr;
	void (*glTextureRangeAPPLE) (GLenum target, GLsizei length, void* pointer) = nullptr;

	//transform hint
	bool APPLE_transform_hint = false;

	//vertex array object
	bool APPLE_vertex_array_object = false;
	void (*glBindVertexArrayAPPLE) (GLuint array) = nullptr;
	void (*glDeleteVertexArraysAPPLE) (GLsizei n, const GLuint* arrays) = nullptr;
	void (*glGenVertexArraysAPPLE) (GLsizei n, const GLuint* arrays) = nullptr;
	GLboolean(*glIsVertexArrayAPPLE) (GLuint array) = nullptr;

	//vertex array range
	bool APPLE_vertex_array_range = false;
	void (*glFlushVertexArrayRangeAPPLE) (GLsizei length, void* pointer) = nullptr;
	void (*glVertexArrayParameteriAPPLE) (GLenum pname, GLint param) = nullptr;
	void (*glVertexArrayRangeAPPLE) (GLsizei length, void* pointer) = nullptr;

	//vertex program evaluators
	bool APPLE_vertex_program_evaluators = false;
	void (*glDisableVertexAttribAPPLE) (GLuint index, GLenum pname) = nullptr;
	void (*glEnableVertexAttribAPPLE) (GLuint index, GLenum pname) = nullptr;
	GLboolean(*glIsVertexAttribEnabledAPPLE) (GLuint index, GLenum pname) = nullptr;
	void (*glMapVertexAttrib1dAPPLE) (GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble* points) = nullptr;
	void (*glMapVertexAttrib1fAPPLE) (GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points) = nullptr;
	void (*glMapVertexAttrib2dAPPLE) (GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points) = nullptr;
	void (*glMapVertexAttrib2fAPPLE) (GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points) = nullptr;

	//ycbcr 422
	bool APPLE_ycbcr_422 = false;

	//*< load Apple Extensions
	void LoadAppleExtensions()
	{
		//aux depth stencil
		FetchProcAddress(APPLE_aux_depth_stencil, "APPLE_aux_depth_stencil");

		//client storage
		FetchProcAddress(APPLE_client_storage, "APPLE_client_storage");

		//clip distance
		FetchProcAddress(APPLE_clip_distance, "APPLE_clip_distance");

		//color buffer packed float
		FetchProcAddress(APPLE_color_buffer_packed_float, "APPLE_color_buffer_packed_float");

		//copy texture levels
		FetchProcAddress(APPLE_copy_texture_levels, "APPLE_copy_texture_levels");
		FetchProcAddress(glCopyTextureLevelsAPPLE, "glCopyTextureLevelsAPPLE");

		//element array
		FetchProcAddress(APPLE_element_array, "APPLE_element_array");		
		FetchProcAddress(glDrawElementArrayAPPLE, "glDrawElementArrayAPPLE");
		FetchProcAddress(glDrawRangeElementArrayAPPLE, "glDrawRangeElementArrayAPPLE");
		FetchProcAddress(glElementPointerAPPLE, "glElementPointerAPPLE");
		FetchProcAddress(glMultiDrawElementArrayAPPLE, "glMultiDrawElementArrayAPPLE");
		FetchProcAddress(glMultiDrawRangeElementArrayAPPLE, "glMultiDrawRangeElementArrayAPPLE");

		//fence
		FetchProcAddress(APPLE_fence, "APPLE_fence");
		FetchProcAddress(glDeleteFencesAPPLE, "glDeleteFencesAPPLE");
		FetchProcAddress(glFinishFenceAPPLE, "glFinishFenceAPPLE");
		FetchProcAddress(glFinishObjectAPPLE, "glFinishObjectAPPLE");
		FetchProcAddress(glGenFencesAPPLE, "glGenFencesAPPLE");
		FetchProcAddress(glIsFenceAPPLE, "glIsFenceAPPLE");
		FetchProcAddress(glSetFenceAPPLE, "glSetFenceAPPLE");
		FetchProcAddress(glTestFenceAPPLE, "glTestFenceAPPLE");
		FetchProcAddress(glTestObjectAPPLE, "glTestObjectAPPLE");

		//float pixels
		FetchProcAddress(APPLE_float_pixels, "APPLE_float_pixels");

		//flush buffer range
		FetchProcAddress(APPLE_flush_buffer_range, "APPLE_flush_buffer_range");
		FetchProcAddress(glBufferParameteriAPPLE, "glBufferParameteriAPPLE");
		FetchProcAddress(glFlushMappedBufferRangeAPPLE, "glFlushMappedBufferRangeAPPLE");

		//framebuffer multisample
		FetchProcAddress(APPLE_framebuffer_multisample, "APPLE_framebuffer_multisample");
		FetchProcAddress(glRenderbufferStorageMultisampleAPPLE, "glRenderbufferStorageMultisampleAPPLE");
		FetchProcAddress(glResolveMultisampleFramebufferAPPLE, "glResolveMultisampleFramebufferAPPLE");

		//object purgeable
		FetchProcAddress(APPLE_object_purgeable, "APPLE_object_purgeable");
		FetchProcAddress(glGetObjectParameterivAPPLE, "glGetObjectParameterivAPPLE");
		FetchProcAddress(glObjectPurgeableAPPLE, "glObjectPurgeableAPPLE");
		FetchProcAddress(glObjectUnpurgeableAPPLE, "glObjectUnpurgeableAPPLE");

		//pixel buffer
		FetchProcAddress(APPLE_pixel_buffer, "APPLE_pixel_buffer");

		//rgb 422
		FetchProcAddress(APPLE_rgb_422, "APPLE_rgb_422");

		//row bytes
		FetchProcAddress(APPLE_row_bytes, "APPLE_row_bytes");

		//specular vector
		FetchProcAddress(APPLE_specular_vector, "APPLE_specular_vector");

		//sync
		FetchProcAddress(APPLE_sync, "APPLE_sync");
		FetchProcAddress(glClientWaitSyncAPPLE, "glClientWaitSyncAPPLE");
		FetchProcAddress(glDeleteSyncAPPLE, "glDeleteSyncAPPLE");
		FetchProcAddress(glFenceSyncAPPLE, "glFenceSyncAPPLE");
		FetchProcAddress(glGetInteger64vAPPLE, "glGetInteger64vAPPLE");
		FetchProcAddress(glGetSyncivAPPLE, "glGetSyncivAPPLE");
		FetchProcAddress(glIsSyncAPPLE, "glIsSyncAPPLE");
		FetchProcAddress(glWaitSyncAPPLE, "glWaitSyncAPPLE");

		//texture 2D limited npot
		FetchProcAddress(APPLE_texture_2D_limited_npot, "APPLE_texture_2D_limited_npot");

		//texture format BGRA8888
		FetchProcAddress(APPLE_texture_format_BGRA8888, "APPLE_texture_format_BGRA8888");

		//texture max level
		FetchProcAddress(APPLE_texture_max_level, "APPLE_texture_max_level");

		//texture packed float
		FetchProcAddress(APPLE_texture_packed_float, "APPLE_texture_packed_float");

		//texture range
		FetchProcAddress(APPLE_texture_range, "APPLE_texture_range");
		FetchProcAddress(glGetTexParameterPointervAPPLE, "glGetTexParameterPointervAPPLE");
		FetchProcAddress(glTextureRangeAPPLE, "glTextureRangeAPPLE");

		//transform hint
		FetchProcAddress(APPLE_transform_hint, "APPLE_transform_hint");

		//vertex array object
		FetchProcAddress(APPLE_vertex_array_object, "APPLE_vertex_array_object");
		FetchProcAddress(glBindVertexArrayAPPLE, "glBindVertexArrayAPPLE");
		FetchProcAddress(glDeleteVertexArraysAPPLE, "glDeleteVertexArraysAPPLE");
		FetchProcAddress(glGenVertexArraysAPPLE, "glGenVertexArraysAPPLE");
		FetchProcAddress(glIsVertexArrayAPPLE, "glIsVertexArrayAPPLE");

		//vertex array range
		FetchProcAddress(APPLE_vertex_array_range, "APPLE_vertex_array_range");
		FetchProcAddress(glFlushVertexArrayRangeAPPLE, "glFlushVertexArrayRangeAPPLE");
		FetchProcAddress(glVertexArrayParameteriAPPLE, "glVertexArrayParameteriAPPLE");
		FetchProcAddress(glVertexArrayRangeAPPLE, "glVertexArrayRangeAPPLE");

		//vertex program evaluators
		FetchProcAddress(APPLE_vertex_program_evaluators, "APPLE_vertex_program_evaluators");
		FetchProcAddress(glDisableVertexAttribAPPLE, "glDisableVertexAttribAPPLE");
		FetchProcAddress(glEnableVertexAttribAPPLE, "glEnableVertexAttribAPPLE");
		FetchProcAddress(glIsVertexAttribEnabledAPPLE, "glIsVertexAttribEnabledAPPLE");
		FetchProcAddress(glMapVertexAttrib1dAPPLE, "glMapVertexAttrib1dAPPLE");
		FetchProcAddress(glMapVertexAttrib1fAPPLE, "glMapVertexAttrib1fAPPLE");
		FetchProcAddress(glMapVertexAttrib2dAPPLE, "glMapVertexAttrib2dAPPLE");
		FetchProcAddress(glMapVertexAttrib2fAPPLE, "glMapVertexAttrib2fAPPLE");

		//ycbcr 422
		FetchProcAddress(APPLE_ycbcr_422, "APPLE_ycbcr_422");
	}

#pragma endregion Apple Extensions

	//OpenGL ARB Extensions
#pragma region ARB
	typedef char GLcharARB;
	typedef unsigned int GLhandleARB;
	typedef int GLfixed;
	typedef struct _cl_context* cl_context;
	typedef struct _cl_event* cl_event;
	typedef ptrdiff_t GLintptrARB;
	typedef ptrdiff_t GLsizeiptrARB;

	enum OpenGL_ARB_t
	{
		//ES2 compatibility
		gl_fixed = 0x140c,
		gl_implementation_color_read_type = 0x8b9a,
		gl_implementation_color_read_format = 0x8b9b,
		gl_rgb565 = 0x8d62,
		gl_low_float = 0x8df0,
		gl_medium_float = 0x8df1,
		gl_high_float = 0x8df2,
		gl_low_int = 0x8df3,
		gl_medium_int = 0x8df4,
		gl_high_int = 0x8df5,
		gl_shader_binary_formats = 0x8df8,
		gl_num_shader_binary_formats = 0x8df9,
		gl_shader_compiler = 0x8dfa,
		gl_max_vertex_uniform_vectors = 0x8dfb,
		gl_max_varying_vectors = 0x8dfc,
		gl_max_fragment_uniform_vectors = 0x8dfd,

		//es3 2 compatibility
		gl_primitive_bounding_box_arb = 0x92be,
		gl_multisample_line_width_range_arb = 0x9381,
		gl_multisample_line_width_granularity_arb = 0x9382,

		//es3 compatibility
		gl_texture_immutable_levels = 0x82df,
		gl_primitive_restart_fixed_index = 0x8d69,
		gl_any_samples_passed_conservative = 0x8d6a,
		gl_max_element_index = 0x8d6b,
		gl_compressed_r11_eac = 0x9270,
		gl_compressed_signed_r11_eac = 0x9271,
		gl_compressed_rg11_eac = 0x9272,
		gl_compressed_signed_rg11_eac = 0x9273,
		gl_compressed_rgb8_etc2 = 0x9274,
		gl_compressed_srgb8_etc2 = 0x9275,
		gl_compressed_rgb8_punchthrough_alpha1_etc2 = 0x9276,
		gl_compressed_srgb8_punchthrough_alpha1_etc2 = 0x9277,
		gl_compressed_rgba8_etc2_eac = 0x9278,
		gl_compressed_srgb8_alpha8_etc2_eac = 0x9279,

		//bindless texture
		gl_unsigned_int64_arb = 0x140f,

		//blend func extended
		gl_src1_color = 0x88f9,
		gl_one_minus_src1_color = 0x88fa,
		gl_one_minus_src1_alpha = 0x88fb,
		gl_max_dual_source_draw_buffers = 0x88fc,

		//buffer storage
		gl_map_read_bit = 0x0001,
		gl_map_write_bit = 0x0002,
		gl_map_persistent_bit = 0x00000040,
		gl_map_coherent_bit = 0x00000080,
		gl_dynamic_storage_bit = 0x0100,
		gl_client_storage_bit = 0x0200,
		gl_client_mapped_buffer_barrier_bit = 0x00004000,
		gl_buffer_immutable_storage = 0x821f,
		gl_buffer_storage_flags = 0x8220,

		//cl event
		gl_sync_cl_event_arb = 0x8240,
		gl_sync_cl_event_complete_arb = 0x8241,

		//clear texture
		gl_clear_texture = 0x9365,

		//clip control
		//gl_lower_left = 0x8ca1,
		//gl_upper_left = 0x8ca2,
		gl_clip_origin = 0x935c,
		gl_clip_depth_mode = 0x935d,
		gl_negative_one_to_one = 0x935e,
		gl_zero_to_one = 0x935f,

		//color buffer float
		gl_rgba_float_mode_arb = 0x8820,
		gl_clamp_vertex_color_arb = 0x891a,
		gl_clamp_fragment_color_arb = 0x891b,
		gl_clamp_read_color_arb = 0x891c,
		gl_fixed_only_arb = 0x891d,

		//compressed texture pixel storage
		gl_unpack_compressed_block_width = 0x9127,
		gl_unpack_compressed_block_height = 0x9128,
		gl_unpack_compressed_block_depth = 0x9129,
		gl_unpack_compressed_block_size = 0x912a,
		gl_pack_compressed_block_width = 0x912b,
		gl_pack_compressed_block_height = 0x912c,
		gl_pack_compressed_block_depth = 0x912d,
		gl_pack_compressed_block_size = 0x912e,

		//compute shader
		gl_compute_shader_bit = 0x00000020,
		gl_max_compute_shared_memory_size = 0x8262,
		gl_max_compute_uniform_components = 0x8263,
		gl_max_compute_atomic_counter_buffers = 0x8264,
		gl_max_compute_atomic_counters = 0x8265,
		gl_max_combined_compute_uniform_components = 0x8266,
		gl_compute_work_group_size = 0x8267,
		gl_max_compute_work_group_invocations = 0x90eb,
		gl_uniform_block_referenced_by_compute_shader = 0x90ec,
		gl_atomic_counter_buffer_referenced_by_compute_shader = 0x90ed,
		gl_dispatch_indirect_buffer = 0x90ee,
		gl_dispatch_indirect_buffer_binding = 0x90ef,
		gl_compute_shader = 0x91b9,
		gl_max_compute_uniform_blocks = 0x91bb,
		gl_max_compute_texture_image_units = 0x91bc,
		gl_max_compute_image_uniforms = 0x91bd,
		gl_max_compute_work_group_count = 0x91be,
		gl_max_compute_work_group_size = 0x91bf,

		//compute variable group size
		gl_max_compute_fixed_group_invocations_arb = 0x90eb,
		gl_max_compute_fixed_group_size_arb = 0x91bf,
		gl_max_compute_variable_group_invocations_arb = 0x9344,
		gl_max_compute_variable_group_size_arb = 0x9345,

		//conditional render inverted
		gl_query_wait_inverted = 0x8e17,
		gl_query_no_wait_inverted = 0x8e18,
		gl_query_by_region_wait_inverted = 0x8e19,
		gl_query_by_region_no_wait_inverted = 0x8e1a,

		//copy buffer
		gl_copy_read_buffer = 0x8f36,
		gl_copy_write_buffer = 0x8f37,

		//cull distance
		gl_max_cull_distances = 0x82f9,
		gl_max_combined_clip_and_cull_distances = 0x82fa,

		//debug output
		gl_debug_output_synchronous_arb = 0x8242,
		gl_debug_next_logged_message_length_arb = 0x8243,
		gl_debug_callback_function_arb = 0x8244,
		gl_debug_callback_user_param_arb = 0x8245,
		gl_debug_source_api_arb = 0x8246,
		gl_debug_source_window_system_arb = 0x8247,
		gl_debug_source_shader_compiler_arb = 0x8248,
		gl_debug_source_third_party_arb = 0x8249,
		gl_debug_source_application_arb = 0x824a,
		gl_debug_source_other_arb = 0x824b,
		gl_debug_type_error_arb = 0x824c,
		gl_debug_type_deprecated_behavior_arb = 0x824d,
		gl_debug_type_undefined_behavior_arb = 0x824e,
		gl_debug_type_portability_arb = 0x824f,
		gl_debug_type_performance_arb = 0x8250,
		gl_debug_type_other_arb = 0x8251,
		gl_max_debug_message_length_arb = 0x9143,
		gl_max_debug_logged_messages_arb = 0x9144,
		gl_debug_logged_messages_arb = 0x9145,
		gl_debug_severity_high_arb = 0x9146,
		gl_debug_severity_medium_arb = 0x9147,
		gl_debug_severity_low_arb = 0x9148,

		//depth buffer float
		gl_depth_component32f = 0x8cac,
		gl_depth32f_stencil8 = 0x8cad,
		gl_float_32_unsigned_int_24_8_rev = 0x8dad,

		//depth clamp
		gl_depth_clamp = 0x864f,

		//depth texture
		gl_depth_component16_arb = 0x81a5,
		gl_depth_component24_arb = 0x81a6,
		gl_depth_component32_arb = 0x81a7,
		gl_texture_depth_size_arb = 0x884a,
		gl_depth_texture_mode_arb = 0x884b,

		//direct state access
		gl_texture_target = 0x1006,
		gl_query_target = 0x82ea,

		//draw buffers
		gl_max_draw_buffers_arb = 0x8824,
		gl_draw_buffer0_arb = 0x8825,
		gl_draw_buffer1_arb = 0x8826,
		gl_draw_buffer2_arb = 0x8827,
		gl_draw_buffer3_arb = 0x8828,
		gl_draw_buffer4_arb = 0x8829,
		gl_draw_buffer5_arb = 0x882a,
		gl_draw_buffer6_arb = 0x882b,
		gl_draw_buffer7_arb = 0x882c,
		gl_draw_buffer8_arb = 0x882d,
		gl_draw_buffer9_arb = 0x882e,
		gl_draw_buffer10_arb = 0x882f,
		gl_draw_buffer11_arb = 0x8830,
		gl_draw_buffer12_arb = 0x8831,
		gl_draw_buffer13_arb = 0x8832,
		gl_draw_buffer14_arb = 0x8833,
		gl_draw_buffer15_arb = 0x8834,

		//draw indirect
		gl_draw_indirect_buffer = 0x8f3f,
		gl_draw_indirect_buffer_binding = 0x8f43,

		//enhanced layouts
		gl_location_component = 0x934a,
		gl_transform_feedback_buffer_index = 0x934b,
		gl_transform_feedback_buffer_stride = 0x934c,

		//explicit uniform location
		gl_max_uniform_locations = 0x826e,

		//fragment program
		gl_fragment_program_arb = 0x8804,
		gl_program_alu_instructions_arb = 0x8805,
		gl_program_tex_instructions_arb = 0x8806,
		gl_program_tex_indirections_arb = 0x8807,
		gl_program_native_alu_instructions_arb = 0x8808,
		gl_program_native_tex_instructions_arb = 0x8809,
		gl_program_native_tex_indirections_arb = 0x880a,
		gl_max_program_alu_instructions_arb = 0x880b,
		gl_max_program_tex_instructions_arb = 0x880c,
		gl_max_program_tex_indirections_arb = 0x880d,
		gl_max_program_native_alu_instructions_arb = 0x880e,
		gl_max_program_native_tex_instructions_arb = 0x880f,
		gl_max_program_native_tex_indirections_arb = 0x8810,
		gl_max_texture_coords_arb = 0x8871,
		gl_max_texture_image_units_arb = 0x8872,

		//fragment shader
		gl_fragment_shader_arb = 0x8b30,
		gl_max_fragment_uniform_components_arb = 0x8b49,
		gl_fragment_shader_derivative_hint_arb = 0x8b8b,

		//framebuffer no attachments
		gl_framebuffer_default_width = 0x9310,
		gl_framebuffer_default_height = 0x9311,
		gl_framebuffer_default_layers = 0x9312,
		gl_framebuffer_default_samples = 0x9313,
		gl_framebuffer_default_fixed_sample_locations = 0x9314,
		gl_max_framebuffer_width = 0x9315,
		gl_max_framebuffer_height = 0x9316,
		gl_max_framebuffer_layers = 0x9317,
		gl_max_framebuffer_samples = 0x9318,

		//framebuffer_object
		gl_invalid_framebuffer_operation = 0x0506,
		gl_framebuffer_attachment_color_encoding = 0x8210,
		gl_framebuffer_attachment_component_type = 0x8211,
		gl_framebuffer_attachment_red_size = 0x8212,
		gl_framebuffer_attachment_green_size = 0x8213,
		gl_framebuffer_attachment_blue_size = 0x8214,
		gl_framebuffer_attachment_alpha_size = 0x8215,
		gl_framebuffer_attachment_depth_size = 0x8216,
		gl_framebuffer_attachment_stencil_size = 0x8217,
		gl_framebuffer_default = 0x8218,
		gl_framebuffer_undefined = 0x8219,
		gl_depth_stencil_attachment = 0x821a,
		gl_index = 0x8222,
		gl_max_renderbuffer_size = 0x84e8,
		gl_depth_stencil = 0x84f9,
		gl_unsigned_int_24_8 = 0x84fa,
		gl_depth24_stencil8 = 0x88f0,
		gl_texture_stencil_size = 0x88f1,
		gl_unsigned_normalized = 0x8c17,
		//gl_srgb = 0x8c40,
		gl_draw_framebuffer_binding = 0x8ca6,
		gl_framebuffer_binding = 0x8ca6,
		gl_renderbuffer_binding = 0x8ca7,
		gl_read_framebuffer = 0x8ca8,
		gl_draw_framebuffer = 0x8ca9,
		gl_read_framebuffer_binding = 0x8caa,
		gl_renderbuffer_samples = 0x8cab,
		gl_framebuffer_attachment_object_type = 0x8cd0,
		gl_framebuffer_attachment_object_name = 0x8cd1,
		gl_framebuffer_attachment_texture_level = 0x8cd2,
		gl_framebuffer_attachment_texture_cube_map_face = 0x8cd3,
		gl_framebuffer_attachment_texture_layer = 0x8cd4,
		gl_framebuffer_complete = 0x8cd5,
		gl_framebuffer_incomplete_attachment = 0x8cd6,
		gl_framebuffer_incomplete_missing_attachment = 0x8cd7,
		gl_framebuffer_incomplete_draw_buffer = 0x8cdb,
		gl_framebuffer_incomplete_read_buffer = 0x8cdc,
		gl_framebuffer_unsupported = 0x8cdd,
		gl_max_color_attachments = 0x8cdf,
		gl_color_attachment0 = 0x8ce0,
		gl_color_attachment1 = 0x8ce1,
		gl_color_attachment2 = 0x8ce2,
		gl_color_attachment3 = 0x8ce3,
		gl_color_attachment4 = 0x8ce4,
		gl_color_attachment5 = 0x8ce5,
		gl_color_attachment6 = 0x8ce6,
		gl_color_attachment7 = 0x8ce7,
		gl_color_attachment8 = 0x8ce8,
		gl_color_attachment9 = 0x8ce9,
		gl_color_attachment10 = 0x8cea,
		gl_color_attachment11 = 0x8ceb,
		gl_color_attachment12 = 0x8cec,
		gl_color_attachment13 = 0x8ced,
		gl_color_attachment14 = 0x8cee,
		gl_color_attachment15 = 0x8cef,
		gl_depth_attachment = 0x8d00,
		gl_stencil_attachment = 0x8d20,
		gl_framebuffer = 0x8d40,
		gl_renderbuffer = 0x8d41,
		gl_renderbuffer_width = 0x8d42,
		gl_renderbuffer_height = 0x8d43,
		gl_renderbuffer_internal_format = 0x8d44,
		gl_stencil_index1 = 0x8d46,
		gl_stencil_index4 = 0x8d47,
		gl_stencil_index8 = 0x8d48,
		gl_stencil_index16 = 0x8d49,
		gl_renderbuffer_red_size = 0x8d50,
		gl_renderbuffer_green_size = 0x8d51,
		gl_renderbuffer_blue_size = 0x8d52,
		gl_renderbuffer_alpha_size = 0x8d53,
		gl_renderbuffer_depth_size = 0x8d54,
		gl_renderbuffer_stencil_size = 0x8d55,
		gl_framebuffer_incomplete_multisample = 0x8d56,
		gl_max_samples = 0x8d57,

		//framebuffer srgb
		gl_framebuffer_srgb = 0x8db9,

		//geometry shader4
		gl_lines_adjacency_arb = 0xa,
		gl_line_strip_adjacency_arb = 0xb,
		gl_triangles_adjacency_arb = 0xc,
		gl_triangle_strip_adjacency_arb = 0xd,
		gl_program_point_size_arb = 0x8642,
		gl_max_geometry_texture_image_units_arb = 0x8c29,
		//gl_framebuffer_attachment_texture_layer = 0x8cd4,
		gl_framebuffer_attachment_layered_arb = 0x8da7,
		gl_framebuffer_incomplete_layer_targets_arb = 0x8da8,
		gl_framebuffer_incomplete_layer_count_arb = 0x8da9,
		gl_geometry_shader_arb = 0x8dd9,
		gl_geometry_vertices_out_arb = 0x8dda,
		gl_geometry_input_type_arb = 0x8ddb,
		gl_geometry_output_type_arb = 0x8ddc,
		gl_max_geometry_varying_components_arb = 0x8ddd,
		gl_max_vertex_varying_components_arb = 0x8dde,
		gl_max_geometry_uniform_components_arb = 0x8ddf,
		gl_max_geometry_output_vertices_arb = 0x8de0,
		gl_max_geometry_total_output_components_arb = 0x8de1,

		//get program binary
		gl_program_binary_retrievable_hint = 0x8257,
		gl_program_binary_length = 0x8741,
		gl_num_program_binary_formats = 0x87fe,
		gl_program_binary_formats = 0x87ff,

		//gl spirv
		gl_shader_binary_format_spir_v_arb = 0x9551,
		gl_spir_v_binary_arb = 0x9552,

		//gpu shader5
		gl_geometry_shader_invocations = 0x887f,
		gl_max_geometry_shader_invocations = 0x8e5a,
		gl_min_fragment_interpolation_offset = 0x8e5b,
		gl_max_fragment_interpolation_offset = 0x8e5c,
		gl_fragment_interpolation_offset_bits = 0x8e5d,
		gl_max_vertex_streams = 0x8e71,

		//gpu shader fp64
		gl_double_mat2 = 0x8f46,
		gl_double_mat3 = 0x8f47,
		gl_double_mat4 = 0x8f48,
		gl_double_mat2x3 = 0x8f49,
		gl_double_mat2x4 = 0x8f4a,
		gl_double_mat3x2 = 0x8f4b,
		gl_double_mat3x4 = 0x8f4c,
		gl_double_mat4x2 = 0x8f4d,
		gl_double_mat4x3 = 0x8f4e,
		gl_double_vec2 = 0x8ffc,
		gl_double_vec3 = 0x8ffd,
		gl_double_vec4 = 0x8ffe,

		//gpu shader int64
		gl_int64_arb = 0x140e,
		//gl_unsigned_int64_arb = 0x140f,
		gl_int64_vec2_arb = 0x8fe9,
		gl_int64_vec3_arb = 0x8fea,
		gl_int64_vec4_arb = 0x8feb,
		gl_unsigned_int64_vec2_arb = 0x8ff5,
		gl_unsigned_int64_vec3_arb = 0x8ff6,
		gl_unsigned_int64_vec4_arb = 0x8ff7,

		//half float pixel
		gl_half_float_arb = 0x140b,

		//half float vertex
		gl_half_float = 0x140b,

		//imaging
		gl_constant_color = 0x8001,
		gl_one_minus_constant_color = 0x8002,
		gl_constant_alpha = 0x8003,
		gl_one_minus_constant_alpha = 0x8004,
		gl_blend_color = 0x8005,
		gl_func_add = 0x8006,
		gl_min = 0x8007,
		gl_max = 0x8008,
		gl_blend_equation = 0x8009,
		gl_func_subtract = 0x800a,
		gl_func_reverse_subtract = 0x800b,
		gl_convolution_1d = 0x8010,
		gl_convolution_2d = 0x8011,
		gl_separable_2d = 0x8012,
		gl_convolution_border_mode = 0x8013,
		gl_convolution_filter_scale = 0x8014,
		gl_convolution_filter_bias = 0x8015,
		gl_reduce = 0x8016,
		gl_convolution_format = 0x8017,
		gl_convolution_width = 0x8018,
		gl_convolution_height = 0x8019,
		gl_max_convolution_width = 0x801a,
		gl_max_convolution_height = 0x801b,
		gl_post_convolution_red_scale = 0x801c,
		gl_post_convolution_green_scale = 0x801d,
		gl_post_convolution_blue_scale = 0x801e,
		gl_post_convolution_alpha_scale = 0x801f,
		gl_post_convolution_red_bias = 0x8020,
		gl_post_convolution_green_bias = 0x8021,
		gl_post_convolution_blue_bias = 0x8022,
		gl_post_convolution_alpha_bias = 0x8023,
		gl_histogram = 0x8024,
		gl_proxy_histogram = 0x8025,
		gl_histogram_width = 0x8026,
		gl_histogram_format = 0x8027,
		gl_histogram_red_size = 0x8028,
		gl_histogram_green_size = 0x8029,
		gl_histogram_blue_size = 0x802a,
		gl_histogram_alpha_size = 0x802b,
		gl_histogram_luminance_size = 0x802c,
		gl_histogram_sink = 0x802d,
		gl_minmax = 0x802e,
		gl_minmax_format = 0x802f,
		gl_minmax_sink = 0x8030,
		gl_table_too_large = 0x8031,
		gl_color_matrix = 0x80b1,
		gl_color_matrix_stack_depth = 0x80b2,
		gl_max_color_matrix_stack_depth = 0x80b3,
		gl_post_color_matrix_red_scale = 0x80b4,
		gl_post_color_matrix_green_scale = 0x80b5,
		gl_post_color_matrix_blue_scale = 0x80b6,
		gl_post_color_matrix_alpha_scale = 0x80b7,
		gl_post_color_matrix_red_bias = 0x80b8,
		gl_post_color_matrix_green_bias = 0x80b9,
		gl_post_color_matrix_blue_bias = 0x80ba,
		gl_post_color_matrix_alpha_bias = 0x80bb,
		gl_color_table = 0x80d0,
		gl_post_convolution_color_table = 0x80d1,
		gl_post_color_matrix_color_table = 0x80d2,
		gl_proxy_color_table = 0x80d3,
		gl_proxy_post_convolution_color_table = 0x80d4,
		gl_proxy_post_color_matrix_color_table = 0x80d5,
		gl_color_table_scale = 0x80d6,
		gl_color_table_bias = 0x80d7,
		gl_color_table_format = 0x80d8,
		gl_color_table_width = 0x80d9,
		gl_color_table_red_size = 0x80da,
		gl_color_table_green_size = 0x80db,
		gl_color_table_blue_size = 0x80dc,
		gl_color_table_alpha_size = 0x80dd,
		gl_color_table_luminance_size = 0x80de,
		gl_color_table_intensity_size = 0x80df,
		gl_ignore_border = 0x8150,
		gl_constant_border = 0x8151,
		gl_wrap_border = 0x8152,
		gl_replicate_border = 0x8153,
		gl_convolution_border_color = 0x8154,

		//indirect parameters
		gl_parameter_buffer_arb = 0x80ee,
		gl_parameter_buffer_binding_arb = 0x80ef,

		//instanced arrays
		gl_vertex_attrib_array_divisor_arb = 0x88fe,

		//internalformat query
		gl_num_sample_counts = 0x9380,

		//internalformat query2
		gl_internalformat_supported = 0x826f,
		gl_internalformat_preferred = 0x8270,
		gl_internalformat_red_size = 0x8271,
		gl_internalformat_green_size = 0x8272,
		gl_internalformat_blue_size = 0x8273,
		gl_internalformat_alpha_size = 0x8274,
		gl_internalformat_depth_size = 0x8275,
		gl_internalformat_stencil_size = 0x8276,
		gl_internalformat_shared_size = 0x8277,
		gl_internalformat_red_type = 0x8278,
		gl_internalformat_green_type = 0x8279,
		gl_internalformat_blue_type = 0x827a,
		gl_internalformat_alpha_type = 0x827b,
		gl_internalformat_depth_type = 0x827c,
		gl_internalformat_stencil_type = 0x827d,
		gl_max_width = 0x827e,
		gl_max_height = 0x827f,
		gl_max_depth = 0x8280,
		gl_max_layers = 0x8281,
		gl_max_combined_dimensions = 0x8282,
		gl_color_components = 0x8283,
		gl_depth_components = 0x8284,
		gl_stencil_components = 0x8285,
		gl_color_renderable = 0x8286,
		gl_depth_renderable = 0x8287,
		gl_stencil_renderable = 0x8288,
		gl_framebuffer_renderable = 0x8289,
		gl_framebuffer_renderable_layered = 0x828a,
		gl_framebuffer_blend = 0x828b,
		gl_read_pixels = 0x828c,
		gl_read_pixels_format = 0x828d,
		gl_read_pixels_type = 0x828e,
		gl_texture_image_format = 0x828f,
		gl_texture_image_type = 0x8290,
		gl_get_texture_image_format = 0x8291,
		gl_get_texture_image_type = 0x8292,
		gl_mipmap = 0x8293,
		gl_manual_generate_mipmap = 0x8294,
		gl_auto_generate_mipmap = 0x8295,
		gl_color_encoding = 0x8296,
		gl_srgb_read = 0x8297,
		gl_srgb_write = 0x8298,
		gl_srgb_decode_arb = 0x8299,
		gl_filter = 0x829a,
		gl_vertex_texture = 0x829b,
		gl_tess_control_texture = 0x829c,
		gl_tess_evaluation_texture = 0x829d,
		gl_geometry_texture = 0x829e,
		gl_fragment_texture = 0x829f,
		gl_compute_texture = 0x82a0,
		gl_texture_shadow = 0x82a1,
		gl_texture_gather = 0x82a2,
		gl_texture_gather_shadow = 0x82a3,
		gl_shader_image_load = 0x82a4,
		gl_shader_image_store = 0x82a5,
		gl_shader_image_atomic = 0x82a6,
		gl_image_texel_size = 0x82a7,
		gl_image_compatibility_class = 0x82a8,
		gl_image_pixel_format = 0x82a9,
		gl_image_pixel_type = 0x82aa,
		gl_simultaneous_texture_and_depth_test = 0x82ac,
		gl_simultaneous_texture_and_stencil_test = 0x82ad,
		gl_simultaneous_texture_and_depth_write = 0x82ae,
		gl_simultaneous_texture_and_stencil_write = 0x82af,
		gl_texture_compressed_block_width = 0x82b1,
		gl_texture_compressed_block_height = 0x82b2,
		gl_texture_compressed_block_size = 0x82b3,
		gl_clear_buffer = 0x82b4,
		gl_texture_view = 0x82b5,
		gl_view_compatibility_class = 0x82b6,
		gl_full_support = 0x82b7,
		gl_caveat_support = 0x82b8,
		gl_image_class_4_x_32 = 0x82b9,
		gl_image_class_2_x_32 = 0x82ba,
		gl_image_class_1_x_32 = 0x82bb,
		gl_image_class_4_x_16 = 0x82bc,
		gl_image_class_2_x_16 = 0x82bd,
		gl_image_class_1_x_16 = 0x82be,
		gl_image_class_4_x_8 = 0x82bf,
		gl_image_class_2_x_8 = 0x82c0,
		gl_image_class_1_x_8 = 0x82c1,
		gl_image_class_11_11_10 = 0x82c2,
		gl_image_class_10_10_10_2 = 0x82c3,
		gl_view_class_128_bits = 0x82c4,
		gl_view_class_96_bits = 0x82c5,
		gl_view_class_64_bits = 0x82c6,
		gl_view_class_48_bits = 0x82c7,
		gl_view_class_32_bits = 0x82c8,
		gl_view_class_24_bits = 0x82c9,
		gl_view_class_16_bits = 0x82ca,
		gl_view_class_8_bits = 0x82cb,
		gl_view_class_s3tc_dxt1_rgb = 0x82cc,
		gl_view_class_s3tc_dxt1_rgba = 0x82cd,
		gl_view_class_s3tc_dxt3_rgba = 0x82ce,
		gl_view_class_s3tc_dxt5_rgba = 0x82cf,
		gl_view_class_rgtc1_red = 0x82d0,
		gl_view_class_rgtc2_rg = 0x82d1,
		gl_view_class_bptc_unorm = 0x82d2,
		gl_view_class_bptc_float = 0x82d3,

		//map buffer alignment
		gl_min_map_buffer_alignment = 0x90bc,

		//map buffer range
		//gl_map_read_bit = 0x0001,
		//gl_map_write_bit = 0x0002,
		gl_map_invalidate_range_bit = 0x0004,
		gl_map_invalidate_buffer_bit = 0x0008,
		gl_map_flush_explicit_bit = 0x0010,
		gl_map_unsynchronized_bit = 0x0020,

		//matrix palette
		gl_matrix_palette_arb = 0x8840,
		gl_max_matrix_palette_stack_depth_arb = 0x8841,
		gl_max_palette_matrices_arb = 0x8842,
		gl_current_palette_matrix_arb = 0x8843,
		gl_matrix_index_array_arb = 0x8844,
		gl_current_matrix_index_arb = 0x8845,
		gl_matrix_index_array_size_arb = 0x8846,
		gl_matrix_index_array_type_arb = 0x8847,
		gl_matrix_index_array_stride_arb = 0x8848,
		gl_matrix_index_array_pointer_arb = 0x8849,

		//multisample
		gl_multisample_arb = 0x809d,
		gl_sample_alpha_to_coverage_arb = 0x809e,
		gl_sample_alpha_to_one_arb = 0x809f,
		gl_sample_coverage_arb = 0x80a0,
		gl_sample_buffers_arb = 0x80a8,
		gl_samples_arb = 0x80a9,
		gl_sample_coverage_value_arb = 0x80aa,
		gl_sample_coverage_invert_arb = 0x80ab,
		gl_multisample_bit_arb = 0x20000000,

		//multitexture
		gl_texture0_arb = 0x84c0,
		gl_texture1_arb = 0x84c1,
		gl_texture2_arb = 0x84c2,
		gl_texture3_arb = 0x84c3,
		gl_texture4_arb = 0x84c4,
		gl_texture5_arb = 0x84c5,
		gl_texture6_arb = 0x84c6,
		gl_texture7_arb = 0x84c7,
		gl_texture8_arb = 0x84c8,
		gl_texture9_arb = 0x84c9,
		gl_texture10_arb = 0x84ca,
		gl_texture11_arb = 0x84cb,
		gl_texture12_arb = 0x84cc,
		gl_texture13_arb = 0x84cd,
		gl_texture14_arb = 0x84ce,
		gl_texture15_arb = 0x84cf,
		gl_texture16_arb = 0x84d0,
		gl_texture17_arb = 0x84d1,
		gl_texture18_arb = 0x84d2,
		gl_texture19_arb = 0x84d3,
		gl_texture20_arb = 0x84d4,
		gl_texture21_arb = 0x84d5,
		gl_texture22_arb = 0x84d6,
		gl_texture23_arb = 0x84d7,
		gl_texture24_arb = 0x84d8,
		gl_texture25_arb = 0x84d9,
		gl_texture26_arb = 0x84da,
		gl_texture27_arb = 0x84db,
		gl_texture28_arb = 0x84dc,
		gl_texture29_arb = 0x84dd,
		gl_texture30_arb = 0x84de,
		gl_texture31_arb = 0x84df,
		gl_active_texture_arb = 0x84e0,
		gl_client_active_texture_arb = 0x84e1,
		gl_max_texture_units_arb = 0x84e2,

		//occlusion query
		gl_query_counter_bits_arb = 0x8864,
		gl_current_query_arb = 0x8865,
		gl_query_result_arb = 0x8866,
		gl_query_result_available_arb = 0x8867,
		gl_samples_passed_arb = 0x8914,

		//occlusion query2
		gl_any_samples_passed = 0x8c2f,

		//parallel shader compile
		gl_max_shader_compiler_threads_arb = 0x91b0,
		gl_completion_status_arb = 0x91b1,

		//pipeline statistics query
		gl_vertices_submitted_arb = 0x82ee,
		gl_primitives_submitted_arb = 0x82ef,
		gl_vertex_shader_invocations_arb = 0x82f0,
		gl_tess_control_shader_patches_arb = 0x82f1,
		gl_tess_evaluation_shader_invocations_arb = 0x82f2,
		gl_geometry_shader_primitives_emitted_arb = 0x82f3,
		gl_fragment_shader_invocations_arb = 0x82f4,
		gl_compute_shader_invocations_arb = 0x82f5,
		gl_clipping_input_primitives_arb = 0x82f6,
		gl_clipping_output_primitives_arb = 0x82f7,
		//gl_geometry_shader_invocations = 0x887f,

		//pixel buffer object
		gl_pixel_pack_buffer_arb = 0x88eb,
		gl_pixel_unpack_buffer_arb = 0x88ec,
		gl_pixel_pack_buffer_binding_arb = 0x88ed,
		gl_pixel_unpack_buffer_binding_arb = 0x88ef,

		//point parameters
		gl_point_size_min_arb = 0x8126,
		gl_point_size_max_arb = 0x8127,
		gl_point_fade_threshold_size_arb = 0x8128,
		gl_point_distance_attenuation_arb = 0x8129,

		//point sprite
		gl_point_sprite_arb = 0x8861,
		gl_coord_replace_arb = 0x8862,

		//polygon offset clamp
		//gl_polygon_offset_clamp = 0x8e1b,

		//program interface query
		gl_uniform = 0x92e1,
		gl_uniform_block = 0x92e2,
		gl_program_input = 0x92e3,
		gl_program_output = 0x92e4,
		gl_buffer_variable = 0x92e5,
		gl_shader_storage_block = 0x92e6,
		gl_is_per_patch = 0x92e7,
		gl_vertex_subroutine = 0x92e8,
		gl_tess_control_subroutine = 0x92e9,
		gl_tess_evaluation_subroutine = 0x92ea,
		gl_geometry_subroutine = 0x92eb,
		gl_fragment_subroutine = 0x92ec,
		gl_compute_subroutine = 0x92ed,
		gl_vertex_subroutine_uniform = 0x92ee,
		gl_tess_control_subroutine_uniform = 0x92ef,
		gl_tess_evaluation_subroutine_uniform = 0x92f0,
		gl_geometry_subroutine_uniform = 0x92f1,
		gl_fragment_subroutine_uniform = 0x92f2,
		gl_compute_subroutine_uniform = 0x92f3,
		gl_transform_feedback_varying = 0x92f4,
		gl_active_resources = 0x92f5,
		gl_max_name_length = 0x92f6,
		gl_max_num_active_variables = 0x92f7,
		gl_max_num_compatible_subroutines = 0x92f8,
		gl_name_length = 0x92f9,
		gl_type = 0x92fa,
		gl_array_size = 0x92fb,
		gl_offset = 0x92fc,
		gl_block_index = 0x92fd,
		gl_array_stride = 0x92fe,
		gl_matrix_stride = 0x92ff,
		gl_is_row_major = 0x9300,
		gl_atomic_counter_buffer_index = 0x9301,
		gl_buffer_binding = 0x9302,
		gl_buffer_data_size = 0x9303,
		gl_num_active_variables = 0x9304,
		gl_active_variables = 0x9305,
		gl_referenced_by_vertex_shader = 0x9306,
		gl_referenced_by_tess_control_shader = 0x9307,
		gl_referenced_by_tess_evaluation_shader = 0x9308,
		gl_referenced_by_geometry_shader = 0x9309,
		gl_referenced_by_fragment_shader = 0x930a,
		gl_referenced_by_compute_shader = 0x930b,
		gl_top_level_array_size = 0x930c,
		gl_top_level_array_stride = 0x930d,
		gl_location = 0x930e,
		gl_location_index = 0x930f,

		//provoking vertex
		gl_quads_follow_provoking_vertex_convention = 0x8e4c,
		gl_first_vertex_convention = 0x8e4d,
		gl_last_vertex_convention = 0x8e4e,
		gl_provoking_vertex = 0x8e4f,

		//query buffer object
		gl_query_buffer_barrier_bit = 0x00008000,
		gl_query_buffer = 0x9192,
		gl_query_buffer_binding = 0x9193,
		gl_query_result_no_wait = 0x9194,

		//robustness
		gl_context_flag_robust_access_bit_arb = 0x00000004,
		gl_lose_context_on_reset_arb = 0x8252,
		gl_guilty_context_reset_arb = 0x8253,
		gl_innocent_context_reset_arb = 0x8254,
		gl_unknown_context_reset_arb = 0x8255,
		gl_reset_notification_strategy_arb = 0x8256,
		gl_no_reset_notification_arb = 0x8261,

		//sample locations
		gl_sample_location_arb = 0x8e50,
		gl_sample_location_subpixel_bits_arb = 0x933d,
		gl_sample_location_pixel_grid_width_arb = 0x933e,
		gl_sample_location_pixel_grid_height_arb = 0x933f,
		gl_programmable_sample_location_table_size_arb = 0x9340,
		gl_programmable_sample_location_arb = 0x9341,
		gl_framebuffer_programmable_sample_locations_arb = 0x9342,
		gl_framebuffer_sample_location_pixel_grid_arb = 0x9343,

		//sample shading
		gl_sample_shading_arb = 0x8c36,
		gl_min_sample_shading_value_arb = 0x8c37,

		//sampler objects
		gl_sampler_binding = 0x8919,

		//seamless cube map
		//gl_texture_cube_map_seamless = 0x884f,

		//seamless cubemap per texture
		//gl_texture_cube_map_seamless = 0x884f,

		//separate shader objects
		gl_vertex_shader_bit = 0x00000001,
		gl_fragment_shader_bit = 0x00000002,
		gl_geometry_shader_bit = 0x00000004,
		gl_tess_control_shader_bit = 0x00000008,
		gl_tess_evaluation_shader_bit = 0x00000010,
		gl_program_separable = 0x8258,
		gl_active_program = 0x8259,
		gl_program_pipeline_binding = 0x825a,
		gl_all_shader_bits = 0xffffffff,

		//shader atomic counters
		gl_atomic_counter_buffer = 0x92c0,
		gl_atomic_counter_buffer_binding = 0x92c1,
		gl_atomic_counter_buffer_start = 0x92c2,
		gl_atomic_counter_buffer_size = 0x92c3,
		gl_atomic_counter_buffer_data_size = 0x92c4,
		gl_atomic_counter_buffer_active_atomic_counters = 0x92c5,
		gl_atomic_counter_buffer_active_atomic_counter_indices = 0x92c6,
		gl_atomic_counter_buffer_referenced_by_vertex_shader = 0x92c7,
		gl_atomic_counter_buffer_referenced_by_tess_control_shader = 0x92c8,
		gl_atomic_counter_buffer_referenced_by_tess_evaluation_shader = 0x92c9,
		gl_atomic_counter_buffer_referenced_by_geometry_shader = 0x92ca,
		gl_atomic_counter_buffer_referenced_by_fragment_shader = 0x92cb,
		gl_max_vertex_atomic_counter_buffers = 0x92cc,
		gl_max_tess_control_atomic_counter_buffers = 0x92cd,
		gl_max_tess_evaluation_atomic_counter_buffers = 0x92ce,
		gl_max_geometry_atomic_counter_buffers = 0x92cf,
		gl_max_fragment_atomic_counter_buffers = 0x92d0,
		gl_max_combined_atomic_counter_buffers = 0x92d1,
		gl_max_vertex_atomic_counters = 0x92d2,
		gl_max_tess_control_atomic_counters = 0x92d3,
		gl_max_tess_evaluation_atomic_counters = 0x92d4,
		gl_max_geometry_atomic_counters = 0x92d5,
		gl_max_fragment_atomic_counters = 0x92d6,
		gl_max_combined_atomic_counters = 0x92d7,
		gl_max_atomic_counter_buffer_size = 0x92d8,
		gl_active_atomic_counter_buffers = 0x92d9,
		gl_uniform_atomic_counter_buffer_index = 0x92da,
		gl_unsigned_int_atomic_counter = 0x92db,
		gl_max_atomic_counter_buffer_bindings = 0x92dc,

		//shader image load store
		gl_vertex_attrib_array_barrier_bit = 0x00000001,
		gl_element_array_barrier_bit = 0x00000002,
		gl_uniform_barrier_bit = 0x00000004,
		gl_texture_fetch_barrier_bit = 0x00000008,
		gl_shader_image_access_barrier_bit = 0x00000020,
		gl_command_barrier_bit = 0x00000040,
		gl_pixel_buffer_barrier_bit = 0x00000080,
		gl_texture_update_barrier_bit = 0x00000100,
		gl_buffer_update_barrier_bit = 0x00000200,
		gl_framebuffer_barrier_bit = 0x00000400,
		gl_transform_feedback_barrier_bit = 0x00000800,
		gl_atomic_counter_barrier_bit = 0x00001000,
		gl_max_image_units = 0x8f38,
		gl_max_combined_image_units_and_fragment_outputs = 0x8f39,
		gl_image_binding_name = 0x8f3a,
		gl_image_binding_level = 0x8f3b,
		gl_image_binding_layered = 0x8f3c,
		gl_image_binding_layer = 0x8f3d,
		gl_image_binding_access = 0x8f3e,
		gl_image_1d = 0x904c,
		gl_image_2d = 0x904d,
		gl_image_3d = 0x904e,
		gl_image_2d_rect = 0x904f,
		gl_image_cube = 0x9050,
		gl_image_buffer = 0x9051,
		gl_image_1d_array = 0x9052,
		gl_image_2d_array = 0x9053,
		gl_image_cube_map_array = 0x9054,
		gl_image_2d_multisample = 0x9055,
		gl_image_2d_multisample_array = 0x9056,
		gl_int_image_1d = 0x9057,
		gl_int_image_2d = 0x9058,
		gl_int_image_3d = 0x9059,
		gl_int_image_2d_rect = 0x905a,
		gl_int_image_cube = 0x905b,
		gl_int_image_buffer = 0x905c,
		gl_int_image_1d_array = 0x905d,
		gl_int_image_2d_array = 0x905e,
		gl_int_image_cube_map_array = 0x905f,
		gl_int_image_2d_multisample = 0x9060,
		gl_int_image_2d_multisample_array = 0x9061,
		gl_unsigned_int_image_1d = 0x9062,
		gl_unsigned_int_image_2d = 0x9063,
		gl_unsigned_int_image_3d = 0x9064,
		gl_unsigned_int_image_2d_rect = 0x9065,
		gl_unsigned_int_image_cube = 0x9066,
		gl_unsigned_int_image_buffer = 0x9067,
		gl_unsigned_int_image_1d_array = 0x9068,
		gl_unsigned_int_image_2d_array = 0x9069,
		gl_unsigned_int_image_cube_map_array = 0x906a,
		gl_unsigned_int_image_2d_multisample = 0x906b,
		gl_unsigned_int_image_2d_multisample_array = 0x906c,
		gl_max_image_samples = 0x906d,
		gl_image_binding_format = 0x906e,
		gl_image_format_compatibility_type = 0x90c7,
		gl_image_format_compatibility_by_size = 0x90c8,
		gl_image_format_compatibility_by_class = 0x90c9,
		gl_max_vertex_image_uniforms = 0x90ca,
		gl_max_tess_control_image_uniforms = 0x90cb,
		gl_max_tess_evaluation_image_uniforms = 0x90cc,
		gl_max_geometry_image_uniforms = 0x90cd,
		gl_max_fragment_image_uniforms = 0x90ce,
		gl_max_combined_image_uniforms = 0x90cf,
		gl_all_barrier_bits = 0xffffffff,

		//shader objects
		gl_program_object_arb = 0x8b40,
		gl_shader_object_arb = 0x8b48,
		gl_object_type_arb = 0x8b4e,
		gl_object_subtype_arb = 0x8b4f,
		gl_float_vec2_arb = 0x8b50,
		gl_float_vec3_arb = 0x8b51,
		gl_float_vec4_arb = 0x8b52,
		gl_int_vec2_arb = 0x8b53,
		gl_int_vec3_arb = 0x8b54,
		gl_int_vec4_arb = 0x8b55,
		gl_bool_arb = 0x8b56,
		gl_bool_vec2_arb = 0x8b57,
		gl_bool_vec3_arb = 0x8b58,
		gl_bool_vec4_arb = 0x8b59,
		gl_float_mat2_arb = 0x8b5a,
		gl_float_mat3_arb = 0x8b5b,
		gl_float_mat4_arb = 0x8b5c,
		gl_sampler_1d_arb = 0x8b5d,
		gl_sampler_2d_arb = 0x8b5e,
		gl_sampler_3d_arb = 0x8b5f,
		gl_sampler_cube_arb = 0x8b60,
		gl_sampler_1d_shadow_arb = 0x8b61,
		gl_sampler_2d_shadow_arb = 0x8b62,
		gl_sampler_2d_rect_arb = 0x8b63,
		gl_sampler_2d_rect_shadow_arb = 0x8b64,
		gl_object_delete_status_arb = 0x8b80,
		gl_object_compile_status_arb = 0x8b81,
		gl_object_link_status_arb = 0x8b82,
		gl_object_validate_status_arb = 0x8b83,
		gl_object_info_log_length_arb = 0x8b84,
		gl_object_attached_objects_arb = 0x8b85,
		gl_object_active_uniforms_arb = 0x8b86,
		gl_object_active_uniform_max_length_arb = 0x8b87,
		gl_object_shader_source_length_arb = 0x8b88,

		//shader storage buffer object
		gl_shader_storage_barrier_bit = 0x2000,
		gl_max_combined_shader_output_resources = 0x8f39,
		gl_shader_storage_buffer = 0x90d2,
		gl_shader_storage_buffer_binding = 0x90d3,
		gl_shader_storage_buffer_start = 0x90d4,
		gl_shader_storage_buffer_size = 0x90d5,
		gl_max_vertex_shader_storage_blocks = 0x90d6,
		gl_max_geometry_shader_storage_blocks = 0x90d7,
		gl_max_tess_control_shader_storage_blocks = 0x90d8,
		gl_max_tess_evaluation_shader_storage_blocks = 0x90d9,
		gl_max_fragment_shader_storage_blocks = 0x90da,
		gl_max_compute_shader_storage_blocks = 0x90db,
		gl_max_combined_shader_storage_blocks = 0x90dc,
		gl_max_shader_storage_buffer_bindings = 0x90dd,
		gl_max_shader_storage_block_size = 0x90de,
		gl_shader_storage_buffer_offset_alignment = 0x90df,

		//shader subroutine
		gl_active_subroutines = 0x8de5,
		gl_active_subroutine_uniforms = 0x8de6,
		gl_max_subroutines = 0x8de7,
		gl_max_subroutine_uniform_locations = 0x8de8,
		gl_active_subroutine_uniform_locations = 0x8e47,
		gl_active_subroutine_max_length = 0x8e48,
		gl_active_subroutine_uniform_max_length = 0x8e49,
		gl_num_compatible_subroutines = 0x8e4a,
		gl_compatible_subroutines = 0x8e4b,

		//shading language 100
		gl_shading_language_version_arb = 0x8b8c,

		//shading language include
		gl_shader_include_arb = 0x8dae,
		gl_named_string_length_arb = 0x8de9,
		gl_named_string_type_arb = 0x8dea,

		//shadow
		gl_texture_compare_mode_arb = 0x884c,
		gl_texture_compare_func_arb = 0x884d,
		gl_compare_r_to_texture_arb = 0x884e,

		//shadow ambient
		gl_texture_compare_fail_value_arb = 0x80bf,

		//sparse buffer
		gl_sparse_storage_bit_arb = 0x0400,
		gl_sparse_buffer_page_size_arb = 0x82f8,

		//sparse texture
		gl_virtual_page_size_x_arb = 0x9195,
		gl_virtual_page_size_y_arb = 0x9196,
		gl_virtual_page_size_z_arb = 0x9197,
		gl_max_sparse_texture_size_arb = 0x9198,
		gl_max_sparse_3d_texture_size_arb = 0x9199,
		gl_max_sparse_array_texture_layers_arb = 0x919a,
		gl_texture_sparse_arb = 0x91a6,
		gl_virtual_page_size_index_arb = 0x91a7,
		gl_num_virtual_page_sizes_arb = 0x91a8,
		gl_sparse_texture_full_array_cube_mipmaps_arb = 0x91a9,
		gl_num_sparse_levels_arb = 0x91aa,

		//spirv extensions
		//gl_spir_v_extensions = 0x9553,
		//gl_num_spir_v_extensions = 0x9554,

		//stencil texturing
		gl_depth_stencil_texture_mode = 0x90ea,

		//sync
		gl_sync_flush_commands_bit = 0x00000001,
		gl_max_server_wait_timeout = 0x9111,
		gl_object_type = 0x9112,
		gl_sync_condition = 0x9113,
		gl_sync_status = 0x9114,
		gl_sync_flags = 0x9115,
		gl_sync_fence = 0x9116,
		gl_sync_gpu_commands_complete = 0x9117,
		gl_unsignaled = 0x9118,
		gl_signaled = 0x9119,
		gl_already_signaled = 0x911a,
		gl_timeout_expired = 0x911b,
		gl_condition_satisfied = 0x911c,
		gl_wait_failed = 0x911d,
		gl_timeout_ignored = 0xffffffffffffffffull,

		//tessellation shader
		gl_patches = 0xe,
		gl_uniform_block_referenced_by_tess_control_shader = 0x84f0,
		gl_uniform_block_referenced_by_tess_evaluation_shader = 0x84f1,
		gl_max_tess_control_input_components = 0x886c,
		gl_max_tess_evaluation_input_components = 0x886d,
		gl_max_combined_tess_control_uniform_components = 0x8e1e,
		gl_max_combined_tess_evaluation_uniform_components = 0x8e1f,
		gl_patch_vertices = 0x8e72,
		gl_patch_default_inner_level = 0x8e73,
		gl_patch_default_outer_level = 0x8e74,
		gl_tess_control_output_vertices = 0x8e75,
		gl_tess_gen_mode = 0x8e76,
		gl_tess_gen_spacing = 0x8e77,
		gl_tess_gen_vertex_order = 0x8e78,
		gl_tess_gen_point_mode = 0x8e79,
		gl_isolines = 0x8e7a,
		gl_fractional_odd = 0x8e7b,
		gl_fractional_even = 0x8e7c,
		gl_max_patch_vertices = 0x8e7d,
		gl_max_tess_gen_level = 0x8e7e,
		gl_max_tess_control_uniform_components = 0x8e7f,
		gl_max_tess_evaluation_uniform_components = 0x8e80,
		gl_max_tess_control_texture_image_units = 0x8e81,
		gl_max_tess_evaluation_texture_image_units = 0x8e82,
		gl_max_tess_control_output_components = 0x8e83,
		gl_max_tess_patch_components = 0x8e84,
		gl_max_tess_control_total_output_components = 0x8e85,
		gl_max_tess_evaluation_output_components = 0x8e86,
		gl_tess_evaluation_shader = 0x8e87,
		gl_tess_control_shader = 0x8e88,
		gl_max_tess_control_uniform_blocks = 0x8e89,
		gl_max_tess_evaluation_uniform_blocks = 0x8e8a,

		//texture border clamp
		gl_clamp_to_border_arb = 0x812d,

		//texture buffer object
		gl_texture_buffer_arb = 0x8c2a,
		gl_max_texture_buffer_size_arb = 0x8c2b,
		gl_texture_binding_buffer_arb = 0x8c2c,
		gl_texture_buffer_data_store_binding_arb = 0x8c2d,
		gl_texture_buffer_format_arb = 0x8c2e,

		//texture buffer range
		gl_texture_buffer_offset = 0x919d,
		gl_texture_buffer_size = 0x919e,
		gl_texture_buffer_offset_alignment = 0x919f,

		//texture compression
		gl_compressed_alpha_arb = 0x84e9,
		gl_compressed_luminance_arb = 0x84ea,
		gl_compressed_luminance_alpha_arb = 0x84eb,
		gl_compressed_intensity_arb = 0x84ec,
		gl_compressed_rgb_arb = 0x84ed,
		gl_compressed_rgba_arb = 0x84ee,
		gl_texture_compression_hint_arb = 0x84ef,
		gl_texture_compressed_image_size_arb = 0x86a0,
		gl_texture_compressed_arb = 0x86a1,
		gl_num_compressed_texture_formats_arb = 0x86a2,
		gl_compressed_texture_formats_arb = 0x86a3,

		//texture compression bptc
		gl_compressed_rgba_bptc_unorm_arb = 0x8e8c,
		gl_compressed_srgb_alpha_bptc_unorm_arb = 0x8e8d,
		gl_compressed_rgb_bptc_signed_float_arb = 0x8e8e,
		gl_compressed_rgb_bptc_unsigned_float_arb = 0x8e8f,

		//texture compression rgtc
		gl_compressed_red_rgtc1 = 0x8dbb,
		gl_compressed_signed_red_rgtc1 = 0x8dbc,
		gl_compressed_rg_rgtc2 = 0x8dbd,
		gl_compressed_signed_rg_rgtc2 = 0x8dbe,

		//texture cube map
		gl_normal_map_arb = 0x8511,
		gl_reflection_map_arb = 0x8512,
		gl_texture_cube_map_arb = 0x8513,
		gl_texture_binding_cube_map_arb = 0x8514,
		gl_texture_cube_map_positive_x_arb = 0x8515,
		gl_texture_cube_map_negative_x_arb = 0x8516,
		gl_texture_cube_map_positive_y_arb = 0x8517,
		gl_texture_cube_map_negative_y_arb = 0x8518,
		gl_texture_cube_map_positive_z_arb = 0x8519,
		gl_texture_cube_map_negative_z_arb = 0x851a,
		gl_proxy_texture_cube_map_arb = 0x851b,
		gl_max_cube_map_texture_size_arb = 0x851c,

		//texture cube map array
		gl_texture_cube_map_array_arb = 0x9009,
		gl_texture_binding_cube_map_array_arb = 0x900a,
		gl_proxy_texture_cube_map_array_arb = 0x900b,
		gl_sampler_cube_map_array_arb = 0x900c,
		gl_sampler_cube_map_array_shadow_arb = 0x900d,
		gl_int_sampler_cube_map_array_arb = 0x900e,
		gl_unsigned_int_sampler_cube_map_array_arb = 0x900f,

		//texture env combine
		gl_subtract_arb = 0x84e7,
		gl_combine_arb = 0x8570,
		gl_combine_rgb_arb = 0x8571,
		gl_combine_alpha_arb = 0x8572,
		gl_rgb_scale_arb = 0x8573,
		gl_add_signed_arb = 0x8574,
		gl_interpolate_arb = 0x8575,
		gl_constant_arb = 0x8576,
		gl_primary_color_arb = 0x8577,
		gl_previous_arb = 0x8578,
		gl_source0_rgb_arb = 0x8580,
		gl_source1_rgb_arb = 0x8581,
		gl_source2_rgb_arb = 0x8582,
		gl_source0_alpha_arb = 0x8588,
		gl_source1_alpha_arb = 0x8589,
		gl_source2_alpha_arb = 0x858a,
		gl_operand0_rgb_arb = 0x8590,
		gl_operand1_rgb_arb = 0x8591,
		gl_operand2_rgb_arb = 0x8592,
		gl_operand0_alpha_arb = 0x8598,
		gl_operand1_alpha_arb = 0x8599,
		gl_operand2_alpha_arb = 0x859a,

		//texture env dot3
		gl_dot3_rgb_arb = 0x86ae,
		gl_dot3_rgba_arb = 0x86af,

		//texture filter anisotropic
		//gl_texture_max_anisotropy = 0x84fe,
		//gl_max_texture_max_anisotropy = 0x84ff,

		//texture filter minmax
		gl_texture_reduction_mode_arb = 0x9366,
		gl_weighted_average_arb = 0x9367,

		//texture float
		gl_rgba32f_arb = 0x8814,
		gl_rgb32f_arb = 0x8815,
		gl_alpha32f_arb = 0x8816,
		gl_intensity32f_arb = 0x8817,
		gl_luminance32f_arb = 0x8818,
		gl_luminance_alpha32f_arb = 0x8819,
		gl_rgba16f_arb = 0x881a,
		gl_rgb16f_arb = 0x881b,
		gl_alpha16f_arb = 0x881c,
		gl_intensity16f_arb = 0x881d,
		gl_luminance16f_arb = 0x881e,
		gl_luminance_alpha16f_arb = 0x881f,
		gl_texture_red_type_arb = 0x8c10,
		gl_texture_green_type_arb = 0x8c11,
		gl_texture_blue_type_arb = 0x8c12,
		gl_texture_alpha_type_arb = 0x8c13,
		gl_texture_luminance_type_arb = 0x8c14,
		gl_texture_intensity_type_arb = 0x8c15,
		gl_texture_depth_type_arb = 0x8c16,
		gl_unsigned_normalized_arb = 0x8c17,

		//texture gather
		gl_min_program_texture_gather_offset_arb = 0x8e5e,
		gl_max_program_texture_gather_offset_arb = 0x8e5f,
		gl_max_program_texture_gather_components_arb = 0x8f9f,

		//texture mirror clamp to edge
		gl_mirror_clamp_to_edge = 0x8743,

		//texture mirrored repeat
		gl_mirrored_repeat_arb = 0x8370,

		//texture multisample
		gl_sample_position = 0x8e50,
		gl_sample_mask = 0x8e51,
		gl_sample_mask_value = 0x8e52,
		gl_max_sample_mask_words = 0x8e59,
		gl_texture_2d_multisample = 0x9100,
		gl_proxy_texture_2d_multisample = 0x9101,
		gl_texture_2d_multisample_array = 0x9102,
		gl_proxy_texture_2d_multisample_array = 0x9103,
		gl_texture_binding_2d_multisample = 0x9104,
		gl_texture_binding_2d_multisample_array = 0x9105,
		gl_texture_samples = 0x9106,
		gl_texture_fixed_sample_locations = 0x9107,
		gl_sampler_2d_multisample = 0x9108,
		gl_int_sampler_2d_multisample = 0x9109,
		gl_unsigned_int_sampler_2d_multisample = 0x910a,
		gl_sampler_2d_multisample_array = 0x910b,
		gl_int_sampler_2d_multisample_array = 0x910c,
		gl_unsigned_int_sampler_2d_multisample_array = 0x910d,
		gl_max_color_texture_samples = 0x910e,
		gl_max_depth_texture_samples = 0x910f,
		gl_max_integer_samples = 0x9110,

		//texture rectangle
		gl_texture_rectangle_arb = 0x84f5,
		gl_texture_binding_rectangle_arb = 0x84f6,
		gl_proxy_texture_rectangle_arb = 0x84f7,
		gl_max_rectangle_texture_size_arb = 0x84f8,
		//gl_sampler_2d_rect_arb = 0x8b63,
		//gl_sampler_2d_rect_shadow_arb = 0x8b64,

		//texture rg
		gl_compressed_red = 0x8225,
		gl_compressed_rg = 0x8226,
		gl_rg = 0x8227,
		gl_rg_integer = 0x8228,
		gl_r8 = 0x8229,
		gl_r16 = 0x822a,
		gl_rg8 = 0x822b,
		gl_rg16 = 0x822c,
		gl_r16f = 0x822d,
		gl_r32f = 0x822e,
		gl_rg16f = 0x822f,
		gl_rg32f = 0x8230,
		gl_r8i = 0x8231,
		gl_r8ui = 0x8232,
		gl_r16i = 0x8233,
		gl_r16ui = 0x8234,
		gl_r32i = 0x8235,
		gl_r32ui = 0x8236,
		gl_rg8i = 0x8237,
		gl_rg8ui = 0x8238,
		gl_rg16i = 0x8239,
		gl_rg16ui = 0x823a,
		gl_rg32i = 0x823b,
		gl_rg32ui = 0x823c,

		//texturergb10 a2ui
		//gl_rgb10_a2ui = 0x906f,

		//texture stencil8
		gl_stencil_index = 0x1901,
		//gl_stencil_index8 = 0x8d48,

		//texture storage
		gl_texture_immutable_format = 0x912f,

		//texture swizzle
		gl_texture_swizzle_r = 0x8e42,
		gl_texture_swizzle_g = 0x8e43,
		gl_texture_swizzle_b = 0x8e44,
		gl_texture_swizzle_a = 0x8e45,
		gl_texture_swizzle_rgba = 0x8e46,

		//texture view
		gl_texture_view_min_level = 0x82db,
		gl_texture_view_num_levels = 0x82dc,
		gl_texture_view_min_layer = 0x82dd,
		gl_texture_view_num_layers = 0x82de,
		//gl_texture_immutable_levels = 0x82df,

		//timer query
		gl_time_elapsed = 0x88bf,
		gl_timestamp = 0x8e28,

		//transform feedback2
		gl_transform_feedback = 0x8e22,
		gl_transform_feedback_buffer_paused = 0x8e23,
		gl_transform_feedback_buffer_active = 0x8e24,
		gl_transform_feedback_binding = 0x8e25,

		//transform feedback3
		gl_max_transform_feedback_buffers = 0x8e70,
		//gl_max_vertex_streams = 0x8e71,

		//transform feedback overflow query
		gl_transform_feedback_overflow_arb = 0x82ec,
		gl_transform_feedback_stream_overflow_arb = 0x82ed,

		//transpose matrix
		gl_transpose_modelview_matrix_arb = 0x84e3,
		gl_transpose_projection_matrix_arb = 0x84e4,
		gl_transpose_texture_matrix_arb = 0x84e5,
		gl_transpose_color_matrix_arb = 0x84e6,

		//uniform buffer object
		gl_uniform_buffer = 0x8a11,
		gl_uniform_buffer_binding = 0x8a28,
		gl_uniform_buffer_start = 0x8a29,
		gl_uniform_buffer_size = 0x8a2a,
		gl_max_vertex_uniform_blocks = 0x8a2b,
		gl_max_geometry_uniform_blocks = 0x8a2c,
		gl_max_fragment_uniform_blocks = 0x8a2d,
		gl_max_combined_uniform_blocks = 0x8a2e,
		gl_max_uniform_buffer_bindings = 0x8a2f,
		gl_max_uniform_block_size = 0x8a30,
		gl_max_combined_vertex_uniform_components = 0x8a31,
		gl_max_combined_geometry_uniform_components = 0x8a32,
		gl_max_combined_fragment_uniform_components = 0x8a33,
		gl_uniform_buffer_offset_alignment = 0x8a34,
		gl_active_uniform_block_max_name_length = 0x8a35,
		gl_active_uniform_blocks = 0x8a36,
		gl_uniform_type = 0x8a37,
		gl_uniform_size = 0x8a38,
		gl_uniform_name_length = 0x8a39,
		gl_uniform_block_index = 0x8a3a,
		gl_uniform_offset = 0x8a3b,
		gl_uniform_array_stride = 0x8a3c,
		gl_uniform_matrix_stride = 0x8a3d,
		gl_uniform_is_row_major = 0x8a3e,
		gl_uniform_block_binding = 0x8a3f,
		gl_uniform_block_data_size = 0x8a40,
		gl_uniform_block_name_length = 0x8a41,
		gl_uniform_block_active_uniforms = 0x8a42,
		gl_uniform_block_active_uniform_indices = 0x8a43,
		gl_uniform_block_referenced_by_vertex_shader = 0x8a44,
		gl_uniform_block_referenced_by_geometry_shader = 0x8a45,
		gl_uniform_block_referenced_by_fragment_shader = 0x8a46,
		gl_invalid_index = 0xffffffffu,

		//vertex array bgra
		//gl_bgra = 0x80e1,

		//vertex array object
		gl_vertex_array_binding = 0x85b5,

		//vertex attrib binding
		gl_vertex_attrib_binding = 0x82d4,
		gl_vertex_attrib_relative_offset = 0x82d5,
		gl_vertex_binding_divisor = 0x82d6,
		gl_vertex_binding_offset = 0x82d7,
		gl_vertex_binding_stride = 0x82d8,
		gl_max_vertex_attrib_relative_offset = 0x82d9,
		gl_max_vertex_attrib_bindings = 0x82da,
		gl_vertex_binding_buffer = 0x8f4f,

		//vertex blend
		gl_modelview0_arb = 0x1700,
		gl_modelview1_arb = 0x850a,
		gl_max_vertex_units_arb = 0x86a4,
		gl_active_vertex_units_arb = 0x86a5,
		gl_weight_sum_unity_arb = 0x86a6,
		gl_vertex_blend_arb = 0x86a7,
		gl_current_weight_arb = 0x86a8,
		gl_weight_array_type_arb = 0x86a9,
		gl_weight_array_stride_arb = 0x86aa,
		gl_weight_array_size_arb = 0x86ab,
		gl_weight_array_pointer_arb = 0x86ac,
		gl_weight_array_arb = 0x86ad,
		gl_modelview2_arb = 0x8722,
		gl_modelview3_arb = 0x8723,
		gl_modelview4_arb = 0x8724,
		gl_modelview5_arb = 0x8725,
		gl_modelview6_arb = 0x8726,
		gl_modelview7_arb = 0x8727,
		gl_modelview8_arb = 0x8728,
		gl_modelview9_arb = 0x8729,
		gl_modelview10_arb = 0x872a,
		gl_modelview11_arb = 0x872b,
		gl_modelview12_arb = 0x872c,
		gl_modelview13_arb = 0x872d,
		gl_modelview14_arb = 0x872e,
		gl_modelview15_arb = 0x872f,
		gl_modelview16_arb = 0x8730,
		gl_modelview17_arb = 0x8731,
		gl_modelview18_arb = 0x8732,
		gl_modelview19_arb = 0x8733,
		gl_modelview20_arb = 0x8734,
		gl_modelview21_arb = 0x8735,
		gl_modelview22_arb = 0x8736,
		gl_modelview23_arb = 0x8737,
		gl_modelview24_arb = 0x8738,
		gl_modelview25_arb = 0x8739,
		gl_modelview26_arb = 0x873a,
		gl_modelview27_arb = 0x873b,
		gl_modelview28_arb = 0x873c,
		gl_modelview29_arb = 0x873d,
		gl_modelview30_arb = 0x873e,
		gl_modelview31_arb = 0x873f,

		//vertex buffer object
		gl_buffer_size_arb = 0x8764,
		gl_buffer_usage_arb = 0x8765,
		gl_array_buffer_arb = 0x8892,
		gl_element_array_buffer_arb = 0x8893,
		gl_array_buffer_binding_arb = 0x8894,
		gl_element_array_buffer_binding_arb = 0x8895,
		gl_vertex_array_buffer_binding_arb = 0x8896,
		gl_normal_array_buffer_binding_arb = 0x8897,
		gl_color_array_buffer_binding_arb = 0x8898,
		gl_index_array_buffer_binding_arb = 0x8899,
		gl_texture_coord_array_buffer_binding_arb = 0x889a,
		gl_edge_flag_array_buffer_binding_arb = 0x889b,
		gl_secondary_color_array_buffer_binding_arb = 0x889c,
		gl_fog_coordinate_array_buffer_binding_arb = 0x889d,
		gl_weight_array_buffer_binding_arb = 0x889e,
		gl_vertex_attrib_array_buffer_binding_arb = 0x889f,
		gl_read_only_arb = 0x88b8,
		gl_write_only_arb = 0x88b9,
		gl_read_write_arb = 0x88ba,
		gl_buffer_access_arb = 0x88bb,
		gl_buffer_mapped_arb = 0x88bc,
		gl_buffer_map_pointer_arb = 0x88bd,
		gl_stream_draw_arb = 0x88e0,
		gl_stream_read_arb = 0x88e1,
		gl_stream_copy_arb = 0x88e2,
		gl_static_draw_arb = 0x88e4,
		gl_static_read_arb = 0x88e5,
		gl_static_copy_arb = 0x88e6,
		gl_dynamic_draw_arb = 0x88e8,
		gl_dynamic_read_arb = 0x88e9,
		gl_dynamic_copy_arb = 0x88ea,

		//vertex program
		gl_color_sum_arb = 0x8458,
		gl_vertex_program_arb = 0x8620,
		gl_vertex_attrib_array_enabled_arb = 0x8622,
		gl_vertex_attrib_array_size_arb = 0x8623,
		gl_vertex_attrib_array_stride_arb = 0x8624,
		gl_vertex_attrib_array_type_arb = 0x8625,
		gl_current_vertex_attrib_arb = 0x8626,
		gl_program_length_arb = 0x8627,
		gl_program_string_arb = 0x8628,
		gl_max_program_matrix_stack_depth_arb = 0x862e,
		gl_max_program_matrices_arb = 0x862f,
		gl_current_matrix_stack_depth_arb = 0x8640,
		gl_current_matrix_arb = 0x8641,
		gl_vertex_program_point_size_arb = 0x8642,
		gl_vertex_program_two_side_arb = 0x8643,
		gl_vertex_attrib_array_pointer_arb = 0x8645,
		gl_program_error_position_arb = 0x864b,
		gl_program_binding_arb = 0x8677,
		gl_max_vertex_attribs_arb = 0x8869,
		gl_vertex_attrib_array_normalized_arb = 0x886a,
		gl_program_error_string_arb = 0x8874,
		gl_program_format_ascii_arb = 0x8875,
		gl_program_format_arb = 0x8876,
		gl_program_instructions_arb = 0x88a0,
		gl_max_program_instructions_arb = 0x88a1,
		gl_program_native_instructions_arb = 0x88a2,
		gl_max_program_native_instructions_arb = 0x88a3,
		gl_program_temporaries_arb = 0x88a4,
		gl_max_program_temporaries_arb = 0x88a5,
		gl_program_native_temporaries_arb = 0x88a6,
		gl_max_program_native_temporaries_arb = 0x88a7,
		gl_program_parameters_arb = 0x88a8,
		gl_max_program_parameters_arb = 0x88a9,
		gl_program_native_parameters_arb = 0x88aa,
		gl_max_program_native_parameters_arb = 0x88ab,
		gl_program_attribs_arb = 0x88ac,
		gl_max_program_attribs_arb = 0x88ad,
		gl_program_native_attribs_arb = 0x88ae,
		gl_max_program_native_attribs_arb = 0x88af,
		gl_program_address_registers_arb = 0x88b0,
		gl_max_program_address_registers_arb = 0x88b1,
		gl_program_native_address_registers_arb = 0x88b2,
		gl_max_program_native_address_registers_arb = 0x88b3,
		gl_max_program_local_parameters_arb = 0x88b4,
		gl_max_program_env_parameters_arb = 0x88b5,
		gl_program_under_native_limits_arb = 0x88b6,
		gl_transpose_current_matrix_arb = 0x88b7,
		gl_matrix0_arb = 0x88c0,
		gl_matrix1_arb = 0x88c1,
		gl_matrix2_arb = 0x88c2,
		gl_matrix3_arb = 0x88c3,
		gl_matrix4_arb = 0x88c4,
		gl_matrix5_arb = 0x88c5,
		gl_matrix6_arb = 0x88c6,
		gl_matrix7_arb = 0x88c7,
		gl_matrix8_arb = 0x88c8,
		gl_matrix9_arb = 0x88c9,
		gl_matrix10_arb = 0x88ca,
		gl_matrix11_arb = 0x88cb,
		gl_matrix12_arb = 0x88cc,
		gl_matrix13_arb = 0x88cd,
		gl_matrix14_arb = 0x88ce,
		gl_matrix15_arb = 0x88cf,
		gl_matrix16_arb = 0x88d0,
		gl_matrix17_arb = 0x88d1,
		gl_matrix18_arb = 0x88d2,
		gl_matrix19_arb = 0x88d3,
		gl_matrix20_arb = 0x88d4,
		gl_matrix21_arb = 0x88d5,
		gl_matrix22_arb = 0x88d6,
		gl_matrix23_arb = 0x88d7,
		gl_matrix24_arb = 0x88d8,
		gl_matrix25_arb = 0x88d9,
		gl_matrix26_arb = 0x88da,
		gl_matrix27_arb = 0x88db,
		gl_matrix28_arb = 0x88dc,
		gl_matrix29_arb = 0x88dd,
		gl_matrix30_arb = 0x88de,
		gl_matrix31_arb = 0x88df,

		//vertex shader
		gl_vertex_shader_arb = 0x8b31,
		gl_max_vertex_uniform_components_arb = 0x8b4a,
		gl_max_varying_floats_arb = 0x8b4b,
		gl_max_vertex_texture_image_units_arb = 0x8b4c,
		gl_max_combined_texture_image_units_arb = 0x8b4d,
		gl_object_active_attributes_arb = 0x8b89,
		gl_object_active_attribute_max_length_arb = 0x8b8a,

		//vertex type 10f_11f_11f rev
		//gl_unsigned_int_10f_11f_11f_rev = 0x8c3b,

		//vertex type 2_10_10_10 rev
		gl_unsigned_int_2_10_10_10_rev = 0x8368,
		gl_int_2_10_10_10_rev = 0x8d9f,

		//viewport array
		gl_depth_range = 0x0b70,
		gl_viewport = 0x0ba2,
		gl_scissor_box = 0x0c10,
		gl_scissor_test = 0x0c11,
		gl_max_viewports = 0x825b,
		gl_viewport_subpixel_bits = 0x825c,
		gl_viewport_bounds_range = 0x825d,
		gl_layer_provoking_vertex = 0x825e,
		gl_viewport_index_provoking_vertex = 0x825f,
		gl_undefined_vertex = 0x8260,
		//gl_first_vertex_convention = 0x8e4d,
		//gl_last_vertex_convention = 0x8e4e,
		//gl_provoking_vertex = 0x8e4f
	};

	//ES2 compatibility
	void (*glClearDepthf) (GLclampf d) = nullptr;
	void (*glDepthRangef) (GLclampf n, GLclampf f) = nullptr;
	void (*glGetShaderPrecisionFormat) (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) = nullptr;
	void (*glReleaseShaderCompiler) (void) = nullptr;
	void (*glShaderBinary) (GLsizei count, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length) = nullptr;

	bool ARB_ES2_compatibility = false;

	//ES3 1 compatibility
	void (*glMemoryBarrierByRegion) (GLbitfield barriers) = nullptr;
	bool ARB_ES3_1_compatibility = false;

	//ES3 2 compatibility
	void (*glPrimitiveBoundingBoxARB) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW) = nullptr;
	bool ARB_ES3_2_compatibility = false;

	//ES3 compatibility
	bool ARB_ES3_compatibility = false;

	//arrays of arrays
	bool ARB_arrays_of_arrays = false;

	//base instance
	void (*glDrawArraysInstancedBaseInstance) (GLenum mode, GLint first, GLsizei count, GLsizei primcount, GLuint baseinstance) = nullptr;
	void (*glDrawElementsInstancedBaseInstance) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount, GLuint baseinstance) = nullptr;
	void (*glDrawElementsInstancedBaseVertexBaseInstance) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount, GLint basevertex, GLuint baseinstance) = nullptr;
	bool ARB_base_instance = false;

	//bindless texture
	GLuint64(*glGetImageHandleARB) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format) = nullptr;
	GLuint64(*glGetTextureHandleARB) (GLuint texture) = nullptr;
	GLuint64(*glGetTextureSamplerHandleARB) (GLuint texture, GLuint sampler) = nullptr;
	void (*glGetVertexAttribLui64vARB) (GLuint index, GLenum pname, GLuint64EXT* params) = nullptr;
	GLboolean(*glIsImageHandleResidentARB) (GLuint64 handle) = nullptr;
	GLboolean(*glIsTextureHandleResidentARB) (GLuint64 handle) = nullptr;
	void (*glMakeImageHandleNonResidentARB) (GLuint64 handle) = nullptr;
	void (*glMakeImageHandleResidentARB) (GLuint64 handle, GLenum access) = nullptr;
	void (*glMakeTextureHandleNonResidentARB) (GLuint64 handle) = nullptr;
	void (*glMakeTextureHandleResidentARB) (GLuint64 handle) = nullptr;
	void (*glProgramUniformHandleui64ARB) (GLuint program, GLint location, GLuint64 value) = nullptr;
	void (*glProgramUniformHandleui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* values) = nullptr;
	void (*glUniformHandleui64ARB) (GLint location, GLuint64 value) = nullptr;
	void (*glUniformHandleui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
	void (*glVertexAttribL1ui64ARB) (GLuint index, GLuint64EXT x) = nullptr;
	void (*glVertexAttribL1ui64vARB) (GLuint index, const GLuint64EXT* v) = nullptr;
	bool ARB_bindless_texture = false;

	//blend func extended
	void (*glBindFragDataLocationIndexed) (GLuint program, GLuint colorNumber, GLuint index, const GLchar * name) = nullptr;
	GLint(*glGetFragDataIndex) (GLuint program, const GLchar* name) = nullptr;
	bool ARB_blend_func_extended = false;

	//buffer storage
	void (*glBufferStorage) (GLenum target, GLsizeiptr size, const void* data, GLbitfield flags) = nullptr;
	bool ARB_buffer_storage = false;

	//cl event
	GLsync(*glCreateSyncFromCLeventARB) (cl_context context, cl_event event, GLbitfield flags) = nullptr;
	bool ARB_cl_event = false;

	//clear buffer object
	void (*glClearBufferData) (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data) = nullptr;
	void (*glClearBufferSubData) (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) = nullptr;
	void (*glClearNamedBufferDataEXT) (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data) = nullptr;
	void (*glClearNamedBufferSubDataEXT) (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) = nullptr;
	bool ARB_clear_buffer_object = false;

	//clear texture
	void (*glClearTexImage) (GLuint texture, GLint level, GLenum format, GLenum type, const void* data) = nullptr;
	void (*glClearTexSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data) = nullptr;
	bool ARB_clear_texture = false;

	//clip control
	void (*glClipControl) (GLenum origin, GLenum depth) = nullptr;
	bool ARB_clip_control = false;

	//color buffer float
	void (*glClampColorARB) (GLenum target, GLenum clamp) = nullptr;
	bool ARB_color_buffer_float = false;

	//compatibility
	bool ARB_compatibility = false;

	//compressed texture pixel storage
	bool ARB_compressed_texture_pixel_storage = false;

	//compute shader
	void (*glDispatchCompute) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) = nullptr;
	void (*glDispatchComputeIndirect) (GLintptr indirect) = nullptr;
	bool ARB_compute_shader = false;

	//compute variable group size
	void (*glDispatchComputeGroupSizeARB) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, GLuint group_size_x, GLuint group_size_y, GLuint group_size_z) = nullptr;
	bool ARB_compute_variable_group_size = false;
	
	 //conditional render inverted
	bool ARB_conditional_render_inverted = false;

	//conservative depth
	bool ARB_conservative_depth = false;

	//copy buffer
	void (*glCopyBufferSubData) (GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size) = nullptr;
	bool ARB_copy_buffer = false;

	//copy image
	void (*glCopyImageSubData) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) = nullptr;
	bool ARB_copy_image = false;
	
	//cull distance
	bool ARB_cull_distance = false;

	//debug output
	typedef void (*GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam);

	void (*glDebugMessageCallbackARB) (GLDEBUGPROC callback, const void* userParam) = nullptr;
	void (*glDebugMessageControlARB) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled) = nullptr;
	void (*glDebugMessageInsertARB) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf) = nullptr;
	GLuint(*glGetDebugMessageLogARB) (GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog) = nullptr;

	bool ARB_debug_output = false;

	//depth buffer float
	bool ARB_depth_buffer_float = false;

	//depth clamp
	bool ARB_depth_clamp = false;

	//depth texture
	bool ARB_depth_texture = false;

	//derivative control
	bool ARB_derivative_control = false;

	//direct state access
	void (*glBindTextureUnit) (GLuint unit, GLuint texture) = nullptr;
	void (*glBlitNamedFramebuffer) (GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
	GLenum (*glCheckNamedFramebufferStatus) (GLuint framebuffer, GLenum target) = nullptr;
	void (*glClearNamedBufferData) (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data) = nullptr;
	void (*glClearNamedBufferSubData) (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) = nullptr;
	void (*glClearNamedFramebufferfi) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) = nullptr;
	void (*glClearNamedFramebufferfv) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat* value) = nullptr;
	void (*glClearNamedFramebufferiv) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value) = nullptr;
	void (*glClearNamedFramebufferuiv) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value) = nullptr;
	void (*glCompressedTextureSubImage1D) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	void (*glCompressedTextureSubImage2D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	void (*glCompressedTextureSubImage3D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	void (*glCopyNamedBufferSubData) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) = nullptr;
	void (*glCopyTextureSubImage1D) (GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = nullptr;
	void (*glCopyTextureSubImage2D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	void (*glCopyTextureSubImage3D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	void (*glCreateBuffers) (GLsizei n, GLuint* buffers) = nullptr;
	void (*glCreateFramebuffers) (GLsizei n, GLuint* framebuffers) = nullptr;
	void (*glCreateProgramPipelines) (GLsizei n, GLuint* pipelines) = nullptr;
	void (*glCreateQueries) (GLenum target, GLsizei n, GLuint* ids) = nullptr;
	void (*glCreateRenderbuffers) (GLsizei n, GLuint* renderbuffers) = nullptr;
	void (*glCreateSamplers) (GLsizei n, GLuint* samplers) = nullptr;
	void (*glCreateTextures) (GLenum target, GLsizei n, GLuint* textures) = nullptr;
	void (*glCreateTransformFeedbacks) (GLsizei n, GLuint* ids) = nullptr;
	void (*glCreateVertexArrays) (GLsizei n, GLuint* arrays) = nullptr;
	void (*glDisableVertexArrayAttrib) (GLuint vaobj, GLuint index) = nullptr;
	void (*glEnableVertexArrayAttrib) (GLuint vaobj, GLuint index) = nullptr;
	void (*glFlushMappedNamedBufferRange) (GLuint buffer, GLintptr offset, GLsizeiptr length) = nullptr;
	void (*glGenerateTextureMipmap) (GLuint texture) = nullptr;
	void (*glGetCompressedTextureImage) (GLuint texture, GLint level, GLsizei bufSize, void* pixels) = nullptr;
	void (*glGetNamedBufferParameteri64v) (GLuint buffer, GLenum pname, GLint64* params) = nullptr;
	void (*glGetNamedBufferParameteriv) (GLuint buffer, GLenum pname, GLint* params) = nullptr;
	void (*glGetNamedBufferPointerv) (GLuint buffer, GLenum pname, void** params) = nullptr;
	void (*glGetNamedBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr size, void* data) = nullptr;
	void (*glGetNamedFramebufferAttachmentParameteriv) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params) = nullptr;
	void (*glGetNamedFramebufferParameteriv) (GLuint framebuffer, GLenum pname, GLint* param) = nullptr;
	void (*glGetNamedRenderbufferParameteriv) (GLuint renderbuffer, GLenum pname, GLint* params) = nullptr;
	void (*glGetQueryBufferObjecti64v) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset) = nullptr;
	void (*glGetQueryBufferObjectiv) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset) = nullptr;
	void (*glGetQueryBufferObjectui64v) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset) = nullptr;
	void (*glGetQueryBufferObjectuiv) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset) = nullptr;
	void (*glGetTextureImage) (GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels) = nullptr;
	void (*glGetTextureLevelParameterfv) (GLuint texture, GLint level, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetTextureLevelParameteriv) (GLuint texture, GLint level, GLenum pname, GLint* params) = nullptr;
	void (*glGetTextureParameterIiv) (GLuint texture, GLenum pname, GLint* params) = nullptr;
	void (*glGetTextureParameterIuiv) (GLuint texture, GLenum pname, GLuint* params) = nullptr;
	void (*glGetTextureParameterfv) (GLuint texture, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetTextureParameteriv) (GLuint texture, GLenum pname, GLint* params) = nullptr;
	void (*glGetTransformFeedbacki64_v) (GLuint xfb, GLenum pname, GLuint index, GLint64* param) = nullptr;
	void (*glGetTransformFeedbacki_v) (GLuint xfb, GLenum pname, GLuint index, GLint* param) = nullptr;
	void (*glGetTransformFeedbackiv) (GLuint xfb, GLenum pname, GLint* param) = nullptr;
	void (*glGetVertexArrayIndexed64iv) (GLuint vaobj, GLuint index, GLenum pname, GLint64* param) = nullptr;
	void (*glGetVertexArrayIndexediv) (GLuint vaobj, GLuint index, GLenum pname, GLint* param) = nullptr;
	void (*glGetVertexArrayiv) (GLuint vaobj, GLenum pname, GLint* param) = nullptr;
	void (*glInvalidateNamedFramebufferData) (GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments) = nullptr;
	void (*glInvalidateNamedFramebufferSubData) (GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	void* (*glMapNamedBuffer) (GLuint buffer, GLenum access) = nullptr;
	void* (*glMapNamedBufferRange) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) = nullptr;
	void (*glNamedBufferData) (GLuint buffer, GLsizeiptr size, const void* data, GLenum usage) = nullptr;
	void (*glNamedBufferStorage) (GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags) = nullptr;
	void (*glNamedBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) = nullptr;
	void (*glNamedFramebufferDrawBuffer) (GLuint framebuffer, GLenum mode) = nullptr;
	void (*glNamedFramebufferDrawBuffers) (GLuint framebuffer, GLsizei n, const GLenum* bufs) = nullptr;
	void (*glNamedFramebufferParameteri) (GLuint framebuffer, GLenum pname, GLint param) = nullptr;
	void (*glNamedFramebufferReadBuffer) (GLuint framebuffer, GLenum mode) = nullptr;
	void (*glNamedFramebufferRenderbuffer) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
	void (*glNamedFramebufferTexture) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) = nullptr;
	void (*glNamedFramebufferTextureLayer) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
	void (*glNamedRenderbufferStorage) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void (*glNamedRenderbufferStorageMultisample) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void (*glTextureBuffer) (GLuint texture, GLenum internalformat, GLuint buffer) = nullptr;
	void (*glTextureBufferRange) (GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	void (*glTextureParameterIiv) (GLuint texture, GLenum pname, const GLint* params) = nullptr;
	void (*glTextureParameterIuiv) (GLuint texture, GLenum pname, const GLuint* params) = nullptr;
	void (*glTextureParameterf) (GLuint texture, GLenum pname, GLfloat param) = nullptr;
	void (*glTextureParameterfv) (GLuint texture, GLenum pname, const GLfloat* param) = nullptr;
	void (*glTextureParameteri) (GLuint texture, GLenum pname, GLint param) = nullptr;
	void (*glTextureParameteriv) (GLuint texture, GLenum pname, const GLint* param) = nullptr;
	void (*glTextureStorage1D) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width) = nullptr;
	void (*glTextureStorage2D) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void (*glTextureStorage2DMultisample) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	void (*glTextureStorage3D) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
	void (*glTextureStorage3DMultisample) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
	void (*glTextureSubImage1D) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) = nullptr;
	void (*glTextureSubImage2D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) = nullptr;
	void (*glTextureSubImage3D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
	void (*glTransformFeedbackBufferBase) (GLuint xfb, GLuint index, GLuint buffer) = nullptr;
	void (*glTransformFeedbackBufferRange) (GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	GLboolean (*glUnmapNamedBuffer) (GLuint buffer) = nullptr;
	void (*glVertexArrayAttribBinding) (GLuint vaobj, GLuint attribindex, GLuint bindingindex) = nullptr;
	void (*glVertexArrayAttribFormat) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) = nullptr;
	void (*glVertexArrayAttribIFormat) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	void (*glVertexArrayAttribLFormat) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	void (*glVertexArrayBindingDivisor) (GLuint vaobj, GLuint bindingindex, GLuint divisor) = nullptr;
	void (*glVertexArrayElementBuffer) (GLuint vaobj, GLuint buffer) = nullptr;
	void (*glVertexArrayVertexBuffer) (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) = nullptr;
	void (*glVertexArrayVertexBuffers) (GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides) = nullptr;
	bool ARB_direct_state_access = false;

	//draw buffers
	void (*glDrawBuffersARB) (GLsizei n, const GLenum * bufs) = nullptr;
	bool ARB_draw_buffers = false;

	//draw buffers blend
	void (*glBlendEquationSeparateiARB) (GLuint buf, GLenum modeRGB, GLenum modeAlpha) = nullptr;
	void (*glBlendEquationiARB) (GLuint buf, GLenum mode) = nullptr;
	void (*glBlendFuncSeparateiARB) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = nullptr;
	void (*glBlendFunciARB) (GLuint buf, GLenum src, GLenum dst) = nullptr;
	bool ARB_draw_buffers_blend = false;

	//draw elements base vertex
	void (*glDrawElementsBaseVertex) (GLenum mode, GLsizei count, GLenum type, void* indices, GLint basevertex) = nullptr;
	void (*glDrawElementsInstancedBaseVertex) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount, GLint basevertex) = nullptr;
	void (*glDrawRangeElementsBaseVertex) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, void* indices, GLint basevertex) = nullptr;
	void (*glMultiDrawElementsBaseVertex) (GLenum mode, GLsizei* count, GLenum type, void** indices, GLsizei primcount, GLint* basevertex) = nullptr;
	bool ARB_draw_elements_base_vertex = false;

	//draw indirect
	void (*glDrawArraysIndirect) (GLenum mode, const void* indirect) = nullptr;
	void (*glDrawElementsIndirect) (GLenum mode, GLenum type, const void* indirect) = nullptr;
	bool ARB_draw_indirect = false;

	//draw instanced
	bool ARB_draw_instanced = false;
	
	//enhanced layouts
	bool ARB_enhanced_layouts = false;

	//explicit attrib location
	bool ARB_explicit_attrib_location = false;

	//explicit uniform location
	bool ARB_explicit_uniform_location = false;

	//fragment coord conventions
	bool ARB_fragment_coord_conventions = false;

	//fragment layer viewport
	bool ARB_fragment_layer_viewport = false;

	//fragment program
	bool ARB_fragment_program = false;

	//fragment program shadow
	bool ARB_fragment_program_shadow = false;

	//fragment shader
	bool ARB_fragment_shader = false;

	//fragment shader interlock
	bool ARB_fragment_shader_interlock = false;

	//framebuffer no attachments
	void (*glFramebufferParameteri) (GLenum target, GLenum pname, GLint param) = nullptr;
	void (*glGetFramebufferParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glGetNamedFramebufferParameterivEXT) (GLuint framebuffer, GLenum pname, GLint* params) = nullptr;
	void (*glNamedFramebufferParameteriEXT) (GLuint framebuffer, GLenum pname, GLint param) = nullptr;
	bool ARB_framebuffer_no_attachments = false;

	//framebuffer_object
	void (*glBindFramebuffer) (GLenum target, GLuint framebuffer) = nullptr;
	void (*glBindRenderbuffer) (GLenum target, GLuint renderbuffer) = nullptr;
	void (*glBlitFramebuffer) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
	GLenum(*glCheckFramebufferStatus) (GLenum target) = nullptr;
	void (*glDeleteFramebuffers) (GLsizei n, const GLuint* framebuffers) = nullptr;
	void (*glDeleteRenderbuffers) (GLsizei n, const GLuint* renderbuffers) = nullptr;
	void (*glFramebufferRenderbuffer) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
	void (*glFramebufferTexture1D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	void (*glFramebufferTexture2D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	void (*glFramebufferTexture3D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint layer) = nullptr;
	void (*glFramebufferTextureLayer) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
	void (*glGenFramebuffers) (GLsizei n, GLuint* framebuffers) = nullptr;
	void (*glGenRenderbuffers) (GLsizei n, GLuint* renderbuffers) = nullptr;
	void (*glGenerateMipmap) (GLenum target) = nullptr;
	void (*glGetFramebufferAttachmentParameteriv) (GLenum target, GLenum attachment, GLenum pname, GLint* params) = nullptr;
	void (*glGetRenderbufferParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	GLboolean(*glIsFramebuffer) (GLuint framebuffer) = nullptr;
	GLboolean(*glIsRenderbuffer) (GLuint renderbuffer) = nullptr;
	void (*glRenderbufferStorage) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void (*glRenderbufferStorageMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	bool ARB_framebuffer_object = false;

	//framebuffer sRGB
	bool ARB_framebuffer_sRGB = false;

	//geometry shader4
	void (*glFramebufferTextureARB) (GLenum target, GLenum attachment, GLuint texture, GLint level) = nullptr;
	void (*glFramebufferTextureFaceARB) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face) = nullptr;
	void (*glFramebufferTextureLayerARB) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
	void (*glProgramParameteriARB) (GLuint program, GLenum pname, GLint value) = nullptr;
	bool ARB_geometry_shader4 = false;

	//get program binary
	void (*glGetProgramBinary) (GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void* binary) = nullptr;
	void (*glProgramBinary) (GLuint program, GLenum binaryFormat, const void* binary, GLsizei length) = nullptr;
	void (*glProgramParameteri) (GLuint program, GLenum pname, GLint value) = nullptr;
	bool ARB_get_program_binary = false;

	//get texture sub image
	void (*glGetCompressedTextureSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels) = nullptr;
	void (*glGetTextureSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels) = nullptr;
	bool ARB_get_texture_sub_image = false;

	//gl spirv
	void (*glSpecializeShaderARB) (GLuint shader, const GLchar * pEntryPoint, GLuint numSpecializationConstants, const GLuint * pConstantIndex, const GLuint * pConstantValue) = nullptr;
	bool ARB_gl_spirv = false;

	//gpu shader5
	bool ARB_gpu_shader5 = false;

	//gpu shader fp64
	void (*glGetUniformdv) (GLuint program, GLint location, GLdouble * params) = nullptr;
	void (*glUniform1d) (GLint location, GLdouble x) = nullptr;
	void (*glUniform1dv) (GLint location, GLsizei count, const GLdouble* value) = nullptr;
	void (*glUniform2d) (GLint location, GLdouble x, GLdouble y) = nullptr;
	void (*glUniform2dv) (GLint location, GLsizei count, const GLdouble* value) = nullptr;
	void (*glUniform3d) (GLint location, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void (*glUniform3dv) (GLint location, GLsizei count, const GLdouble* value) = nullptr;
	void (*glUniform4d) (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void (*glUniform4dv) (GLint location, GLsizei count, const GLdouble* value) = nullptr;
	void (*glUniformMatrix2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glUniformMatrix2x3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glUniformMatrix2x4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glUniformMatrix3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glUniformMatrix3x2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glUniformMatrix3x4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glUniformMatrix4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glUniformMatrix4x2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glUniformMatrix4x3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	bool ARB_gpu_shader_fp64 = false;

	//gpu shader int64
	void (*glGetUniformi64vARB) (GLuint program, GLint location, GLint64 * params) = nullptr;
	void (*glGetUniformui64vARB) (GLuint program, GLint location, GLuint64* params) = nullptr;
	void (*glGetnUniformi64vARB) (GLuint program, GLint location, GLsizei bufSize, GLint64* params) = nullptr;
	void (*glGetnUniformui64vARB) (GLuint program, GLint location, GLsizei bufSize, GLuint64* params) = nullptr;
	void (*glProgramUniform1i64ARB) (GLuint program, GLint location, GLint64 x) = nullptr;
	void (*glProgramUniform1i64vARB) (GLuint program, GLint location, GLsizei count, const GLint64* value) = nullptr;
	void (*glProgramUniform1ui64ARB) (GLuint program, GLint location, GLuint64 x) = nullptr;
	void (*glProgramUniform1ui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* value) = nullptr;
	void (*glProgramUniform2i64ARB) (GLuint program, GLint location, GLint64 x, GLint64 y) = nullptr;
	void (*glProgramUniform2i64vARB) (GLuint program, GLint location, GLsizei count, const GLint64* value) = nullptr;
	void (*glProgramUniform2ui64ARB) (GLuint program, GLint location, GLuint64 x, GLuint64 y) = nullptr;
	void (*glProgramUniform2ui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* value) = nullptr;
	void (*glProgramUniform3i64ARB) (GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z) = nullptr;
	void (*glProgramUniform3i64vARB) (GLuint program, GLint location, GLsizei count, const GLint64* value) = nullptr;
	void (*glProgramUniform3ui64ARB) (GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z) = nullptr;
	void (*glProgramUniform3ui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* value) = nullptr;
	void (*glProgramUniform4i64ARB) (GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w) = nullptr;
	void (*glProgramUniform4i64vARB) (GLuint program, GLint location, GLsizei count, const GLint64* value) = nullptr;
	void (*glProgramUniform4ui64ARB) (GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w) = nullptr;
	void (*glProgramUniform4ui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* value) = nullptr;
	void (*glUniform1i64ARB) (GLint location, GLint64 x) = nullptr;
	void (*glUniform1i64vARB) (GLint location, GLsizei count, const GLint64* value) = nullptr;
	void (*glUniform1ui64ARB) (GLint location, GLuint64 x) = nullptr;
	void (*glUniform1ui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
	void (*glUniform2i64ARB) (GLint location, GLint64 x, GLint64 y) = nullptr;
	void (*glUniform2i64vARB) (GLint location, GLsizei count, const GLint64* value) = nullptr;
	void (*glUniform2ui64ARB) (GLint location, GLuint64 x, GLuint64 y) = nullptr;
	void (*glUniform2ui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
	void (*glUniform3i64ARB) (GLint location, GLint64 x, GLint64 y, GLint64 z) = nullptr;
	void (*glUniform3i64vARB) (GLint location, GLsizei count, const GLint64* value) = nullptr;
	void (*glUniform3ui64ARB) (GLint location, GLuint64 x, GLuint64 y, GLuint64 z) = nullptr;
	void (*glUniform3ui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
	void (*glUniform4i64ARB) (GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w) = nullptr;
	void (*glUniform4i64vARB) (GLint location, GLsizei count, const GLint64* value) = nullptr;
	void (*glUniform4ui64ARB) (GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w) = nullptr;
	void (*glUniform4ui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
	bool ARB_gpu_shader_int64 = false;

	//half float pixel
	bool ARB_half_float_pixel = false;

	//half float vertex
	bool ARB_half_float_vertex = false;

	//imaging
	void (*glColorSubTable) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void* data) = nullptr;
	void (*glColorTable) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* table) = nullptr;
	void (*glColorTableParameterfv) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	void (*glColorTableParameteriv) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	void (*glConvolutionFilter1D) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* image) = nullptr;
	void (*glConvolutionFilter2D) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* image) = nullptr;
	void (*glConvolutionParameterf) (GLenum target, GLenum pname, GLfloat params) = nullptr;
	void (*glConvolutionParameterfv) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	void (*glConvolutionParameteri) (GLenum target, GLenum pname, GLint params) = nullptr;
	void (*glConvolutionParameteriv) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	void (*glCopyColorSubTable) (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width) = nullptr;
	void (*glCopyColorTable) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = nullptr;
	void (*glCopyConvolutionFilter1D) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = nullptr;
	void (*glCopyConvolutionFilter2D) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	void (*glGetColorTable) (GLenum target, GLenum format, GLenum type, void* table) = nullptr;
	void (*glGetColorTableParameterfv) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetColorTableParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glGetConvolutionFilter) (GLenum target, GLenum format, GLenum type, void* image) = nullptr;
	void (*glGetConvolutionParameterfv) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetConvolutionParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glGetHistogram) (GLenum target, GLboolean reset, GLenum format, GLenum type, void* values) = nullptr;
	void (*glGetHistogramParameterfv) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetHistogramParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glGetMinmax) (GLenum target, GLboolean reset, GLenum format, GLenum types, void* values) = nullptr;
	void (*glGetMinmaxParameterfv) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetMinmaxParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glGetSeparableFilter) (GLenum target, GLenum format, GLenum type, void* row, void* column, void* span) = nullptr;
	void (*glHistogram) (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink) = nullptr;
	void (*glMinmax) (GLenum target, GLenum internalformat, GLboolean sink) = nullptr;
	void (*glResetHistogram) (GLenum target) = nullptr;
	void (*glResetMinmax) (GLenum target) = nullptr;
	void (*glSeparableFilter2D) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* row, const void* column) = nullptr;
	bool ARB_imaging = false;

	//indirect parameters
	void (*glMultiDrawArraysIndirectCountARB) (GLenum mode, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) = nullptr;
	void (*glMultiDrawElementsIndirectCountARB) (GLenum mode, GLenum type, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) = nullptr;
	bool ARB_indirect_parameters = false;

	//instanced arrays
	void (*glDrawArraysInstancedARB) (GLenum mode, GLint first, GLsizei count, GLsizei primcount) = nullptr;
	void (*glDrawElementsInstancedARB) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) = nullptr;
	void (*glVertexAttribDivisorARB) (GLuint index, GLuint divisor) = nullptr;
	bool ARB_instanced_arrays = false;

	//internalformat query
	void (*glGetInternalformativ) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params) = nullptr;
	bool ARB_internalformat_query = false;

	//internalformat query2
	void (*glGetInternalformati64v) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params) = nullptr;
	bool ARB_internalformat_query2 = false;

	//invalidate subdata
	void (*glInvalidateBufferData) (GLuint buffer) = nullptr;
	void (*glInvalidateBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr length) = nullptr;
	void (*glInvalidateFramebuffer) (GLenum target, GLsizei numAttachments, const GLenum* attachments) = nullptr;
	void (*glInvalidateSubFramebuffer) (GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	void (*glInvalidateTexImage) (GLuint texture, GLint level) = nullptr;
	void (*glInvalidateTexSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
	bool ARB_invalidate_subdata = false;

	//map buffer alignment
	bool ARB_map_buffer_alignment = false;

	//map buffer range
	void (*glFlushMappedBufferRange) (GLenum target, GLintptr offset, GLsizeiptr length) = nullptr;
	void* (*glMapBufferRange) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) = nullptr;
	bool ARB_map_buffer_range = false;

	//matrix palette
	void (*glCurrentPaletteMatrixARB) (GLint index) = nullptr;
	void (*glMatrixIndexPointerARB) (GLint size, GLenum type, GLsizei stride, void* pointer) = nullptr;
	void (*glMatrixIndexubvARB) (GLint size, GLubyte* indices) = nullptr;
	void (*glMatrixIndexuivARB) (GLint size, GLuint* indices) = nullptr;
	void (*glMatrixIndexusvARB) (GLint size, GLushort* indices) = nullptr;
	bool ARB_matrix_palette = false;

	//multi bind
	void (*glBindBuffersBase) (GLenum target, GLuint first, GLsizei count, const GLuint * buffers) = nullptr;
	void (*glBindBuffersRange) (GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizeiptr* sizes) = nullptr;
	void (*glBindImageTextures) (GLuint first, GLsizei count, const GLuint* textures) = nullptr;
	void (*glBindSamplers) (GLuint first, GLsizei count, const GLuint* samplers) = nullptr;
	void (*glBindTextures) (GLuint first, GLsizei count, const GLuint* textures) = nullptr;
	void (*glBindVertexBuffers) (GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides) = nullptr;
	bool ARB_multi_bind = false;

	//multi draw indirect
	void (*glMultiDrawArraysIndirect) (GLenum mode, const void* indirect, GLsizei primcount, GLsizei stride) = nullptr;
	void (*glMultiDrawElementsIndirect) (GLenum mode, GLenum type, const void* indirect, GLsizei primcount, GLsizei stride) = nullptr;
	bool ARB_multi_draw_indirect = false;

	//multisample
	void (*glSampleCoverageARB) (GLclampf value, GLboolean invert) = nullptr;
	bool ARB_multisample = false;

	//multitexture
	void (*glActiveTextureARB) (GLenum texture) = nullptr;
	void (*glClientActiveTextureARB) (GLenum texture) = nullptr;
	void (*glMultiTexCoord1dARB) (GLenum target, GLdouble s) = nullptr;
	void (*glMultiTexCoord1dvARB) (GLenum target, const GLdouble* v) = nullptr;
	void (*glMultiTexCoord1fARB) (GLenum target, GLfloat s) = nullptr;
	void (*glMultiTexCoord1fvARB) (GLenum target, const GLfloat* v) = nullptr;
	void (*glMultiTexCoord1iARB) (GLenum target, GLint s) = nullptr;
	void (*glMultiTexCoord1ivARB) (GLenum target, const GLint* v) = nullptr;
	void (*glMultiTexCoord1sARB) (GLenum target, GLshort s) = nullptr;
	void (*glMultiTexCoord1svARB) (GLenum target, const GLshort* v) = nullptr;
	void (*glMultiTexCoord2dARB) (GLenum target, GLdouble s, GLdouble t) = nullptr;
	void (*glMultiTexCoord2dvARB) (GLenum target, const GLdouble* v) = nullptr;
	void (*glMultiTexCoord2fARB) (GLenum target, GLfloat s, GLfloat t) = nullptr;
	void (*glMultiTexCoord2fvARB) (GLenum target, const GLfloat* v) = nullptr;
	void (*glMultiTexCoord2iARB) (GLenum target, GLint s, GLint t) = nullptr;
	void (*glMultiTexCoord2ivARB) (GLenum target, const GLint* v) = nullptr;
	void (*glMultiTexCoord2sARB) (GLenum target, GLshort s, GLshort t) = nullptr;
	void (*glMultiTexCoord2svARB) (GLenum target, const GLshort* v) = nullptr;
	void (*glMultiTexCoord3dARB) (GLenum target, GLdouble s, GLdouble t, GLdouble r) = nullptr;
	void (*glMultiTexCoord3dvARB) (GLenum target, const GLdouble* v) = nullptr;
	void (*glMultiTexCoord3fARB) (GLenum target, GLfloat s, GLfloat t, GLfloat r) = nullptr;
	void (*glMultiTexCoord3fvARB) (GLenum target, const GLfloat* v) = nullptr;
	void (*glMultiTexCoord3iARB) (GLenum target, GLint s, GLint t, GLint r) = nullptr;
	void (*glMultiTexCoord3ivARB) (GLenum target, const GLint* v) = nullptr;
	void (*glMultiTexCoord3sARB) (GLenum target, GLshort s, GLshort t, GLshort r) = nullptr;
	void (*glMultiTexCoord3svARB) (GLenum target, const GLshort* v) = nullptr;
	void (*glMultiTexCoord4dARB) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) = nullptr;
	void (*glMultiTexCoord4dvARB) (GLenum target, const GLdouble* v) = nullptr;
	void (*glMultiTexCoord4fARB) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) = nullptr;
	void (*glMultiTexCoord4fvARB) (GLenum target, const GLfloat* v) = nullptr;
	void (*glMultiTexCoord4iARB) (GLenum target, GLint s, GLint t, GLint r, GLint q) = nullptr;
	void (*glMultiTexCoord4ivARB) (GLenum target, const GLint* v) = nullptr;
	void (*glMultiTexCoord4sARB) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) = nullptr;
	void (*glMultiTexCoord4svARB) (GLenum target, const GLshort* v) = nullptr;
	bool ARB_multitexture = false;

	//occlusion query
	void (*glBeginQueryARB) (GLenum target, GLuint id) = nullptr;
	void (*glDeleteQueriesARB) (GLsizei n, const GLuint* ids) = nullptr;
	void (*glEndQueryARB) (GLenum target) = nullptr;
	void (*glGenQueriesARB) (GLsizei n, GLuint* ids) = nullptr;
	void (*glGetQueryObjectivARB) (GLuint id, GLenum pname, GLint* params) = nullptr;
	void (*glGetQueryObjectuivARB) (GLuint id, GLenum pname, GLuint* params) = nullptr;
	void (*glGetQueryivARB) (GLenum target, GLenum pname, GLint* params) = nullptr;
	GLboolean(*glIsQueryARB) (GLuint id) = nullptr;
	bool ARB_occlusion_query = false;

	//occlusion query2
	bool ARB_occlusion_query2 = false;

	//parallel shader compile
	void (*glMaxShaderCompilerThreadsARB) (GLuint count) = nullptr;
	bool ARB_parallel_shader_compile = false;

	//pipeline statistics query
	bool ARB_pipeline_statistics_query = false;

	//pixel buffer object
	bool ARB_pixel_buffer_object = false;

	//point parameters
	void (*glPointParameterfARB) (GLenum pname, GLfloat param) = nullptr;
	void (*glPointParameterfvARB) (GLenum pname, const GLfloat* params) = nullptr;
	bool ARB_point_parameters = false;

	//point sprite
	bool ARB_point_sprite = false;
	
	//polygon offset clamp
	void (*glPolygonOffsetClamp) (GLfloat factor, GLfloat units, GLfloat clamp) = nullptr;
	bool ARB_polygon_offset_clamp = false;

	//post depth coverage
	bool ARB_post_depth_coverage = false;

	//program interface query
	void (*glGetProgramInterfaceiv) (GLuint program, GLenum programInterface, GLenum pname, GLint * params) = nullptr;
	GLuint(*glGetProgramResourceIndex) (GLuint program, GLenum programInterface, const GLchar* name) = nullptr;
	GLint(*glGetProgramResourceLocation) (GLuint program, GLenum programInterface, const GLchar* name) = nullptr;
	GLint(*glGetProgramResourceLocationIndex) (GLuint program, GLenum programInterface, const GLchar* name) = nullptr;
	void (*glGetProgramResourceName) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name) = nullptr;
	void (*glGetProgramResourceiv) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params) = nullptr;
	bool ARB_program_interface_query = false;

	//provoking vertex
	void (*glProvokingVertex) (GLenum mode) = nullptr;
	bool ARB_provoking_vertex = false;

	// query buffer object
	bool ARB_query_buffer_object = false;

	//robust buffer access behavior
	bool ARB_robust_buffer_access_behavior = false;

	//robustness
	GLenum(*glGetGraphicsResetStatusARB) (void) = nullptr;
	void (*glGetnColorTableARB) (GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* table) = nullptr;
	void (*glGetnCompressedTexImageARB) (GLenum target, GLint lod, GLsizei bufSize, void* img) = nullptr;
	void (*glGetnConvolutionFilterARB) (GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* image) = nullptr;
	void (*glGetnHistogramARB) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values) = nullptr;
	void (*glGetnMapdvARB) (GLenum target, GLenum query, GLsizei bufSize, GLdouble* v) = nullptr;
	void (*glGetnMapfvARB) (GLenum target, GLenum query, GLsizei bufSize, GLfloat* v) = nullptr;
	void (*glGetnMapivARB) (GLenum target, GLenum query, GLsizei bufSize, GLint* v) = nullptr;
	void (*glGetnMinmaxARB) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values) = nullptr;
	void (*glGetnPixelMapfvARB) (GLenum map, GLsizei bufSize, GLfloat* values) = nullptr;
	void (*glGetnPixelMapuivARB) (GLenum map, GLsizei bufSize, GLuint* values) = nullptr;
	void (*glGetnPixelMapusvARB) (GLenum map, GLsizei bufSize, GLushort* values) = nullptr;
	void (*glGetnPolygonStippleARB) (GLsizei bufSize, GLubyte* pattern) = nullptr;
	void (*glGetnSeparableFilterARB) (GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void* row, GLsizei columnBufSize, void* column, void* span) = nullptr;
	void (*glGetnTexImageARB) (GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* img) = nullptr;
	void (*glGetnUniformdvARB) (GLuint program, GLint location, GLsizei bufSize, GLdouble* params) = nullptr;
	void (*glGetnUniformfvARB) (GLuint program, GLint location, GLsizei bufSize, GLfloat* params) = nullptr;
	void (*glGetnUniformivARB) (GLuint program, GLint location, GLsizei bufSize, GLint* params) = nullptr;
	void (*glGetnUniformuivARB) (GLuint program, GLint location, GLsizei bufSize, GLuint* params) = nullptr;
	void (*glReadnPixelsARB) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data) = nullptr;
	bool ARB_robustness = false;

	//robustness application isolation
	bool ARB_robustness_application_isolation = false;

	//robustness share group isolation
	bool ARB_robustness_share_group_isolation = false;

	//sample locations
	void (*glFramebufferSampleLocationsfvARB) (GLenum target, GLuint start, GLsizei count, const GLfloat * v) = nullptr;
	void (*glNamedFramebufferSampleLocationsfvARB) (GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v) = nullptr;
	bool ARB_sample_locations = false;

	//sample shading
	void (*glMinSampleShadingARB) (GLclampf value) = nullptr;
	bool ARB_sample_shading = false;

	//sampler objects
	void (*glBindSampler) (GLuint unit, GLuint sampler) = nullptr;
	void (*glDeleteSamplers) (GLsizei count, const GLuint* samplers) = nullptr;
	void (*glGenSamplers) (GLsizei count, GLuint* samplers) = nullptr;
	void (*glGetSamplerParameterIiv) (GLuint sampler, GLenum pname, GLint* params) = nullptr;
	void (*glGetSamplerParameterIuiv) (GLuint sampler, GLenum pname, GLuint* params) = nullptr;
	void (*glGetSamplerParameterfv) (GLuint sampler, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetSamplerParameteriv) (GLuint sampler, GLenum pname, GLint* params) = nullptr;
	GLboolean(*glIsSampler) (GLuint sampler) = nullptr;
	void (*glSamplerParameterIiv) (GLuint sampler, GLenum pname, const GLint* params) = nullptr;
	void (*glSamplerParameterIuiv) (GLuint sampler, GLenum pname, const GLuint* params) = nullptr;
	void (*glSamplerParameterf) (GLuint sampler, GLenum pname, GLfloat param) = nullptr;
	void (*glSamplerParameterfv) (GLuint sampler, GLenum pname, const GLfloat* params) = nullptr;
	void (*glSamplerParameteri) (GLuint sampler, GLenum pname, GLint param) = nullptr;
	void (*glSamplerParameteriv) (GLuint sampler, GLenum pname, const GLint* params) = nullptr;
	bool ARB_sampler_objects = false;

	//seamless cube map
	bool ARB_seamless_cube_map = false;

	//seamless cubemap per texture
	bool ARB_seamless_cubemap_per_texture = false;

	//separate shader objects
	void (*glActiveShaderProgram) (GLuint pipeline, GLuint program) = nullptr;
	void (*glBindProgramPipeline) (GLuint pipeline) = nullptr;
	GLuint(*glCreateShaderProgramv) (GLenum type, GLsizei count, const GLchar* const* strings) = nullptr;
	void (*glDeleteProgramPipelines) (GLsizei n, const GLuint* pipelines) = nullptr;
	void (*glGenProgramPipelines) (GLsizei n, GLuint* pipelines) = nullptr;
	void (*glGetProgramPipelineInfoLog) (GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog) = nullptr;
	void (*glGetProgramPipelineiv) (GLuint pipeline, GLenum pname, GLint* params) = nullptr;
	GLboolean(*glIsProgramPipeline) (GLuint pipeline) = nullptr;
	void (*glProgramUniform1d) (GLuint program, GLint location, GLdouble x) = nullptr;
	void (*glProgramUniform1dv) (GLuint program, GLint location, GLsizei count, const GLdouble* value) = nullptr;
	void (*glProgramUniform1f) (GLuint program, GLint location, GLfloat x) = nullptr;
	void (*glProgramUniform1fv) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	void (*glProgramUniform1i) (GLuint program, GLint location, GLint x) = nullptr;
	void (*glProgramUniform1iv) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	void (*glProgramUniform1ui) (GLuint program, GLint location, GLuint x) = nullptr;
	void (*glProgramUniform1uiv) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	void (*glProgramUniform2d) (GLuint program, GLint location, GLdouble x, GLdouble y) = nullptr;
	void (*glProgramUniform2dv) (GLuint program, GLint location, GLsizei count, const GLdouble* value) = nullptr;
	void (*glProgramUniform2f) (GLuint program, GLint location, GLfloat x, GLfloat y) = nullptr;
	void (*glProgramUniform2fv) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	void (*glProgramUniform2i) (GLuint program, GLint location, GLint x, GLint y) = nullptr;
	void (*glProgramUniform2iv) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	void (*glProgramUniform2ui) (GLuint program, GLint location, GLuint x, GLuint y) = nullptr;
	void (*glProgramUniform2uiv) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	void (*glProgramUniform3d) (GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void (*glProgramUniform3dv) (GLuint program, GLint location, GLsizei count, const GLdouble* value) = nullptr;
	void (*glProgramUniform3f) (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glProgramUniform3fv) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	void (*glProgramUniform3i) (GLuint program, GLint location, GLint x, GLint y, GLint z) = nullptr;
	void (*glProgramUniform3iv) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	void (*glProgramUniform3ui) (GLuint program, GLint location, GLuint x, GLuint y, GLuint z) = nullptr;
	void (*glProgramUniform3uiv) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	void (*glProgramUniform4d) (GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void (*glProgramUniform4dv) (GLuint program, GLint location, GLsizei count, const GLdouble* value) = nullptr;
	void (*glProgramUniform4f) (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void (*glProgramUniform4fv) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	void (*glProgramUniform4i) (GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w) = nullptr;
	void (*glProgramUniform4iv) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	void (*glProgramUniform4ui) (GLuint program, GLint location, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
	void (*glProgramUniform4uiv) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	void (*glProgramUniformMatrix2dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glProgramUniformMatrix2fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glProgramUniformMatrix2x3dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glProgramUniformMatrix2x3fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glProgramUniformMatrix2x4dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glProgramUniformMatrix2x4fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glProgramUniformMatrix3dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glProgramUniformMatrix3fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glProgramUniformMatrix3x2dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glProgramUniformMatrix3x2fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glProgramUniformMatrix3x4dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glProgramUniformMatrix3x4fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glProgramUniformMatrix4dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glProgramUniformMatrix4fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glProgramUniformMatrix4x2dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glProgramUniformMatrix4x2fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glProgramUniformMatrix4x3dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	void (*glProgramUniformMatrix4x3fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glUseProgramStages) (GLuint pipeline, GLbitfield stages, GLuint program) = nullptr;
	void (*glValidateProgramPipeline) (GLuint pipeline) = nullptr;
	bool ARB_separate_shader_objects = false;

	//shader atomic counter ops
	bool ARB_shader_atomic_counter_ops = false;

	//shader atomic counters
	void (*glGetActiveAtomicCounterBufferiv) (GLuint program, GLuint bufferIndex, GLenum pname, GLint * params) = nullptr;
	bool ARB_shader_atomic_counters = false;
	
	//shader ballot
	bool ARB_shader_ballot = false;

	//shader bit encoding
	bool ARB_shader_bit_encoding = false;

	//shader clock
	bool ARB_shader_clock = false;

	//shader draw parameters
	bool ARB_shader_draw_parameters = false;

	//shader group vote
	bool ARB_shader_group_vote = false;

	//shader image load store
	void (*glBindImageTexture) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) = nullptr;
	void (*glMemoryBarrier) (GLbitfield barriers) = nullptr;
	bool ARB_shader_image_load_store = false;

	//shader image size
	bool ARB_shader_image_size = false;

	//shader objects
	void (*glAttachObjectARB) (GLhandleARB containerObj, GLhandleARB obj) = nullptr;
	void (*glCompileShaderARB) (GLhandleARB shaderObj) = nullptr;
	GLhandleARB(*glCreateProgramObjectARB) (void) = nullptr;
	GLhandleARB(*glCreateShaderObjectARB) (GLenum shaderType) = nullptr;
	void (*glDeleteObjectARB) (GLhandleARB obj) = nullptr;
	void (*glDetachObjectARB) (GLhandleARB containerObj, GLhandleARB attachedObj) = nullptr;
	void (*glGetActiveUniformARB) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLcharARB* name) = nullptr;
	void (*glGetAttachedObjectsARB) (GLhandleARB containerObj, GLsizei maxCount, GLsizei* count, GLhandleARB* obj) = nullptr;
	GLhandleARB(*glGetHandleARB) (GLenum pname) = nullptr;
	void (*glGetInfoLogARB) (GLhandleARB obj, GLsizei maxLength, GLsizei* length, GLcharARB* infoLog) = nullptr;
	void (*glGetObjectParameterfvARB) (GLhandleARB obj, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetObjectParameterivARB) (GLhandleARB obj, GLenum pname, GLint* params) = nullptr;
	void (*glGetShaderSourceARB) (GLhandleARB obj, GLsizei maxLength, GLsizei* length, GLcharARB* source) = nullptr;
	GLint(*glGetUniformLocationARB) (GLhandleARB programObj, const GLcharARB* name) = nullptr;
	void (*glGetUniformfvARB) (GLhandleARB programObj, GLint location, GLfloat* params) = nullptr;
	void (*glGetUniformivARB) (GLhandleARB programObj, GLint location, GLint* params) = nullptr;
	void (*glLinkProgramARB) (GLhandleARB programObj) = nullptr;
	void (*glShaderSourceARB) (GLhandleARB shaderObj, GLsizei count, const GLcharARB** string, const GLint* length) = nullptr;
	void (*glUniform1fARB) (GLint location, GLfloat v0) = nullptr;
	void (*glUniform1fvARB) (GLint location, GLsizei count, const GLfloat* value) = nullptr;
	void (*glUniform1iARB) (GLint location, GLint v0) = nullptr;
	void (*glUniform1ivARB) (GLint location, GLsizei count, const GLint* value) = nullptr;
	void (*glUniform2fARB) (GLint location, GLfloat v0, GLfloat v1) = nullptr;
	void (*glUniform2fvARB) (GLint location, GLsizei count, const GLfloat* value) = nullptr;
	void (*glUniform2iARB) (GLint location, GLint v0, GLint v1) = nullptr;
	void (*glUniform2ivARB) (GLint location, GLsizei count, const GLint* value) = nullptr;
	void (*glUniform3fARB) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2) = nullptr;
	void (*glUniform3fvARB) (GLint location, GLsizei count, const GLfloat* value) = nullptr;
	void (*glUniform3iARB) (GLint location, GLint v0, GLint v1, GLint v2) = nullptr;
	void (*glUniform3ivARB) (GLint location, GLsizei count, const GLint* value) = nullptr;
	void (*glUniform4fARB) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) = nullptr;
	void (*glUniform4fvARB) (GLint location, GLsizei count, const GLfloat* value) = nullptr;
	void (*glUniform4iARB) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3) = nullptr;
	void (*glUniform4ivARB) (GLint location, GLsizei count, const GLint* value) = nullptr;
	void (*glUniformMatrix2fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glUniformMatrix3fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glUniformMatrix4fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	void (*glUseProgramObjectARB) (GLhandleARB programObj) = nullptr;
	void (*glValidateProgramARB) (GLhandleARB programObj) = nullptr;

	bool ARB_shader_objects = false;

	//shader precision
	bool ARB_shader_precision = false;

	//shader stencil export
	bool ARB_shader_stencil_export = false;

	//shader storage buffer object
	void (*glShaderStorageBlockBinding) (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) = nullptr;
	bool ARB_shader_storage_buffer_object = false;

	//shader subroutine
	void (*glGetActiveSubroutineName) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name) = nullptr;
	void (*glGetActiveSubroutineUniformName) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name) = nullptr;
	void (*glGetActiveSubroutineUniformiv) (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values) = nullptr;
	void (*glGetProgramStageiv) (GLuint program, GLenum shadertype, GLenum pname, GLint* values) = nullptr;
	GLuint(*glGetSubroutineIndex) (GLuint program, GLenum shadertype, const GLchar* name) = nullptr;
	GLint(*glGetSubroutineUniformLocation) (GLuint program, GLenum shadertype, const GLchar* name) = nullptr;
	void (*glGetUniformSubroutineuiv) (GLenum shadertype, GLint location, GLuint* params) = nullptr;
	void (*glUniformSubroutinesuiv) (GLenum shadertype, GLsizei count, const GLuint* indices) = nullptr;
	bool ARB_shader_subroutine = false;

	//shader texture image samples
	bool ARB_shader_texture_image_samples = false;

	//shader texture lod
	bool ARB_shader_texture_lod = false;

	//shader viewport layer array
	bool ARB_shader_viewport_layer_array = false;

	//shading language 100
	bool ARB_shading_language_100 = false;

	//shading language 420pack
	bool ARB_shading_language_420pack = false;

	//shading language include
	void (*glCompileShaderIncludeARB) (GLuint shader, GLsizei count, const GLchar * const* path, const GLint * length) = nullptr;
	void (*glDeleteNamedStringARB) (GLint namelen, const GLchar* name) = nullptr;
	void (*glGetNamedStringARB) (GLint namelen, const GLchar* name, GLsizei bufSize, GLint* stringlen, GLchar* string) = nullptr;
	void (*glGetNamedStringivARB) (GLint namelen, const GLchar* name, GLenum pname, GLint* params) = nullptr;
	GLboolean(*glIsNamedStringARB) (GLint namelen, const GLchar* name) = nullptr;
	void (*glNamedStringARB) (GLenum type, GLint namelen, const GLchar* name, GLint stringlen, const GLchar* string) = nullptr;
	bool ARB_shading_language_include = false;

	//shading language packing
	bool ARB_shading_language_packing = false;

	//shadow
	bool ARB_shadow = false;

	//shadow ambient
	bool ARB_shadow_ambient = false;

	//sparse buffer
	void (*glBufferPageCommitmentARB) (GLenum target, GLintptr offset, GLsizeiptr size, GLboolean commit) = nullptr;
	bool ARB_sparse_buffer = false;

//sparse texture
	void (*glTexPageCommitmentARB) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit) = nullptr;
	bool ARB_sparse_texture = false;

	//sparse texture2
	bool ARB_sparse_texture2 = false;

	//sparse texture clamp
	bool ARB_sparse_texture_clamp = false;

	//spirv extensions
	bool ARB_spirv_extensions = false;

	//stencil texturing
	bool ARB_stencil_texturing = false;

	//sync
	GLenum(*glClientWaitSync) (GLsync GLsync, GLbitfield flags, GLuint64 timeout) = nullptr;
	void (*glDeleteSync) (GLsync GLsync) = nullptr;
	GLsync(*glFenceSync) (GLenum condition, GLbitfield flags) = nullptr;
	void (*glGetInteger64v) (GLenum pname, GLint64* params) = nullptr;
	void (*glGetSynciv) (GLsync GLsync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) = nullptr;
	GLboolean(*glIsSync) (GLsync GLsync) = nullptr;
	void (*glWaitSync) (GLsync GLsync, GLbitfield flags, GLuint64 timeout) = nullptr;
	bool ARB_sync = false;

	//tessellation shader
	void (*glPatchParameterfv) (GLenum pname, const GLfloat * values) = nullptr;
	void (*glPatchParameteri) (GLenum pname, GLint value) = nullptr;
	bool ARB_tessellation_shader = false;

	//texture barrier
	void (*glTextureBarrier) (void) = nullptr;
	bool ARB_texture_barrier = false;

	//texture border clamp
	bool ARB_texture_border_clamp = false;

	//texture buffer object
	void (*glTexBufferARB) (GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
	bool ARB_texture_buffer_object = false;

	// texture buffer object rgb32
	bool ARB_texture_buffer_object_rgb32 = false;

	//texture buffer range
	void (*glTexBufferRange) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	void (*glTextureBufferRangeEXT) (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	bool ARB_texture_buffer_range = false;

	//texture compression
	void (*glCompressedTexImage1DARB) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) = nullptr;
	void (*glCompressedTexImage2DARB) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) = nullptr;
	void (*glCompressedTexImage3DARB) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) = nullptr;
	void (*glCompressedTexSubImage1DARB) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	void (*glCompressedTexSubImage2DARB) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	void (*glCompressedTexSubImage3DARB) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	void (*glGetCompressedTexImageARB) (GLenum target, GLint lod, void* img) = nullptr;
	bool ARB_texture_compression = false;

	//texture compression bptc
	bool ARB_texture_compression_bptc = false;

	//texture compression rgtc
	bool ARB_texture_compression_rgtc = false;

	//texture cube map
	bool ARB_texture_cube_map = false;

	//texture cube map array
	bool ARB_texture_cube_map_array = false;

	//texture env add
	bool ARB_texture_env_add = false;

	//texture env combine
	bool ARB_texture_env_combine = false;

	//texture env crossbar
	bool ARB_texture_env_crossbar = false;

	//texture env dot3
	bool ARB_texture_env_dot3 = false;

	//texture filter anisotropic
	bool ARB_texture_filter_anisotropic = false;

	//texture filter minmax
	bool ARB_texture_filter_minmax = false;
	
	//texture float
	bool ARB_texture_float = false;

	//texture gather
	bool ARB_texture_gather = false;

	//texture mirror clamp to edge
	bool ARB_texture_mirror_clamp_to_edge = false;

	//texture mirrored repeat
	bool ARB_texture_mirrored_repeat = false;

	//texture multisample
	void (*glGetMultisamplefv) (GLenum pname, GLuint index, GLfloat * val) = nullptr;
	void (*glSampleMaski) (GLuint index, GLbitfield mask) = nullptr;
	void (*glTexImage2DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	void (*glTexImage3DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
	bool ARB_texture_multisample = false;

	//texture non power of two
	bool ARB_texture_non_power_of_two = false;

	//texture query levels
	bool ARB_texture_query_levels = false;

	//texture query lod
	bool ARB_texture_query_lod = false;

	//texture rectangle
	bool ARB_texture_rectangle = false;

	//texture rg
	bool ARB_texture_rg = false;

	//texturergb10 a2ui
	bool ARB_texture_rgb10_a2ui = false;
	
	//texture stencil8
	bool ARB_texture_stencil8 = false;

	//texture storage
	void (*glTexStorage1D) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) = nullptr;
	void (*glTexStorage2D) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void (*glTexStorage3D) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
	bool ARB_texture_storage = false;

	//texture storage multisample
	void (*glTexStorage2DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	void (*glTexStorage3DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
	void (*glTextureStorage2DMultisampleEXT) (GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	void (*glTextureStorage3DMultisampleEXT) (GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
	bool ARB_texture_storage_multisample = false;

	//texture swizzle
	bool ARB_texture_swizzle = false;

	//texture view
	void (*glTextureView) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) = nullptr;
	bool ARB_texture_view = false;

	//timer query
	void (*glGetQueryObjecti64v) (GLuint id, GLenum pname, GLint64 * params) = nullptr;
	void (*glGetQueryObjectui64v) (GLuint id, GLenum pname, GLuint64* params) = nullptr;
	void (*glQueryCounter) (GLuint id, GLenum target) = nullptr;
	bool ARB_timer_query = false;

	//transform feedback2
	void (*glBindTransformFeedback) (GLenum target, GLuint id) = nullptr;
	void (*glDeleteTransformFeedbacks) (GLsizei n, const GLuint* ids) = nullptr;
	void (*glDrawTransformFeedback) (GLenum mode, GLuint id) = nullptr;
	void (*glGenTransformFeedbacks) (GLsizei n, GLuint* ids) = nullptr;
	GLboolean(*glIsTransformFeedback) (GLuint id) = nullptr;
	void (*glPauseTransformFeedback) (void) = nullptr;
	void (*glResumeTransformFeedback) (void) = nullptr;
	bool ARB_transform_feedback2 = false;

	//transform feedback3
	void (*glBeginQueryIndexed) (GLenum target, GLuint index, GLuint id) = nullptr;
	void (*glDrawTransformFeedbackStream) (GLenum mode, GLuint id, GLuint stream) = nullptr;
	void (*glEndQueryIndexed) (GLenum target, GLuint index) = nullptr;
	void (*glGetQueryIndexediv) (GLenum target, GLuint index, GLenum pname, GLint* params) = nullptr;
	bool ARB_transform_feedback3 = false;

	//transform feedback instanced
	void (*glDrawTransformFeedbackInstanced) (GLenum mode, GLuint id, GLsizei primcount) = nullptr;
	void (*glDrawTransformFeedbackStreamInstanced) (GLenum mode, GLuint id, GLuint stream, GLsizei primcount) = nullptr;

	//transform feedback instanced
	bool ARB_transform_feedback_instanced = false;

	//transform feedback overflow query
	bool ARB_transform_feedback_overflow_query = false;

	//transpose matrix
	void (*glLoadTransposeMatrixdARB) (GLdouble m[16]) = nullptr;
	void (*glLoadTransposeMatrixfARB) (GLfloat m[16]) = nullptr;
	void (*glMultTransposeMatrixdARB) (GLdouble m[16]) = nullptr;
	void (*glMultTransposeMatrixfARB) (GLfloat m[16]) = nullptr;
	bool ARB_transpose_matrix = false;

	//uniform buffer object
	void (*glBindBufferBase) (GLenum target, GLuint index, GLuint buffer) = nullptr;
	void (*glBindBufferRange) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	void (*glGetActiveUniformBlockName) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) = nullptr;
	void (*glGetActiveUniformBlockiv) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params) = nullptr;
	void (*glGetActiveUniformName) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName) = nullptr;
	void (*glGetActiveUniformsiv) (GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params) = nullptr;
	void (*glGetIntegeri_v) (GLenum target, GLuint index, GLint* data) = nullptr;
	GLuint(*glGetUniformBlockIndex) (GLuint program, const GLchar* uniformBlockName) = nullptr;
	void (*glGetUniformIndices) (GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices) = nullptr;
	void (*glUniformBlockBinding) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) = nullptr;
	bool ARB_uniform_buffer_object = false;

	//vertex array bgra
	bool ARB_vertex_array_bgra = false;

	//vertex array object
	void (*glBindVertexArray) (GLuint array) = nullptr;
	void (*glDeleteVertexArrays) (GLsizei n, const GLuint* arrays) = nullptr;
	void (*glGenVertexArrays) (GLsizei n, GLuint* arrays) = nullptr;
	GLboolean(*glIsVertexArray) (GLuint array) = nullptr;
	bool ARB_vertex_array_object = false;

	//vertex attrib 64bit
	void (*glGetVertexAttribLdv) (GLuint index, GLenum pname, GLdouble * params) = nullptr;
	void (*glVertexAttribL1d) (GLuint index, GLdouble x) = nullptr;
	void (*glVertexAttribL1dv) (GLuint index, const GLdouble* v) = nullptr;
	void (*glVertexAttribL2d) (GLuint index, GLdouble x, GLdouble y) = nullptr;
	void (*glVertexAttribL2dv) (GLuint index, const GLdouble* v) = nullptr;
	void (*glVertexAttribL3d) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void (*glVertexAttribL3dv) (GLuint index, const GLdouble* v) = nullptr;
	void (*glVertexAttribL4d) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void (*glVertexAttribL4dv) (GLuint index, const GLdouble* v) = nullptr;
	void (*glVertexAttribLPointer) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
	bool ARB_vertex_attrib_64bit = false;

	//vertex attrib binding
	void (*glBindVertexBuffer) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) = nullptr;
	void (*glVertexArrayBindVertexBufferEXT) (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) = nullptr;
	void (*glVertexArrayVertexAttribBindingEXT) (GLuint vaobj, GLuint attribindex, GLuint bindingindex) = nullptr;
	void (*glVertexArrayVertexAttribFormatEXT) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) = nullptr;
	void (*glVertexArrayVertexAttribIFormatEXT) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	void (*glVertexArrayVertexAttribLFormatEXT) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	void (*glVertexArrayVertexBindingDivisorEXT) (GLuint vaobj, GLuint bindingindex, GLuint divisor) = nullptr;
	void (*glVertexAttribBinding) (GLuint attribindex, GLuint bindingindex) = nullptr;
	void (*glVertexAttribFormat) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) = nullptr;
	void (*glVertexAttribIFormat) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	void (*glVertexAttribLFormat) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	void (*glVertexBindingDivisor) (GLuint bindingindex, GLuint divisor) = nullptr;
	bool ARB_vertex_attrib_binding = false;

	//vertex blend
	void (*glVertexBlendARB) (GLint count) = nullptr;
	void (*glWeightPointerARB) (GLint size, GLenum type, GLsizei stride, void* pointer) = nullptr;
	void (*glWeightbvARB) (GLint size, GLbyte* weights) = nullptr;
	void (*glWeightdvARB) (GLint size, GLdouble* weights) = nullptr;
	void (*glWeightfvARB) (GLint size, GLfloat* weights) = nullptr;
	void (*glWeightivARB) (GLint size, GLint* weights) = nullptr;
	void (*glWeightsvARB) (GLint size, GLshort* weights) = nullptr;
	void (*glWeightubvARB) (GLint size, GLubyte* weights) = nullptr;
	void (*glWeightuivARB) (GLint size, GLuint* weights) = nullptr;
	void (*glWeightusvARB) (GLint size, GLushort* weights) = nullptr;
	bool ARB_vertex_blend = false;

	//vertex buffer object 
	void (*glBindBufferARB) (GLenum target, GLuint buffer) = nullptr;
	void (*glBufferDataARB) (GLenum target, GLsizeiptrARB size, const void* data, GLenum usage) = nullptr;
	void (*glBufferSubDataARB) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void* data) = nullptr;
	void (*glDeleteBuffersARB) (GLsizei n, const GLuint* buffers) = nullptr;
	void (*glGenBuffersARB) (GLsizei n, GLuint* buffers) = nullptr;
	void (*glGetBufferParameterivARB) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glGetBufferPointervARB) (GLenum target, GLenum pname, void** params) = nullptr;
	void (*glGetBufferSubDataARB) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, void* data) = nullptr;
	GLboolean(*glIsBufferARB) (GLuint buffer) = nullptr;
	void* (*glMapBufferARB) (GLenum target, GLenum access) = nullptr;
	GLboolean(*glUnmapBufferARB) (GLenum target) = nullptr;
	bool ARB_vertex_buffer_object = false;

	//vertex program
	void (*glBindProgramARB) (GLenum target, GLuint program) = nullptr;
	void (*glDeleteProgramsARB) (GLsizei n, const GLuint* programs) = nullptr;
	void (*glDisableVertexAttribArrayARB) (GLuint index) = nullptr;
	void (*glEnableVertexAttribArrayARB) (GLuint index) = nullptr;
	void (*glGenProgramsARB) (GLsizei n, GLuint* programs) = nullptr;
	void (*glGetProgramEnvParameterdvARB) (GLenum target, GLuint index, GLdouble* params) = nullptr;
	void (*glGetProgramEnvParameterfvARB) (GLenum target, GLuint index, GLfloat* params) = nullptr;
	void (*glGetProgramLocalParameterdvARB) (GLenum target, GLuint index, GLdouble* params) = nullptr;
	void (*glGetProgramLocalParameterfvARB) (GLenum target, GLuint index, GLfloat* params) = nullptr;
	void (*glGetProgramStringARB) (GLenum target, GLenum pname, void* string) = nullptr;
	void (*glGetProgramivARB) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glGetVertexAttribPointervARB) (GLuint index, GLenum pname, void** pointer) = nullptr;
	void (*glGetVertexAttribdvARB) (GLuint index, GLenum pname, GLdouble* params) = nullptr;
	void (*glGetVertexAttribfvARB) (GLuint index, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetVertexAttribivARB) (GLuint index, GLenum pname, GLint* params) = nullptr;
	GLboolean(*glIsProgramARB) (GLuint program) = nullptr;
	void (*glProgramEnvParameter4dARB) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void (*glProgramEnvParameter4dvARB) (GLenum target, GLuint index, const GLdouble* params) = nullptr;
	void (*glProgramEnvParameter4fARB) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void (*glProgramEnvParameter4fvARB) (GLenum target, GLuint index, const GLfloat* params) = nullptr;
	void (*glProgramLocalParameter4dARB) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void (*glProgramLocalParameter4dvARB) (GLenum target, GLuint index, const GLdouble* params) = nullptr;
	void (*glProgramLocalParameter4fARB) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void (*glProgramLocalParameter4fvARB) (GLenum target, GLuint index, const GLfloat* params) = nullptr;
	void (*glProgramStringARB) (GLenum target, GLenum format, GLsizei len, const void* string) = nullptr;
	void (*glVertexAttrib1dARB) (GLuint index, GLdouble x) = nullptr;
	void (*glVertexAttrib1dvARB) (GLuint index, const GLdouble* v) = nullptr;
	void (*glVertexAttrib1fARB) (GLuint index, GLfloat x) = nullptr;
	void (*glVertexAttrib1fvARB) (GLuint index, const GLfloat* v) = nullptr;
	void (*glVertexAttrib1sARB) (GLuint index, GLshort x) = nullptr;
	void (*glVertexAttrib1svARB) (GLuint index, const GLshort* v) = nullptr;
	void (*glVertexAttrib2dARB) (GLuint index, GLdouble x, GLdouble y) = nullptr;
	void (*glVertexAttrib2dvARB) (GLuint index, const GLdouble* v) = nullptr;
	void (*glVertexAttrib2fARB) (GLuint index, GLfloat x, GLfloat y) = nullptr;
	void (*glVertexAttrib2fvARB) (GLuint index, const GLfloat* v) = nullptr;
	void (*glVertexAttrib2sARB) (GLuint index, GLshort x, GLshort y) = nullptr;
	void (*glVertexAttrib2svARB) (GLuint index, const GLshort* v) = nullptr;
	void (*glVertexAttrib3dARB) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void (*glVertexAttrib3dvARB) (GLuint index, const GLdouble* v) = nullptr;
	void (*glVertexAttrib3fARB) (GLuint index, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glVertexAttrib3fvARB) (GLuint index, const GLfloat* v) = nullptr;
	void (*glVertexAttrib3sARB) (GLuint index, GLshort x, GLshort y, GLshort z) = nullptr;
	void (*glVertexAttrib3svARB) (GLuint index, const GLshort* v) = nullptr;
	void (*glVertexAttrib4NbvARB) (GLuint index, const GLbyte* v) = nullptr;
	void (*glVertexAttrib4NivARB) (GLuint index, const GLint* v) = nullptr;
	void (*glVertexAttrib4NsvARB) (GLuint index, const GLshort* v) = nullptr;
	void (*glVertexAttrib4NubARB) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) = nullptr;
	void (*glVertexAttrib4NubvARB) (GLuint index, const GLubyte* v) = nullptr;
	void (*glVertexAttrib4NuivARB) (GLuint index, const GLuint* v) = nullptr;
	void (*glVertexAttrib4NusvARB) (GLuint index, const GLushort* v) = nullptr;
	void (*glVertexAttrib4bvARB) (GLuint index, const GLbyte* v) = nullptr;
	void (*glVertexAttrib4dARB) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void (*glVertexAttrib4dvARB) (GLuint index, const GLdouble* v) = nullptr;
	void (*glVertexAttrib4fARB) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void (*glVertexAttrib4fvARB) (GLuint index, const GLfloat* v) = nullptr;
	void (*glVertexAttrib4ivARB) (GLuint index, const GLint* v) = nullptr;
	void (*glVertexAttrib4sARB) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
	void (*glVertexAttrib4svARB) (GLuint index, const GLshort* v) = nullptr;
	void (*glVertexAttrib4ubvARB) (GLuint index, const GLubyte* v) = nullptr;
	void (*glVertexAttrib4uivARB) (GLuint index, const GLuint* v) = nullptr;
	void (*glVertexAttrib4usvARB) (GLuint index, const GLushort* v) = nullptr;
	void (*glVertexAttribPointerARB) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) = nullptr;
	bool ARB_vertex_program = false;

	//vertex shader
	void (*glBindAttribLocationARB) (GLhandleARB programObj, GLuint index, const GLcharARB * name) = nullptr;
	void (*glGetActiveAttribARB) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLcharARB* name) = nullptr;
	GLint(*glGetAttribLocationARB) (GLhandleARB programObj, const GLcharARB* name) = nullptr;
	bool ARB_vertex_shader = false;

	//vertex type 10f_11f_11f rev
	bool ARB_vertex_type_10f_11f_11f_rev = false;

	//vertex type 2_10_10_10 rev
	void (*glColorP3ui) (GLenum type, GLuint color) = nullptr;
	void (*glColorP3uiv) (GLenum type, const GLuint* color) = nullptr;
	void (*glColorP4ui) (GLenum type, GLuint color) = nullptr;
	void (*glColorP4uiv) (GLenum type, const GLuint* color) = nullptr;
	void (*glMultiTexCoordP1ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	void (*glMultiTexCoordP1uiv) (GLenum texture, GLenum type, const GLuint* coords) = nullptr;
	void (*glMultiTexCoordP2ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	void (*glMultiTexCoordP2uiv) (GLenum texture, GLenum type, const GLuint* coords) = nullptr;
	void (*glMultiTexCoordP3ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	void (*glMultiTexCoordP3uiv) (GLenum texture, GLenum type, const GLuint* coords) = nullptr;
	void (*glMultiTexCoordP4ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	void (*glMultiTexCoordP4uiv) (GLenum texture, GLenum type, const GLuint* coords) = nullptr;
	void (*glNormalP3ui) (GLenum type, GLuint coords) = nullptr;
	void (*glNormalP3uiv) (GLenum type, const GLuint* coords) = nullptr;
	void (*glSecondaryColorP3ui) (GLenum type, GLuint color) = nullptr;
	void (*glSecondaryColorP3uiv) (GLenum type, const GLuint* color) = nullptr;
	void (*glTexCoordP1ui) (GLenum type, GLuint coords) = nullptr;
	void (*glTexCoordP1uiv) (GLenum type, const GLuint* coords) = nullptr;
	void (*glTexCoordP2ui) (GLenum type, GLuint coords) = nullptr;
	void (*glTexCoordP2uiv) (GLenum type, const GLuint* coords) = nullptr;
	void (*glTexCoordP3ui) (GLenum type, GLuint coords) = nullptr;
	void (*glTexCoordP3uiv) (GLenum type, const GLuint* coords) = nullptr;
	void (*glTexCoordP4ui) (GLenum type, GLuint coords) = nullptr;
	void (*glTexCoordP4uiv) (GLenum type, const GLuint* coords) = nullptr;
	void (*glVertexAttribP1ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	void (*glVertexAttribP1uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint* value) = nullptr;
	void (*glVertexAttribP2ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	void (*glVertexAttribP2uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint* value) = nullptr;
	void (*glVertexAttribP3ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	void (*glVertexAttribP3uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint* value) = nullptr;
	void (*glVertexAttribP4ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	void (*glVertexAttribP4uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint* value) = nullptr;
	void (*glVertexP2ui) (GLenum type, GLuint value) = nullptr;
	void (*glVertexP2uiv) (GLenum type, const GLuint* value) = nullptr;
	void (*glVertexP3ui) (GLenum type, GLuint value) = nullptr;
	void (*glVertexP3uiv) (GLenum type, const GLuint* value) = nullptr;
	void (*glVertexP4ui) (GLenum type, GLuint value) = nullptr;
	void (*glVertexP4uiv) (GLenum type, const GLuint* value) = nullptr;
	bool vertex_type_2_10_10_10_rev = false;

	//viewport array
	void (*glDepthRangeArrayv) (GLuint first, GLsizei count, const GLclampd * v) = nullptr;
	void (*glDepthRangeIndexed) (GLuint index, GLclampd n, GLclampd f) = nullptr;
	void (*glGetDoublei_v) (GLenum target, GLuint index, GLdouble* data) = nullptr;
	void (*glGetFloati_v) (GLenum target, GLuint index, GLfloat* data) = nullptr;
	void (*glScissorArrayv) (GLuint first, GLsizei count, const GLint* v) = nullptr;
	void (*glScissorIndexed) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) = nullptr;
	void (*glScissorIndexedv) (GLuint index, const GLint* v) = nullptr;
	void (*glViewportArrayv) (GLuint first, GLsizei count, const GLfloat* v) = nullptr;
	void (*glViewportIndexedf) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) = nullptr;
	void (*glViewportIndexedfv) (GLuint index, const GLfloat* v) = nullptr;
	bool viewport_array  = false;

	//window pos
	void (*glWindowPos2dARB) (GLdouble x, GLdouble y) = nullptr;
	void (*glWindowPos2dvARB) (const GLdouble* p) = nullptr;
	void (*glWindowPos2fARB) (GLfloat x, GLfloat y) = nullptr;
	void (*glWindowPos2fvARB) (const GLfloat* p) = nullptr;
	void (*glWindowPos2iARB) (GLint x, GLint y) = nullptr;
	void (*glWindowPos2ivARB) (const GLint* p) = nullptr;
	void (*glWindowPos2sARB) (GLshort x, GLshort y) = nullptr;
	void (*glWindowPos2svARB) (const GLshort* p) = nullptr;
	void (*glWindowPos3dARB) (GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void (*glWindowPos3dvARB) (const GLdouble* p) = nullptr;
	void (*glWindowPos3fARB) (GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glWindowPos3fvARB) (const GLfloat* p) = nullptr;
	void (*glWindowPos3iARB) (GLint x, GLint y, GLint z) = nullptr;
	void (*glWindowPos3ivARB) (const GLint* p) = nullptr;
	void (*glWindowPos3sARB) (GLshort x, GLshort y, GLshort z) = nullptr;
	void (*glWindowPos3svARB) (const GLshort* p) = nullptr;
	bool ARB_window_pos = false;

	//*< load ARB Extensions
	void LoadARBExtensions()
	{
		//ES2 compatibility
		FetchProcAddress(glClearDepthf, "glClearDepthf");

		FetchProcAddress(glDepthRangef, "glDepthRangef");

		FetchProcAddress(glGetShaderPrecisionFormat, "glGetShaderPrecisionFormat");

		FetchProcAddress(glReleaseShaderCompiler, "glReleaseShaderCompiler");

		FetchProcAddress(glShaderBinary, "glShaderBinary");

		FetchProcAddress(ARB_ES2_compatibility, "GL_ARB_ES2_compatibility");


		//ES3 1 compatibility
		FetchProcAddress(glMemoryBarrierByRegion, "glMemoryBarrierByRegion");

		FetchProcAddress(ARB_ES3_1_compatibility, "ARB_ES3_1_compatibility");


		//ES3 2 compatibility
		FetchProcAddress(glPrimitiveBoundingBoxARB, "glPrimitiveBoundingBoxARB");

		FetchProcAddress(ARB_ES3_2_compatibility, "ARB_ES3_2_compatibility");


		//ES3 compatibility
		FetchProcAddress(ARB_ES3_compatibility, "ARB_ES3_compatibility");


		//arrays of arrays
		FetchProcAddress(ARB_arrays_of_arrays, "ARB_arrays_of_arrays");


		//base instance
		FetchProcAddress(glDrawArraysInstancedBaseInstance, "glDrawArraysInstancedBaseInstance");

		FetchProcAddress(glDrawElementsInstancedBaseInstance, "glDrawElementsInstancedBaseInstance");

		FetchProcAddress(glDrawElementsInstancedBaseVertexBaseInstance, "glDrawElementsInstancedBaseVertexBaseInstance");

		FetchProcAddress(ARB_base_instance, "GL_ARB_base_instance");


		//bindless texture
		FetchProcAddress(glGetImageHandleARB, "glGetImageHandleARB");

		FetchProcAddress(glGetTextureHandleARB, "glGetTextureHandleARB");

		FetchProcAddress(glGetTextureSamplerHandleARB, "glGetTextureSamplerHandleARB");

		FetchProcAddress(glGetVertexAttribLui64vARB, "glGetVertexAttribLui64vARB");

		FetchProcAddress(glIsImageHandleResidentARB, "glIsImageHandleResidentARB");

		FetchProcAddress(glIsTextureHandleResidentARB, "glIsTextureHandleResidentARB");

		FetchProcAddress(glMakeImageHandleNonResidentARB, "glMakeImageHandleNonResidentARB");

		FetchProcAddress(glMakeImageHandleResidentARB, "glMakeImageHandleResidentARB");

		FetchProcAddress(glMakeTextureHandleNonResidentARB, "glMakeTextureHandleNonResidentARB");

		FetchProcAddress(glMakeTextureHandleResidentARB, "glMakeTextureHandleResidentARB");

		FetchProcAddress(glProgramUniformHandleui64ARB, "glProgramUniformHandleui64ARB");

		FetchProcAddress(glProgramUniformHandleui64vARB, "glProgramUniformHandleui64vARB");

		FetchProcAddress(glUniformHandleui64ARB, "glUniformHandleui64ARB");

		FetchProcAddress(glUniformHandleui64vARB, "glUniformHandleui64vARB");

		FetchProcAddress(glVertexAttribL1ui64ARB, "glVertexAttribL1ui64ARB");

		FetchProcAddress(glVertexAttribL1ui64vARB, "glVertexAttribL1ui64vARB");

		FetchProcAddress(ARB_bindless_texture, "GL_ARB_bindless_texture");


		//blend func extended
		FetchProcAddress(glBindFragDataLocationIndexed, "glBindFragDataLocationIndexed");

		FetchProcAddress(glGetFragDataIndex, "glGetFragDataIndex");

		FetchProcAddress(ARB_blend_func_extended, "ARB_blend_func_extended");


		//buffer storage
		FetchProcAddress(glBufferStorage, "glBufferStorage");

		FetchProcAddress(ARB_buffer_storage, "ARB_buffer_storage");


		//cl event
		FetchProcAddress(glCreateSyncFromCLeventARB, "glCreateSyncFromCLeventARB");

		FetchProcAddress(ARB_cl_event, "ARB_cl_event");


		//clear buffer object
		FetchProcAddress(glClearBufferData, "glClearBufferData");

		FetchProcAddress(glClearBufferSubData, "glClearBufferSubData");

		FetchProcAddress(glClearNamedBufferDataEXT, "glClearNamedBufferDataEXT");

		FetchProcAddress(glClearNamedBufferSubDataEXT, "glClearNamedBufferSubDataEXT");

		FetchProcAddress(ARB_clear_buffer_object, "ARB_clear_buffer_object");


		//clear texture
		FetchProcAddress(glClearTexImage, "glClearTexImage");

		FetchProcAddress(glClearTexSubImage, "glClearTexSubImage");

		FetchProcAddress(ARB_clear_texture, "ARB_clear_texture");


		//clip control
		FetchProcAddress(glClipControl, "glClipControl");

		FetchProcAddress(ARB_clip_control, "ARB_clip_control");


		//color buffer float
		FetchProcAddress(glClampColorARB, "glClampColorARB");

		FetchProcAddress(ARB_color_buffer_float, "ARB_color_buffer_float");


		//compatibility
		FetchProcAddress(ARB_compatibility, "ARB_compatibility");


		//compressed texture pixel storage
		FetchProcAddress(ARB_compressed_texture_pixel_storage, "ARB_compressed_texture_pixel_storage");


		//compute shader
		FetchProcAddress(glDispatchCompute, "glDispatchCompute");

		FetchProcAddress(glDispatchComputeIndirect, "glDispatchComputeIndirect");

		FetchProcAddress(ARB_compute_shader, "ARB_compute_shader");


		//compute variable group size
		FetchProcAddress(glDispatchComputeGroupSizeARB, "glDispatchComputeGroupSizeARB");

		FetchProcAddress(ARB_compute_variable_group_size, "ARB_compute_variable_group_size");


		//conditional render inverted
		FetchProcAddress(ARB_conditional_render_inverted, "ARB_conditional_render_inverted");


		//conservative depth
		FetchProcAddress(ARB_conservative_depth, "ARB_conservative_depth");


		//copy buffer
		FetchProcAddress(glCopyBufferSubData, "glCopyBufferSubData");

		FetchProcAddress(ARB_copy_buffer, "ARB_copy_buffer");


		//copy image
		FetchProcAddress(glCopyImageSubData, "glCopyImageSubData");

		FetchProcAddress(ARB_copy_image, "ARB_copy_image");


		//cull distance
		FetchProcAddress(ARB_cull_distance, "ARB_cull_distance");


		//debug output
		FetchProcAddress(glDebugMessageCallbackARB, "glDebugMessageCallbackARB");

		FetchProcAddress(glDebugMessageControlARB, "glDebugMessageControlARB");

		FetchProcAddress(glDebugMessageInsertARB, "glDebugMessageInsertARB");

		FetchProcAddress(glGetDebugMessageLogARB, "glGetDebugMessageLogARB");

		FetchProcAddress(ARB_debug_output, "ARB_debug_output");


		//depth buffer float
		FetchProcAddress(ARB_depth_buffer_float, "ARB_depth_buffer_float");


		//depth clamp
		FetchProcAddress(ARB_depth_clamp, "ARB_depth_clamp");


		//depth texture
		FetchProcAddress(ARB_depth_texture, "ARB_depth_texture");


		//derivative control
		FetchProcAddress(ARB_derivative_control, "ARB_derivative_control");


		//direct state access
		FetchProcAddress(glBindTextureUnit, "glBindTextureUnit");

		FetchProcAddress(glBlitNamedFramebuffer, "glBlitNamedFramebuffer");

		FetchProcAddress(glCheckNamedFramebufferStatus, "glCheckNamedFramebufferStatus");

		FetchProcAddress(glClearNamedBufferData, "glClearNamedBufferData");

		FetchProcAddress(glClearNamedBufferSubData, "glClearNamedBufferSubData");

		FetchProcAddress(glClearNamedFramebufferfi, "glClearNamedFramebufferfi");

		FetchProcAddress(glClearNamedFramebufferfv, "glClearNamedFramebufferfv");

		FetchProcAddress(glClearNamedFramebufferiv, "glClearNamedFramebufferiv");

		FetchProcAddress(glClearNamedFramebufferuiv, "glClearNamedFramebufferuiv");

		FetchProcAddress(glCompressedTextureSubImage1D, "glCompressedTextureSubImage1D");

		FetchProcAddress(glCompressedTextureSubImage2D, "glCompressedTextureSubImage2D");

		FetchProcAddress(glCompressedTextureSubImage3D, "glCompressedTextureSubImage3D");

		FetchProcAddress(glCopyNamedBufferSubData, "glCopyNamedBufferSubData");

		FetchProcAddress(glCopyTextureSubImage1D, "glCopyTextureSubImage1D");

		FetchProcAddress(glCopyTextureSubImage2D, "glCopyTextureSubImage2D");

		FetchProcAddress(glCopyTextureSubImage3D, "glCopyTextureSubImage3D");

		FetchProcAddress(glCreateBuffers, "glCreateBuffers");

		FetchProcAddress(glCreateFramebuffers, "glCreateFramebuffers");

		FetchProcAddress(glCreateProgramPipelines, "glCreateProgramPipelines");

		FetchProcAddress(glCreateQueries, "glCreateQueries");

		FetchProcAddress(glCreateRenderbuffers, "glCreateRenderbuffers");

		FetchProcAddress(glCreateSamplers, "glCreateSamplers");

		FetchProcAddress(glCreateTextures, "glCreateTextures");

		FetchProcAddress(glCreateTransformFeedbacks, "glCreateTransformFeedbacks");

		FetchProcAddress(glCreateVertexArrays, "glCreateVertexArrays");

		FetchProcAddress(glDisableVertexArrayAttrib, "glDisableVertexArrayAttrib");

		FetchProcAddress(glEnableVertexArrayAttrib, "glEnableVertexArrayAttrib");

		FetchProcAddress(glFlushMappedNamedBufferRange, "glFlushMappedNamedBufferRange");

		FetchProcAddress(glGenerateTextureMipmap, "glGenerateTextureMipmap");

		FetchProcAddress(glGetCompressedTextureImage, "glGetCompressedTextureImage");

		FetchProcAddress(glGetNamedBufferParameteri64v, "glGetNamedBufferParameteri64v");

		FetchProcAddress(glGetNamedBufferParameteriv, "glGetNamedBufferParameteriv");

		FetchProcAddress(glGetNamedBufferPointerv, "glGetNamedBufferPointerv");

		FetchProcAddress(glGetNamedBufferSubData, "glGetNamedBufferSubData");

		FetchProcAddress(glGetNamedFramebufferAttachmentParameteriv, "glGetNamedFramebufferAttachmentParameteriv");

		FetchProcAddress(glGetNamedFramebufferParameteriv, "glGetNamedFramebufferParameteriv");

		FetchProcAddress(glGetNamedRenderbufferParameteriv, "glGetNamedRenderbufferParameteriv");

		FetchProcAddress(glGetQueryBufferObjecti64v, "glGetQueryBufferObjecti64v");

		FetchProcAddress(glGetQueryBufferObjectiv, "glGetQueryBufferObjectiv");

		FetchProcAddress(glGetQueryBufferObjectui64v, "glGetQueryBufferObjectui64v");

		FetchProcAddress(glGetQueryBufferObjectuiv, "glGetQueryBufferObjectuiv");

		FetchProcAddress(glGetTextureImage, "glGetTextureImage");

		FetchProcAddress(glGetTextureLevelParameterfv, "glGetTextureLevelParameterfv");

		FetchProcAddress(glGetTextureLevelParameteriv, "glGetTextureLevelParameteriv");

		FetchProcAddress(glGetTextureParameterIiv, "glGetTextureParameterIiv");

		FetchProcAddress(glGetTextureParameterIuiv, "glGetTextureParameterIuiv");

		FetchProcAddress(glGetTextureParameterfv, "glGetTextureParameterfv");

		FetchProcAddress(glGetTextureParameteriv, "glGetTextureParameteriv");

		FetchProcAddress(glGetTransformFeedbacki64_v, "glGetTransformFeedbacki64_v");

		FetchProcAddress(glGetTransformFeedbacki_v, "glGetTransformFeedbacki_v");

		FetchProcAddress(glGetTransformFeedbackiv, "glGetTransformFeedbackiv");

		FetchProcAddress(glGetVertexArrayIndexed64iv, "glGetVertexArrayIndexed64iv");

		FetchProcAddress(glGetVertexArrayIndexediv, "glGetVertexArrayIndexediv");

		FetchProcAddress(glGetVertexArrayiv, "glGetVertexArrayiv");

		FetchProcAddress(glInvalidateNamedFramebufferData, "glInvalidateNamedFramebufferData");

		FetchProcAddress(glInvalidateNamedFramebufferSubData, "glInvalidateNamedFramebufferSubData");

		FetchProcAddress(glMapNamedBuffer, "glMapNamedBuffer");

		FetchProcAddress(glMapNamedBufferRange, "glMapNamedBufferRange");

		FetchProcAddress(glNamedBufferData, "glNamedBufferData");

		FetchProcAddress(glNamedBufferStorage, "glNamedBufferStorage");

		FetchProcAddress(glNamedBufferSubData, "glNamedBufferSubData");

		FetchProcAddress(glNamedFramebufferDrawBuffer, "glNamedFramebufferDrawBuffer");

		FetchProcAddress(glNamedFramebufferDrawBuffers, "glNamedFramebufferDrawBuffers");

		FetchProcAddress(glNamedFramebufferParameteri, "glNamedFramebufferParameteri");

		FetchProcAddress(glNamedFramebufferReadBuffer, "glNamedFramebufferReadBuffer");

		FetchProcAddress(glNamedFramebufferRenderbuffer, "glNamedFramebufferRenderbuffer");

		FetchProcAddress(glNamedFramebufferTexture, "glNamedFramebufferTexture");

		FetchProcAddress(glNamedFramebufferTextureLayer, "glNamedFramebufferTextureLayer");

		FetchProcAddress(glNamedRenderbufferStorage, "glNamedRenderbufferStorage");

		FetchProcAddress(glNamedRenderbufferStorageMultisample, "glNamedRenderbufferStorageMultisample");

		FetchProcAddress(glTextureBuffer, "glTextureBuffer");

		FetchProcAddress(glTextureBufferRange, "glTextureBufferRange");

		FetchProcAddress(glTextureParameterIiv, "glTextureParameterIiv");

		FetchProcAddress(glTextureParameterIuiv, "glTextureParameterIuiv");

		FetchProcAddress(glTextureParameterf, "glTextureParameterf");

		FetchProcAddress(glTextureParameterfv, "glTextureParameterfv");

		FetchProcAddress(glTextureParameteri, "glTextureParameteri");

		FetchProcAddress(glTextureParameteriv, "glTextureParameteriv");

		FetchProcAddress(glTextureStorage1D, "glTextureStorage1D");

		FetchProcAddress(glTextureStorage2D, "glTextureStorage2D");

		FetchProcAddress(glTextureStorage2DMultisample, "glTextureStorage2DMultisample");

		FetchProcAddress(glTextureStorage3D, "glTextureStorage3D");

		FetchProcAddress(glTextureStorage3DMultisample, "glTextureStorage3DMultisample");

		FetchProcAddress(glTextureSubImage1D, "glTextureSubImage1D");

		FetchProcAddress(glTextureSubImage2D, "glTextureSubImage2D");

		FetchProcAddress(glTextureSubImage3D, "glTextureSubImage3D");

		FetchProcAddress(glTransformFeedbackBufferBase, "glTransformFeedbackBufferBase");

		FetchProcAddress(glTransformFeedbackBufferRange, "glTransformFeedbackBufferRange");

		FetchProcAddress(glUnmapNamedBuffer, "glUnmapNamedBuffer");

		FetchProcAddress(glVertexArrayAttribBinding, "glVertexArrayAttribBinding");

		FetchProcAddress(glVertexArrayAttribFormat, "glVertexArrayAttribFormat");

		FetchProcAddress(glVertexArrayAttribIFormat, "glVertexArrayAttribIFormat");

		FetchProcAddress(glVertexArrayAttribLFormat, "glVertexArrayAttribLFormat");

		FetchProcAddress(glVertexArrayBindingDivisor, "glVertexArrayBindingDivisor");

		FetchProcAddress(glVertexArrayElementBuffer, "glVertexArrayElementBuffer");

		FetchProcAddress(glVertexArrayVertexBuffer, "glVertexArrayVertexBuffer");

		FetchProcAddress(glVertexArrayVertexBuffers, "glVertexArrayVertexBuffers");

		FetchProcAddress(ARB_direct_state_access, "ARB_direct_state_access");


		//draw buffers
		FetchProcAddress(glDrawBuffersARB, "glDrawBuffersARB");

		FetchProcAddress(ARB_draw_buffers, "ARB_draw_buffers");


		//draw buffers blend
		FetchProcAddress(glBlendEquationSeparateiARB, "glBlendEquationSeparateiARB");

		FetchProcAddress(glBlendEquationiARB, "glBlendEquationiARB");

		FetchProcAddress(glBlendFuncSeparateiARB, "glBlendFuncSeparateiARB");

		FetchProcAddress(glBlendFunciARB, "glBlendFunciARB");

		FetchProcAddress(ARB_draw_buffers_blend, "ARB_draw_buffers_blend");


		//draw elements base vertex
		FetchProcAddress(glDrawElementsBaseVertex, "glDrawElementsBaseVertex");

		FetchProcAddress(glDrawElementsInstancedBaseVertex, "glDrawElementsInstancedBaseVertex");

		FetchProcAddress(glDrawRangeElementsBaseVertex, "glDrawRangeElementsBaseVertex");

		FetchProcAddress(glMultiDrawElementsBaseVertex, "glMultiDrawElementsBaseVertex");

		FetchProcAddress(ARB_draw_elements_base_vertex, "ARB_draw_elements_base_vertex");


		//draw indirect
		FetchProcAddress(glDrawArraysIndirect, "glDrawArraysIndirect");

		FetchProcAddress(glDrawElementsIndirect, "glDrawElementsIndirect");

		FetchProcAddress(ARB_draw_indirect, "ARB_draw_indirect");


		//draw instanced
		FetchProcAddress(ARB_draw_instanced, "ARB_draw_instanced");


		//enhanced layouts
		FetchProcAddress(ARB_enhanced_layouts, "ARB_enhanced_layouts");


		//explicit attrib location
		FetchProcAddress(ARB_explicit_attrib_location, "ARB_explicit_attrib_location");


		//explicit uniform location
		FetchProcAddress(ARB_explicit_uniform_location, "ARB_explicit_uniform_location");


		//fragment coord conventions
		FetchProcAddress(ARB_fragment_coord_conventions, "ARB_fragment_coord_conventions");


		//fragment layer viewport
		FetchProcAddress(ARB_fragment_layer_viewport, "ARB_fragment_layer_viewport");


		//fragment program
		FetchProcAddress(ARB_fragment_program, "ARB_fragment_program");


		//fragment program shadow
		FetchProcAddress(ARB_fragment_program_shadow, "ARB_fragment_program_shadow");


		//fragment shader
		FetchProcAddress(ARB_fragment_shader, "ARB_fragment_shader");


		//fragment shader interlock
		FetchProcAddress(ARB_fragment_shader_interlock, "ARB_fragment_shader_interlock");


		//framebuffer no attachments
		FetchProcAddress(glFramebufferParameteri, "glFramebufferParameteri");

		FetchProcAddress(glGetFramebufferParameteriv, "glGetFramebufferParameteriv");

		FetchProcAddress(glGetNamedFramebufferParameterivEXT, "glGetNamedFramebufferParameterivEXT");

		FetchProcAddress(glNamedFramebufferParameteriEXT, "glNamedFramebufferParameteriEXT");

		FetchProcAddress(ARB_framebuffer_no_attachments, "ARB_framebuffer_no_attachments");


		//framebuffer_object
		FetchProcAddress(glBindFramebuffer, "glBindFramebuffer");

		FetchProcAddress(glBindRenderbuffer, "glBindRenderbuffer");

		FetchProcAddress(glBlitFramebuffer, "glBlitFramebuffer");

		FetchProcAddress(glCheckFramebufferStatus, "glCheckFramebufferStatus");

		FetchProcAddress(glDeleteFramebuffers, "glDeleteFramebuffers");

		FetchProcAddress(glDeleteRenderbuffers, "glDeleteRenderbuffers");

		FetchProcAddress(glFramebufferRenderbuffer, "glFramebufferRenderbuffer");

		FetchProcAddress(glFramebufferTexture1D, "glFramebufferTexture1D");

		FetchProcAddress(glFramebufferTexture2D, "glFramebufferTexture2D");

		FetchProcAddress(glFramebufferTexture3D, "glFramebufferTexture3D");

		FetchProcAddress(glFramebufferTextureLayer, "glFramebufferTextureLayer");

		FetchProcAddress(glGenFramebuffers, "glGenFramebuffers");

		FetchProcAddress(glGenRenderbuffers, "glGenRenderbuffers");

		FetchProcAddress(glGenerateMipmap, "glGenerateMipmap");

		FetchProcAddress(glGetFramebufferAttachmentParameteriv, "glGetFramebufferAttachmentParameteriv");

		FetchProcAddress(glGetRenderbufferParameteriv, "glGetRenderbufferParameteriv");

		FetchProcAddress(glIsFramebuffer, "glIsFramebuffer");

		FetchProcAddress(glIsRenderbuffer, "glIsRenderbuffer");

		FetchProcAddress(glRenderbufferStorage, "glRenderbufferStorage");

		FetchProcAddress(glRenderbufferStorageMultisample, "glRenderbufferStorageMultisample");

		FetchProcAddress(ARB_framebuffer_object, "ARB_framebuffer_object");


		//framebuffer sRGB
		FetchProcAddress(ARB_framebuffer_sRGB, "ARB_framebuffer_sRGB");


		//geometry shader4
		FetchProcAddress(glFramebufferTextureARB, "glFramebufferTextureARB");

		FetchProcAddress(glFramebufferTextureFaceARB, "glFramebufferTextureFaceARB");

		FetchProcAddress(glFramebufferTextureLayerARB, "glFramebufferTextureLayerARB");

		FetchProcAddress(glProgramParameteriARB, "glProgramParameteriARB");

		FetchProcAddress(ARB_geometry_shader4, "ARB_geometry_shader4");


		//get program binary
		FetchProcAddress(glGetProgramBinary, "glGetProgramBinary");

		FetchProcAddress(glProgramBinary, "glProgramBinary");

		FetchProcAddress(glProgramParameteri, "glProgramParameteri");

		FetchProcAddress(ARB_get_program_binary, "ARB_get_program_binary");


		//get texture sub image
		FetchProcAddress(glGetCompressedTextureSubImage, "glGetCompressedTextureSubImage");

		FetchProcAddress(glGetTextureSubImage, "glGetTextureSubImage");

		FetchProcAddress(ARB_get_texture_sub_image, "ARB_get_texture_sub_image");


		//gl spirv
		FetchProcAddress(glSpecializeShaderARB, "glSpecializeShaderARB");

		FetchProcAddress(ARB_gl_spirv, "ARB_gl_spirv");


		//gpu shader5
		FetchProcAddress(ARB_gpu_shader5, "ARB_gpu_shader5");


		//gpu shader fp64
		FetchProcAddress(glGetUniformdv, "glGetUniformdv");

		FetchProcAddress(glUniform1d, "glUniform1d");

		FetchProcAddress(glUniform1dv, "glUniform1dv");

		FetchProcAddress(glUniform2d, "glUniform2d");

		FetchProcAddress(glUniform2dv, "glUniform2dv");

		FetchProcAddress(glUniform3d, "glUniform3d");

		FetchProcAddress(glUniform3dv, "glUniform3dv");

		FetchProcAddress(glUniform4d, "glUniform4d");

		FetchProcAddress(glUniform4dv, "glUniform4dv");

		FetchProcAddress(glUniformMatrix2dv, "glUniformMatrix2dv");

		FetchProcAddress(glUniformMatrix2x3dv, "glUniformMatrix2x3dv");

		FetchProcAddress(glUniformMatrix2x4dv, "glUniformMatrix2x4dv");

		FetchProcAddress(glUniformMatrix3dv, "glUniformMatrix3dv");

		FetchProcAddress(glUniformMatrix3x2dv, "glUniformMatrix3x2dv");

		FetchProcAddress(glUniformMatrix3x4dv, "glUniformMatrix3x4dv");

		FetchProcAddress(glUniformMatrix4dv, "glUniformMatrix4dv");

		FetchProcAddress(glUniformMatrix4x2dv, "glUniformMatrix4x2dv");

		FetchProcAddress(glUniformMatrix4x3dv, "glUniformMatrix4x3dv");

		FetchProcAddress(ARB_gpu_shader_fp64, "ARB_gpu_shader_fp64");


		//gpu shader int64
		FetchProcAddress(glGetUniformi64vARB, "glGetUniformi64vARB");

		FetchProcAddress(glGetUniformui64vARB, "glGetUniformui64vARB");

		FetchProcAddress(glGetnUniformi64vARB, "glGetnUniformi64vARB");

		FetchProcAddress(glGetnUniformui64vARB, "glGetnUniformui64vARB");

		FetchProcAddress(glProgramUniform1i64ARB, "glProgramUniform1i64ARB");

		FetchProcAddress(glProgramUniform1i64vARB, "glProgramUniform1i64vARB");

		FetchProcAddress(glProgramUniform1ui64ARB, "glProgramUniform1ui64ARB");

		FetchProcAddress(glProgramUniform1ui64vARB, "glProgramUniform1ui64vARB");

		FetchProcAddress(glProgramUniform2i64ARB, "glProgramUniform2i64ARB");

		FetchProcAddress(glProgramUniform2i64vARB, "glProgramUniform2i64vARB");

		FetchProcAddress(glProgramUniform2ui64ARB, "glProgramUniform2ui64ARB");

		FetchProcAddress(glProgramUniform2ui64vARB, "glProgramUniform2ui64vARB");

		FetchProcAddress(glProgramUniform3i64ARB, "glProgramUniform3i64ARB");

		FetchProcAddress(glProgramUniform3i64vARB, "glProgramUniform3i64vARB");

		FetchProcAddress(glProgramUniform3ui64ARB, "glProgramUniform3ui64ARB");

		FetchProcAddress(glProgramUniform3ui64vARB, "glProgramUniform3ui64vARB");

		FetchProcAddress(glProgramUniform4i64ARB, "glProgramUniform4i64ARB");

		FetchProcAddress(glProgramUniform4i64vARB, "glProgramUniform4i64vARB");

		FetchProcAddress(glProgramUniform4ui64ARB, "glProgramUniform4ui64ARB");

		FetchProcAddress(glProgramUniform4ui64vARB, "glProgramUniform4ui64vARB");

		FetchProcAddress(glUniform1i64ARB, "glUniform1i64ARB");

		FetchProcAddress(glUniform1i64vARB, "glUniform1i64vARB");

		FetchProcAddress(glUniform1ui64ARB, "glUniform1ui64ARB");

		FetchProcAddress(glUniform1ui64vARB, "glUniform1ui64vARB");

		FetchProcAddress(glUniform2i64ARB, "glUniform2i64ARB");

		FetchProcAddress(glUniform2i64vARB, "glUniform2i64vARB");

		FetchProcAddress(glUniform2ui64ARB, "glUniform2ui64ARB");

		FetchProcAddress(glUniform2ui64vARB, "glUniform2ui64vARB");

		FetchProcAddress(glUniform3i64ARB, "glUniform3i64ARB");

		FetchProcAddress(glUniform3i64vARB, "glUniform3i64vARB");

		FetchProcAddress(glUniform3ui64ARB, "glUniform3ui64ARB");

		FetchProcAddress(glUniform3ui64vARB, "glUniform3ui64vARB");

		FetchProcAddress(glUniform4i64ARB, "glUniform4i64ARB");

		FetchProcAddress(glUniform4i64vARB, "glUniform4i64vARB");

		FetchProcAddress(glUniform4ui64ARB, "glUniform4ui64ARB");

		FetchProcAddress(glUniform4ui64vARB, "glUniform4ui64vARB");

		FetchProcAddress(ARB_gpu_shader_int64, "ARB_gpu_shader_int64");


		//half float pixel
		FetchProcAddress(ARB_half_float_pixel, "ARB_half_float_pixel");


		//half float vertex
		FetchProcAddress(ARB_half_float_vertex, "ARB_half_float_vertex");


		//imaging
		FetchProcAddress(glColorSubTable, "glColorSubTable");

		FetchProcAddress(glColorTable, "glColorTable");

		FetchProcAddress(glColorTableParameterfv, "glColorTableParameterfv");

		FetchProcAddress(glColorTableParameteriv, "glColorTableParameteriv");

		FetchProcAddress(glConvolutionFilter1D, "glConvolutionFilter1D");

		FetchProcAddress(glConvolutionFilter2D, "glConvolutionFilter2D");

		FetchProcAddress(glConvolutionParameterf, "glConvolutionParameterf");

		FetchProcAddress(glConvolutionParameterfv, "glConvolutionParameterfv");

		FetchProcAddress(glConvolutionParameteri, "glConvolutionParameteri");

		FetchProcAddress(glConvolutionParameteriv, "glConvolutionParameteriv");

		FetchProcAddress(glCopyColorSubTable, "glCopyColorSubTable");

		FetchProcAddress(glCopyColorTable, "glCopyColorTable");

		FetchProcAddress(glCopyConvolutionFilter1D, "glCopyConvolutionFilter1D");

		FetchProcAddress(glCopyConvolutionFilter2D, "glCopyConvolutionFilter2D");

		FetchProcAddress(glGetColorTable, "glGetColorTable");

		FetchProcAddress(glGetColorTableParameterfv, "glGetColorTableParameterfv");

		FetchProcAddress(glGetColorTableParameteriv, "glGetColorTableParameteriv");

		FetchProcAddress(glGetConvolutionFilter, "glGetConvolutionFilter");

		FetchProcAddress(glGetConvolutionParameterfv, "glGetConvolutionParameterfv");

		FetchProcAddress(glGetConvolutionParameteriv, "glGetConvolutionParameteriv");

		FetchProcAddress(glGetHistogram, "glGetHistogram");

		FetchProcAddress(glGetHistogramParameterfv, "glGetHistogramParameterfv");

		FetchProcAddress(glGetHistogramParameteriv, "glGetHistogramParameteriv");

		FetchProcAddress(glGetMinmax, "glGetMinmax");

		FetchProcAddress(glGetMinmaxParameterfv, "glGetMinmaxParameterfv");

		FetchProcAddress(glGetMinmaxParameteriv, "glGetMinmaxParameteriv");

		FetchProcAddress(glGetSeparableFilter, "glGetSeparableFilter");

		FetchProcAddress(glHistogram, "glHistogram");

		FetchProcAddress(glMinmax, "glMinmax");

		FetchProcAddress(glResetHistogram, "glResetHistogram");

		FetchProcAddress(glResetMinmax, "glResetMinmax");

		FetchProcAddress(glSeparableFilter2D, "glSeparableFilter2D");

		FetchProcAddress(ARB_imaging, "ARB_imaging");


		//indirect parameters
		FetchProcAddress(glMultiDrawArraysIndirectCountARB, "glMultiDrawArraysIndirectCountARB");

		FetchProcAddress(glMultiDrawElementsIndirectCountARB, "glMultiDrawElementsIndirectCountARB");

		FetchProcAddress(ARB_indirect_parameters, "ARB_indirect_parameters");


		//instanced arrays
		FetchProcAddress(glDrawArraysInstancedARB, "glDrawArraysInstancedARB");

		FetchProcAddress(glDrawElementsInstancedARB, "glDrawElementsInstancedARB");

		FetchProcAddress(glVertexAttribDivisorARB, "glVertexAttribDivisorARB");

		FetchProcAddress(ARB_instanced_arrays, "ARB_instanced_arrays");


		//internalformat query
		FetchProcAddress(glGetInternalformativ, "glGetInternalformativ");

		FetchProcAddress(ARB_internalformat_query, "ARB_internalformat_query");


		//internalformat query2
		FetchProcAddress(glGetInternalformati64v, "glGetInternalformati64v");

		FetchProcAddress(ARB_internalformat_query2, "ARB_internalformat_query2");


		//invalidate subdata
		FetchProcAddress(glInvalidateBufferData, "glInvalidateBufferData");

		FetchProcAddress(glInvalidateBufferSubData, "glInvalidateBufferSubData");

		FetchProcAddress(glInvalidateFramebuffer, "glInvalidateFramebuffer");

		FetchProcAddress(glInvalidateSubFramebuffer, "glInvalidateSubFramebuffer");

		FetchProcAddress(glInvalidateTexImage, "glInvalidateTexImage");

		FetchProcAddress(glInvalidateTexSubImage, "glInvalidateTexSubImage");

		FetchProcAddress(ARB_invalidate_subdata, "ARB_invalidate_subdata");


		//map buffer alignment
		FetchProcAddress(ARB_map_buffer_alignment, "ARB_map_buffer_alignment");


		//map buffer range
		FetchProcAddress(glFlushMappedBufferRange, "glFlushMappedBufferRange");

		FetchProcAddress(glMapBufferRange, "glMapBufferRange");

		FetchProcAddress(ARB_map_buffer_range, "ARB_map_buffer_range");


		//matrix palette
		FetchProcAddress(glCurrentPaletteMatrixARB, "glCurrentPaletteMatrixARB");

		FetchProcAddress(glMatrixIndexPointerARB, "glMatrixIndexPointerARB");

		FetchProcAddress(glMatrixIndexubvARB, "glMatrixIndexubvARB");

		FetchProcAddress(glMatrixIndexuivARB, "glMatrixIndexuivARB");

		FetchProcAddress(glMatrixIndexusvARB, "glMatrixIndexusvARB");

		FetchProcAddress(ARB_matrix_palette, "ARB_matrix_palette");


		//multi bind
		FetchProcAddress(glBindBuffersBase, "glBindBuffersBase");

		FetchProcAddress(glBindBuffersRange, "glBindBuffersRange");

		FetchProcAddress(glBindImageTextures, "glBindImageTextures");

		FetchProcAddress(glBindSamplers, "glBindSamplers");

		FetchProcAddress(glBindTextures, "glBindTextures");

		FetchProcAddress(glBindVertexBuffers, "glBindVertexBuffers");

		FetchProcAddress(ARB_multi_bind, "ARB_multi_bind");


		//multi draw indirect
		FetchProcAddress(glMultiDrawArraysIndirect, "glMultiDrawArraysIndirect");

		FetchProcAddress(glMultiDrawElementsIndirect, "glMultiDrawElementsIndirect");

		FetchProcAddress(ARB_multi_draw_indirect, "ARB_multi_draw_indirect");


		//multisample
		FetchProcAddress(glSampleCoverageARB, "glSampleCoverageARB");

		FetchProcAddress(ARB_multisample, "ARB_multisample");


		//multitexture
		FetchProcAddress(glActiveTextureARB, "glActiveTextureARB");

		FetchProcAddress(glClientActiveTextureARB, "glClientActiveTextureARB");

		FetchProcAddress(glMultiTexCoord1dARB, "glMultiTexCoord1dARB");

		FetchProcAddress(glMultiTexCoord1dvARB, "glMultiTexCoord1dvARB");

		FetchProcAddress(glMultiTexCoord1fARB, "glMultiTexCoord1fARB");

		FetchProcAddress(glMultiTexCoord1fvARB, "glMultiTexCoord1fvARB");

		FetchProcAddress(glMultiTexCoord1iARB, "glMultiTexCoord1iARB");

		FetchProcAddress(glMultiTexCoord1ivARB, "glMultiTexCoord1ivARB");

		FetchProcAddress(glMultiTexCoord1sARB, "glMultiTexCoord1sARB");

		FetchProcAddress(glMultiTexCoord1svARB, "glMultiTexCoord1svARB");

		FetchProcAddress(glMultiTexCoord2dARB, "glMultiTexCoord2dARB");

		FetchProcAddress(glMultiTexCoord2dvARB, "glMultiTexCoord2dvARB");

		FetchProcAddress(glMultiTexCoord2fARB, "glMultiTexCoord2fARB");

		FetchProcAddress(glMultiTexCoord2fvARB, "glMultiTexCoord2fvARB");

		FetchProcAddress(glMultiTexCoord2iARB, "glMultiTexCoord2iARB");

		FetchProcAddress(glMultiTexCoord2ivARB, "glMultiTexCoord2ivARB");

		FetchProcAddress(glMultiTexCoord2sARB, "glMultiTexCoord2sARB");

		FetchProcAddress(glMultiTexCoord2svARB, "glMultiTexCoord2svARB");

		FetchProcAddress(glMultiTexCoord3dARB, "glMultiTexCoord3dARB");

		FetchProcAddress(glMultiTexCoord3dvARB, "glMultiTexCoord3dvARB");

		FetchProcAddress(glMultiTexCoord3fARB, "glMultiTexCoord3fARB");

		FetchProcAddress(glMultiTexCoord3fvARB, "glMultiTexCoord3fvARB");

		FetchProcAddress(glMultiTexCoord3iARB, "glMultiTexCoord3iARB");

		FetchProcAddress(glMultiTexCoord3ivARB, "glMultiTexCoord3ivARB");

		FetchProcAddress(glMultiTexCoord3sARB, "glMultiTexCoord3sARB");

		FetchProcAddress(glMultiTexCoord3svARB, "glMultiTexCoord3svARB");

		FetchProcAddress(glMultiTexCoord4dARB, "glMultiTexCoord4dARB");

		FetchProcAddress(glMultiTexCoord4dvARB, "glMultiTexCoord4dvARB");

		FetchProcAddress(glMultiTexCoord4fARB, "glMultiTexCoord4fARB");

		FetchProcAddress(glMultiTexCoord4fvARB, "glMultiTexCoord4fvARB");

		FetchProcAddress(glMultiTexCoord4iARB, "glMultiTexCoord4iARB");

		FetchProcAddress(glMultiTexCoord4ivARB, "glMultiTexCoord4ivARB");

		FetchProcAddress(glMultiTexCoord4sARB, "glMultiTexCoord4sARB");

		FetchProcAddress(glMultiTexCoord4svARB, "glMultiTexCoord4svARB");

		FetchProcAddress(ARB_multitexture, "ARB_multitexture");


		//occlusion query
		FetchProcAddress(glBeginQueryARB, "glBeginQueryARB");

		FetchProcAddress(glDeleteQueriesARB, "glDeleteQueriesARB");

		FetchProcAddress(glEndQueryARB, "glEndQueryARB");

		FetchProcAddress(glGenQueriesARB, "glGenQueriesARB");

		FetchProcAddress(glGetQueryObjectivARB, "glGetQueryObjectivARB");

		FetchProcAddress(glGetQueryObjectuivARB, "glGetQueryObjectuivARB");

		FetchProcAddress(glGetQueryivARB, "glGetQueryivARB");

		FetchProcAddress(glIsQueryARB, "glIsQueryARB");

		FetchProcAddress(ARB_occlusion_query, "ARB_occlusion_query");


		//occlusion query2
		FetchProcAddress(ARB_occlusion_query2, "ARB_occlusion_query2");


		//parallel shader compile
		FetchProcAddress(glMaxShaderCompilerThreadsARB, "glMaxShaderCompilerThreadsARB");

		FetchProcAddress(ARB_parallel_shader_compile, "ARB_parallel_shader_compile");


		//pipeline statistics query
		FetchProcAddress(ARB_pipeline_statistics_query, "ARB_pipeline_statistics_query");


		//pixel buffer object
		FetchProcAddress(ARB_pixel_buffer_object, "ARB_pixel_buffer_object");


		//point parameters
		FetchProcAddress(glPointParameterfARB, "glPointParameterfARB");

		FetchProcAddress(glPointParameterfvARB, "glPointParameterfvARB");

		FetchProcAddress(ARB_point_parameters, "ARB_point_parameters");


		//point sprite
		FetchProcAddress(ARB_point_sprite, "ARB_point_sprite");


		//polygon offset clamp
		FetchProcAddress(glPolygonOffsetClamp, "glPolygonOffsetClamp");

		FetchProcAddress(ARB_polygon_offset_clamp, "ARB_polygon_offset_clamp");


		//post depth coverage
		FetchProcAddress(ARB_post_depth_coverage, "ARB_post_depth_coverage");


		//program interface query
		FetchProcAddress(glGetProgramInterfaceiv, "glGetProgramInterfaceiv");

		FetchProcAddress(glGetProgramResourceIndex, "glGetProgramResourceIndex");

		FetchProcAddress(glGetProgramResourceLocation, "glGetProgramResourceLocation");

		FetchProcAddress(glGetProgramResourceLocationIndex, "glGetProgramResourceLocationIndex");

		FetchProcAddress(glGetProgramResourceName, "glGetProgramResourceName");

		FetchProcAddress(glGetProgramResourceiv, "glGetProgramResourceiv");

		FetchProcAddress(ARB_program_interface_query, "ARB_program_interface_query");


		//provoking vertex
		FetchProcAddress(glProvokingVertex, "glProvokingVertex");

		FetchProcAddress(ARB_provoking_vertex, "ARB_provoking_vertex");


		// query buffer object
		FetchProcAddress(ARB_query_buffer_object, "ARB_query_buffer_object");


		//robust buffer access behavior
		FetchProcAddress(ARB_robust_buffer_access_behavior, "ARB_robust_buffer_access_behavior");


		//robustness
		FetchProcAddress(glGetGraphicsResetStatusARB, "glGetGraphicsResetStatusARB");

		FetchProcAddress(glGetnColorTableARB, "glGetnColorTableARB");

		FetchProcAddress(glGetnCompressedTexImageARB, "glGetnCompressedTexImageARB");

		FetchProcAddress(glGetnConvolutionFilterARB, "glGetnConvolutionFilterARB");

		FetchProcAddress(glGetnHistogramARB, "glGetnHistogramARB");

		FetchProcAddress(glGetnMapdvARB, "glGetnMapdvARB");

		FetchProcAddress(glGetnMapfvARB, "glGetnMapfvARB");

		FetchProcAddress(glGetnMapivARB, "glGetnMapivARB");

		FetchProcAddress(glGetnMinmaxARB, "glGetnMinmaxARB");

		FetchProcAddress(glGetnPixelMapfvARB, "glGetnPixelMapfvARB");

		FetchProcAddress(glGetnPixelMapuivARB, "glGetnPixelMapuivARB");

		FetchProcAddress(glGetnPixelMapusvARB, "glGetnPixelMapusvARB");

		FetchProcAddress(glGetnPolygonStippleARB, "glGetnPolygonStippleARB");

		FetchProcAddress(glGetnSeparableFilterARB, "glGetnSeparableFilterARB");

		FetchProcAddress(glGetnTexImageARB, "glGetnTexImageARB");

		FetchProcAddress(glGetnUniformdvARB, "glGetnUniformdvARB");

		FetchProcAddress(glGetnUniformfvARB, "glGetnUniformfvARB");

		FetchProcAddress(glGetnUniformivARB, "glGetnUniformivARB");

		FetchProcAddress(glGetnUniformuivARB, "glGetnUniformuivARB");

		FetchProcAddress(glReadnPixelsARB, "glReadnPixelsARB");

		FetchProcAddress(ARB_robustness, "ARB_robustness");


		//robustness application isolation
		FetchProcAddress(ARB_robustness_application_isolation, "ARB_robustness_application_isolation");


		//robustness share group isolation
		FetchProcAddress(ARB_robustness_share_group_isolation, "ARB_robustness_share_group_isolation");


		//sample locations
		FetchProcAddress(glFramebufferSampleLocationsfvARB, "glFramebufferSampleLocationsfvARB");

		FetchProcAddress(glNamedFramebufferSampleLocationsfvARB, "glNamedFramebufferSampleLocationsfvARB");

		FetchProcAddress(ARB_sample_locations, "ARB_sample_locations");


		//sample shading
		FetchProcAddress(glMinSampleShadingARB, "glMinSampleShadingARB");

		FetchProcAddress(ARB_sample_shading, "ARB_sample_shading");


		//sampler objects
		FetchProcAddress(glBindSampler, "glBindSampler");

		FetchProcAddress(glDeleteSamplers, "glDeleteSamplers");

		FetchProcAddress(glGenSamplers, "glGenSamplers");

		FetchProcAddress(glGetSamplerParameterIiv, "glGetSamplerParameterIiv");

		FetchProcAddress(glGetSamplerParameterIuiv, "glGetSamplerParameterIuiv");

		FetchProcAddress(glGetSamplerParameterfv, "glGetSamplerParameterfv");

		FetchProcAddress(glGetSamplerParameteriv, "glGetSamplerParameteriv");

		FetchProcAddress(glIsSampler, "glIsSampler");

		FetchProcAddress(glSamplerParameterIiv, "glSamplerParameterIiv");

		FetchProcAddress(glSamplerParameterIuiv, "glSamplerParameterIuiv");

		FetchProcAddress(glSamplerParameterf, "glSamplerParameterf");

		FetchProcAddress(glSamplerParameterfv, "glSamplerParameterfv");

		FetchProcAddress(glSamplerParameteri, "glSamplerParameteri");

		FetchProcAddress(glSamplerParameteriv, "glSamplerParameteriv");

		FetchProcAddress(ARB_sampler_objects, "ARB_sampler_objects");


		//seamless cube map
		FetchProcAddress(ARB_seamless_cube_map, "ARB_seamless_cube_map");


		//seamless cubemap per texture
		FetchProcAddress(ARB_seamless_cubemap_per_texture, "ARB_seamless_cubemap_per_texture");


		//separate shader objects
		FetchProcAddress(glActiveShaderProgram, "glActiveShaderProgram");

		FetchProcAddress(glBindProgramPipeline, "glBindProgramPipeline");

		FetchProcAddress(glCreateShaderProgramv, "glCreateShaderProgramv");

		FetchProcAddress(glDeleteProgramPipelines, "glDeleteProgramPipelines");

		FetchProcAddress(glGenProgramPipelines, "glGenProgramPipelines");

		FetchProcAddress(glGetProgramPipelineInfoLog, "glGetProgramPipelineInfoLog");

		FetchProcAddress(glGetProgramPipelineiv, "glGetProgramPipelineiv");

		FetchProcAddress(glIsProgramPipeline, "glIsProgramPipeline");

		FetchProcAddress(glProgramUniform1d, "glProgramUniform1d");

		FetchProcAddress(glProgramUniform1dv, "glProgramUniform1dv");

		FetchProcAddress(glProgramUniform1f, "glProgramUniform1f");

		FetchProcAddress(glProgramUniform1fv, "glProgramUniform1fv");

		FetchProcAddress(glProgramUniform1i, "glProgramUniform1i");

		FetchProcAddress(glProgramUniform1iv, "glProgramUniform1iv");

		FetchProcAddress(glProgramUniform1ui, "glProgramUniform1ui");

		FetchProcAddress(glProgramUniform1uiv, "glProgramUniform1uiv");

		FetchProcAddress(glProgramUniform2d, "glProgramUniform2d");

		FetchProcAddress(glProgramUniform2dv, "glProgramUniform2dv");

		FetchProcAddress(glProgramUniform2f, "glProgramUniform2f");

		FetchProcAddress(glProgramUniform2fv, "glProgramUniform2fv");

		FetchProcAddress(glProgramUniform2i, "glProgramUniform2i");

		FetchProcAddress(glProgramUniform2iv, "glProgramUniform2iv");

		FetchProcAddress(glProgramUniform2ui, "glProgramUniform2ui");

		FetchProcAddress(glProgramUniform2uiv, "glProgramUniform2uiv");

		FetchProcAddress(glProgramUniform3d, "glProgramUniform3d");

		FetchProcAddress(glProgramUniform3dv, "glProgramUniform3dv");

		FetchProcAddress(glProgramUniform3f, "glProgramUniform3f");

		FetchProcAddress(glProgramUniform3fv, "glProgramUniform3fv");

		FetchProcAddress(glProgramUniform3i, "glProgramUniform3i");

		FetchProcAddress(glProgramUniform3iv, "glProgramUniform3iv");

		FetchProcAddress(glProgramUniform3ui, "glProgramUniform3ui");

		FetchProcAddress(glProgramUniform3uiv, "glProgramUniform3uiv");

		FetchProcAddress(glProgramUniform4d, "glProgramUniform4d");

		FetchProcAddress(glProgramUniform4dv, "glProgramUniform4dv");

		FetchProcAddress(glProgramUniform4f, "glProgramUniform4f");

		FetchProcAddress(glProgramUniform4fv, "glProgramUniform4fv");

		FetchProcAddress(glProgramUniform4i, "glProgramUniform4i");

		FetchProcAddress(glProgramUniform4iv, "glProgramUniform4iv");

		FetchProcAddress(glProgramUniform4ui, "glProgramUniform4ui");

		FetchProcAddress(glProgramUniform4uiv, "glProgramUniform4uiv");

		FetchProcAddress(glProgramUniformMatrix2dv, "glProgramUniformMatrix2dv");

		FetchProcAddress(glProgramUniformMatrix2fv, "glProgramUniformMatrix2fv");

		FetchProcAddress(glProgramUniformMatrix2x3dv, "glProgramUniformMatrix2x3dv");

		FetchProcAddress(glProgramUniformMatrix2x3fv, "glProgramUniformMatrix2x3fv");

		FetchProcAddress(glProgramUniformMatrix2x4dv, "glProgramUniformMatrix2x4dv");

		FetchProcAddress(glProgramUniformMatrix2x4fv, "glProgramUniformMatrix2x4fv");

		FetchProcAddress(glProgramUniformMatrix3dv, "glProgramUniformMatrix3dv");

		FetchProcAddress(glProgramUniformMatrix3fv, "glProgramUniformMatrix3fv");

		FetchProcAddress(glProgramUniformMatrix3x2dv, "glProgramUniformMatrix3x2dv");

		FetchProcAddress(glProgramUniformMatrix3x2fv, "glProgramUniformMatrix3x2fv");

		FetchProcAddress(glProgramUniformMatrix3x4dv, "glProgramUniformMatrix3x4dv");

		FetchProcAddress(glProgramUniformMatrix3x4fv, "glProgramUniformMatrix3x4fv");

		FetchProcAddress(glProgramUniformMatrix4dv, "glProgramUniformMatrix4dv");

		FetchProcAddress(glProgramUniformMatrix4fv, "glProgramUniformMatrix4fv");

		FetchProcAddress(glProgramUniformMatrix4x2dv, "glProgramUniformMatrix4x2dv");

		FetchProcAddress(glProgramUniformMatrix4x2fv, "glProgramUniformMatrix4x2fv");

		FetchProcAddress(glProgramUniformMatrix4x3dv, "glProgramUniformMatrix4x3dv");

		FetchProcAddress(glProgramUniformMatrix4x3fv, "glProgramUniformMatrix4x3fv");

		FetchProcAddress(glUseProgramStages, "glUseProgramStages");

		FetchProcAddress(glValidateProgramPipeline, "glValidateProgramPipeline");

		FetchProcAddress(ARB_separate_shader_objects, "ARB_separate_shader_objects");


		//shader atomic counter ops
		FetchProcAddress(ARB_shader_atomic_counter_ops, "ARB_shader_atomic_counter_ops");


		//shader atomic counters
		FetchProcAddress(glGetActiveAtomicCounterBufferiv, "glGetActiveAtomicCounterBufferiv");

		FetchProcAddress(ARB_shader_atomic_counters, "ARB_shader_atomic_counters");


		//shader ballot
		FetchProcAddress(ARB_shader_ballot, "ARB_shader_ballot");


		//shader bit encoding
		FetchProcAddress(ARB_shader_bit_encoding, "ARB_shader_bit_encoding");


		//shader clock
		FetchProcAddress(ARB_shader_clock, "ARB_shader_clock");


		//shader draw parameters
		FetchProcAddress(ARB_shader_draw_parameters, "ARB_shader_draw_parameters");


		//shader group vote
		FetchProcAddress(ARB_shader_group_vote, "ARB_shader_group_vote");


		//shader image load store
		FetchProcAddress(glBindImageTexture, "glBindImageTexture");

		FetchProcAddress(glMemoryBarrier, "glMemoryBarrier");

		FetchProcAddress(ARB_shader_image_load_store, "ARB_shader_image_load_store");


		//shader image size
		FetchProcAddress(ARB_shader_image_size, "ARB_shader_image_size");


		//shader objects
		FetchProcAddress(glAttachObjectARB, "glAttachObjectARB");

		FetchProcAddress(glCompileShaderARB, "glCompileShaderARB");

		FetchProcAddress(glCreateProgramObjectARB, "glCreateProgramObjectARB");

		FetchProcAddress(glCreateShaderObjectARB, "glCreateShaderObjectARB");

		FetchProcAddress(glDeleteObjectARB, "glDeleteObjectARB");

		FetchProcAddress(glDetachObjectARB, "glDetachObjectARB");

		FetchProcAddress(glGetActiveUniformARB, "glGetActiveUniformARB");

		FetchProcAddress(glGetAttachedObjectsARB, "glGetAttachedObjectsARB");

		FetchProcAddress(glGetHandleARB, "glGetHandleARB");

		FetchProcAddress(glGetInfoLogARB, "glGetInfoLogARB");

		FetchProcAddress(glGetObjectParameterfvARB, "glGetObjectParameterfvARB");

		FetchProcAddress(glGetObjectParameterivARB, "glGetObjectParameterivARB");

		FetchProcAddress(glGetShaderSourceARB, "glGetShaderSourceARB");

		FetchProcAddress(glGetUniformLocationARB, "glGetUniformLocationARB");

		FetchProcAddress(glGetUniformfvARB, "glGetUniformfvARB");

		FetchProcAddress(glGetUniformivARB, "glGetUniformivARB");

		FetchProcAddress(glLinkProgramARB, "glLinkProgramARB");

		FetchProcAddress(glShaderSourceARB, "glShaderSourceARB");

		FetchProcAddress(glUniform1fARB, "glUniform1fARB");

		FetchProcAddress(glUniform1fvARB, "glUniform1fvARB");

		FetchProcAddress(glUniform1iARB, "glUniform1iARB");

		FetchProcAddress(glUniform1ivARB, "glUniform1ivARB");

		FetchProcAddress(glUniform2fARB, "glUniform2fARB");

		FetchProcAddress(glUniform2fvARB, "glUniform2fvARB");

		FetchProcAddress(glUniform2iARB, "glUniform2iARB");

		FetchProcAddress(glUniform2ivARB, "glUniform2ivARB");

		FetchProcAddress(glUniform3fARB, "glUniform3fARB");

		FetchProcAddress(glUniform3fvARB, "glUniform3fvARB");

		FetchProcAddress(glUniform3iARB, "glUniform3iARB");

		FetchProcAddress(glUniform3ivARB, "glUniform3ivARB");

		FetchProcAddress(glUniform4fARB, "glUniform4fARB");

		FetchProcAddress(glUniform4fvARB, "glUniform4fvARB");

		FetchProcAddress(glUniform4iARB, "glUniform4iARB");

		FetchProcAddress(glUniform4ivARB, "glUniform4ivARB");

		FetchProcAddress(glUniformMatrix2fvARB, "glUniformMatrix2fvARB");

		FetchProcAddress(glUniformMatrix3fvARB, "glUniformMatrix3fvARB");

		FetchProcAddress(glUniformMatrix4fvARB, "glUniformMatrix4fvARB");

		FetchProcAddress(glUseProgramObjectARB, "glUseProgramObjectARB");

		FetchProcAddress(glValidateProgramARB, "glValidateProgramARB");

		FetchProcAddress(ARB_shader_objects, "ARB_shader_objects");


		//shader precision
		FetchProcAddress(ARB_shader_precision, "ARB_shader_precision");


		//shader stencil export
		FetchProcAddress(ARB_shader_stencil_export, "ARB_shader_stencil_export");


		//shader storage buffer object
		FetchProcAddress(glShaderStorageBlockBinding, "glShaderStorageBlockBinding");

		FetchProcAddress(ARB_shader_storage_buffer_object, "ARB_shader_storage_buffer_object");


		//shader subroutine
		FetchProcAddress(glGetActiveSubroutineName, "glGetActiveSubroutineName");

		FetchProcAddress(glGetActiveSubroutineUniformName, "glGetActiveSubroutineUniformName");

		FetchProcAddress(glGetActiveSubroutineUniformiv, "glGetActiveSubroutineUniformiv");

		FetchProcAddress(glGetProgramStageiv, "glGetProgramStageiv");

		FetchProcAddress(glGetSubroutineIndex, "glGetSubroutineIndex");

		FetchProcAddress(glGetSubroutineUniformLocation, "glGetSubroutineUniformLocation");

		FetchProcAddress(glGetUniformSubroutineuiv, "glGetUniformSubroutineuiv");

		FetchProcAddress(glUniformSubroutinesuiv, "glUniformSubroutinesuiv");

		FetchProcAddress(ARB_shader_subroutine, "ARB_shader_subroutine");


		//shader texture image samples
		FetchProcAddress(ARB_shader_texture_image_samples, "ARB_shader_texture_image_samples");


		//shader texture lod
		FetchProcAddress(ARB_shader_texture_lod, "ARB_shader_texture_lod");


		//shader viewport layer array
		FetchProcAddress(ARB_shader_viewport_layer_array, "ARB_shader_viewport_layer_array");


		//shading language 100
		FetchProcAddress(ARB_shading_language_100, "ARB_shading_language_100");


		//shading language 420pack
		FetchProcAddress(ARB_shading_language_420pack, "ARB_shading_language_420pack");


		//shading language include
		FetchProcAddress(glCompileShaderIncludeARB, "glCompileShaderIncludeARB");

		FetchProcAddress(glDeleteNamedStringARB, "glDeleteNamedStringARB");

		FetchProcAddress(glGetNamedStringARB, "glGetNamedStringARB");

		FetchProcAddress(glGetNamedStringivARB, "glGetNamedStringivARB");

		FetchProcAddress(glIsNamedStringARB, "glIsNamedStringARB");

		FetchProcAddress(glNamedStringARB, "glNamedStringARB");

		FetchProcAddress(ARB_shading_language_include, "ARB_shading_language_include");


		//shading language packing
		FetchProcAddress(ARB_shading_language_packing, "ARB_shading_language_packing");


		//shadow
		FetchProcAddress(ARB_shadow, "ARB_shadow");


		//shadow ambient
		FetchProcAddress(ARB_shadow_ambient, "ARB_shadow_ambient");


		//sparse buffer
		FetchProcAddress(glBufferPageCommitmentARB, "glBufferPageCommitmentARB");

		FetchProcAddress(ARB_sparse_buffer, "ARB_sparse_buffer");


		//sparse texture
		FetchProcAddress(glTexPageCommitmentARB, "glTexPageCommitmentARB");

		FetchProcAddress(ARB_sparse_texture, "ARB_sparse_texture");


		//sparse texture2
		FetchProcAddress(ARB_sparse_texture2, "ARB_sparse_texture2");


		//sparse texture clamp
		FetchProcAddress(ARB_sparse_texture_clamp, "ARB_sparse_texture_clamp");


		//spirv extensions
		FetchProcAddress(ARB_spirv_extensions, "ARB_spirv_extensions");


		//stencil texturing
		FetchProcAddress(ARB_stencil_texturing, "ARB_stencil_texturing");


		//sync
		FetchProcAddress(glClientWaitSync, "glClientWaitSync");

		FetchProcAddress(glDeleteSync, "glDeleteSync");

		FetchProcAddress(glFenceSync, "glFenceSync");

		FetchProcAddress(glGetInteger64v, "glGetInteger64v");

		FetchProcAddress(glGetSynciv, "glGetSynciv");

		FetchProcAddress(glIsSync, "glIsSync");

		FetchProcAddress(glWaitSync, "glWaitSync");

		FetchProcAddress(ARB_sync, "ARB_sync");


		//tessellation shader
		FetchProcAddress(glPatchParameterfv, "glPatchParameterfv");

		FetchProcAddress(glPatchParameteri, "glPatchParameteri");

		FetchProcAddress(ARB_tessellation_shader, "ARB_tessellation_shader");


		//texture barrier
		FetchProcAddress(glTextureBarrier, "glTextureBarrier");

		FetchProcAddress(ARB_texture_barrier, "ARB_texture_barrier");


		//texture border clamp
		FetchProcAddress(ARB_texture_border_clamp, "ARB_texture_border_clamp");


		//texture buffer object
		FetchProcAddress(glTexBufferARB, "glTexBufferARB");

		FetchProcAddress(ARB_texture_buffer_object, "ARB_texture_buffer_object");


		// texture buffer object rgb32
		FetchProcAddress(ARB_texture_buffer_object_rgb32, "ARB_texture_buffer_object_rgb32");


		//texture buffer range
		FetchProcAddress(glTexBufferRange, "glTexBufferRange");

		FetchProcAddress(glTextureBufferRangeEXT, "glTextureBufferRangeEXT");

		FetchProcAddress(ARB_texture_buffer_range, "ARB_texture_buffer_range");


		//texture compression
		FetchProcAddress(glCompressedTexImage1DARB, "glCompressedTexImage1DARB");

		FetchProcAddress(glCompressedTexImage2DARB, "glCompressedTexImage2DARB");

		FetchProcAddress(glCompressedTexImage3DARB, "glCompressedTexImage3DARB");

		FetchProcAddress(glCompressedTexSubImage1DARB, "glCompressedTexSubImage1DARB");

		FetchProcAddress(glCompressedTexSubImage2DARB, "glCompressedTexSubImage2DARB");

		FetchProcAddress(glCompressedTexSubImage3DARB, "glCompressedTexSubImage3DARB");

		FetchProcAddress(glGetCompressedTexImageARB, "glGetCompressedTexImageARB");

		FetchProcAddress(ARB_texture_compression, "ARB_texture_compression");


		//texture compression bptc
		FetchProcAddress(ARB_texture_compression_bptc, "ARB_texture_compression_bptc");


		//texture compression rgtc
		FetchProcAddress(ARB_texture_compression_rgtc, "ARB_texture_compression_rgtc");


		//texture cube map
		FetchProcAddress(ARB_texture_cube_map, "ARB_texture_cube_map");


		//texture cube map array
		FetchProcAddress(ARB_texture_cube_map_array, "ARB_texture_cube_map_array");


		//texture env add
		FetchProcAddress(ARB_texture_env_add, "ARB_texture_env_add");


		//texture env combine
		FetchProcAddress(ARB_texture_env_combine, "ARB_texture_env_combine");


		//texture env crossbar
		FetchProcAddress(ARB_texture_env_crossbar, "ARB_texture_env_crossbar");


		//texture env dot3
		FetchProcAddress(ARB_texture_env_dot3, "ARB_texture_env_dot3");


		//texture filter anisotropic
		FetchProcAddress(ARB_texture_filter_anisotropic, "ARB_texture_filter_anisotropic");


		//texture filter minmax
		FetchProcAddress(ARB_texture_filter_minmax, "ARB_texture_filter_minmax");


		//texture float
		FetchProcAddress(ARB_texture_float, "ARB_texture_float");


		//texture gather
		FetchProcAddress(ARB_texture_gather, "ARB_texture_gather");


		//texture mirror clamp to edge
		FetchProcAddress(ARB_texture_mirror_clamp_to_edge, "ARB_texture_mirror_clamp_to_edge");


		//texture mirrored repeat
		FetchProcAddress(ARB_texture_mirrored_repeat, "ARB_texture_mirrored_repeat");


		//texture multisample
		FetchProcAddress(glGetMultisamplefv, "glGetMultisamplefv");

		FetchProcAddress(glSampleMaski, "glSampleMaski");

		FetchProcAddress(glTexImage2DMultisample, "glTexImage2DMultisample");

		FetchProcAddress(glTexImage3DMultisample, "glTexImage3DMultisample");

		FetchProcAddress(ARB_texture_multisample, "ARB_texture_multisample");


		//texture non power of two
		FetchProcAddress(ARB_texture_non_power_of_two, "ARB_texture_non_power_of_two");


		//texture query levels
		FetchProcAddress(ARB_texture_query_levels, "ARB_texture_query_levels");


		//texture query lod
		FetchProcAddress(ARB_texture_query_lod, "ARB_texture_query_lod");


		//texture rectangle
		FetchProcAddress(ARB_texture_rectangle, "ARB_texture_rectangle");


		//texture rg
		FetchProcAddress(ARB_texture_rg, "ARB_texture_rg");


		//texturergb10 a2ui
		FetchProcAddress(ARB_texture_rgb10_a2ui, "ARB_texture_rgb10_a2ui");


		//texture stencil8
		FetchProcAddress(ARB_texture_stencil8, "ARB_texture_stencil8");


		//texture storage
		FetchProcAddress(glTexStorage1D, "glTexStorage1D");

		FetchProcAddress(glTexStorage2D, "glTexStorage2D");

		FetchProcAddress(glTexStorage3D, "glTexStorage3D");

		FetchProcAddress(ARB_texture_storage, "ARB_texture_storage");


		//texture storage multisample
		FetchProcAddress(glTexStorage2DMultisample, "glTexStorage2DMultisample");

		FetchProcAddress(glTexStorage3DMultisample, "glTexStorage3DMultisample");

		FetchProcAddress(glTextureStorage2DMultisampleEXT, "glTextureStorage2DMultisampleEXT");

		FetchProcAddress(glTextureStorage3DMultisampleEXT, "glTextureStorage3DMultisampleEXT");

		FetchProcAddress(ARB_texture_storage_multisample, "ARB_texture_storage_multisample");


		//texture swizzle
		FetchProcAddress(ARB_texture_swizzle, "ARB_texture_swizzle");


		//texture view
		FetchProcAddress(glTextureView, "glTextureView");
		FetchProcAddress(ARB_texture_view, "ARB_texture_view");

		//timer query
		FetchProcAddress(glGetQueryObjecti64v, "glGetQueryObjecti64v");

		FetchProcAddress(glGetQueryObjectui64v, "glGetQueryObjectui64v");

		FetchProcAddress(glQueryCounter, "glQueryCounter");

		FetchProcAddress(ARB_timer_query, "ARB_timer_query");


		//transform feedback2
		FetchProcAddress(glBindTransformFeedback, "glBindTransformFeedback");

		FetchProcAddress(glDeleteTransformFeedbacks, "glDeleteTransformFeedbacks");

		FetchProcAddress(glDrawTransformFeedback, "glDrawTransformFeedback");

		FetchProcAddress(glGenTransformFeedbacks, "glGenTransformFeedbacks");

		FetchProcAddress(glIsTransformFeedback, "glIsTransformFeedback");

		FetchProcAddress(glPauseTransformFeedback, "glPauseTransformFeedback");

		FetchProcAddress(glResumeTransformFeedback, "glResumeTransformFeedback");

		FetchProcAddress(ARB_transform_feedback2, "ARB_transform_feedback2");


		//transform feedback3
		FetchProcAddress(glBeginQueryIndexed, "glBeginQueryIndexed");

		FetchProcAddress(glDrawTransformFeedbackStream, "glDrawTransformFeedbackStream");

		FetchProcAddress(glEndQueryIndexed, "glEndQueryIndexed");

		FetchProcAddress(glGetQueryIndexediv, "glGetQueryIndexediv");

		FetchProcAddress(ARB_transform_feedback3, "ARB_transform_feedback3");


		//transform feedback instanced
		FetchProcAddress(glDrawTransformFeedbackInstanced, "glDrawTransformFeedbackInstanced");

		FetchProcAddress(glDrawTransformFeedbackStreamInstanced, "glDrawTransformFeedbackStreamInstanced");


		//transform feedback instanced
		FetchProcAddress(ARB_transform_feedback_instanced, "ARB_transform_feedback_instanced");


		//transform feedback overflow query
		FetchProcAddress(ARB_transform_feedback_overflow_query, "ARB_transform_feedback_overflow_query");


		//transpose matrix
		FetchProcAddress(glLoadTransposeMatrixdARB, "glLoadTransposeMatrixdARB");

		FetchProcAddress(glLoadTransposeMatrixfARB, "glLoadTransposeMatrixfARB");

		FetchProcAddress(glMultTransposeMatrixdARB, "glMultTransposeMatrixdARB");

		FetchProcAddress(glMultTransposeMatrixfARB, "glMultTransposeMatrixfARB");

		FetchProcAddress(ARB_transpose_matrix, "ARB_transpose_matrix");


		//uniform buffer object
		FetchProcAddress(glBindBufferBase, "glBindBufferBase");

		FetchProcAddress(glBindBufferRange, "glBindBufferRange");

		FetchProcAddress(glGetActiveUniformBlockName, "glGetActiveUniformBlockName");

		FetchProcAddress(glGetActiveUniformBlockiv, "glGetActiveUniformBlockiv");

		FetchProcAddress(glGetActiveUniformName, "glGetActiveUniformName");

		FetchProcAddress(glGetActiveUniformsiv, "glGetActiveUniformsiv");

		FetchProcAddress(glGetIntegeri_v, "glGetIntegeri_v");

		FetchProcAddress(glGetUniformBlockIndex, "glGetUniformBlockIndex");

		FetchProcAddress(glGetUniformIndices, "glGetUniformIndices");

		FetchProcAddress(glUniformBlockBinding, "glUniformBlockBinding");

		FetchProcAddress(ARB_uniform_buffer_object, "ARB_uniform_buffer_object");


		//vertex array bgra
		FetchProcAddress(ARB_vertex_array_bgra, "ARB_vertex_array_bgra");


		//vertex array object
		FetchProcAddress(glBindVertexArray, "glBindVertexArray");

		FetchProcAddress(glDeleteVertexArrays, "glDeleteVertexArrays");

		FetchProcAddress(glGenVertexArrays, "glGenVertexArrays");

		FetchProcAddress(glIsVertexArray, "glIsVertexArray");

		FetchProcAddress(ARB_vertex_array_object, "ARB_vertex_array_object");


		//vertex attrib 64bit
		FetchProcAddress(glGetVertexAttribLdv, "glGetVertexAttribLdv");

		FetchProcAddress(glVertexAttribL1d, "glVertexAttribL1d");

		FetchProcAddress(glVertexAttribL1dv, "glVertexAttribL1dv");

		FetchProcAddress(glVertexAttribL2d, "glVertexAttribL2d");

		FetchProcAddress(glVertexAttribL2dv, "glVertexAttribL2dv");

		FetchProcAddress(glVertexAttribL3d, "glVertexAttribL3d");

		FetchProcAddress(glVertexAttribL3dv, "glVertexAttribL3dv");

		FetchProcAddress(glVertexAttribL4d, "glVertexAttribL4d");

		FetchProcAddress(glVertexAttribL4dv, "glVertexAttribL4dv");

		FetchProcAddress(glVertexAttribLPointer, "glVertexAttribLPointer");

		FetchProcAddress(ARB_vertex_attrib_64bit, "ARB_vertex_attrib_64bit");


		//vertex attrib binding
		FetchProcAddress(glBindVertexBuffer, "glBindVertexBuffer");

		FetchProcAddress(glVertexArrayBindVertexBufferEXT, "glVertexArrayBindVertexBufferEXT");

		FetchProcAddress(glVertexArrayVertexAttribBindingEXT, "glVertexArrayVertexAttribBindingEXT");

		FetchProcAddress(glVertexArrayVertexAttribFormatEXT, "glVertexArrayVertexAttribFormatEXT");

		FetchProcAddress(glVertexArrayVertexAttribIFormatEXT, "glVertexArrayVertexAttribIFormatEXT");

		FetchProcAddress(glVertexArrayVertexAttribLFormatEXT, "glVertexArrayVertexAttribLFormatEXT");

		FetchProcAddress(glVertexArrayVertexBindingDivisorEXT, "glVertexArrayVertexBindingDivisorEXT");

		FetchProcAddress(glVertexAttribBinding, "glVertexAttribBinding");

		FetchProcAddress(glVertexAttribFormat, "glVertexAttribFormat");

		FetchProcAddress(glVertexAttribIFormat, "glVertexAttribIFormat");

		FetchProcAddress(glVertexAttribLFormat, "glVertexAttribLFormat");

		FetchProcAddress(glVertexBindingDivisor, "glVertexBindingDivisor");

		FetchProcAddress(ARB_vertex_attrib_binding, "ARB_vertex_attrib_binding");


		//vertex blend
		FetchProcAddress(glVertexBlendARB, "glVertexBlendARB");

		FetchProcAddress(glWeightPointerARB, "glWeightPointerARB");

		FetchProcAddress(glWeightbvARB, "glWeightbvARB");

		FetchProcAddress(glWeightdvARB, "glWeightdvARB");

		FetchProcAddress(glWeightfvARB, "glWeightfvARB");

		FetchProcAddress(glWeightivARB, "glWeightivARB");

		FetchProcAddress(glWeightsvARB, "glWeightsvARB");

		FetchProcAddress(glWeightubvARB, "glWeightubvARB");

		FetchProcAddress(glWeightuivARB, "glWeightuivARB");

		FetchProcAddress(glWeightusvARB, "glWeightusvARB");

		FetchProcAddress(ARB_vertex_blend, "ARB_vertex_blend");


		//vertex buffer object 
		FetchProcAddress(glBindBufferARB, "glBindBufferARB");

		FetchProcAddress(glBufferDataARB, "glBufferDataARB");

		FetchProcAddress(glBufferSubDataARB, "glBufferSubDataARB");

		FetchProcAddress(glDeleteBuffersARB, "glDeleteBuffersARB");

		FetchProcAddress(glGenBuffersARB, "glGenBuffersARB");

		FetchProcAddress(glGetBufferParameterivARB, "glGetBufferParameterivARB");

		FetchProcAddress(glGetBufferPointervARB, "glGetBufferPointervARB");

		FetchProcAddress(glGetBufferSubDataARB, "glGetBufferSubDataARB");

		FetchProcAddress(glIsBufferARB, "glIsBufferARB");

		FetchProcAddress(glMapBufferARB, "glMapBufferARB");

		FetchProcAddress(glUnmapBufferARB, "glUnmapBufferARB");

		FetchProcAddress(ARB_vertex_buffer_object, "ARB_vertex_buffer_object");


		//vertex program
		FetchProcAddress(glBindProgramARB, "glBindProgramARB");

		FetchProcAddress(glDeleteProgramsARB, "glDeleteProgramsARB");

		FetchProcAddress(glDisableVertexAttribArrayARB, "glDisableVertexAttribArrayARB");

		FetchProcAddress(glEnableVertexAttribArrayARB, "glEnableVertexAttribArrayARB");

		FetchProcAddress(glGenProgramsARB, "glGenProgramsARB");

		FetchProcAddress(glGetProgramEnvParameterdvARB, "glGetProgramEnvParameterdvARB");

		FetchProcAddress(glGetProgramEnvParameterfvARB, "glGetProgramEnvParameterfvARB");

		FetchProcAddress(glGetProgramLocalParameterdvARB, "glGetProgramLocalParameterdvARB");

		FetchProcAddress(glGetProgramLocalParameterfvARB, "glGetProgramLocalParameterfvARB");

		FetchProcAddress(glGetProgramStringARB, "glGetProgramStringARB");

		FetchProcAddress(glGetProgramivARB, "glGetProgramivARB");

		FetchProcAddress(glGetVertexAttribPointervARB, "glGetVertexAttribPointervARB");

		FetchProcAddress(glGetVertexAttribdvARB, "glGetVertexAttribdvARB");

		FetchProcAddress(glGetVertexAttribfvARB, "glGetVertexAttribfvARB");

		FetchProcAddress(glGetVertexAttribivARB, "glGetVertexAttribivARB");

		FetchProcAddress(glIsProgramARB, "glIsProgramARB");

		FetchProcAddress(glProgramEnvParameter4dARB, "glProgramEnvParameter4dARB");

		FetchProcAddress(glProgramEnvParameter4dvARB, "glProgramEnvParameter4dvARB");

		FetchProcAddress(glProgramEnvParameter4fARB, "glProgramEnvParameter4fARB");

		FetchProcAddress(glProgramEnvParameter4fvARB, "glProgramEnvParameter4fvARB");

		FetchProcAddress(glProgramLocalParameter4dARB, "glProgramLocalParameter4dARB");

		FetchProcAddress(glProgramLocalParameter4dvARB, "glProgramLocalParameter4dvARB");

		FetchProcAddress(glProgramLocalParameter4fARB, "glProgramLocalParameter4fARB");

		FetchProcAddress(glProgramLocalParameter4fvARB, "glProgramLocalParameter4fvARB");

		FetchProcAddress(glProgramStringARB, "glProgramStringARB");

		FetchProcAddress(glVertexAttrib1dARB, "glVertexAttrib1dARB");

		FetchProcAddress(glVertexAttrib1dvARB, "glVertexAttrib1dvARB");

		FetchProcAddress(glVertexAttrib1fARB, "glVertexAttrib1fARB");

		FetchProcAddress(glVertexAttrib1fvARB, "glVertexAttrib1fvARB");

		FetchProcAddress(glVertexAttrib1sARB, "glVertexAttrib1sARB");

		FetchProcAddress(glVertexAttrib1svARB, "glVertexAttrib1svARB");

		FetchProcAddress(glVertexAttrib2dARB, "glVertexAttrib2dARB");

		FetchProcAddress(glVertexAttrib2dvARB, "glVertexAttrib2dvARB");

		FetchProcAddress(glVertexAttrib2fARB, "glVertexAttrib2fARB");

		FetchProcAddress(glVertexAttrib2fvARB, "glVertexAttrib2fvARB");

		FetchProcAddress(glVertexAttrib2sARB, "glVertexAttrib2sARB");

		FetchProcAddress(glVertexAttrib2svARB, "glVertexAttrib2svARB");

		FetchProcAddress(glVertexAttrib3dARB, "glVertexAttrib3dARB");

		FetchProcAddress(glVertexAttrib3dvARB, "glVertexAttrib3dvARB");

		FetchProcAddress(glVertexAttrib3fARB, "glVertexAttrib3fARB");

		FetchProcAddress(glVertexAttrib3fvARB, "glVertexAttrib3fvARB");

		FetchProcAddress(glVertexAttrib3sARB, "glVertexAttrib3sARB");

		FetchProcAddress(glVertexAttrib3svARB, "glVertexAttrib3svARB");

		FetchProcAddress(glVertexAttrib4NbvARB, "glVertexAttrib4NbvARB");

		FetchProcAddress(glVertexAttrib4NivARB, "glVertexAttrib4NivARB");

		FetchProcAddress(glVertexAttrib4NsvARB, "glVertexAttrib4NsvARB");

		FetchProcAddress(glVertexAttrib4NubARB, "glVertexAttrib4NubARB");

		FetchProcAddress(glVertexAttrib4NubvARB, "glVertexAttrib4NubvARB");

		FetchProcAddress(glVertexAttrib4NuivARB, "glVertexAttrib4NuivARB");

		FetchProcAddress(glVertexAttrib4NusvARB, "glVertexAttrib4NusvARB");

		FetchProcAddress(glVertexAttrib4bvARB, "glVertexAttrib4bvARB");

		FetchProcAddress(glVertexAttrib4dARB, "glVertexAttrib4dARB");

		FetchProcAddress(glVertexAttrib4dvARB, "glVertexAttrib4dvARB");

		FetchProcAddress(glVertexAttrib4fARB, "glVertexAttrib4fARB");

		FetchProcAddress(glVertexAttrib4fvARB, "glVertexAttrib4fvARB");

		FetchProcAddress(glVertexAttrib4ivARB, "glVertexAttrib4ivARB");

		FetchProcAddress(glVertexAttrib4sARB, "glVertexAttrib4sARB");

		FetchProcAddress(glVertexAttrib4svARB, "glVertexAttrib4svARB");

		FetchProcAddress(glVertexAttrib4ubvARB, "glVertexAttrib4ubvARB");

		FetchProcAddress(glVertexAttrib4uivARB, "glVertexAttrib4uivARB");

		FetchProcAddress(glVertexAttrib4usvARB, "glVertexAttrib4usvARB");

		FetchProcAddress(glVertexAttribPointerARB, "glVertexAttribPointerARB");

		FetchProcAddress(ARB_vertex_program, "ARB_vertex_program");


		//vertex shader
		FetchProcAddress(glBindAttribLocationARB, "glBindAttribLocationARB");

		FetchProcAddress(glGetActiveAttribARB, "glGetActiveAttribARB");

		FetchProcAddress(glGetAttribLocationARB, "glGetAttribLocationARB");

		FetchProcAddress(ARB_vertex_shader, "ARB_vertex_shader");


		//vertex type 10f_11f_11f rev
		FetchProcAddress(ARB_vertex_type_10f_11f_11f_rev, "ARB_vertex_type_10f_11f_11f_rev");


		//vertex type 2_10_10_10 rev
		FetchProcAddress(glColorP3ui, "glColorP3ui");

		FetchProcAddress(glColorP3uiv, "glColorP3uiv");

		FetchProcAddress(glColorP4ui, "glColorP4ui");

		FetchProcAddress(glColorP4uiv, "glColorP4uiv");

		FetchProcAddress(glMultiTexCoordP1ui, "glMultiTexCoordP1ui");

		FetchProcAddress(glMultiTexCoordP1uiv, "glMultiTexCoordP1uiv");

		FetchProcAddress(glMultiTexCoordP2ui, "glMultiTexCoordP2ui");

		FetchProcAddress(glMultiTexCoordP2uiv, "glMultiTexCoordP2uiv");

		FetchProcAddress(glMultiTexCoordP3ui, "glMultiTexCoordP3ui");

		FetchProcAddress(glMultiTexCoordP3uiv, "glMultiTexCoordP3uiv");

		FetchProcAddress(glMultiTexCoordP4ui, "glMultiTexCoordP4ui");

		FetchProcAddress(glMultiTexCoordP4uiv, "glMultiTexCoordP4uiv");

		FetchProcAddress(glNormalP3ui, "glNormalP3ui");

		FetchProcAddress(glNormalP3uiv, "glNormalP3uiv");

		FetchProcAddress(glSecondaryColorP3ui, "glSecondaryColorP3ui");

		FetchProcAddress(glSecondaryColorP3uiv, "glSecondaryColorP3uiv");

		FetchProcAddress(glTexCoordP1ui, "glTexCoordP1ui");

		FetchProcAddress(glTexCoordP1uiv, "glTexCoordP1uiv");

		FetchProcAddress(glTexCoordP2ui, "glTexCoordP2ui");

		FetchProcAddress(glTexCoordP2uiv, "glTexCoordP2uiv");

		FetchProcAddress(glTexCoordP3ui, "glTexCoordP3ui");

		FetchProcAddress(glTexCoordP3uiv, "glTexCoordP3uiv");

		FetchProcAddress(glTexCoordP4ui, "glTexCoordP4ui");

		FetchProcAddress(glTexCoordP4uiv, "glTexCoordP4uiv");

		FetchProcAddress(glVertexAttribP1ui, "glVertexAttribP1ui");

		FetchProcAddress(glVertexAttribP1uiv, "glVertexAttribP1uiv");

		FetchProcAddress(glVertexAttribP2ui, "glVertexAttribP2ui");

		FetchProcAddress(glVertexAttribP2uiv, "glVertexAttribP2uiv");

		FetchProcAddress(glVertexAttribP3ui, "glVertexAttribP3ui");

		FetchProcAddress(glVertexAttribP3uiv, "glVertexAttribP3uiv");

		FetchProcAddress(glVertexAttribP4ui, "glVertexAttribP4ui");

		FetchProcAddress(glVertexAttribP4uiv, "glVertexAttribP4uiv");

		FetchProcAddress(glVertexP2ui, "glVertexP2ui");

		FetchProcAddress(glVertexP2uiv, "glVertexP2uiv");

		FetchProcAddress(glVertexP3ui, "glVertexP3ui");

		FetchProcAddress(glVertexP3uiv, "glVertexP3uiv");

		FetchProcAddress(glVertexP4ui, "glVertexP4ui");

		FetchProcAddress(glVertexP4uiv, "glVertexP4uiv");

		FetchProcAddress(vertex_type_2_10_10_10_rev, "vertex_type_2_10_10_10_rev");


		//viewport array
		FetchProcAddress(glDepthRangeArrayv, "glDepthRangeArrayv");

		FetchProcAddress(glDepthRangeIndexed, "glDepthRangeIndexed");

		FetchProcAddress(glGetDoublei_v, "glGetDoublei_v");

		FetchProcAddress(glGetFloati_v, "glGetFloati_v");

		FetchProcAddress(glScissorArrayv, "glScissorArrayv");

		FetchProcAddress(glScissorIndexed, "glScissorIndexed");

		FetchProcAddress(glScissorIndexedv, "glScissorIndexedv");

		FetchProcAddress(glViewportArrayv, "glViewportArrayv");

		FetchProcAddress(glViewportIndexedf, "glViewportIndexedf");

		FetchProcAddress(glViewportIndexedfv, "glViewportIndexedfv");

		FetchProcAddress(viewport_array, "viewport_array");


		//window pos
		FetchProcAddress(glWindowPos2dARB, "glWindowPos2dARB");

		FetchProcAddress(glWindowPos2dvARB, "glWindowPos2dvARB");

		FetchProcAddress(glWindowPos2fARB, "glWindowPos2fARB");

		FetchProcAddress(glWindowPos2fvARB, "glWindowPos2fvARB");

		FetchProcAddress(glWindowPos2iARB, "glWindowPos2iARB");

		FetchProcAddress(glWindowPos2ivARB, "glWindowPos2ivARB");

		FetchProcAddress(glWindowPos2sARB, "glWindowPos2sARB");

		FetchProcAddress(glWindowPos2svARB, "glWindowPos2svARB");

		FetchProcAddress(glWindowPos3dARB, "glWindowPos3dARB");

		FetchProcAddress(glWindowPos3dvARB, "glWindowPos3dvARB");

		FetchProcAddress(glWindowPos3fARB, "glWindowPos3fARB");

		FetchProcAddress(glWindowPos3fvARB, "glWindowPos3fvARB");

		FetchProcAddress(glWindowPos3iARB, "glWindowPos3iARB");

		FetchProcAddress(glWindowPos3ivARB, "glWindowPos3ivARB");

		FetchProcAddress(glWindowPos3sARB, "glWindowPos3sARB");

		FetchProcAddress(glWindowPos3svARB, "glWindowPos3svARB");

		FetchProcAddress(ARB_window_pos, "ARB_window_pos");

	}	

#pragma endregion ARB Extensions

	//OpenGL ARM Extensions
#pragma region ARM

	enum openGL_ARM_t
	{
		//mali program binary
		gl_mali_program_binary_arm = 0x8f61,
		//mali shader binary
		gl_mali_shader_binary_arm = 0x8f60,
		//rgba8
		gl_rgba8_oes = 0x8058,
		//shader framebuffer fetch
		gl_fetch_per_sample_arm = 0x8f65,
		gl_fragment_shader_framebuffer_fetch_mrt_arm = 0x8f66,
	};

	//mali program binary 
	bool ARM_mali_program_binary = false;
	//mali shader binary 
	bool ARM_mali_shader_binary = false;
	//rgba8 
	bool ARM_rgba8 = false;
	//shader framebuffer fetch 
	bool ARM_shader_framebuffer_fetch = false;
	//shader framebuffer fetch depth stencil 
	bool ARM_shader_framebuffer_fetch_depth_stencil = false;

	//*< load ARM Extensions
	void LoadARMExtensions()
	{
		//mali program binary 
		FetchProcAddress(ARM_mali_program_binary, "ARM_mali_program_binary");

		//mali shader binary 
		FetchProcAddress(ARM_mali_shader_binary, "ARM_mali_shader_binary");

		//rgba8 
		FetchProcAddress(ARM_rgba8, "ARM_rgba8");

		//shader framebuffer fetch 
		FetchProcAddress(ARM_shader_framebuffer_fetch, "ARM_shader_framebuffer_fetch");

		//shader framebuffer fetch depth stencil 
		FetchProcAddress(ARM_shader_framebuffer_fetch_depth_stencil, "ARM_shader_framebuffer_fetch_depth_stencil");
	}

#pragma endregion ARM Extensions

	//OpenGL ATIX Extensions
#pragma region ATIX

	enum OpenGL_ATIX_t
	{
		//point_sprites
		gl_texture_point_mode_atix = 0x60b0,
		gl_texture_point_one_coord_atix = 0x60b1,
		gl_texture_point_sprite_atix = 0x60b2,
		gl_point_sprite_cull_mode_atix = 0x60b3,
		gl_point_sprite_cull_center_atix = 0x60b4,
		gl_point_sprite_cull_clip_atix = 0x60b5,

		//texture_env_combine3
		gl_modulate_add_atix = 0x8744,
		gl_modulate_signed_add_atix = 0x8745,
		gl_modulate_subtract_atix = 0x8746,

		//texture_env_route
		gl_secondary_color_atix = 0x8747,
		gl_texture_output_rgb_atix = 0x8748,
		gl_texture_output_alpha_atix = 0x8749,

		//vertex_shader_output_point_size
		gl_output_point_size_atix = 0x610e,
	};

	//point sprites
	bool atix_point_sprites = false;

	//texture env combine3
	bool atix_texture_env_combine3 = false;

	//texture env route
	bool atix_texture_env_route = false;

	//vertex shader output point size
	bool atix_vertex_shader_output_point_size = false;

	//*< load ATIX Extensions
	void LoadATIXExtensions()
	{
		//mali program binary 
		FetchProcAddress(ARM_mali_program_binary, "ARM_mali_program_binary");

		//mali shader binary 
		FetchProcAddress(ARM_mali_shader_binary, "ARM_mali_shader_binary");

		//rgba8 
		FetchProcAddress(ARM_rgba8, "ARM_rgba8");

		//shader framebuffer fetch 
		FetchProcAddress(ARM_shader_framebuffer_fetch, "ARM_shader_framebuffer_fetch");

		//shader framebuffer fetch depth stencil 
		FetchProcAddress(ARM_shader_framebuffer_fetch_depth_stencil, "ARM_shader_framebuffer_fetch_depth_stencil");

	}

#pragma endregion ATIX Extensions

	//OpenGL ATI Extensions
#pragma region ATI

	enum OpenGL_ATI_t
	{
		//draw_buffers
		gl_max_draw_buffers_ati = 0x8824,
		gl_draw_buffer0_ati = 0x8825,
		gl_draw_buffer1_ati = 0x8826,
		gl_draw_buffer2_ati = 0x8827,
		gl_draw_buffer3_ati = 0x8828,
		gl_draw_buffer4_ati = 0x8829,
		gl_draw_buffer5_ati = 0x882a,
		gl_draw_buffer6_ati = 0x882b,
		gl_draw_buffer7_ati = 0x882c,
		gl_draw_buffer8_ati = 0x882d,
		gl_draw_buffer9_ati = 0x882e,
		gl_draw_buffer10_ati = 0x882f,
		gl_draw_buffer11_ati = 0x8830,
		gl_draw_buffer12_ati = 0x8831,
		gl_draw_buffer13_ati = 0x8832,
		gl_draw_buffer14_ati = 0x8833,
		gl_draw_buffer15_ati = 0x8834,

		//element_array
		gl_element_array_ati = 0x8768,
		gl_element_array_type_ati = 0x8769,
		gl_element_array_pointer_ati = 0x876a,

		//envmap_bumpmap
		gl_bump_rot_matrix_ati = 0x8775,
		gl_bump_rot_matrix_size_ati = 0x8776,
		gl_bump_num_tex_units_ati = 0x8777,
		gl_bump_tex_units_ati = 0x8778,
		gl_dudv_ati = 0x8779,
		gl_du8dv8_ati = 0x877a,
		gl_bump_envmap_ati = 0x877b,
		gl_bump_target_ati = 0x877c,

		//fragment_shader
		gl_2x_bit_ati = 0x00000001,
		gl_red_bit_ati = 0x00000001,
		gl_4x_bit_ati = 0x00000002,
		gl_comp_bit_ati = 0x00000002,
		gl_green_bit_ati = 0x00000002,
		gl_8x_bit_ati = 0x00000004,
		gl_blue_bit_ati = 0x00000004,
		gl_negate_bit_ati = 0x00000004,
		gl_bias_bit_ati = 0x00000008,
		gl_half_bit_ati = 0x00000008,
		gl_quarter_bit_ati = 0x00000010,
		gl_eighth_bit_ati = 0x00000020,
		gl_saturate_bit_ati = 0x00000040,
		gl_fragment_shader_ati = 0x8920,
		gl_reg_0_ati = 0x8921,
		gl_reg_1_ati = 0x8922,
		gl_reg_2_ati = 0x8923,
		gl_reg_3_ati = 0x8924,
		gl_reg_4_ati = 0x8925,
		gl_reg_5_ati = 0x8926,
		gl_con_0_ati = 0x8941,
		gl_con_1_ati = 0x8942,
		gl_con_2_ati = 0x8943,
		gl_con_3_ati = 0x8944,
		gl_con_4_ati = 0x8945,
		gl_con_5_ati = 0x8946,
		gl_con_6_ati = 0x8947,
		gl_con_7_ati = 0x8948,
		gl_mov_ati = 0x8961,
		gl_add_ati = 0x8963,
		gl_mul_ati = 0x8964,
		gl_sub_ati = 0x8965,
		gl_dot3_ati = 0x8966,
		gl_dot4_ati = 0x8967,
		gl_mad_ati = 0x8968,
		gl_lerp_ati = 0x8969,
		gl_cnd_ati = 0x896a,
		gl_cnd0_ati = 0x896b,
		gl_dot2_add_ati = 0x896c,
		gl_secondary_interpolator_ati = 0x896d,
		gl_num_fragment_registers_ati = 0x896e,
		gl_num_fragment_constants_ati = 0x896f,
		gl_num_passes_ati = 0x8970,
		gl_num_instructions_per_pass_ati = 0x8971,
		gl_num_instructions_total_ati = 0x8972,
		gl_num_input_interpolator_components_ati = 0x8973,
		gl_num_loopback_components_ati = 0x8974,
		gl_color_alpha_pairing_ati = 0x8975,
		gl_swizzle_str_ati = 0x8976,
		gl_swizzle_stq_ati = 0x8977,
		gl_swizzle_str_dr_ati = 0x8978,
		gl_swizzle_stq_dq_ati = 0x8979,
		gl_swizzle_strq_ati = 0x897a,
		gl_swizzle_strq_dq_ati = 0x897b,

		//meminfo
		gl_vbo_free_memory_ati = 0x87fb,
		gl_texture_free_memory_ati = 0x87fc,
		gl_renderbuffer_free_memory_ati = 0x87fd,

		//pn_triangles
		gl_pn_triangles_ati = 0x87f0,
		gl_max_pn_triangles_tesselation_level_ati = 0x87f1,
		gl_pn_triangles_point_mode_ati = 0x87f2,
		gl_pn_triangles_normal_mode_ati = 0x87f3,
		gl_pn_triangles_tesselation_level_ati = 0x87f4,
		gl_pn_triangles_point_mode_linear_ati = 0x87f5,
		gl_pn_triangles_point_mode_cubic_ati = 0x87f6,
		gl_pn_triangles_normal_mode_linear_ati = 0x87f7,
		gl_pn_triangles_normal_mode_quadratic_ati = 0x87f8,

		//separate_stencil
		gl_stencil_back_func_ati = 0x8800,
		gl_stencil_back_fail_ati = 0x8801,
		gl_stencil_back_pass_depth_fail_ati = 0x8802,
		gl_stencil_back_pass_depth_pass_ati = 0x8803,

		//text_fragment_shader
		gl_text_fragment_shader_ati = 0x8200,

		//texture_compression_3dc
		gl_compressed_luminance_alpha_3dc_ati = 0x8837,

		//texture_env_combine3
		gl_modulate_add_ati = 0x8744,
		gl_modulate_signed_add_ati = 0x8745,
		gl_modulate_subtract_ati = 0x8746,

		//texture_float
		gl_rgba_float32_ati = 0x8814,
		gl_rgb_float32_ati = 0x8815,
		gl_alpha_float32_ati = 0x8816,
		gl_intensity_float32_ati = 0x8817,
		gl_luminance_float32_ati = 0x8818,
		gl_luminance_alpha_float32_ati = 0x8819,
		gl_rgba_float16_ati = 0x881a,
		gl_rgb_float16_ati = 0x881b,
		gl_alpha_float16_ati = 0x881c,
		gl_intensity_float16_ati = 0x881d,
		gl_luminance_float16_ati = 0x881e,
		gl_luminance_alpha_float16_ati = 0x881f,

		//texture_mirror_once
		gl_mirror_clamp_ati = 0x8742,
		gl_mirror_clamp_to_edge_ati = 0x8743,

		//vertex_array_object
		gl_static_ati = 0x8760,
		gl_dynamic_ati = 0x8761,
		gl_preserve_ati = 0x8762,
		gl_discard_ati = 0x8763,
		gl_object_buffer_size_ati = 0x8764,
		gl_object_buffer_usage_ati = 0x8765,
		gl_array_object_buffer_ati = 0x8766,
		gl_array_object_offset_ati = 0x8767,

		//vertex_streams
		gl_max_vertex_streams_ati = 0x876b,
		gl_vertex_source_ati = 0x876c,
		gl_vertex_stream0_ati = 0x876d,
		gl_vertex_stream1_ati = 0x876e,
		gl_vertex_stream2_ati = 0x876f,
		gl_vertex_stream3_ati = 0x8770,
		gl_vertex_stream4_ati = 0x8771,
		gl_vertex_stream5_ati = 0x8772,
		gl_vertex_stream6_ati = 0x8773,
		gl_vertex_stream7_ati = 0x8774,
	};

	//draw_buffers
	void (*glDrawBuffersATI) (GLsizei n, const GLenum * bufs) = nullptr;

	bool ATI_draw_buffers = false;

	//element_array
	void (*glDrawElementArrayATI) (GLenum mode, GLsizei count) = nullptr;
	void (*glDrawRangeElementArrayATI) (GLenum mode, GLuint start, GLuint end, GLsizei count) = nullptr;
	void (*glElementPointerATI) (GLenum type, const void* pointer) = nullptr;

	bool ATI_element_array = false;

	//envmap_bumpmap
	void (*glGetTexBumpParameterfvATI) (GLenum pname, GLfloat * param) = nullptr;
	void (*glGetTexBumpParameterivATI) (GLenum pname, GLint* param) = nullptr;
	void (*glTexBumpParameterfvATI) (GLenum pname, GLfloat* param) = nullptr;
	void (*glTexBumpParameterivATI) (GLenum pname, GLint* param) = nullptr;

	bool ATI_envmap_bumpmap = false;

	//fragment_shader
	void (*glAlphaFragmentOp1ATI) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod) = nullptr;
	void (*glAlphaFragmentOp2ATI) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod) = nullptr;
	void (*glAlphaFragmentOp3ATI) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod) = nullptr;
	void (*glBeginFragmentShaderATI) (void) = nullptr;
	void (*glBindFragmentShaderATI) (GLuint id) = nullptr;
	void (*glColorFragmentOp1ATI) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod) = nullptr;
	void (*glColorFragmentOp2ATI) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod) = nullptr;
	void (*glColorFragmentOp3ATI) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod) = nullptr;
	void (*glDeleteFragmentShaderATI) (GLuint id) = nullptr;
	void (*glEndFragmentShaderATI) (void) = nullptr;
	GLuint(*glGenFragmentShadersATI) (GLuint range) = nullptr;
	void (*glPassTexCoordATI) (GLuint dst, GLuint coord, GLenum swizzle) = nullptr;
	void (*glSampleMapATI) (GLuint dst, GLuint interp, GLenum swizzle) = nullptr;
	void (*glSetFragmentShaderConstantATI) (GLuint dst, const GLfloat* value) = nullptr;

	bool ATI_fragment_shader = false;

	//map_object_buffer
	void* (*glMapObjectBufferATI) (GLuint buffer) = nullptr;
	void (*glUnmapObjectBufferATI) (GLuint buffer) = nullptr;

	bool ATI_map_object_buffer = false;

	//meminfo
	bool ATI_meminfo = false;

	//pn_triangles
	void (*glPNTrianglesfATI) (GLenum pname, GLfloat param) = nullptr;
	void (*glPNTrianglesiATI) (GLenum pname, GLint param) = nullptr;

	bool GLEW_ATI_pn_triangles = false;

	//separate_stencil
	void (*glStencilFuncSeparateATI) (GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask) = nullptr;
	void (*glStencilOpSeparateATI) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) = nullptr;

	bool ATI_separate_stencil = false;

	//shader_texture_lod
	bool ATI_shader_texture_lod = false;

	//text_fragment_shader
	bool ATI_text_fragment_shader = false;

	//texture_compression_3dc
	bool ATI_texture_compression_3dc = false;

	//texture_env_combine3
	bool ATI_texture_env_combine3 = false;

	//texture_float
	bool ATI_texture_float = false;

	//texture_mirror_once
	bool ATI_texture_mirror_once = false;

	//vertex_array_object
	void (*glArrayObjectATI) (GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset) = nullptr;
	void (*glFreeObjectBufferATI) (GLuint buffer) = nullptr;
	void (*glGetArrayObjectfvATI) (GLenum array, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetArrayObjectivATI) (GLenum array, GLenum pname, GLint* params) = nullptr;
	void (*glGetObjectBufferfvATI) (GLuint buffer, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetObjectBufferivATI) (GLuint buffer, GLenum pname, GLint* params) = nullptr;
	void (*glGetVariantArrayObjectfvATI) (GLuint id, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetVariantArrayObjectivATI) (GLuint id, GLenum pname, GLint* params) = nullptr;
	GLboolean(*glIsObjectBufferATI) (GLuint buffer) = nullptr;
	GLuint(*glNewObjectBufferATI) (GLsizei size, const void* pointer, GLenum usage) = nullptr;
	void (*glUpdateObjectBufferATI) (GLuint buffer, GLuint offset, GLsizei size, const void* pointer, GLenum preserve) = nullptr;
	void (*glVariantArrayObjectATI) (GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset) = nullptr;

	bool ATI_vertex_array_object = false;

	//vertex_attrib_array_object
	void (*glGetVertexAttribArrayObjectfvATI) (GLuint index, GLenum pname, GLfloat * params) = nullptr;
	void (*glGetVertexAttribArrayObjectivATI) (GLuint index, GLenum pname, GLint* params) = nullptr;
	void (*glVertexAttribArrayObjectATI) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset) = nullptr;

	bool ATI_vertex_attrib_array_object = false;

	//vertex_streams
	void (*glClientActiveVertexStreamATI) (GLenum stream) = nullptr;
	void (*glNormalStream3bATI) (GLenum stream, GLbyte x, GLbyte y, GLbyte z) = nullptr;
	void (*glNormalStream3bvATI) (GLenum stream, const GLbyte* coords) = nullptr;
	void (*glNormalStream3dATI) (GLenum stream, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void (*glNormalStream3dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	void (*glNormalStream3fATI) (GLenum stream, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glNormalStream3fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	void (*glNormalStream3iATI) (GLenum stream, GLint x, GLint y, GLint z) = nullptr;
	void (*glNormalStream3ivATI) (GLenum stream, const GLint* coords) = nullptr;
	void (*glNormalStream3sATI) (GLenum stream, GLshort x, GLshort y, GLshort z) = nullptr;
	void (*glNormalStream3svATI) (GLenum stream, const GLshort* coords) = nullptr;
	void (*glVertexBlendEnvfATI) (GLenum pname, GLfloat param) = nullptr;
	void (*glVertexBlendEnviATI) (GLenum pname, GLint param) = nullptr;
	void (*glVertexStream1dATI) (GLenum stream, GLdouble x) = nullptr;
	void (*glVertexStream1dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	void (*glVertexStream1fATI) (GLenum stream, GLfloat x) = nullptr;
	void (*glVertexStream1fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	void (*glVertexStream1iATI) (GLenum stream, GLint x) = nullptr;
	void (*glVertexStream1ivATI) (GLenum stream, const GLint* coords) = nullptr;
	void (*glVertexStream1sATI) (GLenum stream, GLshort x) = nullptr;
	void (*glVertexStream1svATI) (GLenum stream, const GLshort* coords) = nullptr;
	void (*glVertexStream2dATI) (GLenum stream, GLdouble x, GLdouble y) = nullptr;
	void (*glVertexStream2dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	void (*glVertexStream2fATI) (GLenum stream, GLfloat x, GLfloat y) = nullptr;
	void (*glVertexStream2fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	void (*glVertexStream2iATI) (GLenum stream, GLint x, GLint y) = nullptr;
	void (*glVertexStream2ivATI) (GLenum stream, const GLint* coords) = nullptr;
	void (*glVertexStream2sATI) (GLenum stream, GLshort x, GLshort y) = nullptr;
	void (*glVertexStream2svATI) (GLenum stream, const GLshort* coords) = nullptr;
	void (*glVertexStream3dATI) (GLenum stream, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void (*glVertexStream3dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	void (*glVertexStream3fATI) (GLenum stream, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glVertexStream3fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	void (*glVertexStream3iATI) (GLenum stream, GLint x, GLint y, GLint z) = nullptr;
	void (*glVertexStream3ivATI) (GLenum stream, const GLint* coords) = nullptr;
	void (*glVertexStream3sATI) (GLenum stream, GLshort x, GLshort y, GLshort z) = nullptr;
	void (*glVertexStream3svATI) (GLenum stream, const GLshort* coords) = nullptr;
	void (*glVertexStream4dATI) (GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void (*glVertexStream4dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	void (*glVertexStream4fATI) (GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void (*glVertexStream4fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	void (*glVertexStream4iATI) (GLenum stream, GLint x, GLint y, GLint z, GLint w) = nullptr;
	void (*glVertexStream4ivATI) (GLenum stream, const GLint* coords) = nullptr;
	void (*glVertexStream4sATI) (GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
	void (*glVertexStream4svATI) (GLenum stream, const GLshort* coords) = nullptr;

	bool ATI_vertex_streams = false;

	//*< load ATI Extensions
	void LoadATIExtensions()
	{
		//draw_buffers
		FetchProcAddress(glDrawBuffersATI, "glDrawBuffersATI");

		FetchProcAddress(ATI_draw_buffers, "ATI_draw_buffers");


		//element_array
		FetchProcAddress(glDrawElementArrayATI, "glDrawElementArrayATI");

		FetchProcAddress(glDrawRangeElementArrayATI, "glDrawRangeElementArrayATI");

		FetchProcAddress(glElementPointerATI, "glElementPointerATI");

		FetchProcAddress(ATI_element_array, "ATI_element_array");


		//envmap_bumpmap
		FetchProcAddress(glGetTexBumpParameterfvATI, "glGetTexBumpParameterfvATI");

		FetchProcAddress(glGetTexBumpParameterivATI, "glGetTexBumpParameterivATI");

		FetchProcAddress(glTexBumpParameterfvATI, "glTexBumpParameterfvATI");

		FetchProcAddress(glTexBumpParameterivATI, "glTexBumpParameterivATI");

		FetchProcAddress(ATI_envmap_bumpmap, "ATI_envmap_bumpmap");


		//fragment_shader
		FetchProcAddress(glAlphaFragmentOp1ATI, "glAlphaFragmentOp1ATI");

		FetchProcAddress(glAlphaFragmentOp2ATI, "glAlphaFragmentOp2ATI");

		FetchProcAddress(glAlphaFragmentOp3ATI, "glAlphaFragmentOp3ATI");

		FetchProcAddress(glBeginFragmentShaderATI, "glBeginFragmentShaderATI");

		FetchProcAddress(glBindFragmentShaderATI, "glBindFragmentShaderATI");

		FetchProcAddress(glColorFragmentOp1ATI, "glColorFragmentOp1ATI");

		FetchProcAddress(glColorFragmentOp2ATI, "glColorFragmentOp2ATI");

		FetchProcAddress(glColorFragmentOp3ATI, "glColorFragmentOp3ATI");

		FetchProcAddress(glDeleteFragmentShaderATI, "glDeleteFragmentShaderATI");

		FetchProcAddress(glEndFragmentShaderATI, "glEndFragmentShaderATI");

		FetchProcAddress(glGenFragmentShadersATI, "glGenFragmentShadersATI");

		FetchProcAddress(glPassTexCoordATI, "glPassTexCoordATI");

		FetchProcAddress(glSampleMapATI, "glSampleMapATI");

		FetchProcAddress(glSetFragmentShaderConstantATI, "glSetFragmentShaderConstantATI");

		FetchProcAddress(ATI_fragment_shader, "ATI_fragment_shader");


		//map_object_buffer
		FetchProcAddress(glMapObjectBufferATI, "glMapObjectBufferATI");

		FetchProcAddress(glUnmapObjectBufferATI, "glUnmapObjectBufferATI");

		FetchProcAddress(ATI_map_object_buffer, "ATI_map_object_buffer");


		//meminfo
		FetchProcAddress(ATI_meminfo, "ATI_meminfo");


		//pn_triangles
		FetchProcAddress(glPNTrianglesfATI, "glPNTrianglesfATI");

		FetchProcAddress(glPNTrianglesiATI, "glPNTrianglesiATI");

		FetchProcAddress(GLEW_ATI_pn_triangles, "GLEW_ATI_pn_triangles");


		//separate_stencil
		FetchProcAddress(glStencilFuncSeparateATI, "glStencilFuncSeparateATI");

		FetchProcAddress(glStencilOpSeparateATI, "glStencilOpSeparateATI");

		FetchProcAddress(ATI_separate_stencil, "ATI_separate_stencil");


		//shader_texture_lod
		FetchProcAddress(ATI_shader_texture_lod, "ATI_shader_texture_lod");


		//text_fragment_shader
		FetchProcAddress(ATI_text_fragment_shader, "ATI_text_fragment_shader");


		//texture_compression_3dc
		FetchProcAddress(ATI_texture_compression_3dc, "ATI_texture_compression_3dc");

		//texture_env_combine3
		FetchProcAddress(ATI_texture_env_combine3, "ATI_texture_env_combine3");

		//texture_float
		FetchProcAddress(ATI_texture_float, "ATI_texture_float");

		//texture_mirror_once
		FetchProcAddress(ATI_texture_mirror_once, "ATI_texture_mirror_once");

		//vertex_array_object
		FetchProcAddress(glArrayObjectATI, "glArrayObjectATI");
		FetchProcAddress(glFreeObjectBufferATI, "glFreeObjectBufferATI");
		FetchProcAddress(glGetArrayObjectfvATI, "glGetArrayObjectfvATI");
		FetchProcAddress(glGetArrayObjectivATI, "glGetArrayObjectivATI");
		FetchProcAddress(glGetObjectBufferfvATI, "glGetObjectBufferfvATI");
		FetchProcAddress(glGetObjectBufferivATI, "glGetObjectBufferivATI");
		FetchProcAddress(glGetVariantArrayObjectfvATI, "glGetVariantArrayObjectfvATI");
		FetchProcAddress(glGetVariantArrayObjectivATI, "glGetVariantArrayObjectivATI");
		FetchProcAddress(glIsObjectBufferATI, "glIsObjectBufferATI");
		FetchProcAddress(glNewObjectBufferATI, "glNewObjectBufferATI");
		FetchProcAddress(glUpdateObjectBufferATI, "glUpdateObjectBufferATI");
		FetchProcAddress(glVariantArrayObjectATI, "glVariantArrayObjectATI");
		FetchProcAddress(ATI_vertex_array_object, "ATI_vertex_array_object");

		//vertex_attrib_array_object
		FetchProcAddress(glGetVertexAttribArrayObjectfvATI, "glGetVertexAttribArrayObjectfvATI");
		FetchProcAddress(glGetVertexAttribArrayObjectivATI, "glGetVertexAttribArrayObjectivATI");
		FetchProcAddress(glVertexAttribArrayObjectATI, "glVertexAttribArrayObjectATI");
		FetchProcAddress(ATI_vertex_attrib_array_object, "ATI_vertex_attrib_array_object");

		//vertex_streams
		FetchProcAddress(glClientActiveVertexStreamATI, "glClientActiveVertexStreamATI");
		FetchProcAddress(glNormalStream3bATI, "glNormalStream3bATI");
		FetchProcAddress(glNormalStream3bvATI, "glNormalStream3bvATI");
		FetchProcAddress(glNormalStream3dATI, "glNormalStream3dATI");
		FetchProcAddress(glNormalStream3dvATI, "glNormalStream3dvATI");
		FetchProcAddress(glNormalStream3fATI, "glNormalStream3fATI");
		FetchProcAddress(glNormalStream3fvATI, "glNormalStream3fvATI");
		FetchProcAddress(glNormalStream3iATI, "glNormalStream3iATI");
		FetchProcAddress(glNormalStream3ivATI, "glNormalStream3ivATI");
		FetchProcAddress(glNormalStream3sATI, "glNormalStream3sATI");
		FetchProcAddress(glNormalStream3svATI, "glNormalStream3svATI");
		FetchProcAddress(glVertexBlendEnvfATI, "glVertexBlendEnvfATI");
		FetchProcAddress(glVertexBlendEnviATI, "glVertexBlendEnviATI");
		FetchProcAddress(glVertexStream1dATI, "glVertexStream1dATI");
		FetchProcAddress(glVertexStream1dvATI, "glVertexStream1dvATI");
		FetchProcAddress(glVertexStream1fATI, "glVertexStream1fATI");
		FetchProcAddress(glVertexStream1fvATI, "glVertexStream1fvATI");
		FetchProcAddress(glVertexStream1iATI, "glVertexStream1iATI");
		FetchProcAddress(glVertexStream1ivATI, "glVertexStream1ivATI");
		FetchProcAddress(glVertexStream1sATI, "glVertexStream1sATI");
		FetchProcAddress(glVertexStream1svATI, "glVertexStream1svATI");
		FetchProcAddress(glVertexStream2dATI, "glVertexStream2dATI");
		FetchProcAddress(glVertexStream2dvATI, "glVertexStream2dvATI");
		FetchProcAddress(glVertexStream2fATI, "glVertexStream2fATI");
		FetchProcAddress(glVertexStream2fvATI, "glVertexStream2fvATI");
		FetchProcAddress(glVertexStream2iATI, "glVertexStream2iATI");
		FetchProcAddress(glVertexStream2ivATI, "glVertexStream2ivATI");
		FetchProcAddress(glVertexStream2sATI, "glVertexStream2sATI");
		FetchProcAddress(glVertexStream2svATI, "glVertexStream2svATI");
		FetchProcAddress(glVertexStream3dATI, "glVertexStream3dATI");
		FetchProcAddress(glVertexStream3dvATI, "glVertexStream3dvATI");
		FetchProcAddress(glVertexStream3fATI, "glVertexStream3fATI");
		FetchProcAddress(glVertexStream3fvATI, "glVertexStream3fvATI");
		FetchProcAddress(glVertexStream3iATI, "glVertexStream3iATI");
		FetchProcAddress(glVertexStream3ivATI, "glVertexStream3ivATI");
		FetchProcAddress(glVertexStream3sATI, "glVertexStream3sATI");
		FetchProcAddress(glVertexStream3svATI, "glVertexStream3svATI");
		FetchProcAddress(glVertexStream4dATI, "glVertexStream4dATI");
		FetchProcAddress(glVertexStream4dvATI, "glVertexStream4dvATI");
		FetchProcAddress(glVertexStream4fATI, "glVertexStream4fATI");
		FetchProcAddress(glVertexStream4fvATI, "glVertexStream4fvATI");
		FetchProcAddress(glVertexStream4iATI, "glVertexStream4iATI");
		FetchProcAddress(glVertexStream4ivATI, "glVertexStream4ivATI");
		FetchProcAddress(glVertexStream4sATI, "glVertexStream4sATI");
		FetchProcAddress(glVertexStream4svATI, "glVertexStream4svATI");
		FetchProcAddress(ATI_vertex_streams, "ATI_vertex_streams");
	}

#pragma endregion ATI Extensions

	//OpenGL EGL_KHR Extensions
#pragma region EGL_KHR

	//context  flush control 
	bool EGL_KHR_context_flush_control = false;

	//*< load EGL_KHR Extensions
	void LoadEGLKHRExtensions()
	{
		FetchProcAddress(EGL_KHR_context_flush_control, "EGL_KHR_context_flush_control");
	}

#pragma endregion EGL_KHR Extensions

	//OpenGL EGL_NV Extensions
#pragma region EGL_NV

	enum OpenGL_EGL_NV_t
	{
		//robustness video memory purge
		gl_egl_generate_reset_on_video_memory_purge_nv = 0x334c,
		gl_purged_context_reset_nv = 0x92bb,
	};

	//robustness video memory purge
	bool EGL_NV_robustness_video_memory_purge = false;

	//*< load EGL_NV Extensions
	void LoadEGLNVExtensions()
	{
		//robustness video memory purge
		FetchProcAddress(EGL_NV_robustness_video_memory_purge, "EGL_NV_robustness_video_memory_purge");
	}

#pragma endregion EGL_NV Extensions

	//OpenGL EXT Extensions
#pragma region EXT

		typedef void* GLeglClientBufferEXT;		

		enum OpenGL_EXT_t
		{
			//422 pixels
			gl_422_ext = 0x80cc,
			gl_422_rev_ext = 0x80cd,
			gl_422_average_ext = 0x80ce,
			gl_422_rev_average_ext = 0x80cf,

			//cg shader
			gl_cg_vertex_shader_ext = 0x890e,
			gl_cg_fragment_shader_ext = 0x890f,

			//yuv target
			gl_sampler_external_2d_y2y_ext = 0x8be7,

			//abgr
			gl_abgr_ext = 0x8000,

			//bgra
			gl_bgr_ext = 0x80e0,
			//gl_bgra_ext = 0x80e1,

			//bindable uniform
			gl_max_vertex_bindable_uniforms_ext = 0x8de2,
			gl_max_fragment_bindable_uniforms_ext = 0x8de3,
			gl_max_geometry_bindable_uniforms_ext = 0x8de4,
			gl_max_bindable_uniform_size_ext = 0x8ded,
			gl_uniform_buffer_ext = 0x8dee,
			gl_uniform_buffer_binding_ext = 0x8def,

			//blend color
			gl_constant_color_ext = 0x8001,
			gl_one_minus_constant_color_ext = 0x8002,
			gl_constant_alpha_ext = 0x8003,
			gl_one_minus_constant_alpha_ext = 0x8004,
			gl_blend_color_ext = 0x8005,

			//blend equation separate
			gl_blend_equation_rgb_ext = 0x8009,
			gl_blend_equation_alpha_ext = 0x883d,

			//blend func extended
			gl_src_alpha_saturate_ext = 0x0308,
			gl_src1_alpha_ext = 0x8589,
			gl_src1_color_ext = 0x88f9,
			gl_one_minus_src1_color_ext = 0x88fa,
			gl_one_minus_src1_alpha_ext = 0x88fb,
			gl_max_dual_source_draw_buffers_ext = 0x88fc,
			gl_location_index_ext = 0x930f,

			//blend func separate
			gl_blend_dst_rgb_ext = 0x80c8,
			gl_blend_src_rgb_ext = 0x80c9,
			gl_blend_dst_alpha_ext = 0x80ca,
			gl_blend_src_alpha_ext = 0x80cb,

			//blend minmax
			gl_func_add_ext = 0x8006,
			gl_min_ext = 0x8007,
			gl_max_ext = 0x8008,
			gl_blend_equation_ext = 0x8009,

			//blend subtract
			gl_func_subtract_ext = 0x800a,
			gl_func_reverse_subtract_ext = 0x800b,

			//buffer storage
			//gl_map_read_bit = 0x0001,
			//gl_map_write_bit = 0x0002,
			gl_map_persistent_bit_ext = 0x0040,
			gl_map_coherent_bit_ext = 0x0080,
			gl_dynamic_storage_bit_ext = 0x0100,
			gl_client_storage_bit_ext = 0x0200,
			gl_client_mapped_buffer_barrier_bit_ext = 0x00004000,
			gl_buffer_immutable_storage_ext = 0x821f,
			gl_buffer_storage_flags_ext = 0x8220,

			//clip cull distance
			gl_max_clip_distances_ext = 0x0d32,
			gl_clip_distance0_ext = 0x3000,
			gl_clip_distance1_ext = 0x3001,
			gl_clip_distance2_ext = 0x3002,
			gl_clip_distance3_ext = 0x3003,
			gl_clip_distance4_ext = 0x3004,
			gl_clip_distance5_ext = 0x3005,
			gl_clip_distance6_ext = 0x3006,
			gl_clip_distance7_ext = 0x3007,
			gl_max_cull_distances_ext = 0x82f9,
			gl_max_combined_clip_and_cull_distances_ext = 0x82fa,

			//clip volume hint
			gl_clip_volume_clipping_hint_ext = 0x80f0,

			//cmyka
			gl_cmyk_ext = 0x800c,
			gl_cmyka_ext = 0x800d,
			gl_pack_cmyk_hint_ext = 0x800e,
			gl_unpack_cmyk_hint_ext = 0x800f,

			//color buffer half float
			gl_framebuffer_attachment_component_type_ext = 0x8211,
			gl_r16f_ext = 0x822d,
			gl_rg16f_ext = 0x822f,
			gl_rgba16f_ext = 0x881a,
			gl_rgb16f_ext = 0x881b,
			gl_unsigned_normalized_ext = 0x8c17,

			//compiled vertex array
			gl_array_element_lock_first_ext = 0x81a8,
			gl_array_element_lock_count_ext = 0x81a9,

			//convolution
			gl_convolution_1d_ext = 0x8010,
			gl_convolution_2d_ext = 0x8011,
			gl_separable_2d_ext = 0x8012,
			gl_convolution_border_mode_ext = 0x8013,
			gl_convolution_filter_scale_ext = 0x8014,
			gl_convolution_filter_bias_ext = 0x8015,
			gl_reduce_ext = 0x8016,
			gl_convolution_format_ext = 0x8017,
			gl_convolution_width_ext = 0x8018,
			gl_convolution_height_ext = 0x8019,
			gl_max_convolution_width_ext = 0x801a,
			gl_max_convolution_height_ext = 0x801b,
			gl_post_convolution_red_scale_ext = 0x801c,
			gl_post_convolution_green_scale_ext = 0x801d,
			gl_post_convolution_blue_scale_ext = 0x801e,
			gl_post_convolution_alpha_scale_ext = 0x801f,
			gl_post_convolution_red_bias_ext = 0x8020,
			gl_post_convolution_green_bias_ext = 0x8021,
			gl_post_convolution_blue_bias_ext = 0x8022,
			gl_post_convolution_alpha_bias_ext = 0x8023,

			//coordinate frame
			gl_tangent_array_ext = 0x8439,
			gl_binormal_array_ext = 0x843a,
			gl_current_tangent_ext = 0x843b,
			gl_current_binormal_ext = 0x843c,
			gl_tangent_array_type_ext = 0x843e,
			gl_tangent_array_stride_ext = 0x843f,
			gl_binormal_array_type_ext = 0x8440,
			gl_binormal_array_stride_ext = 0x8441,
			gl_tangent_array_pointer_ext = 0x8442,
			gl_binormal_array_pointer_ext = 0x8443,
			gl_map1_tangent_ext = 0x8444,
			gl_map2_tangent_ext = 0x8445,
			gl_map1_binormal_ext = 0x8446,
			gl_map2_binormal_ext = 0x8447,

			//cull vertex
			gl_cull_vertex_ext = 0x81aa,
			gl_cull_vertex_eye_position_ext = 0x81ab,
			gl_cull_vertex_object_position_ext = 0x81ac,

			//debug label
			gl_program_pipeline_object_ext = 0x8a4f,
			gl_program_object_ext = 0x8b40,
			gl_shader_object_ext = 0x8b48,
			gl_buffer_object_ext = 0x9151,
			gl_query_object_ext = 0x9153,
			gl_vertex_array_object_ext = 0x9154,

			//depth bounds test
			gl_depth_bounds_test_ext = 0x8890,
			gl_depth_bounds_ext = 0x8891,

			//direct state access
			gl_program_matrix_ext = 0x8e2d,
			gl_transpose_program_matrix_ext = 0x8e2e,
			gl_program_matrix_stack_depth_ext = 0x8e2f,

			//discard framebuffer
			gl_color_ext = 0x1800,
			gl_depth_ext = 0x1801,
			gl_stencil_ext = 0x1802,

			//draw buffers
			gl_max_draw_buffers_ext = 0x8824,
			gl_draw_buffer0_ext = 0x8825,
			gl_draw_buffer1_ext = 0x8826,
			gl_draw_buffer2_ext = 0x8827,
			gl_draw_buffer3_ext = 0x8828,
			gl_draw_buffer4_ext = 0x8829,
			gl_draw_buffer5_ext = 0x882a,
			gl_draw_buffer6_ext = 0x882b,
			gl_draw_buffer7_ext = 0x882c,
			gl_draw_buffer8_ext = 0x882d,
			gl_draw_buffer9_ext = 0x882e,
			gl_draw_buffer10_ext = 0x882f,
			gl_draw_buffer11_ext = 0x8830,
			gl_draw_buffer12_ext = 0x8831,
			gl_draw_buffer13_ext = 0x8832,
			gl_draw_buffer14_ext = 0x8833,
			gl_draw_buffer15_ext = 0x8834,
			gl_max_color_attachments_ext = 0x8cdf,
			gl_color_attachment0_ext = 0x8ce0,
			gl_color_attachment1_ext = 0x8ce1,
			gl_color_attachment2_ext = 0x8ce2,
			gl_color_attachment3_ext = 0x8ce3,
			gl_color_attachment4_ext = 0x8ce4,
			gl_color_attachment5_ext = 0x8ce5,
			gl_color_attachment6_ext = 0x8ce6,
			gl_color_attachment7_ext = 0x8ce7,
			gl_color_attachment8_ext = 0x8ce8,
			gl_color_attachment9_ext = 0x8ce9,
			gl_color_attachment10_ext = 0x8cea,
			gl_color_attachment11_ext = 0x8ceb,
			gl_color_attachment12_ext = 0x8cec,
			gl_color_attachment13_ext = 0x8ced,
			gl_color_attachment14_ext = 0x8cee,
			gl_color_attachment15_ext = 0x8cef,

			//draw range elements
			gl_max_elements_vertices_ext = 0x80e8,
			gl_max_elements_indices_ext = 0x80e9,

			//fog coord
			gl_fog_coordinate_source_ext = 0x8450,
			gl_fog_coordinate_ext = 0x8451,
			gl_fragment_depth_ext = 0x8452,
			gl_current_fog_coordinate_ext = 0x8453,
			gl_fog_coordinate_array_type_ext = 0x8454,
			gl_fog_coordinate_array_stride_ext = 0x8455,
			gl_fog_coordinate_array_pointer_ext = 0x8456,
			gl_fog_coordinate_array_ext = 0x8457,

			//fragment lighting
			gl_fragment_lighting_ext = 0x8400,
			gl_fragment_color_material_ext = 0x8401,
			gl_fragment_color_material_face_ext = 0x8402,
			gl_fragment_color_material_parameter_ext = 0x8403,
			gl_max_fragment_lights_ext = 0x8404,
			gl_max_active_lights_ext = 0x8405,
			gl_current_raster_normal_ext = 0x8406,
			gl_light_env_mode_ext = 0x8407,
			gl_fragment_light_model_local_viewer_ext = 0x8408,
			gl_fragment_light_model_two_side_ext = 0x8409,
			gl_fragment_light_model_ambient_ext = 0x840a,
			gl_fragment_light_model_normal_interpolation_ext = 0x840b,
			gl_fragment_light0_ext = 0x840c,
			gl_fragment_light7_ext = 0x8413,

			//framebuffer blit
			gl_draw_framebuffer_binding_ext = 0x8ca6,
			gl_read_framebuffer_ext = 0x8ca8,
			gl_draw_framebuffer_ext = 0x8ca9,
			gl_read_framebuffer_binding_ext = 0x8caa,

			//framebuffer multisample
			gl_renderbuffer_samples_ext = 0x8cab,
			gl_framebuffer_incomplete_multisample_ext = 0x8d56,
			gl_max_samples_ext = 0x8d57,

			//framebuffer multisample blit scaled
			gl_scaled_resolve_fastest_ext = 0x90ba,
			gl_scaled_resolve_nicest_ext = 0x90bb,

			//framebuffer object
			gl_invalid_framebuffer_operation_ext = 0x0506,
			gl_max_renderbuffer_size_ext = 0x84e8,
			gl_framebuffer_binding_ext = 0x8ca6,
			gl_renderbuffer_binding_ext = 0x8ca7,
			gl_framebuffer_attachment_object_type_ext = 0x8cd0,
			gl_framebuffer_attachment_object_name_ext = 0x8cd1,
			gl_framebuffer_attachment_texture_level_ext = 0x8cd2,
			gl_framebuffer_attachment_texture_cube_map_face_ext = 0x8cd3,
			gl_framebuffer_attachment_texture_3d_zoffset_ext = 0x8cd4,
			gl_framebuffer_complete_ext = 0x8cd5,
			gl_framebuffer_incomplete_attachment_ext = 0x8cd6,
			gl_framebuffer_incomplete_missing_attachment_ext = 0x8cd7,
			gl_framebuffer_incomplete_dimensions_ext = 0x8cd9,
			gl_framebuffer_incomplete_formats_ext = 0x8cda,
			gl_framebuffer_incomplete_draw_buffer_ext = 0x8cdb,
			gl_framebuffer_incomplete_read_buffer_ext = 0x8cdc,
			gl_framebuffer_unsupported_ext = 0x8cdd,
			//gl_max_color_attachments_ext = 0x8cdf,
			//gl_color_attachment0_ext = 0x8ce0,
			//gl_color_attachment1_ext = 0x8ce1,
			//gl_color_attachment2_ext = 0x8ce2,
			//gl_color_attachment3_ext = 0x8ce3,
			//gl_color_attachment4_ext = 0x8ce4,
			//gl_color_attachment5_ext = 0x8ce5,
			//gl_color_attachment6_ext = 0x8ce6,
			//gl_color_attachment7_ext = 0x8ce7,
			//gl_color_attachment8_ext = 0x8ce8,
			//gl_color_attachment9_ext = 0x8ce9,
			//gl_color_attachment10_ext = 0x8cea,
			//gl_color_attachment11_ext = 0x8ceb,
			//gl_color_attachment12_ext = 0x8cec,
			//gl_color_attachment13_ext = 0x8ced,
			//gl_color_attachment14_ext = 0x8cee,
			//gl_color_attachment15_ext = 0x8cef,
			gl_depth_attachment_ext = 0x8d00,
			gl_stencil_attachment_ext = 0x8d20,
			gl_framebuffer_ext = 0x8d40,
			gl_renderbuffer_ext = 0x8d41,
			gl_renderbuffer_width_ext = 0x8d42,
			gl_renderbuffer_height_ext = 0x8d43,
			gl_renderbuffer_internal_format_ext = 0x8d44,
			gl_stencil_index1_ext = 0x8d46,
			gl_stencil_index4_ext = 0x8d47,
			gl_stencil_index8_ext = 0x8d48,
			gl_stencil_index16_ext = 0x8d49,
			gl_renderbuffer_red_size_ext = 0x8d50,
			gl_renderbuffer_green_size_ext = 0x8d51,
			gl_renderbuffer_blue_size_ext = 0x8d52,
			gl_renderbuffer_alpha_size_ext = 0x8d53,
			gl_renderbuffer_depth_size_ext = 0x8d54,
			gl_renderbuffer_stencil_size_ext = 0x8d55,

			//framebuffer srgb
			gl_framebuffer_srgb_ext = 0x8db9,
			gl_framebuffer_srgb_capable_ext = 0x8dba,

			//geometry point size
			gl_geometry_shader_bit_ext = 0x00000004,
			gl_lines_adjacency_ext = 0xa,
			gl_line_strip_adjacency_ext = 0xb,
			gl_triangles_adjacency_ext = 0xc,
			gl_triangle_strip_adjacency_ext = 0xd,
			gl_layer_provoking_vertex_ext = 0x825e,
			gl_undefined_vertex_ext = 0x8260,
			gl_geometry_shader_invocations_ext = 0x887f,
			gl_geometry_linked_vertices_out_ext = 0x8916,
			gl_geometry_linked_input_type_ext = 0x8917,
			gl_geometry_linked_output_type_ext = 0x8918,
			gl_max_geometry_uniform_blocks_ext = 0x8a2c,
			gl_max_combined_geometry_uniform_components_ext = 0x8a32,
			gl_max_geometry_texture_image_units_ext = 0x8c29,
			gl_primitives_generated_ext = 0x8c87,
			gl_framebuffer_attachment_layered_ext = 0x8da7,
			gl_framebuffer_incomplete_layer_targets_ext = 0x8da8,
			gl_geometry_shader_ext = 0x8dd9,
			gl_max_geometry_uniform_components_ext = 0x8ddf,
			gl_max_geometry_output_vertices_ext = 0x8de0,
			gl_max_geometry_total_output_components_ext = 0x8de1,
			gl_first_vertex_convention_ext = 0x8e4d,
			gl_last_vertex_convention_ext = 0x8e4e,
			gl_max_geometry_shader_invocations_ext = 0x8e5a,
			gl_max_geometry_image_uniforms_ext = 0x90cd,
			gl_max_geometry_shader_storage_blocks_ext = 0x90d7,
			gl_max_geometry_input_components_ext = 0x9123,
			gl_max_geometry_output_components_ext = 0x9124,
			gl_max_geometry_atomic_counter_buffers_ext = 0x92cf,
			gl_max_geometry_atomic_counters_ext = 0x92d5,
			gl_referenced_by_geometry_shader_ext = 0x9309,
			gl_framebuffer_default_layers_ext = 0x9312,
			gl_max_framebuffer_layers_ext = 0x9317,

			//geometry shader
			//gl_geometry_shader_bit_ext = 0x00000004,
			//gl_lines_adjacency_ext = 0xa,
			//gl_line_strip_adjacency_ext = 0xb,
			//gl_triangles_adjacency_ext = 0xc,
			//gl_triangle_strip_adjacency_ext = 0xd,
			//gl_layer_provoking_vertex_ext = 0x825e,
			//gl_undefined_vertex_ext = 0x8260,
			//gl_geometry_shader_invocations_ext = 0x887f,
			//gl_geometry_linked_vertices_out_ext = 0x8916,
			//gl_geometry_linked_input_type_ext = 0x8917,
			//gl_geometry_linked_output_type_ext = 0x8918,
			//gl_max_geometry_uniform_blocks_ext = 0x8a2c,
			//gl_max_combined_geometry_uniform_components_ext = 0x8a32,
			/*gl_max_geometry_texture_image_units_ext = 0x8c29,
			gl_primitives_generated_ext = 0x8c87,
			gl_framebuffer_attachment_layered_ext = 0x8da7,
			gl_framebuffer_incomplete_layer_targets_ext = 0x8da8,
			gl_geometry_shader_ext = 0x8dd9,
			gl_max_geometry_uniform_components_ext = 0x8ddf,
			gl_max_geometry_output_vertices_ext = 0x8de0,
			gl_max_geometry_total_output_components_ext = 0x8de1,
			gl_first_vertex_convention_ext = 0x8e4d,
			gl_last_vertex_convention_ext = 0x8e4e,
			gl_max_geometry_shader_invocations_ext = 0x8e5a,
			gl_max_geometry_image_uniforms_ext = 0x90cd,
			gl_max_geometry_shader_storage_blocks_ext = 0x90d7,
			gl_max_geometry_input_components_ext = 0x9123,
			gl_max_geometry_output_components_ext = 0x9124,
			gl_max_geometry_atomic_counter_buffers_ext = 0x92cf,
			gl_max_geometry_atomic_counters_ext = 0x92d5,
			gl_referenced_by_geometry_shader_ext = 0x9309,
			gl_framebuffer_default_layers_ext = 0x9312,
			gl_max_framebuffer_layers_ext = 0x9317,*/

			//geometry shader4
			/*gl_lines_adjacency_ext = 0xa,
			gl_line_strip_adjacency_ext = 0xb,
			gl_triangles_adjacency_ext = 0xc,
			gl_triangle_strip_adjacency_ext = 0xd,
			gl_program_point_size_ext = 0x8642,
			gl_max_varying_components_ext = 0x8b4b,
			gl_max_geometry_texture_image_units_ext = 0x8c29,
			gl_framebuffer_attachment_texture_layer_ext = 0x8cd4,
			gl_framebuffer_attachment_layered_ext = 0x8da7,
			gl_framebuffer_incomplete_layer_targets_ext = 0x8da8,
			gl_framebuffer_incomplete_layer_count_ext = 0x8da9,
			gl_geometry_shader_ext = 0x8dd9,
			gl_geometry_vertices_out_ext = 0x8dda,
			gl_geometry_input_type_ext = 0x8ddb,
			gl_geometry_output_type_ext = 0x8ddc,
			gl_max_geometry_varying_components_ext = 0x8ddd,
			gl_max_vertex_varying_components_ext = 0x8dde,
			gl_max_geometry_uniform_components_ext = 0x8ddf,
			gl_max_geometry_output_vertices_ext = 0x8de0,
			gl_max_geometry_total_output_components_ext = 0x8de1,*/

			//gpu shader4
			gl_vertex_attrib_array_integer_ext = 0x88fd,
			gl_sampler_1d_array_ext = 0x8dc0,
			gl_sampler_2d_array_ext = 0x8dc1,
			gl_sampler_buffer_ext = 0x8dc2,
			gl_sampler_1d_array_shadow_ext = 0x8dc3,
			gl_sampler_2d_array_shadow_ext = 0x8dc4,
			gl_sampler_cube_shadow_ext = 0x8dc5,
			gl_unsigned_int_vec2_ext = 0x8dc6,
			gl_unsigned_int_vec3_ext = 0x8dc7,
			gl_unsigned_int_vec4_ext = 0x8dc8,
			gl_int_sampler_1d_ext = 0x8dc9,
			gl_int_sampler_2d_ext = 0x8dca,
			gl_int_sampler_3d_ext = 0x8dcb,
			gl_int_sampler_cube_ext = 0x8dcc,
			gl_int_sampler_2d_rect_ext = 0x8dcd,
			gl_int_sampler_1d_array_ext = 0x8dce,
			gl_int_sampler_2d_array_ext = 0x8dcf,
			gl_int_sampler_buffer_ext = 0x8dd0,
			gl_unsigned_int_sampler_1d_ext = 0x8dd1,
			gl_unsigned_int_sampler_2d_ext = 0x8dd2,
			gl_unsigned_int_sampler_3d_ext = 0x8dd3,
			gl_unsigned_int_sampler_cube_ext = 0x8dd4,
			gl_unsigned_int_sampler_2d_rect_ext = 0x8dd5,
			gl_unsigned_int_sampler_1d_array_ext = 0x8dd6,
			gl_unsigned_int_sampler_2d_array_ext = 0x8dd7,
			gl_unsigned_int_sampler_buffer_ext = 0x8dd8,

			//histogram
			gl_histogram_ext = 0x8024,
			gl_proxy_histogram_ext = 0x8025,
			gl_histogram_width_ext = 0x8026,
			gl_histogram_format_ext = 0x8027,
			gl_histogram_red_size_ext = 0x8028,
			gl_histogram_green_size_ext = 0x8029,
			gl_histogram_blue_size_ext = 0x802a,
			gl_histogram_alpha_size_ext = 0x802b,
			gl_histogram_luminance_size_ext = 0x802c,
			gl_histogram_sink_ext = 0x802d,
			gl_minmax_ext = 0x802e,
			gl_minmax_format_ext = 0x802f,
			gl_minmax_sink_ext = 0x8030,

			//instanced arrays
			gl_vertex_attrib_array_divisor_ext = 0x88fe,

			//light texture
			gl_fragment_material_ext = 0x8349,
			gl_fragment_normal_ext = 0x834a,
			gl_fragment_color_ext = 0x834c,
			gl_attenuation_ext = 0x834d,
			gl_shadow_attenuation_ext = 0x834e,
			gl_texture_application_mode_ext = 0x834f,
			gl_texture_light_ext = 0x8350,
			gl_texture_material_face_ext = 0x8351,
			gl_texture_material_parameter_ext = 0x8352,

			//map buffer range
			gl_map_read_bit_ext = 0x0001,
			gl_map_write_bit_ext = 0x0002,
			gl_map_invalidate_range_bit_ext = 0x0004,
			gl_map_invalidate_buffer_bit_ext = 0x0008,
			gl_map_flush_explicit_bit_ext = 0x0010,
			gl_map_unsynchronized_bit_ext = 0x0020,

			//memory object
			gl_uuid_size_ext = 16,
			gl_texture_tiling_ext = 0x9580,
			gl_dedicated_memory_object_ext = 0x9581,
			gl_num_tiling_types_ext = 0x9582,
			gl_tiling_types_ext = 0x9583,
			gl_optimal_tiling_ext = 0x9584,
			gl_linear_tiling_ext = 0x9585,
			gl_layout_general_ext = 0x958d,
			gl_layout_color_attachment_ext = 0x958e,
			gl_layout_depth_stencil_attachment_ext = 0x958f,
			gl_layout_depth_stencil_read_only_ext = 0x9590,
			gl_layout_shader_read_only_ext = 0x9591,
			gl_layout_transfer_src_ext = 0x9592,
			gl_layout_transfer_dst_ext = 0x9593,
			gl_num_device_uuids_ext = 0x9596,
			gl_device_uuid_ext = 0x9597,
			gl_driver_uuid_ext = 0x9598,
			gl_protected_memory_object_ext = 0x959b,

			//memory object fd
			gl_handle_type_opaque_fd_ext = 0x9586,

			//memory object win32
			gl_luid_size_ext = 8,
			gl_handle_type_opaque_win32_ext = 0x9587,
			gl_handle_type_opaque_win32_kmt_ext = 0x9588,
			gl_handle_type_d3d12_tilepool_ext = 0x9589,
			gl_handle_type_d3d12_resource_ext = 0x958a,
			gl_handle_type_d3d11_image_ext = 0x958b,
			gl_handle_type_d3d11_image_kmt_ext = 0x958c,
			gl_handle_type_d3d12_fence_ext = 0x9594,
			gl_d3d12_fence_value_ext = 0x9595,
			gl_device_luid_ext = 0x9599,
			gl_device_node_mask_ext = 0x959a,

			//multisample
			gl_multisample_ext = 0x809d,
			gl_sample_alpha_to_mask_ext = 0x809e,
			gl_sample_alpha_to_one_ext = 0x809f,
			gl_sample_mask_ext = 0x80a0,
			gl_1pass_ext = 0x80a1,
			gl_2pass_0_ext = 0x80a2,
			gl_2pass_1_ext = 0x80a3,
			gl_4pass_0_ext = 0x80a4,
			gl_4pass_1_ext = 0x80a5,
			gl_4pass_2_ext = 0x80a6,
			gl_4pass_3_ext = 0x80a7,
			gl_sample_buffers_ext = 0x80a8,
			gl_samples_ext = 0x80a9,
			gl_sample_mask_value_ext = 0x80aa,
			gl_sample_mask_invert_ext = 0x80ab,
			gl_sample_pattern_ext = 0x80ac,
			gl_multisample_bit_ext = 0x20000000,

			//multisample compatibility 
			/*gl_multisample_ext = 0x809d,
			gl_sample_alpha_to_one_ext = 0x809f,*/

			//multisampled_render_to_texture,
			/*gl_renderbuffer_samples_ext = 0x8cab,
			gl_framebuffer_incomplete_multisample_ext = 0x8d56,
			gl_max_samples_ext = 0x8d57,*/
			gl_framebuffer_attachment_texture_samples_ext = 0x8d6c,

			//multiview_draw_buffers,
			gl_draw_buffer_ext = 0x0c01,
			gl_read_buffer_ext = 0x0c02,
			gl_color_attachment_ext = 0x90f0,
			gl_multiview_ext = 0x90f1,
			gl_max_multiview_buffers_ext = 0x90f2,

			//packed_depth_stencil,
			gl_depth_stencil_ext = 0x84f9,
			gl_unsigned_int_24_8_ext = 0x84fa,
			gl_depth24_stencil8_ext = 0x88f0,
			gl_texture_stencil_size_ext = 0x88f1,

			//packed_float,
			gl_r11f_g11f_b10f_ext = 0x8c3a,
			gl_unsigned_int_10f_11f_11f_rev_ext = 0x8c3b,
			gl_rgba_signed_components_ext = 0x8c3c,

			//packed_pixels,
			gl_unsigned_byte_3_3_2_ext = 0x8032,
			gl_unsigned_short_4_4_4_4_ext = 0x8033,
			gl_unsigned_short_5_5_5_1_ext = 0x8034,
			gl_unsigned_int_8_8_8_8_ext = 0x8035,
			gl_unsigned_int_10_10_10_2_ext = 0x8036,

			//paletted_texture,
			gl_texture_1d = 0x0de0,
			gl_texture_2d = 0x0de1,
			gl_proxy_texture_1d = 0x8063,
			gl_proxy_texture_2d = 0x8064,
			gl_color_table_format_ext = 0x80d8,
			gl_color_table_width_ext = 0x80d9,
			gl_color_table_red_size_ext = 0x80da,
			gl_color_table_green_size_ext = 0x80db,
			gl_color_table_blue_size_ext = 0x80dc,
			gl_color_table_alpha_size_ext = 0x80dd,
			gl_color_table_luminance_size_ext = 0x80de,
			gl_color_table_intensity_size_ext = 0x80df,
			gl_color_index1_ext = 0x80e2,
			gl_color_index2_ext = 0x80e3,
			gl_color_index4_ext = 0x80e4,
			gl_color_index8_ext = 0x80e5,
			gl_color_index12_ext = 0x80e6,
			gl_color_index16_ext = 0x80e7,
			gl_texture_index_size_ext = 0x80ed,
			/*gl_texture_cube_map_arb = 0x8513,
			gl_proxy_texture_cube_map_arb = 0x851b,*/

			//pixel_buffer_object,
			gl_pixel_pack_buffer_ext = 0x88eb,
			gl_pixel_unpack_buffer_ext = 0x88ec,
			gl_pixel_pack_buffer_binding_ext = 0x88ed,
			gl_pixel_unpack_buffer_binding_ext = 0x88ef,

			//pixel_transform,
			gl_pixel_transform_2d_ext = 0x8330,
			gl_pixel_mag_filter_ext = 0x8331,
			gl_pixel_min_filter_ext = 0x8332,
			gl_pixel_cubic_weight_ext = 0x8333,
			gl_cubic_ext = 0x8334,
			gl_average_ext = 0x8335,
			gl_pixel_transform_2d_stack_depth_ext = 0x8336,
			gl_max_pixel_transform_2d_stack_depth_ext = 0x8337,
			gl_pixel_transform_2d_matrix_ext = 0x8338,

			//point_parameters,
			gl_point_size_min_ext = 0x8126,
			gl_point_size_max_ext = 0x8127,
			gl_point_fade_threshold_size_ext = 0x8128,
			gl_distance_attenuation_ext = 0x8129,

			//polygon_offset,
			gl_polygon_offset_ext = 0x8037,
			gl_polygon_offset_factor_ext = 0x8038,
			gl_polygon_offset_bias_ext = 0x8039,

			//polygon_offset_clamp,
			gl_polygon_offset_clamp_ext = 0x8e1b,

			//provoking_vertex,
			gl_quads_follow_provoking_vertex_convention_ext = 0x8e4c,
			/*gl_first_vertex_convention_ext = 0x8e4d,
			gl_last_vertex_convention_ext = 0x8e4e,*/
			gl_provoking_vertex_ext = 0x8e4f,

			//pvrtc_srgb,
			gl_compressed_srgb_pvrtc_2bppv1_ext = 0x8a54,
			gl_compressed_srgb_pvrtc_4bppv1_ext = 0x8a55,
			gl_compressed_srgb_alpha_pvrtc_2bppv1_ext = 0x8a56,
			gl_compressed_srgb_alpha_pvrtc_4bppv1_ext = 0x8a57,

			//raster_multisample,
			gl_color_samples_nv = 0x8e20,
			gl_raster_multisample_ext = 0x9327,
			gl_raster_samples_ext = 0x9328,
			gl_max_raster_samples_ext = 0x9329,
			gl_raster_fixed_sample_locations_ext = 0x932a,
			gl_multisample_rasterization_allowed_ext = 0x932b,
			gl_effective_raster_samples_ext = 0x932c,
			gl_depth_samples_nv = 0x932d,
			gl_stencil_samples_nv = 0x932e,
			gl_mixed_depth_samples_supported_nv = 0x932f,
			gl_mixed_stencil_samples_supported_nv = 0x9330,
			gl_coverage_modulation_table_nv = 0x9331,
			gl_coverage_modulation_nv = 0x9332,
			gl_coverage_modulation_table_size_nv = 0x9333,

			//read_format_bgra,
			//gl_bgra_ext = 0x80e1,
			gl_unsigned_short_4_4_4_4_rev_ext = 0x8365,
			gl_unsigned_short_1_5_5_5_rev_ext = 0x8366,

			//render_snorm,
			gl_byte = 0x1400,
			gl_short = 0x1402,
			/*gl_r8_snorm = 0x8f94,
			gl_rg8_snorm = 0x8f95,
			gl_rgba8_snorm = 0x8f97,*/
			gl_r16_snorm_ext = 0x8f98,
			gl_rg16_snorm_ext = 0x8f99,
			gl_rgba16_snorm_ext = 0x8f9b,

			//rescale_normal,
			gl_rescale_normal_ext = 0x803a,

			//srgb,
			gl_framebuffer_attachment_color_encoding_ext = 0x8210,
			gl_srgb_ext = 0x8c40,
			gl_srgb_alpha_ext = 0x8c42,
			gl_srgb8_alpha8_ext = 0x8c43,

			//srgb_write_control,
			//gl_framebuffer_srgb_ext = 0x8db9,

			//secondary_color,
			gl_color_sum_ext = 0x8458,
			gl_current_secondary_color_ext = 0x8459,
			gl_secondary_color_array_size_ext = 0x845a,
			gl_secondary_color_array_type_ext = 0x845b,
			gl_secondary_color_array_stride_ext = 0x845c,
			gl_secondary_color_array_pointer_ext = 0x845d,
			gl_secondary_color_array_ext = 0x845e,

			//separate_shader_objects,
			gl_active_program_ext = 0x8b8d,

			//separate_specular_color,
			gl_light_model_color_control_ext = 0x81f8,
			gl_single_color_ext = 0x81f9,
			gl_separate_specular_color_ext = 0x81fa,

			//shader_framebuffer_fetch,
			gl_fragment_shader_discards_samples_ext = 0x8a52,

			//shader_image_load_store,
			gl_vertex_attrib_array_barrier_bit_ext = 0x00000001,
			gl_element_array_barrier_bit_ext = 0x00000002,
			gl_uniform_barrier_bit_ext = 0x00000004,
			gl_texture_fetch_barrier_bit_ext = 0x00000008,
			gl_shader_image_access_barrier_bit_ext = 0x00000020,
			gl_command_barrier_bit_ext = 0x00000040,
			gl_pixel_buffer_barrier_bit_ext = 0x00000080,
			gl_texture_update_barrier_bit_ext = 0x00000100,
			gl_buffer_update_barrier_bit_ext = 0x00000200,
			gl_framebuffer_barrier_bit_ext = 0x00000400,
			gl_transform_feedback_barrier_bit_ext = 0x00000800,
			gl_atomic_counter_barrier_bit_ext = 0x00001000,
			gl_max_image_units_ext = 0x8f38,
			gl_max_combined_image_units_and_fragment_outputs_ext = 0x8f39,
			gl_image_binding_name_ext = 0x8f3a,
			gl_image_binding_level_ext = 0x8f3b,
			gl_image_binding_layered_ext = 0x8f3c,
			gl_image_binding_layer_ext = 0x8f3d,
			gl_image_binding_access_ext = 0x8f3e,
			gl_image_1d_ext = 0x904c,
			gl_image_2d_ext = 0x904d,
			gl_image_3d_ext = 0x904e,
			gl_image_2d_rect_ext = 0x904f,
			gl_image_cube_ext = 0x9050,
			gl_image_buffer_ext = 0x9051,
			gl_image_1d_array_ext = 0x9052,
			gl_image_2d_array_ext = 0x9053,
			gl_image_cube_map_array_ext = 0x9054,
			gl_image_2d_multisample_ext = 0x9055,
			gl_image_2d_multisample_array_ext = 0x9056,
			gl_int_image_1d_ext = 0x9057,
			gl_int_image_2d_ext = 0x9058,
			gl_int_image_3d_ext = 0x9059,
			gl_int_image_2d_rect_ext = 0x905a,
			gl_int_image_cube_ext = 0x905b,
			gl_int_image_buffer_ext = 0x905c,
			gl_int_image_1d_array_ext = 0x905d,
			gl_int_image_2d_array_ext = 0x905e,
			gl_int_image_cube_map_array_ext = 0x905f,
			gl_int_image_2d_multisample_ext = 0x9060,
			gl_int_image_2d_multisample_array_ext = 0x9061,
			gl_unsigned_int_image_1d_ext = 0x9062,
			gl_unsigned_int_image_2d_ext = 0x9063,
			gl_unsigned_int_image_3d_ext = 0x9064,
			gl_unsigned_int_image_2d_rect_ext = 0x9065,
			gl_unsigned_int_image_cube_ext = 0x9066,
			gl_unsigned_int_image_buffer_ext = 0x9067,
			gl_unsigned_int_image_1d_array_ext = 0x9068,
			gl_unsigned_int_image_2d_array_ext = 0x9069,
			gl_unsigned_int_image_cube_map_array_ext = 0x906a,
			gl_unsigned_int_image_2d_multisample_ext = 0x906b,
			gl_unsigned_int_image_2d_multisample_array_ext = 0x906c,
			gl_max_image_samples_ext = 0x906d,
			gl_image_binding_format_ext = 0x906e,
			gl_all_barrier_bits_ext = 0xffffffff,

			//shader_pixel_local_storage,
			gl_max_shader_pixel_local_storage_fast_size_ext = 0x8f63,
			gl_shader_pixel_local_storage_ext = 0x8f64,
			gl_max_shader_pixel_local_storage_size_ext = 0x8f67,

			//shader_pixel_local_storage2,
			gl_max_shader_combined_local_storage_fast_size_ext = 0x9650,
			gl_max_shader_combined_local_storage_size_ext = 0x9651,
			gl_framebuffer_incomplete_insufficient_shader_combined_local_storage_ext = 0x9652,

			//shadow_samplers,
			gl_texture_compare_mode_ext = 0x884c,
			gl_texture_compare_func_ext = 0x884d,
			gl_compare_ref_to_texture_ext = 0x884e,
			gl_sampler_2d_shadow_ext = 0x8b62,

			//shared_texture_palette,
			gl_shared_texture_palette_ext = 0x81fb,

			//sparse_texture,
			/*gl_texture_2d = 0x0de1,
			gl_texture_3d = 0x806f,
			gl_texture_cube_map = 0x8513,
			gl_texture_2d_array = 0x8c1a,*/
			gl_texture_cube_map_array_oes = 0x9009,
			gl_virtual_page_size_x_ext = 0x9195,
			gl_virtual_page_size_y_ext = 0x9196,
			gl_virtual_page_size_z_ext = 0x9197,
			gl_max_sparse_texture_size_ext = 0x9198,
			gl_max_sparse_3d_texture_size_ext = 0x9199,
			gl_max_sparse_array_texture_layers_ext = 0x919a,
			gl_texture_sparse_ext = 0x91a6,
			gl_virtual_page_size_index_ext = 0x91a7,
			gl_num_virtual_page_sizes_ext = 0x91a8,
			gl_sparse_texture_full_array_cube_mipmaps_ext = 0x91a9,
			gl_num_sparse_levels_ext = 0x91aa,

			//stencil_clear_tag,
			gl_stencil_tag_bits_ext = 0x88f2,
			gl_stencil_clear_tag_value_ext = 0x88f3,

			//stencil_two_side,
			gl_stencil_test_two_side_ext = 0x8910,
			gl_active_stencil_face_ext = 0x8911,

			//stencil_wrap,
			gl_incr_wrap_ext = 0x8507,
			gl_decr_wrap_ext = 0x8508,

			//texture,
			gl_alpha4_ext = 0x803b,
			gl_alpha8_ext = 0x803c,
			gl_alpha12_ext = 0x803d,
			gl_alpha16_ext = 0x803e,
			gl_luminance4_ext = 0x803f,
			gl_luminance8_ext = 0x8040,
			gl_luminance12_ext = 0x8041,
			gl_luminance16_ext = 0x8042,
			gl_luminance4_alpha4_ext = 0x8043,
			gl_luminance6_alpha2_ext = 0x8044,
			gl_luminance8_alpha8_ext = 0x8045,
			gl_luminance12_alpha4_ext = 0x8046,
			gl_luminance12_alpha12_ext = 0x8047,
			gl_luminance16_alpha16_ext = 0x8048,
			gl_intensity_ext = 0x8049,
			gl_intensity4_ext = 0x804a,
			gl_intensity8_ext = 0x804b,
			gl_intensity12_ext = 0x804c,
			gl_intensity16_ext = 0x804d,
			gl_rgb2_ext = 0x804e,
			gl_rgb4_ext = 0x804f,
			gl_rgb5_ext = 0x8050,
			gl_rgb8_ext = 0x8051,
			gl_rgb10_ext = 0x8052,
			gl_rgb12_ext = 0x8053,
			gl_rgb16_ext = 0x8054,
			gl_rgba2_ext = 0x8055,
			gl_rgba4_ext = 0x8056,
			gl_rgb5_a1_ext = 0x8057,
			gl_rgba8_ext = 0x8058,
			gl_rgb10_a2_ext = 0x8059,
			gl_rgba12_ext = 0x805a,
			gl_rgba16_ext = 0x805b,
			gl_texture_red_size_ext = 0x805c,
			gl_texture_green_size_ext = 0x805d,
			gl_texture_blue_size_ext = 0x805e,
			gl_texture_alpha_size_ext = 0x805f,
			gl_texture_luminance_size_ext = 0x8060,
			gl_texture_intensity_size_ext = 0x8061,
			gl_replace_ext = 0x8062,
			gl_proxy_texture_1d_ext = 0x8063,
			gl_proxy_texture_2d_ext = 0x8064,

			//texture3d,
			gl_pack_skip_images_ext = 0x806b,
			gl_pack_image_height_ext = 0x806c,
			gl_unpack_skip_images_ext = 0x806d,
			gl_unpack_image_height_ext = 0x806e,
			gl_texture_3d_ext = 0x806f,
			gl_proxy_texture_3d_ext = 0x8070,
			gl_texture_depth_ext = 0x8071,
			gl_texture_wrap_r_ext = 0x8072,
			gl_max_3d_texture_size_ext = 0x8073,

			//texture_array,
			gl_compare_ref_depth_to_texture_ext = 0x884e,
			gl_max_array_texture_layers_ext = 0x88ff,
			gl_texture_1d_array_ext = 0x8c18,
			gl_proxy_texture_1d_array_ext = 0x8c19,
			gl_texture_2d_array_ext = 0x8c1a,
			gl_proxy_texture_2d_array_ext = 0x8c1b,
			gl_texture_binding_1d_array_ext = 0x8c1c,
			gl_texture_binding_2d_array_ext = 0x8c1d,

			//texture_buffer_object,
			gl_texture_buffer_ext = 0x8c2a,
			gl_max_texture_buffer_size_ext = 0x8c2b,
			gl_texture_binding_buffer_ext = 0x8c2c,
			gl_texture_buffer_data_store_binding_ext = 0x8c2d,
			gl_texture_buffer_format_ext = 0x8c2e,

			//texture_compression_astc_decode_mode_rgb9e5,
			gl_texture_astc_decode_precision_ext = 0x8f69,

			//texture_compression_bptc,
			gl_compressed_rgba_bptc_unorm_ext = 0x8e8c,
			gl_compressed_srgb_alpha_bptc_unorm_ext = 0x8e8d,
			gl_compressed_rgb_bptc_signed_float_ext = 0x8e8e,
			gl_compressed_rgb_bptc_unsigned_float_ext = 0x8e8f,

			//texture_compression_latc,
			gl_compressed_luminance_latc1_ext = 0x8c70,
			gl_compressed_signed_luminance_latc1_ext = 0x8c71,
			gl_compressed_luminance_alpha_latc2_ext = 0x8c72,
			gl_compressed_signed_luminance_alpha_latc2_ext = 0x8c73,

			//texture_compression_rgtc,
			gl_compressed_red_rgtc1_ext = 0x8dbb,
			gl_compressed_signed_red_rgtc1_ext = 0x8dbc,
			gl_compressed_red_green_rgtc2_ext = 0x8dbd,
			gl_compressed_signed_red_green_rgtc2_ext = 0x8dbe,

			//texture_compression_s3tc,
			gl_compressed_rgb_s3tc_dxt1_ext = 0x83f0,
			gl_compressed_rgba_s3tc_dxt1_ext = 0x83f1,
			gl_compressed_rgba_s3tc_dxt3_ext = 0x83f2,
			gl_compressed_rgba_s3tc_dxt5_ext = 0x83f3,

			//texture_cube_map,
			gl_normal_map_ext = 0x8511,
			gl_reflection_map_ext = 0x8512,
			gl_texture_cube_map_ext = 0x8513,
			gl_texture_binding_cube_map_ext = 0x8514,
			gl_texture_cube_map_positive_x_ext = 0x8515,
			gl_texture_cube_map_negative_x_ext = 0x8516,
			gl_texture_cube_map_positive_y_ext = 0x8517,
			gl_texture_cube_map_negative_y_ext = 0x8518,
			gl_texture_cube_map_positive_z_ext = 0x8519,
			gl_texture_cube_map_negative_z_ext = 0x851a,
			gl_proxy_texture_cube_map_ext = 0x851b,
			gl_max_cube_map_texture_size_ext = 0x851c,

			//texture_cube_map_array,
			gl_texture_cube_map_array_ext = 0x9009,
			gl_texture_binding_cube_map_array_ext = 0x900a,
			gl_sampler_cube_map_array_ext = 0x900c,
			gl_sampler_cube_map_array_shadow_ext = 0x900d,
			gl_int_sampler_cube_map_array_ext = 0x900e,
			gl_unsigned_int_sampler_cube_map_array_ext = 0x900f,
			/*gl_image_cube_map_array_ext = 0x9054,
			gl_int_image_cube_map_array_ext = 0x905f,
			gl_unsigned_int_image_cube_map_array_ext = 0x906a,*/

			//texture_edge_clamp,
			gl_clamp_to_edge_ext = 0x812f,

			//texture_env_combine,
			gl_combine_ext = 0x8570,
			gl_combine_rgb_ext = 0x8571,
			gl_combine_alpha_ext = 0x8572,
			gl_rgb_scale_ext = 0x8573,
			gl_add_signed_ext = 0x8574,
			gl_interpolate_ext = 0x8575,
			gl_constant_ext = 0x8576,
			gl_primary_color_ext = 0x8577,
			gl_previous_ext = 0x8578,
			gl_source0_rgb_ext = 0x8580,
			gl_source1_rgb_ext = 0x8581,
			gl_source2_rgb_ext = 0x8582,
			gl_source0_alpha_ext = 0x8588,
			gl_source1_alpha_ext = 0x8589,
			gl_source2_alpha_ext = 0x858a,
			gl_operand0_rgb_ext = 0x8590,
			gl_operand1_rgb_ext = 0x8591,
			gl_operand2_rgb_ext = 0x8592,
			gl_operand0_alpha_ext = 0x8598,
			gl_operand1_alpha_ext = 0x8599,
			gl_operand2_alpha_ext = 0x859a,

			//texture_env_dot3,
			gl_dot3_rgb_ext = 0x8740,
			gl_dot3_rgba_ext = 0x8741,

			//texture_filter_anisotropic,
			gl_texture_max_anisotropy_ext = 0x84fe,
			gl_max_texture_max_anisotropy_ext = 0x84ff,

			//texture_filter_minmax,
			gl_texture_reduction_mode_ext = 0x9366,
			gl_weighted_average_ext = 0x9367,

			//texture_format_bgra8888,
			//gl_bgra_ext = 0x80e1,

			//texture_integer,
			gl_rgba32ui_ext = 0x8d70,
			gl_rgb32ui_ext = 0x8d71,
			gl_alpha32ui_ext = 0x8d72,
			gl_intensity32ui_ext = 0x8d73,
			gl_luminance32ui_ext = 0x8d74,
			gl_luminance_alpha32ui_ext = 0x8d75,
			gl_rgba16ui_ext = 0x8d76,
			gl_rgb16ui_ext = 0x8d77,
			gl_alpha16ui_ext = 0x8d78,
			gl_intensity16ui_ext = 0x8d79,
			gl_luminance16ui_ext = 0x8d7a,
			gl_luminance_alpha16ui_ext = 0x8d7b,
			gl_rgba8ui_ext = 0x8d7c,
			gl_rgb8ui_ext = 0x8d7d,
			gl_alpha8ui_ext = 0x8d7e,
			gl_intensity8ui_ext = 0x8d7f,
			gl_luminance8ui_ext = 0x8d80,
			gl_luminance_alpha8ui_ext = 0x8d81,
			gl_rgba32i_ext = 0x8d82,
			gl_rgb32i_ext = 0x8d83,
			gl_alpha32i_ext = 0x8d84,
			gl_intensity32i_ext = 0x8d85,
			gl_luminance32i_ext = 0x8d86,
			gl_luminance_alpha32i_ext = 0x8d87,
			gl_rgba16i_ext = 0x8d88,
			gl_rgb16i_ext = 0x8d89,
			gl_alpha16i_ext = 0x8d8a,
			gl_intensity16i_ext = 0x8d8b,
			gl_luminance16i_ext = 0x8d8c,
			gl_luminance_alpha16i_ext = 0x8d8d,
			gl_rgba8i_ext = 0x8d8e,
			gl_rgb8i_ext = 0x8d8f,
			gl_alpha8i_ext = 0x8d90,
			gl_intensity8i_ext = 0x8d91,
			gl_luminance8i_ext = 0x8d92,
			gl_luminance_alpha8i_ext = 0x8d93,
			gl_red_integer_ext = 0x8d94,
			gl_green_integer_ext = 0x8d95,
			gl_blue_integer_ext = 0x8d96,
			gl_alpha_integer_ext = 0x8d97,
			gl_rgb_integer_ext = 0x8d98,
			gl_rgba_integer_ext = 0x8d99,
			gl_bgr_integer_ext = 0x8d9a,
			gl_bgra_integer_ext = 0x8d9b,
			gl_luminance_integer_ext = 0x8d9c,
			gl_luminance_alpha_integer_ext = 0x8d9d,
			gl_rgba_integer_mode_ext = 0x8d9e,

			//texture_lod_bias,
			gl_max_texture_lod_bias_ext = 0x84fd,
			gl_texture_filter_control_ext = 0x8500,
			gl_texture_lod_bias_ext = 0x8501,

			//texture_mirror_clamp,
			gl_mirror_clamp_ext = 0x8742,
			gl_mirror_clamp_to_edge_ext = 0x8743,
			gl_mirror_clamp_to_border_ext = 0x8912,

			//texture_norm16,
			/*gl_rgb16_ext = 0x8054,
			gl_rgba16_ext = 0x805b,*/
			gl_r16_ext = 0x822a,
			gl_rg16_ext = 0x822c,
			//gl_r16_snorm_ext = 0x8f98,
			//gl_rg16_snorm_ext = 0x8f99,
			gl_rgb16_snorm_ext = 0x8f9a,
			//gl_rgba16_snorm_ext = 0x8f9b,

			//texture_object,
			gl_texture_priority_ext = 0x8066,
			gl_texture_resident_ext = 0x8067,
			gl_texture_1d_binding_ext = 0x8068,
			gl_texture_2d_binding_ext = 0x8069,
			gl_texture_3d_binding_ext = 0x806a,

			//texture_perturb_normal,
			gl_perturb_ext = 0x85ae,
			gl_texture_normal_ext = 0x85af,

			//texture_rectangle,
			gl_texture_rectangle_ext = 0x84f5,
			gl_texture_binding_rectangle_ext = 0x84f6,
			gl_proxy_texture_rectangle_ext = 0x84f7,
			gl_max_rectangle_texture_size_ext = 0x84f8,

			//texture_rg,
			gl_red_ext = 0x1903,
			gl_rg_ext = 0x8227,
			gl_r8_ext = 0x8229,
			gl_rg8_ext = 0x822b,

			//texture_srgb,
			//gl_srgb_ext = 0x8c40,
			gl_srgb8_ext = 0x8c41,
			//gl_srgb_alpha_ext = 0x8c42,
			//gl_srgb8_alpha8_ext = 0x8c43,
			gl_sluminance_alpha_ext = 0x8c44,
			gl_sluminance8_alpha8_ext = 0x8c45,
			gl_sluminance_ext = 0x8c46,
			gl_sluminance8_ext = 0x8c47,
			gl_compressed_srgb_ext = 0x8c48,
			gl_compressed_srgb_alpha_ext = 0x8c49,
			gl_compressed_sluminance_ext = 0x8c4a,
			gl_compressed_sluminance_alpha_ext = 0x8c4b,
			gl_compressed_srgb_s3tc_dxt1_ext = 0x8c4c,
			gl_compressed_srgb_alpha_s3tc_dxt1_ext = 0x8c4d,
			gl_compressed_srgb_alpha_s3tc_dxt3_ext = 0x8c4e,
			gl_compressed_srgb_alpha_s3tc_dxt5_ext = 0x8c4f,

			//texture_srgb_r8,
			gl_sr8_ext = 0x8fbd,

			//texture_srgb_rg8,
			gl_srg8_ext = 0x8fbe,

			//texture_srgb_decode,
			gl_texture_srgb_decode_ext = 0x8a48,
			gl_decode_ext = 0x8a49,
			gl_skip_decode_ext = 0x8a4a,

			//texture_shared_exponent,
			gl_rgb9_e5_ext = 0x8c3d,
			gl_unsigned_int_5_9_9_9_rev_ext = 0x8c3e,
			gl_texture_shared_size_ext = 0x8c3f,

			//texture_snorm,
			/*gl_red_snorm = 0x8f90,
			gl_rg_snorm = 0x8f91,
			gl_rgb_snorm = 0x8f92,
			gl_rgba_snorm = 0x8f93,
			gl_r8_snorm = 0x8f94,
			gl_rg8_snorm = 0x8f95,
			gl_rgb8_snorm = 0x8f96,
			gl_rgba8_snorm = 0x8f97,
			gl_r16_snorm = 0x8f98,
			gl_rg16_snorm = 0x8f99,
			gl_rgb16_snorm = 0x8f9a,
			gl_rgba16_snorm = 0x8f9b,
			gl_signed_normalized = 0x8f9c,*/
			gl_alpha_snorm = 0x9010,
			gl_luminance_snorm = 0x9011,
			gl_luminance_alpha_snorm = 0x9012,
			gl_intensity_snorm = 0x9013,
			gl_alpha8_snorm = 0x9014,
			gl_luminance8_snorm = 0x9015,
			gl_luminance8_alpha8_snorm = 0x9016,
			gl_intensity8_snorm = 0x9017,
			gl_alpha16_snorm = 0x9018,
			gl_luminance16_snorm = 0x9019,
			gl_luminance16_alpha16_snorm = 0x901a,
			gl_intensity16_snorm = 0x901b,

			//texture_storage,
			/*gl_alpha8_ext = 0x803c,
			gl_luminance8_ext = 0x8040,
			gl_luminance8_alpha8_ext = 0x8045,
			gl_rgb10_ext = 0x8052,
			gl_rgb10_a2_ext = 0x8059,
			gl_r8_ext = 0x8229,
			gl_rg8_ext = 0x822b,
			gl_r16f_ext = 0x822d,*/
			gl_r32f_ext = 0x822e,
			//gl_rg16f_ext = 0x822f,
			gl_rg32f_ext = 0x8230,
			gl_rgba32f_ext = 0x8814,
			gl_rgb32f_ext = 0x8815,
			gl_alpha32f_ext = 0x8816,
			gl_luminance32f_ext = 0x8818,
			gl_luminance_alpha32f_ext = 0x8819,
			//gl_rgba16f_ext = 0x881a,
			//gl_rgb16f_ext = 0x881b,
			gl_alpha16f_ext = 0x881c,
			gl_luminance16f_ext = 0x881e,
			gl_luminance_alpha16f_ext = 0x881f,
			//gl_rgb_raw_422_apple = 0x8a51,
			gl_texture_immutable_format_ext = 0x912f,
			//gl_bgra8_ext = 0x93a1,

			//texture_swizzle,
			gl_texture_swizzle_r_ext = 0x8e42,
			gl_texture_swizzle_g_ext = 0x8e43,
			gl_texture_swizzle_b_ext = 0x8e44,
			gl_texture_swizzle_a_ext = 0x8e45,
			gl_texture_swizzle_rgba_ext = 0x8e46,

			//texture_type_2_10_10_10_rev,
			gl_unsigned_int_2_10_10_10_rev_ext = 0x8368,

			//texture_view,
			gl_texture_view_min_level_ext = 0x82db,
			gl_texture_view_num_levels_ext = 0x82dc,
			gl_texture_view_min_layer_ext = 0x82dd,
			gl_texture_view_num_layers_ext = 0x82de,
			//gl_texture_immutable_levels = 0x82df,

			//timer_query,
			gl_time_elapsed_ext = 0x88bf,

			//transform_feedback,
			gl_transform_feedback_varying_max_length_ext = 0x8c76,
			gl_transform_feedback_buffer_mode_ext = 0x8c7f,
			gl_max_transform_feedback_separate_components_ext = 0x8c80,
			gl_transform_feedback_varyings_ext = 0x8c83,
			gl_transform_feedback_buffer_start_ext = 0x8c84,
			gl_transform_feedback_buffer_size_ext = 0x8c85,
			//gl_primitives_generated_ext = 0x8c87,
			gl_transform_feedback_primitives_written_ext = 0x8c88,
			gl_rasterizer_discard_ext = 0x8c89,
			gl_max_transform_feedback_interleaved_components_ext = 0x8c8a,
			gl_max_transform_feedback_separate_attribs_ext = 0x8c8b,
			gl_interleaved_attribs_ext = 0x8c8c,
			gl_separate_attribs_ext = 0x8c8d,
			gl_transform_feedback_buffer_ext = 0x8c8e,
			gl_transform_feedback_buffer_binding_ext = 0x8c8f,

			//unpack_subimage,
			gl_unpack_row_length_ext = 0x0cf2,
			gl_unpack_skip_rows_ext = 0x0cf3,
			gl_unpack_skip_pixels_ext = 0x0cf4,

			//vertex_array,
			gl_double_ext = 0x140a,
			gl_vertex_array_ext = 0x8074,
			gl_normal_array_ext = 0x8075,
			gl_color_array_ext = 0x8076,
			gl_index_array_ext = 0x8077,
			gl_texture_coord_array_ext = 0x8078,
			gl_edge_flag_array_ext = 0x8079,
			gl_vertex_array_size_ext = 0x807a,
			gl_vertex_array_type_ext = 0x807b,
			gl_vertex_array_stride_ext = 0x807c,
			gl_vertex_array_count_ext = 0x807d,
			gl_normal_array_type_ext = 0x807e,
			gl_normal_array_stride_ext = 0x807f,
			gl_normal_array_count_ext = 0x8080,
			gl_color_array_size_ext = 0x8081,
			gl_color_array_type_ext = 0x8082,
			gl_color_array_stride_ext = 0x8083,
			gl_color_array_count_ext = 0x8084,
			gl_index_array_type_ext = 0x8085,
			gl_index_array_stride_ext = 0x8086,
			gl_index_array_count_ext = 0x8087,
			gl_texture_coord_array_size_ext = 0x8088,
			gl_texture_coord_array_type_ext = 0x8089,
			gl_texture_coord_array_stride_ext = 0x808a,
			gl_texture_coord_array_count_ext = 0x808b,
			gl_edge_flag_array_stride_ext = 0x808c,
			gl_edge_flag_array_count_ext = 0x808d,
			gl_vertex_array_pointer_ext = 0x808e,
			gl_normal_array_pointer_ext = 0x808f,
			gl_color_array_pointer_ext = 0x8090,
			gl_index_array_pointer_ext = 0x8091,
			gl_texture_coord_array_pointer_ext = 0x8092,
			gl_edge_flag_array_pointer_ext = 0x8093,

			//vertex_array_bgra,
			//gl_bgra = 0x80e1,

			//vertex_attrib_64bit,
			gl_double_mat2_ext = 0x8f46,
			gl_double_mat3_ext = 0x8f47,
			gl_double_mat4_ext = 0x8f48,
			gl_double_mat2x3_ext = 0x8f49,
			gl_double_mat2x4_ext = 0x8f4a,
			gl_double_mat3x2_ext = 0x8f4b,
			gl_double_mat3x4_ext = 0x8f4c,
			gl_double_mat4x2_ext = 0x8f4d,
			gl_double_mat4x3_ext = 0x8f4e,
			gl_double_vec2_ext = 0x8ffc,
			gl_double_vec3_ext = 0x8ffd,
			gl_double_vec4_ext = 0x8ffe,

			//vertex_shader,
			gl_vertex_shader_ext = 0x8780,
			gl_vertex_shader_binding_ext = 0x8781,
			gl_op_index_ext = 0x8782,
			gl_op_negate_ext = 0x8783,
			gl_op_dot3_ext = 0x8784,
			gl_op_dot4_ext = 0x8785,
			gl_op_mul_ext = 0x8786,
			gl_op_add_ext = 0x8787,
			gl_op_madd_ext = 0x8788,
			gl_op_frac_ext = 0x8789,
			gl_op_max_ext = 0x878a,
			gl_op_min_ext = 0x878b,
			gl_op_set_ge_ext = 0x878c,
			gl_op_set_lt_ext = 0x878d,
			gl_op_clamp_ext = 0x878e,
			gl_op_floor_ext = 0x878f,
			gl_op_round_ext = 0x8790,
			gl_op_exp_base_2_ext = 0x8791,
			gl_op_log_base_2_ext = 0x8792,
			gl_op_power_ext = 0x8793,
			gl_op_recip_ext = 0x8794,
			gl_op_recip_sqrt_ext = 0x8795,
			gl_op_sub_ext = 0x8796,
			gl_op_cross_product_ext = 0x8797,
			gl_op_multiply_matrix_ext = 0x8798,
			gl_op_mov_ext = 0x8799,
			gl_output_vertex_ext = 0x879a,
			gl_output_color0_ext = 0x879b,
			gl_output_color1_ext = 0x879c,
			gl_output_texture_coord0_ext = 0x879d,
			gl_output_texture_coord1_ext = 0x879e,
			gl_output_texture_coord2_ext = 0x879f,
			gl_output_texture_coord3_ext = 0x87a0,
			gl_output_texture_coord4_ext = 0x87a1,
			gl_output_texture_coord5_ext = 0x87a2,
			gl_output_texture_coord6_ext = 0x87a3,
			gl_output_texture_coord7_ext = 0x87a4,
			gl_output_texture_coord8_ext = 0x87a5,
			gl_output_texture_coord9_ext = 0x87a6,
			gl_output_texture_coord10_ext = 0x87a7,
			gl_output_texture_coord11_ext = 0x87a8,
			gl_output_texture_coord12_ext = 0x87a9,
			gl_output_texture_coord13_ext = 0x87aa,
			gl_output_texture_coord14_ext = 0x87ab,
			gl_output_texture_coord15_ext = 0x87ac,
			gl_output_texture_coord16_ext = 0x87ad,
			gl_output_texture_coord17_ext = 0x87ae,
			gl_output_texture_coord18_ext = 0x87af,
			gl_output_texture_coord19_ext = 0x87b0,
			gl_output_texture_coord20_ext = 0x87b1,
			gl_output_texture_coord21_ext = 0x87b2,
			gl_output_texture_coord22_ext = 0x87b3,
			gl_output_texture_coord23_ext = 0x87b4,
			gl_output_texture_coord24_ext = 0x87b5,
			gl_output_texture_coord25_ext = 0x87b6,
			gl_output_texture_coord26_ext = 0x87b7,
			gl_output_texture_coord27_ext = 0x87b8,
			gl_output_texture_coord28_ext = 0x87b9,
			gl_output_texture_coord29_ext = 0x87ba,
			gl_output_texture_coord30_ext = 0x87bb,
			gl_output_texture_coord31_ext = 0x87bc,
			gl_output_fog_ext = 0x87bd,
			gl_scalar_ext = 0x87be,
			gl_vector_ext = 0x87bf,
			gl_matrix_ext = 0x87c0,
			gl_variant_ext = 0x87c1,
			gl_invariant_ext = 0x87c2,
			gl_local_constant_ext = 0x87c3,
			gl_local_ext = 0x87c4,
			gl_max_vertex_shader_instructions_ext = 0x87c5,
			gl_max_vertex_shader_variants_ext = 0x87c6,
			gl_max_vertex_shader_invariants_ext = 0x87c7,
			gl_max_vertex_shader_local_constants_ext = 0x87c8,
			gl_max_vertex_shader_locals_ext = 0x87c9,
			gl_max_optimized_vertex_shader_instructions_ext = 0x87ca,
			gl_max_optimized_vertex_shader_variants_ext = 0x87cb,
			gl_max_optimized_vertex_shader_invariants_ext = 0x87cc,
			gl_max_optimized_vertex_shader_local_constants_ext = 0x87cd,
			gl_max_optimized_vertex_shader_locals_ext = 0x87ce,
			gl_vertex_shader_instructions_ext = 0x87cf,
			gl_vertex_shader_variants_ext = 0x87d0,
			gl_vertex_shader_invariants_ext = 0x87d1,
			gl_vertex_shader_local_constants_ext = 0x87d2,
			gl_vertex_shader_locals_ext = 0x87d3,
			gl_vertex_shader_optimized_ext = 0x87d4,
			gl_x_ext = 0x87d5,
			gl_y_ext = 0x87d6,
			gl_z_ext = 0x87d7,
			gl_w_ext = 0x87d8,
			gl_negative_x_ext = 0x87d9,
			gl_negative_y_ext = 0x87da,
			gl_negative_z_ext = 0x87db,
			gl_negative_w_ext = 0x87dc,
			gl_zero_ext = 0x87dd,
			gl_one_ext = 0x87de,
			gl_negative_one_ext = 0x87df,
			gl_normalized_range_ext = 0x87e0,
			gl_full_range_ext = 0x87e1,
			gl_current_vertex_ext = 0x87e2,
			gl_mvp_matrix_ext = 0x87e3,
			gl_variant_value_ext = 0x87e4,
			gl_variant_datatype_ext = 0x87e5,
			gl_variant_array_stride_ext = 0x87e6,
			gl_variant_array_type_ext = 0x87e7,
			gl_variant_array_ext = 0x87e8,
			gl_variant_array_pointer_ext = 0x87e9,
			gl_invariant_value_ext = 0x87ea,
			gl_invariant_datatype_ext = 0x87eb,
			gl_local_constant_value_ext = 0x87ec,
			gl_local_constant_datatype_ext = 0x87ed,

			//vertex_weighting,
			gl_modelview0_stack_depth_ext = 0x0ba3,
			gl_modelview0_matrix_ext = 0x0ba6,
			gl_modelview0_ext = 0x1700,
			gl_modelview1_stack_depth_ext = 0x8502,
			gl_modelview1_matrix_ext = 0x8506,
			gl_vertex_weighting_ext = 0x8509,
			gl_modelview1_ext = 0x850a,
			gl_current_vertex_weight_ext = 0x850b,
			gl_vertex_weight_array_ext = 0x850c,
			gl_vertex_weight_array_size_ext = 0x850d,
			gl_vertex_weight_array_type_ext = 0x850e,
			gl_vertex_weight_array_stride_ext = 0x850f,
			gl_vertex_weight_array_pointer_ext = 0x8510,

			//window_rectangles,
			gl_inclusive_ext = 0x8f10,
			gl_exclusive_ext = 0x8f11,
			gl_window_rectangle_ext = 0x8f12,
			gl_window_rectangle_mode_ext = 0x8f13,
			gl_max_window_rectangles_ext = 0x8f14,
			gl_num_window_rectangles_ext = 0x8f15,

			//x11_sync_object,
			gl_sync_x11_fence_ext = 0x90e1,

		};

		//422 pixels
		bool EXT_422_pixels = false;		

		//Cg shader
		bool EXT_Cg_shader = false;

		//EGL image array
		bool EXT_EGL_image_array = false;		

		//YUV target
		bool EXT_YUV_target = false;

		//abgr
		bool EXT_abgr = false;

		//base instance
		void (*glDrawArraysInstancedBaseInstanceEXT) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) = nullptr;
		void (*glDrawElementsInstancedBaseInstanceEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLuint baseinstance) = nullptr;
		void (*glDrawElementsInstancedBaseVertexBaseInstanceEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) = nullptr;
		bool EXT_base_instance = false;		

		//bgra
		bool EXT_bgra = false;

		//bindable uniform
		GLint(*glGetUniformBufferSizeEXT) (GLuint program, GLint location) = nullptr;
		GLintptr(*glGetUniformOffsetEXT) (GLuint program, GLint location) = nullptr;
		void (*glUniformBufferEXT) (GLuint program, GLint location, GLuint buffer) = nullptr;
		bool EXT_bindable_uniform = false;		

		//blend color
		void (*glBlendColorEXT) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = nullptr;
		bool EXT_blend_color = false;		

		//blend equation separate
		void (*glBlendEquationSeparateEXT) (GLenum modeRGB, GLenum modeAlpha) = nullptr;
		bool EXT_blend_equation_separate = false;		

		//blend func extended
		void (*glBindFragDataLocationIndexedEXT) (GLuint program, GLuint colorNumber, GLuint index, const GLchar * name) = nullptr;
		GLint(*glGetFragDataIndexEXT) (GLuint program, const GLchar* name) = nullptr;
		GLint(*glGetProgramResourceLocationIndexEXT) (GLuint program, GLenum programInterface, const GLchar* name) = nullptr;
		bool EXT_blend_func_extended = false;		

		//blend func separate
		void (*glBlendFuncSeparateEXT) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) = nullptr;
		bool EXT_blend_func_separate = false;

		//blend logic op
		bool EXT_blend_logic_op = false;		

		//blend minmax
		void (*glBlendEquationEXT) (GLenum mode) = nullptr;
		bool EXT_blend_minmax = false;		

		//blend subtract
		bool EXT_blend_subtract = false;		

		//buffer storage
		void (*glBufferStorageEXT) (GLenum target, GLsizeiptr size, const void* data, GLbitfield flags) = nullptr;
		void (*glNamedBufferStorageEXT) (GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags) = nullptr;
		bool EXT_buffer_storage = false;

		//clear texture
		void (*glClearTexImageEXT) (GLuint texture, GLint level, GLenum format, GLenum type, const void* data) = nullptr;
		void (*glClearTexSubImageEXT) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data) = nullptr;
		bool EXT_clear_texture = false;		

		//clip cull distance
		bool EXT_clip_cull_distance = false;

		//clip volume hint
		bool EXT_clip_volume_hint = false;		

		//cmyka
		bool EXT_cmyka = false;

		//color buffer float
		bool EXT_color_buffer_float = false;		

		//color buffer half float
		bool EXT_color_buffer_half_float = false;

		//color subtable
		void (*glColorSubTableEXT) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void* data) = nullptr;
		void (*glCopyColorSubTableEXT) (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width) = nullptr;
		bool EXT_color_subtable = false;		

		//compiled vertex array
		void (*glLockArraysEXT) (GLint first, GLsizei count) = nullptr;
		void (*glUnlockArraysEXT) (void) = nullptr;
		bool EXT_compiled_vertex_array = false;

		//compressed ETC1 RGB8 sub texture
		bool EXT_compressed_ETC1_RGB8_sub_texture = false;

		//conservative depth
		bool EXT_conservative_depth = false;		

		//convolution
		void (*glConvolutionFilter1DEXT) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* image) = nullptr;
		void (*glConvolutionFilter2DEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* image) = nullptr;
		void (*glConvolutionParameterfEXT) (GLenum target, GLenum pname, GLfloat param) = nullptr;
		void (*glConvolutionParameterfvEXT) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
		void (*glConvolutionParameteriEXT) (GLenum target, GLenum pname, GLint param) = nullptr;
		void (*glConvolutionParameterivEXT) (GLenum target, GLenum pname, const GLint* params) = nullptr;
		void (*glCopyConvolutionFilter1DEXT) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = nullptr;
		void (*glCopyConvolutionFilter2DEXT) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
		void (*glGetConvolutionFilterEXT) (GLenum target, GLenum format, GLenum type, void* image) = nullptr;
		void (*glGetConvolutionParameterfvEXT) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetConvolutionParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glGetSeparableFilterEXT) (GLenum target, GLenum format, GLenum type, void* row, void* column, void* span) = nullptr;
		void (*glSeparableFilter2DEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* row, const void* column) = nullptr;
		bool EXT_convolution = false;		

		//coordinate frame
		void (*glBinormalPointerEXT) (GLenum type, GLsizei stride, void* pointer) = nullptr;
		void (*glTangentPointerEXT) (GLenum type, GLsizei stride, void* pointer) = nullptr;
		bool EXT_coordinate_frame = false;

		//copy image
		void (*glCopyImageSubDataEXT) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) = nullptr;
		bool EXT_copy_image = false;

		//copy texture
		void (*glCopyTexImage1DEXT) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) = nullptr;
		void (*glCopyTexImage2DEXT) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = nullptr;
		void (*glCopyTexSubImage1DEXT) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = nullptr;
		void (*glCopyTexSubImage2DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
		void (*glCopyTexSubImage3DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
		bool EXT_copy_texture = false;		

		//cull vertex
		void (*glCullParameterdvEXT) (GLenum pname, GLdouble * params) = nullptr;
		void (*glCullParameterfvEXT) (GLenum pname, GLfloat* params) = nullptr;
		bool EXT_cull_vertex = false;

		//debug label
		void (*glGetObjectLabelEXT) (GLenum type, GLuint object, GLsizei bufSize, GLsizei * length, GLchar * label) = nullptr;
		void (*glLabelObjectEXT) (GLenum type, GLuint object, GLsizei length, const GLchar* label) = nullptr;
		bool EXT_debug_label = false;

		//debug marker
		void (*glInsertEventMarkerEXT) (GLsizei length, const GLchar * marker) = nullptr;
		void (*glPopGroupMarkerEXT) (void) = nullptr;
		void (*glPushGroupMarkerEXT) (GLsizei length, const GLchar* marker) = nullptr;
		bool EXT_debug_marker = false;

		//depth bounds test
		void (*glDepthBoundsEXT) (GLclampd zmin, GLclampd zmax) = nullptr;
		bool EXT_depth_bounds_test = false;		

		//direct state access
		void (*glBindMultiTextureEXT) (GLenum texunit, GLenum target, GLuint texture) = nullptr;
		GLenum(*glCheckNamedFramebufferStatusEXT) (GLuint framebuffer, GLenum target) = nullptr;
		void (*glClientAttribDefaultEXT) (GLbitfield mask) = nullptr;
		void (*glCompressedMultiTexImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedMultiTexImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedMultiTexImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedMultiTexSubImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedMultiTexSubImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedMultiTexSubImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedTextureImage1DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedTextureImage2DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedTextureImage3DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedTextureSubImage1DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedTextureSubImage2DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedTextureSubImage3DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
		void (*glCopyMultiTexImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) = nullptr;
		void (*glCopyMultiTexImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = nullptr;
		void (*glCopyMultiTexSubImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = nullptr;
		void (*glCopyMultiTexSubImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
		void (*glCopyMultiTexSubImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
		void (*glCopyTextureImage1DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) = nullptr;
		void (*glCopyTextureImage2DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = nullptr;
		void (*glCopyTextureSubImage1DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = nullptr;
		void (*glCopyTextureSubImage2DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
		void (*glCopyTextureSubImage3DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
		void (*glDisableClientStateIndexedEXT) (GLenum array, GLuint index) = nullptr;
		void (*glDisableClientStateiEXT) (GLenum array, GLuint index) = nullptr;
		void (*glDisableVertexArrayAttribEXT) (GLuint vaobj, GLuint index) = nullptr;
		void (*glDisableVertexArrayEXT) (GLuint vaobj, GLenum array) = nullptr;
		void (*glEnableClientStateIndexedEXT) (GLenum array, GLuint index) = nullptr;
		void (*glEnableClientStateiEXT) (GLenum array, GLuint index) = nullptr;
		void (*glEnableVertexArrayAttribEXT) (GLuint vaobj, GLuint index) = nullptr;
		void (*glEnableVertexArrayEXT) (GLuint vaobj, GLenum array) = nullptr;
		void (*glFlushMappedNamedBufferRangeEXT) (GLuint buffer, GLintptr offset, GLsizeiptr length) = nullptr;
		void (*glFramebufferDrawBufferEXT) (GLuint framebuffer, GLenum mode) = nullptr;
		void (*glFramebufferDrawBuffersEXT) (GLuint framebuffer, GLsizei n, const GLenum* bufs) = nullptr;
		void (*glFramebufferReadBufferEXT) (GLuint framebuffer, GLenum mode) = nullptr;
		void (*glGenerateMultiTexMipmapEXT) (GLenum texunit, GLenum target) = nullptr;
		void (*glGenerateTextureMipmapEXT) (GLuint texture, GLenum target) = nullptr;
		void (*glGetCompressedMultiTexImageEXT) (GLenum texunit, GLenum target, GLint level, void* img) = nullptr;
		void (*glGetCompressedTextureImageEXT) (GLuint texture, GLenum target, GLint level, void* img) = nullptr;
		void (*glGetDoubleIndexedvEXT) (GLenum target, GLuint index, GLdouble* params) = nullptr;
		void (*glGetDoublei_vEXT) (GLenum pname, GLuint index, GLdouble* params) = nullptr;
		void (*glGetFloatIndexedvEXT) (GLenum target, GLuint index, GLfloat* params) = nullptr;
		void (*glGetFloati_vEXT) (GLenum pname, GLuint index, GLfloat* params) = nullptr;
		void (*glGetFramebufferParameterivEXT) (GLuint framebuffer, GLenum pname, GLint* param) = nullptr;
		void (*glGetMultiTexEnvfvEXT) (GLenum texunit, GLenum target, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetMultiTexEnvivEXT) (GLenum texunit, GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glGetMultiTexGendvEXT) (GLenum texunit, GLenum coord, GLenum pname, GLdouble* params) = nullptr;
		void (*glGetMultiTexGenfvEXT) (GLenum texunit, GLenum coord, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetMultiTexGenivEXT) (GLenum texunit, GLenum coord, GLenum pname, GLint* params) = nullptr;
		void (*glGetMultiTexImageEXT) (GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void* pixels) = nullptr;
		void (*glGetMultiTexLevelParameterfvEXT) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetMultiTexLevelParameterivEXT) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLint* params) = nullptr;
		void (*glGetMultiTexParameterIivEXT) (GLenum texunit, GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glGetMultiTexParameterIuivEXT) (GLenum texunit, GLenum target, GLenum pname, GLuint* params) = nullptr;
		void (*glGetMultiTexParameterfvEXT) (GLenum texunit, GLenum target, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetMultiTexParameterivEXT) (GLenum texunit, GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glGetNamedBufferParameterivEXT) (GLuint buffer, GLenum pname, GLint* params) = nullptr;
		void (*glGetNamedBufferPointervEXT) (GLuint buffer, GLenum pname, void** params) = nullptr;
		void (*glGetNamedBufferSubDataEXT) (GLuint buffer, GLintptr offset, GLsizeiptr size, void* data) = nullptr;
		void (*glGetNamedFramebufferAttachmentParameterivEXT) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params) = nullptr;
		void (*glGetNamedProgramLocalParameterIivEXT) (GLuint program, GLenum target, GLuint index, GLint* params) = nullptr;
		void (*glGetNamedProgramLocalParameterIuivEXT) (GLuint program, GLenum target, GLuint index, GLuint* params) = nullptr;
		void (*glGetNamedProgramLocalParameterdvEXT) (GLuint program, GLenum target, GLuint index, GLdouble* params) = nullptr;
		void (*glGetNamedProgramLocalParameterfvEXT) (GLuint program, GLenum target, GLuint index, GLfloat* params) = nullptr;
		void (*glGetNamedProgramStringEXT) (GLuint program, GLenum target, GLenum pname, void* string) = nullptr;
		void (*glGetNamedProgramivEXT) (GLuint program, GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glGetNamedRenderbufferParameterivEXT) (GLuint renderbuffer, GLenum pname, GLint* params) = nullptr;
		void (*glGetPointerIndexedvEXT) (GLenum target, GLuint index, void** params) = nullptr;
		void (*glGetPointeri_vEXT) (GLenum pname, GLuint index, void** params) = nullptr;
		void (*glGetTextureImageEXT) (GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void* pixels) = nullptr;
		void (*glGetTextureLevelParameterfvEXT) (GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetTextureLevelParameterivEXT) (GLuint texture, GLenum target, GLint level, GLenum pname, GLint* params) = nullptr;
		void (*glGetTextureParameterIivEXT) (GLuint texture, GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glGetTextureParameterIuivEXT) (GLuint texture, GLenum target, GLenum pname, GLuint* params) = nullptr;
		void (*glGetTextureParameterfvEXT) (GLuint texture, GLenum target, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetTextureParameterivEXT) (GLuint texture, GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glGetVertexArrayIntegeri_vEXT) (GLuint vaobj, GLuint index, GLenum pname, GLint* param) = nullptr;
		void (*glGetVertexArrayIntegervEXT) (GLuint vaobj, GLenum pname, GLint* param) = nullptr;
		void (*glGetVertexArrayPointeri_vEXT) (GLuint vaobj, GLuint index, GLenum pname, void** param) = nullptr;
		void (*glGetVertexArrayPointervEXT) (GLuint vaobj, GLenum pname, void** param) = nullptr;
		void* (*glMapNamedBufferEXT) (GLuint buffer, GLenum access) = nullptr;
		void* (*glMapNamedBufferRangeEXT) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) = nullptr;
		void (*glMatrixFrustumEXT) (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f) = nullptr;
		void (*glMatrixLoadIdentityEXT) (GLenum matrixMode) = nullptr;
		void (*glMatrixLoadTransposedEXT) (GLenum matrixMode, const GLdouble* m) = nullptr;
		void (*glMatrixLoadTransposefEXT) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glMatrixLoaddEXT) (GLenum matrixMode, const GLdouble* m) = nullptr;
		void (*glMatrixLoadfEXT) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glMatrixMultTransposedEXT) (GLenum matrixMode, const GLdouble* m) = nullptr;
		void (*glMatrixMultTransposefEXT) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glMatrixMultdEXT) (GLenum matrixMode, const GLdouble* m) = nullptr;
		void (*glMatrixMultfEXT) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glMatrixOrthoEXT) (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f) = nullptr;
		void (*glMatrixPopEXT) (GLenum matrixMode) = nullptr;
		void (*glMatrixPushEXT) (GLenum matrixMode) = nullptr;
		void (*glMatrixRotatedEXT) (GLenum matrixMode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z) = nullptr;
		void (*glMatrixRotatefEXT) (GLenum matrixMode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) = nullptr;
		void (*glMatrixScaledEXT) (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z) = nullptr;
		void (*glMatrixScalefEXT) (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z) = nullptr;
		void (*glMatrixTranslatedEXT) (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z) = nullptr;
		void (*glMatrixTranslatefEXT) (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z) = nullptr;
		void (*glMultiTexBufferEXT) (GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
		void (*glMultiTexCoordPointerEXT) (GLenum texunit, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
		void (*glMultiTexEnvfEXT) (GLenum texunit, GLenum target, GLenum pname, GLfloat param) = nullptr;
		void (*glMultiTexEnvfvEXT) (GLenum texunit, GLenum target, GLenum pname, const GLfloat* params) = nullptr;
		void (*glMultiTexEnviEXT) (GLenum texunit, GLenum target, GLenum pname, GLint param) = nullptr;
		void (*glMultiTexEnvivEXT) (GLenum texunit, GLenum target, GLenum pname, const GLint* params) = nullptr;
		void (*glMultiTexGendEXT) (GLenum texunit, GLenum coord, GLenum pname, GLdouble param) = nullptr;
		void (*glMultiTexGendvEXT) (GLenum texunit, GLenum coord, GLenum pname, const GLdouble* params) = nullptr;
		void (*glMultiTexGenfEXT) (GLenum texunit, GLenum coord, GLenum pname, GLfloat param) = nullptr;
		void (*glMultiTexGenfvEXT) (GLenum texunit, GLenum coord, GLenum pname, const GLfloat* params) = nullptr;
		void (*glMultiTexGeniEXT) (GLenum texunit, GLenum coord, GLenum pname, GLint param) = nullptr;
		void (*glMultiTexGenivEXT) (GLenum texunit, GLenum coord, GLenum pname, const GLint* params) = nullptr;
		void (*glMultiTexImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glMultiTexImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glMultiTexImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glMultiTexParameterIivEXT) (GLenum texunit, GLenum target, GLenum pname, const GLint* params) = nullptr;
		void (*glMultiTexParameterIuivEXT) (GLenum texunit, GLenum target, GLenum pname, const GLuint* params) = nullptr;
		void (*glMultiTexParameterfEXT) (GLenum texunit, GLenum target, GLenum pname, GLfloat param) = nullptr;
		void (*glMultiTexParameterfvEXT) (GLenum texunit, GLenum target, GLenum pname, const GLfloat* param) = nullptr;
		void (*glMultiTexParameteriEXT) (GLenum texunit, GLenum target, GLenum pname, GLint param) = nullptr;
		void (*glMultiTexParameterivEXT) (GLenum texunit, GLenum target, GLenum pname, const GLint* param) = nullptr;
		void (*glMultiTexRenderbufferEXT) (GLenum texunit, GLenum target, GLuint renderbuffer) = nullptr;
		void (*glMultiTexSubImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glMultiTexSubImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glMultiTexSubImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glNamedBufferDataEXT) (GLuint buffer, GLsizeiptr size, const void* data, GLenum usage) = nullptr;
		void (*glNamedBufferSubDataEXT) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) = nullptr;
		void (*glNamedCopyBufferSubDataEXT) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) = nullptr;
		void (*glNamedFramebufferRenderbufferEXT) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
		void (*glNamedFramebufferTexture1DEXT) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
		void (*glNamedFramebufferTexture2DEXT) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
		void (*glNamedFramebufferTexture3DEXT) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) = nullptr;
		void (*glNamedFramebufferTextureEXT) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) = nullptr;
		void (*glNamedFramebufferTextureFaceEXT) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face) = nullptr;
		void (*glNamedFramebufferTextureLayerEXT) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
		void (*glNamedProgramLocalParameter4dEXT) (GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
		void (*glNamedProgramLocalParameter4dvEXT) (GLuint program, GLenum target, GLuint index, const GLdouble* params) = nullptr;
		void (*glNamedProgramLocalParameter4fEXT) (GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
		void (*glNamedProgramLocalParameter4fvEXT) (GLuint program, GLenum target, GLuint index, const GLfloat* params) = nullptr;
		void (*glNamedProgramLocalParameterI4iEXT) (GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) = nullptr;
		void (*glNamedProgramLocalParameterI4ivEXT) (GLuint program, GLenum target, GLuint index, const GLint* params) = nullptr;
		void (*glNamedProgramLocalParameterI4uiEXT) (GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
		void (*glNamedProgramLocalParameterI4uivEXT) (GLuint program, GLenum target, GLuint index, const GLuint* params) = nullptr;
		void (*glNamedProgramLocalParameters4fvEXT) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat* params) = nullptr;
		void (*glNamedProgramLocalParametersI4ivEXT) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLint* params) = nullptr;
		void (*glNamedProgramLocalParametersI4uivEXT) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint* params) = nullptr;
		void (*glNamedProgramStringEXT) (GLuint program, GLenum target, GLenum format, GLsizei len, const void* string) = nullptr;
		void (*glNamedRenderbufferStorageEXT) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
		void (*glNamedRenderbufferStorageMultisampleCoverageEXT) (GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
		void (*glNamedRenderbufferStorageMultisampleEXT) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
		void (*glProgramUniform1fEXT) (GLuint program, GLint location, GLfloat v0) = nullptr;
		void (*glProgramUniform1fvEXT) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
		void (*glProgramUniform1iEXT) (GLuint program, GLint location, GLint v0) = nullptr;
		void (*glProgramUniform1ivEXT) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
		void (*glProgramUniform1uiEXT) (GLuint program, GLint location, GLuint v0) = nullptr;
		void (*glProgramUniform1uivEXT) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
		void (*glProgramUniform2fEXT) (GLuint program, GLint location, GLfloat v0, GLfloat v1) = nullptr;
		void (*glProgramUniform2fvEXT) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
		void (*glProgramUniform2iEXT) (GLuint program, GLint location, GLint v0, GLint v1) = nullptr;
		void (*glProgramUniform2ivEXT) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
		void (*glProgramUniform2uiEXT) (GLuint program, GLint location, GLuint v0, GLuint v1) = nullptr;
		void (*glProgramUniform2uivEXT) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
		void (*glProgramUniform3fEXT) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) = nullptr;
		void (*glProgramUniform3fvEXT) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
		void (*glProgramUniform3iEXT) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2) = nullptr;
		void (*glProgramUniform3ivEXT) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
		void (*glProgramUniform3uiEXT) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) = nullptr;
		void (*glProgramUniform3uivEXT) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
		void (*glProgramUniform4fEXT) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) = nullptr;
		void (*glProgramUniform4fvEXT) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
		void (*glProgramUniform4iEXT) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) = nullptr;
		void (*glProgramUniform4ivEXT) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
		void (*glProgramUniform4uiEXT) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) = nullptr;
		void (*glProgramUniform4uivEXT) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
		void (*glProgramUniformMatrix2fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glProgramUniformMatrix2x3fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glProgramUniformMatrix2x4fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glProgramUniformMatrix3fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glProgramUniformMatrix3x2fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glProgramUniformMatrix3x4fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glProgramUniformMatrix4fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glProgramUniformMatrix4x2fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glProgramUniformMatrix4x3fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glPushClientAttribDefaultEXT) (GLbitfield mask) = nullptr;
		void (*glTextureBufferEXT) (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
		void (*glTextureImage1DEXT) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glTextureImage2DEXT) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glTextureImage3DEXT) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glTextureParameterIivEXT) (GLuint texture, GLenum target, GLenum pname, const GLint* params) = nullptr;
		void (*glTextureParameterIuivEXT) (GLuint texture, GLenum target, GLenum pname, const GLuint* params) = nullptr;
		void (*glTextureParameterfEXT) (GLuint texture, GLenum target, GLenum pname, GLfloat param) = nullptr;
		void (*glTextureParameterfvEXT) (GLuint texture, GLenum target, GLenum pname, const GLfloat* param) = nullptr;
		void (*glTextureParameteriEXT) (GLuint texture, GLenum target, GLenum pname, GLint param) = nullptr;
		void (*glTextureParameterivEXT) (GLuint texture, GLenum target, GLenum pname, const GLint* param) = nullptr;
		void (*glTextureRenderbufferEXT) (GLuint texture, GLenum target, GLuint renderbuffer) = nullptr;
		void (*glTextureSubImage1DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glTextureSubImage2DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glTextureSubImage3DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
		GLboolean(*glUnmapNamedBufferEXT) (GLuint buffer) = nullptr;
		void (*glVertexArrayColorOffsetEXT) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArrayEdgeFlagOffsetEXT) (GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArrayFogCoordOffsetEXT) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArrayIndexOffsetEXT) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArrayMultiTexCoordOffsetEXT) (GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArrayNormalOffsetEXT) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArraySecondaryColorOffsetEXT) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArrayTexCoordOffsetEXT) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArrayVertexAttribDivisorEXT) (GLuint vaobj, GLuint index, GLuint divisor) = nullptr;
		void (*glVertexArrayVertexAttribIOffsetEXT) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArrayVertexAttribOffsetEXT) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexArrayVertexOffsetEXT) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		bool EXT_direct_state_access = false;		

		//discard framebuffer
		void (*glDiscardFramebufferEXT) (GLenum target, GLsizei numAttachments, const GLenum * attachments) = nullptr;
		bool EXT_discard_framebuffer = false;		

		//draw buffers
		void (*glDrawBuffersEXT) (GLsizei n, const GLenum * bufs) = nullptr;
		bool EXT_draw_buffers = false;

		//draw buffers2
		void (*glColorMaskIndexedEXT) (GLuint buf, GLboolean r, GLboolean g, GLboolean b, GLboolean a) = nullptr;
		void (*glDisableIndexedEXT) (GLenum target, GLuint index) = nullptr;
		void (*glEnableIndexedEXT) (GLenum target, GLuint index) = nullptr;
		void (*glGetBooleanIndexedvEXT) (GLenum value, GLuint index, GLboolean* data) = nullptr;
		void (*glGetIntegerIndexedvEXT) (GLenum value, GLuint index, GLint* data) = nullptr;
		GLboolean(*glIsEnabledIndexedEXT) (GLenum target, GLuint index) = nullptr;
		bool EXT_draw_buffers2 = false;

		//draw buffers indexed
		void (*glBlendEquationSeparateiEXT) (GLuint buf, GLenum modeRGB, GLenum modeAlpha) = nullptr;
		void (*glBlendEquationiEXT) (GLuint buf, GLenum mode) = nullptr;
		void (*glBlendFuncSeparateiEXT) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = nullptr;
		void (*glBlendFunciEXT) (GLuint buf, GLenum src, GLenum dst) = nullptr;
		void (*glColorMaskiEXT) (GLuint buf, GLboolean r, GLboolean g, GLboolean b, GLboolean a) = nullptr;
		void (*glDisableiEXT) (GLenum target, GLuint index) = nullptr;
		void (*glEnableiEXT) (GLenum target, GLuint index) = nullptr;
		GLboolean(*glIsEnablediEXT) (GLenum target, GLuint index) = nullptr;
		bool EXT_draw_buffers_indexed = false;

		//draw elements base vertex
		void (*glDrawElementsBaseVertexEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex) = nullptr;
		void (*glDrawElementsInstancedBaseVertexEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex) = nullptr;
		void (*glDrawRangeElementsBaseVertexEXT) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex) = nullptr;
		void (*glMultiDrawElementsBaseVertexEXT) (GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei primcount, const GLint* basevertex) = nullptr;
		bool EXT_draw_elements_base_vertex = false;

		//draw instanced
		void (*glDrawArraysInstancedEXT) (GLenum mode, GLint start, GLsizei count, GLsizei primcount) = nullptr;
		void (*glDrawElementsInstancedEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) = nullptr;
		bool EXT_draw_instanced = false;		

		//draw range elements
		void (*glDrawRangeElementsEXT) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices) = nullptr;
		bool EXT_draw_range_elements = false;

		//external buffer
		void (*glBufferStorageExternalEXT) (GLenum target, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags) = nullptr;
		void (*glNamedBufferStorageExternalEXT) (GLuint buffer, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags) = nullptr;
		bool EXT_external_buffer = false;

		//float blend
		bool EXT_float_blend = false;		

		//fog coord
		void (*glFogCoordPointerEXT) (GLenum type, GLsizei stride, const void* pointer) = nullptr;
		void (*glFogCoorddEXT) (GLdouble coord) = nullptr;
		void (*glFogCoorddvEXT) (const GLdouble* coord) = nullptr;
		void (*glFogCoordfEXT) (GLfloat coord) = nullptr;
		void (*glFogCoordfvEXT) (const GLfloat* coord) = nullptr;
		bool EXT_fog_coord = false;

		//frag depth
		bool EXT_frag_depth = false;		

		//fragment lighting
		void (*glFragmentColorMaterialEXT) (GLenum face, GLenum mode) = nullptr;
		void (*glFragmentLightModelfEXT) (GLenum pname, GLfloat param) = nullptr;
		void (*glFragmentLightModelfvEXT) (GLenum pname, GLfloat* params) = nullptr;
		void (*glFragmentLightModeliEXT) (GLenum pname, GLint param) = nullptr;
		void (*glFragmentLightModelivEXT) (GLenum pname, GLint* params) = nullptr;
		void (*glFragmentLightfEXT) (GLenum light, GLenum pname, GLfloat param) = nullptr;
		void (*glFragmentLightfvEXT) (GLenum light, GLenum pname, GLfloat* params) = nullptr;
		void (*glFragmentLightiEXT) (GLenum light, GLenum pname, GLint param) = nullptr;
		void (*glFragmentLightivEXT) (GLenum light, GLenum pname, GLint* params) = nullptr;
		void (*glFragmentMaterialfEXT) (GLenum face, GLenum pname, const GLfloat param) = nullptr;
		void (*glFragmentMaterialfvEXT) (GLenum face, GLenum pname, const GLfloat* params) = nullptr;
		void (*glFragmentMaterialiEXT) (GLenum face, GLenum pname, const GLint param) = nullptr;
		void (*glFragmentMaterialivEXT) (GLenum face, GLenum pname, const GLint* params) = nullptr;
		void (*glGetFragmentLightfvEXT) (GLenum light, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetFragmentLightivEXT) (GLenum light, GLenum pname, GLint* params) = nullptr;
		void (*glGetFragmentMaterialfvEXT) (GLenum face, GLenum pname, const GLfloat* params) = nullptr;
		void (*glGetFragmentMaterialivEXT) (GLenum face, GLenum pname, const GLint* params) = nullptr;
		void (*glLightEnviEXT) (GLenum pname, GLint param) = nullptr;
		bool EXT_fragment_lighting = false;		

		//framebuffer blit
		void (*glBlitFramebufferEXT) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
		bool EXT_framebuffer_blit = false;

		//framebuffer multisample
		void (*glRenderbufferStorageMultisampleEXT) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
		bool EXT_framebuffer_multisample = false;		

		//framebuffer multisample blit scaled
		bool EXT_framebuffer_multisample_blit_scaled = false;		

		//framebuffer object
		void (*glBindFramebufferEXT) (GLenum target, GLuint framebuffer) = nullptr;
		void (*glBindRenderbufferEXT) (GLenum target, GLuint renderbuffer) = nullptr;
		GLenum(*glCheckFramebufferStatusEXT) (GLenum target) = nullptr;
		void (*glDeleteFramebuffersEXT) (GLsizei n, const GLuint* framebuffers) = nullptr;
		void (*glDeleteRenderbuffersEXT) (GLsizei n, const GLuint* renderbuffers) = nullptr;
		void (*glFramebufferRenderbufferEXT) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
		void (*glFramebufferTexture1DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
		void (*glFramebufferTexture2DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
		void (*glFramebufferTexture3DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) = nullptr;
		void (*glGenFramebuffersEXT) (GLsizei n, GLuint* framebuffers) = nullptr;
		void (*glGenRenderbuffersEXT) (GLsizei n, GLuint* renderbuffers) = nullptr;
		void (*glGenerateMipmapEXT) (GLenum target) = nullptr;
		void (*glGetFramebufferAttachmentParameterivEXT) (GLenum target, GLenum attachment, GLenum pname, GLint* params) = nullptr;
		void (*glGetRenderbufferParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
		GLboolean(*glIsFramebufferEXT) (GLuint framebuffer) = nullptr;
		GLboolean(*glIsRenderbufferEXT) (GLuint renderbuffer) = nullptr;
		void (*glRenderbufferStorageEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
		bool EXT_framebuffer_object = false;		

		//framebuffer sRGB
		bool EXT_framebuffer_sRGB = false;

		//geometry point size
		bool EXT_geometry_point_size = false;

		//geometry shader
		bool EXT_geometry_shader = false;	

		//geometry shader4
		void (*glFramebufferTextureEXT) (GLenum target, GLenum attachment, GLuint texture, GLint level) = nullptr;
		void (*glFramebufferTextureFaceEXT) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face) = nullptr;
		void (*glProgramParameteriEXT) (GLuint program, GLenum pname, GLint value) = nullptr;
		bool EXT_geometry_shader4 = false;

		//gpu program parameters
		void (*glProgramEnvParameters4fvEXT) (GLenum target, GLuint index, GLsizei count, const GLfloat * params) = nullptr;
		void (*glProgramLocalParameters4fvEXT) (GLenum target, GLuint index, GLsizei count, const GLfloat* params) = nullptr;
		bool EXT_gpu_program_parameters = false;		

		//gpu shader4
		void (*glBindFragDataLocationEXT) (GLuint program, GLuint color, const GLchar * name) = nullptr;
		GLint(*glGetFragDataLocationEXT) (GLuint program, const GLchar* name) = nullptr;
		void (*glGetUniformuivEXT) (GLuint program, GLint location, GLuint* params) = nullptr;
		void (*glGetVertexAttribIivEXT) (GLuint index, GLenum pname, GLint* params) = nullptr;
		void (*glGetVertexAttribIuivEXT) (GLuint index, GLenum pname, GLuint* params) = nullptr;
		void (*glUniform1uiEXT) (GLint location, GLuint v0) = nullptr;
		void (*glUniform1uivEXT) (GLint location, GLsizei count, const GLuint* value) = nullptr;
		void (*glUniform2uiEXT) (GLint location, GLuint v0, GLuint v1) = nullptr;
		void (*glUniform2uivEXT) (GLint location, GLsizei count, const GLuint* value) = nullptr;
		void (*glUniform3uiEXT) (GLint location, GLuint v0, GLuint v1, GLuint v2) = nullptr;
		void (*glUniform3uivEXT) (GLint location, GLsizei count, const GLuint* value) = nullptr;
		void (*glUniform4uiEXT) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) = nullptr;
		void (*glUniform4uivEXT) (GLint location, GLsizei count, const GLuint* value) = nullptr;
		void (*glVertexAttribI1iEXT) (GLuint index, GLint x) = nullptr;
		void (*glVertexAttribI1ivEXT) (GLuint index, const GLint* v) = nullptr;
		void (*glVertexAttribI1uiEXT) (GLuint index, GLuint x) = nullptr;
		void (*glVertexAttribI1uivEXT) (GLuint index, const GLuint* v) = nullptr;
		void (*glVertexAttribI2iEXT) (GLuint index, GLint x, GLint y) = nullptr;
		void (*glVertexAttribI2ivEXT) (GLuint index, const GLint* v) = nullptr;
		void (*glVertexAttribI2uiEXT) (GLuint index, GLuint x, GLuint y) = nullptr;
		void (*glVertexAttribI2uivEXT) (GLuint index, const GLuint* v) = nullptr;
		void (*glVertexAttribI3iEXT) (GLuint index, GLint x, GLint y, GLint z) = nullptr;
		void (*glVertexAttribI3ivEXT) (GLuint index, const GLint* v) = nullptr;
		void (*glVertexAttribI3uiEXT) (GLuint index, GLuint x, GLuint y, GLuint z) = nullptr;
		void (*glVertexAttribI3uivEXT) (GLuint index, const GLuint* v) = nullptr;
		void (*glVertexAttribI4bvEXT) (GLuint index, const GLbyte* v) = nullptr;
		void (*glVertexAttribI4iEXT) (GLuint index, GLint x, GLint y, GLint z, GLint w) = nullptr;
		void (*glVertexAttribI4ivEXT) (GLuint index, const GLint* v) = nullptr;
		void (*glVertexAttribI4svEXT) (GLuint index, const GLshort* v) = nullptr;
		void (*glVertexAttribI4ubvEXT) (GLuint index, const GLubyte* v) = nullptr;
		void (*glVertexAttribI4uiEXT) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
		void (*glVertexAttribI4uivEXT) (GLuint index, const GLuint* v) = nullptr;
		void (*glVertexAttribI4usvEXT) (GLuint index, const GLushort* v) = nullptr;
		void (*glVertexAttribIPointerEXT) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
		bool EXT_gpu_shader4 = false;

		//gpu shader5
		bool EXT_gpu_shader5 = false;		

		//histogram
		void (*glGetHistogramEXT) (GLenum target, GLboolean reset, GLenum format, GLenum type, void* values) = nullptr;
		void (*glGetHistogramParameterfvEXT) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetHistogramParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glGetMinmaxEXT) (GLenum target, GLboolean reset, GLenum format, GLenum type, void* values) = nullptr;
		void (*glGetMinmaxParameterfvEXT) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetMinmaxParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glHistogramEXT) (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink) = nullptr;
		void (*glMinmaxEXT) (GLenum target, GLenum internalformat, GLboolean sink) = nullptr;
		void (*glResetHistogramEXT) (GLenum target) = nullptr;
		void (*glResetMinmaxEXT) (GLenum target) = nullptr;
		bool EXT_histogram = false;
		
		//index array formats
		bool EXT_index_array_formats = false;

		//index func
		void (*glIndexFuncEXT) (GLenum func, GLfloat ref) = nullptr;
		bool EXT_index_func = false;

		//index material
		void (*glIndexMaterialEXT) (GLenum face, GLenum mode) = nullptr;
		bool EXT_index_material = false;

		//index texture
		bool EXT_index_texture = false;		

		//instanced arrays
		void (*glVertexAttribDivisorEXT) (GLuint index, GLuint divisor) = nullptr;
		bool EXT_instanced_arrays = false;		

		//light texture
		void (*glApplyTextureEXT) (GLenum mode) = nullptr;
		void (*glTextureLightEXT) (GLenum pname) = nullptr;
		void (*glTextureMaterialEXT) (GLenum face, GLenum mode) = nullptr;
		bool EXT_light_texture = false;

		//map buffer range
		void (*glFlushMappedBufferRangeEXT) (GLenum target, GLintptr offset, GLsizeiptr length) = nullptr;
		void* (*glMapBufferRangeEXT) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) = nullptr;
		bool EXT_map_buffer_range = false;		

		//memory object
		void (*glBufferStorageMemEXT) (GLenum target, GLsizeiptr size, GLuint memory, GLuint64 offset) = nullptr;
		void (*glCreateMemoryObjectsEXT) (GLsizei n, GLuint* memoryObjects) = nullptr;
		void (*glDeleteMemoryObjectsEXT) (GLsizei n, const GLuint* memoryObjects) = nullptr;
		void (*glGetMemoryObjectParameterivEXT) (GLuint memoryObject, GLenum pname, GLint* params) = nullptr;
		void (*glGetUnsignedBytei_vEXT) (GLenum target, GLuint index, GLubyte* data) = nullptr;
		void (*glGetUnsignedBytevEXT) (GLenum pname, GLubyte* data) = nullptr;
		GLboolean(*glIsMemoryObjectEXT) (GLuint memoryObject) = nullptr;
		void (*glMemoryObjectParameterivEXT) (GLuint memoryObject, GLenum pname, const GLint* params) = nullptr;
		void (*glNamedBufferStorageMemEXT) (GLuint buffer, GLsizeiptr size, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTexStorageMem1DEXT) (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTexStorageMem2DEXT) (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTexStorageMem2DMultisampleEXT) (GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTexStorageMem3DEXT) (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTexStorageMem3DMultisampleEXT) (GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTextureStorageMem1DEXT) (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTextureStorageMem2DEXT) (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTextureStorageMem2DMultisampleEXT) (GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTextureStorageMem3DEXT) (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset) = nullptr;
		void (*glTextureStorageMem3DMultisampleEXT) (GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset) = nullptr;
		bool EXT_memory_object = false;

		//memory object fd
		void (*glImportMemoryFdEXT) (GLuint memory, GLuint64 size, GLenum handleType, GLint fd) = nullptr;
		bool EXT_memory_object_fd = false;

		//memory object win32
		void (*glImportMemoryWin32HandleEXT) (GLuint memory, GLuint64 size, GLenum handleType, void* handle) = nullptr;
		void (*glImportMemoryWin32NameEXT) (GLuint memory, GLuint64 size, GLenum handleType, const void* name) = nullptr;
		bool EXT_memory_object_win32 = false;

		//misc attribute
		bool EXT_misc_attribute = false;

		//multi draw arrays
		void (*glMultiDrawArraysEXT) (GLenum mode, const GLint * first, const GLsizei * count, GLsizei primcount) = nullptr;
		void (*glMultiDrawElementsEXT) (GLenum mode, GLsizei* count, GLenum type, const void* const* indices, GLsizei primcount) = nullptr;
		bool EXT_multi_draw_arrays = false;

		//multi draw indirect
		void (*glMultiDrawArraysIndirectEXT) (GLenum mode, const void* indirect, GLsizei drawcount, GLsizei stride) = nullptr;
		void (*glMultiDrawElementsIndirectEXT) (GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride) = nullptr;
		bool EXT_multi_draw_indirect = false;

		//multiple textures
		bool EXT_multiple_textures = false;

		//multisample
		void (*glSampleMaskEXT) (GLclampf value, GLboolean invert) = nullptr;
		void (*glSamplePatternEXT) (GLenum pattern) = nullptr;
		bool EXT_multisample = false;		

		//multisample compatibility
		bool EXT_multisample_compatibility = false;

		//multisampled render to texture
		void (*glFramebufferTexture2DMultisampleEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples) = nullptr;
		bool EXT_multisampled_render_to_texture = false;

		//multisampled render to texture2
		bool EXT_multisampled_render_to_texture2 = false;		

		//multiview draw buffers
		void (*glDrawBuffersIndexedEXT) (GLint n, const GLenum * location, const GLint * indices) = nullptr;
		void (*glGetIntegeri_vEXT) (GLenum target, GLuint index, GLint* data) = nullptr;
		void (*glReadBufferIndexedEXT) (GLenum src, GLint index) = nullptr;
		bool EXT_multiview_draw_buffers = false;

		//packed depth stencil
		bool EXT_packed_depth_stencil = false;

		//packed float
		bool EXT_packed_float = false;

		//packed pixels
		bool EXT_packed_pixels = false;		

		//paletted texture
		void (*glColorTableEXT) (GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const void* data) = nullptr;
		void (*glGetColorTableEXT) (GLenum target, GLenum format, GLenum type, void* data) = nullptr;
		void (*glGetColorTableParameterfvEXT) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetColorTableParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
		bool EXT_paletted_texture = false;		

		//pixel buffer object
		bool EXT_pixel_buffer_object = false;		

		//pixel transform
		void (*glGetPixelTransformParameterfvEXT) (GLenum target, GLenum pname, const GLfloat * params) = nullptr;
		void (*glGetPixelTransformParameterivEXT) (GLenum target, GLenum pname, const GLint* params) = nullptr;
		void (*glPixelTransformParameterfEXT) (GLenum target, GLenum pname, const GLfloat param) = nullptr;
		void (*glPixelTransformParameterfvEXT) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
		void (*glPixelTransformParameteriEXT) (GLenum target, GLenum pname, const GLint param) = nullptr;
		void (*glPixelTransformParameterivEXT) (GLenum target, GLenum pname, const GLint* params) = nullptr;
		bool EXT_pixel_transform = false;

		//pixel transform color table
		bool EXT_pixel_transform_color_table = false;		

		//point parameters
		void (*glPointParameterfEXT) (GLenum pname, GLfloat param) = nullptr;
		void (*glPointParameterfvEXT) (GLenum pname, const GLfloat* params) = nullptr;
		bool EXT_point_parameters = false;		

		//polygon offset
		void (*glPolygonOffsetEXT) (GLfloat factor, GLfloat bias) = nullptr;
		bool EXT_polygon_offset = false;		

		//polygon offset clamp
		void (*glPolygonOffsetClampEXT) (GLfloat factor, GLfloat units, GLfloat clamp) = nullptr;
		bool EXT_polygon_offset_clamp = false;

		//post depth coverage
		bool EXT_post_depth_coverage = false;		

		//provoking vertex
		void (*glProvokingVertexEXT) (GLenum mode) = nullptr;
		bool EXT_provoking_vertex = false;		

		//pvrtc sRGB
		bool EXT_pvrtc_sRGB = false;

		//raster multisample
		void (*glCoverageModulationNV) (GLenum components) = nullptr;
		void (*glCoverageModulationTableNV) (GLsizei n, const GLfloat* v) = nullptr;
		void (*glGetCoverageModulationTableNV) (GLsizei bufsize, GLfloat* v) = nullptr;
		void (*glRasterSamplesEXT) (GLuint samples, GLboolean fixedsamplelocations) = nullptr;
		bool EXT_raster_multisample = false;		

		//read format bgra
		bool EXT_read_format_bgra = false;

		//render snorm
		bool EXT_render_snorm = false;

		//rescale normal
		bool EXT_rescale_normal = false;		

		//sRGB
		bool EXT_sRGB = false;		

		//sRGB write control
		bool EXT_sRGB_write_control = false;

		//scene marker
		void (*glBeginSceneEXT) (void) = nullptr;
		void (*glEndSceneEXT) (void) = nullptr;
		bool EXT_scene_marker = false;		

		//secondary color
		void (*glSecondaryColor3bEXT) (GLbyte red, GLbyte green, GLbyte blue) = nullptr;
		void (*glSecondaryColor3bvEXT) (const GLbyte* v) = nullptr;
		void (*glSecondaryColor3dEXT) (GLdouble red, GLdouble green, GLdouble blue) = nullptr;
		void (*glSecondaryColor3dvEXT) (const GLdouble* v) = nullptr;
		void (*glSecondaryColor3fEXT) (GLfloat red, GLfloat green, GLfloat blue) = nullptr;
		void (*glSecondaryColor3fvEXT) (const GLfloat* v) = nullptr;
		void (*glSecondaryColor3iEXT) (GLint red, GLint green, GLint blue) = nullptr;
		void (*glSecondaryColor3ivEXT) (const GLint* v) = nullptr;
		void (*glSecondaryColor3sEXT) (GLshort red, GLshort green, GLshort blue) = nullptr;
		void (*glSecondaryColor3svEXT) (const GLshort* v) = nullptr;
		void (*glSecondaryColor3ubEXT) (GLubyte red, GLubyte green, GLubyte blue) = nullptr;
		void (*glSecondaryColor3ubvEXT) (const GLubyte* v) = nullptr;
		void (*glSecondaryColor3uiEXT) (GLuint red, GLuint green, GLuint blue) = nullptr;
		void (*glSecondaryColor3uivEXT) (const GLuint* v) = nullptr;
		void (*glSecondaryColor3usEXT) (GLushort red, GLushort green, GLushort blue) = nullptr;
		void (*glSecondaryColor3usvEXT) (const GLushort* v) = nullptr;
		void (*glSecondaryColorPointerEXT) (GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
		bool EXT_secondary_color = false;

		//semaphore
		void (*glDeleteSemaphoresEXT) (GLsizei n, const GLuint * semaphores) = nullptr;
		void (*glGenSemaphoresEXT) (GLsizei n, GLuint* semaphores) = nullptr;
		void (*glGetSemaphoreParameterui64vEXT) (GLuint semaphore, GLenum pname, GLuint64* params) = nullptr;
		GLboolean(*glIsSemaphoreEXT) (GLuint semaphore) = nullptr;
		void (*glSemaphoreParameterui64vEXT) (GLuint semaphore, GLenum pname, const GLuint64* params) = nullptr;
		void (*glSignalSemaphoreEXT) (GLuint semaphore, GLuint numBufferBarriers, const GLuint* buffers, GLuint numTextureBarriers, const GLuint* textures, const GLenum* dstLayouts) = nullptr;
		void (*glWaitSemaphoreEXT) (GLuint semaphore, GLuint numBufferBarriers, const GLuint* buffers, GLuint numTextureBarriers, const GLuint* textures, const GLenum* srcLayouts) = nullptr;
		bool EXT_semaphore = false;

		//semaphore fd
		void (*glImportSemaphoreFdEXT) (GLuint semaphore, GLenum handleType, GLint fd) = nullptr;
		bool EXT_semaphore_fd = false;

		//semaphore win32
		void (*glImportSemaphoreWin32HandleEXT) (GLuint semaphore, GLenum handleType, void* handle) = nullptr;
		void (*glImportSemaphoreWin32NameEXT) (GLuint semaphore, GLenum handleType, const void* name) = nullptr;
		bool EXT_semaphore_win32 = false;

		//separate shader objects
		void (*glActiveProgramEXT) (GLuint program) = nullptr;
		GLuint(*glCreateShaderProgramEXT) (GLenum type, const GLchar* string) = nullptr;
		void (*glUseShaderProgramEXT) (GLenum type, GLuint program) = nullptr;
		bool EXT_separate_shader_objects = false;		

		//separate specular color
		bool EXT_separate_specular_color = false;		

		//shader framebuffer fetch
		bool EXT_shader_framebuffer_fetch = false;

		//shader group vote
		bool EXT_shader_group_vote = false;

		//shader image load formatted
		bool EXT_shader_image_load_formatted = false;

		//shader image load store
		void (*glBindImageTextureEXT) (GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format) = nullptr;
		void (*glMemoryBarrierEXT) (GLbitfield barriers) = nullptr;
		bool EXT_shader_image_load_store = false;

		//shader implicit conversions
		bool EXT_shader_implicit_conversions = false;

		//shader integer mix
		bool EXT_shader_integer_mix = false;

		//shader io blocks
		bool EXT_shader_io_blocks = false;

		//shader non constant global initializers
		bool EXT_shader_non_constant_global_initializers = false;		

		//shader pixel local storage
		bool EXT_shader_pixel_local_storage = false;

		//shader pixel local storage2
		void (*glClearPixelLocalStorageuiEXT) (GLsizei offset, GLsizei n, const GLuint * values) = nullptr;
		void (*glFramebufferPixelLocalStorageSizeEXT) (GLuint target, GLsizei size) = nullptr;
		GLsizei(*glGetFramebufferPixelLocalStorageSizeEXT) (GLuint target) = nullptr;
		bool EXT_shader_pixel_local_storage2 = false;

		//shader texture lod
		bool EXT_shader_texture_lod = false;

		//shadow funcs
		bool EXT_shadow_funcs = false;

		//shadow samplers
		bool EXT_shadow_samplers = false;

		//shared texture palette
		bool EXT_shared_texture_palette = false;

		//sparse texture
		void (*glTexPageCommitmentEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit) = nullptr;
		void (*glTexturePageCommitmentEXT) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit) = nullptr;
		bool EXT_sparse_texture = false;

		//sparse texture2
		bool EXT_sparse_texture2 = false;		

		//stencil clear tag
		bool EXT_stencil_clear_tag = false;		

		//stencil two side
		void (*glActiveStencilFaceEXT) (GLenum face) = nullptr;
		bool EXT_stencil_two_side = false;

		//stencil wrap
		bool EXT_stencil_wrap = false;

		//subtexture
		void (*glTexSubImage1DEXT) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glTexSubImage2DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glTexSubImage3DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
		bool EXT_subtexture = false;

		//texture
		bool EXT_texture = false;		

		//texture3D
		void (*glTexImage3DEXT) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
		bool EXT_texture3D = false;		

		//texture array
		void (*glFramebufferTextureLayerEXT) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
		bool EXT_texture_array = false;		

		//texture buffer object
		void (*glTexBufferEXT) (GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
		bool EXT_texture_buffer_object = false;

		//texture compression astc decode mode
		bool EXT_texture_compression_astc_decode_mode = false;

		//texture compression astc decode mode rgb9e5
		bool EXT_texture_compression_astc_decode_mode_rgb9e5 = false;

		//texture compression bptc
		bool EXT_texture_compression_bptc = false;

		//texture compression dxt1
		bool EXT_texture_compression_dxt1 = false;

		//texture compression latc
		bool EXT_texture_compression_latc = false;

		//texture compression rgtc
		bool EXT_texture_compression_rgtc = false;

		//texture compression s3tc
		bool EXT_texture_compression_s3tc = false;

		//texture cube map
		bool EXT_texture_cube_map = false;

		//texture cube map array
		bool EXT_texture_cube_map_array = false;

		//texture_edge_clamp
		bool EXT_texture_edge_clamp = false;

		//texture_env
		bool EXT_texture_env = false;

		//texture_env_add
		bool EXT_texture_env_add = false;

		//texture_env_combine
		bool EXT_texture_env_combine = false;

		//texture_env_dot3
		bool EXT_texture_env_dot3 = false;

		//texture_filter_anisotropic
		bool EXT_texture_filter_anisotropic = false;

		//texture_filter_minmax
		bool EXT_texture_filter_minmax = false;

		//texture_format_BGRA8888
		bool EXT_texture_format_BGRA8888 = false;

		//texture_integer
		void (*glClearColorIiEXT) (GLint red, GLint green, GLint blue, GLint alpha) = nullptr;
		void (*glClearColorIuiEXT) (GLuint red, GLuint green, GLuint blue, GLuint alpha) = nullptr;
		void (*glGetTexParameterIivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glGetTexParameterIuivEXT) (GLenum target, GLenum pname, GLuint* params) = nullptr;
		void (*glTexParameterIivEXT) (GLenum target, GLenum pname, const GLint* params) = nullptr;
		void (*glTexParameterIuivEXT) (GLenum target, GLenum pname, const GLuint* params) = nullptr;
		bool EXT_texture_integer = false;		

		//texture_lod_bias
		bool EXT_texture_lod_bias = false;

		//texture_mirror_clamp
		bool EXT_texture_mirror_clamp = false;

		//texture_norm16
		bool EXT_texture_norm16 = false;

		//texture_object
		GLboolean(*glAreTexturesResidentEXT) (GLsizei n, const GLuint * textures, GLboolean * residences) = nullptr;
		void (*glBindTextureEXT) (GLenum target, GLuint texture) = nullptr;
		void (*glDeleteTexturesEXT) (GLsizei n, const GLuint* textures) = nullptr;
		void (*glGenTexturesEXT) (GLsizei n, GLuint* textures) = nullptr;
		GLboolean(*glIsTextureEXT) (GLuint texture) = nullptr;
		void (*glPrioritizeTexturesEXT) (GLsizei n, const GLuint* textures, const GLclampf* priorities) = nullptr;
		bool EXT_texture_object = false;

		//texture_perturb_normal
		void (*glTextureNormalEXT) (GLenum mode) = nullptr;
		bool EXT_texture_perturb_normal = false;

		//texture_rectangle
		bool EXT_texture_rectangle = false;

		//texture_rg
		bool EXT_texture_rg = false;

		//texture_sRGB
		bool EXT_texture_sRGB = false;

		//texture_sRGB_R8
		bool EXT_texture_sRGB_R8 = false;

		//texture_sRGB_RG8
		bool EXT_texture_sRGB_RG8 = false;
		
		//texture_sRGB_decode
		bool EXT_texture_sRGB_decode = false;

		//texture_shared_exponent
		bool EXT_texture_shared_exponent = false;

		//texture_snorm
		bool EXT_texture_snorm = false;

		//texture_storage
		void (*glTexStorage1DEXT) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) = nullptr;
		void (*glTexStorage2DEXT) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
		void (*glTexStorage3DEXT) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
		void (*glTextureStorage1DEXT) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) = nullptr;
		void (*glTextureStorage2DEXT) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
		void (*glTextureStorage3DEXT) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
		bool EXT_texture_storage = false;

		//texture_swizzle
		bool EXT_texture_swizzle = false;

		//texture_type_2_10_10_10_REV
		bool EXT_texture_type_2_10_10_10_REV = false;

		//texture_view
		void (*glTextureViewEXT) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) = nullptr;
		bool EXT_texture_view = false;

		//timer_query
		void (*glGetQueryObjecti64vEXT) (GLuint id, GLenum pname, GLint64EXT * params) = nullptr;
		void (*glGetQueryObjectui64vEXT) (GLuint id, GLenum pname, GLuint64EXT* params) = nullptr;
		bool EXT_timer_query = false;

		//transform_feedback
		void (*glBeginTransformFeedbackEXT) (GLenum primitiveMode) = nullptr;
		void (*glBindBufferBaseEXT) (GLenum target, GLuint index, GLuint buffer) = nullptr;
		void (*glBindBufferOffsetEXT) (GLenum target, GLuint index, GLuint buffer, GLintptr offset) = nullptr;
		void (*glBindBufferRangeEXT) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
		void (*glEndTransformFeedbackEXT) (void) = nullptr;
		void (*glGetTransformFeedbackVaryingEXT) (GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) = nullptr;
		void (*glTransformFeedbackVaryingsEXT) (GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode) = nullptr;
		bool EXT_transform_feedback = false;

		//unpack_subimage
		bool EXT_unpack_subimage = false;

		//vertex_array
		void (*glArrayElementEXT) (GLint i) = nullptr;
		void (*glColorPointerEXT) (GLint size, GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
		void (*glDrawArraysEXT) (GLenum mode, GLint first, GLsizei count) = nullptr;
		void (*glEdgeFlagPointerEXT) (GLsizei stride, GLsizei count, const GLboolean* pointer) = nullptr;
		void (*glIndexPointerEXT) (GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
		void (*glNormalPointerEXT) (GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
		void (*glTexCoordPointerEXT) (GLint size, GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
		void (*glVertexPointerEXT) (GLint size, GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
		bool EXT_vertex_array = false;

		//vertex_array_bgra
		bool EXT_vertex_array_bgra = false;

		//vertex_array_setXXX
		void (*glBindArraySetEXT) (const void* arrayset) = nullptr;
		const void* (*glCreateArraySetExt) (void) = nullptr;
		void (*glDeleteArraySetsEXT) (GLsizei n, const void* arrayset[]) = nullptr;
		bool EXT_vertex_array_setXXX = false;	

		//vertex_attrib_64bit
		void (*glGetVertexAttribLdvEXT) (GLuint index, GLenum pname, GLdouble * params) = nullptr;
		void (*glVertexArrayVertexAttribLOffsetEXT) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
		void (*glVertexAttribL1dEXT) (GLuint index, GLdouble x) = nullptr;
		void (*glVertexAttribL1dvEXT) (GLuint index, const GLdouble* v) = nullptr;
		void (*glVertexAttribL2dEXT) (GLuint index, GLdouble x, GLdouble y) = nullptr;
		void (*glVertexAttribL2dvEXT) (GLuint index, const GLdouble* v) = nullptr;
		void (*glVertexAttribL3dEXT) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
		void (*glVertexAttribL3dvEXT) (GLuint index, const GLdouble* v) = nullptr;
		void (*glVertexAttribL4dEXT) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
		void (*glVertexAttribL4dvEXT) (GLuint index, const GLdouble* v) = nullptr;
		void (*glVertexAttribLPointerEXT) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
		bool EXT_vertex_attrib_64bit = false;		
	
		//vertex_shader
		void (*glBeginVertexShaderEXT) (void) = nullptr;
		GLuint(*glBindLightParameterEXT) (GLenum light, GLenum value) = nullptr;
		GLuint(*glBindMaterialParameterEXT) (GLenum face, GLenum value) = nullptr;
		GLuint(*glBindParameterEXT) (GLenum value) = nullptr;
		GLuint(*glBindTexGenParameterEXT) (GLenum unit, GLenum coord, GLenum value) = nullptr;
		GLuint(*glBindTextureUnitParameterEXT) (GLenum unit, GLenum value) = nullptr;
		void (*glBindVertexShaderEXT) (GLuint id) = nullptr;
		void (*glDeleteVertexShaderEXT) (GLuint id) = nullptr;
		void (*glDisableVariantClientStateEXT) (GLuint id) = nullptr;
		void (*glEnableVariantClientStateEXT) (GLuint id) = nullptr;
		void (*glEndVertexShaderEXT) (void) = nullptr;
		void (*glExtractComponentEXT) (GLuint res, GLuint src, GLuint num) = nullptr;
		GLuint(*glGenSymbolsEXT) (GLenum dataType, GLenum storageType, GLenum range, GLuint components) = nullptr;
		GLuint(*glGenVertexShadersEXT) (GLuint range) = nullptr;
		void (*glGetInvariantBooleanvEXT) (GLuint id, GLenum value, GLboolean* data) = nullptr;
		void (*glGetInvariantFloatvEXT) (GLuint id, GLenum value, GLfloat* data) = nullptr;
		void (*glGetInvariantIntegervEXT) (GLuint id, GLenum value, GLint* data) = nullptr;
		void (*glGetLocalConstantBooleanvEXT) (GLuint id, GLenum value, GLboolean* data) = nullptr;
		void (*glGetLocalConstantFloatvEXT) (GLuint id, GLenum value, GLfloat* data) = nullptr;
		void (*glGetLocalConstantIntegervEXT) (GLuint id, GLenum value, GLint* data) = nullptr;
		void (*glGetVariantBooleanvEXT) (GLuint id, GLenum value, GLboolean* data) = nullptr;
		void (*glGetVariantFloatvEXT) (GLuint id, GLenum value, GLfloat* data) = nullptr;
		void (*glGetVariantIntegervEXT) (GLuint id, GLenum value, GLint* data) = nullptr;
		void (*glGetVariantPointervEXT) (GLuint id, GLenum value, void** data) = nullptr;
		void (*glInsertComponentEXT) (GLuint res, GLuint src, GLuint num) = nullptr;
		GLboolean(*glIsVariantEnabledEXT) (GLuint id, GLenum cap) = nullptr;
		void (*glSetInvariantEXT) (GLuint id, GLenum type, void* addr) = nullptr;
		void (*glSetLocalConstantEXT) (GLuint id, GLenum type, void* addr) = nullptr;
		void (*glShaderOp1EXT) (GLenum op, GLuint res, GLuint arg1) = nullptr;
		void (*glShaderOp2EXT) (GLenum op, GLuint res, GLuint arg1, GLuint arg2) = nullptr;
		void (*glShaderOp3EXT) (GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3) = nullptr;
		void (*glSwizzleEXT) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW) = nullptr;
		void (*glVariantPointerEXT) (GLuint id, GLenum type, GLuint stride, void* addr) = nullptr;
		void (*glVariantbvEXT) (GLuint id, GLbyte* addr) = nullptr;
		void (*glVariantdvEXT) (GLuint id, GLdouble* addr) = nullptr;
		void (*glVariantfvEXT) (GLuint id, GLfloat* addr) = nullptr;
		void (*glVariantivEXT) (GLuint id, GLint* addr) = nullptr;
		void (*glVariantsvEXT) (GLuint id, GLshort* addr) = nullptr;
		void (*glVariantubvEXT) (GLuint id, GLubyte* addr) = nullptr;
		void (*glVariantuivEXT) (GLuint id, GLuint* addr) = nullptr;
		void (*glVariantusvEXT) (GLuint id, GLushort* addr) = nullptr;
		void (*glWriteMaskEXT) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW) = nullptr;
		bool EXT_vertex_shader = false;

		//vertex_weighting
		void (*glVertexWeightPointerEXT) (GLint size, GLenum type, GLsizei stride, void* pointer) = nullptr;
		void (*glVertexWeightfEXT) (GLfloat weight) = nullptr;
		void (*glVertexWeightfvEXT) (GLfloat* weight) = nullptr;
		bool EXT_vertex_weighting = false;

		//win32_keyed_mutex
		GLboolean(*glAcquireKeyedMutexWin32EXT) (GLuint memory, GLuint64 key, GLuint timeout) = nullptr;
		GLboolean(*glReleaseKeyedMutexWin32EXT) (GLuint memory, GLuint64 key) = nullptr;
		bool EXT_win32_keyed_mutex = false;
		
		//window_rectangles
		void (*glWindowRectanglesEXT) (GLenum mode, GLsizei count, const GLint box[]) = nullptr;
		bool EXT_window_rectangles = false;

		//x11_sync_object
		GLsync(*glImportSyncEXT) (GLenum external_sync_type, GLintptr external_sync, GLbitfield flags) = nullptr;
		bool EXT_x11_sync_object = false;

		//*< load EXT Extensions
		void LoadEXTExtensions()
		{
			//422 pixels
			FetchProcAddress(EXT_422_pixels, "EXT_422_pixels");

			//Cg shader
			FetchProcAddress(EXT_Cg_shader, "EXT_Cg_shader");

			//EGL image array
			FetchProcAddress(EXT_EGL_image_array, "EXT_EGL_image_array");

			//YUV target
			FetchProcAddress(EXT_YUV_target, "EXT_YUV_target");

			//abgr
			FetchProcAddress(EXT_abgr, "EXT_abgr");

			//base instance
			FetchProcAddress(glDrawArraysInstancedBaseInstanceEXT, "glDrawArraysInstancedBaseInstanceEXT");
			FetchProcAddress(glDrawElementsInstancedBaseInstanceEXT, "glDrawElementsInstancedBaseInstanceEXT");
			FetchProcAddress(glDrawElementsInstancedBaseVertexBaseInstanceEXT, "glDrawElementsInstancedBaseVertexBaseInstanceEXT");
			FetchProcAddress(EXT_base_instance, "EXT_base_instance");

			//bgra
			FetchProcAddress(EXT_bgra, "EXT_bgra");

			//bindable uniform
			FetchProcAddress(glGetUniformBufferSizeEXT, "glGetUniformBufferSizeEXT");
			FetchProcAddress(glGetUniformOffsetEXT, "glGetUniformOffsetEXT");
			FetchProcAddress(glUniformBufferEXT, "glUniformBufferEXT");
			FetchProcAddress(EXT_bindable_uniform, "EXT_bindable_uniform");

			//blend color
			FetchProcAddress(glBlendColorEXT, "glBlendColorEXT");
			FetchProcAddress(EXT_blend_color, "EXT_blend_color");

			//blend equation separate
			FetchProcAddress(glBlendEquationSeparateEXT, "glBlendEquationSeparateEXT");
			FetchProcAddress(EXT_blend_equation_separate, "EXT_blend_equation_separate");

			//blend func extended
			FetchProcAddress(glBindFragDataLocationIndexedEXT, "glBindFragDataLocationIndexedEXT");
			FetchProcAddress(glGetFragDataIndexEXT, "glGetFragDataIndexEXT");
			FetchProcAddress(glGetProgramResourceLocationIndexEXT, "glGetProgramResourceLocationIndexEXT");
			FetchProcAddress(EXT_blend_func_extended, "EXT_blend_func_extended");

			//blend func separate
			FetchProcAddress(glBlendFuncSeparateEXT, "glBlendFuncSeparateEXT");
			FetchProcAddress(EXT_blend_func_separate, "EXT_blend_func_separate");

			//blend logic op
			FetchProcAddress(EXT_blend_logic_op, "EXT_blend_logic_op");

			//blend minmax
			FetchProcAddress(glBlendEquationEXT, "glBlendEquationEXT");
			FetchProcAddress(EXT_blend_minmax, "EXT_blend_minmax");

			//blend subtract
			FetchProcAddress(EXT_blend_subtract, "EXT_blend_subtract");

			//buffer storage
			FetchProcAddress(glBufferStorageEXT, "glBufferStorageEXT");
			FetchProcAddress(glNamedBufferStorageEXT, "glNamedBufferStorageEXT");
			FetchProcAddress(EXT_buffer_storage, "EXT_buffer_storage");

			//clear texture
			FetchProcAddress(glClearTexImageEXT, "glClearTexImageEXT");
			FetchProcAddress(glClearTexSubImageEXT, "glClearTexSubImageEXT");
			FetchProcAddress(EXT_clear_texture, "EXT_clear_texture");

			//clip cull distance
			FetchProcAddress(EXT_clip_cull_distance, "EXT_clip_cull_distance");

			//clip volume hint
			FetchProcAddress(EXT_clip_volume_hint, "EXT_clip_volume_hint");

			//cmyka
			FetchProcAddress(EXT_cmyka, "EXT_cmyka");

			//color buffer float
			FetchProcAddress(EXT_color_buffer_float, "EXT_color_buffer_float");

			//color buffer half float
			FetchProcAddress(EXT_color_buffer_half_float, "EXT_color_buffer_half_float");

			//color subtable
			FetchProcAddress(glColorSubTableEXT, "glColorSubTableEXT");
			FetchProcAddress(glCopyColorSubTableEXT, "glCopyColorSubTableEXT");
			FetchProcAddress(EXT_color_subtable, "EXT_color_subtable");

			//compiled vertex array
			FetchProcAddress(glLockArraysEXT, "glLockArraysEXT");
			FetchProcAddress(glUnlockArraysEXT, "glUnlockArraysEXT");
			FetchProcAddress(EXT_compiled_vertex_array, "EXT_compiled_vertex_array");

			//compressed ETC1 RGB8 sub texture
			FetchProcAddress(EXT_compressed_ETC1_RGB8_sub_texture, "EXT_compressed_ETC1_RGB8_sub_texture");

			//conservative depth
			FetchProcAddress(EXT_conservative_depth, "EXT_conservative_depth");

			//convolution
			FetchProcAddress(glConvolutionFilter1DEXT, "glConvolutionFilter1DEXT");
			FetchProcAddress(glConvolutionFilter2DEXT, "glConvolutionFilter2DEXT");
			FetchProcAddress(glConvolutionParameterfEXT, "glConvolutionParameterfEXT");
			FetchProcAddress(glConvolutionParameterfvEXT, "glConvolutionParameterfvEXT");
			FetchProcAddress(glConvolutionParameteriEXT, "glConvolutionParameteriEXT");
			FetchProcAddress(glConvolutionParameterivEXT, "glConvolutionParameterivEXT");
			FetchProcAddress(glCopyConvolutionFilter1DEXT, "glCopyConvolutionFilter1DEXT");
			FetchProcAddress(glCopyConvolutionFilter2DEXT, "glCopyConvolutionFilter2DEXT");
			FetchProcAddress(glGetConvolutionFilterEXT, "glGetConvolutionFilterEXT");
			FetchProcAddress(glGetConvolutionParameterfvEXT, "glGetConvolutionParameterfvEXT");
			FetchProcAddress(glGetConvolutionParameterivEXT, "glGetConvolutionParameterivEXT");
			FetchProcAddress(glGetSeparableFilterEXT, "glGetSeparableFilterEXT");
			FetchProcAddress(glSeparableFilter2DEXT, "glSeparableFilter2DEXT");
			FetchProcAddress(EXT_convolution, "EXT_convolution");

			//coordinate frame
			FetchProcAddress(glBinormalPointerEXT, "glBinormalPointerEXT");
			FetchProcAddress(glTangentPointerEXT, "glTangentPointerEXT");
			FetchProcAddress(EXT_coordinate_frame, "EXT_coordinate_frame");

			//copy image
			FetchProcAddress(glCopyImageSubDataEXT, "glCopyImageSubDataEXT");
			FetchProcAddress(EXT_copy_image, "EXT_copy_image");

			//copy texture
			FetchProcAddress(glCopyTexImage1DEXT, "glCopyTexImage1DEXT");
			FetchProcAddress(glCopyTexImage2DEXT, "glCopyTexImage2DEXT");
			FetchProcAddress(glCopyTexSubImage1DEXT, "glCopyTexSubImage1DEXT");
			FetchProcAddress(glCopyTexSubImage2DEXT, "glCopyTexSubImage2DEXT");
			FetchProcAddress(glCopyTexSubImage3DEXT, "glCopyTexSubImage3DEXT");
			FetchProcAddress(EXT_copy_texture, "EXT_copy_texture");

			//cull vertex
			FetchProcAddress(glCullParameterdvEXT, "glCullParameterdvEXT");
			FetchProcAddress(glCullParameterfvEXT, "glCullParameterfvEXT");
			FetchProcAddress(EXT_cull_vertex, "EXT_cull_vertex");

			//debug label
			FetchProcAddress(glGetObjectLabelEXT, "glGetObjectLabelEXT");
			FetchProcAddress(glLabelObjectEXT, "glLabelObjectEXT");
			FetchProcAddress(EXT_debug_label, "EXT_debug_label");

			//debug marker
			FetchProcAddress(glInsertEventMarkerEXT, "glInsertEventMarkerEXT");
			FetchProcAddress(glPopGroupMarkerEXT, "glPopGroupMarkerEXT");
			FetchProcAddress(glPushGroupMarkerEXT, "glPushGroupMarkerEXT");
			FetchProcAddress(EXT_debug_marker, "EXT_debug_marker");

			//depth bounds test
			FetchProcAddress(glDepthBoundsEXT, "glDepthBoundsEXT");
			FetchProcAddress(EXT_depth_bounds_test, "EXT_depth_bounds_test");

			//direct state access
			FetchProcAddress(glBindMultiTextureEXT, "glBindMultiTextureEXT");
			FetchProcAddress(glCheckNamedFramebufferStatusEXT, "glCheckNamedFramebufferStatusEXT");
			FetchProcAddress(glClientAttribDefaultEXT, "glClientAttribDefaultEXT");
			FetchProcAddress(glCompressedMultiTexImage1DEXT, "glCompressedMultiTexImage1DEXT");
			FetchProcAddress(glCompressedMultiTexImage2DEXT, "glCompressedMultiTexImage2DEXT");
			FetchProcAddress(glCompressedMultiTexImage3DEXT, "glCompressedMultiTexImage3DEXT");
			FetchProcAddress(glCompressedMultiTexSubImage1DEXT, "glCompressedMultiTexSubImage1DEXT");
			FetchProcAddress(glCompressedMultiTexSubImage2DEXT, "glCompressedMultiTexSubImage2DEXT");
			FetchProcAddress(glCompressedMultiTexSubImage3DEXT, "glCompressedMultiTexSubImage3DEXT");
			FetchProcAddress(glCompressedTextureImage1DEXT, "glCompressedTextureImage1DEXT");
			FetchProcAddress(glCompressedTextureImage2DEXT, "glCompressedTextureImage2DEXT");
			FetchProcAddress(glCompressedTextureImage3DEXT, "glCompressedTextureImage3DEXT");
			FetchProcAddress(glCompressedTextureSubImage1DEXT, "glCompressedTextureSubImage1DEXT");
			FetchProcAddress(glCompressedTextureSubImage2DEXT, "glCompressedTextureSubImage2DEXT");
			FetchProcAddress(glCompressedTextureSubImage3DEXT, "glCompressedTextureSubImage3DEXT");
			FetchProcAddress(glCopyMultiTexImage1DEXT, "glCopyMultiTexImage1DEXT");
			FetchProcAddress(glCopyMultiTexImage2DEXT, "glCopyMultiTexImage2DEXT");
			FetchProcAddress(glCopyMultiTexSubImage1DEXT, "glCopyMultiTexSubImage1DEXT");
			FetchProcAddress(glCopyMultiTexSubImage2DEXT, "glCopyMultiTexSubImage2DEXT");
			FetchProcAddress(glCopyMultiTexSubImage3DEXT, "glCopyMultiTexSubImage3DEXT");
			FetchProcAddress(glCopyTextureImage1DEXT, "glCopyTextureImage1DEXT");
			FetchProcAddress(glCopyTextureImage2DEXT, "glCopyTextureImage2DEXT");
			FetchProcAddress(glCopyTextureSubImage1DEXT, "glCopyTextureSubImage1DEXT");
			FetchProcAddress(glCopyTextureSubImage2DEXT, "glCopyTextureSubImage2DEXT");
			FetchProcAddress(glCopyTextureSubImage3DEXT, "glCopyTextureSubImage3DEXT");
			FetchProcAddress(glDisableClientStateIndexedEXT, "glDisableClientStateIndexedEXT");
			FetchProcAddress(glDisableClientStateiEXT, "glDisableClientStateiEXT");
			FetchProcAddress(glDisableVertexArrayAttribEXT, "glDisableVertexArrayAttribEXT");
			FetchProcAddress(glDisableVertexArrayEXT, "glDisableVertexArrayEXT");
			FetchProcAddress(glEnableClientStateIndexedEXT, "glEnableClientStateIndexedEXT");
			FetchProcAddress(glEnableClientStateiEXT, "glEnableClientStateiEXT");
			FetchProcAddress(glEnableVertexArrayAttribEXT, "glEnableVertexArrayAttribEXT");
			FetchProcAddress(glEnableVertexArrayEXT, "glEnableVertexArrayEXT");
			FetchProcAddress(glFlushMappedNamedBufferRangeEXT, "glFlushMappedNamedBufferRangeEXT");
			FetchProcAddress(glFramebufferDrawBufferEXT, "glFramebufferDrawBufferEXT");
			FetchProcAddress(glFramebufferDrawBuffersEXT, "glFramebufferDrawBuffersEXT");
			FetchProcAddress(glFramebufferReadBufferEXT, "glFramebufferReadBufferEXT");
			FetchProcAddress(glGenerateMultiTexMipmapEXT, "glGenerateMultiTexMipmapEXT");
			FetchProcAddress(glGenerateTextureMipmapEXT, "glGenerateTextureMipmapEXT");
			FetchProcAddress(glGetCompressedMultiTexImageEXT, "glGetCompressedMultiTexImageEXT");
			FetchProcAddress(glGetCompressedTextureImageEXT, "glGetCompressedTextureImageEXT");

			FetchProcAddress(glGetDoubleIndexedvEXT, "glGetDoubleIndexedvEXT");

			FetchProcAddress(glGetDoublei_vEXT, "glGetDoublei_vEXT");

			FetchProcAddress(glGetFloatIndexedvEXT, "glGetFloatIndexedvEXT");

			FetchProcAddress(glGetFloati_vEXT, "glGetFloati_vEXT");

			FetchProcAddress(glGetFramebufferParameterivEXT, "glGetFramebufferParameterivEXT");

			FetchProcAddress(glGetMultiTexEnvfvEXT, "glGetMultiTexEnvfvEXT");

			FetchProcAddress(glGetMultiTexEnvivEXT, "glGetMultiTexEnvivEXT");

			FetchProcAddress(glGetMultiTexGendvEXT, "glGetMultiTexGendvEXT");

			FetchProcAddress(glGetMultiTexGenfvEXT, "glGetMultiTexGenfvEXT");

			FetchProcAddress(glGetMultiTexGenivEXT, "glGetMultiTexGenivEXT");

			FetchProcAddress(glGetMultiTexImageEXT, "glGetMultiTexImageEXT");

			FetchProcAddress(glGetMultiTexLevelParameterfvEXT, "glGetMultiTexLevelParameterfvEXT");

			FetchProcAddress(glGetMultiTexLevelParameterivEXT, "glGetMultiTexLevelParameterivEXT");

			FetchProcAddress(glGetMultiTexParameterIivEXT, "glGetMultiTexParameterIivEXT");

			FetchProcAddress(glGetMultiTexParameterIuivEXT, "glGetMultiTexParameterIuivEXT");

			FetchProcAddress(glGetMultiTexParameterfvEXT, "glGetMultiTexParameterfvEXT");

			FetchProcAddress(glGetMultiTexParameterivEXT, "glGetMultiTexParameterivEXT");

			FetchProcAddress(glGetNamedBufferParameterivEXT, "glGetNamedBufferParameterivEXT");

			FetchProcAddress(glGetNamedBufferPointervEXT, "glGetNamedBufferPointervEXT");

			FetchProcAddress(glGetNamedBufferSubDataEXT, "glGetNamedBufferSubDataEXT");

			FetchProcAddress(glGetNamedFramebufferAttachmentParameterivEXT, "glGetNamedFramebufferAttachmentParameterivEXT");

			FetchProcAddress(glGetNamedProgramLocalParameterIivEXT, "glGetNamedProgramLocalParameterIivEXT");

			FetchProcAddress(glGetNamedProgramLocalParameterIuivEXT, "glGetNamedProgramLocalParameterIuivEXT");

			FetchProcAddress(glGetNamedProgramLocalParameterdvEXT, "glGetNamedProgramLocalParameterdvEXT");

			FetchProcAddress(glGetNamedProgramLocalParameterfvEXT, "glGetNamedProgramLocalParameterfvEXT");

			FetchProcAddress(glGetNamedProgramStringEXT, "glGetNamedProgramStringEXT");

			FetchProcAddress(glGetNamedProgramivEXT, "glGetNamedProgramivEXT");

			FetchProcAddress(glGetNamedRenderbufferParameterivEXT, "glGetNamedRenderbufferParameterivEXT");

			FetchProcAddress(glGetPointerIndexedvEXT, "glGetPointerIndexedvEXT");

			FetchProcAddress(glGetPointeri_vEXT, "glGetPointeri_vEXT");

			FetchProcAddress(glGetTextureImageEXT, "glGetTextureImageEXT");

			FetchProcAddress(glGetTextureLevelParameterfvEXT, "glGetTextureLevelParameterfvEXT");

			FetchProcAddress(glGetTextureLevelParameterivEXT, "glGetTextureLevelParameterivEXT");

			FetchProcAddress(glGetTextureParameterIivEXT, "glGetTextureParameterIivEXT");

			FetchProcAddress(glGetTextureParameterIuivEXT, "glGetTextureParameterIuivEXT");

			FetchProcAddress(glGetTextureParameterfvEXT, "glGetTextureParameterfvEXT");

			FetchProcAddress(glGetTextureParameterivEXT, "glGetTextureParameterivEXT");

			FetchProcAddress(glGetVertexArrayIntegeri_vEXT, "glGetVertexArrayIntegeri_vEXT");

			FetchProcAddress(glGetVertexArrayIntegervEXT, "glGetVertexArrayIntegervEXT");

			FetchProcAddress(glGetVertexArrayPointeri_vEXT, "glGetVertexArrayPointeri_vEXT");

			FetchProcAddress(glGetVertexArrayPointervEXT, "glGetVertexArrayPointervEXT");

			FetchProcAddress(glMapNamedBufferEXT, "glMapNamedBufferEXT");

			FetchProcAddress(glMapNamedBufferRangeEXT, "glMapNamedBufferRangeEXT");

			FetchProcAddress(glMatrixFrustumEXT, "glMatrixFrustumEXT");

			FetchProcAddress(glMatrixLoadIdentityEXT, "glMatrixLoadIdentityEXT");

			FetchProcAddress(glMatrixLoadTransposedEXT, "glMatrixLoadTransposedEXT");

			FetchProcAddress(glMatrixLoadTransposefEXT, "glMatrixLoadTransposefEXT");

			FetchProcAddress(glMatrixLoaddEXT, "glMatrixLoaddEXT");

			FetchProcAddress(glMatrixLoadfEXT, "glMatrixLoadfEXT");

			FetchProcAddress(glMatrixMultTransposedEXT, "glMatrixMultTransposedEXT");

			FetchProcAddress(glMatrixMultTransposefEXT, "glMatrixMultTransposefEXT");

			FetchProcAddress(glMatrixMultdEXT, "glMatrixMultdEXT");

			FetchProcAddress(glMatrixMultfEXT, "glMatrixMultfEXT");

			FetchProcAddress(glMatrixOrthoEXT, "glMatrixOrthoEXT");

			FetchProcAddress(glMatrixPopEXT, "glMatrixPopEXT");

			FetchProcAddress(glMatrixPushEXT, "glMatrixPushEXT");

			FetchProcAddress(glMatrixRotatedEXT, "glMatrixRotatedEXT");

			FetchProcAddress(glMatrixRotatefEXT, "glMatrixRotatefEXT");

			FetchProcAddress(glMatrixScaledEXT, "glMatrixScaledEXT");

			FetchProcAddress(glMatrixScalefEXT, "glMatrixScalefEXT");

			FetchProcAddress(glMatrixTranslatedEXT, "glMatrixTranslatedEXT");

			FetchProcAddress(glMatrixTranslatefEXT, "glMatrixTranslatefEXT");

			FetchProcAddress(glMultiTexBufferEXT, "glMultiTexBufferEXT");

			FetchProcAddress(glMultiTexCoordPointerEXT, "glMultiTexCoordPointerEXT");

			FetchProcAddress(glMultiTexEnvfEXT, "glMultiTexEnvfEXT");

			FetchProcAddress(glMultiTexEnvfvEXT, "glMultiTexEnvfvEXT");

			FetchProcAddress(glMultiTexEnviEXT, "glMultiTexEnviEXT");

			FetchProcAddress(glMultiTexEnvivEXT, "glMultiTexEnvivEXT");

			FetchProcAddress(glMultiTexGendEXT, "glMultiTexGendEXT");

			FetchProcAddress(glMultiTexGendvEXT, "glMultiTexGendvEXT");

			FetchProcAddress(glMultiTexGenfEXT, "glMultiTexGenfEXT");

			FetchProcAddress(glMultiTexGenfvEXT, "glMultiTexGenfvEXT");

			FetchProcAddress(glMultiTexGeniEXT, "glMultiTexGeniEXT");

			FetchProcAddress(glMultiTexGenivEXT, "glMultiTexGenivEXT");

			FetchProcAddress(glMultiTexImage1DEXT, "glMultiTexImage1DEXT");

			FetchProcAddress(glMultiTexImage2DEXT, "glMultiTexImage2DEXT");

			FetchProcAddress(glMultiTexImage3DEXT, "glMultiTexImage3DEXT");

			FetchProcAddress(glMultiTexParameterIivEXT, "glMultiTexParameterIivEXT");

			FetchProcAddress(glMultiTexParameterIuivEXT, "glMultiTexParameterIuivEXT");

			FetchProcAddress(glMultiTexParameterfEXT, "glMultiTexParameterfEXT");

			FetchProcAddress(glMultiTexParameterfvEXT, "glMultiTexParameterfvEXT");

			FetchProcAddress(glMultiTexParameteriEXT, "glMultiTexParameteriEXT");

			FetchProcAddress(glMultiTexParameterivEXT, "glMultiTexParameterivEXT");

			FetchProcAddress(glMultiTexRenderbufferEXT, "glMultiTexRenderbufferEXT");

			FetchProcAddress(glMultiTexSubImage1DEXT, "glMultiTexSubImage1DEXT");

			FetchProcAddress(glMultiTexSubImage2DEXT, "glMultiTexSubImage2DEXT");

			FetchProcAddress(glMultiTexSubImage3DEXT, "glMultiTexSubImage3DEXT");

			FetchProcAddress(glNamedBufferDataEXT, "glNamedBufferDataEXT");

			FetchProcAddress(glNamedBufferSubDataEXT, "glNamedBufferSubDataEXT");

			FetchProcAddress(glNamedCopyBufferSubDataEXT, "glNamedCopyBufferSubDataEXT");

			FetchProcAddress(glNamedFramebufferRenderbufferEXT, "glNamedFramebufferRenderbufferEXT");

			FetchProcAddress(glNamedFramebufferTexture1DEXT, "glNamedFramebufferTexture1DEXT");

			FetchProcAddress(glNamedFramebufferTexture2DEXT, "glNamedFramebufferTexture2DEXT");

			FetchProcAddress(glNamedFramebufferTexture3DEXT, "glNamedFramebufferTexture3DEXT");

			FetchProcAddress(glNamedFramebufferTextureEXT, "glNamedFramebufferTextureEXT");

			FetchProcAddress(glNamedFramebufferTextureFaceEXT, "glNamedFramebufferTextureFaceEXT");

			FetchProcAddress(glNamedFramebufferTextureLayerEXT, "glNamedFramebufferTextureLayerEXT");

			FetchProcAddress(glNamedProgramLocalParameter4dEXT, "glNamedProgramLocalParameter4dEXT");

			FetchProcAddress(glNamedProgramLocalParameter4dvEXT, "glNamedProgramLocalParameter4dvEXT");

			FetchProcAddress(glNamedProgramLocalParameter4fEXT, "glNamedProgramLocalParameter4fEXT");

			FetchProcAddress(glNamedProgramLocalParameter4fvEXT, "glNamedProgramLocalParameter4fvEXT");

			FetchProcAddress(glNamedProgramLocalParameterI4iEXT, "glNamedProgramLocalParameterI4iEXT");

			FetchProcAddress(glNamedProgramLocalParameterI4ivEXT, "glNamedProgramLocalParameterI4ivEXT");

			FetchProcAddress(glNamedProgramLocalParameterI4uiEXT, "glNamedProgramLocalParameterI4uiEXT");

			FetchProcAddress(glNamedProgramLocalParameterI4uivEXT, "glNamedProgramLocalParameterI4uivEXT");

			FetchProcAddress(glNamedProgramLocalParameters4fvEXT, "glNamedProgramLocalParameters4fvEXT");

			FetchProcAddress(glNamedProgramLocalParametersI4ivEXT, "glNamedProgramLocalParametersI4ivEXT");

			FetchProcAddress(glNamedProgramLocalParametersI4uivEXT, "glNamedProgramLocalParametersI4uivEXT");

			FetchProcAddress(glNamedProgramStringEXT, "glNamedProgramStringEXT");

			FetchProcAddress(glNamedRenderbufferStorageEXT, "glNamedRenderbufferStorageEXT");

			FetchProcAddress(glNamedRenderbufferStorageMultisampleCoverageEXT, "glNamedRenderbufferStorageMultisampleCoverageEXT");

			FetchProcAddress(glNamedRenderbufferStorageMultisampleEXT, "glNamedRenderbufferStorageMultisampleEXT");

			FetchProcAddress(glProgramUniform1fEXT, "glProgramUniform1fEXT");

			FetchProcAddress(glProgramUniform1fvEXT, "glProgramUniform1fvEXT");

			FetchProcAddress(glProgramUniform1iEXT, "glProgramUniform1iEXT");

			FetchProcAddress(glProgramUniform1ivEXT, "glProgramUniform1ivEXT");

			FetchProcAddress(glProgramUniform1uiEXT, "glProgramUniform1uiEXT");

			FetchProcAddress(glProgramUniform1uivEXT, "glProgramUniform1uivEXT");

			FetchProcAddress(glProgramUniform2fEXT, "glProgramUniform2fEXT");

			FetchProcAddress(glProgramUniform2fvEXT, "glProgramUniform2fvEXT");

			FetchProcAddress(glProgramUniform2iEXT, "glProgramUniform2iEXT");

			FetchProcAddress(glProgramUniform2ivEXT, "glProgramUniform2ivEXT");

			FetchProcAddress(glProgramUniform2uiEXT, "glProgramUniform2uiEXT");

			FetchProcAddress(glProgramUniform2uivEXT, "glProgramUniform2uivEXT");

			FetchProcAddress(glProgramUniform3fEXT, "glProgramUniform3fEXT");

			FetchProcAddress(glProgramUniform3fvEXT, "glProgramUniform3fvEXT");

			FetchProcAddress(glProgramUniform3iEXT, "glProgramUniform3iEXT");

			FetchProcAddress(glProgramUniform3ivEXT, "glProgramUniform3ivEXT");

			FetchProcAddress(glProgramUniform3uiEXT, "glProgramUniform3uiEXT");

			FetchProcAddress(glProgramUniform3uivEXT, "glProgramUniform3uivEXT");

			FetchProcAddress(glProgramUniform4fEXT, "glProgramUniform4fEXT");

			FetchProcAddress(glProgramUniform4fvEXT, "glProgramUniform4fvEXT");

			FetchProcAddress(glProgramUniform4iEXT, "glProgramUniform4iEXT");

			FetchProcAddress(glProgramUniform4ivEXT, "glProgramUniform4ivEXT");

			FetchProcAddress(glProgramUniform4uiEXT, "glProgramUniform4uiEXT");

			FetchProcAddress(glProgramUniform4uivEXT, "glProgramUniform4uivEXT");

			FetchProcAddress(glProgramUniformMatrix2fvEXT, "glProgramUniformMatrix2fvEXT");

			FetchProcAddress(glProgramUniformMatrix2x3fvEXT, "glProgramUniformMatrix2x3fvEXT");

			FetchProcAddress(glProgramUniformMatrix2x4fvEXT, "glProgramUniformMatrix2x4fvEXT");

			FetchProcAddress(glProgramUniformMatrix3fvEXT, "glProgramUniformMatrix3fvEXT");

			FetchProcAddress(glProgramUniformMatrix3x2fvEXT, "glProgramUniformMatrix3x2fvEXT");

			FetchProcAddress(glProgramUniformMatrix3x4fvEXT, "glProgramUniformMatrix3x4fvEXT");

			FetchProcAddress(glProgramUniformMatrix4fvEXT, "glProgramUniformMatrix4fvEXT");

			FetchProcAddress(glProgramUniformMatrix4x2fvEXT, "glProgramUniformMatrix4x2fvEXT");

			FetchProcAddress(glProgramUniformMatrix4x3fvEXT, "glProgramUniformMatrix4x3fvEXT");

			FetchProcAddress(glPushClientAttribDefaultEXT, "glPushClientAttribDefaultEXT");

			FetchProcAddress(glTextureBufferEXT, "glTextureBufferEXT");

			FetchProcAddress(glTextureImage1DEXT, "glTextureImage1DEXT");

			FetchProcAddress(glTextureImage2DEXT, "glTextureImage2DEXT");

			FetchProcAddress(glTextureImage3DEXT, "glTextureImage3DEXT");

			FetchProcAddress(glTextureParameterIivEXT, "glTextureParameterIivEXT");

			FetchProcAddress(glTextureParameterIuivEXT, "glTextureParameterIuivEXT");

			FetchProcAddress(glTextureParameterfEXT, "glTextureParameterfEXT");

			FetchProcAddress(glTextureParameterfvEXT, "glTextureParameterfvEXT");

			FetchProcAddress(glTextureParameteriEXT, "glTextureParameteriEXT");

			FetchProcAddress(glTextureParameterivEXT, "glTextureParameterivEXT");

			FetchProcAddress(glTextureRenderbufferEXT, "glTextureRenderbufferEXT");

			FetchProcAddress(glTextureSubImage1DEXT, "glTextureSubImage1DEXT");

			FetchProcAddress(glTextureSubImage2DEXT, "glTextureSubImage2DEXT");

			FetchProcAddress(glTextureSubImage3DEXT, "glTextureSubImage3DEXT");

			FetchProcAddress(glUnmapNamedBufferEXT, "glUnmapNamedBufferEXT");

			FetchProcAddress(glVertexArrayColorOffsetEXT, "glVertexArrayColorOffsetEXT");

			FetchProcAddress(glVertexArrayEdgeFlagOffsetEXT, "glVertexArrayEdgeFlagOffsetEXT");

			FetchProcAddress(glVertexArrayFogCoordOffsetEXT, "glVertexArrayFogCoordOffsetEXT");

			FetchProcAddress(glVertexArrayIndexOffsetEXT, "glVertexArrayIndexOffsetEXT");

			FetchProcAddress(glVertexArrayMultiTexCoordOffsetEXT, "glVertexArrayMultiTexCoordOffsetEXT");

			FetchProcAddress(glVertexArrayNormalOffsetEXT, "glVertexArrayNormalOffsetEXT");

			FetchProcAddress(glVertexArraySecondaryColorOffsetEXT, "glVertexArraySecondaryColorOffsetEXT");

			FetchProcAddress(glVertexArrayTexCoordOffsetEXT, "glVertexArrayTexCoordOffsetEXT");

			FetchProcAddress(glVertexArrayVertexAttribDivisorEXT, "glVertexArrayVertexAttribDivisorEXT");

			FetchProcAddress(glVertexArrayVertexAttribIOffsetEXT, "glVertexArrayVertexAttribIOffsetEXT");

			FetchProcAddress(glVertexArrayVertexAttribOffsetEXT, "glVertexArrayVertexAttribOffsetEXT");

			FetchProcAddress(glVertexArrayVertexOffsetEXT, "glVertexArrayVertexOffsetEXT");

			FetchProcAddress(EXT_direct_state_access, "EXT_direct_state_access");


			//discard framebuffer
			FetchProcAddress(glDiscardFramebufferEXT, "glDiscardFramebufferEXT");

			FetchProcAddress(EXT_discard_framebuffer, "EXT_discard_framebuffer");


			//draw buffers
			FetchProcAddress(glDrawBuffersEXT, "glDrawBuffersEXT");

			FetchProcAddress(EXT_draw_buffers, "EXT_draw_buffers");


			//draw buffers2
			FetchProcAddress(glColorMaskIndexedEXT, "glColorMaskIndexedEXT");

			FetchProcAddress(glDisableIndexedEXT, "glDisableIndexedEXT");

			FetchProcAddress(glEnableIndexedEXT, "glEnableIndexedEXT");

			FetchProcAddress(glGetBooleanIndexedvEXT, "glGetBooleanIndexedvEXT");

			FetchProcAddress(glGetIntegerIndexedvEXT, "glGetIntegerIndexedvEXT");

			FetchProcAddress(glIsEnabledIndexedEXT, "glIsEnabledIndexedEXT");

			FetchProcAddress(EXT_draw_buffers2, "EXT_draw_buffers2");


			//draw buffers indexed
			FetchProcAddress(glBlendEquationSeparateiEXT, "glBlendEquationSeparateiEXT");

			FetchProcAddress(glBlendEquationiEXT, "glBlendEquationiEXT");

			FetchProcAddress(glBlendFuncSeparateiEXT, "glBlendFuncSeparateiEXT");

			FetchProcAddress(glBlendFunciEXT, "glBlendFunciEXT");

			FetchProcAddress(glColorMaskiEXT, "glColorMaskiEXT");

			FetchProcAddress(glDisableiEXT, "glDisableiEXT");

			FetchProcAddress(glEnableiEXT, "glEnableiEXT");

			FetchProcAddress(glIsEnablediEXT, "glIsEnablediEXT");

			FetchProcAddress(EXT_draw_buffers_indexed, "EXT_draw_buffers_indexed");


			//draw elements base vertex
			FetchProcAddress(glDrawElementsBaseVertexEXT, "glDrawElementsBaseVertexEXT");

			FetchProcAddress(glDrawElementsInstancedBaseVertexEXT, "glDrawElementsInstancedBaseVertexEXT");

			FetchProcAddress(glDrawRangeElementsBaseVertexEXT, "glDrawRangeElementsBaseVertexEXT");

			FetchProcAddress(glMultiDrawElementsBaseVertexEXT, "glMultiDrawElementsBaseVertexEXT");

			FetchProcAddress(EXT_draw_elements_base_vertex, "EXT_draw_elements_base_vertex");


			//draw instanced
			FetchProcAddress(glDrawArraysInstancedEXT, "glDrawArraysInstancedEXT");

			FetchProcAddress(glDrawElementsInstancedEXT, "glDrawElementsInstancedEXT");

			FetchProcAddress(EXT_draw_instanced, "EXT_draw_instanced");


			//draw range elements
			FetchProcAddress(glDrawRangeElementsEXT, "glDrawRangeElementsEXT");

			FetchProcAddress(EXT_draw_range_elements, "EXT_draw_range_elements");



			//external buffer
			FetchProcAddress(glBufferStorageExternalEXT, "glBufferStorageExternalEXT");

			FetchProcAddress(glNamedBufferStorageExternalEXT, "glNamedBufferStorageExternalEXT");

			FetchProcAddress(EXT_external_buffer, "EXT_external_buffer");


			//float blend
			FetchProcAddress(EXT_float_blend, "EXT_float_blend");


			//fog coord
			FetchProcAddress(glFogCoordPointerEXT, "glFogCoordPointerEXT");

			FetchProcAddress(glFogCoorddEXT, "glFogCoorddEXT");

			FetchProcAddress(glFogCoorddvEXT, "glFogCoorddvEXT");

			FetchProcAddress(glFogCoordfEXT, "glFogCoordfEXT");

			FetchProcAddress(glFogCoordfvEXT, "glFogCoordfvEXT");

			FetchProcAddress(EXT_fog_coord, "EXT_fog_coord");



			//frag depth
			FetchProcAddress(EXT_frag_depth, "EXT_frag_depth");



			//fragment lighting
			FetchProcAddress(glFragmentColorMaterialEXT, "glFragmentColorMaterialEXT");

			FetchProcAddress(glFragmentLightModelfEXT, "glFragmentLightModelfEXT");

			FetchProcAddress(glFragmentLightModelfvEXT, "glFragmentLightModelfvEXT");

			FetchProcAddress(glFragmentLightModeliEXT, "glFragmentLightModeliEXT");

			FetchProcAddress(glFragmentLightModelivEXT, "glFragmentLightModelivEXT");

			FetchProcAddress(glFragmentLightfEXT, "glFragmentLightfEXT");

			FetchProcAddress(glFragmentLightfvEXT, "glFragmentLightfvEXT");

			FetchProcAddress(glFragmentLightiEXT, "glFragmentLightiEXT");

			FetchProcAddress(glFragmentLightivEXT, "glFragmentLightivEXT");

			FetchProcAddress(glFragmentMaterialfEXT, "glFragmentMaterialfEXT");

			FetchProcAddress(glFragmentMaterialfvEXT, "glFragmentMaterialfvEXT");

			FetchProcAddress(glFragmentMaterialiEXT, "glFragmentMaterialiEXT");

			FetchProcAddress(glFragmentMaterialivEXT, "glFragmentMaterialivEXT");

			FetchProcAddress(glGetFragmentLightfvEXT, "glGetFragmentLightfvEXT");

			FetchProcAddress(glGetFragmentLightivEXT, "glGetFragmentLightivEXT");

			FetchProcAddress(glGetFragmentMaterialfvEXT, "glGetFragmentMaterialfvEXT");

			FetchProcAddress(glGetFragmentMaterialivEXT, "glGetFragmentMaterialivEXT");

			FetchProcAddress(glLightEnviEXT, "glLightEnviEXT");

			FetchProcAddress(EXT_fragment_lighting, "EXT_fragment_lighting");


			//framebuffer blit
			FetchProcAddress(glBlitFramebufferEXT, "glBlitFramebufferEXT");

			FetchProcAddress(EXT_framebuffer_blit, "EXT_framebuffer_blit");


			//framebuffer multisample
			FetchProcAddress(glRenderbufferStorageMultisampleEXT, "glRenderbufferStorageMultisampleEXT");

			FetchProcAddress(EXT_framebuffer_multisample, "EXT_framebuffer_multisample");


			//framebuffer multisample blit scaled
			FetchProcAddress(EXT_framebuffer_multisample_blit_scaled, "EXT_framebuffer_multisample_blit_scaled");


			//framebuffer object
			FetchProcAddress(glBindFramebufferEXT, "glBindFramebufferEXT");

			FetchProcAddress(glBindRenderbufferEXT, "glBindRenderbufferEXT");

			FetchProcAddress(glCheckFramebufferStatusEXT, "glCheckFramebufferStatusEXT");

			FetchProcAddress(glDeleteFramebuffersEXT, "glDeleteFramebuffersEXT");

			FetchProcAddress(glDeleteRenderbuffersEXT, "glDeleteRenderbuffersEXT");

			FetchProcAddress(glFramebufferRenderbufferEXT, "glFramebufferRenderbufferEXT");

			FetchProcAddress(glFramebufferTexture1DEXT, "glFramebufferTexture1DEXT");

			FetchProcAddress(glFramebufferTexture2DEXT, "glFramebufferTexture2DEXT");

			FetchProcAddress(glFramebufferTexture3DEXT, "glFramebufferTexture3DEXT");

			FetchProcAddress(glGenFramebuffersEXT, "glGenFramebuffersEXT");

			FetchProcAddress(glGenRenderbuffersEXT, "glGenRenderbuffersEXT");

			FetchProcAddress(glGenerateMipmapEXT, "glGenerateMipmapEXT");

			FetchProcAddress(glGetFramebufferAttachmentParameterivEXT, "glGetFramebufferAttachmentParameterivEXT");

			FetchProcAddress(glGetRenderbufferParameterivEXT, "glGetRenderbufferParameterivEXT");

			FetchProcAddress(glIsFramebufferEXT, "glIsFramebufferEXT");

			FetchProcAddress(glIsRenderbufferEXT, "glIsRenderbufferEXT");

			FetchProcAddress(glRenderbufferStorageEXT, "glRenderbufferStorageEXT");

			FetchProcAddress(EXT_framebuffer_object, "EXT_framebuffer_object");


			//framebuffer sRGB
			FetchProcAddress(EXT_framebuffer_sRGB, "EXT_framebuffer_sRGB");


			//geometry point size
			FetchProcAddress(EXT_geometry_point_size, "EXT_geometry_point_size");


			//geometry shader
			FetchProcAddress(EXT_geometry_shader, "EXT_geometry_shader");


			//geometry shader4
			FetchProcAddress(glFramebufferTextureEXT, "glFramebufferTextureEXT");

			FetchProcAddress(glFramebufferTextureFaceEXT, "glFramebufferTextureFaceEXT");

			FetchProcAddress(glProgramParameteriEXT, "glProgramParameteriEXT");

			FetchProcAddress(EXT_geometry_shader4, "EXT_geometry_shader4");


			//gpu program parameters
			FetchProcAddress(glProgramEnvParameters4fvEXT, "glProgramEnvParameters4fvEXT");

			FetchProcAddress(glProgramLocalParameters4fvEXT, "glProgramLocalParameters4fvEXT");

			FetchProcAddress(EXT_gpu_program_parameters, "EXT_gpu_program_parameters");


			//gpu shader4
			FetchProcAddress(glBindFragDataLocationEXT, "glBindFragDataLocationEXT");

			FetchProcAddress(glGetFragDataLocationEXT, "glGetFragDataLocationEXT");

			FetchProcAddress(glGetUniformuivEXT, "glGetUniformuivEXT");

			FetchProcAddress(glGetVertexAttribIivEXT, "glGetVertexAttribIivEXT");

			FetchProcAddress(glGetVertexAttribIuivEXT, "glGetVertexAttribIuivEXT");

			FetchProcAddress(glUniform1uiEXT, "glUniform1uiEXT");

			FetchProcAddress(glUniform1uivEXT, "glUniform1uivEXT");

			FetchProcAddress(glUniform2uiEXT, "glUniform2uiEXT");

			FetchProcAddress(glUniform2uivEXT, "glUniform2uivEXT");

			FetchProcAddress(glUniform3uiEXT, "glUniform3uiEXT");

			FetchProcAddress(glUniform3uivEXT, "glUniform3uivEXT");

			FetchProcAddress(glUniform4uiEXT, "glUniform4uiEXT");

			FetchProcAddress(glUniform4uivEXT, "glUniform4uivEXT");

			FetchProcAddress(glVertexAttribI1iEXT, "glVertexAttribI1iEXT");

			FetchProcAddress(glVertexAttribI1ivEXT, "glVertexAttribI1ivEXT");

			FetchProcAddress(glVertexAttribI1uiEXT, "glVertexAttribI1uiEXT");

			FetchProcAddress(glVertexAttribI1uivEXT, "glVertexAttribI1uivEXT");

			FetchProcAddress(glVertexAttribI2iEXT, "glVertexAttribI2iEXT");

			FetchProcAddress(glVertexAttribI2ivEXT, "glVertexAttribI2ivEXT");

			FetchProcAddress(glVertexAttribI2uiEXT, "glVertexAttribI2uiEXT");

			FetchProcAddress(glVertexAttribI2uivEXT, "glVertexAttribI2uivEXT");

			FetchProcAddress(glVertexAttribI3iEXT, "glVertexAttribI3iEXT");

			FetchProcAddress(glVertexAttribI3ivEXT, "glVertexAttribI3ivEXT");

			FetchProcAddress(glVertexAttribI3uiEXT, "glVertexAttribI3uiEXT");

			FetchProcAddress(glVertexAttribI3uivEXT, "glVertexAttribI3uivEXT");

			FetchProcAddress(glVertexAttribI4bvEXT, "glVertexAttribI4bvEXT");

			FetchProcAddress(glVertexAttribI4iEXT, "glVertexAttribI4iEXT");

			FetchProcAddress(glVertexAttribI4ivEXT, "glVertexAttribI4ivEXT");

			FetchProcAddress(glVertexAttribI4svEXT, "glVertexAttribI4svEXT");

			FetchProcAddress(glVertexAttribI4ubvEXT, "glVertexAttribI4ubvEXT");

			FetchProcAddress(glVertexAttribI4uiEXT, "glVertexAttribI4uiEXT");

			FetchProcAddress(glVertexAttribI4uivEXT, "glVertexAttribI4uivEXT");

			FetchProcAddress(glVertexAttribI4usvEXT, "glVertexAttribI4usvEXT");

			FetchProcAddress(glVertexAttribIPointerEXT, "glVertexAttribIPointerEXT");

			FetchProcAddress(EXT_gpu_shader4, "EXT_gpu_shader4");


			//gpu shader5
			FetchProcAddress(EXT_gpu_shader5, "EXT_gpu_shader5");


			//histogram
			FetchProcAddress(glGetHistogramEXT, "glGetHistogramEXT");

			FetchProcAddress(glGetHistogramParameterfvEXT, "glGetHistogramParameterfvEXT");

			FetchProcAddress(glGetHistogramParameterivEXT, "glGetHistogramParameterivEXT");

			FetchProcAddress(glGetMinmaxEXT, "glGetMinmaxEXT");

			FetchProcAddress(glGetMinmaxParameterfvEXT, "glGetMinmaxParameterfvEXT");

			FetchProcAddress(glGetMinmaxParameterivEXT, "glGetMinmaxParameterivEXT");

			FetchProcAddress(glHistogramEXT, "glHistogramEXT");

			FetchProcAddress(glMinmaxEXT, "glMinmaxEXT");

			FetchProcAddress(glResetHistogramEXT, "glResetHistogramEXT");

			FetchProcAddress(glResetMinmaxEXT, "glResetMinmaxEXT");

			FetchProcAddress(EXT_histogram, "EXT_histogram");


			//index array formats
			FetchProcAddress(EXT_index_array_formats, "EXT_index_array_formats");


			//index func
			FetchProcAddress(glIndexFuncEXT, "glIndexFuncEXT");

			FetchProcAddress(EXT_index_func, "EXT_index_func");


			//index material
			FetchProcAddress(glIndexMaterialEXT, "glIndexMaterialEXT");

			FetchProcAddress(EXT_index_material, "EXT_index_material");


			//index texture
			FetchProcAddress(EXT_index_texture, "EXT_index_texture");


			//instanced arrays
			FetchProcAddress(glVertexAttribDivisorEXT, "glVertexAttribDivisorEXT");

			FetchProcAddress(EXT_instanced_arrays, "EXT_instanced_arrays");


			//light texture
			FetchProcAddress(glApplyTextureEXT, "glApplyTextureEXT");

			FetchProcAddress(glTextureLightEXT, "glTextureLightEXT");

			FetchProcAddress(glTextureMaterialEXT, "glTextureMaterialEXT");

			FetchProcAddress(EXT_light_texture, "EXT_light_texture");


			//map buffer range
			FetchProcAddress(glFlushMappedBufferRangeEXT, "glFlushMappedBufferRangeEXT");

			FetchProcAddress(glMapBufferRangeEXT, "glMapBufferRangeEXT");

			FetchProcAddress(EXT_map_buffer_range, "EXT_map_buffer_range");


			//memory object
			FetchProcAddress(glBufferStorageMemEXT, "glBufferStorageMemEXT");

			FetchProcAddress(glCreateMemoryObjectsEXT, "glCreateMemoryObjectsEXT");

			FetchProcAddress(glDeleteMemoryObjectsEXT, "glDeleteMemoryObjectsEXT");

			FetchProcAddress(glGetMemoryObjectParameterivEXT, "glGetMemoryObjectParameterivEXT");

			FetchProcAddress(glGetUnsignedBytei_vEXT, "glGetUnsignedBytei_vEXT");

			FetchProcAddress(glGetUnsignedBytevEXT, "glGetUnsignedBytevEXT");

			FetchProcAddress(glIsMemoryObjectEXT, "glIsMemoryObjectEXT");

			FetchProcAddress(glMemoryObjectParameterivEXT, "glMemoryObjectParameterivEXT");

			FetchProcAddress(glNamedBufferStorageMemEXT, "glNamedBufferStorageMemEXT");

			FetchProcAddress(glTexStorageMem1DEXT, "glTexStorageMem1DEXT");

			FetchProcAddress(glTexStorageMem2DEXT, "glTexStorageMem2DEXT");

			FetchProcAddress(glTexStorageMem2DMultisampleEXT, "glTexStorageMem2DMultisampleEXT");

			FetchProcAddress(glTexStorageMem3DEXT, "glTexStorageMem3DEXT");

			FetchProcAddress(glTexStorageMem3DMultisampleEXT, "glTexStorageMem3DMultisampleEXT");

			FetchProcAddress(glTextureStorageMem1DEXT, "glTextureStorageMem1DEXT");

			FetchProcAddress(glTextureStorageMem2DEXT, "glTextureStorageMem2DEXT");

			FetchProcAddress(glTextureStorageMem2DMultisampleEXT, "glTextureStorageMem2DMultisampleEXT");

			FetchProcAddress(glTextureStorageMem3DEXT, "glTextureStorageMem3DEXT");

			FetchProcAddress(glTextureStorageMem3DMultisampleEXT, "glTextureStorageMem3DMultisampleEXT");

			FetchProcAddress(EXT_memory_object, "EXT_memory_object");


			//memory object fd
			FetchProcAddress(glImportMemoryFdEXT, "glImportMemoryFdEXT");

			FetchProcAddress(EXT_memory_object_fd, "EXT_memory_object_fd");


			//memory object win32
			FetchProcAddress(glImportMemoryWin32HandleEXT, "glImportMemoryWin32HandleEXT");

			FetchProcAddress(glImportMemoryWin32NameEXT, "glImportMemoryWin32NameEXT");

			FetchProcAddress(EXT_memory_object_win32, "EXT_memory_object_win32");


			//misc attribute
			FetchProcAddress(EXT_misc_attribute, "EXT_misc_attribute");


			//multi draw arrays
			FetchProcAddress(glMultiDrawArraysEXT, "glMultiDrawArraysEXT");

			FetchProcAddress(glMultiDrawElementsEXT, "glMultiDrawElementsEXT");

			FetchProcAddress(EXT_multi_draw_arrays, "EXT_multi_draw_arrays");


			//multi draw indirect
			FetchProcAddress(glMultiDrawArraysIndirectEXT, "glMultiDrawArraysIndirectEXT");

			FetchProcAddress(glMultiDrawElementsIndirectEXT, "glMultiDrawElementsIndirectEXT");

			FetchProcAddress(EXT_multi_draw_indirect, "EXT_multi_draw_indirect");


			//multiple textures
			FetchProcAddress(EXT_multiple_textures, "EXT_multiple_textures");


			//multisample
			FetchProcAddress(glSampleMaskEXT, "glSampleMaskEXT");

			FetchProcAddress(glSamplePatternEXT, "glSamplePatternEXT");

			FetchProcAddress(EXT_multisample, "EXT_multisample");


			//multisample compatibility
			FetchProcAddress(EXT_multisample_compatibility, "EXT_multisample_compatibility");


			//multisampled render to texture
			FetchProcAddress(glFramebufferTexture2DMultisampleEXT, "glFramebufferTexture2DMultisampleEXT");

			FetchProcAddress(EXT_multisampled_render_to_texture, "EXT_multisampled_render_to_texture");


			//multisampled render to texture2
			FetchProcAddress(EXT_multisampled_render_to_texture2, "EXT_multisampled_render_to_texture2");


			//multiview draw buffers
			FetchProcAddress(glDrawBuffersIndexedEXT, "glDrawBuffersIndexedEXT");

			FetchProcAddress(glGetIntegeri_vEXT, "glGetIntegeri_vEXT");

			FetchProcAddress(glReadBufferIndexedEXT, "glReadBufferIndexedEXT");

			FetchProcAddress(EXT_multiview_draw_buffers, "EXT_multiview_draw_buffers");


			//packed depth stencil
			FetchProcAddress(EXT_packed_depth_stencil, "EXT_packed_depth_stencil");


			//packed float
			FetchProcAddress(EXT_packed_float, "EXT_packed_float");


			//packed pixels
			FetchProcAddress(EXT_packed_pixels, "EXT_packed_pixels");


			//paletted texture
			FetchProcAddress(glColorTableEXT, "glColorTableEXT");

			FetchProcAddress(glGetColorTableEXT, "glGetColorTableEXT");

			FetchProcAddress(glGetColorTableParameterfvEXT, "glGetColorTableParameterfvEXT");

			FetchProcAddress(glGetColorTableParameterivEXT, "glGetColorTableParameterivEXT");

			FetchProcAddress(EXT_paletted_texture, "EXT_paletted_texture");


			//pixel buffer object
			FetchProcAddress(EXT_pixel_buffer_object, "EXT_pixel_buffer_object");


			//pixel transform
			FetchProcAddress(glGetPixelTransformParameterfvEXT, "glGetPixelTransformParameterfvEXT");

			FetchProcAddress(glGetPixelTransformParameterivEXT, "glGetPixelTransformParameterivEXT");

			FetchProcAddress(glPixelTransformParameterfEXT, "glPixelTransformParameterfEXT");

			FetchProcAddress(glPixelTransformParameterfvEXT, "glPixelTransformParameterfvEXT");

			FetchProcAddress(glPixelTransformParameteriEXT, "glPixelTransformParameteriEXT");

			FetchProcAddress(glPixelTransformParameterivEXT, "glPixelTransformParameterivEXT");

			FetchProcAddress(EXT_pixel_transform, "EXT_pixel_transform");


			//pixel transform color table
			FetchProcAddress(EXT_pixel_transform_color_table, "EXT_pixel_transform_color_table");


			//point parameters
			FetchProcAddress(glPointParameterfEXT, "glPointParameterfEXT");

			FetchProcAddress(glPointParameterfvEXT, "glPointParameterfvEXT");

			FetchProcAddress(EXT_point_parameters, "EXT_point_parameters");


			//polygon offset
			FetchProcAddress(glPolygonOffsetEXT, "glPolygonOffsetEXT");

			FetchProcAddress(EXT_polygon_offset, "EXT_polygon_offset");


			//polygon offset clamp
			FetchProcAddress(glPolygonOffsetClampEXT, "glPolygonOffsetClampEXT");

			FetchProcAddress(EXT_polygon_offset_clamp, "EXT_polygon_offset_clamp");


			//post depth coverage
			FetchProcAddress(EXT_post_depth_coverage, "EXT_post_depth_coverage");


			//provoking vertex
			FetchProcAddress(glProvokingVertexEXT, "glProvokingVertexEXT");

			FetchProcAddress(EXT_provoking_vertex, "EXT_provoking_vertex");


			//pvrtc sRGB
			FetchProcAddress(EXT_pvrtc_sRGB, "EXT_pvrtc_sRGB");


			//raster multisample
			FetchProcAddress(glCoverageModulationNV, "glCoverageModulationNV");

			FetchProcAddress(glCoverageModulationTableNV, "glCoverageModulationTableNV");

			FetchProcAddress(glGetCoverageModulationTableNV, "glGetCoverageModulationTableNV");

			FetchProcAddress(glRasterSamplesEXT, "glRasterSamplesEXT");

			FetchProcAddress(EXT_raster_multisample, "EXT_raster_multisample");


			//read format bgra
			FetchProcAddress(EXT_read_format_bgra, "EXT_read_format_bgra");


			//render snorm
			FetchProcAddress(EXT_render_snorm, "EXT_render_snorm");


			//rescale normal
			FetchProcAddress(EXT_rescale_normal, "EXT_rescale_normal");


			//sRGB
			FetchProcAddress(EXT_sRGB, "EXT_sRGB");


			//sRGB write control
			FetchProcAddress(EXT_sRGB_write_control, "EXT_sRGB_write_control");


			//scene marker
			FetchProcAddress(glBeginSceneEXT, "glBeginSceneEXT");

			FetchProcAddress(glEndSceneEXT, "glEndSceneEXT");

			FetchProcAddress(EXT_scene_marker, "EXT_scene_marker");


			//secondary color
			FetchProcAddress(glSecondaryColor3bEXT, "glSecondaryColor3bEXT");

			FetchProcAddress(glSecondaryColor3bvEXT, "glSecondaryColor3bvEXT");

			FetchProcAddress(glSecondaryColor3dEXT, "glSecondaryColor3dEXT");

			FetchProcAddress(glSecondaryColor3dvEXT, "glSecondaryColor3dvEXT");

			FetchProcAddress(glSecondaryColor3fEXT, "glSecondaryColor3fEXT");

			FetchProcAddress(glSecondaryColor3fvEXT, "glSecondaryColor3fvEXT");

			FetchProcAddress(glSecondaryColor3iEXT, "glSecondaryColor3iEXT");

			FetchProcAddress(glSecondaryColor3ivEXT, "glSecondaryColor3ivEXT");

			FetchProcAddress(glSecondaryColor3sEXT, "glSecondaryColor3sEXT");

			FetchProcAddress(glSecondaryColor3svEXT, "glSecondaryColor3svEXT");

			FetchProcAddress(glSecondaryColor3ubEXT, "glSecondaryColor3ubEXT");

			FetchProcAddress(glSecondaryColor3ubvEXT, "glSecondaryColor3ubvEXT");

			FetchProcAddress(glSecondaryColor3uiEXT, "glSecondaryColor3uiEXT");

			FetchProcAddress(glSecondaryColor3uivEXT, "glSecondaryColor3uivEXT");

			FetchProcAddress(glSecondaryColor3usEXT, "glSecondaryColor3usEXT");

			FetchProcAddress(glSecondaryColor3usvEXT, "glSecondaryColor3usvEXT");

			FetchProcAddress(glSecondaryColorPointerEXT, "glSecondaryColorPointerEXT");

			FetchProcAddress(EXT_secondary_color, "EXT_secondary_color");


			//semaphore
			FetchProcAddress(glDeleteSemaphoresEXT, "glDeleteSemaphoresEXT");

			FetchProcAddress(glGenSemaphoresEXT, "glGenSemaphoresEXT");

			FetchProcAddress(glGetSemaphoreParameterui64vEXT, "glGetSemaphoreParameterui64vEXT");

			FetchProcAddress(glIsSemaphoreEXT, "glIsSemaphoreEXT");

			FetchProcAddress(glSemaphoreParameterui64vEXT, "glSemaphoreParameterui64vEXT");

			FetchProcAddress(glSignalSemaphoreEXT, "glSignalSemaphoreEXT");

			FetchProcAddress(glWaitSemaphoreEXT, "glWaitSemaphoreEXT");

			FetchProcAddress(EXT_semaphore, "EXT_semaphore");


			//semaphore fd
			FetchProcAddress(glImportSemaphoreFdEXT, "glImportSemaphoreFdEXT");

			FetchProcAddress(EXT_semaphore_fd, "EXT_semaphore_fd");


			//semaphore win32
			FetchProcAddress(glImportSemaphoreWin32HandleEXT, "glImportSemaphoreWin32HandleEXT");

			FetchProcAddress(glImportSemaphoreWin32NameEXT, "glImportSemaphoreWin32NameEXT");

			FetchProcAddress(EXT_semaphore_win32, "EXT_semaphore_win32");


			//separate shader objects
			FetchProcAddress(glActiveProgramEXT, "glActiveProgramEXT");

			FetchProcAddress(glCreateShaderProgramEXT, "glCreateShaderProgramEXT");

			FetchProcAddress(glUseShaderProgramEXT, "glUseShaderProgramEXT");

			FetchProcAddress(EXT_separate_shader_objects, "EXT_separate_shader_objects");


			//separate specular color
			FetchProcAddress(EXT_separate_specular_color, "EXT_separate_specular_color");


			//shader framebuffer fetch
			FetchProcAddress(EXT_shader_framebuffer_fetch, "EXT_shader_framebuffer_fetch");


			//shader group vote
			FetchProcAddress(EXT_shader_group_vote, "EXT_shader_group_vote");


			//shader image load formatted
			FetchProcAddress(EXT_shader_image_load_formatted, "EXT_shader_image_load_formatted");


			//shader image load store
			FetchProcAddress(glBindImageTextureEXT, "glBindImageTextureEXT");

			FetchProcAddress(glMemoryBarrierEXT, "glMemoryBarrierEXT");

			FetchProcAddress(EXT_shader_image_load_store, "EXT_shader_image_load_store");


			//shader implicit conversions
			FetchProcAddress(EXT_shader_implicit_conversions, "EXT_shader_implicit_conversions");


			//shader integer mix
			FetchProcAddress(EXT_shader_integer_mix, "EXT_shader_integer_mix");


			//shader io blocks
			FetchProcAddress(EXT_shader_io_blocks, "EXT_shader_io_blocks");


			//shader non constant global initializers
			FetchProcAddress(EXT_shader_non_constant_global_initializers, "EXT_shader_non_constant_global_initializers");


			//shader pixel local storage
			FetchProcAddress(EXT_shader_pixel_local_storage, "EXT_shader_pixel_local_storage");


			//shader pixel local storage2
			FetchProcAddress(glClearPixelLocalStorageuiEXT, "glClearPixelLocalStorageuiEXT");

			FetchProcAddress(glFramebufferPixelLocalStorageSizeEXT, "glFramebufferPixelLocalStorageSizeEXT");

			FetchProcAddress(glGetFramebufferPixelLocalStorageSizeEXT, "glGetFramebufferPixelLocalStorageSizeEXT");

			FetchProcAddress(EXT_shader_pixel_local_storage2, "EXT_shader_pixel_local_storage2");


			//shader texture lod
			FetchProcAddress(EXT_shader_texture_lod, "EXT_shader_texture_lod");


			//shadow funcs
			FetchProcAddress(EXT_shadow_funcs, "EXT_shadow_funcs");


			//shadow samplers
			FetchProcAddress(EXT_shadow_samplers, "EXT_shadow_samplers");


			//shared texture palette
			FetchProcAddress(EXT_shared_texture_palette, "EXT_shared_texture_palette");


			//sparse texture
			FetchProcAddress(glTexPageCommitmentEXT, "glTexPageCommitmentEXT");

			FetchProcAddress(glTexturePageCommitmentEXT, "glTexturePageCommitmentEXT");

			FetchProcAddress(EXT_sparse_texture, "EXT_sparse_texture");


			//sparse texture2
			FetchProcAddress(EXT_sparse_texture2, "EXT_sparse_texture2");


			//stencil clear tag
			FetchProcAddress(EXT_stencil_clear_tag, "EXT_stencil_clear_tag");


			//stencil two side
			FetchProcAddress(glActiveStencilFaceEXT, "glActiveStencilFaceEXT");

			FetchProcAddress(EXT_stencil_two_side, "EXT_stencil_two_side");


			//stencil wrap
			FetchProcAddress(EXT_stencil_wrap, "EXT_stencil_wrap");


			//subtexture
			FetchProcAddress(glTexSubImage1DEXT, "glTexSubImage1DEXT");

			FetchProcAddress(glTexSubImage2DEXT, "glTexSubImage2DEXT");

			FetchProcAddress(glTexSubImage3DEXT, "glTexSubImage3DEXT");

			FetchProcAddress(EXT_subtexture, "EXT_subtexture");


			//texture
			FetchProcAddress(EXT_texture, "EXT_texture");


			//texture3D
			FetchProcAddress(glTexImage3DEXT, "glTexImage3DEXT");

			FetchProcAddress(EXT_texture3D, "EXT_texture3D");


			//texture array
			FetchProcAddress(glFramebufferTextureLayerEXT, "glFramebufferTextureLayerEXT");

			FetchProcAddress(EXT_texture_array, "EXT_texture_array");


			//texture buffer object
			FetchProcAddress(glTexBufferEXT, "glTexBufferEXT");

			FetchProcAddress(EXT_texture_buffer_object, "EXT_texture_buffer_object");


			//texture compression astc decode mode
			FetchProcAddress(EXT_texture_compression_astc_decode_mode, "EXT_texture_compression_astc_decode_mode");


			//texture compression astc decode mode rgb9e5
			FetchProcAddress(EXT_texture_compression_astc_decode_mode_rgb9e5, "EXT_texture_compression_astc_decode_mode_rgb9e5");


			//texture compression bptc
			FetchProcAddress(EXT_texture_compression_bptc, "EXT_texture_compression_bptc");


			//texture compression dxt1
			FetchProcAddress(EXT_texture_compression_dxt1, "EXT_texture_compression_dxt1");


			//texture compression latc
			FetchProcAddress(EXT_texture_compression_latc, "EXT_texture_compression_latc");


			//texture compression rgtc
			FetchProcAddress(EXT_texture_compression_rgtc, "EXT_texture_compression_rgtc");


			//texture compression s3tc
			FetchProcAddress(EXT_texture_compression_s3tc, "EXT_texture_compression_s3tc");


			//texture cube map
			FetchProcAddress(EXT_texture_cube_map, "EXT_texture_cube_map");


			//texture cube map array
			FetchProcAddress(EXT_texture_cube_map_array, "EXT_texture_cube_map_array");


			//texture_edge_clamp
			FetchProcAddress(EXT_texture_edge_clamp, "EXT_texture_edge_clamp");


			//texture_env
			FetchProcAddress(EXT_texture_env, "EXT_texture_env");


			//texture_env_add
			FetchProcAddress(EXT_texture_env_add, "EXT_texture_env_add");


			//texture_env_combine
			FetchProcAddress(EXT_texture_env_combine, "EXT_texture_env_combine");


			//texture_env_dot3
			FetchProcAddress(EXT_texture_env_dot3, "EXT_texture_env_dot3");


			//texture_filter_anisotropic
			FetchProcAddress(EXT_texture_filter_anisotropic, "EXT_texture_filter_anisotropic");


			//texture_filter_minmax
			FetchProcAddress(EXT_texture_filter_minmax, "EXT_texture_filter_minmax");


			//texture_format_BGRA8888
			FetchProcAddress(EXT_texture_format_BGRA8888, "EXT_texture_format_BGRA8888");


			//texture_integer
			FetchProcAddress(glClearColorIiEXT, "glClearColorIiEXT");

			FetchProcAddress(glClearColorIuiEXT, "glClearColorIuiEXT");

			FetchProcAddress(glGetTexParameterIivEXT, "glGetTexParameterIivEXT");

			FetchProcAddress(glGetTexParameterIuivEXT, "glGetTexParameterIuivEXT");

			FetchProcAddress(glTexParameterIivEXT, "glTexParameterIivEXT");

			FetchProcAddress(glTexParameterIuivEXT, "glTexParameterIuivEXT");

			FetchProcAddress(EXT_texture_integer, "EXT_texture_integer");


			//texture_lod_bias
			FetchProcAddress(EXT_texture_lod_bias, "EXT_texture_lod_bias");


			//texture_mirror_clamp
			FetchProcAddress(EXT_texture_mirror_clamp, "EXT_texture_mirror_clamp");


			//texture_norm16
			FetchProcAddress(EXT_texture_norm16, "EXT_texture_norm16");


			//texture_object
			FetchProcAddress(glAreTexturesResidentEXT, "glAreTexturesResidentEXT");

			FetchProcAddress(glBindTextureEXT, "glBindTextureEXT");

			FetchProcAddress(glDeleteTexturesEXT, "glDeleteTexturesEXT");

			FetchProcAddress(glGenTexturesEXT, "glGenTexturesEXT");

			FetchProcAddress(glIsTextureEXT, "glIsTextureEXT");

			FetchProcAddress(glPrioritizeTexturesEXT, "glPrioritizeTexturesEXT");

			FetchProcAddress(EXT_texture_object, "EXT_texture_object");


			//texture_perturb_normal
			FetchProcAddress(glTextureNormalEXT, "glTextureNormalEXT");

			FetchProcAddress(EXT_texture_perturb_normal, "EXT_texture_perturb_normal");


			//texture_rectangle
			FetchProcAddress(EXT_texture_rectangle, "EXT_texture_rectangle");


			//texture_rg
			FetchProcAddress(EXT_texture_rg, "EXT_texture_rg");


			//texture_sRGB
			FetchProcAddress(EXT_texture_sRGB, "EXT_texture_sRGB");


			//texture_sRGB_R8
			FetchProcAddress(EXT_texture_sRGB_R8, "EXT_texture_sRGB_R8");


			//texture_sRGB_RG8
			FetchProcAddress(EXT_texture_sRGB_RG8, "EXT_texture_sRGB_RG8");


			//texture_sRGB_decode
			FetchProcAddress(EXT_texture_sRGB_decode, "EXT_texture_sRGB_decode");


			//texture_shared_exponent
			FetchProcAddress(EXT_texture_shared_exponent, "EXT_texture_shared_exponent");


			//texture_snorm
			FetchProcAddress(EXT_texture_snorm, "EXT_texture_snorm");


			//texture_storage
			FetchProcAddress(glTexStorage1DEXT, "glTexStorage1DEXT");

			FetchProcAddress(glTexStorage2DEXT, "glTexStorage2DEXT");

			FetchProcAddress(glTexStorage3DEXT, "glTexStorage3DEXT");

			FetchProcAddress(glTextureStorage1DEXT, "glTextureStorage1DEXT");

			FetchProcAddress(glTextureStorage2DEXT, "glTextureStorage2DEXT");

			FetchProcAddress(glTextureStorage3DEXT, "glTextureStorage3DEXT");

			FetchProcAddress(EXT_texture_storage, "EXT_texture_storage");


			//texture_swizzle
			FetchProcAddress(EXT_texture_swizzle, "EXT_texture_swizzle");


			//texture_type_2_10_10_10_REV
			FetchProcAddress(EXT_texture_type_2_10_10_10_REV, "EXT_texture_type_2_10_10_10_REV");


			//texture_view
			FetchProcAddress(glTextureViewEXT, "glTextureViewEXT");

			FetchProcAddress(EXT_texture_view, "EXT_texture_view");


			//timer_query
			FetchProcAddress(glGetQueryObjecti64vEXT, "glGetQueryObjecti64vEXT");

			FetchProcAddress(glGetQueryObjectui64vEXT, "glGetQueryObjectui64vEXT");

			FetchProcAddress(EXT_timer_query, "EXT_timer_query");


			//transform_feedback
			FetchProcAddress(glBeginTransformFeedbackEXT, "glBeginTransformFeedbackEXT");

			FetchProcAddress(glBindBufferBaseEXT, "glBindBufferBaseEXT");

			FetchProcAddress(glBindBufferOffsetEXT, "glBindBufferOffsetEXT");

			FetchProcAddress(glBindBufferRangeEXT, "glBindBufferRangeEXT");

			FetchProcAddress(glEndTransformFeedbackEXT, "glEndTransformFeedbackEXT");

			FetchProcAddress(glGetTransformFeedbackVaryingEXT, "glGetTransformFeedbackVaryingEXT");

			FetchProcAddress(glTransformFeedbackVaryingsEXT, "glTransformFeedbackVaryingsEXT");

			FetchProcAddress(EXT_transform_feedback, "EXT_transform_feedback");


			//unpack_subimage
			FetchProcAddress(EXT_unpack_subimage, "EXT_unpack_subimage");


			//vertex_array
			FetchProcAddress(glArrayElementEXT, "glArrayElementEXT");

			FetchProcAddress(glColorPointerEXT, "glColorPointerEXT");

			FetchProcAddress(glDrawArraysEXT, "glDrawArraysEXT");

			FetchProcAddress(glEdgeFlagPointerEXT, "glEdgeFlagPointerEXT");

			FetchProcAddress(glIndexPointerEXT, "glIndexPointerEXT");

			FetchProcAddress(glNormalPointerEXT, "glNormalPointerEXT");

			FetchProcAddress(glTexCoordPointerEXT, "glTexCoordPointerEXT");

			FetchProcAddress(glVertexPointerEXT, "glVertexPointerEXT");

			FetchProcAddress(EXT_vertex_array, "EXT_vertex_array");


			//vertex_array_bgra
			FetchProcAddress(EXT_vertex_array_bgra, "EXT_vertex_array_bgra");


			//vertex_array_setXXX
			FetchProcAddress(glBindArraySetEXT, "glBindArraySetEXT");

			FetchProcAddress(glCreateArraySetExt, "glCreateArraySetExt");

			FetchProcAddress(glDeleteArraySetsEXT, "glDeleteArraySetsEXT");

			FetchProcAddress(EXT_vertex_array_setXXX, "EXT_vertex_array_setXXX");


			//vertex_attrib_64bit
			FetchProcAddress(glGetVertexAttribLdvEXT, "glGetVertexAttribLdvEXT");

			FetchProcAddress(glVertexArrayVertexAttribLOffsetEXT, "glVertexArrayVertexAttribLOffsetEXT");

			FetchProcAddress(glVertexAttribL1dEXT, "glVertexAttribL1dEXT");

			FetchProcAddress(glVertexAttribL1dvEXT, "glVertexAttribL1dvEXT");

			FetchProcAddress(glVertexAttribL2dEXT, "glVertexAttribL2dEXT");

			FetchProcAddress(glVertexAttribL2dvEXT, "glVertexAttribL2dvEXT");

			FetchProcAddress(glVertexAttribL3dEXT, "glVertexAttribL3dEXT");

			FetchProcAddress(glVertexAttribL3dvEXT, "glVertexAttribL3dvEXT");

			FetchProcAddress(glVertexAttribL4dEXT, "glVertexAttribL4dEXT");

			FetchProcAddress(glVertexAttribL4dvEXT, "glVertexAttribL4dvEXT");

			FetchProcAddress(glVertexAttribLPointerEXT, "glVertexAttribLPointerEXT");

			FetchProcAddress(EXT_vertex_attrib_64bit, "EXT_vertex_attrib_64bit");


			//vertex_shader
			FetchProcAddress(glBeginVertexShaderEXT, "glBeginVertexShaderEXT");

			FetchProcAddress(glBindLightParameterEXT, "glBindLightParameterEXT");

			FetchProcAddress(glBindMaterialParameterEXT, "glBindMaterialParameterEXT");

			FetchProcAddress(glBindParameterEXT, "glBindParameterEXT");

			FetchProcAddress(glBindTexGenParameterEXT, "glBindTexGenParameterEXT");

			FetchProcAddress(glBindTextureUnitParameterEXT, "glBindTextureUnitParameterEXT");

			FetchProcAddress(glBindVertexShaderEXT, "glBindVertexShaderEXT");

			FetchProcAddress(glDeleteVertexShaderEXT, "glDeleteVertexShaderEXT");

			FetchProcAddress(glDisableVariantClientStateEXT, "glDisableVariantClientStateEXT");

			FetchProcAddress(glEnableVariantClientStateEXT, "glEnableVariantClientStateEXT");

			FetchProcAddress(glEndVertexShaderEXT, "glEndVertexShaderEXT");

			FetchProcAddress(glExtractComponentEXT, "glExtractComponentEXT");

			FetchProcAddress(glGenSymbolsEXT, "glGenSymbolsEXT");

			FetchProcAddress(glGenVertexShadersEXT, "glGenVertexShadersEXT");

			FetchProcAddress(glGetInvariantBooleanvEXT, "glGetInvariantBooleanvEXT");

			FetchProcAddress(glGetInvariantFloatvEXT, "glGetInvariantFloatvEXT");

			FetchProcAddress(glGetInvariantIntegervEXT, "glGetInvariantIntegervEXT");

			FetchProcAddress(glGetLocalConstantBooleanvEXT, "glGetLocalConstantBooleanvEXT");

			FetchProcAddress(glGetLocalConstantFloatvEXT, "glGetLocalConstantFloatvEXT");

			FetchProcAddress(glGetLocalConstantIntegervEXT, "glGetLocalConstantIntegervEXT");

			FetchProcAddress(glGetVariantBooleanvEXT, "glGetVariantBooleanvEXT");

			FetchProcAddress(glGetVariantFloatvEXT, "glGetVariantFloatvEXT");

			FetchProcAddress(glGetVariantIntegervEXT, "glGetVariantIntegervEXT");

			FetchProcAddress(glGetVariantPointervEXT, "glGetVariantPointervEXT");

			FetchProcAddress(glInsertComponentEXT, "glInsertComponentEXT");

			FetchProcAddress(glIsVariantEnabledEXT, "glIsVariantEnabledEXT");

			FetchProcAddress(glSetInvariantEXT, "glSetInvariantEXT");

			FetchProcAddress(glSetLocalConstantEXT, "glSetLocalConstantEXT");

			FetchProcAddress(glShaderOp1EXT, "glShaderOp1EXT");

			FetchProcAddress(glShaderOp2EXT, "glShaderOp2EXT");

			FetchProcAddress(glShaderOp3EXT, "glShaderOp3EXT");

			FetchProcAddress(glSwizzleEXT, "glSwizzleEXT");

			FetchProcAddress(glVariantPointerEXT, "glVariantPointerEXT");

			FetchProcAddress(glVariantbvEXT, "glVariantbvEXT");

			FetchProcAddress(glVariantdvEXT, "glVariantdvEXT");

			FetchProcAddress(glVariantfvEXT, "glVariantfvEXT");

			FetchProcAddress(glVariantivEXT, "glVariantivEXT");

			FetchProcAddress(glVariantsvEXT, "glVariantsvEXT");

			FetchProcAddress(glVariantubvEXT, "glVariantubvEXT");

			FetchProcAddress(glVariantuivEXT, "glVariantuivEXT");

			FetchProcAddress(glVariantusvEXT, "glVariantusvEXT");

			FetchProcAddress(glWriteMaskEXT, "glWriteMaskEXT");

			FetchProcAddress(EXT_vertex_shader, "EXT_vertex_shader");


			//vertex_weighting
			FetchProcAddress(glVertexWeightPointerEXT, "glVertexWeightPointerEXT");
			FetchProcAddress(glVertexWeightfEXT, "glVertexWeightfEXT");
			FetchProcAddress(glVertexWeightfvEXT, "glVertexWeightfvEXT");
			FetchProcAddress(EXT_vertex_weighting, "EXT_vertex_weighting");

			//win32_keyed_mutex
			FetchProcAddress(glAcquireKeyedMutexWin32EXT, "glAcquireKeyedMutexWin32EXT");
			FetchProcAddress(glReleaseKeyedMutexWin32EXT, "glReleaseKeyedMutexWin32EXT");
			FetchProcAddress(EXT_win32_keyed_mutex, "EXT_win32_keyed_mutex");

			//window_rectangles
			FetchProcAddress(glWindowRectanglesEXT, "glWindowRectanglesEXT");
			FetchProcAddress(EXT_window_rectangles, "EXT_window_rectangles");

			//x11_sync_object
			FetchProcAddress(glImportSyncEXT, "glImportSyncEXT");
			FetchProcAddress(EXT_x11_sync_object, "EXT_x11_sync_object");

		}

#pragma endregion EXT Extensions

	//OpenGL Gremedy Extensions
#pragma region Gremedy

	//frame terminator 
	void (*glFrameTerminatorGREMEDY) (void) = nullptr;
	bool GREMEDY_frame_terminator = false;

	//string marker 
	void (*glStringMarkerGREMEDY) (GLsizei len, const void* string) = nullptr;
	bool GREMEDY_string_marker = false;

	//*< load Gremedy Extensions
	void LoadGremedyExtensions()
	{
		//frame terminator 
		FetchProcAddress(glFrameTerminatorGREMEDY, "glFrameTerminatorGREMEDY");
		FetchProcAddress(GREMEDY_frame_terminator, "GREMEDY_frame_terminator");

		//string marker 
		FetchProcAddress(glStringMarkerGREMEDY, "glStringMarkerGREMEDY");
		FetchProcAddress(GREMEDY_string_marker, "GREMEDY_string_marker");
	}

#pragma endregion Gremedy Extensions

	//OpenGL HP Extensions
#pragma region HP

	//convolution border modes
	bool convolution_border_modes = false;

	//image transform 
	void (*glGetImageTransformParameterfvHP) (GLenum target, GLenum pname, const GLfloat * params) = nullptr;
	void (*glGetImageTransformParameterivHP) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	void (*glImageTransformParameterfHP) (GLenum target, GLenum pname, const GLfloat param) = nullptr;
	void (*glImageTransformParameterfvHP) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	void (*glImageTransformParameteriHP) (GLenum target, GLenum pname, const GLint param) = nullptr;
	void (*glImageTransformParameterivHP) (GLenum target, GLenum pname, const GLint* params) = nullptr;

	bool image_transform = false;

	//occlusion test
	bool occlusion_test = false;

	//texture lighting 
	bool texture_lighting = false;

	//*< load HP Extensions
	void LoadHPExtensions()
	{
		//convolution border modes
		FetchProcAddress(convolution_border_modes, "convolution_border_modes");

		//image transform 
		FetchProcAddress(glGetImageTransformParameterfvHP, "glGetImageTransformParameterfvHP");
		FetchProcAddress(glGetImageTransformParameterivHP, "glGetImageTransformParameterivHP");
		FetchProcAddress(glImageTransformParameterfHP, "glImageTransformParameterfHP");
		FetchProcAddress(glImageTransformParameterfvHP, "glImageTransformParameterfvHP");
		FetchProcAddress(glImageTransformParameteriHP, "glImageTransformParameteriHP");
		FetchProcAddress(glImageTransformParameterivHP, "glImageTransformParameterivHP");
		FetchProcAddress(image_transform, "image_transform");

		//occlusion test
		FetchProcAddress(occlusion_test, "occlusion_test");

		//texture lighting 
		FetchProcAddress(texture_lighting, "texture_lighting");
	}

#pragma endregion HP Extensions

	//OpenGL IBM Extensions
#pragma region IBM

	enum OpenGL_IBM_t
	{
		//cull vertex
		gl_cull_vertex_ibm = 0x103050,

		//rasterpos clip
		gl_raster_position_unclipped_ibm = 0x103010,

		//static data
		gl_all_static_data_ibm = 0x103060,
		gl_static_vertex_array_ibm = 0x103061,

		//texture mirrored repeat
		gl_mirrored_repeat_ibm = 0x8370,

		//vertex array lists
		gl_vertex_array_list_ibm = 0x103070,
		gl_normal_array_list_ibm = 0x103071,
		gl_color_array_list_ibm = 0x103072,
		gl_index_array_list_ibm = 0x103073,
		gl_texture_coord_array_list_ibm = 0x103074,
		gl_edge_flag_array_list_ibm = 0x103075,
		gl_fog_coordinate_array_list_ibm = 0x103076,
		gl_secondary_color_array_list_ibm = 0x103077,
		gl_vertex_array_list_stride_ibm = 0x103080,
		gl_normal_array_list_stride_ibm = 0x103081,
		gl_color_array_list_stride_ibm = 0x103082,
		gl_index_array_list_stride_ibm = 0x103083,
		gl_texture_coord_array_list_stride_ibm = 0x103084,
		gl_edge_flag_array_list_stride_ibm = 0x103085,
		gl_fog_coordinate_array_list_stride_ibm = 0x103086,
		gl_secondary_color_array_list_stride_ibm = 0x103087,
	};

	//cull vertex 
	bool IBM_cull_vertex = false;

	//multimode draw arrays
	void (*glMultiModeDrawArraysIBM) (const GLenum * mode, const GLint * first, const GLsizei * count, GLsizei primcount, GLint modestride) = nullptr;
	void (*glMultiModeDrawElementsIBM) (const GLenum* mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei primcount, GLint modestride) = nullptr;

	bool IBM_multimode_draw_arrays = false;

	//rasterpos clip
	bool IBM_rasterpos_clip = false;

	//static data
	bool IBM_static_data = false;

	//texture mirrored_ repeat 
	bool IBM_texture_mirrored_repeat = false;

	//vertex array lists 
	void (*glColorPointerListIBM) (GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	void (*glEdgeFlagPointerListIBM) (GLint stride, const GLboolean** pointer, GLint ptrstride) = nullptr;
	void (*glFogCoordPointerListIBM) (GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	void (*glIndexPointerListIBM) (GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	void (*glNormalPointerListIBM) (GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	void (*glSecondaryColorPointerListIBM) (GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	void (*glTexCoordPointerListIBM) (GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	void (*glVertexPointerListIBM) (GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;

	bool IBM_vertex_array_lists = false;

	//*< load IBM Extensions
	void LoadIBMExtensions()
	{
		//cull vertex 
		FetchProcAddress(IBM_cull_vertex, "IBM_cull_vertex");

		//multimode draw arrays
		FetchProcAddress(glMultiModeDrawArraysIBM, "glMultiModeDrawArraysIBM");
		FetchProcAddress(glMultiModeDrawElementsIBM, "glMultiModeDrawElementsIBM");
		FetchProcAddress(IBM_multimode_draw_arrays, "IBM_multimode_draw_arrays");

		//rasterpos clip
		FetchProcAddress(IBM_rasterpos_clip, "IBM_rasterpos_clip");

		//static data
		FetchProcAddress(IBM_static_data, "IBM_static_data");

		//texture mirrored_ repeat 
		FetchProcAddress(IBM_texture_mirrored_repeat, "IBM_texture_mirrored_repeat");

		//vertex array lists 
		FetchProcAddress(glColorPointerListIBM, "glColorPointerListIBM");
		FetchProcAddress(glEdgeFlagPointerListIBM, "glEdgeFlagPointerListIBM");
		FetchProcAddress(glFogCoordPointerListIBM, "glFogCoordPointerListIBM");
		FetchProcAddress(glIndexPointerListIBM, "glIndexPointerListIBM");
		FetchProcAddress(glNormalPointerListIBM, "glNormalPointerListIBM");
		FetchProcAddress(glSecondaryColorPointerListIBM, "glSecondaryColorPointerListIBM");
		FetchProcAddress(glTexCoordPointerListIBM, "glTexCoordPointerListIBM");
		FetchProcAddress(glVertexPointerListIBM, "glVertexPointerListIBM");
		FetchProcAddress(IBM_vertex_array_lists, "IBM_vertex_array_lists");
	}	

#pragma endregion IBM Extensions

	//OpenGL INGR Extensions
#pragma region INGR

	enum OpenGL_INGR_t
	{
		//color clamp
		gl_red_min_clamp_ingr = 0x8560,
		gl_green_min_clamp_ingr = 0x8561,
		gl_blue_min_clamp_ingr = 0x8562,
		gl_alpha_min_clamp_ingr = 0x8563,
		gl_red_max_clamp_ingr = 0x8564,
		gl_green_max_clamp_ingr = 0x8565,
		gl_blue_max_clamp_ingr = 0x8566,
		gl_alpha_max_clamp_ingr = 0x8567,

		//interlace read
		gl_interlace_read_ingr = 0x8568,
	};

	//color clamp
	bool INGR_color_clamp = false;

	//interlace read
	bool INGR_interlace_read = false;

	//*< load INGR Extensions
	void LoadINGRExtensions()
	{
		//color clamp
		FetchProcAddress(INGR_color_clamp, "INGR_color_clamp");

		//interlace read
		FetchProcAddress(INGR_interlace_read, "INGR_interlace_read");
	}



#pragma endregion INGR Extensions

	//OpenGL Intel Extensions
#pragma region Intel

	enum OpenGL_Intel_t
	{
		//conservative rasterization
		gl_conservative_rasterization_intel = 0x83fe,

		//map texture
		gl_layout_default_intel = 0,
		gl_layout_linear_intel = 1,
		gl_layout_linear_cpu_cached_intel = 2,
		gl_texture_memory_layout_intel = 0x83ff,

		//parallel arrays
		gl_parallel_arrays_intel = 0x83f4,
		gl_vertex_array_parallel_pointers_intel = 0x83f5,
		gl_normal_array_parallel_pointers_intel = 0x83f6,
		gl_color_array_parallel_pointers_intel = 0x83f7,
		gl_texture_coord_array_parallel_pointers_intel = 0x83f8,

		//performance query
		gl_perfquery_single_context_intel = 0x0000,
		gl_perfquery_global_context_intel = 0x0001,
		gl_perfquery_donot_flush_intel = 0x83f9,
		gl_perfquery_flush_intel = 0x83fa,
		gl_perfquery_wait_intel = 0x83fb,
		gl_perfquery_counter_event_intel = 0x94f0,
		gl_perfquery_counter_duration_norm_intel = 0x94f1,
		gl_perfquery_counter_duration_raw_intel = 0x94f2,
		gl_perfquery_counter_throughput_intel = 0x94f3,
		gl_perfquery_counter_raw_intel = 0x94f4,
		gl_perfquery_counter_timestamp_intel = 0x94f5,
		gl_perfquery_counter_data_uint32_intel = 0x94f8,
		gl_perfquery_counter_data_uint64_intel = 0x94f9,
		gl_perfquery_counter_data_float_intel = 0x94fa,
		gl_perfquery_counter_data_double_intel = 0x94fb,
		gl_perfquery_counter_data_bool32_intel = 0x94fc,
		gl_perfquery_query_name_length_max_intel = 0x94fd,
		gl_perfquery_counter_name_length_max_intel = 0x94fe,
		gl_perfquery_counter_desc_length_max_intel = 0x94ff,
		gl_perfquery_gpa_extended_counters_intel = 0x9500,
	};

	//conservative rasterization
	bool INTEL_conservative_rasterization = false;

	//fragment shader ordering
	bool INTEL_fragment_shader_ordering = false;

	//framebuffer CMAA 
	bool INTEL_framebuffer_CMAA = false;

	//map texture
	void* (*glMapTexture2DINTEL) (GLuint texture, GLint level, GLbitfield access, GLint * stride, GLenum * layout) = nullptr;
	void (*glSyncTextureINTEL) (GLuint texture) = nullptr;
	void (*glUnmapTexture2DINTEL) (GLuint texture, GLint level) = nullptr;
	bool INTEL_map_texture = false;

	//parallel arrays
	void (*glColorPointervINTEL) (GLint size, GLenum type, const void** pointer) = nullptr;
	void (*glNormalPointervINTEL) (GLenum type, const void** pointer) = nullptr;
	void (*glTexCoordPointervINTEL) (GLint size, GLenum type, const void** pointer) = nullptr;
	void (*glVertexPointervINTEL) (GLint size, GLenum type, const void** pointer) = nullptr;
	bool INTEL_parallel_arrays = false;

	//performance query
	void (*glBeginPerfQueryINTEL) (GLuint queryHandle) = nullptr;
	void (*glCreatePerfQueryINTEL) (GLuint queryId, GLuint* queryHandle) = nullptr;
	void (*glDeletePerfQueryINTEL) (GLuint queryHandle) = nullptr;
	void (*glEndPerfQueryINTEL) (GLuint queryHandle) = nullptr;
	void (*glGetFirstPerfQueryIdINTEL) (GLuint* queryId) = nullptr;
	void (*glGetNextPerfQueryIdINTEL) (GLuint queryId, GLuint* nextQueryId) = nullptr;
	void (*glGetPerfCounterInfoINTEL) (GLuint queryId, GLuint counterId, GLuint counterNameLength, GLchar* counterName, GLuint counterDescLength, GLchar* counterDesc, GLuint* counterOffset, GLuint* counterDataSize, GLuint* counterTypeEnum, GLuint* counterDataTypeEnum, GLuint64* rawCounterMaxValue) = nullptr;
	void (*glGetPerfQueryDataINTEL) (GLuint queryHandle, GLuint flags, GLsizei dataSize, void* data, GLuint* bytesWritten) = nullptr;
	void (*glGetPerfQueryIdByNameINTEL) (GLchar* queryName, GLuint* queryId) = nullptr;
	void (*glGetPerfQueryInfoINTEL) (GLuint queryId, GLuint queryNameLength, GLchar* queryName, GLuint* dataSize, GLuint* noCounters, GLuint* noInstances, GLuint* capsMask) = nullptr;
	bool INTEL_performance_query = false;

	//texture scissor
	void (*glTexScissorFuncINTEL) (GLenum target, GLenum lfunc, GLenum hfunc) = nullptr;
	void (*glTexScissorINTEL) (GLenum target, GLclampf tlow, GLclampf thigh) = nullptr;
	bool INTEL_texture_scissor = false;

	//*< load Intel Extensions
	void LoadIntelExtensions()
	{
		//conservative rasterization
		FetchProcAddress(INTEL_conservative_rasterization, "INTEL_conservative_rasterization");

		//fragment shader ordering
		FetchProcAddress(INTEL_fragment_shader_ordering, "INTEL_fragment_shader_ordering");

		//framebuffer CMAA 
		FetchProcAddress(INTEL_framebuffer_CMAA, "INTEL_framebuffer_CMAA");

		//map texture
		FetchProcAddress(glMapTexture2DINTEL, "glMapTexture2DINTEL");
		FetchProcAddress(glSyncTextureINTEL, "glSyncTextureINTEL");
		FetchProcAddress(glUnmapTexture2DINTEL, "glUnmapTexture2DINTEL");
		FetchProcAddress(INTEL_map_texture, "INTEL_map_texture");

		//parallel arrays
		FetchProcAddress(glColorPointervINTEL, "glColorPointervINTEL");
		FetchProcAddress(glNormalPointervINTEL, "glNormalPointervINTEL");
		FetchProcAddress(glTexCoordPointervINTEL, "glTexCoordPointervINTEL");
		FetchProcAddress(glVertexPointervINTEL, "glVertexPointervINTEL");
		FetchProcAddress(INTEL_parallel_arrays, "INTEL_parallel_arrays");

		//performance query
		FetchProcAddress(glBeginPerfQueryINTEL, "glBeginPerfQueryINTEL");
		FetchProcAddress(glCreatePerfQueryINTEL, "glCreatePerfQueryINTEL");
		FetchProcAddress(glDeletePerfQueryINTEL, "glDeletePerfQueryINTEL");
		FetchProcAddress(glEndPerfQueryINTEL, "glEndPerfQueryINTEL");
		FetchProcAddress(glGetFirstPerfQueryIdINTEL, "glGetFirstPerfQueryIdINTEL");
		FetchProcAddress(glGetNextPerfQueryIdINTEL, "glGetNextPerfQueryIdINTEL");
		FetchProcAddress(glGetPerfCounterInfoINTEL, "glGetPerfCounterInfoINTEL");
		FetchProcAddress(glGetPerfQueryDataINTEL, "glGetPerfQueryDataINTEL");
		FetchProcAddress(glGetPerfQueryIdByNameINTEL, "glGetPerfQueryIdByNameINTEL");
		FetchProcAddress(glGetPerfQueryInfoINTEL, "glGetPerfQueryInfoINTEL");
		FetchProcAddress(INTEL_performance_query, "INTEL_performance_query");

		//texture scissor
		FetchProcAddress(glTexScissorFuncINTEL, "glTexScissorFuncINTEL");
		FetchProcAddress(glTexScissorINTEL, "glTexScissorINTEL");
		FetchProcAddress(INTEL_texture_scissor, "INTEL_texture_scissor");
	}

#pragma endregion intel Extensions

	//OpenGL KHR Extensions
#pragma region KHR

	enum OpengL_KHR_t
	{
		//blend equation advanced
		gl_blend_advanced_coherent_khr = 0x9285,
		gl_multiply_khr = 0x9294,
		gl_screen_khr = 0x9295,
		gl_overlay_khr = 0x9296,
		gl_darken_khr = 0x9297,
		gl_lighten_khr = 0x9298,
		gl_colordodge_khr = 0x9299,
		gl_colorburn_khr = 0x929a,
		gl_hardlight_khr = 0x929b,
		gl_softlight_khr = 0x929c,
		gl_difference_khr = 0x929e,
		gl_exclusion_khr = 0x92a0,
		gl_hsl_hue_khr = 0x92ad,
		gl_hsl_saturation_khr = 0x92ae,
		gl_hsl_color_khr = 0x92af,
		gl_hsl_luminosity_khr = 0x92b0,

		//debug
		gl_context_flag_debug_bit = 0x00000002,
		gl_stack_overflow = 0x0503,
		gl_stack_underflow = 0x0504,
		gl_debug_output_synchronous = 0x8242,
		gl_debug_next_logged_message_length = 0x8243,
		gl_debug_callback_function = 0x8244,
		gl_debug_callback_user_param = 0x8245,
		gl_debug_source_api = 0x8246,
		gl_debug_source_window_system = 0x8247,
		gl_debug_source_shader_compiler = 0x8248,
		gl_debug_source_third_party = 0x8249,
		gl_debug_source_application = 0x824a,
		gl_debug_source_other = 0x824b,
		gl_debug_type_error = 0x824c,
		gl_debug_type_deprecated_behavior = 0x824d,
		gl_debug_type_undefined_behavior = 0x824e,
		gl_debug_type_portability = 0x824f,
		gl_debug_type_performance = 0x8250,
		gl_debug_type_other = 0x8251,
		gl_debug_type_marker = 0x8268,
		gl_debug_type_push_group = 0x8269,
		gl_debug_type_pop_group = 0x826a,
		gl_debug_severity_notification = 0x826b,
		gl_max_debug_group_stack_depth = 0x826c,
		gl_debug_group_stack_depth = 0x826d,
		gl_buffer = 0x82e0,
		gl_shader = 0x82e1,
		gl_program = 0x82e2,
		gl_query = 0x82e3,
		gl_program_pipeline = 0x82e4,
		gl_sampler = 0x82e6,
		gl_display_list = 0x82e7,
		gl_max_label_length = 0x82e8,
		gl_max_debug_message_length = 0x9143,
		gl_max_debug_logged_messages = 0x9144,
		gl_debug_logged_messages = 0x9145,
		gl_debug_severity_high = 0x9146,
		gl_debug_severity_medium = 0x9147,
		gl_debug_severity_low = 0x9148,
		gl_debug_output = 0x92e0,

		//no error
		gl_context_flag_no_error_bit_khr = 0x00000008,

		//parallel shader compile
		gl_max_shader_compiler_threads_khr = 0x91b0,
		gl_completion_status_khr = 0x91b1,

		//robustness
		gl_context_lost = 0x0507,
		gl_lose_context_on_reset = 0x8252,
		gl_guilty_context_reset = 0x8253,
		gl_innocent_context_reset = 0x8254,
		gl_unknown_context_reset = 0x8255,
		gl_reset_notification_strategy = 0x8256,
		gl_no_reset_notification = 0x8261,
		gl_context_robust_access = 0x90f3,

		//texture compression astc hdr
		gl_compressed_rgba_astc_4x4_khr = 0x93b0,
		gl_compressed_rgba_astc_5x4_khr = 0x93b1,
		gl_compressed_rgba_astc_5x5_khr = 0x93b2,
		gl_compressed_rgba_astc_6x5_khr = 0x93b3,
		gl_compressed_rgba_astc_6x6_khr = 0x93b4,
		gl_compressed_rgba_astc_8x5_khr = 0x93b5,
		gl_compressed_rgba_astc_8x6_khr = 0x93b6,
		gl_compressed_rgba_astc_8x8_khr = 0x93b7,
		gl_compressed_rgba_astc_10x5_khr = 0x93b8,
		gl_compressed_rgba_astc_10x6_khr = 0x93b9,
		gl_compressed_rgba_astc_10x8_khr = 0x93ba,
		gl_compressed_rgba_astc_10x10_khr = 0x93bb,
		gl_compressed_rgba_astc_12x10_khr = 0x93bc,
		gl_compressed_rgba_astc_12x12_khr = 0x93bd,
		gl_compressed_srgb8_alpha8_astc_4x4_khr = 0x93d0,
		gl_compressed_srgb8_alpha8_astc_5x4_khr = 0x93d1,
		gl_compressed_srgb8_alpha8_astc_5x5_khr = 0x93d2,
		gl_compressed_srgb8_alpha8_astc_6x5_khr = 0x93d3,
		gl_compressed_srgb8_alpha8_astc_6x6_khr = 0x93d4,
		gl_compressed_srgb8_alpha8_astc_8x5_khr = 0x93d5,
		gl_compressed_srgb8_alpha8_astc_8x6_khr = 0x93d6,
		gl_compressed_srgb8_alpha8_astc_8x8_khr = 0x93d7,
		gl_compressed_srgb8_alpha8_astc_10x5_khr = 0x93d8,
		gl_compressed_srgb8_alpha8_astc_10x6_khr = 0x93d9,
		gl_compressed_srgb8_alpha8_astc_10x8_khr = 0x93da,
		gl_compressed_srgb8_alpha8_astc_10x10_khr = 0x93db,
		gl_compressed_srgb8_alpha8_astc_12x10_khr = 0x93dc,
		gl_compressed_srgb8_alpha8_astc_12x12_khr = 0x93dd,
	};

	//blend equation advanced
	void (*glBlendBarrierKHR) (void) = nullptr;
	bool KHR_blend_equation_advanced = false;

	//blend equation advanced coherent
	bool KHR_blend_equation_advanced_coherent = false;

	//context flush control
	bool KHR_context_flush_control = false;

	//debug
	typedef void (*GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam);
	void (*glDebugMessageCallback) (GLDEBUGPROC callback, const void* userParam) = nullptr;
	void (*glDebugMessageControl) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled) = nullptr;
	void (*glDebugMessageInsert) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf) = nullptr;
	GLuint(*glGetDebugMessageLog) (GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog) = nullptr;
	void (*glGetObjectLabel) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label) = nullptr;
	void (*glGetObjectPtrLabel) (void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label) = nullptr;
	void (*glObjectLabel) (GLenum identifier, GLuint name, GLsizei length, const GLchar* label) = nullptr;
	void (*glObjectPtrLabel) (void* ptr, GLsizei length, const GLchar* label) = nullptr;
	void (*glPopDebugGroup) (void) = nullptr;
	void (*glPushDebugGroup) (GLenum source, GLuint id, GLsizei length, const GLchar* message) = nullptr;
	bool KHR_debug = false;

	//no error
	bool KHR_no_error = false;

	//parallel shader compile
	void (*glMaxShaderCompilerThreadsKHR) (GLuint count) = nullptr;
	bool KHR_parallel_shader_compile = false;

	//robust buffer access behavior 
	bool KHR_robust_buffer_access_behavior = false;

	//robustness
	void (*glGetnUniformfv) (GLuint program, GLint location, GLsizei bufSize, GLfloat * params) = nullptr;
	void (*glGetnUniformiv) (GLuint program, GLint location, GLsizei bufSize, GLint* params) = nullptr;
	void (*glGetnUniformuiv) (GLuint program, GLint location, GLsizei bufSize, GLuint* params) = nullptr;
	void (*glReadnPixels) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data) = nullptr;
	bool KHR_robustness = false;

	//texture compression astc hdr
	bool KHR_texture_compression_astc_hdr = false;

	//texture compression astc ldr
	bool KHR_texture_compression_astc_ldr = false;

	//texture compression astc sliced 3d
	bool KHR_texture_compression_astc_sliced_3d = false;

	//*< load KHR Extensions
	void LoadKHRExtensions()
	{
		//blend equation advanced
		FetchProcAddress(glBlendBarrierKHR, "glBlendBarrierKHR");

		FetchProcAddress(KHR_blend_equation_advanced, "KHR_blend_equation_advanced");

		//blend equation advanced coherent
		FetchProcAddress(KHR_blend_equation_advanced_coherent, "KHR_blend_equation_advanced_coherent");

		//context flush control
		FetchProcAddress(KHR_context_flush_control, "KHR_context_flush_control");

		//debug
		FetchProcAddress(glDebugMessageCallback, "glDebugMessageCallback");
		FetchProcAddress(glDebugMessageControl, "glDebugMessageControl");
		FetchProcAddress(glDebugMessageInsert, "glDebugMessageInsert");
		FetchProcAddress(glGetDebugMessageLog, "glGetDebugMessageLog");
		FetchProcAddress(glGetObjectLabel, "glGetObjectLabel");
		FetchProcAddress(glGetObjectPtrLabel, "glGetObjectPtrLabel");
		FetchProcAddress(glObjectLabel, "glObjectLabel");
		FetchProcAddress(glObjectPtrLabel, "glObjectPtrLabel");
		FetchProcAddress(glPopDebugGroup, "glPopDebugGroup");
		FetchProcAddress(glPushDebugGroup, "glPushDebugGroup");
		FetchProcAddress(KHR_debug, "KHR_debug");

		//no error
		FetchProcAddress(KHR_no_error, "KHR_no_error");

		//parallel shader compile
		FetchProcAddress(glMaxShaderCompilerThreadsKHR, "glMaxShaderCompilerThreadsKHR");
		FetchProcAddress(KHR_parallel_shader_compile, "KHR_parallel_shader_compile");

		//robust buffer access behavior 
		FetchProcAddress(KHR_robust_buffer_access_behavior, "KHR_robust_buffer_access_behavior");

		//robustness
		FetchProcAddress(glGetnUniformfv, "glGetnUniformfv");
		FetchProcAddress(glGetnUniformiv, "glGetnUniformiv");
		FetchProcAddress(glGetnUniformuiv, "glGetnUniformuiv");
		FetchProcAddress(glReadnPixels, "glReadnPixels");
		FetchProcAddress(KHR_robustness, "KHR_robustness");

		//texture compression astc hdr
		FetchProcAddress(KHR_texture_compression_astc_hdr, "KHR_texture_compression_astc_hdr");

		//texture compression astc ldr
		FetchProcAddress(KHR_texture_compression_astc_ldr, "KHR_texture_compression_astc_ldr");

		//texture compression astc sliced 3d
		FetchProcAddress(KHR_texture_compression_astc_sliced_3d, "KHR_texture_compression_astc_sliced_3d");
	}

	

#pragma endregion KHR Extensions

	//OpenGL KTX Extensions
#pragma region KTX

	enum OpenGL_KTX_t
	{
		//buffer region
		gl_ktx_front_region = 0x0,
		gl_ktx_back_region = 0x1,
		gl_ktx_z_region = 0x2,
		gl_ktx_stencil_region = 0x3,
	};

	//buffer region
	GLuint(*glBufferRegionEnabled) (void) = nullptr;
	void (*glDeleteBufferRegion) (GLenum region) = nullptr;
	void (*glDrawBufferRegion) (GLuint region, GLint x, GLint y, GLsizei width, GLsizei height, GLint xDest, GLint yDest) = nullptr;
	GLuint(*glNewBufferRegion) (GLenum region) = nullptr;
	void (*glReadBufferRegion) (GLuint region, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	bool KTX_buffer_region = false;

	//*< load KTX Extensions
	void LoadKTXExtensions()
	{
		//buffer region
		FetchProcAddress(glBufferRegionEnabled, "glBufferRegionEnabled");
		FetchProcAddress(glDeleteBufferRegion, "glDeleteBufferRegion");
		FetchProcAddress(glDrawBufferRegion, "glDrawBufferRegion");
		FetchProcAddress(glNewBufferRegion, "glNewBufferRegion");
		FetchProcAddress(glReadBufferRegion, "glReadBufferRegion");
		FetchProcAddress(KTX_buffer_region, "KTX_buffer_region");
	}

#pragma endregion KTX Extensions

	//OpenGL MESAX Extensions
#pragma region MESAX

	enum OpenGL_MESAX_t
	{
		//texture stack
		gl_texture_1d_stack_mesax = 0x8759,
		gl_texture_2d_stack_mesax = 0x875a,
		gl_proxy_texture_1d_stack_mesax = 0x875b,
		gl_proxy_texture_2d_stack_mesax = 0x875c,
		gl_texture_1d_stack_binding_mesax = 0x875d,
		gl_texture_2d_stack_binding_mesax = 0x875e,
	};

	//texture stack
	bool MESAX_texture_stack = false;

	//*< load MESAX Extensions
	void LoadMESAXExtensions()
	{
		//texture stack
		FetchProcAddress(MESAX_texture_stack, "MESAX_texture_stack");
	}

#pragma endregion MESAX Extensions

	//OpenGL MESA Extensions
#pragma region MESA
	   
	enum OpenGL_MESA_t
	{
		//ycbcr_texture
		gl_unsigned_short_8_8_mesa = 0x85ba,
		gl_unsigned_short_8_8_rev_mesa = 0x85bb,
		gl_ycbcr_mesa = 0x8757,

		//pack_invert
		gl_pack_invert_mesa = 0x8758,
	};

	//pack_invert
	bool MESA_pack_invert = false;

	//resize_buffers
	void (*glResizeBuffersMESA) (void) = nullptr;
	bool MESA_resize_buffers = false;

	//shader_integer_functions
	bool MESA_shader_integer_functions = false;

	//window_pos
	void (*glWindowPos2dMESA) (GLdouble x, GLdouble y) = nullptr;
	void (*glWindowPos2dvMESA) (const GLdouble* p) = nullptr;
	void (*glWindowPos2fMESA) (GLfloat x, GLfloat y) = nullptr;
	void (*glWindowPos2fvMESA) (const GLfloat* p) = nullptr;
	void (*glWindowPos2iMESA) (GLint x, GLint y) = nullptr;
	void (*glWindowPos2ivMESA) (const GLint* p) = nullptr;
	void (*glWindowPos2sMESA) (GLshort x, GLshort y) = nullptr;
	void (*glWindowPos2svMESA) (const GLshort* p) = nullptr;
	void (*glWindowPos3dMESA) (GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void (*glWindowPos3dvMESA) (const GLdouble* p) = nullptr;
	void (*glWindowPos3fMESA) (GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glWindowPos3fvMESA) (const GLfloat* p) = nullptr;
	void (*glWindowPos3iMESA) (GLint x, GLint y, GLint z) = nullptr;
	void (*glWindowPos3ivMESA) (const GLint* p) = nullptr;
	void (*glWindowPos3sMESA) (GLshort x, GLshort y, GLshort z) = nullptr;
	void (*glWindowPos3svMESA) (const GLshort* p) = nullptr;
	void (*glWindowPos4dMESA) (GLdouble x, GLdouble y, GLdouble z, GLdouble) = nullptr;
	void (*glWindowPos4dvMESA) (const GLdouble* p) = nullptr;
	void (*glWindowPos4fMESA) (GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void (*glWindowPos4fvMESA) (const GLfloat* p) = nullptr;
	void (*glWindowPos4iMESA) (GLint x, GLint y, GLint z, GLint w) = nullptr;
	void (*glWindowPos4ivMESA) (const GLint* p) = nullptr;
	void (*glWindowPos4sMESA) (GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
	void (*glWindowPos4svMESA) (const GLshort* p) = nullptr;
	bool MESA_window_pos = false;

	//ycbcr_texture
	bool MESA_ycbcr_texture = false;

	//*< load MESA Extensions
	void LoadMESAExtensions()
	{
		//pack_invert
		FetchProcAddress(MESA_pack_invert, "MESA_pack_invert");

		//resize_buffers
		FetchProcAddress(glResizeBuffersMESA, "glResizeBuffersMESA");
		FetchProcAddress(MESA_resize_buffers, "MESA_resize_buffers");

		//shader_integer_functions
		FetchProcAddress(MESA_shader_integer_functions, "MESA_shader_integer_functions");

		//window_pos
		FetchProcAddress(glWindowPos2dMESA, "glWindowPos2dMESA");
		FetchProcAddress(glWindowPos2dvMESA, "glWindowPos2dvMESA");
		FetchProcAddress(glWindowPos2fMESA, "glWindowPos2fMESA");
		FetchProcAddress(glWindowPos2fvMESA, "glWindowPos2fvMESA");
		FetchProcAddress(glWindowPos2iMESA, "glWindowPos2iMESA");
		FetchProcAddress(glWindowPos2ivMESA, "glWindowPos2ivMESA");
		FetchProcAddress(glWindowPos2sMESA, "glWindowPos2sMESA");
		FetchProcAddress(glWindowPos2svMESA, "glWindowPos2svMESA");
		FetchProcAddress(glWindowPos3dMESA, "glWindowPos3dMESA");
		FetchProcAddress(glWindowPos3dvMESA, "glWindowPos3dvMESA");
		FetchProcAddress(glWindowPos3fMESA, "glWindowPos3fMESA");
		FetchProcAddress(glWindowPos3fvMESA, "glWindowPos3fvMESA");
		FetchProcAddress(glWindowPos3iMESA, "glWindowPos3iMESA");
		FetchProcAddress(glWindowPos3ivMESA, "glWindowPos3ivMESA");
		FetchProcAddress(glWindowPos3sMESA, "glWindowPos3sMESA");
		FetchProcAddress(glWindowPos3svMESA, "glWindowPos3svMESA");
		FetchProcAddress(glWindowPos4dMESA, "glWindowPos4dMESA");
		FetchProcAddress(glWindowPos4dvMESA, "glWindowPos4dvMESA");
		FetchProcAddress(glWindowPos4fMESA, "glWindowPos4fMESA");
		FetchProcAddress(glWindowPos4fvMESA, "glWindowPos4fvMESA");
		FetchProcAddress(glWindowPos4iMESA, "glWindowPos4iMESA");
		FetchProcAddress(glWindowPos4ivMESA, "glWindowPos4ivMESA");
		FetchProcAddress(glWindowPos4sMESA, "glWindowPos4sMESA");
		FetchProcAddress(glWindowPos4svMESA, "glWindowPos4svMESA");
		FetchProcAddress(MESA_window_pos, "MESA_window_pos");

		//ycbcr_texture
		FetchProcAddress(MESA_ycbcr_texture, "MESA_ycbcr_texture");
	}

#pragma endregion MESA Extensions
		
	//OpenGL NVX Extensions
#pragma region NVX

	enum OpenGL_NVX_t
	{
		//gpu_memory_info
		gl_gpu_memory_info_dedicated_vidmem_nvx = 0x9047,
		gl_gpu_memory_info_total_available_memory_nvx = 0x9048,
		gl_gpu_memory_info_current_available_vidmem_nvx = 0x9049,
		gl_gpu_memory_info_eviction_count_nvx = 0x904a,
		gl_gpu_memory_info_evicted_memory_nvx = 0x904b,

		//linked_gpu_multicast
		gl_lgpu_separate_storage_bit_nvx = 0x0800,
		gl_max_lgpu_gpus_nvx = 0x92ba,
	};

	//blend_equation_advanced_multi_draw_buffers
	bool NVX_blend_equation_advanced_multi_draw_buffers = false;

	//conditional_render
	void (*glBeginConditionalRenderNVX) (GLuint id) = nullptr;
	void (*glEndConditionalRenderNVX) (void) = nullptr;
	bool NVX_conditional_render = false;

	//gpu_memory_info
	bool NVX_gpu_memory_info = false;

	//linked_gpu_multicast
	void (*glLGPUCopyImageSubDataNVX) (GLuint sourceGpu, GLbitfield destinationGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srxY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
	void (*glLGPUInterlockNVX) (void) = nullptr;
	void (*glLGPUNamedBufferSubDataNVX) (GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) = nullptr;
	bool NVX_linked_gpu_multicast = false;

	//*< load NVX Extensions
	void LoadNVXExtensions()
	{
		//blend_equation_advanced_multi_draw_buffers
		FetchProcAddress(NVX_blend_equation_advanced_multi_draw_buffers, "NVX_blend_equation_advanced_multi_draw_buffers");

		//conditional_render
		FetchProcAddress(glBeginConditionalRenderNVX, "glBeginConditionalRenderNVX");
		FetchProcAddress(glEndConditionalRenderNVX, "glEndConditionalRenderNVX");
		FetchProcAddress(NVX_conditional_render, "NVX_conditional_render");

		//gpu_memory_info
		FetchProcAddress(NVX_gpu_memory_info, "NVX_gpu_memory_info");

		//linked_gpu_multicast
		FetchProcAddress(glLGPUCopyImageSubDataNVX, "glLGPUCopyImageSubDataNVX");
		FetchProcAddress(glLGPUInterlockNVX, "glLGPUInterlockNVX");
		FetchProcAddress(glLGPUNamedBufferSubDataNVX, "glLGPUNamedBufferSubDataNVX");
		FetchProcAddress(NVX_linked_gpu_multicast, "NVX_linked_gpu_multicast");
	}		

#pragma endregion NVX Extensions

	//OpenGL NV Extensions
#pragma region NV

		typedef GLintptr GLvdpauSurfaceNV;
		typedef unsigned short GLhalf;

		enum OpenGL_NV_t
		{
			//3dvision_settings
			gl_3dvision_stereo_nv = 0x90f4,
			gl_stereo_separation_nv = 0x90f5,
			gl_stereo_convergence_nv = 0x90f6,
			gl_stereo_cutoff_nv = 0x90f7,
			gl_stereo_projection_nv = 0x90f8,
			gl_stereo_projection_perspective_nv = 0x90f9,
			gl_stereo_projection_ortho_nv = 0x90fa,

			//egl_stream_consumer_external
			gl_texture_external_oes = 0x8d65,
			gl_sampler_external_oes = 0x8d66,
			gl_texture_binding_external_oes = 0x8d67,
			gl_required_texture_image_units_oes = 0x8d68,

			//alpha_to_coverage_dither_control
			gl_alpha_to_coverage_dither_mode_nv = 0x92bf,
			gl_alpha_to_coverage_dither_default_nv = 0x934d,
			gl_alpha_to_coverage_dither_enable_nv = 0x934e,
			gl_alpha_to_coverage_dither_disable_nv = 0x934f,

			//bgr
			gl_bgr_nv = 0x80e0,

			//blend_equation_advanced
			gl_xor_nv = 0x1506,
			gl_red_nv = 0x1903,
			gl_green_nv = 0x1904,
			gl_blue_nv = 0x1905,
			gl_blend_premultiplied_src_nv = 0x9280,
			gl_blend_overlap_nv = 0x9281,
			gl_uncorrelated_nv = 0x9282,
			gl_disjoint_nv = 0x9283,
			gl_conjoint_nv = 0x9284,
			gl_blend_advanced_coherent_nv = 0x9285,
			gl_src_nv = 0x9286,
			gl_dst_nv = 0x9287,
			gl_src_over_nv = 0x9288,
			gl_dst_over_nv = 0x9289,
			gl_src_in_nv = 0x928a,
			gl_dst_in_nv = 0x928b,
			gl_src_out_nv = 0x928c,
			gl_dst_out_nv = 0x928d,
			gl_src_atop_nv = 0x928e,
			gl_dst_atop_nv = 0x928f,
			gl_plus_nv = 0x9291,
			gl_plus_darker_nv = 0x9292,
			gl_multiply_nv = 0x9294,
			gl_screen_nv = 0x9295,
			gl_overlay_nv = 0x9296,
			gl_darken_nv = 0x9297,
			gl_lighten_nv = 0x9298,
			gl_colordodge_nv = 0x9299,
			gl_colorburn_nv = 0x929a,
			gl_hardlight_nv = 0x929b,
			gl_softlight_nv = 0x929c,
			gl_difference_nv = 0x929e,
			gl_minus_nv = 0x929f,
			gl_exclusion_nv = 0x92a0,
			gl_contrast_nv = 0x92a1,
			gl_invert_rgb_nv = 0x92a3,
			gl_lineardodge_nv = 0x92a4,
			gl_linearburn_nv = 0x92a5,
			gl_vividlight_nv = 0x92a6,
			gl_linearlight_nv = 0x92a7,
			gl_pinlight_nv = 0x92a8,
			gl_hardmix_nv = 0x92a9,
			gl_hsl_hue_nv = 0x92ad,
			gl_hsl_saturation_nv = 0x92ae,
			gl_hsl_color_nv = 0x92af,
			gl_hsl_luminosity_nv = 0x92b0,
			gl_plus_clamped_nv = 0x92b1,
			gl_plus_clamped_alpha_nv = 0x92b2,
			gl_minus_clamped_nv = 0x92b3,
			gl_invert_ovg_nv = 0x92b4,

			//blend_minmax_factor
			//gl_factor_min_amd = 0x901c,
			//gl_factor_max_amd = 0x901d,

			//clip_space_w_scaling
			gl_viewport_position_w_scale_nv = 0x937c,
			gl_viewport_position_w_scale_x_coeff_nv = 0x937d,
			gl_viewport_position_w_scale_y_coeff_nv = 0x937e,

			//command_list
			gl_terminate_sequence_command_nv = 0x0000,
			gl_nop_command_nv = 0x0001,
			gl_draw_elements_command_nv = 0x0002,
			gl_draw_arrays_command_nv = 0x0003,
			gl_draw_elements_strip_command_nv = 0x0004,
			gl_draw_arrays_strip_command_nv = 0x0005,
			gl_draw_elements_instanced_command_nv = 0x0006,
			gl_draw_arrays_instanced_command_nv = 0x0007,
			gl_element_address_command_nv = 0x0008,
			gl_attribute_address_command_nv = 0x0009,
			gl_uniform_address_command_nv = 0x000a,
			gl_blend_color_command_nv = 0x000b,
			gl_stencil_ref_command_nv = 0x000c,
			gl_line_width_command_nv = 0x000d,
			gl_polygon_offset_command_nv = 0x000e,
			gl_alpha_ref_command_nv = 0x000f,
			gl_viewport_command_nv = 0x0010,
			gl_scissor_command_nv = 0x0011,
			gl_front_face_command_nv = 0x0012,

			//compute_program5
			gl_compute_program_nv = 0x90fb,
			gl_compute_program_parameter_buffer_nv = 0x90fc,

			//conditional_render
			gl_query_wait_nv = 0x8e13,
			gl_query_no_wait_nv = 0x8e14,
			gl_query_by_region_wait_nv = 0x8e15,
			gl_query_by_region_no_wait_nv = 0x8e16,

			//conservative_raster
			gl_conservative_rasterization_nv = 0x9346,
			gl_subpixel_precision_bias_x_bits_nv = 0x9347,
			gl_subpixel_precision_bias_y_bits_nv = 0x9348,
			gl_max_subpixel_precision_bias_bits_nv = 0x9349,

			//conservative_raster_dilate
			gl_conservative_raster_dilate_nv = 0x9379,
			gl_conservative_raster_dilate_range_nv = 0x937a,
			gl_conservative_raster_dilate_granularity_nv = 0x937b,

			//conservative_raster_pre_snap_triangles
			gl_conservative_raster_mode_nv = 0x954d,
			gl_conservative_raster_mode_post_snap_nv = 0x954e,
			gl_conservative_raster_mode_pre_snap_triangles_nv = 0x954f,

			//copy_buffer
			gl_copy_read_buffer_nv = 0x8f36,
			gl_copy_write_buffer_nv = 0x8f37,

			//copy_depth_to_color
			gl_depth_stencil_to_rgba_nv = 0x886e,
			gl_depth_stencil_to_bgra_nv = 0x886f,

			//deep_texture3d
			gl_max_deep_3d_texture_width_height_nv = 0x90d0,
			gl_max_deep_3d_texture_depth_nv = 0x90d1,

			//depth_buffer_float
			gl_depth_component32f_nv = 0x8dab,
			gl_depth32f_stencil8_nv = 0x8dac,
			gl_float_32_unsigned_int_24_8_rev_nv = 0x8dad,
			gl_depth_buffer_float_mode_nv = 0x8daf,

			//depth_clamp
			gl_depth_clamp_nv = 0x864f,

			//depth_range_unclamped
			gl_sample_count_bits_nv = 0x8864,
			gl_current_sample_count_query_nv = 0x8865,
			gl_query_result_nv = 0x8866,
			gl_query_result_available_nv = 0x8867,
			gl_sample_count_nv = 0x8914,

			//draw_buffers
			gl_max_draw_buffers_nv = 0x8824,
			gl_draw_buffer0_nv = 0x8825,
			gl_draw_buffer1_nv = 0x8826,
			gl_draw_buffer2_nv = 0x8827,
			gl_draw_buffer3_nv = 0x8828,
			gl_draw_buffer4_nv = 0x8829,
			gl_draw_buffer5_nv = 0x882a,
			gl_draw_buffer6_nv = 0x882b,
			gl_draw_buffer7_nv = 0x882c,
			gl_draw_buffer8_nv = 0x882d,
			gl_draw_buffer9_nv = 0x882e,
			gl_draw_buffer10_nv = 0x882f,
			gl_draw_buffer11_nv = 0x8830,
			gl_draw_buffer12_nv = 0x8831,
			gl_draw_buffer13_nv = 0x8832,
			gl_draw_buffer14_nv = 0x8833,
			gl_draw_buffer15_nv = 0x8834,
			gl_color_attachment0_nv = 0x8ce0,
			gl_color_attachment1_nv = 0x8ce1,
			gl_color_attachment2_nv = 0x8ce2,
			gl_color_attachment3_nv = 0x8ce3,
			gl_color_attachment4_nv = 0x8ce4,
			gl_color_attachment5_nv = 0x8ce5,
			gl_color_attachment6_nv = 0x8ce6,
			gl_color_attachment7_nv = 0x8ce7,
			gl_color_attachment8_nv = 0x8ce8,
			gl_color_attachment9_nv = 0x8ce9,
			gl_color_attachment10_nv = 0x8cea,
			gl_color_attachment11_nv = 0x8ceb,
			gl_color_attachment12_nv = 0x8cec,
			gl_color_attachment13_nv = 0x8ced,
			gl_color_attachment14_nv = 0x8cee,
			gl_color_attachment15_nv = 0x8cef,

			//evaluators
			gl_eval_2d_nv = 0x86c0,
			gl_eval_triangular_2d_nv = 0x86c1,
			gl_map_tessellation_nv = 0x86c2,
			gl_map_attrib_u_order_nv = 0x86c3,
			gl_map_attrib_v_order_nv = 0x86c4,
			gl_eval_fractional_tessellation_nv = 0x86c5,
			gl_eval_vertex_attrib0_nv = 0x86c6,
			gl_eval_vertex_attrib1_nv = 0x86c7,
			gl_eval_vertex_attrib2_nv = 0x86c8,
			gl_eval_vertex_attrib3_nv = 0x86c9,
			gl_eval_vertex_attrib4_nv = 0x86ca,
			gl_eval_vertex_attrib5_nv = 0x86cb,
			gl_eval_vertex_attrib6_nv = 0x86cc,
			gl_eval_vertex_attrib7_nv = 0x86cd,
			gl_eval_vertex_attrib8_nv = 0x86ce,
			gl_eval_vertex_attrib9_nv = 0x86cf,
			gl_eval_vertex_attrib10_nv = 0x86d0,
			gl_eval_vertex_attrib11_nv = 0x86d1,
			gl_eval_vertex_attrib12_nv = 0x86d2,
			gl_eval_vertex_attrib13_nv = 0x86d3,
			gl_eval_vertex_attrib14_nv = 0x86d4,
			gl_eval_vertex_attrib15_nv = 0x86d5,
			gl_max_map_tessellation_nv = 0x86d6,
			gl_max_rational_eval_order_nv = 0x86d7,

			//explicit_multisample
			gl_sample_position_nv = 0x8e50,
			gl_sample_mask_nv = 0x8e51,
			gl_sample_mask_value_nv = 0x8e52,
			gl_texture_binding_renderbuffer_nv = 0x8e53,
			gl_texture_renderbuffer_data_store_binding_nv = 0x8e54,
			gl_texture_renderbuffer_nv = 0x8e55,
			gl_sampler_renderbuffer_nv = 0x8e56,
			gl_int_sampler_renderbuffer_nv = 0x8e57,
			gl_unsigned_int_sampler_renderbuffer_nv = 0x8e58,
			gl_max_sample_mask_words_nv = 0x8e59,

			//fbo_color_attachments
			gl_max_color_attachments_nv = 0x8cdf,
			/*gl_color_attachment0_nv = 0x8ce0,
			gl_color_attachment1_nv = 0x8ce1,
			gl_color_attachment2_nv = 0x8ce2,
			gl_color_attachment3_nv = 0x8ce3,
			gl_color_attachment4_nv = 0x8ce4,
			gl_color_attachment5_nv = 0x8ce5,
			gl_color_attachment6_nv = 0x8ce6,
			gl_color_attachment7_nv = 0x8ce7,
			gl_color_attachment8_nv = 0x8ce8,
			gl_color_attachment9_nv = 0x8ce9,
			gl_color_attachment10_nv = 0x8cea,
			gl_color_attachment11_nv = 0x8ceb,
			gl_color_attachment12_nv = 0x8cec,
			gl_color_attachment13_nv = 0x8ced,
			gl_color_attachment14_nv = 0x8cee,
			gl_color_attachment15_nv = 0x8cef,*/

			//fence
			gl_all_completed_nv = 0x84f2,
			gl_fence_status_nv = 0x84f3,
			gl_fence_condition_nv = 0x84f4,

			//fill_rectangle
			gl_fill_rectangle_nv = 0x933c,

			//float_buffer
			gl_float_r_nv = 0x8880,
			gl_float_rg_nv = 0x8881,
			gl_float_rgb_nv = 0x8882,
			gl_float_rgba_nv = 0x8883,
			gl_float_r16_nv = 0x8884,
			gl_float_r32_nv = 0x8885,
			gl_float_rg16_nv = 0x8886,
			gl_float_rg32_nv = 0x8887,
			gl_float_rgb16_nv = 0x8888,
			gl_float_rgb32_nv = 0x8889,
			gl_float_rgba16_nv = 0x888a,
			gl_float_rgba32_nv = 0x888b,
			gl_texture_float_components_nv = 0x888c,
			gl_float_clear_color_value_nv = 0x888d,
			gl_float_rgba_mode_nv = 0x888e,

			//fog_distanc
			gl_fog_distance_mode_nv = 0x855a,
			gl_eye_radial_nv = 0x855b,
			gl_eye_plane_absolute_nv = 0x855c,

			//fragment_coverage_to_color
			gl_fragment_coverage_to_color_nv = 0x92dd,
			gl_fragment_coverage_color_nv = 0x92de,

			//fragment_program
			gl_max_fragment_program_local_parameters_nv = 0x8868,
			gl_fragment_program_nv = 0x8870,
			gl_max_texture_coords_nv = 0x8871,
			gl_max_texture_image_units_nv = 0x8872,
			gl_fragment_program_binding_nv = 0x8873,
			gl_program_error_string_nv = 0x8874,

			//fragment_program2
			gl_max_program_exec_instructions_nv = 0x88f4,
			gl_max_program_call_depth_nv = 0x88f5,
			gl_max_program_if_depth_nv = 0x88f6,
			gl_max_program_loop_depth_nv = 0x88f7,
			gl_max_program_loop_count_nv = 0x88f8,

			//framebuffer_blit
			gl_draw_framebuffer_binding_nv = 0x8ca6,
			gl_read_framebuffer_nv = 0x8ca8,
			gl_draw_framebuffer_nv = 0x8ca9,
			gl_read_framebuffer_binding_nv = 0x8caa,

			//framebuffer_mixed_samples
			/*gl_color_samples_nv = 0x8e20,
			gl_raster_multisample_ext = 0x9327,
			gl_raster_samples_ext = 0x9328,
			gl_max_raster_samples_ext = 0x9329,
			gl_raster_fixed_sample_locations_ext = 0x932a,
			gl_multisample_rasterization_allowed_ext = 0x932b,
			gl_effective_raster_samples_ext = 0x932c,
			gl_depth_samples_nv = 0x932d,
			gl_stencil_samples_nv = 0x932e,
			gl_mixed_depth_samples_supported_nv = 0x932f,
			gl_mixed_stencil_samples_supported_nv = 0x9330,
			gl_coverage_modulation_table_nv = 0x9331,
			gl_coverage_modulation_nv = 0x9332,
			gl_coverage_modulation_table_size_nv = 0x9333,*/

			//framebuffer_multisample
			gl_renderbuffer_samples_nv = 0x8cab,
			gl_framebuffer_incomplete_multisample_nv = 0x8d56,
			gl_max_samples_nv = 0x8d57,

			//framebuffer_multisample_coverage
			gl_renderbuffer_coverage_samples_nv = 0x8cab,
			gl_renderbuffer_color_samples_nv = 0x8e10,
			gl_max_multisample_coverage_modes_nv = 0x8e11,
			gl_multisample_coverage_modes_nv = 0x8e12,

			//geometry_program4
			gl_geometry_program_nv = 0x8c26,
			gl_max_program_output_vertices_nv = 0x8c27,
			gl_max_program_total_output_components_nv = 0x8c28,

			//gpu_multicast
			gl_per_gpu_storage_bit_nv = 0x0800,
			gl_multicast_gpus_nv = 0x92ba,
			gl_per_gpu_storage_nv = 0x9548,
			gl_multicast_programmable_sample_location_nv = 0x9549,
			gl_render_gpu_mask_nv = 0x9558,

			//gpu_program4
			gl_min_program_texel_offset_nv = 0x8904,
			gl_max_program_texel_offset_nv = 0x8905,
			gl_program_attrib_components_nv = 0x8906,
			gl_program_result_components_nv = 0x8907,
			gl_max_program_attrib_components_nv = 0x8908,
			gl_max_program_result_components_nv = 0x8909,
			gl_max_program_generic_attribs_nv = 0x8da5,
			gl_max_program_generic_results_nv = 0x8da6,

			//gpu_program5
			gl_max_geometry_program_invocations_nv = 0x8e5a,
			gl_min_fragment_interpolation_offset_nv = 0x8e5b,
			gl_max_fragment_interpolation_offset_nv = 0x8e5c,
			gl_fragment_program_interpolation_offset_bits_nv = 0x8e5d,
			gl_min_program_texture_gather_offset_nv = 0x8e5e,
			gl_max_program_texture_gather_offset_nv = 0x8e5f,

			//gpu_shader5
			gl_int64_nv = 0x140e,
			gl_unsigned_int64_nv = 0x140f,
			gl_int8_nv = 0x8fe0,
			gl_int8_vec2_nv = 0x8fe1,
			gl_int8_vec3_nv = 0x8fe2,
			gl_int8_vec4_nv = 0x8fe3,
			gl_int16_nv = 0x8fe4,
			gl_int16_vec2_nv = 0x8fe5,
			gl_int16_vec3_nv = 0x8fe6,
			gl_int16_vec4_nv = 0x8fe7,
			gl_int64_vec2_nv = 0x8fe9,
			gl_int64_vec3_nv = 0x8fea,
			gl_int64_vec4_nv = 0x8feb,
			gl_unsigned_int8_nv = 0x8fec,
			gl_unsigned_int8_vec2_nv = 0x8fed,
			gl_unsigned_int8_vec3_nv = 0x8fee,
			gl_unsigned_int8_vec4_nv = 0x8fef,
			gl_unsigned_int16_nv = 0x8ff0,
			gl_unsigned_int16_vec2_nv = 0x8ff1,
			gl_unsigned_int16_vec3_nv = 0x8ff2,
			gl_unsigned_int16_vec4_nv = 0x8ff3,
			gl_unsigned_int64_vec2_nv = 0x8ff5,
			gl_unsigned_int64_vec3_nv = 0x8ff6,
			gl_unsigned_int64_vec4_nv = 0x8ff7,
			/*gl_float16_nv = 0x8ff8,
			gl_float16_vec2_nv = 0x8ff9,
			gl_float16_vec3_nv = 0x8ffa,
			gl_float16_vec4_nv = 0x8ffb,*/

			//half_float
			gl_half_float_nv = 0x140b,

			//instanced_arrays
			gl_vertex_attrib_array_divisor_nv = 0x88fe,

			//internalformat_sample_query
			gl_multisamples_nv = 0x9371,
			gl_supersample_scale_x_nv = 0x9372,
			gl_supersample_scale_y_nv = 0x9373,
			gl_conformant_nv = 0x9374,

			//light_max_exponent
			gl_max_shininess_nv = 0x8504,
			gl_max_spot_exponent_nv = 0x8505,

			//multisample_coverage
			//gl_color_samples_nv = 0x8e20,

			//multisample_filter_hint
			gl_multisample_filter_hint_nv = 0x8534,

			//non_square_matrices
			gl_float_mat2x3_nv = 0x8b65,
			gl_float_mat2x4_nv = 0x8b66,
			gl_float_mat3x2_nv = 0x8b67,
			gl_float_mat3x4_nv = 0x8b68,
			gl_float_mat4x2_nv = 0x8b69,
			gl_float_mat4x3_nv = 0x8b6a,

			//occlusion_query
			gl_pixel_counter_bits_nv = 0x8864,
			gl_current_occlusion_query_id_nv = 0x8865,
			gl_pixel_count_nv = 0x8866,
			gl_pixel_count_available_nv = 0x8867,

			//pack_subimage
			gl_pack_row_length_nv = 0x0d02,
			gl_pack_skip_rows_nv = 0x0d03,
			gl_pack_skip_pixels_nv = 0x0d04,

			//packed_depth_stencil
			gl_depth_stencil_nv = 0x84f9,
			gl_unsigned_int_24_8_nv = 0x84fa,

			//packed_float
			gl_r11f_g11f_b10f_nv = 0x8c3a,
			gl_unsigned_int_10f_11f_11f_rev_nv = 0x8c3b,

			//packed_float_linear
			//gl_r11f_g11f_b10f_nv = 0x8c3a,
			//gl_unsigned_int_10f_11f_11f_rev_nv = 0x8c3b,

			//parameter_buffer_object
			gl_max_program_parameter_buffer_bindings_nv = 0x8da0,
			gl_max_program_parameter_buffer_size_nv = 0x8da1,
			gl_vertex_program_parameter_buffer_nv = 0x8da2,
			gl_geometry_program_parameter_buffer_nv = 0x8da3,
			gl_fragment_program_parameter_buffer_nv = 0x8da4,

			//path_rendering
			gl_close_path_nv = 0x00,
			gl_bold_bit_nv = 0x01,
			gl_glyph_width_bit_nv = 0x01,
			gl_glyph_height_bit_nv = 0x02,
			gl_italic_bit_nv = 0x02,
			gl_move_to_nv = 0x02,
			gl_relative_move_to_nv = 0x03,
			gl_glyph_horizontal_bearing_x_bit_nv = 0x04,
			gl_line_to_nv = 0x04,
			gl_relative_line_to_nv = 0x05,
			gl_horizontal_line_to_nv = 0x06,
			gl_relative_horizontal_line_to_nv = 0x07,
			gl_glyph_horizontal_bearing_y_bit_nv = 0x08,
			gl_vertical_line_to_nv = 0x08,
			gl_relative_vertical_line_to_nv = 0x09,
			gl_quadratic_curve_to_nv = 0x0a,
			gl_relative_quadratic_curve_to_nv = 0x0b,
			gl_cubic_curve_to_nv = 0x0c,
			gl_relative_cubic_curve_to_nv = 0x0d,
			gl_smooth_quadratic_curve_to_nv = 0x0e,
			gl_relative_smooth_quadratic_curve_to_nv = 0x0f,
			gl_glyph_horizontal_bearing_advance_bit_nv = 0x10,
			gl_smooth_cubic_curve_to_nv = 0x10,
			gl_relative_smooth_cubic_curve_to_nv = 0x11,
			gl_small_ccw_arc_to_nv = 0x12,
			gl_relative_small_ccw_arc_to_nv = 0x13,
			gl_small_cw_arc_to_nv = 0x14,
			gl_relative_small_cw_arc_to_nv = 0x15,
			gl_large_ccw_arc_to_nv = 0x16,
			gl_relative_large_ccw_arc_to_nv = 0x17,
			gl_large_cw_arc_to_nv = 0x18,
			gl_relative_large_cw_arc_to_nv = 0x19,
			gl_conic_curve_to_nv = 0x1a,
			gl_relative_conic_curve_to_nv = 0x1b,
			gl_glyph_vertical_bearing_x_bit_nv = 0x20,
			gl_glyph_vertical_bearing_y_bit_nv = 0x40,
			gl_glyph_vertical_bearing_advance_bit_nv = 0x80,
			gl_rounded_rect_nv = 0xe8,
			gl_relative_rounded_rect_nv = 0xe9,
			gl_rounded_rect2_nv = 0xea,
			gl_relative_rounded_rect2_nv = 0xeb,
			gl_rounded_rect4_nv = 0xec,
			gl_relative_rounded_rect4_nv = 0xed,
			gl_rounded_rect8_nv = 0xee,
			gl_relative_rounded_rect8_nv = 0xef,
			gl_restart_path_nv = 0xf0,
			gl_dup_first_cubic_curve_to_nv = 0xf2,
			gl_dup_last_cubic_curve_to_nv = 0xf4,
			gl_rect_nv = 0xf6,
			gl_relative_rect_nv = 0xf7,
			gl_circular_ccw_arc_to_nv = 0xf8,
			gl_circular_cw_arc_to_nv = 0xfa,
			gl_circular_tangent_arc_to_nv = 0xfc,
			gl_arc_to_nv = 0xfe,
			gl_relative_arc_to_nv = 0xff,
			gl_glyph_has_kerning_bit_nv = 0x100,
			gl_primary_color_nv = 0x852c,
			gl_secondary_color_nv = 0x852d,
			//gl_primary_color = 0x8577,
			gl_path_format_svg_nv = 0x9070,
			gl_path_format_ps_nv = 0x9071,
			gl_standard_font_name_nv = 0x9072,
			gl_system_font_name_nv = 0x9073,
			gl_file_name_nv = 0x9074,
			gl_path_stroke_width_nv = 0x9075,
			gl_path_end_caps_nv = 0x9076,
			gl_path_initial_end_cap_nv = 0x9077,
			gl_path_terminal_end_cap_nv = 0x9078,
			gl_path_join_style_nv = 0x9079,
			gl_path_miter_limit_nv = 0x907a,
			gl_path_dash_caps_nv = 0x907b,
			gl_path_initial_dash_cap_nv = 0x907c,
			gl_path_terminal_dash_cap_nv = 0x907d,
			gl_path_dash_offset_nv = 0x907e,
			gl_path_client_length_nv = 0x907f,
			gl_path_fill_mode_nv = 0x9080,
			gl_path_fill_mask_nv = 0x9081,
			gl_path_fill_cover_mode_nv = 0x9082,
			gl_path_stroke_cover_mode_nv = 0x9083,
			gl_path_stroke_mask_nv = 0x9084,
			gl_path_stroke_bound_nv = 0x9086,
			gl_count_up_nv = 0x9088,
			gl_count_down_nv = 0x9089,
			gl_path_object_bounding_box_nv = 0x908a,
			gl_convex_hull_nv = 0x908b,
			gl_bounding_box_nv = 0x908d,
			gl_translate_x_nv = 0x908e,
			gl_translate_y_nv = 0x908f,
			gl_translate_2d_nv = 0x9090,
			gl_translate_3d_nv = 0x9091,
			gl_affine_2d_nv = 0x9092,
			gl_affine_3d_nv = 0x9094,
			gl_transpose_affine_2d_nv = 0x9096,
			gl_transpose_affine_3d_nv = 0x9098,
			gl_utf8_nv = 0x909a,
			gl_utf16_nv = 0x909b,
			gl_bounding_box_of_bounding_boxes_nv = 0x909c,
			gl_path_command_count_nv = 0x909d,
			gl_path_coord_count_nv = 0x909e,
			gl_path_dash_array_count_nv = 0x909f,
			gl_path_computed_length_nv = 0x90a0,
			gl_path_fill_bounding_box_nv = 0x90a1,
			gl_path_stroke_bounding_box_nv = 0x90a2,
			gl_square_nv = 0x90a3,
			gl_round_nv = 0x90a4,
			gl_triangular_nv = 0x90a5,
			gl_bevel_nv = 0x90a6,
			gl_miter_revert_nv = 0x90a7,
			gl_miter_truncate_nv = 0x90a8,
			gl_skip_missing_glyph_nv = 0x90a9,
			gl_use_missing_glyph_nv = 0x90aa,
			gl_path_error_position_nv = 0x90ab,
			gl_path_fog_gen_mode_nv = 0x90ac,
			gl_accum_adjacent_pairs_nv = 0x90ad,
			gl_adjacent_pairs_nv = 0x90ae,
			gl_first_to_rest_nv = 0x90af,
			gl_path_gen_mode_nv = 0x90b0,
			gl_path_gen_coeff_nv = 0x90b1,
			gl_path_gen_color_format_nv = 0x90b2,
			gl_path_gen_components_nv = 0x90b3,
			gl_path_dash_offset_reset_nv = 0x90b4,
			gl_move_to_resets_nv = 0x90b5,
			gl_move_to_continues_nv = 0x90b6,
			gl_path_stencil_func_nv = 0x90b7,
			gl_path_stencil_ref_nv = 0x90b8,
			gl_path_stencil_value_mask_nv = 0x90b9,
			gl_path_stencil_depth_offset_factor_nv = 0x90bd,
			gl_path_stencil_depth_offset_units_nv = 0x90be,
			gl_path_cover_depth_func_nv = 0x90bf,
			gl_font_glyphs_available_nv = 0x9368,
			gl_font_target_unavailable_nv = 0x9369,
			gl_font_unavailable_nv = 0x936a,
			gl_font_unintelligible_nv = 0x936b,
			gl_standard_font_format_nv = 0x936c,
			gl_fragment_input_nv = 0x936d,
			gl_font_x_min_bounds_bit_nv = 0x00010000,
			gl_font_y_min_bounds_bit_nv = 0x00020000,
			gl_font_x_max_bounds_bit_nv = 0x00040000,
			gl_font_y_max_bounds_bit_nv = 0x00080000,
			gl_font_units_per_em_bit_nv = 0x00100000,
			gl_font_ascender_bit_nv = 0x00200000,
			gl_font_descender_bit_nv = 0x00400000,
			gl_font_height_bit_nv = 0x00800000,
			gl_font_max_advance_width_bit_nv = 0x01000000,
			gl_font_max_advance_height_bit_nv = 0x02000000,
			gl_font_underline_position_bit_nv = 0x04000000,
			gl_font_underline_thickness_bit_nv = 0x08000000,
			gl_font_has_kerning_bit_nv = 0x10000000,
			gl_font_num_glyph_indices_bit_nv = 0x20000000,

			//path_rendering_shared_edge
			gl_shared_edge_nv = 0xc0,

			//pixel_buffer_object
			gl_pixel_pack_buffer_nv = 0x88eb,
			gl_pixel_unpack_buffer_nv = 0x88ec,
			gl_pixel_pack_buffer_binding_nv = 0x88ed,
			gl_pixel_unpack_buffer_binding_nv = 0x88ef,

			//pixel_data_range
			gl_write_pixel_data_range_nv = 0x8878,
			gl_read_pixel_data_range_nv = 0x8879,
			gl_write_pixel_data_range_length_nv = 0x887a,
			gl_read_pixel_data_range_length_nv = 0x887b,
			gl_write_pixel_data_range_pointer_nv = 0x887c,
			gl_read_pixel_data_range_pointer_nv = 0x887d,

			//point_sprite
			gl_point_sprite_nv = 0x8861,
			gl_coord_replace_nv = 0x8862,
			gl_point_sprite_r_mode_nv = 0x8863,

			//polygon_mode
			gl_polygon_mode_nv = 0x0b40,
			gl_point_nv = 0x1b00,
			gl_line_nv = 0x1b01,
			gl_fill_nv = 0x1b02,
			gl_polygon_offset_point_nv = 0x2a01,
			gl_polygon_offset_line_nv = 0x2a02,

			//present_video
			gl_frame_nv = 0x8e26,
			gl_fields_nv = 0x8e27,
			gl_current_time_nv = 0x8e28,
			gl_num_fill_streams_nv = 0x8e29,
			gl_present_time_nv = 0x8e2a,
			gl_present_duration_nv = 0x8e2b,

			//primitive_restart
			gl_primitive_restart_nv = 0x8558,
			gl_primitive_restart_index_nv = 0x8559,

			//register_combiners
			gl_register_combiners_nv = 0x8522,
			gl_variable_a_nv = 0x8523,
			gl_variable_b_nv = 0x8524,
			gl_variable_c_nv = 0x8525,
			gl_variable_d_nv = 0x8526,
			gl_variable_e_nv = 0x8527,
			gl_variable_f_nv = 0x8528,
			gl_variable_g_nv = 0x8529,
			gl_constant_color0_nv = 0x852a,
			gl_constant_color1_nv = 0x852b,
			//gl_primary_color_nv = 0x852c,
			//gl_secondary_color_nv = 0x852d,
			gl_spare0_nv = 0x852e,
			gl_spare1_nv = 0x852f,
			gl_discard_nv = 0x8530,
			gl_e_times_f_nv = 0x8531,
			gl_spare0_plus_secondary_color_nv = 0x8532,
			gl_unsigned_identity_nv = 0x8536,
			gl_unsigned_invert_nv = 0x8537,
			gl_expand_normal_nv = 0x8538,
			gl_expand_negate_nv = 0x8539,
			gl_half_bias_normal_nv = 0x853a,
			gl_half_bias_negate_nv = 0x853b,
			gl_signed_identity_nv = 0x853c,
			gl_signed_negate_nv = 0x853d,
			gl_scale_by_two_nv = 0x853e,
			gl_scale_by_four_nv = 0x853f,
			gl_scale_by_one_half_nv = 0x8540,
			gl_bias_by_negative_one_half_nv = 0x8541,
			gl_combiner_input_nv = 0x8542,
			gl_combiner_mapping_nv = 0x8543,
			gl_combiner_component_usage_nv = 0x8544,
			gl_combiner_ab_dot_product_nv = 0x8545,
			gl_combiner_cd_dot_product_nv = 0x8546,
			gl_combiner_mux_sum_nv = 0x8547,
			gl_combiner_scale_nv = 0x8548,
			gl_combiner_bias_nv = 0x8549,
			gl_combiner_ab_output_nv = 0x854a,
			gl_combiner_cd_output_nv = 0x854b,
			gl_combiner_sum_output_nv = 0x854c,
			gl_max_general_combiners_nv = 0x854d,
			gl_num_general_combiners_nv = 0x854e,
			gl_color_sum_clamp_nv = 0x854f,
			gl_combiner0_nv = 0x8550,
			gl_combiner1_nv = 0x8551,
			gl_combiner2_nv = 0x8552,
			gl_combiner3_nv = 0x8553,
			gl_combiner4_nv = 0x8554,
			gl_combiner5_nv = 0x8555,
			gl_combiner6_nv = 0x8556,
			gl_combiner7_nv = 0x8557,

			//register_combiners2
			gl_per_stage_constants_nv = 0x8535,

			//robustness_video_memory_purge
			//gl_egl_generate_reset_on_video_memory_purge_nv = 0x334c,
			//gl_purged_context_reset_nv = 0x92bb,

			//srgb_formats
			gl_etc1_srgb8_nv = 0x88ee,
			gl_srgb8_nv = 0x8c41,
			gl_sluminance_alpha_nv = 0x8c44,
			gl_sluminance8_alpha8_nv = 0x8c45,
			gl_sluminance_nv = 0x8c46,
			gl_sluminance8_nv = 0x8c47,
			gl_compressed_srgb_s3tc_dxt1_nv = 0x8c4c,
			gl_compressed_srgb_alpha_s3tc_dxt1_nv = 0x8c4d,
			gl_compressed_srgb_alpha_s3tc_dxt3_nv = 0x8c4e,
			gl_compressed_srgb_alpha_s3tc_dxt5_nv = 0x8c4f,

			//sample_locations
			gl_sample_location_nv = 0x8e50,
			gl_sample_location_subpixel_bits_nv = 0x933d,
			gl_sample_location_pixel_grid_width_nv = 0x933e,
			gl_sample_location_pixel_grid_height_nv = 0x933f,
			gl_programmable_sample_location_table_size_nv = 0x9340,
			gl_programmable_sample_location_nv = 0x9341,
			gl_framebuffer_programmable_sample_locations_nv = 0x9342,
			gl_framebuffer_sample_location_pixel_grid_nv = 0x9343,

			//shader_buffer_load
			gl_buffer_gpu_address_nv = 0x8f1d,
			gl_gpu_address_nv = 0x8f34,
			gl_max_shader_buffer_address_nv = 0x8f35,

			//shader_thread_group
			gl_warp_size_nv = 0x9339,
			gl_warps_per_sm_nv = 0x933a,
			gl_sm_count_nv = 0x933b,

			//shadow_samplers_array
			gl_sampler_2d_array_shadow_nv = 0x8dc4,

			//shadow_samplers_cube
			gl_sampler_cube_shadow_nv = 0x8dc5,

			//tessellation_program5
			gl_max_program_patch_attribs_nv = 0x86d8,
			gl_tess_control_program_nv = 0x891e,
			gl_tess_evaluation_program_nv = 0x891f,
			gl_tess_control_program_parameter_buffer_nv = 0x8c74,
			gl_tess_evaluation_program_parameter_buffer_nv = 0x8c75,

			//texgen_emboss
			gl_emboss_light_nv = 0x855d,
			gl_emboss_constant_nv = 0x855e,
			gl_emboss_map_nv = 0x855f,

			//texgen_reflection
			gl_normal_map_nv = 0x8511,
			gl_reflection_map_nv = 0x8512,

			//texture_array
			gl_unpack_skip_images_nv = 0x806d,
			gl_unpack_image_height_nv = 0x806e,
			gl_max_array_texture_layers_nv = 0x88ff,
			gl_texture_2d_array_nv = 0x8c1a,
			gl_texture_binding_2d_array_nv = 0x8c1d,
			gl_framebuffer_attachment_texture_layer_nv = 0x8cd4,
			gl_sampler_2d_array_nv = 0x8dc1,

			//texture_border_clamp
			gl_texture_border_color_nv = 0x1004,
			gl_clamp_to_border_nv = 0x812d,

			//texture_compression_latc
			gl_compressed_luminance_latc1_nv = 0x8c70,
			gl_compressed_signed_luminance_latc1_nv = 0x8c71,
			gl_compressed_luminance_alpha_latc2_nv = 0x8c72,
			gl_compressed_signed_luminance_alpha_latc2_nv = 0x8c73,

			//texture_compression_s3tc
			gl_compressed_rgb_s3tc_dxt1_nv = 0x83f0,
			gl_compressed_rgba_s3tc_dxt1_nv = 0x83f1,
			gl_compressed_rgba_s3tc_dxt3_nv = 0x83f2,
			gl_compressed_rgba_s3tc_dxt5_nv = 0x83f3,

			//texture_env_combine4
			gl_combine4_nv = 0x8503,
			gl_source3_rgb_nv = 0x8583,
			gl_source3_alpha_nv = 0x858b,
			gl_operand3_rgb_nv = 0x8593,
			gl_operand3_alpha_nv = 0x859b,

			//texture_expand_normal
			gl_texture_unsigned_remap_mode_nv = 0x888f,

			//texture_multisample
			gl_texture_coverage_samples_nv = 0x9045,
			gl_texture_color_samples_nv = 0x9046,

			//texture_rectangle
			gl_texture_rectangle_nv = 0x84f5,
			gl_texture_binding_rectangle_nv = 0x84f6,
			gl_proxy_texture_rectangle_nv = 0x84f7,
			gl_max_rectangle_texture_size_nv = 0x84f8,

			//texture_shader
			gl_offset_texture_rectangle_nv = 0x864c,
			gl_offset_texture_rectangle_scale_nv = 0x864d,
			gl_dot_product_texture_rectangle_nv = 0x864e,
			gl_rgba_unsigned_dot_product_mapping_nv = 0x86d9,
			gl_unsigned_int_s8_s8_8_8_nv = 0x86da,
			gl_unsigned_int_8_8_s8_s8_rev_nv = 0x86db,
			gl_dsdt_mag_intensity_nv = 0x86dc,
			gl_shader_consistent_nv = 0x86dd,
			gl_texture_shader_nv = 0x86de,
			gl_shader_operation_nv = 0x86df,
			gl_cull_modes_nv = 0x86e0,
			gl_offset_texture_2d_matrix_nv = 0x86e1,
			gl_offset_texture_matrix_nv = 0x86e1,
			gl_offset_texture_2d_scale_nv = 0x86e2,
			gl_offset_texture_scale_nv = 0x86e2,
			gl_offset_texture_2d_bias_nv = 0x86e3,
			gl_offset_texture_bias_nv = 0x86e3,
			gl_previous_texture_input_nv = 0x86e4,
			gl_const_eye_nv = 0x86e5,
			gl_pass_through_nv = 0x86e6,
			gl_cull_fragment_nv = 0x86e7,
			gl_offset_texture_2d_nv = 0x86e8,
			gl_dependent_ar_texture_2d_nv = 0x86e9,
			gl_dependent_gb_texture_2d_nv = 0x86ea,
			gl_dot_product_nv = 0x86ec,
			gl_dot_product_depth_replace_nv = 0x86ed,
			gl_dot_product_texture_2d_nv = 0x86ee,
			gl_dot_product_texture_cube_map_nv = 0x86f0,
			gl_dot_product_diffuse_cube_map_nv = 0x86f1,
			gl_dot_product_reflect_cube_map_nv = 0x86f2,
			gl_dot_product_const_eye_reflect_cube_map_nv = 0x86f3,
			gl_hilo_nv = 0x86f4,
			gl_dsdt_nv = 0x86f5,
			gl_dsdt_mag_nv = 0x86f6,
			gl_dsdt_mag_vib_nv = 0x86f7,
			gl_hilo16_nv = 0x86f8,
			gl_signed_hilo_nv = 0x86f9,
			gl_signed_hilo16_nv = 0x86fa,
			gl_signed_rgba_nv = 0x86fb,
			gl_signed_rgba8_nv = 0x86fc,
			gl_signed_rgb_nv = 0x86fe,
			gl_signed_rgb8_nv = 0x86ff,
			gl_signed_luminance_nv = 0x8701,
			gl_signed_luminance8_nv = 0x8702,
			gl_signed_luminance_alpha_nv = 0x8703,
			gl_signed_luminance8_alpha8_nv = 0x8704,
			gl_signed_alpha_nv = 0x8705,
			gl_signed_alpha8_nv = 0x8706,
			gl_signed_intensity_nv = 0x8707,
			gl_signed_intensity8_nv = 0x8708,
			gl_dsdt8_nv = 0x8709,
			gl_dsdt8_mag8_nv = 0x870a,
			gl_dsdt8_mag8_intensity8_nv = 0x870b,
			gl_signed_rgb_unsigned_alpha_nv = 0x870c,
			gl_signed_rgb8_unsigned_alpha8_nv = 0x870d,
			gl_hi_scale_nv = 0x870e,
			gl_lo_scale_nv = 0x870f,
			gl_ds_scale_nv = 0x8710,
			gl_dt_scale_nv = 0x8711,
			gl_magnitude_scale_nv = 0x8712,
			gl_vibrance_scale_nv = 0x8713,
			gl_hi_bias_nv = 0x8714,
			gl_lo_bias_nv = 0x8715,
			gl_ds_bias_nv = 0x8716,
			gl_dt_bias_nv = 0x8717,
			gl_magnitude_bias_nv = 0x8718,
			gl_vibrance_bias_nv = 0x8719,
			gl_texture_border_values_nv = 0x871a,
			gl_texture_hi_size_nv = 0x871b,
			gl_texture_lo_size_nv = 0x871c,
			gl_texture_ds_size_nv = 0x871d,
			gl_texture_dt_size_nv = 0x871e,
			gl_texture_mag_size_nv = 0x871f,

			//texture_shader2
			//gl_unsigned_int_s8_s8_8_8_nv = 0x86da,
			//gl_unsigned_int_8_8_s8_s8_rev_nv = 0x86db,
			//gl_dsdt_mag_intensity_nv = 0x86dc,
			gl_dot_product_texture_3d_nv = 0x86ef,
			/*gl_hilo_nv = 0x86f4,
			gl_dsdt_nv = 0x86f5,
			gl_dsdt_mag_nv = 0x86f6,
			gl_dsdt_mag_vib_nv = 0x86f7,
			gl_hilo16_nv = 0x86f8,
			gl_signed_hilo_nv = 0x86f9,
			gl_signed_hilo16_nv = 0x86fa,
			gl_signed_rgba_nv = 0x86fb,
			gl_signed_rgba8_nv = 0x86fc,
			gl_signed_rgb_nv = 0x86fe,
			gl_signed_rgb8_nv = 0x86ff,
			gl_signed_luminance_nv = 0x8701,
			gl_signed_luminance8_nv = 0x8702,
			gl_signed_luminance_alpha_nv = 0x8703,
			gl_signed_luminance8_alpha8_nv = 0x8704,
			gl_signed_alpha_nv = 0x8705,
			gl_signed_alpha8_nv = 0x8706,
			gl_signed_intensity_nv = 0x8707,
			gl_signed_intensity8_nv = 0x8708,
			gl_dsdt8_nv = 0x8709,
			gl_dsdt8_mag8_nv = 0x870a,
			gl_dsdt8_mag8_intensity8_nv = 0x870b,
			gl_signed_rgb_unsigned_alpha_nv = 0x870c,
			gl_signed_rgb8_unsigned_alpha8_nv = 0x870d,*/

			//texture_shader3
			gl_offset_projective_texture_2d_nv = 0x8850,
			gl_offset_projective_texture_2d_scale_nv = 0x8851,
			gl_offset_projective_texture_rectangle_nv = 0x8852,
			gl_offset_projective_texture_rectangle_scale_nv = 0x8853,
			gl_offset_hilo_texture_2d_nv = 0x8854,
			gl_offset_hilo_texture_rectangle_nv = 0x8855,
			gl_offset_hilo_projective_texture_2d_nv = 0x8856,
			gl_offset_hilo_projective_texture_rectangle_nv = 0x8857,
			gl_dependent_hilo_texture_2d_nv = 0x8858,
			gl_dependent_rgb_texture_3d_nv = 0x8859,
			gl_dependent_rgb_texture_cube_map_nv = 0x885a,
			gl_dot_product_pass_through_nv = 0x885b,
			gl_dot_product_texture_1d_nv = 0x885c,
			gl_dot_product_affine_depth_replace_nv = 0x885d,
			gl_hilo8_nv = 0x885e,
			gl_signed_hilo8_nv = 0x885f,
			gl_force_blue_to_one_nv = 0x8860,

			//transform_feedback
			gl_back_primary_color_nv = 0x8c77,
			gl_back_secondary_color_nv = 0x8c78,
			gl_texture_coord_nv = 0x8c79,
			gl_clip_distance_nv = 0x8c7a,
			gl_vertex_id_nv = 0x8c7b,
			gl_primitive_id_nv = 0x8c7c,
			gl_generic_attrib_nv = 0x8c7d,
			gl_transform_feedback_attribs_nv = 0x8c7e,
			gl_transform_feedback_buffer_mode_nv = 0x8c7f,
			gl_max_transform_feedback_separate_components_nv = 0x8c80,
			gl_active_varyings_nv = 0x8c81,
			gl_active_varying_max_length_nv = 0x8c82,
			gl_transform_feedback_varyings_nv = 0x8c83,
			gl_transform_feedback_buffer_start_nv = 0x8c84,
			gl_transform_feedback_buffer_size_nv = 0x8c85,
			gl_transform_feedback_record_nv = 0x8c86,
			gl_primitives_generated_nv = 0x8c87,
			gl_transform_feedback_primitives_written_nv = 0x8c88,
			gl_rasterizer_discard_nv = 0x8c89,
			gl_max_transform_feedback_interleaved_components_nv = 0x8c8a,
			gl_max_transform_feedback_separate_attribs_nv = 0x8c8b,
			gl_interleaved_attribs_nv = 0x8c8c,
			gl_separate_attribs_nv = 0x8c8d,
			gl_transform_feedback_buffer_nv = 0x8c8e,
			gl_transform_feedback_buffer_binding_nv = 0x8c8f,

			//transform_feedback2
			gl_transform_feedback_nv = 0x8e22,
			gl_transform_feedback_buffer_paused_nv = 0x8e23,
			gl_transform_feedback_buffer_active_nv = 0x8e24,
			gl_transform_feedback_binding_nv = 0x8e25,

			//uniform_buffer_unified_memory
			gl_uniform_buffer_unified_nv = 0x936e,
			gl_uniform_buffer_address_nv = 0x936f,
			gl_uniform_buffer_length_nv = 0x9370,

			//vdpau_interop
			gl_surface_state_nv = 0x86eb,
			gl_surface_registered_nv = 0x86fd,
			gl_surface_mapped_nv = 0x8700,
			gl_write_discard_nv = 0x88be,

			//vertex_array_range
			gl_vertex_array_range_nv = 0x851d,
			gl_vertex_array_range_length_nv = 0x851e,
			gl_vertex_array_range_valid_nv = 0x851f,
			gl_max_vertex_array_range_element_nv = 0x8520,
			gl_vertex_array_range_pointer_nv = 0x8521,

			//vertex_array_range2
			gl_vertex_array_range_without_flush_nv = 0x8533,

			//vertex_attrib_integer_64bit
			//gl_int64_nv = 0x140e,
			//gl_unsigned_int64_nv = 0x140f,

			//vertex_buffer_unified_memory
			gl_vertex_attrib_array_unified_nv = 0x8f1e,
			gl_element_array_unified_nv = 0x8f1f,
			gl_vertex_attrib_array_address_nv = 0x8f20,
			gl_vertex_array_address_nv = 0x8f21,
			gl_normal_array_address_nv = 0x8f22,
			gl_color_array_address_nv = 0x8f23,
			gl_index_array_address_nv = 0x8f24,
			gl_texture_coord_array_address_nv = 0x8f25,
			gl_edge_flag_array_address_nv = 0x8f26,
			gl_secondary_color_array_address_nv = 0x8f27,
			gl_fog_coord_array_address_nv = 0x8f28,
			gl_element_array_address_nv = 0x8f29,
			gl_vertex_attrib_array_length_nv = 0x8f2a,
			gl_vertex_array_length_nv = 0x8f2b,
			gl_normal_array_length_nv = 0x8f2c,
			gl_color_array_length_nv = 0x8f2d,
			gl_index_array_length_nv = 0x8f2e,
			gl_texture_coord_array_length_nv = 0x8f2f,
			gl_edge_flag_array_length_nv = 0x8f30,
			gl_secondary_color_array_length_nv = 0x8f31,
			gl_fog_coord_array_length_nv = 0x8f32,
			gl_element_array_length_nv = 0x8f33,
			gl_draw_indirect_unified_nv = 0x8f40,
			gl_draw_indirect_address_nv = 0x8f41,
			gl_draw_indirect_length_nv = 0x8f42,

			//vertex_program
			gl_vertex_program_nv = 0x8620,
			gl_vertex_state_program_nv = 0x8621,
			gl_attrib_array_size_nv = 0x8623,
			gl_attrib_array_stride_nv = 0x8624,
			gl_attrib_array_type_nv = 0x8625,
			gl_current_attrib_nv = 0x8626,
			gl_program_length_nv = 0x8627,
			gl_program_string_nv = 0x8628,
			gl_modelview_projection_nv = 0x8629,
			gl_identity_nv = 0x862a,
			gl_inverse_nv = 0x862b,
			gl_transpose_nv = 0x862c,
			gl_inverse_transpose_nv = 0x862d,
			gl_max_track_matrix_stack_depth_nv = 0x862e,
			gl_max_track_matrices_nv = 0x862f,
			gl_matrix0_nv = 0x8630,
			gl_matrix1_nv = 0x8631,
			gl_matrix2_nv = 0x8632,
			gl_matrix3_nv = 0x8633,
			gl_matrix4_nv = 0x8634,
			gl_matrix5_nv = 0x8635,
			gl_matrix6_nv = 0x8636,
			gl_matrix7_nv = 0x8637,
			gl_current_matrix_stack_depth_nv = 0x8640,
			gl_current_matrix_nv = 0x8641,
			gl_vertex_program_point_size_nv = 0x8642,
			gl_vertex_program_two_side_nv = 0x8643,
			gl_program_parameter_nv = 0x8644,
			gl_attrib_array_pointer_nv = 0x8645,
			gl_program_target_nv = 0x8646,
			gl_program_resident_nv = 0x8647,
			gl_track_matrix_nv = 0x8648,
			gl_track_matrix_transform_nv = 0x8649,
			gl_vertex_program_binding_nv = 0x864a,
			gl_program_error_position_nv = 0x864b,
			gl_vertex_attrib_array0_nv = 0x8650,
			gl_vertex_attrib_array1_nv = 0x8651,
			gl_vertex_attrib_array2_nv = 0x8652,
			gl_vertex_attrib_array3_nv = 0x8653,
			gl_vertex_attrib_array4_nv = 0x8654,
			gl_vertex_attrib_array5_nv = 0x8655,
			gl_vertex_attrib_array6_nv = 0x8656,
			gl_vertex_attrib_array7_nv = 0x8657,
			gl_vertex_attrib_array8_nv = 0x8658,
			gl_vertex_attrib_array9_nv = 0x8659,
			gl_vertex_attrib_array10_nv = 0x865a,
			gl_vertex_attrib_array11_nv = 0x865b,
			gl_vertex_attrib_array12_nv = 0x865c,
			gl_vertex_attrib_array13_nv = 0x865d,
			gl_vertex_attrib_array14_nv = 0x865e,
			gl_vertex_attrib_array15_nv = 0x865f,
			gl_map1_vertex_attrib0_4_nv = 0x8660,
			gl_map1_vertex_attrib1_4_nv = 0x8661,
			gl_map1_vertex_attrib2_4_nv = 0x8662,
			gl_map1_vertex_attrib3_4_nv = 0x8663,
			gl_map1_vertex_attrib4_4_nv = 0x8664,
			gl_map1_vertex_attrib5_4_nv = 0x8665,
			gl_map1_vertex_attrib6_4_nv = 0x8666,
			gl_map1_vertex_attrib7_4_nv = 0x8667,
			gl_map1_vertex_attrib8_4_nv = 0x8668,
			gl_map1_vertex_attrib9_4_nv = 0x8669,
			gl_map1_vertex_attrib10_4_nv = 0x866a,
			gl_map1_vertex_attrib11_4_nv = 0x866b,
			gl_map1_vertex_attrib12_4_nv = 0x866c,
			gl_map1_vertex_attrib13_4_nv = 0x866d,
			gl_map1_vertex_attrib14_4_nv = 0x866e,
			gl_map1_vertex_attrib15_4_nv = 0x866f,
			gl_map2_vertex_attrib0_4_nv = 0x8670,
			gl_map2_vertex_attrib1_4_nv = 0x8671,
			gl_map2_vertex_attrib2_4_nv = 0x8672,
			gl_map2_vertex_attrib3_4_nv = 0x8673,
			gl_map2_vertex_attrib4_4_nv = 0x8674,
			gl_map2_vertex_attrib5_4_nv = 0x8675,
			gl_map2_vertex_attrib6_4_nv = 0x8676,
			gl_map2_vertex_attrib7_4_nv = 0x8677,
			gl_map2_vertex_attrib8_4_nv = 0x8678,
			gl_map2_vertex_attrib9_4_nv = 0x8679,
			gl_map2_vertex_attrib10_4_nv = 0x867a,
			gl_map2_vertex_attrib11_4_nv = 0x867b,
			gl_map2_vertex_attrib12_4_nv = 0x867c,
			gl_map2_vertex_attrib13_4_nv = 0x867d,
			gl_map2_vertex_attrib14_4_nv = 0x867e,
			gl_map2_vertex_attrib15_4_nv = 0x867f,

			//vertex_program2_option
			/*gl_max_program_exec_instructions_nv = 0x88f4,
			gl_max_program_call_depth_nv = 0x88f5,*/

			//vertex_program3
			max_vertex_texture_image_units_arb = 0x8b4c,

			//vertex_program4
			gl_vertex_attrib_array_integer_nv = 0x88fd,

			//video_capture
			gl_video_buffer_nv = 0x9020,
			gl_video_buffer_binding_nv = 0x9021,
			gl_field_upper_nv = 0x9022,
			gl_field_lower_nv = 0x9023,
			gl_num_video_capture_streams_nv = 0x9024,
			gl_next_video_capture_buffer_status_nv = 0x9025,
			gl_video_capture_to_422_supported_nv = 0x9026,
			gl_last_video_capture_status_nv = 0x9027,
			gl_video_buffer_pitch_nv = 0x9028,
			gl_video_color_conversion_matrix_nv = 0x9029,
			gl_video_color_conversion_max_nv = 0x902a,
			gl_video_color_conversion_min_nv = 0x902b,
			gl_video_color_conversion_offset_nv = 0x902c,
			gl_video_buffer_internal_format_nv = 0x902d,
			gl_partial_success_nv = 0x902e,
			gl_success_nv = 0x902f,
			gl_failure_nv = 0x9030,
			gl_ycbycr8_422_nv = 0x9031,
			gl_ycbaycr8a_4224_nv = 0x9032,
			gl_z6y10z6cb10z6y10z6cr10_422_nv = 0x9033,
			gl_z6y10z6cb10z6a10z6y10z6cr10z6a10_4224_nv = 0x9034,
			gl_z4y12z4cb12z4y12z4cr12_422_nv = 0x9035,
			gl_z4y12z4cb12z4a12z4y12z4cr12z4a12_4224_nv = 0x9036,
			gl_z4y12z4cb12z4cr12_444_nv = 0x9037,
			gl_video_capture_frame_width_nv = 0x9038,
			gl_video_capture_frame_height_nv = 0x9039,
			gl_video_capture_field_upper_height_nv = 0x903a,
			gl_video_capture_field_lower_height_nv = 0x903b,
			gl_video_capture_surface_origin_nv = 0x903c,

			//viewport_array
			/*gl_depth_range = 0x0b70,
			gl_viewport = 0x0ba2,
			gl_scissor_box = 0x0c10,
			gl_scissor_test = 0x0c11,*/
			gl_max_viewports_nv = 0x825b,
			gl_viewport_subpixel_bits_nv = 0x825c,
			gl_viewport_bounds_range_nv = 0x825d,
			gl_viewport_index_provoking_vertex_nv = 0x825f,

			//viewport_swizzle
			gl_viewport_swizzle_positive_x_nv = 0x9350,
			gl_viewport_swizzle_negative_x_nv = 0x9351,
			gl_viewport_swizzle_positive_y_nv = 0x9352,
			gl_viewport_swizzle_negative_y_nv = 0x9353,
			gl_viewport_swizzle_positive_z_nv = 0x9354,
			gl_viewport_swizzle_negative_z_nv = 0x9355,
			gl_viewport_swizzle_positive_w_nv = 0x9356,
			gl_viewport_swizzle_negative_w_nv = 0x9357,
			gl_viewport_swizzle_x_nv = 0x9358,
			gl_viewport_swizzle_y_nv = 0x9359,
			gl_viewport_swizzle_z_nv = 0x935a,
			gl_viewport_swizzle_w_nv = 0x935b,
		};

		//3dvision_settings
		void (*glStereoParameterfNV) (GLenum pname, GLfloat param) = nullptr;
		void (*glStereoParameteriNV) (GLenum pname, GLint param) = nullptr;
		bool NV_3dvision_settings = false;

		//EGL_stream_consumer_external
		bool NV_EGL_stream_consumer_external = false;

		//alpha_to_coverage_dither_control
		bool NV_alpha_to_coverage_dither_control = false;

		//bgr
		bool NV_bgr = false;

		//bindless_multi_draw_indirect
		void (*glMultiDrawArraysIndirectBindlessNV) (GLenum mode, const void* indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount) = nullptr;
		void (*glMultiDrawElementsIndirectBindlessNV) (GLenum mode, GLenum type, const void* indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount) = nullptr;
		bool NV_bindless_multi_draw_indirect = false;

		//bindless_multi_draw_indirect_count
		void (*glMultiDrawArraysIndirectBindlessCountNV) (GLenum mode, const void* indirect, GLintptr drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount) = nullptr;
		void (*glMultiDrawElementsIndirectBindlessCountNV) (GLenum mode, GLenum type, const void* indirect, GLintptr drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount) = nullptr;
		bool NV_bindless_multi_draw_indirect_count = false;

		//bindless_texture
		GLuint64(*glGetImageHandleNV) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format) = nullptr;
		GLuint64(*glGetTextureHandleNV) (GLuint texture) = nullptr;
		GLuint64(*glGetTextureSamplerHandleNV) (GLuint texture, GLuint sampler) = nullptr;
		GLboolean(*glIsImageHandleResidentNV) (GLuint64 handle) = nullptr;
		GLboolean(*glIsTextureHandleResidentNV) (GLuint64 handle) = nullptr;
		void (*glMakeImageHandleNonResidentNV) (GLuint64 handle) = nullptr;
		void (*glMakeImageHandleResidentNV) (GLuint64 handle, GLenum access) = nullptr;
		void (*glMakeTextureHandleNonResidentNV) (GLuint64 handle) = nullptr;
		void (*glMakeTextureHandleResidentNV) (GLuint64 handle) = nullptr;
		void (*glProgramUniformHandleui64NV) (GLuint program, GLint location, GLuint64 value) = nullptr;
		void (*glProgramUniformHandleui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64* values) = nullptr;
		void (*glUniformHandleui64NV) (GLint location, GLuint64 value) = nullptr;
		void (*glUniformHandleui64vNV) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
		bool NV_bindless_texture = false;
		
		//blend_equation_advanced
		void (*glBlendBarrierNV) (void) = nullptr;
		void (*glBlendParameteriNV) (GLenum pname, GLint value) = nullptr;
		bool NV_blend_equation_advanced = false;

		//blend_equation_advanced_coherent
		bool NV_blend_equation_advanced_coherent = false;

		//blend_minmax_factor
		bool NV_blend_minmax_factor = false;

		//blend_square
		bool NV_blend_square = false;

		//clip_space_w_scaling
		void (*glViewportPositionWScaleNV) (GLuint index, GLfloat xcoeff, GLfloat ycoeff) = nullptr;
		bool NV_clip_space_w_scaling = false;

		//command_list
		void (*glCallCommandListNV) (GLuint list) = nullptr;
		void (*glCommandListSegmentsNV) (GLuint list, GLuint segments) = nullptr;
		void (*glCompileCommandListNV) (GLuint list) = nullptr;
		void (*glCreateCommandListsNV) (GLsizei n, GLuint* lists) = nullptr;
		void (*glCreateStatesNV) (GLsizei n, GLuint* states) = nullptr;
		void (*glDeleteCommandListsNV) (GLsizei n, const GLuint* lists) = nullptr;
		void (*glDeleteStatesNV) (GLsizei n, const GLuint* states) = nullptr;
		void (*glDrawCommandsAddressNV) (GLenum primitiveMode, const GLuint64* indirects, const GLsizei* sizes, GLuint count) = nullptr;
		void (*glDrawCommandsNV) (GLenum primitiveMode, GLuint buffer, const GLintptr* indirects, const GLsizei* sizes, GLuint count) = nullptr;
		void (*glDrawCommandsStatesAddressNV) (const GLuint64* indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count) = nullptr;
		void (*glDrawCommandsStatesNV) (GLuint buffer, const GLintptr* indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count) = nullptr;
		GLuint(*glGetCommandHeaderNV) (GLenum tokenID, GLuint size) = nullptr;
		GLushort(*glGetStageIndexNV) (GLenum shadertype) = nullptr;
		GLboolean(*glIsCommandListNV) (GLuint list) = nullptr;
		GLboolean(*glIsStateNV) (GLuint state) = nullptr;
		void (*glListDrawCommandsStatesClientNV) (GLuint list, GLuint segment, const void** indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count) = nullptr;
		void (*glStateCaptureNV) (GLuint state, GLenum mode) = nullptr;
		bool NV_command_list = false;

		//compute_program5
		bool NV_compute_program5 = false;

		//conditional_render
		void (*glBeginConditionalRenderNV) (GLuint id, GLenum mode) = nullptr;
		void (*glEndConditionalRenderNV) (void) = nullptr;
		bool NV_conditional_render = false;

		//conservative_raster
		void (*glSubpixelPrecisionBiasNV) (GLuint xbits, GLuint ybits) = nullptr;
		bool NV_conservative_raster = false;

		//conservative_raster_dilate
		void (*glConservativeRasterParameterfNV) (GLenum pname, GLfloat value) = nullptr;
		bool NV_conservative_raster_dilate = false;

		//conservative_raster_pre_snap_triangles
		void (*glConservativeRasterParameteriNV) (GLenum pname, GLint param) = nullptr;
		bool NV_conservative_raster_pre_snap_triangles = false;

		//copy_buffer
		void (*glCopyBufferSubDataNV) (GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size) = nullptr;
		bool NV_copy_buffer = false;

		//copy_depth_to_color
		bool NV_copy_depth_to_color = false;

		//copy_image
		void (*glCopyImageSubDataNV) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
		bool NV_copy_image = false;		

		//deep_texture3D
		bool NV_deep_texture3D = false;

		//depth_buffer_float
		void (*glClearDepthdNV) (GLdouble depth) = nullptr;
		void (*glDepthBoundsdNV) (GLdouble zmin, GLdouble zmax) = nullptr;
		void (*glDepthRangedNV) (GLdouble zNear, GLdouble zFar) = nullptr;
		bool NV_depth_buffer_float = false;

		//depth_clamp
		bool NV_depth_clamp = false;

		//depth_range_unclamped
		bool NV_depth_range_unclamped = false;

		//draw_buffers
		void (*glDrawBuffersNV) (GLsizei n, const GLenum * bufs) = nullptr;
		bool NV_draw_buffers = false;

		//draw_instanced
		void (*glDrawArraysInstancedNV) (GLenum mode, GLint first, GLsizei count, GLsizei primcount) = nullptr;
		void (*glDrawElementsInstancedNV) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) = nullptr;
		bool NV_draw_instanced = false;

		//draw_texture
		void (*glDrawTextureNV) (GLuint texture, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1) = nullptr;
		bool NV_draw_texture = false;

		//draw_vulkan_image
		typedef void (APIENTRY * GLVULKANPROCNV)(void);

		void (*glDrawVkImageNV) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1) = nullptr;
		GLVULKANPROCNV(*glGetVkProcAddrNV) (const GLchar* name) = nullptr;
		void (*glSignalVkFenceNV) (GLuint64 vkFence) = nullptr;
		void (*glSignalVkSemaphoreNV) (GLuint64 vkSemaphore) = nullptr;
		void (*glWaitVkSemaphoreNV) (GLuint64 vkSemaphore) = nullptr;
		bool NV_draw_vulkan_image = false;

		//evaluators
		void (*glEvalMapsNV) (GLenum target, GLenum mode) = nullptr;
		void (*glGetMapAttribParameterfvNV) (GLenum target, GLuint index, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetMapAttribParameterivNV) (GLenum target, GLuint index, GLenum pname, GLint* params) = nullptr;
		void (*glGetMapControlPointsNV) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, void* points) = nullptr;
		void (*glGetMapParameterfvNV) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetMapParameterivNV) (GLenum target, GLenum pname, GLint* params) = nullptr;
		void (*glMapControlPointsNV) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const void* points) = nullptr;
		void (*glMapParameterfvNV) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
		void (*glMapParameterivNV) (GLenum target, GLenum pname, const GLint* params) = nullptr;
		bool NV_evaluators = false;

		//explicit_attrib_location
		bool NV_explicit_attrib_location = false;

		//explicit_multisample
		void (*glGetMultisamplefvNV) (GLenum pname, GLuint index, GLfloat * val) = nullptr;
		void (*glSampleMaskIndexedNV) (GLuint index, GLbitfield mask) = nullptr;
		void (*glTexRenderbufferNV) (GLenum target, GLuint renderbuffer) = nullptr;
		bool NV_explicit_multisample = false;

		//fbo_color_attachments
		bool NV_fbo_color_attachments = false;

		//fence
		void (*glDeleteFencesNV) (GLsizei n, const GLuint * fences) = nullptr;
		void (*glFinishFenceNV) (GLuint fence) = nullptr;
		void (*glGenFencesNV) (GLsizei n, GLuint* fences) = nullptr;
		void (*glGetFenceivNV) (GLuint fence, GLenum pname, GLint* params) = nullptr;
		GLboolean(*glIsFenceNV) (GLuint fence) = nullptr;
		void (*glSetFenceNV) (GLuint fence, GLenum condition) = nullptr;
		GLboolean(*glTestFenceNV) (GLuint fence) = nullptr;
		bool NV_fence = false;

		//fill_rectangle
		bool NV_fill_rectangle = false;
		
		//float_buffer
		bool NV_float_buffer = false;

		//fog_distance
		bool NV_fog_distance = false;

		//fragment_coverage_to_color
		void (*glFragmentCoverageColorNV) (GLuint color) = nullptr;
		bool NV_fragment_coverage_to_color = false;

		//fragment_program
		void (*glGetProgramNamedParameterdvNV) (GLuint id, GLsizei len, const GLubyte * name, GLdouble * params) = nullptr;
		void (*glGetProgramNamedParameterfvNV) (GLuint id, GLsizei len, const GLubyte* name, GLfloat* params) = nullptr;
		void (*glProgramNamedParameter4dNV) (GLuint id, GLsizei len, const GLubyte* name, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
		void (*glProgramNamedParameter4dvNV) (GLuint id, GLsizei len, const GLubyte* name, const GLdouble v[]) = nullptr;
		void (*glProgramNamedParameter4fNV) (GLuint id, GLsizei len, const GLubyte* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
		void (*glProgramNamedParameter4fvNV) (GLuint id, GLsizei len, const GLubyte* name, const GLfloat v[]) = nullptr;
		bool NV_fragment_program = false;

		//fragment_program2
		bool NV_fragment_program2 = false;

		//fragment_program4
		bool NV_fragment_program4 = false;	

		//fragment_program_option
		bool NV_fragment_program_option = false;

		//fragment_shader_interlock
		bool NV_fragment_shader_interlock = false;

		//framebuffer_blit
		void (*glBlitFramebufferNV) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
		bool NV_framebuffer_blit = false;

		//framebuffer_mixed_samples
		bool NV_framebuffer_mixed_samples = false;

		//framebuffer_multisample
		void (*glRenderbufferStorageMultisampleNV) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
		bool NV_framebuffer_multisample = false;

		//framebuffer_multisample_coverage
		void (*glRenderbufferStorageMultisampleCoverageNV) (GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
		bool NV_framebuffer_multisample_coverage = false;

		//generate_mipmap_sRGB
		bool NV_generate_mipmap_sRGB = false;

		//geometry_program4
		void (*glProgramVertexLimitNV) (GLenum target, GLint limit) = nullptr;
		bool NV_geometry_program4 = false;

		//geometry_shader4
		bool NV_geometry_shader4 = false;

		//geometry_shader_passthrough
		bool NV_geometry_shader_passthrough = false;

		//gpu_multicast
		void (*glMulticastBarrierNV) (void) = nullptr;
		void (*glMulticastBlitFramebufferNV) (GLuint srcGpu, GLuint dstGpu, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
		void (*glMulticastBufferSubDataNV) (GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) = nullptr;
		void (*glMulticastCopyBufferSubDataNV) (GLuint readGpu, GLbitfield writeGpuMask, GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) = nullptr;
		void (*glMulticastCopyImageSubDataNV) (GLuint srcGpu, GLbitfield dstGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) = nullptr;
		void (*glMulticastFramebufferSampleLocationsfvNV) (GLuint gpu, GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v) = nullptr;
		void (*glMulticastGetQueryObjecti64vNV) (GLuint gpu, GLuint id, GLenum pname, GLint64* params) = nullptr;
		void (*glMulticastGetQueryObjectivNV) (GLuint gpu, GLuint id, GLenum pname, GLint* params) = nullptr;
		void (*glMulticastGetQueryObjectui64vNV) (GLuint gpu, GLuint id, GLenum pname, GLuint64* params) = nullptr;
		void (*glMulticastGetQueryObjectuivNV) (GLuint gpu, GLuint id, GLenum pname, GLuint* params) = nullptr;
		void (*glMulticastWaitSyncNV) (GLuint signalGpu, GLbitfield waitGpuMask) = nullptr;
		void (*glRenderGpuMaskNV) (GLbitfield mask) = nullptr;
		bool NV_gpu_multicast = false;

		//gpu_program4
		void (*glProgramEnvParameterI4iNV) (GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) = nullptr;
		void (*glProgramEnvParameterI4ivNV) (GLenum target, GLuint index, const GLint* params) = nullptr;
		void (*glProgramEnvParameterI4uiNV) (GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
		void (*glProgramEnvParameterI4uivNV) (GLenum target, GLuint index, const GLuint* params) = nullptr;
		void (*glProgramEnvParametersI4ivNV) (GLenum target, GLuint index, GLsizei count, const GLint* params) = nullptr;
		void (*glProgramEnvParametersI4uivNV) (GLenum target, GLuint index, GLsizei count, const GLuint* params) = nullptr;
		void (*glProgramLocalParameterI4iNV) (GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) = nullptr;
		void (*glProgramLocalParameterI4ivNV) (GLenum target, GLuint index, const GLint* params) = nullptr;
		void (*glProgramLocalParameterI4uiNV) (GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
		void (*glProgramLocalParameterI4uivNV) (GLenum target, GLuint index, const GLuint* params) = nullptr;
		void (*glProgramLocalParametersI4ivNV) (GLenum target, GLuint index, GLsizei count, const GLint* params) = nullptr;
		void (*glProgramLocalParametersI4uivNV) (GLenum target, GLuint index, GLsizei count, const GLuint* params) = nullptr;
		bool NV_gpu_program4 = false;

		//gpu_program5
		bool NV_gpu_program5 = false;

		//gpu_program5_mem_extended
		bool NV_gpu_program5_mem_extended = false;

		//gpu_program_fp64
		bool NV_gpu_program_fp64 = false;

		//gpu_shader5
		void (*glGetUniformi64vNV) (GLuint program, GLint location, GLint64EXT * params) = nullptr;
		void (*glGetUniformui64vNV) (GLuint program, GLint location, GLuint64EXT* params) = nullptr;
		void (*glProgramUniform1i64NV) (GLuint program, GLint location, GLint64EXT x) = nullptr;
		void (*glProgramUniform1i64vNV) (GLuint program, GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
		void (*glProgramUniform1ui64NV) (GLuint program, GLint location, GLuint64EXT x) = nullptr;
		void (*glProgramUniform1ui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		void (*glProgramUniform2i64NV) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y) = nullptr;
		void (*glProgramUniform2i64vNV) (GLuint program, GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
		void (*glProgramUniform2ui64NV) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y) = nullptr;
		void (*glProgramUniform2ui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		void (*glProgramUniform3i64NV) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z) = nullptr;
		void (*glProgramUniform3i64vNV) (GLuint program, GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
		void (*glProgramUniform3ui64NV) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z) = nullptr;
		void (*glProgramUniform3ui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		void (*glProgramUniform4i64NV) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w) = nullptr;
		void (*glProgramUniform4i64vNV) (GLuint program, GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
		void (*glProgramUniform4ui64NV) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) = nullptr;
		void (*glProgramUniform4ui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		void (*glUniform1i64NV) (GLint location, GLint64EXT x) = nullptr;
		void (*glUniform1i64vNV) (GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
		void (*glUniform1ui64NV) (GLint location, GLuint64EXT x) = nullptr;
		void (*glUniform1ui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		void (*glUniform2i64NV) (GLint location, GLint64EXT x, GLint64EXT y) = nullptr;
		void (*glUniform2i64vNV) (GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
		void (*glUniform2ui64NV) (GLint location, GLuint64EXT x, GLuint64EXT y) = nullptr;
		void (*glUniform2ui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		void (*glUniform3i64NV) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z) = nullptr;
		void (*glUniform3i64vNV) (GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
		void (*glUniform3ui64NV) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z) = nullptr;
		void (*glUniform3ui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		void (*glUniform4i64NV) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w) = nullptr;
		void (*glUniform4i64vNV) (GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
		void (*glUniform4ui64NV) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) = nullptr;
		void (*glUniform4ui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		bool NV_gpu_shader5 = false;

		//half_float
		void (*glColor3hNV) (GLhalf red, GLhalf green, GLhalf blue) = nullptr;
		void (*glColor3hvNV) (const GLhalf* v) = nullptr;
		void (*glColor4hNV) (GLhalf red, GLhalf green, GLhalf blue, GLhalf alpha) = nullptr;
		void (*glColor4hvNV) (const GLhalf* v) = nullptr;
		void (*glFogCoordhNV) (GLhalf fog) = nullptr;
		void (*glFogCoordhvNV) (const GLhalf* fog) = nullptr;
		void (*glMultiTexCoord1hNV) (GLenum target, GLhalf s) = nullptr;
		void (*glMultiTexCoord1hvNV) (GLenum target, const GLhalf* v) = nullptr;
		void (*glMultiTexCoord2hNV) (GLenum target, GLhalf s, GLhalf t) = nullptr;
		void (*glMultiTexCoord2hvNV) (GLenum target, const GLhalf* v) = nullptr;
		void (*glMultiTexCoord3hNV) (GLenum target, GLhalf s, GLhalf t, GLhalf r) = nullptr;
		void (*glMultiTexCoord3hvNV) (GLenum target, const GLhalf* v) = nullptr;
		void (*glMultiTexCoord4hNV) (GLenum target, GLhalf s, GLhalf t, GLhalf r, GLhalf q) = nullptr;
		void (*glMultiTexCoord4hvNV) (GLenum target, const GLhalf* v) = nullptr;
		void (*glNormal3hNV) (GLhalf nx, GLhalf ny, GLhalf nz) = nullptr;
		void (*glNormal3hvNV) (const GLhalf* v) = nullptr;
		void (*glSecondaryColor3hNV) (GLhalf red, GLhalf green, GLhalf blue) = nullptr;
		void (*glSecondaryColor3hvNV) (const GLhalf* v) = nullptr;
		void (*glTexCoord1hNV) (GLhalf s) = nullptr;
		void (*glTexCoord1hvNV) (const GLhalf* v) = nullptr;
		void (*glTexCoord2hNV) (GLhalf s, GLhalf t) = nullptr;
		void (*glTexCoord2hvNV) (const GLhalf* v) = nullptr;
		void (*glTexCoord3hNV) (GLhalf s, GLhalf t, GLhalf r) = nullptr;
		void (*glTexCoord3hvNV) (const GLhalf* v) = nullptr;
		void (*glTexCoord4hNV) (GLhalf s, GLhalf t, GLhalf r, GLhalf q) = nullptr;
		void (*glTexCoord4hvNV) (const GLhalf* v) = nullptr;
		void (*glVertex2hNV) (GLhalf x, GLhalf y) = nullptr;
		void (*glVertex2hvNV) (const GLhalf* v) = nullptr;
		void (*glVertex3hNV) (GLhalf x, GLhalf y, GLhalf z) = nullptr;
		void (*glVertex3hvNV) (const GLhalf* v) = nullptr;
		void (*glVertex4hNV) (GLhalf x, GLhalf y, GLhalf z, GLhalf w) = nullptr;
		void (*glVertex4hvNV) (const GLhalf* v) = nullptr;
		void (*glVertexAttrib1hNV) (GLuint index, GLhalf x) = nullptr;
		void (*glVertexAttrib1hvNV) (GLuint index, const GLhalf* v) = nullptr;
		void (*glVertexAttrib2hNV) (GLuint index, GLhalf x, GLhalf y) = nullptr;
		void (*glVertexAttrib2hvNV) (GLuint index, const GLhalf* v) = nullptr;
		void (*glVertexAttrib3hNV) (GLuint index, GLhalf x, GLhalf y, GLhalf z) = nullptr;
		void (*glVertexAttrib3hvNV) (GLuint index, const GLhalf* v) = nullptr;
		void (*glVertexAttrib4hNV) (GLuint index, GLhalf x, GLhalf y, GLhalf z, GLhalf w) = nullptr;
		void (*glVertexAttrib4hvNV) (GLuint index, const GLhalf* v) = nullptr;
		void (*glVertexAttribs1hvNV) (GLuint index, GLsizei n, const GLhalf* v) = nullptr;
		void (*glVertexAttribs2hvNV) (GLuint index, GLsizei n, const GLhalf* v) = nullptr;
		void (*glVertexAttribs3hvNV) (GLuint index, GLsizei n, const GLhalf* v) = nullptr;
		void (*glVertexAttribs4hvNV) (GLuint index, GLsizei n, const GLhalf* v) = nullptr;
		void (*glVertexWeighthNV) (GLhalf weight) = nullptr;
		void (*glVertexWeighthvNV) (const GLhalf* weight) = nullptr;

		//half_float
		bool NV_half_float = false;

		//image_formats
		bool NV_image_formats = false;

		//instanced_arrays
		void (*glVertexAttribDivisorNV) (GLuint index, GLuint divisor) = nullptr;
		bool NV_instanced_arrays = false;

		//internalformat_sample_query
		void (*glGetInternalformatSampleivNV) (GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei bufSize, GLint * params) = nullptr;
		bool NV_internalformat_sample_query = false;

		//light_max_exponent
		bool NV_light_max_exponent = false;

		//multisample_coverage
		bool NV_multisample_coverage = false;

		//multisample_filter_hint
		bool NV_multisample_filter_hint = false;

		//non_square_matrices
		void (*glUniformMatrix2x3fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) = nullptr;
		void (*glUniformMatrix2x4fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glUniformMatrix3x2fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glUniformMatrix3x4fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glUniformMatrix4x2fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		void (*glUniformMatrix4x3fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
		bool NV_non_square_matrices = false;

		//occlusion_query
		void (*glBeginOcclusionQueryNV) (GLuint id) = nullptr;
		void (*glDeleteOcclusionQueriesNV) (GLsizei n, const GLuint* ids) = nullptr;
		void (*glEndOcclusionQueryNV) (void) = nullptr;
		void (*glGenOcclusionQueriesNV) (GLsizei n, GLuint* ids) = nullptr;
		void (*glGetOcclusionQueryivNV) (GLuint id, GLenum pname, GLint* params) = nullptr;
		void (*glGetOcclusionQueryuivNV) (GLuint id, GLenum pname, GLuint* params) = nullptr;
		GLboolean(*glIsOcclusionQueryNV) (GLuint id) = nullptr;
		bool NV_occlusion_query = false;

		//pack_subimage
		bool NV_pack_subimage = false;

		//packed_depth_stencil
		bool NV_packed_depth_stencil = false;

		//packed_float
		bool NV_packed_float = false;

		//packed_float_linear
		bool NV_packed_float_linear = false;

		//parameter_buffer_object
		void (*glProgramBufferParametersIivNV) (GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLint * params) = nullptr;
		void (*glProgramBufferParametersIuivNV) (GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLuint* params) = nullptr;
		void (*glProgramBufferParametersfvNV) (GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLfloat* params) = nullptr;
		bool NV_parameter_buffer_object = false;

		//parameter_buffer_object2
		bool NV_parameter_buffer_object2 = false;

		//path_rendering
		void (*glCopyPathNV) (GLuint resultPath, GLuint srcPath) = nullptr;
		void (*glCoverFillPathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) = nullptr;
		void (*glCoverFillPathNV) (GLuint path, GLenum coverMode) = nullptr;
		void (*glCoverStrokePathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) = nullptr;
		void (*glCoverStrokePathNV) (GLuint path, GLenum coverMode) = nullptr;
		void (*glDeletePathsNV) (GLuint path, GLsizei range) = nullptr;
		GLuint(*glGenPathsNV) (GLsizei range) = nullptr;
		void (*glGetPathColorGenfvNV) (GLenum color, GLenum pname, GLfloat* value) = nullptr;
		void (*glGetPathColorGenivNV) (GLenum color, GLenum pname, GLint* value) = nullptr;
		void (*glGetPathCommandsNV) (GLuint path, GLubyte* commands) = nullptr;
		void (*glGetPathCoordsNV) (GLuint path, GLfloat* coords) = nullptr;
		void (*glGetPathDashArrayNV) (GLuint path, GLfloat* dashArray) = nullptr;
		GLfloat(*glGetPathLengthNV) (GLuint path, GLsizei startSegment, GLsizei numSegments) = nullptr;
		void (*glGetPathMetricRangeNV) (GLbitfield metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride, GLfloat* metrics) = nullptr;
		void (*glGetPathMetricsNV) (GLbitfield metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLsizei stride, GLfloat* metrics) = nullptr;
		void (*glGetPathParameterfvNV) (GLuint path, GLenum pname, GLfloat* value) = nullptr;
		void (*glGetPathParameterivNV) (GLuint path, GLenum pname, GLint* value) = nullptr;
		void (*glGetPathSpacingNV) (GLenum pathListMode, GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat* returnedSpacing) = nullptr;
		void (*glGetPathTexGenfvNV) (GLenum texCoordSet, GLenum pname, GLfloat* value) = nullptr;
		void (*glGetPathTexGenivNV) (GLenum texCoordSet, GLenum pname, GLint* value) = nullptr;
		void (*glGetProgramResourcefvNV) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLfloat* params) = nullptr;
		void (*glInterpolatePathsNV) (GLuint resultPath, GLuint pathA, GLuint pathB, GLfloat weight) = nullptr;
		GLboolean(*glIsPathNV) (GLuint path) = nullptr;
		GLboolean(*glIsPointInFillPathNV) (GLuint path, GLuint mask, GLfloat x, GLfloat y) = nullptr;
		GLboolean(*glIsPointInStrokePathNV) (GLuint path, GLfloat x, GLfloat y) = nullptr;
		void (*glMatrixLoad3x2fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glMatrixLoad3x3fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glMatrixLoadTranspose3x3fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glMatrixMult3x2fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glMatrixMult3x3fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glMatrixMultTranspose3x3fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
		void (*glPathColorGenNV) (GLenum color, GLenum genMode, GLenum colorFormat, const GLfloat* coeffs) = nullptr;
		void (*glPathCommandsNV) (GLuint path, GLsizei numCommands, const GLubyte* commands, GLsizei numCoords, GLenum coordType, const void* coords) = nullptr;
		void (*glPathCoordsNV) (GLuint path, GLsizei numCoords, GLenum coordType, const void* coords) = nullptr;
		void (*glPathCoverDepthFuncNV) (GLenum zfunc) = nullptr;
		void (*glPathDashArrayNV) (GLuint path, GLsizei dashCount, const GLfloat* dashArray) = nullptr;
		void (*glPathFogGenNV) (GLenum genMode) = nullptr;
		GLenum(*glPathGlyphIndexArrayNV) (GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale) = nullptr;
		GLenum(*glPathGlyphIndexRangeNV) (GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint baseAndCount[2]) = nullptr;
		void (*glPathGlyphRangeNV) (GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei numGlyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale) = nullptr;
		void (*glPathGlyphsNV) (GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLsizei numGlyphs, GLenum type, const void* charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale) = nullptr;
		GLenum(*glPathMemoryGlyphIndexArrayNV) (GLuint firstPathName, GLenum fontTarget, GLsizeiptr fontSize, const void* fontData, GLsizei faceIndex, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale) = nullptr;
		void (*glPathParameterfNV) (GLuint path, GLenum pname, GLfloat value) = nullptr;
		void (*glPathParameterfvNV) (GLuint path, GLenum pname, const GLfloat* value) = nullptr;
		void (*glPathParameteriNV) (GLuint path, GLenum pname, GLint value) = nullptr;
		void (*glPathParameterivNV) (GLuint path, GLenum pname, const GLint* value) = nullptr;
		void (*glPathStencilDepthOffsetNV) (GLfloat factor, GLfloat units) = nullptr;
		void (*glPathStencilFuncNV) (GLenum func, GLint ref, GLuint mask) = nullptr;
		void (*glPathStringNV) (GLuint path, GLenum format, GLsizei length, const void* pathString) = nullptr;
		void (*glPathSubCommandsNV) (GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte* commands, GLsizei numCoords, GLenum coordType, const void* coords) = nullptr;
		void (*glPathSubCoordsNV) (GLuint path, GLsizei coordStart, GLsizei numCoords, GLenum coordType, const void* coords) = nullptr;
		void (*glPathTexGenNV) (GLenum texCoordSet, GLenum genMode, GLint components, const GLfloat* coeffs) = nullptr;
		GLboolean(*glPointAlongPathNV) (GLuint path, GLsizei startSegment, GLsizei numSegments, GLfloat distance, GLfloat* x, GLfloat* y, GLfloat* tangentX, GLfloat* tangentY) = nullptr;
		void (*glProgramPathFragmentInputGenNV) (GLuint program, GLint location, GLenum genMode, GLint components, const GLfloat* coeffs) = nullptr;
		void (*glStencilFillPathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, const GLfloat* transformValues) = nullptr;
		void (*glStencilFillPathNV) (GLuint path, GLenum fillMode, GLuint mask) = nullptr;
		void (*glStencilStrokePathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, const GLfloat* transformValues) = nullptr;
		void (*glStencilStrokePathNV) (GLuint path, GLint reference, GLuint mask) = nullptr;
		void (*glStencilThenCoverFillPathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) = nullptr;
		void (*glStencilThenCoverFillPathNV) (GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode) = nullptr;
		void (*glStencilThenCoverStrokePathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) = nullptr;
		void (*glStencilThenCoverStrokePathNV) (GLuint path, GLint reference, GLuint mask, GLenum coverMode) = nullptr;
		void (*glTransformPathNV) (GLuint resultPath, GLuint srcPath, GLenum transformType, const GLfloat* transformValues) = nullptr;
		void (*glWeightPathsNV) (GLuint resultPath, GLsizei numPaths, const GLuint paths[], const GLfloat weights[]) = nullptr;
		bool NV_path_rendering = false;

		//path_rendering_shared_edge
		bool NV_path_rendering_shared_edge = false;

		//pixel_buffer_object
		bool NV_pixel_buffer_object = false;

		//pixel_data_range
		void (*glFlushPixelDataRangeNV) (GLenum target) = nullptr;
		void (*glPixelDataRangeNV) (GLenum target, GLsizei length, void* pointer) = nullptr;
		bool NV_pixel_data_range = false;

		//platform_binary
		bool NV_platform_binary = false;

		//point_sprite
		void (*glPointParameteriNV) (GLenum pname, GLint param) = nullptr;
		void (*glPointParameterivNV) (GLenum pname, const GLint* params) = nullptr;
		bool NV_point_sprite = false;

		//polygon_mode
		void (*glPolygonModeNV) (GLenum face, GLenum mode) = nullptr;
		bool NV_polygon_mode = false;

		//present_video
		void (*glGetVideoi64vNV) (GLuint video_slot, GLenum pname, GLint64EXT * params) = nullptr;
		void (*glGetVideoivNV) (GLuint video_slot, GLenum pname, GLint* params) = nullptr;
		void (*glGetVideoui64vNV) (GLuint video_slot, GLenum pname, GLuint64EXT* params) = nullptr;
		void (*glGetVideouivNV) (GLuint video_slot, GLenum pname, GLuint* params) = nullptr;
		void (*glPresentFrameDualFillNV) (GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3) = nullptr;
		void (*glPresentFrameKeyedNV) (GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1) = nullptr;
		bool NV_present_video = false;		

		//primitive_restart
		void (*glPrimitiveRestartIndexNV) (GLuint index) = nullptr;
		void (*glPrimitiveRestartNV) (void) = nullptr;
		bool NV_primitive_restart = false;

		//read_depth
		bool NV_read_depth = false;

		//read_depth_stencil
		bool NV_read_depth_stencil = false;

		//read_stencil
		bool NV_read_stencil = false;

		//register_combiners
		void (*glCombinerInputNV) (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage) = nullptr;
		void (*glCombinerOutputNV) (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum) = nullptr;
		void (*glCombinerParameterfNV) (GLenum pname, GLfloat param) = nullptr;
		void (*glCombinerParameterfvNV) (GLenum pname, const GLfloat* params) = nullptr;
		void (*glCombinerParameteriNV) (GLenum pname, GLint param) = nullptr;
		void (*glCombinerParameterivNV) (GLenum pname, const GLint* params) = nullptr;
		void (*glFinalCombinerInputNV) (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage) = nullptr;
		void (*glGetCombinerInputParameterfvNV) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetCombinerInputParameterivNV) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint* params) = nullptr;
		void (*glGetCombinerOutputParameterfvNV) (GLenum stage, GLenum portion, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetCombinerOutputParameterivNV) (GLenum stage, GLenum portion, GLenum pname, GLint* params) = nullptr;
		void (*glGetFinalCombinerInputParameterfvNV) (GLenum variable, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetFinalCombinerInputParameterivNV) (GLenum variable, GLenum pname, GLint* params) = nullptr;
		bool NV_register_combiners = false;

		//register_combiners2
		void (*glCombinerStageParameterfvNV) (GLenum stage, GLenum pname, const GLfloat * params) = nullptr;
		void (*glGetCombinerStageParameterfvNV) (GLenum stage, GLenum pname, GLfloat* params) = nullptr;
		bool NV_register_combiners2 = false;	

		//robustness_video_memory_purge
		bool NV_robustness_video_memory_purge = false;

		//sRGB_formats
		bool NV_sRGB_formats = false;

		//sample_locations
		void (*glFramebufferSampleLocationsfvNV) (GLenum target, GLuint start, GLsizei count, const GLfloat * v) = nullptr;
		void (*glNamedFramebufferSampleLocationsfvNV) (GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v) = nullptr;
		bool NV_sample_locations = false;

		//sample_mask_override_coverage
		bool NV_sample_mask_override_coverage = false;

		//shader_atomic_counters
		bool NV_shader_atomic_counters = false;

		//shader_atomic_float
		bool NV_shader_atomic_float = false;

		//shader_atomic_float64
		bool NV_shader_atomic_float64 = false;

		//shader_atomic_fp16_vector
		bool NV_shader_atomic_fp16_vector = false;

		//shader_atomic_int64
		bool NV_shader_atomic_int64 = false;

		//shader_buffer_load
		void (*glGetBufferParameterui64vNV) (GLenum target, GLenum pname, GLuint64EXT * params) = nullptr;
		void (*glGetIntegerui64vNV) (GLenum value, GLuint64EXT* result) = nullptr;
		void (*glGetNamedBufferParameterui64vNV) (GLuint buffer, GLenum pname, GLuint64EXT* params) = nullptr;
		GLboolean(*glIsBufferResidentNV) (GLenum target) = nullptr;
		GLboolean(*glIsNamedBufferResidentNV) (GLuint buffer) = nullptr;
		void (*glMakeBufferNonResidentNV) (GLenum target) = nullptr;
		void (*glMakeBufferResidentNV) (GLenum target, GLenum access) = nullptr;
		void (*glMakeNamedBufferNonResidentNV) (GLuint buffer) = nullptr;
		void (*glMakeNamedBufferResidentNV) (GLuint buffer, GLenum access) = nullptr;
		void (*glProgramUniformui64NV) (GLuint program, GLint location, GLuint64EXT value) = nullptr;
		void (*glProgramUniformui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		void (*glUniformui64NV) (GLint location, GLuint64EXT value) = nullptr;
		void (*glUniformui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
		bool NV_shader_buffer_load = false;

		//shader_noperspective_interpolation
		bool NV_shader_noperspective_interpolation = false;

		//shader_storage_buffer_object
		bool NV_shader_storage_buffer_object = false;

		//shader_thread_group
		bool NV_shader_thread_group = false;

		//shader_thread_shuffle
		bool NV_shader_thread_shuffle = false;

		//shadow_samplers_array
		bool NV_shadow_samplers_array = false;

		//shadow_samplers_cube
		bool NV_shadow_samplers_cube = false;

		//stereo_view_rendering
		bool NV_stereo_view_rendering = false;

		//tessellation_program5
		bool NV_tessellation_program5 = false;

		//texgen_emboss
		bool NV_texgen_emboss = false;

		//texgen_reflection
		bool NV_texgen_reflection = false;

		//texture_array
		void (*glCompressedTexImage3DNV) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) = nullptr;
		void (*glCompressedTexSubImage3DNV) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
		void (*glCopyTexSubImage3DNV) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
		void (*glFramebufferTextureLayerNV) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
		void (*glTexImage3DNV) (GLenum target, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
		void (*glTexSubImage3DNV) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
		bool NV_texture_array = false;

		//texture_barrier
		void (*glTextureBarrierNV) (void) = nullptr;
		bool NV_texture_barrier = false;

		//texture_border_clamp
		bool NV_texture_border_clamp = false;

		//texture_compression_latc
		bool NV_texture_compression_latc = false;

		//texture_compression_s3tc
		bool NV_texture_compression_s3tc = false;

		//texture_compression_s3tc_update
		bool NV_texture_compression_s3tc_update = false;

		//texture_compression_vtc
		bool NV_texture_compression_vtc = false;

		//texture_env_combine4
		bool NV_texture_env_combine4 = false;

		//texture_expand_normal
		bool NV_texture_expand_normal = false;

		//texture_multisample
		void (*glTexImage2DMultisampleCoverageNV) (GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) = nullptr;
		void (*glTexImage3DMultisampleCoverageNV) (GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) = nullptr;
		void (*glTextureImage2DMultisampleCoverageNV) (GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) = nullptr;
		void (*glTextureImage2DMultisampleNV) (GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) = nullptr;
		void (*glTextureImage3DMultisampleCoverageNV) (GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) = nullptr;
		void (*glTextureImage3DMultisampleNV) (GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) = nullptr;
		bool NV_texture_multisample = false;

		//texture_npot_2D_mipmap
		bool NV_texture_npot_2D_mipmap = false;

		//texture_rectangle
		bool NV_texture_rectangle = false;

		//texture_rectangle_compressed
		bool NV_texture_rectangle_compressed = false;

		//texture_shader
		bool NV_texture_shader = false;

		//texture_shader2
		bool NV_texture_shader2 = false;

		//texture_shader3
		bool NV_texture_shader3 = false;

		//transform_feedback
		void (*glActiveVaryingNV) (GLuint program, const GLchar * name) = nullptr;
		void (*glBeginTransformFeedbackNV) (GLenum primitiveMode) = nullptr;
		void (*glBindBufferBaseNV) (GLenum target, GLuint index, GLuint buffer) = nullptr;
		void (*glBindBufferOffsetNV) (GLenum target, GLuint index, GLuint buffer, GLintptr offset) = nullptr;
		void (*glBindBufferRangeNV) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
		void (*glEndTransformFeedbackNV) (void) = nullptr;
		void (*glGetActiveVaryingNV) (GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) = nullptr;
		void (*glGetTransformFeedbackVaryingNV) (GLuint program, GLuint index, GLint* location) = nullptr;
		GLint(*glGetVaryingLocationNV) (GLuint program, const GLchar* name) = nullptr;
		void (*glTransformFeedbackAttribsNV) (GLuint count, const GLint* attribs, GLenum bufferMode) = nullptr;
		void (*glTransformFeedbackVaryingsNV) (GLuint program, GLsizei count, const GLint* locations, GLenum bufferMode) = nullptr;
		bool NV_transform_feedback = false;

		//transform_feedback2
		void (*glBindTransformFeedbackNV) (GLenum target, GLuint id) = nullptr;
		void (*glDeleteTransformFeedbacksNV) (GLsizei n, const GLuint* ids) = nullptr;
		void (*glDrawTransformFeedbackNV) (GLenum mode, GLuint id) = nullptr;
		void (*glGenTransformFeedbacksNV) (GLsizei n, GLuint* ids) = nullptr;
		GLboolean(*glIsTransformFeedbackNV) (GLuint id) = nullptr;
		void (*glPauseTransformFeedbackNV) (void) = nullptr;
		void (*glResumeTransformFeedbackNV) (void) = nullptr;
		bool NV_transform_feedback2 = false;

		//uniform_buffer_unified_memory
		bool NV_uniform_buffer_unified_memory = false;
		
		//vdpau_interop
		void (*glVDPAUFiniNV) (void) = nullptr;
		void (*glVDPAUGetSurfaceivNV) (GLvdpauSurfaceNV surface, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) = nullptr;
		void (*glVDPAUInitNV) (const void* vdpDevice, const void* getProcAddress) = nullptr;
		void (*glVDPAUIsSurfaceNV) (GLvdpauSurfaceNV surface) = nullptr;
		void (*glVDPAUMapSurfacesNV) (GLsizei numSurfaces, const GLvdpauSurfaceNV* surfaces) = nullptr;
		GLvdpauSurfaceNV(*glVDPAURegisterOutputSurfaceNV) (const void* vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint* textureNames) = nullptr;
		GLvdpauSurfaceNV(*glVDPAURegisterVideoSurfaceNV) (const void* vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint* textureNames) = nullptr;
		void (*glVDPAUSurfaceAccessNV) (GLvdpauSurfaceNV surface, GLenum access) = nullptr;
		void (*glVDPAUUnmapSurfacesNV) (GLsizei numSurface, const GLvdpauSurfaceNV* surfaces) = nullptr;
		void (*glVDPAUUnregisterSurfaceNV) (GLvdpauSurfaceNV surface) = nullptr;
		bool NV_vdpau_interop = false;

		//vertex_array_range
		void (*glFlushVertexArrayRangeNV) (void) = nullptr;
		void (*glVertexArrayRangeNV) (GLsizei length, void* pointer) = nullptr;
		bool NV_vertex_array_range = false;		

		//vertex_array_range2
		bool NV_vertex_array_range2 = false;

		//vertex_attrib_integer_64bit
		void (*glGetVertexAttribLi64vNV) (GLuint index, GLenum pname, GLint64EXT * params) = nullptr;
		void (*glGetVertexAttribLui64vNV) (GLuint index, GLenum pname, GLuint64EXT* params) = nullptr;
		void (*glVertexAttribL1i64NV) (GLuint index, GLint64EXT x) = nullptr;
		void (*glVertexAttribL1i64vNV) (GLuint index, const GLint64EXT* v) = nullptr;
		void (*glVertexAttribL1ui64NV) (GLuint index, GLuint64EXT x) = nullptr;
		void (*glVertexAttribL1ui64vNV) (GLuint index, const GLuint64EXT* v) = nullptr;
		void (*glVertexAttribL2i64NV) (GLuint index, GLint64EXT x, GLint64EXT y) = nullptr;
		void (*glVertexAttribL2i64vNV) (GLuint index, const GLint64EXT* v) = nullptr;
		void (*glVertexAttribL2ui64NV) (GLuint index, GLuint64EXT x, GLuint64EXT y) = nullptr;
		void (*glVertexAttribL2ui64vNV) (GLuint index, const GLuint64EXT* v) = nullptr;
		void (*glVertexAttribL3i64NV) (GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z) = nullptr;
		void (*glVertexAttribL3i64vNV) (GLuint index, const GLint64EXT* v) = nullptr;
		void (*glVertexAttribL3ui64NV) (GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z) = nullptr;
		void (*glVertexAttribL3ui64vNV) (GLuint index, const GLuint64EXT* v) = nullptr;
		void (*glVertexAttribL4i64NV) (GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w) = nullptr;
		void (*glVertexAttribL4i64vNV) (GLuint index, const GLint64EXT* v) = nullptr;
		void (*glVertexAttribL4ui64NV) (GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) = nullptr;
		void (*glVertexAttribL4ui64vNV) (GLuint index, const GLuint64EXT* v) = nullptr;
		void (*glVertexAttribLFormatNV) (GLuint index, GLint size, GLenum type, GLsizei stride) = nullptr;
		bool NV_vertex_attrib_integer_64bit = false;

		//vertex_buffer_unified_memory
		void (*glBufferAddressRangeNV) (GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length) = nullptr;
		void (*glColorFormatNV) (GLint size, GLenum type, GLsizei stride) = nullptr;
		void (*glEdgeFlagFormatNV) (GLsizei stride) = nullptr;
		void (*glFogCoordFormatNV) (GLenum type, GLsizei stride) = nullptr;
		void (*glGetIntegerui64i_vNV) (GLenum value, GLuint index, GLuint64EXT result[]) = nullptr;
		void (*glIndexFormatNV) (GLenum type, GLsizei stride) = nullptr;
		void (*glNormalFormatNV) (GLenum type, GLsizei stride) = nullptr;
		void (*glSecondaryColorFormatNV) (GLint size, GLenum type, GLsizei stride) = nullptr;
		void (*glTexCoordFormatNV) (GLint size, GLenum type, GLsizei stride) = nullptr;
		void (*glVertexAttribFormatNV) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride) = nullptr;
		void (*glVertexAttribIFormatNV) (GLuint index, GLint size, GLenum type, GLsizei stride) = nullptr;
		void (*glVertexFormatNV) (GLint size, GLenum type, GLsizei stride) = nullptr;
		bool NV_vertex_buffer_unified_memory = false;

		//vertex_program
		GLboolean(*glAreProgramsResidentNV) (GLsizei n, const GLuint * ids, GLboolean * residences) = nullptr;
		void (*glBindProgramNV) (GLenum target, GLuint id) = nullptr;
		void (*glDeleteProgramsNV) (GLsizei n, const GLuint* ids) = nullptr;
		void (*glExecuteProgramNV) (GLenum target, GLuint id, const GLfloat* params) = nullptr;
		void (*glGenProgramsNV) (GLsizei n, GLuint* ids) = nullptr;
		void (*glGetProgramParameterdvNV) (GLenum target, GLuint index, GLenum pname, GLdouble* params) = nullptr;
		void (*glGetProgramParameterfvNV) (GLenum target, GLuint index, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetProgramStringNV) (GLuint id, GLenum pname, GLubyte* program) = nullptr;
		void (*glGetProgramivNV) (GLuint id, GLenum pname, GLint* params) = nullptr;
		void (*glGetTrackMatrixivNV) (GLenum target, GLuint address, GLenum pname, GLint* params) = nullptr;
		void (*glGetVertexAttribPointervNV) (GLuint index, GLenum pname, void** pointer) = nullptr;
		void (*glGetVertexAttribdvNV) (GLuint index, GLenum pname, GLdouble* params) = nullptr;
		void (*glGetVertexAttribfvNV) (GLuint index, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetVertexAttribivNV) (GLuint index, GLenum pname, GLint* params) = nullptr;
		GLboolean(*glIsProgramNV) (GLuint id) = nullptr;
		void (*glLoadProgramNV) (GLenum target, GLuint id, GLsizei len, const GLubyte* program) = nullptr;
		void (*glProgramParameter4dNV) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
		void (*glProgramParameter4dvNV) (GLenum target, GLuint index, const GLdouble* params) = nullptr;
		void (*glProgramParameter4fNV) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
		void (*glProgramParameter4fvNV) (GLenum target, GLuint index, const GLfloat* params) = nullptr;
		void (*glProgramParameters4dvNV) (GLenum target, GLuint index, GLsizei num, const GLdouble* params) = nullptr;
		void (*glProgramParameters4fvNV) (GLenum target, GLuint index, GLsizei num, const GLfloat* params) = nullptr;
		void (*glRequestResidentProgramsNV) (GLsizei n, GLuint* ids) = nullptr;
		void (*glTrackMatrixNV) (GLenum target, GLuint address, GLenum matrix, GLenum transform) = nullptr;
		void (*glVertexAttrib1dNV) (GLuint index, GLdouble x) = nullptr;
		void (*glVertexAttrib1dvNV) (GLuint index, const GLdouble* v) = nullptr;
		void (*glVertexAttrib1fNV) (GLuint index, GLfloat x) = nullptr;
		void (*glVertexAttrib1fvNV) (GLuint index, const GLfloat* v) = nullptr;
		void (*glVertexAttrib1sNV) (GLuint index, GLshort x) = nullptr;
		void (*glVertexAttrib1svNV) (GLuint index, const GLshort* v) = nullptr;
		void (*glVertexAttrib2dNV) (GLuint index, GLdouble x, GLdouble y) = nullptr;
		void (*glVertexAttrib2dvNV) (GLuint index, const GLdouble* v) = nullptr;
		void (*glVertexAttrib2fNV) (GLuint index, GLfloat x, GLfloat y) = nullptr;
		void (*glVertexAttrib2fvNV) (GLuint index, const GLfloat* v) = nullptr;
		void (*glVertexAttrib2sNV) (GLuint index, GLshort x, GLshort y) = nullptr;
		void (*glVertexAttrib2svNV) (GLuint index, const GLshort* v) = nullptr;
		void (*glVertexAttrib3dNV) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
		void (*glVertexAttrib3dvNV) (GLuint index, const GLdouble* v) = nullptr;
		void (*glVertexAttrib3fNV) (GLuint index, GLfloat x, GLfloat y, GLfloat z) = nullptr;
		void (*glVertexAttrib3fvNV) (GLuint index, const GLfloat* v) = nullptr;
		void (*glVertexAttrib3sNV) (GLuint index, GLshort x, GLshort y, GLshort z) = nullptr;
		void (*glVertexAttrib3svNV) (GLuint index, const GLshort* v) = nullptr;
		void (*glVertexAttrib4dNV) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
		void (*glVertexAttrib4dvNV) (GLuint index, const GLdouble* v) = nullptr;
		void (*glVertexAttrib4fNV) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
		void (*glVertexAttrib4fvNV) (GLuint index, const GLfloat* v) = nullptr;
		void (*glVertexAttrib4sNV) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
		void (*glVertexAttrib4svNV) (GLuint index, const GLshort* v) = nullptr;
		void (*glVertexAttrib4ubNV) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) = nullptr;
		void (*glVertexAttrib4ubvNV) (GLuint index, const GLubyte* v) = nullptr;
		void (*glVertexAttribPointerNV) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
		void (*glVertexAttribs1dvNV) (GLuint index, GLsizei n, const GLdouble* v) = nullptr;
		void (*glVertexAttribs1fvNV) (GLuint index, GLsizei n, const GLfloat* v) = nullptr;
		void (*glVertexAttribs1svNV) (GLuint index, GLsizei n, const GLshort* v) = nullptr;
		void (*glVertexAttribs2dvNV) (GLuint index, GLsizei n, const GLdouble* v) = nullptr;
		void (*glVertexAttribs2fvNV) (GLuint index, GLsizei n, const GLfloat* v) = nullptr;
		void (*glVertexAttribs2svNV) (GLuint index, GLsizei n, const GLshort* v) = nullptr;
		void (*glVertexAttribs3dvNV) (GLuint index, GLsizei n, const GLdouble* v) = nullptr;
		void (*glVertexAttribs3fvNV) (GLuint index, GLsizei n, const GLfloat* v) = nullptr;
		void (*glVertexAttribs3svNV) (GLuint index, GLsizei n, const GLshort* v) = nullptr;
		void (*glVertexAttribs4dvNV) (GLuint index, GLsizei n, const GLdouble* v) = nullptr;
		void (*glVertexAttribs4fvNV) (GLuint index, GLsizei n, const GLfloat* v) = nullptr;
		void (*glVertexAttribs4svNV) (GLuint index, GLsizei n, const GLshort* v) = nullptr;
		void (*glVertexAttribs4ubvNV) (GLuint index, GLsizei n, const GLubyte* v) = nullptr;
		bool NV_vertex_program = false;

		//vertex_program1_1
		bool NV_vertex_program1_1 = false;

		//vertex_program2
		bool NV_vertex_program2 = false;

		//vertex_program2_option
		bool NV_vertex_program2_option = false;

		//vertex_program3
		bool NV_vertex_program3 = false;

		//vertex_program4
		bool NV_vertex_program4 = false;

		//video_capture
		void (*glBeginVideoCaptureNV) (GLuint video_capture_slot) = nullptr;
		void (*glBindVideoCaptureStreamBufferNV) (GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLintptrARB offset) = nullptr;
		void (*glBindVideoCaptureStreamTextureNV) (GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLenum target, GLuint texture) = nullptr;
		void (*glEndVideoCaptureNV) (GLuint video_capture_slot) = nullptr;
		void (*glGetVideoCaptureStreamdvNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, GLdouble* params) = nullptr;
		void (*glGetVideoCaptureStreamfvNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, GLfloat* params) = nullptr;
		void (*glGetVideoCaptureStreamivNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, GLint* params) = nullptr;
		void (*glGetVideoCaptureivNV) (GLuint video_capture_slot, GLenum pname, GLint* params) = nullptr;
		GLenum(*glVideoCaptureNV) (GLuint video_capture_slot, GLuint* sequence_num, GLuint64EXT* capture_time) = nullptr;
		void (*glVideoCaptureStreamParameterdvNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, const GLdouble* params) = nullptr;
		void (*glVideoCaptureStreamParameterfvNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, const GLfloat* params) = nullptr;
		void (*glVideoCaptureStreamParameterivNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, const GLint* params) = nullptr;
		bool NV_video_capture = false;

		//viewport_array
		void (*glDepthRangeArrayfvNV) (GLuint first, GLsizei count, const GLfloat * v) = nullptr;
		void (*glDepthRangeIndexedfNV) (GLuint index, GLfloat n, GLfloat f) = nullptr;
		void (*glDisableiNV) (GLenum target, GLuint index) = nullptr;
		void (*glEnableiNV) (GLenum target, GLuint index) = nullptr;
		void (*glGetFloati_vNV) (GLenum target, GLuint index, GLfloat* data) = nullptr;
		GLboolean(*glIsEnablediNV) (GLenum target, GLuint index) = nullptr;
		void (*glScissorArrayvNV) (GLuint first, GLsizei count, const GLint* v) = nullptr;
		void (*glScissorIndexedNV) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) = nullptr;
		void (*glScissorIndexedvNV) (GLuint index, const GLint* v) = nullptr;
		void (*glViewportArrayvNV) (GLuint first, GLsizei count, const GLfloat* v) = nullptr;
		void (*glViewportIndexedfNV) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) = nullptr;
		void (*glViewportIndexedfvNV) (GLuint index, const GLfloat* v) = nullptr;
		bool NV_viewport_array = false;

		//viewport_array2
		bool NV_viewport_array2 = false;
			   		 	  
		//viewport_swizzle
		void (*glViewportSwizzleNV) (GLuint index, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew) = nullptr;
		bool NV_viewport_swizzle = false;

		//*< load NV Extensions
		void LoadNVExtensions()
		{
			//3dvision_settings
			FetchProcAddress(glStereoParameterfNV, "glStereoParameterfNV");
			FetchProcAddress(glStereoParameteriNV, "glStereoParameteriNV");
			FetchProcAddress(NV_3dvision_settings, "NV_3dvision_settings");

			//EGL_stream_consumer_external
			FetchProcAddress(NV_EGL_stream_consumer_external, "NV_EGL_stream_consumer_external");

			//alpha_to_coverage_dither_control
			FetchProcAddress(NV_alpha_to_coverage_dither_control, "NV_alpha_to_coverage_dither_control");

			//bgr
			FetchProcAddress(NV_bgr, "NV_bgr");

			//bindless_multi_draw_indirect
			FetchProcAddress(glMultiDrawArraysIndirectBindlessNV, "glMultiDrawArraysIndirectBindlessNV");
			FetchProcAddress(glMultiDrawElementsIndirectBindlessNV, "glMultiDrawElementsIndirectBindlessNV");
			FetchProcAddress(NV_bindless_multi_draw_indirect, "NV_bindless_multi_draw_indirect");

			//bindless_multi_draw_indirect_count
			FetchProcAddress(glMultiDrawArraysIndirectBindlessCountNV, "glMultiDrawArraysIndirectBindlessCountNV");
			FetchProcAddress(glMultiDrawElementsIndirectBindlessCountNV, "glMultiDrawElementsIndirectBindlessCountNV");
			FetchProcAddress(NV_bindless_multi_draw_indirect_count, "NV_bindless_multi_draw_indirect_count");

			//bindless_texture
			FetchProcAddress(glGetImageHandleNV, "glGetImageHandleNV");
			FetchProcAddress(glGetTextureHandleNV, "glGetTextureHandleNV");
			FetchProcAddress(glGetTextureSamplerHandleNV, "glGetTextureSamplerHandleNV");
			FetchProcAddress(glIsImageHandleResidentNV, "glIsImageHandleResidentNV");
			FetchProcAddress(glIsTextureHandleResidentNV, "glIsTextureHandleResidentNV");
			FetchProcAddress(glMakeImageHandleNonResidentNV, "glMakeImageHandleNonResidentNV");
			FetchProcAddress(glMakeImageHandleResidentNV, "glMakeImageHandleResidentNV");
			FetchProcAddress(glMakeTextureHandleNonResidentNV, "glMakeTextureHandleNonResidentNV");
			FetchProcAddress(glMakeTextureHandleResidentNV, "glMakeTextureHandleResidentNV");
			FetchProcAddress(glProgramUniformHandleui64NV, "glProgramUniformHandleui64NV");
			FetchProcAddress(glProgramUniformHandleui64vNV, "glProgramUniformHandleui64vNV");
			FetchProcAddress(glUniformHandleui64NV, "glUniformHandleui64NV");
			FetchProcAddress(glUniformHandleui64vNV, "glUniformHandleui64vNV");
			FetchProcAddress(NV_bindless_texture, "NV_bindless_texture");

			//blend_equation_advanced
			FetchProcAddress(glBlendBarrierNV, "glBlendBarrierNV");
			FetchProcAddress(glBlendParameteriNV, "glBlendParameteriNV");
			FetchProcAddress(NV_blend_equation_advanced, "NV_blend_equation_advanced");

			//blend_equation_advanced_coherent
			FetchProcAddress(NV_blend_equation_advanced_coherent, "NV_blend_equation_advanced_coherent");

			//blend_minmax_factor
			FetchProcAddress(NV_blend_minmax_factor, "NV_blend_minmax_factor");

			//blend_square
			FetchProcAddress(NV_blend_square, "NV_blend_square");

			//clip_space_w_scaling
			FetchProcAddress(glViewportPositionWScaleNV, "glViewportPositionWScaleNV");
			FetchProcAddress(NV_clip_space_w_scaling, "NV_clip_space_w_scaling");

			//command_list
			FetchProcAddress(glCallCommandListNV, "glCallCommandListNV");
			FetchProcAddress(glCommandListSegmentsNV, "glCommandListSegmentsNV");
			FetchProcAddress(glCompileCommandListNV, "glCompileCommandListNV");
			FetchProcAddress(glCreateCommandListsNV, "glCreateCommandListsNV");
			FetchProcAddress(glCreateStatesNV, "glCreateStatesNV");
			FetchProcAddress(glDeleteCommandListsNV, "glDeleteCommandListsNV");
			FetchProcAddress(glDeleteStatesNV, "glDeleteStatesNV");
			FetchProcAddress(glDrawCommandsAddressNV, "glDrawCommandsAddressNV");
			FetchProcAddress(glDrawCommandsNV, "glDrawCommandsNV");
			FetchProcAddress(glDrawCommandsStatesAddressNV, "glDrawCommandsStatesAddressNV");
			FetchProcAddress(glDrawCommandsStatesNV, "glDrawCommandsStatesNV");
			FetchProcAddress(glGetCommandHeaderNV, "glGetCommandHeaderNV");
			FetchProcAddress(glGetStageIndexNV, "glGetStageIndexNV");
			FetchProcAddress(glIsCommandListNV, "glIsCommandListNV");
			FetchProcAddress(glIsStateNV, "glIsStateNV");
			FetchProcAddress(glListDrawCommandsStatesClientNV, "glListDrawCommandsStatesClientNV");
			FetchProcAddress(glStateCaptureNV, "glStateCaptureNV");
			FetchProcAddress(NV_command_list, "NV_command_list");

			//compute_program5
			FetchProcAddress(NV_compute_program5, "NV_compute_program5");

			//conditional_render
			FetchProcAddress(glBeginConditionalRenderNV, "glBeginConditionalRenderNV");
			FetchProcAddress(glEndConditionalRenderNV, "glEndConditionalRenderNV");
			FetchProcAddress(NV_conditional_render, "NV_conditional_render");

			//conservative_raster
			FetchProcAddress(glSubpixelPrecisionBiasNV, "glSubpixelPrecisionBiasNV");
			FetchProcAddress(NV_conservative_raster, "NV_conservative_raster");

			//conservative_raster_dilate
			FetchProcAddress(glConservativeRasterParameterfNV, "glConservativeRasterParameterfNV");
			FetchProcAddress(NV_conservative_raster_dilate, "NV_conservative_raster_dilate");

			//conservative_raster_pre_snap_triangles
			FetchProcAddress(glConservativeRasterParameteriNV, "glConservativeRasterParameteriNV");
			FetchProcAddress(NV_conservative_raster_pre_snap_triangles, "NV_conservative_raster_pre_snap_triangles");

			//copy_buffer
			FetchProcAddress(glCopyBufferSubDataNV, "glCopyBufferSubDataNV");
			FetchProcAddress(NV_copy_buffer, "NV_copy_buffer");

			//copy_depth_to_color
			FetchProcAddress(NV_copy_depth_to_color, "NV_copy_depth_to_color");

			//copy_image
			FetchProcAddress(glCopyImageSubDataNV, "glCopyImageSubDataNV");
			FetchProcAddress(NV_copy_image, "NV_copy_image");

			//deep_texture3D
			FetchProcAddress(NV_deep_texture3D, "NV_deep_texture3D");

			//depth_buffer_float
			FetchProcAddress(glClearDepthdNV, "glClearDepthdNV");
			FetchProcAddress(glDepthBoundsdNV, "glDepthBoundsdNV");
			FetchProcAddress(glDepthRangedNV, "glDepthRangedNV");
			FetchProcAddress(NV_depth_buffer_float, "NV_depth_buffer_float");

			//depth_clamp
			FetchProcAddress(NV_depth_clamp, "NV_depth_clamp");

			//depth_range_unclamped
			FetchProcAddress(NV_depth_range_unclamped, "NV_depth_range_unclamped");

			//draw_buffers
			FetchProcAddress(glDrawBuffersNV, "glDrawBuffersNV");
			FetchProcAddress(NV_draw_buffers, "NV_draw_buffers");

			//draw_instanced
			FetchProcAddress(glDrawArraysInstancedNV, "glDrawArraysInstancedNV");
			FetchProcAddress(glDrawElementsInstancedNV, "glDrawElementsInstancedNV");
			FetchProcAddress(NV_draw_instanced, "NV_draw_instanced");

			//draw_texture
			FetchProcAddress(glDrawTextureNV, "glDrawTextureNV");
			FetchProcAddress(NV_draw_texture, "NV_draw_texture");

			//draw_vulkan_image
			FetchProcAddress(glDrawVkImageNV, "glDrawVkImageNV");
			FetchProcAddress(glGetVkProcAddrNV, "glGetVkProcAddrNV");
			FetchProcAddress(glSignalVkFenceNV, "glSignalVkFenceNV");
			FetchProcAddress(glSignalVkSemaphoreNV, "glSignalVkSemaphoreNV");
			FetchProcAddress(glWaitVkSemaphoreNV, "glWaitVkSemaphoreNV");
			FetchProcAddress(NV_draw_vulkan_image, "NV_draw_vulkan_image");

			//evaluators
			FetchProcAddress(glEvalMapsNV, "glEvalMapsNV");
			FetchProcAddress(glGetMapAttribParameterfvNV, "glGetMapAttribParameterfvNV");
			FetchProcAddress(glGetMapAttribParameterivNV, "glGetMapAttribParameterivNV");
			FetchProcAddress(glGetMapControlPointsNV, "glGetMapControlPointsNV");
			FetchProcAddress(glGetMapParameterfvNV, "glGetMapParameterfvNV");
			FetchProcAddress(glGetMapParameterivNV, "glGetMapParameterivNV");
			FetchProcAddress(glMapControlPointsNV, "glMapControlPointsNV");
			FetchProcAddress(glMapParameterfvNV, "glMapParameterfvNV");
			FetchProcAddress(glMapParameterivNV, "glMapParameterivNV");
			FetchProcAddress(NV_evaluators, "NV_evaluators");

			//explicit_attrib_location
			FetchProcAddress(NV_explicit_attrib_location, "NV_explicit_attrib_location");

			//explicit_multisample
			FetchProcAddress(glGetMultisamplefvNV, "glGetMultisamplefvNV");
			FetchProcAddress(glSampleMaskIndexedNV, "glSampleMaskIndexedNV");
			FetchProcAddress(glTexRenderbufferNV, "glTexRenderbufferNV");
			FetchProcAddress(NV_explicit_multisample, "NV_explicit_multisample");

			//fbo_color_attachments
			FetchProcAddress(NV_fbo_color_attachments, "NV_fbo_color_attachments");

			//fence
			FetchProcAddress(glDeleteFencesNV, "glDeleteFencesNV");
			FetchProcAddress(glFinishFenceNV, "glFinishFenceNV");
			FetchProcAddress(glGenFencesNV, "glGenFencesNV");
			FetchProcAddress(glGetFenceivNV, "glGetFenceivNV");
			FetchProcAddress(glIsFenceNV, "glIsFenceNV");
			FetchProcAddress(glSetFenceNV, "glSetFenceNV");
			FetchProcAddress(glTestFenceNV, "glTestFenceNV");
			FetchProcAddress(NV_fence, "NV_fence");

			//fill_rectangle
			FetchProcAddress(NV_fill_rectangle, "NV_fill_rectangle");

			//float_buffer
			FetchProcAddress(NV_float_buffer, "NV_float_buffer");

			//fog_distance
			FetchProcAddress(NV_fog_distance, "NV_fog_distance");

			//fragment_coverage_to_color
			FetchProcAddress(glFragmentCoverageColorNV, "glFragmentCoverageColorNV");
			FetchProcAddress(NV_fragment_coverage_to_color, "NV_fragment_coverage_to_color");

			//fragment_program
			FetchProcAddress(glGetProgramNamedParameterdvNV, "glGetProgramNamedParameterdvNV");
			FetchProcAddress(glGetProgramNamedParameterfvNV, "glGetProgramNamedParameterfvNV");
			FetchProcAddress(glProgramNamedParameter4dNV, "glProgramNamedParameter4dNV");
			FetchProcAddress(glProgramNamedParameter4dvNV, "glProgramNamedParameter4dvNV");
			FetchProcAddress(glProgramNamedParameter4fNV, "glProgramNamedParameter4fNV");
			FetchProcAddress(glProgramNamedParameter4fvNV, "glProgramNamedParameter4fvNV");
			FetchProcAddress(NV_fragment_program, "NV_fragment_program");

			//fragment_program2
			FetchProcAddress(NV_fragment_program2, "NV_fragment_program2");

			//fragment_program4
			FetchProcAddress(NV_fragment_program4, "NV_fragment_program4");

			//fragment_program_option
			FetchProcAddress(NV_fragment_program_option, "NV_fragment_program_option");

			//fragment_shader_interlock
			FetchProcAddress(NV_fragment_shader_interlock, "NV_fragment_shader_interlock");

			//framebuffer_blit
			FetchProcAddress(glBlitFramebufferNV, "glBlitFramebufferNV");
			FetchProcAddress(NV_framebuffer_blit, "NV_framebuffer_blit");

			//framebuffer_mixed_samples
			FetchProcAddress(NV_framebuffer_mixed_samples, "NV_framebuffer_mixed_samples");

			//framebuffer_multisample
			FetchProcAddress(glRenderbufferStorageMultisampleNV, "glRenderbufferStorageMultisampleNV");
			FetchProcAddress(NV_framebuffer_multisample, "NV_framebuffer_multisample");

			//framebuffer_multisample_coverage
			FetchProcAddress(glRenderbufferStorageMultisampleCoverageNV, "glRenderbufferStorageMultisampleCoverageNV");
			FetchProcAddress(NV_framebuffer_multisample_coverage, "NV_framebuffer_multisample_coverage");

			//generate_mipmap_sRGB
			FetchProcAddress(NV_generate_mipmap_sRGB, "NV_generate_mipmap_sRGB");

			//geometry_program4
			FetchProcAddress(glProgramVertexLimitNV, "glProgramVertexLimitNV");
			FetchProcAddress(NV_geometry_program4, "NV_geometry_program4");

			//geometry_shader4
			FetchProcAddress(NV_geometry_shader4, "NV_geometry_shader4");

			//geometry_shader_passthrough
			FetchProcAddress(NV_geometry_shader_passthrough, "NV_geometry_shader_passthrough");

			//gpu_multicast
			FetchProcAddress(glMulticastBarrierNV, "glMulticastBarrierNV");
			FetchProcAddress(glMulticastBlitFramebufferNV, "glMulticastBlitFramebufferNV");
			FetchProcAddress(glMulticastBufferSubDataNV, "glMulticastBufferSubDataNV");
			FetchProcAddress(glMulticastCopyBufferSubDataNV, "glMulticastCopyBufferSubDataNV");
			FetchProcAddress(glMulticastCopyImageSubDataNV, "glMulticastCopyImageSubDataNV");
			FetchProcAddress(glMulticastFramebufferSampleLocationsfvNV, "glMulticastFramebufferSampleLocationsfvNV");
			FetchProcAddress(glMulticastGetQueryObjecti64vNV, "glMulticastGetQueryObjecti64vNV");
			FetchProcAddress(glMulticastGetQueryObjectivNV, "glMulticastGetQueryObjectivNV");
			FetchProcAddress(glMulticastGetQueryObjectui64vNV, "glMulticastGetQueryObjectui64vNV");
			FetchProcAddress(glMulticastGetQueryObjectuivNV, "glMulticastGetQueryObjectuivNV");
			FetchProcAddress(glMulticastWaitSyncNV, "glMulticastWaitSyncNV");
			FetchProcAddress(glRenderGpuMaskNV, "glRenderGpuMaskNV");
			FetchProcAddress(NV_gpu_multicast, "NV_gpu_multicast");

			//gpu_program4
			FetchProcAddress(glProgramEnvParameterI4iNV, "glProgramEnvParameterI4iNV");
			FetchProcAddress(glProgramEnvParameterI4ivNV, "glProgramEnvParameterI4ivNV");
			FetchProcAddress(glProgramEnvParameterI4uiNV, "glProgramEnvParameterI4uiNV");
			FetchProcAddress(glProgramEnvParameterI4uivNV, "glProgramEnvParameterI4uivNV");
			FetchProcAddress(glProgramEnvParametersI4ivNV, "glProgramEnvParametersI4ivNV");
			FetchProcAddress(glProgramEnvParametersI4uivNV, "glProgramEnvParametersI4uivNV");
			FetchProcAddress(glProgramLocalParameterI4iNV, "glProgramLocalParameterI4iNV");
			FetchProcAddress(glProgramLocalParameterI4ivNV, "glProgramLocalParameterI4ivNV");
			FetchProcAddress(glProgramLocalParameterI4uiNV, "glProgramLocalParameterI4uiNV");
			FetchProcAddress(glProgramLocalParameterI4uivNV, "glProgramLocalParameterI4uivNV");
			FetchProcAddress(glProgramLocalParametersI4ivNV, "glProgramLocalParametersI4ivNV");
			FetchProcAddress(glProgramLocalParametersI4uivNV, "glProgramLocalParametersI4uivNV");
			FetchProcAddress(NV_gpu_program4, "NV_gpu_program4");

			//gpu_program5
			FetchProcAddress(NV_gpu_program5, "NV_gpu_program5");

			//gpu_program5_mem_extended
			FetchProcAddress(NV_gpu_program5_mem_extended, "NV_gpu_program5_mem_extended");

			//gpu_program_fp64
			FetchProcAddress(NV_gpu_program_fp64, "NV_gpu_program_fp64");

			//gpu_shader5
			FetchProcAddress(glGetUniformi64vNV, "glGetUniformi64vNV");
			FetchProcAddress(glGetUniformui64vNV, "glGetUniformui64vNV");
			FetchProcAddress(glProgramUniform1i64NV, "glProgramUniform1i64NV");
			FetchProcAddress(glProgramUniform1i64vNV, "glProgramUniform1i64vNV");
			FetchProcAddress(glProgramUniform1ui64NV, "glProgramUniform1ui64NV");
			FetchProcAddress(glProgramUniform1ui64vNV, "glProgramUniform1ui64vNV");
			FetchProcAddress(glProgramUniform2i64NV, "glProgramUniform2i64NV");
			FetchProcAddress(glProgramUniform2i64vNV, "glProgramUniform2i64vNV");
			FetchProcAddress(glProgramUniform2ui64NV, "glProgramUniform2ui64NV");
			FetchProcAddress(glProgramUniform2ui64vNV, "glProgramUniform2ui64vNV");
			FetchProcAddress(glProgramUniform3i64NV, "glProgramUniform3i64NV");
			FetchProcAddress(glProgramUniform3i64vNV, "glProgramUniform3i64vNV");
			FetchProcAddress(glProgramUniform3ui64NV, "glProgramUniform3ui64NV");
			FetchProcAddress(glProgramUniform3ui64vNV, "glProgramUniform3ui64vNV");
			FetchProcAddress(glProgramUniform4i64NV, "glProgramUniform4i64NV");
			FetchProcAddress(glProgramUniform4i64vNV, "glProgramUniform4i64vNV");
			FetchProcAddress(glProgramUniform4ui64NV, "glProgramUniform4ui64NV");
			FetchProcAddress(glProgramUniform4ui64vNV, "glProgramUniform4ui64vNV");
			FetchProcAddress(glUniform1i64NV, "glUniform1i64NV");
			FetchProcAddress(glUniform1i64vNV, "glUniform1i64vNV");
			FetchProcAddress(glUniform1ui64NV, "glUniform1ui64NV");
			FetchProcAddress(glUniform1ui64vNV, "glUniform1ui64vNV");
			FetchProcAddress(glUniform2i64NV, "glUniform2i64NV");
			FetchProcAddress(glUniform2i64vNV, "glUniform2i64vNV");
			FetchProcAddress(glUniform2ui64NV, "glUniform2ui64NV");
			FetchProcAddress(glUniform2ui64vNV, "glUniform2ui64vNV");
			FetchProcAddress(glUniform3i64NV, "glUniform3i64NV");
			FetchProcAddress(glUniform3i64vNV, "glUniform3i64vNV");
			FetchProcAddress(glUniform3ui64NV, "glUniform3ui64NV");
			FetchProcAddress(glUniform3ui64vNV, "glUniform3ui64vNV");
			FetchProcAddress(glUniform4i64NV, "glUniform4i64NV");
			FetchProcAddress(glUniform4i64vNV, "glUniform4i64vNV");
			FetchProcAddress(glUniform4ui64NV, "glUniform4ui64NV");
			FetchProcAddress(glUniform4ui64vNV, "glUniform4ui64vNV");
			FetchProcAddress(NV_gpu_shader5, "NV_gpu_shader5");

			//half_float
			FetchProcAddress(glColor3hNV, "glColor3hNV");
			FetchProcAddress(glColor3hvNV, "glColor3hvNV");
			FetchProcAddress(glColor4hNV, "glColor4hNV");
			FetchProcAddress(glColor4hvNV, "glColor4hvNV");
			FetchProcAddress(glFogCoordhNV, "glFogCoordhNV");
			FetchProcAddress(glFogCoordhvNV, "glFogCoordhvNV");
			FetchProcAddress(glMultiTexCoord1hNV, "glMultiTexCoord1hNV");
			FetchProcAddress(glMultiTexCoord1hvNV, "glMultiTexCoord1hvNV");
			FetchProcAddress(glMultiTexCoord2hNV, "glMultiTexCoord2hNV");
			FetchProcAddress(glMultiTexCoord2hvNV, "glMultiTexCoord2hvNV");
			FetchProcAddress(glMultiTexCoord3hNV, "glMultiTexCoord3hNV");
			FetchProcAddress(glMultiTexCoord3hvNV, "glMultiTexCoord3hvNV");
			FetchProcAddress(glMultiTexCoord4hNV, "glMultiTexCoord4hNV");
			FetchProcAddress(glMultiTexCoord4hvNV, "glMultiTexCoord4hvNV");
			FetchProcAddress(glNormal3hNV, "glNormal3hNV");
			FetchProcAddress(glNormal3hvNV, "glNormal3hvNV");
			FetchProcAddress(glSecondaryColor3hNV, "glSecondaryColor3hNV");
			FetchProcAddress(glSecondaryColor3hvNV, "glSecondaryColor3hvNV");
			FetchProcAddress(glTexCoord1hNV, "glTexCoord1hNV");
			FetchProcAddress(glTexCoord1hvNV, "glTexCoord1hvNV");
			FetchProcAddress(glTexCoord2hNV, "glTexCoord2hNV");
			FetchProcAddress(glTexCoord2hvNV, "glTexCoord2hvNV");
			FetchProcAddress(glTexCoord3hNV, "glTexCoord3hNV");
			FetchProcAddress(glTexCoord3hvNV, "glTexCoord3hvNV");
			FetchProcAddress(glTexCoord4hNV, "glTexCoord4hNV");
			FetchProcAddress(glTexCoord4hvNV, "glTexCoord4hvNV");
			FetchProcAddress(glVertex2hNV, "glVertex2hNV");
			FetchProcAddress(glVertex2hvNV, "glVertex2hvNV");
			FetchProcAddress(glVertex3hNV, "glVertex3hNV");
			FetchProcAddress(glVertex3hvNV, "glVertex3hvNV");
			FetchProcAddress(glVertex4hNV, "glVertex4hNV");
			FetchProcAddress(glVertex4hvNV, "glVertex4hvNV");
			FetchProcAddress(glVertexAttrib1hNV, "glVertexAttrib1hNV");
			FetchProcAddress(glVertexAttrib1hvNV, "glVertexAttrib1hvNV");
			FetchProcAddress(glVertexAttrib2hNV, "glVertexAttrib2hNV");
			FetchProcAddress(glVertexAttrib2hvNV, "glVertexAttrib2hvNV");
			FetchProcAddress(glVertexAttrib3hNV, "glVertexAttrib3hNV");
			FetchProcAddress(glVertexAttrib3hvNV, "glVertexAttrib3hvNV");
			FetchProcAddress(glVertexAttrib4hNV, "glVertexAttrib4hNV");
			FetchProcAddress(glVertexAttrib4hvNV, "glVertexAttrib4hvNV");
			FetchProcAddress(glVertexAttribs1hvNV, "glVertexAttribs1hvNV");
			FetchProcAddress(glVertexAttribs2hvNV, "glVertexAttribs2hvNV");
			FetchProcAddress(glVertexAttribs3hvNV, "glVertexAttribs3hvNV");
			FetchProcAddress(glVertexAttribs4hvNV, "glVertexAttribs4hvNV");
			FetchProcAddress(glVertexWeighthNV, "glVertexWeighthNV");
			FetchProcAddress(glVertexWeighthvNV, "glVertexWeighthvNV");

			//half_float
			FetchProcAddress(NV_half_float, "NV_half_float");

			//image_formats
			FetchProcAddress(NV_image_formats, "NV_image_formats");

			//instanced_arrays
			FetchProcAddress(glVertexAttribDivisorNV, "glVertexAttribDivisorNV");
			FetchProcAddress(NV_instanced_arrays, "NV_instanced_arrays");

			//internalformat_sample_query
			FetchProcAddress(glGetInternalformatSampleivNV, "glGetInternalformatSampleivNV");
			FetchProcAddress(NV_internalformat_sample_query, "NV_internalformat_sample_query");

			//light_max_exponent
			FetchProcAddress(NV_light_max_exponent, "NV_light_max_exponent");

			//multisample_coverage
			FetchProcAddress(NV_multisample_coverage, "NV_multisample_coverage");

			//multisample_filter_hint
			FetchProcAddress(NV_multisample_filter_hint, "NV_multisample_filter_hint");

			//non_square_matrices
			FetchProcAddress(glUniformMatrix2x3fvNV, "glUniformMatrix2x3fvNV");
			FetchProcAddress(glUniformMatrix2x4fvNV, "glUniformMatrix2x4fvNV");
			FetchProcAddress(glUniformMatrix3x2fvNV, "glUniformMatrix3x2fvNV");
			FetchProcAddress(glUniformMatrix3x4fvNV, "glUniformMatrix3x4fvNV");
			FetchProcAddress(glUniformMatrix4x2fvNV, "glUniformMatrix4x2fvNV");
			FetchProcAddress(glUniformMatrix4x3fvNV, "glUniformMatrix4x3fvNV");
			FetchProcAddress(NV_non_square_matrices, "NV_non_square_matrices");

			//occlusion_query
			FetchProcAddress(glBeginOcclusionQueryNV, "glBeginOcclusionQueryNV");
			FetchProcAddress(glDeleteOcclusionQueriesNV, "glDeleteOcclusionQueriesNV");
			FetchProcAddress(glEndOcclusionQueryNV, "glEndOcclusionQueryNV");
			FetchProcAddress(glGenOcclusionQueriesNV, "glGenOcclusionQueriesNV");
			FetchProcAddress(glGetOcclusionQueryivNV, "glGetOcclusionQueryivNV");
			FetchProcAddress(glGetOcclusionQueryuivNV, "glGetOcclusionQueryuivNV");
			FetchProcAddress(glIsOcclusionQueryNV, "glIsOcclusionQueryNV");
			FetchProcAddress(NV_occlusion_query, "NV_occlusion_query");

			//pack_subimage
			FetchProcAddress(NV_pack_subimage, "NV_pack_subimage");

			//packed_depth_stencil
			FetchProcAddress(NV_packed_depth_stencil, "NV_packed_depth_stencil");

			//packed_float
			FetchProcAddress(NV_packed_float, "NV_packed_float");

			//packed_float_linear
			FetchProcAddress(NV_packed_float_linear, "NV_packed_float_linear");

			//parameter_buffer_object
			FetchProcAddress(glProgramBufferParametersIivNV, "glProgramBufferParametersIivNV");
			FetchProcAddress(glProgramBufferParametersIuivNV, "glProgramBufferParametersIuivNV");
			FetchProcAddress(glProgramBufferParametersfvNV, "glProgramBufferParametersfvNV");
			FetchProcAddress(NV_parameter_buffer_object, "NV_parameter_buffer_object");

			//parameter_buffer_object2
			FetchProcAddress(NV_parameter_buffer_object2, "NV_parameter_buffer_object2");

			//path_rendering
			FetchProcAddress(glCopyPathNV, "glCopyPathNV");
			FetchProcAddress(glCoverFillPathInstancedNV, "glCoverFillPathInstancedNV");
			FetchProcAddress(glCoverFillPathNV, "glCoverFillPathNV");
			FetchProcAddress(glCoverStrokePathInstancedNV, "glCoverStrokePathInstancedNV");
			FetchProcAddress(glCoverStrokePathNV, "glCoverStrokePathNV");
			FetchProcAddress(glDeletePathsNV, "glDeletePathsNV");
			FetchProcAddress(glGenPathsNV, "glGenPathsNV");
			FetchProcAddress(glGetPathColorGenfvNV, "glGetPathColorGenfvNV");
			FetchProcAddress(glGetPathColorGenivNV, "glGetPathColorGenivNV");
			FetchProcAddress(glGetPathCommandsNV, "glGetPathCommandsNV");
			FetchProcAddress(glGetPathCoordsNV, "glGetPathCoordsNV");
			FetchProcAddress(glGetPathDashArrayNV, "glGetPathDashArrayNV");
			FetchProcAddress(glGetPathLengthNV, "glGetPathLengthNV");
			FetchProcAddress(glGetPathMetricRangeNV, "glGetPathMetricRangeNV");
			FetchProcAddress(glGetPathMetricsNV, "glGetPathMetricsNV");
			FetchProcAddress(glGetPathParameterfvNV, "glGetPathParameterfvNV");
			FetchProcAddress(glGetPathParameterivNV, "glGetPathParameterivNV");
			FetchProcAddress(glGetPathSpacingNV, "glGetPathSpacingNV");
			FetchProcAddress(glGetPathTexGenfvNV, "glGetPathTexGenfvNV");
			FetchProcAddress(glGetPathTexGenivNV, "glGetPathTexGenivNV");
			FetchProcAddress(glGetProgramResourcefvNV, "glGetProgramResourcefvNV");
			FetchProcAddress(glInterpolatePathsNV, "glInterpolatePathsNV");
			FetchProcAddress(glIsPathNV, "glIsPathNV");
			FetchProcAddress(glIsPointInFillPathNV, "glIsPointInFillPathNV");
			FetchProcAddress(glIsPointInStrokePathNV, "glIsPointInStrokePathNV");
			FetchProcAddress(glMatrixLoad3x2fNV, "glMatrixLoad3x2fNV");
			FetchProcAddress(glMatrixLoad3x3fNV, "glMatrixLoad3x3fNV");
			FetchProcAddress(glMatrixLoadTranspose3x3fNV, "glMatrixLoadTranspose3x3fNV");
			FetchProcAddress(glMatrixMult3x2fNV, "glMatrixMult3x2fNV");
			FetchProcAddress(glMatrixMult3x3fNV, "glMatrixMult3x3fNV");
			FetchProcAddress(glMatrixMultTranspose3x3fNV, "glMatrixMultTranspose3x3fNV");
			FetchProcAddress(glPathColorGenNV, "glPathColorGenNV");
			FetchProcAddress(glPathCommandsNV, "glPathCommandsNV");
			FetchProcAddress(glPathCoordsNV, "glPathCoordsNV");
			FetchProcAddress(glPathCoverDepthFuncNV, "glPathCoverDepthFuncNV");
			FetchProcAddress(glPathDashArrayNV, "glPathDashArrayNV");
			FetchProcAddress(glPathFogGenNV, "glPathFogGenNV");
			FetchProcAddress(glPathGlyphIndexArrayNV, "glPathGlyphIndexArrayNV");
			FetchProcAddress(glPathGlyphIndexRangeNV, "glPathGlyphIndexRangeNV");
			FetchProcAddress(glPathGlyphRangeNV, "glPathGlyphRangeNV");
			FetchProcAddress(glPathGlyphsNV, "glPathGlyphsNV");
			FetchProcAddress(glPathMemoryGlyphIndexArrayNV, "glPathMemoryGlyphIndexArrayNV");
			FetchProcAddress(glPathParameterfNV, "glPathParameterfNV");
			FetchProcAddress(glPathParameterfvNV, "glPathParameterfvNV");
			FetchProcAddress(glPathParameteriNV, "glPathParameteriNV");
			FetchProcAddress(glPathParameterivNV, "glPathParameterivNV");
			FetchProcAddress(glPathStencilDepthOffsetNV, "glPathStencilDepthOffsetNV");
			FetchProcAddress(glPathStencilFuncNV, "glPathStencilFuncNV");
			FetchProcAddress(glPathStringNV, "glPathStringNV");
			FetchProcAddress(glPathSubCommandsNV, "glPathSubCommandsNV");
			FetchProcAddress(glPathSubCoordsNV, "glPathSubCoordsNV");
			FetchProcAddress(glPathTexGenNV, "glPathTexGenNV");
			FetchProcAddress(glPointAlongPathNV, "glPointAlongPathNV");
			FetchProcAddress(glProgramPathFragmentInputGenNV, "glProgramPathFragmentInputGenNV");
			FetchProcAddress(glStencilFillPathInstancedNV, "glStencilFillPathInstancedNV");
			FetchProcAddress(glStencilFillPathNV, "glStencilFillPathNV");
			FetchProcAddress(glStencilStrokePathInstancedNV, "glStencilStrokePathInstancedNV");
			FetchProcAddress(glStencilStrokePathNV, "glStencilStrokePathNV");
			FetchProcAddress(glStencilThenCoverFillPathInstancedNV, "glStencilThenCoverFillPathInstancedNV");
			FetchProcAddress(glStencilThenCoverFillPathNV, "glStencilThenCoverFillPathNV");
			FetchProcAddress(glStencilThenCoverStrokePathInstancedNV, "glStencilThenCoverStrokePathInstancedNV");
			FetchProcAddress(glStencilThenCoverStrokePathNV, "glStencilThenCoverStrokePathNV");
			FetchProcAddress(glTransformPathNV, "glTransformPathNV");
			FetchProcAddress(glWeightPathsNV, "glWeightPathsNV");
			FetchProcAddress(NV_path_rendering, "NV_path_rendering");

			//path_rendering_shared_edge
			FetchProcAddress(NV_path_rendering_shared_edge, "NV_path_rendering_shared_edge");

			//pixel_buffer_object
			FetchProcAddress(NV_pixel_buffer_object, "NV_pixel_buffer_object");

			//pixel_data_range
			FetchProcAddress(glFlushPixelDataRangeNV, "glFlushPixelDataRangeNV");
			FetchProcAddress(glPixelDataRangeNV, "glPixelDataRangeNV");
			FetchProcAddress(NV_pixel_data_range, "NV_pixel_data_range");

			//platform_binary
			FetchProcAddress(NV_platform_binary, "NV_platform_binary");

			//point_sprite
			FetchProcAddress(glPointParameteriNV, "glPointParameteriNV");
			FetchProcAddress(glPointParameterivNV, "glPointParameterivNV");
			FetchProcAddress(NV_point_sprite, "NV_point_sprite");

			//polygon_mode
			FetchProcAddress(glPolygonModeNV, "glPolygonModeNV");
			FetchProcAddress(NV_polygon_mode, "NV_polygon_mode");

			//present_video
			FetchProcAddress(glGetVideoi64vNV, "glGetVideoi64vNV");
			FetchProcAddress(glGetVideoivNV, "glGetVideoivNV");
			FetchProcAddress(glGetVideoui64vNV, "glGetVideoui64vNV");
			FetchProcAddress(glGetVideouivNV, "glGetVideouivNV");
			FetchProcAddress(glPresentFrameDualFillNV, "glPresentFrameDualFillNV");
			FetchProcAddress(glPresentFrameKeyedNV, "glPresentFrameKeyedNV");
			FetchProcAddress(NV_present_video, "NV_present_video");

			//primitive_restart
			FetchProcAddress(glPrimitiveRestartIndexNV, "glPrimitiveRestartIndexNV");
			FetchProcAddress(glPrimitiveRestartNV, "glPrimitiveRestartNV");
			FetchProcAddress(NV_primitive_restart, "NV_primitive_restart");

			//read_depth
			FetchProcAddress(NV_read_depth, "NV_read_depth");

			//read_depth_stencil
			FetchProcAddress(NV_read_depth_stencil, "NV_read_depth_stencil");

			//read_stencil
			FetchProcAddress(NV_read_stencil, "NV_read_stencil");

			//register_combiners
			FetchProcAddress(glCombinerInputNV, "glCombinerInputNV");
			FetchProcAddress(glCombinerOutputNV, "glCombinerOutputNV");
			FetchProcAddress(glCombinerParameterfNV, "glCombinerParameterfNV");
			FetchProcAddress(glCombinerParameterfvNV, "glCombinerParameterfvNV");
			FetchProcAddress(glCombinerParameteriNV, "glCombinerParameteriNV");
			FetchProcAddress(glCombinerParameterivNV, "glCombinerParameterivNV");
			FetchProcAddress(glFinalCombinerInputNV, "glFinalCombinerInputNV");
			FetchProcAddress(glGetCombinerInputParameterfvNV, "glGetCombinerInputParameterfvNV");
			FetchProcAddress(glGetCombinerInputParameterivNV, "glGetCombinerInputParameterivNV");
			FetchProcAddress(glGetCombinerOutputParameterfvNV, "glGetCombinerOutputParameterfvNV");
			FetchProcAddress(glGetCombinerOutputParameterivNV, "glGetCombinerOutputParameterivNV");
			FetchProcAddress(glGetFinalCombinerInputParameterfvNV, "glGetFinalCombinerInputParameterfvNV");
			FetchProcAddress(glGetFinalCombinerInputParameterivNV, "glGetFinalCombinerInputParameterivNV");
			FetchProcAddress(NV_register_combiners, "NV_register_combiners");

			//register_combiners2
			FetchProcAddress(glCombinerStageParameterfvNV, "glCombinerStageParameterfvNV");
			FetchProcAddress(glGetCombinerStageParameterfvNV, "glGetCombinerStageParameterfvNV");
			FetchProcAddress(NV_register_combiners2, "NV_register_combiners2");

			//robustness_video_memory_purge
			FetchProcAddress(NV_robustness_video_memory_purge, "NV_robustness_video_memory_purge");

			//sRGB_formats
			FetchProcAddress(NV_sRGB_formats, "NV_sRGB_formats");

			//sample_locations
			FetchProcAddress(glFramebufferSampleLocationsfvNV, "glFramebufferSampleLocationsfvNV");
			FetchProcAddress(glNamedFramebufferSampleLocationsfvNV, "glNamedFramebufferSampleLocationsfvNV");
			FetchProcAddress(NV_sample_locations, "NV_sample_locations");

			//sample_mask_override_coverage
			FetchProcAddress(NV_sample_mask_override_coverage, "NV_sample_mask_override_coverage");

			//shader_atomic_counters
			FetchProcAddress(NV_shader_atomic_counters, "NV_shader_atomic_counters");

			//shader_atomic_float
			FetchProcAddress(NV_shader_atomic_float, "NV_shader_atomic_float");

			//shader_atomic_float64
			FetchProcAddress(NV_shader_atomic_float64, "NV_shader_atomic_float64");

			//shader_atomic_fp16_vector
			FetchProcAddress(NV_shader_atomic_fp16_vector, "NV_shader_atomic_fp16_vector");

			//shader_atomic_int64
			FetchProcAddress(NV_shader_atomic_int64, "NV_shader_atomic_int64");

			//shader_buffer_load
			FetchProcAddress(glGetBufferParameterui64vNV, "glGetBufferParameterui64vNV");
			FetchProcAddress(glGetIntegerui64vNV, "glGetIntegerui64vNV");
			FetchProcAddress(glGetNamedBufferParameterui64vNV, "glGetNamedBufferParameterui64vNV");
			FetchProcAddress(glIsBufferResidentNV, "glIsBufferResidentNV");
			FetchProcAddress(glIsNamedBufferResidentNV, "glIsNamedBufferResidentNV");
			FetchProcAddress(glMakeBufferNonResidentNV, "glMakeBufferNonResidentNV");
			FetchProcAddress(glMakeBufferResidentNV, "glMakeBufferResidentNV");
			FetchProcAddress(glMakeNamedBufferNonResidentNV, "glMakeNamedBufferNonResidentNV");
			FetchProcAddress(glMakeNamedBufferResidentNV, "glMakeNamedBufferResidentNV");
			FetchProcAddress(glProgramUniformui64NV, "glProgramUniformui64NV");
			FetchProcAddress(glProgramUniformui64vNV, "glProgramUniformui64vNV");
			FetchProcAddress(glUniformui64NV, "glUniformui64NV");
			FetchProcAddress(glUniformui64vNV, "glUniformui64vNV");
			FetchProcAddress(NV_shader_buffer_load, "NV_shader_buffer_load");

			//shader_noperspective_interpolation
			FetchProcAddress(NV_shader_noperspective_interpolation, "NV_shader_noperspective_interpolation");

			//shader_storage_buffer_object
			FetchProcAddress(NV_shader_storage_buffer_object, "NV_shader_storage_buffer_object");

			//shader_thread_group
			FetchProcAddress(NV_shader_thread_group, "NV_shader_thread_group");

			//shader_thread_shuffle
			FetchProcAddress(NV_shader_thread_shuffle, "NV_shader_thread_shuffle");

			//shadow_samplers_array
			FetchProcAddress(NV_shadow_samplers_array, "NV_shadow_samplers_array");

			//shadow_samplers_cube
			FetchProcAddress(NV_shadow_samplers_cube, "NV_shadow_samplers_cube");

			//stereo_view_rendering
			FetchProcAddress(NV_stereo_view_rendering, "NV_stereo_view_rendering");

			//tessellation_program5
			FetchProcAddress(NV_tessellation_program5, "NV_tessellation_program5");

			//texgen_emboss
			FetchProcAddress(NV_texgen_emboss, "NV_texgen_emboss");

			//texgen_reflection
			FetchProcAddress(NV_texgen_reflection, "NV_texgen_reflection");

			//texture_array
			FetchProcAddress(glCompressedTexImage3DNV, "glCompressedTexImage3DNV");
			FetchProcAddress(glCompressedTexSubImage3DNV, "glCompressedTexSubImage3DNV");
			FetchProcAddress(glCopyTexSubImage3DNV, "glCopyTexSubImage3DNV");
			FetchProcAddress(glFramebufferTextureLayerNV, "glFramebufferTextureLayerNV");
			FetchProcAddress(glTexImage3DNV, "glTexImage3DNV");
			FetchProcAddress(glTexSubImage3DNV, "glTexSubImage3DNV");
			FetchProcAddress(NV_texture_array, "NV_texture_array");

			//texture_barrier
			FetchProcAddress(glTextureBarrierNV, "glTextureBarrierNV");
			FetchProcAddress(NV_texture_barrier, "NV_texture_barrier");

			//texture_border_clamp
			FetchProcAddress(NV_texture_border_clamp, "NV_texture_border_clamp");

			//texture_compression_latc
			FetchProcAddress(NV_texture_compression_latc, "NV_texture_compression_latc");

			//texture_compression_s3tc
			FetchProcAddress(NV_texture_compression_s3tc, "NV_texture_compression_s3tc");

			//texture_compression_s3tc_update
			FetchProcAddress(NV_texture_compression_s3tc_update, "NV_texture_compression_s3tc_update");

			//texture_compression_vtc
			FetchProcAddress(NV_texture_compression_vtc, "NV_texture_compression_vtc");

			//texture_env_combine4
			FetchProcAddress(NV_texture_env_combine4, "NV_texture_env_combine4");

			//texture_expand_normal
			FetchProcAddress(NV_texture_expand_normal, "NV_texture_expand_normal");

			//texture_multisample
			FetchProcAddress(glTexImage2DMultisampleCoverageNV, "glTexImage2DMultisampleCoverageNV");
			FetchProcAddress(glTexImage3DMultisampleCoverageNV, "glTexImage3DMultisampleCoverageNV");
			FetchProcAddress(glTextureImage2DMultisampleCoverageNV, "glTextureImage2DMultisampleCoverageNV");
			FetchProcAddress(glTextureImage2DMultisampleNV, "glTextureImage2DMultisampleNV");
			FetchProcAddress(glTextureImage3DMultisampleCoverageNV, "glTextureImage3DMultisampleCoverageNV");
			FetchProcAddress(glTextureImage3DMultisampleNV, "glTextureImage3DMultisampleNV");
			FetchProcAddress(NV_texture_multisample, "NV_texture_multisample");

			//texture_npot_2D_mipmap
			FetchProcAddress(NV_texture_npot_2D_mipmap, "NV_texture_npot_2D_mipmap");

			//texture_rectangle
			FetchProcAddress(NV_texture_rectangle, "NV_texture_rectangle");

			//texture_rectangle_compressed
			FetchProcAddress(NV_texture_rectangle_compressed, "NV_texture_rectangle_compressed");

			//texture_shader
			FetchProcAddress(NV_texture_shader, "NV_texture_shader");

			//texture_shader2
			FetchProcAddress(NV_texture_shader2, "NV_texture_shader2");

			//texture_shader3
			FetchProcAddress(NV_texture_shader3, "NV_texture_shader3");

			//transform_feedback
			FetchProcAddress(glActiveVaryingNV, "glActiveVaryingNV");
			FetchProcAddress(glBeginTransformFeedbackNV, "glBeginTransformFeedbackNV");
			FetchProcAddress(glBindBufferBaseNV, "glBindBufferBaseNV");
			FetchProcAddress(glBindBufferOffsetNV, "glBindBufferOffsetNV");
			FetchProcAddress(glBindBufferRangeNV, "glBindBufferRangeNV");
			FetchProcAddress(glEndTransformFeedbackNV, "glEndTransformFeedbackNV");
			FetchProcAddress(glGetActiveVaryingNV, "glGetActiveVaryingNV");
			FetchProcAddress(glGetTransformFeedbackVaryingNV, "glGetTransformFeedbackVaryingNV");
			FetchProcAddress(glGetVaryingLocationNV, "glGetVaryingLocationNV");
			FetchProcAddress(glTransformFeedbackAttribsNV, "glTransformFeedbackAttribsNV");
			FetchProcAddress(glTransformFeedbackVaryingsNV, "glTransformFeedbackVaryingsNV");
			FetchProcAddress(NV_transform_feedback, "NV_transform_feedback");

			//transform_feedback2
			FetchProcAddress(glBindTransformFeedbackNV, "glBindTransformFeedbackNV");
			FetchProcAddress(glDeleteTransformFeedbacksNV, "glDeleteTransformFeedbacksNV");
			FetchProcAddress(glDrawTransformFeedbackNV, "glDrawTransformFeedbackNV");
			FetchProcAddress(glGenTransformFeedbacksNV, "glGenTransformFeedbacksNV");
			FetchProcAddress(glIsTransformFeedbackNV, "glIsTransformFeedbackNV");
			FetchProcAddress(glPauseTransformFeedbackNV, "glPauseTransformFeedbackNV");
			FetchProcAddress(glResumeTransformFeedbackNV, "glResumeTransformFeedbackNV");
			FetchProcAddress(NV_transform_feedback2, "NV_transform_feedback2");

			//uniform_buffer_unified_memory
			FetchProcAddress(NV_uniform_buffer_unified_memory, "NV_uniform_buffer_unified_memory");

			//vdpau_interop
			FetchProcAddress(glVDPAUFiniNV, "glVDPAUFiniNV");
			FetchProcAddress(glVDPAUGetSurfaceivNV, "glVDPAUGetSurfaceivNV");
			FetchProcAddress(glVDPAUInitNV, "glVDPAUInitNV");
			FetchProcAddress(glVDPAUIsSurfaceNV, "glVDPAUIsSurfaceNV");
			FetchProcAddress(glVDPAUMapSurfacesNV, "glVDPAUMapSurfacesNV");
			FetchProcAddress(glVDPAURegisterOutputSurfaceNV, "glVDPAURegisterOutputSurfaceNV");
			FetchProcAddress(glVDPAURegisterVideoSurfaceNV, "glVDPAURegisterVideoSurfaceNV");
			FetchProcAddress(glVDPAUSurfaceAccessNV, "glVDPAUSurfaceAccessNV");
			FetchProcAddress(glVDPAUUnmapSurfacesNV, "glVDPAUUnmapSurfacesNV");
			FetchProcAddress(glVDPAUUnregisterSurfaceNV, "glVDPAUUnregisterSurfaceNV");
			FetchProcAddress(NV_vdpau_interop, "NV_vdpau_interop");

			//vertex_array_range
			FetchProcAddress(glFlushVertexArrayRangeNV, "glFlushVertexArrayRangeNV");
			FetchProcAddress(glVertexArrayRangeNV, "glVertexArrayRangeNV");
			FetchProcAddress(NV_vertex_array_range, "NV_vertex_array_range");

			//vertex_array_range2
			FetchProcAddress(NV_vertex_array_range2, "NV_vertex_array_range2");

			//vertex_attrib_integer_64bit
			FetchProcAddress(glGetVertexAttribLi64vNV, "glGetVertexAttribLi64vNV");
			FetchProcAddress(glGetVertexAttribLui64vNV, "glGetVertexAttribLui64vNV");
			FetchProcAddress(glVertexAttribL1i64NV, "glVertexAttribL1i64NV");
			FetchProcAddress(glVertexAttribL1i64vNV, "glVertexAttribL1i64vNV");
			FetchProcAddress(glVertexAttribL1ui64NV, "glVertexAttribL1ui64NV");
			FetchProcAddress(glVertexAttribL1ui64vNV, "glVertexAttribL1ui64vNV");
			FetchProcAddress(glVertexAttribL2i64NV, "glVertexAttribL2i64NV");
			FetchProcAddress(glVertexAttribL2i64vNV, "glVertexAttribL2i64vNV");
			FetchProcAddress(glVertexAttribL2ui64NV, "glVertexAttribL2ui64NV");
			FetchProcAddress(glVertexAttribL2ui64vNV, "glVertexAttribL2ui64vNV");
			FetchProcAddress(glVertexAttribL3i64NV, "glVertexAttribL3i64NV");
			FetchProcAddress(glVertexAttribL3i64vNV, "glVertexAttribL3i64vNV");
			FetchProcAddress(glVertexAttribL3ui64NV, "glVertexAttribL3ui64NV");
			FetchProcAddress(glVertexAttribL3ui64vNV, "glVertexAttribL3ui64vNV");
			FetchProcAddress(glVertexAttribL4i64NV, "glVertexAttribL4i64NV");
			FetchProcAddress(glVertexAttribL4i64vNV, "glVertexAttribL4i64vNV");
			FetchProcAddress(glVertexAttribL4ui64NV, "glVertexAttribL4ui64NV");
			FetchProcAddress(glVertexAttribL4ui64vNV, "glVertexAttribL4ui64vNV");
			FetchProcAddress(glVertexAttribLFormatNV, "glVertexAttribLFormatNV");
			FetchProcAddress(NV_vertex_attrib_integer_64bit, "NV_vertex_attrib_integer_64bit");

			//vertex_buffer_unified_memory
			FetchProcAddress(glBufferAddressRangeNV, "glBufferAddressRangeNV");
			FetchProcAddress(glColorFormatNV, "glColorFormatNV");
			FetchProcAddress(glEdgeFlagFormatNV, "glEdgeFlagFormatNV");
			FetchProcAddress(glFogCoordFormatNV, "glFogCoordFormatNV");
			FetchProcAddress(glGetIntegerui64i_vNV, "glGetIntegerui64i_vNV");
			FetchProcAddress(glIndexFormatNV, "glIndexFormatNV");
			FetchProcAddress(glNormalFormatNV, "glNormalFormatNV");
			FetchProcAddress(glSecondaryColorFormatNV, "glSecondaryColorFormatNV");
			FetchProcAddress(glTexCoordFormatNV, "glTexCoordFormatNV");
			FetchProcAddress(glVertexAttribFormatNV, "glVertexAttribFormatNV");
			FetchProcAddress(glVertexAttribIFormatNV, "glVertexAttribIFormatNV");
			FetchProcAddress(glVertexFormatNV, "glVertexFormatNV");
			FetchProcAddress(NV_vertex_buffer_unified_memory, "NV_vertex_buffer_unified_memory");

			//vertex_program
			FetchProcAddress(glAreProgramsResidentNV, "glAreProgramsResidentNV");
			FetchProcAddress(glBindProgramNV, "glBindProgramNV");
			FetchProcAddress(glDeleteProgramsNV, "glDeleteProgramsNV");
			FetchProcAddress(glExecuteProgramNV, "glExecuteProgramNV");
			FetchProcAddress(glGenProgramsNV, "glGenProgramsNV");
			FetchProcAddress(glGetProgramParameterdvNV, "glGetProgramParameterdvNV");
			FetchProcAddress(glGetProgramParameterfvNV, "glGetProgramParameterfvNV");
			FetchProcAddress(glGetProgramStringNV, "glGetProgramStringNV");
			FetchProcAddress(glGetProgramivNV, "glGetProgramivNV");
			FetchProcAddress(glGetTrackMatrixivNV, "glGetTrackMatrixivNV");
			FetchProcAddress(glGetVertexAttribPointervNV, "glGetVertexAttribPointervNV");
			FetchProcAddress(glGetVertexAttribdvNV, "glGetVertexAttribdvNV");
			FetchProcAddress(glGetVertexAttribfvNV, "glGetVertexAttribfvNV");
			FetchProcAddress(glGetVertexAttribivNV, "glGetVertexAttribivNV");
			FetchProcAddress(glIsProgramNV, "glIsProgramNV");
			FetchProcAddress(glLoadProgramNV, "glLoadProgramNV");
			FetchProcAddress(glProgramParameter4dNV, "glProgramParameter4dNV");
			FetchProcAddress(glProgramParameter4dvNV, "glProgramParameter4dvNV");
			FetchProcAddress(glProgramParameter4fNV, "glProgramParameter4fNV");
			FetchProcAddress(glProgramParameter4fvNV, "glProgramParameter4fvNV");
			FetchProcAddress(glProgramParameters4dvNV, "glProgramParameters4dvNV");
			FetchProcAddress(glProgramParameters4fvNV, "glProgramParameters4fvNV");
			FetchProcAddress(glRequestResidentProgramsNV, "glRequestResidentProgramsNV");
			FetchProcAddress(glTrackMatrixNV, "glTrackMatrixNV");
			FetchProcAddress(glVertexAttrib1dNV, "glVertexAttrib1dNV");
			FetchProcAddress(glVertexAttrib1dvNV, "glVertexAttrib1dvNV");
			FetchProcAddress(glVertexAttrib1fNV, "glVertexAttrib1fNV");
			FetchProcAddress(glVertexAttrib1fvNV, "glVertexAttrib1fvNV");
			FetchProcAddress(glVertexAttrib1sNV, "glVertexAttrib1sNV");
			FetchProcAddress(glVertexAttrib1svNV, "glVertexAttrib1svNV");
			FetchProcAddress(glVertexAttrib2dNV, "glVertexAttrib2dNV");
			FetchProcAddress(glVertexAttrib2dvNV, "glVertexAttrib2dvNV");
			FetchProcAddress(glVertexAttrib2fNV, "glVertexAttrib2fNV");
			FetchProcAddress(glVertexAttrib2fvNV, "glVertexAttrib2fvNV");
			FetchProcAddress(glVertexAttrib2sNV, "glVertexAttrib2sNV");
			FetchProcAddress(glVertexAttrib2svNV, "glVertexAttrib2svNV");
			FetchProcAddress(glVertexAttrib3dNV, "glVertexAttrib3dNV");
			FetchProcAddress(glVertexAttrib3dvNV, "glVertexAttrib3dvNV");
			FetchProcAddress(glVertexAttrib3fNV, "glVertexAttrib3fNV");
			FetchProcAddress(glVertexAttrib3fvNV, "glVertexAttrib3fvNV");
			FetchProcAddress(glVertexAttrib3sNV, "glVertexAttrib3sNV");
			FetchProcAddress(glVertexAttrib3svNV, "glVertexAttrib3svNV");
			FetchProcAddress(glVertexAttrib4dNV, "glVertexAttrib4dNV");
			FetchProcAddress(glVertexAttrib4dvNV, "glVertexAttrib4dvNV");
			FetchProcAddress(glVertexAttrib4fNV, "glVertexAttrib4fNV");
			FetchProcAddress(glVertexAttrib4fvNV, "glVertexAttrib4fvNV");
			FetchProcAddress(glVertexAttrib4sNV, "glVertexAttrib4sNV");
			FetchProcAddress(glVertexAttrib4svNV, "glVertexAttrib4svNV");
			FetchProcAddress(glVertexAttrib4ubNV, "glVertexAttrib4ubNV");
			FetchProcAddress(glVertexAttrib4ubvNV, "glVertexAttrib4ubvNV");
			FetchProcAddress(glVertexAttribPointerNV, "glVertexAttribPointerNV");
			FetchProcAddress(glVertexAttribs1dvNV, "glVertexAttribs1dvNV");
			FetchProcAddress(glVertexAttribs1fvNV, "glVertexAttribs1fvNV");
			FetchProcAddress(glVertexAttribs1svNV, "glVertexAttribs1svNV");
			FetchProcAddress(glVertexAttribs2dvNV, "glVertexAttribs2dvNV");
			FetchProcAddress(glVertexAttribs2fvNV, "glVertexAttribs2fvNV");
			FetchProcAddress(glVertexAttribs2svNV, "glVertexAttribs2svNV");
			FetchProcAddress(glVertexAttribs3dvNV, "glVertexAttribs3dvNV");
			FetchProcAddress(glVertexAttribs3fvNV, "glVertexAttribs3fvNV");
			FetchProcAddress(glVertexAttribs3svNV, "glVertexAttribs3svNV");
			FetchProcAddress(glVertexAttribs4dvNV, "glVertexAttribs4dvNV");
			FetchProcAddress(glVertexAttribs4fvNV, "glVertexAttribs4fvNV");
			FetchProcAddress(glVertexAttribs4svNV, "glVertexAttribs4svNV");
			FetchProcAddress(glVertexAttribs4ubvNV, "glVertexAttribs4ubvNV");
			FetchProcAddress(NV_vertex_program, "NV_vertex_program");

			//vertex_program1_1
			FetchProcAddress(NV_vertex_program1_1, "NV_vertex_program1_1");

			//vertex_program2
			FetchProcAddress(NV_vertex_program2, "NV_vertex_program2");

			//vertex_program2_option
			FetchProcAddress(NV_vertex_program2_option, "NV_vertex_program2_option");

			//vertex_program3
			FetchProcAddress(NV_vertex_program3, "NV_vertex_program3");

			//vertex_program4
			FetchProcAddress(NV_vertex_program4, "NV_vertex_program4");

			//video_capture
			FetchProcAddress(glBeginVideoCaptureNV, "glBeginVideoCaptureNV");
			FetchProcAddress(glBindVideoCaptureStreamBufferNV, "glBindVideoCaptureStreamBufferNV");
			FetchProcAddress(glBindVideoCaptureStreamTextureNV, "glBindVideoCaptureStreamTextureNV");
			FetchProcAddress(glEndVideoCaptureNV, "glEndVideoCaptureNV");
			FetchProcAddress(glGetVideoCaptureStreamdvNV, "glGetVideoCaptureStreamdvNV");
			FetchProcAddress(glGetVideoCaptureStreamfvNV, "glGetVideoCaptureStreamfvNV");
			FetchProcAddress(glGetVideoCaptureStreamivNV, "glGetVideoCaptureStreamivNV");
			FetchProcAddress(glGetVideoCaptureivNV, "glGetVideoCaptureivNV");
			FetchProcAddress(glVideoCaptureNV, "glVideoCaptureNV");
			FetchProcAddress(glVideoCaptureStreamParameterdvNV, "glVideoCaptureStreamParameterdvNV");
			FetchProcAddress(glVideoCaptureStreamParameterfvNV, "glVideoCaptureStreamParameterfvNV");
			FetchProcAddress(glVideoCaptureStreamParameterivNV, "glVideoCaptureStreamParameterivNV");
			FetchProcAddress(NV_video_capture, "NV_video_capture");

			//viewport_array
			FetchProcAddress(glDepthRangeArrayfvNV, "glDepthRangeArrayfvNV");
			FetchProcAddress(glDepthRangeIndexedfNV, "glDepthRangeIndexedfNV");
			FetchProcAddress(glDisableiNV, "glDisableiNV");
			FetchProcAddress(glEnableiNV, "glEnableiNV");
			FetchProcAddress(glGetFloati_vNV, "glGetFloati_vNV");
			FetchProcAddress(glIsEnablediNV, "glIsEnablediNV");
			FetchProcAddress(glScissorArrayvNV, "glScissorArrayvNV");
			FetchProcAddress(glScissorIndexedNV, "glScissorIndexedNV");
			FetchProcAddress(glScissorIndexedvNV, "glScissorIndexedvNV");
			FetchProcAddress(glViewportArrayvNV, "glViewportArrayvNV");
			FetchProcAddress(glViewportIndexedfNV, "glViewportIndexedfNV");
			FetchProcAddress(glViewportIndexedfvNV, "glViewportIndexedfvNV");
			FetchProcAddress(NV_viewport_array, "NV_viewport_array");

			//viewport_array2
			FetchProcAddress(NV_viewport_array2, "NV_viewport_array2");

			//viewport_swizzle
			FetchProcAddress(glViewportSwizzleNV, "glViewportSwizzleNV");
			FetchProcAddress(NV_viewport_swizzle, "NV_viewport_swizzle");
		}

#pragma endregion NV Extensions

	//OpenGL OES Extensions
#pragma region OES

		//byte coordinates
		bool byte_coordinates = false;

		//*< load OES Extensions
		void LoadOESExtensions()
		{
			//byte coordinates
			FetchProcAddress(byte_coordinates, "FetchProcAddress");
		}		
		
#pragma endregion OES Extensions

	//OpenGL OML Extensions
#pragma region OML 

	enum OpenGL_OML_t
	{
		//interlace
		gl_interlace_oml = 0x8980,
		gl_interlace_read_oml = 0x8981,

		//resample
		gl_pack_resample_oml = 0x8984,
		gl_unpack_resample_oml = 0x8985,
		gl_resample_replicate_oml = 0x8986,
		gl_resample_zero_fill_oml = 0x8987,
		gl_resample_average_oml = 0x8988,
		gl_resample_decimate_oml = 0x8989,

		//subsample
		gl_format_subsample_24_24_oml = 0x8982,
		gl_format_subsample_244_244_oml = 0x8983,
	};

	//interlace
	bool OML_interlace = false;

	//resample
	bool OML_resample = false;

	//subsample
	bool GLEW_OML_subsample = false;

	//*< load OML Extensions
	void LoadOMLExtensions()
	{
		//interlace
		FetchProcAddress(OML_interlace, "");

		//resample
		FetchProcAddress(OML_resample, "");

		//subsample
		FetchProcAddress(GLEW_OML_subsample, "");
	}

#pragma endregion OML Extensions

	//OpenGL OVE Extensions
#pragma region OVR 

	enum OpenGL_OVR_t
	{
		//OVR multiview multisampled render to texture
		gl_framebuffer_attachment_texture_num_views_ovr = 0x9630,
		gl_max_views_ovr = 0x9631,
		gl_framebuffer_attachment_texture_base_view_index_ovr = 0x9632,
		gl_framebuffer_incomplete_view_targets_ovr = 0x9633,
	};

	//multiview
	void (*glFramebufferTextureMultiviewOVR) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint baseViewIndex, GLsizei numViews) = nullptr;
	bool OVR_multiview = false;

	//multiview2
	bool OVR_multiview2 = false;

	//OVR multiview multisampled render to texture
	void (*glFramebufferTextureMultisampleMultiviewOVR) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint baseViewIndex, GLsizei numViews) = nullptr;
	bool OVR_multiview_multisampled_render_to_texture = false;

	//*< load OVR Extensions
	void LoadOVRExtensions()
	{
		//multiview
		FetchProcAddress(glFramebufferTextureMultiviewOVR, "glFramebufferTextureMultiviewOVR");
		FetchProcAddress(OVR_multiview, "OVR_multiview");

		//multiview2
		FetchProcAddress(OVR_multiview2, "OVR_multiview2");

		//OVR multiview multisampled render to texture
		FetchProcAddress(glFramebufferTextureMultisampleMultiviewOVR, "glFramebufferTextureMultisampleMultiviewOVR");
		FetchProcAddress(OVR_multiview_multisampled_render_to_texture, "OVR_multiview_multisampled_render_to_texture");
	}

#pragma endregion OVE Extensions

	//OpenGL PGI Extensions
#pragma region PGI

	enum OpenGL_PGI_t
	{
		//misc_hints
		gl_prefer_doublebuffer_hint_pgi = 107000,
		gl_conserve_memory_hint_pgi = 107005,
		gl_reclaim_memory_hint_pgi = 107006,
		gl_native_graphics_handle_pgi = 107010,
		gl_native_graphics_begin_hint_pgi = 107011,
		gl_native_graphics_end_hint_pgi = 107012,
		gl_always_fast_hint_pgi = 107020,
		gl_always_soft_hint_pgi = 107021,
		gl_allow_draw_obj_hint_pgi = 107022,
		gl_allow_draw_win_hint_pgi = 107023,
		gl_allow_draw_frg_hint_pgi = 107024,
		gl_allow_draw_mem_hint_pgi = 107025,
		gl_strict_depthfunc_hint_pgi = 107030,
		gl_strict_lighting_hint_pgi = 107031,
		gl_strict_scissor_hint_pgi = 107032,
		gl_full_stipple_hint_pgi = 107033,
		gl_clip_near_hint_pgi = 107040,
		gl_clip_far_hint_pgi = 107041,
		gl_wide_line_hint_pgi = 107042,
		gl_back_normals_hint_pgi = 107043,

		//vertex hints
		gl_vertex23_bit_pgi = 0x00000004,
		gl_vertex4_bit_pgi = 0x00000008,
		gl_color3_bit_pgi = 0x00010000,
		gl_color4_bit_pgi = 0x00020000,
		gl_edgeflag_bit_pgi = 0x00040000,
		gl_index_bit_pgi = 0x00080000,
		gl_mat_ambient_bit_pgi = 0x00100000,
		gl_vertex_data_hint_pgi = 107050,
		gl_vertex_consistent_hint_pgi = 107051,
		gl_material_side_hint_pgi = 107052,
		gl_max_vertex_hint_pgi = 107053,
		gl_mat_ambient_and_diffuse_bit_pgi = 0x00200000,
		gl_mat_diffuse_bit_pgi = 0x00400000,
		gl_mat_emission_bit_pgi = 0x00800000,
		gl_mat_color_indexes_bit_pgi = 0x01000000,
		gl_mat_shininess_bit_pgi = 0x02000000,
		gl_mat_specular_bit_pgi = 0x04000000,
		gl_normal_bit_pgi = 0x08000000,
		gl_texcoord1_bit_pgi = 0x10000000,
		gl_texcoord2_bit_pgi = 0x20000000,
		gl_texcoord3_bit_pgi = 0x40000000,
		gl_texcoord4_bit_pgi = 0x80000000,
	};

	//misc_hints
	bool PGI_misc_hints = false;

	//vertex hints
	bool PGI_vertex_hints = false;

	//*< load PGI Extensions
	void LoadPGIExtensions()
	{
		//misc_hints
		FetchProcAddress(PGI_misc_hints, "PGI_misc_hints");

		//vertex hints
		FetchProcAddress(PGI_vertex_hints, "PGI_vertex_hints");
	}	

#pragma endregion PGI Extensions

	//OpenGL QCOM Extensions
#pragma region QCOM

	enum OpenGL_QCOM_t
	{
		//alpha_test
		gl_alpha_test_qcom = 0x0bc0,
		gl_alpha_test_func_qcom = 0x0bc1,
		gl_alpha_test_ref_qcom = 0x0bc2,

		//binning_control
		gl_dont_care = 0x1100,
		gl_binning_control_hint_qcom = 0x8fb0,
		gl_cpu_optimized_qcom = 0x8fb1,
		gl_gpu_optimized_qcom = 0x8fb2,
		gl_render_direct_to_framebuffer_qcom = 0x8fb3,

		//extended_get
		gl_texture_width_qcom = 0x8bd2,
		gl_texture_height_qcom = 0x8bd3,
		gl_texture_depth_qcom = 0x8bd4,
		gl_texture_internal_format_qcom = 0x8bd5,
		gl_texture_format_qcom = 0x8bd6,
		gl_texture_type_qcom = 0x8bd7,
		gl_texture_image_valid_qcom = 0x8bd8,
		gl_texture_num_levels_qcom = 0x8bd9,
		gl_texture_target_qcom = 0x8bda,
		gl_texture_object_valid_qcom = 0x8bdb,
		gl_state_restore = 0x8bdc,

		//framebuffer_foveated
		gl_foveation_enable_bit_qcom = 0x1,
		gl_foveation_scaled_bin_method_bit_qcom = 0x2,

		//perfmon_global_mode
		gl_perfmon_global_mode_qcom = 0x8fa0,

		//shader_framebuffer_fetch_noncoherent
		gl_framebuffer_fetch_noncoherent_qcom = 0x96a2,

		//tiled_rendering
		gl_color_buffer_bit0_qcom = 0x00000001,
		gl_color_buffer_bit1_qcom = 0x00000002,
		gl_color_buffer_bit2_qcom = 0x00000004,
		gl_color_buffer_bit3_qcom = 0x00000008,
		gl_color_buffer_bit4_qcom = 0x00000010,
		gl_color_buffer_bit5_qcom = 0x00000020,
		gl_color_buffer_bit6_qcom = 0x00000040,
		gl_color_buffer_bit7_qcom = 0x00000080,
		gl_depth_buffer_bit0_qcom = 0x00000100,
		gl_depth_buffer_bit1_qcom = 0x00000200,
		gl_depth_buffer_bit2_qcom = 0x00000400,
		gl_depth_buffer_bit3_qcom = 0x00000800,
		gl_depth_buffer_bit4_qcom = 0x00001000,
		gl_depth_buffer_bit5_qcom = 0x00002000,
		gl_depth_buffer_bit6_qcom = 0x00004000,
		gl_depth_buffer_bit7_qcom = 0x00008000,
		gl_stencil_buffer_bit0_qcom = 0x00010000,
		gl_stencil_buffer_bit1_qcom = 0x00020000,
		gl_stencil_buffer_bit2_qcom = 0x00040000,
		gl_stencil_buffer_bit3_qcom = 0x00080000,
		gl_stencil_buffer_bit4_qcom = 0x00100000,
		gl_stencil_buffer_bit5_qcom = 0x00200000,
		gl_stencil_buffer_bit6_qcom = 0x00400000,
		gl_stencil_buffer_bit7_qcom = 0x00800000,
		gl_multisample_buffer_bit0_qcom = 0x01000000,
		gl_multisample_buffer_bit1_qcom = 0x02000000,
		gl_multisample_buffer_bit2_qcom = 0x04000000,
		gl_multisample_buffer_bit3_qcom = 0x08000000,
		gl_multisample_buffer_bit4_qcom = 0x10000000,
		gl_multisample_buffer_bit5_qcom = 0x20000000,
		gl_multisample_buffer_bit6_qcom = 0x40000000,
		gl_multisample_buffer_bit7_qcom = 0x80000000,

		//writeonly_rendering
		gl_writeonly_rendering_qcom = 0x8823,
	};

	//alpha_test
	void (*glAlphaFuncQCOM) (GLenum func, GLclampf ref) = nullptr;
	bool QCOM_alpha_test = false;

	//binning_control
	bool QCOM_binning_control = false;

	//driver_control
	void (*glDisableDriverControlQCOM) (GLuint driverControl) = nullptr;
	void (*glEnableDriverControlQCOM) (GLuint driverControl) = nullptr;
	void (*glGetDriverControlStringQCOM) (GLuint driverControl, GLsizei bufSize, GLsizei* length, GLchar* driverControlString) = nullptr;
	void (*glGetDriverControlsQCOM) (GLint* num, GLsizei size, GLuint* driverControls) = nullptr;

	//driver_control
	bool QCOM_driver_control = false;	

	//extended_get
	void (*glExtGetBufferPointervQCOM) (GLenum target, void** params) = nullptr;
	void (*glExtGetBuffersQCOM) (GLuint* buffers, GLint maxBuffers, GLint* numBuffers) = nullptr;
	void (*glExtGetFramebuffersQCOM) (GLuint* framebuffers, GLint maxFramebuffers, GLint* numFramebuffers) = nullptr;
	void (*glExtGetRenderbuffersQCOM) (GLuint* renderbuffers, GLint maxRenderbuffers, GLint* numRenderbuffers) = nullptr;
	void (*glExtGetTexLevelParameterivQCOM) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint* params) = nullptr;
	void (*glExtGetTexSubImageQCOM) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void* texels) = nullptr;
	void (*glExtGetTexturesQCOM) (GLuint* textures, GLint maxTextures, GLint* numTextures) = nullptr;
	void (*glExtTexObjectStateOverrideiQCOM) (GLenum target, GLenum pname, GLint param) = nullptr;
	bool QCOM_extended_get = false;

	//extended_get2
	void (*glExtGetProgramBinarySourceQCOM) (GLuint program, GLenum shadertype, GLchar * source, GLint * length) = nullptr;
	void (*glExtGetProgramsQCOM) (GLuint* programs, GLint maxPrograms, GLint* numPrograms) = nullptr;
	void (*glExtGetShadersQCOM) (GLuint* shaders, GLint maxShaders, GLint* numShaders) = nullptr;
	GLboolean(*glExtIsProgramBinaryQCOM) (GLuint program) = nullptr;
	bool QCOM_extended_get2 = false;

	//framebuffer_foveated
	void (*glFramebufferFoveationConfigQCOM) (GLuint fbo, GLuint numLayers, GLuint focalPointsPerLayer, GLuint requestedFeatures, GLuint * providedFeatures) = nullptr;
	void (*glFramebufferFoveationParametersQCOM) (GLuint fbo, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea) = nullptr;
	bool QCOM_framebuffer_foveated = false;

	//perfmon_global_mode
	bool QCOM_perfmon_global_mode = false;

	//shader_framebuffer_fetch_noncoherent
	void (*glFramebufferFetchBarrierQCOM) (void) = nullptr;
	bool QCOM_shader_framebuffer_fetch_noncoherent = false;

	//tiled_rendering
	void (*glEndTilingQCOM) (GLbitfield preserveMask) = nullptr;
	void (*glStartTilingQCOM) (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask) = nullptr;
	bool QCOM_tiled_rendering = false;

	//writeonly_rendering
	bool QCOM_writeonly_rendering = false;

	//*< load QCOM Extensions
	void LoadQCOMExtensions()
	{
		//alpha_test
		FetchProcAddress(glAlphaFuncQCOM, "glAlphaFuncQCOM");
		FetchProcAddress(QCOM_alpha_test, "QCOM_alpha_test");

		//binning_control
		FetchProcAddress(QCOM_binning_control, "QCOM_binning_control");

		//driver_control
		FetchProcAddress(glDisableDriverControlQCOM, "glDisableDriverControlQCOM");
		FetchProcAddress(glEnableDriverControlQCOM, "glEnableDriverControlQCOM");
		FetchProcAddress(glGetDriverControlStringQCOM, "glGetDriverControlStringQCOM");
		FetchProcAddress(glGetDriverControlsQCOM, "glGetDriverControlsQCOM");

		//driver_control
		FetchProcAddress(QCOM_driver_control, "QCOM_driver_control");

		//extended_get
		FetchProcAddress(glExtGetBufferPointervQCOM, "glExtGetBufferPointervQCOM");
		FetchProcAddress(glExtGetBuffersQCOM, "glExtGetBuffersQCOM");
		FetchProcAddress(glExtGetFramebuffersQCOM, "glExtGetFramebuffersQCOM");
		FetchProcAddress(glExtGetRenderbuffersQCOM, "glExtGetRenderbuffersQCOM");
		FetchProcAddress(glExtGetTexLevelParameterivQCOM, "glExtGetTexLevelParameterivQCOM");
		FetchProcAddress(glExtGetTexSubImageQCOM, "glExtGetTexSubImageQCOM");
		FetchProcAddress(glExtGetTexturesQCOM, "glExtGetTexturesQCOM");
		FetchProcAddress(glExtTexObjectStateOverrideiQCOM, "glExtTexObjectStateOverrideiQCOM");
		FetchProcAddress(QCOM_extended_get, "QCOM_extended_get");

		//extended_get2
		FetchProcAddress(glExtGetProgramBinarySourceQCOM, "glExtGetProgramBinarySourceQCOM");
		FetchProcAddress(glExtGetProgramsQCOM, "glExtGetProgramsQCOM");
		FetchProcAddress(glExtGetShadersQCOM, "glExtGetShadersQCOM");
		FetchProcAddress(glExtIsProgramBinaryQCOM, "glExtIsProgramBinaryQCOM");
		FetchProcAddress(QCOM_extended_get2, "QCOM_extended_get2");

		//framebuffer_foveated
		FetchProcAddress(glFramebufferFoveationConfigQCOM, "glFramebufferFoveationConfigQCOM");
		FetchProcAddress(glFramebufferFoveationParametersQCOM, "glFramebufferFoveationParametersQCOM");
		FetchProcAddress(QCOM_framebuffer_foveated, "QCOM_framebuffer_foveated");

		//perfmon_global_mode
		FetchProcAddress(QCOM_perfmon_global_mode, "QCOM_perfmon_global_mode");

		//shader_framebuffer_fetch_noncoherent
		FetchProcAddress(glFramebufferFetchBarrierQCOM, "glFramebufferFetchBarrierQCOM");
		FetchProcAddress(QCOM_shader_framebuffer_fetch_noncoherent, "QCOM_shader_framebuffer_fetch_noncoherent");

		//tiled_rendering
		FetchProcAddress(glEndTilingQCOM, "glEndTilingQCOM");
		FetchProcAddress(glStartTilingQCOM, "glStartTilingQCOM");
		FetchProcAddress(QCOM_tiled_rendering, "QCOM_tiled_rendering");

		//writeonly_rendering
		FetchProcAddress(QCOM_writeonly_rendering, "QCOM_writeonly_rendering");
	}

#pragma endregion QCOM Extensions

	//OpenGL Regal Extensions
#pragma region Regal

	typedef int GLclampx;

	enum OpenGL_Regal_t
	{

		//enable
		gl_error_regal = 0x9322,
		gl_debug_regal = 0x9323,
		gl_log_regal = 0x9324,
		gl_emulation_regal = 0x9325,
		gl_driver_regal = 0x9326,
		gl_missing_regal = 0x9360,
		gl_trace_regal = 0x9361,
		gl_cache_regal = 0x9362,
		gl_code_regal = 0x9363,
		gl_statistics_regal = 0x9364,

		//log
		gl_log_error_regal = 0x9319,
		gl_log_warning_regal = 0x931a,
		gl_log_info_regal = 0x931b,
		gl_log_app_regal = 0x931c,
		gl_log_driver_regal = 0x931d,
		gl_log_internal_regal = 0x931e,
		gl_log_debug_regal = 0x931f,
		gl_log_status_regal = 0x9320,
		gl_log_http_regal = 0x9321,
	};

	//ES1_0_compatibility
	void (*glAlphaFuncx) (GLenum func, GLclampx ref) = nullptr;
	void (*glClearColorx) (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha) = nullptr;
	void (*glClearDepthx) (GLclampx depth) = nullptr;
	void (*glColor4x) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) = nullptr;
	void (*glDepthRangex) (GLclampx zNear, GLclampx zFar) = nullptr;
	void (*glFogx) (GLenum pname, GLfixed param) = nullptr;
	void (*glFogxv) (GLenum pname, const GLfixed* params) = nullptr;
	void (*glFrustumf) (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) = nullptr;
	void (*glFrustumx) (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) = nullptr;
	void (*glLightModelx) (GLenum pname, GLfixed param) = nullptr;
	void (*glLightModelxv) (GLenum pname, const GLfixed* params) = nullptr;
	void (*glLightx) (GLenum light, GLenum pname, GLfixed param) = nullptr;
	void (*glLightxv) (GLenum light, GLenum pname, const GLfixed* params) = nullptr;
	void (*glLineWidthx) (GLfixed width) = nullptr;
	void (*glLoadMatrixx) (const GLfixed* m) = nullptr;
	void (*glMaterialx) (GLenum face, GLenum pname, GLfixed param) = nullptr;
	void (*glMaterialxv) (GLenum face, GLenum pname, const GLfixed* params) = nullptr;
	void (*glMultMatrixx) (const GLfixed* m) = nullptr;
	void (*glMultiTexCoord4x) (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q) = nullptr;
	void (*glNormal3x) (GLfixed nx, GLfixed ny, GLfixed nz) = nullptr;
	void (*glOrthof) (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) = nullptr;
	void (*glOrthox) (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) = nullptr;
	void (*glPointSizex) (GLfixed size) = nullptr;
	void (*glPolygonOffsetx) (GLfixed factor, GLfixed units) = nullptr;
	void (*glRotatex) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z) = nullptr;
	void (*glSampleCoveragex) (GLclampx value, GLboolean invert) = nullptr;
	void (*glScalex) (GLfixed x, GLfixed y, GLfixed z) = nullptr;
	void (*glTexEnvx) (GLenum target, GLenum pname, GLfixed param) = nullptr;
	void (*glTexEnvxv) (GLenum target, GLenum pname, const GLfixed* params) = nullptr;
	void (*glTexParameterx) (GLenum target, GLenum pname, GLfixed param) = nullptr;
	void (*glTranslatex) (GLfixed x, GLfixed y, GLfixed z) = nullptr;
	bool REGAL_ES1_0_compatibility = false;

	//ES1_1_compatibility
	void (*glClipPlanef) (GLenum plane, const GLfloat * equation) = nullptr;
	void (*glClipPlanex) (GLenum plane, const GLfixed* equation) = nullptr;
	void (*glGetClipPlanef) (GLenum pname, GLfloat eqn[4]) = nullptr;
	void (*glGetClipPlanex) (GLenum pname, GLfixed eqn[4]) = nullptr;
	void (*glGetFixedv) (GLenum pname, GLfixed* params) = nullptr;
	void (*glGetLightxv) (GLenum light, GLenum pname, GLfixed* params) = nullptr;
	void (*glGetMaterialxv) (GLenum face, GLenum pname, GLfixed* params) = nullptr;
	void (*glGetTexEnvxv) (GLenum env, GLenum pname, GLfixed* params) = nullptr;
	void (*glGetTexParameterxv) (GLenum target, GLenum pname, GLfixed* params) = nullptr;
	void (*glPointParameterx) (GLenum pname, GLfixed param) = nullptr;
	void (*glPointParameterxv) (GLenum pname, const GLfixed* params) = nullptr;
	void (*glPointSizePointerOES) (GLenum type, GLsizei stride, const void* pointer) = nullptr;
	void (*glTexParameterxv) (GLenum target, GLenum pname, const GLfixed* params) = nullptr;
	bool REGAL_ES1_1_compatibility = false;

	//enable
	bool REGAL_enable = false;

	//error_string
	const GLchar * (*glErrorStringREGAL) (GLenum error) = nullptr;
	bool REGAL_error_string = false;

	//extension_query
	GLboolean(*glGetExtensionREGAL) (const GLchar * ext) = nullptr;
	GLboolean(*glIsSupportedREGAL) (const GLchar* ext) = nullptr;
	bool REGAL_extension_query = false;

	//log
	typedef void (GLLOGPROCREGAL)(GLenum stream, GLsizei length, const GLchar * message, void* context);
	void (*glLogMessageCallbackREGAL) (GLLOGPROCREGAL callback) = nullptr;
	bool REGAL_log = false;

	//proc_address
	void* (*glGetProcAddressREGAL) (const GLchar * name) = nullptr;
	bool REGAL_proc_address = false;

	//*< load Regal Extensions
	void LoadRegalExtensions()
	{
		//ES1_0_compatibility
		FetchProcAddress(glAlphaFuncx, "glAlphaFuncx");
		FetchProcAddress(glClearColorx, "glClearColorx");
		FetchProcAddress(glClearDepthx, "glClearDepthx");
		FetchProcAddress(glColor4x, "glColor4x");
		FetchProcAddress(glDepthRangex, "glDepthRangex");
		FetchProcAddress(glFogx, "glFogx");
		FetchProcAddress(glFogxv, "glFogxv");
		FetchProcAddress(glFrustumf, "glFrustumf");
		FetchProcAddress(glFrustumx, "glFrustumx");
		FetchProcAddress(glLightModelx, "glLightModelx");
		FetchProcAddress(glLightModelxv, "glLightModelxv");
		FetchProcAddress(glLightx, "glLightx");
		FetchProcAddress(glLightxv, "glLightxv");
		FetchProcAddress(glLineWidthx, "glLineWidthx");
		FetchProcAddress(glLoadMatrixx, "glLoadMatrixx");
		FetchProcAddress(glMaterialx, "glMaterialx");
		FetchProcAddress(glMaterialxv, "glMaterialxv");
		FetchProcAddress(glMultMatrixx, "glMultMatrixx");
		FetchProcAddress(glMultiTexCoord4x, "glMultiTexCoord4x");
		FetchProcAddress(glNormal3x, "glNormal3x");
		FetchProcAddress(glOrthof, "glOrthof");
		FetchProcAddress(glOrthox, "glOrthox");
		FetchProcAddress(glPointSizex, "glPointSizex");
		FetchProcAddress(glPolygonOffsetx, "glPolygonOffsetx");
		FetchProcAddress(glRotatex, "glRotatex");
		FetchProcAddress(glSampleCoveragex, "glSampleCoveragex");
		FetchProcAddress(glScalex, "glScalex");
		FetchProcAddress(glTexEnvx, "glTexEnvx");
		FetchProcAddress(glTexEnvxv, "glTexEnvxv");
		FetchProcAddress(glTexParameterx, "glTexParameterx");
		FetchProcAddress(glTranslatex, "glTranslatex");
		FetchProcAddress(REGAL_ES1_0_compatibility, "REGAL_ES1_0_compatibility");

		//ES1_1_compatibility
		FetchProcAddress(glClipPlanef, "glClipPlanef");
		FetchProcAddress(glClipPlanex, "glClipPlanex");
		FetchProcAddress(glGetClipPlanef, "glGetClipPlanef");
		FetchProcAddress(glGetClipPlanex, "glGetClipPlanex");
		FetchProcAddress(glGetFixedv, "glGetFixedv");
		FetchProcAddress(glGetLightxv, "glGetLightxv");
		FetchProcAddress(glGetMaterialxv, "glGetMaterialxv");
		FetchProcAddress(glGetTexEnvxv, "glGetTexEnvxv");
		FetchProcAddress(glGetTexParameterxv, "glGetTexParameterxv");
		FetchProcAddress(glPointParameterx, "glPointParameterx");
		FetchProcAddress(glPointParameterxv, "glPointParameterxv");
		FetchProcAddress(glPointSizePointerOES, "glPointSizePointerOES");
		FetchProcAddress(glTexParameterxv, "glTexParameterxv");
		FetchProcAddress(REGAL_ES1_1_compatibility, "REGAL_ES1_1_compatibility");

		//enable
		FetchProcAddress(REGAL_enable, "REGAL_enable");

		//error_string
		FetchProcAddress(glErrorStringREGAL, "glErrorStringREGAL");
		FetchProcAddress(REGAL_error_string, "REGAL_error_string");

		//extension_query
		FetchProcAddress(glGetExtensionREGAL, "glGetExtensionREGAL");
		FetchProcAddress(glIsSupportedREGAL, "glIsSupportedREGAL");
		FetchProcAddress(REGAL_extension_query, "REGAL_extension_query");

		//log
		FetchProcAddress(glLogMessageCallbackREGAL, "glLogMessageCallbackREGAL");
		FetchProcAddress(REGAL_log, "REGAL_log");

		//proc_address
		FetchProcAddress(glGetProcAddressREGAL, "glGetProcAddressREGAL");
		FetchProcAddress(REGAL_proc_address, "REGAL_proc_address");
	}

#pragma endregion Regal Extensions

	//OpenGL REND Extensions
#pragma region REND

	enum OpenGL_REND_t
	{
		//screen_coordinates
		gl_screen_coordinates_rend = 0x8490,
		gl_inverted_screen_w_rend = 0x8491,
	};

	//screen_coordinates
	bool screen_coordinates = false;

	//*< load REND Extensions
	void LoadRENDExtensions()
	{
		FetchProcAddress(screen_coordinates, "screen_coordinates");
	}

#pragma endregion REND Extensions

	//OpenGL S3 Extensions
#pragma region S3

	enum OpenGL_S3_t
	{
		//s3tc
		gl_rgb_s3tc = 0x83a0,
		gl_rgb4_s3tc = 0x83a1,
		gl_rgba_s3tc = 0x83a2,
		gl_rgba4_s3tc = 0x83a3,
		gl_rgba_dxt5_s3tc = 0x83a4,
		gl_rgba4_dxt5_s3tc = 0x83a5,
	};

	//s3tc
	bool S3_s3tc = false;

	//*< load S3 Extensions
	void LoadS3Extensions()
	{
		FetchProcAddress(S3_s3tc, "S3_s3tc");
	}

#pragma endregion S3 Extensions

	//OpenGL SGIS Extensions
#pragma region SGIS

	enum OpenGL_SGIS_t
	{
		//color_range
		gl_extended_range_sgis = 0x85a5,
		gl_min_red_sgis = 0x85a6,
		gl_max_red_sgis = 0x85a7,
		gl_min_green_sgis = 0x85a8,
		gl_max_green_sgis = 0x85a9,
		gl_min_blue_sgis = 0x85aa,
		gl_max_blue_sgis = 0x85ab,
		gl_min_alpha_sgis = 0x85ac,
		gl_max_alpha_sgis = 0x85ad,

		//generate_mipmap
		gl_generate_mipmap_sgis = 0x8191,
		gl_generate_mipmap_hint_sgis = 0x8192,

		//multisample
		gl_multisample_sgis = 0x809d,
		gl_sample_alpha_to_mask_sgis = 0x809e,
		gl_sample_alpha_to_one_sgis = 0x809f,
		gl_sample_mask_sgis = 0x80a0,
		gl_1pass_sgis = 0x80a1,
		gl_2pass_0_sgis = 0x80a2,
		gl_2pass_1_sgis = 0x80a3,
		gl_4pass_0_sgis = 0x80a4,
		gl_4pass_1_sgis = 0x80a5,
		gl_4pass_2_sgis = 0x80a6,
		gl_4pass_3_sgis = 0x80a7,
		gl_sample_buffers_sgis = 0x80a8,
		gl_samples_sgis = 0x80a9,
		gl_sample_mask_value_sgis = 0x80aa,
		gl_sample_mask_invert_sgis = 0x80ab,
		gl_sample_pattern_sgis = 0x80ac,

		//multitexture
		gl_selected_texture_sgis = 0x83c0,
		gl_selected_texture_coord_set_sgis = 0x83c1,
		gl_selected_texture_transform_sgis = 0x83c2,
		gl_max_textures_sgis = 0x83c3,
		gl_max_texture_coord_sets_sgis = 0x83c4,
		gl_texture_coord_set_interleave_factor_sgis = 0x83c5,
		gl_texture_env_coord_set_sgis = 0x83c6,
		gl_texture0_sgis = 0x83c7,
		gl_texture1_sgis = 0x83c8,
		gl_texture2_sgis = 0x83c9,
		gl_texture3_sgis = 0x83ca,

		//point_line_texgen
		gl_eye_distance_to_point_sgis = 0x81f0,
		gl_object_distance_to_point_sgis = 0x81f1,
		gl_eye_distance_to_line_sgis = 0x81f2,
		gl_object_distance_to_line_sgis = 0x81f3,
		gl_eye_point_sgis = 0x81f4,
		gl_object_point_sgis = 0x81f5,
		gl_eye_line_sgis = 0x81f6,
		gl_object_line_sgis = 0x81f7,

		//texture_border_clamp
		gl_clamp_to_border_sgis = 0x812d,

		//texture_edge_clamp
		gl_clamp_to_edge_sgis = 0x812f,

		//texture_lod
		gl_texture_min_lod_sgis = 0x813a,
		gl_texture_max_lod_sgis = 0x813b,
		gl_texture_base_level_sgis = 0x813c,
		gl_texture_max_level_sgis = 0x813d,
	};

	//clip_band_hint
	bool SGIS_clip_band_hint = false;

	//color_range
	bool SGIS_color_range = false;

	//detail_texture
	void (*glDetailTexFuncSGIS) (GLenum target, GLsizei n, const GLfloat * points) = nullptr;
	void (*glGetDetailTexFuncSGIS) (GLenum target, GLfloat* points) = nullptr;
	bool SGIS_detail_texture = false;

	//fog_function
	void (*glFogFuncSGIS) (GLsizei n, const GLfloat * points) = nullptr;
	void (*glGetFogFuncSGIS) (GLfloat* points) = nullptr;
	bool SGIS_fog_function = false;

	//generate_mipmap
	bool SGIS_generate_mipmap = false;

	//line_texgen
	bool SGIS_line_texgen = false;

	//multisample
	void (*glSampleMaskSGIS) (GLclampf value, GLboolean invert) = nullptr;
	void (*glSamplePatternSGIS) (GLenum pattern) = nullptr;
	bool SGIS_multisample = false;

	//multitexture
	void (*glInterleavedTextureCoordSetsSGIS) (GLint factor) = nullptr;
	void (*glSelectTextureCoordSetSGIS) (GLenum target) = nullptr;
	void (*glSelectTextureSGIS) (GLenum target) = nullptr;
	void (*glSelectTextureTransformSGIS) (GLenum target) = nullptr;
	bool SGIS_multitexture = false;

	//pixel_texture
	bool SGIS_pixel_texture = false;

	//point_line_texgen
	bool SGIS_point_line_texgen = false;

	//shared_multisample
	void (*glMultisampleSubRectPosSGIS) (GLint x, GLint y) = nullptr;
	bool SGIS_shared_multisample = false;

	//sharpen_texture
	void (*glGetSharpenTexFuncSGIS) (GLenum target, GLfloat * points) = nullptr;
	void (*glSharpenTexFuncSGIS) (GLenum target, GLsizei n, const GLfloat* points) = nullptr;
	bool SGIS_sharpen_texture = false;

	//texture4D
	void (*glTexImage4DSGIS) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei extent, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
	void (*glTexSubImage4DSGIS) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei extent, GLenum format, GLenum type, const void* pixels) = nullptr;
	bool SGIS_texture4D = false;

	//texture_border_clamp
	bool SGIS_texture_border_clamp = false;

	//texture_edge_clamp
	bool SGIS_texture_edge_clamp = false;

	//texture_filter4
	void (*glGetTexFilterFuncSGIS) (GLenum target, GLenum filter, GLfloat * weights) = nullptr;
	void (*glTexFilterFuncSGIS) (GLenum target, GLenum filter, GLsizei n, const GLfloat* weights) = nullptr;
	bool SGIS_texture_filter4 = false;

	//texture_lod
	bool SGIS_texture_lod = false;

	//texture_select
	bool SGIS_texture_select = false;

	//*< load SGIS Extensions
	void LoadSGISExtensions()
	{
		//clip_band_hint
		FetchProcAddress(SGIS_clip_band_hint, "SGIS_clip_band_hint");

		//color_range
		FetchProcAddress(SGIS_color_range, "SGIS_color_range");

		//detail_texture
		FetchProcAddress(glDetailTexFuncSGIS, "glDetailTexFuncSGIS");
		FetchProcAddress(glGetDetailTexFuncSGIS, "glGetDetailTexFuncSGIS");
		FetchProcAddress(SGIS_detail_texture, "SGIS_detail_texture");

		//fog_function
		FetchProcAddress(glFogFuncSGIS, "glFogFuncSGIS");
		FetchProcAddress(glGetFogFuncSGIS, "glGetFogFuncSGIS");
		FetchProcAddress(SGIS_fog_function, "SGIS_fog_function");

		//generate_mipmap
		FetchProcAddress(SGIS_generate_mipmap, "SGIS_generate_mipmap");

		//line_texgen
		FetchProcAddress(SGIS_line_texgen, "SGIS_line_texgen");

		//multisample
		FetchProcAddress(glSampleMaskSGIS, "glSampleMaskSGIS");
		FetchProcAddress(glSamplePatternSGIS, "glSamplePatternSGIS");
		FetchProcAddress(SGIS_multisample, "SGIS_multisample");

		//multitexture
		FetchProcAddress(glInterleavedTextureCoordSetsSGIS, "glInterleavedTextureCoordSetsSGIS");
		FetchProcAddress(glSelectTextureCoordSetSGIS, "glSelectTextureCoordSetSGIS");
		FetchProcAddress(glSelectTextureSGIS, "glSelectTextureSGIS");
		FetchProcAddress(glSelectTextureTransformSGIS, "glSelectTextureTransformSGIS");
		FetchProcAddress(SGIS_multitexture, "SGIS_multitexture");

		//pixel_texture
		FetchProcAddress(SGIS_pixel_texture, "SGIS_pixel_texture");

		//point_line_texgen
		FetchProcAddress(SGIS_point_line_texgen, "SGIS_point_line_texgen");

		//shared_multisample
		FetchProcAddress(glMultisampleSubRectPosSGIS, "glMultisampleSubRectPosSGIS");
		FetchProcAddress(SGIS_shared_multisample, "SGIS_shared_multisample");

		//sharpen_texture
		FetchProcAddress(glGetSharpenTexFuncSGIS, "glGetSharpenTexFuncSGIS");
		FetchProcAddress(glSharpenTexFuncSGIS, "glSharpenTexFuncSGIS");
		FetchProcAddress(SGIS_sharpen_texture, "SGIS_sharpen_texture");

		//texture4D
		FetchProcAddress(glTexImage4DSGIS, "glTexImage4DSGIS");
		FetchProcAddress(glTexSubImage4DSGIS, "glTexSubImage4DSGIS");
		FetchProcAddress(SGIS_texture4D, "SGIS_texture4D");

		//texture_border_clamp
		FetchProcAddress(SGIS_texture_border_clamp, "SGIS_texture_border_clamp");

		//texture_edge_clamp
		FetchProcAddress(SGIS_texture_edge_clamp, "SGIS_texture_edge_clamp");

		//texture_filter4
		FetchProcAddress(glGetTexFilterFuncSGIS, "glGetTexFilterFuncSGIS");
		FetchProcAddress(glTexFilterFuncSGIS, "glTexFilterFuncSGIS");
		FetchProcAddress(SGIS_texture_filter4, "SGIS_texture_filter4");

		//texture_lod
		FetchProcAddress(SGIS_texture_lod, "SGIS_texture_lod");

		//texture_select
		FetchProcAddress(SGIS_texture_select, "SGIS_texture_select");
	}

#pragma endregion SGIS Extensions

	//OpenGL SGIX Extensions
#pragma region SGIX 

	enum OpenGL_SGIX_t
	{
		//async
		gl_async_marker_sgix = 0x8329,

		//async_histogram
		gl_async_histogram_sgix = 0x832c,
		gl_max_async_histogram_sgix = 0x832d,

		//async_pixel
		gl_async_tex_image_sgix = 0x835c,
		gl_async_draw_pixels_sgix = 0x835d,
		gl_async_read_pixels_sgix = 0x835e,
		gl_max_async_tex_image_sgix = 0x835f,
		gl_max_async_draw_pixels_sgix = 0x8360,
		gl_max_async_read_pixels_sgix = 0x8361,

		//bali_g_instruments
		gl_bali_num_tris_culled_instrument = 0x6080,
		gl_bali_num_prims_clipped_instrument = 0x6081,
		gl_bali_num_prims_reject_instrument = 0x6082,
		gl_bali_num_prims_clip_result_instrument = 0x6083,

		//bali_r_instruments
		gl_bali_fragments_generated_instrument = 0x6090,
		gl_bali_depth_pass_instrument = 0x6091,
		gl_bali_r_chip_count = 0x6092,

		//blend_alpha_minmax
		gl_alpha_min_sgix = 0x8320,
		gl_alpha_max_sgix = 0x8321,

		//blend_cadd
		gl_func_complex_add_ext = 0x601c,

		//blend_cmultiply
		gl_func_complex_multiply_ext = 0x601b,

		//color_matrix_accuracy
		gl_color_matrix_hint = 0x8317,

		//convolution_accuracy
		gl_convolution_hint_sgix = 0x8316,

		//cube_map
		gl_env_map_sgix = 0x8340,
		gl_cube_map_sgix = 0x8341,
		gl_cube_map_zp_sgix = 0x8342,
		gl_cube_map_zn_sgix = 0x8343,
		gl_cube_map_xn_sgix = 0x8344,
		gl_cube_map_xp_sgix = 0x8345,
		gl_cube_map_yn_sgix = 0x8346,
		gl_cube_map_yp_sgix = 0x8347,
		gl_cube_map_binding_sgix = 0x8348,

		//datapipe
		gl_geometry_bit = 0x1,
		gl_image_bit = 0x2,

		//depth_pass_instrument
		gl_depth_pass_instrument_sgix = 0x8310,
		gl_depth_pass_instrument_counters_sgix = 0x8311,
		gl_depth_pass_instrument_max_sgix = 0x8312,

		//depth_texture
		gl_depth_component16_sgix = 0x81a5,
		gl_depth_component24_sgix = 0x81a6,
		gl_depth_component32_sgix = 0x81a7,

		//fog_blend
		gl_fog_blend_alpha_sgix = 0x81fe,
		gl_fog_blend_color_sgix = 0x81ff,

		//fog_layers
		gl_fog_type_sgix = 0x8323,
		gl_uniform_sgix = 0x8324,
		gl_layered_sgix = 0x8325,
		gl_fog_ground_plane_sgix = 0x8326,
		gl_fog_layers_points_sgix = 0x8327,
		gl_max_fog_layers_points_sgix = 0x8328,

		//fog_offset
		gl_fog_offset_sgix = 0x8198,
		gl_fog_offset_value_sgix = 0x8199,

		//fog_scale
		gl_fog_scale_sgix = 0x81fc,
		gl_fog_scale_value_sgix = 0x81fd,

		//fragment_lighting_space
		gl_eye_space_sgix = 0x8436,
		gl_tangent_space_sgix = 0x8437,
		gl_object_space_sgix = 0x8438,
		gl_fragment_light_space_sgix = 0x843d,

		//fragments_instrument
		gl_fragments_instrument_sgix = 0x8313,
		gl_fragments_instrument_counters_sgix = 0x8314,
		gl_fragments_instrument_max_sgix = 0x8315,

		//icc_texture
		gl_rgb_icc_sgix = 0x8460,
		gl_rgba_icc_sgix = 0x8461,
		gl_alpha_icc_sgix = 0x8462,
		gl_luminance_icc_sgix = 0x8463,
		gl_intensity_icc_sgix = 0x8464,
		gl_luminance_alpha_icc_sgix = 0x8465,
		gl_r5_g6_b5_icc_sgix = 0x8466,
		gl_r5_g6_b5_a8_icc_sgix = 0x8467,
		gl_alpha16_icc_sgix = 0x8468,
		gl_luminance16_icc_sgix = 0x8469,
		gl_intensity16_icc_sgix = 0x846a,
		gl_luminance16_alpha8_icc_sgix = 0x846b,

		//igloo_interface
		gl_igloo_fullscreen_sgix = 0x819e,
		gl_igloo_viewport_offset_sgix = 0x819f,
		gl_igloo_swaptmesh_sgix = 0x81a0,
		gl_igloo_colornormal_sgix = 0x81a1,
		gl_igloo_irisgl_mode_sgix = 0x81a2,
		gl_igloo_lmc_color_sgix = 0x81a3,
		gl_igloo_tmeshmode_sgix = 0x81a4,
		gl_light31 = 0xbead,

		//interlace
		gl_interlace_sgix = 0x8094,

		//line_quality_hint
		gl_line_quality_hint_sgix = 0x835b,

		//nurbs_eval
		gl_map1_vertex_3_nurbs_sgix = 0x81cb,
		gl_map1_vertex_4_nurbs_sgix = 0x81cc,
		gl_map1_index_nurbs_sgix = 0x81cd,
		gl_map1_color_4_nurbs_sgix = 0x81ce,
		gl_map1_normal_nurbs_sgix = 0x81cf,
		gl_map1_texture_coord_1_nurbs_sgix = 0x81e0,
		gl_map1_texture_coord_2_nurbs_sgix = 0x81e1,
		gl_map1_texture_coord_3_nurbs_sgix = 0x81e2,
		gl_map1_texture_coord_4_nurbs_sgix = 0x81e3,
		gl_map2_vertex_3_nurbs_sgix = 0x81e4,
		gl_map2_vertex_4_nurbs_sgix = 0x81e5,
		gl_map2_index_nurbs_sgix = 0x81e6,
		gl_map2_color_4_nurbs_sgix = 0x81e7,
		gl_map2_normal_nurbs_sgix = 0x81e8,
		gl_map2_texture_coord_1_nurbs_sgix = 0x81e9,
		gl_map2_texture_coord_2_nurbs_sgix = 0x81ea,
		gl_map2_texture_coord_3_nurbs_sgix = 0x81eb,
		gl_map2_texture_coord_4_nurbs_sgix = 0x81ec,
		gl_nurbs_knot_count_sgix = 0x81ed,
		gl_nurbs_knot_vector_sgix = 0x81ee,

		//occlusion_instrument
		gl_occlusion_instrument_sgix = 0x6060,

		//polynomial_ffd
		gl_texture_deformation_bit_sgix = 0x1,
		gl_geometry_deformation_bit_sgix = 0x2,

		//resample
		gl_pack_resample_sgix = 0x842e,
		gl_unpack_resample_sgix = 0x842f,
		gl_resample_decimate_sgix = 0x8430,
		gl_resample_replicate_sgix = 0x8433,
		gl_resample_zero_fill_sgix = 0x8434,

		//scalebias_hint
		gl_scalebias_hint_sgix = 0x8322,

		//shadow
		gl_texture_compare_sgix = 0x819a,
		gl_texture_compare_operator_sgix = 0x819b,
		gl_texture_lequal_r_sgix = 0x819c,
		gl_texture_gequal_r_sgix = 0x819d,

		//shadow_ambient
		gl_shadow_ambient_sgix = 0x80bf,

		//slim
		gl_pack_max_compressed_size_sgix = 0x831b,
		gl_slim8u_sgix = 0x831d,
		gl_slim10u_sgix = 0x831e,
		gl_slim12s_sgix = 0x831f,

		//spotlight_cutoff
		gl_spot_cutoff_delta_sgix = 0x8193,

		//subsample
		gl_pack_subsample_rate_sgix = 0x85a0,
		gl_unpack_subsample_rate_sgix = 0x85a1,
		gl_pixel_subsample_4444_sgix = 0x85a2,
		gl_pixel_subsample_2424_sgix = 0x85a3,
		gl_pixel_subsample_4242_sgix = 0x85a4,

		//texture_coordinate_clamp
		gl_texture_max_clamp_s_sgix = 0x8369,
		gl_texture_max_clamp_t_sgix = 0x836a,
		gl_texture_max_clamp_r_sgix = 0x836b,

		//texture_mipmap_anisotropic
		gl_texture_mipmap_anisotropy_sgix = 0x832e,
		gl_max_mipmap_anisotropy_sgix = 0x832f,

		//texture_multi_buffer
		gl_texture_multi_buffer_hint_sgix = 0x812e,

		//texture_phase
		gl_phase_sgix = 0x832a,

		//texture_range
		gl_rgb_signed_sgix = 0x85e0,
		gl_rgba_signed_sgix = 0x85e1,
		gl_alpha_signed_sgix = 0x85e2,
		gl_luminance_signed_sgix = 0x85e3,
		gl_intensity_signed_sgix = 0x85e4,
		gl_luminance_alpha_signed_sgix = 0x85e5,
		gl_rgb16_signed_sgix = 0x85e6,
		gl_rgba16_signed_sgix = 0x85e7,
		gl_alpha16_signed_sgix = 0x85e8,
		gl_luminance16_signed_sgix = 0x85e9,
		gl_intensity16_signed_sgix = 0x85ea,
		gl_luminance16_alpha16_signed_sgix = 0x85eb,
		gl_rgb_extended_range_sgix = 0x85ec,
		gl_rgba_extended_range_sgix = 0x85ed,
		gl_alpha_extended_range_sgix = 0x85ee,
		gl_luminance_extended_range_sgix = 0x85ef,
		gl_intensity_extended_range_sgix = 0x85f0,
		gl_luminance_alpha_extended_range_sgix = 0x85f1,
		gl_rgb16_extended_range_sgix = 0x85f2,
		gl_rgba16_extended_range_sgix = 0x85f3,
		gl_alpha16_extended_range_sgix = 0x85f4,
		gl_luminance16_extended_range_sgix = 0x85f5,
		gl_intensity16_extended_range_sgix = 0x85f6,
		gl_luminance16_alpha16_extended_range_sgix = 0x85f7,
		gl_min_luminance_sgis = 0x85f8,
		gl_max_luminance_sgis = 0x85f9,
		gl_min_intensity_sgis = 0x85fa,
		gl_max_intensity_sgis = 0x85fb,

		//texture_scale_bias
		gl_post_texture_filter_bias_sgix = 0x8179,
		gl_post_texture_filter_scale_sgix = 0x817a,
		gl_post_texture_filter_bias_range_sgix = 0x817b,
		gl_post_texture_filter_scale_range_sgix = 0x817c,

		//vertex_preclip
		gl_vertex_preclip_sgix = 0x83ee,
		gl_vertex_preclip_hint_sgix = 0x83ef,

		//vertex_preclip_hint
		//gl_vertex_preclip_sgix = 0x83ee,
		//gl_vertex_preclip_hint_sgix = 0x83ef,

		//ycrcba
		gl_ycrcb_sgix = 0x8318,
		gl_ycrcba_sgix = 0x8319
	};

	//async
	void (*glAsyncMarkerSGIX) (GLuint marker) = nullptr;
	void (*glDeleteAsyncMarkersSGIX) (GLuint marker, GLsizei range) = nullptr;
	GLint(*glFinishAsyncSGIX) (GLuint* markerp) = nullptr;
	GLuint(*glGenAsyncMarkersSGIX) (GLsizei range) = nullptr;
	GLboolean(*glIsAsyncMarkerSGIX) (GLuint marker) = nullptr;
	GLint(*glPollAsyncSGIX) (GLuint* markerp) = nullptr;
	bool SGIX_async = false;

	//async_histogram
	bool SGIX_async_histogram = false;

	//async_pixel
	bool SGIX_async_pixel = false;

	//bali_g_instruments
	bool SGIX_bali_g_instruments = false;

	//bali_r_instruments
	bool SGIX_bali_r_instruments = false;

	//bali_timer_instruments
	bool SGIX_bali_timer_instruments = false;

	//blend_alpha_minmax
	bool SGIX_blend_alpha_minmax = false;

	//blend_cadd
	bool SGIX_blend_cadd = false;

	//blend_cmultiply
	bool SGIX_blend_cmultiply = false;

	//calligraphic_fragment
	bool SGIX_calligraphic_fragment = false;

	//clipmap
	bool SGIX_clipmap = false;

	//color_matrix_accuracy
	bool SGIX_color_matrix_accuracy = false;

	//color_table_index_mode
	bool SGIX_color_table_index_mode = false;

	//complex_polar
	bool SGIX_complex_polar = false;

	//convolution_accuracy
	bool SGIX_convolution_accuracy = false;

	//cube_map
	bool SGIX_cube_map = false;

	//cylinder_texgen
	bool SGIX_cylinder_texgen = false;

	//datapipe
	void (*glAddressSpace) (GLenum space, GLbitfield mask) = nullptr;
	GLint(*glDataPipe) (GLenum space) = nullptr;
	bool SGIX_datapipe = false;

	//decimation
	bool SGIX_decimation = false;

	//depth_pass_instrument
	bool SGIX_depth_pass_instrument = false;

	//depth_texture
	bool SGIX_depth_texture = false;

	//dvc
	bool SGIX_dvc = false;

	//flush_raster
	void (*glFlushRasterSGIX) (void) = nullptr;
	bool SGIX_flush_raster = false;

	//fog_blend
	bool SGIX_fog_blend = false;

	//fog_factor_to_alpha
	bool SGIX_fog_factor_to_alpha = false;

	//fog_layers
	void (*glFogLayersSGIX) (GLsizei n, const GLfloat * points) = nullptr;
	void (*glGetFogLayersSGIX) (GLfloat* points) = nullptr;
	bool SGIX_fog_layers = false;

	//fog_offset
	bool SGIX_fog_offset = false;

	//fog_patchy
	bool SGIX_fog_patchy = false;

	//fog_scale
	bool SGIX_fog_scale = false;

	//fog_texture
	void (*glTextureFogSGIX) (GLenum pname) = nullptr;
	bool SGIX_fog_texture = false;

	//fragment_lighting_space
	bool SGIX_fragment_lighting_space = false;

	//fragment_specular_lighting
	void (*glFragmentColorMaterialSGIX) (GLenum face, GLenum mode) = nullptr;
	void (*glFragmentLightModelfSGIX) (GLenum pname, GLfloat param) = nullptr;
	void (*glFragmentLightModelfvSGIX) (GLenum pname, GLfloat* params) = nullptr;
	void (*glFragmentLightModeliSGIX) (GLenum pname, GLint param) = nullptr;
	void (*glFragmentLightModelivSGIX) (GLenum pname, GLint* params) = nullptr;
	void (*glFragmentLightfSGIX) (GLenum light, GLenum pname, GLfloat param) = nullptr;
	void (*glFragmentLightfvSGIX) (GLenum light, GLenum pname, GLfloat* params) = nullptr;
	void (*glFragmentLightiSGIX) (GLenum light, GLenum pname, GLint param) = nullptr;
	void (*glFragmentLightivSGIX) (GLenum light, GLenum pname, GLint* params) = nullptr;
	void (*glFragmentMaterialfSGIX) (GLenum face, GLenum pname, const GLfloat param) = nullptr;
	void (*glFragmentMaterialfvSGIX) (GLenum face, GLenum pname, const GLfloat* params) = nullptr;
	void (*glFragmentMaterialiSGIX) (GLenum face, GLenum pname, const GLint param) = nullptr;
	void (*glFragmentMaterialivSGIX) (GLenum face, GLenum pname, const GLint* params) = nullptr;
	void (*glGetFragmentLightfvSGIX) (GLenum light, GLenum value, GLfloat* data) = nullptr;
	void (*glGetFragmentLightivSGIX) (GLenum light, GLenum value, GLint* data) = nullptr;
	void (*glGetFragmentMaterialfvSGIX) (GLenum face, GLenum pname, const GLfloat* data) = nullptr;
	void (*glGetFragmentMaterialivSGIX) (GLenum face, GLenum pname, const GLint* data) = nullptr;
	bool SGIX_fragment_specular_lighting = false;

	//fragments_instrument
	bool SGIX_fragments_instrument = false;

	//framezoom
	void (*glFrameZoomSGIX) (GLint factor) = nullptr;
	bool SGIX_framezoom = false;

	//icc_texture
	bool SGIX_icc_texture = false;

	//igloo_interface
	void (*glIglooInterfaceSGIX) (GLenum pname, void* param) = nullptr;
	bool SGIX_igloo_interface = false;

	//image_compression
	bool SGIX_image_compression = false;

	//impact_pixel_texture
	bool SGIX_impact_pixel_texture = false;

	//instrument_error
	bool SGIX_instrument_error = false;

	//interlace
	bool SGIX_interlace = false;

	//ir_instrument1
	bool SGIX_ir_instrument1 = false;

	//line_quality_hint
	bool SGIX_line_quality_hint = false;

	//list_priority
	bool SGIX_list_priority = false;

	//mpeg1
	void (*glAllocMPEGPredictorsSGIX) (GLsizei width, GLsizei height, GLsizei n, GLuint * predictors) = nullptr;
	void (*glDeleteMPEGPredictorsSGIX) (GLsizei n, GLuint* predictors) = nullptr;
	void (*glGenMPEGPredictorsSGIX) (GLsizei n, GLuint* predictors) = nullptr;
	void (*glGetMPEGParameterfvSGIX) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetMPEGParameterivSGIX) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glGetMPEGPredictorSGIX) (GLenum target, GLenum format, GLenum type, void* pixels) = nullptr;
	void (*glGetMPEGQuantTableubv) (GLenum target, GLubyte* values) = nullptr;
	GLboolean(*glIsMPEGPredictorSGIX) (GLuint predictor) = nullptr;
	void (*glMPEGPredictorSGIX) (GLenum target, GLenum format, GLenum type, void* pixels) = nullptr;
	void (*glMPEGQuantTableubv) (GLenum target, GLubyte* values) = nullptr;
	void (*glSwapMPEGPredictorsSGIX) (GLenum target0, GLenum target1) = nullptr;
	bool SGIX_mpeg1 = false;

	//mpeg2
	bool SGIX_mpeg2 = false;

	//nonlinear_lighting_pervertex
	void (*glGetNonlinLightfvSGIX) (GLenum light, GLenum pname, GLint * terms, GLfloat * data) = nullptr;
	void (*glGetNonlinMaterialfvSGIX) (GLenum face, GLenum pname, GLint* terms, const GLfloat* data) = nullptr;
	void (*glNonlinLightfvSGIX) (GLenum light, GLenum pname, GLint terms, GLfloat* params) = nullptr;
	void (*glNonlinMaterialfvSGIX) (GLenum face, GLenum pname, GLint terms, const GLfloat* params) = nullptr;
	bool SGIX_nonlinear_lighting_pervertex = false;

	//nurbs_eval
	bool SGIX_nurbs_eval = false;

	//occlusion_instrument
	bool SGIX_occlusion_instrument = false;

	//packed_6bytes
	bool SGIX_packed_6bytes = false;

	//pixel_texture
	void (*glPixelTexGenSGIX) (GLenum mode) = nullptr;
	bool SGIX_pixel_texture = false;

	//pixel_texture_bits
	bool SGIX_pixel_texture_bits = false;

	//pixel_texture_lod
	bool SGIX_pixel_texture_lod = false;

	//pixel_tiles
	bool SGIX_pixel_tiles = false;

	//polynomial_ffd
	void (*glDeformSGIX) (GLbitfield mask) = nullptr;
	void (*glLoadIdentityDeformationMapSGIX) (GLbitfield mask) = nullptr;
	bool SGIX_polynomial_ffd = false;

	//quad_mesh
	void (*glMeshBreadthSGIX) (GLint breadth) = nullptr;
	void (*glMeshStrideSGIX) (GLint stride) = nullptr;
	bool SGIX_quad_mesh = false;

	//reference_plane
	void (*glReferencePlaneSGIX) (const GLdouble * equation) = nullptr;
	bool SGIX_reference_plane = false;

	//resample
	bool SGIX_resample = false;

	//scalebias_hint
	bool SGIX_scalebias_hint = false;

	//shadow
	bool SGIX_shadow = false;

	//shadow_ambient
	bool SGIX_shadow_ambient = false;

	//slim
	bool SGIX_slim = false;

	//spotlight_cutoff
	bool SGIX_spotlight_cutoff = false;

	//sprite
	void (*glSpriteParameterfSGIX) (GLenum pname, GLfloat param) = nullptr;
	void (*glSpriteParameterfvSGIX) (GLenum pname, GLfloat* params) = nullptr;
	void (*glSpriteParameteriSGIX) (GLenum pname, GLint param) = nullptr;
	void (*glSpriteParameterivSGIX) (GLenum pname, GLint* params) = nullptr;
	bool SGIX_sprite = false;

	//subdiv_patch
	bool SGIX_subdiv_patch = false;

	//subsample
	bool SGIX_subsample = false;

	//tag_sample_buffer
	void (*glTagSampleBufferSGIX) (void) = nullptr;
	bool SGIX_tag_sample_buffer = false;

	//texture_add_env
	bool SGIX_texture_add_env = false;

	//texture_coordinate_clamp
	bool SGIX_texture_coordinate_clamp = false;

	//texture_lod_bias
	bool SGIX_texture_lod_bias = false;

	//texture_mipmap_anisotropic
	bool SGIX_texture_mipmap_anisotropic = false;

	//texture_multi_buffer
	bool SGIX_texture_multi_buffer = false;		

	//texture_phase
	bool SGIX_texture_phase = false;

	//texture_range
	bool SGIX_texture_range = false;

	//texture_scale_bias
	bool SGIX_texture_scale_bias = false;

	//texture_supersample
	bool SGIX_texture_supersample = false;

	//vector_ops
	void (*glGetVectorOperationSGIX) (GLenum operation) = nullptr;
	void (*glVectorOperationSGIX) (GLenum operation) = nullptr;
	bool SGIX_vector_ops = false;

	//vertex_array_object
	GLboolean(*glAreVertexArraysResidentSGIX) (GLsizei n, const GLuint * arrays, GLboolean * residences) = nullptr;
	void (*glBindVertexArraySGIX) (GLuint array) = nullptr;
	void (*glDeleteVertexArraysSGIX) (GLsizei n, const GLuint* arrays) = nullptr;
	void (*glGenVertexArraysSGIX) (GLsizei n, GLuint* arrays) = nullptr;
	GLboolean(*glIsVertexArraySGIX) (GLuint array) = nullptr;
	void (*glPrioritizeVertexArraysSGIX) (GLsizei n, const GLuint* arrays, const GLclampf* priorities) = nullptr;
	bool SGIX_vertex_array_object = false;

	//vertex_preclip
	bool SGIX_vertex_preclip = false;		

	//vertex_preclip_hint
	bool SGIX_vertex_preclip_hint = false;

	//ycrcb
	bool SGIX_ycrcb = false;

	//ycrcb_subsample
	bool SGIX_ycrcb_subsample = false;

	//ycrcba
	bool SGIX_ycrcba = false;

	//*< load SGIX Extensions
	void LoadSGIXExtensions()
	{
		//async
		FetchProcAddress(glAsyncMarkerSGIX, "glAsyncMarkerSGIX");
		FetchProcAddress(glDeleteAsyncMarkersSGIX, "glDeleteAsyncMarkersSGIX");
		FetchProcAddress(glFinishAsyncSGIX, "glFinishAsyncSGIX");
		FetchProcAddress(glGenAsyncMarkersSGIX, "glGenAsyncMarkersSGIX");
		FetchProcAddress(glIsAsyncMarkerSGIX, "glIsAsyncMarkerSGIX");
		FetchProcAddress(glPollAsyncSGIX, "glPollAsyncSGIX");
		FetchProcAddress(SGIX_async, "SGIX_async");

		//async_histogram
		FetchProcAddress(SGIX_async_histogram, "SGIX_async_histogram");

		//async_pixel
		FetchProcAddress(SGIX_async_pixel, "SGIX_async_pixel");

		//bali_g_instruments
		FetchProcAddress(SGIX_bali_g_instruments, "SGIX_bali_g_instruments");

		//bali_r_instruments
		FetchProcAddress(SGIX_bali_r_instruments, "SGIX_bali_r_instruments");

		//bali_timer_instruments
		FetchProcAddress(SGIX_bali_timer_instruments, "SGIX_bali_timer_instruments");

		//blend_alpha_minmax
		FetchProcAddress(SGIX_blend_alpha_minmax, "SGIX_blend_alpha_minmax");

		//blend_cadd
		FetchProcAddress(SGIX_blend_cadd, "SGIX_blend_cadd");

		//blend_cmultiply
		FetchProcAddress(SGIX_blend_cmultiply, "SGIX_blend_cmultiply");

		//calligraphic_fragment
		FetchProcAddress(SGIX_calligraphic_fragment, "SGIX_calligraphic_fragment");

		//clipmap
		FetchProcAddress(SGIX_clipmap, "SGIX_clipmap");

		//color_matrix_accuracy
		FetchProcAddress(SGIX_color_matrix_accuracy, "SGIX_color_matrix_accuracy");

		//color_table_index_mode
		FetchProcAddress(SGIX_color_table_index_mode, "SGIX_color_table_index_mode");

		//complex_polar
		FetchProcAddress(SGIX_complex_polar, "SGIX_complex_polar");

		//convolution_accuracy
		FetchProcAddress(SGIX_convolution_accuracy, "SGIX_convolution_accuracy");

		//cube_map
		FetchProcAddress(SGIX_cube_map, "SGIX_cube_map");

		//cylinder_texgen
		FetchProcAddress(SGIX_cylinder_texgen, "SGIX_cylinder_texgen");

		//datapipe
		FetchProcAddress(glAddressSpace, "glAddressSpace");
		FetchProcAddress(glDataPipe, "glDataPipe");
		FetchProcAddress(SGIX_datapipe, "SGIX_datapipe");

		//decimation
		FetchProcAddress(SGIX_decimation, "SGIX_decimation");

		//depth_pass_instrument
		FetchProcAddress(SGIX_depth_pass_instrument, "SGIX_depth_pass_instrument");

		//depth_texture
		FetchProcAddress(SGIX_depth_texture, "SGIX_depth_texture");

		//dvc
		FetchProcAddress(SGIX_dvc, "SGIX_dvc");

		//flush_raster
		FetchProcAddress(glFlushRasterSGIX, "glFlushRasterSGIX");
		FetchProcAddress(SGIX_flush_raster, "SGIX_flush_raster");

		//fog_blend
		FetchProcAddress(SGIX_fog_blend, "SGIX_fog_blend");

		//fog_factor_to_alpha
		FetchProcAddress(SGIX_fog_factor_to_alpha, "SGIX_fog_factor_to_alpha");

		//fog_layers
		FetchProcAddress(glFogLayersSGIX, "glFogLayersSGIX");
		FetchProcAddress(glGetFogLayersSGIX, "glGetFogLayersSGIX");
		FetchProcAddress(SGIX_fog_layers, "SGIX_fog_layers");

		//fog_offset
		FetchProcAddress(SGIX_fog_offset, "SGIX_fog_offset");

		//fog_patchy
		FetchProcAddress(SGIX_fog_patchy, "SGIX_fog_patchy");

		//fog_scale
		FetchProcAddress(SGIX_fog_scale, "SGIX_fog_scale");

		//fog_texture
		FetchProcAddress(glTextureFogSGIX, "glTextureFogSGIX");
		FetchProcAddress(SGIX_fog_texture, "SGIX_fog_texture");

		//fragment_lighting_space
		FetchProcAddress(SGIX_fragment_lighting_space, "SGIX_fragment_lighting_space");

		//fragment_specular_lighting
		FetchProcAddress(glFragmentColorMaterialSGIX, "glFragmentColorMaterialSGIX");
		FetchProcAddress(glFragmentLightModelfSGIX, "glFragmentLightModelfSGIX");
		FetchProcAddress(glFragmentLightModelfvSGIX, "glFragmentLightModelfvSGIX");
		FetchProcAddress(glFragmentLightModeliSGIX, "glFragmentLightModeliSGIX");
		FetchProcAddress(glFragmentLightModelivSGIX, "glFragmentLightModelivSGIX");
		FetchProcAddress(glFragmentLightfSGIX, "glFragmentLightfSGIX");
		FetchProcAddress(glFragmentLightfvSGIX, "glFragmentLightfvSGIX");
		FetchProcAddress(glFragmentLightiSGIX, "glFragmentLightiSGIX");
		FetchProcAddress(glFragmentLightivSGIX, "glFragmentLightivSGIX");
		FetchProcAddress(glFragmentMaterialfSGIX, "glFragmentMaterialfSGIX");
		FetchProcAddress(glFragmentMaterialfvSGIX, "glFragmentMaterialfvSGIX");
		FetchProcAddress(glFragmentMaterialiSGIX, "glFragmentMaterialiSGIX");
		FetchProcAddress(glFragmentMaterialivSGIX, "glFragmentMaterialivSGIX");
		FetchProcAddress(glGetFragmentLightfvSGIX, "glGetFragmentLightfvSGIX");
		FetchProcAddress(glGetFragmentLightivSGIX, "glGetFragmentLightivSGIX");
		FetchProcAddress(glGetFragmentMaterialfvSGIX, "glGetFragmentMaterialfvSGIX");
		FetchProcAddress(glGetFragmentMaterialivSGIX, "glGetFragmentMaterialivSGIX");
		FetchProcAddress(SGIX_fragment_specular_lighting, "SGIX_fragment_specular_lighting");

		//fragments_instrument
		FetchProcAddress(SGIX_fragments_instrument, "SGIX_fragments_instrument");

		//framezoom
		FetchProcAddress(glFrameZoomSGIX, "glFrameZoomSGIX");
		FetchProcAddress(SGIX_framezoom, "SGIX_framezoom");

		//icc_texture
		FetchProcAddress(SGIX_icc_texture, "SGIX_icc_texture");

		//igloo_interface
		FetchProcAddress(glIglooInterfaceSGIX, "glIglooInterfaceSGIX");
		FetchProcAddress(SGIX_igloo_interface, "SGIX_igloo_interface");

		//image_compression
		FetchProcAddress(SGIX_image_compression, "SGIX_image_compression");

		//impact_pixel_texture
		FetchProcAddress(SGIX_impact_pixel_texture, "SGIX_impact_pixel_texture");

		//instrument_error
		FetchProcAddress(SGIX_instrument_error, "SGIX_instrument_error");

		//interlace
		FetchProcAddress(SGIX_interlace, "SGIX_interlace");

		//ir_instrument1
		FetchProcAddress(SGIX_ir_instrument1, "SGIX_ir_instrument1");

		//line_quality_hint
		FetchProcAddress(SGIX_line_quality_hint, "SGIX_line_quality_hint");

		//list_priority
		FetchProcAddress(SGIX_list_priority, "SGIX_list_priority");

		//mpeg1
		FetchProcAddress(glAllocMPEGPredictorsSGIX, "glAllocMPEGPredictorsSGIX");
		FetchProcAddress(glDeleteMPEGPredictorsSGIX, "glDeleteMPEGPredictorsSGIX");
		FetchProcAddress(glGenMPEGPredictorsSGIX, "glGenMPEGPredictorsSGIX");
		FetchProcAddress(glGetMPEGParameterfvSGIX, "glGetMPEGParameterfvSGIX");
		FetchProcAddress(glGetMPEGParameterivSGIX, "glGetMPEGParameterivSGIX");
		FetchProcAddress(glGetMPEGPredictorSGIX, "glGetMPEGPredictorSGIX");
		FetchProcAddress(glGetMPEGQuantTableubv, "glGetMPEGQuantTableubv");
		FetchProcAddress(glIsMPEGPredictorSGIX, "glIsMPEGPredictorSGIX");
		FetchProcAddress(glMPEGPredictorSGIX, "glMPEGPredictorSGIX");
		FetchProcAddress(glMPEGQuantTableubv, "glMPEGQuantTableubv");
		FetchProcAddress(glSwapMPEGPredictorsSGIX, "glSwapMPEGPredictorsSGIX");
		FetchProcAddress(SGIX_mpeg1, "SGIX_mpeg1");

		//mpeg2
		FetchProcAddress(SGIX_mpeg2, "SGIX_mpeg2");

		//nonlinear_lighting_pervertex
		FetchProcAddress(glGetNonlinLightfvSGIX, "glGetNonlinLightfvSGIX");
		FetchProcAddress(glGetNonlinMaterialfvSGIX, "glGetNonlinMaterialfvSGIX");
		FetchProcAddress(glNonlinLightfvSGIX, "glNonlinLightfvSGIX");
		FetchProcAddress(glNonlinMaterialfvSGIX, "glNonlinMaterialfvSGIX");
		FetchProcAddress(SGIX_nonlinear_lighting_pervertex, "SGIX_nonlinear_lighting_pervertex");

		//nurbs_eval
		FetchProcAddress(SGIX_nurbs_eval, "SGIX_nurbs_eval");

		//occlusion_instrument
		FetchProcAddress(SGIX_occlusion_instrument, "SGIX_occlusion_instrument");

		//packed_6bytes
		FetchProcAddress(SGIX_packed_6bytes, "SGIX_packed_6bytes");

		//pixel_texture
		FetchProcAddress(glPixelTexGenSGIX, "glPixelTexGenSGIX");
		FetchProcAddress(SGIX_pixel_texture, "SGIX_pixel_texture");

		//pixel_texture_bits
		FetchProcAddress(SGIX_pixel_texture_bits, "SGIX_pixel_texture_bits");

		//pixel_texture_lod
		FetchProcAddress(SGIX_pixel_texture_lod, "SGIX_pixel_texture_lod");

		//pixel_tiles
		FetchProcAddress(SGIX_pixel_tiles, "SGIX_pixel_tiles");

		//polynomial_ffd
		FetchProcAddress(glDeformSGIX, "glDeformSGIX");
		FetchProcAddress(glLoadIdentityDeformationMapSGIX, "glLoadIdentityDeformationMapSGIX");
		FetchProcAddress(SGIX_polynomial_ffd, "SGIX_polynomial_ffd");

		//quad_mesh
		FetchProcAddress(glMeshBreadthSGIX, "glMeshBreadthSGIX");
		FetchProcAddress(glMeshStrideSGIX, "glMeshStrideSGIX");
		FetchProcAddress(SGIX_quad_mesh, "SGIX_quad_mesh");

		//reference_plane
		FetchProcAddress(glReferencePlaneSGIX, "glReferencePlaneSGIX");
		FetchProcAddress(SGIX_reference_plane, "SGIX_reference_plane");

		//resample
		FetchProcAddress(SGIX_resample, "SGIX_resample");

		//scalebias_hint
		FetchProcAddress(SGIX_scalebias_hint, "SGIX_scalebias_hint");

		//shadow
		FetchProcAddress(SGIX_shadow, "SGIX_shadow");

		//shadow_ambient
		FetchProcAddress(SGIX_shadow_ambient, "SGIX_shadow_ambient");

		//slim
		FetchProcAddress(SGIX_slim, "SGIX_slim");

		//spotlight_cutoff
		FetchProcAddress(SGIX_spotlight_cutoff, "SGIX_spotlight_cutoff");

		//sprite
		FetchProcAddress(glSpriteParameterfSGIX, "glSpriteParameterfSGIX");
		FetchProcAddress(glSpriteParameterfvSGIX, "glSpriteParameterfvSGIX");
		FetchProcAddress(glSpriteParameteriSGIX, "glSpriteParameteriSGIX");
		FetchProcAddress(glSpriteParameterivSGIX, "glSpriteParameterivSGIX");
		FetchProcAddress(SGIX_sprite, "SGIX_sprite");

		//subdiv_patch
		FetchProcAddress(SGIX_subdiv_patch, "SGIX_subdiv_patch");

		//subsample
		FetchProcAddress(SGIX_subsample, "SGIX_subsample");

		//tag_sample_buffer
		FetchProcAddress(glTagSampleBufferSGIX, "glTagSampleBufferSGIX");
		FetchProcAddress(SGIX_tag_sample_buffer, "SGIX_tag_sample_buffer");

		//texture_add_env
		FetchProcAddress(SGIX_texture_add_env, "SGIX_texture_add_env");

		//texture_coordinate_clamp
		FetchProcAddress(SGIX_texture_coordinate_clamp, "SGIX_texture_coordinate_clamp");

		//texture_lod_bias
		FetchProcAddress(SGIX_texture_lod_bias, "SGIX_texture_lod_bias");

		//texture_mipmap_anisotropic
		FetchProcAddress(SGIX_texture_mipmap_anisotropic, "SGIX_texture_mipmap_anisotropic");

		//texture_multi_buffer
		FetchProcAddress(SGIX_texture_multi_buffer, "SGIX_texture_multi_buffer");

		//texture_phase
		FetchProcAddress(SGIX_texture_phase, "SGIX_texture_phase");

		//texture_range
		FetchProcAddress(SGIX_texture_range, "SGIX_texture_range");

		//texture_scale_bias
		FetchProcAddress(SGIX_texture_scale_bias, "SGIX_texture_scale_bias");

		//texture_supersample
		FetchProcAddress(SGIX_texture_supersample, "SGIX_texture_supersample");

		//vector_ops
		FetchProcAddress(glGetVectorOperationSGIX, "glGetVectorOperationSGIX");
		FetchProcAddress(glVectorOperationSGIX, "glVectorOperationSGIX");
		FetchProcAddress(SGIX_vector_ops, "SGIX_vector_ops");

		//vertex_array_object
		FetchProcAddress(glAreVertexArraysResidentSGIX, "glAreVertexArraysResidentSGIX");
		FetchProcAddress(glBindVertexArraySGIX, "glBindVertexArraySGIX");
		FetchProcAddress(glDeleteVertexArraysSGIX, "glDeleteVertexArraysSGIX");
		FetchProcAddress(glGenVertexArraysSGIX, "glGenVertexArraysSGIX");
		FetchProcAddress(glIsVertexArraySGIX, "glIsVertexArraySGIX");
		FetchProcAddress(glPrioritizeVertexArraysSGIX, "glPrioritizeVertexArraysSGIX");
		FetchProcAddress(SGIX_vertex_array_object, "SGIX_vertex_array_object");

		//vertex_preclip
		FetchProcAddress(SGIX_vertex_preclip, "SGIX_vertex_preclip");

		//vertex_preclip_hint
		FetchProcAddress(SGIX_vertex_preclip_hint, "SGIX_vertex_preclip_hint");

		//ycrcb
		FetchProcAddress(SGIX_ycrcb, "SGIX_ycrcb");

		//ycrcb_subsample
		FetchProcAddress(SGIX_ycrcb_subsample, "SGIX_ycrcb_subsample");

		//ycrcba
		FetchProcAddress(SGIX_ycrcba, "SGIX_ycrcba");
	}

#pragma endregion SGIX Extensions

	//OpenGL SGI Extensions
#pragma region SGI

	enum OpenGL_SGI_t
	{
		//color_matrix
		gl_color_matrix_sgi = 0x80b1,
		gl_color_matrix_stack_depth_sgi = 0x80b2,
		gl_max_color_matrix_stack_depth_sgi = 0x80b3,
		gl_post_color_matrix_red_scale_sgi = 0x80b4,
		gl_post_color_matrix_green_scale_sgi = 0x80b5,
		gl_post_color_matrix_blue_scale_sgi = 0x80b6,
		gl_post_color_matrix_alpha_scale_sgi = 0x80b7,
		gl_post_color_matrix_red_bias_sgi = 0x80b8,
		gl_post_color_matrix_green_bias_sgi = 0x80b9,
		gl_post_color_matrix_blue_bias_sgi = 0x80ba,
		gl_post_color_matrix_alpha_bias_sgi = 0x80bb,

		//color_table
		gl_color_table_sgi = 0x80d0,
		gl_post_convolution_color_table_sgi = 0x80d1,
		gl_post_color_matrix_color_table_sgi = 0x80d2,
		gl_proxy_color_table_sgi = 0x80d3,
		gl_proxy_post_convolution_color_table_sgi = 0x80d4,
		gl_proxy_post_color_matrix_color_table_sgi = 0x80d5,
		gl_color_table_scale_sgi = 0x80d6,
		gl_color_table_bias_sgi = 0x80d7,
		gl_color_table_format_sgi = 0x80d8,
		gl_color_table_width_sgi = 0x80d9,
		gl_color_table_red_size_sgi = 0x80da,
		gl_color_table_green_size_sgi = 0x80db,
		gl_color_table_blue_size_sgi = 0x80dc,
		gl_color_table_alpha_size_sgi = 0x80dd,
		gl_color_table_luminance_size_sgi = 0x80de,
		gl_color_table_intensity_size_sgi = 0x80df,

		//complex_type
		gl_complex_unsigned_byte_sgi = 0x81bd,
		gl_complex_byte_sgi = 0x81be,
		gl_complex_unsigned_short_sgi = 0x81bf,
		gl_complex_short_sgi = 0x81c0,
		gl_complex_unsigned_int_sgi = 0x81c1,
		gl_complex_int_sgi = 0x81c2,
		gl_complex_float_sgi = 0x81c3,

		//fft
		gl_pixel_transform_operator_sgi = 0x81c4,
		gl_convolution_sgi = 0x81c5,
		gl_fft_1d_sgi = 0x81c6,
		gl_pixel_transform_sgi = 0x81c7,
		gl_max_fft_width_sgi = 0x81c8,

		//texture_color_table
		gl_texture_color_table_sgi = 0x80bc,
		gl_proxy_texture_color_table_sgi = 0x80bd,
	};

	//color_matrix
	bool SGI_color_matrix = false;

	//color_table
	void (*glColorTableParameterfvSGI) (GLenum target, GLenum pname, const GLfloat * params) = nullptr;
	void (*glColorTableParameterivSGI) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	void (*glColorTableSGI) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* table) = nullptr;
	void (*glCopyColorTableSGI) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = nullptr;
	void (*glGetColorTableParameterfvSGI) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	void (*glGetColorTableParameterivSGI) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glGetColorTableSGI) (GLenum target, GLenum format, GLenum type, void* table) = nullptr;
	bool SGI_color_table = false;

	//complex
	bool SGI_complex = false;

	//complex_type
	bool SGI_complex_type = false;

	//fft
	void (*glGetPixelTransformParameterfvSGI) (GLenum target, GLenum pname, GLfloat * params) = nullptr;
	void (*glGetPixelTransformParameterivSGI) (GLenum target, GLenum pname, GLint* params) = nullptr;
	void (*glPixelTransformParameterfSGI) (GLenum target, GLenum pname, GLfloat param) = nullptr;
	void (*glPixelTransformParameterfvSGI) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	void (*glPixelTransformParameteriSGI) (GLenum target, GLenum pname, GLint param) = nullptr;
	void (*glPixelTransformParameterivSGI) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	void (*glPixelTransformSGI) (GLenum target) = nullptr;
	bool SGI_fft = false;

	//texture_color_table
	bool SGI_texture_color_table = false;

	//*< load SGI Extensions
	void LoadSGIExtensions()
	{
		//color_matrix
		FetchProcAddress(SGI_color_matrix, "SGI_color_matrix");

		//color_table
		FetchProcAddress(glColorTableParameterfvSGI, "glColorTableParameterfvSGI");
		FetchProcAddress(glColorTableParameterivSGI, "glColorTableParameterivSGI");
		FetchProcAddress(glColorTableSGI, "glColorTableSGI");
		FetchProcAddress(glCopyColorTableSGI, "glCopyColorTableSGI");
		FetchProcAddress(glGetColorTableParameterfvSGI, "glGetColorTableParameterfvSGI");
		FetchProcAddress(glGetColorTableParameterivSGI, "glGetColorTableParameterivSGI");
		FetchProcAddress(glGetColorTableSGI, "glGetColorTableSGI");
		FetchProcAddress(SGI_color_table, "SGI_color_table");

		//complex
		FetchProcAddress(SGI_complex, "SGI_complex");

		//complex_type
		FetchProcAddress(SGI_complex_type, "SGI_complex_type");

		//fft
		FetchProcAddress(glGetPixelTransformParameterfvSGI, "glGetPixelTransformParameterfvSGI");
		FetchProcAddress(glGetPixelTransformParameterivSGI, "glGetPixelTransformParameterivSGI");
		FetchProcAddress(glPixelTransformParameterfSGI, "glPixelTransformParameterfSGI");
		FetchProcAddress(glPixelTransformParameterfvSGI, "glPixelTransformParameterfvSGI");
		FetchProcAddress(glPixelTransformParameteriSGI, "glPixelTransformParameteriSGI");
		FetchProcAddress(glPixelTransformParameterivSGI, "glPixelTransformParameterivSGI");
		FetchProcAddress(glPixelTransformSGI, "glPixelTransformSGI");

		FetchProcAddress(SGI_fft, "SGI_fft");

		//texture_color_table
		FetchProcAddress(SGI_texture_color_table, "SGI_texture_color_table");
	}

#pragma endregion SGI Extensions

	//OpenGL SUNX Extensions
#pragma region SUNX

	enum OpenGL_SUNX_t
	{
		//constant data
		gl_unpack_constant_data_sunx = 0x81d5,
		gl_texture_constant_data_sunx = 0x81d6,
	};

	//constant data
	void (*glFinishTextureSUNX) (void) = nullptr;
	bool SUNX_constant_data = false;

	//*< load SUNX Extensions
	void LoadSUNXExtensions()
	{
		FetchProcAddress(glFinishTextureSUNX, "glFinishTextureSUNX");
		FetchProcAddress(SUNX_constant_data, "glFinishTextureSUNX");
	}

#pragma endregion SUNX Extensions

	//OpenGL SUN Extensions
#pragma region SUN

	enum OpenGL_SUN_t
	{
		//convolution_border_modes
		gl_wrap_border_sun = 0x81d4,

		//global_alpha
		gl_global_alpha_sun = 0x81d9,
		gl_global_alpha_factor_sun = 0x81da,

		//mesh_array
		gl_quad_mesh_sun = 0x8614,
		gl_triangle_mesh_sun = 0x8615,

		//slice_accum
		gl_slice_accum_sun = 0x85cc,

		//triangle_list
		gl_restart_sun = 0x01,
		gl_replace_middle_sun = 0x02,
		gl_replace_oldest_sun = 0x03,
		gl_triangle_list_sun = 0x81d7,
		gl_replacement_code_sun = 0x81d8,
		gl_replacement_code_array_sun = 0x85c0,
		gl_replacement_code_array_type_sun = 0x85c1,
		gl_replacement_code_array_stride_sun = 0x85c2,
		gl_replacement_code_array_pointer_sun = 0x85c3,
		gl_r1ui_v3f_sun = 0x85c4,
		gl_r1ui_c4ub_v3f_sun = 0x85c5,
		gl_r1ui_c3f_v3f_sun = 0x85c6,
		gl_r1ui_n3f_v3f_sun = 0x85c7,
		gl_r1ui_c4f_n3f_v3f_sun = 0x85c8,
		gl_r1ui_t2f_v3f_sun = 0x85c9,
		gl_r1ui_t2f_n3f_v3f_sun = 0x85ca,
		gl_r1ui_t2f_c4f_n3f_v3f_sun = 0x85cb,
	};

	//convolution_border_modes
	bool SUN_convolution_border_modes = false;

	//global_alpha
	void (*glGlobalAlphaFactorbSUN) (GLbyte factor) = nullptr;
	void (*glGlobalAlphaFactordSUN) (GLdouble factor) = nullptr;
	void (*glGlobalAlphaFactorfSUN) (GLfloat factor) = nullptr;
	void (*glGlobalAlphaFactoriSUN) (GLint factor) = nullptr;
	void (*glGlobalAlphaFactorsSUN) (GLshort factor) = nullptr;
	void (*glGlobalAlphaFactorubSUN) (GLubyte factor) = nullptr;
	void (*glGlobalAlphaFactoruiSUN) (GLuint factor) = nullptr;
	void (*glGlobalAlphaFactorusSUN) (GLushort factor) = nullptr;
	bool SUN_global_alpha = false;

	//mesh_array
	bool SUN_mesh_array = false;

	//read_video_pixels
	void (*glReadVideoPixelsSUN) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels) = nullptr;
	bool SUN_read_video_pixels = false;

	//slice_accum
	bool SUN_slice_accum = false;

	//triangle list
	void (*glReplacementCodePointerSUN) (GLenum type, GLsizei stride, const void* pointer) = nullptr;
	void (*glReplacementCodeubSUN) (GLubyte code) = nullptr;
	void (*glReplacementCodeubvSUN) (const GLubyte* code) = nullptr;
	void (*glReplacementCodeuiSUN) (GLuint code) = nullptr;
	void (*glReplacementCodeuivSUN) (const GLuint* code) = nullptr;
	void (*glReplacementCodeusSUN) (GLushort code) = nullptr;
	void (*glReplacementCodeusvSUN) (const GLushort* code) = nullptr;
	bool SUN_triangle_list = false;

	//vertex
	void (*glColor3fVertex3fSUN) (GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glColor3fVertex3fvSUN) (const GLfloat* c, const GLfloat* v) = nullptr;
	void (*glColor4fNormal3fVertex3fSUN) (GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glColor4fNormal3fVertex3fvSUN) (const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	void (*glColor4ubVertex2fSUN) (GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y) = nullptr;
	void (*glColor4ubVertex2fvSUN) (const GLubyte* c, const GLfloat* v) = nullptr;
	void (*glColor4ubVertex3fSUN) (GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glColor4ubVertex3fvSUN) (const GLubyte* c, const GLfloat* v) = nullptr;
	void (*glNormal3fVertex3fSUN) (GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glNormal3fVertex3fvSUN) (const GLfloat* n, const GLfloat* v) = nullptr;
	void (*glReplacementCodeuiColor3fVertex3fSUN) (GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glReplacementCodeuiColor3fVertex3fvSUN) (const GLuint* rc, const GLfloat* c, const GLfloat* v) = nullptr;
	void (*glReplacementCodeuiColor4fNormal3fVertex3fSUN) (GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glReplacementCodeuiColor4fNormal3fVertex3fvSUN) (const GLuint* rc, const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	void (*glReplacementCodeuiColor4ubVertex3fSUN) (GLuint rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glReplacementCodeuiColor4ubVertex3fvSUN) (const GLuint* rc, const GLubyte* c, const GLfloat* v) = nullptr;
	void (*glReplacementCodeuiNormal3fVertex3fSUN) (GLuint rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glReplacementCodeuiNormal3fVertex3fvSUN) (const GLuint* rc, const GLfloat* n, const GLfloat* v) = nullptr;
	void (*glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN) (GLuint rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN) (const GLuint* rc, const GLfloat* tc, const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	void (*glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN) (GLuint rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN) (const GLuint* rc, const GLfloat* tc, const GLfloat* n, const GLfloat* v) = nullptr;
	void (*glReplacementCodeuiTexCoord2fVertex3fSUN) (GLuint rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glReplacementCodeuiTexCoord2fVertex3fvSUN) (const GLuint* rc, const GLfloat* tc, const GLfloat* v) = nullptr;
	void (*glReplacementCodeuiVertex3fSUN) (GLuint rc, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glReplacementCodeuiVertex3fvSUN) (const GLuint* rc, const GLfloat* v) = nullptr;
	void (*glTexCoord2fColor3fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glTexCoord2fColor3fVertex3fvSUN) (const GLfloat* tc, const GLfloat* c, const GLfloat* v) = nullptr;
	void (*glTexCoord2fColor4fNormal3fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glTexCoord2fColor4fNormal3fVertex3fvSUN) (const GLfloat* tc, const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	void (*glTexCoord2fColor4ubVertex3fSUN) (GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glTexCoord2fColor4ubVertex3fvSUN) (const GLfloat* tc, const GLubyte* c, const GLfloat* v) = nullptr;
	void (*glTexCoord2fNormal3fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glTexCoord2fNormal3fVertex3fvSUN) (const GLfloat* tc, const GLfloat* n, const GLfloat* v) = nullptr;
	void (*glTexCoord2fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glTexCoord2fVertex3fvSUN) (const GLfloat* tc, const GLfloat* v) = nullptr;
	void (*glTexCoord4fColor4fNormal3fVertex4fSUN) (GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void (*glTexCoord4fColor4fNormal3fVertex4fvSUN) (const GLfloat* tc, const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	void (*glTexCoord4fVertex4fSUN) (GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void (*glTexCoord4fVertex4fvSUN) (const GLfloat* tc, const GLfloat* v) = nullptr;
	bool SUN_vertex = false;

	//*< load SUN Extensions
	void LoadSUNExtensions()
	{
		//convolution_border_modes
		FetchProcAddress(SUN_convolution_border_modes, "SUN_convolution_border_modes");
		//global_alpha
		FetchProcAddress(glGlobalAlphaFactorbSUN, "glGlobalAlphaFactorbSUN");
		FetchProcAddress(glGlobalAlphaFactordSUN, "glGlobalAlphaFactordSUN");
		FetchProcAddress(glGlobalAlphaFactorfSUN, "glGlobalAlphaFactorfSUN");
		FetchProcAddress(glGlobalAlphaFactoriSUN, "glGlobalAlphaFactoriSUN");
		FetchProcAddress(glGlobalAlphaFactorsSUN, "glGlobalAlphaFactorsSUN");
		FetchProcAddress(glGlobalAlphaFactorubSUN, "glGlobalAlphaFactorubSUN");
		FetchProcAddress(glGlobalAlphaFactoruiSUN, "glGlobalAlphaFactoruiSUN");
		FetchProcAddress(glGlobalAlphaFactorusSUN, "glGlobalAlphaFactorusSUN");
		FetchProcAddress(SUN_global_alpha, "SUN_global_alpha");

		//mesh_array
		FetchProcAddress(SUN_mesh_array, "SUN_mesh_array");

		//read_video_pixels
		FetchProcAddress(glReadVideoPixelsSUN, "glReadVideoPixelsSUN");
		FetchProcAddress(SUN_read_video_pixels, "SUN_read_video_pixels");

		//slice_accum
		FetchProcAddress(SUN_slice_accum, "SUN_slice_accum");

		//triangle list
		FetchProcAddress(glReplacementCodePointerSUN, "glReplacementCodePointerSUN");
		FetchProcAddress(glReplacementCodeubSUN, "glReplacementCodeubSUN");
		FetchProcAddress(glReplacementCodeubvSUN, "glReplacementCodeubvSUN");
		FetchProcAddress(glReplacementCodeuiSUN, "glReplacementCodeuiSUN");
		FetchProcAddress(glReplacementCodeuivSUN, "glReplacementCodeuivSUN");
		FetchProcAddress(glReplacementCodeusSUN, "glReplacementCodeusSUN");
		FetchProcAddress(glReplacementCodeusvSUN, "glReplacementCodeusvSUN");
		FetchProcAddress(SUN_triangle_list, "SUN_triangle_list");

		//vertex
		FetchProcAddress(glColor3fVertex3fSUN, "glColor3fVertex3fSUN");
		FetchProcAddress(glColor3fVertex3fvSUN, "glColor3fVertex3fvSUN");
		FetchProcAddress(glColor4fNormal3fVertex3fSUN, "glColor4fNormal3fVertex3fSUN");
		FetchProcAddress(glColor4fNormal3fVertex3fvSUN, "glColor4fNormal3fVertex3fvSUN");
		FetchProcAddress(glColor4ubVertex2fSUN, "glColor4ubVertex2fSUN");
		FetchProcAddress(glColor4ubVertex2fvSUN, "glColor4ubVertex2fvSUN");
		FetchProcAddress(glColor4ubVertex3fSUN, "glColor4ubVertex3fSUN");
		FetchProcAddress(glColor4ubVertex3fvSUN, "glColor4ubVertex3fvSUN");
		FetchProcAddress(glNormal3fVertex3fSUN, "glNormal3fVertex3fSUN");
		FetchProcAddress(glNormal3fVertex3fvSUN, "glNormal3fVertex3fvSUN");
		FetchProcAddress(glReplacementCodeuiColor3fVertex3fSUN, "glReplacementCodeuiColor3fVertex3fSUN");
		FetchProcAddress(glReplacementCodeuiColor3fVertex3fvSUN, "glReplacementCodeuiColor3fVertex3fvSUN");
		FetchProcAddress(glReplacementCodeuiColor4fNormal3fVertex3fSUN, "glReplacementCodeuiColor4fNormal3fVertex3fSUN");
		FetchProcAddress(glReplacementCodeuiColor4fNormal3fVertex3fvSUN, "glReplacementCodeuiColor4fNormal3fVertex3fvSUN");
		FetchProcAddress(glReplacementCodeuiColor4ubVertex3fSUN, "glReplacementCodeuiColor4ubVertex3fSUN");
		FetchProcAddress(glReplacementCodeuiColor4ubVertex3fvSUN, "glReplacementCodeuiColor4ubVertex3fvSUN");
		FetchProcAddress(glReplacementCodeuiNormal3fVertex3fSUN, "glReplacementCodeuiNormal3fVertex3fSUN");
		FetchProcAddress(glReplacementCodeuiNormal3fVertex3fvSUN, "glReplacementCodeuiNormal3fVertex3fvSUN");
		FetchProcAddress(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN, "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN");
		FetchProcAddress(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN, "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN");
		FetchProcAddress(glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN, "glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN");
		FetchProcAddress(glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN, "glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN");
		FetchProcAddress(glReplacementCodeuiTexCoord2fVertex3fSUN, "glReplacementCodeuiTexCoord2fVertex3fSUN");
		FetchProcAddress(glReplacementCodeuiTexCoord2fVertex3fvSUN, "glReplacementCodeuiTexCoord2fVertex3fvSUN");
		FetchProcAddress(glReplacementCodeuiVertex3fSUN, "glReplacementCodeuiVertex3fSUN");
		FetchProcAddress(glReplacementCodeuiVertex3fvSUN, "glReplacementCodeuiVertex3fvSUN");
		FetchProcAddress(glTexCoord2fColor3fVertex3fSUN, "glTexCoord2fColor3fVertex3fSUN");
		FetchProcAddress(glTexCoord2fColor3fVertex3fvSUN, "glTexCoord2fColor3fVertex3fvSUN");
		FetchProcAddress(glTexCoord2fColor4fNormal3fVertex3fSUN, "glTexCoord2fColor4fNormal3fVertex3fSUN");
		FetchProcAddress(glTexCoord2fColor4fNormal3fVertex3fvSUN, "glTexCoord2fColor4fNormal3fVertex3fvSUN");
		FetchProcAddress(glTexCoord2fColor4ubVertex3fSUN, "glTexCoord2fColor4ubVertex3fSUN");
		FetchProcAddress(glTexCoord2fColor4ubVertex3fvSUN, "glTexCoord2fColor4ubVertex3fvSUN");
		FetchProcAddress(glTexCoord2fNormal3fVertex3fSUN, "glTexCoord2fNormal3fVertex3fSUN");
		FetchProcAddress(glTexCoord2fNormal3fVertex3fvSUN, "glTexCoord2fNormal3fVertex3fvSUN");
		FetchProcAddress(glTexCoord2fVertex3fSUN, "glTexCoord2fVertex3fSUN");
		FetchProcAddress(glTexCoord2fVertex3fvSUN, "glTexCoord2fVertex3fvSUN");
		FetchProcAddress(glTexCoord4fColor4fNormal3fVertex4fSUN, "glTexCoord4fColor4fNormal3fVertex4fSUN");
		FetchProcAddress(glTexCoord4fColor4fNormal3fVertex4fvSUN, "glTexCoord4fColor4fNormal3fVertex4fvSUN");
		FetchProcAddress(glTexCoord4fVertex4fSUN, "glTexCoord4fVertex4fSUN");
		FetchProcAddress(glTexCoord4fVertex4fvSUN, "glTexCoord4fVertex4fvSUN");
		FetchProcAddress(SUN_vertex, "SUN_vertex");
	}
	
#pragma endregion SUN Extensions

	//OpenGL WIN Extensions
#pragma region WIN 

	enum OpenGL_WIN_t
	{
		//phong shading
		gl_phong_win = 0x80ea,
		gl_phong_hint_win = 0x80eb,

		//specular fog
		gl_fog_specular_texture_win = 0x80ec,
	};

	//phong shading
	bool phong_shading = false;

	//scene markerXXX
	bool scene_markerXXX = false;

	//specular fog
	bool specular_fog = false;

	//swap hint
	void (*glAddSwapHintRectWIN) (GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	bool swap_hint = false;

	//*< load WIN Extensions
	void LoadWINExtensions()
	{
		//phong shading
		FetchProcAddress(phong_shading, "phong_shading");

		//scene markerXXX
		FetchProcAddress(scene_markerXXX, "scene_markerXXX");

		//specular fog
		FetchProcAddress(specular_fog, "specular_fog");

		//swap hint
		FetchProcAddress(glAddSwapHintRectWIN, "glAddSwapHintRectWIN");
		FetchProcAddress(swap_hint, "swap_hint");
	}

#pragma endregion WIN Extensions

	enum glVersion_t
	{
		version1_2 =		1L << 1,
		version1_3 =		1L << 2,
		version1_4 =		1L << 3,
		version1_5 =		1L << 4,
		version2_0 =		1L << 5,
		version2_1 =		1L << 6,
		version3_0 =		1L << 7,
		version3_1 =		1L << 8,
		version3_2 =		1L << 9,
		version3_3 =		1L << 10,
		version4_0 =		1L << 11,
		version4_1 =		1L << 12,
		version4_2 =		1L << 13,
		version4_3 =		1L << 14,
		version4_4 =		1L << 15,
		version4_5 =		1L << 16,
		version4_6 =		1L << 17,
	};

	enum vendor_t : long long unsigned int
	{
		V3DFX		 = 1L << 1,
		AMD			 = 1L << 2, 
		Android		 = 1L << 3,
		Angle		 = 1L << 4,
		Apple		 = 1L << 5,
		ARB			 = 1L << 6,
		ARM			 = 1L << 7,
		ATIX		 = 1L << 8,
		ATI			 = 1L << 9,
		EGL_KHR		 = 1L << 10,
		EGL_NV		 = 1L << 11,
		EXT			 = 1L << 12,
		Gremedy		 = 1L << 13,
		HP			 = 1L << 14,
		IBM			 = 1L << 15,
		INGR		 = 1L << 16,
		Intel		 = 1L << 17,
		KHR			 = 1L << 18,
		KTX			 = 1L << 19,
		MesaX		 = 1L << 20,
		Mesa		 = 1L << 21, 
		NVX			 = 1L << 22,
		NV			 = 1L << 23,
		OES			 = 1L << 24,
		OML			 = 1L << 25,
		OVR			 = 1L << 26,
		PGI			 = 1L << 27,
		QCOM		 = 1L << 28,
		Regal		 = 1L << 29,
		REND		 = 1L << 30,
		S3			 = 1L << 31,
		SGIS		 = 1L << 32,
		SGIX		 = 1L << 33,
		SGI			 = 1L << 34,
		SUNX		 = 1L << 35,
		SUN			 = 1L << 36,
		WIN			 = 1L << 37,
	};

	enum class error_t
	{
		success,
		loadFailed,
		versionLoadFailed,
		Unsupported1_2,
		Unsupported1_3,
		Unsupported1_4,
		Unsupported1_5,
		Unsupported2_0,
		Unsupported2_1,
		Unsupported3_0,
		Unsupported3_1,
		Unsupported3_2,
		Unsupported3_3,
		Unsupported4_0,
		Unsupported4_1,
		Unsupported4_2,
		Unsupported4_3,
		Unsupported4_4,
		Unsupported4_5,
		Unsupported4_6,
	};

	class error_category : public std::error_category
	{
	public:

		const char* name() const throw() override
		{
		return "TinyExtender";
		}

		/** 
		*	return the error message associated with the given error number
		*/
		virtual std::string message(int errorValue) const override
		{
		error_t err = (error_t)errorValue;
		switch (err)
		{
			case error_t::loadFailed:
			{
				return "Error: extension has failed to load";
			}

			case error_t::versionLoadFailed:
			{
				return "Error: Could not get OpenGL version";
			}

			case error_t::Unsupported1_2:
			{
				return "Error: OpenGL 1.2 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported1_3:
			{
				return "Error: OpenGL 1.3 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported1_4:
			{
				return "Error: OpenGL 1.4 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported1_5:
			{
				return "Error: OpenGL 1.5 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported2_0:
			{
				return "Error: OpenGL 2.0 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported2_1:
			{
				return "Error: OpenGL 2.1 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported3_0:
			{
				return "Error: OpenGL 3.0 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported3_1:
			{
				return "Error: OpenGL 3.1 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported3_2:
			{
				return "Error: OpenGL 3.2 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported3_3:
			{
				return "Error: OpenGL 3.3 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported4_0:
			{
				return "Error: OpenGL 4.0 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported4_1:
			{
				return "Error: OpenGL 4.1 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported4_2:
			{
				return "Error: OpenGL 4.2 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported4_3:
			{
				return "Error: OpenGL 4.3 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported4_4:
			{
				return "Error: OpenGL 4.4 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported4_5:
			{
				return "Error: OpenGL 4.5 extensions unsupported. stopping loading here";
			}

			case error_t::Unsupported4_6:
			{
				return "Error: OpenGL 4.6 extensions unsupported. stopping loading here";
			}

			default:
			{
				return "Error: unspecified error \n";
			}
		}
		}

		error_category() {};

		const static error_category& get()
		{
		const static error_category category;
		return category;
		}
	};

	std::error_code make_error_code(error_t errorCode)
	{
		return std::error_code(static_cast<int>(errorCode), error_category::get());
	}
};

namespace std
{
	template<> struct is_error_code_enum<TinyExtender::error_t> : std::true_type {};
};

namespace TinyExtender
{
	GLuint glVersionMajor;
	GLuint glVersionMinor;

	//*< get OpenGL version
	std::error_code InitializeGLVersion()
	{
		const GLubyte* versionString = glGetString(GL_VERSION);

		if (versionString != nullptr)
		{
			glVersionMajor = versionString[0] - '0';
			glVersionMinor = versionString[2] - '0';
			return TinyExtender::error_t::success;
		}

		else
		{
			return TinyExtender::error_t::versionLoadFailed;
		}
	}

	//*< load all Vendor Extensions
	void LoadAllVendors()
	{
		Load3DFXExtensions();
		LoadAMDExtensions();
		LoadAndroidExtensions();
		LoadAngleExtensions();
		LoadAppleExtensions();
		LoadARBExtensions();
		LoadARMExtensions();
		LoadATIXExtensions();
		LoadATIExtensions();
		LoadEGLKHRExtensions();
		LoadEGLNVExtensions();
		LoadEXTExtensions();
		LoadGremedyExtensions();
		LoadHPExtensions();
		LoadIBMExtensions();
		LoadINGRExtensions();
		LoadIntelExtensions();
		LoadKHRExtensions();
		LoadKTXExtensions();
		LoadMESAXExtensions();
		LoadMESAExtensions();
		LoadNVXExtensions();
		LoadNVExtensions();
		LoadOESExtensions();
		LoadOMLExtensions();
		LoadOVRExtensions();
		LoadPGIExtensions();
		LoadQCOMExtensions();
		LoadRegalExtensions();
		LoadS3Extensions();
		LoadSGISExtensions();
		LoadSGIXExtensions();
		LoadSGIExtensions();
		LoadSUNXExtensions();
		LoadSUNExtensions();
		LoadWINExtensions();
	}

	//*< load all applicable OpenGL extensions
	std::error_code InitializeExtentions()
	{
		std::error_code errCode = InitializeGLVersion();

		if (errCode == TinyExtender::error_t::versionLoadFailed)
		{
			return 	errCode;
		}

		//load vendor specific extensions first or last?

		if (glVersionMajor > 1 || (glVersionMinor >= 2 && glVersionMajor >= 1))
		{
			Load1_2Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported1_2;
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 3 && glVersionMajor >= 1))
		{
			Load1_3Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported1_3;
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 4 && glVersionMajor >= 1))
		{
			Load1_4Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported1_4;
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 5 && glVersionMajor >= 1))
		{
			Load1_5Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported1_5;
		}

		if (glVersionMajor >= 2)
		{
			Load2_0Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported2_0;
		}

		if (glVersionMajor > 2 || (glVersionMinor >= 1 && glVersionMajor >= 2))
		{
			Load2_1Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported2_1;
		}

		if (glVersionMajor >= 3)
		{
			Load3_0Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported3_0;
		}

		if (glVersionMajor > 3 || (glVersionMinor >= 1 && glVersionMajor >= 3))
		{
			Load3_1Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported3_1;
		}

		if (glVersionMajor > 3 || (glVersionMinor >= 2 && glVersionMajor >= 3))
		{
			Load3_2Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported3_2;
		}

		if (glVersionMajor > 3 || (glVersionMinor >= 3 && glVersionMajor >= 3))
		{
			Load3_3Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported3_3;
		}

		if (glVersionMajor >= 4)
		{
			Load4_0Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported4_0;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 1 && glVersionMajor >= 4))
		{
			Load4_1Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported4_1;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 2 && glVersionMajor >= 4))
		{
			Load4_2Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported4_2;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 3 && glVersionMajor >= 4))
		{
			Load4_3Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported4_3;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 4 && glVersionMajor >= 4))
		{
			Load4_4Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported4_4;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 5 && glVersionMajor >= 4))
		{
			Load4_5Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported4_5;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 6 && glVersionMajor >= 4))
		{
			Load4_6Extensions();
		}

		else
		{
			errCode = TinyExtender::error_t::Unsupported4_6;
		}

		//ok load all vendors here
		LoadAllVendors();
		errCode = TinyExtender::error_t::success;
		return errCode;
	}

	//*< load specific OpenGL extensions via OpenGL versions
	std::error_code InitializeExtensionsSpecific(unsigned int OpenGLVersions, long long unsigned int vendors)
	{
		std::error_code errCode = error_t::success;

		if (OpenGLVersions & glVersion_t::version1_2)
		{
			if (glVersionMajor > 1 || (glVersionMinor >= 2 && glVersionMajor >= 1))
			{
				Load1_2Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported1_2;
			}
		}

		if (OpenGLVersions & glVersion_t::version1_3)
		{
			if (glVersionMajor > 1 || (glVersionMinor >= 3 && glVersionMajor >= 1))
			{
				Load1_3Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported1_3;
			}
		}

		if (OpenGLVersions & glVersion_t::version1_4)
		{
			if (glVersionMajor > 1 || (glVersionMinor >= 4 && glVersionMajor >= 1))
			{
				Load1_4Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported1_4;
			}
		}

		if (OpenGLVersions & glVersion_t::version1_5)
		{
			if (glVersionMajor > 1 || (glVersionMinor >= 5 && glVersionMajor >= 1))
			{
				Load1_5Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported1_5;
			}
		}

		if (OpenGLVersions & glVersion_t::version2_0)
		{
			if (glVersionMajor > 2)
			{
				Load2_0Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported2_0;
			}
		}

		if (OpenGLVersions & glVersion_t::version2_1)
		{
			if (glVersionMajor > 2 || (glVersionMinor >= 1 && glVersionMajor >= 2))
			{
				Load2_1Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported2_1;
			}
		}

		if (OpenGLVersions & glVersion_t::version3_0)
		{
			if (glVersionMajor > 3)
			{
				Load3_0Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported3_0;
			}
		}

		if (OpenGLVersions & glVersion_t::version3_1)
		{
			if (glVersionMajor > 3 || (glVersionMinor >= 1 && glVersionMajor >= 3))
			{
				Load3_1Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported3_1;
			}
		}

		if (OpenGLVersions & glVersion_t::version3_2)
		{
			if (glVersionMajor > 3 || (glVersionMinor >= 2 && glVersionMajor >= 3))
			{
				Load3_2Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported3_2;
			}
		}

		if (OpenGLVersions & glVersion_t::version3_3)
		{
			if (glVersionMajor > 3 || (glVersionMinor >= 3 && glVersionMajor >= 3))
			{
				Load3_3Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported3_3;
			}
		}

		if (OpenGLVersions & glVersion_t::version4_0)
		{
			if (glVersionMajor > 4)
			{
				Load4_0Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported4_0;
			}
		}

		if (OpenGLVersions & glVersion_t::version4_1)
		{
			if (glVersionMajor > 4 || (glVersionMinor >= 1 && glVersionMajor >= 4))
			{
				Load4_1Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported4_1;
			}
		}

		if (OpenGLVersions & glVersion_t::version4_2)
		{
			if (glVersionMajor > 4 || (glVersionMinor >= 2 && glVersionMajor >= 4))
			{
				Load4_2Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported4_2;
			}
		}

		if (OpenGLVersions & glVersion_t::version4_3)
		{
			if (glVersionMajor > 4 || (glVersionMinor >= 3 && glVersionMajor >= 4))
			{
				Load4_3Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported4_3;
			}
		}

		if (OpenGLVersions & glVersion_t::version4_4)
		{
			if (glVersionMajor > 4 || (glVersionMinor >= 4 && glVersionMajor >= 4))
			{
				Load4_4Extensions();
			}

			else
			{
				errCode = TinyExtender::error_t::Unsupported4_4;
			}
		}

		if (vendors & vendor_t::V3DFX)
		{
			Load3DFXExtensions();
		}

		if (vendors & vendor_t::AMD)
		{
			LoadAMDExtensions();
		}
		if (vendors & vendor_t::Android)
		{
			LoadAndroidExtensions();
		}
		if (vendors & vendor_t::Angle)
		{
			LoadAngleExtensions();
		}
		if (vendors & vendor_t::Apple)
		{
			LoadAppleExtensions();
		}
		if (vendors & vendor_t::ARB)
		{
			LoadARBExtensions();
		}
		if (vendors & vendor_t::ARM)
		{
			LoadARMExtensions();
		}
		if (vendors & vendor_t::ATIX)
		{
			LoadATIXExtensions();
		}
		if (vendors & vendor_t::ATI)
		{
			LoadATIExtensions();
		}
		if (vendors & vendor_t::EGL_KHR)
		{
			LoadEGLKHRExtensions();
		}
		if (vendors & vendor_t::EGL_NV)
		{
			LoadEGLNVExtensions();
		}
		if (vendors & vendor_t::EXT)
		{
			LoadEXTExtensions();
		}
		if (vendors & vendor_t::Gremedy)
		{
			LoadGremedyExtensions();
		}
		if (vendors & vendor_t::HP)
		{
			LoadHPExtensions();
		}
		if (vendors & vendor_t::IBM)
		{
			LoadIBMExtensions();
		}
		if (vendors & vendor_t::INGR)
		{
			LoadINGRExtensions();
		}
		if (vendors & vendor_t::Intel)
		{
			LoadIntelExtensions();
		}
		if (vendors & vendor_t::KHR)
		{
			LoadKHRExtensions();
		}
		if (vendors & vendor_t::KTX)
		{
			LoadKTXExtensions();
		}
		if (vendors & vendor_t::MesaX)
		{
			LoadMESAXExtensions();
		}
		if (vendors & vendor_t::Mesa)
		{
			LoadMESAExtensions();
		}
		if (vendors & vendor_t::NVX)
		{
			LoadNVXExtensions();
		}
		if (vendors & vendor_t::NV)
		{
			LoadNVExtensions();
		}
		if (vendors & vendor_t::OES)
		{
			LoadOESExtensions();
		}
		if (vendors & vendor_t::OML)
		{
			LoadOMLExtensions();
		}
		if (vendors & vendor_t::OVR)
		{
			LoadOVRExtensions();
		}
		if (vendors & vendor_t::PGI)
		{
			LoadPGIExtensions();
		}
		if (vendors & vendor_t::QCOM)
		{
			LoadQCOMExtensions();
		}
		if (vendors & vendor_t::Regal)
		{
			LoadRegalExtensions();
		}
		if (vendors & vendor_t::REND)
		{
			LoadRENDExtensions();
		}
		if (vendors & vendor_t::S3)
		{
			LoadS3Extensions();
		}
		if (vendors & vendor_t::SGIS)
		{
			LoadSGISExtensions();
		}
		if (vendors & vendor_t::SGIX)
		{
			LoadSGIXExtensions();
		}
		if (vendors & vendor_t::SGI)
		{
			LoadSGIExtensions();
		}
		if (vendors & vendor_t::SUNX)
		{
			LoadSUNXExtensions();
		}
		if (vendors & vendor_t::SUN)
		{
			LoadSUNExtensions();
		}
		if (vendors & vendor_t::WIN)
		{
			LoadWINExtensions();
		}

		return errCode;
	}

	//*< whether an extension is supported
	bool IsExtensionSupported(const char* extensionName)
	{
		GLubyte* end;//the last extension name in Extensions
		size_t	nameLength; //the string length of the extension name

		nameLength = strlen((const char*)extensionName);

		GLubyte* allExtensions = (GLubyte*)glGetString(GL_EXTENSIONS); //get all supported extensions

		if (allExtensions != nullptr)
		{
			end = allExtensions + strlen((const char*)allExtensions);

			while (allExtensions < end)
			{
				size_t str = strcspn((const char*)allExtensions, "");

				if ((nameLength == str) && (strncmp((const char*)extensionName, (const char*)allExtensions, str) == 0))
				{
					return true;
				}

				allExtensions += (str + 1);
			}
		return false;
		}
		return false;
	}
}
#endif
