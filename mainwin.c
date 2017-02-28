#include <ncurses.h>
#include <string.h>
typedef struct _win_border_struct {
	chtype	ls, rs, ts, bs,
		tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {
	char name[20];
	int startx, starty;
	int height, width;
	WIN_BORDER border;
}WIN;

void init_con_params(WIN *p_win);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);
void resize_win(WIN *p_win);
int main(int argc, char *argv[])
{
	
	WIN contacts;
	strcpy(contacts.name,  "contacts");
	WIN write;
	strcpy(write.name, "write");
	WIN conversation;
	strcpy(conversation.name, "conversation");
	int ch;

	initscr();
	start_color();
	cbreak;

	keypad(stdscr, TRUE);
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	//init window stuff
	init_con_params(&conversation);
	print_win_params(&conversation);

	attron(COLOR_PAIR(1));
	printw("Press F1 to close");
	refresh();
	attroff(COLOR_PAIR(1));

	create_box(&conversation, TRUE);
	while((ch = getch()) != KEY_F(1))
	{
		resize_win(&conversation);
		refresh();
		switch(ch)
		{case KEY_LEFT:
			create_box(&conversation,FALSE);
			--conversation.startx;
			create_box(&conversation,TRUE);
			break;
		 case KEY_RIGHT:
			create_box(&conversation,FALSE);
			++conversation.startx;
			create_box(&conversation,TRUE);
			break;
		case KEY_UP:
			create_box(&conversation,FALSE);
			--conversation.starty;
			create_box(&conversation,TRUE);
			break;
		case KEY_DOWN:
			create_box(&conversation,FALSE);
			++conversation.starty;
			create_box(&conversation,TRUE);
			break;
		}}
endwin();
return 0;
}
void resize_win(WIN *p_win){
	if (strcmp("conversation",p_win->name) ==0){
		p_win->height = LINES -4;
		p_win->width = COLS -12;
	}
	create_box(p_win,FALSE);
	create_box(p_win,TRUE);


}
void init_con_params(WIN *p_win){
	p_win->height = LINES -4;
	p_win->width = COLS -12;
	p_win->starty = 0;
	p_win->startx = 0;
	
	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '|';
	p_win->border.bs = '|';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';
}

void print_win_params(WIN *p_win)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
			p_win->width,p_win->height);
	refresh();
#endif
}

void create_box(WIN *p_win, bool flag)
{	int i,j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if(flag == TRUE)
	{
		mvaddch(y,x, p_win->border.tl);
		mvaddch(y, x+w, p_win->border.tr);
		mvaddch(y+h, x, p_win->border.bl);
		mvaddch(y+h, x+w, p_win->border.br);
		mvhline(y,x+1, p_win->border.ts, w-1);
		mvhline(y+h, x+1, p_win->border.bs, w-1);
		mvvline(y+1, x, p_win->border.ls, h-1);
		mvvline(y+1, x+w, p_win->border.ls, h-1);
	}
	else
		for(j=y;j <= y + h; ++j)
			for(i = x; i<= x +w;++i)
				mvaddch(j,i,' ');
	refresh();
}














