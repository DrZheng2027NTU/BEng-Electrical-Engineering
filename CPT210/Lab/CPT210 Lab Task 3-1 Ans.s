numbers	dcd		12, 15
res		fill		4
		
		;		Task 3.1
		;		Implement positive number multiplication using the instructions you have learned.
		;		Assume the two numbers are 15 bits long at maximum and are stored in "numbers".
		;		Note that mul is not supported in VisUAL. Your solution must work for all possible values.
		;		Store the result in res.
		
		adr		r9, numbers
		ldr		r2, [r9]		; r2 wil be first number
		ldr		r3, [r9, #4]	; r3 will be second number
		
loop1
		cmp		r4, r3		; if r4==r3, exit program else continue loop
		beq		exit
		
		add		r5, r5, r2	; update r5 for each loop
		add		r4, r4, #1	; increment loop counter
		b		loop1
exit
		adr		r0, res
		str		r5, [r0]