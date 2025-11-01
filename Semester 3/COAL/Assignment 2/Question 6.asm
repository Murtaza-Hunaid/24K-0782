; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    op1 SDWORD 15
    op2 SDWORD 25
    x SDWORD 10
    y SDWORD 20
    z SDWORD 0

.code
main PROC
while_start:
    mov eax, op1
    cmp eax, op2
    jg while_end

    mov eax, op1
    cmp eax, x
    jl else_part
    cmp eax, y
    jg else_part

then_part:
    add z, 10
    jmp after_if

else_part:
    sub z, 10

after_if:
    dec op1
    jmp while_start

while_end:
    mov eax, z
    call WriteInt
    call Crlf
    exit
main ENDP
END main
