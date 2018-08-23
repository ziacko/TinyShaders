#ifndef TINYEXTENDER_H_
#define TINYEXTENDER_H_

#if defined(_WIN32) || defined(_WIN64)
#define TE_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif //WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX 1
#endif //NOMINMAX

#include <Windows.h>
#include <gl/GL.h>
#endif //_WIN32 || _WIN64

#if defined(__linux__)
#define TE_LINUX
#include <GL/glx.h>
#endif //__linux__

#include <system_error>
#include <cstring>

#ifndef GLEXT_64_TYPES_DEFINED
	/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#if defined(__STDC__)
	using int64_t = long long int;
	using uint64_t = unsigned long long int;
#endif /* __STDC__ */
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
	using int32_t = __int32;
	using int64_t = __int64;
	using uint64_t = unsigned __int64;
#else
	/* fall back if nothing above works */
#include <inttypes.h>
#endif
#endif

namespace TinyExtender
{
	//OpenGL 1.2 Extensions
	void(*glDrawRangeElements) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices) = nullptr;
	void(*glTexImage3D) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels) = nullptr;
	void(*glTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels) = nullptr;
	void(*glCopyTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	enum openGL1_2
	{
		gl_unsigned_byte_3_3_2 =				0x8032,
		gl_unsigned_short_4_4_4_4 =				0x8033,
		gl_unsigned_short_5_5_5_1 =				0x8034,
		gl_unsigned_int_8_8_8_8 =				0x8035,
		gl_unsigned_int_10_10_10_2 =			0x8036,
		gl_texture_binding_3d =					0x806a,
		gl_pack_skip_images =					0x806b,
		gl_pack_image_height =					0x806c,
		gl_unpack_skip_images =					0x806d,
		gl_unpack_image_height =				0x806e,
		gl_texture_3d =							0x806f,
		gl_proxy_texture_3d =					0x8070,
		gl_texture_depth =						0x8071,
		gl_texture_wrap_r =						0x8072,
		gl_max_3d_texture_size =				0x8073,
		gl_unsigned_byte_2_3_3_rev =			0x8362,
		gl_unsigned_short_5_6_5 =				0x8363,
		gl_unsigned_short_5_6_5_rev =			0x8364,
		gl_unsigned_short_4_4_4_4_rev =			0x8365,
		gl_unsigned_short_1_5_5_5_rev =			0x8366,
		gl_unsigned_int_8_8_8_8_rev =			0x8367,
		gl_unsigned_int_2_10_10_10_rev =		0x8368,
		gl_bgr =								0x80e0,
		gl_bgra =								0x80e1,
		gl_max_elements_vertices =				0x80e8,
		gl_max_elements_indices =				0x80e9,
		gl_clamp_to_edge =						0x812f,
		gl_texture_min_lod =					0x813a,
		gl_texture_max_lod =					0x813b,
		gl_texture_base_level =					0x813c,
		gl_texture_max_level =					0x813d,
		gl_smooth_point_size_range =			0x0b12,
		gl_smooth_point_size_granularity =		0x0b13,
		gl_smooth_line_width_range =			0x0b22,
		gl_smooth_line_width_granularity =		0x0b23,
		gl_aliased_line_width_range =			0x846e,
		gl_rescale_normal =						0x803a,
		gl_light_model_color_control =			0x81f8,
		gl_single_color =						0x81f9,
		gl_separate_specular_color =			0x81fa,
		gl_aliased_point_size_range =			0x846d
	};

	//OpenGL 1.3 Extensions
	void(*glActiveTexture) (GLenum texture) = nullptr;
	void(*glSampleCoverage) (GLfloat value, GLboolean invert) = nullptr;
	void(*glCompressedTexImage3D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data) = nullptr;
	void(*glCompressedTexImage2D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data) = nullptr;
	void(*glCompressedTexImage1D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data) = nullptr;
	void(*glCompressedTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data) = nullptr;
	void(*glCompressedTexSubImage2D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data) = nullptr;
	void(*glCompressedTexSubImage1D) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data) = nullptr;
	void(*glGetCompressedTexImage) (GLenum target, GLint level, void *img) = nullptr;
	void(*glClientActiveTexture) (GLenum texture) = nullptr;
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
	void(*glLoadTransposeMatrixf) (const GLfloat *m) = nullptr;
	void(*glLoadTransposeMatrixd) (const GLdouble *m) = nullptr;
	void(*glMultTransposeMatrixf) (const GLfloat *m) = nullptr;
	void(*glMultTransposeMatrixd) (const GLdouble *m) = nullptr;
	enum openGL1_3
	{
		gl_texture0 =								0x84c0,
		gl_texture1 =								0x84c1,
		gl_texture2 =								0x84c2,
		gl_texture3 =								0x84c3,
		gl_texture4 =								0x84c4,
		gl_texture5 =								0x84c5,
		gl_texture6 =								0x84c6,
		gl_texture7 =								0x84c7,
		gl_texture8 =								0x84c8,
		gl_texture9 =								0x84c9,
		gl_texture10 =								0x84ca,
		gl_texture11 =								0x84cb,
		gl_texture12 =								0x84cc,
		gl_texture13 =								0x84cd,
		gl_texture14 =								0x84ce,
		gl_texture15 =								0x84cf,
		gl_texture16 =								0x84d0,
		gl_texture17 =								0x84d1,
		gl_texture18 =								0x84d2,
		gl_texture19 =								0x84d3,
		gl_texture20 =								0x84d4,
		gl_texture21 =								0x84d5,
		gl_texture22 =								0x84d6,
		gl_texture23 =								0x84d7,
		gl_texture24 =								0x84d8,
		gl_texture25 =								0x84d9,
		gl_texture26 =								0x84da,
		gl_texture27 =								0x84db,
		gl_texture28 =								0x84dc,
		gl_texture29 =								0x84dd,
		gl_texture30 =								0x84de,
		gl_texture31 =								0x84df,
		gl_active_texture =							0x84e0,
		gl_multisample =							0x809d,
		gl_sample_alpha_to_coverage =				0x809e,
		gl_sample_alpha_to_one =					0x809f,
		gl_sample_coverage =						0x80a0,
		gl_sample_buffers =							0x80a8,
		gl_samples =								0x80a9,
		gl_sample_coverage_value =					0x80aa,
		gl_sample_coverage_invert =					0x80ab,
		gl_texture_cube_map =						0x8513,
		gl_texture_binding_cube_map =				0x8514,
		gl_texture_cube_map_positive_x =			0x8515,
		gl_texture_cube_map_negative_x =			0x8516,
		gl_texture_cube_map_positive_y =			0x8517,
		gl_texture_cube_map_negative_y =			0x8518,
		gl_texture_cube_map_positive_z =			0x8519,
		gl_texture_cube_map_negative_z =			0x851a,
		gl_proxy_texture_cube_map =					0x851b,
		gl_max_cube_map_texture_size =				0x851c,
		gl_compressed_rgb =							0x84ed,
		gl_compressed_rgba =						0x84ee,
		gl_texture_compression_hint =				0x84ef,
		gl_texture_compressed_image_size =			0x86a0,
		gl_texture_compressed =						0x86a1,
		gl_num_compressed_texture_formats =			0x86a2,
		gl_compressed_texture_formats =				0x86a3,
		gl_clamp_to_border =						0x812d,
		gl_client_active_texture =					0x84e1,
		gl_max_texture_units =						0x84e2,
		gl_transpose_modelview_matrix =				0x84e3,
		gl_transpose_projection_matrix =			0x84e4,
		gl_transpose_texture_matrix =				0x84e5,
		gl_transpose_color_matrix =					0x84e6,
		gl_multisample_bit =						0x20000000,
		gl_normal_map =								0x8511,
		gl_reflection_map =							0x8512,
		gl_compressed_alpha =						0x84e9,
		gl_compressed_luminance =					0x84ea,
		gl_compressed_luminance_alpha =				0x84eb,
		gl_compressed_intensity =					0x84ec,
		gl_combine =								0x8570,
		gl_combine_rgb =							0x8571,
		gl_combine_alpha =							0x8572,
		gl_source0_rgb =							0x8580,
		gl_source1_rgb =							0x8581,
		gl_source2_rgb =							0x8582,
		gl_source0_alpha =							0x8588,
		gl_source1_alpha =							0x8589,
		gl_source2_alpha =							0x858a,
		gl_operand0_rgb =							0x8590,
		gl_operand1_rgb =							0x8591,
		gl_operand2_rgb =							0x8592,
		gl_operand0_alpha =							0x8598,
		gl_operand1_alpha =							0x8599,
		gl_operand2_alpha =							0x859a,
		gl_rgb_scale =								0x8573,
		gl_add_signed =								0x8574,
		gl_interpolate =							0x8575,
		gl_subtract =								0x84e7,
		gl_constant =								0x8576,
		gl_primary_color =							0x8577,
		gl_previous =								0x8578,
		gl_dot3_rgb =								0x86ae,
		gl_dot3_rgba =								0x86af,
	};

	//OpenGL 1.4 Extensions
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
	void(*glBlendColor) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = nullptr;
	void(*glBlendEquation) (GLenum mode) = nullptr;
	enum openGL1_4
	{
		gl_blend_dst_rgb =						0x80c8,
		gl_blend_src_rgb =						0x80c9,
		gl_blend_dst_alpha =					0x80ca,
		gl_blend_src_alpha =					0x80cb,
		gl_point_fade_threshold_size =			0x8128,
		gl_depth_component16 =					0x81a5,
		gl_depth_component24 =					0x81a6,
		gl_depth_component32 =					0x81a7,
		gl_mirrored_repeat =					0x8370,
		gl_max_texture_lod_bias =				0x84fd,
		gl_texture_lod_bias =					0x8501,
		gl_incr_wrap =							0x8507,
		gl_decr_wrap =							0x8508,
		gl_texture_depth_size =					0x884a,
		gl_texture_compare_mode =				0x884c,
		gl_texture_compare_func =				0x884d,
		gl_point_size_min =						0x8126,
		gl_point_size_max =						0x8127,
		gl_point_distance_attenuation =			0x8129,
		gl_generate_mipmap =					0x8191,
		gl_generate_mipmap_hint =				0x8192,
		gl_fog_coordinate_source =				0x8450,
		gl_fog_coordinate =						0x8451,
		gl_fragment_depth =						0x8452,
		gl_current_fog_coordinate =				0x8453,
		gl_fog_coordinate_array_type =			0x8454,
		gl_fog_coordinate_array_stride =		0x8455,
		gl_fog_coordinate_array_pointer =		0x8456,
		gl_fog_coordinate_array =				0x8457,
		gl_color_sum =							0x8458,
		gl_current_secondary_color =			0x8459,
		gl_secondary_color_array_size =			0x845a,
		gl_secondary_color_array_type =			0x845b,
		gl_secondary_color_array_stride =		0x845c,
		gl_secondary_color_array_pointer =		0x845d,
		gl_secondary_color_array =				0x845e,
		gl_texture_filter_control =				0x8500,
		gl_depth_texture_mode =					0x884b,
		gl_compare_r_to_texture =				0x884e,
		gl_func_add =							0x8006,
		gl_func_subtract =						0x800a,
		gl_func_reverse_subtract =				0x800b,
		gl_min =								0x8007,
		gl_max =								0x8008,
		gl_constant_color =						0x8001,
		gl_one_minus_constant_color =			0x8002,
		gl_constant_alpha =						0x8003,
		gl_one_minus_constant_alpha =			0x8004
	};

	//OpenGL 1.5 Extensions
	using GLsizeiptr = ptrdiff_t;
	using GLintptr = ptrdiff_t;
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
	enum openGL1_5
	{
		gl_buffer_size =								0x8764,
		gl_buffer_usage =								0x8765,
		gl_query_counter_bits =							0x8864,
		gl_current_query =								0x8865,
		gl_query_result =								0x8866,
		gl_query_result_available =						0x8867,
		gl_array_buffer =								0x8892,
		gl_element_array_buffer =						0x8893,
		gl_array_buffer_binding =						0x8894,
		gl_element_array_buffer_binding =				0x8895,
		gl_vertex_attrib_array_buffer_binding =			0x889f,
		gl_read_only =									0x88b8,
		gl_write_only =									0x88b9,
		gl_read_write =									0x88ba,
		gl_buffer_access =								0x88bb,
		gl_buffer_mapped =								0x88bc,
		gl_buffer_map_pointer =							0x88bd,
		gl_stream_draw =								0x88e0,
		gl_stream_read =								0x88e1,
		gl_stream_copy =								0x88e2,
		gl_static_draw =								0x88e4,
		gl_static_read =								0x88e5,
		gl_static_copy =								0x88e6,
		gl_dynamic_draw =								0x88e8,
		gl_dynamic_read =								0x88e9,
		gl_dynamic_copy =								0x88ea,
		gl_samples_passed =								0x8914,
		gl_src1_alpha =									0x8589,
		gl_vertex_array_buffer_binding =				0x8896,
		gl_normal_array_buffer_binding =				0x8897,
		gl_color_array_buffer_binding =					0x8898,
		gl_index_array_buffer_binding =					0x8899,
		gl_texture_coord_array_buffer_binding =			0x889a,
		gl_edge_flag_array_buffer_binding =				0x889b,
		gl_secondary_color_array_buffer_binding =		0x889c,
		gl_fog_coordinate_array_buffer_binding =		0x889d,
		gl_weight_array_buffer_binding =				0x889e,
		gl_fog_coord_src =								0x8450,
		gl_fog_coord =									0x8451,
		gl_current_fog_coord =							0x8453,
		gl_fog_coord_array_type =						0x8454,
		gl_fog_coord_array_stride =						0x8455,
		gl_fog_coord_array_pointer =					0x8456,
		gl_fog_coord_array =							0x8457,
		gl_fog_coord_array_buffer_binding =				0x889d,
		gl_src0_rgb =									0x8580,
		gl_src1_rgb =									0x8581,
		gl_src2_rgb =									0x8582,
		gl_src0_alpha =									0x8588,
		gl_src2_alpha =									0x858a,
	};

	//2.0 extensions
	using GLchar = char;
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
	enum openGL2_0
	{
		gl_blend_equation_rgb =						0x8009,
		gl_vertex_attrib_array_enabled =			0x8622,
		gl_vertex_attrib_array_size =				0x8623,
		gl_vertex_attrib_array_stride =				0x8624,
		gl_vertex_attrib_array_type =				0x8625,
		gl_current_vertex_attrib =					0x8626,
		gl_vertex_program_point_size =				0x8642,
		gl_vertex_attrib_array_pointer =			0x8645,
		gl_stencil_back_func =						0x8800,
		gl_stencil_back_fail =						0x8801,
		gl_stencil_back_pass_depth_fail =			0x8802,
		gl_stencil_back_pass_depth_pass =			0x8803,
		gl_max_draw_buffers =						0x8824,
		gl_draw_buffer0 =							0x8825,
		gl_draw_buffer1 =							0x8826,
		gl_draw_buffer2 =							0x8827,
		gl_draw_buffer3 =							0x8828,
		gl_draw_buffer4 =							0x8829,
		gl_draw_buffer5 =							0x882a,
		gl_draw_buffer6 =							0x882b,
		gl_draw_buffer7 =							0x882c,
		gl_draw_buffer8 =							0x882d,
		gl_draw_buffer9 =							0x882e,
		gl_draw_buffer10 =							0x882f,
		gl_draw_buffer11 =							0x8830,
		gl_draw_buffer12 =							0x8831,
		gl_draw_buffer13 =							0x8832,
		gl_draw_buffer14 =							0x8833,
		gl_draw_buffer15 =							0x8834,
		gl_blend_equation_alpha =					0x883d,
		gl_max_vertex_attribs =						0x8869,
		gl_vertex_attrib_array_normalized =			0x886a,
		gl_max_texture_image_units =				0x8872,
		gl_fragment_shader =						0x8b30,
		gl_vertex_shader =							0x8b31,
		gl_max_fragment_uniform_components =		0x8b49,
		gl_max_vertex_uniform_components =			0x8b4a,
		gl_max_varying_floats =						0x8b4b,
		gl_max_vertex_texture_image_units =			0x8b4c,
		gl_max_combined_texture_image_units =		0x8b4d,
		gl_shader_type =							0x8b4f,
		gl_float_vec2 =								0x8b50,
		gl_float_vec3 =								0x8b51,
		gl_float_vec4 =								0x8b52,
		gl_int_vec2 =								0x8b53,
		gl_int_vec3 =								0x8b54,
		gl_int_vec4 =								0x8b55,
		gl_bool =									0x8b56,
		gl_bool_vec2 =								0x8b57,
		gl_bool_vec3 =								0x8b58,
		gl_bool_vec4 =								0x8b59,
		gl_float_mat2 =								0x8b5a,
		gl_float_mat3 =								0x8b5b,
		gl_float_mat4 =								0x8b5c,
		gl_sampler_1d =								0x8b5d,
		gl_sampler_2d =								0x8b5e,
		gl_sampler_3d =								0x8b5f,
		gl_sampler_cube =							0x8b60,
		gl_sampler_1d_shadow =						0x8b61,
		gl_sampler_2d_shadow =						0x8b62,
		gl_delete_status =							0x8b80,
		gl_compile_status =							0x8b81,
		gl_link_status =							0x8b82,
		gl_validate_status =						0x8b83,
		gl_info_log_length =						0x8b84,
		gl_attached_shaders =						0x8b85,
		gl_active_uniforms =						0x8b86,
		gl_active_uniform_max_length =				0x8b87,
		gl_shader_source_length =					0x8b88,
		gl_active_attributes =						0x8b89,
		gl_active_attribute_max_length =			0x8b8a,
		gl_fragment_shader_derivative_hint =		0x8b8b,
		gl_shading_language_version =				0x8b8c,
		gl_current_program =						0x8b8d,
		gl_point_sprite_coord_origin =				0x8ca0,
		gl_lower_left =								0x8ca1,
		gl_upper_left =								0x8ca2,
		gl_stencil_back_ref =						0x8ca3,
		gl_stencil_back_value_mask =				0x8ca4,
		gl_stencil_back_writemask =					0x8ca5,
		gl_vertex_program_two_side =				0x8643,
		gl_point_sprite =							0x8861,
		gl_coord_replace =							0x8862,
		gl_max_texture_coords =						0x8871
	};

	//OpenGL 2.1 Extensions
	void(*glUniformMatrix2x3fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix3x2fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix2x4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix4x2fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix3x4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glUniformMatrix4x3fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	enum openGL2_1
	{
		gl_pixel_pack_buffer =					0x88eb,
		gl_pixel_unpack_buffer =				0x88ec,
		gl_pixel_pack_buffer_binding =			0x88ed,
		gl_pixel_unpack_buffer_binding =		0x88ef,
		gl_float_mat2x3 =						0x8b65,
		gl_float_mat2x4 =						0x8b66,
		gl_float_mat3x2 =						0x8b67,
		gl_float_mat3x4 =						0x8b68,
		gl_float_mat4x2 =						0x8b69,
		gl_float_mat4x3 =						0x8b6a,
		gl_srgb =								0x8c40,
		gl_srgb8 =								0x8c41,
		gl_srgb_alpha =							0x8c42,
		gl_srgb8_alpha8 =						0x8c43,
		gl_compressed_srgb =					0x8c48,
		gl_compressed_srgb_alpha =				0x8c49,
		gl_current_raster_secondary_color =		0x845f,
		gl_sluminance_alpha =					0x8c44,
		gl_sluminance8_alpha8 =					0x8c45,
		gl_sluminance =							0x8c46,
		gl_sluminance8 =						0x8c47,
		gl_compressed_sluminance =				0x8c4a,
		gl_compressed_sluminance_alpha =		0x8c4b,
	};
	
	//3.0 extensions
	using GLhalf = unsigned short;
	void(*glColorMaski) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) = nullptr;
	void(*glGetBooleani_v) (GLenum target, GLuint index, GLboolean *data) = nullptr;
	void(*glGetIntegeri_v) (GLenum target, GLuint index, GLint *data) = nullptr;
	void(*glEnablei) (GLenum target, GLuint index) = nullptr;
	void(*glDisablei) (GLenum target, GLuint index) = nullptr;
	GLboolean(*glIsEnabledi) (GLenum target, GLuint index) = nullptr;
	void(*glBeginTransformFeedback) (GLenum primitiveMode) = nullptr;
	void(*glEndTransformFeedback) (void) = nullptr;
	void(*glBindBufferRange) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	void(*glBindBufferBase) (GLenum target, GLuint index, GLuint buffer) = nullptr;
	void(*glTransformFeedbackVaryings) (GLuint program, GLsizei count, const GLchar** varyings, GLenum bufferMode) = nullptr;
	void(*glGetTransformFeedbackVarying) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name) = nullptr;
	void(*glClampColor) (GLenum target, GLenum clamp) = nullptr;
	void(*glBeginConditionalRender) (GLuint id, GLenum mode) = nullptr;
	void(*glEndConditionalRender) (void) = nullptr;
	void(*glVertexAttribIPointer) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer) = nullptr;
	void(*glGetVertexAttribIiv) (GLuint index, GLenum pname, GLint *params) = nullptr;
	void(*glGetVertexAttribIuiv) (GLuint index, GLenum pname, GLuint *params) = nullptr;
	void(*glVertexAttribI1i) (GLuint index, GLint x) = nullptr;
	void(*glVertexAttribI2i) (GLuint index, GLint x, GLint y) = nullptr;
	void(*glVertexAttribI3i) (GLuint index, GLint x, GLint y, GLint z) = nullptr;
	void(*glVertexAttribI4i) (GLuint index, GLint x, GLint y, GLint z, GLint w) = nullptr;
	void(*glVertexAttribI1ui) (GLuint index, GLuint x) = nullptr;
	void(*glVertexAttribI2ui) (GLuint index, GLuint x, GLuint y) = nullptr;
	void(*glVertexAttribI3ui) (GLuint index, GLuint x, GLuint y, GLuint z) = nullptr;
	void(*glVertexAttribI4ui) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
	void(*glVertexAttribI1iv) (GLuint index, const GLint *v) = nullptr;
	void(*glVertexAttribI2iv) (GLuint index, const GLint *v) = nullptr;
	void(*glVertexAttribI3iv) (GLuint index, const GLint *v) = nullptr;
	void(*glVertexAttribI4iv) (GLuint index, const GLint *v) = nullptr;
	void(*glVertexAttribI1uiv) (GLuint index, const GLuint *v) = nullptr;
	void(*glVertexAttribI2uiv) (GLuint index, const GLuint *v) = nullptr;
	void(*glVertexAttribI3uiv) (GLuint index, const GLuint *v) = nullptr;
	void(*glVertexAttribI4uiv) (GLuint index, const GLuint *v) = nullptr;
	void(*glVertexAttribI4bv) (GLuint index, const GLbyte *v) = nullptr;
	void(*glVertexAttribI4sv) (GLuint index, const GLshort *v) = nullptr;
	void(*glVertexAttribI4ubv) (GLuint index, const GLubyte *v) = nullptr;
	void(*glVertexAttribI4usv) (GLuint index, const GLushort *v) = nullptr;
	void(*glGetUniformuiv) (GLuint program, GLint location, GLuint *params) = nullptr;
	void(*glBindFragDataLocation) (GLuint program, GLuint color, const GLchar *name) = nullptr;
	GLint(*glGetFragDataLocation) (GLuint program, const GLchar *name) = nullptr;
	void(*glUniform1ui) (GLint location, GLuint v0) = nullptr;
	void(*glUniform2ui) (GLint location, GLuint v0, GLuint v1) = nullptr;
	void(*glUniform3ui) (GLint location, GLuint v0, GLuint v1, GLuint v2) = nullptr;
	void(*glUniform4ui) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) = nullptr;
	void(*glUniform1uiv) (GLint location, GLsizei count, const GLuint *value) = nullptr;
	void(*glUniform2uiv) (GLint location, GLsizei count, const GLuint *value) = nullptr;
	void(*glUniform3uiv) (GLint location, GLsizei count, const GLuint *value) = nullptr;
	void(*glUniform4uiv) (GLint location, GLsizei count, const GLuint *value) = nullptr;
	void(*glTexParameterIiv) (GLenum target, GLenum pname, const GLint *params) = nullptr;
	void(*glTexParameterIuiv) (GLenum target, GLenum pname, const GLuint *params) = nullptr;
	void(*glGetTexParameterIiv) (GLenum target, GLenum pname, GLint *params) = nullptr;
	void(*glGetTexParameterIuiv) (GLenum target, GLenum pname, GLuint *params) = nullptr;
	void(*glClearBufferiv) (GLenum buffer, GLint drawbuffer, const GLint *value) = nullptr;
	void(*glClearBufferuiv) (GLenum buffer, GLint drawbuffer, const GLuint *value) = nullptr;
	void(*glClearBufferfv) (GLenum buffer, GLint drawbuffer, const GLfloat *value) = nullptr;
	void(*glClearBufferfi) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) = nullptr;
	const GLubyte* (*glGetStringi) (GLenum name, GLuint index) = nullptr;
	GLboolean(*glIsRenderbuffer) (GLuint renderbuffer) = nullptr;
	void(*glBindRenderbuffer) (GLenum target, GLuint renderbuffer) = nullptr;
	void(*glDeleteRenderbuffers) (GLsizei n, const GLuint *renderbuffers) = nullptr;
	void(*glGenRenderbuffers) (GLsizei n, GLuint *renderbuffers) = nullptr;
	void(*glRenderbufferStorage) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void(*glGetRenderbufferParameteriv) (GLenum target, GLenum pname, GLint *params) = nullptr;
	GLboolean(*glIsFramebuffer) (GLuint framebuffer) = nullptr;
	void(*glBindFramebuffer) (GLenum target, GLuint framebuffer) = nullptr;
	void(*glDeleteFramebuffers) (GLsizei n, const GLuint *framebuffers) = nullptr;
	void(*glGenFramebuffers) (GLsizei n, GLuint *framebuffers) = nullptr;
	GLenum(*glCheckFramebufferStatus) (GLenum target) = nullptr;
	void(*glFramebufferTexture1D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	void(*glFramebufferTexture2D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	void(*glFramebufferTexture3D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) = nullptr;
	void(*glFramebufferRenderbuffer) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
	void(*glGetFramebufferAttachmentParameteriv) (GLenum target, GLenum attachment, GLenum pname, GLint *params) = nullptr;
	void(*glGenerateMipmap) (GLenum target) = nullptr;
	void(*glBlitFramebuffer) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
	void(*glRenderbufferStorageMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void(*glFramebufferTextureLayer) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
	void *(*glMapBufferRange) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) = nullptr;
	void(*glFlushMappedBufferRange) (GLenum target, GLintptr offset, GLsizeiptr length) = nullptr;
	void(*glBindVertexArray) (GLuint array) = nullptr;
	void(*glDeleteVertexArrays) (GLsizei n, const GLuint *arrays) = nullptr;
	void(*glGenVertexArrays) (GLsizei n, GLuint *arrays) = nullptr;
	GLboolean(*glIsVertexArray) (GLuint array) = nullptr;
	enum openGL3_0
	{
		gl_compare_ref_to_texture =								0x884e,
		gl_clip_distance0 =										0x3000,
		gl_clip_distance1 =										0x3001,
		gl_clip_distance2 =										0x3002,
		gl_clip_distance3 =										0x3003,
		gl_clip_distance4 =										0x3004,
		gl_clip_distance5 =										0x3005,
		gl_clip_distance6 =										0x3006,
		gl_clip_distance7 =										0x3007,
		gl_max_clip_distances =									0x0d32,
		gl_major_version =										0x821b,
		gl_minor_version =										0x821c,
		gl_num_extensions =										0x821d,
		gl_context_flags =										0x821e,
		gl_compressed_red =										0x8225,
		gl_compressed_rg =										0x8226,
		gl_context_flag_forward_compatible_bit =				0x00000001,
		gl_rgba32f =											0x8814,
		gl_rgb32f =												0x8815,
		gl_rgba16f =											0x881a,
		gl_rgb16f =												0x881b,
		gl_vertex_attrib_array_integer =						0x88fd,
		gl_max_array_texture_layers =							0x88ff,
		gl_min_program_texel_offset =							0x8904,
		gl_max_program_texel_offset =							0x8905,
		gl_clamp_read_color =									0x891c,
		gl_fixed_only =											0x891d,
		gl_max_varying_components =								0x8b4b,
		gl_texture_1d_array =									0x8c18,
		gl_proxy_texture_1d_array =								0x8c19,
		gl_texture_2d_array =									0x8c1a,
		gl_proxy_texture_2d_array =								0x8c1b,
		gl_texture_binding_1d_array =							0x8c1c,
		gl_texture_binding_2d_array =							0x8c1d,
		gl_r11f_g11f_b10f =										0x8c3a,
		gl_unsigned_int_10f_11f_11f_rev =						0x8c3b,
		gl_rgb9_e5 =											0x8c3d,
		gl_unsigned_int_5_9_9_9_rev =							0x8c3e,
		gl_texture_shared_size =								0x8c3f,
		gl_transform_feedback_varying_max_length =				0x8c76,
		gl_transform_feedback_buffer_mode =						0x8c7f,
		gl_max_transform_feedback_separate_components =			0x8c80,
		gl_transform_feedback_varyings =						0x8c83,
		gl_transform_feedback_buffer_start =					0x8c84,
		gl_transform_feedback_buffer_size =						0x8c85,
		gl_primitives_generated =								0x8c87,
		gl_transform_feedback_primitives_written =				0x8c88,
		gl_rasterizer_discard =									0x8c89,
		gl_max_transform_feedback_interleaved_components =		0x8c8a,
		gl_max_transform_feedback_separate_attribs =			0x8c8b,
		gl_interleaved_attribs =								0x8c8c,
		gl_separate_attribs =									0x8c8d,
		gl_transform_feedback_buffer =							0x8c8e,
		gl_transform_feedback_buffer_binding =					0x8c8f,
		gl_rgba32ui =											0x8d70,
		gl_rgb32ui =											0x8d71,
		gl_rgba16ui =											0x8d76,
		gl_rgb16ui =											0x8d77,
		gl_rgba8ui =											0x8d7c,
		gl_rgb8ui =												0x8d7d,
		gl_rgba32i =											0x8d82,
		gl_rgb32i =												0x8d83,
		gl_rgba16i =											0x8d88,
		gl_rgb16i =												0x8d89,
		gl_rgba8i =												0x8d8e,
		gl_rgb8i =												0x8d8f,
		gl_red_integer =										0x8d94,
		gl_green_integer =										0x8d95,
		gl_blue_integer =										0x8d96,
		gl_rgb_integer =										0x8d98,
		gl_rgba_integer =										0x8d99,
		gl_bgr_integer =										0x8d9a,
		gl_bgra_integer =										0x8d9b,
		gl_sampler_1d_array =									0x8dc0,
		gl_sampler_2d_array =									0x8dc1,
		gl_sampler_1d_array_shadow =							0x8dc3,
		gl_sampler_2d_array_shadow =							0x8dc4,
		gl_sampler_cube_shadow =								0x8dc5,
		gl_unsigned_int_vec2 =									0x8dc6,
		gl_unsigned_int_vec3 =									0x8dc7,
		gl_unsigned_int_vec4 =									0x8dc8,
		gl_int_sampler_1d =										0x8dc9,
		gl_int_sampler_2d =										0x8dca,
		gl_int_sampler_3d =										0x8dcb,
		gl_int_sampler_cube =									0x8dcc,
		gl_int_sampler_1d_array =								0x8dce,
		gl_int_sampler_2d_array =								0x8dcf,
		gl_unsigned_int_sampler_1d =							0x8dd1,
		gl_unsigned_int_sampler_2d =							0x8dd2,
		gl_unsigned_int_sampler_3d =							0x8dd3,
		gl_unsigned_int_sampler_cube =							0x8dd4,
		gl_unsigned_int_sampler_1d_array =						0x8dd6,
		gl_unsigned_int_sampler_2d_array =						0x8dd7,
		gl_query_wait =											0x8e13,
		gl_query_no_wait =										0x8e14,
		gl_query_by_region_wait =								0x8e15,
		gl_query_by_region_no_wait =							0x8e16,
		gl_buffer_access_flags =								0x911f,
		gl_buffer_map_length =									0x9120,
		gl_buffer_map_offset =									0x9121,
		gl_depth_component32f =									0x8cac,
		gl_depth32f_stencil8 =									0x8cad,
		gl_float_32_unsigned_int_24_8_rev =						0x8dad,
		gl_invalid_framebuffer_operation =						0x0506,
		gl_framebuffer_attachment_color_encoding =				0x8210,
		gl_framebuffer_attachment_component_type =				0x8211,
		gl_framebuffer_attachment_red_size =					0x8212,
		gl_framebuffer_attachment_green_size =					0x8213,
		gl_framebuffer_attachment_blue_size =					0x8214,
		gl_framebuffer_attachment_alpha_size =					0x8215,
		gl_framebuffer_attachment_depth_size =					0x8216,
		gl_framebuffer_attachment_stencil_size =				0x8217,
		gl_framebuffer_default =								0x8218,
		gl_framebuffer_undefined =								0x8219,
		gl_depth_stencil_attachment =							0x821a,
		gl_max_renderbuffer_size =								0x84e8,
		gl_depth_stencil =										0x84f9,
		gl_unsigned_int_24_8 =									0x84fa,
		gl_depth24_stencil8 =									0x88f0,
		gl_texture_stencil_size =								0x88f1,
		gl_texture_red_type =									0x8c10,
		gl_texture_green_type =									0x8c11,
		gl_texture_blue_type =									0x8c12,
		gl_texture_alpha_type =									0x8c13,
		gl_texture_depth_type =									0x8c16,
		gl_unsigned_normalized =								0x8c17,
		gl_framebuffer_binding =								0x8ca6,
		gl_draw_framebuffer_binding =							0x8ca6,
		gl_renderbuffer_binding =								0x8ca7,
		gl_read_framebuffer =									0x8ca8,
		gl_draw_framebuffer =									0x8ca9,
		gl_read_framebuffer_binding =							0x8caa,
		gl_renderbuffer_samples =								0x8cab,
		gl_framebuffer_attachment_object_type =					0x8cd0,
		gl_framebuffer_attachment_object_name =					0x8cd1,
		gl_framebuffer_attachment_texture_level =				0x8cd2,
		gl_framebuffer_attachment_texture_cube_map_face =		0x8cd3,
		gl_framebuffer_attachment_texture_layer =				0x8cd4,
		gl_framebuffer_complete =								0x8cd5,
		gl_framebuffer_incomplete_attachment =					0x8cd6,
		gl_framebuffer_incomplete_missing_attachment =			0x8cd7,
		gl_framebuffer_incomplete_draw_buffer =					0x8cdb,
		gl_framebuffer_incomplete_read_buffer =					0x8cdc,
		gl_framebuffer_unsupported =							0x8cdd,
		gl_max_color_attachments =								0x8cdf,
		gl_color_attachment0 =									0x8ce0,
		gl_color_attachment1 =									0x8ce1,
		gl_color_attachment2 =									0x8ce2,
		gl_color_attachment3 =									0x8ce3,
		gl_color_attachment4 =									0x8ce4,
		gl_color_attachment5 =									0x8ce5,
		gl_color_attachment6 =									0x8ce6,
		gl_color_attachment7 =									0x8ce7,
		gl_color_attachment8 =									0x8ce8,
		gl_color_attachment9 =									0x8ce9,
		gl_color_attachment10 =									0x8cea,
		gl_color_attachment11 =									0x8ceb,
		gl_color_attachment12 =									0x8cec,
		gl_color_attachment13 =									0x8ced,
		gl_color_attachment14 =									0x8cee,
		gl_color_attachment15 =									0x8cef,
		gl_depth_attachment =									0x8d00,
		gl_stencil_attachment =									0x8d20,
		gl_framebuffer =										0x8d40,
		gl_renderbuffer =										0x8d41,
		gl_renderbuffer_width =									0x8d42,
		gl_renderbuffer_height =								0x8d43,
		gl_renderbuffer_internal_format =						0x8d44,
		gl_stencil_index1 =										0x8d46,
		gl_stencil_index4 =										0x8d47,
		gl_stencil_index8 =										0x8d48,
		gl_stencil_index16 =									0x8d49,
		gl_renderbuffer_red_size =								0x8d50,
		gl_renderbuffer_green_size =							0x8d51,
		gl_renderbuffer_blue_size =								0x8d52,
		gl_renderbuffer_alpha_size =							0x8d53,
		gl_renderbuffer_depth_size =							0x8d54,
		gl_renderbuffer_stencil_size =							0x8d55,
		gl_framebuffer_incomplete_multisample =					0x8d56,
		gl_max_samples =										0x8d57,
		gl_index =												0x8222,
		gl_texture_luminance_type =								0x8c14,
		gl_texture_intensity_type =								0x8c15,
		gl_framebuffer_srgb =									0x8db9,
		gl_half_float =											0x140b,
		gl_map_read_bit =										0x0001,
		gl_map_write_bit =										0x0002,
		gl_map_invalidate_range_bit =							0x0004,
		gl_map_invalidate_buffer_bit =							0x0008,
		gl_map_flush_explicit_bit =								0x0010,
		gl_map_unsynchronized_bit =								0x0020,
		gl_compressed_red_rgtc1 =								0x8dbb,
		gl_compressed_signed_red_rgtc1 =						0x8dbc,
		gl_compressed_rg_rgtc2 =								0x8dbd,
		gl_compressed_signed_rg_rgtc2 =							0x8dbe,
		gl_rg =													0x8227,
		gl_rg_integer =											0x8228,
		gl_r8 =													0x8229,
		gl_r16 =												0x822a,
		gl_rg8 =												0x822b,
		gl_rg16 =												0x822c,
		gl_r16f =												0x822d,
		gl_r32f =												0x822e,
		gl_rg16f =												0x822f,
		gl_rg32f =												0x8230,
		gl_r8i =												0x8231,
		gl_r8ui =												0x8232,
		gl_r16i =												0x8233,
		gl_r16ui =												0x8234,
		gl_r32i =												0x8235,
		gl_r32ui =												0x8236,
		gl_rg8i =												0x8237,
		gl_rg8ui =												0x8238,
		gl_rg16i =												0x8239,
		gl_rg16ui =												0x823a,
		gl_rg32i =												0x823b,
		gl_rg32ui =												0x823c,
		gl_vertex_array_binding =								0x85b5,
		gl_clamp_vertex_color =									0x891a,
		gl_clamp_fragment_color =								0x891b,
		gl_alpha_integer =										0x8d97,
	};

	//OpenGL 3.1 Extensions
	void(*glDrawArraysInstanced) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount) = nullptr;
	void(*glDrawElementsInstanced) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount) = nullptr;
	void(*glTexBuffer) (GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
	void(*glPrimitiveRestartIndex) (GLuint index) = nullptr;
	void(*glCopyBufferSubData) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) = nullptr;
	void(*glGetUniformIndices) (GLuint program, GLsizei uniformCount, const GLchar** uniformNames, GLuint *uniformIndices) = nullptr;
	void(*glGetActiveUniformsiv) (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params) = nullptr;
	void(*glGetActiveUniformName) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName) = nullptr;
	GLuint(*glGetUniformBlockIndex) (GLuint program, const GLchar *uniformBlockName) = nullptr;
	void(*glGetActiveUniformBlockiv) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params) = nullptr;
	void(*glGetActiveUniformBlockName) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName) = nullptr;
	void(*glUniformBlockBinding) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) = nullptr;
	enum openGL3_1
	{
		gl_sampler_2d_rect =									0x8b63,
		gl_sampler_2d_rect_shadow =								0x8b64,
		gl_sampler_buffer =										0x8dc2,
		gl_int_sampler_2d_rect =								0x8dcd,
		gl_int_sampler_buffer =									0x8dd0,
		gl_unsigned_int_sampler_2d_rect =						0x8dd5,
		gl_unsigned_int_sampler_buffer =						0x8dd8,
		gl_texture_buffer =										0x8c2a,
		gl_max_texture_buffer_size =							0x8c2b,
		gl_texture_binding_buffer =								0x8c2c,
		gl_texture_buffer_data_store_binding =					0x8c2d,
		gl_texture_rectangle =									0x84f5,
		gl_texture_binding_rectangle =							0x84f6,
		gl_proxy_texture_rectangle =							0x84f7,
		gl_max_rectangle_texture_size =							0x84f8,
		gl_r8_snorm =											0x8f94,
		gl_rg8_snorm =											0x8f95,
		gl_rgb8_snorm =											0x8f96,
		gl_rgba8_snorm =										0x8f97,
		gl_r16_snorm =											0x8f98,
		gl_rg16_snorm =											0x8f99,
		gl_rgb16_snorm =										0x8f9a,
		gl_rgba16_snorm =										0x8f9b,
		gl_signed_normalized =									0x8f9c,
		gl_primitive_restart =									0x8f9d,
		gl_primitive_restart_index =							0x8f9e,
		gl_copy_read_buffer =									0x8f36,
		gl_copy_write_buffer =									0x8f37,
		gl_uniform_buffer =										0x8a11,
		gl_uniform_buffer_binding =								0x8a28,
		gl_uniform_buffer_start =								0x8a29,
		gl_uniform_buffer_size =								0x8a2a,
		gl_max_vertex_uniform_blocks =							0x8a2b,
		gl_max_fragment_uniform_blocks =						0x8a2d,
		gl_max_combined_uniform_blocks =						0x8a2e,
		gl_max_uniform_buffer_bindings =						0x8a2f,
		gl_max_uniform_block_size =								0x8a30,
		gl_max_combined_vertex_uniform_components =				0x8a31,
		gl_max_combined_fragment_uniform_components =			0x8a33,
		gl_uniform_buffer_offset_alignment =					0x8a34,
		gl_active_uniform_block_max_name_length =				0x8a35,
		gl_active_uniform_blocks =								0x8a36,
		gl_uniform_type =										0x8a37,
		gl_uniform_size =										0x8a38,
		gl_uniform_name_length =								0x8a39,
		gl_uniform_block_index =								0x8a3a,
		gl_uniform_offset =										0x8a3b,
		gl_uniform_array_stride =								0x8a3c,
		gl_uniform_matrix_stride =								0x8a3d,
		gl_uniform_is_row_major =								0x8a3e,
		gl_uniform_block_binding =								0x8a3f,
		gl_uniform_block_data_size =							0x8a40,
		gl_uniform_block_name_length =							0x8a41,
		gl_uniform_block_active_uniforms =						0x8a42,
		gl_uniform_block_active_uniform_indices =				0x8a43,
		gl_uniform_block_referenced_by_vertex_shader =			0x8a44,
		gl_uniform_block_referenced_by_fragment_shader =		0x8a46,
		gl_invalid_index =										0xffffffffu
	};

	//OpenGL 3.2 Extensions
	typedef struct __GLsync* GLsync;
	using GLuint64 = uint64_t;
	using GLint64 = int64_t;
	void(*glDrawElementsBaseVertex) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex) = nullptr;
	void(*glDrawRangeElementsBaseVertex) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex) = nullptr;
	void(*glDrawElementsInstancedBaseVertex) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex) = nullptr;
	void(*glMultiDrawElementsBaseVertex) (GLenum mode, const GLsizei *count, GLenum type, const void** indices, GLsizei drawcount, const GLint *basevertex) = nullptr;
	void(*glProvokingVertex) (GLenum mode) = nullptr;
	GLsync(*glFenceSync) (GLenum condition, GLbitfield flags) = nullptr;
	GLboolean(*glIsSync) (GLsync sync) = nullptr;
	void(*glDeleteSync) (GLsync sync) = nullptr;
	GLenum(*glClientWaitSync) (GLsync sync, GLbitfield flags, GLuint64 timeout) = nullptr;
	void(*glWaitSync) (GLsync sync, GLbitfield flags, GLuint64 timeout) = nullptr;
	void(*glGetInteger64v) (GLenum pname, GLint64 *params) = nullptr;
	void(*glGetSynciv) (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values) = nullptr;
	void(*glGetInteger64i_v) (GLenum target, GLuint index, GLint64 *data) = nullptr;
	void(*glGetBufferParameteri64v) (GLenum target, GLenum pname, GLint64 *params) = nullptr;
	void(*glFramebufferTexture) (GLenum target, GLenum attachment, GLuint texture, GLint level) = nullptr;
	void(*glTexImage2DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	void(*glTexImage3DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
	void(*glGetMultisamplefv) (GLenum pname, GLuint index, GLfloat *val) = nullptr;
	void(*glSampleMaski) (GLuint index, GLbitfield mask) = nullptr;
	enum openGL3_2
	{
		gl_context_core_profile_bit =						0x00000001,
		gl_context_compatibility_profile_bit =				0x00000002,
		gl_lines_adjacency =								0x000a,
		gl_line_strip_adjacency =							0x000b,
		gl_triangles_adjacency =							0x000c,
		gl_triangle_strip_adjacency =						0x000d,
		gl_program_point_size =								0x8642,
		gl_max_geometry_texture_image_units =				0x8c29,
		gl_framebuffer_attachment_layered =					0x8da7,
		gl_framebuffer_incomplete_layer_targets =			0x8da8,
		gl_geometry_shader =								0x8dd9,
		gl_geometry_vertices_out =							0x8916,
		gl_geometry_input_type =							0x8917,
		gl_geometry_output_type =							0x8918,
		gl_max_geometry_uniform_components =				0x8ddf,
		gl_max_geometry_output_vertices =					0x8de0,
		gl_max_geometry_total_output_components =			0x8de1,
		gl_max_vertex_output_components =					0x9122,
		gl_max_geometry_input_components =					0x9123,
		gl_max_geometry_output_components =					0x9124,
		gl_max_fragment_input_components =					0x9125,
		gl_context_profile_mask =							0x9126,
		gl_depth_clamp =									0x864f,
		gl_quads_follow_provoking_vertex_convention =		0x8e4c,
		gl_first_vertex_convention =						0x8e4d,
		gl_last_vertex_convention =							0x8e4e,
		gl_provoking_vertex =								0x8e4f,
		gl_texture_cube_map_seamless =						0x884f,
		gl_max_server_wait_timeout =						0x9111,
		gl_object_type =									0x9112,
		gl_sync_condition =									0x9113,
		gl_sync_status =									0x9114,
		gl_sync_flags =										0x9115,
		gl_sync_fence =										0x9116,
		gl_sync_gpu_commands_complete =						0x9117,
		gl_unsignaled =										0x9118,
		gl_signaled =										0x9119,
		gl_already_signaled =								0x911a,
		gl_timeout_expired =								0x911b,
		gl_condition_satisfied =							0x911c,
		gl_wait_failed =									0x911d,
		gl_timeout_ignored =								0xffffffffffffffffull,
		gl_sync_flush_commands_bit =						0x00000001,
		gl_sample_position =								0x8e50,
		gl_sample_mask =									0x8e51,
		gl_sample_mask_value =								0x8e52,
		gl_max_sample_mask_words =							0x8e59,
		gl_texture_2d_multisample =							0x9100,
		gl_proxy_texture_2d_multisample =					0x9101,
		gl_texture_2d_multisample_array =					0x9102,
		gl_proxy_texture_2d_multisample_array =				0x9103,
		gl_texture_binding_2d_multisample =					0x9104,
		gl_texture_binding_2d_multisample_array =			0x9105,
		gl_texture_samples =								0x9106,
		gl_texture_fixed_sample_locations =					0x9107,
		gl_sampler_2d_multisample =							0x9108,
		gl_int_sampler_2d_multisample =						0x9109,
		gl_unsigned_int_sampler_2d_multisample =			0x910a,
		gl_sampler_2d_multisample_array =					0x910b,
		gl_int_sampler_2d_multisample_array =				0x910c,
		gl_unsigned_int_sampler_2d_multisample_array =		0x910d,
		gl_max_color_texture_samples =						0x910e,
		gl_max_depth_texture_samples =						0x910f,
		gl_max_integer_samples =							0x9110,
	};

	//OpenGL 3.3 Extensions
	void(*glBindFragDataLocationIndexed) (GLuint program, GLuint colorNumber, GLuint index, const GLchar *name) = nullptr;
	GLint(*glGetFragDataIndex) (GLuint program, const GLchar *name) = nullptr;
	void(*glGenSamplers) (GLsizei count, GLuint *samplers) = nullptr;
	void(*glDeleteSamplers) (GLsizei count, const GLuint *samplers) = nullptr;
	GLboolean(*glIsSampler) (GLuint sampler) = nullptr;
	void(*glBindSampler) (GLuint unit, GLuint sampler) = nullptr;
	void(*glSamplerParameteri) (GLuint sampler, GLenum pname, GLint param) = nullptr;
	void(*glSamplerParameteriv) (GLuint sampler, GLenum pname, const GLint *param) = nullptr;
	void(*glSamplerParameterf) (GLuint sampler, GLenum pname, GLfloat param) = nullptr;
	void(*glSamplerParameterfv) (GLuint sampler, GLenum pname, const GLfloat *param) = nullptr;
	void(*glSamplerParameterIiv) (GLuint sampler, GLenum pname, const GLint *param) = nullptr;
	void(*glSamplerParameterIuiv) (GLuint sampler, GLenum pname, const GLuint *param) = nullptr;
	void(*glGetSamplerParameteriv) (GLuint sampler, GLenum pname, GLint *params) = nullptr;
	void(*glGetSamplerParameterIiv) (GLuint sampler, GLenum pname, GLint *params) = nullptr;
	void(*glGetSamplerParameterfv) (GLuint sampler, GLenum pname, GLfloat *params) = nullptr;
	void(*glGetSamplerParameterIuiv) (GLuint sampler, GLenum pname, GLuint *params) = nullptr;
	void(*glQueryCounter) (GLuint id, GLenum target) = nullptr;
	void(*glGetQueryObjecti64v) (GLuint id, GLenum pname, GLint64 *params) = nullptr;
	void(*glGetQueryObjectui64v) (GLuint id, GLenum pname, GLuint64 *params) = nullptr;
	void(*glVertexAttribDivisor) (GLuint index, GLuint divisor) = nullptr;
	void(*glVertexAttribP1ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	void(*glVertexAttribP1uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value) = nullptr;
	void(*glVertexAttribP2ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	void(*glVertexAttribP2uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value) = nullptr;
	void(*glVertexAttribP3ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	void(*glVertexAttribP3uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value) = nullptr;
	void(*glVertexAttribP4ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	void(*glVertexAttribP4uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value) = nullptr;
	void(*glVertexP2ui) (GLenum type, GLuint value) = nullptr;
	void(*glVertexP2uiv) (GLenum type, const GLuint *value) = nullptr;
	void(*glVertexP3ui) (GLenum type, GLuint value) = nullptr;
	void(*glVertexP3uiv) (GLenum type, const GLuint *value) = nullptr;
	void(*glVertexP4ui) (GLenum type, GLuint value) = nullptr;
	void(*glVertexP4uiv) (GLenum type, const GLuint *value) = nullptr;
	void(*glTexCoordP1ui) (GLenum type, GLuint coords) = nullptr;
	void(*glTexCoordP1uiv) (GLenum type, const GLuint *coords) = nullptr;
	void(*glTexCoordP2ui) (GLenum type, GLuint coords) = nullptr;
	void(*glTexCoordP2uiv) (GLenum type, const GLuint *coords) = nullptr;
	void(*glTexCoordP3ui) (GLenum type, GLuint coords) = nullptr;
	void(*glTexCoordP3uiv) (GLenum type, const GLuint *coords) = nullptr;
	void(*glTexCoordP4ui) (GLenum type, GLuint coords) = nullptr;
	void(*glTexCoordP4uiv) (GLenum type, const GLuint *coords) = nullptr;
	void(*glMultiTexCoordP1ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	void(*glMultiTexCoordP1uiv) (GLenum texture, GLenum type, const GLuint *coords) = nullptr;
	void(*glMultiTexCoordP2ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	void(*glMultiTexCoordP2uiv) (GLenum texture, GLenum type, const GLuint *coords) = nullptr;
	void(*glMultiTexCoordP3ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	void(*glMultiTexCoordP3uiv) (GLenum texture, GLenum type, const GLuint *coords) = nullptr;
	void(*glMultiTexCoordP4ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	void(*glMultiTexCoordP4uiv) (GLenum texture, GLenum type, const GLuint *coords) = nullptr;
	void(*glNormalP3ui) (GLenum type, GLuint coords) = nullptr;
	void(*glNormalP3uiv) (GLenum type, const GLuint *coords) = nullptr;
	void(*glColorP3ui) (GLenum type, GLuint color) = nullptr;
	void(*glColorP3uiv) (GLenum type, const GLuint *color) = nullptr;
	void(*glColorP4ui) (GLenum type, GLuint color) = nullptr;
	void(*glColorP4uiv) (GLenum type, const GLuint *color) = nullptr;
	void(*glSecondaryColorP3ui) (GLenum type, GLuint color) = nullptr;
	void(*glSecondaryColorP3uiv) (GLenum type, const GLuint *color) = nullptr;
	enum openGL3_3
	{
		gl_vertex_attrib_array_divisor =		0x88fe,
		gl_src1_color =							0x88f9,
		gl_one_minus_src1_color =				0x88fa,
		gl_one_minus_src1_alpha =				0x88fb,
		gl_max_dual_source_draw_buffers =		0x88fc,
		gl_any_samples_passed =					0x8c2f,
		gl_sampler_binding =					0x8919,
		gl_rgb10_a2ui =							0x906f,
		gl_texture_swizzle_r =					0x8e42,
		gl_texture_swizzle_g =					0x8e43,
		gl_texture_swizzle_b =					0x8e44,
		gl_texture_swizzle_a =					0x8e45,
		gl_texture_swizzle_rgba =				0x8e46,
		gl_time_elapsed =						0x88bf,
		gl_timestamp =							0x8e28,
		gl_int_2_10_10_10_rev =					0x8d9f,
	};

	//OpenGL 4.0 Extensions
	void(*glMinSampleShading) (GLfloat value) = nullptr;
	void(*glBlendEquationi) (GLuint buf, GLenum mode) = nullptr;
	void(*glBlendEquationSeparatei) (GLuint buf, GLenum modeRGB, GLenum modeAlpha) = nullptr;
	void(*glBlendFunci) (GLuint buf, GLenum src, GLenum dst) = nullptr;
	void(*glBlendFuncSeparatei) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = nullptr;
	void(*glDrawArraysIndirect) (GLenum mode, const void* indirect) = nullptr;
	void(*glDrawElementsIndirect) (GLenum mode, GLenum type, const void* indirect) = nullptr;
	void(*glUniform1d) (GLint location, GLdouble x) = nullptr;
	void(*glUniform2d) (GLint location, GLdouble x, GLdouble y) = nullptr;
	void(*glUniform3d) (GLint location, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void(*glUniform4d) (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void(*glUniform1dv) (GLint location, GLsizei count, const GLdouble *value) = nullptr;
	void(*glUniform2dv) (GLint location, GLsizei count, const GLdouble *value) = nullptr;
	void(*glUniform3dv) (GLint location, GLsizei count, const GLdouble *value) = nullptr;
	void(*glUniform4dv) (GLint location, GLsizei count, const GLdouble *value) = nullptr;
	void(*glUniformMatrix2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glUniformMatrix3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glUniformMatrix4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glUniformMatrix2x3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glUniformMatrix2x4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glUniformMatrix3x2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glUniformMatrix3x4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glUniformMatrix4x2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glUniformMatrix4x3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glGetUniformdv) (GLuint program, GLint location, GLdouble *params) = nullptr;
	GLint(*glGetSubroutineUniformLocation) (GLuint program, GLenum shadertype, const GLchar *name) = nullptr;
	GLuint(*glGetSubroutineIndex) (GLuint program, GLenum shadertype, const GLchar *name) = nullptr;
	void(*glGetActiveSubroutineUniformiv) (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values) = nullptr;
	void(*glGetActiveSubroutineUniformName) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name) = nullptr;
	void(*glGetActiveSubroutineName) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name) = nullptr;
	void(*glUniformSubroutinesuiv) (GLenum shadertype, GLsizei count, const GLuint *indices) = nullptr;
	void(*glGetUniformSubroutineuiv) (GLenum shadertype, GLint location, GLuint *params) = nullptr;
	void(*glGetProgramStageiv) (GLuint program, GLenum shadertype, GLenum pname, GLint *values) = nullptr;
	void(*glPatchParameteri) (GLenum pname, GLint value) = nullptr;
	void(*glPatchParameterfv) (GLenum pname, const GLfloat *values) = nullptr;
	void(*glBindTransformFeedback) (GLenum target, GLuint id) = nullptr;
	void(*glDeleteTransformFeedbacks) (GLsizei n, const GLuint *ids) = nullptr;
	void(*glGenTransformFeedbacks) (GLsizei n, GLuint *ids) = nullptr;
	GLboolean(*glIsTransformFeedback) (GLuint id) = nullptr;
	void(*glPauseTransformFeedback) (void) = nullptr;
	void(*glResumeTransformFeedback) (void) = nullptr;
	void(*glDrawTransformFeedback) (GLenum mode, GLuint id) = nullptr;
	void(*glDrawTransformFeedbackStream) (GLenum mode, GLuint id, GLuint stream) = nullptr;
	void(*glBeginQueryIndexed) (GLenum target, GLuint index, GLuint id) = nullptr;
	void(*glEndQueryIndexed) (GLenum target, GLuint index) = nullptr;
	void(*glGetQueryIndexediv) (GLenum target, GLuint index, GLenum pname, GLint *params) = nullptr;
	enum openGL4_0
	{
		gl_sample_shading =												0x8c36,
		gl_min_sample_shading_value =									0x8c37,
		gl_min_program_texture_gather_offset =							0x8e5e,
		gl_max_program_texture_gather_offset =							0x8e5f,
		gl_texture_cube_map_array =										0x9009,
		gl_texture_binding_cube_map_array =								0x900a,
		gl_proxy_texture_cube_map_array =								0x900b,
		gl_sampler_cube_map_array =										0x900c,
		gl_sampler_cube_map_array_shadow =								0x900d,
		gl_int_sampler_cube_map_array =									0x900e,
		gl_unsigned_int_sampler_cube_map_array =						0x900f,
		gl_draw_indirect_buffer =										0x8f3f,
		gl_draw_indirect_buffer_binding =								0x8f43,
		gl_geometry_shader_invocations =								0x887f,
		gl_max_geometry_shader_invocations =							0x8e5a,
		gl_min_fragment_interpolation_offset =							0x8e5b,
		gl_max_fragment_interpolation_offset =							0x8e5c,
		gl_fragment_interpolation_offset_bits =							0x8e5d,
		gl_max_vertex_streams =											0x8e71,
		gl_double_vec2 =												0x8ffc,
		gl_double_vec3 =												0x8ffd,
		gl_double_vec4 =												0x8ffe,
		gl_double_mat2 =												0x8f46,
		gl_double_mat3 =												0x8f47,
		gl_double_mat4 =												0x8f48,
		gl_double_mat2x3 =												0x8f49,
		gl_double_mat2x4 =												0x8f4a,
		gl_double_mat3x2 =												0x8f4b,
		gl_double_mat3x4 =												0x8f4c,
		gl_double_mat4x2 =												0x8f4d,
		gl_double_mat4x3 =												0x8f4e,
		gl_active_subroutines =											0x8de5,
		gl_active_subroutine_uniforms =									0x8de6,
		gl_active_subroutine_uniform_locations =						0x8e47,
		gl_active_subroutine_max_length =								0x8e48,
		gl_active_subroutine_uniform_max_length =						0x8e49,
		gl_max_subroutines =											0x8de7,
		gl_max_subroutine_uniform_locations =							0x8de8,
		gl_num_compatible_subroutines =									0x8e4a,
		gl_compatible_subroutines =										0x8e4b,
		gl_patches =													0x000e,
		gl_patch_vertices =												0x8e72,
		gl_patch_default_inner_level =									0x8e73,
		gl_patch_default_outer_level =									0x8e74,
		gl_tess_control_output_vertices =								0x8e75,
		gl_tess_gen_mode =												0x8e76,
		gl_tess_gen_spacing =											0x8e77,
		gl_tess_gen_vertex_order =										0x8e78,
		gl_tess_gen_point_mode =										0x8e79,
		gl_isolines =													0x8e7a,
		gl_fractional_odd =												0x8e7b,
		gl_fractional_even =											0x8e7c,
		gl_max_patch_vertices =											0x8e7d,
		gl_max_tess_gen_level =											0x8e7e,
		gl_max_tess_control_uniform_components =						0x8e7f,
		gl_max_tess_evaluation_uniform_components =						0x8e80,
		gl_max_tess_control_texture_image_units =						0x8e81,
		gl_max_tess_evaluation_texture_image_units =					0x8e82,
		gl_max_tess_control_output_components =							0x8e83,
		gl_max_tess_patch_components =									0x8e84,
		gl_max_tess_control_total_output_components =					0x8e85,
		gl_max_tess_evaluation_output_components =						0x8e86,
		gl_max_tess_control_uniform_blocks =							0x8e89,
		gl_max_tess_evaluation_uniform_blocks =							0x8e8a,
		gl_max_tess_control_input_components =							0x886c,
		gl_max_tess_evaluation_input_components =						0x886d,
		gl_max_combined_tess_control_uniform_components =				0x8e1e,
		gl_max_combined_tess_evaluation_uniform_components =			0x8e1f,
		gl_uniform_block_referenced_by_tess_control_shader =			0x84f0,
		gl_uniform_block_referenced_by_tess_evaluation_shader =			0x84f1,
		gl_tess_evaluation_shader =										0x8e87,
		gl_tess_control_shader =										0x8e88,
		gl_transform_feedback =											0x8e22,
		gl_transform_feedback_buffer_paused =							0x8e23,
		gl_transform_feedback_buffer_active =							0x8e24,
		gl_transform_feedback_binding =									0x8e25,
		gl_max_transform_feedback_buffers =								0x8e70,
	};

	//OpenGL 4.1 Extensions
	void(*glReleaseShaderCompiler) (void) = nullptr;
	void(*glShaderBinary) (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length) = nullptr;
	void(*glGetShaderPrecisionFormat) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision) = nullptr;
	void(*glDepthRangef) (GLfloat n, GLfloat f) = nullptr;
	void(*glClearDepthf) (GLfloat d) = nullptr;
	void(*glGetProgramBinary) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary) = nullptr;
	void(*glProgramBinary) (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length) = nullptr;
	void(*glProgramParameteri) (GLuint program, GLenum pname, GLint value) = nullptr;
	void(*glUseProgramStages) (GLuint pipeline, GLbitfield stages, GLuint program) = nullptr;
	void(*glActiveShaderProgram) (GLuint pipeline, GLuint program) = nullptr;
	GLuint(*glCreateShaderProgramv) (GLenum type, GLsizei count, const GLchar *const*strings) = nullptr;
	void(*glBindProgramPipeline) (GLuint pipeline) = nullptr;
	void(*glDeleteProgramPipelines) (GLsizei n, const GLuint *pipelines) = nullptr;
	void(*glGenProgramPipelines) (GLsizei n, GLuint *pipelines) = nullptr;
	GLboolean(*glIsProgramPipeline) (GLuint pipeline) = nullptr;
	void(*glGetProgramPipelineiv) (GLuint pipeline, GLenum pname, GLint *params) = nullptr;
	void(*glProgramUniform1i) (GLuint program, GLint location, GLint v0) = nullptr;
	void(*glProgramUniform1iv) (GLuint program, GLint location, GLsizei count, const GLint *value) = nullptr;
	void(*glProgramUniform1f) (GLuint program, GLint location, GLfloat v0) = nullptr;
	void(*glProgramUniform1fv) (GLuint program, GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void(*glProgramUniform1d) (GLuint program, GLint location, GLdouble v0) = nullptr;
	void(*glProgramUniform1dv) (GLuint program, GLint location, GLsizei count, const GLdouble *value) = nullptr;
	void(*glProgramUniform1ui) (GLuint program, GLint location, GLuint v0) = nullptr;
	void(*glProgramUniform1uiv) (GLuint program, GLint location, GLsizei count, const GLuint *value) = nullptr;
	void(*glProgramUniform2i) (GLuint program, GLint location, GLint v0, GLint v1) = nullptr;
	void(*glProgramUniform2iv) (GLuint program, GLint location, GLsizei count, const GLint *value) = nullptr;
	void(*glProgramUniform2f) (GLuint program, GLint location, GLfloat v0, GLfloat v1) = nullptr;
	void(*glProgramUniform2fv) (GLuint program, GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void(*glProgramUniform2d) (GLuint program, GLint location, GLdouble v0, GLdouble v1) = nullptr;
	void(*glProgramUniform2dv) (GLuint program, GLint location, GLsizei count, const GLdouble *value) = nullptr;
	void(*glProgramUniform2ui) (GLuint program, GLint location, GLuint v0, GLuint v1) = nullptr;
	void(*glProgramUniform2uiv) (GLuint program, GLint location, GLsizei count, const GLuint *value) = nullptr;
	void(*glProgramUniform3i) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2) = nullptr;
	void(*glProgramUniform3iv) (GLuint program, GLint location, GLsizei count, const GLint *value) = nullptr;
	void(*glProgramUniform3f) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) = nullptr;
	void(*glProgramUniform3fv) (GLuint program, GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void(*glProgramUniform3d) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2) = nullptr;
	void(*glProgramUniform3dv) (GLuint program, GLint location, GLsizei count, const GLdouble *value) = nullptr;
	void(*glProgramUniform3ui) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) = nullptr;
	void(*glProgramUniform3uiv) (GLuint program, GLint location, GLsizei count, const GLuint *value) = nullptr;
	void(*glProgramUniform4i) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) = nullptr;
	void(*glProgramUniform4iv) (GLuint program, GLint location, GLsizei count, const GLint *value) = nullptr;
	void(*glProgramUniform4f) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) = nullptr;
	void(*glProgramUniform4fv) (GLuint program, GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void(*glProgramUniform4d) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) = nullptr;
	void(*glProgramUniform4dv) (GLuint program, GLint location, GLsizei count, const GLdouble *value) = nullptr;
	void(*glProgramUniform4ui) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) = nullptr;
	void(*glProgramUniform4uiv) (GLuint program, GLint location, GLsizei count, const GLuint *value) = nullptr;
	void(*glProgramUniformMatrix2fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glProgramUniformMatrix3fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glProgramUniformMatrix4fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glProgramUniformMatrix2dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glProgramUniformMatrix3dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glProgramUniformMatrix4dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glProgramUniformMatrix2x3fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glProgramUniformMatrix3x2fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glProgramUniformMatrix2x4fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glProgramUniformMatrix4x2fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glProgramUniformMatrix3x4fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glProgramUniformMatrix4x3fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void(*glProgramUniformMatrix2x3dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glProgramUniformMatrix3x2dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glProgramUniformMatrix2x4dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glProgramUniformMatrix4x2dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glProgramUniformMatrix3x4dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glProgramUniformMatrix4x3dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) = nullptr;
	void(*glValidateProgramPipeline) (GLuint pipeline) = nullptr;
	void(*glGetProgramPipelineInfoLog) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog) = nullptr;
	void(*glVertexAttribL1d) (GLuint index, GLdouble x) = nullptr;
	void(*glVertexAttribL2d) (GLuint index, GLdouble x, GLdouble y) = nullptr;
	void(*glVertexAttribL3d) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	void(*glVertexAttribL4d) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	void(*glVertexAttribL1dv) (GLuint index, const GLdouble *v) = nullptr;
	void(*glVertexAttribL2dv) (GLuint index, const GLdouble *v) = nullptr;
	void(*glVertexAttribL3dv) (GLuint index, const GLdouble *v) = nullptr;
	void(*glVertexAttribL4dv) (GLuint index, const GLdouble *v) = nullptr;
	void(*glVertexAttribLPointer) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer) = nullptr;
	void(*glGetVertexAttribLdv) (GLuint index, GLenum pname, GLdouble *params) = nullptr;
	void(*glViewportArrayv) (GLuint first, GLsizei count, const GLfloat *v) = nullptr;
	void(*glViewportIndexedf) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) = nullptr;
	void(*glViewportIndexedfv) (GLuint index, const GLfloat *v) = nullptr;
	void(*glScissorArrayv) (GLuint first, GLsizei count, const GLint *v) = nullptr;
	void(*glScissorIndexed) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) = nullptr;
	void(*glScissorIndexedv) (GLuint index, const GLint *v) = nullptr;
	void(*glDepthRangeIndexed) (GLuint first, GLsizei count, const GLdouble *v) = nullptr;
	void(*glDepthRangeArrayv) (GLuint index, GLdouble n, GLdouble f) = nullptr;
	void(*glGetFloati_v) (GLenum target, GLuint index, GLfloat *data) = nullptr;
	void(*glGetDoublei_v) (GLenum target, GLuint index, GLdouble *data) = nullptr;
	enum openGL4_1
	{
		gl_fixed =									0x140c,
		gl_implementation_color_read_type =			0x8b9a,
		gl_implementation_color_read_format =		0x8b9b,
		gl_low_float =								0x8df0,
		gl_medium_float =							0x8df1,
		gl_high_float =								0x8df2,
		gl_low_int =								0x8df3,
		gl_medium_int =								0x8df4,
		gl_high_int =								0x8df5,
		gl_shader_compiler =						0x8dfa,
		gl_shader_binary_formats =					0x8df8,
		gl_num_shader_binary_formats =				0x8df9,
		gl_max_vertex_uniform_vectors =				0x8dfb,
		gl_max_varying_vectors =					0x8dfc,
		gl_max_fragment_uniform_vectors =			0x8dfd,
		gl_rgb565 =									0x8d62,
		gl_program_binary_retrievable_hint =		0x8257,
		gl_program_binary_length =					0x8741,
		gl_num_program_binary_formats =				0x87fe,
		gl_program_binary_formats =					0x87ff,
		gl_vertex_shader_bit =						0x00000001,
		gl_fragment_shader_bit =					0x00000002,
		gl_geometry_shader_bit =					0x00000004,
		gl_tess_control_shader_bit =				0x00000008,
		gl_tess_evaluation_shader_bit =				0x00000010,
		gl_all_shader_bits =						0xffffffff,
		gl_program_separable =						0x8258,
		gl_active_program =							0x8259,
		gl_program_pipeline_binding =				0x825a,
		gl_max_viewports =							0x825b,
		gl_viewport_subpixel_bits =					0x825c,
		gl_viewport_bounds_range =					0x825d,
		gl_layer_provoking_vertex =					0x825e,
		gl_viewport_index_provoking_vertex =		0x825f,
		gl_undefined_vertex =						0x8260
	};

	//OpenGL 4.2 Extensions
	void(*glDrawArraysInstancedBaseInstance) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) = nullptr;
	void(*glDrawElementsInstancedBaseInstance) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance) = nullptr;
	void(*glDrawElementsInstancedBaseVertexBaseInstance) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) = nullptr;
	void(*glGetInternalformativ) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params) = nullptr;
	void(*glGetActiveAtomicCounterBufferiv) (GLuint program, GLuint bufferIndex, GLenum pname, GLint *params) = nullptr;
	void(*glBindImageTexture) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) = nullptr;
	void(*glMemoryBarrier) (GLbitfield barriers) = nullptr;
	void(*glTexStorage1D) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) = nullptr;
	void(*glTexStorage2D) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void(*glTexStorage3D) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
	void(*glDrawTransformFeedbackInstanced) (GLenum mode, GLuint id, GLsizei instancecount) = nullptr;
	void(*glDrawTransformFeedbackStreamInstanced) (GLenum mode, GLuint id, GLuint stream, GLsizei instancecount) = nullptr;
	enum openGL4_2
	{
		gl_unpack_compressed_block_width =										0x9127,
		gl_unpack_compressed_block_height =										0x9128,
		gl_unpack_compressed_block_depth =										0x9129,
		gl_unpack_compressed_block_size =										0x912a,
		gl_pack_compressed_block_width =										0x912b,
		gl_pack_compressed_block_height =										0x912c,
		gl_pack_compressed_block_depth =										0x912d,
		gl_pack_compressed_block_size =											0x912e,
		gl_num_sample_counts =													0x9380,
		gl_min_map_buffer_alignment =											0x90bc,
		gl_atomic_counter_buffer =												0x92c0,
		gl_atomic_counter_buffer_binding =										0x92c1,
		gl_atomic_counter_buffer_start =										0x92c2,
		gl_atomic_counter_buffer_size =											0x92c3,
		gl_atomic_counter_buffer_data_size =									0x92c4,
		gl_atomic_counter_buffer_active_atomic_counters =						0x92c5,
		gl_atomic_counter_buffer_active_atomic_counter_indices =				0x92c6,
		gl_atomic_counter_buffer_referenced_by_vertex_shader =					0x92c7,
		gl_atomic_counter_buffer_referenced_by_tess_control_shader =			0x92c8,
		gl_atomic_counter_buffer_referenced_by_tess_evaluation_shader =			0x92c9,
		gl_atomic_counter_buffer_referenced_by_geometry_shader =				0x92ca,
		gl_atomic_counter_buffer_referenced_by_fragment_shader =				0x92cb,
		gl_max_vertex_atomic_counter_buffers =									0x92cc,
		gl_max_tess_control_atomic_counter_buffers =							0x92cd,
		gl_max_tess_evaluation_atomic_counter_buffers =							0x92ce,
		gl_max_geometry_atomic_counter_buffers =								0x92cf,
		gl_max_fragment_atomic_counter_buffers =								0x92d0,
		gl_max_combined_atomic_counter_buffers =								0x92d1,
		gl_max_vertex_atomic_counters =											0x92d2,
		gl_max_tess_control_atomic_counters =									0x92d3,
		gl_max_tess_evaluation_atomic_counters =								0x92d4,
		gl_max_geometry_atomic_counters =										0x92d5,
		gl_max_fragment_atomic_counters =										0x92d6,
		gl_max_combined_atomic_counters =										0x92d7,
		gl_max_atomic_counter_buffer_size =										0x92d8,
		gl_max_atomic_counter_buffer_bindings =									0x92dc,
		gl_active_atomic_counter_buffers =										0x92d9,
		gl_uniform_atomic_counter_buffer_index =								0x92da,
		gl_unsigned_int_atomic_counter =										0x92db,
		gl_vertex_attrib_array_barrier_bit =									0x00000001,
		gl_element_array_barrier_bit =											0x00000002,
		gl_uniform_barrier_bit =												0x00000004,
		gl_texture_fetch_barrier_bit =											0x00000008,
		gl_shader_image_access_barrier_bit =									0x00000020,
		gl_command_barrier_bit =												0x00000040,
		gl_pixel_buffer_barrier_bit =											0x00000080,
		gl_texture_update_barrier_bit =											0x00000100,
		gl_buffer_update_barrier_bit =											0x00000200,
		gl_framebuffer_barrier_bit =											0x00000400,
		gl_transform_feedback_barrier_bit =										0x00000800,
		gl_atomic_counter_barrier_bit =											0x00001000,
		gl_all_barrier_bits =													0xffffffff,
		gl_max_image_units =													0x8f38,
		gl_max_combined_image_units_and_fragment_outputs =						0x8f39,
		gl_image_binding_name =													0x8f3a,
		gl_image_binding_level =												0x8f3b,
		gl_image_binding_layered =												0x8f3c,
		gl_image_binding_layer =												0x8f3d,
		gl_image_binding_access =												0x8f3e,
		gl_image_1d =															0x904c,
		gl_image_2d =															0x904d,
		gl_image_3d =															0x904e,
		gl_image_2d_rect =														0x904f,
		gl_image_cube =															0x9050,
		gl_image_buffer =														0x9051,
		gl_image_1d_array =														0x9052,
		gl_image_2d_array =														0x9053,
		gl_image_cube_map_array =												0x9054,
		gl_image_2d_multisample =												0x9055,
		gl_image_2d_multisample_array =											0x9056,
		gl_int_image_1d =														0x9057,
		gl_int_image_2d =														0x9058,
		gl_int_image_3d =														0x9059,
		gl_int_image_2d_rect =													0x905a,
		gl_int_image_cube =														0x905b,
		gl_int_image_buffer =													0x905c,
		gl_int_image_1d_array =													0x905d,
		gl_int_image_2d_array =													0x905e,
		gl_int_image_cube_map_array =											0x905f,
		gl_int_image_2d_multisample =											0x9060,
		gl_int_image_2d_multisample_array =										0x9061,
		gl_unsigned_int_image_1d =												0x9062,
		gl_unsigned_int_image_2d =												0x9063,
		gl_unsigned_int_image_3d =												0x9064,
		gl_unsigned_int_image_2d_rect =											0x9065,
		gl_unsigned_int_image_cube =											0x9066,
		gl_unsigned_int_image_buffer =											0x9067,
		gl_unsigned_int_image_1d_array =										0x9068,
		gl_unsigned_int_image_2d_array =										0x9069,
		gl_unsigned_int_image_cube_map_array =									0x906a,
		gl_unsigned_int_image_2d_multisample =									0x906b,
		gl_unsigned_int_image_2d_multisample_array =							0x906c,
		gl_max_image_samples =													0x906d,
		gl_image_binding_format =												0x906e,
		gl_image_format_compatibility_type =									0x90c7,
		gl_image_format_compatibility_by_size =									0x90c8,
		gl_image_format_compatibility_by_class =								0x90c9,
		gl_max_vertex_image_uniforms =											0x90ca,
		gl_max_tess_control_image_uniforms =									0x90cb,
		gl_max_tess_evaluation_image_uniforms =									0x90cc,
		gl_max_geometry_image_uniforms =										0x90cd,
		gl_max_fragment_image_uniforms =										0x90ce,
		gl_max_combined_image_uniforms =										0x90cf,
		gl_texture_immutable_format =											0x912f,
	};

	//OpenGL 4.3 Extensions
	using glDebug = void (*)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
	void(*glClearBufferData) (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data) = nullptr;
	void(*glClearBufferSubData) (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data) = nullptr;
	void(*glDispatchCompute) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) = nullptr;
	void(*glDispatchComputeIndirect) (GLintptr indirect) = nullptr;
	void(*glCopyImageSubData) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) = nullptr;
	void(*glFramebufferParameteri) (GLenum target, GLenum pname, GLint param) = nullptr;
	void(*glGetFramebufferParameteriv) (GLenum target, GLenum pname, GLint *params) = nullptr;
	void(*glGetInternalformati64v) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params) = nullptr;
	void(*glInvalidateTexSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
	void(*glInvalidateTexImage) (GLuint texture, GLint level) = nullptr;
	void(*glInvalidateBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr length) = nullptr;
	void(*glInvalidateBufferData) (GLuint buffer) = nullptr;
	void(*glInvalidateFramebuffer) (GLenum target, GLsizei numAttachments, const GLenum *attachments) = nullptr;
	void(*glInvalidateSubFramebuffer) (GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	void(*glMultiDrawArraysIndirect) (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride) = nullptr;
	void(*glMultiDrawElementsIndirect) (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride) = nullptr;
	void(*glGetProgramInterfaceiv) (GLuint program, GLenum programInterface, GLenum pname, GLint *params) = nullptr;
	GLuint(*glGetProgramResourceIndex) (GLuint program, GLenum programInterface, const GLchar *name) = nullptr;
	void(*glGetProgramResourceName) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name) = nullptr;
	void(*glGetProgramResourceiv) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params) = nullptr;
	GLint(*glGetProgramResourceLocation) (GLuint program, GLenum programInterface, const GLchar *name) = nullptr;
	GLint(*glGetProgramResourceLocationIndex) (GLuint program, GLenum programInterface, const GLchar *name) = nullptr;
	void(*glShaderStorageBlockBinding) (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) = nullptr;
	void(*glTexBufferRange) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	void(*glTexStorage2DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	void(*glTexStorage3DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
	void(*glTextureView) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) = nullptr;
	void(*glBindVertexBuffer) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) = nullptr;
	void(*glVertexAttribFormat) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) = nullptr;
	void(*glVertexAttribIFormat) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	void(*glVertexAttribLFormat) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	void(*glVertexAttribBinding) (GLuint attribindex, GLuint bindingindex) = nullptr;
	void(*glVertexBindingDivisor) (GLuint bindingindex, GLuint divisor) = nullptr;
	void(*glDebugMessageControl) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled) = nullptr;
	void(*glDebugMessageInsert) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf) = nullptr;
	void(*glDebugMessageCallback) (glDebug callback, const void *userParam) = nullptr;
	GLuint(*glGetDebugMessageLog) (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog) = nullptr;
	void(*glPushDebugGroup) (GLenum source, GLuint id, GLsizei length, const GLchar *message) = nullptr;
	void(*glPopDebugGroup) (void) = nullptr;
	void(*glObjectLabel) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label) = nullptr;
	void(*glObjectPtrLabel) (const void *ptr, GLsizei length, const GLchar *label) = nullptr;
	void(*glGetObjectLabel) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label) = nullptr;
	void(*glGetObjectPtrLabel) (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label) = nullptr;
	enum openGL4_3
	{
		gl_num_shading_language_versions =								0x82e9,
		gl_vertex_attrib_array_long =									0x874e,
		gl_compressed_rgb8_etc2 =										0x9274,
		gl_compressed_srgb8_etc2 =										0x9275,
		gl_compressed_rgb8_punchthrough_alpha1_etc2 =					0x9276,
		gl_compressed_srgb8_punchthrough_alpha1_etc2 =					0x9277,
		gl_compressed_rgba8_etc2_eac =									0x9278,
		gl_compressed_srgb8_alpha8_etc2_eac =							0x9279,
		gl_compressed_r11_eac =											0x9270,
		gl_compressed_signed_r11_eac =									0x9271,
		gl_compressed_rg11_eac =										0x9272,
		gl_compressed_signed_rg11_eac =									0x9273,
		gl_primitive_restart_fixed_index =								0x8d69,
		gl_any_samples_passed_conservative =							0x8d6a,
		gl_max_element_index =											0x8d6b,
		gl_compute_shader =												0x91b9,
		gl_max_compute_uniform_blocks =									0x91bb,
		gl_max_compute_texture_image_units =							0x91bc,
		gl_max_compute_image_uniforms =									0x91bd,
		gl_max_compute_shared_memory_size =								0x8262,
		gl_max_compute_uniform_components =								0x8263,
		gl_max_compute_atomic_counter_buffers =							0x8264,
		gl_max_compute_atomic_counters =								0x8265,
		gl_max_combined_compute_uniform_components =					0x8266,
		gl_max_compute_work_group_invocations =							0x90eb,
		gl_max_compute_work_group_count =								0x91be,
		gl_max_compute_work_group_size =								0x91bf,
		gl_compute_work_group_size =									0x8267,
		gl_uniform_block_referenced_by_compute_shader =					0x90ec,
		gl_atomic_counter_buffer_referenced_by_compute_shader =			0x90ed,
		gl_dispatch_indirect_buffer =									0x90ee,
		gl_dispatch_indirect_buffer_binding =							0x90ef,
		gl_debug_output_synchronous =									0x8242,
		gl_debug_next_logged_message_length =							0x8243,
		gl_debug_callback_function =									0x8244,
		gl_debug_callback_user_param =									0x8245,
		gl_debug_source_api =											0x8246,
		gl_debug_source_window_system =									0x8247,
		gl_debug_source_shader_compiler =								0x8248,
		gl_debug_source_third_party =									0x8249,
		gl_debug_source_application =									0x824a,
		gl_debug_source_other =											0x824b,
		gl_debug_type_error =											0x824c,
		gl_debug_type_deprecated_behavior =								0x824d,
		gl_debug_type_undefined_behavior =								0x824e,
		gl_debug_type_portability =										0x824f,
		gl_debug_type_performance =										0x8250,
		gl_debug_type_other =											0x8251,
		gl_max_debug_message_length =									0x9143,
		gl_max_debug_logged_messages =									0x9144,
		gl_debug_logged_messages =										0x9145,
		gl_debug_severity_high =										0x9146,
		gl_debug_severity_medium =										0x9147,
		gl_debug_severity_low =											0x9148,
		gl_debug_type_marker =											0x8268,
		gl_debug_type_push_group =										0x8269,
		gl_debug_type_pop_group =										0x826a,
		gl_debug_severity_notification =								0x826b,
		gl_max_debug_group_stack_depth =								0x826c,
		gl_debug_group_stack_depth =									0x826d,
		gl_buffer =														0x82e0,
		gl_shader =														0x82e1,
		gl_program =													0x82e2,
		gl_query =														0x82e3,
		gl_program_pipeline =											0x82e4,
		gl_sampler =													0x82e6,
		gl_max_label_length =											0x82e8,
		gl_debug_output =												0x92e0,
		gl_context_flag_debug_bit =										0x00000002,
		gl_max_uniform_locations =										0x826e,
		gl_framebuffer_default_width =									0x9310,
		gl_framebuffer_default_height =									0x9311,
		gl_framebuffer_default_layers =									0x9312,
		gl_framebuffer_default_samples =								0x9313,
		gl_framebuffer_default_fixed_sample_locations =					0x9314,
		gl_max_framebuffer_width =										0x9315,
		gl_max_framebuffer_height =										0x9316,
		gl_max_framebuffer_layers =										0x9317,
		gl_max_framebuffer_samples =									0x9318,
		gl_internalformat_supported =									0x826f,
		gl_internalformat_preferred =									0x8270,
		gl_internalformat_red_size =									0x8271,
		gl_internalformat_green_size =									0x8272,
		gl_internalformat_blue_size =									0x8273,
		gl_internalformat_alpha_size =									0x8274,
		gl_internalformat_depth_size =									0x8275,
		gl_internalformat_stencil_size =								0x8276,
		gl_internalformat_shared_size =									0x8277,
		gl_internalformat_red_type =									0x8278,
		gl_internalformat_green_type =									0x8279,
		gl_internalformat_blue_type =									0x827a,
		gl_internalformat_alpha_type =									0x827b,
		gl_internalformat_depth_type =									0x827c,
		gl_internalformat_stencil_type =								0x827d,
		gl_max_width =													0x827e,
		gl_max_height =													0x827f,
		gl_max_depth =													0x8280,
		gl_max_layers =													0x8281,
		gl_max_combined_dimensions =									0x8282,
		gl_color_components =											0x8283,
		gl_depth_components =											0x8284,
		gl_stencil_components =											0x8285,
		gl_color_renderable =											0x8286,
		gl_depth_renderable =											0x8287,
		gl_stencil_renderable =											0x8288,
		gl_framebuffer_renderable =										0x8289,
		gl_framebuffer_renderable_layered =								0x828a,
		gl_framebuffer_blend =											0x828b,
		gl_read_pixels =												0x828c,
		gl_read_pixels_format =											0x828d,
		gl_read_pixels_type =											0x828e,
		gl_texture_image_format =										0x828f,
		gl_texture_image_type =											0x8290,
		gl_get_texture_image_format =									0x8291,
		gl_get_texture_image_type =										0x8292,
		gl_mipmap =														0x8293,
		gl_manual_generate_mipmap =										0x8294,
		gl_auto_generate_mipmap =										0x8295,
		gl_color_encoding =												0x8296,
		gl_srgb_read =													0x8297,
		gl_srgb_write =													0x8298,
		gl_filter =														0x829a,
		gl_vertex_texture =												0x829b,
		gl_tess_control_texture =										0x829c,
		gl_tess_evaluation_texture =									0x829d,
		gl_geometry_texture =											0x829e,
		gl_fragment_texture =											0x829f,
		gl_compute_texture =											0x82a0,
		gl_texture_shadow =												0x82a1,
		gl_texture_gather =												0x82a2,
		gl_texture_gather_shadow =										0x82a3,
		gl_shader_image_load =											0x82a4,
		gl_shader_image_store =											0x82a5,
		gl_shader_image_atomic =										0x82a6,
		gl_image_texel_size =											0x82a7,
		gl_image_compatibility_class =									0x82a8,
		gl_image_pixel_format =											0x82a9,
		gl_image_pixel_type =											0x82aa,
		gl_simultaneous_texture_and_depth_test =						0x82ac,
		gl_simultaneous_texture_and_stencil_test =						0x82ad,
		gl_simultaneous_texture_and_depth_write =						0x82ae,
		gl_simultaneous_texture_and_stencil_write =						0x82af,
		gl_texture_compressed_block_width =								0x82b1,
		gl_texture_compressed_block_height =							0x82b2,
		gl_texture_compressed_block_size =								0x82b3,
		gl_clear_buffer =												0x82b4,
		gl_texture_view =												0x82b5,
		gl_view_compatibility_class =									0x82b6,
		gl_full_support =												0x82b7,
		gl_caveat_support =												0x82b8,
		gl_image_class_4_x_32 =											0x82b9,
		gl_image_class_2_x_32 =											0x82ba,
		gl_image_class_1_x_32 =											0x82bb,
		gl_image_class_4_x_16 =											0x82bc,
		gl_image_class_2_x_16 =											0x82bd,
		gl_image_class_1_x_16 =											0x82be,
		gl_image_class_4_x_8 =											0x82bf,
		gl_image_class_2_x_8 =											0x82c0,
		gl_image_class_1_x_8 =											0x82c1,
		gl_image_class_11_11_10 =										0x82c2,
		gl_image_class_10_10_10_2 =										0x82c3,
		gl_view_class_128_bits =										0x82c4,
		gl_view_class_96_bits =											0x82c5,
		gl_view_class_64_bits =											0x82c6,
		gl_view_class_48_bits =											0x82c7,
		gl_view_class_32_bits =											0x82c8,
		gl_view_class_24_bits =											0x82c9,
		gl_view_class_16_bits =											0x82ca,
		gl_view_class_8_bits =											0x82cb,
		gl_view_class_s3tc_dxt1_rgb =									0x82cc,
		gl_view_class_s3tc_dxt1_rgba =									0x82cd,
		gl_view_class_s3tc_dxt3_rgba =									0x82ce,
		gl_view_class_s3tc_dxt5_rgba =									0x82cf,
		gl_view_class_rgtc1_red =										0x82d0,
		gl_view_class_rgtc2_rg =										0x82d1,
		gl_view_class_bptc_unorm =										0x82d2,
		gl_view_class_bptc_float =										0x82d3,
		gl_uniform =													0x92e1,
		gl_uniform_block =												0x92e2,
		gl_program_input =												0x92e3,
		gl_program_output =												0x92e4,
		gl_buffer_variable =											0x92e5,
		gl_shader_storage_block =										0x92e6,
		gl_vertex_subroutine =											0x92e8,
		gl_tess_control_subroutine =									0x92e9,
		gl_tess_evaluation_subroutine =									0x92ea,
		gl_geometry_subroutine =										0x92eb,
		gl_fragment_subroutine =										0x92ec,
		gl_compute_subroutine =											0x92ed,
		gl_vertex_subroutine_uniform =									0x92ee,
		gl_tess_control_subroutine_uniform =							0x92ef,
		gl_tess_evaluation_subroutine_uniform =							0x92f0,
		gl_geometry_subroutine_uniform =								0x92f1,
		gl_fragment_subroutine_uniform =								0x92f2,
		gl_compute_subroutine_uniform =									0x92f3,
		gl_transform_feedback_varying =									0x92f4,
		gl_active_resources =											0x92f5,
		gl_max_name_length =											0x92f6,
		gl_max_num_active_variables =									0x92f7,
		gl_max_num_compatible_subroutines =								0x92f8,
		gl_name_length =												0x92f9,
		gl_type =														0x92fa,
		gl_array_size =													0x92fb,
		gl_offset =														0x92fc,
		gl_block_index =												0x92fd,
		gl_array_stride =												0x92fe,
		gl_matrix_stride =												0x92ff,
		gl_is_row_major =												0x9300,
		gl_atomic_counter_buffer_index =								0x9301,
		gl_buffer_binding =												0x9302,
		gl_buffer_data_size =											0x9303,
		gl_num_active_variables =										0x9304,
		gl_active_variables =											0x9305,
		gl_referenced_by_vertex_shader =								0x9306,
		gl_referenced_by_tess_control_shader =							0x9307,
		gl_referenced_by_tess_evaluation_shader =						0x9308,
		gl_referenced_by_geometry_shader =								0x9309,
		gl_referenced_by_fragment_shader =								0x930a,
		gl_referenced_by_compute_shader =								0x930b,
		gl_top_level_array_size =										0x930c,
		gl_top_level_array_stride =										0x930d,
		gl_location =													0x930e,
		gl_location_index =												0x930f,
		gl_is_per_patch =												0x92e7,
		gl_shader_storage_buffer =										0x90d2,
		gl_shader_storage_buffer_binding =								0x90d3,
		gl_shader_storage_buffer_start =								0x90d4,
		gl_shader_storage_buffer_size =									0x90d5,
		gl_max_vertex_shader_storage_blocks =							0x90d6,
		gl_max_geometry_shader_storage_blocks =							0x90d7,
		gl_max_tess_control_shader_storage_blocks =						0x90d8,
		gl_max_tess_evaluation_shader_storage_blocks =					0x90d9,
		gl_max_fragment_shader_storage_blocks =							0x90da,
		gl_max_compute_shader_storage_blocks =							0x90db,
		gl_max_combined_shader_storage_blocks =							0x90dc,
		gl_max_shader_storage_buffer_bindings =							0x90dd,
		gl_max_shader_storage_block_size =								0x90de,
		gl_shader_storage_buffer_offset_alignment =						0x90df,
		gl_shader_storage_barrier_bit =									0x00002000,
		gl_max_combined_shader_output_resources =						0x8f39,
		gl_depth_stencil_texture_mode =									0x90ea,
		gl_texture_buffer_offset =										0x919d,
		gl_texture_buffer_size =										0x919e,
		gl_texture_buffer_offset_alignment =							0x919f,
		gl_texture_view_min_level =										0x82db,
		gl_texture_view_num_levels =									0x82dc,
		gl_texture_view_min_layer =										0x82dd,
		gl_texture_view_num_layers =									0x82de,
		gl_texture_immutable_levels =									0x82df,
		gl_vertex_attrib_binding =										0x82d4,
		gl_vertex_attrib_relative_offset =								0x82d5,
		gl_vertex_binding_divisor =										0x82d6,
		gl_vertex_binding_offset =										0x82d7,
		gl_vertex_binding_stride =										0x82d8,
		gl_max_vertex_attrib_relative_offset =							0x82d9,
		gl_max_vertex_attrib_bindings =									0x82da,
		gl_display_list =												0x82e7,
	};

	//OpenGL 4.4 Extensions
	void(*glBufferStorage) (GLenum target, GLsizeiptr size, const void *data, GLbitfield flags) = nullptr;
	void(*glClearTexImage) (GLuint texture, GLint level, GLenum format, GLenum type, const void *data) = nullptr;
	void(*glClearTexSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data) = nullptr;
	void(*glBindBuffersBase) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers) = nullptr;
	void(*glBindBuffersRange) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes) = nullptr;
	void(*glBindTextures) (GLuint first, GLsizei count, const GLuint *textures) = nullptr;
	void(*glBindSamplers) (GLuint first, GLsizei count, const GLuint *samplers) = nullptr;
	void(*glBindImageTextures) (GLuint first, GLsizei count, const GLuint *textures) = nullptr;
	void(*glBindVertexBuffers) (GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides) = nullptr;
	enum openGL4_4
	{
		gl_max_vertex_attrib_stride =						0x82e5,
		gl_primitive_restart_for_patches_supported =		0x8221,
		gl_texture_buffer_binding =							0x8c2a,
		gl_map_persistent_bit =								0x0040,
		gl_map_coherent_bit =								0x0080,
		gl_dynamic_storage_bit =							0x0100,
		gl_client_storage_bit =								0x0200,
		gl_client_mapped_buffer_barrier_bit = 				0x00004000,
		gl_buffer_immutable_storage =						0x821f,
		gl_buffer_storage_flags =							0x8220,
		gl_clear_texture =									0x9365,
		gl_location_component =								0x934a,
		gl_transform_feedback_buffer_index =				0x934b,
		gl_transform_feedback_buffer_stride =				0x934c,
		gl_query_buffer =									0x9192,
		gl_query_buffer_barrier_bit =						0x00008000,
		gl_query_buffer_binding =							0x9193,
		gl_query_result_no_wait =							0x9194,
		gl_mirror_clamp_to_edge =							0x8743
	};
	
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

	/**< returns a proc address to an OpenGL extension */
	template<typename T> void FetchProcAddress(T& funcPointer, const char* procName)
	{
#if defined(TE_WINDOWS)
		funcPointer = (T)wglGetProcAddress(procName);
#elif defined(TE_LINUX)
		funcPointer = (T)glXGetProcAddress(procName);
#endif
	}

	/**< get OpenGL version */
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

	/**< load OpenGL 1.2 extensions */
	void Load1_2Extensions()
	{
		FetchProcAddress(glDrawRangeElements, "glDrawRangeElements");
		FetchProcAddress(glTexImage3D, "glTexImage3D");
		FetchProcAddress(glTexSubImage3D, "glTexSubImage3D");
		FetchProcAddress(glCopyTexSubImage3D, "glCopyTexSubImage3D");
	}
	
	/**< load OpenGL 1.3 extensions */
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

	/**< load OpenGL 1.4 extensions */
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

	/**< load OpenGL 1.5 extensions */
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

	/**< load OpenGL 2.0 extensions */
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

	/**< load OpenGL 2.1 extensions */
	void Load2_1Extensions()
	{
		FetchProcAddress(glUniformMatrix2x3fv, "glUniformMatrix2x3fv");
		FetchProcAddress(glUniformMatrix3x2fv, "glUniformMatrix3x2fv");
		FetchProcAddress(glUniformMatrix2x4fv, "glUniformMatrix2x4fv");
		FetchProcAddress(glUniformMatrix4x2fv, "glUniformMatrix4x2fv");
		FetchProcAddress(glUniformMatrix3x4fv, "glUniformMatrix3x4fv");
		FetchProcAddress(glUniformMatrix4x3fv, "glUniformMatrix4x3fv");
	}

	/**< load OpenGL 3.0 extensions */
	void Load3_0Extensions()
	{
		FetchProcAddress(glColorMaski, "glColorMaski");
		FetchProcAddress(glGetBooleani_v, "glGetBooleani_v");
		FetchProcAddress(glGetIntegeri_v, "glGetIntegeri_v");
		FetchProcAddress(glEnablei, "glEnablei");
		FetchProcAddress(glDisablei, "glDisablei");
		FetchProcAddress(glIsEnabledi, "glIsEnabledi");
		FetchProcAddress(glBeginTransformFeedback, "glBeginTransformFeedback");
		FetchProcAddress(glEndTransformFeedback, "glEndTransformFeedback");
		FetchProcAddress(glBindBufferRange, "glBindBufferRange");
		FetchProcAddress(glBindBufferBase, "glBindBufferBase");
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
		FetchProcAddress(glIsRenderbuffer, "glIsRenderbuffer");
		FetchProcAddress(glBindRenderbuffer, "glBindRenderbuffer");
		FetchProcAddress(glDeleteRenderbuffers, "glDeleteRenderbuffers");
		FetchProcAddress(glGenRenderbuffers, "glGenRenderbuffers");
		FetchProcAddress(glRenderbufferStorage, "glRenderbufferStorage");
		FetchProcAddress(glGetRenderbufferParameteriv, "glGetRenderbufferParameteriv");
		FetchProcAddress(glIsFramebuffer, "glIsFramebuffer");
		FetchProcAddress(glBindFramebuffer, "glBindFramebuffer");
		FetchProcAddress(glDeleteFramebuffers, "glDeleteFramebuffers");
		FetchProcAddress(glGenFramebuffers, "glGenFramebuffers");
		FetchProcAddress(glCheckFramebufferStatus, "glCheckFramebufferStatus");
		FetchProcAddress(glFramebufferTexture1D, "glFramebufferTexture1D");
		FetchProcAddress(glFramebufferTexture2D, "glFramebufferTexture2D");
		FetchProcAddress(glFramebufferTexture3D, "glFramebufferTexture3D");
		FetchProcAddress(glFramebufferRenderbuffer, "glFramebufferRenderbuffer");
		FetchProcAddress(glGetFramebufferAttachmentParameteriv, "glGetFramebufferAttachmentParameteriv");
		FetchProcAddress(glGenerateMipmap, "glGenerateMipmap");
		FetchProcAddress(glBlitFramebuffer, "glBlitFramebuffer");
		FetchProcAddress(glRenderbufferStorageMultisample, "glRenderbufferStorageMultisample");
		FetchProcAddress(glFramebufferTextureLayer, "glFramebufferTextureLayer");
		FetchProcAddress(glMapBufferRange, "glMapBufferRange");
		FetchProcAddress(glFlushMappedBufferRange, "glFlushMappedBufferRange");
		FetchProcAddress(glBindVertexArray, "glBindVertexArray");
		FetchProcAddress(glDeleteVertexArrays, "glDeleteVertexArrays");
		FetchProcAddress(glGenVertexArrays, "glGenVertexArrays");
		FetchProcAddress(glIsVertexArray, "glIsVertexArray");
	}

	/**< load OpenGL 3.1 extensions */
	void Load3_1Extensions()
	{
		FetchProcAddress(glDrawArraysInstanced, "glDrawArraysInstanced");
		FetchProcAddress(glDrawElementsInstanced, "glDrawElementsInstanced");
		FetchProcAddress(glTexBuffer, "glTexBuffer");
		FetchProcAddress(glPrimitiveRestartIndex, "glPrimitiveRestartIndex");
		FetchProcAddress(glCopyBufferSubData, "glCopyBufferSubData");
		FetchProcAddress(glGetUniformIndices, "glGetUniformIndices");
		FetchProcAddress(glGetActiveUniformsiv, "glGetActiveUniformsiv");
		FetchProcAddress(glGetActiveUniformName, "glGetActiveUniformName");
		FetchProcAddress(glGetUniformBlockIndex, "glGetUniformBlockIndex");
		FetchProcAddress(glGetActiveUniformBlockiv, "glGetActiveUniformBlockiv");
		FetchProcAddress(glGetActiveUniformBlockName, "glGetActiveUniformBlockName");
		FetchProcAddress(glUniformBlockBinding, "glUniformBlockBinding");
	}

	/**< load OpenGL 3.2 extensions */
	void Load3_2Extensions()
	{
		FetchProcAddress(glDrawElementsBaseVertex, "glDrawElementsBaseVertex");
		FetchProcAddress(glDrawRangeElementsBaseVertex, "glDrawRangeElementsBaseVertex");
		FetchProcAddress(glDrawElementsInstancedBaseVertex, "glDrawElementsInstancedBaseVertex");
		FetchProcAddress(glMultiDrawElementsBaseVertex, "glMultiDrawElementsBaseVertex");
		FetchProcAddress(glProvokingVertex, "glProvokingVertex");
		FetchProcAddress(glFenceSync, "glFenceSync");
		FetchProcAddress(glIsSync, "glIsSync");
		FetchProcAddress(glDeleteSync, "glDeleteSync");
		FetchProcAddress(glClientWaitSync, "glClientWaitSync");
		FetchProcAddress(glWaitSync, "glWaitSync");
		FetchProcAddress(glGetInteger64v, "glGetInteger64v");
		FetchProcAddress(glGetSynciv, "glGetSynciv");
		FetchProcAddress(glGetInteger64i_v, "glGetInteger64i_v");
		FetchProcAddress(glGetBufferParameteri64v, "glGetBufferParameteri64v");
		FetchProcAddress(glFramebufferTexture, "glFramebufferTexture");
		FetchProcAddress(glTexImage2DMultisample, "glTexImage2DMultisample");
		FetchProcAddress(glTexImage3DMultisample, "glTexImage3DMultisample");
		FetchProcAddress(glGetMultisamplefv, "glGetMultisamplefv");
		FetchProcAddress(glSampleMaski, "glSampleMaski");
	}
	
	/**< load OpenGL 3.3 extensions */
	void Load3_3Extensions()
	{
		FetchProcAddress(glBindFragDataLocationIndexed, "glBindFragDataLocationIndexed");
		FetchProcAddress(glGetFragDataIndex, "glGetFragDataIndex");
		FetchProcAddress(glGenSamplers, "glGenSamplers");
		FetchProcAddress(glDeleteSamplers, "glDeleteSamplers");
		FetchProcAddress(glIsSampler, "glIsSampler");
		FetchProcAddress(glBindSampler, "glBindSampler");
		FetchProcAddress(glSamplerParameteri, "glSamplerParameteri");
		FetchProcAddress(glSamplerParameteriv, "glSamplerParameteriv");
		FetchProcAddress(glSamplerParameterf, "glSamplerParameterf");
		FetchProcAddress(glSamplerParameterfv, "glSamplerParameterfv");
		FetchProcAddress(glSamplerParameterIiv, "glSamplerParameterIiv");
		FetchProcAddress(glSamplerParameterIuiv, "glSamplerParameterIuiv");
		FetchProcAddress(glGetSamplerParameteriv, "glGetSamplerParameteriv");
		FetchProcAddress(glGetSamplerParameterIiv, "glGetSamplerParameterIiv");
		FetchProcAddress(glGetSamplerParameterfv, "glGetSamplerParameterfv");
		FetchProcAddress(glGetSamplerParameterIuiv, "glGetSamplerParameterIuiv");
		FetchProcAddress(glQueryCounter, "glQueryCounter");
		FetchProcAddress(glGetQueryObjecti64v, "glGetQueryObjecti64v");
		FetchProcAddress(glGetQueryObjectui64v, "glGetQueryObjectui64v");
		FetchProcAddress(glVertexAttribDivisor, "glVertexAttribDivisor");
		FetchProcAddress(glVertexAttribP1ui, "glVertexAttribP1ui");
		FetchProcAddress(glVertexAttribP1uiv, "glVertexAttribP1uiv");
		FetchProcAddress(glVertexAttribP2ui, "glVertexAttribP2ui");
		FetchProcAddress(glVertexAttribP2uiv, "glVertexAttribP2uiv");
		FetchProcAddress(glVertexAttribP3ui, "glVertexAttribP3ui");
		FetchProcAddress(glVertexAttribP3uiv, "glVertexAttribP3uiv");
		FetchProcAddress(glVertexAttribP4ui, "glVertexAttribP4ui");
		FetchProcAddress(glVertexAttribP4uiv, "glVertexAttribP4uiv");
		FetchProcAddress(glVertexAttrib4uiv, "glVertexAttrib4uiv");
		FetchProcAddress(glVertexP2ui, "glVertexP2ui");
		FetchProcAddress(glVertexP2uiv, "glVertexP2uiv");
		FetchProcAddress(glVertexP3ui, "glVertexP3ui");
		FetchProcAddress(glVertexP3uiv, "glVertexP3uiv");
		FetchProcAddress(glVertexP4ui, "glVertexP4ui");
		FetchProcAddress(glVertexP4uiv, "glVertexP4uiv");
		FetchProcAddress(glTexCoordP1ui, "glTexCoordP1ui");
		FetchProcAddress(glTexCoordP1uiv, "glTexCoordP1uiv");
		FetchProcAddress(glTexCoordP2ui, "glTexCoordP2ui");
		FetchProcAddress(glTexCoordP2uiv, "glTexCoordP2uiv");
		FetchProcAddress(glTexCoordP3ui, "glTexCoordP3ui");
		FetchProcAddress(glTexCoordP3uiv, "glTexCoordP3uiv");
		FetchProcAddress(glTexCoordP4ui, "glTexCoordP4ui");
		FetchProcAddress(glTexCoordP4uiv, "glTexCoordP4uiv");
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
		FetchProcAddress(glColorP3ui, "glColorP3ui");
		FetchProcAddress(glColorP3uiv, "glColorP3uiv");
		FetchProcAddress(glColorP4ui, "glColorP4ui");
		FetchProcAddress(glColorP4uiv, "glColorP4uiv");
		FetchProcAddress(glSecondaryColorP3ui, "glSecondaryColorP3ui");
		FetchProcAddress(glSecondaryColorP3uiv, "glSecondaryColorP3uiv");
	}

	/**< load OpenGL 4.0 extensions */
	void Load4_0Extensions()
	{
		FetchProcAddress(glMinSampleShading, "glMinSampleShading");
		FetchProcAddress(glBlendEquationi, "glBlendEquationi");
		FetchProcAddress(glBlendEquationSeparatei, "glBlendEquationSeparatei");
		FetchProcAddress(glBlendFunci, "glBlendFunci");
		FetchProcAddress(glBlendFuncSeparatei, "glBlendFuncSeparatei");
		FetchProcAddress(glDrawArraysIndirect, "glDrawArraysIndirect");
		FetchProcAddress(glDrawElementsIndirect, "glDrawElementsIndirect");
		FetchProcAddress(glUniform1d, "glUniform1d");
		FetchProcAddress(glUniform2d, "glUniform2d");
		FetchProcAddress(glUniform3d, "glUniform3d");
		FetchProcAddress(glUniform4d, "glUniform4d");
		FetchProcAddress(glUniform1dv, "glUniform1dv");
		FetchProcAddress(glUniform2dv, "glUniform2dv");
		FetchProcAddress(glUniform3dv, "glUniform3dv");
		FetchProcAddress(glUniform4dv, "glUniform4dv");
		FetchProcAddress(glUniformMatrix2dv, "glUniformMatrix2dv");
		FetchProcAddress(glUniformMatrix3dv, "glUniformMatrix3dv");
		FetchProcAddress(glUniformMatrix4dv, "glUniformMatrix4dv");
		FetchProcAddress(glUniformMatrix2x3dv, "glUniformMatrix2x3dv");
		FetchProcAddress(glUniformMatrix2x4dv, "glUniformMatrix2x4dv");
		FetchProcAddress(glUniformMatrix3x2dv, "glUniformMatrix3x2dv");
		FetchProcAddress(glUniformMatrix3x4dv, "glUniformMatrix3x4dv");
		FetchProcAddress(glUniformMatrix4x2dv, "glUniformMatrix4x2dv");
		FetchProcAddress(glUniformMatrix4x3dv, "glUniformMatrix4x3dv");
		FetchProcAddress(glGetUniformdv, "glGetUniformdv");
		FetchProcAddress(glGetSubroutineUniformLocation, "glGetSubroutineUniformLocation");
		FetchProcAddress(glGetSubroutineIndex, "glGetSubroutineIndex");
		FetchProcAddress(glGetActiveSubroutineUniformiv, "glGetActiveSubroutineUniformiv");
		FetchProcAddress(glGetActiveSubroutineUniformName, "glGetActiveSubroutineUniformName");
		FetchProcAddress(glGetActiveSubroutineName, "glGetActiveSubroutineName");
		FetchProcAddress(glUniformSubroutinesuiv, "glUniformSubroutinesuiv");
		FetchProcAddress(glGetUniformSubroutineuiv, "glGetUniformSubroutineuiv");
		FetchProcAddress(glGetProgramStageiv, "glGetProgramStageiv");
		FetchProcAddress(glPatchParameteri, "glPatchParameteri");
		FetchProcAddress(glPatchParameterfv, "glPatchParameterfv");
		FetchProcAddress(glBindTransformFeedback, "glBindTransformFeedback");
		FetchProcAddress(glDeleteTransformFeedbacks, "glDeleteTransformFeedbacks");
		FetchProcAddress(glGenTransformFeedbacks, "glGenTransformFeedbacks");
		FetchProcAddress(glIsTransformFeedback, "glIsTransformFeedback");
		FetchProcAddress(glPauseTransformFeedback, "glPauseTransformFeedback");
		FetchProcAddress(glResumeTransformFeedback, "glResumeTransformFeedback");
		FetchProcAddress(glDrawTransformFeedback, "glDrawTransformFeedback");
		FetchProcAddress(glDrawTransformFeedbackStream, "glDrawTransformFeedbackStream");
		FetchProcAddress(glBeginQueryIndexed, "glBeginQueryIndexed");
		FetchProcAddress(glEndQueryIndexed, "glEndQueryIndexed");
		FetchProcAddress(glGetQueryIndexediv, "glGetQueryIndexediv");
	}

	/**< load OpenGL 4.1 extensions */
	void Load4_1Extensions()
	{
		FetchProcAddress(glReleaseShaderCompiler, "glReleaseShaderCompiler");
		FetchProcAddress(glShaderBinary, "glShaderBinary");
		FetchProcAddress(glGetShaderPrecisionFormat, "glGetShaderPrecisionFormat");
		FetchProcAddress(glDepthRangef, "glDepthRangef");
		FetchProcAddress(glClearDepthf, "glClearDepthf");
		FetchProcAddress(glGetProgramBinary, "glGetProgramBinary");
		FetchProcAddress(glProgramBinary, "glProgramBinary");
		FetchProcAddress(glProgramParameteri, "glProgramParameteri");
		FetchProcAddress(glUseProgramStages, "glUseProgramStages");
		FetchProcAddress(glActiveShaderProgram, "glActiveShaderProgram");
		FetchProcAddress(glCreateShaderProgramv, "glCreateShaderProgramv");
		FetchProcAddress(glBindProgramPipeline, "glBindProgramPipeline");
		FetchProcAddress(glDeleteProgramPipelines, "glDeleteProgramPipelines");
		FetchProcAddress(glGenProgramPipelines, "glGenProgramPipelines");
		FetchProcAddress(glIsProgramPipeline, "glIsProgramPipeline");
		FetchProcAddress(glGetProgramPipelineiv, "glGetProgramPipelineiv");
		FetchProcAddress(glProgramUniform1i, "glProgramUniform1i");
		FetchProcAddress(glProgramUniform1iv, "glProgramUniform1iv");
		FetchProcAddress(glProgramUniform1f, "glProgramUniform1f");
		FetchProcAddress(glProgramUniform1fv, "glProgramUniform1fv");
		FetchProcAddress(glProgramUniform1d, "glProgramUniform1d");
		FetchProcAddress(glProgramUniform1dv, "glProgramUniform1dv");
		FetchProcAddress(glProgramUniform1ui, "glProgramUniform1ui");
		FetchProcAddress(glProgramUniform1uiv, "glProgramUniform1uiv");
		FetchProcAddress(glProgramUniform2i, "glProgramUniform2i");
		FetchProcAddress(glProgramUniform2iv, "glProgramUniform2iv");
		FetchProcAddress(glProgramUniform2f, "glProgramUniform2f");
		FetchProcAddress(glProgramUniform2fv, "glProgramUniform2fv");
		FetchProcAddress(glProgramUniform2d, "glProgramUniform2d");
		FetchProcAddress(glProgramUniform2dv, "glProgramUniform2dv");
		FetchProcAddress(glProgramUniform2ui, "glProgramUniform2ui");
		FetchProcAddress(glProgramUniform2uiv, "glProgramUniform2uiv");
		FetchProcAddress(glProgramUniform3i, "glProgramUniform3i");
		FetchProcAddress(glProgramUniform3iv, "glProgramUniform3iv");
		FetchProcAddress(glProgramUniform3f, "glProgramUniform3f");
		FetchProcAddress(glProgramUniform3fv, "glProgramUniform3fv");
		FetchProcAddress(glProgramUniform3d, "glProgramUniform3d");
		FetchProcAddress(glProgramUniform3dv, "glProgramUniform3dv");
		FetchProcAddress(glProgramUniform3ui, "glProgramUniform3ui");
		FetchProcAddress(glProgramUniform3uiv, "glProgramUniform3uiv");
		FetchProcAddress(glProgramUniform4i, "glProgramUniform4i");
		FetchProcAddress(glProgramUniform4iv, "glProgramUniform4iv");
		FetchProcAddress(glProgramUniform4f, "glProgramUniform4f");
		FetchProcAddress(glProgramUniform4fv, "glProgramUniform4fv");
		FetchProcAddress(glProgramUniform4d, "glProgramUniform4d");
		FetchProcAddress(glProgramUniform4dv, "glProgramUniform4dv");
		FetchProcAddress(glProgramUniform4ui, "glProgramUniform4ui");
		FetchProcAddress(glProgramUniform4uiv, "glProgramUniform4uiv");
		FetchProcAddress(glProgramUniformMatrix2fv, "glProgramUniformMatrix2fv");
		FetchProcAddress(glProgramUniformMatrix3fv, "glProgramUniformMatrix3fv");
		FetchProcAddress(glProgramUniformMatrix4fv, "glProgramUniformMatrix4fv");
		FetchProcAddress(glProgramUniformMatrix2dv, "glProgramUniformMatrix2dv");
		FetchProcAddress(glProgramUniformMatrix3dv, "glProgramUniformMatrix3dv");
		FetchProcAddress(glProgramUniformMatrix4dv, "glProgramUniformMatrix4dv");
		FetchProcAddress(glProgramUniformMatrix2x3fv, "glProgramUniformMatrix2x3fv");
		FetchProcAddress(glProgramUniformMatrix3x2fv, "glProgramUniformMatrix3x2fv");
		FetchProcAddress(glProgramUniformMatrix2x4fv, "glProgramUniformMatrix2x4fv");
		FetchProcAddress(glProgramUniformMatrix4x2fv, "glProgramUniformMatrix4x2fv");
		FetchProcAddress(glProgramUniformMatrix3x4fv, "glProgramUniformMatrix3x4fv");
		FetchProcAddress(glProgramUniformMatrix4x3fv, "glProgramUniformMatrix4x3fv");
		FetchProcAddress(glProgramUniformMatrix2x3dv, "glProgramUniformMatrix2x3dv");
		FetchProcAddress(glProgramUniformMatrix3x2dv, "glProgramUniformMatrix3x2dv");
		FetchProcAddress(glProgramUniformMatrix2x4dv, "glProgramUniformMatrix2x4dv");
		FetchProcAddress(glProgramUniformMatrix4x2dv, "glProgramUniformMatrix4x2dv");
		FetchProcAddress(glProgramUniformMatrix3x4dv, "glProgramUniformMatrix3x4dv");
		FetchProcAddress(glProgramUniformMatrix4x3dv, "glProgramUniformMatrix4x3dv");
		FetchProcAddress(glValidateProgramPipeline, "glValidateProgramPipeline");
		FetchProcAddress(glGetProgramPipelineInfoLog, "glGetProgramPipelineInfoLog");
		FetchProcAddress(glVertexAttribL1d, "glVertexAttribL1d");
		FetchProcAddress(glVertexAttribL2d, "glVertexAttribL2d");
		FetchProcAddress(glVertexAttribL3d, "glVertexAttribL3d");
		FetchProcAddress(glVertexAttribL4d, "glVertexAttribL4d");
		FetchProcAddress(glVertexAttribL1dv, "glVertexAttribL1dv");
		FetchProcAddress(glVertexAttribL2dv, "glVertexAttribL2dv");
		FetchProcAddress(glVertexAttribL3dv, "glVertexAttribL3dv");
		FetchProcAddress(glVertexAttribL4dv, "glVertexAttribL4dv");
		FetchProcAddress(glVertexAttribLPointer, "glVertexAttribLPointer");
		FetchProcAddress(glGetVertexAttribLdv, "glGetVertexAttribLdv");
		FetchProcAddress(glViewportArrayv, "glViewportArrayv");
		FetchProcAddress(glViewportIndexedf, "glViewportIndexedf");
		FetchProcAddress(glViewportIndexedfv, "glViewportIndexedfv");
		FetchProcAddress(glScissorArrayv, "glScissorArrayv");
		FetchProcAddress(glScissorIndexed, "glScissorIndexed");
		FetchProcAddress(glScissorIndexedv, "glScissorIndexedv");
		FetchProcAddress(glDepthRangeIndexed, "glDepthRangeIndexed");
		FetchProcAddress(glDepthRangeArrayv, "glDepthRangeArrayv");
		FetchProcAddress(glGetFloati_v, "glGetFloati_v");
		FetchProcAddress(glGetDoublei_v, "glGetDoublei_v");
	}

	/**< load OpenGL 4.2 extensions */
	void Load4_2Extensions()
	{
		FetchProcAddress(glDrawArraysInstancedBaseInstance, "glDrawArraysInstancedBaseInstance");
		FetchProcAddress(glDrawElementsInstancedBaseInstance, "glDrawElementsInstancedBaseInstance");
		FetchProcAddress(glDrawElementsInstancedBaseVertexBaseInstance, "glDrawElementsInstancedBaseVertexBaseInstance");
		FetchProcAddress(glGetInternalformativ, "glGetInternalformativ");
		FetchProcAddress(glGetActiveAtomicCounterBufferiv, "glGetActiveAtomicCounterBufferiv");
		FetchProcAddress(glBindImageTexture, "glBindImageTexture");
		FetchProcAddress(glMemoryBarrier, "glMemoryBarrier");
		FetchProcAddress(glTexStorage1D, "glTexStorage1D");
		FetchProcAddress(glTexStorage2D, "glTexStorage2D");
		FetchProcAddress(glTexStorage3D, "glTexStorage3D");
		FetchProcAddress(glDrawTransformFeedbackInstanced, "glDrawTransformFeedbackInstanced");
		FetchProcAddress(glDrawTransformFeedbackStreamInstanced, "glDrawTransformFeedbackStreamInstanced");
	}

	/**< load OpenGL 4.3 extensions */
	void Load4_3Extensions()
	{
		FetchProcAddress(glClearBufferData, "glClearBufferData");
		FetchProcAddress(glClearBufferSubData, "glClearBufferSubData");
		FetchProcAddress(glDispatchCompute, "glDispatchCompute");
		FetchProcAddress(glDispatchComputeIndirect, "glDispatchComputeIndirect");
		FetchProcAddress(glCopyImageSubData, "glCopyImageSubData");
		FetchProcAddress(glFramebufferParameteri, "glFramebufferParameteri");
		FetchProcAddress(glGetFramebufferParameteriv, "glGetFramebufferParameteriv");
		FetchProcAddress(glGetInternalformati64v, "glGetInternalformati64v");
		FetchProcAddress(glInvalidateTexSubImage, "glInvalidateTexSubImage");
		FetchProcAddress(glInvalidateTexImage, "glInvalidateTexImage");
		FetchProcAddress(glInvalidateBufferSubData, "glInvalidateBufferSubData");
		FetchProcAddress(glInvalidateBufferData, "glInvalidateBufferData");
		FetchProcAddress(glInvalidateFramebuffer, "glInvalidateFramebuffer");
		FetchProcAddress(glInvalidateSubFramebuffer, "glInvalidateSubFramebuffer");
		FetchProcAddress(glMultiDrawArraysIndirect, "glMultiDrawArraysIndirect");
		FetchProcAddress(glMultiDrawElementsIndirect, "glMultiDrawElementsIndirect");
		FetchProcAddress(glGetProgramInterfaceiv, "glGetProgramInterfaceiv");
		FetchProcAddress(glGetProgramResourceIndex, "glGetProgramResourceIndex");
		FetchProcAddress(glGetProgramResourceName, "glGetProgramResourceName");
		FetchProcAddress(glGetProgramResourceiv, "glGetProgramResourceiv");
		FetchProcAddress(glGetProgramResourceLocation, "glGetProgramResourceLocation");
		FetchProcAddress(glGetProgramResourceLocationIndex, "glGetProgramResourceLocationIndex");
		FetchProcAddress(glShaderStorageBlockBinding, "glShaderStorageBlockBinding");
		FetchProcAddress(glTexBufferRange, "glTexBufferRange");
		FetchProcAddress(glTexStorage2DMultisample, "glTexStorage2DMultisample");
		FetchProcAddress(glTexStorage3DMultisample, "glTexStorage3DMultisample");
		FetchProcAddress(glTextureView, "glTextureView");
		FetchProcAddress(glBindVertexBuffer, "glBindVertexBuffer");
		FetchProcAddress(glVertexAttribFormat, "glVertexAttribFormat");
		FetchProcAddress(glVertexAttribIFormat, "glVertexAttribIFormat");
		FetchProcAddress(glVertexAttribLFormat, "glVertexAttribLFormat");
		FetchProcAddress(glVertexAttribBinding, "glVertexAttribBinding");
		FetchProcAddress(glVertexBindingDivisor, "glVertexBindingDivisor");
		FetchProcAddress(glDebugMessageControl, "glDebugMessageControl");
		FetchProcAddress(glDebugMessageInsert, "glDebugMessageInsert");
		FetchProcAddress(glDebugMessageCallback, "glDebugMessageCallback");
		FetchProcAddress(glGetDebugMessageLog, "glGetDebugMessageLog");
		FetchProcAddress(glPushDebugGroup, "glPushDebugGroup");
		FetchProcAddress(glPopDebugGroup, "glPopDebugGroup");
		FetchProcAddress(glObjectLabel, "glObjectLabel");
		FetchProcAddress(glObjectPtrLabel, "glObjectPtrLabel");
		FetchProcAddress(glGetObjectLabel, "glGetObjectLabel");
		FetchProcAddress(glGetObjectPtrLabel, "glGetObjectPtrLabel");
	}

	/**< load OpenGL 4.4 extensions */
	void Load4_4Extensions()
	{
		FetchProcAddress(glBufferStorage, "glBufferStorage");
		FetchProcAddress(glClearTexImage, "glClearTexImage");
		FetchProcAddress(glClearTexSubImage, "glClearTexSubImage");
		FetchProcAddress(glBindBuffersBase, "glBindBuffersBase");
		FetchProcAddress(glBindBuffersRange, "glBindBuffersRange");
		FetchProcAddress(glBindTextures, "glBindTextures");
		FetchProcAddress(glBindSamplers, "glBindSamplers");
		FetchProcAddress(glBindImageTextures, "glBindImageTextures");
		FetchProcAddress(glBindVertexBuffers, "glBindVertexBuffers");
	}

	/**< load all applicable OpenGL extensions */
	std::error_code InitializeExtentions()
	{
		std::error_code errCode = InitializeGLVersion();

		if (errCode == TinyExtender::error_t::versionLoadFailed)
		{
			return 	errCode;
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 2 && glVersionMajor >= 1))
		{
			Load1_2Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported1_2;
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 3 && glVersionMajor >= 1))
		{
			Load1_3Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported1_3;
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 4 && glVersionMajor >= 1))
		{
			Load1_4Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported1_4;
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 5 && glVersionMajor >= 1))
		{
			Load1_5Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported1_5;
		}

		if (glVersionMajor >= 2)
		{
			Load2_0Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported2_0;
		}

		if (glVersionMajor > 2 || (glVersionMinor >= 1 && glVersionMajor >= 2))
		{
			Load2_1Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported2_1;
		}

		if (glVersionMajor >= 3)
		{
			Load3_0Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported3_0;
		}

		if (glVersionMajor > 3 || (glVersionMinor >= 1 && glVersionMajor >= 3))
		{
			Load3_1Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported3_1;
		}

		if (glVersionMajor > 3 || (glVersionMinor >= 2 && glVersionMajor >= 3))
		{
			Load3_2Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported3_2;
		}

		if (glVersionMajor > 3 || (glVersionMinor >= 3 && glVersionMajor >= 3))
		{
			Load3_3Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported3_3;
		}

		if (glVersionMajor >= 4)
		{
			Load4_0Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported4_0;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 1 && glVersionMajor >= 4))
		{
			Load4_1Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported4_1;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 2 && glVersionMajor >= 4))
		{
			Load4_2Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported4_2;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 3 && glVersionMajor >= 4))
		{
			Load4_3Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported4_3;
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 4 && glVersionMajor >= 4))
		{
			Load4_4Extensions();
		}

		else
		{
			return TinyExtender::error_t::Unsupported4_4;
		}

		return TinyExtender::error_t::success;
	}

	/**< load specific OpenGL extensions via OpenGL versions */
	std::error_code InitializeExtensionsSpecific(unsigned int OpenGLVersions)
	{
		if (OpenGLVersions & glVersion_t::version1_2)
		{
			if (glVersionMajor > 1 || (glVersionMinor >= 2 && glVersionMajor >= 1))
			{
				Load1_2Extensions();
			}

			else
			{
				return TinyExtender::error_t::Unsupported1_2;
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
				return TinyExtender::error_t::Unsupported1_3;
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
				return TinyExtender::error_t::Unsupported1_4;
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
				return TinyExtender::error_t::Unsupported1_5;
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
				return TinyExtender::error_t::Unsupported2_0;
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
				return TinyExtender::error_t::Unsupported2_1;
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
				return TinyExtender::error_t::Unsupported3_0;
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
				return TinyExtender::error_t::Unsupported3_1;
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
				return TinyExtender::error_t::Unsupported3_2;
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
				return TinyExtender::error_t::Unsupported3_3;
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
				return TinyExtender::error_t::Unsupported4_0;
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
				return TinyExtender::error_t::Unsupported4_1;
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
				return TinyExtender::error_t::Unsupported4_2;
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
				return TinyExtender::error_t::Unsupported4_3;
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
				return TinyExtender::error_t::Unsupported4_4;
			}
		}

		return TinyExtender::error_t::success;
	}

	/**< whether an extension is supported */
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
				size_t str = strcspn((const char*)allExtensions, " ");

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
