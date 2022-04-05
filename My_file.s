    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
Lable2 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
    jr $ra
