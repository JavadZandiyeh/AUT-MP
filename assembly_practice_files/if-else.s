	export __main
	area myCode, code, readonly
	entry

__main
	;if(R0 < R1)
	;	R2 = 5
	;else
	;	R2 = 10
	mov R0, #3
	mov R1, #2
	cmp R0, R1
	bcc if_part
	mov R2, #10; else parat
	b here

if_part
	mov R2, #5
	b here

here b here
	end