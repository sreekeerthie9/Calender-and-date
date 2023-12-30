#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

#define TLE 218
#define TRE 191
#define BRE 217
#define BLE 192
#define TT 194
#define LT 195
#define RT 180
#define BT 193
#define HOR 196
#define VER 179
#define SP 32
#define PLUS 197
#define BS 8
#define NL 10
#define WIDTH 5
#define DIM 7
#define TOTCOL 125
#define TOTROW 25
#define DOWN 80
#define UP 72
#define LEFT 75
#define RIGHT 77

void pl(int x){
	printf("%c",x);
}

void gotol(int x, int y){

 COORD coord;

 coord.X = x;

 coord.Y = y;

 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

int dayOfWeek(int y,int m,int d){
	static int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
	if(m<3)
		y--;
	return (y+y/4-y/100+y/400+t[m-1]+d)%7;
}

void smallbox(int col , int row){
	int ctr1;
	int ctr2;

	gotol(col,row);
	pl(TLE);
	for(ctr1=0;ctr1<12;ctr1++){
		pl(HOR);
	}
	pl(TRE);
	row+=1;
	gotol(col,row);
	pl(VER);
	for(ctr1=0;ctr1<12;ctr1++){
		pl(SP);
	}
	pl(VER);
	row+=1;
	gotol(col,row);
	pl(BLE);
	for(ctr1=0;ctr1<12;ctr1++){
		pl(HOR);
	}
	pl(BRE);
	
}

void dabba(){
	int i;
	int ctr1;
	int ctr2;
	int ctr3;
	int row;
	int col;
	col = (TOTCOL - (WIDTH*DIM)+(DIM+1))/2;
	row = (TOTROW - (DIM)+(DIM+1))/2;
	gotol(col,row);
	pl(TLE);
	for(ctr2=0;ctr2<DIM;ctr2++){
		for(ctr1=0;ctr1<WIDTH;ctr1++){
			pl(HOR);
		}
	pl(TT);
	}
	pl(BS);
	pl(TRE);
	
	for(ctr3=0;ctr3<DIM;ctr3++){
		row+=1;
		gotol(col,row);
		for(ctr2=0;ctr2<=DIM;ctr2++){
			pl(VER);
			for(ctr1=0;ctr1<WIDTH;ctr1++){
				pl(SP);
			}			
		}
		row+=1;
		gotol(col,row);
		pl(LT);
		for(ctr2=0;ctr2<DIM;ctr2++){
			for(ctr1=0;ctr1<WIDTH;ctr1++){
				pl(HOR);
			}
		pl(PLUS);
		}
		pl(BS);
		pl(RT);
	}
	gotol(col,row);
	pl(BLE);
	for(ctr2=0;ctr2<DIM;ctr2++){
		for(ctr1=0;ctr1<WIDTH;ctr1++){
			pl(HOR);
		}
		pl(BT);
	}
	pl(BS);
	pl(BRE);
}

void days_of_week(){
	int ctr;
	int row;
	int col;
	col = (TOTCOL - (WIDTH*DIM)+(DIM+1))/2;
	row = (TOTROW - (DIM)+(DIM+1))/2;
	col+=2;
	row+=1;
	gotol(col,row);
	char *week_days[DIM]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
	for(ctr=0;ctr<DIM;ctr++){
		gotol(col+(ctr*(WIDTH+1)),row);
		printf("%s",week_days[ctr]);
	}
}

void calendar(int month , int year){
	int dayctr;
	int ctr;
	int row;
	int col;
	
	char *month_names[]={"","January","February","March","April","May","June","July","August","September","October","November","December"};
	int days_in_months[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	
	col = (TOTCOL - (WIDTH*DIM)+(DIM+1))/2;
	row = (TOTROW - (DIM)+(DIM+1))/2;
	
	smallbox(col+7,row-4);
	gotol(col+9,row-3);
	printf("%10s",month_names[month]);
	
	smallbox(col+25,row-4);
	gotol(col+26,row-3);
	printf("%7d",year);
	
	row+=3;
	col+=3;
	gotol(col,row);
	
	days_in_months[2]=(((year%4==0)&&(year%100!=0))||(year%400==0))?29:28;
	
	for(ctr=dayOfWeek(year,month,1),dayctr=1;dayctr<=days_in_months[month];dayctr+=1,ctr+=1){
		if(ctr==DIM){
			ctr=0;
			row+=2;
		}
		gotol(col+(ctr*(WIDTH+1)),row);
		printf("%02d",dayctr);
	}
}

void cleancalendar(){
	int dayctr;
	int ctr;
	int row;
	int col;
	
	
	
	col = (TOTCOL - (WIDTH*DIM)+(DIM+1))/2;
	row = (TOTROW - (DIM)+(DIM+1))/2;
	
	gotol(col,row-10);
    printf("click right arrow for next month");
    gotol(col,row-9);
    printf("click left arrow for previous month");
    gotol(col,row-8);
   	printf("click up arrow for next year\n");
   	gotol(col,row-7);
    printf("click down arrow for previous year\n");
	
	row+=3;
	col+=3;
	gotol(col,row);
	
	for(ctr=0,dayctr=1;dayctr<=42;dayctr+=1,ctr+=1){
		if(ctr==DIM){
			ctr=0;
			row+=2;
		}
		gotol(col+(ctr*(WIDTH+1)),row);
		printf("  ");
	}
}

int main(){
	int year;
	int month;
	int key;
	
	month=10;
	year=2023;
	
	dabba();
	days_of_week();
	do{
		cleancalendar();
		calendar(month,year);
		getch();
		key = getch();
		
		switch(key){
			case RIGHT:
				month+=1;
				if(month>12){
					month=1;
					year+=1;
				}
				break;
			case LEFT:
				month-=1;
				if(month==0){
					month=12;
					year-=1;
				}
				break;
			case UP:
				year+=1;
				break;
			case DOWN:
				year-=1;
		}
		
	}while(key!=27);
	
	
    
	return EXIT_SUCCESS;
	
}

