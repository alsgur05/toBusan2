#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

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

int length, p, m_stm;
int train_lenght_exit, madongseok_exit, p_exit = 0;
char characters[] = { 'C', 'Z', 'M' }; // 0, 1, 2
int sum1 = 0;
int sum2 = 0;
int turn = 0;
int c_aggro;
int m_aggro;
int m_status;
int r_move_c = rand() % 100;
int r_move_z = rand() % 100;
int c = length - 6;
int z = length - 3;
int m = length - 2;
int m_move;

//초기화, 초기 상태
void train_first() {
	do
	{
		printf("traing length(15 ~ 50) >> ");
		scanf_s("%d", &length);
	} while (LEN_MAX < length || LEN_MIN > length);

	do
	{
		printf("madongseok stamina(0 ~ 5) >> ");
		scanf_s("%d", &m_stm);
	} while (STM_MAX < m_stm || STM_MIN > m_stm);

	do
	{
		printf("percentile probability 'p' (10 ~ 90) >> ");
		scanf_s("%d", &p);
	} while (PROB_MAX < p || PROB_MIN > p);
	printf("\n");
}
//void train_length() {
//	while (train_lenght_exit != 1)
//	{
//		printf("train length(15 ~ 50) >> ");
//		scanf_s("%d", &length);
//		if (LEN_MAX < length || LEN_MIN > length) {
//			continue;
//		}
//		else
//		{
//			++train_lenght_exit;
//		}
//	}
//
//}
//void madongseok_stamina() {
//	while (madongseok_exit != 1)
//	{
//		printf("madongseok stamina(0 ~ 5) >> ");
//		scanf_s("%d", &madongseok_stm);
//		if (STM_MAX < madongseok_stm || STM_MIN > madongseok_stm) {
//			continue;
//		}
//		else
//		{
//			++madongseok_exit;
//		}
//	}
//}
//void percent() {
//	while (p_exit != 1)
//	{
//		printf("percentile probability 'p' (10 ~ 90) >> ");
//		scanf_s("%d", &p);
//		if (PROB_MAX < p || PROB_MIN > p) {
//			continue;
//		}
//		else
//		{
//			++p_exit;
//		}
//	}
//} //열차 길이, 


void character_start() {
	printf("#");
	for (int i = 1; i < length - 1; i++) {
		if (i == c) {
			printf("%c", characters[0]);
		}
		else if (i == z) {
			printf("%c", characters[1]);
		}
		else if (i == m) {
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
	for (int i = 0; i < 3; i++)
	{
		printf("\n");
	}
}

// 1턴 <이동> 페이즈 (시민-좀비-마동석)
void madongseok_move() {
	if (m == z + 1) {
		printf("madongseok move(0 : stay) >> ");
	}
	else {
		printf("madongseok move(0 : stay, 1 : left) >> ");
	}
	scanf_s("%d", &m_move);
	if (m_move == 1 && m_aggro <= AGGRO_MAX) { //마동석 움직이고 어그로max보다 작을경우
		--m;
		++m_aggro;
		train_start();
		printf("madongseok move %d -> %d (aggro : %d -> %d, stamina : %d)\n", m + 1, m, m_aggro - 1, m_aggro, m_stm);
	}
	else if (m_move == 1)
	{

	}
	else if (m_move == 0 && m_aggro == 0) { //마동석 어그로가 0이고 안움직일경우
		train_start();
		printf("madongseok : stay %d, (aggro : %d, stamina : %d)\n", m, m_aggro, m_stm);
	}
	else if (m_move == 0 && m_aggro > 0) { //마동석 어그로가 0보다 크고 안움직일경우
		--m_aggro;
		train_start();
		printf("madongseok : stay %d, (aggro : %d -> %d, stamina : %d)\n", m, m_aggro, m_aggro - 1, m_stm);
	}
	else { //AGGRO_MAX가 최대일경우
		--m; //?
	}
}

void CZ_turn() {
	++turn;
	if (r_move_c <= 100 - p) {
		--c;
		++c_aggro;
		++sum1;
	}
	if (turn % 2 == 1) {
		if (r_move_z <= p || c_aggro > m_aggro) {
			--z;
			++sum2;
		}
		else if (r_move_z <= p || c_aggro < m_aggro) {
			++z;
			++sum2;
		}
	}
}

void CZ_move() {  //CZ_turn을 넣으면 함수 하나당 한개의 기능이 아닌가?
	CZ_turn();
	train_start();
	if (sum1) {
		printf("citizen : %d -> %d (aggro : %d -> %d)\n", c + 1, c, c_aggro - 1, c_aggro);
	}
	else {
		printf("citizen : stay %d\n", c);
	}
	if (turn % 2 == 1) {
		if (sum2 || c_aggro > m_aggro) {  ///sum2 = 1
			printf("zombie : %d -> %d\n", z + 1, z);
		}
		else if (sum2 || c_aggro < m_aggro) {
			printf("zombie : %d -> %d\n", z, z - 1);
		}
		else {
			printf("zomdie : stay %d\n", z);
		}
	}
	if (turn % 2 == 0) {
		printf("zomide : stay %d(cannot move)\n", z);
	}
	printf("\n");
}

void status() {
	if (sum1)
	{
		printf("citizen move.\n");
	}
	else
	{
		printf("citizen deos nothing\n");
	}
	printf("zombie attcked nobody.\n");
	printf("madongseok action (0.rest, 1.provoke) >> ");
	scanf("%d", &status);
	if (status == 0)
	{
		--m_aggro;
		++m_stm;
		printf("madongseok rests...\n");
		printf("madongseok: %d (agrro : %d -> %d, stamina : %d -> %d", m, m_aggro + 1, m_aggro, m_stm - 1, m_stm);
	}
	else
	{
		printf("madongseok provoked zombie...");
		printf("madongseok: %d (agrro : %d -> %d, stamina : %d", m, m_aggro, AGGRO_MAX);
	}
}



int main() {
	srand(1);  //ㅅㅂ 스렌드 1 넣으면 안되는거였노...
	//초기화, 초기 상태
	train_first(); //열차 길이, 마동석 stm, 확률 설정
	c = length - 6;
	z = length - 3;
	m = length - 2;
	train_start();
	// 1턴 <이동> 페이즈 (시민-좀비-마동석)
	while (1)
	{
		CZ_move();
		madongseok_move();
	}
	return 0;
}