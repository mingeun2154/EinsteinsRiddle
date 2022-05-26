#ifndef __EINSTEINS_RIDDLE__
#define __EINSTEINS_RIDDLE__

/** House 구조체가 가지는 값들 **/
// Color 
#define BLUE (1)
#define GREEN (2)
#define RED (3)
#define WHITE (4)
#define YELLOW (5)
// nationality 
#define BRIT (6)
#define DANE (7)
#define GERMAN (8)
#define NORWEIGIAN (9)
#define SWEDE (10)
// beverage
#define BEER (11)
#define COFFEE (12)
#define MILK (13)
#define TEA (14)
#define WATER (15)
// cigar brand
#define BLUE_MASTER (16)
#define DUNHILL (17)
#define PALL_MALL (18)
#define PRINCE (19)
#define BLEND (20)
// pet
#define CAT (21)
#define BIRD (22)
#define DOG (23)
#define FISH (24)
#define HORSE (25)

void expand(int index); /** backtracking **/
int promising(int level); /** depth=level인 노드를 탐색할지 말지 결정한다. **/
void printSolution(); /** 정답을 출력한다 **/

const char* printStringColor(int colorNum); // colorNum에 대응되는 문자열을 return한다.
const char* printStringNationality(int nationNum); // nationNum에 대응되는 문자열을 reutnr한다.
const char* printStringBeverage(int beverageNum); // beverageNum에 대응되는 문자열을 return한다.
const char* printStringBrand(int brandNum); // brandNum에 대응되는 문자열을 return한다.
const char* printStringPet(int petNum); // petNum에 대응되는 문자열을 return한다.

#endif