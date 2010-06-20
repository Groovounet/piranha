//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 01-06-2004
//! \file ./gl/proc.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./proc.h"

bool gl::ARB_fragment_program = false;
bool gl::ARB_fragment_shader = false;
bool gl::ARB_multitexture = false;
bool gl::ARB_point_parameters = false;
bool gl::ARB_point_sprite = false;
bool gl::ARB_shader_objects = false;
bool gl::ARB_texture_compression = false;
bool gl::ARB_texture_env_add = false;
bool gl::ARB_texture_env_combine = false;
bool gl::ARB_texture_rectangle = false;
bool gl::ARB_vertex_buffer_object = false;
bool gl::ARB_vertex_program = false;
bool gl::ARB_vertex_shader = false;
bool gl::SGIS_generate_mipmap = false;
bool gl::NV_point_sprite = false;
bool gl::NV_texture_rectangle = false;

// GL_ARB_fragment_program

// GL_ARB_fragment_shader

// GL_ARB_multitexture
PFNGLACTIVETEXTUREARBPROC                       glActiveTextureARB = 0;
PFNGLCLIENTACTIVETEXTUREARBPROC                 glClientActiveTextureARB = 0;
PFNGLMULTITEXCOORD2FARBPROC                     glMultiTexCoord2fARB = 0;
PFNGLMULTITEXCOORD2FVARBPROC                    glMultiTexCoord2fvARB = 0;

// GL_ARB_point_parameters
PFNGLPOINTPARAMETERFARBPROC                     glPointParameterfARB  = 0;
PFNGLPOINTPARAMETERFVARBPROC                    glPointParameterfvARB = 0;

// GL_ARB_point_sprite

// GL_ARB_shader_objects
PFNGLDELETEOBJECTARBPROC                        glDeleteObjectARB = 0;
PFNGLGETHANDLEARBPROC                           glGetHandleARB = 0;
PFNGLDETACHOBJECTARBPROC                        glDetachObjectARB = 0;
PFNGLCREATESHADEROBJECTARBPROC                  glCreateShaderObjectARB = 0;
PFNGLSHADERSOURCEARBPROC                        glShaderSourceARB = 0;
PFNGLCOMPILESHADERARBPROC                       glCompileShaderARB = 0;
PFNGLCREATEPROGRAMOBJECTARBPROC                 glCreateProgramObjectARB = 0;
PFNGLATTACHOBJECTARBPROC                        glAttachObjectARB = 0;
PFNGLLINKPROGRAMARBPROC                         glLinkProgramARB = 0;
PFNGLUSEPROGRAMOBJECTARBPROC                    glUseProgramObjectARB = 0;
PFNGLVALIDATEPROGRAMARBPROC                     glValidateProgramARB = 0;
PFNGLUNIFORM1FARBPROC                           glUniform1fARB = 0;
PFNGLUNIFORM2FARBPROC                           glUniform2fARB = 0;
PFNGLUNIFORM3FARBPROC                           glUniform3fARB = 0;
PFNGLUNIFORM4FARBPROC                           glUniform4fARB = 0;
PFNGLUNIFORM1IARBPROC                           glUniform1iARB = 0;
PFNGLUNIFORM2IARBPROC                           glUniform2iARB = 0;
PFNGLUNIFORM3IARBPROC                           glUniform3iARB = 0;
PFNGLUNIFORM4IARBPROC                           glUniform4iARB = 0;
PFNGLUNIFORM1FVARBPROC                          glUniform1fvARB = 0;
PFNGLUNIFORM2FVARBPROC                          glUniform2fvARB = 0;
PFNGLUNIFORM3FVARBPROC                          glUniform3fvARB = 0;
PFNGLUNIFORM4FVARBPROC                          glUniform4fvARB = 0;
PFNGLUNIFORM1IVARBPROC                          glUniform1ivARB = 0;
PFNGLUNIFORM2IVARBPROC                          glUniform2ivARB = 0;
PFNGLUNIFORM3IVARBPROC                          glUniform3ivARB = 0;
PFNGLUNIFORM4IVARBPROC                          glUniform4ivARB = 0;
PFNGLUNIFORMMATRIX2FVARBPROC                    glUniformMatrix2fvARB = 0;
PFNGLUNIFORMMATRIX3FVARBPROC                    glUniformMatrix3fvARB = 0;
PFNGLUNIFORMMATRIX4FVARBPROC                    glUniformMatrix4fvARB = 0;
PFNGLGETOBJECTPARAMETERFVARBPROC                glGetObjectParameterfvARB = 0;
PFNGLGETOBJECTPARAMETERIVARBPROC                glGetObjectParameterivARB = 0;
PFNGLGETINFOLOGARBPROC                          glGetInfoLogARB = 0;
PFNGLGETATTACHEDOBJECTSARBPROC                  glGetAttachedObjectsARB = 0;
PFNGLGETUNIFORMLOCATIONARBPROC                  glGetUniformLocationARB = 0;
PFNGLGETACTIVEUNIFORMARBPROC                    glGetActiveUniformARB = 0;
PFNGLGETUNIFORMFVARBPROC                        glGetUniformfvARB = 0;
PFNGLGETUNIFORMIVARBPROC                        glGetUniformivARB = 0;
PFNGLGETSHADERSOURCEARBPROC                     glGetShaderSourceARB = 0;

