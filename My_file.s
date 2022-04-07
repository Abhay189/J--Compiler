    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,8
    sw $ra,0($sp)
    li $s5,1259
    li $s3,78
    li $s1,9
    li $s0,8
    mul $s2,$s1,$s0
    mul $s4,$s3,$s2
    subu $s6,$s5,$s4
    sw $s6,4($sp)
Lable1 : 
    lw $ra,0($sp)
    addu $sp,$sp,8
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

