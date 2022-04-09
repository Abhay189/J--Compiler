    .text 
    .globl main 
main: 
    jal Lable0 
    li $v0,10 
    syscall

Lable0 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    .data
Lable2 :
    .byte 97 ,115 ,100 ,102 ,0
    .align 2
    .text
    la $s7,Lable2
    move $a0,$s7
    jal Lprints
    .data
Lable3 :
    .byte 8 ,9 ,10 ,12 ,13 ,34 ,39 ,92 ,0
    .align 2
    .text
    la $s7,Lable3
    move $a0,$s7
    jal Lprints
    .data
Lable4 :
    .byte 1 ,26 ,0
    .align 2
    .text
    la $s7,Lable4
    move $a0,$s7
    jal Lprints
    li $s7,1
    beqz $s7,Lable5
    .data
Lable6 :
    .byte 32 ,97 ,115 ,100 ,102 ,0
    .align 2
    .text
    la $s7,Lable6
    move $a0,$s7
    jal Lprints
Lable5 :
Lable1 : 
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

