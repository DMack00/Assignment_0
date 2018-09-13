#include "da.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"



 struct da 
{
    int arraySize,arrayCapacity,debugFlag;

    void (*display)(void *,FILE *);
    void (*free)(void *);

    void **data;  
};


DA *newDA(void)
{
    DA *P = malloc(sizeof(DA));

    assert(P != 0);

    P->arraySize = 0;
    P->arrayCapacity = 1;
    P->debugFlag = 0;
   
    P->data = malloc(sizeof(void*));
    
    return P;
}

void setDAdisplay(DA *d,void (*f)(void *,FILE *))
{
    d->display = f;
}

void setDAfree(DA *d,void (*f)(void *))
{
    d->free = f;
}

void insertDA(DA *items, int index, void *value)
{

 assert(sizeof(items) != 0);   
 assert(index >= 0 && index <= items->arraySize);
    
    if(items->arraySize == items->arrayCapacity)
    {
        items->data = realloc(items->data, sizeof(void*)*(items->arrayCapacity*2));
        items->arrayCapacity = items->arrayCapacity*2;
    }
    
    
    if(index == items->arraySize)
    {
        items->data[index] = value;
    }
    
    if (index < items->arraySize)
    {
        void *temp1 = items->data[index];
        void *temp2 = 0;
        
        
        items->data[index] = value;
        
        for(int i = index;i < items->arraySize; i++)
        {
            temp2 =items->data[i+1];
            items->data[i+1] = temp1;
            temp1 = temp2;
        }
    }
    
    items->arraySize++;
}

void *removeDA(DA *items, int index)
{
    void *temp = items->data[index];
    assert(items->arraySize > 0);
    assert(index <= items->arraySize);

    if(index == items->arraySize)
    {
        items->arraySize--;
    }
    
    if(index < items->arraySize )
    {
        void *newValue = items->data[index+1];
        void *curValue = items->data[index];
        void *temp = 0;
        int i;
        
        for(i = index; i < items->arraySize; i++)
        {
            curValue = items->data[i];
            temp = curValue;
            curValue = newValue;
            newValue = temp;
        }
    }

    if(items->arraySize < (items->arrayCapacity/4))
    {
        items->data = realloc(items->data, sizeof(void*)* (items->arrayCapacity/2));
        items->arrayCapacity = (items->arrayCapacity/2);
    }
    items->arraySize--;
    return temp;
}
 
void unionDA(DA *recipient, DA *donor)
{
    for(int i = 0; i < donor->arraySize; i++)
    {
        insertDA(recipient,recipient->arraySize,donor->data[i]);
    }
    donor->arraySize = 0;
    donor->arrayCapacity = 1;

}

void *getDA(DA *items, int index)
{
    void *temp = items->data[index];
    return temp;
}

void *setDA(DA *items, int index, void *value)
{
    assert(index >= 0 && index <= items->arraySize);
    void *temp = 0;
    if(index == items->arraySize)
    {
        temp = items->data[index];
        insertDA(items,index,value);
    }

    else 
    {
        temp =items->data[index];
        items->data[index] = value;
    }
    return temp;
}

int sizeDA(DA *items)
{
    return items->arraySize;
}

void displayDA(DA *items, FILE *fp)
{
   
    fprintf(fp,"[");
    //fprintf(stdout ,"[%d]\n",items->debugFlag);
    
    //Debug flag is set
    if(items->debugFlag != 0) 
    {
        if(items->arraySize == 0)
        {
            fprintf(fp,"[%d]",items->arrayCapacity - items->arraySize);
        }
        if(items->display != 0) 
        {
            for (int i = 0; i < items->arraySize; i++)
            {
                items->display(items->data[i],fp);
                fprintf(fp,",");
            }
            fprintf(fp,"[%d]]", items->arrayCapacity - items->arraySize);
        }
        else if(items->display == 0)
        {
            for(int i = 0; i < items->arraySize; i++)
            {
                fprintf(fp,"@%p,",items->data[i]);
            }
            fprintf(fp,"[%d]]",items->arrayCapacity - items->arraySize);
        }
    }
    
    //Debug flag is not set
    if(items->debugFlag == 0)
    {
        if(items->display != 0)
        {
            //fprintf(stdout ,"[%s]\n", "display != 0");
            for (int i = 0; i < items->arraySize; i++)
            {
                items->display(items->data[i],fp);
        
                //If not last element
                 if(i != items->arraySize - 1)
                 {
                   fprintf(fp,",");
                 }
            }
            items->display(items->data[items->arraySize],fp);
                fprintf(fp,"]");
        }

        //This one works
        if(items->display == 0)
        {
            for(int i = 0; i < items->arraySize; i++)
            {
                fprintf(fp,"@%p",items->data[i]);
                //Dont print last comma
                if(i != items->arraySize - 1)
                {
                    fprintf(fp,",");
                }
            }
                fprintf(fp,"]");
        }  
    }
        
    
    fprintf(fp,"]");

}

int debugDA(DA *items, int level)
{
    int temp = items->debugFlag;
    items->debugFlag = level;
    return temp;
}

void freeDA(DA *items)  
{
    if (items->free != 0)
    {
        for(int i = 0; i < items->arraySize; i++)
        {
            items->free(items->data[i]);
        } 
    }
    free(items->data);
    free(items);
    
}
