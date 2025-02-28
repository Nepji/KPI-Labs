import org.apache.commons.math3.ode.FirstOrderDifferentialEquations;
import org.apache.commons.math3.ode.FirstOrderIntegrator;
import org.apache.commons.math3.ode.nonstiff.EulerIntegrator;
import org.apache.commons.math3.ode.nonstiff.ClassicalRungeKuttaIntegrator;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        double x0 = 0, y0 = 0, tStart = 0, tEnd = 1, stepStart = 0.1;
        double precision = 0.1;
        var equations = new RealisedFirstOrderDifferentialEquations();
        Euler(equations,x0,y0,tStart,tEnd,stepStart, precision);
        x0 = 0; y0 = 0; tStart = 0; stepStart = 0.1;
        RK4(equations,x0,y0,tStart,tEnd,stepStart, precision);

    }

    private static double FX(double x0, double y0, double t)
    {
        return 4*t+x0-y0+6;
    }
    private static double FY(double x0, double y0, double t1)
    {
        return -x0+4*y0;
    }

    private static double solveEulerLib(FirstOrderDifferentialEquations equations, double x0, double y0, double tStart, double tEND, double stepStart, double precision){
        double[]eulerResult = {x0,y0}, oldEulerRes;
        List<double[]> res = new ArrayList<>();
        int itter = 0;
        res.add(new double[]{itter,eulerResult[0],eulerResult[1]});
        do {
            oldEulerRes = eulerResult;
            eulerResult = solve(new EulerIntegrator(stepStart), equations,x0, y0,tStart,tEND);
            stepStart /= 2;
            itter++;
            res.add(new double[]{itter,eulerResult[0],eulerResult[1]});
        }while (calculateRootMSquereError(eulerResult,oldEulerRes) > precision);
        print(res,stepStart*2,"Euler Library");
        return  stepStart;
    }
    private static void Euler(RealisedFirstOrderDifferentialEquations equations, double x0, double y0, double tStart, double tEnd, double stepStart, double precision) {
        stepStart = solveEulerLib(equations,x0,y0,tStart,tEnd,stepStart, precision) * 10;
        double[] eulerRes = {x0, y0};
        int INTER = 0;
        List<double[]> result = new ArrayList<>();
        result.add(new double[]{INTER, eulerRes[0], eulerRes[1]});

        for (; tStart < tEnd; tStart += stepStart) {
            double dxdt = FX(x0, y0, tStart);
            double dydt = FY(x0, y0, tStart);

            x0 += stepStart * dxdt;
            y0 += stepStart * dydt;

            eulerRes = new double[]{x0, y0};
            INTER++;

            result.add(new double[]{INTER, eulerRes[0], eulerRes[1]});
        }

        print(result, stepStart, "Own Euler");
    }



    private static void RK4(RealisedFirstOrderDifferentialEquations equations, double x0, double y0, double tStart, double tEND, double stepStart, double precision){
        stepStart = solveRK4Lib(equations,x0,y0,tStart,tEND,stepStart, precision);
        List<double[]> res = new ArrayList<>();
        res.add(new double[]{1, x0, y0});

        for (double t = tStart; t < tEND; t += stepStart) {
            double kf1x = stepStart * FX(x0, y0, t);
            double kf1y = stepStart * FY(x0, y0, t);

            double kf2x = stepStart * FX(x0 + kf1x / 2, y0 + kf1y / 2, t + stepStart / 2);
            double kf2y = stepStart * FY(x0 + kf1x / 2, y0 + kf1y / 2, t + stepStart / 2);

            double kf3x = stepStart * FX(x0 + kf2x / 2, y0 + kf2y / 2, t + stepStart / 2);
            double kf3y = stepStart * FY(x0 + kf2x / 2, y0 + kf2y / 2, t + stepStart / 2);

            double kf4x = stepStart * FX(x0 + kf3x, y0 + kf3y, t + stepStart);
            double kf4y = stepStart * FY(x0 + kf3x, y0 + kf3y, t + stepStart);

            x0 += (kf1x + 2 * kf2x + 2 * kf3x + kf4x) / 6;
            y0 += (kf1y + 2 * kf2y + 2 * kf3y + kf4y) / 6;

            res.add(new double[]{res.size() + 1, x0, y0});
        }

        print(res, stepStart, "Own Runge-Kutta 4s");;
    }
    private static double solveRK4Lib(FirstOrderDifferentialEquations equations, double x0, double y0, double tStart, double tEND, double stepStart, double precision){
        double[] rungeKuttaRes = {x0,y0}, oldRungeKuttaRes;
        List<double[]> res = new ArrayList<>();
        int INTER = 0;
        res.add(new double[]{INTER,rungeKuttaRes[0],rungeKuttaRes[1]});

        do {
            oldRungeKuttaRes = rungeKuttaRes;
            rungeKuttaRes = solve(new ClassicalRungeKuttaIntegrator(stepStart), equations,x0, y0,tStart,tEND);
            stepStart/=2;
            INTER++;
            res.add(new double[]{INTER,rungeKuttaRes[0],rungeKuttaRes[1]});
        }while (calculateRootMSquereError(rungeKuttaRes, oldRungeKuttaRes) > 0.1);
        print(res,stepStart*2,"RungeKutta 4s Library");
        return stepStart*2;
    }


    private static  double calculateRootMSquereError(double[] current, double[] precision){
        double sumSquaredDifferences = 0.0;
        for (int i = 0; i < current.length; i++) {
            double difference = current[i] - precision[i];
            sumSquaredDifferences += difference * difference;
        }
        double meanSquaredDifference = sumSquaredDifferences / current.length;
        return Math.sqrt(meanSquaredDifference);
    }

    private static double[] solve(
            FirstOrderIntegrator integrator,
            FirstOrderDifferentialEquations equations,
            double initialX,
            double initialY,
            double initialTime,
            double endTime
    ) {
        double[] initialValues = new double[]{initialX, initialY};
        integrator.integrate(equations, initialTime, initialValues, endTime, initialValues);
        return initialValues;
    }


    private static void print(List<double[]> list, double step, String method) {
        System.out.println("Method: "+method);
        System.out.println("┌─────┬──────────────────────┬──────────────────────┐");
        System.out.println("│  I  │           X          │           Y          │");
        System.out.println("├─────┼──────────────────────┼──────────────────────┤");

        if (list.size() > 50) {
            System.out.printf("│%5.0f│ %20.5f │ %20.5f │%n", list.get(0)[0], list.get(0)[1], list.get(0)[1]);
            System.out.printf("│%5.0f│ %20.5f │ %20.5f │%n", list.get(1)[0], list.get(1)[2], list.get(1)[2]);
            System.out.printf("│%5.0f│ %20.5f │ %20.5f │%n", list.get(list.size()/2)[0], list.get(list.size()/2)[1], list.get(list.size()/2)[2]);
            System.out.printf("│%5.0f│ %20.5f │ %20.5f │%n", list.get(list.size()-2)[0], list.get(list.size()-2)[1], list.get(list.size()-2)[2]);
            System.out.printf("│%5.0f│ %20.5f │ %20.5f │%n", list.get(list.size()-1)[0], list.get(list.size()-1)[1], list.get(list.size()-1)[2]);
        } else {
            for (double[] data : list) {
                System.out.printf("│%5.0f│ %20.5f │ %20.5f │%n", data[0], data[1], data[2]);
            }
        }
        System.out.println("└─────┴──────────────────────┴──────────────────────┘");
        System.out.println("┌─────┬──────────────────────┬──────────────────────┐");
        System.out.println("│ Id  │    Parametr          │      Value           │");
        System.out.println("├─────┼──────────────────────┼──────────────────────┤");
        System.out.printf("│ 1   │    Steps             │ %20.5f │%n", (double)list.size());
        System.out.printf("│ 2   │    Step`s Size       │ %20.5f │%n", step);
        System.out.println("└─────┴──────────────────────┴──────────────────────┘");
    }
}