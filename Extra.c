//Library
#include <stdio.h>
#include<math.h>
#include<string.h>
//Variable global
//a,b, c, d tells me what term of that they take for example a= A or A' or 00.
int a, b, c, d;
char opt1[2], opt2[2], opt3[2], opt4[2];
//Prototipo de funciones
void KMap3Variables(int k, int opt, int pos1[k], int pos[opt], int term);
void KMap4Variables(int k, int opt, int pos[opt], int term);
void Options();
//Body
int main(){
	int input=0, output=0, opt=0, i=0, j=0, k=0, term=0, ho=0;
	char b[3][5];
	ho=0;
	printf("%d", ho);
	printf("How many inputs are there?\n");
	scanf("%d", &input);	
	opt=pow(2,input);
	int pos[opt];
	//Define value for outputs
	for(i=0;i<opt;i++){
		printf("For the first output (O_%d), write the value for position %d: ",i,i);
		scanf("%d", &pos[i]);
		if(pos[i]==1){
			//Find where 1s are 
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
	int Kmap[5][2], i=0, j=0, l=0, active[5][2], g=0;
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
	if(k==8){
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
				a=((float)1.5*pow(i,2))-((float)2.5*i);
				b=0;
				Options();
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
				Options();
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
					Options();
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
					a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
					b=-((float)0.5*pow(i,2))+((float)1.5*i);
					c=j;
					Options();
					strcpy(group[g], opt1);
					strcat(group[g], opt2);
					strcat(group[g], opt3):
					g++;	
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
					a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
					b=-((float)0.5*pow(i,2))+((float)1.5*i);
					c=j+1;
					Options();
					strcpy(group[g], opt1);
					strcat(group[g], opt2);
					strcat(group[g], opt3):
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
void Options(){
	char A[2]="A", B[2]="B", C[2]="C", D[2]="D", noA[3]="A'\0", noB[2]="B'", noC[2]="C'", noD[2]="D'";
	switch(a){
		case 0:  
			strcpy(opt1, noA);
			break;
		case 1: 
			strcpy(opt1, A);
			break;
		default: 
			strcpy(opt1, "00");
	}
	switch(b){
		case 0: 
			strcpy(opt2, noB);
			break;
		case 1: 
			strcpy(opt2, B);
			break;
		default: 
			strcpy(opt2, "00");	
	}
	switch(c){
		case 0: 
			strcpy(opt3, noC);
			break;
		case 1: 
			strcpy(opt3, C);
			break;		
		default: 
			strcpy(opt3, "00");
	}
	switch(d){
		case 0:  
			strcpy(opt4, noD);
			break;
		case 1: 
			strcpy(opt4, D);
			break;
		default: 
			strcpy(opt4, "00");
	}
}
