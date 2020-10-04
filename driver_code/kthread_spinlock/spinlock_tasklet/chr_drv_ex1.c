#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>               //kmalloc()
#include<linux/uaccess.h>            //copy_to/from_user()
#include<linux/ioctl.h>
#include<linux/sysfs.h>
#include<linux/kobject.h>
#include<linux/interrupt.h>
#include<asm/io.h>
#include<linux/kthread.h>
#include<linux/delay.h>

#define mem_size 1024
#define IRQ_NO 1
unsigned int i=0;

unsigned long chr_spinlock_variable=0;
void tasklet_func(unsigned long data);

struct tasklet_struct *tasklet;


/* Declare the tasklet */
//DECLARE_TASKLET(tasklet,tasklet_func,1);

DEFINE_SPINLOCK(chr_spinlock);

/* Tasklet function body */
void tasklet_func(unsigned long data)
{ 
    spin_lock_irq(&chr_spinlock);
    chr_spinlock_variable++;
    printk(KERN_INFO"Executing the Tasklet function : data =%lu\n",chr_spinlock_variable);
    spin_unlock_irq(&chr_spinlock);
}

static irqreturn_t irq_handler(int irq, void *dev_id)
{
    spin_lock_irq(&chr_spinlock);
    chr_spinlock_variable++;
    printk(KERN_INFO"keyboard: Interrupt Occured and executing ISR routinr%lu\n",chr_spinlock_variable);
    spin_unlock_irq(&chr_spinlock);
    /*Scheduling the tasklet*/
    tasklet_schedule(tasklet);
    return IRQ_HANDLED;
}
volatile int chr_value=0;

// Define the ioctl code
#define WR_DATA _IOW('a','a',int32_t*)
#define RD_DATA _IOR('a','b',int32_t*)

int32_t val = 0;


dev_t dev=0;
static struct class *dev_class;
static struct cdev my_cdev;
uint8_t *kernel_buffer;

static int __init chr_driver_init(void);
static void __exit chr_driver_exit(void);

static struct task_struct *chr_thread1; 
static struct task_struct *chr_thread2; 


static int my_open(struct inode *inode,struct file *file);
static int my_release(struct inode *inode,struct file *file);
static ssize_t my_read(struct file *filp,char __user *buf, size_t len,loff_t *off);
static ssize_t my_write(struct file *filp,const char __user *buf, size_t len,loff_t *off);
static long chr_ioctl(struct file *file,unsigned int cmd,unsigned long arg);
int thrd_func1(void *p);
int thrd_func2(void *p);

int thrd_func1(void *p)
{
//    int i=0;
    while(!kthread_should_stop())
    {
        if(!spin_is_locked(&chr_spinlock))
        {
            printk(KERN_INFO"spinlock is not locked in thread function1...\n");
        }
        spin_lock(&chr_spinlock);
        if(spin_is_locked(&chr_spinlock))
        {
            printk(KERN_INFO"spinlock is locker in thread function1...\n");
        }
        chr_spinlock_variable++;
        printk(KERN_INFO"In thread function 1 %lu\n",chr_spinlock_variable);
        spin_unlock(&chr_spinlock);
        msleep(1000);
    }
    return 0;
}

int thrd_func2(void *p)
{
 while(!kthread_should_stop())
    {
        if(!spin_is_locked(&chr_spinlock))
        {
            printk(KERN_INFO"spinlock is not locked in thread function2...\n");
        }
        spin_lock(&chr_spinlock);
        if(spin_is_locked(&chr_spinlock))
        {
            printk(KERN_INFO"spinlock is locker in thread function2...\n");
        }
        chr_spinlock_variable++;
        printk(KERN_INFO"In thread function 1 %lu\n",chr_spinlock_variable);
        spin_unlock(&chr_spinlock);
        msleep(1000);
    }
    return 0;

}

static struct file_operations fops = 
{
	.owner	=	THIS_MODULE,
	.read	=	my_read,
	.write	=	my_write,
	.open	=	my_open,
        .unlocked_ioctl = chr_ioctl,
	.release=	my_release,
};

