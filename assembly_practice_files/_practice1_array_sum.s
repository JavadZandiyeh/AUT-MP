; result = sum of array elements
	area myData, data
memory equ 0x20000000
array_size equ 0xFF

	export __main
	area myCode, code, readonly
	entry

__main
	ldr SP, =(memory + 0xFFF)
	ldr R0, =memory  ; *array
	mov R1, #array_size ; array_size
	stmfd SP!, {R0-R1}
	bl my_func
	ldmfd SP! {R2} ; return value of my_func
	
here b here
		
my_func
	ldmfd SP!, {R0-R1} ; input params
	mov R2, #0 ; result
	mov R3, #0 ; i
loop
	add R4, R0, R3 ; address of array[i]
	ldr R4, [R4] ; array[i]
	add R2, R2, R4 ; result += array[i]

	add R3, R3, #4 ; i++
	cmp R3, R1
	bne loop
	bx LR
	end