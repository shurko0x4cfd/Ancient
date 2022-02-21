
C:\Root\Soft\Creation\Coding\Asm\masm32\bin\ml.exe ^
/coff /c /Flex-list.lst /Foex-files\ex.obj ex.asm

C:\Root\Soft\Creation\Coding\Asm\masm32\bin\link.exe ^
/subsystem:windows /map:ex-files\ex.map ex-files\ex.obj

pause