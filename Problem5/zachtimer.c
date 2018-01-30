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
