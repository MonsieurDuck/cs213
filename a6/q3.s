.pos 0x100

# #step1
# ld   $0x0, r0            # r0 = temp_sum = 0
# ld  $base,r1            #r1=&base
# ld  $1,r2               #r2=temp_i=1
# ld (r1,r2,4),r3         #r3=grade[0]
# add r3,r0               #r3=temp_sum=grade[0]
# inc r2                 #r2=temp_i++
# ld (r1,r2,4),r3         #r3=grade[1]
# add r3,r0               #r3=temp_sum=grade[0]+grade[1]
# inc r2                 #r2=temp_i++
# ld (r1,r2,4),r3         #r3=grade[2]
# add r3,r0               #r3=temp_sum=grade[0]+grade[1]+grade[2]
# inc r2                 #r2=temp_i++
# ld (r1,r2,4),r3         #r3=grade[3]
# add r3,r0               #r3=temp_sum=grade[0]+grade[1]+grade[2]+grade[3]
# shr $2,r0              #r0=temp_sum/4
# inc r2                  #r2=temp_i++
# st r0,(r1,r2,4)           #average=temp_sum/4

#step2
ld $0,r0    #r0=temp_i=0
ld $n,r1    #r1=&n
ld (r1),r1  #r1=n
not r1  #r1=~r1
inc r1  #r1=-n
add r0,r1  #r1=temp_i-n
ld  $base,r2        #r2=&base

loop: beq r1, sort_loop #if temp_i=n, goto then
ld 4(r2),r3       #r3=grade[0]
ld $0,r4         #r4=temp_sum=0
add r3,r4        #r4=temp_sum=grade[0]
ld 8(r2),r3       #r3=grade[1]
add r3,r4        #r4=temp_sum=grade[0]+grade[1]
ld 12(r2),r3         #r3=grade[2]
add r3,r4          #r4=temp_sum=grade[0]+grade[1]+grade[2]
ld 16(r2),r3         #r3=grade[3]
add r3,r4           #r4=temp_sum=grade[0]+grade[1]+grade[2]+grade[3]
shr $2,r4           #r4=temp_sum/4
st r4,20(r2)     #average=temp_sum/4
ld $24,r5  #r5=24
add r5,r2  #r2=r2+24
inc r1    #temp_i++
br loop


#step3
#sort
sort_loop:
ld $n,r0 #r0=$n
ld (r0),r0 #r0=n
ld $s,r1 #r1=&s
ld (r1),r1 #r1=s
dec r0 #n--

sort_outer_loop:
beq r0,median #if n=0, goto median
ld $1,r2 #r1=temp_j=1

sort_inner_loop:
mov r0,r3 #r3=r0=n
not r3 #r3=~n
inc r3 #r3=-n
add r2,r3 #r3=temp_j-n
bgt r3,outer_loop #if temp_j-n>0, goto outer_loop 


outer_loop:dec r0 #n--
br sort_outer_loop


# sort_inner_loop:
# ld $1,r2 #r2=temp_j
# not r0
# inc r0 #r0=-temp_i
# add r2,r0 #r0=j-i
# bgt r0,end_inner_loop #if j-i,goto end_inner_loop


#if s[j-1].avr > s[j].avr
#*a=&s[j-1]  *b=&s[j]
mov r2,r4 #r4=temp_j
shl $4,r4 #r4=16j
mov r2,r5 #r5=temp_j
shl $3,r5 #r5=8j
add r5,r4 #r4=24j
add r1, r4 #r4=&s[j]
mov r4, r5 #r5=&s[j]
ld $-24, r6 #r6=-24 = - sizeof(struct Student)
add r6, r4 #r4 = &s[j - 1]
ld 20(r4),r6  # r6 = s[j - 1].avr
ld 20(r5),r7  # r7 = s[j].avr
not r6 
inc r6  # r6=-s[j-1].avr
add r7,r6 #r6 = s[j].avr-s[j-1].avr
bgt r6,inner_loop   # if s[j].average > s[j - 1].average goto inner_loop
beq r6,inner_loop     # if s[j].average == s[j - 1].average goto inner_loop


inner_loop:inc r2 #j++
br sort_inner_loop



ld $6, r3
swap_loop: beq r3,inner_loop  #if k=0, goto sort_inner_loop
ld (r4),r6  #r6= *a
ld (r5),r7  #r7= *b
st r7,(r4)  #*a = *b
st r6,(r5)  #*b = *a
inca r4  #a++
inca r5  #b++
dec r3  #k--
br swap_loop



median:
ld $n, r0       # r0 = &n
ld (r0), r0     # r0 = n
shr $1, r0      # r0 = n / 2
mov r0, r1      # r1 = n / 2
shl $4, r0      # r0 = 16(n / 2)
shl $3, r1      # r1 = 8(n / 2)
add r1, r0      # r0 = 24(n / 2)
ld $s, r1       # r1 = &s
ld (r1), r1     # r1 = s
add r1, r0      # r0 = &s[n / 2]
ld (r0), r0     # r0 = s[n / 2].studentid
ld $m, r1       # r1 = &m
st r0, (r1)     # m  = s[n / 2].studentid
halt



.pos 0x1000
n:    .long 3     # 3 students
m:    .long 0     # put the answer here
s:    .long base  # address of the array

base: .long 1234  # student 0 ID
.long 80 #grade[0]
.long 60 #grade[1]
.long 78 #grade[2]
.long 90 #grade[3]
.long 0 # computed average
.long 1235 #student 1 ID
.long 76 #grade[0]
.long 64 #grade[1]
.long 82 #grade[2]
.long 99 #grade[3]
.long 0 # computed average
.long 1236 #student 2 ID
.long 54 #grade[0]
.long 68 #grade[1]
.long 87 #grade[2]
.long 50 #grade[3]
.long 0 # computed average





