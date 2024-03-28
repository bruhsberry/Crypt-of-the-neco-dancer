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
Game game("levels\\\\level1.txt");
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
vector<Texture> textures, hearts;
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
    textures[tex::ironSwordTex].loadFromFile("Sprites\\iron sword.png");
    textures[tex::ironBroadswordTex].loadFromFile("Sprites\\iron broadsword.png");
    textures[tex::goldSwordTex].loadFromFile("Sprites\\gold sword.png");
    textures[tex::goldBroadswordTex].loadFromFile("Sprites\\gold broadsword.png");
    textures[tex::titaniumSwordTex].loadFromFile("Sprites\\titanium sword.png");
    textures[tex::titaniumBroadswordTex].loadFromFile("Sprites\\titanium broadsword.png");
    textures[tex::notexture].loadFromFile("Sprites\\aaaa.png");
    textures[tex::shadow].loadFromFile("Sprites\\shadow.png");
    textures[tex::woodenTorchTex].loadFromFile("Sprites\\wooden torch.png");
    textures[tex::steelTorchTex].loadFromFile("Sprites\\steel torch.png");
    textures[tex::magicTorchTex].loadFromFile("Sprites\\magic torch.png");
    textures[tex::ironSpearTex].loadFromFile("Sprites\\iron spear.png");
    textures[tex::titaniumSpearTex].loadFromFile("Sprites\\titanium spear.png");
    textures[tex::goldSpearTex].loadFromFile("Sprites\\gold spear.png");
    textures[tex::letherArmorTex].loadFromFile("Sprites\\lether.png");
    textures[tex::chainArmorTex].loadFromFile("Sprites\\chainmail.png");
    textures[tex::plateArmorTex].loadFromFile("Sprites\\plate.png");
    textures[tex::chestTex].loadFromFile("Sprites\\chest.png");
    hearts.resize(6);
    for (int i = 0; i < 6; i++)
        hearts[i].loadFromFile("Sprites\\hp\\" + to_string(i + 1) + "hp.png");
    
}

