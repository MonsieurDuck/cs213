.pos 0x100
                 ld   $sb, r5             # initialise stack pointer
                 inca r5                  # ...to bottom of stack
                 gpc  $0x6, r6            # set return address
                 j    main                 # call copy
                 halt                     # end
.pos 0x200
main:  deca r5  #allocate stack frame
       st r6,0x0(r5)   #save ra on stack
       gpc $0x6,r6  #set returne address
       j copy

       ld 0x0(r5),r6 #lload ra from stack
       inca r5 #deallocate stack frame
       j 0x0(r6)  #return

.pos 0x400
copy:  ld $-16, r0 #r0=-16
       add r0,r5  #allocate stack frame
       st r6,0xc(r5) #store ra to stack
       ld $0, r0 # r0=0
       st r0,(r5) #i=0
       ld (r5),r1 #r1=temp_i
       ld $src,r2 #r2=&src[0]
       ld (r2,r1,4),r3 #r3=src[temp_i]
       mov r5,r4 #r4=the address stored in stack pointer
       inca r4 #r4=r4+4

whileloop:
       beq r3,end #if src[temp_i]=0, goto end
       st r3,(r4,r1,4) #dst[temp_i] = src[temp_i]
       inc r1 #temp_i++
       st r1,(r5) #i=temp_i
       ld (r2,r1,4),r3 #r3=src[temp_i]
       br whileloop #goto whileloop

end:   st r0,(r4,r1,4) #dst[i]=0
       ld 0xc(r5),r6 #load ra from stack
       ld $0xc,r0 #r0=12
       add r0,r5 #deallocate stack frame
       j 0x0(r6) #return



.pos 0x500
src:       .long 0x1  #src[0]
           .long 0x2  #src[1] 
           .long 0x80c
           .long 0xff00ff00
           .long 0x0000ffff   #ld $-1,r0
           .long 0xffffff00   #finished with nop slide
           .long 0x0100ffff   #ld $-1,r1
           .long 0xffffff00   #finished with nop slide
           .long 0x0200ffff   #ld $-1,r2
           .long 0xffffff00   #finished with nop slide
           .long 0x0300ffff   #ld $-1,r3
           .long 0xffffff00   #finished with nop slide
           .long 0x0400ffff   #ld $-1,r4
           .long 0xffffff00   #finished with nop slide
           .long 0x0500ffff   #ld $-1,r5
           .long 0xffffff00   #finished with nop slide
           .long 0x0600ffff   #ld $-1,r6
           .long 0xffffff00   #finished with nop slide
           .long 0x0700ffff   #ld $-1,r7
           .long 0xffffff00   #finished with nop slide
           .long 0xff00f000

.pos 0x800
stackTop:   .long 0x0
            .long 0x0
sb:         .long 0x0
