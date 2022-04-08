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
Lable1 : 
    subu $sp,$sp,12
    sw $ra,0($sp)
    li $s7,78
    sw $s7,4($sp)
    lw $s7,4($sp)
    move $a0,$s7
    jal Lprinti
Lable3 : 
    lw $ra,0($sp)
    addu $sp,$sp,12
    jr $ra

Lprints: 
    li	$v0, 4
    syscall
    jr $ra

Lprintb: 
    li	$v0, 1
    syscall
    jr $ra

Lprintc: 
    li	$v0, 11
    syscall
    jr $ra

Lprinti: 
    li	$v0, 1
    syscall
    jr $ra