// GL_ARB_texture_compression
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC                glCompressedTexImage3DARB = 0;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC                glCompressedTexImage2DARB = 0;
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC                glCompressedTexImage1DARB = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC             glCompressedTexSubImage3DARB = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC             glCompressedTexSubImage2DARB = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC             glCompressedTexSubImage1DARB = 0;
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC               glGetCompressedTexImageARB = 0;

// GL_ARB_texture_env_add

// GL_ARB_texture_env_combine

// GL_ARB_texture_rectangle

// GL_ARB_vertex_buffer_object
PFNGLBINDBUFFERARBPROC                          glBindBufferARB = 0;
PFNGLDELETEBUFFERSARBPROC                       glDeleteBuffersARB = 0;
PFNGLGENBUFFERSARBPROC                          glGenBuffersARB = 0;
PFNGLISBUFFERARBPROC                            glIsBufferARB = 0;
PFNGLBUFFERDATAARBPROC                          glBufferDataARB = 0;
PFNGLBUFFERSUBDATAARBPROC                       glBufferSubDataARB = 0;
PFNGLGETBUFFERSUBDATAARBPROC                    glGetBufferSubDataARB = 0;
PFNGLMAPBUFFERARBPROC                           glMapBufferARB = 0;
PFNGLUNMAPBUFFERARBPROC                         glUnmapBufferARB = 0;
PFNGLGETBUFFERPARAMETERIVARBPROC                glGetBufferParameterivARB = 0;
PFNGLGETBUFFERPOINTERVARBPROC                   glGetBufferPointervARB = 0;

// GL_ARB_vertex_program
PFNGLVERTEXATTRIB1DARBPROC                      glVertexAttrib1dARB = 0;
PFNGLVERTEXATTRIB1DVARBPROC                     glVertexAttrib1dvARB = 0;
PFNGLVERTEXATTRIB1FARBPROC                      glVertexAttrib1fARB = 0;
PFNGLVERTEXATTRIB1FVARBPROC                     glVertexAttrib1fvARB = 0;
PFNGLVERTEXATTRIB1SARBPROC                      glVertexAttrib1sARB = 0;
PFNGLVERTEXATTRIB1SVARBPROC                     glVertexAttrib1svARB = 0;
PFNGLVERTEXATTRIB2DARBPROC                      glVertexAttrib2dARB = 0;
PFNGLVERTEXATTRIB2DVARBPROC                     glVertexAttrib2dvARB = 0;
PFNGLVERTEXATTRIB2FARBPROC                      glVertexAttrib2fARB = 0;
PFNGLVERTEXATTRIB2FVARBPROC                     glVertexAttrib2fvARB = 0;
PFNGLVERTEXATTRIB2SARBPROC                      glVertexAttrib2sARB = 0;
PFNGLVERTEXATTRIB2SVARBPROC                     glVertexAttrib2svARB = 0;
PFNGLVERTEXATTRIB3DARBPROC                      glVertexAttrib3dARB = 0;
PFNGLVERTEXATTRIB3DVARBPROC                     glVertexAttrib3dvARB = 0;
PFNGLVERTEXATTRIB3FARBPROC                      glVertexAttrib3fARB = 0;
PFNGLVERTEXATTRIB3FVARBPROC                     glVertexAttrib3fvARB = 0;
PFNGLVERTEXATTRIB3SARBPROC                      glVertexAttrib3sARB = 0;
PFNGLVERTEXATTRIB3SVARBPROC                     glVertexAttrib3svARB = 0;
PFNGLVERTEXATTRIB4NBVARBPROC                    glVertexAttrib4NbvARB = 0;
PFNGLVERTEXATTRIB4NIVARBPROC                    glVertexAttrib4NivARB = 0;
PFNGLVERTEXATTRIB4NSVARBPROC                    glVertexAttrib4NsvARB = 0;
PFNGLVERTEXATTRIB4NUBARBPROC                    glVertexAttrib4NubARB = 0;
PFNGLVERTEXATTRIB4NUBVARBPROC                   glVertexAttrib4NubvARB = 0;
PFNGLVERTEXATTRIB4NUIVARBPROC                   glVertexAttrib4NuivARB = 0;
PFNGLVERTEXATTRIB4NUSVARBPROC                   glVertexAttrib4NusvARB = 0;
PFNGLVERTEXATTRIB4BVARBPROC                     glVertexAttrib4bvARB = 0;
PFNGLVERTEXATTRIB4DARBPROC                      glVertexAttrib4dARB = 0;
PFNGLVERTEXATTRIB4DVARBPROC                     glVertexAttrib4dvARB = 0;
PFNGLVERTEXATTRIB4FARBPROC                      glVertexAttrib4fARB = 0;
PFNGLVERTEXATTRIB4FVARBPROC                     glVertexAttrib4fvARB = 0;
PFNGLVERTEXATTRIB4IVARBPROC                     glVertexAttrib4ivARB = 0;
PFNGLVERTEXATTRIB4SARBPROC                      glVertexAttrib4sARB = 0;
PFNGLVERTEXATTRIB4SVARBPROC                     glVertexAttrib4svARB = 0;
PFNGLVERTEXATTRIB4UBVARBPROC                    glVertexAttrib4ubvARB = 0;
PFNGLVERTEXATTRIB4UIVARBPROC                    glVertexAttrib4uivARB = 0;
PFNGLVERTEXATTRIB4USVARBPROC                    glVertexAttrib4usvARB = 0;
PFNGLVERTEXATTRIBPOINTERARBPROC                 glVertexAttribPointerARB = 0;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC             glEnableVertexAttribArrayARB = 0;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC            glDisableVertexAttribArrayARB = 0;
PFNGLPROGRAMSTRINGARBPROC                       glProgramStringARB = 0;
PFNGLBINDPROGRAMARBPROC                         glBindProgramARB = 0;
PFNGLDELETEPROGRAMSARBPROC                      glDeleteProgramsARB = 0;
PFNGLGENPROGRAMSARBPROC                         glGenProgramsARB = 0;
PFNGLPROGRAMENVPARAMETER4DARBPROC               glProgramEnvParameter4dARB = 0;
PFNGLPROGRAMENVPARAMETER4DVARBPROC              glProgramEnvParameter4dvARB = 0;
PFNGLPROGRAMENVPARAMETER4FARBPROC               glProgramEnvParameter4fARB = 0;
PFNGLPROGRAMENVPARAMETER4FVARBPROC              glProgramEnvParameter4fvARB = 0;
PFNGLPROGRAMLOCALPARAMETER4DARBPROC             glProgramLocalParameter4dARB = 0;
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC            glProgramLocalParameter4dvARB = 0;
PFNGLPROGRAMLOCALPARAMETER4FARBPROC             glProgramLocalParameter4fARB = 0;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC            glProgramLocalParameter4fvARB = 0;
PFNGLGETPROGRAMENVPARAMETERDVARBPROC            glGetProgramEnvParameterdvARB = 0;
PFNGLGETPROGRAMENVPARAMETERFVARBPROC            glGetProgramEnvParameterfvARB = 0;
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC          glGetProgramLocalParameterdvARB = 0;
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC          glGetProgramLocalParameterfvARB = 0;
PFNGLGETPROGRAMIVARBPROC                        glGetProgramivARB = 0;
PFNGLGETPROGRAMSTRINGARBPROC                    glGetProgramStringARB = 0;
PFNGLGETVERTEXATTRIBDVARBPROC                   glGetVertexAttribdvARB = 0;
PFNGLGETVERTEXATTRIBFVARBPROC                   glGetVertexAttribfvARB = 0;
PFNGLGETVERTEXATTRIBIVARBPROC                   glGetVertexAttribivARB = 0;
PFNGLGETVERTEXATTRIBPOINTERVARBPROC             glGetVertexAttribPointervARB = 0;
PFNGLISPROGRAMARBPROC                           glIsProgramARB = 0;

