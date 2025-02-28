package lr;
import java.text.DecimalFormat;
import java.util.Scanner;

public class RgrTr15Rude {
    public static void main(String[] args) {
        Scanner opo = new Scanner(System.in);
        int Ex, i, j, choose;
        System.out.print("Choose the Ex: ");
        Ex = opo.nextInt();
        System.out.print("----------------------------------------\n");
        if (Ex == 1) {
            ////////////////////////////////////////////////////////////
            System.out.println("Початок виконання завдання <1>\n\nДанні згідно варіанту №1:");
            double[][] GauseGun ={  {0, -2, 4, 5, 1, -1.6},
                                    {3, 3, -5, 2, 4, -36.4},
                                    {-4, -1, 5, 5, 5, -33.5},
                                    {-1, -5, 0, -1, -2, 63.7},
                                    {0, 2, 3, 2, 2, -48.7}  };

            for (i = 0; i < GauseGun.length; i++) {
                System.out.print("{");
                for (j = 0; j < GauseGun[i].length; j++) {
                    System.out.print("(" + GauseGun[i][j] + ")");
                    if (j == GauseGun[i].length - 2) {
                        System.out.print("== ");
                    } else if (j < GauseGun[i].length - 2) {
                        System.out.print(" +");
                    }
                }
                System.out.print("}\n");
            }
            ////////////////////////////////////////////////////////////
            System.out.print("Бажаєте ввести зміни?\n<1> - так.\n<0> - ні.\nВибір: ");
            choose = opo.nextInt();
            System.out.print("----------------------------------------\n");
            if (choose == 1) {
                System.out.println("Ввід значень для масиву розміром 5х6.");
                for (i = 0; i < 5; i++) {
                    System.out.printf("Введіть 6 значень через пробіл для рядка №%d: ", i + 1);
                    for (j = 0; j < 6; j++) {
                        GauseGun[i][j] = opo.nextDouble();
                    }
                }

            } else if (choose < 0 || choose > 1) {
                System.out.println("Відповідь сприйнята як <0>");
            }
            ////////////////////////////////////////////////////////////////
            //Створення буферного масиву
            double[][] TOR = new double[7][6];
            //Виклик методу task13 перший раз
            for(i=0;i<5;i++)
                for(j=0;j<6;j++)
                    TOR[i][j]=GauseGun[i][j];
            TOR[6][1]=1;
            task13(TOR);
            //Виклик методу task13 другий раз
            double[][] triGause = task11(GauseGun);
            for(i=0;i<5;i++)
                for(j=0;j<6;j++)
                    TOR[i][j]=triGause[i][j];
            task13(TOR);
            //Виклик методу task13 третій раз
            double[] x = task12(triGause);
            for(i=0;i<5;i++)
                TOR[1][i]=x[i];
            TOR[6][1]=3;
            task13(TOR);
            /////////////////////////////////////////////////////////////////
            }
         else if (Ex == 2) {
            System.out.println("Початок виконання завдання <2>");
            for (j = 0; j < 3; j++) {
                System.out.println("Введіть натуральне число: ");
                int vol = opo.nextInt();
                int[] sum = task2(vol);
                System.out.print("Сумма натуральних чисел: ");
                for (i = 0; i < sum.length - 2; i++) System.out.print(sum[i + 1] + " ");
                int rez = sum[sum.length - 1];
                System.out.print(" = " + rez + "\n");
            }
        } else {
            System.out.print("Error...Incorrect choose.");
            System.exit(0);
        }


    }
    //Методи
    public static double[][] task11(double[][] GauseGun){

        double[][] triGun = new double[5][6];
        int z =0;
        //Створення ще одного масиву за для розєднання від основного масиву
        while (z<GauseGun.length){
            for (int j = 0;j<GauseGun[0].length;j++){
                triGun[z][j] = GauseGun[z][j];
            }
            z++;
        }
        double k;
        int y = 0;
        int ZERO = -1;
        int left = 0;
        //Перевырка нулів в матриці та виконання методу Гауса
        for (int g = left;g<triGun.length-1;g++) {
            if(triGun[g][g] == 0){
                for (int i = g;i<triGun.length;i++)
                    if(triGun[i][g] != 0){
                        ZERO = i;
                        break;
                    }

                if(ZERO>=0)
                    for (int i = g; i < triGun[0].length; i++)
                        triGun[g][i] = triGun[g][i] + triGun[ZERO][i];
                else if(ZERO == -1)
                    left++;
            }
            if(g<triGun[0].length) {
                for (int i = 1 + g; i < triGun.length; i++) {
                    if (triGun[g][g+y] !=0) {
                        k = triGun[i][g+y] / triGun[g][g+y];
                        for (int j = g; j < triGun[0].length; j++) {
                            triGun[i][j] = triGun[i][j] - triGun[g][j] * k;
                        }
                    }
                    else {
                        i--;
                        y++;
                    }
                }
            }
        }
        return triGun;
    }

    private static double[] task12(double[][] triGause) {
        int i, j;
        double[] x = new double[5];
        for (i = triGause.length - 1; i >= 0; i--) {
            x[i] = triGause[i][triGause.length] / triGause[i][i];
            for (j = triGause.length - 1; j > i; j--) {
                x[i] = x[i] - triGause[i][j] * x[j] / triGause[i][i];
            }
        }
        return x;
    }

    private static void task13(double[][] TOR) {
        DecimalFormat DF = new DecimalFormat("##.###");
        int i, j, loky;
        loky = (int) TOR[6][1];
        //Створення нового масиву за для розєднання від буферного масиву
        double[][] LOKY = new double[5][6];
        for(i=0;i<5;i++)
            for(j=0;j<6;j++)
                LOKY[i][j] = TOR[i][j];
        //Вивід первинного масиву або трикутного масиву
        if (loky == 1) 
            {
                System.out.print("\nЗначення масиву:\n");
                for (i = 0; i < LOKY.length; i++) {
                    System.out.print("{");
                    for (j = 0; j < LOKY[i].length; j++) {
                        System.out.printf(DF.format(LOKY[i][j]));
                        if (j < LOKY[i].length - 1) {
                            System.out.print("| ");
                        }
                    }
                    System.out.print("}\n");
                }
                System.out.print("----------------------------------------\n");
              
            }
        //Вивід вектору результатів
        else if (loky == 3) 
            {
                System.out.println("----------------------------------------\nРезультати Х: ");
                for (i = 0; i < 6;i++) {
                    System.out.println("Значення Х" + i + " = " + DF.format(LOKY[1][i]));
                }
            }
        
        }

    private static int[] task2 ( int vol){
            int i, s = 0;
            int num = (int) Math.log10(vol) + 1;
            int[] sum = new int[num + 2];
            //Обробка заданого числа, вирахунок суми та запис використаних чисел
            for (i = 0; vol != 0; i++) {
                sum[i] = vol % 10;
                s += vol % 10;
                vol /= 10;
            }
            //Сортування чисел суми
            boolean
                    sorted = false;
            int temp;
            while (!sorted) {
                sorted = true;
                for (i = 0; i < sum.length - 2; i++) {
                    if (sum[i] > sum[i + 1]) {
                        temp = sum[i];
                        sum[i] = sum[i + 1];
                        sum[i + 1] = temp;
                        sorted = false;
                    }
                }
            }
            sum[num + 1] = s;
            return sum;
        }
    }






