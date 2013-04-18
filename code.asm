.model small
.stack
.data
b3 dw 0
b4 dw 0
.code
printf proc
push bx
push cx
push dx
mov cx,0
mov bx,10
loop1:
mov dx,0
div bx
push dx
inc cx
cmp ax,0
jne loop1
loop2:
pop dx
mov ah,02h
add dl,'0'
int 21h
loop loop2
pop dx
pop cx
pop bx
ret
printf endp
scanf proc
push bx
push cx
push dx
mov bx,10
mov ax,0
loop3:
push ax
mov ah,01h
int 21h
cmp al,0dh
je finish
sub al,'0'
mov cl,al
pop ax
mul bx
add ax,cx
jmp loop3
finish:
pop ax
pop dx
pop cx
pop bx
ret
scanf endp



start proc


call scanf
mov b3, AX
call scanf
mov b4, AX
label_11:
mov AX,b3
push AX
mov AX,0
pop DX
cmp AX,DX
jle true_11_9383
jmp false_11_9383
true_11_9383:
mov AX, 1
jmp resume_11_9383
false_11_9383:
mov AX, 0
resume_11_9383:
cmp AX,1
je label_11
ret


start endp
end start
