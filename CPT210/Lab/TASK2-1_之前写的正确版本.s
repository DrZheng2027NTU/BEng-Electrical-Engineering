mydata dcd     0xABCDEF01
res1   fill    4
       ;实现按照位次反转并把结果存储在res1里面
       adr     r6, mydata
       ldr     r1, [r6] ;r1中是原序列
       mov     r0, #0 ;左移索引
       mov     r5, #31 ;末尾索引
       ;这边说一下我的思路：我认为需要单独算一个bit31的处理结果
       ;然后每次循环之后的结果都会有一个记忆单元，可以相加
       lsrs    r7,r1,#31 ;r7存储bit31的处理结果，作为记忆单元
       add     r0,r0,#1 ;r0用于循环的索引从1开始

loop1  
       cmp     r0, r5 ;循环索引不能超过上限31
       bgt     end1
       lsl     r2, r1, r0 ;r2存储第一次左移之后的序列
       lsr     r3, r2, #31 ;r3存储第一次右移之后的序列
       lsl     r4, r3, r0 ;r4存储第二次左移之后的序列
       add     r7, r7, r4 ;这样r7始终存储每一次相加的结果
       add     r0, r0, #1 ;左移索引自增
       b       loop1 ;一定要有一个b loop来终止回路

end1   
       adr     r8, res1
       str     r7, [r8]
