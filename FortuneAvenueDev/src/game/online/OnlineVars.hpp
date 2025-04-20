#pragma once
#include <unordered_map>
#include <map>
#include <cstdint>  // Para uint32_t y uint8_t
#include <vector>   // Para std::vector

extern int playerIndex;
extern int turnopermitido;
extern bool accionCompra;
extern bool accionXhouse;
extern bool juegoTerminado;
//extern int conteoturn;
extern float initialSpeedActi;
extern float decelerationRateActi;
extern bool giroActivo;
extern std::map<uint32_t, std::vector<uint8_t>> MYplayerImageFragments;