#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data[200],binary[26],ones,implicants;
    char str[26];
    struct node* next;
};

int var,minterm,number=1,COL=2,check=1,select=0,size,imptable[100][100],counter=0,essenterms[200],q=0,num=0;
struct node *head1,*head,*head2,*head3,*head4;
char ch1[26],ch2[26];
void sorting()
{
    struct node *temp1,*temp2;
    temp1=temp2=head1;
    while(temp1!=NULL)
    {
        temp2=head1;
        while(temp2!=NULL)
        {
            if(temp1->data[0]<temp2->data[0])
            {
                swap(temp1,temp2);
            }
            temp2=temp2->next;
        }
        if(temp1->next==NULL)
        {
            size=temp1->data[0];
        }
        temp1=temp1->next;
    }
}

void swap(struct node* temp1,struct node* temp2)
{
    int x,y,i=0;
    i=var;
    for(i=0;i<var;i++)
    {
        y=temp1->binary[i];
        temp1->binary[i]=temp2->binary[i];
        temp2->binary[i]=y;
    }
    y=temp1->ones;
    temp1->ones=temp2->ones;
    temp2->ones=y;
    x=temp1->data[0];
    temp1->data[0]=temp2->data[0];
    temp2->data[0]=x;
}

void table1()
{
    int i,count=0,j;
    struct node* temp;
    struct node* next;
    struct node* head3;
    temp=head3=head1;
    head1=next=(struct node*)malloc(sizeof(struct node));
    for(i=0;i<=var;i++)
    {
        temp=head3;
        while(temp!=NULL)
        {
            if(temp->ones==i)
            {
                next->data[0]=temp->data[0];
                for(j=0;j<var;j++)
                {
                    next->binary[j]=temp->binary[j];
                }
                next->ones=temp->ones;
                next=next->next=(struct node*)malloc(sizeof(struct node));
            }
            temp=temp->next;
        }
    }
    next->next=NULL;
}

void disp()
{
    int i,j=minterm;
    struct node* temp;
    temp=head1;
    printf("\n\nTABLE::%d\n\n\n",number);
    while(temp->next!=NULL)
    {
        printf("%d\t",temp->data[0]);
        for(i=var-1;i>=0;i--)
        {
            printf("%d",temp->binary[i]);
        }
        temp=temp->next;
        printf("\n");
    }
    temp->next=NULL;
    number++;
}

