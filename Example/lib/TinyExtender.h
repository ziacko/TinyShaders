#ifndef TINYEXTENDER_H_
#define TINYEXTENDER_H_

#define GETFUNCTION(function) function

#define GLVERSION1_2 1L << 1
#define GLVERSION1_3 1L << 2
#define GLVERSION1_4 1L << 3
#define GLVERSION1_5 1L << 4
#define GLVERSION2_0 1L << 5
#define GLVERSION2_1 1L << 6
#define GLVERSION3_0 1L << 7
#define GLVERSION3_1 1L << 8
#define GLVERSION3_2 1L << 9
#define GLVERSION3_3 1L << 10
#define GLVERSION4_0 1L << 11
#define GLVERSION4_1 1L << 12
#define GLVERSION4_2 1L << 13
#define GLVERSION4_3 1L << 14
#define GLVERSION4_4 1L << 15

#if defined(_WIN32)
#include <Windows.h>
#include <gl/GL.h>

//this automatically loads the OpenGL library if you are using Visual studio 
#pragma comment (lib, "opengl32.lib")
#endif

#if defined(__linux__)
#include <GL/glx.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stddef.h>

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif

//OpenGL 1.2 Extensions
#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_TEXTURE_BINDING_3D             0x806A
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY  0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY  0x0B23
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E
#define GL_RESCALE_NORMAL                 0x803A
#define GL_LIGHT_MODEL_COLOR_CONTROL      0x81F8
#define GL_SINGLE_COLOR                   0x81F9
#define GL_SEPARATE_SPECULAR_COLOR        0x81FA
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLDRAWRANGEELEMENTSPROC __teDrawRangeElements;
extern PFNGLTEXIMAGE3DPROC __teTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC __teTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC __teCopyTexSubImage3D;
#define glDrawRangeElements GETFUNCTION(__teDrawRangeElements)
#define glTexImage3D GETFUNCTION(__teTexImage3D)
#define glTexSubImage3D GETFUNCTION(__teTexSubImage3D)
#define glCopyTexSubImage3D GETFUNCTION(__teCopyTexSubImage3D)

//OpenGL 1.3 Extensions
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP         0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_TEXTURE_COMPRESSION_HINT       0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define GL_TEXTURE_COMPRESSED             0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define GL_CLAMP_TO_BORDER                0x812D
#define GL_CLIENT_ACTIVE_TEXTURE          0x84E1
#define GL_MAX_TEXTURE_UNITS              0x84E2
#define GL_TRANSPOSE_MODELVIEW_MATRIX     0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX    0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX       0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX         0x84E6
#define GL_MULTISAMPLE_BIT                0x20000000
#define GL_NORMAL_MAP                     0x8511
#define GL_REFLECTION_MAP                 0x8512
#define GL_COMPRESSED_ALPHA               0x84E9
#define GL_COMPRESSED_LUMINANCE           0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA     0x84EB
#define GL_COMPRESSED_INTENSITY           0x84EC
#define GL_COMBINE                        0x8570
#define GL_COMBINE_RGB                    0x8571
#define GL_COMBINE_ALPHA                  0x8572
#define GL_SOURCE0_RGB                    0x8580
#define GL_SOURCE1_RGB                    0x8581
#define GL_SOURCE2_RGB                    0x8582
#define GL_SOURCE0_ALPHA                  0x8588
#define GL_SOURCE1_ALPHA                  0x8589
#define GL_SOURCE2_ALPHA                  0x858A
#define GL_OPERAND0_RGB                   0x8590
#define GL_OPERAND1_RGB                   0x8591
#define GL_OPERAND2_RGB                   0x8592
#define GL_OPERAND0_ALPHA                 0x8598
#define GL_OPERAND1_ALPHA                 0x8599
#define GL_OPERAND2_ALPHA                 0x859A
#define GL_RGB_SCALE                      0x8573
#define GL_ADD_SIGNED                     0x8574
#define GL_INTERPOLATE                    0x8575
#define GL_SUBTRACT                       0x84E7
#define GL_CONSTANT                       0x8576
#define GL_PRIMARY_COLOR                  0x8577
#define GL_PREVIOUS                       0x8578
#define GL_DOT3_RGB                       0x86AE
#define GL_DOT3_RGBA                      0x86AF
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat value, GLboolean invert);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, void *img);
typedef void (APIENTRYP PFNGLCLIENTACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1DPROC) (GLenum target, GLdouble s);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1FPROC) (GLenum target, GLfloat s);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1IPROC) (GLenum target, GLint s);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1SPROC) (GLenum target, GLshort s);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2DPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2FPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2IPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2SPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3IPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3SPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4IPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4SPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRYP PFNGLLOADTRANSPOSEMATRIXFPROC) (const GLfloat *m);
typedef void (APIENTRYP PFNGLLOADTRANSPOSEMATRIXDPROC) (const GLdouble *m);
typedef void (APIENTRYP PFNGLMULTTRANSPOSEMATRIXFPROC) (const GLfloat *m);
typedef void (APIENTRYP PFNGLMULTTRANSPOSEMATRIXDPROC) (const GLdouble *m);
extern PFNGLACTIVETEXTUREPROC __teActiveTexture;
extern PFNGLSAMPLECOVERAGEPROC __teSampleCoverage;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC __teCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC __teCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC __teCompressedTexImage1D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC __teCompressedTexSubImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC __teCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC __teCompressedTexSubImage1D;
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC __teGetCompressedTexImage;
extern PFNGLCLIENTACTIVETEXTUREPROC __teClientActiveTexture;
extern PFNGLMULTITEXCOORD1DPROC __teMultiTexCoord1d;
extern PFNGLMULTITEXCOORD1DVPROC __teMultiTexCoord1dv;
extern PFNGLMULTITEXCOORD1FPROC __teMultiTexCoord1f;
extern PFNGLMULTITEXCOORD1FVPROC __teMultiTexCoord1fv;
extern PFNGLMULTITEXCOORD1IPROC __teMultiTexCoord1i;
extern PFNGLMULTITEXCOORD1IVPROC __teMultiTexCoord1iv;
extern PFNGLMULTITEXCOORD1SPROC __teMultiTexCoord1s;
extern PFNGLMULTITEXCOORD1SVPROC __teMultiTexCoord1sv;
extern PFNGLMULTITEXCOORD2DPROC __teMultiTexCoord2d;
extern PFNGLMULTITEXCOORD2DVPROC __teMultiTexCoord2dv;
extern PFNGLMULTITEXCOORD2FPROC __teMultiTexCoord2f;
extern PFNGLMULTITEXCOORD2FVPROC __teMultiTexCoord2fv;
extern PFNGLMULTITEXCOORD2IPROC __teMultiTexCoord2i;
extern PFNGLMULTITEXCOORD2IVPROC __teMultiTexCoord2iv;
extern PFNGLMULTITEXCOORD2SPROC __teMultiTexCoord2s;
extern PFNGLMULTITEXCOORD2SVPROC __teMultiTexCoord2sv;
extern PFNGLMULTITEXCOORD3DPROC __teMultiTexCoord3d;
extern PFNGLMULTITEXCOORD3DVPROC __teMultiTexCoord3dv;
extern PFNGLMULTITEXCOORD3FPROC __teMultiTexCoord3f;
extern PFNGLMULTITEXCOORD3FVPROC __teMultiTexCoord3fv;
extern PFNGLMULTITEXCOORD3IPROC __teMultiTexCoord3i;
extern PFNGLMULTITEXCOORD3IVPROC __teMultiTexCoord3iv;
extern PFNGLMULTITEXCOORD3SPROC __teMultiTexCoord3s;
extern PFNGLMULTITEXCOORD3SVPROC __teMultiTexCoord3sv;
extern PFNGLMULTITEXCOORD4DPROC __teMultiTexCoord4d;
extern PFNGLMULTITEXCOORD4DVPROC __teMultiTexCoord4dv;
extern PFNGLMULTITEXCOORD4FPROC __teMultiTexCoord4f;
extern PFNGLMULTITEXCOORD4FVPROC __teMultiTexCoord4fv;
extern PFNGLMULTITEXCOORD4IPROC __teMultiTexCoord4i;
extern PFNGLMULTITEXCOORD4IVPROC __teMultiTexCoord4iv;
extern PFNGLMULTITEXCOORD4SPROC __teMultiTexCoord4s;
extern PFNGLMULTITEXCOORD4SVPROC __teMultiTexCoord4sv;
extern PFNGLLOADTRANSPOSEMATRIXFPROC __teLoadTransposeMatrixf;
extern PFNGLLOADTRANSPOSEMATRIXDPROC __teLoadTransposeMatrixd;
extern PFNGLMULTTRANSPOSEMATRIXFPROC __teMultTransposeMatrixf;
extern PFNGLMULTTRANSPOSEMATRIXDPROC __teMultTransposeMatrixd;
#define glActiveTexture GETFUNCTION(__teActiveTexture)
#define glSampleCoverage GETFUNCTION(__teSampleCoverage)
#define glCompressedTexImage3D GETFUNCTION(__teCompressedTexImage3D)
#define glCompressedTexImage2D GETFUNCTION(__teCompressedTexImage2D)
#define glCompressedTexImage1D GETFUNCTION(__teCompressedTexImage1D)
#define glCompressedTexSubImage3D GETFUNCTION(__teCompressedTexSubImage3D)
#define glCompressedTexSubImage2D GETFUNCTION(__teCompressedTexSubImage2D)
#define glCompressedTexSubImage1D GETFUNCTION(__teCompressedTexSubImage1D)
#define glGetCompressedTexImage GETFUNCTION(__teGetCompressedTexImage)
#define glClientActiveTexture GETFUNCTION(__teClientActiveTexture)
#define glMultiTexCoord1d GETFUNCTION(__teMultiTexCoord1d)
#define glMultiTexCoord1dv GETFUNCTION(__teMultiTexCoord1dv)
#define glMultiTexCoord1f GETFUNCTION(__teMultiTexCoord1f)
#define glMultiTexCoord1fv GETFUNCTION(__teMultiTexCoord1fv)
#define glMultiTexCoord1i GETFUNCTION(__teMultiTexCoord1i)
#define glMultiTexCoord1iv GETFUNCTION(__teMultiTexCoord1iv)
#define glMultiTexCoord1s GETFUNCTION(__teMultiTexCoord1s)
#define glMultiTexCoord2sv GETFUNCTION(__teMultiTexCoord2sv)
#define glMultiTexCoord2d GETFUNCTION(__teMultiTexCoord2d)
#define glMultiTexCoord2dv GETFUNCTION(__teMultiTexCoord2dv)
#define glMultiTexCoord2f GETFUNCTION(__teMultiTexCoord2f)
#define glMultiTexCoord2fv GETFUNCTION(__teMultiTexCoord2fv)
#define glMultiTexCoord2i GETFUNCTION(__teMultiTexCoord2i)
#define glMultiTexCoord2iv GETFUNCTION(__teMultiTexCoord2iv)
#define glMultiTexCoord2s GETFUNCTION(__teMultiTexCoord2s)
#define glMultiTexCoord2sv GETFUNCTION(__teMultiTexCoord2sv)
#define glMultiTexCoord3d GETFUNCTION(__teMultiTexCoord3d)
#define glMultiTexCoord3dv GETFUNCTION(__teMultiTexCoord3dv)
#define glMultiTexCoord3f GETFUNCTION(__teMultiTexCoord3f)
#define glMultiTexCoord3fv GETFUNCTION(__teMultiTexCoord3fv)
#define glMultiTexCoord3i GETFUNCTION(__teMultiTexCoord3i)
#define glMultiTexCoord3iv GETFUNCTION(__teMultiTexCoord3iv)
#define glMultiTexCoord3s GETFUNCTION(__teMultiTexCoord3s)
#define glMultiTexCoord3sv GETFUNCTION(__teMultiTexCoord3sv)
#define glMultiTexCoord4d GETFUNCTION(__teMultiTexCoord4d)
#define glMultiTexCoord4dv GETFUNCTION(__teMultiTexCoord4dv)
#define glMultiTexCoord4f GETFUNCTION(__teMultiTexCoord4f)
#define glMultiTexCoord4fv GETFUNCTION(__teMultiTexCoord4fv)
#define glMultiTexCoord4i GETFUNCTION(__teMultiTexCoord4i)
#define glMultiTexCoord4iv GETFUNCTION(__teMultiTexCoord4iv)
#define glMultiTexCoord4s GETFUNCTION(__teMultiTexCoord4s)
#define glMultiTexCoord4sv GETFUNCTION(__teMultiTexCoord4sv)

