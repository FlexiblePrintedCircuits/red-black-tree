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

struct node *search(struct node *root, int number)
{
    struct node *now_node = root;

    while (now_node)
    {
        if (number < now_node->value)
        {
            now_node = now_node->left_node;
        }
        else if (number > now_node->value)
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

void right_rotation(struct node **root, struct node *target)
{
    if (!target || !target->left_node)
        return;

    struct node *left_node = target->left_node;

    target->left_node = left_node->rigth_node;

    if (target->left_node)
        target->left_node->parent = target;

    left_node->parent = target->parent;

    if (!target->parent)
        (*root) = left_node;
    else if (target == target->parent->left_node)
        target->parent->left_node = left_node;
    else
        target->parent->rigth_node = left_node;

    left_node->rigth_node = target;
    target->parent = left_node;
}

void left_rotation(struct node **root, struct node *target)
{
    if (!target || !target->rigth_node)
        return;
    struct node *right_node = target->rigth_node;

    target->rigth_node = right_node->left_node;

    if (target->rigth_node)
        target->rigth_node->parent = target;

    right_node->parent = target->parent;

    if (!target->parent)
        (*root) = right_node;
    else if (target == target->parent->rigth_node)
        target->parent->rigth_node = right_node;
    else
        target->parent->left_node = right_node;

    right_node->left_node = target;
    target->parent = right_node;
}

void fix(struct node **root, struct node *target)
{
    while (target != *root && target != (*root)->left_node && target != (*root)->rigth_node && target->parent->color == 1)
    {
        struct node *tmp;

        if (target->parent && target->parent->parent && target->parent == target->parent->parent->left_node)
            tmp = target->parent->parent->rigth_node;
        else
            tmp = target->parent->parent->left_node;

        if (!tmp)
            target = target->parent->parent;
        else if (tmp->color == 1)
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
                right_rotation(root, target->parent->parent);
            }

            if (target->parent && target->parent->parent && target->parent == target->parent->parent->left_node &&
                target == target->parent->rigth_node)
            {
                int color_number = target->color;
                target->color = target->parent->parent->color;
                target->parent->parent->color = color_number;
                left_rotation(root, target->parent);
                right_rotation(root, target->parent->parent);
            }

            if (target->parent && target->parent->parent &&
                target->parent == target->parent->parent->rigth_node &&
                target == target->parent->rigth_node)
            {
                int color_number = target->parent->color;
                target->parent->color = target->parent->parent->color;
                target->parent->parent->color = color_number;
                left_rotation(root, target->parent->parent);
            }

            if (target->parent && target->parent->parent && target->parent == target->parent->parent->rigth_node &&
                target == target->parent->left_node)
            {
                int color_number = target->color;
                target->color = target->parent->parent->color;
                target->parent->parent->color = color_number;
                right_rotation(root, target->parent);
                left_rotation(root, target->parent->parent);
            }
        }
    }
    (*root)->color = 0;
}

void insert(struct node **root, int value)
{
    struct node *target_of_insertion = (struct node *)malloc(sizeof(struct node));
    target_of_insertion->value = value;
    target_of_insertion->left_node = NULL;
    target_of_insertion->rigth_node = NULL;
    target_of_insertion->parent = NULL;

    if (*root == NULL)
    {
        target_of_insertion->color = 0; // 黒に設定
        (*root) = target_of_insertion;
    }
    else
    {
        struct node *tmp1 = NULL;
        struct node *tmp2 = (*root);

        while (tmp2 != NULL)
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

        fix(root, target_of_insertion);
    }
}

void trans(struct node **root, struct node *x, struct node *y)
{
    if (x->parent == NULL)
    {
        (*root) = y;
    }
    else if (x == x->parent->left_node)
    {
        x->parent->left_node = y;
    }
    else
    {
        x->parent->rigth_node = y;
    }

    y->parent = x->parent;
}

