
//  Programming and Algorithm coursework 3


#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX 10
#define EMPTY -1

/*  Functions prototypes */
char start_program(char expression[]);



char check_prefix_post_infix(char x[]);

//-------------------------------------------------------------------------------------------------

float EvaluatePostfix(char str[]);
void evaluation_push (int data);
int evaluation_pop ();

struct node {
    int data;
    struct node *next;
};

struct node *top = NULL;

/* create a new node with the given data */
struct node* createNode(int data) {
    struct node *ptr = (struct node *) malloc(sizeof (struct node));
    ptr->data = data;
    ptr->next = NULL;
}


//------------------------------------------------------------------------------------
/* infix to postfix */

struct stack
{
	char data[MAX];
	int top;
};

int isempty(struct stack *s);
void emptystack(struct stack* s);
void in2post_push(struct stack* s,int item);
char in2post_pop(struct stack* s);
int isoperator(char e);
int priority(char e);
void infix_to_postfix(char* infix, char * postfix, int insertspace);


//-------------------------------------------------------------------------------------------------
/* infix to prefix */

void in2pre_push(struct stack* s,int item);
char in2pre_pop(struct stack* s);
void infix_to_prefix(char* infix, char * prefix, int insertspace);

//---------------------------------------------------------------------------------------------------
/* prefix to infix */

void push2(int *x);
char *pop2();

void prefix_to_infix (char exp[100]);

struct pre2in
 {
    char exp[100];
    struct stack *next;

};

struct pre2in *top2 = NULL;

//---------------------------------------------------------------------------------------------------
/* postfix to infix */

void push1(int *x);
char *pop1();

void postfix_to_infix (char exp[100]);

struct post2in
 {
    char exp[100];
    struct stack *next;

};

struct post2in *top1 = NULL;

//-----------------------------------------------------------------------------------------------------
/* postfix to prefix */

void post_to_pre(char exp[]);

//-------------------------------------------------------------------------------------------------------
/* prefix to postfix */

void pre_to_post(char exp[]);

//-------------------------------------------------------------------------------------------------------

float EvaluatePrefix(char exp[]);
float EvaluateInfix(char exp[]);

//-------------------------------------------------------------------------------------------------
void FILE_prefix_to_infix (char exp[100]);
void FILE_postfix_to_infix (char exp[100]);
void FILE_post_to_pre(char exp[]);
void FILE_pre_to_post(char exp[]);
float FILE_EvaluatePostfix(char str[]);          // functions for file part
float FILE_EvaluatePrefix(char exp[]);
float FILE_EvaluateInfix(char exp[]);
char FILE_start_program(char expression[]);
char FILE_check_prefix_post_infix(char x[]);

//------------------------------------------------------------------------------


char pre_to_postBOX[100];
char post_to_preBOX[100];     // global variables
char post_to_inBOX[100];
char FILE_pre_to_postBOX[100];
char FILE_post_to_preBOX[100];
char FILE_post_to_inBOX[100];
//---------------------------------------

struct check {
        int data;
        struct check *next;
  };
  struct check *head = NULL;


  struct node* createStack (int data) {
        struct check *ptr = (struct check *) malloc(sizeof (struct check));
        ptr->data = data;
        ptr->next = NULL;
  }

void push(int data);
int pop();





int main() {

    char expression[50] = { 0 };

    int choice1;
    char entered_location[60];

    printf("********************************************************************************************");
    printf("\n\t\t\tExpression Conversion & Evaluation Program\t\t\t\n");
    printf("********************************************************************************************");

    printf("\n\nWelcome!\nDo you want to read expression from file or enter expression with default input(keyboard)?\nChoose  (1) from file\n\t(2) from keyboard\n");
    scanf(" %d", &choice1);

    if(choice1 == 1) {

    char location[] = "c:\\G51PGA\\default.txt";

        printf("\nPlease enter the location of your file:\n");   // ask user for file location
        scanf("%s", &entered_location);


        if(strcmp(entered_location, location) == 0){        // if the location that user enter is correct, then read the content in the file
                                                            // if not correct, then end program
            FILE * fpointer;

            fpointer = fopen("c:\\G51PGA\\default.txt", "r");       // read from file and print the content of the file om the screen

            char singleLine[50];

            printf("\nRead from file: ");

           while(!feof(fpointer)) {

            fgets(singleLine, 50, fpointer);
            puts(singleLine);
           }
    fclose(fpointer);

    FILE_start_program(singleLine);    // call functions for FILE

    } else{

    printf("\nYou have entered a wrong directory.\nPlease try again next time.\n");
    printf("\nEND OF PROGRAM\n");
    return 0;

    }

    } else if(choice1 == 2) {


    printf("\nPlease enter an expression from keyboard (Need to have spaces in between):\nFor example ( 5 + 2 ):\n");         // prompt input from user
    scanf(" %20[^\n]", expression);

    int i;
    for(i=0;i<=strlen(expression);i++) {

    while(expression[i] >='a' && expression[i] <='z' || expression[i] >='A' && expression[i] <='Z' )
        {
        printf("\nI'm sorry to inform that there's characters in your expression.");                   // if expression has characters in them, there's error
        printf("\nPlease enter only integers and have spaces in between\nFor example(5 + 2):\n");

        scanf(" %20[^\n]", expression);
        }
    }
            FILE * fpointer;

            fpointer = fopen("c:\\G51PGA\\input.txt", "w");

            fprintf(fpointer, "Your input: %s", expression);

            fclose(fpointer);


    start_program(expression);    // call functions for default input

    }

return 0;
}

