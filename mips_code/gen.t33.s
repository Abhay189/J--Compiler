    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,8
    sw $ra,0($sp)
Lable2 :
    li $s5,1
    negu $s6,$s5
    lw $s4,0($sp)
    move $s3,$v0
    sne $s7,$s5,$s6
    beqz $s7,Lable3
    jal Lgetchar
    move $s5,$v0
    sw $s5,4($sp)
    lw $s5,4($sp)
    move $a0,$s5
    jal Lprintc
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

