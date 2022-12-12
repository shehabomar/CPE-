function [bisection] = bisectionCalc(lowerBound,upperBound,Re,D,r)
    mid = (lowerBound + upperBound)/2;
    while abs(NumericalF(Re, D, r,lowerBound).*NumericalF(Re, D, r,mid)) >= 0.00001 
        
        if (NumericalF(Re, D, r,lowerBound)*NumericalF(Re, D, r,mid)) < 0
            upperBound = mid;
        else   
            lowerBound = mid;
        end
        mid = (lowerBound + upperBound)/2;
    end
    bisection = mid;
end  