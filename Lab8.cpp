#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

void CreateCharacter();
void HUD();
void Combat();
void CombatHUD();
void Moving();
void CreateMonster();
void LevelUp();
void EndGame();

string name = " ", race = " ", sex = " ";
int level = 0, xp = 0, health = 0, totalHealth = 0,
    maxHealth = 0, nextLevel = 0, heal = 0, monsterHp = 0,
    monsterXp = 0, monsterLevel = 0, raceDamageModifier = 0,
    evasionStat = 0;

string monsterName[] = {"Goblin", "Dwarf", "Ogre", "Witch", "Demon", "Wizard"};
int currentMonsterNames = 5;
string currentMonster = " ";
 
string playerRace[] = {"Elf", "Dwarf", "Human", "Elemental", "Half-Orc"};

int main()
{

    srand(time(0));

    level = 1;
    xp = 0;
    nextLevel = 76;

    CreateCharacter();

    totalHealth = health;
    maxHealth = totalHealth;

    HUD();
    Moving();

    system("pause");
    return 0;
}

void CreateCharacter()
{
    cout << "Enter Character's Name: ";
    cin >> name;

    cout << "Enter Character's Race\n\n";
    cout << "- Elf\n";
    cout << "- Dwarf\n";
    cout << "- Human\n";
    cout << "- Elemental\n";
    cout << "- Half Orc\n\n";

    while(true){
        cout << "Enter your choice: ";
        cin >> race;

        for_each(race.begin(), race.end(), [](char & c){
            c = tolower(c);
        });

        if(race == "elf"){
            health = 80;
            raceDamageModifier = 1;
            evasionStat = 40;
            race = "Elf";
            break;
        }
        else if(race == "dwarf"){
            health = 120;
            raceDamageModifier = 0;
            evasionStat = 60;
            race = "Dwarf";
            break;
        }
        else if(race == "human"){
            health = 100;
            raceDamageModifier = 0;
            evasionStat = 50;
            race = "Human";
            break;
        }
        else if(race == "elemental"){
            health = 60;
            raceDamageModifier = 2;
            evasionStat = 35;
            race = "Elemental";
            break;
        }
        else if(race == "half orc"){
            health = 140;
            raceDamageModifier = 0;
            evasionStat = 65;
            race = "Half-Orc";
            break;
        }
        else{
            cout << "Invalid Choice, please choose again.\n";
        }
    }

    cout << "Enter Character's Sex: ";
    cin >> sex;

    sex[0] = toupper(sex[0]);
    name[0] = toupper(name[0]);

    // Fancy animation
    system("cls");
    cout << "Creating Character.\n";
    Sleep(500);
    system("cls");

    cout << "Creating Character..\n";
    Sleep(500);
    system("cls");

    cout << "Creating Character...\n";
    Sleep(500);
    system("cls");
}

void HUD()
{
    Sleep(500);
    system("cls");
    cout << "Name : " << name << "      Health: " << totalHealth << "\nRace: " << race
         << "\nSex: " << sex << "\nLevel: " << level << "\nxp: " << xp << "\nXp to Level: " << nextLevel << endl;

    Moving();
}

void Moving()
{

    int choice;

    cout << "\n\n";
    cout << "1. Move Forward\n";
    cout << "2. Relax\n";
    cout << "3. Move Backwards\n";
    cout << "\n";

    cin >> choice;

    if (choice == 1)
    {
        int temp = rand() % 100 + 1;
        cout << "You begin moving forward...\n";
        if (temp >= 50)
        {
            // Encounter monster
            CreateMonster();
            string tempName = monsterName[rand() % currentMonsterNames];
            cout << "A " << tempName << "! Prepare to Fight\n";
            currentMonster = tempName;
            Sleep(1000);
            Combat();
        }
        cout << "You find nothing of interest.\n";
        Sleep(1000);
        HUD();
    }
    else if (choice == 2)
    {
        cout << "You want to set up camp for the evening\n";
        if (totalHealth <= maxHealth - 1)
        {
            totalHealth += 5 + (level * 5) ;
        }
        if (totalHealth >= maxHealth)
        {
            totalHealth = maxHealth;
            cout << "You have returned to max health!" << endl;
        }
        else{
            cout << "You healed by resting. Health is now " << totalHealth << endl;
        }
        Sleep(1000);
        HUD();
    }
    else if (choice == 3)
    {
        int temp = rand() % 100 + 1;
        cout << "You begin moving backwards...\n";
        if (temp >= 50)
        {
            // Encounter monster
            CreateMonster();
            string tempName = monsterName[rand() % currentMonsterNames];
            cout << "A " << tempName << "! Prepare to Fight\n";
            currentMonster = tempName;
            Sleep(1000);
            Combat();
        }
        cout << "You find nothing of interest.\n";
        Sleep(1000);
        HUD();
    }
    else
    {
        cout << "Invalid Number\n";
        Sleep(500);
        Moving();
    }
}

