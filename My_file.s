    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    .data
Lable2 :
    .bite 105 ,111 ,111 ,0
    .align 2
    .text
    la $s7,Lable2
    move $a0,$s7
    jal Lprints
Lable1 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
    jr $ra
