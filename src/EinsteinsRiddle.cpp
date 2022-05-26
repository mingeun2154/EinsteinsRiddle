#include <vector>
#include <iostream>
#include "EinsteinsRiddle.h"

using namespace std;

/** ---------------------------------------------------------- **/
int totalNode=0; /** 방문 노드 개수 **/
int solutionCount = 0; /** 임시 변수 **/

int colors[]={BLUE, GREEN, RED, WHITE, YELLOW};
int nationalities[]={BRIT, DANE, GERMAN, NORWEIGIAN, SWEDE};
int beverages[]={BEER, COFFEE, MILK, TEA, WATER};
int brands[]={BLUE_MASTER, DUNHILL, PALL_MALL, PRINCE, BLEND};
int pets[]={CAT, BIRD, DOG, FISH, HORSE};

/** 중복되는 특징을 없애기 위한 배열 **/
int usedColor[]={0,0,0,0,0};
int usedNationality[]={0,0,0,0,0};
int usedBeverage[]={0,0,0,0,0};
int usedBrand[]={0,0,0,0,0};
int usedPet[]={0,0,0,0,0};

/** 
 * solution[0~4] - 1번째 집의 색, 국적, 음료, 브랜드, 애완동물
 * solution[5~9] - 2번째 집의 색, 국적, 음료, 브랜드, 애완동물
 * solution[10~14] - 3번째 집의색, 국적, 음료, 브랜드, 애완동물
 * solution[15~19] - 4번째 집의색, 국적, 음료, 브랜드, 애완동물
 * solution[20~24] - 5번째 집의색, 국적, 음료, 브랜드, 애완동물
 **/
vector<int> solution;

/** ---------------------------------------------------------- **/

void expand(int depth){
  if(depth==25){
    printSolution();
    solutionCount++;
    return;
  }

  /** backtrack **/
  if(depth>0 && depth%5==0){
    if(promising(depth)==-1) {
      return;
    }
  }
  
  totalNode++;
  /** backtracking을 활용해 순열 생성 **/
  switch (depth%5)
  {
  case 0: /** color 배치 **/
    for(int i=0;i<5;i++){
      if(usedColor[i]==1)
        continue;
      else{
        usedColor[i]=1;
        solution.push_back(colors[i]);
        expand(depth+1);
        solution.pop_back();
        usedColor[i]=0;
      }
    }
    break;

  case 1: /** nationality 배치 **/
    for(int i=0;i<5;i++){
      if(usedNationality[i]==1)
        continue;
      else{
        usedNationality[i]=1;
        solution.push_back(nationalities[i]);
        expand(depth+1);
        solution.pop_back();
        usedNationality[i]=0;
      }
    }
    break;

  case 2: /** beverage 배치 **/
    for(int i=0;i<5;i++){
      if(usedBeverage[i]==1)
        continue;
      else{
        usedBeverage[i]=1;
        solution.push_back(beverages[i]);
        expand(depth+1);
        solution.pop_back();
        usedBeverage[i]=0;
      }
    }
    break;

  case 3: /** brand of cigar 배치 **/
    for(int i=0;i<5;i++){
      if(usedBrand[i]==1)
        continue;
      else{
        usedBrand[i]=1;
        solution.push_back(brands[i]);
        expand(depth+1);
        solution.pop_back();
        usedBrand[i]=0;
      }
    }
    break;

  case 4: /** pet 배치 **/
    for(int i=0;i<5;i++){
      if(usedPet[i]==1)
        continue;
      else{
        usedPet[i]=1;
        solution.push_back(pets[i]);
        expand(depth+1);
        solution.pop_back();
        usedPet[i]=0;
      }
    }
    break;

  default:
    break;
  }
}

void printSolution(){
  for(int i=0;i<25;i++){
    if(i%5==0)
      cout<<"\nhouse "<<i/5+1<<endl;
    switch (i%5)
    {
    case 0:
      cout<<"color : "<<printStringColor(solution[i]);
      break;
    case 1:
      cout<<"nationality : "<<printStringNationality(solution[i]);
      break;
    case 2:
      cout<<"beverage : "<<printStringBeverage(solution[i]);
      break;
    case 3:
      cout<<"brand of cigar : "<<printStringBeverage(solution[i]);
      break;
    case 4:
      cout<<"pet : "<<printStringPet(solution[i]);
      break;
    default:
      break;
    }
    cout<<"\n";
  }

  cout<<endl;
  cout<<solutionCount<<endl;
  cout<<"방문한 노드 수 : "<<totalNode<<endl;
}

const char* printStringColor(int colorNum){
  switch (colorNum)
  {
  case BLUE:
    return "blue";
  case GREEN:
    return "green";
  case RED:
    return "red";
  case WHITE:
    return "white";
  case YELLOW:
    return "yellow";
  }

  return "error";
}

