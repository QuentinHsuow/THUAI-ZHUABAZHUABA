#include "ai.h"

/* 植物结构体：
 * (int) row - 植物所在的行数
 * (int) col - 植物所在的列数
 * (int) priority - 植物的优先级
 * (int) type - 植物的类型
 */
struct plant {
    int row;
    int col;
    int priority;
    int type;
};

/* 僵尸结构体
 * (int) type - 僵尸的类型
 * (int) row - 僵尸所在的行数
 */
struct zombie{
    int type;
    int row;
    bool operator == (const zombie& z)const {return type == z.type && row == z.row;}
};

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
    【修改记录】 5.6重写了forcecalculation函数，更改了坚果墙和寒冰射手的武力值计算规则
               5.14OKAY
     *************************************************************************/
    int ForceCalculation(int row, bool isZombie, IPlayer* player);

    /*************************************************************************
    【函数名称】 StrongerAmount
    【函数功能】 计算植物的武力值比僵尸的武力值大多少
    【参数】 row-要比较的行数；
    【返回值】 返回植物武力值与僵尸武力值的差
    【修改记录】 5.14OKAY
     *************************************************************************/
    int StrongerAmount(int row, IPlayer* player);

    /*************************************************************************
    【函数名称】 StrongerArray
    【函数功能】 计算植物的武力值比僵尸的武力值大多少的数组
    【参数】 /
    【返回值】 返回植物武力值与僵尸武力值的差的数组，arr[i]代表第i行的差值
    【修改记录】 5.14OKAY
     *************************************************************************/
    int* StrongerArray(IPlayer* player);

    /*************************************************************************
    【函数名称】 WeakestRow
    【函数功能】 计算僵尸比植物强的最多的一行
    【参数】 /
    【返回值】 返回僵尸比植物强的最多的一行
    【修改记录】 5.14OKAY
     *************************************************************************/
    int WeakestRow(IPlayer* player);

    /*************************************************************************
    【函数名称】 isPlantStronger
    【函数功能】 判断是不是植物比僵尸强
    【参数】 /
    【返回值】 true:植物比僵尸强；false：植物比僵尸弱
    【修改记录】 5.14OKAY
     *************************************************************************/
     bool isPlantStronger(IPlayer* player);
}

/* BattleField
 * @brief: 计算战场上情况（有没有x对象）的函数组
 * 1.DenseOfZombie 计算一格内的僵尸有多少
 * 2.isWithoutVM 计算战场上某一行是否有寒冰射手和建国
 * 3.isWithoutWinterArray 计算战场上每一行是否有寒冰射手和建国
 * ~4.WherePole 计算战场上哪一行有撑杆跳
 * 4.NumZombieArray 计算战场上Type型植物/僵尸的种类
 * 5.NumPlantArray 计算战场上Type型
 * 6.SquashFirstArray
 * 7.WherePlantType
 * 8.WhereZombieType
 * 9.isPlanttype判断某植物在一行的分布
 * 10.isAnySunflower 判断是否有向日葵
 * 11.isFullForce 判断植物是否为满状态
 * 12.isManyZombies 判断一行僵尸是不是很多
 */
namespace BattleField {
    /*************************************************************************
    【函数名称】 DenseOfZombie
    【函数功能】 计算一格内的僵尸有多少
    【参数】 row-要计算的行； col-要计算的列
    【返回值】 返回row行col列有多少僵尸
    【修改记录】 5.14OKAY
     *************************************************************************/
    int DenseOfZombie(IPlayer *player, int row, int col);

    /*************************************************************************
    【函数名称】 isWithoutWiner
    【函数功能】 计算战场上某一行是否有寒冰射手
    【参数】 row-要计算的行数
    【返回值】 true-没有寒冰射手，false-有;如果这一行被攻破，返回false
    【修改记录】 5.14OKAY
     *************************************************************************/
    bool isWithoutWinter(IPlayer *player, int row);

    /*************************************************************************
    【函数名称】 isWithoutWinterArray
    【函数功能】 计算战场上每一行是否有寒冰射手和建国
    【参数】 \
    【返回值】 bool array[5]; true-没有寒冰射手与建国，false-有;如果这一行被攻破，返回false
    【修改记录】 5.14OKAY
     *************************************************************************/
    bool *isWithoutWinterArray(IPlayer *player);

    /*************************************************************************
    【函数名称】 NumZombieArray
    【函数功能】 计算战场上type型僵尸的数量
    【参数】
    【返回值】 int[5]
    【修改记录】 5.14添加
     *************************************************************************/
    int *NumZombieArray(int type, IPlayer *player);

    /*************************************************************************
    【函数名称】 NumPlantArray
    【函数功能】 计算战场上type型植物的数量
    【参数】
    【返回值】 int[5]
    【修改记录】 5.14添加
     *************************************************************************/
    int *NumPlantArray(int type, IPlayer *player);

    /*************************************************************************
   【函数名称】 SquashFirstArray
   【函数功能】 判断squash是不是在最前面一行
   【参数】 \
   【返回值】bool 0-4row; false-without;true-with
   【修改记录】
    *************************************************************************/
    bool *SquashFirstArray(IPlayer *player);

    /*************************************************************************
   【函数名称】 WherePlantType
   【函数功能】
   【参数】 \
   【返回值】 -1 都有， [0,4]没有的行数
   【修改记录】5.6添加函数,5.14改成两个函数
    *************************************************************************/
    int WherePlantType(int type, IPlayer *player);

    /*************************************************************************
   【函数名称】 WhereZombieType
   【函数功能】
   【参数】 \
   【返回值】 -1 都有， [0,4]没有的行数
   【修改记录】5.6添加函数，5.14改成两个函数
    *************************************************************************/
    int WhereZombieType(int type, IPlayer *player);

    /*************************************************************************
   【函数名称】 isPlantType
   【函数功能】 返回一个长度为11的数组，第一个元素为该植物数量n，之后n个元素为植物放置的位置
   【参数】 行数row, 植物的种类t, 数组
   【返回值】 / 返回该植物的数量（为了防止内存泄漏，需要使用前创建一个int[11]数组 ）
   【修改记录】
    *************************************************************************/
    int isPlantType(int row, int t, int arr[11], IPlayer *player);

