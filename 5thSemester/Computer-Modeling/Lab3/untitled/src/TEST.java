import java.util.ArrayList;
import java.util.List;

public class TEST {
    public static void main(String[] args) {
        double x0 = 0, y0 = 0, tStart = 0, tEnd = 1, stepStart = 1.953125E-4 ;
        RK4(x0,y0,tStart,tEnd,stepStart);
    }

    private static double FX1(double x0, double y0, double t)
    {
        return 4*t+x0-y0+6;
    }

    private static double FY1(double x0, double y0, double t1)
    {
        return -x0+4*y0;
    }

    private static void RK4(double x0, double y0, double tStart, double tEnd, double stepStart) {
        List<double[]> res = new ArrayList<>();
        int itter = 1;
        res.add(new double[]{itter, x0, y0});

        while (tStart < tEnd) {
            double k1x = stepStart * FX1(x0, y0, tStart);
            double k1y = stepStart * FY1(x0, y0, tStart);

            double k2x = stepStart * FX1(x0 + k1x / 2, y0 + k1y / 2, tStart + stepStart / 2);
            double k2y = stepStart * FY1(x0 + k1x / 2, y0 + k1y / 2, tStart + stepStart / 2);

            double k3x = stepStart * FX1(x0 + k2x / 2, y0 + k2y / 2, tStart + stepStart / 2);
            double k3y = stepStart * FY1(x0 + k2x / 2, y0 + k2y / 2, tStart + stepStart / 2);

            double k4x = stepStart * FX1(x0 + k3x, y0 + k3y, tStart + stepStart);
            double k4y = stepStart * FY1(x0 + k3x, y0 + k3y, tStart + stepStart);

            x0 = x0 + (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
            y0 = y0 + (k1y + 2 * k2y + 2 * k3y + k4y) / 6;

            tStart += stepStart;
            itter++;

            res.add(new double[]{itter, x0, y0});
        }
        print(res, stepStart, "Own Runge-Kutta");
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
