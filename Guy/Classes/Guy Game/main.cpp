#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Monster class
class Monster
{
public:
    int hp;
    int position;
    bool hpAssigned;
    Monster(int pos)
    {
        hp = 0;
        position = pos;
        hpAssigned = false;
    }

    void rollHP()
    {
        if (!hpAssigned)
        {
            hp = rand() % 5 + 3; // Dice roll: 3-7
            hpAssigned = true;
        }
    }
};

// Player class
class Player
{
public:
    int position;
    int xp;
    int level;
    string weapon;
    int attackBonus;
    int baseDamageMax;
    Player()
    {
        position = 0;
        xp = 0;
        level = 1;
        weapon = "fists";
        attackBonus = 0;
        baseDamageMax = 3; // Starts with 1-3 damage
    }

    bool updateWeapon(string newWeapon, int newBonus)
    {
        if (newBonus > attackBonus)
        {
            weapon = newWeapon;
            attackBonus = newBonus;
            return true;
        }
        return false;
    }

    void checkLevelUp()
    {
        if (level == 1 && xp >= 8)
        {
            level = 2;
            baseDamageMax = 4;
            cout << "Level up! Reached Level 2 - Base damage increased to 1-4!\n";
        }
        else if (level == 2 && xp >= 16)
        {
            level = 3;
            baseDamageMax = 5;
            cout << "Level up! Reached Level 3 - Base damage increased to 1-5!\n";
        }
        else if (level == 3 && xp >= 24)
        {
            level = 4;
            baseDamageMax = 6;
            cout << "Level up! Reached Level 4 - Base damage increased to 1-6!\n";
        }
    }
};

// Board class
class Board
{
private:
    vector<char> grid;
    vector<Monster> monsters;
    Player player;
    vector<pair<int, string>> weapons;
    int boardSize;

    string generateWeaponName()
    {
        string prefixes[] = {"Blood-", "Gore-", "Death-", "Skull-", "Rot-", "Plague-", "Doom-"};
        string bases[] = {"reaver", "shredder", "mauler", "grinder", "flayer", "crusher", "rend"};
        string suffixes[] = {" of Dismemberment", " of Eternal Woe", " of Gut-Spilling",
                             " of Bone-Snapping", " of Flesh-Ripping", " of Soul-Eating",
                             " of Corpse-Twisting"};

        string name = prefixes[rand() % 7] + bases[rand() % 7] + suffixes[rand() % 7];
        return name;
    }

    bool hasMonster(int pos)
    {
        for (const auto &monster : monsters)
        {
            if (monster.position == pos)
            {
                return true;
            }
        }
        return false;
    }

public:
    Board()
    {
        srand(static_cast<unsigned int>(time(0)));
        boardSize = rand() % 21 + 20; // 20 to 40
        grid.resize(boardSize, '*');
        grid[0] = 'P'; // Initial player position

        int maxMonsters = min(18, boardSize - 2);
        int minMonsters = min(10, maxMonsters);
        int monsterCount = rand() % (maxMonsters - minMonsters + 1) + minMonsters;
        int monstersPlaced = 0;
        while (monstersPlaced < monsterCount)
        {
            int pos = rand() % boardSize;
            if (grid[pos] == '*')
            {
                monsters.push_back(Monster(pos));
                grid[pos] = 'M';
                monstersPlaced++;
            }
        }

        int weaponsPlaced = 0;
        while (weaponsPlaced < 5)
        {
            int pos = rand() % boardSize;
            if (grid[pos] == '*')
            {
                weapons.push_back(pair<int, string>(pos, generateWeaponName()));
                grid[pos] = 'W';
                weaponsPlaced++;
            }
        }
    }

    void display()
    {
        for (int i = 0; i < boardSize; i++)
        {
            if (i == player.position && hasMonster(i))
            {
                cout << "P/M "; // Player and monster together
            }
            else if (i == player.position)
            {
                cout << "P "; // Player only
            }
            else if (hasMonster(i))
            {
                cout << "M "; // Monster only
            }
            else
            {
                cout << grid[i] << " "; // Empty or weapon
            }
        }
        cout << "\nPosition: " << player.position
             << " | XP: " << player.xp
             << " | Level: " << player.level
             << " | Weapon: " << player.weapon
             << " (+" << player.attackBonus << ")\n";
    }

    void movePlayer()
    {
        int oldPosition = player.position;
        player.position = (player.position + 1) % boardSize;

        if (!hasMonster(oldPosition))
        {
            grid[oldPosition] = '*';
        }

        for (size_t i = 0; i < monsters.size(); i++)
        {
            if (monsters[i].position == player.position)
            {
                monsters[i].rollHP();
                cout << "Monster encountered at position " << player.position
                     << " with " << monsters[i].hp << " HP!\n";
                break;
            }
        }

        for (size_t i = 0; i < weapons.size(); i++)
        {
            if (weapons[i].first == player.position)
            {
                int newBonus = rand() % 7 + 3; // 3 to 9
                string newWeapon = weapons[i].second;

                if (player.updateWeapon(newWeapon, newBonus))
                {
                    cout << "Picked up better weapon: " << player.weapon
                         << " (+" << newBonus << ")!\n";
                    weapons.erase(weapons.begin() + static_cast<ptrdiff_t>(i));
                    if (!hasMonster(player.position))
                    {
                        grid[player.position] = '*';
                    }
                }
                else
                {
                    cout << "Found " << newWeapon << " (+" << newBonus << ") but kept "
                         << player.weapon << " (+" << player.attackBonus << ") (better bonus)\n";
                    weapons.erase(weapons.begin() + static_cast<ptrdiff_t>(i));
                    if (!hasMonster(player.position))
                    {
                        grid[player.position] = '*';
                    }
                }
                break;
            }
        }
    }

    bool fight()
    {
        for (size_t i = 0; i < monsters.size(); i++)
        {
            if (monsters[i].position == player.position)
            {
                if (!monsters[i].hpAssigned)
                {
                    monsters[i].rollHP();
                }
                int diceRoll = rand() % player.baseDamageMax + 1;
                int damage = diceRoll + player.attackBonus;
                cout << "Attacking with " << player.weapon << ": Rolled " << diceRoll
                     << " + " << player.attackBonus << " = " << damage << " damage!\n";
                monsters[i].hp -= damage;

                if (monsters[i].hp <= 0)
                {
                    cout << "Monster defeated! +2 XP\n";
                    player.xp += 2;
                    player.checkLevelUp();
                    monsters.erase(monsters.begin() + static_cast<ptrdiff_t>(i));
                    grid[player.position] = '*';
                    i--;
                }
                else
                {
                    cout << "Monster HP remaining: " << monsters[i].hp << "\n";
                }
            }
        }
        return monsters.empty();
    }

    bool isGameOver()
    {
        return monsters.empty();
    }

    Player &getPlayer()
    {
        return player;
    }
};

// Main class/game loop
int main()
{
    Board game;
    int choice;

    cout << "Welcome to Monster Slayer!\n";

    while (!game.isGameOver())
    {
        game.display();
        cout << "\n1. Travel\n2. Fight\nChoice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            game.movePlayer();
            break;
        case 2:
            game.fight();
            break;
        default:
            cout << "Invalid choice!\n";
        }
    }

    game.display();
    cout << "\nAll monsters defeated! You win!\n";
    cout << "Final Stats - Level: " << game.getPlayer().level
         << " | XP: " << game.getPlayer().xp << "\n";

    return 0;
}