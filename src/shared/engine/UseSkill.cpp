#include "../engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

UseSkill::UseSkill(state::Character& usedCharacter,std::vector<std::unique_ptr<state::Character>>& targetCharacter,int numberSkill):character(usedCharacter),targetList(targetCharacter),skillNumber(numberSkill){
  commandType= UseSkillcmd;
}