// GL_ARB_vertex_shader
PFNGLBINDATTRIBLOCATIONARBPROC                  glBindAttribLocationARB = 0;
PFNGLGETACTIVEATTRIBARBPROC                     glGetActiveAttribARB = 0;
PFNGLGETATTRIBLOCATIONARBPROC                   glGetAttribLocationARB = 0;

// GL_SGIS_generate_mipmap

// GL_NV_point_sprite

// GL_NV_texture_rectangle

bool gl::Check ()
{
    bool bCheck = true;

    // Check the number of available texture units
    int iTextureUnits = 0;
    glGetIntegerv (GL_MAX_TEXTURE_UNITS_ARB, &iTextureUnits);
    if (iTextureUnits >= 4)
    {
        printf ("Graphic card has %d texture units\n", iTextureUnits);
    }
    else
    {
        printf ("Graphic card has %d texture units but it must have 4 units at least\n", iTextureUnits);
    }

    if (gl::ARB_fragment_program)
        printf ("GL_ARB_fragment_program is supported\n");
    else
    {
        printf ("GL_ARB_fragment_program is required\n");
        bCheck = false;
    }

    if (gl::ARB_fragment_shader)
        printf ("GL_ARB_fragment_shader is supported\n");
    else
    {
        printf ("GL_ARB_fragment_shader is required\n");
        bCheck = false;
    }

    if (gl::ARB_multitexture)
        printf ("GL_ARB_multitexture is supported\n");
    else
    {
        printf ("GL_ARB_multitexture is required\n");
        bCheck = false;
    }

    if (gl::ARB_point_parameters)
        printf ("GL_ARB_point_parameters is supported\n");
    else
    {
        printf ("GL_ARB_point_parameters is required\n");
        bCheck = false;
    }

    if (gl::ARB_point_sprite && gl::NV_point_sprite)
    {
        printf ("GL_ARB_point_sprite is supported\n");
        printf ("GL_NV_point_sprite is supported\n");
    }
    else if (gl::ARB_point_sprite && !gl::NV_point_sprite)
    {
        printf ("GL_ARB_point_sprite is supported\n");
        printf ("GL_NV_point_sprite isn't supported but it needn't\n");
    }
    else if (!gl::ARB_point_sprite && gl::NV_point_sprite)
    {
        printf ("GL_ARB_point_sprite isn't supported but recommended\n");
        printf ("GL_NV_point_sprite is supported\n");
    }
    else if (!gl::ARB_point_sprite && !gl::NV_point_sprite)
    {
        printf ("GL_ARB_point_sprite isn't supported but it need\n");
        printf ("GL_NV_point_sprite isn't supported but it need\n");
        bCheck = false;
    }

    if (gl::ARB_shader_objects)
        printf ("GL_ARB_shader_objects is supported\n");
    else
    {
        printf ("GL_ARB_shader_objects is required\n");
        bCheck = false;
    }
       
    if (gl::ARB_texture_compression)
        printf ("GL_ARB_texture_compression is supported\n");
    //else
    //    printf ("GL_ARB_texture_compression is required\n");

    if (gl::ARB_texture_env_combine)
        printf ("GL_ARB_texture_env_combine is supported\n");
    else
    {
        printf ("GL_ARB_texture_env_combine is required\n");
        bCheck = false;
    }

    if (gl::ARB_texture_env_add)
        printf ("GL_ARB_texture_env_add is supported\n");
    else
    {
        printf ("GL_ARB_texture_env_add is required\n");
        bCheck = false;
    }

    if (gl::ARB_texture_rectangle && gl::NV_texture_rectangle)
    {
        printf ("GL_NV_texture_rectangle is supported\n");
        printf ("GL_ARB_texture_rectangle is supported\n");
    }
    else if (gl::ARB_texture_rectangle && !gl::NV_texture_rectangle)
    {
        printf ("GL_ARB_texture_rectangle is supported\n");
        printf ("GL_NV_texture_rectangle isn't supported but it needn't\n");
    }
    else if (!gl::ARB_texture_rectangle && gl::NV_texture_rectangle)
    {
        printf ("GL_ARB_texture_rectangle isn't supported but recommended\n");
        printf ("GL_NV_texture_rectangle is supported\n");
    }
    else if (!gl::ARB_texture_rectangle && !gl::NV_texture_rectangle)
    {
        printf ("GL_ARB_texture_rectangle isn't supported but it need\n");
        printf ("GL_NV_texture_rectangle isn't supported but it need\n");
        bCheck = false;
    }

    if (gl::ARB_vertex_buffer_object)
        printf ("GL_ARB_vertex_buffer_object is supported\n");
/*    else
        printf ("GL_ARB_vertex_buffer_object is required\n");
*/
    if (gl::ARB_vertex_program)
        printf ("GL_ARB_vertex_program is supported\n");
    else
    {
        printf ("GL_ARB_vertex_program is required\n");
        bCheck = false;
    }

    if (gl::ARB_vertex_shader)
        printf ("GL_ARB_vertex_shader is supported\n");
    else
    {
        printf ("GL_ARB_vertex_shader is required\n");
        bCheck = false;
    }

    if (gl::SGIS_generate_mipmap)
        printf ("GL_SGIS_generate_mipmap is supported\n");
    else
        printf ("GL_SGIS_generate_mipmap is recommended\n");

    return bCheck;
}

