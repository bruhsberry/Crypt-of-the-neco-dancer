#include <SFML/Graphics.hpp>
//#include <vector>
//#include <fstream>
#include <thread>
//#include "Map.h"
#include "Player.h"
//#include "Weapon.h"

using namespace sf;
using namespace std;
#define CELL 64
#define WIN_HEIGHT board.height*CELL
#define WIN_LENGTH board.length*CELL
#define LIGHT_RAD 6
//Map board = Map("1.txt");
Map board = Map("level1.txt");

Player player = Player(9, 9);
View mainView(FloatRect(0.f, 0.f, 10 * CELL, 10 * CELL));
Event event;
vector<vector<float>> light, lightTemp;

enum tex { playerSprite, wallTex, dirtTex, greenSlimeTex, blueSlimeTex, redSlimeTex,
    purpleSlimeTex, notexture, batTex, skeletonTex, zombieTex, stoneSwordTex, 
    goldSwordTex, ironSwordTex, stoneBroadswordTex, ironBroadswordTex,
    goldBroadswordTex, goldTex, shadow};
#define TEXTURES_AMOUNT 19
vector<Texture> textures;
void loadTextures() {
    textures.resize(TEXTURES_AMOUNT);
    textures[tex::playerSprite].loadFromFile("Sprites\\neko.png");
    textures[tex::wallTex].loadFromFile("Sprites\\wall.png");
    textures[tex::dirtTex].loadFromFile("Sprites\\dirt.png");
    textures[tex::greenSlimeTex].loadFromFile("Sprites\\greenslime.png");
    textures[tex::redSlimeTex].loadFromFile("Sprites\\redslime.png");
    textures[tex::purpleSlimeTex].loadFromFile("Sprites\\purpleslime.png");
    textures[tex::blueSlimeTex].loadFromFile("Sprites\\blueslime.png");
    textures[tex::batTex].loadFromFile("Sprites\\bat.png");
    textures[tex::skeletonTex].loadFromFile("Sprites\\skeleton.png");
    textures[tex::zombieTex].loadFromFile("Sprites\\zombie.png");
    textures[tex::goldTex].loadFromFile("Sprites\\gold.png");
    textures[tex::stoneSwordTex].loadFromFile("Sprites\\stone sword.png");
    textures[tex::stoneBroadswordTex].loadFromFile("Sprites\\stone broadsword.png");
    textures[tex::goldSwordTex].loadFromFile("Sprites\\gold sword.png");
    textures[tex::goldBroadswordTex].loadFromFile("Sprites\\gold broadsword.png");
    textures[tex::ironSwordTex].loadFromFile("Sprites\\iron sword.png");
    textures[tex::ironBroadswordTex].loadFromFile("Sprites\\iron broadsword.png");
    textures[tex::notexture].loadFromFile("Sprites\\aaaa.png");
    textures[tex::shadow].loadFromFile("Sprites\\shadow.png");
}

