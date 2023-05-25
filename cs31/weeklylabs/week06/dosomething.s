	.text
	.globl	dosomething
	.type	dosomething, @function
dosomething:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	subl	$16, %esp  # create some space for local variables
                           # (you can add more if you'd like: ex. subl $30, %esp)
        # implement the body of this function here
        # the parameter n is allocated on the stack at addresss:  8(%ebp)
        # you can used -4(%ebp) and -8(%ebp) as space for local vars x and res
        # if you want more local variable space, add more above:
        #   ex. subl $24, %esp   (you don't need to do this for this function)


        # the function return values is in regiester %eax
        # here we are returning 3 from this function...change it

	movl 8(%ebp), %edx
	addl $20, %edx
	movl %edx, -4(%ebp)
	imull $3, %edx
	movl  %edx, -8(%ebp)

	leave
	ret
	.size	dosomething, .-dosomething
