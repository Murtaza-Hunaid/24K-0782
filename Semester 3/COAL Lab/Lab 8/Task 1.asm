; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter number ",0
    msg2 BYTE ": ",0
    msg_pos BYTE "Positive numbers: ",0
    msg_neg BYTE "Negative numbers: ",0
    msg_zero BYTE "Zeros: ",0
    pos_count DWORD 0
    neg_count DWORD 0
    zero_count DWORD 0

.code
main PROC
    mov ecx, 5              
    mov ebx, 1        

input_loop:
    mov edx, OFFSET msg1
    call WriteString
    mov eax, ebx
    call WriteDec
    mov edx, OFFSET msg2
    call WriteString
    call ReadInt
    cmp eax, 0
    je zero_case
    jl neg_case

pos_case:
    inc pos_count
    jmp next_input

neg_case:
    inc neg_count
    jmp next_input

zero_case:
    inc zero_count

next_input:
    inc ebx
    loop input_loop

    mov edx, OFFSET msg_pos
    call WriteString
    mov eax, pos_count
    call WriteDec
    call Crlf

    mov edx, OFFSET msg_neg
    call WriteString
    mov eax, neg_count
    call WriteDec
    call Crlf

    mov edx, OFFSET msg_zero
    call WriteString
    mov eax, zero_count
    call WriteDec
    call Crlf
    exit
main ENDP
END main
