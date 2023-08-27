
#ifndef TARA_CFG_H
#include "tara_cfg.h"
#endif







asset_t ecu = {"ECU"};
asset_t communicationPath = {"Communication Path"};
asset_t dataPath = {"Data Path"};



risk_treatment_decision_t makeRiskTreatmentDecision(double riskValue) {
    if (riskValue <= 10) {
        return REDUCE;
    } else if (riskValue <= 20) {
        return AVOID;
    } else if (riskValue <= 30) {
        return TRANSFER;
    } else {
        return ACCEPT;
    }
}

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
}

int main() {// TODO
    struct damage_scenario_t ecuTampering = {
        "ECU Tampering",
        {
            {SEVERE, MAJOR, MODERATE, NEGLIGIBLE},
            {SEVERE, MAJOR, MODERATE, NEGLIGIBLE},
            {SEVERE, MAJOR, MODERATE, NEGLIGIBLE},
            {SEVERE, MAJOR, MODERATE, NEGLIGIBLE}
        },
        {
            {SEVERE, MAJOR, MODERATE, NEGLIGIBLE},
            {SEVERE, MAJOR, MODERATE, NEGLIGIBLE},
            {SEVERE, MAJOR, MODERATE, NEGLIGIBLE},
            {SEVERE, MAJOR, MODERATE, NEGLIGIBLE}
        }
    };
    
    attack_scenario_t physicalAccess = {
        "Physical Access",
        {T0, Ex0, K0, W0, Eq0} // Örnek değerler
    };
    
    double feasibilitySum = calculateAttackFeasibility(physicalAccess);
    int attackFeasibleClass = calculateAttackFeasibleClass(feasibilitySum);
    double riskValue = calculateRiskValue(feasibilitySum, attackFeasibleClass);
    risk_treatment_decision_t decision =
