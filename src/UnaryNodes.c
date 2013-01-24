
#include "UnaryNodes.h"

#include <stddef.h>
#include <limits.h>

/**
 * Function Prototypes
 */

struct Value NumNegNode_visit(struct Node *node);
struct Value ComplementNode_visit(struct Node *node);
struct Value BoolNegNode_visit(struct Node *node);
struct Value AbsNode_visit(struct Node *node);

/**
 * NodeSpec definitions
 */

const struct NodeSpec NumNegSpecDef = {
    &NumNegNode_visit,
    NULL
};
const struct NodeSpec ComplementSpecDef = {
    &ComplementNode_visit,
    NULL
};
const struct NodeSpec BoolNegSpecDef = {
    &BoolNegNode_visit,
    NULL
};
const struct NodeSpec AbsSpecDef = {
    &AbsNode_visit,
    NULL
};

const struct NodeSpec const *NumNegSpec = &NumNegSpecDef;
const struct NodeSpec const *ComplementSpec = &ComplementSpecDef;
const struct NodeSpec const *BoolNegSpec = &BoolNegSpecDef;
const struct NodeSpec const *AbsSpec = &AbsSpecDef;


/**
 * Function Definitions
 */

#define APPLY_INTEGER(rval, op)                      \
    case VALUE_BYTE:                                 \
        rval.value.s_byte = op(rval.value.s_byte);   \
        break;                                       \
    case VALUE_SHORT:                                \
        rval.value.s_short = op(rval.value.s_short); \
        break;                                       \
    case VALUE_INT:                                  \
        rval.value.s_int = op(rval.value.s_int);     \
        break;                                       \
    case VALUE_LONG:                                 \
        rval.value.s_long = op(rval.value.s_long);   \
        break

#define APPLY_UINTEGER(rval, op)                         \
    case VALUE_UBYTE:                                    \
        rval.value.u_byte = op(rval.value.u_byte);       \
        break;                                           \
    case VALUE_USHORT:                                   \
        rval.value.u_short = op(rval.value.u_short);     \
        break;                                           \
    case VALUE_UINT:                                     \
        rval.value.u_int = op(rval.value.u_int);         \
        break;                                           \
    case VALUE_ULONG:                                    \
        rval.value.u_long = op(rval.value.s_long);       \
        break

#define APPLY_FLOAT(rval, op)                           \
    case VALUE_FLOAT:                                   \
        rval.value.t_float = op(rval.value.t_float);    \
        break;                                          \
    case VALUE_DOUBLE:                                  \
        rval.value.t_double = op(rval.value.t_double);  \
        break

#define APPLY_BOOLEAN(rval, op)                    \
    case VALUE_BOOL:                               \
        rval.value.t_bool = op(rval.value.t_bool); \
        break


struct Value
NumNegNode_visit(struct Node *node)
{
    struct Value rval = VISIT(((struct UnaryOpNode *)node)->value);
    switch(rval.type) {
        APPLY_INTEGER(rval, -);
        APPLY_UINTEGER(rval, -);
        APPLY_FLOAT(rval, -);
    case VALUE_NIL:
        break;
    default:
        rval.type = VALUE_NIL;
        rval.value.u_long = 0;
    }
    return rval;
}

struct Value
ComplementNode_visit(struct Node *node)
{
    struct Value rval = VISIT(((struct UnaryOpNode *)node)->value);
    switch(rval.type) {
        APPLY_INTEGER(rval, ~);
        APPLY_UINTEGER(rval, ~);
        APPLY_FLOAT(rval, -1.0 + -); /*< Should work... */
    default:
        rval.type = VALUE_NIL;
        rval.value.u_long = 0;
    }
    return rval;
}

struct Value
BoolNegNode_visit(struct Node *node)
{
    struct Value rval = VISIT(((struct UnaryOpNode *)node)->value);
    switch(rval.type) {
        APPLY_INTEGER(rval, !);
        APPLY_UINTEGER(rval, !);
        APPLY_BOOLEAN(rval, !);
    case VALUE_FLOAT:
        rval.value.t_float = (rval.value.t_float != 0.0) ? 0.0 : 1.0;
        break;
    case VALUE_DOUBLE:
        rval.value.t_double = (rval.value.t_double != 0.0) ? 0.0 : 1.0;
        break;
    default:
        rval.type = VALUE_NIL;
        rval.value.u_long = 0;
    }
    return rval;
}

/* Define our bitwise stuff vs. branch stuff */
#define BITWISE_ABS(i) (i) & ~(1 << (sizeof(i) * CHAR_BIT - 1))
#define BRANCH_ABS(i) ((i) < 0) ? -(i) : (i)
#ifdef ABS_NO_BRANCH
# define ABS_OP(i) BITWISE_ABS(i)
#else
# define ABS_OP(i) BRANCH_ABS(i)
#endif
struct Value
AbsNode_visit(struct Node *node)
{
    struct Value rval = VISIT(((struct UnaryOpNode *)node)->value);
    switch(rval.type) {
    case VALUE_NIL:
    case VALUE_UBYTE:
    case VALUE_USHORT:
    case VALUE_UINT:
    case VALUE_ULONG:
        /* Do nothing, unsigned values and Nil can't be negative */
        break;
    case VALUE_BYTE:
        rval.value.s_byte = ABS_OP(rval.value.s_byte);
        break;
    case VALUE_SHORT:
        rval.value.s_short = ABS_OP(rval.value.s_short);
        break;
    case VALUE_INT:
        rval.value.s_int = ABS_OP(rval.value.s_int);
        break;
    case VALUE_LONG:
        rval.value.s_long = ABS_OP(rval.value.s_long);
        break;
    case VALUE_FLOAT:
        rval.value.t_float = BRANCH_ABS(rval.value.t_float);
        break;
    case VALUE_DOUBLE:
        rval.value.t_double = BRANCH_ABS(rval.value.t_double);
        break;
    default:
        /* Throw an exception */
        break;
    }
    return rval;
}
