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
Lable2 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    li $s7,12345
    sw $s7,Lable1
Lable3 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
    jr $ra
Lable0 : 
    subu $sp,$sp,8
    sw $ra,0($sp)
    jal Lable2
    move $s7,$v0
    lw $s6,0($sp)
    move $a0,$s6
    jal Lprinti
    li $s7,0
    sw $s7,4($sp)
    lw $s5,4($sp)
    move $a0,$s5
    jal Lprintb
Lable4 : 
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

