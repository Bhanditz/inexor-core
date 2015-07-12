// rendergl.cpp: core opengl rendering stuff

#include "inexor/engine/engine.h"
#include "inexor/shared/filesystem.h"

bool hasTR = false, hasFBO = false, hasDS = false, hasTF = false, hasTRG = false, hasS3TC = false, hasFXT1 = false, hasAF = false, hasNVFB = false, hasFBB = false, hasUBO = false, hasMBR = false;
int hasstencil = 0;

VAR(glversion, 1, 0, 0);
VAR(glslversion, 1, 0, 0);

// OpenGL 1.3
#ifdef WIN32
PFNGLACTIVETEXTUREPROC       glActiveTexture_       = NULL;
PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture_ = NULL;

PFNGLBLENDEQUATIONEXTPROC glBlendEquation_ = NULL;
PFNGLBLENDCOLOREXTPROC    glBlendColor_    = NULL;

PFNGLTEXIMAGE3DPROC        glTexImage3D_        = NULL;
PFNGLTEXSUBIMAGE3DPROC     glTexSubImage3D_     = NULL;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D_ = NULL;

PFNGLCOMPRESSEDTEXIMAGE3DPROC    glCompressedTexImage3D_    = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC    glCompressedTexImage2D_    = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DPROC    glCompressedTexImage1D_    = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D_ = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D_ = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D_ = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEPROC   glGetCompressedTexImage_   = NULL;

PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements_ = NULL;
#endif

// OpenGL 2.1
#ifndef __APPLE__
PFNGLMULTIDRAWARRAYSPROC   glMultiDrawArrays_   = NULL;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements_ = NULL;

PFNGLBLENDFUNCSEPARATEPROC     glBlendFuncSeparate_     = NULL;
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate_ = NULL;
PFNGLSTENCILOPSEPARATEPROC     glStencilOpSeparate_     = NULL;
PFNGLSTENCILFUNCSEPARATEPROC   glStencilFuncSeparate_   = NULL;
PFNGLSTENCILMASKSEPARATEPROC   glStencilMaskSeparate_   = NULL;

PFNGLGENBUFFERSPROC       glGenBuffers_       = NULL;
PFNGLBINDBUFFERPROC       glBindBuffer_       = NULL;
PFNGLMAPBUFFERPROC        glMapBuffer_        = NULL;
PFNGLUNMAPBUFFERPROC      glUnmapBuffer_      = NULL;
PFNGLBUFFERDATAPROC       glBufferData_       = NULL;
PFNGLBUFFERSUBDATAPROC    glBufferSubData_    = NULL;
PFNGLDELETEBUFFERSPROC    glDeleteBuffers_    = NULL;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData_ = NULL;

PFNGLGENQUERIESPROC        glGenQueries_        = NULL;
PFNGLDELETEQUERIESPROC     glDeleteQueries_     = NULL;
PFNGLBEGINQUERYPROC        glBeginQuery_        = NULL;
PFNGLENDQUERYPROC          glEndQuery_          = NULL;
PFNGLGETQUERYIVPROC        glGetQueryiv_        = NULL;
PFNGLGETQUERYOBJECTIVPROC  glGetQueryObjectiv_  = NULL;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv_ = NULL;

PFNGLCREATEPROGRAMPROC            glCreateProgram_            = NULL;
PFNGLDELETEPROGRAMPROC            glDeleteProgram_            = NULL;
PFNGLUSEPROGRAMPROC               glUseProgram_               = NULL;
PFNGLCREATESHADERPROC             glCreateShader_             = NULL;
PFNGLDELETESHADERPROC             glDeleteShader_             = NULL;
PFNGLSHADERSOURCEPROC             glShaderSource_             = NULL;
PFNGLCOMPILESHADERPROC            glCompileShader_            = NULL;
PFNGLGETSHADERIVPROC              glGetShaderiv_              = NULL;
PFNGLGETPROGRAMIVPROC             glGetProgramiv_             = NULL;
PFNGLATTACHSHADERPROC             glAttachShader_             = NULL;
PFNGLGETPROGRAMINFOLOGPROC        glGetProgramInfoLog_        = NULL;
PFNGLGETSHADERINFOLOGPROC         glGetShaderInfoLog_         = NULL;
PFNGLLINKPROGRAMPROC              glLinkProgram_              = NULL;
PFNGLGETUNIFORMLOCATIONPROC       glGetUniformLocation_       = NULL;
PFNGLUNIFORM1FPROC                glUniform1f_                = NULL;
PFNGLUNIFORM2FPROC                glUniform2f_                = NULL;
PFNGLUNIFORM3FPROC                glUniform3f_                = NULL;
PFNGLUNIFORM4FPROC                glUniform4f_                = NULL;
PFNGLUNIFORM1FVPROC               glUniform1fv_               = NULL;
PFNGLUNIFORM2FVPROC               glUniform2fv_               = NULL;
PFNGLUNIFORM3FVPROC               glUniform3fv_               = NULL;
PFNGLUNIFORM4FVPROC               glUniform4fv_               = NULL;
PFNGLUNIFORM1IPROC                glUniform1i_                = NULL;
PFNGLUNIFORM2IPROC                glUniform2i_                = NULL;
PFNGLUNIFORM3IPROC                glUniform3i_                = NULL;
PFNGLUNIFORM4IPROC                glUniform4i_                = NULL;
PFNGLUNIFORM1IVPROC               glUniform1iv_               = NULL;
PFNGLUNIFORM2IVPROC               glUniform2iv_               = NULL;
PFNGLUNIFORM3IVPROC               glUniform3iv_               = NULL;
PFNGLUNIFORM4IVPROC               glUniform4iv_               = NULL;
PFNGLUNIFORMMATRIX2FVPROC         glUniformMatrix2fv_         = NULL;
PFNGLUNIFORMMATRIX3FVPROC         glUniformMatrix3fv_         = NULL;
PFNGLUNIFORMMATRIX4FVPROC         glUniformMatrix4fv_         = NULL;
PFNGLBINDATTRIBLOCATIONPROC       glBindAttribLocation_       = NULL;
PFNGLGETACTIVEUNIFORMPROC         glGetActiveUniform_         = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray_  = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray_ = NULL;

PFNGLVERTEXATTRIB1FPROC           glVertexAttrib1f_           = NULL;
PFNGLVERTEXATTRIB1FVPROC          glVertexAttrib1fv_          = NULL;
PFNGLVERTEXATTRIB1SPROC           glVertexAttrib1s_           = NULL;
PFNGLVERTEXATTRIB1SVPROC          glVertexAttrib1sv_          = NULL;
PFNGLVERTEXATTRIB2FPROC           glVertexAttrib2f_           = NULL;
PFNGLVERTEXATTRIB2FVPROC          glVertexAttrib2fv_          = NULL;
PFNGLVERTEXATTRIB2SPROC           glVertexAttrib2s_           = NULL;
PFNGLVERTEXATTRIB2SVPROC          glVertexAttrib2sv_          = NULL;
PFNGLVERTEXATTRIB3FPROC           glVertexAttrib3f_           = NULL;
PFNGLVERTEXATTRIB3FVPROC          glVertexAttrib3fv_          = NULL;
PFNGLVERTEXATTRIB3SPROC           glVertexAttrib3s_           = NULL;
PFNGLVERTEXATTRIB3SVPROC          glVertexAttrib3sv_          = NULL;
PFNGLVERTEXATTRIB4FPROC           glVertexAttrib4f_           = NULL;
PFNGLVERTEXATTRIB4FVPROC          glVertexAttrib4fv_          = NULL;
PFNGLVERTEXATTRIB4SPROC           glVertexAttrib4s_           = NULL;
PFNGLVERTEXATTRIB4SVPROC          glVertexAttrib4sv_          = NULL;
PFNGLVERTEXATTRIB4BVPROC          glVertexAttrib4bv_          = NULL;
PFNGLVERTEXATTRIB4IVPROC          glVertexAttrib4iv_          = NULL;
PFNGLVERTEXATTRIB4UBVPROC         glVertexAttrib4ubv_         = NULL;
PFNGLVERTEXATTRIB4UIVPROC         glVertexAttrib4uiv_         = NULL;
PFNGLVERTEXATTRIB4USVPROC         glVertexAttrib4usv_         = NULL;
PFNGLVERTEXATTRIB4NBVPROC         glVertexAttrib4Nbv_         = NULL;
PFNGLVERTEXATTRIB4NIVPROC         glVertexAttrib4Niv_         = NULL;
PFNGLVERTEXATTRIB4NUBPROC         glVertexAttrib4Nub_         = NULL;
PFNGLVERTEXATTRIB4NUBVPROC        glVertexAttrib4Nubv_        = NULL;
PFNGLVERTEXATTRIB4NUIVPROC        glVertexAttrib4Nuiv_        = NULL;
PFNGLVERTEXATTRIB4NUSVPROC        glVertexAttrib4Nusv_        = NULL;
PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer_      = NULL;

PFNGLUNIFORMMATRIX2X3FVPROC       glUniformMatrix2x3fv_       = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC       glUniformMatrix3x2fv_       = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC       glUniformMatrix2x4fv_       = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC       glUniformMatrix4x2fv_       = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC       glUniformMatrix3x4fv_       = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC       glUniformMatrix4x3fv_       = NULL;

PFNGLDRAWBUFFERSPROC glDrawBuffers_ = NULL;
#endif

// GL_EXT_framebuffer_object
PFNGLBINDRENDERBUFFEREXTPROC        glBindRenderbuffer_        = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC     glDeleteRenderbuffers_     = NULL;
PFNGLGENFRAMEBUFFERSEXTPROC         glGenRenderbuffers_        = NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC     glRenderbufferStorage_     = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC  glCheckFramebufferStatus_  = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC         glBindFramebuffer_         = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC      glDeleteFramebuffers_      = NULL;
PFNGLGENFRAMEBUFFERSEXTPROC         glGenFramebuffers_         = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC    glFramebufferTexture2D_    = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbuffer_ = NULL;
PFNGLGENERATEMIPMAPEXTPROC          glGenerateMipmap_          = NULL;

// GL_EXT_framebuffer_blit
PFNGLBLITFRAMEBUFFEREXTPROC         glBlitFramebuffer_         = NULL;

// GL_ARB_uniform_buffer_object
PFNGLGETUNIFORMINDICESPROC       glGetUniformIndices_       = NULL;
PFNGLGETACTIVEUNIFORMSIVPROC     glGetActiveUniformsiv_     = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC    glGetUniformBlockIndex_    = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv_ = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC     glUniformBlockBinding_     = NULL;
PFNGLBINDBUFFERBASEPROC          glBindBufferBase_          = NULL;
PFNGLBINDBUFFERRANGEPROC         glBindBufferRange_         = NULL;

// GL_ARB_map_buffer_range
PFNGLMAPBUFFERRANGEPROC         glMapBufferRange_         = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange_ = NULL;

void *getprocaddress(const char *name)
{
    return SDL_GL_GetProcAddress(name);
}

VARP(ati_skybox_bug, 0, 0, 1);
VAR(ati_minmax_bug, 0, 0, 1);
VAR(ati_cubemap_bug, 0, 0, 1);
VAR(intel_immediate_bug, 0, 0, 1);
VAR(intel_vertexarray_bug, 0, 0, 1);
VAR(sdl_backingstore_bug, -1, 0, 1);
VAR(minimizetcusage, 1, 0, 0);
VAR(usetexrect, 1, 0, 0);
VAR(useubo, 1, 0, 0);
VAR(usetexcompress, 1, 0, 0);
VAR(rtscissor, 0, 1, 1);
VAR(blurtile, 0, 1, 1);
VAR(rtsharefb, 0, 1, 1);

