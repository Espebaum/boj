#include <stdio.h>
#include <stdlib.h>
typedef struct s_node
{
    char			val;
    struct s_node	*left;
    struct s_node	*right;
}   t_node;

t_node *make_node(char val)
{
    t_node *t;
    t = (t_node *) malloc(sizeof(t_node));
    t->val = val;
    t->left = NULL;
    t->right = NULL;
	return t;
}

void    delete_node(t_node * t)
{
    free(t);
}

int N;
t_node *node[26];

void	preorder(t_node *now)
{
	printf("%c", now->val);
	if (now->left != NULL)
		preorder(now->left);
	if (now->right != NULL)
		preorder(now->right);
}

void	inorder(t_node *now)
{
	if (now->left != NULL)
		inorder(now->left);
	printf("%c", now->val);
	if (now->right != NULL)
		inorder(now->right);
}

void	postorder(t_node *now)
{
	if (now->left != NULL)
		postorder(now->left);
	if (now->right != NULL)
		postorder(now->right);
	printf("%c", now->val);
}

int main(void)
{
    scanf("%d", &N);
    node[0] = make_node('A');
    for (int i=0;i<N;++i)
    {
        char c[3];
        scanf(" %c %c %c",c,c+1,c+2);
        if (c[1] != '.')
        {
            node[c[1] - 'A'] = make_node(c[1]);
            node[c[0] - 'A']->left = node[c[1] - 'A'];
        }
		if (c[2] != '.')
        {
            node[c[2] - 'A'] = make_node(c[2]);
            node[c[0] - 'A']->right = node[c[2] - 'A'];
        }
    }
	preorder(node[0]);
	printf("\n");
	inorder(node[0]);
	printf("\n");
	postorder(node[0]);
	printf("\n");
}