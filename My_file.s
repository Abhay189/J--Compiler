    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,8
    sw $ra,0($sp)
    jal Lable1
    lw $s4,0($sp)
a case not handled in arithmatic expressions  
    xori $s6,$s5,1
    sw $s6,4($sp)
    lw $s6,4($sp)
    move $a0,$s6
    jal Lprintb
Lable2 : 
    lw $ra,0($sp)
    addu $sp,$sp,8
    jr $ra
Lable1 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    li $s6,1
    move $v0,$s6
    j Lable3
Lable3 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
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

