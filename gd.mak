# IBM Developer's Workframe/2 Make File Creation run at 22:14:07 on 09/13/95

# Make File Creation run in directory:
#   E:\SOURCE\GD1.2;

.SUFFIXES:

.SUFFIXES: .c .cpp .cxx

ALL:      gd.OBJ \
     gdfontg.OBJ \
     gdfontl.OBJ \
     gdfontmb.OBJ \
     gdfonts.OBJ \
     gdfontt.OBJ


{.}.c.obj:
   ICC.EXE /C   .\$*.c

{.}.cpp.obj:
   ICC.EXE /C   .\$*.cpp

{.}.cxx.obj:
   ICC.EXE /C   .\$*.cxx

!include GD.DEP
