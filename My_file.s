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
    .data
Lable2 :
    .word 0
    .text
Lable0 : 
    subu $sp,$sp,12
    sw $ra,0($sp)
    li $s7,123
    sw $s7,Lable1
    li $s7,456
    sw $s7,4($sp)
    li $s7,789
    sw $s7,Lable2
    li $s7,42
    sw $s7,Lable2
    lw $s5,Lable2
    li $s4,42
    sw $s6,4($sp)
    lw $s3,4($sp)
    lw $s1,Lable2
    li $s0,42
    sw $s6,Lable1
    li $s7,10
    sw $s7,8($sp)
    lw $s7,Lable1
    move $a0,$s7
    jal Lprinti
    lw $s7,4($sp)
    move $a0,$s7
    jal Lprinti
    lw $s7,Lable2
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