void render() {
    sf::Vector2f worldPos(0, 0);
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

    Sprite sprite, shadow, playerSprite, enemySprite, startSprite, borderSprite, iconSprite;
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
            switch (game.board.it[i]->typeOf()) {
            case items::letherArmor:
                sprite.setTexture(textures[tex::letherArmorTex]);
                break;
            case items::chainArmor:
                sprite.setTexture(textures[tex::chainArmorTex]);
                break;
            case items::plateArmor:
                sprite.setTexture(textures[tex::plateArmorTex]);
                break;
            case items::ironSword:
                sprite.setTexture(textures[tex::ironSwordTex]);
                break;
            case items::titaniumSword:
                sprite.setTexture(textures[tex::titaniumSwordTex]);
                break;
            case items::goldSword:
                sprite.setTexture(textures[tex::goldSwordTex]);
                break;
            case items::ironBroadsword:
                sprite.setTexture(textures[tex::ironBroadswordTex]);
                break;
            case items::titaniumBroadsword:
                sprite.setTexture(textures[tex::titaniumBroadswordTex]);
                break;
            case items::goldBroadsword:
                sprite.setTexture(textures[tex::goldBroadswordTex]);
                break;
            case items::ironSpear:
                sprite.setTexture(textures[tex::ironSpearTex]);
                break;
            case items::titaniumSpear:
                sprite.setTexture(textures[tex::titaniumSpearTex]);
                break;
            case items::goldSpear:
                sprite.setTexture(textures[tex::goldSpearTex]);
                break;
            case items::magicTorch:
                sprite.setTexture(textures[tex::magicTorchTex]);
                break;
            case items::steelTorch:
                sprite.setTexture(textures[tex::steelTorchTex]);
                break;
            case items::woodenTorch:
                sprite.setTexture(textures[tex::woodenTorchTex]);
                break;
            default:
                sprite.setTexture(textures[tex::notexture]);
                break;

            }
            sprite.setPosition(game.board.it[i]->x * CELL, game.board.it[i]->y * CELL);
            window.draw(sprite);
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
        //тени
        for (int i = 0; i < game.board.height; i++) {
            for (int j = 0; j < game.board.length; j++)
            {
                shadow.setPosition(j * CELL, i * CELL);
                shadow.setColor(sf::Color(0, 0, 0, 255 * (1 - light[j][i])));
                window.draw(shadow);
            }
        }

        
        borderSprite.setPosition(game.player.x * CELL - 250, game.player.y * CELL - 210);
        iconSprite.setPosition(game.player.x* CELL - 250, game.player.y* CELL - 210);
        switch (game.player.weapon->typeOf())
        {
        case items::ironSword:
            iconSprite.setTexture(textures[tex::ironSwordTex]);
            window.draw(iconSprite);
            break;
        case items::titaniumSword:
            iconSprite.setTexture(textures[tex::titaniumSwordTex]);
            window.draw(iconSprite);
            break;
        case items::goldSword:
            iconSprite.setTexture(textures[tex::goldSwordTex]);
            window.draw(iconSprite);
            break;
        case items::ironBroadsword:
            iconSprite.setTexture(textures[tex::ironBroadswordTex]);
            window.draw(iconSprite);
            break;
        case items::titaniumBroadsword:
            iconSprite.setTexture(textures[tex::titaniumBroadswordTex]);
            window.draw(iconSprite);
            break;
        case items::goldBroadsword:
            iconSprite.setTexture(textures[tex::goldBroadswordTex]);
            window.draw(iconSprite);
            break;
        case items::ironSpear:
            iconSprite.setTexture(textures[tex::ironSpearTex]);
            window.draw(iconSprite);
            break;
        case items::titaniumSpear:
            iconSprite.setTexture(textures[tex::titaniumSpearTex]);
            window.draw(iconSprite);
            break;
        case items::goldSpear:
            iconSprite.setTexture(textures[tex::goldSpearTex]);
            window.draw(iconSprite);
            break;
        default:
            break;
        }
        window.draw(borderSprite);
        borderSprite.setPosition(game.player.x* CELL - 250, game.player.y* CELL - 150);
        iconSprite.setPosition(game.player.x* CELL - 250, game.player.y* CELL - 150);
        switch (game.player.armor->typeOf()) {
        case items::letherArmor:
            iconSprite.setTexture(textures[tex::letherArmorTex]);
            window.draw(iconSprite);
            break;
        case items::chainArmor:
            iconSprite.setTexture(textures[tex::chainArmorTex]);
            window.draw(iconSprite);
            break;
        case items::plateArmor:
            iconSprite.setTexture(textures[tex::plateArmorTex]);
            window.draw(iconSprite);
            break;
        }
        window.draw(borderSprite);
        borderSprite.setPosition(game.player.x* CELL - 250, game.player.y* CELL - 90);
        iconSprite.setPosition(game.player.x* CELL - 250, game.player.y* CELL - 90);
        window.draw(borderSprite);
        switch (game.player.torch->typeOf()) {
        case items::magicTorch:
            iconSprite.setTexture(textures[tex::magicTorchTex]);
            window.draw(iconSprite);
            break;
        case items::steelTorch:
            iconSprite.setTexture(textures[tex::steelTorchTex]);
            window.draw(iconSprite);
            break;
        case items::woodenTorch:
            iconSprite.setTexture(textures[tex::woodenTorchTex]);
            window.draw(iconSprite);
            break;
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
                if (game.player.weapon->name == "No weapon") {
                    delete(game.player.weapon);
                    game.player.weapon = nullptr;
                }
                tempw = game.player.weapon;
                game.player.weapon = dynamic_cast <Weapon*> (game.board.m[game.player.x][game.player.y].item);
                game.board.m[game.player.x][game.player.y].item = tempw;
                break;
            case armor:
                if (game.player.armor->name == "No armor") {
                    delete(game.player.armor);
                    game.player.armor = nullptr;
                }
                tempa = game.player.armor;
                game.player.armor = dynamic_cast <Armor*> (game.board.m[game.player.x][game.player.y].item);
                game.board.m[game.player.x][game.player.y].item = tempa;
                break;
            case torch:
                if (game.player.torch->name == "No torch") {
                    delete(game.player.torch);
                    game.player.torch = nullptr;
                }
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
    lightTemp.clear();
    lightTemp.resize(game.board.length);
    for (int i = 0; i < game.board.length; i++)
        lightTemp[i].resize(game.board.height);
    lightRec(game.player.x, game.player.y, game.player.torch->power);
    for (int i = 0; i < game.board.height; i++)
        for (int j = 0; j < game.board.length; j++)
            lightTemp[j][i] /= game.player.torch->power;
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
                    if (!game.player.weapon->attack(directions::left, &game.board, game.player.x, game.player.y)) {
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
                    if (!game.player.weapon->attack(directions::right, &game.board, game.player.x, game.player.y)) {
                        smoothStep(directions::right);
                        checkItems();
                        checkExit();
                    }
                    enemyUpd();

                }
                break;
            case sf::Keyboard::Up:
                if (game.player.y > 0 && game.board.m[game.player.x][max((int)game.player.y - 1, 0)].tile != tile::wall && !buttonPressed) {
                    if (!game.player.weapon->attack(directions::up, &game.board, game.player.x, game.player.y)) {
                        smoothStep(directions::up);
                        checkItems();
                        checkExit();
                    }
                    enemyUpd();
                }
                break;
            case sf::Keyboard::Down:
                if (game.player.y < game.board.height-1 && game.board.m[game.player.x][min((int)game.player.y + 1, game.board.height)].tile != tile::wall && !buttonPressed) {
                    if (!game.player.weapon->attack(directions::down, &game.board, game.player.x, game.player.y)) {
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