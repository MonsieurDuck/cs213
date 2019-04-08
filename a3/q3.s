.pos 0x100

  # a = 3;
  ld $3,r0  #r0=3
  ld $a,r1  #r1=address of a
  st r0,(r1) #a=3

  #p = &a;
  ld $p,r2  #r2=address of p
  st r1,(r2) #p = &a

  #*p = *p - 1;
  ld (r2),r1 #r1=p
  ld (r1),r3 #r3=*p
  dec r3  #r3=*p-1
  st r3,(r1) #*p = *p - 1

  #p = &b[0];
  ld $b,r4 #r4=address of b[0]
  st r4,(r2)

  #p++;
  ld (r2),r5  #r5=p
  inca r5  #p++
  st r5,(r2) #p=p++

  #p[a] = b[a];
  ld (r1),r1 #r1=a=3
  ld (r4,r1,4),r6  #r6=b[a]
  ld (r2),r7  #r7=address of b[1]
  st r6,(r7,r1,4) #p[a]=b[a]

  #*(p+3) = b[0];
  ld (r4),r4 #r4=b[0]
  st r4,12(r7)  #*(p+3)=b[0]

    halt

.pos 0x200
# Data area

a:  .long 0             # a
b:  .long 4             # b[0]
    .long 0             # b[1]
    .long 2             # b[2]
    .long 1             # b[3]
    .long 3             # b[4]
p:  .long 0             # p

