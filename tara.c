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
static atk_feas_class_t calc_attack_feasible_class(uint8_t feasibility_sum) ;

static impact_level_t calc_impact_level(impact_rating_t* impact);

static uint8_t is_risk_threatment_desicion(risk_value_t risk_val);

static uint8_t is_cs_goals(cybersecurity_goal_t* goal_cfg, risk_assessment_t* risk_in);


static uint8_t is_cs_claims(cybersecurity_claim_t* claim_cfg, risk_assessment_t* risk_in);

uint8_t risk_table[4][4] =
        {
            {R_VERY_LOW, R_VERY_LOW, R_LOW, R_LOW},
            {R_VERY_LOW, R_LOW, R_MODERATE, R_MODERATE},
            {R_LOW, R_MODERATE, R_MODERATE, R_HIGH},
            {R_LOW, R_MODERATE, R_HIGH, R_VERY_HIGH},

        };
/*
void tara_main(tara_cfg_t *tara_cfg)
{
    // TODO
}*/

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

// risk_table
risk_value_t calc_risk_value(atk_feas_class_t attackFeasibleClass, impact_level_t impact) 
{ 
    risk_value_t riskValue = risk_table[impact][attackFeasibleClass];
    return riskValue;
}


static uint8_t is_risk_threatment_desicion(risk_value_t risk_val)
{
    uint8_t desicion = 0U;

    if((risk_val =! R_VERY_LOW) && (risk_val =! R_LOW))
    {
        desicion = 1U;
    }
    else
    {
        desicion = 0U;
    }

    return desicion;
}


static uint8_t is_cs_goals(cybersecurity_goal_t* goal_cfg, risk_assessment_t* risk_in)
{
    uint8_t result = 0U;
    if((risk_in->decision == REDUCE) || (risk_in->decision == AVOID))
    {
        goal_cfg->risk_assessment = risk_in;
        result = 1U;
    }
    else
    {
        result = 0U;
    }

    return result;
}

static uint8_t is_cs_claims(cybersecurity_claim_t* claim_cfg, risk_assessment_t* risk_in)
{
    uint8_t result = 0U;
    if((risk_in->decision == ACCEPT) || (risk_in->decision == TRANSFER))
    {
        claim_cfg->risk_assessment = risk_in;
        result = 1U;
    }
    else
    {
        result = 0U;
    }

    return result;
}
/*
static void save_damage_scenario(FILE *file, damage_scenario_t *scenario) {
    fprintf(file, "%s\n%s\n", scenario->d_id, scenario->description);
}

static void save_data(FILE *file, asset_t *data) {
    fprintf(file, "%s\n%zu\n", data->name, data->num_damage_scenarios);
    for (size_t i = 0; i < data->num_damage_scenarios; ++i) {
        save_damage_scenario(file, &data->damage_scenarios[i]);
    }
}

static void save_function(FILE *file, asset_t *function) {
    fprintf(file, "%s\n%zu\n", function->name, function->num_sub_assets);
    for (size_t i = 0; i < function->num_sub_assets; ++i) {
        save_data(file, &function->sub_assets[i]);
    }
}

static void save_ecu(FILE *file, asset_t *ecu) {
    fprintf(file, "%s\n%zu\n", ecu->name, ecu->num_sub_assets);
    for (size_t i = 0; i < ecu->num_sub_assets; ++i) {
        save_function(file, &ecu->sub_assets[i]);
    }
}

static void save_system(asset_t *system) 
{
    FILE *file = fopen("TARA.txt", "w");
    if (file == NULL) {
        printf("File open error.\n");
        exit(1);
    }

    fprintf(file, "%zu\n", system->num_sub_assets);
    for (size_t i = 0; i < system->num_sub_assets; ++i) {
        save_ecu(file, &system->sub_assets[i]);
    }
    fclose(file);
}*/


void clear_newline(char *str) 
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0'; // Remove newline character
    }
}

bool get_positive_integer(size_t *num) 
{
    int result = scanf("%zu", num);
    while (getchar() != '\n'); // Clear input buffer
    return (bool)((result == 1) && (*num > 0));
}