VAR(dbgexts, 0, 0, 1);

bool hasext(const char *exts, const char *ext)
{
    int len = strlen(ext);
    if(len) for(const char *cur = exts; (cur = strstr(cur, ext)); cur += len)
    {
        if((cur == exts || cur[-1] == ' ') && (cur[len] == ' ' || !cur[len])) return true;
    }
    return false;
}

void gl_checkextensions()
{
    const char *vendor = (const char *)glGetString(GL_VENDOR);
    const char *exts = (const char *)glGetString(GL_EXTENSIONS);
    const char *renderer = (const char *)glGetString(GL_RENDERER);
    const char *version = (const char *)glGetString(GL_VERSION);
    conoutf(CON_INIT, "Renderer: %s (%s)", renderer, vendor);
    conoutf(CON_INIT, "Driver: %s", version);

#ifdef __APPLE__
    extern int mac_osversion();
    int osversion = mac_osversion();  /* 0x0A0500 = 10.5 (Leopard) */
    sdl_backingstore_bug = -1;
#endif

    bool mesa = false, intel = false, ati = false, nvidia = false;
    if(strstr(renderer, "Mesa") || strstr(version, "Mesa"))
    {
        mesa = true;
        if(strstr(renderer, "Intel")) intel = true;
    }
    else if(strstr(vendor, "NVIDIA"))
        nvidia = true;
    else if(strstr(vendor, "ATI") || strstr(vendor, "Advanced Micro Devices"))
        ati = true;
    else if(strstr(vendor, "Intel"))
        intel = true;

    uint glmajorversion, glminorversion;
    if(sscanf(version, " %u.%u", &glmajorversion, &glminorversion) != 2) glversion = 100;
    else glversion = glmajorversion*100 + glminorversion*10;

    if(glversion < 210) fatal("OpenGL 2.1 or greater is required!");

    const char *glslstr = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
    uint glslmajorversion, glslminorversion;
    if(glslstr && sscanf(glslstr, " %u.%u", &glslmajorversion, &glslminorversion) == 2) glslversion = glslmajorversion*100 + glslminorversion;

    if(glslversion < 120) fatal("GLSL 1.20 or greater is required!");

    GLint val;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &val);
    hwtexsize = val;
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &val);
    hwcubetexsize = val;

#ifdef WIN32
    glActiveTexture_ =            (PFNGLACTIVETEXTUREPROC)            getprocaddress("glActiveTexture");
    glClientActiveTexture_ =      (PFNGLCLIENTACTIVETEXTUREPROC)      getprocaddress("glClientActiveTexture");

    glBlendEquation_ =            (PFNGLBLENDEQUATIONPROC)            getprocaddress("glBlendEquation");
    glBlendColor_ =               (PFNGLBLENDCOLORPROC)               getprocaddress("glBlendColor");

    glTexImage3D_ =               (PFNGLTEXIMAGE3DPROC)               getprocaddress("glTexImage3D");
    glTexSubImage3D_ =            (PFNGLTEXSUBIMAGE3DPROC)            getprocaddress("glTexSubImage3D");
    glCopyTexSubImage3D_ =        (PFNGLCOPYTEXSUBIMAGE3DPROC)        getprocaddress("glCopyTexSubImage3D");

    glCompressedTexImage3D_ =     (PFNGLCOMPRESSEDTEXIMAGE3DPROC)     getprocaddress("glCompressedTexImage3D");
    glCompressedTexImage2D_ =     (PFNGLCOMPRESSEDTEXIMAGE2DPROC)     getprocaddress("glCompressedTexImage2D");
    glCompressedTexImage1D_ =     (PFNGLCOMPRESSEDTEXIMAGE1DPROC)     getprocaddress("glCompressedTexImage1D");
    glCompressedTexSubImage3D_ =  (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)  getprocaddress("glCompressedTexSubImage3D");
    glCompressedTexSubImage2D_ =  (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)  getprocaddress("glCompressedTexSubImage2D");
    glCompressedTexSubImage1D_ =  (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)  getprocaddress("glCompressedTexSubImage1D");
    glGetCompressedTexImage_ =    (PFNGLGETCOMPRESSEDTEXIMAGEPROC)    getprocaddress("glGetCompressedTexImage");

    glDrawRangeElements_ =        (PFNGLDRAWRANGEELEMENTSPROC)        getprocaddress("glDrawRangeElements");
#endif

#ifndef __APPLE__
    glMultiDrawArrays_ =          (PFNGLMULTIDRAWARRAYSPROC)          getprocaddress("glMultiDrawArrays");
    glMultiDrawElements_ =        (PFNGLMULTIDRAWELEMENTSPROC)        getprocaddress("glMultiDrawElements");

    glBlendFuncSeparate_ =        (PFNGLBLENDFUNCSEPARATEPROC)        getprocaddress("glBlendFuncSeparate");
    glBlendEquationSeparate_ =    (PFNGLBLENDEQUATIONSEPARATEPROC)    getprocaddress("glBlendEquationSeparate");
    glStencilOpSeparate_ =        (PFNGLSTENCILOPSEPARATEPROC)        getprocaddress("glStencilOpSeparate");
    glStencilFuncSeparate_ =      (PFNGLSTENCILFUNCSEPARATEPROC)      getprocaddress("glStencilFuncSeparate");
    glStencilMaskSeparate_ =      (PFNGLSTENCILMASKSEPARATEPROC)      getprocaddress("glStencilMaskSeparate");

    glGenBuffers_ =               (PFNGLGENBUFFERSPROC)               getprocaddress("glGenBuffers");
    glBindBuffer_ =               (PFNGLBINDBUFFERPROC)               getprocaddress("glBindBuffer");
    glMapBuffer_ =                (PFNGLMAPBUFFERPROC)                getprocaddress("glMapBuffer");
    glUnmapBuffer_ =              (PFNGLUNMAPBUFFERPROC)              getprocaddress("glUnmapBuffer");
    glBufferData_ =               (PFNGLBUFFERDATAPROC)               getprocaddress("glBufferData");
    glBufferSubData_ =            (PFNGLBUFFERSUBDATAPROC)            getprocaddress("glBufferSubData");
    glDeleteBuffers_ =            (PFNGLDELETEBUFFERSPROC)            getprocaddress("glDeleteBuffers");
    glGetBufferSubData_ =         (PFNGLGETBUFFERSUBDATAPROC)         getprocaddress("glGetBufferSubData");

    glGetQueryiv_ =               (PFNGLGETQUERYIVPROC)               getprocaddress("glGetQueryiv");
    glGenQueries_ =               (PFNGLGENQUERIESPROC)               getprocaddress("glGenQueries");
    glDeleteQueries_ =            (PFNGLDELETEQUERIESPROC)            getprocaddress("glDeleteQueries");
    glBeginQuery_ =               (PFNGLBEGINQUERYPROC)               getprocaddress("glBeginQuery");
    glEndQuery_ =                 (PFNGLENDQUERYPROC)                 getprocaddress("glEndQuery");
    glGetQueryObjectiv_ =         (PFNGLGETQUERYOBJECTIVPROC)         getprocaddress("glGetQueryObjectiv");
    glGetQueryObjectuiv_ =        (PFNGLGETQUERYOBJECTUIVPROC)        getprocaddress("glGetQueryObjectuiv");

    glCreateProgram_ =            (PFNGLCREATEPROGRAMPROC)            getprocaddress("glCreateProgram");
    glDeleteProgram_ =            (PFNGLDELETEPROGRAMPROC)            getprocaddress("glDeleteProgram");
    glUseProgram_ =               (PFNGLUSEPROGRAMPROC)               getprocaddress("glUseProgram");
    glCreateShader_ =             (PFNGLCREATESHADERPROC)             getprocaddress("glCreateShader");
    glDeleteShader_ =             (PFNGLDELETESHADERPROC)             getprocaddress("glDeleteShader");
    glShaderSource_ =             (PFNGLSHADERSOURCEPROC)             getprocaddress("glShaderSource");
    glCompileShader_ =            (PFNGLCOMPILESHADERPROC)            getprocaddress("glCompileShader");
    glGetShaderiv_ =              (PFNGLGETSHADERIVPROC)              getprocaddress("glGetShaderiv");
    glGetProgramiv_ =             (PFNGLGETPROGRAMIVPROC)             getprocaddress("glGetProgramiv");
    glAttachShader_ =             (PFNGLATTACHSHADERPROC)             getprocaddress("glAttachShader");
    glGetProgramInfoLog_ =        (PFNGLGETPROGRAMINFOLOGPROC)        getprocaddress("glGetProgramInfoLog");
    glGetShaderInfoLog_ =         (PFNGLGETSHADERINFOLOGPROC)         getprocaddress("glGetShaderInfoLog");
    glLinkProgram_ =              (PFNGLLINKPROGRAMPROC)              getprocaddress("glLinkProgram");
    glGetUniformLocation_ =       (PFNGLGETUNIFORMLOCATIONPROC)       getprocaddress("glGetUniformLocation");
    glUniform1f_ =                (PFNGLUNIFORM1FPROC)                getprocaddress("glUniform1f");
    glUniform2f_ =                (PFNGLUNIFORM2FPROC)                getprocaddress("glUniform2f");
    glUniform3f_ =                (PFNGLUNIFORM3FPROC)                getprocaddress("glUniform3f");
    glUniform4f_ =                (PFNGLUNIFORM4FPROC)                getprocaddress("glUniform4f");
    glUniform1fv_ =               (PFNGLUNIFORM1FVPROC)               getprocaddress("glUniform1fv");
    glUniform2fv_ =               (PFNGLUNIFORM2FVPROC)               getprocaddress("glUniform2fv");
    glUniform3fv_ =               (PFNGLUNIFORM3FVPROC)               getprocaddress("glUniform3fv");
    glUniform4fv_ =               (PFNGLUNIFORM4FVPROC)               getprocaddress("glUniform4fv");
    glUniform1i_ =                (PFNGLUNIFORM1IPROC)                getprocaddress("glUniform1i");
    glUniform2i_ =                (PFNGLUNIFORM2IPROC)                getprocaddress("glUniform2i");
    glUniform3i_ =                (PFNGLUNIFORM3IPROC)                getprocaddress("glUniform3i");
    glUniform4i_ =                (PFNGLUNIFORM4IPROC)                getprocaddress("glUniform4i");
    glUniform1iv_ =               (PFNGLUNIFORM1IVPROC)               getprocaddress("glUniform1iv");
    glUniform2iv_ =               (PFNGLUNIFORM2IVPROC)               getprocaddress("glUniform2iv");
    glUniform3iv_ =               (PFNGLUNIFORM3IVPROC)               getprocaddress("glUniform3iv");
    glUniform4iv_ =               (PFNGLUNIFORM4IVPROC)               getprocaddress("glUniform4iv");
    glUniformMatrix2fv_ =         (PFNGLUNIFORMMATRIX2FVPROC)         getprocaddress("glUniformMatrix2fv");
    glUniformMatrix3fv_ =         (PFNGLUNIFORMMATRIX3FVPROC)         getprocaddress("glUniformMatrix3fv");
    glUniformMatrix4fv_ =         (PFNGLUNIFORMMATRIX4FVPROC)         getprocaddress("glUniformMatrix4fv");
    glBindAttribLocation_ =       (PFNGLBINDATTRIBLOCATIONPROC)       getprocaddress("glBindAttribLocation");
    glGetActiveUniform_ =         (PFNGLGETACTIVEUNIFORMPROC)         getprocaddress("glGetActiveUniform");
    glEnableVertexAttribArray_ =  (PFNGLENABLEVERTEXATTRIBARRAYPROC)  getprocaddress("glEnableVertexAttribArray");
    glDisableVertexAttribArray_ = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) getprocaddress("glDisableVertexAttribArray");

    glVertexAttrib1f_ =           (PFNGLVERTEXATTRIB1FPROC)           getprocaddress("glVertexAttrib1f");
    glVertexAttrib1fv_ =          (PFNGLVERTEXATTRIB1FVPROC)          getprocaddress("glVertexAttrib1fv");
    glVertexAttrib1s_ =           (PFNGLVERTEXATTRIB1SPROC)           getprocaddress("glVertexAttrib1s");
    glVertexAttrib1sv_ =          (PFNGLVERTEXATTRIB1SVPROC)          getprocaddress("glVertexAttrib1sv");
    glVertexAttrib2f_ =           (PFNGLVERTEXATTRIB2FPROC)           getprocaddress("glVertexAttrib2f");
    glVertexAttrib2fv_ =          (PFNGLVERTEXATTRIB2FVPROC)          getprocaddress("glVertexAttrib2fv");
    glVertexAttrib2s_ =           (PFNGLVERTEXATTRIB2SPROC)           getprocaddress("glVertexAttrib2s");
    glVertexAttrib2sv_ =          (PFNGLVERTEXATTRIB2SVPROC)          getprocaddress("glVertexAttrib2sv");
    glVertexAttrib3f_ =           (PFNGLVERTEXATTRIB3FPROC)           getprocaddress("glVertexAttrib3f");
    glVertexAttrib3fv_ =          (PFNGLVERTEXATTRIB3FVPROC)          getprocaddress("glVertexAttrib3fv");
    glVertexAttrib3s_ =           (PFNGLVERTEXATTRIB3SPROC)           getprocaddress("glVertexAttrib3s");
    glVertexAttrib3sv_ =          (PFNGLVERTEXATTRIB3SVPROC)          getprocaddress("glVertexAttrib3sv");
    glVertexAttrib4f_ =           (PFNGLVERTEXATTRIB4FPROC)           getprocaddress("glVertexAttrib4f");
    glVertexAttrib4fv_ =          (PFNGLVERTEXATTRIB4FVPROC)          getprocaddress("glVertexAttrib4fv");
    glVertexAttrib4s_ =           (PFNGLVERTEXATTRIB4SPROC)           getprocaddress("glVertexAttrib4s");
    glVertexAttrib4sv_ =          (PFNGLVERTEXATTRIB4SVPROC)          getprocaddress("glVertexAttrib4sv");
    glVertexAttrib4bv_ =          (PFNGLVERTEXATTRIB4BVPROC)          getprocaddress("glVertexAttrib4bv");
    glVertexAttrib4iv_ =          (PFNGLVERTEXATTRIB4IVPROC)          getprocaddress("glVertexAttrib4iv");
    glVertexAttrib4ubv_ =         (PFNGLVERTEXATTRIB4UBVPROC)         getprocaddress("glVertexAttrib4ubv");
    glVertexAttrib4uiv_ =         (PFNGLVERTEXATTRIB4UIVPROC)         getprocaddress("glVertexAttrib4uiv");
    glVertexAttrib4usv_ =         (PFNGLVERTEXATTRIB4USVPROC)         getprocaddress("glVertexAttrib4usv");
    glVertexAttrib4Nbv_ =         (PFNGLVERTEXATTRIB4NBVPROC)         getprocaddress("glVertexAttrib4Nbv");
    glVertexAttrib4Niv_ =         (PFNGLVERTEXATTRIB4NIVPROC)         getprocaddress("glVertexAttrib4Niv");
    glVertexAttrib4Nub_ =         (PFNGLVERTEXATTRIB4NUBPROC)         getprocaddress("glVertexAttrib4Nub");
    glVertexAttrib4Nubv_ =        (PFNGLVERTEXATTRIB4NUBVPROC)        getprocaddress("glVertexAttrib4Nubv");
    glVertexAttrib4Nuiv_ =        (PFNGLVERTEXATTRIB4NUIVPROC)        getprocaddress("glVertexAttrib4Nuiv");
    glVertexAttrib4Nusv_ =        (PFNGLVERTEXATTRIB4NUSVPROC)        getprocaddress("glVertexAttrib4Nusv");
    glVertexAttribPointer_ =      (PFNGLVERTEXATTRIBPOINTERPROC)      getprocaddress("glVertexAttribPointer");

    glUniformMatrix2x3fv_ =       (PFNGLUNIFORMMATRIX2X3FVPROC)       getprocaddress("glUniformMatrix2x3fv");
    glUniformMatrix3x2fv_ =       (PFNGLUNIFORMMATRIX3X2FVPROC)       getprocaddress("glUniformMatrix3x2fv");
    glUniformMatrix2x4fv_ =       (PFNGLUNIFORMMATRIX2X4FVPROC)       getprocaddress("glUniformMatrix2x4fv");
    glUniformMatrix4x2fv_ =       (PFNGLUNIFORMMATRIX4X2FVPROC)       getprocaddress("glUniformMatrix4x2fv");
    glUniformMatrix3x4fv_ =       (PFNGLUNIFORMMATRIX3X4FVPROC)       getprocaddress("glUniformMatrix3x4fv");
    glUniformMatrix4x3fv_ =       (PFNGLUNIFORMMATRIX4X3FVPROC)       getprocaddress("glUniformMatrix4x3fv");

    glDrawBuffers_ =              (PFNGLDRAWBUFFERSPROC)              getprocaddress("glDrawBuffers");
