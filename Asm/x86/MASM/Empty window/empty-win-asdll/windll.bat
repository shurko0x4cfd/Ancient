
C:\Root\Soft\Creation\Coding\Asm\masm32\bin\ml.exe ^
/coff /c /Flew-list.lst /Foew-files\ew.obj ew.asm

C:\Root\Soft\Creation\Coding\Asm\masm32\bin\link.exe ^
/DLL /EXPORT:DllInit /EXPORT:DllMain /subsystem:windows /map:ew-files\ew.map /MAPINFO:EXPORTS ew-files\ew.obj

pause