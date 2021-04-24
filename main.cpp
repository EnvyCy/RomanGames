//Jan Cichy
#include <iostream>
using namespace std;

class PLAYER_CLASS;
class CAESAR_CLASS;
class ARENA_CLASS;
class HUMAN_CLASS;
class BEAST_CLASS;
class BERSERKER_CLASS;
class SQUAD_CLASS;

class PLAYER_CLASS{
protected:
    unsigned int current_health;
    unsigned int max_health;
    unsigned int damage;
    unsigned int agility;
    string human_id;
    string beast_id;
    virtual void die() = 0;
public:
    PLAYER_CLASS();
    virtual unsigned int getRemainingHealth() = 0;
    bool isDead();
    virtual unsigned int getDamage() = 0;
    virtual unsigned int getAgility() = 0;
    virtual void takeDamage(unsigned int damage) = 0;
    virtual void printParams() = 0;
    virtual void applyWinnerReward() = 0;
    virtual void cure() = 0;

    friend class CAESAR_CLASS;
    friend class SQUAD_CLASS;
};

class CAESAR_CLASS{
public:
    int caesar_count;
    CAESAR_CLASS();
    void judgeDeathOfLife(PLAYER_CLASS* player);

};

class ARENA_CLASS{
private:
    CAESAR_CLASS* Caesar;
public:
    ARENA_CLASS(CAESAR_CLASS* Caesar);
    void fight(PLAYER_CLASS* player1, PLAYER_CLASS* player2);
};

class HUMAN_CLASS : public virtual PLAYER_CLASS {
public:
    unsigned int defence;
    HUMAN_CLASS(string);
    unsigned int getAgility();
    unsigned int getDamage();
    unsigned int getRemainingHealth();
    void takeDamage(unsigned int);
    void printParams();
    void die();
    void applyWinnerReward();
    void cure();

};

class BEAST_CLASS : public virtual PLAYER_CLASS{
public:
//    string Id;
    BEAST_CLASS(string);
    unsigned int getAgility();
    unsigned int getDamage();
    void takeDamage(unsigned int);
    void printParams();
    void die();
    unsigned int getRemainingHealth();
    void applyWinnerReward();
    void cure();
};

class BERSERKER_CLASS : public HUMAN_CLASS, public BEAST_CLASS {
public:
//    string human_id;
//    string beast_id;
    BERSERKER_CLASS(string h, string b);
    unsigned int getAgility();
    unsigned int getDamage();
    void takeDamage(unsigned int);
    void printParams();
    void die();
    unsigned int getRemainingHealth();
    void applyWinnerReward();
    void cure();
};

class SQUAD_CLASS : public PLAYER_CLASS{
public:
    struct list{
        PLAYER_CLASS* player;
        list* next_player;
        list(){
            next_player = NULL;
        }

    };
    list* first_player;

    string Id;
    bool squad_dead;
    unsigned int player_count;
    SQUAD_CLASS(string);
    void addPlayer(PLAYER_CLASS* player);
    unsigned int getRemainingHealth();
    unsigned int getAgility();
    unsigned int getDamage();
    void takeDamage(unsigned int damage);
    void printParams();
    bool nameExists(PLAYER_CLASS*);
    void die();
    void applyWinnerReward();
    void cure();
    void eraseTheDead();
    void eraseFirst();

};



PLAYER_CLASS::PLAYER_CLASS(){

}   //PLAYER

bool PLAYER_CLASS::isDead() {
    return (current_health == 0);
}

void PLAYER_CLASS::cure() {
    current_health = max_health;
}


CAESAR_CLASS::CAESAR_CLASS(){
    caesar_count = 0;
}       //CAESAR

void CAESAR_CLASS::judgeDeathOfLife(PLAYER_CLASS *player) {     //CAESAR
    caesar_count++;
    if (caesar_count % 3 == 0)
        player->die();
}



HUMAN_CLASS::HUMAN_CLASS(string Id){
    human_id = Id;
    max_health = 200;
    current_health = 200;
    damage = 30;
    agility = 10;
    defence = 10;
};  //HUMAN

unsigned int HUMAN_CLASS::getAgility(){
    return agility;
}

unsigned int HUMAN_CLASS::getDamage(){
    return damage;
}

void HUMAN_CLASS::takeDamage(unsigned int amount){
    if(amount > (agility + defence)) {
        amount -= (agility + defence);

        if (amount > current_health)
            current_health = 0;
        else
            current_health -= amount;
    }
}

