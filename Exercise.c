#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N 20
#define M 5

typedef struct Poly Poly;

struct Poly{
	int syntel;
	int power;
	Poly *next;
};

int num(int multi)
{
	return (int)(((double)rand()/((double) RAND_MAX + 1))*multi);
}

Poly *create(Poly *head,Poly *last, int x, int y)
{
	//tha dhmiourgei polyonymo me tyxaies times
	Poly *temp = (Poly *)malloc(sizeof(Poly));
	if(temp == NULL)
	{
		printf("Error at allocating Memory ");
		exit(1);
	}
	temp->syntel = x;
	temp->power = y;
	temp->next = NULL;
	if(head == NULL)
		head = temp;
	else
		last->next = temp;
	return head;
}

void freept(Poly *pt)
{
	Poly *temp;
	while(pt != NULL)
	{
		temp = pt;
		pt = pt->next;
		free(temp);
	}
}

Poly *usage()
{
	Poly *head,*last;
	head = last = NULL;
	int power,number1;
	power = number1 = 0;
	while(num(M))
	{
		if( (number1 = num(N)) == 0)
		{
			power++;
			continue;
		}
		else
		{
			head = create(head, last, number1, power);
			power++;
			if(head->next == NULL)
				last = head;
			else 
				last = last->next;
		}
	}
	return head;
}

Poly *POLYadd(Poly *p, Poly *q)
{
	//tha kanei prosthesi polyonimwn
	Poly *neo,*neol,*temp,*temp2;
	neo = neol = temp = temp2 = NULL;
	while(p != NULL)
	{
		neo = create(neo, neol, p->syntel, p->power);
		if(neo->next == NULL)
			neol = neo;
		else
			neol = neol->next;
		p = p->next;
	}
	temp = neo;
	while( temp != NULL && q != NULL)
	{
		if(temp->power == q->power)
		{
			temp->syntel += q->syntel;
			q = q->next;
		}
		else if(temp->next != NULL)
		{
			if( (temp->next->power > q->power) && (temp->power < q->power) )
			{
				temp2 = create(temp2,temp2,q->syntel,q->power);
				temp2->next = temp->next;
				temp->next = temp2;
				temp2 = NULL;
				q = q->next;
				temp = temp->next;
			}
			else
				temp = temp->next;
		}
		else if(temp->next == NULL)
			temp = temp->next;

 	}
 	while(q != NULL)
 	{
 		neo = create(neo,neol,q->syntel,q->power);
 		if(neo->next == NULL)
 			neol = neo;
 		else
 		    neol = neol->next;
 		q = q->next;
 	}
    return neo;
}

Poly *POLYsub(Poly *p, Poly *q)
{
	//tha kanei afairesh polyo
	Poly *temp = q;
	while(temp != NULL)
	{
		temp->syntel *= (-1);
		temp = temp->next;
	}
	temp = POLYadd(p,q);
	while(q != NULL)
	{
		q->syntel *= (-1);
		q = q->next;
	}
	return temp;
}

Poly *POLYmult(Poly *p, Poly *q)
{
	//tha kanei pollaplasiasmo poly
	Poly *temp,*neos,*neosl,*ret;
	temp = neos = ret = NULL;
    while(p !=NULL)
    {
    	temp = q;
    	while(temp != NULL)
    	{
 	 		neos = create( neos,neosl,(p->syntel)*(temp->syntel),(p->power)+(temp->power) );
			if(neos->next == NULL)
				neosl = neos;
			else
				neosl = neosl->next;
   			temp = temp->next;
   		}
   		if(ret == NULL)
   			ret = neos;
   		else
   		{
   			ret = POLYadd(ret,neos);
   			freept(neos);
   		}
   		neos = neosl = NULL;
   		p = p->next;
   }
   return ret;
}

Poly *POLYdiff(Poly *p)
{
	//tha kanei paragwgish polyo
	if( p == NULL)
		return p;
	if(p->power == 0)
		p = p->next;
	Poly *temp = p;
	while(temp != NULL)
	{
		temp->syntel = (temp->syntel)*(temp->power);
		temp->power = --(temp->power);
		temp = temp->next;
	}
	return p;
}

int  POLYeval(Poly *p, int x)
{
	//apotimhsh polyo
	int apotelesma = 0;
	while(p != NULL)
	{
		apotelesma += (p->syntel)*((int)pow(x, p->power));
		p = p->next;
	}
	return apotelesma;
}

void POLYprint(Poly *p)
{
	//ektypwnei to polyo
	while(p != NULL)
	{
		printf("%dx^%d ",p->syntel, p->power);
		p = p->next;
	}
	printf("\n");
}

void main(void)
{
	srand(time(NULL));
	printf("The input is random-generated\n");
	int value;
	Poly  *poly1,*poly2,*poly3,*poly4;
	poly1 = poly2 = poly3 = poly4 = NULL;
	poly1 = usage();
	poly2 = usage();
	printf("Poly1: ");
	POLYprint(poly1);
	printf("Poly2: ");
	POLYprint(poly2);
	poly3 = POLYadd(poly1, poly2);
	poly3 = POLYmult(poly3, poly3);
	printf("Poly3: ");
	POLYprint(poly3);
	poly4 = POLYdiff(poly1);
	printf("Poly4: ");
	POLYprint(poly4);
	poly3 = POLYsub(poly3, poly4);
	printf("Poly3: ");
	POLYprint(poly3);
	printf("Give Input to evaluate: ");
	scanf("%d",&value);
	printf("Result: %d\n",POLYeval(poly3,value));
	free(poly1);
	free(poly2);
	free(poly3);
	free(poly4);
}
