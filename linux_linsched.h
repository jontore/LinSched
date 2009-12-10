/* LinSched -- The Linux Scheduler Simulator
 * Copyright (C) 2008  John M. Calandrino
 * E-mail: jmc@cs.unc.edu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (see COPYING); if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef LINUX_LINSCHED_H
#define LINUX_LINSCHED_H

#include <linux/sched.h>
#include <malloc.h>

/* Definitions and declarations. */
#define LINSCHED_RAND_SEED	123456
#define LINSCHED_MAX_TASKS	10000
extern struct task_struct *__linsched_tasks[LINSCHED_MAX_TASKS];

/* Some definitions for allocation of task-related structures.  */
#define linsched_alloc_thread_info(tsk) ((struct thread_info *) \
        malloc(sizeof(struct thread_info)))
#define linsched_alloc_task_struct() ((struct task_struct *) \
        malloc(sizeof(struct task_struct)))

/* Declarations of functions from sched.c that were redefined here. */
void fire_sched_out_preempt_notifiers(struct task_struct *curr,
		struct task_struct *next);
void fire_sched_in_preempt_notifiers(struct task_struct *curr);

/* Declarations of system initialization (or "boot") function. */
asmlinkage void __init start_kernel(void);

/* Scheduler "system calls" that are used during task creation. */
asmlinkage long sys_sched_setscheduler(pid_t pid, int policy,
				       struct sched_param __user *param);
asmlinkage long sys_nice(int increment);

/* linsched functions */
void linsched_change_cpu(int cpu);
void linsched_init_cpus(void);
void linsched_init(void);
void linsched_default_callback(void);
void linsched_announce_callback(void);
void linsched_exit_callback(void);
struct task_struct *__linsched_create_task(void (*callback)(void));
void linsched_disable_migrations(void);
void linsched_enable_migrations(void);
int linsched_force_migration(struct task_struct *task, int dest_cpu, int migr);
struct task_struct *linsched_get_task(int task_id);
void linsched_create_normal_task(void (*callback)(void), int niceval);
void linsched_create_batch_task(void (*callback)(void), int niceval);
void linsched_create_RTfifo_task(void (*callback)(void), int prio);
void linsched_create_RTrr_task(void (*callback)(void), int prio);
void linsched_yield(void);
void linsched_random_init(int seed);
unsigned long linsched_random(void);
void linsched_run_sim(int sim_ticks);

#endif /* LINUX_LINSCHED_H */

