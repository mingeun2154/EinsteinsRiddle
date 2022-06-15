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
    return;
  }

  /** backtrack **/
  if(depth>0 && depth%5==0){
    // cout<<depth<<endl;
    // printStatus();
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

void printNumberOfNode(){
  cout<<"방문한 노드 개수 : "<<totalNode<<endl;
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
      cout<<"brand of cigar : "<<printStringBrand(solution[i]);
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
int promising(int depth){
  // 색, 국적, 등의 정보가 담긴 index
  int color = depth-5;
  int nationality = depth-4;
  int beverage = depth-3;
  int brand = depth-2;
  int pet = depth-1;

  /** hint1 - The Brit lives in a red house**/
  if(solution[color]==RED)
    if(solution[nationality]!=BRIT){
      // cout<<"-1-\n";
      return -1;
    }
  if(solution[nationality]==BRIT)
    if(solution[color]!=RED){
      // cout<<"-1-\n";
      return -1;
    }
  /** hint2 - The Swede keeps dogs as pets**/
  if(solution[nationality]==SWEDE)
    if(solution[pet]!=DOG){
      // cout<<"-2-\n";
      return -1;
    }
  if(solution[pet]==DOG)
    if(solution[nationality]!=SWEDE){
      // cout<<"-2-\n";
      return -1;
    }
  /** hint3 - The Dane drinks tea **/
  if(solution[nationality]==DANE)
    if(solution[beverage]!=TEA){
      // cout<<"-3-\n";
      return -1;
    }
  if(solution[beverage]==TEA)
    if(solution[nationality]!=DANE){
      // cout<<"-3-\n";
      return -1;
    }
  /** hint4 - The green house is on the left of the white house. **/
  if(depth>9){
    if(solution[color]==WHITE)
      if(solution[color-5]!=GREEN){
        // cout<<"-4-\n";
        return -1;
      }
    if(solution[color-5]==GREEN)
      if(solution[color]!=WHITE){
        // cout<<"-4-\n";
        return -1;
      }
  }
  /** hint5 - The green house owner drinks coffee **/
  if(solution[color]==GREEN)
    if(solution[beverage]!=COFFEE){
      // cout<<"-5-\n";
      return -1;
    }
  if(solution[beverage]==COFFEE)
    if(solution[color]!=GREEN){
      // cout<<"-5-\n";
      return -1;
    }
  /** hint6 - The person who smokes Pall Mall rears birds **/
  if(solution[brand]==PALL_MALL)
    if(solution[pet]!=BIRD){
      // cout<<"-6-\n";
      return -1;
    }
  if(solution[pet]==BIRD)
    if(solution[brand]!=PALL_MALL){
      // cout<<"-6-\n";
      return -1;
    }
  /** hint7 - The owner of the yellow house smokes Dunhill **/
  if(solution[color]==YELLOW)
    if(solution[brand]!=DUNHILL){
      // cout<<"-7-\n";
      return -1;
    }
  if(solution[brand]==DUNHILL) 
    if(solution[color]!=YELLOW){
      // cout<<"-7-\n";
      return -1;
    }
  /** hint8 - 가운데 집 : MILK **/
  if(depth==15) /** 가운데 집 :  MILK **/
    if(solution[beverage]!=MILK){
      // cout<<"-8-\n";
      return -1;
    }
  if(solution[beverage]==MILK)
    if(depth!=15) {
      // cout<<"-8-\n";
      return -1;
    }
  /** hint9 - 첫 번째 집 : Norweigian**/
  if(depth==5)
    if(solution[nationality]!=NORWEIGIAN) {
      // cout<<"-9-\n";
      return -1;
    }
  if(solution[nationality]==NORWEIGIAN) 
    if(depth!=5) {
      // cout<<"-9-\n";
      return -1;
    }
  /** hint10 - The man who smokes Blend lives next to the one who keeps cats **/
  if(depth>9 && depth<21){
    if(solution[brand]==BLEND)
      if(solution[pet-5]!=CAT)
        return -1;
    if(solution[pet]==CAT)
      if(solution[brand-5]!=BLEND)
        return -1;
  }
  /** hint11 - The man who keeps horses lives next to the main who smokes Dunhill. **/
  if(depth==10)
    if(solution[pet]!=HORSE){
      // cout<<"-11-\n";
      return -1;
    }
  if(solution[pet]==HORSE)
    if(depth!=10){
      // cout<<"-11-\n";
      return -1;
    }
  /** hint12 - The owner who smokes blue Master drinks beer. **/
  if(solution[brand]==BLUE_MASTER)
    if(solution[beverage]!=BEER){
      // cout<<"-12-\n";
      return -1;
    }
  if(solution[beverage]==BEER)
    if(solution[brand]!=BLUE_MASTER){
      // cout<<"-12-\n";
      return -1;
    }
  /** hint13 The German somkes Prince. **/
  if(solution[nationality]==GERMAN)
    if(solution[brand]!=PRINCE){
      // cout<<"-13-\n";
      return -1;
    }
  if(solution[brand]==PRINCE)
    if(solution[nationality]!=GERMAN){
      // cout<<"-13-\n";
      return -1;
    }
  /** hint14 두 번째 집 : BLUE **/
  if(depth==10) 
    if(solution[depth-5]!=BLUE) {
      // cout<<"-14-\n";
      return -1;
    }
  if(solution[depth-5]==BLUE) 
    if(depth!=10){
      // cout<<"-14-\n";
      return -1;
    }
  /** hint15 - The man who smokes Blend has a neighbor who drinks water. **/
  if(depth>9 && depth<21){
    if(solution[brand]==BLEND)
      if(solution[beverage-5]!=WATER)
        return -1;
    if(solution[beverage]==WATER)
      if(solution[brand-5]!=BLEND)
        return -1;
  }
  /** extra **/
  if(depth==5) /** 첫 번째 집 : YELLOW**/
    if(solution[color]!=YELLOW){ /** 첫 번째 집 : YELLOW**/
      // cout<<"-extra-\n";
      return -1;
    }
  if(solution[color]==YELLOW) /** 첫 번째 집 : YELLOW**/
    if(depth!=5){ /** 첫 번째 집 : YELLOW**/
      // cout<<"-extra-\n";
      return -1;
    }

  /** promising **/
  return 1;
}

void printStatus(){
  vector<int>::iterator iter;
  for(iter=solution.begin();iter!=solution.end();++iter)
    cout<<*iter<<' ';
  cout<<"\n";
}