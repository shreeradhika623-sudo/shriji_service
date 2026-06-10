#ifndef SHRIJI_ERROR_POLICY_H
#define SHRIJI_ERROR_POLICY_H

#include "../krst/krst_types.h"

typedef struct {

    KRSTResponseType response_type;

    int allow_auto_fix;
    int risk;
    int teach_level;

} ErrorPolicyDecision;

int shriji_update_error_memory(int code);

ErrorPolicyDecision
shriji_error_policy_decide(
    int repeat_count,
    int has_fix_rule
);

#endif
