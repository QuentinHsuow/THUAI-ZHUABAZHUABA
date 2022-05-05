#include "ai.h"

/* 植物结构体：
 * (int) row - 植物所在的行数
 * (int) col - 植物所在的列数
 * (int) priority - 植物的优先级
 * (int) type - 植物的类型
 */
typedef struct tagPlant {
    int row;
    int col;
    int priority;
    int type;
} plant;

/* 僵尸结构体
 * (int) type - 僵尸的类型
 * (int) row - 僵尸所在的行数
 */
typedef struct tagZombie{
    int type;
    int row;
} zombie;

/* ForceCompare
 * @brief: 计算战场上实时战斗力的函数
 * 1.ForceCalculation 计算植物/僵尸方的武力总值 - basis of all the following functions
 * 2.StrongerAmount 计算植物的武力值比僵尸的武力值大多少
 * 3.StrongerArray 计算植物的武力值比僵尸的武力值大多少的数组
 * 4.WeakestRow 计算僵尸比植物强的最多的一行
 * 5.isPlantStronger 判断是不是植物比僵尸强
 */
namespace ForceCompare{
    /*************************************************************************
    【函数名称】 ForceCalculation
    【函数功能】 计算植物/僵尸方的武力总值
    【参数】 row-要比较的行数； isZombie-是不是僵尸；
    【返回值】 返回植物/僵尸方的武力总值
     *************************************************************************/
    int ForceCalculation(int row, bool isZombie, IPlayer* player);

    /*************************************************************************
    【函数名称】 StrongerAmount
    【函数功能】 计算植物的武力值比僵尸的武力值大多少
    【参数】 row-要比较的行数；
    【返回值】 返回植物武力值与僵尸武力值的差
     *************************************************************************/
    inline int StrongerAmount(int row, IPlayer* player);

    /*************************************************************************
    【函数名称】 StrongerArray
    【函数功能】 计算植物的武力值比僵尸的武力值大多少的数组
    【参数】 /
    【返回值】 返回植物武力值与僵尸武力值的差的数组，arr[i]代表第i行的差值
     *************************************************************************/
    int* StrongerArray(IPlayer* player);

    /*************************************************************************
    【函数名称】 WeakestRow
    【函数功能】 计算僵尸比植物强的最多的一行
    【参数】 /
    【返回值】 返回僵尸比植物强的最多的一行
     *************************************************************************/
    int WeakestRow(IPlayer* player);

    /*************************************************************************
    【函数名称】 isPlantStronger
    【函数功能】 判断是不是植物比僵尸强
    【参数】 /
    【返回值】 true:植物比僵尸强；false：植物比僵尸弱
     *************************************************************************/
     bool isPlantStronger(IPlayer* player);
}

/* BattleField
 * @brief: 计算战场上情况（有没有x对象）的函数组
 * 1.DenseOfZombie 计算一格内的僵尸有多少
 * 2.isWithoutVM 计算战场上某一行是否有寒冰射手和建国
 * 3.isWithoutWinterArray 计算战场上每一行是否有寒冰射手和建国
 * 4.WherePole 计算战场上哪一行有撑杆跳
 * 5.NumTypeArray 计算战场上Type型植物/僵尸的种类
 */
namespace BattleField{
    /*************************************************************************
    【函数名称】 DenseOfZombie
    【函数功能】 计算一格内的僵尸有多少
    【参数】 row-要计算的行； col-要计算的列
    【返回值】 返回row行col列有多少僵尸
     *************************************************************************/
    int DenseOfZombie(IPlayer* player, int row, int col);

    /*************************************************************************
    【函数名称】 isWithoutVM
    【函数功能】 计算战场上某一行是否有寒冰射手和建国
    【参数】 row-要计算的行数
    【返回值】 true-没有寒冰射手与建国，false-有;如果这一行被攻破，返回false
     *************************************************************************/
    bool isWithoutWinter(IPlayer* player, int row);

    /*************************************************************************
    【函数名称】 isWithoutWinterArray
    【函数功能】 计算战场上每一行是否有寒冰射手和建国
    【参数】 \
    【返回值】 bool array[5]; true-没有寒冰射手与建国，false-有;如果这一行被攻破，返回false
     *************************************************************************/
    bool* isWithoutWinterArray(IPlayer* player);