void HUMAN_CLASS::printParams(){
    if(current_health == 0)
        cout << human_id << ":" << "R.I.P." << endl;
    else
        cout << human_id << ":" << max_health << ":" << current_health << ":" << this->getRemainingHealth() << "%:"
        << damage << ":" << agility << ":" << defence << endl;
}

void HUMAN_CLASS::die() {
    current_health = 0;
}

unsigned int HUMAN_CLASS::getRemainingHealth() {
    double a = (double)current_health / (double)max_health;
    return (a * 100);
}

void HUMAN_CLASS::applyWinnerReward() {
    damage += 2;
    agility += 2;
}

void HUMAN_CLASS::cure() {
    current_health = max_health;
}



BEAST_CLASS::BEAST_CLASS(string Id){
    beast_id = Id;
    max_health = 150;
    current_health = 150;
    damage = 40;
    agility = 20;

}       //BEAST

void BEAST_CLASS::printParams(){
    if(current_health == 0)
        cout << beast_id << ":" << "R.I.P." << endl;
    else
        cout << beast_id << ":" << max_health << ":" << current_health << ":" << (100 * current_health) / max_health << "%:"
         << this->getDamage() << ":" << agility << endl;
}

unsigned int BEAST_CLASS::getAgility(){
    return agility;
}

unsigned int BEAST_CLASS::getDamage(){
    if(this->getRemainingHealth() < 25)
        return damage * 2;

    return damage;
}

void BEAST_CLASS::takeDamage(unsigned int amount){
    if(amount > this->getAgility() / 2) {
        amount -= this->getAgility() / 2;

        if (amount > current_health)
            current_health = 0;
        else
            current_health -= amount;
    }
}

void BEAST_CLASS::die() {
    current_health = 0;
}

unsigned int BEAST_CLASS::getRemainingHealth() {
    double a = (double)current_health / (double)max_health;
    return (a * 100);
}

void BEAST_CLASS::applyWinnerReward() {
    damage += 2;
    agility += 2;
}

void BEAST_CLASS::cure() {
    current_health = max_health;
}



BERSERKER_CLASS::BERSERKER_CLASS(string Human, string Beast): HUMAN_CLASS(Human), BEAST_CLASS(Beast){      //BERSERKER   todo
    this->human_id = Human;
    this->beast_id = Beast;
    max_health = 200;
    current_health = 200;
    damage = 35;
    agility = 5;
    defence = 15;
}   //BERSERKER

unsigned int BERSERKER_CLASS::getAgility() {
    return agility;
}

unsigned int BERSERKER_CLASS::getDamage() {
    if(getRemainingHealth() < 25)
        return damage * 2;

    return damage;
}

void BERSERKER_CLASS::takeDamage(unsigned int amount) {
    if(amount > (defence + agility)) {
        if (getRemainingHealth() >= 25) {     //takes damage like human
            amount -= (defence + agility);
            if (amount > current_health)
                current_health = 0;
            else
                current_health -= amount;
        } else {           //takes damage like beast
            amount -= agility / 2;

            if (amount > current_health)
                current_health = 0;
            else
                current_health -= amount;
        }
    }
}

void BERSERKER_CLASS::printParams(){
    if(getRemainingHealth() >= 25 || isDead()){         //print for human
        if(isDead())
            cout << human_id << ":" << "R.I.P." << endl;
        else
            cout << human_id << ":" << max_health << ":" << current_health << ":" << this->getRemainingHealth() << "%:"
                 << damage << ":" << agility << ":" << defence << endl;
    }
    else{               //print for beast
        if(isDead())
            cout << beast_id << ":" << "R.I.P." << endl;
        else
            cout << beast_id << ":" << max_health << ":" << current_health << ":" << (100 * current_health) / max_health << "%:"
                 << this->getDamage() << ":" << agility << endl;
    }

}

void BERSERKER_CLASS::die() {
    current_health = 0;
}

unsigned int BERSERKER_CLASS::getRemainingHealth() {
    double a = (double)current_health / (double)max_health;
    return (a * 100);
}

void BERSERKER_CLASS::applyWinnerReward() {
    damage += 2;
    agility += 2;
}

void BERSERKER_CLASS::cure() {
    current_health = max_health;
}



SQUAD_CLASS::SQUAD_CLASS(string Id) {      //SQUAD
    this->Id = Id;
    player_count = 0;
    first_player = NULL;
    squad_dead = true;
}       //SQUAD

