.pos 0x100
ld $b, r0 #r0=address of b
ld (r0),r1 #r1=value of b
mov r1, r3 #copy b vlue to r3
inc r3 # r3<-r3+1
inca r3 #r3<-r3+4
shr $1, r3 #r3<-r3/2
and r1, r3 # r3<-r3&r1
shl $2, r3 #r3<-r3<<2
ld $a,r2 #r2=address of a
st r3,(r2) # r2=r3
halt










.pos 0x1000
a:           .long 0xffffffff
.pos 0x2000
b:           .long 0x00000001