    /*************************************************************************
    【函数名称】 WherePole
    【函数功能】 计算战场上哪一行有撑杆跳
    【参数】 \
    【返回值】 -1：没有撑杆跳；[0,4]撑杆跳的行数
     *************************************************************************/
    int WherePole(IPlayer* player);

    /*************************************************************************
    【函数名称】 NumTypeArray
    【函数功能】 计算战场上type型植物/僵尸的数量
    【参数】 isZombie-true:zombie;false-plant
    【返回值】 int[5]
     *************************************************************************/
    int* NumTypeArray(bool isZombie, int type, IPlayer* player);

}

/* Util
 * @brief: 实用小函数
 * 1.SetPlant 将数据值注入结构体
 * 2.GetBestPlant 得到当前最佳植物
 * 3.GetBestZombie 得到当前最佳僵尸组
 */
namespace Util{
    /*************************************************************************
    【函数名称】 SetPlant
    【函数功能】 将数据值注入结构体
    【参数】 i:row, j: col, pri: priority, type: 植物类型
    【返回值】 void
     *************************************************************************/
    void SetPlant(plant* Plant, int i, int j, int pri, int type);

    /*************************************************************************
    【函数名称】 GetBestPlant
    【函数功能】 得到当前最佳植物
    【参数】 /
    【返回值】 最佳植物
     *************************************************************************/
    plant GetBestPlant(IPlayer* player);

    /*************************************************************************
    【函数名称】 GetBestZombie
    【函数功能】 得到当前最佳僵尸
    【参数】 /
    【返回值】 最佳僵尸
     *************************************************************************/
    zombie GetBestZombie(IPlayer* player);
}

/* Plant
 * 向日葵：
 * - 前50回合优先度为1300
 * - 前200回合优先度为1200
 * - 如果所有植物都强势，那么优先度为1150
 * 冰豌豆：
 * - 阳光比较少时，防御敌人，优先度为900
 * - 如果植物变得强势，种满三列，优先度为550
 * 豌豆：
 * - 阳光比较少时，防御敌人，优先度为1050
 * - 如果植物变得强势，种满两列，优先度为600
 * 坚果墙：
 * - 在前200回合，主动防御铁桶等僵尸，优先度1000
 * - 在后200回合，阳光高于450时补齐坚果墙，优先度800
 * - 在所有回合，如果僵尸进入了草坪两格，自动放坚果墙防御，优先级为1100
 * - 存在巨人和雪橇时，如果已经决定在这一行放置坚果，取消之
 * 倭瓜：
 * - 存在巨人僵尸时，立即放置，优先度1200（应该很高）
 * - 如果一格内僵尸浓度很大，立即放置，优先度1150（也比较高）
 * - 如果快被打穿了，则立即放置倭瓜，优先度2000（应仅次于向日葵）
 * 辣椒：
 * - 如果一行僵尸过于强大，放置辣椒，优先度1110
 */
namespace Plant{
    plant SunFlower(IPlayer* player);
    plant WinterPeaShooter(IPlayer* player);
    plant PeaShooter(IPlayer* player);
    plant SmallNut(IPlayer* player);
    plant Pepper(IPlayer* player);
    plant Squash(IPlayer* player);
    void RemovePeaShooter(IPlayer* player, plant pt);
}

namespace ZombieUtil{
    /*************************************************************************
   【函数名称】 BestAssault
   【函数功能】 计算最佳骚扰行数
   【参数】 \
   【返回值】 最佳的骚扰行数
    *************************************************************************/
    int BestAssault(IPlayer *player);

    /*************************************************************************
   【函数名称】 isPost
   【函数功能】 判断是否进入后期
   【参数】 \
   【返回值】 判断assault和wait的界限
   【修改记录】 5.5 通过寒冰射手是否大于BrokenLines-2来判断是否进入后期
    *************************************************************************/
    bool isPost(IPlayer* player);

    /*************************************************************************
   【函数名称】 StartBestPosition
   【函数功能】 判断start阶段最佳的放置位点
   【参数】 \
   【返回值】 僵尸放置的行数
   【修改记录】
    *************************************************************************/
    int StartBestPosition(bool isNormal, IPlayer* player);

