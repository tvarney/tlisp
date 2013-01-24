
#ifndef TLISP_UNARY_NODES_H
#define TLISP_UNARY_NODES_H

#include "Node.h"

extern const struct NodeSpec const *NumNegSpec;
extern const struct NodeSpec const *ComplementSpec;
extern const struct NodeSpec const *BoolNegSpec;

extern const struct NodeSpec const *AbsSpec;

#define NumNegNode_new(value)     UnaryOpNode_new(NumNegSpec, value)
#define ComplementNode_new(value) UnaryOpNode_new(ComplementSpec, value)
#define BoolNegNode_new(value)    UnaryOpNode_new(BoolNegSpec, value)

#define AbsNode_new(value)        UnaryOpNode_new(AbsSpec, value)

#endif
