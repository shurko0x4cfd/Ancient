
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

DllMain	proc	STDCALL uses ebx edi esi Arg1:DWORD, Arg2:DWORD, Arg3:DWORD

	push	MB_ICONINFORMATION
	push	offset mb_title
	push	offset mb_msg
	push	0
	call	near ptr MessageBoxA@16

	ret

DllMain endp




DllInit	proc	STDCALL uses ebx edi esi Arg1:DWORD, Arg2:DWORD, Arg3:DWORD


; ----- Получаем дескриптор процесса. ----- ;

	push	0
	call	near ptr GetModuleHandleA@4
	mov	hInst, eax

; ----- Получили дескриптор процесса. ----- ;



; ----- Заполняем структуру wndclassex. ----- ;

	mov	wcex.cbSize,      type wndclassex
	mov	wcex.style,       CS_HREDRAW+CS_VREDRAW
	mov	wcex.lpfnWndProc, offset wndp
	mov	wcex.cbClsExtra,  0
	mov	wcex.cbWndExtra,  0
	mov	eax, hInst
	mov	wcex.hInstance,   eax

	push	IDI_ASTERISK		;стандартная иконка
	push	0			;NULL
	call	near ptr LoadIconA@8
	mov	wcex.hIcon,eax		;дескриптор иконки в поле hIcon структуры wcl

	push	IDC_ARROW		;стандартный курсор - стрелка
	push	0
	call	near ptr LoadCursorA@8
	mov	wcex.hCursor, eax	;дескриптор курсора в поле hCursor структуры wcl

	push	WHITE_BRUSH
	call	near ptr GetStockObject@4
	mov	wcex.hbrBackground, eax

	mov	dword ptr wcex.lpszMenuName,	0		;без главного меню
	mov	dword ptr wcex.lpszClassName,	offset szWCName	;имя класса окна
	mov	dword ptr wcex.hIconSm,		0

; ----- Закончили заполнение wndclassex. ----- ;



; ----- Регистрируем экземпляр класса окна. ----- ;

	push	offset wcex
	call	near ptr RegisterClassExA@4	; зарегистрируем класс

; ----- Зарегистрировали экземпляр класса окна. ----- ;



; ----- Создаём окно. ----- ;

	push	0			; lpParam
	push	hInst			; hInstance
	push	NULL			; menu
	push	NULL			; parent hwnd
	push	600			; Или CW_USEDEFAULT. Высота окна.
 	push	600			; Или CW_USEDEFAULT. Ширина окна.
	push	250			; Или CW_USEDEFAULT. Координата y левого верхнего угла окна
	push	600			; Или CW_USEDEFAULT. Координата x левого верхнего угла
	push	WS_OVERLAPPEDWINDOW	; стиль окна
	push	offset szWTName		; Строка заголовка окна
	push	offset szWCName		; имя класса окна
	push	NULL
	call	near ptr CreateWindowExA@48
	mov	hwnd,eax		;hwnd - дескриптор окна

; ----- Создали окно. ----- ;



; ----- Показываем окно. ----- ;

;показать окно:
;готовим вызов BOOL ShowWindow(
;	HWND hWnd,     // handle to window
;	int nCmdShow   // show state of window
;	)
	push	SW_SHOWNORMAL
	push	hwnd
	call	near ptr ShowWindow@8

; ----- Показали окно. ----- ;



; ----- Цикл обработки сообщений. ----- ;

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

; ----- Цикл обработки сообщений. ----- ;



; ----- Выход по завершении цикла обработки сообщений. ----- ;

end_msgloop:

;	push	0
;	call	near ptr ExitProcess@4

;	invoke	ExitProcess, 0

; ----- Выход по завершении цикла обработки сообщений. ----- ;


;	push	MB_ICONINFORMATION
;	push	offset mb_title
;	push	offset mb_msg
;	push	0
;	call	near ptr MessageBoxA@16

	ret

DllInit endp




wndp	proc	stdcall uses ebx edi esi wndp_hWnd:DWORD, wndp_uMsg:DWORD, wndp_wParam:DWORD, wndp_lParam:DWORD

	cmp	wndp_uMsg, WM_DESTROY
	je	wndp_wmdestroy

	jmp	wndp_dwp


wndp_wmdestroy:

	push	0
	call	near ptr PostQuitMessage@4
	mov	eax,0		;возвращаемое значение 0
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


end DllMain









