.pos 0x100

    #  tmp = 0;
    ld $0, r0      #r0=0
    ld $tmp,r1     #r1=address of tmp
    st r0,(r1)     #tmp=0

    #  tos = 0; 
    ld $tos,r2     #r2=address of tos
    st r0,(r2)     #tos=0

    #  s[tos] = a[0];
    ld $a, r3        #r3=address of a = a[0]
    ld 0(r3), r3     #r3 = a[0]
    ld $s, r4        #r4=address of s = s[0]
    ld (r2),r2       #r2=tos
    shl $2,r2        #r2=4r2
    add r4,r2        #r2=r2+r4 = address of s[tos]
    st r3,(r2)       #s[tos] = a[0];

    #  tos++;
    ld $tos,r5     #r5=address of tos
    ld 0(r5),r5    #r5=tos
    inc r5         #r5=tos++
    ld $tos,r6     #r6=address of tos
    st r5, (r6)    #tos++

    #  s[tos] = a[1];
    ld $a, r3        #r3=address of a = a[0]
    ld 4(r3), r3     #r3 = a[1]
    ld $s, r4        #r4=address of s = s[0]
    shl $2,r5        #r5=4r5 tos=4tos
    add r4,r5        #r5=r5+r4 = address of s[tos]
    st r3,(r5)       #s[tos] = a[1];

    #  tos++;
    ld $tos,r5     #r5=address of tos
    ld 0(r5),r5    #r5=tos
    inc r5         #r5=tos++
    ld $tos,r6     #r6=address of tos
    st r5, (r6)    #tos++


    #  s[tos] = a[2];
    ld $a, r3        #r3=address of a = a[0]
    ld 8(r3), r3     #r3 = a[2]
    ld $s, r4        #r4=address of s = s[0]
    shl $2,r5        #r5=4r5 tos=4tos
    add r4,r5        #r5=r5+r4 = address of s[tos]
    st r3,(r5)       #s[tos] = a[2];

    #  tos++;
    ld $tos,r5     #r5=address of tos
    ld 0(r5),r5    #r5=tos
    inc r5         #r5=tos++
    ld $tos,r6     #r6=address of tos
    st r5, (r6)    #tos++


    #  tos--;
    ld $tos,r5     #r5=address of tos
    ld 0(r5),r5    #r5=tos
    dec r5         #r5=tos--
    ld $tos,r6     #r6=address of tos
    st r5, (r6)    #tos--


    #  tmp = s[tos];
    ld (r4,r5,4),r6 #r6=s[tos]
    st r6,(r1) #tmp=s[tos]
    #  tos--;
     ld $tos,r5     #r5=address of tos
    ld 0(r5),r5    #r5=tos
    dec r5         #r5=tos--
    ld $tos,r6     #r6=address of tos
    st r5, (r6)    #tos--
    #  tmp = tmp + s[tos];
    ld (r4,r5,4),r6 #r6=s[tos]
    ld (r1),r2 #r2=tmp
    add r6,r2 #r2=r2+r6 =tmp+s[tos]
    st r2, (r1) #tmp=tmp+s[tos]
    #  tos--;
     ld $tos,r5     #r5=address of tos
    ld 0(r5),r5    #r5=tos
    dec r5         #r5=tos--
    ld $tos,r6     #r6=address of tos
    st r5, (r6)    #tos--
    #  tmp = tmp + s[tos];
    ld (r4,r5,4),r6 #r6=s[tos]
    ld (r1),r2 #r2=tmp
    add r6,r2 #r2=r2+r6 =tmp+s[tos]
    st r2, (r1) #tmp=tmp+s[tos]
  

    halt

.pos 0x200
# Data area

a:  .long 1             # a[0]
    .long 2             # a[1]
    .long 3             # a[2]
s:  .long 0             # s[0]
    .long 0             # s[1]
    .long 0             # s[2]
    .long 0             # s[3]
    .long 0             # s[4]
tos:  .long 1            # tos
tmp:  .long 1          #tmp

