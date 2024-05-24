////문제점 : Q. 열차 길이를 15로 했을때 안의 길이(C,Z,M이 움직이는 공간)를 15로 하는건가?
///*
//Q. 깃헙 기록하고있는 방식이 이게 맞나
//A. 깃헙 서버에 남기 때문에(Blame) readme에 기록 안해도됨.
//*/
///*
//Q. <이동> 페이즈 진행 순서가
//상태 출력 - 시민 이동 - 좀비 이동 - 상태 출력 - 마동석 이동(입력)]인데 내가 한게 맞나?
//*/
///*
//Q. <이동>, <행동> 코드를 분리해서 만들라는 말인가?
//*/
///*
//Q.마동석이 한턴에 move/stay 와 rest/provoke 를 다 하는데 둘다 0을 입력하면 한턴에 어그로를 2를 감소 시킬수있는건가?
//*/
///*
//Q. ctrl + k + c 눌렀을때 기준으로 줄을 세는건가?
//A. 20줄 엄청 막 신경 안써도됨
//*/
///*
//해야할거:
//!!repo 새로 파서 .c로 업로드!!
//마동석 이동 잘못 적으면 다시 질문 > 해결완
//좀비 마동석 공격 >> m_ation 부분 ZM 인접했을때 (0.rest 1.provoke. 2.hold) 뜨는 문구가 다름
//>>
//마동석 붙들기
//어그로가 같거나 마동석이 높을때 좀비가 도망감;;(어그로 상관안쓰고 좀비가 시민쪽으로만 가고있음)
//M_move 20줄 안으로 만들기 > 해결완
//
//
//현재 마동석 어그로가 AGGRO_MIN을 넘는 문제가 생김
//*/
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <Windows.h>
//#include <time.h>
//
//// 기차길이
//#define LEN_MIN 15   
//#define LEN_MAX 50
//
////마동석 체력
//#define STM_MIN 0    
//#define STM_MAX 5
//
////확률
//#define PROB_MIN 10  
//#define PROB_MAX 90
//
////어그로 범위
//#define AGGRO_MIN 0  
//#define AGGRO_MAX 5
//
////마동석 이동 방향
//#define MOVE_LEFT 1
//#define MOVE_STAY 0
//
//// 좀비의 공격 대상
//#define ATK_NONE 0
//#define ATK_CITIZEN 1 
//#define ATK_DONGSEOK 2
//
//// 마동석 행동
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
////초기화, 초기 상태
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
//	else { //시민이 못움직일떄
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
////Z_trun 20줄 넘는데..?
//void Z_turn() { //turn을 계산한것을 바탕으로 move에서 출력하기 때문에 프린트 X
//	if (turn % 2 == 1) {
//		if (m == z + 1 && c_aggro <= m_aggro)
//		{
//			++ZM_cannotMove; //초기화 시켜줘야됨 >> 해줌
//		}
//		else if (c == z - 1 && c_aggro > m_aggro)
//		{
//			++ZC_cannotMove;
//		}
//		else
//		{
//			if (m_aggro < c_aggro)
//			{
//				if (z != c + 1) //시민과 인접하지 않은 경우
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
//		printf("시민 탈출");
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
//// 1턴 <이동> 페이즈 (시민-좀비-마동석)
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
//void Z_move() { //프린트 부분이라 생각하면 편함
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
//void CZ_move() { //프린트 부분
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
//			if (m_aggro == AGGRO_MAX) //AGGRO_MAX일때 움직이면 어그로 그대로
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
//			if (m_aggro == AGGRO_MAX) //AGGRO_MAX일때 움직이면 어그로 그대로
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
//		if (m == z + 1) //mz 인접할경우
//		{
//			++m_action_while;
//			printf("madongseok action (0.rest, 1.provoke, 2. pull)");
//			scanf_s("%d", &status);
//		}
//		else //mz 인접안할경우
//		{
//			++m_action_while;
//			printf("madongseok action (0.rest, 1.provoke)");
//			scanf_s("%d", &status);
//		}
//	} while (m_action_while == 0);
//}
//
//void m_action() { //m_aggro 만들어서 어그로는 따로  >>  현재 M_move에서 다루고있음
//	m_action_Q();
//	if (m == z + 1) // 인접할 경우, status가 0,1,2인 경우 밖에 없음
//	{
//		if (status == ACTION_REST || status == ACTION_PROVOKE || status == ACTION_PULL)
//		{
//			printf("\n");
//			if (status == ACTION_REST) //stay
//			{
//				--m_stm;
//				--m_aggro;
//				if (m_stm > STM_MIN) //AGGRO_MAX는 다른 함수에서 다뤄
//				{//m_stm이 무조건 줄어야함
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
//				if (m_stm == STM_MAX) //AGGRO_MAX는 다른 함수에서 다뤄
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
//	else //인접하지 않을경우
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
//	srand((unsigned int)time(NULL));  //ㅅㅂ 스렌드 1 넣으면 안되는거였노...
//	//초기화, 초기 상태
//	train_first(); //열차 길이, 마동석 stm, 확률 설정
//	train_start();
//	// 1턴 <이동> 페이즈 (시민-좀비-마동석)
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
//		printf("turn : %d\n", turn); //테스트
//		CZ_turn(); //C_turn > Z_turn
//		CZ_move(); //train_start > C_move > Z_move
//		game_over();
//		M_moveAndTrain();
//		Z_atteck();
//		CZM_status(); //m_action
//	}
//	return 0;
//}