// END OF PROGRAM

//-----------------------------------------------------------------------------------

char start_program(char expression[]) {

    char choice;
    int i, flag = 0, data = 0;
    char str[100];

    strcpy(str, expression);

     for (i = 0; i < strlen(str); i++) {        // check if expression is balanced, if it's not balanced, end program

                if (str[i] == '(' || str[i] == '{'
                        || str[i] == '[') {
                                push(str[i]);
                                continue;
                }
                if (str[i] == ')' || str[i] == '}' || str[i] == ']') {

                        data = pop();
                        if ((str[i] == ')' && data != '(') || data == -1 ||
                                (str[i] == '}' && data != '{') ||
                                        (str[i] == ']' && data != '[')) {

                                flag = 1;
                                break;
                        }

                }
        }

        if (flag == 1 || head != NULL){
                printf("\nExpression is not balanced.\nPlease try again next time.\n\n");
                printf("END OF PROGRAM\n");
                return 0; }
        else {
                printf("\nExpression is balanced\n\n");
        }


    printf("Please choose an option:\n(A)Convert to infix, prefix, postfix\n(B)Evaluate\n(C)Exit\n\n");         // user choose what to do next with the expression
    scanf(" %c", &choice);



    if (choice == 'C') {
        printf("Thank you for using this program.\n");
        return 0;
    }
    else
        if (choice == 'A') {

            printf("\n");                                                   // options triggered depends on choice
            check_prefix_post_infix(expression);

        }
        else
            if (choice == 'B')
            {

                // determine what type of expression entered then only evaluate

                if (expression[(strlen(expression)-1)] == '+' || expression[(strlen(expression)-1)] == '-' || expression[(strlen(expression)-1)] == '*' || expression[(strlen(expression)-1)] == '/' || expression[(strlen(expression)-1)] == '^')

                {

                    printf("\nYou have entered a postfix expression to evaluate.\n");
                    EvaluatePostfix(expression);                  // call postfix evaluation function

                } else
                    if (expression[0] == '+' || expression[0] == '-' || expression[0] == '*' || expression[0] == '/' || expression[0] == '^' )

                    {

                        printf("\nYou have entered a prefix expression to evaluate.\n");
                        EvaluatePrefix(expression);                // call prefix evaluation function

                    } else

                    {
                        printf("\nYou have entered a infix expression to evaluate.\n");
                        EvaluateInfix(expression);                  // call infix evaluation function
                    }

            }

    return 0;

    // End of program

}


//------------------------------------------------------------------------------------------------------------------------


// check whether inputs are prefix, postfix or infix

