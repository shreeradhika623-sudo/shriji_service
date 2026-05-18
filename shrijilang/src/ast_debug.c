#include <stdio.h>
#include "../include/ast_debug.h"

static void print_indent(int level)
{
    for (int i = 0; i < level; i++)
        printf("  ");
}

static void ast_print_inner(ASTNode *node, int level)
{
    if (!node) {
        print_indent(level);
        printf("NULL\n");
        return;
    }

    print_indent(level);

    switch (node->type)
    {
        case AST_NUMBER:
            printf("NUMBER %g\n", node->number_value);
            break;

        case AST_IDENTIFIER:
            printf("IDENTIFIER %s\n", node->name);
            break;

        case AST_ASSIGNMENT:
            printf("ASSIGN %s\n", node->name);

            ast_print_inner(node->value, level + 1);
            break;

        case AST_PROGRAM:
            printf("PROGRAM\n");

            for (int i = 0; i < node->stmt_count; i++)
                ast_print_inner(node->statements[i], level + 1);

            break;


         case AST_UPDATE:
              printf("UPDATE %s\n", node->name);

                ast_print_inner(node->value, level + 1);
             break;

         case AST_COMMAND:
              printf("COMMAND\n");

                ast_print_inner(node->value, level + 1);
             break;


         case AST_WHILE:
    printf("WHILE\n");

    print_indent(level + 1);
    printf("CONDITION\n");

    ast_print_inner(node->condition, level + 2);

    print_indent(level + 1);
    printf("BODY\n");

    ast_print_inner(node->body, level + 2);

    break;

case AST_IF:
    printf("IF\n");

    print_indent(level + 1);
    printf("CONDITION\n");

    ast_print_inner(node->condition, level + 2);

    print_indent(level + 1);
    printf("THEN\n");

   ast_print_inner(node->left, level + 2);
    break;

case AST_BLOCK:
    printf("BLOCK\n");

    for (int i = 0; i < node->stmt_count; i++)
        ast_print_inner(node->statements[i], level + 1);

    break;

case AST_BINARY:
    printf("BINARY %s\n", node->op);

    ast_print_inner(node->left, level + 1);
    ast_print_inner(node->right, level + 1);

    break;

     case AST_RACHNA:
    printf("RACHNA %s\n", node->rachna_name);

    print_indent(level + 1);
    printf("PARAMS\n");

    for (int i = 0; i < node->rachna_param_count; i++)
    {
        ast_print_inner(node->rachna_params[i], level + 2);
    }

    print_indent(level + 1);
    printf("BODY\n");

    ast_print_inner(node->rachna_body, level + 2);

    break;

case AST_CALL:
    printf("CALL %s\n", node->function_name);

    for (int i = 0; i < node->arg_count; i++)
    {
        ast_print_inner(node->args[i], level + 1);
    }

    break;

case AST_RETURN:
    printf("RETURN\n");

    ast_print_inner(node->return_expr, level + 1);

    break;

         default:
            printf("NODE type=%d\n", node->type);
            break;
    }
}

void ast_print(ASTNode *node)
{
    ast_print_inner(node, 0);
}
