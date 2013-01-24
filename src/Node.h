
#ifndef TLISP_NODE_H
#define TLISP_NODE_H

#include "Value.h"

#define VISIT(node) (((node)->visitfn)(node))

enum NodeId {
    NODE_VALUE,
    NODE_UNARY_OP,
    NODE_BINARY_OP
};

struct Node;
typedef void (*NodeDeleteFn)(struct Node *);
typedef void (*NodeWriteFn)(struct Node *);
typedef struct Value (*NodeVisitFn)(struct Node *);

struct Node {
    enum NodeId type;
    NodeDeleteFn deletefn;
    NodeVisitFn visitfn;
    NodeWriteFn writefn;
};
struct NodeSpec {
    NodeVisitFn visitfn;
    NodeWriteFn writefn;
};

struct ValueNode {
    struct Node _base;
    struct Value value;
};

struct UnaryOpNode {
    struct Node _base;
    struct Node *value;
};

struct BinaryOpNode {
    struct Node _base;
    struct Node *lhs, *rhs;
};

struct ValueNode *ValueNode_new(enum ValueType type, union ValueData data);
void ValueNode_delete(struct Node *node);
struct Value ValueNode_visit(struct Node *node);

struct UnaryOpNode * UnaryOpNode_new(const struct NodeSpec const *spec,
                                     struct Node *value);
void UnaryOpNode_delete(struct Node *node);

struct BinaryOpNode * BinaryOpNode_new(const struct NodeSpec const *spec,
                                       struct Node *lhs,
                                       struct Node *rhs);
void BinaryOpNode_delete(struct Node *node);

extern const struct ValueNode *NilNode, *FalseNode, *TrueNode;

#endif
