
C:\Root\Soft\Creation\Coding\Asm\masm32\bin\ml.exe ^
/coff /c /Fledlluser-list.lst /Foew-files\dlluser.obj dlluser.asm

C:\Root\Soft\Creation\Coding\Asm\masm32\bin\link.exe ^
/subsystem:windows /map:ew-files\dlluser.map ew-files\dlluser.obj

pause