    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

    .data
Lable1 :
    .word 0
    .text
Lable0 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    li $s7,990
    sw $s7,Lable1
Lable2 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
    jr $ra
