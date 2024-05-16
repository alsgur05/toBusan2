#include <stdio.h>
#include <stdlib.h>

// 기차길이
#define LEN_MIN 15   
#define LEN_MAX 50

//마동석 체력
#define STM_MIN 0    
#define STM_MAX 5

//확률
#define PROB_MIN 10  
#define PROB_MAX 90

//어그로 범위
#define AGGRO_MIN 0  
#define AGGRO_MAX 5

//마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1 
#define ATK_DONGSEOK 2

// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2


int length, 
	p, 
	madongseok_stm;
int train_lenght_exit,
	madongseok_exit,
	p_exit = 0;
char characters[] = { 'C', 'Z', 'M' }; // 0, 1, 2
int sum1 = 0;
int sum2 = 0;
int r_move_c = rand() % 100;
int c = length - 7;
int z = length - 4;
int m = length - 3;

void train_length() {
	while (train_lenght_exit != 1)
	{
		printf("train length(15 ~ 50) >> ");
		scanf_s("%d", &length);
		if (LEN_MAX < length || LEN_MIN > length) {
			continue;
		}
		else
		{
			++train_lenght_exit;
		}
	}
	
}
void madongseok_stamina() {
	while (madongseok_exit != 1)
	{
		printf("madongseok stamina(0 ~ 5) >> ");
		scanf_s("%d", &madongseok_stm);
		if (STM_MAX < madongseok_stm || STM_MIN > madongseok_stm) {
			continue;
		}
		else
		{
			++madongseok_exit;
		}
	}
}
void percent() {
	while (p_exit != 1)
	{
		printf("percentile probability 'p' (10 ~ 90) >> ");
		scanf_s("%d", &p);
		if (PROB_MAX < p || PROB_MIN > p) {
			continue;
		}
		else
		{
			++p_exit;
		}
	}
}


void character_start() {
	printf("#");
	for (int i = 1; i < length - 1; i++) {
		if (i == length - 6) {
			printf("%c", characters[0]);
		}
		else if (i == length - 3) {
			printf("%c", characters[1]);
		}
		else if (i == length - 2) {
			printf("%c", characters[2]);
		}
		else {
			printf(" ");
		}
	}
	printf("#");
	printf("\n");
	for (int i = 0; i < length; i++) {
		printf("#");
	}
}
void train_start() {
	for (int i = 0; i < length; i++) {
		printf("#");
	}
	printf("\n");
	character_start(); //
}



//void character_move() {
//	if (r_move_c <= 100 - p) {
//		--c;
//		++sum1;
//	}
//	else {
//		if (sum1 == 0) {
//			sum1 += 0;
//		}
//	}
//	int r_move_z = rand() % 100;
//	if (turn % 2 == 1) {
//		if (r_move_z <= p) {
//			--z;
//			++sum2;
//		}
//	}
//	else {
//		if (sum2 == 0) {
//			sum2 += 0;
//		}
//	}
//}  //나중에 다시

int main() {
	//초기화, 초기 상태
	train_length();
	madongseok_stamina();
	percent();
	train_start();
	// 1턴 <이동> 페이즈 (시민-좀비-마동석)

	
	return 0;
}