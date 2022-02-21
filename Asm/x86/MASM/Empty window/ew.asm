
; Alexander (Shurko) Stadnichenko
; Public domain

.586p
.model flat, stdcall

includelib	<C:\Root\Soft\Creation\Coding\Asm\masm32\lib\kernel32.lib>
includelib	<C:\Root\Soft\Creation\Coding\Asm\masm32\lib\user32.lib>
includelib	<C:\Root\Soft\Creation\Coding\Asm\masm32\lib\gdi32.lib>

extrn	GetModuleHandleA@4:dword
extrn	LoadCursorA@8:dword
extrn	LoadIconA@8:dword
extrn	GetStockObject@4:dword
extrn	RegisterClassExA@4:dword
extrn	CreateWindowExA@48:dword
extrn	ShowWindow@8:dword
extrn	GetMessageA@16:dword
extrn	TranslateMessage@4:dword
extrn	DispatchMessageA@4:dword
extrn	PostQuitMessage@4:dword

extrn	ExitProcess@4:dword
extrn	MessageBoxA@16:dword
extrn	DefWindowProcA@16:dword

ExitProcess	PROTO STDCALL :DWORD


.XLIST
include		<C:\Root\Data\Creation\Coding\Asm\masm\Win-apps\ss-win\msgbox\WindowA.inc>
.LIST

.data

hInst		HANDLE		0
wcex		wndclassex	<>
hwnd		dd		0
; message		MSG		<?>
message		dw	6 dup(0)
szWCName	db	'WCName', 0
szWTName	db	'Window Title',0


mb_title	db	'Title', 0
mb_msg		db	'This is realy working !', 0

.code
_start proc ; near
; _start:



; ----- �������� ���������� ��������. ----- ;

	push	0
	call	near ptr GetModuleHandleA@4
	mov	hInst, eax

; ----- �������� ���������� ��������. ----- ;



; ----- ��������� ��������� wndclassex. ----- ;

	mov	wcex.cbSize,      type wndclassex
	mov	wcex.style,       CS_HREDRAW+CS_VREDRAW
	mov	wcex.lpfnWndProc, offset wndp
	mov	wcex.cbClsExtra,  0
	mov	wcex.cbWndExtra,  0
	mov	eax, hInst
	mov	wcex.hInstance,   eax

	push	IDI_ASTERISK		;����������� ������
	push	0			;NULL
	call	near ptr LoadIconA@8
	mov	wcex.hIcon,eax		;���������� ������ � ���� hIcon ��������� wcl

	push	IDC_ARROW		;����������� ������ - �������
	push	0
	call	near ptr LoadCursorA@8
	mov	wcex.hCursor, eax	;���������� ������� � ���� hCursor ��������� wcl

	push	WHITE_BRUSH
	call	near ptr GetStockObject@4
	mov	wcex.hbrBackground, eax

	mov	dword ptr wcex.lpszMenuName,	0		;��� �������� ����
	mov	dword ptr wcex.lpszClassName,	offset szWCName	;��� ������ ����
	mov	dword ptr wcex.hIconSm,		0

; ----- ��������� ���������� wndclassex. ----- ;



; ----- ������������ ��������� ������ ����. ----- ;

	push	offset wcex
	call	near ptr RegisterClassExA@4	; �������������� �����

; ----- ���������������� ��������� ������ ����. ----- ;



; ----- ������ ����. ----- ;

	push	0			; lpParam
	push	hInst			; hInstance
	push	NULL			; menu
	push	NULL			; parent hwnd
	push	600			; ��� CW_USEDEFAULT. ������ ����.
 	push	600			; ��� CW_USEDEFAULT. ������ ����.
	push	250			; ��� CW_USEDEFAULT. ���������� y ������ �������� ���� ����
	push	600			; ��� CW_USEDEFAULT. ���������� x ������ �������� ����
	push	WS_OVERLAPPEDWINDOW	; ����� ����
	push	offset szWTName		; ������ ��������� ����
	push	offset szWCName		; ��� ������ ����
	push	NULL
	call	near ptr CreateWindowExA@48
	mov	hwnd,eax		;hwnd - ���������� ����

; ----- ������� ����. ----- ;



; ----- ���������� ����. ----- ;

;�������� ����:
;������� ����� BOOL ShowWindow(
;	HWND hWnd,     // handle to window
;	int nCmdShow   // show state of window
;	)
	push	SW_SHOWNORMAL
	push	hwnd
	call	near ptr ShowWindow@8

; ----- �������� ����. ----- ;



; ----- ���� ��������� ���������. ----- ;

msgloop:

	push	0
	push	0
	push	NULL
	push	offset message
	call	near ptr GetMessageA@16
	cmp	ax,0
	je	end_msgloop


	push	offset message
	call	near ptr TranslateMessage@4


	push	offset message
	call	near ptr DispatchMessageA@4


	jmp	msgloop

; ----- ���� ��������� ���������. ----- ;



; ----- ����� �� ���������� ����� ��������� ���������. ----- ;

end_msgloop:
;	push	0
;	call	near ptr ExitProcess@4

	invoke	ExitProcess, 0

; ----- ����� �� ���������� ����� ��������� ���������. ----- ;


	push	MB_ICONINFORMATION
	push	offset mb_title
	push	offset mb_msg
	push	0
	call	near ptr MessageBoxA@16


_start endp



wndp	proc	stdcall uses ebx edi esi wndp_hWnd:DWORD, wndp_uMsg:DWORD, wndp_wParam:DWORD, wndp_lParam:DWORD

; public	wndp
; local	@@hdc:DWORD


	cmp	wndp_uMsg, WM_DESTROY
	je	wndp_wmdestroy

	jmp	wndp_dwp


wndp_wmdestroy:

	push	0
	call	near ptr PostQuitMessage@4
	mov	eax,0		;������������ �������� 0
	jmp	wndp_exit


wndp_dwp:

	push	wndp_lParam
	push	wndp_wParam
	push	wndp_uMsg
	push	wndp_hWnd
	call	near ptr DefWindowProcA@16


wndp_exit:

	ret

wndp	endp


end _start


