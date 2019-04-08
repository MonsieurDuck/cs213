.pos 0x1000
                 ld $s,r0         # r0 = & s
                 ld $i,r1         #r1=&i
                 ld (r1),r1       #r1=i
                 ld (r0,r1,4),r2  #r2=s.x[i]
                 ld $v0,r3 #r3=&v0
                 st r2,(r3) #v0=s.x[i]

                 ld 8(r0),r4  #r4=&(s.y[i])
                 ld (r4,r1,4),r4 #r4=s.y[i]
                 ld $v1,r3 #r3=&v1
                 st r4,(r3) #v1=s.y[i]

                 ld 12(r0),r6 #r6=&s.z
                 ld (r6,r1,4),r3 #r3=s.z->x[i]
                 ld $v2,r4 #r4=&v2
                 st r3,(r4) #v2=s,z->x[i]

                 ld 12(r6),r6 #r6=&(s.z->z)
                 ld 8(r6),r6 #r6=&(s.z->z->y)
                 ld (r6,r1,4),r7 #r7=s.z->z->y[i]
                 ld $v3,r4 #r4=&v3
                 st r7,(r4) #v3=s.z->z->y[i]

                 halt    

.pos 0x2000
static:
i: .long 1
v0: .long 0
v1: .long 0
v2: .long 0
v3: .long 0
s: .long 1
   .long 0
   .long s_y
   .long s_z

.pos 0x3000
heap:
s_y:  .long 2     # s.y[0]
      .long 6     # s.y[1]
s_z:   .long 3      # s.z->x[0]
       .long 0     # s.z->x[1]
       .long 0     # s.z->y
       .long s_z_z #s.z->z
s_z_z: .long 0     # s.z->z->x[]
       .long 0     # s.z->z->x[1]
       .long s_z_z_y   # s.z->z->y
       .long 0     #s.z->z->z
s_z_z_y: .long 4 #s.z->z->y[0]
         .long 0 #s.z->z->y[1]


