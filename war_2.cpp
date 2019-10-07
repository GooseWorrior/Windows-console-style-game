#include<iostream>
#include<windows.h>
#include <conio.h>
#include<ctime>
using namespace std;

struct pos {
	int x;
	int y;
};
struct cursor {
	pos offset;
	int height;
	int code;
	int life;
};
void gotoxy(int x, int y)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(hOut, c);
}

const char * shape_1[] = {"    ^    ",
                          "==^=+=^==",
                          "    +    ",
                          "   =^=   "};
const char * shape_0[] = {"*"};
const char * shape_2[] = {"  ##  ",
                          "<<##>>",
						  "  ##  "};
    
void print_shape(const char * shape[], cursor cursor_inst) {
	int pos = cursor_inst.offset.y;
	gotoxy(cursor_inst.offset.x, pos);
	for (int i = 0; i < cursor_inst.height; i++) {
		cout<<shape[i];
		pos++;
		gotoxy(cursor_inst.offset.x, pos);
	}
}

void generate(cursor c, cursor obj_list[1000], int * pos) {
   obj_list[*pos] = c;
   *pos += 1;
}

int check_hit(cursor obj, cursor obj_list[1000], int pos) {
	int count = 0;
	for (int i = 0; i < pos; i++) {
		if (obj_list[i].code == 0 && obj_list[i].offset.y <= 5/*& obj_list[i].offset.x <= obj.offset.x + 3 &&
		obj_list[i].offset.x >= obj.offset.x && obj_list[i].offset.x <= obj.offset.y + 2 && 
		obj_list[i].offset.y >= obj.offset.y*/) {
			count++;
			obj_list[i].code = -1;
		}
	}
	return count;
}

void physics(cursor obj_list[1000], int pos, int counter) {
	for (int i = 0; i < pos; i++) {
		switch(obj_list[i].code) {
   	     case 0:
   	     	obj_list[i].offset.y -= 1;
   	     	if (obj_list[i].offset.y < 0) {
   	     		obj_list[i].code = -1;
			}
   	    break;
   	     case 2:
			int temp = check_hit(obj_list[i], obj_list, pos); 
   	        if (temp) {
   	        	obj_list[i].life -= temp;
			}
			if (obj_list[i].life <= 0) {
				obj_list[i].code = -1;
			} else if (counter % 100 == 0) {
   	        	obj_list[i].offset.x += (rand() % 3) - 1;
			}
        }	
	}
}
void print_obj_list(cursor obj_list[1000], int pos) {
	for (int i = 0; i < pos; i++) {
		switch(obj_list[i].code) {
   	     case 0:
   	     	print_shape(shape_0, obj_list[i]);
   	    break;
     	case 1:
     		print_shape(shape_1, obj_list[i]);
   	    break;
   	    case 2:
   	    	print_shape(shape_2, obj_list[i]);
   	    break;
        }	
	}
}
// 0: bullet 1: plane -1: destroyed 2: enemy
int main() {
	srand(time(NULL));
	const int USER = 0;
	int counter = 0;
	int pos = 0;
    cursor object_list [1000];
	cursor temp_cursor = {{50, 20}, 4, 1, 10};
	 print_shape(shape_1, temp_cursor);
	 generate(temp_cursor, object_list, &pos);
	 
	 
	 int temp_x = 0;
	 int temp_y = 0;
/*	 for (int i = 0; i < 5; i++) {
	 	temp_x = rand() % 90;
	 	temp_y = rand() % 10;
	 	temp_cursor = {{temp_x, temp_y}, 3, 2, 3};
	 	generate(temp_cursor, object_list, &pos);
	 }*/
	while (1) {
		if(_kbhit())
		{
			switch(_getch())
			{
				case 115:
					system("cls");
        			object_list[USER].offset.y += 1;
        			break;
				case 97:
					system("cls");
					object_list[USER].offset.x -= 1;
        			break;
        		case 100:
        			system("cls");
        			object_list[USER].offset.x += 1;
        			break;
        		case 119:
        			system("cls");
        			object_list[USER].offset.y -= 1;
        			break;
        		case 32:
        		    system("cls");
        		    temp_cursor = {{object_list[USER].offset.x + 4,
					object_list[USER].offset.y - 1}, 1, 0, 0};
        			generate(temp_cursor, object_list, &pos);
        			break;
			}
		}
		counter++;
		if (counter % 50 == 0) {
			physics(object_list, pos, counter);
		}
		if (counter == 10000) {
			counter = 0;
		}
		print_obj_list(object_list, pos);
	}
	return 0;
}