void SQUAD_CLASS::addPlayer(PLAYER_CLASS* player) {
    if(player->isDead())      //if added player is dead
        return;

    if(nameExists(player))      //if player already exists
        return;

    squad_dead = false;
    list* added_player = new list;
    added_player->player = player;
    added_player->player->human_id = player->human_id;
    added_player->player->beast_id = player->beast_id;

    if(first_player == NULL)
        first_player = added_player;
    else{
        list* tmp = first_player;
        while(tmp->next_player){
            tmp = tmp->next_player;
        }

        tmp->next_player = added_player;
    }

    player_count++;
}

unsigned int SQUAD_CLASS::getRemainingHealth(){    //find player with max health
    if(first_player == NULL)
        return 0;
    unsigned int max_health1 = first_player->player->getRemainingHealth();
    list* tmp = first_player;
    while(tmp){
        if(tmp->player->getRemainingHealth() > max_health)
            max_health = tmp->player->getRemainingHealth();
        tmp = tmp->next_player;
    }

    return max_health1;
}

bool SQUAD_CLASS::nameExists(PLAYER_CLASS* player){
    if (first_player == NULL)
        return false;

    list *tmp = first_player;
    while (tmp) {
        if (tmp->player == player)
            return true;

        tmp = tmp->next_player;
    }
    return false;
}

unsigned int SQUAD_CLASS::getAgility() {
    if(first_player == NULL)
        return 0;
    unsigned int min_agility = first_player->player->getAgility();
    list* tmp = first_player;
    while(tmp){
        if(tmp->player->getAgility() < min_agility)
            min_agility = tmp->player->getAgility();

        tmp = tmp->next_player;
    }

    return min_agility;
}

unsigned int SQUAD_CLASS::getDamage() {
    if(first_player == NULL)
        return 0;
    unsigned int total_damage = 0;
    list* tmp = first_player;
    while(tmp){
        total_damage += tmp->player->getDamage();
        tmp = tmp->next_player;
    }

    return total_damage;

}

void SQUAD_CLASS::takeDamage(unsigned int damage) {
    if(first_player == NULL)
        return;
    list* tmp = first_player;
    damage /= player_count;
    while(tmp){
        tmp->player->takeDamage(damage);
        tmp = tmp->next_player;
    }
    eraseTheDead();
}

void SQUAD_CLASS::printParams() {
    if(squad_dead || first_player == NULL)
        cout << Id <<  ":nemo" << endl;
    else{
        cout << Id << ":" << player_count << ":" << getRemainingHealth() << "%:" <<
        getDamage() << ":" << getAgility() << endl;
    }

    if(first_player == NULL)
        return;

    list* tmp = first_player;
    while(tmp){
        tmp->player->printParams();
        tmp = tmp->next_player;
    }
}

void SQUAD_CLASS::die(){
    if(first_player == NULL)
        return;

    list *temp = first_player;
    while (temp) {
        temp->player->current_health = 0;
        temp = temp->next_player;
    }
    first_player = NULL;
    squad_dead = true;
}

void SQUAD_CLASS::applyWinnerReward() {
    if(first_player == NULL)
        return;
    list* tmp = first_player;
    while(tmp){
        if(!tmp->player->isDead())
            tmp->player->applyWinnerReward();


        tmp = tmp->next_player;
    }
}

void SQUAD_CLASS::cure() {
    if(first_player == NULL)
        return;
    list* tmp = first_player;
    while(tmp){
        if(!tmp->player->isDead())
            tmp->player->current_health = tmp->player->max_health;

        tmp = tmp->next_player;
    }
}

void SQUAD_CLASS::eraseFirst(){
    if(first_player == NULL)
        return;

    if(first_player->next_player == NULL) {
        delete first_player;
        first_player = NULL;
    }
    else {
        list* tmp = first_player->next_player;
        delete first_player;
        first_player = tmp;
    }
}

