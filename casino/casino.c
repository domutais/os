#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BET_AMOUNT 150
#define START_AMOUNT 5000

#define LVL1_MULTIPLIER 1.307
#define LVL2_MULTIPLIER 1.7082
#define LVL3_MULTIPLIER 2.2327
#define LVL4_MULTIPLIER 2.9181
#define LVL5_MULTIPLIER 3.8140
#define LVL6_MULTIPLIER 5.0
#define LOSE_MULTIPLIER -2.5525

void help();
int game();

int credit = START_AMOUNT;

int main() {
	help();
	
	int cmd;

	if (credit < BET_AMOUNT) {
		printf("GAME OVER: you have run out of money and can't make any bets.\n");
		exit(0);
	}

	while(1) {
		printf("\nCredits: $%d. Bet price: $%d\n", credit, BET_AMOUNT);
		printf("> ");
		scanf("%d", &cmd);

		if (cmd == 0) exit(0);

		else if (cmd == 1) help();

		else if (cmd == 2) {
			cmd -= BET_AMOUNT;
			credit += game(0);
		}

		else if (cmd == 252525) {
			printf("Welcome home, boss! What's the combination, eh? - ");
			int tmp;
			scanf("%d", &tmp);
			credit += game(tmp);
		}

		else printf("%d is not a valid command", cmd);

		if (credit == 2147483647) { 
			printf(" You are an absolute winner! Good luck and see you next time!\n");
			exit(0);
		}
	}

	return 0;
}

int game(int combination) {
	srand(time(NULL));
	combination = combination ? combination : rand() % 512;

	credit -= BET_AMOUNT;
	int prize = BET_AMOUNT;
	double multiplier = 0;
	
	printf("Made a bet. You rolled: %d %d %d\n", combination / 64, (combination / 8) % 8, combination % 8);
	
	if (combination == 438) multiplier = LOSE_MULTIPLIER;
	else if (combination == 511) multiplier = LVL6_MULTIPLIER;
	else if (combination >= 504 && combination <= 511) multiplier = LVL5_MULTIPLIER;
	else if (combination >= 448 && combination <= 511) multiplier = LVL4_MULTIPLIER;
	else if (combination >= 360 && combination <= 367) multiplier = LVL4_MULTIPLIER;
	else if (combination >= 320 && combination <= 383) multiplier = LVL3_MULTIPLIER;
	else if (combination == 292) multiplier = LVL3_MULTIPLIER;
	else if (combination == 219) multiplier = LVL2_MULTIPLIER;
	else if (combination == 146) multiplier = LVL2_MULTIPLIER;
	else if (combination == 73) multiplier = LVL1_MULTIPLIER;
	else if (combination == 0) multiplier = LVL1_MULTIPLIER;
	
	prize *= multiplier;

	if (multiplier == 5.0) {
		printf("JACKPOT! YOU WIN!");
		return 2147483647 - credit;
	}
	
	if (multiplier == 0) printf("You won nothing. Maybe try again?\n");
	else if (multiplier > 0) printf("You won $%d. Congratulations!\n", prize);
	else printf("Well, that was an unlucky one! You lost $%d!\n", -prize);
	printf("\n");
	
	return prize;

}

void help() {
	printf("\n == ONE-ARMED BANDIT == \n\n");
	
	printf("Commands:\n");
	printf("1 - shows this message\n");
	printf("2 - make a bet ($%d) and start the game\n", BET_AMOUNT);
	printf("0 - exit\n\n");

	printf("Rules:\n");
	printf("At the start of the game you are given $%d.\nTo start, type in '+'. Each game costs $%d. Then, a random combination of three numbers 0-7 will be chosen. Depending on the combination, you may win a certain amount of money (see table below).\n", START_AMOUNT, BET_AMOUNT);
	printf("When you don't have enough money to continue, you lose and the game ends.\n");
	printf("When you roll '7 7 7', it's a jackpot and you win the game.\n\n");
}

