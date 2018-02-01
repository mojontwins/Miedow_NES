        
                                                 // Level I,            Level 0,            Level 1             Level 2             Level 3             Level 4             Level 5             Level 6,            Level 7,            Level 8,            Level 9,            Level 10.   
const unsigned char * const l_ts_pals [] =        { ts2_pals,           ts1_pals,           ts3_pals,           ts4_pals,           ts1_pals,           ts3_pals,           ts0_pals,           ts1_pals,           ts4_pals,           ts0_pals,           ts3_pals,           ts5_pals            };
const unsigned char * const l_ts_tmaps [] =       { ts2_tmaps,          ts1_tmaps,          ts3_tmaps,          ts4_tmaps,          ts1_tmaps,          ts3_tmaps,          ts0_tmaps,          ts1_tmaps,          ts4_tmaps,          ts0_tmaps,          ts3_tmaps,          ts5_tmaps,          };
const unsigned char l_fpbs [] =                   { 0,                  0,                  1,                  26,                 0,                  1,                  0,                  0,                  26,                 0,                  1,                  0,                  };

const unsigned char * const l_behs [] =           { behs2,              behs1,              behs3,              behs4,              behs1,              behs3,              behs0,              behs1,              behs4,              behs0,              behs3,              behs5,              };
const unsigned char * const l_tp_defs [] =        { 0,                  tp_defs1,           tp_defs3,           tp_defs4,           tp_defs1,           tp_defs3,           0,                  tp_defs1,           tp_defs4,           0,                  tp_defs3,           0,                  };

const unsigned char l_chr_rom [] =                { MAP_03_CHRROM,      MAP_01_CHRROM,      MAP_02_CHRROM,      MAP_04_CHRROM,      MAP_01_CHRROM,      MAP_02_CHRROM,      MAP_00_CHRROM,      MAP_01_CHRROM,      MAP_04_CHRROM,      MAP_00_CHRROM,      MAP_02_CHRROM,      MAP_05_CHRROM       };
const unsigned int * const l_map [] =             { map_03_scr_offsets, map_01_scr_offsets, map_02_scr_offsets, map_04_scr_offsets, map_01_scr_offsets, map_02_scr_offsets, map_00_scr_offsets, map_01_scr_offsets, map_04_scr_offsets, map_00_scr_offsets, map_02_scr_offsets, map_05_scr_offsets  };
const unsigned char * const l_locks [] =          { 0,                  map_01_locks,       map_02_locks,       map_04_locks,       map_01_locks,       map_02_locks,       map_00_locks,       map_01_locks,       map_04_locks,       map_00_locks,       map_02_locks,       0                   };

const unsigned char l_scr_ini [] =                { 0,                  21,                 10,                 0,                  22,                 20,                 12,                 0,                  18,                 12,                 5,                  20,                 };
const unsigned char player_ini_x [] =             { 3,                  8,                  3,                  3,                  8,                  2,                  6,                  2,                  8,                  3,                  2,                  7,                  };
const unsigned char player_ini_y [] =             { 8,                  9,                  6,                  4,                  9,                  4,                  8,                  3,                  7,                  4,                  5,                  10,                 };

const unsigned char * const * const l_enems [] =  { enems_i,            enems_1,            enems_2,            enems_3,            enems_1,            enems_2,            enems_0,            enems_1,            enems_3,            enems_0,            enems_2,            enems_4             };
const unsigned char * const l_hotspots [] =       { hotspots_i,         hotspots_1,         hotspots_2,         hotspots_3,         hotspots_1,         hotspots_2,         hotspots_0,         hotspots_1,         hotspots_3,         hotspots_0,         hotspots_2,         hotspots_4          };
const unsigned char l_max_bolts [] =              { 0,                  20,                 5,                  20,                 20,                 5,                  3,                  20,                 20,                 3,                  3,                  1,                  };
const unsigned char l_max_hotspots_type_1 [] =    { 0,                  1,                  1,                  1,                  2,                  2,                  5,                  1,                  3,                  5,                  1,                  1,                  };

// 1 = lightning, 2 = rain, 4 = make rain variable
const unsigned char l_custom_on_off [] =          { 0,                  6,                  1,                  7,                  2,                  7,                  3,                  3,                  2,                  3,                  2,                  0,                  };

const unsigned char * const l_pal_ts [] =         { palts0,             palts0,             palts0,             palts2,             palts1,             palts1,             palts0,             palts1,             palts1,             palts1,             palts2,             palts0              };
const unsigned char l_music [] =                  { MUSIC_BASE,         MUSIC_0,            MUSIC_1,            MUSIC_2,            MUSIC_0,            MUSIC_1,            MUSIC_3,            MUSIC_0,            MUSIC_2,            MUSIC_3,            MUSIC_1,            MUSIC_4             };

const unsigned char l_facing [] =                 { CELL_FACING_DOWN,   CELL_FACING_UP,     CELL_FACING_RIGHT,  CELL_FACING_DOWN,   CELL_FACING_UP,     CELL_FACING_RIGHT,  CELL_FACING_DOWN,   CELL_FACING_RIGHT,  CELL_FACING_DOWN,   CELL_FACING_DOWN,   CELL_FACING_RIGHT,  CELL_FACING_UP      };
