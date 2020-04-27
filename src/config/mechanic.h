
#ifndef DEEPLINEWARS_MECHANIC_H
#define DEEPLINEWARS_MECHANIC_H


class mechanic {

public:
    mechanic() {}

    int upgradeCostStart = 20000;
    double upgradeCostFactor = 0.8;
    double upgradeEffectFactor = 0.1;
    int tickEntityMove = 10;
    bool renderEveryStep = true;

};


#endif //DEEPLINEWARS_MECHANIC_H
