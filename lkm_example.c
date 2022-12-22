#include <linux/module.h>    
#include <linux/kernel.h>     
#include <linux/init.h>       
#include <linux/list.h>
#include <linux/moduleparam.h>
#include <linux/cred.h>
#include <linux/resource.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/unistd.h>
#include <asm/current.h>
#include <linux/syscalls.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("5.19.8");
MODULE_DESCRIPTION("Process info from pid"); 

static int givenpid;

/*
 * sys_print_process_info - prints the pid, user id, process group id, and command path
 * for the process with the given pid
 *
 * @pid: the pid of the process to print info for
 *
 * Return: 0 on success, negative error code on failure
 */
module_param(givenpid,int,0644);

//asmlinkage long sys_print_process_info(int pid)
static int __init sys_print_process_info(void)
{
  struct task_struct *task;

  if (givenpid < 0) {
    return -EINVAL;
  }

  // Find the task_struct for the process with the given pid
  task = pid_task(find_vpid(givenpid),PIDTYPE_PID);
  if (!task) {
    // Return an error if the process with the given pid does not exist
    return -ESRCH;
  }

  // Print the pid, user id, process group id, and command path
  printk(KERN_INFO "pid: %ld\n", givenpid);
  printk(KERN_INFO "user id: %d\n", task->cred->uid);
  printk(KERN_INFO "process group id: %d\n", task->cred->gid);
  printk(KERN_INFO "command path: %s\n", task->comm);

  return 0;
}

static void __exit exitmod(void){
    printk("Exiting Module.");
}

module_init(sys_print_process_info);
module_exit(exitmod);