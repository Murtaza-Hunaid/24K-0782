; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter first number: ", 0
    msg2 BYTE "Enter second number: ", 0
    msg3 BYTE "Enter third number: ", 0
    msgU BYTE "Largest (Unsigned) = ", 0
    msgS BYTE "Largest (Signed) = ", 0
    num1 DWORD ?
    num2 DWORD ?
    num3 DWORD ?
    largestU DWORD ?
    largestS DWORD ?

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

    mov edx, OFFSET msg3
    call WriteString
    call ReadInt
    mov num3, eax

    mov eax, num1
    mov largestU, eax
    mov ebx, num2
    cmp eax, ebx
    jae skipU1
    mov largestU, ebx
    mov eax, ebx

skipU1:
    mov ebx, num3
    cmp eax, ebx
    jae skipU2
    mov largestU, ebx

skipU2:

    mov edx, OFFSET msgU
    call WriteString
    mov eax, largestU
    call WriteInt
    call Crlf

    mov eax, num1
    mov largestS, eax
    mov ebx, num2
    cmp eax, ebx
    jge skipS1
    mov largestS, ebx
    mov eax, ebx

skipS1:
    mov ebx, num3
    cmp eax, ebx
    jge skipS2
    mov largestS, ebx

skipS2:
    mov edx, OFFSET msgS
    call WriteString
    mov eax, largestS
    call WriteInt
    call Crlf
    exit
main ENDP
END main
