#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACK_SIZE 1024

void t_low_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while(1)
    {
        printk("T_LOW running\n");
        k_msleep(300);
    }
}

void t_med_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while(1)
    {
        printk("T_MED running\n");
        k_msleep(200);
    }
}

void t_high_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while(1)
    {
        printk("T_HIGH running\n");
        k_msleep(100);
    }
}

void t_coop_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while(1)
    {
        for(int i = 0; i < 5; i++)
        {
            volatile uint32_t x = 0;
            for(uint32_t j = 0; j < 1000000; j++)
            {
                x++;
            }

            printk("T_COOP busy-work iteration %d done\n", i);
        }

        printk("T_COOP yielding\n");
        k_yield();
    }
}

K_THREAD_DEFINE(t_low, STACK_SIZE, t_low_fn, NULL, NULL, NULL,
    7, 0, 0);
K_THREAD_DEFINE(t_med, STACK_SIZE, t_med_fn, NULL, NULL, NULL,
    5, 0, 0);
K_THREAD_DEFINE(t_high, STACK_SIZE, t_high_fn, NULL, NULL, NULL,
    3, 0, 0);
K_THREAD_DEFINE(t_coop, STACK_SIZE, t_coop_fn, NULL, NULL, NULL,
    -1, 0, 0);

int main(void)
{
    return 0;
}

