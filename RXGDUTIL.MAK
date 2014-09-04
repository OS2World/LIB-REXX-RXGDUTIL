# IBM Developer's Workframe/2 Make File Creation run at 22:04:13 on 09/14/95

# Make File Creation run in directory:
#   E:\SOURCE\GD1.2;

.SUFFIXES:

.SUFFIXES: .c .cpp .cxx

RXGDUTIL.DLL:  \
  GD.LIB \
  RXGDUTIL.OBJ \
  RXGDUTIL.MAK
   ICC.EXE @<<
/Tdp /Ge- /Gs /Gn /B"/NOE"
 /Fe"RXGDUTIL.DLL" REXX.lib RXGDUTIL.DEF
GD.LIB
RXGDUTIL.OBJ
<<
  IMPLIB RXGDUTIL.LIB RXGDUTIL.DLL

{.}.c.obj:
   ICC.EXE /Ge- /C   .\$*.c

{.}.cpp.obj:
   ICC.EXE /Ss /Ge- /Gs /Gn /C   .\$*.cpp

{.}.cxx.obj:
   ICC.EXE /Ss /Ge- /Gs /Gn /C   .\$*.cxx

!include RXGDUTIL.DEP
