/*
 * CCPROG2 MP3 SOURCE CODE
 *
 *    Do not forget to encode your name, section and date of submission.
 *
 *    LASTNAME1, FIRSTNAME1:              SECTION1:
 *    LASTNAME1, FIRSTNAME1:              SECTION1:
 *
 *    DATE SUBMITTED:
 *
 * Rename this file using your last names in alphabetical order, for example CRUZ_TAN.c
 *
 * Make sure to compile your C source code with a -Wall directive.
 *    Example: CCPROG2> gcc -Wall LASTNAME1_LASTNAME2.c
 *
 * Fix all warnings.  Do NOT run the program if you still have a warning.  You must have
 * 0 error, 0 warning before running the program.
 *
 * DO NOT run your a.exe with input/output redirection anymore because MP3 is
 * already supposed to be on text file processing.
 *
 * You should run your a.exe file simply as follows:
 *    Example: a
 */

#include <stdio.h>
#include <string.h>

// include your own header file
#include "LASTNAME1_LASTNAME2.h"

/* Do NOT include other header files. */

/*
 * HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
 *
 * 1. You must apply struct data type, and text file processing MP Part 3 (MP3).
 *      a. Re-use the contents of your header file LASTNAME1_LASTNAME2.h.
 *      b. Follow the same hard requirements in MP2 on struct data type, and structure access using
 *         * and ., and -> operators.
 * 2. Data should be read from SoGA_DATASET.txt using fscanf().
 * 3. The main() function should call the appropriate C function, and then call fprintf() to
 *    write the answer to each question onto the OUTPUT_LASTNAME1_LASTNAME2.txt file. Numeric
 *    answers with double data type must be written with 6 digits after the decimal point.
 * 4. There should NOT be any printf() and scanf() statement in the entire source code,
 *    not even in main(), and in the function that reads the SoGA data text file.
 * 5. Document your codes with SENSIBLE comments.
 * 6. Use double data type (not float) for all floating point values/variables/functions/return
 * type.
 * 7. Do NOT use any global variables.
 * 8. Do NOT use library functions that were NOT discussed in our class.
 */

/*
 * ALL typedef declarations must be encoded in your header file.
 * All #define must be encoded in your header file.
 * Do NOT place them in this file.
 */

/*
 * Define any function that you need below this comment.
 *
 * For functions that serve as answers to the questions, include the following as comments
 * BEFORE the function definition itself:
 *    a. Question number, and the actual question.
 *    b. Thereafter, type the answer number, and the corresponding expected answer.
 *
 * For example:
 *    Q1:  Which country has the lowest baseline life expectancy?
 *    A1:  Lesotho
 *
 * The following should be included as comments and appear BEFORE each function definition:
 *    a. Purpose: describe succinctly what the function is supposed to accomplish.
 *    b. Parameters: describe succinctly the nature/purpose of each parameter.
 *    c. Return type: if the function is not void, describe succinctly what it will return as a
 * result.
 *
 * Document the body of the function by including comments alongside codes that you think
 * may not be easy to understand to the person reading the codes.
 */

/**
 * @brief Loads the territory data from the dataset file into the provided territories array.
 * @param territories The array of the territories.
 */
void load_data(Territory territories[DATASET_TERRITORIES_LENGTH]) {
    int index;
    FILE *dataset_file = fopen("SoGA_DATASET.txt", "r");
    int column_count = 16;
    Territory territory;

    for (index = 0;
         fscanf(dataset_file, " %s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf ",
                territory.name, &territory.base_life_expectancy, &territory.air_pollution_yll,
                &territory.ambient_particulate_matter_pollution_yll,
                &territory.ambient_ozone_pollution_yll, &territory.household_air_pollution_yll,
                &territory.environmental_hazards_yll, &territory.occupational_hazards_yll,
                &territory.unsafe_wash_yll, &territory.metabolic_syndrome_yll,
                &territory.starvation_yll, &territory.diabetes_yll, &territory.tobacco_yll,
                &territory.smoking_yll, &territory.second_hand_smoking_yll,
                &territory.unsafe_sex_yll) == column_count;
         index++) {
        territories[index] = territory;
    }

    fclose(dataset_file);
}