    /*************************************************************************
   【函数名称】 isAnySunflower
   【函数功能】 判断是否有向日葵
   【参数】 /
   【返回值】 / true-没有向日葵
   【修改记录】
    *************************************************************************/
    bool isAnySunflower(IPlayer *player);

    /*************************************************************************
   【函数名称】 isFullForce
   【函数功能】 判断植物是否发育完全
   【参数】 /
   【返回值】 / true-发育完全
   【修改记录】
    *************************************************************************/
    bool isFullForce(IPlayer* player);

    /*************************************************************************
   【函数名称】 isManyZombies
   【函数功能】 判断场上僵尸是不是很多
   【参数】 僵尸数量临界值num, 行数row
   【返回值】 / true-僵尸大于等于临界值
   【修改记录】
    *************************************************************************/
    bool isManyZombies(int num, int row, IPlayer* player);
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
    【修改记录】5.14okay
     *************************************************************************/
    void SetPlant(plant* Plant, int i, int j, int pri, int type);

    /*************************************************************************
    【函数名称】 GetBestPlant
    【函数功能】 得到当前最佳植物
    【参数】 /
    【返回值】 最佳植物
    【修改记录】5.14okay
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
 *【修改记录】5.06 ：1.新增了后期铲除向日葵的机制； 2.将向日葵先种满行再种满列更改为先种满列再种满行
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
   【函数名称】 StartBestPositionNormal
   【函数功能】 判断start阶段最佳的放置位点
   【参数】 \
   【返回值】 僵尸放置的行数
   【修改记录】5.14增加该函数
             5.15不能完全看向日葵
             5.17找没有战斗力的一行放
    *************************************************************************/
    int StartBestPositionNormal(IPlayer* player);

    /*************************************************************************
   【函数名称】 StartBestPositionBucket
   【函数功能】 判断start阶段是不是最好放置
   【参数】 \
   【返回值】
   【修改记录】5.14add
             5.17 找没有向日葵的一行放
    *************************************************************************/
    int StartBestPositionBucket(IPlayer* player);

    /*************************************************************************
   【函数名称】 StartBestPositionPole
   【函数功能】 判断start阶段是不是最好放置Pole
   【参数】 \
   【返回值】 -1 不应该放置pole， [0,4]放置pole的行数
   【修改记录】5.14 change name
             5.17 如果对手在有铁桶的一行放窝瓜
    *************************************************************************/
    int StartBestPositionPole(IPlayer* player);

    /*************************************************************************
   【函数名称】 isStageFour
   【函数功能】 判断是否停止送人头
   【参数】 \
   【返回值】 false - continue, true - stop
   【修改记录】
    *************************************************************************/
    int BestDistribution(IPlayer* player);

    /*************************************************************************
   【函数名称】
   【函数功能】 判断是否停止送人头
   【参数】 \
   【返回值】 false - continue, true - stop
   【修改记录】
   *************************************************************************/
    int AvoidSquash(IPlayer* player);

    /*************************************************************************
   【函数名称】
   【函数功能】 返回作为僵尸方剩余植物的行数
   【参数】 \
   【返回值】 false - continue, true - stop
   【修改记录】
   *************************************************************************/
    int getLeftLineNumZom(IPlayer* player);

    /*************************************************************************
   【函数名称】
   【函数功能】 返回作为僵尸方剩余植物的行数
   【参数】 \
   【返回值】 false - continue, true - stop
   【修改记录】
   *************************************************************************/
    /*int FinalDistribution(IPlayer* player);
    int FinalNext(IPlayer* player);
    int FinalEnforce(IPlayer* player);*/
}

namespace ZombieStage{
    /*************************************************************************
   【函数名称】 isStageOne
   【函数功能】 判断是否进入二阶段
   【参数】 \
   【返回值】 判断assault和wait的界限
   【修改记录】 5.5 通过寒冰射手是否大于BrokenLines-2来判断是否进入后期
    *************************************************************************/
    bool isStageOne(IPlayer* player);

    /*************************************************************************
   【函数名称】 isStageTwo
   【函数功能】 判断是否进入二阶段
   【参数】 \
   【返回值】 判断assault和wait的界限
   【修改记录】 5.5 通过寒冰射手是否大于BrokenLines-2来判断是否进入后期
    *************************************************************************/
    bool isStageTwo(IPlayer* player);

    /*************************************************************************
   【函数名称】 isStageThree
   【函数功能】 判断是否进入三阶段
   【参数】 \
   【返回值】 判断assault和wait的界限
   【修改记录】 5.5 通过寒冰射手是否大于BrokenLines-2来判断是否进入后期
    *************************************************************************/
    bool isStageThree(IPlayer* player);
}

namespace Zombie {
    /*************************************************************************
    【函数名称】Start
    【函数功能】返回[1,25)回合中需要放置的僵尸
    【参数】 /
    【返回值】 最佳僵尸
    【修改历史】5.5 增加了放在某一行的判断；
              5.18 铁桶能不能放
     *************************************************************************/
    zombie Start(IPlayer *player);
    zombie Assault(IPlayer *player);
    zombie Wait(IPlayer *player);
    zombie ZombieWave2(IPlayer *player);
    zombie ZombieWave3(IPlayer* player);
    zombie WaveByWave(IPlayer *player);
    zombie NextWave(IPlayer* player);
    //zombie FinalBattle(IPlayer* player);
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
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int BrokenLinesScore = player->getBrokenLinesScore();
    int NotBrokenLinesNum = player->getNotBrokenLines();
    int KillPlantsScore = player->getKillPlantsScore();
    int KillZombiesScore = player->getKillZombiesScore();
    int LeftPlants = player->getLeftPlants();
    int Score = player->getScore();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    int sum = 0;
    int planttmp[3][11] = { 0 };//临时存储植物的数量和列数，第一个元素代表个数，后面的代表种植该植物的列数
    int zombietmp[5] = { 0 };//临时存储僵尸的数量