void SQUAD_CLASS::eraseTheDead(){
    if(first_player == NULL)
        return;
    list* tmp = first_player;
    if(first_player->next_player == NULL) {
        if(first_player->player->isDead()){      //erase first player if hes dead
            player_count--;
            eraseFirst();
        }
        return;
    }
    list* tmp1 = NULL;

    while(tmp->next_player) {
        if(first_player->player->isDead()) {
            player_count--;
            tmp1 = tmp->next_player;
            delete first_player;
            first_player = tmp1;
            tmp = tmp1;
        } else
            break;
    }
    if(first_player->next_player == NULL) {
        if(first_player->player->isDead()) {
            player_count--;
            delete first_player;
            first_player = NULL;
            return;
        } else
            return;
    }
    if(first_player->next_player->next_player == NULL) {
        if(first_player->next_player->player->isDead()) {
            player_count--;
            delete first_player->next_player;
            first_player->next_player = NULL;
            return;
        } else
            return;
    }
    while(tmp->next_player->next_player) {
        if(tmp->next_player->player->isDead()) {
            player_count--;
            tmp1 = tmp->next_player->next_player;
            delete tmp->next_player;
            tmp->next_player = tmp1;
        } else
            tmp = tmp->next_player;
    }
    list* tmp2 = first_player;
    while(tmp2->next_player->next_player) {
        tmp2 = tmp2->next_player;
    }
    if(tmp2->next_player->player->isDead()) {
        player_count--;
        delete tmp2->next_player;
        tmp2->next_player = NULL;
    }
}


ARENA_CLASS::ARENA_CLASS(CAESAR_CLASS* Caesar){
    this->Caesar = Caesar;
}       //ARENA

void ARENA_CLASS::fight(PLAYER_CLASS *player1, PLAYER_CLASS *player2) {
    if(player1->getRemainingHealth() == 0 || player2->getRemainingHealth() == 0)
        return;

    unsigned int AG1 = player1->getAgility();
    unsigned int AG2 = player2->getAgility();
    int attack_counter = 0;
    PLAYER_CLASS *P1;
    PLAYER_CLASS *P2;

    if(AG2 > AG1){
        P1 = player2;
        P2 = player1;
    }
    else{
        P1 = player1;
        P2 = player2;
    }

    P1->printParams();
    P2->printParams();



    while(!(P2->getRemainingHealth() < 10 || P1->getRemainingHealth() < 10 || attack_counter == 40)) {
        if (!(P1->getRemainingHealth() == 0)) {      //if player1 is alive
            attack_counter++;
            P2->takeDamage(P1->getDamage());        //attack player2
            P2->printParams();
        }

        if(P2->getRemainingHealth() < 10 || P1->getRemainingHealth() < 10 || attack_counter == 40)
            break;

        if (!(P2->getRemainingHealth() == 0)) {      //if player2 is alive
            attack_counter++;
            P1->takeDamage(P2->getDamage());    //attack player1
            P1->printParams();
        }
    }

    if(!(P1->getRemainingHealth() == 0)){                                                    //judge player1
        if(attack_counter % 2 == 0)
            Caesar->judgeDeathOfLife(P1);
        P1->printParams();
    }

    if(!(P2->getRemainingHealth() == 0)){                                                    //judge player2
        if(attack_counter % 2 == 0)
            Caesar->judgeDeathOfLife(P2);
        P2->printParams();
    }

    if(!(P1->getRemainingHealth() == 0)){               //if alive apply reward to player1
        P1->applyWinnerReward();
        P1->cure();
    }

    if(!(P2->getRemainingHealth() == 0)){             //if alive apply reward to player2
        P2->applyWinnerReward();
        P2->cure();
    }

    P1->printParams();
    P2->printParams();


}
int main() {
    CAESAR_CLASS caesar;

    ARENA_CLASS arena(&caesar);

    HUMAN_CLASS human1("human1");
    BEAST_CLASS beast1("beast1");
    BERSERKER_CLASS berserker1("berserker-human1", "berserker-beast1");

    HUMAN_CLASS dead("dead-human");
    dead.takeDamage(500);

    SQUAD_CLASS squad("squad");
    squad.addPlayer(&human1);
    squad.addPlayer(&beast1);
    squad.addPlayer(&berserker1);
    squad.addPlayer(&dead);
    squad.addPlayer(&human1);
    squad.addPlayer(&beast1);
    squad.addPlayer(&berserker1);

    HUMAN_CLASS human2("human2");
    HUMAN_CLASS human3("human3");
    HUMAN_CLASS human4("human4");
    HUMAN_CLASS human5("human5");

    SQUAD_CLASS humansquad("humansquad");
    humansquad.addPlayer(&human2);
    humansquad.addPlayer(&human3);
    humansquad.addPlayer(&human4);
    humansquad.addPlayer(&human5);

    arena.fight(&humansquad, &squad);
}