#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

#define MAX_PID_LEN 10

/*
 * sys_print_process_info - prints the pid, user id, process group id, and command path
 * for the process with the given pid
 *
 * @pid: the pid of the process to print info for
 *
 * Return: 0 on success, negative error code on failure
 */
asmlinkage long sys_print_process_info(char __user *pid_str)
{
  char pid_buf[MAX_PID_LEN];
  long pid;
  struct task_struct *task;

  // Copy the pid from userspace to kernelspace
  if (copy_from_user(pid_buf, pid_str, MAX_PID_LEN)) {
    return -EFAULT;
  }

  // Convert the pid string to a long
  if (kstrtol(pid_buf, 10, &pid) < 0) {
    return -EINVAL;
  }

  // Find the task_struct for the process with the given pid
  task = find_task_by_vpid(pid);
  if (!task) {
    // Return an error if the process with the given pid does not exist
    return -ESRCH;
  }

  // Print the pid, user id, process group id, and command path
  printk("pid: %ld\n", pid);
  printk("user id: %d\n", task->cred->uid);
  printk("process group id: %d\n", task->cred->gid);
  printk("command path: %s\n", task->comm);

  return 0;
}