#endif

    if(hasext(exts, "GL_ARB_texture_float") || hasext(exts, "GL_ATI_texture_float"))
    {
        hasTF = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_float extension.");
        shadowmap = 1;
        extern SharedVar<int> smoothshadowmappeel;
        smoothshadowmappeel = 1;
    }

    if(hasext(exts, "GL_ARB_texture_rg"))
    {
        hasTRG = true;
        if(dbgexts) conoutf("\frUsing GL_ARB_texture_rg extension.");
    }

    if(hasext(exts, "GL_NV_float_buffer")) 
    {
        hasNVFB = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_NV_float_buffer extension.");
    }

    if(hasext(exts, "GL_EXT_framebuffer_object"))
    {
        glBindRenderbuffer_        = (PFNGLBINDRENDERBUFFEREXTPROC)       getprocaddress("glBindRenderbufferEXT");
        glDeleteRenderbuffers_     = (PFNGLDELETERENDERBUFFERSEXTPROC)    getprocaddress("glDeleteRenderbuffersEXT");
        glGenRenderbuffers_        = (PFNGLGENFRAMEBUFFERSEXTPROC)        getprocaddress("glGenRenderbuffersEXT");
        glRenderbufferStorage_     = (PFNGLRENDERBUFFERSTORAGEEXTPROC)    getprocaddress("glRenderbufferStorageEXT");
        glCheckFramebufferStatus_  = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) getprocaddress("glCheckFramebufferStatusEXT");
        glBindFramebuffer_         = (PFNGLBINDFRAMEBUFFEREXTPROC)        getprocaddress("glBindFramebufferEXT");
        glDeleteFramebuffers_      = (PFNGLDELETEFRAMEBUFFERSEXTPROC)     getprocaddress("glDeleteFramebuffersEXT");
        glGenFramebuffers_         = (PFNGLGENFRAMEBUFFERSEXTPROC)        getprocaddress("glGenFramebuffersEXT");
        glFramebufferTexture2D_    = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)   getprocaddress("glFramebufferTexture2DEXT");
        glFramebufferRenderbuffer_ = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)getprocaddress("glFramebufferRenderbufferEXT");
        glGenerateMipmap_          = (PFNGLGENERATEMIPMAPEXTPROC)         getprocaddress("glGenerateMipmapEXT");
        hasFBO = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_framebuffer_object extension.");

        if(hasext(exts, "GL_EXT_framebuffer_blit"))
        {
            glBlitFramebuffer_     = (PFNGLBLITFRAMEBUFFEREXTPROC)        getprocaddress("glBlitFramebufferEXT");
            hasFBB = true;
            if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_framebuffer_blit extension.");
        }
    }
    else conoutf(CON_WARN, "WARNING: No framebuffer object support. (reflective water may be slow)");

    extern SharedVar<int> fpdepthfx;
    if(ati)
    {
        //conoutf(CON_WARN, "WARNING: ATI cards may show garbage in skybox. (use \"/ati_skybox_bug 1\" to fix)");

        minimizetcusage = 1;
        if(hasTF && (hasTRG || hasNVFB)) fpdepthfx = 1;
        // On Catalyst 10.2, issuing an occlusion query on the first draw using a given cubemap texture causes a nasty crash
        ati_cubemap_bug = 1;
    }
    else if(nvidia)
    {
        reservevpparams = 10;
        rtsharefb = 0; // work-around for strange driver stalls involving when using many FBOs
        extern SharedVar<int> filltjoints;
        if(glversion < 300 && !hasext(exts, "GL_EXT_gpu_shader4")) filltjoints = 0; // DX9 or less NV cards seem to not cause many sparklies

        if(hasTF) fpdepthfx = 1;
    }
    else
    {
        if(intel)
        {
#ifdef __APPLE__
            intel_immediate_bug = 1;
#endif
#ifdef WIN32
            intel_immediate_bug = 1;
            //intel_vertexarray_bug = 1;
#endif
        }

        reservevpparams = 20;
    }

    if(hasext(exts, "GL_ARB_map_buffer_range"))
    {
        glMapBufferRange_         = (PFNGLMAPBUFFERRANGEPROC)        getprocaddress("glMapBufferRange");
        glFlushMappedBufferRange_ = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)getprocaddress("glFlushMappedBufferRange");
        hasMBR = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_map_buffer_range.");
    }

    if(hasext(exts, "GL_ARB_uniform_buffer_object"))
    {
        glGetUniformIndices_       = (PFNGLGETUNIFORMINDICESPROC)      getprocaddress("glGetUniformIndices");
        glGetActiveUniformsiv_     = (PFNGLGETACTIVEUNIFORMSIVPROC)    getprocaddress("glGetActiveUniformsiv");
        glGetUniformBlockIndex_    = (PFNGLGETUNIFORMBLOCKINDEXPROC)   getprocaddress("glGetUniformBlockIndex");
        glGetActiveUniformBlockiv_ = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)getprocaddress("glGetActiveUniformBlockiv");
        glUniformBlockBinding_     = (PFNGLUNIFORMBLOCKBINDINGPROC)    getprocaddress("glUniformBlockBinding");
        glBindBufferBase_          = (PFNGLBINDBUFFERBASEPROC)         getprocaddress("glBindBufferBase");
        glBindBufferRange_         = (PFNGLBINDBUFFERRANGEPROC)        getprocaddress("glBindBufferRange");

        useubo = 1;
        hasUBO = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_uniform_buffer_object extension.");
    }

    if(hasext(exts, "GL_EXT_texture_rectangle") || hasext(exts, "GL_ARB_texture_rectangle"))
    {
        usetexrect = 1;
        hasTR = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_rectangle extension.");
    }
    else conoutf(CON_WARN, "WARNING: No texture rectangle support. (no full screen shaders)");

    if(hasext(exts, "GL_EXT_packed_depth_stencil") || hasext(exts, "GL_NV_packed_depth_stencil"))
    {
        hasDS = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_packed_depth_stencil extension.");
    }

    if(hasext(exts, "GL_EXT_texture_compression_s3tc"))
    {
        hasS3TC = true;
#ifdef __APPLE__
        usetexcompress = 1;
#else
        if(!mesa) usetexcompress = 2;
#endif
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_compression_s3tc extension.");
    }
    else if(hasext(exts, "GL_EXT_texture_compression_dxt1") && hasext(exts, "GL_ANGLE_texture_compression_dxt3") && hasext(exts, "GL_ANGLE_texture_compression_dxt5"))
    {
        hasS3TC = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_compression_dxt1 extension.");
    }
    if(hasext(exts, "GL_3DFX_texture_compression_FXT1"))
    {
        hasFXT1 = true;
        if(mesa) usetexcompress = max(usetexcompress, 1);
        if(dbgexts) conoutf(CON_INIT, "Using GL_3DFX_texture_compression_FXT1.");
    }

    if(hasext(exts, "GL_EXT_texture_filter_anisotropic"))
    {
        GLint val;
        glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &val);
        hwmaxaniso = val;
        hasAF = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_filter_anisotropic extension.");
    }

    if(glversion >= 300 || hasext(exts, "GL_EXT_gpu_shader4"))
    {
        // on DX10 or above class cards (i.e. GF8 or RadeonHD) enable expensive features
        extern SharedVar<int> grass, glare, maxdynlights, depthfxsize, depthfxrect, depthfxfilter, blurdepthfx;
        grass = 1;
        waterfallrefract = 1;
        glare = 1;
        maxdynlights = MAXDYNLIGHTS;
        if(hasTR)
        {
            depthfxsize = 10;
            depthfxrect = 1;
            depthfxfilter = 0;
            blurdepthfx = 0;
        }
    }
}

