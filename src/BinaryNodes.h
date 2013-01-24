
#ifndef TLISP_BINARY_NODES_H
#define TLISP_BINARY_NODES_H

#include "Node.h"

extern const struct NodeSpec const *AddNodeSpec;
extern const struct NodeSpec const *SubNodeSpec;
extern const struct NodeSpec const *MulNodeSpec;
extern const struct NodeSpec const *DivNodeSpec;
extern const struct NodeSpec const *ModNodeSpec;

#define AddNode_new(lhs, rhs) BinaryOpNode_new(AddNodeSpec, lhs, rhs)
#define SubNode_new(lhs, rhs) BinaryOpNode_new(SubNodeSpec, lhs, rhs)
#define MulNode_new(lhs, rhs) BinaryOpNode_new(MulNodeSpec, lhs, rhs)
#define DivNode_new(lhs, rhs) BinaryOpNode_new(DivNodeSpec, lhs, rhs)
#define ModNode_new(lhs, rhs) BinaryOpNode_new(ModNodeSpec, lhs, rhs)

#endif
