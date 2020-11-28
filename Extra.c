//Library
#include <stdio.h>
#include<math.h>
#include<string.h>
//Variable global
//a,b, c, d tells me what term of that they take for example a= A or A' or 00.
int a, b, c, d, tryInvert;
char opt1[4], opt2[4], opt3[4], opt4[4];
//Prototipo de funciones
void KMap3Variables(int k, int opt, int pos1[k], int pos[opt], int term);
void KMap4Variables(int k, int opt, int pos[opt], int term);
void Options(int term);
//Body
int main(){
	int input=0, output=0, opt=0, i=0, j=0, k=0, term=0, hoho=0;
	char b[3][5];
	printf("How many inputs are there?\n");
	scanf("%d", &input);	
	opt=pow(2,input);
	int pos[opt];
	//Define value for outputs
	for(i=0;i<opt;i++){
		printf("For the first output (O_%d), write the value for position %d: ",i,i);
		scanf("%d", &pos[i]);
		while(pos[i]!=0 && pos[i]!=1){
			printf("For the first output (O_%d), write the value for position %d: ",i,i);
			scanf("%d", &pos[i]);
		}
		if(pos[i]==1){
			//Find how mant 1s are 
			k++;
		}
	}
	printf("Write 0 if you want the POS, or write 1 if you want the SOP\n"); 
	scanf("%d", &term);
	int pos1[k];
	k=0;
	for(i=0;i<opt;i++){
		if(pos[i]==1){
			//Find where 1s 
			pos1[k]=i;
			k++;
		}
	}
	if(input==3){
		KMap3Variables(k, opt, pos1, pos, term);
	}
	if(input==4){
		KMap4Variables(k, opt, pos, term);
	}
}

