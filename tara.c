#include "tara.h"

/**
 * @brief calc_attack_feasibility
 * 
 * @param attack 
 * @return uint8_t 
 */
static uint8_t calc_attack_feasibility(attack_feasibility_t* attack);

/**
 * @brief calculate_attack_feasible_class
 * 
 * @param feasibility_sum 
 * @return atk_feas_class_t 
 */
static atk_feas_class_t calculate_attack_feasible_class(uint8_t feasibility_sum) ;

static impact_level_t calc_impact_level(impact_rating_t* impact);


void tara_main(tara_cfg_t *tara_cfg)
{
    // TODO
}

/**
 * @brief calc_attack_feasibility
 * 
 * @param attack 
 * @return uint8_t 
 */
static uint8_t calc_attack_feasibility(attack_feasibility_t* attack) 
{
    uint8_t sum = 0;
    sum += (uint8_t)attack->atk_feas_ea;
    sum += (uint8_t)attack->atk_feas_ie;
    sum += (uint8_t)attack->atk_feas_ki;
    sum += (uint8_t)attack->atk_feas_se;
    sum += (uint8_t)attack->atk_feas_wo;

    return sum;
}

/**
 * @brief calculate_attack_feasible_class
 * 
 * @param feasibility_sum 
 * @return atk_feas_class_t 
 */
static atk_feas_class_t calc_attack_feasible_class(uint8_t feasibility_sum) 
{
    atk_feas_class_t ret_val;

    if (feasibility_sum >= 24U) 
    {  
        ret_val = VERY_LOW;
    } 
    else if (feasibility_sum >= 20 && feasibility_sum < 24) 
    {
        ret_val = LOW;
    } 
    else if (feasibility_sum >= 14 && feasibility_sum < 20) 
    {
        ret_val = MEDIUM;
    } 
    else if (feasibility_sum >= 10 && feasibility_sum < 14) 
    {
        ret_val = HIGH;
    } 
    else if (feasibility_sum < 10) 
    {
        ret_val = VERY_HIGH;
    } 
    else 
    {
        ret_val = VERY_LOW;
    }

    return ret_val;
}

/**
 * @brief cal_impact_level
 * 
 * @param impact 
 * @return impact_level_t 
 */
static impact_level_t calc_impact_level(impact_rating_t* impact)
{
    impact_level_t ret_val = NEGLIGIBLE;
    for(int coun=0; coun < 0x4 ; coun++)
    {
        if(impact->ru_impact[coun].ru_impact == SEVERE)
        {
            ret_val = SEVERE;
            return ret_val;
        }
        else if(impact->ru_impact[coun].ru_impact < NEGLIGIBLE)
        {
            ret_val = impact->ru_impact[coun].ru_impact;
        }
    } 

    for(int coun=0; coun < 0x2; coun++)
    {
        if(impact->oem_impact[coun].oem_impact == SEVERE)
        {
            ret_val = SEVERE;
            return ret_val;
        }
        else if(impact->oem_impact[coun].oem_impact < NEGLIGIBLE)
        {
            ret_val = impact->oem_impact[coun].oem_impact;
        }
    }

    return ret_val;
}


double calc_risk_value(atk_feas_class_t feasibilitySum, impact_rating_t attackFeasibleClass) 
{
    double riskValue = feasibilitySum * attackFeasibleClass;
    return riskValue;
}