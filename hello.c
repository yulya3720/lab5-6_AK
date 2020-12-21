#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/ktime.h>

struct personal_list_head {
struct personal_list_head *next;
ktime_t time;
};

MODULE_AUTHOR("Yuliia Lykhatska IV-82");
MODULE_DESCRIPTION("Writing Hello, World in Kernel");
MODULE_LICENSE("Dual BSD/GPL");

static struct personal_list_head *header;


static uint count = 1;
module_param(count, uint, S_IRUGO);
MODULE_PARM_DESC(count, "How many times to write Hello, world");


static int __init initter(void)
{
  uint i = 0;
  struct personal_list_head *temp;

  if (count == 0) {
    printk(KERN_WARNING "WARNING! \nCounter is 0");
  } else if (count >= 5 && count <= 10) {
    printk(KERN_WARNING "WARNING! \nCounter is between 5 and 10");
  } else if (count > 10) {
    printk(KERN_ERR "Counter is greater than 10");
    return -EINVAL;
  }

  header = kmalloc(sizeof(struct personal_list_head *), GFP_KERNEL);
  temp = header;
  for (i = 0; i < count; i++) {
    temp->next = kmalloc(sizeof(struct personal_list_head), GFP_KERNEL);
    temp->time = ktime_get();
    pr_info("Hello World!");
    }
    if (count != 0) {
      kfree(temp->next);
      temp->next = NULL;
    }
  printk(KERN_INFO "count: %d\n", count);
  return 0;
}


static void __exit exitter(void)
{
struct personal_list_head *variable;
while (header != NULL && count != 0) {
  variable = header;
  pr_info("Time : %lld", variable->time);
  header = variable->next;
  kfree(variable);
}
if (count == 0) {
pr_info("Time is 0 because print wasn't used");
}
pr_info("");
}

module_init(initter);
module_exit(exitter);
