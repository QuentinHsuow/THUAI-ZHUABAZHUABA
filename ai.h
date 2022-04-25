/* FC19 2022 ai.h
*
*/

#ifndef _FC19_AI_H_
#define _FC19_AI_H_
#include "Interface.h"

#ifdef _MSC_VER
extern "C" _declspec(dllexport) void  player_ai(IPlayer * Player);
#endif

#ifdef __GNUC__
extern "C" void player_ai(IPlayer * _Player);
#endif


#endif