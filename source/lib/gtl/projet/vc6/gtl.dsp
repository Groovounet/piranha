# Microsoft Developer Studio Project File - Name="gtl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=gtl - Win32 Debug SDL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gtl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gtl.mak" CFG="gtl - Win32 Debug SDL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gtl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gtl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "gtl - Win32 Release SDL" (based on "Win32 (x86) Static Library")
!MESSAGE "gtl - Win32 Debug SDL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gtl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/vc6/gtl.lib"

!ELSEIF  "$(CFG)" == "gtl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/vc6/gtl.lib"

!ELSEIF  "$(CFG)" == "gtl - Win32 Release SDL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "gtl___Win32_Release_SDL"
# PROP BASE Intermediate_Dir "gtl___Win32_Release_SDL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_SDL"
# PROP Intermediate_Dir "Release_SDL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/vc6/gtl.lib"

!ELSEIF  "$(CFG)" == "gtl - Win32 Debug SDL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gtl___Win32_Debug_SDL"
# PROP BASE Intermediate_Dir "gtl___Win32_Debug_SDL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_SDL"
# PROP Intermediate_Dir "Debug_SDL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/vc6/gtl.lib"

!ENDIF 

# Begin Target

# Name "gtl - Win32 Release"
# Name "gtl - Win32 Debug"
# Name "gtl - Win32 Release SDL"
# Name "gtl - Win32 Debug SDL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\gtl_camera.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_color3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_color4.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_complex_algebraic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_complex_polar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_font_tga.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_gl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_glext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_image_bmp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_image_raw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_image_tga.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_math.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_matrix2x2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_matrix3x3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_matrix4x4.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_polynomial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_quaternion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_rand.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_screenshot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_shader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_vector2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_vector3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_vector4.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\gtl.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_camera.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_color.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_color3.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_color4.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_complex_algebraic.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_complex_polar.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_font.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_font_tga.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_gl.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_glext.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_image.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_image_bmp.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_image_raw.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_image_tga.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_math.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_matrix2x2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_matrix3x3.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_matrix4x4.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_polynomial.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_quaternion.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_rand.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_screenshot.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_shader.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_vector.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_vector2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_vector3.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_vector4.h
# End Source File
# End Group
# End Target
# End Project
