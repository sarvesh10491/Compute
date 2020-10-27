#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sarvesh");
MODULE_DESCRIPTION("Simple Hello world");

static int __init init_hello(void)
{
    printk(KERN_INFO "Hello World..\n");

    return 0;
}

static void __exit cleanup_hello(void)
{
    printk(KERN_INFO "Goodbye World..\n");
}

module_init(init_hello);
module_exit(cleanup_hello);