void create_system(tara_cfg_t *system) 
{
    printf("Enter the number of ECUs in the system: ");
    size_t num_ecus;
    while (!get_positive_integer(&num_ecus)) 
    {
        printf("Please enter a valid positive number: ");
    }

    system->num_ecu = num_ecus;
    system->ecu = (ecu_t *)malloc(num_ecus * sizeof(ecu_t));
    if (system->ecu == NULL) 
    {
        printf("Memory allocation error.\n");
        exit(1);
    }

    for (size_t i = 0; i < num_ecus; ++i) {
        printf("Enter the name of ECU %zu: ", i + 1);
        fgets(system->ecu[i].ecu_info.name, sizeof(system->ecu[i].ecu_info.name), stdin);
        clear_newline(system->ecu[i].ecu_info.name);

        if (strlen(system->ecu[i].ecu_info.name) >= sizeof(system->ecu[i].ecu_info.name)) 
        {
            printf("ECU name is too long.\n");
            exit(1);
        }

        create_function(&system->ecu[i]);
    }
    //save_system(system);
}

void create_function(ecu_t* ecu) 
{
    printf("Enter the number of functions for %s: ", ecu->ecu_info.name);
    size_t num_functions;
    while (!get_positive_integer(&num_functions)) {
        printf("Please enter a valid positive number: ");
    }

    ecu->num_function = num_functions;
    ecu->function = (function_t *)malloc(num_functions * sizeof(function_t));
    if (ecu->function == NULL) 
    {
        printf("Memory allocation error.\n");
        exit(1);
    }

    for (size_t i = 0; i < ecu->num_function; ++i) 
    {
        printf("Enter the name of function %zu for %s: ", i + 1, ecu->ecu_info.name);
        fgets(ecu->function[i].function_info.name, sizeof(ecu->function[i].function_info.name), stdin);
        clear_newline(ecu->function[i].function_info.name);

        if (strlen(ecu->function[i].function_info.name) >= sizeof(ecu->function[i].function_info.name)) 
        {
            printf("Function name is too long.\n");
            exit(1);
        }

        create_data(&ecu->function[i]);
    }
}

void create_data(function_t *function) 
{
    printf("Enter the number of data for %s: ", function->function_info.name);
    size_t num_data;
    while (!get_positive_integer(&num_data)) {
        printf("Please enter a valid positive number: ");
    }

    function->num_data = num_data;
    function->data = (data_t *)malloc(num_data * sizeof(data_t));
    
    if (function->data == NULL) 
    {
        printf("Memory allocation error.\n");
        exit(1);
    }

    for (size_t i = 0; i < num_data; ++i) 
    {
        printf("Enter the name of data %zu for %s: ", i + 1, function->function_info.name);
        fgets(function->data[i].data_info.name, sizeof(function->data[i].data_info.name), stdin);
        clear_newline(function->data[i].data_info.name);

        if (strlen(function->data[i].data_info.name) >= sizeof(function->data[i].data_info.name)) 
        {
            printf("Data name is too long.\n");
            exit(1);
        }

        create_damage_scenario(&function->data[i]);
    }
}

void create_damage_scenario(data_t *data) 
{
    static size_t id_counter = 1;

    printf("Enter the number of damage scenario for %s: ", data->data_info.name);
    size_t num_damage;
    while (!get_positive_integer(&num_damage)) 
    {
        printf("Please enter a valid positive number: ");
    }

    data->damage_scenario.num_damage_scenario_info = num_damage;
    data->damage_scenario.damage_scenario_info = 
        (damage_scenario_info_t *)malloc(num_damage * sizeof(damage_scenario_info_t));
    
    if (data->damage_scenario.damage_scenario_info == NULL) 
    {
        printf("Memory allocation error.\n");
        exit(1);
    }

    for (size_t i = 0; i < num_damage; ++i) 
    {
        snprintf(data->damage_scenario.damage_scenario_info[i].d_id, 
            sizeof(data->damage_scenario.damage_scenario_info[i].d_id), 
            "DS.%zu", id_counter++);
        printf("Enter the description for damage scenario %s for %s: ", 
            data->damage_scenario.damage_scenario_info->d_id, 
            data->data_info.name);
        fgets(data->damage_scenario.damage_scenario_info[i].description, 
            sizeof(data->damage_scenario.damage_scenario_info[i].description), stdin);
        clear_newline(data->damage_scenario.damage_scenario_info[i].description);

        if (strlen(data->damage_scenario.damage_scenario_info[i].description) >= 
            sizeof(data->damage_scenario.damage_scenario_info[i].description)) 
        {
            printf("Data name is too long.\n");
            exit(1);
        }
    }
}

