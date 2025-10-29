; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    marks DWORD 50 DUP(?)              
    count_pass DWORD 0
    count_fail DWORD 0
    num_stds DWORD ?
    msg1 BYTE "Enter number of students: ",0
    msg2 BYTE "Enter marks: ",0
    msg3 BYTE "Passed Students= ",0
    msg4 BYTE "Failed students= ",0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    mov num_stds, eax
    mov ecx, eax
    mov esi, OFFSET marks

inputLoop:
    mov edx, OFFSET msg2
    call WriteString
    call ReadInt
    mov [esi], eax
    add esi, TYPE marks
    loop inputLoop

    call CountGrades
    mov edx, OFFSET msg3
    call WriteString
    mov eax, count_pass
    call WriteDec
    call crlf

    mov edx, OFFSET msg4
    call WriteString
    mov eax, count_fail
    call WriteDec
    call crlf
    exit
main ENDP

CountGrades PROC
    mov ecx, num_stds
    mov esi, OFFSET marks

nextMark:
    mov eax, [esi]
    cmp eax, 50
    jl fail
    inc count_pass
    jmp cont

fail:
    inc count_fail

cont:
    add esi, TYPE marks
    loop nextMark
    ret
CountGrades ENDP
END main