void KMap3Variables(int k, int opt, int pos1[k], int pos[opt], int term){
	//K map is literally the diagram of the K map, active is like a flag (tells me which minterms are available)
	int Kmap[5][2], i=0, j=0, l=0, active[5][2], g=0, cmp=0;
	char group[4][10];
	for(i=0; i<4; i++){
		//initializes all to 0 
		strcpy(group[i], "00\0");
	}
	//Saves values for the last row, which is the same as the first one (it is "cycle")
	Kmap[4][0]=pos[l];
	Kmap[4][1]=pos[l+1];
	active[4][0]=pos[l];
	active[4][1]=pos[l+1];
	//Saves values for the first 2 rows
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			Kmap[i][j]=pos[l];
			active[i][j]=pos[l];
			l++;
		}
	}
	//Saves values for the last 2 rows
	for(i=3;i>1;i--){
		for(j=0;j<2;j++){
			Kmap[i][j]=pos[l];
			active[i][j]=pos[l];
			l++;
		}
	}
	//Eliminates the option that all the minterms are 1s
	if(k==8){
		//constant 1
		strcpy(group[g], "1\0");
	}
	//Eliminates the option that all minterms are 0s
	else if (k==0){
		//constant 0
		strcpy(group[g], "0\0");
	}
	//Checks for groups
	else{
		//First groups of 4s
		for(i=0; i<4; i++){
			j=0;
			/*tells me if the group is 2X2:
				11
				11					*/
			if(Kmap[i][j]==Kmap[i][j+1] && Kmap[i+1][j]==Kmap[i+1][j+1] && Kmap[i][j]==Kmap[i+1][j] && Kmap[i][j]==term){
				active[i][j]=!term;
				active[i][j+1]=!term;
				active[i+1][j]=!term;
				active[i+1][j+1]=!term;
				a=((float)1.5*pow(i,2))-((float)2.5*i);
				b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
				Options(term);
				if(a==1 || a==0){
					strcpy(group[g], opt1);
				}
				else{
					strcpy(group[g], opt2);
				}
				g++;
				if(Kmap[0][0]==term || Kmap[4][0]==term){
					//As in the matrix "active", the first and last row are the same, both of them have to be changed.
					active[0][0]=!term;
					active[0][1]=!term;
					active[4][0]=!term;
					active[4][1]=!term;	
				}
			}
		}
		for(j=0; j<2; j++){
			//checks for a 4-vertical group.
			if(Kmap[0][j]==Kmap[1][j] && Kmap[0][j]==Kmap[2][j] && Kmap[0][j]==Kmap[3][j] && Kmap[0][j]==term){
				active[0][j]=!term;
				active[1][j]=!term;
				active[2][j]=!term;
				active[3][j]=!term;
				active[4][j]=!term;
				c=j;
				Options(term);
				strcpy(group[g], opt3);
				g++;
			}
		}
		//Now we need to see the pairs or the singles
		//determines pairs with the ungrouped
		for(i=0;i<4;i++){
			j=0;
			//Checks if the 2-group is horizontal: 11
			if(active[i][j]==term){
				if(active[i][j+1]==term){
					active[i][j]=!term;
					active[i][j+1]=!term;
					a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
					b=-((float)0.5*pow(i,2))+((float)1.5*i);
					Options(term);
					strcpy(group[g], opt1);
					strcat(group[g], opt2);
					g++;
					if(i==0 || i==3){
						active[0][0]=!term;
						active[0][1]=!term;
						active[4][0]=!term;
						active[4][1]=!term;	
					}
				}
				/*checks if the 2-groups is vertical
				 10
				 10	*/
				else if(active[i+1][j]==term){
					active[i][j]=!term;
					active[i+1][j]=!term;
					a=((float)1.5*pow(i,2))-((float)2.5*i);
					b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
					c=j;
					Options(term);
					if(a==1 || a==0){
						strcpy(group[g], opt1);
					}
					else{
						strcpy(group[g], opt2);
					}
					strcat(group[g], opt3);
					g++;
					if(i==0 || i==3){
						active[0][0]=!term;
						active[4][0]=!term;
					}
				}
			}
			/*Groups is vertical, but for the other column
			 01
			 01 */
			else if(active[i][j+1]==term){
				if(active[i+1][j+1]==term){
					active[i][j+1]=!term;
					active[i+1][j+1]=!term;
					a=((float)1.5*pow(i,2))-((float)2.5*i);
					b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
					c=j+1;
					Options(term);
					if(a==1 || a==0){
						strcpy(group[g], opt1);
					}
					else{
						strcpy(group[g], opt2);
					}
					strcat(group[g], opt3);
					g++;
					if(i==0 || i==3){
						active[0][1]=!term;
						active[4][1]=!term;	
					}
				}
			}
		}
		//Determines pairs with the grouped or the singles
		for(i=0;i<4;i++){
			j=0;
			//horizontal 2 group 1I
			if(active[i][j]==term){
				if(Kmap[i][j+1]==term){
					active[i][j]=!term;
					a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
					b=-((float)0.5*pow(i,2))+((float)1.5*i);
					Options(term);
					strcpy(group[g], opt1);
					strcat(group[g], opt2);
					g++;
					if(i==0 || i==3){
						active[0][0]=!term;
						active[4][0]=!term;
					}	
				}
				//vertical 2 group for first column (compares downwards)
				else if(Kmap[i+1][j]==term){
					active[i][j]=!term;	
					a=((float)1.5*pow(i,2))-((float)2.5*i);
					b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
					c=j;
					Options(term);
					if(a==1 || a==0){
						strcpy(group[g], opt1);
					}
					else{
						strcpy(group[g], opt2);
					}
					strcat(group[g], opt3);
					g++;
					if(i==0 || i==3){
						active[0][0]=!term;
						active[4][0]=!term;
					}
				}
				//vertical 2 group for first column (compares upwards)
				else if(Kmap[i-1][j]==term){
					active[i][j]=!term;	
					a=((float)1.5*pow((i-1),2))-((float)2.5*(i-1));
					b=((float)2.5*pow((i-1),2))-((float)10.5*(i-1))+9;
					c=j;
					Options(term);
					if(a==1 || a==0){
						strcpy(group[g], opt1);
					}
					else{
						strcpy(group[g], opt2);
					}
					strcat(group[g], opt3);
					g++;
					if(i==0 || i==3){
						active[0][0]=!term;
						active[4][0]=!term;
					}
				}
				else{
					//Its a one group (only checks in the first column)
					active[i][j]=!term;	
					a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
					b=-((float)0.5*pow(i,2))+((float)1.5*i);
					c=j;
					Options(term);
					strcpy(group[g], opt1);
					strcat(group[g], opt2);
					strcat(group[g], opt3);
					printf("a: %d, b: %d, c: %d, group: %s\n", a, b, c, group[g]);
					g++;	
				}
			}
			else if(active[i][j+1]==term){
				//Checks vertical 2-group for the second column (checks downwards)
				if(Kmap[i+1][j+1]==term){
					active[i][j+1]=!term;
					a=((float)1.5*pow(i,2))-((float)2.5*i);
					b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
					c=j+1;
					Options(term);
					if(a==1 || a==0){
						strcpy(group[g], opt1);
					}
					else{
						strcpy(group[g], opt2);
					}
					strcat(group[g], opt3);
					g++;
					if(i==0 || i==3){
						active[0][1]=!term;
						active[4][1]=!term;
					}	
				}
				//Checks vertical 2-group for the second column (checks upwards)
				else if(Kmap[i-1][j+1]==term){
					active[i][j+1]=!term;
					a=((float)1.5*pow((i-1),2))-((float)2.5*(i-1));
					b=((float)2.5*pow((i-1),2))-((float)10.5*(i-1))+9;
					c=j+1;
					Options(term);
					if(a==1 || a==0){
						strcpy(group[g], opt1);
					}
					else{
						strcpy(group[g], opt2);
					}
					strcat(group[g], opt3);
					g++;
					if(i==0 || i==3){
						active[0][1]=!term;
						active[4][1]=!term;
					}	
				}
				//Checks horizontally I1
				else if(Kmap[i][j]==term){
					active[i][j+1]=!term;
					a=((float)1.5*pow(i,2))-((float)2.5*i);
					b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
					Options(term);
					if(a==1 || a==0){
						strcpy(group[g], opt1);
					}
					else{
						strcpy(group[g], opt2);
					}
					g++;
						if(i==0 || i==3){
						active[0][1]=!term;
						active[4][1]=!term;
					}	
					if(i==0 || i==3){
						active[0][1]=!term;
						active[4][1]=!term;
					}	
				}
				else{
					//Its a one group (only checks in the second column)
					active[i][j+1]=!term;
					a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
					b=-((float)0.5*pow(i,2))+((float)1.5*i);
					c=j+1;
					Options(term);
					strcpy(group[g], opt1);
					strcat(group[g], opt2);
					strcat(group[g], opt3);
					printf("a: %d, b: %d, c: %d, group: %s\n", a, b, c, group[g]);
					g++;
					if(i==0 || i==3){
						active[0][1]=!term;
						active[4][1]=!term;
					}	
				}	
			}
		}
	}
	//To see if the values were saved correctly
	for(i=0;i<4;i++){
			j=0;
			printf("|%d|", Kmap[i][j]);
			printf("%d|\n", Kmap[i][j+1]);
	}
	//To see if the "flags" were marked correctly
	printf("_____\n");
	for(i=0;i<5;i++){
			j=0;
			printf("|%d|", active[i][j]);
			printf("%d|\n", active[i][j+1]);
	}
	///*
	for(i=0;i<4; i++){
		printf("Group %d: %s\n", i+1, group[i]);
	}//*/
	g=1;
	/*
	printf("F(ABC)=%s", group[g-1]);
	cmp=strcmp(group[g], "00\0");
	while(cmp==1){
		if(term==1){
			printf("+%s", group[g]);
			g++;
			cmp=strcmp(group[g], "00\0");
		}
		else{
			printf("(%s)", group[g]);
			g++;
			cmp=strcmp(group[g], "00\0");
		}
	}//*/
}

