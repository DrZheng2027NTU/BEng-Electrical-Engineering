values   dcd     2, 3, 6, 1, 8, 5, 6, 8
res1     fill    4
         adr     r9, values
         ;任务：找出最大值，并且放到res1里面
         adr     r0, values;第一个索引
         add     r1, r0, #0x28;最后索引
         ldr     r2, [r0];自定义最大值
loop1    
         cmp     r0, r1
         bgt     endloop1
         ldr     r3, [r0,#4]!
         cmp     r2, r3
         bgt     endloop1
         mov     r2, r3
         b       loop1

endloop1 
         adr     r4, res1
         str     r2, [r4]

;这个是错误的，原因在于：如果我r2>r3，你确实不用更新r2最大值
;但是问题是：你也不能退出循环啊，你还是要回到b loop的呀
