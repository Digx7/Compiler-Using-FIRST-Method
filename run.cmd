@ECHO OFF

del compiler.exe

ECHO compiling scripts

g++ -o compiler compiler.cpp

ECHO running scripts

.\compiler