    for (int i = 0; i < columns; i++)//录入僵尸数量信息
    {
        int k = 0;
        while (Zombies[row][i][k] != -1)
        {
            if (Zombies[row][i][k] == 1) zombietmp[0]++;//普通僵尸
            if (Zombies[row][i][k] == 2) zombietmp[1]++;//铁桶僵尸
            if (Zombies[row][i][k] == 3) zombietmp[2]++;//撑杆跳僵尸
            if (Zombies[row][i][k] == 4) zombietmp[3]++;//雪橇僵尸
            if (Zombies[row][i][k] == 5) zombietmp[4]++;//巨人僵尸
            k++;
        }
    }
    for (int j = 0; j < columns; j++)//录入植物数量信息
    {
        if (Plants[row][j] == 2)
        {
            ++planttmp[0][0];
            planttmp[0][(planttmp[0][0])] = j;
        }//冰豌豆
        else if (Plants[row][j] == 3)
        {
            ++planttmp[1][0];
            planttmp[1][(planttmp[1][0])] = j;
        }//豌豆
        else if (Plants[row][j] == 4)
        {
            ++planttmp[2][0];
            planttmp[2][(planttmp[2][0])] = j;
        }//坚果墙
    }

    if (isZombie)//计算僵尸的武力值
    {
        sum += 270 * zombietmp[0] + 820 * zombietmp[1] + 200 * 5 / 4.5 * zombietmp[2] +
               1600 * 5 / 7 * zombietmp[3] + 3000 * zombietmp[4];
    }
    else
    {
        //豌豆射手
        for (int i = 1; i <= planttmp[1][0]; i++)
            sum += (10 - planttmp[1][i]) * 10 * 5;
        //坚果墙
        if (planttmp[2][0] != 0 && zombietmp[4] == 0 && zombietmp[3] == 0)//存在巨人或者雪车，坚果就不顶用了
        {
            int allZombieNum = 0;
            for (int i = 0; i < 3; ++i)
                allZombieNum += zombietmp[i];// 计算僵尸总量
            if(allZombieNum != 0)
                sum += 530 * planttmp[2][0] * (1 - 1 / allZombieNum);//存在撑杆僵尸，坚果墙将会被削弱
            if (planttmp[1][0] == 0 && planttmp[0][0] == 0 ) sum = 100 * planttmp[2][0];//如果没有豌豆掩护，坚果用处降低
        }
        //寒冰射手
        for (int i = 1; i <= planttmp[0][0]; i++)
            sum += (10 - planttmp[0][i]) * 20 * 5;
        if (planttmp[0][0] != 0) sum *= 2;//如果存在寒冰射手，可以近似认为，植物的能力翻倍了！
    }
    return sum;
}
int ForceCompare::StrongerAmount(int row, IPlayer* player) {
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
bool ForceCompare::isPlantStronger(IPlayer* player) {
    int* LeftLines = player->Camp->getLeftLines();
    bool isStronger = true;
    for (int i = 0; i < 5; ++i) {
        if (LeftLines[i] == 0) continue;
        if (StrongerAmount(i, player) < 0) isStronger = false;//修改
    }
    return isStronger;
}
int BattleField::DenseOfZombie(IPlayer* player, int row, int col) {

    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();

    if (LeftLines[row] == 0) return 0;

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
int* BattleField::NumZombieArray(int type, IPlayer*player){
    int*** Zombies = player->Camp->getCurrentZombies();
    int cols = player->Camp->getColumns();
    int* LeftLines = player->Camp->getLeftLines();
    int* arr = new int[5];
    for(int i = 0; i < 5; ++i) arr[i] = 0;

    for(int i = 0; i < 5; ++i){

        if(LeftLines[i] == 0) continue;

        for(int j = 0; j < cols; j++){
            int k = 0;
            while(Zombies[i][j][k] != -1){
                if(Zombies[i][j][k] == type){
                    arr[i]++;
                }
                ++k;
            }
        } // col-loop

    } // row-loop


    return arr;
}
int* BattleField::NumPlantArray(int type, IPlayer *player) {
    int** Plants = player->Camp->getCurrentPlants();
    int cols = player->Camp->getColumns();
    int* LeftLines = player->Camp->getLeftLines();
    int* arr = new int[5];
    for(int i = 0; i < 5; ++i) arr[i] = 0;

    for(int i = 0; i < 5; ++i){

        if(LeftLines[i] == 0) continue;

        for(int j = 0; j < cols; ++j){
            if(Plants[i][j] == type){
                arr[i]++;
            }
        }

    } // row-loop

    return arr;
}
bool* BattleField::SquashFirstArray(IPlayer* player){
    int** Plants = player->Camp->getCurrentPlants();
    int cols = player->Camp->getColumns();
    int* GArr = NumZombieArray(5, player);
    int* SArr = NumZombieArray(4, player);
    bool* arr = new bool[5];
    for(int i = 0; i < 5; ++i){
        if((Plants[i][cols-1] == 6 || (Plants[i][cols-2] == 6 && Plants[i][cols-1] == 0)) && (SArr[i] != 0 || GArr[i] != 0)) arr[i] = true;
        else arr[i] = false;
    }
    return arr;
}
int BattleField::WherePlantType(int type, IPlayer *player) {
    int* NumType = NumPlantArray(type, player);
    int* LeftLines = player->Camp->getLeftLines();
    int** Plants = player->Camp->getCurrentPlants();
    int cols = player->Camp->getColumns();
    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        if(NumType[i] != 0) return i;
    }
    delete[] NumType;
    return -1;
}
int BattleField::WhereZombieType(int type, IPlayer *player) {
    int* NumType = NumZombieArray(type, player);
    int* LeftLines = player->Camp->getLeftLines();
    int*** Zombies = player->Camp->getCurrentZombies();
    int cols = player->Camp->getColumns();
    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        if(NumType[i] != 0) return i;
    }
    delete[] NumType;
    return -1;
}
int BattleField::isPlantType(int row, int t, int arr[11], IPlayer* player) {
    int columns = player->Camp->getColumns();
    int** Plants = player->Camp->getCurrentPlants();

    for (int i = 0; i < 11; i++)
        arr[i] = 0;
    for (int j = 0; j < columns; j++)
        if (Plants[row][j] == t)
        {
            ++arr[0];
            arr[(arr[0])] = j;
        }
    return arr[0];
}
bool BattleField::isAnySunflower(IPlayer* player)
{
    int* LeftLines = player->Camp->getLeftLines();
    int** Plants = player->Camp->getCurrentPlants();
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        if (LeftLines[i] == 0) continue;
        for (int j = 0; j < 10; j++)
            if (Plants[i][j] == 1) sum++;
        if (sum >= 2) return false;
    }
    return true;
}
bool BattleField::isFullForce(IPlayer* player)
{
    int* arr = BattleField::NumPlantArray(2, player);
    int* LeftLines = player->Camp->getLeftLines();
    for (int i = 0; i < 5; ++i)
    {
        if (LeftLines[i] == 0) continue;
        if (arr[i] < 2) return false;
    }
    return true;
}
bool BattleField::isManyZombies(int num, int row, IPlayer* player)
{
    int*** Zombies = player->Camp->getCurrentZombies();
    int count = 0;
    for (int j = 0; j < 10; j++)
    {
        for (int k = 0; Zombies[row][j][k] != -1; ++k)
        {
            ++count;
            if (count >= num) return true;
        }
    }
    return false;
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
zombie Util::GetBestZombie(IPlayer *player){
    int turn = player->getTime();
    if(turn < 370) {
        if (!ZombieStage::isStageOne(player)) return Zombie::Start(player);
        else if (ZombieStage::isStageOne(player) && !ZombieStage::isStageTwo(player)) return Zombie::Assault(player);
    }
    // [370,480) 摆烂
    else if((turn >= 480 && turn < 550) || (turn >= 980 && turn < 1050) || (turn >= 1480 && turn < 1550)){
        if(!ZombieStage::isStageThree(player)) return Zombie::ZombieWave2(player);
        else if(ZombieStage::isStageThree(player)) return Zombie::ZombieWave3(player);
    }
    else if(turn >= 700 && turn < 980 ){
        if (!ZombieStage::isStageTwo(player)) return Zombie::Assault(player);
        else if (ZombieStage::isStageTwo(player) && !ZombieStage::isStageThree(player))return Zombie::Wait(player);
    }
    else if ((turn >= 550 && turn < 700) || (turn >= 1050 && turn < 1400) || turn >= 1550){
        return Zombie::NextWave(player);
    }
    return {-1, -1};
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

    if (turn < 50) {
        for (int j = 4; j >= 3; --j)
            for (int i = 0; i < 5; ++i) {
                if (LeftLines[i] == 0 || ForceCompare::ForceCalculation(i, false, player) <
                                         2 * ForceCompare::ForceCalculation(i, true, player)) continue;//如果一行产生威胁，就不种向日葵
                if (Plants[i][j] == 0) { row = i; col = j; p = 1300; break; }
                if (Plants[i][j] == 0) { row = i; col = j; p = 1300; break; }
            }
    }
    else if (turn < 200 && Sun > 125) {
        for (int j = 4; j >= 3; --j)
            for (int i = 0; i < 5; ++i) {
                if (LeftLines[i] == 0 || ForceCompare::ForceCalculation(i, false, player) <
                                         2 * ForceCompare::ForceCalculation(i, true, player)) continue;//如果一行产生威胁，就不种向日葵
                if (Plants[i][j] == 0) { row = i; col = j; p = 1000; break; }
                if (Plants[i][j] == 0) { row = i; col = j; p = 1000; break; }
            }
    }
    else if (ForceCompare::isPlantStronger(player)) {
        int tmp = 3;
        int i = 0;
        for (i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0) continue;
            if (Plants[i][3] == 2) break;
        }
        if (i != 5) tmp = 6;//如果发现第3列开始种寒冰了，将向日葵调整至第6列
        for (int i = 0; i < 5; ++i) {
            if (LeftLines[i] == 0 || ForceCompare::ForceCalculation(i, false, player) <
                                     2 * ForceCompare::ForceCalculation(i, true, player)) continue;
            if (Plants[i][4] == 0) { row = i; col = 4; p = 1150; break; }
            if (Plants[i][tmp] == 0) { row = i; col = tmp; p = 1150; break; }
            if (Plants[i][7] == 0 && turn < 500)
            {
                bool flag = true;
                for (int j = 0; j < 5; j++)
                    if (Plants[j][2] != 2) flag = false;//前500回，如果种了一列寒冰，就在第七行种植临时的向日葵
                if (flag) { row = i; col = 7; p = 1150; break; }
            }
        }
    }

    if (Sun < 50) p = 0;
    if (PlantCD[0] != 0) p = 0;
    if (col == -1 || row == -1) return { 0, 0, 0 };
    else return { row, col, p, 1 };
}
plant Plant::WinterPeaShooter(IPlayer* player) {

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
        int tmp[5] = { 2, 0, 1, 3, 5 };
        for (int j = 4; j >= 0; j--)
            for (int i = 4; i >= 0; --i) {
                if (LeftLines[i] == 0) continue;
                if (Plants[i][tmp[j]] != 2)
                {
                    row = i;
                    col = tmp[j];
                    p = 550;
                }
            }
    }
    if (PlantCD[1] != 0 || Sun < 500 || col == -1) p = 0;
    if (BattleField::isAnySunflower(player) && Sun < 450) p = 0;//留足够的阳光种植向日葵
    return { row, col, p, 2 };
}
plant Plant::PeaShooter(IPlayer* player) {

    int* PlantCD = player->Camp->getPlantCD();
    int Sun = player->Camp->getSun();
    int** Plants = player->Camp->getCurrentPlants();
    int* LeftLines = player->Camp->getLeftLines();
    int*** Zombies = player->Camp->getCurrentZombies();
    int turn = player->getTime();
    int N = player->getNotBrokenLines();

    int p = 0;
    int row = 0;
    int col = 0;

    if (!ForceCompare::isPlantStronger(player))//如果阳光比较少，节约一点
    {
        p = 1150;
        //在没有坚果保护的情况下别种豌豆,保证先种坚果
        int* arr = new int[N];
        int* arrRow = new int[N];
        for (int i = 0; i < N; i++)
        {
            arr[i] = 0;
            arrRow[i] = 0;
        }
        int tmpaccount = 0;
        for (int i = 0; i < 5; i++)
            if (LeftLines[i] != 0)
            {
                arr[tmpaccount] = ForceCompare::StrongerAmount(i, player);
                arrRow[tmpaccount] = i;
                tmpaccount++;
            }
        for (int i = 0; i < N - 1; i++)
            for (int j = 0; j < N - 1 - i; j++)
            {
                if (arr[j + 1] < arr[j])
                {
                    int tmparr = 0;
                    int tmp = 0;
                    tmparr = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmparr;
                    tmp = arrRow[j + 1]; arrRow[j + 1] = arrRow[j]; arrRow[j] = tmp;
                }
            }//将strongarray排序
        /*
        std::cout << arrRow[0] << " "
            << arrRow[1] << " "
            << arrRow[2] << " "
            << arrRow[3] << " "
            << arrRow[4] << " " << std::endl;
            */
        int i = 0;
        for (i = 0; i < N; ++i)
        {
            int j = 0;
            if (arr[i] >= 0)
            {
                p = 0;
                break;
            }
            int tmpj = ForceCompare::ForceCalculation(arrRow[i], true, player) / 50 + 2;
            if (tmpj > 10) tmpj = 10;
            for (j = 0; j < tmpj; ++j)
                if (Zombies[(arrRow[i])][j][0] != -1)
                    break;
            if (j == tmpj || ForceCompare::ForceCalculation(arrRow[i], false, player) != 0)
            {
                row = arrRow[i];
                break;
            }
        }
        if (i == N) p = 0;
        if (Plants[row][0] == 0) col = 0;
        else if (Plants[row][1] == 0) col = 1;
        else col = -1;//没地方种了，以后可以在这里加入铲子
    }
    else if (ForceCompare::isPlantStronger(player) && turn > 50)// 有余力时，摆满一列
    {
        for (int j = 1; j >= 0; j--)
            for (int i = 0; i < 5; i++)
            {
                if (LeftLines[i] == 0) continue;
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
    if (BattleField::isAnySunflower(player) && Sun < 150) p = 0;//留足够的阳光种植向日葵
    return { row, col, p, 3 };
}
plant Plant::SmallNut(IPlayer* player) {

    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    plant Boss = { 0, 0, 0, 4 };
    /*
    //在开始时在保护战斗力弱的行
    if (turn < 200)
    {
        //检索是否有比较弱的行，种植坚果墙
        for (int i = 0; i < rows; i++)
        {
            if (LeftLines[i] == 0) continue;
            //种植坚果，如果一行出现了铁桶僵尸
            if (Zombies[i][columns - 2][0] == 2)
                Util::SetPlant(&Boss, i, columns - 2, 1000, 4);
        }
    }
    */
    if(turn >= 200)
    {
        //在战斗后期，自动补齐坚果墙
        for (int i = 0; i < rows; i++)
        {
            if (LeftLines[i] == 0) continue;
            if (Plants[i][columns - 1] == 0 && Sun > 450 && LeftLines[i] == 1)//如果有多余阳光，且没有被攻破,则补齐一行坚果墙
                Util::SetPlant(&Boss, i, columns - 1, 800, 4);
        }
    }
    //被动防御优先
    for (int j = columns - 2; j >= 0; j--)// 从后往前遍历，前面的结果会覆盖后面的结果，从而使得在最前面的僵尸前放置
        for (int i = 0; i < rows; i++)
        {
            if (LeftLines[i] == 0) continue;
            int ptmp = 1150 - (j - 7) * 5 - ForceCompare::StrongerAmount(i, player) / 100;//种植坚果的比较机制
            if (Zombies[i][j][0] != -1 && Boss.priority < ptmp && Plants[i][j] == 0) {//如果僵尸攻入了内地
                if (j > 1 && Plants[i][j - 1] == 0) Util::SetPlant(&Boss, i, j - 1, ptmp, 4);
                else Util::SetPlant(&Boss, i, j, ptmp, 4);
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
        if (PlantCD[3] != 0 || Sun < 50) Util::SetPlant(&Boss, 0, 0, 0, 4);//CD不够时，CD自动清零
        if (BattleField::isAnySunflower(player) && Sun < 100) Boss.priority = 0;//留足够的阳光种植向日葵
    }
    return Boss;
}
plant Plant::Pepper(IPlayer* player) {

    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int* PlantCD = player->Camp->getPlantCD();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();
    int turn = player->getTime();
    int* arr = BattleField::NumPlantArray(2, player);

    int value = 1600;//在比赛开始时，降低使用辣椒的门槛，使得两个铁桶就能触发辣椒
    if (turn > 50 && !BattleField::isFullForce(player)) value = 1700;
    else if (turn > 50 && BattleField::isFullForce(player)) value = 4100;

    plant Boss = { 0,0,0, 5 };
    for (int i = 0; i < rows; i++)
    {
        if (LeftLines[i] == 0) continue;
        int ptmp = 1200 - ForceCompare::StrongerAmount(i, player) / 200;
        //优先度调节，如果一格内的僵尸浓度超过总战力值的一半，优先放倭瓜，否则放辣椒
        if (ForceCompare::ForceCalculation(i, true, player) - 1200 > ForceCompare::ForceCalculation(i, false, player)
            || ForceCompare::ForceCalculation(i, true, player) > value
            || BattleField::isManyZombies(3, i, player))
            if (Boss.priority < ptmp)
                Util::SetPlant(&Boss, i, columns - 1, ptmp, 5);//优先级应该较高
    }
    if (PlantCD[4] != 0 || Sun < 125) Boss.priority = 0;
    if (BattleField::isAnySunflower(player) && Sun < 175) Boss.priority = 0;//留足够的阳光种植向日葵
    return Boss;
}
plant Plant::Squash(IPlayer* player) {

    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int* PlantCD = player->Camp->getPlantCD();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();
    int turn = player->getTime();
    int** Plants = player->Camp->getCurrentPlants();

    plant Boss = { 0,0,0, 6 };
    for (int i = 0;i < rows;i++)
    {
        if (LeftLines[i] == 0) continue;
        for (int j = 0;j < columns;j++)
        {
            int ttmp = 1100;
            if (BattleField::DenseOfZombie(player, i, j) * 2 > ForceCompare::ForceCalculation(i, true, player))
                ttmp = 1200;
            int ptmp = ttmp + BattleField::DenseOfZombie(player, i, j) / 200;//根据战力值来区分优先度
            int puttmp = 800;//前期使用倭瓜的门槛较低，即一个铁桶就使用
            if (turn > 200 || ForceCompare::isPlantStronger(player)) puttmp = 1200;
            if (BattleField::DenseOfZombie(player, i, j) > puttmp
                && Boss.priority < ptmp)//取最大优先度
                Util::SetPlant(&Boss, i, j, ptmp, 6);
            /*
            if (j > 1 && Plants[i][j - 1] == 0) Util::SetPlant(&Boss, i, j - 1, ptmp, 6);
            else Util::SetPlant(&Boss, i, j, ptmp, 6);//碰到一大坨僵尸且一行没有足够的战力时的的优先度,优先级应次于添加攻击性植物
            */
            //绝地反击，如果僵尸快打穿了
            if (j == 0 && Zombies[i][0][0] != -1 && Boss.priority < 2000)
                Util::SetPlant(&Boss, i, 0, 2000, 6);//此地逻辑存疑，待修正
        }
    }
    if (ForceCompare::isPlantStronger(player))//倭瓜长城
    {
        int i = 0, j = 0;
        bool flag = true;
        for (i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0) continue;
            if (Plants[i][0] != 2) flag = false;
        }
        if (flag)//种了足够多的寒冰射手
        {
            for (i = 0; i < 5; i++)
            {
                if (LeftLines[i] == 0) continue;
                if (Plants[i][columns - 2] == 0 || Plants[i][columns - 2] == 4)
                    Util::SetPlant(&Boss, i, columns - 2, 500, 6);
            }
        }
    }
    if (PlantCD[5] != 0 || Sun < 50) Boss.priority = 0;
    if (BattleField::isAnySunflower(player) && Sun < 100) Boss.priority = 0;//留足够的阳光种植向日葵
    return Boss;
}
void Plant::RemovePeaShooter(IPlayer* player, plant pt) {
    int** Plants = player->Camp->getCurrentPlants();
    if (pt.type == 2 && Plants[pt.row][pt.col] != 2)
        player->removePlant(pt.row, pt.col);
    if (pt.type == 3 && Plants[pt.row][pt.col] == 4)
        player->removePlant(pt.row, pt.col);
    if (pt.type == 6 && Plants[pt.row][pt.col] == 4)
        player->removePlant(pt.row, pt.col);
}
bool ZombieStage::isStageOne(IPlayer *player) {
    // 有LeftLine行都有豌豆了
    int LeftLineNumber = ZombieUtil::getLeftLineNumZom(player);
    int* LeftLines = player->Camp->getLeftLines();
    int* NumPea = BattleField::NumPlantArray(3, player);
    int* NumWinter = BattleField::NumPlantArray(2, player);
    int greater = 0;
    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        if(NumPea[i] != 0 || NumWinter[i] != 0) greater++;
    }
    return greater >= LeftLineNumber;
}
bool ZombieStage::isStageTwo(IPlayer *player) {
    // 有LeftLine-1行都有一个寒冰或者2个豌豆了
    int LeftLineNumber = ZombieUtil::getLeftLineNumZom(player);
    int turn = player->getTime();
    int* NumWinter = BattleField::NumPlantArray(2, player);
    int* NumPea = BattleField::NumPlantArray(3, player);
    int greater = 0;
    for(int i = 0; i < 5; ++i)
        if(NumWinter[i] >= 1 || NumPea[i] >= 2) greater++;
    return greater >= LeftLineNumber-1;
}
bool ZombieStage::isStageThree(IPlayer* player){
    // 有LeftLine-1行都有2个寒冰了
    int LeftLineNumber = ZombieUtil::getLeftLineNumZom(player);
    int turn = player->getTime();
    int* NumWinter = BattleField::NumPlantArray(2, player);
    int greater = 0;
    for(int i = 0; i < 5; ++i)
        if(NumWinter[i] >= 2) greater++;
    return greater >= LeftLineNumber-1;
}
int ZombieUtil::BestAssault(IPlayer *player) {
    int* LeftLines = player->Camp->getLeftLines();
    int* PeaNum = BattleField::NumPlantArray(3, player);
    int* WinterNum = BattleField::NumPlantArray(2, player);
    int* NutNum = BattleField::NumPlantArray(4, player);
    int* IronNum = BattleField::NumZombieArray(2, player);
    int* NorNum = BattleField::NumZombieArray(1, player);
    int Arr[5];
    for(int i = 0; i < 5; ++i)
        Arr[i] = PeaNum[i] + 4 * WinterNum[i] + NutNum[i] - 2 * IronNum[i] - NorNum[i];

    int row = -1;
    int min = 100;
    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        if(min > Arr[i]){
            min = Arr[i];
            row = i;
        }
    }
    delete[] PeaNum;
    delete[] WinterNum;
    delete[] NutNum;
    delete[] NorNum;
    delete[] IronNum;

    return row;
}
int ZombieUtil::StartBestPositionNormal( IPlayer *player) {
    int turn = player->getTime();
    int *LeftLines = player->Camp->getLeftLines();
    int *SunFlowerNum = BattleField::NumPlantArray(1, player);
    int *PeaNum = BattleField::NumPlantArray(3, player);
    int *NutNum = BattleField::NumPlantArray(4, player);
    int *IronNum = BattleField::NumZombieArray(2, player);
    int* NorNum = BattleField::NumZombieArray(1, player);
    int* PoleNum = BattleField::NumZombieArray(3, player);
    int num = 100;
    int max = -1;
    int row = -1;

    if(turn == 2) {
        for (int i = 0; i < 5; ++i) {
            // 跳过空行
            if (LeftLines[i] == 0) continue;
            // 筛选出没有铁桶僵尸并且没有豌豆和坚果的一行
            if (IronNum[i] == 0 && PeaNum[i] == 0 && NutNum[i] == 0 && PoleNum[i] == 0) {
                if(row == -1 ||( row != -1 && (SunFlowerNum[i] > SunFlowerNum[row])) ) row = i;
            }
        }
    }//turn == 3

    else{
        for(int i = 0; i < 5; ++i){
            if(LeftLines[i] == 0) continue;
            // 否则就在没有建国或者没有豌豆并且向日葵最多的地方放普僵
            if(NutNum[i] == 0 || PeaNum[i] == 0){
                if(SunFlowerNum[i] >= max){
                    if((row != -1 && NutNum[i] + PeaNum[i] < NutNum[row] + PeaNum[row]) || row == -1) {
                        max = SunFlowerNum[i];
                        row = i;
                    }
                }
            }
        }
    }

    delete[] SunFlowerNum;
    delete[] NutNum;
    delete[] NorNum;
    delete[] PoleNum;
    delete[] PeaNum;

    return row;
}
int ZombieUtil::StartBestPositionBucket(IPlayer *player) {
    int turn = player->getTime();
    int* LeftLines = player->Camp->getLeftLines();
    int* SunFlowerNum = BattleField::NumPlantArray(1, player);
    int* NutNum = BattleField::NumPlantArray(4, player);
    int* PeaNum = BattleField::NumPlantArray(3, player);
    int* IronNum = BattleField::NumZombieArray(2, player);

    int row = -1;
    int max = 0;

    // 找有向日葵的一行放
    if(turn == 2) {
        for (int i = 0; i < 5; ++i) {
            if (LeftLines[i] == 0) continue;
            if (SunFlowerNum[i] != 0) row = i;
        }
        if(row == -1){
            for(int i = 0; i < 5; ++i){
                if(LeftLines[i] == 0) continue;
                if(NutNum[i] == 0 && PeaNum[i] == 0) row = i;
            }
        }
    }// turn == 1


    else{
        for(int i = 0; i < 5; ++i){
            if(LeftLines[i] == 0) continue;
            if(SunFlowerNum[i] == max && NutNum[i] + PeaNum[i] < NutNum[row] + PeaNum[row]){
                max = SunFlowerNum[i];
                row = i;
            }
            else if(SunFlowerNum[i] > max) {
                max = SunFlowerNum[i];
                row = i;
            }
        } // row-loop
    }

    delete[] SunFlowerNum;
    delete[] NutNum;
    delete[] PeaNum;
    delete[] IronNum;

    return row;
}
int ZombieUtil::StartBestPositionPole(IPlayer* player){
    // 如果这一行有一个坚果，并且没有豌豆，则返回pole，考虑向日葵的数量是最多的
    int turn = player->getTime();
    int* LeftLines = player->Camp->getLeftLines();
    int* PeaNum = BattleField::NumPlantArray(3, player);
    int* IronNum = BattleField::NumZombieArray(2, player);
    int* NutNum = BattleField::NumPlantArray(4, player);
    int* NorNum = BattleField::NumZombieArray(1, player);
    int* SunFlowerNum = BattleField::NumPlantArray(1, player);
    int row = -1;

    // 在第三回合的特殊判断
    if(turn == 4) {
        for (int i = 0; i < 5; ++i) {
            // 跳过空行
            if (LeftLines[i] == 0) continue;
            // 筛选出没有铁桶僵尸并且没有豌豆和坚果的一行
            if (IronNum[i] == 0 && PeaNum[i] == 0 && NutNum[i] == 0 && NorNum[i] == 0) {
                if( row == -1 ||( row != -1 &&(SunFlowerNum[i] > SunFlowerNum[row])))row = i;
            }
        }
    }//turn == 5

    delete[] PeaNum;
    delete[] IronNum;
    delete[] NutNum;

    return row;
}