void glext(char *ext)
{
    const char *exts = (const char *)glGetString(GL_EXTENSIONS);
    intret(hasext(exts, ext) ? 1 : 0);
}
COMMAND(glext, "s");

void gl_resize()
{
    glViewport(0, 0, screenw, screenh);
}
 
void gl_init(int depth, int fsaa)
{
    gl_resize();
    glClearColor(0, 0, 0, 0);
    glClearDepth(1);
    glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    
    glDisable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    //glHint(GL_FOG_HINT, GL_NICEST);
    GLfloat fogcolor[4] = { 0, 0, 0, 0 };
    glFogfv(GL_FOG_COLOR, fogcolor);
    

    glEnable(GL_LINE_SMOOTH);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);

#ifdef __APPLE__
    if(sdl_backingstore_bug)
    {
        if(fsaa)
        {
            sdl_backingstore_bug = 1;
            // since SDL doesn't add kCGLPFABackingStore to the pixelformat and so it isn't guaranteed to be preserved - only manifests when using fsaa?
            //conoutf(CON_WARN, "WARNING: Using SDL backingstore workaround. (use \"/sdl_backingstore_bug 0\" to disable if unnecessary)");
        }
        else sdl_backingstore_bug = -1;
    }
#endif

    extern void setupshaders();
    setupshaders();

    setuptexcompress();
}

void cleanupgl()
{
    extern void cleanupmotionblur();
    cleanupmotionblur();

    extern void clearminimap();
    clearminimap();
}

#define VARRAY_INTERNAL
#include "varray.h"

VAR(wireframe, 0, 0, 1);

ICOMMAND(getcamyaw, "", (), floatret(camera1->yaw));
ICOMMAND(getcampitch, "", (), floatret(camera1->pitch));
ICOMMAND(getcamroll, "", (), floatret(camera1->roll));
ICOMMAND(getcampos, "", (), 
{
    defformatstring(pos)("%s %s %s", floatstr(camera1->o.x), floatstr(camera1->o.y), floatstr(camera1->o.z));
    result(pos);
});

vec worldpos, camdir, camright, camup;

void findorientation()
{
    mvmatrix.transposedtransformnormal(vec(viewmatrix.getcolumn(1)), camdir);
    mvmatrix.transposedtransformnormal(vec(viewmatrix.getcolumn(0)).neg(), camright);
    mvmatrix.transposedtransformnormal(vec(viewmatrix.getcolumn(2)), camup);

    if(raycubepos(camera1->o, camdir, worldpos, 0, RAY_CLIPMAT|RAY_SKIPFIRST) == -1)
        worldpos = vec(camdir).mul(2*worldsize).add(camera1->o); //otherwise 3dgui won't work when outside of map
}

void transplayer()
{
    // move from RH to Z-up LH quake style worldspace
    glLoadMatrixf(viewmatrix.v);

    glRotatef(camera1->roll, 0, 1, 0);
    glRotatef(camera1->pitch, -1, 0, 0);
    glRotatef(camera1->yaw, 0, 0, -1);

    glTranslatef(-camera1->o.x, -camera1->o.y, -camera1->o.z);   
}

float curfov = 100, curavatarfov = 65, fovy, aspect;
int farplane;
VARP(zoominvel, 0, 250, 5000);
VARP(zoomoutvel, 0, 100, 5000);
VARP(zoomfov, 10, 35, 150);
VARP(fov, 10, 100, 150);
VAR(avatarzoomfov, 10, 25, 60);
VAR(avatarfov, 10, 65, 150);
FVAR(avatardepth, 0, 0.5f, 1);
FVARNP(aspect, forceaspect, 0, 0, 1e3f);

static float zoomprogress = 0;
VAR(zoom, -1, 0, 1);

void disablezoom()
{
    zoom = 0;
    zoomprogress = 0;
}

void computezoom()
{
    if(!zoom) { zoomprogress = 0; curfov = fov; curavatarfov = avatarfov; return; }
    if(zoom > 0) zoomprogress = zoominvel ? min(zoomprogress + float(elapsedtime) / zoominvel, 1.0f) : 1;
    else
    {
        zoomprogress = zoomoutvel ? max(zoomprogress - float(elapsedtime) / zoomoutvel, 0.0f) : 0;
        if(zoomprogress <= 0) zoom = 0;
    }
    curfov = zoomfov*zoomprogress + fov*(1 - zoomprogress);
    curavatarfov = avatarzoomfov*zoomprogress + avatarfov*(1 - zoomprogress);
}

FVARP(zoomsens, 1e-3f, 1, 1000);
FVARP(zoomaccel, 0, 0, 1000);
VARP(zoomautosens, 0, 1, 1);
FVARP(sensitivity, 1e-3f, 3, 1000);
FVARP(sensitivityscale, 1e-3f, 1, 1000);
VARP(invmouse, 0, 0, 1);
FVARP(mouseaccel, 0, 0, 1000);
 
VAR(thirdperson, 0, 0, 2);
FVAR(thirdpersondistance, 0, 20, 50);
FVAR(thirdpersonup, -25, 0, 25);
FVAR(thirdpersonside, -25, 0, 25);
physent *camera1 = NULL;
bool detachedcamera = false;
bool isthirdperson() { return player!=camera1 || detachedcamera || reflecting; }

void fixcamerarange()
{
    const float MAXPITCH = 90.0f;
    if(camera1->pitch>MAXPITCH) camera1->pitch = MAXPITCH;
    if(camera1->pitch<-MAXPITCH) camera1->pitch = -MAXPITCH;
    while(camera1->yaw<0.0f) camera1->yaw += 360.0f;
    while(camera1->yaw>=360.0f) camera1->yaw -= 360.0f;
}

void mousemove(int dx, int dy)
{
    if(!game::allowmouselook()) return;
    float cursens = sensitivity, curaccel = mouseaccel;
    if(zoom)
    {
        if(zoomautosens) 
        {
            cursens = float(sensitivity*zoomfov)/fov;
            curaccel = float(mouseaccel*zoomfov)/fov;
        }
        else 
        {
            cursens = zoomsens;
            curaccel = zoomaccel;
        }
    }
    if(curaccel && curtime && (dx || dy)) cursens += curaccel * sqrtf(dx*dx + dy*dy)/curtime;
    cursens /= 33.0f*sensitivityscale;
    camera1->yaw += dx*cursens;
    camera1->pitch -= dy*cursens*(invmouse ? -1 : 1);
    fixcamerarange();
    if(camera1!=player && !detachedcamera)
    {
        player->yaw = camera1->yaw;
        player->pitch = camera1->pitch;
    }
}

void recomputecamera()
{
    game::setupcamera();
    computezoom();

    bool shoulddetach = thirdperson > 1 || game::detachcamera();
    if(!thirdperson && !shoulddetach)
    {
        camera1 = player;
        detachedcamera = false;
    }
    else
    {
        static physent tempcamera;
        camera1 = &tempcamera;
        if(detachedcamera && shoulddetach) camera1->o = player->o;
        else
        {
            *camera1 = *player;
            detachedcamera = shoulddetach;
        }
        camera1->reset();
        camera1->type = ENT_CAMERA;
        camera1->move = -1;
        camera1->eyeheight = camera1->aboveeye = camera1->radius = camera1->xradius = camera1->yradius = 2;
       
        matrix3x3 orient;
        orient.identity();
        orient.rotate_around_y(camera1->roll*RAD);
        orient.rotate_around_x(camera1->pitch*-RAD);
        orient.rotate_around_z(camera1->yaw*-RAD);
        vec dir = vec(orient.b).neg(), side = vec(orient.a).neg(), up = orient.c;

        if(game::collidecamera()) 
        {
            movecamera(camera1, dir, thirdpersondistance, 1);
            movecamera(camera1, dir, clamp(thirdpersondistance - camera1->o.dist(player->o), 0.0f, 1.0f), 0.1f);
            if(thirdpersonup)
            {
                vec pos = camera1->o;
                float dist = fabs(thirdpersonup);
                if(thirdpersonup < 0) up.neg();
                movecamera(camera1, up, dist, 1);
                movecamera(camera1, up, clamp(dist - camera1->o.dist(pos), 0.0f, 1.0f), 0.1f);
            }
            if(thirdpersonside)
            {
                vec pos = camera1->o;
                float dist = fabs(thirdpersonside);
                if(thirdpersonside < 0) side.neg();
                movecamera(camera1, side, dist, 1);
                movecamera(camera1, side, clamp(dist - camera1->o.dist(pos), 0.0f, 1.0f), 0.1f);
            }
        }
        else 
        {
            camera1->o.add(vec(dir).mul(thirdpersondistance));
            if(thirdpersonup) camera1->o.add(vec(up).mul(thirdpersonup));
            if(thirdpersonside) camera1->o.add(vec(side).mul(thirdpersonside));
        }
    }

    setviewcell(camera1->o);
}

extern const glmatrixf viewmatrix(vec4(-1, 0, 0, 0), vec4(0, 0, 1, 0), vec4(0, -1, 0, 0));
glmatrixf mvmatrix, projmatrix, mvpmatrix, invmvmatrix, invmvpmatrix;

void readmatrices()
{
    glGetFloatv(GL_MODELVIEW_MATRIX, mvmatrix.v);
    glGetFloatv(GL_PROJECTION_MATRIX, projmatrix.v);

    mvpmatrix.mul(projmatrix, mvmatrix);
    invmvmatrix.invert(mvmatrix);
    invmvpmatrix.invert(mvpmatrix);
}

FVAR(nearplane, 0.01f, 0.54f, 2.0f);

void project(float fovy, float aspect, int farplane, bool flipx = false, bool flipy = false, bool swapxy = false, float zscale = 1)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(swapxy) glRotatef(90, 0, 0, 1);
    if(flipx || flipy!=swapxy || zscale!=1) glScalef(flipx ? -1 : 1, flipy!=swapxy ? -1 : 1, zscale);
    GLdouble ydist = nearplane * tan(fovy/2*RAD), xdist = ydist * aspect;
    glFrustum(-xdist, xdist, -ydist, ydist, nearplane, farplane);
    glMatrixMode(GL_MODELVIEW);
}

