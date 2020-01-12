#include <iostream>
#include <vector>

struct Point {
    size_t x;
    size_t y;
};

class Base {
};

class Map {
public:
    Point map_size;
    char array[100][100];

public:
    Map(size_t a, size_t b) {
        map_size.x = a + 1;
        map_size.y = b + 1;
        srand(time(0));

        for (size_t i = 0; i <= a; ++i)
            for (size_t j = 0; j <= b; ++j) {
                array[i][j] = '#';
            }

        for (size_t i = 1; i < a; ++i)
            for (size_t j = 1; j < b; ++j) {
                int rr = rand() % 10 + 1;
                if (rr != 1)
                    array[i][j] = '.';
                else
                    array[i][j] = '#';
            }
    }
//
//    virtual bool CheckMove(int delta, char direction, Point pos) {
//        if (direction == 'x') {
//            return this->array[pos.x + delta][pos.y] != '#';
//        } else if (direction == 'y') {
//            return this->array[pos.x][pos.y + delta] != '#';
//        }
//        throw std::runtime_error("not x or y");
//    }

    virtual bool MaybeMove(int dx, int dy, Point &pos) {
        if (dx != 0 && dy != 0) dx = 0;
        if (array[pos.x + dx][pos.y + dy] != '.' && array[pos.x + dx][pos.y + dy] != 'K')
            return false;
        pos.x += dx;
        pos.y += dy;
        return true;
    }

    void print() {
        for (size_t j = 0; j < map_size.y; ++j) {
            for (size_t i = 0; i < map_size.x; ++i) {
                std::cout << array[i][j];
            }
            std::cout << std::endl;
        }
    }
};

class AidKit : public Base {
public:
    Point posit;
    int hill;
    char sym;

    AidKit(Map &map) {
        sym = 'A';
        hill = 15;
        posit.x = rand() % map.map_size.x - 1;
        posit.y = rand() % map.map_size.y - 1;
        while (map.array[posit.x][posit.y] != '.') {
            posit.x = rand() % map.map_size.x - 1;
            posit.y = rand() % map.map_size.y - 1;
        }
    }

    char GetSym() {
        return sym;
    }

    Point GetPos() {
        return posit;
    }
};

class Character : public Base {
protected:
    char key;
    int hp;
    int damage;
    char sym;
    Point pos;

public:
    Character(Map (&map)) {
        pos.x = rand() % map.map_size.x - 1;
        pos.y = rand() % map.map_size.y - 1;
        while (map.array[pos.x][pos.y] != '.') {
            pos.x = rand() % map.map_size.x - 1;
            pos.y = rand() % map.map_size.y - 1;
        }
    }

    virtual bool Move(Map (&map)) = 0;

    Point GetPos() {
        return pos;
    }

    int GetHp() {
        return hp;
    }

    int GetDamage() {
        return damage;
    }

    char GetSym() {
        return sym;
    }

    std::string KEY;
};

class MainHero : public Character {
public:
    MainHero(Map (&map)) : Character(map) {
        hp = 100;
        damage = 10;
        sym = 'K';
    }


    void hilling(AidKit A) {
        hp += A.hill;
        if (hp > 100) {
            hp = 100;
        }
    }

    bool Move(Map (&map)) override {
        key = KEY[0];
        bool result = false;
        size_t prev_x = GetPos().x;
        size_t prev_y = GetPos().y;

//        if (key == 71 || key == 75 || key == 79 || key == 72) return true;
//            Bullet *B = new Bullet;
//        }
        if ((key == 'a') && (map.array[pos.x - 1][pos.y] != '#') && (pos.x != 1)) {
            pos.x--;
            result = true;
        } else if ((key == 'w') && (map.array[pos.x][pos.y - 1] != '#') && (pos.y != 1)) {
            pos.y--;
            result = true;
        } else if ((key == 's') && (map.array[pos.x][pos.y + 1] != '#') &&
                   (this->pos.y + 1 < map.map_size.y)) {
            pos.y++;
            result = true;
        } else if ((key == 'd') && (map.array[pos.x + 1][pos.y] != '#') &&
                   (this->pos.x + 1 < map.map_size.x)) {
            pos.x++;
            result = true;
        } else if ((key == 'a') || (key == 'w') || (key == 's') || (key == 'd')) {
            result = true;
        }
        map.array[prev_x][prev_y] = '.';
        map.array[GetPos().x][GetPos().y] = this->GetSym();

        return result;
    }
};

//class Bullet : public Character {
//    Point previous;
//    size_t pos_x;
//    size_t pos_y;
//public:
//    Bullet(Map (&map)) : Character(map){
//        damage = 10;
//        sym = '*';
//        for (int i = 0; i < map.map_size.x; ++i) {
//            for (int j = 0; j < map.map_size.y; ++j) {
//                if (map.array[i][j] == 'K') {
//                    pos_x = i;
//                    pos_y = j;
//                }
//            }
//        }
//        previous.x = 0;
//        previous.y = 0;
//    }
//
//    bool Move (Map &map) override {
////        std::string KEY;
////        std::cin >> KEY;
//        key = KEY[0];
//        size_t prev_x = GetPos().x;
//        size_t prev_y = GetPos().y;
//
//        if (key == 71){
//            pos.x = pos_x - 1;
//        } else if (key == 75) {
//            pos.y = pos_y + 1;
//        } else if (key == 79){
//            pos.x = pos_x + 1;
//        } else if (key == 72) {
//            pos.y = pos_y - 1;
//        }
//        if (map.array[GetPos().x][GetPos().y] == '#') {
//            map.array[prev_x][prev_y] = '#';
//        }
//        else map.array[GetPos().x][GetPos().y] = this->GetSym();
//    }
//};

