#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DRIVER_NAME "ChrDev_Module"

// @ Initialization
static unsigned int test_chrdev_alloc_major = 0;
static unsigned int index_of_dev = 1;
static struct cdev test_chrdev_alloc_cdev;

static int test_chrdev_alloc_open(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "test_chrdev_alloc is open.\n");
    return 0;
}

static int test_chrdev_alloc_close(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "test_chrdev_alloc is close.\n");
    return 0;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = test_chrdev_alloc_open,
    .release = test_chrdev_alloc_close,
};

static int test_alloc_chrdev_init(void)
{
    // @ define MKDEV(ma,mi)	(((ma) << MINORBITS) | (mi))
    dev_t dev = MKDEV(test_chrdev_alloc_major, 0);
    int alloc_ret = 0;
    int cdev_ret = 0;

    alloc_ret = alloc_chrdev_region( &dev, 0, index_of_dev, DRIVER_NAME );
    if(alloc_ret)
        goto error;
    // @ MAJOR(dev)	((unsigned int) ((dev) >> MINORBITS))
    test_chrdev_alloc_major = MAJOR(dev);

    cdev_init( &test_chrdev_alloc_cdev, &fops );
    cdev_ret = cdev_add( &test_chrdev_alloc_cdev, dev, index_of_dev );
    if(cdev_ret)
        goto error;
    printk(KERN_ALERT "%s driver - major number %d installed.\n", DRIVER_NAME, test_chrdev_alloc_major);
    return 0;

error:
    return -1;
}

void test_alloc_chrdev_exit(void)
{
    dev_t dev = MKDEV(test_chrdev_alloc_major, 0);

    cdev_del( &test_chrdev_alloc_cdev );
    unregister_chrdev_region(dev, index_of_dev);
    printk(KERN_ALERT "%s driver removed.\n", DRIVER_NAME);
}

module_init(test_alloc_chrdev_init);
module_exit(test_alloc_chrdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chi-Shen Yeh , Intel Corporation");
MODULE_DESCRIPTION("This is sample module under NTHU Linux Kernel");



/*

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
 
#define DRIVER_NAME "test_chrdev"
static unsigned int test_chrdev_alloc_major = 0;
static unsigned int num_of_dev = 1;
static struct cdev test_chrdev_alloc_cdev;
 
static int test_chrdev_alloc_open(struct inode *inode, struct file *filp)
{
 printk(KERN_ALERT "test_chrdev_alloc is open.\n");
 return 0;
}
 
static int test_chrdev_alloc_close(struct inode *inode, struct file *filp)
{
 printk(KERN_ALERT "test_chrdev_alloc is close.\n");
 return 0;
}
 
struct file_operations fops = {
 .owner = THIS_MODULE,
 .open = test_chrdev_alloc_open,
 .release = test_chrdev_alloc_close,
};
 
static int test_alloc_chrdev_init(void)
{
 dev_t dev = MKDEV(test_chrdev_alloc_major, 0);
 int alloc_ret = 0;
 int cdev_ret = 0;
 
 alloc_ret = alloc_chrdev_region(&dev, 0, num_of_dev, DRIVER_NAME);
 if (alloc_ret)
  goto error;
 test_chrdev_alloc_major = MAJOR(dev);
 
 cdev_init(&test_chrdev_alloc_cdev, &fops);
 cdev_ret = cdev_add(&test_chrdev_alloc_cdev, dev, num_of_dev);
 if (cdev_ret)
  goto error;
 
 printk(KERN_ALERT "%s driver(major number %d) installed.\n", DRIVER_NAME, test_chrdev_alloc_major);
 return 0;
 
error:
 if (cdev_ret == 0)
  cdev_del(&test_chrdev_alloc_cdev);
 if (alloc_ret == 0)
  unregister_chrdev_region(dev, num_of_dev);
 return -1;
}
 
void test_alloc_chrdev_exit(void)
{
 dev_t dev = MKDEV(test_chrdev_alloc_major, 0);
 
 cdev_del(&test_chrdev_alloc_cdev);
 unregister_chrdev_region(dev, num_of_dev);
 printk(KERN_ALERT "%s driver removed.\n", DRIVER_NAME);
}
 
module_init(test_alloc_chrdev_init);
module_exit(test_alloc_chrdev_exit);
 
MODULE_LICENSE("GPL") ;
MODULE_AUTHOR("Wang Chen Shu");
MODULE_DESCRIPTION("This is test_alloc_chrdev module.");

 */