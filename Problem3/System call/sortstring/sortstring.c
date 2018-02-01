#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/uaccess.h>
#include<linux/slab.h>
#include<linux/errno.h>

SYSCALL_DEFINE3(sort_string, int*, inbuf, int*, outbuf, int, size) {

	int *kptr = (int*) kmalloc(size * sizeof(int), GFP_KERNEL);

	if(kptr==NULL)
	{
		printk(KERN_ERR "Kernel Allocation failed\n");
		return EFAULT;
	}
	
	if(inbuf==NULL)
	{
		printk(KERN_ERR "User input buffer unallocated\n");
		return EFAULT;
	}

	if(outbuf==NULL)
	{
		printk(KERN_ERR "User output buffer unallocated\n");
		return EFAULT;
	}

	if(size<1)
	{
		printk(KERN_ERR "Invalid buffer size\n");
		return EPERM;
	}

	int temp = 0, j, i;

	printk(KERN_INFO "Entered sortstring\n");

	printk(KERN_INFO "Buffer size: %d\n", size);



	if(copy_from_user(kptr, inbuf, size * sizeof(int))==0)
	{
		printk(KERN_INFO "copy_from_user successful\n");
	}
	else
	{
		printk(KERN_ERR "copy_from_user failed\n");
		return EFAULT;
	}

	printk(KERN_INFO "Starting sort\n");

	for (i = 1; i < size; i++) {
		for (j = 0; j < size - i; j++) {
			if (*(kptr+j) > *(kptr+j+1)) {
				temp = *(kptr+j);
				*(kptr+j) = *(kptr+j+1);
				*(kptr+j+1) = temp;
			}
		}
	}
	
	printk(KERN_INFO "Finished sort\n");

	if(copy_to_user(outbuf, kptr, size * sizeof(int))==0)
	{
		printk(KERN_INFO "copy_to_user successful\n");
	}
	else
	{
		printk(KERN_ERR "copy_to_user failed\n");
		return EFAULT;
	}

	printk(KERN_INFO "Exiting sortstring\n");
	return 0;
}
