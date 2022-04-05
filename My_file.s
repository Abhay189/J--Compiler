    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,16
    sw $ra,0($sp)
    li $s7,99
    li $s6,78
Lable1 : 
    lw $ra,0($sp)
    addu $sp,$sp,16
    jr $ra