    /*************************************************************************
   【函数名称】 StartBestPositionPole
   【函数功能】 判断start阶段是不是最好放置Pole
   【参数】 \
   【返回值】 -1 不应该放置pole， [0,4]放置pole的行数
   【修改记录】
    *************************************************************************/
    int StartBestPositionPole(IPlayer* player);
}

namespace Zombie {
    /*************************************************************************
    【函数名称】Start
    【函数功能】返回[1,25)回合中需要放置的僵尸
    【参数】 /
    【返回值】 最佳僵尸
    【修改历史】5.5 增加了放在某一行的判断；
     *************************************************************************/
    zombie Start(IPlayer *player);

    zombie Assault(IPlayer *player);
    zombie Wait(IPlayer *player);
    zombie ZombieWave(IPlayer *player);
    zombie WaveByWave(IPlayer *player);
}

void player_ai(IPlayer* player)
{
    // 获取植物方还是僵尸方
    int Type = player->Camp->getCurrentType();

    if (Type == 0)//植物方
    {
        plant pt = Util::GetBestPlant(player);
        Plant::RemovePeaShooter(player, pt);
        if (pt.priority > 0) player->PlacePlant(pt.type, pt.row, pt.col);
    }

    if (Type == 1)//僵尸方
    {
        zombie zb = Util::GetBestZombie(player);
        if (zb.type != -1) player->PlaceZombie(zb.type, zb.row);
    }
}

