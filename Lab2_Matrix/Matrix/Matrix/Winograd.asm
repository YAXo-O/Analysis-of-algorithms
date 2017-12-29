.code
;ruine@bk.ru
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
	shr rax, 1;
	mov d, rax;

	mov QWord ptr i, 0;

rowFactorOuter:
	mov rbx, i;
	mov rax, b;
	mul rbx;
	mov rbx, rax;
	mov rdx, g;
	mov rax, [rdx + rbx*8];
	mov rcx, [rdx + rbx*8 + 8];
	mul rcx;

	mov rdx, rowFactor;
	mov rbx, i;
	mov [rdx + rbx*8], rax;

	mov rax, 1;
	mov j, rax;
	rowFactorInner:
		mov rax, d;
		cmp j, rax;
		jge rowFactorInnerEnd;

		;// Index[i][2*j]
		mov rax, i;
		mul QWord ptr b;
		add rax, j;
		add rax, j;
		mov rsi, rax;

		;// Index[i][2*j + 1]
		mov rbx, rsi;
		inc rbx;

		mov rdx, g;
		mov rax, [rdx + rbx*8];
		mul QWord ptr [rdx + rsi*8];
		mov rdx, rowFactor;
		mov rbx, i;
		add [rdx + rbx*8], rax;

		inc QWord ptr j;
		jmp rowFactorInner
		rowFactorInnerEnd:


	inc QWord ptr i;
	mov rax, a;
	cmp i, rax;
	jb rowFactorOuter;
	

	mov QWord ptr i, 0;

colFactorOuter:
	mov rdx, h;
	mov rbx, i;
	mov rcx, [rdx + rbx*8];
	mov rsi, c;
	add rsi, rbx;
	mov rax, [rdx + rsi*8];
	mul rcx;

	mov rdx, colFactor;
	mov [rdx + rbx*8], rax;

	mov rax, 1;
	mov j, rax;
	colFactorInner:
		mov rax, d;
		cmp j, rax;
		jge colFactorInnerEnd;

		;// Index[2*j][i]
		mov rax, j;
		add rax, j
		mul QWord ptr c;
		add rax, i;
		mov rbx, rax;

		;// Index[(2*j + 1)][i]
		mov rax, j;
		add rax, j
		inc rax;
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
		jmp colFactorInner;
		colFactorInnerEnd:
		
	inc QWord ptr i;
	mov rax, c;
	cmp i, rax;
	jb colFactorOuter;

	;for i = 1 to a do
	;	for j = 1 to c do
	;		Ri,j = -rowFactor[i] - columnFactor[j]
	;		for k = 1 to d do
	;			Ri,j = Ri,j + (Gi,2k-1 + H2k,j)*(Gi,2k + H2k-1,j)
	;		end for k
	;	end for j
	;end for i 

	mov rax, 0;
	mov i, rax;
	winogradOuter:
		
		mov rax, 0;
		mov j, rax;
		winogradMiddle: ;
			;Ri,j = -rowFactor[i] - columnFactor[j]
			; [i;j] = j*dimX + i; dimX = c
			mov rax, QWord ptr rowFactor;
			mov rsi, i;
			mov rdx, QWord ptr [rax + rsi*8];
			push rdx; --rowFactor[i]

			mov rax, colFactor;
			mov rsi, j;
			mov rdx, [rax + rsi*8];
			pop rax; --
			add rax, rdx; rowFactor[i] - columnFactor[j]
			mov rdx, 0;
			sub rdx, rax;
			push rdx;

			mov rax, i;
			mul QWord ptr c;
			add rax, j;
			mov rsi, rax;
			mov rax, QWord ptr r;
			pop rdx;
			mov QWord ptr [rax + rsi*8], rdx; 


			mov rax, 0;
			mov k, rax;
			winogradInner:
				mov rax, k;
				cmp rax, d;
				jge winogradInnerEnd;

				;Ri,j = Ri,j + (Gi,2k+1 + H2k,j)*(Gi,2k + H2k+1,j)
				;[i;2k+1] = i*dimX + 2k + 1; dimX = c
				mov rax, i;
				mul QWord ptr b;
				add rax, k;
				add rax, k;
				inc rax;
				mov rbx, rax;

				mov rax, QWord ptr g;
				mov rdx, QWord ptr [rax + rbx*8];
				push rdx; (G[i;2k-1])

				;[2k; j] = 2k*dimX + j
				mov rax, k;
				add rax, k;
				mul QWord ptr c;
				add rax, j;
				mov rbx, rax;

				mov rax, QWord ptr h;
				mov rdx, QWord ptr [rax + rbx*8];
				pop rbx;
				add rdx, rbx;
				push rdx; --(G[i; 2k-1] + H[2k; j])
				
				;[i;2k] = i*dimX + 2*k
				mov rax, i;
				mul QWord ptr b;
				add rax, k;
				add rax, k;
				mov rbx, rax;

				mov rax, QWord ptr g;
				mov rdx, QWord ptr [rax + rbx*8];
				push rdx;

				;[2k-1;j] = (2*k + 1)*dimX + j
				mov rax, k;
				add rax, k;
				inc rax;
				mul QWord ptr c;
				add rax, j;
				mov rbx, rax;

				mov rax, QWord ptr h;
				mov rdx, QWord ptr [rax + rbx*8];
				pop rax;
				add rax, rdx;
				pop rcx;

				mul rcx;
				
				mov rbx, QWord ptr r;
				mov rdx, [rbx + rsi*8];
				add [rbx + rsi*8], rax;
				mov rax, [rbx + rsi*8];

				inc QWord ptr k;
				mov rax, k;
				mov rbx, j;
				jmp winogradInner;
				winogradInnerEnd:;
				

			inc QWord ptr j;
			mov rax, j;
			cmp rax, c;
			jb winogradMiddle;

		inc QWord ptr i;
		mov rax, i;
		cmp rax, a;
		jb winogradOuter;

; Non-odd sizes	
	mov rax, b;
	mov rbx, 2;
	xor edx, edx;
	div rbx;
	cmp rdx, 0;
	je epilog;

	xor rax, rax;
	mov i, rax;
	
	outerNonOdd:
		mov rax, a;
		cmp i, rax;
		jge outerNonOddEnd;

		mov rax, 0;
		mov j, rax;
		innerNonOdd:
			mov rax, c;
			cmp j, rax;
			jge innerNonOddEnd;

			;R[i;j]; [i;j] = i*dimX + j; dimX = c;
			mov rax, i;
			mul QWord ptr c;
			add rax, j;
			push rax;

			;[i*b + b]
			mov rax, i;
			mul QWord ptr b;
			add rax, b;
			dec rax;
			mov rdx, g;
			mov rax, [rdx + rax*8];
			push rax;

			;[(b-1)*c + j]
			mov rax, b;
			dec rax;
			mul QWord ptr c;
			add rax, j;
			
			mov rdx, h;
			mov rax, QWord ptr [rdx + rax*8];
			pop rcx;
			mul rcx;

			pop rsi;
			mov rdx, r;
			add [rdx + rsi*8], rax;

			inc QWord ptr j;
			innerNonOddEnd:		

		inc QWord ptr i;
		outerNonOddEnd:


; Epilog
epilog:
	add rbp, 40;
	pop rbp;

	ret
winogradMasm endp;

end