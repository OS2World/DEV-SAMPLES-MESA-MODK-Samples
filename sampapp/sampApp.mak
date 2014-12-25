# Created by IBM WorkFrame/2 MakeMake at 17:28:11 on 07/27/95
#
# This makefile should be run in the following directory:
#   d:\development\mdisamp
#
# The actions included in this makefile are:
#   BIND::Resource Bind
#   COMPILE::CLC C++
#   COMPILE::Resource Compile
#   LINK::CLC Link

.all: \
  .\sampApp.exe \
  sampApp.mak

.SUFFIXES:

.SUFFIXES: .cpp .rc

.rc.res:
      @echo WF::COMPILE::Resource Compile
      rc.exe -r %s %|fF.RES

.cpp.obj:
      @echo WF::COMPILE::CLC C++
      icc.exe /Ti /I..\ /DM2Z /Q /Fi /Si /Gm /G5 /C %s

.\sampApp.exe: \
    .\sampApp.obj \
    .\sampcont.obj \
    ..\mesa_dok.lib \
    .\sampApp.res
      @echo WF::LINK::CLC Link
      icc.exe @<<
 /B" /pmtype:pm /de"
 /FesampApp.exe
 ..\mesa_dok.lib
 .\sampcont.obj
 .\sampApp.obj
  sampApp.def
<<
      @echo WF::BIND::Resource Bind
      rc.exe .\sampApp.res sampApp.exe


!include sampApp.Dep
