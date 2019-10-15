#include "../state.h"
#include <iostream>

using namespace std;
using namespace state;


int Character::getMaxHP(state::Race race, state::Job job, state::Level level){
    int maxHP=0;

    if (race.race == Monster){
        maxHP=30 + 5*level.getLevel();
    }
    else if (race.race == Beastman){
        maxHP=30 + 5*level.getLevel();
    }
    else if (race.race == Demon){
        maxHP=30 + 5*level.getLevel();
    }
    else if (race.race == Human){
        maxHP=30 + 5*level.getLevel();
    }

    if(job.job == Pugilist){
        maxHP+=20;
    }
    if(job.job == Swordman){
        maxHP+=20;
    }
    if(job.job == Archer){
        maxHP+=20;
    }
    if(job.job == Magician){
        maxHP+=20;
    }
    return maxHP;
}

int Character::getMaxMP(state::Race race, state::Job job, state::Level level){
    int maxMP=0;
    if (race.race == Monster){
        maxMP=20 + 5*level.getLevel();
    }
    else if (race.race == Beastman){
        maxMP=10 + 5*level.getLevel();
    }
    else if (race.race == Demon){
        maxMP=30 + 5*level.getLevel();
    }
    else if (race.race == Human){
        maxMP=0 + 5*level.getLevel();
    }

    if(job.job == Pugilist){
        return maxMP;
    }
    if(job.job == Swordman){
        return maxMP;
    }
    if(job.job == Archer){
        return maxMP;
    }
    if(job.job == Magician){
        return maxMP+20;
    }

    return -1;
}

int Character::getEvade (state::Race race, state::Job job, state::Level level){
    int evade=0;
    if (race.race == Monster){
        evade=10 + 5*level.getLevel();
    }
    else if (race.race == Beastman){
        evade=15 + 5*level.getLevel();
    }
    else if (race.race == Demon){
        evade=20 + 5*level.getLevel();
    }
    else if (race.race == Human){
        evade=10 + 5*level.getLevel();
    }

    if(job.job == Pugilist){
        return evade+10;
    }
    if(job.job == Swordman){
        return evade;
    }
    if(job.job == Archer){
        return evade;
    }
    if(job.job == Magician){
        return evade;
    }
    return evade;
}

int Character::getAttackPower (state::Race race, state::Job job, state::Level level){
    int attack=0;
    if (race.race == Monster){
        attack=10 + 5*level.getLevel();
    }
    else if (race.race == Beastman){
        attack=15 + 5*level.getLevel();
    }
    else if (race.race == Demon){
        attack=20 + 5*level.getLevel();
    }
    else if (race.race == Human){
        attack=10 + 5*level.getLevel();
    }

    if(job.job == Pugilist){
        return attack+10;
    }
    if(job.job == Swordman){
        return attack;
    }
    if(job.job == Archer){
        return attack;
    }
    if(job.job == Magician){
        return attack;
    }
    return -1;
}

int Character::getMagicPower (state::Race race, state::Job job, state::Level level){
    int magic=0;
    if (race.race == Monster){
        magic=10 + 5*level.getLevel();
    }
    else if (race.race == Beastman){
        magic=15 + 5*level.getLevel();
    }
    else if (race.race == Demon){
        magic=20 + 5*level.getLevel();
    }
    else if (race.race == Human){
        magic=10 + 5*level.getLevel();
    }

    if(job.job == Pugilist){
        return magic;
    }
    if(job.job == Swordman){
        return magic;
    }
    if(job.job == Archer){
        return magic;
    }
    if(job.job == Magician){
        return magic+10;
    }
    return -1;

}

int Character::getDefense (state::Race race, state::Job job, state::Level level){
    int defense=0;
    if (race.race == Monster){
        defense=10 + 5*level.getLevel();
    }
    else if (race.race == Beastman){
        defense=15 + 5*level.getLevel();
    }
    else if (race.race == Demon){
        defense=20 + 5*level.getLevel();
    }
    else if (race.race == Human){
        defense=10 + 5*level.getLevel();
    }

    if(job.job == Pugilist){
        return defense;
    }
    if(job.job == Swordman){
        return defense+10;
    }
    if(job.job == Archer){
        return defense;
    }
    if(job.job == Magician){
        return defense;
    }
    return -1;

}

std::vector<state::Skill> Character::getSkillList (state::Job job, state::Level level){
    std::vector<Skill> skills(0);
    if (job.job == Magician){
        Skill fire {};
        fire.skillName="fire ball";
        fire.damage=10;
        fire.hpRecovery=0;
        skills.push_back(fire);
    }

    return skills;
}

state::Position Character::getPosition (){
    return position;
}
