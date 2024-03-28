    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable1 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    .data
Lable3 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable3
    move $a0,$s6
    jal Lprints
Lable2 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
    jr $ra
Lable0 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    li $s5,123
    negu $s6,$s5
    move $a0,$s6
    jal Lprinti
    jal Lable1
    move $s7,$v0
    li $s5,2147483648
    negu $s6,$s5
    move $a0,$s6
    jal Lprinti
    jal Lable1
    move $s7,$v0
    li $s4,2147483648
    negu $s5,$s4
    negu $s6,$s5
    move $a0,$s6
    jal Lprinti
    jal Lable1
    move $s7,$v0
    li $s3,2147483648
    negu $s4,$s3
    negu $s5,$s4
    negu $s6,$s5
    move $a0,$s6
    jal Lprinti
    jal Lable1
    move $s7,$v0
Lable4 : 
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