int ZombieUtil::BestDistribution(IPlayer *player) {
    int* GagNum = BattleField::NumZombieArray(5, player);
    int* SleNum = BattleField::NumZombieArray(4, player);
    int* WinterNum = BattleField::NumPlantArray(2, player);
    int ZomNum[5];
    for(int i = 0; i < 5; ++i) ZomNum[i] = GagNum[i] + SleNum[i];

    int row = -1;
    int min = 6;

    for(int i = 0; i < 5; ++i){
        if(ZomNum[i] == 0){
            if(WinterNum[i] < min){
                min = WinterNum[i];
                row = i;
            }
        }
    }

    delete[] GagNum;
    delete[] SleNum;
    delete[] WinterNum;

    return row;
}
int ZombieUtil::AvoidSquash(IPlayer* player){
    bool* SquashArr = BattleField::SquashFirstArray(player);
    int* LeftLines = player->Camp->getLeftLines();
    int* StrArr = ForceCompare::StrongerArray(player);
    int row = -1;
    int min = 100000;
    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        if(SquashArr[i] != 0 && StrArr[i] < min){
            min = StrArr[i];
            row = i;
        }
    }
    return row;
}
int ZombieUtil::getLeftLineNumZom(IPlayer *player) {
    int* LeftLines = player->Camp->getLeftLines();
    int left = 0;
    for(int i = 0; i < 5; ++i)
        if(LeftLines[i] == 1) left++;
    return left;
}
/*
int ZombieUtil::FinalDistribution(IPlayer *player) {
    int* GArr = BattleField::NumZombieArray(5, player);
    int* SArr = BattleField::NumZombieArray(4, player);
    int* WinterNum = BattleField::NumPlantArray(2, player);
    int* LeftLines = player->Camp->getLeftLines();
    int max = 10000;
    int row = -1;

    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        if(GArr[i] == 0 && SArr[i] == 0){
            if(row == -1 || (row != -1 && WinterNum[i] < WinterNum[row])) row = i;
        }
    }
    return row;
}
int ZombieUtil::FinalNext(IPlayer *player) {
    int* GArr = BattleField::NumZombieArray(5, player);
    int* SArr = BattleField::NumZombieArray(4, player);
    int* LeftLines = player->Camp->getLeftLines();

    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        if(GArr[i] != 0 && SArr[i] == 0) return i;
    }
    return -1;
}
int ZombieUtil::FinalEnforce(IPlayer *player) {
    int* GArr = BattleField::NumZombieArray(5, player);
    int* SArr = BattleField::NumZombieArray(4, player);
    int* WinArr = BattleField::NumPlantArray(2, player);
    int* LeftLines = player->Camp->getLeftLines();
    int maxrow = 0;

    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        if(GArr[i] != 0 && SArr[i] != 0) maxrow++;
        if(maxrow == 2) return i;
    }
    return -1;
}
 */
