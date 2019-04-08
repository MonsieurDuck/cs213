.pos 0x0
ld   $sb, r5   # [01] sp = address of last word of stack
inca r5    # [02] sp = address of word after stack
gpc  $6, r6 # [03] ra = pc + 6
j    0x300  #call main()
                 halt                     
.pos 0x100
s:                .long 0x00001000         #s
.pos 0x200
update:                ld   (r5), r0 #r0=first arg
ld   4(r5), r1 #r1= second arg
ld   $0x100, r2   #r2=address of s
ld   (r2), r2 #r2=value of s =address of a
ld   (r2, r1, 4), r3   #r3=a[second arg]
add  r3, r0  #r0=r0+r3=0+first arg
st   r0, (r2, r1, 4) #a[second arg]=first arg+a[second arg]
j    (r6) #return
.pos 0x300
main:                ld   $-12, r0     #r0=-12=size of caller part for update's frame
add  r0, r5    #allocate argument part for update's frame
st   r6, 8(r5) #save ra on stack
ld   $1, r0  #r0=1, value of first arg
st   r0, (r5) #save first arg on stack
ld   $2, r0 #r0=2, value of second arg
st   r0, 4(r5) #save second arg on stack
ld   $-8, r0 #r0=-8=size of caller part for second update's frame
add  r0, r5   #allocate caller part for second update's frame
ld   $3, r0 #r0=3, value of first arg
st   r0, (r5) #save first arg on stack
ld   $4, r0 #r0=4, value of second arg
st   r0, 4(r5) #save second arg on stack
gpc  $6, r6   #r6=pc+6
j    0x200  #call update(3,4)
ld   $8, r0  #r0 = 8 = size of caller part of update's frame
add  r0, r5  #deallocate caller part of update's frame
ld   (r5), r1 #r1=1
ld   4(r5), r2 #r2=2
ld   $-8, r0 #r0=-8=size of caller part for second update's frame
add  r0, r5 #allocate caller part for second update's frame
st   r1, (r5)  #first arg=1
st   r2, 4(r5) #second arg=2
gpc  $6, r6  #r6=pc6
j    0x200 #call update(1,2)
ld   $8, r0 #r0 = 8 = size of caller part of update's frame
add  r0, r5  #deallocate caller part of update's frame
ld   8(r5), r6 #load ra from stack
ld   $12, r0 #r0=12=size of arg
add  r0, r5  #deallocate caller part of stack frame
j    (r6) #return
.pos 0x1000
a:                 .long 0
                 .long 0
                 .long 0
                 .long 0
                 .long 0
                 .long 0
                 .long 0
                 .long 0
                 .long 0
                 .long 0
.pos 0x8000
# These are here so you can see (some of) the stack contents.
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
sb: .long 0
