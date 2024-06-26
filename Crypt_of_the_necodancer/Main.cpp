#include <SFML/Graphics.hpp>
#include <thread>
#include "Game.h"

using namespace sf;
using namespace std;
#define CELL 64
#define WIN_HEIGHT game.board.height*CELL
#define WIN_LENGTH game.board.length*CELL
#define LIGHT_RAD 6
bool started = false, changingLevelLock = false, changingLevelAnswer = false, gameOver = false, closing = false;
int attackAnim = 4;
Game game("levels\\\\bonuslevel.txt");
View mainView(FloatRect(0.f, 0.f, 10 * CELL, 10 * CELL));
Event event;
vector<vector<float>> light, lightTemp;

enum tex { playerTex, wallTex, dirtTex, exitTex, greenSlimeTex, blueSlimeTex, redSlimeTex,
    purpleSlimeTex, notexture, batTex, skeletonTex, zombieTex, ironSwordTex, 
    goldSwordTex, titaniumSwordTex, ironBroadswordTex, titaniumBroadswordTex,
    goldBroadswordTex, goldTex, shadow, woodenTorchTex, steelTorchTex, magicTorchTex,
    ironSpearTex, titaniumSpearTex, goldSpearTex, letherArmorTex, chainArmorTex, 
    plateArmorTex, chestTex
};
#define TEXTURES_AMOUNT 30
vector<Texture> textures, hearts, attackTex;
void loadTextures() {
    textures.resize(TEXTURES_AMOUNT);
    textures[tex::playerTex].loadFromFile("Sprites\\neko.png");
    textures[tex::wallTex].loadFromFile("Sprites\\wall.png");
    textures[tex::dirtTex].loadFromFile("Sprites\\dirt.png");
    textures[tex::exitTex].loadFromFile("Sprites\\exit.png");
    textures[tex::greenSlimeTex].loadFromFile("Sprites\\greenslime.png");
    textures[tex::redSlimeTex].loadFromFile("Sprites\\redslime.png");
    textures[tex::purpleSlimeTex].loadFromFile("Sprites\\purpleslime.png");
    textures[tex::blueSlimeTex].loadFromFile("Sprites\\blueslime.png");
    textures[tex::batTex].loadFromFile("Sprites\\bat.png");
    textures[tex::skeletonTex].loadFromFile("Sprites\\skeleton.png");
    textures[tex::zombieTex].loadFromFile("Sprites\\zombie.png");
    textures[tex::goldTex].loadFromFile("Sprites\\gold.png");
    textures[tex::shadow].loadFromFile("Sprites\\shadow.png");
    textures[tex::chestTex].loadFromFile("Sprites\\chest.png");
    hearts.resize(6);
    for (int i = 0; i < 6; i++)
        hearts[i].loadFromFile("Sprites\\hp\\" + to_string(i + 1) + "hp.png");
    attackTex.resize(9);
        attackTex[0].loadFromFile("Sprites\\attack anim\\sword0.png");
        attackTex[1].loadFromFile("Sprites\\attack anim\\sword1.png");
        attackTex[2].loadFromFile("Sprites\\attack anim\\sword2.png");
        attackTex[3].loadFromFile("Sprites\\attack anim\\broadsword0.png");
        attackTex[4].loadFromFile("Sprites\\attack anim\\broadsword1.png");
        attackTex[5].loadFromFile("Sprites\\attack anim\\broadsword2.png");
        attackTex[6].loadFromFile("Sprites\\attack anim\\spear0.png");
        attackTex[7].loadFromFile("Sprites\\attack anim\\spear1.png");
        attackTex[8].loadFromFile("Sprites\\attack anim\\spear2.png");
    
}

