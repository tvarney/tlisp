
#include "Node.h"

#include <stdlib.h>

#define DELETE(node) node->deletefn(node)

struct ValueNode *
ValueNode_new(enum ValueType type, union ValueData data)
{
    struct ValueNode *node;
    
    node = malloc(sizeof(struct ValueNode));
    if(node) {
        /* Set the correct node type */
        node->_base.type = NODE_VALUE;
        node->_base.deletefn = &ValueNode_delete;
        node->_base.visitfn = &ValueNode_visit;
        
        /* Fill in data */
        node->value.type = type;
        node->value.value = data;
    }
    return node;
}

void
ValueNode_delete(struct Node *node)
{
    free(node);
}

struct Value
ValueNode_visit(struct Node *node)
{
    return ((struct ValueNode *)node)->value;
}

struct UnaryOpNode *
UnaryOpNode_new(const struct NodeSpec const *spec, struct Node *value)
{
    struct UnaryOpNode *node;
    
    node = malloc(sizeof(struct UnaryOpNode));
    if(node) {
        /* Set the correct node type */
        node->_base.type = NODE_UNARY_OP;
        node->_base.deletefn = &UnaryOpNode_delete;
        node->_base.visitfn = spec->visitfn;
        node->_base.writefn = spec->writefn;
        
        /* Fill in data */
        node->value = value;
    }
    return node;
}

void
UnaryOpNode_delete(struct Node *node)
{
    /* Delete the sub-node. */
    DELETE(((struct UnaryOpNode *)node)->value);
    free(node);
}

struct BinaryOpNode *
BinaryOpNode_new(const struct NodeSpec const *spec, struct Node *lhs,
                 struct Node *rhs)
{
    struct BinaryOpNode *node;
    
    node = malloc(sizeof(struct UnaryOpNode));
    if(node) {
        /* Set the correct node type */
        node->_base.type = NODE_BINARY_OP;
        node->_base.deletefn = &BinaryOpNode_delete;
        node->_base.visitfn = spec->visitfn;
        node->_base.writefn = spec->writefn;
        
        /* Fill in data */
        node->lhs = lhs;
        node->rhs = rhs;
    }
    return node;
}

void
BinaryOpNode_delete(struct Node *node)
{
    DELETE(((struct BinaryOpNode *)node)->lhs);
    DELETE(((struct BinaryOpNode *)node)->rhs);
    free(node);
}

/* Static Nodes */

static void
StaticDeleteFn(struct Node *node)
{
    (void)node;
}

static const struct ValueNode StaticNilNode = {
    { NODE_VALUE, &StaticDeleteFn, &ValueNode_visit, NULL },
    { VALUE_NIL, { 0 } }
};

static const struct ValueNode StaticFalseNode = {
    { NODE_VALUE, &StaticDeleteFn, &ValueNode_visit, NULL },
    { VALUE_BOOL, { 0 } }
};

static const struct ValueNode StaticTrueNode = {
    { NODE_VALUE, &StaticDeleteFn, &ValueNode_visit, NULL },
    {VALUE_BOOL, { 1 } }
};

const struct ValueNode *NilNode = &StaticNilNode;
const struct ValueNode *FalseNode = &StaticFalseNode;
const struct ValueNode *TrueNode = &StaticTrueNode;

