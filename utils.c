//
// Created by kamil on 09.07.18.
//

#include "utils.h"

double round2(double number) {
    return round(100*number)/100;
}

int is_in_error_margin(double ground_truth, double value, double error_margin) {
    double diff = ground_truth*error_margin;
    double min = ground_truth - diff;
    double max = ground_truth + diff;
    if(value >= min && value <= max) {
        return 1;
    }
    return 0;
}