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
    subu $sp,$sp,4
    sw $ra,0($sp)
    li $s7,12
    sw $s7,Lable1
    jal Lable3
    move $s7,$v0
    li $s4,2
    lw $s3,Lable2
    subu $s5,$s3,$s4
    lw $s3,Lable1
    bnez $s5,Lable5
    .data
Lable6 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable6
    j error
Lable5 :
    div $s6,$s3,$s5
    move $a0,$s6
    jal Lprinti
Lable4 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
    jr $ra
Lable3 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    li $s7,2
    sw $s7,Lable2
Lable7 : 
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

