/*						
 *
 *
 *
 *  Project1 - Digital Clock
 *
 *
 *
 */


#include <stdio.h>		//include stdio.h header file to use  printf,scanf
#include <time.h>		//include time.h header file to get system time and convert to string using asctime
#include <stdlib.h>		//include stdlib.h header file to use system("clear") functionality
#include <string.h>		//include string.h header file to use strcmp() function
#include <signal.h>		//include signal.h header file to catch ctrl+c and reset ANSI code

void printRow(int color,int cur);		//printRow funtion which prints a row(5 colored whitespaces) (#####).
void printMidSpace(int color,int cur);		//function to print a single row with a blank space inbetweeen colored spaces (## ##) Intakes color(int color) and which column/element to be printed(int cur)
void printLeftSpace(int color,int cur);		//function to print a single row with two colored spaces at the beginihng followed by 3  balnks(##    ) Intakes color(int color) and which column/element to be printed (int cur)
void printRightSpace(int color,int cur);	//function to print a single row with two colored spaces at the end with 3 blank spaces at the begining (   ##) Intakes color(int color) and which column/element to be printed (int cur)
void One(int color,int cur);                            //function to print number 1.Intakes color(int color) and which column/element to be printed(int cur)
void Zero(int color,int cur);				//function to print number 0.Intakes color(int color) and which column/element to be printed (int cur)
void Two(int color,int cur);				//function to print number 2.Intakes color(int color) and which column/element to be printed (int cur)
void Three(int color,int cur);				//function to print number 3.Intakes color(int color) and which column/element to be printed (int cur)
void Four(int color,int cur);				//function to print number 4.Intakes color(int color) and which column/element to be printed (int cur)
void Five(int color,int cur);				//function to print number 5.Intakes color(int color) and which column/element to be printed (int cur)
void Six(int color,int cur);				//function to print number 6.Intakes color(int color) and which column/element to be printed (int cur)
void Seven(int color,int cur);				//function to print number 7.Intakes color(int color) and which column/element to be printed (int cur)
void Eight(int color,int cur);				//function to print number 8.Intakes color(int color) and which column/element to be printed (int cur)
void Nine(int color,int cur);				//function to print number 9.Intakes color(int color) and which column/element to be printed (int cur)
int cursor(int col);					//function to return next cursor position as an integar depending on the column/element being printed.Intakes column 
void Dots(int color,int cur);				//function to print two vertical dots 
void chooseNumber(char num,int color,int col);		//function to print digit depending on which digit to print in the string for time obtained by asctime()
int colorFun(char* color);				//function to return ANSI color code number depending on user input
void usage();						//function to print usage of program
void abortProg(int);					//function to catch ctrl+c to reset  ANSI escape codes

