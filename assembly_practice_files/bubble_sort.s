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
	
here b here
		
my_func
	ldmfd SP!, {R0-R1} ; input params
	mov R2, #0 ; i
loop1
;;;;;;;;;;;;;;;;;;;;;;;; start of loop1
	mov R3, #0 ; j
	sub R1, R1, #1 ; array_size -= 1

loop2
;;;;;;;;;;;;;; start of loop2
	ldr R4, [R0, R3] ; R4 = array[R0 + R3] = array[j]
	add R3, R3, #1
	ldr R5, [R0, R3] ; R5 = array[j+1]
	sub R3, R3, #1
	cmp R4, R5
	bcc end_if
	;;;;; start if
		; swap
	str R5, [R0, R3]
	add R3, R3, #1
	str R4, [R0, R3]
	sub R3, R3, #1
		; end swap
	;;;;; end if
end_if
	add R3, R3, #1
	cmp R1, R3
	bne loop2
;;;;;;;;;;;;;; end of loop2

	add R1, R1, #1 ; array_size += 1
	add R2, R2, #1
	cmp R2, R1
	bne loop1
;;;;;;;;;;;;;;;;;;;;;;;; end of loop1
	
	
	bx LR
	end