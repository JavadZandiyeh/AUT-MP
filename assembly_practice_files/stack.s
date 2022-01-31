	area myData, data
memory equ 0x20000000
stack_size equ 12
	
	export __main
	area myCode, code, readonly
	entry

__main
	;push R0 and R1 and R2 into stack
	mov R1, #1
	mov R2, #2
	mov R3, #3
	ldr SP, =(memory + stack_size)
	stmfd SP!, {R1-R3}; push with result writeback
	ldmfd SP!, {R4-R6}; pop with result writeback
	mov R4, #1
	end