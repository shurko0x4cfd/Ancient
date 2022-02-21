
.586p
.model flat, stdcall

includelib      <C:\Root\Data\Creation\Coding\Asm\masm\Win-apps\ss-win\empty-win-asdll\ew.lib>

includelib	<C:\Root\Soft\Creation\Coding\Asm\masm32\lib\kernel32.lib>
includelib	<C:\Root\Soft\Creation\Coding\Asm\masm32\lib\user32.lib>


extrn	DllInit@12:dword
; extrn	DllMain@12:dword

extrn	ExitProcess@4:dword
extrn	MessageBoxA@16:dword

.XLIST
include		<C:\Root\Data\Creation\Coding\Asm\masm\Win-apps\ss-win\msgbox\WindowA.inc>
.LIST




.data

mb_title	db	'Title', 0
mb_msg		db	'Dll user.', 0




.code
_start:


	push	0
	push	0
	push	0
	call	near ptr DllInit@12


	push	MB_ICONINFORMATION
	push	offset mb_title
	push	offset mb_msg
	push	0
	call	near ptr MessageBoxA@16


	push	0
	call	near ptr ExitProcess@4
	ret

end _start







