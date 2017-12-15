.code

; r8 - pointer to data struct

winogradMasm proc
; Prolog
	push rbp;
	mov rbp, rsp;
	sub rbp, 40; 
	
	mov r8, rcx;

; Vars
	g equ [r8];
	h equ [r8 + 8];
	r equ [r8 + 16];
	a equ [r8 + 24];
	b equ [r8 + 32];
	c equ [r8 + 40];
	rowFactor equ [r8 + 48];
	colFactor equ [r8 + 56];
	i equ  [rbp - 8];
	j equ [rbp - 16];
	k equ [rbp - 24];
	d equ [rbp - 32];
	
	mov rax, b;
	shr rax, 2;
	mov d, rax;

	mov QWord ptr i, 0;
rowFactorOuter:
	mov rdx, rowFactor;
	mov rbx, i;
	mov rax, 0;
	mov [rdx + rbx*8], rax;

	mov rax, 1;
	mov j, rax;
	rowFactorInner:
		;// Index[i][2*j - 1]
		mov rax, i;
		mul QWord ptr b;
		add rax, j;
		add rax, j;
		mov rsi, rax;
		dec rsi;

		;// Index[i][2*j - 2]
		mov rbx, rsi;
		dec rbx;

		mov rdx, g;
		mov rax, [rdx + rbx*8];
		mul QWord ptr [rdx + rsi*8];
		mov rdx, rowFactor;
		mov rbx, i;
		add [rdx + rbx], rax;

		inc QWord ptr j;
		mov rax, d;
		cmp j, rax;
		jb rowFactorInner;
		


	inc QWord ptr i;
	mov rax, a;
	cmp i, rax;
	jb rowFactorOuter;
	

	mov QWord ptr i, 0;
colFactorOuter:
	mov rdx, colFactor;
	mov rbx, i;
	mov rax, 0;
	mov [rdx + rbx*8], rax;

	mov rax, 1;
	mov j, rax;
	colFactorInner:
		;// Index[2*j - 2][i]
		mov rax, j;
		add rax, j
		sub rax, 2;
		mul QWord ptr c;
		add rax, i;
		mov rbx, rax;

		;// Index[2*j - 1][i]
		mov rax, j;
		add rax, j
		dec rax;
		mul QWord ptr c;
		add rax, i;
		mov rsi, rax;

		mov rdx, h;
		mov rax, [rdx + rbx*8];
		mul QWord ptr [rdx + rsi*8];
		mov rdx, colFactor;
		mov rbx, i;
		add [rdx + rbx*8], rax;

		inc QWord ptr j;
		mov rax, d;
		cmp j, rax;
		jb colFactorInner;
		
	inc QWord ptr i;
	mov rax, c;
	cmp i, rax;
	jb colFactorOuter;

	; For int i = 0; i < a; i++
	; For int j = 0; j < c; j++
	xor rax, rax;
	mov i, rax;
winogradOuter:

	xor rax, rax;
	mov j, rax;
	winogradMiddle:
		; R[i][j] = - rowFactor[i] - colFactor[j]
		; [i][j] = i*dimX + j; dimX = c;

		mov rax, c;
		mul i;
		add rax, j;
		
		inc i;
		mov rax, c;
		cmp j, rax;
		jb winogradMiddle;

	inc i;
	mov rax, a;
	cmp i, rax;
	jb winogradOuter;

; Epilog
	add rbp, 40;
	pop rbp;

	ret
winogradMasm endp;

end