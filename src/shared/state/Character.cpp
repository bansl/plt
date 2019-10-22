#include "../state.h"
#include <iostream>

using namespace std;
using namespace state;


int Character::getMaxHP(state::Race race, state::Job job, state::Level level){
    int maxHP=0;

    if (race.getRace()== Monster){
        maxHP=30 + 5*level.getLevel();
    }
    else if (race.getRace() == Beastman){
        maxHP=30 + 5*level.getLevel();
    }
    else if (race.getRace() == Demon){
        maxHP=30 + 5*level.getLevel();
    }
    else if (race.getRace() == Human){
        maxHP=30 + 5*level.getLevel();
    }

    if(job.getJob() == Pugilist){
        maxHP+=20;
    }
    if(job.getJob() == Swordman){
        maxHP+=20;
    }
    if(job.getJob() == Archer){
        maxHP+=20;
    }
    if(job.getJob() == Magician){
        maxHP+=20;
    }
    return maxHP;
}

int Character::getMaxMP(state::Race race, state::Job job, state::Level level){
    int maxMP=0;
    if (race.getRace() == Monster){
        maxMP=20 + 5*level.getLevel();
    }
    else if (race.getRace() == Beastman){
        maxMP=10 + 5*level.getLevel();
    }
    else if (race.getRace() == Demon){
        maxMP=30 + 5*level.getLevel();
    }
    else if (race.getRace() == Human){
        maxMP=0 + 5*level.getLevel();
    }

    if(job.getJob() == Pugilist){
        return maxMP;
    }
    if(job.getJob() == Swordman){
        return maxMP;
    }
    if(job.getJob() == Archer){
        return maxMP;
    }
    if(job.getJob() == Magician){
        return maxMP+20;
    }

    return -1;
}

int Character::getEvade (state::Race race, state::Job job, state::Level level){
    int evade=0;
    if (race.getRace() == Monster){
        evade=10 + 5*level.getLevel();
    }
    else if (race.getRace() == Beastman){
        evade=15 + 5*level.getLevel();
    }
    else if (race.getRace() == Demon){
        evade=20 + 5*level.getLevel();
    }
    else if (race.getRace() == Human){
        evade=10 + 5*level.getLevel();
    }

    if(job.getJob() == Pugilist){
        return evade+10;
    }
    if(job.getJob() == Swordman){
        return evade;
    }
    if(job.getJob() == Archer){
        return evade;
    }
    if(job.getJob() == Magician){
        return evade;
    }
    return -1;
}

int Character::getAttackPower (state::Race race, state::Job job, state::Level level){
    int attack=0;
    if (race.getRace() == Monster){
        attack=10 + 5*level.getLevel();
    }
    else if (race.getRace() == Beastman){
        attack=15 + 5*level.getLevel();
    }
    else if (race.getRace() == Demon){
        attack=20 + 5*level.getLevel();
    }
    else if (race.getRace() == Human){
        attack=10 + 5*level.getLevel();
    }

    if(job.getJob() == Pugilist){
        return attack+10;
    }
    if(job.getJob() == Swordman){
        return attack;
    }
    if(job.getJob() == Archer){
        return attack;
    }
    if(job.getJob() == Magician){
        return attack;
    }
    return -1;
}

int Character::getMagicPower (state::Race race, state::Job job, state::Level level){
    int magic=0;
    if (race.getRace() == Monster){
        magic=10 + 5*level.getLevel();
    }
    else if (race.getRace() == Beastman){
        magic=15 + 5*level.getLevel();
    }
    else if (race.getRace() == Demon){
        magic=20 + 5*level.getLevel();
    }
    else if (race.getRace() == Human){
        magic=10 + 5*level.getLevel();
    }

    if(job.getJob() == Pugilist){
        return magic;
    }
    if(job.getJob() == Swordman){
        return magic;
    }
    if(job.getJob() == Archer){
        return magic;
    }
    if(job.getJob() == Magician){
        return magic+10;
    }
    return -1;

}

int Character::getDefense (state::Race race, state::Job job, state::Level level){
    int defense=0;
    if (race.getRace() == Monster){
        defense=10 + 5*level.getLevel();
    }
    else if (race.getRace() == Beastman){
        defense=15 + 5*level.getLevel();
    }
    else if (race.getRace() == Demon){
        defense=20 + 5*level.getLevel();
    }
    else if (race.getRace() == Human){
        defense=10 + 5*level.getLevel();
    }

    if(job.getJob() == Pugilist){
        return defense;
    }
    if(job.getJob() == Swordman){
        return defense+10;
    }
    if(job.getJob() == Archer){
        return defense;
    }
    if(job.getJob() == Magician){
        return defense;
    }
    return -1;

}

std::vector<state::Skill> Character::getSkillList (state::Job job, state::Level level){
    std::vector<Skill> skills(0);
    if (job.getJob() == Magician){
        Skill fire {};
        fire.skillName="fire ball";
        fire.damage=10;
        fire.hpRecovery=0;
        skills.push_back(fire);
    }

    return skills;
}

state::Position& Character::getPosition(){
	Position & addrPosition = position;
	return addrPosition ;
}

int Character::setCurrentHP (int hpModifier){
    this->currentHP+=hpModifier;
    return 1;
}
int Character::setCurrentMP (int mpModifier){
    this->currentMP+=mpModifier;
    return 1;
}

state::Level Character::getLevel (){
    return level;
}

state::Race Character::getRace (){
    return race;
}

state::Job Character::getJob (){
    return job;
}
void Character::setRace(state::Race race){
  this->race=race;
}

void Character::setJob(state::Job job){
  this->job=job;
}

int Character::getCurrentHP (){
    return currentHP;
}

int Character::getCurrentMP (){
    return currentMP;
}

void Character::initHPMP (state::Race race, state::Job job, state::Level level){
    this->currentHP=getMaxHP(race,job,level);
    this->currentMP=getMaxMP(race,job,level);
}