/*
 * Q1:  Which territory has the highest change in life expectancy due to smoking that is not greater
 * than <parameter_number> years?
 * A1:
 *      1.0: Puerto_Rico
 *      -2.0: INVALID INPUT
 *      3.0: Lebanon
 */

/**
 * @brief Solves the first question by looping through the territories, storing the smoking YLL
 * value, and replacing the stored smoking YLL value if another territory has a higher value.
 * @param territories The array of the territories.
 * @param maximum_yyl The <parameter_number> value.
 * @returns `-1` if `maximum_yll` is less than or equal to `0` or the index of the territory in
 * `territories`.
 */
int solve_question_one(Territory territories[DATASET_TERRITORIES_LENGTH], double maximum_yll) {
    int index;
    Territory territory;
    int highest_smoking_yll_index = -1;

    if (maximum_yll <= 0) {
        return -1;
    } else {
        for (index = 0; index < DATASET_TERRITORIES_LENGTH; index++) {
            territory = territories[index];

            if (territory.smoking_yll <= maximum_yll &&
                (highest_smoking_yll_index == -1 ||
                 territory.smoking_yll > territories[highest_smoking_yll_index].smoking_yll)) {
                highest_smoking_yll_index = index;
            }
        }

        return highest_smoking_yll_index;
    }
}

/**
 * @brief Prints the answer to the first question to the passed results file.
 * @note This function runs `solve_question_one()` to get the answer to the question.
 * @param results_file The object of the output text file.
 * @param territories The array of the territories.
 * @param maximum_yyl The <parameter_number> value.
 */
void print_question_one_answer(FILE *results_file,
                               Territory territories[DATASET_TERRITORIES_LENGTH],
                               double maximum_yyl) {
    int territory_index = solve_question_one(territories, maximum_yyl);

    if (territory_index < 0) {
        fprintf(results_file, "Answer (<parameter_number> = %lf): INVALID INPUT\n", maximum_yyl);
    } else {
        fprintf(results_file, "Answer (<parameter_number> = %lf): %s\n", maximum_yyl,
                territories[territory_index].name);
    }
}

/*
 * Q2:  What is the sum of the loss of life expectancy due to metabolic syndrome, dietary factors,
 * and fasting plasma sugar for <parameter_territory_name>?
 * A2:  Taiwan: 6.656377
 *      South_Korea: 5.476058
 *      Japan: 4.182285
 */

/**
 * @brief Solves the second question by looping through the territories until the territory matches
 * the provided name and sums up its metabolic syndrome, starvation (dietary factors), and diabetes
 * (high fasting plasma sugar) YYLs.
 * @param territories The array of the territories.
 * @param territory_name The <parameter_territory_name> value.
 * @returns The value sum of the territory's `metabolic_syndrome_yll`, `starvation_yll`, and
 * `diabetes_yll` or `-1` if invalid.
 */
double solve_question_two(Territory territories[DATASET_TERRITORIES_LENGTH],
                          String territory_name) {
    int index;
    int territory_index = -1;
    Territory territory;

    for (index = 0; index < DATASET_TERRITORIES_LENGTH && territory_index == -1; index++) {
        if (strncmp(territories[index].name, territory_name, MAXIMUM_TERRITORY_NAME_LENGTH) == 0) {
            territory_index = index;
        }
    }

    if (territory_index == -1) {
        return -1;
    } else {
        territory = territories[territory_index];

        return territory.metabolic_syndrome_yll + territory.starvation_yll + territory.diabetes_yll;
    }
}

/**
 * @brief Prints the answer to the second question to the passed results file.
 * @note This function runs `solve_question_two()` to get the answer to the question.
 * @param results_file The object of the output text file.
 * @param territories The array of the territories.
 * @param territory_name The <parameter_territory_name> value.
 */