//OpenGL 1.4 Extensions
#define GL_BLEND_DST_RGB                  0x80C8
#define GL_BLEND_SRC_RGB                  0x80C9
#define GL_BLEND_DST_ALPHA                0x80CA
#define GL_BLEND_SRC_ALPHA                0x80CB
#define GL_POINT_FADE_THRESHOLD_SIZE      0x8128
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_MIRRORED_REPEAT                0x8370
#define GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#define GL_TEXTURE_LOD_BIAS               0x8501
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508
#define GL_TEXTURE_DEPTH_SIZE             0x884A
#define GL_TEXTURE_COMPARE_MODE           0x884C
#define GL_TEXTURE_COMPARE_FUNC           0x884D
#define GL_POINT_SIZE_MIN                 0x8126
#define GL_POINT_SIZE_MAX                 0x8127
#define GL_POINT_DISTANCE_ATTENUATION     0x8129
#define GL_GENERATE_MIPMAP                0x8191
#define GL_GENERATE_MIPMAP_HINT           0x8192
#define GL_FOG_COORDINATE_SOURCE          0x8450
#define GL_FOG_COORDINATE                 0x8451
#define GL_FRAGMENT_DEPTH                 0x8452
#define GL_CURRENT_FOG_COORDINATE         0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE      0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE    0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER   0x8456
#define GL_FOG_COORDINATE_ARRAY           0x8457
#define GL_COLOR_SUM                      0x8458
#define GL_CURRENT_SECONDARY_COLOR        0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE     0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE     0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE   0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER  0x845D
#define GL_SECONDARY_COLOR_ARRAY          0x845E
#define GL_TEXTURE_FILTER_CONTROL         0x8500
#define GL_DEPTH_TEXTURE_MODE             0x884B
#define GL_COMPARE_R_TO_TEXTURE           0x884E
#define GL_FUNC_ADD                       0x8006
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC) (GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC) (GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLFOGCOORDFPROC) (GLfloat coord);
typedef void (APIENTRYP PFNGLFOGCOORDFVPROC) (const GLfloat *coord);
typedef void (APIENTRYP PFNGLFOGCOORDDPROC) (GLdouble coord);
typedef void (APIENTRYP PFNGLFOGCOORDDVPROC) (const GLdouble *coord);
typedef void (APIENTRYP PFNGLFOGCOORDPOINTERPROC) (GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3BPROC) (GLbyte red, GLbyte green, GLbyte blue);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3BVPROC) (const GLbyte *v);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3DPROC) (GLdouble red, GLdouble green, GLdouble blue);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3DVPROC) (const GLdouble *v);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3FPROC) (GLfloat red, GLfloat green, GLfloat blue);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3FVPROC) (const GLfloat *v);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3IPROC) (GLint red, GLint green, GLint blue);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3IVPROC) (const GLint *v);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3SPROC) (GLshort red, GLshort green, GLshort blue);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3SVPROC) (const GLshort *v);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3UBPROC) (GLubyte red, GLubyte green, GLubyte blue);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3UBVPROC) (const GLubyte *v);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3UIPROC) (GLuint red, GLuint green, GLuint blue);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3UIVPROC) (const GLuint *v);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3USPROC) (GLushort red, GLushort green, GLushort blue);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3USVPROC) (const GLushort *v);
typedef void (APIENTRYP PFNGLSECONDARYCOLORPOINTERPROC) (GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLWINDOWPOS2DPROC) (GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLWINDOWPOS2DVPROC) (const GLdouble *v);
typedef void (APIENTRYP PFNGLWINDOWPOS2FPROC) (GLfloat x, GLfloat y);
typedef void (APIENTRYP PFNGLWINDOWPOS2FVPROC) (const GLfloat *v);
typedef void (APIENTRYP PFNGLWINDOWPOS2IPROC) (GLint x, GLint y);
typedef void (APIENTRYP PFNGLWINDOWPOS2IVPROC) (const GLint *v);
typedef void (APIENTRYP PFNGLWINDOWPOS2SPROC) (GLshort x, GLshort y);
typedef void (APIENTRYP PFNGLWINDOWPOS2SVPROC) (const GLshort *v);
typedef void (APIENTRYP PFNGLWINDOWPOS3DPROC) (GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLWINDOWPOS3DVPROC) (const GLdouble *v);
typedef void (APIENTRYP PFNGLWINDOWPOS3FPROC) (GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLWINDOWPOS3FVPROC) (const GLfloat *v);
typedef void (APIENTRYP PFNGLWINDOWPOS3IPROC) (GLint x, GLint y, GLint z);
typedef void (APIENTRYP PFNGLWINDOWPOS3IVPROC) (const GLint *v);
typedef void (APIENTRYP PFNGLWINDOWPOS3SPROC) (GLshort x, GLshort y, GLshort z);
typedef void (APIENTRYP PFNGLWINDOWPOS3SVPROC) (const GLshort *v);
typedef void (APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
extern PFNGLBLENDFUNCSEPARATEPROC __teBlendFuncSeparate;
extern PFNGLMULTIDRAWARRAYSPROC __teMultiDrawArrays;
extern PFNGLMULTIDRAWELEMENTSPROC __teMultiDrawElements;
extern PFNGLPOINTPARAMETERFPROC __tePointParameterf;
extern PFNGLPOINTPARAMETERFVPROC __tePointParameterfv;
extern PFNGLPOINTPARAMETERIPROC __tePointParameteri;
extern PFNGLPOINTPARAMETERIVPROC __tePointParameteriv;
extern PFNGLFOGCOORDFPROC __teFogCoordf;
extern PFNGLFOGCOORDFVPROC __teFogCoordfv;
extern PFNGLFOGCOORDDPROC __teFogCoordd;
extern PFNGLFOGCOORDDVPROC __teFogCoorddv;
extern PFNGLFOGCOORDPOINTERPROC __teFogCoordPointer;
extern PFNGLSECONDARYCOLOR3BPROC __teSecondaryColor3b;
extern PFNGLSECONDARYCOLOR3BVPROC __teSecondaryColor3bv;
extern PFNGLSECONDARYCOLOR3DPROC __teSecondaryColor3d;
extern PFNGLSECONDARYCOLOR3DVPROC __teSecondaryColor3dv;
extern PFNGLSECONDARYCOLOR3FPROC __teSecondaryColor3f;
extern PFNGLSECONDARYCOLOR3FVPROC __teSecondaryColor3fv;
extern PFNGLSECONDARYCOLOR3IPROC __teSecondaryColor3i;
extern PFNGLSECONDARYCOLOR3IVPROC __teSecondaryColor3iv;
extern PFNGLSECONDARYCOLOR3SPROC __teSecondaryColor3s;
extern PFNGLSECONDARYCOLOR3SVPROC __teSecondaryColor3sv;
extern PFNGLSECONDARYCOLOR3UBPROC __teSecondaryColor3ub;
extern PFNGLSECONDARYCOLOR3UBVPROC __teSecondaryColor3ubv;
extern PFNGLSECONDARYCOLOR3UIPROC __teSecondaryColor3ui;
extern PFNGLSECONDARYCOLOR3UIVPROC __teSecondaryColor3uiv;
extern PFNGLSECONDARYCOLOR3USPROC __teSecondaryColor3us;
extern PFNGLSECONDARYCOLOR3USVPROC __teSecondaryColor3usv;
extern PFNGLSECONDARYCOLORPOINTERPROC __teSecondaryColorPointer;
extern PFNGLWINDOWPOS2DPROC __teWindowPos2d;
extern PFNGLWINDOWPOS2DVPROC __teWindowPos2dv;
extern PFNGLWINDOWPOS2FPROC __teWindowPos2f;
extern PFNGLWINDOWPOS2FVPROC __teWindowPos2fv;
extern PFNGLWINDOWPOS2IPROC __teWindowPos2i;
extern PFNGLWINDOWPOS2IVPROC __teWindowPos2iv;
extern PFNGLWINDOWPOS2SPROC __teWindowPos2s;
extern PFNGLWINDOWPOS2SVPROC __teWindowPos2sv;
extern PFNGLWINDOWPOS3DPROC __teWindowPos3d;
extern PFNGLWINDOWPOS3DVPROC __teWindowPos3dv;
extern PFNGLWINDOWPOS3FPROC __teWindowPos3f;
extern PFNGLWINDOWPOS3FVPROC __teWindowPos3fv;
extern PFNGLWINDOWPOS3IPROC __teWindowPos3i;
extern PFNGLWINDOWPOS3IVPROC __teWindowPos3iv;
extern PFNGLWINDOWPOS3SPROC __teWindowPos3s;
extern PFNGLWINDOWPOS3SVPROC __teWindowPos3sv;
extern PFNGLBLENDCOLORPROC __teBlendColor;
extern PFNGLBLENDEQUATIONPROC __teBlendEquation;
#define glBlendFuncSeparate GETFUNCTION(__teBlendFuncSeparate)
#define glMultiDrawArrays GETFUNCTION(__teMultiDrawArrays)
#define glMultiDrawElements GETFUNCTION(__teMultiDrawElements)
#define glPointParameterf GETFUNCTION(__tePointParameterf)
#define glPointParameterfv GETFUNCTION(__tePointParameterfv)
#define glPointParameteri GETFUNCTION(__tePointParameteri)
#define glPointParameteriv GETFUNCTION(__tePointParameteriv)
#define glFogCoordf GETFUNCTION(__teFogCoordf)
#define glFogCoordfv GETFUNCTION(__teFogCoordfv)
#define glFogCoordd GETFUNCTION(__teFogCoordd)
#define glFogCoorddv GETFUNCTION(__teFogCoorddv)
#define glFogCoordPointer GETFUNCTION(__teFogCoordPointer)
#define glSecondaryColor3b GETFUNCTION(__teSecondaryColor3b)
#define glSecondaryColor3bv GETFUNCTION(__teSecondaryColor3bv)
#define glSecondaryColor3d GETFUNCTION(__teSecondaryColor3d)
#define glSecondaryColor3dv GETFUNCTION(__teSecondaryColor3dv)
#define glSecondaryColor3f GETFUNCTION(__teSecondaryColor3f)
#define glSecondaryColor3fv GETFUNCTION(__teSecondaryColor3fv)
#define glSecondaryColor3i GETFUNCTION(__teSecondaryColor3i)
#define glSecondaryColor3iv GETFUNCTION(__teSecondaryColor3iv)
#define glSecondaryColor3s GETFUNCTION(__teSecondaryColor3s)
#define glSecondaryColor3sv GETFUNCTION(__teSecondaryColor3sv)
#define glSecondaryColor3ub GETFUNCTION(__teSecondaryColor3ub)
#define glSecondaryColor3ubv GETFUNCTION(__teSecondaryColor3ubv)
#define glSecondaryColor3ui GETFUNCTION(__teSecondaryColor3ui)
#define glSecondaryColor3uiv GETFUNCTION(__teSecondaryColor3uiv)
#define glSecondaryColor3us GETFUNCTION(__teSecondaryColor3us)
#define glSecondaryColor3usv GETFUNCTION(__teSecondaryColor3usv)
#define glSecondaryColorPointer GETFUNCTION(__teSecondaryColorPointer)
#define glWindowPos2d GETFUNCTION(__teWindowPos2d)
#define glWindowPos2dv GETFUNCTION(__teWindowPos2dv)
#define glWindowPos2f GETFUNCTION(__teWindowPos2f)
#define glWindowPos2fv GETFUNCTION(__teWindowPos2fv)
#define glWindowPos2i GETFUNCTION(__teWindowPos2i)
#define glWindowPos2iv GETFUNCTION(__teWindowPos2iv)
#define glWindowPos2s GETFUNCTION(__teWindowPos2s)
#define glWindowPos2sv GETFUNCTION(__teWindowPos2sv)
#define glWindowPos3d GETFUNCTION(__teWindowPos3d)
#define glWindowPos3dv GETFUNCTION(__teWindowPos3dv)
#define glWindowPos3f GETFUNCTION(__teWindowPos3f)
#define glWindowPos3fv GETFUNCTION(__teWindowPos3fv)
#define glWindowPos3i GETFUNCTION(__teWindowPos3i)
#define glWindowPos3iv GETFUNCTION(__teWindowPos3iv)
#define glWindowPos3s GETFUNCTION(__teWindowPos3s)
#define glWindowPos3sv GETFUNCTION(__teWindowPos3sv)
#define glBlendColor GETFUNCTION(__teBlendColor)
#define glBlendEquation GETFUNCTION(__teBlendEquation)

//OpenGL 1.5 Extensions
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765
#define GL_QUERY_COUNTER_BITS             0x8864
#define GL_CURRENT_QUERY                  0x8865
#define GL_QUERY_RESULT                   0x8866
#define GL_QUERY_RESULT_AVAILABLE         0x8867
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_READ_ONLY                      0x88B8
#define GL_WRITE_ONLY                     0x88B9
#define GL_READ_WRITE                     0x88BA
#define GL_BUFFER_ACCESS                  0x88BB
#define GL_BUFFER_MAPPED                  0x88BC
#define GL_BUFFER_MAP_POINTER             0x88BD
#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA
#define GL_SAMPLES_PASSED                 0x8914
#define GL_SRC1_ALPHA                     0x8589
#define GL_VERTEX_ARRAY_BUFFER_BINDING    0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING    0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING     0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING     0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING 0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING 0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING    0x889E
#define GL_FOG_COORD_SRC                  0x8450
#define GL_FOG_COORD                      0x8451
#define GL_CURRENT_FOG_COORD              0x8453
#define GL_FOG_COORD_ARRAY_TYPE           0x8454
#define GL_FOG_COORD_ARRAY_STRIDE         0x8455
#define GL_FOG_COORD_ARRAY_POINTER        0x8456
#define GL_FOG_COORD_ARRAY                0x8457
#define GL_FOG_COORD_ARRAY_BUFFER_BINDING 0x889D
#define GL_SRC0_RGB                       0x8580
#define GL_SRC1_RGB                       0x8581
#define GL_SRC2_RGB                       0x8582
#define GL_SRC0_ALPHA                     0x8588
#define GL_SRC2_ALPHA                     0x858A
typedef void (APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, const GLuint *ids);
typedef GLboolean(APIENTRYP PFNGLISQUERYPROC) (GLuint id);
typedef void (APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef GLboolean(APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, void *data);
typedef void *(APIENTRYP PFNGLMAPBUFFERPROC) (GLenum target, GLenum access);
typedef GLboolean(APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, void **params);
extern PFNGLGENQUERIESPROC __teGenQueries;
extern PFNGLDELETEQUERIESPROC __teDeleteQueries;
extern PFNGLISQUERYPROC __teIsQuery;
extern PFNGLBEGINQUERYPROC __teBeginQuery;
extern PFNGLENDQUERYPROC __teEndQuery;
extern PFNGLGETQUERYIVPROC __teGetQueryiv;
extern PFNGLGETQUERYOBJECTIVPROC __teGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTUIVPROC __teGetQueryObjectuiv;
extern PFNGLBINDBUFFERPROC __teBindBuffer;
extern PFNGLDELETEBUFFERSPROC __teDeleteBuffers;
extern PFNGLGENBUFFERSPROC __teGenBuffers;
extern PFNGLISBUFFERPROC __teIsBuffer;
extern PFNGLBUFFERDATAPROC __teBufferData;
extern PFNGLBUFFERSUBDATAPROC __teBufferSubData;
extern PFNGLGETBUFFERSUBDATAPROC __teGetBufferSubData;
extern PFNGLMAPBUFFERPROC __teMapBuffer;
extern PFNGLUNMAPBUFFERPROC __teUnmapBuffer;
extern PFNGLGETBUFFERPARAMETERIVPROC __teGetBufferParameteriv;
extern PFNGLGETBUFFERPOINTERVPROC __teGetBufferPointerv;
#define glGenQueries GETFUNCTION(__teGenQueries)
#define glDeleteQueries GETFUNCTION(__teDeleteQueries)
#define glIsQuery GETFUNCTION(__teIsQuery)
#define glBeginQuery GETFUNCTION(__teBeginQuery)
#define glEndQuery GETFUNCTION(__teEndQuery)
#define glGetQueryiv GETFUNCTION(__teGetQueryiv)
#define glGetQueryObjectiv GETFUNCTION(__teGetQueryObjectiv)
#define glGetQueryObjectuiv GETFUNCTION(__teGetQueryObjectuiv)
#define glBindBuffer GETFUNCTION(__teBindBuffer)
#define glDeleteBuffers GETFUNCTION(__teDeleteBuffers)
#define glGenBuffers GETFUNCTION(__teGenBuffers)
#define glIsBuffer GETFUNCTION(__teIsBuffer)
#define glBufferData GETFUNCTION(__teBufferData)
#define glBufferSubData GETFUNCTION(__teBufferSubData)
#define glGetBufferSubData GETFUNCTION(__teGetBufferSubData)
#define glMapBuffer GETFUNCTION(__teMapBuffer)
#define glUnmapBuffer GETFUNCTION(__teUnmapBuffer)
#define glGetBufferParameteriv GETFUNCTION(__teGetBufferParameteriv)
#define glGetBufferPointerv GETFUNCTION(__teGetBufferPointerv)

//OpenGL 2.0 Extensions
typedef char GLchar;
#define GL_BLEND_EQUATION_RGB             0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE       0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#define GL_CURRENT_VERTEX_ATTRIB          0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE      0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_MAX_DRAW_BUFFERS               0x8824
#define GL_DRAW_BUFFER0                   0x8825
#define GL_DRAW_BUFFER1                   0x8826
#define GL_DRAW_BUFFER2                   0x8827
#define GL_DRAW_BUFFER3                   0x8828
#define GL_DRAW_BUFFER4                   0x8829
#define GL_DRAW_BUFFER5                   0x882A
#define GL_DRAW_BUFFER6                   0x882B
#define GL_DRAW_BUFFER7                   0x882C
#define GL_DRAW_BUFFER8                   0x882D
#define GL_DRAW_BUFFER9                   0x882E
#define GL_DRAW_BUFFER10                  0x882F
#define GL_DRAW_BUFFER11                  0x8830
#define GL_DRAW_BUFFER12                  0x8831
#define GL_DRAW_BUFFER13                  0x8832
#define GL_DRAW_BUFFER14                  0x8833
#define GL_DRAW_BUFFER15                  0x8834
#define GL_BLEND_EQUATION_ALPHA           0x883D
#define GL_MAX_VERTEX_ATTRIBS             0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#define GL_MAX_VARYING_FLOATS             0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE                    0x8B4F
#define GL_FLOAT_VEC2                     0x8B50
#define GL_FLOAT_VEC3                     0x8B51
#define GL_FLOAT_VEC4                     0x8B52
#define GL_INT_VEC2                       0x8B53
#define GL_INT_VEC3                       0x8B54
#define GL_INT_VEC4                       0x8B55
#define GL_BOOL                           0x8B56
#define GL_BOOL_VEC2                      0x8B57
#define GL_BOOL_VEC3                      0x8B58
#define GL_BOOL_VEC4                      0x8B59
#define GL_FLOAT_MAT2                     0x8B5A
#define GL_FLOAT_MAT3                     0x8B5B
#define GL_FLOAT_MAT4                     0x8B5C
#define GL_SAMPLER_1D                     0x8B5D
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_3D                     0x8B5F
#define GL_SAMPLER_CUBE                   0x8B60
#define GL_SAMPLER_1D_SHADOW              0x8B61
#define GL_SAMPLER_2D_SHADOW              0x8B62
#define GL_DELETE_STATUS                  0x8B80
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ACTIVE_UNIFORMS                0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH      0x8B87
#define GL_SHADER_SOURCE_LENGTH           0x8B88
#define GL_ACTIVE_ATTRIBUTES              0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN      0x8CA0
#define GL_LOWER_LEFT                     0x8CA1
#define GL_UPPER_LEFT                     0x8CA2
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
#define GL_VERTEX_PROGRAM_TWO_SIDE        0x8643
#define GL_POINT_SPRITE                   0x8861
#define GL_COORD_REPLACE                  0x8862
#define GL_MAX_TEXTURE_COORDS             0x8871
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, const GLenum *bufs);
typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const GLchar *name);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint(APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint(APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
typedef GLint(APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
typedef GLint(APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, void **pointer);
typedef GLboolean(APIENTRYP PFNGLISPROGRAMPROC) (GLuint program);
typedef GLboolean(APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC) (GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC) (GLuint index, GLshort x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC) (GLuint index, GLshort x, GLshort y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
extern PFNGLBLENDEQUATIONSEPARATEPROC __teBlendEquationSeparate;
extern PFNGLDRAWBUFFERSPROC __teDrawBuffers;
extern PFNGLSTENCILOPSEPARATEPROC __teStencilOpSeparate;
extern PFNGLSTENCILFUNCSEPARATEPROC __teStencilFuncSeparate;
extern PFNGLSTENCILMASKSEPARATEPROC __teStencilMaskSeparate;
extern PFNGLATTACHSHADERPROC __teAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC __teBindAttribLocation;
extern PFNGLCOMPILESHADERPROC __teCompileShader;
extern PFNGLCREATEPROGRAMPROC __teCreateProgram;
extern PFNGLCREATESHADERPROC __teCreateShader;
extern PFNGLDELETEPROGRAMPROC __teDeleteProgram;
extern PFNGLDELETESHADERPROC __teDeleteShader;
extern PFNGLDETACHSHADERPROC __teDetachShader;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC __teDisableVertexAttribArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC __teEnableVertexAttribArray;
extern PFNGLGETACTIVEATTRIBPROC __teGetActiveAttrib;
extern PFNGLGETACTIVEUNIFORMPROC __teGetActiveUniform;
extern PFNGLGETATTACHEDSHADERSPROC __teGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC __teGetAttribLocation;
extern PFNGLGETPROGRAMIVPROC __teGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC __teGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC __teGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC __teGetShaderInfoLog;
extern PFNGLGETSHADERSOURCEPROC __teGetShaderSource;
extern PFNGLGETUNIFORMLOCATIONPROC __teGetUniformLocation;
extern PFNGLGETUNIFORMFVPROC __teGetUniformfv;
extern PFNGLGETUNIFORMIVPROC __teGetUniformiv;
extern PFNGLGETVERTEXATTRIBDVPROC __teGetVertexAttribdv;
extern PFNGLGETVERTEXATTRIBFVPROC __teGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC __teGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC __teGetVertexAttribPointerv;
extern PFNGLISPROGRAMPROC __teIsProgram;
extern PFNGLISSHADERPROC __teIsShader;
extern PFNGLLINKPROGRAMPROC __teLinkProgram;
extern PFNGLSHADERSOURCEPROC __teShaderSource;
extern PFNGLUSEPROGRAMPROC __teUseProgram;
extern PFNGLUNIFORM1FPROC __teUniform1f;
extern PFNGLUNIFORM2FPROC __teUniform2f;
extern PFNGLUNIFORM3FPROC __teUniform3f;
extern PFNGLUNIFORM4FPROC __teUniform4f;
extern PFNGLUNIFORM1IPROC __teUniform1i;
extern PFNGLUNIFORM2IPROC __teUniform2i;
extern PFNGLUNIFORM3IPROC __teUniform3i;
extern PFNGLUNIFORM4IPROC __teUniform4i;
extern PFNGLUNIFORM1FVPROC __teUniform1fv;
extern PFNGLUNIFORM2FVPROC __teUniform2fv;
extern PFNGLUNIFORM3FVPROC __teUniform3fv;
extern PFNGLUNIFORM4FVPROC __teUniform4fv;
extern PFNGLUNIFORM1IVPROC __teUniform1iv;
extern PFNGLUNIFORM2IVPROC __teUniform2iv;
extern PFNGLUNIFORM3IVPROC __teUniform3iv;
extern PFNGLUNIFORM4IVPROC __teUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC __teUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC __teUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC __teUniformMatrix4fv;
extern PFNGLVALIDATEPROGRAMPROC __teValidateProgram;
extern PFNGLVERTEXATTRIB1DPROC __teVertexAttrib1d;
extern PFNGLVERTEXATTRIB1DVPROC __teVertexAttrib1dv;
extern PFNGLVERTEXATTRIB1FPROC __teVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC __teVertexAttrib1fv;
extern PFNGLVERTEXATTRIB1SPROC __teVertexAttrib1s;
extern PFNGLVERTEXATTRIB1SVPROC __teVertexAttrib1sv;
extern PFNGLVERTEXATTRIB2DPROC __teVertexAttrib2d;
extern PFNGLVERTEXATTRIB2DVPROC __teVertexAttrib2dv;
extern PFNGLVERTEXATTRIB2FPROC __teVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC __teVertexAttrib2fv;
extern PFNGLVERTEXATTRIB2SPROC __teVertexAttrib2s;
extern PFNGLVERTEXATTRIB2SVPROC __teVertexAttrib2sv;
extern PFNGLVERTEXATTRIB3DPROC __teVertexAttrib3d;
extern PFNGLVERTEXATTRIB3DVPROC __teVertexAttrib3dv;
extern PFNGLVERTEXATTRIB3FPROC __teVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC __teVertexAttrib3fv;
extern PFNGLVERTEXATTRIB3SPROC __teVertexAttrib3s;
extern PFNGLVERTEXATTRIB3SVPROC __teVertexAttrib3sv;
extern PFNGLVERTEXATTRIB4NBVPROC __teVertexAttrib4Nbv;
extern PFNGLVERTEXATTRIB4NIVPROC __teVertexAttrib4Niv;
extern PFNGLVERTEXATTRIB4NSVPROC __teVertexAttrib4Nsv;
extern PFNGLVERTEXATTRIB4NUBPROC __teVertexAttrib4Nub;
extern PFNGLVERTEXATTRIB4NUBVPROC __teVertexAttrib4Nubv;
extern PFNGLVERTEXATTRIB4NUIVPROC __teVertexAttrib4Nuiv;
extern PFNGLVERTEXATTRIB4NUSVPROC __teVertexAttrib4Nusv;
extern PFNGLVERTEXATTRIB4BVPROC __teVertexAttrib4bv;
extern PFNGLVERTEXATTRIB4DPROC __teVertexAttrib4d;
extern PFNGLVERTEXATTRIB4DVPROC __teVertexAttrib4dv;
extern PFNGLVERTEXATTRIB4FPROC __teVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC __teVertexAttrib4fv;
extern PFNGLVERTEXATTRIB4IVPROC __teVertexAttrib4iv;
extern PFNGLVERTEXATTRIB4SPROC __teVertexAttrib4s;
extern PFNGLVERTEXATTRIB4SVPROC __teVertexAttrib4sv;
extern PFNGLVERTEXATTRIB4UBVPROC __teVertexAttrib4ubv;
extern PFNGLVERTEXATTRIB4UIVPROC __teVertexAttrib4uiv;
extern PFNGLVERTEXATTRIB4USVPROC __teVertexAttrib4usv;
extern PFNGLVERTEXATTRIBPOINTERPROC __teVertexAttribPointer;
#define glBlendEquationSeparate GETFUNCTION(__teBlendEquationSeparate)
#define glDrawBuffers GETFUNCTION(__teDrawBuffers)
#define glStencilOpSeparate GETFUNCTION(__teStencilOpSeparate)
#define glStencilFuncSeparate GETFUNCTION(__teStencilFuncSeparate)
#define glStencilMaskSeparate GETFUNCTION(__teStencilMaskSeparate)
#define glAttachShader GETFUNCTION(__teAttachShader)
#define glBindAttribLocation GETFUNCTION(__teBindAttribLocation)
#define glCompileShader GETFUNCTION(__teCompileShader)
#define glCreateProgram GETFUNCTION(__teCreateProgram)
#define glCreateShader GETFUNCTION(__teCreateShader)
#define glDeleteProgram GETFUNCTION(__teDeleteProgram)
#define glDeleteShader GETFUNCTION(__teDeleteShader)
#define glDetachShader GETFUNCTION(__teDetachShader)
#define glDisableVertexAttribArray GETFUNCTION(__teDisableVertexAttribArray)
#define glEnableVertexAttribArray GETFUNCTION(__teEnableVertexAttribArray)
#define glGetActiveAttrib GETFUNCTION(__teGetActiveAttrib)
#define glGetActiveUniform GETFUNCTION(__teGetActiveUniform)
#define glGetAttachedShaders GETFUNCTION(__teGetAttachedShaders)
#define glGetAttribLocation GETFUNCTION(__teGetAttribLocation)
#define glGetProgramiv GETFUNCTION(__teGetProgramiv)
#define glGetProgramInfoLog GETFUNCTION(__teGetProgramInfoLog)
#define glGetShaderiv GETFUNCTION(__teGetShaderiv)
#define glGetShaderInfoLog GETFUNCTION(__teGetShaderInfoLog)
#define glGetShaderSource GETFUNCTION(__teGetShaderSource)
#define glGetUniformLocation GETFUNCTION(__teGetUniformLocation)
#define glGetUniformfv GETFUNCTION(__teGetUniformfv)
#define glGetUniformiv GETFUNCTION(__teGetUniformiv)
#define glGetVertexAttribdv GETFUNCTION(__teGetVertexAttribdv)
#define glGetVertexAttribfv GETFUNCTION(__teGetVertexAttribfv)
#define glGetVertexAttribiv GETFUNCTION(__teGetVertexAttribiv)
#define glGetVertexAttribPointerv GETFUNCTION(__teGetVertexAttribPointerv)
#define glIsProgram GETFUNCTION(__teIsProgram)
#define glIsShader GETFUNCTION(__teIsShader)
#define glLinkProgram GETFUNCTION(__teLinkProgram)
#define glShaderSource GETFUNCTION(__teShaderSource)
#define glUseProgram GETFUNCTION(__teUseProgram)
#define glUniform1f GETFUNCTION(__teUniform1f)
#define glUniform2f GETFUNCTION(__teUniform2f)
#define glUniform3f GETFUNCTION(__teUniform3f)
#define glUniform4f GETFUNCTION(__teUniform4f)
#define glUniform1i GETFUNCTION(__teUniform1i)
#define glUniform2i GETFUNCTION(__teUniform2i)
#define glUniform3i GETFUNCTION(__teUniform3i)
#define glUniform4i GETFUNCTION(__teUniform4i)
#define glUniform1fv GETFUNCTION(__teUniform1fv)
#define glUniform2fv GETFUNCTION(__teUniform2fv)
#define glUniform3fv GETFUNCTION(__teUniform3fv)
#define glUniform4fv GETFUNCTION(__teUniform4fv)
#define glUniform1iv GETFUNCTION(__teUniform1iv)
#define glUniform2iv GETFUNCTION(__teUniform2iv)
#define glUniform3iv GETFUNCTION(__teUniform3iv)
#define glUniform4iv GETFUNCTION(__teUniform4iv)
#define glUniformMatrix2fv GETFUNCTION(__teUniformMatrix2fv)
#define glUniformMatrix3fv GETFUNCTION(__teUniformMatrix3fv)
#define glUniformMatrix4fv GETFUNCTION(__teUniformMatrix4fv)
#define glValidateProgram GETFUNCTION(__teValidateProgram)
#define glVertexAttrib1d GETFUNCTION(__teVertexAttrib1d)
#define glVertexAttrib1dv GETFUNCTION(__teVertexAttrib1dv)
#define glVertexAttrib1f GETFUNCTION(__teVertexAttrib1f)
#define glVertexAttrib1fv GETFUNCTION(__teVertexAttrib1fv)
#define glVertexAttrib1s GETFUNCTION(__teVertexAttrib1s)
#define glVertexAttrib1sv GETFUNCTION(__teVertexAttrib1sv)
#define glVertexAttrib2d GETFUNCTION(__teVertexAttrib2d)
#define glVertexAttrib2dv GETFUNCTION(__teVertexAttrib2dv)
#define glVertexAttrib2f GETFUNCTION(__teVertexAttrib2f)
#define glVertexAttrib2fv GETFUNCTION(__teVertexAttrib2fv)
#define glVertexAttrib2s GETFUNCTION(__teVertexAttrib2s)
#define glVertexAttrib2sv GETFUNCTION(__teVertexAttrib2sv)
#define glVertexAttrib3d GETFUNCTION(__teVertexAttrib3d)
#define glVertexAttrib3dv GETFUNCTION(__teVertexAttrib3dv)
#define glVertexAttrib3f GETFUNCTION(__teVertexAttrib3f)
#define glVertexAttrib3fv GETFUNCTION(__teVertexAttrib3fv)
#define glVertexAttrib3s GETFUNCTION(__teVertexAttrib3s)
#define glVertexAttrib3sv GETFUNCTION(__teVertexAttrib3sv)
#define glVertexAttrib4Nbv GETFUNCTION(__teVertexAttrib4Nbv)
#define glVertexAttrib4Niv GETFUNCTION(__teVertexAttrib4Niv)
#define glVertexAttrib4Nsv GETFUNCTION(__teVertexAttrib4Nsv)
#define glVertexAttrib4Nub GETFUNCTION(__teVertexAttrib4Nub)
#define glVertexAttrib4Nubv GETFUNCTION(__teVertexAttrib4Nubv)
#define glVertexAttrib4Nuiv GETFUNCTION(__teVertexAttrib4Nuiv)
#define glVertexAttrib4Nusv GETFUNCTION(__teVertexAttrib4Nusv)
#define glVertexAttrib4bv GETFUNCTION(__teVertexAttrib4bv)
#define glVertexAttrib4d GETFUNCTION(__teVertexAttrib4d)
#define glVertexAttrib4dv GETFUNCTION(__teVertexAttrib4dv)
#define glVertexAttrib4f GETFUNCTION(__teVertexAttrib4f)
#define glVertexAttrib4fv GETFUNCTION(__teVertexAttrib4fv)
#define glVertexAttrib4iv GETFUNCTION(__teVertexAttrib4iv)
#define glVertexAttrib4s GETFUNCTION(__teVertexAttrib4s)
#define glVertexAttrib4sv GETFUNCTION(__teVertexAttrib4sv)
#define glVertexAttrib4ubv GETFUNCTION(__teVertexAttrib4ubv)
#define glVertexAttrib4uiv GETFUNCTION(__teVertexAttrib4uiv)
#define glVertexAttrib4usv GETFUNCTION(__teVertexAttrib4usv)
#define glVertexAttribPointer GETFUNCTION(__teVertexAttribPointer)

//OpenGL 2.1 Extensions
#define GL_PIXEL_PACK_BUFFER              0x88EB
#define GL_PIXEL_UNPACK_BUFFER            0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING      0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING    0x88EF
#define GL_FLOAT_MAT2x3                   0x8B65
#define GL_FLOAT_MAT2x4                   0x8B66
#define GL_FLOAT_MAT3x2                   0x8B67
#define GL_FLOAT_MAT3x4                   0x8B68
#define GL_FLOAT_MAT4x2                   0x8B69
#define GL_FLOAT_MAT4x3                   0x8B6A
#define GL_SRGB                           0x8C40
#define GL_SRGB8                          0x8C41
#define GL_SRGB_ALPHA                     0x8C42
#define GL_SRGB8_ALPHA8                   0x8C43
#define GL_COMPRESSED_SRGB                0x8C48
#define GL_COMPRESSED_SRGB_ALPHA          0x8C49
#define GL_CURRENT_RASTER_SECONDARY_COLOR 0x845F
#define GL_SLUMINANCE_ALPHA               0x8C44
#define GL_SLUMINANCE8_ALPHA8             0x8C45
#define GL_SLUMINANCE                     0x8C46
#define GL_SLUMINANCE8                    0x8C47
#define GL_COMPRESSED_SLUMINANCE          0x8C4A
#define GL_COMPRESSED_SLUMINANCE_ALPHA    0x8C4B
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX2X3FVPROC __teUniformMatrix2x3fv;
extern PFNGLUNIFORMMATRIX3X2FVPROC __teUniformMatrix3x2fv;
extern PFNGLUNIFORMMATRIX2X4FVPROC __teUniformMatrix2x4fv;
extern PFNGLUNIFORMMATRIX4X2FVPROC __teUniformMatrix4x2fv;
extern PFNGLUNIFORMMATRIX3X4FVPROC __teUniformMatrix3x4fv;
extern PFNGLUNIFORMMATRIX4X3FVPROC __teUniformMatrix4x3fv;
#define glUniformMatrix2x3fv GETFUNCTION(__teUniformMatrix2x3fv)
#define glUniformMatrix3x2fv GETFUNCTION(__teUniformMatrix3x2fv)
#define glUniformMatrix2x4fv GETFUNCTION(__teUniformMatrix2x4fv)
#define glUniformMatrix4x2fv GETFUNCTION(__teUniformMatrix4x2fv)
#define glUniformMatrix3x4fv GETFUNCTION(__teUniformMatrix3x4fv)
#define glUniformMatrix4x3fv GETFUNCTION(__teUniformMatrix4x3fv)

//OpenGL 3.0 Extensions
typedef unsigned short GLhalf;
#define GL_COMPARE_REF_TO_TEXTURE         0x884E
#define GL_CLIP_DISTANCE0                 0x3000
#define GL_CLIP_DISTANCE1                 0x3001
#define GL_CLIP_DISTANCE2                 0x3002
#define GL_CLIP_DISTANCE3                 0x3003
#define GL_CLIP_DISTANCE4                 0x3004
#define GL_CLIP_DISTANCE5                 0x3005
#define GL_CLIP_DISTANCE6                 0x3006
#define GL_CLIP_DISTANCE7                 0x3007
#define GL_MAX_CLIP_DISTANCES             0x0D32
#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C
#define GL_NUM_EXTENSIONS                 0x821D
#define GL_CONTEXT_FLAGS                  0x821E
#define GL_COMPRESSED_RED                 0x8225
#define GL_COMPRESSED_RG                  0x8226
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x00000001
#define GL_RGBA32F                        0x8814
#define GL_RGB32F                         0x8815
#define GL_RGBA16F                        0x881A
#define GL_RGB16F                         0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER    0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET       0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET       0x8905
#define GL_CLAMP_READ_COLOR               0x891C
#define GL_FIXED_ONLY                     0x891D
#define GL_MAX_VARYING_COMPONENTS         0x8B4B
#define GL_TEXTURE_1D_ARRAY               0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY         0x8C19
#define GL_TEXTURE_2D_ARRAY               0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY         0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY       0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#define GL_R11F_G11F_B10F                 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#define GL_RGB9_E5                        0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#define GL_TEXTURE_SHARED_SIZE            0x8C3F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#define GL_PRIMITIVES_GENERATED           0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#define GL_RASTERIZER_DISCARD             0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#define GL_INTERLEAVED_ATTRIBS            0x8C8C
#define GL_SEPARATE_ATTRIBS               0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER      0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#define GL_RGBA32UI                       0x8D70
#define GL_RGB32UI                        0x8D71
#define GL_RGBA16UI                       0x8D76
#define GL_RGB16UI                        0x8D77
#define GL_RGBA8UI                        0x8D7C
#define GL_RGB8UI                         0x8D7D
#define GL_RGBA32I                        0x8D82
#define GL_RGB32I                         0x8D83
#define GL_RGBA16I                        0x8D88
#define GL_RGB16I                         0x8D89
#define GL_RGBA8I                         0x8D8E
#define GL_RGB8I                          0x8D8F
#define GL_RED_INTEGER                    0x8D94
#define GL_GREEN_INTEGER                  0x8D95
#define GL_BLUE_INTEGER                   0x8D96
#define GL_RGB_INTEGER                    0x8D98
#define GL_RGBA_INTEGER                   0x8D99
#define GL_BGR_INTEGER                    0x8D9A
#define GL_BGRA_INTEGER                   0x8D9B
#define GL_SAMPLER_1D_ARRAY               0x8DC0
#define GL_SAMPLER_2D_ARRAY               0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW        0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#define GL_SAMPLER_CUBE_SHADOW            0x8DC5
#define GL_UNSIGNED_INT_VEC2              0x8DC6
#define GL_UNSIGNED_INT_VEC3              0x8DC7
#define GL_UNSIGNED_INT_VEC4              0x8DC8
#define GL_INT_SAMPLER_1D                 0x8DC9
#define GL_INT_SAMPLER_2D                 0x8DCA
#define GL_INT_SAMPLER_3D                 0x8DCB
#define GL_INT_SAMPLER_CUBE               0x8DCC
#define GL_INT_SAMPLER_1D_ARRAY           0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_1D        0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY  0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#define GL_QUERY_WAIT                     0x8E13
#define GL_QUERY_NO_WAIT                  0x8E14
#define GL_QUERY_BY_REGION_WAIT           0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT        0x8E16
#define GL_BUFFER_ACCESS_FLAGS            0x911F
#define GL_BUFFER_MAP_LENGTH              0x9120
#define GL_BUFFER_MAP_OFFSET              0x9121
#define GL_DEPTH_COMPONENT32F             0x8CAC
#define GL_DEPTH32F_STENCIL8              0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_DEFAULT            0x8218
#define GL_FRAMEBUFFER_UNDEFINED          0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT       0x821A
#define GL_MAX_RENDERBUFFER_SIZE          0x84E8
#define GL_DEPTH_STENCIL                  0x84F9
#define GL_UNSIGNED_INT_24_8              0x84FA
#define GL_DEPTH24_STENCIL8               0x88F0
#define GL_TEXTURE_STENCIL_SIZE           0x88F1
#define GL_TEXTURE_RED_TYPE               0x8C10
#define GL_TEXTURE_GREEN_TYPE             0x8C11
#define GL_TEXTURE_BLUE_TYPE              0x8C12
#define GL_TEXTURE_ALPHA_TYPE             0x8C13
#define GL_TEXTURE_DEPTH_TYPE             0x8C16
#define GL_UNSIGNED_NORMALIZED            0x8C17
#define GL_FRAMEBUFFER_BINDING            0x8CA6
#define GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#define GL_RENDERBUFFER_BINDING           0x8CA7
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#define GL_RENDERBUFFER_SAMPLES           0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_COLOR_ATTACHMENT1              0x8CE1
#define GL_COLOR_ATTACHMENT2              0x8CE2
#define GL_COLOR_ATTACHMENT3              0x8CE3
#define GL_COLOR_ATTACHMENT4              0x8CE4
#define GL_COLOR_ATTACHMENT5              0x8CE5
#define GL_COLOR_ATTACHMENT6              0x8CE6
#define GL_COLOR_ATTACHMENT7              0x8CE7
#define GL_COLOR_ATTACHMENT8              0x8CE8
#define GL_COLOR_ATTACHMENT9              0x8CE9
#define GL_COLOR_ATTACHMENT10             0x8CEA
#define GL_COLOR_ATTACHMENT11             0x8CEB
#define GL_COLOR_ATTACHMENT12             0x8CEC
#define GL_COLOR_ATTACHMENT13             0x8CED
#define GL_COLOR_ATTACHMENT14             0x8CEE
#define GL_COLOR_ATTACHMENT15             0x8CEF
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_STENCIL_ATTACHMENT             0x8D20
#define GL_FRAMEBUFFER                    0x8D40
#define GL_RENDERBUFFER                   0x8D41
#define GL_RENDERBUFFER_WIDTH             0x8D42
#define GL_RENDERBUFFER_HEIGHT            0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT   0x8D44
#define GL_STENCIL_INDEX1                 0x8D46
#define GL_STENCIL_INDEX4                 0x8D47
#define GL_STENCIL_INDEX8                 0x8D48
#define GL_STENCIL_INDEX16                0x8D49
#define GL_RENDERBUFFER_RED_SIZE          0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE        0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE         0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE        0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE        0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE      0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_MAX_SAMPLES                    0x8D57
#define GL_INDEX                          0x8222
#define GL_TEXTURE_LUMINANCE_TYPE         0x8C14
#define GL_TEXTURE_INTENSITY_TYPE         0x8C15
#define GL_FRAMEBUFFER_SRGB               0x8DB9
#define GL_HALF_FLOAT                     0x140B
#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT       0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT      0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT         0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT         0x0020
#define GL_COMPRESSED_RED_RGTC1           0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1    0x8DBC
#define GL_COMPRESSED_RG_RGTC2            0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2     0x8DBE
#define GL_RG                             0x8227
#define GL_RG_INTEGER                     0x8228
#define GL_R8                             0x8229
#define GL_R16                            0x822A
#define GL_RG8                            0x822B
#define GL_RG16                           0x822C
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_R8I                            0x8231
#define GL_R8UI                           0x8232
#define GL_R16I                           0x8233
#define GL_R16UI                          0x8234
#define GL_R32I                           0x8235
#define GL_R32UI                          0x8236
#define GL_RG8I                           0x8237
#define GL_RG8UI                          0x8238
#define GL_RG16I                          0x8239
#define GL_RG16UI                         0x823A
#define GL_RG32I                          0x823B
#define GL_RG32UI                         0x823C
#define GL_VERTEX_ARRAY_BINDING           0x85B5
#define GL_CLAMP_VERTEX_COLOR             0x891A
#define GL_CLAMP_FRAGMENT_COLOR           0x891B
#define GL_ALPHA_INTEGER                  0x8D97
typedef void (APIENTRYP PFNGLCOLORMASKIPROC) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum target, GLuint index, GLboolean *data);
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum target, GLuint index, GLint *data);
typedef void (APIENTRYP PFNGLENABLEIPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLDISABLEIPROC) (GLenum target, GLuint index);
typedef GLboolean(APIENTRYP PFNGLISENABLEDIPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitiveMode);
typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLCLAMPCOLORPROC) (GLenum target, GLenum clamp);
typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC) (GLuint id, GLenum mode);
typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERPROC) (void);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint index, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IPROC) (GLuint index, GLint x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IPROC) (GLuint index, GLint x, GLint y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IPROC) (GLuint index, GLint x, GLint y, GLint z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIPROC) (GLuint index, GLuint x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIPROC) (GLuint index, GLuint x, GLuint y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4BVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4USVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint program, GLint location, GLuint *params);
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC) (GLuint program, GLuint color, const GLchar *name);
typedef GLint(APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, const GLuint *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef const GLubyte *(APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
typedef GLboolean(APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, const GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef GLboolean(APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, const GLuint *framebuffers);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
typedef GLenum(APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum target);
typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void *(APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLboolean(APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
extern PFNGLCOLORMASKIPROC __teColorMaski;
extern PFNGLGETBOOLEANI_VPROC __teGetBooleani_v;
extern PFNGLGETINTEGERI_VPROC __teGetIntegeri_v;
extern PFNGLENABLEIPROC __teEnablei;
extern PFNGLDISABLEIPROC __teDisablei;
extern PFNGLISENABLEDIPROC __teIsEnabledi;
extern PFNGLBEGINTRANSFORMFEEDBACKPROC __teBeginTransformFeedback;
extern PFNGLENDTRANSFORMFEEDBACKPROC __teEndTransformFeedback;
extern PFNGLBINDBUFFERRANGEPROC __teBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC __teBindBufferBase;
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC __teTransformFeedbackVaryings;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC __teGetTransformFeedbackVarying;
extern PFNGLCLAMPCOLORPROC __teClampColor;
extern PFNGLBEGINCONDITIONALRENDERPROC __teBeginConditionalRender;
extern PFNGLENDCONDITIONALRENDERPROC __teEndConditionalRender;
extern PFNGLVERTEXATTRIBIPOINTERPROC __teVertexAttribIPointer;
extern PFNGLGETVERTEXATTRIBIIVPROC __teGetVertexAttribIiv;
extern PFNGLGETVERTEXATTRIBIUIVPROC __teGetVertexAttribIuiv;
extern PFNGLVERTEXATTRIBI1IPROC __teVertexAttribI1i;
extern PFNGLVERTEXATTRIBI2IPROC __teVertexAttribI2i;
extern PFNGLVERTEXATTRIBI3IPROC __teVertexAttribI3i;
extern PFNGLVERTEXATTRIBI4IPROC __teVertexAttribI4i;
extern PFNGLVERTEXATTRIBI1UIPROC __teVertexAttribI1ui;
extern PFNGLVERTEXATTRIBI2UIPROC __teVertexAttribI2ui;
extern PFNGLVERTEXATTRIBI3UIPROC __teVertexAttribI3ui;
extern PFNGLVERTEXATTRIBI4UIPROC __teVertexAttribI4ui;
extern PFNGLVERTEXATTRIBI1IVPROC __teVertexAttribI1iv;
extern PFNGLVERTEXATTRIBI2IVPROC __teVertexAttribI2iv;
extern PFNGLVERTEXATTRIBI3IVPROC __teVertexAttribI3iv;
extern PFNGLVERTEXATTRIBI4IVPROC __teVertexAttribI4iv;
extern PFNGLVERTEXATTRIBI1UIVPROC __teVertexAttribI1uiv;
extern PFNGLVERTEXATTRIBI2UIVPROC __teVertexAttribI2uiv;
extern PFNGLVERTEXATTRIBI3UIVPROC __teVertexAttribI3uiv;
extern PFNGLVERTEXATTRIBI4UIVPROC __teVertexAttribI4uiv;
extern PFNGLVERTEXATTRIBI4BVPROC __teVertexAttribI4bv;
extern PFNGLVERTEXATTRIBI4SVPROC __teVertexAttribI4sv;
extern PFNGLVERTEXATTRIBI4UBVPROC __teVertexAttribI4ubv;
extern PFNGLVERTEXATTRIBI4USVPROC __teVertexAttribI4usv;
extern PFNGLGETUNIFORMUIVPROC __teGetUniformuiv;
extern PFNGLBINDFRAGDATALOCATIONPROC __teBindFragDataLocation;
extern PFNGLGETFRAGDATALOCATIONPROC __teGetFragDataLocation;
extern PFNGLUNIFORM1UIPROC __teUniform1ui;
extern PFNGLUNIFORM2UIPROC __teUniform2ui;
extern PFNGLUNIFORM3UIPROC __teUniform3ui;
extern PFNGLUNIFORM4UIPROC __teUniform4ui;
extern PFNGLUNIFORM1UIVPROC __teUniform1uiv;
extern PFNGLUNIFORM2UIVPROC __teUniform2uiv;
extern PFNGLUNIFORM3UIVPROC __teUniform3uiv;
extern PFNGLUNIFORM4UIVPROC __teUniform4uiv;
extern PFNGLTEXPARAMETERIIVPROC __teTexParameterIiv;
extern PFNGLTEXPARAMETERIUIVPROC __teTexParameterIuiv;
extern PFNGLGETTEXPARAMETERIIVPROC __teGetTexParameterIiv;
extern PFNGLGETTEXPARAMETERIUIVPROC __teGetTexParameterIuiv;
extern PFNGLCLEARBUFFERIVPROC __teClearBufferiv;
extern PFNGLCLEARBUFFERUIVPROC __teClearBufferuiv;
extern PFNGLCLEARBUFFERFVPROC __teClearBufferfv;
extern PFNGLCLEARBUFFERFIPROC __teClearBufferfi;
extern PFNGLGETSTRINGIPROC __teGetStringi;
extern PFNGLISRENDERBUFFERPROC __teIsRenderbuffer;
extern PFNGLBINDRENDERBUFFERPROC __teBindRenderbuffer;
extern PFNGLDELETERENDERBUFFERSPROC __teDeleteRenderbuffers;
extern PFNGLGENRENDERBUFFERSPROC __teGenRenderbuffers;
extern PFNGLRENDERBUFFERSTORAGEPROC __teRenderbufferStorage;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC __teGetRenderbufferParameteriv;
extern PFNGLISFRAMEBUFFERPROC __teIsFramebuffer;
extern PFNGLBINDFRAMEBUFFERPROC __teBindFramebuffer;
extern PFNGLDELETEFRAMEBUFFERSPROC __teDeleteFramebuffers;
extern PFNGLGENFRAMEBUFFERSPROC __teGenFramebuffers;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC __teCheckFramebufferStatus;
extern PFNGLFRAMEBUFFERTEXTURE1DPROC __teFramebufferTexture1D;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC __teFramebufferTexture2D;
extern PFNGLFRAMEBUFFERTEXTURE3DPROC __teFramebufferTexture3D;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC __teFramebufferRenderbuffer;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC __teGetFramebufferAttachmentParameteriv;
extern PFNGLGENERATEMIPMAPPROC __teGenerateMipmap;
extern PFNGLBLITFRAMEBUFFERPROC __teBlitFramebuffer;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC __teRenderbufferStorageMultisample;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC __teFramebufferTextureLayer;
extern PFNGLMAPBUFFERRANGEPROC __teMapBufferRange;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC __teFlushMappedBufferRange;
extern PFNGLBINDVERTEXARRAYPROC __teBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC __teDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC __teGenVertexArrays;
extern PFNGLISVERTEXARRAYPROC __teIsVertexArray;
#define glColorMaski GETFUNCTION(__teColorMaski)
#define glGetBooleani_v GETFUNCTION(__teGetBooleani_v)
#define glGetIntegeri_v GETFUNCTION(__teGetIntegeri_v)
#define glEnablei GETFUNCTION(__teEnablei)
#define glDisablei GETFUNCTION(__teDisablei)
#define glIsEnabledi GETFUNCTION(__teIsEnabledi)
#define glBeginTransformFeedback GETFUNCTION(__teBeginTransformFeedback)
#define glEndTransformFeedback GETFUNCTION(__teEndTransformFeedback)
#define glBindBufferRange GETFUNCTION(__teBindBufferRange)
#define glBindBufferBase GETFUNCTION(__teBindBufferBase)
#define glTransformFeedbackVaryings GETFUNCTION(__teTransformFeedbackVaryings)
#define glGetTransformFeedbackVarying GETFUNCTION(__teGetTransformFeedbackVarying)
#define glClampColor GETFUNCTION(__teClampColor)
#define glBeginConditionalRender GETFUNCTION(__teBeginConditionalRender)
#define glEndConditionalRender GETFUNCTION(__teEndConditionalRender)
#define glVertexAttribIPointer GETFUNCTION(__teVertexAttribIPointer)
#define glGetVertexAttribIiv GETFUNCTION(__teGetVertexAttribIiv)
#define glGetVertexAttribIuiv GETFUNCTION(__teGetVertexAttribIuiv)
#define glVertexAttribI1i GETFUNCTION(__teVertexAttribI1i)
#define glVertexAttribI2i GETFUNCTION(__teVertexAttribI2i)
#define glVertexAttribI3i GETFUNCTION(__teVertexAttribI3i)
#define glVertexAttribI4i GETFUNCTION(__teVertexAttribI4i)
#define glVertexAttribI1ui GETFUNCTION(__teVertexAttribI1ui)
#define glVertexAttribI2ui GETFUNCTION(__teVertexAttribI2ui)
#define glVertexAttribI3ui GETFUNCTION(__teVertexAttribI3ui)
#define glVertexAttribI4ui GETFUNCTION(__teVertexAttribI4ui)
#define glVertexAttribI1iv GETFUNCTION(__teVertexAttribI1iv)
#define glVertexAttribI2iv GETFUNCTION(__teVertexAttribI2iv)
#define glVertexAttribI3iv GETFUNCTION(__teVertexAttribI3iv)
#define glVertexAttribI4iv GETFUNCTION(__teVertexAttribI4iv)
#define glVertexAttribI1uiv GETFUNCTION(__teVertexAttribI1uiv)
#define glVertexAttribI2uiv GETFUNCTION(__teVertexAttribI2uiv)
#define glVertexAttribI3uiv GETFUNCTION(__teVertexAttribI3uiv)
#define glVertexAttribI4uiv GETFUNCTION(__teVertexAttribI4uiv)
#define glVertexAttribI4bv GETFUNCTION(__teVertexAttribI4bv)
#define glVertexAttribI4sv GETFUNCTION(__teVertexAttribI4sv)
#define glVertexAttribI4ubv GETFUNCTION(__teVertexAttribI4ubv)
#define glVertexAttribI4usv GETFUNCTION(__teVertexAttribI4usv)
#define glGetUniformuiv GETFUNCTION(__teGetUniformuiv)
#define glBindFragDataLocation GETFUNCTION(__teBindFragDataLocation)
#define glGetFragDataLocation GETFUNCTION(__teGetFragDataLocation)
#define glUniform1ui GETFUNCTION(__teUniform1ui)
#define glUniform2ui GETFUNCTION(__teUniform2ui)
#define glUniform3ui GETFUNCTION(__teUniform3ui)
#define glUniform4ui GETFUNCTION(__teUniform4ui)
#define glUniform1uiv GETFUNCTION(__teUniform1uiv)
#define glUniform2uiv GETFUNCTION(__teUniform2uiv)
#define glUniform3uiv GETFUNCTION(__teUniform3uiv)
#define glUniform4uiv GETFUNCTION(__teUniform4uiv)
#define glTexParameterIiv GETFUNCTION(__teTexParameterIiv)
#define glTexParameterIuiv GETFUNCTION(__teTexParameterIuiv)
#define glGetTexParameterIiv GETFUNCTION(__teGetTexParameterIiv)
#define glGetTexParameterIuiv GETFUNCTION(__teGetTexParameterIuiv)
#define glClearBufferiv GETFUNCTION(__teClearBufferiv)
#define glClearBufferuiv GETFUNCTION(__teClearBufferuiv)
#define glClearBufferfv GETFUNCTION(__teClearBufferfv)
#define glClearBufferfi GETFUNCTION(__teClearBufferfi)
#define glGetStringi GETFUNCTION(__teGetStringi)
#define glIsRenderbuffer GETFUNCTION(__teIsRenderbuffer)
#define glBindRenderbuffer GETFUNCTION(__teBindRenderbuffer)
#define glDeleteRenderbuffers GETFUNCTION(__teDeleteRenderbuffers)
#define glGenRenderbuffers GETFUNCTION(__teGenRenderbuffers)
#define glRenderbufferStorage GETFUNCTION(__teRenderbufferStorage)
#define glGetRenderbufferParameteriv GETFUNCTION(__teGetRenderbufferParameteriv)
#define glIsFramebuffer GETFUNCTION(__teIsFramebuffer)
#define glBindFramebuffer GETFUNCTION(__teBindFramebuffer)
#define glDeleteFramebuffers GETFUNCTION(__teDeleteFramebuffers)
#define glGenFramebuffers GETFUNCTION(__teGenFramebuffers)
#define glCheckFrameBufferStatus GETFUNCTION(__teCheckFramebufferStatus)
#define glFramebufferTexture1D GETFUNCTION(__teFramebufferTexture1D)
#define glFramebufferTexture2D GETFUNCTION(__teFramebufferTexture2D)
#define glFramebufferTexture3D GETFUNCTION(__teFramebufferTexture3D)
#define glFramebufferRenderbuffer GETFUNCTION(__teFramebufferRenderbuffer)
#define glGetFramebufferAttachmentParameteriv GETFUNCTION(__teGetFramebufferAttachmentParameteriv)
#define glGenerateMipmap GETFUNCTION(__teGenerateMipmap)
#define glBlitFramebuffer GETFUNCTION(__teBlitFramebuffer)
#define glRenderbufferStorageMultisample GETFUNCTION(__teRenderbufferStorageMultisample)
#define glFramebufferTextureLayer GETFUNCTION(__teFramebufferTextureLayer)
#define glMapBufferRange GETFUNCTION(__teMapBufferRange)
#define glFlushMappedBufferRange GETFUNCTION(__teFlushMappedBufferRange)
#define glBindVertexArray GETFUNCTION(__teBindVertexArray)
#define glDeleteVertexArrays GETFUNCTION(__teDeleteVertexArrays)
#define glGenVertexArrays GETFUNCTION(__teGenVertexArrays)
#define glIsVertexArray GETFUNCTION(__teIsVertexArray)

//OpenGL 3.1 Extensions
#define GL_SAMPLER_2D_RECT                0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW         0x8B64
#define GL_SAMPLER_BUFFER                 0x8DC2
#define GL_INT_SAMPLER_2D_RECT            0x8DCD
#define GL_INT_SAMPLER_BUFFER             0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT   0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_BUFFER    0x8DD8
#define GL_TEXTURE_BUFFER                 0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE        0x8C2B
#define GL_TEXTURE_BINDING_BUFFER         0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
#define GL_TEXTURE_RECTANGLE              0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE      0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE        0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE     0x84F8
#define GL_R8_SNORM                       0x8F94
#define GL_RG8_SNORM                      0x8F95
#define GL_RGB8_SNORM                     0x8F96
#define GL_RGBA8_SNORM                    0x8F97
#define GL_R16_SNORM                      0x8F98
#define GL_RG16_SNORM                     0x8F99
#define GL_RGB16_SNORM                    0x8F9A
#define GL_RGBA16_SNORM                   0x8F9B
#define GL_SIGNED_NORMALIZED              0x8F9C
#define GL_PRIMITIVE_RESTART              0x8F9D
#define GL_PRIMITIVE_RESTART_INDEX        0x8F9E
#define GL_COPY_READ_BUFFER               0x8F36
#define GL_COPY_WRITE_BUFFER              0x8F37
#define GL_UNIFORM_BUFFER                 0x8A11
#define GL_UNIFORM_BUFFER_BINDING         0x8A28
#define GL_UNIFORM_BUFFER_START           0x8A29
#define GL_UNIFORM_BUFFER_SIZE            0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS      0x8A2B
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS    0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS    0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS    0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE         0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS          0x8A36
#define GL_UNIFORM_TYPE                   0x8A37
#define GL_UNIFORM_SIZE                   0x8A38
#define GL_UNIFORM_NAME_LENGTH            0x8A39
#define GL_UNIFORM_BLOCK_INDEX            0x8A3A
#define GL_UNIFORM_OFFSET                 0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE           0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE          0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR           0x8A3E
#define GL_UNIFORM_BLOCK_BINDING          0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE        0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH      0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS  0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_INVALID_INDEX                  0xFFFFFFFFu
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
typedef void (APIENTRYP PFNGLTEXBUFFERPROC) (GLenum target, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC) (GLuint index);
typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
typedef GLuint(APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, const GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
extern PFNGLDRAWARRAYSINSTANCEDPROC __teDrawArraysInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDPROC __teDrawElementsInstanced;
extern PFNGLTEXBUFFERPROC __teTexBuffer;
extern PFNGLPRIMITIVERESTARTINDEXPROC __tePrimitiveRestartIndex;
extern PFNGLCOPYBUFFERSUBDATAPROC __teCopyBufferSubdata;
extern PFNGLGETUNIFORMINDICESPROC __teGetUniformIndices;
extern PFNGLGETACTIVEUNIFORMSIVPROC __teGetActiveUniformsiv;
extern PFNGLGETACTIVEUNIFORMNAMEPROC __teGetActiveUniformName;
extern PFNGLGETUNIFORMBLOCKINDEXPROC __teGetUniformBlockIndex;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC __teGetActiveUniformBlockiv;
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC __teGetActiveUniformBlockName;
extern PFNGLUNIFORMBLOCKBINDINGPROC __teUniformBlockBinding;
#define glDrawArraysInstanced GETFUNCTION(__teDrawArraysInstanced)
#define glDrawElementsInstanced GETFUNCTION(__teDrawElementsInstanced)
#define glTexBuffer GETFUNCTION(__teTexBuffer)
#define glPrimtiveRestartIndex GETFUNCTION(__tePrimitiveRestartIndex)
#define glCopyBufferSubdata GETFUNCTION(__teCopyBufferSubdata)
#define glGetUniformIndices GETFUNCTION(__teGetUniformIndices)
#define glGetActiveUniformsiv GETFUNCTION(__teGetActiveUniformsiv)
#define glGetActiveUniformName GETFUNCTION(__teGetActiveUniformName)
#define glGetUniformBlockIndex GETFUNCTION(__teGetUniformBlockIndex)
#define glGetActiveUniformBlockiv GETFUNCTION(__teGetActiveUniformBlockiv)
#define glGetActiveUniformBlockName GETFUNCTION(__teGetActiveUniformBlockName)
#define glUniformBlockBinding GETFUNCTION(__teUniformBlockBinding)

//OpenGL 3.2 Extensions
typedef struct __GLsync *GLsync;
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
typedef uint64_t GLuint64;
typedef int64_t GLint64;
#define GL_CONTEXT_CORE_PROFILE_BIT       0x00000001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_LINES_ADJACENCY                0x000A
#define GL_LINE_STRIP_ADJACENCY           0x000B
#define GL_TRIANGLES_ADJACENCY            0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#define GL_PROGRAM_POINT_SIZE             0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#define GL_GEOMETRY_SHADER                0x8DD9
#define GL_GEOMETRY_VERTICES_OUT          0x8916
#define GL_GEOMETRY_INPUT_TYPE            0x8917
#define GL_GEOMETRY_OUTPUT_TYPE           0x8918
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES   0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS   0x9122
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS  0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS  0x9125
#define GL_CONTEXT_PROFILE_MASK           0x9126
#define GL_DEPTH_CLAMP                    0x864F
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8E4C
#define GL_FIRST_VERTEX_CONVENTION        0x8E4D
#define GL_LAST_VERTEX_CONVENTION         0x8E4E
#define GL_PROVOKING_VERTEX               0x8E4F
#define GL_TEXTURE_CUBE_MAP_SEAMLESS      0x884F
#define GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#define GL_OBJECT_TYPE                    0x9112
#define GL_SYNC_CONDITION                 0x9113
#define GL_SYNC_STATUS                    0x9114
#define GL_SYNC_FLAGS                     0x9115
#define GL_SYNC_FENCE                     0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#define GL_UNSIGNALED                     0x9118
#define GL_SIGNALED                       0x9119
#define GL_ALREADY_SIGNALED               0x911A
#define GL_TIMEOUT_EXPIRED                0x911B
#define GL_CONDITION_SATISFIED            0x911C
#define GL_WAIT_FAILED                    0x911D
#define GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#define GL_SYNC_FLUSH_COMMANDS_BIT        0x00000001
#define GL_SAMPLE_POSITION                0x8E50
#define GL_SAMPLE_MASK                    0x8E51
#define GL_SAMPLE_MASK_VALUE              0x8E52
#define GL_MAX_SAMPLE_MASK_WORDS          0x8E59
#define GL_TEXTURE_2D_MULTISAMPLE         0x9100
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE   0x9101
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_SAMPLES                0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_SAMPLER_2D_MULTISAMPLE         0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
#define GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES      0x910F
#define GL_MAX_INTEGER_SAMPLES            0x9110
typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
typedef void (APIENTRYP PFNGLPROVOKINGVERTEXPROC) (GLenum mode);
typedef GLsync(APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
typedef GLboolean(APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
typedef void (APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
typedef GLenum(APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum target, GLuint index, GLint64 *data);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum target, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLTEXIMAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXIMAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint index, GLfloat *val);
typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint index, GLbitfield mask);
extern PFNGLDRAWELEMENTSBASEVERTEXPROC __teDrawElementsBaseVertex;
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC __teDrawRangeElementsBaseVertex;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC __teDrawElementsInstancedBaseVertex;
extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC __teMultiDrawElementsBaseVertex;
extern PFNGLPROVOKINGVERTEXPROC __teProvokingVertex;
extern PFNGLFENCESYNCPROC __teFenceSync;
extern PFNGLISSYNCPROC __teIsSync;
extern PFNGLDELETESYNCPROC __teDeleteSync;
extern PFNGLCLIENTWAITSYNCPROC __teClientWaitSync;
extern PFNGLWAITSYNCPROC __teWaitSync;
extern PFNGLGETINTEGER64VPROC __teGetInteger64v;
extern PFNGLGETSYNCIVPROC __teGetSynciv;
extern PFNGLGETINTEGER64I_VPROC __teGetInteger64i_v;
extern PFNGLGETBUFFERPARAMETERI64VPROC __teGetBufferParameteri64v;
extern PFNGLFRAMEBUFFERTEXTUREPROC __teFramebufferTexture;
extern PFNGLTEXIMAGE2DMULTISAMPLEPROC __teTexImage2DMultisample;
extern PFNGLTEXIMAGE3DMULTISAMPLEPROC __teTexImage3DMultisample;
extern PFNGLGETMULTISAMPLEFVPROC __teGetMultisamplefv;
extern PFNGLSAMPLEMASKIPROC __teSampleMaski;
#define glDrawElementsBaseVertex GETFUNCTION(__teDrawElementsBaseVertex)
#define glDrawRangeElementsBaseVertex GETFUNCTION(__teDrawRangeElementsBaseVertex)
#define glDrawElementsInstancedBaseVertex GETFUNCTION(__teDrawElementsInstancedBaseVertex)
#define glMultiDrawElementsBaseVertex GETFUNCTION(__teMultiDrawElementsBaseVertex)
#define glProvokingVertex GETFUNCTION(__teProvokingVertex)
#define glFenceSync GETFUNCTION(__teFenceSync)
#define glIsSync GETFUNCTION(__teIsSync)
#define glDeleteSync GETFUNCTION(__teDeleteSync)
#define glClientWaitSync GETFUNCTION(__teClientWaitSync)
#define glWaitSync GETFUNCTION(__teWaitSync)
#define glGetInteger64v GETFUNCTION(__teGetInteger64v)
#define glGetSynciv GETFUNCTION(__teGetSynciv)
#define glGetInteger64i_v GETFUNCTION(__teGetInteger64i_v)
#define glGetBufferParameteri64v GETFUNCTION(__teGetBufferParameteri64v)
#define glFramebufferTexture GETFUNCTION(__teFramebufferTexture)
#define glTexImage2DMultiSample GETFUNCTION(__teTexImage2DMultisample)
#define glTexImage3DMultisample GETFUNCTION(__teTexImage3DMultisample)
#define glGetMultisamplefv GETFUNCTION(__teGetMultisamplefv)
#define glSampleMaski GETFUNCTION(__teSampleMaski)

//OpenGL 3.3 Extensions
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR    0x88FE
#define GL_SRC1_COLOR                     0x88F9
#define GL_ONE_MINUS_SRC1_COLOR           0x88FA
#define GL_ONE_MINUS_SRC1_ALPHA           0x88FB
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS   0x88FC
#define GL_ANY_SAMPLES_PASSED             0x8C2F
#define GL_SAMPLER_BINDING                0x8919
#define GL_RGB10_A2UI                     0x906F
#define GL_TEXTURE_SWIZZLE_R              0x8E42
#define GL_TEXTURE_SWIZZLE_G              0x8E43
#define GL_TEXTURE_SWIZZLE_B              0x8E44
#define GL_TEXTURE_SWIZZLE_A              0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA           0x8E46
#define GL_TIME_ELAPSED                   0x88BF
#define GL_TIMESTAMP                      0x8E28
#define GL_INT_2_10_10_10_REV             0x8D9F
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) (GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
typedef GLint(APIENTRYP PFNGLGETFRAGDATAINDEXPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei count, GLuint *samplers);
typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei count, const GLuint *samplers);
typedef GLboolean(APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
typedef void (APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, const GLfloat *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, const GLuint *param);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC) (GLuint id, GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC) (GLuint id, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC) (GLuint id, GLenum pname, GLuint64 *params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint index, GLuint divisor);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXP2UIPROC) (GLenum type, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXP2UIVPROC) (GLenum type, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXP3UIPROC) (GLenum type, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXP3UIVPROC) (GLenum type, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXP4UIPROC) (GLenum type, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXP4UIVPROC) (GLenum type, const GLuint *value);
typedef void (APIENTRYP PFNGLTEXCOORDP1UIPROC) (GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLTEXCOORDP1UIVPROC) (GLenum type, const GLuint *coords);
typedef void (APIENTRYP PFNGLTEXCOORDP2UIPROC) (GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLTEXCOORDP2UIVPROC) (GLenum type, const GLuint *coords);
typedef void (APIENTRYP PFNGLTEXCOORDP3UIPROC) (GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLTEXCOORDP3UIVPROC) (GLenum type, const GLuint *coords);
typedef void (APIENTRYP PFNGLTEXCOORDP4UIPROC) (GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLTEXCOORDP4UIVPROC) (GLenum type, const GLuint *coords);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIPROC) (GLenum texture, GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIVPROC) (GLenum texture, GLenum type, const GLuint *coords);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIPROC) (GLenum texture, GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIVPROC) (GLenum texture, GLenum type, const GLuint *coords);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIPROC) (GLenum texture, GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIVPROC) (GLenum texture, GLenum type, const GLuint *coords);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIPROC) (GLenum texture, GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIVPROC) (GLenum texture, GLenum type, const GLuint *coords);
typedef void (APIENTRYP PFNGLNORMALP3UIPROC) (GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLNORMALP3UIVPROC) (GLenum type, const GLuint *coords);
typedef void (APIENTRYP PFNGLCOLORP3UIPROC) (GLenum type, GLuint color);
typedef void (APIENTRYP PFNGLCOLORP3UIVPROC) (GLenum type, const GLuint *color);
typedef void (APIENTRYP PFNGLCOLORP4UIPROC) (GLenum type, GLuint color);
typedef void (APIENTRYP PFNGLCOLORP4UIVPROC) (GLenum type, const GLuint *color);
typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIPROC) (GLenum type, GLuint color);
typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIVPROC) (GLenum type, const GLuint *color);
extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC __teBindFragDataLocationIndexed;
extern PFNGLGETFRAGDATAINDEXPROC __teGetFragDataIndex;
extern PFNGLGENSAMPLERSPROC __teGenSamplers;
extern PFNGLDELETESAMPLERSPROC __teDeleteSamplers;
extern PFNGLISSAMPLERPROC __teIsSampler;
extern PFNGLBINDSAMPLERPROC __teBindSampler;
extern PFNGLSAMPLERPARAMETERIPROC __teSamplerParameteri;
extern PFNGLSAMPLERPARAMETERIVPROC __teSamplerParameteriv;
extern PFNGLSAMPLERPARAMETERFPROC __teSamplerParameterf;
extern PFNGLSAMPLERPARAMETERFVPROC __teSamplerParameterfv;
extern PFNGLSAMPLERPARAMETERIIVPROC __teSamplerParameterIiv;
extern PFNGLSAMPLERPARAMETERIUIVPROC __teSamplerParameterIuiv;
extern PFNGLGETSAMPLERPARAMETERIVPROC __teGetSamplerParameteriv;
extern PFNGLGETSAMPLERPARAMETERIIVPROC __teGetSamplerParameterIiv;
extern PFNGLGETSAMPLERPARAMETERFVPROC __teGetSamplerParameterfv;
extern PFNGLGETSAMPLERPARAMETERIUIVPROC __teGetSamplerParameterIuiv;
extern PFNGLQUERYCOUNTERPROC __teQueryCounter;
extern PFNGLGETQUERYOBJECTI64VPROC __teGetQueryObjecti64v;
extern PFNGLGETQUERYOBJECTUI64VPROC __teGetQueryObjectui64v;
extern PFNGLVERTEXATTRIBDIVISORPROC __teVertexAttribDivisor;
extern PFNGLVERTEXATTRIBP1UIPROC __teVertexAttribP1ui;
extern PFNGLVERTEXATTRIBP1UIVPROC __teVertexAttribP1uiv;
extern PFNGLVERTEXATTRIBP2UIPROC __teVertexAttribP2ui;
extern PFNGLVERTEXATTRIBP2UIVPROC __teVertexAttribP2uiv;
extern PFNGLVERTEXATTRIBP3UIPROC __teVertexAttribP3ui;
extern PFNGLVERTEXATTRIBP3UIVPROC __teVertexAttribP3uiv;
extern PFNGLVERTEXATTRIBP4UIPROC __teVertexAttribP4ui;
extern PFNGLVERTEXATTRIBP4UIVPROC __teVertexAttribP4uiv;
extern PFNGLVERTEXP2UIPROC __teVertexP2ui;
extern PFNGLVERTEXP2UIVPROC __teVertexP2uiv;
extern PFNGLVERTEXP3UIPROC __teVertexP3ui;
extern PFNGLVERTEXP3UIVPROC __teVertexP3uiv;
extern PFNGLVERTEXP4UIPROC __teVertexP4ui;
extern PFNGLVERTEXP4UIVPROC __teVertexP4uiv;
extern PFNGLTEXCOORDP1UIPROC __teTexCoordP1ui;
extern PFNGLTEXCOORDP1UIVPROC __teTexCoordP1uiv;
extern PFNGLTEXCOORDP2UIPROC __teTexCoordP2ui;
extern PFNGLTEXCOORDP2UIVPROC __teTexCoordP2uiv;
extern PFNGLTEXCOORDP3UIPROC __teTexCoordP3ui;
extern PFNGLTEXCOORDP3UIVPROC __teTexCoordP3uiv;
extern PFNGLTEXCOORDP4UIPROC __teTexCoordP4ui;
extern PFNGLTEXCOORDP4UIVPROC __teTexCoordP4uiv;
extern PFNGLMULTITEXCOORDP1UIPROC __teMultiTexCoordP1ui;
extern PFNGLMULTITEXCOORDP1UIVPROC __teMultiTexCoordP1uiv;
extern PFNGLMULTITEXCOORDP2UIPROC __teMultiTexCoordP2ui;
extern PFNGLMULTITEXCOORDP2UIVPROC __teMultiTexCoordP2uiv;
extern PFNGLMULTITEXCOORDP3UIPROC __teMultiTexCoordP3ui;
extern PFNGLMULTITEXCOORDP3UIVPROC __teMultiTexCoordP3uiv;
extern PFNGLMULTITEXCOORDP4UIPROC __teMultiTexCoordP4ui;
extern PFNGLMULTITEXCOORDP4UIVPROC __teMultiTexCoordP4uiv;
extern PFNGLNORMALP3UIPROC __teNormalP3ui;
extern PFNGLNORMALP3UIVPROC __teNormalP3uiv;
extern PFNGLCOLORP3UIPROC __teColorP3ui;
extern PFNGLCOLORP3UIVPROC __teColorP3uiv;
extern PFNGLCOLORP4UIPROC __teColorP4ui;
extern PFNGLCOLORP4UIVPROC __teColorP4uiv;
extern PFNGLSECONDARYCOLORP3UIPROC __teSecondaryColorP3ui;
extern PFNGLSECONDARYCOLORP3UIVPROC __teSecondaryColorP3uiv;
#define glBindFragDataLocationIndexed GETFUNCTION(__teBindFragDataLocationIndexed)
#define glGetFragDataIndex GETFUNCTION(__teGetFragDataIndex)
#define glGenSamplers GETFUNCTION(__teGenSamplers)
#define glDeleteSamplers GETFUNCTION(__teDeleteSamplers)
#define glIsSampler GETFUNCTION(__teIsShader)
#define glBindSampler GETFUNCTION(__teBindSampler)
#define glSamplerParameteri GETFUNCTION(__teSamplerParameteri)
#define glSamplerParameteriv GETFUNCTION(__teSamplerParameteriv)
#define glSamplerParameterf GETFUNCTION(__teSamplerParameterf)
#define glSamplerParameterfv GETFUNCTION(__teSamplerParameterfv)
#define glSamplerParameterIiv GETFUNCTION(__teSamplerParameterIiv)
#define glSamplerParameterIuiv GETFUNCTION(__teSamplerParameterIuiv)
#define glGetSamplerParameteriv GETFUNCTION(__teGetSamplerParameteriv)
#define glGetSamplerParameterIiv GETFUNCTION(__teGetSamplerParameterIiv)
#define glGetSamplerParameterfv GETFUNCTION(__teGetSamplerParameterfv)
#define glGetSamplerParameterIuiv GETFUNCTION(__teGetSamplerParameterIuiv)
#define glQueryCounter GETFUNCTION(__teQueryCounter)
#define glGetQueryObjecti64v GETFUNCTION(__teGetQueryObjecti64v)
#define glGetQueryObjectui64v GETFUNCTION(__teGetQueryObjectui64v)
#define glVertexAttribDivisor GETFUNCTION(__teVertexAttribDivisor)
#define glVertexAttribP1ui GETFUNCTION(__teVertexAttribP1ui)
#define glVertexAttribP1uiv GETFUNCTION(__teVertexAttribP1uiv)
#define glVertexAttribP2ui GETFUNCTION(__teVertexAttribP2ui)
#define glVertexAttribP2uiv GETFUNCTION(__teVertexAttribP2uiv)
#define glVertexAttribP3ui GETFUNCTION(__teVertexAttribP3ui)
#define glVertexAttribP3uiv GETFUNCTION(__teVertexAttribP3uiv)
#define glVertexAttribP4ui GETFUNCTION(__teVertexAttribP4ui)
#define glVertexAttribP4uiv GETFUNCTION(__teVertexAttribP4uiv)
#define glVertexP2ui GETFUNCTION(__teVertexP2ui)
#define glVertexP2uiv GETFUNCTION(__teVertexP2uiv)
#define glVertexP3ui GETFUNCTION(__teVertexP3ui)
#define glVertexP3uiv GETFUNCTION(__teVertexP3uiv)
#define glVertexP4ui GETFUNCTION(__teVertexP4ui)
#define glVertexP4uiv GETFUNCTION(__teVertexP4uiv)
#define glTexCoordP1ui GETFUNCTION(__teTexCoordP1ui)
#define glTexCoordP1uiv GETFUNCTION(__teTexCoordP1uiv)
#define glTexCoordP2ui GETFUNCTION(__teTexCoordP2ui)
#define glTexCoordP2uiv GETFUNCTION(__teTexCoordP2uiv)
#define glTexCoordP3ui GETFUNCTION(__teTexCoordP3ui)
#define glTexCoordP3uiv GETFUNCTION(__teTexCoordP3uiv)
#define glTexCoordP4ui GETFUNCTION(__teTexCoordP4ui)
#define glTexCoordP4uiv GETFUNCTION(__teTexCoordP4uiv)
#define glMultiTexCoordP1ui GETFUNCTION(__teMultiTexCoordP1ui)
#define glMultiTexCoordP1uiv GETFUNCTION(__teMultiTexCoordP1uiv)
#define glMultiTexCoordP2ui GETFUNCTION(__teMultiTexCoordP2ui)
#define glMultiTexCoordP2uiv GETFUNCTION(__teMultiTexCoordP2uiv)
#define glMultiTexCoordP3ui GETFUNCTION(__teMultiTexCoordP3ui)
#define glMultiTexCoordP3uiv GETFUNCTION(__teMultiTexCoordP3uiv)
#define glMultiTexCoordP4ui GETFUNCTION(__teMultiTexCoordP4ui)
#define glMultiTexCoordP4uiv GETFUNCTION(__teMultiTexCoordP4uiv)
#define glNormalP3ui GETFUNCTION(__teNormalP3ui)
#define glNormalP3uiv GETFUNCTION(__teNormalP3uiv)
#define glColorP3ui GETFUNCTION(__teColorP3ui)
#define glColorP3uiv GETFUNCTION(__teColorP3uiv)
#define glColorP4ui GETFUNCTION(__teColorP4ui)
#define glColorP4uiv GETFUNCTION(__teColorP4uiv)
#define glSecondaryColorP3ui GETFUNCTION(__teSecondaryColorP3ui)
#define glSecondaryColorP3uiv GETFUNCTION(__teSecondaryColorP3uiv)

