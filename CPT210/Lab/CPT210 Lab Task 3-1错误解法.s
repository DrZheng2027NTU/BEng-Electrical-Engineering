numbers  dcd     12, 15
res      fill    4
         adr     r0, numbers
         ;错误写法
         ;adr    r0, numbers, #4
         ;正确写法
         add     r1, r0, #4
         ldr     r2, [r0];r2=12
         ldr     r3, [r1];r3=15
         mov     r4, #0
loop1    
         cmp     r4, r3
         bge     endloop1
         add     r5, r2, r2
         add     r4, r4, #1
         b       loop1

endloop1 
         adr     r6, res
         str     r5, [r6]



