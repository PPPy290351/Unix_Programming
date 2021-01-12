// Key: writing a driver to talk to a specific hardware for intialization before start using and releasing resources before exit from the kernel

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h> // @ for module_init and module_exit declarations

// @ For kernel debugging, mostly use 'printk' 
// @ KERN_INFO / KERN_ERR , to specify a log level

// @my_init is the driver initializtion entry point 
// @my_init() is called during system startup. <- If driver is statically compiled into the kernel
// @or when the module is inserted into the kernel, depend on the driver is type of module or kernel function.
static int my_init(void)
{
    printk(KERN_INFO"Hello World\n");
    return 0;
}

static void my_exit(void)
{
    printk(KERN_INFO"Bye World\n");
    return;
}

module_init( my_init );
module_exit( my_exit );