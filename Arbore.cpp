#include <stdio.h>
#include <iostream>
using namespace std;

struct student
{
	int cod;
	char *nume;
	float medie;
};

struct nodarb
{
	student inf;
	nodarb *left, *right;
};
struct nodl {
	student inf;
	nodl *next, *prev;
};
nodl *inserareLista(student s, nodl *cap, nodl **coada) {

	nodl *nou = (nodl*)malloc(sizeof(nodl));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc(sizeof(char)*(strlen(s.nume) + 1));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->next = NULL;
	nou->prev = NULL;
	if (cap == NULL) {
		cap = nou;
		(*coada) = nou;
	}
	else {
		nodl* temp = cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		(*coada) = nou;

	}
	return cap;
}
nodarb *creare(student s, nodarb *st, nodarb *dr)
{
	nodarb *nou = (nodarb*)malloc(sizeof(nodarb));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodarb *inserare(student s, nodarb *rad)
{
	nodarb *aux = rad;
	if (rad == NULL)
	{
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (true)
		{
			if (s.cod < aux->inf.cod)
				if (aux->left != NULL)
					aux = aux->left;
				else
				{
					aux->left = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (s.cod > aux->inf.cod)
					if (aux->right != NULL)
						aux = aux->right;
					else
					{
						aux->right = creare(s, NULL, NULL);
						return rad;
					}
				else
					return rad;
		}
}

void preordine(nodarb *rad)
{
	if (rad != NULL)
	{
		printf("\nCod=%d, Nume=%s, Medie=%5.2f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
		preordine(rad->left);
		preordine(rad->right);
	}
}

void inordine(nodarb *rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
		inordine(rad->right);
	}
}

void postordine(nodarb *rad)
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
	}
}


void afisareListaCapCoada(nodl* cap) {
	nodl *temp = cap;
	while (temp != NULL) {
		printf("\n Cod: %d, Nume: %s, Medie: %5.2f", temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}
void afisareListaCoadaCap(nodl* coada) {
	nodl* temp = coada;
	while (temp != NULL) {
		printf("\n Cod: %d, Nume: %s, Medie: %5.2f", temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->prev;
	}
}
void conversieArboreInListaDubla(nodarb *rad, nodl **cap, nodl **coada) {
	student s;

	if (rad != NULL) {
		s.cod = rad->inf.cod;
		s.nume = (char*)malloc((strlen(rad->inf.nume) + 1) * sizeof(char));
		strcpy(s.nume, rad->inf.nume);
		s.medie = rad->inf.medie;
		*cap = inserareLista(s, *cap, &(*coada));
		nodarb *st = rad->left;
		nodarb *dr = rad->right;
		free(rad->inf.nume);
		free(rad);
		conversieArboreInListaDubla(st, cap, &(*coada));
		conversieArboreInListaDubla(dr, cap, &(*coada));
	}

}
void dezalocareLista(nodl* cap) {
	nodl *temp = cap;
	nodl* temp2;
	while (temp->next != NULL) {
		temp2 = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = temp2;

	}
}

void main()
{
	int n;
	
	printf("Nr studenti: ");
	scanf("%d", &n);

	nodarb *rad = NULL;
	student s;
	char buffer[20];

	for (int i = 0; i < n; i++) {
		printf("\nCod:");
		scanf("%d", &s.cod);
		printf("\nNume: ");
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("\nMedie:");
		scanf( "%f", &s.medie);

		rad = inserare(s, rad);
	}

	

	preordine(rad);
	printf("\n------------------------\n");
	inordine(rad);
	printf("\n------------------------\n");
	postordine(rad);

	nodl *cap = NULL;
	nodl *coada = NULL;

	printf("\nlista----------------\n");
	conversieArboreInListaDubla(rad, &cap, &coada);
	printf("Valoare cap %d", cap);
	printf("\nafisare lista cap-coada----------------\n");
	afisareListaCapCoada(cap);

	printf("\nafisare lista coada-cap----------------\n");
	afisareListaCoadaCap(coada);
	dezalocareLista(cap);
}