vec calcavatarpos(const vec &pos, float dist)
{
    vec eyepos;
    mvmatrix.transform(pos, eyepos);
    GLdouble ydist = nearplane * tan(curavatarfov/2*RAD), xdist = ydist * aspect;
    vec4 scrpos;
    scrpos.x = eyepos.x*nearplane/xdist;
    scrpos.y = eyepos.y*nearplane/ydist;
    scrpos.z = (eyepos.z*(farplane + nearplane) - 2*nearplane*farplane) / (farplane - nearplane);
    scrpos.w = -eyepos.z;

    vec worldpos = invmvpmatrix.perspectivetransform(scrpos);
    vec dir = vec(worldpos).sub(camera1->o).rescale(dist);
    return dir.add(camera1->o);
}

VAR(reflectclip, 0, 6, 64);
VAR(reflectclipavatar, -64, 0, 64);

glmatrixf clipmatrix;

static const glmatrixf dummymatrix;
static int projectioncount = 0;
void pushprojection(const glmatrixf &m = dummymatrix)
{
    glMatrixMode(GL_PROJECTION);
    if(projectioncount <= 0) glPushMatrix();
    if(&m != &dummymatrix) glLoadMatrixf(m.v);
    if(fogging)
    {
        glMultMatrixf(mvmatrix.v);
        glMultMatrixf(invfogmatrix.v);
    }
    glMatrixMode(GL_MODELVIEW);
    projectioncount++;
}

void popprojection()
{
    --projectioncount;
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    if(projectioncount > 0)
    {
        glPushMatrix();
        if(fogging)
        {
            glMultMatrixf(mvmatrix.v);
            glMultMatrixf(invfogmatrix.v);
        }
    }
    glMatrixMode(GL_MODELVIEW);
}

FVAR(polygonoffsetfactor, -1e4f, -3.0f, 1e4f);
FVAR(polygonoffsetunits, -1e4f, -3.0f, 1e4f);
FVAR(depthoffset, -1e4f, 0.01f, 1e4f);

void enablepolygonoffset(GLenum type)
{
    if(!depthoffset)
    {
        glPolygonOffset(polygonoffsetfactor, polygonoffsetunits);
        glEnable(type);
        return;
    }
    
    bool clipped = reflectz < 1e15f && reflectclip;

    glmatrixf offsetmatrix = clipped ? clipmatrix : projmatrix;
    offsetmatrix[14] += depthoffset * projmatrix[10];

    glMatrixMode(GL_PROJECTION);
    if(!clipped) glPushMatrix();
    glLoadMatrixf(offsetmatrix.v);
    if(fogging)
    {
        glMultMatrixf(mvmatrix.v);
        glMultMatrixf(invfogmatrix.v);
    }
    glMatrixMode(GL_MODELVIEW);
}