void print_question_two_answer(FILE *results_file,
                               Territory territories[DATASET_TERRITORIES_LENGTH],
                               char *territory_name) {
    double data_sum = solve_question_two(territories, territory_name);

    if (data_sum == -1) {
        fprintf(results_file, "Answer (<parameter_territory_name> = %s): INVALID INPUT\n",
                territory_name);
    } else {
        fprintf(results_file, "Answer (<parameter_territory_name> = %s): %lf\n", territory_name,
                data_sum);
    }
}

/*
 * Q3:  Does <parameter_territory_name> have a negligible change in life expectancy due to ozone
 * (less than 0.01)?
 * A3:  Taiwan: false
 *      South_Korea: false
 *      Japan: false
 */

/**
 * @brief Solves the third question by looping through the territories until the territory matches
 * the provided name and checking if its ambient ozone pollution YLL is less than `0.01`.
 * @param territories The array of the territories.
 * @param territory_name The <parameter_territory_name> value.
 * @returns `1` if the territory's `ambient_ozone_pollution_yll` value is less than `0.01`, `0` if
 * not, or `-1` if invalid.
 */
int solve_question_three(Territory territories[DATASET_TERRITORIES_LENGTH], String territory_name) {
    int index;
    int territory_index = -1;

    for (index = 0; index < DATASET_TERRITORIES_LENGTH && territory_index == -1; index++) {
        if (strncmp(territories[index].name, territory_name, MAXIMUM_TERRITORY_NAME_LENGTH) == 0) {
            territory_index = index;
        }
    }

    if (territory_index == -1) {
        return -1;
    } else {
        return territories[territory_index].ambient_ozone_pollution_yll < 0.01;
    }
}

/**
 * @brief Prints the answer to the third question to the passed results file.
 * @note This function runs `solve_question_three()` to get the answer to the question.
 * @param results_file The object of the output text file.
 * @param territories The array of the territories.
 * @param territory_name The <parameter_territory_name> value.
 */
void print_question_three_answer(FILE *results_file,
                                 Territory territories[DATASET_TERRITORIES_LENGTH],
                                 char *territory_name) {
    int is_negligible_change = solve_question_three(territories, territory_name);

    if (is_negligible_change == -1) {
        fprintf(results_file, "Answer (<parameter_territory_name> = %s): INVALID INPUT\n",
                territory_name);
    } else if (is_negligible_change) {
        fprintf(results_file, "Answer (<parameter_territory_name> = %s): true\n", territory_name);
    } else {
        fprintf(results_file, "Answer (<parameter_territory_name> = %s): false\n", territory_name);
    }
}

/*
 * Q4:  What is the average change in life expectancy due to air pollution for the top
 * <parameter_number> territories with the highest baseline life expectancy? List the respective
 * territories.
 * A4:  10:
 *          1. Singapore (0.565649)
 *          2. Japan (0.297785)
 *          3. Iceland (0.087976)
 *          4. Switzerland (0.220011)
 *          5. Italy (0.409795)
 *          6. Spain (0.258372)
 *          7. Israel (0.501422)
 *          8. Norway (0.106604)
 *          9. South_Korea (0.691468)
 *          10. Luxembourg (0.244940)
 *      0:  INVALID INPUT
 *      3:
 *          1. Singapore (0.565649)
 *          2. Japan (0.297785)
 *          3. Iceland (0.087976)
 */

/**
 * @brief Solves the fourth question by copying the provided array of territories, sorting the array
 * copy by base life expectancy through [insertion
 * sort](https://en.wikipedia.org/wiki/Insertion_sort) and returning the average air pollution YYL
 * of all the top territories up until the lowest rank.
 * @param territories The array of the territories.
 * @param lowest_rank The <parameter_number> value.
 * @param[out] sorted_territories The sorted array of the territories.
 * @returns The average air pollution YYL of all the top territories up until the lowest rank.
 */