//OpenGL 4.0 Extensions
#define GL_SAMPLE_SHADING                 0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE       0x8C37
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
#define GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY   0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#define GL_DRAW_INDIRECT_BUFFER           0x8F3F
#define GL_DRAW_INDIRECT_BUFFER_BINDING   0x8F43
#define GL_GEOMETRY_SHADER_INVOCATIONS    0x887F
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
#define GL_MAX_VERTEX_STREAMS             0x8E71
#define GL_DOUBLE_VEC2                    0x8FFC
#define GL_DOUBLE_VEC3                    0x8FFD
#define GL_DOUBLE_VEC4                    0x8FFE
#define GL_DOUBLE_MAT2                    0x8F46
#define GL_DOUBLE_MAT3                    0x8F47
#define GL_DOUBLE_MAT4                    0x8F48
#define GL_DOUBLE_MAT2x3                  0x8F49
#define GL_DOUBLE_MAT2x4                  0x8F4A
#define GL_DOUBLE_MAT3x2                  0x8F4B
#define GL_DOUBLE_MAT3x4                  0x8F4C
#define GL_DOUBLE_MAT4x2                  0x8F4D
#define GL_DOUBLE_MAT4x3                  0x8F4E
#define GL_ACTIVE_SUBROUTINES             0x8DE5
#define GL_ACTIVE_SUBROUTINE_UNIFORMS     0x8DE6
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8E47
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH   0x8E48
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8E49
#define GL_MAX_SUBROUTINES                0x8DE7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8DE8
#define GL_NUM_COMPATIBLE_SUBROUTINES     0x8E4A
#define GL_COMPATIBLE_SUBROUTINES         0x8E4B
#define GL_PATCHES                        0x000E
#define GL_PATCH_VERTICES                 0x8E72
#define GL_PATCH_DEFAULT_INNER_LEVEL      0x8E73
#define GL_PATCH_DEFAULT_OUTER_LEVEL      0x8E74
#define GL_TESS_CONTROL_OUTPUT_VERTICES   0x8E75
#define GL_TESS_GEN_MODE                  0x8E76
#define GL_TESS_GEN_SPACING               0x8E77
#define GL_TESS_GEN_VERTEX_ORDER          0x8E78
#define GL_TESS_GEN_POINT_MODE            0x8E79
#define GL_ISOLINES                       0x8E7A
#define GL_FRACTIONAL_ODD                 0x8E7B
#define GL_FRACTIONAL_EVEN                0x8E7C
#define GL_MAX_PATCH_VERTICES             0x8E7D
#define GL_MAX_TESS_GEN_LEVEL             0x8E7E
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#define GL_MAX_TESS_PATCH_COMPONENTS      0x8E84
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8E85
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886C
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886D
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84F0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84F1
#define GL_TESS_EVALUATION_SHADER         0x8E87
#define GL_TESS_CONTROL_SHADER            0x8E88
#define GL_TRANSFORM_FEEDBACK             0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8E70
typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat value);
typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum mode);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect);
typedef void (APIENTRYP PFNGLUNIFORM1DPROC) (GLint location, GLdouble x);
typedef void (APIENTRYP PFNGLUNIFORM2DPROC) (GLint location, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLUNIFORM3DPROC) (GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLUNIFORM4DPROC) (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLUNIFORM1DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM2DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM3DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM4DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLGETUNIFORMDVPROC) (GLuint program, GLint location, GLdouble *params);
typedef GLint(APIENTRYP PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) (GLuint program, GLenum shadertype, const GLchar *name);
typedef GLuint(APIENTRYP PFNGLGETSUBROUTINEINDEXPROC) (GLuint program, GLenum shadertype, const GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINENAMEPROC) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLUNIFORMSUBROUTINESUIVPROC) (GLenum shadertype, GLsizei count, const GLuint *indices);
typedef void (APIENTRYP PFNGLGETUNIFORMSUBROUTINEUIVPROC) (GLenum shadertype, GLint location, GLuint *params);
typedef void (APIENTRYP PFNGLGETPROGRAMSTAGEIVPROC) (GLuint program, GLenum shadertype, GLenum pname, GLint *values);
typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLPATCHPARAMETERFVPROC) (GLenum pname, const GLfloat *values);
typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, const GLuint *ids);
typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
typedef GLboolean(APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKPROC) (GLenum mode, GLuint id);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) (GLenum mode, GLuint id, GLuint stream);
typedef void (APIENTRYP PFNGLBEGINQUERYINDEXEDPROC) (GLenum target, GLuint index, GLuint id);
typedef void (APIENTRYP PFNGLENDQUERYINDEXEDPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLGETQUERYINDEXEDIVPROC) (GLenum target, GLuint index, GLenum pname, GLint *params);
extern PFNGLMINSAMPLESHADINGPROC __teMinSampleShading;
extern PFNGLBLENDEQUATIONIPROC __teBlendEquationi;
extern PFNGLBLENDEQUATIONSEPARATEIPROC __teBlendEquationSeparatei;
extern PFNGLBLENDFUNCIPROC __teBlendFunci;
extern PFNGLBLENDFUNCSEPARATEIPROC __teBlendFuncSeparatei;
extern PFNGLDRAWARRAYSINDIRECTPROC __teDrawArraysIndirect;
extern PFNGLDRAWELEMENTSINDIRECTPROC __teDrawElementsIndirect;
extern PFNGLUNIFORM1DPROC __teUniform1d;
extern PFNGLUNIFORM2DPROC __teUniform2d;
extern PFNGLUNIFORM3DPROC __teUniform3d;
extern PFNGLUNIFORM4DPROC __teUniform4d;
extern PFNGLUNIFORM1DVPROC __teUniform1dv;
extern PFNGLUNIFORM2DVPROC __teUniform2dv;
extern PFNGLUNIFORM3DVPROC __teUniform3dv;
extern PFNGLUNIFORM4DVPROC __teUniform4dv;
extern PFNGLUNIFORMMATRIX2DVPROC __teUniformMatrix2dv;
extern PFNGLUNIFORMMATRIX3DVPROC __teUniformMatrix3dv;
extern PFNGLUNIFORMMATRIX4DVPROC __teUniformMatrix4dv;
extern PFNGLUNIFORMMATRIX2X3DVPROC __teUniformMatrix2x3dv;
extern PFNGLUNIFORMMATRIX2X4DVPROC __teUniformMatrix2x4dv;
extern PFNGLUNIFORMMATRIX3X2DVPROC __teUniformMatrix3x2dv;
extern PFNGLUNIFORMMATRIX3X4DVPROC __teUniformMatrix3x4dv;
extern PFNGLUNIFORMMATRIX4X2DVPROC __teUniformMatrix4x2dv;
extern PFNGLUNIFORMMATRIX4X3DVPROC __teUniformMatrix4x3dv;
extern PFNGLGETUNIFORMDVPROC __teGetUniformdv;
extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC __teGetSubroutineUniformLocation;
extern PFNGLGETSUBROUTINEINDEXPROC __teGetSubroutineIndex;
extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC __teGetActiveSubroutineUniformiv;
extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC __teGetActiveSubroutineUniformName;
extern PFNGLGETACTIVESUBROUTINENAMEPROC __teGetActiveSubroutineName;
extern PFNGLUNIFORMSUBROUTINESUIVPROC __teUniformSubroutinesuiv;
extern PFNGLGETUNIFORMSUBROUTINEUIVPROC __teGetUniformSubroutineuiv;
extern PFNGLGETPROGRAMSTAGEIVPROC __teGetProgramStageiv;
extern PFNGLPATCHPARAMETERIPROC __tePatchParameteri;
extern PFNGLPATCHPARAMETERFVPROC __tePatchParameterfv;
extern PFNGLBINDTRANSFORMFEEDBACKPROC __teBindTransformFeedback;
extern PFNGLDELETETRANSFORMFEEDBACKSPROC __teDeleteTransformFeedbacks;
extern PFNGLGENTRANSFORMFEEDBACKSPROC __teGenTransformFeedbacks;
extern PFNGLISTRANSFORMFEEDBACKPROC __teIsTransformFeedback;
extern PFNGLPAUSETRANSFORMFEEDBACKPROC __tePauseTransformFeedback;
extern PFNGLRESUMETRANSFORMFEEDBACKPROC __teResumeTransformFeedback;
extern PFNGLDRAWTRANSFORMFEEDBACKPROC __teDrawTransformFeedback;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC __teDrawTransformFeedbackStream;
extern PFNGLBEGINQUERYINDEXEDPROC __teBeginQueryIndexed;
extern PFNGLENDQUERYINDEXEDPROC __teEndQueryIndexed;
extern PFNGLGETQUERYINDEXEDIVPROC __teGetQueryIndexediv;
#define glMinSampleShading GETFUNCTION(__teMinSampleShading)
#define glBlendEquationi GETFUNCTION(__teBlendEquationi)
#define glBlendEquationSeparatei GETFUNCTION(__teBlendEquationSeparatei)
#define glBlendFunci GETFUNCTION(__teBlendFunci)
#define glBlendFuncSeparatei GETFUNCTION(__teBlendFuncSeparatei)
#define glDrawArraysIndirect GETFUNCTION(__teDrawArraysIndirect)
#define glDrawElementsIndirect GETFUNCTION(__teDrawElementsIndirect)
#define glUniform1d GETFUNCTION(__teUniform1d)
#define glUniform2d GETFUNCTION(__teUniform2d)
#define glUniform3d GETFUNCTION(__teUniform3d)
#define glUniform4d GETFUNCTION(__teUniform4d)
#define glUniform1dv GETFUNCTION(__teUniform1dv)
#define glUniform2dv GETFUNCTION(__teUniform2dv)
#define glUniform3dv GETFUNCTION(__teUniform3dv)
#define glUniform4dv GETFUNCTION(__teUniform4dv)
#define glUniformMatrix2dv GETFUNCTION(__teUniformMatrix2dv)
#define glUniformMatrix3dv GETFUNCTION(__teUniformMatrix3dv)
#define glUniformMatrix4dv GETFUNCTION(__teUniformMatrix4dv)
#define glUniformMatrix2x3dv GETFUNCTION(__teUniformMatrix2x3dv)
#define glUniformMatrix2x4dv GETFUNCTION(__teUniformMatrix2x4dv)
#define glUniformMatrix3x2dv GETFUNCTION(__teUniformMatrix3x2dv)
#define glUniformMatrix3x4dv GETFUNCTION(__teUniformMatrix3x4dv)
#define glUniformMatrix4x2dv GETFUNCTION(__teUniformMatrix4x2dv)
#define glUniformMatrix4x3dv GETFUNCTION(__teUniformMatrix4x3dv)
#define glGetUniformdv GETFUNCTION(__teGetUniformdv)
#define glGetSubroutineUniformLocation GETFUNCTION(__teGetSubroutineUniformLocation)
#define glGetSubroutineIndex GETFUNCTION(__teGetSubroutineIndex)
#define glGetActiveSubroutineUniformiv GETFUNCTION(__teGetActiveSubroutineUniformiv)
#define glGetActiveSubroutineUniformName GETFUNCTION(__teGetActiveSubroutineUniformName)
#define glGetActiveSubroutineName GETFUNCTION(__teGetActiveSubroutineName)
#define glUniformSubroutinesuiv GETFUNCTION(__teUniformSubroutinesuiv)
#define glGetUniformSubroutineuiv GETFUNCTION(__teGetUniformSubroutineuiv)
#define glGetProgramStageiv GETFUNCTION(__teGetProgramStageiv)
#define glPatchParameteri GETFUNCTION(__tePatchParameteri)
#define glPatchParameterfv GETFUNCTION(__tePatchParameterfv)
#define glBindTransformFeedback GETFUNCTION(__teBindTransformFeedback)
#define glDeleteTransformFeedbacks GETFUNCTION(__teDeleteTransformFeedbacks)
#define glGenTransformFeedbacks GETFUNCTION(__teGenTransformFeedbacks)
#define glIsTransformFeedback GETFUNCTION(__teIsTransformFeedback)
#define glPauseTransformFeedback GETFUNCTION(__tePauseTransformFeedback)
#define glResumeTransformFeedback GETFUNCTION(__teResumeTransformFeedback)
#define glDrawTransformFeedback GETFUNCTION(__teDrawTransformFeedback)
#define glDrawTransformFeedbackStream GETFUNCTION(__teDrawTransformFeedbackStream)
#define glBeginQueryIndexed GETFUNCTION(__teBeginQueryIndexed)
#define glEndQueryIndexed GETFUNCTION(__teEndQueryIndexed)
#define glGetQueryIndexediv GETFUNCTION(__teGetQueryIndexediv)

