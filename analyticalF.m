function [AnalyticalF] = analyticalF(r,Re,diameter)
    
    AnalyticalF = 1.325./(log((r/(3.7.*diameter))+(5.74./(Re.^0.9)))).^2;
end