    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,8
    sw $ra,0($sp)
    li $s7,87
    sw $s7,4($sp)
    li $s7,98
    move $a1,$s7
    jal Lable1
Lable2 : 
    lw $ra,0($sp)
    addu $sp,$sp,8
    jr $ra
Lable1 : 
    subu $sp,$sp,16
    sw $ra,0($sp)
    sw $a0,4($sp)
    sw $a1,8($sp)
    lw $s6,4($sp)
    sw $s6,12($sp)
    lw $s7,12($sp)
    move $a0,$s7
    jal Lprinti
Lable3 : 
    lw $ra,0($sp)
    addu $sp,$sp,16
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