//OpenGL 4.1 Extensions
#define GL_FIXED                          0x140C
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#define GL_LOW_FLOAT                      0x8DF0
#define GL_MEDIUM_FLOAT                   0x8DF1
#define GL_HIGH_FLOAT                     0x8DF2
#define GL_LOW_INT                        0x8DF3
#define GL_MEDIUM_INT                     0x8DF4
#define GL_HIGH_INT                       0x8DF5
#define GL_SHADER_COMPILER                0x8DFA
#define GL_SHADER_BINARY_FORMATS          0x8DF8
#define GL_NUM_SHADER_BINARY_FORMATS      0x8DF9
#define GL_MAX_VERTEX_UNIFORM_VECTORS     0x8DFB
#define GL_MAX_VARYING_VECTORS            0x8DFC
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS   0x8DFD
#define GL_RGB565                         0x8D62
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_BINARY_LENGTH          0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS     0x87FE
#define GL_PROGRAM_BINARY_FORMATS         0x87FF
#define GL_VERTEX_SHADER_BIT              0x00000001
#define GL_FRAGMENT_SHADER_BIT            0x00000002
#define GL_GEOMETRY_SHADER_BIT            0x00000004
#define GL_TESS_CONTROL_SHADER_BIT        0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT     0x00000010
#define GL_ALL_SHADER_BITS                0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE              0x8258
#define GL_ACTIVE_PROGRAM                 0x8259
#define GL_PROGRAM_PIPELINE_BINDING       0x825A
#define GL_MAX_VIEWPORTS                  0x825B
#define GL_VIEWPORT_SUBPIXEL_BITS         0x825C
#define GL_VIEWPORT_BOUNDS_RANGE          0x825D
#define GL_LAYER_PROVOKING_VERTEX         0x825E
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825F
#define GL_UNDEFINED_VERTEX               0x8260
typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (void);
typedef void (APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint program, GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint program);
typedef GLuint(APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei count, const GLchar *const*strings);
typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, const GLuint *pipelines);
typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
typedef GLboolean(APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint program, GLint location, GLint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint program, GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DPROC) (GLuint program, GLint location, GLdouble v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint program, GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint program, GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DPROC) (GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLDVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRYP PFNGLVIEWPORTARRAYVPROC) (GLuint first, GLsizei count, const GLfloat *v);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLSCISSORARRAYVPROC) (GLuint first, GLsizei count, const GLint *v);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDPROC) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYVPROC) (GLuint first, GLsizei count, const GLdouble *v);
typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDPROC) (GLuint index, GLdouble n, GLdouble f);
typedef void (APIENTRYP PFNGLGETFLOATI_VPROC) (GLenum target, GLuint index, GLfloat *data);
typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC) (GLenum target, GLuint index, GLdouble *data);
extern PFNGLRELEASESHADERCOMPILERPROC __teReleaseShaderCompiler;
extern PFNGLSHADERBINARYPROC __teShaderBinary;
extern PFNGLGETSHADERPRECISIONFORMATPROC __teGetShaderPrecisionFormat;
extern PFNGLDEPTHRANGEFPROC __teDepthRangef;
extern PFNGLCLEARDEPTHFPROC __teClearDepthf;
extern PFNGLGETPROGRAMBINARYPROC __teGetProgramBinary;
extern PFNGLPROGRAMBINARYPROC __teProgramBinary;
extern PFNGLPROGRAMPARAMETERIPROC __teProgramParameteri;
extern PFNGLUSEPROGRAMSTAGESPROC __teUseProgramStages;
extern PFNGLACTIVESHADERPROGRAMPROC __teActiveShaderProgram;
extern PFNGLCREATESHADERPROGRAMVPROC __teCreateShaderProgramv;
extern PFNGLBINDPROGRAMPIPELINEPROC __teBindProgramPipeline;
extern PFNGLDELETEPROGRAMPIPELINESPROC __teDeleteProgramPipelines;
extern PFNGLGENPROGRAMPIPELINESPROC __teGenProgramPipelines;
extern PFNGLISPROGRAMPIPELINEPROC __teIsProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEIVPROC __teGetProgramPipelineiv;
extern PFNGLPROGRAMUNIFORM1IPROC __teProgramUniform1i;
extern PFNGLPROGRAMUNIFORM1IVPROC __teProgramUniform1iv;
extern PFNGLPROGRAMUNIFORM1FPROC __teProgramUniform1f;
extern PFNGLPROGRAMUNIFORM1FVPROC __teProgramUniform1fv;
extern PFNGLPROGRAMUNIFORM1DPROC __teProgramUniform1d;
extern PFNGLPROGRAMUNIFORM1DVPROC __teProgramUniform1dv;
extern PFNGLPROGRAMUNIFORM1UIPROC __teProgramUniform1ui;
extern PFNGLPROGRAMUNIFORM1UIVPROC __teProgramUniform1uiv;
extern PFNGLPROGRAMUNIFORM2IPROC __teProgramUniform2i;
extern PFNGLPROGRAMUNIFORM2IVPROC __teProgramUniform2iv;
extern PFNGLPROGRAMUNIFORM2FPROC __teProgramUniform2f;
extern PFNGLPROGRAMUNIFORM2FVPROC __teProgramUniform2fv;
extern PFNGLPROGRAMUNIFORM2DPROC __teProgramUniform2d;
extern PFNGLPROGRAMUNIFORM2DVPROC __teProgramUniform2dv;
extern PFNGLPROGRAMUNIFORM2UIPROC __teProgramUniform2ui;
extern PFNGLPROGRAMUNIFORM2UIVPROC __teProgramUniform2uiv;
extern PFNGLPROGRAMUNIFORM3IPROC __teProgramUniform3i;
extern PFNGLPROGRAMUNIFORM3IVPROC __teProgramUniform3iv;
extern PFNGLPROGRAMUNIFORM3FPROC __teProgramUniform3f;
extern PFNGLPROGRAMUNIFORM3FVPROC __teProgramUniform3fv;
extern PFNGLPROGRAMUNIFORM3DPROC __teProgramUniform3d;
extern PFNGLPROGRAMUNIFORM3DVPROC __teProgramUniform3dv;
extern PFNGLPROGRAMUNIFORM3UIPROC __teProgramUniform3ui;
extern PFNGLPROGRAMUNIFORM3UIVPROC __teProgramUniform3uiv;
extern PFNGLPROGRAMUNIFORM4IPROC __teProgramUniform4i;
extern PFNGLPROGRAMUNIFORM4IVPROC __teProgramUniform4iv;
extern PFNGLPROGRAMUNIFORM4FPROC __teProgramUniform4f;
extern PFNGLPROGRAMUNIFORM4FVPROC __teProgramUniform4fv;
extern PFNGLPROGRAMUNIFORM4DPROC __teProgramUniform4d;
extern PFNGLPROGRAMUNIFORM4DVPROC __teProgramUniform4dv;
extern PFNGLPROGRAMUNIFORM4UIPROC __teProgramUniform4ui;
extern PFNGLPROGRAMUNIFORM4UIVPROC __teProgramUniform4uiv;
extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC __teProgramUniformMatrix2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC __teProgramUniformMatrix3fv;
extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC __teProgramUniformMatrix4fv;
extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC __teProgramUniformMatrix2dv;
extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC __teProgramUniformMatrix3dv;
extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC __teProgramUniformMatrix4dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC __teProgramUniformMatrix2x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC __teProgramUniformMatrix3x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC __teProgramUniformMatrix2x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC __teProgramUniformMatrix4x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC __teProgramUniformMatrix3x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC __teProgramUniformMatrix4x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC __teProgramUniformMatrix2x3dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC __teProgramUniformMatrix3x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC __teProgramUniformMatrix2x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC __teProgramUniformMatrix4x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC __teProgramUniformMatrix3x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC __teProgramUniformMatrix4x3dv;
extern PFNGLVALIDATEPROGRAMPIPELINEPROC __teValidateProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC __teGetProgramPipelineInfoLog;
extern PFNGLVERTEXATTRIBL1DPROC __teVertexAttribL1d;
extern PFNGLVERTEXATTRIBL2DPROC __teVertexAttribL2d;
extern PFNGLVERTEXATTRIBL3DPROC __teVertexAttribL3d;
extern PFNGLVERTEXATTRIBL4DPROC __teVertexAttribL4d;
extern PFNGLVERTEXATTRIBL1DVPROC __teVertexAttribL1dv;
extern PFNGLVERTEXATTRIBL2DVPROC __teVertexAttribL2dv;
extern PFNGLVERTEXATTRIBL3DVPROC __teVertexAttribL3dv;
extern PFNGLVERTEXATTRIBL4DVPROC __teVertexAttribL4dv;
extern PFNGLVERTEXATTRIBLPOINTERPROC __teVertexAttribLPointer;
extern PFNGLGETVERTEXATTRIBLDVPROC __teGetVertexAttribLdv;
extern PFNGLVIEWPORTARRAYVPROC __teViewportArrayv;
extern PFNGLVIEWPORTINDEXEDFPROC __teViewportIndexedf;
extern PFNGLVIEWPORTINDEXEDFVPROC __teViewportIndexedfv;
extern PFNGLSCISSORARRAYVPROC __teScissorArrayv;
extern PFNGLSCISSORINDEXEDPROC __teScissorIndexed;
extern PFNGLSCISSORINDEXEDVPROC __teScissorIndexedv;
extern PFNGLDEPTHRANGEARRAYVPROC __teDepthRangeArrayv;
extern PFNGLDEPTHRANGEINDEXEDPROC __teDepthRangeIndexed;
extern PFNGLGETFLOATI_VPROC __teGetFloati_v;
extern PFNGLGETDOUBLEI_VPROC __teGetDoublei_v;
#define glReleaseShaderCompiler GETFUNCTION(__teReleaseShaderCompiler)
#define glShaderBinary GETFUNCTION(__teShaderBinary)
#define glGetShaderPrecisionFormat GETFUNCTION(__teGetShaderPrecisionFormat)
#define glDepthRangef GETFUNCTION(__teDepthRangef)
#define glClearDepthf GETFUNCTION(__teClearDepthf)
#define glGetProgramBinary GETFUNCTION(__teGetProgramBinary)
#define glProgramBinary GETFUNCTION(__teProgramBinary)
#define glProgramParameteri GETFUNCTION(__teProgramParameteri)
#define glUseProgramStages GETFUNCTION(__teUseProgramStages)
#define glActiveShaderProgram GETFUNCTION(__teActiveShaderProgram)
#define glCreateShaderProgramv GETFUNCTION(__teCreateShaderProgramv)
#define glBindProgramPipeline GETFUNCTION(__teBindProgramPipeline)
#define glDeleteProgramPipelines GETFUNCTION(__teDeleteProgramPipelines)
#define glGenProgramPipelines GETFUNCTION(__teGenProgramPipelines)
#define glIsProgramPipeline GETFUNCTION(__teIsProgramPipeline)
#define glGetProgramPipelineiv GETFUNCTION(__teGetProgramPipelineiv)
#define glProgramUniform1i GETFUNCTION(__teProgramUniform1i)
#define glProgramUniform1iv GETFUNCTION(__teProgramUniform1iv)
#define glProgramUniform1f GETFUNCTION(__teProgramUniform1f)
#define glProgramUniform1fv GETFUNCTION(__teProgramUniform1fv)
#define glProgramUniform1d GETFUNCTION(__teProgramUniform1d)
#define glProgramUniform1dv GETFUNCTION(__teProgramUniform1dv)
#define glProgramUniform1ui GETFUNCTION(__teProgramUniform1ui)
#define glProgramUniform1uiv GETFUNCTION(__teProgramUniform1uiv)
#define glProgramUniform2i GETFUNCTION(__teProgramUniform2i)
#define glProgramUniform2iv GETFUNCTION(__teProgramUniform2iv)
#define glProgramUniform2f GETFUNCTION(__teProgramUniform2f)
#define glProgramUniform2fv GETFUNCTION(__teProgramUniform2fv)
#define glProgramUniform2d GETFUNCTION(__teProgramUniform2d)
#define glProgramUniform2dv GETFUNCTION(__teProgramUniform2dv)
#define glProgramUniform2ui GETFUNCTION(__teProgramUniform2ui)
#define glProgramUniform2uiv GETFUNCTION(__teProgramUniform2uiv)
#define glProgramUniform3i GETFUNCTION(__teProgramUniform3i)
#define glProgramUniform3iv GETFUNCTION(__teProgramUniform3iv)
#define glProgramUniform3f GETFUNCTION(__teProgramUniform3f)
#define glProgramUniform3fv GETFUNCTION(__teProgramUniform3fv)
#define glProgramUniform3d GETFUNCTION(__teProgramUniform3d)
#define glProgramUniform3dv GETFUNCTION(__teProgramUniform3dv)
#define glProgramUniform3ui GETFUNCTION(__teProgramUniform3ui)
#define glProgramUniform3uiv GETFUNCTION(__teProgramUniform3uiv)
#define glProgramUniform4i GETFUNCTION(__teProgramUniform4i)
#define glProgramUniform4iv GETFUNCTION(__teProgramUniform4iv)
#define glProgramUniform4f GETFUNCTION(__teProgramUniform4f)
#define glProgramUniform4fv GETFUNCTION(__teProgramUniform4fv)
#define glProgramUniform4d GETFUNCTION(__teProgramUniform4d)
#define glProgramUniform4dv GETFUNCTION(__teProgramUniform4dv)
#define glProgramUniform4ui GETFUNCTION(__teProgramUniform4ui)
#define glProgramUniform4uiv GETFUNCTION(__teProgramUniform4uiv)
#define glProgramUniformMatrix2fv GETFUNCTION(__teProgramUniformMatrix2fv)
#define glProgramUniformMatrix3fv GETFUNCTION(__teProgramUniformMatrix2fv)
#define glProgramUniformMatrix4fv GETFUNCTION(__teProgramUniformMatrix2fv)
#define glProgramUniformMatrix2dv GETFUNCTION(__teProgramUniformMatrix2dv)
#define glProgramUniformMatrix3dv GETFUNCTION(__teProgramUniformMatrix3dv)
#define glProgramUniformMatrix4dv GETFUNCTION(__teProgramUniformMatrix4dv)
#define glProgramUniformMatrix2x3fv GETFUNCTION(__teProgramUniformMatrix2x3fv)
#define glProgramUniformMatrix3x2fv GETFUNCTION(__teProgramUniformMatrix3x2fv)
#define glProgramUniformMatrix2x4fv GETFUNCTION(__teProgramUniformMatrix2x4fv)
#define glProgramUniformMatrix4x2fv GETFUNCTION(__teProgramUniformMatrix4x2fv)
#define glProgramUniformMatrix3x4fv GETFUNCTION(__teProgramUniformMatrix3x4fv)
#define glProgramUniformMatrix4x3fv GETFUNCTION(__teProgramUniformMatrix4x3fv)
#define glProgramUniformMatrix2x3dv GETFUNCTION(__teProgramUniformMatrix2x3dv)
#define glProgramUniformMatrix3x2dv GETFUNCTION(__teProgramUniformMatrix3x2dv)
#define glProgramUniformMatrix2x4dv GETFUNCTION(__teProgramUniformMatrix2x4dv)
#define glProgramUniformMatrix4x2dv GETFUNCTION(__teProgramUniformMatrix4x2dv)
#define glProgramUniformMatrix3x4dv GETFUNCTION(__teProgramUniformMatrix3x2dv)
#define glProgramUniformMatrix4x3dv GETFUNCTION(__teProgramUniformMatrix4x3dv)
#define glValidateProgramPipeline GETFUNCTION(__teValidateProgramPipeline)
#define glGetProgramPipelineInfoLog GETFUNCTION(__teGetProgramPipelineInfoLog)
#define glVertexAttribL1d GETFUNCTION(__teVertexAttribL1d)
#define glVertexAttribL2d GETFUNCTION(__teVertexAttribL2d)
#define glVertexAttribL3d GETFUNCTION(__teVertexAttribL3d)
#define glVertexAttribL4d GETFUNCTION(__teVertexAttribL4d)
#define glVertexAttribL1dv GETFUNCTION(__teVertexAttribL1dv)
#define glVertexAttribL2dv GETFUNCTION(__teVertexAttribL2dv)
#define glVertexAttribL3dv GETFUNCTION(__teVertexAttribL3dv)
#define glVertexAttribL4dv GETFUNCTION(__teVertexAttribL4dv)
#define glVertexAttribLPointer GETFUNCTION(__teVertexAttribLPointer)
#define glGetVertexAttribLdv GETFUNCTION(__teGetVertexAttribLdv)
#define glViewportarrayv GETFUNCTION(__teViewportArrayv)
#define glViewportIndexedf GETFUNCTION(__teViewportIndexedf)
#define glViewportIndexedfv GETFUNCTION(__teViewportIndexedfv)
#define glScissorArrayv GETFUNCTION(__teScissorArrayv)
#define glScissorIndexed GETFUNCTION(__teScissorIndexed)
#define glScissorIndexedv GETFUNCTION(__teScissorIndexedv)
#define glDepthRangeIndexed GETFUNCTION(__teDepthRangeIndexed)
#define glGetFloati_v GETFUNCTION(__teGetFloati_v)
#define glGetDoublei_v GETFUNCTION(__teGetDoublei_v)

