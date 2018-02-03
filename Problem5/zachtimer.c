/*****************************************************************************
 * Copyright (C) 2018 by Zach Farmer
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for
 * any misuse of this material.
 *
*****************************************************************************/
/**
 * @file zachtimer.c
 * @brief An example kernel module triggering a periodic timer
 *
 * This is a short sample program to demonstrate a kernel module.
 * it can take the name and interval of the timer as command-line arguments.
 *
 * @modparam name the name of the executor. Zach Farmer by default.
 * @modparam interval_ms the interval of the periodic timer. 500ms by default.
 *
 * @author Zach Farmer
 * @date February 3 2018
 * @version 1.0
 *
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zach Farmer");
MODULE_DESCRIPTION("Zachs Timer");
MODULE_VERSION("0.01");

static char* name = "Zach Farmer";
static int interval_ms = 500;

module_param(name, charp, S_IRUGO);
module_param(interval_ms, int, S_IRUGO);

static struct timer_list ztimer;

static int timerfires;

void zachtimer_callback(struct timer_list * this_is_a_stupid_argument_to_require_in_this_function)
{
  	mod_timer(&ztimer, jiffies + msecs_to_jiffies(interval_ms));
	timerfires++;
	//print input name, default "Zach Farmer"
	printk(KERN_INFO "%s\n", name);
	//print # of timer fires
	printk(KERN_INFO "zachtimer has fired %d times\n", timerfires);

}

int zachtimer_init(void)
{
  printk(KERN_INFO "Initializing zachtimer");
  timerfires = 0;
  /* setup timer to call zachtimer_callback */
  timer_setup(&ztimer,zachtimer_callback, 0);
  /* set timer interval to the input interval_ms (default 500)*/
  mod_timer(&ztimer, jiffies + msecs_to_jiffies(interval_ms));
  return 0;
}

void zachtimer_exit(void)
{
  printk(KERN_INFO "Exiting zachtimer");
  /* remove kernel timer when unloading module */
  del_timer(&ztimer);
  return;
}

module_init(zachtimer_init);
module_exit(zachtimer_exit);
