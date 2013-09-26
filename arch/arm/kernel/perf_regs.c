
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/perf_event.h>
#include <linux/bug.h>
#include <uapi/asm/perf_regs.h>
#include <asm/ptrace.h>

u64 perf_reg_value(struct pt_regs *regs, int idx)
{
	if (WARN_ON_ONCE((u32)idx >= PERF_REG_ARM_MAX))
		return 0;

	return regs->uregs[idx];
}

#define REG_RESERVED (~((1ULL << PERF_REG_ARM_MAX) - 1))

int perf_reg_validate(u64 mask)
{
	if (!mask || mask & REG_RESERVED)
		return -EINVAL;

	return 0;
}

u64 perf_reg_abi(struct task_struct *task)
{
	return PERF_SAMPLE_REGS_ABI_32;
}
