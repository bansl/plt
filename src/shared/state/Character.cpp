#include "../state.h"
#include <iostream>

using namespace std;
using namespace state;


int Character::getMaxHP(){
    int maxHP=0;

    if (this->race.getRace()== Monster){
        maxHP=30 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Beastman){
        maxHP=30 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Demon){
        maxHP=30 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Human){
        maxHP=30 + 5*this->level.getLevel();
    }

    if(this->job.getJob() == Pugilist){
        maxHP+=20;
    }
    if(this->job.getJob() == Swordman){
        maxHP+=20;
    }
    if(this->job.getJob() == Archer){
        maxHP+=20;
    }
    if(this->job.getJob() == Magician){
        maxHP+=20;
    }
    return maxHP;
}

int Character::getMaxMP(){
    int maxMP=0;
    if (this->race.getRace() == Monster){
        maxMP=20 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Beastman){
        maxMP=10 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Demon){
        maxMP=30 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Human){
        maxMP=0 + 5*this->level.getLevel();
    }

    if(this->job.getJob() == Pugilist){
        return maxMP;
    }
    if(this->job.getJob() == Swordman){
        return maxMP;
    }
    if(this->job.getJob() == Archer){
        return maxMP;
    }
    if(this->job.getJob() == Magician){
        return maxMP+20;
    }

    return -1;
}

int Character::getEvade (){
    int evade=0;
    if (this->race.getRace() == Monster){
        evade=10 + 5*this->level.getLevel();
    }
    else if (race.getRace() == Beastman){
        evade=15 + 5*this->level.getLevel();
    }
    else if (race.getRace() == Demon){
        evade=20 + 5*this->level.getLevel();
    }
    else if (race.getRace() == Human){
        evade=10 + 5*this->level.getLevel();
    }

    if(this->job.getJob() == Pugilist){
        return evade+10;
    }
    else if(this->job.getJob() == Swordman){
        return evade;
    }
    else if(this->job.getJob() == Archer){
        return evade;
    }
    else if(this->job.getJob() == Magician){
        return evade;
    }
    return -1;
}

int Character::getAttackPower (){
    int attack=0;
    if (this->race.getRace() == Monster){
        attack=10 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Beastman){
        attack=15 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Demon){
        attack=20 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Human){
        attack=10 + 5*this->level.getLevel();
    }

    if(this->job.getJob() == Pugilist){
        return attack+10;
    }
    else if(this->job.getJob() == Swordman){
        return attack;
    }
    else if(this->job.getJob() == Archer){
        return attack;
    }
    else if(this->job.getJob() == Magician){
        return attack;
    }
    return -1;
}

int Character::getMagicPower (){
    int magic=0;
    if (this->race.getRace() == Monster){
        magic=10 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Beastman){
        magic=15 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Demon){
        magic=20 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Human){
        magic=10 + 5*this->level.getLevel();
    }

    if(this->job.getJob() == Pugilist){
        return magic;
    }
    else if(this->job.getJob() == Swordman){
        return magic;
    }
    else if(this->job.getJob() == Archer){
        return magic;
    }
    else if(this->job.getJob() == Magician){
        return magic+10;
    }
    return -1;

}

int Character::getDefense (){
    int defense=0;
    if (this->race.getRace() == Monster){
        defense=10 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Beastman){
        defense=15 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Demon){
        defense=20 + 5*this->level.getLevel();
    }
    else if (this->race.getRace() == Human){
        defense=10 + 5*this->level.getLevel();
    }
    if(getStatus()==Defending){
      defense=defense*1.5;
    }

    if(this->job.getJob() == Pugilist){
        return defense;
    }
    else if(this->job.getJob() == Swordman){
        return defense+10;
    }
    else if(this->job.getJob() == Archer){
        return defense;
    }
    else if(this->job.getJob() == Magician){
        return defense;
    }
    return -1;

}

void Character::initializeSkill(){
  if (this->job.getJob() == Magician){
          Skill fire {};
          fire.skillName="fire ball";
          fire.setEffect(10,0);
          fire.setMpCost(5);
          addSkill(fire);
  }
}

std::vector<Skill*>& Character::getSkillList(){
  std::vector<Skill*>& addrSkillList=listSkill;
  return addrSkillList;
}

void Character::addSkill(state::Skill newSkill){
  Skill * ptr_skill =(new Skill(newSkill));
  listSkill.push_back(ptr_skill);
}

state::Position& Character::getPosition(){
	Position & addrPosition = position;
	return addrPosition ;
}

void Character::setCurrentHP (int hpModifier){
  if(this->currentHP+hpModifier>getMaxHP()){
    this->currentHP=getMaxHP();
  }
  else{
    this->currentHP+=hpModifier;
  }
}

void Character::setCurrentMP (int mpModifier){
  if(this->currentMP+mpModifier>getMaxMP()){
    this->currentMP=getMaxMP();
  }
  else{
    this->currentMP+=mpModifier;
  }
}

state::Level& Character::getLevel (){
    Level & addrLevel= level;
    return addrLevel;
}

state::Race& Character::getRace (){
    Race & addrRace=race;
    return addrRace;
}

state::Job& Character::getJob (){
    Job & addrJob=job;
    return addrJob;
}

int Character::getCurrentHP (){
    return currentHP;
}

int Character::getCurrentMP (){
    return currentMP;
}

void Character::initHPMP (){
    this->currentHP=getMaxHP();
    this->currentMP=getMaxMP();
}

state::StatusList Character::getStatus(){
    return status;
}
void Character::setStatus(state::StatusList newstatus){
    status=newstatus;
}
