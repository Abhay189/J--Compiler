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
    lw $s6,Lable2
    sw $s6,4($sp)
    lw $s7,4($sp)
    sw $s7,Lable1
    li $s7,10
    sw $s7,8($sp)
    lw $s6,Lable1
    move $a0,$s6
    jal Lprinti
    lw $s6,8($sp)
    move $a0,$s6
    jal Lprintc
    lw $s6,4($sp)
    move $a0,$s6
    jal Lprinti
    lw $s6,8($sp)
    move $a0,$s6
    jal Lprintc
    lw $s6,Lable2
    move $a0,$s6
    jal Lprinti
    lw $s6,8($sp)
    move $a0,$s6
    jal Lprintc
Lable3 : 
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

