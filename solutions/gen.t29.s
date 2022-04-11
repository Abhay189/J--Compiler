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
    .data
Lable3 :
    .word 0
    .text
Lable4 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    .data
Lable10 :
    .byte 101 ,118 ,97 ,108 ,117 ,97 ,116 ,101 ,100 ,32 ,65 ,10 ,0
    .align 2
    .text
    la $s7,Lable10
    move $a0,$s7
    jal Lprints
    lw $s6,Lable1
    move $v0,$s6
    j Lable9
Lable9 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
    jr $ra
Lable5 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    .data
Lable12 :
    .byte 101 ,118 ,97 ,108 ,117 ,97 ,116 ,101 ,100 ,32 ,66 ,10 ,0
    .align 2
    .text
    la $s6,Lable12
    move $a0,$s6
    jal Lprints
    lw $s6,Lable2
    move $v0,$s6
    j Lable11
Lable11 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
    jr $ra
Lable6 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    .data
Lable14 :
    .byte 101 ,118 ,97 ,108 ,117 ,97 ,116 ,101 ,100 ,32 ,67 ,10 ,0
    .align 2
    .text
    la $s6,Lable14
    move $a0,$s6
    jal Lprints
    lw $s6,Lable3
    move $v0,$s6
    j Lable13
Lable13 : 
    lw $ra,0($sp)
    addu $sp,$sp,4
    jr $ra
Lable7 : 
    subu $sp,$sp,16
    sw $ra,0($sp)
    sw $a0,4($sp)
    sw $a1,8($sp)
    sw $a2,12($sp)
    lw $s6,4($sp)
    sw $s6,Lable1
    lw $s6,8($sp)
    sw $s6,Lable2
    lw $s6,12($sp)
    sw $s6,Lable3
    .data
Lable16 :
    .byte 105 ,102 ,32 ,40 ,40 ,65 ,32 ,38 ,38 ,32 ,66 ,41 ,32 ,124 ,124 ,32 ,67 ,41 ,32 ,123 ,46 ,46 ,46 ,125 ,32 ,101 ,108 ,115 ,101 ,32 ,123 ,46 ,46 ,46 ,125 ,44 ,32 ,119 ,105 ,116 ,104 ,32 ,65 ,61 ,0
    .align 2
    .text
    la $s6,Lable16
    move $a0,$s6
    jal Lprints
    lw $s6,Lable1
    move $a0,$s6
    jal Lprintb
    .data
Lable17 :
    .byte 32 ,66 ,61 ,0
    .align 2
    .text
    la $s6,Lable17
    move $a0,$s6
    jal Lprints
    lw $s6,Lable2
    move $a0,$s6
    jal Lprintb
    .data
Lable18 :
    .byte 32 ,67 ,61 ,0
    .align 2
    .text
    la $s6,Lable18
    move $a0,$s6
    jal Lprints
    lw $s6,Lable3
    move $a0,$s6
    jal Lprintb
    .data
Lable19 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable19
    move $a0,$s6
    jal Lprints
a case not handled in arithmatic expressions  
a case not handled in arithmatic expressions  
a case not handled in arithmatic expressions  
    move $s4,$s3
    beqz $s4,Lable22
    move $s4,$s1
    beqz $s4,Lable22
Lable22 :
    move $s6,$s6
    beqz $s4,Lable23
    move $s6,$s4
Lable23 :
    beqz $s6,Lable21
    jal Lable6
    jal Lable5
    jal Lable4
    .data
Lable24 :
    .byte 105 ,102 ,45 ,112 ,97 ,114 ,116 ,32 ,101 ,120 ,101 ,99 ,117 ,116 ,101 ,100 ,10 ,0
    .align 2
    .text
    la $s6,Lable24
    move $a0,$s6
    jal Lprints
    j Lable20
Lable21 :
    .data
Lable25 :
    .byte 101 ,108 ,115 ,101 ,45 ,112 ,97 ,114 ,116 ,32 ,101 ,120 ,101 ,99 ,117 ,116 ,101 ,100 ,10 ,0
    .align 2
    .text
    la $s6,Lable25
    move $a0,$s6
    jal Lprints
