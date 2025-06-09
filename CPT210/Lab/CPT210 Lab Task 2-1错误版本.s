         ;task2.1所有位次反转，bit31 to bit 0, bit30 to bit1 ,……
mydata   dcd     0xABCDEF01
res1     fill    4
         adr     r0, mydata;r0也表示了首地址
         ldrb    r2, [r0];先提取当前的一位,bit31
         add     r3, r0, #0x16;r3表示了末地址

loop1    
         ;先做索引检查
         cmp     r0, r3;r0永远表示当前序列的首元素的地址
         bge     endloop1
         ;正式循环
         ldr     r1, [r0];每次循环开始之前要读取当前序列r1
         ldrb    r4, [r0], #1 ;提取当前的一位,bit31
         ;顺便少用一个寄存器处理自增
         lsl     r5, r1, #1;r4就表示了左移之后的序列
         add     r6, r5, r4;bit31变成bit0之后的新序列就是r6
         b       loop1

endloop1 
         ;add    r7, res1
         adr     r7, res1
         str     r6, [r7]

;错误原因在于ldr不能处理非4的倍数的索引



