PIO_PER equ 0x400E0E00
PIO_OER equ 0x400E0E10
PIO_SODR equ 0x400E0E30
PIO_CODR equ 0x400E0E34

PIO_ISR equ 0x400E0E4C

	area myCode, code, readonly
	export __main
	entry

__main
	bl enable_pio

polling_interrupt_loop
	mov r4, #2_1000
	ldr r6, =PIO_ISR
	ldr r5, [r6]
	cmp r4, r5
	BEQ loop
	bl polling_interrupt_loop
	
button_check2
	mov r4, #2_10000 	
	ldr r6, =PIO_ISR
	ldr r5, [r6]
	cmp r4, r5
	beq polling_interrupt_loop
	bx lr
	
loop
	; part 1
	bl led_on
	bl delay
	
	; part 2
	mov r4, #2_001
	bl led_off
	bl delay
	
	; part 3
	bl led_on
	mov r4, #2_010
	bl led_off
	bl delay
	
	; part 4
	mov r4, #2_011
	bl led_off
	bl delay
	
	; part 5
	bl led_on
	mov r4, #2_100
	bl led_off
	bl delay
	
	; part 6
	mov r4, #2_101
	bl led_off
	bl delay
	
	; part 7
	bl led_on
	mov r4, #2_110
	bl led_off
	bl delay
	
	; part 8
	mov r4, #2_111
	bl led_off
	bl delay
	
	
	bl button_check2
	
	bl loop

enable_pio
	mov r4, #2_111
	
	ldr r5, =PIO_PER
	str r4, [r5]
	
	ldr r5, =PIO_OER
	str r4, [r5]
	
	bx lr

led_on
	mov r4, #2_111
	
	ldr r5, =PIO_SODR
	str r4, [r5]
	bx lr

led_off
	;mov r4, #2_111
	
	ldr r5, =PIO_CODR
	str r4, [r5]
	
	bx lr

delay
	mov r4, #0
	ldr r5, =0x00A00A

delay_loop
	add r4, r4, #1
	
	cmp r4, r5
	bne delay_loop
	bx lr
	
	end