Lable20 :
Lable15 : 
    lw $ra,0($sp)
    addu $sp,$sp,16
    jr $ra
Lable8 : 
    subu $sp,$sp,20
    sw $ra,0($sp)
    sw $a0,4($sp)
    sw $a1,8($sp)
    sw $a2,12($sp)
    lw $s4,4($sp)
    sw $s4,Lable1
    lw $s4,8($sp)
    sw $s4,Lable2
    lw $s4,12($sp)
    sw $s4,Lable3
    .data
Lable27 :
    .byte 120 ,32 ,61 ,32 ,40 ,65 ,32 ,38 ,38 ,32 ,33 ,66 ,41 ,32 ,124 ,124 ,32 ,67 ,44 ,32 ,119 ,105 ,116 ,104 ,32 ,65 ,61 ,0
    .align 2
    .text
    la $s6,Lable27
    move $a0,$s6
    jal Lprints
    lw $s4,Lable1
    move $a0,$s4
    jal Lprintb
    .data
Lable28 :
    .byte 32 ,66 ,61 ,0
    .align 2
    .text
    la $s6,Lable28
    move $a0,$s6
    jal Lprints
    lw $s4,Lable2
    move $a0,$s4
    jal Lprintb
    .data
Lable29 :
    .byte 32 ,67 ,61 ,0
    .align 2
    .text
    la $s6,Lable29
    move $a0,$s6
    jal Lprints
    lw $s4,Lable3
    move $a0,$s4
    jal Lprintb
    .data
Lable30 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable30
    move $a0,$s6
    jal Lprints
    jal Lable6
    jal Lable5
    jal Lable4
a case not handled in arithmatic expressions  
a case not handled in arithmatic expressions  
    xori $t9,$t8,1
a case not handled in arithmatic expressions  
    move $s3,$t9
    beqz $s3,Lable31
    move $s3,$t8
    beqz $s3,Lable31
Lable31 :
    move $s4,$s6
    beqz $s3,Lable32
    move $s4,$s3
Lable32 :
    sw $s4,16($sp)
    .data
Lable33 :
    .byte 120 ,61 ,0
    .align 2
    .text
    la $s6,Lable33
    move $a0,$s6
    jal Lprints
    lw $s4,16($sp)
    move $a0,$s4
    jal Lprintb
    .data
Lable34 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable34
    move $a0,$s6
    jal Lprints
Lable26 : 
    lw $ra,0($sp)
    addu $sp,$sp,20
    jr $ra
Lable0 : 
    subu $sp,$sp,4
    sw $ra,0($sp)
    jal Lable7
    .data
Lable36 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable36
    move $a0,$s6
    jal Lprints
    jal Lable7
    .data
Lable37 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable37
    move $a0,$s6
    jal Lprints
    jal Lable7
    .data
Lable38 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable38
    move $a0,$s6
    jal Lprints
    jal Lable7
    .data
Lable39 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable39
    move $a0,$s6
    jal Lprints
    jal Lable7
    .data
Lable40 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable40
    move $a0,$s6
    jal Lprints
    jal Lable7
    .data
Lable41 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable41
    move $a0,$s6
    jal Lprints
    jal Lable7
    .data
Lable42 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable42
    move $a0,$s6
    jal Lprints
    jal Lable7
    .data
Lable43 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable43
    move $a0,$s6
    jal Lprints
    jal Lable8
    .data
Lable44 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable44
    move $a0,$s6
    jal Lprints
    jal Lable8
    .data
Lable45 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable45
    move $a0,$s6
    jal Lprints
    jal Lable8
    .data
Lable46 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable46
    move $a0,$s6
    jal Lprints
    jal Lable8
    .data
Lable47 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable47
    move $a0,$s6
    jal Lprints
    jal Lable8
    .data
Lable48 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable48
    move $a0,$s6
    jal Lprints
    jal Lable8
    .data
Lable49 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable49
    move $a0,$s6
    jal Lprints
    jal Lable8
    .data
Lable50 :
    .byte 10 ,0
    .align 2
    .text
    la $s6,Lable50
    move $a0,$s6
    jal Lprints
    jal Lable8
Lable35 : 
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