void print_assets(tara_cfg_t *system) 
{
    
    printf("System Tree:\n");
    if(system->num_ecu == 0U)
    {
        printf("There isn't any asset of the system");
        printf("\n");
    }
    else
    {
    for (size_t i = 0; i < system->num_ecu; ++i) 
    {
        if(system->ecu[i].num_function == 0U)
        {
            printf("%s -> ", system->ecu[i].ecu_info.name);
            printf("\n");
        } 
        else
        {
        for(size_t k=0; k<system->ecu[i].num_function;k++)
        {
            if(system->ecu[i].function[k].num_data == 0U)
            {
                printf("%s -> ", system->ecu[i].ecu_info.name);
                printf("%s -> ", system->ecu[i].function[k].function_info.name);
                printf("\n");
            }
            else
            {
            for(size_t l=0; l<system->ecu[i].function[k].num_data;l++)
            {
                if(system->ecu[i].function[k].data[l].damage_scenario.
                    num_damage_scenario_info == 0U)
                {
                    printf("%s -> ", system->ecu[i].ecu_info.name);
                    printf("%s -> ", system->ecu[i].function[k].function_info.name);
                    printf("%s -> ", system->ecu[i].function[k].data[l].data_info.name);
                    printf("\n");
                }
                else
                {
                for(size_t m=0; m<system->ecu[i].function[k].data[l].damage_scenario.
                    num_damage_scenario_info;m++)
                {
                    printf("%s -> ", system->ecu[i].ecu_info.name);
                    printf("%s -> ", system->ecu[i].function[k].function_info.name);
                    printf("%s -> ", system->ecu[i].function[k].data[l].data_info.name);
                    printf("%s.", system->ecu[i].function[k].data[l].damage_scenario.
                            damage_scenario_info[m].d_id);
                    printf("%s", system->ecu[i].function[k].data[l].damage_scenario.
                            damage_scenario_info[m].description);
                    printf("\n");
                }} 
            }} 
        }}
    }}
    
}


/*static void print_assets_to_file_recursive(FILE *file, asset_t *asset, int depth) {
    for (int i = 0; i < depth; ++i) {
        fprintf(file, "  ");
    }
    fprintf(file, "- %s\n", asset->name);

    for (size_t i = 0; i < asset->num_sub_assets; ++i) {
        print_assets_to_file_recursive(file, &asset->sub_assets[i], depth + 1);
    }
}

void print_assets_to_file(asset_t *asset) {
    char filename[MAX_PATH]; // Dizin boyutunu artırdık
    char exe_path[MAX_PATH];  // Max path length
    FILE *file;

    DWORD result = GetModuleFileNameA(NULL, exe_path, sizeof(exe_path));
    if (result == 0) {
        perror("GetModuleFileNameA");
        exit(1);
    }

    // Find the last directory separator
    char *last_separator = strrchr(exe_path, '\\');
    if (last_separator) {
        *last_separator = '\0';
    }

    snprintf(filename, sizeof(filename), "%s\\%s", exe_path, "sistem_definition.txt");

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }

    fprintf(file, "Asset hierarchy:\n");
    print_assets_to_file_recursive(file, asset, 0);

    fclose(file);

    printf("Ağaç yapısı '%s' dosyasına kaydedildi.\n", filename);
}*/