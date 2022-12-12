function [numnericalF] = NumericalF(Re, diameter, roughness,frictionfactor)
    numnericalF = ((1./sqrt(frictionfactor)) + 2.*log10(roughness./(3.7.*diameter) + 2.51./(Re.*sqrt(frictionfactor))));
end