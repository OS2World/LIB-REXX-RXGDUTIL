Rem - This .CMD file will create the LIBRARY and the DLL file for
Rem - RXGDUTIL.DLL

Rem - Build the Library first
nmake -f gd.mak
call gdlib.cmd


Rem - Build the DLL
nmake -f rxgdutil.mak
