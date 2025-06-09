mydata	dcd		0xABCDEF01
res1		fill		4
		
		;		task 2.1
		;		Reverse the bits of mydata and save it to res1.
		;		The pattern is:
		;		The most significant bit will become the least significant bit.
		;		The second msb will become the second lsb.
		;		The third msb -> third lsb
		;		...
		;
		;		examples:
		;		0x80008000 -> 0x00010001
		;		0x00018000 -> 0x00018000
		;		0x13700000 -> 0x00000EC8
		
		adr		r3, mydata
		ldr		r2, [r3]	; r2 will be mydata
		
loop1
		;		loop condition, loop will run 32 times, r1 will become 0 to 31
		cmp		r1, #31
		bgt		exit
		
		;		pointer for each bit of mydata
		lsl		r4, r2, r1	; remove all bits left of "current selected bit"
		lsr		r4, r4, #31	; remove all bits right of "current selected bit"
		lsl		r4, r4, r1	; reverse postion of "current selected bit"
		orr		r0, r0, r4 	; add this bit to current reveresed data so far
		add		r1, r1, #1 	; increment loop counter or pointer
		b		loop1
exit
		adr		r5, res1
		str		r0, [r5]