void delete_fix(struct node **root, struct node *x)
{
    struct node *w;

    while (x != *root && x->color == 0)
    {

        if (x == x->parent->left_node)
        {
            w = x->parent->rigth_node;

            if (w->color == 1)
            {
                w->color = 0;
                x->parent->color = 1;
                left_rotation(root, x->parent);
                w = x->parent->rigth_node;
            }

            if (w->left_node->color == 0 && w->rigth_node->color == 0)
            {
                w->color = 1;
                x->parent->color = 0;
                x = x->parent;
            }
            else
            {
                if (w->rigth_node->color == 0)
                {
                    w->color = 1;
                    w->left_node->color = 0;
                    right_rotation(root, w);
                    w = x->parent->rigth_node;
                }

                w->color = x->parent->color;
                x->parent->color = 0;
                x->rigth_node->color = 0;
                left_rotation(root, x->parent);
                x = (*root);
            }
        }
        else
        {
            w = x->parent->left_node;

            if (w->color == 1)
            {
                w->color = 0;
                x->parent->color = 0;
                right_rotation(root, x->parent);
                w = x->parent->left_node;
            }

            if (w->left_node->color == 0 && w->rigth_node->color == 0)
            {
                w->color = 1;
                x->parent->color = 0;
                x = x->parent;
            }
            else
            {

                if (w->left_node->color == 0)
                {
                    w->color = 1;
                    w->rigth_node->color = 0;
                    left_rotation(root, w);
                    w = x->parent->left_node;
                }

                w->color = x->parent->color;
                x->parent->color = 0;
                w->left_node->color = 0;
                right_rotation(root, x->parent);
                x = (*root);
            }
        }
    }

    x->color = 0;
}

void delete (struct node **root, struct node *target)
{
    struct node *y, *x;
    int color_number;

    y = target;
    color_number = y->color;

    if (target->left_node == NULL)
    {
        x = target->rigth_node;
        trans(root, target, target->rigth_node);
    }
    else if (target->rigth_node == NULL)
    {
        x = target->left_node;
        trans(root, target, target->left_node);
    }
    else
    {
        while (target->rigth_node->left_node != NULL) {
            target->rigth_node = target->rigth_node->left_node;
        }

        color_number = y->color;

        x = y->rigth_node;

        if (y->parent == target)
        {
            x->parent = y;
        }
        else
        {
            trans(root, y, y->rigth_node);
            y->rigth_node = target->rigth_node;
            y->rigth_node->parent = y;
        }

        trans(root, target, y);
        y->left_node = target->left_node;
        y->left_node->parent = y;
        y->color = target->color;
    }

    if (color_number == 0)
    {
        delete_fix(root, x);
    }
}

void inorder(struct node *root)
{
    if (root == NULL)
        return;
    inorder(root->left_node);
    printf("%d ", root->value);
    inorder(root->rigth_node);
}

int main(void) {
    struct node *root = NULL;

    int insert_n = 6;
    int insert_values[] = {60, 40, 30, 10, 50, 20};

    int search_n = 2;
    int search_values[] = {30, 55};

    int delete_n = 6;
    int delete_values[] = {20, 40, 60, 30, 50, 10};

    for (int i = 0; i < insert_n; i++) {
        printf("Insert %d : ", insert_values[i]);
        insert(&root, insert_values[i]);
        inorder(root);
        printf("\n");
    }
    printf("Result: ");
    inorder(root);
    printf("\n\n");

    for (int i = 0; i < search_n; i++) {
        printf("Serch result %d : ", search_values[i]);
        if (search(root, search_values[i])) {
            printf("exist\n");
        } else {
            printf("not exist\n");
        }
    }
    printf("\n");

    for (int i = 0; i < delete_n; i++) {
        printf("Delete %d : ", delete_values[i]);
        delete (&root, search(root, delete_values[i]));
        inorder(root);
        printf("\n");
    }

    return 0;
}

