#include "cda.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

 struct cda 
{
    int arraySize,arrayCapacity,debugFlag;

    void (*display)(void *,FILE *);
    void (*free)(void*, void*);

    void **data;
    void *items;
    void *value;
    void *front;
    void *back;
    void *recipient;
    void *donor;
    void *fp;
};

CDA *newCDA(void)
{
    CDA *P = malloc(sizeof(CDA));

    assert(P != 0);

    P->arraySize = 0;
    P->arrayCapacity = 1;
    P->debugFlag = 0;
    P->free = 0;
    P->display = 0;

    P->data = malloc(sizeof(void*));
    
    return P;
}

void setCDAdisplay(CDA *items, void (*display)(void *,FILE *))
{
    items->display = display;
}

void setCDAfree(CDA *items, void (*free)(void *))
{
    items->free = free;
}

void insertCDA(CDA *items,int index,void *value) //create a function to fix indexes
{
    assert (index >= items->back && index <= items->front);
    
    void *P;

    items->front = items->data[items->arraySize];
    items->back = items->data[0];

    if(items->arraySize == items->arrayCapacity)
    {
        P = realloc(items->data, sizeof(items->arrayCapacity*2));
        items->arrayCapacity = items->arrayCapacity*2;
    }

    if(index == items->arraySize)
    {
        items->front = value;
        items->front--;
    }

    if(index == 0)
    {
       items->back = value;
       items->back++;
    }

    else
    {
        void *newValue = value;
        void *curValue = items->data[index];
        void *temp = 0;
        int i;
       
        if(index < items->arraySize/2)
        {
            void *temp1 = items->data[index];
            void *temp2 = 0;
    
            items->data[index] = value;
            
            for(int i = index;index < items->back; i++)
            {
                temp2 =items->data[i+1];
                items->data[i+1] = temp1;
                temp1 = temp2;
            }
        }

        if(index > items->arraySize/2)
        {
            void *temp1 = items->data[index];
            void *temp2 = 0;
    
            items->data[index] = value;
            
            for(int i = index;index > items->back; i++)
            {
                temp2 =items->data[i+1];
                items->data[i+1] = temp1;
                temp1 = temp2;
            }
        }
    }
}

void *removeCDA(CDA *items,int index)
{

}
void unionCDA(CDA *recipient,CDA *donor)
{
    
}

void *getCDA(CDA *items,int index)
{
    return items->data[index];
}

void *setCDA(CDA *items,int index,void *value)
{
    void *temp = items->data[index];
    if(index == items->arraySize);
    {
        insertCDAfront(items,value);
    }
}

int  sizeCDA(CDA *items)
{
    return items->arraySize;
}

void displayCDA(CDA *items,FILE *fp)
{

}

int  debugCDA(CDA *items,int level)
{
    void *temp = items->debugFlag;
    items->debugFlag = level;
    return temp;
}


void freeCDA(CDA *items)
{

}
