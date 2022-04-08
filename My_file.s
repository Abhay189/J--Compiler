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
Lable3 : 
    subu $sp,$sp,12
    sw $ra,0($sp)
    .data
Lable5 :
    .byte 10 ,40 ,105 ,116 ,39 ,115 ,32 ,111 ,107 ,32 ,105 ,102 ,32 ,116 ,104 ,101 ,32 ,102 ,111 ,108 ,108 ,111 ,119 ,105 ,110 ,103 ,32 ,97 ,114 ,101 ,110 ,39 ,116 ,32 ,48 ,47 ,102 ,97 ,108 ,115 ,101 ,41 ,10 ,0
    .align 2
    .text
    la $s7,Lable5
    move $a0,$s7
    jal Lprints
    .data
Lable6 :
    .byte 9 ,108 ,111 ,99 ,97 ,108 ,32 ,105 ,110 ,116 ,32 ,100 ,101 ,102 ,97 ,117 ,108 ,116 ,32 ,118 ,97 ,108 ,117 ,101 ,58 ,32 ,0
    .align 2
    .text
    la $s7,Lable6
    move $a0,$s7
    jal Lprints
    lw $s7,0($sp)
    move $a0,$s7
    jal Lprinti
    .data
Lable7 :
    .byte 10 ,0
    .align 2
    .text
    la $s7,Lable7
    move $a0,$s7
    jal Lprints
    .data
Lable8 :
    .byte 9 ,108 ,111 ,99 ,97 ,108 ,32 ,98 ,111 ,111 ,108 ,101 ,97 ,110 ,32 ,100 ,101 ,102 ,97 ,117 ,108 ,116 ,32 ,118 ,97 ,108 ,117 ,101 ,58 ,32 ,0
    .align 2
    .text
    la $s7,Lable8
    move $a0,$s7
    jal Lprints
    lw $s6,0($sp)
    move $a0,$s6
    jal Lprintb
    .data
Lable9 :
    .byte 10 ,0
    .align 2
    .text
    la $s7,Lable9
    move $a0,$s7
    jal Lprints
    li $s7,123
    sw $s7,4($sp)
    li $s7,1
    sw $s7,8($sp)
Lable4 : 
    lw $ra,0($sp)
    addu $sp,$sp,12
    jr $ra
Lable0 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    .data
Lable11 :
    .byte 103 ,108 ,111 ,98 ,97 ,108 ,32 ,105 ,110 ,116 ,32 ,100 ,101 ,102 ,97 ,117 ,108 ,116 ,32 ,118 ,97 ,108 ,117 ,101 ,58 ,32 ,0
    .align 2
    .text
    la $s7,Lable11
    move $a0,$s7
    jal Lprints
    lw $s7,Lable1
    move $a0,$s7
    jal Lprinti
    .data
Lable12 :
    .byte 10 ,0
    .align 2
    .text
    la $s7,Lable12
    move $a0,$s7
    jal Lprints
    .data
Lable13 :
    .byte 103 ,108 ,111 ,98 ,97 ,108 ,32 ,98 ,111 ,111 ,108 ,101 ,97 ,110 ,32 ,100 ,101 ,102 ,97 ,117 ,108 ,116 ,32 ,118 ,97 ,108 ,117 ,101 ,58 ,32 ,0
    .align 2
    .text
    la $s7,Lable13
    move $a0,$s7
    jal Lprints
    lw $s6,Lable2
    move $a0,$s6
    jal Lprintb
    .data
Lable14 :
    .byte 10 ,0
    .align 2
    .text
    la $s7,Lable14
    move $a0,$s7
    jal Lprints
    jal Lable3
    jal Lable3
Lable10 : 
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
    .byte 116 ,114 ,117 ,101 ,0
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

