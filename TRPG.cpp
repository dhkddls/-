#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// 직업별 능력치 구조체
struct JobStats {
    int health;
    int attack;
    int defense;
};
// 적 클래스
class Enemy {
public:
    string name;
    int health;
    int attack;
    float evadeChance; // 회피 확률
    int experienceReward; // 경험치 보상

    Enemy(string n, int h, int a, float evade, int exp) : name(n), health(h), attack(a), evadeChance(evade), experienceReward(exp) {}

    bool evadeAttack() {
        return (static_cast<float>(rand()) / RAND_MAX) < evadeChance; // 회피 성공 여부
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0; // 체력이 0 이하로 떨어지지 않도록
    }
};
// 직업별 능력치 초기화
JobStats getJobStats(const string& job) {
    if (job == "전사") {
        return { 120, 15, 10 }; // 전사: 체력, 공격력, 방어력
    }
    else if (job == "마법사") {
        return { 80, 20, 5 }; // 마법사: 체력, 공격력, 방어력
    }
    else if (job == "도적") {
        return { 90, 18, 7 }; // 도적: 체력, 공격력, 방어력
    }
    else if (job == "요리사") {
        return { 70, 10, 5 }; // 요리사: 체력, 공격력, 방어력
    }
    else if (job == "사냥꾼") {
        return { 100, 15, 8 }; // 사냥꾼: 체력, 공격력, 방어력
    }
    else if (job == "검투사") {
        return { 110, 17, 9 }; // 검투사: 체력, 공격력, 방어력
    }
    else if (job == "성직자") {
        return { 85, 12, 6 }; // 성직자: 체력, 공격력, 방어력
    }
    else if (job == "방패기사") {
        return { 130, 14, 15 }; // 방패기사: 체력, 공격력, 방어력
    }
    else {
        return { 100, 10, 5 }; // 기본값
    }
}

// 캐릭터 클래스
class Character {
public:
    string name;
    string job;
    int level;
    int health;
    int attack;
    int defense;
    int experience;
    float evadeChance; // 회피 확률

    Character(string n, string j) : name(n), job(j), level(1), experience(0) {
        JobStats stats = getJobStats(j);
        health = stats.health;
        attack = stats.attack;
        defense = stats.defense;
        evadeChance = 0.1f; // 기본 회피 확률 설정 (10%)
    }

    void levelUp() {
        level++;
        health += 20;
        attack += 5;
        defense += 2;
        cout << name << "이(가) 레벨 " << level << "로 상승했습니다!" << endl;
    }

