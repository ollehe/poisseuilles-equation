[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.svg#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/ydreP/poisseuilles-equation#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.svg#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/ydreP/poisseuilles-equation#gh-light-mode-only)

# Hagen–Poiseuille equation for determining the pressure drop in a cylindrical pipe. 
This short program computes the distribution of the pressure drop in a cylindrical pipe using [Hagen-Poiseuilles equation](https://en.wikipedia.org/wiki/Hagen%E2%80%93Poiseuille_equation).  

\[
\Delta p = \frac{8 \cdot \pi \cdot \mu \cdot L \cdot Q}{A^2}
\]

where:

- **μ**: Dynamic viscosity of the fluid (Pa·s)
- **L**: Length of the pipe (m)
- **Q**: Volumetric flow rate of the fluid (m³/s)
- **A**: Cross-sectional area of the pipe (m²)

The program simulates the flow of water at a temperature of 20°C, assuming the flow is laminar.

## Features

- **Laminar Flow Calculation**: Computes the pressure drop for laminar flow in a cylindrical pipe.
- **Randomized Parameters**: Utilizes uniform and log-normal distributions to model uncertainties in physical parameters such as pipe length, cross-sectional area, flow rate, and viscosity.
- **Extensible Design**: Provides a foundation for future enhancements, such as implementing a Reynolds number check for laminar flow or allowing user-defined fluid properties.

## Dependencies

- **Standard C Libraries**: `stdio.h`, `stdlib.h`, `math.h`
- **Signaloid UXHW Library**: `uxhw.h` (for uncertainty-aware calculations)

## Usage

Clone the repository and compile the code using a C compiler that supports the required libraries:

## Example

The program calculates the pressure drop for water flowing through a pipe with the following default parameters:

- **Pipe Length**: 1 m ± 0.01 m
- **Cross-Sectional Area**: 0.1 m² ± 0.001 m²
- **Mean Flow Rate**: 0.5 m³/s ± 0.0001 m³/s
- **Mean Dynamic Viscosity**: 0.001 Pa·s ± 0.002e-6 Pa·s

## References

- Viscosity of liquid water in the range −8 °C to 150 °C, https://doi.org/10.1063/1.555581

## Future Work

- Implement a check for laminar flow by calculating the Reynolds number.
- Modify the randomized parameters to better fit reality.



