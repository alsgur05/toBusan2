////������ : Q. ���� ���̸� 15�� ������ ���� ����(C,Z,M�� �����̴� ����)�� 15�� �ϴ°ǰ�?
///*
//Q. ���� ����ϰ��ִ� ����� �̰� �³�
//A. ���� ������ ���� ������(Blame) readme�� ��� ���ص���.
//*/
///*
//Q. <�̵�> ������ ���� ������
//���� ��� - �ù� �̵� - ���� �̵� - ���� ��� - ������ �̵�(�Է�)]�ε� ���� �Ѱ� �³�?
//*/
///*
//Q. <�̵�>, <�ൿ> �ڵ带 �и��ؼ� ������ ���ΰ�?
//*/
///*
//Q.�������� ���Ͽ� move/stay �� rest/provoke �� �� �ϴµ� �Ѵ� 0�� �Է��ϸ� ���Ͽ� ��׷θ� 2�� ���� ��ų���ִ°ǰ�?
//*/
///*
//Q. ctrl + k + c �������� �������� ���� ���°ǰ�?
//A. 20�� ��û �� �Ű� �Ƚᵵ��
//*/
///*
//�ؾ��Ұ�:
//!!repo ���� �ļ� .c�� ���ε�!!
//������ �̵� �߸� ������ �ٽ� ���� > �ذ��
//���� ������ ���� >> m_ation �κ� ZM ���������� (0.rest 1.provoke. 2.hold) �ߴ� ������ �ٸ�
//>>
//������ �ٵ��
//��׷ΰ� ���ų� �������� ������ ���� ������;;(��׷� ����Ⱦ��� ���� �ù������θ� ��������)
//M_move 20�� ������ ����� > �ذ��
//
//
//���� ������ ��׷ΰ� AGGRO_MIN�� �Ѵ� ������ ����
//*/
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <Windows.h>
//#include <time.h>
//
//// ��������
//#define LEN_MIN 15   
//#define LEN_MAX 50
//
////������ ü��
//#define STM_MIN 0    
//#define STM_MAX 5
//
////Ȯ��
//#define PROB_MIN 10  
//#define PROB_MAX 90
//
////��׷� ����
//#define AGGRO_MIN 0  
//#define AGGRO_MAX 5
//
////������ �̵� ����
//#define MOVE_LEFT 1
//#define MOVE_STAY 0
//
//// ������ ���� ���
//#define ATK_NONE 0
//#define ATK_CITIZEN 1 
//#define ATK_DONGSEOK 2
//
//// ������ �ൿ
//#define ACTION_REST 0
//#define ACTION_PROVOKE 1
//#define ACTION_PULL 2	
//
//int length, p, m_stm;
//int train_lenght_exit, madongseok_exit, p_exit = 0;
//char characters[] = { 'C', 'Z', 'M' }; // 0, 1, 2
//int sum1 = 0;
//int sum2 = 0;
//int turn = 0;
//int c_aggro = 1, m_aggro = 1;
//int m_status, m_move;
//int c, z, m;
//int status;
//int x;
//int m_action_while;
//int m_aggro_medium;
//int z_atteck_m, z_atteck_c;
//int zombie_cannotMove = 0;
//int ZM_cannotMove;
//int ZC_cannotMove;
//int m_pull;
//int gameOver;
//
////�ʱ�ȭ, �ʱ� ����
//void train_first() {
//	do
//	{
//		printf("train length(15 ~ 50) >> ");
//		scanf_s("%d", &length);
//	} while (LEN_MAX < length || LEN_MIN > length);
//
//	do
//	{
//		printf("madongseok stamina(0 ~ 5) >> ");
//		scanf_s("%d", &m_stm);
//	} while (STM_MAX < m_stm || STM_MIN > m_stm);
//
//	do
//	{
//		printf("percentile probability 'p' (10 ~ 90) >> ");
//		scanf_s("%d", &p);
//	} while (PROB_MAX < p || PROB_MIN > p);
//	printf("\n");
//	c = length - 6;
//	z = length - 3;
//	m = length - 2;
//}
//void C_turn() {
//	int r_move_c = rand() % 100;
//	if (r_move_c <= 100 - p) {
//		--c;
//		++c_aggro;
//		++sum1;
//	}
//	else { //�ù��� �������ϋ�
//		if (c_aggro == AGGRO_MIN) {
//			return;
//			sum1 = 0;
//		}
//		else {
//			--c_aggro;
//			sum1 = 0;
//		}
//	}
//}
////Z_trun 20�� �Ѵµ�..?
//void Z_turn() { //turn�� ����Ѱ��� �������� move���� ����ϱ� ������ ����Ʈ X
//	if (turn % 2 == 1) {
//		if (m == z + 1 && c_aggro <= m_aggro)
//		{
//			++ZM_cannotMove; //�ʱ�ȭ ������ߵ� >> ����
//		}
//		else if (c == z - 1 && c_aggro > m_aggro)
//		{
//			++ZC_cannotMove;
//		}
//		else
//		{
//			if (m_aggro < c_aggro)
//			{
//				if (z != c + 1) //�ùΰ� �������� ���� ���
//				{
//					--z;
//				}
//			}
//			else
//			{
//				if (z != m - 1)
//				{
//					++z;
//				}
//			}
//		}
//	}
//}
//void CZ_turn() {
//	C_turn();
//	Z_turn();
//}
//
//void character_position() {
//	printf("#");
//	for (int i = 1; i < length - 1; i++) {
//		if (i == c) {
//			printf("%c", characters[0]);
//		}
//		else if (i == z) {
//			printf("%c", characters[1]);
//		}
//		else if (i == m) {
//			printf("%c", characters[2]);
//		}
//		else {
//			printf(" ");
//		}
//	}
//	printf("#\n");
//	for (int i = 0; i < length; i++) {
//		printf("#");
//	}
//}
//void train_start() {
//
//	for (int i = 0; i < length; i++) {
//		printf("#");
//	}
//	printf("\n");
//	character_position();
//	printf("\n\n\n");
//}
//void game_over() {
//	if (c && length == 1)
//	{
//		printf("�ù� Ż��");
//		exit(1);
//	}
//	else if (c == z + 1)
//	{
//		printf("GAME OVER! citizen dead...");
//		++gameOver;
//		exit(1);
//	}
//}
//void m_move_Q() {
//	if (m == z + 1) {
//		printf("madongseok move(0 : stay) >> ");
//	}
//	else {
//		printf("madongseok move(0 : stay, 1 : left) >> ");
//	}
//}
//
//
//// 1�� <�̵�> ������ (�ù�-����-������)
//
//int y = 0;
//
//void m_limited_aggro() {
//	if (m_move == MOVE_LEFT) { // Move
//		if (m_aggro < AGGRO_MAX) {
//			++m_aggro;
//		}
//	}
//	else if (m_move == MOVE_STAY) { // Stay
//		if (m_aggro > AGGRO_MIN) {
//			--m_aggro;
//		}
//	}
//}
//void C_move() {
//	if (sum1 == 1 && c_aggro < AGGRO_MAX) {
//		printf("citizen : %d -> %d (aggro : %d -> %d)\n", c + 1, c, c_aggro - 1, c_aggro);
//	}
//	else if (sum1 == 1 && c_aggro == AGGRO_MAX)
//	{
//		printf("citizen : %d -> %d (aggro : %d)\n", c + 1, c, c_aggro);
//	}
//	else { //sum == 0
//		printf("citizen : stay %d (aggro : %d -> %d)\n", c, c_aggro + 1, c_aggro);
//	}
//}
//void Z_move() { //����Ʈ �κ��̶� �����ϸ� ����
//	if (m_pull == 1)
//	{
//		printf("zombie stay %d(from madongseok pull)", z);
//	}
//	else
//	{
//		if (turn % 2 == 1)
//		{
//			if (ZM_cannotMove == 1)
//			{
//				printf("zombie stay %d(right madongseok)\n", z);
//			}
//			else if (ZC_cannotMove == 1)
//			{
//				printf("zombie stay %d(left citizen)\n", z);
//			}
//			else
//			{
//				if (c_aggro > m_aggro)
//				{
//					printf("zombie : %d -> %d\n", z, z - 1);
//				}
//				else
//				{
//					printf("zombie : %d -> %d\n", z - 1, z);
//				}
//			}
//		}
//		else
//		{
//			printf("zombie stay %d(form turn)", z);
//		}
//		printf("\n");
//	}
//
//}
//void CZ_move() { //����Ʈ �κ�
//	train_start();
//	C_move();
//	Z_move();
//}
//
//void M_move() {
//	do
//	{
//		m_move_Q();
//		scanf_s("%d", &m_move);
//		if (m_move == MOVE_LEFT)
//		{
//			++y;
//			if (m_aggro == AGGRO_MAX) //AGGRO_MAX�϶� �����̸� ��׷� �״��
//			{
//				printf("madongseok move %d -> %d (aggro : %d, stamina : %d)\n", m + 1, m, m_aggro, m_stm);
//			}
//			else if (m_aggro == AGGRO_MIN)
//			{
//				printf("madongseok move %d -> %d (aggro : %d, stamina : %d)\n", m + 1, m, m_aggro, m_stm);
//			}
//			else
//			{
//				++m_aggro;
//				printf("madongseok move %d -> %d (aggro : %d -> %d, stamina : %d)\n", m + 1, m, m_aggro - 1, m_aggro, m_stm);
//			}
//		}
//		else if (m_move == MOVE_STAY)
//		{
//			++y;
//			if (m_aggro == AGGRO_MAX) //AGGRO_MAX�϶� �����̸� ��׷� �״��
//			{
//				printf("madongseok stay %d (aggro : %d, stamina : %d)\n", m, m_aggro, m_stm);
//			}
//			else if (m_aggro == AGGRO_MIN)
//			{
//				printf("madongseok stay %d (aggro : %d, stamina : %d)\n", m, m_aggro, m_stm);
//			}
//			/*else if (m_aggro == 1)
//			{
//				--m_aggro;
//				printf("madongseok stay %d (aggro : %d -> %d, stamina : %d)\n", m, m_aggro + 1, m_aggro, m_stm);
//			}*/
//			else
//			{
//				--m_aggro;
//				printf("madongseok stay %d (aggro : %d -> %d, stamina : %d)\n", m, m_aggro + 1, m_aggro, m_stm);
//			}
//		}
//		else
//		{
//			y = 0;
//		}
//		
//	} while (y == 0);
//}
//
//void M_moveAndTrain() {
//	M_move();
//	train_start();
//}
//
//void m_action_Q() {
//	do
//	{
//		if (m == z + 1) //mz �����Ұ��
//		{
//			++m_action_while;
//			printf("madongseok action (0.rest, 1.provoke, 2. pull)");
//			scanf_s("%d", &status);
//		}
//		else //mz �������Ұ��
//		{
//			++m_action_while;
//			printf("madongseok action (0.rest, 1.provoke)");
//			scanf_s("%d", &status);
//		}
//	} while (m_action_while == 0);
//}
//
//void m_action() { //m_aggro ���� ��׷δ� ����  >>  ���� M_move���� �ٷ������
//	m_action_Q();
//	if (m == z + 1) // ������ ���, status�� 0,1,2�� ��� �ۿ� ����
//	{
//		if (status == ACTION_REST || status == ACTION_PROVOKE || status == ACTION_PULL)
//		{
//			printf("\n");
//			if (status == ACTION_REST) //stay
//			{
//				--m_stm;
//				--m_aggro;
//				if (m_stm > STM_MIN) //AGGRO_MAX�� �ٸ� �Լ����� �ٷ�
//				{//m_stm�� ������ �پ����
//					printf("madongseok rests...\nmadongseok : %d (aggro : %d -> %d, stamina : %d -> %d)\n\n\n", m, m_aggro + 1, m_aggro, m_stm + 1, m_stm);
//				}
//				else {
//					printf("madongseok killed by zombie...\ngame over\n\n\n");
//					game_over();
//				}
//			}
//			else if (status == ACTION_PROVOKE)
//			{
//				--m_stm;
//				if (m_stm == STM_MAX) //AGGRO_MAX�� �ٸ� �Լ����� �ٷ�
//				{
//					printf("madongseok provoked zombie...\nmadongseok %d (aaggro : %d -> %d, stamina : %d -> %d)\n\n\n", m, m_aggro_medium, m_aggro, m_stm + 1, m_stm);
//				}
//				else {
//					printf("madongseok provoked zombie...\nmadongseok : %d (aggro : %d -> %d, stamina : %d)\n\n\n", m, m_aggro + 1, AGGRO_MAX, m_stm);
//				}
//			}
//			else //status == ACTION_PULL
//			{
//				--m_stm;
//				m_aggro + 2;
//				int r_pull_m = rand() % 100;
//				if (r_pull_m <= 100 - p)
//				{
//					++m_pull;
//					printf("madongseok pulled zombie... Next turn, it's can't move\nmadongseok : %d (aggro : %d -> %d, stamina : %d -> %d)\n\n\n", m, m_aggro - 2, m_aggro, m_stm + 1, m_stm);
//				}
//				else
//				{
//					printf("madongseok failed to pull zombie\nmadongseok : %d (aggro : %d -> %d, stamina: %d -> %d)\n\n\n", m, m_aggro - 2, m_aggro, m_stm + 1, m_stm);
//				}
//			}
//		}
//	}
//	else //�������� �������
//	{
//		if (status == ACTION_REST)
//		{
//
//		}
//		else if (status == ACTION_PROVOKE)
//		{
//
//		}
//		else //status == ACTION_PULL
//		{
//
//		}
//	}
//}
//
//void CZM_status() {
//	if (sum1) {
//		printf("citizen move.\n");
//	}
//	else {
//		printf("citizen deos nothing\n");
//	}
//	if (c == z - 1) {
//		printf("zombie attcked citizen.\n");
//	}
//	else if (m == z + 1) {
//		printf("zombie attcked madongseok");
//	}
//	else if (c == z - 1 && m == z + 1)
//	{
//		printf("zombie atteck madongseok (aggro : %d vs %d, madongseok stamina : %d -> %d)\n", c_aggro, m_aggro, m_stm + 1, m_stm);
//	}
//	else {
//		printf("zombie attcked nobody");
//	}
//	printf("\n");
//	m_action();
//}
//
//
//
//void Z_atteck() {
//	if (z == m + 1)
//	{
//		++z_atteck_m;
//		if (z_atteck_m == 1)
//		{
//			--m_stm;
//		}
//	}
//	else if (z == c - 1)
//	{
//		++z_atteck_c;
//		if (z_atteck_c == 1)
//		{
//			game_over();
//		}
//	}
//}
//
//
//
//int main() {
//	srand((unsigned int)time(NULL));  //���� ������ 1 ������ �ȵǴ°ſ���...
//	//�ʱ�ȭ, �ʱ� ����
//	train_first(); //���� ����, ������ stm, Ȯ�� ����
//	train_start();
//	// 1�� <�̵�> ������ (�ù�-����-������)
//	while (gameOver == 0)
//	{
//		x = 0;
//		sum1 = 0;
//		++turn;
//		ZM_cannotMove = 0;
//		ZC_cannotMove = 0;
//		m_action_while = 0;
//		m_pull = 0;
//		gameOver = 0;
//		printf("turn : %d\n", turn); //�׽�Ʈ
//		CZ_turn(); //C_turn > Z_turn
//		CZ_move(); //train_start > C_move > Z_move
//		game_over();
//		M_moveAndTrain();
//		Z_atteck();
//		CZM_status(); //m_action
//	}
//	return 0;
//}