	.arch msp430g2553
	.p2align 1,0
	.text


	.global greenControl
	.extern P1OUT

greenControl:
	cmp #0, r12
	jz off
	;1 is the green LED
	bis #1, &P1OUT		;or
	pop r0
off:	and #~1, &P1OUT
	pop r0
