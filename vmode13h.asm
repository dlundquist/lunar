	P386N
	IDEAL
	MODEL small

	DATASEG

	CODESEG

	PUBLIC	_setmode
	PUBLIC	_wtsync
	PUBLIC	_cleardevice
	PUBLIC	_swap
	PUBLIC	_putpixel
	PUBLIC	_getpixel
	PUBLIC	_screenadr
	PUBLIC	_vmemalloc
	PUBLIC	_vmemfree

PROC	_setmode	NEAR
	ARG	mode:Word
	push	bp
	mov	bp,sp
	mov	ax,[mode]
	int	10h
	pop	bp
	ret
ENDP	_setmode

PROC	_wtsync		NEAR
	push	ax
	push	dx
	mov	dx,3DAh
@@vr1:	in	al,dx
	test	al,8
	jne	@@vr1
@@vr2:	in	al,dx
	test	al,8
	je	@@vr2
	pop	dx
	pop	ax
	ret
ENDP	_wtsync

PROC	_cleardevice	NEAR
	ARG	dest:Dword
	push	bp
	mov	bp,sp
	push	di
	xor	eax,eax
	les	di,[dest]
	mov	cx,16000
	rep	stosd
	pop	di
	pop	bp
	ret
ENDP	_cleardevice

PROC	_swap		NEAR
	ARG	src:Dword, dest:Dword
	push	bp
	mov	bp,sp
	push	ds
	push	si
	push	di
	lds	si,[src]
	les	di,[dest]
	mov	cx,16000
	rep	movsd
	pop	di
	pop	si
	pop	ds
	pop	bp
	ret
ENDP	_swap

PROC	_putpixel	NEAR
	ARG	xpos:Word, ypos:Word, color:Byte, dest:Dword
	push	bp
	mov	bp,sp
	push	di
	les	di,[dest]
	mov	di,[xpos]
	mov	ax,[ypos]
	xchg	ah,al
	add	di,ax
	shr	ax,2
	add	di,ax
	mov	al,[color]
	mov	[es:di],al
	pop	di
	pop	bp
	ret
ENDP	_putpixel

PROC	_getpixel	NEAR
	ARG	xpos:Word, ypos:Word, src:Dword
	push	bp
	mov	bp,sp
	push	di
	les	di,[src]
	mov	di,[xpos]
	mov	ax,[ypos]
	xchg	ah,al
	add	di,ax
	shr	ax,2
	add	di,ax
	mov	al,[es:di]
	pop	di
	pop	bp
	ret
ENDP	_getpixel

PROC	_screenadr	NEAR
	xor	ax,ax
	mov	dx,0a000h
	ret
ENDP	_screenadr

PROC	_vmemalloc	NEAR
	ARG	bytes:Word
	push	bp
	mov	bp,sp
	mov	bx,[bytes]
	shr	bx,4
	inc	bx
	mov	ah,48h
	int	21h
	mov	dx,ax
	jnc	@@nerr
	xor	dx,dx
@@nerr:	xor	ax,ax
	pop	bp
	ret
ENDP	_vmemalloc

PROC	_vmemfree	NEAR
	ARG	block:Dword
	push	bp
	mov	bp,sp
	les	ax,[block]
	mov	ah,49h
	int	21h
	jnc	@@nerr
	xor	ax,ax
@@nerr: pop	bp
	ret
ENDP	_vmemfree

	END
