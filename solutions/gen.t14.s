    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,12
    sw $ra,0($sp)
    li $s7,0
    sw $s7,4($sp)
    li $s7,1000000
    sw $s7,8($sp)
Lable2 :
    lw $s5,8($sp)
    lw $s4,4($sp)
    subu $s6,$s4,$s5
    lw $s4,4($sp)
    sgt $s7,$s4,$s6
    beqz $s7,Lable3
    lw $s6,8($sp)
    lw $s5,4($sp)
    addu $s4,$s5,$s6
    sw $s4,4($sp)
    j Lable2
Lable3 :
    lw $s5,8($sp)
    lw $s6,4($sp)
    subu $s4,$s6,$s5
    sw $s4,4($sp)
Lable4 :
    li $s6,1
    lw $s5,4($sp)
    subu $s4,$s5,$s6
    lw $s5,4($sp)
    sgt $s7,$s5,$s4
    beqz $s7,Lable5
    li $s4,1
    lw $s6,4($sp)
    addu $s5,$s6,$s4
    sw $s5,4($sp)
    j Lable4
Lable5 :
    .data
Lable6 :
    .byte 109 ,105 ,110 ,105 ,110 ,116 ,32 ,105 ,115 ,32 ,0
    .align 2
    .text
    la $s7,Lable6
    move $a0,$s7
    jal Lprints
    lw $s5,4($sp)
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
Lable1 : 
    lw $ra,0($sp)
    addu $sp,$sp,12
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