double solve_question_four(Territory territories[DATASET_TERRITORIES_LENGTH], int lowest_rank,
                           Territory sorted_territories[DATASET_TERRITORIES_LENGTH]) {
    int index;
    Territory territory;
    int other_index;
    double total_air_pollution_yll = 0;

    if (lowest_rank == 0) {
        return -1;
    } else {
        for (index = 0; index < DATASET_TERRITORIES_LENGTH; index++) {
            sorted_territories[index] = territories[index];
        }

        for (index = 1; index < DATASET_TERRITORIES_LENGTH; index++) {
            territory = sorted_territories[index];
            other_index = index - 1;

            while (other_index >= 0 && sorted_territories[other_index].base_life_expectancy <
                                           territory.base_life_expectancy) {
                sorted_territories[other_index + 1] = sorted_territories[other_index];
                other_index -= 1;
            }

            sorted_territories[other_index + 1] = territory;
        }

        for (index = 0; index < lowest_rank; index++) {
            total_air_pollution_yll += sorted_territories[index].air_pollution_yll;
        }

        return total_air_pollution_yll / lowest_rank;
    }
}

/**
 * @brief Prints the answer to the fourth question to the passed results file.
 * @note This function runs `solve_question_four()` to get the answer to the question.
 * @param results_file The object of the output text file.
 * @param territories The array of the territories.
 * @param lowest_rank The <parameter_number> value.
 */
void print_question_four_answer(FILE *results_file,
                                Territory territories[DATASET_TERRITORIES_LENGTH],
                                int lowest_rank) {
    Territory sorted_territories[DATASET_TERRITORIES_LENGTH];
    double average_air_pollution_yll =
        solve_question_four(territories, lowest_rank, sorted_territories);
    int rank;

    if (average_air_pollution_yll < 0) {
        fprintf(results_file, "Answer (<parameter_number> = %d): INVALID INPUT\n", lowest_rank);
    } else {
        fprintf(results_file, "Answer (<parameter_number> = %d): %lf\n", lowest_rank,
                average_air_pollution_yll);

        for (rank = 0; rank < lowest_rank; rank++) {
            Territory territory = sorted_territories[rank];

            fprintf(results_file, "    %d. %s (%lf)\n", rank + 1, territory.name,
                    territory.air_pollution_yll);
        }
    }
}

/*
 * Q5:  What is the minimum change in life expectancy due to environmental/occupational hazards that
 * is greater than 3% of the respective territories' baseline life expectancy?
 * A5:  South_Africa (2.175128)
 */

/**
 * @brief Solves the fifth question by looping through the territories, storing the hazards YLL
 * value if it is greater than three percent (3%) of the base life expectancy, and replacing the
 * stored hazards YLL value if another territory has a lower value.
 * @param territories The array of the territories.
 * @returns The index of the territory in `territories`.
 */
int solve_question_five(Territory territories[DATASET_TERRITORIES_LENGTH]) {
    int index;
    Territory territory;
    double minimum_hazards_yll;
    double territory_minimum_hazards_yll;
    int minimum_hazards_yll_index = -1;

    for (index = 0; index < DATASET_TERRITORIES_LENGTH; index++) {
        territory = territories[index];
        minimum_hazards_yll = territory.base_life_expectancy * 0.03;

        if (territory.environmental_hazards_yll > minimum_hazards_yll ||
            territory.occupational_hazards_yll > minimum_hazards_yll) {
            if (territory.environmental_hazards_yll > minimum_hazards_yll) {
                territory_minimum_hazards_yll = territory.environmental_hazards_yll;
            } else {
                territory_minimum_hazards_yll = territory.occupational_hazards_yll;
            }

            if (minimum_hazards_yll_index == -1 ||
                (territory_minimum_hazards_yll <
                     territories[minimum_hazards_yll_index].environmental_hazards_yll ||
                 territory_minimum_hazards_yll <
                     territories[minimum_hazards_yll_index].occupational_hazards_yll)) {
                minimum_hazards_yll_index = index;
            }
        }
    }

    return minimum_hazards_yll_index;
}

