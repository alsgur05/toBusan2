#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

// ��������
#define LEN_MIN 15   
#define LEN_MAX 50

//������ ü��
#define STM_MIN 0    
#define STM_MAX 5

//Ȯ��
#define PROB_MIN 10  
#define PROB_MAX 90

//��׷� ����
#define AGGRO_MIN 0  
#define AGGRO_MAX 5

//������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1 
#define ATK_DONGSEOK 2

// ������ �ൿ
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
int c = length - 6;
int z = length - 3;
int m = length - 2;
int m_move;
int status;
int test = 0;
int m_aggro_medium;

//�ʱ�ȭ, �ʱ� ����
void CZ_turn() {
	++turn;
	if (r_move_c <= 100 - p) {
		--c;
		++c_aggro;
		++sum1;
	}
	if (turn % 2 == 1) {
		if (c_aggro > m_aggro) {
			--z;
			++sum2;
		}
		else if (c_aggro < m_aggro) {
			++z;
			++sum2;
		}
		else if(c_aggro == m_aggro) {
			++z;
		}
	} else {
		sum2 = 0;
	}
}
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
void madongseok_status() {
	if (m == z + 1) {
		printf("madongseok move(0 : stay) >> ");
	}
	else {
		printf("madongseok move(0 : stay, 1 : left) >> ");
	}
}
// 1�� <�̵�> ������ (�ù�-����-������)
void madongseok_move() {
	madongseok_status();
	scanf_s("%d", &m_move);
	if (m_move == 1 && m_aggro <= AGGRO_MAX) { //������ �����̰� ��׷�max���� �������
		--m;
		++m_aggro;
		CZ_turn();
		train_start();
		printf("madongseok move %d -> %d (aggro : %d -> %d, stamina : %d)\n\n", m + 1, m, m_aggro - 1, m_aggro, m_stm);
	}
	else if (m_move == 1 && m_aggro == AGGRO_MAX)
	{
		--m;
		CZ_turn();
		train_start();
		printf("madongseok move %d -> %d (aggro : %d, stamina : %d)\n\n", m + 1, m, m_aggro, m_stm);
	}
	else if (m_move == 0 && m_aggro == 0) { //������ ��׷ΰ� 0�̰� �ȿ����ϰ��
		CZ_turn();
		train_start();
		printf("madongseok : stay %d, (aggro : %d, stamina : %d)\n\n", m, m_aggro, m_stm);
	}
	else if (m_move == 0 && m_aggro > 0) { //������ ��׷ΰ� 0���� ũ�� �ȿ����ϰ��
		--m_aggro;
		CZ_turn();
		train_start();
		printf("madongseok : stay %d, (aggro : %d -> %d, stamina : %d)\n\n", m, m_aggro + 1, m_aggro, m_stm);
	}
}



void CZ_move() {  //CZ_turn�� ������ �Լ� �ϳ��� �Ѱ��� ����� �ƴѰ�?
	CZ_turn();
	train_start();
	if (sum1) {
		printf("citizen : %d -> %d (aggro : %d -> %d)\n", c + 1, c, c_aggro - 1, c_aggro);
	}
	else {
		printf("citizen : stay %d\n", c);
	}
	if (turn % 2 == 1) {
		if (c_aggro > m_aggro) {  ///sum2 = 1
			printf("zombie : %d -> %d\n", z + 1, z);
		}
		else if (c_aggro == m_aggro) { //��׷ΰ� ������ �ù������� �̵�
			printf("zombie : %d -> %d\n", z, z - 1);
		}
	} 
	else {
		printf("zomide : stay %d(cannot move)\n", z);
	}
	printf("\n");
}


void CZM_status() {
	if (sum1) {
		printf("citizen move.\n");
	}
	else {
		printf("citizen deos nothing\n");
	}
	printf("zombie attcked nobody.\n");
	printf("madongseok action (0.rest, 1.provoke) >> ");
	scanf_s("%d", &status);
	printf("\n");
	do
	{
		if (status == 0 && m_aggro == 0) {
			if (m_stm == STM_MAX) {
				printf("madongseok rests...\n");
				printf("madongseok: %d (agrro : %d, stamina : %d)\n", m, m_aggro, m_stm);
				++test; //test = 1;
			}
			else {
				++m_stm;
				printf("madongseok rests...\n");
				printf("madongseok: %d (agrro : %d, stamina : %d -> %d)\n", m, m_aggro, m_stm - 1, m_stm);
				++test; //test = 1;
			}

		}
		else if (status == 0 && m_aggro > 0)
		{
			--m_aggro;
			++m_stm;
			printf("madongseok rests...\n");
			printf("madongseok: %d (agrro : %d -> %d, stamina : %d -> %d)\n", m, m_aggro + 1, m_aggro, m_stm - 1, m_stm);
			++test; //test = 1;
		}
		else if (status == 1) {
			m_aggro_medium = m_aggro;
			m_aggro = AGGRO_MAX;
			printf("madongseok provoked zombie...\n");
			printf("madongseok: %d (agrro : %d -> %d, stamina : %d)\n", m, m_aggro_medium, AGGRO_MAX, m_stm);
			++test; //test = 1;
		}
		else {
			test = 0;
		}
	} while (test == 0);

}



int main() {
	srand(1);  //���� ������ 1 ������ �ȵǴ°ſ���...
	//�ʱ�ȭ, �ʱ� ����
	train_first(); //���� ����, ������ stm, Ȯ�� ����
	c = length - 6;
	z = length - 3;
	m = length - 2;
	train_start();
	// 1�� <�̵�> ������ (�ù�-����-������)
	while (1)
	{
		sum1 = 0;
		sum2 = 0;
		CZ_move();
		madongseok_move();
		CZM_status();
	}
	return 0;
}