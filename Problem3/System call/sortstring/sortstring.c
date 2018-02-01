#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/uaccess.h>
#include<linux/slab.h>

SYSCALL_DEFINE3(sort_string, int*, inbuf, int*, outbuf, int, size) {

	int *kptr = (int*) kmalloc(size * sizeof(int), GFP_KERNEL);
	
	int temp = 0, j, i;

	printk("Entered sortstring\n");

	printk("Buffer size: %d\n", size);



	if(copy_from_user(kptr, inbuf, size * sizeof(int))==0)
	{
		printk("copy_from_user successful\n");
	}
	else
	{
		printk("copy_from_user failed\n");
	}

	printk("Starting sort\n");

	for (i = 1; i < size; i++) {
		for (j = 0; j < size - i; j++) {
			if (*(kptr+j) > *(kptr+j+1)) {
				temp = *(kptr+j);
				*(kptr+j) = *(kptr+j+1);
				*(kptr+j+1) = temp;
			}
		}
	}
	
	printk("Finished sort\n");

	if(copy_to_user(outbuf, kptr, size * sizeof(int))==0)
	{
		printk("copy_to_user successful\n");
	}
	else
	{
		printk("copy_to_user failed\n");
	}

	printk("Exiting sortstring\n");
	return 0;
}