void disablepolygonoffset(GLenum type)
{
    if(!depthoffset)
    {
        glDisable(type);
        return;
    }
    
    bool clipped = reflectz < 1e15f && reflectclip;

    glMatrixMode(GL_PROJECTION);
    if(clipped) 
    {
        glLoadMatrixf(clipmatrix.v);
        if(fogging)
        {
            glMultMatrixf(mvmatrix.v);
            glMultMatrixf(invfogmatrix.v);
        }
    }
    else glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void calcspherescissor(const vec &center, float size, float &sx1, float &sy1, float &sx2, float &sy2)
{
    vec worldpos(center);
    if(reflecting) worldpos.z = 2*reflectz - worldpos.z; 
    vec e(mvmatrix.transformx(worldpos),
          mvmatrix.transformy(worldpos),
          mvmatrix.transformz(worldpos));
    if(e.z > 2*size) { sx1 = sy1 = 1; sx2 = sy2 = -1; return; }
    float zzrr = e.z*e.z - size*size,
          dx = e.x*e.x + zzrr, dy = e.y*e.y + zzrr,
          focaldist = 1.0f/tan(fovy*0.5f*RAD);
    sx1 = sy1 = -1;
    sx2 = sy2 = 1;
    #define CHECKPLANE(c, dir, focaldist, low, high) \
    do { \
        float nzc = (cz*cz + 1) / (cz dir drt) - cz, \
              pz = (d##c)/(nzc*e.c - e.z); \
        if(pz > 0) \
        { \
            float c = (focaldist)*nzc, \
                  pc = pz*nzc; \
            if(pc < e.c) low = c; \
            else if(pc > e.c) high = c; \
        } \
    } while(0)
    if(dx > 0)
    {
        float cz = e.x/e.z, drt = sqrtf(dx)/size;
        CHECKPLANE(x, -, focaldist/aspect, sx1, sx2);
        CHECKPLANE(x, +, focaldist/aspect, sx1, sx2);
    }
    if(dy > 0)
    {
        float cz = e.y/e.z, drt = sqrtf(dy)/size;
        CHECKPLANE(y, -, focaldist, sy1, sy2);
        CHECKPLANE(y, +, focaldist, sy1, sy2);
    }
}

static int scissoring = 0;
static GLint oldscissor[4];

int pushscissor(float sx1, float sy1, float sx2, float sy2)
{
    scissoring = 0;

    if(sx1 <= -1 && sy1 <= -1 && sx2 >= 1 && sy2 >= 1) return 0;

    sx1 = max(sx1, -1.0f);
    sy1 = max(sy1, -1.0f);
    sx2 = min(sx2, 1.0f);
    sy2 = min(sy2, 1.0f);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int sx = viewport[0] + int(floor((sx1+1)*0.5f*viewport[2])),
        sy = viewport[1] + int(floor((sy1+1)*0.5f*viewport[3])),
        sw = viewport[0] + int(ceil((sx2+1)*0.5f*viewport[2])) - sx,
        sh = viewport[1] + int(ceil((sy2+1)*0.5f*viewport[3])) - sy;
    if(sw <= 0 || sh <= 0) return 0;

    if(glIsEnabled(GL_SCISSOR_TEST))
    {
        glGetIntegerv(GL_SCISSOR_BOX, oldscissor);
        sw += sx;
        sh += sy;
        sx = max(sx, int(oldscissor[0]));
        sy = max(sy, int(oldscissor[1]));
        sw = min(sw, int(oldscissor[0] + oldscissor[2])) - sx;
        sh = min(sh, int(oldscissor[1] + oldscissor[3])) - sy;
        if(sw <= 0 || sh <= 0) return 0;
        scissoring = 2;
    }
    else scissoring = 1;

    glScissor(sx, sy, sw, sh);
    if(scissoring<=1) glEnable(GL_SCISSOR_TEST);
    
    return scissoring;
}

void popscissor()
{
    if(scissoring>1) glScissor(oldscissor[0], oldscissor[1], oldscissor[2], oldscissor[3]);
    else if(scissoring) glDisable(GL_SCISSOR_TEST);
    scissoring = 0;
}

glmatrixf envmatrix;

void setenvmatrix()
{
    envmatrix = fogging ? fogmatrix : mvmatrix;
    if(reflecting) envmatrix.reflectz(reflectz);
    envmatrix.transpose();
}

VARR(fog, 16, 4000, 1000024);
bvec fogcolor(0x80, 0x99, 0xB3);
HVARFR(fogcolour, 0, 0x8099B3, 0xFFFFFF,
{
    fogcolor = bvec((fogcolour>>16)&0xFF, (fogcolour>>8)&0xFF, fogcolour&0xFF);
});

static float findsurface(int fogmat, const vec &v, int &abovemat)
{
    fogmat &= MATF_VOLUME;
    ivec o(v), co;
    int csize;
    do
    {
        cube &c = lookupcube(o.x, o.y, o.z, 0, co, csize);
        int mat = c.material&MATF_VOLUME;
        if(mat != fogmat)
        {
            abovemat = isliquid(mat) ? c.material : MAT_AIR;
            return o.z;
        }
        o.z = co.z + csize;
    }
    while(o.z < worldsize);
    abovemat = MAT_AIR;
    return worldsize;
}

static void blendfog(int fogmat, float blend, float logblend, float &start, float &end, float *fogc)
{
    switch(fogmat&MATF_VOLUME)
    {
        case MAT_WATER:
        {
            const bvec &wcol = getwatercolor(fogmat);
            int wfog = getwaterfog(fogmat);
            loopk(3) fogc[k] += blend*wcol[k]/255.0f;
            end += logblend*min(fog, max(wfog*4, 32));
            break;
        }

        case MAT_LAVA:
        {
            const bvec &lcol = getlavacolor(fogmat);
            int lfog = getlavafog(fogmat);
            loopk(3) fogc[k] += blend*lcol[k]/255.0f;
            end += logblend*min(fog, max(lfog*4, 32));
            break;
        }

        default:
            loopk(3) fogc[k] += blend*fogcolor[k]/255.0f;
            start += logblend*(fog+64)/8;
            end += logblend*fog;
            break;
    }
}

static void setfog(int fogmat, float below = 1, int abovemat = MAT_AIR)
{
    float fogc[4] = { 0, 0, 0, 1 };
    float start = 0, end = 0;
    float logscale = 256, logblend = log(1 + (logscale - 1)*below) / log(logscale);

    blendfog(fogmat, below, logblend, start, end, fogc);
    if(below < 1) blendfog(abovemat, 1-below, 1-logblend, start, end, fogc);

    glFogf(GL_FOG_START, start);
    glFogf(GL_FOG_END, end);
    glFogfv(GL_FOG_COLOR, fogc);
    glClearColor(fogc[0], fogc[1], fogc[2], 1.0f);
}

static void blendfogoverlay(int fogmat, float blend, float *overlay)
{
    float maxc;
    switch(fogmat&MATF_VOLUME)
    {
        case MAT_WATER:
        {
            const bvec &wcol = getwatercolor(fogmat);
            maxc = max(wcol[0], max(wcol[1], wcol[2]));
            loopk(3) overlay[k] += blend*max(0.4f, wcol[k]/min(32.0f + maxc*7.0f/8.0f, 255.0f));
            break;
        }

        case MAT_LAVA:
        {
            const bvec &lcol = getlavacolor(fogmat);
            maxc = max(lcol[0], max(lcol[1], lcol[2]));
            loopk(3) overlay[k] += blend*max(0.4f, lcol[k]/min(32.0f + maxc*7.0f/8.0f, 255.0f));
            break;
        }

        default:
            loopk(3) overlay[k] += blend;
            break;
    }
}

void drawfogoverlay(int fogmat, float fogblend, int abovemat)
{
    notextureshader->set();

    glEnable(GL_BLEND);
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    float overlay[3] = { 0, 0, 0 };
    blendfogoverlay(fogmat, fogblend, overlay);
    blendfogoverlay(abovemat, 1-fogblend, overlay);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3fv(overlay);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glEnd();
    glDisable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    defaultshader->set();
}

bool renderedgame = false;

void rendergame(bool mainpass)
{
    game::rendergame(mainpass);
    if(!shadowmapping) renderedgame = true;
}

VARP(skyboxglare, 0, 1, 1);

void drawglare()
{
    glaring = true;
    refracting = -1;

    float oldfogstart, oldfogend, oldfogcolor[4], zerofog[4] = { 0, 0, 0, 1 };
    glGetFloatv(GL_FOG_START, &oldfogstart);
    glGetFloatv(GL_FOG_END, &oldfogend);
    glGetFloatv(GL_FOG_COLOR, oldfogcolor);

    glFogf(GL_FOG_START, (fog+64)/8);
    glFogf(GL_FOG_END, fog);
    glFogfv(GL_FOG_COLOR, zerofog);

    glClearColor(0, 0, 0, 1);
    glClear((skyboxglare ? 0 : GL_COLOR_BUFFER_BIT) | GL_DEPTH_BUFFER_BIT);

    rendergeom();

    if(skyboxglare) drawskybox(farplane, false);

    renderreflectedmapmodels();
    rendergame();
    if(!isthirdperson())
    {
        project(curavatarfov, aspect, farplane, false, false, false, avatardepth);
        game::renderavatar();
        project(fovy, aspect, farplane);
    }

    renderwater();
    rendermaterials();
    renderalphageom();
    renderparticles();

    glFogf(GL_FOG_START, oldfogstart);
    glFogf(GL_FOG_END, oldfogend);
    glFogfv(GL_FOG_COLOR, oldfogcolor);

    refracting = 0;
    glaring = false;
}

VARP(reflectmms, 0, 1, 1);
VARR(refractsky, 0, 0, 1);

glmatrixf fogmatrix, invfogmatrix;

void drawreflection(float z, bool refract, int fogdepth, const bvec &col)
{
    reflectz = z < 0 ? 1e16f : z;
    reflecting = !refract;
    refracting = refract ? (z < 0 || camera1->o.z >= z ? -1 : 1) : 0;
    fading = waterrefract && waterfade && hasFBO && z>=0;
    fogging = refracting<0 && z>=0;
    refractfog = fogdepth;
    refractcolor = fogging ? col : fogcolor;

    float oldfogstart, oldfogend, oldfogcolor[4];
    glGetFloatv(GL_FOG_START, &oldfogstart);
    glGetFloatv(GL_FOG_END, &oldfogend);
    glGetFloatv(GL_FOG_COLOR, oldfogcolor);

    if(fogging)
    {
        glFogf(GL_FOG_START, camera1->o.z - z);
        glFogf(GL_FOG_END, camera1->o.z - (z-max(refractfog, 1)));
        GLfloat m[16] =
        {
             1,   0,  0, 0,
             0,   1,  0, 0,
             0,   0,  1, 0,
            -camera1->o.x, -camera1->o.y, -camera1->o.z, 1
        };
        memcpy(fogmatrix.v, m, sizeof(m));
        invfogmatrix.invert(fogmatrix);
        pushprojection();
        glPushMatrix();
        glLoadMatrixf(fogmatrix.v);
        float fogc[4] = { col.x/255.0f, col.y/255.0f, col.z/255.0f, 1.0f };
        glFogfv(GL_FOG_COLOR, fogc);
    }
    else
    {
        glFogf(GL_FOG_START, (fog+64)/8);
        glFogf(GL_FOG_END, fog);
        float fogc[4] = { fogcolor.x/255.0f, fogcolor.y/255.0f, fogcolor.z/255.0f, 1.0f };
        glFogfv(GL_FOG_COLOR, fogc);
    }

    if(fading)
    {
        float scale = fogging ? -0.25f : 0.25f, offset = 2*fabs(scale) - scale*z;
        GLOBALPARAMF(waterfadeparams, scale, offset, -scale, offset + camera1->o.z*scale);
    }

    if(reflecting)
    {
        glPushMatrix();
        glTranslatef(0, 0, 2*z);
        glScalef(1, 1, -1);

        glFrontFace(GL_CCW);
    }

    setenvmatrix();

    if(reflectclip && z>=0)
    {
        float zoffset = reflectclip/4.0f, zclip;
        if(refracting<0)
        {
            zclip = z+zoffset;
            if(camera1->o.z<=zclip) zclip = z;
        }
        else
        {
            zclip = z-zoffset;
            if(camera1->o.z>=zclip && camera1->o.z<=z+4.0f) zclip = z;
            if(reflecting) zclip = 2*z - zclip;
        }
        plane clipplane;
        invmvmatrix.transposedtransform(plane(0, 0, refracting>0 ? 1 : -1, refracting>0 ? -zclip : zclip), clipplane);
        clipmatrix.clip(clipplane, projmatrix);
        pushprojection(clipmatrix);
    }

    renderreflectedgeom(refracting<0 && z>=0 && caustics, fogging);

    if(reflecting || refracting>0 || (refracting<0 && refractsky) || z<0)
    {
        if(fading) glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        if(reflectclip && z>=0) popprojection();
        if(fogging) 
        {
            popprojection();
            glPopMatrix();
        }
        drawskybox(farplane, false);
        if(fogging) 
        {
            pushprojection();
            glPushMatrix();
            glLoadMatrixf(fogmatrix.v);
        }
        if(reflectclip && z>=0) pushprojection(clipmatrix);
        if(fading) glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
    }
    else if(fading) glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);

    renderdecals();

    if(reflectmms) renderreflectedmapmodels();
    rendergame();

    if(refracting && z>=0 && !isthirdperson() && fabs(camera1->o.z-z) <= 0.5f*(player->eyeheight + player->aboveeye))
    {   
        glmatrixf avatarproj;
        avatarproj.perspective(curavatarfov, aspect, nearplane, farplane);
        if(reflectclip)
        {
            popprojection();
            glmatrixf avatarclip;
            plane clipplane;
            invmvmatrix.transposedtransform(plane(0, 0, refracting, reflectclipavatar/4.0f - refracting*z), clipplane);
            avatarclip.clip(clipplane, avatarproj);
            pushprojection(avatarclip);
        }
        else pushprojection(avatarproj);
        game::renderavatar();
        popprojection();
        if(reflectclip) pushprojection(clipmatrix);
    }

    if(refracting) rendergrass();
    rendermaterials();
    renderalphageom(fogging);
    renderparticles();

    if(fading) glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    if(reflectclip && z>=0) popprojection();

    if(reflecting)
    {
        glPopMatrix();

        glFrontFace(GL_CW);
    }

    if(fogging) 
    {
        popprojection();
        glPopMatrix();
    }
    glFogf(GL_FOG_START, oldfogstart);
    glFogf(GL_FOG_END, oldfogend);
    glFogfv(GL_FOG_COLOR, oldfogcolor);
    
    reflectz = 1e16f;
    refracting = 0;
    reflecting = fading = fogging = false;

    setenvmatrix();
}

bool envmapping = false;

void drawcubemap(int size, const vec &o, float yaw, float pitch, const cubemapside &side)
{
    envmapping = true;

    physent *oldcamera = camera1;
    static physent cmcamera;
    cmcamera = *player;
    cmcamera.reset();
    cmcamera.type = ENT_CAMERA;
    cmcamera.o = o;
    cmcamera.yaw = yaw;
    cmcamera.pitch = pitch;
    cmcamera.roll = 0;
    camera1 = &cmcamera;
    setviewcell(camera1->o);
   
    defaultshader->set();

    int fogmat = lookupmaterial(o)&(MATF_VOLUME|MATF_INDEX);

    setfog(fogmat);

    glClear(GL_DEPTH_BUFFER_BIT);

    int farplane = worldsize*2;

    project(90.0f, 1.0f, farplane, !side.flipx, !side.flipy, side.swapxy);

    transplayer();
    readmatrices();
    findorientation();
    setenvmatrix();

    glEnable(GL_FOG);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    xtravertsva = xtraverts = glde = gbatches = 0;

    visiblecubes();

    if(limitsky()) drawskybox(farplane, true);

    rendergeom();

    if(!limitsky()) drawskybox(farplane, false);

//    queryreflections();

    rendermapmodels();
    renderalphageom();

//    drawreflections();

//    renderwater();
//    rendermaterials();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_FOG);

    camera1 = oldcamera;
    envmapping = false;
}

bool modelpreviewing = false;

namespace modelpreview
{
    physent *oldcamera;
    float oldfogstart, oldfogend, oldfogcolor[4]; 

    physent camera;

    void start(bool background)
    {
        float fovy = 90.f, aspect = 1.f;
        envmapping = modelpreviewing = true;

        oldcamera = camera1;
        camera = *camera1;
        camera.reset();
        camera.type = ENT_CAMERA;
        camera.o = vec(0, 0, 0);
        camera.yaw = 0;
        camera.pitch = 0;
        camera.roll = 0;
        camera1 = &camera;

        glGetFloatv(GL_FOG_START, &oldfogstart);
        glGetFloatv(GL_FOG_END, &oldfogend);
        glGetFloatv(GL_FOG_COLOR, oldfogcolor);

        GLfloat fogc[4] = { 0, 0, 0, 1 };
        glFogf(GL_FOG_START, 0);
        glFogf(GL_FOG_END, 1000000);
        glFogfv(GL_FOG_COLOR, fogc);
        glClearColor(fogc[0], fogc[1], fogc[2], fogc[3]);

        glClear((background ? GL_COLOR_BUFFER_BIT : 0) | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        project(fovy, aspect, 1024);
        transplayer();
        readmatrices();
        setenvmatrix();

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    }

    void end()
    {
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        defaultshader->set();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glFogf(GL_FOG_START, oldfogstart);
        glFogf(GL_FOG_END, oldfogend);
        glFogfv(GL_FOG_COLOR, oldfogcolor);
        glClearColor(oldfogcolor[0], oldfogcolor[1], oldfogcolor[2], oldfogcolor[3]);

        camera1 = oldcamera;
        envmapping = modelpreviewing = false;
    }
}

bool minimapping = false;

GLuint minimaptex = 0;
vec minimapcenter(0, 0, 0), minimapradius(0, 0, 0), minimapscale(0, 0, 0);

void clearminimap()
{
    if(minimaptex) { glDeleteTextures(1, &minimaptex); minimaptex = 0; }
}

VARR(minimapheight, 0, 0, 2<<16);
bvec minimapcolor(0, 0, 0);
HVARFR(minimapcolour, 0, 0, 0xFFFFFF,
{
    minimapcolor = bvec((minimapcolour>>16)&0xFF, (minimapcolour>>8)&0xFF, minimapcolour&0xFF);
});
VARR(minimapclip, 0, 0, 1);
VARFP(minimapsize, 7, 8, 10, { if(minimaptex) drawminimap(); });

void bindminimap()
{
    glBindTexture(GL_TEXTURE_2D, minimaptex);
}

void clipminimap(ivec &bbmin, ivec &bbmax, cube *c = worldroot, int x = 0, int y = 0, int z = 0, int size = worldsize>>1)
{
    loopi(8)
    {
        ivec o(i, x, y, z, size);
        if(c[i].children) clipminimap(bbmin, bbmax, c[i].children, o.x, o.y, o.z, size>>1);
        else if(!isentirelysolid(c[i]) && (c[i].material&MATF_CLIP)!=MAT_CLIP)
        {
            loopk(3) bbmin[k] = min(bbmin[k], o[k]);
            loopk(3) bbmax[k] = max(bbmax[k], o[k] + size);
        }
    }
}

void drawminimap()
{
    if(!game::needminimap()) { clearminimap(); return; }

    renderprogress(0, "generating mini-map...", 0, !renderedframe);

    int size = 1<<minimapsize, sizelimit = min(hwtexsize, min(screenw, screenh));
    while(size > sizelimit) size /= 2;
    if(!minimaptex) glGenTextures(1, &minimaptex);

    extern vector<vtxarray *> valist;
    ivec bbmin(worldsize, worldsize, worldsize), bbmax(0, 0, 0);
    loopv(valist)
    {
        vtxarray *va = valist[i];
        loopk(3)
        {
            if(va->geommin[k]>va->geommax[k]) continue;
            bbmin[k] = min(bbmin[k], va->geommin[k]);
            bbmax[k] = max(bbmax[k], va->geommax[k]);
        }
    }
    if(minimapclip)
    {
        ivec clipmin(worldsize, worldsize, worldsize), clipmax(0, 0, 0);
        clipminimap(clipmin, clipmax);
        loopk(2) bbmin[k] = max(bbmin[k], clipmin[k]);
        loopk(2) bbmax[k] = min(bbmax[k], clipmax[k]); 
    }
 
    minimapradius = vec(bbmax).sub(vec(bbmin)).mul(0.5f); 
    minimapcenter = vec(bbmin).add(minimapradius);
    minimapradius.x = minimapradius.y = max(minimapradius.x, minimapradius.y);
    minimapscale = vec((0.5f - 1.0f/size)/minimapradius.x, (0.5f - 1.0f/size)/minimapradius.y, 1.0f);

    envmapping = minimapping = true;

    physent *oldcamera = camera1;
    static physent cmcamera;
    cmcamera = *player;
    cmcamera.reset();
    cmcamera.type = ENT_CAMERA;
    cmcamera.o = vec(minimapcenter.x, minimapcenter.y, max(minimapcenter.z + minimapradius.z + 1, float(minimapheight)));
    cmcamera.yaw = 0;
    cmcamera.pitch = -90;
    cmcamera.roll = 0;
    camera1 = &cmcamera;
    setviewcell(vec(-1, -1, -1));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-minimapradius.x, minimapradius.x, -minimapradius.y, minimapradius.y, 0, camera1->o.z + 1);
    glScalef(-1, 1, 1);
    glMatrixMode(GL_MODELVIEW);

    transplayer();

    defaultshader->set();

    GLfloat fogc[4] = { minimapcolor.x/255.0f, minimapcolor.y/255.0f, minimapcolor.z/255.0f, 1.0f };
    glFogf(GL_FOG_START, 0);
    glFogf(GL_FOG_END, 1000000);
    glFogfv(GL_FOG_COLOR, fogc);

    glClearColor(fogc[0], fogc[1], fogc[2], fogc[3]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, size, size);

    glDisable(GL_FOG);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glFrontFace(GL_CCW);

    xtravertsva = xtraverts = glde = gbatches = 0;

    visiblecubes(false);
    queryreflections();
    drawreflections();

    loopi(minimapheight > 0 && minimapheight < minimapcenter.z + minimapradius.z ? 2 : 1)
    {
        if(i)
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            camera1->o.z = minimapheight;
            transplayer();
        }
        rendergeom();
        rendermapmodels();
        renderwater();
        rendermaterials();
        renderalphageom();
    }

    glFrontFace(GL_CW);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_FOG);

    glViewport(0, 0, screenw, screenh);

    camera1 = oldcamera;
    envmapping = minimapping = false;

    glBindTexture(GL_TEXTURE_2D, minimaptex);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5, 0, 0, size, size, 0);
    setuptexparameters(minimaptex, NULL, 3, 1, GL_RGB5, GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat border[4] = { minimapcolor.x/255.0f, minimapcolor.y/255.0f, minimapcolor.z/255.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool deferdrawtextures = false;

void drawtextures()
{
    if(minimized) { deferdrawtextures = true; return; }
    deferdrawtextures = false;
    genenvmaps();
    drawminimap();
}

GLuint motiontex = 0;
int motionw = 0, motionh = 0, lastmotion = 0;

void cleanupmotionblur()
{
    if(motiontex) { glDeleteTextures(1, &motiontex); motiontex = 0; }
    motionw = motionh = 0;
    lastmotion = 0;
}

VARFP(motionblur, 0, 0, 1, { if(!motionblur) cleanupmotionblur(); });
VARP(motionblurmillis, 1, 5, 1000);
FVARP(motionblurscale, 0, 0.5f, 1);

void addmotionblur()
{
    if(!motionblur || !hasTR || max(screenw, screenh) > hwtexsize) return;

    if(game::ispaused()) { lastmotion = 0; return; }

    if(!motiontex || motionw != screenw || motionh != screenh)
    {
        if(!motiontex) glGenTextures(1, &motiontex);
        motionw = screenw;
        motionh = screenh;
        lastmotion = 0;
        createtexture(motiontex, motionw, motionh, NULL, 3, 0, GL_RGB, GL_TEXTURE_RECTANGLE_ARB);
    }

    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, motiontex);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    rectshader->set();

    glColor4f(1, 1, 1, lastmotion ? pow(motionblurscale, max(float(lastmillis - lastmotion)/motionblurmillis, 1.0f)) : 0);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(      0,       0); glVertex2f(-1, -1);
    glTexCoord2f(motionw,       0); glVertex2f( 1, -1);
    glTexCoord2f(      0, motionh); glVertex2f(-1,  1);
    glTexCoord2f(motionw, motionh); glVertex2f( 1,  1);
    glEnd();

    glDisable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
 
    if(lastmillis - lastmotion >= motionblurmillis)
    {
        lastmotion = lastmillis - lastmillis%motionblurmillis;

        glCopyTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, 0, 0, screenw, screenh);
    }
}