int ForceCompare::ForceCalculation(int row, bool isZombie, IPlayer* player)
{
    int* LeftLines = player->Camp->getLeftLines();
    int columns = player->Camp->getColumns();
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();

    if(LeftLines[row] == 0) return 0;

    int sum = 0;
    if (isZombie)//计算僵尸的武力值
    {
        for (int i = 0; i < columns; i++)
        {
            int k = 0;
            while (Zombies[row][i][k] != -1)
            {
                //计算武力值时，让武力值和血量、速度成正比
                if (Zombies[row][i][k] == 1)//普通僵尸
                    sum += 270;//将普通僵尸作为标杆
                else if (Zombies[row][i][k] == 2)//铁桶僵尸
                    sum += 820;
                else if (Zombies[row][i][k] == 3)//撑杆跳僵尸
                    sum += 200 * 5 / 4.5;//这里是对撑杆僵尸的估算，个人觉得撑杆用处不大，故没有考虑在内
                else if (Zombies[row][i][k] == 4)//雪橇僵尸
                    sum += 1600 * 5 / 7;
                else if (Zombies[row][i][k] == 5)//巨人僵尸
                    sum += 3000;
                k++;
            }
        }
    }
    else
    {
        for (int j = 0; j < columns; j++)
        {
            if (Plants[row][j] == 2)//冰豌豆
                sum += (10 - j) * 5 * 40;//普通僵尸走到跟前时造成的总伤害
            if (Plants[row][j] == 3)//豌豆
                sum += (10 - j) * 5 * 10;
            if (Plants[row][j] == 4)//坚果墙
                sum += 530;//注：此处计算坚果墙武力值为估算，是在只有一个豌豆和一个僵尸情况下估算的
        }
    }
    return sum;
}
inline int ForceCompare::StrongerAmount(int row, IPlayer* player) {
    return ForceCalculation(row, false, player) - ForceCalculation(row, true, player);
}
int* ForceCompare::StrongerArray(IPlayer* player) {
    int* stronger_arr = new int[5];
    for (int i = 0; i < 5; ++i) stronger_arr[i] = StrongerAmount(i, player);
    return stronger_arr;
}
int ForceCompare::WeakestRow(IPlayer* player) {

    int* LeftLines = player->Camp->getLeftLines();
    int* stronger_arr = StrongerArray(player);

    int min = 100000;
    int row = -1;

    for (int i = 0; i < 5; ++i) {
        if (LeftLines[i] == 1) {
            if (stronger_arr[i] < min) {
                min = stronger_arr[i];
                row = i;
            }
        }
    }
    return row;
}
bool ForceCompare::isPlantStronger(IPlayer* player){
    int* LeftLines = player->Camp->getLeftLines();
    bool isStronger = true;
    for (int i = 0; i < 5; ++i) {
        if (LeftLines[i] == 0) continue;
        if (StrongerAmount(i, player) < 0) isStronger = false;//修改
    }
    return isStronger;
}
int BattleField::DenseOfZombie(IPlayer* player, int row, int col){

    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();

    if(LeftLines[row] == 0) return 0;

    int sum = 0;
    int k = 0;
    while (Zombies[row][col][k] != -1)
    {
        if (Zombies[row][col][k] == 1) sum += 270;
        else if (Zombies[row][col][k] == 2) sum += 820;
        else if (Zombies[row][col][k] == 3) sum += 200 * 10 / 9;
        else if (Zombies[row][col][k] == 4) sum += 1600 * 5 / 7;
        else sum += 3000;
        k++;
    }
    return sum;
}
bool BattleField::isWithoutWinter(IPlayer* player, int row) {

    int* LeftLines = player->Camp->getLeftLines();
    int cols = player->Camp->getColumns();
    int** Plants = player->Camp->getCurrentPlants();

    if(LeftLines[row] == 0) return false;

    for(int i = 0; i < cols; ++i){
        if(Plants[row][i] == 2){
            return false;
        }
    }

    return true;
}
bool* BattleField::isWithoutWinterArray(IPlayer* player){
    bool* arr = new bool[5];
    for(int i = 0; i < 5; ++i){
        arr[i] = isWithoutWinter(player, i);
    }
    return arr;
}
int BattleField::WherePole(IPlayer* player) {
    int columns = player->Camp->getColumns();
    int ***Zombies = player->Camp->getCurrentZombies();
    int *LeftLines = player->Camp->getLeftLines();
    int r = -1;
    bool flag = false;
    for (int i = 0; i < 5; i++)//防范撑杆的偷袭
    {
        if (LeftLines[i] == 0) continue;
        for (int j = 0; j < columns; j++) {
            int k = 0;
            while (Zombies[i][j][k] != -1) {
                if (Zombies[i][j][k] == 3 && !flag) {
                    flag = true;
                    r = i;
                }
                k++;
            }
        }
    }
    return r;
}
int* BattleField::NumTypeArray(bool isZombie, int type, IPlayer*player){
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int cols = player->Camp->getColumns();
    int* LeftLines = player->Camp->getLeftLines();
    int* arr = new int[5];

    if(isZombie){
        for(int i = 0; i < 5; ++i){
            if(LeftLines[i] == 0){
                arr[i] = 0;
                continue;
            }
            for(int j = 0; j < cols; j++){
                for(int k = 0; Zombies[i][j][k] != -1; k++){
                    if(Zombies[i][j][k] == type){
                        arr[i]++;
                    } // zombieType
                } // inner-most loop
            } // col-loop
        } // row-loop
    }
    else{
        for (int i = 0; i < 5; i++) {
            if (LeftLines[i] == 0) {
                arr[i] = 0;
                continue;
            }
            for (int j = 0; j < cols; ++j) {
                if (Plants[i][j] == type) {
                    arr[i]++;
                }
            }
        }
    }
    return arr;
}
void Util::SetPlant(plant* Plant, int i, int j, int pri, int type)
{
    Plant->row = i;
    Plant->col = j;
    Plant->priority = pri;
    Plant->type = type;
}
plant Util::GetBestPlant(IPlayer *player) {
    plant arr[6];
    arr[0] = Plant::SunFlower(player);
    arr[1] = Plant::WinterPeaShooter(player);
    arr[2] = Plant::PeaShooter(player);
    arr[3] = Plant::SmallNut(player);
    arr[4] = Plant::Pepper(player);
    arr[5] = Plant::Squash(player);

    plant best = arr[0];
    for (int i = 1; i < 6; ++i) {
        if (arr[i].priority > best.priority) {
            best = arr[i];
        }
    }
    return best;
}
zombie Util::GetBestZombie(IPlayer *player)  {
    int turn = player->getTime();
    if (turn < 25) return Zombie::Start(player);
    if (turn >= 25 && turn < 490 && !ZombieUtil::isPost(player)) return Zombie::Assault(player);
    if (turn >= 25 && turn < 490 && ZombieUtil::isPost(player)) return Zombie::Wait(player);
    if (turn >= 490 && turn < 550) return Zombie::ZombieWave(player);
    if (turn >= 550 && turn < 990 && !ZombieUtil::isPost(player)) return Zombie::Assault(player);
    if (turn >= 550 && turn < 990 && ZombieUtil::isPost(player)) return Zombie::Wait(player);
    if (turn >= 990 && turn < 1050) return Zombie::ZombieWave(player);
    if (turn >= 1050 && turn < 1490) return Zombie::WaveByWave(player);
    if (turn >= 1490 && turn < 1550) return Zombie::ZombieWave(player);
    if (turn >= 1550) return Zombie::WaveByWave(player);
}
plant Plant::SunFlower(IPlayer* player) {

    int* PlantCD = player->Camp->getPlantCD();
    int turn = player->getTime();
    int Sun = player->Camp->getSun();
    int** Plants = player->Camp->getCurrentPlants();
    int* LeftLines = player->Camp->getLeftLines();

    int col = 0;
    int row = 0;
    int p = 0;

    if (turn < 30) {
        for (int i = 0; i < 5; ++i) {
            if(LeftLines[i] == 0 || ForceCompare::ForceCalculation(i, false, player) <
                                    2 * ForceCompare::ForceCalculation(i, true, player)) continue;//如果一行产生威胁，就不种向日葵
            if (Plants[i][3] == 0) { row = i; col = 3; p = 1300; break; }
            if (Plants[i][4] == 0) { row = i; col = 4; p = 1300; break; }
        }
    }
    else if (turn < 200 && Sun > 125) {
        for (int i = 0; i < 5; ++i) {
            if(LeftLines[i] == 0 || ForceCompare::StrongerAmount(i, player) < 0) continue;
            if (Plants[i][3] == 0) { row = i; col = 3; p = 1000; break; }
            if (Plants[i][4] == 0) { row = i; col = 4; p = 1000; break; }
        }
    }
    else if(ForceCompare::isPlantStronger(player)) {
        for (int i = 0; i < 5; ++i) {
            if(LeftLines[i] == 0) continue;
            if (Plants[i][3] == 0) { row = i; col = 3; p = 1150; break; }
            if (Plants[i][4] == 0) { row = i; col = 4; p = 1150; break; }
        }
    }

    if (Sun < 50) p = 0;
    if (PlantCD[0] != 0) p = 0;
    if (col == -1 || row == -1) return { 0, 0, 0 };
    else return {  row, col, p, 1 };

}
plant Plant::WinterPeaShooter(IPlayer *player) {

    int* PlantCD = player->Camp->getPlantCD();
    int Sun = player->Camp->getSun();
    int** Plants = player->Camp->getCurrentPlants();
    int* LeftLines = player->Camp->getLeftLines();

    int p = 0;
    int row = 0;
    int col = 0;

    if (!ForceCompare::isPlantStronger(player))//如果阳光比较少，节约一点
    {
        p = 900;
        row = ForceCompare::WeakestRow(player);
        if (Plants[row][2] == 0) col = 2;
        else if (Plants[row][4] == 0) col = 4;
        else col = -1;//没地方种了
    }
    else// 有余力时，摆满三列
    {
        int tmp[5] = {2, 5, 0, 1, 6};
        for(int j = 4; j >= 0; j--)
            for (int i = 0; i < 5; i++){
                if(LeftLines[i] == 0) continue;
                if (Plants[i][tmp[j]] != 2)
                {
                    row = i;
                    col = tmp[j];
                    p = 550;
                }
            }
    }
    if (PlantCD[1] != 0 || Sun < 500 || col == -1) p = 0;

    return { row, col, p, 2 };
}
plant Plant::PeaShooter(IPlayer *player) {

    int* PlantCD = player->Camp->getPlantCD();
    int Sun = player->Camp->getSun();
    int** Plants = player->Camp->getCurrentPlants();
    int* LeftLines = player->Camp->getLeftLines();

    int p = 0;
    int row = 0;
    int col = 0;

    if (!ForceCompare::isPlantStronger(player))//如果阳光比较少，节约一点
    {
        p = 1050;
        if (BattleField::WherePole(player) == -1) row = ForceCompare::WeakestRow(player);
        else row = BattleField::WherePole(player);
        if (Plants[row][0] == 0) col = 0;
        else if (Plants[row][1] == 0) col = 1;
        else col = -1;//没地方种了，以后可以在这里加入铲子
    }
    else// 有余力时，摆满一列
    {
        for (int j = 1; j >= 0; j--)
            for (int i = 0; i < 5; i++)
            {
                if(LeftLines[i] == 0) continue;
                if (Plants[i][j] == 0 || Plants[i][j] == 4)//铲坚果墙
                {
                    row = i;
                    col = j;
                    p = 600;
                    break;
                }
            }
    }
    if (PlantCD[2] != 0 || Sun < 100 || col == -1 || Sun > 1000) p = 0;

    return { row, col, p, 3 };
}
plant Plant::SmallNut(IPlayer *player) {

    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    plant Boss = { 0, 0, 0, 4 };
    //在开始时在保护战斗力弱的行
    if (turn < 200)
    {
        //检索是否有比较弱的行，种植坚果墙
        for (int i = 0; i < rows; i++)
        {
            if (LeftLines[i] == 0) continue;
            //种植坚果，如果一行出现了铁桶僵尸
            if (Zombies[i][columns - 1][0] == 2)
                Util::SetPlant(&Boss, i, columns - 1, 1000, 4);
        }
    }
    else
    {
        //在战斗后期，自动补齐坚果墙
        for (int j = columns - 2; j <= columns - 1; j++)
            for (int i = 0; i < rows; i++)
            {
                if (LeftLines[i] == 0) continue;
                if (Plants[i][j] == 0 && Sun > 450 && LeftLines[i] == 1)//如果有多余阳光，且没有被攻破,则补齐一行坚果墙
                    Util::SetPlant(&Boss, i, j, 800, 4);
            }
    }
    //被动防御优先
    for (int j = columns - 2; j >= 0; j--)// 从后往前遍历，前面的结果会覆盖后面的结果，从而使得在最前面的僵尸前放置
        for (int i = 0; i < rows; i++)
        {
            if (LeftLines[i] == 0) continue;
            if (Zombies[i][j][0] != -1) {//如果僵尸攻入了内地
                if (j > 1 && Plants[i][j - 1] == 0) {
                    Util::SetPlant(&Boss, i, j - 1, 1100, 4);
                }
                else {
                    Util::SetPlant(&Boss, i, j, 1100, 4);
                }
            }
        }
    //场上有巨人僵尸时，不放坚果墙
    if (Boss.priority != 0)
    {
        for (int i = 0; i < columns; i++)
        {
            int k = 0;
            while (Zombies[Boss.row][i][k] != -1)
            {
                if (Zombies[Boss.row][i][k] == 4 || Zombies[Boss.row][i][k] == 5)
                    Util::SetPlant(&Boss, 0, 0, 0, 4);
                k++;
            }
        }
        if (PlantCD[3] != 0) Util::SetPlant(&Boss, 0, 0, 0, 4);//CD不够时，CD自动清零
    }
    return Boss;
}
plant Plant::Pepper(IPlayer *player){

    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int *PlantCD = player->Camp->getPlantCD();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();
    int turn = player->getTime();

    int value = 1600;
    if (turn > 50) value = 1700;//小trick,在比赛开始时，降低使用辣椒的门槛，使得两个铁桶就能触发辣椒

    plant Boss = {0,0,0, 5};
    for(int i=0;i<rows;i++)
    {
        if (LeftLines[i] == 0) continue;
        if (ForceCompare::ForceCalculation(i, true, player) - 1200 > ForceCompare::ForceCalculation(i, false, player)
            || ForceCompare::ForceCalculation(i, true, player) > value)
            Util::SetPlant(&Boss, i, columns - 1, 1150, 5);//优先级应该较高
    }
    if (PlantCD[4] != 0 || Sun < 125) Boss.priority = 0;
    //
    return Boss;
}
plant Plant::Squash(IPlayer *player){

    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int *PlantCD = player->Camp->getPlantCD();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    plant Boss = {0,0,0, 6};
    for(int i = 0;i < rows;i++)
    {
        if (LeftLines[i] == 0) continue;
        for(int j = 0;j < columns;j++)
        {
            int k = 0;
            //砸巨人僵尸
            while(Zombies[i][j][k] != -1)
            {
                if (Zombies[i][j][k] == 5 && Boss.priority < 1500)
                {
                    Util::SetPlant(&Boss, i, j, 1500, 6);
                }//碰到巨人僵尸的优先度,the second highest, only lower than sunflower
                if (BattleField::DenseOfZombie(player, i, j) > 1200 && ForceCompare::ForceCalculation(i, true, player) > ForceCompare::ForceCalculation(i, false, player) && Boss.priority < 1400)
                    Util::SetPlant(&Boss, i, j, 1400, 6);//碰到一大坨僵尸且一行没有足够的战力时的的优先度,优先级应次于添加攻击性植物
                k++;
            }
            //绝地反击，如果僵尸快打穿了
            if (j == 0 && Zombies[i][0][0] != -1 && Boss.priority < 2000)
                Util::SetPlant(&Boss, i, 0, 2000, 6);//此地逻辑存疑，待修正
        }
    }
    if (PlantCD[5] != 0 || Sun < 50) Boss.priority = 0;
    return Boss;
}
void Plant::RemovePeaShooter(IPlayer *player, plant pt) {
    int** Plants = player->Camp->getCurrentPlants();
    if (pt.type == 2 && Plants[pt.row][pt.col] != 2)
        player->removePlant(pt.row, pt.col);
    if(pt.type == 3 && Plants[pt.row][pt.col] == 4)
        player->removePlant(pt.row, pt.col);
}

