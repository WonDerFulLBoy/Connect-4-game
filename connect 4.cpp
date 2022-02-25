#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <ctime>

const int row = 6;
const int col = 7;

int player1_color = 6 ;
int player2_color = 4 ;
int menu_color = 10 ;
int border_color = 14 ;

void clearScreen() {
	system("cls");
}

void sleep(unsigned int mseconds) {
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

void setTextColor(int textColor, int backColor = 0) {
	 HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	 int colorAttribute = backColor << 4 | textColor;
	 SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void game_print_border(int border[row][col]){
	clearScreen();
	for(int i=0;i<=row*2;i++){
		for(int j=0;j<=col*2;j++){
			if(i%2==0){
				setTextColor(border_color);
				printf("-");
			}else if (j%2==0){
                setTextColor(border_color);
				printf("|");
			}else{
				if(border[i/2][j/2]==0){
				    setTextColor(border_color);
					printf(" ");
				}else if(border[i/2][j/2]==1){
					setTextColor(player1_color);
					printf("X");
				}else{
				    setTextColor(player2_color);
					printf("O");
				}
			}
		}
		printf("\n");
		sleep(10);
	}
}

// -1 => bazi edame darad.
// 0 => bazi mosavi shode.
// 1 => nafar aval borde
// 2 => nafar dovom berde
int game_status(int border[row][col]){
	bool sw=false;
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(border[i][j]==0){
				sw=true;
			    continue;
			}
			// rast
			int count=1;
			int k=j+1;
			while(k<col && border[i][j]==border[i][k]){
				k++;
				count++;
			}
			if(count>=4){
				return border[i][j];
			}
			// rast paine
			count =1;
			k = i+1;
			int k2=j+1;
			while(k<row && k2<col && border[i][j]==border[k][k2]){
				k++;
				k2++;
				count++;
			}
			if(count >=4){
				return border[i][j];
			}
			// paine
			count =1;
			k = i+1;
			while(k<row && border[i][j]==border[k][j]){
				k++;
				count++;
			}
			if(count >=4){
				return border[i][j];
			}
			// chap paine
			count =1;
			k = i+1;
		    k2=j-1;
			while(k<row && k2>=0 && border[i][j]==border[k][k2]){
				k++;
				k2--;
				count++;
			}
			if(count >=4){
				return border[i][j];
			}
		}
	}

	if(sw == true){
		return -1;
	}
	return 0;
}
int game_pos(int border[row][col],int y){
	if (y<0 || y>=col){
		return -1;
	}
	int x=row-1;
	while(x>=0 && border[x][y]!=0){
		x--;
	}
	return x;
}

void game(){
	int border[row][col]={{0}};
	int turn=1;
	int x,y;
	while(game_status(border) == -1){
		game_print_border(border);
//		setTextColor(border_color);
		do{
			printf("turn %d input:",turn);
			scanf(" %d",&y);
			y--;
			x = game_pos(border,y);
		}while(x == -1);
		border[x][y]=turn;
		if(turn ==1){
			turn =2;
		}else{
			turn =1;
		}
	}
	game_print_border(border);
	int status =game_status(border);
	setTextColor(border_color);
	if(status==1){
		printf("Woooow nafar aval bord.");
	}else if(status==2){
		printf("Woooow nafar dovom bord.");
	}else{
		printf("no no mosavi shod...!");
	}
	sleep(3000);
}

void menu_start(){
	int pos;
	while(true){
		clearScreen();
		setTextColor(menu_color);
		printf("1:start game\n");
		printf("2:exit\n");
		scanf(" %d",&pos);
		switch(pos){
			case 1:
				game();
				break;
			case 2:
				printf("bye bye");
				sleep(1000);
				return;
		}
	}
}

int main(int argc, char** argv) {
	menu_start();
	return 0;
}
