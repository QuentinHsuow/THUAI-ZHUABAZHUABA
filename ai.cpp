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
 * (int) priority - 僵尸的优先级
 */
typedef struct tagZombie{
    int type = 0;
    int row = 0;
    int priority = 0;
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
    【函数名称】 Weakest Row
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
 * 3.isWithoutVMArray 计算战场上每一行是否有寒冰射手和建国
 * 4.WherePole 计算战场上哪一行有撑杆跳
 * 5.BestAssault 计算最佳骚扰行数
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
    bool isWithoutWM(IPlayer* player, int row);

    /*************************************************************************
    【函数名称】 isWithoutVMArray
    【函数功能】 计算战场上每一行是否有寒冰射手和建国
    【参数】 \
    【返回值】 bool array[5]; true-没有寒冰射手与建国，false-有;如果这一行被攻破，返回false
     *************************************************************************/
    bool* isWithoutVMArray(IPlayer* player);

    /*************************************************************************
    【函数名称】 WherePole
    【函数功能】 计算战场上哪一行有撑杆跳
    【参数】 \
    【返回值】 -1：没有撑杆跳；[0,4]撑杆跳的行数
     *************************************************************************/
    int WherePole(IPlayer* player);

    /*************************************************************************
   【函数名称】 BestAssault
   【函数功能】 计算最佳骚扰行数
   【参数】 \
   【返回值】 最佳的骚扰行数
    *************************************************************************/
    int BestAssault(IPlayer *player);
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

/* Zombie
 * Start:[1, 25)
 * Assault:[25, 100)
 * Wait:[100, 495), [550, 995)
 * ZombieWave:[495, 550), [995, 1050)
 * WaveByWave: [1050, 2000]
 */
namespace Zombie {
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

    // 考虑BrokenLines问题
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
                sum += j * 5 * 40;//普通僵尸走到跟前时造成的总伤害
            if (Plants[row][j] == 3)//豌豆
                sum += j * 5 * 10;
            if (Plants[row][j] == 4)//坚果墙
                sum += 53 * 10;//注：此处计算坚果墙武力值为估算，是在只有一个豌豆和一个僵尸情况下估算的
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
    int min = 10000;
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
        if (LeftLines[i] == 0) break;
        if (StrongerAmount(i, player) <= 0) isStronger = false;
    }
    return isStronger;
}
int BattleField::DenseOfZombie(IPlayer* player, int row, int col)
{
    int*** Zombies = player->Camp->getCurrentZombies();
    int sum = 0;
    int k = 0;
    while (Zombies[row][col][k] != -1)
    {
        if (Zombies[row][col][k] == 1) sum += 270;
        else if (Zombies[row][col][k] == 2) sum += 820;
        else if (Zombies[row][col][k] == 3) sum += 200 * 5 / 4.5;
        else if (Zombies[row][col][k] == 4) sum += 1600 * 5 / 7;
        else sum += 3000;
        k++;
    }
    return sum;
}
bool BattleField::isWithoutWM(IPlayer* player, int row) {

    int* LeftLines = player->Camp->getLeftLines();
    int cols = player->Camp->getColumns();
    int** Plants = player->Camp->getCurrentPlants();

    if(LeftLines[row] == 1) return false;

    for(int i = 0; i < cols; ++i){
        if(Plants[row][i] == 2 || Plants[row][i] == 4){
            return false;
        }
    }

    return true;
}
bool* BattleField::isWithoutVMArray(IPlayer* player){
    bool* arr = new bool[5];
    for(int i = 0; i < 5; ++i){
        arr[i] = isWithoutWM(player, i);
    }
    return arr;
}
int BattleField::WherePole(IPlayer* player){
    int columns = player->Camp->getColumns();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int r = -1;
    bool flag = false;
    for (int i = 0; i < 5; i++)//防范撑杆的偷袭
    {
        if(LeftLines[i] == 0) break;
        for (int j = 0; j < columns; j++)
        {
            int k = 0;
            while (Zombies[i][j][k] != -1)
            {
                if (Zombies[i][j][k] == 3 && !flag)
                {
                    flag = true;
                    r = i;
                }
                k++;
            }
        }
    }
    return r;
}
int BattleField::BestAssault(IPlayer *player) {
    bool *without_arr = BattleField::isWithoutVMArray(player);
    int *stronger_arr = ForceCompare::StrongerArray(player);
    int *LeftLines = player->Camp->getLeftLines();
    int row = -1;
    int min = 100000;
    for (int i = 0; i < 5; ++i) {
        if (without_arr[i] == 0 && LeftLines[i] == 1) {
            if (stronger_arr[i] < min) {
                min = stronger_arr[i];
                row = i;
            }
        }
    }
    return row;
}
void Util::SetPlant(plant* Plant, int i, int j, int pri, int type)
{
    Plant->row = i;
    Plant->col = j;
    Plant->priority = pri;
    Plant->type = type;
}
plant Util::GetBestPlant(IPlayer *player) {
    int type = player->Camp->getCurrentType();
    plant arr[6];
    arr[0] = Plant::SunFlower(player);
    arr[1] = Plant::WinterPeaShooter(player);
    arr[2] = Plant::PeaShooter(player);
    arr[3] = Plant::SmallNut(player);
    arr[4] = Plant::Pepper(player);
    arr[5] = Plant::Squash(player);

    plant best = arr[0];
    int t = 1;
    for (int i = 1; i < 6; ++i)
        if (arr[i].priority > best.priority) {
            best = arr[i];
            t = i + 1;
        }
    return best;
}
zombie Util::GetBestZombie(IPlayer *player)  {
    int turn = player->getTime();
    if (turn < 25) return Zombie::Start(player);
    if (turn >= 25 && turn < 100) return Zombie::Assault(player);
    if (turn >= 100 && turn < 495) return Zombie::Wait(player);
    if (turn >= 495 && turn < 550) return Zombie::ZombieWave(player);
    if (turn >= 550 && turn < 995) return Zombie::Wait(player);
    if (turn >= 995 && turn < 1050) return Zombie::ZombieWave(player);
    if (turn >= 1050 && turn < 1495) return Zombie::WaveByWave(player);
    if (turn >= 1495 && turn < 1550) return Zombie::ZombieWave(player);
    if (turn >= 1550) return Zombie::WaveByWave(player);
}
plant Plant::SunFlower(IPlayer* player) {

    int* PlantCD = player->Camp->getPlantCD();
    int turn = player->getTime();
    int Sun = player->Camp->getSun();
    int** Plants = player->Camp->getCurrentPlants();
    int* LeftLines = player->Camp->getLeftLines();

    int col = -1;
    int row = -1;
    int p = 0;

    if (turn < 30) {
        for (int i = 0; i < 5; ++i) {
            if(LeftLines[i] == 0) break;
            if (Plants[i][3] == 0) { row = i; col = 3; p = 1300; break; }
            if (Plants[i][4] == 0) { row = i; col = 4; p = 1300; break; }
        }
    }
    else if (turn < 200) {
        for (int i = 0; i < 5; ++i) {
            if(LeftLines[i] == 0) break;
            if (Plants[i][3] == 0) { row = i; col = 3; p = 1000; break; }
            if (Plants[i][4] == 0) { row = i; col = 4; p = 1000; break; }
        }
    }
    else if(ForceCompare::isPlantStronger(player)) {
        for (int i = 0; i < 5; ++i) {
            if(LeftLines[i] == 0) break;
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
                if(LeftLines[i] == 0) break;
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
        for (int j = 0; j < 2; j++)
            for (int i = 0; i < 5; i++)
            {
                if(LeftLines[i] == 0) break;
                if (Plants[i][j] == 0)
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
            if (LeftLines[i] == 0) break;
            //种植坚果，如果一行出现了两个僵尸或者出现了铁桶僵尸
            if (Zombies[i][columns - 1][0] == 2 || Zombies[i][columns - 1][1] != -1)
                Util::SetPlant(&Boss, i, columns - 1, 1000, 4);
        }
    }
    else
    {
        //在战斗后期，自动补齐坚果墙
        for (int j = columns - 3; j <= columns - 1; j++)
            for (int i = 0; i < rows; i++)
            {
                if (LeftLines[i] == 0) break;
                if (Plants[i][j] == 0 && Sun > 450 && LeftLines[i] == 1)//如果有多余阳光，且没有被攻破,则补齐一行坚果墙
                    Util::SetPlant(&Boss, i, j, 800, 4);
            }
    }
    //被动防御优先
    for (int j = 0; j < columns - 1; j++)
        for (int i = 0; i < rows; i++)
        {
            if (LeftLines[i] == 0) break;
            if (Zombies[i][j][0] != -1)//如果僵尸攻入了内地
                Util::SetPlant(&Boss, i, j, 1100, 4);
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
plant Plant::Pepper(IPlayer *player) {

    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int *PlantCD = player->Camp->getPlantCD();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    plant Boss = {0,0,0, 5};
    for(int i=0;i<rows;i++)
    {
        if (LeftLines[i] == 0) break;
        if (ForceCompare::ForceCalculation(i, true, player) - 1100 > ForceCompare::ForceCalculation(i, false, player)
            || ForceCompare::ForceCalculation(i, true, player) > 1700)
            Util::SetPlant(&Boss, i, columns - 1, 1100, 5);//优先级应该较高
    }
    if (PlantCD[4] != 0 || Sun < 125) Boss.priority = 0;
    return Boss;
}
plant Plant::Squash(IPlayer *player) {

    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int *PlantCD = player->Camp->getPlantCD();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    plant Boss = {0,0,0, 6};
    for(int i = 0;i < rows;i++)
    {
        if (LeftLines[i] == 0) break;
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
                if (BattleField::DenseOfZombie(player, i, j) > 1100 && ForceCompare::ForceCalculation(i, true, player) < ForceCompare::ForceCalculation(i, false, player) && Boss.priority < 1150)
                    Util::SetPlant(&Boss, i, j, 1150, 6);//碰到一大坨僵尸且一行没有足够的战力时的的优先度,优先级应次于添加攻击性植物
                k++;
            }
            //绝地反击，如果僵尸快打穿了
            if (j == 1 && Zombies[i][1][0] != -1 && Boss.priority < 2000)
                Util::SetPlant(&Boss, i, 1, 2000, 6);//此地逻辑存疑，待修正
        }
    }
    if (PlantCD[5] != 0 || Sun < 50) Boss.priority = 0;
    return Boss;
}
void Plant::RemovePeaShooter(IPlayer *player, plant pt) {
    int** Plants = player->Camp->getCurrentPlants();
    if (pt.type == 2 && Plants[pt.row][pt.col] != 2)
        player->removePlant(pt.row, pt.col);
}
zombie Zombie::Start(IPlayer *player){

    int turn = player->getTime();
    int* PlantCD = player->Camp->getPlantCD();

    int t = -1;
    int y = -1;
    if (turn < 5){
        if (PlantCD[1] == 0) { t = 2; y = 0; }
        else if (PlantCD[0] == 0) { t = 1; y = 1; }
    }

    else if (PlantCD[1] == 0) { t = 2; y = 0; }

    return { t, y };
}
zombie Zombie::Assault(IPlayer *player) {
    int* PlantCD = player->Camp->getPlantCD();
    int row = BattleField::BestAssault(player);
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

    if (turn % 500 == 495) return{ 5, row };
    if (turn % 500 == 0) return{ 5, row };
    if (turn % 500 == 10)return{ 4, row };
    else return { -1, -1 };
}
zombie Zombie::WaveByWave(IPlayer *player)  {
    int row = ForceCompare::WeakestRow(player);
    int turn = player->getTime();

    if (turn % 100 == 0) return{ 5, row };
    if (turn % 100 == 3) return{ 2, row };
    if (turn % 100 == 5) return { 4, row };
    else return { -1, -1 };
}

