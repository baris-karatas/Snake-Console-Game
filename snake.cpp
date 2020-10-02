#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <pthread.h>
#include <time.h>
int piece=7;
int kor[2][100]={{10,10,10,10,10,10,10},
				 {11,10,9,8,7,6,5}};
char state;
int x=1;
FILE *fptr;
char map[20][100]; 
int yem_x,yem_y;
char queue[100];  // kordinates of snake where shoud to be 
char hi_score[100];
void  *thread(void *vargp)
  {
  		bool j=true;
  		char tmp;
  		//sleep(1);
  		state='4';
  		while(j){

		 tmp=getch();//gets input from user
  			if(state=='4'&&tmp=='6'){						// and prints input into array of queue 
  				state='4';
			}else if(state=='8'&&tmp=='5'){				// and prints input into array of queue 
				state='8';
			}else if(state=='6'&&tmp=='4'){						// and prints input into array of queue 
				state='6';
			}else if(state=='5'&&tmp=='8'){
				state='5';
			}else{state=tmp;
			} 
			if(tmp=='q'){					 
				j=false;
			} 		
		}
		
  	
  	return NULL;
  }
void *Game_Over(void *vargp)  {
	int i,j;
	while(x){
		for(i=0;i<piece-1;i++){
		for(j=i+1;j<piece-1;j++){
			if(kor[0][i]==kor[0][j]){
				if(kor[1][i]==kor[1][j]){
					x=0;
					i=piece;
					j=piece;
					pthread_exit(NULL);				
				}
			}
		}
	}
	}
	
	
	
}

