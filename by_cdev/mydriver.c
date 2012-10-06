// Below code is from link: http://bbs.chinaunix.net/forum.php?mod=viewthread&tid=3772447
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

dev_t t_iDevNo = 0;
struct cdev *t_pDev = NULL;

static ssize_t Read(struct file *pFile, char __user *pUsr, size_t count, loff_t *pLoff)
{
    printk("MyDrv: Read in myDev....................\n");
    return 0;
}

static ssize_t Write(struct file *pFile, const char __user *pUsr, size_t count, loff_t *pLoff)
{
    printk("MyDrv: Write in myDev...................\n");
    return 0;
}

static int Open(struct inode *inode, struct file *file)
{
    printk("MrDrv: Open in myDev....................\n");
    return 0;
}

static int Release(struct inode *inode, struct file *file)
{
    printk("MyDrv: Release in myDev.................\n");
    return 0;
}

static struct file_operations fileOps = {
    .owner = THIS_MODULE,
    .read = Read,
    .write = Write,
    .open = Open,
    .release = Release
};

static int __init MyDriverInit(void)
{
    int iRet = 0;
    int iDevMajor = 0;

    if(iDevMajor > 0) {      // 如果预设了有效值
        t_iDevNo = MKDEV(iDevMajor, 0);                             // major device number
        iRet = register_chrdev_region(t_iDevNo, 1, "MyDrv_dev");    // 静态申请
    } else {
        iRet = alloc_chrdev_region(&t_iDevNo, 0, 1, "MyDrv_dev");   // 动态申请
    }

    if(iRet >= 0) {
        t_pDev = cdev_alloc();
        if(t_pDev != NULL) {
            //kobject_set_name(&t_pDev->kobj, "MyDrv_kobject");   // didn't find it in /sys, why?
            t_pDev->owner = THIS_MODULE;
            t_pDev->ops = &fileOps;     // associate the fileOps
            t_pDev->dev = t_iDevNo;
            t_pDev->count = 1;
            cdev_init(t_pDev, t_pDev->ops);
            iRet = cdev_add(t_pDev, t_iDevNo, 1);   // association
            if(iRet != 0) {
                printk(KERN_NOTICE"MyDrv: cdev_add fail............\n");
                unregister_chrdev_region(t_iDevNo, 1);
            }
        } else {
            printk(KERN_NOTICE"MyDrv: kmalloc fail..................\n");
            unregister_chrdev_region(t_iDevNo, 1);
        }
    } else {
        printk(KERN_INFO"MyDrv: Can't get device number.................\n");
    }

    printk(KERN_ALERT "MyDrv: Insert my driver.......................\n");
    return iRet;
}

static void __exit MyDriverExit(void)
{
    cdev_del(t_pDev);
    unregister_chrdev_region(t_iDevNo, 1);
    printk(KERN_ALERT "MyDrv: Remove my dirver..................\n");
}

module_init(MyDriverInit);
module_exit(MyDriverExit);
