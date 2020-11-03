#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int H = 17, W = 150;
float offsetX = 0, offsetY = 0;

using namespace sf;

String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0",
"0                                                                                    w                                                   w           0",
"0                   w                                  w                   w                                                                         0",
"0                                      w                                       kk                         w                                          0",
"0                                                                             k  k    k    k                                                         0",
"0                      c                                                      k      kkk  kkk  w                                                     0",
"0                                                                       r     k       k    k                                                         0",
"0                                                                      rr     k  k                                             U                     0",
"0                                                                     rrr      kk                                                                    0",
"0               c    kckck                                           rrrr0                     0                                                     0",
"0                                      t0                           rrrrr                                                                            0",
"0G                                     00              t0          rrrrrr            G                                                       t0      0",
"0           d    g       d             00              00         rrrrrrr                                        d     g                     00      0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
}; 