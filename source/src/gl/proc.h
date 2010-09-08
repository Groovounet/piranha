//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 01-06-2004
//! \file ./gl/proc.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_GL_PROC_H__
#define __PIRANHA_GL_PROC_H__

#include "../util/common.h"

namespace gl {

void Init ();
bool Check ();

extern bool ARB_fragment_program;
extern bool ARB_fragment_shader;
extern bool ARB_multitexture;
extern bool ARB_point_parameters;
extern bool ARB_point_sprite;
extern bool ARB_shader_objects;
extern bool ARB_texture_compression;
extern bool ARB_texture_env_add;
extern bool ARB_texture_env_combine;
extern bool ARB_texture_rectangle;
extern bool ARB_vertex_buffer_object;
extern bool ARB_vertex_program;
extern bool ARB_vertex_shader;
extern bool NV_point_sprite;
extern bool NV_texture_rectangle;
extern bool SGIS_generate_mipmap;

}; // gl
/*
// GL_ARB_fragment_program

// GL_ARB_fragment_shader

// GL_ARB_multitexture
extern PFNGLACTIVETEXTUREARBPROC                       glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC                 glClientActiveTextureARB;
extern PFNGLMULTITEXCOORD2FARBPROC                     glMultiTexCoord2fARB;
extern PFNGLMULTITEXCOORD2FVARBPROC                    glMultiTexCoord2fvARB;

// GL_ARB_point_parameters
extern PFNGLPOINTPARAMETERFARBPROC                     glPointParameterfARB;
extern PFNGLPOINTPARAMETERFVARBPROC                    glPointParameterfvARB;

// GL_ARB_shader_objects
extern PFNGLDELETEOBJECTARBPROC            glDeleteObjectARB;
extern PFNGLGETHANDLEARBPROC               glGetHandleARB;
extern PFNGLDETACHOBJECTARBPROC            glDetachObjectARB;
extern PFNGLCREATESHADEROBJECTARBPROC      glCreateShaderObjectARB;
extern PFNGLSHADERSOURCEARBPROC            glShaderSourceARB;
extern PFNGLCOMPILESHADERARBPROC           glCompileShaderARB;
extern PFNGLCREATEPROGRAMOBJECTARBPROC     glCreateProgramObjectARB;
extern PFNGLATTACHOBJECTARBPROC            glAttachObjectARB;
extern PFNGLLINKPROGRAMARBPROC             glLinkProgramARB;
extern PFNGLUSEPROGRAMOBJECTARBPROC        glUseProgramObjectARB;
extern PFNGLVALIDATEPROGRAMARBPROC         glValidateProgramARB;
extern PFNGLUNIFORM1FARBPROC               glUniform1fARB;
extern PFNGLUNIFORM2FARBPROC               glUniform2fARB;
extern PFNGLUNIFORM3FARBPROC               glUniform3fARB;
extern PFNGLUNIFORM4FARBPROC               glUniform4fARB;
extern PFNGLUNIFORM1IARBPROC               glUniform1iARB;
extern PFNGLUNIFORM2IARBPROC               glUniform2iARB;
extern PFNGLUNIFORM3IARBPROC               glUniform3iARB;
extern PFNGLUNIFORM4IARBPROC               glUniform4iARB;
extern PFNGLUNIFORM1FVARBPROC              glUniform1fvARB;
extern PFNGLUNIFORM2FVARBPROC              glUniform2fvARB;
extern PFNGLUNIFORM3FVARBPROC              glUniform3fvARB;
extern PFNGLUNIFORM4FVARBPROC              glUniform4fvARB;
extern PFNGLUNIFORM1IVARBPROC              glUniform1ivARB;
extern PFNGLUNIFORM2IVARBPROC              glUniform2ivARB;
extern PFNGLUNIFORM3IVARBPROC              glUniform3ivARB;
extern PFNGLUNIFORM4IVARBPROC              glUniform4ivARB;
extern PFNGLUNIFORMMATRIX2FVARBPROC        glUniformMatrix2fvARB;
extern PFNGLUNIFORMMATRIX3FVARBPROC        glUniformMatrix3fvARB;
extern PFNGLUNIFORMMATRIX4FVARBPROC        glUniformMatrix4fvARB;
extern PFNGLGETOBJECTPARAMETERFVARBPROC    glGetObjectParameterfvARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC    glGetObjectParameterivARB;
extern PFNGLGETINFOLOGARBPROC              glGetInfoLogARB;
extern PFNGLGETATTACHEDOBJECTSARBPROC      glGetAttachedObjectsARB;
extern PFNGLGETUNIFORMLOCATIONARBPROC      glGetUniformLocationARB;
extern PFNGLGETACTIVEUNIFORMARBPROC        glGetActiveUniformARB;
extern PFNGLGETUNIFORMFVARBPROC            glGetUniformfvARB;
extern PFNGLGETUNIFORMIVARBPROC            glGetUniformivARB;
extern PFNGLGETSHADERSOURCEARBPROC         glGetShaderSourceARB;

// GL_ARB_texture_compression
extern PFNGLCOMPRESSEDTEXIMAGE3DARBPROC                glCompressedTexImage3DARB;
extern PFNGLCOMPRESSEDTEXIMAGE2DARBPROC                glCompressedTexImage2DARB;
extern PFNGLCOMPRESSEDTEXIMAGE1DARBPROC                glCompressedTexImage1DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC             glCompressedTexSubImage3DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC             glCompressedTexSubImage2DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC             glCompressedTexSubImage1DARB;
extern PFNGLGETCOMPRESSEDTEXIMAGEARBPROC               glGetCompressedTexImageARB;

// GL_ARB_texture_end_add

// GL_ARB_texture_env_combine

// GL_ARB_texture_rectangle

// GL_ARB_vertex_buffer_object
extern PFNGLBINDBUFFERARBPROC                          glBindBufferARB;
extern PFNGLDELETEBUFFERSARBPROC                       glDeleteBuffersARB;
extern PFNGLGENBUFFERSARBPROC                          glGenBuffersARB;
extern PFNGLISBUFFERARBPROC                            glIsBufferARB;
extern PFNGLBUFFERDATAARBPROC                          glBufferDataARB;
extern PFNGLBUFFERSUBDATAARBPROC                       glBufferSubDataARB;
extern PFNGLGETBUFFERSUBDATAARBPROC                    glGetBufferSubDataARB;
extern PFNGLMAPBUFFERARBPROC                           glMapBufferARB;
extern PFNGLUNMAPBUFFERARBPROC                         glUnmapBufferARB;
extern PFNGLGETBUFFERPARAMETERIVARBPROC                glGetBufferParameterivARB;
extern PFNGLGETBUFFERPOINTERVARBPROC                   glGetBufferPointervARB;

// GL_ARB_vertex_program
extern PFNGLVERTEXATTRIB1DARBPROC                      glVertexAttrib1dARB;
extern PFNGLVERTEXATTRIB1DVARBPROC                     glVertexAttrib1dvARB;
extern PFNGLVERTEXATTRIB1FARBPROC                      glVertexAttrib1fARB;
extern PFNGLVERTEXATTRIB1FVARBPROC                     glVertexAttrib1fvARB;
extern PFNGLVERTEXATTRIB1SARBPROC                      glVertexAttrib1sARB;
extern PFNGLVERTEXATTRIB1SVARBPROC                     glVertexAttrib1svARB;
extern PFNGLVERTEXATTRIB2DARBPROC                      glVertexAttrib2dARB;
extern PFNGLVERTEXATTRIB2DVARBPROC                     glVertexAttrib2dvARB;
extern PFNGLVERTEXATTRIB2FARBPROC                      glVertexAttrib2fARB;
extern PFNGLVERTEXATTRIB2FVARBPROC                     glVertexAttrib2fvARB;
extern PFNGLVERTEXATTRIB2SARBPROC                      glVertexAttrib2sARB;
extern PFNGLVERTEXATTRIB2SVARBPROC                     glVertexAttrib2svARB;
extern PFNGLVERTEXATTRIB3DARBPROC                      glVertexAttrib3dARB;
extern PFNGLVERTEXATTRIB3DVARBPROC                     glVertexAttrib3dvARB;
extern PFNGLVERTEXATTRIB3FARBPROC                      glVertexAttrib3fARB;
extern PFNGLVERTEXATTRIB3FVARBPROC                     glVertexAttrib3fvARB;
extern PFNGLVERTEXATTRIB3SARBPROC                      glVertexAttrib3sARB;
extern PFNGLVERTEXATTRIB3SVARBPROC                     glVertexAttrib3svARB;
extern PFNGLVERTEXATTRIB4NBVARBPROC                    glVertexAttrib4NbvARB;
extern PFNGLVERTEXATTRIB4NIVARBPROC                    glVertexAttrib4NivARB;
extern PFNGLVERTEXATTRIB4NSVARBPROC                    glVertexAttrib4NsvARB;
extern PFNGLVERTEXATTRIB4NUBARBPROC                    glVertexAttrib4NubARB;
extern PFNGLVERTEXATTRIB4NUBVARBPROC                   glVertexAttrib4NubvARB;
extern PFNGLVERTEXATTRIB4NUIVARBPROC                   glVertexAttrib4NuivARB;
extern PFNGLVERTEXATTRIB4NUSVARBPROC                   glVertexAttrib4NusvARB;
extern PFNGLVERTEXATTRIB4BVARBPROC                     glVertexAttrib4bvARB;
extern PFNGLVERTEXATTRIB4DARBPROC                      glVertexAttrib4dARB;
extern PFNGLVERTEXATTRIB4DVARBPROC                     glVertexAttrib4dvARB;
extern PFNGLVERTEXATTRIB4FARBPROC                      glVertexAttrib4fARB;
extern PFNGLVERTEXATTRIB4FVARBPROC                     glVertexAttrib4fvARB;
extern PFNGLVERTEXATTRIB4IVARBPROC                     glVertexAttrib4ivARB;
extern PFNGLVERTEXATTRIB4SARBPROC                      glVertexAttrib4sARB;
extern PFNGLVERTEXATTRIB4SVARBPROC                     glVertexAttrib4svARB;
extern PFNGLVERTEXATTRIB4UBVARBPROC                    glVertexAttrib4ubvARB;
extern PFNGLVERTEXATTRIB4UIVARBPROC                    glVertexAttrib4uivARB;
extern PFNGLVERTEXATTRIB4USVARBPROC                    glVertexAttrib4usvARB;
extern PFNGLVERTEXATTRIBPOINTERARBPROC                 glVertexAttribPointerARB;
extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC             glEnableVertexAttribArrayARB;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC            glDisableVertexAttribArrayARB;
extern PFNGLPROGRAMSTRINGARBPROC                       glProgramStringARB;
extern PFNGLBINDPROGRAMARBPROC                         glBindProgramARB;
extern PFNGLDELETEPROGRAMSARBPROC                      glDeleteProgramsARB;
extern PFNGLGENPROGRAMSARBPROC                         glGenProgramsARB;
extern PFNGLPROGRAMENVPARAMETER4DARBPROC               glProgramEnvParameter4dARB;
extern PFNGLPROGRAMENVPARAMETER4DVARBPROC              glProgramEnvParameter4dvARB;
extern PFNGLPROGRAMENVPARAMETER4FARBPROC               glProgramEnvParameter4fARB;
extern PFNGLPROGRAMENVPARAMETER4FVARBPROC              glProgramEnvParameter4fvARB;
extern PFNGLPROGRAMLOCALPARAMETER4DARBPROC             glProgramLocalParameter4dARB;
extern PFNGLPROGRAMLOCALPARAMETER4DVARBPROC            glProgramLocalParameter4dvARB;
extern PFNGLPROGRAMLOCALPARAMETER4FARBPROC             glProgramLocalParameter4fARB;
extern PFNGLPROGRAMLOCALPARAMETER4FVARBPROC            glProgramLocalParameter4fvARB;
extern PFNGLGETPROGRAMENVPARAMETERDVARBPROC            glGetProgramEnvParameterdvARB;
extern PFNGLGETPROGRAMENVPARAMETERFVARBPROC            glGetProgramEnvParameterfvARB;
extern PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC          glGetProgramLocalParameterdvARB;
extern PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC          glGetProgramLocalParameterfvARB;
extern PFNGLGETPROGRAMIVARBPROC                        glGetProgramivARB;
extern PFNGLGETPROGRAMSTRINGARBPROC                    glGetProgramStringARB;
extern PFNGLGETVERTEXATTRIBDVARBPROC                   glGetVertexAttribdvARB;
extern PFNGLGETVERTEXATTRIBFVARBPROC                   glGetVertexAttribfvARB;
extern PFNGLGETVERTEXATTRIBIVARBPROC                   glGetVertexAttribivARB;
extern PFNGLGETVERTEXATTRIBPOINTERVARBPROC             glGetVertexAttribPointervARB;
extern PFNGLISPROGRAMARBPROC                           glIsProgramARB;

// GL_ARB_vertex_shader
extern PFNGLBINDATTRIBLOCATIONARBPROC                  glBindAttribLocationARB;
extern PFNGLGETACTIVEATTRIBARBPROC                     glGetActiveAttribARB;
extern PFNGLGETATTRIBLOCATIONARBPROC                   glGetAttribLocationARB;

// GL_NV_texture_rectangle

// GL_SGIS_generate_mipmap
*/
#endif //__PIRANHA_GL_PROC_H__