void gl::Init ()
{
    char* szExtension = (char*)glGetString (GL_EXTENSIONS);

    // GL_ARB_fragment_program
    if (strstr (szExtension, "GL_ARB_fragment_program"))
    {
        ARB_fragment_program = true;
    }

    // GL_ARB_fragment_shader
    if (strstr (szExtension, "GL_ARB_fragment_shader"))
    {
        ARB_fragment_shader = true;
    }

    // GL_ARB_multitexture
    if (strstr (szExtension, "GL_ARB_multitexture"))
    {
        ARB_multitexture = true;
	    if (!glActiveTextureARB)
		    glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) SDL_GL_GetProcAddress ("glActiveTextureARB");
	    if (!glClientActiveTextureARB)
		    glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) SDL_GL_GetProcAddress ("glClientActiveTextureARB");
	    if (!glMultiTexCoord2fARB)
		    glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) SDL_GL_GetProcAddress ("glMultiTexCoord2fARB");
	    if (!glMultiTexCoord2fvARB)
		    glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC) SDL_GL_GetProcAddress ("glMultiTexCoord2fvARB");
    }

    // GL_ARB_point_parameters
    if (strstr (szExtension, "GL_ARB_point_parameters"))
    {
        ARB_point_parameters = true;
	    if (!glPointParameterfARB)
		    glPointParameterfARB = (PFNGLPOINTPARAMETERFARBPROC) SDL_GL_GetProcAddress ("glPointParameterfARB");
	    if (!glPointParameterfvARB)
		    glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC) SDL_GL_GetProcAddress ("glPointParameterfvARB");
    }

    // GL_ARB_point_sprite
    if (strstr (szExtension, "GL_ARB_point_sprite"))
    {
        ARB_point_sprite = true;
    }

    // GL_ARB_shader_objects
    if (strstr (szExtension, "GL_ARB_shader_objects"))
    {
        ARB_shader_objects = true;
        if (!glDeleteObjectARB)
            glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) SDL_GL_GetProcAddress ("glDeleteObjectARB");
        if (!glGetHandleARB)
            glGetHandleARB = (PFNGLGETHANDLEARBPROC) SDL_GL_GetProcAddress ("glGetHandleARB");
        if (!glDetachObjectARB)
            glDetachObjectARB = (PFNGLDETACHOBJECTARBPROC) SDL_GL_GetProcAddress ("glDetachObjectARB");
        if (!glCreateShaderObjectARB)
            glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) SDL_GL_GetProcAddress ("glCreateShaderObjectARB");
        if (!glShaderSourceARB)
            glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) SDL_GL_GetProcAddress ("glShaderSourceARB");
        if (!glCompileShaderARB)
            glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) SDL_GL_GetProcAddress ("glCompileShaderARB");
        if (!glCreateProgramObjectARB)
            glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) SDL_GL_GetProcAddress ("glCreateProgramObjectARB");
        if (!glAttachObjectARB)
            glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) SDL_GL_GetProcAddress ("glAttachObjectARB");
        if (!glLinkProgramARB)
            glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) SDL_GL_GetProcAddress ("glLinkProgramARB");
        if (!glUseProgramObjectARB)
            glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) SDL_GL_GetProcAddress ("glUseProgramObjectARB");
        if (!glValidateProgramARB)
            glValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC) SDL_GL_GetProcAddress ("glValidateProgramARB");
        if (!glUniform1fARB)
            glUniform1fARB = (PFNGLUNIFORM1FARBPROC) SDL_GL_GetProcAddress ("glUniform1fARB");
        if (!glUniform2fARB)
            glUniform2fARB = (PFNGLUNIFORM2FARBPROC) SDL_GL_GetProcAddress ("glUniform2fARB");
        if (!glUniform3fARB)
            glUniform3fARB = (PFNGLUNIFORM3FARBPROC) SDL_GL_GetProcAddress ("glUniform3fARB");
        if (!glUniform4fARB)
            glUniform4fARB = (PFNGLUNIFORM4FARBPROC) SDL_GL_GetProcAddress ("glUniform4fARB");
        if (!glUniform1iARB)
            glUniform1iARB = (PFNGLUNIFORM1IARBPROC) SDL_GL_GetProcAddress ("glUniform1iARB");
        if (!glUniform2iARB)
            glUniform2iARB = (PFNGLUNIFORM2IARBPROC) SDL_GL_GetProcAddress ("glUniform2iARB");
        if (!glUniform3iARB)
            glUniform3iARB = (PFNGLUNIFORM3IARBPROC) SDL_GL_GetProcAddress ("glUniform3iARB");
        if (!glUniform4iARB)
            glUniform4iARB = (PFNGLUNIFORM4IARBPROC) SDL_GL_GetProcAddress ("glUniform4iARB");
        if (!glUniform1fvARB)
            glUniform1fvARB = (PFNGLUNIFORM1FVARBPROC) SDL_GL_GetProcAddress ("glUniform1fvARB");
        if (!glUniform2fvARB)
            glUniform2fvARB = (PFNGLUNIFORM2FVARBPROC) SDL_GL_GetProcAddress ("glUniform2fvARB");
        if (!glUniform3fvARB)
            glUniform3fvARB = (PFNGLUNIFORM3FVARBPROC) SDL_GL_GetProcAddress ("glUniform3fvARB");
        if (!glUniform4fvARB)
            glUniform4fvARB = (PFNGLUNIFORM4FVARBPROC) SDL_GL_GetProcAddress ("glUniform4fvARB");
        if (!glUniform1ivARB)
            glUniform1ivARB = (PFNGLUNIFORM1IVARBPROC) SDL_GL_GetProcAddress ("glUniform1ivARB");
        if (!glUniform2ivARB)
            glUniform2ivARB = (PFNGLUNIFORM2IVARBPROC) SDL_GL_GetProcAddress ("glUniform2ivARB");
        if (!glUniform3ivARB)
            glUniform3ivARB = (PFNGLUNIFORM3IVARBPROC) SDL_GL_GetProcAddress ("glUniform3ivARB");
        if (!glUniform4ivARB)
            glUniform4ivARB = (PFNGLUNIFORM4IVARBPROC) SDL_GL_GetProcAddress ("glUniform4ivARB");
        if (!glUniformMatrix2fvARB)
            glUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC) SDL_GL_GetProcAddress ("glUniformMatrix2fvARB");
        if (!glUniformMatrix3fvARB)
            glUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC) SDL_GL_GetProcAddress ("glUniformMatrix3fvARB");
        if (!glUniformMatrix4fvARB)
            glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC) SDL_GL_GetProcAddress ("glUniformMatrix4fvARB");
        if (!glGetObjectParameterfvARB)
            glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC) SDL_GL_GetProcAddress ("glGetObjectParameterfvARB");
        if (!glGetObjectParameterivARB)
            glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) SDL_GL_GetProcAddress ("glGetObjectParameterivARB");
        if (!glGetInfoLogARB)
            glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) SDL_GL_GetProcAddress ("glGetInfoLogARB");
        if (!glGetAttachedObjectsARB)
            glGetAttachedObjectsARB = (PFNGLGETATTACHEDOBJECTSARBPROC) SDL_GL_GetProcAddress ("glGetAttachedObjectsARB");
        if (!glGetUniformLocationARB)
            glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) SDL_GL_GetProcAddress ("glGetUniformLocationARB");
        if (!glGetActiveUniformARB)
            glGetActiveUniformARB = (PFNGLGETACTIVEUNIFORMARBPROC) SDL_GL_GetProcAddress ("glGetActiveUniformARB");
        if (!glGetUniformfvARB)
            glGetUniformfvARB = (PFNGLGETUNIFORMFVARBPROC) SDL_GL_GetProcAddress ("glGetUniformfvARB");
        if (!glGetUniformivARB)
            glGetUniformivARB = (PFNGLGETUNIFORMIVARBPROC) SDL_GL_GetProcAddress ("glGetUniformivARB");
        if (!glGetShaderSourceARB)
            glGetShaderSourceARB = (PFNGLGETSHADERSOURCEARBPROC) SDL_GL_GetProcAddress ("glGetShaderSourceARB");
    }

    // GL_ARB_texture_compression
    if (strstr (szExtension, "GL_ARB_texture_compression"))
    {
        ARB_texture_compression = true;
        if (!glCompressedTexImage3DARB)
            glCompressedTexImage3DARB = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC) SDL_GL_GetProcAddress ("glCompressedTexImage3DARB");
        if (!glCompressedTexImage2DARB)
            glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC) SDL_GL_GetProcAddress ("glCompressedTexImage2DARB");
        if (!glCompressedTexImage1DARB)
            glCompressedTexImage1DARB = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC) SDL_GL_GetProcAddress ("glCompressedTexImage1DARB");
        if (!glCompressedTexSubImage3DARB)
            glCompressedTexSubImage3DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC) SDL_GL_GetProcAddress ("glCompressedTexSubImage3DARB");
        if (!glCompressedTexSubImage2DARB)
            glCompressedTexSubImage2DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC) SDL_GL_GetProcAddress ("glCompressedTexSubImage2DARB");
        if (!glCompressedTexSubImage1DARB)
            glCompressedTexSubImage1DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC) SDL_GL_GetProcAddress ("glCompressedTexSubImage1DARB");
        if (!glGetCompressedTexImageARB)
            glGetCompressedTexImageARB = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC) SDL_GL_GetProcAddress ("glGetCompressedTexImageARB");
    }

    // GL_ARB_texture_end_combine
    if (strstr (szExtension, "GL_ARB_texture_env_combine"))
    {
        ARB_texture_env_combine = true;
    }

    // GL_ARB_texture_end_add
    if (strstr (szExtension, "GL_ARB_texture_env_add"))
    {
        ARB_texture_env_add = true;
    }

    // GL_ARB_texture_rectangle
    if (strstr (szExtension, "GL_ARB_texture_rectangle"))
    {
        ARB_texture_rectangle = true;
    }

    // GL_ARB_vertex_buffer_object
    if (strstr (szExtension, "GL_ARB_vertex_buffer_object"))
    {
        ARB_vertex_buffer_object = true;
        if (!glBindBufferARB)
            glBindBufferARB = (PFNGLBINDBUFFERARBPROC) SDL_GL_GetProcAddress ("glBindBufferARB");
        if (!glDeleteBuffersARB)
            glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) SDL_GL_GetProcAddress ("glDeleteBuffersARB");
        if (!glGenBuffersARB)
            glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) SDL_GL_GetProcAddress ("glGenBuffersARB");
        if (!glIsBufferARB)
            glIsBufferARB = (PFNGLISBUFFERARBPROC) SDL_GL_GetProcAddress ("glIsBufferARB");
        if (!glBufferDataARB)
            glBufferDataARB = (PFNGLBUFFERDATAARBPROC) SDL_GL_GetProcAddress ("glBufferDataARB");
        if (!glBufferSubDataARB)
            glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC) SDL_GL_GetProcAddress ("glBufferSubDataARB");
        if (!glGetBufferSubDataARB)
            glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC) SDL_GL_GetProcAddress ("glGetBufferSubDataARB");
        if (!glMapBufferARB)
            glMapBufferARB = (PFNGLMAPBUFFERARBPROC) SDL_GL_GetProcAddress ("glMapBufferARB");
        if (!glUnmapBufferARB)
            glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) SDL_GL_GetProcAddress ("glUnmapBufferARB");
        if (!glGetBufferParameterivARB)
            glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) SDL_GL_GetProcAddress ("glGetBufferParameterivARB");
        if (!glGetBufferPointervARB)
            glGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC) SDL_GL_GetProcAddress ("glGetBufferPointervARB");
    }

    // GL_ARB_vertex_program
    if (strstr (szExtension, "GL_ARB_vertex_program"))
    {
        ARB_vertex_program = true;
        if (!glVertexAttrib1dARB)
            glVertexAttrib1dARB = (PFNGLVERTEXATTRIB1DARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib1dARB");
        if (!glVertexAttrib1dvARB)
            glVertexAttrib1dvARB = (PFNGLVERTEXATTRIB1DVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib1dvARB");
        if (!glVertexAttrib1fARB)
            glVertexAttrib1fARB = (PFNGLVERTEXATTRIB1FARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib1fARB");
        if (!glVertexAttrib1fvARB)
            glVertexAttrib1fvARB = (PFNGLVERTEXATTRIB1FVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib1fvARB");
        if (!glVertexAttrib1sARB)
            glVertexAttrib1sARB = (PFNGLVERTEXATTRIB1SARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib1sARB");
        if (!glVertexAttrib1svARB)
            glVertexAttrib1svARB = (PFNGLVERTEXATTRIB1SVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib1svARB");
        if (!glVertexAttrib2dARB)
            glVertexAttrib2dARB = (PFNGLVERTEXATTRIB2DARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib2dARB");
        if (!glVertexAttrib2dvARB)
            glVertexAttrib2dvARB = (PFNGLVERTEXATTRIB2DVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib2dvARB");
        if (!glVertexAttrib2fARB)
            glVertexAttrib2fARB = (PFNGLVERTEXATTRIB2FARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib2fARB");
        if (!glVertexAttrib2fvARB)
            glVertexAttrib2fvARB = (PFNGLVERTEXATTRIB2FVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib2fvARB");
        if (!glVertexAttrib2sARB)
            glVertexAttrib2sARB = (PFNGLVERTEXATTRIB2SARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib2sARB");
        if (!glVertexAttrib2svARB)
            glVertexAttrib2svARB = (PFNGLVERTEXATTRIB2SVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib2svARB");
        if (!glVertexAttrib3dARB)
            glVertexAttrib3dARB = (PFNGLVERTEXATTRIB3DARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib3dARB");
        if (!glVertexAttrib3dvARB)
            glVertexAttrib3dvARB = (PFNGLVERTEXATTRIB3DVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib3dvARB");
        if (!glVertexAttrib3fARB)
            glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib3fARB");
        if (!glVertexAttrib3fvARB)
            glVertexAttrib3fvARB = (PFNGLVERTEXATTRIB3FVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib3fvARB");
        if (!glVertexAttrib3sARB)
            glVertexAttrib3sARB = (PFNGLVERTEXATTRIB3SARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib3sARB");
        if (!glVertexAttrib3svARB)
            glVertexAttrib3svARB = (PFNGLVERTEXATTRIB3SVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib3svARB");
        if (!glVertexAttrib4NbvARB)
            glVertexAttrib4NbvARB = (PFNGLVERTEXATTRIB4NBVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4NbvARB");
        if (!glVertexAttrib4NivARB)
            glVertexAttrib4NivARB = (PFNGLVERTEXATTRIB4NIVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4NivARB");
        if (!glVertexAttrib4NsvARB)
            glVertexAttrib4NsvARB = (PFNGLVERTEXATTRIB4NSVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4NsvARB");
        if (!glVertexAttrib4NubARB)
            glVertexAttrib4NubARB = (PFNGLVERTEXATTRIB4NUBARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4NubARB");
        if (!glVertexAttrib4NubvARB)
            glVertexAttrib4NubvARB = (PFNGLVERTEXATTRIB4NUBVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4NubvARB");
        if (!glVertexAttrib4NuivARB)
            glVertexAttrib4NuivARB = (PFNGLVERTEXATTRIB4NUIVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4NuivARB");
        if (!glVertexAttrib4NusvARB)
            glVertexAttrib4NusvARB = (PFNGLVERTEXATTRIB4NUSVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4NusvARB");
        if (!glVertexAttrib4bvARB)
            glVertexAttrib4bvARB = (PFNGLVERTEXATTRIB4BVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4bvARB");
        if (!glVertexAttrib4dARB)
            glVertexAttrib4dARB = (PFNGLVERTEXATTRIB4DARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4dARB");
        if (!glVertexAttrib4dvARB)
            glVertexAttrib4dvARB = (PFNGLVERTEXATTRIB4DVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4dvARB");
        if (!glVertexAttrib4fARB)
            glVertexAttrib4fARB = (PFNGLVERTEXATTRIB4FARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4fARB");
        if (!glVertexAttrib4fvARB)
            glVertexAttrib4fvARB = (PFNGLVERTEXATTRIB4FVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4fvARB");
        if (!glVertexAttrib4ivARB)
            glVertexAttrib4ivARB = (PFNGLVERTEXATTRIB4IVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4ivARB");
        if (!glVertexAttrib4sARB)
            glVertexAttrib4sARB = (PFNGLVERTEXATTRIB4SARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4sARB");
        if (!glVertexAttrib4svARB)
            glVertexAttrib4svARB = (PFNGLVERTEXATTRIB4SVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4svARB");
        if (!glVertexAttrib4ubvARB)
            glVertexAttrib4ubvARB = (PFNGLVERTEXATTRIB4UBVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4ubvARB");
        if (!glVertexAttrib4uivARB)
            glVertexAttrib4uivARB = (PFNGLVERTEXATTRIB4UIVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4uivARB");
        if (!glVertexAttrib4usvARB)
            glVertexAttrib4usvARB = (PFNGLVERTEXATTRIB4USVARBPROC) SDL_GL_GetProcAddress ("glVertexAttrib4usvARB");
        if (!glVertexAttribPointerARB)
            glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC) SDL_GL_GetProcAddress ("glVertexAttribPointerARB");
        if (!glEnableVertexAttribArrayARB)
            glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) SDL_GL_GetProcAddress ("glEnableVertexAttribArrayARB");
        if (!glDisableVertexAttribArrayARB)
            glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) SDL_GL_GetProcAddress ("glDisableVertexAttribArrayARB");
        if (!glProgramStringARB)
            glProgramStringARB = (PFNGLPROGRAMSTRINGARBPROC) SDL_GL_GetProcAddress ("glProgramStringARB");
        if (!glBindProgramARB)
            glBindProgramARB = (PFNGLBINDPROGRAMARBPROC) SDL_GL_GetProcAddress ("glBindProgramARB");
        if (!glDeleteProgramsARB)
            glDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC) SDL_GL_GetProcAddress ("glDeleteProgramsARB");
        if (!glGenProgramsARB)
            glGenProgramsARB = (PFNGLGENPROGRAMSARBPROC) SDL_GL_GetProcAddress ("glGenProgramsARB");
        if (!glProgramEnvParameter4dARB)
            glProgramEnvParameter4dARB = (PFNGLPROGRAMENVPARAMETER4DARBPROC) SDL_GL_GetProcAddress ("glProgramEnvParameter4dARB");
        if (!glProgramEnvParameter4dvARB)
            glProgramEnvParameter4dvARB = (PFNGLPROGRAMENVPARAMETER4DVARBPROC) SDL_GL_GetProcAddress ("glProgramEnvParameter4dvARB");
        if (!glProgramEnvParameter4fARB)
            glProgramEnvParameter4fARB = (PFNGLPROGRAMENVPARAMETER4FARBPROC) SDL_GL_GetProcAddress ("glProgramEnvParameter4fARB");
        if (!glProgramEnvParameter4fvARB)
            glProgramEnvParameter4fvARB = (PFNGLPROGRAMENVPARAMETER4FVARBPROC) SDL_GL_GetProcAddress ("glProgramEnvParameter4fvARB");
        if (!glProgramLocalParameter4dARB)
            glProgramLocalParameter4dARB = (PFNGLPROGRAMLOCALPARAMETER4DARBPROC) SDL_GL_GetProcAddress ("glProgramLocalParameter4dARB");
        if (!glProgramLocalParameter4dvARB)
            glProgramLocalParameter4dvARB = (PFNGLPROGRAMLOCALPARAMETER4DVARBPROC) SDL_GL_GetProcAddress ("glProgramLocalParameter4dvARB");
        if (!glProgramLocalParameter4fARB)
            glProgramLocalParameter4fARB = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC) SDL_GL_GetProcAddress ("glProgramLocalParameter4fARB");
        if (!glProgramLocalParameter4fvARB)
            glProgramLocalParameter4fvARB = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC) SDL_GL_GetProcAddress ("glProgramLocalParameter4fvARB");
        if (!glGetProgramEnvParameterdvARB)
            glGetProgramEnvParameterdvARB = (PFNGLGETPROGRAMENVPARAMETERDVARBPROC) SDL_GL_GetProcAddress ("glGetProgramEnvParameterdvARB");
        if (!glGetProgramEnvParameterfvARB)
            glGetProgramEnvParameterfvARB = (PFNGLGETPROGRAMENVPARAMETERFVARBPROC) SDL_GL_GetProcAddress ("glGetProgramEnvParameterfvARB");
        if (!glGetProgramLocalParameterdvARB)
            glGetProgramLocalParameterdvARB = (PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC) SDL_GL_GetProcAddress ("glGetProgramLocalParameterdvARB");
        if (!glGetProgramLocalParameterfvARB)
            glGetProgramLocalParameterfvARB = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC) SDL_GL_GetProcAddress ("glGetProgramLocalParameterfvARB");
        if (!glGetProgramivARB)
            glGetProgramivARB = (PFNGLGETPROGRAMIVARBPROC) SDL_GL_GetProcAddress ("glGetProgramivARB");
        if (!glGetProgramStringARB)
            glGetProgramStringARB = (PFNGLGETPROGRAMSTRINGARBPROC) SDL_GL_GetProcAddress ("glGetProgramStringARB");
        if (!glGetVertexAttribdvARB)
            glGetVertexAttribdvARB = (PFNGLGETVERTEXATTRIBDVARBPROC) SDL_GL_GetProcAddress ("glGetVertexAttribdvARB");
        if (!glGetVertexAttribfvARB)
            glGetVertexAttribfvARB = (PFNGLGETVERTEXATTRIBFVARBPROC) SDL_GL_GetProcAddress ("glGetVertexAttribfvARB");
        if (!glGetVertexAttribivARB)
            glGetVertexAttribivARB = (PFNGLGETVERTEXATTRIBIVARBPROC) SDL_GL_GetProcAddress ("glGetVertexAttribivARB");
        if (!glGetVertexAttribPointervARB)
            glGetVertexAttribPointervARB = (PFNGLGETVERTEXATTRIBPOINTERVARBPROC) SDL_GL_GetProcAddress ("glGetVertexAttribPointervARB");
        if (!glIsProgramARB)
            glIsProgramARB = (PFNGLISPROGRAMARBPROC) SDL_GL_GetProcAddress ("glIsProgramARB");
    }

    // GL_ARB_vertex_shader
    if (strstr (szExtension, "GL_ARB_vertex_shader"))
    {
        ARB_vertex_shader = true;
        if (!glBindAttribLocationARB)
            glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC) SDL_GL_GetProcAddress ("glBindAttribLocationARB");
        if (!glGetActiveAttribARB)
            glGetActiveAttribARB = (PFNGLGETACTIVEATTRIBARBPROC) SDL_GL_GetProcAddress ("glGetActiveAttribARB");
        if (!glGetAttribLocationARB)
            glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC) SDL_GL_GetProcAddress ("glGetAttribLocationARB");
    }

    // GL_SGIS_generate_mipmap
    if (strstr (szExtension, "GL_SGIS_generate_mipmap"))
    {
        SGIS_generate_mipmap = true;
    }

    // GL_NV_point_sprite
    if (strstr (szExtension, "GL_NV_point_sprite"))
    {
        NV_point_sprite = true;
    }

    // GL_NV_texture_rectangle
    if (strstr (szExtension, "GL_NV_texture_rectangle"))
    {
        NV_texture_rectangle = true;
    }
}
