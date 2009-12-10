# John Calandrino - LinS/ched Makefil 
PROGS = linsched
CC = gcc
LINUXDIR = linux-2.6.32-rc3
CFLAGS =  -g -D__KERNEL__ -D__LINSCHED__ -Wall -Wundef -Wstrict-prototypes -Werror-implicit-function-declaration -fno-common  -I ${LINUXDIR}/include -I ${LINUXDIR}/arch/x86/include  -include ${LINUXDIR}/include/linux/autoconf.h -include linux_linsched.h -Wno-pointer-sign
CLEANFILES = *.o *.out *~ *.er
OBJFILES = linsched.o linux_linsched.o  ${LINUXDIR}/kernel/sched.o ${LINUXDIR}/kernel/fork.o ${LINUXDIR}/arch/x86/kernel/init_task.o ${LINUXDIR}/kernel/exit.o ${LINUXDIR}/kernel/time.o ${LINUXDIR}/kernel/cpu.o ${LINUXDIR}/kernel/percpu.o ${LINUXDIR}/kernel/sched_clock.o ${LINUXDIR}/kernel/sched_cpupri.o ${LINUXDIR}/kernel/hrtimer.o ${LINUXDIR}/kernel/cred.o ${LINUXDIR}/kernel/signal.o ${LINUXDIR}/kernel/pid.o ${LINUXDIR}/kernel/time/timekeeping.o ${LINUXDIR}/kernel/time/ntp.o ${LINUXDIR}/kernel/time/jiffies.o ${LINUXDIR}/init/main.o ${LINUXDIR}/lib/rbtree.o ${LINUXDIR}/lib/div64.o ${LINUXDIR}/lib/cpumask.o ${LINUXDIR}/lib/bitmap.o ${LINUXDIR}/lib/list_debug.o ${LINUXDIR}/lib/find_next_bit.o ${LINUXDIR}/lib/hweight.o ${LINUXDIR}/lib/reciprocal_div.o ${LINUXDIR}/lib/plist.o 
 
all:		${PROGS}

linsched:	${OBJFILES}
		${CC} ${LFLAGS} -o $@ ${OBJFILES}

%.o:		%.c
		${CC} -o $*.o ${CFLAGS} -c $*.c

clean:
		rm -f ${PROGS} ${OBJFILES} ${CLEANFILES} ${ERRORFILE} ${OUTFILE}

bkup:
		tar cvjf linsched_${LINUXDIR}_bkup.bz2 *