void CreateMonster()
{
    monsterHp = 30;
    monsterLevel = (rand() % 3) + level;

    monsterHp = (rand() % 30) * monsterLevel;

    monsterXp = monsterHp;

    if (monsterHp == 0)
    {
        CreateMonster();
    }
    if (monsterLevel == 0)
    {
        CreateMonster();
    }
}

void CombatHUD()
{
    Sleep(500);
    system("cls");
    cout << "Name: " << name << "       |       Monster Name: " << currentMonster << "\nHealth: " << totalHealth << "       |       Monster Health: " << monsterHp << "\nLevel: " << level << "        |       Monster Level: " << monsterLevel << endl;
}

void Combat()
{
    CombatHUD();
    int playerAttack;
    int playerDamage = (8 * level / 2) + (raceDamageModifier * level / 2);
    int monsterAttack = 6 * monsterLevel / 2;

    if (totalHealth >= 1 && monsterHp >= 1)
    {
        cout << "\n";
        cout << "1. Attack\n";
        cout << "2. Block\n";
        cout << "3. RUN!\n";
        cout << "\n";
        cin >> playerAttack;

        if (playerAttack == 1)
        {
            // Attack
            cout << "Attacking... you did " << playerDamage << " damage to the " << currentMonster << endl;
            monsterHp -= playerDamage;
            Sleep(1000);
            CombatHUD();
            if (monsterHp >= 1)
            {
                cout << "\n";
                cout << "The Monster is Attacking...\n";
                totalHealth -= monsterAttack;
                cout << "You suffered " << monsterAttack << " dmanage, HP is now " << totalHealth << endl;

                // change to function

                if (totalHealth <= 0)
                {
                    totalHealth = 0;
                    system("cls");
                    EndGame();
                }
            }
            else if (monsterHp <= 0)
            {
                monsterHp = 0;
                cout << "\n";
                cout << "You Defeated " << currentMonster << ", you are rewarded with " << monsterXp << " xp.\n";
                Sleep(1000);
                LevelUp();
                HUD();
            }
            Sleep(1000);
            Combat();
        }
        else if (playerAttack == 2)
        {
            // Block
            cout << "Blocking...\n";
            int i = rand() % 100 + 1;
            if (i >= evasionStat)
            {
                cout << "You Blocked the incoming attack\n";
                heal = maxHealth / 10;
                cout << "You have been healed for " << heal << endl;
                totalHealth += heal;
                if (totalHealth >= maxHealth)
                {
                    totalHealth = maxHealth;
                }
                Sleep(1000);
                Combat();
            }
            else
            {
                cout << "You failed to block the monster's attack\n";
                totalHealth -= monsterAttack;
                if (totalHealth <= 0)
                {
                    totalHealth = 0;
                    cout << "You were stabbed in the back for " << monsterAttack << " damage. That's Lethal!" << endl;
                    Sleep(1000);
                    system("cls");
                    EndGame();
                }
                cout << "You were stabbed in the back for " << monsterAttack << " damage. Current HP: " << totalHealth << endl;
                Sleep(1000);
                Combat();
            }
        }
        else if (playerAttack == 3)
        {
            // Run
            cout << "You try to run away\n";
            int x = rand() % 100 + 1;
            if (x >= 50)
            {
                cout << "You successfully run away!\n";
                HUD();
            }
            else
            {
                cout << "You failed to run away\n";
                cout << "The monster lands a crushing blow!";
                totalHealth -= monsterAttack + 10;
                if (totalHealth <= 0)
                {
                    totalHealth = 0;
                    cout << "You sustained a crushing blow for " << monsterAttack << " damage. That's Lethal!" << endl;
                    Sleep(1000);
                    system("cls");
                    EndGame();
                }
                cout << "The monster dealt you " << monsterAttack + 10 << " damage. Current HP is " << totalHealth << endl;
                Sleep(1000);
                Combat();
            }
        }
        else
        {
            cout << "Invalid Number\n";
            Sleep(500);
            Combat();
        }
    }
}

void LevelUp()
{
    xp += monsterXp;

    if (xp >= nextLevel)
    {
        level++;
        xp -= nextLevel;
        nextLevel = (nextLevel * 3) / 2;
        maxHealth += 20;
        totalHealth = maxHealth;
        cout << "You're leveling up! You are now level: " << level << endl;
        cout << "Your max health is now " << maxHealth << " and you've been fully healed" << endl;
        Sleep(2000);
        HUD();
    }
}

void EndGame()
{
    cout << "You Died!\nYou were level: " << level << "\nYou were killed by a " << currentMonster << endl;
    Sleep(5000);
    exit(0);
}