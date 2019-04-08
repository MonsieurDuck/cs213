.pos 0x100


    # i = a[3]
    ld $a, r0         #r0=address of a
    ld $i, r1         #r1=address of i
    ld 12(r0),r2      #r2 = a[3]
    st r2,(r1)        #i = a[3]

    # i = a[i]
    ld (r1),r3        #r3 = i
    ld (r0,r3,4),r4   #r4 = a[i]
    st r4,(r1)        #i = a[i]

    # p = &j
    ld $p,r2          #r2=address of p
    ld $j,r3          #r3=address of j
    st r3,(r2)        #p=&j

    # *p = 4
    ld $4,r4          #r4=4  
    st r4,(r3)        # *p=4   the memory in the adrress (p point to) is 4 ==> m[&j] = 4 

    # p = &a[a[2]]
    ld $a, r0         #r0=address of a= a[0]
    ld 8(r0),r1       #r1=a[2]
    ld (r0,r1,4),r2   #r2=a[r1] =a[a[2]]
    shl $2,r1         #r1=4r1
    add r0,r1         #r1=r1+r0
    ld $p,r3          #r3=address of p
    st r1,(r3)        #p=&a[a[2]]

    # *p = *p + a[4]
    ld $a, r0         #r0=address of a
    ld $4,r1          #r1=4
    ld (r0,r1,4),r2   #r2=a[4]
    ld (r3),r4        #r4=p
    ld (r4),r5        #r5=*p
    add r2, r5        #r5= r2+r5 = a[4] + *p  
    st r5,(r4)        # m[&p] = r5 = *p +a[4] 

    halt

.pos 0x200
# Data area

a:  .long 0             # a[0]
    .long 0             # a[1]
    .long 2             # a[2]
    .long 1             # a[3]
    .long 3             # a[4]
    .long 0             # a[5]
    .long 0             # a[6]
    .long 0             # a[7]
    .long 0             # a[8]
    .long 0             # a[9]
i:  .long 0             # i
j:  .long 0             # j
p:  .long j             # j

