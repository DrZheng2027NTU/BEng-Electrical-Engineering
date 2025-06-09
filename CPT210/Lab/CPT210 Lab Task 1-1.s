values   dcd     2, 3, 6, 1, 8, 5, 6, 8
res1     fill    4
         adr     r9, values
         ;任务：找出最大值，并且放到res1里面
         ;显性自定义一个最大值，然后刷新就完事啦
         ;错误写法：add  r0, values;数组首地址提取
         adr     r0, values;数组首地址提取
         ldr     r1, [r0]
         ;这样我人为定义第一个元素是最大值，并且存储在r1之中了
         ;for    (int i=0, i<6, i++)
         ;如果从c看的话，我需要2个索引，一个最大，一个最小，一个是自增逻辑
         ;然后现在的话,r0已经是最小索引了
         add     r2, r0, #0x28
         ;得到最大索引
loop1    
         cmp     r0, r2
         bge     endloop1;做一个索引检查
         ldr     r3, [r0,#4]!;我这么操作是是不是都不需要手动索引自增了
         ;r3是比较数字，r1是被比较数字（max）
         cmp     r1, r3
         bgt     over ;如果r1大的话，最大值不更新
         ;如果r1小，就更新
         ;错误写法：mov    r3, r1
         mov     r1, r3
over     
         b       loop1

endloop1 
         adr     r4, res1
         str     r1, [r4]