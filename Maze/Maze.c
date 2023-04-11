#include <stdio.h>
#include <stdlib.h>
#define MAZE_SIZE 12 // 스택의 최대 크기
int back_count = 0, counter = 0;
typedef struct {
	short r;
	short c;
}element;

typedef struct {
	element data[MAZE_SIZE];
	int top;
} StackType;
// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAZE_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
		{'1','1','1','1','1','1','1','1','1','1'},
		{'e','1','0','1','0','0','0','1','0','1'},
		{'0','0','0','1','0','0','0','1','0','1'},
		{'0','1','0','0','0','1','1','0','0','1'},
		{'1','0','0','0','1','0','0','0','0','1'},
		{'1','0','0','0','1','0','0','0','0','1'},
		{'1','0','0','0','0','0','1','0','1','1'},
		{'1','0','1','1','1','0','1','1','0','1'},
		{'1','1','0','0','0','0','0','0','0','x'},
		{'1','1','1','1','1','1','1','1','1','1'}
};

void push_loc(StackType* s, int r, int c) {
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
	else
		counter++;
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c ", maze[r][c]);
		}
		printf("\n");
	}
	printf("-------------------");
}

int main() {
	int r, c;
	StackType s;

	init_stack(&s);
	here = entry;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		maze_print(maze);
		counter = 0;
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		if (counter == 4) {
			back_count++;
		}
		if (is_empty(&s)) {
			printf("\nFail!\n");
			printf("Back count: %d\n", back_count);
			return;
		}
		else 
			here = pop(&s);
	}
	printf("\nSuccess!\n");
	printf("Back count: %d\n", back_count);
	return 0;
}