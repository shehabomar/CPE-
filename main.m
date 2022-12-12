%--------------------------
% Omar Mohamed Atia Shehab 
% Date:   December 12, 2022  
%       Assignment4        
% Pipe Friction - The Friction Factor 
check = true;
while check
    disp("Choose a number: ");
    disp("1- Displays the numerical and analytical values for the friction factor.");
    disp("2- Conduct the analysis of how the friction factor varies with the conduit diameter.");    
    disp("3- Conduct the analysis of how the friction factor varies with the pipe roughness.");
    disp("4- Conduct the analysis of how the friction factor varies with the fluid density.");
    disp("5- Conduct the analysis of how the friction factor varies with the dynamic viscosity.");
    disp("6- Exit");
    choice = input("Enter an option: ");
    if choice == 1
        fluidDensity = input("please enter the fluid density between 0.5 to 2000: ");
        while (fluidDensity < 0.5 || fluidDensity > 2000)
            fluidDensity = input("Invalid, please enter the fluid density between 0.5 to 2000: ");    
        end

        fluidVisco = input("please enter the fluid viscosity between 10^-6 to 300: ");
        while (fluidVisco < 1e-6 || fluidVisco > 300)
            fluidVisco = input("Invalid, please enter the fluid viscosity between 10^-6 to 300: ");
        end
        D = input("please enter the diameter: ");
        V = input("please enter the velocity: ");
        epsilon = input("enter epsilon between 0.0001 to 3: ");
        epsilon = epsilon/1000;
        while (epsilon < 1e-6 || epsilon > 0.003)
            epsilon = input("invalid, enter epsilon between 0.0001 to 3: ");
        end
        Re = (fluidDensity*V*D)/fluidVisco;
        if (Re <= 4000)
            fprintf("Re should be greater than 4000 \n");
            break;
        end
        f0 = analyticalF(epsilon,Re,D);
        root = bisectionCalc(0.008,0.08,Re,D,epsilon);
        fprintf("analytical friction: %f\n",f0);
        fprintf("bisection: %f\n",root);
    elseif choice == 2
        fluidDensity = input("please enter the fluid density between 0.5 to 2000: ");
        while (fluidDensity < 0.5 || fluidDensity > 2000)
            fluidDensity = input("Invalid, please enter the fluid density between 0.5 to 2000: ");    
        end
        fluidVisco = input("please enter the fluid viscosity: ");
        while (fluidVisco < 1e-6 || fluidVisco > 300)
            fluidVisco = input("Invalid, please enter the fluid viscosity between 10^-6 to 300: ");
        end
        V = input("please enter the velocity: ");
        epsilon = input("enter epsilon between 0.0001 to 3: ");
        epsilon = epsilon/1000;
        while (epsilon < 1e-6 || epsilon > 0.003)
            epsilon = input("invalid, enter epsilon between 0.0001 to 3: ");
        end
        lower = input("enter the lower value for the conduit diameter: ");
        upper = input("enter the upper value for the conduit diameter: ");
        size = input("enter the size value for the conduit diameter: ");
        D = lower:size:upper; 
        Analytical_F = zeros(length(D),1);
        f = zeros(length(D),1);
        for i=1:length(D)    
            Re= (fluidDensity.*V.*D(i))./fluidVisco;
            Analytical_F(i) = analyticalF(epsilon,Re,D(i));
            f(i) = bisectionCalc(0.008,0.08,Re,D(i),epsilon);
        end
        if (Re <= 4000)
            fprintf('Re should be greater than 4000, try again \n');
            break;
        end
        plot(D, f,'b');
        xlabel('Conduit Diameter (D)');
        ylabel('Friction Factor');
        title('Friction Factor vs. Conduit Diameter');
        hold on;
        plot(D, Analytical_F,'--r');
        legend('Numerical', 'Analytical');
        hold off;
        saveas(gcf, 'FrictionFactor vs Conduit Diameter.png');
    elseif choice == 3
        fluidDensity = input("please enter the fluid density between 0.5 to 2000: ");
        while (fluidDensity < 0.5 || fluidDensity > 2000)
            fluidDensity = input("Invalid, please enter the fluid density between 0.5 to 2000: ");    
        end
        fluidVisco = input("please enter the fluid viscosity between 10^-6 to 300: ");
        while (fluidVisco < 1e-6 || fluidVisco > 300)
            fluidVisco = input("Invalid, please enter the fluid viscosity between 10^-6 to 300: ");
        end
        D = input("please enter the diameter: ");
        V = input("please enter the velocity: ");
        lower = input("enter the lower value for the Roughness: ");
        upper = input("enter the upper value for the Roughness: ");
        size = input("enter the size value for the Roughness: ");

        epsilon = lower:size:upper; 
        Analytical_F = zeros(numel(epsilon),1);
        R = zeros(numel(epsilon),1);
        Re = fluidDensity.*V.*D./fluidVisco;
        
        for i=1:numel(epsilon)    
            Analytical_F(i) = analyticalF(epsilon(i),Re,D);
            R(i) = bisectionCalc(0.008,0.08,Re,D,epsilon(i));
        end        
        if (Re <= 4000)
            fprintf('Re should be greater than 4000, try again \n');
            break;
        end
        plot(epsilon, R,'b');
        xlabel('Roughness (R)');
        ylabel('Friction Factor');
        title('Friction Factor vs. Roughness');
        hold on;
        plot(epsilon, Analytical_F,'--r');
        legend('Numerical','Analytical');
        hold off;
        saveas(gcf, 'FrictionFactor vs Roughness.png');

    elseif choice == 4
        fluidVisco = input("please enter the fluid viscosity between 10^-6 to 300: ");
        while (fluidVisco < 1e-6 || fluidVisco > 300)
            fluidVisco = input("Invalid, please enter the fluid viscosity between 10^-6 to 300: ");
        end
        D = input("please enter the diameter: ");
        V = input("please enter the velocity: ");
        epsilon = input("enter epsilon between 0.0001 to 3: ");
        epsilon = epsilon/1000;
        while (epsilon < 1e-6 || epsilon > 0.003)
            epsilon = input("invalid, enter epsilon between 0.0001 to 3: ");
        end
        lower = input("enter the lower value for the fluid density: ");
        upper = input("enter the upper value for the fluid density: ");
        size = input("enter the size value for the fluid density: ");      
        fd = lower:size:upper; 
        Analytical_F = zeros(numel(fd),1);
        R = zeros(numel(fd),1);
        for i = 1:numel(fd)
            Re = fd(i).*V.*D./fluidVisco;
            Analytical_F(i) = analyticalF(epsilon, Re, D);
            R(i) = bisectionCalc(0.008, 0.08, Re, D, epsilon);
        end
        if (Re <= 4000)
            fprintf('Re should be greater than 4000, try again \n');
            break;
        end
        plot(fd, R,'b');
        xlabel('Fluid Density');
        ylabel('Friction Factor');
        title('Friction Factor vs. Fluid Density');
        hold on;
        plot(fd, Analytical_F,'--r');
        legend('Numerical', 'Analytical');
        hold off;
        saveas(gcf, 'FrictionFactor vs Fluid Density.png');
    elseif choice == 5
        fluidDensity = input("please enter the fluid density between 0.5 to 2000: ");
        while (fluidDensity < 0.5 || fluidDensity > 2000)
            fluidDensity = input("Invalid, please enter the fluid density between 0.5 to 2000: ");    
        end
        D = input("please enter the diameter: ");
        V = input("please enter the velocity: ");
        epsilon = input("enter epsilon between 0.0001 to 3: ");
        epsilon = epsilon/1000;
        while (epsilon < 1e-6 || epsilon > 0.003)
            epsilon = input("invalid, enter epsilon between 0.0001 to 3: ");
        end
        lower = input("enter the lower value for the fluid viscosity: ");
        upper = input("enter the upper value for the fluid viscosity: ");
        size = input("enter the size value for the fluid viscosity: ");      
        fv = lower:size:upper; 
        Analytical_F = zeros(numel(fv),1);
        v = zeros(numel(fv),1);
        for i = 1:numel(fv)
            Re = fluidDensity.*V.*D./fv(i);
            Analytical_F(i) = analyticalF(epsilon, Re, D); 
            v(i) = bisectionCalc(0.008, 0.08, Re, D, epsilon);
        end
        if (Re <= 4000)
            fprintf('Re should be greater than 4000, try again \n');
            break;
        end
        plot(fv, v,'b');
        hold on;
        plot(fv, Analytical_F,'--r');
        xlabel('Fluid Density');
        ylabel('Friction Factor');
        title('Friction Factor vs. Fluid Density');
        legend('Numerical', 'Analytical');
        hold off;
        saveas(gcf, 'FrictionFactor vs Fluid Density.png');
    elseif choice == 6
        check = false;
    else
        disp("Not a valid number please try again: ");
    end
end



