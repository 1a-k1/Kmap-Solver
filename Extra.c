//Library
#include <stdio.h>
#include<math.h>
#include<string.h>
//Variable global
//a,b, c, d tells me what term of that they take for example a= A or A' or 00.
int a, b, c, d, tryInvert;
char opt1[4], opt2[4], opt3[4], opt4[4];
//Prototipo de funciones
void KMap3Variables(int k, int opt, int pos[opt], int term);
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
	if(input==3){
		KMap3Variables(k, opt, pos, term);
	}
	else if(input==4){
		KMap4Variables(k, opt, pos, term);
	}
}

void KMap3Variables(int k, int opt, int pos[opt], int term){
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
					if(term==0){
						strcat(group[g], "+");
					}
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
					if(term==0){
						strcat(group[g], "+");
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
					if(term==0){
						strcat(group[g], "+");
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
					if(term==0){
						strcat(group[g], "+");
					}
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
					if(term==0){
						strcat(group[g], "+");
					}
					strcat(group[g], opt3);
					g++;
					if(i==0 || i==3){
						active[0][0]=!term;
						active[4][0]=!term;
					}
				}
				//vertical 2 group for first column (compares upwards)
				else if(Kmap[i-1][j]==term && i!=0){
					printf("%d", Kmap[i-1][j]);
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
					if(term==0){
						strcat(group[g], "+");
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
					if(term==0){
						strcat(group[g], "+");
					}
					strcat(group[g], opt2);
					if(term==0){
						strcat(group[g], "+");
					}
					strcat(group[g], opt3);
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
					if(term==0){
						strcat(group[g], "+");
					}
					strcat(group[g], opt3);
					g++;
					if(i==0 || i==3){
						active[0][1]=!term;
						active[4][1]=!term;
					}	
				}
				//Checks vertical 2-group for the second column (checks upwards)
				else if(Kmap[i-1][j+1]==term && i!=0){
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
					if(term==0){
						strcat(group[g], "+");
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
					a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
					b=-((float)0.5*pow(i,2))+((float)1.5*i);
					Options(term);
					strcpy(group[g], opt1);
					if(term==0){
						strcat(group[g], "+");
					}
					strcat(group[g], opt2);
					g++;	
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
					if(term==0){
						strcat(group[g], "+");
					}
					strcat(group[g], opt2);
					if(term==0){
						strcat(group[g], "+");
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
	/*
	for(i=0;i<4; i++){
		printf("Group %d: %s\n", i+1, group[i]);
	}//*/
	g=1;
	///*
	printf("F(ABC)=(%s)", group[g-1]);
	cmp=strcmp(group[g], "00\0");
	while(cmp==1 && g!=4){
		if(term==1){
			printf("+(%s)", group[g]);
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
//same as in Kmap3. horizontal8 is so that if there is an 8group it doesn't look for the 4 group horizontal, same goes for vertical
int Kmap[5][5], i=0, j=0, l=0, active[5][5], g=0, cmp=0, horizontal8=0, vertical8=0;
	char group[8][15];
	for(i=0; i<8; i++){
		//initializes all to 0 
		strcpy(group[i], "00\0");
	}
	for(i=0;i<2;i++){
		//Saves values for the first 2 rows
		//saves values for the first 2 columns
		for(j=0;j<2;j++){
			Kmap[i][j]=pos[j+(4*i)];
			active[i][j]=pos[j+(4*i)];
		}
		//Saves values for the second 2 columns
		l=1;
		for(j=2; j<4; j++){
			Kmap[i][j]=pos[j+l+(4*i)];
			active[i][j]=pos[j+l+(4*i)];
			l=l-2;
		}
	//Saves values for the last 2 rows
		//saves values for the first 2 columns
		for(j=0;j<2;j++){
			Kmap[i+2][j]=pos[j-(4*i)+12];
			active[i+2][j]=pos[j-(4*i)+12];
		}
		for(j=0; j<2; j++){
			//Saves values for the second 2 rows
			Kmap[i+2][j+2]=pos[15-j-(4*i)];
			active[i+2][j+2]=pos[15-j-(4*i)];
		}
	}
	//Saves values for the last row and column, which is the same as the first one (it is "cycle")
	for(i=0;i<5;i++){
		Kmap[4][i]=Kmap[0][i];
		active[4][i]=active[0][i];
		Kmap[i][4]=Kmap[i][0];
		active[i][4]=active[i][0];
	}
	
	//Eliminates the option that all the minterms are 1s
	if(k==16){
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
		//First checcks horizontally and vertically for groups of 8s and 4s
		for(i=0; i<3; i++){
			j=0;   
			//Check horizontally for 4 ----
			if(Kmap[i][j]==Kmap[i][j+1] && Kmap[i][j+2]==Kmap[i][j+3] && Kmap[i][j]==Kmap[i][j+3] && Kmap[i][j]==term){
				//Checks if it is an 8 group
				if(Kmap[i+1][j]==Kmap[i+1][j+1] && Kmap[i+1][j+2]==Kmap[i+1][j+3] && Kmap[i+1][j]==Kmap[i+1][j+3] && Kmap[i+1][j]==term){
					horizontal8=1;
					a=((float)1.5*pow(i,2))-((float)2.5*i);
					b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
					Options(term);
					if(a==1 || a==0){
						strcpy(group[g], opt1);
					}
					else{
						strcpy(group[g], opt2);
					}
					printf("Found a 8 group (horizontal): %s\n", group[g]);
					g++;
					active[i+1][j]=!term;	
					active[i+1][j+1]=!term;
					active[i+1][j+2]=!term;
					active[i+1][j+3]=!term;
					active[i+1][j+4]=!term;
				}
				//checks if the 8 group is with the borders
				else if(i==0 && Kmap[3][j]==Kmap[3][j+1] && Kmap[3][j+2]==Kmap[3][j+3] && Kmap[3][j]==Kmap[3][j+3] && Kmap[3][j]==term){
					horizontal8=2;
					a=((float)1.5*pow(3,2))-((float)2.5*3);
					b=((float)2.5*pow(3,2))-((float)10.5*3)+9;
					Options(term);
					if(a==1 || a==0){
						strcpy(group[g], opt1);
					}
					else{
						strcpy(group[g], opt2);
					}
					printf("Found a 4 group (the borders): %s\n", group[g]);
					g++;
					active[3][j]=!term;	
					active[3][j+1]=!term;
					active[3][j+2]=!term;
					active[3][j+3]=!term;
					active[3][j+4]=!term;
				}				
				//If it is not an 8 group, it is a 4 group (horizontal)
				else if(horizontal8==0){
					a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);	
					b=-((float)0.5*pow(i,2))+((float)1.5*i);
					Options(term);
					strcpy(group[g], opt1);
					if(term==0){
						strcat(group[g], "+");
					}
					strcat(group[g], opt2);
					printf("Found a 4 group (horizontal): %s\n", group[g]);
					g++;
				}
				active[i][j]=!term;	
				active[i][j+1]=!term;
				active[i][j+2]=!term;
				active[i][j+3]=!term;
				active[i][j+4]=!term;
				if(i==0 || horizontal8==2){
					active[0][j]=!term;	
					active[0][j+1]=!term;
					active[0][j+2]=!term;
					active[0][j+3]=!term;
					active[0][j+4]=!term;
					active[4][j]=!term;	
					active[4][j+1]=!term;
					active[4][j+2]=!term;
					active[4][j+3]=!term;
					active[4][j+4]=!term;
				}
			}
			//Checks vertically for 4 terms
			else if(Kmap[j][i]==Kmap[j+1][i] && Kmap[j+2][i]==Kmap[j+3][i] && Kmap[j][i]==Kmap[j+3][i] && Kmap[j][i]==term){
				//Checks if its an 8 vertical group
				if(Kmap[j][i+1]==Kmap[j+1][i+1] && Kmap[j+2][i+1]==Kmap[j+3][i+1] && Kmap[j][i+1]==Kmap[j+3][i+1] && Kmap[j][i+1]==term){
					vertical8=1;
					c=((float)1.5*pow(i,2))-((float)2.5*i);
					d=((float)2.5*pow(i,2))-((float)10.5*i)+9;
					Options(term);
					if(c==1 || c==0){
						strcpy(group[g], opt2);
					}
					else{
						strcpy(group[g], opt3);	
					}
					printf("Found an 8 group (vertical) %s\n", group[g]);
					g++;
					active[j][i+1]=!term;	
					active[j+1][i+1]=!term;
					active[j+2][i+1]=!term;
					active[j+3][i+1]=!term;
					active[j+4][i+1]=!term;
				}
				//checks borders
				else if(i==0 && Kmap[j][3]==Kmap[j+1][3] && Kmap[j+2][3]==Kmap[j+3][3] && Kmap[j][3]==Kmap[j+3][3] && Kmap[j][3]==term){
					vertical8=2;
					c=((float)1.5*pow(3,2))-((float)2.5*3);
					d=((float)2.5*pow(3,2))-((float)10.5*3)+9;
					Options(term);
					if(c==1 || c==0){
						strcpy(group[g], opt2);
					}
					else{
						strcpy(group[g], opt3);	
					}
					printf("Found a 8 group (the borders): %s\n", group[g]);
					g++;
					active[j][3]=!term;	
					active[j+1][3]=!term;
					active[j+2][3]=!term;
					active[j+3][3]=!term;
					active[j+4][3]=!term;
				}
				//If not, it is a 4 group
				else if(vertical8==0){
					c=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);	
					d=-((float)0.5*pow(i,2))+((float)1.5*i);
					Options(term);
					strcpy(group[g], opt3);
					if(term==0){
						strcat(group[g], "+");
					}
					strcat(group[g], opt4);
					printf("Found a 4 group (vertical): %s\n", group[g]);
					g++;
				}
				active[j][i]=!term;	
				active[j+1][i]=!term;
				active[j+2][i]=!term;
				active[j+3][i]=!term;
				active[j+4][i]=!term;
				if(i==0 || vertical8==2){
					active[0][0]=!term;	
					active[1][0]=!term;
					active[2][0]=!term;
					active[3][0]=!term;
					active[4][0]=!term;
					active[0][4]=!term;	
					active[1][4]=!term;
					active[2][4]=!term;
					active[3][4]=!term;
					active[4][4]=!term;
				}
			}
		}
		//Then, a 2X2 group will be found
		for(i=0; i<4; i++){
			/*tells me if the group is 2X2:
				11
				11					*/
			for(j=0; j<4; j++){
				if(active[i][j]==term){
					//Check right downwards
					if(Kmap[i][j]==Kmap[i][j+1] && Kmap[i+1][j]==Kmap[i+1][j+1] && Kmap[i][j]==Kmap[i+1][j] && Kmap[i][j]==term){
						//Groups with ungrouped or groupes
						if(active[i][j]==term || active[i+1][j+1]==term || active[i+1][j]==term || active[i][j+1]==term){
							a=((float)1.5*pow(i,2))-((float)2.5*i);
							b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
							c=((float)1.5*pow(j,2))-((float)2.5*j);
							d=((float)2.5*pow(j,2))-((float)10.5*j)+9;
							Options(term);
							if(a==1 || a==0){
								strcpy(group[g], opt1);
							}
							else{
								strcpy(group[g], opt2);
							}
							if(term==0){
								strcat(group[g], "+");
							}
							if(c==1 || c==0){
								strcat(group[g], opt3);
							}			
							else{
								strcat(group[g], opt4);
							}
							printf("Found a 2X2 group: %s\n", group[g]);	
							g++;
							active[i][j]=!term;
							active[i][j+1]=!term;
							active[i+1][j]=!term;
							active[i+1][j+1]=!term;
							if(i==0 || i==3){
								//As in the matrix "active", the first and last row are the same, both of them have to be changed.
								active[0][j]=!term;
								active[0][j+1]=!term;
								active[4][j]=!term;
								active[4][j+1]=!term;	
								if(j==0 || j==3){
									active[i][0]=!term;
									active[i+1][0]=!term;
									active[i][4]=!term;
									active[i+1][4]=!term;		
								}
								if(j==3 && i==3){
									active[0][0]=!term;
								}
							}
							else if(j==0 || j==3){
								active[i][0]=!term;
								active[i+1][0]=!term;
								active[i][4]=!term;
								active[i+1][4]=!term;	
								if(i==0 || i==3){
									active[0][0]=!term;
									active[0][4]=!term;
									active[4][0]=!term;
									active[4][4]=!term;
								}
							}
						}
					}	
					//Checks right upwards
					else if((Kmap[i][j]==Kmap[i][j+1] && Kmap[i-1][j]==Kmap[i-1][j+1] && Kmap[i][j]==Kmap[i-1][j] && Kmap[i][j]==term) && (i!=0)){
						//Groups with ungrouped or groupes
						if(active[i][j]==term || active[i+1][j+1]==term || active[i+1][j]==term || active[i][j+1]==term){
							a=((float)1.5*pow((i-1),2))-((float)2.5*(i-1));
							b=((float)2.5*pow((i-1),2))-((float)10.5*(i-1))+9;
							c=((float)1.5*pow(j,2))-((float)2.5*j);
							d=((float)2.5*pow(j,2))-((float)10.5*j)+9;
							Options(term);
							if(a==1 || a==0){
								strcpy(group[g], opt1);
							}
							else{
								strcpy(group[g], opt2);
							}
							if(term==0){
								strcat(group[g], "+");
							}
							if(c==1 || c==0){
								strcat(group[g], opt3);
							}			
							else{
								strcat(group[g], opt4);
							}
							printf("Found a 2X2 group: %s\n", group[g]);	
							g++;
							active[i][j]=!term;
							active[i][j+1]=!term;
							active[i-1][j]=!term;
							active[i-1][j+1]=!term;
							if(i==0 || i==3){
								//As in the matrix "active", the first and last row are the same, both of them have to be changed.
								active[0][j]=!term;
								active[0][j+1]=!term;
								active[4][j]=!term;
								active[4][j+1]=!term;	
								if(j==0 || j==3){
									active[i][0]=!term;
									active[i-1][0]=!term;
									active[i][4]=!term;
									active[i-1][4]=!term;		
								}
								if(j==3 && i==3){
									active[0][0]=!term;
								}
							}
							else if(j==0 || j==3){
								active[i][0]=!term;
								active[i-1][0]=!term;
								active[i][4]=!term;
								active[i-1][4]=!term;	
								if(i==0 || i==3){
									active[0][0]=!term;
									active[0][4]=!term;
									active[4][0]=!term;
									active[4][4]=!term;
								}
							}
						}
					}
					//Checks left downwards				
					else if((Kmap[i][j]==Kmap[i][j-1] && Kmap[i+1][j]==Kmap[i+1][j-1] && Kmap[i][j]==Kmap[i+1][j-1] && Kmap[i][j]==term) && (j!=0)){
						//Groups with ungrouped or groupes
						if(active[i][j]==term || active[i+1][j+1]==term || active[i+1][j]==term || active[i][j+1]==term){
							a=((float)1.5*pow(i,2))-((float)2.5*i);
							b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
							c=((float)1.5*pow((j-1),2))-((float)2.5*(j-1));
							d=((float)2.5*pow((j-1),2))-((float)10.5*(j-1))+9;
							Options(term);
							if(a==1 || a==0){
								strcpy(group[g], opt1);
							}
							else{
								strcpy(group[g], opt2);
							}
							if(term==0){
								strcat(group[g], "+");
							}
							if(c==1 || c==0){
								strcat(group[g], opt3);
							}			
							else{
								strcat(group[g], opt4);
							}
							printf("Found a 2X2 group: %s\n", group[g]);	
							g++;
							active[i][j]=!term;
							active[i][j-1]=!term;
							active[i+1][j]=!term;
							active[i+1][j-1]=!term;
							if(i==0 || i==3){
								//As in the matrix "active", the first and last row are the same, both of them have to be changed.
								active[0][j]=!term;
								active[0][j-1]=!term;
								active[4][j]=!term;
								active[4][j-1]=!term;	
								if(j==0 || j==3){
									active[i][0]=!term;
									active[i+1][0]=!term;
									active[i][4]=!term;
									active[i+1][4]=!term;		
								}
								if(j==3 && i==3){
									active[0][0]=!term;
								}
							}
							else if(j==0 || j==3){
								active[i][0]=!term;
								active[i+1][0]=!term;
								active[i][4]=!term;
								active[i+1][4]=!term;	
								if(i==0 || i==3){
									active[0][0]=!term;
									active[0][4]=!term;
									active[4][0]=!term;
									active[4][4]=!term;
								}
							}
						}
					}
					//Checks left upwards
					else if(Kmap[i][j]==Kmap[i][j-1] && Kmap[i-1][j]==Kmap[i-1][j-1] && Kmap[i][j]==Kmap[i-1][j] && Kmap[i][j]==term && j!=0 && i!=0){
						
						//Groups with ungrouped or groupes
						if(active[i][j]==term || active[i+1][j+1]==term || active[i+1][j]==term || active[i][j+1]==term){
							a=((float)1.5*pow((i-1),2))-((float)2.5*(i-1));
							b=((float)2.5*pow((i-1),2))-((float)10.5*(i-1))+9;
							c=((float)1.5*pow((j-1),2))-((float)2.5*(j-1));
							d=((float)2.5*pow((j-1),2))-((float)10.5*(j-1))+9;
							Options(term);
							if(a==1 || a==0){
								strcpy(group[g], opt1);
							}
							else{
								strcpy(group[g], opt2);
							}
							if(term==0){
								strcat(group[g], "+");
							}
							if(c==1 || c==0){
								strcat(group[g], opt3);
							}			
							else{
								strcat(group[g], opt4);
							}
							printf("Found a 2X2 group: %s\n", group[g]);	
							g++;
							active[i][j]=!term;
							active[i][j-1]=!term;
							active[i-1][j]=!term;
							active[i-1][j-1]=!term;
							if(i==0 || i==3){
								//As in the matrix "active", the first and last row are the same, both of them have to be changed.
								active[0][j]=!term;
								active[0][j-1]=!term;
								active[4][j]=!term;
								active[4][j-1]=!term;	
								if(j==0 || j==3){
									active[i][0]=!term;
									active[i-1][0]=!term;
									active[i][4]=!term;
									active[i-1][4]=!term;		
								}
								if(j==3 && i==3){
									active[0][0]=!term;
								}
							}
							else if(j==0 || j==3){
								active[i][0]=!term;
								active[i-1][0]=!term;
								active[i][4]=!term;
								active[i-1][4]=!term;	
								if(i==0 || i==3){
									active[0][0]=!term;
									active[0][4]=!term;
									active[4][0]=!term;
									active[4][4]=!term;
								}
							}
						}
					}
				}
			}
		}
		//Now we need to see the pairs or the singles
		//determines pairs with the ungrouped
		for(i=0;i<4;i++){
			for(j=0; j<4; j++){
				//Checks if the 2-group is horizontal: 11
				if(active[i][j]==term){
					if(active[i][j+1]==term){
						printf("Found a pair (horizontal): ");
						a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
						b=-((float)0.5*pow(i,2))+((float)1.5*i);
						c=((float)1.5*pow(j,2))-((float)2.5*j);
						d=((float)2.5*pow(j,2))-((float)10.5*j)+9;
						Options(term);
						strcpy(group[g], opt1);
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt2);
						if(term==0){
							strcat(group[g], "+");
						}
						if(c==1 || c==0){
							strcat(group[g], opt3);
						}
						else{
							strcat(group[g], opt4);			
						}
						printf("%s\n", group[g]);
						g++;
						active[i][j]=!term;
						active[i][j+1]=!term;
						if(i==0 || i==3){
							active[0][j]=!term;
							active[0][j+1]=!term;
							active[4][j]=!term;
							active[4][j+1]=!term;
							if(j==0 || j==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;
							}	
						}
						else if(j==0 || j==3){
							active[0][i]=!term;
							active[4][i]=!term;
							if(i==0 || i==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;	
							}
						}
					}
					/*checks if the 2-groups is vertical (downwards)
					 1
					 1*/	
					else if(active[i+1][j]==term){
						printf("Hello");
						c=-((float)0.33*pow(j,3))+((float)1.5*pow(j,2))-((float)1.17*j);
						d=-((float)0.5*pow(j,2))+((float)1.5*j);
						a=((float)1.5*pow(i,2))-((float)2.5*i);
						b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
						Options(term);
						if(a==1 || a==0){
							strcpy(group[g], opt1);
						}
						else{
							strcpy(group[g], opt2);			
						}
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt3);
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt4);
						printf("Found a pair (vertical): %s\n", group[g]);
						g++;
						active[i][j]=!term;
						active[i+1][j]=!term;
						if(j==0 || j==3){
							active[i][0]=!term;
							active[i+1][0]=!term;
							active[i][4]=!term;
							active[i+1][4]=!term;	
							if(i==0 || i==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;	
							}
						}
						else if(i==0 || i==3){
							active[0][j]=!term;
							active[4][j]=!term;
							if(j==0 || j==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;
							}	
						}
					}		
				}
			}
		}
		/*for(i=0;i<5;i++){
			j=0;
			printf("|%d|", active[i][j]);
			printf("%d|", active[i][j+1]);
			printf("%d|", active[i][j+2]);
			printf("%d|", active[i][j+3]);
			printf("%d|\n", active[i][j+4]);
		}*/
		//Determines pairs with the grouped or the singles
		for(i=0;i<4;i++){
			for(j=0; j<4; j++){
				//Checks if the 2-group is horizontal: 1I (right)
				if(active[i][j]==term){
					if(Kmap[i][j+1]==term){
						printf("Found a pair, withe the right number which was already grouped:");
						a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
						b=-((float)0.5*pow(i,2))+((float)1.5*i);
						c=((float)1.5*pow(j,2))-((float)2.5*j);
						d=((float)2.5*pow(j,2))-((float)10.5*j)+9;
						Options(term);
						strcpy(group[g], opt1);
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt2);
						if(term==0){
							strcat(group[g], "+");
						}
						if(c==1 || c==0){
							strcat(group[g], opt3);
						}
						else{
							strcat(group[g], opt4);			
						}
						printf("%s\n", group[g]);
						g++;
						active[i][j]=!term;
						if(i==0 || i==3){
							active[0][j]=!term;
							active[4][j]=!term;
							if(j==0 || j==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;
							}	
						}
						else if(j==0 || j==3){
							active[0][i]=!term;
							active[4][i]=!term;
							if(i==0 || i==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;	
							}
						}
					}
					/*checks if the 2-groups is vertical (downwards)
					 1
					 I*/	
					else if(Kmap[i+1][j]==term){
						printf("Found a pair, with the below number which was already grouped:");
						c=-((float)0.33*pow(j,3))+((float)1.5*pow(j,2))-((float)1.17*j);
						d=-((float)0.5*pow(j,2))+((float)1.5*j);
						a=((float)1.5*pow(i,2))-((float)2.5*i);
						b=((float)2.5*pow(i,2))-((float)10.5*i)+9;
						Options(term);
						if(a==1 || a==0){
							strcpy(group[g], opt1);
						}
						else{
							strcpy(group[g], opt2);			
						}
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt3);
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt4);
						printf("%s\n", group[g]);
						g++;
						active[i][j]=!term;
						if(j==0 || j==3){
							active[i][0]=!term;
							active[i][4]=!term;
							if(i==0 || i==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;	
							}
						}
						else if(i==0 || i==3){
							active[0][j]=!term;
							active[4][j]=!term;
							if(j==0 || j==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;
							}	
						}
					}
					/*checks if the 2-groups is vertical (upwards)
					 1
					 1*/	
					else if(Kmap[i-1][j]==term && i!=0){
						printf("Found a pair, with the upper number which was already grouped:");
						c=-((float)0.33*pow(j,3))+((float)1.5*pow(j,2))-((float)1.17*j);
						d=-((float)0.5*pow(j,2))+((float)1.5*j);
						a=((float)1.5*pow((i-1),2))-((float)2.5*(i-1));
						b=((float)2.5*pow((i-1),2))-((float)10.5*(i-1))+9;
						Options(term);
						if(a==1 || a==0){
							strcpy(group[g], opt1);
						}
						else{
							strcpy(group[g], opt2);			
						}
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt3);
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt4);
						printf("%s\n", group[g]);
						g++;
						active[i][j]=!term;
						if(j==0 || j==3){
							active[i][0]=!term;
							active[i][4]=!term;
							if(i==0 || i==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;	
							}
						}
						else if(i==0 || i==3){
							active[0][j]=!term;
							active[4][j]=!term;
							if(j==0 || j==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;
							}	
						}
					}
					//Check horizontally, checks the left value.
					else if(Kmap[i][j-1]==term && j!=0){
						printf("Found a pair, withe the left number which was already grouped:");
						a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);
						b=-((float)0.5*pow(i,2))+((float)1.5*i);
						c=((float)1.5*pow((j-1),2))-((float)2.5*(j-1));
						d=((float)2.5*pow((j-1),2))-((float)10.5*(j-1))+9;
						Options(term);
						strcpy(group[g], opt1);
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt2);
						if(term==0){
							strcat(group[g], "+");
						}
						if(c==1 || c==0){
							strcat(group[g], opt3);
						}
						else{
							strcat(group[g], opt4);			
						}
						printf("The groups is [%s]\n", group[g]);
						g++;
						active[i][j]=!term;
						if(i==0 || i==3){
							active[0][j]=!term;
							active[4][j]=!term;
							if(j==0 || j==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;
							}	
						}
						else if(j==0 || j==3){
							active[0][i]=!term;
							active[4][i]=!term;
							if(i==0 || i==3){
								active[0][0]=!term;
								active[0][4]=!term;
								active[4][0]=!term;
								active[4][4]=!term;	
							}
						}
					}
					//It is a one group
					else{
						a=-((float)0.33*pow(i,3))+((float)1.5*pow(i,2))-((float)1.17*i);	
						b=-((float)0.5*pow(i,2))+((float)1.5*i);
						c=-((float)0.33*pow(j,3))+((float)1.5*pow(j,2))-((float)1.17*j);	
						d=-((float)0.5*pow(j,2))+((float)1.5*j);
						Options(term);
						strcpy(group[g],opt1);
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt2);
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt3);
						if(term==0){
							strcat(group[g], "+");
						}
						strcat(group[g], opt4);
						g++;
						active[i][j]=!term;
					}		
				}
			}
		}
	}
	//To see if the values were saved correctly
	///*
	for(i=0;i<4;i++){
			j=0;
			printf("|%d|", Kmap[i][j]);
			printf("%d|", Kmap[i][j+1]);
			printf("|%d|", Kmap[i][j+2]);
			printf("%d|\n", Kmap[i][j+3]);
	}//*/
	
	//To see if the "flags" were marked correctly
	printf("_____\n");
	//*/
	for(i=0;i<5;i++){
			j=0;
			printf("|%d|", active[i][j]);
			printf("%d|", active[i][j+1]);
			printf("%d|", active[i][j+2]);
			printf("%d|", active[i][j+3]);
			printf("%d|\n", active[i][j+4]);
	}//*/
	/*
	for(i=0;i<4; i++){
		printf("Group %d: %s\n", i+1, group[i]);
	}//*/
	g=1;
	///*
	printf("F(ABCD)=(%s)", group[g-1]);
	cmp=strcmp(group[g], "00\0");
	while(cmp==1 && g!=8){
		if(term==1){
			printf("+(%s)", group[g]);
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
/*void Nand(){
}*/
