#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CMAX 50

struct node
{
	char C;
	int f;

	//to use it as a list
	struct node *right;

	//to use it as a tree

	struct node *real_left;
	struct node *real_right;
};

typedef struct node *tree;

//________________________________________________________________

tree creatNode(char car, int freq)
{
	tree tmp;
	tmp = (tree)malloc(sizeof(struct node));

	tmp->C = car;
	tmp->f = freq;
	tmp->right = NULL;

	tmp->real_left = NULL;
	tmp->real_right = NULL;
	return tmp;
}

int exist_list(tree L, char Ch)
{
	tree p = L;
	//if(!L) return 0;
	while (p)
	{
		if (p->C == Ch)
			return 1;
		p = p->right;
	}
	return 0;
}

tree tri_h_set(tree list)
{
	int tmpfr;
	char tmpc;
	tree p, q, tmprr, tmprl;

	for (p = list; p->right; p = p->right)
	{
		for (q = list; q->right; q = q->right)
		{
			if (q->f > q->right->f)
			{
				tmpfr = q->f;
				tmpc = q->C;
				tmprr = q->real_right;
				tmprl = q->real_left;

				q->f = q->right->f;
				q->C = q->right->C;
				q->real_right = q->right->real_right;
				q->real_left = q->right->real_left;

				q->right->f = tmpfr;
				q->right->C = tmpc;
				q->right->real_right = tmprr;
				q->right->real_left = tmprl;
			}
		}
	}

	return list;
}

tree pop(tree list)
{
	return list->right;
}

//________________________________________________________________
int calcfreq(char *Ch, char car)
{
	int i, n = 0;
	for (i = 0; i < strlen(Ch); i++)
	{
		if (car == *(Ch + i))
			n++;
	}
	return n;
}

tree dataset(char *STR)
{
	int dim = strlen(STR), i;
	tree out = NULL, add, tmp;

	for (i = 0; i < dim; ++i)
	{
		if (exist_list(out, *(STR + i)) == 0)
		{
			if (!out)
			{
				add = creatNode(*(STR + i), calcfreq(STR, *(STR + i)));
				out = add;
			}
			else
			{
				add = creatNode(*(STR + i), calcfreq(STR, *(STR + i)));
				tmp = out;
				add->right = tmp;
				out = add;
			}
		}
	}
	out = tri_h_set(out);
	return out;
}

tree hufman_func(tree data_list)
{
	tree out = data_list, add, tmp, R, L;
	int g;

	while (out->right)
	{
		g = out->f + out->right->f;
		add = creatNode('#', g);

		add->real_right = (tree)malloc(sizeof(struct node));
		add->real_left = (tree)malloc(sizeof(struct node));

		*(add->real_right) = *(out->right);
		*(add->real_left) = *(out);

		out = pop(out);
		out = pop(out);

		tmp = out;
		add->right = tmp;
		out = add;
		out = tri_h_set(out);
	}

	return out;
}

void afficher_code(tree T, char *CODE)
{
	char TMP[CMAX];

	if ((T->real_left == NULL) && (T->real_right == NULL))
	{
		printf("[%c,%d] : [%s]\n", T->C, T->f, CODE);
		return;
	}
	if (T->real_left)
	{
		strcpy(TMP, CODE);
		strcat(TMP, "0");
		afficher_code(T->real_left, TMP);
	}
	if (T->real_right)
	{
		strcpy(TMP, CODE);
		strcat(TMP, "1");
		afficher_code(T->real_right, TMP);
	}
}

void afficher_list(tree T)
{
	tree p = T;
	printf("\n-------------------------------------\n\nchaque char et sa freq :  \n");
	while (p)
	{
		printf("['%c', <%d>]  \n ", p->C, p->f);
		p = p->right;
	}
	printf("\n-------------------------------------\n");
}

int main()
{
	char userinput[200];
	char CODE[CMAX] = "";
	tree T, H;
	char choice = ' ';

	do
	{
		system("clear");
		printf("\n\n-------------------------------------\n");
		printf("entrez une chaine de char svp :  \n 	---> ");
		scanf("%s", userinput);

		printf("Votre chaine est : %s\n", userinput);

		T = dataset(userinput);
		afficher_list(T);

		H = hufman_func(T);
		afficher_code(H, CODE);

		getchar();

		printf("\n\n[x = exit ,else = continue]\n");

		scanf("%c", &choice);
	} while (choice != 'x');

	return 0;
}