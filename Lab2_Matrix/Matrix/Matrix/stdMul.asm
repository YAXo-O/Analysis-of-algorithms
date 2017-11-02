.code

; rcx - A matrix
; rdx - B matrix
; r8 - C matrix
; r9 - l
; rbp + 48 - m
; rbp + 56 - n
; rbp - 8 - i
; rbp - 16 - j
; rbp - 24 - k
; rbp - 32 - id - current Celement id
; rbp - 40 - Aij

matricesMultiply proc
; Prolog
	push rbp;
	mov rbp, rsp;
	sub rsp, 40;

; Vars
	i equ [rbp - 8];
	j equ [rbp - 16];
	k equ [rbp - 24];
	Cid equ [rbp - 32];
	Aij equ [rbp - 40];
	l equ r9;
	m equ [rbp + 48];
	n equ [rbp + 56];

; Saving params
	mov r10, rcx;
	mov r11, rdx;

; Rows loop
	mov rax, 0;
	mov j, rax;
rows:
	mov rax, 0;
	mov i, rax;
	cols:
		; id = i + j*dimX = i + j*n
		mov rax, n;
		mul QWord ptr j;
		add rax, i;
		mov rdx, 8;
		mul rdx;
		mov Cid, rax;
		mov rsi, rax;
		mov rax, 0;
		mov QWord ptr [r8 + rsi], rax;

		mov QWord ptr k, rax;
		sum:
			;// Ajk
			mov rax, j;
			mul QWord ptr m;
			add rax, QWord ptr k;
			mov rdx, 8;
			mul rdx
			mov rsi, rax;
			mov rax, QWord ptr [r10 + rsi];
			mov Aij, rax;
			;// Bki
			mov rax, k;
			mul QWord ptr n;
			add rax, QWord ptr j;
			mov rdx, 8;
			mul rdx
			mov rsi, rax;
			mov rax, [r11 + rsi];

			mul QWord ptr Aij;
			mov rsi, QWord ptr Cid;
			add QWord ptr [r8 + rsi], rax;

			inc QWord ptr k;
			mov rax, m;
			cmp k, rax;
			jb sum;

		inc QWord ptr i;
		mov rax, QWord ptr n;
		cmp QWord ptr i, rax;
		jb cols;
	
	inc QWord ptr j;
	cmp QWord ptr j, l;
	jb rows;
	
; Epilog
	add rsp, 40;
	pop rbp;

	ret
matricesMultiply endp;

end