char check_prefix_post_infix(char x[]) {


    char option;
    char post[50] = { 0 };
    char pre[50] = { 0 };
    char yolo[50];          // for prefix to postfix
    char solo[50];          // for postfix to prefix

        strcpy(yolo, x);
        strcpy(solo, x);

    // all conversion outputs will be written in new file output.txt


    if (x[0] == '+' || x[0] == '-' || x[0] == '*' || x[0] == '/' || x[0] == '^' )

    {


        printf("This is a prefix expression.\n");                           // if first character is operator, then it's prefix
        printf("Do you want to convert it to \n(A) postfix \n(B) infix \n(C) both? \nSelect A, B or C option:\n\n");
        scanf(" %c", &option);

        switch (option) {


            case 'A':

                pre_to_post(x);
                printf("\nPrefix to postfix is: %s\n", pre_to_postBOX);

                FILE * fpointer;

                fpointer = fopen("c:\\G51PGA\\output.txt", "w");

                fprintf(fpointer, "Prefix to postfix: %s", pre_to_postBOX);

                fclose(fpointer);

                break;

            case 'B':

                prefix_to_infix(x);
                break;

            case 'C':

                prefix_to_infix(x);
                pre_to_post(yolo);
                printf("\nPrefix to postfix is: %s\n", pre_to_postBOX);

                fpointer = fopen("c:\\G51PGA\\output.txt", "a");

                fprintf(fpointer, "\nPrefix to postfix: %s", pre_to_postBOX);

                fclose(fpointer);


                break;

            }

        return 0;

    } else

        if (x[(strlen(x)-1)] == '+' || x[(strlen(x)-1)] == '-' || x[(strlen(x)-1)] == '*' || x[(strlen(x)-1)] == '/' || x[(strlen(x)-1)] == '^')

        {

            printf("This is a postfix expression.\n");                          // if last character is operator, then it's postfix
            printf("Do you want to convert it to \n(A) infix \n(B) prefix \n(C) both? \nSelect A, B or C option:\n\n");
            scanf(" %c", &option);

            switch (option) {

                case 'A':
                    postfix_to_infix(x);
                    printf("\nPostfix to infix is: %s\n", post_to_inBOX);
                    FILE * fpointer;

                    fpointer = fopen("c:\\G51PGA\\output.txt", "w");

                    fprintf(fpointer, "Postfix to infix: %s", post_to_inBOX);

                    fclose(fpointer);
                    break;

                case 'B':

                    post_to_pre(x);
                    printf("\nPostfix to prefix is: %s\n", post_to_preBOX);

                    fpointer = fopen("c:\\G51PGA\\output.txt", "w");

                    fprintf(fpointer, "Postfix to prefix: %s", post_to_preBOX);

                    fclose(fpointer);
                    break;

                case 'C':

                    postfix_to_infix(x);
                    printf("\nPostfix to infix is: %s\n", post_to_inBOX);

                    fpointer = fopen("c:\\G51PGA\\output.txt", "w");

                    fprintf(fpointer, "Postfix to infix: %s", post_to_inBOX);

                    fclose(fpointer);

                    post_to_pre(solo);
                    printf("\nPostfix to prefix is: %s\n", post_to_preBOX);

                    fpointer = fopen("c:\\G51PGA\\output.txt", "a");

                    fprintf(fpointer, "\nPostfix to prefix: %s", post_to_preBOX);

                    fclose(fpointer);
                    break;
                }
            return 0;

        } else



    printf("This is an infix expression.\n");                                                                            //   if not both, then it's infix
    printf("Do you want to convert it to \n(A) prefix \n(B) postfix \n(C) both? \nSelect A, B or C option:\n\n");
    scanf(" %c", &option);



    switch (option) {

            // options triggered according to user inputs


        case 'A':

            infix_to_prefix(&x[0], &pre[0], 1);
            printf("\nInfix to prefix is : %s\n\n",&pre[0]);              // call prefix function

            FILE * fpointer;

            fpointer = fopen("c:\\G51PGA\\output.txt", "w");

            fprintf(fpointer, "Infix to prefix: %s",&pre[0]);

            fclose(fpointer);

            break;

        case 'B':

            infix_to_postfix(&x[0], &post[0], 1);             // call postfix function
            printf("\nInfix to postfix is : %s\n\n",&post[0]);

            fpointer = fopen("c:\\G51PGA\\output.txt", "w");

            fprintf(fpointer, "Infix to postfix: %s",&post[0]);

            fclose(fpointer);

            break;

        case 'C':

            infix_to_prefix(&x[0], &pre[0], 1);
            printf("\nInfix to prefix is : %s\n",&pre[0]);


            fpointer = fopen("c:\\G51PGA\\output.txt", "w");

            fprintf(fpointer, "Infix to prefix: %s",&pre[0]);

            fclose(fpointer);

            infix_to_postfix(&x[0], &post[0], 1);
            printf("\nInfix to postfix is : %s\n",&post[0]);


            fpointer = fopen("c:\\G51PGA\\output.txt", "a");

            fprintf(fpointer, "\nInfix to postfix: %s",&post[0]);

            fclose(fpointer);

            break;

    }


    return 0;

}



//----------------------------------------------------------------------------------------------------------------
// Functions to check paranthesis balance

 void push(int data) {
        struct check *temp, *ptr = createStack(data);
        if (head == NULL) {
                head = ptr;
                return;
        }
        temp = head;
        ptr->next = temp;
        head = ptr;
  }


  int pop() {
        int data;
        struct check *temp;
        if (head == NULL)
                return -1;
        data = head->data;
        temp = head;
        head = temp->next;
        free (temp);
        return (data);
  }
//--------------------------------------------------------------------------------------------------------------

/*  change infix to prefix  */

void infix_to_prefix(char* infix, char * prefix, int insertspace)
{

	struct stack X;
	emptystack(&X);
    char n1;
	char *i,*p;

	i = &infix[0];
	p = &prefix[0];

	strrev(infix);    // reverse the input

	while(*i)
	{
		while(*i == ' ' || *i == '\t')
		{
			i++;
		}

		if( isdigit(*i) || isalpha(*i) )
		{
			while( isdigit(*i) || isalpha(*i))
			{
				*p = *i;
				p++;
				i++;
			}

			if(insertspace)
			{
				*p = ' ';     // add spaces
				p++;
			}

		}

		if( *i == '(' )
		{
			in2pre_push(&X,*i);
			i++;
		}

		if( *i == ')')
		{
			n1 = in2pre_pop(&X);
			while( n1 != '(' )
			{
				*p = n1;
				p++;

				if(insertspace)
				{
					*p = ' ';
					p++;
				}

				n1 = in2pre_pop(&X);
			}
			i++;
		}

		if( isoperator(*i) )
		{
			if(isempty(&X))
				in2pre_push(&X,*i);
			else
			{
				n1 = in2pre_pop(&X);
				while(priority(n1) >= priority(*i))
				{
					*p = n1;
					p++;

					if(insertspace)
					{
						*p = ' ';
						p++;
					}

					n1 = in2pre_pop(&X);
				}
				in2pre_push(&X,n1);
				in2pre_push(&X,*i);
			}
			i++;
		}
	}
	while(!isempty(&X))
	{
		n1 = in2pre_pop(&X);
		*p = n1;
		p++;

		if(insertspace)
		{
			*p = ' ';
			p++;
		}

	}
	*p = '\0';   // empty buffer

	strrev(prefix);     // reverse the string again
}



void in2pre_push(struct stack* s,int item)
{
	if(s->top == (MAX-1))
	{
		printf("\nSTACK FULL");
	}
	else
	{
		++s->top;
		s->data[s->top]=item;
	}
}