    void gainExperience(int exp) {
        experience += exp;
        if (experience >= level * 100) { // 레벨업 조건
            experience -= level * 100;
            levelUp();
        }
    

    bool evadeAttack() {
        return (static_cast<float>(rand()) / RAND_MAX) < evadeChance; // 회피 성공 여부
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0; // 체력이 0 이하로 떨어지지 않도록
    }

    // 직업별 스킬 사용
    void useSkill(int skillChoice, Enemy& enemy) {
        if (job == "전사") {
            if (skillChoice == 1) {
                int damage = attack * 2; // 강력한 공격
                enemy.takeDamage(damage);
                cout << name << "이(가) 강력한 공격으로 " << enemy.name << "에게 " << damage << "의 피해를 입혔습니다!" << endl;
            }
            else if (skillChoice == 2) {
                health += 15; // 체력 회복
                cout << name << "이(가) 체력을 15 회복했습니다!" << endl;
            }
        }
        else if (job == "마법사") {
            if (skillChoice == 1) {
                int damage = attack * 1.5; // 마법 공격
                enemy.takeDamage(damage);
                cout << name << "이(가) 마법 공격으로 " << enemy.name << "에게 " << damage << "의 피해를 입혔습니다!" << endl;
            }
            else if (skillChoice == 2) {
                evadeChance += 0.1f; // 회피 확률 증가
                cout << name << "이(가) 마법으로 회피 확률을 증가시켰습니다!" << endl;
            }
        }
        else if (job == "도적") {
            if (skillChoice == 1) {
                int damage = attack * 1.8; // 빠른 공격
                enemy.takeDamage(damage);
                cout << name << "이(가) 빠른 공격으로 " << enemy.name << "에게 " << damage << "의 피해를 입혔습니다!" << endl;
            }
            else if (skillChoice == 2) {
                evadeChance += 0.2f; // 회피 확률 증가
                cout << name << "이(가) 은신하여 회피 확률을 증가시켰습니다!" << endl;
            }
        }
        else if (job == "요리사") {
            if (skillChoice == 1) {
                health += 20; // 요리로 체력 회복
                cout << name << "이(가) 요리로 체력을 20 회복했습니다!" << endl;
            }
            else if (skillChoice == 2) {
                attack += 5; // 공격력 증가
                cout << name << "이(가) 요리로 공격력을 5 증가시켰습니다!" << endl;
            }
        }
        else if (job == "사냥꾼") {
            if (skillChoice == 1) {
                int damage = attack * 1.5; // 원거리 공격
                enemy.takeDamage(damage);
                cout << name << "이(가) 원거리 공격으로 " << enemy.name << "에게 " << damage << "의 피해를 입혔습니다!" << endl;
            }
            else if (skillChoice == 2) {
                evadeChance += 0.15f; // 회피 확률 증가
                cout << name << "이(가) 숲의 은신으로 회피 확률을 증가시켰습니다!" << endl;
            }
        }
        else if (job == "검투사") {
            if (skillChoice == 1) {
                int damage = attack * 2; // 강력한 검술
                enemy.takeDamage(damage);
                cout << name << "이(가) 강력한 검술로 " << enemy.name << "에게 " << damage << "의 피해를 입혔습니다!" << endl;
            }
            else if (skillChoice == 2) {
                defense += 5; // 방어력 증가
                cout << name << "이(가) 방어력을 5 증가시켰습니다!" << endl;
            }
        }
        else if (job == "성직자") {
            if (skillChoice == 1) {
                health += 10; // 치유
                cout << name << "이(가) 치유로 체력을 10 회복했습니다!" << endl;
            }
            else if (skillChoice == 2) {
                // 아군의 방어력 증가 (여기서는 자기 자신)
                defense += 3;
                cout << name << "이(가) 아군의 방어력을 3 증가시켰습니다!" << endl;
            }
        }
        else if (job == "방패기사") {
            if (skillChoice == 1) {
                int damage = attack * 1.5; // 방패로 공격
                enemy.takeDamage(damage);
                cout << name << "이(가) 방패로 " << enemy.name << "에게 " << damage << "의 피해를 입혔습니다!" << endl;
            }
            else if (skillChoice == 2) {
                defense += 10; // 방어력 증가
                cout << name << "이(가) 방어력을 10 증가시켰습니다!" << endl;
            }
        }
    }
};

// 전투 함수
void battle(Character& player, const Enemy& enemy) {
    cout << player.name << " (레벨 " << player.level << ") vs " << enemy.name << endl;

    Enemy enemyCopy = enemy; // 적의 복사본 생성

    while (player.health > 0 && enemyCopy.health > 0) {
        // 플레이어 턴
        cout << "\n당신의 턴! 행동을 선택하세요:\n1. 공격\n2. 회피\n3. 스킬 사용\n";
        int choice;
        cin >> choice;

        if (choice == 1) { // 공격
            if (!enemyCopy.evadeAttack()) { // 적이 회피하지 못하면 공격
                int damage = player.attack - enemyCopy.attack / 2; // 방어력 적용
                enemyCopy.takeDamage(damage);
                cout << player.name << "이(가) " << enemyCopy.name << "에게 " << damage << "의 피해를 입혔습니다!" << endl;
            }
            else {
                cout << enemyCopy.name << "이(가) 공격을 회피했습니다!" << endl;
            }
        }
        else if (choice == 2) { // 회피
            player.evadeChance += 0.1f; // 회피 확률 증가
            cout << player.name << "이(가) 회피 자세를 취했습니다!" << endl;
        }
        else if (choice == 3) { // 스킬 사용
            cout << "사용할 스킬을 선택하세요:\n1. 스킬 1\n2. 스킬 2\n";
            int skillChoice;
            cin >> skillChoice;
            player.useSkill(skillChoice, enemyCopy);
        }
        else {
            cout << "잘못된 선택입니다! 턴을 잃었습니다." << endl;
        }

        if (enemyCopy.health <= 0) {
            cout << enemyCopy.name << "이(가) 패배했습니다!" << endl;
            player.gainExperience(enemyCopy.experienceReward); // 경험치 획득
            player.health += 10; // 적을 무찔렀을 때 체력 회복
            cout << player.name << "이(가) 체력을 10 회복했습니다!" << endl;
            return;
        }

        // 적 턴
        cout << "\n" << enemyCopy.name << "의 턴!" << endl;
        if (!player.evadeAttack()) { // 플레이어가 회피하지 못하면 공격
            int damage = enemyCopy.attack - player.defense / 2; // 방어력 적용
            player.takeDamage(damage);
            cout << enemyCopy.name << "이(가) " << player.name << "에게 " << damage << "의 피해를 입혔습니다!" << endl;
        }
        else {
            cout << player.name << "이(가) 공격을 회피했습니다!" << endl;
        }

        if (player.health <= 0) {
            cout << player.name << "이(가) 패배했습니다!" << endl;
            return;
        }

        // 현재 체력 출력
        cout << player.name << " 체력: " << player.health << ", " << enemyCopy.name << " 체력: " << enemyCopy.health << endl;
    }
}

// 메인 함수
int main() {
    srand(static_cast<unsigned int>(time(0))); // 랜덤 시드 초기화

    string playerName, playerJob;
    cout << "당신의 캐릭터 이름을 입력하세요: ";
    cin >> playerName;
    cout << "직업을 선택하세요 (전사, 마법사, 도적, 요리사, 사냥꾼, 검투사, 성직자, 방패기사): ";
    cin >> playerJob;

    Character player(playerName, playerJob);

    // 적 목록 생성
    Enemy enemies[] = {
        Enemy("나무인형", 20, 3, 0.1f, 30),
        Enemy("슬라임", 25, 4, 0.15f, 40),
        Enemy("고블린", 30, 5, 0.2f, 50),
        Enemy("오크", 40, 7, 0.25f, 70),
        Enemy("미노타우로스", 50, 10, 0.3f, 100),
        Enemy("와이번", 60, 12, 0.35f, 150),
        Enemy("리치", 80, 15, 0.4f, 200),
        Enemy("드래곤", 100, 20, 0.5f, 300)
    };

    for (const auto& enemy : enemies) {
        cout << "야생의 " << enemy.name << "이(가) 나타났습니다!" << endl;
        battle(player, enemy); // const Enemy&로 전달
        if (player.health <= 0) {
            cout << "게임 오버!" << endl;
            break;
        }
    }

    return 0;
}
