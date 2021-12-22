#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/slab.h>
#include <linux/ktime.h>


MODULE_AUTHOR("Boyko Michael <m.boyko1228@gmail.com>");
MODULE_DESCRIPTION("LabWork #6");
MODULE_LICENSE("Dual BSD/GPL");

struct list_head_ {
	struct list_head_ *next;
	ktime_t time;
	};

static int amount = 1;
static struct list_head_ *head;

module_param(amount, uint, 0444);
MODULE_PARM_DESC(amount, "Number of times 'Hello, world!' will be printed");

uint i;
static int __init hello_init(void)
{
	struct list_head_ *var1, *var2;
	head = kmalloc(sizeof(struct list_head_ *), GFP_KERNEL);
	var1 = head;
	
	if (amount == 0) {
		pr_warn("Amount is equal to zero!");
		}
	else if (amount >= 5 && amount <= 10) {
		pr_warn("Amount is greater than 5 and less than 10");
		}
	else if (amount > 10) {
		BUG_ON(amount > 10);
		pr_warn("Amount is greater than 10!");
		return -EINVAL;
		}

	for (i = 0; i < amount; i++){
		var1->next = kmalloc(sizeof(struct list_head_), GFP_KERNEL);
		var1->time = ktime_get();
		if (i == 7){
			var1 = NULL;
			}
			
		BUG_ON(!var1);
		pr_info("Hello, world!\n");
		var2 = var1;
		var1 = var1->next;
	}
	
	if (amount != 0) {
		kfree(var2->next);
		var2->next = NULL;
	}
	
	return 0;
}

static void __exit hello_exit(void)
{
	struct list_head_ *var;
	while (amount != 0 && head != NULL) {
		var = head;
		pr_info("Time - %lld", var->time);
		head = var->next;
		kfree(var);
	}
pr_info("\n");
}

module_init(hello_init);
module_exit(hello_exit);
