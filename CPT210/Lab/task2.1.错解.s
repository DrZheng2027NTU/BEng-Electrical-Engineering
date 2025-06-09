         ;task2.1所有位次反转，bit31 to bit 0, bit30 to bit1 ,……
mydata   dcd     0xABCDEF01
res1     fill    4
         ;思路是需要一个基数，然后每次的结果和这个级数相加
         ;每次运算都要按照左右左
         ;step1: 基数构建
         adr     r0, mydata
         ldr     r1, [r0]
         lsr     r1, r1, #0b32;得到基数
         mov     r2, #1;首索引
         mov     r3, #31;末索引
         mov     r5, #0
loop1    
         cmp     r2, r3
         bgt     endloop1
         ldr     r4, [r0];需要一个原始数字,并且不被覆盖
         lsl     r4, r4, r2
         lsr     r4, r4, #0b32
         lsl     r4, r4, r2;操作完之后的数字
         add     r5, r1, r4
         add     r2, r2, #1
         b       loop1

endloop1 
         adr     r6, res1
         str     r5, [r6]



