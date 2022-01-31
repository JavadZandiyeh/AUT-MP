	area myData, data
const equ 4

	export __main
	area myCode, code, readonly
	entry

__main
	mov r0, #const
	mov r1, #1
	mov r2, #1
	
loop
	mul r1, r1, r2; r1 = r1 * r2
	add r2, r2, #1; r2 = r2 + 1
	subs r4, r0, r2; r4 = r0 - r2
	bne loop
	mul r1, r1, r2
	
finish b finish
	end