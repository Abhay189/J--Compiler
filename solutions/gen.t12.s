    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,20
    sw $ra,0($sp)
    li $s7,2
    sw $s7,4($sp)
    li $s7,1
    sw $s7,8($sp)
    li $s7,0
    sw $s7,12($sp)
    .data
Lable2 :
    .byte 102 ,105 ,98 ,40 ,48 ,41 ,32 ,61 ,32 ,48 ,10 ,0
    .align 2
    .text
    la $s7,Lable2
    move $a0,$s7
    jal Lprints
    .data
Lable3 :
    .byte 102 ,105 ,98 ,40 ,49 ,41 ,32 ,61 ,32 ,49 ,10 ,0
    .align 2
    .text
    la $s7,Lable3
    move $a0,$s7
    jal Lprints
Lable4 :
    li $s6,47
    lw $s5,4($sp)
    slt $s7,$s5,$s6
    beqz $s7,Lable5
    .data
Lable6 :
    .byte 102 ,105 ,98 ,40 ,0
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
    .byte 41 ,32 ,61 ,32 ,0
    .align 2
    .text
    la $s5,Lable7
    move $a0,$s5
    jal Lprints
    lw $s6,12($sp)
    lw $s4,8($sp)
    addu $s5,$s4,$s6
    sw $s5,16($sp)
    lw $s5,16($sp)
    move $a0,$s5
    jal Lprinti
    lw $s5,8($sp)
    sw $s5,12($sp)
    lw $s5,16($sp)
    sw $s5,8($sp)
    .data
Lable8 :
    .byte 10 ,0
    .align 2
    .text
    la $s5,Lable8
    move $a0,$s5
    jal Lprints
    li $s4,1
    lw $s6,4($sp)
    addu $s5,$s6,$s4
    sw $s5,4($sp)
    j Lable4
Lable5 :
Lable1 : 
    lw $ra,0($sp)
    addu $sp,$sp,20
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

