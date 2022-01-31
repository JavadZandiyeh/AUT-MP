	area myData, data
memory equ 0x20000000
stack_size equ 12
	
	export __main
	area myCode, code, readonly
	entry

__main
	mov R1, #1
	mov R2, #2
	mov R3, #3
	mov R4, #4
	mov R5, #5
	mov R6, #6
	
	ldr SP, =(memory + stack_size)
	stmfd SP!, {R1-R3}
	mov R7, SP; my_func stack
	
	ldr SP, =(memory + 24)
	stmfd SP!, {R4-R6}
	mov R8, SP; main stack
	
	bl my_func
	
	mov SP, R8
	ldmfd SP!, {R4-R6}

here b here
		
my_func
	mov SP, R7; restore my_func stack pointer
	ldmfd SP!, {R4-R6}; restore params
	mov R4, #0
	mov R5, #0
	mov R6, #0
	bx LR