void render() {
    Vector2f worldPos(0, 0);
    Clock clock;
    RenderWindow window(VideoMode(800, 800), L"Crypt of the necodancer!", Style::Close);
    window.setVerticalSyncEnabled(true);
    mainView.setCenter(game.player.x * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
    //window.setView(mainView);
    loadTextures();
    Text priceText, statsText;
    Font goldFont;
    goldFont.loadFromFile("Sprites\\joystix.monospace-regular.otf");
    priceText.setFont(goldFont);
    priceText.setScale(0.6, 0.6);
    priceText.setOrigin(35, 2);
    statsText.setFont(goldFont);
    statsText.setScale(0.6, 0.6);

    Sprite sprite, shadow, playerSprite, enemySprite, startSprite, borderSprite, iconSprite, attackSprite;
    shadow.setTexture(textures[tex::shadow]);
    playerSprite.setTexture(textures[tex::playerTex]);
    playerSprite.setOrigin(CELL / 2, CELL / 2);
    enemySprite.setOrigin(CELL / 2, CELL / 2);
 

    Texture start, border;
    border.loadFromFile("Sprites\\border.png");
    borderSprite.setTexture(border);
    borderSprite.setOrigin(32, 32);
    iconSprite.setOrigin(32, 32);
    iconSprite.setScale(0.5, 0.5);

    start.loadFromFile("Sprites\\start.png");
    startSprite.setTexture(start);
    window.clear(Color::Black);
    window.draw(startSprite);
    window.display();

    while (!started) {
        while (window.pollEvent(event)) {
            sleep(milliseconds(1));
        }
    }
    while (window.isOpen())
    {  
        while (game.player.gameover) {
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) {
                    window.close();
                    closing = true;
                }
            }
            start.loadFromFile("Sprites\\death.png");
            startSprite.setOrigin(400, 400);
            startSprite.setPosition(game.player.x * CELL + CELL/2, game.player.y * CELL + CELL / 2);
            window.draw(startSprite);
            window.display();
        }
        window.setView(mainView);
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
                closing = true;
            }
        }
        if (closing) break;
        window.clear(Color::Black);
        while (changingLevelLock) {
            changingLevelAnswer = true;
            sleep(milliseconds(1));
        }


        for (int i = 0; i <game.board.length; i++)
        {
            for (int j = 0; j < game.board.height; j++)
            {
                sprite.setPosition(i* CELL, j* CELL);
                switch (game.board.m[i][j].tile) {
                case tile::wall: 
                    sprite.setTexture(textures[tex::wallTex]);
                    break;
                
                case tile::empty: 
                    sprite.setTexture(textures[tex::dirtTex]);
                    break;
                
                case tile::exitDoor: 
                    sprite.setTexture(textures[tex::exitTex]);
                    break;
                default:
                    sprite.setTexture(textures[tex::notexture]);
                    break;
                }
                window.draw(sprite);
                if (game.board.m[i][j].gold) sprite.setTexture(textures[tex::goldTex]);
                window.draw(sprite);
            }
        }

        for (int i = 0; i < game.board.it.size(); i++)
        {
            if (game.board.it[i] == nullptr) continue;
            if (game.board.it[i]->held) continue;
            sprite.setPosition(game.board.it[i]->x * CELL, game.board.it[i]->y * CELL);
            window.draw(game.board.it[i]->loadSprite());

            if (game.board.it[i]->price > 0) {
                priceText.setString(to_string(game.board.it[i]->price)+"$");
                priceText.setPosition(game.board.it[i]->x * CELL + CELL/2, game.board.it[i]->y * CELL + 45);
                window.draw(priceText);
            }
        }

        for (int i = 0; i < game.board.e.size(); i++)
        {
            while (game.player.weapon->killing) {
                game.player.weapon->killingAnswer = true;
                sleep(milliseconds(0.1));
            }
            if (game.board.e[i] == nullptr) continue;
            switch (game.board.e[i]->typeOf()) {
            case enemyTypes::greenSlime:
                enemySprite.setTexture(textures[tex::greenSlimeTex]);
                enemySprite.setScale(-1.f, 1.f);
                break;
            case enemyTypes::blueSlime:
                enemySprite.setTexture(textures[tex::blueSlimeTex]);
                enemySprite.setScale(-1.f, 1.f);
                break;
            case enemyTypes::purpleSlime:
                enemySprite.setTexture(textures[tex::purpleSlimeTex]);
                enemySprite.setScale(-1.f, 1.f);
                break;
            case enemyTypes::redSlime:
                enemySprite.setTexture(textures[tex::redSlimeTex]);
                enemySprite.setScale(-1.f, 1.f);
                break;
            case enemyTypes::zombie:
                enemySprite.setTexture(textures[tex::zombieTex]);
                if (game.board.e[i]->facingLeft)  enemySprite.setScale(1.f, 1.f);
                else enemySprite.setScale(-1.f, 1.f);
                break;
            case enemyTypes::bat:
                enemySprite.setTexture(textures[tex::batTex]);
                if (game.board.e[i]->facingLeft)  enemySprite.setScale(-1.f, 1.f);
                else enemySprite.setScale(1.f, 1.f);
                break;
            case enemyTypes::skeleton:
                enemySprite.setTexture(textures[tex::skeletonTex]);
                if (game.board.e[i]->facingLeft)  enemySprite.setScale(1.f, 1.f);
                else enemySprite.setScale(-1.f, 1.f);
                break;
            case enemyTypes::chest:
                enemySprite.setTexture(textures[tex::chestTex]);
                enemySprite.setScale(1.f, 1.f);
                break;
            default:
                enemySprite.setTexture(textures[tex::notexture]);
                break;

            }
            enemySprite.setPosition(game.board.e[i]->x * CELL + CELL / 2, game.board.e[i]->y * CELL+ CELL / 2);
            window.draw(enemySprite);
            if (game.board.e[i]->typeOf() != enemyTypes::chest) {
                sprite.setTexture(hearts[min(game.board.e[i]->health - 1, 5)]);
                sprite.setPosition(game.board.e[i]->x * CELL, game.board.e[i]->y * CELL - 40);
                window.draw(sprite);
            }
        }
        
        playerSprite.setPosition(game.player.x * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
        if (game.player.facingLeft) playerSprite.setScale(-1.f, 1.f);
        else playerSprite.setScale(1.f, 1.f);
        window.draw(playerSprite);


        if (attackAnim<3) {
            if (attackAnim == 0) {
                clock.restart();
                attackAnim++;
            }
            if (clock.getElapsedTime().asMilliseconds() > 80.0f) {
                attackAnim++;
                clock.restart();
            }
            
            switch (game.player.weapon->weaponType())
            {
            case 1:
                attackSprite.setTexture(attackTex[attackAnim - 1]);
                attackSprite.setOrigin(CELL / 2, CELL / 2);
                break;
            case 2:
                attackSprite.setTexture(attackTex[attackAnim + 2]);
                attackSprite.setOrigin(CELL / 2 + CELL, CELL / 2);
                break;
            case 3:
                attackSprite.setTexture(attackTex[attackAnim + 5]);
                attackSprite.setOrigin(CELL / 2, CELL / 2 + CELL);
                break;
            default:
                break;
            }
            switch (game.player.lastAttackDir)
            {
            case directions::left:
                attackSprite.setPosition((game.player.x - 1) * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
                attackSprite.setRotation(-90);
                break;
            case directions::right:
                attackSprite.setPosition((game.player.x + 1) * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
                attackSprite.setRotation(+90);
                break;
            case directions::up:
                attackSprite.setPosition(game.player.x * CELL + CELL / 2, (game.player.y - 1) * CELL + CELL / 2);
                attackSprite.setRotation(0);
                break;
            case directions::down:
                attackSprite.setPosition(game.player.x * CELL + CELL / 2, (game.player.y + 1) * CELL + CELL / 2);
                attackSprite.setRotation(180);
                break;
            default:
                attackSprite.setPosition(game.player.x * CELL, game.player.y * CELL);
                break;
            }
            
            window.draw(attackSprite);
        }

        //����
        for (int i = 0; i < game.board.height; i++) {
            for (int j = 0; j < game.board.length; j++)
            {
                shadow.setPosition(j * CELL, i * CELL);
                shadow.setColor(sf::Color(0, 0, 0, 255 * (1 - light[j][i])));
                window.draw(shadow);
            }
        }

        
        borderSprite.setPosition(game.player.x * CELL - 250, game.player.y * CELL - 210);
        window.draw(borderSprite);
        iconSprite = game.player.weapon->loadIcon();
        iconSprite.setPosition(game.player.x* CELL - 250, game.player.y* CELL - 210);
        window.draw(iconSprite);

        borderSprite.setPosition(game.player.x* CELL - 250, game.player.y* CELL - 150);
        window.draw(borderSprite);
        if (game.player.armor != nullptr) {
            iconSprite = game.player.armor->loadIcon();
            iconSprite.setPosition(game.player.x * CELL - 250, game.player.y * CELL - 150);
            window.draw(iconSprite);
        }

        borderSprite.setPosition(game.player.x* CELL - 250, game.player.y* CELL - 90);
        window.draw(borderSprite);
        if (game.player.torch != nullptr) {
            iconSprite = game.player.torch->loadIcon();
            iconSprite.setPosition(game.player.x* CELL - 250, game.player.y* CELL - 90);
            window.draw(iconSprite);
        }

        statsText.setPosition(game.player.x* CELL - 270, game.player.y* CELL - 280);
        statsText.setString("gold: " + to_string(game.player.gold));
        window.draw(statsText);
        statsText.setPosition(game.player.x* CELL - 270, game.player.y* CELL - 260);
        statsText.setString("hp: " + to_string(game.player.health) + "/" + to_string(game.player.maxhealth));
        window.draw(statsText);

        window.display();
    }
}

void enemyUpd() {
    for (int i = 0; i < game.board.e.size(); i++)
    {
        if (game.board.e[i] == nullptr) continue;
        int attack = game.board.e[i]->update(&game.board, game.player.x, game.player.y);
        if (attack) game.player.takeDamage(attack);
    }
}

void smoothStep(int dir){
    int destination;
    switch (dir)
    {
    case directions::right: {
        destination = game.player.x + 1;
        while (game.player.x < destination) {
            game.player.x += 0.01;
            mainView.setCenter(game.player.x * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
            sleep(milliseconds(1));
        }
        game.player.x = floor(game.player.x);
        break;
    }
    case directions::left: {
        destination = game.player.x - 1;
        while (game.player.x  > destination) {
            game.player.x -= 0.01;
            mainView.setCenter(game.player.x * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
            sleep(milliseconds(1));
        }

        game.player.x = ceil(game.player.x);
        break;
    }
    case directions::up: {
        destination = game.player.y - 1;
        while (game.player.y > destination) {
            game.player.y -= 0.01;
            mainView.setCenter(game.player.x * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
            sleep(milliseconds(1));
        }
        game.player.y = ceil(game.player.y);
        break;
    }
    case directions::down: {
        destination = game.player.y + 1;
        while (game.player.y < destination) {
            game.player.y += 0.01;
            mainView.setCenter(game.player.x * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
            sleep(milliseconds(1));
        }
        game.player.y = floor(game.player.y);
        break;
    }
    default:
        break;
    }
}

void checkItems() {
    if (game.board.m[game.player.x][game.player.y].item != nullptr) {
        Weapon* tempw;
        Armor* tempa;
        Torch* tempt;
        if (game.player.gold >= game.board.m[game.player.x][game.player.y].item->price) {
            game.player.gold -= game.board.m[game.player.x][game.player.y].item->price;
            game.board.m[game.player.x][game.player.y].item->held = true;
            game.board.m[game.player.x][game.player.y].item->price = 0;

            switch (game.board.m[game.player.x][game.player.y].item->type())
            {
            case weapon:
                if (game.player.weapon->weaponType() == -1) {
                    delete(game.player.weapon);
                    game.player.weapon = nullptr;
                }
                tempw = game.player.weapon;
                game.player.weapon = dynamic_cast <Weapon*> (game.board.m[game.player.x][game.player.y].item);
                game.board.m[game.player.x][game.player.y].item = tempw;
                break;
            case armor:
                tempa = game.player.armor;
                game.player.armor = dynamic_cast <Armor*> (game.board.m[game.player.x][game.player.y].item);
                game.board.m[game.player.x][game.player.y].item = tempa;
                break;
            case torch:
                tempt = game.player.torch;
                game.player.torch = dynamic_cast <Torch*> (game.board.m[game.player.x][game.player.y].item);
                game.board.m[game.player.x][game.player.y].item = tempt;
                break;
            default:
                break;
            }
            if (game.board.m[game.player.x][game.player.y].item != nullptr) {
                game.board.m[game.player.x][game.player.y].item->held = false;
                game.board.m[game.player.x][game.player.y].item->x = game.player.x;
                game.board.m[game.player.x][game.player.y].item->y = game.player.y;
            }
        }
    }
    if (game.board.m[game.player.x][game.player.y].gold) {
        game.player.gold += game.board.m[game.player.x][game.player.y].gold;
        game.board.m[game.player.x][game.player.y].gold = 0;
    }
    cout << game.player.gold << '\n';

}

int clampx(int value) {
    return min(max(value, 0), game.board.length-1);
}
int clampy(int value) {
    return min(max(value, 0), game.board.height - 1);
}
void lightRec(int x, int y, int value) {
    lightTemp[x][y] = value;
    if (value > 1 && game.board.m[x][y].tile < tile::wall) {
        if (y > 0 && lightTemp[x][y - 1] < value) lightRec(x, y - 1, value - 1);
        if (y < game.board.height - 1 && lightTemp[x][y + 1] < value) lightRec(x, y + 1, value - 1);
        if (x < game.board.length - 1 && lightTemp[x + 1][y] < value) lightRec(x + 1, y, value - 1);
        if (x > 0 && lightTemp[x - 1][y] < value) lightRec(x - 1, y, value - 1);
    }
}

void lightUpdate() {
    short brightness = 3;
    if (game.player.torch != nullptr) brightness = game.player.torch->power;
    lightTemp.clear();
    lightTemp.resize(game.board.length);
    for (int i = 0; i < game.board.length; i++)
        lightTemp[i].resize(game.board.height);
    lightRec(game.player.x, game.player.y, brightness);
    for (int i = 0; i < game.board.height; i++)
        for (int j = 0; j < game.board.length; j++)
            lightTemp[j][i] /= brightness;
    light = lightTemp;
}

void changeLevel() {
    changingLevelLock = true;
    while (!changingLevelAnswer) sleep(milliseconds(1));
    game.NextLevel();
    mainView.setCenter(game.player.x * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
    lightUpdate();
    changingLevelAnswer = false;
    changingLevelLock = false;
}

void checkExit() {
    if (game.board.m[game.player.x][game.player.y].tile == tile::exitDoor) changeLevel();
}
int attackCheck(int dir, Map* board, int x, int y) {
    bool res = game.player.weapon->attack(dir, board, x, y);
    if (res && game.player.weapon->weaponType() != -1) {
        attackAnim = 0;
        game.player.lastAttackDir = dir;
    }
    return  res;
}
void control() {
    srand(time(NULL));
    bool buttonPressed = false;
    while (true)
    {
        if (closing) break;
        if (event.type == sf::Event::KeyPressed) {

            switch (event.key.code) {
            case sf::Keyboard::Left:
                if (game.player.x > 0 && game.board.m[max((int)game.player.x - 1, 0)][game.player.y].tile != tile::wall && !buttonPressed) {
                    game.player.facingLeft = true;
                    if (!attackCheck(directions::left, &game.board, game.player.x, game.player.y)) {
                        smoothStep(directions::left);
                        checkItems();
                        checkExit();
                    }
                    enemyUpd();

                }
                break;
            case sf::Keyboard::Right:
                if (game.player.x < game.board.length-1 && game.board.m[min((int)game.player.x + 1, game.board.length)][game.player.y].tile != tile::wall && !buttonPressed) {
                    game.player.facingLeft = false;
                    if (!attackCheck(directions::right, &game.board, game.player.x, game.player.y)) {
                        smoothStep(directions::right);
                        checkItems();
                        checkExit();
                    }
                    enemyUpd();

                }
                break;
            case sf::Keyboard::Up:
                if (game.player.y > 0 && game.board.m[game.player.x][max((int)game.player.y - 1, 0)].tile != tile::wall && !buttonPressed) {
                    if (!attackCheck(directions::up, &game.board, game.player.x, game.player.y)) {
                        smoothStep(directions::up);
                        checkItems();
                        checkExit();
                    }
                    enemyUpd();
                }
                break;
            case sf::Keyboard::Down:
                if (game.player.y < game.board.height-1 && game.board.m[game.player.x][min((int)game.player.y + 1, game.board.height)].tile != tile::wall && !buttonPressed) {
                    if (!attackCheck(directions::down, &game.board, game.player.x, game.player.y)) {
                        smoothStep(directions::down);
                        checkItems();
                        checkExit();
                    }
                    enemyUpd();
                }
                break;
            //case sf::Keyboard::Space :
            //    if(!buttonPressed)
            //        enemyUpd();
            //    break;
            //case sf::Keyboard::F:
            //    if (!buttonPressed) {
     
            //        changeLevel();
            //    }
            //    break;
            //
            }
            if (!buttonPressed) {
                lightUpdate();
            }
            buttonPressed = true;
        }
        else buttonPressed = false;
        while (game.player.gameover) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                game.Restart();
                mainView.setCenter(game.player.x * CELL + CELL / 2, game.player.y * CELL + CELL / 2);
                lightUpdate();
                game.player.gameover = false;
            }
        }
            
    }
}
void fullbright() {
    light.clear();
    light.resize(game.board.length);
    for (int i = 0; i < game.board.length; i++) {
        light[i].resize(game.board.height);
        for (int j = 0; j < game.board.height; j++)
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

    while(!started){
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            started = true;
        }
    }
    thread ctr(control);
    rend.join();
    ctr.join();
    return 0;
}