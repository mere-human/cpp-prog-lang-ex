@echo off
call "e:\Software\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64     
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:out.exe
cl.exe %compilerflags% %* /link %linkerflags%