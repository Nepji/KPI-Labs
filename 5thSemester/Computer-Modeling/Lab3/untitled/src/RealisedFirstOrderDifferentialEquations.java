import org.apache.commons.math3.exception.DimensionMismatchException;
import org.apache.commons.math3.exception.MaxCountExceededException;
import org.apache.commons.math3.ode.FirstOrderDifferentialEquations;


public class RealisedFirstOrderDifferentialEquations implements FirstOrderDifferentialEquations{
    @Override
    public int getDimension() {
        return 2;
    }

    @Override
    public void computeDerivatives(double t, double[] doubles, double[] doublesArray) throws MaxCountExceededException, DimensionMismatchException {
        doublesArray[0] = 4 * t + doubles[0] - doubles[1] + 6;
        doublesArray[1] = -doubles[0] + 4 * doubles[1];
    }
}