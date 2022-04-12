    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

    .data
Lable2 :
    .word 0
    .text
Lable1 : 
    subu $sp,$sp,8
    sw $ra,0($sp)
    jal Lgetchar
    move $s6,$v0
    sw $s6,4($sp)
    lw $s6,Lable2
    lw $s5,4($sp)
    sne $s7,$s5,$s6
    beqz $s7,Lable4
    jal Lable1
    move $s7,$v0
    lw $s5,4($sp)
    move $a0,$s5
    jal Lprintc
Lable4 :
Lable3 : 
    lw $ra,0($sp)
    addu $sp,$sp,8
    jr $ra
Lable0 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    li $s7,10
    sw $s7,Lable2
    jal Lable1
    move $s7,$v0
Lable5 : 
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

Lgetchar:
    li $v0, 12
    syscall
    jr $ra

error:
    li $v0, 4
    syscall
    li $v0, 10
    syscall