void end_loop(struct node* ptr)
{
    struct node* temp;
    temp=ptr;
    while(temp->next->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=NULL;
}

void further_groupings()
{
    int i,count,k,j,x;
    struct node *temp,*next,*p,*imp;
    check=0;
    if(COL==2)
    {
        imp=head2=(struct node*)malloc(sizeof(struct node));
        p=head;
        next=head1->next;
        temp=head1;
    }
    else
    {
        imp=head3;
        head1=head;
        temp=head1;
        next=head1->next;
        p=head=(struct node*)malloc(sizeof(struct node));
    }
    implicants(head1);
    printf("\n\nTABLE%d\n\n\n",number);
    while(temp!=NULL)
    {
        next=temp->next;
        while(next!=NULL)
        {
            count=0;
            if(next->ones-temp->ones==1)
            {
                for(i=0;i<var;i++)
                {
                    if(temp->binary[i]!=next->binary[i])
                    {
                        k=i;
                        count++;
                    }
                }
            }
            if(count==1)
            {
                temp->implicants=0;
                next->implicants=0;
                select++;
                check++;
                for(i=0;i<var;i++)
                {
                    p->binary[i]=temp->binary[i];
                }
                p->binary[k]=-1;
                x=0;
                for(j=0;j<COL/2;j++)
                {
                    p->data[x]=temp->data[j];
                    x++;
                }
                for(j=0;j<COL/2;j++)
                {
                    p->data[x]=next->data[j];
                    x++;
                }
                p->ones=temp->ones;
                for(j=0;j<COL;j++)
                {
                    printf("%d,",p->data[j]);
                }
                printf("\t");
                for(i=var-1;i>=0;i--)
                {
                    if(p->binary[i]==-1)
                        printf("-");
                    else
                        printf("%d",p->binary[i]);
                }
                printf("\n");
                p=p->next=(struct node*)malloc(sizeof(struct node));
            }
            next=next->next;
        }
        temp=temp->next;
    }
    p->next=NULL;
    if(check!=0)
    {
        end_loop(head);
    }
    temp=head1;
    while(temp!=NULL)
    {
        if(temp->implicants==1)
        {
            i=0;
            for(i=0;i<COL/2;i++)
            {
                imp->data[i]=temp->data[i];
            }
            imp->data[i]=-1;
            for(i=0;i<var;i++)
            {
                imp->binary[i]=temp->binary[i];
            }
            imp=imp->next=(struct node*)malloc(sizeof(struct node));
        }
        temp=temp->next;
    }
    head3=imp;
    COL=COL*2;
    number++;
}

int difference(struct node* p,struct node* q)
{
    int i,count=0,j;
    for(i=0;i<var;i++)
    {
        if(p->binary[i]!=q->binary[i])
        {
            j=i;
            count++;
        }
    }
    if(count==1)
    {
        q->binary[j]=-1;
        return 1;
    }
    return 0;
}

void display_implicants()
{
    int i=0;
    struct node* temp;
    temp=head2;
    printf("\n\nThe prime implicants :n\n");
    while(temp!=NULL)
    {
        i=0;
        while(temp->data[i]!=-1)
        {
            printf("%d,",temp->data[i]);
            i++;
        }
        printf("\t\t");
        i=var-1;
        while(i>=0)
        {
            if(temp->binary[i]==-1)
            {
                printf("-");
            }
            else
            {
                printf("%d",temp->binary[i]);
            }
            i--;
        }
        temp=temp->next;
        printf("\n");
        counter++;
    }
}

void implicants(struct node* ptr)
{
    struct node* temp;
    temp=ptr;
    while(temp!=NULL)
    {
        temp->implicants=1;
        temp=temp->next;
    }
}

void collect()
{
    int common=0,i;
    struct node *temp1,*temp2,*temp3;
    temp1=temp2=head2;
    while(temp1!=NULL)
    {
        temp2=temp1->next;
        while(temp2!=NULL)
        {
            common=0;
            for(i=0;i<var;i++)
            {
                if(temp2->binary[i]==temp1->binary[i])
                {
                    common++;
                }
            }
            if(common==var)
            {
                temp3=head2;
                while(temp3->next!=temp2)
                {
                    temp3=temp3->next;
                }
                temp3->next=temp2->next;
                temp2=temp3;
            }
            temp2=temp2->next;
        }
        temp1=temp1->next;
    }
}

void variables()
{
    int i;
    for(i=0;i<26;i++)
    {
        ch1[i]=65+i;
        ch2[i]=97+i;
    }
}

void convert()
{
    int i,j;
    struct node* temp;
    temp=head4;
    while(temp!=NULL)
    {
        j=0;
        for(i=0;i<var;i++)
        {
            if(temp->binary[i]==0)
            {
                temp->str[j]=ch2[i];
                j++;
            }
            if(temp->binary[i]==1)
            {
                temp->str[j]=ch1[i];
                j++;
            }
        }
        temp=temp->next;
    }
}

void func()
{
    struct node* temp;
    temp=head4;
    printf("\n\nThe minimized function is : ");
    while(temp!=NULL)
    {
        printf("%s",temp->str);
        if(temp->next!=NULL)
        {
            printf(" + ");
        }
        temp=temp->next;
    }
}

void implicants_table()
{
    struct node* temp;
    int i,j,k,m,n,x,y,count=0,count2=0;
    for(i=0;i<counter;i++)
    {
        for(j=0;j<=size;j++)
        {
            imptable[i][j]=0;
        }

    }

    i=0;
    j=0;
    k=0;
    temp=head2;
    while(temp!=NULL)
    {
        k=0;
        while(temp->data[k]!=-1)
        {
            imptable[i][temp->data[k]]=1;
            k++;
        }
        i++;
        temp=temp->next;
    }

    for(i=0;i<counter;i++)
    {
        for(j=0;j<=size;j++)
        {
            count=0;
            if(imptable[i][j]==1)
            {
                y=j;
                x=i;
                for(k=0;k<counter;k++)
                {
                    if(imptable[k][j]==1)
                    {
                        count++;
                    }
                }
                if(count==1)
                {
                    essenterms[q]=x;
                    q++;
                    for(n=0;n<=size;n++)
                    {
                        if(imptable[i][n]==1)
                        {
                            for(m=0;m<counter;m++)
                            {
                                imptable[m][n]=0;
                            }
                        }
                    }
                }
            }
        }
    }

    essenterms[q]=-1;
    i=0;

}

void other_implicants()
{

    num=0;
    int count1=0,count2=0;
    int i,j;
    for(i=0;i<counter;i++)
    {
        count1=0;
        for(j=0;j<=size;j++)
        {
            if(imptable[i][j]==1)
            {
                num++;
                count1++;
            }
        }
        if(count1>count2)
        {
            essenterms[q]=i;
            count2=count1;
        }
    }
    for(j=0;j<=size;j++)
    {
        if(imptable[essenterms[q]][j]==1)
        {
            for(i=0;i<counter;i++)
            {
                imptable[i][j]=0;
            }
        }
    }

    q++;
    essenterms[q]=-1;

    if(num>0)
    {
        other_implicants();
    }
}

void final_terms()
{
    int i=0,j,c=0,x;
    struct node *temp,*ptr;
    head4=temp=(struct node*)malloc(sizeof(struct node));
    while(essenterms[i]!=-1)
    {
        ptr=head2;
        x=essenterms[i];
        for(j=0;j<x;j++)
        {
            ptr=ptr->next;
        }
        j=0;
        while(ptr->data[j]!=-1)
        {
            temp->data[j]=ptr->data[j];
            j++;
        }
        temp->data[j]=-1;
        for(j=0;j<var;j++)
        {
            temp->binary[j]=ptr->binary[j];
        }
        temp=temp->next=(struct node*)malloc(sizeof(struct node));
        i++;
        c++;
    }
    temp->next=NULL;
}
int main()
{
    int i,j,k,x;
    struct node* temp;
    printf("\nASSIGNMENT 2017\n");
    printf("\nNAME: ASHISH VARSHNEY\n");
    printf("\nFACULTY NO: 16PEB544\n");
    printf("\nENROLLMENT NO:GH6329\n");
    printf("\nSubject CODE :CO207\n");
    printf("\nSubmitted To:Prof.M.M. Sufyan Beg");
    printf("\n--------------------TABULATION METHOD------------------\n");
    printf("\nEnter the number of variables : ");
    scanf("%d",&var);
    printf("\nEnter the number of minterms : ");
    scanf("%d",&minterm);
    i=minterm-1;
    head1=temp=(struct node*)malloc(sizeof(struct node));
    printf("\nEnter the minterms \n\n");
    scanf("%d",&temp->data[0]);
    j=temp->data[0];
    temp->ones=0;
    x=var;
    k=0;
    while(x--)
    {
        if(j%2==1)
        {
            temp->binary[k]=1;
            temp->ones++;
        }
        else
        {
            temp->binary[k]=0;
        }
        j/=2;
        k++;
    }
    while(i--)
    {
        temp=temp->next=(struct node*)malloc(sizeof(struct node));
        scanf("%d",&temp->data[0]);
        j=temp->data[0];
        temp->ones=0;
        x=var;
        k=0;
        while(x--)
        {
            if(j%2==1)
            {
                temp->binary[k]=1;
                temp->ones++;
            }
            else
            {
                temp->binary[k]=0;
            }
            j/=2;
            k++;
        }
    }
    temp->next=NULL;
    sorting();
    table1();
    disp();
    end_loop(head1);
    head=(struct node*)malloc(sizeof(struct node));
    while(check>0)
    {
        further_groupings();
    }
    head3->next=NULL;
    printf("no more implcants\n\n");
    end_loop(head2);
    collect();
    display_implicants();
    variables();

    implicants_table();
    other_implicants();
    final_terms();
    end_loop(head4);
    convert();
    func();
    printf("\n **** '0' represents small letter and '1' represents capital letter\n");
    printf("\n------THANKYOU--------\n");

    return 0;
}

