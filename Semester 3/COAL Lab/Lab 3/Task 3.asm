; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
	num1 DWORD 500
	num2 DWORD 200

.code
main PROC
	mov ebx, 500
	mov ecx, 200

	add ebx, ecx
	mov eax, ebx
	call WriteInt	
	exit
main ENDP
END main