void down(int d1){
	kor[0][d1]++;
	if(kor[0][d1]>=19){
	kor[0][d1]=0;
	}
}
void up(int b1){
	kor[0][b1]--;
	if(kor[0][b1]<=0){
		kor[0][b1]=19;
		}	
	
}
void left(int c1){
	kor[1][c1]--;
	 if(kor[1][c1]<=0){
		kor[1][c1]=49;
		}	
}
void right(int a1){
	kor[1][a1]++;
	if(kor[1][a1]>=49){
	kor[1][a1]=0;	
	}
}
void *yon_thread(void *vargp){
		
		int j;
		j=1;
		
		int b;
		pthread_t trigger;
		pthread_create(&trigger,NULL,Game_Over,NULL);
		srand((unsigned)time(NULL));
		yem_x=rand();
		yem_x=yem_x%48;
		yem_y=rand();
		yem_y=yem_y%18;
		int a,i;
		
		int domestic;
		
		for(i=0;i<piece;i++){
			queue[i]='4';
		}
		while(x){
			domestic=piece;
			for(a=domestic-1;a>0;a--){
			queue[a]=queue[a-1];
		}
		queue[0]=state;
		for(a=0;a<=domestic;a++){
			if(queue[a]=='4'){
				left(domestic-a-1);
			}
				if(queue[a]=='8'){
				up(domestic-a-1);
			}
				if(queue[a]=='6'){
				right(domestic-a-1);
			}
				if(queue[a]=='5'){
				down(domestic-a-1);
			}
			
		}
		usleep(125*1000);
		
		
		//ret=(void*)b;
	
		}
		
		
	
}
void *score_counter(void *vargp){
	int aq;
	int *pointer;
	char temporary[100];
	pointer=&piece;
	//char tmp[100];
	char* filename="C:\\Users\\baris\\Desktop\\GitHUb\\snake\\hiscore.txt";
	fptr=fopen(filename,"r");
     fgets(temporary,100,fptr);
     //temporary-=44;
     int katsay=1,a, j,i=0;
     while(temporary[i]!=NULL){
     	i++;
	 }
	 for(j=0;j<i;j++){
		 for(a=0;a<i-j-1;a++){
		 	katsay=katsay*10;
		 }
		 aq=aq+(temporary[j]-48)*katsay;
		 katsay=1;
		 
		 
	 }
	 
	if(aq<*pointer){
	fptr=fopen(filename,"w");
	fprintf(fptr,"%d",*pointer);
	fclose(fptr);
	fptr=fopen(filename,"r");
	//fscanf(fptr,"%d",hi_score);
	fgets(hi_score,100,fptr);
	
	fclose(fptr);
	}
	
}
void *Food(void *vargp){
		int i=piece;
		char tmp;
		int matrix[2][piece+1];
		srand((unsigned)time(NULL));
		yem_x=rand();
		yem_x=yem_x%48;
	    pthread_t hi_score; 
	    pthread_create(&hi_score, NULL,score_counter,NULL);
	    pthread_join(hi_score, NULL);
		yem_y=rand();
		yem_y=yem_y%18;
		yem_y++;
		yem_x++;
	matrix[0][0]=0;
	matrix[0][0]=0;
	for(i=0;i<piece+1;i++){
		matrix[0][i+1]=kor[0][i];
		matrix[1][i+1]=kor[1][i];
	}
	for(i=0;i<piece+1;i++){
		kor[0][i]=matrix[0][i];
		kor[1][i]=matrix[1][i];
	}
			
	//kor[0][0]=kor[0][1];
	//kor[1][0]=kor[1][1];
	tmp=queue[piece-1];
	queue[piece]=queue[piece-1];
	
	if(queue[piece]=='4'){
		kor[0][0]=kor[0][1];
		kor[1][0]=kor[1][1]+1;
	}
	if(queue[piece]=='5'){
		kor[0][0]=kor[0][1]-1;
		kor[1][0]=kor[1][1];
	}if(queue[piece]=='6'){
		kor[0][0]=kor[0][1];
		kor[1][0]=kor[1][1]-1;
	}if(queue[piece]=='8'){
		kor[0][0]=kor[0][1]+1;
		kor[1][0]=kor[1][1];
	}
	piece++;		
}
void *ana_thread(void *vargp){
	
	int i,j,k;
	
	int a1;
	char temp[100];
	for(i=0;i<20;i++){
		for(j=0;j<50;j++){
			map[i][j]=' ';
		}
	}
	
	for(i=0;i<20;i++){
		map[i][0]='#';
		map[i][49]='#';
	}
	for(i=0;i<50;i++){
		map[0][i]='#';
		map[19][i]='#';
	}
	
	while(x){
		
		for(i=1;i<19;i++){
			for(j=1;j<49;j++){
				map[i][j]=' ';
				if(i==yem_y&&j==yem_x){
					map[i][j]='f';
				}
				for(k=0;k<piece;k++){
					if(kor[0][k]>=19){
						kor[0][k]==0;	
					}
					 if(kor[0][k]==i&&kor[1][k]==j){
					map[i][j]='*';
					
					}
					
					
					
					
					
				
			}
		}
	}
		
		printf("Score : %d \t\t",piece-1);
		printf("High score is : %s\n\n",hi_score);	
		for(i=0;i<20;i++){
			for(j=0;j<50;j++){
				printf("%c ",map[i][j]);
				                                                              
			}
			printf("\n");
		}
		printf("MADED BY DARKSTONE.INC");
		if(kor[0][piece-1]==yem_y&&kor[1][piece-1]==yem_x){
			pthread_t thread_id;
			pthread_create(&thread_id,NULL,Food,NULL);
		}
		
		
		usleep(30*1000);
	
		
		
		system("cls");
	  
					
		}
		
		
		
		
	}
	
				 
int main(){
	int i,j;
	char* filename="C:\\Users\\baris\\Desktop\\GitHUb\\snake\\hiscore.txt";
	fptr=fopen(filename,"r");
    fgets(hi_score,100,fptr);
	pthread_t thread_id;
//	pthread_t Game_Over;
//	pthread_create(&Game_Over,)
//	pthread_t thread_id;
	pthread_create(&thread_id, NULL,thread,NULL);
	pthread_create(&thread_id,NULL,ana_thread,NULL);
	pthread_create(&thread_id,NULL,yon_thread,NULL);
	pthread_join(thread_id,NULL);
	//system("cls");
	pthread_cancel(thread_id);
	printf("Score : %d \t\t",piece-1);
		printf("High score is : %s\n\n",hi_score);	
		for(i=0;i<20;i++){
			for(j=0;j<50;j++){
				printf("%c ",map[i][j]);
				                                                              
			}
			printf("\n");
		}
		printf("MADED BY BLACKSTONE.INC\n");
	printf("GAME OVER your score is: %d",piece-1);
	
}