static int my_open(struct inode *inode,struct file *file)
{
    /* creating physical memory */
    if((kernel_buffer = kmalloc(mem_size,GFP_KERNEL)) == 0)
    {
        printk(KERN_INFO"Cannot allocate the memory to the kernel..\n");
        return -1;
    }
    printk(KERN_INFO"Device file opened....\n");
    return 0;
}

static int my_release(struct inode *inode,struct file *file)
{
    kfree(kernel_buffer);
    printk(KERN_INFO"Device file closed.....\n");
    return 0;
}


static ssize_t my_read(struct file *filp,char __user *buf,size_t len,loff_t *off)
{
    copy_to_user(buf,kernel_buffer,mem_size);
    printk(KERN_INFO"Data read : DONE.....\n");
    return mem_size;
}

static ssize_t my_write(struct file *filp,const char __user *buf, size_t len,loff_t *off)
{
    copy_from_user(kernel_buffer,buf,len);
    printk(KERN_INFO"Data is written successfully");
    return len;
}

static long chr_ioctl(struct file *file,unsigned int cmd,unsigned long arg)
{
    switch(cmd)
    {
        case WR_DATA:
            copy_from_user(&val,(int32_t*)arg,sizeof(val));
            printk(KERN_INFO"val = %d\n",val);
            break;
        case RD_DATA:
            copy_to_user((int32_t*)arg,&val,sizeof(val));
            break;
    }
return 0;
}

static int __init chr_driver_init(void)
{
/* Allocating major number */
if((alloc_chrdev_region(&dev,0,1,"my_Dev")) < 0)
{
	printk(KERN_INFO"Cannot allocate the major number ..\n");
	return -1;
}
printk(KERN_INFO"MAJOR = %d MINOR = %d..\n",MAJOR(dev),MINOR(dev));

/* creating cdev structure */

cdev_init(&my_cdev,&fops);

/* Adding character device to the system */

if((cdev_add(&my_cdev,dev,1)) < 0)
{
printk(KERN_INFO"Cannot add the device to the system....\n");
goto r_class;
}

/* creating struct class  */
if((dev_class = class_create(THIS_MODULE,"my_class")) == NULL)
{
printk(KERN_INFO"cannot create the struct class.....\n");
goto r_class;
}

/* creating device  */

if((device_create(dev_class,NULL,dev,NULL,"my_device")) == NULL)
{
printk(KERN_INFO"cannot create the device ...\n");
goto r_device;
}

if (request_irq(IRQ_NO, irq_handler, IRQF_SHARED, "chr_device", (void *)(irq_handler)))
{
    printk(KERN_INFO"chr_device:cannot register IRQ");
    goto irq;
}

tasklet=kmalloc(sizeof(struct tasklet_struct),GFP_KERNEL);
if(tasklet == NULL)
{
    printk(KERN_INFO"cannot allocate memory...\n");
    goto irq;
}

tasklet_init(tasklet,tasklet_func,0); // Dynamic method


chr_thread1 = kthread_create(thrd_func1,NULL,"chr thread 1");
if(chr_thread1)
{
    wake_up_process(chr_thread1);
}
else
{
    printk(KERN_INFO"Unable to create the thread.\n");
    goto r_device;
}


chr_thread2 = kthread_run(thrd_func2,NULL,"chr thread 2");
if(chr_thread2)
{
    printk(KERN_INFO"Succesfully created kernel thread..\n");
}
else
{
    printk(KERN_INFO"Unable to create the thread.\n");
    goto r_device;
}

printk(KERN_INFO"Device drive insert......done properly...\n");
return 0;

irq:
                free_irq(IRQ_NO,(void *)(irq_handler));

r_device:
		class_destroy(dev_class);



r_class:
		unregister_chrdev_region(dev,1);
		return -1;


}


static void __exit chr_driver_exit(void)
{
kthread_stop(chr_thread1);
kthread_stop(chr_thread2);
free_irq(IRQ_NO,(void *)(irq_handler));
tasklet_kill(tasklet);
device_destroy(dev_class,dev);
class_destroy(dev_class);
cdev_del(&my_cdev);
unregister_chrdev_region(dev,1);
printk(KERN_INFO"device driver is removed successfully");
}


module_init(chr_driver_init);
module_exit(chr_driver_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jasim Hussain Lakhara");
MODULE_DESCRIPTION("The character device driver");