bool dopostfx = false;

void invalidatepostfx()
{
    dopostfx = false;
}

void gl_drawhud(int w, int h);

int xtraverts, xtravertsva;

void gl_drawframe()
{
    if(deferdrawtextures) drawtextures();

    defaultshader->set();

    updatedynlights();

    aspect = forceaspect ? forceaspect : screenw/float(screenh);
    fovy = 2*atan2(tan(curfov/2*RAD), aspect)/RAD;
    
    int fogmat = lookupmaterial(camera1->o)&(MATF_VOLUME|MATF_INDEX), abovemat = MAT_AIR;
    float fogblend = 1.0f, causticspass = 0.0f;
    if(isliquid(fogmat&MATF_VOLUME))
    {
        float z = findsurface(fogmat, camera1->o, abovemat) - WATER_OFFSET;
        if(camera1->o.z < z + 1) fogblend = min(z + 1 - camera1->o.z, 1.0f);
        else fogmat = abovemat;
        if(caustics && (fogmat&MATF_VOLUME)==MAT_WATER && camera1->o.z < z)
            causticspass = min(z - camera1->o.z, 1.0f);
    }
    else fogmat = MAT_AIR;    
    setfog(fogmat, fogblend, abovemat);
    if(fogmat!=MAT_AIR)
    {
        float blend = abovemat==MAT_AIR ? fogblend : 1.0f;
        fovy += blend*sinf(lastmillis/1000.0)*2.0f;
        aspect += blend*sinf(lastmillis/1000.0+PI)*0.1f;
    }

    farplane = worldsize*2;

    project(fovy, aspect, farplane);
    transplayer();
    readmatrices();
    findorientation();
    setenvmatrix();

    glEnable(GL_FOG);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    xtravertsva = xtraverts = glde = gbatches = 0;

    if(!hasFBO)
    {
        if(dopostfx)
        {
            drawglaretex();
            drawdepthfxtex();
            drawreflections();
        }
        else dopostfx = true;
    }

    visiblecubes();
    
    if(shadowmap && !hasFBO) rendershadowmap();

    glClear(GL_DEPTH_BUFFER_BIT|(wireframe && editmode ? GL_COLOR_BUFFER_BIT : 0)|(hasstencil ? GL_STENCIL_BUFFER_BIT : 0));

    if(wireframe && editmode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    if(limitsky()) drawskybox(farplane, true);

    rendergeom(causticspass);

    extern SharedVar<int> outline;
    if(!wireframe && editmode && outline) renderoutline();

    queryreflections();

    generategrass();

    if(!limitsky()) drawskybox(farplane, false);

    renderdecals(true);

    rendermapmodels();
    rendergame(true);
    if(!isthirdperson())
    {
        project(curavatarfov, aspect, farplane, false, false, false, avatardepth);
        game::renderavatar();
        project(fovy, aspect, farplane);
    }

    if(wireframe && editmode) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(hasFBO) 
    {
        drawglaretex();
        drawdepthfxtex();
        drawreflections();
    }

    if(wireframe && editmode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    renderwater();
    rendergrass();

    rendermaterials();
    renderalphageom();

    if(wireframe && editmode) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    renderparticles(true);

    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    addmotionblur();
    addglare();
    if(isliquid(fogmat&MATF_VOLUME)) drawfogoverlay(fogmat, fogblend, abovemat);
    renderpostfx();

    defaultshader->set();
    g3d_render();

    notextureshader->set();

    gl_drawhud();

    renderedgame = false;
}

void gl_drawmainmenu()
{
    xtravertsva = xtraverts = glde = gbatches = 0;

    renderbackground(NULL, NULL, NULL, NULL, true, true);
    renderpostfx();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    defaultshader->set();
    g3d_render();

    notextureshader->set();

    gl_drawhud();
}

VARNP(damagecompass, usedamagecompass, 0, 1, 1);
VARP(damagecompassfade, 1, 1000, 10000);
VARP(damagecompasssize, 1, 30, 100);
VARP(damagecompassalpha, 1, 25, 100);
VARP(damagecompassmin, 1, 25, 1000);
VARP(damagecompassmax, 1, 200, 1000);

float dcompass[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
void damagecompass(int n, const vec &loc)
{
    if(!usedamagecompass || minimized) return;
    vec delta(loc);
    delta.sub(camera1->o); 
    float yaw, pitch;
    if(delta.magnitude()<4) yaw = camera1->yaw;
    else vectoyawpitch(delta, yaw, pitch);
    yaw -= camera1->yaw;
    if(yaw >= 360) yaw = fmod(yaw, 360);
    else if(yaw < 0) yaw = 360 - fmod(-yaw, 360);
    int dir = (int(yaw+22.5f)%360)/45;
    dcompass[dir] += max(n, damagecompassmin)/float(damagecompassmax);
    if(dcompass[dir]>1) dcompass[dir] = 1;

}
void drawdamagecompass(int w, int h)
{
    int dirs = 0;
    float size = damagecompasssize/100.0f*min(h, w)/2.0f;
    loopi(8) if(dcompass[i]>0)
    {
        if(!dirs)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1, 0, 0, damagecompassalpha/100.0f);
        }
        dirs++;

        glPushMatrix();
        glTranslatef(w/2, h/2, 0);
        glRotatef(i*45, 0, 0, 1);
        glTranslatef(0, -size/2.0f-min(h, w)/4.0f, 0);
        float logscale = 32,
              scale = log(1 + (logscale - 1)*dcompass[i]) / log(logscale);
        glScalef(size*scale, size*scale, 0);

        glBegin(GL_TRIANGLES);
        glVertex3f(1, 1, 0);
        glVertex3f(-1, 1, 0);
        glVertex3f(0, 0, 0);
        glEnd();
        glPopMatrix();

        // fade in log space so short blips don't disappear too quickly
        scale -= float(curtime)/damagecompassfade;
        dcompass[i] = scale > 0 ? (pow(logscale, scale) - 1) / (logscale - 1) : 0;
    }
}

int damageblendmillis = 0;

VARFP(damagescreen, 0, 1, 1, { if(!damagescreen) damageblendmillis = 0; });
VARP(damagescreenfactor, 1, 7, 100);
VARP(damagescreenalpha, 1, 45, 100);
VARP(damagescreenfade, 0, 125, 1000);
VARP(damagescreenmin, 1, 10, 1000);
VARP(damagescreenmax, 1, 100, 1000);

void damageblend(int n)
{
    if(!damagescreen || minimized) return;
    if(lastmillis > damageblendmillis) damageblendmillis = lastmillis;
    damageblendmillis += clamp(n, damagescreenmin, damagescreenmax)*damagescreenfactor;
}

void drawdamagescreen(int w, int h)
{
    if(lastmillis >= damageblendmillis) return;

    defaultshader->set();

    static Texture *damagetex = NULL;
    if(!damagetex) {
        string damagetex_filename;
        inexor::filesystem::appendmediadir(damagetex_filename, "damage.png", DIR_UI);
    	damagetex = textureload(damagetex_filename, 3);
    }

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, damagetex->id);
    float fade = damagescreenalpha/100.0f;
    if(damageblendmillis - lastmillis < damagescreenfade)
        fade *= float(damageblendmillis - lastmillis)/damagescreenfade;
    glColor4f(fade, fade, fade, fade);

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 0); glVertex2f(0, 0);
    glTexCoord2f(1, 0); glVertex2f(w, 0);
    glTexCoord2f(0, 1); glVertex2f(0, h);
    glTexCoord2f(1, 1); glVertex2f(w, h);
    glEnd();

    notextureshader->set();
}