class Princess : public Character {
public:
    Princess(Map (&map)) : Character(map) {
        hp = 100;
        damage = 10;
        sym = 'P';
    }

    virtual bool Move(Map (&map)) {
        map.array[this->GetPos().x][this->GetPos().y] = this->GetSym();
        return true;
    }

};

class Monster : public Character {
public:

    Monster(Map (&map)) : Character(map) {}

    virtual bool Move(Map (&map)) = 0;

};

class Dragon : public Monster {
public:
    Dragon(Map (&map)) : Monster(map) {
        hp = 200;
        damage = 20;
        sym = 'D';
    }

    static int sgn(int x) { return x < 0 ? -1 : x > 0 ? 1 : 0; }

    virtual bool Move(Map (&map)) override {
        int pos_x = 0, pos_y = 0;
        size_t prev_x = this->GetPos().x;
        size_t prev_y = this->GetPos().y;

        for (int i = 0; i < map.map_size.x; ++i) {
            for (int j = 0; j < map.map_size.y; ++j) {
                if (map.array[i][j] == 'K') {
                    pos_x = i;
                    pos_y = j;
                }
            }
        }

        if (!map.MaybeMove(sgn(pos_x - prev_x), sgn(pos_y - prev_y), pos)) {
            if (map.array[GetPos().x - 1][GetPos().y] == '.')
                pos.x--;
            else if (map.array[GetPos().x][GetPos().y - 1] == '.')
                pos.y--;
            else if (map.array[GetPos().x + 1][GetPos().y] == '.')
                pos.x++;
            else pos.y++;
        }
        map.array[GetPos().x][GetPos().y] = this->GetSym();
        map.array[prev_x][prev_y] = '.';
        return true;
    }
};

class Zombie : public Monster {
public:
    Zombie(Map (&map)) : Monster(map) {
        hp = 50;
        damage = 5;
        sym = 'Z';
    }

    static int sgn(int x) { return x < 0 ? -1 : x > 0 ? 1 : 0; }

    virtual bool Move(Map (&map)) override {
        int pos_x = 0, pos_y = 0;
        size_t prev_x = this->GetPos().x;
        size_t prev_y = this->GetPos().y;

        for (int i = 0; i < map.map_size.x; ++i) {
            for (int j = 0; j < map.map_size.y; ++j) {
                if (map.array[i][j] == 'K') {
                    pos_x = i;
                    pos_y = j;
                }
            }
        }

        if (!map.MaybeMove(sgn(pos_x - prev_x), sgn(pos_y - prev_y), pos)) {
            if ((map.array[GetPos().x - 1][GetPos().y] == '.') || (map.array[pos.x--][pos.y] == 'K'))
                pos.x--;
            else if ((map.array[GetPos().x][GetPos().y - 1] == '.') || (map.array[pos.x][pos.y--] == 'K'))
                pos.y--;
            else if ((map.array[GetPos().x + 1][GetPos().y] == '.') || (map.array[pos.x++][pos.y] == 'K'))
                pos.x++;
            else pos.y++;
        }
        map.array[this->GetPos().x][this->GetPos().y] = this->GetSym();
        map.array[prev_x][prev_y] = '.';
        return true;
    }
};

class GameManager {
public:
    Map map;
    MainHero K;
    Princess P;
    AidKit *A;
//    Bullet *B;
    int flag = 0;
    int lose = 0;
    std::vector<Character *> Characters;
    bool GameIsRunning = true;

    GameManager() : map(25, 7), K(map), P(map) {

        Characters.push_back(&K);
        Characters.push_back(&P);

        Zombie *Z1 = new Zombie(map);
        Characters.push_back(Z1);

        Dragon *D = new Dragon(map);
        Characters.push_back(D);

        for (Character *k: Characters) {
            map.array[k->GetPos().x][k->GetPos().y] = k->GetSym();
        }

    }

    void play() {
        map.print();
        while (GameIsRunning) {
//            B = new Bullet(map);
            std::cin >> K.KEY;
//            K.KEY = B->KEY;

            for (Character *c: Characters) {
                bool print_map = c->Move(map);
                if (c->GetSym() == 'Z' || c->GetSym() == 'D') {
                    if ((c->GetPos().x == K.GetPos().x) && (c->GetPos().y == K.GetPos().y)) {
                        lose = 1;
                    }
                }
            }

//            B->Move(map);

            flag++;
            if (flag == 5) {
                A = new AidKit(map);
                map.array[A->GetPos().x][A->GetPos().y] = A->GetSym();
            }
            if ((K.GetPos().x == A->GetPos().x) && (K.GetPos().y == A->GetPos().y)) {
                K.hilling(*A);
                delete A;
                flag = 0;
            }

            if ((K.GetPos().x == P.GetPos().x) && (K.GetPos().y == P.GetPos().y)) {
                std::cout << "YOU WIN!!!" << std::endl;
                exit(0);
            }

            map.print();
            if (lose) {
                std::cout << "YOU LOOOOOOOOOOSE!!!" << std::endl;
                exit(0);
            }
        }
    }
};

int main() {
    GameManager Game;
    Game.play();
}