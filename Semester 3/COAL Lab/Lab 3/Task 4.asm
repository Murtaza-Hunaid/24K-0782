; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.code
main PROC
	mov ebx, 90
	add ebx, 5Ah
	add ebx, 01011010b
	add ebx, 66

	mov eax, ebx
	call WriteInt
	exit
main ENDP
END main
