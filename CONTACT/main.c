#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#include<windows.h>
void addNewcontact(void);
void listAll(void);
void deletecontact(void);
void modifycontact(void);
int findcontact(void);
int prompt(void);
int findnum (int);


typedef struct contact {
    int number;
    char name[20];
    char phone[15];
    char email[20];
    struct contact *next;
    int count;
    } Contact;
Contact *head,*cur,*temp;
/*head is used to point to first record in list
cur points to current record in list
temp contains address of new node
*/
int cnum = 0;/*slno*/

int main()
{
    system("color f5");
    FILE *datafile;
    char *filename = "contact.dat";
    char ch;
    head = NULL;
    datafile = fopen(filename,"r");

    if(datafile)
    {
	    head = (struct contact *)malloc(sizeof(struct contact));
        cur = head;
	    while(1)
        {
		    temp = (struct contact *)malloc(sizeof(struct contact));
		    fread(cur,sizeof(struct contact),1,datafile);
		    if(cur->next == NULL)
			    break;
		    cur->next = temp;       /* pointer referencing next node*/
            cur->count=0;
		    cur = temp;             /* make current record new*/
	    }
	    fclose(datafile);                /* close file - */
	    cnum = cur->number;

    }

    do
    {
	fflush(stdin);
        printf("\nWelcome To The Contact Database\n");/* print menu messages*/
        printf("-- -----------------------------\n");
        printf("1 - Add a new contact\n\n");
        printf("2 - Delete contact\n\n");
        printf("3 - List all contacts\n\n");
        printf("4 - Modify contact\n\n");
        printf("5 - Find a contact by name\n");
        printf("-- -----------------------------\n");
        printf("Q - Save and quit\n\n");
        printf("\n\nYour choice:");
        ch = getchar();
	    ch = toupper(ch);/*changes user input case to upper case*/
        switch(ch)
        {
            case '1':
                printf("Add a new contact\n");
                fflush(stdin);
                addNewcontact();
                break;
	    case '2':
            puts("Delete a contact\n");
            system("cls");
            deletecontact();
            system("pause");
            system("cls");
            break;
	    case '3':
            puts("List all contacts\n");
            system("cls");
            listAll();
            system("pause");
            system("cls");
            break;
            case '4':
            puts("Modify a contact\n");
            system("cls");
            modifycontact();
            system("pause");
            system("cls");
            break;
	    case '5':
	        system("cls");
            puts("Find a contact by name\n");
            findcontact();
            system("pause");
            system("cls");
            break;
        case 'Q':
            puts("Save and quit\n");
            default:
            break;

        }
    }while(ch != 'Q');
    cur = head;

    if(cur == NULL)
	    return(0);

    datafile = fopen(filename,"w");

    if(datafile == NULL)
    {
	    printf("Error writing to %s\n",filename);
	    return(1);
    }

    while(cur != NULL)
    {
	    fwrite(cur,sizeof(struct contact),1,datafile);
	    cur = cur->next;
    }
    fclose(datafile);
    return(0);
}


void addNewcontact(void)
{
    system("cls");
    temp = (struct contact *)malloc(sizeof(struct contact));

    if(head==NULL)
        head = cur = temp;

    else
    {
        cur = head;
        while(cur->next != NULL)
            cur = cur->next;
            cur->next = temp;
        cur = temp;
    }
    cnum++;
    printf("contact number %d\n\n",cnum);
    cur->number = cnum;

    printf("Enter contact name:");
    gets(cur->name);
    printf("\n\nEnter contact Phone number:");
    gets(cur->phone);
    while(strlen(cur->phone)!=10){
          MessageBox(NULL, "CONTACT NUMBER SHOULD BE 10 DIGIT", "WARNING", MB_OK);
        printf("\nEnter contact Phone number:");
    gets(cur->phone);
    }

    printf("\n\nEnter contact email:");
    gets(cur->email);
    printf("contact added!");
    cur->count=0;

    cur->next = NULL;
    system("cls");
}

void listAll(void) /* list all contacts function*/
{
    system("cls");
    if(head==NULL)
        puts("There are no contacts to display!");

    else
    {
	    printf("SL NO.\t\tNAME\t\tPHONE\t\tEMAIL\n");
        puts("------ -------------------- ------------- -------------------");
                            /*prints table titles*/
        cur=head;

        do
        {

                printf("%d\t\t%s\t\t%s\t%s\n",cur->number,cur->name,cur->phone,cur->email);
                /*prints values of number, name, phone and email*/
        }while((cur=cur->next) != NULL);
    }


}

void deletecontact(void)     /*delete contact function */
{
    Contact *ptr;
    int record;
    struct contact *prev;
    if(head==NULL)
    {
        puts("There are no contacts to delete!");
	return;
    }

    listAll();		/* show all records*/
    printf("Enter contact account number to delete: ");
    scanf("%d",&record);
    cur = head;

    while(cur != NULL)
    {
        if(cur->number == record)
	{
	    if(cur == head)
        {
            head=cur->next;
            ptr=head;
        }
        else
        {
        prev->next = cur->next;/*previous pointer used if record*/
         ptr=prev->next;
        }

         while(ptr!=NULL)
         {
             ptr->number--;
             ptr=ptr->next;

         }

        free(cur); /*frees memory */
	    printf("contact %d deleted!\n",record);
	    return;
	}

	else
	{
        prev = cur;
	    cur = cur->next;
	}
    }
    printf("contact %d not found!\n",record);

 }

void modifycontact(void)   /*modify contact function*/
{
    system("cls");
    int record, result;
    if(head==NULL)
    {
        puts("There are no contacts to modify!");
	return;
    }

    listAll();		/* show all records */
    printf("Enter contact account number to modify or change: ");
    scanf("%d",&record);  /*scan user input to record*/
    result = findnum(record);

    if( result >0 ){
	    printf("Contact %d:\n",cur->number);
	    printf("Name: %s\n",cur->name);
	    if(prompt())
		    gets(cur->name);
	    printf("Phone: %s\n",cur->phone);
	    if(prompt())
		    gets(cur->phone);
	    printf("Email: %s\n",cur->email);
	    if(prompt())
		    gets(cur->email);
	    return;
	}
    printf("contact %d was not found!\n",record);
}

int findnum (int recordnum)
{

    int record;
    record = recordnum;
    cur = head;
    while(cur != NULL)
    {

        if(cur->number == record)
	     {
           return 1;
         }

	else
	{
	    cur = cur->next;
	}
    }
    return -1;
}
int findcontact(void) /* find contact function*/
{

     char buff[20];

     if(head==NULL)
	{
        puts("There are no contacts to find!");
	    return 1;
    }

    printf("Enter contact name: ");
    fflush(stdin);/*clears any text from the input stream*/
    gets(buff);

    cur = head;
    printf("SL NO.\t\tNAME\t\tPHONE\t\tEMAIL\n");
        puts("------ -------------------- ------------- -------------------");
    while(cur != NULL)
    {

        if( strcmp(cur->name, buff) == 0 )
	    {
        printf("%d\t\t%s\t\t%s\t%s\n",cur->number,cur->name,cur->phone,cur->email);
        cur=cur->next;
        }


		else
		{
			cur = cur->next;
		}
    }


}

int prompt(void)
{

	char ch;
    fflush(stdin);
	printf("Update? (Y to update any other key to not)");
	ch = getchar();
	ch = toupper(ch);
	fflush(stdin);
	if(ch == 'Y')
	{
		printf("Enter new value: ");
		return(1);
	}
	else
		return(0);
}
