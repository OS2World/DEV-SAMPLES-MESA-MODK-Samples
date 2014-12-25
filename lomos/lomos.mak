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
  .\lomos.exe \
  lomos.mak

.SUFFIXES:

.SUFFIXES: .cpp .rc

.rc.res:
      @echo WF::COMPILE::Resource Compile
      rc.exe -r %s %|fF.RES

.cpp.obj:
      @echo WF::COMPILE::CLC C++
      icc.exe /Ti /I..\ /DM2Z /Q /Fi /Si /Gm /G5 /C %s

.\lomos.exe: \
    .\lomos.obj \
    .\loandet.obj \
    .\sampcont.obj \
    ..\mesa_dok.lib \
    .\lomos.res
      @echo WF::LINK::CLC Link
      icc.exe @<<
 /B" /pmtype:pm /de"
 /Felomos.exe
 ..\mesa_dok.lib
 .\loandet.obj
 .\sampcont.obj
 .\lomos.obj
  lomos.def
<<
      @echo WF::BIND::Resource Bind
      rc.exe .\lomos.res lomos.exe


!include lomos.Dep
