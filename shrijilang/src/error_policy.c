#include "../include/error_policy.h"

#define MAX_ERROR_TYPES 50

typedef struct {
    int code;
    int count;
} ErrorMemory;

static ErrorMemory error_memory[MAX_ERROR_TYPES];
static int error_memory_size = 0;

int shriji_update_error_memory(int code)
{
    for (int i = 0; i < error_memory_size; i++)
    {
        if (error_memory[i].code == code)
        {
            error_memory[i].count++;
            return error_memory[i].count;
        }
    }

    if (error_memory_size >= MAX_ERROR_TYPES)
    {
        error_memory_size = 0;
    }

    error_memory[error_memory_size].code = code;
    error_memory[error_memory_size].count = 1;
    error_memory_size++;

    return 1;
}

ErrorPolicyDecision
shriji_error_policy_decide(
    int repeat_count,
    int has_fix_rule
)
{
    ErrorPolicyDecision d = {0};

    if (repeat_count >= 10)
    {
        d.response_type = KRST_RESPONSE_CRITICAL;
        d.allow_auto_fix = has_fix_rule;
        d.risk = 80;
        d.teach_level = KRST_TEACH_TRAIN;
        return d;
    }

    if (repeat_count >= 7)
    {
        d.response_type = KRST_RESPONSE_WARNING;
        d.allow_auto_fix = has_fix_rule;
        d.risk = 50;
        d.teach_level = KRST_TEACH_DEEP;
        return d;
    }

    if (repeat_count >= 3 && has_fix_rule)
    {
        d.response_type = KRST_RESPONSE_AUTO_FIX;
        d.allow_auto_fix = 1;
        d.risk = 50;
        d.teach_level = KRST_TEACH_DEEP;
        return d;
    }

    d.response_type = KRST_RESPONSE_ERROR;
    d.allow_auto_fix = 0;
    d.risk = 20;
    d.teach_level = KRST_TEACH_EXPLAIN;

    return d;
}
