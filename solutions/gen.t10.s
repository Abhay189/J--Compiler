    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,8
    sw $ra,0($sp)
    li $s7,0
    sw $s7,4($sp)
Lable3 :
    li $s6,46
    lw $s5,4($sp)
    sle $s7,$s5,$s6
    beqz $s7,Lable4
    .data
Lable5 :
    .byte 102 ,105 ,98 ,40 ,0
    .align 2
    .text
    la $s7,Lable5
    move $a0,$s7
    jal Lprints
    lw $s5,4($sp)
    move $a0,$s5
    jal Lprinti
    .data
Lable6 :
    .byte 41 ,32 ,61 ,32 ,0
    .align 2
    .text
    la $s5,Lable6
    move $a0,$s5
    jal Lprints
    lw $s5,4($sp)
    move $a0,$s5
    jal Lable1
    lw $s4,4($sp)
a case not handled in arithmatic expressions  
    move $a0,$s5
    jal Lprinti
    .data
Lable7 :
    .byte 10 ,0
    .align 2
    .text
    la $s5,Lable7
    move $a0,$s5
    jal Lprints
    li $s3,1
    lw $s2,4($sp)
    addu $s5,$s2,$s3
    sw $s5,4($sp)
    j Lable3
Lable4 :
Lable2 : 
    lw $ra,0($sp)
    addu $sp,$sp,8
    jr $ra
Lable1 : 
    subu $sp,$sp,8
    sw $ra,0($sp)
    sw $a0,4($sp)
    li $s5,0
    lw $s2,4($sp)
    seq $s5,$s2,$s5
    beqz $s5,Lable9
    li $s2,0
    move $v0,$s2
    j Lable8
Lable9 :
    li $s2,1
    lw $s5,4($sp)
    seq $s2,$s5,$s2
    beqz $s2,Lable10
    li $s5,1
    move $v0,$s5
    j Lable8
Lable10 :
    li $s0,2
    lw $t9,4($sp)
    subu $s1,$t9,$s0
a case not handled in arithmatic expressions  
    li $t7,1
    lw $t6,4($sp)
    subu $t8,$t6,$t7
a case not handled in arithmatic expressions  
    addu $s5,$t9,$s2
    move $v0,$s5
    j Lable8
    jal Lable1
    jal Lable1
Lable8 : 
    lw $ra,0($sp)
    addu $sp,$sp,8
    jr $ra

Lprints: 
    li	$v0, 4
    syscall
    jr $ra

    .data
LTrue : 
    .byte 116 ,114 ,117 ,101 ,0
    .align 2
    .text
    .data
LFalse : 
    .byte 102 ,97 ,108 ,115 ,101 ,0
    .align 2
    .text
Lprintb: 
    li $t0,0
    li $t1,1
    beq $a0,$t0,LFal
    beq $a0,$t1,LTru
    jr $ra
LFal: 
    la $t0,LFalse
    move $a0,$t0
    li	$v0, 4
    syscall
    jr $ra
LTru: 
    la $t0,LTrue
    move $a0,$t0
    li	$v0, 4
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

Lgetchar:
    li $v0, 12
    syscall
    jr $ra

error:
    li $v0, 4
    syscall
    li $v0, 10
    syscall

