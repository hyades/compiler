
void insert(funTable FT[],char *fname, symbol type, char *name,int ion , int offset)
{
	int hval,hval2,hkey=100;

	hval = hash(fname,hkey);
	strcpy(FT[hval].fname,fname);
	hval2 = hash(name,hkey);
	strcpy(FT[hval].table[hval2].name,name);
	FT[hval].table[hval2].type = type;
	FT[hval].table[hval2].ion = ion;
	FT[hval].table[hval2].offset = offset;
	FT[hval].table[hval2].filled = 1;
}

//RT,temp2->next[1]->t->lexeme,temp3->next[1]->t->s,temp3->next[2]->t->lexeme

void insert(recTable RT[],char *rname, symbol type, char *name)
{
	int hval,hval2,hkey=100;

	hval = hash(rname,hkey);
	strcpy(RT[hval].rname,rname);
	hval2 = hash(name,hkey);
	strcpy(RT[hval].table[hval2].name,name);
	RT[hval].table[hval2].type = type;
	RT[hval].table[hval2].filled = 1;
}


//insert(GT,temp2->next[1]->t->s,temp2->next[2]->t->lexeme)

void insert(variable GT[],symbol type, char *name)
{
	int hval,hkey=100;

	hval = hash(name,hkey);
	strcpy(GT[hval].name,name);
	GT[hval].type = type;
	GT[hval].filled = 1;	
}



void createSymbolTable( GT[], FT[], RT[], A)
{
	int i,j,k,l,m,n,offset=1;
	parseTree temp,temp1;
	for(i=0;A->next[i]!=NULL;i++)
	{
		if(A->next[i]->t->s==function)
		{
			temp = A->next[i];	
			if(temp->next[1]->t->s==parameter_list)
			{
				temp1 = temp->next[1];
				offset = 0;
				for(j=0;temp1->next[j]!=NULL;j+=2)
				{
					//check
					insert(FT,temp->next[0]->t->lexeme,temp1->next[j]->t->s,temp1->next[j+1]->t->lexeme,0,offset) ;
					// ft _functionname int d3b4b5 input==0 offset
				}				
			}
			if(temp->next[2]->t->s==parameter_list)
			{
				temp1 = temp->next[2];
				offset = 0;
				for(j=0;temp1->next[j]!=NULL;j+=2)
				{
					//check
					insert(FT,temp->next[0]->t->lexeme,temp1->next[j]->t->s,temp1->next[j+1]->t->lexeme,1,offset) ;
					// ft _functionname int d3b4b5 outputs==1 offset
				}				
			}
			else if(temp->next[2]->t->s==stmts)
			{
				temp1 = temp->next[2];
				offset=1;
				for(j=0;temp1->next[j]!=NULL;j++)
				{

					temp2 = temp1->next[j];
					if(temp2->t->s == typedefinition)
					{
						//rec
						//check
						//if(!check(RT,temp2->next[1]->t->lexeme))
							for(k=2;temp2->next[k]->t->s != TK_ENDRECORD;k++)
							{
								temp3 = temp2->next[k]; //field-defination
								insert(RT,temp2->next[1]->t->lexeme,temp3->next[1]->t->s,temp3->next[2]->t->lexeme);
							}
						/*
						else
						{
							printf("MULTIPLE DECLARATIONS OF RECORD %s\n",temp2->next[1]->t->lexeme);
							return;
						}
						*/

					}
					else if(temp2->t->s == declaration)
					{
						//ft
						if(temp2->next[3]!=NULL)
						{
							//global
							//check
							insert(GT,temp2->next[1]->t->s,temp2->next[2]->t->lexeme)
						}
						else
						{
							//check
							insert(FT,temp->next[0]->t->lexeme,temp2->next[1]->t->s,temp2->next[2]->t->lexeme,2,offset) ;
							offset++;	
						}
						
						// ft _functionname int d3b4b5 normal == 2 offset
					}
					else
						break;
				}
								
			}
			if(temp->next[3]->t->s==stmts)
			{
				temp1 = temp->next[3];
				for(j=0;temp1->next[j]!=NULL;j++)
				{
					temp2 = temp1->next[j];
					if(temp2->t->s == typedefinition)
					{
						//rec
					}
					else if(temp2->t->s == declaration)
					{
						//ft
						offset = 1;
						for(k=0;temp2->next[k]!=NULL;k+=2)
						{
							insert(FT,temp->next[0]->t->lexeme,temp2->next[k]->t->s,tempc2->next[k+1]->t->lexeme,2,offset) ;
							offset++;
							// ft _functionname int d3b4b5 normal == 2 offset
						}	
					}
					else
						break;
				}
								
			}
		}
		else
		{

		}
	}
}




