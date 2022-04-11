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
    .data
Lable4 :
    .word 0
    .text
    .data
Lable5 :
    .word 0
    .text
    .data
Lable6 :
    .word 0
    .text
    .data
Lable7 :
    .word 0
    .text
    .data
Lable8 :
    .word 0
    .text
    .data
Lable9 :
    .word 0
    .text
    .data
Lable10 :
    .word 0
    .text
    .data
Lable11 :
    .word 0
    .text
    .data
Lable12 :
    .word 0
    .text
    .data
Lable13 :
    .word 0
    .text
    .data
Lable14 :
    .word 0
    .text
    .data
Lable15 :
    .word 0
    .text
    .data
Lable16 :
    .word 0
    .text
    .data
Lable18 :
    .word 0
    .text
Lable0 : 
    subu $sp,$sp,20
    sw $ra,0($sp)
    li $s7,1
    move $a0,$s7
    jal Lable19
    li $s7,0
    sw $s7,4($sp)
Lable22 :
    li $s6,14
    lw $s5,4($sp)
    sle $s7,$s5,$s6
    beqz $s7,Lable23
    li $s5,0
    lw $s6,4($sp)
    seq $s7,$s6,$s5
    beqz $s7,Lable25
    jal Lable20
    li $s5,100
a case not handled in arithmatic expressions  
    bnez $s5,Lable26
    .data
Lable27 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable27
    j error
Lable26 :
    rem $s6,$s4,$s5
    sw $s6,Lable1
    j Lable24
Lable25 :
    li $s6,1
    lw $s4,4($sp)
    seq $s7,$s4,$s6
    beqz $s7,Lable29
    jal Lable20
    li $s6,100
a case not handled in arithmatic expressions  
    bnez $s6,Lable30
    .data
Lable31 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable31
    j error
Lable30 :
    rem $s4,$s5,$s6
    sw $s4,Lable2
    j Lable28
Lable29 :
    li $s4,2
    lw $s5,4($sp)
    seq $s7,$s5,$s4
    beqz $s7,Lable33
    jal Lable20
    li $s4,100
a case not handled in arithmatic expressions  
    bnez $s4,Lable34
    .data
Lable35 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable35
    j error
Lable34 :
    rem $s5,$s6,$s4
    sw $s5,Lable3
    j Lable32
Lable33 :
    li $s5,3
    lw $s6,4($sp)
    seq $s7,$s6,$s5
    beqz $s7,Lable37
    jal Lable20
    li $s5,100
a case not handled in arithmatic expressions  
    bnez $s5,Lable38
    .data
Lable39 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable39
    j error
Lable38 :
    rem $s6,$s4,$s5
    sw $s6,Lable4
    j Lable36
Lable37 :
    li $s6,4
    lw $s4,4($sp)
    seq $s7,$s4,$s6
    beqz $s7,Lable41
    jal Lable20
    li $s6,100
a case not handled in arithmatic expressions  
    bnez $s6,Lable42
    .data
Lable43 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable43
    j error
Lable42 :
    rem $s4,$s5,$s6
    sw $s4,Lable5
    j Lable40
Lable41 :
    li $s4,5
    lw $s5,4($sp)
    seq $s7,$s5,$s4
    beqz $s7,Lable45
    jal Lable20
    li $s4,100
a case not handled in arithmatic expressions  
    bnez $s4,Lable46
    .data
Lable47 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable47
    j error
Lable46 :
    rem $s5,$s6,$s4
    sw $s5,Lable6
    j Lable44
Lable45 :
    li $s5,6
    lw $s6,4($sp)
    seq $s7,$s6,$s5
    beqz $s7,Lable49
    jal Lable20
    li $s5,100
a case not handled in arithmatic expressions  
    bnez $s5,Lable50
    .data
Lable51 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable51
    j error
Lable50 :
    rem $s6,$s4,$s5
    sw $s6,Lable7
    j Lable48
Lable49 :
    li $s6,7
    lw $s4,4($sp)
    seq $s7,$s4,$s6
    beqz $s7,Lable53
    jal Lable20
    li $s6,100
a case not handled in arithmatic expressions  
    bnez $s6,Lable54
    .data
Lable55 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable55
    j error
Lable54 :
    rem $s4,$s5,$s6
    sw $s4,Lable8
    j Lable52
Lable53 :
    li $s4,8
    lw $s5,4($sp)
    seq $s7,$s5,$s4
    beqz $s7,Lable57
    jal Lable20
    li $s4,100
a case not handled in arithmatic expressions  
    bnez $s4,Lable58
    .data
Lable59 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable59
    j error
Lable58 :
    rem $s5,$s6,$s4
    sw $s5,Lable9
    j Lable56
Lable57 :
    li $s5,9
    lw $s6,4($sp)
    seq $s7,$s6,$s5
    beqz $s7,Lable61
    jal Lable20
    li $s5,100
a case not handled in arithmatic expressions  
    bnez $s5,Lable62
    .data
Lable63 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable63
    j error
Lable62 :
    rem $s6,$s4,$s5
    sw $s6,Lable10
    j Lable60
Lable61 :
    li $s6,10
    lw $s4,4($sp)
    seq $s7,$s4,$s6
    beqz $s7,Lable65
    jal Lable20
    li $s6,100
a case not handled in arithmatic expressions  
    bnez $s6,Lable66
    .data
Lable67 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable67
    j error
Lable66 :
    rem $s4,$s5,$s6
    sw $s4,Lable11
    j Lable64
Lable65 :
    li $s4,11
    lw $s5,4($sp)
    seq $s7,$s5,$s4
    beqz $s7,Lable69
    jal Lable20
    li $s4,100
a case not handled in arithmatic expressions  
    bnez $s4,Lable70
    .data
Lable71 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable71
    j error
Lable70 :
    rem $s5,$s6,$s4
    sw $s5,Lable12
    j Lable68
Lable69 :
    li $s5,12
    lw $s6,4($sp)
    seq $s7,$s6,$s5
    beqz $s7,Lable73
    jal Lable20
    li $s5,100
a case not handled in arithmatic expressions  
    bnez $s5,Lable74
    .data
Lable75 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable75
    j error
Lable74 :
    rem $s6,$s4,$s5
    sw $s6,Lable13
    j Lable72
Lable73 :
    li $s6,13
    lw $s4,4($sp)
    seq $s7,$s4,$s6
    beqz $s7,Lable77
    jal Lable20
    li $s6,100
a case not handled in arithmatic expressions  
    bnez $s6,Lable78
    .data
Lable79 :
    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0
    .align 2
    .text
    la $a0,Lable79
    j error
Lable78 :
    rem $s4,$s5,$s6
    sw $s4,Lable14
    j Lable76
Lable77 :
    li $s4,14
    lw $s5,4($sp)
    seq $s7,$s5,$s4
    beqz $s7,Lable80
    jal Lable20
    li $s4,100
