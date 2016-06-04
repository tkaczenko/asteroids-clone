#include "../include/../include/GameObject.h"

SDL_Point GameObject::baseFormula(const int& a, const int& b, const int& c, const int& d)
{
    return {int(cosA * a - sinA * b + position.x),
                int(sinA * c + cosA * d + position.y)};
}

int** GameObject::readConfig(const std::string& filename)
{
    std::ifstream config (filename);
    if (config.is_open()) {
        int countM;
        int countN;
        config >> countM;
        config >> countN;
        int **arr = new int*[countM];
        for (int i = 0; i < countM; i++) {
            arr[i] = new int[countN];
            for (int j = 0; j < countN; j++) {
                config >> arr[i][j];
            }
        }
        config.close();
        return arr;
    } else {
        std::cout << "Error: Not found config file at " << filename << std::endl;
        return nullptr;
    }
}
