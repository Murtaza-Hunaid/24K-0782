; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter first number: ",0
    msg2 BYTE "Enter second number: ",0
    msg3 BYTE "Product = ",0
    num1 DWORD ?
    num2 DWORD ?
    product DWORD 0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    mov num1, eax
    mov edx, OFFSET msg2
    call WriteString
    call ReadInt
    mov num2, eax
    mov eax, num1        
    mov ebx, num2       
    mov ecx, 0          

multiply_loop:
    test ebx, 1         
    jz skip_add
    add ecx, eax 
    
skip_add:
    shl eax, 1           
    shr ebx, 1          
    cmp ebx, 0
    jne multiply_loop

    mov edx, OFFSET msg3
    call WriteString
    mov eax, ecx
    call WriteDec
    call crlf
    exit
main ENDP
END main
