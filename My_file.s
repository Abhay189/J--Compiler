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
Lable2 :
    li $s6,20
    lw $s5,4($sp)
    slt $s7,$s5,$s6
    beqz $s7,Lable3
    lw $s5,4($sp)
    move $a0,$s5
    jal Lprinti
    li $s5,15
    lw $s6,4($sp)
    seq $s5,$s6,$s5
    beqz $s5,Lable4
    j Lable3
Lable4 :
    li $s5,1
    lw $s4,4($sp)
    addu $s6,$s4,$s5
    sw $s6,4($sp)
    j Lable2
Lable3 :
Lable1 : 
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