char in2pre_pop(struct stack* s)
{
	char ret=(char)EMPTY;
	if(!isempty(s))
	{
		ret= s->data[s->top];
		--s->top;
	}
	return ret;
}

//-------------------------------------------------------------------------------------------------------------------

/* change infix to postfix */
// same like infix to postfix, but just remove the reverse parts

void infix_to_postfix(char* infix, char * postfix, int insertspace)
{

	struct stack X;
	emptystack(&X);

	char n1;
	char *i,*p;
	i = &infix[0];
	p = &postfix[0];


	while(*i)
	{
		while(*i == ' ' || *i == '\t')
		{
			i++;
		}

		if( isdigit(*i) || isalpha(*i) )
		{
			while( isdigit(*i) || isalpha(*i))
			{
				*p = *i;
				p++;
				i++;
			}

			if(insertspace)
			{
				*p = ' ';
				p++;
			}

		}

		if( *i == '(' )
		{
			in2post_push(&X,*i);
			i++;
		}

		if( *i == ')')
		{
			n1 = in2post_pop(&X);
			while( n1 != '(' )
			{
				*p = n1;
				p++;

				if(insertspace)
				{
					*p = ' ';
					p++;
				}

				n1 = in2post_pop(&X);
			}
			i++;
		}

		if( isoperator(*i) )
		{
			if(isempty(&X))
				in2post_push(&X,*i);
			else
			{
				n1 = in2post_pop(&X);
				while(priority(n1) >= priority(*i))
				{
					*p = n1;
					p++;

					if(insertspace)
					{
						*p = ' ';
						p++;
					}
					n1 = in2post_pop(&X);
				}
				in2post_push(&X,n1);
				in2post_push(&X,*i);
			}
			i++;
		}
	}
	while(!isempty(&X))
	{
		n1 = in2post_pop(&X);
		*p = n1;
		p++;

		if(insertspace)
		{
			*p = ' ';
			p++;
		}

	}
	*p = '\0';

}


int isempty(struct stack *s)
{
	return (s->top == EMPTY) ? 1 : 0;
}

void emptystack(struct stack* s)
{
	s->top=EMPTY;
}

void in2post_push(struct stack* s,int item)
{
	if(s->top == (MAX-1))
	{
		printf("\nSTACK FULL");
	}
	else
	{
		++s->top;
		s->data[s->top]=item;
	}
}

char in2post_pop(struct stack* s)
{
	char ret=(char)EMPTY;
	if(!isempty(s))
	{
		ret= s->data[s->top];
		--s->top;
	}
	return ret;
}


int isoperator(char e)
{
	if(e == '+' || e == '-' || e == '*' || e == '/' || e == '%' || e == '^')
		return 1;
	else
		return 0;
}


int priority(char e)
{
	int prio = 0;

	if(e == '^'){
        prio = 3;
	}
	else
        if(e == '*' || e == '/' || e =='%')
        {
		prio = 2;
        }
	else
        if(e == '+' || e == '-')
			{
			    prio = 1;
			}
	return prio;
}


//------------------------------------------------------------------------------------------------------------------

// prefix to infix

void push2(int *x)
{
    struct pre2in *temp1;

    temp1 = (struct pre2in*)malloc(sizeof(struct pre2in));
    strcpy(temp1->exp , x);
    temp1->next =top2;
    top2=temp1;
}

char *pop2()
{
    struct pre2in *temp1;
    char x[100];

        temp1=top2;
        strcpy(x,top2->exp);
        top2 = top2->next;
        free(temp1);

        return x;
}

 // prefix to infix

void prefix_to_infix (char exp[100])
{
    int i,j,k;
    int prefix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];

    strrev(exp);

    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)          //remove punctuation in array
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)
        {
            prefix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){    //change arrays from int to char

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(prefix[num_operand], temp, 10) ;
                strcpy(answer,temp);
                push2(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcpy (infix,")");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , "(");
                push2(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push2(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

        char infix_final[50];

        strcpy(infix_final, top2->exp);

        strrev(infix_final);

            printf("\nPrefix to infix is :  %s\n", infix_final);

        FILE * fpointer;

        fpointer = fopen("c:\\G51PGA\\output.txt", "w");

        fprintf(fpointer, "Prefix to infix: %s", infix_final);

        fclose(fpointer);
}


//-----------------------------------------------------------------------------------------------------------------

    // postfix to infix

    void push1(int *x)
{
    struct post2in *temp1;

    temp1 = (struct post2in*)malloc(sizeof(struct post2in));
    strcpy(temp1->exp , x);
    temp1->next =top1;
    top1=temp1;
}

char *pop1()
{
    struct post2in *temp1;
    char x[100];

        temp1=top1;
        strcpy(x,top1->exp);
        top1 = top1->next;
        free(temp1);

        return x;
}



void postfix_to_infix (char exp[100])
{
    int i,j,k;
    int postfix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];


    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)          //remove punctuation in array
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)
        {
            postfix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){         //change array from int to char

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(postfix[num_operand], temp, 10) ;
                strcpy(answer,temp);
                push1(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop1());
                strcpy (operand1,pop1());
                strcpy (infix,"(");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , ")");
                push1(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop1());
                strcpy (operand1,pop1());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push1(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

            strcpy(post_to_inBOX, top1->exp);


}


