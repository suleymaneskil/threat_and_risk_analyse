/**
 * @file tara_cfg.htmlinclude 
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef TARA_CFG_H
#define TARA_CFG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*****************************************************
 * Enums
 * **************************************************/
/**
 * @brief impact_levels
 * 
 */
typedef enum impact_level_e 
{
    NEGLIGIBLE,
    MODERATE,
    MAJOR,
    SEVERE
    
}impact_level_t;

/**
 * @brief Road User Impact Level
 * 
 */
typedef enum ru_impact_class_e
{
    FINANCIAL,
    OPERATIONAL,
    SAFETY,
    PRIVACY
}ru_impact_class_t;

/**
 * @brief OEM Impact Level
 * Financial Impact:
    F3 → Severe → breakdown of production; substantial worldwide recall or loss of business > 10m EUR
    F2 → Major → disruption of production; limited recall, financial loss of business <= 10m EUR
    F1 → Moderate → financial loss to business <= 100k EUR
    F0 → Neglible → financial loss to business <= 1k EUR
 * Operational Impact:
    O3 → Severe → Many operational vehicles affect from threats.
 * 
 */
typedef enum oem_impact_class_e
{  
    FINANCIAL,
    OPERATIONAL
}oem_impact_class_t;



/**
 * @brief Attack Feasibility for Elapsed Time(EA)
 * How much time does attacker process for the attack?
 *  T0 — Less than one day — 0
    T1 — Between one day and one week — 1
    T2 — Between one week and two weeks — 2
    T3 — Between two weeks and one month — 4
    T4 — Between one month and two months — 7
    T5 — Between two and three months — 10
    T6 — Between three and four months — 13
    T7 — Between four and five months — 15
    T8 — Between five and six months — 17
    T9 — More than six months — 19
 */
typedef enum  elapsed_time_e
{
    T0 = 0U, 
    T1 = 1U, 
    T2 = 2U,
    T3 = 4U, 
    T4 = 7U, 
    T5 = 10U, 
    T6 = 13U, 
    T7 = 15U, 
    T8 = 17U, 
    T9 = 19U
}elapsed_time_t;

/**
 * @brief Attack Feasibility for ## Specialist Expertise (SE)
 * What kind of expertise level does it need to attack?
 *  Level  — Factor — Value
    Ex0 — Layman — 0
    Ex1 — Proficient — 3 
    Ex2 — Expert — 6
    Ex3 — Multiple Experts — 8
 */
typedef enum  specialist_expertise_e
{
    Ex0 = 0U,
    Ex1 = 3U, 
    Ex2 = 6U, 
    Ex3 = 8U
}specialist_expertise_t;

/**
 * @brief Attack Feasibility for Knowledge of Item (KI)
 * What should attacker know about the item? 
 *  Level  — Factor — Value
    K0 — Public Information — 0
    K1 — Restricted Information — 3 
    K2 — Sensitive Information — 7
    K3 — Critical Information — 11
 */
typedef enum  knowledge_of_item_e
{
    K0 = 0U, 
    K1 = 3U, 
    K2 = 7U, 
    K3 = 11U
}knowledge_of_item_t;

/**
 * @brief Attack Feasibility for Window of Opportunity (WO)
 * Attack path or opportunity like physical connection
 * Level  — Factor — Value
    W0 — Unnecessary / Unlimited Access — 0
    W1 — Easy — 1 
    W2 — Moderate — 4
    W3 — Difficult — 10
 * 
 */
typedef enum  window_opportuntiy_e
{
    W0 = 0U, 
    W1 = 1U, 
    W2 = 4U, 
    W3 = 10U

}window_opportuntiy_t;

/**
 * @brief Attack Feasibility for IT hardware/software or other equipment (EQ)
 * What kind of tool does attacker need to attack?
 * Level  — Factor — Value
    Eq0 — Standard — 0
    Eq1 — Specialized — 4 
    Eq2 — Bespoke — 7
    Eq3 — Multiple Bespoke— 9
 * 
 */
typedef enum  it_equipment_e
{
    Eq0 = 0U, 
    Eq1 = 4U, 
    Eq2 = 7U, 
    Eq3 = 9U
}it_equipment_t;

/**
 * @brief RiskTreatmentDecision
 * 
 */
typedef enum risk_treatment_decision_e {
    REDUCE,
    AVOID,
    TRANSFER,
    ACCEPT
}risk_treatment_decision_t;

/**
 * @brief SecurityController
 * 
 */
typedef enum security_controller_e {
    AUTHENTICATION,
    SECURE_FLASHING,
    SECURE_DIAGNOSTIC,
    IVD,
    SECOC
}security_controller_t;

/*****************************************************
 * Structure
 * **************************************************/
typedef struct asset_s {
    const char *name;
}asset_t;

typedef struct attack_scenario_s
{
    const char* d_id;
    const char* description;
    
}attack_scenario_t;

typedef struct damage_scenario_s
{
    const char* d_id;
    const char* description;
    
}damage_scenario_t;


typedef struct ru_impact_s
{
    ru_impact_class_t ru_impact_class;
    impact_level_t ru_impact;

}ru_impact_t;

typedef struct oem_impact_s
{
    oem_impact_class_t oem_impact_class;
    impact_level_t oem_impact;
    
}oem_impact_t;

typedef struct impact_rating_s 
{
    damage_scenario_t damage_scenario;
    ru_impact_t    ru_impact[4];
    oem_impact_t oem_impact[2];

}impact_rating_t;

typedef struct attack_feasibility_s 
{
    attack_scenario_t       attack_scenario;
    elapsed_time_t          atk_feas_ea;
    specialist_expertise_t  atk_feas_se;
    knowledge_of_item_t     atk_feas_ki;
    window_opportuntiy_t    atk_feas_wo;
    it_equipment_t          atk_feas_ie;
    
}attack_feasibility_t;


typedef struct risk_assessment_s 
{
    impact_rating_t impact;
    attack_feasibility_t attack;
    double riskValue;
    risk_treatment_decision_t decision;
    
}risk_assessment_t;

typedef struct cybersecurity_goal_s 
{
    security_controller_t *control;
    risk_assessment_t *risk_assessment;

}cybersecurity_goal_t;

typedef struct cybersecurity_claim_s {
    risk_assessment_t *risk_assessment;

}cybersecurity_claim_t;

typedef struct tara_cfg_s
{
    cybersecurity_claim_t claim;
    cybersecurity_goal_t goal;
}tara_cfg_t;


/*****************************************************
 * Enums
 * **************************************************/

#endif