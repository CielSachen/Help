/*
 * CCPROG2 MP3 header file (.h source code)
 *
 *    Do not forget to encode your name, section and date of submission.
 *
 *    LASTNAME1, FIRSTNAME1:              SECTION1:
 *    LASTNAME1, FIRSTNAME1:              SECTION1:
 *
 *    DATE SUBMITTED:
 *
 * Rename this file using your last names in alphabetical order, for example CRUZ_TAN.h
 *
 * Make sure to include your header file in your C source code for MP Part 2.
 */

/*
 * Encode below this comment the following:
 *
 * 1. #define directives
 * 2. typedef alias(es) for your string(s)
 * 3. declaration of your user-defined struct data type(s)
 * 4. typedef alias(es) for your struct data type(s)
 *
 * You may have as many typedef as you deem necessary.
 *
 * This header should NOT include the codes for any function definitions.  Function definitions
 * should be encoded in your C source file only.
 */

/* You have to put an inline comment for each struct member as part of the documentation. */

/** @brief The maximum length of a territory’s name. */
#define MAXIMUM_TERRITORY_NAME_LENGTH 33
/** @brief The number of territories in the dataset. */
#define DATASET_TERRITORIES_LENGTH 203

/** @brief An alias for an array of characters long enough to contain a territory name. */
typedef char String[33];

/** @brief The entry of a territory in the dataset. */
typedef struct Territory {
    /** @brief The name of the territory. */
    String name;
    /** @brief The base life expectancy in years. */
    double base_life_expectancy;
    /** @brief The years of life lost from air pollution. */
    double air_pollution_yll;
    /** @brief The years of life lost from ambient particular matter pollution. */
    double ambient_particulate_matter_pollution_yll;
    /** @brief The years of life lost from ambient ozone pollution. */
    double ambient_ozone_pollution_yll;
    /** @brief The years of life lost from household air pollution. */
    double household_air_pollution_yll;
    /** @brief The years of life lost from environmental hazards. */
    double environmental_hazards_yll;
    /** @brief The years of life lost from occupational hazards. */
    double occupational_hazards_yll;
    /** @brief The years of life lost from unsafe water, sanitation, and health. */
    double unsafe_wash_yll;
    /** @brief The years of life lost from metabolic syndrome. */
    double metabolic_syndrome_yll;
    /** @brief The years of life lost from starvation. */
    double starvation_yll;
    /** @brief The years of life lost from diabetes. */
    double diabetes_yll;
    /** @brief The years of life lost from tobacco. */
    double tobacco_yll;
    /** @brief The years of life lost from smoking. */
    double smoking_yll;
    /** @brief The years of life lost from second hand smoking. */
    double second_hand_smoking_yll;
    /** @brief The years of life lost from unsafe sex */
    double unsafe_sex_yll;
} Territory;
