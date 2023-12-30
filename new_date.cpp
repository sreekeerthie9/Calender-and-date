#include<iostream>
using namespace std;

class date{
	private:
		int offset;
		int isLeap(int yyyy){
			return (((yyyy%4==0)&&(yyyy%100!=0))||(yyyy%400==0))?1:0;
		}
	public:
		date( int dd=1,int mm=1,int yyyy=1900){
			int temp_year;
			offset=0;
			int days_gone_as_months[]={0,0,31,59,90,120,151,181,212,243,273,304,334};
			for(int temp_year=1900;temp_year<yyyy;temp_year+=1 ){
				offset+=365+isLeap(temp_year);
			}
			offset+=days_gone_as_months[mm];
			offset+=dd;
		}
		
		void printdate(){
			int yyyy;
			int mm;
			int dd;
			int temp_offset;
			temp_offset=offset;
			int days_gone_as_months[]={0,0,31,59,90,120,151,181,212,243,273,304,334};
			for(yyyy=1900 ;temp_offset>=365;yyyy++){
				temp_offset-=365+isLeap(yyyy);
			}
			for(mm=1;mm<=12 && temp_offset>days_gone_as_months[mm];mm++);
			mm-=1;
			dd=temp_offset-days_gone_as_months[mm];
			cout<<dd<<"/"<<mm<<"/"<<yyyy<<endl;
			
		}
		
		date operator +(int incDays){
			date temp;					// we should not change actualoffset so we are taking tenp offset
			temp.offset = offset;
			temp.offset+=incDays;
			
			return temp;
		}
		date operator -(int decDays){	//decreasing the date to given number of days
			date temp;
			temp.offset=offset;
			temp.offset-=decDays;
			
			return temp;
		}
		date operator - (date gd){		//how many days in between
			int res;
			res= offset-gd.offset;
			cout<<res<<"\n";
			if(res<0)
				res=-res;
			return res;					//returning no.of days between our date and given date
		}
		bool operator > (date gd)
		{
			return offset > gd.offset;
		}
		
		bool operator < (date gd)
		{
			return offset < gd.offset;
		}
		bool operator == (date gd){
			return offset == gd.offset;
		}
};

int main(){
	date today(18,10,2023);
	date dob(12,3,2004);
	date mdob(23,3,1975);
	dob.printdate();
	today.printdate();
	
	date nod = dob+10000;
	nod.printdate();
	
	date tomorrow = today+25;
	tomorrow.printdate();
	date yesterday = today-25;
	yesterday.printdate();
	
	  
	(today.operator -(dob)).printdate();
	
	(today.operator -(mdob)).printdate();
	
	bool less=(today<tomorrow);
	cout<<less<<endl;
	cout<<(tomorrow==yesterday)<<endl;
}