const char* printStringNationality(int nationNum){
  switch (nationNum)
  {
  case BRIT:
    return "Brit";
  case DANE:
    return "Dane";
  case GERMAN:
    return "German";
  case NORWEIGIAN:
    return "Norweigian";
  case SWEDE:
    return "Swede";
  }
  return "error";
}


const char* printStringBeverage(int beverageNum){
  switch (beverageNum)
  {
  case BEER:
    return "beer";
  case COFFEE:
    return "coffee";
  case MILK:
    return "milk";
  case TEA:
    return "tea";
  case WATER:
    return "water";
  }
  return "error";
}

const char* printStringBrand(int brandNum){
  switch (brandNum)
  {
  case BLUE_MASTER:
    return "Blue Master";
  case DUNHILL:
    return "Dunhill";
  case PALL_MALL:
    return "Pall Mall";
  case PRINCE:
    return "Prince";
  case BLEND:
    return "Blend";
  }
  return "error";
}

const char* printStringPet(int petNum){
  switch (petNum)
  {
  case CAT:
    return "cat";
  case BIRD:
    return "bird";
  case DOG:
    return "dog";
  case FISH:
    return "fish";
  case HORSE:
    return "horse";
  }
  return "error";
}

/** 
 * (level%5)번째 집의 성립 여부를 판단하여 트리를 확장할지 결정한다. 
 * 1: 계속 진행, -1: backtrack
**/
int promising(int level){
  // 색, 국적, 등의 정보가 담긴 index
  int color = level-5;
  int nationality = level-4;
  int beverage = level-3;
  int brand = level-2;
  int pet = level-1;

  /** hint1 - The Brit lives in a red house**/
  if(solution[color]==RED)
    if(solution[nationality]!=BRIT)
      return -1;
  if(solution[nationality]==BRIT)
    if(solution[color]!=RED)
      return -1;
  /** hint2 - The Swede keeps dogs as pets**/
  if(solution[nationality]==SWEDE)
    if(solution[pet]!=DOG)
      return -1;
  if(solution[pet]==DOG)
    if(solution[nationality]!=SWEDE)
      return -1;
  /** hint3 - The Dane drinks tea **/
  if(solution[nationality]==DANE)
    if(solution[beverage]!=TEA)
      return -1;
  if(solution[beverage]==TEA)
    if(solution[nationality]!=DANE)
      return -1;
  /** hint5 - The green house owner drinks coffee **/
  if(solution[color]==GREEN)
    if(solution[beverage]!=COFFEE)
      return -1;
  if(solution[beverage]==COFFEE)
    if(solution[color]!=GREEN)
      return -1;
  /** hint6 - The person who smokes Pall Mall rears birds **/
  if(solution[brand]==PALL_MALL)
    if(solution[pet]!=BIRD)
      return -1;
  if(solution[pet]==BIRD)
    if(solution[brand]!=PALL_MALL)
      return -1;
  /** hint7 - 첫 번째 집 : DUNHILL **/
  if(level==5)
    if(solution[brand]!=DUNHILL) 
      return -1;
  if(solution[brand]==DUNHILL) 
    if(level!=5) 
      return -1;
  /** hint8 - 가운데 집 : MILK **/
  if(level==15) /** 가운데 집 :  MILK **/
    if(solution[beverage]!=MILK)
      return -1;
  if(solution[beverage]==MILK)
    if(level!=15) 
      return -1;
  /** hint9 - 첫 번째 집 : Norweigian**/
  if(level==5)
    if(solution[nationality]!=NORWEIGIAN) 
      return -1;
  if(solution[nationality]!=NORWEIGIAN) 
    if(level!=5) 
      return -1;
  /** hint11 - 두 번째 집 : Horse **/
  if(level==10)
    if(solution[pet]!=HORSE)
      return -1;
  if(solution[pet]==HORSE)
    if(level!=10)
      return -1;
  /** hint12 **/
  if(solution[brand]==BLUE_MASTER)
    if(solution[beverage]!=BEER)
      return -1;
  if(solution[beverage]==BEER)
    if(solution[brand]!=BLUE_MASTER)
      return -1;
  /** hint13 **/
  if(solution[nationality]==GERMAN)
    if(solution[brand]!=PRINCE)
      return -1;
  if(solution[brand]==PRINCE)
    if(solution[nationality]!=GERMAN)
      return -1;
  /** hint14 두 번째 집 : BLUE **/
  if(level==10) 
    if(solution[level-5]!=BLUE) 
    return -1;
  if(solution[level-5]==BLUE) 
    if(level!=10)
      return -1;
  /** extra **/
  if(level==5) /** 첫 번째 집 : YELLOW**/
    if(solution[color]!=YELLOW) /** 첫 번째 집 : YELLOW**/
      return -1;
  if(solution[color]==YELLOW) /** 첫 번째 집 : YELLOW**/
    if(level!=5) /** 첫 번째 집 : YELLOW**/
      return -1;

  /** promising **/
  return 1;
}