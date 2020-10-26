#include <stdio.h>
#include <iostream>
using namespace std;

struct student
{
	int varsta;
	char *nume;
	float medie;
	int nrNote;
	int *vectNote;
};

struct nodCoada
{
	student inf;
	nodCoada *next;
};

void put(nodCoada **prim, nodCoada **ultim, student s)
{
	nodCoada *nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.varsta = s.varsta;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->inf.nrNote = s.nrNote;
	nou->inf.vectNote = (int*)malloc(sizeof(int)*s.nrNote);
	for (int i = 0; i < s.nrNote; i++) {
		nou->inf.vectNote[i] = s.vectNote[i];
	}
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

int get(nodCoada **prim, nodCoada **ultim, student *s)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*s).varsta = (*prim)->inf.varsta;
		(*s).nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*prim)->inf.nume);
		(*s).medie = (*prim)->inf.medie;
		(*s).nrNote = (*prim)->inf.nrNote;
		(*s).vectNote = (int*)malloc(sizeof(int)*((*prim)->inf.nrNote));
		for (int i = 0; i < (*s).nrNote; i++) {
			(*s).vectNote[i] = (*prim)->inf.vectNote[i];
		}
		nodCoada *temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.nume);
		free(temp);
		return 0;
	}
	else if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void traversare(nodCoada *prim)
{
	nodCoada *temp = prim;
	while (temp)
	{
		printf("\nVarsta=%d, Nume=%s, Medie=%5.2f, Nr de note=%d si urmatoarele note: ",
			temp->inf.varsta, temp->inf.nume, temp->inf.medie,temp->inf.nrNote);
		for (int i = 0; i < temp->inf.nrNote; i++)
			printf("%d ", temp->inf.vectNote[i]);
		temp = temp->next;
	}
}

void conversieCoadaVector(nodCoada **prim, nodCoada **ultim, student *vect, int *nr)
{
	student s;
	while (get(prim, ultim, &s) == 0)
	{
		vect[*nr] = s;
		(*nr)++;
	}
}

void main()
{
	int n;
	printf("Nr. studenti=");
	scanf("%d", &n);

	nodCoada *prim = NULL, *ultim = NULL;
	student s;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("\nVarsta=");
		scanf("%d", &s.varsta);
		printf("\nNume=");
		scanf(" %[^\n]s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("\nMedie=");
		scanf("%f", &s.medie);
		printf("\nNr note=");
		scanf("%d", &s.nrNote);
		s.vectNote = (int*)malloc(sizeof(int)*s.nrNote);
		for (int i = 0; i < s.nrNote; i++) {
			s.vectNote[i]=0;
		}
		
		for (int i = 0; i < s.nrNote; i++) {
			printf("nota %d :", i + 1);
			scanf("%d",&s.vectNote[i]);
		}

		put(&prim, &ultim, s);
	}
	traversare(prim);

	/*student s1;
	while(get(&prim, &ultim, &s1)==0)
	{
		printf("\nVarsta=%d, Nume=%s, Medie=%5.2f", s1.varsta, s1.nume, s1.medie);
		free(s1.nume);
	}*/

	student s1;
	get(&prim, &ultim, &s1);
	free(s1.nume);

	printf("\n----------------\n");

	student *vect = (student*)malloc(n * sizeof(student));
	int nr = 0;
	conversieCoadaVector(&prim, &ultim, vect, &nr);
	for (int i = 0; i < nr; i++)
	{
		printf("\nVarsta=%d, Nume=%s, Medie=%5.2f  Nr de note=%d si urmatoarele note: ",
			vect[i].varsta, vect[i].nume, vect[i].medie, vect[i].nrNote);
		for (int j = 0; j < vect[i].nrNote; j++)
			printf("%d ", vect[i].vectNote[j]);
	}
	for (int i = 0; i < nr; i++)
		free(vect[i].nume);
	free(vect);
}