int ZombieUtil::BestAssault(IPlayer *player) {
    bool *without_arr = BattleField::isWithoutWinterArray(player);
    int *stronger_arr = ForceCompare::StrongerArray(player);
    int *LeftLines = player->Camp->getLeftLines();
    int row = -1;
    int min = 100000;
    for (int i = 0; i < 5; ++i) {
        if (without_arr[i] && LeftLines[i] == 1) {
            if (stronger_arr[i] < min) {
                min = stronger_arr[i];
                row = i;
            }
        }
    }
    return row;
}
bool ZombieUtil::isPost(IPlayer *player) {
    int** Plants = player->Camp->getCurrentPlants();
    int* LeftLines = player->Camp->getLeftLines();
    int LeftLineNumber = player->getNotBrokenLines();
    int cols = player->Camp->getColumns();

    int WinterNum = 0;
    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        WinterNum += !BattleField::isWithoutWinter(player, i);
    }
    return WinterNum >= LeftLineNumber-2;
}
int ZombieUtil::StartBestPosition(bool isNormal, IPlayer *player) {
    int* LeftLines = player->Camp->getLeftLines();
    int* SunFlowerNum = BattleField::NumTypeArray(false, 1, player);
    int* PeaNum = BattleField::NumTypeArray(false, 2, player);
    int* NutNum = BattleField::NumTypeArray(false, 4, player);
    int* IronNum = BattleField::NumTypeArray(true, 2, player);
    int max = 0;
    int row = -1;
    if(isNormal){
        for (int i = 0; i < 5; ++i) {
            // 跳过空行
            if (LeftLines[i] == 0) continue;
                // 筛选出没有铁桶僵尸并且没有豌豆和坚果的一行
            else if (IronNum[i] == 0 && NutNum[i] == 0 && PeaNum[i] == 0) {
                // 选出向日葵最多的一行
                if (SunFlowerNum[i] > max) {
                    max = SunFlowerNum[i];
                    row = i;
                }
            }
        }
    }
    else {
        for (int i = 0; i < 5; ++i) {
            // 跳过空行
            if (LeftLines[i] == 0) continue;
                // 筛选出没有铁桶僵尸的一行
            else if (IronNum[i] == 0 && NutNum[i] + PeaNum[i] <=2) {
                // 选出向日葵最多的一行
                if (SunFlowerNum[i] > max) {
                    max = SunFlowerNum[i];
                    row = i;
                }
            }
        }
        if(row == -1){
            for (int i = 0; i < 5; ++i) {
                // 跳过空行
                if (LeftLines[i] == 0) continue;
                    // 筛选出没有铁桶僵尸的一行
                else if (IronNum[i] == 0 && NutNum[i] + PeaNum[i] <=3) {
                    // 选出向日葵最多的一行
                    if (SunFlowerNum[i] > max) {
                        max = SunFlowerNum[i];
                        row = i;
                    }
                }
            }
        }
    }
    return row;
}
int ZombieUtil::StartBestPositionPole(IPlayer* player){
    // 如果这一行有一个坚果，并且没有豌豆，则返回pole，考虑向日葵的数量是最多的
    int* LeftLines = player->Camp->getLeftLines();
    int* SunFlowerNum = BattleField::NumTypeArray(false, 1, player);
    int* PeaNum = BattleField::NumTypeArray(false, 2, player);
    int* NutNum = BattleField::NumTypeArray(false, 4, player);
    int* IronNum = BattleField::NumTypeArray(true, 2, player);
    int max = 0;
    int row = -1;

    for (int i = 0; i < 5; ++i) {
        // 跳过空行
        if (LeftLines[i] == 0) continue;
        // 筛选出没有铁桶僵尸并且没有豌豆和坚果的一行
        else if (IronNum[i] == 0 && NutNum[i] == 1 && PeaNum[i] == 0) {
            // 选出向日葵最多的一行
            if (SunFlowerNum[i] > max) {
                max = SunFlowerNum[i];
                row = i;
            }
        }
    }
    return row;
}
zombie Zombie::Start(IPlayer *player){
    int turn = player->getTime();
    int Sun = player->Camp->getSun();
    int* PlantCD = player->Camp->getPlantCD();
    int rowNormal = ZombieUtil::StartBestPosition(true, player);
    int rowUnNormal = ZombieUtil::StartBestPosition(false, player);
    // 首先在第二回合的时候在向日葵最多的地方放置一个铁桶僵尸
    if(turn == 2) return {2, rowUnNormal};
    // 然后在向日葵最多并且没有
    if(turn == 3) return{1, rowNormal};
    else if(turn > 3){
        if(Sun > 200 && ZombieUtil::StartBestPositionPole(player)!= -1) return {3, ZombieUtil::StartBestPositionPole(player)};
        if(PlantCD[0] == 0) return {1, rowNormal};
    }
    return {-1, -1};
}
zombie Zombie::Assault(IPlayer *player) {
    int* PlantCD = player->Camp->getPlantCD();
    int row = ZombieUtil::BestAssault(player);
    if (row != -1 && PlantCD[1] == 0) return{ 2, row };
    else return { -1, -1 };
}
zombie Zombie::Wait(IPlayer *player) {
    int turn = player->getTime();
    int* PlantCD = player->Camp->getPlantCD();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    int t = -1;
    int y = -1;
    for (int i = 0; i < 5; i++)
    {
        if(LeftLines[i] == 0) break;
        if (turn < 495)
        {

            if (ForceCompare::ForceCalculation(i, false, player) <= 510)
            {
                t = 2;
                y = i;
            }
        }
        else
        {
            if (ForceCompare::ForceCalculation(i, false, player) <= 2200)
            {
                t = 5;
                y = i;
            }
        }
    }
    if (PlantCD[y] != 0 || Sun < 300) { t = -1; y = -1; }
    return { t, y };
}
zombie Zombie::ZombieWave(IPlayer *player) {
    int row = ForceCompare::WeakestRow(player);
    int turn = player->getTime();

    if (turn % 500 == 490) return{ 5, row };
    if (turn % 500 == 0) return{ 5, row };
    if (turn % 500 == 10)return{ 4, row };
    else return { -1, -1 };
}
zombie Zombie::WaveByWave(IPlayer *player)  {
    int row = ForceCompare::WeakestRow(player);
    int turn = player->getTime();

    if (turn % 100 == 0) return{ 5, row };
    if (turn % 100 == 10) return{ 2, row };
    if (turn % 100 == 20) return { 4, row };
    else return { -1, -1 };
}

