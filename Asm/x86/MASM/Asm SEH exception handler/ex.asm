
; Alexander (Shurko) Stadnichenko
; Public domain

.586p
.model flat, stdcall

includelib	<C:\Root\Soft\Creation\Coding\Asm\masm32\lib\kernel32.lib>
includelib	<C:\Root\Soft\Creation\Coding\Asm\masm32\lib\user32.lib>

extrn	ExitProcess@4:dword
extrn	MessageBoxA@16:dword

.XLIST
include		<C:\Root\Data\Creation\Coding\Asm\masm\Win-apps\ss-win\exception-hndl\context.inc>
include		<C:\Root\Data\Creation\Coding\Asm\masm\Win-apps\ss-win\exception-hndl\WindowA.inc>
.LIST

.data

hexdgt		db	'0123456789ABCDEF'

mydw_msg	db	'DWORD:', 32, 32, '0x'
mydw		db	8 dup(0), 0

mb_title	db	'Title', 0
msg_before_hndl	db	'��������� �� ��������� �����������.', 0
msg_afters_hndl	db	'��������� ����� ��������� �����������.', 0
msg_afterd_hndl	db	'��������� ����� �������� �����������.', 0
msg_intime_hndl	db	'��������� �� ����� ���������.', 0

.code
assume fs:nothing

_start:


	push	MB_ICONINFORMATION
	push	offset mb_title
	push	offset msg_before_hndl
	push	0
	call	near ptr MessageBoxA@16


	push	offset	e_handler
	push	dword ptr fs:[0]
	mov	fs:[0],esp


	push	MB_ICONINFORMATION
	push	offset mb_title
	push	offset msg_afters_hndl
	push	0
	call	near ptr MessageBoxA@16


	xor	edx, edx
	mov	eax, 012345678h
	mov	ebx, 0
	div	bx


	mov	edx, eax
	mov	ebx, offset hexdgt
	mov	esi, offset mydw + 7
	mov	ecx, 16
l2:
	mov	eax, edx
	and	eax, 0fh

	xlat
	mov	byte ptr [esi], al

	shr	edx, 4
	dec	esi
	dec	ecx
	loop	l2


	push	MB_ICONINFORMATION
	push	offset mb_title
	push	offset mydw_msg
	push	0
	call	near ptr MessageBoxA@16

	pop	dword ptr fs:[0]
	add	esp,4


	push	MB_ICONINFORMATION
	push	offset mb_title
	push	offset msg_afterd_hndl
	push	0
	call	near ptr MessageBoxA@16


	push	0
	call	near ptr ExitProcess@4
	ret


e_handler	proc	uses	ebx edi esi	ExceptionRecord:dword, \
						EstablisherFrame:dword,\
						ContextRecord:dword,   \
						DispatcherContext:dword


	mov	edx, ContextRecord ; ExceptionRecord
	mov	edx, [edx+0] ; [edx].context.regEax

	mov	ebx, offset hexdgt
	mov	esi, offset mydw + 7
	mov	ecx, 16
l1:
	mov	eax, edx
	and	eax, 0fh

	xlat
	mov	byte ptr [esi], al

	shr	edx, 4
	dec	esi
	dec	ecx
	loop	l1


	mov	edx, ContextRecord ; ExceptionRecord
	mov	dword ptr [edx].context.regEbx, 1


	push	MB_ICONINFORMATION
	push	offset mb_title
	push	offset mydw_msg
	push	0
	call	near ptr MessageBoxA@16


ehandler_exit:

	mov	eax, 0
	ret

e_handler	endp


end _start

;	push	MB_ICONINFORMATION
;	push	offset mb_title
;	push	offset mb_msg
;	push	0
;	call	near ptr MessageBoxA@16

