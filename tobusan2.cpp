//문제점 : 좀비가 짝수턴에 못움직여야햐는데 움직이고 있음 >> 해결완
//문제점 : p가 60~70일때 첫턴에서 마동석쪽으로 움직여서 M이 사라짐 >> ZM이 인접할떈 못움직이게 만들자 >> 해결완
//문제점 : 마동석 스테미나가 5를 넘기는 문제가 생김, 못넘기게 만들자 
//문제점 : 

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

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
int turn = 0;
int c_aggro = 1, m_aggro = 1;
int m_status, m_move;
int r_move_c = rand() % 100;
int c, z, m;
int status;
int x = 0;
int m_aggro_medium;
int atteck = 0;

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
	c = length - 6;
	z = length - 3;
	m = length - 2;
}
void C_turn() {
	if (r_move_c <= 100 - p) { //시민이 움직일떄
		/*if (c_aggro <  AGGRO_MAX) {
			++c_aggro;
			--c;
			++sum1;
		}
		else {
			--c;
			++sum1;
		}*/
		--c;
		++sum1;
	}
	else { //시민이 못움직일떄
		if (c_aggro == AGGRO_MIN) {
			return;
			sum1 = 0;
		}
		else {
			--c_aggro;
			sum1 = 0;
		}
	}
}
void Z_turn() {
	if (turn % 2 == 1) {
		if (z + 1 == m || z == c + 1) { //좀비가 시민 또는 마동석과 인접할때 못움직임
			return;
		}
		if (c_aggro > m_aggro) {
			--z;
		}
		else if (c_aggro < m_aggro) {
			++z;
		}
		else if (c_aggro == m_aggro) {
			++z;
		}
	}
}

void CZ_turn() {
	C_turn();
	Z_turn();
}

void character_position() {
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
	printf("#\n");
	for (int i = 0; i < length; i++) {
		printf("#");
	}
}
void train_start() {
	printf("turn : %d\n", turn);
	for (int i = 0; i < length; i++) {
		printf("#");
	}
	printf("\n");
	character_position();
	printf("\n\n\n");
}


void madongseok_status() {
	if (m == z + 1) {
		printf("madongseok move(0 : stay) >> ");
	}
	else {
		printf("madongseok move(0 : stay, 1 : left) >> ");
	}
}
// 1턴 <이동> 페이즈 (시민-좀비-마동석)
void madongseok_move() {
	madongseok_status();
	scanf_s("%d", &m_move);
	if (m_move == MOVE_LEFT && m_aggro < AGGRO_MAX) { //마동석 움직이고 어그로max보다 작을경우
		--m;
		++m_aggro;
		train_start();
		printf("madongseok move %d -> %d (aggro : %d -> %d, stamina : %d)\n\n", m + 1, m, m_aggro - 1, m_aggro, m_stm);
	}
	else if (m_move == MOVE_LEFT && m_aggro == AGGRO_MAX) //마동석 움직이고 어그로 max일 경우
	{
		--m;
		train_start();
		printf("madongseok move %d -> %d (aggro : %d, stamina : %d)\n\n", m + 1, m, m_aggro, m_stm);
	}
	else if (m_move == MOVE_STAY && m_aggro == AGGRO_MIN) { //마동석 안움직이고 어그로가 0 일경우
		train_start();
		printf("madongseok : stay %d, (aggro : %d, stamina : %d)\n\n", m, m_aggro, m_stm);
	}
	else if (m_move == MOVE_STAY && m_aggro > AGGRO_MIN) { //마동석 안움직이고 어그로가 0보다 큰경우
		--m_aggro;
		train_start();
		printf("madongseok : stay %d, (aggro : %d -> %d, stamina : %d)\n\n", m, m_aggro + 1, m_aggro, m_stm);
	}
}


void C_move() {
	if (sum1 == 1 && c_aggro < AGGRO_MAX) {
		++c_aggro;
		printf("citizen : %d -> %d (aggro : %d -> %d)\n", c + 1, c, c_aggro - 1, c_aggro);
	}
	else if (sum1 == 1 && c_aggro == AGGRO_MAX)
	{
		printf("citizen : %d -> %d (aggro : %d)\n", c + 1, c, c_aggro);
	}
	else { //sum == 0
		printf("citizen : stay %d\n", c);
	}
}
void Z_move() {
	if (turn % 2 == 1) {
		if (c_aggro > m_aggro) { //시민 어그로가 더 크면
			printf("zombie : %d -> %d\n", z + 1, z);
		}
		else if (c_aggro <= m_aggro) {//마동석 어그로가 시민과 같거나 크면
			if (z + 1 == m) {
				printf("zombie stay %d", z);
			} else {
				printf("zombie : %d -> %d\n", z - 1, z);
			}
		}
	}
	else {
		printf("zomide : stay %d(cannot move)\n", z);
	}
	printf("\n");
}
void CZ_move() {
	train_start();
	C_move();
	Z_move();
}

void m_action() {
	while (x == 0)
	{
		printf("madongseok action (0.rest, 1.provoke) >> ");
		scanf_s("%d", &status);

		if (status == ACTION_REST || status == ACTION_PROVOKE)
		{
			printf("\n");
			++x; //x = 1; > while문 빠져나감
			if (status == ACTION_REST && m_aggro == 0) { //m_aggro 1부터 시작인데? >> 이 코드 실행 안되고 있었음
				if (m_stm == STM_MAX) { //마동석 stm이 5를 넘지 못하게 하는 부분
					printf("madongseok rests...\nmadongseok: %d (agrro : %d, stamina : %d)\n", m, m_aggro, m_stm);
				}
				else {
					++m_stm;
					printf("madongseok rests...\nmadongseok: %d (agrro : %d, stamina : %d -> %d)\n", m, m_aggro, m_stm - 1, m_stm);
				}

			}
			else if (status == ACTION_REST && m_aggro > 0)
			{
				--m_aggro;
				if (m_stm < STM_MAX) {
					++m_stm;
					printf("madongseok rests...\nmadongseok: %d (agrro : %d -> %d, stamina : %d -> %d)\n", m, m_aggro + 1, m_aggro, m_stm - 1, m_stm);
				}
				else
				{
					printf("madongseok rests...\nmadongseok: %d (aggro : %d -> %d, stamina : %d", m, m_aggro + 1, m_aggro, m_stm);
				}
			}
			else if (status == ACTION_PROVOKE) {
				m_aggro_medium = m_aggro;
				m_aggro = AGGRO_MAX;
				printf("madongseok provoked zombie...\nmadongseok: %d (agrro : %d -> %d, stamina : %d)\n", m, m_aggro_medium, AGGRO_MAX, m_stm);
			}
		}
		else {
			x = 0;
		}
	}
}
void CZM_status() {
	if (sum1) {
		printf("citizen move.\n");
	}
	else {
		printf("citizen deos nothing\n");
	}
	if (c == z - 1) {
		printf("zombie attcked citizen.\n");
	}
	else if (m == z + 1) {
		printf("zombie attcked madongseok");
	}
	else {
		printf("zombie attcked nobody");
	}
	printf("\n");
	m_action();
}



int main() {
	srand((unsigned int)time(NULL));  //ㅅㅂ 스렌드 1 넣으면 안되는거였노...
	//초기화, 초기 상태
	train_first(); //열차 길이, 마동석 stm, 확률 설정
	train_start();
	// 1턴 <이동> 페이즈 (시민-좀비-마동석)
	while (1)
	{
		sum1 = 0;
		++turn;
		CZ_turn();
		CZ_move();
		madongseok_move();
		CZM_status();
	}
	return 0;
}