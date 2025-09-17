#ifndef TINYEXTENDER_H_
#define	TINYEXTENDER_H_

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wredefined"

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
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#include <gl/GL.h>
#endif //_WIN32 || _WIN64

#if defined(__linux__)
#ifndef TE_LINUX
#define TE_LINUX
#endif
#include <GL/glx.h>
#endif //__linux__

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

#include <utility>
#include <vector>
#include <cstdlib>
#include <functional>
#include <memory>
#include <bitset>
#include <cmath>
#include <ranges>

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

	/**< returns a proc address to an OpenGL extension */
	template<typename T> void FetchProcAddress(T& funcPointer, const char* procName)
	{
#if defined(TE_WINDOWS)
		funcPointer = (T)wglGetProcAddress(procName);
#elif defined(TE_LINUX)
		funcPointer = (T)glXGetProcAddress((const unsigned char*)procName);
#endif
	}

	//OpenGL 1.2 Extensions
#pragma region OpenGL1_2

	#define GL_SMOOTH_POINT_SIZE_RANGE 0x0b12
	#define GL_SMOOTH_POINT_SIZE_GRANULARITY 0x0b13
	#define GL_SMOOTH_LINE_WIDTH_RANGE 0x0b22
	#define GL_SMOOTH_LINE_WIDTH_GRANULARITY 0x0b23
	#define GL_UNSIGNED_BYTE_3_3_2 0x8032
	#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
	#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
	#define GL_UNSIGNED_INT_8_8_8_8 0x8035
	#define GL_UNSIGNED_INT_10_10_10_2 0x8036
	#define GL_RESCALE_NORMAL 0x803a
	#define GL_TEXTURE_BINDING_3D 0x806a
	#define GL_PACK_SKIP_IMAGES 0x806b
	#define GL_PACK_IMAGE_HEIGHT 0x806c
	#define GL_UNPACK_SKIP_IMAGES 0x806d
	#define GL_UNPACK_IMAGE_HEIGHT 0x806e
	#define GL_TEXTURE_3D 0x806f
	#define GL_PROXY_TEXTURE_3D 0x8070
	#define GL_TEXTURE_DEPTH 0x8071
	#define GL_TEXTURE_WRAP_R 0x8072
	#define GL_MAX_3D_TEXTURE_SIZE 0x8073
	#define GL_BGR 0x80e0
	#define GL_BGRA 0x80e1
	#define GL_MAX_ELEMENTS_VERTICES 0x80e8
	#define GL_MAX_ELEMENTS_INDICES 0x80e9
	#define GL_CLAMP_TO_EDGE 0x812f
	#define GL_TEXTURE_MIN_LOD 0x813a
	#define GL_TEXTURE_MAX_LOD 0x813b
	#define GL_TEXTURE_BASE_LEVEL 0x813c
	#define GL_TEXTURE_MAX_LEVEL 0x813d
	#define GL_LIGHT_MODEL_COLOR_CONTROL 0x81f8
	#define GL_SINGLE_COLOR 0x81f9
	#define GL_SEPARATE_SPECULAR_COLOR 0x81fa
	#define GL_UNSIGNED_BYTE_2_3_3_REV 0x8362
	#define GL_UNSIGNED_SHORT_5_6_5 0x8363
	#define GL_UNSIGNED_SHORT_5_6_5_REV 0x8364
	#define GL_UNSIGNED_SHORT_4_4_4_4_REV 0x8365
	#define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
	#define GL_UNSIGNED_INT_8_8_8_8_REV 0x8367
	#define GL_ALIASED_POINT_SIZE_RANGE 0x846d
	#define GL_ALIASED_LINE_WIDTH_RANGE 0x846e

	inline void(*glDrawRangeElements) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices) = nullptr;
	inline void(*glTexImage3D) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels) = nullptr;
	inline void(*glTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels) = nullptr;
	inline void(*glCopyTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;

	//*< load OpenGL 1.2 extensions
	inline void Load1_2Extensions()
	{
		FetchProcAddress(glDrawRangeElements, "glDrawRangeElements");
		FetchProcAddress(glTexImage3D, "glTexImage3D");
		FetchProcAddress(glTexSubImage3D, "glTexSubImage3D");
		FetchProcAddress(glCopyTexSubImage3D, "glCopyTexSubImage3D");
	}

#pragma endregion OpenGL1_2 Extensions

	//OpenGL 1.3 Extensions
#pragma region OpenGL1_3

	// OpenGL 1.3 defines
	#define GL_MULTISAMPLE 0x809d
	#define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809e
	#define GL_SAMPLE_ALPHA_TO_ONE 0x809f
	#define GL_SAMPLE_COVERAGE 0x80a0
	#define GL_SAMPLE_BUFFERS 0x80a8
	#define GL_SAMPLES 0x80a9
	#define GL_SAMPLE_COVERAGE_VALUE 0x80aa
	#define GL_SAMPLE_COVERAGE_INVERT 0x80ab
	#define GL_CLAMP_TO_BORDER 0x812d
	#define GL_TEXTURE0 0x84c0
	#define GL_TEXTURE1 0x84c1
	#define GL_TEXTURE2 0x84c2
	#define GL_TEXTURE3 0x84c3
	#define GL_TEXTURE4 0x84c4
	#define GL_TEXTURE5 0x84c5
	#define GL_TEXTURE6 0x84c6
	#define GL_TEXTURE7 0x84c7
	#define GL_TEXTURE8 0x84c8
	#define GL_TEXTURE9 0x84c9
	#define GL_TEXTURE10 0x84ca
	#define GL_TEXTURE11 0x84cb
	#define GL_TEXTURE12 0x84cc
	#define GL_TEXTURE13 0x84cd
	#define GL_TEXTURE14 0x84ce
	#define GL_TEXTURE15 0x84cf
	#define GL_TEXTURE16 0x84d0
	#define GL_TEXTURE17 0x84d1
	#define GL_TEXTURE18 0x84d2
	#define GL_TEXTURE19 0x84d3
	#define GL_TEXTURE20 0x84d4
	#define GL_TEXTURE21 0x84d5
	#define GL_TEXTURE22 0x84d6
	#define GL_TEXTURE23 0x84d7
	#define GL_TEXTURE24 0x84d8
	#define GL_TEXTURE25 0x84d9
	#define GL_TEXTURE26 0x84da
	#define GL_TEXTURE27 0x84db
	#define GL_TEXTURE28 0x84dc
	#define GL_TEXTURE29 0x84dd
	#define GL_TEXTURE30 0x84de
	#define GL_TEXTURE31 0x84df
	#define GL_ACTIVE_TEXTURE 0x84e0
	#define GL_CLIENT_ACTIVE_TEXTURE 0x84e1
	#define GL_MAX_TEXTURE_UNITS 0x84e2
	#define GL_TRANSPOSE_MODELVIEW_MATRIX 0x84e3
	#define GL_TRANSPOSE_PROJECTION_MATRIX 0x84e4
	#define GL_TRANSPOSE_TEXTURE_MATRIX 0x84e5
	#define GL_TRANSPOSE_COLOR_MATRIX 0x84e6
	#define GL_SUBTRACT 0x84e7
	#define GL_COMPRESSED_ALPHA 0x84e9
	#define GL_COMPRESSED_LUMINANCE 0x84ea
	#define GL_COMPRESSED_LUMINANCE_ALPHA 0x84eb
	#define GL_COMPRESSED_INTENSITY 0x84ec
	#define GL_COMPRESSED_RGB 0x84ed
	#define GL_COMPRESSED_RGBA 0x84ee
	#define GL_TEXTURE_COMPRESSION_HINT 0x84ef
	#define GL_NORMAL_MAP 0x8511
	#define GL_REFLECTION_MAP 0x8512
	#define GL_TEXTURE_CUBE_MAP 0x8513
	#define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
	#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
	#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
	#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
	#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
	#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
	#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851a
	#define GL_PROXY_TEXTURE_CUBE_MAP 0x851b
	#define GL_MAX_CUBE_MAP_TEXTURE_SIZE 0x851c
	#define GL_COMBINE 0x8570
	#define GL_COMBINE_RGB 0x8571
	#define GL_COMBINE_ALPHA 0x8572
	#define GL_RGB_SCALE 0x8573
	#define GL_ADD_SIGNED 0x8574
	#define GL_INTERPOLATE 0x8575
	#define GL_CONSTANT 0x8576
	#define GL_PRIMARY_COLOR 0x8577
	#define GL_PREVIOUS 0x8578
	#define GL_SOURCE0_RGB 0x8580
	#define GL_SOURCE1_RGB 0x8581
	#define GL_SOURCE2_RGB 0x8582
	#define GL_SOURCE0_ALPHA 0x8588
	#define GL_SOURCE1_ALPHA 0x8589
	#define GL_SOURCE2_ALPHA 0x858a
	#define GL_OPERAND0_RGB 0x8590
	#define GL_OPERAND1_RGB 0x8591
	#define GL_OPERAND2_RGB 0x8592
	#define GL_OPERAND0_ALPHA 0x8598
	#define GL_OPERAND1_ALPHA 0x8599
	#define GL_OPERAND2_ALPHA 0x859a
	#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE 0x86a0
	#define GL_TEXTURE_COMPRESSED 0x86a1
	#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86a2
	#define GL_COMPRESSED_TEXTURE_FORMATS 0x86a3
	#define GL_DOT3_RGB 0x86ae
	#define GL_DOT3_RGBA 0x86af
	#define GL_MULTISAMPLE_BIT 0x20000000

#ifndef TE_LINUX
	inline void(*glActiveTexture) (GLenum texture) = nullptr;
#endif
	inline void(*glClientActiveTexture) (GLenum texture) = nullptr;
	inline void(*glCompressedTexImage1D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTexImage2D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTexImage3D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data) = nullptr;

	inline void(*glCompressedTexSubImage1D) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data) = nullptr;
#ifndef TE_LINUX
	void(*glCompressedTexSubImage2D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
#endif
	inline void(*glCompressedTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glGetCompressedTexImage) (GLenum target, GLint level, void *img) = nullptr;
	
	inline void(*glLoadTransposeMatrixd) (const GLdouble* m) = nullptr;
	inline void(*glLoadTransposeMatrixf) (const GLfloat* m) = nullptr;
	inline void(*glMultTransposeMatrixd) (const GLdouble* m) = nullptr;
	inline void(*glMultTransposeMatrixf) (const GLfloat* m) = nullptr;

	inline void(*glMultiTexCoord1d) (GLenum target, GLdouble s) = nullptr;
	inline void(*glMultiTexCoord1dv) (GLenum target, const GLdouble *v) = nullptr;
	inline void(*glMultiTexCoord1f) (GLenum target, GLfloat s) = nullptr;
	inline void(*glMultiTexCoord1fv) (GLenum target, const GLfloat *v) = nullptr;
	inline void(*glMultiTexCoord1i) (GLenum target, GLint s) = nullptr;
	inline void(*glMultiTexCoord1iv) (GLenum target, const GLint *v) = nullptr;
	inline void(*glMultiTexCoord1s) (GLenum target, GLshort s) = nullptr;
	inline void(*glMultiTexCoord1sv) (GLenum target, const GLshort *v) = nullptr;
	inline void(*glMultiTexCoord2d) (GLenum target, GLdouble s, GLdouble t) = nullptr;
	inline void(*glMultiTexCoord2dv) (GLenum target, const GLdouble *v) = nullptr;
	inline void(*glMultiTexCoord2f) (GLenum target, GLfloat s, GLfloat t) = nullptr;
	inline void(*glMultiTexCoord2fv) (GLenum target, const GLfloat *v) = nullptr;
	inline void(*glMultiTexCoord2i) (GLenum target, GLint s, GLint t) = nullptr;
	inline void(*glMultiTexCoord2iv) (GLenum target, const GLint *v) = nullptr;
	inline void(*glMultiTexCoord2s) (GLenum target, GLshort s, GLshort t) = nullptr;
	inline void(*glMultiTexCoord2sv) (GLenum target, const GLshort *v) = nullptr;
	inline void(*glMultiTexCoord3d) (GLenum target, GLdouble s, GLdouble t, GLdouble r) = nullptr;
	inline void(*glMultiTexCoord3dv) (GLenum target, const GLdouble *v) = nullptr;
	inline void(*glMultiTexCoord3f) (GLenum target, GLfloat s, GLfloat t, GLfloat r) = nullptr;
	inline void(*glMultiTexCoord3fv) (GLenum target, const GLfloat *v) = nullptr;
	inline void(*glMultiTexCoord3i) (GLenum target, GLint s, GLint t, GLint r) = nullptr;
	inline void(*glMultiTexCoord3iv) (GLenum target, const GLint *v) = nullptr;
	inline void(*glMultiTexCoord3s) (GLenum target, GLshort s, GLshort t, GLshort r) = nullptr;
	inline void(*glMultiTexCoord3sv) (GLenum target, const GLshort *v) = nullptr;
	inline void(*glMultiTexCoord4d) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) = nullptr;
	inline void(*glMultiTexCoord4dv) (GLenum target, const GLdouble *v) = nullptr;
	inline void(*glMultiTexCoord4f) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) = nullptr;
	inline void(*glMultiTexCoord4fv) (GLenum target, const GLfloat *v) = nullptr;
	inline void(*glMultiTexCoord4i) (GLenum target, GLint s, GLint t, GLint r, GLint q) = nullptr;
	inline void(*glMultiTexCoord4iv) (GLenum target, const GLint *v) = nullptr;
	inline void(*glMultiTexCoord4s) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) = nullptr;
	inline void(*glMultiTexCoord4sv) (GLenum target, const GLshort *v) = nullptr;
	inline void(*glSampleCoverage) (GLfloat value, GLboolean invert) = nullptr;

	//*< load OpenGL 1.3 extensions
	inline void Load1_3Extensions()
	{
#ifndef TE_LINUX
		FetchProcAddress(glActiveTexture, "glActiveTexture");
#endif
		FetchProcAddress(glSampleCoverage, "glSampleCoverage");
		FetchProcAddress(glCompressedTexImage3D, "glCompressedTexImage3D");
		FetchProcAddress(glCompressedTexImage2D, "glCompressedTexImage2D");
		FetchProcAddress(glCompressedTexImage1D, "glCompressedTexImage1D");
		FetchProcAddress(glCompressedTexSubImage3D, "glCompressedTexSubImage3D");
#ifndef TE_LINUX
		FetchProcAddress(glCompressedTexSubImage2D, "glCompressedTexSubImage2D");
#endif
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

	#define GL_BLEND_DST_RGB 0x80c8
	#define GL_BLEND_SRC_RGB 0x80c9
	#define GL_BLEND_DST_ALPHA 0x80ca
	#define GL_BLEND_SRC_ALPHA 0x80cb
	#define GL_POINT_SIZE_MIN 0x8126
	#define GL_POINT_SIZE_MAX 0x8127
	#define GL_POINT_FADE_THRESHOLD_SIZE 0x8128
	#define GL_POINT_DISTANCE_ATTENUATION 0x8129
	#define GL_GENERATE_MIPMAP 0x8191
	#define GL_GENERATE_MIPMAP_HINT 0x8192
	#define GL_DEPTH_COMPONENT16 0x81a5
	#define GL_DEPTH_COMPONENT24 0x81a6
	#define GL_DEPTH_COMPONENT32 0x81a7
	#define GL_MIRRORED_REPEAT 0x8370
	#define GL_FOG_COORDINATE_SOURCE 0x8450
	#define GL_FOG_COORDINATE 0x8451
	#define GL_FRAGMENT_DEPTH 0x8452
	#define GL_CURRENT_FOG_COORDINATE 0x8453
	#define GL_FOG_COORDINATE_ARRAY_TYPE 0x8454
	#define GL_FOG_COORDINATE_ARRAY_STRIDE 0x8455
	#define GL_FOG_COORDINATE_ARRAY_POINTER 0x8456
	#define GL_FOG_COORDINATE_ARRAY 0x8457
	#define GL_COLOR_SUM 0x8458
	#define GL_CURRENT_SECONDARY_COLOR 0x8459
	#define GL_SECONDARY_COLOR_ARRAY_SIZE 0x845a
	#define GL_SECONDARY_COLOR_ARRAY_TYPE 0x845b
	#define GL_SECONDARY_COLOR_ARRAY_STRIDE 0x845c
	#define GL_SECONDARY_COLOR_ARRAY_POINTER 0x845d
	#define GL_SECONDARY_COLOR_ARRAY 0x845e
	#define GL_MAX_TEXTURE_LOD_BIAS 0x84fd
	#define GL_TEXTURE_FILTER_CONTROL 0x8500
	#define GL_TEXTURE_LOD_BIAS 0x8501
	#define GL_INCR_WRAP 0x8507
	#define GL_DECR_WRAP 0x8508
	#define GL_TEXTURE_DEPTH_SIZE 0x884a
	#define GL_DEPTH_TEXTURE_MODE 0x884b
	#define GL_TEXTURE_COMPARE_MODE 0x884c
	#define GL_TEXTURE_COMPARE_FUNC 0x884d
	#define GL_COMPARE_R_TO_TEXTURE 0x884e

	inline void(*glBlendColor) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = nullptr;
#ifndef TE_LINUX
	inline void(*glBlendEquation) (GLenum mode) = nullptr;
#endif
	inline void(*glBlendFuncSeparate) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) = nullptr;
	inline void(*glMultiDrawArrays) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount) = nullptr;
	inline void(*glMultiDrawElements) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount) = nullptr;
	inline void(*glPointParameterf) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glPointParameterfv) (GLenum pname, const GLfloat *params) = nullptr;
	inline void(*glPointParameteri) (GLenum pname, GLint param) = nullptr;
	inline void(*glPointParameteriv) (GLenum pname, const GLint *params) = nullptr;
	inline void(*glFogCoordf) (GLfloat coord) = nullptr;
	inline void(*glFogCoordfv) (const GLfloat *coord) = nullptr;
	inline void(*glFogCoordd) (GLdouble coord) = nullptr;
	inline void(*glFogCoorddv) (const GLdouble *coord) = nullptr;
	inline void(*glFogCoordPointer) (GLenum type, GLsizei stride, const void *pointer) = nullptr;
	inline void(*glSecondaryColor3b) (GLbyte red, GLbyte green, GLbyte blue) = nullptr;
	inline void(*glSecondaryColor3bv) (const GLbyte *v) = nullptr;
	inline void(*glSecondaryColor3d) (GLdouble red, GLdouble green, GLdouble blue) = nullptr;
	inline void(*glSecondaryColor3dv) (const GLdouble *v) = nullptr;
	inline void(*glSecondaryColor3f) (GLfloat red, GLfloat green, GLfloat blue) = nullptr;
	inline void(*glSecondaryColor3fv) (const GLfloat *v) = nullptr;
	inline void(*glSecondaryColor3i) (GLint red, GLint green, GLint blue) = nullptr;
	inline void(*glSecondaryColor3iv) (const GLint *v) = nullptr;
	inline void(*glSecondaryColor3s) (GLshort red, GLshort green, GLshort blue) = nullptr;
	inline void(*glSecondaryColor3sv) (const GLshort *v) = nullptr;
	inline void(*glSecondaryColor3ub) (GLubyte red, GLubyte green, GLubyte blue) = nullptr;
	inline void(*glSecondaryColor3ubv) (const GLubyte *v) = nullptr;
	inline void(*glSecondaryColor3ui) (GLuint red, GLuint green, GLuint blue) = nullptr;
	inline void(*glSecondaryColor3uiv) (const GLuint *v) = nullptr;
	inline void(*glSecondaryColor3us) (GLushort red, GLushort green, GLushort blue) = nullptr;
	inline void(*glSecondaryColor3usv) (const GLushort *v) = nullptr;
	inline void(*glSecondaryColorPointer) (GLint size, GLenum type, GLsizei stride, const void *pointer) = nullptr;
	inline void(*glWindowPos2d) (GLdouble x, GLdouble y) = nullptr;
	inline void(*glWindowPos2dv) (const GLdouble *v) = nullptr;
	inline void(*glWindowPos2f) (GLfloat x, GLfloat y) = nullptr;
	inline void(*glWindowPos2fv) (const GLfloat *v) = nullptr;
	inline void(*glWindowPos2i) (GLint x, GLint y) = nullptr;
	inline void(*glWindowPos2iv) (const GLint *v) = nullptr;
	inline void(*glWindowPos2s) (GLshort x, GLshort y) = nullptr;
	inline void(*glWindowPos2sv) (const GLshort *v) = nullptr;
	inline void(*glWindowPos3d) (GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glWindowPos3dv) (const GLdouble *v) = nullptr;
	inline void(*glWindowPos3f) (GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glWindowPos3fv) (const GLfloat *v) = nullptr;
	inline void(*glWindowPos3i) (GLint x, GLint y, GLint z) = nullptr;
	inline void(*glWindowPos3iv) (const GLint *v) = nullptr;
	inline void(*glWindowPos3s) (GLshort x, GLshort y, GLshort z) = nullptr;
	inline void(*glWindowPos3sv) (const GLshort *v) = nullptr;

	//*< load OpenGL 1.4 extensions
	inline void Load1_4Extensions()
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
#ifndef TE_LINUX
		FetchProcAddress(glBlendEquation, "glBlendEquation");
#endif
	}
#pragma endregion OpenGL1_4 Extensions

	//OpenGL 1.5 Extensions
#pragma region OpenGL1_5

	using GLsizeiptr = ptrdiff_t;
	using GLintptr = ptrdiff_t;

	// OpenGL 1.5 defines
	#define GL_BUFFER_SIZE 0x8764
	#define GL_BUFFER_USAGE 0x8765
	#define GL_QUERY_COUNTER_BITS 0x8864
	#define GL_CURRENT_QUERY 0x8865
	#define GL_QUERY_RESULT 0x8866
	#define GL_QUERY_RESULT_AVAILABLE 0x8867
	#define GL_ARRAY_BUFFER 0x8892
	#define GL_ELEMENT_ARRAY_BUFFER 0x8893
	#define GL_ARRAY_BUFFER_BINDING 0x8894
	#define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
	#define GL_VERTEX_ARRAY_BUFFER_BINDING 0x8896
	#define GL_NORMAL_ARRAY_BUFFER_BINDING 0x8897
	#define GL_COLOR_ARRAY_BUFFER_BINDING 0x8898
	#define GL_INDEX_ARRAY_BUFFER_BINDING 0x8899
	#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889a
	#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING 0x889b
	#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING 0x889c
	#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING 0x889d
	#define GL_WEIGHT_ARRAY_BUFFER_BINDING 0x889e
	#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889f
	#define GL_READ_ONLY 0x88b8
	#define GL_WRITE_ONLY 0x88b9
	#define GL_READ_WRITE 0x88ba
	#define GL_BUFFER_ACCESS 0x88bb
	#define GL_BUFFER_MAPPED 0x88bc
	#define GL_BUFFER_MAP_POINTER 0x88bd
	#define GL_STREAM_DRAW 0x88e0
	#define GL_STREAM_READ 0x88e1
	#define GL_STREAM_COPY 0x88e2
	#define GL_STATIC_DRAW 0x88e4
	#define GL_STATIC_READ 0x88e5
	#define GL_STATIC_COPY 0x88e6
	#define GL_DYNAMIC_DRAW 0x88e8
	#define GL_DYNAMIC_READ 0x88e9
	#define GL_DYNAMIC_COPY 0x88ea
	#define GL_SAMPLES_PASSED 0x8914
	// what is the point of this?
	#define GL_CURRENT_FOG_COORD GL_CURRENT_FOG_COORDINATE
	#define GL_FOG_COORD GL_FOG_COORDINATE
	#define GL_FOG_COORD_ARRAY GL_FOG_COORDINATE_ARRAY
	#define GL_FOG_COORD_ARRAY_BUFFER_BINDING GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING
	#define GL_FOG_COORD_ARRAY_POINTER GL_FOG_COORDINATE_ARRAY_POINTER
	#define GL_FOG_COORD_ARRAY_STRIDE GL_FOG_COORDINATE_ARRAY_STRIDE
	#define GL_FOG_COORD_ARRAY_TYPE GL_FOG_COORDINATE_ARRAY_TYPE
	#define GL_FOG_COORD_SRC GL_FOG_COORDINATE_SOURCE
	#define GL_SRC0_ALPHA GL_SOURCE0_ALPHA
	#define GL_SRC0_RGB GL_SOURCE0_RGB
	#define GL_SRC1_ALPHA GL_SOURCE1_ALPHA
	#define GL_SRC1_RGB GL_SOURCE1_RGB
	#define GL_SRC2_ALPHA GL_SOURCE2_ALPHA
	#define GL_SRC2_RGB GL_SOURCE2_RGB

	inline void(*glGenQueries) (GLsizei n, GLuint *ids);
	inline void(*glDeleteQueries) (GLsizei n, const GLuint *ids);
	inline GLboolean(*glIsQuery) (GLuint id);
	inline void(*glBeginQuery) (GLenum target, GLuint id);
	inline void(*glEndQuery) (GLenum target);
	inline void(*glGetQueryiv) (GLenum target, GLenum pname, GLint *params);
	inline void(*glGetQueryObjectiv) (GLuint id, GLenum pname, GLint *params);
	inline void(*glGetQueryObjectuiv) (GLuint id, GLenum pname, GLuint *params);
	inline void(*glBindBuffer) (GLenum target, GLuint buffer);
	inline void(*glDeleteBuffers) (GLsizei n, const GLuint *buffers);
	inline void(*glGenBuffers) (GLsizei n, GLuint *buffers);
	inline GLboolean(*glIsBuffer) (GLuint buffer);
	inline void(*glBufferData) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
	inline void(*glBufferSubData) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
	inline void(*glGetBufferSubData) (GLenum target, GLintptr offset, GLsizeiptr size, void *data);
	inline void * (*glMapBuffer) (GLenum target, GLenum access);
	inline GLboolean(*glUnmapBuffer) (GLenum target);
	inline void(*glGetBufferParameteriv) (GLenum target, GLenum pname, GLint *params);
	inline void(*glGetBufferPointerv) (GLenum target, GLenum pname, void **params);

	//*< load OpenGL 1.5 extensions
	inline void Load1_5Extensions()
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
	
	// OpenGL 2.0 defines
	#define GL_BLEND_EQUATION_RGB 0x8009
	#define GL_VERTEX_ATTRIB_ARRAY_ENABLED 0x8622
	#define GL_VERTEX_ATTRIB_ARRAY_SIZE 0x8623
	#define GL_VERTEX_ATTRIB_ARRAY_STRIDE 0x8624
	#define GL_VERTEX_ATTRIB_ARRAY_TYPE 0x8625
	#define GL_CURRENT_VERTEX_ATTRIB 0x8626
	#define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642
	#define GL_VERTEX_ATTRIB_ARRAY_POINTER 0x8645
	#define GL_STENCIL_BACK_FUNC 0x8800
	#define GL_STENCIL_BACK_FAIL 0x8801
	#define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
	#define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
	#define GL_MAX_DRAW_BUFFERS 0x8824
	#define GL_DRAW_BUFFER0 0x8825
	#define GL_DRAW_BUFFER1 0x8826
	#define GL_DRAW_BUFFER2 0x8827
	#define GL_DRAW_BUFFER3 0x8828
	#define GL_DRAW_BUFFER4 0x8829
	#define GL_DRAW_BUFFER5 0x882a
	#define GL_DRAW_BUFFER6 0x882b
	#define GL_DRAW_BUFFER7 0x882c
	#define GL_DRAW_BUFFER8 0x882d
	#define GL_DRAW_BUFFER9 0x882e
	#define GL_DRAW_BUFFER10 0x882f
	#define GL_DRAW_BUFFER11 0x8830
	#define GL_DRAW_BUFFER12 0x8831
	#define GL_DRAW_BUFFER13 0x8832
	#define GL_DRAW_BUFFER14 0x8833
	#define GL_DRAW_BUFFER15 0x8834
	#define GL_BLEND_EQUATION_ALPHA 0x883d
	#define GL_MAX_VERTEX_ATTRIBS 0x8869
	#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886a
	#define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
	#define GL_FRAGMENT_SHADER 0x8b30
	#define GL_VERTEX_SHADER 0x8b31
	#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8b49
	#define GL_MAX_VERTEX_UNIFORM_COMPONENTS 0x8b4a
	#define GL_MAX_VARYING_FLOATS 0x8b4b
	#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8b4c
	#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8b4d
	#define GL_SHADER_TYPE 0x8b4f
	#define GL_FLOAT_VEC2 0x8b50
	#define GL_FLOAT_VEC3 0x8b51
	#define GL_FLOAT_VEC4 0x8b52
	#define GL_INT_VEC2 0x8b53
	#define GL_INT_VEC3 0x8b54
	#define GL_INT_VEC4 0x8b55
	#define GL_BOOL 0x8b56
	#define GL_BOOL_VEC2 0x8b57
	#define GL_BOOL_VEC3 0x8b58
	#define GL_BOOL_VEC4 0x8b59
	#define GL_FLOAT_MAT2 0x8b5a
	#define GL_FLOAT_MAT3 0x8b5b
	#define GL_FLOAT_MAT4 0x8b5c
	#define GL_SAMPLER_1D 0x8b5d
	#define GL_SAMPLER_2D 0x8b5e
	#define GL_SAMPLER_3D 0x8b5f
	#define GL_SAMPLER_CUBE 0x8b60
	#define GL_SAMPLER_1D_SHADOW 0x8b61
	#define GL_SAMPLER_2D_SHADOW 0x8b62
	#define GL_DELETE_STATUS 0x8b80
	#define GL_COMPILE_STATUS 0x8b81
	#define GL_LINK_STATUS 0x8b82
	#define GL_VALIDATE_STATUS 0x8b83
	#define GL_INFO_LOG_LENGTH 0x8b84
	#define GL_ATTACHED_SHADERS 0x8b85
	#define GL_ACTIVE_UNIFORMS 0x8b86
	#define GL_ACTIVE_UNIFORM_MAX_LENGTH 0x8b87
	#define GL_SHADER_SOURCE_LENGTH 0x8b88
	#define GL_ACTIVE_ATTRIBUTES 0x8b89
	#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 0x8b8a
	#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8b8b
	#define GL_SHADING_LANGUAGE_VERSION 0x8b8c
	#define GL_CURRENT_PROGRAM 0x8b8d
	#define GL_POINT_SPRITE_COORD_ORIGIN 0x8ca0
	#define GL_LOWER_LEFT 0x8ca1
	#define GL_UPPER_LEFT 0x8ca2
	#define GL_STENCIL_BACK_REF 0x8ca3
	#define GL_STENCIL_BACK_VALUE_MASK 0x8ca4
	#define GL_STENCIL_BACK_WRITEMASK 0x8ca5
	#define GL_VERTEX_PROGRAM_TWO_SIDE 0x8643
	#define GL_POINT_SPRITE 0x8861
	#define GL_COORD_REPLACE 0x8862
	#define GL_MAX_TEXTURE_COORDS 0x8871
	
	inline void(*glBlendEquationSeparate) (GLenum modeRGB, GLenum modeAlpha) = nullptr;
	inline void(*glDrawBuffers) (GLsizei n, const GLenum *bufs) = nullptr;
	inline void(*glStencilOpSeparate) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) = nullptr;
	inline void(*glStencilFuncSeparate) (GLenum face, GLenum func, GLint ref, GLuint mask) = nullptr;
	inline void(*glStencilMaskSeparate) (GLenum face, GLuint mask) = nullptr;
	inline void(*glAttachShader) (GLuint program, GLuint shader) = nullptr;
	inline void(*glBindAttribLocation) (GLuint program, GLuint index, const GLchar *name) = nullptr;
	inline void(*glCompileShader) (GLuint shader) = nullptr;
	inline GLuint(*glCreateProgram) (void) = nullptr;
	inline GLuint(*glCreateShader) (GLenum type) = nullptr;
	inline void(*glDeleteProgram) (GLuint program) = nullptr;
	inline void(*glDeleteShader) (GLuint shader) = nullptr;
	inline void(*glDetachShader) (GLuint program, GLuint shader) = nullptr;
	inline void(*glDisableVertexAttribArray) (GLuint index) = nullptr;
	inline void(*glEnableVertexAttribArray) (GLuint index) = nullptr;
	inline void(*glGetActiveAttrib) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) = nullptr;
	inline void(*glGetActiveUniform) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) = nullptr;
	inline void(*glGetAttachedShaders) (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders) = nullptr;
	inline GLint(*glGetAttribLocation) (GLuint program, const GLchar *name) = nullptr;
	inline void(*glGetProgramiv) (GLuint program, GLenum pname, GLint *params) = nullptr;
	inline void(*glGetProgramInfoLog) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) = nullptr;
	inline void(*glGetShaderiv) (GLuint shader, GLenum pname, GLint *params) = nullptr;
	inline void(*glGetShaderInfoLog) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) = nullptr;
	inline void(*glGetShaderSource) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source) = nullptr;
	inline GLint(*glGetUniformLocation) (GLuint program, const GLchar *name) = nullptr;
	inline void(*glGetUniformfv) (GLuint program, GLint location, GLfloat *params) = nullptr;
	inline void(*glGetUniformiv) (GLuint program, GLint location, GLint *params) = nullptr;
	inline void(*glGetVertexAttribdv) (GLuint index, GLenum pname, GLdouble *params) = nullptr;
	inline void(*glGetVertexAttribfv) (GLuint index, GLenum pname, GLfloat *params) = nullptr;
	inline void(*glGetVertexAttribiv) (GLuint index, GLenum pname, GLint *params) = nullptr;
	inline void(*glGetVertexAttribPointerv) (GLuint index, GLenum pname, void **pointer) = nullptr;
	inline GLboolean(*glIsProgram) (GLuint program) = nullptr;
	inline GLboolean(*glIsShader) (GLuint shader) = nullptr;
	inline void(*glLinkProgram) (GLuint program) = nullptr;
	inline void(*glShaderSource) (GLuint shader, GLsizei count, const GLchar** string, const GLint *length) = nullptr;
	inline void(*glUseProgram) (GLuint program) = nullptr;
	inline void(*glUniform1f) (GLint location, GLfloat v0) = nullptr;
	inline void(*glUniform2f) (GLint location, GLfloat v0, GLfloat v1) = nullptr;
	inline void(*glUniform3f) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2) = nullptr;
	inline void(*glUniform4f) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) = nullptr;
	inline void(*glUniform1i) (GLint location, GLint v0) = nullptr;
	inline void(*glUniform2i) (GLint location, GLint v0, GLint v1) = nullptr;
	inline void(*glUniform3i) (GLint location, GLint v0, GLint v1, GLint v2) = nullptr;
	inline void(*glUniform4i) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3) = nullptr;
	inline void(*glUniform1fv) (GLint location, GLsizei count, const GLfloat *value) = nullptr;
	inline void(*glUniform2fv) (GLint location, GLsizei count, const GLfloat *value) = nullptr;
	inline void(*glUniform3fv) (GLint location, GLsizei count, const GLfloat *value) = nullptr;
	inline void(*glUniform4fv) (GLint location, GLsizei count, const GLfloat *value) = nullptr;
	inline void(*glUniform1iv) (GLint location, GLsizei count, const GLint *value) = nullptr;
	inline void(*glUniform2iv) (GLint location, GLsizei count, const GLint *value) = nullptr;
	inline void(*glUniform3iv) (GLint location, GLsizei count, const GLint *value) = nullptr;
	inline void(*glUniform4iv) (GLint location, GLsizei count, const GLint *value) = nullptr;
	inline void(*glUniformMatrix2fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	inline void(*glUniformMatrix3fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	inline void(*glUniformMatrix4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	inline void(*glValidateProgram) (GLuint program) = nullptr;
	inline void(*glVertexAttrib1d) (GLuint index, GLdouble x) = nullptr;
	inline void(*glVertexAttrib1dv) (GLuint index, const GLdouble *v) = nullptr;
	inline void(*glVertexAttrib1f) (GLuint index, GLfloat x) = nullptr;
	inline void(*glVertexAttrib1fv) (GLuint index, const GLfloat *v) = nullptr;
	inline void(*glVertexAttrib1s) (GLuint index, GLshort x) = nullptr;
	inline void(*glVertexAttrib1sv) (GLuint index, const GLshort *v) = nullptr;
	inline void(*glVertexAttrib2d) (GLuint index, GLdouble x, GLdouble y) = nullptr;
	inline void(*glVertexAttrib2dv) (GLuint index, const GLdouble *v) = nullptr;
	inline void(*glVertexAttrib2f) (GLuint index, GLfloat x, GLfloat y) = nullptr;
	inline void(*glVertexAttrib2fv) (GLuint index, const GLfloat *v) = nullptr;
	inline void(*glVertexAttrib2s) (GLuint index, GLshort x, GLshort y) = nullptr;
	inline void(*glVertexAttrib2sv) (GLuint index, const GLshort *v) = nullptr;
	inline void(*glVertexAttrib3d) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glVertexAttrib3dv) (GLuint index, const GLdouble *v) = nullptr;
	inline void(*glVertexAttrib3f) (GLuint index, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glVertexAttrib3fv) (GLuint index, const GLfloat *v) = nullptr;
	inline void(*glVertexAttrib3s) (GLuint index, GLshort x, GLshort y, GLshort z) = nullptr;
	inline void(*glVertexAttrib3sv) (GLuint index, const GLshort *v) = nullptr;
	inline void(*glVertexAttrib4Nbv) (GLuint index, const GLbyte *v) = nullptr;
	inline void(*glVertexAttrib4Niv) (GLuint index, const GLint *v) = nullptr;
	inline void(*glVertexAttrib4Nsv) (GLuint index, const GLshort *v) = nullptr;
	inline void(*glVertexAttrib4Nub) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) = nullptr;
	inline void(*glVertexAttrib4Nubv) (GLuint index, const GLubyte *v) = nullptr;
	inline void(*glVertexAttrib4Nuiv) (GLuint index, const GLuint *v) = nullptr;
	inline void(*glVertexAttrib4Nusv) (GLuint index, const GLushort *v) = nullptr;
	inline void(*glVertexAttrib4bv) (GLuint index, const GLbyte *v) = nullptr;
	inline void(*glVertexAttrib4d) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glVertexAttrib4dv) (GLuint index, const GLdouble *v) = nullptr;
	inline void(*glVertexAttrib4f) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glVertexAttrib4fv) (GLuint index, const GLfloat *v) = nullptr;
	inline void(*glVertexAttrib4iv) (GLuint index, const GLint *v) = nullptr;
	inline void(*glVertexAttrib4s) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
	inline void(*glVertexAttrib4sv) (GLuint index, const GLshort *v) = nullptr;
	inline void(*glVertexAttrib4ubv) (GLuint index, const GLubyte *v) = nullptr;
	inline void(*glVertexAttrib4uiv) (GLuint index, const GLuint *v) = nullptr;
	inline void(*glVertexAttrib4usv) (GLuint index, const GLushort *v) = nullptr;
	inline void(*glVertexAttribPointer) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) = nullptr;
	
	//*< load OpenGL 2.0 extensions
	inline void Load2_0Extensions()
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

	#define GL_PIXEL_PACK_BUFFER 0x88eb
	#define GL_PIXEL_UNPACK_BUFFER 0x88ec
	#define GL_PIXEL_PACK_BUFFER_BINDING 0x88ed
	#define GL_PIXEL_UNPACK_BUFFER_BINDING 0x88ef
	#define GL_FLOAT_MAT2x3 0x8b65
	#define GL_FLOAT_MAT2x4 0x8b66
	#define GL_FLOAT_MAT3x2 0x8b67
	#define GL_FLOAT_MAT3x4 0x8b68
	#define GL_FLOAT_MAT4x2 0x8b69
	#define GL_FLOAT_MAT4x3 0x8b6a
	#define GL_SRGB 0x8c40
	#define GL_SRGB8 0x8c41
	#define GL_SRGB_ALPHA 0x8c42
	#define GL_SRGB8_ALPHA8 0x8c43
	#define GL_COMPRESSED_SRGB 0x8c48
	#define GL_COMPRESSED_SRGB_ALPHA 0x8c49
	#define GL_CURRENT_RASTER_SECONDARY_COLOR 0x845f
	#define GL_SLUMINANCE_ALPHA 0x8c44
	#define GL_SLUMINANCE8_ALPHA8 0x8c45
	#define GL_SLUMINANCE 0x8c46
	#define GL_SLUMINANCE8 0x8c47
	#define GL_COMPRESSED_SLUMINANCE 0x8c4a
	#define GL_COMPRESSED_SLUMINANCE_ALPHA 0x8c4b

	inline void(*glUniformMatrix2x3fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	inline void(*glUniformMatrix3x2fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	inline void(*glUniformMatrix2x4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	inline void(*glUniformMatrix4x2fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	inline void(*glUniformMatrix3x4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	inline void(*glUniformMatrix4x3fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;

	//*< load OpenGL 2.1 extensions
	inline void Load2_1Extensions()
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

	// OpenGL 3.0 defines
	#define GL_CLIP_DISTANCE0 0x3000
	#define GL_CLIP_DISTANCE1 0x3001
	#define GL_CLIP_DISTANCE2 0x3002
	#define GL_CLIP_DISTANCE3 0x3003
	#define GL_CLIP_DISTANCE4 0x3004
	#define GL_CLIP_DISTANCE5 0x3005
	#define GL_COMPARE_REF_TO_TEXTURE 0x884E
	#define GL_MAX_CLIP_DISTANCES 0x0D32
	#define GL_MAX_VARYING_COMPONENTS GL_MAX_VARYING_FLOATS

	#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x0001
	#define GL_MAJOR_VERSION 0x821b
	#define GL_MINOR_VERSION 0x821c
	#define GL_NUM_EXTENSIONS 0x821d
	#define GL_CONTEXT_FLAGS 0x821e
	#define GL_DEPTH_BUFFER 0x8223
	#define GL_STENCIL_BUFFER 0x8224
	#define GL_RGBA32F 0x8814
	#define GL_RGB32F 0x8815
	#define GL_RGBA16F 0x881a
	#define GL_RGB16F 0x881b
	#define GL_VERTEX_ATTRIB_ARRAY_INTEGER 0x88fd
	#define GL_MAX_ARRAY_TEXTURE_LAYERS 0x88ff
	#define GL_MIN_PROGRAM_TEXEL_OFFSET 0x8904
	#define GL_MAX_PROGRAM_TEXEL_OFFSET 0x8905
	#define GL_CLAMP_VERTEX_COLOR 0x891a
	#define GL_CLAMP_FRAGMENT_COLOR 0x891b
	#define GL_CLAMP_READ_COLOR 0x891c
	#define GL_FIXED_ONLY 0x891d
	#define GL_TEXTURE_RED_TYPE 0x8c10
	#define GL_TEXTURE_GREEN_TYPE 0x8c11
	#define GL_TEXTURE_BLUE_TYPE 0x8c12
	#define GL_TEXTURE_ALPHA_TYPE 0x8c13
	#define GL_TEXTURE_LUMINANCE_TYPE 0x8c14
	#define GL_TEXTURE_INTENSITY_TYPE 0x8c15
	#define GL_TEXTURE_DEPTH_TYPE 0x8c16
	#define GL_TEXTURE_1D_ARRAY 0x8c18
	#define GL_PROXY_TEXTURE_1D_ARRAY 0x8c19
	#define GL_TEXTURE_2D_ARRAY 0x8c1a
	#define GL_PROXY_TEXTURE_2D_ARRAY 0x8c1b
	#define GL_TEXTURE_BINDING_1D_ARRAY 0x8c1c
	#define GL_TEXTURE_BINDING_2D_ARRAY 0x8c1d
	#define GL_R11F_G11F_B10F 0x8c3a
	#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8c3b
	#define GL_RGB9_E5 0x8c3d
	#define GL_UNSIGNED_INT_5_9_9_9_REV 0x8c3e
	#define GL_TEXTURE_SHARED_SIZE 0x8c3f
	#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8c76
	#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8c7f
	#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8c80
	#define GL_TRANSFORM_FEEDBACK_VARYINGS 0x8c83
	#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8c84
	#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8c85
	#define GL_PRIMITIVES_GENERATED 0x8c87
	#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8c88
	#define GL_RASTERIZER_DISCARD 0x8c89
	#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8c8a
	#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8c8b
	#define GL_INTERLEAVED_ATTRIBS 0x8c8c
	#define GL_SEPARATE_ATTRIBS 0x8c8d
	#define GL_TRANSFORM_FEEDBACK_BUFFER 0x8c8e
	#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8c8f
	#define GL_RGBA32UI 0x8d70
	#define GL_RGB32UI 0x8d71
	#define GL_RGBA16UI 0x8d76
	#define GL_RGB16UI 0x8d77
	#define GL_RGBA8UI 0x8d7c
	#define GL_RGB8UI 0x8d7d
	#define GL_RGBA32I 0x8d82
	#define GL_RGB32I 0x8d83
	#define GL_RGBA16I 0x8d88
	#define GL_RGB16I 0x8d89
	#define GL_RGBA8I 0x8d8e
	#define GL_RGB8I 0x8d8f
	#define GL_RED_INTEGER 0x8d94
	#define GL_GREEN_INTEGER 0x8d95
	#define GL_BLUE_INTEGER 0x8d96
	#define GL_ALPHA_INTEGER 0x8d97
	#define GL_RGB_INTEGER 0x8d98
	#define GL_RGBA_INTEGER 0x8d99
	#define GL_BGR_INTEGER 0x8d9a
	#define GL_BGRA_INTEGER 0x8d9b
	#define GL_SAMPLER_1D_ARRAY 0x8dc0
	#define GL_SAMPLER_2D_ARRAY 0x8dc1
	#define GL_SAMPLER_1D_ARRAY_SHADOW 0x8dc3
	#define GL_SAMPLER_2D_ARRAY_SHADOW 0x8dc4
	#define GL_SAMPLER_CUBE_SHADOW 0x8dc5
	#define GL_UNSIGNED_INT_VEC2 0x8dc6
	#define GL_UNSIGNED_INT_VEC3 0x8dc7
	#define GL_UNSIGNED_INT_VEC4 0x8dc8
	#define GL_INT_SAMPLER_1D 0x8dc9
	#define GL_INT_SAMPLER_2D 0x8dca
	#define GL_INT_SAMPLER_3D 0x8dcb
	#define GL_INT_SAMPLER_CUBE 0x8dcc
	#define GL_INT_SAMPLER_1D_ARRAY 0x8dce
	#define GL_INT_SAMPLER_2D_ARRAY 0x8dcf
	#define GL_UNSIGNED_INT_SAMPLER_1D 0x8dd1
	#define GL_UNSIGNED_INT_SAMPLER_2D 0x8dd2
	#define GL_UNSIGNED_INT_SAMPLER_3D 0x8dd3
	#define GL_UNSIGNED_INT_SAMPLER_CUBE 0x8dd4
	#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 0x8dd6
	#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 0x8dd7
	#define GL_QUERY_WAIT 0x8e13
	#define GL_QUERY_NO_WAIT 0x8e14
	#define GL_QUERY_BY_REGION_WAIT 0x8e15
	#define GL_QUERY_BY_REGION_NO_WAIT 0x8e16

	inline void (*glBeginConditionalRender) (GLuint id, GLenum mode);
	inline void (*glBeginTransformFeedback) (GLenum primitiveMode);
	inline void (*glBindFragDataLocation) (GLuint program, GLuint colorNumber, const GLchar* name);
	inline void (*glClampColor) (GLenum target, GLenum clamp);
	inline void (*glClearBufferfi) (GLenum buffer, GLint drawBuffer, GLfloat depth, GLint stencil);
	inline void (*glClearBufferfv) (GLenum buffer, GLint drawBuffer, const GLfloat* value);
	inline void (*glClearBufferiv) (GLenum buffer, GLint drawBuffer, const GLint* value);
	inline void (*glClearBufferuiv) (GLenum buffer, GLint drawBuffer, const GLuint* value);
	inline void (*glColorMaski) (GLuint buf, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	inline void (*glDisablei) (GLenum cap, GLuint index);
	inline void (*glEnablei) (GLenum cap, GLuint index);
	inline void (*glEndConditionalRender) (void);
	inline void (*glEndTransformFeedback) (void);
	inline void (*glGetBooleani_v) (GLenum pname, GLuint index, GLboolean* data);
	inline GLint(*glGetFragDataLocation) (GLuint program, const GLchar* name);
	inline const GLubyte* (*glGetStringi) (GLenum name, GLuint index);
	inline void (*glGetTexParameterIiv) (GLenum target, GLenum pname, GLint* params);
	inline void (*glGetTexParameterIuiv) (GLenum target, GLenum pname, GLuint* params);
	inline void (*glGetTransformFeedbackVarying) (GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);
	inline void (*glGetUniformuiv) (GLuint program, GLint location, GLuint* params);
	inline void (*glGetVertexAttribIiv) (GLuint index, GLenum pname, GLint* params);
	inline void (*glGetVertexAttribIuiv) (GLuint index, GLenum pname, GLuint* params);
	inline GLboolean(*glIsEnabledi) (GLenum cap, GLuint index);
	inline void (*glTexParameterIiv) (GLenum target, GLenum pname, const GLint* params);
	inline void (*glTexParameterIuiv) (GLenum target, GLenum pname, const GLuint* params);
	inline void (*glTransformFeedbackVaryings) (GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode);
	inline void (*glUniform1ui) (GLint location, GLuint v0);
	inline void (*glUniform1uiv) (GLint location, GLsizei count, const GLuint* value);
	inline void (*glUniform2ui) (GLint location, GLuint v0, GLuint v1);
	inline void (*glUniform2uiv) (GLint location, GLsizei count, const GLuint* value);
	inline void (*glUniform3ui) (GLint location, GLuint v0, GLuint v1, GLuint v2);
	inline void (*glUniform3uiv) (GLint location, GLsizei count, const GLuint* value);
	inline void (*glUniform4ui) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	inline void (*glUniform4uiv) (GLint location, GLsizei count, const GLuint* value);
	inline void (*glVertexAttribI1i) (GLuint index, GLint v0);
	inline void (*glVertexAttribI1iv) (GLuint index, const GLint* v0);
	inline void (*glVertexAttribI1ui) (GLuint index, GLuint v0);
	inline void (*glVertexAttribI1uiv) (GLuint index, const GLuint* v0);
	inline void (*glVertexAttribI2i) (GLuint index, GLint v0, GLint v1);
	inline void (*glVertexAttribI2iv) (GLuint index, const GLint* v0);
	inline void (*glVertexAttribI2ui) (GLuint index, GLuint v0, GLuint v1);
	inline void (*glVertexAttribI2uiv) (GLuint index, const GLuint* v0);
	inline void (*glVertexAttribI3i) (GLuint index, GLint v0, GLint v1, GLint v2);
	inline void (*glVertexAttribI3iv) (GLuint index, const GLint* v0);
	inline void (*glVertexAttribI3ui) (GLuint index, GLuint v0, GLuint v1, GLuint v2);
	inline void (*glVertexAttribI3uiv) (GLuint index, const GLuint* v0);
	inline void (*glVertexAttribI4bv) (GLuint index, const GLbyte* v0);
	inline void (*glVertexAttribI4i) (GLuint index, GLint v0, GLint v1, GLint v2, GLint v3);
	inline void (*glVertexAttribI4iv) (GLuint index, const GLint* v0);
	inline void (*glVertexAttribI4sv) (GLuint index, const GLshort* v0);
	inline void (*glVertexAttribI4ubv) (GLuint index, const GLubyte* v0);
	inline void (*glVertexAttribI4ui) (GLuint index, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	inline void (*glVertexAttribI4uiv) (GLuint index, const GLuint* v0);
	inline void (*glVertexAttribI4usv) (GLuint index, const GLushort* v0);
	inline void (*glVertexAttribIPointer) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);

	//*< load OpenGL 3.0 extensions
	inline void Load3_0Extensions()
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

	#define GL_TEXTURE_RECTANGLE 0x84f5
	#define GL_TEXTURE_BINDING_RECTANGLE 0x84f6
	#define GL_PROXY_TEXTURE_RECTANGLE 0x84f7
	#define GL_MAX_RECTANGLE_TEXTURE_SIZE 0x84f8
	#define GL_SAMPLER_2D_RECT 0x8b63
	#define GL_SAMPLER_2D_RECT_SHADOW 0x8b64
	#define GL_TEXTURE_BUFFER 0x8c2a
	#define GL_MAX_TEXTURE_BUFFER_SIZE 0x8c2b
	#define GL_TEXTURE_BINDING_BUFFER 0x8c2c
	#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8c2d
	#define GL_TEXTURE_BUFFER_FORMAT 0x8c2e
	#define GL_SAMPLER_BUFFER 0x8dc2
	#define GL_INT_SAMPLER_2D_RECT 0x8dcd
	#define GL_INT_SAMPLER_BUFFER 0x8dd0
	#define GL_UNSIGNED_INT_SAMPLER_2D_RECT 0x8dd5
	#define GL_UNSIGNED_INT_SAMPLER_BUFFER 0x8dd8
	#define GL_RED_SNORM 0x8f90
	#define GL_RG_SNORM 0x8f91
	#define GL_RGB_SNORM 0x8f92
	#define GL_RGBA_SNORM 0x8f93
	#define GL_R8_SNORM 0x8f94
	#define GL_RG8_SNORM 0x8f95
	#define GL_RGB8_SNORM 0x8f96
	#define GL_RGBA8_SNORM 0x8f97
	#define GL_R16_SNORM 0x8f98
	#define GL_RG16_SNORM 0x8f99
	#define GL_RGB16_SNORM 0x8f9a
	#define GL_RGBA16_SNORM 0x8f9b
	#define GL_SIGNED_NORMALIZED 0x8f9c
	#define GL_PRIMITIVE_RESTART 0x8f9d
	#define GL_PRIMITIVE_RESTART_INDEX 0x8f9e

	inline void(*glDrawArraysInstanced) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount) = nullptr;
	inline void(*glDrawElementsInstanced) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount) = nullptr;
	inline void(*glTexBuffer) (GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
	inline void(*glPrimitiveRestartIndex) (GLuint index) = nullptr;

	//*< load OpenGL 3.1 extensions
	inline void Load3_1Extensions()
	{
		FetchProcAddress(glDrawArraysInstanced, "glDrawArraysInstanced");
		FetchProcAddress(glDrawElementsInstanced, "glDrawElementsInstanced");
		FetchProcAddress(glTexBuffer, "glTexBuffer");
		FetchProcAddress(glPrimitiveRestartIndex, "glPrimitiveRestartIndex");
	}
	
#pragma endregion OpenGL3_1 Extensions

	//OpenGL 3.2 Extensions
#pragma region OpenGL3_2

	#define GL_CONTEXT_CORE_PROFILE_BIT 0x00000001
	#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
	#define GL_LINES_ADJACENCY 0x000a
	#define GL_LINE_STRIP_ADJACENCY 0x000b
	#define GL_TRIANGLES_ADJACENCY 0x000c
	#define GL_TRIANGLE_STRIP_ADJACENCY 0x000d
	#define GL_PROGRAM_POINT_SIZE 0x8642
	#define GL_GEOMETRY_VERTICES_OUT 0x8916
	#define GL_GEOMETRY_INPUT_TYPE 0x8917
	#define GL_GEOMETRY_OUTPUT_TYPE 0x8918
	#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8c29
	#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8da7
	#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8da8
	#define GL_GEOMETRY_SHADER 0x8dd9
	#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8ddf
	#define GL_MAX_GEOMETRY_OUTPUT_VERTICES 0x8de0
	#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8de1
	#define GL_MAX_VERTEX_OUTPUT_COMPONENTS 0x9122
	#define GL_MAX_GEOMETRY_INPUT_COMPONENTS 0x9123
	#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
	#define GL_MAX_FRAGMENT_INPUT_COMPONENTS 0x9125
	#define GL_CONTEXT_PROFILE_MASK 0x9126

	inline void(*glFramebufferTexture) (GLenum target, GLenum attachment, GLuint texture, GLint level) = nullptr;
	inline void(*glGetBufferParameteri64v) (GLenum target, GLenum pname, GLint64* params) = nullptr;
	inline void(*glGetInteger64i_v) (GLenum target, GLuint index, GLint64* data) = nullptr;

	//*< load OpenGL 3.2 extensions
	inline void Load3_2Extensions()
	{
		FetchProcAddress(glGetInteger64i_v, "glGetInteger64i_v");
		FetchProcAddress(glGetBufferParameteri64v, "glGetBufferParameteri64v");
		FetchProcAddress(glFramebufferTexture, "glFramebufferTexture");
	}

#pragma endregion OpenGL3_2 Extensions

	//OpenGL 3.3 Extensions
#pragma region OpenGL3_3
	
	#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR 0x88FE
	#define GL_RGB10_A2UI 0x906F

	inline void(*glVertexAttribDivisor) (GLuint index, GLuint divisor) = nullptr;

	//*< load OpenGL 3.3 extensions
	inline void Load3_3Extensions()
	{
		FetchProcAddress(glVertexAttribDivisor, "glVertexAttribDivisor");
	}
#pragma endregion OpenGL3_3 Extensions

	//OpenGL 4.0 Extensions
#pragma region OpenGL4_0

	#define GL_SAMPLE_SHADING 0x8c36
	#define GL_MIN_SAMPLE_SHADING_VALUE 0x8c37
	#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8e5e
	#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8e5f
	#define GL_MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS 0x8f9f
	#define GL_TEXTURE_CUBE_MAP_ARRAY 0x9009
	#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900a
	#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY 0x900b
	#define GL_SAMPLER_CUBE_MAP_ARRAY 0x900c
	#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 0x900d
	#define GL_INT_SAMPLER_CUBE_MAP_ARRAY 0x900e
	#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900f

	inline void(*glMinSampleShading) (GLfloat value) = nullptr;
	inline void(*glBlendEquationi) (GLuint buf, GLenum mode) = nullptr;
	inline void(*glBlendEquationSeparatei) (GLuint buf, GLenum modeRGB, GLenum modeAlpha) = nullptr;
	inline void(*glBlendFunci) (GLuint buf, GLenum src, GLenum dst) = nullptr;
	inline void(*glBlendFuncSeparatei) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = nullptr;

	//*< load OpenGL 4.0 extensions
	inline void Load4_0Extensions()
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
	inline void Load4_1Extensions()
	{

	}

#pragma endregion OpenGL4_1 Extensions

	//OpenGL 4.2 Extensions
#pragma region OpenGL4_2
	
	#define GL_TRANSFORM_FEEDBACK_PAUSED                0x8e23
	#define GL_TRANSFORM_FEEDBACK_ACTIVE                0x8e24
	#define GL_COMPRESSED_RGBA_BPTC_UNORM               0x8e8c
	#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM         0x8e8d
	#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT         0x8e8e
	#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT       0x8e8f
	#define GL_COPY_READ_BUFFER_BINDING                 0x8f36
	#define GL_COPY_WRITE_BUFFER_BINDING                0x8f37

	//*< load OpenGL 4.2 extensions
	inline void Load4_2Extensions()
	{

	}

#pragma endregion OpenGL4_2 Extensions

	//OpenGL 4.3 Extensions
#pragma region OpenGL4_3
	#define GL_NUM_SHADING_LANGUAGE_VERSIONS 0x82e9
	#define GL_VERTEX_ATTRIB_ARRAY_LONG 0x874e

	//*< load OpenGL 4.3 extensions
	inline void Load4_3Extensions()
	{

	}

#pragma endregion OpenGL4_3 Extensions

	//OpenGL 4.4 Extensions
#pragma region OpenGL4_4
	#define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
	#define GL_MAX_VERTEX_ATTRIB_STRIDE 0x82e5
	#define GL_TEXTURE_BUFFER_BINDING 0x8c2a

	//*< load OpenGL 4.4 extensions
	inline void Load4_4Extensions()
	{

	}

#pragma endregion OpenGL4_4 Extensions

	//OpenGL 4.5 Extensions
#pragma region OpenGL4_5
	inline GLenum(*glGetGraphicsResetStatus) (void) = nullptr;
	inline void(*glGetnCompressedTexImage) (GLenum target, GLint lod, GLsizei bufSize, GLvoid* pixels) = nullptr;
	inline void(*glGetnTexImage) (GLenum tex, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid* pixels) = nullptr;
	inline void(*glGetnUniformdv) (GLuint program, GLint location, GLsizei bufSize, GLdouble* params) = nullptr;

	//*< load OpenGL 4.5 extensions
	inline void Load4_5Extensions()
	{
		FetchProcAddress(glGetGraphicsResetStatus, "glGetGraphicsResetStatus");
		FetchProcAddress(glGetnCompressedTexImage, "glGetnCompressedTexImage");
		FetchProcAddress(glGetnTexImage, "glGetnTexImage");
		FetchProcAddress(glGetnUniformdv, "glGetnUniformdv");
	}

	// OpenGL 4.5 defines
	#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 0x00000004

#pragma endregion OpenGL4_5 Extensions
	
	//OpenGL 4.6? Extensions
#pragma region OpenGL4_6

	#define GL_CONTEXT_FLAG_NO_ERROR_BIT 0x00000008
	#define GL_PARAMETER_BUFFER 0x80ee
	#define GL_PARAMETER_BUFFER_BINDING 0x80ef
	#define GL_TRANSFORM_FEEDBACK_OVERFLOW 0x82ec
	#define GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW 0x82ed
	#define GL_VERTICES_SUBMITTED 0x82ee
	#define GL_PRIMITIVES_SUBMITTED 0x82ef
	#define GL_VERTEX_SHADER_INVOCATIONS 0x82f0
	#define GL_TESS_CONTROL_SHADER_PATCHES 0x82f1
	#define GL_TESS_EVALUATION_SHADER_INVOCATIONS 0x82f2
	#define GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED 0x82f3
	#define GL_FRAGMENT_SHADER_INVOCATIONS 0x82f4
	#define GL_COMPUTE_SHADER_INVOCATIONS 0x82f5
	#define GL_CLIPPING_INPUT_PRIMITIVES 0x82f6
	#define GL_CLIPPING_OUTPUT_PRIMITIVES 0x82f7
	#define GL_TEXTURE_MAX_ANISOTROPY 0x84fe
	#define GL_MAX_TEXTURE_MAX_ANISOTROPY 0x84ff
	#define GL_POLYGON_OFFSET_CLAMP 0x8e1b
	#define GL_SHADER_BINARY_FORMAT_SPIR_V 0x9551
	#define GL_SPIR_V_BINARY 0x9552
	#define GL_SPIR_V_EXTENSIONS 0x9553
	#define GL_NUM_SPIR_V_EXTENSIONS 0x9554

	inline GLenum(*glMultiDrawArraysIndirectCount) (GLenum mode, const GLvoid* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) = nullptr;
	inline GLenum(*glMultiDrawElementsIndirectCount) (GLenum mode, GLenum type, const GLvoid* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) = nullptr;
	inline GLenum(*glSpecializeShader) (GLuint shader, const GLchar* pEntryPoint, GLuint numSpecializationConstants, const GLuint* pConstantIndex, const GLuint* pConstantValue) = nullptr;

	//*< load OpenGL 4.6 extensions
	inline void Load4_6Extensions()
	{
		FetchProcAddress(glMultiDrawArraysIndirectCount, "glMultiDrawArraysIndirectCount");
		FetchProcAddress(glMultiDrawElementsIndirectCount, "glMultiDrawElementsIndirectCount");
		FetchProcAddress(glSpecializeShader, "glSpecializeShader");
	}

#pragma endregion OpenGL4_6 Extensions

	//OpenGL 3DFX Extensions
#pragma region 3DFX

	// 3DFX extension defines
	#define GL_MULTISAMPLE_3DFX           0x86b2
	#define GL_SAMPLE_BUFFERS_3DFX        0x86b3
	#define GL_SAMPLES_3DFX               0x86b4
	#define GL_MULTISAMPLE_BIT_3DFX       0x20000000
	#define GL_COMPRESSED_RGB_FXT1_3DFX   0x86b0
	#define GL_COMPRESSED_RGBA_FXT1_3DFX  0x86b1

	//multisample
#define multisample_3DFX 1

	//tbuffer
#define tbuffer_3DFX 1
	inline void (*glTbufferMask3DFX) (GLuint mask) = nullptr;

	//texture compression FXT1
#define texture_compression_FXT1_3DFX 1

	//*< load OpenGL 3DFX Extensions
	inline void Load3DFXExtensions()
	{
		//tbuffer
		FetchProcAddress(glTbufferMask3DFX, "glTbufferMask3DFX");
	}

#pragma endregion 3DFX Extensions

	//OpenGL AMD Extensions
#pragma region AMD

		//blend minmax factor,
		#define GL_FACTOR_MIN_AMD 0x901c
		#define GL_FACTOR_MAX_AMD 0x901d

		//compressed 3dc texture,
		#define GL_3DC_X_AMD 0x87f9
		#define GL_3DC_XY_AMD 0x87fa

		//compressed atc texture,
		#define GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87ee
		#define GL_ATC_RGB_AMD 0x8c92
		#define GL_ATC_RGBA_EXPLICIT_ALPHA_AMD 0x8c93

		//debug output,
		#define GL_MAX_DEBUG_MESSAGE_LENGTH_AMD 0x9143
		#define GL_MAX_DEBUG_LOGGED_MESSAGES_AMD 0x9144
		#define GL_DEBUG_LOGGED_MESSAGES_AMD 0x9145
		#define GL_DEBUG_SEVERITY_HIGH_AMD 0x9146
		#define GL_DEBUG_SEVERITY_MEDIUM_AMD 0x9147
		#define GL_DEBUG_SEVERITY_LOW_AMD 0x9148
		#define GL_DEBUG_CATEGORY_API_ERROR_AMD 0x9149
		#define GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD 0x914a
		#define GL_DEBUG_CATEGORY_DEPRECATION_AMD 0x914b
		#define GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD 0x914c
		#define GL_DEBUG_CATEGORY_PERFORMANCE_AMD 0x914d
		#define GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD 0x914e
		#define GL_DEBUG_CATEGORY_APPLICATION_AMD 0x914f
		#define GL_DEBUG_CATEGORY_OTHER_AMD 0x9150

		//depth clamp separate,
		#define GL_DEPTH_CLAMP_NEAR_AMD 0x901e
		#define GL_DEPTH_CLAMP_FAR_AMD  0x901f

		//framebuffer sample positions,
		#define GL_SUBSAMPLE_DISTANCE_AMD 0x883f
		#define GL_PIXELS_PER_SAMPLE_PATTERN_X_AMD 0x91ae
		#define GL_PIXELS_PER_SAMPLE_PATTERN_Y_AMD 0x91af
		#define GL_ALL_PIXELS_AMD 0xffffffff

		//gpu shader half float,
		#define GL_FLOAT16_NV 0x8ff8
		#define GL_FLOAT16_VEC2_NV 0x8ff9
		#define GL_FLOAT16_VEC3_NV 0x8ffa
		#define GL_FLOAT16_VEC4_NV 0x8ffb
		#define GL_FLOAT16_MAT2_AMD 0x91c5
		#define GL_FLOAT16_MAT3_AMD 0x91c6
		#define GL_FLOAT16_MAT4_AMD 0x91c7
		#define GL_FLOAT16_MAT2X3_AMD 0x91c8
		#define GL_FLOAT16_MAT2X4_AMD 0x91c9
		#define GL_FLOAT16_MAT3X2_AMD 0x91ca
		#define GL_FLOAT16_MAT3X4_AMD 0x91cb
		#define GL_FLOAT16_MAT4X2_AMD 0x91cc
		#define GL_FLOAT16_MAT4X3_AMD 0x91cd

		//interleaved elements,
		#define GL_RED_AMD 0x1903
		#define GL_GREEN_AMD 0x1904
		#define GL_BLUE_AMD 0x1905
		#define GL_ALPHA_AMD 0x1906
		#define GL_RG8UI_AMD 0x8238
		#define GL_RG16UI_AMD 0x823a
		#define GL_RGBA8UI_AMD 0x8d7c
		#define GL_VERTEX_ELEMENT_SWIZZLE_AMD 0x91a4
		#define GL_VERTEX_ID_SWIZZLE_AMD 0x91a5

		//name gen delete,
		#define GL_DATA_BUFFER_AMD 0x9151
		#define GL_PERFORMANCE_MONITOR_AMD 0x9152
		#define GL_QUERY_OBJECT_AMD 0x9153
		#define GL_VERTEX_ARRAY_OBJECT_AMD 0x9154
		#define GL_SAMPLER_OBJECT_AMD 0x9155

		//occlusion query event,
		#define GL_QUERY_DEPTH_PASS_EVENT_BIT_AMD        0x00000001
		#define GL_QUERY_DEPTH_FAIL_EVENT_BIT_AMD        0x00000002
		#define GL_QUERY_STENCIL_FAIL_EVENT_BIT_AMD      0x00000004
		#define GL_QUERY_DEPTH_BOUNDS_FAIL_EVENT_BIT_AMD 0x00000008
		#define GL_OCCLUSION_QUERY_EVENT_MASK_AMD        0x874f
		#define GL_QUERY_ALL_EVENT_BITS_AMD              0xffffffff

		//performance monitor,
		#define GL_COUNTER_TYPE_AMD 0x8bc0
		#define GL_COUNTER_RANGE_AMD 0x8bc1
		#define GL_UNSIGNED_INT64_AMD 0x8bc2
		#define GL_PERCENTAGE_AMD 0x8bc3
		#define GL_PERFMON_RESULT_AVAILABLE_AMD 0x8bc4
		#define GL_PERFMON_RESULT_SIZE_AMD 0x8bc5
		#define GL_PERFMON_RESULT_AMD 0x8bc6

		//pinned memory,
		#define GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD 0x9160

		//program binary z400,
		#define GL_Z400_BINARY_AMD 0x8740

		//query buffer object,
		#define GL_QUERY_BUFFER_AMD 0x9192
		#define GL_QUERY_BUFFER_BINDING_AMD 0x9193
		#define GL_QUERY_RESULT_NO_WAIT_AMD 0x9194

		//seamless cubemap per texture,
		#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884f

		//sparse texture,
		#define GL_TEXTURE_STORAGE_SPARSE_BIT_AMD 0x00000001
		#define GL_VIRTUAL_PAGE_SIZE_X_AMD 0x9195
		#define GL_VIRTUAL_PAGE_SIZE_Y_AMD 0x9196
		#define GL_VIRTUAL_PAGE_SIZE_Z_AMD 0x9197
		#define GL_MAX_SPARSE_TEXTURE_SIZE_AMD 0x9198
		#define GL_MAX_SPARSE_3D_TEXTURE_SIZE_AMD 0x9199
		#define GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_AMD 0x919a
		#define GL_MIN_SPARSE_LEVEL_AMD 0x919b
		#define GL_MIN_LOD_WARNING_AMD 0x919c

		//stencil operation extended,
		#define GL_SET_AMD 0x874a
		#define GL_REPLACE_VALUE_AMD 0x874b
		#define GL_STENCIL_OP_VALUE_AMD 0x874c
		#define GL_STENCIL_BACK_OP_VALUE_AMD 0x874d

		//transform feedback,
		#define GL_STREAM_RASTERIZATION_AMD 0x91a0

		//vertex shader tesselator,
		#define GL_SAMPLER_BUFFER_AMD 0x9001
		#define GL_INT_SAMPLER_BUFFER_AMD 0x9002
		#define GL_UNSIGNED_INT_SAMPLER_BUFFER_AMD 0x9003
		#define GL_TESSELLATION_MODE_AMD 0x9004
		#define GL_TESSELLATION_FACTOR_AMD 0x9005
		#define GL_DISCRETE_AMD 0x9006
		#define GL_CONTINUOUS_AMD 0x9007

	//blend minmax factor
#define AMD_blend_minmax_factor 1

	//compressed 3DC texture
#define AMD_compressed_3DC_texture 1

	//compressed ATC texture
#define AMD_compressed_ATC_texture 1

	//conservative depth
#define AMD_conservative_depth 1

	//debug output
#define AMD_debug_output 1
	typedef void (*GLDEBUGPROCAMD)(GLuint id, GLenum category, GLenum severity, GLsizei length, const GLchar* message, void* userParam);
	inline void (*glDebugMessageCallbackAMD) (GLDEBUGPROCAMD callback, void* userParam) = nullptr;
	inline void (*glDebugMessageEnableAMD) (GLenum category, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled) = nullptr;
	inline void (*glDebugMessageInsertAMD) (GLenum category, GLenum severity, GLuint id, GLsizei length, const GLchar* buf) = nullptr;
	inline GLuint (*glGetDebugMessageLogAMD) (GLuint count, GLsizei bufsize, GLenum* categories, GLuint* severities, GLuint* ids, GLsizei* lengths, GLchar* message) = nullptr;

	//depth clamp separate
#define AMD_depth_clamp_separate 1

	//draw buffers blend
#define AMD_draw_buffers_blend 1
	inline void (*glBlendEquationIndexedAMD) (GLuint buf, GLenum mode) = nullptr;
	inline void (*glBlendEquationSeparateIndexedAMD) (GLuint buf, GLenum modeRGB, GLenum modeAlpha) = nullptr;
	inline void (*glBlendFuncIndexedAMD) (GLuint buf, GLenum src, GLenum dst) = nullptr;
	inline void (*glBlendFuncSeparateIndexedAMD) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = nullptr;

	//framebuffer sample positions
#define AMD_framebuffer_sample_positions 1
	inline void (*glFramebufferSamplePositionsfvAMD) (GLenum target, GLuint numsamples, GLuint pixelindex, const GLfloat* values) = nullptr;
	inline void (*glGetFramebufferParameterfvAMD) (GLenum target, GLenum pname, GLuint numsamples, GLuint pixelindex, GLsizei size, GLfloat* values) = nullptr;
	inline void (*glGetNamedFramebufferParameterfvAMD) (GLuint framebuffer, GLenum pname, GLuint numsamples, GLuint pixelindex, GLsizei size, GLfloat* values) = nullptr;
	inline void (*glNamedFramebufferSamplePositionsfvAMD) (GLuint framebuffer, GLuint numsamples, GLuint pixelindex, const GLfloat* values) = nullptr;

	//gcn shader
#define AMD_gcn_shader 1

	//gpu shader half float
#define AMD_gpu_shader_half_float 1

	//gpu shader int16
#define AMD_gpu_shader_int16 1

	//gpu shader int64
#define AMD_gpu_shader_int64 1

	//interleaved elements
#define AMD_interleaved_elements 1
	inline void (*glVertexAttribParameteriAMD) (GLuint index, GLenum pname, GLint param) = nullptr;

	//multi draw indirect
#define AMD_multi_draw_indirect 1
	inline void (*glMultiDrawArraysIndirectAMD) (GLenum mode, const void* indirect, GLsizei primcount, GLsizei stride) = nullptr;
	inline void (*glMultiDrawElementsIndirectAMD) (GLenum mode, GLenum type, const void* indirect, GLsizei primcount, GLsizei stride) = nullptr;

	//name gen delete
#define AMD_name_gen_delete 1
	inline void (*glDeleteNamesAMD) (GLenum identifier, GLuint num, const GLuint* names) = nullptr;
	inline void (*glGenNamesAMD) (GLenum identifier, GLuint num, GLuint* names) = nullptr;
	inline GLboolean(*glIsNameAMD) (GLenum identifier, GLuint name) = nullptr;

	//occlusion query event
#define AMD_occlusion_query_event 1
	inline void (*glQueryObjectParameteruiAMD) (GLenum target, GLuint id, GLenum pname, GLuint param) = nullptr;

	//performance monitor
#define AMD_performance_monitor 1
	inline void (*glBeginPerfMonitorAMD) (GLuint monitor) = nullptr;
	inline void (*glDeletePerfMonitorsAMD) (GLsizei n, GLuint* monitors) = nullptr;
	inline void (*glEndPerfMonitorAMD) (GLuint monitor) = nullptr;
	inline void (*glGenPerfMonitorsAMD) (GLsizei n, GLuint* monitors) = nullptr;
	inline void (*glGetPerfMonitorCounterDataAMD) (GLuint monitor, GLenum pname, GLsizei dataSize, GLuint* data, GLint* bytesWritten) = nullptr;
	inline void (*glGetPerfMonitorCounterInfoAMD) (GLuint group, GLuint counter, GLenum pname, void* data) = nullptr;
	inline void (*glGetPerfMonitorCounterStringAMD) (GLuint group, GLuint counter, GLsizei bufSize, GLsizei* length, GLchar* counterString) = nullptr;
	inline void (*glGetPerfMonitorCountersAMD) (GLuint group, GLint* numCounters, GLint* maxActiveCounters, GLsizei countersSize, GLuint* counters) = nullptr;
	inline void (*glGetPerfMonitorGroupStringAMD) (GLuint group, GLsizei bufSize, GLsizei* length, GLchar* groupString) = nullptr;
	inline void (*glGetPerfMonitorGroupsAMD) (GLint* numGroups, GLsizei groupsSize, GLuint* groups) = nullptr;
	inline void (*glSelectPerfMonitorCountersAMD) (GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint* counterList) = nullptr;

	//pinned memory
#define AMD_pinned_memory 1

	//program binary Z400
#define AMD_program_binary_Z400 1

	//query buffer object
#define AMD_query_buffer_object 1

	//sample positions
#define AMD_sample_positions 1
	inline void (*glSetMultisamplefvAMD) (GLenum pname, GLuint index, const GLfloat* val) = nullptr;

	//seamless cubemap per texture
#define AMD_seamless_cubemap_per_texture 1

	//shader atomic counter ops
#define AMD_shader_atomic_counter_ops 1

	//shader ballot
#define AMD_shader_ballot 1

	//shader explicit vertex parameter
#define AMD_shader_explicit_vertex_parameter 1

	//shader stencil export
#define AMD_shader_stencil_export 1

	//shader stencil value export
#define AMD_shader_stencil_value_export 1

	//shader trinary minmax
#define AMD_shader_trinary_minmax 1

	//sparse texture
#define AMD_sparse_texture 1
	inline void (*glTexStorageSparseAMD) (GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags) = nullptr;
	inline void (*glTextureStorageSparseAMD) (GLuint texture, GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags) = nullptr;

	//stencil operation extended
#define AMD_stencil_operation_extended 1
	inline void (*glStencilOpValueAMD) (GLenum face, GLuint value) = nullptr;

	//texture gather bias lod
#define AMD_texture_gather_bias_lod 1

	//texture texture4
#define AMD_texture_texture4 1

	//transform feedback3 lines triangles
#define AMD_transform_feedback3_lines_triangles 1

	//transform feedback4
#define AMD_transform_feedback4 1

	//vertex shader layer
#define AMD_vertex_shader_layer 1

	//vertex shader tessellator
#define AMD_vertex_shader_tessellator 1
	inline void (*glTessellationFactorAMD) (GLfloat factor) = nullptr;
	inline void (*glTessellationModeAMD) (GLenum mode) = nullptr;

	//vertex shader viewport index
#define AMD_vertex_shader_viewport_index 1

	//*< load OpenGL AMD Extensions
	inline void LoadAMDExtensions()
	{
		//debug output
		FetchProcAddress(glDebugMessageCallbackAMD, "glDebugMessageCallbackAMD");
		FetchProcAddress(glDebugMessageEnableAMD, "glDebugMessageEnableAMD");
		FetchProcAddress(glDebugMessageInsertAMD, "glDebugMessageInsertAMD");
		FetchProcAddress(glGetDebugMessageLogAMD, "glGetDebugMessageLogAMD");

		//draw buffers blend
		FetchProcAddress(glBlendEquationIndexedAMD, "glBlendEquationIndexedAMD");
		FetchProcAddress(glBlendEquationSeparateIndexedAMD, "glBlendEquationSeparateIndexedAMD");
		FetchProcAddress(glBlendFuncIndexedAMD, "glBlendFuncIndexedAMD");
		FetchProcAddress(glBlendFuncSeparateIndexedAMD, "glBlendFuncSeparateIndexedAMD");

		//framebuffer sample positions
		FetchProcAddress(glFramebufferSamplePositionsfvAMD, "glFramebufferSamplePositionsfvAMD");
		FetchProcAddress(glGetFramebufferParameterfvAMD, "glGetFramebufferParameterfvAMD");
		FetchProcAddress(glGetNamedFramebufferParameterfvAMD, "glGetNamedFramebufferParameterfvAMD");
		FetchProcAddress(glNamedFramebufferSamplePositionsfvAMD, "glNamedFramebufferSamplePositionsfvAMD");

		//interleaved elements
		FetchProcAddress(glVertexAttribParameteriAMD, "glVertexAttribParameteriAMD");

		//multi draw indirect
		FetchProcAddress(glMultiDrawArraysIndirectAMD, "glMultiDrawArraysIndirectAMD");
		FetchProcAddress(glMultiDrawElementsIndirectAMD, "glMultiDrawElementsIndirectAMD");

		//name gen delete
		FetchProcAddress(glDeleteNamesAMD, "glDeleteNamesAMD");
		FetchProcAddress(glGenNamesAMD, "glGenNamesAMD");
		FetchProcAddress(glIsNameAMD, "glIsNameAMD");

		//occlusion query event
		FetchProcAddress(glQueryObjectParameteruiAMD, "glQueryObjectParameteruiAMD");

		//performance monitor
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

		//sample positions
		FetchProcAddress(glSetMultisamplefvAMD, "glSetMultisamplefvAMD");

		//sparse texture
		FetchProcAddress(glTexStorageSparseAMD, "glTexStorageSparseAMD");
		FetchProcAddress(glTextureStorageSparseAMD, "glTextureStorageSparseAMD");

		//stencil operation extended
		FetchProcAddress(glStencilOpValueAMD, "glStencilOpValueAMD");

		//vertex shader tessellator
		FetchProcAddress(glTessellationFactorAMD, "glTessellationFactorAMD");
		FetchProcAddress(glTessellationModeAMD, "glTessellationModeAMD");
	}

#pragma endregion AMD Extensions

	//OpenGL Android Extensions
#pragma region Android
	//ANDROID_extension_pack_es31a
#define ANDROID_extension_pack_es31a 1

	//*< load Android Extensions
	inline void LoadAndroidExtensions()
	{

	}
#pragma endregion Android Extensions

	//OpenGL Angle Extensions
#pragma region Angle

		//framebuffer blit
		#define GL_DRAW_FRAMEBUFFER_BINDING_ANGLE 0x8ca6
		#define GL_READ_FRAMEBUFFER_ANGLE 0x8ca8
		#define GL_DRAW_FRAMEBUFFER_ANGLE 0x8ca9
		#define GL_READ_FRAMEBUFFER_BINDING_ANGLE 0x8caa

		//framebuffer multisample
		#define GL_RENDERBUFFER_SAMPLES_ANGLE 0x8cab
		#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE 0x8d56
		#define GL_MAX_SAMPLES_ANGLE 0x8d57

		//instanced arrays
		#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ANGLE 0x88fe

		//pack reverse row order
		#define GL_PACK_REVERSE_ROW_ORDER_ANGLE 0x93a4

		//program binary
		#define GL_PROGRAM_BINARY_ANGLE 0x93a6

		//texture compression
		#define GL_COMPRESSED_RGB_S3TC_DXT1_ANGLE 0x83f0
		#define GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE 0x83f1
		#define GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE 0x83f2
		#define GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE 0x83f3

		//texture usage
		#define GL_TEXTURE_USAGE_ANGLE 0x93a2
		#define GL_FRAMEBUFFER_ATTACHMENT_ANGLE 0x93a3

		//timer query
		#define GL_QUERY_COUNTER_BITS_ANGLE 0x8864
		#define GL_CURRENT_QUERY_ANGLE 0x8865
		#define GL_QUERY_RESULT_ANGLE 0x8866
		#define GL_QUERY_RESULT_AVAILABLE_ANGLE 0x8867
		#define GL_TIME_ELAPSED_ANGLE 0x88bf
		#define GL_TIMESTAMP_ANGLE 0x8e28

		//translated shader source
		#define GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE 0x93a0

	//depth texture
#define ANGLE_depth_texture 1

	//framebuffer blit
#define ANGLE_framebuffer_blit 1
	inline void (*glBlitFramebufferANGLE) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;

	//framebuffer multisample
#define ANGLE_framebuffer_multisample 1
	inline void (*glRenderbufferStorageMultisampleANGLE) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;

	//instanced arrays
#define ANGLE_instanced_arrays 1
	inline void (*glDrawArraysInstancedANGLE) (GLenum mode, GLint first, GLsizei count, GLsizei primcount) = nullptr;
	inline void (*glDrawElementsInstancedANGLE) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) = nullptr;
	inline void (*glVertexAttribDivisorANGLE) (GLuint index, GLuint divisor) = nullptr;

	//pack reverse row order
#define ANGLE_pack_reverse_row_order 1

	//program binary
#define ANGLE_program_binary 1

	//texture compression dxt1
#define ANGLE_texture_compression_dxt1 1

	//texture compression dxt3
#define ANGLE_texture_compression_dxt3 1

	//texture compression dxt5
#define ANGLE_texture_compression_dxt5 1

	//texture usage
#define ANGLE_texture_usage 1

	//timer query
#define ANGLE_timer_query 1
	inline void (*glBeginQueryANGLE) (GLenum target, GLuint id) = nullptr;
	inline void (*glDeleteQueriesANGLE) (GLsizei n, const GLuint* ids) = nullptr;
	inline void (*glEndQueryANGLE) (GLenum target) = nullptr;
	inline void (*glGenQueriesANGLE) (GLsizei n, GLuint* ids) = nullptr;
	inline void (*glGetQueryObjecti64vANGLE) (GLuint id, GLenum pname, GLint64* params) = nullptr;
	inline void (*glGetQueryObjectivANGLE) (GLuint id, GLenum pname, GLint* params) = nullptr;
	inline void (*glGetQueryObjectui64vANGLE) (GLuint id, GLenum pname, GLuint64* params) = nullptr;
	inline void (*glGetQueryObjectuivANGLE) (GLuint id, GLenum pname, GLuint* params) = nullptr;
	inline void (*glGetQueryivANGLE) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsQueryANGLE) (GLuint id) = nullptr;
	inline void (*glQueryCounterANGLE) (GLuint id, GLenum target) = nullptr;

	//translated shader source
#define ANGLE_translated_shader_source 1
	inline void (*glGetTranslatedShaderSourceANGLE) (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source) = nullptr;

	//*< load Angle Extensions
	inline void LoadAngleExtensions()
	{
		//framebuffer blit
		FetchProcAddress(glBlitFramebufferANGLE, "glBlitFramebufferANGLE");

		//framebuffer multisample
		FetchProcAddress(glRenderbufferStorageMultisampleANGLE, "glRenderbufferStorageMultisampleANGLE");

		//instanced arrays
		FetchProcAddress(glDrawArraysInstancedANGLE, "glDrawArraysInstancedANGLE");
		FetchProcAddress(glDrawElementsInstancedANGLE, "glDrawElementsInstancedANGLE");
		FetchProcAddress(glVertexAttribDivisorANGLE, "glVertexAttribDivisorANGLE");

		//timer query
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
		FetchProcAddress(glGetTranslatedShaderSourceANGLE, "glGetTranslatedShaderSourceANGLE");
	}

#pragma endregion Angle Extensions

	//OpenGL Apple Extensions
#pragma region Apple

		//aux depth stencil
		#define GL_AUX_DEPTH_STENCIL_APPLE 0x8A14

		//client storage,
		#define GL_UNPACK_CLIENT_STORAGE_APPLE 0x85b2

		//clip distance,
		#define GL_MAX_CLIP_DISTANCES_APPLE 0x0d32
		#define GL_CLIP_DISTANCE0_APPLE 0x3000
		#define GL_CLIP_DISTANCE1_APPLE 0x3001
		#define GL_CLIP_DISTANCE2_APPLE 0x3002
		#define GL_CLIP_DISTANCE3_APPLE 0x3003
		#define GL_CLIP_DISTANCE4_APPLE 0x3004
		#define GL_CLIP_DISTANCE5_APPLE 0x3005
		#define GL_CLIP_DISTANCE6_APPLE 0x3006
		#define GL_CLIP_DISTANCE7_APPLE 0x3007

		//element array,
		#define GL_ELEMENT_ARRAY_APPLE 0x8a0c
		#define GL_ELEMENT_ARRAY_TYPE_APPLE 0x8a0d
		#define GL_ELEMENT_ARRAY_POINTER_APPLE 0x8a0e

		//fence,
		#define GL_DRAW_PIXELS_APPLE 0x8a0a
		#define GL_FENCE_APPLE 0x8a0b

		//float pixels,
		#define GL_HALF_APPLE 0x140b
		#define GL_RGBA_FLOAT32_APPLE 0x8814
		#define GL_RGB_FLOAT32_APPLE 0x8815
		#define GL_ALPHA_FLOAT32_APPLE 0x8816
		#define GL_INTENSITY_FLOAT32_APPLE 0x8817
		#define GL_LUMINANCE_FLOAT32_APPLE 0x8818
		#define GL_LUMINANCE_ALPHA_FLOAT32_APPLE 0x8819
		#define GL_RGBA_FLOAT16_APPLE 0x881a
		#define GL_RGB_FLOAT16_APPLE 0x881b
		#define GL_ALPHA_FLOAT16_APPLE 0x881c
		#define GL_INTENSITY_FLOAT16_APPLE 0x881d
		#define GL_LUMINANCE_FLOAT16_APPLE 0x881e
		#define GL_LUMINANCE_ALPHA_FLOAT16_APPLE 0x881f
		#define GL_COLOR_FLOAT_APPLE 0x8a0f

		//flush buffer range,
		#define GL_BUFFER_SERIALIZED_MODIFY_APPLE 0x8a12
		#define GL_BUFFER_FLUSHING_UNMAP_APPLE 0x8a13

		//framebuffer multisample,
		#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8ca6
		#define GL_READ_FRAMEBUFFER_APPLE 0x8ca8
		#define GL_DRAW_FRAMEBUFFER_APPLE 0x8ca9
		#define GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8caa
		#define GL_RENDERBUFFER_SAMPLES_APPLE 0x8cab
		#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8d56
		#define GL_MAX_SAMPLES_APPLE 0x8d57

		//object purgeable,
		#define GL_BUFFER_OBJECT_APPLE 0x85b3
		#define GL_RELEASED_APPLE 0x8a19
		#define GL_VOLATILE_APPLE 0x8a1a
		#define GL_RETAINED_APPLE 0x8a1b
		#define GL_UNDEFINED_APPLE 0x8a1c
		#define GL_PURGEABLE_APPLE 0x8a1d

		//pixel buffer,
		#define GL_MIN_PBUFFER_VIEWPORT_DIMS_APPLE 0x8a10

		//rgb 422,
		#define GL_UNSIGNED_SHORT_8_8_APPLE 0x85ba
		#define GL_UNSIGNED_SHORT_8_8_REV_APPLE 0x85bb
		#define GL_RGB_422_APPLE 0x8a1f
		#define GL_RGB_RAW_422_APPLE 0x8a51

		//row bytes,
		#define GL_PACK_ROW_BYTES_APPLE 0x8a15
		#define GL_UNPACK_ROW_BYTES_APPLE 0x8a16

		//specular vector,
		#define GL_LIGHT_MODEL_SPECULAR_VECTOR_APPLE 0x85b0

		//sync,
		#define GL_SYNC_FLUSH_COMMANDS_BIT_APPLE 0x00000001
		#define GL_SYNC_OBJECT_APPLE 0x8a53
		#define GL_MAX_SERVER_WAIT_TIMEOUT_APPLE 0x9111
		#define GL_OBJECT_TYPE_APPLE 0x9112
		#define GL_SYNC_CONDITION_APPLE 0x9113
		#define GL_SYNC_STATUS_APPLE 0x9114
		#define GL_SYNC_FLAGS_APPLE 0x9115
		#define GL_SYNC_FENCE_APPLE 0x9116
		#define GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
		#define GL_UNSIGNALED_APPLE 0x9118
		#define GL_SIGNALED_APPLE 0x9119
		#define GL_ALREADY_SIGNALED_APPLE 0x911a
		#define GL_TIMEOUT_EXPIRED_APPLE 0x911b
		#define GL_CONDITION_SATISFIED_APPLE 0x911c
		#define GL_WAIT_FAILED_APPLE 0x911d
		#define GL_TIMEOUT_IGNORED_APPLE 0xffffffffffffffffull

		//texture format bgra_8888,
		#define GL_BGRA_EXT 0x80e1
		#define GL_BGRA8_EXT 0x93a1

		//texture max level,
		#define GL_TEXTURE_MAX_LEVEL_APPLE 0x813d

		//texture packed float,
		#define GL_R11F_G11F_B10F_APPLE 0x8c3a
		#define GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE 0x8c3b
		#define GL_RGB9_E5_APPLE 0x8c3d
		#define GL_UNSIGNED_INT_5_9_9_9_REV_APPLE 0x8c3e

		//texture range,
		#define GL_TEXTURE_RANGE_LENGTH_APPLE 0x85b7
		#define GL_TEXTURE_RANGE_POINTER_APPLE 0x85b8
		#define GL_TEXTURE_STORAGE_HINT_APPLE 0x85bc
		#define GL_STORAGE_PRIVATE_APPLE 0x85bd
		#define GL_STORAGE_CACHED_APPLE 0x85be
		#define GL_STORAGE_SHARED_APPLE 0x85bf

		//transform hint,
		#define GL_TRANSFORM_HINT_APPLE 0x85b1

		//vertex array object,
		#define GL_VERTEX_ARRAY_BINDING_APPLE 0x85b5

		//vertex array range,
		#define GL_VERTEX_ARRAY_RANGE_APPLE 0x851d
		#define GL_VERTEX_ARRAY_RANGE_LENGTH_APPLE 0x851e
		#define GL_VERTEX_ARRAY_STORAGE_HINT_APPLE 0x851f
		#define GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_APPLE 0x8520
		#define GL_VERTEX_ARRAY_RANGE_POINTER_APPLE 0x8521

		//vertex program evaluators,
		#define GL_VERTEX_ATTRIB_MAP1_APPLE 0x8a00
		#define GL_VERTEX_ATTRIB_MAP2_APPLE 0x8a01
		#define GL_VERTEX_ATTRIB_MAP1_SIZE_APPLE 0x8a02
		#define GL_VERTEX_ATTRIB_MAP1_COEFF_APPLE 0x8a03
		#define GL_VERTEX_ATTRIB_MAP1_ORDER_APPLE 0x8a04
		#define GL_VERTEX_ATTRIB_MAP1_DOMAIN_APPLE 0x8a05
		#define GL_VERTEX_ATTRIB_MAP2_SIZE_APPLE 0x8a06
		#define GL_VERTEX_ATTRIB_MAP2_COEFF_APPLE 0x8a07
		#define GL_VERTEX_ATTRIB_MAP2_ORDER_APPLE 0x8a08
		#define GL_VERTEX_ATTRIB_MAP2_DOMAIN_APPLE 0x8a09

		//ycbcr 422,
		#define GL_YCBCR_422_APPLE 0x85b9

	//aux depth stencil
#define APPLE_aux_depth_stencil 1

	//client storage
#define APPLE_client_storage 1

	//clip distance
#define APPLE_clip_distance 1

	//color buffer packed float
#define APPLE_color_buffer_packed_float 1

	//copy texture levels
#define APPLE_copy_texture_levels 1
	inline void (*glCopyTextureLevelsAPPLE) (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount) = nullptr;

	//element array
#define APPLE_element_array 1
	inline void (*glDrawElementArrayAPPLE) (GLenum mode, GLint first, GLsizei count) = nullptr;
	inline void (*glDrawRangeElementArrayAPPLE) (GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count) = nullptr;
	inline void (*glElementPointerAPPLE) (GLenum type, const void* pointer) = nullptr;
	inline void (*glMultiDrawElementArrayAPPLE) (GLenum mode, const GLint* first, const GLsizei* count, GLsizei primcount) = nullptr;
	inline void (*glMultiDrawRangeElementArrayAPPLE) (GLenum mode, GLuint start, GLuint end, const GLint* first, const GLsizei* count, GLsizei primcount) = nullptr;

	//fence
#define APPLE_fence 1
	inline void (*glDeleteFencesAPPLE) (GLsizei n, const GLuint* fences) = nullptr;
	inline void (*glFinishFenceAPPLE) (GLuint fence) = nullptr;
	inline void (*glFinishObjectAPPLE) (GLenum object, GLint name) = nullptr;
	inline void (*glGenFencesAPPLE) (GLsizei n, GLuint* fences) = nullptr;
	inline GLboolean(*glIsFenceAPPLE) (GLuint fence) = nullptr;
	inline void (*glSetFenceAPPLE) (GLuint fence) = nullptr;
	inline GLboolean(*glTestFenceAPPLE) (GLuint fence) = nullptr;
	inline GLboolean(*glTestObjectAPPLE) (GLenum object, GLuint name) = nullptr;

	//float pixels
#define APPLE_float_pixels 1

	//flush buffer range
#define APPLE_flush_buffer_range 1
	inline void (*glBufferParameteriAPPLE) (GLenum target, GLenum pname, GLint param) = nullptr;
	inline void (*glFlushMappedBufferRangeAPPLE) (GLenum target, GLintptr offset, GLsizeiptr size) = nullptr;

	//framebuffer multisample
#define APPLE_framebuffer_multisample 1
	inline void (*glRenderbufferStorageMultisampleAPPLE) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void (*glResolveMultisampleFramebufferAPPLE) (void) = nullptr;

	//object purgeable
#define APPLE_object_purgeable 1
	inline void (*glGetObjectParameterivAPPLE) (GLenum objectType, GLuint name, GLenum pname, GLint* params) = nullptr;
	inline GLenum(*glObjectPurgeableAPPLE) (GLenum objectType, GLuint name, GLenum option) = nullptr;
	inline GLenum(*glObjectUnpurgeableAPPLE) (GLenum objectType, GLuint name, GLenum option) = nullptr;

	//pixel buffer
#define APPLE_pixel_buffer 1

	//rgb 422
#define APPLE_rgb_422 1

	//row bytes
#define APPLE_row_bytes 1

	//specular vector
#define APPLE_specular_vector 1

	//sync
#define APPLE_sync 1
	inline GLenum(*glClientWaitSyncAPPLE) (GLsync GLsync, GLbitfield flags, GLuint64 timeout) = nullptr;
	inline void (*glDeleteSyncAPPLE) (GLsync GLsync) = nullptr;
	inline GLsync(*glFenceSyncAPPLE) (GLenum condition, GLbitfield flags) = nullptr;
	inline void (*glGetInteger64vAPPLE) (GLenum pname, GLint64* params) = nullptr;
	inline void (*glGetSyncivAPPLE) (GLsync GLsync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) = nullptr;
	inline GLboolean(*glIsSyncAPPLE) (GLsync GLsync) = nullptr;
	inline void (*glWaitSyncAPPLE) (GLsync GLsync, GLbitfield flags, GLuint64 timeout) = nullptr;

	//texture 2D limited npot
#define APPLE_texture_2D_limited_npot 1

	//texture format BGRA8888
#define APPLE_texture_format_BGRA8888 1

	//texture max level
#define APPLE_texture_max_level 1

	//texture packed float
#define APPLE_texture_packed_float 1

	//texture range
#define APPLE_texture_range 1
	inline void (*glGetTexParameterPointervAPPLE) (GLenum target, GLenum pname, void** params) = nullptr;
	inline void (*glTextureRangeAPPLE) (GLenum target, GLsizei length, void* pointer) = nullptr;

	//transform hint
#define APPLE_transform_hint 1

	//vertex array object
#define APPLE_vertex_array_object 1
	inline void (*glBindVertexArrayAPPLE) (GLuint array) = nullptr;
	inline void (*glDeleteVertexArraysAPPLE) (GLsizei n, const GLuint* arrays) = nullptr;
	inline void (*glGenVertexArraysAPPLE) (GLsizei n, const GLuint* arrays) = nullptr;
	inline GLboolean(*glIsVertexArrayAPPLE) (GLuint array) = nullptr;

	//vertex array range
#define APPLE_vertex_array_range 1
	inline void (*glFlushVertexArrayRangeAPPLE) (GLsizei length, void* pointer) = nullptr;
	inline void (*glVertexArrayParameteriAPPLE) (GLenum pname, GLint param) = nullptr;
	inline void (*glVertexArrayRangeAPPLE) (GLsizei length, void* pointer) = nullptr;

	//vertex program evaluators
#define APPLE_vertex_program_evaluators 1
	inline void (*glDisableVertexAttribAPPLE) (GLuint index, GLenum pname) = nullptr;
	inline void (*glEnableVertexAttribAPPLE) (GLuint index, GLenum pname) = nullptr;
	inline GLboolean(*glIsVertexAttribEnabledAPPLE) (GLuint index, GLenum pname) = nullptr;
	inline void (*glMapVertexAttrib1dAPPLE) (GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble* points) = nullptr;
	inline void (*glMapVertexAttrib1fAPPLE) (GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points) = nullptr;
	inline void (*glMapVertexAttrib2dAPPLE) (GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points) = nullptr;
	inline void (*glMapVertexAttrib2fAPPLE) (GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points) = nullptr;

	//ycbcr 422
#define APPLE_ycbcr_422 1

	//*< load Apple Extensions
	inline void LoadAppleExtensions()
	{
		//copy texture levels
		FetchProcAddress(glCopyTextureLevelsAPPLE, "glCopyTextureLevelsAPPLE");

		//element array
		FetchProcAddress(glDrawElementArrayAPPLE, "glDrawElementArrayAPPLE");
		FetchProcAddress(glDrawRangeElementArrayAPPLE, "glDrawRangeElementArrayAPPLE");
		FetchProcAddress(glElementPointerAPPLE, "glElementPointerAPPLE");
		FetchProcAddress(glMultiDrawElementArrayAPPLE, "glMultiDrawElementArrayAPPLE");
		FetchProcAddress(glMultiDrawRangeElementArrayAPPLE, "glMultiDrawRangeElementArrayAPPLE");

		//fence
		FetchProcAddress(glDeleteFencesAPPLE, "glDeleteFencesAPPLE");
		FetchProcAddress(glFinishFenceAPPLE, "glFinishFenceAPPLE");
		FetchProcAddress(glFinishObjectAPPLE, "glFinishObjectAPPLE");
		FetchProcAddress(glGenFencesAPPLE, "glGenFencesAPPLE");
		FetchProcAddress(glIsFenceAPPLE, "glIsFenceAPPLE");
		FetchProcAddress(glSetFenceAPPLE, "glSetFenceAPPLE");
		FetchProcAddress(glTestFenceAPPLE, "glTestFenceAPPLE");
		FetchProcAddress(glTestObjectAPPLE, "glTestObjectAPPLE");

		//flush buffer range
		FetchProcAddress(glBufferParameteriAPPLE, "glBufferParameteriAPPLE");
		FetchProcAddress(glFlushMappedBufferRangeAPPLE, "glFlushMappedBufferRangeAPPLE");

		//framebuffer multisample
		FetchProcAddress(glRenderbufferStorageMultisampleAPPLE, "glRenderbufferStorageMultisampleAPPLE");
		FetchProcAddress(glResolveMultisampleFramebufferAPPLE, "glResolveMultisampleFramebufferAPPLE");

		//object purgeable
		FetchProcAddress(glGetObjectParameterivAPPLE, "glGetObjectParameterivAPPLE");
		FetchProcAddress(glObjectPurgeableAPPLE, "glObjectPurgeableAPPLE");
		FetchProcAddress(glObjectUnpurgeableAPPLE, "glObjectUnpurgeableAPPLE");

		//sync
		FetchProcAddress(glClientWaitSyncAPPLE, "glClientWaitSyncAPPLE");
		FetchProcAddress(glDeleteSyncAPPLE, "glDeleteSyncAPPLE");
		FetchProcAddress(glFenceSyncAPPLE, "glFenceSyncAPPLE");
		FetchProcAddress(glGetInteger64vAPPLE, "glGetInteger64vAPPLE");
		FetchProcAddress(glGetSyncivAPPLE, "glGetSyncivAPPLE");
		FetchProcAddress(glIsSyncAPPLE, "glIsSyncAPPLE");
		FetchProcAddress(glWaitSyncAPPLE, "glWaitSyncAPPLE");

		//texture range
		FetchProcAddress(glGetTexParameterPointervAPPLE, "glGetTexParameterPointervAPPLE");
		FetchProcAddress(glTextureRangeAPPLE, "glTextureRangeAPPLE");

		//vertex array object
		FetchProcAddress(glBindVertexArrayAPPLE, "glBindVertexArrayAPPLE");
		FetchProcAddress(glDeleteVertexArraysAPPLE, "glDeleteVertexArraysAPPLE");
		FetchProcAddress(glGenVertexArraysAPPLE, "glGenVertexArraysAPPLE");
		FetchProcAddress(glIsVertexArrayAPPLE, "glIsVertexArrayAPPLE");

		//vertex array range
		FetchProcAddress(glFlushVertexArrayRangeAPPLE, "glFlushVertexArrayRangeAPPLE");
		FetchProcAddress(glVertexArrayParameteriAPPLE, "glVertexArrayParameteriAPPLE");
		FetchProcAddress(glVertexArrayRangeAPPLE, "glVertexArrayRangeAPPLE");

		//vertex program evaluators
		FetchProcAddress(glDisableVertexAttribAPPLE, "glDisableVertexAttribAPPLE");
		FetchProcAddress(glEnableVertexAttribAPPLE, "glEnableVertexAttribAPPLE");
		FetchProcAddress(glIsVertexAttribEnabledAPPLE, "glIsVertexAttribEnabledAPPLE");
		FetchProcAddress(glMapVertexAttrib1dAPPLE, "glMapVertexAttrib1dAPPLE");
		FetchProcAddress(glMapVertexAttrib1fAPPLE, "glMapVertexAttrib1fAPPLE");
		FetchProcAddress(glMapVertexAttrib2dAPPLE, "glMapVertexAttrib2dAPPLE");
		FetchProcAddress(glMapVertexAttrib2fAPPLE, "glMapVertexAttrib2fAPPLE");
	}

#pragma endregion Apple Extensions

	//OpenGL ARB Extensions
#pragma region ARB
	typedef char GLcharARB;
	typedef unsigned int GLhandleARB;
	typedef int GLfixed;
	//typedef struct _cl_context* cl_context;
	//typedef struct _cl_event* cl_event;
	typedef ptrdiff_t GLintptrARB;
	typedef ptrdiff_t GLsizeiptrARB;


#define GL_FIXED 0x140c
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8b9a
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8b9b
#define GL_RGB565 0x8d62
#define GL_LOW_FLOAT 0x8df0
#define GL_MEDIUM_FLOAT 0x8df1
#define GL_HIGH_FLOAT 0x8df2
#define GL_LOW_INT 0x8df3
#define GL_MEDIUM_INT 0x8df4
#define GL_HIGH_INT 0x8df5
#define GL_SHADER_BINARY_FORMATS 0x8df8
#define GL_NUM_SHADER_BINARY_FORMATS 0x8df9
#define GL_SHADER_COMPILER 0x8dfa
#define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8dfb
#define GL_MAX_VARYING_VECTORS 0x8dfc
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8dfd
#define GL_PRIMITIVE_BOUNDING_BOX_ARB 0x92be
#define GL_MULTISAMPLE_LINE_WIDTH_RANGE_ARB 0x9381
#define GL_MULTISAMPLE_LINE_WIDTH_GRANULARITY_ARB 0x9382
#define GL_TEXTURE_IMMUTABLE_LEVELS 0x82df
#define GL_PRIMITIVE_RESTART_FIXED_INDEX 0x8d69
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8d6a
#define GL_MAX_ELEMENT_INDEX 0x8d6b
#define GL_COMPRESSED_R11_EAC 0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC 0x9271
#define GL_COMPRESSED_RG11_EAC 0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC 0x9273
#define GL_COMPRESSED_RGB8_ETC2 0x9274
#define GL_COMPRESSED_SRGB8_ETC2 0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC 0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#define GL_UNSIGNED_INT64_ARB 0x140f
#define GL_SRC1_COLOR 0x88f9
#define GL_ONE_MINUS_SRC1_COLOR 0x88fa
#define GL_ONE_MINUS_SRC1_ALPHA 0x88fb
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS 0x88fc
#define GL_MAP_READ_BIT 0x0001
#define GL_MAP_WRITE_BIT 0x0002
#define GL_MAP_PERSISTENT_BIT 0x00000040
#define GL_MAP_COHERENT_BIT 0x00000080
#define GL_DYNAMIC_STORAGE_BIT 0x0100
#define GL_CLIENT_STORAGE_BIT 0x0200
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 0x00004000
#define GL_BUFFER_IMMUTABLE_STORAGE 0x821f
#define GL_BUFFER_STORAGE_FLAGS 0x8220
#define GL_SYNC_CL_EVENT_ARB 0x8240
#define GL_SYNC_CL_EVENT_COMPLETE_ARB 0x8241
#define GL_CLEAR_TEXTURE 0x9365
#define GL_LOWER_LEFT 0x8ca1
#define GL_UPPER_LEFT 0x8ca2
#define GL_CLIP_ORIGIN 0x935c
#define GL_CLIP_DEPTH_MODE 0x935d
#define GL_NEGATIVE_ONE_TO_ONE 0x935e
#define GL_ZERO_TO_ONE 0x935f
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#define GL_CLAMP_VERTEX_COLOR_ARB 0x891a
#define GL_CLAMP_FRAGMENT_COLOR_ARB 0x891b
#define GL_CLAMP_READ_COLOR_ARB 0x891c
#define GL_FIXED_ONLY_ARB 0x891d
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH 0x9127
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH 0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE 0x912a
#define GL_PACK_COMPRESSED_BLOCK_WIDTH 0x912b
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT 0x912c
#define GL_PACK_COMPRESSED_BLOCK_DEPTH 0x912d
#define GL_PACK_COMPRESSED_BLOCK_SIZE 0x912e
#define GL_COMPUTE_SHADER_BIT 0x00000020
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS 0x8265
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#define GL_COMPUTE_WORK_GROUP_SIZE 0x8267
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90eb
#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 0x90ec
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ed
#define GL_DISPATCH_INDIRECT_BUFFER 0x90ee
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90ef
#define GL_COMPUTE_SHADER 0x91b9
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS 0x91bb
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91bc
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS 0x91bd
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT 0x91be
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE 0x91bf
#define GL_MAX_COMPUTE_FIXED_GROUP_INVOCATIONS_ARB 0x90eb
#define GL_MAX_COMPUTE_FIXED_GROUP_SIZE_ARB 0x91bf
#define GL_MAX_COMPUTE_VARIABLE_GROUP_INVOCATIONS_ARB 0x9344
#define GL_MAX_COMPUTE_VARIABLE_GROUP_SIZE_ARB 0x9345
#define GL_QUERY_WAIT_INVERTED 0x8e17
#define GL_QUERY_NO_WAIT_INVERTED 0x8e18
#define GL_QUERY_BY_REGION_WAIT_INVERTED 0x8e19
#define GL_QUERY_BY_REGION_NO_WAIT_INVERTED 0x8e1a
#define GL_COPY_READ_BUFFER 0x8f36
#define GL_COPY_WRITE_BUFFER 0x8f37
#define GL_MAX_CULL_DISTANCES 0x82f9
#define GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 0x82fa
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB 0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION_ARB 0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM_ARB 0x8245
#define GL_DEBUG_SOURCE_API_ARB 0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB 0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB 0x8249
#define GL_DEBUG_SOURCE_APPLICATION_ARB 0x824a
#define GL_DEBUG_SOURCE_OTHER_ARB 0x824b
#define GL_DEBUG_TYPE_ERROR_ARB 0x824c
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB 0x824d
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB 0x824e
#define GL_DEBUG_TYPE_PORTABILITY_ARB 0x824f
#define GL_DEBUG_TYPE_PERFORMANCE_ARB 0x8250
#define GL_DEBUG_TYPE_OTHER_ARB 0x8251
#define GL_MAX_DEBUG_MESSAGE_LENGTH_ARB 0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES_ARB 0x9144
#define GL_DEBUG_LOGGED_MESSAGES_ARB 0x9145
#define GL_DEBUG_SEVERITY_HIGH_ARB 0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_ARB 0x9147
#define GL_DEBUG_SEVERITY_LOW_ARB 0x9148
#define GL_DEPTH_COMPONENT32F 0x8cac
#define GL_DEPTH32F_STENCIL8 0x8cad
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8dad
#define GL_DEPTH_CLAMP 0x864f
#define GL_DEPTH_COMPONENT16_ARB 0x81a5
#define GL_DEPTH_COMPONENT24_ARB 0x81a6
#define GL_DEPTH_COMPONENT32_ARB 0x81a7
#define GL_TEXTURE_DEPTH_SIZE_ARB 0x884a
#define GL_DEPTH_TEXTURE_MODE_ARB 0x884b
#define GL_TEXTURE_TARGET 0x1006
#define GL_QUERY_TARGET 0x82ea
#define GL_MAX_DRAW_BUFFERS_ARB 0x8824
#define GL_DRAW_BUFFER0_ARB 0x8825
#define GL_DRAW_BUFFER1_ARB 0x8826
#define GL_DRAW_BUFFER2_ARB 0x8827
#define GL_DRAW_BUFFER3_ARB 0x8828
#define GL_DRAW_BUFFER4_ARB 0x8829
#define GL_DRAW_BUFFER5_ARB 0x882a
#define GL_DRAW_BUFFER6_ARB 0x882b
#define GL_DRAW_BUFFER7_ARB 0x882c
#define GL_DRAW_BUFFER8_ARB 0x882d
#define GL_DRAW_BUFFER9_ARB 0x882e
#define GL_DRAW_BUFFER10_ARB 0x882f
#define GL_DRAW_BUFFER11_ARB 0x8830
#define GL_DRAW_BUFFER12_ARB 0x8831
#define GL_DRAW_BUFFER13_ARB 0x8832
#define GL_DRAW_BUFFER14_ARB 0x8833
#define GL_DRAW_BUFFER15_ARB 0x8834
#define GL_DRAW_INDIRECT_BUFFER 0x8f3f
#define GL_DRAW_INDIRECT_BUFFER_BINDING 0x8f43
#define GL_LOCATION_COMPONENT 0x934a
#define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 0x934b
#define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 0x934c
#define GL_MAX_UNIFORM_LOCATIONS 0x826e
#define GL_FRAGMENT_PROGRAM_ARB 0x8804
#define GL_PROGRAM_ALU_INSTRUCTIONS_ARB 0x8805
#define GL_PROGRAM_TEX_INSTRUCTIONS_ARB 0x8806
#define GL_PROGRAM_TEX_INDIRECTIONS_ARB 0x8807
#define GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB 0x8808
#define GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB 0x8809
#define GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB 0x880a
#define GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB 0x880b
#define GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB 0x880c
#define GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB 0x880d
#define GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB 0x880e
#define GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB 0x880f
#define GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB 0x8810
#define GL_MAX_TEXTURE_COORDS_ARB 0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB 0x8872
#define GL_FRAGMENT_SHADER_ARB 0x8b30
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB 0x8b49
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_ARB 0x8b8b
#define GL_FRAMEBUFFER_DEFAULT_WIDTH 0x9310
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT 0x9311
#define GL_FRAMEBUFFER_DEFAULT_LAYERS 0x9312
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES 0x9313
#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#define GL_MAX_FRAMEBUFFER_WIDTH 0x9315
#define GL_MAX_FRAMEBUFFER_HEIGHT 0x9316
#define GL_MAX_FRAMEBUFFER_LAYERS 0x9317
#define GL_MAX_FRAMEBUFFER_SAMPLES 0x9318
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_DEFAULT 0x8218
#define GL_FRAMEBUFFER_UNDEFINED 0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821a
#define GL_INDEX 0x8222
#define GL_MAX_RENDERBUFFER_SIZE 0x84e8
#define GL_DEPTH_STENCIL 0x84f9
#define GL_UNSIGNED_INT_24_8 0x84fa
#define GL_DEPTH24_STENCIL8 0x88f0
#define GL_TEXTURE_STENCIL_SIZE 0x88f1
#define GL_UNSIGNED_NORMALIZED 0x8c17
#define GL_SRGB 0x8c40
#define GL_DRAW_FRAMEBUFFER_BINDING 0x8ca6
#define GL_FRAMEBUFFER_BINDING 0x8ca6
#define GL_RENDERBUFFER_BINDING 0x8ca7
#define GL_READ_FRAMEBUFFER 0x8ca8
#define GL_DRAW_FRAMEBUFFER 0x8ca9
#define GL_READ_FRAMEBUFFER_BINDING 0x8caa
#define GL_RENDERBUFFER_SAMPLES 0x8cab
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8cd0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8cd1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8cd2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8cd3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8cd4
#define GL_FRAMEBUFFER_COMPLETE 0x8cd5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8cd6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8cd7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8cdb
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8cdc
#define GL_FRAMEBUFFER_UNSUPPORTED 0x8cdd
#define GL_MAX_COLOR_ATTACHMENTS 0x8cdf
#define GL_COLOR_ATTACHMENT0 0x8ce0
#define GL_COLOR_ATTACHMENT1 0x8ce1
#define GL_COLOR_ATTACHMENT2 0x8ce2
#define GL_COLOR_ATTACHMENT3 0x8ce3
#define GL_COLOR_ATTACHMENT4 0x8ce4
#define GL_COLOR_ATTACHMENT5 0x8ce5
#define GL_COLOR_ATTACHMENT6 0x8ce6
#define GL_COLOR_ATTACHMENT7 0x8ce7
#define GL_COLOR_ATTACHMENT8 0x8ce8
#define GL_COLOR_ATTACHMENT9 0x8ce9
#define GL_COLOR_ATTACHMENT10 0x8cea
#define GL_COLOR_ATTACHMENT11 0x8ceb
#define GL_COLOR_ATTACHMENT12 0x8cec
#define GL_COLOR_ATTACHMENT13 0x8ced
#define GL_COLOR_ATTACHMENT14 0x8cee
#define GL_COLOR_ATTACHMENT15 0x8cef
#define GL_DEPTH_ATTACHMENT 0x8d00
#define GL_STENCIL_ATTACHMENT 0x8d20
#define GL_FRAMEBUFFER 0x8d40
#define GL_RENDERBUFFER 0x8d41
#define GL_RENDERBUFFER_WIDTH 0x8d42
#define GL_RENDERBUFFER_HEIGHT 0x8d43
#define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8d44
#define GL_STENCIL_INDEX1 0x8d46
#define GL_STENCIL_INDEX4 0x8d47
#define GL_STENCIL_INDEX8 0x8d48
#define GL_STENCIL_INDEX16 0x8d49
#define GL_RENDERBUFFER_RED_SIZE 0x8d50
#define GL_RENDERBUFFER_GREEN_SIZE 0x8d51
#define GL_RENDERBUFFER_BLUE_SIZE 0x8d52
#define GL_RENDERBUFFER_ALPHA_SIZE 0x8d53
#define GL_RENDERBUFFER_DEPTH_SIZE 0x8d54
#define GL_RENDERBUFFER_STENCIL_SIZE 0x8d55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8d56
#define GL_MAX_SAMPLES 0x8d57
#define GL_FRAMEBUFFER_SRGB 0x8db9
#define GL_LINES_ADJACENCY_ARB 0xa
#define GL_LINE_STRIP_ADJACENCY_ARB 0xb
#define GL_TRIANGLES_ADJACENCY_ARB 0xc
#define GL_TRIANGLE_STRIP_ADJACENCY_ARB 0xd
#define GL_PROGRAM_POINT_SIZE_ARB 0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_ARB 0x8c29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_ARB 0x8da7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_ARB 0x8da8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB 0x8da9
#define GL_GEOMETRY_SHADER_ARB 0x8dd9
#define GL_GEOMETRY_VERTICES_OUT_ARB 0x8dda
#define GL_GEOMETRY_INPUT_TYPE_ARB 0x8ddb
#define GL_GEOMETRY_OUTPUT_TYPE_ARB 0x8ddc
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB 0x8ddd
#define GL_MAX_VERTEX_VARYING_COMPONENTS_ARB 0x8dde
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_ARB 0x8ddf
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_ARB 0x8de0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_ARB 0x8de1
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_BINARY_LENGTH 0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS 0x87fe
#define GL_PROGRAM_BINARY_FORMATS 0x87ff
#define GL_SHADER_BINARY_FORMAT_SPIR_V_ARB 0x9551
#define GL_SPIR_V_BINARY_ARB 0x9552
#define GL_GEOMETRY_SHADER_INVOCATIONS 0x887f
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8e5a
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8e5b
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8e5c
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8e5d
#define GL_MAX_VERTEX_STREAMS 0x8e71
#define GL_DOUBLE_MAT2 0x8f46
#define GL_DOUBLE_MAT3 0x8f47
#define GL_DOUBLE_MAT4 0x8f48
#define GL_DOUBLE_MAT2X3 0x8f49
#define GL_DOUBLE_MAT2X4 0x8f4a
#define GL_DOUBLE_MAT3X2 0x8f4b
#define GL_DOUBLE_MAT3X4 0x8f4c
#define GL_DOUBLE_MAT4X2 0x8f4d
#define GL_DOUBLE_MAT4X3 0x8f4e
#define GL_DOUBLE_VEC2 0x8ffc
#define GL_DOUBLE_VEC3 0x8ffd
#define GL_DOUBLE_VEC4 0x8ffe
#define GL_INT64_ARB 0x140e
#define GL_INT64_VEC2_ARB 0x8fe9
#define GL_INT64_VEC3_ARB 0x8fea
#define GL_INT64_VEC4_ARB 0x8feb
#define GL_UNSIGNED_INT64_VEC2_ARB 0x8ff5
#define GL_UNSIGNED_INT64_VEC3_ARB 0x8ff6
#define GL_UNSIGNED_INT64_VEC4_ARB 0x8ff7
#define GL_HALF_FLOAT_ARB 0x140b
#define GL_HALF_FLOAT 0x140b
#define GL_CONSTANT_COLOR 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#define GL_CONSTANT_ALPHA 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#define GL_BLEND_COLOR 0x8005
#define GL_FUNC_ADD 0x8006
#define GL_MIN 0x8007
#define GL_MAX 0x8008
#define GL_BLEND_EQUATION 0x8009
#define GL_FUNC_SUBTRACT 0x800a
#define GL_FUNC_REVERSE_SUBTRACT 0x800b
#define GL_CONVOLUTION_1D 0x8010
#define GL_CONVOLUTION_2D 0x8011
#define GL_SEPARABLE_2D 0x8012
#define GL_CONVOLUTION_BORDER_MODE 0x8013
#define GL_CONVOLUTION_FILTER_SCALE 0x8014
#define GL_CONVOLUTION_FILTER_BIAS 0x8015
#define GL_REDUCE 0x8016
#define GL_CONVOLUTION_FORMAT 0x8017
#define GL_CONVOLUTION_WIDTH 0x8018
#define GL_CONVOLUTION_HEIGHT 0x8019
#define GL_MAX_CONVOLUTION_WIDTH 0x801a
#define GL_MAX_CONVOLUTION_HEIGHT 0x801b
#define GL_POST_CONVOLUTION_RED_SCALE 0x801c
#define GL_POST_CONVOLUTION_GREEN_SCALE 0x801d
#define GL_POST_CONVOLUTION_BLUE_SCALE 0x801e
#define GL_POST_CONVOLUTION_ALPHA_SCALE 0x801f
#define GL_POST_CONVOLUTION_RED_BIAS 0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS 0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS 0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS 0x8023
#define GL_HISTOGRAM 0x8024
#define GL_PROXY_HISTOGRAM 0x8025
#define GL_HISTOGRAM_WIDTH 0x8026
#define GL_HISTOGRAM_FORMAT 0x8027
#define GL_HISTOGRAM_RED_SIZE 0x8028
#define GL_HISTOGRAM_GREEN_SIZE 0x8029
#define GL_HISTOGRAM_BLUE_SIZE 0x802a
#define GL_HISTOGRAM_ALPHA_SIZE 0x802b
#define GL_HISTOGRAM_LUMINANCE_SIZE 0x802c
#define GL_HISTOGRAM_SINK 0x802d
#define GL_MINMAX 0x802e
#define GL_MINMAX_FORMAT 0x802f
#define GL_MINMAX_SINK 0x8030
#define GL_TABLE_TOO_LARGE 0x8031
#define GL_COLOR_MATRIX 0x80b1
#define GL_COLOR_MATRIX_STACK_DEPTH 0x80b2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH 0x80b3
#define GL_POST_COLOR_MATRIX_RED_SCALE 0x80b4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE 0x80b5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE 0x80b6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE 0x80b7
#define GL_POST_COLOR_MATRIX_RED_BIAS 0x80b8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS 0x80b9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS 0x80ba
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS 0x80bb
#define GL_COLOR_TABLE 0x80d0
#define GL_POST_CONVOLUTION_COLOR_TABLE 0x80d1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE 0x80d2
#define GL_PROXY_COLOR_TABLE 0x80d3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE 0x80d4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE 0x80d5
#define GL_COLOR_TABLE_SCALE 0x80d6
#define GL_COLOR_TABLE_BIAS 0x80d7
#define GL_COLOR_TABLE_FORMAT 0x80d8
#define GL_COLOR_TABLE_WIDTH 0x80d9
#define GL_COLOR_TABLE_RED_SIZE 0x80da
#define GL_COLOR_TABLE_GREEN_SIZE 0x80db
#define GL_COLOR_TABLE_BLUE_SIZE 0x80dc
#define GL_COLOR_TABLE_ALPHA_SIZE 0x80dd
#define GL_COLOR_TABLE_LUMINANCE_SIZE 0x80de
#define GL_COLOR_TABLE_INTENSITY_SIZE 0x80df
#define GL_IGNORE_BORDER 0x8150
#define GL_CONSTANT_BORDER 0x8151
#define GL_WRAP_BORDER 0x8152
#define GL_REPLICATE_BORDER 0x8153
#define GL_CONVOLUTION_BORDER_COLOR 0x8154
#define GL_PARAMETER_BUFFER_ARB 0x80ee
#define GL_PARAMETER_BUFFER_BINDING_ARB 0x80ef
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ARB 0x88fe
#define GL_NUM_SAMPLE_COUNTS 0x9380
#define GL_INTERNALFORMAT_SUPPORTED 0x826f
#define GL_INTERNALFORMAT_PREFERRED 0x8270
#define GL_INTERNALFORMAT_RED_SIZE 0x8271
#define GL_INTERNALFORMAT_GREEN_SIZE 0x8272
#define GL_INTERNALFORMAT_BLUE_SIZE 0x8273
#define GL_INTERNALFORMAT_ALPHA_SIZE 0x8274
#define GL_INTERNALFORMAT_DEPTH_SIZE 0x8275
#define GL_INTERNALFORMAT_STENCIL_SIZE 0x8276
#define GL_INTERNALFORMAT_SHARED_SIZE 0x8277
#define GL_INTERNALFORMAT_RED_TYPE 0x8278
#define GL_INTERNALFORMAT_GREEN_TYPE 0x8279
#define GL_INTERNALFORMAT_BLUE_TYPE 0x827a
#define GL_INTERNALFORMAT_ALPHA_TYPE 0x827b
#define GL_INTERNALFORMAT_DEPTH_TYPE 0x827c
#define GL_INTERNALFORMAT_STENCIL_TYPE 0x827d
#define GL_MAX_WIDTH 0x827e
#define GL_MAX_HEIGHT 0x827f
#define GL_MAX_DEPTH 0x8280
#define GL_MAX_LAYERS 0x8281
#define GL_MAX_COMBINED_DIMENSIONS 0x8282
#define GL_COLOR_COMPONENTS 0x8283
#define GL_DEPTH_COMPONENTS 0x8284
#define GL_STENCIL_COMPONENTS 0x8285
#define GL_COLOR_RENDERABLE 0x8286
#define GL_DEPTH_RENDERABLE 0x8287
#define GL_STENCIL_RENDERABLE 0x8288
#define GL_FRAMEBUFFER_RENDERABLE 0x8289
#define GL_FRAMEBUFFER_RENDERABLE_LAYERED 0x828a
#define GL_FRAMEBUFFER_BLEND 0x828b
#define GL_READ_PIXELS 0x828c
#define GL_READ_PIXELS_FORMAT 0x828d
#define GL_READ_PIXELS_TYPE 0x828e
#define GL_TEXTURE_IMAGE_FORMAT 0x828f
#define GL_TEXTURE_IMAGE_TYPE 0x8290
#define GL_GET_TEXTURE_IMAGE_FORMAT 0x8291
#define GL_GET_TEXTURE_IMAGE_TYPE 0x8292
#define GL_MIPMAP 0x8293
#define GL_MANUAL_GENERATE_MIPMAP 0x8294
#define GL_AUTO_GENERATE_MIPMAP 0x8295
#define GL_COLOR_ENCODING 0x8296
#define GL_SRGB_READ 0x8297
#define GL_SRGB_WRITE 0x8298
#define GL_SRGB_DECODE_ARB 0x8299
#define GL_FILTER 0x829a
#define GL_VERTEX_TEXTURE 0x829b
#define GL_TESS_CONTROL_TEXTURE 0x829c
#define GL_TESS_EVALUATION_TEXTURE 0x829d
#define GL_GEOMETRY_TEXTURE 0x829e
#define GL_FRAGMENT_TEXTURE 0x829f
#define GL_COMPUTE_TEXTURE 0x82a0
#define GL_TEXTURE_SHADOW 0x82a1
#define GL_TEXTURE_GATHER 0x82a2
#define GL_TEXTURE_GATHER_SHADOW 0x82a3
#define GL_SHADER_IMAGE_LOAD 0x82a4
#define GL_SHADER_IMAGE_STORE 0x82a5
#define GL_SHADER_IMAGE_ATOMIC 0x82a6
#define GL_IMAGE_TEXEL_SIZE 0x82a7
#define GL_IMAGE_COMPATIBILITY_CLASS 0x82a8
#define GL_IMAGE_PIXEL_FORMAT 0x82a9
#define GL_IMAGE_PIXEL_TYPE 0x82aa
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 0x82ac
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 0x82ad
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 0x82ae
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 0x82af
#define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 0x82b1
#define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 0x82b2
#define GL_TEXTURE_COMPRESSED_BLOCK_SIZE 0x82b3
#define GL_CLEAR_BUFFER 0x82b4
#define GL_TEXTURE_VIEW 0x82b5
#define GL_VIEW_COMPATIBILITY_CLASS 0x82b6
#define GL_FULL_SUPPORT 0x82b7
#define GL_CAVEAT_SUPPORT 0x82b8
#define GL_IMAGE_CLASS_4_X_32 0x82b9
#define GL_IMAGE_CLASS_2_X_32 0x82ba
#define GL_IMAGE_CLASS_1_X_32 0x82bb
#define GL_IMAGE_CLASS_4_X_16 0x82bc
#define GL_IMAGE_CLASS_2_X_16 0x82bd
#define GL_IMAGE_CLASS_1_X_16 0x82be
#define GL_IMAGE_CLASS_4_X_8 0x82bf
#define GL_IMAGE_CLASS_2_X_8 0x82c0
#define GL_IMAGE_CLASS_1_X_8 0x82c1
#define GL_IMAGE_CLASS_11_11_10 0x82c2
#define GL_IMAGE_CLASS_10_10_10_2 0x82c3
#define GL_VIEW_CLASS_128_BITS 0x82c4
#define GL_VIEW_CLASS_96_BITS 0x82c5
#define GL_VIEW_CLASS_64_BITS 0x82c6
#define GL_VIEW_CLASS_48_BITS 0x82c7
#define GL_VIEW_CLASS_32_BITS 0x82c8
#define GL_VIEW_CLASS_24_BITS 0x82c9
#define GL_VIEW_CLASS_16_BITS 0x82ca
#define GL_VIEW_CLASS_8_BITS 0x82cb
#define GL_VIEW_CLASS_S3TC_DXT1_RGB 0x82cc
#define GL_VIEW_CLASS_S3TC_DXT1_RGBA 0x82cd
#define GL_VIEW_CLASS_S3TC_DXT3_RGBA 0x82ce
#define GL_VIEW_CLASS_S3TC_DXT5_RGBA 0x82cf
#define GL_VIEW_CLASS_RGTC1_RED 0x82d0
#define GL_VIEW_CLASS_RGTC2_RG 0x82d1
#define GL_VIEW_CLASS_BPTC_UNORM 0x82d2
#define GL_VIEW_CLASS_BPTC_FLOAT 0x82d3
#define GL_MIN_MAP_BUFFER_ALIGNMENT 0x90bc
#define GL_MAP_INVALIDATE_RANGE_BIT 0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT 0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT 0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT 0x0020
#define GL_MATRIX_PALETTE_ARB 0x8840
#define GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB 0x8841
#define GL_MAX_PALETTE_MATRICES_ARB 0x8842
#define GL_CURRENT_PALETTE_MATRIX_ARB 0x8843
#define GL_MATRIX_INDEX_ARRAY_ARB 0x8844
#define GL_CURRENT_MATRIX_INDEX_ARB 0x8845
#define GL_MATRIX_INDEX_ARRAY_SIZE_ARB 0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_ARB 0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_ARB 0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_ARB 0x8849
#define GL_MULTISAMPLE_ARB 0x809d
#define GL_SAMPLE_ALPHA_TO_COVERAGE_ARB 0x809e
#define GL_SAMPLE_ALPHA_TO_ONE_ARB 0x809f
#define GL_SAMPLE_COVERAGE_ARB 0x80a0
#define GL_SAMPLE_BUFFERS_ARB 0x80a8
#define GL_SAMPLES_ARB 0x80a9
#define GL_SAMPLE_COVERAGE_VALUE_ARB 0x80aa
#define GL_SAMPLE_COVERAGE_INVERT_ARB 0x80ab
#define GL_MULTISAMPLE_BIT_ARB 0x20000000
#define GL_TEXTURE0_ARB 0x84c0
#define GL_TEXTURE1_ARB 0x84c1
#define GL_TEXTURE2_ARB 0x84c2
#define GL_TEXTURE3_ARB 0x84c3
#define GL_TEXTURE4_ARB 0x84c4
#define GL_TEXTURE5_ARB 0x84c5
#define GL_TEXTURE6_ARB 0x84c6
#define GL_TEXTURE7_ARB 0x84c7
#define GL_TEXTURE8_ARB 0x84c8
#define GL_TEXTURE9_ARB 0x84c9
#define GL_TEXTURE10_ARB 0x84ca
#define GL_TEXTURE11_ARB 0x84cb
#define GL_TEXTURE12_ARB 0x84cc
#define GL_TEXTURE13_ARB 0x84cd
#define GL_TEXTURE14_ARB 0x84ce
#define GL_TEXTURE15_ARB 0x84cf
#define GL_TEXTURE16_ARB 0x84d0
#define GL_TEXTURE17_ARB 0x84d1
#define GL_TEXTURE18_ARB 0x84d2
#define GL_TEXTURE19_ARB 0x84d3
#define GL_TEXTURE20_ARB 0x84d4
#define GL_TEXTURE21_ARB 0x84d5
#define GL_TEXTURE22_ARB 0x84d6
#define GL_TEXTURE23_ARB 0x84d7
#define GL_TEXTURE24_ARB 0x84d8
#define GL_TEXTURE25_ARB 0x84d9
#define GL_TEXTURE26_ARB 0x84da
#define GL_TEXTURE27_ARB 0x84db
#define GL_TEXTURE28_ARB 0x84dc
#define GL_TEXTURE29_ARB 0x84dd
#define GL_TEXTURE30_ARB 0x84de
#define GL_TEXTURE31_ARB 0x84df
#define GL_ACTIVE_TEXTURE_ARB 0x84e0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB 0x84e1
#define GL_MAX_TEXTURE_UNITS_ARB 0x84e2
#define GL_QUERY_COUNTER_BITS_ARB 0x8864
#define GL_CURRENT_QUERY_ARB 0x8865
#define GL_QUERY_RESULT_ARB 0x8866
#define GL_QUERY_RESULT_AVAILABLE_ARB 0x8867
#define GL_SAMPLES_PASSED_ARB 0x8914
#define GL_ANY_SAMPLES_PASSED 0x8c2f
#define GL_MAX_SHADER_COMPILER_THREADS_ARB 0x91b0
#define GL_COMPLETION_STATUS_ARB 0x91b1
#define GL_VERTICES_SUBMITTED_ARB 0x82ee
#define GL_PRIMITIVES_SUBMITTED_ARB 0x82ef
#define GL_VERTEX_SHADER_INVOCATIONS_ARB 0x82f0
#define GL_TESS_CONTROL_SHADER_PATCHES_ARB 0x82f1
#define GL_TESS_EVALUATION_SHADER_INVOCATIONS_ARB 0x82f2
#define GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED_ARB 0x82f3
#define GL_FRAGMENT_SHADER_INVOCATIONS_ARB 0x82f4
#define GL_COMPUTE_SHADER_INVOCATIONS_ARB 0x82f5
#define GL_CLIPPING_INPUT_PRIMITIVES_ARB 0x82f6
#define GL_CLIPPING_OUTPUT_PRIMITIVES_ARB 0x82f7
#define GL_PIXEL_PACK_BUFFER_ARB 0x88eb
#define GL_PIXEL_UNPACK_BUFFER_ARB 0x88ec
#define GL_PIXEL_PACK_BUFFER_BINDING_ARB 0x88ed
#define GL_PIXEL_UNPACK_BUFFER_BINDING_ARB 0x88ef
#define GL_POINT_SIZE_MIN_ARB 0x8126
#define GL_POINT_SIZE_MAX_ARB 0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_ARB 0x8128
#define GL_POINT_DISTANCE_ATTENUATION_ARB 0x8129
#define GL_POINT_SPRITE_ARB 0x8861
#define GL_COORD_REPLACE_ARB 0x8862
#define GL_POLYGON_OFFSET_CLAMP 0x8e1b
#define GL_UNIFORM 0x92e1
#define GL_UNIFORM_BLOCK 0x92e2
#define GL_PROGRAM_INPUT 0x92e3
#define GL_PROGRAM_OUTPUT 0x92e4
#define GL_BUFFER_VARIABLE 0x92e5
#define GL_SHADER_STORAGE_BLOCK 0x92e6
#define GL_IS_PER_PATCH 0x92e7
#define GL_VERTEX_SUBROUTINE 0x92e8
#define GL_TESS_CONTROL_SUBROUTINE 0x92e9
#define GL_TESS_EVALUATION_SUBROUTINE 0x92ea
#define GL_GEOMETRY_SUBROUTINE 0x92eb
#define GL_FRAGMENT_SUBROUTINE 0x92ec
#define GL_COMPUTE_SUBROUTINE 0x92ed
#define GL_VERTEX_SUBROUTINE_UNIFORM 0x92ee
#define GL_TESS_CONTROL_SUBROUTINE_UNIFORM 0x92ef
#define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 0x92f0
#define GL_GEOMETRY_SUBROUTINE_UNIFORM 0x92f1
#define GL_FRAGMENT_SUBROUTINE_UNIFORM 0x92f2
#define GL_COMPUTE_SUBROUTINE_UNIFORM 0x92f3
#define GL_TRANSFORM_FEEDBACK_VARYING 0x92f4
#define GL_ACTIVE_RESOURCES 0x92f5
#define GL_MAX_NAME_LENGTH 0x92f6
#define GL_MAX_NUM_ACTIVE_VARIABLES 0x92f7
#define GL_MAX_NUM_COMPATIBLE_SUBROUTINES 0x92f8
#define GL_NAME_LENGTH 0x92f9
#define GL_TYPE 0x92fa
#define GL_ARRAY_SIZE 0x92fb
#define GL_OFFSET 0x92fc
#define GL_BLOCK_INDEX 0x92fd
#define GL_ARRAY_STRIDE 0x92fe
#define GL_MATRIX_STRIDE 0x92ff
#define GL_IS_ROW_MAJOR 0x9300
#define GL_ATOMIC_COUNTER_BUFFER_INDEX 0x9301
#define GL_BUFFER_BINDING 0x9302
#define GL_BUFFER_DATA_SIZE 0x9303
#define GL_NUM_ACTIVE_VARIABLES 0x9304
#define GL_ACTIVE_VARIABLES 0x9305
#define GL_REFERENCED_BY_VERTEX_SHADER 0x9306
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#define GL_REFERENCED_BY_GEOMETRY_SHADER 0x9309
#define GL_REFERENCED_BY_FRAGMENT_SHADER 0x930a
#define GL_REFERENCED_BY_COMPUTE_SHADER 0x930b
#define GL_TOP_LEVEL_ARRAY_SIZE 0x930c
#define GL_TOP_LEVEL_ARRAY_STRIDE 0x930d
#define GL_LOCATION 0x930e
#define GL_LOCATION_INDEX 0x930f
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8e4c
#define GL_FIRST_VERTEX_CONVENTION 0x8e4d
#define GL_LAST_VERTEX_CONVENTION 0x8e4e
#define GL_PROVOKING_VERTEX 0x8e4f
#define GL_QUERY_BUFFER_BARRIER_BIT 0x00008000
#define GL_QUERY_BUFFER 0x9192
#define GL_QUERY_BUFFER_BINDING 0x9193
#define GL_QUERY_RESULT_NO_WAIT 0x9194
#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB 0x00000004
#define GL_LOSE_CONTEXT_ON_RESET_ARB 0x8252
#define GL_GUILTY_CONTEXT_RESET_ARB 0x8253
#define GL_INNOCENT_CONTEXT_RESET_ARB 0x8254
#define GL_UNKNOWN_CONTEXT_RESET_ARB 0x8255
#define GL_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define GL_NO_RESET_NOTIFICATION_ARB 0x8261
#define GL_SAMPLE_LOCATION_ARB 0x8e50
#define GL_SAMPLE_LOCATION_SUBPIXEL_BITS_ARB 0x933d
#define GL_SAMPLE_LOCATION_PIXEL_GRID_WIDTH_ARB 0x933e
#define GL_SAMPLE_LOCATION_PIXEL_GRID_HEIGHT_ARB 0x933f
#define GL_PROGRAMMABLE_SAMPLE_LOCATION_TABLE_SIZE_ARB 0x9340
#define GL_PROGRAMMABLE_SAMPLE_LOCATION_ARB 0x9341
#define GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_ARB 0x9342
#define GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_ARB 0x9343
#define GL_SAMPLE_SHADING_ARB 0x8c36
#define GL_MIN_SAMPLE_SHADING_VALUE_ARB 0x8c37
#define GL_SAMPLER_BINDING 0x8919
#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884f
#define GL_VERTEX_SHADER_BIT 0x00000001
#define GL_FRAGMENT_SHADER_BIT 0x00000002
#define GL_GEOMETRY_SHADER_BIT 0x00000004
#define GL_TESS_CONTROL_SHADER_BIT 0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT 0x00000010
#define GL_PROGRAM_SEPARABLE 0x8258
#define GL_ACTIVE_PROGRAM 0x8259
#define GL_PROGRAM_PIPELINE_BINDING 0x825a
#define GL_ALL_SHADER_BITS 0xffffffff
#define GL_ATOMIC_COUNTER_BUFFER 0x92c0
#define GL_ATOMIC_COUNTER_BUFFER_BINDING 0x92c1
#define GL_ATOMIC_COUNTER_BUFFER_START 0x92c2
#define GL_ATOMIC_COUNTER_BUFFER_SIZE 0x92c3
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 0x92c4
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 0x92c5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 0x92c6
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 0x92c7
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 0x92c8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92c9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 0x92ca
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 0x92cb
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92cc
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92cd
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92ce
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92cf
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92d0
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92d1
#define GL_MAX_VERTEX_ATOMIC_COUNTERS 0x92d2
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92d3
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92d4
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS 0x92d5
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS 0x92d6
#define GL_MAX_COMBINED_ATOMIC_COUNTERS 0x92d7
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92d8
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS 0x92d9
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 0x92da
#define GL_UNSIGNED_INT_ATOMIC_COUNTER 0x92db
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92dc
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT 0x00000002
#define GL_UNIFORM_BARRIER_BIT 0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT 0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#define GL_COMMAND_BARRIER_BIT 0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT 0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT 0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT 0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT 0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT 0x00001000
#define GL_MAX_IMAGE_UNITS 0x8f38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8f39
#define GL_IMAGE_BINDING_NAME 0x8f3a
#define GL_IMAGE_BINDING_LEVEL 0x8f3b
#define GL_IMAGE_BINDING_LAYERED 0x8f3c
#define GL_IMAGE_BINDING_LAYER 0x8f3d
#define GL_IMAGE_BINDING_ACCESS 0x8f3e
#define GL_IMAGE_1D 0x904c
#define GL_IMAGE_2D 0x904d
#define GL_IMAGE_3D 0x904e
#define GL_IMAGE_2D_RECT 0x904f
#define GL_IMAGE_CUBE 0x9050
#define GL_IMAGE_BUFFER 0x9051
#define GL_IMAGE_1D_ARRAY 0x9052
#define GL_IMAGE_2D_ARRAY 0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY 0x9054
#define GL_IMAGE_2D_MULTISAMPLE 0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY 0x9056
#define GL_INT_IMAGE_1D 0x9057
#define GL_INT_IMAGE_2D 0x9058
#define GL_INT_IMAGE_3D 0x9059
#define GL_INT_IMAGE_2D_RECT 0x905a
#define GL_INT_IMAGE_CUBE 0x905b
#define GL_INT_IMAGE_BUFFER 0x905c
#define GL_INT_IMAGE_1D_ARRAY 0x905d
#define GL_INT_IMAGE_2D_ARRAY 0x905e
#define GL_INT_IMAGE_CUBE_MAP_ARRAY 0x905f
#define GL_INT_IMAGE_2D_MULTISAMPLE 0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x9061
#define GL_UNSIGNED_INT_IMAGE_1D 0x9062
#define GL_UNSIGNED_INT_IMAGE_2D 0x9063
#define GL_UNSIGNED_INT_IMAGE_3D 0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT 0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE 0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER 0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY 0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY 0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906a
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 0x906b
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x906c
#define GL_MAX_IMAGE_SAMPLES 0x906d
#define GL_IMAGE_BINDING_FORMAT 0x906e
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90c7
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90c8
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90c9
#define GL_MAX_VERTEX_IMAGE_UNIFORMS 0x90ca
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90cb
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90cc
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS 0x90cd
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS 0x90ce
#define GL_MAX_COMBINED_IMAGE_UNIFORMS 0x90cf
#define GL_ALL_BARRIER_BITS 0xffffffff
#define GL_PROGRAM_OBJECT_ARB 0x8b40
#define GL_SHADER_OBJECT_ARB 0x8b48
#define GL_OBJECT_TYPE_ARB 0x8b4e
#define GL_OBJECT_SUBTYPE_ARB 0x8b4f
#define GL_FLOAT_VEC2_ARB 0x8b50
#define GL_FLOAT_VEC3_ARB 0x8b51
#define GL_FLOAT_VEC4_ARB 0x8b52
#define GL_INT_VEC2_ARB 0x8b53
#define GL_INT_VEC3_ARB 0x8b54
#define GL_INT_VEC4_ARB 0x8b55
#define GL_BOOL_ARB 0x8b56
#define GL_BOOL_VEC2_ARB 0x8b57
#define GL_BOOL_VEC3_ARB 0x8b58
#define GL_BOOL_VEC4_ARB 0x8b59
#define GL_FLOAT_MAT2_ARB 0x8b5a
#define GL_FLOAT_MAT3_ARB 0x8b5b
#define GL_FLOAT_MAT4_ARB 0x8b5c
#define GL_SAMPLER_1D_ARB 0x8b5d
#define GL_SAMPLER_2D_ARB 0x8b5e
#define GL_SAMPLER_3D_ARB 0x8b5f
#define GL_SAMPLER_CUBE_ARB 0x8b60
#define GL_SAMPLER_1D_SHADOW_ARB 0x8b61
#define GL_SAMPLER_2D_SHADOW_ARB 0x8b62
#define GL_SAMPLER_2D_RECT_ARB 0x8b63
#define GL_SAMPLER_2D_RECT_SHADOW_ARB 0x8b64
#define GL_OBJECT_DELETE_STATUS_ARB 0x8b80
#define GL_OBJECT_COMPILE_STATUS_ARB 0x8b81
#define GL_OBJECT_LINK_STATUS_ARB 0x8b82
#define GL_OBJECT_VALIDATE_STATUS_ARB 0x8b83
#define GL_OBJECT_INFO_LOG_LENGTH_ARB 0x8b84
#define GL_OBJECT_ATTACHED_OBJECTS_ARB 0x8b85
#define GL_OBJECT_ACTIVE_UNIFORMS_ARB 0x8b86
#define GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB 0x8b87
#define GL_OBJECT_SHADER_SOURCE_LENGTH_ARB 0x8b88
#define GL_SHADER_STORAGE_BARRIER_BIT 0x2000
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8f39
#define GL_SHADER_STORAGE_BUFFER 0x90d2
#define GL_SHADER_STORAGE_BUFFER_BINDING 0x90d3
#define GL_SHADER_STORAGE_BUFFER_START 0x90d4
#define GL_SHADER_STORAGE_BUFFER_SIZE 0x90d5
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90d6
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90d7
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90d8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90d9
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90da
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90db
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90dc
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90dd
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE 0x90de
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90df
#define GL_ACTIVE_SUBROUTINES 0x8de5
#define GL_ACTIVE_SUBROUTINE_UNIFORMS 0x8de6
#define GL_MAX_SUBROUTINES 0x8de7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8de8
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8e47
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH 0x8e48
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8e49
#define GL_NUM_COMPATIBLE_SUBROUTINES 0x8e4a
#define GL_COMPATIBLE_SUBROUTINES 0x8e4b
#define GL_SHADING_LANGUAGE_VERSION_ARB 0x8b8c
#define GL_SHADER_INCLUDE_ARB 0x8dae
#define GL_NAMED_STRING_LENGTH_ARB 0x8de9
#define GL_NAMED_STRING_TYPE_ARB 0x8dea
#define GL_TEXTURE_COMPARE_MODE_ARB 0x884c
#define GL_TEXTURE_COMPARE_FUNC_ARB 0x884d
#define GL_COMPARE_R_TO_TEXTURE_ARB 0x884e
#define GL_TEXTURE_COMPARE_FAIL_VALUE_ARB 0x80bf
#define GL_SPARSE_STORAGE_BIT_ARB 0x0400
#define GL_SPARSE_BUFFER_PAGE_SIZE_ARB 0x82f8
#define GL_VIRTUAL_PAGE_SIZE_X_ARB 0x9195
#define GL_VIRTUAL_PAGE_SIZE_Y_ARB 0x9196
#define GL_VIRTUAL_PAGE_SIZE_Z_ARB 0x9197
#define GL_MAX_SPARSE_TEXTURE_SIZE_ARB 0x9198
#define GL_MAX_SPARSE_3D_TEXTURE_SIZE_ARB 0x9199
#define GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_ARB 0x919a
#define GL_TEXTURE_SPARSE_ARB 0x91a6
#define GL_VIRTUAL_PAGE_SIZE_INDEX_ARB 0x91a7
#define GL_NUM_VIRTUAL_PAGE_SIZES_ARB 0x91a8
#define GL_SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_ARB 0x91a9
#define GL_NUM_SPARSE_LEVELS_ARB 0x91aa
#define GL_SPIR_V_EXTENSIONS 0x9553
#define GL_NUM_SPIR_V_EXTENSIONS 0x9554
#define GL_DEPTH_STENCIL_TEXTURE_MODE 0x90ea
#define GL_SYNC_FLUSH_COMMANDS_BIT 0x00000001
#define GL_MAX_SERVER_WAIT_TIMEOUT 0x9111
#define GL_OBJECT_TYPE 0x9112
#define GL_SYNC_CONDITION 0x9113
#define GL_SYNC_STATUS 0x9114
#define GL_SYNC_FLAGS 0x9115
#define GL_SYNC_FENCE 0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE 0x9117
#define GL_UNSIGNALED 0x9118
#define GL_SIGNALED 0x9119
#define GL_ALREADY_SIGNALED 0x911a
#define GL_TIMEOUT_EXPIRED 0x911b
#define GL_CONDITION_SATISFIED 0x911c
#define GL_WAIT_FAILED 0x911d
#define GL_TIMEOUT_IGNORED 0xffffffffffffffffull
#define GL_PATCHES 0xe
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84f0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84f1
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886c
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886d
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8e1e
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8e1f
#define GL_PATCH_VERTICES 0x8e72
#define GL_PATCH_DEFAULT_INNER_LEVEL 0x8e73
#define GL_PATCH_DEFAULT_OUTER_LEVEL 0x8e74
#define GL_TESS_CONTROL_OUTPUT_VERTICES 0x8e75
#define GL_TESS_GEN_MODE 0x8e76
#define GL_TESS_GEN_SPACING 0x8e77
#define GL_TESS_GEN_VERTEX_ORDER 0x8e78
#define GL_TESS_GEN_POINT_MODE 0x8e79
#define GL_ISOLINES 0x8e7a
#define GL_FRACTIONAL_ODD 0x8e7b
#define GL_FRACTIONAL_EVEN 0x8e7c
#define GL_MAX_PATCH_VERTICES 0x8e7d
#define GL_MAX_TESS_GEN_LEVEL 0x8e7e
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8e7f
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8e80
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8e81
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8e82
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8e83
#define GL_MAX_TESS_PATCH_COMPONENTS 0x8e84
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8e85
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8e86
#define GL_TESS_EVALUATION_SHADER 0x8e87
#define GL_TESS_CONTROL_SHADER 0x8e88
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8e89
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8e8a
#define GL_CLAMP_TO_BORDER_ARB 0x812d
#define GL_TEXTURE_BUFFER_ARB 0x8c2a
#define GL_MAX_TEXTURE_BUFFER_SIZE_ARB 0x8c2b
#define GL_TEXTURE_BINDING_BUFFER_ARB 0x8c2c
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING_ARB 0x8c2d
#define GL_TEXTURE_BUFFER_FORMAT_ARB 0x8c2e
#define GL_TEXTURE_BUFFER_OFFSET 0x919d
#define GL_TEXTURE_BUFFER_SIZE 0x919e
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919f
#define GL_COMPRESSED_ALPHA_ARB 0x84e9
#define GL_COMPRESSED_LUMINANCE_ARB 0x84ea
#define GL_COMPRESSED_LUMINANCE_ALPHA_ARB 0x84eb
#define GL_COMPRESSED_INTENSITY_ARB 0x84ec
#define GL_COMPRESSED_RGB_ARB 0x84ed
#define GL_COMPRESSED_RGBA_ARB 0x84ee
#define GL_TEXTURE_COMPRESSION_HINT_ARB 0x84ef
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB 0x86a0
#define GL_TEXTURE_COMPRESSED_ARB 0x86a1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB 0x86a2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB 0x86a3
#define GL_COMPRESSED_RGBA_BPTC_UNORM_ARB 0x8e8c
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB 0x8e8d
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB 0x8e8e
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB 0x8e8f
#define GL_COMPRESSED_RED_RGTC1 0x8dbb
#define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8dbc
#define GL_COMPRESSED_RG_RGTC2 0x8dbd
#define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8dbe
#define GL_NORMAL_MAP_ARB 0x8511
#define GL_REFLECTION_MAP_ARB 0x8512
#define GL_TEXTURE_CUBE_MAP_ARB 0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB 0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB 0x851a
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB 0x851b
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB 0x851c
#define GL_TEXTURE_CUBE_MAP_ARRAY_ARB 0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_ARB 0x900a
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY_ARB 0x900b
#define GL_SAMPLER_CUBE_MAP_ARRAY_ARB 0x900c
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_ARB 0x900d
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY_ARB 0x900e
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_ARB 0x900f
#define GL_SUBTRACT_ARB 0x84e7
#define GL_COMBINE_ARB 0x8570
#define GL_COMBINE_RGB_ARB 0x8571
#define GL_COMBINE_ALPHA_ARB 0x8572
#define GL_RGB_SCALE_ARB 0x8573
#define GL_ADD_SIGNED_ARB 0x8574
#define GL_INTERPOLATE_ARB 0x8575
#define GL_CONSTANT_ARB 0x8576
#define GL_PRIMARY_COLOR_ARB 0x8577
#define GL_PREVIOUS_ARB 0x8578
#define GL_SOURCE0_RGB_ARB 0x8580
#define GL_SOURCE1_RGB_ARB 0x8581
#define GL_SOURCE2_RGB_ARB 0x8582
#define GL_SOURCE0_ALPHA_ARB 0x8588
#define GL_SOURCE1_ALPHA_ARB 0x8589
#define GL_SOURCE2_ALPHA_ARB 0x858a
#define GL_OPERAND0_RGB_ARB 0x8590
#define GL_OPERAND1_RGB_ARB 0x8591
#define GL_OPERAND2_RGB_ARB 0x8592
#define GL_OPERAND0_ALPHA_ARB 0x8598
#define GL_OPERAND1_ALPHA_ARB 0x8599
#define GL_OPERAND2_ALPHA_ARB 0x859a
#define GL_DOT3_RGB_ARB 0x86ae
#define GL_DOT3_RGBA_ARB 0x86af
#define GL_TEXTURE_MAX_ANISOTROPY 0x84fe
#define GL_MAX_TEXTURE_MAX_ANISOTROPY 0x84ff
#define GL_TEXTURE_REDUCTION_MODE_ARB 0x9366
#define GL_WEIGHTED_AVERAGE_ARB 0x9367
#define GL_RGBA32F_ARB 0x8814
#define GL_RGB32F_ARB 0x8815
#define GL_ALPHA32F_ARB 0x8816
#define GL_INTENSITY32F_ARB 0x8817
#define GL_LUMINANCE32F_ARB 0x8818
#define GL_LUMINANCE_ALPHA32F_ARB 0x8819
#define GL_RGBA16F_ARB 0x881a
#define GL_RGB16F_ARB 0x881b
#define GL_ALPHA16F_ARB 0x881c
#define GL_INTENSITY16F_ARB 0x881d
#define GL_LUMINANCE16F_ARB 0x881e
#define GL_LUMINANCE_ALPHA16F_ARB 0x881f
#define GL_TEXTURE_RED_TYPE_ARB 0x8c10
#define GL_TEXTURE_GREEN_TYPE_ARB 0x8c11
#define GL_TEXTURE_BLUE_TYPE_ARB 0x8c12
#define GL_TEXTURE_ALPHA_TYPE_ARB 0x8c13
#define GL_TEXTURE_LUMINANCE_TYPE_ARB 0x8c14
#define GL_TEXTURE_INTENSITY_TYPE_ARB 0x8c15
#define GL_TEXTURE_DEPTH_TYPE_ARB 0x8c16
#define GL_UNSIGNED_NORMALIZED_ARB 0x8c17
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB 0x8e5e
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_ARB 0x8e5f
#define GL_MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS_ARB 0x8f9f
#define GL_MIRROR_CLAMP_TO_EDGE 0x8743
#define GL_MIRRORED_REPEAT_ARB 0x8370
#define GL_SAMPLE_POSITION 0x8e50
#define GL_SAMPLE_MASK 0x8e51
#define GL_SAMPLE_MASK_VALUE 0x8e52
#define GL_MAX_SAMPLE_MASK_WORDS 0x8e59
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE 0x9101
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_SAMPLES 0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_SAMPLER_2D_MULTISAMPLE 0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE 0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910a
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910b
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910c
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910d
#define GL_MAX_COLOR_TEXTURE_SAMPLES 0x910e
#define GL_MAX_DEPTH_TEXTURE_SAMPLES 0x910f
#define GL_MAX_INTEGER_SAMPLES 0x9110
#define GL_TEXTURE_RECTANGLE_ARB 0x84f5
#define GL_TEXTURE_BINDING_RECTANGLE_ARB 0x84f6
#define GL_PROXY_TEXTURE_RECTANGLE_ARB 0x84f7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB 0x84f8
#define GL_COMPRESSED_RED 0x8225
#define GL_COMPRESSED_RG 0x8226
#define GL_RG 0x8227
#define GL_RG_INTEGER 0x8228
#define GL_R8 0x8229
#define GL_R16 0x822a
#define GL_RG8 0x822b
#define GL_RG16 0x822c
#define GL_R16F 0x822d
#define GL_R32F 0x822e
#define GL_RG16F 0x822f
#define GL_RG32F 0x8230
#define GL_R8I 0x8231
#define GL_R8UI 0x8232
#define GL_R16I 0x8233
#define GL_R16UI 0x8234
#define GL_R32I 0x8235
#define GL_R32UI 0x8236
#define GL_RG8I 0x8237
#define GL_RG8UI 0x8238
#define GL_RG16I 0x8239
#define GL_RG16UI 0x823a
#define GL_RG32I 0x823b
#define GL_RG32UI 0x823c
#define GL_RGB10_A2UI 0x906f
#define GL_STENCIL_INDEX 0x1901
#define GL_STENCIL_INDEX8 0x8d48
#define GL_TEXTURE_IMMUTABLE_FORMAT 0x912f
#define GL_TEXTURE_SWIZZLE_R 0x8e42
#define GL_TEXTURE_SWIZZLE_G 0x8e43
#define GL_TEXTURE_SWIZZLE_B 0x8e44
#define GL_TEXTURE_SWIZZLE_A 0x8e45
#define GL_TEXTURE_SWIZZLE_RGBA 0x8e46
#define GL_TEXTURE_VIEW_MIN_LEVEL 0x82db
#define GL_TEXTURE_VIEW_NUM_LEVELS 0x82dc
#define GL_TEXTURE_VIEW_MIN_LAYER 0x82dd
#define GL_TEXTURE_VIEW_NUM_LAYERS 0x82de
#define GL_TIME_ELAPSED 0x88bf
#define GL_TIMESTAMP 0x8e28
#define GL_TRANSFORM_FEEDBACK 0x8e22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8e23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8e24
#define GL_TRANSFORM_FEEDBACK_BINDING 0x8e25
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8e70
#define GL_TRANSFORM_FEEDBACK_OVERFLOW_ARB 0x82ec
#define GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW_ARB 0x82ed
#define GL_TRANSPOSE_MODELVIEW_MATRIX_ARB 0x84e3
#define GL_TRANSPOSE_PROJECTION_MATRIX_ARB 0x84e4
#define GL_TRANSPOSE_TEXTURE_MATRIX_ARB 0x84e5
#define GL_TRANSPOSE_COLOR_MATRIX_ARB 0x84e6
#define GL_UNIFORM_BUFFER 0x8a11
#define GL_UNIFORM_BUFFER_BINDING 0x8a28
#define GL_UNIFORM_BUFFER_START 0x8a29
#define GL_UNIFORM_BUFFER_SIZE 0x8a2a
#define GL_MAX_VERTEX_UNIFORM_BLOCKS 0x8a2b
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS 0x8a2c
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS 0x8a2d
#define GL_MAX_COMBINED_UNIFORM_BLOCKS 0x8a2e
#define GL_MAX_UNIFORM_BUFFER_BINDINGS 0x8a2f
#define GL_MAX_UNIFORM_BLOCK_SIZE 0x8a30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8a31
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8a32
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8a33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8a34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8a35
#define GL_ACTIVE_UNIFORM_BLOCKS 0x8a36
#define GL_UNIFORM_TYPE 0x8a37
#define GL_UNIFORM_SIZE 0x8a38
#define GL_UNIFORM_NAME_LENGTH 0x8a39
#define GL_UNIFORM_BLOCK_INDEX 0x8a3a
#define GL_UNIFORM_OFFSET 0x8a3b
#define GL_UNIFORM_ARRAY_STRIDE 0x8a3c
#define GL_UNIFORM_MATRIX_STRIDE 0x8a3d
#define GL_UNIFORM_IS_ROW_MAJOR 0x8a3e
#define GL_UNIFORM_BLOCK_BINDING 0x8a3f
#define GL_UNIFORM_BLOCK_DATA_SIZE 0x8a40
#define GL_UNIFORM_BLOCK_NAME_LENGTH 0x8a41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8a42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8a43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8a44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8a45
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8a46
#define GL_INVALID_INDEX 0xffffffffu
#define GL_BGRA 0x80e1
#define GL_VERTEX_ARRAY_BINDING 0x85b5
#define GL_VERTEX_ATTRIB_BINDING 0x82d4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82d5
#define GL_VERTEX_BINDING_DIVISOR 0x82d6
#define GL_VERTEX_BINDING_OFFSET 0x82d7
#define GL_VERTEX_BINDING_STRIDE 0x82d8
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82d9
#define GL_MAX_VERTEX_ATTRIB_BINDINGS 0x82da
#define GL_VERTEX_BINDING_BUFFER 0x8f4f
#define GL_MODELVIEW0_ARB 0x1700
#define GL_MODELVIEW1_ARB 0x850a
#define GL_MAX_VERTEX_UNITS_ARB 0x86a4
#define GL_ACTIVE_VERTEX_UNITS_ARB 0x86a5
#define GL_WEIGHT_SUM_UNITY_ARB 0x86a6
#define GL_VERTEX_BLEND_ARB 0x86a7
#define GL_CURRENT_WEIGHT_ARB 0x86a8
#define GL_WEIGHT_ARRAY_TYPE_ARB 0x86a9
#define GL_WEIGHT_ARRAY_STRIDE_ARB 0x86aa
#define GL_WEIGHT_ARRAY_SIZE_ARB 0x86ab
#define GL_WEIGHT_ARRAY_POINTER_ARB 0x86ac
#define GL_WEIGHT_ARRAY_ARB 0x86ad
#define GL_MODELVIEW2_ARB 0x8722
#define GL_MODELVIEW3_ARB 0x8723
#define GL_MODELVIEW4_ARB 0x8724
#define GL_MODELVIEW5_ARB 0x8725
#define GL_MODELVIEW6_ARB 0x8726
#define GL_MODELVIEW7_ARB 0x8727
#define GL_MODELVIEW8_ARB 0x8728
#define GL_MODELVIEW9_ARB 0x8729
#define GL_MODELVIEW10_ARB 0x872a
#define GL_MODELVIEW11_ARB 0x872b
#define GL_MODELVIEW12_ARB 0x872c
#define GL_MODELVIEW13_ARB 0x872d
#define GL_MODELVIEW14_ARB 0x872e
#define GL_MODELVIEW15_ARB 0x872f
#define GL_MODELVIEW16_ARB 0x8730
#define GL_MODELVIEW17_ARB 0x8731
#define GL_MODELVIEW18_ARB 0x8732
#define GL_MODELVIEW19_ARB 0x8733
#define GL_MODELVIEW20_ARB 0x8734
#define GL_MODELVIEW21_ARB 0x8735
#define GL_MODELVIEW22_ARB 0x8736
#define GL_MODELVIEW23_ARB 0x8737
#define GL_MODELVIEW24_ARB 0x8738
#define GL_MODELVIEW25_ARB 0x8739
#define GL_MODELVIEW26_ARB 0x873a
#define GL_MODELVIEW27_ARB 0x873b
#define GL_MODELVIEW28_ARB 0x873c
#define GL_MODELVIEW29_ARB 0x873d
#define GL_MODELVIEW30_ARB 0x873e
#define GL_MODELVIEW31_ARB 0x873f
#define GL_BUFFER_SIZE_ARB 0x8764
#define GL_BUFFER_USAGE_ARB 0x8765
#define GL_ARRAY_BUFFER_ARB 0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB 0x8893
#define GL_ARRAY_BUFFER_BINDING_ARB 0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB 0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB 0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB 0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB 0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB 0x8899
#define GL_GEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB 0x889a
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB 0x889b
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB 0x889c
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB 0x889d
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB 0x889e
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB 0x889f
#define GL_READ_ONLY_ARB 0x88b8
#define GL_WRITE_ONLY_ARB 0x88b9
#define GL_READ_WRITE_ARB 0x88ba
#define GL_BUFFER_ACCESS_ARB 0x88bb
#define GL_BUFFER_MAPPED_ARB 0x88bc
#define GL_BUFFER_MAP_POINTER_ARB 0x88bd
#define GL_STREAM_DRAW_ARB 0x88e0
#define GL_STREAM_READ_ARB 0x88e1
#define GL_STREAM_COPY_ARB 0x88e2
#define GL_STATIC_DRAW_ARB 0x88e4
#define GL_STATIC_READ_ARB 0x88e5
#define GL_STATIC_COPY_ARB 0x88e6
#define GL_DYNAMIC_DRAW_ARB 0x88e8
#define GL_DYNAMIC_READ_ARB 0x88e9
#define GL_DYNAMIC_COPY_ARB 0x88ea
#define GL_COLOR_SUM_ARB 0x8458
#define GL_VERTEX_PROGRAM_ARB 0x8620
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB 0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB 0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB 0x8625
#define GL_CURRENT_VERTEX_ATTRIB_ARB 0x8626
#define GL_PROGRAM_LENGTH_ARB 0x8627
#define GL_PROGRAM_STRING_ARB 0x8628
#define GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB 0x862e
#define GL_MAX_PROGRAM_MATRICES_ARB 0x862f
#define GL_CURRENT_MATRIX_STACK_DEPTH_ARB 0x8640
#define GL_CURRENT_MATRIX_ARB 0x8641
#define GL_VERTEX_PROGRAM_POINT_SIZE_ARB 0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_ARB 0x8643
#define GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB 0x8645
#define GL_PROGRAM_ERROR_POSITION_ARB 0x864b
#define GL_PROGRAM_BINDING_ARB 0x8677
#define GL_MAX_VERTEX_ATTRIBS_ARB 0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB 0x886a
#define GL_PROGRAM_ERROR_STRING_ARB 0x8874
#define GL_PROGRAM_FORMAT_ASCII_ARB 0x8875
#define GL_PROGRAM_FORMAT_ARB 0x8876
#define GL_PROGRAM_INSTRUCTIONS_ARB 0x88a0
#define GL_MAX_PROGRAM_INSTRUCTIONS_ARB 0x88a1
#define GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB 0x88a2
#define GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB 0x88a3
#define GL_PROGRAM_TEMPORARIES_ARB 0x88a4
#define GL_MAX_PROGRAM_TEMPORARIES_ARB 0x88a5
#define GL_PROGRAM_NATIVE_TEMPORARIES_ARB 0x88a6
#define GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB 0x88a7
#define GL_PROGRAM_PARAMETERS_ARB 0x88a8
#define GL_MAX_PROGRAM_PARAMETERS_ARB 0x88a9
#define GL_PROGRAM_NATIVE_PARAMETERS_ARB 0x88aa
#define GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB 0x88ab
#define GL_PROGRAM_ATTRIBS_ARB 0x88ac
#define GL_MAX_PROGRAM_ATTRIBS_ARB 0x88ad
#define GL_PROGRAM_NATIVE_ATTRIBS_ARB 0x88ae
#define GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB 0x88af
#define GL_PROGRAM_ADDRESS_REGISTERS_ARB 0x88b0
#define GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB 0x88b1
#define GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB 0x88b2
#define GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB 0x88b3
#define GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB 0x88b4
#define GL_MAX_PROGRAM_ENV_PARAMETERS_ARB 0x88b5
#define GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB 0x88b6
#define GL_TRANSPOSE_CURRENT_MATRIX_ARB 0x88b7
#define GL_MATRIX0_ARB 0x88c0
#define GL_MATRIX1_ARB 0x88c1
#define GL_MATRIX2_ARB 0x88c2
#define GL_MATRIX3_ARB 0x88c3
#define GL_MATRIX4_ARB 0x88c4
#define GL_MATRIX5_ARB 0x88c5
#define GL_MATRIX6_ARB 0x88c6
#define GL_MATRIX7_ARB 0x88c7
#define GL_MATRIX8_ARB 0x88c8
#define GL_MATRIX9_ARB 0x88c9
#define GL_MATRIX10_ARB 0x88ca
#define GL_MATRIX11_ARB 0x88cb
#define GL_MATRIX12_ARB 0x88cc
#define GL_MATRIX13_ARB 0x88cd
#define GL_MATRIX14_ARB 0x88ce
#define GL_MATRIX15_ARB 0x88cf
#define GL_MATRIX16_ARB 0x88d0
#define GL_MATRIX17_ARB 0x88d1
#define GL_MATRIX18_ARB 0x88d2
#define GL_MATRIX19_ARB 0x88d3
#define GL_MATRIX20_ARB 0x88d4
#define GL_MATRIX21_ARB 0x88d5
#define GL_MATRIX22_ARB 0x88d6
#define GL_MATRIX23_ARB 0x88d7
#define GL_MATRIX24_ARB 0x88d8
#define GL_MATRIX25_ARB 0x88d9
#define GL_MATRIX26_ARB 0x88da
#define GL_MATRIX27_ARB 0x88db
#define GL_MATRIX28_ARB 0x88dc
#define GL_MATRIX29_ARB 0x88dd
#define GL_MATRIX30_ARB 0x88de
#define GL_MATRIX31_ARB 0x88df

#define GL_VERTEX_SHADER_ARB 0x8b31
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB 0x8b4a
#define GL_MAX_VARYING_FLOATS_ARB 0x8b4b
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB 0x8b4c
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB 0x8b4d
#define GL_OBJECT_ACTIVE_ATTRIBUTES_ARB 0x8b89
#define GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB 0x8b8a

#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8c3b

#define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368
#define GL_INT_2_10_10_10_REV 0x8d9f

#define GL_DEPTH_RANGE 0x0b70
#define GL_VIEWPORT 0x0ba2
#define GL_SCISSOR_BOX 0x0c10
#define GL_SCISSOR_TEST 0x0c11
#define GL_MAX_VIEWPORTS 0x825b
#define GL_VIEWPORT_SUBPIXEL_BITS 0x825c
#define GL_VIEWPORT_BOUNDS_RANGE 0x825d
#define GL_LAYER_PROVOKING_VERTEX 0x825e
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825f
#define GL_UNDEFINED_VERTEX 0x8260
#define GL_FIRST_VERTEX_CONVENTION 0x8e4d
#define GL_LAST_VERTEX_CONVENTION 0x8e4e
#define GL_PROVOKING_VERTEX 0x8e4f

	//ES2 compatibility
	inline void (*glClearDepthf) (GLclampf d) = nullptr;
	inline void (*glDepthRangef) (GLclampf n, GLclampf f) = nullptr;
	inline void (*glGetShaderPrecisionFormat) (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) = nullptr;
	inline void (*glReleaseShaderCompiler) (void) = nullptr;
	inline void (*glShaderBinary) (GLsizei count, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length) = nullptr;

#define ARB_ES2_compatibility 1

	//ES3 1 compatibility
	inline void (*glMemoryBarrierByRegion) (GLbitfield barriers) = nullptr;
#define ARB_ES3_1_compatibility 1

	//ES3 2 compatibility
	inline void (*glPrimitiveBoundingBoxARB) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW) = nullptr;
#define ARB_ES3_2_compatibility 1

	//ES3 compatibility
#define ARB_ES3_compatibility 1

	//arrays of arrays
#define ARB_arrays_of_arrays 1

	//base instance
	inline void (*glDrawArraysInstancedBaseInstance) (GLenum mode, GLint first, GLsizei count, GLsizei primcount, GLuint baseinstance) = nullptr;
	inline void (*glDrawElementsInstancedBaseInstance) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount, GLuint baseinstance) = nullptr;
	inline void (*glDrawElementsInstancedBaseVertexBaseInstance) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount, GLint basevertex, GLuint baseinstance) = nullptr;
#define ARB_base_instance 1

	//bindless texture
	inline GLuint64(*glGetImageHandleARB) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format) = nullptr;
	inline GLuint64(*glGetTextureHandleARB) (GLuint texture) = nullptr;
	inline GLuint64(*glGetTextureSamplerHandleARB) (GLuint texture, GLuint sampler) = nullptr;
	inline void (*glGetVertexAttribLui64vARB) (GLuint index, GLenum pname, GLuint64EXT* params) = nullptr;
	inline GLboolean(*glIsImageHandleResidentARB) (GLuint64 handle) = nullptr;
	inline GLboolean(*glIsTextureHandleResidentARB) (GLuint64 handle) = nullptr;
	inline void (*glMakeImageHandleNonResidentARB) (GLuint64 handle) = nullptr;
	inline void (*glMakeImageHandleResidentARB) (GLuint64 handle, GLenum access) = nullptr;
	inline void (*glMakeTextureHandleNonResidentARB) (GLuint64 handle) = nullptr;
	inline void (*glMakeTextureHandleResidentARB) (GLuint64 handle) = nullptr;
	inline void (*glProgramUniformHandleui64ARB) (GLuint program, GLint location, GLuint64 value) = nullptr;
	inline void (*glProgramUniformHandleui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* values) = nullptr;
	inline void (*glUniformHandleui64ARB) (GLint location, GLuint64 value) = nullptr;
	inline void (*glUniformHandleui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
	inline void (*glVertexAttribL1ui64ARB) (GLuint index, GLuint64EXT x) = nullptr;
	inline void (*glVertexAttribL1ui64vARB) (GLuint index, const GLuint64EXT* v) = nullptr;
#define ARB_bindless_texture 1

	//blend func extended
	inline void (*glBindFragDataLocationIndexed) (GLuint program, GLuint colorNumber, GLuint index, const GLchar * name) = nullptr;
	inline GLint(*glGetFragDataIndex) (GLuint program, const GLchar* name) = nullptr;
#define ARB_blend_func_extended 1

	//buffer storage
	inline void(*glBufferStorage) (GLenum target, GLsizeiptr size, const void* data, GLbitfield flags) = nullptr;
#define ARB_buffer_storage 1

	//cl event
	//inline GLsync(*glCreateSyncFromCLeventARB) (cl_context context, cl_event event, GLbitfield flags) = nullptr;
#define ARB_cl_event 1

	//clear buffer object
	inline void(*glClearBufferData) (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glClearBufferSubData) (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glClearNamedBufferDataEXT) (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glClearNamedBufferSubDataEXT) (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) = nullptr;
#define ARB_clear_buffer_object 1

	//clear texture
	inline void(*glClearTexImage) (GLuint texture, GLint level, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glClearTexSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data) = nullptr;
#define ARB_clear_texture 1

	//clip control
	inline void(*glClipControl) (GLenum origin, GLenum depth) = nullptr;
#define ARB_clip_control 1

	//color buffer float
	inline void(*glClampColorARB) (GLenum target, GLenum clamp) = nullptr;
#define ARB_color_buffer_float 1

	//compatibility
#define ARB_compatibility 1

	//compressed texture pixel storage
#define ARB_compressed_texture_pixel_storage 1

	//compute shader
	inline void(*glDispatchCompute) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) = nullptr;
	inline void(*glDispatchComputeIndirect) (GLintptr indirect) = nullptr;
#define ARB_compute_shader 1

	//compute variable group size
	inline void(*glDispatchComputeGroupSizeARB) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, GLuint group_size_x, GLuint group_size_y, GLuint group_size_z) = nullptr;
#define ARB_compute_variable_group_size 1

	//conditional render inverted
#define ARB_conditional_render_inverted 1

	//conservative depth
#define ARB_conservative_depth 1

	//copy buffer
	inline void(*glCopyBufferSubData) (GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size) = nullptr;
#define ARB_copy_buffer 1

	//copy image
	inline void(*glCopyImageSubData) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) = nullptr;
#define ARB_copy_image 1

	//cull distance
#define ARB_cull_distance 1

	//debug output
	typedef void(*GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam);

	inline void(*glDebugMessageCallbackARB) (GLDEBUGPROC callback, const void* userParam) = nullptr;
	inline void(*glDebugMessageControlARB) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled) = nullptr;
	inline void(*glDebugMessageInsertARB) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf) = nullptr;
	inline GLuint(*glGetDebugMessageLogARB) (GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog) = nullptr;

#define ARB_debug_output 1

	//depth buffer float
#define ARB_depth_buffer_float 1

	//depth clamp
#define ARB_depth_clamp 1

	//depth texture
#define ARB_depth_texture 1

	//derivative control
#define ARB_derivative_control 1

	//direct state access
	inline void(*glBindTextureUnit) (GLuint unit, GLuint texture) = nullptr;
	inline void(*glBlitNamedFramebuffer) (GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
	inline GLenum (*glCheckNamedFramebufferStatus) (GLuint framebuffer, GLenum target) = nullptr;
	inline void(*glClearNamedBufferData) (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glClearNamedBufferSubData) (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glClearNamedFramebufferfi) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) = nullptr;
	inline void(*glClearNamedFramebufferfv) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat* value) = nullptr;
	inline void(*glClearNamedFramebufferiv) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value) = nullptr;
	inline void(*glClearNamedFramebufferuiv) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value) = nullptr;
	inline void(*glCompressedTextureSubImage1D) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTextureSubImage2D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTextureSubImage3D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCopyNamedBufferSubData) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) = nullptr;
	inline void(*glCopyTextureSubImage1D) (GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = nullptr;
	inline void(*glCopyTextureSubImage2D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glCopyTextureSubImage3D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glCreateBuffers) (GLsizei n, GLuint* buffers) = nullptr;
	inline void(*glCreateFramebuffers) (GLsizei n, GLuint* framebuffers) = nullptr;
	inline void(*glCreateProgramPipelines) (GLsizei n, GLuint* pipelines) = nullptr;
	inline void(*glCreateQueries) (GLenum target, GLsizei n, GLuint* ids) = nullptr;
	inline void(*glCreateRenderbuffers) (GLsizei n, GLuint* renderbuffers) = nullptr;
	inline void(*glCreateSamplers) (GLsizei n, GLuint* samplers) = nullptr;
	inline void(*glCreateTextures) (GLenum target, GLsizei n, GLuint* textures) = nullptr;
	inline void(*glCreateTransformFeedbacks) (GLsizei n, GLuint* ids) = nullptr;
	inline void(*glCreateVertexArrays) (GLsizei n, GLuint* arrays) = nullptr;
	inline void(*glDisableVertexArrayAttrib) (GLuint vaobj, GLuint index) = nullptr;
	inline void(*glEnableVertexArrayAttrib) (GLuint vaobj, GLuint index) = nullptr;
	inline void(*glFlushMappedNamedBufferRange) (GLuint buffer, GLintptr offset, GLsizeiptr length) = nullptr;
	inline void(*glGenerateTextureMipmap) (GLuint texture) = nullptr;
	inline void(*glGetCompressedTextureImage) (GLuint texture, GLint level, GLsizei bufSize, void* pixels) = nullptr;
	inline void(*glGetNamedBufferParameteri64v) (GLuint buffer, GLenum pname, GLint64* params) = nullptr;
	inline void(*glGetNamedBufferParameteriv) (GLuint buffer, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetNamedBufferPointerv) (GLuint buffer, GLenum pname, void** params) = nullptr;
	inline void(*glGetNamedBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr size, void* data) = nullptr;
	inline void(*glGetNamedFramebufferAttachmentParameteriv) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetNamedFramebufferParameteriv) (GLuint framebuffer, GLenum pname, GLint* param) = nullptr;
	inline void(*glGetNamedRenderbufferParameteriv) (GLuint renderbuffer, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetQueryBufferObjecti64v) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset) = nullptr;
	inline void(*glGetQueryBufferObjectiv) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset) = nullptr;
	inline void(*glGetQueryBufferObjectui64v) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset) = nullptr;
	inline void(*glGetQueryBufferObjectuiv) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset) = nullptr;
	inline void(*glGetTextureImage) (GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels) = nullptr;
	inline void(*glGetTextureLevelParameterfv) (GLuint texture, GLint level, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetTextureLevelParameteriv) (GLuint texture, GLint level, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetTextureParameterIiv) (GLuint texture, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetTextureParameterIuiv) (GLuint texture, GLenum pname, GLuint* params) = nullptr;
	inline void(*glGetTextureParameterfv) (GLuint texture, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetTextureParameteriv) (GLuint texture, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetTransformFeedbacki64_v) (GLuint xfb, GLenum pname, GLuint index, GLint64* param) = nullptr;
	inline void(*glGetTransformFeedbacki_v) (GLuint xfb, GLenum pname, GLuint index, GLint* param) = nullptr;
	inline void(*glGetTransformFeedbackiv) (GLuint xfb, GLenum pname, GLint* param) = nullptr;
	inline void(*glGetVertexArrayIndexed64iv) (GLuint vaobj, GLuint index, GLenum pname, GLint64* param) = nullptr;
	inline void(*glGetVertexArrayIndexediv) (GLuint vaobj, GLuint index, GLenum pname, GLint* param) = nullptr;
	inline void(*glGetVertexArrayiv) (GLuint vaobj, GLenum pname, GLint* param) = nullptr;
	inline void(*glInvalidateNamedFramebufferData) (GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments) = nullptr;
	inline void(*glInvalidateNamedFramebufferSubData) (GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void* (*glMapNamedBuffer) (GLuint buffer, GLenum access) = nullptr;
	inline void* (*glMapNamedBufferRange) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) = nullptr;
	inline void(*glNamedBufferData) (GLuint buffer, GLsizeiptr size, const void* data, GLenum usage) = nullptr;
	inline void(*glNamedBufferStorage) (GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags) = nullptr;
	inline void(*glNamedBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) = nullptr;
	inline void(*glNamedFramebufferDrawBuffer) (GLuint framebuffer, GLenum mode) = nullptr;
	inline void(*glNamedFramebufferDrawBuffers) (GLuint framebuffer, GLsizei n, const GLenum* bufs) = nullptr;
	inline void(*glNamedFramebufferParameteri) (GLuint framebuffer, GLenum pname, GLint param) = nullptr;
	inline void(*glNamedFramebufferReadBuffer) (GLuint framebuffer, GLenum mode) = nullptr;
	inline void(*glNamedFramebufferRenderbuffer) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
	inline void(*glNamedFramebufferTexture) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) = nullptr;
	inline void(*glNamedFramebufferTextureLayer) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
	inline void(*glNamedRenderbufferStorage) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glNamedRenderbufferStorageMultisample) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glTextureBuffer) (GLuint texture, GLenum internalformat, GLuint buffer) = nullptr;
	inline void(*glTextureBufferRange) (GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	inline void(*glTextureParameterIiv) (GLuint texture, GLenum pname, const GLint* params) = nullptr;
	inline void(*glTextureParameterIuiv) (GLuint texture, GLenum pname, const GLuint* params) = nullptr;
	inline void(*glTextureParameterf) (GLuint texture, GLenum pname, GLfloat param) = nullptr;
	inline void(*glTextureParameterfv) (GLuint texture, GLenum pname, const GLfloat* param) = nullptr;
	inline void(*glTextureParameteri) (GLuint texture, GLenum pname, GLint param) = nullptr;
	inline void(*glTextureParameteriv) (GLuint texture, GLenum pname, const GLint* param) = nullptr;
	inline void(*glTextureStorage1D) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width) = nullptr;
	inline void(*glTextureStorage2D) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glTextureStorage2DMultisample) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	inline void(*glTextureStorage3D) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
	inline void(*glTextureStorage3DMultisample) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
	inline void(*glTextureSubImage1D) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTextureSubImage2D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTextureSubImage3D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTransformFeedbackBufferBase) (GLuint xfb, GLuint index, GLuint buffer) = nullptr;
	inline void(*glTransformFeedbackBufferRange) (GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	inline GLboolean (*glUnmapNamedBuffer) (GLuint buffer) = nullptr;
	inline void(*glVertexArrayAttribBinding) (GLuint vaobj, GLuint attribindex, GLuint bindingindex) = nullptr;
	inline void(*glVertexArrayAttribFormat) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) = nullptr;
	inline void(*glVertexArrayAttribIFormat) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	inline void(*glVertexArrayAttribLFormat) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	inline void(*glVertexArrayBindingDivisor) (GLuint vaobj, GLuint bindingindex, GLuint divisor) = nullptr;
	inline void(*glVertexArrayElementBuffer) (GLuint vaobj, GLuint buffer) = nullptr;
	inline void(*glVertexArrayVertexBuffer) (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) = nullptr;
	inline void(*glVertexArrayVertexBuffers) (GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides) = nullptr;
#define ARB_direct_state_access 1

	//draw buffers
	inline void(*glDrawBuffersARB) (GLsizei n, const GLenum * bufs) = nullptr;
#define ARB_draw_buffers 1

	//draw buffers blend
	inline void(*glBlendEquationSeparateiARB) (GLuint buf, GLenum modeRGB, GLenum modeAlpha) = nullptr;
	inline void(*glBlendEquationiARB) (GLuint buf, GLenum mode) = nullptr;
	inline void(*glBlendFuncSeparateiARB) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = nullptr;
	inline void(*glBlendFunciARB) (GLuint buf, GLenum src, GLenum dst) = nullptr;
#define ARB_draw_buffers_blend 1

	//draw elements base vertex
	inline void(*glDrawElementsBaseVertex) (GLenum mode, GLsizei count, GLenum type, void* indices, GLint basevertex) = nullptr;
	inline void(*glDrawElementsInstancedBaseVertex) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount, GLint basevertex) = nullptr;
	inline void(*glDrawRangeElementsBaseVertex) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, void* indices, GLint basevertex) = nullptr;
	inline void(*glMultiDrawElementsBaseVertex) (GLenum mode, GLsizei* count, GLenum type, void** indices, GLsizei primcount, GLint* basevertex) = nullptr;
#define ARB_draw_elements_base_vertex 1

	//draw indirect
	inline void(*glDrawArraysIndirect) (GLenum mode, const void* indirect) = nullptr;
	inline void(*glDrawElementsIndirect) (GLenum mode, GLenum type, const void* indirect) = nullptr;
#define ARB_draw_indirect 1

	//draw instanced
#define ARB_draw_instanced 1

	//enhanced layouts
#define ARB_enhanced_layouts 1

	//explicit attrib location
#define ARB_explicit_attrib_location 1

	//explicit uniform location
#define ARB_explicit_uniform_location 1

	//fragment coord conventions
#define ARB_fragment_coord_conventions 1

	//fragment layer viewport
#define ARB_fragment_layer_viewport 1

	//fragment program
#define ARB_fragment_program 1

	//fragment program shadow
#define ARB_fragment_program_shadow 1

	//fragment shader
#define ARB_fragment_shader 1

	//fragment shader interlock
#define ARB_fragment_shader_interlock 1

	//framebuffer no attachments
	inline void(*glFramebufferParameteri) (GLenum target, GLenum pname, GLint param) = nullptr;
	inline void(*glGetFramebufferParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetNamedFramebufferParameterivEXT) (GLuint framebuffer, GLenum pname, GLint* params) = nullptr;
	inline void(*glNamedFramebufferParameteriEXT) (GLuint framebuffer, GLenum pname, GLint param) = nullptr;
#define ARB_framebuffer_no_attachments 1

	//framebuffer_object
	inline void(*glBindFramebuffer) (GLenum target, GLuint framebuffer) = nullptr;
	inline void(*glBindRenderbuffer) (GLenum target, GLuint renderbuffer) = nullptr;
	inline void(*glBlitFramebuffer) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
	inline GLenum(*glCheckFramebufferStatus) (GLenum target) = nullptr;
	inline void(*glDeleteFramebuffers) (GLsizei n, const GLuint* framebuffers) = nullptr;
	inline void(*glDeleteRenderbuffers) (GLsizei n, const GLuint* renderbuffers) = nullptr;
	inline void(*glFramebufferRenderbuffer) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
	inline void(*glFramebufferTexture1D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	inline void(*glFramebufferTexture2D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	inline void(*glFramebufferTexture3D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint layer) = nullptr;
	inline void(*glFramebufferTextureLayer) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
	inline void(*glGenFramebuffers) (GLsizei n, GLuint* framebuffers) = nullptr;
	inline void(*glGenRenderbuffers) (GLsizei n, GLuint* renderbuffers) = nullptr;
	inline void(*glGenerateMipmap) (GLenum target) = nullptr;
	inline void(*glGetFramebufferAttachmentParameteriv) (GLenum target, GLenum attachment, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetRenderbufferParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsFramebuffer) (GLuint framebuffer) = nullptr;
	inline GLboolean(*glIsRenderbuffer) (GLuint renderbuffer) = nullptr;
	inline void(*glRenderbufferStorage) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glRenderbufferStorageMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
#define ARB_framebuffer_object 1

	//framebuffer sRGB
#define ARB_framebuffer_sRGB 1

	//geometry shader4
	inline void(*glFramebufferTextureARB) (GLenum target, GLenum attachment, GLuint texture, GLint level) = nullptr;
	inline void(*glFramebufferTextureFaceARB) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face) = nullptr;
	inline void(*glFramebufferTextureLayerARB) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
	inline void(*glProgramParameteriARB) (GLuint program, GLenum pname, GLint value) = nullptr;
#define ARB_geometry_shader4 1

	//get program binary
	inline void(*glGetProgramBinary) (GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void* binary) = nullptr;
	inline void(*glProgramBinary) (GLuint program, GLenum binaryFormat, const void* binary, GLsizei length) = nullptr;
	inline void(*glProgramParameteri) (GLuint program, GLenum pname, GLint value) = nullptr;
#define ARB_get_program_binary 1

	//get texture sub image
	inline void(*glGetCompressedTextureSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels) = nullptr;
	inline void(*glGetTextureSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels) = nullptr;
#define ARB_get_texture_sub_image 1

	//gl spirv
	inline void(*glSpecializeShaderARB) (GLuint shader, const GLchar * pEntryPoint, GLuint numSpecializationConstants, const GLuint * pConstantIndex, const GLuint * pConstantValue) = nullptr;
#define ARB_gl_spirv 1

	//gpu shader5
#define ARB_gpu_shader5 1

	//gpu shader fp64
	inline void(*glGetUniformdv) (GLuint program, GLint location, GLdouble * params) = nullptr;
	inline void(*glUniform1d) (GLint location, GLdouble x) = nullptr;
	inline void(*glUniform1dv) (GLint location, GLsizei count, const GLdouble* value) = nullptr;
	inline void(*glUniform2d) (GLint location, GLdouble x, GLdouble y) = nullptr;
	inline void(*glUniform2dv) (GLint location, GLsizei count, const GLdouble* value) = nullptr;
	inline void(*glUniform3d) (GLint location, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glUniform3dv) (GLint location, GLsizei count, const GLdouble* value) = nullptr;
	inline void(*glUniform4d) (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glUniform4dv) (GLint location, GLsizei count, const GLdouble* value) = nullptr;
	inline void(*glUniformMatrix2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glUniformMatrix2x3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glUniformMatrix2x4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glUniformMatrix3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glUniformMatrix3x2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glUniformMatrix3x4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glUniformMatrix4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glUniformMatrix4x2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glUniformMatrix4x3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
#define ARB_gpu_shader_fp64 1

	//gpu shader int64
	inline void(*glGetUniformi64vARB) (GLuint program, GLint location, GLint64 * params) = nullptr;
	inline void(*glGetUniformui64vARB) (GLuint program, GLint location, GLuint64* params) = nullptr;
	inline void(*glGetnUniformi64vARB) (GLuint program, GLint location, GLsizei bufSize, GLint64* params) = nullptr;
	inline void(*glGetnUniformui64vARB) (GLuint program, GLint location, GLsizei bufSize, GLuint64* params) = nullptr;
	inline void(*glProgramUniform1i64ARB) (GLuint program, GLint location, GLint64 x) = nullptr;
	inline void(*glProgramUniform1i64vARB) (GLuint program, GLint location, GLsizei count, const GLint64* value) = nullptr;
	inline void(*glProgramUniform1ui64ARB) (GLuint program, GLint location, GLuint64 x) = nullptr;
	inline void(*glProgramUniform1ui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* value) = nullptr;
	inline void(*glProgramUniform2i64ARB) (GLuint program, GLint location, GLint64 x, GLint64 y) = nullptr;
	inline void(*glProgramUniform2i64vARB) (GLuint program, GLint location, GLsizei count, const GLint64* value) = nullptr;
	inline void(*glProgramUniform2ui64ARB) (GLuint program, GLint location, GLuint64 x, GLuint64 y) = nullptr;
	inline void(*glProgramUniform2ui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* value) = nullptr;
	inline void(*glProgramUniform3i64ARB) (GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z) = nullptr;
	inline void(*glProgramUniform3i64vARB) (GLuint program, GLint location, GLsizei count, const GLint64* value) = nullptr;
	inline void(*glProgramUniform3ui64ARB) (GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z) = nullptr;
	inline void(*glProgramUniform3ui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* value) = nullptr;
	inline void(*glProgramUniform4i64ARB) (GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w) = nullptr;
	inline void(*glProgramUniform4i64vARB) (GLuint program, GLint location, GLsizei count, const GLint64* value) = nullptr;
	inline void(*glProgramUniform4ui64ARB) (GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w) = nullptr;
	inline void(*glProgramUniform4ui64vARB) (GLuint program, GLint location, GLsizei count, const GLuint64* value) = nullptr;
	inline void(*glUniform1i64ARB) (GLint location, GLint64 x) = nullptr;
	inline void(*glUniform1i64vARB) (GLint location, GLsizei count, const GLint64* value) = nullptr;
	inline void(*glUniform1ui64ARB) (GLint location, GLuint64 x) = nullptr;
	inline void(*glUniform1ui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
	inline void(*glUniform2i64ARB) (GLint location, GLint64 x, GLint64 y) = nullptr;
	inline void(*glUniform2i64vARB) (GLint location, GLsizei count, const GLint64* value) = nullptr;
	inline void(*glUniform2ui64ARB) (GLint location, GLuint64 x, GLuint64 y) = nullptr;
	inline void(*glUniform2ui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
	inline void(*glUniform3i64ARB) (GLint location, GLint64 x, GLint64 y, GLint64 z) = nullptr;
	inline void(*glUniform3i64vARB) (GLint location, GLsizei count, const GLint64* value) = nullptr;
	inline void(*glUniform3ui64ARB) (GLint location, GLuint64 x, GLuint64 y, GLuint64 z) = nullptr;
	inline void(*glUniform3ui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
	inline void(*glUniform4i64ARB) (GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w) = nullptr;
	inline void(*glUniform4i64vARB) (GLint location, GLsizei count, const GLint64* value) = nullptr;
	inline void(*glUniform4ui64ARB) (GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w) = nullptr;
	inline void(*glUniform4ui64vARB) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
#define ARB_gpu_shader_int64 1

	//half float pixel
#define ARB_half_float_pixel 1

	//half float vertex
#define ARB_half_float_vertex 1

	//imaging
	inline void(*glColorSubTable) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glColorTable) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* table) = nullptr;
	inline void(*glColorTableParameterfv) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glColorTableParameteriv) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glConvolutionFilter1D) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* image) = nullptr;
	inline void(*glConvolutionFilter2D) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* image) = nullptr;
	inline void(*glConvolutionParameterf) (GLenum target, GLenum pname, GLfloat params) = nullptr;
	inline void(*glConvolutionParameterfv) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glConvolutionParameteri) (GLenum target, GLenum pname, GLint params) = nullptr;
	inline void(*glConvolutionParameteriv) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glCopyColorSubTable) (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width) = nullptr;
	inline void(*glCopyColorTable) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = nullptr;
	inline void(*glCopyConvolutionFilter1D) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = nullptr;
	inline void(*glCopyConvolutionFilter2D) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glGetColorTable) (GLenum target, GLenum format, GLenum type, void* table) = nullptr;
	inline void(*glGetColorTableParameterfv) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetColorTableParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetConvolutionFilter) (GLenum target, GLenum format, GLenum type, void* image) = nullptr;
	inline void(*glGetConvolutionParameterfv) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetConvolutionParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetHistogram) (GLenum target, GLboolean reset, GLenum format, GLenum type, void* values) = nullptr;
	inline void(*glGetHistogramParameterfv) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetHistogramParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetMinmax) (GLenum target, GLboolean reset, GLenum format, GLenum types, void* values) = nullptr;
	inline void(*glGetMinmaxParameterfv) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetMinmaxParameteriv) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetSeparableFilter) (GLenum target, GLenum format, GLenum type, void* row, void* column, void* span) = nullptr;
	inline void(*glHistogram) (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink) = nullptr;
	inline void(*glMinmax) (GLenum target, GLenum internalformat, GLboolean sink) = nullptr;
	inline void(*glResetHistogram) (GLenum target) = nullptr;
	inline void(*glResetMinmax) (GLenum target) = nullptr;
	inline void(*glSeparableFilter2D) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* row, const void* column) = nullptr;
#define ARB_imaging 1

	//indirect parameters
	inline void(*glMultiDrawArraysIndirectCountARB) (GLenum mode, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) = nullptr;
	inline void(*glMultiDrawElementsIndirectCountARB) (GLenum mode, GLenum type, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) = nullptr;
#define ARB_indirect_parameters 1

	//instanced arrays
	inline void(*glDrawArraysInstancedARB) (GLenum mode, GLint first, GLsizei count, GLsizei primcount) = nullptr;
	inline void(*glDrawElementsInstancedARB) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) = nullptr;
	inline void(*glVertexAttribDivisorARB) (GLuint index, GLuint divisor) = nullptr;
#define ARB_instanced_arrays 1

	//internalformat query
	inline void(*glGetInternalformativ) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params) = nullptr;
#define ARB_internalformat_query 1

	//internalformat query2
	inline void(*glGetInternalformati64v) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params) = nullptr;
#define ARB_internalformat_query2 1

	//invalidate subdata
	inline void(*glInvalidateBufferData) (GLuint buffer) = nullptr;
	inline void(*glInvalidateBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr length) = nullptr;
	inline void(*glInvalidateFramebuffer) (GLenum target, GLsizei numAttachments, const GLenum* attachments) = nullptr;
	inline void(*glInvalidateSubFramebuffer) (GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glInvalidateTexImage) (GLuint texture, GLint level) = nullptr;
	inline void(*glInvalidateTexSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
#define ARB_invalidate_subdata 1

	//map buffer alignment
#define ARB_map_buffer_alignment 1

	//map buffer range
	inline void(*glFlushMappedBufferRange) (GLenum target, GLintptr offset, GLsizeiptr length) = nullptr;
	inline void* (*glMapBufferRange) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) = nullptr;
#define ARB_map_buffer_range 1

	//matrix palette
	inline void(*glCurrentPaletteMatrixARB) (GLint index) = nullptr;
	inline void(*glMatrixIndexPointerARB) (GLint size, GLenum type, GLsizei stride, void* pointer) = nullptr;
	inline void(*glMatrixIndexubvARB) (GLint size, GLubyte* indices) = nullptr;
	inline void(*glMatrixIndexuivARB) (GLint size, GLuint* indices) = nullptr;
	inline void(*glMatrixIndexusvARB) (GLint size, GLushort* indices) = nullptr;
#define ARB_matrix_palette 1

	//multi bind
	inline void(*glBindBuffersBase) (GLenum target, GLuint first, GLsizei count, const GLuint * buffers) = nullptr;
	inline void(*glBindBuffersRange) (GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizeiptr* sizes) = nullptr;
	inline void(*glBindImageTextures) (GLuint first, GLsizei count, const GLuint* textures) = nullptr;
	inline void(*glBindSamplers) (GLuint first, GLsizei count, const GLuint* samplers) = nullptr;
	inline void(*glBindTextures) (GLuint first, GLsizei count, const GLuint* textures) = nullptr;
	inline void(*glBindVertexBuffers) (GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides) = nullptr;
#define ARB_multi_bind 1

	//multi draw indirect
	inline void(*glMultiDrawArraysIndirect) (GLenum mode, const void* indirect, GLsizei primcount, GLsizei stride) = nullptr;
	inline void(*glMultiDrawElementsIndirect) (GLenum mode, GLenum type, const void* indirect, GLsizei primcount, GLsizei stride) = nullptr;
#define ARB_multi_draw_indirect 1

	//multisample
	inline void(*glSampleCoverageARB) (GLclampf value, GLboolean invert) = nullptr;
#define ARB_multisample 1

	//multitexture
	inline void(*glActiveTextureARB) (GLenum texture) = nullptr;
	inline void(*glClientActiveTextureARB) (GLenum texture) = nullptr;
	inline void(*glMultiTexCoord1dARB) (GLenum target, GLdouble s) = nullptr;
	inline void(*glMultiTexCoord1dvARB) (GLenum target, const GLdouble* v) = nullptr;
	inline void(*glMultiTexCoord1fARB) (GLenum target, GLfloat s) = nullptr;
	inline void(*glMultiTexCoord1fvARB) (GLenum target, const GLfloat* v) = nullptr;
	inline void(*glMultiTexCoord1iARB) (GLenum target, GLint s) = nullptr;
	inline void(*glMultiTexCoord1ivARB) (GLenum target, const GLint* v) = nullptr;
	inline void(*glMultiTexCoord1sARB) (GLenum target, GLshort s) = nullptr;
	inline void(*glMultiTexCoord1svARB) (GLenum target, const GLshort* v) = nullptr;
	inline void(*glMultiTexCoord2dARB) (GLenum target, GLdouble s, GLdouble t) = nullptr;
	inline void(*glMultiTexCoord2dvARB) (GLenum target, const GLdouble* v) = nullptr;
	inline void(*glMultiTexCoord2fARB) (GLenum target, GLfloat s, GLfloat t) = nullptr;
	inline void(*glMultiTexCoord2fvARB) (GLenum target, const GLfloat* v) = nullptr;
	inline void(*glMultiTexCoord2iARB) (GLenum target, GLint s, GLint t) = nullptr;
	inline void(*glMultiTexCoord2ivARB) (GLenum target, const GLint* v) = nullptr;
	inline void(*glMultiTexCoord2sARB) (GLenum target, GLshort s, GLshort t) = nullptr;
	inline void(*glMultiTexCoord2svARB) (GLenum target, const GLshort* v) = nullptr;
	inline void(*glMultiTexCoord3dARB) (GLenum target, GLdouble s, GLdouble t, GLdouble r) = nullptr;
	inline void(*glMultiTexCoord3dvARB) (GLenum target, const GLdouble* v) = nullptr;
	inline void(*glMultiTexCoord3fARB) (GLenum target, GLfloat s, GLfloat t, GLfloat r) = nullptr;
	inline void(*glMultiTexCoord3fvARB) (GLenum target, const GLfloat* v) = nullptr;
	inline void(*glMultiTexCoord3iARB) (GLenum target, GLint s, GLint t, GLint r) = nullptr;
	inline void(*glMultiTexCoord3ivARB) (GLenum target, const GLint* v) = nullptr;
	inline void(*glMultiTexCoord3sARB) (GLenum target, GLshort s, GLshort t, GLshort r) = nullptr;
	inline void(*glMultiTexCoord3svARB) (GLenum target, const GLshort* v) = nullptr;
	inline void(*glMultiTexCoord4dARB) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) = nullptr;
	inline void(*glMultiTexCoord4dvARB) (GLenum target, const GLdouble* v) = nullptr;
	inline void(*glMultiTexCoord4fARB) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) = nullptr;
	inline void(*glMultiTexCoord4fvARB) (GLenum target, const GLfloat* v) = nullptr;
	inline void(*glMultiTexCoord4iARB) (GLenum target, GLint s, GLint t, GLint r, GLint q) = nullptr;
	inline void(*glMultiTexCoord4ivARB) (GLenum target, const GLint* v) = nullptr;
	inline void(*glMultiTexCoord4sARB) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) = nullptr;
	inline void(*glMultiTexCoord4svARB) (GLenum target, const GLshort* v) = nullptr;
#define ARB_multitexture 1

	//occlusion query
	inline void(*glBeginQueryARB) (GLenum target, GLuint id) = nullptr;
	inline void(*glDeleteQueriesARB) (GLsizei n, const GLuint* ids) = nullptr;
	inline void(*glEndQueryARB) (GLenum target) = nullptr;
	inline void(*glGenQueriesARB) (GLsizei n, GLuint* ids) = nullptr;
	inline void(*glGetQueryObjectivARB) (GLuint id, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetQueryObjectuivARB) (GLuint id, GLenum pname, GLuint* params) = nullptr;
	inline void(*glGetQueryivARB) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsQueryARB) (GLuint id) = nullptr;
#define ARB_occlusion_query 1

	//occlusion query2
#define ARB_occlusion_query2 1

	//parallel shader compile
	inline void(*glMaxShaderCompilerThreadsARB) (GLuint count) = nullptr;
#define ARB_parallel_shader_compile 1

	//pipeline statistics query
#define ARB_pipeline_statistics_query 1

	//pixel buffer object
#define ARB_pixel_buffer_object 1

	//point parameters
	inline void(*glPointParameterfARB) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glPointParameterfvARB) (GLenum pname, const GLfloat* params) = nullptr;
#define ARB_point_parameters 1

	//point sprite
#define ARB_point_sprite 1

	//polygon offset clamp
	inline void(*glPolygonOffsetClamp) (GLfloat factor, GLfloat units, GLfloat clamp) = nullptr;
#define ARB_polygon_offset_clamp 1

	//post depth coverage
#define ARB_post_depth_coverage 1

	//program interface query
	inline void(*glGetProgramInterfaceiv) (GLuint program, GLenum programInterface, GLenum pname, GLint * params) = nullptr;
	inline GLuint(*glGetProgramResourceIndex) (GLuint program, GLenum programInterface, const GLchar* name) = nullptr;
	inline GLint(*glGetProgramResourceLocation) (GLuint program, GLenum programInterface, const GLchar* name) = nullptr;
	inline GLint(*glGetProgramResourceLocationIndex) (GLuint program, GLenum programInterface, const GLchar* name) = nullptr;
	inline void(*glGetProgramResourceName) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name) = nullptr;
	inline void(*glGetProgramResourceiv) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params) = nullptr;
#define ARB_program_interface_query 1

	//provoking vertex
	inline void(*glProvokingVertex) (GLenum mode) = nullptr;
#define ARB_provoking_vertex 1

	// query buffer object
#define ARB_query_buffer_object 1

	//robust buffer access behavior
#define ARB_robust_buffer_access_behavior 1

	//robustness
	inline GLenum(*glGetGraphicsResetStatusARB) (void) = nullptr;
	inline void(*glGetnColorTableARB) (GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* table) = nullptr;
	inline void(*glGetnCompressedTexImageARB) (GLenum target, GLint lod, GLsizei bufSize, void* img) = nullptr;
	inline void(*glGetnConvolutionFilterARB) (GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* image) = nullptr;
	inline void(*glGetnHistogramARB) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values) = nullptr;
	inline void(*glGetnMapdvARB) (GLenum target, GLenum query, GLsizei bufSize, GLdouble* v) = nullptr;
	inline void(*glGetnMapfvARB) (GLenum target, GLenum query, GLsizei bufSize, GLfloat* v) = nullptr;
	inline void(*glGetnMapivARB) (GLenum target, GLenum query, GLsizei bufSize, GLint* v) = nullptr;
	inline void(*glGetnMinmaxARB) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values) = nullptr;
	inline void(*glGetnPixelMapfvARB) (GLenum map, GLsizei bufSize, GLfloat* values) = nullptr;
	inline void(*glGetnPixelMapuivARB) (GLenum map, GLsizei bufSize, GLuint* values) = nullptr;
	inline void(*glGetnPixelMapusvARB) (GLenum map, GLsizei bufSize, GLushort* values) = nullptr;
	inline void(*glGetnPolygonStippleARB) (GLsizei bufSize, GLubyte* pattern) = nullptr;
	inline void(*glGetnSeparableFilterARB) (GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void* row, GLsizei columnBufSize, void* column, void* span) = nullptr;
	inline void(*glGetnTexImageARB) (GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* img) = nullptr;
	inline void(*glGetnUniformdvARB) (GLuint program, GLint location, GLsizei bufSize, GLdouble* params) = nullptr;
	inline void(*glGetnUniformfvARB) (GLuint program, GLint location, GLsizei bufSize, GLfloat* params) = nullptr;
	inline void(*glGetnUniformivARB) (GLuint program, GLint location, GLsizei bufSize, GLint* params) = nullptr;
	inline void(*glGetnUniformuivARB) (GLuint program, GLint location, GLsizei bufSize, GLuint* params) = nullptr;
	inline void(*glReadnPixelsARB) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data) = nullptr;
#define ARB_robustness 1

	//robustness application isolation
#define ARB_robustness_application_isolation 1

	//robustness share group isolation
#define ARB_robustness_share_group_isolation 1

	//sample locations
	inline void(*glFramebufferSampleLocationsfvARB) (GLenum target, GLuint start, GLsizei count, const GLfloat * v) = nullptr;
	inline void(*glNamedFramebufferSampleLocationsfvARB) (GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v) = nullptr;
#define ARB_sample_locations 1

	//sample shading
	inline void(*glMinSampleShadingARB) (GLclampf value) = nullptr;
#define ARB_sample_shading 1

	//sampler objects
	inline void(*glBindSampler) (GLuint unit, GLuint sampler) = nullptr;
	inline void(*glDeleteSamplers) (GLsizei count, const GLuint* samplers) = nullptr;
	inline void(*glGenSamplers) (GLsizei count, GLuint* samplers) = nullptr;
	inline void(*glGetSamplerParameterIiv) (GLuint sampler, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetSamplerParameterIuiv) (GLuint sampler, GLenum pname, GLuint* params) = nullptr;
	inline void(*glGetSamplerParameterfv) (GLuint sampler, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetSamplerParameteriv) (GLuint sampler, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsSampler) (GLuint sampler) = nullptr;
	inline void(*glSamplerParameterIiv) (GLuint sampler, GLenum pname, const GLint* params) = nullptr;
	inline void(*glSamplerParameterIuiv) (GLuint sampler, GLenum pname, const GLuint* params) = nullptr;
	inline void(*glSamplerParameterf) (GLuint sampler, GLenum pname, GLfloat param) = nullptr;
	inline void(*glSamplerParameterfv) (GLuint sampler, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glSamplerParameteri) (GLuint sampler, GLenum pname, GLint param) = nullptr;
	inline void(*glSamplerParameteriv) (GLuint sampler, GLenum pname, const GLint* params) = nullptr;
#define ARB_sampler_objects 1

	//seamless cube map
#define ARB_seamless_cube_map 1

	//seamless cubemap per texture
#define ARB_seamless_cubemap_per_texture 1

	//separate shader objects
	inline void(*glActiveShaderProgram) (GLuint pipeline, GLuint program) = nullptr;
	inline void(*glBindProgramPipeline) (GLuint pipeline) = nullptr;
	inline GLuint(*glCreateShaderProgramv) (GLenum type, GLsizei count, const GLchar* const* strings) = nullptr;
	inline void(*glDeleteProgramPipelines) (GLsizei n, const GLuint* pipelines) = nullptr;
	inline void(*glGenProgramPipelines) (GLsizei n, GLuint* pipelines) = nullptr;
	inline void(*glGetProgramPipelineInfoLog) (GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog) = nullptr;
	inline void(*glGetProgramPipelineiv) (GLuint pipeline, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsProgramPipeline) (GLuint pipeline) = nullptr;
	inline void(*glProgramUniform1d) (GLuint program, GLint location, GLdouble x) = nullptr;
	inline void(*glProgramUniform1dv) (GLuint program, GLint location, GLsizei count, const GLdouble* value) = nullptr;
	inline void(*glProgramUniform1f) (GLuint program, GLint location, GLfloat x) = nullptr;
	inline void(*glProgramUniform1fv) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glProgramUniform1i) (GLuint program, GLint location, GLint x) = nullptr;
	inline void(*glProgramUniform1iv) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glProgramUniform1ui) (GLuint program, GLint location, GLuint x) = nullptr;
	inline void(*glProgramUniform1uiv) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glProgramUniform2d) (GLuint program, GLint location, GLdouble x, GLdouble y) = nullptr;
	inline void(*glProgramUniform2dv) (GLuint program, GLint location, GLsizei count, const GLdouble* value) = nullptr;
	inline void(*glProgramUniform2f) (GLuint program, GLint location, GLfloat x, GLfloat y) = nullptr;
	inline void(*glProgramUniform2fv) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glProgramUniform2i) (GLuint program, GLint location, GLint x, GLint y) = nullptr;
	inline void(*glProgramUniform2iv) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glProgramUniform2ui) (GLuint program, GLint location, GLuint x, GLuint y) = nullptr;
	inline void(*glProgramUniform2uiv) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glProgramUniform3d) (GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glProgramUniform3dv) (GLuint program, GLint location, GLsizei count, const GLdouble* value) = nullptr;
	inline void(*glProgramUniform3f) (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glProgramUniform3fv) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glProgramUniform3i) (GLuint program, GLint location, GLint x, GLint y, GLint z) = nullptr;
	inline void(*glProgramUniform3iv) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glProgramUniform3ui) (GLuint program, GLint location, GLuint x, GLuint y, GLuint z) = nullptr;
	inline void(*glProgramUniform3uiv) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glProgramUniform4d) (GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glProgramUniform4dv) (GLuint program, GLint location, GLsizei count, const GLdouble* value) = nullptr;
	inline void(*glProgramUniform4f) (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glProgramUniform4fv) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glProgramUniform4i) (GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w) = nullptr;
	inline void(*glProgramUniform4iv) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glProgramUniform4ui) (GLuint program, GLint location, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
	inline void(*glProgramUniform4uiv) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glProgramUniformMatrix2dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glProgramUniformMatrix2fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix2x3dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glProgramUniformMatrix2x3fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix2x4dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glProgramUniformMatrix2x4fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix3dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glProgramUniformMatrix3fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix3x2dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glProgramUniformMatrix3x2fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix3x4dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glProgramUniformMatrix3x4fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix4dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glProgramUniformMatrix4fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix4x2dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glProgramUniformMatrix4x2fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix4x3dv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value) = nullptr;
	inline void(*glProgramUniformMatrix4x3fv) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glUseProgramStages) (GLuint pipeline, GLbitfield stages, GLuint program) = nullptr;
	inline void(*glValidateProgramPipeline) (GLuint pipeline) = nullptr;
#define ARB_separate_shader_objects 1

	//shader atomic counter ops
#define ARB_shader_atomic_counter_ops 1

	//shader atomic counters
	inline void(*glGetActiveAtomicCounterBufferiv) (GLuint program, GLuint bufferIndex, GLenum pname, GLint * params) = nullptr;
#define ARB_shader_atomic_counters 1

	//shader ballot
#define ARB_shader_ballot 1

	//shader bit encoding
#define ARB_shader_bit_encoding 1

	//shader clock
#define ARB_shader_clock 1

	//shader draw parameters
#define ARB_shader_draw_parameters 1

	//shader group vote
#define ARB_shader_group_vote 1

	//shader image load store
	inline void(*glBindImageTexture) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) = nullptr;
	inline void(*glMemoryBarrier) (GLbitfield barriers) = nullptr;
#define ARB_shader_image_load_store 1

	//shader image size
#define ARB_shader_image_size 1

	//shader objects
	inline void(*glAttachObjectARB) (GLhandleARB containerObj, GLhandleARB obj) = nullptr;
	inline void(*glCompileShaderARB) (GLhandleARB shaderObj) = nullptr;
	inline GLhandleARB(*glCreateProgramObjectARB) (void) = nullptr;
	inline GLhandleARB(*glCreateShaderObjectARB) (GLenum shaderType) = nullptr;
	inline void(*glDeleteObjectARB) (GLhandleARB obj) = nullptr;
	inline void(*glDetachObjectARB) (GLhandleARB containerObj, GLhandleARB attachedObj) = nullptr;
	inline void(*glGetActiveUniformARB) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLcharARB* name) = nullptr;
	inline void(*glGetAttachedObjectsARB) (GLhandleARB containerObj, GLsizei maxCount, GLsizei* count, GLhandleARB* obj) = nullptr;
	inline GLhandleARB(*glGetHandleARB) (GLenum pname) = nullptr;
	inline void(*glGetInfoLogARB) (GLhandleARB obj, GLsizei maxLength, GLsizei* length, GLcharARB* infoLog) = nullptr;
	inline void(*glGetObjectParameterfvARB) (GLhandleARB obj, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetObjectParameterivARB) (GLhandleARB obj, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetShaderSourceARB) (GLhandleARB obj, GLsizei maxLength, GLsizei* length, GLcharARB* source) = nullptr;
	inline GLint(*glGetUniformLocationARB) (GLhandleARB programObj, const GLcharARB* name) = nullptr;
	inline void(*glGetUniformfvARB) (GLhandleARB programObj, GLint location, GLfloat* params) = nullptr;
	inline void(*glGetUniformivARB) (GLhandleARB programObj, GLint location, GLint* params) = nullptr;
	inline void(*glLinkProgramARB) (GLhandleARB programObj) = nullptr;
	inline void(*glShaderSourceARB) (GLhandleARB shaderObj, GLsizei count, const GLcharARB** string, const GLint* length) = nullptr;
	inline void(*glUniform1fARB) (GLint location, GLfloat v0) = nullptr;
	inline void(*glUniform1fvARB) (GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glUniform1iARB) (GLint location, GLint v0) = nullptr;
	inline void(*glUniform1ivARB) (GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glUniform2fARB) (GLint location, GLfloat v0, GLfloat v1) = nullptr;
	inline void(*glUniform2fvARB) (GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glUniform2iARB) (GLint location, GLint v0, GLint v1) = nullptr;
	inline void(*glUniform2ivARB) (GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glUniform3fARB) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2) = nullptr;
	inline void(*glUniform3fvARB) (GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glUniform3iARB) (GLint location, GLint v0, GLint v1, GLint v2) = nullptr;
	inline void(*glUniform3ivARB) (GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glUniform4fARB) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) = nullptr;
	inline void(*glUniform4fvARB) (GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glUniform4iARB) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3) = nullptr;
	inline void(*glUniform4ivARB) (GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glUniformMatrix2fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glUniformMatrix3fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glUniformMatrix4fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glUseProgramObjectARB) (GLhandleARB programObj) = nullptr;
	inline void(*glValidateProgramARB) (GLhandleARB programObj) = nullptr;

#define ARB_shader_objects 1

	//shader precision
#define ARB_shader_precision 1

	//shader stencil export
#define ARB_shader_stencil_export 1

	//shader storage buffer object
	inline void(*glShaderStorageBlockBinding) (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) = nullptr;
#define ARB_shader_storage_buffer_object 1

	//shader subroutine
	inline void(*glGetActiveSubroutineName) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name) = nullptr;
	inline void(*glGetActiveSubroutineUniformName) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name) = nullptr;
	inline void(*glGetActiveSubroutineUniformiv) (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values) = nullptr;
	inline void(*glGetProgramStageiv) (GLuint program, GLenum shadertype, GLenum pname, GLint* values) = nullptr;
	inline GLuint(*glGetSubroutineIndex) (GLuint program, GLenum shadertype, const GLchar* name) = nullptr;
	inline GLint(*glGetSubroutineUniformLocation) (GLuint program, GLenum shadertype, const GLchar* name) = nullptr;
	inline void(*glGetUniformSubroutineuiv) (GLenum shadertype, GLint location, GLuint* params) = nullptr;
	inline void(*glUniformSubroutinesuiv) (GLenum shadertype, GLsizei count, const GLuint* indices) = nullptr;
#define ARB_shader_subroutine 1

	//shader texture image samples
#define ARB_shader_texture_image_samples 1

	//shader texture lod
#define ARB_shader_texture_lod 1

	//shader viewport layer array
#define ARB_shader_viewport_layer_array 1

	//shading language 100
#define ARB_shading_language_100 1

	//shading language 420pack
#define ARB_shading_language_420pack 1

	//shading language include
	inline void(*glCompileShaderIncludeARB) (GLuint shader, GLsizei count, const GLchar * const* path, const GLint * length) = nullptr;
	inline void(*glDeleteNamedStringARB) (GLint namelen, const GLchar* name) = nullptr;
	inline void(*glGetNamedStringARB) (GLint namelen, const GLchar* name, GLsizei bufSize, GLint* stringlen, GLchar* string) = nullptr;
	inline void(*glGetNamedStringivARB) (GLint namelen, const GLchar* name, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsNamedStringARB) (GLint namelen, const GLchar* name) = nullptr;
	inline void(*glNamedStringARB) (GLenum type, GLint namelen, const GLchar* name, GLint stringlen, const GLchar* string) = nullptr;
#define ARB_shading_language_include 1

	//shading language packing
#define ARB_shading_language_packing 1

	//shadow
#define ARB_shadow 1

	//shadow ambient
#define ARB_shadow_ambient 1

	//sparse buffer
	inline void(*glBufferPageCommitmentARB) (GLenum target, GLintptr offset, GLsizeiptr size, GLboolean commit) = nullptr;
#define ARB_sparse_buffer 1

	//sparse texture
	inline void(*glTexPageCommitmentARB) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit) = nullptr;
#define ARB_sparse_texture 1

	//sparse texture2
#define ARB_sparse_texture2 1

	//sparse texture clamp
#define ARB_sparse_texture_clamp 1

	//spirv extensions
#define ARB_spirv_extensions 1

	//stencil texturing
#define ARB_stencil_texturing 1

	//sync
	inline GLenum(*glClientWaitSync) (GLsync GLsync, GLbitfield flags, GLuint64 timeout) = nullptr;
	inline void(*glDeleteSync) (GLsync GLsync) = nullptr;
	inline GLsync(*glFenceSync) (GLenum condition, GLbitfield flags) = nullptr;
	inline void(*glGetInteger64v) (GLenum pname, GLint64* params) = nullptr;
	inline void(*glGetSynciv) (GLsync GLsync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) = nullptr;
	inline GLboolean(*glIsSync) (GLsync GLsync) = nullptr;
	inline void(*glWaitSync) (GLsync GLsync, GLbitfield flags, GLuint64 timeout) = nullptr;
#define ARB_sync 1

	//tessellation shader
	inline void(*glPatchParameterfv) (GLenum pname, const GLfloat * values) = nullptr;
	inline void(*glPatchParameteri) (GLenum pname, GLint value) = nullptr;
#define ARB_tessellation_shader 1

	//texture barrier
	inline void(*glTextureBarrier) (void) = nullptr;
#define ARB_texture_barrier 1

	//texture border clamp
#define ARB_texture_border_clamp 1

	//texture buffer object
	inline void(*glTexBufferARB) (GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
#define ARB_texture_buffer_object 1

	// texture buffer object rgb32
#define ARB_texture_buffer_object_rgb32 1

	//texture buffer range
	inline void(*glTexBufferRange) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	inline void(*glTextureBufferRangeEXT) (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
#define ARB_texture_buffer_range 1

	//texture compression
	inline void(*glCompressedTexImage1DARB) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTexImage2DARB) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTexImage3DARB) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTexSubImage1DARB) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTexSubImage2DARB) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTexSubImage3DARB) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glGetCompressedTexImageARB) (GLenum target, GLint lod, void* img) = nullptr;
#define ARB_texture_compression 1

	//texture compression bptc
#define ARB_texture_compression_bptc 1

	//texture compression rgtc
#define ARB_texture_compression_rgtc 1

	//texture cube map
#define ARB_texture_cube_map 1

	//texture cube map array
#define ARB_texture_cube_map_array 1

	//texture env add
#define ARB_texture_env_add 1

	//texture env combine
#define ARB_texture_env_combine 1

	//texture env crossbar
#define ARB_texture_env_crossbar 1

	//texture env dot3
#define ARB_texture_env_dot3 1

	//texture filter anisotropic
#define ARB_texture_filter_anisotropic 1

	//texture filter minmax
#define ARB_texture_filter_minmax 1

	//texture float
#define ARB_texture_float 1

	//texture gather
#define ARB_texture_gather 1

	//texture mirror clamp to edge
#define ARB_texture_mirror_clamp_to_edge 1

	//texture mirrored repeat
#define ARB_texture_mirrored_repeat 1

	//texture multisample
	inline void(*glGetMultisamplefv) (GLenum pname, GLuint index, GLfloat * val) = nullptr;
	inline void(*glSampleMaski) (GLuint index, GLbitfield mask) = nullptr;
	inline void(*glTexImage2DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	inline void(*glTexImage3DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
#define ARB_texture_multisample 1

	//texture non power of two
#define ARB_texture_non_power_of_two 1

	//texture query levels
#define ARB_texture_query_levels 1

	//texture query lod
#define ARB_texture_query_lod 1

	//texture rectangle
#define ARB_texture_rectangle 1

	//texture rg
#define ARB_texture_rg 1

	//texturergb10 a2ui
#define ARB_texture_rgb10_a2ui 1

	//texture stencil8
#define ARB_texture_stencil8 1

	//texture storage
	inline void(*glTexStorage1D) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) = nullptr;
	inline void(*glTexStorage2D) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glTexStorage3D) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
#define ARB_texture_storage 1

	//texture storage multisample
	inline void(*glTexStorage2DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	inline void(*glTexStorage3DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
	inline void(*glTextureStorage2DMultisampleEXT) (GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) = nullptr;
	inline void(*glTextureStorage3DMultisampleEXT) (GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) = nullptr;
#define ARB_texture_storage_multisample 1

	//texture swizzle
#define ARB_texture_swizzle 1

	//texture view
	inline void(*glTextureView) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) = nullptr;
#define ARB_texture_view 1

	//timer query
	inline void(*glGetQueryObjecti64v) (GLuint id, GLenum pname, GLint64 * params) = nullptr;
	inline void(*glGetQueryObjectui64v) (GLuint id, GLenum pname, GLuint64* params) = nullptr;
	inline void(*glQueryCounter) (GLuint id, GLenum target) = nullptr;
#define ARB_timer_query 1

	//transform feedback2
	inline void(*glBindTransformFeedback) (GLenum target, GLuint id) = nullptr;
	inline void(*glDeleteTransformFeedbacks) (GLsizei n, const GLuint* ids) = nullptr;
	inline void(*glDrawTransformFeedback) (GLenum mode, GLuint id) = nullptr;
	inline void(*glGenTransformFeedbacks) (GLsizei n, GLuint* ids) = nullptr;
	inline GLboolean(*glIsTransformFeedback) (GLuint id) = nullptr;
	inline void(*glPauseTransformFeedback) (void) = nullptr;
	inline void(*glResumeTransformFeedback) (void) = nullptr;
#define ARB_transform_feedback2 1

	//transform feedback3
	inline void(*glBeginQueryIndexed) (GLenum target, GLuint index, GLuint id) = nullptr;
	inline void(*glDrawTransformFeedbackStream) (GLenum mode, GLuint id, GLuint stream) = nullptr;
	inline void(*glEndQueryIndexed) (GLenum target, GLuint index) = nullptr;
	inline void(*glGetQueryIndexediv) (GLenum target, GLuint index, GLenum pname, GLint* params) = nullptr;
#define ARB_transform_feedback3 1

	//transform feedback instanced
	inline void(*glDrawTransformFeedbackInstanced) (GLenum mode, GLuint id, GLsizei primcount) = nullptr;
	inline void(*glDrawTransformFeedbackStreamInstanced) (GLenum mode, GLuint id, GLuint stream, GLsizei primcount) = nullptr;

	//transform feedback instanced
#define ARB_transform_feedback_instanced 1

	//transform feedback overflow query
#define ARB_transform_feedback_overflow_query 1

	//transpose matrix
	inline void(*glLoadTransposeMatrixdARB) (GLdouble m[16]) = nullptr;
	inline void(*glLoadTransposeMatrixfARB) (GLfloat m[16]) = nullptr;
	inline void(*glMultTransposeMatrixdARB) (GLdouble m[16]) = nullptr;
	inline void(*glMultTransposeMatrixfARB) (GLfloat m[16]) = nullptr;
#define ARB_transpose_matrix 1

	//uniform buffer object
	inline void(*glBindBufferBase) (GLenum target, GLuint index, GLuint buffer) = nullptr;
	inline void(*glBindBufferRange) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	inline void(*glGetActiveUniformBlockName) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) = nullptr;
	inline void(*glGetActiveUniformBlockiv) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetActiveUniformName) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName) = nullptr;
	inline void(*glGetActiveUniformsiv) (GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetIntegeri_v) (GLenum target, GLuint index, GLint* data) = nullptr;
	inline GLuint(*glGetUniformBlockIndex) (GLuint program, const GLchar* uniformBlockName) = nullptr;
	inline void(*glGetUniformIndices) (GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices) = nullptr;
	inline void(*glUniformBlockBinding) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) = nullptr;
#define ARB_uniform_buffer_object 1

	//vertex array bgra
#define ARB_vertex_array_bgra 1

	//vertex array object
	inline void(*glBindVertexArray) (GLuint array) = nullptr;
	inline void(*glDeleteVertexArrays) (GLsizei n, const GLuint* arrays) = nullptr;
	inline void(*glGenVertexArrays) (GLsizei n, GLuint* arrays) = nullptr;
	inline GLboolean(*glIsVertexArray) (GLuint array) = nullptr;
#define ARB_vertex_array_object 1

	//vertex attrib 64bit
	inline void(*glGetVertexAttribLdv) (GLuint index, GLenum pname, GLdouble * params) = nullptr;
	inline void(*glVertexAttribL1d) (GLuint index, GLdouble x) = nullptr;
	inline void(*glVertexAttribL1dv) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribL2d) (GLuint index, GLdouble x, GLdouble y) = nullptr;
	inline void(*glVertexAttribL2dv) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribL3d) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glVertexAttribL3dv) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribL4d) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glVertexAttribL4dv) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribLPointer) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
#define ARB_vertex_attrib_64bit 1

	//vertex attrib binding
	inline void(*glBindVertexBuffer) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) = nullptr;
	inline void(*glVertexArrayBindVertexBufferEXT) (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) = nullptr;
	inline void(*glVertexArrayVertexAttribBindingEXT) (GLuint vaobj, GLuint attribindex, GLuint bindingindex) = nullptr;
	inline void(*glVertexArrayVertexAttribFormatEXT) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) = nullptr;
	inline void(*glVertexArrayVertexAttribIFormatEXT) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	inline void(*glVertexArrayVertexAttribLFormatEXT) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	inline void(*glVertexArrayVertexBindingDivisorEXT) (GLuint vaobj, GLuint bindingindex, GLuint divisor) = nullptr;
	inline void(*glVertexAttribBinding) (GLuint attribindex, GLuint bindingindex) = nullptr;
	inline void(*glVertexAttribFormat) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) = nullptr;
	inline void(*glVertexAttribIFormat) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	inline void(*glVertexAttribLFormat) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) = nullptr;
	inline void(*glVertexBindingDivisor) (GLuint bindingindex, GLuint divisor) = nullptr;
#define ARB_vertex_attrib_binding 1

	//vertex blend
	inline void(*glVertexBlendARB) (GLint count) = nullptr;
	inline void(*glWeightPointerARB) (GLint size, GLenum type, GLsizei stride, void* pointer) = nullptr;
	inline void(*glWeightbvARB) (GLint size, GLbyte* weights) = nullptr;
	inline void(*glWeightdvARB) (GLint size, GLdouble* weights) = nullptr;
	inline void(*glWeightfvARB) (GLint size, GLfloat* weights) = nullptr;
	inline void(*glWeightivARB) (GLint size, GLint* weights) = nullptr;
	inline void(*glWeightsvARB) (GLint size, GLshort* weights) = nullptr;
	inline void(*glWeightubvARB) (GLint size, GLubyte* weights) = nullptr;
	inline void(*glWeightuivARB) (GLint size, GLuint* weights) = nullptr;
	inline void(*glWeightusvARB) (GLint size, GLushort* weights) = nullptr;
#define ARB_vertex_blend 1

	//vertex buffer object
	inline void(*glBindBufferARB) (GLenum target, GLuint buffer) = nullptr;
	inline void(*glBufferDataARB) (GLenum target, GLsizeiptrARB size, const void* data, GLenum usage) = nullptr;
	inline void(*glBufferSubDataARB) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void* data) = nullptr;
	inline void(*glDeleteBuffersARB) (GLsizei n, const GLuint* buffers) = nullptr;
	inline void(*glGenBuffersARB) (GLsizei n, GLuint* buffers) = nullptr;
	inline void(*glGetBufferParameterivARB) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetBufferPointervARB) (GLenum target, GLenum pname, void** params) = nullptr;
	inline void(*glGetBufferSubDataARB) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, void* data) = nullptr;
	inline GLboolean(*glIsBufferARB) (GLuint buffer) = nullptr;
	inline void* (*glMapBufferARB) (GLenum target, GLenum access) = nullptr;
	inline GLboolean(*glUnmapBufferARB) (GLenum target) = nullptr;
#define ARB_vertex_buffer_object 1

	//vertex program
	inline void(*glBindProgramARB) (GLenum target, GLuint program) = nullptr;
	inline void(*glDeleteProgramsARB) (GLsizei n, const GLuint* programs) = nullptr;
	inline void(*glDisableVertexAttribArrayARB) (GLuint index) = nullptr;
	inline void(*glEnableVertexAttribArrayARB) (GLuint index) = nullptr;
	inline void(*glGenProgramsARB) (GLsizei n, GLuint* programs) = nullptr;
	inline void(*glGetProgramEnvParameterdvARB) (GLenum target, GLuint index, GLdouble* params) = nullptr;
	inline void(*glGetProgramEnvParameterfvARB) (GLenum target, GLuint index, GLfloat* params) = nullptr;
	inline void(*glGetProgramLocalParameterdvARB) (GLenum target, GLuint index, GLdouble* params) = nullptr;
	inline void(*glGetProgramLocalParameterfvARB) (GLenum target, GLuint index, GLfloat* params) = nullptr;
	inline void(*glGetProgramStringARB) (GLenum target, GLenum pname, void* string) = nullptr;
	inline void(*glGetProgramivARB) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetVertexAttribPointervARB) (GLuint index, GLenum pname, void** pointer) = nullptr;
	inline void(*glGetVertexAttribdvARB) (GLuint index, GLenum pname, GLdouble* params) = nullptr;
	inline void(*glGetVertexAttribfvARB) (GLuint index, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetVertexAttribivARB) (GLuint index, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsProgramARB) (GLuint program) = nullptr;
	inline void(*glProgramEnvParameter4dARB) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glProgramEnvParameter4dvARB) (GLenum target, GLuint index, const GLdouble* params) = nullptr;
	inline void(*glProgramEnvParameter4fARB) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glProgramEnvParameter4fvARB) (GLenum target, GLuint index, const GLfloat* params) = nullptr;
	inline void(*glProgramLocalParameter4dARB) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glProgramLocalParameter4dvARB) (GLenum target, GLuint index, const GLdouble* params) = nullptr;
	inline void(*glProgramLocalParameter4fARB) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glProgramLocalParameter4fvARB) (GLenum target, GLuint index, const GLfloat* params) = nullptr;
	inline void(*glProgramStringARB) (GLenum target, GLenum format, GLsizei len, const void* string) = nullptr;
	inline void(*glVertexAttrib1dARB) (GLuint index, GLdouble x) = nullptr;
	inline void(*glVertexAttrib1dvARB) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttrib1fARB) (GLuint index, GLfloat x) = nullptr;
	inline void(*glVertexAttrib1fvARB) (GLuint index, const GLfloat* v) = nullptr;
	inline void(*glVertexAttrib1sARB) (GLuint index, GLshort x) = nullptr;
	inline void(*glVertexAttrib1svARB) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttrib2dARB) (GLuint index, GLdouble x, GLdouble y) = nullptr;
	inline void(*glVertexAttrib2dvARB) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttrib2fARB) (GLuint index, GLfloat x, GLfloat y) = nullptr;
	inline void(*glVertexAttrib2fvARB) (GLuint index, const GLfloat* v) = nullptr;
	inline void(*glVertexAttrib2sARB) (GLuint index, GLshort x, GLshort y) = nullptr;
	inline void(*glVertexAttrib2svARB) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttrib3dARB) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glVertexAttrib3dvARB) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttrib3fARB) (GLuint index, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glVertexAttrib3fvARB) (GLuint index, const GLfloat* v) = nullptr;
	inline void(*glVertexAttrib3sARB) (GLuint index, GLshort x, GLshort y, GLshort z) = nullptr;
	inline void(*glVertexAttrib3svARB) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttrib4NbvARB) (GLuint index, const GLbyte* v) = nullptr;
	inline void(*glVertexAttrib4NivARB) (GLuint index, const GLint* v) = nullptr;
	inline void(*glVertexAttrib4NsvARB) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttrib4NubARB) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) = nullptr;
	inline void(*glVertexAttrib4NubvARB) (GLuint index, const GLubyte* v) = nullptr;
	inline void(*glVertexAttrib4NuivARB) (GLuint index, const GLuint* v) = nullptr;
	inline void(*glVertexAttrib4NusvARB) (GLuint index, const GLushort* v) = nullptr;
	inline void(*glVertexAttrib4bvARB) (GLuint index, const GLbyte* v) = nullptr;
	inline void(*glVertexAttrib4dARB) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glVertexAttrib4dvARB) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttrib4fARB) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glVertexAttrib4fvARB) (GLuint index, const GLfloat* v) = nullptr;
	inline void(*glVertexAttrib4ivARB) (GLuint index, const GLint* v) = nullptr;
	inline void(*glVertexAttrib4sARB) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
	inline void(*glVertexAttrib4svARB) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttrib4ubvARB) (GLuint index, const GLubyte* v) = nullptr;
	inline void(*glVertexAttrib4uivARB) (GLuint index, const GLuint* v) = nullptr;
	inline void(*glVertexAttrib4usvARB) (GLuint index, const GLushort* v) = nullptr;
	inline void(*glVertexAttribPointerARB) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) = nullptr;
#define ARB_vertex_program 1

	//vertex shader
	inline void(*glBindAttribLocationARB) (GLhandleARB programObj, GLuint index, const GLcharARB * name) = nullptr;
	inline void(*glGetActiveAttribARB) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLcharARB* name) = nullptr;
	inline GLint(*glGetAttribLocationARB) (GLhandleARB programObj, const GLcharARB* name) = nullptr;
#define ARB_vertex_shader 1

	//vertex type 10f_11f_11f rev
#define ARB_vertex_type_10f_11f_11f_rev 1

	//vertex type 2_10_10_10 rev
	inline void(*glColorP3ui) (GLenum type, GLuint color) = nullptr;
	inline void(*glColorP3uiv) (GLenum type, const GLuint* color) = nullptr;
	inline void(*glColorP4ui) (GLenum type, GLuint color) = nullptr;
	inline void(*glColorP4uiv) (GLenum type, const GLuint* color) = nullptr;
	inline void(*glMultiTexCoordP1ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	inline void(*glMultiTexCoordP1uiv) (GLenum texture, GLenum type, const GLuint* coords) = nullptr;
	inline void(*glMultiTexCoordP2ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	inline void(*glMultiTexCoordP2uiv) (GLenum texture, GLenum type, const GLuint* coords) = nullptr;
	inline void(*glMultiTexCoordP3ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	inline void(*glMultiTexCoordP3uiv) (GLenum texture, GLenum type, const GLuint* coords) = nullptr;
	inline void(*glMultiTexCoordP4ui) (GLenum texture, GLenum type, GLuint coords) = nullptr;
	inline void(*glMultiTexCoordP4uiv) (GLenum texture, GLenum type, const GLuint* coords) = nullptr;
	inline void(*glNormalP3ui) (GLenum type, GLuint coords) = nullptr;
	inline void(*glNormalP3uiv) (GLenum type, const GLuint* coords) = nullptr;
	inline void(*glSecondaryColorP3ui) (GLenum type, GLuint color) = nullptr;
	inline void(*glSecondaryColorP3uiv) (GLenum type, const GLuint* color) = nullptr;
	inline void(*glTexCoordP1ui) (GLenum type, GLuint coords) = nullptr;
	inline void(*glTexCoordP1uiv) (GLenum type, const GLuint* coords) = nullptr;
	inline void(*glTexCoordP2ui) (GLenum type, GLuint coords) = nullptr;
	inline void(*glTexCoordP2uiv) (GLenum type, const GLuint* coords) = nullptr;
	inline void(*glTexCoordP3ui) (GLenum type, GLuint coords) = nullptr;
	inline void(*glTexCoordP3uiv) (GLenum type, const GLuint* coords) = nullptr;
	inline void(*glTexCoordP4ui) (GLenum type, GLuint coords) = nullptr;
	inline void(*glTexCoordP4uiv) (GLenum type, const GLuint* coords) = nullptr;
	inline void(*glVertexAttribP1ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	inline void(*glVertexAttribP1uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint* value) = nullptr;
	inline void(*glVertexAttribP2ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	inline void(*glVertexAttribP2uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint* value) = nullptr;
	inline void(*glVertexAttribP3ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	inline void(*glVertexAttribP3uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint* value) = nullptr;
	inline void(*glVertexAttribP4ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value) = nullptr;
	inline void(*glVertexAttribP4uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint* value) = nullptr;
	inline void(*glVertexP2ui) (GLenum type, GLuint value) = nullptr;
	inline void(*glVertexP2uiv) (GLenum type, const GLuint* value) = nullptr;
	inline void(*glVertexP3ui) (GLenum type, GLuint value) = nullptr;
	inline void(*glVertexP3uiv) (GLenum type, const GLuint* value) = nullptr;
	inline void(*glVertexP4ui) (GLenum type, GLuint value) = nullptr;
	inline void(*glVertexP4uiv) (GLenum type, const GLuint* value) = nullptr;
#define ARB_vertex_type_2_10_10_10_rev 1

	//viewport array
	inline void(*glDepthRangeArrayv) (GLuint first, GLsizei count, const GLclampd * v) = nullptr;
	inline void(*glDepthRangeIndexed) (GLuint index, GLclampd n, GLclampd f) = nullptr;
	inline void(*glGetDoublei_v) (GLenum target, GLuint index, GLdouble* data) = nullptr;
	inline void(*glGetFloati_v) (GLenum target, GLuint index, GLfloat* data) = nullptr;
	inline void(*glScissorArrayv) (GLuint first, GLsizei count, const GLint* v) = nullptr;
	inline void(*glScissorIndexed) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) = nullptr;
	inline void(*glScissorIndexedv) (GLuint index, const GLint* v) = nullptr;
	inline void(*glViewportArrayv) (GLuint first, GLsizei count, const GLfloat* v) = nullptr;
	inline void(*glViewportIndexedf) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) = nullptr;
	inline void(*glViewportIndexedfv) (GLuint index, const GLfloat* v) = nullptr;
#define ARB_viewport_array  1

	//window pos
	inline void(*glWindowPos2dARB) (GLdouble x, GLdouble y) = nullptr;
	inline void(*glWindowPos2dvARB) (const GLdouble* p) = nullptr;
	inline void(*glWindowPos2fARB) (GLfloat x, GLfloat y) = nullptr;
	inline void(*glWindowPos2fvARB) (const GLfloat* p) = nullptr;
	inline void(*glWindowPos2iARB) (GLint x, GLint y) = nullptr;
	inline void(*glWindowPos2ivARB) (const GLint* p) = nullptr;
	inline void(*glWindowPos2sARB) (GLshort x, GLshort y) = nullptr;
	inline void(*glWindowPos2svARB) (const GLshort* p) = nullptr;
	inline void(*glWindowPos3dARB) (GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glWindowPos3dvARB) (const GLdouble* p) = nullptr;
	inline void(*glWindowPos3fARB) (GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glWindowPos3fvARB) (const GLfloat* p) = nullptr;
	inline void(*glWindowPos3iARB) (GLint x, GLint y, GLint z) = nullptr;
	inline void(*glWindowPos3ivARB) (const GLint* p) = nullptr;
	inline void(*glWindowPos3sARB) (GLshort x, GLshort y, GLshort z) = nullptr;
	inline void(*glWindowPos3svARB) (const GLshort* p) = nullptr;
#define ARB_window_pos 1

	//*< load ARB Extensions
	inline void LoadARBExtensions()
	{
		//ES2 compatibility
		FetchProcAddress(glClearDepthf, "glClearDepthf");
		FetchProcAddress(glDepthRangef, "glDepthRangef");
		FetchProcAddress(glGetShaderPrecisionFormat, "glGetShaderPrecisionFormat");
		FetchProcAddress(glReleaseShaderCompiler, "glReleaseShaderCompiler");
		FetchProcAddress(glShaderBinary, "glShaderBinary");

		//ES3 1 compatibility
		FetchProcAddress(glMemoryBarrierByRegion, "glMemoryBarrierByRegion");

		//ES3 2 compatibility
		FetchProcAddress(glPrimitiveBoundingBoxARB, "glPrimitiveBoundingBoxARB");

		//base instance
		FetchProcAddress(glDrawArraysInstancedBaseInstance, "glDrawArraysInstancedBaseInstance");
		FetchProcAddress(glDrawElementsInstancedBaseInstance, "glDrawElementsInstancedBaseInstance");
		FetchProcAddress(glDrawElementsInstancedBaseVertexBaseInstance, "glDrawElementsInstancedBaseVertexBaseInstance");

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

		//blend func extended
		FetchProcAddress(glBindFragDataLocationIndexed, "glBindFragDataLocationIndexed");
		FetchProcAddress(glGetFragDataIndex, "glGetFragDataIndex");

		//buffer storage
		FetchProcAddress(glBufferStorage, "glBufferStorage");

		//cl event
		//FetchProcAddress(glCreateSyncFromCLeventARB, "glCreateSyncFromCLeventARB");

		//clear buffer object
		FetchProcAddress(glClearBufferData, "glClearBufferData");
		FetchProcAddress(glClearBufferSubData, "glClearBufferSubData");
		FetchProcAddress(glClearNamedBufferDataEXT, "glClearNamedBufferDataEXT");
		FetchProcAddress(glClearNamedBufferSubDataEXT, "glClearNamedBufferSubDataEXT");

		//clear texture
		FetchProcAddress(glClearTexImage, "glClearTexImage");
		FetchProcAddress(glClearTexSubImage, "glClearTexSubImage");

		//clip control
		FetchProcAddress(glClipControl, "glClipControl");

		//color buffer float
		FetchProcAddress(glClampColorARB, "glClampColorARB");

		//compute shader
		FetchProcAddress(glDispatchCompute, "glDispatchCompute");
		FetchProcAddress(glDispatchComputeIndirect, "glDispatchComputeIndirect");

		//compute variable group size
		FetchProcAddress(glDispatchComputeGroupSizeARB, "glDispatchComputeGroupSizeARB");

		//copy buffer
		FetchProcAddress(glCopyBufferSubData, "glCopyBufferSubData");

		//copy image
		FetchProcAddress(glCopyImageSubData, "glCopyImageSubData");

		//debug output
		FetchProcAddress(glDebugMessageCallbackARB, "glDebugMessageCallbackARB");
		FetchProcAddress(glDebugMessageControlARB, "glDebugMessageControlARB");
		FetchProcAddress(glDebugMessageInsertARB, "glDebugMessageInsertARB");
		FetchProcAddress(glGetDebugMessageLogARB, "glGetDebugMessageLogARB");

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

		//draw buffers
		FetchProcAddress(glDrawBuffersARB, "glDrawBuffersARB");

		//draw buffers blend
		FetchProcAddress(glBlendEquationSeparateiARB, "glBlendEquationSeparateiARB");
		FetchProcAddress(glBlendEquationiARB, "glBlendEquationiARB");
		FetchProcAddress(glBlendFuncSeparateiARB, "glBlendFuncSeparateiARB");
		FetchProcAddress(glBlendFunciARB, "glBlendFunciARB");

		//draw elements base vertex
		FetchProcAddress(glDrawElementsBaseVertex, "glDrawElementsBaseVertex");
		FetchProcAddress(glDrawElementsInstancedBaseVertex, "glDrawElementsInstancedBaseVertex");
		FetchProcAddress(glDrawRangeElementsBaseVertex, "glDrawRangeElementsBaseVertex");
		FetchProcAddress(glMultiDrawElementsBaseVertex, "glMultiDrawElementsBaseVertex");

		//draw indirect
		FetchProcAddress(glDrawArraysIndirect, "glDrawArraysIndirect");
		FetchProcAddress(glDrawElementsIndirect, "glDrawElementsIndirect");

		//framebuffer no attachments
		FetchProcAddress(glFramebufferParameteri, "glFramebufferParameteri");
		FetchProcAddress(glGetFramebufferParameteriv, "glGetFramebufferParameteriv");
		FetchProcAddress(glGetNamedFramebufferParameterivEXT, "glGetNamedFramebufferParameterivEXT");
		FetchProcAddress(glNamedFramebufferParameteriEXT, "glNamedFramebufferParameteriEXT");

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

		//geometry shader4
		FetchProcAddress(glFramebufferTextureARB, "glFramebufferTextureARB");
		FetchProcAddress(glFramebufferTextureFaceARB, "glFramebufferTextureFaceARB");
		FetchProcAddress(glFramebufferTextureLayerARB, "glFramebufferTextureLayerARB");
		FetchProcAddress(glProgramParameteriARB, "glProgramParameteriARB");

		//get program binary
		FetchProcAddress(glGetProgramBinary, "glGetProgramBinary");
		FetchProcAddress(glProgramBinary, "glProgramBinary");
		FetchProcAddress(glProgramParameteri, "glProgramParameteri");

		//get texture sub image
		FetchProcAddress(glGetCompressedTextureSubImage, "glGetCompressedTextureSubImage");
		FetchProcAddress(glGetTextureSubImage, "glGetTextureSubImage");

		//gl spirv
		FetchProcAddress(glSpecializeShaderARB, "glSpecializeShaderARB");

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

		//indirect parameters
		FetchProcAddress(glMultiDrawArraysIndirectCountARB, "glMultiDrawArraysIndirectCountARB");
		FetchProcAddress(glMultiDrawElementsIndirectCountARB, "glMultiDrawElementsIndirectCountARB");

		//instanced arrays
		FetchProcAddress(glDrawArraysInstancedARB, "glDrawArraysInstancedARB");
		FetchProcAddress(glDrawElementsInstancedARB, "glDrawElementsInstancedARB");
		FetchProcAddress(glVertexAttribDivisorARB, "glVertexAttribDivisorARB");

		//internalformat query
		FetchProcAddress(glGetInternalformativ, "glGetInternalformativ");

		//internalformat query2
		FetchProcAddress(glGetInternalformati64v, "glGetInternalformati64v");

		//invalidate subdata
		FetchProcAddress(glInvalidateBufferData, "glInvalidateBufferData");
		FetchProcAddress(glInvalidateBufferSubData, "glInvalidateBufferSubData");
		FetchProcAddress(glInvalidateFramebuffer, "glInvalidateFramebuffer");
		FetchProcAddress(glInvalidateSubFramebuffer, "glInvalidateSubFramebuffer");
		FetchProcAddress(glInvalidateTexImage, "glInvalidateTexImage");
		FetchProcAddress(glInvalidateTexSubImage, "glInvalidateTexSubImage");

		//map buffer range
		FetchProcAddress(glFlushMappedBufferRange, "glFlushMappedBufferRange");
		FetchProcAddress(glMapBufferRange, "glMapBufferRange");

		//matrix palette
		FetchProcAddress(glCurrentPaletteMatrixARB, "glCurrentPaletteMatrixARB");
		FetchProcAddress(glMatrixIndexPointerARB, "glMatrixIndexPointerARB");
		FetchProcAddress(glMatrixIndexubvARB, "glMatrixIndexubvARB");
		FetchProcAddress(glMatrixIndexuivARB, "glMatrixIndexuivARB");
		FetchProcAddress(glMatrixIndexusvARB, "glMatrixIndexusvARB");

		//multi bind
		FetchProcAddress(glBindBuffersBase, "glBindBuffersBase");
		FetchProcAddress(glBindBuffersRange, "glBindBuffersRange");
		FetchProcAddress(glBindImageTextures, "glBindImageTextures");
		FetchProcAddress(glBindSamplers, "glBindSamplers");
		FetchProcAddress(glBindTextures, "glBindTextures");
		FetchProcAddress(glBindVertexBuffers, "glBindVertexBuffers");

		//multi draw indirect
		FetchProcAddress(glMultiDrawArraysIndirect, "glMultiDrawArraysIndirect");
		FetchProcAddress(glMultiDrawElementsIndirect, "glMultiDrawElementsIndirect");

		//multisample
		FetchProcAddress(glSampleCoverageARB, "glSampleCoverageARB");

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

		//occlusion query
		FetchProcAddress(glBeginQueryARB, "glBeginQueryARB");
		FetchProcAddress(glDeleteQueriesARB, "glDeleteQueriesARB");
		FetchProcAddress(glEndQueryARB, "glEndQueryARB");
		FetchProcAddress(glGenQueriesARB, "glGenQueriesARB");
		FetchProcAddress(glGetQueryObjectivARB, "glGetQueryObjectivARB");
		FetchProcAddress(glGetQueryObjectuivARB, "glGetQueryObjectuivARB");
		FetchProcAddress(glGetQueryivARB, "glGetQueryivARB");
		FetchProcAddress(glIsQueryARB, "glIsQueryARB");

		//parallel shader compile
		FetchProcAddress(glMaxShaderCompilerThreadsARB, "glMaxShaderCompilerThreadsARB");

		//point parameters
		FetchProcAddress(glPointParameterfARB, "glPointParameterfARB");
		FetchProcAddress(glPointParameterfvARB, "glPointParameterfvARB");

		//polygon offset clamp
		FetchProcAddress(glPolygonOffsetClamp, "glPolygonOffsetClamp");

		//program interface query
		FetchProcAddress(glGetProgramInterfaceiv, "glGetProgramInterfaceiv");
		FetchProcAddress(glGetProgramResourceIndex, "glGetProgramResourceIndex");
		FetchProcAddress(glGetProgramResourceLocation, "glGetProgramResourceLocation");
		FetchProcAddress(glGetProgramResourceLocationIndex, "glGetProgramResourceLocationIndex");
		FetchProcAddress(glGetProgramResourceName, "glGetProgramResourceName");
		FetchProcAddress(glGetProgramResourceiv, "glGetProgramResourceiv");

		//provoking vertex
		FetchProcAddress(glProvokingVertex, "glProvokingVertex");

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

		//sample locations
		FetchProcAddress(glFramebufferSampleLocationsfvARB, "glFramebufferSampleLocationsfvARB");
		FetchProcAddress(glNamedFramebufferSampleLocationsfvARB, "glNamedFramebufferSampleLocationsfvARB");

		//sample shading
		FetchProcAddress(glMinSampleShadingARB, "glMinSampleShadingARB");

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

		//shader atomic counters
		FetchProcAddress(glGetActiveAtomicCounterBufferiv, "glGetActiveAtomicCounterBufferiv");

		//shader image load store
		FetchProcAddress(glBindImageTexture, "glBindImageTexture");
		FetchProcAddress(glMemoryBarrier, "glMemoryBarrier");


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

		//shader storage buffer object
		FetchProcAddress(glShaderStorageBlockBinding, "glShaderStorageBlockBinding");

		//shader subroutine
		FetchProcAddress(glGetActiveSubroutineName, "glGetActiveSubroutineName");
		FetchProcAddress(glGetActiveSubroutineUniformName, "glGetActiveSubroutineUniformName");
		FetchProcAddress(glGetActiveSubroutineUniformiv, "glGetActiveSubroutineUniformiv");
		FetchProcAddress(glGetProgramStageiv, "glGetProgramStageiv");
		FetchProcAddress(glGetSubroutineIndex, "glGetSubroutineIndex");
		FetchProcAddress(glGetSubroutineUniformLocation, "glGetSubroutineUniformLocation");
		FetchProcAddress(glGetUniformSubroutineuiv, "glGetUniformSubroutineuiv");
		FetchProcAddress(glUniformSubroutinesuiv, "glUniformSubroutinesuiv");

		//shading language include
		FetchProcAddress(glCompileShaderIncludeARB, "glCompileShaderIncludeARB");
		FetchProcAddress(glDeleteNamedStringARB, "glDeleteNamedStringARB");
		FetchProcAddress(glGetNamedStringARB, "glGetNamedStringARB");
		FetchProcAddress(glGetNamedStringivARB, "glGetNamedStringivARB");
		FetchProcAddress(glIsNamedStringARB, "glIsNamedStringARB");
		FetchProcAddress(glNamedStringARB, "glNamedStringARB");

		//sparse buffer
		FetchProcAddress(glBufferPageCommitmentARB, "glBufferPageCommitmentARB");

		//sparse texture
		FetchProcAddress(glTexPageCommitmentARB, "glTexPageCommitmentARB");

		//sync
		FetchProcAddress(glClientWaitSync, "glClientWaitSync");
		FetchProcAddress(glDeleteSync, "glDeleteSync");
		FetchProcAddress(glFenceSync, "glFenceSync");
		FetchProcAddress(glGetInteger64v, "glGetInteger64v");
		FetchProcAddress(glGetSynciv, "glGetSynciv");
		FetchProcAddress(glIsSync, "glIsSync");
		FetchProcAddress(glWaitSync, "glWaitSync");

		//tessellation shader
		FetchProcAddress(glPatchParameterfv, "glPatchParameterfv");
		FetchProcAddress(glPatchParameteri, "glPatchParameteri");

		//texture barrier
		FetchProcAddress(glTextureBarrier, "glTextureBarrier");

		//texture buffer object
		FetchProcAddress(glTexBufferARB, "glTexBufferARB");

		//texture buffer range
		FetchProcAddress(glTexBufferRange, "glTexBufferRange");
		FetchProcAddress(glTextureBufferRangeEXT, "glTextureBufferRangeEXT");

		//texture compression
		FetchProcAddress(glCompressedTexImage1DARB, "glCompressedTexImage1DARB");
		FetchProcAddress(glCompressedTexImage2DARB, "glCompressedTexImage2DARB");
		FetchProcAddress(glCompressedTexImage3DARB, "glCompressedTexImage3DARB");
		FetchProcAddress(glCompressedTexSubImage1DARB, "glCompressedTexSubImage1DARB");
		FetchProcAddress(glCompressedTexSubImage2DARB, "glCompressedTexSubImage2DARB");
		FetchProcAddress(glCompressedTexSubImage3DARB, "glCompressedTexSubImage3DARB");
		FetchProcAddress(glGetCompressedTexImageARB, "glGetCompressedTexImageARB");

		//texture multisample
		FetchProcAddress(glGetMultisamplefv, "glGetMultisamplefv");
		FetchProcAddress(glSampleMaski, "glSampleMaski");
		FetchProcAddress(glTexImage2DMultisample, "glTexImage2DMultisample");
		FetchProcAddress(glTexImage3DMultisample, "glTexImage3DMultisample");

		//texture storage
		FetchProcAddress(glTexStorage1D, "glTexStorage1D");
		FetchProcAddress(glTexStorage2D, "glTexStorage2D");
		FetchProcAddress(glTexStorage3D, "glTexStorage3D");

		//texture storage multisample
		FetchProcAddress(glTexStorage2DMultisample, "glTexStorage2DMultisample");
		FetchProcAddress(glTexStorage3DMultisample, "glTexStorage3DMultisample");
		FetchProcAddress(glTextureStorage2DMultisampleEXT, "glTextureStorage2DMultisampleEXT");
		FetchProcAddress(glTextureStorage3DMultisampleEXT, "glTextureStorage3DMultisampleEXT");

		//texture view
		FetchProcAddress(glTextureView, "glTextureView");

		//timer query
		FetchProcAddress(glGetQueryObjecti64v, "glGetQueryObjecti64v");
		FetchProcAddress(glGetQueryObjectui64v, "glGetQueryObjectui64v");
		FetchProcAddress(glQueryCounter, "glQueryCounter");

		//transform feedback2
		FetchProcAddress(glBindTransformFeedback, "glBindTransformFeedback");
		FetchProcAddress(glDeleteTransformFeedbacks, "glDeleteTransformFeedbacks");
		FetchProcAddress(glDrawTransformFeedback, "glDrawTransformFeedback");
		FetchProcAddress(glGenTransformFeedbacks, "glGenTransformFeedbacks");
		FetchProcAddress(glIsTransformFeedback, "glIsTransformFeedback");
		FetchProcAddress(glPauseTransformFeedback, "glPauseTransformFeedback");
		FetchProcAddress(glResumeTransformFeedback, "glResumeTransformFeedback");

		//transform feedback3
		FetchProcAddress(glBeginQueryIndexed, "glBeginQueryIndexed");
		FetchProcAddress(glDrawTransformFeedbackStream, "glDrawTransformFeedbackStream");
		FetchProcAddress(glEndQueryIndexed, "glEndQueryIndexed");
		FetchProcAddress(glGetQueryIndexediv, "glGetQueryIndexediv");

		//transform feedback instanced
		FetchProcAddress(glDrawTransformFeedbackInstanced, "glDrawTransformFeedbackInstanced");
		FetchProcAddress(glDrawTransformFeedbackStreamInstanced, "glDrawTransformFeedbackStreamInstanced");

		//transpose matrix
		FetchProcAddress(glLoadTransposeMatrixdARB, "glLoadTransposeMatrixdARB");
		FetchProcAddress(glLoadTransposeMatrixfARB, "glLoadTransposeMatrixfARB");
		FetchProcAddress(glMultTransposeMatrixdARB, "glMultTransposeMatrixdARB");
		FetchProcAddress(glMultTransposeMatrixfARB, "glMultTransposeMatrixfARB");

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

		//vertex array object
		FetchProcAddress(glBindVertexArray, "glBindVertexArray");
		FetchProcAddress(glDeleteVertexArrays, "glDeleteVertexArrays");
		FetchProcAddress(glGenVertexArrays, "glGenVertexArrays");
		FetchProcAddress(glIsVertexArray, "glIsVertexArray");

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

		//vertex shader
		FetchProcAddress(glBindAttribLocationARB, "glBindAttribLocationARB");
		FetchProcAddress(glGetActiveAttribARB, "glGetActiveAttribARB");
		FetchProcAddress(glGetAttribLocationARB, "glGetAttribLocationARB");

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
	}

#pragma endregion ARB Extensions

	//OpenGL ARM Extensions
#pragma region ARM

	//mali program binary
	#define GL_MALI_PROGRAM_BINARY_ARM 0x8f61

	//mali shader binary
	#define GL_MALI_SHADER_BINARY_ARM 0x8f60

	//rgba8
	#define GL_RGBA8_OES 0x8058

	//shader framebuffer fetch
	#define GL_FETCH_PER_SAMPLE_ARM 0x8f65
	#define GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM 0x8f66

	//mali program binary
#define ARM_mali_program_binary 1
	//mali shader binary
#define ARM_mali_shader_binary 1
	//rgba8
#define ARM_rgba8 1
	//shader framebuffer fetch
#define ARM_shader_framebuffer_fetch 1
	//shader framebuffer fetch depth stencil
#define ARM_shader_framebuffer_fetch_depth_stencil 1

	//*< load ARM Extensions
	inline void LoadARMExtensions()
	{

	}

#pragma endregion ARM Extensions

	//OpenGL ATIX Extensions
#pragma region ATIX

	//point_sprites
	#define GL_TEXTURE_POINT_MODE_ATIX 0x60b0
	#define GL_TEXTURE_POINT_ONE_COORD_ATIX 0x60b1
	#define GL_TEXTURE_POINT_SPRITE_ATIX 0x60b2
	#define GL_POINT_SPRITE_CULL_MODE_ATIX 0x60b3
	#define GL_POINT_SPRITE_CULL_CENTER_ATIX 0x60b4
	#define GL_POINT_SPRITE_CULL_CLIP_ATIX 0x60b5
	#define GL_MODULATE_ADD_ATIX 0x8744
	#define GL_MODULATE_SIGNED_ADD_ATIX 0x8745
	#define GL_MODULATE_SUBTRACT_ATIX 0x8746
	#define GL_SECONDARY_COLOR_ATIX 0x8747
	#define GL_TEXTURE_OUTPUT_RGB_ATIX 0x8748
	#define GL_TEXTURE_OUTPUT_ALPHA_ATIX 0x8749
	#define GL_OUTPUT_POINT_SIZE_ATIX 0x610e

	//point sprites
#define atix_point_sprites 1

	//texture env combine3
#define atix_texture_env_combine3 1

	//texture env route
#define atix_texture_env_route 1

	//vertex shader output point size
#define atix_vertex_shader_output_point_size 1

	//*< load ATIX Extensions
	inline void LoadATIXExtensions()
	{

	}

#pragma endregion ATIX Extensions

	//OpenGL ATI Extensions
#pragma region ATI

#define GL_MAX_DRAW_BUFFERS_ATI 0x8824
#define GL_DRAW_BUFFER0_ATI 0x8825
#define GL_DRAW_BUFFER1_ATI 0x8826
#define GL_DRAW_BUFFER2_ATI 0x8827
#define GL_DRAW_BUFFER3_ATI 0x8828
#define GL_DRAW_BUFFER4_ATI 0x8829
#define GL_DRAW_BUFFER5_ATI 0x882a
#define GL_DRAW_BUFFER6_ATI 0x882b
#define GL_DRAW_BUFFER7_ATI 0x882c
#define GL_DRAW_BUFFER8_ATI 0x882d
#define GL_DRAW_BUFFER9_ATI 0x882e
#define GL_DRAW_BUFFER10_ATI 0x882f
#define GL_DRAW_BUFFER11_ATI 0x8830
#define GL_DRAW_BUFFER12_ATI 0x8831
#define GL_DRAW_BUFFER13_ATI 0x8832
#define GL_DRAW_BUFFER14_ATI 0x8833
#define GL_DRAW_BUFFER15_ATI 0x8834
#define GL_ELEMENT_ARRAY_ATI 0x8768
#define GL_ELEMENT_ARRAY_TYPE_ATI 0x8769
#define GL_ELEMENT_ARRAY_POINTER_ATI 0x876a
#define GL_BUMP_ROT_MATRIX_ATI 0x8775
#define GL_BUMP_ROT_MATRIX_SIZE_ATI 0x8776
#define GL_BUMP_NUM_TEX_UNITS_ATI 0x8777
#define GL_BUMP_TEX_UNITS_ATI 0x8778
#define GL_DUDV_ATI 0x8779
#define GL_DU8DV8_ATI 0x877a
#define GL_BUMP_ENVMAP_ATI 0x877b
#define GL_BUMP_TARGET_ATI 0x877c
#define GL_2X_BIT_ATI 0x00000001
#define GL_RED_BIT_ATI 0x00000001
#define GL_4X_BIT_ATI 0x00000002
#define GL_COMP_BIT_ATI 0x00000002
#define GL_GREEN_BIT_ATI 0x00000002
#define GL_8X_BIT_ATI 0x00000004
#define GL_BLUE_BIT_ATI 0x00000004
#define GL_NEGATE_BIT_ATI 0x00000004
#define GL_BIAS_BIT_ATI 0x00000008
#define GL_HALF_BIT_ATI 0x00000008
#define GL_QUARTER_BIT_ATI 0x00000010
#define GL_EIGHTH_BIT_ATI 0x00000020
#define GL_SATURATE_BIT_ATI 0x00000040
#define GL_FRAGMENT_SHADER_ATI 0x8920
#define GL_REG_0_ATI 0x8921
#define GL_REG_1_ATI 0x8922
#define GL_REG_2_ATI 0x8923
#define GL_REG_3_ATI 0x8924
#define GL_REG_4_ATI 0x8925
#define GL_REG_5_ATI 0x8926
#define GL_CON_0_ATI 0x8941
#define GL_CON_1_ATI 0x8942
#define GL_CON_2_ATI 0x8943
#define GL_CON_3_ATI 0x8944
#define GL_CON_4_ATI 0x8945
#define GL_CON_5_ATI 0x8946
#define GL_CON_6_ATI 0x8947
#define GL_CON_7_ATI 0x8948
#define GL_MOV_ATI 0x8961
#define GL_ADD_ATI 0x8963
#define GL_MUL_ATI 0x8964
#define GL_SUB_ATI 0x8965
#define GL_DOT3_ATI 0x8966
#define GL_DOT4_ATI 0x8967
#define GL_MAD_ATI 0x8968
#define GL_LERP_ATI 0x8969
#define GL_CND_ATI 0x896a
#define GL_CND0_ATI 0x896b
#define GL_DOT2_ADD_ATI 0x896c
#define GL_SECONDARY_INTERPOLATOR_ATI 0x896d
#define GL_NUM_FRAGMENT_REGISTERS_ATI 0x896e
#define GL_NUM_FRAGMENT_CONSTANTS_ATI 0x896f
#define GL_NUM_PASSES_ATI 0x8970
#define GL_NUM_INSTRUCTIONS_PER_PASS_ATI 0x8971
#define GL_NUM_INSTRUCTIONS_TOTAL_ATI 0x8972
#define GL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI 0x8973
#define GL_NUM_LOOPBACK_COMPONENTS_ATI 0x8974
#define GL_COLOR_ALPHA_PAIRING_ATI 0x8975
#define GL_SWIZZLE_STR_ATI 0x8976
#define GL_SWIZZLE_STQ_ATI 0x8977
#define GL_SWIZZLE_STR_DR_ATI 0x8978
#define GL_SWIZZLE_STQ_DQ_ATI 0x8979
#define GL_SWIZZLE_STRQ_ATI 0x897a
#define GL_SWIZZLE_STRQ_DQ_ATI 0x897b
#define GL_VBO_FREE_MEMORY_ATI 0x87fb
#define GL_TEXTURE_FREE_MEMORY_ATI 0x87fc
#define GL_RENDERBUFFER_FREE_MEMORY_ATI 0x87fd
#define GL_PN_TRIANGLES_ATI 0x87f0
#define GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI 0x87f1
#define GL_PN_TRIANGLES_POINT_MODE_ATI 0x87f2
#define GL_PN_TRIANGLES_NORMAL_MODE_ATI 0x87f3
#define GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI 0x87f4
#define GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI 0x87f5
#define GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI 0x87f6
#define GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI 0x87f7
#define GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI 0x87f8
#define GL_STENCIL_BACK_FUNC_ATI 0x8800
#define GL_STENCIL_BACK_FAIL_ATI 0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL_ATI 0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS_ATI 0x8803
#define GL_TEXT_FRAGMENT_SHADER_ATI 0x8200
#define GL_COMPRESSED_LUMINANCE_ALPHA_3DC_ATI 0x8837
#define GL_MODULATE_ADD_ATI 0x8744
#define GL_MODULATE_SIGNED_ADD_ATI 0x8745
#define GL_MODULATE_SUBTRACT_ATI 0x8746
#define GL_RGBA_FLOAT32_ATI 0x8814
#define GL_RGB_FLOAT32_ATI 0x8815
#define GL_ALPHA_FLOAT32_ATI 0x8816
#define GL_INTENSITY_FLOAT32_ATI 0x8817
#define GL_LUMINANCE_FLOAT32_ATI 0x8818
#define GL_LUMINANCE_ALPHA_FLOAT32_ATI 0x8819
#define GL_RGBA_FLOAT16_ATI 0x881a
#define GL_RGB_FLOAT16_ATI 0x881b
#define GL_ALPHA_FLOAT16_ATI 0x881c
#define GL_INTENSITY_FLOAT16_ATI 0x881d
#define GL_LUMINANCE_FLOAT16_ATI 0x881e
#define GL_LUMINANCE_ALPHA_FLOAT16_ATI 0x881f
#define GL_MIRROR_CLAMP_ATI 0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_ATI 0x8743
#define GL_STATIC_ATI 0x8760
#define GL_DYNAMIC_ATI 0x8761
#define GL_PRESERVE_ATI 0x8762
#define GL_DISCARD_ATI 0x8763
#define GL_OBJECT_BUFFER_SIZE_ATI 0x8764
#define GL_OBJECT_BUFFER_USAGE_ATI 0x8765
#define GL_ARRAY_OBJECT_BUFFER_ATI 0x8766
#define GL_ARRAY_OBJECT_OFFSET_ATI 0x8767
#define GL_MAX_VERTEX_STREAMS_ATI 0x876b
#define GL_VERTEX_SOURCE_ATI 0x876c
#define GL_VERTEX_STREAM0_ATI 0x876d
#define GL_VERTEX_STREAM1_ATI 0x876e
#define GL_VERTEX_STREAM2_ATI 0x876f
#define GL_VERTEX_STREAM3_ATI 0x8770
#define GL_VERTEX_STREAM4_ATI 0x8771
#define GL_VERTEX_STREAM5_ATI 0x8772
#define GL_VERTEX_STREAM6_ATI 0x8773
#define GL_VERTEX_STREAM7_ATI 0x8774

	//draw_buffers
	inline void(*glDrawBuffersATI) (GLsizei n, const GLenum * bufs) = nullptr;

#define ATI_draw_buffers 1

	//element_array
	inline void(*glDrawElementArrayATI) (GLenum mode, GLsizei count) = nullptr;
	inline void(*glDrawRangeElementArrayATI) (GLenum mode, GLuint start, GLuint end, GLsizei count) = nullptr;
	inline void(*glElementPointerATI) (GLenum type, const void* pointer) = nullptr;

#define ATI_element_array 1

	//envmap_bumpmap
	inline void(*glGetTexBumpParameterfvATI) (GLenum pname, GLfloat * param) = nullptr;
	inline void(*glGetTexBumpParameterivATI) (GLenum pname, GLint* param) = nullptr;
	inline void(*glTexBumpParameterfvATI) (GLenum pname, GLfloat* param) = nullptr;
	inline void(*glTexBumpParameterivATI) (GLenum pname, GLint* param) = nullptr;

#define ATI_envmap_bumpmap 1

	//fragment_shader
	inline void(*glAlphaFragmentOp1ATI) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod) = nullptr;
	inline void(*glAlphaFragmentOp2ATI) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod) = nullptr;
	inline void(*glAlphaFragmentOp3ATI) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod) = nullptr;
	inline void(*glBeginFragmentShaderATI) (void) = nullptr;
	inline void(*glBindFragmentShaderATI) (GLuint id) = nullptr;
	inline void(*glColorFragmentOp1ATI) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod) = nullptr;
	inline void(*glColorFragmentOp2ATI) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod) = nullptr;
	inline void(*glColorFragmentOp3ATI) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod) = nullptr;
	inline void(*glDeleteFragmentShaderATI) (GLuint id) = nullptr;
	inline void(*glEndFragmentShaderATI) (void) = nullptr;
	inline GLuint(*glGenFragmentShadersATI) (GLuint range) = nullptr;
	inline void(*glPassTexCoordATI) (GLuint dst, GLuint coord, GLenum swizzle) = nullptr;
	inline void(*glSampleMapATI) (GLuint dst, GLuint interp, GLenum swizzle) = nullptr;
	inline void(*glSetFragmentShaderConstantATI) (GLuint dst, const GLfloat* value) = nullptr;

#define ATI_fragment_shader 1

	//map_object_buffer
	inline void* (*glMapObjectBufferATI) (GLuint buffer) = nullptr;
	inline void(*glUnmapObjectBufferATI) (GLuint buffer) = nullptr;

#define ATI_map_object_buffer 1

	//meminfo
#define ATI_meminfo 1

	//pn_triangles
	inline void(*glPNTrianglesfATI) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glPNTrianglesiATI) (GLenum pname, GLint param) = nullptr;

#define ATI_pn_triangles 1

	//separate_stencil
	inline void(*glStencilFuncSeparateATI) (GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask) = nullptr;
	inline void(*glStencilOpSeparateATI) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) = nullptr;

#define ATI_separate_stencil 1

	//shader_texture_lod
#define ATI_shader_texture_lod 1

	//text_fragment_shader
#define ATI_text_fragment_shader 1

	//texture_compression_3dc
#define ATI_texture_compression_3dc 1

	//texture_env_combine3
#define ATI_texture_env_combine3 1

	//texture_float
#define ATI_texture_float 1

	//texture_mirror_once
#define ATI_texture_mirror_once 1

	//vertex_array_object
	inline void(*glArrayObjectATI) (GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset) = nullptr;
	inline void(*glFreeObjectBufferATI) (GLuint buffer) = nullptr;
	inline void(*glGetArrayObjectfvATI) (GLenum array, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetArrayObjectivATI) (GLenum array, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetObjectBufferfvATI) (GLuint buffer, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetObjectBufferivATI) (GLuint buffer, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetVariantArrayObjectfvATI) (GLuint id, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetVariantArrayObjectivATI) (GLuint id, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsObjectBufferATI) (GLuint buffer) = nullptr;
	inline GLuint(*glNewObjectBufferATI) (GLsizei size, const void* pointer, GLenum usage) = nullptr;
	inline void(*glUpdateObjectBufferATI) (GLuint buffer, GLuint offset, GLsizei size, const void* pointer, GLenum preserve) = nullptr;
	inline void(*glVariantArrayObjectATI) (GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset) = nullptr;

#define ATI_vertex_array_object 1

	//vertex_attrib_array_object
	inline void(*glGetVertexAttribArrayObjectfvATI) (GLuint index, GLenum pname, GLfloat * params) = nullptr;
	inline void(*glGetVertexAttribArrayObjectivATI) (GLuint index, GLenum pname, GLint* params) = nullptr;
	inline void(*glVertexAttribArrayObjectATI) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset) = nullptr;

#define ATI_vertex_attrib_array_object 1

	//vertex_streams
	inline void(*glClientActiveVertexStreamATI) (GLenum stream) = nullptr;
	inline void(*glNormalStream3bATI) (GLenum stream, GLbyte x, GLbyte y, GLbyte z) = nullptr;
	inline void(*glNormalStream3bvATI) (GLenum stream, const GLbyte* coords) = nullptr;
	inline void(*glNormalStream3dATI) (GLenum stream, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glNormalStream3dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	inline void(*glNormalStream3fATI) (GLenum stream, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glNormalStream3fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	inline void(*glNormalStream3iATI) (GLenum stream, GLint x, GLint y, GLint z) = nullptr;
	inline void(*glNormalStream3ivATI) (GLenum stream, const GLint* coords) = nullptr;
	inline void(*glNormalStream3sATI) (GLenum stream, GLshort x, GLshort y, GLshort z) = nullptr;
	inline void(*glNormalStream3svATI) (GLenum stream, const GLshort* coords) = nullptr;
	inline void(*glVertexBlendEnvfATI) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glVertexBlendEnviATI) (GLenum pname, GLint param) = nullptr;
	inline void(*glVertexStream1dATI) (GLenum stream, GLdouble x) = nullptr;
	inline void(*glVertexStream1dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	inline void(*glVertexStream1fATI) (GLenum stream, GLfloat x) = nullptr;
	inline void(*glVertexStream1fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	inline void(*glVertexStream1iATI) (GLenum stream, GLint x) = nullptr;
	inline void(*glVertexStream1ivATI) (GLenum stream, const GLint* coords) = nullptr;
	inline void(*glVertexStream1sATI) (GLenum stream, GLshort x) = nullptr;
	inline void(*glVertexStream1svATI) (GLenum stream, const GLshort* coords) = nullptr;
	inline void(*glVertexStream2dATI) (GLenum stream, GLdouble x, GLdouble y) = nullptr;
	inline void(*glVertexStream2dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	inline void(*glVertexStream2fATI) (GLenum stream, GLfloat x, GLfloat y) = nullptr;
	inline void(*glVertexStream2fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	inline void(*glVertexStream2iATI) (GLenum stream, GLint x, GLint y) = nullptr;
	inline void(*glVertexStream2ivATI) (GLenum stream, const GLint* coords) = nullptr;
	inline void(*glVertexStream2sATI) (GLenum stream, GLshort x, GLshort y) = nullptr;
	inline void(*glVertexStream2svATI) (GLenum stream, const GLshort* coords) = nullptr;
	inline void(*glVertexStream3dATI) (GLenum stream, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glVertexStream3dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	inline void(*glVertexStream3fATI) (GLenum stream, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glVertexStream3fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	inline void(*glVertexStream3iATI) (GLenum stream, GLint x, GLint y, GLint z) = nullptr;
	inline void(*glVertexStream3ivATI) (GLenum stream, const GLint* coords) = nullptr;
	inline void(*glVertexStream3sATI) (GLenum stream, GLshort x, GLshort y, GLshort z) = nullptr;
	inline void(*glVertexStream3svATI) (GLenum stream, const GLshort* coords) = nullptr;
	inline void(*glVertexStream4dATI) (GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glVertexStream4dvATI) (GLenum stream, const GLdouble* coords) = nullptr;
	inline void(*glVertexStream4fATI) (GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glVertexStream4fvATI) (GLenum stream, const GLfloat* coords) = nullptr;
	inline void(*glVertexStream4iATI) (GLenum stream, GLint x, GLint y, GLint z, GLint w) = nullptr;
	inline void(*glVertexStream4ivATI) (GLenum stream, const GLint* coords) = nullptr;
	inline void(*glVertexStream4sATI) (GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
	inline void(*glVertexStream4svATI) (GLenum stream, const GLshort* coords) = nullptr;

#define ATI_vertex_streams 1

	//*< load ATI Extensions
	inline void LoadATIExtensions()
	{
		//draw_buffers
		FetchProcAddress(glDrawBuffersATI, "glDrawBuffersATI");

		//element_array
		FetchProcAddress(glDrawElementArrayATI, "glDrawElementArrayATI");
		FetchProcAddress(glDrawRangeElementArrayATI, "glDrawRangeElementArrayATI");
		FetchProcAddress(glElementPointerATI, "glElementPointerATI");

		//envmap_bumpmap
		FetchProcAddress(glGetTexBumpParameterfvATI, "glGetTexBumpParameterfvATI");
		FetchProcAddress(glGetTexBumpParameterivATI, "glGetTexBumpParameterivATI");
		FetchProcAddress(glTexBumpParameterfvATI, "glTexBumpParameterfvATI");
		FetchProcAddress(glTexBumpParameterivATI, "glTexBumpParameterivATI");

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

		//map_object_buffer
		FetchProcAddress(glMapObjectBufferATI, "glMapObjectBufferATI");
		FetchProcAddress(glUnmapObjectBufferATI, "glUnmapObjectBufferATI");

		//pn_triangles
		FetchProcAddress(glPNTrianglesfATI, "glPNTrianglesfATI");
		FetchProcAddress(glPNTrianglesiATI, "glPNTrianglesiATI");

		//separate_stencil
		FetchProcAddress(glStencilFuncSeparateATI, "glStencilFuncSeparateATI");
		FetchProcAddress(glStencilOpSeparateATI, "glStencilOpSeparateATI");

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

		//vertex_attrib_array_object
		FetchProcAddress(glGetVertexAttribArrayObjectfvATI, "glGetVertexAttribArrayObjectfvATI");
		FetchProcAddress(glGetVertexAttribArrayObjectivATI, "glGetVertexAttribArrayObjectivATI");
		FetchProcAddress(glVertexAttribArrayObjectATI, "glVertexAttribArrayObjectATI");

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
	}

#pragma endregion ATI Extensions

	//OpenGL EGL_KHR Extensions
#pragma region EGL_KHR

	//context  flush control
#define EGL_KHR_context_flush_control 1

	//*< load EGL_KHR Extensions
	inline void LoadEGLKHRExtensions()
	{

	}

#pragma endregion EGL_KHR Extensions

	//OpenGL EGL_NV Extensions
#pragma region EGL_NV

	//robustness video memory purge
	#define GL_EGL_GENERATE_RESET_ON_VIDEO_MEMORY_PURGE_NV 0x334c
	#define GL_PURGED_CONTEXT_RESET_NV 0x92bb

	//robustness video memory purge
#define EGL_NV_robustness_video_memory_purge 1

	//*< load EGL_NV Extensions
	inline void LoadEGLNVExtensions()
	{

	}

#pragma endregion EGL_NV Extensions

	//OpenGL EXT Extensions
#pragma region EXT

	typedef void* GLeglClientBufferEXT;

#define GL_422_EXT 0x80cc
#define GL_422_REV_EXT 0x80cd
#define GL_422_AVERAGE_EXT 0x80ce
#define GL_422_REV_AVERAGE_EXT 0x80cf
#define GL_CG_VERTEX_SHADER_EXT 0x890e
#define GL_CG_FRAGMENT_SHADER_EXT 0x890f
#define GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT 0x8be7
#define GL_ABGR_EXT 0x8000
#define GL_BGR_EXT 0x80e0
#define GL_BGRA_EXT 0x80e1
#define GL_MAX_VERTEX_BINDABLE_UNIFORMS_EXT 0x8de2
#define GL_MAX_FRAGMENT_BINDABLE_UNIFORMS_EXT 0x8de3
#define GL_MAX_GEOMETRY_BINDABLE_UNIFORMS_EXT 0x8de4
#define GL_MAX_BINDABLE_UNIFORM_SIZE_EXT 0x8ded
#define GL_UNIFORM_BUFFER_EXT 0x8dee
#define GL_UNIFORM_BUFFER_BINDING_EXT 0x8def
#define GL_CONSTANT_COLOR_EXT 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR_EXT 0x8002
#define GL_CONSTANT_ALPHA_EXT 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA_EXT 0x8004
#define GL_BLEND_COLOR_EXT 0x8005
#define GL_BLEND_EQUATION_RGB_EXT 0x8009
#define GL_BLEND_EQUATION_ALPHA_EXT 0x883d
#define GL_SRC_ALPHA_SATURATE_EXT 0x0308
#define GL_SRC1_ALPHA_EXT 0x8589
#define GL_SRC1_COLOR_EXT 0x88f9
#define GL_ONE_MINUS_SRC1_COLOR_EXT 0x88fa
#define GL_ONE_MINUS_SRC1_ALPHA_EXT 0x88fb
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS_EXT 0x88fc
#define GL_LOCATION_INDEX_EXT 0x930f
#define GL_BLEND_DST_RGB_EXT 0x80c8
#define GL_BLEND_SRC_RGB_EXT 0x80c9
#define GL_BLEND_DST_ALPHA_EXT 0x80ca
#define GL_BLEND_SRC_ALPHA_EXT 0x80cb
#define GL_FUNC_ADD_EXT 0x8006
#define GL_MIN_EXT 0x8007
#define GL_MAX_EXT 0x8008
#define GL_BLEND_EQUATION_EXT 0x8009
#define GL_FUNC_SUBTRACT_EXT 0x800a
#define GL_FUNC_REVERSE_SUBTRACT_EXT 0x800b
#define GL_MAP_READ_BIT_EXT 0x0001
#define GL_MAP_WRITE_BIT_EXT 0x0002
#define GL_MAP_PERSISTENT_BIT_EXT 0x0040
#define GL_MAP_COHERENT_BIT_EXT 0x0080
#define GL_DYNAMIC_STORAGE_BIT_EXT 0x0100
#define GL_CLIENT_STORAGE_BIT_EXT 0x0200
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT_EXT 0x00004000
#define GL_BUFFER_IMMUTABLE_STORAGE_EXT 0x821f
#define GL_BUFFER_STORAGE_FLAGS_EXT 0x8220
#define GL_MAX_CLIP_DISTANCES_EXT 0x0d32
#define GL_CLIP_DISTANCE0_EXT 0x3000
#define GL_CLIP_DISTANCE1_EXT 0x3001
#define GL_CLIP_DISTANCE2_EXT 0x3002
#define GL_CLIP_DISTANCE3_EXT 0x3003
#define GL_CLIP_DISTANCE4_EXT 0x3004
#define GL_CLIP_DISTANCE5_EXT 0x3005
#define GL_CLIP_DISTANCE6_EXT 0x3006
#define GL_CLIP_DISTANCE7_EXT 0x3007
#define GL_MAX_CULL_DISTANCES_EXT 0x82f9
#define GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT 0x82fa
#define GL_CLIP_VOLUME_CLIPPING_HINT_EXT 0x80f0
#define GL_CMYK_EXT 0x800c
#define GL_CMYKA_EXT 0x800d
#define GL_PACK_CMYK_HINT_EXT 0x800e
#define GL_UNPACK_CMYK_HINT_EXT 0x800f
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT 0x8211
#define GL_R16F_EXT 0x822d
#define GL_RG16F_EXT 0x822f
#define GL_RGBA16F_EXT 0x881a
#define GL_RGB16F_EXT 0x881b
#define GL_UNSIGNED_NORMALIZED_EXT 0x8c17
#define GL_ARRAY_ELEMENT_LOCK_FIRST_EXT 0x81a8
#define GL_ARRAY_ELEMENT_LOCK_COUNT_EXT 0x81a9
#define GL_CONVOLUTION_1D_EXT 0x8010
#define GL_CONVOLUTION_2D_EXT 0x8011
#define GL_SEPARABLE_2D_EXT 0x8012
#define GL_CONVOLUTION_BORDER_MODE_EXT 0x8013
#define GL_CONVOLUTION_FILTER_SCALE_EXT 0x8014
#define GL_CONVOLUTION_FILTER_BIAS_EXT 0x8015
#define GL_REDUCE_EXT 0x8016
#define GL_CONVOLUTION_FORMAT_EXT 0x8017
#define GL_CONVOLUTION_WIDTH_EXT 0x8018
#define GL_CONVOLUTION_HEIGHT_EXT 0x8019
#define GL_MAX_CONVOLUTION_WIDTH_EXT 0x801a
#define GL_MAX_CONVOLUTION_HEIGHT_EXT 0x801b
#define GL_POST_CONVOLUTION_RED_SCALE_EXT 0x801c
#define GL_POST_CONVOLUTION_GREEN_SCALE_EXT 0x801d
#define GL_POST_CONVOLUTION_BLUE_SCALE_EXT 0x801e
#define GL_POST_CONVOLUTION_ALPHA_SCALE_EXT 0x801f
#define GL_POST_CONVOLUTION_RED_BIAS_EXT 0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS_EXT 0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS_EXT 0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS_EXT 0x8023
#define GL_TANGENT_ARRAY_EXT 0x8439
#define GL_BINORMAL_ARRAY_EXT 0x843a
#define GL_CURRENT_TANGENT_EXT 0x843b
#define GL_CURRENT_BINORMAL_EXT 0x843c
#define GL_TANGENT_ARRAY_TYPE_EXT 0x843e
#define GL_TANGENT_ARRAY_STRIDE_EXT 0x843f
#define GL_BINORMAL_ARRAY_TYPE_EXT 0x8440
#define GL_BINORMAL_ARRAY_STRIDE_EXT 0x8441
#define GL_TANGENT_ARRAY_POINTER_EXT 0x8442
#define GL_BINORMAL_ARRAY_POINTER_EXT 0x8443
#define GL_MAP1_TANGENT_EXT 0x8444
#define GL_MAP2_TANGENT_EXT 0x8445
#define GL_MAP1_BINORMAL_EXT 0x8446
#define GL_MAP2_BINORMAL_EXT 0x8447
#define GL_CULL_VERTEX_EXT 0x81aa
#define GL_CULL_VERTEX_EYE_POSITION_EXT 0x81ab
#define GL_CULL_VERTEX_OBJECT_POSITION_EXT 0x81ac
#define GL_PROGRAM_PIPELINE_OBJECT_EXT 0x8a4f
#define GL_PROGRAM_OBJECT_EXT 0x8b40
#define GL_SHADER_OBJECT_EXT 0x8b48
#define GL_BUFFER_OBJECT_EXT 0x9151
#define GL_QUERY_OBJECT_EXT 0x9153
#define GL_VERTEX_ARRAY_OBJECT_EXT 0x9154
#define GL_DEPTH_BOUNDS_TEST_EXT 0x8890
#define GL_DEPTH_BOUNDS_EXT 0x8891
#define GL_PROGRAM_MATRIX_EXT 0x8e2d
#define GL_TRANSPOSE_PROGRAM_MATRIX_EXT 0x8e2e
#define GL_PROGRAM_MATRIX_STACK_DEPTH_EXT 0x8e2f
#define GL_COLOR_EXT 0x1800
#define GL_DEPTH_EXT 0x1801
#define GL_STENCIL_EXT 0x1802
#define GL_MAX_DRAW_BUFFERS_EXT 0x8824
#define GL_DRAW_BUFFER0_EXT 0x8825
#define GL_DRAW_BUFFER1_EXT 0x8826
#define GL_DRAW_BUFFER2_EXT 0x8827
#define GL_DRAW_BUFFER3_EXT 0x8828
#define GL_DRAW_BUFFER4_EXT 0x8829
#define GL_DRAW_BUFFER5_EXT 0x882a
#define GL_DRAW_BUFFER6_EXT 0x882b
#define GL_DRAW_BUFFER7_EXT 0x882c
#define GL_DRAW_BUFFER8_EXT 0x882d
#define GL_DRAW_BUFFER9_EXT 0x882e
#define GL_DRAW_BUFFER10_EXT 0x882f
#define GL_DRAW_BUFFER11_EXT 0x8830
#define GL_DRAW_BUFFER12_EXT 0x8831
#define GL_DRAW_BUFFER13_EXT 0x8832
#define GL_DRAW_BUFFER14_EXT 0x8833
#define GL_DRAW_BUFFER15_EXT 0x8834
#define GL_MAX_COLOR_ATTACHMENTS_EXT 0x8cdf
#define GL_COLOR_ATTACHMENT0_EXT 0x8ce0
#define GL_COLOR_ATTACHMENT1_EXT 0x8ce1
#define GL_COLOR_ATTACHMENT2_EXT 0x8ce2
#define GL_COLOR_ATTACHMENT3_EXT 0x8ce3
#define GL_COLOR_ATTACHMENT4_EXT 0x8ce4
#define GL_COLOR_ATTACHMENT5_EXT 0x8ce5
#define GL_COLOR_ATTACHMENT6_EXT 0x8ce6
#define GL_COLOR_ATTACHMENT7_EXT 0x8ce7
#define GL_COLOR_ATTACHMENT8_EXT 0x8ce8
#define GL_COLOR_ATTACHMENT9_EXT 0x8ce9
#define GL_COLOR_ATTACHMENT10_EXT 0x8cea
#define GL_COLOR_ATTACHMENT11_EXT 0x8ceb
#define GL_COLOR_ATTACHMENT12_EXT 0x8cec
#define GL_COLOR_ATTACHMENT13_EXT 0x8ced
#define GL_COLOR_ATTACHMENT14_EXT 0x8cee
#define GL_COLOR_ATTACHMENT15_EXT 0x8cef
#define GL_MAX_ELEMENTS_VERTICES_EXT 0x80e8
#define GL_MAX_ELEMENTS_INDICES_EXT 0x80e9
#define GL_FOG_COORDINATE_SOURCE_EXT 0x8450
#define GL_FOG_COORDINATE_EXT 0x8451
#define GL_FRAGMENT_DEPTH_EXT 0x8452
#define GL_CURRENT_FOG_COORDINATE_EXT 0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE_EXT 0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE_EXT 0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER_EXT 0x8456
#define GL_FOG_COORDINATE_ARRAY_EXT 0x8457
#define GL_FRAGMENT_LIGHTING_EXT 0x8400
#define GL_FRAGMENT_COLOR_MATERIAL_EXT 0x8401
#define GL_FRAGMENT_COLOR_MATERIAL_FACE_EXT 0x8402
#define GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_EXT 0x8403
#define GL_MAX_FRAGMENT_LIGHTS_EXT 0x8404
#define GL_MAX_ACTIVE_LIGHTS_EXT 0x8405
#define GL_CURRENT_RASTER_NORMAL_EXT 0x8406
#define GL_LIGHT_ENV_MODE_EXT 0x8407
#define GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_EXT 0x8408
#define GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_EXT 0x8409
#define GL_FRAGMENT_LIGHT_MODEL_AMBIENT_EXT 0x840a
#define GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_EXT 0x840b
#define GL_FRAGMENT_LIGHT0_EXT 0x840c
#define GL_FRAGMENT_LIGHT7_EXT 0x8413
#define GL_DRAW_FRAMEBUFFER_BINDING_EXT 0x8ca6
#define GL_READ_FRAMEBUFFER_EXT 0x8ca8
#define GL_DRAW_FRAMEBUFFER_EXT 0x8ca9
#define GL_READ_FRAMEBUFFER_BINDING_EXT 0x8caa
#define GL_RENDERBUFFER_SAMPLES_EXT 0x8cab
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8d56
#define GL_MAX_SAMPLES_EXT 0x8d57
#define GL_SCALED_RESOLVE_FASTEST_EXT 0x90ba
#define GL_SCALED_RESOLVE_NICEST_EXT 0x90bb
#define GL_INVALID_FRAMEBUFFER_OPERATION_EXT 0x0506
#define GL_MAX_RENDERBUFFER_SIZE_EXT 0x84e8
#define GL_FRAMEBUFFER_BINDING_EXT 0x8ca6
#define GL_RENDERBUFFER_BINDING_EXT 0x8ca7
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT 0x8cd0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT 0x8cd1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT 0x8cd2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT 0x8cd3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT 0x8cd4
#define GL_FRAMEBUFFER_COMPLETE_EXT 0x8cd5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 0x8cd6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT 0x8cd7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT 0x8cd9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT 0x8cda
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT 0x8cdb
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT 0x8cdc
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT 0x8cdd
#define GL_DEPTH_ATTACHMENT_EXT 0x8d00
#define GL_STENCIL_ATTACHMENT_EXT 0x8d20
#define GL_FRAMEBUFFER_EXT 0x8d40
#define GL_RENDERBUFFER_EXT 0x8d41
#define GL_RENDERBUFFER_WIDTH_EXT 0x8d42
#define GL_RENDERBUFFER_HEIGHT_EXT 0x8d43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT 0x8d44
#define GL_STENCIL_INDEX1_EXT 0x8d46
#define GL_STENCIL_INDEX4_EXT 0x8d47
#define GL_STENCIL_INDEX8_EXT 0x8d48
#define GL_STENCIL_INDEX16_EXT 0x8d49
#define GL_RENDERBUFFER_RED_SIZE_EXT 0x8d50
#define GL_RENDERBUFFER_GREEN_SIZE_EXT 0x8d51
#define GL_RENDERBUFFER_BLUE_SIZE_EXT 0x8d52
#define GL_RENDERBUFFER_ALPHA_SIZE_EXT 0x8d53
#define GL_RENDERBUFFER_DEPTH_SIZE_EXT 0x8d54
#define GL_RENDERBUFFER_STENCIL_SIZE_EXT 0x8d55
#define GL_FRAMEBUFFER_SRGB_EXT 0x8db9
#define GL_FRAMEBUFFER_SRGB_CAPABLE_EXT 0x8dba
#define GL_GEOMETRY_SHADER_BIT_EXT 0x00000004
#define GL_LINES_ADJACENCY_EXT 0x000a
#define GL_LINE_STRIP_ADJACENCY_EXT 0x000b
#define GL_TRIANGLES_ADJACENCY_EXT 0x000c
#define GL_TRIANGLE_STRIP_ADJACENCY_EXT 0x000d
#define GL_LAYER_PROVOKING_VERTEX_EXT 0x825e
#define GL_UNDEFINED_VERTEX_EXT 0x8260
#define GL_GEOMETRY_SHADER_INVOCATIONS_EXT 0x887f
#define GL_GEOMETRY_LINKED_VERTICES_OUT_EXT 0x8916
#define GL_GEOMETRY_LINKED_INPUT_TYPE_EXT 0x8917
#define GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT 0x8918
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS_EXT 0x8a2c
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_EXT 0x8a32
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8c29
#define GL_PRIMITIVES_GENERATED_EXT 0x8c87
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8da7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8da8
#define GL_GEOMETRY_SHADER_EXT 0x8dd9
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT 0x8ddf
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8de0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT 0x8de1
#define GL_FIRST_VERTEX_CONVENTION_EXT 0x8e4d
#define GL_LAST_VERTEX_CONVENTION_EXT 0x8e4e
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT 0x8e5a
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT 0x90cd
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_EXT 0x90d7
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS_EXT 0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT 0x9124
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT 0x92cf
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT 0x92d5
#define GL_REFERENCED_BY_GEOMETRY_SHADER_EXT 0x9309
#define GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT 0x9312
#define GL_MAX_FRAMEBUFFER_LAYERS_EXT 0x9317

#define GL_LINES_ADJACENCY_EXT 0x000a
#define GL_LINE_STRIP_ADJACENCY_EXT 0x000b
#define GL_TRIANGLES_ADJACENCY_EXT 0x000c
#define GL_TRIANGLE_STRIP_ADJACENCY_EXT 0x000d
#define GL_PROGRAM_POINT_SIZE_EXT 0x8642
#define GL_MAX_VARYING_COMPONENTS_EXT 0x8b4b
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8c29
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT 0x8cd4
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8da7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8da8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_EXT 0x8da9
#define GL_GEOMETRY_SHADER_EXT 0x8dd9
#define GL_GEOMETRY_VERTICES_OUT_EXT 0x8dda
#define GL_GEOMETRY_INPUT_TYPE_EXT 0x8ddb
#define GL_GEOMETRY_OUTPUT_TYPE_EXT 0x8ddc
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_EXT 0x8ddd
#define GL_MAX_VERTEX_VARYING_COMPONENTS_EXT 0x8dde
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT 0x8ddf
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8de0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT 0x8de1

#define GL_VERTEX_ATTRIB_ARRAY_INTEGER_EXT 0x88fd
#define GL_SAMPLER_1D_ARRAY_EXT 0x8dc0
#define GL_SAMPLER_2D_ARRAY_EXT 0x8dc1
#define GL_SAMPLER_BUFFER_EXT 0x8dc2
#define GL_SAMPLER_1D_ARRAY_SHADOW_EXT 0x8dc3
#define GL_SAMPLER_2D_ARRAY_SHADOW_EXT 0x8dc4
#define GL_SAMPLER_CUBE_SHADOW_EXT 0x8dc5
#define GL_UNSIGNED_INT_VEC2_EXT 0x8dc6
#define GL_UNSIGNED_INT_VEC3_EXT 0x8dc7
#define GL_UNSIGNED_INT_VEC4_EXT 0x8dc8
#define GL_INT_SAMPLER_1D_EXT 0x8dc9
#define GL_INT_SAMPLER_2D_EXT 0x8dca
#define GL_INT_SAMPLER_3D_EXT 0x8dcb
#define GL_INT_SAMPLER_CUBE_EXT 0x8dcc
#define GL_INT_SAMPLER_2D_RECT_EXT 0x8dcd
#define GL_INT_SAMPLER_1D_ARRAY_EXT 0x8dce
#define GL_INT_SAMPLER_2D_ARRAY_EXT 0x8dcf
#define GL_INT_SAMPLER_BUFFER_EXT 0x8dd0
#define GL_UNSIGNED_INT_SAMPLER_1D_EXT 0x8dd1
#define GL_UNSIGNED_INT_SAMPLER_2D_EXT 0x8dd2
#define GL_UNSIGNED_INT_SAMPLER_3D_EXT 0x8dd3
#define GL_UNSIGNED_INT_SAMPLER_CUBE_EXT 0x8dd4
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT_EXT 0x8dd5
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY_EXT 0x8dd6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY_EXT 0x8dd7
#define GL_UNSIGNED_INT_SAMPLER_BUFFER_EXT 0x8dd8

#define GL_HISTOGRAM_EXT 0x8024
#define GL_PROXY_HISTOGRAM_EXT 0x8025
#define GL_HISTOGRAM_WIDTH_EXT 0x8026
#define GL_HISTOGRAM_FORMAT_EXT 0x8027
#define GL_HISTOGRAM_RED_SIZE_EXT 0x8028
#define GL_HISTOGRAM_GREEN_SIZE_EXT 0x8029
#define GL_HISTOGRAM_BLUE_SIZE_EXT 0x802a
#define GL_HISTOGRAM_ALPHA_SIZE_EXT 0x802b
#define GL_HISTOGRAM_LUMINANCE_SIZE_EXT 0x802c
#define GL_HISTOGRAM_SINK_EXT 0x802d
#define GL_MINMAX_EXT 0x802e
#define GL_MINMAX_FORMAT_EXT 0x802f
#define GL_MINMAX_SINK_EXT 0x8030
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_EXT 0x88fe
#define GL_FRAGMENT_MATERIAL_EXT 0x8349
#define GL_FRAGMENT_NORMAL_EXT 0x834a
#define GL_FRAGMENT_COLOR_EXT 0x834c
#define GL_ATTENUATION_EXT 0x834d
#define GL_SHADOW_ATTENUATION_EXT 0x834e
#define GL_TEXTURE_APPLICATION_MODE_EXT 0x834f
#define GL_TEXTURE_LIGHT_EXT 0x8350
#define GL_TEXTURE_MATERIAL_FACE_EXT 0x8351
#define GL_TEXTURE_MATERIAL_PARAMETER_EXT 0x8352

#define GL_MAP_READ_BIT_EXT 0x0001
#define GL_MAP_WRITE_BIT_EXT 0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT_EXT 0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT_EXT 0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT_EXT 0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT_EXT 0x0020
#define GL_UUID_SIZE_EXT 16
#define GL_TEXTURE_TILING_EXT 0x9580
#define GL_DEDICATED_MEMORY_OBJECT_EXT 0x9581
#define GL_NUM_TILING_TYPES_EXT 0x9582
#define GL_TILING_TYPES_EXT 0x9583
#define GL_OPTIMAL_TILING_EXT 0x9584
#define GL_LINEAR_TILING_EXT 0x9585
#define GL_LAYOUT_GENERAL_EXT 0x958D
#define GL_LAYOUT_COLOR_ATTACHMENT_EXT 0x958E
#define GL_LAYOUT_DEPTH_STENCIL_ATTACHMENT_EXT 0x958F
#define GL_LAYOUT_DEPTH_STENCIL_READ_ONLY_EXT 0x9590
#define GL_LAYOUT_SHADER_READ_ONLY_EXT 0x9591
#define GL_LAYOUT_TRANSFER_SRC_EXT 0x9592
#define GL_LAYOUT_TRANSFER_DST_EXT 0x9593
#define GL_NUM_DEVICE_UUIDS_EXT 0x9596
#define GL_DEVICE_UUID_EXT 0x9597
#define GL_DRIVER_UUID_EXT 0x9598
#define GL_PROTECTED_MEMORY_OBJECT_EXT 0x959B
#define GL_HANDLE_TYPE_OPAQUE_FD_EXT 0x9586
#define GL_LUID_SIZE_EXT 8
#define GL_HANDLE_TYPE_OPAQUE_WIN32_EXT 0x9587
#define GL_HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT 0x9588
#define GL_HANDLE_TYPE_D3D12_TILEPOOL_EXT 0x9589
#define GL_HANDLE_TYPE_D3D12_RESOURCE_EXT 0x958A
#define GL_HANDLE_TYPE_D3D11_IMAGE_EXT 0x958B
#define GL_HANDLE_TYPE_D3D11_IMAGE_KMT_EXT 0x958C
#define GL_HANDLE_TYPE_D3D12_FENCE_EXT 0x9594
#define GL_D3D12_FENCE_VALUE_EXT 0x9595
#define GL_DEVICE_LUID_EXT 0x9599
#define GL_DEVICE_NODE_MASK_EXT 0x959A
#define GL_MULTISAMPLE_EXT 0x809D
#define GL_SAMPLE_ALPHA_TO_MASK_EXT 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_EXT 0x809F
#define GL_SAMPLE_MASK_EXT 0x80A0
#define GL_1PASS_EXT 0x80A1
#define GL_2PASS_0_EXT 0x80A2
#define GL_2PASS_1_EXT 0x80A3
#define GL_4PASS_0_EXT 0x80A4
#define GL_4PASS_1_EXT 0x80A5
#define GL_4PASS_2_EXT 0x80A6
#define GL_4PASS_3_EXT 0x80A7
#define GL_SAMPLE_BUFFERS_EXT 0x80A8
#define GL_SAMPLES_EXT 0x80A9
#define GL_SAMPLE_MASK_VALUE_EXT 0x80AA
#define GL_SAMPLE_MASK_INVERT_EXT 0x80AB
#define GL_SAMPLE_PATTERN_EXT 0x80AC
#define GL_MULTISAMPLE_BIT_EXT 0x20000000
#define GL_RENDERBUFFER_SAMPLES_EXT 0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#define GL_MAX_SAMPLES_EXT 0x8D57
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C

#define GL_DRAW_BUFFER_EXT 0x0c01
#define GL_READ_BUFFER_EXT 0x0c02
#define GL_COLOR_ATTACHMENT_EXT 0x90f0
#define GL_MULTIVIEW_EXT 0x90f1
#define GL_MAX_MULTIVIEW_BUFFERS_EXT 0x90f2

#define GL_DEPTH_STENCIL_EXT 0x84f9
#define GL_UNSIGNED_INT_24_8_EXT 0x84fa
#define GL_DEPTH24_STENCIL8_EXT 0x88f0
#define GL_TEXTURE_STENCIL_SIZE_EXT 0x88f1c

#define GL_R11F_G11F_B10F_EXT 0x8c3a
#define GL_UNSIGNED_INT_10F_11F_11F_REV_EXT 0x8c3b
#define GL_RGBA_SIGNED_COMPONENTS_EXT 0x8c3c

#define GL_UNSIGNED_BYTE_3_3_2_EXT 0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4_EXT 0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1_EXT 0x8034
#define GL_UNSIGNED_INT_8_8_8_8_EXT 0x8035
#define GL_UNSIGNED_INT_10_10_10_2_EXT 0x8036

#define GL_TEXTURE_1D 0x0de0
#define GL_TEXTURE_2D 0x0de1
#define GL_PROXY_TEXTURE_1D 0x8063
#define GL_PROXY_TEXTURE_2D 0x8064
#define GL_COLOR_TABLE_FORMAT_EXT 0x80d8
#define GL_COLOR_TABLE_WIDTH_EXT 0x80d9
#define GL_COLOR_TABLE_RED_SIZE_EXT 0x80da
#define GL_COLOR_TABLE_GREEN_SIZE_EXT 0x80db
#define GL_COLOR_TABLE_BLUE_SIZE_EXT 0x80dc
#define GL_COLOR_TABLE_ALPHA_SIZE_EXT 0x80dd
#define GL_COLOR_TABLE_LUMINANCE_SIZE_EXT 0x80de
#define GL_COLOR_TABLE_INTENSITY_SIZE_EXT 0x80df
#define GL_COLOR_INDEX1_EXT 0x80e2
#define GL_COLOR_INDEX2_EXT 0x80e3
#define GL_COLOR_INDEX4_EXT 0x80e4
#define GL_COLOR_INDEX8_EXT 0x80e5
#define GL_COLOR_INDEX12_EXT 0x80e6
#define GL_COLOR_INDEX16_EXT 0x80e7
#define GL_TEXTURE_INDEX_SIZE_EXT 0x80ed
#define GL_TEXTURE_CUBE_MAP_ARB 0x8513
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB 0x851b

#define GL_PIXEL_PACK_BUFFER_EXT 0x88eb
#define GL_PIXEL_UNPACK_BUFFER_EXT 0x88ec
#define GL_PIXEL_PACK_BUFFER_BINDING_EXT 0x88ed
#define GL_PIXEL_UNPACK_BUFFER_BINDING_EXT 0x88ef
#define GL_PIXEL_TRANSFORM_2D_EXT 0x8330
#define GL_PIXEL_MAG_FILTER_EXT 0x8331
#define GL_PIXEL_MIN_FILTER_EXT 0x8332
#define GL_PIXEL_CUBIC_WEIGHT_EXT 0x8333
#define GL_CUBIC_EXT 0x8334
#define GL_AVERAGE_EXT 0x8335
#define GL_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT 0x8336
#define GL_MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT 0x8337
#define GL_PIXEL_TRANSFORM_2D_MATRIX_EXT 0x8338

#define GL_POINT_SIZE_MIN_EXT 0x8126
#define GL_POINT_SIZE_MAX_EXT 0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT 0x8128
#define GL_DISTANCE_ATTENUATION_EXT 0x8129
#define GL_POLYGON_OFFSET_EXT 0x8037
#define GL_POLYGON_OFFSET_FACTOR_EXT 0x8038
#define GL_POLYGON_OFFSET_BIAS_EXT 0x8039
#define GL_POLYGON_OFFSET_CLAMP_EXT 0x8e1b

#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION_EXT 0x8e4c
#define GL_FIRST_VERTEX_CONVENTION_EXT 0x8E4D
#define GL_LAST_VERTEX_CONVENTION_EXT 0x8E4E
#define GL_PROVOKING_VERTEX_EXT 0x8e4f

#define GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8a54
#define GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8a55
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8a56
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8a57

#define GL_COLOR_SAMPLES_NV 0x8e20
#define GL_RASTER_MULTISAMPLE_EXT 0x9327
#define GL_RASTER_SAMPLES_EXT 0x9328
#define GL_MAX_RASTER_SAMPLES_EXT 0x9329
#define GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932a
#define GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932b
#define GL_EFFECTIVE_RASTER_SAMPLES_EXT 0x932c
#define GL_DEPTH_SAMPLES_NV 0x932d
#define GL_STENCIL_SAMPLES_NV 0x932e
#define GL_MIXED_DEPTH_SAMPLES_SUPPORTED_NV 0x932f
#define GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#define GL_COVERAGE_MODULATION_TABLE_NV 0x9331
#define GL_COVERAGE_MODULATION_NV 0x9332
#define GL_COVERAGE_MODULATION_TABLE_SIZE_NV 0x9333

#define GL_BGRA_EXT 0x80e1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366

#define GL_BYTE 0x1400
#define GL_SHORT 0x1402
#define GL_R8_SNORM 0x8f94
#define GL_RG8_SNORM 0x8f95
#define GL_RGBA8_SNORM 0x8f97
#define GL_R16_SNORM_EXT 0x8f98
#define GL_RG16_SNORM_EXT 0x8f99
#define GL_RGBA16_SNORM_EXT 0x8f9b

#define GL_RESCALE_NORMAL_EXT 0x803A
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#define GL_SRGB_EXT 0x8C40
#define GL_SRGB_ALPHA_EXT 0x8C42
#define GL_SRGB8_ALPHA8_EXT 0x8C43
#define GL_FRAMEBUFFER_SRGB_EXT 0x8DB9
#define GL_COLOR_SUM_EXT 0x8458
#define GL_CURRENT_SECONDARY_COLOR_EXT 0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE_EXT 0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE_EXT 0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT 0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER_EXT 0x845D
#define GL_SECONDARY_COLOR_ARRAY_EXT 0x845E
#define GL_ACTIVE_PROGRAM_EXT 0x8B8D
#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT 0x81F8
#define GL_SINGLE_COLOR_EXT 0x81F9
#define GL_SEPARATE_SPECULAR_COLOR_EXT 0x81FA
#define GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT_EXT 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT_EXT 0x00000002
#define GL_UNIFORM_BARRIER_BIT_EXT 0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT_EXT 0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT_EXT 0x00000020
#define GL_COMMAND_BARRIER_BIT_EXT 0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT_EXT 0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT_EXT 0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT_EXT 0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT_EXT 0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT_EXT 0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT_EXT 0x00001000
#define GL_MAX_IMAGE_UNITS_EXT 0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS_EXT 0x8F39
#define GL_IMAGE_BINDING_NAME_EXT 0x8F3A
#define GL_IMAGE_BINDING_LEVEL_EXT 0x8F3B
#define GL_IMAGE_BINDING_LAYERED_EXT 0x8F3C
#define GL_IMAGE_BINDING_LAYER_EXT 0x8F3D
#define GL_IMAGE_BINDING_ACCESS_EXT 0x8F3E
#define GL_IMAGE_1D_EXT 0x904C
#define GL_IMAGE_2D_EXT 0x904D
#define GL_IMAGE_3D_EXT 0x904E
#define GL_IMAGE_2D_RECT_EXT 0x904F
#define GL_IMAGE_CUBE_EXT 0x9050
#define GL_IMAGE_BUFFER_EXT 0x9051
#define GL_IMAGE_1D_ARRAY_EXT 0x9052
#define GL_IMAGE_2D_ARRAY_EXT 0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY_EXT 0x9054
#define GL_IMAGE_2D_MULTISAMPLE_EXT 0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY_EXT 0x9056
#define GL_INT_IMAGE_1D_EXT 0x9057
#define GL_INT_IMAGE_2D_EXT 0x9058
#define GL_INT_IMAGE_3D_EXT 0x9059
#define GL_INT_IMAGE_2D_RECT_EXT 0x905A
#define GL_INT_IMAGE_CUBE_EXT 0x905B
#define GL_INT_IMAGE_BUFFER_EXT 0x905C
#define GL_INT_IMAGE_1D_ARRAY_EXT 0x905D
#define GL_INT_IMAGE_2D_ARRAY_EXT 0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE_EXT 0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT 0x9061
#define GL_UNSIGNED_INT_IMAGE_1D_EXT 0x9062
#define GL_UNSIGNED_INT_IMAGE_2D_EXT 0x9063
#define GL_UNSIGNED_INT_IMAGE_3D_EXT 0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT_EXT 0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE_EXT 0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER_EXT 0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY_EXT 0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY_EXT 0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_EXT 0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT 0x906C
#define GL_MAX_IMAGE_SAMPLES_EXT 0x906D
#define GL_IMAGE_BINDING_FORMAT_EXT 0x906E
#define GL_ALL_BARRIER_BITS_EXT 0xFFFFFFFF

#define GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_SIZE_EXT 0x8F63
#define GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64
#define GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_SIZE_EXT 0x8F67
#define GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_SIZE_EXT 0x9650
#define GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_SIZE_EXT 0x9651
#define GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
#define GL_TEXTURE_COMPARE_MODE_EXT 0x884C
#define GL_TEXTURE_COMPARE_FUNC_EXT 0x884D
#define GL_COMPARE_REF_TO_TEXTURE_EXT 0x884E
#define GL_SAMPLER_2D_SHADOW_EXT 0x8B62
#define GL_SHARED_TEXTURE_PALETTE_EXT 0x81FB
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_3D 0x806F
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_2D_ARRAY 0x8C1A
#define GL_TEXTURE_CUBE_MAP_ARRAY_OES 0x9009
#define GL_VIRTUAL_PAGE_SIZE_X_EXT 0x9195
#define GL_VIRTUAL_PAGE_SIZE_Y_EXT 0x9196
#define GL_VIRTUAL_PAGE_SIZE_Z_EXT 0x9197
#define GL_MAX_SPARSE_TEXTURE_SIZE_EXT 0x9198
#define GL_MAX_SPARSE_3D_TEXTURE_SIZE_EXT 0x9199
#define GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#define GL_TEXTURE_SPARSE_EXT 0x91A6
#define GL_VIRTUAL_PAGE_SIZE_INDEX_EXT 0x91A7
#define GL_NUM_VIRTUAL_PAGE_SIZES_EXT 0x91A8
#define GL_SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
#define GL_NUM_SPARSE_LEVELS_EXT 0x91AA
#define GL_STENCIL_TAG_BITS_EXT 0x88F2
#define GL_STENCIL_CLEAR_TAG_VALUE_EXT 0x88F3
#define GL_STENCIL_TEST_TWO_SIDE_EXT 0x8910
#define GL_ACTIVE_STENCIL_FACE_EXT 0x8911
#define GL_INCR_WRAP_EXT 0x8507
#define GL_DECR_WRAP_EXT 0x8508
#define GL_ALPHA4_EXT 0x803B
#define GL_ALPHA8_EXT 0x803C
#define GL_ALPHA12_EXT 0x803D
#define GL_ALPHA16_EXT 0x803E
#define GL_LUMINANCE4_EXT 0x803F
#define GL_LUMINANCE8_EXT 0x8040
#define GL_LUMINANCE12_EXT 0x8041
#define GL_LUMINANCE16_EXT 0x8042
#define GL_LUMINANCE4_ALPHA4_EXT 0x8043
#define GL_LUMINANCE6_ALPHA2_EXT 0x8044
#define GL_LUMINANCE8_ALPHA8_EXT 0x8045
#define GL_LUMINANCE12_ALPHA4_EXT 0x8046
#define GL_LUMINANCE12_ALPHA12_EXT 0x8047
#define GL_LUMINANCE16_ALPHA16_EXT 0x8048
#define GL_INTENSITY_EXT 0x8049
#define GL_INTENSITY4_EXT 0x804A
#define GL_INTENSITY8_EXT 0x804B
#define GL_INTENSITY12_EXT 0x804C
#define GL_INTENSITY16_EXT 0x804D
#define GL_RGB2_EXT 0x804E
#define GL_RGB4_EXT 0x804F
#define GL_RGB5_EXT 0x8050
#define GL_RGB8_EXT 0x8051
#define GL_RGB10_EXT 0x8052
#define GL_RGB12_EXT 0x8053
#define GL_RGB16_EXT 0x8054
#define GL_RGBA2_EXT 0x8055
#define GL_RGBA4_EXT 0x8056
#define GL_RGB5_A1_EXT 0x8057
#define GL_RGBA8_EXT 0x8058
#define GL_RGB10_A2_EXT 0x8059
#define GL_RGBA12_EXT 0x805A
#define GL_RGBA16_EXT 0x805B
#define GL_TEXTURE_RED_SIZE_EXT 0x805C
#define GL_TEXTURE_GREEN_SIZE_EXT 0x805D
#define GL_TEXTURE_BLUE_SIZE_EXT 0x805E
#define GL_TEXTURE_ALPHA_SIZE_EXT 0x805F
#define GL_TEXTURE_LUMINANCE_SIZE_EXT 0x8060
#define GL_TEXTURE_INTENSITY_SIZE_EXT 0x8061
#define GL_REPLACE_EXT 0x8062
#define GL_PROXY_TEXTURE_1D_EXT 0x8063
#define GL_PROXY_TEXTURE_2D_EXT 0x8064
#define GL_PACK_SKIP_IMAGES_EXT 0x806B
#define GL_PACK_IMAGE_HEIGHT_EXT 0x806C
#define GL_UNPACK_SKIP_IMAGES_EXT 0x806D
#define GL_UNPACK_IMAGE_HEIGHT_EXT 0x806E
#define GL_TEXTURE_3D_EXT 0x806F
#define GL_PROXY_TEXTURE_3D_EXT 0x8070
#define GL_TEXTURE_DEPTH_EXT 0x8071
#define GL_TEXTURE_WRAP_R_EXT 0x8072
#define GL_MAX_3D_TEXTURE_SIZE_EXT 0x8073

#define GL_COMPARE_REF_DEPTH_TO_TEXTURE_EXT 0x884E
#define GL_MAX_ARRAY_TEXTURE_LAYERS_EXT 0x88FF
#define GL_TEXTURE_1D_ARRAY_EXT 0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY_EXT 0x8C19
#define GL_TEXTURE_2D_ARRAY_EXT 0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY_EXT 0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY_EXT 0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY_EXT 0x8C1D
#define GL_TEXTURE_BUFFER_EXT 0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE_EXT 0x8C2B
#define GL_TEXTURE_BINDING_BUFFER_EXT 0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING_EXT 0x8C2D
#define GL_TEXTURE_BUFFER_FORMAT_EXT 0x8C2E
#define GL_TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69
#define GL_COMPRESSED_RGBA_BPTC_UNORM_EXT 0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT 0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT 0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#define GL_COMPRESSED_LUMINANCE_LATC1_EXT 0x8C70
#define GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT 0x8C71
#define GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT 0x8C72
#define GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT 0x8C73
#define GL_COMPRESSED_RED_RGTC1_EXT 0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#define GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#define GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#define GL_NORMAL_MAP_EXT 0x8511
#define GL_REFLECTION_MAP_EXT 0x8512
#define GL_TEXTURE_CUBE_MAP_EXT 0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_EXT 0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT 0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_EXT 0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT 0x851C
#define GL_TEXTURE_CUBE_MAP_ARRAY_EXT 0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT 0x900A
#define GL_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT 0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900F
#define GL_IMAGE_CUBE_MAP_ARRAY_EXT 0x9054
#define GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x905F
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#define GL_CLAMP_TO_EDGE_EXT 0x812F

#define GL_COMBINE_EXT 0x8570
#define GL_COMBINE_RGB_EXT 0x8571
#define GL_COMBINE_ALPHA_EXT 0x8572
#define GL_RGB_SCALE_EXT 0x8573
#define GL_ADD_SIGNED_EXT 0x8574
#define GL_INTERPOLATE_EXT 0x8575
#define GL_CONSTANT_EXT 0x8576
#define GL_PRIMARY_COLOR_EXT 0x8577
#define GL_PREVIOUS_EXT 0x8578
#define GL_SOURCE0_RGB_EXT 0x8580
#define GL_SOURCE1_RGB_EXT 0x8581
#define GL_SOURCE2_RGB_EXT 0x8582
#define GL_SOURCE0_ALPHA_EXT 0x8588
#define GL_SOURCE1_ALPHA_EXT 0x8589
#define GL_SOURCE2_ALPHA_EXT 0x858A
#define GL_OPERAND0_RGB_EXT 0x8590
#define GL_OPERAND1_RGB_EXT 0x8591
#define GL_OPERAND2_RGB_EXT 0x8592
#define GL_OPERAND0_ALPHA_EXT 0x8598
#define GL_OPERAND1_ALPHA_EXT 0x8599
#define GL_OPERAND2_ALPHA_EXT 0x859A
#define GL_DOT3_RGB_EXT 0x8740
#define GL_DOT3_RGBA_EXT 0x8741
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#define GL_TEXTURE_REDUCTION_MODE_EXT 0x9366
#define GL_WEIGHTED_AVERAGE_EXT 0x9367
#define GL_BGRA_EXT 0x80E1
#define GL_RGBA32UI_EXT 0x8D70
#define GL_RGB32UI_EXT 0x8D71
#define GL_ALPHA32UI_EXT 0x8D72
#define GL_INTENSITY32UI_EXT 0x8D73
#define GL_LUMINANCE32UI_EXT 0x8D74
#define GL_LUMINANCE_ALPHA32UI_EXT 0x8D75
#define GL_RGBA16UI_EXT 0x8D76
#define GL_RGB16UI_EXT 0x8D77
#define GL_ALPHA16UI_EXT 0x8D78
#define GL_INTENSITY16UI_EXT 0x8D79
#define GL_LUMINANCE16UI_EXT 0x8D7A
#define GL_LUMINANCE_ALPHA16UI_EXT 0x8D7B
#define GL_RGBA8UI_EXT 0x8D7C
#define GL_RGB8UI_EXT 0x8D7D
#define GL_ALPHA8UI_EXT 0x8D7E
#define GL_INTENSITY8UI_EXT 0x8D7F
#define GL_LUMINANCE8UI_EXT 0x8D80
#define GL_LUMINANCE_ALPHA8UI_EXT 0x8D81
#define GL_RGBA32I_EXT 0x8D82
#define GL_RGB32I_EXT 0x8D83
#define GL_ALPHA32I_EXT 0x8D84
#define GL_INTENSITY32I_EXT 0x8D85
#define GL_LUMINANCE32I_EXT 0x8D86
#define GL_LUMINANCE_ALPHA32I_EXT 0x8D87
#define GL_RGBA16I_EXT 0x8D88
#define GL_RGB16I_EXT 0x8D89
#define GL_ALPHA16I_EXT 0x8D8A
#define GL_INTENSITY16I_EXT 0x8D8B
#define GL_LUMINANCE16I_EXT 0x8D8C
#define GL_LUMINANCE_ALPHA16I_EXT 0x8D8D
#define GL_RGBA8I_EXT 0x8D8E
#define GL_RGB8I_EXT 0x8D8F
#define GL_ALPHA8I_EXT 0x8D90
#define GL_INTENSITY8I_EXT 0x8D91
#define GL_LUMINANCE8I_EXT 0x8D92
#define GL_LUMINANCE_ALPHA8I_EXT 0x8D93
#define GL_RED_INTEGER_EXT 0x8D94
#define GL_GREEN_INTEGER_EXT 0x8D95
#define GL_BLUE_INTEGER_EXT 0x8D96
#define GL_ALPHA_INTEGER_EXT 0x8D97
#define GL_RGB_INTEGER_EXT 0x8D98
#define GL_RGBA_INTEGER_EXT 0x8D99
#define GL_BGR_INTEGER_EXT 0x8D9A
#define GL_BGRA_INTEGER_EXT 0x8D9B
#define GL_LUMINANCE_INTEGER_EXT 0x8D9C
#define GL_LUMINANCE_ALPHA_INTEGER_EXT 0x8D9D
#define GL_RGBA_INTEGER_MODE_EXT 0x8D9E
#define GL_MAX_TEXTURE_LOD_BIAS_EXT 0x84FD
#define GL_TEXTURE_FILTER_CONTROL_EXT 0x8500
#define GL_TEXTURE_LOD_BIAS_EXT 0x8501
#define GL_MIRROR_CLAMP_EXT 0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_EXT 0x8743
#define GL_MIRROR_CLAMP_TO_BORDER_EXT 0x8912

#define GL_RGB16_EXT 0x8054
#define GL_RGBA16_EXT 0x805B
#define GL_R16_EXT 0x822A
#define GL_RG16_EXT 0x822C
#define GL_R16_SNORM_EXT 0x8F98
#define GL_RG16_SNORM_EXT 0x8F99
#define GL_RGB16_SNORM_EXT 0x8F9A
#define GL_RGBA16_SNORM_EXT 0x8F9B
#define GL_TEXTURE_PRIORITY_EXT 0x8066
#define GL_TEXTURE_RESIDENT_EXT 0x8067
#define GL_TEXTURE_1D_BINDING_EXT 0x8068
#define GL_TEXTURE_2D_BINDING_EXT 0x8069
#define GL_TEXTURE_3D_BINDING_EXT 0x806A
#define GL_PERTURB_EXT 0x85AE
#define GL_TEXTURE_NORMAL_EXT 0x85AF
#define GL_TEXTURE_RECTANGLE_EXT 0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_EXT 0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_EXT 0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_EXT 0x84F8
#define GL_RED_EXT 0x1903
#define GL_RG_EXT 0x8227
#define GL_R8_EXT 0x8229
#define GL_RG8_EXT 0x822B
#define GL_SRGB_EXT 0x8C40
#define GL_SRGB8_EXT 0x8C41
#define GL_SRGB_ALPHA_EXT 0x8C42
#define GL_SRGB8_ALPHA8_EXT 0x8C43
#define GL_SLUMINANCE_ALPHA_EXT 0x8C44
#define GL_SLUMINANCE8_ALPHA8_EXT 0x8C45
#define GL_SLUMINANCE_EXT 0x8C46
#define GL_SLUMINANCE8_EXT 0x8C47
#define GL_COMPRESSED_SRGB_EXT 0x8C48
#define GL_COMPRESSED_SRGB_ALPHA_EXT 0x8C49
#define GL_COMPRESSED_SLUMINANCE_EXT 0x8C4A
#define GL_COMPRESSED_SLUMINANCE_ALPHA_EXT 0x8C4B
#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT 0x8C4C
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#define GL_SR8_EXT 0x8FBD
#define GL_SRG8_EXT 0x8FBE
#define GL_TEXTURE_SRGB_DECODE_EXT 0x8A48
#define GL_DECODE_EXT 0x8A49
#define GL_SKIP_DECODE_EXT 0x8A4A
#define GL_RGB9_E5_EXT 0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV_EXT 0x8C3E
#define GL_TEXTURE_SHARED_SIZE_EXT 0x8C3F
#define GL_RED_SNORM 0x8F90
#define GL_RG_SNORM 0x8F91
#define GL_RGB_SNORM 0x8F92
#define GL_RGBA_SNORM 0x8F93
#define GL_R8_SNORM 0x8F94
#define GL_RG8_SNORM 0x8F95
#define GL_RGB8_SNORM 0x8F96
#define GL_RGBA8_SNORM 0x8F97
#define GL_R16_SNORM 0x8F98
#define GL_RG16_SNORM 0x8F99
#define GL_RGB16_SNORM 0x8F9A
#define GL_RGBA16_SNORM 0x8F9B
#define GL_SIGNED_NORMALIZED 0x8F9C
#define GL_ALPHA_SNORM 0x9010
#define GL_LUMINANCE_SNORM 0x9011
#define GL_LUMINANCE_ALPHA_SNORM 0x9012
#define GL_INTENSITY_SNORM 0x9013
#define GL_ALPHA8_SNORM 0x9014
#define GL_LUMINANCE8_SNORM 0x9015
#define GL_LUMINANCE8_ALPHA8_SNORM 0x9016
#define GL_INTENSITY8_SNORM 0x9017
#define GL_ALPHA16_SNORM 0x9018
#define GL_LUMINANCE16_SNORM 0x9019
#define GL_LUMINANCE16_ALPHA16_SNORM 0x901A
#define GL_INTENSITY16_SNORM 0x901B

#define GL_ALPHA8_EXT 0x803C
#define GL_LUMINANCE8_EXT 0x8040
#define GL_LUMINANCE8_ALPHA8_EXT 0x8045
#define GL_RGB10_EXT 0x8052
#define GL_RGB10_A2_EXT 0x8059
#define GL_R8_EXT 0x8229
#define GL_RG8_EXT 0x822B
#define GL_R16F_EXT 0x822D
#define GL_R32F_EXT 0x822E
#define GL_RG16F_EXT 0x822F
#define GL_RG32F_EXT 0x8230
#define GL_RGBA32F_EXT 0x8814
#define GL_RGB32F_EXT 0x8815
#define GL_ALPHA32F_EXT 0x8816
#define GL_LUMINANCE32F_EXT 0x8818
#define GL_LUMINANCE_ALPHA32F_EXT 0x8819
#define GL_RGBA16F_EXT 0x881A
#define GL_RGB16F_EXT 0x881B
#define GL_ALPHA16F_EXT 0x881C
#define GL_LUMINANCE16F_EXT 0x881E
#define GL_LUMINANCE_ALPHA16F_EXT 0x881F
#define GL_RGB_RAW_422_APPLE 0x8A51
#define GL_TEXTURE_IMMUTABLE_FORMAT_EXT 0x912F
#define GL_BGRA8_EXT 0x93A1
#define GL_TEXTURE_SWIZZLE_R_EXT 0x8E42
#define GL_TEXTURE_SWIZZLE_G_EXT 0x8E43
#define GL_TEXTURE_SWIZZLE_B_EXT 0x8E44
#define GL_TEXTURE_SWIZZLE_A_EXT 0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA_EXT 0x8E46
#define GL_UNSIGNED_INT_2_10_10_10_REV_EXT 0x8368
#define GL_TEXTURE_VIEW_MIN_LEVEL_EXT 0x82DB
#define GL_TEXTURE_VIEW_NUM_LEVELS_EXT 0x82DC
#define GL_TEXTURE_VIEW_MIN_LAYER_EXT 0x82DD
#define GL_TEXTURE_VIEW_NUM_LAYERS_EXT 0x82DE
#define GL_TEXTURE_IMMUTABLE_LEVELS 0x82DF
#define GL_TIME_ELAPSED_EXT 0x88BF
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH_EXT 0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE_EXT 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_EXT 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS_EXT 0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START_EXT 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE_EXT 0x8C85
#define GL_PRIMITIVES_GENERATED_EXT 0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_EXT 0x8C88
#define GL_RASTERIZER_DISCARD_EXT 0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_EXT 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_EXT 0x8C8B
#define GL_INTERLEAVED_ATTRIBS_EXT 0x8C8C
#define GL_SEPARATE_ATTRIBS_EXT 0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER_EXT 0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING_EXT 0x8C8F
#define GL_UNPACK_ROW_LENGTH_EXT 0x0CF2
#define GL_UNPACK_SKIP_ROWS_EXT 0x0CF3
#define GL_UNPACK_SKIP_PIXELS_EXT 0x0CF4
#define GL_DOUBLE_EXT 0x140A
#define GL_VERTEX_ARRAY_EXT 0x8074
#define GL_NORMAL_ARRAY_EXT 0x8075
#define GL_COLOR_ARRAY_EXT 0x8076
#define GL_INDEX_ARRAY_EXT 0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT 0x8078
#define GL_EDGE_FLAG_ARRAY_EXT 0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT 0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT 0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT 0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT 0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT 0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT 0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT 0x8080
#define GL_COLOR_ARRAY_SIZE_EXT 0x8081
#define GL_COLOR_ARRAY_TYPE_EXT 0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT 0x8083
#define GL_COLOR_ARRAY_COUNT_EXT 0x8084
#define GL_INDEX_ARRAY_TYPE_EXT 0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT 0x8086
#define GL_INDEX_ARRAY_COUNT_EXT 0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT 0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT 0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT 0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT 0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT 0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT 0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT 0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT 0x808F
#define GL_COLOR_ARRAY_POINTER_EXT 0x8090
#define GL_INDEX_ARRAY_POINTER_EXT 0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT 0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT 0x8093
#define GL_BGRA 0x80E1
#define GL_DOUBLE_MAT2_EXT 0x8F46
#define GL_DOUBLE_MAT3_EXT 0x8F47
#define GL_DOUBLE_MAT4_EXT 0x8F48
#define GL_DOUBLE_MAT2X3_EXT 0x8F49
#define GL_DOUBLE_MAT2X4_EXT 0x8F4A
#define GL_DOUBLE_MAT3X2_EXT 0x8F4B
#define GL_DOUBLE_MAT3X4_EXT 0x8F4C
#define GL_DOUBLE_MAT4X2_EXT 0x8F4D
#define GL_DOUBLE_MAT4X3_EXT 0x8F4E
#define GL_DOUBLE_VEC2_EXT 0x8FFC
#define GL_DOUBLE_VEC3_EXT 0x8FFD
#define GL_DOUBLE_VEC4_EXT 0x8FFE

#define GL_VERTEX_SHADER_EXT                         0x8780
#define GL_VERTEX_SHADER_BINDING_EXT                 0x8781
#define GL_OP_INDEX_EXT                              0x8782
#define GL_OP_NEGATE_EXT                             0x8783
#define GL_OP_DOT3_EXT                               0x8784
#define GL_OP_DOT4_EXT                               0x8785
#define GL_OP_MUL_EXT                                0x8786
#define GL_OP_ADD_EXT                                0x8787
#define GL_OP_MADD_EXT                               0x8788
#define GL_OP_FRAC_EXT                               0x8789
#define GL_OP_MAX_EXT                                0x878A
#define GL_OP_MIN_EXT                                0x878B
#define GL_OP_SET_GE_EXT                             0x878C
#define GL_OP_SET_LT_EXT                             0x878D
#define GL_OP_CLAMP_EXT                              0x878E
#define GL_OP_FLOOR_EXT                              0x878F
#define GL_OP_ROUND_EXT                              0x8790
#define GL_OP_EXP_BASE_2_EXT                         0x8791
#define GL_OP_LOG_BASE_2_EXT                         0x8792
#define GL_OP_POWER_EXT                              0x8793
#define GL_OP_RECIP_EXT                              0x8794
#define GL_OP_RECIP_SQRT_EXT                         0x8795
#define GL_OP_SUB_EXT                                0x8796
#define GL_OP_CROSS_PRODUCT_EXT                      0x8797
#define GL_OP_MULTIPLY_MATRIX_EXT                    0x8798
#define GL_OP_MOV_EXT                                0x8799
#define GL_OUTPUT_VERTEX_EXT                         0x879A
#define GL_OUTPUT_COLOR0_EXT                         0x879B
#define GL_OUTPUT_COLOR1_EXT                         0x879C
#define GL_OUTPUT_TEXTURE_COORD0_EXT                 0x879D
#define GL_OUTPUT_TEXTURE_COORD1_EXT                 0x879E
#define GL_OUTPUT_TEXTURE_COORD2_EXT                 0x879F
#define GL_OUTPUT_TEXTURE_COORD3_EXT                 0x87A0
#define GL_OUTPUT_TEXTURE_COORD4_EXT                 0x87A1
#define GL_OUTPUT_TEXTURE_COORD5_EXT                 0x87A2
#define GL_OUTPUT_TEXTURE_COORD6_EXT                 0x87A3
#define GL_OUTPUT_TEXTURE_COORD7_EXT                 0x87A4
#define GL_OUTPUT_TEXTURE_COORD8_EXT                 0x87A5
#define GL_OUTPUT_TEXTURE_COORD9_EXT                 0x87A6
#define GL_OUTPUT_TEXTURE_COORD10_EXT                0x87A7
#define GL_OUTPUT_TEXTURE_COORD11_EXT                0x87A8
#define GL_OUTPUT_TEXTURE_COORD12_EXT                0x87A9
#define GL_OUTPUT_TEXTURE_COORD13_EXT                0x87AA
#define GL_OUTPUT_TEXTURE_COORD14_EXT                0x87AB
#define GL_OUTPUT_TEXTURE_COORD15_EXT                0x87AC
#define GL_OUTPUT_TEXTURE_COORD16_EXT                0x87AD
#define GL_OUTPUT_TEXTURE_COORD17_EXT                0x87AE
#define GL_OUTPUT_TEXTURE_COORD18_EXT                0x87AF
#define GL_OUTPUT_TEXTURE_COORD19_EXT                0x87B0
#define GL_OUTPUT_TEXTURE_COORD20_EXT                0x87B1
#define GL_OUTPUT_TEXTURE_COORD21_EXT                0x87B2
#define GL_OUTPUT_TEXTURE_COORD22_EXT                0x87B3
#define GL_OUTPUT_TEXTURE_COORD23_EXT                0x87B4
#define GL_OUTPUT_TEXTURE_COORD24_EXT                0x87B5
#define GL_OUTPUT_TEXTURE_COORD25_EXT                0x87B6
#define GL_OUTPUT_TEXTURE_COORD26_EXT                0x87B7
#define GL_OUTPUT_TEXTURE_COORD27_EXT                0x87B8
#define GL_OUTPUT_TEXTURE_COORD28_EXT                0x87B9
#define GL_OUTPUT_TEXTURE_COORD29_EXT                0x87BA
#define GL_OUTPUT_TEXTURE_COORD30_EXT                0x87BB
#define GL_OUTPUT_TEXTURE_COORD31_EXT                0x87BC
#define GL_OUTPUT_FOG_EXT                            0x87BD
#define GL_SCALAR_EXT                                0x87BE
#define GL_VECTOR_EXT                                0x87BF
#define GL_MATRIX_EXT                                0x87C0
#define GL_VARIANT_EXT                               0x87C1
#define GL_INVARIANT_EXT                             0x87C2
#define GL_LOCAL_CONSTANT_EXT                        0x87C3
#define GL_LOCAL_EXT                                 0x87C4
#define GL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT        0x87C5
#define GL_MAX_VERTEX_SHADER_VARIANTS_EXT            0x87C6
#define GL_MAX_VERTEX_SHADER_INVARIANTS_EXT          0x87C7
#define GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT     0x87C8
#define GL_MAX_VERTEX_SHADER_LOCALS_EXT              0x87C9
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT 0x87CA
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT  0x87CB
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT 0x87CC
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT 0x87CD
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT    0x87CE
#define GL_VERTEX_SHADER_INSTRUCTIONS_EXT            0x87CF
#define GL_VERTEX_SHADER_VARIANTS_EXT                0x87D0
#define GL_VERTEX_SHADER_INVARIANTS_EXT              0x87D1
#define GL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT         0x87D2
#define GL_VERTEX_SHADER_LOCALS_EXT                  0x87D3
#define GL_VERTEX_SHADER_OPTIMIZED_EXT               0x87D4
#define GL_X_EXT                                     0x87D5
#define GL_Y_EXT                                     0x87D6
#define GL_Z_EXT                                     0x87D7
#define GL_W_EXT                                     0x87D8
#define GL_NEGATIVE_X_EXT                            0x87D9
#define GL_NEGATIVE_Y_EXT                            0x87DA
#define GL_NEGATIVE_Z_EXT                            0x87DB
#define GL_NEGATIVE_W_EXT                            0x87DC
#define GL_ZERO_EXT                                  0x87DD
#define GL_ONE_EXT                                   0x87DE
#define GL_NEGATIVE_ONE_EXT                          0x87DF
#define GL_NORMALIZED_RANGE_EXT                      0x87E0
#define GL_FULL_RANGE_EXT                            0x87E1
#define GL_CURRENT_VERTEX_EXT                        0x87E2
#define GL_MVP_MATRIX_EXT                            0x87E3
#define GL_VARIANT_VALUE_EXT                         0x87E4
#define GL_VARIANT_DATATYPE_EXT                      0x87E5
#define GL_VARIANT_ARRAY_STRIDE_EXT                  0x87E6
#define GL_VARIANT_ARRAY_TYPE_EXT                    0x87E7
#define GL_VARIANT_ARRAY_EXT                         0x87E8
#define GL_VARIANT_ARRAY_POINTER_EXT                 0x87E9
#define GL_INVARIANT_VALUE_EXT                       0x87EA
#define GL_INVARIANT_DATATYPE_EXT                    0x87EB
#define GL_LOCAL_CONSTANT_VALUE_EXT                  0x87EC
#define GL_LOCAL_CONSTANT_DATATYPE_EXT               0x87ED

#define GL_MODELVIEW0_STACK_DEPTH_EXT                0x0BA3
#define GL_MODELVIEW0_MATRIX_EXT                     0x0BA6
#define GL_MODELVIEW0_EXT                            0x1700
#define GL_MODELVIEW1_STACK_DEPTH_EXT                0x8502
#define GL_MODELVIEW1_MATRIX_EXT                     0x8506
#define GL_VERTEX_WEIGHTING_EXT                      0x8509
#define GL_MODELVIEW1_EXT                            0x850A
#define GL_CURRENT_VERTEX_WEIGHT_EXT                 0x850B
#define GL_VERTEX_WEIGHT_ARRAY_EXT                   0x850C
#define GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT              0x850D
#define GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT              0x850E
#define GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT            0x850F
#define GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT           0x8510

#define GL_INCLUSIVE_EXT                             0x8F10
#define GL_EXCLUSIVE_EXT                             0x8F11
#define GL_WINDOW_RECTANGLE_EXT                      0x8F12
#define GL_WINDOW_RECTANGLE_MODE_EXT                 0x8F13
#define GL_MAX_WINDOW_RECTANGLES_EXT                 0x8F14
#define GL_NUM_WINDOW_RECTANGLES_EXT                 0x8F15

#define GL_SYNC_X11_FENCE_EXT                        0x90E1

	//422 pixels
#define EXT_422_pixels 1

	//Cg shader
#define EXT_Cg_shader 1

	//EGL image array
#define EXT_EGL_image_array 1

	//YUV target
#define EXT_YUV_target 1

	//abgr
#define EXT_abgr 1

	//base instance
	inline void(*glDrawArraysInstancedBaseInstanceEXT) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) = nullptr;
	inline void(*glDrawElementsInstancedBaseInstanceEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLuint baseinstance) = nullptr;
	inline void(*glDrawElementsInstancedBaseVertexBaseInstanceEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) = nullptr;
#define EXT_base_instance 1

	//bgra
#define EXT_bgra 1

	//bindable uniform
	inline GLint(*glGetUniformBufferSizeEXT) (GLuint program, GLint location) = nullptr;
	inline GLintptr(*glGetUniformOffsetEXT) (GLuint program, GLint location) = nullptr;
	inline void(*glUniformBufferEXT) (GLuint program, GLint location, GLuint buffer) = nullptr;
#define EXT_bindable_uniform 1

	//blend color
	inline void(*glBlendColorEXT) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = nullptr;
#define EXT_blend_color 1

	//blend equation separate
	inline void(*glBlendEquationSeparateEXT) (GLenum modeRGB, GLenum modeAlpha) = nullptr;
#define EXT_blend_equation_separate 1

	//blend func extended
	inline void(*glBindFragDataLocationIndexedEXT) (GLuint program, GLuint colorNumber, GLuint index, const GLchar * name) = nullptr;
	inline GLint(*glGetFragDataIndexEXT) (GLuint program, const GLchar* name) = nullptr;
	inline GLint(*glGetProgramResourceLocationIndexEXT) (GLuint program, GLenum programInterface, const GLchar* name) = nullptr;
#define EXT_blend_func_extended 1

	//blend func separate
	inline void(*glBlendFuncSeparateEXT) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) = nullptr;
#define EXT_blend_func_separate 1

	//blend logic op
#define EXT_blend_logic_op 1

	//blend minmax
	inline void(*glBlendEquationEXT) (GLenum mode) = nullptr;
#define EXT_blend_minmax 1

	//blend subtract
#define EXT_blend_subtract 1

	//buffer storage
	inline void(*glBufferStorageEXT) (GLenum target, GLsizeiptr size, const void* data, GLbitfield flags) = nullptr;
	inline void(*glNamedBufferStorageEXT) (GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags) = nullptr;
#define EXT_buffer_storage 1

	//clear texture
	inline void(*glClearTexImageEXT) (GLuint texture, GLint level, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glClearTexSubImageEXT) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data) = nullptr;
#define EXT_clear_texture 1

	//clip cull distance
#define EXT_clip_cull_distance 1

	//clip volume hint
#define EXT_clip_volume_hint 1

	//cmyka
#define EXT_cmyka 1

	//color buffer float
#define EXT_color_buffer_float 1

	//color buffer half float
#define EXT_color_buffer_half_float 1

	//color subtable
	inline void(*glColorSubTableEXT) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glCopyColorSubTableEXT) (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width) = nullptr;
#define EXT_color_subtable 1

	//compiled vertex array
	inline void(*glLockArraysEXT) (GLint first, GLsizei count) = nullptr;
	inline void(*glUnlockArraysEXT) (void) = nullptr;
#define EXT_compiled_vertex_array 1

	//compressed ETC1 RGB8 sub texture
#define EXT_compressed_ETC1_RGB8_sub_texture 1

	//conservative depth
#define EXT_conservative_depth 1

	//convolution
	inline void(*glConvolutionFilter1DEXT) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* image) = nullptr;
	inline void(*glConvolutionFilter2DEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* image) = nullptr;
	inline void(*glConvolutionParameterfEXT) (GLenum target, GLenum pname, GLfloat param) = nullptr;
	inline void(*glConvolutionParameterfvEXT) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glConvolutionParameteriEXT) (GLenum target, GLenum pname, GLint param) = nullptr;
	inline void(*glConvolutionParameterivEXT) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glCopyConvolutionFilter1DEXT) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = nullptr;
	inline void(*glCopyConvolutionFilter2DEXT) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glGetConvolutionFilterEXT) (GLenum target, GLenum format, GLenum type, void* image) = nullptr;
	inline void(*glGetConvolutionParameterfvEXT) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetConvolutionParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetSeparableFilterEXT) (GLenum target, GLenum format, GLenum type, void* row, void* column, void* span) = nullptr;
	inline void(*glSeparableFilter2DEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* row, const void* column) = nullptr;
#define EXT_convolution 1

	//coordinate frame
	inline void(*glBinormalPointerEXT) (GLenum type, GLsizei stride, void* pointer) = nullptr;
	inline void(*glTangentPointerEXT) (GLenum type, GLsizei stride, void* pointer) = nullptr;
#define EXT_coordinate_frame 1

	//copy image
	inline void(*glCopyImageSubDataEXT) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) = nullptr;
#define EXT_copy_image 1

	//copy texture
	inline void(*glCopyTexImage1DEXT) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) = nullptr;
	inline void(*glCopyTexImage2DEXT) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = nullptr;
	inline void(*glCopyTexSubImage1DEXT) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = nullptr;
	inline void(*glCopyTexSubImage2DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glCopyTexSubImage3DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
#define EXT_copy_texture 1

	//cull vertex
	inline void(*glCullParameterdvEXT) (GLenum pname, GLdouble * params) = nullptr;
	inline void(*glCullParameterfvEXT) (GLenum pname, GLfloat* params) = nullptr;
#define EXT_cull_vertex 1

	//debug label
	inline void(*glGetObjectLabelEXT) (GLenum type, GLuint object, GLsizei bufSize, GLsizei * length, GLchar * label) = nullptr;
	inline void(*glLabelObjectEXT) (GLenum type, GLuint object, GLsizei length, const GLchar* label) = nullptr;
#define EXT_debug_label 1

	//debug marker
	inline void(*glInsertEventMarkerEXT) (GLsizei length, const GLchar * marker) = nullptr;
	inline void(*glPopGroupMarkerEXT) (void) = nullptr;
	inline void(*glPushGroupMarkerEXT) (GLsizei length, const GLchar* marker) = nullptr;
#define EXT_debug_marker 1

	//depth bounds test
	inline void(*glDepthBoundsEXT) (GLclampd zmin, GLclampd zmax) = nullptr;
#define EXT_depth_bounds_test 1

	//direct state access
	inline void(*glBindMultiTextureEXT) (GLenum texunit, GLenum target, GLuint texture) = nullptr;
	inline GLenum(*glCheckNamedFramebufferStatusEXT) (GLuint framebuffer, GLenum target) = nullptr;
	inline void(*glClientAttribDefaultEXT) (GLbitfield mask) = nullptr;
	inline void(*glCompressedMultiTexImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedMultiTexImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedMultiTexImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedMultiTexSubImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedMultiTexSubImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedMultiTexSubImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTextureImage1DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTextureImage2DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTextureImage3DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTextureSubImage1DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTextureSubImage2DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTextureSubImage3DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCopyMultiTexImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) = nullptr;
	inline void(*glCopyMultiTexImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = nullptr;
	inline void(*glCopyMultiTexSubImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = nullptr;
	inline void(*glCopyMultiTexSubImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glCopyMultiTexSubImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glCopyTextureImage1DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) = nullptr;
	inline void(*glCopyTextureImage2DEXT) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = nullptr;
	inline void(*glCopyTextureSubImage1DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = nullptr;
	inline void(*glCopyTextureSubImage2DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glCopyTextureSubImage3DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glDisableClientStateIndexedEXT) (GLenum array, GLuint index) = nullptr;
	inline void(*glDisableClientStateiEXT) (GLenum array, GLuint index) = nullptr;
	inline void(*glDisableVertexArrayAttribEXT) (GLuint vaobj, GLuint index) = nullptr;
	inline void(*glDisableVertexArrayEXT) (GLuint vaobj, GLenum array) = nullptr;
	inline void(*glEnableClientStateIndexedEXT) (GLenum array, GLuint index) = nullptr;
	inline void(*glEnableClientStateiEXT) (GLenum array, GLuint index) = nullptr;
	inline void(*glEnableVertexArrayAttribEXT) (GLuint vaobj, GLuint index) = nullptr;
	inline void(*glEnableVertexArrayEXT) (GLuint vaobj, GLenum array) = nullptr;
	inline void(*glFlushMappedNamedBufferRangeEXT) (GLuint buffer, GLintptr offset, GLsizeiptr length) = nullptr;
	inline void(*glFramebufferDrawBufferEXT) (GLuint framebuffer, GLenum mode) = nullptr;
	inline void(*glFramebufferDrawBuffersEXT) (GLuint framebuffer, GLsizei n, const GLenum* bufs) = nullptr;
	inline void(*glFramebufferReadBufferEXT) (GLuint framebuffer, GLenum mode) = nullptr;
	inline void(*glGenerateMultiTexMipmapEXT) (GLenum texunit, GLenum target) = nullptr;
	inline void(*glGenerateTextureMipmapEXT) (GLuint texture, GLenum target) = nullptr;
	inline void(*glGetCompressedMultiTexImageEXT) (GLenum texunit, GLenum target, GLint level, void* img) = nullptr;
	inline void(*glGetCompressedTextureImageEXT) (GLuint texture, GLenum target, GLint level, void* img) = nullptr;
	inline void(*glGetDoubleIndexedvEXT) (GLenum target, GLuint index, GLdouble* params) = nullptr;
	inline void(*glGetDoublei_vEXT) (GLenum pname, GLuint index, GLdouble* params) = nullptr;
	inline void(*glGetFloatIndexedvEXT) (GLenum target, GLuint index, GLfloat* params) = nullptr;
	inline void(*glGetFloati_vEXT) (GLenum pname, GLuint index, GLfloat* params) = nullptr;
	inline void(*glGetFramebufferParameterivEXT) (GLuint framebuffer, GLenum pname, GLint* param) = nullptr;
	inline void(*glGetMultiTexEnvfvEXT) (GLenum texunit, GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetMultiTexEnvivEXT) (GLenum texunit, GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetMultiTexGendvEXT) (GLenum texunit, GLenum coord, GLenum pname, GLdouble* params) = nullptr;
	inline void(*glGetMultiTexGenfvEXT) (GLenum texunit, GLenum coord, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetMultiTexGenivEXT) (GLenum texunit, GLenum coord, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetMultiTexImageEXT) (GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void* pixels) = nullptr;
	inline void(*glGetMultiTexLevelParameterfvEXT) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetMultiTexLevelParameterivEXT) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetMultiTexParameterIivEXT) (GLenum texunit, GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetMultiTexParameterIuivEXT) (GLenum texunit, GLenum target, GLenum pname, GLuint* params) = nullptr;
	inline void(*glGetMultiTexParameterfvEXT) (GLenum texunit, GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetMultiTexParameterivEXT) (GLenum texunit, GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetNamedBufferParameterivEXT) (GLuint buffer, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetNamedBufferPointervEXT) (GLuint buffer, GLenum pname, void** params) = nullptr;
	inline void(*glGetNamedBufferSubDataEXT) (GLuint buffer, GLintptr offset, GLsizeiptr size, void* data) = nullptr;
	inline void(*glGetNamedFramebufferAttachmentParameterivEXT) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetNamedProgramLocalParameterIivEXT) (GLuint program, GLenum target, GLuint index, GLint* params) = nullptr;
	inline void(*glGetNamedProgramLocalParameterIuivEXT) (GLuint program, GLenum target, GLuint index, GLuint* params) = nullptr;
	inline void(*glGetNamedProgramLocalParameterdvEXT) (GLuint program, GLenum target, GLuint index, GLdouble* params) = nullptr;
	inline void(*glGetNamedProgramLocalParameterfvEXT) (GLuint program, GLenum target, GLuint index, GLfloat* params) = nullptr;
	inline void(*glGetNamedProgramStringEXT) (GLuint program, GLenum target, GLenum pname, void* string) = nullptr;
	inline void(*glGetNamedProgramivEXT) (GLuint program, GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetNamedRenderbufferParameterivEXT) (GLuint renderbuffer, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetPointerIndexedvEXT) (GLenum target, GLuint index, void** params) = nullptr;
	inline void(*glGetPointeri_vEXT) (GLenum pname, GLuint index, void** params) = nullptr;
	inline void(*glGetTextureImageEXT) (GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void* pixels) = nullptr;
	inline void(*glGetTextureLevelParameterfvEXT) (GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetTextureLevelParameterivEXT) (GLuint texture, GLenum target, GLint level, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetTextureParameterIivEXT) (GLuint texture, GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetTextureParameterIuivEXT) (GLuint texture, GLenum target, GLenum pname, GLuint* params) = nullptr;
	inline void(*glGetTextureParameterfvEXT) (GLuint texture, GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetTextureParameterivEXT) (GLuint texture, GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetVertexArrayIntegeri_vEXT) (GLuint vaobj, GLuint index, GLenum pname, GLint* param) = nullptr;
	inline void(*glGetVertexArrayIntegervEXT) (GLuint vaobj, GLenum pname, GLint* param) = nullptr;
	inline void(*glGetVertexArrayPointeri_vEXT) (GLuint vaobj, GLuint index, GLenum pname, void** param) = nullptr;
	inline void(*glGetVertexArrayPointervEXT) (GLuint vaobj, GLenum pname, void** param) = nullptr;
	inline void* (*glMapNamedBufferEXT) (GLuint buffer, GLenum access) = nullptr;
	inline void* (*glMapNamedBufferRangeEXT) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) = nullptr;
	inline void(*glMatrixFrustumEXT) (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f) = nullptr;
	inline void(*glMatrixLoadIdentityEXT) (GLenum matrixMode) = nullptr;
	inline void(*glMatrixLoadTransposedEXT) (GLenum matrixMode, const GLdouble* m) = nullptr;
	inline void(*glMatrixLoadTransposefEXT) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glMatrixLoaddEXT) (GLenum matrixMode, const GLdouble* m) = nullptr;
	inline void(*glMatrixLoadfEXT) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glMatrixMultTransposedEXT) (GLenum matrixMode, const GLdouble* m) = nullptr;
	inline void(*glMatrixMultTransposefEXT) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glMatrixMultdEXT) (GLenum matrixMode, const GLdouble* m) = nullptr;
	inline void(*glMatrixMultfEXT) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glMatrixOrthoEXT) (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f) = nullptr;
	inline void(*glMatrixPopEXT) (GLenum matrixMode) = nullptr;
	inline void(*glMatrixPushEXT) (GLenum matrixMode) = nullptr;
	inline void(*glMatrixRotatedEXT) (GLenum matrixMode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glMatrixRotatefEXT) (GLenum matrixMode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glMatrixScaledEXT) (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glMatrixScalefEXT) (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glMatrixTranslatedEXT) (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glMatrixTranslatefEXT) (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glMultiTexBufferEXT) (GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
	inline void(*glMultiTexCoordPointerEXT) (GLenum texunit, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
	inline void(*glMultiTexEnvfEXT) (GLenum texunit, GLenum target, GLenum pname, GLfloat param) = nullptr;
	inline void(*glMultiTexEnvfvEXT) (GLenum texunit, GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glMultiTexEnviEXT) (GLenum texunit, GLenum target, GLenum pname, GLint param) = nullptr;
	inline void(*glMultiTexEnvivEXT) (GLenum texunit, GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glMultiTexGendEXT) (GLenum texunit, GLenum coord, GLenum pname, GLdouble param) = nullptr;
	inline void(*glMultiTexGendvEXT) (GLenum texunit, GLenum coord, GLenum pname, const GLdouble* params) = nullptr;
	inline void(*glMultiTexGenfEXT) (GLenum texunit, GLenum coord, GLenum pname, GLfloat param) = nullptr;
	inline void(*glMultiTexGenfvEXT) (GLenum texunit, GLenum coord, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glMultiTexGeniEXT) (GLenum texunit, GLenum coord, GLenum pname, GLint param) = nullptr;
	inline void(*glMultiTexGenivEXT) (GLenum texunit, GLenum coord, GLenum pname, const GLint* params) = nullptr;
	inline void(*glMultiTexImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glMultiTexImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glMultiTexImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glMultiTexParameterIivEXT) (GLenum texunit, GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glMultiTexParameterIuivEXT) (GLenum texunit, GLenum target, GLenum pname, const GLuint* params) = nullptr;
	inline void(*glMultiTexParameterfEXT) (GLenum texunit, GLenum target, GLenum pname, GLfloat param) = nullptr;
	inline void(*glMultiTexParameterfvEXT) (GLenum texunit, GLenum target, GLenum pname, const GLfloat* param) = nullptr;
	inline void(*glMultiTexParameteriEXT) (GLenum texunit, GLenum target, GLenum pname, GLint param) = nullptr;
	inline void(*glMultiTexParameterivEXT) (GLenum texunit, GLenum target, GLenum pname, const GLint* param) = nullptr;
	inline void(*glMultiTexRenderbufferEXT) (GLenum texunit, GLenum target, GLuint renderbuffer) = nullptr;
	inline void(*glMultiTexSubImage1DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glMultiTexSubImage2DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glMultiTexSubImage3DEXT) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glNamedBufferDataEXT) (GLuint buffer, GLsizeiptr size, const void* data, GLenum usage) = nullptr;
	inline void(*glNamedBufferSubDataEXT) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) = nullptr;
	inline void(*glNamedCopyBufferSubDataEXT) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) = nullptr;
	inline void(*glNamedFramebufferRenderbufferEXT) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
	inline void(*glNamedFramebufferTexture1DEXT) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	inline void(*glNamedFramebufferTexture2DEXT) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	inline void(*glNamedFramebufferTexture3DEXT) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) = nullptr;
	inline void(*glNamedFramebufferTextureEXT) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) = nullptr;
	inline void(*glNamedFramebufferTextureFaceEXT) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face) = nullptr;
	inline void(*glNamedFramebufferTextureLayerEXT) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
	inline void(*glNamedProgramLocalParameter4dEXT) (GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glNamedProgramLocalParameter4dvEXT) (GLuint program, GLenum target, GLuint index, const GLdouble* params) = nullptr;
	inline void(*glNamedProgramLocalParameter4fEXT) (GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glNamedProgramLocalParameter4fvEXT) (GLuint program, GLenum target, GLuint index, const GLfloat* params) = nullptr;
	inline void(*glNamedProgramLocalParameterI4iEXT) (GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) = nullptr;
	inline void(*glNamedProgramLocalParameterI4ivEXT) (GLuint program, GLenum target, GLuint index, const GLint* params) = nullptr;
	inline void(*glNamedProgramLocalParameterI4uiEXT) (GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
	inline void(*glNamedProgramLocalParameterI4uivEXT) (GLuint program, GLenum target, GLuint index, const GLuint* params) = nullptr;
	inline void(*glNamedProgramLocalParameters4fvEXT) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat* params) = nullptr;
	inline void(*glNamedProgramLocalParametersI4ivEXT) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLint* params) = nullptr;
	inline void(*glNamedProgramLocalParametersI4uivEXT) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint* params) = nullptr;
	inline void(*glNamedProgramStringEXT) (GLuint program, GLenum target, GLenum format, GLsizei len, const void* string) = nullptr;
	inline void(*glNamedRenderbufferStorageEXT) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glNamedRenderbufferStorageMultisampleCoverageEXT) (GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glNamedRenderbufferStorageMultisampleEXT) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glProgramUniform1fEXT) (GLuint program, GLint location, GLfloat v0) = nullptr;
	inline void(*glProgramUniform1fvEXT) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glProgramUniform1iEXT) (GLuint program, GLint location, GLint v0) = nullptr;
	inline void(*glProgramUniform1ivEXT) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glProgramUniform1uiEXT) (GLuint program, GLint location, GLuint v0) = nullptr;
	inline void(*glProgramUniform1uivEXT) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glProgramUniform2fEXT) (GLuint program, GLint location, GLfloat v0, GLfloat v1) = nullptr;
	inline void(*glProgramUniform2fvEXT) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glProgramUniform2iEXT) (GLuint program, GLint location, GLint v0, GLint v1) = nullptr;
	inline void(*glProgramUniform2ivEXT) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glProgramUniform2uiEXT) (GLuint program, GLint location, GLuint v0, GLuint v1) = nullptr;
	inline void(*glProgramUniform2uivEXT) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glProgramUniform3fEXT) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) = nullptr;
	inline void(*glProgramUniform3fvEXT) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glProgramUniform3iEXT) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2) = nullptr;
	inline void(*glProgramUniform3ivEXT) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glProgramUniform3uiEXT) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) = nullptr;
	inline void(*glProgramUniform3uivEXT) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glProgramUniform4fEXT) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) = nullptr;
	inline void(*glProgramUniform4fvEXT) (GLuint program, GLint location, GLsizei count, const GLfloat* value) = nullptr;
	inline void(*glProgramUniform4iEXT) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) = nullptr;
	inline void(*glProgramUniform4ivEXT) (GLuint program, GLint location, GLsizei count, const GLint* value) = nullptr;
	inline void(*glProgramUniform4uiEXT) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) = nullptr;
	inline void(*glProgramUniform4uivEXT) (GLuint program, GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glProgramUniformMatrix2fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix2x3fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix2x4fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix3fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix3x2fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix3x4fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix4fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix4x2fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glProgramUniformMatrix4x3fvEXT) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glPushClientAttribDefaultEXT) (GLbitfield mask) = nullptr;
	inline void(*glTextureBufferEXT) (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
	inline void(*glTextureImage1DEXT) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTextureImage2DEXT) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTextureImage3DEXT) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTextureParameterIivEXT) (GLuint texture, GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glTextureParameterIuivEXT) (GLuint texture, GLenum target, GLenum pname, const GLuint* params) = nullptr;
	inline void(*glTextureParameterfEXT) (GLuint texture, GLenum target, GLenum pname, GLfloat param) = nullptr;
	inline void(*glTextureParameterfvEXT) (GLuint texture, GLenum target, GLenum pname, const GLfloat* param) = nullptr;
	inline void(*glTextureParameteriEXT) (GLuint texture, GLenum target, GLenum pname, GLint param) = nullptr;
	inline void(*glTextureParameterivEXT) (GLuint texture, GLenum target, GLenum pname, const GLint* param) = nullptr;
	inline void(*glTextureRenderbufferEXT) (GLuint texture, GLenum target, GLuint renderbuffer) = nullptr;
	inline void(*glTextureSubImage1DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTextureSubImage2DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTextureSubImage3DEXT) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline GLboolean(*glUnmapNamedBufferEXT) (GLuint buffer) = nullptr;
	inline void(*glVertexArrayColorOffsetEXT) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArrayEdgeFlagOffsetEXT) (GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArrayFogCoordOffsetEXT) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArrayIndexOffsetEXT) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArrayMultiTexCoordOffsetEXT) (GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArrayNormalOffsetEXT) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArraySecondaryColorOffsetEXT) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArrayTexCoordOffsetEXT) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArrayVertexAttribDivisorEXT) (GLuint vaobj, GLuint index, GLuint divisor) = nullptr;
	inline void(*glVertexArrayVertexAttribIOffsetEXT) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArrayVertexAttribOffsetEXT) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexArrayVertexOffsetEXT) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
#define EXT_direct_state_access 1

	//discard framebuffer
	inline void(*glDiscardFramebufferEXT) (GLenum target, GLsizei numAttachments, const GLenum * attachments) = nullptr;
#define EXT_discard_framebuffer 1

	//draw buffers
	inline void(*glDrawBuffersEXT) (GLsizei n, const GLenum * bufs) = nullptr;
#define EXT_draw_buffers 1

	//draw buffers2
	inline void(*glColorMaskIndexedEXT) (GLuint buf, GLboolean r, GLboolean g, GLboolean b, GLboolean a) = nullptr;
	inline void(*glDisableIndexedEXT) (GLenum target, GLuint index) = nullptr;
	inline void(*glEnableIndexedEXT) (GLenum target, GLuint index) = nullptr;
	inline void(*glGetBooleanIndexedvEXT) (GLenum value, GLuint index, GLboolean* data) = nullptr;
	inline void(*glGetIntegerIndexedvEXT) (GLenum value, GLuint index, GLint* data) = nullptr;
	inline GLboolean(*glIsEnabledIndexedEXT) (GLenum target, GLuint index) = nullptr;
#define EXT_draw_buffers2 1

	//draw buffers indexed
	inline void(*glBlendEquationSeparateiEXT) (GLuint buf, GLenum modeRGB, GLenum modeAlpha) = nullptr;
	inline void(*glBlendEquationiEXT) (GLuint buf, GLenum mode) = nullptr;
	inline void(*glBlendFuncSeparateiEXT) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = nullptr;
	inline void(*glBlendFunciEXT) (GLuint buf, GLenum src, GLenum dst) = nullptr;
	inline void(*glColorMaskiEXT) (GLuint buf, GLboolean r, GLboolean g, GLboolean b, GLboolean a) = nullptr;
	inline void(*glDisableiEXT) (GLenum target, GLuint index) = nullptr;
	inline void(*glEnableiEXT) (GLenum target, GLuint index) = nullptr;
	inline GLboolean(*glIsEnablediEXT) (GLenum target, GLuint index) = nullptr;
#define EXT_draw_buffers_indexed 1

	//draw elements base vertex
	inline void(*glDrawElementsBaseVertexEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex) = nullptr;
	inline void(*glDrawElementsInstancedBaseVertexEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex) = nullptr;
	inline void(*glDrawRangeElementsBaseVertexEXT) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex) = nullptr;
	inline void(*glMultiDrawElementsBaseVertexEXT) (GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei primcount, const GLint* basevertex) = nullptr;
#define EXT_draw_elements_base_vertex 1

	//draw instanced
	inline void(*glDrawArraysInstancedEXT) (GLenum mode, GLint start, GLsizei count, GLsizei primcount) = nullptr;
	inline void(*glDrawElementsInstancedEXT) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) = nullptr;
#define EXT_draw_instanced 1

	//draw range elements
	inline void(*glDrawRangeElementsEXT) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices) = nullptr;
#define EXT_draw_range_elements 1

	//external buffer
	inline void(*glBufferStorageExternalEXT) (GLenum target, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags) = nullptr;
	inline void(*glNamedBufferStorageExternalEXT) (GLuint buffer, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags) = nullptr;
#define EXT_external_buffer 1

	//float blend
#define EXT_float_blend 1

	//fog coord
	inline void(*glFogCoordPointerEXT) (GLenum type, GLsizei stride, const void* pointer) = nullptr;
	inline void(*glFogCoorddEXT) (GLdouble coord) = nullptr;
	inline void(*glFogCoorddvEXT) (const GLdouble* coord) = nullptr;
	inline void(*glFogCoordfEXT) (GLfloat coord) = nullptr;
	inline void(*glFogCoordfvEXT) (const GLfloat* coord) = nullptr;
#define EXT_fog_coord 1

	//frag depth
#define EXT_frag_depth 1

	//fragment lighting
	inline void(*glFragmentColorMaterialEXT) (GLenum face, GLenum mode) = nullptr;
	inline void(*glFragmentLightModelfEXT) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glFragmentLightModelfvEXT) (GLenum pname, GLfloat* params) = nullptr;
	inline void(*glFragmentLightModeliEXT) (GLenum pname, GLint param) = nullptr;
	inline void(*glFragmentLightModelivEXT) (GLenum pname, GLint* params) = nullptr;
	inline void(*glFragmentLightfEXT) (GLenum light, GLenum pname, GLfloat param) = nullptr;
	inline void(*glFragmentLightfvEXT) (GLenum light, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glFragmentLightiEXT) (GLenum light, GLenum pname, GLint param) = nullptr;
	inline void(*glFragmentLightivEXT) (GLenum light, GLenum pname, GLint* params) = nullptr;
	inline void(*glFragmentMaterialfEXT) (GLenum face, GLenum pname, const GLfloat param) = nullptr;
	inline void(*glFragmentMaterialfvEXT) (GLenum face, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glFragmentMaterialiEXT) (GLenum face, GLenum pname, const GLint param) = nullptr;
	inline void(*glFragmentMaterialivEXT) (GLenum face, GLenum pname, const GLint* params) = nullptr;
	inline void(*glGetFragmentLightfvEXT) (GLenum light, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetFragmentLightivEXT) (GLenum light, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetFragmentMaterialfvEXT) (GLenum face, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glGetFragmentMaterialivEXT) (GLenum face, GLenum pname, const GLint* params) = nullptr;
	inline void(*glLightEnviEXT) (GLenum pname, GLint param) = nullptr;
#define EXT_fragment_lighting 1

	//framebuffer blit
	inline void(*glBlitFramebufferEXT) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
#define EXT_framebuffer_blit 1

	//framebuffer multisample
	inline void(*glRenderbufferStorageMultisampleEXT) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
#define EXT_framebuffer_multisample 1

	//framebuffer multisample blit scaled
#define EXT_framebuffer_multisample_blit_scaled 1

	//framebuffer object
	inline void(*glBindFramebufferEXT) (GLenum target, GLuint framebuffer) = nullptr;
	inline void(*glBindRenderbufferEXT) (GLenum target, GLuint renderbuffer) = nullptr;
	inline GLenum(*glCheckFramebufferStatusEXT) (GLenum target) = nullptr;
	inline void(*glDeleteFramebuffersEXT) (GLsizei n, const GLuint* framebuffers) = nullptr;
	inline void(*glDeleteRenderbuffersEXT) (GLsizei n, const GLuint* renderbuffers) = nullptr;
	inline void(*glFramebufferRenderbufferEXT) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
	inline void(*glFramebufferTexture1DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	inline void(*glFramebufferTexture2DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	inline void(*glFramebufferTexture3DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) = nullptr;
	inline void(*glGenFramebuffersEXT) (GLsizei n, GLuint* framebuffers) = nullptr;
	inline void(*glGenRenderbuffersEXT) (GLsizei n, GLuint* renderbuffers) = nullptr;
	inline void(*glGenerateMipmapEXT) (GLenum target) = nullptr;
	inline void(*glGetFramebufferAttachmentParameterivEXT) (GLenum target, GLenum attachment, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetRenderbufferParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsFramebufferEXT) (GLuint framebuffer) = nullptr;
	inline GLboolean(*glIsRenderbufferEXT) (GLuint renderbuffer) = nullptr;
	inline void(*glRenderbufferStorageEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
#define EXT_framebuffer_object 1

	//framebuffer sRGB
#define EXT_framebuffer_sRGB 1

	//geometry point size
#define EXT_geometry_point_size 1

	//geometry shader
#define EXT_geometry_shader 1

	//geometry shader4
	inline void(*glFramebufferTextureEXT) (GLenum target, GLenum attachment, GLuint texture, GLint level) = nullptr;
	inline void(*glFramebufferTextureFaceEXT) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face) = nullptr;
	inline void(*glProgramParameteriEXT) (GLuint program, GLenum pname, GLint value) = nullptr;
#define EXT_geometry_shader4 1

	//gpu program parameters
	inline void(*glProgramEnvParameters4fvEXT) (GLenum target, GLuint index, GLsizei count, const GLfloat * params) = nullptr;
	inline void(*glProgramLocalParameters4fvEXT) (GLenum target, GLuint index, GLsizei count, const GLfloat* params) = nullptr;
#define EXT_gpu_program_parameters 1

	//gpu shader4
	inline void(*glBindFragDataLocationEXT) (GLuint program, GLuint color, const GLchar * name) = nullptr;
	inline GLint(*glGetFragDataLocationEXT) (GLuint program, const GLchar* name) = nullptr;
	inline void(*glGetUniformuivEXT) (GLuint program, GLint location, GLuint* params) = nullptr;
	inline void(*glGetVertexAttribIivEXT) (GLuint index, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetVertexAttribIuivEXT) (GLuint index, GLenum pname, GLuint* params) = nullptr;
	inline void(*glUniform1uiEXT) (GLint location, GLuint v0) = nullptr;
	inline void(*glUniform1uivEXT) (GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glUniform2uiEXT) (GLint location, GLuint v0, GLuint v1) = nullptr;
	inline void(*glUniform2uivEXT) (GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glUniform3uiEXT) (GLint location, GLuint v0, GLuint v1, GLuint v2) = nullptr;
	inline void(*glUniform3uivEXT) (GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glUniform4uiEXT) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) = nullptr;
	inline void(*glUniform4uivEXT) (GLint location, GLsizei count, const GLuint* value) = nullptr;
	inline void(*glVertexAttribI1iEXT) (GLuint index, GLint x) = nullptr;
	inline void(*glVertexAttribI1ivEXT) (GLuint index, const GLint* v) = nullptr;
	inline void(*glVertexAttribI1uiEXT) (GLuint index, GLuint x) = nullptr;
	inline void(*glVertexAttribI1uivEXT) (GLuint index, const GLuint* v) = nullptr;
	inline void(*glVertexAttribI2iEXT) (GLuint index, GLint x, GLint y) = nullptr;
	inline void(*glVertexAttribI2ivEXT) (GLuint index, const GLint* v) = nullptr;
	inline void(*glVertexAttribI2uiEXT) (GLuint index, GLuint x, GLuint y) = nullptr;
	inline void(*glVertexAttribI2uivEXT) (GLuint index, const GLuint* v) = nullptr;
	inline void(*glVertexAttribI3iEXT) (GLuint index, GLint x, GLint y, GLint z) = nullptr;
	inline void(*glVertexAttribI3ivEXT) (GLuint index, const GLint* v) = nullptr;
	inline void(*glVertexAttribI3uiEXT) (GLuint index, GLuint x, GLuint y, GLuint z) = nullptr;
	inline void(*glVertexAttribI3uivEXT) (GLuint index, const GLuint* v) = nullptr;
	inline void(*glVertexAttribI4bvEXT) (GLuint index, const GLbyte* v) = nullptr;
	inline void(*glVertexAttribI4iEXT) (GLuint index, GLint x, GLint y, GLint z, GLint w) = nullptr;
	inline void(*glVertexAttribI4ivEXT) (GLuint index, const GLint* v) = nullptr;
	inline void(*glVertexAttribI4svEXT) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttribI4ubvEXT) (GLuint index, const GLubyte* v) = nullptr;
	inline void(*glVertexAttribI4uiEXT) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
	inline void(*glVertexAttribI4uivEXT) (GLuint index, const GLuint* v) = nullptr;
	inline void(*glVertexAttribI4usvEXT) (GLuint index, const GLushort* v) = nullptr;
	inline void(*glVertexAttribIPointerEXT) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
#define EXT_gpu_shader4 1

	//gpu shader5
#define EXT_gpu_shader5 1

	//histogram
	inline void(*glGetHistogramEXT) (GLenum target, GLboolean reset, GLenum format, GLenum type, void* values) = nullptr;
	inline void(*glGetHistogramParameterfvEXT) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetHistogramParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetMinmaxEXT) (GLenum target, GLboolean reset, GLenum format, GLenum type, void* values) = nullptr;
	inline void(*glGetMinmaxParameterfvEXT) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetMinmaxParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glHistogramEXT) (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink) = nullptr;
	inline void(*glMinmaxEXT) (GLenum target, GLenum internalformat, GLboolean sink) = nullptr;
	inline void(*glResetHistogramEXT) (GLenum target) = nullptr;
	inline void(*glResetMinmaxEXT) (GLenum target) = nullptr;
#define EXT_histogram 1

	//index array formats
#define EXT_index_array_formats 1

	//index func
	inline void(*glIndexFuncEXT) (GLenum func, GLfloat ref) = nullptr;
#define EXT_index_func 1

	//index material
	inline void(*glIndexMaterialEXT) (GLenum face, GLenum mode) = nullptr;
#define EXT_index_material 1

	//index texture
#define EXT_index_texture 1

	//instanced arrays
	inline void(*glVertexAttribDivisorEXT) (GLuint index, GLuint divisor) = nullptr;
#define EXT_instanced_arrays 1

	//light texture
	inline void(*glApplyTextureEXT) (GLenum mode) = nullptr;
	inline void(*glTextureLightEXT) (GLenum pname) = nullptr;
	inline void(*glTextureMaterialEXT) (GLenum face, GLenum mode) = nullptr;
#define EXT_light_texture 1

	//map buffer range
	inline void(*glFlushMappedBufferRangeEXT) (GLenum target, GLintptr offset, GLsizeiptr length) = nullptr;
	inline void* (*glMapBufferRangeEXT) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) = nullptr;
#define EXT_map_buffer_range 1

	//memory object
	inline void(*glBufferStorageMemEXT) (GLenum target, GLsizeiptr size, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glCreateMemoryObjectsEXT) (GLsizei n, GLuint* memoryObjects) = nullptr;
	inline void(*glDeleteMemoryObjectsEXT) (GLsizei n, const GLuint* memoryObjects) = nullptr;
	inline void(*glGetMemoryObjectParameterivEXT) (GLuint memoryObject, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetUnsignedBytei_vEXT) (GLenum target, GLuint index, GLubyte* data) = nullptr;
	inline void(*glGetUnsignedBytevEXT) (GLenum pname, GLubyte* data) = nullptr;
	inline GLboolean(*glIsMemoryObjectEXT) (GLuint memoryObject) = nullptr;
	inline void(*glMemoryObjectParameterivEXT) (GLuint memoryObject, GLenum pname, const GLint* params) = nullptr;
	inline void(*glNamedBufferStorageMemEXT) (GLuint buffer, GLsizeiptr size, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTexStorageMem1DEXT) (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTexStorageMem2DEXT) (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTexStorageMem2DMultisampleEXT) (GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTexStorageMem3DEXT) (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTexStorageMem3DMultisampleEXT) (GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTextureStorageMem1DEXT) (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTextureStorageMem2DEXT) (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTextureStorageMem2DMultisampleEXT) (GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTextureStorageMem3DEXT) (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset) = nullptr;
	inline void(*glTextureStorageMem3DMultisampleEXT) (GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset) = nullptr;
#define EXT_memory_object 1

	//memory object fd
	inline void(*glImportMemoryFdEXT) (GLuint memory, GLuint64 size, GLenum handleType, GLint fd) = nullptr;
#define EXT_memory_object_fd 1

	//memory object win32
	inline void(*glImportMemoryWin32HandleEXT) (GLuint memory, GLuint64 size, GLenum handleType, void* handle) = nullptr;
	inline void(*glImportMemoryWin32NameEXT) (GLuint memory, GLuint64 size, GLenum handleType, const void* name) = nullptr;
#define EXT_memory_object_win32 1

	//misc attribute
#define EXT_misc_attribute 1

	//multi draw arrays
	inline void(*glMultiDrawArraysEXT) (GLenum mode, const GLint * first, const GLsizei * count, GLsizei primcount) = nullptr;
	inline void(*glMultiDrawElementsEXT) (GLenum mode, GLsizei* count, GLenum type, const void* const* indices, GLsizei primcount) = nullptr;
#define EXT_multi_draw_arrays 1

	//multi draw indirect
	inline void(*glMultiDrawArraysIndirectEXT) (GLenum mode, const void* indirect, GLsizei drawcount, GLsizei stride) = nullptr;
	inline void(*glMultiDrawElementsIndirectEXT) (GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride) = nullptr;
#define EXT_multi_draw_indirect 1

	//multiple textures
#define EXT_multiple_textures 1

	//multisample
	inline void(*glSampleMaskEXT) (GLclampf value, GLboolean invert) = nullptr;
	inline void(*glSamplePatternEXT) (GLenum pattern) = nullptr;
#define EXT_multisample 1

	//multisample compatibility
#define EXT_multisample_compatibility 1

	//multisampled render to texture
	inline void(*glFramebufferTexture2DMultisampleEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples) = nullptr;
#define EXT_multisampled_render_to_texture 1

	//multisampled render to texture2
#define EXT_multisampled_render_to_texture2 1

	//multiview draw buffers
	inline void(*glDrawBuffersIndexedEXT) (GLint n, const GLenum * location, const GLint * indices) = nullptr;
	inline void(*glGetIntegeri_vEXT) (GLenum target, GLuint index, GLint* data) = nullptr;
	inline void(*glReadBufferIndexedEXT) (GLenum src, GLint index) = nullptr;
#define EXT_multiview_draw_buffers 1

	//packed depth stencil
#define EXT_packed_depth_stencil 1

	//packed float
#define EXT_packed_float 1

	//packed pixels
#define EXT_packed_pixels 1

	//paletted texture
	inline void(*glColorTableEXT) (GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const void* data) = nullptr;
	inline void(*glGetColorTableEXT) (GLenum target, GLenum format, GLenum type, void* data) = nullptr;
	inline void(*glGetColorTableParameterfvEXT) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetColorTableParameterivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
#define EXT_paletted_texture 1

	//pixel buffer object
#define EXT_pixel_buffer_object 1

	//pixel transform
	inline void(*glGetPixelTransformParameterfvEXT) (GLenum target, GLenum pname, const GLfloat * params) = nullptr;
	inline void(*glGetPixelTransformParameterivEXT) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glPixelTransformParameterfEXT) (GLenum target, GLenum pname, const GLfloat param) = nullptr;
	inline void(*glPixelTransformParameterfvEXT) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glPixelTransformParameteriEXT) (GLenum target, GLenum pname, const GLint param) = nullptr;
	inline void(*glPixelTransformParameterivEXT) (GLenum target, GLenum pname, const GLint* params) = nullptr;
#define EXT_pixel_transform 1

	//pixel transform color table
#define EXT_pixel_transform_color_table 1

	//point parameters
	inline void(*glPointParameterfEXT) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glPointParameterfvEXT) (GLenum pname, const GLfloat* params) = nullptr;
#define EXT_point_parameters 1

	//polygon offset
	inline void(*glPolygonOffsetEXT) (GLfloat factor, GLfloat bias) = nullptr;
#define EXT_polygon_offset 1

	//polygon offset clamp
	inline void(*glPolygonOffsetClampEXT) (GLfloat factor, GLfloat units, GLfloat clamp) = nullptr;
#define EXT_polygon_offset_clamp 1

	//post depth coverage
#define EXT_post_depth_coverage 1

	//provoking vertex
	inline void(*glProvokingVertexEXT) (GLenum mode) = nullptr;
#define EXT_provoking_vertex 1

	//pvrtc sRGB
#define EXT_pvrtc_sRGB 1

	//raster multisample
	inline void(*glCoverageModulationNV) (GLenum components) = nullptr;
	inline void(*glCoverageModulationTableNV) (GLsizei n, const GLfloat* v) = nullptr;
	inline void(*glGetCoverageModulationTableNV) (GLsizei bufsize, GLfloat* v) = nullptr;
	inline void(*glRasterSamplesEXT) (GLuint samples, GLboolean fixedsamplelocations) = nullptr;
#define EXT_raster_multisample 1

	//read format bgra
#define EXT_read_format_bgra 1

	//render snorm
#define EXT_render_snorm 1

	//rescale normal
#define EXT_rescale_normal 1

	//sRGB
#define EXT_sRGB 1

	//sRGB write control
#define EXT_sRGB_write_control 1

	//scene marker
	inline void(*glBeginSceneEXT) (void) = nullptr;
	inline void(*glEndSceneEXT) (void) = nullptr;
#define EXT_scene_marker 1

	//secondary color
	inline void(*glSecondaryColor3bEXT) (GLbyte red, GLbyte green, GLbyte blue) = nullptr;
	inline void(*glSecondaryColor3bvEXT) (const GLbyte* v) = nullptr;
	inline void(*glSecondaryColor3dEXT) (GLdouble red, GLdouble green, GLdouble blue) = nullptr;
	inline void(*glSecondaryColor3dvEXT) (const GLdouble* v) = nullptr;
	inline void(*glSecondaryColor3fEXT) (GLfloat red, GLfloat green, GLfloat blue) = nullptr;
	inline void(*glSecondaryColor3fvEXT) (const GLfloat* v) = nullptr;
	inline void(*glSecondaryColor3iEXT) (GLint red, GLint green, GLint blue) = nullptr;
	inline void(*glSecondaryColor3ivEXT) (const GLint* v) = nullptr;
	inline void(*glSecondaryColor3sEXT) (GLshort red, GLshort green, GLshort blue) = nullptr;
	inline void(*glSecondaryColor3svEXT) (const GLshort* v) = nullptr;
	inline void(*glSecondaryColor3ubEXT) (GLubyte red, GLubyte green, GLubyte blue) = nullptr;
	inline void(*glSecondaryColor3ubvEXT) (const GLubyte* v) = nullptr;
	inline void(*glSecondaryColor3uiEXT) (GLuint red, GLuint green, GLuint blue) = nullptr;
	inline void(*glSecondaryColor3uivEXT) (const GLuint* v) = nullptr;
	inline void(*glSecondaryColor3usEXT) (GLushort red, GLushort green, GLushort blue) = nullptr;
	inline void(*glSecondaryColor3usvEXT) (const GLushort* v) = nullptr;
	inline void(*glSecondaryColorPointerEXT) (GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
#define EXT_secondary_color 1

	//semaphore
	inline void(*glDeleteSemaphoresEXT) (GLsizei n, const GLuint * semaphores) = nullptr;
	inline void(*glGenSemaphoresEXT) (GLsizei n, GLuint* semaphores) = nullptr;
	inline void(*glGetSemaphoreParameterui64vEXT) (GLuint semaphore, GLenum pname, GLuint64* params) = nullptr;
	inline GLboolean(*glIsSemaphoreEXT) (GLuint semaphore) = nullptr;
	inline void(*glSemaphoreParameterui64vEXT) (GLuint semaphore, GLenum pname, const GLuint64* params) = nullptr;
	inline void(*glSignalSemaphoreEXT) (GLuint semaphore, GLuint numBufferBarriers, const GLuint* buffers, GLuint numTextureBarriers, const GLuint* textures, const GLenum* dstLayouts) = nullptr;
	inline void(*glWaitSemaphoreEXT) (GLuint semaphore, GLuint numBufferBarriers, const GLuint* buffers, GLuint numTextureBarriers, const GLuint* textures, const GLenum* srcLayouts) = nullptr;
#define EXT_semaphore 1

	//semaphore fd
	inline void(*glImportSemaphoreFdEXT) (GLuint semaphore, GLenum handleType, GLint fd) = nullptr;
#define EXT_semaphore_fd 1

	//semaphore win32
	inline void(*glImportSemaphoreWin32HandleEXT) (GLuint semaphore, GLenum handleType, void* handle) = nullptr;
	inline void(*glImportSemaphoreWin32NameEXT) (GLuint semaphore, GLenum handleType, const void* name) = nullptr;
#define EXT_semaphore_win32 1

	//separate shader objects
	inline void(*glActiveProgramEXT) (GLuint program) = nullptr;
	inline GLuint(*glCreateShaderProgramEXT) (GLenum type, const GLchar* string) = nullptr;
	inline void(*glUseShaderProgramEXT) (GLenum type, GLuint program) = nullptr;
#define EXT_separate_shader_objects 1

	//separate specular color
#define EXT_separate_specular_color 1

	//shader framebuffer fetch
#define EXT_shader_framebuffer_fetch 1

	//shader group vote
#define EXT_shader_group_vote 1

	//shader image load formatted
#define EXT_shader_image_load_formatted 1

	//shader image load store
	inline void(*glBindImageTextureEXT) (GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format) = nullptr;
	inline void(*glMemoryBarrierEXT) (GLbitfield barriers) = nullptr;
#define EXT_shader_image_load_store 1

	//shader implicit conversions
#define EXT_shader_implicit_conversions 1

	//shader integer mix
#define EXT_shader_integer_mix 1

	//shader io blocks
#define EXT_shader_io_blocks 1

	//shader non constant global initializers
#define EXT_shader_non_constant_global_initializers 1

	//shader pixel local storage
#define EXT_shader_pixel_local_storage 1

	//shader pixel local storage2
	inline void(*glClearPixelLocalStorageuiEXT) (GLsizei offset, GLsizei n, const GLuint * values) = nullptr;
	inline void(*glFramebufferPixelLocalStorageSizeEXT) (GLuint target, GLsizei size) = nullptr;
	inline GLsizei(*glGetFramebufferPixelLocalStorageSizeEXT) (GLuint target) = nullptr;
#define EXT_shader_pixel_local_storage2 1

	//shader texture lod
#define EXT_shader_texture_lod 1

	//shadow funcs
#define EXT_shadow_funcs 1

	//shadow samplers
#define EXT_shadow_samplers 1

	//shared texture palette
#define EXT_shared_texture_palette 1

	//sparse texture
	inline void(*glTexPageCommitmentEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit) = nullptr;
	inline void(*glTexturePageCommitmentEXT) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit) = nullptr;
#define EXT_sparse_texture 1

	//sparse texture2
#define EXT_sparse_texture2 1

	//stencil clear tag
#define EXT_stencil_clear_tag 1

	//stencil two side
	inline void(*glActiveStencilFaceEXT) (GLenum face) = nullptr;
#define EXT_stencil_two_side 1

	//stencil wrap
#define EXT_stencil_wrap 1

	//subtexture
	inline void(*glTexSubImage1DEXT) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTexSubImage2DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTexSubImage3DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
#define EXT_subtexture 1

	//texture
#define EXT_texture 1

	//texture3D
	inline void(*glTexImage3DEXT) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
#define EXT_texture3D 1

	//texture array
	inline void(*glFramebufferTextureLayerEXT) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
#define EXT_texture_array 1

	//texture buffer object
	inline void(*glTexBufferEXT) (GLenum target, GLenum internalformat, GLuint buffer) = nullptr;
#define EXT_texture_buffer_object 1

	//texture compression astc decode mode
#define EXT_texture_compression_astc_decode_mode 1

	//texture compression astc decode mode rgb9e5
#define EXT_texture_compression_astc_decode_mode_rgb9e5 1

	//texture compression bptc
#define EXT_texture_compression_bptc 1

	//texture compression dxt1
#define EXT_texture_compression_dxt1 1

	//texture compression latc
#define EXT_texture_compression_latc 1

	//texture compression rgtc
#define EXT_texture_compression_rgtc 1

	//texture compression s3tc
#define EXT_texture_compression_s3tc 1

	//texture cube map
#define EXT_texture_cube_map 1

	//texture cube map array
#define EXT_texture_cube_map_array 1

	//texture_edge_clamp
#define EXT_texture_edge_clamp 1

	//texture_env
#define EXT_texture_env 1

	//texture_env_add
#define EXT_texture_env_add 1

	//texture_env_combine
#define EXT_texture_env_combine 1

	//texture_env_dot3
#define EXT_texture_env_dot3 1

	//texture_filter_anisotropic
#define EXT_texture_filter_anisotropic 1

	//texture_filter_minmax
#define EXT_texture_filter_minmax 1

	//texture_format_BGRA8888
#define EXT_texture_format_BGRA8888 1

	//texture_integer
	inline void(*glClearColorIiEXT) (GLint red, GLint green, GLint blue, GLint alpha) = nullptr;
	inline void(*glClearColorIuiEXT) (GLuint red, GLuint green, GLuint blue, GLuint alpha) = nullptr;
	inline void(*glGetTexParameterIivEXT) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetTexParameterIuivEXT) (GLenum target, GLenum pname, GLuint* params) = nullptr;
	inline void(*glTexParameterIivEXT) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glTexParameterIuivEXT) (GLenum target, GLenum pname, const GLuint* params) = nullptr;
#define EXT_texture_integer 1

	//texture_lod_bias
#define EXT_texture_lod_bias 1

	//texture_mirror_clamp
#define EXT_texture_mirror_clamp 1

	//texture_norm16
#define EXT_texture_norm16 1

	//texture_object
	inline GLboolean(*glAreTexturesResidentEXT) (GLsizei n, const GLuint * textures, GLboolean * residences) = nullptr;
	inline void(*glBindTextureEXT) (GLenum target, GLuint texture) = nullptr;
	inline void(*glDeleteTexturesEXT) (GLsizei n, const GLuint* textures) = nullptr;
	inline void(*glGenTexturesEXT) (GLsizei n, GLuint* textures) = nullptr;
	inline GLboolean(*glIsTextureEXT) (GLuint texture) = nullptr;
	inline void(*glPrioritizeTexturesEXT) (GLsizei n, const GLuint* textures, const GLclampf* priorities) = nullptr;
#define EXT_texture_object 1

	//texture_perturb_normal
	inline void(*glTextureNormalEXT) (GLenum mode) = nullptr;
#define EXT_texture_perturb_normal 1

	//texture_rectangle
#define EXT_texture_rectangle 1

	//texture_rg
#define EXT_texture_rg 1

	//texture_sRGB
#define EXT_texture_sRGB 1

	//texture_sRGB_R8
#define EXT_texture_sRGB_R8 1

	//texture_sRGB_RG8
#define EXT_texture_sRGB_RG8 1

	//texture_sRGB_decode
#define EXT_texture_sRGB_decode 1

	//texture_shared_exponent
#define EXT_texture_shared_exponent 1

	//texture_snorm
#define EXT_texture_snorm 1

	//texture_storage
	inline void(*glTexStorage1DEXT) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) = nullptr;
	inline void(*glTexStorage2DEXT) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glTexStorage3DEXT) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
	inline void(*glTextureStorage1DEXT) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) = nullptr;
	inline void(*glTextureStorage2DEXT) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	inline void(*glTextureStorage3DEXT) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
#define EXT_texture_storage 1

	//texture_swizzle
#define EXT_texture_swizzle 1

	//texture_type_2_10_10_10_REV
#define EXT_texture_type_2_10_10_10_REV 1

	//texture_view
	inline void(*glTextureViewEXT) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) = nullptr;
#define EXT_texture_view 1

	//timer_query
	inline void(*glGetQueryObjecti64vEXT) (GLuint id, GLenum pname, GLint64EXT * params) = nullptr;
	inline void(*glGetQueryObjectui64vEXT) (GLuint id, GLenum pname, GLuint64EXT* params) = nullptr;
#define EXT_timer_query 1

	//transform_feedback
	inline void(*glBeginTransformFeedbackEXT) (GLenum primitiveMode) = nullptr;
	inline void(*glBindBufferBaseEXT) (GLenum target, GLuint index, GLuint buffer) = nullptr;
	inline void(*glBindBufferOffsetEXT) (GLenum target, GLuint index, GLuint buffer, GLintptr offset) = nullptr;
	inline void(*glBindBufferRangeEXT) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	inline void(*glEndTransformFeedbackEXT) (void) = nullptr;
	inline void(*glGetTransformFeedbackVaryingEXT) (GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) = nullptr;
	inline void(*glTransformFeedbackVaryingsEXT) (GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode) = nullptr;
#define EXT_transform_feedback 1

	//unpack_subimage
#define EXT_unpack_subimage 1

	//vertex_array
	inline void(*glArrayElementEXT) (GLint i) = nullptr;
	inline void(*glColorPointerEXT) (GLint size, GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
	inline void(*glDrawArraysEXT) (GLenum mode, GLint first, GLsizei count) = nullptr;
	inline void(*glEdgeFlagPointerEXT) (GLsizei stride, GLsizei count, const GLboolean* pointer) = nullptr;
	inline void(*glIndexPointerEXT) (GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
	inline void(*glNormalPointerEXT) (GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
	inline void(*glTexCoordPointerEXT) (GLint size, GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
	inline void(*glVertexPointerEXT) (GLint size, GLenum type, GLsizei stride, GLsizei count, const void* pointer) = nullptr;
#define EXT_vertex_array 1

	//vertex_array_bgra
#define EXT_vertex_array_bgra 1

	//vertex_array_setXXX
	inline void(*glBindArraySetEXT) (const void* arrayset) = nullptr;
	inline const void* (*glCreateArraySetExt) (void) = nullptr;
	inline void(*glDeleteArraySetsEXT) (GLsizei n, const void* arrayset[]) = nullptr;
#define EXT_vertex_array_setXXX 1

	//vertex_attrib_64bit
	inline void(*glGetVertexAttribLdvEXT) (GLuint index, GLenum pname, GLdouble * params) = nullptr;
	inline void(*glVertexArrayVertexAttribLOffsetEXT) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset) = nullptr;
	inline void(*glVertexAttribL1dEXT) (GLuint index, GLdouble x) = nullptr;
	inline void(*glVertexAttribL1dvEXT) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribL2dEXT) (GLuint index, GLdouble x, GLdouble y) = nullptr;
	inline void(*glVertexAttribL2dvEXT) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribL3dEXT) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glVertexAttribL3dvEXT) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribL4dEXT) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glVertexAttribL4dvEXT) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribLPointerEXT) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
#define EXT_vertex_attrib_64bit 1

	//vertex_shader
	inline void(*glBeginVertexShaderEXT) (void) = nullptr;
	inline GLuint(*glBindLightParameterEXT) (GLenum light, GLenum value) = nullptr;
	inline GLuint(*glBindMaterialParameterEXT) (GLenum face, GLenum value) = nullptr;
	inline GLuint(*glBindParameterEXT) (GLenum value) = nullptr;
	inline GLuint(*glBindTexGenParameterEXT) (GLenum unit, GLenum coord, GLenum value) = nullptr;
	inline GLuint(*glBindTextureUnitParameterEXT) (GLenum unit, GLenum value) = nullptr;
	inline void(*glBindVertexShaderEXT) (GLuint id) = nullptr;
	inline void(*glDeleteVertexShaderEXT) (GLuint id) = nullptr;
	inline void(*glDisableVariantClientStateEXT) (GLuint id) = nullptr;
	inline void(*glEnableVariantClientStateEXT) (GLuint id) = nullptr;
	inline void(*glEndVertexShaderEXT) (void) = nullptr;
	inline void(*glExtractComponentEXT) (GLuint res, GLuint src, GLuint num) = nullptr;
	inline GLuint(*glGenSymbolsEXT) (GLenum dataType, GLenum storageType, GLenum range, GLuint components) = nullptr;
	inline GLuint(*glGenVertexShadersEXT) (GLuint range) = nullptr;
	inline void(*glGetInvariantBooleanvEXT) (GLuint id, GLenum value, GLboolean* data) = nullptr;
	inline void(*glGetInvariantFloatvEXT) (GLuint id, GLenum value, GLfloat* data) = nullptr;
	inline void(*glGetInvariantIntegervEXT) (GLuint id, GLenum value, GLint* data) = nullptr;
	inline void(*glGetLocalConstantBooleanvEXT) (GLuint id, GLenum value, GLboolean* data) = nullptr;
	inline void(*glGetLocalConstantFloatvEXT) (GLuint id, GLenum value, GLfloat* data) = nullptr;
	inline void(*glGetLocalConstantIntegervEXT) (GLuint id, GLenum value, GLint* data) = nullptr;
	inline void(*glGetVariantBooleanvEXT) (GLuint id, GLenum value, GLboolean* data) = nullptr;
	inline void(*glGetVariantFloatvEXT) (GLuint id, GLenum value, GLfloat* data) = nullptr;
	inline void(*glGetVariantIntegervEXT) (GLuint id, GLenum value, GLint* data) = nullptr;
	inline void(*glGetVariantPointervEXT) (GLuint id, GLenum value, void** data) = nullptr;
	inline void(*glInsertComponentEXT) (GLuint res, GLuint src, GLuint num) = nullptr;
	inline GLboolean(*glIsVariantEnabledEXT) (GLuint id, GLenum cap) = nullptr;
	inline void(*glSetInvariantEXT) (GLuint id, GLenum type, void* addr) = nullptr;
	inline void(*glSetLocalConstantEXT) (GLuint id, GLenum type, void* addr) = nullptr;
	inline void(*glShaderOp1EXT) (GLenum op, GLuint res, GLuint arg1) = nullptr;
	inline void(*glShaderOp2EXT) (GLenum op, GLuint res, GLuint arg1, GLuint arg2) = nullptr;
	inline void(*glShaderOp3EXT) (GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3) = nullptr;
	inline void(*glSwizzleEXT) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW) = nullptr;
	inline void(*glVariantPointerEXT) (GLuint id, GLenum type, GLuint stride, void* addr) = nullptr;
	inline void(*glVariantbvEXT) (GLuint id, GLbyte* addr) = nullptr;
	inline void(*glVariantdvEXT) (GLuint id, GLdouble* addr) = nullptr;
	inline void(*glVariantfvEXT) (GLuint id, GLfloat* addr) = nullptr;
	inline void(*glVariantivEXT) (GLuint id, GLint* addr) = nullptr;
	inline void(*glVariantsvEXT) (GLuint id, GLshort* addr) = nullptr;
	inline void(*glVariantubvEXT) (GLuint id, GLubyte* addr) = nullptr;
	inline void(*glVariantuivEXT) (GLuint id, GLuint* addr) = nullptr;
	inline void(*glVariantusvEXT) (GLuint id, GLushort* addr) = nullptr;
	inline void(*glWriteMaskEXT) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW) = nullptr;
#define EXT_vertex_shader 1

	//vertex_weighting
	inline void(*glVertexWeightPointerEXT) (GLint size, GLenum type, GLsizei stride, void* pointer) = nullptr;
	inline void(*glVertexWeightfEXT) (GLfloat weight) = nullptr;
	inline void(*glVertexWeightfvEXT) (GLfloat* weight) = nullptr;
#define EXT_vertex_weighting 1

	//win32_keyed_mutex
	inline GLboolean(*glAcquireKeyedMutexWin32EXT) (GLuint memory, GLuint64 key, GLuint timeout) = nullptr;
	inline GLboolean(*glReleaseKeyedMutexWin32EXT) (GLuint memory, GLuint64 key) = nullptr;
#define EXT_win32_keyed_mutex 1

	//window_rectangles
	inline void(*glWindowRectanglesEXT) (GLenum mode, GLsizei count, const GLint box[]) = nullptr;
#define EXT_window_rectangles 1

	//x11_sync_object
	inline GLsync(*glImportSyncEXT) (GLenum external_sync_type, GLintptr external_sync, GLbitfield flags) = nullptr;
#define EXT_x11_sync_object 1

	//*< load EXT Extensions
	inline void LoadEXTExtensions()
	{

		//base instance
		FetchProcAddress(glDrawArraysInstancedBaseInstanceEXT, "glDrawArraysInstancedBaseInstanceEXT");
		FetchProcAddress(glDrawElementsInstancedBaseInstanceEXT, "glDrawElementsInstancedBaseInstanceEXT");
		FetchProcAddress(glDrawElementsInstancedBaseVertexBaseInstanceEXT, "glDrawElementsInstancedBaseVertexBaseInstanceEXT");

		//bindable uniform
		FetchProcAddress(glGetUniformBufferSizeEXT, "glGetUniformBufferSizeEXT");
		FetchProcAddress(glGetUniformOffsetEXT, "glGetUniformOffsetEXT");
		FetchProcAddress(glUniformBufferEXT, "glUniformBufferEXT");

		//blend color
		FetchProcAddress(glBlendColorEXT, "glBlendColorEXT");

		//blend equation separate
		FetchProcAddress(glBlendEquationSeparateEXT, "glBlendEquationSeparateEXT");

		//blend func extended
		FetchProcAddress(glBindFragDataLocationIndexedEXT, "glBindFragDataLocationIndexedEXT");
		FetchProcAddress(glGetFragDataIndexEXT, "glGetFragDataIndexEXT");
		FetchProcAddress(glGetProgramResourceLocationIndexEXT, "glGetProgramResourceLocationIndexEXT");

		//blend func separate
		FetchProcAddress(glBlendFuncSeparateEXT, "glBlendFuncSeparateEXT");

		//blend minmax
		FetchProcAddress(glBlendEquationEXT, "glBlendEquationEXT");

		//buffer storage
		FetchProcAddress(glBufferStorageEXT, "glBufferStorageEXT");
		FetchProcAddress(glNamedBufferStorageEXT, "glNamedBufferStorageEXT");

		//clear texture
		FetchProcAddress(glClearTexImageEXT, "glClearTexImageEXT");
		FetchProcAddress(glClearTexSubImageEXT, "glClearTexSubImageEXT");

		//color subtable
		FetchProcAddress(glColorSubTableEXT, "glColorSubTableEXT");
		FetchProcAddress(glCopyColorSubTableEXT, "glCopyColorSubTableEXT");

		//compiled vertex array
		FetchProcAddress(glLockArraysEXT, "glLockArraysEXT");
		FetchProcAddress(glUnlockArraysEXT, "glUnlockArraysEXT");

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

		//coordinate frame
		FetchProcAddress(glBinormalPointerEXT, "glBinormalPointerEXT");
		FetchProcAddress(glTangentPointerEXT, "glTangentPointerEXT");

		//copy image
		FetchProcAddress(glCopyImageSubDataEXT, "glCopyImageSubDataEXT");

		//copy texture
		FetchProcAddress(glCopyTexImage1DEXT, "glCopyTexImage1DEXT");
		FetchProcAddress(glCopyTexImage2DEXT, "glCopyTexImage2DEXT");
		FetchProcAddress(glCopyTexSubImage1DEXT, "glCopyTexSubImage1DEXT");
		FetchProcAddress(glCopyTexSubImage2DEXT, "glCopyTexSubImage2DEXT");
		FetchProcAddress(glCopyTexSubImage3DEXT, "glCopyTexSubImage3DEXT");

		//cull vertex
		FetchProcAddress(glCullParameterdvEXT, "glCullParameterdvEXT");
		FetchProcAddress(glCullParameterfvEXT, "glCullParameterfvEXT");

		//debug label
		FetchProcAddress(glGetObjectLabelEXT, "glGetObjectLabelEXT");
		FetchProcAddress(glLabelObjectEXT, "glLabelObjectEXT");

		//debug marker
		FetchProcAddress(glInsertEventMarkerEXT, "glInsertEventMarkerEXT");
		FetchProcAddress(glPopGroupMarkerEXT, "glPopGroupMarkerEXT");
		FetchProcAddress(glPushGroupMarkerEXT, "glPushGroupMarkerEXT");

		//depth bounds test
		FetchProcAddress(glDepthBoundsEXT, "glDepthBoundsEXT");

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

		//discard framebuffer
		FetchProcAddress(glDiscardFramebufferEXT, "glDiscardFramebufferEXT");

		//draw buffers
		FetchProcAddress(glDrawBuffersEXT, "glDrawBuffersEXT");

		//draw buffers2
		FetchProcAddress(glColorMaskIndexedEXT, "glColorMaskIndexedEXT");
		FetchProcAddress(glDisableIndexedEXT, "glDisableIndexedEXT");
		FetchProcAddress(glEnableIndexedEXT, "glEnableIndexedEXT");
		FetchProcAddress(glGetBooleanIndexedvEXT, "glGetBooleanIndexedvEXT");
		FetchProcAddress(glGetIntegerIndexedvEXT, "glGetIntegerIndexedvEXT");
		FetchProcAddress(glIsEnabledIndexedEXT, "glIsEnabledIndexedEXT");

		//draw buffers indexed
		FetchProcAddress(glBlendEquationSeparateiEXT, "glBlendEquationSeparateiEXT");
		FetchProcAddress(glBlendEquationiEXT, "glBlendEquationiEXT");
		FetchProcAddress(glBlendFuncSeparateiEXT, "glBlendFuncSeparateiEXT");
		FetchProcAddress(glBlendFunciEXT, "glBlendFunciEXT");
		FetchProcAddress(glColorMaskiEXT, "glColorMaskiEXT");
		FetchProcAddress(glDisableiEXT, "glDisableiEXT");
		FetchProcAddress(glEnableiEXT, "glEnableiEXT");
		FetchProcAddress(glIsEnablediEXT, "glIsEnablediEXT");

		//draw elements base vertex
		FetchProcAddress(glDrawElementsBaseVertexEXT, "glDrawElementsBaseVertexEXT");
		FetchProcAddress(glDrawElementsInstancedBaseVertexEXT, "glDrawElementsInstancedBaseVertexEXT");
		FetchProcAddress(glDrawRangeElementsBaseVertexEXT, "glDrawRangeElementsBaseVertexEXT");
		FetchProcAddress(glMultiDrawElementsBaseVertexEXT, "glMultiDrawElementsBaseVertexEXT");

		//draw instanced
		FetchProcAddress(glDrawArraysInstancedEXT, "glDrawArraysInstancedEXT");
		FetchProcAddress(glDrawElementsInstancedEXT, "glDrawElementsInstancedEXT");

		//draw range elements
		FetchProcAddress(glDrawRangeElementsEXT, "glDrawRangeElementsEXT");

		//external buffer
		FetchProcAddress(glBufferStorageExternalEXT, "glBufferStorageExternalEXT");
		FetchProcAddress(glNamedBufferStorageExternalEXT, "glNamedBufferStorageExternalEXT");

		//fog coord
		FetchProcAddress(glFogCoordPointerEXT, "glFogCoordPointerEXT");
		FetchProcAddress(glFogCoorddEXT, "glFogCoorddEXT");
		FetchProcAddress(glFogCoorddvEXT, "glFogCoorddvEXT");
		FetchProcAddress(glFogCoordfEXT, "glFogCoordfEXT");
		FetchProcAddress(glFogCoordfvEXT, "glFogCoordfvEXT");

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

		//framebuffer blit
		FetchProcAddress(glBlitFramebufferEXT, "glBlitFramebufferEXT");

		//framebuffer multisample
		FetchProcAddress(glRenderbufferStorageMultisampleEXT, "glRenderbufferStorageMultisampleEXT");

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

		//geometry shader4
		FetchProcAddress(glFramebufferTextureEXT, "glFramebufferTextureEXT");
		FetchProcAddress(glFramebufferTextureFaceEXT, "glFramebufferTextureFaceEXT");
		FetchProcAddress(glProgramParameteriEXT, "glProgramParameteriEXT");

		//gpu program parameters
		FetchProcAddress(glProgramEnvParameters4fvEXT, "glProgramEnvParameters4fvEXT");
		FetchProcAddress(glProgramLocalParameters4fvEXT, "glProgramLocalParameters4fvEXT");

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

		//index func
		FetchProcAddress(glIndexFuncEXT, "glIndexFuncEXT");

		//index material
		FetchProcAddress(glIndexMaterialEXT, "glIndexMaterialEXT");

		//instanced arrays
		FetchProcAddress(glVertexAttribDivisorEXT, "glVertexAttribDivisorEXT");

		//light texture
		FetchProcAddress(glApplyTextureEXT, "glApplyTextureEXT");
		FetchProcAddress(glTextureLightEXT, "glTextureLightEXT");
		FetchProcAddress(glTextureMaterialEXT, "glTextureMaterialEXT");

		//map buffer range
		FetchProcAddress(glFlushMappedBufferRangeEXT, "glFlushMappedBufferRangeEXT");
		FetchProcAddress(glMapBufferRangeEXT, "glMapBufferRangeEXT");

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

		//memory object fd
		FetchProcAddress(glImportMemoryFdEXT, "glImportMemoryFdEXT");

		//memory object win32
		FetchProcAddress(glImportMemoryWin32HandleEXT, "glImportMemoryWin32HandleEXT");
		FetchProcAddress(glImportMemoryWin32NameEXT, "glImportMemoryWin32NameEXT");

		//multi draw arrays
		FetchProcAddress(glMultiDrawArraysEXT, "glMultiDrawArraysEXT");
		FetchProcAddress(glMultiDrawElementsEXT, "glMultiDrawElementsEXT");

		//multi draw indirect
		FetchProcAddress(glMultiDrawArraysIndirectEXT, "glMultiDrawArraysIndirectEXT");
		FetchProcAddress(glMultiDrawElementsIndirectEXT, "glMultiDrawElementsIndirectEXT");

		//multisample
		FetchProcAddress(glSampleMaskEXT, "glSampleMaskEXT");
		FetchProcAddress(glSamplePatternEXT, "glSamplePatternEXT");

		//multisampled render to texture
		FetchProcAddress(glFramebufferTexture2DMultisampleEXT, "glFramebufferTexture2DMultisampleEXT");

		//multiview draw buffers
		FetchProcAddress(glDrawBuffersIndexedEXT, "glDrawBuffersIndexedEXT");
		FetchProcAddress(glGetIntegeri_vEXT, "glGetIntegeri_vEXT");
		FetchProcAddress(glReadBufferIndexedEXT, "glReadBufferIndexedEXT");

		//paletted texture
		FetchProcAddress(glColorTableEXT, "glColorTableEXT");
		FetchProcAddress(glGetColorTableEXT, "glGetColorTableEXT");
		FetchProcAddress(glGetColorTableParameterfvEXT, "glGetColorTableParameterfvEXT");
		FetchProcAddress(glGetColorTableParameterivEXT, "glGetColorTableParameterivEXT");

		//pixel transform
		FetchProcAddress(glGetPixelTransformParameterfvEXT, "glGetPixelTransformParameterfvEXT");
		FetchProcAddress(glGetPixelTransformParameterivEXT, "glGetPixelTransformParameterivEXT");
		FetchProcAddress(glPixelTransformParameterfEXT, "glPixelTransformParameterfEXT");
		FetchProcAddress(glPixelTransformParameterfvEXT, "glPixelTransformParameterfvEXT");
		FetchProcAddress(glPixelTransformParameteriEXT, "glPixelTransformParameteriEXT");
		FetchProcAddress(glPixelTransformParameterivEXT, "glPixelTransformParameterivEXT");

		//point parameters
		FetchProcAddress(glPointParameterfEXT, "glPointParameterfEXT");
		FetchProcAddress(glPointParameterfvEXT, "glPointParameterfvEXT");

		//polygon offset
		FetchProcAddress(glPolygonOffsetEXT, "glPolygonOffsetEXT");

		//polygon offset clamp
		FetchProcAddress(glPolygonOffsetClampEXT, "glPolygonOffsetClampEXT");

		//provoking vertex
		FetchProcAddress(glProvokingVertexEXT, "glProvokingVertexEXT");

		//raster multisample
		FetchProcAddress(glCoverageModulationNV, "glCoverageModulationNV");
		FetchProcAddress(glCoverageModulationTableNV, "glCoverageModulationTableNV");
		FetchProcAddress(glGetCoverageModulationTableNV, "glGetCoverageModulationTableNV");
		FetchProcAddress(glRasterSamplesEXT, "glRasterSamplesEXT");

		//scene marker
		FetchProcAddress(glBeginSceneEXT, "glBeginSceneEXT");
		FetchProcAddress(glEndSceneEXT, "glEndSceneEXT");

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

		//semaphore
		FetchProcAddress(glDeleteSemaphoresEXT, "glDeleteSemaphoresEXT");
		FetchProcAddress(glGenSemaphoresEXT, "glGenSemaphoresEXT");
		FetchProcAddress(glGetSemaphoreParameterui64vEXT, "glGetSemaphoreParameterui64vEXT");
		FetchProcAddress(glIsSemaphoreEXT, "glIsSemaphoreEXT");
		FetchProcAddress(glSemaphoreParameterui64vEXT, "glSemaphoreParameterui64vEXT");
		FetchProcAddress(glSignalSemaphoreEXT, "glSignalSemaphoreEXT");
		FetchProcAddress(glWaitSemaphoreEXT, "glWaitSemaphoreEXT");

		//semaphore fd
		FetchProcAddress(glImportSemaphoreFdEXT, "glImportSemaphoreFdEXT");

		//semaphore win32
		FetchProcAddress(glImportSemaphoreWin32HandleEXT, "glImportSemaphoreWin32HandleEXT");
		FetchProcAddress(glImportSemaphoreWin32NameEXT, "glImportSemaphoreWin32NameEXT");

		//separate shader objects
		FetchProcAddress(glActiveProgramEXT, "glActiveProgramEXT");
		FetchProcAddress(glCreateShaderProgramEXT, "glCreateShaderProgramEXT");
		FetchProcAddress(glUseShaderProgramEXT, "glUseShaderProgramEXT");

		//shader image load store
		FetchProcAddress(glBindImageTextureEXT, "glBindImageTextureEXT");
		FetchProcAddress(glMemoryBarrierEXT, "glMemoryBarrierEXT");

		//shader pixel local storage2
		FetchProcAddress(glClearPixelLocalStorageuiEXT, "glClearPixelLocalStorageuiEXT");
		FetchProcAddress(glFramebufferPixelLocalStorageSizeEXT, "glFramebufferPixelLocalStorageSizeEXT");
		FetchProcAddress(glGetFramebufferPixelLocalStorageSizeEXT, "glGetFramebufferPixelLocalStorageSizeEXT");

		//sparse texture
		FetchProcAddress(glTexPageCommitmentEXT, "glTexPageCommitmentEXT");
		FetchProcAddress(glTexturePageCommitmentEXT, "glTexturePageCommitmentEXT");

		//stencil two side
		FetchProcAddress(glActiveStencilFaceEXT, "glActiveStencilFaceEXT");

		//subtexture
		FetchProcAddress(glTexSubImage1DEXT, "glTexSubImage1DEXT");
		FetchProcAddress(glTexSubImage2DEXT, "glTexSubImage2DEXT");
		FetchProcAddress(glTexSubImage3DEXT, "glTexSubImage3DEXT");

		//texture3D
		FetchProcAddress(glTexImage3DEXT, "glTexImage3DEXT");

		//texture array
		FetchProcAddress(glFramebufferTextureLayerEXT, "glFramebufferTextureLayerEXT");

		//texture buffer object
		FetchProcAddress(glTexBufferEXT, "glTexBufferEXT");

		//texture_integer
		FetchProcAddress(glClearColorIiEXT, "glClearColorIiEXT");
		FetchProcAddress(glClearColorIuiEXT, "glClearColorIuiEXT");
		FetchProcAddress(glGetTexParameterIivEXT, "glGetTexParameterIivEXT");
		FetchProcAddress(glGetTexParameterIuivEXT, "glGetTexParameterIuivEXT");
		FetchProcAddress(glTexParameterIivEXT, "glTexParameterIivEXT");
		FetchProcAddress(glTexParameterIuivEXT, "glTexParameterIuivEXT");

		//texture_object
		FetchProcAddress(glAreTexturesResidentEXT, "glAreTexturesResidentEXT");
		FetchProcAddress(glBindTextureEXT, "glBindTextureEXT");
		FetchProcAddress(glDeleteTexturesEXT, "glDeleteTexturesEXT");
		FetchProcAddress(glGenTexturesEXT, "glGenTexturesEXT");
		FetchProcAddress(glIsTextureEXT, "glIsTextureEXT");
		FetchProcAddress(glPrioritizeTexturesEXT, "glPrioritizeTexturesEXT");

		//texture_perturb_normal
		FetchProcAddress(glTextureNormalEXT, "glTextureNormalEXT");

		//texture_storage
		FetchProcAddress(glTexStorage1DEXT, "glTexStorage1DEXT");
		FetchProcAddress(glTexStorage2DEXT, "glTexStorage2DEXT");
		FetchProcAddress(glTexStorage3DEXT, "glTexStorage3DEXT");
		FetchProcAddress(glTextureStorage1DEXT, "glTextureStorage1DEXT");
		FetchProcAddress(glTextureStorage2DEXT, "glTextureStorage2DEXT");
		FetchProcAddress(glTextureStorage3DEXT, "glTextureStorage3DEXT");

		//texture_view
		FetchProcAddress(glTextureViewEXT, "glTextureViewEXT");

		//timer_query
		FetchProcAddress(glGetQueryObjecti64vEXT, "glGetQueryObjecti64vEXT");
		FetchProcAddress(glGetQueryObjectui64vEXT, "glGetQueryObjectui64vEXT");

		//transform_feedback
		FetchProcAddress(glBeginTransformFeedbackEXT, "glBeginTransformFeedbackEXT");
		FetchProcAddress(glBindBufferBaseEXT, "glBindBufferBaseEXT");
		FetchProcAddress(glBindBufferOffsetEXT, "glBindBufferOffsetEXT");
		FetchProcAddress(glBindBufferRangeEXT, "glBindBufferRangeEXT");
		FetchProcAddress(glEndTransformFeedbackEXT, "glEndTransformFeedbackEXT");
		FetchProcAddress(glGetTransformFeedbackVaryingEXT, "glGetTransformFeedbackVaryingEXT");
		FetchProcAddress(glTransformFeedbackVaryingsEXT, "glTransformFeedbackVaryingsEXT");

		//vertex_array
		FetchProcAddress(glArrayElementEXT, "glArrayElementEXT");
		FetchProcAddress(glColorPointerEXT, "glColorPointerEXT");
		FetchProcAddress(glDrawArraysEXT, "glDrawArraysEXT");
		FetchProcAddress(glEdgeFlagPointerEXT, "glEdgeFlagPointerEXT");
		FetchProcAddress(glIndexPointerEXT, "glIndexPointerEXT");
		FetchProcAddress(glNormalPointerEXT, "glNormalPointerEXT");
		FetchProcAddress(glTexCoordPointerEXT, "glTexCoordPointerEXT");
		FetchProcAddress(glVertexPointerEXT, "glVertexPointerEXT");

		//vertex_array_setXXX
		FetchProcAddress(glBindArraySetEXT, "glBindArraySetEXT");
		FetchProcAddress(glCreateArraySetExt, "glCreateArraySetExt");
		FetchProcAddress(glDeleteArraySetsEXT, "glDeleteArraySetsEXT");

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

		//vertex_weighting
		FetchProcAddress(glVertexWeightPointerEXT, "glVertexWeightPointerEXT");
		FetchProcAddress(glVertexWeightfEXT, "glVertexWeightfEXT");
		FetchProcAddress(glVertexWeightfvEXT, "glVertexWeightfvEXT");

		//win32_keyed_mutex
		FetchProcAddress(glAcquireKeyedMutexWin32EXT, "glAcquireKeyedMutexWin32EXT");
		FetchProcAddress(glReleaseKeyedMutexWin32EXT, "glReleaseKeyedMutexWin32EXT");

		//window_rectangles
		FetchProcAddress(glWindowRectanglesEXT, "glWindowRectanglesEXT");

		//x11_sync_object
		FetchProcAddress(glImportSyncEXT, "glImportSyncEXT");
	}

#pragma endregion EXT Extensions

	//OpenGL Gremedy Extensions
#pragma region Gremedy

	//frame terminator
	inline void(*glFrameTerminatorGREMEDY) (void) = nullptr;
#define GREMEDY_frame_terminator 1

	//string marker
	inline void(*glStringMarkerGREMEDY) (GLsizei len, const void* string) = nullptr;
#define GREMEDY_string_marker 1

	//*< load Gremedy Extensions
	inline void LoadGremedyExtensions()
	{
		//frame terminator
		FetchProcAddress(glFrameTerminatorGREMEDY, "glFrameTerminatorGREMEDY");

		//string marker
		FetchProcAddress(glStringMarkerGREMEDY, "glStringMarkerGREMEDY");
	}

#pragma endregion Gremedy Extensions

	//OpenGL HP Extensions
#pragma region HP

	//convolution border modes
#define convolution_border_modes 1

	//image transform
	inline void(*glGetImageTransformParameterfvHP) (GLenum target, GLenum pname, const GLfloat * params) = nullptr;
	inline void(*glGetImageTransformParameterivHP) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glImageTransformParameterfHP) (GLenum target, GLenum pname, const GLfloat param) = nullptr;
	inline void(*glImageTransformParameterfvHP) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glImageTransformParameteriHP) (GLenum target, GLenum pname, const GLint param) = nullptr;
	inline void(*glImageTransformParameterivHP) (GLenum target, GLenum pname, const GLint* params) = nullptr;
#define image_transform 1

	//occlusion test
#define occlusion_test 1

	//texture lighting
#define texture_lighting 1

	//*< load HP Extensions
	inline void LoadHPExtensions()
	{
		//image transform
		FetchProcAddress(glGetImageTransformParameterfvHP, "glGetImageTransformParameterfvHP");
		FetchProcAddress(glGetImageTransformParameterivHP, "glGetImageTransformParameterivHP");
		FetchProcAddress(glImageTransformParameterfHP, "glImageTransformParameterfHP");
		FetchProcAddress(glImageTransformParameterfvHP, "glImageTransformParameterfvHP");
		FetchProcAddress(glImageTransformParameteriHP, "glImageTransformParameteriHP");
		FetchProcAddress(glImageTransformParameterivHP, "glImageTransformParameterivHP");
	}

#pragma endregion HP Extensions

	//OpenGL IBM Extensions
#pragma region IBM

#define GL_CULL_VERTEX_IBM                            0x103050

#define GL_RASTER_POSITION_UNCLIPPED_IBM              0x103010

#define GL_ALL_STATIC_DATA_IBM                        0x103060
#define GL_STATIC_VERTEX_ARRAY_IBM                    0x103061

#define GL_MIRRORED_REPEAT_IBM                        0x8370

#define GL_VERTEX_ARRAY_LIST_IBM                      0x103070
#define GL_NORMAL_ARRAY_LIST_IBM                      0x103071
#define GL_COLOR_ARRAY_LIST_IBM                       0x103072
#define GL_INDEX_ARRAY_LIST_IBM                       0x103073
#define GL_TEXTURE_COORD_ARRAY_LIST_IBM               0x103074
#define GL_EDGE_FLAG_ARRAY_LIST_IBM                   0x103075
#define GL_FOG_COORDINATE_ARRAY_LIST_IBM              0x103076
#define GL_SECONDARY_COLOR_ARRAY_LIST_IBM             0x103077

#define GL_VERTEX_ARRAY_LIST_STRIDE_IBM               0x103080
#define GL_NORMAL_ARRAY_LIST_STRIDE_IBM               0x103081
#define GL_COLOR_ARRAY_LIST_STRIDE_IBM                0x103082
#define GL_INDEX_ARRAY_LIST_STRIDE_IBM                0x103083
#define GL_TEXTURE_COORD_ARRAY_LIST_STRIDE_IBM        0x103084
#define GL_EDGE_FLAG_ARRAY_LIST_STRIDE_IBM            0x103085
#define GL_FOG_COORDINATE_ARRAY_LIST_STRIDE_IBM       0x103086
#define GL_SECONDARY_COLOR_ARRAY_LIST_STRIDE_IBM      0x103087


	//cull vertex
#define IBM_cull_vertex 1

	//multimode draw arrays
	inline void(*glMultiModeDrawArraysIBM) (const GLenum * mode, const GLint * first, const GLsizei * count, GLsizei primcount, GLint modestride) = nullptr;
	inline void(*glMultiModeDrawElementsIBM) (const GLenum* mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei primcount, GLint modestride) = nullptr;

#define IBM_multimode_draw_arrays 1

	//rasterpos clip
#define IBM_rasterpos_clip 1

	//static data
#define IBM_static_data 1

	//texture mirrored_ repeat
#define IBM_texture_mirrored_repeat 1

	//vertex array lists
	inline void(*glColorPointerListIBM) (GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	inline void(*glEdgeFlagPointerListIBM) (GLint stride, const GLboolean** pointer, GLint ptrstride) = nullptr;
	inline void(*glFogCoordPointerListIBM) (GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	inline void(*glIndexPointerListIBM) (GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	inline void(*glNormalPointerListIBM) (GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	inline void(*glSecondaryColorPointerListIBM) (GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	inline void(*glTexCoordPointerListIBM) (GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;
	inline void(*glVertexPointerListIBM) (GLint size, GLenum type, GLint stride, const void** pointer, GLint ptrstride) = nullptr;

#define IBM_vertex_array_lists 1

	//*< load IBM Extensions
	inline void LoadIBMExtensions()
	{
		//multimode draw arrays
		FetchProcAddress(glMultiModeDrawArraysIBM, "glMultiModeDrawArraysIBM");
		FetchProcAddress(glMultiModeDrawElementsIBM, "glMultiModeDrawElementsIBM");

		//vertex array lists
		FetchProcAddress(glColorPointerListIBM, "glColorPointerListIBM");
		FetchProcAddress(glEdgeFlagPointerListIBM, "glEdgeFlagPointerListIBM");
		FetchProcAddress(glFogCoordPointerListIBM, "glFogCoordPointerListIBM");
		FetchProcAddress(glIndexPointerListIBM, "glIndexPointerListIBM");
		FetchProcAddress(glNormalPointerListIBM, "glNormalPointerListIBM");
		FetchProcAddress(glSecondaryColorPointerListIBM, "glSecondaryColorPointerListIBM");
		FetchProcAddress(glTexCoordPointerListIBM, "glTexCoordPointerListIBM");
		FetchProcAddress(glVertexPointerListIBM, "glVertexPointerListIBM");
	}

#pragma endregion IBM Extensions

	//OpenGL INGR Extensions
#pragma region INGR

#define GL_RED_MIN_CLAMP_INGR                         0x8560
#define GL_GREEN_MIN_CLAMP_INGR                       0x8561
#define GL_BLUE_MIN_CLAMP_INGR                        0x8562
#define GL_ALPHA_MIN_CLAMP_INGR                       0x8563
#define GL_RED_MAX_CLAMP_INGR                         0x8564
#define GL_GREEN_MAX_CLAMP_INGR                       0x8565
#define GL_BLUE_MAX_CLAMP_INGR                        0x8566
#define GL_ALPHA_MAX_CLAMP_INGR                       0x8567

#define GL_INTERLACE_READ_INGR                        0x8568

	//color clamp
#define INGR_color_clamp 1

	//interlace read
#define INGR_interlace_read 1

	//*< load INGR Extensions
	inline void LoadINGRExtensions()
	{

	}

#pragma endregion INGR Extensions

	//OpenGL Intel Extensions
#pragma region Intel

// Conservative Rasterization
#define GL_CONSERVATIVE_RASTERIZATION_INTEL           0x83FE

// Map Texture Layout
#define GL_LAYOUT_DEFAULT_INTEL                       0x0000
#define GL_LAYOUT_LINEAR_INTEL                        0x0001
#define GL_LAYOUT_LINEAR_CPU_CACHED_INTEL             0x0002
#define GL_TEXTURE_MEMORY_LAYOUT_INTEL                0x83FF

// Parallel Arrays
#define GL_PARALLEL_ARRAYS_INTEL                      0x83F4
#define GL_VERTEX_ARRAY_PARALLEL_POINTERS_INTEL       0x83F5
#define GL_NORMAL_ARRAY_PARALLEL_POINTERS_INTEL       0x83F6
#define GL_COLOR_ARRAY_PARALLEL_POINTERS_INTEL        0x83F7
#define GL_TEXTURE_COORD_ARRAY_PARALLEL_POINTERS_INTEL 0x83F8

// Performance Query
#define GL_PERFQUERY_SINGLE_CONTEXT_INTEL             0x0000
#define GL_PERFQUERY_GLOBAL_CONTEXT_INTEL             0x0001
#define GL_PERFQUERY_DONOT_FLUSH_INTEL                0x83F9
#define GL_PERFQUERY_FLUSH_INTEL                      0x83FA
#define GL_PERFQUERY_WAIT_INTEL                       0x83FB
#define GL_PERFQUERY_COUNTER_EVENT_INTEL              0x94F0
#define GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL      0x94F1
#define GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL       0x94F2
#define GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL         0x94F3
#define GL_PERFQUERY_COUNTER_RAW_INTEL                0x94F4
#define GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL          0x94F5
#define GL_PERFQUERY_COUNTER_DATA_UINT32_INTEL        0x94F8
#define GL_PERFQUERY_COUNTER_DATA_UINT64_INTEL        0x94F9
#define GL_PERFQUERY_COUNTER_DATA_FLOAT_INTEL         0x94FA
#define GL_PERFQUERY_COUNTER_DATA_DOUBLE_INTEL        0x94FB
#define GL_PERFQUERY_COUNTER_DATA_BOOL32_INTEL        0x94FC
#define GL_PERFQUERY_QUERY_NAME_LENGTH_MAX_INTEL      0x94FD
#define GL_PERFQUERY_COUNTER_NAME_LENGTH_MAX_INTEL    0x94FE
#define GL_PERFQUERY_COUNTER_DESC_LENGTH_MAX_INTEL    0x94FF
#define GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL      0x9500


	//conservative rasterization
#define INTEL_conservative_rasterization 1

	//fragment shader ordering
#define INTEL_fragment_shader_ordering 1

	//framebuffer CMAA
#define INTEL_framebuffer_CMAA 1

	//map texture
	inline void* (*glMapTexture2DINTEL) (GLuint texture, GLint level, GLbitfield access, GLint * stride, GLenum * layout) = nullptr;
	inline void(*glSyncTextureINTEL) (GLuint texture) = nullptr;
	inline void(*glUnmapTexture2DINTEL) (GLuint texture, GLint level) = nullptr;
#define INTEL_map_texture 1

	//parallel arrays
	inline void(*glColorPointervINTEL) (GLint size, GLenum type, const void** pointer) = nullptr;
	inline void(*glNormalPointervINTEL) (GLenum type, const void** pointer) = nullptr;
	inline void(*glTexCoordPointervINTEL) (GLint size, GLenum type, const void** pointer) = nullptr;
	inline void(*glVertexPointervINTEL) (GLint size, GLenum type, const void** pointer) = nullptr;
#define INTEL_parallel_arrays 1

	//performance query
	inline void(*glBeginPerfQueryINTEL) (GLuint queryHandle) = nullptr;
	inline void(*glCreatePerfQueryINTEL) (GLuint queryId, GLuint* queryHandle) = nullptr;
	inline void(*glDeletePerfQueryINTEL) (GLuint queryHandle) = nullptr;
	inline void(*glEndPerfQueryINTEL) (GLuint queryHandle) = nullptr;
	inline void(*glGetFirstPerfQueryIdINTEL) (GLuint* queryId) = nullptr;
	inline void(*glGetNextPerfQueryIdINTEL) (GLuint queryId, GLuint* nextQueryId) = nullptr;
	inline void(*glGetPerfCounterInfoINTEL) (GLuint queryId, GLuint counterId, GLuint counterNameLength, GLchar* counterName, GLuint counterDescLength, GLchar* counterDesc, GLuint* counterOffset, GLuint* counterDataSize, GLuint* counterTypeEnum, GLuint* counterDataTypeEnum, GLuint64* rawCounterMaxValue) = nullptr;
	inline void(*glGetPerfQueryDataINTEL) (GLuint queryHandle, GLuint flags, GLsizei dataSize, void* data, GLuint* bytesWritten) = nullptr;
	inline void(*glGetPerfQueryIdByNameINTEL) (GLchar* queryName, GLuint* queryId) = nullptr;
	inline void(*glGetPerfQueryInfoINTEL) (GLuint queryId, GLuint queryNameLength, GLchar* queryName, GLuint* dataSize, GLuint* noCounters, GLuint* noInstances, GLuint* capsMask) = nullptr;
#define INTEL_performance_query 1

	//texture scissor
	inline void(*glTexScissorFuncINTEL) (GLenum target, GLenum lfunc, GLenum hfunc) = nullptr;
	inline void(*glTexScissorINTEL) (GLenum target, GLclampf tlow, GLclampf thigh) = nullptr;
#define INTEL_texture_scissor 1

	//*< load Intel Extensions
	inline void LoadIntelExtensions()
	{
		//map texture
		FetchProcAddress(glMapTexture2DINTEL, "glMapTexture2DINTEL");
		FetchProcAddress(glSyncTextureINTEL, "glSyncTextureINTEL");
		FetchProcAddress(glUnmapTexture2DINTEL, "glUnmapTexture2DINTEL");

		//parallel arrays
		FetchProcAddress(glColorPointervINTEL, "glColorPointervINTEL");
		FetchProcAddress(glNormalPointervINTEL, "glNormalPointervINTEL");
		FetchProcAddress(glTexCoordPointervINTEL, "glTexCoordPointervINTEL");
		FetchProcAddress(glVertexPointervINTEL, "glVertexPointervINTEL");

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

		//texture scissor
		FetchProcAddress(glTexScissorFuncINTEL, "glTexScissorFuncINTEL");
		FetchProcAddress(glTexScissorINTEL, "glTexScissorINTEL");
	}

#pragma endregion Intel Extensions

	//OpenGL KHR Extensions
#pragma region KHR

// Blend Equation Advanced
#define GL_BLEND_ADVANCED_COHERENT_KHR                0x9285
#define GL_MULTIPLY_KHR                               0x9294
#define GL_SCREEN_KHR                                 0x9295
#define GL_OVERLAY_KHR                                0x9296
#define GL_DARKEN_KHR                                 0x9297
#define GL_LIGHTEN_KHR                                0x9298
#define GL_COLORDODGE_KHR                             0x9299
#define GL_COLORBURN_KHR                              0x929A
#define GL_HARDLIGHT_KHR                              0x929B
#define GL_SOFTLIGHT_KHR                              0x929C
#define GL_DIFFERENCE_KHR                             0x929E
#define GL_EXCLUSION_KHR                              0x92A0
#define GL_HSL_HUE_KHR                                0x92AD
#define GL_HSL_SATURATION_KHR                         0x92AE
#define GL_HSL_COLOR_KHR                              0x92AF
#define GL_HSL_LUMINOSITY_KHR                         0x92B0

// Debug
#define GL_CONTEXT_FLAG_DEBUG_BIT                     0x00000002
#define GL_STACK_OVERFLOW                             0x0503
#define GL_STACK_UNDERFLOW                            0x0504
#define GL_DEBUG_OUTPUT_SYNCHRONOUS                   0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH           0x8243
#define GL_DEBUG_CALLBACK_FUNCTION                    0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM                  0x8245
#define GL_DEBUG_SOURCE_API                           0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM                 0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER               0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY                   0x8249
#define GL_DEBUG_SOURCE_APPLICATION                   0x824A
#define GL_DEBUG_SOURCE_OTHER                         0x824B
#define GL_DEBUG_TYPE_ERROR                           0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR             0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR              0x824E
#define GL_DEBUG_TYPE_PORTABILITY                     0x824F
#define GL_DEBUG_TYPE_PERFORMANCE                     0x8250
#define GL_DEBUG_TYPE_OTHER                           0x8251
#define GL_DEBUG_TYPE_MARKER                          0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP                      0x8269
#define GL_DEBUG_TYPE_POP_GROUP                       0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION                0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH                0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH                    0x826D
#define GL_BUFFER                                     0x82E0
#define GL_SHADER                                     0x82E1
#define GL_PROGRAM                                    0x82E2
#define GL_QUERY                                      0x82E3
#define GL_PROGRAM_PIPELINE                           0x82E4
#define GL_SAMPLER                                    0x82E6
#define GL_DISPLAY_LIST                               0x82E7
#define GL_MAX_LABEL_LENGTH                           0x82E8
#define GL_MAX_DEBUG_MESSAGE_LENGTH                   0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES                  0x9144
#define GL_DEBUG_LOGGED_MESSAGES                      0x9145
#define GL_DEBUG_SEVERITY_HIGH                        0x9146
#define GL_DEBUG_SEVERITY_MEDIUM                      0x9147
#define GL_DEBUG_SEVERITY_LOW                         0x9148
#define GL_DEBUG_OUTPUT                               0x92E0

// No Error
#define GL_CONTEXT_FLAG_NO_ERROR_BIT_KHR              0x00000008

// Parallel Shader Compile
#define GL_MAX_SHADER_COMPILER_THREADS_KHR            0x91B0
#define GL_COMPLETION_STATUS_KHR                      0x91B1

// Robustness
#define GL_CONTEXT_LOST                               0x0507
#define GL_LOSE_CONTEXT_ON_RESET                      0x8252
#define GL_GUILTY_CONTEXT_RESET                       0x8253
#define GL_INNOCENT_CONTEXT_RESET                     0x8254
#define GL_UNKNOWN_CONTEXT_RESET                      0x8255
#define GL_RESET_NOTIFICATION_STRATEGY                0x8256
#define GL_NO_RESET_NOTIFICATION                      0x8261
#define GL_CONTEXT_ROBUST_ACCESS                      0x90F3

// Texture Compression ASTC HDR
#define GL_COMPRESSED_RGBA_ASTC_4X4_KHR               0x93B0
#define GL_COMPRESSED_RGBA_ASTC_5X4_KHR               0x93B1
#define GL_COMPRESSED_RGBA_ASTC_5X5_KHR               0x93B2
#define GL_COMPRESSED_RGBA_ASTC_6X5_KHR               0x93B3
#define GL_COMPRESSED_RGBA_ASTC_6X6_KHR               0x93B4
#define GL_COMPRESSED_RGBA_ASTC_8X5_KHR               0x93B5
#define GL_COMPRESSED_RGBA_ASTC_8X6_KHR               0x93B6
#define GL_COMPRESSED_RGBA_ASTC_8X8_KHR               0x93B7
#define GL_COMPRESSED_RGBA_ASTC_10X5_KHR              0x93B8
#define GL_COMPRESSED_RGBA_ASTC_10X6_KHR              0x93B9
#define GL_COMPRESSED_RGBA_ASTC_10X8_KHR              0x93BA
#define GL_COMPRESSED_RGBA_ASTC_10X10_KHR             0x93BB
#define GL_COMPRESSED_RGBA_ASTC_12X10_KHR             0x93BC
#define GL_COMPRESSED_RGBA_ASTC_12X12_KHR             0x93BD

#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4X4_KHR       0x93D0
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5X4_KHR       0x93D1
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5X5_KHR       0x93D2
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6X5_KHR       0x93D3
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6X6_KHR       0x93D4
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8X5_KHR       0x93D5
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8X6_KHR       0x93D6
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8X8_KHR       0x93D7
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10X5_KHR      0x93D8
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10X6_KHR      0x93D9
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10X8_KHR      0x93DA
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10X10_KHR     0x93DB
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12X10_KHR     0x93DC
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12X12_KHR     0x93DD


	//blend equation advanced
	inline void(*glBlendBarrierKHR) (void) = nullptr;
#define KHR_blend_equation_advanced 1

	//blend equation advanced coherent
#define KHR_blend_equation_advanced_coherent 1

	//context flush control
#define KHR_context_flush_control 1

	//debug
	typedef void(*GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam);
	inline void(*glDebugMessageCallback) (GLDEBUGPROC callback, const void* userParam) = nullptr;
	inline void(*glDebugMessageControl) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled) = nullptr;
	inline void(*glDebugMessageInsert) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf) = nullptr;
	inline GLuint(*glGetDebugMessageLog) (GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog) = nullptr;
	inline void(*glGetObjectLabel) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label) = nullptr;
	inline void(*glGetObjectPtrLabel) (void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label) = nullptr;
	inline void(*glObjectLabel) (GLenum identifier, GLuint name, GLsizei length, const GLchar* label) = nullptr;
	inline void(*glObjectPtrLabel) (void* ptr, GLsizei length, const GLchar* label) = nullptr;
	inline void(*glPopDebugGroup) (void) = nullptr;
	inline void(*glPushDebugGroup) (GLenum source, GLuint id, GLsizei length, const GLchar* message) = nullptr;
#define KHR_debug 1

	//no error
#define KHR_no_error 1

	//parallel shader compile
	inline void(*glMaxShaderCompilerThreadsKHR) (GLuint count) = nullptr;
#define KHR_parallel_shader_compile 1

	//robust buffer access behavior
#define KHR_robust_buffer_access_behavior 1

	//robustness
	inline void(*glGetnUniformfv) (GLuint program, GLint location, GLsizei bufSize, GLfloat * params) = nullptr;
	inline void(*glGetnUniformiv) (GLuint program, GLint location, GLsizei bufSize, GLint* params) = nullptr;
	inline void(*glGetnUniformuiv) (GLuint program, GLint location, GLsizei bufSize, GLuint* params) = nullptr;
	inline void(*glReadnPixels) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data) = nullptr;
#define KHR_robustness 1

	//texture compression astc hdr
#define KHR_texture_compression_astc_hdr 1

	//texture compression astc ldr
#define KHR_texture_compression_astc_ldr 1

	//texture compression astc sliced 3d
#define KHR_texture_compression_astc_sliced_3d 1

	//*< load KHR Extensions
	inline void LoadKHRExtensions()
	{
		//blend equation advanced
		FetchProcAddress(glBlendBarrierKHR, "glBlendBarrierKHR");

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

		//parallel shader compile
		FetchProcAddress(glMaxShaderCompilerThreadsKHR, "glMaxShaderCompilerThreadsKHR");

		//robustness
		FetchProcAddress(glGetnUniformfv, "glGetnUniformfv");
		FetchProcAddress(glGetnUniformiv, "glGetnUniformiv");
		FetchProcAddress(glGetnUniformuiv, "glGetnUniformuiv");
		FetchProcAddress(glReadnPixels, "glReadnPixels");
	}



#pragma endregion KHR Extensions

	//OpenGL KTX Extensions
#pragma region KTX

// Buffer Region
#define GL_KTX_FRONT_REGION                           0x0
#define GL_KTX_BACK_REGION                            0x1
#define GL_KTX_Z_REGION                               0x2
#define GL_KTX_STENCIL_REGION                         0x3

	//buffer region
	inline GLuint(*glBufferRegionEnabled) (void) = nullptr;
	inline void(*glDeleteBufferRegion) (GLenum region) = nullptr;
	inline void(*glDrawBufferRegion) (GLuint region, GLint x, GLint y, GLsizei width, GLsizei height, GLint xDest, GLint yDest) = nullptr;
	inline GLuint(*glNewBufferRegion) (GLenum region) = nullptr;
	inline void(*glReadBufferRegion) (GLuint region, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
#define KTX_buffer_region 1

	//*< load KTX Extensions
	inline void LoadKTXExtensions()
	{
		//buffer region
		FetchProcAddress(glBufferRegionEnabled, "glBufferRegionEnabled");
		FetchProcAddress(glDeleteBufferRegion, "glDeleteBufferRegion");
		FetchProcAddress(glDrawBufferRegion, "glDrawBufferRegion");
		FetchProcAddress(glNewBufferRegion, "glNewBufferRegion");
		FetchProcAddress(glReadBufferRegion, "glReadBufferRegion");
	}

#pragma endregion KTX Extensions

	//OpenGL MESAX Extensions
#pragma region MESAX

// Texture Stack
#define GL_TEXTURE_1D_STACK_MESAX                     0x8759
#define GL_TEXTURE_2D_STACK_MESAX                     0x875A
#define GL_PROXY_TEXTURE_1D_STACK_MESAX               0x875B
#define GL_PROXY_TEXTURE_2D_STACK_MESAX               0x875C
#define GL_TEXTURE_1D_STACK_BINDING_MESAX             0x875D
#define GL_TEXTURE_2D_STACK_BINDING_MESAX             0x875E


	//texture stack
#define MESAX_texture_stack 1

	//*< load MESAX Extensions
	inline void LoadMESAXExtensions()
	{

	}

#pragma endregion MESAX Extensions

	//OpenGL MESA Extensions
#pragma region MESA

// YCbCr Texture
#define GL_UNSIGNED_SHORT_8_8_MESA                    0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_MESA                0x85BB
#define GL_YCBCR_MESA                                 0x8757

// Pack Invert
#define GL_PACK_INVERT_MESA                           0x8758

	//pack_invert
#define MESA_pack_invert 1

	//resize_buffers
	inline void(*glResizeBuffersMESA) (void) = nullptr;
#define MESA_resize_buffers 1

	//shader_integer_functions
#define MESA_shader_integer_functions 1

	//window_pos
	inline void(*glWindowPos2dMESA) (GLdouble x, GLdouble y) = nullptr;
	inline void(*glWindowPos2dvMESA) (const GLdouble* p) = nullptr;
	inline void(*glWindowPos2fMESA) (GLfloat x, GLfloat y) = nullptr;
	inline void(*glWindowPos2fvMESA) (const GLfloat* p) = nullptr;
	inline void(*glWindowPos2iMESA) (GLint x, GLint y) = nullptr;
	inline void(*glWindowPos2ivMESA) (const GLint* p) = nullptr;
	inline void(*glWindowPos2sMESA) (GLshort x, GLshort y) = nullptr;
	inline void(*glWindowPos2svMESA) (const GLshort* p) = nullptr;
	inline void(*glWindowPos3dMESA) (GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glWindowPos3dvMESA) (const GLdouble* p) = nullptr;
	inline void(*glWindowPos3fMESA) (GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glWindowPos3fvMESA) (const GLfloat* p) = nullptr;
	inline void(*glWindowPos3iMESA) (GLint x, GLint y, GLint z) = nullptr;
	inline void(*glWindowPos3ivMESA) (const GLint* p) = nullptr;
	inline void(*glWindowPos3sMESA) (GLshort x, GLshort y, GLshort z) = nullptr;
	inline void(*glWindowPos3svMESA) (const GLshort* p) = nullptr;
	inline void(*glWindowPos4dMESA) (GLdouble x, GLdouble y, GLdouble z, GLdouble) = nullptr;
	inline void(*glWindowPos4dvMESA) (const GLdouble* p) = nullptr;
	inline void(*glWindowPos4fMESA) (GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glWindowPos4fvMESA) (const GLfloat* p) = nullptr;
	inline void(*glWindowPos4iMESA) (GLint x, GLint y, GLint z, GLint w) = nullptr;
	inline void(*glWindowPos4ivMESA) (const GLint* p) = nullptr;
	inline void(*glWindowPos4sMESA) (GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
	inline void(*glWindowPos4svMESA) (const GLshort* p) = nullptr;
#define MESA_window_pos 1

	//ycbcr_texture
#define MESA_ycbcr_texture 1

	//*< load MESA Extensions
	inline void LoadMESAExtensions()
	{
		//resize_buffers
		FetchProcAddress(glResizeBuffersMESA, "glResizeBuffersMESA");

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
	}

#pragma endregion MESA Extensions

	//OpenGL NVX Extensions
#pragma region NVX

// GPU Memory Info
#define GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX       0x9047
#define GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX 0x9048
#define GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX 0x9049
#define GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX         0x904A
#define GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX         0x904B

// Linked GPU Multicast
#define GL_LGPU_SEPARATE_STORAGE_BIT_NVX              0x0800
#define GL_MAX_LGPU_GPUS_NVX                          0x92BA


	//blend_equation_advanced_multi_draw_buffers
#define NVX_blend_equation_advanced_multi_draw_buffers 1

	//conditional_render
	inline void(*glBeginConditionalRenderNVX) (GLuint id) = nullptr;
	inline void(*glEndConditionalRenderNVX) (void) = nullptr;
#define NVX_conditional_render 1

	//gpu_memory_info
#define NVX_gpu_memory_info 1

	//linked_gpu_multicast
	inline void(*glLGPUCopyImageSubDataNVX) (GLuint sourceGpu, GLbitfield destinationGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srxY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
	inline void(*glLGPUInterlockNVX) (void) = nullptr;
	inline void(*glLGPUNamedBufferSubDataNVX) (GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) = nullptr;
#define NVX_linked_gpu_multicast 1

	//*< load NVX Extensions
	inline void LoadNVXExtensions()
	{
		//conditional_render
		FetchProcAddress(glBeginConditionalRenderNVX, "glBeginConditionalRenderNVX");
		FetchProcAddress(glEndConditionalRenderNVX, "glEndConditionalRenderNVX");

		//linked_gpu_multicast
		FetchProcAddress(glLGPUCopyImageSubDataNVX, "glLGPUCopyImageSubDataNVX");
		FetchProcAddress(glLGPUInterlockNVX, "glLGPUInterlockNVX");
		FetchProcAddress(glLGPUNamedBufferSubDataNVX, "glLGPUNamedBufferSubDataNVX");
	}

#pragma endregion NVX Extensions

	//OpenGL NV Extensions
#pragma region NV

	typedef GLintptr GLvdpauSurfaceNV;
	typedef unsigned short GLhalf;

// 3D Vision Settings (NV)
#define GL_3DVISION_STEREO_NV                         0x90F4
#define GL_STEREO_SEPARATION_NV                       0x90F5
#define GL_STEREO_CONVERGENCE_NV                      0x90F6
#define GL_STEREO_CUTOFF_NV                           0x90F7
#define GL_STEREO_PROJECTION_NV                       0x90F8
#define GL_STEREO_PROJECTION_PERSPECTIVE_NV           0x90F9
#define GL_STEREO_PROJECTION_ORTHO_NV                 0x90FA

// EGL Stream Consumer External (OES)
#define GL_TEXTURE_EXTERNAL_OES                       0x8D65
#define GL_SAMPLER_EXTERNAL_OES                       0x8D66
#define GL_TEXTURE_BINDING_EXTERNAL_OES               0x8D67
#define GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES           0x8D68

// Alpha To Coverage Dither Control (NV)
#define GL_ALPHA_TO_COVERAGE_DITHER_MODE_NV           0x92BF
#define GL_ALPHA_TO_COVERAGE_DITHER_DEFAULT_NV        0x934D
#define GL_ALPHA_TO_COVERAGE_DITHER_ENABLE_NV         0x934E
#define GL_ALPHA_TO_COVERAGE_DITHER_DISABLE_NV        0x934F

// BGR Format (NV)
#define GL_BGR_NV                                     0x80E0

// Blend Equation Advanced (NV)
#define GL_XOR_NV                                     0x1506
#define GL_RED_NV                                     0x1903
#define GL_GREEN_NV                                   0x1904
#define GL_BLUE_NV                                    0x1905
#define GL_BLEND_PREMULTIPLIED_SRC_NV                 0x9280
#define GL_BLEND_OVERLAP_NV                           0x9281
#define GL_UNCORRELATED_NV                            0x9282
#define GL_DISJOINT_NV                                0x9283
#define GL_CONJOINT_NV                                0x9284
#define GL_BLEND_ADVANCED_COHERENT_NV                 0x9285
#define GL_SRC_NV                                     0x9286
#define GL_DST_NV                                     0x9287
#define GL_SRC_OVER_NV                                0x9288
#define GL_DST_OVER_NV                                0x9289
#define GL_SRC_IN_NV                                  0x928A
#define GL_DST_IN_NV                                  0x928B
#define GL_SRC_OUT_NV                                 0x928C
#define GL_DST_OUT_NV                                 0x928D
#define GL_SRC_ATOP_NV                                0x928E
#define GL_DST_ATOP_NV                                0x928F
#define GL_PLUS_NV                                    0x9291
#define GL_PLUS_DARKER_NV                             0x9292
#define GL_MULTIPLY_NV                                0x9294
#define GL_SCREEN_NV                                  0x9295
#define GL_OVERLAY_NV                                 0x9296
#define GL_DARKEN_NV                                  0x9297
#define GL_LIGHTEN_NV                                 0x9298
#define GL_COLORDODGE_NV                              0x9299
#define GL_COLORBURN_NV                               0x929A
#define GL_HARDLIGHT_NV                               0x929B
#define GL_SOFTLIGHT_NV                               0x929C
#define GL_DIFFERENCE_NV                              0x929E
#define GL_MINUS_NV                                   0x929F
#define GL_EXCLUSION_NV                               0x92A0
#define GL_CONTRAST_NV                                0x92A1
#define GL_INVERT_RGB_NV                              0x92A3
#define GL_LINEARDODGE_NV                             0x92A4
#define GL_LINEARBURN_NV                              0x92A5
#define GL_VIVIDLIGHT_NV                              0x92A6
#define GL_LINEARLIGHT_NV                             0x92A7
#define GL_PINLIGHT_NV                                0x92A8
#define GL_HARDMIX_NV                                 0x92A9
#define GL_HSL_HUE_NV                                 0x92AD
#define GL_HSL_SATURATION_NV                          0x92AE
#define GL_HSL_COLOR_NV                               0x92AF
#define GL_HSL_LUMINOSITY_NV                          0x92B0
#define GL_PLUS_CLAMPED_NV                            0x92B1
#define GL_PLUS_CLAMPED_ALPHA_NV                      0x92B2
#define GL_MINUS_CLAMPED_NV                           0x92B3
#define GL_INVERT_OVG_NV                              0x92B4

// Blend Minmax Factor (AMD)
#define GL_FACTOR_MIN_AMD                             0x901C
#define GL_FACTOR_MAX_AMD                             0x901D

// Clip Space W Scaling (NV)
#define GL_VIEWPORT_POSITION_W_SCALE_NV               0x937C
#define GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV       0x937D
#define GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV       0x937E


// Command List
#define GL_TERMINATE_SEQUENCE_COMMAND_NV             0x0000
#define GL_NOP_COMMAND_NV                             0x0001
#define GL_DRAW_ELEMENTS_COMMAND_NV                   0x0002
#define GL_DRAW_ARRAYS_COMMAND_NV                     0x0003
#define GL_DRAW_ELEMENTS_STRIP_COMMAND_NV             0x0004
#define GL_DRAW_ARRAYS_STRIP_COMMAND_NV               0x0005
#define GL_DRAW_ELEMENTS_INSTANCED_COMMAND_NV         0x0006
#define GL_DRAW_ARRAYS_INSTANCED_COMMAND_NV           0x0007
#define GL_ELEMENT_ADDRESS_COMMAND_NV                  0x0008
#define GL_ATTRIBUTE_ADDRESS_COMMAND_NV                0x0009
#define GL_UNIFORM_ADDRESS_COMMAND_NV                  0x000A
#define GL_BLEND_COLOR_COMMAND_NV                      0x000B
#define GL_STENCIL_REF_COMMAND_NV                      0x000C
#define GL_LINE_WIDTH_COMMAND_NV                       0x000D
#define GL_POLYGON_OFFSET_COMMAND_NV                   0x000E
#define GL_ALPHA_REF_COMMAND_NV                        0x000F
#define GL_VIEWPORT_COMMAND_NV                         0x0010
#define GL_SCISSOR_COMMAND_NV                          0x0011
#define GL_FRONT_FACE_COMMAND_NV                       0x0012

// Compute Program5
#define GL_COMPUTE_PROGRAM_NV                         0x90FB
#define GL_COMPUTE_PROGRAM_PARAMETER_BUFFER_NV       0x90FC

// Conditional Render
#define GL_QUERY_WAIT_NV                              0x8E13
#define GL_QUERY_NO_WAIT_NV                           0x8E14
#define GL_QUERY_BY_REGION_WAIT_NV                    0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT_NV                 0x8E16

// Conservative Raster
#define GL_CONSERVATIVE_RASTERIZATION_NV              0x9346
#define GL_SUBPIXEL_PRECISION_BIAS_X_BITS_NV           0x9347
#define GL_SUBPIXEL_PRECISION_BIAS_Y_BITS_NV           0x9348
#define GL_MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV         0x9349

// Conservative Raster Dilate
#define GL_CONSERVATIVE_RASTER_DILATE_NV               0x9379
#define GL_CONSERVATIVE_RASTER_DILATE_RANGE_NV         0x937A
#define GL_CONSERVATIVE_RASTER_DILATE_GRANULARITY_NV   0x937B

// Conservative Raster Pre Snap Triangles
#define GL_CONSERVATIVE_RASTER_MODE_NV                  0x954D
#define GL_CONSERVATIVE_RASTER_MODE_POST_SNAP_NV       0x954E
#define GL_CONSERVATIVE_RASTER_MODE_PRE_SNAP_TRIANGLES_NV 0x954F

// Copy Buffer
#define GL_COPY_READ_BUFFER_NV                         0x8F36
#define GL_COPY_WRITE_BUFFER_NV                        0x8F37

// Copy Depth to Color
#define GL_DEPTH_STENCIL_TO_RGBA_NV                    0x886E
#define GL_DEPTH_STENCIL_TO_BGRA_NV                    0x886F

// Deep Texture3D
#define GL_MAX_DEEP_3D_TEXTURE_WIDTH_HEIGHT_NV         0x90D0
#define GL_MAX_DEEP_3D_TEXTURE_DEPTH_NV                 0x90D1

// Depth Buffer Float
#define GL_DEPTH_COMPONENT32F_NV                       0x8DAB
#define GL_DEPTH32F_STENCIL8_NV                        0x8DAC
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV_NV           0x8DAD
#define GL_DEPTH_BUFFER_FLOAT_MODE_NV                  0x8DAF

// Depth Clamp
#define GL_DEPTH_CLAMP_NV                              0x864F

// Depth Range Unclamped
#define GL_SAMPLE_COUNT_BITS_NV                        0x8864
#define GL_CURRENT_SAMPLE_COUNT_QUERY_NV               0x8865
#define GL_QUERY_RESULT_NV                             0x8866
#define GL_QUERY_RESULT_AVAILABLE_NV                   0x8867
#define GL_SAMPLE_COUNT_NV                             0x8914

// Draw Buffers
#define GL_MAX_DRAW_BUFFERS_NV                         0x8824
#define GL_DRAW_BUFFER0_NV                             0x8825
#define GL_DRAW_BUFFER1_NV                             0x8826
#define GL_DRAW_BUFFER2_NV                             0x8827
#define GL_DRAW_BUFFER3_NV                             0x8828
#define GL_DRAW_BUFFER4_NV                             0x8829
#define GL_DRAW_BUFFER5_NV                             0x882A
#define GL_DRAW_BUFFER6_NV                             0x882B
#define GL_DRAW_BUFFER7_NV                             0x882C
#define GL_DRAW_BUFFER8_NV                             0x882D
#define GL_DRAW_BUFFER9_NV                             0x882E
#define GL_DRAW_BUFFER10_NV                            0x882F
#define GL_DRAW_BUFFER11_NV                            0x8830
#define GL_DRAW_BUFFER12_NV                            0x8831
#define GL_DRAW_BUFFER13_NV                            0x8832
#define GL_DRAW_BUFFER14_NV                            0x8833
#define GL_DRAW_BUFFER15_NV                            0x8834

#define GL_COLOR_ATTACHMENT0_NV                        0x8CE0
#define GL_COLOR_ATTACHMENT1_NV                        0x8CE1
#define GL_COLOR_ATTACHMENT2_NV                        0x8CE2
#define GL_COLOR_ATTACHMENT3_NV                        0x8CE3
#define GL_COLOR_ATTACHMENT4_NV                        0x8CE4
#define GL_COLOR_ATTACHMENT5_NV                        0x8CE5
#define GL_COLOR_ATTACHMENT6_NV                        0x8CE6
#define GL_COLOR_ATTACHMENT7_NV                        0x8CE7
#define GL_COLOR_ATTACHMENT8_NV                        0x8CE8
#define GL_COLOR_ATTACHMENT9_NV                        0x8CE9
#define GL_COLOR_ATTACHMENT10_NV                       0x8CEA
#define GL_COLOR_ATTACHMENT11_NV                       0x8CEB
#define GL_COLOR_ATTACHMENT12_NV                       0x8CEC
#define GL_COLOR_ATTACHMENT13_NV                       0x8CED
#define GL_COLOR_ATTACHMENT14_NV                       0x8CEE
#define GL_COLOR_ATTACHMENT15_NV                       0x8CEF

// Evaluators
#define GL_EVAL_2D_NV                           0x86C0
#define GL_EVAL_TRIANGULAR_2D_NV                0x86C1
#define GL_MAP_TESSELLATION_NV                   0x86C2
#define GL_MAP_ATTRIB_U_ORDER_NV                 0x86C3
#define GL_MAP_ATTRIB_V_ORDER_NV                 0x86C4
#define GL_EVAL_FRACTIONAL_TESSELLATION_NV      0x86C5
#define GL_EVAL_VERTEX_ATTRIB0_NV                0x86C6
#define GL_EVAL_VERTEX_ATTRIB1_NV                0x86C7
#define GL_EVAL_VERTEX_ATTRIB2_NV                0x86C8
#define GL_EVAL_VERTEX_ATTRIB3_NV                0x86C9
#define GL_EVAL_VERTEX_ATTRIB4_NV                0x86CA
#define GL_EVAL_VERTEX_ATTRIB5_NV                0x86CB
#define GL_EVAL_VERTEX_ATTRIB6_NV                0x86CC
#define GL_EVAL_VERTEX_ATTRIB7_NV                0x86CD
#define GL_EVAL_VERTEX_ATTRIB8_NV                0x86CE
#define GL_EVAL_VERTEX_ATTRIB9_NV                0x86CF
#define GL_EVAL_VERTEX_ATTRIB10_NV               0x86D0
#define GL_EVAL_VERTEX_ATTRIB11_NV               0x86D1
#define GL_EVAL_VERTEX_ATTRIB12_NV               0x86D2
#define GL_EVAL_VERTEX_ATTRIB13_NV               0x86D3
#define GL_EVAL_VERTEX_ATTRIB14_NV               0x86D4
#define GL_EVAL_VERTEX_ATTRIB15_NV               0x86D5
#define GL_MAX_MAP_TESSELLATION_NV               0x86D6
#define GL_MAX_RATIONAL_EVAL_ORDER_NV            0x86D7

// Explicit Multisample
#define GL_SAMPLE_POSITION_NV                    0x8E50
#define GL_SAMPLE_MASK_NV                        0x8E51
#define GL_SAMPLE_MASK_VALUE_NV                  0x8E52
#define GL_TEXTURE_BINDING_RENDERBUFFER_NV      0x8E53
#define GL_TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV 0x8E54
#define GL_TEXTURE_RENDERBUFFER_NV               0x8E55
#define GL_SAMPLER_RENDERBUFFER_NV               0x8E56
#define GL_INT_SAMPLER_RENDERBUFFER_NV           0x8E57
#define GL_UNSIGNED_INT_SAMPLER_RENDERBUFFER_NV  0x8E58
#define GL_MAX_SAMPLE_MASK_WORDS_NV               0x8E59

// FBO Color Attachments
#define GL_MAX_COLOR_ATTACHMENTS_NV              0x8CDF
#define GL_COLOR_ATTACHMENT0_NV                  0x8CE0
#define GL_COLOR_ATTACHMENT1_NV                  0x8CE1
#define GL_COLOR_ATTACHMENT2_NV                  0x8CE2
#define GL_COLOR_ATTACHMENT3_NV                  0x8CE3
#define GL_COLOR_ATTACHMENT4_NV                  0x8CE4
#define GL_COLOR_ATTACHMENT5_NV                  0x8CE5
#define GL_COLOR_ATTACHMENT6_NV                  0x8CE6
#define GL_COLOR_ATTACHMENT7_NV                  0x8CE7
#define GL_COLOR_ATTACHMENT8_NV                  0x8CE8
#define GL_COLOR_ATTACHMENT9_NV                  0x8CE9
#define GL_COLOR_ATTACHMENT10_NV                 0x8CEA
#define GL_COLOR_ATTACHMENT11_NV                 0x8CEB
#define GL_COLOR_ATTACHMENT12_NV                 0x8CEC
#define GL_COLOR_ATTACHMENT13_NV                 0x8CED
#define GL_COLOR_ATTACHMENT14_NV                 0x8CEE
#define GL_COLOR_ATTACHMENT15_NV                 0x8CEF

// Fence
#define GL_ALL_COMPLETED_NV                      0x84F2
#define GL_FENCE_STATUS_NV                       0x84F3
#define GL_FENCE_CONDITION_NV                    0x84F4

// Fill Rectangle
#define GL_FILL_RECTANGLE_NV                     0x933C

// Float Buffer
#define GL_FLOAT_R_NV                           0x8880
#define GL_FLOAT_RG_NV                          0x8881
#define GL_FLOAT_RGB_NV                         0x8882
#define GL_FLOAT_RGBA_NV                        0x8883
#define GL_FLOAT_R16_NV                         0x8884
#define GL_FLOAT_R32_NV                         0x8885
#define GL_FLOAT_RG16_NV                        0x8886
#define GL_FLOAT_RG32_NV                        0x8887
#define GL_FLOAT_RGB16_NV                       0x8888
#define GL_FLOAT_RGB32_NV                       0x8889
#define GL_FLOAT_RGBA16_NV                      0x888A
#define GL_FLOAT_RGBA32_NV                      0x888B
#define GL_TEXTURE_FLOAT_COMPONENTS_NV          0x888C
#define GL_FLOAT_CLEAR_COLOR_VALUE_NV            0x888D
#define GL_FLOAT_RGBA_MODE_NV                    0x888E


// Fog Distance
#define GL_FOG_DISTANCE_MODE_NV                 0x855A
#define GL_EYE_RADIAL_NV                       0x855B
#define GL_EYE_PLANE_ABSOLUTE_NV               0x855C

// Fragment Coverage to Color
#define GL_FRAGMENT_COVERAGE_TO_COLOR_NV       0x92DD
#define GL_FRAGMENT_COVERAGE_COLOR_NV          0x92DE

// Fragment Program
#define GL_MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV 0x8868
#define GL_FRAGMENT_PROGRAM_NV                  0x8870
#define GL_MAX_TEXTURE_COORDS_NV                0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_NV           0x8872
#define GL_FRAGMENT_PROGRAM_BINDING_NV          0x8873
#define GL_PROGRAM_ERROR_STRING_NV              0x8874

// Fragment Program 2
#define GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV    0x88F4
#define GL_MAX_PROGRAM_CALL_DEPTH_NV            0x88F5
#define GL_MAX_PROGRAM_IF_DEPTH_NV              0x88F6
#define GL_MAX_PROGRAM_LOOP_DEPTH_NV            0x88F7
#define GL_MAX_PROGRAM_LOOP_COUNT_NV            0x88F8

// Framebuffer Blit
#define GL_DRAW_FRAMEBUFFER_BINDING_NV          0x8CA6
#define GL_READ_FRAMEBUFFER_NV                   0x8CA8
#define GL_DRAW_FRAMEBUFFER_NV                   0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING_NV           0x8CAA

// Framebuffer Mixed Samples
#define GL_COLOR_SAMPLES_NV                      0x8E20
#define GL_RASTER_MULTISAMPLE_EXT                0x9327
#define GL_RASTER_SAMPLES_EXT                    0x9328
#define GL_MAX_RASTER_SAMPLES_EXT                0x9329
#define GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT    0x932A
#define GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#define GL_EFFECTIVE_RASTER_SAMPLES_EXT         0x932C
#define GL_DEPTH_SAMPLES_NV                      0x932D
#define GL_STENCIL_SAMPLES_NV                    0x932E
#define GL_MIXED_DEPTH_SAMPLES_SUPPORTED_NV     0x932F
#define GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV   0x9330
#define GL_COVERAGE_MODULATION_TABLE_NV          0x9331
#define GL_COVERAGE_MODULATION_NV                0x9332
#define GL_COVERAGE_MODULATION_TABLE_SIZE_NV    0x9333

// Framebuffer Multisample
#define GL_RENDERBUFFER_SAMPLES_NV               0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV 0x8D56
#define GL_MAX_SAMPLES_NV                        0x8D57

// Framebuffer Multisample Coverage
#define GL_RENDERBUFFER_COVERAGE_SAMPLES_NV     0x8CAB
#define GL_RENDERBUFFER_COLOR_SAMPLES_NV        0x8E10
#define GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV    0x8E11
#define GL_MULTISAMPLE_COVERAGE_MODES_NV        0x8E12


// Geometry Program 4
#define GL_GEOMETRY_PROGRAM_NV                     0x8C26
#define GL_MAX_PROGRAM_OUTPUT_VERTICES_NV          0x8C27
#define GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV  0x8C28

// GPU Multicast
#define GL_PER_GPU_STORAGE_BIT_NV                   0x0800
#define GL_MULTICAST_GPUS_NV                        0x92BA
#define GL_PER_GPU_STORAGE_NV                       0x9548
#define GL_MULTICAST_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9549
#define GL_RENDER_GPU_MASK_NV                       0x9558

// GPU Program 4
#define GL_MIN_PROGRAM_TEXEL_OFFSET_NV              0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET_NV              0x8905
#define GL_PROGRAM_ATTRIB_COMPONENTS_NV             0x8906
#define GL_PROGRAM_RESULT_COMPONENTS_NV             0x8907
#define GL_MAX_PROGRAM_ATTRIB_COMPONENTS_NV         0x8908
#define GL_MAX_PROGRAM_RESULT_COMPONENTS_NV         0x8909
#define GL_MAX_PROGRAM_GENERIC_ATTRIBS_NV           0x8DA5
#define GL_MAX_PROGRAM_GENERIC_RESULTS_NV           0x8DA6

// GPU Program 5
#define GL_MAX_GEOMETRY_PROGRAM_INVOCATIONS_NV      0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET_NV     0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET_NV     0x8E5C
#define GL_FRAGMENT_PROGRAM_INTERPOLATION_OFFSET_BITS_NV 0x8E5D
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_NV     0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_NV     0x8E5F

// GPU Shader 5
#define GL_INT64_NV                                 0x140E
#define GL_UNSIGNED_INT64_NV                        0x140F
#define GL_INT8_NV                                  0x8FE0
#define GL_INT8_VEC2_NV                             0x8FE1
#define GL_INT8_VEC3_NV                             0x8FE2
#define GL_INT8_VEC4_NV                             0x8FE3
#define GL_INT16_NV                                 0x8FE4
#define GL_INT16_VEC2_NV                            0x8FE5
#define GL_INT16_VEC3_NV                            0x8FE6
#define GL_INT16_VEC4_NV                            0x8FE7
#define GL_INT64_VEC2_NV                            0x8FE9
#define GL_INT64_VEC3_NV                            0x8FEA
#define GL_INT64_VEC4_NV                            0x8FEB
#define GL_UNSIGNED_INT8_NV                         0x8FEC
#define GL_UNSIGNED_INT8_VEC2_NV                    0x8FED
#define GL_UNSIGNED_INT8_VEC3_NV                    0x8FEE
#define GL_UNSIGNED_INT8_VEC4_NV                    0x8FEF
#define GL_UNSIGNED_INT16_NV                        0x8FF0
#define GL_UNSIGNED_INT16_VEC2_NV                   0x8FF1
#define GL_UNSIGNED_INT16_VEC3_NV                   0x8FF2
#define GL_UNSIGNED_INT16_VEC4_NV                   0x8FF3
#define GL_UNSIGNED_INT64_VEC2_NV                   0x8FF5
#define GL_UNSIGNED_INT64_VEC3_NV                   0x8FF6
#define GL_UNSIGNED_INT64_VEC4_NV                   0x8FF7
#define GL_FLOAT16_NV                               0x8FF8
#define GL_FLOAT16_VEC2_NV                          0x8FF9
#define GL_FLOAT16_VEC3_NV                          0x8FFA
#define GL_FLOAT16_VEC4_NV                          0x8FFB

// Half Float
#define GL_HALF_FLOAT_NV                            0x140B

// Instanced Arrays
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_NV          0x88FE

// Internalformat Sample Query
#define GL_MULTISAMPLES_NV                          0x9371
#define GL_SUPERSAMPLE_SCALE_X_NV                   0x9372
#define GL_SUPERSAMPLE_SCALE_Y_NV                   0x9373
#define GL_CONFORMANT_NV                            0x9374

// Light Max Exponent
#define GL_MAX_SHININESS_NV                         0x8504
#define GL_MAX_SPOT_EXPONENT_NV                     0x8505

// Multisample Coverage
#define GL_COLOR_SAMPLES_NV                         0x8E20

// Multisample Filter Hint
#define GL_MULTISAMPLE_FILTER_HINT_NV               0x8534

// Non-square Matrices
#define GL_FLOAT_MAT2x3_NV                          0x8B65
#define GL_FLOAT_MAT2x4_NV                          0x8B66
#define GL_FLOAT_MAT3x2_NV                          0x8B67
#define GL_FLOAT_MAT3x4_NV                          0x8B68
#define GL_FLOAT_MAT4x2_NV                          0x8B69
#define GL_FLOAT_MAT4x3_NV                          0x8B6A

// Occlusion Query
#define GL_PIXEL_COUNTER_BITS_NV                     0x8864
#define GL_CURRENT_OCCLUSION_QUERY_ID_NV             0x8865
#define GL_PIXEL_COUNT_NV                            0x8866
#define GL_PIXEL_COUNT_AVAILABLE_NV                  0x8867

// Pack Subimage
#define GL_PACK_ROW_LENGTH_NV                        0x0D02
#define GL_PACK_SKIP_ROWS_NV                         0x0D03
#define GL_PACK_SKIP_PIXELS_NV                       0x0D04

// Packed Depth Stencil
#define GL_DEPTH_STENCIL_NV                          0x84F9
#define GL_UNSIGNED_INT_24_8_NV                      0x84FA

// Packed Float
#define GL_R11F_G11F_B10F_NV                         0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV_NV           0x8C3B

// Parameter Buffer Object
#define GL_MAX_PROGRAM_PARAMETER_BUFFER_BINDINGS_NV 0x8DA0
#define GL_MAX_PROGRAM_PARAMETER_BUFFER_SIZE_NV    0x8DA1
#define GL_VERTEX_PROGRAM_PARAMETER_BUFFER_NV      0x8DA2
#define GL_GEOMETRY_PROGRAM_PARAMETER_BUFFER_NV    0x8DA3
#define GL_FRAGMENT_PROGRAM_PARAMETER_BUFFER_NV    0x8DA4

// Path Rendering
#define GL_CLOSE_PATH_NV                             0x00
#define GL_BOLD_BIT_NV                               0x01
#define GL_GLYPH_WIDTH_BIT_NV                        0x01
#define GL_GLYPH_HEIGHT_BIT_NV                       0x02
#define GL_ITALIC_BIT_NV                             0x02
#define GL_MOVE_TO_NV                                0x02
#define GL_RELATIVE_MOVE_TO_NV                       0x03
#define GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV        0x04
#define GL_LINE_TO_NV                                0x04
#define GL_RELATIVE_LINE_TO_NV                       0x05
#define GL_HORIZONTAL_LINE_TO_NV                     0x06
#define GL_RELATIVE_HORIZONTAL_LINE_TO_NV            0x07
#define GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV        0x08
#define GL_VERTICAL_LINE_TO_NV                       0x08
#define GL_RELATIVE_VERTICAL_LINE_TO_NV              0x09
#define GL_QUADRATIC_CURVE_TO_NV                     0x0A
#define GL_RELATIVE_QUADRATIC_CURVE_TO_NV            0x0B
#define GL_CUBIC_CURVE_TO_NV                         0x0C
#define GL_RELATIVE_CUBIC_CURVE_TO_NV                 0x0D
#define GL_SMOOTH_QUADRATIC_CURVE_TO_NV              0x0E
#define GL_RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV     0x0F
#define GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV   0x10
#define GL_SMOOTH_CUBIC_CURVE_TO_NV                   0x10
#define GL_RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV          0x11
#define GL_SMALL_CCW_ARC_TO_NV                        0x12
#define GL_RELATIVE_SMALL_CCW_ARC_TO_NV               0x13
#define GL_SMALL_CW_ARC_TO_NV                         0x14
#define GL_RELATIVE_SMALL_CW_ARC_TO_NV                 0x15
#define GL_LARGE_CCW_ARC_TO_NV                        0x16
#define GL_RELATIVE_LARGE_CCW_ARC_TO_NV               0x17
#define GL_LARGE_CW_ARC_TO_NV                         0x18
#define GL_RELATIVE_LARGE_CW_ARC_TO_NV                 0x19
#define GL_CONIC_CURVE_TO_NV                          0x1A
#define GL_RELATIVE_CONIC_CURVE_TO_NV                 0x1B
#define GL_GLYPH_VERTICAL_BEARING_X_BIT_NV            0x20
#define GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV            0x40
#define GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV      0x80
#define GL_ROUNDED_RECT_NV                            0xE8
#define GL_RELATIVE_ROUNDED_RECT_NV                   0xE9
#define GL_ROUNDED_RECT2_NV                           0xEA
#define GL_RELATIVE_ROUNDED_RECT2_NV                  0xEB
#define GL_ROUNDED_RECT4_NV                           0xEC
#define GL_RELATIVE_ROUNDED_RECT4_NV                  0xED
#define GL_ROUNDED_RECT8_NV                           0xEE
#define GL_RELATIVE_ROUNDED_RECT8_NV                  0xEF
#define GL_RESTART_PATH_NV                            0xF0
#define GL_DUP_FIRST_CUBIC_CURVE_TO_NV                 0xF2
#define GL_DUP_LAST_CUBIC_CURVE_TO_NV                  0xF4
#define GL_RECT_NV                                   0xF6
#define GL_RELATIVE_RECT_NV                           0xF7
#define GL_CIRCULAR_CCW_ARC_TO_NV                      0xF8
#define GL_CIRCULAR_CW_ARC_TO_NV                       0xFA
#define GL_CIRCULAR_TANGENT_ARC_TO_NV                   0xFC
#define GL_ARC_TO_NV                                 0xFE
#define GL_RELATIVE_ARC_TO_NV                         0xFF
#define GL_GLYPH_HAS_KERNING_BIT_NV                  0x100
#define GL_PRIMARY_COLOR_NV                          0x852C
#define GL_SECONDARY_COLOR_NV                        0x852D
#define GL_PRIMARY_COLOR                             0x8577
#define GL_PATH_FORMAT_SVG_NV                        0x9070
#define GL_PATH_FORMAT_PS_NV                         0x9071
#define GL_STANDARD_FONT_NAME_NV                      0x9072
#define GL_SYSTEM_FONT_NAME_NV                        0x9073
#define GL_FILE_NAME_NV                              0x9074
#define GL_PATH_STROKE_WIDTH_NV                       0x9075
#define GL_PATH_END_CAPS_NV                          0x9076
#define GL_PATH_INITIAL_END_CAP_NV                   0x9077
#define GL_PATH_TERMINAL_END_CAP_NV                  0x9078
#define GL_PATH_JOIN_STYLE_NV                        0x9079
#define GL_PATH_MITER_LIMIT_NV                       0x907A
#define GL_PATH_DASH_CAPS_NV                         0x907B
#define GL_PATH_INITIAL_DASH_CAP_NV                  0x907C
#define GL_PATH_TERMINAL_DASH_CAP_NV                 0x907D
#define GL_PATH_DASH_OFFSET_NV                       0x907E
#define GL_PATH_CLIENT_LENGTH_NV                     0x907F
#define GL_PATH_FILL_MODE_NV                         0x9080
#define GL_PATH_FILL_MASK_NV                         0x9081
#define GL_PATH_FILL_COVER_MODE_NV                   0x9082
#define GL_PATH_STROKE_COVER_MODE_NV                 0x9083
#define GL_PATH_STROKE_MASK_NV                       0x9084
#define GL_PATH_STROKE_BOUND_NV                      0x9086
#define GL_COUNT_UP_NV                              0x9088
#define GL_COUNT_DOWN_NV                            0x9089
#define GL_PATH_OBJECT_BOUNDING_BOX_NV               0x908A
#define GL_CONVEX_HULL_NV                           0x908B
#define GL_BOUNDING_BOX_NV                          0x908D
#define GL_TRANSLATE_X_NV                           0x908E
#define GL_TRANSLATE_Y_NV                           0x908F
#define GL_TRANSLATE_2D_NV                          0x9090
#define GL_TRANSLATE_3D_NV                          0x9091
#define GL_AFFINE_2D_NV                             0x9092
#define GL_AFFINE_3D_NV                             0x9094
#define GL_TRANSPOSE_AFFINE_2D_NV                   0x9096
#define GL_TRANSPOSE_AFFINE_3D_NV                   0x9098
#define GL_UTF8_NV                                  0x909A
#define GL_UTF16_NV                                 0x909B
#define GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV        0x909C
#define GL_PATH_COMMAND_COUNT_NV                     0x909D
#define GL_PATH_COORD_COUNT_NV                       0x909E
#define GL_PATH_DASH_ARRAY_COUNT_NV                  0x909F
#define GL_PATH_COMPUTED_LENGTH_NV                   0x90A0
#define GL_PATH_FILL_BOUNDING_BOX_NV                 0x90A1
#define GL_PATH_STROKE_BOUNDING_BOX_NV               0x90A2
#define GL_SQUARE_NV                                0x90A3
#define GL_ROUND_NV                                 0x90A4
#define GL_TRIANGULAR_NV                            0x90A5
#define GL_BEVEL_NV                                 0x90A6
#define GL_MITER_REVERT_NV                          0x90A7
#define GL_MITER_TRUNCATE_NV                        0x90A8
#define GL_SKIP_MISSING_GLYPH_NV                     0x90A9
#define GL_USE_MISSING_GLYPH_NV                      0x90AA
#define GL_PATH_ERROR_POSITION_NV                    0x90AB
#define GL_PATH_FOG_GEN_MODE_NV                      0x90AC
#define GL_ACCUM_ADJACENT_PAIRS_NV                   0x90AD
#define GL_ADJACENT_PAIRS_NV                         0x90AE
#define GL_FIRST_TO_REST_NV                         0x90AF
#define GL_PATH_GEN_MODE_NV                         0x90B0
#define GL_PATH_GEN_COEFF_NV                        0x90B1
#define GL_PATH_GEN_COLOR_FORMAT_NV                  0x90B2
#define GL_PATH_GEN_COMPONENTS_NV                    0x90B3
#define GL_PATH_DASH_OFFSET_RESET_NV                 0x90B4
#define GL_MOVE_TO_RESETS_NV                         0x90B5
#define GL_MOVE_TO_CONTINUES_NV                      0x90B6
#define GL_PATH_STENCIL_FUNC_NV                      0x90B7
#define GL_PATH_STENCIL_REF_NV                       0x90B8
#define GL_PATH_STENCIL_VALUE_MASK_NV                0x90B9
#define GL_PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV      0x90BD
#define GL_PATH_STENCIL_DEPTH_OFFSET_UNITS_NV       0x90BE
#define GL_PATH_COVER_DEPTH_FUNC_NV                  0x90BF
#define GL_FONT_GLYPHS_AVAILABLE_NV                  0x9368
#define GL_FONT_TARGET_UNAVAILABLE_NV                0x9369
#define GL_FONT_UNAVAILABLE_NV                       0x936A
#define GL_FONT_UNINTELLIGIBLE_NV                    0x936B
#define GL_STANDARD_FONT_FORMAT_NV                   0x936C
#define GL_FRAGMENT_INPUT_NV                         0x936D
#define GL_FONT_X_MIN_BOUNDS_BIT_NV                  0x00010000
#define GL_FONT_Y_MIN_BOUNDS_BIT_NV                  0x00020000
#define GL_FONT_X_MAX_BOUNDS_BIT_NV                  0x00040000
#define GL_FONT_Y_MAX_BOUNDS_BIT_NV                  0x00080000
#define GL_FONT_UNITS_PER_EM_BIT_NV                   0x00100000
#define GL_FONT_ASCENDER_BIT_NV                       0x00200000
#define GL_FONT_DESCENDER_BIT_NV                      0x00400000
#define GL_FONT_HEIGHT_BIT_NV                         0x00800000
#define GL_FONT_MAX_ADVANCE_WIDTH_BIT_NV              0x01000000
#define GL_FONT_MAX_ADVANCE_HEIGHT_BIT_NV             0x02000000
#define GL_FONT_UNDERLINE_POSITION_BIT_NV             0x04000000
#define GL_FONT_UNDERLINE_THICKNESS_BIT_NV            0x08000000
#define GL_FONT_HAS_KERNING_BIT_NV                     0x10000000
#define GL_FONT_NUM_GLYPH_INDICES_BIT_NV               0x20000000


// Path Rendering Shared Edge
#define GL_SHARED_EDGE_NV                       0xC0

// Pixel Buffer Object
#define GL_PIXEL_PACK_BUFFER_NV                 0x88EB
#define GL_PIXEL_UNPACK_BUFFER_NV               0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING_NV         0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING_NV       0x88EF

// Pixel Data Range
#define GL_WRITE_PIXEL_DATA_RANGE_NV            0x8878
#define GL_READ_PIXEL_DATA_RANGE_NV             0x8879
#define GL_WRITE_PIXEL_DATA_RANGE_LENGTH_NV     0x887A
#define GL_READ_PIXEL_DATA_RANGE_LENGTH_NV      0x887B
#define GL_WRITE_PIXEL_DATA_RANGE_POINTER_NV    0x887C
#define GL_READ_PIXEL_DATA_RANGE_POINTER_NV     0x887D

// Point Sprite
#define GL_POINT_SPRITE_NV                      0x8861
#define GL_COORD_REPLACE_NV                     0x8862
#define GL_POINT_SPRITE_R_MODE_NV               0x8863

// Polygon Mode
#define GL_POLYGON_MODE_NV                      0x0B40
#define GL_POINT_NV                            0x1B00
#define GL_LINE_NV                             0x1B01
#define GL_FILL_NV                             0x1B02
#define GL_POLYGON_OFFSET_POINT_NV              0x2A01
#define GL_POLYGON_OFFSET_LINE_NV               0x2A02

// Present Video
#define GL_FRAME_NV                            0x8E26
#define GL_FIELDS_NV                           0x8E27
#define GL_CURRENT_TIME_NV                     0x8E28
#define GL_NUM_FILL_STREAMS_NV                 0x8E29
#define GL_PRESENT_TIME_NV                     0x8E2A
#define GL_PRESENT_DURATION_NV                 0x8E2B

// Primitive Restart
#define GL_PRIMITIVE_RESTART_NV                0x8558
#define GL_PRIMITIVE_RESTART_INDEX_NV          0x8559

// Register Combiners
#define GL_REGISTER_COMBINERS_NV               0x8522
#define GL_VARIABLE_A_NV                       0x8523
#define GL_VARIABLE_B_NV                       0x8524
#define GL_VARIABLE_C_NV                       0x8525
#define GL_VARIABLE_D_NV                       0x8526
#define GL_VARIABLE_E_NV                       0x8527
#define GL_VARIABLE_F_NV                       0x8528
#define GL_VARIABLE_G_NV                       0x8529
#define GL_CONSTANT_COLOR0_NV                  0x852A
#define GL_CONSTANT_COLOR1_NV                  0x852B
#define GL_PRIMARY_COLOR_NV                    0x852C
#define GL_SECONDARY_COLOR_NV                  0x852D
#define GL_SPARE0_NV                          0x852E
#define GL_SPARE1_NV                          0x852F
#define GL_DISCARD_NV                         0x8530
#define GL_E_TIMES_F_NV                       0x8531
#define GL_SPARE0_PLUS_SECONDARY_COLOR_NV     0x8532
#define GL_UNSIGNED_IDENTITY_NV               0x8536
#define GL_UNSIGNED_INVERT_NV                 0x8537
#define GL_EXPAND_NORMAL_NV                   0x8538
#define GL_EXPAND_NEGATE_NV                   0x8539
#define GL_HALF_BIAS_NORMAL_NV                0x853A
#define GL_HALF_BIAS_NEGATE_NV                0x853B
#define GL_SIGNED_IDENTITY_NV                 0x853C
#define GL_SIGNED_NEGATE_NV                   0x853D
#define GL_SCALE_BY_TWO_NV                    0x853E
#define GL_SCALE_BY_FOUR_NV                   0x853F
#define GL_SCALE_BY_ONE_HALF_NV               0x8540
#define GL_BIAS_BY_NEGATIVE_ONE_HALF_NV      0x8541
#define GL_COMBINER_INPUT_NV                  0x8542
#define GL_COMBINER_MAPPING_NV                0x8543
#define GL_COMBINER_COMPONENT_USAGE_NV       0x8544
#define GL_COMBINER_AB_DOT_PRODUCT_NV        0x8545
#define GL_COMBINER_CD_DOT_PRODUCT_NV        0x8546
#define GL_COMBINER_MUX_SUM_NV                0x8547
#define GL_COMBINER_SCALE_NV                  0x8548
#define GL_COMBINER_BIAS_NV                   0x8549
#define GL_COMBINER_AB_OUTPUT_NV              0x854A
#define GL_COMBINER_CD_OUTPUT_NV              0x854B
#define GL_COMBINER_SUM_OUTPUT_NV             0x854C
#define GL_MAX_GENERAL_COMBINERS_NV           0x854D
#define GL_NUM_GENERAL_COMBINERS_NV           0x854E
#define GL_COLOR_SUM_CLAMP_NV                 0x854F
#define GL_COMBINER0_NV                       0x8550
#define GL_COMBINER1_NV                       0x8551
#define GL_COMBINER2_NV                       0x8552
#define GL_COMBINER3_NV                       0x8553
#define GL_COMBINER4_NV                       0x8554
#define GL_COMBINER5_NV                       0x8555
#define GL_COMBINER6_NV                       0x8556
#define GL_COMBINER7_NV                       0x8557

// Register Combiners 2
#define GL_PER_STAGE_CONSTANTS_NV             0x8535

// Robustness Video Memory Purge
#define GL_EGL_GENERATE_RESET_ON_VIDEO_MEMORY_PURGE_NV 0x334C
#define GL_PURGED_CONTEXT_RESET_NV             0x92BB


// sRGB formats
#define GL_ETC1_SRGB8_NV                      0x88EE
#define GL_SRGB8_NV                          0x8C41
#define GL_SLUMINANCE_ALPHA_NV               0x8C44
#define GL_SLUMINANCE8_ALPHA8_NV             0x8C45
#define GL_SLUMINANCE_NV                     0x8C46
#define GL_SLUMINANCE8_NV                    0x8C47
#define GL_COMPRESSED_SRGB_S3TC_DXT1_NV     0x8C4C
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV 0x8C4D
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV 0x8C4E
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV 0x8C4F

// Sample locations
#define GL_SAMPLE_LOCATION_NV                0x8E50
#define GL_SAMPLE_LOCATION_SUBPIXEL_BITS_NV 0x933D
#define GL_SAMPLE_LOCATION_PIXEL_GRID_WIDTH_NV 0x933E
#define GL_SAMPLE_LOCATION_PIXEL_GRID_HEIGHT_NV 0x933F
#define GL_PROGRAMMABLE_SAMPLE_LOCATION_TABLE_SIZE_NV 0x9340
#define GL_PROGRAMMABLE_SAMPLE_LOCATION_NV  0x9341
#define GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#define GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343

// Shader buffer load
#define GL_BUFFER_GPU_ADDRESS_NV             0x8F1D
#define GL_GPU_ADDRESS_NV                    0x8F34
#define GL_MAX_SHADER_BUFFER_ADDRESS_NV     0x8F35

// Shader thread group
#define GL_WARP_SIZE_NV                     0x9339
#define GL_WARPS_PER_SM_NV                  0x933A
#define GL_SM_COUNT_NV                      0x933B

// Shadow samplers array
#define GL_SAMPLER_2D_ARRAY_SHADOW_NV      0x8DC4

// Shadow samplers cube
#define GL_SAMPLER_CUBE_SHADOW_NV          0x8DC5

// Tessellation program 5
#define GL_MAX_PROGRAM_PATCH_ATTRIBS_NV    0x86D8
#define GL_TESS_CONTROL_PROGRAM_NV         0x891E
#define GL_TESS_EVALUATION_PROGRAM_NV      0x891F
#define GL_TESS_CONTROL_PROGRAM_PARAMETER_BUFFER_NV 0x8C74
#define GL_TESS_EVALUATION_PROGRAM_PARAMETER_BUFFER_NV 0x8C75

// Texgen emboss
#define GL_EMBOSS_LIGHT_NV                  0x855D
#define GL_EMBOSS_CONSTANT_NV               0x855E
#define GL_EMBOSS_MAP_NV                   0x855F

// Texgen reflection
#define GL_NORMAL_MAP_NV                   0x8511
#define GL_REFLECTION_MAP_NV               0x8512

// Texture array
#define GL_UNPACK_SKIP_IMAGES_NV           0x806D
#define GL_UNPACK_IMAGE_HEIGHT_NV          0x806E
#define GL_MAX_ARRAY_TEXTURE_LAYERS_NV     0x88FF
#define GL_TEXTURE_2D_ARRAY_NV             0x8C1A
#define GL_TEXTURE_BINDING_2D_ARRAY_NV     0x8C1D
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_NV 0x8CD4
#define GL_SAMPLER_2D_ARRAY_NV             0x8DC1

// Texture border clamp
#define GL_TEXTURE_BORDER_COLOR_NV         0x1004
#define GL_CLAMP_TO_BORDER_NV              0x812D

// Texture compression LATC
#define GL_COMPRESSED_LUMINANCE_LATC1_NV          0x8C70
#define GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_NV   0x8C71
#define GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_NV    0x8C72
#define GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_NV 0x8C73

// Texture compression S3TC
#define GL_COMPRESSED_RGB_S3TC_DXT1_NV      0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_NV     0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_NV     0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_NV     0x83F3

// Texture env combine4
#define GL_COMBINE4_NV                      0x8503
#define GL_SOURCE3_RGB_NV                   0x8583
#define GL_SOURCE3_ALPHA_NV                 0x858B
#define GL_OPERAND3_RGB_NV                  0x8593
#define GL_OPERAND3_ALPHA_NV                0x859B

// Texture expand normal
#define GL_TEXTURE_UNSIGNED_REMAP_MODE_NV  0x888F

// Texture multisample
#define GL_TEXTURE_COVERAGE_SAMPLES_NV     0x9045
#define GL_TEXTURE_COLOR_SAMPLES_NV        0x9046

// Texture rectangle
#define GL_TEXTURE_RECTANGLE_NV            0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_NV    0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_NV      0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_NV   0x84F8

// Texture shader
#define GL_OFFSET_TEXTURE_RECTANGLE_NV          0x864C
#define GL_OFFSET_TEXTURE_RECTANGLE_SCALE_NV    0x864D
#define GL_DOT_PRODUCT_TEXTURE_RECTANGLE_NV     0x864E
#define GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV 0x86D9
#define GL_UNSIGNED_INT_S8_S8_8_8_NV             0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV         0x86DB
#define GL_DSDT_MAG_INTENSITY_NV                  0x86DC
#define GL_SHADER_CONSISTENT_NV                   0x86DD
#define GL_TEXTURE_SHADER_NV                       0x86DE
#define GL_SHADER_OPERATION_NV                     0x86DF
#define GL_CULL_MODES_NV                           0x86E0
#define GL_OFFSET_TEXTURE_2D_MATRIX_NV             0x86E1
#define GL_OFFSET_TEXTURE_MATRIX_NV                 0x86E1
#define GL_OFFSET_TEXTURE_2D_SCALE_NV                0x86E2
#define GL_OFFSET_TEXTURE_SCALE_NV                    0x86E2
#define GL_OFFSET_TEXTURE_2D_BIAS_NV                   0x86E3
#define GL_OFFSET_TEXTURE_BIAS_NV                         0x86E3
#define GL_PREVIOUS_TEXTURE_INPUT_NV                     0x86E4
#define GL_CONST_EYE_NV                                     0x86E5
#define GL_PASS_THROUGH_NV                                0x86E6
#define GL_CULL_FRAGMENT_NV                               0x86E7
#define GL_OFFSET_TEXTURE_2D_NV                          0x86E8
#define GL_DEPENDENT_AR_TEXTURE_2D_NV                0x86E9
#define GL_DEPENDENT_GB_TEXTURE_2D_NV                 0x86EA
#define GL_DOT_PRODUCT_NV                                  0x86EC
#define GL_DOT_PRODUCT_DEPTH_REPLACE_NV             0x86ED
#define GL_DOT_PRODUCT_TEXTURE_2D_NV                  0x86EE
#define GL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV       0x86F0
#define GL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV         0x86F1
#define GL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV          0x86F2
#define GL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV 0x86F3
#define GL_HILO_NV                                             0x86F4
#define GL_DSDT_NV                                             0x86F5
#define GL_DSDT_MAG_NV                                      0x86F6
#define GL_DSDT_MAG_VIB_NV                                0x86F7
#define GL_HILO16_NV                                          0x86F8
#define GL_SIGNED_HILO_NV                                  0x86F9
#define GL_SIGNED_HILO16_NV                               0x86FA
#define GL_SIGNED_RGBA_NV                                    0x86FB
#define GL_SIGNED_RGBA8_NV                                  0x86FC
#define GL_SIGNED_RGB_NV                                     0x86FE
#define GL_SIGNED_RGB8_NV                                    0x86FF
#define GL_SIGNED_LUMINANCE_NV                            0x8701
#define GL_SIGNED_LUMINANCE8_NV                          0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV                  0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV                0x8704
#define GL_SIGNED_ALPHA_NV                                    0x8705
#define GL_SIGNED_ALPHA8_NV                                  0x8706
#define GL_SIGNED_INTENSITY_NV                               0x8707
#define GL_SIGNED_INTENSITY8_NV                             0x8708
#define GL_DSDT8_NV                                             0x8709
#define GL_DSDT8_MAG8_NV                                    0x870A
#define GL_DSDT8_MAG8_INTENSITY8_NV                      0x870B
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV                 0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV             0x870D
#define GL_HI_SCALE_NV                                         0x870E
#define GL_LO_SCALE_NV                                         0x870F
#define GL_DS_SCALE_NV                                         0x8710
#define GL_DT_SCALE_NV                                         0x8711
#define GL_MAGNITUDE_SCALE_NV                             0x8712
#define GL_VIBRANCE_SCALE_NV                                 0x8713
#define GL_HI_BIAS_NV                                          0x8714
#define GL_LO_BIAS_NV                                          0x8715
#define GL_DS_BIAS_NV                                          0x8716
#define GL_DT_BIAS_NV                                          0x8717
#define GL_MAGNITUDE_BIAS_NV                               0x8718
#define GL_VIBRANCE_BIAS_NV                                 0x8719
#define GL_TEXTURE_BORDER_VALUES_NV                     0x871A
#define GL_TEXTURE_HI_SIZE_NV                               0x871B
#define GL_TEXTURE_LO_SIZE_NV                               0x871C
#define GL_TEXTURE_DS_SIZE_NV                               0x871D
#define GL_TEXTURE_DT_SIZE_NV                               0x871E
#define GL_TEXTURE_MAG_SIZE_NV                             0x871F


// texture_shader2
#define GL_UNSIGNED_INT_S8_S8_8_8_NV           0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV       0x86DB
#define GL_DSDT_MAG_INTENSITY_NV                0x86DC
#define GL_DOT_PRODUCT_TEXTURE_3D_NV            0x86EF
#define GL_HILO_NV                              0x86F4
#define GL_DSDT_NV                              0x86F5
#define GL_DSDT_MAG_NV                          0x86F6
#define GL_DSDT_MAG_VIB_NV                      0x86F7
#define GL_HILO16_NV                           0x86F8
#define GL_SIGNED_HILO_NV                       0x86F9
#define GL_SIGNED_HILO16_NV                    0x86FA
#define GL_SIGNED_RGBA_NV                       0x86FB
#define GL_SIGNED_RGBA8_NV                      0x86FC
#define GL_SIGNED_RGB_NV                        0x86FE
#define GL_SIGNED_RGB8_NV                       0x86FF
#define GL_SIGNED_LUMINANCE_NV                  0x8701
#define GL_SIGNED_LUMINANCE8_NV                 0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV            0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV          0x8704
#define GL_SIGNED_ALPHA_NV                      0x8705
#define GL_SIGNED_ALPHA8_NV                     0x8706
#define GL_SIGNED_INTENSITY_NV                  0x8707
#define GL_SIGNED_INTENSITY8_NV                 0x8708
#define GL_DSDT8_NV                            0x8709
#define GL_DSDT8_MAG8_NV                       0x870A
#define GL_DSDT8_MAG8_INTENSITY8_NV            0x870B
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV         0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV       0x870D

// texture_shader3
#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_NV     0x8850
#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_SCALE_NV 0x8851
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_NV 0x8852
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_SCALE_NV 0x8853
#define GL_OFFSET_HILO_TEXTURE_2D_NV            0x8854
#define GL_OFFSET_HILO_TEXTURE_RECTANGLE_NV     0x8855
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_2D_NV 0x8856
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_RECTANGLE_NV 0x8857
#define GL_DEPENDENT_HILO_TEXTURE_2D_NV         0x8858
#define GL_DEPENDENT_RGB_TEXTURE_3D_NV          0x8859
#define GL_DEPENDENT_RGB_TEXTURE_CUBE_MAP_NV    0x885A
#define GL_DOT_PRODUCT_PASS_THROUGH_NV           0x885B
#define GL_DOT_PRODUCT_TEXTURE_1D_NV             0x885C
#define GL_DOT_PRODUCT_AFFINE_DEPTH_REPLACE_NV  0x885D
#define GL_HILO8_NV                             0x885E
#define GL_SIGNED_HILO8_NV                      0x885F
#define GL_FORCE_BLUE_TO_ONE_NV                 0x8860

// transform_feedback
#define GL_BACK_PRIMARY_COLOR_NV                 0x8C77
#define GL_BACK_SECONDARY_COLOR_NV               0x8C78
#define GL_TEXTURE_COORD_NV                      0x8C79
#define GL_CLIP_DISTANCE_NV                      0x8C7A
#define GL_VERTEX_ID_NV                          0x8C7B
#define GL_PRIMITIVE_ID_NV                       0x8C7C
#define GL_GENERIC_ATTRIB_NV                     0x8C7D
#define GL_TRANSFORM_FEEDBACK_ATTRIBS_NV        0x8C7E
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE_NV    0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_NV 0x8C80
#define GL_ACTIVE_VARYINGS_NV                    0x8C81
#define GL_ACTIVE_VARYING_MAX_LENGTH_NV         0x8C82
#define GL_TRANSFORM_FEEDBACK_VARYINGS_NV       0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START_NV   0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE_NV    0x8C85
#define GL_TRANSFORM_FEEDBACK_RECORD_NV         0x8C86
#define GL_PRIMITIVES_GENERATED_NV               0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_NV 0x8C88
#define GL_RASTERIZER_DISCARD_NV                 0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_NV 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_NV 0x8C8B
#define GL_INTERLEAVED_ATTRIBS_NV                0x8C8C
#define GL_SEPARATE_ATTRIBS_NV                   0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER_NV         0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING_NV 0x8C8F

// transform_feedback2
#define GL_TRANSFORM_FEEDBACK_NV                 0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED_NV  0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE_NV  0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING_NV        0x8E25

// uniform_buffer_unified_memory
#define GL_UNIFORM_BUFFER_UNIFIED_NV             0x936E
#define GL_UNIFORM_BUFFER_ADDRESS_NV             0x936F
#define GL_UNIFORM_BUFFER_LENGTH_NV              0x9370

// vdpau_interop
#define GL_SURFACE_STATE_NV                      0x86EB
#define GL_SURFACE_REGISTERED_NV                 0x86FD
#define GL_SURFACE_MAPPED_NV                     0x8700
#define GL_WRITE_DISCARD_NV                      0x88BE

// vertex_array_range
#define GL_VERTEX_ARRAY_RANGE_NV                 0x851D
#define GL_VERTEX_ARRAY_RANGE_LENGTH_NV          0x851E
#define GL_VERTEX_ARRAY_RANGE_VALID_NV           0x851F
#define GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV     0x8520
#define GL_VERTEX_ARRAY_RANGE_POINTER_NV         0x8521

// vertex_array_range2
#define GL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV   0x8533


// vertex_attrib_integer_64bit
#define GL_INT64_NV                            0x140E
#define GL_UNSIGNED_INT64_NV                   0x140F

// vertex_buffer_unified_memory
#define GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV     0x8F1E
#define GL_ELEMENT_ARRAY_UNIFIED_NV            0x8F1F
#define GL_VERTEX_ATTRIB_ARRAY_ADDRESS_NV     0x8F20
#define GL_VERTEX_ARRAY_ADDRESS_NV             0x8F21
#define GL_NORMAL_ARRAY_ADDRESS_NV             0x8F22
#define GL_COLOR_ARRAY_ADDRESS_NV              0x8F23
#define GL_INDEX_ARRAY_ADDRESS_NV              0x8F24
#define GL_TEXTURE_COORD_ARRAY_ADDRESS_NV     0x8F25
#define GL_EDGE_FLAG_ARRAY_ADDRESS_NV          0x8F26
#define GL_SECONDARY_COLOR_ARRAY_ADDRESS_NV    0x8F27
#define GL_FOG_COORD_ARRAY_ADDRESS_NV          0x8F28
#define GL_ELEMENT_ARRAY_ADDRESS_NV            0x8F29
#define GL_VERTEX_ATTRIB_ARRAY_LENGTH_NV      0x8F2A
#define GL_VERTEX_ARRAY_LENGTH_NV              0x8F2B
#define GL_NORMAL_ARRAY_LENGTH_NV              0x8F2C
#define GL_COLOR_ARRAY_LENGTH_NV               0x8F2D
#define GL_INDEX_ARRAY_LENGTH_NV               0x8F2E
#define GL_TEXTURE_COORD_ARRAY_LENGTH_NV      0x8F2F
#define GL_EDGE_FLAG_ARRAY_LENGTH_NV           0x8F30
#define GL_SECONDARY_COLOR_ARRAY_LENGTH_NV     0x8F31
#define GL_FOG_COORD_ARRAY_LENGTH_NV           0x8F32
#define GL_ELEMENT_ARRAY_LENGTH_NV             0x8F33
#define GL_DRAW_INDIRECT_UNIFIED_NV            0x8F40
#define GL_DRAW_INDIRECT_ADDRESS_NV            0x8F41
#define GL_DRAW_INDIRECT_LENGTH_NV             0x8F42

// vertex_program
#define GL_VERTEX_PROGRAM_NV                   0x8620
#define GL_VERTEX_STATE_PROGRAM_NV             0x8621
#define GL_ATTRIB_ARRAY_SIZE_NV                0x8623
#define GL_ATTRIB_ARRAY_STRIDE_NV              0x8624
#define GL_ATTRIB_ARRAY_TYPE_NV                0x8625
#define GL_CURRENT_ATTRIB_NV                   0x8626
#define GL_PROGRAM_LENGTH_NV                   0x8627
#define GL_PROGRAM_STRING_NV                   0x8628
#define GL_MODELVIEW_PROJECTION_NV             0x8629
#define GL_IDENTITY_NV                        0x862A
#define GL_INVERSE_NV                         0x862B
#define GL_TRANSPOSE_NV                       0x862C
#define GL_INVERSE_TRANSPOSE_NV               0x862D
#define GL_MAX_TRACK_MATRIX_STACK_DEPTH_NV    0x862E
#define GL_MAX_TRACK_MATRICES_NV              0x862F
#define GL_MATRIX0_NV                         0x8630
#define GL_MATRIX1_NV                         0x8631
#define GL_MATRIX2_NV                         0x8632
#define GL_MATRIX3_NV                         0x8633
#define GL_MATRIX4_NV                         0x8634
#define GL_MATRIX5_NV                         0x8635
#define GL_MATRIX6_NV                         0x8636
#define GL_MATRIX7_NV                         0x8637
#define GL_CURRENT_MATRIX_STACK_DEPTH_NV      0x8640
#define GL_CURRENT_MATRIX_NV                   0x8641
#define GL_VERTEX_PROGRAM_POINT_SIZE_NV       0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_NV          0x8643
#define GL_PROGRAM_PARAMETER_NV               0x8644
#define GL_ATTRIB_ARRAY_POINTER_NV            0x8645
#define GL_PROGRAM_TARGET_NV                  0x8646
#define GL_PROGRAM_RESIDENT_NV                0x8647
#define GL_TRACK_MATRIX_NV                    0x8648
#define GL_TRACK_MATRIX_TRANSFORM_NV          0x8649
#define GL_VERTEX_PROGRAM_BINDING_NV          0x864A
#define GL_PROGRAM_ERROR_POSITION_NV          0x864B
#define GL_VERTEX_ATTRIB_ARRAY0_NV            0x8650
#define GL_VERTEX_ATTRIB_ARRAY1_NV            0x8651
#define GL_VERTEX_ATTRIB_ARRAY2_NV            0x8652
#define GL_VERTEX_ATTRIB_ARRAY3_NV            0x8653
#define GL_VERTEX_ATTRIB_ARRAY4_NV            0x8654
#define GL_VERTEX_ATTRIB_ARRAY5_NV            0x8655
#define GL_VERTEX_ATTRIB_ARRAY6_NV            0x8656
#define GL_VERTEX_ATTRIB_ARRAY7_NV            0x8657
#define GL_VERTEX_ATTRIB_ARRAY8_NV            0x8658
#define GL_VERTEX_ATTRIB_ARRAY9_NV            0x8659
#define GL_VERTEX_ATTRIB_ARRAY10_NV           0x865A
#define GL_VERTEX_ATTRIB_ARRAY11_NV           0x865B
#define GL_VERTEX_ATTRIB_ARRAY12_NV           0x865C
#define GL_VERTEX_ATTRIB_ARRAY13_NV           0x865D
#define GL_VERTEX_ATTRIB_ARRAY14_NV           0x865E
#define GL_VERTEX_ATTRIB_ARRAY15_NV           0x865F
#define GL_MAP1_VERTEX_ATTRIB0_4_NV           0x8660
#define GL_MAP1_VERTEX_ATTRIB1_4_NV           0x8661
#define GL_MAP1_VERTEX_ATTRIB2_4_NV           0x8662
#define GL_MAP1_VERTEX_ATTRIB3_4_NV           0x8663
#define GL_MAP1_VERTEX_ATTRIB4_4_NV           0x8664
#define GL_MAP1_VERTEX_ATTRIB5_4_NV           0x8665
#define GL_MAP1_VERTEX_ATTRIB6_4_NV           0x8666
#define GL_MAP1_VERTEX_ATTRIB7_4_NV           0x8667
#define GL_MAP1_VERTEX_ATTRIB8_4_NV           0x8668
#define GL_MAP1_VERTEX_ATTRIB9_4_NV           0x8669
#define GL_MAP1_VERTEX_ATTRIB10_4_NV          0x866A
#define GL_MAP1_VERTEX_ATTRIB11_4_NV          0x866B
#define GL_MAP1_VERTEX_ATTRIB12_4_NV          0x866C
#define GL_MAP1_VERTEX_ATTRIB13_4_NV          0x866D
#define GL_MAP1_VERTEX_ATTRIB14_4_NV          0x866E
#define GL_MAP1_VERTEX_ATTRIB15_4_NV          0x866F
#define GL_MAP2_VERTEX_ATTRIB0_4_NV           0x8670
#define GL_MAP2_VERTEX_ATTRIB1_4_NV           0x8671
#define GL_MAP2_VERTEX_ATTRIB2_4_NV           0x8672
#define GL_MAP2_VERTEX_ATTRIB3_4_NV           0x8673
#define GL_MAP2_VERTEX_ATTRIB4_4_NV           0x8674
#define GL_MAP2_VERTEX_ATTRIB5_4_NV           0x8675
#define GL_MAP2_VERTEX_ATTRIB6_4_NV           0x8676
#define GL_MAP2_VERTEX_ATTRIB7_4_NV           0x8677
#define GL_MAP2_VERTEX_ATTRIB8_4_NV           0x8678
#define GL_MAP2_VERTEX_ATTRIB9_4_NV           0x8679
#define GL_MAP2_VERTEX_ATTRIB10_4_NV          0x867A
#define GL_MAP2_VERTEX_ATTRIB11_4_NV          0x867B
#define GL_MAP2_VERTEX_ATTRIB12_4_NV          0x867C
#define GL_MAP2_VERTEX_ATTRIB13_4_NV          0x867D
#define GL_MAP2_VERTEX_ATTRIB14_4_NV          0x867E
#define GL_MAP2_VERTEX_ATTRIB15_4_NV          0x867F

// vertex_program2_option
#define GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV   0x88F4
#define GL_MAX_PROGRAM_CALL_DEPTH_NV           0x88F5

// vertex_program3
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB 0x8B4C

// vertex_program4
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER_NV     0x88FD

// video_capture
#define GL_VIDEO_BUFFER_NV                     0x9020
#define GL_VIDEO_BUFFER_BINDING_NV             0x9021
#define GL_FIELD_UPPER_NV                      0x9022
#define GL_FIELD_LOWER_NV                      0x9023
#define GL_NUM_VIDEO_CAPTURE_STREAMS_NV       0x9024
#define GL_NEXT_VIDEO_CAPTURE_BUFFER_STATUS_NV 0x9025
#define GL_VIDEO_CAPTURE_TO_422_SUPPORTED_NV  0x9026
#define GL_LAST_VIDEO_CAPTURE_STATUS_NV       0x9027
#define GL_VIDEO_BUFFER_PITCH_NV               0x9028
#define GL_VIDEO_COLOR_CONVERSION_MATRIX_NV   0x9029
#define GL_VIDEO_COLOR_CONVERSION_MAX_NV      0x902A
#define GL_VIDEO_COLOR_CONVERSION_MIN_NV      0x902B
#define GL_VIDEO_COLOR_CONVERSION_OFFSET_NV   0x902C
#define GL_VIDEO_BUFFER_INTERNAL_FORMAT_NV    0x902D
#define GL_PARTIAL_SUCCESS_NV                  0x902E
#define GL_SUCCESS_NV                         0x902F
#define GL_FAILURE_NV                         0x9030
#define GL_YCBYCR8_422_NV                     0x9031
#define GL_YCBAYCR8A_4224_NV                  0x9032
#define GL_Z6Y10Z6CB10Z6Y10Z6CR10_422_NV     0x9033
#define GL_Z6Y10Z6CB10Z6A10Z6Y10Z6CR10Z6A10_4224_NV 0x9034
#define GL_Z4Y12Z4CB12Z4Y12Z4CR12_422_NV     0x9035
#define GL_Z4Y12Z4CB12Z4A12Z4Y12Z4CR12Z4A12_4224_NV 0x9036
#define GL_Z4Y12Z4CB12Z4CR12_444_NV           0x9037
#define GL_VIDEO_CAPTURE_FRAME_WIDTH_NV       0x9038
#define GL_VIDEO_CAPTURE_FRAME_HEIGHT_NV      0x9039
#define GL_VIDEO_CAPTURE_FIELD_UPPER_HEIGHT_NV 0x903A
#define GL_VIDEO_CAPTURE_FIELD_LOWER_HEIGHT_NV 0x903B
#define GL_VIDEO_CAPTURE_SURFACE_ORIGIN_NV    0x903C

// viewport_array
#define GL_DEPTH_RANGE                         0x0B70
#define GL_VIEWPORT                           0x0BA2
#define GL_SCISSOR_BOX                       0x0C10
#define GL_SCISSOR_TEST                      0x0C11
#define GL_MAX_VIEWPORTS_NV                  0x825B
#define GL_VIEWPORT_SUBPIXEL_BITS_NV         0x825C
#define GL_VIEWPORT_BOUNDS_RANGE_NV          0x825D
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX_NV 0x825F

// viewport_swizzle
#define GL_VIEWPORT_SWIZZLE_POSITIVE_X_NV    0x9350
#define GL_VIEWPORT_SWIZZLE_NEGATIVE_X_NV    0x9351
#define GL_VIEWPORT_SWIZZLE_POSITIVE_Y_NV    0x9352
#define GL_VIEWPORT_SWIZZLE_NEGATIVE_Y_NV    0x9353
#define GL_VIEWPORT_SWIZZLE_POSITIVE_Z_NV    0x9354
#define GL_VIEWPORT_SWIZZLE_NEGATIVE_Z_NV    0x9355
#define GL_VIEWPORT_SWIZZLE_POSITIVE_W_NV    0x9356
#define GL_VIEWPORT_SWIZZLE_NEGATIVE_W_NV    0x9357
#define GL_VIEWPORT_SWIZZLE_X_NV              0x9358
#define GL_VIEWPORT_SWIZZLE_Y_NV              0x9359
#define GL_VIEWPORT_SWIZZLE_Z_NV              0x935A
#define GL_VIEWPORT_SWIZZLE_W_NV              0x935B


	//3dvision_settings
	inline void(*glStereoParameterfNV) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glStereoParameteriNV) (GLenum pname, GLint param) = nullptr;
#define NV_3dvision_settings 1

	//EGL_stream_consumer_external
#define NV_EGL_stream_consumer_external 1

	//alpha_to_coverage_dither_control
#define NV_alpha_to_coverage_dither_control 1

	//bgr
#define NV_bgr 1

	//bindless_multi_draw_indirect
	inline void(*glMultiDrawArraysIndirectBindlessNV) (GLenum mode, const void* indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount) = nullptr;
	inline void(*glMultiDrawElementsIndirectBindlessNV) (GLenum mode, GLenum type, const void* indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount) = nullptr;
#define NV_bindless_multi_draw_indirect 1

	//bindless_multi_draw_indirect_count
	inline void(*glMultiDrawArraysIndirectBindlessCountNV) (GLenum mode, const void* indirect, GLintptr drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount) = nullptr;
	inline void(*glMultiDrawElementsIndirectBindlessCountNV) (GLenum mode, GLenum type, const void* indirect, GLintptr drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount) = nullptr;
#define NV_bindless_multi_draw_indirect_count 1

	//bindless_texture
	inline GLuint64(*glGetImageHandleNV) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format) = nullptr;
	inline GLuint64(*glGetTextureHandleNV) (GLuint texture) = nullptr;
	inline GLuint64(*glGetTextureSamplerHandleNV) (GLuint texture, GLuint sampler) = nullptr;
	inline GLboolean(*glIsImageHandleResidentNV) (GLuint64 handle) = nullptr;
	inline GLboolean(*glIsTextureHandleResidentNV) (GLuint64 handle) = nullptr;
	inline void(*glMakeImageHandleNonResidentNV) (GLuint64 handle) = nullptr;
	inline void(*glMakeImageHandleResidentNV) (GLuint64 handle, GLenum access) = nullptr;
	inline void(*glMakeTextureHandleNonResidentNV) (GLuint64 handle) = nullptr;
	inline void(*glMakeTextureHandleResidentNV) (GLuint64 handle) = nullptr;
	inline void(*glProgramUniformHandleui64NV) (GLuint program, GLint location, GLuint64 value) = nullptr;
	inline void(*glProgramUniformHandleui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64* values) = nullptr;
	inline void(*glUniformHandleui64NV) (GLint location, GLuint64 value) = nullptr;
	inline void(*glUniformHandleui64vNV) (GLint location, GLsizei count, const GLuint64* value) = nullptr;
#define NV_bindless_texture 1

	//blend_equation_advanced
	inline void(*glBlendBarrierNV) (void) = nullptr;
	inline void(*glBlendParameteriNV) (GLenum pname, GLint value) = nullptr;
#define NV_blend_equation_advanced 1

	//blend_equation_advanced_coherent
#define NV_blend_equation_advanced_coherent 1

	//blend_minmax_factor
#define NV_blend_minmax_factor 1

	//blend_square
#define NV_blend_square 1

	//clip_space_w_scaling
	inline void(*glViewportPositionWScaleNV) (GLuint index, GLfloat xcoeff, GLfloat ycoeff) = nullptr;
#define NV_clip_space_w_scaling 1

	//command_list
	inline void(*glCallCommandListNV) (GLuint list) = nullptr;
	inline void(*glCommandListSegmentsNV) (GLuint list, GLuint segments) = nullptr;
	inline void(*glCompileCommandListNV) (GLuint list) = nullptr;
	inline void(*glCreateCommandListsNV) (GLsizei n, GLuint* lists) = nullptr;
	inline void(*glCreateStatesNV) (GLsizei n, GLuint* states) = nullptr;
	inline void(*glDeleteCommandListsNV) (GLsizei n, const GLuint* lists) = nullptr;
	inline void(*glDeleteStatesNV) (GLsizei n, const GLuint* states) = nullptr;
	inline void(*glDrawCommandsAddressNV) (GLenum primitiveMode, const GLuint64* indirects, const GLsizei* sizes, GLuint count) = nullptr;
	inline void(*glDrawCommandsNV) (GLenum primitiveMode, GLuint buffer, const GLintptr* indirects, const GLsizei* sizes, GLuint count) = nullptr;
	inline void(*glDrawCommandsStatesAddressNV) (const GLuint64* indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count) = nullptr;
	inline void(*glDrawCommandsStatesNV) (GLuint buffer, const GLintptr* indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count) = nullptr;
	inline GLuint(*glGetCommandHeaderNV) (GLenum tokenID, GLuint size) = nullptr;
	inline GLushort(*glGetStageIndexNV) (GLenum shadertype) = nullptr;
	inline GLboolean(*glIsCommandListNV) (GLuint list) = nullptr;
	inline GLboolean(*glIsStateNV) (GLuint state) = nullptr;
	inline void(*glListDrawCommandsStatesClientNV) (GLuint list, GLuint segment, const void** indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count) = nullptr;
	inline void(*glStateCaptureNV) (GLuint state, GLenum mode) = nullptr;
#define NV_command_list 1

	//compute_program5
#define NV_compute_program5 1

	//conditional_render
	inline void(*glBeginConditionalRenderNV) (GLuint id, GLenum mode) = nullptr;
	inline void(*glEndConditionalRenderNV) (void) = nullptr;
#define NV_conditional_render 1

	//conservative_raster
	inline void(*glSubpixelPrecisionBiasNV) (GLuint xbits, GLuint ybits) = nullptr;
#define NV_conservative_raster 1

	//conservative_raster_dilate
	inline void(*glConservativeRasterParameterfNV) (GLenum pname, GLfloat value) = nullptr;
#define NV_conservative_raster_dilate 1

	//conservative_raster_pre_snap_triangles
	inline void(*glConservativeRasterParameteriNV) (GLenum pname, GLint param) = nullptr;
#define NV_conservative_raster_pre_snap_triangles 1

	//copy_buffer
	inline void(*glCopyBufferSubDataNV) (GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size) = nullptr;
#define NV_copy_buffer 1

	//copy_depth_to_color
#define NV_copy_depth_to_color 1

	//copy_image
	inline void(*glCopyImageSubDataNV) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth) = nullptr;
#define NV_copy_image 1

	//deep_texture3D
#define NV_deep_texture3D 1

	//depth_buffer_float
	inline void(*glClearDepthdNV) (GLdouble depth) = nullptr;
	inline void(*glDepthBoundsdNV) (GLdouble zmin, GLdouble zmax) = nullptr;
	inline void(*glDepthRangedNV) (GLdouble zNear, GLdouble zFar) = nullptr;
#define NV_depth_buffer_float 1

	//depth_clamp
#define NV_depth_clamp 1

	//depth_range_unclamped
#define NV_depth_range_unclamped 1

	//draw_buffers
	inline void(*glDrawBuffersNV) (GLsizei n, const GLenum * bufs) = nullptr;
#define NV_draw_buffers 1

	//draw_instanced
	inline void(*glDrawArraysInstancedNV) (GLenum mode, GLint first, GLsizei count, GLsizei primcount) = nullptr;
	inline void(*glDrawElementsInstancedNV) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) = nullptr;
#define NV_draw_instanced 1

	//draw_texture
	inline void(*glDrawTextureNV) (GLuint texture, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1) = nullptr;
#define NV_draw_texture 1

	//draw_vulkan_image
	typedef void(APIENTRY * GLVULKANPROCNV)(void);

	inline void(*glDrawVkImageNV) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1) = nullptr;
	inline GLVULKANPROCNV(*glGetVkProcAddrNV) (const GLchar* name) = nullptr;
	inline void(*glSignalVkFenceNV) (GLuint64 vkFence) = nullptr;
	inline void(*glSignalVkSemaphoreNV) (GLuint64 vkSemaphore) = nullptr;
	inline void(*glWaitVkSemaphoreNV) (GLuint64 vkSemaphore) = nullptr;
#define NV_draw_vulkan_image 1

	//evaluators
	inline void(*glEvalMapsNV) (GLenum target, GLenum mode) = nullptr;
	inline void(*glGetMapAttribParameterfvNV) (GLenum target, GLuint index, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetMapAttribParameterivNV) (GLenum target, GLuint index, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetMapControlPointsNV) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, void* points) = nullptr;
	inline void(*glGetMapParameterfvNV) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetMapParameterivNV) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glMapControlPointsNV) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const void* points) = nullptr;
	inline void(*glMapParameterfvNV) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glMapParameterivNV) (GLenum target, GLenum pname, const GLint* params) = nullptr;
#define NV_evaluators 1

	//explicit_attrib_location
#define NV_explicit_attrib_location 1

	//explicit_multisample
	inline void(*glGetMultisamplefvNV) (GLenum pname, GLuint index, GLfloat * val) = nullptr;
	inline void(*glSampleMaskIndexedNV) (GLuint index, GLbitfield mask) = nullptr;
	inline void(*glTexRenderbufferNV) (GLenum target, GLuint renderbuffer) = nullptr;
#define NV_explicit_multisample 1

	//fbo_color_attachments
#define NV_fbo_color_attachments 1

	//fence
	inline void(*glDeleteFencesNV) (GLsizei n, const GLuint * fences) = nullptr;
	inline void(*glFinishFenceNV) (GLuint fence) = nullptr;
	inline void(*glGenFencesNV) (GLsizei n, GLuint* fences) = nullptr;
	inline void(*glGetFenceivNV) (GLuint fence, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsFenceNV) (GLuint fence) = nullptr;
	inline void(*glSetFenceNV) (GLuint fence, GLenum condition) = nullptr;
	inline GLboolean(*glTestFenceNV) (GLuint fence) = nullptr;
#define NV_fence 1

	//fill_rectangle
#define NV_fill_rectangle 1

	//float_buffer
#define NV_float_buffer 1

	//fog_distance
#define NV_fog_distance 1

	//fragment_coverage_to_color
	inline void(*glFragmentCoverageColorNV) (GLuint color) = nullptr;
#define NV_fragment_coverage_to_color 1

	//fragment_program
	inline void(*glGetProgramNamedParameterdvNV) (GLuint id, GLsizei len, const GLubyte * name, GLdouble * params) = nullptr;
	inline void(*glGetProgramNamedParameterfvNV) (GLuint id, GLsizei len, const GLubyte* name, GLfloat* params) = nullptr;
	inline void(*glProgramNamedParameter4dNV) (GLuint id, GLsizei len, const GLubyte* name, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glProgramNamedParameter4dvNV) (GLuint id, GLsizei len, const GLubyte* name, const GLdouble v[]) = nullptr;
	inline void(*glProgramNamedParameter4fNV) (GLuint id, GLsizei len, const GLubyte* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glProgramNamedParameter4fvNV) (GLuint id, GLsizei len, const GLubyte* name, const GLfloat v[]) = nullptr;
#define NV_fragment_program 1

	//fragment_program2
#define NV_fragment_program2 1

	//fragment_program4
#define NV_fragment_program4 1

	//fragment_program_option
#define NV_fragment_program_option 1

	//fragment_shader_interlock
#define NV_fragment_shader_interlock 1

	//framebuffer_blit
	inline void(*glBlitFramebufferNV) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
#define NV_framebuffer_blit 1

	//framebuffer_mixed_samples
#define NV_framebuffer_mixed_samples 1

	//framebuffer_multisample
	inline void(*glRenderbufferStorageMultisampleNV) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
#define NV_framebuffer_multisample 1

	//framebuffer_multisample_coverage
	inline void(*glRenderbufferStorageMultisampleCoverageNV) (GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
#define NV_framebuffer_multisample_coverage 1

	//generate_mipmap_sRGB
#define NV_generate_mipmap_sRGB 1

	//geometry_program4
	inline void(*glProgramVertexLimitNV) (GLenum target, GLint limit) = nullptr;
#define NV_geometry_program4 1

	//geometry_shader4
#define NV_geometry_shader4 1

	//geometry_shader_passthrough
#define NV_geometry_shader_passthrough 1

	//gpu_multicast
	inline void(*glMulticastBarrierNV) (void) = nullptr;
	inline void(*glMulticastBlitFramebufferNV) (GLuint srcGpu, GLuint dstGpu, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = nullptr;
	inline void(*glMulticastBufferSubDataNV) (GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) = nullptr;
	inline void(*glMulticastCopyBufferSubDataNV) (GLuint readGpu, GLbitfield writeGpuMask, GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) = nullptr;
	inline void(*glMulticastCopyImageSubDataNV) (GLuint srcGpu, GLbitfield dstGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) = nullptr;
	inline void(*glMulticastFramebufferSampleLocationsfvNV) (GLuint gpu, GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v) = nullptr;
	inline void(*glMulticastGetQueryObjecti64vNV) (GLuint gpu, GLuint id, GLenum pname, GLint64* params) = nullptr;
	inline void(*glMulticastGetQueryObjectivNV) (GLuint gpu, GLuint id, GLenum pname, GLint* params) = nullptr;
	inline void(*glMulticastGetQueryObjectui64vNV) (GLuint gpu, GLuint id, GLenum pname, GLuint64* params) = nullptr;
	inline void(*glMulticastGetQueryObjectuivNV) (GLuint gpu, GLuint id, GLenum pname, GLuint* params) = nullptr;
	inline void(*glMulticastWaitSyncNV) (GLuint signalGpu, GLbitfield waitGpuMask) = nullptr;
	inline void(*glRenderGpuMaskNV) (GLbitfield mask) = nullptr;
#define NV_gpu_multicast 1

	//gpu_program4
	inline void(*glProgramEnvParameterI4iNV) (GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) = nullptr;
	inline void(*glProgramEnvParameterI4ivNV) (GLenum target, GLuint index, const GLint* params) = nullptr;
	inline void(*glProgramEnvParameterI4uiNV) (GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
	inline void(*glProgramEnvParameterI4uivNV) (GLenum target, GLuint index, const GLuint* params) = nullptr;
	inline void(*glProgramEnvParametersI4ivNV) (GLenum target, GLuint index, GLsizei count, const GLint* params) = nullptr;
	inline void(*glProgramEnvParametersI4uivNV) (GLenum target, GLuint index, GLsizei count, const GLuint* params) = nullptr;
	inline void(*glProgramLocalParameterI4iNV) (GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) = nullptr;
	inline void(*glProgramLocalParameterI4ivNV) (GLenum target, GLuint index, const GLint* params) = nullptr;
	inline void(*glProgramLocalParameterI4uiNV) (GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = nullptr;
	inline void(*glProgramLocalParameterI4uivNV) (GLenum target, GLuint index, const GLuint* params) = nullptr;
	inline void(*glProgramLocalParametersI4ivNV) (GLenum target, GLuint index, GLsizei count, const GLint* params) = nullptr;
	inline void(*glProgramLocalParametersI4uivNV) (GLenum target, GLuint index, GLsizei count, const GLuint* params) = nullptr;
#define NV_gpu_program4 1

	//gpu_program5
#define NV_gpu_program5 1

	//gpu_program5_mem_extended
#define NV_gpu_program5_mem_extended 1

	//gpu_program_fp64
#define NV_gpu_program_fp64 1

	//gpu_shader5
	inline void(*glGetUniformi64vNV) (GLuint program, GLint location, GLint64EXT * params) = nullptr;
	inline void(*glGetUniformui64vNV) (GLuint program, GLint location, GLuint64EXT* params) = nullptr;
	inline void(*glProgramUniform1i64NV) (GLuint program, GLint location, GLint64EXT x) = nullptr;
	inline void(*glProgramUniform1i64vNV) (GLuint program, GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
	inline void(*glProgramUniform1ui64NV) (GLuint program, GLint location, GLuint64EXT x) = nullptr;
	inline void(*glProgramUniform1ui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
	inline void(*glProgramUniform2i64NV) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y) = nullptr;
	inline void(*glProgramUniform2i64vNV) (GLuint program, GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
	inline void(*glProgramUniform2ui64NV) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y) = nullptr;
	inline void(*glProgramUniform2ui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
	inline void(*glProgramUniform3i64NV) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z) = nullptr;
	inline void(*glProgramUniform3i64vNV) (GLuint program, GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
	inline void(*glProgramUniform3ui64NV) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z) = nullptr;
	inline void(*glProgramUniform3ui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
	inline void(*glProgramUniform4i64NV) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w) = nullptr;
	inline void(*glProgramUniform4i64vNV) (GLuint program, GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
	inline void(*glProgramUniform4ui64NV) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) = nullptr;
	inline void(*glProgramUniform4ui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
	inline void(*glUniform1i64NV) (GLint location, GLint64EXT x) = nullptr;
	inline void(*glUniform1i64vNV) (GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
	inline void(*glUniform1ui64NV) (GLint location, GLuint64EXT x) = nullptr;
	inline void(*glUniform1ui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
	inline void(*glUniform2i64NV) (GLint location, GLint64EXT x, GLint64EXT y) = nullptr;
	inline void(*glUniform2i64vNV) (GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
	inline void(*glUniform2ui64NV) (GLint location, GLuint64EXT x, GLuint64EXT y) = nullptr;
	inline void(*glUniform2ui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
	inline void(*glUniform3i64NV) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z) = nullptr;
	inline void(*glUniform3i64vNV) (GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
	inline void(*glUniform3ui64NV) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z) = nullptr;
	inline void(*glUniform3ui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
	inline void(*glUniform4i64NV) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w) = nullptr;
	inline void(*glUniform4i64vNV) (GLint location, GLsizei count, const GLint64EXT* value) = nullptr;
	inline void(*glUniform4ui64NV) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) = nullptr;
	inline void(*glUniform4ui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
#define NV_gpu_shader5 1

	//half_float
	inline void(*glColor3hNV) (GLhalf red, GLhalf green, GLhalf blue) = nullptr;
	inline void(*glColor3hvNV) (const GLhalf* v) = nullptr;
	inline void(*glColor4hNV) (GLhalf red, GLhalf green, GLhalf blue, GLhalf alpha) = nullptr;
	inline void(*glColor4hvNV) (const GLhalf* v) = nullptr;
	inline void(*glFogCoordhNV) (GLhalf fog) = nullptr;
	inline void(*glFogCoordhvNV) (const GLhalf* fog) = nullptr;
	inline void(*glMultiTexCoord1hNV) (GLenum target, GLhalf s) = nullptr;
	inline void(*glMultiTexCoord1hvNV) (GLenum target, const GLhalf* v) = nullptr;
	inline void(*glMultiTexCoord2hNV) (GLenum target, GLhalf s, GLhalf t) = nullptr;
	inline void(*glMultiTexCoord2hvNV) (GLenum target, const GLhalf* v) = nullptr;
	inline void(*glMultiTexCoord3hNV) (GLenum target, GLhalf s, GLhalf t, GLhalf r) = nullptr;
	inline void(*glMultiTexCoord3hvNV) (GLenum target, const GLhalf* v) = nullptr;
	inline void(*glMultiTexCoord4hNV) (GLenum target, GLhalf s, GLhalf t, GLhalf r, GLhalf q) = nullptr;
	inline void(*glMultiTexCoord4hvNV) (GLenum target, const GLhalf* v) = nullptr;
	inline void(*glNormal3hNV) (GLhalf nx, GLhalf ny, GLhalf nz) = nullptr;
	inline void(*glNormal3hvNV) (const GLhalf* v) = nullptr;
	inline void(*glSecondaryColor3hNV) (GLhalf red, GLhalf green, GLhalf blue) = nullptr;
	inline void(*glSecondaryColor3hvNV) (const GLhalf* v) = nullptr;
	inline void(*glTexCoord1hNV) (GLhalf s) = nullptr;
	inline void(*glTexCoord1hvNV) (const GLhalf* v) = nullptr;
	inline void(*glTexCoord2hNV) (GLhalf s, GLhalf t) = nullptr;
	inline void(*glTexCoord2hvNV) (const GLhalf* v) = nullptr;
	inline void(*glTexCoord3hNV) (GLhalf s, GLhalf t, GLhalf r) = nullptr;
	inline void(*glTexCoord3hvNV) (const GLhalf* v) = nullptr;
	inline void(*glTexCoord4hNV) (GLhalf s, GLhalf t, GLhalf r, GLhalf q) = nullptr;
	inline void(*glTexCoord4hvNV) (const GLhalf* v) = nullptr;
	inline void(*glVertex2hNV) (GLhalf x, GLhalf y) = nullptr;
	inline void(*glVertex2hvNV) (const GLhalf* v) = nullptr;
	inline void(*glVertex3hNV) (GLhalf x, GLhalf y, GLhalf z) = nullptr;
	inline void(*glVertex3hvNV) (const GLhalf* v) = nullptr;
	inline void(*glVertex4hNV) (GLhalf x, GLhalf y, GLhalf z, GLhalf w) = nullptr;
	inline void(*glVertex4hvNV) (const GLhalf* v) = nullptr;
	inline void(*glVertexAttrib1hNV) (GLuint index, GLhalf x) = nullptr;
	inline void(*glVertexAttrib1hvNV) (GLuint index, const GLhalf* v) = nullptr;
	inline void(*glVertexAttrib2hNV) (GLuint index, GLhalf x, GLhalf y) = nullptr;
	inline void(*glVertexAttrib2hvNV) (GLuint index, const GLhalf* v) = nullptr;
	inline void(*glVertexAttrib3hNV) (GLuint index, GLhalf x, GLhalf y, GLhalf z) = nullptr;
	inline void(*glVertexAttrib3hvNV) (GLuint index, const GLhalf* v) = nullptr;
	inline void(*glVertexAttrib4hNV) (GLuint index, GLhalf x, GLhalf y, GLhalf z, GLhalf w) = nullptr;
	inline void(*glVertexAttrib4hvNV) (GLuint index, const GLhalf* v) = nullptr;
	inline void(*glVertexAttribs1hvNV) (GLuint index, GLsizei n, const GLhalf* v) = nullptr;
	inline void(*glVertexAttribs2hvNV) (GLuint index, GLsizei n, const GLhalf* v) = nullptr;
	inline void(*glVertexAttribs3hvNV) (GLuint index, GLsizei n, const GLhalf* v) = nullptr;
	inline void(*glVertexAttribs4hvNV) (GLuint index, GLsizei n, const GLhalf* v) = nullptr;
	inline void(*glVertexWeighthNV) (GLhalf weight) = nullptr;
	inline void(*glVertexWeighthvNV) (const GLhalf* weight) = nullptr;

	//half_float
#define NV_half_float 1

	//image_formats
#define NV_image_formats 1

	//instanced_arrays
	inline void(*glVertexAttribDivisorNV) (GLuint index, GLuint divisor) = nullptr;
#define NV_instanced_arrays 1

	//internalformat_sample_query
	inline void(*glGetInternalformatSampleivNV) (GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei bufSize, GLint * params) = nullptr;
#define NV_internalformat_sample_query 1

	//light_max_exponent
#define NV_light_max_exponent 1

	//multisample_coverage
#define NV_multisample_coverage 1

	//multisample_filter_hint
#define NV_multisample_filter_hint 1

	//non_square_matrices
	inline void(*glUniformMatrix2x3fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) = nullptr;
	inline void(*glUniformMatrix2x4fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glUniformMatrix3x2fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glUniformMatrix3x4fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glUniformMatrix4x2fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
	inline void(*glUniformMatrix4x3fvNV) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
#define NV_non_square_matrices 1

	//occlusion_query
	inline void(*glBeginOcclusionQueryNV) (GLuint id) = nullptr;
	inline void(*glDeleteOcclusionQueriesNV) (GLsizei n, const GLuint* ids) = nullptr;
	inline void(*glEndOcclusionQueryNV) (void) = nullptr;
	inline void(*glGenOcclusionQueriesNV) (GLsizei n, GLuint* ids) = nullptr;
	inline void(*glGetOcclusionQueryivNV) (GLuint id, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetOcclusionQueryuivNV) (GLuint id, GLenum pname, GLuint* params) = nullptr;
	inline GLboolean(*glIsOcclusionQueryNV) (GLuint id) = nullptr;
#define NV_occlusion_query 1

	//pack_subimage
#define NV_pack_subimage 1

	//packed_depth_stencil
#define NV_packed_depth_stencil 1

	//packed_float
#define NV_packed_float 1

	//packed_float_linear
#define NV_packed_float_linear 1

	//parameter_buffer_object
	inline void(*glProgramBufferParametersIivNV) (GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLint * params) = nullptr;
	inline void(*glProgramBufferParametersIuivNV) (GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLuint* params) = nullptr;
	inline void(*glProgramBufferParametersfvNV) (GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLfloat* params) = nullptr;
#define NV_parameter_buffer_object 1

	//parameter_buffer_object2
#define NV_parameter_buffer_object2 1

	//path_rendering
	inline void(*glCopyPathNV) (GLuint resultPath, GLuint srcPath) = nullptr;
	inline void(*glCoverFillPathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) = nullptr;
	inline void(*glCoverFillPathNV) (GLuint path, GLenum coverMode) = nullptr;
	inline void(*glCoverStrokePathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) = nullptr;
	inline void(*glCoverStrokePathNV) (GLuint path, GLenum coverMode) = nullptr;
	inline void(*glDeletePathsNV) (GLuint path, GLsizei range) = nullptr;
	inline GLuint(*glGenPathsNV) (GLsizei range) = nullptr;
	inline void(*glGetPathColorGenfvNV) (GLenum color, GLenum pname, GLfloat* value) = nullptr;
	inline void(*glGetPathColorGenivNV) (GLenum color, GLenum pname, GLint* value) = nullptr;
	inline void(*glGetPathCommandsNV) (GLuint path, GLubyte* commands) = nullptr;
	inline void(*glGetPathCoordsNV) (GLuint path, GLfloat* coords) = nullptr;
	inline void(*glGetPathDashArrayNV) (GLuint path, GLfloat* dashArray) = nullptr;
	inline GLfloat(*glGetPathLengthNV) (GLuint path, GLsizei startSegment, GLsizei numSegments) = nullptr;
	inline void(*glGetPathMetricRangeNV) (GLbitfield metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride, GLfloat* metrics) = nullptr;
	inline void(*glGetPathMetricsNV) (GLbitfield metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLsizei stride, GLfloat* metrics) = nullptr;
	inline void(*glGetPathParameterfvNV) (GLuint path, GLenum pname, GLfloat* value) = nullptr;
	inline void(*glGetPathParameterivNV) (GLuint path, GLenum pname, GLint* value) = nullptr;
	inline void(*glGetPathSpacingNV) (GLenum pathListMode, GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat* returnedSpacing) = nullptr;
	inline void(*glGetPathTexGenfvNV) (GLenum texCoordSet, GLenum pname, GLfloat* value) = nullptr;
	inline void(*glGetPathTexGenivNV) (GLenum texCoordSet, GLenum pname, GLint* value) = nullptr;
	inline void(*glGetProgramResourcefvNV) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLfloat* params) = nullptr;
	inline void(*glInterpolatePathsNV) (GLuint resultPath, GLuint pathA, GLuint pathB, GLfloat weight) = nullptr;
	inline GLboolean(*glIsPathNV) (GLuint path) = nullptr;
	inline GLboolean(*glIsPointInFillPathNV) (GLuint path, GLuint mask, GLfloat x, GLfloat y) = nullptr;
	inline GLboolean(*glIsPointInStrokePathNV) (GLuint path, GLfloat x, GLfloat y) = nullptr;
	inline void(*glMatrixLoad3x2fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glMatrixLoad3x3fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glMatrixLoadTranspose3x3fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glMatrixMult3x2fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glMatrixMult3x3fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glMatrixMultTranspose3x3fNV) (GLenum matrixMode, const GLfloat* m) = nullptr;
	inline void(*glPathColorGenNV) (GLenum color, GLenum genMode, GLenum colorFormat, const GLfloat* coeffs) = nullptr;
	inline void(*glPathCommandsNV) (GLuint path, GLsizei numCommands, const GLubyte* commands, GLsizei numCoords, GLenum coordType, const void* coords) = nullptr;
	inline void(*glPathCoordsNV) (GLuint path, GLsizei numCoords, GLenum coordType, const void* coords) = nullptr;
	inline void(*glPathCoverDepthFuncNV) (GLenum zfunc) = nullptr;
	inline void(*glPathDashArrayNV) (GLuint path, GLsizei dashCount, const GLfloat* dashArray) = nullptr;
	inline void(*glPathFogGenNV) (GLenum genMode) = nullptr;
	inline GLenum(*glPathGlyphIndexArrayNV) (GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale) = nullptr;
	inline GLenum(*glPathGlyphIndexRangeNV) (GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint baseAndCount[2]) = nullptr;
	inline void(*glPathGlyphRangeNV) (GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei numGlyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale) = nullptr;
	inline void(*glPathGlyphsNV) (GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLsizei numGlyphs, GLenum type, const void* charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale) = nullptr;
	inline GLenum(*glPathMemoryGlyphIndexArrayNV) (GLuint firstPathName, GLenum fontTarget, GLsizeiptr fontSize, const void* fontData, GLsizei faceIndex, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale) = nullptr;
	inline void(*glPathParameterfNV) (GLuint path, GLenum pname, GLfloat value) = nullptr;
	inline void(*glPathParameterfvNV) (GLuint path, GLenum pname, const GLfloat* value) = nullptr;
	inline void(*glPathParameteriNV) (GLuint path, GLenum pname, GLint value) = nullptr;
	inline void(*glPathParameterivNV) (GLuint path, GLenum pname, const GLint* value) = nullptr;
	inline void(*glPathStencilDepthOffsetNV) (GLfloat factor, GLfloat units) = nullptr;
	inline void(*glPathStencilFuncNV) (GLenum func, GLint ref, GLuint mask) = nullptr;
	inline void(*glPathStringNV) (GLuint path, GLenum format, GLsizei length, const void* pathString) = nullptr;
	inline void(*glPathSubCommandsNV) (GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte* commands, GLsizei numCoords, GLenum coordType, const void* coords) = nullptr;
	inline void(*glPathSubCoordsNV) (GLuint path, GLsizei coordStart, GLsizei numCoords, GLenum coordType, const void* coords) = nullptr;
	inline void(*glPathTexGenNV) (GLenum texCoordSet, GLenum genMode, GLint components, const GLfloat* coeffs) = nullptr;
	inline GLboolean(*glPointAlongPathNV) (GLuint path, GLsizei startSegment, GLsizei numSegments, GLfloat distance, GLfloat* x, GLfloat* y, GLfloat* tangentX, GLfloat* tangentY) = nullptr;
	inline void(*glProgramPathFragmentInputGenNV) (GLuint program, GLint location, GLenum genMode, GLint components, const GLfloat* coeffs) = nullptr;
	inline void(*glStencilFillPathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, const GLfloat* transformValues) = nullptr;
	inline void(*glStencilFillPathNV) (GLuint path, GLenum fillMode, GLuint mask) = nullptr;
	inline void(*glStencilStrokePathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, const GLfloat* transformValues) = nullptr;
	inline void(*glStencilStrokePathNV) (GLuint path, GLint reference, GLuint mask) = nullptr;
	inline void(*glStencilThenCoverFillPathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) = nullptr;
	inline void(*glStencilThenCoverFillPathNV) (GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode) = nullptr;
	inline void(*glStencilThenCoverStrokePathInstancedNV) (GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat* transformValues) = nullptr;
	inline void(*glStencilThenCoverStrokePathNV) (GLuint path, GLint reference, GLuint mask, GLenum coverMode) = nullptr;
	inline void(*glTransformPathNV) (GLuint resultPath, GLuint srcPath, GLenum transformType, const GLfloat* transformValues) = nullptr;
	inline void(*glWeightPathsNV) (GLuint resultPath, GLsizei numPaths, const GLuint paths[], const GLfloat weights[]) = nullptr;
#define NV_path_rendering 1

	//path_rendering_shared_edge
#define NV_path_rendering_shared_edge 1

	//pixel_buffer_object
#define NV_pixel_buffer_object 1

	//pixel_data_range
	inline void(*glFlushPixelDataRangeNV) (GLenum target) = nullptr;
	inline void(*glPixelDataRangeNV) (GLenum target, GLsizei length, void* pointer) = nullptr;
#define NV_pixel_data_range 1

	//platform_binary
#define NV_platform_binary 1

	//point_sprite
	inline void(*glPointParameteriNV) (GLenum pname, GLint param) = nullptr;
	inline void(*glPointParameterivNV) (GLenum pname, const GLint* params) = nullptr;
#define NV_point_sprite 1

	//polygon_mode
	inline void(*glPolygonModeNV) (GLenum face, GLenum mode) = nullptr;
#define NV_polygon_mode 1

	//present_video
	inline void(*glGetVideoi64vNV) (GLuint video_slot, GLenum pname, GLint64EXT * params) = nullptr;
	inline void(*glGetVideoivNV) (GLuint video_slot, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetVideoui64vNV) (GLuint video_slot, GLenum pname, GLuint64EXT* params) = nullptr;
	inline void(*glGetVideouivNV) (GLuint video_slot, GLenum pname, GLuint* params) = nullptr;
	inline void(*glPresentFrameDualFillNV) (GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3) = nullptr;
	inline void(*glPresentFrameKeyedNV) (GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1) = nullptr;
#define NV_present_video 1

	//primitive_restart
	inline void(*glPrimitiveRestartIndexNV) (GLuint index) = nullptr;
	inline void(*glPrimitiveRestartNV) (void) = nullptr;
#define NV_primitive_restart 1

	//read_depth
#define NV_read_depth 1

	//read_depth_stencil
#define NV_read_depth_stencil 1

	//read_stencil
#define NV_read_stencil 1

	//register_combiners
	inline void(*glCombinerInputNV) (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage) = nullptr;
	inline void(*glCombinerOutputNV) (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum) = nullptr;
	inline void(*glCombinerParameterfNV) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glCombinerParameterfvNV) (GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glCombinerParameteriNV) (GLenum pname, GLint param) = nullptr;
	inline void(*glCombinerParameterivNV) (GLenum pname, const GLint* params) = nullptr;
	inline void(*glFinalCombinerInputNV) (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage) = nullptr;
	inline void(*glGetCombinerInputParameterfvNV) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetCombinerInputParameterivNV) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetCombinerOutputParameterfvNV) (GLenum stage, GLenum portion, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetCombinerOutputParameterivNV) (GLenum stage, GLenum portion, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetFinalCombinerInputParameterfvNV) (GLenum variable, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetFinalCombinerInputParameterivNV) (GLenum variable, GLenum pname, GLint* params) = nullptr;
#define NV_register_combiners 1

	//register_combiners2
	inline void(*glCombinerStageParameterfvNV) (GLenum stage, GLenum pname, const GLfloat * params) = nullptr;
	inline void(*glGetCombinerStageParameterfvNV) (GLenum stage, GLenum pname, GLfloat* params) = nullptr;
#define NV_register_combiners2 1

	//robustness_video_memory_purge
#define NV_robustness_video_memory_purge 1

	//sRGB_formats
#define NV_sRGB_formats 1

	//sample_locations
	inline void(*glFramebufferSampleLocationsfvNV) (GLenum target, GLuint start, GLsizei count, const GLfloat * v) = nullptr;
	inline void(*glNamedFramebufferSampleLocationsfvNV) (GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v) = nullptr;
#define NV_sample_locations 1

	//sample_mask_override_coverage
#define NV_sample_mask_override_coverage 1

	//shader_atomic_counters
#define NV_shader_atomic_counters 1

	//shader_atomic_float
#define NV_shader_atomic_float 1

	//shader_atomic_float64
#define NV_shader_atomic_float64 1

	//shader_atomic_fp16_vector
#define NV_shader_atomic_fp16_vector 1

	//shader_atomic_int64
#define NV_shader_atomic_int64 1

	//shader_buffer_load
	inline void(*glGetBufferParameterui64vNV) (GLenum target, GLenum pname, GLuint64EXT * params) = nullptr;
	inline void(*glGetIntegerui64vNV) (GLenum value, GLuint64EXT* result) = nullptr;
	inline void(*glGetNamedBufferParameterui64vNV) (GLuint buffer, GLenum pname, GLuint64EXT* params) = nullptr;
	inline GLboolean(*glIsBufferResidentNV) (GLenum target) = nullptr;
	inline GLboolean(*glIsNamedBufferResidentNV) (GLuint buffer) = nullptr;
	inline void(*glMakeBufferNonResidentNV) (GLenum target) = nullptr;
	inline void(*glMakeBufferResidentNV) (GLenum target, GLenum access) = nullptr;
	inline void(*glMakeNamedBufferNonResidentNV) (GLuint buffer) = nullptr;
	inline void(*glMakeNamedBufferResidentNV) (GLuint buffer, GLenum access) = nullptr;
	inline void(*glProgramUniformui64NV) (GLuint program, GLint location, GLuint64EXT value) = nullptr;
	inline void(*glProgramUniformui64vNV) (GLuint program, GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
	inline void(*glUniformui64NV) (GLint location, GLuint64EXT value) = nullptr;
	inline void(*glUniformui64vNV) (GLint location, GLsizei count, const GLuint64EXT* value) = nullptr;
#define NV_shader_buffer_load 1

	//shader_noperspective_interpolation
#define NV_shader_noperspective_interpolation 1

	//shader_storage_buffer_object
#define NV_shader_storage_buffer_object 1

	//shader_thread_group
#define NV_shader_thread_group 1

	//shader_thread_shuffle
#define NV_shader_thread_shuffle 1

	//shadow_samplers_array
#define NV_shadow_samplers_array 1

	//shadow_samplers_cube
#define NV_shadow_samplers_cube 1

	//stereo_view_rendering
#define NV_stereo_view_rendering 1

	//tessellation_program5
#define NV_tessellation_program5 1

	//texgen_emboss
#define NV_texgen_emboss 1

	//texgen_reflection
#define NV_texgen_reflection 1

	//texture_array
	inline void(*glCompressedTexImage3DNV) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCompressedTexSubImage3DNV) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) = nullptr;
	inline void(*glCopyTexSubImage3DNV) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	inline void(*glFramebufferTextureLayerNV) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) = nullptr;
	inline void(*glTexImage3DNV) (GLenum target, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTexSubImage3DNV) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) = nullptr;
#define NV_texture_array 1

	//texture_barrier
	inline void(*glTextureBarrierNV) (void) = nullptr;
#define NV_texture_barrier 1

	//texture_border_clamp
#define NV_texture_border_clamp 1

	//texture_compression_latc
#define NV_texture_compression_latc 1

	//texture_compression_s3tc
#define NV_texture_compression_s3tc 1

	//texture_compression_s3tc_update
#define NV_texture_compression_s3tc_update 1

	//texture_compression_vtc
#define NV_texture_compression_vtc 1

	//texture_env_combine4
#define NV_texture_env_combine4 1

	//texture_expand_normal
#define NV_texture_expand_normal 1

	//texture_multisample
	inline void(*glTexImage2DMultisampleCoverageNV) (GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) = nullptr;
	inline void(*glTexImage3DMultisampleCoverageNV) (GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) = nullptr;
	inline void(*glTextureImage2DMultisampleCoverageNV) (GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) = nullptr;
	inline void(*glTextureImage2DMultisampleNV) (GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) = nullptr;
	inline void(*glTextureImage3DMultisampleCoverageNV) (GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) = nullptr;
	inline void(*glTextureImage3DMultisampleNV) (GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) = nullptr;
#define NV_texture_multisample 1

	//texture_npot_2D_mipmap
#define NV_texture_npot_2D_mipmap 1

	//texture_rectangle
#define NV_texture_rectangle 1

	//texture_rectangle_compressed
#define NV_texture_rectangle_compressed 1

	//texture_shader
#define NV_texture_shader 1

	//texture_shader2
#define NV_texture_shader2 1

	//texture_shader3
#define NV_texture_shader3 1

	//transform_feedback
	inline void(*glActiveVaryingNV) (GLuint program, const GLchar * name) = nullptr;
	inline void(*glBeginTransformFeedbackNV) (GLenum primitiveMode) = nullptr;
	inline void(*glBindBufferBaseNV) (GLenum target, GLuint index, GLuint buffer) = nullptr;
	inline void(*glBindBufferOffsetNV) (GLenum target, GLuint index, GLuint buffer, GLintptr offset) = nullptr;
	inline void(*glBindBufferRangeNV) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) = nullptr;
	inline void(*glEndTransformFeedbackNV) (void) = nullptr;
	inline void(*glGetActiveVaryingNV) (GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) = nullptr;
	inline void(*glGetTransformFeedbackVaryingNV) (GLuint program, GLuint index, GLint* location) = nullptr;
	inline GLint(*glGetVaryingLocationNV) (GLuint program, const GLchar* name) = nullptr;
	inline void(*glTransformFeedbackAttribsNV) (GLuint count, const GLint* attribs, GLenum bufferMode) = nullptr;
	inline void(*glTransformFeedbackVaryingsNV) (GLuint program, GLsizei count, const GLint* locations, GLenum bufferMode) = nullptr;
#define NV_transform_feedback 1

	//transform_feedback2
	inline void(*glBindTransformFeedbackNV) (GLenum target, GLuint id) = nullptr;
	inline void(*glDeleteTransformFeedbacksNV) (GLsizei n, const GLuint* ids) = nullptr;
	inline void(*glDrawTransformFeedbackNV) (GLenum mode, GLuint id) = nullptr;
	inline void(*glGenTransformFeedbacksNV) (GLsizei n, GLuint* ids) = nullptr;
	inline GLboolean(*glIsTransformFeedbackNV) (GLuint id) = nullptr;
	inline void(*glPauseTransformFeedbackNV) (void) = nullptr;
	inline void(*glResumeTransformFeedbackNV) (void) = nullptr;
#define NV_transform_feedback2 1

	//uniform_buffer_unified_memory
#define NV_uniform_buffer_unified_memory 1

	//vdpau_interop
	inline void(*glVDPAUFiniNV) (void) = nullptr;
	inline void(*glVDPAUGetSurfaceivNV) (GLvdpauSurfaceNV surface, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) = nullptr;
	inline void(*glVDPAUInitNV) (const void* vdpDevice, const void* getProcAddress) = nullptr;
	inline void(*glVDPAUIsSurfaceNV) (GLvdpauSurfaceNV surface) = nullptr;
	inline void(*glVDPAUMapSurfacesNV) (GLsizei numSurfaces, const GLvdpauSurfaceNV* surfaces) = nullptr;
	inline GLvdpauSurfaceNV(*glVDPAURegisterOutputSurfaceNV) (const void* vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint* textureNames) = nullptr;
	inline GLvdpauSurfaceNV(*glVDPAURegisterVideoSurfaceNV) (const void* vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint* textureNames) = nullptr;
	inline void(*glVDPAUSurfaceAccessNV) (GLvdpauSurfaceNV surface, GLenum access) = nullptr;
	inline void(*glVDPAUUnmapSurfacesNV) (GLsizei numSurface, const GLvdpauSurfaceNV* surfaces) = nullptr;
	inline void(*glVDPAUUnregisterSurfaceNV) (GLvdpauSurfaceNV surface) = nullptr;
#define NV_vdpau_interop 1

	//vertex_array_range
	inline void(*glFlushVertexArrayRangeNV) (void) = nullptr;
	inline void(*glVertexArrayRangeNV) (GLsizei length, void* pointer) = nullptr;
#define NV_vertex_array_range 1

	//vertex_array_range2
#define NV_vertex_array_range2 1

	//vertex_attrib_integer_64bit
	inline void(*glGetVertexAttribLi64vNV) (GLuint index, GLenum pname, GLint64EXT * params) = nullptr;
	inline void(*glGetVertexAttribLui64vNV) (GLuint index, GLenum pname, GLuint64EXT* params) = nullptr;
	inline void(*glVertexAttribL1i64NV) (GLuint index, GLint64EXT x) = nullptr;
	inline void(*glVertexAttribL1i64vNV) (GLuint index, const GLint64EXT* v) = nullptr;
	inline void(*glVertexAttribL1ui64NV) (GLuint index, GLuint64EXT x) = nullptr;
	inline void(*glVertexAttribL1ui64vNV) (GLuint index, const GLuint64EXT* v) = nullptr;
	inline void(*glVertexAttribL2i64NV) (GLuint index, GLint64EXT x, GLint64EXT y) = nullptr;
	inline void(*glVertexAttribL2i64vNV) (GLuint index, const GLint64EXT* v) = nullptr;
	inline void(*glVertexAttribL2ui64NV) (GLuint index, GLuint64EXT x, GLuint64EXT y) = nullptr;
	inline void(*glVertexAttribL2ui64vNV) (GLuint index, const GLuint64EXT* v) = nullptr;
	inline void(*glVertexAttribL3i64NV) (GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z) = nullptr;
	inline void(*glVertexAttribL3i64vNV) (GLuint index, const GLint64EXT* v) = nullptr;
	inline void(*glVertexAttribL3ui64NV) (GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z) = nullptr;
	inline void(*glVertexAttribL3ui64vNV) (GLuint index, const GLuint64EXT* v) = nullptr;
	inline void(*glVertexAttribL4i64NV) (GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w) = nullptr;
	inline void(*glVertexAttribL4i64vNV) (GLuint index, const GLint64EXT* v) = nullptr;
	inline void(*glVertexAttribL4ui64NV) (GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) = nullptr;
	inline void(*glVertexAttribL4ui64vNV) (GLuint index, const GLuint64EXT* v) = nullptr;
	inline void(*glVertexAttribLFormatNV) (GLuint index, GLint size, GLenum type, GLsizei stride) = nullptr;
#define NV_vertex_attrib_integer_64bit 1

	//vertex_buffer_unified_memory
	inline void(*glBufferAddressRangeNV) (GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length) = nullptr;
	inline void(*glColorFormatNV) (GLint size, GLenum type, GLsizei stride) = nullptr;
	inline void(*glEdgeFlagFormatNV) (GLsizei stride) = nullptr;
	inline void(*glFogCoordFormatNV) (GLenum type, GLsizei stride) = nullptr;
	inline void(*glGetIntegerui64i_vNV) (GLenum value, GLuint index, GLuint64EXT result[]) = nullptr;
	inline void(*glIndexFormatNV) (GLenum type, GLsizei stride) = nullptr;
	inline void(*glNormalFormatNV) (GLenum type, GLsizei stride) = nullptr;
	inline void(*glSecondaryColorFormatNV) (GLint size, GLenum type, GLsizei stride) = nullptr;
	inline void(*glTexCoordFormatNV) (GLint size, GLenum type, GLsizei stride) = nullptr;
	inline void(*glVertexAttribFormatNV) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride) = nullptr;
	inline void(*glVertexAttribIFormatNV) (GLuint index, GLint size, GLenum type, GLsizei stride) = nullptr;
	inline void(*glVertexFormatNV) (GLint size, GLenum type, GLsizei stride) = nullptr;
#define NV_vertex_buffer_unified_memory 1

	//vertex_program
	inline GLboolean(*glAreProgramsResidentNV) (GLsizei n, const GLuint * ids, GLboolean * residences) = nullptr;
	inline void(*glBindProgramNV) (GLenum target, GLuint id) = nullptr;
	inline void(*glDeleteProgramsNV) (GLsizei n, const GLuint* ids) = nullptr;
	inline void(*glExecuteProgramNV) (GLenum target, GLuint id, const GLfloat* params) = nullptr;
	inline void(*glGenProgramsNV) (GLsizei n, GLuint* ids) = nullptr;
	inline void(*glGetProgramParameterdvNV) (GLenum target, GLuint index, GLenum pname, GLdouble* params) = nullptr;
	inline void(*glGetProgramParameterfvNV) (GLenum target, GLuint index, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetProgramStringNV) (GLuint id, GLenum pname, GLubyte* program) = nullptr;
	inline void(*glGetProgramivNV) (GLuint id, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetTrackMatrixivNV) (GLenum target, GLuint address, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetVertexAttribPointervNV) (GLuint index, GLenum pname, void** pointer) = nullptr;
	inline void(*glGetVertexAttribdvNV) (GLuint index, GLenum pname, GLdouble* params) = nullptr;
	inline void(*glGetVertexAttribfvNV) (GLuint index, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetVertexAttribivNV) (GLuint index, GLenum pname, GLint* params) = nullptr;
	inline GLboolean(*glIsProgramNV) (GLuint id) = nullptr;
	inline void(*glLoadProgramNV) (GLenum target, GLuint id, GLsizei len, const GLubyte* program) = nullptr;
	inline void(*glProgramParameter4dNV) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glProgramParameter4dvNV) (GLenum target, GLuint index, const GLdouble* params) = nullptr;
	inline void(*glProgramParameter4fNV) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glProgramParameter4fvNV) (GLenum target, GLuint index, const GLfloat* params) = nullptr;
	inline void(*glProgramParameters4dvNV) (GLenum target, GLuint index, GLsizei num, const GLdouble* params) = nullptr;
	inline void(*glProgramParameters4fvNV) (GLenum target, GLuint index, GLsizei num, const GLfloat* params) = nullptr;
	inline void(*glRequestResidentProgramsNV) (GLsizei n, GLuint* ids) = nullptr;
	inline void(*glTrackMatrixNV) (GLenum target, GLuint address, GLenum matrix, GLenum transform) = nullptr;
	inline void(*glVertexAttrib1dNV) (GLuint index, GLdouble x) = nullptr;
	inline void(*glVertexAttrib1dvNV) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttrib1fNV) (GLuint index, GLfloat x) = nullptr;
	inline void(*glVertexAttrib1fvNV) (GLuint index, const GLfloat* v) = nullptr;
	inline void(*glVertexAttrib1sNV) (GLuint index, GLshort x) = nullptr;
	inline void(*glVertexAttrib1svNV) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttrib2dNV) (GLuint index, GLdouble x, GLdouble y) = nullptr;
	inline void(*glVertexAttrib2dvNV) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttrib2fNV) (GLuint index, GLfloat x, GLfloat y) = nullptr;
	inline void(*glVertexAttrib2fvNV) (GLuint index, const GLfloat* v) = nullptr;
	inline void(*glVertexAttrib2sNV) (GLuint index, GLshort x, GLshort y) = nullptr;
	inline void(*glVertexAttrib2svNV) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttrib3dNV) (GLuint index, GLdouble x, GLdouble y, GLdouble z) = nullptr;
	inline void(*glVertexAttrib3dvNV) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttrib3fNV) (GLuint index, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glVertexAttrib3fvNV) (GLuint index, const GLfloat* v) = nullptr;
	inline void(*glVertexAttrib3sNV) (GLuint index, GLshort x, GLshort y, GLshort z) = nullptr;
	inline void(*glVertexAttrib3svNV) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttrib4dNV) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = nullptr;
	inline void(*glVertexAttrib4dvNV) (GLuint index, const GLdouble* v) = nullptr;
	inline void(*glVertexAttrib4fNV) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glVertexAttrib4fvNV) (GLuint index, const GLfloat* v) = nullptr;
	inline void(*glVertexAttrib4sNV) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) = nullptr;
	inline void(*glVertexAttrib4svNV) (GLuint index, const GLshort* v) = nullptr;
	inline void(*glVertexAttrib4ubNV) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) = nullptr;
	inline void(*glVertexAttrib4ubvNV) (GLuint index, const GLubyte* v) = nullptr;
	inline void(*glVertexAttribPointerNV) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) = nullptr;
	inline void(*glVertexAttribs1dvNV) (GLuint index, GLsizei n, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribs1fvNV) (GLuint index, GLsizei n, const GLfloat* v) = nullptr;
	inline void(*glVertexAttribs1svNV) (GLuint index, GLsizei n, const GLshort* v) = nullptr;
	inline void(*glVertexAttribs2dvNV) (GLuint index, GLsizei n, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribs2fvNV) (GLuint index, GLsizei n, const GLfloat* v) = nullptr;
	inline void(*glVertexAttribs2svNV) (GLuint index, GLsizei n, const GLshort* v) = nullptr;
	inline void(*glVertexAttribs3dvNV) (GLuint index, GLsizei n, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribs3fvNV) (GLuint index, GLsizei n, const GLfloat* v) = nullptr;
	inline void(*glVertexAttribs3svNV) (GLuint index, GLsizei n, const GLshort* v) = nullptr;
	inline void(*glVertexAttribs4dvNV) (GLuint index, GLsizei n, const GLdouble* v) = nullptr;
	inline void(*glVertexAttribs4fvNV) (GLuint index, GLsizei n, const GLfloat* v) = nullptr;
	inline void(*glVertexAttribs4svNV) (GLuint index, GLsizei n, const GLshort* v) = nullptr;
	inline void(*glVertexAttribs4ubvNV) (GLuint index, GLsizei n, const GLubyte* v) = nullptr;
#define NV_vertex_program 1

	//vertex_program1_1
#define NV_vertex_program1_1 1

	//vertex_program2
#define NV_vertex_program2 1

	//vertex_program2_option
#define NV_vertex_program2_option 1

	//vertex_program3
#define NV_vertex_program3 1

	//vertex_program4
#define NV_vertex_program4 1

	//video_capture
	inline void(*glBeginVideoCaptureNV) (GLuint video_capture_slot) = nullptr;
	inline void(*glBindVideoCaptureStreamBufferNV) (GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLintptrARB offset) = nullptr;
	inline void(*glBindVideoCaptureStreamTextureNV) (GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLenum target, GLuint texture) = nullptr;
	inline void(*glEndVideoCaptureNV) (GLuint video_capture_slot) = nullptr;
	inline void(*glGetVideoCaptureStreamdvNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, GLdouble* params) = nullptr;
	inline void(*glGetVideoCaptureStreamfvNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetVideoCaptureStreamivNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetVideoCaptureivNV) (GLuint video_capture_slot, GLenum pname, GLint* params) = nullptr;
	inline GLenum(*glVideoCaptureNV) (GLuint video_capture_slot, GLuint* sequence_num, GLuint64EXT* capture_time) = nullptr;
	inline void(*glVideoCaptureStreamParameterdvNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, const GLdouble* params) = nullptr;
	inline void(*glVideoCaptureStreamParameterfvNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glVideoCaptureStreamParameterivNV) (GLuint video_capture_slot, GLuint stream, GLenum pname, const GLint* params) = nullptr;
#define NV_video_capture 1

	//viewport_array
	inline void(*glDepthRangeArrayfvNV) (GLuint first, GLsizei count, const GLfloat * v) = nullptr;
	inline void(*glDepthRangeIndexedfNV) (GLuint index, GLfloat n, GLfloat f) = nullptr;
	inline void(*glDisableiNV) (GLenum target, GLuint index) = nullptr;
	inline void(*glEnableiNV) (GLenum target, GLuint index) = nullptr;
	inline void(*glGetFloati_vNV) (GLenum target, GLuint index, GLfloat* data) = nullptr;
	inline GLboolean(*glIsEnablediNV) (GLenum target, GLuint index) = nullptr;
	inline void(*glScissorArrayvNV) (GLuint first, GLsizei count, const GLint* v) = nullptr;
	inline void(*glScissorIndexedNV) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) = nullptr;
	inline void(*glScissorIndexedvNV) (GLuint index, const GLint* v) = nullptr;
	inline void(*glViewportArrayvNV) (GLuint first, GLsizei count, const GLfloat* v) = nullptr;
	inline void(*glViewportIndexedfNV) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) = nullptr;
	inline void(*glViewportIndexedfvNV) (GLuint index, const GLfloat* v) = nullptr;
#define NV_viewport_array 1

	//viewport_array2
#define NV_viewport_array2 1

	//viewport_swizzle
	inline void(*glViewportSwizzleNV) (GLuint index, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew) = nullptr;
#define NV_viewport_swizzle 1

	//*< load NV Extensions
	inline void LoadNVExtensions()
	{
		//3dvision_settings
		FetchProcAddress(glStereoParameterfNV, "glStereoParameterfNV");
		FetchProcAddress(glStereoParameteriNV, "glStereoParameteriNV");

		//bindless_multi_draw_indirect
		FetchProcAddress(glMultiDrawArraysIndirectBindlessNV, "glMultiDrawArraysIndirectBindlessNV");
		FetchProcAddress(glMultiDrawElementsIndirectBindlessNV, "glMultiDrawElementsIndirectBindlessNV");

		//bindless_multi_draw_indirect_count
		FetchProcAddress(glMultiDrawArraysIndirectBindlessCountNV, "glMultiDrawArraysIndirectBindlessCountNV");
		FetchProcAddress(glMultiDrawElementsIndirectBindlessCountNV, "glMultiDrawElementsIndirectBindlessCountNV");

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

		//blend_equation_advanced
		FetchProcAddress(glBlendBarrierNV, "glBlendBarrierNV");
		FetchProcAddress(glBlendParameteriNV, "glBlendParameteriNV");

		//clip_space_w_scaling
		FetchProcAddress(glViewportPositionWScaleNV, "glViewportPositionWScaleNV");

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

		//conditional_render
		FetchProcAddress(glBeginConditionalRenderNV, "glBeginConditionalRenderNV");
		FetchProcAddress(glEndConditionalRenderNV, "glEndConditionalRenderNV");

		//conservative_raster
		FetchProcAddress(glSubpixelPrecisionBiasNV, "glSubpixelPrecisionBiasNV");

		//conservative_raster_dilate
		FetchProcAddress(glConservativeRasterParameterfNV, "glConservativeRasterParameterfNV");

		//conservative_raster_pre_snap_triangles
		FetchProcAddress(glConservativeRasterParameteriNV, "glConservativeRasterParameteriNV");

		//copy_buffer
		FetchProcAddress(glCopyBufferSubDataNV, "glCopyBufferSubDataNV");

		//copy_image
		FetchProcAddress(glCopyImageSubDataNV, "glCopyImageSubDataNV");

		//depth_buffer_float
		FetchProcAddress(glClearDepthdNV, "glClearDepthdNV");
		FetchProcAddress(glDepthBoundsdNV, "glDepthBoundsdNV");
		FetchProcAddress(glDepthRangedNV, "glDepthRangedNV");

		//draw_buffers
		FetchProcAddress(glDrawBuffersNV, "glDrawBuffersNV");

		//draw_instanced
		FetchProcAddress(glDrawArraysInstancedNV, "glDrawArraysInstancedNV");
		FetchProcAddress(glDrawElementsInstancedNV, "glDrawElementsInstancedNV");

		//draw_texture
		FetchProcAddress(glDrawTextureNV, "glDrawTextureNV");

		//draw_vulkan_image
		FetchProcAddress(glDrawVkImageNV, "glDrawVkImageNV");
		FetchProcAddress(glGetVkProcAddrNV, "glGetVkProcAddrNV");
		FetchProcAddress(glSignalVkFenceNV, "glSignalVkFenceNV");
		FetchProcAddress(glSignalVkSemaphoreNV, "glSignalVkSemaphoreNV");
		FetchProcAddress(glWaitVkSemaphoreNV, "glWaitVkSemaphoreNV");

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

		//explicit_multisample
		FetchProcAddress(glGetMultisamplefvNV, "glGetMultisamplefvNV");
		FetchProcAddress(glSampleMaskIndexedNV, "glSampleMaskIndexedNV");
		FetchProcAddress(glTexRenderbufferNV, "glTexRenderbufferNV");

		//fence
		FetchProcAddress(glDeleteFencesNV, "glDeleteFencesNV");
		FetchProcAddress(glFinishFenceNV, "glFinishFenceNV");
		FetchProcAddress(glGenFencesNV, "glGenFencesNV");
		FetchProcAddress(glGetFenceivNV, "glGetFenceivNV");
		FetchProcAddress(glIsFenceNV, "glIsFenceNV");
		FetchProcAddress(glSetFenceNV, "glSetFenceNV");
		FetchProcAddress(glTestFenceNV, "glTestFenceNV");

		//fragment_coverage_to_color
		FetchProcAddress(glFragmentCoverageColorNV, "glFragmentCoverageColorNV");

		//fragment_program
		FetchProcAddress(glGetProgramNamedParameterdvNV, "glGetProgramNamedParameterdvNV");
		FetchProcAddress(glGetProgramNamedParameterfvNV, "glGetProgramNamedParameterfvNV");
		FetchProcAddress(glProgramNamedParameter4dNV, "glProgramNamedParameter4dNV");
		FetchProcAddress(glProgramNamedParameter4dvNV, "glProgramNamedParameter4dvNV");
		FetchProcAddress(glProgramNamedParameter4fNV, "glProgramNamedParameter4fNV");
		FetchProcAddress(glProgramNamedParameter4fvNV, "glProgramNamedParameter4fvNV");

		//framebuffer_blit
		FetchProcAddress(glBlitFramebufferNV, "glBlitFramebufferNV");

		//framebuffer_multisample
		FetchProcAddress(glRenderbufferStorageMultisampleNV, "glRenderbufferStorageMultisampleNV");


		//framebuffer_multisample_coverage
		FetchProcAddress(glRenderbufferStorageMultisampleCoverageNV, "glRenderbufferStorageMultisampleCoverageNV");

		//geometry_program4
		FetchProcAddress(glProgramVertexLimitNV, "glProgramVertexLimitNV");

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

		//instanced_arrays
		FetchProcAddress(glVertexAttribDivisorNV, "glVertexAttribDivisorNV");

		//internalformat_sample_query
		FetchProcAddress(glGetInternalformatSampleivNV, "glGetInternalformatSampleivNV");

		//non_square_matrices
		FetchProcAddress(glUniformMatrix2x3fvNV, "glUniformMatrix2x3fvNV");
		FetchProcAddress(glUniformMatrix2x4fvNV, "glUniformMatrix2x4fvNV");
		FetchProcAddress(glUniformMatrix3x2fvNV, "glUniformMatrix3x2fvNV");
		FetchProcAddress(glUniformMatrix3x4fvNV, "glUniformMatrix3x4fvNV");
		FetchProcAddress(glUniformMatrix4x2fvNV, "glUniformMatrix4x2fvNV");
		FetchProcAddress(glUniformMatrix4x3fvNV, "glUniformMatrix4x3fvNV");

		//occlusion_query
		FetchProcAddress(glBeginOcclusionQueryNV, "glBeginOcclusionQueryNV");
		FetchProcAddress(glDeleteOcclusionQueriesNV, "glDeleteOcclusionQueriesNV");
		FetchProcAddress(glEndOcclusionQueryNV, "glEndOcclusionQueryNV");
		FetchProcAddress(glGenOcclusionQueriesNV, "glGenOcclusionQueriesNV");
		FetchProcAddress(glGetOcclusionQueryivNV, "glGetOcclusionQueryivNV");
		FetchProcAddress(glGetOcclusionQueryuivNV, "glGetOcclusionQueryuivNV");
		FetchProcAddress(glIsOcclusionQueryNV, "glIsOcclusionQueryNV");

		//parameter_buffer_object
		FetchProcAddress(glProgramBufferParametersIivNV, "glProgramBufferParametersIivNV");
		FetchProcAddress(glProgramBufferParametersIuivNV, "glProgramBufferParametersIuivNV");
		FetchProcAddress(glProgramBufferParametersfvNV, "glProgramBufferParametersfvNV");

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

		//pixel_data_range
		FetchProcAddress(glFlushPixelDataRangeNV, "glFlushPixelDataRangeNV");
		FetchProcAddress(glPixelDataRangeNV, "glPixelDataRangeNV");

		//point_sprite
		FetchProcAddress(glPointParameteriNV, "glPointParameteriNV");
		FetchProcAddress(glPointParameterivNV, "glPointParameterivNV");

		//polygon_mode
		FetchProcAddress(glPolygonModeNV, "glPolygonModeNV");

		//present_video
		FetchProcAddress(glGetVideoi64vNV, "glGetVideoi64vNV");
		FetchProcAddress(glGetVideoivNV, "glGetVideoivNV");
		FetchProcAddress(glGetVideoui64vNV, "glGetVideoui64vNV");
		FetchProcAddress(glGetVideouivNV, "glGetVideouivNV");
		FetchProcAddress(glPresentFrameDualFillNV, "glPresentFrameDualFillNV");
		FetchProcAddress(glPresentFrameKeyedNV, "glPresentFrameKeyedNV");

		//primitive_restart
		FetchProcAddress(glPrimitiveRestartIndexNV, "glPrimitiveRestartIndexNV");
		FetchProcAddress(glPrimitiveRestartNV, "glPrimitiveRestartNV");

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

		//register_combiners2
		FetchProcAddress(glCombinerStageParameterfvNV, "glCombinerStageParameterfvNV");
		FetchProcAddress(glGetCombinerStageParameterfvNV, "glGetCombinerStageParameterfvNV");

		//sample_locations
		FetchProcAddress(glFramebufferSampleLocationsfvNV, "glFramebufferSampleLocationsfvNV");
		FetchProcAddress(glNamedFramebufferSampleLocationsfvNV, "glNamedFramebufferSampleLocationsfvNV");

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

		//texture_array
		FetchProcAddress(glCompressedTexImage3DNV, "glCompressedTexImage3DNV");
		FetchProcAddress(glCompressedTexSubImage3DNV, "glCompressedTexSubImage3DNV");
		FetchProcAddress(glCopyTexSubImage3DNV, "glCopyTexSubImage3DNV");
		FetchProcAddress(glFramebufferTextureLayerNV, "glFramebufferTextureLayerNV");
		FetchProcAddress(glTexImage3DNV, "glTexImage3DNV");
		FetchProcAddress(glTexSubImage3DNV, "glTexSubImage3DNV");

		//texture_barrier
		FetchProcAddress(glTextureBarrierNV, "glTextureBarrierNV");

		//texture_multisample
		FetchProcAddress(glTexImage2DMultisampleCoverageNV, "glTexImage2DMultisampleCoverageNV");
		FetchProcAddress(glTexImage3DMultisampleCoverageNV, "glTexImage3DMultisampleCoverageNV");
		FetchProcAddress(glTextureImage2DMultisampleCoverageNV, "glTextureImage2DMultisampleCoverageNV");
		FetchProcAddress(glTextureImage2DMultisampleNV, "glTextureImage2DMultisampleNV");
		FetchProcAddress(glTextureImage3DMultisampleCoverageNV, "glTextureImage3DMultisampleCoverageNV");
		FetchProcAddress(glTextureImage3DMultisampleNV, "glTextureImage3DMultisampleNV");

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

		//transform_feedback2
		FetchProcAddress(glBindTransformFeedbackNV, "glBindTransformFeedbackNV");
		FetchProcAddress(glDeleteTransformFeedbacksNV, "glDeleteTransformFeedbacksNV");
		FetchProcAddress(glDrawTransformFeedbackNV, "glDrawTransformFeedbackNV");
		FetchProcAddress(glGenTransformFeedbacksNV, "glGenTransformFeedbacksNV");
		FetchProcAddress(glIsTransformFeedbackNV, "glIsTransformFeedbackNV");
		FetchProcAddress(glPauseTransformFeedbackNV, "glPauseTransformFeedbackNV");
		FetchProcAddress(glResumeTransformFeedbackNV, "glResumeTransformFeedbackNV");

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

		//vertex_array_range
		FetchProcAddress(glFlushVertexArrayRangeNV, "glFlushVertexArrayRangeNV");
		FetchProcAddress(glVertexArrayRangeNV, "glVertexArrayRangeNV");

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

		//viewport_swizzle
		FetchProcAddress(glViewportSwizzleNV, "glViewportSwizzleNV");
	}

#pragma endregion NV Extensions

	//OpenGL OES Extensions
#pragma region OES

	//byte coordinates
#define byte_coordinates 1

	//*< load OES Extensions
	inline void LoadOESExtensions()
	{

	}

#pragma endregion OES Extensions

	//OpenGL OML Extensions
#pragma region OML

// interlace
#define GL_INTERLACE_OML                   0x8980
#define GL_INTERLACE_READ_OML              0x8981

// resample
#define GL_PACK_RESAMPLE_OML               0x8984
#define GL_UNPACK_RESAMPLE_OML             0x8985
#define GL_RESAMPLE_REPLICATE_OML          0x8986
#define GL_RESAMPLE_ZERO_FILL_OML          0x8987
#define GL_RESAMPLE_AVERAGE_OML            0x8988
#define GL_RESAMPLE_DECIMATE_OML           0x8989

// subsample
#define GL_FORMAT_SUBSAMPLE_24_24_OML      0x8982
#define GL_FORMAT_SUBSAMPLE_244_244_OML    0x8983


	//interlace
#define OML_interlace 1

	//resample
#define OML_resample 1

	//subsample
#define GLEW_OML_subsample 1

	//*< load OML Extensions
	inline void LoadOMLExtensions()
	{

	}

#pragma endregion OML Extensions

	//OpenGL OVE Extensions
#pragma region OVR

// OVR multiview multisampled render to texture
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_NUM_VIEWS_OVR          0x9630
#define GL_MAX_VIEWS_OVR                                          0x9631
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_BASE_VIEW_INDEX_OVR    0x9632
#define GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR               0x9633


	//multiview
	inline void(*glFramebufferTextureMultiviewOVR) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint baseViewIndex, GLsizei numViews) = nullptr;
#define OVR_multiview 1

	//multiview2
#define OVR_multiview2 1

	//OVR multiview multisampled render to texture
	inline void(*glFramebufferTextureMultisampleMultiviewOVR) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint baseViewIndex, GLsizei numViews) = nullptr;
#define OVR_multiview_multisampled_render_to_texture 1

	//*< load OVR Extensions
	inline void LoadOVRExtensions()
	{
		//multiview
		FetchProcAddress(glFramebufferTextureMultiviewOVR, "glFramebufferTextureMultiviewOVR");

		//OVR multiview multisampled render to texture
		FetchProcAddress(glFramebufferTextureMultisampleMultiviewOVR, "glFramebufferTextureMultisampleMultiviewOVR");
	}

#pragma endregion OVE Extensions

	//OpenGL PGI Extensions
#pragma region PGI

// misc_hints
#define GL_PREFER_DOUBLEBUFFER_HINT_PGI          107000
#define GL_CONSERVE_MEMORY_HINT_PGI              107005
#define GL_RECLAIM_MEMORY_HINT_PGI               107006
#define GL_NATIVE_GRAPHICS_HANDLE_PGI            107010
#define GL_NATIVE_GRAPHICS_BEGIN_HINT_PGI        107011
#define GL_NATIVE_GRAPHICS_END_HINT_PGI          107012
#define GL_ALWAYS_FAST_HINT_PGI                   107020
#define GL_ALWAYS_SOFT_HINT_PGI                   107021
#define GL_ALLOW_DRAW_OBJ_HINT_PGI                107022
#define GL_ALLOW_DRAW_WIN_HINT_PGI                107023
#define GL_ALLOW_DRAW_FRG_HINT_PGI                107024
#define GL_ALLOW_DRAW_MEM_HINT_PGI                107025
#define GL_STRICT_DEPTHFUNC_HINT_PGI              107030
#define GL_STRICT_LIGHTING_HINT_PGI               107031
#define GL_STRICT_SCISSOR_HINT_PGI                107032
#define GL_FULL_STIPPLE_HINT_PGI                  107033
#define GL_CLIP_NEAR_HINT_PGI                     107040
#define GL_CLIP_FAR_HINT_PGI                      107041
#define GL_WIDE_LINE_HINT_PGI                     107042
#define GL_BACK_NORMALS_HINT_PGI                  107043

// vertex hints
#define GL_VERTEX23_BIT_PGI                       0x00000004
#define GL_VERTEX4_BIT_PGI                        0x00000008
#define GL_COLOR3_BIT_PGI                         0x00010000
#define GL_COLOR4_BIT_PGI                         0x00020000
#define GL_EDGEFLAG_BIT_PGI                       0x00040000
#define GL_INDEX_BIT_PGI                          0x00080000
#define GL_MAT_AMBIENT_BIT_PGI                    0x00100000
#define GL_VERTEX_DATA_HINT_PGI                   107050
#define GL_VERTEX_CONSISTENT_HINT_PGI             107051
#define GL_MATERIAL_SIDE_HINT_PGI                 107052
#define GL_MAX_VERTEX_HINT_PGI                    107053
#define GL_MAT_AMBIENT_AND_DIFFUSE_BIT_PGI       0x00200000
#define GL_MAT_DIFFUSE_BIT_PGI                    0x00400000
#define GL_MAT_EMISSION_BIT_PGI                   0x00800000
#define GL_MAT_COLOR_INDEXES_BIT_PGI              0x01000000
#define GL_MAT_SHININESS_BIT_PGI                  0x02000000
#define GL_MAT_SPECULAR_BIT_PGI                   0x04000000
#define GL_NORMAL_BIT_PGI                         0x08000000
#define GL_TEXCOORD1_BIT_PGI                      0x10000000
#define GL_TEXCOORD2_BIT_PGI                      0x20000000
#define GL_TEXCOORD3_BIT_PGI                      0x40000000
#define GL_TEXCOORD4_BIT_PGI                      0x80000000


	//misc_hints
#define PGI_misc_hints 1

	//vertex hints
#define PGI_vertex_hints 1

	//*< load PGI Extensions
	inline void LoadPGIExtensions()
	{

	}

#pragma endregion PGI Extensions

	//OpenGL QCOM Extensions
#pragma region QCOM

// alpha_test
#define GL_ALPHA_TEST_QCOM                    0x0bc0
#define GL_ALPHA_TEST_FUNC_QCOM               0x0bc1
#define GL_ALPHA_TEST_REF_QCOM                0x0bc2

// binning_control
#define GL_DONT_CARE                         0x1100
#define GL_BINNING_CONTROL_HINT_QCOM         0x8fb0
#define GL_CPU_OPTIMIZED_QCOM                 0x8fb1
#define GL_GPU_OPTIMIZED_QCOM                 0x8fb2
#define GL_RENDER_DIRECT_TO_FRAMEBUFFER_QCOM 0x8fb3

// extended_get
#define GL_TEXTURE_WIDTH_QCOM                 0x8bd2
#define GL_TEXTURE_HEIGHT_QCOM                0x8bd3
#define GL_TEXTURE_DEPTH_QCOM                 0x8bd4
#define GL_TEXTURE_INTERNAL_FORMAT_QCOM      0x8bd5
#define GL_TEXTURE_FORMAT_QCOM                0x8bd6
#define GL_TEXTURE_TYPE_QCOM                  0x8bd7
#define GL_TEXTURE_IMAGE_VALID_QCOM          0x8bd8
#define GL_TEXTURE_NUM_LEVELS_QCOM            0x8bd9
#define GL_TEXTURE_TARGET_QCOM                0x8bda
#define GL_TEXTURE_OBJECT_VALID_QCOM         0x8bdb
#define GL_STATE_RESTORE                     0x8bdc

// framebuffer_foveated
#define GL_FOVEATION_ENABLE_BIT_QCOM          0x1
#define GL_FOVEATION_SCALED_BIN_METHOD_BIT_QCOM 0x2

// perfmon_global_mode
#define GL_PERFMON_GLOBAL_MODE_QCOM           0x8fa0

// shader_framebuffer_fetch_noncoherent
#define GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM 0x96a2

// tiled_rendering
#define GL_COLOR_BUFFER_BIT0_QCOM             0x00000001
#define GL_COLOR_BUFFER_BIT1_QCOM             0x00000002
#define GL_COLOR_BUFFER_BIT2_QCOM             0x00000004
#define GL_COLOR_BUFFER_BIT3_QCOM             0x00000008
#define GL_COLOR_BUFFER_BIT4_QCOM             0x00000010
#define GL_COLOR_BUFFER_BIT5_QCOM             0x00000020
#define GL_COLOR_BUFFER_BIT6_QCOM             0x00000040
#define GL_COLOR_BUFFER_BIT7_QCOM             0x00000080
#define GL_DEPTH_BUFFER_BIT0_QCOM             0x00000100
#define GL_DEPTH_BUFFER_BIT1_QCOM             0x00000200
#define GL_DEPTH_BUFFER_BIT2_QCOM             0x00000400
#define GL_DEPTH_BUFFER_BIT3_QCOM             0x00000800
#define GL_DEPTH_BUFFER_BIT4_QCOM             0x00001000
#define GL_DEPTH_BUFFER_BIT5_QCOM             0x00002000
#define GL_DEPTH_BUFFER_BIT6_QCOM             0x00004000
#define GL_DEPTH_BUFFER_BIT7_QCOM             0x00008000
#define GL_STENCIL_BUFFER_BIT0_QCOM           0x00010000
#define GL_STENCIL_BUFFER_BIT1_QCOM           0x00020000
#define GL_STENCIL_BUFFER_BIT2_QCOM           0x00040000
#define GL_STENCIL_BUFFER_BIT3_QCOM           0x00080000
#define GL_STENCIL_BUFFER_BIT4_QCOM           0x00100000
#define GL_STENCIL_BUFFER_BIT5_QCOM           0x00200000
#define GL_STENCIL_BUFFER_BIT6_QCOM           0x00400000
#define GL_STENCIL_BUFFER_BIT7_QCOM           0x00800000
#define GL_MULTISAMPLE_BUFFER_BIT0_QCOM       0x01000000
#define GL_MULTISAMPLE_BUFFER_BIT1_QCOM       0x02000000
#define GL_MULTISAMPLE_BUFFER_BIT2_QCOM       0x04000000
#define GL_MULTISAMPLE_BUFFER_BIT3_QCOM       0x08000000
#define GL_MULTISAMPLE_BUFFER_BIT4_QCOM       0x10000000
#define GL_MULTISAMPLE_BUFFER_BIT5_QCOM       0x20000000
#define GL_MULTISAMPLE_BUFFER_BIT6_QCOM       0x40000000
#define GL_MULTISAMPLE_BUFFER_BIT7_QCOM       0x80000000

// writeonly_rendering
#define GL_WRITEONLY_RENDERING_QCOM           0x8823

	//alpha_test
	inline void(*glAlphaFuncQCOM) (GLenum func, GLclampf ref) = nullptr;
#define QCOM_alpha_test 1

	//binning_control
#define QCOM_binning_control 1

	//driver_control
	inline void(*glDisableDriverControlQCOM) (GLuint driverControl) = nullptr;
	inline void(*glEnableDriverControlQCOM) (GLuint driverControl) = nullptr;
	inline void(*glGetDriverControlStringQCOM) (GLuint driverControl, GLsizei bufSize, GLsizei* length, GLchar* driverControlString) = nullptr;
	inline void(*glGetDriverControlsQCOM) (GLint* num, GLsizei size, GLuint* driverControls) = nullptr;

	//driver_control
#define QCOM_driver_control 1

	//extended_get
	inline void(*glExtGetBufferPointervQCOM) (GLenum target, void** params) = nullptr;
	inline void(*glExtGetBuffersQCOM) (GLuint* buffers, GLint maxBuffers, GLint* numBuffers) = nullptr;
	inline void(*glExtGetFramebuffersQCOM) (GLuint* framebuffers, GLint maxFramebuffers, GLint* numFramebuffers) = nullptr;
	inline void(*glExtGetRenderbuffersQCOM) (GLuint* renderbuffers, GLint maxRenderbuffers, GLint* numRenderbuffers) = nullptr;
	inline void(*glExtGetTexLevelParameterivQCOM) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint* params) = nullptr;
	inline void(*glExtGetTexSubImageQCOM) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void* texels) = nullptr;
	inline void(*glExtGetTexturesQCOM) (GLuint* textures, GLint maxTextures, GLint* numTextures) = nullptr;
	inline void(*glExtTexObjectStateOverrideiQCOM) (GLenum target, GLenum pname, GLint param) = nullptr;
#define QCOM_extended_get 1

	//extended_get2
	inline void(*glExtGetProgramBinarySourceQCOM) (GLuint program, GLenum shadertype, GLchar * source, GLint * length) = nullptr;
	inline void(*glExtGetProgramsQCOM) (GLuint* programs, GLint maxPrograms, GLint* numPrograms) = nullptr;
	inline void(*glExtGetShadersQCOM) (GLuint* shaders, GLint maxShaders, GLint* numShaders) = nullptr;
	inline GLboolean(*glExtIsProgramBinaryQCOM) (GLuint program) = nullptr;
#define QCOM_extended_get2 1

	//framebuffer_foveated
	inline void(*glFramebufferFoveationConfigQCOM) (GLuint fbo, GLuint numLayers, GLuint focalPointsPerLayer, GLuint requestedFeatures, GLuint * providedFeatures) = nullptr;
	inline void(*glFramebufferFoveationParametersQCOM) (GLuint fbo, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea) = nullptr;
#define QCOM_framebuffer_foveated 1

	//perfmon_global_mode
#define QCOM_perfmon_global_mode 1

	//shader_framebuffer_fetch_noncoherent
	inline void(*glFramebufferFetchBarrierQCOM) (void) = nullptr;
#define QCOM_shader_framebuffer_fetch_noncoherent 1

	//tiled_rendering
	inline void(*glEndTilingQCOM) (GLbitfield preserveMask) = nullptr;
	inline void(*glStartTilingQCOM) (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask) = nullptr;
#define QCOM_tiled_rendering 1

	//writeonly_rendering
#define QCOM_writeonly_rendering 1

	//*< load QCOM Extensions
	inline void LoadQCOMExtensions()
	{
		//alpha_test
		FetchProcAddress(glAlphaFuncQCOM, "glAlphaFuncQCOM");

		//driver_control
		FetchProcAddress(glDisableDriverControlQCOM, "glDisableDriverControlQCOM");
		FetchProcAddress(glEnableDriverControlQCOM, "glEnableDriverControlQCOM");
		FetchProcAddress(glGetDriverControlStringQCOM, "glGetDriverControlStringQCOM");
		FetchProcAddress(glGetDriverControlsQCOM, "glGetDriverControlsQCOM");

		//extended_get
		FetchProcAddress(glExtGetBufferPointervQCOM, "glExtGetBufferPointervQCOM");
		FetchProcAddress(glExtGetBuffersQCOM, "glExtGetBuffersQCOM");
		FetchProcAddress(glExtGetFramebuffersQCOM, "glExtGetFramebuffersQCOM");
		FetchProcAddress(glExtGetRenderbuffersQCOM, "glExtGetRenderbuffersQCOM");
		FetchProcAddress(glExtGetTexLevelParameterivQCOM, "glExtGetTexLevelParameterivQCOM");
		FetchProcAddress(glExtGetTexSubImageQCOM, "glExtGetTexSubImageQCOM");
		FetchProcAddress(glExtGetTexturesQCOM, "glExtGetTexturesQCOM");
		FetchProcAddress(glExtTexObjectStateOverrideiQCOM, "glExtTexObjectStateOverrideiQCOM");

		//extended_get2
		FetchProcAddress(glExtGetProgramBinarySourceQCOM, "glExtGetProgramBinarySourceQCOM");
		FetchProcAddress(glExtGetProgramsQCOM, "glExtGetProgramsQCOM");
		FetchProcAddress(glExtGetShadersQCOM, "glExtGetShadersQCOM");
		FetchProcAddress(glExtIsProgramBinaryQCOM, "glExtIsProgramBinaryQCOM");

		//framebuffer_foveated
		FetchProcAddress(glFramebufferFoveationConfigQCOM, "glFramebufferFoveationConfigQCOM");
		FetchProcAddress(glFramebufferFoveationParametersQCOM, "glFramebufferFoveationParametersQCOM");

		//shader_framebuffer_fetch_noncoherent
		FetchProcAddress(glFramebufferFetchBarrierQCOM, "glFramebufferFetchBarrierQCOM");

		//tiled_rendering
		FetchProcAddress(glEndTilingQCOM, "glEndTilingQCOM");
		FetchProcAddress(glStartTilingQCOM, "glStartTilingQCOM");
	}

#pragma endregion QCOM Extensions

	//OpenGL Regal Extensions
#pragma region Regal

	typedef int GLclampx;

// enable
#define GL_ERROR_REGAL            0x9322
#define GL_DEBUG_REGAL            0x9323
#define GL_LOG_REGAL              0x9324
#define GL_EMULATION_REGAL        0x9325
#define GL_DRIVER_REGAL           0x9326
#define GL_MISSING_REGAL          0x9360
#define GL_TRACE_REGAL            0x9361
#define GL_CACHE_REGAL            0x9362
#define GL_CODE_REGAL             0x9363
#define GL_STATISTICS_REGAL       0x9364

// log
#define GL_LOG_ERROR_REGAL        0x9319
#define GL_LOG_WARNING_REGAL      0x931a
#define GL_LOG_INFO_REGAL         0x931b
#define GL_LOG_APP_REGAL          0x931c
#define GL_LOG_DRIVER_REGAL       0x931d
#define GL_LOG_INTERNAL_REGAL     0x931e
#define GL_LOG_DEBUG_REGAL        0x931f
#define GL_LOG_STATUS_REGAL       0x9320
#define GL_LOG_HTTP_REGAL         0x9321


	//ES1_0_compatibility
	inline void(*glAlphaFuncx) (GLenum func, GLclampx ref) = nullptr;
	inline void(*glClearColorx) (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha) = nullptr;
	inline void(*glClearDepthx) (GLclampx depth) = nullptr;
	inline void(*glColor4x) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) = nullptr;
	inline void(*glDepthRangex) (GLclampx zNear, GLclampx zFar) = nullptr;
	inline void(*glFogx) (GLenum pname, GLfixed param) = nullptr;
	inline void(*glFogxv) (GLenum pname, const GLfixed* params) = nullptr;
	inline void(*glFrustumf) (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) = nullptr;
	inline void(*glFrustumx) (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) = nullptr;
	inline void(*glLightModelx) (GLenum pname, GLfixed param) = nullptr;
	inline void(*glLightModelxv) (GLenum pname, const GLfixed* params) = nullptr;
	inline void(*glLightx) (GLenum light, GLenum pname, GLfixed param) = nullptr;
	inline void(*glLightxv) (GLenum light, GLenum pname, const GLfixed* params) = nullptr;
	inline void(*glLineWidthx) (GLfixed width) = nullptr;
	inline void(*glLoadMatrixx) (const GLfixed* m) = nullptr;
	inline void(*glMaterialx) (GLenum face, GLenum pname, GLfixed param) = nullptr;
	inline void(*glMaterialxv) (GLenum face, GLenum pname, const GLfixed* params) = nullptr;
	inline void(*glMultMatrixx) (const GLfixed* m) = nullptr;
	inline void(*glMultiTexCoord4x) (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q) = nullptr;
	inline void(*glNormal3x) (GLfixed nx, GLfixed ny, GLfixed nz) = nullptr;
	inline void(*glOrthof) (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) = nullptr;
	inline void(*glOrthox) (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) = nullptr;
	inline void(*glPointSizex) (GLfixed size) = nullptr;
	inline void(*glPolygonOffsetx) (GLfixed factor, GLfixed units) = nullptr;
	inline void(*glRotatex) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z) = nullptr;
	inline void(*glSampleCoveragex) (GLclampx value, GLboolean invert) = nullptr;
	inline void(*glScalex) (GLfixed x, GLfixed y, GLfixed z) = nullptr;
	inline void(*glTexEnvx) (GLenum target, GLenum pname, GLfixed param) = nullptr;
	inline void(*glTexEnvxv) (GLenum target, GLenum pname, const GLfixed* params) = nullptr;
	inline void(*glTexParameterx) (GLenum target, GLenum pname, GLfixed param) = nullptr;
	inline void(*glTranslatex) (GLfixed x, GLfixed y, GLfixed z) = nullptr;
#define REGAL_ES1_0_compatibility 1

	//ES1_1_compatibility
	inline void(*glClipPlanef) (GLenum plane, const GLfloat * equation) = nullptr;
	inline void(*glClipPlanex) (GLenum plane, const GLfixed* equation) = nullptr;
	inline void(*glGetClipPlanef) (GLenum pname, GLfloat eqn[4]) = nullptr;
	inline void(*glGetClipPlanex) (GLenum pname, GLfixed eqn[4]) = nullptr;
	inline void(*glGetFixedv) (GLenum pname, GLfixed* params) = nullptr;
	inline void(*glGetLightxv) (GLenum light, GLenum pname, GLfixed* params) = nullptr;
	inline void(*glGetMaterialxv) (GLenum face, GLenum pname, GLfixed* params) = nullptr;
	inline void(*glGetTexEnvxv) (GLenum env, GLenum pname, GLfixed* params) = nullptr;
	inline void(*glGetTexParameterxv) (GLenum target, GLenum pname, GLfixed* params) = nullptr;
	inline void(*glPointParameterx) (GLenum pname, GLfixed param) = nullptr;
	inline void(*glPointParameterxv) (GLenum pname, const GLfixed* params) = nullptr;
	inline void(*glPointSizePointerOES) (GLenum type, GLsizei stride, const void* pointer) = nullptr;
	inline void(*glTexParameterxv) (GLenum target, GLenum pname, const GLfixed* params) = nullptr;
#define REGAL_ES1_1_compatibility 1

	//enable
#define REGAL_enable 1

	//error_string
	inline const GLchar * (*glErrorStringREGAL) (GLenum error) = nullptr;
#define REGAL_error_string 1

	//extension_query
	inline GLboolean(*glGetExtensionREGAL) (const GLchar * ext) = nullptr;
	inline GLboolean(*glIsSupportedREGAL) (const GLchar* ext) = nullptr;
#define REGAL_extension_query 1

	//log
	typedef void(GLLOGPROCREGAL)(GLenum stream, GLsizei length, const GLchar * message, void* context);
	inline void(*glLogMessageCallbackREGAL) (GLLOGPROCREGAL callback) = nullptr;
#define REGAL_log 1

	//proc_address
	inline void* (*glGetProcAddressREGAL) (const GLchar * name) = nullptr;
#define REGAL_proc_address 1

	//*< load Regal Extensions
	inline void LoadRegalExtensions()
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

		//error_string
		FetchProcAddress(glErrorStringREGAL, "glErrorStringREGAL");

		//extension_query
		FetchProcAddress(glGetExtensionREGAL, "glGetExtensionREGAL");
		FetchProcAddress(glIsSupportedREGAL, "glIsSupportedREGAL");

		//log
		FetchProcAddress(glLogMessageCallbackREGAL, "glLogMessageCallbackREGAL");

		//proc_address
		FetchProcAddress(glGetProcAddressREGAL, "glGetProcAddressREGAL");
	}

#pragma endregion Regal Extensions

	//OpenGL REND Extensions
#pragma region REND

// screen_coordinates
#define GL_SCREEN_COORDINATES_REND      0x8490
#define GL_INVERTED_SCREEN_W_REND       0x8491


	//screen_coordinates
#define REND_screen_coordinates 1

	//*< load REND Extensions
	inline void LoadRENDExtensions()
	{

	}

#pragma endregion REND Extensions

	//OpenGL S3 Extensions
#pragma region S3

// s3tc
#define GL_RGB_S3TC             0x83A0
#define GL_RGB4_S3TC            0x83A1
#define GL_RGBA_S3TC            0x83A2
#define GL_RGBA4_S3TC           0x83A3
#define GL_RGBA_DXT5_S3TC       0x83A4
#define GL_RGBA4_DXT5_S3TC      0x83A5


	//s3tc
#define S3_s3tc 1

	//*< load S3 Extensions
	inline void LoadS3Extensions()
	{

	}

#pragma endregion S3 Extensions

	//OpenGL SGIS Extensions
#pragma region SGIS

// color_range
#define GL_EXTENDED_RANGE_SGIS            0x85A5
#define GL_MIN_RED_SGIS                   0x85A6
#define GL_MAX_RED_SGIS                   0x85A7
#define GL_MIN_GREEN_SGIS                 0x85A8
#define GL_MAX_GREEN_SGIS                 0x85A9
#define GL_MIN_BLUE_SGIS                  0x85AA
#define GL_MAX_BLUE_SGIS                  0x85AB
#define GL_MIN_ALPHA_SGIS                 0x85AC
#define GL_MAX_ALPHA_SGIS                 0x85AD

// generate_mipmap
#define GL_GENERATE_MIPMAP_SGIS           0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS      0x8192

// multisample
#define GL_MULTISAMPLE_SGIS               0x809D
#define GL_SAMPLE_ALPHA_TO_MASK_SGIS     0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_SGIS      0x809F
#define GL_SAMPLE_MASK_SGIS              0x80A0
#define GL_1PASS_SGIS                   0x80A1
#define GL_2PASS_0_SGIS                 0x80A2
#define GL_2PASS_1_SGIS                 0x80A3
#define GL_4PASS_0_SGIS                 0x80A4
#define GL_4PASS_1_SGIS                 0x80A5
#define GL_4PASS_2_SGIS                 0x80A6
#define GL_4PASS_3_SGIS                 0x80A7
#define GL_SAMPLE_BUFFERS_SGIS          0x80A8
#define GL_SAMPLES_SGIS                 0x80A9
#define GL_SAMPLE_MASK_VALUE_SGIS       0x80AA
#define GL_SAMPLE_MASK_INVERT_SGIS      0x80AB
#define GL_SAMPLE_PATTERN_SGIS          0x80AC

// multitexture
#define GL_SELECTED_TEXTURE_SGIS         0x83C0
#define GL_SELECTED_TEXTURE_COORD_SET_SGIS 0x83C1
#define GL_SELECTED_TEXTURE_TRANSFORM_SGIS 0x83C2
#define GL_MAX_TEXTURES_SGIS             0x83C3
#define GL_MAX_TEXTURE_COORD_SETS_SGIS  0x83C4
#define GL_TEXTURE_COORD_SET_INTERLEAVE_FACTOR_SGIS 0x83C5
#define GL_TEXTURE_ENV_COORD_SET_SGIS   0x83C6
#define GL_TEXTURE0_SGIS                 0x83C7
#define GL_TEXTURE1_SGIS                 0x83C8
#define GL_TEXTURE2_SGIS                 0x83C9
#define GL_TEXTURE3_SGIS                 0x83CA

// point_line_texgen
#define GL_EYE_DISTANCE_TO_POINT_SGIS   0x81F0
#define GL_OBJECT_DISTANCE_TO_POINT_SGIS 0x81F1
#define GL_EYE_DISTANCE_TO_LINE_SGIS    0x81F2
#define GL_OBJECT_DISTANCE_TO_LINE_SGIS 0x81F3
#define GL_EYE_POINT_SGIS               0x81F4
#define GL_OBJECT_POINT_SGIS            0x81F5
#define GL_EYE_LINE_SGIS                0x81F6
#define GL_OBJECT_LINE_SGIS             0x81F7

// texture_border_clamp
#define GL_CLAMP_TO_BORDER_SGIS         0x812D

// texture_edge_clamp
#define GL_CLAMP_TO_EDGE_SGIS           0x812F

// texture_lod
#define GL_TEXTURE_MIN_LOD_SGIS         0x813A
#define GL_TEXTURE_MAX_LOD_SGIS         0x813B
#define GL_TEXTURE_BASE_LEVEL_SGIS      0x813C
#define GL_TEXTURE_MAX_LEVEL_SGIS       0x813D

	//clip_band_hint
#define SGIS_clip_band_hint 1

	//color_range
#define SGIS_color_range 1

	//detail_texture
	inline void(*glDetailTexFuncSGIS) (GLenum target, GLsizei n, const GLfloat * points) = nullptr;
	inline void(*glGetDetailTexFuncSGIS) (GLenum target, GLfloat* points) = nullptr;
#define SGIS_detail_texture 1

	//fog_function
	inline void(*glFogFuncSGIS) (GLsizei n, const GLfloat * points) = nullptr;
	inline void(*glGetFogFuncSGIS) (GLfloat* points) = nullptr;
#define SGIS_fog_function 1

	//generate_mipmap
#define SGIS_generate_mipmap 1

	//line_texgen
#define SGIS_line_texgen 1

	//multisample
	inline void(*glSampleMaskSGIS) (GLclampf value, GLboolean invert) = nullptr;
	inline void(*glSamplePatternSGIS) (GLenum pattern) = nullptr;
#define SGIS_multisample 1

	//multitexture
	inline void(*glInterleavedTextureCoordSetsSGIS) (GLint factor) = nullptr;
	inline void(*glSelectTextureCoordSetSGIS) (GLenum target) = nullptr;
	inline void(*glSelectTextureSGIS) (GLenum target) = nullptr;
	inline void(*glSelectTextureTransformSGIS) (GLenum target) = nullptr;
#define SGIS_multitexture 1

	//pixel_texture
#define SGIS_pixel_texture 1

	//point_line_texgen
#define SGIS_point_line_texgen 1

	//shared_multisample
	inline void(*glMultisampleSubRectPosSGIS) (GLint x, GLint y) = nullptr;
#define SGIS_shared_multisample 1

	//sharpen_texture
	inline void(*glGetSharpenTexFuncSGIS) (GLenum target, GLfloat * points) = nullptr;
	inline void(*glSharpenTexFuncSGIS) (GLenum target, GLsizei n, const GLfloat* points) = nullptr;
#define SGIS_sharpen_texture 1

	//texture4D
	inline void(*glTexImage4DSGIS) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei extent, GLint border, GLenum format, GLenum type, const void* pixels) = nullptr;
	inline void(*glTexSubImage4DSGIS) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei extent, GLenum format, GLenum type, const void* pixels) = nullptr;
#define SGIS_texture4D 1

	//texture_border_clamp
#define SGIS_texture_border_clamp 1

	//texture_edge_clamp
#define SGIS_texture_edge_clamp 1

	//texture_filter4
	inline void(*glGetTexFilterFuncSGIS) (GLenum target, GLenum filter, GLfloat * weights) = nullptr;
	inline void(*glTexFilterFuncSGIS) (GLenum target, GLenum filter, GLsizei n, const GLfloat* weights) = nullptr;
#define SGIS_texture_filter4 1

	//texture_lod
#define SGIS_texture_lod 1

	//texture_select
#define SGIS_texture_select 1

	//*< load SGIS Extensions
	inline void LoadSGISExtensions()
	{
		//detail_texture
		FetchProcAddress(glDetailTexFuncSGIS, "glDetailTexFuncSGIS");
		FetchProcAddress(glGetDetailTexFuncSGIS, "glGetDetailTexFuncSGIS");

		//fog_function
		FetchProcAddress(glFogFuncSGIS, "glFogFuncSGIS");
		FetchProcAddress(glGetFogFuncSGIS, "glGetFogFuncSGIS");

		//multisample
		FetchProcAddress(glSampleMaskSGIS, "glSampleMaskSGIS");
		FetchProcAddress(glSamplePatternSGIS, "glSamplePatternSGIS");

		//multitexture
		FetchProcAddress(glInterleavedTextureCoordSetsSGIS, "glInterleavedTextureCoordSetsSGIS");
		FetchProcAddress(glSelectTextureCoordSetSGIS, "glSelectTextureCoordSetSGIS");
		FetchProcAddress(glSelectTextureSGIS, "glSelectTextureSGIS");
		FetchProcAddress(glSelectTextureTransformSGIS, "glSelectTextureTransformSGIS");

		//shared_multisample
		FetchProcAddress(glMultisampleSubRectPosSGIS, "glMultisampleSubRectPosSGIS");

		//sharpen_texture
		FetchProcAddress(glGetSharpenTexFuncSGIS, "glGetSharpenTexFuncSGIS");
		FetchProcAddress(glSharpenTexFuncSGIS, "glSharpenTexFuncSGIS");

		//texture4D
		FetchProcAddress(glTexImage4DSGIS, "glTexImage4DSGIS");
		FetchProcAddress(glTexSubImage4DSGIS, "glTexSubImage4DSGIS");

		//texture_filter4
		FetchProcAddress(glGetTexFilterFuncSGIS, "glGetTexFilterFuncSGIS");
		FetchProcAddress(glTexFilterFuncSGIS, "glTexFilterFuncSGIS");
	}

#pragma endregion SGIS Extensions

	//OpenGL SGIX Extensions
#pragma region SGIX

// async
#define GL_ASYNC_MARKER_SGIX                     0x8329

// async_histogram
#define GL_ASYNC_HISTOGRAM_SGIX                  0x832C
#define GL_MAX_ASYNC_HISTOGRAM_SGIX              0x832D

// async_pixel
#define GL_ASYNC_TEX_IMAGE_SGIX                   0x835C
#define GL_ASYNC_DRAW_PIXELS_SGIX                 0x835D
#define GL_ASYNC_READ_PIXELS_SGIX                 0x835E
#define GL_MAX_ASYNC_TEX_IMAGE_SGIX               0x835F
#define GL_MAX_ASYNC_DRAW_PIXELS_SGIX             0x8360
#define GL_MAX_ASYNC_READ_PIXELS_SGIX             0x8361

// bali_g_instruments
#define GL_BALI_NUM_TRIS_CULLED_INSTRUMENT        0x6080
#define GL_BALI_NUM_PRIMS_CLIPPED_INSTRUMENT      0x6081
#define GL_BALI_NUM_PRIMS_REJECT_INSTRUMENT       0x6082
#define GL_BALI_NUM_PRIMS_CLIP_RESULT_INSTRUMENT  0x6083

// bali_r_instruments
#define GL_BALI_FRAGMENTS_GENERATED_INSTRUMENT    0x6090
#define GL_BALI_DEPTH_PASS_INSTRUMENT              0x6091
#define GL_BALI_R_CHIP_COUNT                       0x6092

// blend_alpha_minmax
#define GL_ALPHA_MIN_SGIX                          0x8320
#define GL_ALPHA_MAX_SGIX                          0x8321

// blend_cadd
#define GL_FUNC_COMPLEX_ADD_EXT                    0x601C

// blend_cmultiply
#define GL_FUNC_COMPLEX_MULTIPLY_EXT               0x601B

// color_matrix_accuracy
#define GL_COLOR_MATRIX_HINT                       0x8317

// convolution_accuracy
#define GL_CONVOLUTION_HINT_SGIX                   0x8316

// cube_map
#define GL_ENV_MAP_SGIX                            0x8340
#define GL_CUBE_MAP_SGIX                           0x8341
#define GL_CUBE_MAP_ZP_SGIX                        0x8342
#define GL_CUBE_MAP_ZN_SGIX                        0x8343
#define GL_CUBE_MAP_XN_SGIX                        0x8344
#define GL_CUBE_MAP_XP_SGIX                        0x8345
#define GL_CUBE_MAP_YN_SGIX                        0x8346
#define GL_CUBE_MAP_YP_SGIX                        0x8347
#define GL_CUBE_MAP_BINDING_SGIX                   0x8348

// datapipe
#define GL_GEOMETRY_BIT                            0x1
#define GL_IMAGE_BIT                               0x2

// depth_pass_instrument
#define GL_DEPTH_PASS_INSTRUMENT_SGIX              0x8310
#define GL_DEPTH_PASS_INSTRUMENT_COUNTERS_SGIX     0x8311
#define GL_DEPTH_PASS_INSTRUMENT_MAX_SGIX          0x8312

// depth_texture
#define GL_DEPTH_COMPONENT16_SGIX                   0x81A5
#define GL_DEPTH_COMPONENT24_SGIX                   0x81A6
#define GL_DEPTH_COMPONENT32_SGIX                   0x81A7

// fog_blend
#define GL_FOG_BLEND_ALPHA_SGIX                    0x81FE
#define GL_FOG_BLEND_COLOR_SGIX                    0x81FF

// fog_layers
#define GL_FOG_TYPE_SGIX                           0x8323
#define GL_UNIFORM_SGIX                            0x8324
#define GL_LAYERED_SGIX                            0x8325
#define GL_FOG_GROUND_PLANE_SGIX                   0x8326
#define GL_FOG_LAYERS_POINTS_SGIX                  0x8327
#define GL_MAX_FOG_LAYERS_POINTS_SGIX              0x8328

// fog_offset
#define GL_FOG_OFFSET_SGIX                         0x8198
#define GL_FOG_OFFSET_VALUE_SGIX                   0x8199

// fog_scale
#define GL_FOG_SCALE_SGIX                          0x81FC
#define GL_FOG_SCALE_VALUE_SGIX                    0x81FD

// fragment_lighting_space
#define GL_EYE_SPACE_SGIX                          0x8436
#define GL_TANGENT_SPACE_SGIX                      0x8437
#define GL_OBJECT_SPACE_SGIX                       0x8438
#define GL_FRAGMENT_LIGHT_SPACE_SGIX               0x843D

// fragments_instrument
#define GL_FRAGMENTS_INSTRUMENT_SGIX               0x8313
#define GL_FRAGMENTS_INSTRUMENT_COUNTERS_SGIX     0x8314
#define GL_FRAGMENTS_INSTRUMENT_MAX_SGIX          0x8315

// icc_texture
#define GL_RGB_ICC_SGIX                            0x8460
#define GL_RGBA_ICC_SGIX                           0x8461
#define GL_ALPHA_ICC_SGIX                          0x8462
#define GL_LUMINANCE_ICC_SGIX                      0x8463
#define GL_INTENSITY_ICC_SGIX                      0x8464
#define GL_LUMINANCE_ALPHA_ICC_SGIX                0x8465
#define GL_R5_G6_B5_ICC_SGIX                       0x8466
#define GL_R5_G6_B5_A8_ICC_SGIX                    0x8467
#define GL_ALPHA16_ICC_SGIX                        0x8468
#define GL_LUMINANCE16_ICC_SGIX                    0x8469
#define GL_INTENSITY16_ICC_SGIX                    0x846A
#define GL_LUMINANCE16_ALPHA8_ICC_SGIX             0x846B

// igloo_interface
#define GL_IGLOO_FULLSCREEN_SGIX                   0x819E
#define GL_IGLOO_VIEWPORT_OFFSET_SGIX              0x819F
#define GL_IGLOO_SWAPTMESH_SGIX                    0x81A0
#define GL_IGLOO_COLORNORMAL_SGIX                   0x81A1
#define GL_IGLOO_IRISGL_MODE_SGIX                  0x81A2
#define GL_IGLOO_LMC_COLOR_SGIX                    0x81A3
#define GL_IGLOO_TMESHM0DE_SGIX                    0x81A4
#define GL_LIGHT31                                  0xBEAD

// interlace
#define GL_INTERLACE_SGIX                          0x8094

// line_quality_hint
#define GL_LINE_QUALITY_HINT_SGIX                   0x835B

// nurbs_eval
#define GL_MAP1_VERTEX_3_NURBS_SGIX                0x81CB
#define GL_MAP1_VERTEX_4_NURBS_SGIX                0x81CC
#define GL_MAP1_INDEX_NURBS_SGIX                   0x81CD
#define GL_MAP1_COLOR_4_NURBS_SGIX                  0x81CE
#define GL_MAP1_NORMAL_NURBS_SGIX                   0x81CF
#define GL_MAP1_TEXTURE_COORD_1_NURBS_SGIX          0x81E0
#define GL_MAP1_TEXTURE_COORD_2_NURBS_SGIX          0x81E1
#define GL_MAP1_TEXTURE_COORD_3_NURBS_SGIX          0x81E2
#define GL_MAP1_TEXTURE_COORD_4_NURBS_SGIX          0x81E3
#define GL_MAP2_VERTEX_3_NURBS_SGIX                0x81E4
#define GL_MAP2_VERTEX_4_NURBS_SGIX                0x81E5
#define GL_MAP2_INDEX_NURBS_SGIX                   0x81E6
#define GL_MAP2_COLOR_4_NURBS_SGIX                  0x81E7
#define GL_MAP2_NORMAL_NURBS_SGIX                   0x81E8
#define GL_MAP2_TEXTURE_COORD_1_NURBS_SGIX          0x81E9
#define GL_MAP2_TEXTURE_COORD_2_NURBS_SGIX          0x81EA
#define GL_MAP2_TEXTURE_COORD_3_NURBS_SGIX          0x81EB
#define GL_MAP2_TEXTURE_COORD_4_NURBS_SGIX          0x81EC
#define GL_NURBS_KNOT_COUNT_SGIX                    0x81ED
#define GL_NURBS_KNOT_VECTOR_SGIX                   0x81EE

// occlusion_instrument
#define GL_OCCLUSION_INSTRUMENT_SGIX               0x6060

// polynomial_ffd
#define GL_TEXTURE_DEFORMATION_BIT_SGIX             0x1
#define GL_GEOMETRY_DEFORMATION_BIT_SGIX            0x2

// resample
#define GL_PACK_RESAMPLE_SGIX                      0x842E
#define GL_UNPACK_RESAMPLE_SGIX                    0x842F
#define GL_RESAMPLE_DECIMATE_SGIX                   0x8430
#define GL_RESAMPLE_REPLICATE_SGIX                  0x8433
#define GL_RESAMPLE_ZERO_FILL_SGIX                   0x8434

// scalebias_hint
#define GL_SCALEBIAS_HINT_SGIX                     0x8322

// shadow
#define GL_TEXTURE_COMPARE_SGIX                    0x819A
#define GL_TEXTURE_COMPARE_OPERATOR_SGIX           0x819B
#define GL_TEXTURE_LEQUAL_R_SGIX                    0x819C
#define GL_TEXTURE_GEQUAL_R_SGIX                    0x819D

// shadow_ambient
#define GL_SHADOW_AMBIENT_SGIX                     0x80BF

// slim
#define GL_PACK_MAX_COMPRESSED_SIZE_SGIX           0x831B
#define GL_SLIM8U_SGIX                             0x831D
#define GL_SLIM10U_SGIX                            0x831E
#define GL_SLIM12S_SGIX                            0x831F

// spotlight_cutoff
#define GL_SPOT_CUTOFF_DELTA_SGIX                   0x8193

// subsample
#define GL_PACK_SUBSAMPLE_RATE_SGIX                0x85A0
#define GL_UNPACK_SUBSAMPLE_RATE_SGIX              0x85A1
#define GL_PIXEL_SUBSAMPLE_4444_SGIX               0x85A2
#define GL_PIXEL_SUBSAMPLE_2424_SGIX               0x85A3
#define GL_PIXEL_SUBSAMPLE_4242_SGIX               0x85A4

// texture_coordinate_clamp
#define GL_TEXTURE_MAX_CLAMP_S_SGIX                 0x8369
#define GL_TEXTURE_MAX_CLAMP_T_SGIX                 0x836A
#define GL_TEXTURE_MAX_CLAMP_R_SGIX                 0x836B

// texture_mipmap_anisotropic
#define GL_TEXTURE_MIPMAP_ANISOTROPY_SGIX           0x832E
#define GL_MAX_MIPMAP_ANISOTROPY_SGIX               0x832F

// texture_multi_buffer
#define GL_TEXTURE_MULTI_BUFFER_HINT_SGIX           0x812E

// texture_phase
#define GL_PHASE_SGIX                              0x832A

// texture_range
#define GL_RGB_SIGNED_SGIX                         0x85E0
#define GL_RGBA_SIGNED_SGIX                        0x85E1
#define GL_ALPHA_SIGNED_SGIX                       0x85E2
#define GL_LUMINANCE_SIGNED_SGIX                   0x85E3
#define GL_INTENSITY_SIGNED_SGIX                   0x85E4
#define GL_LUMINANCE_ALPHA_SIGNED_SGIX             0x85E5
#define GL_RGB16_SIGNED_SGIX                       0x85E6
#define GL_RGBA16_SIGNED_SGIX                      0x85E7
#define GL_ALPHA16_SIGNED_SGIX                     0x85E8
#define GL_LUMINANCE16_SIGNED_SGIX                 0x85E9
#define GL_INTENSITY16_SIGNED_SGIX                 0x85EA
#define GL_LUMINANCE16_ALPHA16_SIGNED_SGIX         0x85EB
#define GL_RGB_EXTENDED_RANGE_SGIX                 0x85EC
#define GL_RGBA_EXTENDED_RANGE_SGIX                0x85ED
#define GL_ALPHA_EXTENDED_RANGE_SGIX               0x85EE
#define GL_LUMINANCE_EXTENDED_RANGE_SGIX           0x85EF
#define GL_INTENSITY_EXTENDED_RANGE_SGIX           0x85F0
#define GL_LUMINANCE_ALPHA_EXTENDED_RANGE_SGIX     0x85F1
#define GL_RGB16_EXTENDED_RANGE_SGIX               0x85F2
#define GL_RGBA16_EXTENDED_RANGE_SGIX              0x85F3
#define GL_ALPHA16_EXTENDED_RANGE_SGIX             0x85F4
#define GL_LUMINANCE16_EXTENDED_RANGE_SGIX         0x85F5
#define GL_INTENSITY16_EXTENDED_RANGE_SGIX         0x85F6
#define GL_LUMINANCE16_ALPHA16_EXTENDED_RANGE_SGIX 0x85F7
#define GL_MIN_LUMINANCE_SGIS                      0x85F8
#define GL_MAX_LUMINANCE_SGIS                      0x85F9
#define GL_MIN_INTENSITY_SGIS                      0x85FA
#define GL_MAX_INTENSITY_SGIS                      0x85FB

// texture_scale_bias
#define GL_POST_TEXTURE_FILTER_BIAS_SGIX           0x8179
#define GL_POST_TEXTURE_FILTER_SCALE_SGIX          0x817A
#define GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX     0x817B
#define GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX    0x817C

// vertex_preclip
#define GL_VERTEX_PRECLIP_SGIX                     0x83EE
#define GL_VERTEX_PRECLIP_HINT_SGIX                0x83EF

// ycrcba
#define GL_YCRCB_SGIX                             0x8318
#define GL_YCRCBA_SGIX                            0x8319


	//async
	inline void(*glAsyncMarkerSGIX) (GLuint marker) = nullptr;
	inline void(*glDeleteAsyncMarkersSGIX) (GLuint marker, GLsizei range) = nullptr;
	inline GLint(*glFinishAsyncSGIX) (GLuint* markerp) = nullptr;
	inline GLuint(*glGenAsyncMarkersSGIX) (GLsizei range) = nullptr;
	inline GLboolean(*glIsAsyncMarkerSGIX) (GLuint marker) = nullptr;
	inline GLint(*glPollAsyncSGIX) (GLuint* markerp) = nullptr;

#define SGIX_async 1

	//async_histogram
#define SGIX_async_histogram 1

	//async_pixel
#define SGIX_async_pixel 1

	//bali_g_instruments
#define SGIX_bali_g_instruments 1

	//bali_r_instruments
#define SGIX_bali_r_instruments 1

	//bali_timer_instruments
#define SGIX_bali_timer_instruments 1

	//blend_alpha_minmax
#define SGIX_blend_alpha_minmax 1

	//blend_cadd
#define SGIX_blend_cadd 1

	//blend_cmultiply
#define SGIX_blend_cmultiply 1

	//calligraphic_fragment
#define SGIX_calligraphic_fragment 1

	//clipmap
#define SGIX_clipmap 1

	//color_matrix_accuracy
#define SGIX_color_matrix_accuracy 1

	//color_table_index_mode
#define SGIX_color_table_index_mode 1

	//complex_polar
#define SGIX_complex_polar 1

	//convolution_accuracy
#define SGIX_convolution_accuracy 1

	//cube_map
#define SGIX_cube_map 1

	//cylinder_texgen
#define SGIX_cylinder_texgen 1

	//datapipe
	inline void(*glAddressSpace) (GLenum space, GLbitfield mask) = nullptr;
	inline GLint(*glDataPipe) (GLenum space) = nullptr;
#define SGIX_datapipe 1

	//decimation
#define SGIX_decimation 1

	//depth_pass_instrument
#define SGIX_depth_pass_instrument 1

	//depth_texture
#define SGIX_depth_texture 1

	//dvc
#define SGIX_dvc 1

	//flush_raster
	inline void(*glFlushRasterSGIX) (void) = nullptr;
#define SGIX_flush_raster 1

	//fog_blend
#define SGIX_fog_blend 1

	//fog_factor_to_alpha
#define SGIX_fog_factor_to_alpha 1

	//fog_layers
	inline void(*glFogLayersSGIX) (GLsizei n, const GLfloat * points) = nullptr;
	inline void(*glGetFogLayersSGIX) (GLfloat* points) = nullptr;
#define SGIX_fog_layers 1

	//fog_offset
#define SGIX_fog_offset 1

	//fog_patchy
#define SGIX_fog_patchy 1

	//fog_scale
#define SGIX_fog_scale 1

	//fog_texture
	inline void(*glTextureFogSGIX) (GLenum pname) = nullptr;
#define SGIX_fog_texture 1

	//fragment_lighting_space
#define SGIX_fragment_lighting_space 1

	//fragment_specular_lighting
	inline void(*glFragmentColorMaterialSGIX) (GLenum face, GLenum mode) = nullptr;
	inline void(*glFragmentLightModelfSGIX) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glFragmentLightModelfvSGIX) (GLenum pname, GLfloat* params) = nullptr;
	inline void(*glFragmentLightModeliSGIX) (GLenum pname, GLint param) = nullptr;
	inline void(*glFragmentLightModelivSGIX) (GLenum pname, GLint* params) = nullptr;
	inline void(*glFragmentLightfSGIX) (GLenum light, GLenum pname, GLfloat param) = nullptr;
	inline void(*glFragmentLightfvSGIX) (GLenum light, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glFragmentLightiSGIX) (GLenum light, GLenum pname, GLint param) = nullptr;
	inline void(*glFragmentLightivSGIX) (GLenum light, GLenum pname, GLint* params) = nullptr;
	inline void(*glFragmentMaterialfSGIX) (GLenum face, GLenum pname, const GLfloat param) = nullptr;
	inline void(*glFragmentMaterialfvSGIX) (GLenum face, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glFragmentMaterialiSGIX) (GLenum face, GLenum pname, const GLint param) = nullptr;
	inline void(*glFragmentMaterialivSGIX) (GLenum face, GLenum pname, const GLint* params) = nullptr;
	inline void(*glGetFragmentLightfvSGIX) (GLenum light, GLenum value, GLfloat* data) = nullptr;
	inline void(*glGetFragmentLightivSGIX) (GLenum light, GLenum value, GLint* data) = nullptr;
	inline void(*glGetFragmentMaterialfvSGIX) (GLenum face, GLenum pname, const GLfloat* data) = nullptr;
	inline void(*glGetFragmentMaterialivSGIX) (GLenum face, GLenum pname, const GLint* data) = nullptr;
#define SGIX_fragment_specular_lighting 1

	//fragments_instrument
#define SGIX_fragments_instrument 1

	//framezoom
	inline void(*glFrameZoomSGIX) (GLint factor) = nullptr;
#define SGIX_framezoom 1

	//icc_texture
#define SGIX_icc_texture 1

	//igloo_interface
	inline void(*glIglooInterfaceSGIX) (GLenum pname, void* param) = nullptr;
#define SGIX_igloo_interface 1

	//image_compression
#define SGIX_image_compression 1

	//impact_pixel_texture
#define SGIX_impact_pixel_texture 1

	//instrument_error
#define SGIX_instrument_error 1

	//interlace
#define SGIX_interlace 1

	//ir_instrument1
#define SGIX_ir_instrument1 1

	//line_quality_hint
#define SGIX_line_quality_hint 1

	//list_priority
#define SGIX_list_priority 1

	//mpeg1
	inline void(*glAllocMPEGPredictorsSGIX) (GLsizei width, GLsizei height, GLsizei n, GLuint * predictors) = nullptr;
	inline void(*glDeleteMPEGPredictorsSGIX) (GLsizei n, GLuint* predictors) = nullptr;
	inline void(*glGenMPEGPredictorsSGIX) (GLsizei n, GLuint* predictors) = nullptr;
	inline void(*glGetMPEGParameterfvSGIX) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetMPEGParameterivSGIX) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetMPEGPredictorSGIX) (GLenum target, GLenum format, GLenum type, void* pixels) = nullptr;
	inline void(*glGetMPEGQuantTableubv) (GLenum target, GLubyte* values) = nullptr;
	inline GLboolean(*glIsMPEGPredictorSGIX) (GLuint predictor) = nullptr;
	inline void(*glMPEGPredictorSGIX) (GLenum target, GLenum format, GLenum type, void* pixels) = nullptr;
	inline void(*glMPEGQuantTableubv) (GLenum target, GLubyte* values) = nullptr;
	inline void(*glSwapMPEGPredictorsSGIX) (GLenum target0, GLenum target1) = nullptr;
#define SGIX_mpeg1 1

	//mpeg2
#define SGIX_mpeg2 1

	//nonlinear_lighting_pervertex
	inline void(*glGetNonlinLightfvSGIX) (GLenum light, GLenum pname, GLint * terms, GLfloat * data) = nullptr;
	inline void(*glGetNonlinMaterialfvSGIX) (GLenum face, GLenum pname, GLint* terms, const GLfloat* data) = nullptr;
	inline void(*glNonlinLightfvSGIX) (GLenum light, GLenum pname, GLint terms, GLfloat* params) = nullptr;
	inline void(*glNonlinMaterialfvSGIX) (GLenum face, GLenum pname, GLint terms, const GLfloat* params) = nullptr;
#define SGIX_nonlinear_lighting_pervertex 1

	//nurbs_eval
#define SGIX_nurbs_eval 1

	//occlusion_instrument
#define SGIX_occlusion_instrument 1

	//packed_6bytes
#define SGIX_packed_6bytes 1

	//pixel_texture
	inline void(*glPixelTexGenSGIX) (GLenum mode) = nullptr;
#define SGIX_pixel_texture 1

	//pixel_texture_bits
#define SGIX_pixel_texture_bits 1

	//pixel_texture_lod
#define SGIX_pixel_texture_lod 1

	//pixel_tiles
#define SGIX_pixel_tiles 1

	//polynomial_ffd
	inline void(*glDeformSGIX) (GLbitfield mask) = nullptr;
	inline void(*glLoadIdentityDeformationMapSGIX) (GLbitfield mask) = nullptr;
#define SGIX_polynomial_ffd 1

	//quad_mesh
	inline void(*glMeshBreadthSGIX) (GLint breadth) = nullptr;
	inline void(*glMeshStrideSGIX) (GLint stride) = nullptr;
#define SGIX_quad_mesh 1

	//reference_plane
	inline void(*glReferencePlaneSGIX) (const GLdouble * equation) = nullptr;
#define SGIX_reference_plane 1

	//resample
#define SGIX_resample 1

	//scalebias_hint
#define SGIX_scalebias_hint 1

	//shadow
#define SGIX_shadow 1

	//shadow_ambient
#define SGIX_shadow_ambient 1

	//slim
#define SGIX_slim 1

	//spotlight_cutoff
#define SGIX_spotlight_cutoff 1

	//sprite
	inline void(*glSpriteParameterfSGIX) (GLenum pname, GLfloat param) = nullptr;
	inline void(*glSpriteParameterfvSGIX) (GLenum pname, GLfloat* params) = nullptr;
	inline void(*glSpriteParameteriSGIX) (GLenum pname, GLint param) = nullptr;
	inline void(*glSpriteParameterivSGIX) (GLenum pname, GLint* params) = nullptr;
#define SGIX_sprite 1

	//subdiv_patch
#define SGIX_subdiv_patch 1

	//subsample
#define SGIX_subsample 1

	//tag_sample_buffer
	inline void(*glTagSampleBufferSGIX) (void) = nullptr;
#define SGIX_tag_sample_buffer 1

	//texture_add_env
#define SGIX_texture_add_env 1

	//texture_coordinate_clamp
#define SGIX_texture_coordinate_clamp 1

	//texture_lod_bias
#define SGIX_texture_lod_bias 1

	//texture_mipmap_anisotropic
#define SGIX_texture_mipmap_anisotropic 1

	//texture_multi_buffer
#define SGIX_texture_multi_buffer 1

	//texture_phase
#define SGIX_texture_phase 1

	//texture_range
#define SGIX_texture_range 1

	//texture_scale_bias
#define SGIX_texture_scale_bias 1

	//texture_supersample
#define SGIX_texture_supersample 1

	//vector_ops
	inline void(*glGetVectorOperationSGIX) (GLenum operation) = nullptr;
	inline void(*glVectorOperationSGIX) (GLenum operation) = nullptr;
#define SGIX_vector_ops 1

	//vertex_array_object
	inline GLboolean(*glAreVertexArraysResidentSGIX) (GLsizei n, const GLuint * arrays, GLboolean * residences) = nullptr;
	inline void(*glBindVertexArraySGIX) (GLuint array) = nullptr;
	inline void(*glDeleteVertexArraysSGIX) (GLsizei n, const GLuint* arrays) = nullptr;
	inline void(*glGenVertexArraysSGIX) (GLsizei n, GLuint* arrays) = nullptr;
	inline GLboolean(*glIsVertexArraySGIX) (GLuint array) = nullptr;
	inline void(*glPrioritizeVertexArraysSGIX) (GLsizei n, const GLuint* arrays, const GLclampf* priorities) = nullptr;
#define SGIX_vertex_array_object 1

	//vertex_preclip
#define SGIX_vertex_preclip 1

	//vertex_preclip_hint
#define SGIX_vertex_preclip_hint 1

	//ycrcb
#define SGIX_ycrcb 1

	//ycrcb_subsample
#define SGIX_ycrcb_subsample 1

	//ycrcba
#define SGIX_ycrcba 1

	//*< load SGIX Extensions
	inline void LoadSGIXExtensions()
	{
		//async
		FetchProcAddress(glAsyncMarkerSGIX, "glAsyncMarkerSGIX");
		FetchProcAddress(glDeleteAsyncMarkersSGIX, "glDeleteAsyncMarkersSGIX");
		FetchProcAddress(glFinishAsyncSGIX, "glFinishAsyncSGIX");
		FetchProcAddress(glGenAsyncMarkersSGIX, "glGenAsyncMarkersSGIX");
		FetchProcAddress(glIsAsyncMarkerSGIX, "glIsAsyncMarkerSGIX");
		FetchProcAddress(glPollAsyncSGIX, "glPollAsyncSGIX");

		//datapipe
		FetchProcAddress(glAddressSpace, "glAddressSpace");
		FetchProcAddress(glDataPipe, "glDataPipe");

		//flush_raster
		FetchProcAddress(glFlushRasterSGIX, "glFlushRasterSGIX");

		//fog_layers
		FetchProcAddress(glFogLayersSGIX, "glFogLayersSGIX");
		FetchProcAddress(glGetFogLayersSGIX, "glGetFogLayersSGIX");

		//fog_texture
		FetchProcAddress(glTextureFogSGIX, "glTextureFogSGIX");

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

		//framezoom
		FetchProcAddress(glFrameZoomSGIX, "glFrameZoomSGIX");

		//igloo_interface
		FetchProcAddress(glIglooInterfaceSGIX, "glIglooInterfaceSGIX");

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

		//nonlinear_lighting_pervertex
		FetchProcAddress(glGetNonlinLightfvSGIX, "glGetNonlinLightfvSGIX");
		FetchProcAddress(glGetNonlinMaterialfvSGIX, "glGetNonlinMaterialfvSGIX");
		FetchProcAddress(glNonlinLightfvSGIX, "glNonlinLightfvSGIX");
		FetchProcAddress(glNonlinMaterialfvSGIX, "glNonlinMaterialfvSGIX");

		//pixel_texture
		FetchProcAddress(glPixelTexGenSGIX, "glPixelTexGenSGIX");

		//polynomial_ffd
		FetchProcAddress(glDeformSGIX, "glDeformSGIX");
		FetchProcAddress(glLoadIdentityDeformationMapSGIX, "glLoadIdentityDeformationMapSGIX");

		//quad_mesh
		FetchProcAddress(glMeshBreadthSGIX, "glMeshBreadthSGIX");
		FetchProcAddress(glMeshStrideSGIX, "glMeshStrideSGIX");

		//reference_plane
		FetchProcAddress(glReferencePlaneSGIX, "glReferencePlaneSGIX");

		//sprite
		FetchProcAddress(glSpriteParameterfSGIX, "glSpriteParameterfSGIX");
		FetchProcAddress(glSpriteParameterfvSGIX, "glSpriteParameterfvSGIX");
		FetchProcAddress(glSpriteParameteriSGIX, "glSpriteParameteriSGIX");
		FetchProcAddress(glSpriteParameterivSGIX, "glSpriteParameterivSGIX");

		//tag_sample_buffer
		FetchProcAddress(glTagSampleBufferSGIX, "glTagSampleBufferSGIX");

		//vector_ops
		FetchProcAddress(glGetVectorOperationSGIX, "glGetVectorOperationSGIX");
		FetchProcAddress(glVectorOperationSGIX, "glVectorOperationSGIX");

		//vertex_array_object
		FetchProcAddress(glAreVertexArraysResidentSGIX, "glAreVertexArraysResidentSGIX");
		FetchProcAddress(glBindVertexArraySGIX, "glBindVertexArraySGIX");
		FetchProcAddress(glDeleteVertexArraysSGIX, "glDeleteVertexArraysSGIX");
		FetchProcAddress(glGenVertexArraysSGIX, "glGenVertexArraysSGIX");
		FetchProcAddress(glIsVertexArraySGIX, "glIsVertexArraySGIX");
		FetchProcAddress(glPrioritizeVertexArraysSGIX, "glPrioritizeVertexArraysSGIX");
	}

#pragma endregion SGIX Extensions

	//OpenGL SGI Extensions
#pragma region SGI

// color_matrix
#define GL_COLOR_MATRIX_SGI                     0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH_SGI         0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH_SGI     0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE_SGI      0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE_SGI    0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE_SGI     0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE_SGI    0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS_SGI       0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS_SGI     0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS_SGI      0x80BA
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS_SGI     0x80BB

// color_table
#define GL_COLOR_TABLE_SGI                       0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE_SGI    0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI   0x80D2
#define GL_PROXY_COLOR_TABLE_SGI                 0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE_SGI 0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE_SGI 0x80D5
#define GL_COLOR_TABLE_SCALE_SGI                 0x80D6
#define GL_COLOR_TABLE_BIAS_SGI                  0x80D7
#define GL_COLOR_TABLE_FORMAT_SGI                0x80D8
#define GL_COLOR_TABLE_WIDTH_SGI                 0x80D9
#define GL_COLOR_TABLE_RED_SIZE_SGI              0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE_SGI            0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE_SGI             0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE_SGI            0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE_SGI        0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE_SGI        0x80DF

// complex_type
#define GL_COMPLEX_UNSIGNED_BYTE_SGI             0x81BD
#define GL_COMPLEX_BYTE_SGI                      0x81BE
#define GL_COMPLEX_UNSIGNED_SHORT_SGI            0x81BF
#define GL_COMPLEX_SHORT_SGI                     0x81C0
#define GL_COMPLEX_UNSIGNED_INT_SGI              0x81C1
#define GL_COMPLEX_INT_SGI                       0x81C2
#define GL_COMPLEX_FLOAT_SGI                     0x81C3

// fft
#define GL_PIXEL_TRANSFORM_OPERATOR_SGI          0x81C4
#define GL_CONVOLUTION_SGI                       0x81C5
#define GL_FFT_1D_SGI                           0x81C6
#define GL_PIXEL_TRANSFORM_SGI                   0x81C7
#define GL_MAX_FFT_WIDTH_SGI                     0x81C8

// texture_color_table
#define GL_TEXTURE_COLOR_TABLE_SGI               0x80BC
#define GL_PROXY_TEXTURE_COLOR_TABLE_SGI         0x80BD


	//color_matrix
#define SGI_color_matrix 1

	//color_table
	inline void(*glColorTableParameterfvSGI) (GLenum target, GLenum pname, const GLfloat * params) = nullptr;
	inline void(*glColorTableParameterivSGI) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glColorTableSGI) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void* table) = nullptr;
	inline void(*glCopyColorTableSGI) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = nullptr;
	inline void(*glGetColorTableParameterfvSGI) (GLenum target, GLenum pname, GLfloat* params) = nullptr;
	inline void(*glGetColorTableParameterivSGI) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glGetColorTableSGI) (GLenum target, GLenum format, GLenum type, void* table) = nullptr;
#define SGI_color_table 1

	//complex
#define SGI_complex 1

	//complex_type
#define SGI_complex_type 1

	//fft
	inline void(*glGetPixelTransformParameterfvSGI) (GLenum target, GLenum pname, GLfloat * params) = nullptr;
	inline void(*glGetPixelTransformParameterivSGI) (GLenum target, GLenum pname, GLint* params) = nullptr;
	inline void(*glPixelTransformParameterfSGI) (GLenum target, GLenum pname, GLfloat param) = nullptr;
	inline void(*glPixelTransformParameterfvSGI) (GLenum target, GLenum pname, const GLfloat* params) = nullptr;
	inline void(*glPixelTransformParameteriSGI) (GLenum target, GLenum pname, GLint param) = nullptr;
	inline void(*glPixelTransformParameterivSGI) (GLenum target, GLenum pname, const GLint* params) = nullptr;
	inline void(*glPixelTransformSGI) (GLenum target) = nullptr;
#define SGI_fft 1

	//texture_color_table
#define SGI_texture_color_table 1

	//*< load SGI Extensions
	inline void LoadSGIExtensions()
	{
		//color_table
		FetchProcAddress(glColorTableParameterfvSGI, "glColorTableParameterfvSGI");
		FetchProcAddress(glColorTableParameterivSGI, "glColorTableParameterivSGI");
		FetchProcAddress(glColorTableSGI, "glColorTableSGI");
		FetchProcAddress(glCopyColorTableSGI, "glCopyColorTableSGI");
		FetchProcAddress(glGetColorTableParameterfvSGI, "glGetColorTableParameterfvSGI");
		FetchProcAddress(glGetColorTableParameterivSGI, "glGetColorTableParameterivSGI");
		FetchProcAddress(glGetColorTableSGI, "glGetColorTableSGI");

		//fft
		FetchProcAddress(glGetPixelTransformParameterfvSGI, "glGetPixelTransformParameterfvSGI");
		FetchProcAddress(glGetPixelTransformParameterivSGI, "glGetPixelTransformParameterivSGI");
		FetchProcAddress(glPixelTransformParameterfSGI, "glPixelTransformParameterfSGI");
		FetchProcAddress(glPixelTransformParameterfvSGI, "glPixelTransformParameterfvSGI");
		FetchProcAddress(glPixelTransformParameteriSGI, "glPixelTransformParameteriSGI");
		FetchProcAddress(glPixelTransformParameterivSGI, "glPixelTransformParameterivSGI");
		FetchProcAddress(glPixelTransformSGI, "glPixelTransformSGI");
	}

#pragma endregion SGI Extensions

	//OpenGL SUNX Extensions
#pragma region SUNX

	enum OpenGL_SUNX_e
	{
		//constant data
		gl_unpack_constant_data_sunx = 0x81d5,
		gl_texture_constant_data_sunx = 0x81d6,
	};

	//constant data
	inline void(*glFinishTextureSUNX) (void) = nullptr;
#define SUNX_constant_data 1

	//*< load SUNX Extensions
	inline void LoadSUNXExtensions()
	{
		FetchProcAddress(glFinishTextureSUNX, "glFinishTextureSUNX");
	}

#pragma endregion SUNX Extensions

	//OpenGL SUN Extensions
#pragma region SUN

// convolution_border_modes
#define GL_WRAP_BORDER_SUN                     0x81D4

// global_alpha
#define GL_GLOBAL_ALPHA_SUN                    0x81D9
#define GL_GLOBAL_ALPHA_FACTOR_SUN             0x81DA

// mesh_array
#define GL_QUAD_MESH_SUN                      0x8614
#define GL_TRIANGLE_MESH_SUN                  0x8615

// slice_accum
#define GL_SLICE_ACCUM_SUN                    0x85CC

// triangle_list
#define GL_RESTART_SUN                        0x01
#define GL_REPLACE_MIDDLE_SUN                 0x02
#define GL_REPLACE_OLDEST_SUN                 0x03
#define GL_TRIANGLE_LIST_SUN                  0x81D7
#define GL_REPLACEMENT_CODE_SUN               0x81D8
#define GL_REPLACEMENT_CODE_ARRAY_SUN         0x85C0
#define GL_REPLACEMENT_CODE_ARRAY_TYPE_SUN    0x85C1
#define GL_REPLACEMENT_CODE_ARRAY_STRIDE_SUN  0x85C2
#define GL_REPLACEMENT_CODE_ARRAY_POINTER_SUN 0x85C3
#define GL_R1UI_V3F_SUN                       0x85C4
#define GL_R1UI_C4UB_V3F_SUN                  0x85C5
#define GL_R1UI_C3F_V3F_SUN                   0x85C6
#define GL_R1UI_N3F_V3F_SUN                   0x85C7
#define GL_R1UI_C4F_N3F_V3F_SUN               0x85C8
#define GL_R1UI_T2F_V3F_SUN                   0x85C9
#define GL_R1UI_T2F_N3F_V3F_SUN               0x85CA
#define GL_R1UI_T2F_C4F_N3F_V3F_SUN           0x85CB


	//convolution_border_modes
#define SUN_convolution_border_modes 1

	//global_alpha
	inline void(*glGlobalAlphaFactorbSUN) (GLbyte factor) = nullptr;
	inline void(*glGlobalAlphaFactordSUN) (GLdouble factor) = nullptr;
	inline void(*glGlobalAlphaFactorfSUN) (GLfloat factor) = nullptr;
	inline void(*glGlobalAlphaFactoriSUN) (GLint factor) = nullptr;
	inline void(*glGlobalAlphaFactorsSUN) (GLshort factor) = nullptr;
	inline void(*glGlobalAlphaFactorubSUN) (GLubyte factor) = nullptr;
	inline void(*glGlobalAlphaFactoruiSUN) (GLuint factor) = nullptr;
	inline void(*glGlobalAlphaFactorusSUN) (GLushort factor) = nullptr;
#define SUN_global_alpha 1

	//mesh_array
#define SUN_mesh_array 1

	//read_video_pixels
	inline void(*glReadVideoPixelsSUN) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels) = nullptr;
#define SUN_read_video_pixels 1

	//slice_accum
#define SUN_slice_accum 1

	//triangle list
	inline void(*glReplacementCodePointerSUN) (GLenum type, GLsizei stride, const void* pointer) = nullptr;
	inline void(*glReplacementCodeubSUN) (GLubyte code) = nullptr;
	inline void(*glReplacementCodeubvSUN) (const GLubyte* code) = nullptr;
	inline void(*glReplacementCodeuiSUN) (GLuint code) = nullptr;
	inline void(*glReplacementCodeuivSUN) (const GLuint* code) = nullptr;
	inline void(*glReplacementCodeusSUN) (GLushort code) = nullptr;
	inline void(*glReplacementCodeusvSUN) (const GLushort* code) = nullptr;
#define SUN_triangle_list 1

	//vertex
	inline void(*glColor3fVertex3fSUN) (GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glColor3fVertex3fvSUN) (const GLfloat* c, const GLfloat* v) = nullptr;
	inline void(*glColor4fNormal3fVertex3fSUN) (GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glColor4fNormal3fVertex3fvSUN) (const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	inline void(*glColor4ubVertex2fSUN) (GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y) = nullptr;
	inline void(*glColor4ubVertex2fvSUN) (const GLubyte* c, const GLfloat* v) = nullptr;
	inline void(*glColor4ubVertex3fSUN) (GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glColor4ubVertex3fvSUN) (const GLubyte* c, const GLfloat* v) = nullptr;
	inline void(*glNormal3fVertex3fSUN) (GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glNormal3fVertex3fvSUN) (const GLfloat* n, const GLfloat* v) = nullptr;
	inline void(*glReplacementCodeuiColor3fVertex3fSUN) (GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glReplacementCodeuiColor3fVertex3fvSUN) (const GLuint* rc, const GLfloat* c, const GLfloat* v) = nullptr;
	inline void(*glReplacementCodeuiColor4fNormal3fVertex3fSUN) (GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glReplacementCodeuiColor4fNormal3fVertex3fvSUN) (const GLuint* rc, const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	inline void(*glReplacementCodeuiColor4ubVertex3fSUN) (GLuint rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glReplacementCodeuiColor4ubVertex3fvSUN) (const GLuint* rc, const GLubyte* c, const GLfloat* v) = nullptr;
	inline void(*glReplacementCodeuiNormal3fVertex3fSUN) (GLuint rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glReplacementCodeuiNormal3fVertex3fvSUN) (const GLuint* rc, const GLfloat* n, const GLfloat* v) = nullptr;
	inline void(*glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN) (GLuint rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN) (const GLuint* rc, const GLfloat* tc, const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	inline void(*glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN) (GLuint rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN) (const GLuint* rc, const GLfloat* tc, const GLfloat* n, const GLfloat* v) = nullptr;
	inline void(*glReplacementCodeuiTexCoord2fVertex3fSUN) (GLuint rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glReplacementCodeuiTexCoord2fVertex3fvSUN) (const GLuint* rc, const GLfloat* tc, const GLfloat* v) = nullptr;
	inline void(*glReplacementCodeuiVertex3fSUN) (GLuint rc, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glReplacementCodeuiVertex3fvSUN) (const GLuint* rc, const GLfloat* v) = nullptr;
	inline void(*glTexCoord2fColor3fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glTexCoord2fColor3fVertex3fvSUN) (const GLfloat* tc, const GLfloat* c, const GLfloat* v) = nullptr;
	inline void(*glTexCoord2fColor4fNormal3fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glTexCoord2fColor4fNormal3fVertex3fvSUN) (const GLfloat* tc, const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	inline void(*glTexCoord2fColor4ubVertex3fSUN) (GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glTexCoord2fColor4ubVertex3fvSUN) (const GLfloat* tc, const GLubyte* c, const GLfloat* v) = nullptr;
	inline void(*glTexCoord2fNormal3fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glTexCoord2fNormal3fVertex3fvSUN) (const GLfloat* tc, const GLfloat* n, const GLfloat* v) = nullptr;
	inline void(*glTexCoord2fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	inline void(*glTexCoord2fVertex3fvSUN) (const GLfloat* tc, const GLfloat* v) = nullptr;
	inline void(*glTexCoord4fColor4fNormal3fVertex4fSUN) (GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glTexCoord4fColor4fNormal3fVertex4fvSUN) (const GLfloat* tc, const GLfloat* c, const GLfloat* n, const GLfloat* v) = nullptr;
	inline void(*glTexCoord4fVertex4fSUN) (GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	inline void(*glTexCoord4fVertex4fvSUN) (const GLfloat* tc, const GLfloat* v) = nullptr;
#define SUN_vertex 1

	//*< load SUN Extensions
	inline void LoadSUNExtensions()
	{
		//global_alpha
		FetchProcAddress(glGlobalAlphaFactorbSUN, "glGlobalAlphaFactorbSUN");
		FetchProcAddress(glGlobalAlphaFactordSUN, "glGlobalAlphaFactordSUN");
		FetchProcAddress(glGlobalAlphaFactorfSUN, "glGlobalAlphaFactorfSUN");
		FetchProcAddress(glGlobalAlphaFactoriSUN, "glGlobalAlphaFactoriSUN");
		FetchProcAddress(glGlobalAlphaFactorsSUN, "glGlobalAlphaFactorsSUN");
		FetchProcAddress(glGlobalAlphaFactorubSUN, "glGlobalAlphaFactorubSUN");
		FetchProcAddress(glGlobalAlphaFactoruiSUN, "glGlobalAlphaFactoruiSUN");
		FetchProcAddress(glGlobalAlphaFactorusSUN, "glGlobalAlphaFactorusSUN");

		//read_video_pixels
		FetchProcAddress(glReadVideoPixelsSUN, "glReadVideoPixelsSUN");

		//triangle list
		FetchProcAddress(glReplacementCodePointerSUN, "glReplacementCodePointerSUN");
		FetchProcAddress(glReplacementCodeubSUN, "glReplacementCodeubSUN");
		FetchProcAddress(glReplacementCodeubvSUN, "glReplacementCodeubvSUN");
		FetchProcAddress(glReplacementCodeuiSUN, "glReplacementCodeuiSUN");
		FetchProcAddress(glReplacementCodeuivSUN, "glReplacementCodeuivSUN");
		FetchProcAddress(glReplacementCodeusSUN, "glReplacementCodeusSUN");
		FetchProcAddress(glReplacementCodeusvSUN, "glReplacementCodeusvSUN");

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
	}

#pragma endregion SUN Extensions

	//OpenGL WIN Extensions
#pragma region WIN

// phong shading
#define GL_PHONG_WIN              0x80EA
#define GL_PHONG_HINT_WIN         0x80EB

// specular fog
#define GL_FOG_SPECULAR_TEXTURE_WIN  0x80EC


	//phong shading
#define phong_shading 1

	//scene markerXXX
#define scene_markerXXX 1

	//specular fog
#define specular_fog 1

	//swap hint
	inline void(*glAddSwapHintRectWIN) (GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
#define swap_hint 1

	//*< load WIN Extensions
	inline void LoadWINExtensions()
	{
		//swap hint
		FetchProcAddress(glAddSwapHintRectWIN, "glAddSwapHintRectWIN");
	}

#pragma endregion WIN Extensions

	enum glVersion_e
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

	enum class vendor_e
	{
		V3DFX,
		AMD,
		Android,
		Angle,
		Apple,
		ARB,
		ARM,
		ATIX,
		ATI,
		EGL_KHR,
		EGL_NV,
		EXT,
		Gremedy,
		HP,
		IBM,
		INGR,
		Intel,
		KHR,
		KTX,
		MesaX,
		Mesa,
		NVX,
		NV,
		OES,
		OML,
		OVR,
		PGI,
		QCOM,
		Regal,
		REND,
		S3,
		SGIS,
		SGIX,
		SGI,
		SUNX,
		SUN,
		WIN,
	};

	enum error_e
	{
		loadFailed = 0,
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

	typedef std::pair<error_e,  std::string> errorEntry;
	using errorEvent_c = std::function<void(const std::string& message)>;
	inline errorEvent_c errorEvent;

	namespace
	{
		const std::unordered_map<error_e, std::string> errorLUT =
		{
			errorEntry(error_e::loadFailed, "Error: extension has failed to load"),
			errorEntry(error_e::Unsupported1_2, "Error: OpenGL 1.2 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported1_3, "Error: OpenGL 1.3 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported1_4, "Error: OpenGL 1.4 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported1_5, "Error: OpenGL 1.5 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported2_0, "Error: OpenGL 2.0 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported2_1, "Error: OpenGL 2.1 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported3_0, "Error: OpenGL 3.0 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported3_1, "Error: OpenGL 3.1 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported3_2, "Error: OpenGL 3.2 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported3_3, "Error: OpenGL 3.3 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported4_0, "Error: OpenGL 4.0 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported4_1, "Error: OpenGL 4.1 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported4_2, "Error: OpenGL 4.2 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported4_3, "Error: OpenGL 4.3 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported4_4, "Error: OpenGL 4.4 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported4_5, "Error: OpenGL 4.5 extensions unsupported. stopping loading here"),
			errorEntry(error_e::Unsupported4_6, "Error: OpenGL 4.6 extensions unsupported. stopping loading here"),
		};
		inline std::vector<errorEntry> errorLog;


		inline void AddErrorLog(const error_e& newError, const uint16_t& fileLine = __LINE__, const std::string& functionName = __FUNCTION__)
		{
			auto newString = errorLUT.at(newError);

			//add to string then send it along
			newString.append(" | in function: %s ");
			newString.append(functionName);
			newString.append("at line %i \n");
			newString.append(std::to_string(fileLine));

			const auto newEntry = errorEntry(newError, newString);

			errorLog.push_back(newEntry);

			if (errorEvent != nullptr)
			{
				errorEvent(newEntry.second);
			}
		}

		inline GLuint glVersionMajor;
		inline GLuint glVersionMinor;
}


	inline GLuint GetGLVersionMajor()
	{
		return glVersionMajor;
	}

	inline GLuint GetGLVersionMinor()
	{
		return glVersionMinor;
	}

	/**< get OpenGL version */
	inline void InitializeGLVersion()
	{
		const GLubyte* versionString = glGetString(GL_VERSION);

		if (versionString != nullptr)
		{
			glVersionMajor = versionString[0] - '0';
			glVersionMinor = versionString[2] - '0';
		}

		else
		{
			AddErrorLog(error_e::versionLoadFailed);
		}
	}

	/**< load all Vendor Extensions */
	inline void LoadAllVendors()
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

	/**< load all applicable OpenGL extensions */
	inline void InitializeExtensions()
	{
		InitializeGLVersion();

		//load vendor specific extensions first or last?
		if (glVersionMajor > 1 || (glVersionMinor >= 2 && glVersionMajor >= 1))
		{
			Load1_2Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported1_2);
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 3 && glVersionMajor >= 1))
		{
			Load1_3Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported1_3);
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 4 && glVersionMajor >= 1))
		{
			Load1_4Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported1_4);
		}

		if (glVersionMajor > 1 || (glVersionMinor >= 5 && glVersionMajor >= 1))
		{
			Load1_5Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported1_5);
		}

		if (glVersionMajor >= 2)
		{
			Load2_0Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported2_0);
		}

		if (glVersionMajor > 2 || (glVersionMinor >= 1 && glVersionMajor >= 2))
		{
			Load2_1Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported2_1);
		}

		if (glVersionMajor >= 3)
		{
			Load3_0Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported3_0);
		}

		if (glVersionMajor > 3 || (glVersionMinor >= 1 && glVersionMajor >= 3))
		{
			Load3_1Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported3_1);
		}

		if (glVersionMajor > 3 || (glVersionMinor >= 2 && glVersionMajor >= 3))
		{
			Load3_2Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported3_2);
		}

		if (glVersionMajor > 3 || (glVersionMinor >= 3 && glVersionMajor >= 3))
		{
			Load3_3Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported3_3);
		}

		if (glVersionMajor >= 4)
		{
			Load4_0Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported4_0);
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 1 && glVersionMajor >= 4))
		{
			Load4_1Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported4_1);
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 2 && glVersionMajor >= 4))
		{
			Load4_2Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported4_2);
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 3 && glVersionMajor >= 4))
		{
			Load4_3Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported4_3);
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 4 && glVersionMajor >= 4))
		{
			Load4_4Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported4_4);
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 5 && glVersionMajor >= 4))
		{
			Load4_5Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported4_5);
		}

		if (glVersionMajor > 4 || (glVersionMinor >= 6 && glVersionMajor >= 4))
		{
			Load4_6Extensions();
		}

		else
		{
			AddErrorLog(error_e::Unsupported4_6);
		}

		//ok load all vendors here
		LoadAllVendors();
	}

	/**< load specific OpenGL extensions via OpenGL versions */
	inline void InitializeExtensionsSpecific(const uint32_t& OpenGLVersions)
	{
		if (OpenGLVersions & glVersion_e::version1_2)
		{
			if (glVersionMajor > 1 || (glVersionMinor >= 2 && glVersionMajor >= 1))
			{
				Load1_2Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported1_2);
			}
		}

		if (OpenGLVersions & glVersion_e::version1_3)
		{
			if (glVersionMajor > 1 || (glVersionMinor >= 3 && glVersionMajor >= 1))
			{
				Load1_3Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported1_3);
			}
		}

		if (OpenGLVersions & glVersion_e::version1_4)
		{
			if (glVersionMajor > 1 || (glVersionMinor >= 4 && glVersionMajor >= 1))
			{
				Load1_4Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported1_4);
			}
		}

		if (OpenGLVersions & glVersion_e::version1_5)
		{
			if (glVersionMajor > 1 || (glVersionMinor >= 5 && glVersionMajor >= 1))
			{
				Load1_5Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported1_5);
			}
		}

		if (OpenGLVersions & glVersion_e::version2_0)
		{
			if (glVersionMajor > 2)
			{
				Load2_0Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported2_0);
			}
		}

		if (OpenGLVersions & glVersion_e::version2_1)
		{
			if (glVersionMajor > 2 || (glVersionMinor >= 1 && glVersionMajor >= 2))
			{
				Load2_1Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported2_1);
			}
		}

		if (OpenGLVersions & glVersion_e::version3_0)
		{
			if (glVersionMajor > 3)
			{
				Load3_0Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported3_0);
			}
		}

		if (OpenGLVersions & glVersion_e::version3_1)
		{
			if (glVersionMajor > 3 || (glVersionMinor >= 1 && glVersionMajor >= 3))
			{
				Load3_1Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported3_1);
			}
		}

		if (OpenGLVersions & glVersion_e::version3_2)
		{
			if (glVersionMajor > 3 || (glVersionMinor >= 2 && glVersionMajor >= 3))
			{
				Load3_2Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported3_2);
			}
		}

		if (OpenGLVersions & glVersion_e::version3_3)
		{
			if (glVersionMajor > 3 || (glVersionMinor >= 3 && glVersionMajor >= 3))
			{
				Load3_3Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported3_3);
			}
		}

		if (OpenGLVersions & glVersion_e::version4_0)
		{
			if (glVersionMajor > 4)
			{
				Load4_0Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported4_0);
			}
		}

		if (OpenGLVersions & glVersion_e::version4_1)
		{
			if (glVersionMajor > 4 || (glVersionMinor >= 1 && glVersionMajor >= 4))
			{
				Load4_1Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported4_1);
			}
		}

		if (OpenGLVersions & glVersion_e::version4_2)
		{
			if (glVersionMajor > 4 || (glVersionMinor >= 2 && glVersionMajor >= 4))
			{
				Load4_2Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported4_2);
			}
		}

		if (OpenGLVersions & glVersion_e::version4_3)
		{
			if (glVersionMajor > 4 || (glVersionMinor >= 3 && glVersionMajor >= 4))
			{
				Load4_3Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported4_3);
			}
		}

		if (OpenGLVersions & glVersion_e::version4_4)
		{
			if (glVersionMajor > 4 || (glVersionMinor >= 4 && glVersionMajor >= 4))
			{
				Load4_4Extensions();
			}

			else
			{
				AddErrorLog(error_e::Unsupported4_4);
			}
		}
	}

	inline void InitializeVendorExtensions(const vendor_e& vendor)
	{
		switch (vendor)
		{
			case vendor_e::V3DFX: Load3DFXExtensions(); break;
			case vendor_e::AMD: LoadAMDExtensions(); break;
			case vendor_e::Android: LoadAndroidExtensions(); break;
			case vendor_e::Angle: LoadAngleExtensions(); break;
			case vendor_e::Apple: LoadAppleExtensions(); break;
			case vendor_e::ARB: LoadARBExtensions(); break;
			case vendor_e::ARM: LoadARMExtensions(); break;
			case vendor_e::ATIX: LoadATIXExtensions(); break;
			case vendor_e::ATI: LoadATIExtensions(); break;
			case vendor_e::EGL_KHR: LoadEGLKHRExtensions(); break;
			case vendor_e::EGL_NV: LoadEGLNVExtensions(); break;
			case vendor_e::EXT: LoadEXTExtensions(); break;
			case vendor_e::Gremedy: LoadGremedyExtensions(); break;
			case vendor_e::HP: LoadHPExtensions(); break;
			case vendor_e::IBM: LoadIBMExtensions(); break;
			case vendor_e::INGR: LoadINGRExtensions(); break;
			case vendor_e::Intel: LoadIntelExtensions(); break;
			case vendor_e::KHR: LoadKHRExtensions(); break;
			case vendor_e::KTX: LoadKTXExtensions(); break;
			case vendor_e::MesaX: LoadMESAXExtensions(); break;
			case vendor_e::Mesa: LoadMESAExtensions(); break;
			case vendor_e::NVX: LoadNVXExtensions(); break;
			case vendor_e::NV: LoadNVExtensions(); break;
			case vendor_e::OES: LoadOESExtensions(); break;
			case vendor_e::OML: LoadOMLExtensions(); break;
			case vendor_e::OVR: LoadOVRExtensions(); break;
			case vendor_e::PGI: LoadPGIExtensions(); break;
			case vendor_e::QCOM: LoadQCOMExtensions(); break;
			case vendor_e::Regal: LoadRegalExtensions(); break;
			case vendor_e::REND: LoadRENDExtensions(); break;
			case vendor_e::S3: LoadS3Extensions(); break;
			case vendor_e::SGIS: LoadSGISExtensions(); break;
			case vendor_e::SGIX: LoadSGIXExtensions(); break;
			case vendor_e::SGI: LoadSGIExtensions(); break;
			case vendor_e::SUNX: LoadSUNXExtensions(); break;
			case vendor_e::SUN: LoadSUNExtensions(); break;
			case vendor_e::WIN: LoadWINExtensions(); break;
			default: break;
		}
	}

	/**< whether an extension is supported */
	inline bool IsExtensionSupported(const char* extensionName)
	{
		//the string length of the extension name

		const size_t nameLength = strlen((const char*)extensionName);

		GLubyte* allExtensions = (GLubyte*)glGetString(GL_EXTENSIONS); //get all supported extensions

		if (allExtensions != nullptr)
		{
			GLubyte* end = allExtensions + strlen((const char*)allExtensions);

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
#pragma clang diagnostic pop
#endif