void render() {
    sf::Vector2f worldPos(0, 0);
    RenderWindow window(VideoMode(800, 800), L"Crypt of the necodancer!", Style::Default);
    window.setVerticalSyncEnabled(true);
    mainView.setCenter(player.x * CELL + CELL / 2, player.y * CELL + CELL / 2);
    window.setView(mainView);
    loadTextures();
    

    Sprite sprite;
    Sprite shadow;
    shadow.setTexture(textures[tex::shadow]);
    while (window.isOpen())
    {
        window.setView(mainView);
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        //sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
       // // convert it to world coordinates
       // worldPos = window.mapPixelToCoords(pixelPos);
       // worldPos.x = worldPos.x / CELL;
       // worldPos.y = worldPos.y / CELL;


        window.clear(Color::Black);
        for (int i = 0; i <board.length; i++)
        {
            for (int j = 0; j < board.height; j++)
            {

                sprite.setPosition(i* CELL, j* CELL);

                switch (board.m[i][j].tile) {
                case 1: {
                    sprite.setTexture(textures[tex::wallTex]);
                    break;
                }
                case 0: {
                    sprite.setTexture(textures[tex::dirtTex]);
                    break;
                }
                }

                window.draw(sprite);
                if (board.m[i][j].gold) sprite.setTexture(textures[tex::goldTex]);
                window.draw(sprite);
            }
        }

        for (int i = 0; i < board.it.size(); i++)
        {
            if (board.it[i] == nullptr) continue;
            if (board.it[i]->held) continue;
            switch (board.it[i]->typeOf()) {
            case items::testArmor:
                sprite.setTexture(textures[tex::notexture]);
                break;
            case items::testSword:
                sprite.setTexture(textures[tex::stoneSwordTex]);
                break;
            case items::ironSword:
                sprite.setTexture(textures[tex::ironSwordTex]);
                break;
            default:
                sprite.setTexture(textures[tex::notexture]);
                break;

            }
            sprite.setPosition(board.it[i]->x * CELL, board.it[i]->y * CELL);
            window.draw(sprite);
        }

        for (int i = 0; i < board.e.size(); i++)
        {
            if (board.e[i] == nullptr) continue;
            switch (board.e[i]->typeOf()) {
            case enemyTypes::greenSlime:
                sprite.setTexture(textures[tex::greenSlimeTex]);
                break;
            case enemyTypes::blueSlime:
                sprite.setTexture(textures[tex::blueSlimeTex]);
                break;
            case enemyTypes::purpleSlime:
                sprite.setTexture(textures[tex::purpleSlimeTex]);
                break;
            case enemyTypes::redSlime:
                sprite.setTexture(textures[tex::redSlimeTex]);
                break;
            case enemyTypes::zombie:
                sprite.setTexture(textures[tex::zombieTex]);
                break;
            case enemyTypes::bat:
                sprite.setTexture(textures[tex::batTex]);
                break;
            case enemyTypes::skeleton:
                sprite.setTexture(textures[tex::skeletonTex]);
                break;
            default:
                sprite.setTexture(textures[tex::notexture]);
                break;

            }
            sprite.setPosition(board.e[i]->x * CELL, board.e[i]->y * CELL);
            window.draw(sprite);
        }
        
        sprite.setPosition(player.x * CELL, player.y * CELL);
        sprite.setTexture(textures[tex::playerSprite]);
        window.draw(sprite);

        for (int i = 0; i < board.height; i++) {
            for (int j = 0; j < board.length; j++)
            {
                shadow.setPosition(j * CELL, i * CELL);
                shadow.setColor(sf::Color(0, 0, 0, 255 * (1 - light[j][i])));
                window.draw(shadow);
            }
        }


        window.display();
    }
}

void enemyUpd() {
    for (int i = 0; i < board.e.size(); i++)
    {
        if (board.e[i] == nullptr) continue;
        int attack = board.e[i]->update(&board, player.x, player.y);
        if (attack) player.takeDamage(attack);
    }
}

void smoothStep(int dir){
    int destination;
    switch (dir)
    {
    case directions::right: {
        destination = player.x + 1;
        while (player.x < destination) {
            player.x += 0.01;
            mainView.setCenter(player.x * CELL + CELL / 2, player.y * CELL + CELL / 2);
            sleep(milliseconds(1));
        }
        player.x = floor(player.x);
        break;
    }
    case directions::left: {
        destination = player.x - 1;
        while (player.x  > destination) {
            player.x -= 0.01;
            mainView.setCenter(player.x * CELL + CELL / 2, player.y * CELL + CELL / 2);
            sleep(milliseconds(1));
        }

        player.x = ceil(player.x);
        break;
    }
    case directions::up: {
        destination = player.y - 1;
        while (player.y > destination) {
            player.y -= 0.01;
            mainView.setCenter(player.x * CELL + CELL / 2, player.y * CELL + CELL / 2);
            sleep(milliseconds(1));
        }
        player.y = ceil(player.y);
        break;
    }
    case directions::down: {
        destination = player.y + 1;
        while (player.y < destination) {
            player.y += 0.01;
            mainView.setCenter(player.x * CELL + CELL / 2, player.y * CELL + CELL / 2);
            sleep(milliseconds(1));
        }
        player.y = floor(player.y);
        break;
    }
    default:
        break;
    }
}

