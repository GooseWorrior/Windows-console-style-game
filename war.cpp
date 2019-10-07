#include<iostream>
#include<windows.h>
#include <conio.h>
using namespace std;

struct pos {
	int x;
	int y;
};
struct cursor {
	pos offset;
	int height;
	int code;
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

void physics(cursor obj_list[1000], int pos) {
	for (int i = 0; i < pos; i++) {
		switch(obj_list[i].code) {
   	     case 0:
   	     	obj_list[i].offset.y -= 1;
   	    break;
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
        }	
	}
}
// 0: bullet 1: plane
int main() {
	const int USER = 0;
	int counter = 0;
	int pos = 0;
    cursor object_list [1000];
	cursor temp_cursor = {{0, 0}, 4, 1};
	 print_shape(shape_1, temp_cursor);
	 generate(temp_cursor, object_list, &pos);
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
					object_list[USER].offset.y - 1}, 1, 0};
        			generate(temp_cursor, object_list, &pos);
        			break;
			}
		}
		counter++;
		if (counter == 100) {
			physics(object_list, pos);
			counter == 0;
		}
		print_obj_list(object_list, pos);
	}
	return 0;
}
