//#ifndef TARA_H
#include "tara.h"
//#endif


/*

asset_t ecu = {"ECU"};
asset_t communicationPath = {"Communication Path"};
asset_t dataPath = {"Data Path"};


security_controller_t *createCybersecurityControl(risk_treatment_decision_t decision, security_controller_t controller) {
    security_controller_t *control = malloc(sizeof(security_controller_t));
    control->controller = controller;
    control->decision = decision;
    return control;
}

risk_assessment_t *createRiskAssessment(damage_scenario_t damage, attack_scenario_t attack, double riskValue, risk_treatment_decision_t decision, security_controller_t *control) {
    risk_assessment_t *assessment = malloc(sizeof(risk_assessment_t));
    assessment->damage = damage;
    assessment->attack = attack;
    assessment->riskValue = riskValue;
    assessment->decision = decision;
    assessment->control = control;
    return assessment;
}

struct CybersecurityGoal *createCybersecurityGoal(security_controller_t *control, risk_assessment_t *assessment) {
    struct CybersecurityGoal *goal = malloc(sizeof(struct CybersecurityGoal));
    goal->control = control;
    goal->riskAssessment = assessment;
    return goal;
}

void printRiskAssessment(risk_assessment_t *assessment) {
    printf("Risk Assessment:\n");
    // ... Gerekli bilgilerin yazdırılması
}

void printCybersecurityGoal(struct CybersecurityGoal *goal) {
    printf("Cybersecurity Goal:\n");
    printf("Security Controller: %d\n", goal->control->controller);
    printf("Risk Assessment Address: %p\n", goal->riskAssessment);
}*/


int main() 
{
    tara_cfg_t tara_system;

    printf("Test here\n");

    create_system(&tara_system);

    printf("The tara_system assets are saved!!\n\n\n\n");
    
    print_assets(&tara_system);
    //print_assets_to_file(&tara_system);

    for (size_t i = 0; i < tara_system.num_ecu; ++i) {
        for (size_t j = 0; j < tara_system.ecu[i].num_function; ++j) 
        {
            for (size_t k = 0; k < tara_system.ecu[i].function[j].num_data; ++k) 
            {
                free(tara_system.ecu[i].function[j].data[k].
                    damage_scenario.damage_scenario_info);
            }
            free(tara_system.ecu[i].function[j].data);
        }
        free(tara_system.ecu[i].function);
    }
    free(tara_system.ecu);

    return 0;
}