void checkItems() {
    if (board.m[player.x][player.y].item != nullptr) {
        Weapon* tempw;
        Armor* tempa;
        board.m[player.x][player.y].item->held = true;

        switch (board.m[player.x][player.y].item->type())
        {
        case weapon:
            if (player.weapon->name == "No weapon") {
                delete(player.weapon);
                player.weapon = nullptr;
            }
            tempw = player.weapon;
            player.weapon = dynamic_cast <Weapon*> (board.m[player.x][player.y].item);
            board.m[player.x][player.y].item = tempw;
            break;
        case armor:
            if (player.armor->name == "No armor") {
                delete(player.armor);
                player.armor = nullptr;
            }
            tempa = player.armor;
            player.armor = dynamic_cast <Armor*> (board.m[player.x][player.y].item);
            board.m[player.x][player.y].item = tempa;
            break;
        default:
            break;
        }
        if (board.m[player.x][player.y].item != nullptr) {
            board.m[player.x][player.y].item->held = false;
            board.m[player.x][player.y].item->x = player.x;
            board.m[player.x][player.y].item->y = player.y;
        }
    }
    if (board.m[player.x][player.y].gold) {
        player.gold += board.m[player.x][player.y].gold;
        board.m[player.x][player.y].gold = 0;
    }

}

int clampx(int value) {
    return min(max(value, 0), board.length-1);
}
int clampy(int value) {
    return min(max(value, 0), board.height - 1);
}

void lightRec(int x, int y, int value) {
    lightTemp[x][y] = value;
    if (value > 1 && board.m[x][y].tile < tile::wall) {
        if (y > 0 && lightTemp[x][y-1] < value) lightRec(x, y - 1, value - 1);
        if (y < board.height - 1 && lightTemp[x][y+1] < value) lightRec(x, y + 1, value - 1);
        if (x < board.length - 1 && lightTemp[x+1][y] < value) lightRec(x + 1, y, value - 1);
        if (x > 0 && lightTemp[x-1][y] < value) lightRec(x - 1, y, value - 1);
    }
}
void lightUpdate() {
    lightTemp.clear();
    lightTemp.resize(board.length);
    for (int i = 0; i < board.length; i++) 
        lightTemp[i].resize(board.height);
    lightRec(player.x, player.y, LIGHT_RAD);
    for (int i = 0; i < board.height; i++) 
        for (int j = 0; j < board.length; j++)
            lightTemp[j][i] /= LIGHT_RAD;
    light = lightTemp;
}
void control() {
    srand(time(NULL));
    bool buttonPressed = false;
    while (true)
    {
        if (event.type == sf::Event::KeyPressed) {

            switch (event.key.code) {
            case sf::Keyboard::Left:
                if (player.x > 0 && board.m[max((int)player.x - 1, 0)][player.y].tile != wall && !buttonPressed && !player.weapon->attack(directions::left, &board, player.x, player.y)) {
                    smoothStep(directions::left);
                    enemyUpd();
                    checkItems();
                }
                break;
            case sf::Keyboard::Right:
                if (player.x < board.length-1 && board.m[min((int)player.x + 1, board.length)][player.y].tile != wall && !buttonPressed && !player.weapon->attack(directions::right, &board, player.x, player.y)) {
                    smoothStep(directions::right);
                    enemyUpd();
                    checkItems();
                }
                break;
            case sf::Keyboard::Up:
                if (player.y > 0 && board.m[player.x][max((int)player.y - 1, 0)].tile != wall && !buttonPressed && !player.weapon->attack(directions::up, &board, player.x, player.y)) {
                    smoothStep(directions::up);
                    enemyUpd();
                    checkItems();
                }
                break;
            case sf::Keyboard::Down:
                if (player.y < board.height-1 && board.m[player.x][min((int)player.y + 1, board.height)].tile != wall && !buttonPressed && !player.weapon->attack(directions::down, &board, player.x, player.y)) {
                    smoothStep(directions::down);
                    enemyUpd();
                    checkItems();
                }
                break;
            case sf::Keyboard::Space :
                if(!buttonPressed)
                    enemyUpd();
                break;
            }
            if (!buttonPressed) {
                lightUpdate();
            }
            buttonPressed = true;
        }
        else buttonPressed = false;
    }
}
void fullbright() {
    light.clear();
    light.resize(board.length);
    for (int i = 0; i < board.length; i++) {
        light[i].resize(board.height);
        for (int j = 0; j < board.height; j++)
        {
            light[i][j] = 1;
        }
    }
}
int main()
{
    lightUpdate();
    srand(time(NULL));
    
    thread rend(render);
    thread ctr(control);
    rend.join();
    ctr.join();
}