#include <linux/init.h>
#include <linux/module.h>


// @my_init is the driver initializtion entry point 
// @my_init() is called during system startup. <- If driver is statically compiled into the kernel
// @or when the module is inserted into the kernel, depend on the driver is type of module or kernel function.
static int my_init(void)
{
    return 0;
}

static void my_exit(void)
{
    return;
}

module_init( my_init );
module_exit( my_exit );