//-------------------------------------------------------------------------------------------------------------------
// convert postfix to infix, then from infix to prefix

 void post_to_pre(char exp[]){

      int i,j,k;
    int postfix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];


    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)          //remove punctuation in array
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)                      //tokenize the string
        {
            postfix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(postfix[num_operand], temp, 10) ;      //change int array to char array
                strcpy(answer,temp);
                push1(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop1());
                strcpy (operand1,pop1());
                strcpy (infix,"(");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , ")");
                push1(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop1());
                strcpy (operand1,pop1());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push1(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

        char infix_final[50];
        char pre[50] = { 0 };


        strcpy(infix_final, top1->exp);


    char temporary[50];
    k=0;

    for (i=0; infix_final[i]!= '\0'; i++)
    {
        if (infix_final[i] == '(' || infix_final[i] == ')')
        {
            for (j=0; j<strlen(infix_final); j++)
            {
                temporary[k] = ' ';
                k++;
            }
        }
        else
        {
            temporary[k]=infix_final[i];
            k++;
        }
    }


        infix_to_prefix(&temporary[0], &pre[0], 1 );

        strcpy(post_to_preBOX, &pre[0]);

        }

//------------------------------------------------------------------------------------------------------------------
// convert prefix to infix , then from infix to postfix

void pre_to_post(char exp[]) {

   int i,j,k;
    int prefix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];

    strrev(exp);

    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)          //remove punctuation in array
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)
        {
            prefix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(prefix[num_operand], temp, 10) ;
                strcpy(answer,temp);
                push2(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcpy (infix,")");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , "(");
                push2(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push2(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

        char infix_final[50];
        char post[50] = { 0 };

        strcpy(infix_final, top2->exp);

        strrev(infix_final);

        char temporary[50];
        k=0;

        for (i=0; infix_final[i]!= '\0'; i++)
        {
        if (infix_final[i] == '(' || infix_final[i] == ')')
        {
            for (j=0; j<strlen(infix_final); j++)
            {
                temporary[k] = ' ';
                k++;
            }
        }
        else
        {
            temporary[k]=infix_final[i];
            k++;
        }
    }

        infix_to_postfix(&infix_final[0], &post[0], 1);

        strcpy(pre_to_postBOX, &post[0]);


}

//------------------------------------------------------------------------------------------------------------------


// postfix evaluation

float EvaluatePostfix(char str[]){

    int i, data = -1,  result,  operand1, operand2;


    for (i = 0; i < strlen(str); i++) {
        if (isdigit(str[i])) {

            data = (data == -1) ? 0 : data;
            data = (data * 10) + (str[i] - 48);      // if input is digit, parse
            continue;
        }

        /* push the operator into the stack */
        if (data != -1) {
            evaluation_push(data);
        }

        if (str[i] == '+' || str[i] == '-'
            || str[i] == '*' || str[i] == '/') {      // if the  character is an operator,then pop two elements from the stack,
                                                      // put  operator and push the result into the stack

            operand2 = evaluation_pop();
            operand1 = evaluation_pop();
            if (operand1 == -1 || operand2 == -1)
                break;
            switch (str[i]) {
                case '+':
                    result = operand1 + operand2;
                                                       // push the result into the stack
                    evaluation_push(result);
                    break;
                case '-':
                    result = operand1 - operand2;
                    evaluation_push(result);
                    break;
                case '*':
                    result = operand1 * operand2;
                    evaluation_push(result);
                    break;
                case '/':
                    result = operand1 / operand2;
                    evaluation_push(result);
                    break;
            }
        }
        data = -1;
    }
    if (top != NULL && top->next == NULL) {
        printf("Evaluation result:%d\n", top->data);
          FILE * fpointer;

        fpointer = fopen("c:\\G51PGA\\output.txt", "w");

        fprintf(fpointer, "Evaluation result: %d\n", top->data);

        fclose(fpointer);
    }
    else {
        printf("Expression Error\n");   // give error if expression is wrong
    }
    return 0;
}

// change prefix expression into postfix, then evaluate
float EvaluatePrefix(char exp[]){

     int i,j,k;
    int prefix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];

    strrev(exp);

    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)
        {
            prefix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(prefix[num_operand], temp, 10) ;      //change int array to char array
                strcpy(answer,temp);
                push2(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcpy (infix,")");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , "(");
                push2(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push2(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

        char infix_final[50];
        char post[50] = { 0 };

        strcpy(infix_final, top2->exp);

        strrev(infix_final);

        char temporary[50];
        k=0;

        for (i=0; infix_final[i]!= '\0'; i++)
        {
        if (infix_final[i] == '(' || infix_final[i] == ')')
        {
            for (j=0; j<strlen(infix_final); j++)
            {
                temporary[k] = ' ';
                k++;
            }
        }
        else
        {
            temporary[k]=infix_final[i];
            k++;
        }
    }

        infix_to_postfix(&infix_final[0], &post[0], 1);

        EvaluatePostfix(&post[0]);

}

// change infix expression into postfix, then evaluate
float EvaluateInfix(char exp[]){

char post[50] = { 0 };

infix_to_postfix(&exp[0], &post[0], 1);

EvaluatePostfix(&post[0]);

}


/* push the input data into the stack */
void evaluation_push (int data) {
    struct node *ptr = createNode(data);
    if (top == NULL) {
        top = ptr;
        return;
    }
    ptr->next = top;
    top = ptr;
}

/* pop the top element from the stack */
int evaluation_pop () {
    int data;
    struct node *temp;
    if (top == NULL)
        return -1;
    data = top->data;
    temp = top;
    top =  top->next;
    free(temp);
    return (data);
}


/* ***************************************************************************************** */
/* FILE SECTION */
// call these functions if the user read from file
// totally the same with functions above, but all the outputs will be appended to the same file which is 'default.txt'

void FILE_prefix_to_infix (char exp[100])
{
    int i,j,k;
    int prefix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];

    strrev(exp);

    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)          //remove punctuation in array
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)
        {
            prefix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(prefix[num_operand], temp, 10) ;
                strcpy(answer,temp);
                push2(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcpy (infix,")");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , "(");
                push2(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push2(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

        char infix_final[50];

        strcpy(infix_final, top2->exp);

        strrev(infix_final);

            printf("\nPrefix to infix is :  %s\n", infix_final);

            FILE * fpointer;

            fpointer = fopen("c:\\G51PGA\\default.txt", "a");

            fprintf(fpointer, "\nPrefix to infix: %s", infix_final);

            fclose(fpointer);
}
//-------------------------------------------------------------------------

void FILE_postfix_to_infix (char exp[100])
{
    int i,j,k;
    int postfix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];


    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)
        {
            postfix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(postfix[num_operand], temp, 10) ;      //change int array to char array
                strcpy(answer,temp);
                push1(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop1());
                strcpy (operand1,pop1());
                strcpy (infix,"(");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , ")");
                push1(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop1());
                strcpy (operand1,pop1());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push1(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

        strcpy(FILE_post_to_inBOX, top1->exp);

}
//------------------------------------------------------------------------

void FILE_post_to_pre(char exp[])
{


      int i,j,k;
    int postfix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];


    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)
        {
            postfix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(postfix[num_operand], temp, 10) ;      //change int array to char array
                strcpy(answer,temp);
                push1(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop1());
                strcpy (operand1,pop1());
                strcpy (infix,"(");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , ")");
                push1(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop1());
                strcpy (operand1,pop1());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push1(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

        char infix_final[50];
        char pre[50] = { 0 };


        strcpy(infix_final, top1->exp);


    char temporary[50];
    k=0;

    for (i=0; infix_final[i]!= '\0'; i++)
    {
        if (infix_final[i] == '(' || infix_final[i] == ')')
        {
            for (j=0; j<strlen(infix_final); j++)
            {
                temporary[k] = ' ';
                k++;
            }
        }
        else
        {
            temporary[k]=infix_final[i];
            k++;
        }
    }


        infix_to_prefix(&temporary[0], &pre[0], 1 );

       strcpy(FILE_post_to_preBOX, &pre[0]);

        }
//----------------------------------------------------------------------------

void FILE_pre_to_post(char exp[])
 {

   int i,j,k;
    int prefix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];

    strrev(exp);

    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)
        {
            prefix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(prefix[num_operand], temp, 10) ;      //change int array to char array
                strcpy(answer,temp);
                push2(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcpy (infix,")");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , "(");
                push2(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push2(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

        char infix_final[50];
        char post[50] = { 0 };

        strcpy(infix_final, top2->exp);

        strrev(infix_final);

        char temporary[50];
        k=0;

        for (i=0; infix_final[i]!= '\0'; i++)
        {
        if (infix_final[i] == '(' || infix_final[i] == ')')
        {
            for (j=0; j<strlen(infix_final); j++)
            {
                temporary[k] = ' ';
                k++;
            }
        }
        else
        {
            temporary[k]=infix_final[i];
            k++;
        }
    }

        infix_to_postfix(&infix_final[0], &post[0], 1);

        strcpy(FILE_pre_to_postBOX, &post[0]);

}

float FILE_EvaluatePostfix(char str[])
{

    int i, data = -1,  result,  operand1, operand2;



    for (i = 0; i < strlen(str); i++) {
        if (isdigit(str[i])) {

            data = (data == -1) ? 0 : data;
            data = (data * 10) + (str[i] - 48);
            continue;
        }


        if (data != -1) {
            evaluation_push(data);
        }

        if (str[i] == '+' || str[i] == '-'
            || str[i] == '*' || str[i] == '/') {

            operand2 = evaluation_pop();
            operand1 = evaluation_pop();
            if (operand1 == -1 || operand2 == -1)
                break;
            switch (str[i]) {
                case '+':
                    result = operand1 + operand2;

                    evaluation_push(result);
                    break;
                case '-':
                    result = operand1 - operand2;
                    evaluation_push(result);
                    break;
                case '*':
                    result = operand1 * operand2;
                    evaluation_push(result);
                    break;
                case '/':
                    result = operand1 / operand2;
                    evaluation_push(result);
                    break;
            }
        }
        data = -1;
    }
    if (top != NULL && top->next == NULL) {
        printf("Evaluation result:%d\n", top->data);

          FILE * fpointer;

        fpointer = fopen("c:\\G51PGA\\default.txt", "a");

        fprintf(fpointer, "\nEvaluation result: %d\n", top->data);

        fclose(fpointer);
    }
    else {
        printf("Expression Error\n");
    }
    return 0;
}

float FILE_EvaluatePrefix(char exp[])
{

     int i,j,k;
    int prefix[100]= {0};
    int num_operand;
    char temp [2] = {' ', '\0'};
    char answer[50];
    char exp1[100];
    char infix[100]={0};
    char *token;
    char operand1 [50]= {'\0'};
    char operand2 [50]= {'\0'};
    char optr [2];

    strrev(exp);

    strcpy(exp1,exp);

    for (i = 0, j = 0; i<strlen(exp); i++,j++)
    {
        if (ispunct(exp[i]) == 0)
            exp[j]=exp[i];
        else
            j=j-2;
    }
    exp[j]=0;

        i = 0;
        token = strtok(exp, " ");

        while ( token != NULL)
        {
            prefix[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");

        }

        num_operand=0;
        for (i=0; i< strlen(exp1) ; i++){

            if (isdigit(exp1[i])==1){
                if (isdigit(exp1[i+1])){
                    i++;
                }
                itoa(prefix[num_operand], temp, 10) ;      //change int array to char array
                strcpy(answer,temp);
                push2(answer);
                num_operand++;
            }

        else if ((exp1[i] == '+') || (exp1[i] == '-') )
            {

                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcpy (infix,")");
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                strcat (infix , "(");
                push2(infix);

            }

            else if ((exp1[i] == '*') || (exp1[i] == '/') || (exp1[i] == '^') )
            {
                strcpy (operand2,pop2());
                strcpy (operand1,pop2());
                strcat (infix,operand1);
                strcat(infix, " ");
                optr[0] = exp1[i];
                optr[1] = '\0';
                strcat (infix ,optr);
                strcat(infix, " ");
                strcat (infix ,operand2);
                push2(infix);
            }

            else if(exp1 [i] == ' '){
               continue;
            }

            for (k=0; infix[k] ; k++)
                {
                    infix[k] = '\0';
                }

        }

        char infix_final[50];
        char post[50] = { 0 };

        strcpy(infix_final, top2->exp);

        strrev(infix_final);

        char temporary[50];
        k=0;

        for (i=0; infix_final[i]!= '\0'; i++)
        {
        if (infix_final[i] == '(' || infix_final[i] == ')')
        {
            for (j=0; j<strlen(infix_final); j++)
            {
                temporary[k] = ' ';
                k++;
            }
        }
        else
        {
            temporary[k]=infix_final[i];
            k++;
        }
    }

        infix_to_postfix(&infix_final[0], &post[0], 1);

        FILE_EvaluatePostfix(&post[0]);

}

float FILE_EvaluateInfix(char exp[])
{

char post[50] = { 0 };

infix_to_postfix(&exp[0], &post[0], 1);

FILE_EvaluatePostfix(&post[0]);

}

char FILE_start_program(char expression[])
 {

    char choice;
    int i, flag = 0, data = 0;
    char str[100];

    strcpy(str, expression);

     for (i = 0; i < strlen(str); i++) {        // check if expression is balanced, if it's not balanced, end program

                if (str[i] == '(' || str[i] == '{'
                        || str[i] == '[') {
                                push(str[i]);
                                continue;
                }
                if (str[i] == ')' || str[i] == '}' || str[i] == ']') {

                        data = pop();
                        if ((str[i] == ')' && data != '(') || data == -1 ||
                                (str[i] == '}' && data != '{') ||
                                        (str[i] == ']' && data != '[')) {

                                flag = 1;
                                break;
                        }

                }
        }

        if (flag == 1 || head != NULL){
                printf("\nExpression is not balanced.\nPlease try again next time.\n\n");
                printf("END OF PROGRAM\n");
                return 0; }
        else {
                printf("\nExpression is balanced\n\n");
        }



    printf("Please choose an option:\n(A)Convert to infix, prefix, postfix\n(B)Evaluate\n(C)Exit\n\n");
    // user choose what to do next with the expression
    scanf(" %c", &choice);



    if (choice == 'C') {
        printf("Thank you for using this program.\n");
        return 0;
    }
    else
        if (choice == 'A') {

            printf("\n");                                                   // options triggered depends on choice
            FILE_check_prefix_post_infix(expression);

        }
        else
            if (choice == 'B')
            {

                // determine what type of expression entered then only evaluate

                if (expression[(strlen(expression)-1)] == '+' || expression[(strlen(expression)-1)] == '-' || expression[(strlen(expression)-1)] == '*' || expression[(strlen(expression)-1)] == '/' || expression[(strlen(expression)-1)] == '^')

                {

                    printf("\nYou have entered a postfix expression to evaluate.\n");
                    FILE_EvaluatePostfix(expression);                  // call postfix evaluation function

                } else
                    if (expression[0] == '+' || expression[0] == '-' || expression[0] == '*' || expression[0] == '/' || expression[0] == '^' )

                    {

                        printf("\nYou have entered a prefix expression to evaluate.\n");
                        FILE_EvaluatePrefix(expression);

                    } else

                    {
                        printf("\nYou have entered a infix expression to evaluate.\n");
                        FILE_EvaluateInfix(expression);
                    }

            }

    return 0;



}

char FILE_check_prefix_post_infix(char x[])
{


    char option;
    char post[50] = { 0 };
    char pre[50] = { 0 };
    char yolo[50];          // for prefix to postfix
    char solo[50];          // for postfix to prefix

        strcpy(yolo, x);
        strcpy(solo, x);




    if (x[0] == '+' || x[0] == '-' || x[0] == '*' || x[0] == '/' || x[0] == '^' )

    {


        printf("This is a prefix expression.\n");                                                                               // if first character is operator, then it's prefix
        printf("Do you want to convert it to \n(A) postfix \n(B) infix \n(C) both? \nSelect A, B or C option:\n\n");
        scanf(" %c", &option);

        switch (option) {

            case 'B':

                FILE_prefix_to_infix(x);
                break;

            case 'A':

                FILE_pre_to_post(x);
                printf("\nPrefix to postfix is: %s\n", FILE_pre_to_postBOX);

                FILE * fpointer;

                fpointer = fopen("c:\\G51PGA\\default.txt", "a");

                fprintf(fpointer, "\nPrefix to postfix: %s", FILE_pre_to_postBOX);

                fclose(fpointer);
                break;

            case 'C':

                FILE_prefix_to_infix(x);
                FILE_pre_to_post(yolo);

                printf("\nPrefix to postfix is: %s\n", FILE_pre_to_postBOX);
                fpointer = fopen("c:\\G51PGA\\default.txt", "a");

                fprintf(fpointer, "\nPrefix to postfix: %s", FILE_pre_to_postBOX);

                fclose(fpointer);

                break;

            }

        return 0;

    } else

        if (x[(strlen(x)-1)] == '+' || x[(strlen(x)-1)] == '-' || x[(strlen(x)-1)] == '*' || x[(strlen(x)-1)] == '/' || x[(strlen(x)-1)] == '^')

        {

            printf("This is a postfix expression.\n");                                                                            // if last character is operator, then it's postfix
            printf("Do you want to convert it to \n(A) infix \n(B) prefix \n(C) both? \nSelect A, B or C option:\n\n");
            scanf(" %c", &option);

            switch (option) {

                case 'A':
                    FILE_postfix_to_infix(x);
                     printf("\nPostfix to infix is :  %s\n", FILE_post_to_inBOX);

                    FILE * fpointer;

                    fpointer = fopen("c:\\G51PGA\\default.txt", "a");

                    fprintf(fpointer, "\nPostfix to infix: %s", FILE_post_to_inBOX);

                    fclose(fpointer);
                    break;

                case 'B':

                    FILE_post_to_pre(x);
                    printf("\nPostfix to prefix is: %s\n", FILE_post_to_preBOX);

                    fpointer = fopen("c:\\G51PGA\\default.txt", "a");

                    fprintf(fpointer, "\nPostfix to prefix: %s",  FILE_post_to_preBOX);

                    fclose(fpointer);
                    break;

                case 'C':

                    FILE_postfix_to_infix(x);
                    printf("\nPostfix to infix is :  %s\n", FILE_post_to_inBOX);

                    fpointer = fopen("c:\\G51PGA\\default.txt", "a");

                    fprintf(fpointer, "\nPostfix to infix: %s", FILE_post_to_inBOX);

                    fclose(fpointer);

                    FILE_post_to_pre(solo);

                    printf("\nPostfix to prefix is: %s\n", FILE_post_to_preBOX);
                    fpointer = fopen("c:\\G51PGA\\default.txt", "a");

                    fprintf(fpointer, "\nPostfix to prefix: %s", FILE_post_to_preBOX);

                    fclose(fpointer);


                    break;
                }
            return 0;

        } else



    printf("This is an infix expression.\n");                                                                            //   if not both, then it's infix
    printf("Do you want to convert it to \n(A) prefix \n(B) postfix \n(C) both? \nSelect A, B or C option:\n\n");
    scanf(" %c", &option);



    switch (option) {

            // options triggered according to user inputs


        case 'A':

            infix_to_prefix(&x[0], &pre[0], 1);
            printf("\nInfix to prefix is : %s\n",&pre[0]);              // call prefix function
            FILE * fpointer;

            fpointer = fopen("c:\\G51PGA\\default.txt", "a");

            fprintf(fpointer, "\nInfix to prefix: %s",&pre[0]);

            fclose(fpointer);

            break;

        case 'B':

            infix_to_postfix(&x[0], &post[0], 1);             // call postfix function
            printf("\nInfix to postfix is : %s\n",&post[0]);


            fpointer = fopen("c:\\G51PGA\\default.txt", "a");

            fprintf(fpointer, "\nInfix to postfix: %s",&post[0]);

            fclose(fpointer);

            break;

        case 'C':

            infix_to_prefix(&x[0], &pre[0], 1);
            printf("\nInfix to prefix is : %s\n",&pre[0]);


            fpointer = fopen("c:\\G51PGA\\default.txt", "a");

            fprintf(fpointer, "\nInfix to prefix: %s",&pre[0]);

            fclose(fpointer);

            infix_to_postfix(&x[0], &post[0], 1);
            printf("\nInfix to postfix is : %s\n",&post[0]);


            fpointer = fopen("c:\\G51PGA\\default.txt", "a");

            fprintf(fpointer, "\nInfix to postfix: %s",&post[0]);

            fclose(fpointer);

            break;

    }


    return 0;

}