int main(int argc,char ** argv){
	
	printf("\033[s");			//saves initial cursor position
	signal(SIGINT, abortProg);		//use of signal() to catch ctrl cand run abortProg() function		
	int color=47;				//set color to white
						//error handling
	if(argc==1){				
		color=47;
	}else if(strcmp(argv[1],"-c")==0){
		
		if(argc==2){
			printf("\033[31mInvalid\033[0m use of arguments.\n");
			usage();
			return 0;
		}else{	
			color = colorFun(argv[2]);
			if(color==0){
				printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n",argv[2]);
				return 0;
			}
		}
	}else if(strcmp(argv[1],"-h")==0){
		usage();
		printf("<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
		return 0;

	}else{
		printf("\033[31mInvalid\033[0m use of arguments.\n");
		usage();
		return 0;
		
	}
	
	printf("\033[?25l");			//ANSI escape code making the cursor invisible

	time_t s,print_time=0;			//declaring varable time_t to store system time and declare and initialize print_time to get last printed time

	struct tm* current_time;		//declaring struct to store current time

	system("clear"); 			//clear screen
	printf("\n");				//print new line;
	while(1){				//while loop to continously print time 
		if((time(NULL)-print_time)>=1){	//checking whether the differencee between  number of seconds since 1970 given by time(NULL) and printed time is equal or greater than 1
			
			fflush(stdout);

			s = time(NULL);		//storing time in variable s

			current_time = localtime(&s);	//getting local time using localtime() function 

			for(int i=0;i<8;i++){		//for loop iterate over the time as a string usiing asctim()
				chooseNumber(asctime(current_time)[i+11],color,i);	//getting only the time in asctime[] string and feeding each digit into choooseNumber() function which prints the digits
			}
			print_time = time(NULL);	//assign print time to current time
			printf("\n\033[22C");		//adjust cursor position to print date
			
			printf("\033[%dm%d-%02d-%02d\n",color-10,current_time->tm_year+1900,((current_time->tm_mon==11)?1:current_time->tm_mon+1),current_time->tm_mday);	//print date using elements in current_time variable
			printf("\033[7A");		//move cursor to inital starting position
		}
	}
}

void abortProg(int sig){		//function to catch ctrl+c to reset  ANSI escape codes
	
	printf("\033[?25h");		//make cursore visible
	printf("\033[0m");		//reset ANSI escape code
	printf("\033[u");		//restore cursor to inital saved position
	printf("\033[J");		//clear screen
	exit(0);

}
void usage(){
	printf("usage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n");
}

void chooseNumber(char num,int color,int col){	//function to print digit depending on which digit to print in the string for time obtained by asctime()

	if(col!=0){				//for all columns excluding 0, move the cursor up by 5 rows after printing the number
		printf("\033[5A");
	}	
	int cur = cursor(col);			//initialize cur to store output of cursor() function which returns how many spaces the cursor move to the right

	switch(num)				//switch to choose number to be printed
	{	
		case '0':			//0 digit runs the Zero() function and passes the color and cursor position(cur)
			Zero(color,cur);
			break;
		case '1':			//1 digit runs the One() function and passes the color and cursor position(cur)
                        One(color,cur);
                        break;
		case '2':			//2 digit runs the Two) function and passes the color and cursor position(cur)
                        Two(color,cur);
                        break;
		case '3':			//3 digit runs the Three() function and passes the color and cursor position(cur)
                        Three(color,cur);
                        break;
		case '4':			//4 digit runs the Four() function and passes the color and cursor position(cur)
                        Four(color,cur);
                        break;
                case '5':			//5 digit runs the Five() function and passes the color and cursor position(cur)
                        Five(color,cur);
                        break;
                case '6':			//6 digit runs the Six() function and passes the color and cursor position(cur)
                        Six(color,cur);
                        break;
                case '7':			//7 digit runs the Seven() function and passes the color and cursor position(cur)
                        Seven(color,cur);
                        break;
		case '8':			//8 digit runs the Eight() function and passes the color and cursor position(cur)
                        Eight(color,cur);
                        break;
                case '9':			//9 digit runs the Nine() function and passes the color and cursor position(cur)
                        Nine(color,cur);
                        break;
		case ':':			//case : runs Dots() function and passes the color and cursor position(cur)
			Dots(color,cur);
			break;
		default:			//default prints error
			printf("Error\n");	
			break;
		}
		printf("\033[0;m");

}

int cursor(int col){				 //function to return next cursor position as an integar depending on the column/element being printed.Intakes column

        switch(col)				//switch case to run function according to input column
        {
                case 0:				//taking initial column as zero
                        return 1;		//return 1 so that the cursor moves 1 step to the right
                case 1:				//for column 1 return 8 so that the cursor moves 8 steps to the right
                        return 8;
		case 2:				//for column 2 return 16 so that the cursor moves 16 steps to the right
                        return 16;
                case 3:				//for column 3 return 20 so that the cursor moves 20 steps to the right
                        return 20;
                case 4:				//for column 4 return 27 so that the cursor moves 27 steps to the right
                        return 27;
		case 5:				//for column 5 return 35 so that the cursor moves 35 steps to the right
                        return 35;		
                case 6:				//for column 6 return 39 so that the cursor moves 39 steps to the right
                        return 39;
                case 7:				//for column 7 return 46 so that the cursor moves 46 steps to the right
                        return 46;
                default:			//default value returns 0 though it would not be required
                        return 0;

        }

}

void Dots(int color,int cur){			//function to print the two vertical dots

        printf("\033[1B");			//move cursor 1 step down from the top 
        printf("\033[%dC",cur);			//move cursor to relevant column 
        printf("\033[;%dm  ",color);		//print two colored spaces
        printf("\033[2B");			//move curspr two steeps down
        printf("\033[2D");			//move cursor two steps to the left
        printf("\033[;%dm  ",color);		//print two colored spaces
        printf("\033[1B");			//move one step down
        printf("\033[0;m");			//reset ANSI color codes
        printf("\n");				//move cursor to newline
}

void Zero(int color,int cur){                   //function to print number 0.Intakes color(int color) and which column/element to be printed (int cur) and passes the arguments to Row printing functions

        printRow(color,cur);                    //using function printRow to print      #####
        printMidSpace(color,cur);               //using function midSpace to print      ## ##
        printMidSpace(color,cur);               //using function midSpace to print      ## ##
        printMidSpace(color,cur);               //using function midSpace to print      ## ##
        printRow(color,cur);                    //using function printRow to print      #####
        printf("\033[0;m");
}

void One(int color,int cur){                    //function to print 1
                                	                                                        //	##
        for(int i=0;i<=4;i++){                  //for loop to use row function 5 times      		##
                printRightSpace(color,cur);     //using printRightSpace() function to form the number 1 ##
        }                                                                                       //      ##
        printf("\033[0;m");                     //reset ANSI color codes                                ##
}
void Two(int color,int cur){			//function to print number 2.Intakes color(int color) and which column/element to be printed (int cur) and passes the arguments to Row printing functions

        printRow(color,cur);			//using function printRow to print      #####
        printRightSpace(color,cur);		//using function RightSpace to print       ##
        printRow(color,cur);			//using function printRow to print      #####
        printLeftSpace(color,cur);		//using function LeftSpace to print     ##
        printRow(color,cur);			//using function printRow to print      #####
}

void Three(int color,int cur){			//function to print number 3.Intakes color(int color) and which column/element to be printed (int cur) and passes the arguments to Row printing functions

        printRow(color,cur);			//using function printRow to print      #####
        printRightSpace(color,cur);		//using function RightSpace to print       ##
        printRow(color,cur);			//using function printRow to print      #####
        printRightSpace(color,cur);		//using function RIghtSpace to print       ##
        printRow(color,cur);			//using function printRow to print      #####
}
void Four(int color,int cur){			//function to print number 4.Intakes color(int color) and which column/element to be printed (int cur) and passes the arguments to Row printing functions

        printMidSpace(color,cur);		//using function MidSpace to print      ## ##
        printMidSpace(color,cur);		//using function MidSpace to print      ## ##
        printRow(color,cur);			//using function printRow to print      #####
        printRightSpace(color,cur);		//using function RightSpace to print       ##
        printRightSpace(color,cur);		//using function RightSpace to print       ##
}
void Five(int color,int cur){			//function to print number 5.Intakes color(int color) and which column/element to be printed (int cur) and passes the arguments to Row printing functions

        printRow(color,cur);			//using function printRow to print      #####
        printLeftSpace(color,cur);		//using function LeftSpace to print     ##
        printRow(color,cur);			//using function printRow to print      #####
        printRightSpace(color,cur);		//using function RightSpace to print       ##
        printRow(color,cur);			//using function printRow to print      #####
}
void Six(int color,int cur){			//function to print number 6.Intakes color(int color) and which column/element to be printed (int cur) and passes the arguments to Row printing functions

        printRow(color,cur);			//using function printRow to print      #####
        printLeftSpace(color,cur);		//using function LeftSpace to print     ##
        printRow(color,cur);			//using function printRow to print      #####
        printMidSpace(color,cur);		//using function midSpace to print      ## ##
        printRow(color,cur);			//using function printRow to print      #####
}
void Seven(int color,int cur){			//function to print number 7.Intakes color(int color) and which column/element to be printed (int cur) and passes the arguments to Row printing functions

        printRow(color,cur);			//using function printRow to print      #####
        printRightSpace(color,cur);		//using function RightSpace to print       ##
        printRightSpace(color,cur);		//using function RightSpace to print       ##
        printRightSpace(color,cur);		//using function RightSpace to print       ##
        printRightSpace(color,cur);		//using function RightSpace to print       ##
}
void Eight(int color,int cur){			//function to print number 8.Intakes color(int color) and which column/element to be printed (int cur) and passes the arguments to Row printing functions

        printRow(color,cur);			//using function printRow to print      #####
        printMidSpace(color,cur);		//using function midSpace to print      ## ##
        printRow(color,cur);			//using function printRow to print      #####
        printMidSpace(color,cur);		//using function midSpace to print      ## ##
        printRow(color,cur);			//using function printRow to print      #####
}

void Nine(int color,int cur){			//function to print number 9.Intakes color(int color) and which column/element to be printed (int cur) and passes the arguments to Row printing functions	

	printRow(color,cur);			//using function printRow to print      #####
        printMidSpace(color,cur);		//using function midspace to print      ## ##
        printRow(color,cur);			//using function printRow to print      #####
        printRightSpace(color,cur);		//using function rightSpace to print   	   ##
        printRow(color,cur);			//using function printRow to print      #####
}

void printLeftSpace(int color,int cur){		//function to print a single row with a colored whitespaces at the beginihng followed by 3 balnks(##   ) Intakes color(int color) and which column/element to be printed (int cur)

        printf("\033[%dC",cur);				//move cursor to relevant column using cur
        for(int i=0;i<=5;i++){				//for loop go through the row
                if(i<2){			
                        printf("\033[;%dm ",color);	//if i<2 print colored space
                }else{
                        printf("\033[0;m");		//else print blank space
                        printf(" ");
                }
        }
        printf("\n");
}

void printRightSpace(int color,int cur){	//function to print a single row with 3 colored spaces at the end with 3 blanks at the begining (   ##).Intakes color(int color) and which column/element to be printed (int cur)

        printf("\033[%dC",cur);				//move cursor to relevant column using cur
        for(int i=0;i<=5;i++){				//for loop to print colored space
                if(i>3){				//if int i>3 color the space
                        printf("\033[;%dm ",color);	//using int color to set the specific color
                }else{
                        printf(" ");			//if int<4 leave a blank space
                }
        }
        printf("\n");					//jump to the next line
        printf("\033[0;m");				//reset ANSI escape codes
}


void printRow(int color,int cur){		//printRow funtion which prints a row(5 colored spaces) (#####).

        printf("\033[%dC",cur);			//set color according to input cur
        printf("\033[;%dm      \n",color);	//print 5 colored spaces which makes up a row
        printf("\033[0;m");			//reset ANSi escape code
}
void printMidSpace(int color,int cur){		//function to print a single row with a blank space inbetweeen colored spaces (## ##).Intakes color(int color) and which column/element to be printed(int cur)

        printf("\033[%dC",cur);				//move cursor to relevant column using cur
        for(int i=0;i<=5;i++){;				//for loop go through the spaces
                if((i<2)||(i>3)){			//if i<2 or i>3 print colored space
                        printf("\033[;%dm ",color);
                }else{					//else print blank space
                      	printf("\033[0;m");
                        printf(" ");
                }
                printf("\033[0;m");			//reset ANSI escape code
        }
        printf("\n");
}
		
int colorFun(char * color){				//function to return ANSI color code number depending on user input

        if(strcmp(color,"red")==0){			//"red" returns color code 41
                return 41;
        }else if(strcmp(color,"black")==0){		//"black" returns color code 40
                return 40;
        }else if(strcmp(color,"green")==0){		//"green" returns color code 42
                return 42;
        }else if(strcmp(color,"yellow")==0){		//"yellow" returns color code 43
                return 43;
        }else if(strcmp(color,"blue")==0){		//"blue" returns color code 44
                return 44;
        }else if(strcmp(color,"magenta")==0){		//"magenta" returns color code 45
                return 45;
        }else if(strcmp(color,"cyan")==0){		//"cyan" returns color code 46
                return 46;
        }else{				
                return 0;
        }
}	