/**
 * @brief Prints the answer to the fifth question to the passed results file.
 * @note This function runs `solve_question_five()` to get the answer to the question.
 * @param results_file The object of the output text file.
 * @param territories The array of the territories.
 */
void print_question_five_answer(FILE *results_file,
                                Territory territories[DATASET_TERRITORIES_LENGTH]) {
    Territory minimum_hazards_territory = territories[solve_question_five(territories)];
    double minimum_hazards_yll;

    if (minimum_hazards_territory.environmental_hazards_yll >
        minimum_hazards_territory.base_life_expectancy * 0.03) {
        minimum_hazards_yll = minimum_hazards_territory.environmental_hazards_yll;
    } else {
        minimum_hazards_yll = minimum_hazards_territory.occupational_hazards_yll;
    }

    fprintf(results_file, "Answer: %s (%lf)\n", minimum_hazards_territory.name,
            minimum_hazards_yll);
}

int main(void) {
    /* Declare your own local variables. Describe the purpose of your local variables. */

    /** @brief The object of the output text file. */
    FILE *results_file = fopen("OUTPUT_LASTNAME1_LASTNAME2.txt", "w");
    /** @brief The array of the territories. */
    Territory territories[DATASET_TERRITORIES_LENGTH];

    /*
     * Call the function that answers a question. Thereafter, use fprintf() NOT printf()
     * to output the the question and the corresponding answer onto OUTPUT_LASTNAME1_LASTNAME2.TXT.
     *
     * expectancy = Q1_Answer(territory, param_x, param_y); // where expectancy, territory, param_x
     * and param_y are local variables.
     *
     * fprintf(fp, "Q1: Which territory has the lowest baseline life expectancy?\n");
     * fprintf(fp, "A1: %s %lf\n", territory, expectancy);
     *
     *
     * You should have multiple test cases, i.e., functions calls to answer those
     * Questions that involve parameter(s).
     */

    load_data(territories);

    fprintf(results_file, "----- CCPROG2 MP : 2023-24 : Question 1 -----\n");

    fprintf(
        results_file,
        "Which territory has the highest change in life expectancy due to smoking that is not greater than <parameter_number> years?\n");

    print_question_one_answer(results_file, territories, 1.0);
    print_question_one_answer(results_file, territories, -2.0);
    print_question_one_answer(results_file, territories, 3.0);

    fprintf(results_file, "\n----- CCPROG2 MP : 2023-24 : Question 2 -----\n");

    fprintf(
        results_file,
        "What is the sum of the loss of life expectancy due to metabolic syndrome, dietary factors, and fasting plasma sugar for <parameter_territory_name>?\n");

    print_question_two_answer(results_file, territories, "Taiwan");
    print_question_two_answer(results_file, territories, "South_Korea");
    print_question_two_answer(results_file, territories, "Japan");

    fprintf(results_file, "\n----- CCPROG2 MP : 2023-24 : Question 3 -----\n");

    fprintf(
        results_file,
        "Does <parameter_territory_name> have a negligible change in life expectancy due to ozone (less than 0.01)?\n");

    print_question_three_answer(results_file, territories, "Taiwan");
    print_question_three_answer(results_file, territories, "South_Korea");
    print_question_three_answer(results_file, territories, "Japan");

    fprintf(results_file, "\n----- CCPROG2 MP : 2023-24 : Question 4 -----\n");

    fprintf(
        results_file,
        "What is the average change in life expectancy due to air pollution for the top <parameter_number> territories with the highest baseline life expectancy? List the respective territories.\n");

    print_question_four_answer(results_file, territories, 10);
    print_question_four_answer(results_file, territories, 0);
    print_question_four_answer(results_file, territories, 3);

    fprintf(results_file, "\n----- CCPROG2 MP : 2023-24 : Question 5 -----\n");

    fprintf(
        results_file,
        "What is the minimum change in life expectancy due to environmental/occupational hazards that is greater than 3%% of the respective territories' baseline life expectancy?\n");

    print_question_five_answer(results_file, territories);

    fclose(results_file);

    return 0;
}
