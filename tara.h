/**
 * @file tara.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef TARA_H
#define TARA_H

#ifndef TARA_CFG_H
#include "tara_cfg.h"
#endif

/**
 * @brief 
 * 
 */
typedef enum atk_feas_class_e
{
    VERY_LOW,
    LOW,
    MEDIUM,
    HIGH,
    VERY_HIGH

}atk_feas_class_t;

typedef enum risk_value_e
{
    R_VERY_LOW,
    R_LOW,
    R_MODERATE,
    R_HIGH,
    R_VERY_HIGH

}risk_value_t;

//void tara_main(tara_cfg_t *tara_cfg);

//void create_asset(asset_t* asset);

void create_system(tara_cfg_t *system);
void create_function(ecu_t *ecu);
void create_data(function_t *function);
void create_damage_scenario(data_t *data);

void print_assets(tara_cfg_t *system);
void clear_newline(char *str);
bool get_positive_integer(size_t *num);


risk_value_t calc_risk_value(atk_feas_class_t attackFeasibleClass, impact_level_t impact);


#endif