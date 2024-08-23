/*
 * Program: Pressure Drop in a Cylindrical Pipe Using Poiseuille’s Equation
 * Author: [Olle Hallqvist Elias]
 * Date: [22/8/2024]
 * 
 * Overview:
 * This program calculates the pressure drop for a laminar flow of fluid through a cylindrical pipe using Poiseuille’s equation:
 * 
 *     Δp = (8 * π * μ * L * Q) / A^2
 * 
 * where:
 *     μ is the dynamic viscosity of the fluid (Pa·s)
 *     L is the length of the pipe (m)
 *     Q is the volumetric flow rate of the fluid (m^3/s)
 *     A is the cross-sectional area of the pipe (m^2)
 * 
 * The program assumes the fluid is water at 20°C, and the flow is laminar.
 * 
 * Dependencies:
 * - Standard C libraries: stdio.h, stdlib.h, math.h
 * - Signaloid UXHW library: uxhw.h
 * Input:
 * The program internally sets the fluid properties (e.g., viscosity) and pipe dimensions.
 * 
 * Output:
 * The program prints the pressure drop in Pascals (Pa).
 * 
 * Example:
 * The program calculates the pressure drop for a water flow at a temperature of 20 °C with a given set of parameters and outputs the result.
 * 
 * References:
 * - Viscosity of liquid water in the range −8 °C to 150 °C, https://doi.org/10.1063/1.555581
 * 
 * Future Work:
 * - Implement a check for laminar flow by calculating the Reynolds number.
 */
#include <stdio.h>
#include <stdlib.h>
#include <uxhw.h>
#include <math.h>
// Struct for fluid 
struct Fluid {
    double mean_flow_rate; // (m^3/s)
    double flow_rate_stdev; // (m^3/s)

    double mean_dynamic_viscosity; // (Pa·s)
    double dynamic_viscosity_stdev; // (Pa·s)

};
// Struct for pipe 
struct Pipe {

    double length; // (m)
    double length_tolerance; // (m)

    double cross_section; // (m^2)
    double cross_section_tolerance; // (m^2)

};

/*
 * Function: computePressureDifference
 * -----------------------------------
 * Computes the pressure drop in the pipe using Poiseuille’s equation.
 * 
 * fluid: Pointer to a Fluid struct containing the fluid properties.
 * pipe: Pointer to a Pipe struct containing the pipe properties.
 * 
 * returns: The pressure drop in Pascals (Pa).
 * Notes: 
 *      - Model is only valid if the length of the pipe is sufficiently long, and the cross-sectional area is not too large. 
 *      - Possible modification/extension is to add a test to check whether quantities actually give a laminar flow. 
 *        A suitable test would be to compute the Reynolds number, would require an extension of the fluid struct to incorporate more physical quantities of the fluid.
 *      - A more accurate representation would be to find empirical distributions of the random distributions. 
 *      - Could include a test verifying that quantities such as the length and cross-sectional area are always positive. 
 */
double computePressureDifference(struct Fluid* fluid, struct Pipe* pipe) {
    
    // Pipe quantities: 
    // Distributions: pipe_length, cross section are chosen as uniform random variables over intervals of the form: mean ± error
    double pipe_length = UxHwDoubleUniformDist(pipe->length-pipe->length_tolerance, pipe->length + pipe->length_tolerance);
    double cross_section = UxHwDoubleUniformDist(pipe->cross_section-pipe->cross_section_tolerance, pipe->cross_section+pipe->cross_section_tolerance);

    //Fluid quantities: 
    // dynamic viscosity is chosen as log-normal with small variance, flow_rate chosen as uniform over an interval of the form: mean ± error
    double flow_rate = UxHwDoubleUniformDist(fluid->mean_flow_rate-fluid->flow_rate_stdev, fluid->mean_flow_rate+fluid->flow_rate_stdev);
    double viscosity = UxHwDoubleLognormalDist(fluid->mean_dynamic_viscosity, fluid->dynamic_viscosity_stdev);

    //Poiseulle's equation
    return 8*M_PI*pipe_length*flow_rate*viscosity/(cross_section*cross_section);

}

int main() {
    /* Initialize the fluid and the pipe:
    - This example assumes that the fluid is water for this example at a fixed temperature of 20 degrees celcius 
    - Viscosity measurements are from : Viscosity of liquid water in the range −8 °C to 150 °C, https://doi.org/10.1063/1.555581
    - Flow rate should be relatively low since we are in a laminar setting, good flow meters have a precision of 0.1 % (according to Google)
    */
    struct Fluid water = {
        .mean_dynamic_viscosity = 0.001, 
        .dynamic_viscosity_stdev = 0.002e-6, 
        .mean_flow_rate = 0.5 , 
        .flow_rate_stdev = 0.0001  
    };
    struct Pipe p = {
        .length = 1 , 
        .length_tolerance = 0.01 , 
        .cross_section = 0.1 , 
        .cross_section_tolerance = 0.001
    };
    // Compute and print the pressure difference

    double pressure_difference = computePressureDifference ( &water, &p );
    printf("Pressure difference is given by: %f Pa", pressure_difference);

	return 0;
}
