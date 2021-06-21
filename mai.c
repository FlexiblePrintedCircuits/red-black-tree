#include <stdio.h>
#include <stdlib.h>


struct node
{
    int value;
    int color; // 黒が0, 赤が1
    struct node *parent;
    struct node *left_node;
    struct node *rigth_node;
};

struct node *root = NULL; 

struct node *search(struct node *root, int number)
{
    struct node *now_node = root;

    while (now_node)
    {
        if (number < now_node->number)
        {
            now_node = now_node->left_node;
        }
        else if (number > now_node->number)
        {
            now_node = now_node->rigth_node;
        }
        else
        {
            return now_node;
        }
    }

    return NULL;
}

void right_rotation(struct node *target)
{
    struct node *left_node = target->left_node;

    target->left_node = left_node->rigth_node;

    if (target->left_node)
        target->left_node->parent = target;

    left_node->parent = target->parent;

    if (!target->parent)
        root = left_node;
    else if (target == target->parent->left_node)
        target->parent->left_node = left_node;
    else
        target->parent->rigth_node = left_node;

    left_node->rigth_node = target;
    target->parent = left_node;
}

void left_rotation(struct node *target)
{
    struct node *right_node = target->rigth_node;

    target->rigth_node = right_node->left_node;

    if (target->rigth_node)
        target->rigth_node->parent = target;

    right_node->parent = target->parent;

    if (!target->parent)
        root = right_node;
    else if (target == target->parent->rigth_node)
        target->parent->rigth_node = right_node;
    else
        target->parent->left_node = right_node;

    right_node->left_node = target;
    target->parent = right_node;
}

void insert(int value)
{
    struct node *target_of_insertion = (struct node *)malloc(sizeof(struct node));
    target_of_insertion->value = value;
    target_of_insertion->left_node = target_of_insertion->rigth_node = target_of_insertion->parent = NULL;

    if (root == NULL)
    {
        target_of_insertion->color = 0; // 黒に設定
        (root) = z;
    }
    else
    {
        struct node *tmp1 = NULL;
        struct node *tmp2 = (*root);

        while (tmp1 != NULL)
        {
            tmp1 = tmp2;
            if (target_of_insertion->value < tmp2->value)
                tmp2 = tmp2->left_node;
            else
                tmp2 = tmp2->rigth_node;
        }
        target_of_insertion->parent = tmp1;
        if (target_of_insertion->value > tmp1->value)
            tmp1->rigth_node = target_of_insertion;
        else
            tmp1->left_node = target_of_insertion;
        target_of_insertion->color = 1; // 赤に設定

        fix(target_of_insertion);
    }
}

void fix(struct node *target)
{
    while (target != *root && target->parent->color == 1)
    {
        struct node *tmp;

        if (target->parent == target->parent->parent->left_node)
            tmp = target->parent->parent->rigth_node;
        else
            tmp = target->parent->parent->left_node;

        if (tmp->color == 1)
        {
            tmp->color = 0;
            target->parent->color = 0;
            target->parent->parent->color = 1;
            target = target->parent->parent;
        }

        else
        {
            if (target->parent == target->parent->parent->left_node &&
                target == target->parent->left_node)
            {
                int color_number = target->parent->color;
                target->parent->color = target->parent->parent->color;
                target->parent->parent->color = color_number;
                right_rotation(target->parent->parent);
            }

            if (target->parent == target->parent->parent->left_node &&
                target == target->parent->rigth_node)
            {
                int color_number = target->color;
                target->color = target->parent->parent->color;
                target->parent->parent->color = color_number;
                left_rotation(target->parent);
                right_rotation(target->parent->parent);
            }

            if (target->parent == target->parent->parent->rigth_node &&
                target == target->parent->rigth_node)
            {
                int color_number = target->parent->color;
                target->parent->color = target->parent->parent->color;
                target->parent->parent->color = color_number;
                left_rotation(target->parent->parent);
            }

            if (target->parent == target->parent->parent->rigth_node &&
                target == target->parent->left_node)
            {
                int color_number = target->color;
                target->color = target->parent->parent->color;
                target->parent->parent->color = color_number;
                right_rotation(target->parent);
                left_rotation(target->parent->parent);
            }
        }
    }
    (*root)->color = 0;
}

int main(void) {

    return 0;
}

