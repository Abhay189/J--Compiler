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
    la $s5,Lable5
    move $a0,$s5
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
    lw $s6,4($sp)
    move $a0,$s6
    jal Lable1
    move $s5,$v0
    move $s7,$s5
    move $a0,$s7
    jal Lprinti
    .data
Lable7 :
    .byte 10 ,0
    .align 2
    .text
    la $s5,Lable7
    move $a0,$s5
    jal Lprints
    li $s6,1
    lw $s4,4($sp)
    addu $s5,$s4,$s6
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
    lw $s4,4($sp)
    seq $s7,$s4,$s5
    beqz $s7,Lable9
    li $s4,0
    move $v0,$s4
    j Lable8
Lable9 :
    li $s4,1
    lw $s5,4($sp)
    seq $s4,$s5,$s4
    beqz $s4,Lable10
    li $s5,1
    move $v0,$s5
    j Lable8
Lable10 :
    li $s2,2
    lw $s1,4($sp)
    subu $s3,$s1,$s2
    move $a0,$s3
    move $s4,$v0
    li $s2,1
    lw $s0,4($sp)
    subu $s1,$s0,$s2
    move $a0,$s1
    move $s3,$v0
    addu $s5,$s3,$s4
    move $v0,$s5
    j Lable8
    jal Lable1
    move $s5,$v0
    jal Lable1
    move $s5,$v0
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

