.pos 0x100
ld   $0x0, r0            # r0 = temp_i = 0
ld   $a, r1              # r1 = address of a[0]
ld   $b, r6              #r6=address of b[0]
ld   $0x0, r2            # r2 = temp_c = 0
ld   $n, r4               # r4 = address of n
ld (r4),r4               #r4=n
not r4                    #r4=~n
inc r4                    #r4=-n
loop:            mov  r0, r5              # r5 = temp_i
add  r4, r5              # r5 = temp_i-n
beq  r5, end_loop        # if temp_i=n goto +4
ld $base,r3
ld (r1, r0, 4), r3       # r3 = a[temp_i]
ld (r6, r0, 4), r7       #r7=b[temp_i]
not r7                   #r7=!b[temp_i]
inc r7                   #r7=-b[temp_i]
add r3,r7                #r7=a[temp_i]-b[temp_i]
bgt r7, then             # if(a[temp_i]>b[temp_i]) goto then
br end_if                # if(a[temp_i<=b[temp_i]) goto end_if
then: inc r2              # temp_c += 1
end_if:inc  r0                  # temp_i++
br   loop                # goto -7
end_loop:        ld   $c, r1              # r1 = address of s
st   r2, 0x0(r1)         # c = temp_c
st   r0, 0x4(r1)         # i = temp_i
halt
.pos 0x1000

c:            .long 0x00000000
i:            .long 0xffffffff # i
n:            .long 0x00000005  #n
a:            .long 0x0000000a  # a[0]
              .long 0x00000014  #a[1]
              .long 0x0000001e  #a[2]
              .long 0x00000028  #a[3]
              .long 0x00000032 #a[4]
b:            .long 0x0000000b #b[0]
              .long 0x00000014 #b[1]
              .long 0x0000001c #b[2]
              .long 0x0000002c #b[3]
              .long 0x00000030 #b[4]



