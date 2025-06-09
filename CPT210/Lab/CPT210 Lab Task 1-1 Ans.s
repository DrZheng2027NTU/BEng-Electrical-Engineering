values	dcd		2, 3, 6, 1, 8, 5, 6, 8
res1		fill		4
		
		;		task 1.1
		;		Find out the highest value among these values and store the result to res1
		;		***Make sure your program works for all cases with 8 numbers***
		
		adr		r9, values
		mov		r0, r9		; r0 will be the first number's address
		add		r1, r0, #28	; r1 will be the last number's address
		ldr		r5, [r0]		; get the first element, r5 will be the highest value so far
loop1
		add		r0, r0, #4	; point r0 to the next number;
		
		;		if r0 exceeds the last address
		cmp		r0, r1
		bgt		exit1		;     we will stop.
		
		;		else, check next number and repeat
		ldr		r6, [r0]  	; get the next number
		cmp		r5, r6		; compare against highest
		
		;		if highest (r5) is greater than current (r6), next loop
		bgt		loop1
		;		else, update the higest (r5), then next loop
		mov		r5, r6
		b		loop1
		
exit1
		adr		r0, res1
		str		r5, [r0]