//OpenGL 4.2 Extensions
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH  0x9127
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH  0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE   0x912A
#define GL_PACK_COMPRESSED_BLOCK_WIDTH    0x912B
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT   0x912C
#define GL_PACK_COMPRESSED_BLOCK_DEPTH    0x912D
#define GL_PACK_COMPRESSED_BLOCK_SIZE     0x912E
#define GL_NUM_SAMPLE_COUNTS              0x9380
#define GL_MIN_MAP_BUFFER_ALIGNMENT       0x90BC
#define GL_ATOMIC_COUNTER_BUFFER          0x92C0
#define GL_ATOMIC_COUNTER_BUFFER_BINDING  0x92C1
#define GL_ATOMIC_COUNTER_BUFFER_START    0x92C2
#define GL_ATOMIC_COUNTER_BUFFER_SIZE     0x92C3
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 0x92C4
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 0x92C5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 0x92C6
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 0x92C7
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 0x92C8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92C9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 0x92CA
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 0x92CB
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92CC
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#define GL_MAX_VERTEX_ATOMIC_COUNTERS     0x92D2
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS   0x92D5
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#define GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92D8
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92DC
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS  0x92D9
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 0x92DA
#define GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT      0x00000002
#define GL_UNIFORM_BARRIER_BIT            0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT      0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#define GL_COMMAND_BARRIER_BIT            0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT       0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT     0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT      0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT        0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT     0x00001000
#define GL_ALL_BARRIER_BITS               0xFFFFFFFF
#define GL_MAX_IMAGE_UNITS                0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8F39
#define GL_IMAGE_BINDING_NAME             0x8F3A
#define GL_IMAGE_BINDING_LEVEL            0x8F3B
#define GL_IMAGE_BINDING_LAYERED          0x8F3C
#define GL_IMAGE_BINDING_LAYER            0x8F3D
#define GL_IMAGE_BINDING_ACCESS           0x8F3E
#define GL_IMAGE_1D                       0x904C
#define GL_IMAGE_2D                       0x904D
#define GL_IMAGE_3D                       0x904E
#define GL_IMAGE_2D_RECT                  0x904F
#define GL_IMAGE_CUBE                     0x9050
#define GL_IMAGE_BUFFER                   0x9051
#define GL_IMAGE_1D_ARRAY                 0x9052
#define GL_IMAGE_2D_ARRAY                 0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY           0x9054
#define GL_IMAGE_2D_MULTISAMPLE           0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY     0x9056
#define GL_INT_IMAGE_1D                   0x9057
#define GL_INT_IMAGE_2D                   0x9058
#define GL_INT_IMAGE_3D                   0x9059
#define GL_INT_IMAGE_2D_RECT              0x905A
#define GL_INT_IMAGE_CUBE                 0x905B
#define GL_INT_IMAGE_BUFFER               0x905C
#define GL_INT_IMAGE_1D_ARRAY             0x905D
#define GL_INT_IMAGE_2D_ARRAY             0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY       0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE       0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x9061
#define GL_UNSIGNED_INT_IMAGE_1D          0x9062
#define GL_UNSIGNED_INT_IMAGE_2D          0x9063
#define GL_UNSIGNED_INT_IMAGE_3D          0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT     0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER      0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY    0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x906C
#define GL_MAX_IMAGE_SAMPLES              0x906D
#define GL_IMAGE_BINDING_FORMAT           0x906E
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90C8
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#define GL_MAX_VERTEX_IMAGE_UNIFORMS      0x90CA
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS    0x90CD
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#define GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#define GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) (GLuint program, GLuint bufferIndex, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
typedef void (APIENTRYP PFNGLTEXSTORAGE1DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) (GLenum mode, GLuint id, GLsizei instancecount);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) (GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
extern PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC __teDrawArraysInstancedBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC __teDrawElementsInstancedBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC __teDrawElementsInstancedBaseVertexBaseInstance;
extern PFNGLGETINTERNALFORMATIVPROC __teGetInternalformativ;
extern PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC __teGetActiveAtomicCounterBufferiv;
extern PFNGLBINDIMAGETEXTUREPROC __teBindImageTexture;
extern PFNGLMEMORYBARRIERPROC __teMemoryBarrier;
extern PFNGLTEXSTORAGE1DPROC __teTexStorage1D;
extern PFNGLTEXSTORAGE2DPROC __teTexStorage2D;
extern PFNGLTEXSTORAGE3DPROC __teTexStorage3D;
extern PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC __teDrawTransformFeedbackInstanced;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC __teDrawTransformFeedbackStreamInstanced;
#define glDrawArraysInstancedBaseInstance GETFUNCTION(__teDrawArraysInstancedBaseInstance)
#define glDrawElementsInstancedBaseInstance GETFUNCTION(__teDrawElementsInstancedBaseInstance)
#define glDrawElementsInstancedBaseVertexBaseInstance GETFUNCTION(__teDrawElementsInstancedBaseVertexBaseInstance)
#define glGetInternalFormativ GETFUNCTION(__teGetInternalformativ)
#define glGetActiveAtomicCounterBufferiv GETFUNCTION(__teGetActiveAtomicCounterBufferiv)
#define glBindImageTexture GETFUNCTION(__teBindImageTexture)
#define glMemoryBarrier GETFUNCTION(__teMemoryBarrier)
#define glTexStorage1D GETFUNCTION(__teTexStorage1D)
#define glTexStorage2D GETFUNCTION(__teTexStorage2D)
#define glTexStorage3D GETFUNCTION(__teTexStorage3D)
#define glDrawTransformFeedbackInstanced GETFUNCTION(__teDrawTransformFeedbackInstanced)
#define glDrawTransformFeedbackStreamInstanced GETFUNCTION(__teDrawTransformFeedbackStreamInstanced)

//OpenGL 4.3 Extensions
typedef void (APIENTRY  *GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
#define GL_NUM_SHADING_LANGUAGE_VERSIONS  0x82E9
#define GL_VERTEX_ATTRIB_ARRAY_LONG       0x874E
#define GL_COMPRESSED_RGB8_ETC2           0x9274
#define GL_COMPRESSED_SRGB8_ETC2          0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#define GL_COMPRESSED_R11_EAC             0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#define GL_COMPRESSED_RG11_EAC            0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#define GL_PRIMITIVE_RESTART_FIXED_INDEX  0x8D69
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#define GL_MAX_ELEMENT_INDEX              0x8D6B
#define GL_COMPUTE_SHADER                 0x91B9
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS     0x91BB
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90EB
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT   0x91BE
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE    0x91BF
#define GL_COMPUTE_WORK_GROUP_SIZE        0x8267
#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 0x90EC
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ED
#define GL_DISPATCH_INDIRECT_BUFFER       0x90EE
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90EF
#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION        0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#define GL_DEBUG_SOURCE_API               0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM     0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER   0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY       0x8249
#define GL_DEBUG_SOURCE_APPLICATION       0x824A
#define GL_DEBUG_SOURCE_OTHER             0x824B
#define GL_DEBUG_TYPE_ERROR               0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#define GL_DEBUG_TYPE_PORTABILITY         0x824F
#define GL_DEBUG_TYPE_PERFORMANCE         0x8250
#define GL_DEBUG_TYPE_OTHER               0x8251
#define GL_MAX_DEBUG_MESSAGE_LENGTH       0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES      0x9144
#define GL_DEBUG_LOGGED_MESSAGES          0x9145
#define GL_DEBUG_SEVERITY_HIGH            0x9146
#define GL_DEBUG_SEVERITY_MEDIUM          0x9147
#define GL_DEBUG_SEVERITY_LOW             0x9148
#define GL_DEBUG_TYPE_MARKER              0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP          0x8269
#define GL_DEBUG_TYPE_POP_GROUP           0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH    0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH        0x826D
#define GL_BUFFER                         0x82E0
#define GL_SHADER                         0x82E1
#define GL_PROGRAM                        0x82E2
#define GL_QUERY                          0x82E3
#define GL_PROGRAM_PIPELINE               0x82E4
#define GL_SAMPLER                        0x82E6
#define GL_MAX_LABEL_LENGTH               0x82E8
#define GL_DEBUG_OUTPUT                   0x92E0
#define GL_CONTEXT_FLAG_DEBUG_BIT         0x00000002
#define GL_MAX_UNIFORM_LOCATIONS          0x826E
#define GL_FRAMEBUFFER_DEFAULT_WIDTH      0x9310
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT     0x9311
#define GL_FRAMEBUFFER_DEFAULT_LAYERS     0x9312
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#define GL_MAX_FRAMEBUFFER_WIDTH          0x9315
#define GL_MAX_FRAMEBUFFER_HEIGHT         0x9316
#define GL_MAX_FRAMEBUFFER_LAYERS         0x9317
#define GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#define GL_INTERNALFORMAT_SUPPORTED       0x826F
#define GL_INTERNALFORMAT_PREFERRED       0x8270
#define GL_INTERNALFORMAT_RED_SIZE        0x8271
#define GL_INTERNALFORMAT_GREEN_SIZE      0x8272
#define GL_INTERNALFORMAT_BLUE_SIZE       0x8273
#define GL_INTERNALFORMAT_ALPHA_SIZE      0x8274
#define GL_INTERNALFORMAT_DEPTH_SIZE      0x8275
#define GL_INTERNALFORMAT_STENCIL_SIZE    0x8276
#define GL_INTERNALFORMAT_SHARED_SIZE     0x8277
#define GL_INTERNALFORMAT_RED_TYPE        0x8278
#define GL_INTERNALFORMAT_GREEN_TYPE      0x8279
#define GL_INTERNALFORMAT_BLUE_TYPE       0x827A
#define GL_INTERNALFORMAT_ALPHA_TYPE      0x827B
#define GL_INTERNALFORMAT_DEPTH_TYPE      0x827C
#define GL_INTERNALFORMAT_STENCIL_TYPE    0x827D
#define GL_MAX_WIDTH                      0x827E
#define GL_MAX_HEIGHT                     0x827F
#define GL_MAX_DEPTH                      0x8280
#define GL_MAX_LAYERS                     0x8281
#define GL_MAX_COMBINED_DIMENSIONS        0x8282
#define GL_COLOR_COMPONENTS               0x8283
#define GL_DEPTH_COMPONENTS               0x8284
#define GL_STENCIL_COMPONENTS             0x8285
#define GL_COLOR_RENDERABLE               0x8286
#define GL_DEPTH_RENDERABLE               0x8287
#define GL_STENCIL_RENDERABLE             0x8288
#define GL_FRAMEBUFFER_RENDERABLE         0x8289
#define GL_FRAMEBUFFER_RENDERABLE_LAYERED 0x828A
#define GL_FRAMEBUFFER_BLEND              0x828B
#define GL_READ_PIXELS                    0x828C
#define GL_READ_PIXELS_FORMAT             0x828D
#define GL_READ_PIXELS_TYPE               0x828E
#define GL_TEXTURE_IMAGE_FORMAT           0x828F
#define GL_TEXTURE_IMAGE_TYPE             0x8290
#define GL_GET_TEXTURE_IMAGE_FORMAT       0x8291
#define GL_GET_TEXTURE_IMAGE_TYPE         0x8292
#define GL_MIPMAP                         0x8293
#define GL_MANUAL_GENERATE_MIPMAP         0x8294
#define GL_AUTO_GENERATE_MIPMAP           0x8295
#define GL_COLOR_ENCODING                 0x8296
#define GL_SRGB_READ                      0x8297
#define GL_SRGB_WRITE                     0x8298
#define GL_FILTER                         0x829A
#define GL_VERTEX_TEXTURE                 0x829B
#define GL_TESS_CONTROL_TEXTURE           0x829C
#define GL_TESS_EVALUATION_TEXTURE        0x829D
#define GL_GEOMETRY_TEXTURE               0x829E
#define GL_FRAGMENT_TEXTURE               0x829F
#define GL_COMPUTE_TEXTURE                0x82A0
#define GL_TEXTURE_SHADOW                 0x82A1
#define GL_TEXTURE_GATHER                 0x82A2
#define GL_TEXTURE_GATHER_SHADOW          0x82A3
#define GL_SHADER_IMAGE_LOAD              0x82A4
#define GL_SHADER_IMAGE_STORE             0x82A5
#define GL_SHADER_IMAGE_ATOMIC            0x82A6
#define GL_IMAGE_TEXEL_SIZE               0x82A7
#define GL_IMAGE_COMPATIBILITY_CLASS      0x82A8
#define GL_IMAGE_PIXEL_FORMAT             0x82A9
#define GL_IMAGE_PIXEL_TYPE               0x82AA
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 0x82AC
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 0x82AD
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 0x82AE
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 0x82AF
#define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 0x82B1
#define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 0x82B2
#define GL_TEXTURE_COMPRESSED_BLOCK_SIZE  0x82B3
#define GL_CLEAR_BUFFER                   0x82B4
#define GL_TEXTURE_VIEW                   0x82B5
#define GL_VIEW_COMPATIBILITY_CLASS       0x82B6
#define GL_FULL_SUPPORT                   0x82B7
#define GL_CAVEAT_SUPPORT                 0x82B8
#define GL_IMAGE_CLASS_4_X_32             0x82B9
#define GL_IMAGE_CLASS_2_X_32             0x82BA
#define GL_IMAGE_CLASS_1_X_32             0x82BB
#define GL_IMAGE_CLASS_4_X_16             0x82BC
#define GL_IMAGE_CLASS_2_X_16             0x82BD
#define GL_IMAGE_CLASS_1_X_16             0x82BE
#define GL_IMAGE_CLASS_4_X_8              0x82BF
#define GL_IMAGE_CLASS_2_X_8              0x82C0
#define GL_IMAGE_CLASS_1_X_8              0x82C1
#define GL_IMAGE_CLASS_11_11_10           0x82C2
#define GL_IMAGE_CLASS_10_10_10_2         0x82C3
#define GL_VIEW_CLASS_128_BITS            0x82C4
#define GL_VIEW_CLASS_96_BITS             0x82C5
#define GL_VIEW_CLASS_64_BITS             0x82C6
#define GL_VIEW_CLASS_48_BITS             0x82C7
#define GL_VIEW_CLASS_32_BITS             0x82C8
#define GL_VIEW_CLASS_24_BITS             0x82C9
#define GL_VIEW_CLASS_16_BITS             0x82CA
#define GL_VIEW_CLASS_8_BITS              0x82CB
#define GL_VIEW_CLASS_S3TC_DXT1_RGB       0x82CC
#define GL_VIEW_CLASS_S3TC_DXT1_RGBA      0x82CD
#define GL_VIEW_CLASS_S3TC_DXT3_RGBA      0x82CE
#define GL_VIEW_CLASS_S3TC_DXT5_RGBA      0x82CF
#define GL_VIEW_CLASS_RGTC1_RED           0x82D0
#define GL_VIEW_CLASS_RGTC2_RG            0x82D1
#define GL_VIEW_CLASS_BPTC_UNORM          0x82D2
#define GL_VIEW_CLASS_BPTC_FLOAT          0x82D3
#define GL_UNIFORM                        0x92E1
#define GL_UNIFORM_BLOCK                  0x92E2
#define GL_PROGRAM_INPUT                  0x92E3
#define GL_PROGRAM_OUTPUT                 0x92E4
#define GL_BUFFER_VARIABLE                0x92E5
#define GL_SHADER_STORAGE_BLOCK           0x92E6
#define GL_VERTEX_SUBROUTINE              0x92E8
#define GL_TESS_CONTROL_SUBROUTINE        0x92E9
#define GL_TESS_EVALUATION_SUBROUTINE     0x92EA
#define GL_GEOMETRY_SUBROUTINE            0x92EB
#define GL_FRAGMENT_SUBROUTINE            0x92EC
#define GL_COMPUTE_SUBROUTINE             0x92ED
#define GL_VERTEX_SUBROUTINE_UNIFORM      0x92EE
#define GL_TESS_CONTROL_SUBROUTINE_UNIFORM 0x92EF
#define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 0x92F0
#define GL_GEOMETRY_SUBROUTINE_UNIFORM    0x92F1
#define GL_FRAGMENT_SUBROUTINE_UNIFORM    0x92F2
#define GL_COMPUTE_SUBROUTINE_UNIFORM     0x92F3
#define GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#define GL_ACTIVE_RESOURCES               0x92F5
#define GL_MAX_NAME_LENGTH                0x92F6
#define GL_MAX_NUM_ACTIVE_VARIABLES       0x92F7
#define GL_MAX_NUM_COMPATIBLE_SUBROUTINES 0x92F8
#define GL_NAME_LENGTH                    0x92F9
#define GL_TYPE                           0x92FA
#define GL_ARRAY_SIZE                     0x92FB
#define GL_OFFSET                         0x92FC
#define GL_BLOCK_INDEX                    0x92FD
#define GL_ARRAY_STRIDE                   0x92FE
#define GL_MATRIX_STRIDE                  0x92FF
#define GL_IS_ROW_MAJOR                   0x9300
#define GL_ATOMIC_COUNTER_BUFFER_INDEX    0x9301
#define GL_BUFFER_BINDING                 0x9302
#define GL_BUFFER_DATA_SIZE               0x9303
#define GL_NUM_ACTIVE_VARIABLES           0x9304
#define GL_ACTIVE_VARIABLES               0x9305
#define GL_REFERENCED_BY_VERTEX_SHADER    0x9306
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#define GL_REFERENCED_BY_GEOMETRY_SHADER  0x9309
#define GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#define GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#define GL_TOP_LEVEL_ARRAY_SIZE           0x930C
#define GL_TOP_LEVEL_ARRAY_STRIDE         0x930D
#define GL_LOCATION                       0x930E
#define GL_LOCATION_INDEX                 0x930F
#define GL_IS_PER_PATCH                   0x92E7
#define GL_SHADER_STORAGE_BUFFER          0x90D2
#define GL_SHADER_STORAGE_BUFFER_BINDING  0x90D3
#define GL_SHADER_STORAGE_BUFFER_START    0x90D4
#define GL_SHADER_STORAGE_BUFFER_SIZE     0x90D5
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90D6
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90D7
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90D8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90D9
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90DA
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90DB
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90DC
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90DD
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE  0x90DE
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90DF
#define GL_SHADER_STORAGE_BARRIER_BIT     0x00002000
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#define GL_DEPTH_STENCIL_TEXTURE_MODE     0x90EA
#define GL_TEXTURE_BUFFER_OFFSET          0x919D
#define GL_TEXTURE_BUFFER_SIZE            0x919E
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919F
#define GL_TEXTURE_VIEW_MIN_LEVEL         0x82DB
#define GL_TEXTURE_VIEW_NUM_LEVELS        0x82DC
#define GL_TEXTURE_VIEW_MIN_LAYER         0x82DD
#define GL_TEXTURE_VIEW_NUM_LAYERS        0x82DE
#define GL_TEXTURE_IMMUTABLE_LEVELS       0x82DF
#define GL_VERTEX_ATTRIB_BINDING          0x82D4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET  0x82D5
#define GL_VERTEX_BINDING_DIVISOR         0x82D6
#define GL_VERTEX_BINDING_OFFSET          0x82D7
#define GL_VERTEX_BINDING_STRIDE          0x82D8
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D9
#define GL_MAX_VERTEX_ATTRIB_BINDINGS     0x82DA
#define GL_DISPLAY_LIST                   0x82E7
typedef void (APIENTRYP PFNGLCLEARBUFFERDATAPROC) (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARBUFFERSUBDATAPROC) (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr indirect);
typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATI64VPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params);
typedef void (APIENTRYP PFNGLINVALIDATETEXSUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLINVALIDATETEXIMAGEPROC) (GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERDATAPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments);
typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
typedef GLuint(APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params);
typedef GLint(APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef GLint(APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (APIENTRYP PFNGLSHADERSTORAGEBLOCKBINDINGPROC) (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTUREVIEWPROC) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);
typedef GLuint(APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC) (void);
typedef void (APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC) (const void *ptr, GLsizei length, const GLchar *label);
typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
extern PFNGLCLEARBUFFERDATAPROC __teClearBufferData;
extern PFNGLCLEARBUFFERSUBDATAPROC __teClearBufferSubdata;
extern PFNGLDISPATCHCOMPUTEPROC __teDispatchCompute;
extern PFNGLDISPATCHCOMPUTEINDIRECTPROC __teDispatchComputeIndirect;
extern PFNGLCOPYIMAGESUBDATAPROC  __teCopyImageSubdata;
extern PFNGLFRAMEBUFFERPARAMETERIPROC __teFramebufferParameteri;
extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC __teGetFramebufferParameteriv;
extern PFNGLGETINTERNALFORMATI64VPROC __teGetInternalformati64v;
extern PFNGLINVALIDATETEXSUBIMAGEPROC __teInvalidateTexSubImage;
extern PFNGLINVALIDATETEXIMAGEPROC __teInvalidateTexImage;
extern PFNGLINVALIDATEBUFFERSUBDATAPROC __teInvalidateBufferSubdata;
extern PFNGLINVALIDATEBUFFERDATAPROC __teInvalidateBufferData;
extern PFNGLINVALIDATEFRAMEBUFFERPROC __teInvalidateFramebuffer;
extern PFNGLINVALIDATESUBFRAMEBUFFERPROC __teInvalidateSubFramebuffer;
extern PFNGLMULTIDRAWARRAYSINDIRECTPROC __teMultiDrawArraysIndirect;
extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC __teMultiDrawElementsIndirect;
extern PFNGLGETPROGRAMINTERFACEIVPROC __teGetProgramInterfaceiv;
extern PFNGLGETPROGRAMRESOURCEINDEXPROC __teGetProgramResourceIndex;
extern PFNGLGETPROGRAMRESOURCENAMEPROC __teGetProgramResourceName;
extern PFNGLGETPROGRAMRESOURCEIVPROC __teGetProgramResourceiv;
extern PFNGLGETPROGRAMRESOURCELOCATIONPROC __teGetProgramResourceLocation;
extern PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC __teGetProgramResourceLocationIndex;
extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC __teShaderStorageBlockBinding;
extern PFNGLTEXBUFFERRANGEPROC __teTexBufferRange;
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC __teTexStorage2DMultisample;
extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC __teTexStorage3DMultisample;
extern PFNGLTEXTUREVIEWPROC __teTextureView;
extern PFNGLBINDVERTEXBUFFERPROC __teBindVertexBuffer;
extern PFNGLVERTEXATTRIBFORMATPROC __teVertexAttribFormat;
extern PFNGLVERTEXATTRIBIFORMATPROC __teVertexAttribIFormat;
extern PFNGLVERTEXATTRIBLFORMATPROC __teVertexAttribLFormat;
extern PFNGLVERTEXATTRIBBINDINGPROC __teVertexAttribBinding;
extern PFNGLVERTEXBINDINGDIVISORPROC __teVertexBindingDivisor;
extern PFNGLDEBUGMESSAGECONTROLPROC __teDebugMessageControl;
extern PFNGLDEBUGMESSAGEINSERTPROC __teDebugMessageInsert;
extern PFNGLDEBUGMESSAGECALLBACKPROC __teDebugMessageCallback;
extern PFNGLGETDEBUGMESSAGELOGPROC __teGetDebugMessageLog;
extern PFNGLPUSHDEBUGGROUPPROC __tePushDebugGroup;
extern PFNGLPOPDEBUGGROUPPROC __tePopDebugGroup;
extern PFNGLOBJECTLABELPROC __teObjectLabel;
extern PFNGLGETOBJECTLABELPROC __teGetObjectLabel;
extern PFNGLOBJECTPTRLABELPROC __teObjectPtrLabel;
extern PFNGLGETOBJECTPTRLABELPROC __teGetObjectPtrLabel;
#define glClearBufferData GETFUNCTION(__teClearBufferData)
#define glClearBufferSubdata GETFUNCTION(__teClearBufferSubdata)
#define glDispatchCompute GETFUNCTION(__teDispatchCompute)
#define glDispatchComputeIndirect GETFUNCTION(__teDispatchComputeIndirect)
#define glCopyImageSubdata GETFUNCTION(__teCopyImageSubdata)
#define glFramebufferParameteri GETFUNCTION(__teFramebufferParameteri)
#define glGetFramebufferParameteriv GETFUNCTION(__teGetFramebufferParameteriv)
#define glGetInternalFormati64v GETFUNCTION(__teGetInternalformati64v)
#define glInvalidateTexSubImage GETFUNCTION(__teInvalidateTexSubImage)
#define glInvalidateTexImage GETFUNCTION(__teInvalidateTexImage)
#define glInvalidateBufferSubdata GETFUNCTION(__teInvalidateBufferSubdata)
#define glInvalidateBufferData GETFUNCTION(__teInvalidateBufferData)
#define glInvalidateFramebuffer GETFUNCTION(__teInvalidateFramebuffer)
#define glInvalidateSubFramebuffer GETFUNCTION(__teInvalidateSubFramebuffer)
#define glMultiDrawArraysIndirect GETFUNCTION(__teMultiDrawArraysIndirect)
#define glMultiDrawElementsIndirect GETFUNCTION(__teMultiDrawElementsIndirect)
#define glGetProgramInterfaceiv GETFUNCTION(__teGetProgramInterfaceiv)
#define glGetProgramResourceIndex GETFUNCTION(__teGetProgramResourceIndex)
#define glGetProgramResourceName GETFUNCTION(__teGetProgramResourceName)
#define glGetProgramResourceiv GETFUNCTION(__teGetProgramResourceiv)
#define glGetProgramResourceLocation GETFUNCTION(__teGetProgramResourceLocation)
#define glGetProgramResourceLocationIndex GETFUNCTION(__teGetProgramResourceLocationIndex)
#define glShaderStorageBlockBinding GETFUNCTION(__teShaderStorageBlockBinding)
#define glTexBufferRange GETFUNCTION(__teTexBufferRange)
#define glTexStorage2DMultisample GETFUNCTION(__teTexStorage2DMultisample)
#define glTexStorage3DMultisample GETFUNCTION(__teTexStorage3DMultisample)
#define glTextureView GETFUNCTION(__teTextureView)
#define glBindVertexBuffer GETFUNCTION(__teBindVertexBuffer)
#define glVertexAttribFormat GETFUNCTION(__teVertexAttribFormat)
#define glVertexAttribIFormat GETFUNCTION(__teVertexAttribIFormat)
#define glVertexAttribLFormat GETFUNCTION(__teVertexAttribLFormat)
#define glVertexAttribBinding GETFUNCTION(__teVertexAttribBinding)
#define glVertexBindingDivisor GETFUNCTION(__teVertexBindingDivisor)
#define glDebugMessageControl GETFUNCTION(__teDebugMessageControl)
#define glDebugMessageInsert GETFUNCTION(__teDebugMessageInsert)
#define glDebugMessageCallback GETFUNCTION(__teDebugMessageCallback)
#define glGetDebugMessageLog GETFUNCTION(__teGetDebugMessageLog)
#define glPushDebugGroup GETFUNCTION(__tePushDebugGroup)
#define glPopDebugGroup GETFUNCTION(__tePopDebugGroup)
#define glObjectLabel GETFUNCTION(__teObjectLabel)
#define glObjectPtrLabel GETFUNCTION(__teObjectPtrLabel)
#define glGetObjectPtrLabel GETFUNCTION(__teGetObjectPtrLabel)

//OpenGL 4.4 Extensions
#define GL_MAX_VERTEX_ATTRIB_STRIDE       0x82E5
#define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#define GL_TEXTURE_BUFFER_BINDING         0x8C2A
#define GL_MAP_PERSISTENT_BIT             0x0040
#define GL_MAP_COHERENT_BIT               0x0080
#define GL_DYNAMIC_STORAGE_BIT            0x0100
#define GL_CLIENT_STORAGE_BIT             0x0200
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 0x00004000
#define GL_BUFFER_IMMUTABLE_STORAGE       0x821F
#define GL_BUFFER_STORAGE_FLAGS           0x8220
#define GL_CLEAR_TEXTURE                  0x9365
#define GL_LOCATION_COMPONENT             0x934A
#define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 0x934B
#define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 0x934C
#define GL_QUERY_BUFFER                   0x9192
#define GL_QUERY_BUFFER_BARRIER_BIT       0x00008000
#define GL_QUERY_BUFFER_BINDING           0x9193
#define GL_QUERY_RESULT_NO_WAIT           0x9194
#define GL_MIRROR_CLAMP_TO_EDGE           0x8743
typedef void (APIENTRYP PFNGLBUFFERSTORAGEPROC) (GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (APIENTRYP PFNGLCLEARTEXIMAGEPROC) (GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARTEXSUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLBINDBUFFERSBASEPROC) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
typedef void (APIENTRYP PFNGLBINDBUFFERSRANGEPROC) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
typedef void (APIENTRYP PFNGLBINDTEXTURESPROC) (GLuint first, GLsizei count, const GLuint *textures);
typedef void (APIENTRYP PFNGLBINDSAMPLERSPROC) (GLuint first, GLsizei count, const GLuint *samplers);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTURESPROC) (GLuint first, GLsizei count, const GLuint *textures);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERSPROC) (GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
extern PFNGLBUFFERSTORAGEPROC __teBufferStorage;
extern PFNGLCLEARTEXIMAGEPROC __teClearTexImage;
extern PFNGLCLEARTEXSUBIMAGEPROC __teClearTexSubImage;
extern PFNGLBINDBUFFERSBASEPROC __teBindBuffersBase;
extern PFNGLBINDBUFFERSRANGEPROC __teBindBuffersRange;
extern PFNGLBINDTEXTURESPROC __teBindTextures;
extern PFNGLBINDSAMPLERSPROC __teBindSamplers;
extern PFNGLBINDIMAGETEXTURESPROC __teBindImageTextures;
extern PFNGLBINDVERTEXBUFFERSPROC __teBindVertexBuffers;
#define glBufferStorage GETFUNCTION(__teBufferStorage)
#define glClearTexImage GETFUNCTION(__teClearTexImage)
#define glClearTexSubImage GETFUNCTION(__teClearTexSubImage)
#define glBindBuffersBase GETFUNCTION(__teBindBuffersBase)
#define glBindBuffersRange GETFUNCTION(__teBindBuffersRange)
#define glBindTextures GETFUNCTION(__teBindTextures)
#define glBindSamplers GETFUNCTION(__teBindSamplers)
#define glBindImageTextures GETFUNCTION(__teBindImageTextures)
#define glBindVertexBuffers GETFUNCTION(__teBindVertexBuffers)

class TinyExtender
{
public:
	
	TinyExtender(){}
	~TinyExtender(){}

	static GLvoid InitializeExtensions()
	{
		TinyExtender::InitializeGLVersion();
		GLuint Version_Major, Version_Minor;
		Version_Major = TinyExtender::GLVersion_Major;
		Version_Minor = TinyExtender::GLVersion_Minor;

		//this was a bad idea...
		//(Version_Major >= 1 && Version_Minor >= 2) ? Load1_2Extensions() : TinyExtender::PrintErrorMessage(Version_Major, Version_Minor);

		if (Version_Major > 1 || (Version_Minor >= 2 && Version_Major >= 1))
		{
			Load1_2Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(1, 2);
			return;
		}

		if (Version_Major > 1 || (Version_Minor >= 3 && Version_Major >= 1))
		{
			Load1_3Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(1, 3);
			return;
		}

		if (Version_Major > 1 || (Version_Minor >= 4 && Version_Major >= 1))
		{
			Load1_4Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(1, 4);
			return;
		}

		if (Version_Major > 1 || (Version_Minor >= 5 && Version_Major >= 1))
		{
			Load1_5Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(1, 5);
			return;
		}

		if (Version_Major > 2 || (Version_Minor >= 0 && Version_Major >= 2))
		{
			Load2_0Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(2, 0);
			return;
		}

		if (Version_Major > 2 || (Version_Minor >= 1 && Version_Major >= 2))
		{
			Load2_1Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(2, 1);
			return;
		}

		if (Version_Major > 3 || (Version_Minor >= 0 && Version_Major >= 3))
		{
			Load3_0Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(3, 0);
			return;
		}

		if (Version_Major > 3 || (Version_Minor >= 1 && Version_Major >= 3))
		{
			Load3_1Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(3, 1);
			return;
		}

		if (Version_Major > 3 || (Version_Minor >= 2 && Version_Major >= 3))
		{
			Load3_2Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(3, 2);
			return;
		}

		if (Version_Major > 3 || (Version_Minor >= 3 && Version_Major >= 3))
		{
			Load3_3Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(3, 3);
			return;
		}

		if (Version_Major > 4 || (Version_Minor >= 0 && Version_Major >= 4))
		{
			Load4_0Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(4, 0);
			return;
		}

		if (Version_Major > 4 || (Version_Minor >= 1 && Version_Major >= 4))
		{
			Load4_1Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(4, 1);
			return;
		}

		if (Version_Major > 4 || (Version_Minor >= 2 && Version_Major >= 4))
		{
			Load4_2Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(4, 2);
			return;
		}

		if (Version_Major > 4 || (Version_Minor >= 3 && Version_Minor >= 4))
		{
			Load4_3Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(4, 3);
		}

		if (Version_Major > 4 || (Version_Minor >= 4 && Version_Major >= 4))
		{
			Load4_4Extensions();
		}

		else
		{
			TinyExtender::PrintErrorMessage(4, 4);
			return;
		}
	}

	static GLvoid InitializeExtensionsSpecific(GLbitfield OpenGLVersions)
	{
		TinyExtender::InitializeGLVersion();
		GLuint Version_Major = TinyExtender::GLVersion_Major;
		GLuint Version_Minor = TinyExtender::GLVersion_Minor;

		if (OpenGLVersions & GLVERSION1_2)
		{
			if (Version_Major > 1 || (Version_Minor >= 2 && Version_Major >= 1))
			{
				TinyExtender::Load1_2Extensions();
			}

			TinyExtender::PrintErrorMessage(1, 2);
		}

		if (OpenGLVersions & GLVERSION1_3)
		{
			if (Version_Major > 1 || (Version_Minor >= 3 && Version_Major >= 1))
			{
				TinyExtender::Load1_3Extensions();
			}

			TinyExtender::PrintErrorMessage(1, 3);
		}

		if (OpenGLVersions & GLVERSION1_4)
		{
			if (Version_Major > 1 || (Version_Minor >= 4 && Version_Major >= 1))
			{
				TinyExtender::Load1_4Extensions();
			}

			TinyExtender::PrintErrorMessage(1, 4);
		}

		if (OpenGLVersions & GLVERSION1_5)
		{
			if (Version_Major > 1 || (Version_Minor >= 5 && Version_Major >= 1))
			{
				TinyExtender::Load1_5Extensions();
			}

			TinyExtender::PrintErrorMessage(1, 5);
		}

		if (OpenGLVersions & GLVERSION2_0)
		{
			if (Version_Major > 2 || (Version_Minor >= 0 && Version_Major >= 2))
			{
				TinyExtender::Load2_0Extensions();
			}

			TinyExtender::PrintErrorMessage(2, 0);
		}

		if (OpenGLVersions & GLVERSION2_1)
		{
			if (Version_Major > 2 || (Version_Minor >= 1 && Version_Major >= 2))
			{
				TinyExtender::Load2_1Extensions();
			}

			TinyExtender::PrintErrorMessage(2, 1);
		}

		if (OpenGLVersions & GLVERSION3_0)
		{
			if (Version_Major > 3 || (Version_Minor >= 0 && Version_Major >= 3))
			{
				TinyExtender::Load3_0Extensions();
			}

			TinyExtender::PrintErrorMessage(3, 0);
		}

		if (OpenGLVersions & GLVERSION3_1)
		{
			if (Version_Major > 3 || (Version_Minor >= 1 && Version_Major >= 3))
			{
				TinyExtender::Load3_1Extensions();
			}

			TinyExtender::PrintErrorMessage(3, 1);
		}

		if (OpenGLVersions & GLVERSION3_2)
		{
			if (Version_Major > 3 || (Version_Minor >= 2 && Version_Major >= 3))
			{
				TinyExtender::Load3_2Extensions();
			}

			TinyExtender::PrintErrorMessage(3, 2);
		}

		if (OpenGLVersions & GLVERSION3_3)
		{
			if (Version_Major > 3 || (Version_Minor >= 3 && Version_Major >= 3))
			{
				TinyExtender::Load3_3Extensions();
			}

			TinyExtender::PrintErrorMessage(3, 3);
		}

		if (OpenGLVersions & GLVERSION4_0)
		{
			if (Version_Major > 4 || (Version_Minor >= 0 && Version_Major >= 4))
			{
				TinyExtender::Load4_0Extensions();
			}

			TinyExtender::PrintErrorMessage(4, 0);
		}

		if (OpenGLVersions & GLVERSION4_1)
		{
			if (Version_Major > 4 || (Version_Minor >= 1 && Version_Major >= 4))
			{
				TinyExtender::Load4_1Extensions();
			}

			TinyExtender::PrintErrorMessage(4, 1);
		}

		if (OpenGLVersions & GLVERSION4_2)
		{
			if (Version_Major > 4 || (Version_Minor >= 2 && Version_Major >= 4))
			{
				TinyExtender::Load4_2Extensions();
			}

			TinyExtender::PrintErrorMessage(4, 2);
		}

		if (OpenGLVersions & GLVERSION4_3)
		{
			if (Version_Major > 4 || (Version_Minor >= 3 && Version_Major >= 4))
			{
				TinyExtender::Load4_3Extensions();
			}

			TinyExtender::PrintErrorMessage(4, 3);
		}

		if (OpenGLVersions & GLVERSION4_4)
		{
			if (Version_Major > 4 || (Version_Minor >= 4 && Version_Major >= 4))
			{
				TinyExtender::Load4_4Extensions();
			}

			TinyExtender::PrintErrorMessage(4, 4);
		}
	}

	static GLvoid GetOpenGLVersion(GLuint& Version_Major, GLuint& Version_Minor)
	{
		Version_Major = TinyExtender::GLVersion_Major;
		Version_Minor = TinyExtender::GLVersion_Minor;
	}
	
	static GLboolean IsExtensionSupported(GLubyte* ExtensionName)
	{
		GLubyte* End; //the last extension name in Extensions 
		GLint NameLength; //the string length of the given extension

		NameLength = strlen((const char*)ExtensionName); // the length of the given extension name string 

		GLubyte* Extensions = (GLubyte*)glGetString(GL_EXTENSIONS); // get all supported extensions

		//if extensions is not empty
		if (Extensions)
		{
			End = Extensions + strlen((const char*)Extensions);

			while (Extensions < End)
			{
				GLint Blarg = strcspn((const char*)Extensions, " ");
				if ((NameLength == Blarg) && (strncmp((const char*)ExtensionName, (const char*)Extensions, Blarg) == 0))
				{
					return GL_TRUE;
				}

				Extensions += (Blarg + 1);
			}
			return GL_FALSE;
		}
		return GL_FALSE;
	}

private:
	static GLuint GLVersion_Major, GLVersion_Minor;

	static inline GLvoid Load1_2Extensions()
	{
		glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawRangeElements");
		glTexImage3D = (PFNGLTEXIMAGE3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexImage3D");
		glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexSubImage3D");
		glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCopyTexSubImage3D");
	}

	static inline GLvoid Load1_3Extensions()
	{
		glActiveTexture = (PFNGLACTIVETEXTUREPROC)TinyExtender::GetProcAddress((const GLubyte*)"glActiveTexture");
		glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSampleCoverage");
		glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCompressedTexImage3D");
		glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCompressedTexImage2D");
		glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCompressedTexImage1D");
		glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCompressedTexSubImage3D");
		glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCompressedTexSubImage2D");
		glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCompressedTexSubImage1D");
	}

	static inline GLvoid Load1_4Extensions()
	{
		glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBlendFuncSeparate");
		glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiDrawArrays");
		glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiDrawElements");
		glPointParameterf = (PFNGLPOINTPARAMETERFPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPointParameterf");
		glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPointParameterfv");
		glPointParameteri = (PFNGLPOINTPARAMETERIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPointParameteri");
		glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPointParameteriv");
		glFogCoordf = (PFNGLFOGCOORDFPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFogCoordf");
		glFogCoordfv = (PFNGLFOGCOORDFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFogCoordfv");
		glFogCoordd = (PFNGLFOGCOORDDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFogCoordd");
		glFogCoorddv = (PFNGLFOGCOORDDVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFogCoorddv");
		glFogCoordPointer = (PFNGLFOGCOORDPOINTERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFogCoordPointer");
		glSecondaryColor3b = (PFNGLSECONDARYCOLOR3BPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3b");
		glSecondaryColor3bv = (PFNGLSECONDARYCOLOR3BVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3bv");
		glSecondaryColor3d = (PFNGLSECONDARYCOLOR3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3d");
		glSecondaryColor3dv = (PFNGLSECONDARYCOLOR3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3dv");
		glSecondaryColor3f = (PFNGLSECONDARYCOLOR3FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3f");
		glSecondaryColor3fv = (PFNGLSECONDARYCOLOR3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3fv");
		glSecondaryColor3i = (PFNGLSECONDARYCOLOR3IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3i");
		glSecondaryColor3iv = (PFNGLSECONDARYCOLOR3IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3iv");
		glSecondaryColor3s = (PFNGLSECONDARYCOLOR3SPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3s");
		glSecondaryColor3sv = (PFNGLSECONDARYCOLOR3SVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3sv");
		glSecondaryColor3ub = (PFNGLSECONDARYCOLOR3UBPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3ub");
		glSecondaryColor3ubv = (PFNGLSECONDARYCOLOR3UBVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3ubv");
		glSecondaryColor3ui = (PFNGLSECONDARYCOLOR3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3ui");
		glSecondaryColor3uiv = (PFNGLSECONDARYCOLOR3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3uiv");
		glSecondaryColor3us = (PFNGLSECONDARYCOLOR3USPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3us");
		glSecondaryColor3usv = (PFNGLSECONDARYCOLOR3USVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColor3usv");
		glSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColorPointer");
		glWindowPos2d = (PFNGLWINDOWPOS2DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos2d");
		glWindowPos2dv = (PFNGLWINDOWPOS2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos2dv");
		glWindowPos2f = (PFNGLWINDOWPOS2FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos2f");
		glWindowPos2fv = (PFNGLWINDOWPOS2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos2fv");
		glWindowPos2i = (PFNGLWINDOWPOS2IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos2i");
		glWindowPos2iv = (PFNGLWINDOWPOS2IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos2iv");
		glWindowPos2s = (PFNGLWINDOWPOS2SPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos2s");
		glWindowPos2sv = (PFNGLWINDOWPOS2SVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos2sv");
		glWindowPos3d = (PFNGLWINDOWPOS3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos3d");
		glWindowPos3dv = (PFNGLWINDOWPOS3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos3dv");
		glWindowPos3f = (PFNGLWINDOWPOS3FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos3f");
		glWindowPos3fv = (PFNGLWINDOWPOS3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos3fv");
		glWindowPos3i = (PFNGLWINDOWPOS3IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos3i");
		glWindowPos3iv = (PFNGLWINDOWPOS3IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos3iv");
		glWindowPos3s = (PFNGLWINDOWPOS3SPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos3s");
		glWindowPos3sv = (PFNGLWINDOWPOS3SVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWindowPos3sv");
		glBlendColor = (PFNGLBLENDCOLORPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBlendColor");
		glBlendEquation = (PFNGLBLENDEQUATIONPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBlendEquation");
	}

	static inline GLvoid Load1_5Extensions()
	{
		glGenQueries = (PFNGLGENQUERIESPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGenQueries");
		glDeleteQueries = (PFNGLDELETEQUERIESPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteQueries");
		glIsQuery = (PFNGLISQUERYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsQuery");
		glBeginQuery = (PFNGLBEGINQUERYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBeginQuery");
		glEndQuery = (PFNGLENDQUERYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glEndQuery");
		glGetQueryiv = (PFNGLGETQUERYIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetQueryiv");
		glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetQueryObjectiv");
		glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetQueryObjectuiv");
		glBindBuffer = (PFNGLBINDBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindBuffer");
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteBuffers");
		glGenBuffers = (PFNGLGENBUFFERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGenBuffers");
		glIsBuffer = (PFNGLISBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBufferData");
		glBufferSubData = (PFNGLBUFFERSUBDATAPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBufferSubData");
		glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetBufferSubData");
		glMapBuffer = (PFNGLMAPBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMapBuffer");
		glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUnmapBuffer");
		glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetBufferParameteriv");
		glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetBufferPointerv");
	}

	static inline GLvoid Load2_0Extensions()
	{
		glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBlendEquationSeparate");
		glDrawBuffers = (PFNGLDRAWBUFFERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawBuffers");
		glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glStencilOpSeparate");
		glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glStencilFuncSeparate");
		glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glStencilMaskSeparate");
		glAttachShader = (PFNGLATTACHSHADERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glAttachShader");
		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindAttribLocation");
		glCompileShader = (PFNGLCOMPILESHADERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCompileShader");
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCreateProgram");
		glCreateShader = (PFNGLCREATESHADERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCreateShader");
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteProgram");
		glDeleteShader = (PFNGLDELETESHADERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteShader");
		glDetachShader = (PFNGLDETACHSHADERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDetachShader");
		glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDisableVertexAttribArray");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glEnableVertexAttribArray");
		glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveAttrib");
		glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveUniform");
		glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetAttachedShaders");
		glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetAttribLocation");
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramiv");
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramInfoLog");
		glGetShaderiv = (PFNGLGETSHADERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetShaderiv");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetShaderInfoLog");
		glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetShaderSource");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetUniformLocation");
		glGetUniformfv = (PFNGLGETUNIFORMFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetUniformfv");
		glGetUniformiv = (PFNGLGETUNIFORMIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetUniformiv");
		glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetVertexAttribdv");
		glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetVertexAttribfv");
		glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetVertexAttribiv");
		glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetVertexAttribPointerv");
		glIsProgram = (PFNGLISPROGRAMPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsProgram");
		glIsShader = (PFNGLISSHADERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsShader");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)TinyExtender::GetProcAddress((const GLubyte*)"glLinkProgram");
		glShaderSource = (PFNGLSHADERSOURCEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glShaderSource");
		glUseProgram = (PFNGLUSEPROGRAMPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUseProgram");
		glUniform1f = (PFNGLUNIFORM1FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform1f");
		glUniform2f = (PFNGLUNIFORM2FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform2f");
		glUniform3f = (PFNGLUNIFORM3FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform3f");
		glUniform4f = (PFNGLUNIFORM4FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform4f");
		glUniform1i = (PFNGLUNIFORM1IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform1i");
		glUniform2i = (PFNGLUNIFORM2IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform2i");
		glUniform3i = (PFNGLUNIFORM3IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform3i");
		glUniform4i = (PFNGLUNIFORM4IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform4i");
		glUniform1fv = (PFNGLUNIFORM1FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform1fv");
		glUniform2fv = (PFNGLUNIFORM2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform2fv");
		glUniform3fv = (PFNGLUNIFORM3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform3fv");
		glUniform4fv = (PFNGLUNIFORM4FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform4fv");
		glUniform1iv = (PFNGLUNIFORM1IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform1iv");
		glUniform2iv = (PFNGLUNIFORM2IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform2iv");
		glUniform3iv = (PFNGLUNIFORM3IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform3iv");
		glUniform4iv = (PFNGLUNIFORM4IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform4iv");
		glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix2fv");
		glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix3fv");
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix4fv");
		glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)TinyExtender::GetProcAddress((const GLubyte*)"glValidateProgram");
		glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib1d");
		glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib1dv");
		glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib1f");
		glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib1fv");
		glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib1s");
		glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib1sv");
		glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib2d");
		glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib2dv");
		glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib2f");
		glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib2fv");
		glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib2s");
		glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib2sv");
		glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib3d");
		glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib3dv");
		glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib3f");
		glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib3fv");
		glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib3s");
		glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib3sv");
		glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4Nbv");
		glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4Niv");
		glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4Nsv");
		glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4Nub");
		glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4Nubv");
		glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4Nuiv");
		glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4Nusv");
		glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4bv");
		glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4d");
		glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4dv");
		glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4f");
		glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4fv");
		glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4iv");
		glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4s");
		glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4sv");
		glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4ubv");
		glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4uiv");
		glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4usv");
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribPointer");
	}

	static inline GLvoid Load2_1Extensions()
	{
		glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix2x3fv");
		glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix3x2fv");
		glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix2x4fv");
		glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix4x2fv");
		glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix3x4fv");
		glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix4x3fv");
	}

	static inline GLvoid Load3_0Extensions()
	{
		glColorMaski = (PFNGLCOLORMASKIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glColorMaski");
		glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetBooleani_v");
		glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetIntegeri_v");
		glEnablei = (PFNGLENABLEIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glEnablei");
		glDisablei = (PFNGLDISABLEIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDisablei");
		glIsEnabledi = (PFNGLISENABLEDIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsEnabledi");
		glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBeginTransformFeedback");
		glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)TinyExtender::GetProcAddress((const GLubyte*)"glEndTransformFeedback");
		glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindBufferRange");
		glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindBufferBase");
		glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTransformFeedbackVaryings");
		glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetTransformFeedbackVarying");
		glClampColor = (PFNGLCLAMPCOLORPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClampColor");
		glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBeginConditionalRender");
		glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glEndConditionalRender");
		glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribIPointer");
		glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetVertexAttribIiv");
		glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetVertexAttribIuiv");
		glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI1i");
		glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI2i");
		glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI3i");
		glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI4i");
		glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI1ui");
		glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI2ui");
		glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI3ui");
		glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI4ui");
		glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI1iv");
		glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI2iv");
		glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI3iv");
		glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI4iv");
		glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI1uiv");
		glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI2uiv");
		glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI3uiv");
		glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI4uiv");
		glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI4bv");
		glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI4sv");
		glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI4ubv");
		glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribI4usv");
		glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetUniformuiv");
		glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindFragDataLocation");
		glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetFragDataLocation");
		glUniform1ui = (PFNGLUNIFORM1UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform1ui");
		glUniform2ui = (PFNGLUNIFORM2UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform2ui");
		glUniform3ui = (PFNGLUNIFORM3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform3ui");
		glUniform4ui = (PFNGLUNIFORM4UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform4ui");
		glUniform1uiv = (PFNGLUNIFORM1UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform1uiv");
		glUniform2uiv = (PFNGLUNIFORM2UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform2uiv");
		glUniform3uiv = (PFNGLUNIFORM3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform3uiv");
		glUniform4uiv = (PFNGLUNIFORM4UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform4uiv");
		glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexParameterIiv");
		glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexParameterIuiv");
		glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetTexParameterIiv");
		glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetTexParameterIuiv");
		glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClearBufferiv");
		glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClearBufferuiv");
		glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClearBufferfv");
		glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClearBufferi");
		glGetStringi = (PFNGLGETSTRINGIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetStringi");
		glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsRenderbuffer");
		glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindRenderbuffer");
		glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteRenderbuffers");
		glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGenRenderbuffers");
		glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glRenderbufferStorage");
		glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetRenderbufferParameteriv");
		glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsFramebuffer");
		glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindFramebuffer");
		glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteFramebuffers");
		glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGenFramebuffers");
		glCheckFrameBufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCheckFrameBufferStatus");
		glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFramebufferTexture1D");
		glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFramebufferTexture2D");
		glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFramebufferTexture3D");
		glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFramebufferRenderbuffer");
		glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetFramebufferAttachmentParameteriv");
		glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGenerateMapmap");
		glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBlitFramebuffer");
		glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glRenderbufferStorageMultisample");
		glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFramebufferTextureLayer");
		glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMapBufferRange");
		glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFlushMappedBufferRange");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindVertexArray");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteVertexArrays");
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGenVertexArrays");
		glIsVertexArray = (PFNGLISVERTEXARRAYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsVertexArray");
	}

	static inline GLvoid Load3_1Extensions()
	{
		glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawArraysInstanced");
		glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawElementsInstanced");
		glTexBuffer = (PFNGLTEXBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexBuffer");
		glPrimtiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPrimtiveRestartIndex");
		glCopyBufferSubdata = (PFNGLCOPYBUFFERSUBDATAPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCopyBufferSubdata");
		glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetUniformIndices");
		glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveUniformsiv");
		glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveUniformName");
		glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetUniformBlockIndex");
		glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveUniformBlockiv");
		glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveUniformBlockName");
		glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformBlockBinding");
	}

	static inline GLvoid Load3_2Extensions()
	{
		glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawElementsBaseVertex");
		glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawRangeElementsBaseVertex");
		glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawElementsInstancedBaseVertex");
		glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiDrawElementsBaseVertex");
		glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProvokingVertex");
		glFenceSync = (PFNGLFENCESYNCPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFenceSync");
		glIsSync = (PFNGLISSYNCPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsSync");
		glDeleteSync = (PFNGLDELETESYNCPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteSync");
		glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClientWaitSync");
		glWaitSync = (PFNGLWAITSYNCPROC)TinyExtender::GetProcAddress((const GLubyte*)"glWaitSync");
		glGetInteger64v = (PFNGLGETINTEGER64VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetInteger64v");
		glGetSynciv = (PFNGLGETSYNCIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetSynciv");
		glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetInteger64i_v");
		glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetBufferParameteri64v");
		glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFramebufferTexture");
		glTexImage2DMultiSample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexImage2DMultiSample");
		glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexImage3DMultisample");
		glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetMultisamplefv");
		glSampleMaski = (PFNGLSAMPLEMASKIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSampleMaski");
	}
	
	static inline GLvoid Load3_3Extensions()
	{
		glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindFragDataLocationIndexed");
		glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetFragDataIndex");
		glGenSamplers = (PFNGLGENSAMPLERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGenSamplers");
		glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteSamplers");
		glIsSampler = (PFNGLISSAMPLERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsSampler");
		glBindSampler = (PFNGLBINDSAMPLERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindSampler");
		glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSamplerParameteri");
		glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSamplerParameteriv");
		glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSamplerParameterf");
		glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSamplerParameterfv");
		glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSamplerParameterIiv");
		glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSamplerParameterIuiv");
		glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetSamplerParameteriv");
		glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetSamplerParameterIiv");
		glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetSamplerParameterfv");
		glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetSamplerParameterIuiv");
		glQueryCounter = (PFNGLQUERYCOUNTERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glQueryCounter");
		glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetQueryObjecti64v");
		glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetQueryObjectui64v");
		glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribDivisor");
		glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribP1ui");
		glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribP1uiv");
		glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribP2ui");
		glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribP2uiv");
		glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribP3ui");
		glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribP3uiv");
		glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribP4ui");
		glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttrib4uiv");
		glVertexP2ui = (PFNGLVERTEXP2UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexP2ui");
		glVertexP2uiv = (PFNGLVERTEXP2UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexP2uiv");
		glVertexP3ui = (PFNGLVERTEXP3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexP3ui");
		glVertexP3uiv = (PFNGLVERTEXP3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexP3uiv");
		glVertexP4ui = (PFNGLVERTEXP4UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexP4ui");
		glVertexP4uiv = (PFNGLVERTEXP4UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexP4uiv");
		glTexCoordP1ui = (PFNGLTEXCOORDP1UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexCoordP1ui");
		glTexCoordP1uiv = (PFNGLTEXCOORDP1UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexCoordP1uiv");
		glTexCoordP2ui = (PFNGLTEXCOORDP2UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexCoordP2ui");
		glTexCoordP2uiv = (PFNGLTEXCOORDP2UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexCoordP2uiv");
		glTexCoordP3ui = (PFNGLTEXCOORDP3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexCoordP3ui");
		glTexCoordP3uiv = (PFNGLTEXCOORDP3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexCoordP3uiv");
		glTexCoordP4ui = (PFNGLTEXCOORDP4UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexCoordP4ui");
		glTexCoordP4uiv = (PFNGLTEXCOORDP4UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexCoordP4uiv");
		glMultiTexCoordP1ui = (PFNGLMULTITEXCOORDP1UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiTexCoordP1ui");
		glMultiTexCoordP1uiv = (PFNGLMULTITEXCOORDP1UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiTexCoordP1uiv");
		glMultiTexCoordP2ui = (PFNGLMULTITEXCOORDP2UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiTexCoordP2ui");
		glMultiTexCoordP2uiv = (PFNGLMULTITEXCOORDP2UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiTexCoordP2uiv");
		glMultiTexCoordP3ui = (PFNGLMULTITEXCOORDP3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiTexCoordP3ui");
		glMultiTexCoordP3uiv = (PFNGLMULTITEXCOORDP3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiTexCoordP3uiv");
		glMultiTexCoordP4ui = (PFNGLMULTITEXCOORDP4UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiTexCoordP4ui");
		glMultiTexCoordP4uiv = (PFNGLMULTITEXCOORDP4UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiTexCoordP4uiv");
		glNormalP3ui = (PFNGLNORMALP3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glNormalP3ui");
		glNormalP3uiv = (PFNGLNORMALP3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glNormalP3uiv");
		glColorP3ui = (PFNGLCOLORP3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glColorP3ui");
		glColorP3uiv = (PFNGLCOLORP3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glColorP3uiv");
		glColorP4ui = (PFNGLCOLORP4UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glColorP4ui");
		glColorP4uiv = (PFNGLCOLORP4UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glColorP4uiv");
		glSecondaryColorP3ui = (PFNGLSECONDARYCOLORP3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColorP3ui");
		glSecondaryColorP3uiv = (PFNGLSECONDARYCOLORP3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glSecondaryColorP3uiv");
	}

	static inline GLvoid Load4_0Extensions()
	{
		glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMinSampleShading");
		glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBlendEquationi");
		glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBlendEquationSeparatei");
		glBlendFunci = (PFNGLBLENDFUNCIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBlendFunci");
		glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBlendFuncSeparatei");
		glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawArraysIndirect");
		glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawElementsIndirect");
		glUniform1d = (PFNGLUNIFORM1DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform1d");
		glUniform2d = (PFNGLUNIFORM2DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform2d");
		glUniform3d = (PFNGLUNIFORM3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform3d");
		glUniform4d = (PFNGLUNIFORM4DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform4d");
		glUniform1dv = (PFNGLUNIFORM1DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform1dv");
		glUniform2dv = (PFNGLUNIFORM2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform2dv");
		glUniform3dv = (PFNGLUNIFORM3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform3dv");
		glUniform4dv = (PFNGLUNIFORM4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniform4dv");
		glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix2dv");
		glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix3dv");
		glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix4dv");
		glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix2x3dv");
		glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix2x4dv");
		glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix3x2dv");
		glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix3x4dv");
		glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix4x2dv");
		glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformMatrix4x3dv");
		glGetUniformdv = (PFNGLGETUNIFORMDVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetUniformdv");
		glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetSubroutineUniformLocation");
		glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetSubroutineIndex");
		glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveSubroutineUniformiv");
		glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveSubroutineUniformName");
		glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveSubroutineName");
		glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUniformSubroutinesuiv");
		glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetUniformSubroutineuiv");
		glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramStageiv");
		glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPatchParameteri");
		glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPatchParameterfv");
		glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindTransformFeedback");
		glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteTransformFeedbacks");
		glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGenTransformFeedbacks");
		glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsTransformFeedback");
		glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPauseTransformFeedback");
		glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)TinyExtender::GetProcAddress((const GLubyte*)"glResumeTransformFeedback");
		glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawTransformFeedback");
		glDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawTransformFeedbackStream");
		glBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBeginQueryIndexed");
		glEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glEndQueryIndexed");
		glGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetQueryIndexediv");
	}

	static inline GLvoid Load4_1Extensions()
	{
		glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glReleaseShaderCompiler");
		glShaderBinary = (PFNGLSHADERBINARYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glShaderBinary");
		glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetShaderPrecisionFormat");
		glDepthRangef = (PFNGLDEPTHRANGEFPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDepthRangef");
		glClearDepthf = (PFNGLCLEARDEPTHFPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClearDepthf");
		glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramBinary");
		glProgramBinary = (PFNGLPROGRAMBINARYPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramBinary");
		glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramParameteri");
		glUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)TinyExtender::GetProcAddress((const GLubyte*)"glUseProgramStages");
		glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)TinyExtender::GetProcAddress((const GLubyte*)"glActiveShaderProgram");
		glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCreateShaderProgramv");
		glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindProgramPipeline");
		glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDeleteProgramPipelines");
		glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGenProgramPipelines");
		glIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glIsProgramPipeline");
		glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramPipelineiv");
		glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform1i");
		glProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform1iv");
		glProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform1f");
		glProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform1fv");
		glProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform1d");
		glProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform1dv");
		glProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform1ui");
		glProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform1uiv");
		glProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform2i");
		glProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform2iv");
		glProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform2f");
		glProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform2fv");
		glProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform2d");
		glProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform2dv");
		glProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform2ui");
		glProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform2uiv");
		glProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform3i");
		glProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform3iv");
		glProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform3f");
		glProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform3fv");
		glProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform3d");
		glProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform3dv");
		glProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform3ui");
		glProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform3uiv");
		glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform4i");
		glProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform4iv");
		glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform4f");
		glProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform4fv");
		glProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform4d");
		glProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform4dv");
		glProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform4ui");
		glProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniform4uiv");
		glProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix2fv");
		glProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix3fv");
		glProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix4fv");
		glProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix2dv");
		glProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix3dv");
		glProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix4dv");
		glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix2x3fv");
		glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix3x2fv");
		glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix2x4fv");
		glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix4x2fv");
		glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix3x4fv");
		glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix4x3fv");
		glProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix2x3dv");
		glProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix3x2dv");
		glProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix2x4dv");
		glProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix4x2dv");
		glProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix3x4dv");
		glProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glProgramUniformMatrix4x3dv");
		glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glValidateProgramPipeline");
		glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramPipelineInfoLog");
		glVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribL1d");
		glVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribL2d");
		glVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribL3d");
		glVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribL4d");
		glVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribL1dv");
		glVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribL2dv");
		glVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribL3dv");
		glVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribL4dv");
		glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribLPointer");
		glGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetVertexAttribLdv");
		glViewportarrayv = (PFNGLVIEWPORTARRAYVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glViewportarrayv");
		glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)TinyExtender::GetProcAddress((const GLubyte*)"glViewportIndexedf");
		glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glViewportIndexedfv");
		glScissorArrayv = (PFNGLSCISSORARRAYVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glScissorArrayv");
		glScissorIndexed = (PFNGLSCISSORINDEXEDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glScissorIndexed");
		glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glScissorIndexedv");
		glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDepthRangeIndexed");
		glGetFloati_v = (PFNGLGETFLOATI_VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetFloati_v");
		glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetDoublei_v");
	}

	static inline GLvoid Load4_2Extensions()
	{
		glDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawArraysInstancedBaseInstance");
		glDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawElementsInstancedBaseInstance");
		glDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawElementsInstancedBaseVertexBaseInstance");
		glGetInternalFormativ = (PFNGLGETINTERNALFORMATIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetInternalFormativ");
		glGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetActiveAtomicCounterBufferiv");
		glBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindImageTexture");
		glMemoryBarrier = (PFNGLMEMORYBARRIERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMemoryBarrier");
		glTexStorage1D = (PFNGLTEXSTORAGE1DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexStorage1D");
		glTexStorage2D = (PFNGLTEXSTORAGE2DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexStorage2D");
		glTexStorage3D = (PFNGLTEXSTORAGE3DPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexStorage3D");
		glDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawTransformFeedbackInstanced");
		glDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDrawTransformFeedbackStreamInstanced");
	}

	static inline GLvoid Load4_3Extensions()
	{
		glClearBufferData = (PFNGLCLEARBUFFERDATAPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClearBufferData");
		glClearBufferSubdata = (PFNGLCLEARBUFFERSUBDATAPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClearBufferSubdata");
		glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDispatchCompute");
		glDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDispatchComputeIndirect");
		glCopyImageSubdata = (PFNGLCOPYIMAGESUBDATAPROC)TinyExtender::GetProcAddress((const GLubyte*)"glCopyImageSubdata");
		glFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC)TinyExtender::GetProcAddress((const GLubyte*)"glFramebufferParameteri");
		glGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetFramebufferParameteriv");
		glGetInternalFormati64v = (PFNGLGETINTERNALFORMATI64VPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetInternalFormati64v");
		glInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glInvalidateTexSubImage");
		glInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glInvalidateTexImage");
		glInvalidateBufferSubdata = (PFNGLINVALIDATEBUFFERSUBDATAPROC)TinyExtender::GetProcAddress((const GLubyte*)"glInvalidateBufferSubdata");
		glInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC)TinyExtender::GetProcAddress((const GLubyte*)"glInvalidateBufferData");
		glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glInvalidateFramebuffer");
		glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glInvalidateSubFramebuffer");
		glMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiDrawArraysIndirect");
		glMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)TinyExtender::GetProcAddress((const GLubyte*)"glMultiDrawElementsIndirect");
		glGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramInterfaceiv");
		glGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramResourceIndex");
		glGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramResourceName");
		glGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramResourceiv");
		glGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramResourceLocation");
		glGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetProgramResourceLocationIndex");
		glShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC)TinyExtender::GetProcAddress((const GLubyte*)"glShaderStorageBlockBinding");
		glTexBufferRange = (PFNGLTEXBUFFERRANGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexBufferRange");
		glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexStorage2DMultisample");
		glTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTexStorage3DMultisample");
		glTextureView = (PFNGLTEXTUREVIEWPROC)TinyExtender::GetProcAddress((const GLubyte*)"glTextureView");
		glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindVertexBuffer");
		glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribFormat");
		glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribIFormat");
		glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribLFormat");
		glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexAttribBinding");
		glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)TinyExtender::GetProcAddress((const GLubyte*)"glVertexBindingDivisor");
		glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDebugMessageControl");
		glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDebugMessageInsert");
		glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)TinyExtender::GetProcAddress((const GLubyte*)"glDebugMessageCallback");
		glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetDebugMessageLog");
		glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPushDebugGroup");
		glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)TinyExtender::GetProcAddress((const GLubyte*)"glPopDebugGroup");
		glObjectLabel = (PFNGLOBJECTLABELPROC)TinyExtender::GetProcAddress((const GLubyte*)"glObjectLabel");
		glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)TinyExtender::GetProcAddress((const GLubyte*)"glObjectPtrLabel");
		glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)TinyExtender::GetProcAddress((const GLubyte*)"glGetObjectPtrLabel");
	}

	static inline GLvoid Load4_4Extensions()
	{
		glBufferStorage = (PFNGLBUFFERSTORAGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBufferStorage");
		glClearTexImage = (PFNGLCLEARTEXIMAGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClearTexImage");
		glClearTexSubImage = (PFNGLCLEARTEXSUBIMAGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glClearTexSubImage");
		glBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindBuffersBase");
		glBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindBuffersRange");
		glBindTextures = (PFNGLBINDTEXTURESPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindTextures");
		glBindSamplers = (PFNGLBINDSAMPLERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindSamplers");
		glBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindImageTextures");
		glBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC)TinyExtender::GetProcAddress((const GLubyte*)"glBindVertexBuffers");
	}

	static GLvoid InitializeGLVersion()
	{
		const GLubyte* VersionString = glGetString(GL_VERSION);

		TinyExtender::GLVersion_Major = VersionString[0] - '0';
		TinyExtender::GLVersion_Minor = VersionString[2] - '0';
	}

	static GLvoid PrintErrorMessage(GLuint Version_Major, GLuint Version_Minor)
	{
		printf("Error: OpenGL version %i.%i not supported. stopping here\n", Version_Major, Version_Minor);
	}

	static void* GetProcAddress(const GLubyte* ProcName)
	{
#if defined(_WIN32)
		return wglGetProcAddress((LPCTSTR)ProcName);
#endif

#if defined(__linux__)
		return glXGetProcAddress(ProcName);
#endif
	}
};

//#if defined(__linux__)
//OpenGL 1.2 Extensions
PFNGLDRAWRANGEELEMENTSPROC __teDrawRangeElements = 0;
PFNGLTEXIMAGE3DPROC __teTexImage3D = 0;
PFNGLTEXSUBIMAGE3DPROC __teTexSubImage3D = 0;
PFNGLCOPYTEXSUBIMAGE3DPROC __teCopyTexSubImage3D = 0;
//OpenGL 1.3 Extensions
PFNGLACTIVETEXTUREPROC __teActiveTexture = 0;
PFNGLSAMPLECOVERAGEPROC __teSampleCoverage = 0;
PFNGLCOMPRESSEDTEXIMAGE3DPROC __teCompressedTexImage3D = 0;
PFNGLCOMPRESSEDTEXIMAGE2DPROC __teCompressedTexImage2D = 0;
PFNGLCOMPRESSEDTEXIMAGE1DPROC __teCompressedTexImage1D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC __teCompressedTexSubImage3D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC __teCompressedTexSubImage2D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC __teCompressedTexSubImage1D = 0;
PFNGLGETCOMPRESSEDTEXIMAGEPROC __teGetCompressedTexImage = 0;
PFNGLCLIENTACTIVETEXTUREPROC __teClientActiveTexture = 0;
PFNGLMULTITEXCOORD1DPROC __teMultiTexCoord1d = 0;
PFNGLMULTITEXCOORD1DVPROC __teMultiTexCoord1dv = 0;
PFNGLMULTITEXCOORD1FPROC __teMultiTexCoord1f = 0;
PFNGLMULTITEXCOORD1FVPROC __teMultiTexCoord1fv = 0;
PFNGLMULTITEXCOORD1IPROC __teMultiTexCoord1i = 0;
PFNGLMULTITEXCOORD1IVPROC __teMultiTexCoord1iv = 0;
PFNGLMULTITEXCOORD1SPROC __teMultiTexCoord1s = 0;
PFNGLMULTITEXCOORD1SVPROC __teMultiTexCoord1sv = 0;
PFNGLMULTITEXCOORD2DPROC __teMultiTexCoord2d = 0;
PFNGLMULTITEXCOORD2DVPROC __teMultiTexCoord2dv = 0;
PFNGLMULTITEXCOORD2FPROC __teMultiTexCoord2f = 0;
PFNGLMULTITEXCOORD2FVPROC __teMultiTexCoord2fv = 0;
PFNGLMULTITEXCOORD2IPROC __teMultiTexCoord2i = 0;
PFNGLMULTITEXCOORD2IVPROC __teMultiTexCoord2iv = 0;
PFNGLMULTITEXCOORD2SPROC __teMultiTexCoord2s = 0;
PFNGLMULTITEXCOORD2SVPROC __teMultiTexCoord2sv = 0;
PFNGLMULTITEXCOORD3DPROC __teMultiTexCoord3d = 0;
PFNGLMULTITEXCOORD3DVPROC __teMultiTexCoord3dv = 0;
PFNGLMULTITEXCOORD3FPROC __teMultiTexCoord3f = 0;
PFNGLMULTITEXCOORD3FVPROC __teMultiTexCoord3fv = 0;
PFNGLMULTITEXCOORD3IPROC __teMultiTexCoord3i = 0;
PFNGLMULTITEXCOORD3IVPROC __teMultiTexCoord3iv = 0;
PFNGLMULTITEXCOORD3SPROC __teMultiTexCoord3s = 0;
PFNGLMULTITEXCOORD3SVPROC __teMultiTexCoord3sv = 0;
PFNGLMULTITEXCOORD4DPROC __teMultiTexCoord4d = 0;
PFNGLMULTITEXCOORD4DVPROC __teMultiTexCoord4dv = 0;
PFNGLMULTITEXCOORD4FPROC __teMultiTexCoord4f = 0;
PFNGLMULTITEXCOORD4FVPROC __teMultiTexCoord4fv = 0;
PFNGLMULTITEXCOORD4IPROC __teMultiTexCoord4i = 0;
PFNGLMULTITEXCOORD4IVPROC __teMultiTexCoord4iv = 0;
PFNGLMULTITEXCOORD4SPROC __teMultiTexCoord4s = 0;
PFNGLMULTITEXCOORD4SVPROC __teMultiTexCoord4sv = 0;
PFNGLLOADTRANSPOSEMATRIXFPROC __teLoadTransposeMatrixf = 0;
PFNGLLOADTRANSPOSEMATRIXDPROC __teLoadTransposeMatrixd = 0;
PFNGLMULTTRANSPOSEMATRIXFPROC __teMultTransposeMatrixf = 0;
PFNGLMULTTRANSPOSEMATRIXDPROC __teMultTransposeMatrixd = 0;

//OpenGL 1.4 Extensions
PFNGLBLENDFUNCSEPARATEPROC __teBlendFuncSeparate = 0;
PFNGLMULTIDRAWARRAYSPROC __teMultiDrawArrays = 0;
PFNGLMULTIDRAWELEMENTSPROC __teMultiDrawElements = 0;
PFNGLPOINTPARAMETERFPROC __tePointParameterf = 0;
PFNGLPOINTPARAMETERFVPROC __tePointParameterfv = 0;
PFNGLPOINTPARAMETERIPROC __tePointParameteri = 0;
PFNGLPOINTPARAMETERIVPROC __tePointParameteriv = 0;
PFNGLFOGCOORDFPROC __teFogCoordf = 0;
PFNGLFOGCOORDFVPROC __teFogCoordfv = 0;
PFNGLFOGCOORDDPROC __teFogCoordd = 0;
PFNGLFOGCOORDDVPROC __teFogCoorddv = 0;
PFNGLFOGCOORDPOINTERPROC __teFogCoordPointer = 0;
PFNGLSECONDARYCOLOR3BPROC __teSecondaryColor3b = 0;
PFNGLSECONDARYCOLOR3BVPROC __teSecondaryColor3bv = 0;
PFNGLSECONDARYCOLOR3DPROC __teSecondaryColor3d = 0;
PFNGLSECONDARYCOLOR3DVPROC __teSecondaryColor3dv = 0;
PFNGLSECONDARYCOLOR3FPROC __teSecondaryColor3f = 0;
PFNGLSECONDARYCOLOR3FVPROC __teSecondaryColor3fv = 0;
PFNGLSECONDARYCOLOR3IPROC __teSecondaryColor3i = 0;
PFNGLSECONDARYCOLOR3IVPROC __teSecondaryColor3iv = 0;
PFNGLSECONDARYCOLOR3SPROC __teSecondaryColor3s = 0;
PFNGLSECONDARYCOLOR3SVPROC __teSecondaryColor3sv = 0;
PFNGLSECONDARYCOLOR3UBPROC __teSecondaryColor3ub = 0;
PFNGLSECONDARYCOLOR3UBVPROC __teSecondaryColor3ubv = 0;
PFNGLSECONDARYCOLOR3UIPROC __teSecondaryColor3ui = 0;
PFNGLSECONDARYCOLOR3UIVPROC __teSecondaryColor3uiv = 0;
PFNGLSECONDARYCOLOR3USPROC __teSecondaryColor3us = 0;
PFNGLSECONDARYCOLOR3USVPROC __teSecondaryColor3usv = 0;
PFNGLSECONDARYCOLORPOINTERPROC __teSecondaryColorPointer = 0;
PFNGLWINDOWPOS2DPROC __teWindowPos2d = 0;
PFNGLWINDOWPOS2DVPROC __teWindowPos2dv = 0;
PFNGLWINDOWPOS2FPROC __teWindowPos2f = 0;
PFNGLWINDOWPOS2FVPROC __teWindowPos2fv = 0;
PFNGLWINDOWPOS2IPROC __teWindowPos2i = 0;
PFNGLWINDOWPOS2IVPROC __teWindowPos2iv = 0;
PFNGLWINDOWPOS2SPROC __teWindowPos2s = 0;
PFNGLWINDOWPOS2SVPROC __teWindowPos2sv = 0;
PFNGLWINDOWPOS3DPROC __teWindowPos3d = 0;
PFNGLWINDOWPOS3DVPROC __teWindowPos3dv = 0;
PFNGLWINDOWPOS3FPROC __teWindowPos3f = 0;
PFNGLWINDOWPOS3FVPROC __teWindowPos3fv = 0;
PFNGLWINDOWPOS3IPROC __teWindowPos3i = 0;
PFNGLWINDOWPOS3IVPROC __teWindowPos3iv = 0;
PFNGLWINDOWPOS3SPROC __teWindowPos3s = 0;
PFNGLWINDOWPOS3SVPROC __teWindowPos3sv = 0;
PFNGLBLENDCOLORPROC __teBlendColor = 0;
PFNGLBLENDEQUATIONPROC __teBlendEquation = 0;
//OpenGL 1.5 Extensions
PFNGLGENQUERIESPROC __teGenQueries = 0;
PFNGLDELETEQUERIESPROC __teDeleteQueries = 0;
PFNGLISQUERYPROC __teIsQuery = 0;
PFNGLBEGINQUERYPROC __teBeginQuery = 0;
PFNGLENDQUERYPROC __teEndQuery = 0;
PFNGLGETQUERYIVPROC __teGetQueryiv = 0;
PFNGLGETQUERYOBJECTIVPROC __teGetQueryObjectiv = 0;
PFNGLGETQUERYOBJECTUIVPROC __teGetQueryObjectuiv = 0;
PFNGLBINDBUFFERPROC __teBindBuffer = 0;
PFNGLDELETEBUFFERSPROC __teDeleteBuffers = 0;
PFNGLGENBUFFERSPROC __teGenBuffers = 0;
PFNGLISBUFFERPROC __teIsBuffer = 0;
PFNGLBUFFERDATAPROC __teBufferData = 0;
PFNGLBUFFERSUBDATAPROC __teBufferSubData = 0;
PFNGLGETBUFFERSUBDATAPROC __teGetBufferSubData = 0;
PFNGLMAPBUFFERPROC __teMapBuffer = 0;
PFNGLUNMAPBUFFERPROC __teUnmapBuffer = 0;
PFNGLGETBUFFERPARAMETERIVPROC __teGetBufferParameteriv = 0;
PFNGLGETBUFFERPOINTERVPROC __teGetBufferPointerv = 0;
//OpenGL 2.0 Extensions
PFNGLBLENDEQUATIONSEPARATEPROC __teBlendEquationSeparate = 0;
PFNGLDRAWBUFFERSPROC __teDrawBuffers = 0;
PFNGLSTENCILOPSEPARATEPROC __teStencilOpSeparate = 0;
PFNGLSTENCILFUNCSEPARATEPROC __teStencilFuncSeparate = 0;
PFNGLSTENCILMASKSEPARATEPROC __teStencilMaskSeparate = 0;
PFNGLATTACHSHADERPROC __teAttachShader = 0;
PFNGLBINDATTRIBLOCATIONPROC __teBindAttribLocation = 0;
PFNGLCOMPILESHADERPROC __teCompileShader = 0;
PFNGLCREATEPROGRAMPROC __teCreateProgram = 0;
PFNGLCREATESHADERPROC __teCreateShader = 0;
PFNGLDELETEPROGRAMPROC __teDeleteProgram = 0;
PFNGLDELETESHADERPROC __teDeleteShader = 0;
PFNGLDETACHSHADERPROC __teDetachShader = 0;
PFNGLDISABLEVERTEXATTRIBARRAYPROC __teDisableVertexAttribArray = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC __teEnableVertexAttribArray = 0;
PFNGLGETACTIVEATTRIBPROC __teGetActiveAttrib = 0;
PFNGLGETACTIVEUNIFORMPROC __teGetActiveUniform = 0;
PFNGLGETATTACHEDSHADERSPROC __teGetAttachedShaders = 0;
PFNGLGETATTRIBLOCATIONPROC __teGetAttribLocation = 0;
PFNGLGETPROGRAMIVPROC __teGetProgramiv = 0;
PFNGLGETPROGRAMINFOLOGPROC __teGetProgramInfoLog = 0;
PFNGLGETSHADERIVPROC __teGetShaderiv = 0;
PFNGLGETSHADERINFOLOGPROC __teGetShaderInfoLog = 0;
PFNGLGETSHADERSOURCEPROC __teGetShaderSource = 0;
PFNGLGETUNIFORMLOCATIONPROC __teGetUniformLocation = 0;
PFNGLGETUNIFORMFVPROC __teGetUniformfv = 0;
PFNGLGETUNIFORMIVPROC __teGetUniformiv = 0;
PFNGLGETVERTEXATTRIBDVPROC __teGetVertexAttribdv = 0;
PFNGLGETVERTEXATTRIBFVPROC __teGetVertexAttribfv = 0;
PFNGLGETVERTEXATTRIBIVPROC __teGetVertexAttribiv = 0;
PFNGLGETVERTEXATTRIBPOINTERVPROC __teGetVertexAttribPointerv = 0;
PFNGLISPROGRAMPROC __teIsProgram = 0;
PFNGLISSHADERPROC __teIsShader = 0;
PFNGLLINKPROGRAMPROC __teLinkProgram = 0;
PFNGLSHADERSOURCEPROC __teShaderSource = 0;
PFNGLUSEPROGRAMPROC __teUseProgram = 0;
PFNGLUNIFORM1FPROC __teUniform1f = 0;
PFNGLUNIFORM2FPROC __teUniform2f = 0;
PFNGLUNIFORM3FPROC __teUniform3f = 0;
PFNGLUNIFORM4FPROC __teUniform4f = 0;
PFNGLUNIFORM1IPROC __teUniform1i = 0;
PFNGLUNIFORM2IPROC __teUniform2i = 0;
PFNGLUNIFORM3IPROC __teUniform3i = 0;
PFNGLUNIFORM4IPROC __teUniform4i = 0;
PFNGLUNIFORM1FVPROC __teUniform1fv = 0;
PFNGLUNIFORM2FVPROC __teUniform2fv = 0;
PFNGLUNIFORM3FVPROC __teUniform3fv = 0;
PFNGLUNIFORM4FVPROC __teUniform4fv = 0;
PFNGLUNIFORM1IVPROC __teUniform1iv = 0;
PFNGLUNIFORM2IVPROC __teUniform2iv = 0;
PFNGLUNIFORM3IVPROC __teUniform3iv = 0;
PFNGLUNIFORM4IVPROC __teUniform4iv = 0;
PFNGLUNIFORMMATRIX2FVPROC __teUniformMatrix2fv = 0;
PFNGLUNIFORMMATRIX3FVPROC __teUniformMatrix3fv = 0;
PFNGLUNIFORMMATRIX4FVPROC __teUniformMatrix4fv = 0;
PFNGLVALIDATEPROGRAMPROC __teValidateProgram = 0;
PFNGLVERTEXATTRIB1DPROC __teVertexAttrib1d = 0;
PFNGLVERTEXATTRIB1DVPROC __teVertexAttrib1dv = 0;
PFNGLVERTEXATTRIB1FPROC __teVertexAttrib1f = 0;
PFNGLVERTEXATTRIB1FVPROC __teVertexAttrib1fv = 0;
PFNGLVERTEXATTRIB1SPROC __teVertexAttrib1s = 0;
PFNGLVERTEXATTRIB1SVPROC __teVertexAttrib1sv = 0;
PFNGLVERTEXATTRIB2DPROC __teVertexAttrib2d = 0;
PFNGLVERTEXATTRIB2DVPROC __teVertexAttrib2dv = 0;
PFNGLVERTEXATTRIB2FPROC __teVertexAttrib2f = 0;
PFNGLVERTEXATTRIB2FVPROC __teVertexAttrib2fv = 0;
PFNGLVERTEXATTRIB2SPROC __teVertexAttrib2s = 0;
PFNGLVERTEXATTRIB2SVPROC __teVertexAttrib2sv = 0;
PFNGLVERTEXATTRIB3DPROC __teVertexAttrib3d = 0;
PFNGLVERTEXATTRIB3DVPROC __teVertexAttrib3dv = 0;
PFNGLVERTEXATTRIB3FPROC __teVertexAttrib3f = 0;
PFNGLVERTEXATTRIB3FVPROC __teVertexAttrib3fv = 0;
PFNGLVERTEXATTRIB3SPROC __teVertexAttrib3s = 0;
PFNGLVERTEXATTRIB3SVPROC __teVertexAttrib3sv = 0;
PFNGLVERTEXATTRIB4NBVPROC __teVertexAttrib4Nbv = 0;
PFNGLVERTEXATTRIB4NIVPROC __teVertexAttrib4Niv = 0;
PFNGLVERTEXATTRIB4NSVPROC __teVertexAttrib4Nsv = 0;
PFNGLVERTEXATTRIB4NUBPROC __teVertexAttrib4Nub = 0;
PFNGLVERTEXATTRIB4NUBVPROC __teVertexAttrib4Nubv = 0;
PFNGLVERTEXATTRIB4NUIVPROC __teVertexAttrib4Nuiv = 0;
PFNGLVERTEXATTRIB4NUSVPROC __teVertexAttrib4Nusv = 0;
PFNGLVERTEXATTRIB4BVPROC __teVertexAttrib4bv = 0;
PFNGLVERTEXATTRIB4DPROC __teVertexAttrib4d = 0;
PFNGLVERTEXATTRIB4DVPROC __teVertexAttrib4dv = 0;
PFNGLVERTEXATTRIB4FPROC __teVertexAttrib4f = 0;
PFNGLVERTEXATTRIB4FVPROC __teVertexAttrib4fv = 0;
PFNGLVERTEXATTRIB4IVPROC __teVertexAttrib4iv = 0;
PFNGLVERTEXATTRIB4SPROC __teVertexAttrib4s = 0;
PFNGLVERTEXATTRIB4SVPROC __teVertexAttrib4sv = 0;
PFNGLVERTEXATTRIB4UBVPROC __teVertexAttrib4ubv = 0;
PFNGLVERTEXATTRIB4UIVPROC __teVertexAttrib4uiv = 0;
PFNGLVERTEXATTRIB4USVPROC __teVertexAttrib4usv = 0;
PFNGLVERTEXATTRIBPOINTERPROC __teVertexAttribPointer = 0;

//OpenGL 2.1 Extensions
PFNGLUNIFORMMATRIX2X3FVPROC __teUniformMatrix2x3fv = 0;
PFNGLUNIFORMMATRIX3X2FVPROC __teUniformMatrix3x2fv = 0;
PFNGLUNIFORMMATRIX2X4FVPROC __teUniformMatrix2x4fv = 0;
PFNGLUNIFORMMATRIX4X2FVPROC __teUniformMatrix4x2fv = 0;
PFNGLUNIFORMMATRIX3X4FVPROC __teUniformMatrix3x4fv = 0;
PFNGLUNIFORMMATRIX4X3FVPROC __teUniformMatrix4x3fv = 0;

PFNGLCOLORMASKIPROC __teColorMaski = 0;
PFNGLGETBOOLEANI_VPROC __teGetBooleani_v = 0;
PFNGLGETINTEGERI_VPROC __teGetIntegeri_v = 0;
PFNGLENABLEIPROC __teEnablei = 0;
PFNGLDISABLEIPROC __teDisablei = 0;
PFNGLISENABLEDIPROC __teIsEnabledi = 0;
PFNGLBEGINTRANSFORMFEEDBACKPROC __teBeginTransformFeedback = 0;
PFNGLENDTRANSFORMFEEDBACKPROC __teEndTransformFeedback = 0;
PFNGLBINDBUFFERRANGEPROC __teBindBufferRange = 0;
PFNGLBINDBUFFERBASEPROC __teBindBufferBase = 0;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC __teTransformFeedbackVaryings = 0;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC __teGetTransformFeedbackVarying = 0;
PFNGLCLAMPCOLORPROC __teClampColor = 0;
PFNGLBEGINCONDITIONALRENDERPROC __teBeginConditionalRender = 0;
PFNGLENDCONDITIONALRENDERPROC __teEndConditionalRender = 0;
PFNGLVERTEXATTRIBIPOINTERPROC __teVertexAttribIPointer = 0;
PFNGLGETVERTEXATTRIBIIVPROC __teGetVertexAttribIiv = 0;
PFNGLGETVERTEXATTRIBIUIVPROC __teGetVertexAttribIuiv = 0;
PFNGLVERTEXATTRIBI1IPROC __teVertexAttribI1i = 0;
PFNGLVERTEXATTRIBI2IPROC __teVertexAttribI2i = 0;
PFNGLVERTEXATTRIBI3IPROC __teVertexAttribI3i = 0;
PFNGLVERTEXATTRIBI4IPROC __teVertexAttribI4i = 0;
PFNGLVERTEXATTRIBI1UIPROC __teVertexAttribI1ui = 0;
PFNGLVERTEXATTRIBI2UIPROC __teVertexAttribI2ui = 0;
PFNGLVERTEXATTRIBI3UIPROC __teVertexAttribI3ui = 0;
PFNGLVERTEXATTRIBI4UIPROC __teVertexAttribI4ui = 0;
PFNGLVERTEXATTRIBI1IVPROC __teVertexAttribI1iv = 0;
PFNGLVERTEXATTRIBI2IVPROC __teVertexAttribI2iv = 0;
PFNGLVERTEXATTRIBI3IVPROC __teVertexAttribI3iv = 0;
PFNGLVERTEXATTRIBI4IVPROC __teVertexAttribI4iv = 0;
PFNGLVERTEXATTRIBI1UIVPROC __teVertexAttribI1uiv = 0;
PFNGLVERTEXATTRIBI2UIVPROC __teVertexAttribI2uiv = 0;
PFNGLVERTEXATTRIBI3UIVPROC __teVertexAttribI3uiv = 0;
PFNGLVERTEXATTRIBI4UIVPROC __teVertexAttribI4uiv = 0;
PFNGLVERTEXATTRIBI4BVPROC __teVertexAttribI4bv = 0;
PFNGLVERTEXATTRIBI4SVPROC __teVertexAttribI4sv = 0;
PFNGLVERTEXATTRIBI4UBVPROC __teVertexAttribI4ubv = 0;
PFNGLVERTEXATTRIBI4USVPROC __teVertexAttribI4usv = 0;
PFNGLGETUNIFORMUIVPROC __teGetUniformuiv = 0;
PFNGLBINDFRAGDATALOCATIONPROC __teBindFragDataLocation = 0;
PFNGLGETFRAGDATALOCATIONPROC __teGetFragDataLocation = 0;
PFNGLUNIFORM1UIPROC __teUniform1ui = 0;
PFNGLUNIFORM2UIPROC __teUniform2ui = 0;
PFNGLUNIFORM3UIPROC __teUniform3ui = 0;
PFNGLUNIFORM4UIPROC __teUniform4ui = 0;
PFNGLUNIFORM1UIVPROC __teUniform1uiv = 0;
PFNGLUNIFORM2UIVPROC __teUniform2uiv = 0;
PFNGLUNIFORM3UIVPROC __teUniform3uiv = 0;
PFNGLUNIFORM4UIVPROC __teUniform4uiv = 0;
PFNGLTEXPARAMETERIIVPROC __teTexParameterIiv = 0;
PFNGLTEXPARAMETERIUIVPROC __teTexParameterIuiv = 0;
PFNGLGETTEXPARAMETERIIVPROC __teGetTexParameterIiv = 0;
PFNGLGETTEXPARAMETERIUIVPROC __teGetTexParameterIuiv = 0;
PFNGLCLEARBUFFERIVPROC __teClearBufferiv = 0;
PFNGLCLEARBUFFERUIVPROC __teClearBufferuiv = 0;
PFNGLCLEARBUFFERFVPROC __teClearBufferfv = 0;
PFNGLCLEARBUFFERFIPROC __teClearBufferfi = 0;
PFNGLGETSTRINGIPROC __teGetStringi = 0;
PFNGLISRENDERBUFFERPROC __teIsRenderbuffer = 0;
PFNGLBINDRENDERBUFFERPROC __teBindRenderbuffer = 0;
PFNGLDELETERENDERBUFFERSPROC __teDeleteRenderbuffers = 0;
PFNGLGENRENDERBUFFERSPROC __teGenRenderbuffers = 0;
PFNGLRENDERBUFFERSTORAGEPROC __teRenderbufferStorage = 0;
PFNGLGETRENDERBUFFERPARAMETERIVPROC __teGetRenderbufferParameteriv = 0;
PFNGLISFRAMEBUFFERPROC __teIsFramebuffer = 0;
PFNGLBINDFRAMEBUFFERPROC __teBindFramebuffer = 0;
PFNGLDELETEFRAMEBUFFERSPROC __teDeleteFramebuffers = 0;
PFNGLGENFRAMEBUFFERSPROC __teGenFramebuffers = 0;
PFNGLCHECKFRAMEBUFFERSTATUSPROC __teCheckFramebufferStatus = 0;
PFNGLFRAMEBUFFERTEXTURE1DPROC __teFramebufferTexture1D = 0;
PFNGLFRAMEBUFFERTEXTURE2DPROC __teFramebufferTexture2D = 0;
PFNGLFRAMEBUFFERTEXTURE3DPROC __teFramebufferTexture3D = 0;
PFNGLFRAMEBUFFERRENDERBUFFERPROC __teFramebufferRenderbuffer = 0;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC __teGetFramebufferAttachmentParameteriv = 0;
PFNGLGENERATEMIPMAPPROC __teGenerateMipmap = 0;
PFNGLBLITFRAMEBUFFERPROC __teBlitFramebuffer = 0;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC __teRenderbufferStorageMultisample = 0;
PFNGLFRAMEBUFFERTEXTURELAYERPROC __teFramebufferTextureLayer = 0;
PFNGLMAPBUFFERRANGEPROC __teMapBufferRange = 0;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC __teFlushMappedBufferRange = 0;
PFNGLBINDVERTEXARRAYPROC __teBindVertexArray = 0;
PFNGLDELETEVERTEXARRAYSPROC __teDeleteVertexArrays = 0;
PFNGLGENVERTEXARRAYSPROC __teGenVertexArrays = 0;
PFNGLISVERTEXARRAYPROC __teIsVertexArray = 0;

//OpenGL 3.1 Extensions
PFNGLDRAWARRAYSINSTANCEDPROC __teDrawArraysInstanced = 0;
PFNGLDRAWELEMENTSINSTANCEDPROC __teDrawElementsInstanced = 0;
PFNGLTEXBUFFERPROC __teTexBuffer = 0;
PFNGLPRIMITIVERESTARTINDEXPROC __tePrimitiveRestartIndex = 0;
PFNGLCOPYBUFFERSUBDATAPROC __teCopyBufferSubdata = 0;
PFNGLGETUNIFORMINDICESPROC __teGetUniformIndices = 0;
PFNGLGETACTIVEUNIFORMSIVPROC __teGetActiveUniformsiv = 0;
PFNGLGETACTIVEUNIFORMNAMEPROC __teGetActiveUniformName = 0;
PFNGLGETUNIFORMBLOCKINDEXPROC __teGetUniformBlockIndex = 0;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC __teGetActiveUniformBlockiv = 0;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC __teGetActiveUniformBlockName = 0;
PFNGLUNIFORMBLOCKBINDINGPROC __teUniformBlockBinding = 0;

//OpenGL 3.2 Extensions
PFNGLDRAWELEMENTSBASEVERTEXPROC __teDrawElementsBaseVertex = 0;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC __teDrawRangeElementsBaseVertex = 0;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC __teDrawElementsInstancedBaseVertex = 0;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC __teMultiDrawElementsBaseVertex = 0;
PFNGLPROVOKINGVERTEXPROC __teProvokingVertex = 0;
PFNGLFENCESYNCPROC __teFenceSync = 0;
PFNGLISSYNCPROC __teIsSync = 0;
PFNGLDELETESYNCPROC __teDeleteSync = 0;
PFNGLCLIENTWAITSYNCPROC __teClientWaitSync = 0;
PFNGLWAITSYNCPROC __teWaitSync = 0;
PFNGLGETINTEGER64VPROC __teGetInteger64v = 0;
PFNGLGETSYNCIVPROC __teGetSynciv = 0;
PFNGLGETINTEGER64I_VPROC __teGetInteger64i_v = 0;
PFNGLGETBUFFERPARAMETERI64VPROC __teGetBufferParameteri64v = 0;
PFNGLFRAMEBUFFERTEXTUREPROC __teFramebufferTexture = 0;
PFNGLTEXIMAGE2DMULTISAMPLEPROC __teTexImage2DMultisample = 0;
PFNGLTEXIMAGE3DMULTISAMPLEPROC __teTexImage3DMultisample = 0;
PFNGLGETMULTISAMPLEFVPROC __teGetMultisamplefv = 0;
PFNGLSAMPLEMASKIPROC __teSampleMaski = 0;

//OpenGL 3.3 Extensions
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC __teBindFragDataLocationIndexed = 0;
PFNGLGETFRAGDATAINDEXPROC __teGetFragDataIndex = 0;
PFNGLGENSAMPLERSPROC __teGenSamplers = 0;
PFNGLDELETESAMPLERSPROC __teDeleteSamplers = 0;
PFNGLISSAMPLERPROC __teIsSampler = 0;
PFNGLBINDSAMPLERPROC __teBindSampler = 0;
PFNGLSAMPLERPARAMETERIPROC __teSamplerParameteri = 0;
PFNGLSAMPLERPARAMETERIVPROC __teSamplerParameteriv = 0;
PFNGLSAMPLERPARAMETERFPROC __teSamplerParameterf = 0;
PFNGLSAMPLERPARAMETERFVPROC __teSamplerParameterfv = 0;
PFNGLSAMPLERPARAMETERIIVPROC __teSamplerParameterIiv = 0;
PFNGLSAMPLERPARAMETERIUIVPROC __teSamplerParameterIuiv = 0;
PFNGLGETSAMPLERPARAMETERIVPROC __teGetSamplerParameteriv = 0;
PFNGLGETSAMPLERPARAMETERIIVPROC __teGetSamplerParameterIiv = 0;
PFNGLGETSAMPLERPARAMETERFVPROC __teGetSamplerParameterfv = 0;
PFNGLGETSAMPLERPARAMETERIUIVPROC __teGetSamplerParameterIuiv = 0;
PFNGLQUERYCOUNTERPROC __teQueryCounter = 0;
PFNGLGETQUERYOBJECTI64VPROC __teGetQueryObjecti64v = 0;
PFNGLGETQUERYOBJECTUI64VPROC __teGetQueryObjectui64v = 0;
PFNGLVERTEXATTRIBDIVISORPROC __teVertexAttribDivisor = 0;
PFNGLVERTEXATTRIBP1UIPROC __teVertexAttribP1ui = 0;
PFNGLVERTEXATTRIBP1UIVPROC __teVertexAttribP1uiv = 0;
PFNGLVERTEXATTRIBP2UIPROC __teVertexAttribP2ui = 0;
PFNGLVERTEXATTRIBP2UIVPROC __teVertexAttribP2uiv = 0;
PFNGLVERTEXATTRIBP3UIPROC __teVertexAttribP3ui = 0;
PFNGLVERTEXATTRIBP3UIVPROC __teVertexAttribP3uiv = 0;
PFNGLVERTEXATTRIBP4UIPROC __teVertexAttribP4ui = 0;
PFNGLVERTEXATTRIBP4UIVPROC __teVertexAttribP4uiv = 0;
PFNGLVERTEXP2UIPROC __teVertexP2ui = 0;
PFNGLVERTEXP2UIVPROC __teVertexP2uiv = 0;
PFNGLVERTEXP3UIPROC __teVertexP3ui = 0;
PFNGLVERTEXP3UIVPROC __teVertexP3uiv = 0;
PFNGLVERTEXP4UIPROC __teVertexP4ui = 0;
PFNGLVERTEXP4UIVPROC __teVertexP4uiv = 0;
PFNGLTEXCOORDP1UIPROC __teTexCoordP1ui = 0;
PFNGLTEXCOORDP1UIVPROC __teTexCoordP1uiv = 0;
PFNGLTEXCOORDP2UIPROC __teTexCoordP2ui = 0;
PFNGLTEXCOORDP2UIVPROC __teTexCoordP2uiv = 0;
PFNGLTEXCOORDP3UIPROC __teTexCoordP3ui = 0;
PFNGLTEXCOORDP3UIVPROC __teTexCoordP3uiv = 0;
PFNGLTEXCOORDP4UIPROC __teTexCoordP4ui = 0;
PFNGLTEXCOORDP4UIVPROC __teTexCoordP4uiv = 0;
PFNGLMULTITEXCOORDP1UIPROC __teMultiTexCoordP1ui = 0;
PFNGLMULTITEXCOORDP1UIVPROC __teMultiTexCoordP1uiv = 0;
PFNGLMULTITEXCOORDP2UIPROC __teMultiTexCoordP2ui = 0;
PFNGLMULTITEXCOORDP2UIVPROC __teMultiTexCoordP2uiv = 0;
PFNGLMULTITEXCOORDP3UIPROC __teMultiTexCoordP3ui = 0;
PFNGLMULTITEXCOORDP3UIVPROC __teMultiTexCoordP3uiv = 0;
PFNGLMULTITEXCOORDP4UIPROC __teMultiTexCoordP4ui = 0;
PFNGLMULTITEXCOORDP4UIVPROC __teMultiTexCoordP4uiv = 0;
PFNGLNORMALP3UIPROC __teNormalP3ui = 0;
PFNGLNORMALP3UIVPROC __teNormalP3uiv = 0;
PFNGLCOLORP3UIPROC __teColorP3ui = 0;
PFNGLCOLORP3UIVPROC __teColorP3uiv = 0;
PFNGLCOLORP4UIPROC __teColorP4ui = 0;
PFNGLCOLORP4UIVPROC __teColorP4uiv = 0;
PFNGLSECONDARYCOLORP3UIPROC __teSecondaryColorP3ui = 0;
PFNGLSECONDARYCOLORP3UIVPROC __teSecondaryColorP3uiv = 0;

//OpenGL 4.0 Extensions
PFNGLMINSAMPLESHADINGPROC __teMinSampleShading = 0;
PFNGLBLENDEQUATIONIPROC __teBlendEquationi = 0;
PFNGLBLENDEQUATIONSEPARATEIPROC __teBlendEquationSeparatei = 0;
PFNGLBLENDFUNCIPROC __teBlendFunci = 0;
PFNGLBLENDFUNCSEPARATEIPROC __teBlendFuncSeparatei = 0;
PFNGLDRAWARRAYSINDIRECTPROC __teDrawArraysIndirect = 0;
PFNGLDRAWELEMENTSINDIRECTPROC __teDrawElementsIndirect = 0;
PFNGLUNIFORM1DPROC __teUniform1d = 0;
PFNGLUNIFORM2DPROC __teUniform2d = 0;
PFNGLUNIFORM3DPROC __teUniform3d = 0;
PFNGLUNIFORM4DPROC __teUniform4d = 0;
PFNGLUNIFORM1DVPROC __teUniform1dv = 0;
PFNGLUNIFORM2DVPROC __teUniform2dv = 0;
PFNGLUNIFORM3DVPROC __teUniform3dv = 0;
PFNGLUNIFORM4DVPROC __teUniform4dv = 0;
PFNGLUNIFORMMATRIX2DVPROC __teUniformMatrix2dv = 0;
PFNGLUNIFORMMATRIX3DVPROC __teUniformMatrix3dv = 0;
PFNGLUNIFORMMATRIX4DVPROC __teUniformMatrix4dv = 0;
PFNGLUNIFORMMATRIX2X3DVPROC __teUniformMatrix2x3dv = 0;
PFNGLUNIFORMMATRIX2X4DVPROC __teUniformMatrix2x4dv = 0;
PFNGLUNIFORMMATRIX3X2DVPROC __teUniformMatrix3x2dv = 0;
PFNGLUNIFORMMATRIX3X4DVPROC __teUniformMatrix3x4dv = 0;
PFNGLUNIFORMMATRIX4X2DVPROC __teUniformMatrix4x2dv = 0;
PFNGLUNIFORMMATRIX4X3DVPROC __teUniformMatrix4x3dv = 0;
PFNGLGETUNIFORMDVPROC __teGetUniformdv = 0;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC __teGetSubroutineUniformLocation = 0;
PFNGLGETSUBROUTINEINDEXPROC __teGetSubroutineIndex = 0;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC __teGetActiveSubroutineUniformiv = 0;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC __teGetActiveSubroutineUniformName = 0;
PFNGLGETACTIVESUBROUTINENAMEPROC __teGetActiveSubroutineName = 0;
PFNGLUNIFORMSUBROUTINESUIVPROC __teUniformSubroutinesuiv = 0;
PFNGLGETUNIFORMSUBROUTINEUIVPROC __teGetUniformSubroutineuiv = 0;
PFNGLGETPROGRAMSTAGEIVPROC __teGetProgramStageiv = 0;
PFNGLPATCHPARAMETERIPROC __tePatchParameteri = 0;
PFNGLPATCHPARAMETERFVPROC __tePatchParameterfv = 0;
PFNGLBINDTRANSFORMFEEDBACKPROC __teBindTransformFeedback = 0;
PFNGLDELETETRANSFORMFEEDBACKSPROC __teDeleteTransformFeedbacks = 0;
PFNGLGENTRANSFORMFEEDBACKSPROC __teGenTransformFeedbacks = 0;
PFNGLISTRANSFORMFEEDBACKPROC __teIsTransformFeedback = 0;
PFNGLPAUSETRANSFORMFEEDBACKPROC __tePauseTransformFeedback = 0;
PFNGLRESUMETRANSFORMFEEDBACKPROC __teResumeTransformFeedback = 0;
PFNGLDRAWTRANSFORMFEEDBACKPROC __teDrawTransformFeedback = 0;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC __teDrawTransformFeedbackStream = 0;
PFNGLBEGINQUERYINDEXEDPROC __teBeginQueryIndexed = 0;
PFNGLENDQUERYINDEXEDPROC __teEndQueryIndexed = 0;
PFNGLGETQUERYINDEXEDIVPROC __teGetQueryIndexediv = 0;

//OpenGL 4.1 Extensions
PFNGLRELEASESHADERCOMPILERPROC __teReleaseShaderCompiler = 0;
PFNGLSHADERBINARYPROC __teShaderBinary = 0;
PFNGLGETSHADERPRECISIONFORMATPROC __teGetShaderPrecisionFormat = 0;
PFNGLDEPTHRANGEFPROC __teDepthRangef = 0;
PFNGLCLEARDEPTHFPROC __teClearDepthf = 0;
PFNGLGETPROGRAMBINARYPROC __teGetProgramBinary = 0;
PFNGLPROGRAMBINARYPROC __teProgramBinary = 0;
PFNGLPROGRAMPARAMETERIPROC __teProgramParameteri = 0;
PFNGLUSEPROGRAMSTAGESPROC __teUseProgramStages = 0;
PFNGLACTIVESHADERPROGRAMPROC __teActiveShaderProgram = 0;
PFNGLCREATESHADERPROGRAMVPROC __teCreateShaderProgramv = 0;
PFNGLBINDPROGRAMPIPELINEPROC __teBindProgramPipeline = 0;
PFNGLDELETEPROGRAMPIPELINESPROC __teDeleteProgramPipelines = 0;
PFNGLGENPROGRAMPIPELINESPROC __teGenProgramPipelines = 0;
PFNGLISPROGRAMPIPELINEPROC __teIsProgramPipeline = 0;
PFNGLGETPROGRAMPIPELINEIVPROC __teGetProgramPipelineiv = 0;
PFNGLPROGRAMUNIFORM1IPROC __teProgramUniform1i = 0;
PFNGLPROGRAMUNIFORM1IVPROC __teProgramUniform1iv = 0;
PFNGLPROGRAMUNIFORM1FPROC __teProgramUniform1f = 0;
PFNGLPROGRAMUNIFORM1FVPROC __teProgramUniform1fv = 0;
PFNGLPROGRAMUNIFORM1DPROC __teProgramUniform1d = 0;
PFNGLPROGRAMUNIFORM1DVPROC __teProgramUniform1dv = 0;
PFNGLPROGRAMUNIFORM1UIPROC __teProgramUniform1ui = 0;
PFNGLPROGRAMUNIFORM1UIVPROC __teProgramUniform1uiv = 0;
PFNGLPROGRAMUNIFORM2IPROC __teProgramUniform2i = 0;
PFNGLPROGRAMUNIFORM2IVPROC __teProgramUniform2iv = 0;
PFNGLPROGRAMUNIFORM2FPROC __teProgramUniform2f = 0;
PFNGLPROGRAMUNIFORM2FVPROC __teProgramUniform2fv = 0;
PFNGLPROGRAMUNIFORM2DPROC __teProgramUniform2d = 0;
PFNGLPROGRAMUNIFORM2DVPROC __teProgramUniform2dv = 0;
PFNGLPROGRAMUNIFORM2UIPROC __teProgramUniform2ui = 0;
PFNGLPROGRAMUNIFORM2UIVPROC __teProgramUniform2uiv = 0;
PFNGLPROGRAMUNIFORM3IPROC __teProgramUniform3i = 0;
PFNGLPROGRAMUNIFORM3IVPROC __teProgramUniform3iv = 0;
PFNGLPROGRAMUNIFORM3FPROC __teProgramUniform3f = 0;
PFNGLPROGRAMUNIFORM3FVPROC __teProgramUniform3fv = 0;
PFNGLPROGRAMUNIFORM3DPROC __teProgramUniform3d = 0;
PFNGLPROGRAMUNIFORM3DVPROC __teProgramUniform3dv = 0;
PFNGLPROGRAMUNIFORM3UIPROC __teProgramUniform3ui = 0;
PFNGLPROGRAMUNIFORM3UIVPROC __teProgramUniform3uiv = 0;
PFNGLPROGRAMUNIFORM4IPROC __teProgramUniform4i = 0;
PFNGLPROGRAMUNIFORM4IVPROC __teProgramUniform4iv = 0;
PFNGLPROGRAMUNIFORM4FPROC __teProgramUniform4f = 0;
PFNGLPROGRAMUNIFORM4FVPROC __teProgramUniform4fv = 0;
PFNGLPROGRAMUNIFORM4DPROC __teProgramUniform4d = 0;
PFNGLPROGRAMUNIFORM4DVPROC __teProgramUniform4dv = 0;
PFNGLPROGRAMUNIFORM4UIPROC __teProgramUniform4ui = 0;
PFNGLPROGRAMUNIFORM4UIVPROC __teProgramUniform4uiv = 0;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC __teProgramUniformMatrix2fv = 0;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC __teProgramUniformMatrix3fv = 0;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC __teProgramUniformMatrix4fv = 0;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC __teProgramUniformMatrix2dv = 0;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC __teProgramUniformMatrix3dv = 0;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC __teProgramUniformMatrix4dv = 0;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC __teProgramUniformMatrix2x3fv = 0;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC __teProgramUniformMatrix3x2fv = 0;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC __teProgramUniformMatrix2x4fv = 0;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC __teProgramUniformMatrix4x2fv = 0;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC __teProgramUniformMatrix3x4fv = 0;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC __teProgramUniformMatrix4x3fv = 0;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC __teProgramUniformMatrix2x3dv = 0;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC __teProgramUniformMatrix3x2dv = 0;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC __teProgramUniformMatrix2x4dv = 0;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC __teProgramUniformMatrix4x2dv = 0;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC __teProgramUniformMatrix3x4dv = 0;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC __teProgramUniformMatrix4x3dv = 0;
PFNGLVALIDATEPROGRAMPIPELINEPROC __teValidateProgramPipeline = 0;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC __teGetProgramPipelineInfoLog = 0;
PFNGLVERTEXATTRIBL1DPROC __teVertexAttribL1d = 0;
PFNGLVERTEXATTRIBL2DPROC __teVertexAttribL2d = 0;
PFNGLVERTEXATTRIBL3DPROC __teVertexAttribL3d = 0;
PFNGLVERTEXATTRIBL4DPROC __teVertexAttribL4d = 0;
PFNGLVERTEXATTRIBL1DVPROC __teVertexAttribL1dv = 0;
PFNGLVERTEXATTRIBL2DVPROC __teVertexAttribL2dv = 0;
PFNGLVERTEXATTRIBL3DVPROC __teVertexAttribL3dv = 0;
PFNGLVERTEXATTRIBL4DVPROC __teVertexAttribL4dv = 0;
PFNGLVERTEXATTRIBLPOINTERPROC __teVertexAttribLPointer = 0;
PFNGLGETVERTEXATTRIBLDVPROC __teGetVertexAttribLdv = 0;
PFNGLVIEWPORTARRAYVPROC __teViewportArrayv = 0;
PFNGLVIEWPORTINDEXEDFPROC __teViewportIndexedf = 0;
PFNGLVIEWPORTINDEXEDFVPROC __teViewportIndexedfv = 0;
PFNGLSCISSORARRAYVPROC __teScissorArrayv = 0;
PFNGLSCISSORINDEXEDPROC __teScissorIndexed = 0;
PFNGLSCISSORINDEXEDVPROC __teScissorIndexedv = 0;
PFNGLDEPTHRANGEARRAYVPROC __teDepthRangeArrayv = 0;
PFNGLDEPTHRANGEINDEXEDPROC __teDepthRangeIndexed = 0;
PFNGLGETFLOATI_VPROC __teGetFloati_v = 0;
PFNGLGETDOUBLEI_VPROC __teGetDoublei_v = 0;

//OpenGL 4.2 Extensions
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC __teDrawArraysInstancedBaseInstance = 0;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC __teDrawElementsInstancedBaseInstance = 0;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC __teDrawElementsInstancedBaseVertexBaseInstance = 0;
PFNGLGETINTERNALFORMATIVPROC __teGetInternalformativ = 0;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC __teGetActiveAtomicCounterBufferiv = 0;
PFNGLBINDIMAGETEXTUREPROC __teBindImageTexture = 0;
PFNGLMEMORYBARRIERPROC __teMemoryBarrier = 0;
PFNGLTEXSTORAGE1DPROC __teTexStorage1D = 0;
PFNGLTEXSTORAGE2DPROC __teTexStorage2D = 0;
PFNGLTEXSTORAGE3DPROC __teTexStorage3D = 0;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC __teDrawTransformFeedbackInstanced = 0;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC __teDrawTransformFeedbackStreamInstanced = 0;

//OpenGL 4.3 Extensions
PFNGLCLEARBUFFERDATAPROC __teClearBufferData = 0;
PFNGLCLEARBUFFERSUBDATAPROC __teClearBufferSubdata = 0;
PFNGLDISPATCHCOMPUTEPROC __teDispatchCompute = 0;
PFNGLDISPATCHCOMPUTEINDIRECTPROC __teDispatchComputeIndirect = 0;
PFNGLCOPYIMAGESUBDATAPROC  __teCopyImageSubdata = 0;
PFNGLFRAMEBUFFERPARAMETERIPROC __teFramebufferParameteri = 0;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC __teGetFramebufferParameteriv = 0;
PFNGLGETINTERNALFORMATI64VPROC __teGetInternalformati64v = 0;
PFNGLINVALIDATETEXSUBIMAGEPROC __teInvalidateTexSubImage = 0;
PFNGLINVALIDATETEXIMAGEPROC __teInvalidateTexImage = 0;
PFNGLINVALIDATEBUFFERSUBDATAPROC __teInvalidateBufferSubdata = 0;
PFNGLINVALIDATEBUFFERDATAPROC __teInvalidateBufferData = 0;
PFNGLINVALIDATEFRAMEBUFFERPROC __teInvalidateFramebuffer = 0;
PFNGLINVALIDATESUBFRAMEBUFFERPROC __teInvalidateSubFramebuffer = 0;
PFNGLMULTIDRAWARRAYSINDIRECTPROC __teMultiDrawArraysIndirect = 0;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC __teMultiDrawElementsIndirect = 0;
PFNGLGETPROGRAMINTERFACEIVPROC __teGetProgramInterfaceiv = 0;
PFNGLGETPROGRAMRESOURCEINDEXPROC __teGetProgramResourceIndex = 0;
PFNGLGETPROGRAMRESOURCENAMEPROC __teGetProgramResourceName = 0;
PFNGLGETPROGRAMRESOURCEIVPROC __teGetProgramResourceiv = 0;
PFNGLGETPROGRAMRESOURCELOCATIONPROC __teGetProgramResourceLocation = 0;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC __teGetProgramResourceLocationIndex = 0;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC __teShaderStorageBlockBinding = 0;
PFNGLTEXBUFFERRANGEPROC __teTexBufferRange = 0;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC __teTexStorage2DMultisample = 0;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC __teTexStorage3DMultisample = 0;
PFNGLTEXTUREVIEWPROC __teTextureView = 0;
PFNGLBINDVERTEXBUFFERPROC __teBindVertexBuffer = 0;
PFNGLVERTEXATTRIBFORMATPROC __teVertexAttribFormat = 0;
PFNGLVERTEXATTRIBIFORMATPROC __teVertexAttribIFormat = 0;
PFNGLVERTEXATTRIBLFORMATPROC __teVertexAttribLFormat = 0;
PFNGLVERTEXATTRIBBINDINGPROC __teVertexAttribBinding = 0;
PFNGLVERTEXBINDINGDIVISORPROC __teVertexBindingDivisor = 0;
PFNGLDEBUGMESSAGECONTROLPROC __teDebugMessageControl = 0;
PFNGLDEBUGMESSAGEINSERTPROC __teDebugMessageInsert = 0;
PFNGLDEBUGMESSAGECALLBACKPROC __teDebugMessageCallback = 0;
PFNGLGETDEBUGMESSAGELOGPROC __teGetDebugMessageLog = 0;
PFNGLPUSHDEBUGGROUPPROC __tePushDebugGroup = 0;
PFNGLPOPDEBUGGROUPPROC __tePopDebugGroup = 0;
PFNGLOBJECTLABELPROC __teObjectLabel = 0;
PFNGLGETOBJECTLABELPROC __teGetObjectLabel = 0;
PFNGLOBJECTPTRLABELPROC __teObjectPtrLabel = 0;
PFNGLGETOBJECTPTRLABELPROC __teGetObjectPtrLabel = 0;

//OpenGL 4.4 Extensions
PFNGLBUFFERSTORAGEPROC __teBufferStorage = 0;
PFNGLCLEARTEXIMAGEPROC __teClearTexImage = 0;
PFNGLCLEARTEXSUBIMAGEPROC __teClearTexSubImage = 0;
PFNGLBINDBUFFERSBASEPROC __teBindBuffersBase = 0;
PFNGLBINDBUFFERSRANGEPROC __teBindBuffersRange = 0;
PFNGLBINDTEXTURESPROC __teBindTextures = 0;
PFNGLBINDSAMPLERSPROC __teBindSamplers = 0;
PFNGLBINDIMAGETEXTURESPROC __teBindImageTextures = 0;
PFNGLBINDVERTEXBUFFERSPROC __teBindVertexBuffers = 0;

GLuint TinyExtender::GLVersion_Major = 0;
GLuint TinyExtender::GLVersion_Minor = 0;
//#endif

#endif