VAR(hidestats, 0, 0, 1);
VAR(hidehud, 0, 0, 1);

VARP(crosshairsize, 0, 15, 50);
VARP(cursorsize, 0, 30, 50);
VARP(crosshairfx, 0, 1, 1);
VARP(crosshaircolors, 0, 1, 1);

// Directory where crosshairs are stored.
SVARP(crosshairdir, "media/interface/crosshair");

#define MAXCROSSHAIRS 4
static Texture *crosshairs[MAXCROSSHAIRS] = { NULL, NULL, NULL, NULL };

void loadcrosshair(const char *name, int i)
{
    if(i < 0 || i >= MAXCROSSHAIRS) return;
    crosshairs[i] = name ? textureload(tempformatstring("%s/%s", *crosshairdir, name), 3, true) : notexture;
    if(!crosshairs[i] || crosshairs[i] == notexture) 
    {
        name = game::defaultcrosshair(i);
        crosshairs[i] = textureload(tempformatstring("%s/%s", *crosshairdir, name), 3, true);
    }
}

void loadcrosshair_(const char *name, int *i)
{
	loadcrosshair(name, *i);
}

COMMANDN(loadcrosshair, loadcrosshair_, "si");

ICOMMAND(getcrosshair, "i", (int *i), 
{
    const char *name = "";
    if(*i >= 0 && *i < MAXCROSSHAIRS)
    {
        name = crosshairs[*i] ? crosshairs[*i]->name : tempformatstring("%s/%s", *crosshairdir, game::defaultcrosshair(*i));
    }
    result(name);
});
 
void writecrosshairs(stream *f)
{
    loopi(MAXCROSSHAIRS) if(crosshairs[i] && crosshairs[i] != notexture)
    {
        size_t len = strlen(crosshairdir);
        if(!strncmp(crosshairs[i]->name, path(crosshairdir), len))
        {
            crosshairs[i]->name += len+1;
        }
        f->printf("loadcrosshair %s %d\n", escapestring(crosshairs[i]->name), i);
    }
    f->printf("\n");
}

static Texture *cursortex = NULL;
SVARFP(cursor, "media/interface/cursor/default.png", cursortex = NULL);

void drawcrosshair(int w, int h)
{
    bool windowhit = g3d_windowhit(true, false);
    if(!windowhit && (hidehud || mainmenu)) return; //(hidehud || player->state==CS_SPECTATOR || player->state==CS_DEAD)) return;

    float r = 1, g = 1, b = 1, cx = 0.5f, cy = 0.5f, chsize;
    Texture *crosshair;
    if(windowhit)
    {
		if(!cursortex) cursortex = textureload(cursor, 3, true);
        crosshair = cursortex;
        chsize = cursorsize*w/900.0f;
        g3d_cursorpos(cx, cy);
    }
    else
    { 
        int index = game::selectcrosshair(r, g, b);
        if(index < 0) return;
        if(!crosshairfx) index = 0;
        if(!crosshairfx || !crosshaircolors) r = g = b = 1;
        crosshair = crosshairs[index];
        if(!crosshair) 
        {
            loadcrosshair(NULL, index);
            crosshair = crosshairs[index];
        }
        chsize = crosshairsize*w/900.0f;
    }
    if(crosshair->type&Texture::ALPHA) glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    else glBlendFunc(GL_ONE, GL_ONE);
    glColor3f(r, g, b);
    float x = cx*w - (windowhit ? 0 : chsize/2.0f);
    float y = cy*h - (windowhit ? 0 : chsize/2.0f);
    glBindTexture(GL_TEXTURE_2D, crosshair->id);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 0); glVertex2f(x,          y);
    glTexCoord2f(1, 0); glVertex2f(x + chsize, y);
    glTexCoord2f(0, 1); glVertex2f(x,          y + chsize);
    glTexCoord2f(1, 1); glVertex2f(x + chsize, y + chsize);
    glEnd();
}

VARP(wallclock, 0, 0, 1);
VARP(wallclock24, 0, 0, 1);
VARP(wallclocksecs, 0, 0, 1);

static time_t walltime = 0;

VARP(showfps, 0, 1, 1);
VARP(showfpsrange, 0, 0, 1);
VAR(showeditstats, 0, 0, 1);
VAR(statrate, 1, 200, 1000);

FVARP(conscale, 1e-3f, 0.33f, 1e3f);

void gl_drawhud()
{
    int w = screenw, h = screenh;
    if(forceaspect) w = int(ceil(h*forceaspect));

    if(editmode && !hidehud && !mainmenu)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);

        renderblendbrush();

        rendereditcursor();

        glDepthMask(GL_TRUE);
        glDisable(GL_DEPTH_TEST);
    }

    gettextres(w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glColor3f(1, 1, 1);

    extern SharedVar<int> debugsm;
    if(debugsm)
    {
        extern void viewshadowmap();
        viewshadowmap();
    }

    extern SharedVar<int> debugglare;
    if(debugglare)
    {
        extern void viewglaretex();
        viewglaretex();
    }

    extern SharedVar<int> debugdepthfx;
    if(debugdepthfx)
    {
        extern void viewdepthfxtex();
        viewdepthfxtex();
    }

    glEnable(GL_BLEND);
    
    if(!mainmenu)
    {
        drawdamagescreen(w, h);
        drawdamagecompass(w, h);
    }

    defaultshader->set();

    int conw = int(w/conscale), conh = int(h/conscale), abovehud = conh - FONTH, limitgui = abovehud;
    if(!hidehud && !mainmenu)
    {
        if(!hidestats)
        {
            glPushMatrix();
            glScalef(conscale, conscale, 1);

            int roffset = 0;
            if(showfps)
            {
                static int lastfps = 0, prevfps[3] = { 0, 0, 0 }, curfps[3] = { 0, 0, 0 };
                if(totalmillis - lastfps >= statrate)
                {
                    memcpy(prevfps, curfps, sizeof(prevfps));
                    lastfps = totalmillis - (totalmillis%statrate);
                }
                int nextfps[3];
                getfps(nextfps[0], nextfps[1], nextfps[2]);
                loopi(3) if(prevfps[i]==curfps[i]) curfps[i] = nextfps[i];
                if(showfpsrange) draw_textf("fps %d+%d-%d", conw-7*FONTH, conh-FONTH*3/2, curfps[0], curfps[1], curfps[2]);
                else draw_textf("fps %d", conw-5*FONTH, conh-FONTH*3/2, curfps[0]);
                roffset += FONTH;
            }

            if(wallclock)
            {
                if(!walltime) { walltime = time(NULL); walltime -= totalmillis/1000; if(!walltime) walltime++; }
                time_t walloffset = walltime + totalmillis/1000;
                struct tm *localvals = localtime(&walloffset);
                static string buf;
                if(localvals && strftime(buf, sizeof(buf), wallclocksecs ? (wallclock24 ? "%H:%M:%S" : "%I:%M:%S%p") : (wallclock24 ? "%H:%M" : "%I:%M%p"), localvals))
                {
                    // hack because not all platforms (windows) support %P lowercase option
                    // also strip leading 0 from 12 hour time
                    char *dst = buf;
                    const char *src = &buf[!wallclock24 && buf[0]=='0' ? 1 : 0];
                    while(*src) *dst++ = tolower(*src++);
                    *dst++ = '\0'; 
                    draw_text(buf, conw-5*FONTH, conh-FONTH*3/2-roffset);
                    roffset += FONTH;
                }
            }
                       
            if(editmode || showeditstats)
            {
                static int laststats = 0, prevstats[8] = { 0, 0, 0, 0, 0, 0, 0 }, curstats[8] = { 0, 0, 0, 0, 0, 0, 0 };
                if(totalmillis - laststats >= statrate)
                {
                    memcpy(prevstats, curstats, sizeof(prevstats));
                    laststats = totalmillis - (totalmillis%statrate);
                }
                int nextstats[8] =
                {
                    vtris*100/max(wtris, 1),
                    vverts*100/max(wverts, 1),
                    xtraverts/1024,
                    xtravertsva/1024,
                    glde,
                    gbatches,
                    getnumqueries(),
                    rplanes
                };
                loopi(8) if(prevstats[i]==curstats[i]) curstats[i] = nextstats[i];

                abovehud -= 2*FONTH;
                draw_textf("wtr:%dk(%d%%) wvt:%dk(%d%%) evt:%dk eva:%dk", FONTH/2, abovehud, wtris/1024, curstats[0], wverts/1024, curstats[1], curstats[2], curstats[3]);
                draw_textf("ond:%d va:%d gl:%d(%d) oq:%d lm:%d rp:%d pvs:%d", FONTH/2, abovehud+FONTH, allocnodes*8, allocva, curstats[4], curstats[5], curstats[6], lightmaps.length(), curstats[7], getnumviewcells());
                limitgui = abovehud;
            }

            if(editmode)
            {
                abovehud -= FONTH;
                draw_textf("cube %s%d%s", FONTH/2, abovehud, selchildcount<0 ? "1/" : "", abs(selchildcount), showmat && selchildmat > 0 ? getmaterialdesc(selchildmat, ": ") : "");

                char *editinfo = executestr("edithud");
                if(editinfo)
                {
                    if(editinfo[0])
                    {
                        int tw, th;
                        text_bounds(editinfo, tw, th);
                        th += FONTH-1; th -= th%FONTH;
                        abovehud -= max(th, FONTH);
                        draw_text(editinfo, FONTH/2, abovehud);
                    }
                    DELETEA(editinfo);
                }
            }
            else if(identexists("gamehud"))
            {
                char *gameinfo = executestr("gamehud");
                if(gameinfo)
                {
                    if(gameinfo[0])
                    {
                        int tw, th;
                        text_bounds(gameinfo, tw, th);
                        th += FONTH-1; th -= th%FONTH;
                        roffset += max(th, FONTH);    
                        draw_text(gameinfo, conw-max(5*FONTH, 2*FONTH+tw), conh-FONTH/2-roffset);
                    }
                    DELETEA(gameinfo);
                }
            } 
            
            glPopMatrix();
        }

        if(hidestats || (!editmode && !showeditstats))
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            game::gameplayhud(w, h);
            limitgui = abovehud = min(abovehud, int(conh*game::abovegameplayhud(w, h)));
        }

        rendertexturepanel(w, h);
    }
    
    g3d_limitscale((2*limitgui - conh) / float(conh));

    glPushMatrix();
    glScalef(conscale, conscale, 1);
    abovehud -= rendercommand(FONTH/2, abovehud - FONTH/2, conw-FONTH);
    extern SharedVar<int> fullconsole;
    if(!hidehud || fullconsole) renderconsole(conw, conh, abovehud - FONTH/2);
    glPopMatrix();

    drawcrosshair(w, h);

    glDisable(GL_BLEND);
}