void KMap4Variables(int k, int opt, int pos[opt], int term){
	//K map is literally the diagram of the K map, active is like a flag (tells me which minterms are available)
	int Kmap[5][5], i=0, j=0, l=0, active[5][2], g=0;
	char group[4][2];
	for(i=0; i<4; i++){
		//initializes all to 0 
		strcpy(group[i], "00\0");
	}
	//Saves values for the last row, which is the same as the first one (it is "cycle")
	Kmap[4][0]=pos[l];
	Kmap[4][1]=pos[l+1];
	active[4][0]=pos[l];
	active[4][1]=pos[l+1];
	//Saves values for the first 2 rows
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			Kmap[i][j]=pos[l];
			active[i][j]=pos[l];
			l++;
		}
	}
	//Saves values for the last 2 rows
	for(i=3;i>1;i--){
		for(j=0;j<2;j++){
			Kmap[i][j]=pos[l];
			active[i][j]=pos[l];
			l++;
		}
	}
	//Eliminates the option that all the minterms are 1s
	if(k==16){
		//constant 1
		strcpy(group[g], "1");
	}
	//Eliminates the option that all minterms are 0s
	else if (k==0){
		//constant 0
		strcpy(group[g], "0");
	}
	//Checks for groups
	else{
		//First groups of 4s
		for(i=0; i<4; i++){
			j=0;
			/*tells me if the group is 2X2:
				11
				11					*/
			if(Kmap[i][j]==Kmap[i][j+1] && Kmap[i+1][j]==Kmap[i+1][j+1] && Kmap[i][j]==Kmap[i+1][j] && Kmap[i][j]==term){
				active[i][j]=!term;
				active[i][j+1]=!term;
				active[i+1][j]=!term;
				active[i+1][j+1]=!term;
				if(Kmap[0][0]==term || Kmap[4][0]==term){
					//As in the matrix "active", the first and last row are the same, both of them have to be changed.
					active[0][0]=!term;
					active[0][1]=!term;
					active[4][0]=!term;
					active[4][1]=!term;	
				}
			}
		}
		for(j=0; j<1; j++){
			//checks for a 4-vertical group.
			if(Kmap[0][j]==Kmap[1][j] && Kmap[0][j]==Kmap[2][j] && Kmap[0][j]==Kmap[3][j] && Kmap[0][j]==term){
				active[0][j]=!term;
				active[1][j]=!term;
				active[2][j]=!term;
				active[3][j]=!term;
				active[4][j]=!term;
			}
		}
		//Now we need to see the pairs or the singles
		//determines pairs with the ungrouped
		for(i=0;i<4;i++){
			j=0;
			//Checks if the 2-group is horizontal: 11
			if(active[i][j]==term){
				if(active[i][j+1]==term){
					active[i][j]=!term;
					active[i][j+1]=!term;
					if(i==0 || i==3){
						active[0][0]=!term;
						active[0][1]=!term;
						active[4][0]=!term;
						active[4][1]=!term;	
					}
				}
				/*checks if the 2-groups is vertical
				 10
				 10	*/
				else if(active[i+1][j]==term){
					active[i][j]=!term;
					active[i+1][j]=!term;
					if(i==0 || i==3){
						active[0][0]=!term;
						active[4][0]=!term;
					}
				}
			}
			/*Groups is vertical, but for the other column
			 01
			 01 */
			else if(active[i][j+1]==term){
				if(active[i+1][j+1]==term){
					active[i][j+1]=!term;
					active[i+1][j+1]=!term;
					if(i==0 || i==3){
						active[0][1]=!term;
						active[4][1]=!term;	
					}
				}
			}
		}
		//Determines pairs with the grouped or the singles
		for(i=0;i<4;i++){
			j=0;
			//horizontal 2 group 1I
			if(active[i][j]==term){
				if(Kmap[i][j+1]==term){
					active[i][j]=!term;
					if(i==0 || i==3){
						active[0][0]=!term;
						active[4][0]=!term;
					}	
				}
				//vertical 2 group for first column
				else if(Kmap[i+1][j]==term){
					active[i][j]=!term;	
					if(i==0 || i==3){
						active[0][0]=!term;
						active[4][0]=!term;
					}
				}
				
				else{
					//Its a one group (only checks in the first column)
					active[i][j]=!term;		
				}
			}
			else if(active[i][j+1]==term){
				//Checks vertical 2-group for the second column
				if(Kmap[i+1][j+1]==term){
					active[i][j+1]=!term;
				}
				else if(Kmap[i][j+1]==term){
					active[i][j+1]=!term;
						if(i==0 || i==3){
						active[0][1]=!term;
						active[4][1]=!term;
					}	
				}
				else{
					//Its a one group (only checks in the second column)
					active[i][j]=!term;
					strcat(group[g], opt1);
					strcat(group[g], opt2);
					strcat(group[g], opt3);
					printf("%s.....", group[g]);
					g++;
				}	
			}
		}
	}
	//To see if the values were saved correctly
	for(i=0;i<4;i++){
			j=0;
			printf("|%d|", Kmap[i][j]);
			printf("%d|\n", Kmap[i][j+1]);
	}
	//To see if the "flags" were marked correctly
	printf("_____\n");
	for(i=0;i<5;i++){
			j=0;
			printf("|%d|", active[i][j]);
			printf("%d|\n", active[i][j+1]);
	}
	
}
void Options(int term){
	char A[4]="A\0", B[4]="B\0", C[4]="C\0", D[4]="D\0", noA[4]="A'\0", noB[4]="B'\0", noC[4]="C'\0", noD[4]="D'\0";
	if(term==1){
		switch(a){
			case 0:  
				strcpy(opt1, noA);
				break;
			case 1: 
				strcpy(opt1, A);
				break;
			default: 
				strcpy(opt1, "00\0");
		}
		switch(b){
			case 0: 
				strcpy(opt2, noB);
				break;
			case 1: 
				strcpy(opt2, B);
				break;
			default: 
				strcpy(opt2, "00\0");	
		}
		switch(c){
			case 0: 
				strcpy(opt3, noC);
				break;
			case 1: 
				strcpy(opt3, C);
				break;		
			default: 
				strcpy(opt3, "00\0");
		}
		switch(d){
			case 0:  
				strcpy(opt4, noD);
				break;
			case 1: 
				strcpy(opt4, D);
				break;
			default: 
				strcpy(opt4, "00\0");
		}
	}
	else{
		strcpy(A,"A+\0");
		strcpy(B, "B+\0");
		strcpy(C, "C+\0");
		strcpy(D, "D+\0");
		strcpy(noA,"A'+\0");
		strcpy(noB, "B'+\0");
		strcpy(noC, "C'+\0");
		strcpy(noD, "D'+\0");
		switch(a){
			case 0:  
				strcpy(opt1, A);
				break;
			case 1: 
				strcpy(opt1, noA);
				break;
			default: 
				strcpy(opt1, "00\0");
		}
		switch(b){
			case 0: 
				strcpy(opt2, B);
				break;
			case 1: 
				strcpy(opt2, noB);
				break;
			default: 
				strcpy(opt2, "00\0");	
		}
		switch(c){
			case 0: 
				strcpy(opt3, C);
				break;
			case 1: 
				strcpy(opt3, noC);
				break;		
			default: 
				strcpy(opt3, "00\0");
		}
		switch(d){
			case 0:  
				strcpy(opt4, D);
				break;
			case 1: 
				strcpy(opt4, noD);
				break;
			default: 
				strcpy(opt4, "00\0");
		}	
	}
}
/*void POS(){
	switch(tryInvert){
		
	}
}*/