zombie Zombie::Start(IPlayer *player){
    int turn = player->getTime();
    int Sun = player->Camp->getSun();
    int* PlantCD = player->Camp->getPlantCD();
    int rowNormal = ZombieUtil::StartBestPositionNormal(player);
    int rowBucket = ZombieUtil::StartBestPositionBucket(player);
    int rowPole = ZombieUtil::StartBestPositionPole(player);

    // 前期的特定操作
    //if(turn == 2 && rowBucket != -1) return {2, rowBucket};
    if(turn == 2 && rowNormal != -1) return{1, rowNormal};
    if(turn == 4 && rowPole != -1) return{3, rowPole};

    // 从第十回合开始
    if(turn > 6){
        if(rowBucket != -1 && PlantCD[1] == 0 && Sun > 115) return {2, rowBucket};
        if(rowNormal != -1 && PlantCD[0] == 0) return {1, rowNormal};
    }
    return {-1, -1};
}
zombie Zombie::Assault(IPlayer *player) {
    int turn = player->getTime();
    int Sun = player->Camp->getSun();
    int* PlantCD = player->Camp->getPlantCD();
    int row = ZombieUtil::BestAssault(player);

    if (row != -1 && PlantCD[1] == 0) return{ 2, row };
    else if (Sun >= PlantCD[1] * (turn % 200) - 20 && row != -1) return {1, row};
    return { -1, -1 };
}
zombie Zombie::Wait(IPlayer *player) {
    // 唯一的目标是连续放两个g和一个冰车
    int* PlantCD = player->Camp->getPlantCD();
    int Sun = player->Camp->getSun();
    int turn = player->getTime();
    int SumSun = 800;
    int WhereG = BattleField::WhereZombieType(5, player);
    if(turn < 600) SumSun -= 1000 + 800 - (600 - turn) * 3;
    else if(turn < 800) SumSun -= 1000 + (800 - turn) * 4;
    else if(turn < 1000) SumSun -= (1000 - turn) * 5;

    if(Sun > SumSun + 700 && Sun > 700) return {5, ForceCompare::WeakestRow(player)};
    if(WhereG != -1 && PlantCD[4] != 0 && Sun > SumSun + 100 && Sun > 300) return {4, ForceCompare::WeakestRow(player)};
    if(WhereG != -1 && PlantCD[4] == 0 && Sun > SumSun + 100 && Sun > 300) return {5, ForceCompare::WeakestRow(player)};

    return {-1, -1};
}
zombie Zombie::ZombieWave2(IPlayer *player) {
    int Sun = player->Camp->getSun();
    int row = ForceCompare::WeakestRow(player);
    int disRow = ZombieUtil::BestDistribution(player);
    int turn = player->getTime();

    if (turn % 500 == 490) return {5, row};
    if (turn % 500 == 495 && Sun > 350) return {4,row};
    if (turn % 500 == 500) return {5, disRow};
    if (turn % 500 == 510)  return {4, row};
    if (turn % 500 >= 20 && turn % 500 <= 50) return {5, row};
    return {-1, -1};

}
zombie Zombie::ZombieWave3(IPlayer *player) {
    int Sun = player->Camp->getSun();
    int row = ForceCompare::WeakestRow(player);
    int turn = player->getTime();

    if (turn % 500 == 480) return{ 5, row };
    if (turn % 500 == 495 && Sun > 650) return{ 4, row };
    if (turn % 500 == 5)return{ 5, row };
    if (turn % 500 >= 20 && turn % 500 <= 50) return {4, row};
    return { -1, -1 };
}
zombie Zombie::NextWave(IPlayer *player) {
    int turn = player->getTime();
    int AvoidRow = ZombieUtil::AvoidSquash(player);
    if (AvoidRow != -1) return {2, AvoidRow};

    int* PlantCD = player->Camp->getPlantCD();
    int Sun = player->Camp->getSun();
    int WhereG = BattleField::WhereZombieType(5, player);
    int WhereS = BattleField::WhereZombieType(4, player);

    int* IronNum = BattleField::NumZombieArray(2, player);
    int* PeaNum = BattleField::NumPlantArray(3, player);
    int* WinterNum = BattleField::NumPlantArray(2, player);
    int* LeftLines = player->Camp->getLeftLines();
    int row = -1;
    int min = 100;
    for(int i = 0; i < 5; ++i){
        if(LeftLines[i] == 0) continue;
        if(WinterNum[i] <= 3 && PeaNum[i] < 3){
            if(WinterNum[i] < min){
                min = WinterNum[i];
                row = i;
            }
        }
    }

    delete[] PeaNum;
    delete[] WinterNum;

    int WRow = ForceCompare::WeakestRow(player);
    if ((WhereG != -1 || row != -1 || WhereS != -1 || turn > 1550) && Sun > 300 && WRow != -1) {
        if(PlantCD[4] == 0) return {5, WRow};
        else if(PlantCD[3] == 0 && Sun > 300) return{4, WRow};
    }
    return {-1, -1};
}
/*
zombie Zombie::FinalBattle(IPlayer *player) {
    int first = ZombieUtil::FinalDistribution(player);
    int next = ZombieUtil::FinalNext(player);
    int enforce = ZombieUtil::FinalEnforce(player);
    int* PlantCD = player->Camp->getPlantCD();
    int Sun = player->Camp->getSun();
    int turn = player->getTime();
    int AvoidRow = ZombieUtil::AvoidSquash(player);
    int* IronNum = BattleField::NumZombieArray(2, player);

    if(AvoidRow != -1) return {2, AvoidRow};

    if(enforce != -1 && PlantCD[4] == 0 && Sun >= 300) return {5, enforce};
    else if(enforce != -1 && PlantCD[3] == 0 && Sun >= 300) return {4, enforce};
    if(first != -1 && PlantCD[4] == 0 && Sun >= 300) return {5, first};
    else if(next != -1 && PlantCD[4] == 0 && Sun >= 300) return {5, next};
    else if(next != -1 && PlantCD[3] == 0 && Sun >= 300) return {4, next};
    return {-1, -1};
}*/